---
ts: 2026-11-06T12:32:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WvoHlPFfR6qno2pzOeSj
---
w1 and w2 both score 0!

w1: keepalive → `do { lim = cnt + zr; } while (0);` — keeps the pin (zr). Result: PARTIAL:pin (keepalive cracked, barriers still there).
w2: same but also drops zr (`do { lim = cnt; } while (0);`) — keeps NO pin? Let me check: w2 removed zr from the lim assignment but the decl `register s32 zr __asm__("$0")` remains and `cnt = n + zr` still uses it! Let me check w2's source: w2 = w1 with LIM replaced (absent) and the do-while replaced with `do { lim = cnt; }`. So `cnt = n + zr;` is still there → the pin is still used. So w2 keeps the pin too, but drops the `+ zr` on lim.

Wait, w1 replaced LIM (`lim = cnt + zr;`) with `do { lim = cnt + zr; } while (0);`. So w1 keeps zr in both places.
w2 = w1 with the do-while text replaced by `do { lim = cnt; }` → cnt = n + zr remains.

Both keep the pin. So both crack only the keepalive: PARTIAL:pin (barrier still present, pin still present).

Hmm, w2 is interesting: `lim = cnt;` inside a do-while(0) — a plain copy, but the do-while adds the loop ref weight. And it scores 0! So the keepalive is cracked.

Now, can we also crack the barriers? w5 (barriers replaced with do-while/pointer, pin kept, keepalive kept) = 8. w7 (both barriers + keepalive → do-while) = 8.

The barrier [4] (w3) = 4; memory barrier (w4) = 4. Neither cracked.

Let me try more ideas for the barriers:

For [4] (reorg delay slot): the target needs the fall-through head ineligible. The do-while around the call arm didn't change it (w3 = 4). What about wrapping the CONDITION in a do-while? Or restructuring the if:

```
if (*(s16 *)((u8 *)D_80115158 + ((s32)i << 1)) != 0) {
    ot = xf8017E1D4(ot, panel, (s32)i);
}
```
The fall-through head is `move a0,s0` (ot arg setup). To make reorg not use it, the body's first insn must not be eligible. Options: make the body start with a store (not eligible for delay slots?) or with a call.

What if we reorder the call's argument evaluation so the first instruction is not a move? E.g., `ot = xf8017E1D4((s32 *)ot, panel, (s32)i);` same.

What if the body computes `panel + 0x20` first? That's outside.

Hmm, the comment says the barrier is the fix; C can't express "don't fill the delay slot". But maybe a do-while(0) INSIDE the if before the call:

```
if (...) {
    do { ot = xf8017E1D4(ot, panel, (s32)i); } while (0);
}
```
That's what w3 did (4). What about:
```
if (...) {
    do { } while (0);  // !FAKE: do-while
    ot = xf8017E1D4(ot, panel, (s32)i);
}
```
An empty do-while — does it emit anything? It might create a block boundary. Let me try. But an empty loop might be optimized away.

Alternatively, wrap the whole `if` in a do-while:
```
do {
    if (...) { ot = ...; }
} while (0);
```
That splits the EBB before the if.

Let me also think about the memory barrier (w4=4 ORDER): the pointer-store trick didn't help. Let me look at the w4 diff to see.

Actually, maybe combine: if we can crack one more kind, we'd get PARTIAL:pin (keeping only the pin) — a much better result (2 of 3 cracked).

Wait, actually w1/w2 already give PARTIAL:pin (barrier+keepalive? no — w1 keeps the barriers AND the pin; it drops only the keepalive). Let me recompute: w1 = orig minus the keepalive asm, plus do-while around lim. The barriers [4] and memory are still in the body. So kinds kept = barrier,pin → result PARTIAL:barrier,pin.

w2 = same (barrier,pin).

Hmm, so PARTIAL:barrier,pin. Better than nothing.

Can we crack the barrier [4] too? Let me try more shapes. And the memory barrier.

Let me check the memory barrier issue: target keeps `sw s0,0(at)` (D_801151D0 store) AFTER the RMW. Without the barrier, sched2 hoists it. The pointer trick didn't work (still 4). Maybe because gcc folded gp back to &D_801151D0.

What if the pointer is a global or passed through something opaque? E.g., `*(s32 *)((u8 *)ot - (u32)ot + (u32)&D_801151D0)`? launder.

What if we make the store's address depend on ot: `D_801151D0 = (s32)(ot);` no.

What if we store through the OT pointer: `ot[-1] = ...`? changes memory.

Hmm. What about making the D_801151D0 store depend on the RMW value: 
```
u32 v = (D_800AE7B8[*pb].f4[2] & 0xFF000000) | (((u32)ot) & 0xFFFFFF);
D_800AE7B8[*pb].f4[2] = v;
ot += 10;
D_801151D0 = (s32)ot;
```
The store of v and the load of f4[2] alias; the D_801151D0 store still doesn't depend.

What if the stored value is derived from v: `D_801151D0 = (s32)((u32)ot & ~(v & 0));` identity launder.

What if we swap the order: `D_801151D0 = (s32)ot;` BEFORE the RMW? Then the target's order (after) differs.

Hmm, what if we make the RMW read the value the store writes? No.

OK, the memory barrier may be a WALL.

For barrier [4]: let me try a few more shapes quickly. Let me look at the w3 diff to see exactly what's wrong.

Actually w3's diff is the same as s2's (the barrier [4] removal): the delay slot at the beqz. The do-while around the call didn't change it.

Ideas:
- Put the call in a nested do-while with the condition inside.
- Restructure the if to use a temp: `s32 hit = *(s16 *)(...); if (hit != 0) { ... }` — changes code (adds a move?).
- Move `i = i + 1` before the if? No, changes semantics (i used in the call).

Hmm, the target's delay slot `addiu v0,s1,1` comes from the loop tail's `i = i + 1`. reorg fills the beqz delay slot from the TAKEN thread (the if body). The taken thread is: move a0,s0; jal; ... Actually reorg's fill_eager_delay_slots looks at the insn after the branch (fall-through) and the target of the branch. In the target, the delay slot holds `addiu v0,s1,1` — which is from the taken thread? The taken thread starts at the body. Hmm, `addiu v0,s1,1` appears at 2248 (delay slot) and again at 225c (in the body after the call). So it's copied from the taken thread's later insn (reorg can steal from the taken thread if the branch is taken... no, that's only for branches known taken).

Actually fill_simple_delay_slots can fill from the target if the branch is likely taken. Whatever.

The key: with the barrier, the fall-through head (`move a0,s0`) is ineligible, so reorg steals from the taken thread (the increment). Without, it uses the fall-through head.

To make the fall-through head ineligible in C: the head must not be a simple register copy. What if the call's first argument setup is a load or an add? E.g., if `ot` were computed: `xf8017E1D4(ot + 0, panel, i)` — folds. `xf8017E1D4((s32 *)ot, ...)` same.

What if the first argument is `(s32 *)ot` where ot is s32* — no change.

What if we swap the argument order in C? `xf8017E1D4(ot, panel, (s32)i)` → the arg regs are a0=ot, a1=panel, a2=i. Target: a0=s0 (ot), a1=s3 (panel), a2=i. If we reorder C args, the code changes.

Hmm, what if the call's first arg is the RESULT of an expression like `(s32 *)((u32)ot)`: folds.

What if we put a statement before the call in the body that isn't fillable: e.g., `panel = panel;`? identity → deleted.

What if the body's first statement is `ot = ot;`? deleted.

What about making the if body a compound statement with a declaration? `{ s32 t = (s32)i; ot = xf8017E1D4(ot, panel, t); }` — the temp t might add a move.

Hmm, what if the call is `ot = xf8017E1D4(ot, panel, (s32)(s16)i)`? The (s32)i is already a sign-extended value; target uses a2 from the loop. Adding (s16) might change.

Let me look at the target around 2244:
```
223c: lh v0,0(at)
2240: nop
2244: beqz v0,2260
2248: addiu v0,s1,1     <- delay slot
224c: move a0,s0
2250: jal func_8017E1D4
2254: move a1,s3         <- call delay slot
2258: move s0,v0
225c: addiu v0,s1,1
2260: move s1,v0
```
So the beqz's delay slot is the increment (from the taken path's tail), and the call's delay slot is move a1,s3 (panel). Note a2 must be set before: at 222c-2230, `sra a2,v0,0x10` and `sll v0,a2,1` — a2 = (s32)i is already set earlier in the loop! So the call's args: a0 (move), a1 (move in delay), a2 (already from the loop head).

Without the barrier, mine:
```
beqz v0, ...
move a0,s0      <- delay slot (fall-through head)
```
Then the taken path would have jal and the rest shifted.

To prevent the fall-through head from being eligible, we could make the body's first insn something reorg can't move, like a `jal`... 

What if we reorder the body statements: put `panel = panel + 0x20;` INSIDE the if before the call? No, changes semantics/order (target has panel += 0x20 in the loop tail).

What if the body calls a helper with a different argument order that puts a1 first? No.

Honestly, the [4] barrier looks like a genuine reorg wall (`dbr-delay-fill` or `sched1-load-delay-fill`). There's a tag `dbr-delay-fill` (delayed-branch fill takes a fall-through insn the target leaves out). Yes! That's exactly it.

So: barrier [4] = WALL dbr-delay-fill; memory barrier = WALL sched-store-sink (scheduler sinks/hoists a store past the target slot)? Actually sched2 hoists the store above the RMW. The tag `sched-store-sink` exists: "scheduler sinks a store past the target slot (G28)". Here it's hoisting (sinking = moving later). Hmm, "sched-store-sink" is about sinking; ours hoists. There's also `cse-store-forward` (cse1/combine). Our diff is ORDER (sched2). Let me use `sched2-store-hoist`? The walls.txt has `sched-store-sink`. I could define a new tag `sched2-store-hoist` (pass-what). Hmm, the tag should be `<pass>-<what>`: `sched2-store-hoist`.

And the pin: WALL (the +zr opaque copy has no C spelling: `no-c-spelling` or `lreg-copy-merge`). The moves line 25 has `combine-copy-merge` ("combine merges a reg copy the target keeps, so the pin stays"). That's a good tag for the pin: the copy `cnt = n` is merged away. Use `combine-copy-merge`? Actually it's local-alloc/cse merging the copy. The tag `cse-copy-merge` exists: "cse merges a copy the target keeps in its own reg". That fits: `cnt = n` merged by cse. Use `cse-copy-merge`.

So the best result: crack the keepalive only → PARTIAL:barrier,pin, with walls dbr-delay-fill (barrier[4]), sched2-store-hoist (memory barrier), cse-copy-merge (pin).

Wait, but w1/w2 still keep the barriers; if we can't crack them, the result is PARTIAL:barrier,pin. That's a valid PARTIAL (win.c scores 0).

But hold on: can we combine the keepalive crack with dropping ONE of the barriers? w5/w7 = 8 (not 0). So no.

Let me try a couple more ideas for barrier [4] and the memory barrier before settling. Time: ~05:35. Item 2 started 05:28. Budget 20-30 min → until ~05:55. Let me spend ~10 more minutes.

For barrier [4]:
Idea: `if (*(s16 *)(...) != 0) { ... }` — what if we make the condition's branch a different structure, e.g., `if (*(s16 *)(...) == 0) { } else { ot = ...; }`? That swaps the branches: beqz → the else. Target has beqz to the skip. With if/else, the code would be beqz to the call... Let me try:

```
if (*(s16 *)((u8 *)D_80115158 + ((s32)i << 1)) == 0) {
} else {
    ot = xf8017E1D4(ot, panel, (s32)i);
}
```
The empty then-branch might be removed. Hmm.

Idea: use a temp for the condition: `s32 t = *(s16 *)(...); if (t != 0)`. The load into a temp then beqz t. Target: `lh v0,0(at); nop; beqz v0`. Same.

Idea: make the body start with a store: what if we compute the call args in a different order by using a helper expression... 

Actually, maybe try: `ot = xf8017E1D4((s32 *)ot, panel, i);` where i is s16 → the call's third arg is (s32)i; gcc would emit the sign-extend maybe. Already there.

What about making the call's FIRST argument not a copy: e.g., pass `ot` but with ot being a variable that's already in a0? No.

Hmm, what about reordering the loop body statements: 
```
i = i + 1;   // no
```

What about wrapping the loop body in do-while(0) — w6 = 31, bad.

What about a do-while(0) around the condition only? Not possible.

Let me try the `if/else` swap and a `do { } while(0)` empty block before the call.

For the memory barrier: 
Idea: make the store depend on the RMW by reusing the computed value: 
```
u32 v = (D_800AE7B8[*pb].f4[2] & 0xFF000000) | (((u32)ot) & 0xFFFFFF);
D_800AE7B8[*pb].f4[2] = v;
ot += 10;
D_801151D0 = (s32)ot;
```
Still no dependency. But if the store value were `(s32)(ot) + (v & 0)`? launder.

What if the D_801151D0 store is placed inside the same statement as the RMW via a comma? `D_800AE7B8[*pb].f4[2] = v, D_801151D0 = (s32)ot;` — same.

Idea: make D_801151D0's address computation use `pb`: no.

Idea: `*(s32 *)((u8 *)&D_801151D0) = (s32)ot;` — same address, no.

Idea: use a volatile pointer? `*(volatile s32 *)&D_801151D0 = (s32)ot;` — a volatile store can't be moved across other memory ops? Actually sched2 treats volatile as a barrier! That's a real-C construct (volatile), but is it a "lever"? It's not an asm; it's a real C qualifier. The target's original had a memory clobber. Using volatile might be considered a new lever of a different kind... The brief says no new lever of any kind; volatile is arguably a C-level trick, but it IS semantically meaningful (it's a global that's externally visible). Hmm, risky. But let me test the score; if it gives 0, I'd need to judge whether it counts. The kinds list for this item doesn't include "volatile". The constraint "no new lever of any kind" is strict. I'd rather not.

Let me test the ideas and see.

Actually, wait. Let me reconsider the pin. w2 cracked the keepalive with a plain `do { lim = cnt; } while (0);`. Interesting — the do-while also removed the need for `+ zr` on lim, but `cnt = n + zr` remains. Can we do the same for cnt? `do { cnt = n; } while (0);`? The keepalive-like effect: a do-while adds ref weight. Let me try replacing `cnt = n + zr;` with `do { cnt = n; } while (0);` and dropping zr entirely. Maybe the do-while prevents the coalescing? Actually the do-while creates a loop; the assignment inside gets loop_depth refs. But coalescing is a value thing, not refs. Hmm, but let me test.

Also: maybe with the keepalive cracked via do-while, the pin becomes removable. Let me test u-variants:
- x1: w2 with `cnt = n + zr` → `do { cnt = n; } while (0);` and zr decl removed.
- x2: w1 (keepalive→do-while) with `cnt = n + zr` → `cnt = n;` (zr removed).
- x3: full: both do-whiles, zr removed, barriers kept.

Let me test.
