---
ts: 2026-11-06T08:39:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_a2wLpy7kgOTjxqfh1AxZ
---
Interesting: `func_801846B4` at 1587 uses a struct `tmp` and passes `&tmp`. Note line 1587 declares the struct inside the else-if block. In our function the analogous idiom is a struct/array. The original source probably used a struct `tmp` and passed `&tmp`.

But that doesn't fix the sinking.

Hmm, maybe the key: in the target, a0=sp+24 is computed *before* the D_801270CC load because of the **stores to sp18 earlier**? No.

Let me look at how func_801846B4's call arg is scheduled: it passes &tmp; the address is computed right before the call probably.

Let me step back and consider the possibility that the real C difference is the *structure* of the if: maybe the original source was:

```c
if (D_801270C8 != 0) {
    void *a0pin = sp18;
    if (D_801270CC == 0) {
        ...
```
which is c1 → sunk.

OR the original source computed the address before the outer if but the outer if's test itself was a call... no.

Alternatively, maybe the original used `u16 sp18[10];` but passed `sp18` in the call and the *compiler's target* (built from the current src with asm) is what we must match — so we need to match the asm's effect. The asm makes a0 live in B1. What real C keeps a value live in B1? A use that the compiler can't remove. What about using the pointer as the *destination of a store in B1 that's dead but not deletable*? A dead store would be deleted by flow. A store to a global? Not in target.

What about a use in the inner if's condition that costs zero instructions because it's a comparison of the pointer against a *register* value? E.g.:

```c
if (D_801270CC == 0 && a0pin != (void *)D_801270C8)
```
adds a compare.

Hmm, what about making the inner if condition involve a *load through the pointer* that is already loaded? No.

New idea: make the array a *pointer to a stack slot passed through a function that returns it*? no.

Let me look at the problem from the scheduling angle instead. Perhaps we can leave the address in B2 but make sched1 place it *before* the bnez? Impossible (block boundary).

Unless we eliminate the inner branch as a branch: e.g., write it as a loop `do { ... } while (0)`? C0535 says do-while splits cse1 EBB and cracked a sched1-birth-order item! The moves file says C0535 (do{}while(0) splits cse1 EBB). Interesting: maybe wrapping the inner body in do-while changes things. But the branch structure must stay (bnez exists in target).

Hmm, what if we invert the nesting: 
```c
if (D_801270C8 != 0 && D_801270CC == 0) { ... }
```
Then the addiu would be in the same block after both tests → no.

What if:
```c
if (D_801270C8 != 0) {
    if (D_801270CC == 0) {
        void *a0pin = sp18;
        ...
```
addiu in B2 after bnez → mine.

So to get addiu before the bnez, the assignment must be in B1 and not sunk. Let me actually test whether a 2-use variant prevents sinking: 

```c
void *a0pin = sp18;
if (D_801270CC == 0) {
    ...
    func_8012C51C(a0pin, ...);
} 
```
with an additional *real* use in B1, e.g. `sp18[4] = 0;` moved? No.

What about the use `a0pin = a0pin;`? dropped.

What about the use in B1 being `func_8012C51C`'s address? no.

Hmm, what about **initializing sp18 partially in B1**? The target has no stores in B1.

Let me look at GCC 2.7.2's cse: does it propagate a constant into a use in a different basic block when the set is in a block with a conditional branch? cse processes the extended basic block; the branch splits blocks but cse handles each block with the table carried over (it invalidates on labels). So yes.

What makes cse NOT record the set? If the destination is used in a way cse doesn't track... e.g. if `a0pin` is a *volatile* variable (would add memory traffic).

OK here's another thought: what if we don't use a pointer variable at all but pass an expression that forces the address computation earlier due to **argument evaluation order**: `func_8012C51C(a0pin, (s32)param_1)`. What if we swap the argument order in the source? Can't change the call signature/args.

What about passing `(void *)(sp18)` where sp18 is an array — gcc computes it at the call.

Hmm, what if the address is used as a *store base* in the same block B1 for one of the stores that the target puts in B2 — no.

Let me look at the target instruction at 2d4c again: `addiu a0,sp,24`. And note the delay slot of the *first* beqz at 2cec is a nop, not filled. Interesting: at 2cec (beqz after func_8012BEE8) the delay is nop, and at 2d48 (beqz D_801270C8) the delay is the addiu.

GCC reorg fills delay slots from the fallthrough insn. At 2d48, the fallthrough (B1 start) is the addiu → filled. In mine, B1 starts with lui (the load of D_801270CC) → why wasn't that filled into the delay slot? It is a load of a global — safe, but reorg may not move loads into delay slots because of... it does sometimes. In mine at 2d48 the delay is nop, and the lui at 2d50. Hmm, reorg didn't fill it. Why? Because the lui/lw pair loads D_801270CC and the branch's target 2dac... the delay slot executes even when the branch is taken, so the load must be safe and its result unused on the taken path — it is unused (v0 dead at 2dac). Should be safe. Maybe reorg only fills with insns it knows are safe and the lw might fault? GCC 2.7.2 is conservative about loads in delay slots? It filled the addiu (arithmetic) but not a load. So it prefers arithmetic.

OK so in mine B1 = {lui, lw, nop, bnez} — hmm why is there a nop at 2d58 before bnez? That's the load delay slot. Then bnez's delay = addiu (from B2, moved up by reorg? no, reorg can move the fallthrough insn into the bnez delay slot: the addiu is the first insn of B2/fallthrough, so reorg moved it into the bnez delay slot). Yes! So in mine, the addiu is the first insn of B2 and reorg moved it into the bnez delay slot. In target, the addiu is the first insn of B1 and reorg moved it into the beqz delay slot.

So: the addiu needs to be in B1. The asm put it there. Real C must put a use in B1.

What if we move one of the *stores* to B1? Changes bytes.

What if we add a *real* use in B1 that the target also effectively has: the call! What if we move the call... no.

OK, radical: maybe use `goto` to make B1 contain the address computation via a computed... no.

Alternative: maybe use a **pointer to the array declared at function scope and used in both branches** so its live range spans B1, forcing the computation in B1? E.g.:

```c
void *a0pin = sp18;
if (D_801270C8 != 0) {
    if (D_801270CC == 0) { ... call(a0pin) }
}
```
The assignment is before the outer if → addiu at the top (before the D_801270C8 load), which would change more (but maybe reorg moves it? The block before the beqz at 2d48 contains the lui/lw/nop; an addiu at the top of that block... Actually the assignment would be emitted right after the prologue, before `jal func_8012BEE8`. That changes insns 0..5 region. Unless sched1 moves it down within the same block to right before the beqz, and reorg fills the slot! That could work! The whole function body up to the first branch is one block (after the call, a new block starts). The assignment would be after the call `func_8012BEE8` (since it's after that call in source) — so in the block that starts after the jal (block B0': {lhu, sh, ..., lui, lw, beqz}). Wait, the source order: the first `if (func_8012BEE8(...) != 0)` block, then our `if (D_801270C8 != 0)`. The `void *a0pin = sp18;` if declared at function scope with init at decl would be at the top before the first if → emitted before the func_8012BEE8 call. That changes the prologue.

But if declared at function scope *without* init, and assigned inside B1 (the D_801270C8 block)... that's c1.

Hmm, what if assigned right before the outer if:
```c
if (D_801270C8 != 0) {
```
No — assignment before it:
```c
a0pin = sp18;
if (D_801270C8 != 0) { if (...) {...} }
```
Then the addiu is at the end of the previous block, right before the `lui/lw` of D_801270C8? Actually the assignment would be emitted after the first if-block, before the D_801270C8 load. The block: {..., a0pin=sp18, lui v0, lw v0, nop, beqz}. sched1 could reorder; reorg could move the addiu into the delay slot if it's the last insn before the branch — but the lui/lw are between. Hmm, but maybe sched1 moves the addiu to just before the branch (it's independent). Then reorg fills the slot with the addiu (arithmetic, safe). That could give exactly the target! Worth testing.

But wait: does cse then sink it into B2? The set is in the previous block, used in B2 — cse would propagate and delete it. Then the addiu reappears at the call in B2 (in the bnez delay slot). Unless cse doesn't propagate across... it does.

Ugh. cse is the enemy. Unless the set is in a block that cse considers "not a simple block" due to the branch? No.

Let me just test a few candidates empirically and look at the diffs. Empirical beats theory here. Let me write 4-6 candidates and score them with sc.sh.

Candidates:
c2: a0pin assigned before the outer if (function-scope decl).
c3: a0pin used for stores too (pointer reuse) - `((u16*)a0pin)[0] = ...` etc.
c4: two-level: declare `u16 *a0pin = sp18;` and add a real use in B1 that's harmless: maybe `sp18[4] = sp18[4];`? That's a load+store, adds insns but maybe flow removes it? flow-dead-store would delete the store, leaving the load (dead) → deleted. Probably removed entirely.
c5: `if (D_801270CC == 0)` with a0pin passed via a cast expression at the call: `func_8012C51C((void *)((u32)a0pin & 0xFFFFFF), ...)` — identity-ish, and adds instructions. No.
c6: wrap in do-while(0) around the inner body (C0535).

Let me first test c2 and c6, and a variant where the array is accessed via a struct pointer.

Actually — hold on. Let me reconsider the problem: maybe the crack is to make the *inner condition* load happen earlier and the addiu... no, we need addiu before bnez.

Wait, actually, is it possible that in the target, the addiu in the beqz delay slot came from *B2* by reorg? reorg can move insns *from before* the branch into the delay slot only within the same block; the addiu is in B2 (after the branch), so reorg could move it up into the delay slot only if it's the immediately following insn in the same block. The bnez ends B1 and the fallthrough is B2. reorg processes a basic block's jumps: it can fill a delay slot with the insn after the jump if that insn is in the same block (fallthrough). Here the insn after beqz is `lui` in mine, `addiu` in target. So target's addiu is at B1's start.

Hmm OK here's another thought: what if the target's B1 start insn order is addiu first because **expand emitted the address computation before the D_801270CC load** — i.e., the source's assignment is in B1 (c1 structure) and the *scheduler* kept it first, while in mine cse sank it. So we need cse-proof. 

What cse-proof real use exists in B1? The only one: the asm. So maybe the intended crack is different: maybe we can make the addiu *not* sinkable by making it part of a *memory access in B1 that the target has*. Is there any memory access in B1? The load of D_801270CC — that's a global load. Not the array.

Hmm, wait! What about `D_801270CC == 0` — what if the source read the global through a pointer derived from... no.

Let me look at the *first* if block for a similar pattern: `p = &D_8018A91A; if (*p == 0) func_80183DA4((s32)p - 6);` — the target at 2d1c-2d38: lui a0; addiu a0; lh v0,0(a0); bnez; jal; addiu a0,a0,-6. Here the address `p` is computed with lui/addiu at 2d1c/2d20 and used for the load at 2d24. So the address computation happens in the block.

Interesting: `(s32)p - 6` computed in the delay slot at 2d38 as `addiu a0,a0,-6`. So the source passes a pointer expression to the call.

Now the key: in the target, `lui a0; addiu a0` is computed BEFORE the load `lh v0,0(a0)`. That's just normal addressing.

Hmm, let me look at how the decompiler wrote the original C for that: `p = &D_8018A91A; if (*p == 0) func_80183DA4((s32)p - 6);`.

OK let me try the empirical route. Let me write candidates.

Candidate list:
- c2: function-scope pointer assigned right before the outer if.
- c3: pointer assigned inside B1 (c1) but with two uses: call + one store through the pointer in B2.
- c4: do{}while(0) around the inner if body.
- c5: invert the inner test with goto.
- c6: inner condition `if (!D_801270CC)`.

Actually, c1 already differs only by the addiu. Small moves might flip sched1's ordering even in B2? No — block structure is fixed by cse.

Let me think about cse more concretely. In c1, cse replaces the use of a0pin (the call arg) with sp+24, deleting the set. Then expand had already emitted the addiu; cse's replacement means the addiu in B1 is dead → deleted. The addiu is emitted at the call in B2 by... wait, if cse replaces the pseudo with the constant expression `(plus sp 24)` in the call insn, then the register allocator must materialize it right there → addiu in B2. Yes.

To block cse: make the value used in a context cse can't substitute. Options: use in an insn with a memory operand? Hmm.

What if a0pin is used as a **store address in B2** (e.g., `*(u16*)a0pin = 0` or `((u16*)a0pin)[5] = 0`)? cse can still substitute a constant address into a memory operand (`sh zero, 24(sp)`), and it does (that's cse-const-addr wall).

What if the pointer is used in a *conditional* in B2 (e.g., `if (a0pin)`)? folded.

What if the pointer value is compared to another pointer variable? e.g. `if (a0pin != p)` where p is a global pointer — adds a compare and branch.

Hmm, what if the pointer is passed to the call AND stored into a global? adds a store.

OK, maybe the answer is to make the array a **local struct whose address escapes through a call in B1**? No call in B1.

Wait... maybe there IS a call in B1 in the target? Let me re-read the target: after beqz at 2d48 → addiu; then lui/lw D_801270CC; bnez. No call.

Hmm hm. Let me reconsider whether the target's addiu really is in B1 in RTL. Maybe the compiler emitted it in B2 but *before* the bnez because the bnez and the addiu were in the same block! Wait — is the `bnez` the branch of the inner if? Yes: `if (D_801270CC == 0)` → bnez v0, done. The addiu could be part of the *block ending* at the bnez if the compiler scheduled it there... but sched1 doesn't move insns across block boundaries, and the addiu's original block is B2 (after the branch). Unless the addiu's RTL was in B1.

Alternatively, maybe reorg's delay-slot filling for the *first* branch pulled the addiu from... no.

Could the addiu be in B1 because the address was used in the inner if's *condition*? The condition is a load of D_801270CC. Hmm, what if the source is:

```c
if (D_801270C8 != 0) {
    if (D_801270CC == 0) {
```
and gcc evaluates the address of sp18 early because... no.

New hypothesis: the address `sp+24` might be computed as part of **setting up the store address** for the stores in B2, and sched1 hoisted it into B1? Not possible across blocks.

Let me just test empirically whether ANY simple variant changes it. Let me create several candidates and score.

Let me write c2..c7 in one go.

c2: a0pin at function scope, assigned before outer if.
c3: c1 + use a0pin for the stores (pointer reuse):
```c
void *a0pin = sp18;
if (D_801270CC == 0) {
    u16 *q = a0pin;
    D_801270CC = 1;
    q[0] = CAST_ALIAS(u16, param_1, 6);
    ...
    func_8012C51C(a0pin, (s32)param_1);
}
```
c4: do{}while(0) around the stores+call (C0535).
c5: `if (!D_801270CC)`.
c6: invert with goto.
c7: move `sp18[4]=0; sp18[5]=0;` order? not now.

Also an important one: c8: use the array in the *outer if condition* via a comma? no.

Let me look at how the store order in the source differs from the target: source order is sp18[0], [1], [2], [3], [5], [4], [8..9], [7]; target order at 2d74: sh v0,24(sp) [0]; 2d80 sh [1]; 2d8c li 30 → sh 30(sp) [3]; 2d94 sh zero,34(sp) [5]; 2d98 sh zero,32(sp) [4]; 2d9c sw zero,40(sp) [8,9]; 2da0 sh zero,38(sp) [7]; 2da4 sh v1,28(sp) [2]. Matches source order with sched1.

OK let me generate the candidates.
