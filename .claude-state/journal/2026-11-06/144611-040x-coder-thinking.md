---
ts: 2026-11-06T21:46:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hBCNRcDgmgXEhVFYWEcI
---
There's `oracle.baseline_path(obj)`. I could write a small script to dump the target asm using tools modules, but easier: use `--explain`? That prints residual only.

Alternative: get target disassembly via `tools/` helper. Is there `tools/disas.py`? Let me grep tools for OBJDUMP usage / a "dump asm" tool.

Actually, simpler: I can write a scratch python script under my shard dir that imports tools.modules to get the baseline object and disassemble. But maybe not needed.

Let me think about the mechanism instead, and test candidates empirically — cheaper.

Key insight from the diff: mine lacks `move v1,a0` before `beq v1,v0`. The target's `one` is pinned $2 (v0) and iv2c is v1, iVar2 is a0.

Where does iVar2 live? a0. So target: `move v1,a0` (iv2c = iVar2), then `beq v1,v0` (iv2c != one).

To force the copy with real C, options:

(1) Make iv2c a *different type* whose conversion emits a real instruction that is itself the move. E.g., `iv2c` as `unsigned short`? Then `iv2c = iVar2` stores a HImode: it would emit `sll/sra` or `andi`... Since iVar2 is known 1..16 (positive, < 32768), truncation to unsigned short is provably a no-op? GCC still needs to zero-extend to int for the compare — but the compare `iv2c != one` with iv2c unsigned short: GCC knows the range, might fold. Hmm.

(2) Force the copy by making the two live ranges conflict: if iv2c and iVar2 can't share a register, local-alloc must emit a move. They conflict if iv2c's live range overlaps iVar2's *and* they're both live simultaneously — but they're the same value; if cse propagates, iv2c disappears.

The real question: how to stop cse's copy propagation. cse records `iv2c == iVar2` and replaces iv2c's uses. It only does this within an EBB. So we need the use in a different EBB than the copy, and jump1 must not merge the blocks.

What creates a non-mergeable block boundary between two statements? A conditional jump with both edges, or a label that's a jump target from elsewhere. 

Idea: wrap the copy+use in an if/else where both arms do the same thing? jump2 would merge identical arms.

Idea: put the copy inside a `do { ... } while (0)` that also contains a conditional:
```
do {
    iv2c = iVar2;
    if (iv2c != one) uVar5 = 0;
} while (0);
```
jump1 merges the loop body back into the parent? The do-while's body has a conditional inside; the block containing the copy and the conditional are the same block anyway.

What about:
```
if (iVar2 == 0) { iv2c = 0; } else { iv2c = iVar2; }
```
That's wrong semantically? iVar2 is 1..16 so `iVar2 == 0` is never true, but GCC can't know (t+1 where t = param_2>>16 & 0xf — it CAN know: t is 0..15 so t+1 is 1..16; nonzero_bits might prove != 0 and delete the branch!). Actually GCC 2.7.2's range analysis is weak; the and with 0xf gives nonzero_bits... maybe.

Even if kept, we'd add a branch. Too costly.

Idea: use a helper variable of a different *mode* to force a real conversion that is exactly one instruction `move`? No.

Alternative approach — maybe the move doesn't have to come from the iv2c copy. What if we restructure so that iVar2's value is copied to another variable that IS used, in a way cse can't fold: e.g., 

```
t = param_2 >> 0x10 & 0xf;
iVar2 = t + 1;
iv2c = t + 1;    /* recompute */
```
cse would CSE the two computations (same expression) and reuse — cse's constant/expression hashing replaces the second `t+1` with the first pseudo → becomes a copy → then copy propagation deletes it. Same.

Idea: use the pinned `one` register? one is $2 pinned, assigned 1 after. The target's compare is `beq v1,v0`.

Hmm, what about making iv2c live across a call... no calls.

Let me reconsider: maybe use an s16 *variable* whose sign-extension is not provable, and then the sign-extend itself (2 insns) would break the count. Unless... the value's type is s16 and the assignment `iv2c = tmp` is where the sign extension happens. In func_80182ED4 the sign extension folded because t was loaded as s16.

What if iv2c is declared `s16` and compared to `one` (int)? The compare `iv2c != one` would compare the s16 zero/sign-extended.

Wait — actually let me revisit: what if we make the copy involve a *different pseudo with a different mode* such that cse sees `iv2c = (int)tmp` as a conversion, but combine folds it into a move and the move survives because... In func_80182ED4 it survived! The key difference: there, tmp/u were computed BEFORE the if, in a different block from the use (`t = u - 1` in the else). Block boundary = the if.

So: in our case, can we put `iv2c = iVar2` before a branch and use iv2c after? The structure is:
```
if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; }
else { t = ...; iVar2 = t + 1; param_2 <<= 4; }
{ int iv2c; iv2c = iVar2; one = 1; if (iv2c != one) uVar5 = 0; }
uVar1 = ...;
```
The copy is after the if/else join. If we move the copy into each arm (both arms assign iv2c), then... cse: in the then-arm iv2c=1; in else-arm iv2c=iVar2 — the copy in the else arm is still same-block as its use? The use is after the join, a different block (the join block). cse's copy table resets at block boundaries (unless the block is reachable by fall-through in the same EBB... the join block is reached by jump from the then-arm and fall-through from else).

Hmm! That's promising and semantically identical:
```
if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; iv2c = 1; }
else { t=...; iVar2 = t+1; param_2 <<= 4; iv2c = iVar2; }
one = 1;
if (iv2c != one) uVar5 = 0;
```
But then in the else arm, `iv2c = iVar2` is the last statement — combine/cse within the block would still equate iv2c and iVar2 (same block!). Then the use in the join block: cse's copy table is per-EBB; the join block is a new block, so the copy might not be visible... but the copy in the else block would still be deleted as a dead copy if iv2c's only use is in the join block? No — cse deletes a copy only if it can replace all uses; if the use is in another block, it can't (it keeps the copy). Actually cse's copy propagation within an EBB: `iv2c = iVar2` followed by no use in the same block — the copy remains. Then iv2c is a live variable across the block boundary and local-alloc must give it a register — a move is emitted (possibly coalesced with iVar2 if iVar2 dies there... iVar2 is used later in `r = iVar2 << 3`, so it doesn't die → no coalesce → move survives!).

That's exactly the RM1 mechanism ("hoist it above the branch so the copy and its use land in different blocks").

But there are two arms — we'd need iv2c assigned in both, or only in the else arm and the then-arm value... The then-arm sets iVar2=1 and iv2c must be 1. We could write:

```
if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; iv2c = 1; }
else { ...; iv2c = iVar2; }
```
But `iv2c = 1` in the then-arm is a constant move (li), while the target's move is `move v1,a0`. Hmm, in the target, after the then-arm, does it have `li v1,1`? Let me check the target asm around. The target's `move v1,a0` is at index 27, in the else path presumably.

Alternatively assign iv2c = iVar2 in BOTH arms (then-arm: after iVar2=1, `iv2c = iVar2;` → that's a copy of the constant, likely folded to li v1,1). Hmm, target might have `li v1,1` there.

Let me look at the target asm. I need it. Let me write a scratch disassembler under my shard dir using tools modules (oracle.baseline_path + md.insns_from_object). Let me check the module names in tools/.
