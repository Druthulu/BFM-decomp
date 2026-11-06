---
ts: 2026-10-22T21:23:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QAQqZO9UusjhdmQYIBQB
---
b1 is only off by one instruction: `addiu a2,sp,32` at index 8 (mine) vs 14 (target). Mine schedules it early (right after `lhu v0,6(s0)`), target places it just before the jal (in the call group).

So mtx launder dropped is fine except the a2 addiu is hoisted by sched1. This is a sched1 birth-boost issue: the addiu a2,sp,32 birth is boosted so it's scheduled early. The m1 launder (hard-reg pseudo) changed its priority.

Now, how to make `addiu a2,sp,32` (the &mid arg for call 1) land late, and `addiu a0,sp,32` for call 2 — in b1 that's already right.

The problem: m1 = mid (a pointer to a local array) — sched1 hoists the address computation. In target, `addiu a2,sp,32` is right before jal (delay-1 position). Options:
- give m1 a 2nd use so it's not birth-boosted (a real second set) — but then cse... hmm.
- Order statements: currently m1 = mid is before mtx load. In target, a2 is computed at the call. The address is invariant; sched1 hoisted it because the pseudo is born early (statement m1 = mid at line 19 comes before the call). Actually sched1 schedules within a basic block; the addiu's birth is at its definition point. Since `m1 = mid` is a separate statement before the call, sched1 may move it later (it's a dependent of nothing) or earlier. It moved it EARLY (to index 8).

Wait, mine put `addiu a2,sp,32` at index 8, i.e. before the sh v0,18(sp). The birth boost for a set with a single use in the same block usually defers... Actually sched1's "birth boost" pushes an instruction up right after its dependencies are ready. Here `addiu a2,sp,32` depends on sp only → ready immediately → scheduled early.

In the target, a2 is set late because in the original C the address was materialized at the call site.

So: write the call with `mid` inline (no m1 temp) for the first call? Then `mid` decays to a2 at the call... The compiler would still emit addiu a2,sp,32 before the call, but as part of call arg setup (like `addiu a1,sp,16` and `addiu a2,sp,32` which appear at 11 and 14 in the target, i.e. the arg setup group). Note a1 = sp+16 appears at index 11, i.e. late-ish (before the lw a0 and the call). So arg-setup addius go in the call group. Good.

So try: drop both m1/m2 temps and pass `mid` directly — that was a2.c: score 22, 36 ins. Worse. Let me look at a2's full diff.

Actually a2.c had `s32 mid[2]` passed directly to both calls: `...(mtx + 0x34, pin, mid)` and `...(mid, &out)`. Score 22, 36 ins.

Hmm. Let me think about what makes the target special. The target: a2=sp+32 computed once for call 1, a0=sp+32 computed fresh for call 2 — the address is NOT held across the call (no s-reg). In b1 (with m1 launder kept), the launder makes m1 a hard-reg pseudo; reload assigns it... but we saw no s-reg in b1, good. So the m1 launder is what prevents the value from being kept across the call.

Why? The launder `__asm__("=r"(m1) : "0"(m1))` forces m1 into a hard register (a fixed register chosen at asm time? no — "=r" with "0" input is a matching constraint; it becomes a pseudo with a REG_ASM... effectively an opaque set). After reload, m1's value is a hard reg; the address &mid in a register, and reload rematerializes `addiu a2,sp,32` at each use? Hmm, but the second use is m2 = mid (a separate copy from the launder-free source), and cse gave m2 the same value as... 

Anyway, mechanism: the launder prevented the address from being held in a callee-saved register across the call, and also placed it in the call group.

Lever-free alternatives to get this:
1. Make m1 die before the call: m1 is used only as the call arg, so it's live only to the call. But the address value is shared with m2's use (cse). The issue is cse creates one pseudo live across the call. To break cse equivalence without a launder:
   - Use different pointer expressions for the two calls that cse can't equate: e.g. `m1 = mid;` and `m2 = &mid[1]; m2--;`? That's an identity launder (not allowed? "identity address spellings do NOT count as a crack").
   - Make the second call's pointer derived from a different object at the same address? No.
   
2. Prevent the cross-call live range by using the value in a way that requires rematerialization... 

3. Alternative: reorder so `mid`'s address is computed after the first call: e.g. declare `mid` as a local inside a block after call 1? But mid must be passed to call 1 too.

4. Use the array element type: the two calls take different types: call1 takes s32* (a2), call2 takes s32* too. Same.

5. Statement order: put `m1 = mid;` immediately before call 1 and `m2 = mid;` immediately before call 2 (already so).

Hmm, what if I split the pointer: give the first call `&mid[0]` and the second `mid`. Same.

6. Make the address computation non-invariant by using a variable index: `m2 = &mid[i]` with i = 0 stored in a variable? That would add insns.

Wait — maybe the real question is different: in b1 the only diff is a2's position (one insn out of place), score 2. That's very close. Maybe a small statement-order change fixes it: the `addiu a2,sp,32` is hoisted to right after `sh v0,18(sp)`. If the mtx load `lw a0,32(a0)` were scheduled earlier... Let me think about sched1: within the block, insns have priorities. `addiu a2,sp,32` (born early since m1 = mid statement is before the mtx load? no, mtx load is line 17, m1 = mid is line 19 → m1's birth is after the mtx load).

Hmm, in the generated RTL, the mtx load is `lw a0,32(a0)` (index 13) and the a2 addiu index 8. sched1 moved the a2 addiu BEFORE the mtx load's birth. That's the "birth boost" — an insn whose operands are ready is scheduled as early as possible after the previous insn that defines... 

Actually in sched1, an instruction with only ready deps gets scheduled at the earliest cycle; since there are no dependencies, it can go anywhere. The scheduler uses priority = length of longest path to the end of block (insn priority). `addiu a2,sp,32` feeds the jal → high priority → scheduled early. In the target, the arg-setup addiu is in the delay slot region... sched1 runs before the delay-slot pass; the target has a2 at 14 right before jal 15, i.e. scheduled last-ish.

So what made the target's a2 late? Perhaps in the target source, the address a2 was computed *after* the pin assignment (a1) and after the lw a0. All three arg setups are in sequence 11,13,14: a1 at 11, lw a0 at 13, a2 at 14. That's "argument setup in source order" (a1, a0, a2). In b1, a2 got hoisted above the sh v0,18.

Hmm, note the mtx launder's removal changed the schedule: with mtx launder (b2 or orig), the schedule matched exactly. The launder on mtx makes the mtx value opaque so it can't be rematerialized... In b1 (no mtx launder), mtx = *(s32*)(param_1+0x20) is a load into a0 (13), and `mtx+0x34` becomes the delay-slot addiu. Fine.

So with the mtx launder gone, sched1 places the a2 addiu at index 8. Why? Because the launder on mtx was an extra insn (a zero-width asm) between the mtx set and its use, which affected scheduling/priorities.

Idea: instead of removing the mtx launder, restructure so that mtx's value has a real second set or use that fixes the schedule. The brief wants NO launder. Alternatives to the mtx launder:
- `mtx = *(s32 *)(param_1 + 0x20);` then use `mtx + 0x34` — the launder is just forcing a hard reg. Lever-free might work if we reorder the statements so that the schedule comes out right.

Let me try variants of statement order in b1:
v1: move `pin = &in;` after the mtx load.
v2: move `m1 = mid;` right before the call (already).
v3: put the mtx load before `pin = &in;`.
v4: combine: `((void(*)...)(mtx + 0x34, &in, mid)` inline.

Let me first look at what's at index 8 vs target: target has `nop` at 8 (from the lhu delay) and mine has a2 addiu. The load lhu v0,6(s0) at 7 with its delay slot at 8 = nop in target. Mine fills index 8 with addiu a2 — actually that's sched1 putting the addiu in the load delay slot! Then index 9 sh v0,18(sp). So sched1 filled a load delay slot with the addiu. Target fills it with nop.

Hmm so it's a scheduling order difference: sched1 picked addiu a2,sp,32 to fill the gap after the lhu at index 7.

In target, the corresponding slot is a nop, and a2 comes at 14.

Options: change the birth position of the a2 addiu. If `m1 = mid;` is placed after the mtx load (it is: line 19 after line 17), hmm but the scheduler reordered.

Actually maybe simpler: make the a2 addiu depend on something that is defined later, e.g. use the pointer `mid` whose address computation... 

Alternatively, kill the a2 computation entirely by using an address that's already computed: `pin` is &in (sp+16), and mid is sp+32 = pin + 16. If I write `m1 = pin + 4;` (s32* arithmetic: +4 elements = +16 bytes)? That's an identity-ish spelling but it's a real arithmetic chain (addiu a2,a1,16) which would be a different insn (a2 = a1 + 16 rather than sp-based) — target wants addiu a2,sp,32. No.

Hmm. What about making the a2 value a 2nd use of something: e.g., `m1 = mid;` where mid is declared after out... The stack offsets are fixed by decl order: in(16), out(24), mid(32). If mid were declared first, offsets change. No.

Let me consider the alternative: use `do { } while (0)` around something? Not a lever per se — the catalog mentions `do{}while(0)` only with // !FAKE comment (that's for fake barriers). Using do-while for ref weight is a move (used in other shards). It's plain C. But is it a "lever of another kind"? do-while is a real C construct, used in prior MATCHes (e.g. func_80128ED8 used keepalive... ). The moves list shows do-while used to affect ref weights — that's allowed as real C.

Let's experiment systematically with the m1/m2/mtx structure. Since the m1 launder is essential (21), maybe replacing it with a real-C construct that keeps the value rematerialised. 

Idea: the launder forces m1 to be a *hard register* — meaning the value lives in a fixed register, and reload must materialize the address there. Without it, cse shares the pseudo.

Real C alternative to break cse sharing: make the two uses *different values* that are equal in address. E.g.:
```
m1 = mid;                    // s32*
...
m2 = mid + 0;                // identity — not allowed
```
What about `m2 = (s32 *)((u8 *)mid + 0);` identity, no.

What about giving mid a real second set after the first call? e.g.
```
mid[0] = mid[0];   // no-op store, would emit insns
```

Alternatively, make the first call's third arg a *different variable* that aliases the same memory: declare `union { s32 a[2]; s32 b[2]; } u;` then call1 gets u.a, call2 gets u.b — same address, but cse sees different decls with the same base... cse would still compute both as sp+32 and equate them (same address expression). Hmm, but they're different MEMs; the address pseudo is the same `&u` → cse equates.

Hmm. Actually wait. Let me reconsider the real mechanism: why is &mid live across the call at all in the lever-free version? Because cse equated m1 and m2, so one pseudo (call it P = &mid) is live from before call1 to call2. Since it's live across a call, it goes to a callee-saved reg (s1) → frame grows.

The target has NO s1: because the value is rematerialized (addiu sp+32 twice). Reload rematerializes a REG_EQUIV constant like (plus sp 32) when needed. But the allocator preferred to hold it in s1 (cheaper than recomputing? no—recomputing is cheaper). Actually if it's live across a call, global-alloc assigns a callee-saved reg; reload only rematerializes when it can't allocate. So to force rematerialization, the value must not be a single pseudo live across the call.

So I need cse NOT to merge the two address computations. Ways in real C:
(a) Make the first call's argument a different expression whose value is computed fresh: e.g. call1 arg = `&mid[0]`, call2 arg = `mid`. cse: &mid[0] == mid, equated.
(b) Insert a "2nd set" of mid between: e.g. after call1, do something that redefines mid — like `mid = (s32 *)...` no, it's an array.
(c) Change mid from an array to a pointer: `s32 *mid = ...`? It must be stack memory.
(d) Use `volatile`? That's a different lever (barrier-ish). Not allowed presumably (it's a barrier kind).
(e) Make the second call's arg come from a *load*: e.g. store &mid into a variable before call1, and after call1 read it back:
```
s32 *pm = mid;
call1(..., mid);
call2(pm, &out);
```
Hmm, pm = mid is still the same value; cse equates → same problem. But if pm is stored to memory and reloaded... 

(f) Real second set of the pointer:
```
s32 *m1 = mid;
call1(..., m1);
m1 = mid;      // real 2nd set (re-assignment)
call2(m1, &out);
```
That's a real 2nd set (m1 reassigned) — allowed per C0505 catalog ("init at decl", "statement order", temps). A 2nd set of m1 makes m1's live range shorter? Actually it splits the pseudo: after the 2nd set, the value is a new pseudo, so the first pseudo dies at the 2nd set (which is before call 2), so nothing is live across call1... no wait, the first pseudo is live from `m1 = mid` to `m1 = mid` (the second), which crosses call1 → still live across the call. Hmm, but its only use is the 2nd set, so it can be rematerialized? Actually a copy `m1 = mid` where the source is rematerializable: reload could remat. It may still hold in s1.

Hmm, but moves.md line 44/50 shows: "launder->real 2nd set pv = *p; pv &= 0xFF000000" — the pattern of replacing a launder with a real 2nd set. And line 190: "the launder -> do{}while(0) + v0 = (s16)v0 (a real 2nd set)".

So a real 2nd set is the sanctioned move. What real 2nd set can I give to the mid pointer? E.g.:
```
m1 = mid;
call1(..., m1);
m2 = mid;
m1 = m2;        // dead? 
```
Hmm.

Better: think about what the target needs: the address recomputed for call2 (addiu a0,sp,32) and computed once for call1 (addiu a2,sp,32). Since both are just sp+32, we need two separate computations, neither live across the call.

If I write the source with two distinct pointer variables initialized at their use points, and prevent cse from merging... In b1 (m1 launder kept), the schedule is exactly right except the a2 position. Wait, in b1 the m1 launder is KEPT — that's why it works. Without it, we get s1.

What if I declare mid as a *struct* and take member addresses? No.

What about making the second call's pointer an offset from `out`? out is at sp+24, mid at sp+32 → mid = out + 8 bytes = (s32*)((char*)&out + 8). But target's a0 = addiu a0,sp,32 exactly; if I write `(s32 *)((char *)&out + 8)`, gcc computes addiu a0,sp,32 (folding the +8 into the base) — that's an "identity address spelling"? It's not identity; it's a different base plus an offset that folds. It IS effectively the same address; the moves list says "identity address spellings do NOT count as a crack". This is a real different expression though the value is identical... risky, and it's a launder-like trick. Prefer real C.

Alternative real-C approach: make `mid` and `out` one array? e.g. `s32 buf[4]; Vec3 *out = (Vec3*)(buf+2);` Hmm.

Let me look at the other three items first? No — work item by item. But I have limited budget (20-30 min per item). Let me be efficient.

Practical approach: since b1 (mtx launder dropped, m1 launder kept) scores 2 with only an ordering difference, and nopin scores 22, the m1 launder is the real lever. To crack it I need a real 2nd set / pointer reuse that makes the mid address not live across the call.

Try: replace m1/m2 with a single variable that is reassigned:
```
m1 = mid;
call1(..., m1);
m1 = mid;      // 2nd set
call2(m1, &out);
```
Let me test that. Also try:
```
call1(..., mid);
call2(mid, &out);  -> a2.c = 22
```

And try `m2 = mid;` with mid as `s32 mid[2]` but declared *after* the calls? no.

Another idea: split the mid buffer into two uses: since call1 writes 2 words (s32* = 8 bytes) and call2 reads... Let me just try a batch of variants with sc.sh.

Variants (all with mtx launder dropped, since that one is nearly free):
c1: m1 = mid; call1(m1); m1 = mid; call2(m1).
c2: call1(..., mid); m2 = mid; call2(m2).
c3: m1 = mid; call1(m1); call2(mid).
c4: m1 = mid; call1(m1); m2 = mid + 0 ... no.
c5: reorder pin/mtx.
c6: two-element: `s32 *m1 = mid; ...; s32 *m2 = &mid[0];`? cse equates.

Also: maybe keep mtx launder-free but change the *decl* order or use s32 mid[2] → s32 mid[2] with initialization.

Let me also try the "do {} while(0)" trick? That doesn't affect values.

Let me write these variants quickly.

Actually first, let me reconsider: what does the launder `__asm__("=r"(m1):"0"(m1))` do exactly? It creates an asm insn whose output is a new pseudo with constraint "=r" and input the same value. At reload, the output pseudo gets a hard register; the input is a copy. The effect: m1's use in the call is the asm output pseudo, which is *not* cse-equal to mid (opaque). So call1's a2 = the asm result, and call2's a0 = mid's value (fresh). Since the asm output is only used once (in call1), reload must materialize it: addiu a2,sp,32 right before the call.

So the essence: call1's argument must be a value distinct from mid's cse class, materialized fresh at the call.

Real C way to get a distinct-but-equal pointer that the compiler must materialize at the call site: hmm, any expression that's not cse-equal. E.g. `m1 = (s32 *)((char *)mid + (mtx - mtx));` — that's identity arithmetic, hacky, and would emit extra insns.

What about using a *different array object* with the same stack slot? Two arrays can't share a slot.

What about making the first call's arg a pointer that comes from a function? no.

OK here's a cleaner idea: swap which call gets the temp. What if the second call's pointer is `m2` (fresh) and the first call's is `mid` directly, and we break the cse by *storing to mid between the calls*? Storing to mid between calls doesn't change the address.

Hmm, what about making the address non-constant: declare `s32 mid[2]` and pass `mid + k` where k is a variable known-zero... that adds insns.

Different tack: maybe cse isn't the culprit; maybe the allocator's preference is. Let me test whether a plain `m1 = mid; call1(m1); m2 = mid; call2(m2);` but with `m1`/`m2` declared as `s32 *` (as now) is the same as nopin (22). Yes, that's nopin.

What if the two calls use *different types* so the two address pseudos differ in mode? Both s32*. What if call1's arg is `(s32 *)&in`? No, wrong semantics (in is at 16).

Wait — actually, hmm. What does call1's third arg semantically need? `func_8012F14C(mtx+0x34, pin, m1)` — m1 = mid, an output buffer for a matrix (s32*). And call2 `func_8012EFB8(m2, &out)` — m2 = mid read as input. So the same buffer.

Idea: declare mid as a `Vec3`? No, s32[2] is 8 bytes; frame shows mid at sp+32 and out at sp+24 (Vec3 = 12 bytes: 24..35?). Hmm wait: out is Vec3 (12 bytes) at sp+24 → occupies 24..35, overlapping mid at 32? That can't be. Let me recompute: frame 48, sp+16 = in (12 bytes: 16..27), out at 24? That overlaps in. Hmm, maybe Vec3 is 8 bytes (f0,f2,f4 = 3 s16 = 6 bytes, padded to 8). in at 16..23, out at 24..31, mid at 32..39. Yes! Vec3 = 8 bytes (three s16 + 2 pad). Good.

So mid at 32, 8 bytes, frame 48. Fine.

Now: is there any real-C way to have the compiler emit the address twice? What if the second call's arg is `&mid[0]` and the first is `mid`? cse: (plus sp 32) both. Same.

What if I make mid a `s32 mid[2]` and pass `mid + 0`? Same.

What if I use a pointer variable that is stored to memory and reloaded between calls:
```
s32 *m1 = mid;
call1(..., m1);
m1 = mid;    // real 2nd set — the first value's only use is the 2nd set
call2(m1, &out);
```
Now the first pseudo (call it P0 = &mid at the decl) is live across call1, but its only use is the copy to m1 after the call. Reload can rematerialize P0 at that copy → no s-reg needed. And the second pseudo (P1) is used at call2, computed fresh. So both addresses materialize: addiu a2,sp,32 (for call1's arg via m1 first set) and addiu a0,sp,32. But m1's two sets share one register; the value must be in a register at call1 (a2) and recomputed after. This could work!

Actually careful: `s32 *m1 = mid;` then `m1 = mid;` — the second assignment is a real 2nd set of the variable m1. That's a legit C move ("init at decl" + reassignment). Not an identity launder on a *value* used for masking... it is reassigning a pointer to the same address. Hmm, is that an "identity-statement launder"? The prohibition: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". A 2nd set `m1 = mid;` is the sanctioned "real 2nd set" move in moves.md (e.g., "launder->real 2nd set pv = *p; pv &= 0xFF000000" — that one changes the value though). Hmm, "v0 = (s16)v0" (a real 2nd set) — value-preserving cast, accepted as a crack in G14 (line 191: "six v = (s16)v; real 2nd sets (v is a sign-extended s16, so the cast is a no-op)"). So a value-preserving 2nd set was accepted as a crack there. A dead copy `vol2 = vol` was also accepted (line 199: "dead copy vol2=vol + a 2nd def").

So `m1 = mid;` twice is in the same family: a real 2nd set that shortens a live range. It's a real C statement, not an asm/launder. I'll count it as a crack if it works — and it's not an identity *address spelling* like `(char*)p+0`.

Let me test a batch of variants.
