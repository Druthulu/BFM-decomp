---
ts: 2026-11-06T08:38:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_29pRXykIPAuZHzU4Pkiu
---
Confirmed. Target: addiu a0,sp,24 at 2d4c in the beqz delay slot, and bnez delay slot = li v0,1.

Now, this is a scheduling birth-order difference (sched1-birth-order tag exists). Real C moves to change birth order: reorder statements so the address is born before the load of D_801270CC.

Key: sched1 schedules within a basic block. The block after `beqz` (D_801270C8 test) contains: addiu a0,sp,24 (in target) / not; lui v0; lw v0(D_801270CC); nop; bnez; then B2.

Wait, if the addiu is in B1, then the C source must produce it there. But sched1 doesn't move insns across basic blocks. So the structural difference is real: in target, the address computation is in B1; in mine, B2.

Hmm, but is it? In mine (c1), the addiu is at 2d60, after the bnez → B2. In target at 2d4c, B1. So yes, structurally different blocks. The asm forces expand to emit the address in B1.

So we need a real C use of the address in B1. Let me think about what "real C" construct gcc 2.7.2 would keep in B1 without generating extra instructions:

Possibility: `sp18` used as an lvalue in B1? E.g., an assignment `sp18[4] = 0` in B1 — but the target's stores are in B2.

Possibility: the source had the call argument as a *conditional expression*: `func_8012C51C(D_801270CC == 0 ? sp18 : sp18, param_1)`? Silly.

Possibility: the original code assigned `a0pin = sp18` in B1 (outside the inner if) and gcc's expand of a variable's initialization emits the addiu in B1; then in B2 the call uses a0pin. Does GCC emit the addiu in B1? An assignment `a0pin = sp18;` to a local pointer: gcc's expand will emit the address computation at the assignment point if the variable is "live" (used later). Then flow/sched may sink it... Actually GCC 2.7.2 emits RTL for the assignment immediately: `(set (reg a0pin) (plus sp 24))`. Then the optimizer (cse/flow/sched) may move/eliminate it. But sched1 only schedules within a block; the assignment RTL is in B1. cse might propagate the constant into B2 (if a0pin used once), eliminating the B1 set — that's the risk (cse-const-addr wall). But maybe with the branch in between, cse won't propagate a stack address across a block boundary? cse does global cse within extended basic blocks; it can. Hmm.

Test it! Candidate: declare a0pin in the outer if block before the inner if, with init:
```c
if (D_801270C8 != 0) {
    void *a0pin = sp18;
    if (D_801270CC == 0) { ... }
}
```
That's exactly the orig structure minus the asm! And c1 was produced by deleting the asm line from orig — which leaves exactly that. Right: c1 has `void *a0pin = sp18;` in B1 and it still got sunk to B2. So cse/flow sank it.

So we need something stronger. What about using a0pin in B1 in a way that produces no insn but prevents sinking: e.g. an `if` that tests it? `if (a0pin == 0)` folded away. `if (a0pin != sp18)`? also fold.

What about using it as the condition of the inner if:
```c
if (D_801270CC == 0) {
```
→
```c
if (a0pin[4] == 0 && D_801270CC == 0) 
```
No.

Alternatively: swap the nesting: compute the address in the *outer* if's condition through a real read:
```c
if (D_801270C8 != 0) {
    u16 *a0pin = sp18;
    if (D_801270CC == 0) {
```
sunk.

What about passing it to a function in B1 that the target also calls? In B1 the target has no call.

Hmm, what if the address is used to compute one of the *stores*' address in B2 but the store itself... no.

Different idea: maybe the CSE that sinks the addiu can be defeated by making the pointer not a constant expression but something cse can't fold: e.g., `u16 *a0pin = sp18 + 0;` same. `u16 *a0pin = &sp18[0];` same.

What about making a0pin a `u16 *` and the call takes `void *`; add a cast? Same.

What if we use the address in a *volatile-free* real operation that costs no instruction: e.g., `(void)a0pin;` — that's a no-op expression, gcc drops it. Not a use.

Use `a0pin = a0pin;`? dropped.

What about the "identity-statement launder" ban: `w = (w>>16<<16)|x` doesn't count. So no.

What about `a0pin[0] = a0pin[0];`? That's a real load+store (adds insns).

Hmm, think about the actual target semantics: the asm forces a0 to hold the address at the start of B1. Is there any real C statement that reads/writes through the pointer but compiles away? No.

Alternative: maybe restructure so the call is in B1 conditionally via a different control flow that yields the same code. E.g.:

```c
if (D_801270C8 != 0) {
    void *a0pin = sp18;
    if (D_801270CC != 0) goto done;
    ...stores...
    func_8012C51C(a0pin, param_1);
done:;
}
```
Same structure.

Or invert: 
```c
if (D_801270C8 != 0) {
    void *a0pin = sp18;
    if (D_801270CC == 0) { ... }
}
```
Same.

What if the stores are moved before the inner test? No, changes code.

What if we make the pointer's address computation part of the inner condition by using a real data dependency: e.g. `if (D_801270CC == 0 && a0pin != (void*)0xFFFFFFFF)`? gcc might not fold a comparison against 0xFFFFFFFF? It knows sp+24 can't be 0xFFFFFFFF? Probably folds.

What about `if (D_801270CC == 0 && (u32)a0pin >= 0x10000)`? Stack addresses are unknown at compile time → not folded! A comparison `(u32)a0pin >= 0x10000` would generate `sltu` instructions though. Extra insns. Not good.

Hmm. What about `if (D_801270CC == 0 && a0pin)`: `a0pin` truth test → folded to true.

OK, maybe a different lever-free route: change the *scheduling* of B2 so the addiu ends up in the beqz delay slot... impossible across the branch.

Wait wait. Let me re-examine. Is the target's addiu really in B1, or could reorg have moved an insn from before the branch into the delay slot? GCC reorg delay-slot filling: for a branch, it can fill the delay slot with an insn from *before* the branch (moving it after) if the insn is safe and not needed on the other path. If the addiu were the last insn of the *previous* block (the block ending at beqz), reorg could move it into the delay slot.

Previous block: {lui v0; lw v0; nop; beqz}. Hmm, the addiu would have to be immediately before beqz (the lw is at 2d40, then nop 2d44, then beqz). Could reorg move the addiu from before the nop? No, only the immediately preceding insn... Actually reorg's fill_simple_delay_slots examines insns before the jump in the same block, from the jump backwards, skipping nops; it can move the last non-nop insn if safe. So if the block were {addiu a0,sp,24; lui v0; lw v0; beqz}, the preceding insn is lw — moving the lw after the branch would be unsafe (branch may skip it? no, the branch target is after the block...). Hmm, actually the fill moves the insn after the jump into the delay slot, which is the *fallthrough* path only if the jump is not taken... For a conditional branch, the delay slot executes always, so the moved insn must be safe on both paths. `lw` of a global — safe (no fault). GCC often fills with the fallthrough insn.

Let me think about the target ordering differently. Target B1: {addiu; lui; lw; nop; bnez; li v0,1...}. The addiu is first, then the D_801270CC load. If the source order were `a0pin = sp18;` then `if (D_801270CC == 0)`, that's exactly the order! So in target, expand emitted the addiu at the assignment point (B1 start), and sched1 kept it first (or it was emitted first and stayed). In mine, cse/flow removed the B1 assignment and re-materialized the address at the call in B2 (addiu in the bnez delay slot).

So the fix: prevent cse from propagating/sinking the address from the B1 assignment into B2. What prevents cse? An intervening use that cse can't handle, or a call (calls block cse for memory but not for values... in GCC 2.7.2 cse, calls do clobber registers but a pseudo holding sp+24 would be fine).

What about making a0pin used twice — once in B1 (real, harmless) and once in B2? If a0pin has 2 uses, cse won't sink? cse can still propagate a constant into multiple uses, but GCC's cse does "constant propagation" only if the value is a constant expression and the reg is not used elsewhere... Actually cse replaces the reg with the constant at all uses and deletes the set. With 2 uses, it can still do that.

The keepalive asm is opaque: cse doesn't know the asm's semantics but it does know it uses the reg in an asm operand — cse can't delete the set because the asm needs the register. That's why it works.

Real C opaque use that costs nothing... Hmm.

What about a *function call* in B1? The target has none. But: the D_801270CC load... no.

What if we reorder so that the address computation is a *store address* in B1 for a store that also exists in B2? Not possible.

Alternative approach: accept that the addiu must be in B2 (mine) but change which branch's delay slot it fills. In mine it fills the bnez delay slot. Could a different sched1 order make it fill... no, it's in B2 which starts after the bnez. The target has it before the bnez.

Unless: make the inner if a *loop* so the address is computed before the branch? no.

Hmm, hold on. What if the CSE sink is defeated by *statement order*: put the `a0pin = sp18` assignment after a use in B1 that reads memory (like the D_801270CC load)? E.g.:

```c
if (D_801270C8 != 0) {
    void *a0pin;
    if (D_801270CC == 0) { ... }
}
```
No.

What if we read D_801270CC into a local in B1 explicitly:
```c
if (D_801270C8 != 0) {
    void *a0pin = sp18;
    s32 c = D_801270CC;
    if (c == 0) { ... }
}
```
Doesn't change the sink.

Let me test whether the problem is cse or sched1. I can compile candidates with -fno-... but we can't change flags; the TU build flags are fixed.

Let me try a few candidates quickly with sc.sh:
c2: a0pin = sp18; then use `a0pin[0] = ...` for all stores AND pass a0pin (real, multiple uses in B2). Still B2.
c3: hoist `sp18[4] = 0; sp18[5] = 0;`? changes order.

Different idea: what if the call's argument is not the array address directly but a pointer that is *computed from a value that's live*: e.g. use a pointer variable `p` (already in the function, s16 *p) — no.

Hmm, let me look at the broader context: maybe the function's original C is a known idiom in this repo. Let me grep the TU for similar patterns where a stack array is passed to a call with a keepalive, and see if other functions in the repo crack it differently. Also check the "moves.md" for sched1-birth-order entries: "sched1 orders two independent insn births opposite to source; reorder moves the other". Here the addiu is independent of the D_801270CC load, so sched1's order between them matters! In target, addiu first; in mine, addiu after the branch (B2). But if both were in the same block, reordering source could flip sched1's order.

Wait, could the addiu actually be in B1 in mine too, but scheduled after the bnez? No — sched1 doesn't move insns across basic blocks, and the bnez ends B1. Actually, is the bnez the end of B1? The block structure: B1 ends at the conditional branch (bnez). Insns after it in the emitted stream belong to B2 (fallthrough). Sched1 schedules each block separately and emits blocks in order. So an insn emitted after bnez is in B2. Therefore in mine the address is in B2. Confirmed by the fact that cse propagated it.

So the crux: prevent cse from propagating sp+24 into B2. Ways cse fails:
1. The reg is used in an asm (banned).
2. The reg is used in a way cse doesn't track: e.g., its address is taken (`&a0pin`)? That would need a stack slot (adds insns).
3. The set is not a simple constant/address? e.g. `a0pin = sp18 + (x*0)`? identity launder banned and cse folds.
4. Volatile.
5. The value is live across a call that could... no.
6. cse gives up when the value is used in a loop? no loop.
7. cse's `--` : GCC 2.7.2 cse has a limit on the number of sets; and cse doesn't propagate constants into insns whose... hmm.

Actually! In GCC 2.7.2, cse does NOT propagate a constant expression into an insn if the register is used in a *different basic block* and the value is not a "cheap constant"? No, it does global cse within extended blocks.

Alternatively, flow might delete the B1 set as dead if cse replaced the use. The order: cse runs before flow.

What if the use in B2 is a *memory address* operand? The addiu is computed as a call argument (a register use), cse propagates fine.

Hmm, let me test the "2 uses" idea quickly and a few others. Also test: `a0pin` used in B1 by an `if` on a *non-foldable* property... adds insns.

Another approach: change the type of the array so the address computation is not a simple constant: e.g. pass `&sp18[0]` vs `sp18` — same.

What about passing the address through a `u8*` cast: `func_8012C51C((void *)((u8 *)sp18), param_1)` — same.

Hmm, what if we make the call argument be `sp18 + 0`? Folded.

What about making `a0pin` point to the *middle*: `a0pin = &sp18[0]` same; `a0pin = (void *)((u16 *)sp18 + 0)` same.

Let me think about what real source code would look like. This is decompiled code from the original; the original programmer wrote something. The keepalive marks "NEEDED DIFFERS" — the decompiler's body differs. The target's a0 is sp+24 computed early. In the original source maybe the call was:

```c
func_8012C51C(sp18, param_1);
```
and gcc computed a0 early because of *argument evaluation order* combined with the second argument being `param_1` (in a0/s0). Hmm, in the target, `move a1,s0` happens at 2d7c inside B2. So no.

Maybe the original source had the call's first arg as a *different expression*, like `&sp18[0]` where sp18 is declared as `u16 sp18[10]` — no.

Alternatively maybe the original source used a pointer variable that was also used for the stores. Look at the target stores: all use `(sp)` with offsets, so no base pointer.

Let me look at what other functions in the same TU with a similar pattern look like. Perhaps this exact pattern (stack array passed to a call) appears elsewhere with a working body. Let me grep the TU for "func_8012C51C".
