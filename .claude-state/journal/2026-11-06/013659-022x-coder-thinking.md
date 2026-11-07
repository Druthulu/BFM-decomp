---
ts: 2026-11-06T08:36:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oUWh7okGBQOBnbkIWj3w
---
This is cand.o = my c1 candidate (58 insns, with addiu at 2d60 in bnez delay slot). The target (from the diff) has at the corresponding spot:

target:
```
beqz v0, ...     (at 0x2da8 target address)
addiu a0,sp,24   (delay slot)
...
bnez v0, ...
(no addiu)
```
So target's addiu sits in the beqz delay slot of the *second* branch (the D_801270CC test at 2d5c region). In mine: 2d48 beqz (D_801270C8) with nop; then 2d50/2d54 load D_801270CC; 2d5c bnez with addiu in delay slot. Target: 2d48 beqz with addiu in delay; then bnez with no addiu (its delay slot would be filled with something else or nop).

Wait the diff indices: mine[28] = beqz, mine[29] = nop; target[28] = beqz, target[29] = addiu. Mine[33] = bnez, mine[34] = addiu; target[33] = bnez, target[34] = -- (target only has 57 insns, so target[34] is the following insn from mine[35]). So in the target, the addiu is in the *first* branch's delay slot (the D_801270C8 beqz), executed unconditionally after the test. And the bnez's delay slot is filled with mine[35] (which is `li v0,1`? in mine 2d64 is li v0,1 after addiu).

Hmm wait, in mine the order is: beqz at 28 (nop delay), lw D_801270CC at 31? Let me index mine's insns 28-40: 
- 28 beqz (2d48)
- 29 nop (2d4c)
- 30 lui v0 (2d50)
- 31 lw v0 (2d54)
- 32 nop (2d58)
- 33 bnez (2d5c)
- 34 addiu a0,sp,24 (2d60)
- 35 li v0,1 (2d64)
...
Target: 28 beqz, 29 addiu a0,sp,24, 30 lui, 31 lw, 32 nop, 33 bnez, 34 li v0,1 ...

So in the target, the addiu is hoisted into the delay slot of the *first* beqz, i.e., it's executed before the second test. That means the addiu's birth is before the second branch. In GCC, reorg's delay-slot filling put it there: reorg fills a delay slot with the *previous* insn if it can't fill with next? No: reorg fills with the next insn (if it's not a jump target) otherwise previous. Here the addiu is placed after beqz, meaning it's the "next" insn after the beqz in the schedule. So in the target schedule, the addiu is immediately after the first beqz, before the lui/lw of D_801270CC. In mine, it's after the bnez.

This is a scheduling difference: sched1 ordered the addiu later. Actually the sequence after the branch: in mine the addiu is right after bnez; in target right after beqz. So the address computation is scheduled before the D_801270CC load in the target.

What real-C change would birth the address earlier? If the address were computed as part of the *outer* if body start, e.g.:

```c
if (D_801270C8 != 0) {
    void *a0pin = sp18;
    ...
```
That's what we have and it gets scheduled after bnez. Hmm, because sched1 within a basic block orders by dependencies; the addiu is independent of the loads, so it could be anywhere. sched1 picks order by priority (insn priority based on critical path). The addiu feeds the call (far away), low priority. The loads feed the bnez (near), high priority. So sched1 puts loads first. In target, addiu is first — meaning its priority was higher, or it was *before the basic block*, i.e., emitted in a previous block.

Key insight: in target, the addiu is in the delay slot of beqz — reorg moved an insn from *before* the branch? reorg fills delay slots: for a branch, it looks at the insn *after* it (fallthrough) first? In GCC 2.7.2 reorg, delay slot filling: if the insn after the jump can be moved into the delay slot, do it; else look at the insn before the jump (from the same block). Here, "insn after" in the target schedule would be the lui. It could have been filled with something else. Hmm.

Actually, maybe simpler: the target has the addiu *before* the beqz in its schedule (i.e., at the end of the previous block), and reorg moved it after the branch into the delay slot. Wait no: if it were before the beqz, reorg can move it into the delay slot (the "previous insn" fill). That's plausible! In target source order: compute a0pin (addiu a0,sp,24) at the end of the outer block, then beqz. reorg moves the addiu into the delay slot → after beqz. That fits.

So the real C computes the address *before* the D_801270C8 test! I.e., `void *a0pin = sp18;` is materialized before the `if (D_801270C8 != 0)` test — like the keepalive does (the asm is before the if... wait, no: the asm is inside the if).

Look at orig: 
```c
if (D_801270C8 != 0) {
    void *a0pin = sp18;
    __asm__(...);
```
The asm is inside. But GCC's expand hoists the address computation out? With the asm, the addiu is emitted before the beqz. Because the asm creates a use right at the start of the block, and gcc's expand emits the address at the point of first use, which is the asm inside the if — but the branch is `beqz` for `D_801270C8 != 0` and the asm's code is in the fallthrough. Hmm, then how is the addiu before the beqz?

Because in the target, the beqz is at 28 and the addiu is at 29 (delay slot). Before the beqz there's the D_801270C8 load at 2d3c-2d44. So the addiu is NOT before the beqz in program order; it's in the delay slot. reorg moved it from after the branch (fallthrough start) into the delay slot? No — the fallthrough insn is the addiu itself in mine too (mine has addiu after bnez, not after beqz).

OK here's the thing: with the asm (score 0, orig), the schedule must be: beqz at 28, addiu in delay (29). The asm forces a0 to hold sp18 at the start of the if-body; the if-body begins right after the beqz. So the addiu is the first insn of the body, and reorg put it in the beqz delay slot. Without the asm, sched1 within the block scheduled the addiu after the bnez (because the bnez is a separate block boundary? no...).

Wait — actually the structure is two nested ifs: `if (D_801270C8 != 0) { if (D_801270CC == 0) { ... } }`. Two basic blocks. In the target, the addiu is at the start of the outer-if body, *before* the inner if test → it's in block B1 (outer body), and reorg fills the beqz delay with it. In mine, the addiu is in block B2 (inner body), after the bnez.

So with the asm, expand emits the address computation in block B1 (because the asm use is in B1). Without, the only use is in B2, so it's emitted in B2.

To fix lever-free, we need a real use of the address in block B1 (before the inner if). What real use? Options:
- Store through it in B1? The target has no such store.
- Call something with it? No.
- Use it in the inner condition: `if (*(void **)&D_801270CC == ...)` no.

Hmm. But wait: the target has NO other use. So the original C must have had something in B1 that the compiler optimized into this. Or the original binary's code just came from a source where the address was computed in B1 for the call in B2 — which is what the asm emulates.

Real C construct that computes an address in an outer block for later use: taking the address in a declaration initialized in B1 and used in B2. gcc sinks it. Unless the address is passed to something in B1.

Alternative: restructure the ifs so that the address is used in B1's condition:
```c
if (D_801270C8 != 0) {
    u16 *a0pin = sp18;
    if (D_801270CC == 0 && a0pin != 0) { ... }
```
gcc knows a0pin != 0 (address of local) → folds, and then the use disappears (flow-known-value). Also that's a launder-ish identity.

What about `if (D_801270CC == 0 && (s32)a0pin > 0)`? Also known.

Hmm what about passing the address to a function in B1 that the target doesn't have? No, target has only the one call.

Wait — maybe the target's block structure is different: maybe the source was a single condition `if (D_801270C8 != 0 && D_801270CC == 0)`? Then the two tests would be in one block and the addiu could be scheduled... no, the target has the addiu between the two tests, which suggests the address is computed in B1.

Alternatively: maybe the original code had the address computed *unconditionally* before the `if (D_801270C8 != 0)` test:
```c
void *a0pin = sp18;
if (D_801270C8 != 0) { if (D_801270CC == 0) { ... call(a0pin,...) } }
```
Then the addiu would be at the top, before the D_801270C8 load, not in the delay slot. Unless reorg moved it later... reorg only moves within a block. The addiu before the beqz could be moved into the delay slot by reorg? reorg delay-slot filling considers the insn before the jump if it's safe to move down. Yes! GCC's reorg can fill a delay slot with the instruction *preceding* the jump (moving it after). So the original schedule: `addiu a0,sp,24; lui v0; lw v0; beqz v0` — wait but then the addiu is before the lui/lw in the schedule; reorg would move it into the delay slot only if it's the immediately preceding insn (adjacent). The immediately preceding insn is the lw at 2d44? Actually the branch's delay fill looks at the insn before the branch: `lw v0, 0(v0)` — can't move a load after the branch (it's fine actually? load is safe). Hmm, but the target shows `lw` at 2d44 then `nop` at 2d4c? Wait target: 2d44 lw, then 2d48 beqz, then addiu. Let me reconstruct target from mine: target[28]=beqz means target insns 0..27 are same as mine's 0..27. Mine 0..27 includes ... let me map: mine at 2d3c lui v0; 2d40 lw v0; 2d44 nop; 2d48 beqz. Mine's index 28 is 2d48. So target = mine with addiu moved from 34 to 29. Target: 2d3c lui, 2d40 lw, 2d44 nop, 2d48 beqz, 2d4c addiu, 2d50 lui, 2d54 lw, 2d58 nop, 2d5c bnez, 2d60 li v0,1...

So in the target, the addiu is after the beqz (delay slot), and the fallthrough of the beqz starts with the addiu. Then the D_801270CC load. So block B1 = {addiu a0,sp,24; lui; lw; nop; bnez}. The addiu is the first insn of B1 and reorg put it into the beqz delay slot (moving the first fallthrough insn up into the slot). That's standard.

In mine, B1 = {lui; lw; nop; bnez; addiu...}? No — mine's addiu is after bnez, i.e., in B2's start, and reorg put it in bnez's delay slot. So sched1 scheduled the addiu after the branch (into B2).

So the difference is purely scheduling: in target, the addiu is scheduled before the D_801270CC load; in mine, after the bnez. Both are within B1's instruction stream pre-scheduling (the addiu belongs to B1 in target because its use... hmm, if the addiu were in B2 pre-scheduling, sched1 would never move it into B1 across a branch). So structurally, the target's addiu is in B1. So the original source DID have a use in B1.

What could it be? Let's think about the keepalive semantics: `__asm__ ("" :: "r"(a0pin))` forces a0pin into a register at that point, in B1. The asm has no other effect. So the "real C" that would do the same: a use of the address in B1 that doesn't add instructions.

Idea: make the inner if's *condition* depend on the pointer in a way that survives optimization: e.g. `if (D_801270CC == 0)` → `if (a0pin[0] == a0pin[0])`? No, fold.

Real C use with no instruction: pass the address as an argument to a call... no call in B1.

Alternative: restructure so the call is in B1 with a conditional around the *stores*? The target's structure: B1 tests D_801270CC, and only if 0 does the body (stores + call). The call is in B2.

Hmm, what if the source had `func_8012C51C(sp18, param_1)` and the address was computed early because the call's argument is a *stack array address* and gcc's expand of the call argument happens before the branch? No.

What about `sp18[0] = ...` stores: in the target, the stores in B2 use 24(sp). The address a0=sp+24 is computed in B1. Why would GCC compute sp+24 in B1? Only if a pseudo for it is live into B2. 

New idea: what if the C had the array passed to the call, and the address computation is CSE'd with something in B1? E.g., if B1 also computed sp+24 for a store that was later... no.

Maybe the real crack is different: use a *different* argument expression that gcc must materialize earlier due to argument evaluation order with the second arg. `func_8012C51C(a0pin, (s32)param_1)`: param_1 is in a0 (incoming). For the call, a0 must become &sp18 and a1 = param_1. gcc must copy param_1 (s0?) Actually param_1 was moved to s0 in the prologue (`move s0,a0`). At the call: `move a1,s0` (2d80) and `addiu a0,sp,24` (2d60 in mine, in the bnez delay). Fine.

Hmm. Let me look at other examples in moves.md with similar "keepalive" cracks: W04 "keepalive replaced by return v0", W06 "obase set right after pbase and used for the first load too", G24 func_800CB458 "pass arg0 to func_800CAF84 (cast call) — keeps $4 live across the Struct16 copies". These are real uses.

For this item, maybe the answer: the call `func_8012C51C(a0pin, (s32)param_1)` — maybe the original passes `sp18` as the first arg but the address is also used by a store... 

Let me try a completely different tactic: brute-force with the move catalog. The brief says "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)". 

Try: move the `a0pin` declaration+init to *before* the outer if? Then a0 is computed at function start — too early (before the first if). Score would differ more.

Try: `if (D_801270C8 != 0 && D_801270CC == 0)` combined, with `a0pin` declared and initialized... then a0 materializes in the combined block, after both tests. Worse.

Try: compute the pointer inside the *outer* condition: `if (D_801270C8 != 0)` → no.

What about making the call argument be `&sp18[0]` where sp18 is a struct? No.

Let me reconsider: maybe the target's `addiu a0,sp,24` in B1 is because the *first* store `sp18[0] = CAST_ALIAS(u16, param_1, 6)` uses a base register. In the target, stores are `sh v0,24(sp)` — base sp. So no.

Alternatively, maybe the original C had `func_8012C51C(sp18, param_1)` *hoisted above* the `if (D_801270CC == 0)`? No, the call is inside.

Let me look at the score-0 orig disassembly (with the asm) to see exactly what the asm yields, and then think about which C construct produces the same. Actually the orig scores 0, so it's identical to target. The asm is a lever that we must replace.

Given the difficulty, maybe there's a simpler real-C trick: use the array's address in the inner `if` condition as a genuine data access that the target also has? No.

Hmm, what about declaring `u16 *a0pin = sp18;` and then *assigning one of the stores through a0pin before the branch*? Not in target.

Another angle: the constraint says MATCH requires kinds gone. If we can't crack it lever-free, it's a WALL with best score 4 — but the item would still need a win.c? No: WALL just records best. DONE WHEN: "each MATCH/PARTIAL has its win.c scoring 0" — WALL doesn't need win.c.

But we should try hard. 20-30 min per item.

Let me check if a `sched1` ordering move helps: the difference is one addiu's position. A real C change that changes the birth order: e.g., reorder statements, use the pointer for something. What about making the pointer a `u16 *a0pin = &sp18[0];` and using `a0pin[0] = ...` for the stores? Then a0pin is used in B2 for stores — still B2.

What if we pass `a0pin` to the call as before but ALSO make the stores go through it? Same block.

Hmm, actually maybe the key is the *scope* of a0pin: currently declared inside the if-block. What if declared at function scope with init at decl? Then the addiu would be at the top (frame setup), too early.

Wait, what about the declaration placement between the two ifs:
```c
if (D_801270C8 != 0) {
    void *a0pin;
    if (D_801270CC == 0) {
        a0pin = sp18;
        ...
```
gcc puts the assignment where used → B2.

What if the address computation is used in the condition of the inner if in a real way:
```c
if (D_801270CC == 0 && *(s32 *)a0pin == 0)
```
No.

Let me try a different real-C construct: a *conditional expression* that makes the pointer live across the branch:
```c
void *a0pin = sp18;
if (D_801270CC == 0 ? (sp18[4] = 0, 1) : 0) ...
```
adds instructions.

OK, maybe the real trick here: use the address as the destination of a store that the target has in B1? There is none.

Alternatively — maybe target's addiu is actually a *CSE'd* value from the earlier block: notice at 2d10 there is `addiu a0,sp,16` (for the func_80184138 call in the first if). Could the compiler have computed sp+24... no, different.

Let me look at the original binary disassembly to be sure (target). Where is the target .s? Perhaps tools/asm-differ or build/asm has per-bank .s of the original. Let me find the target source: maybe `build/asm/ov_SC01_084.s` or the reference disassembly. Let me check `build/asm`.
