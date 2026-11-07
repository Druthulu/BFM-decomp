---
ts: 2026-11-06T12:30:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q8Ap2eS1B2uIwBtQlxjv
---
s2 (barrier [4] removed): the delay slot of the beqz at 2254/225c: target has `addiu v0,s1,1` in the beqz delay slot (the copy of the increment into the taken thread), mine leaves it later. That's the reorg behavior explained in the comment. To crack this without the asm barrier, we need the fall-through head to be ineligible. The comment says the barrier makes it ineligible. Real C alternative? Hmm.

s3 (memory barrier removed): the final store D_801151D0 = ot moved: target keeps it AFTER the OT read-modify-write; without the barrier, sched2 hoists it above. A real-C fix: make the store dependent on the RMW? E.g., `D_801151D0 = (s32)ot;` — ot is used in the RMW; sched2 hoists the store because it thinks the objects don't alias (D_801151D0 is a scalar, D_800AE7B8[..].f4[2] is mem/s). Real C: use the same object/alias so the scheduler can't hoist. E.g., if D_801151D0 were accessed as mem/s... The comment says sched2 disambiguates them.

Hmm, what if we reorder the C so the store naturally comes last? It already does. The scheduler hoists it because of the alias analysis.

Real C alternative: make the store depend on a value computed by the RMW: `D_801151D0 = (s32)(ot + 0);`? folds. `D_801151D0 = (s32)(ot); ot += 10;` — already.

Wait, look at the C:
```
ot[0] = 0x2000000;
ot[0] = (D_800AE7B8[*pb].f4[2] & 0xFFFFFF) | 0x2000000;
D_800AE7B8[*pb].f4[2] = (D_800AE7B8[*pb].f4[2] & 0xFF000000) | (((u32)ot) & 0xFFFFFF);
ot += 10;
__asm__ __volatile__("" ::: "memory");
D_801151D0 = (s32)ot;
```
s3 diff: mine has `lui at; sw s0,0(at)` at insn 160 (before the RMW?), target at 165-167 (after). So without the memory barrier, sched2 hoists the D_801151D0 store.

Real C: make the store's value depend on the RMW result. E.g., if we write the store as part of the same expression:
```
D_801151D0 = (s32)(ot += 10);
```
Would that help? The store still doesn't depend on the RMW.

Hmm, the RMW is on D_800AE7B8[*pb].f4[2] (a global array element) and the store is D_801151D0. sched2's alias analysis thinks they don't alias (mem/s vs scalar). To make them alias, we could read the f4[2] into a variable and use it... e.g.:

```
u32 v = D_800AE7B8[*pb].f4[2];
D_800AE7B8[*pb].f4[2] = (v & 0xFF000000) | (((u32)ot) & 0xFFFFFF);
ot += 10;
D_801151D0 = (s32)ot;
```
Still no dependency.

What if the stored value depends on the RMW value? No, the value is ot.

Real C cannot easily force an ordering without a barrier... unless we make the two stores to the same alias set. Hmm.

What if we use a pointer for the D_801151D0 store that the compiler can't disambiguate: e.g., `*(s32 *)&D_801151D0 = (s32)ot;`? That's the same scalar.

What if we write through a pointer variable: `s32 *gp = &D_801151D0; *gp = (s32)ot;` — the compiler might still know the address. With -O2, gcc's alias analysis may treat `*gp` as unknown → could alias the array store → keeps the order! Let's try.

Actually, sched2 runs on RTL and uses alias sets from the MEM rtx. `*gp` where gp is a pseudo holding &D_801151D0 → the MEM is (reg) → alias set 0 (unknown) → conflicts with everything. That would prevent hoisting!

But it would also change the instruction: `lui at; sw s0,0(at)` — target has `lui at,0x0; sw s0,0(at)` with a relocation to D_801151D0. With *gp, the compiler may still fold the address into the store (since gp is a known constant address? if gp is a local initialized to &D_801151D0, gcc's cse may fold). Let me try.

Let me test the memory-barrier replacement idea: `s32 *gp = &D_801151D0; *gp = (s32)ot;`.

Also for s2 (barrier [4]): the reorg issue. Real-C alternatives: the barrier makes the fall-through head ineligible. The comment: "Without it reorg's fill_eager_delay_slots takes the fall-through's `addu $a0,$s0,$zero` into the `beqz`'s delay slot; the target instead copies `addiu $v0,$s1,1` out of the TAKEN thread". Hmm, this is about the beqz at 2254 (the `if (*(s16*)... != 0)` test). The target's delay slot has `addiu v0,s1,1` (the i+1 increment from the loop tail, hoisted into the taken thread).

Real C: reorder the loop body so the increment's copy is in the taken thread? The C is:
```
if (*(s16 *)(...) != 0) {
    ot = xf8017E1D4(ot, panel, (s32)i);
}
i = i + 1;
```
Target: the `i+1` (addiu v0,s1,1) appears in the beqz delay slot AND at 225c (after the call). The increment is computed in the delay slot (taken thread = the if body) and then again in the fall-through. That's a reorg artifact.

To reproduce without the asm barrier: maybe restructure so the fall-through's first insn is not `addu a0,s0,zero`. The fall-through head is the if body: `move a0,s0` (ot arg). The barrier makes it ineligible for the delay slot.

Real C: reorder the call arguments? The call is `xf8017E1D4(ot, panel, (s32)i)`. The first arg setup `move a0,s0`. If we compute something else first in the body... e.g., `(s32)i` is already in a2? Target at 224c: `move a0,s0`; 2250 jal; 2254 move a1,s3 (delay); 2258 move s0,v0; 225c addiu v0,s1,1.

Hmm wait, the target's beqz at 2244 has delay slot `addiu v0,s1,1` (2248). Then the body: move a0,s0; jal; move a1,s3 (delay); move s0,v0; addiu v0,s1,1; then 2260 move s1,v0.

So the increment appears twice: once in the beqz delay slot and once at 225c. Mine (no barrier): the beqz delay slot gets the body's `move a0,s0`, and the taken thread is restructured.

Real C: make the fall-through head ineligible. What if the body's first statement is not a simple copy? E.g., if the call's first argument expression is complex: `ot = xf8017E1D4((s32 *)ot, ...)` — same.

What if we reorder the arguments: `xf8017E1D4(ot, panel, i)` — the arg setup order a0,a1,a2. The first move is a0. To make the head ineligible, the first insn could be something not fillable, e.g., a load or a call... 

What if we put `panel = panel + 0x20;` at the start of the if body? Then the body's first insn is `addiu s3,s3,32`? But the target has panel += 0x20 at the loop tail (2274 delay slot of bnez). Moving it changes code.

Hmm, what about using a different C form for the call that changes the arg-setup order: e.g., `ot = xf8017E1D4(ot, panel, i + 0);`?

This is getting deep. Let me first check whether the pin (s4=3) is the most crackable, then decide which subset to pursue.

Actually, let me reconsider the goal: PARTIAL is acceptable. If I can crack ONE kind while keeping the other two at 0, that's a PARTIAL. E.g., crack the pin (keep barrier+keepalive) → need score 0. s4 (pin removed, barriers+keepalive kept) = 3. Crack the barrier [4] (keep pin+keepalive) = s2 = 4. Crack the memory barrier = s3 = 4. Crack the keepalive = s1 = 8.

So the closest is s4 (pin, 3). Let me try to close s4: the missing `move v0,v1` (cnt copy).

Idea: `cnt = n;` → what if we write `cnt = n + 0;` and gcc's `-fno-...`? No.

What if cnt is declared `s32 cnt = n;`? Same.

What if we use `cnt = n, i = 0;`? Same.

Hmm, what if `cnt` is computed from `lim` instead: `lim = n; if (lim != 0) { cnt = lim; ...}`? Then the guard tests lim (in a temp) and the loop uses lim. Target: guard tests v0 (cnt), loop bound s2 (lim). If we write:

```
lim = n;
i = 0;
if (lim != 0) {
    ...
    } while ((s32)i < lim);
}
```
Then lim is one variable, used in the guard and the loop → gcc keeps lim in a callee-saved reg (s2) because it crosses the call. The guard would test s2, not v0. Mismatch.

The target's guard tests a COPY (v0) of n, while lim (s2) holds another copy. So the source has two variables: cnt (guard) and lim (loop bound). The guard uses cnt; the loop uses lim. `cnt = n; lim = cnt;`.

Since cnt dies at the guard and lim is born right after, coalescing is possible but gcc ALSO must place lim in a callee-saved reg (crosses the call). Coalescing cnt and lim would put both in s2; the guard would then test s2. Target tests v0, so no coalescing. Why not? Because `lim = cnt + zr` is a plus.

Real C: `lim = cnt;` is a copy → coalesce. So we need a real op.

What if `lim = cnt + i;` where i = 0 at that point? i is set to 0 in the delay slot of the guard (target: move s1,zero at 2220). In C, `i = 0;` comes before the if:
```
cnt = n + zr;
i = 0;
if (cnt != 0) {
    lim = cnt + zr;
```
If we write `lim = cnt + i;` with i=0 known, gcc folds (i is a known constant 0). Unless i is a variable whose value gcc can't prove... it's assigned 0 right before. Folds.

What if the order is `lim = cnt + i` where i is s16 and gcc can't prove? It can.

Hmm.

What if `lim = cnt` is written as `lim = (s32)(u16)cnt`? Extra andi.

What if cnt is a pointer and lim = (s32)cnt... no.

Let me try a batch of quick variants on s4 to find the cnt copy:
u1: `cnt = n & 0xFFFF;` (andi — opcode mismatch but let's see the score)
u2: `cnt = n + i;` with i=0 before
u3: `cnt = n;` with `if (n != 0)` and lim = cnt
u4: pointer trick: `s32 *cp = &n; cnt = *cp;` (forces n to stack — probably bad)
u5: `cnt = n; lim = cnt;` with the guard `if (cnt != 0)` but cnt declared after n... same
u6: use `cnt = n, n = cnt;`? 
u7: `cnt = n;` then `lim = cnt;` and use `cnt` in the loop condition as well: `} while ((s32)i < lim && cnt != 0);` — changes code.
u8: `cnt = n | 0;` folds.
u9: `cnt = n - (i = 0);`? 

Honestly, the `+ zr` pin is a well-known GCC-2.7.2 trick for opaque copies, and the comment says plain C coalesces. This is likely a WALL for the pin.

Let me check the keepalive (s1=8) diff — maybe it's crackable with a real ref (like do-while ref weight, which is exactly its purpose: pricing). The comment says the keepalive buys +1 ref on lim for §137 allocno pricing (lim vs panel for $s2/$s3). A do-while(0) adds REG_N_REFS += loop_depth! That's exactly the "do-while ref weight" move from moves line 25. Let me try wrapping the loop body in a do-while? The loop is already a do-while. Hmm, the keepalive is before the loop on lim.

The pricing: lim needs more refs so it gets $s2 over panel. A do{}while(0) around the loop would increase the loop_depth of the refs inside the loop (including lim's ref in the condition), raising lim's priority. Let me try wrapping the whole loop in an outer do-while(0):

```
do {
    if (cnt != 0) {
        lim = cnt;
        do { ... } while ((s32)i < lim);
    }
} while (0);  // !FAKE: do-while
```
That adds a loop level; lim's ref in the inner condition gets REG_N_REFS += loop_depth(2)? Let me check how gcc counts: REG_N_REFS += loop_depth for each reference. The keepalive asm adds +1 ref to lim (per operand? the comment says a 2-operand asm buys +1).

A do-while(0) around the loop would add +1 (or more) to every ref inside, including panel's refs. Hmm, panel is used inside the loop too (panel = panel + 0x20). So both get boosted equally — no relative change. The keepalive adds a ref only to lim.

Alternatively, put lim in a do-while(0) context alone? `do { lim = cnt; } while (0);` — lim's ref count +1 (the loop_depth applies to the ref inside). Let me try that: replace the keepalive asm with `do { lim = cnt; } while (0);`? But then lim = cnt is inside a loop; the assignment's ref to lim gets +1. That might replicate the pricing!

Actually, the keepalive is AFTER `lim = cnt` and before the loop:
```
lim = cnt + zr;
__asm__ __volatile__("" :: "r"(lim), "r"(lim));   /* +1 ref */
do { ... } while ((s32)i < lim);
```
So it adds one extra ref to lim.

A do-while(0) around `lim = cnt;` would add +1 to the ref of lim in that assignment (REG_N_REFS += loop_depth, loop_depth=1). Let me try:

```
do { lim = cnt; } while (0);  // !FAKE: do-while
```
This keeps semantics and might reproduce the pricing. Let's test on top of s1 (keepalive removed): replace the keepalive line with that. Also test on orig (keeping the pin).

Similarly for the barriers: maybe do-while block splits can replace them (C0535).

Let me generate these variants:
w1: orig with keepalive → `do { lim = cnt + zr; } while (0);` (pin kept)
w2: s1 with `do { lim = cnt; } while (0);` (pin removed too? s1 keeps the pin)
w3: orig with barrier[4] → do-while around the call arm
w4: orig with memory barrier → pointer store `s32 *gp = &D_801151D0; *gp = (s32)ot;`
w5: combos.

Let me do these quickly.
