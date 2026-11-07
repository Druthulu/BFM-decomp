---
ts: 2026-11-06T21:44:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OCvaAI00DGGWGJhm4kEE
---
Both 5, 55 ins. So the sign-extension didn't survive — because iVar2 is known to be 1..16, combine folds sign_extend to a copy, and cse merges.

The target's move v1,a0: a copy that survives. We need a mechanism where the copy is not cse-equivalent.

Ideas:
1. Store/load through a local memory object? That's a different instruction (sw/lw), no.
2. Compute iv2c from a value that isn't the same pseudo: e.g., make iVar2 die at the copy and re-materialize later differently. If iVar2 dies at the copy (no later use), local-alloc will coalesce iv2c and iVar2 (copy pref), removing the move. Not that.
3. cse's copy propagation is per-EBB; the do-while split was merged by jump1. Maybe a construct that survives jump1: a loop? `while (0) { }`? That's the same. What about an `if (0) {}`? folded away.
   C0535 says do{}while(0) splits cse1 EBB — but here it did not work. Why? Because the do-while at the top level of a block: jump1 merges the block? Actually the RM3x note in C0535: "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item". Maybe the split works only when the do-while wraps a store that gets deleted... Hmm.

   Wait — maybe it DID split the EBB, but cse1's copy table isn't the issue: the propagation might be done by `combine` (which also does copy propagation across... no, combine works within a basic block). Or by cse2? Or maybe jump1 merged. Let me check the actual generated asm for w1: the diff showed `beq a0,v0` — a0 is iVar2's reg. So iv2c was fully coalesced/propagated.

4. Make the copy go through a function call? no.

5. Change the comparison: `if (iv2c != one) uVar5 = 0;` — one is pinned to $2. The target: `beq v1,v0` where v0 = one. If instead we could get iv2c into v1 by local-alloc without a copy... The move exists because the target's source had a copy.

6. An asm-free way to create a genuine "copy to a new register" that cse cannot see through: make the two variables have different modes and not provably equal. E.g., make iv2c `unsigned int` and iVar2 `int`: still same mode (SImode) and equal.

7. Use a pointer cast: `iv2c = *(int*)&iVar2;`? That's an identity address spelling launder — explicitly not counted.

8. Volatile read of a temp: `volatile int tmp = iVar2; iv2c = tmp;` — volatile is a lever (new kind) — forbidden.

9. Create the copy via a struct field assignment through a local struct? That's a memory op.

10. Make iVar2's value flow through an s16 *parameter/variable of a different type* so that the copy is a real mode conversion not provable: e.g., `iv2c = (s16)t2` where t2 is `unsigned short` loaded... no.

Hmm. Let me reconsider: maybe the move can come from a different place. The target: `move v1,a0` where a0 = iVar2 from the else arm (t+1). What if instead of a copy, we compute iVar2's value twice into two variables — i.e., `iVar2 = t + 1; iv2c = t + 1;`? combine/cse would see the same expression and reuse. But if written as `iv2c = iVar2 + 0`? identity.

What about: `iv2c = iVar2;` where iVar2 is declared `register`? no, register vars forbidden.

What if the else arm assigns to iv2c directly and iVar2 is derived from iv2c?
```
t = param_2 >> 16 & 0xf;
iv2c = t + 1;
iVar2 = iv2c;
```
Then the copy is iVar2 = iv2c, and iVar2 is used later (in r = iVar2 << 3). cse would equate them and propagate iVar2→iv2c, deleting the copy... The move in the target is `move v1,a0`: v1 = iv2c (in v1), a0 = iVar2. Same thing.

Hmm, what about making iv2c's live range start earlier (declared/assigned before the branch) so local-alloc must place it in a different register than iVar2? The RM1 note says: "hoist it above the branch so the copy and its use land in different blocks" — that's what made it survive there. In our case, the copy is in the same block as the use (the if block). Since cse propagates copies within a block regardless.

What if we hoist `iv2c = iVar2;` above the `if ((short)iVar4 == six)` test, i.e., before the else arm assigns iVar2? Then iv2c = iVar2 (old value, wrong semantics).

Different: put the copy in a separate block:
```
{
    int iv2c;
    if (iVar2) { ... }
}
```
Hmm.

Alternative real-C: make the copy pass through a function parameter to a no-op? no calls allowed (would change code).

Let me think about what mechanism the launder actually provides: `__asm__("=r"(iv2c):"0"(iv2c))` forces iv2c into a register (a new pseudo not equal to iVar2's). The copy `iv2c = iVar2` remains as an insn because the asm reads iVar2 and writes a new pseudo.

Real-C analog: an operation that GCC 2.7.2 won't simplify because of a hard-register operand — e.g., `iv2c = iVar2 + zr` with zr pinned to $0. But that's a pin (forbidden kind). Hmm — but the item's kinds are `launder` only; pins "under other causes" already exist and "may stay, never added". Adding a $0 pin is adding a pin lever — forbidden.

Wait — but a C-level expression that combine can't fold... The RM1 note says a C-level zero folds. What about `iv2c = (int)((unsigned)iVar2 | 0)`? identity — launder.

Hmm. What about making the value come from a bitfield extraction or a truncation that is *not* provable? iVar2's range is known (1..16). What if we widen the range: e.g., compute iVar2 differently so GCC can't prove the sign-extend is a no-op, then... but the sign-extend would emit sll/sra (2 insns) not a move.

Actually — what if the HImode copy is done on a variable whose value GCC knows is already sign-extended s16? Then `tmp = (s16)iVar2` folds to a copy... and cse propagates.

Hmm, in func_80182ED4 the value t came from `((Unk*)arg0)->unk84` (a load, unknown range), so the sign-extend was real (but the value was already in a register sign-extended? no...). The note says "the sign extension folds away (t is a sign-extended s16 already)". So there the sign-extend folded, and yet the copy survived as `or v1,v0`. Why did it survive there but not here?

Because of block structure: `tmp = (s16)t; u = tmp;` before the if, and `u` used in the else arm (a different block). cse's copy propagation is per extended basic block... the if/else creates blocks. cse can propagate across a block boundary only if the block is the same EBB (fall-through into). Hmm, and cse2 (post-loop) too.

In our case, the copy and its use are in the same block → propagated.

So: put the copy and the use in different blocks, with the value still correct. Structure:

```
{
    int iv2c;
    iv2c = iVar2;
    if (iv2c) { ... }
}
```
Hmm. Actually the target code around: the else arm computes iVar2 = t+1, then the copy to v1, then compares v1 with v0 (one=1) and conditionally sets uVar5=0. So the copy is directly before the compare.

Could we introduce a real branch between? E.g.:
```
if (iv2c != one) uVar5 = 0;
```
becomes
```
if (iv2c == one) { } else { uVar5 = 0; }
```
No extra branch emitted (both arms simple) — but the structure may create blocks. Hmm.

Alternatively put the copy inside the if-arm:
```
if (iv2c != one) uVar5 = 0;
```
with iv2c assigned before an `if (something)`. 

Let me think about what creates a block boundary in GCC 2.7.2 that jump1 won't merge: a conditional branch (if) or a loop. If we insert a harmless `if (iv2c != 0) { }`? It would emit a branch — changes code.

Hmm.

Alternative: make the copy not equivalent by using different types where the conversion is a no-op instruction-wise but cse can't equate: e.g., iv2c as `unsigned` and iVar2 as `int` with a conversion `iv2c = (unsigned)iVar2` — same mode, cse sees it as a copy.

What about a union? no.

What about: `iv2c = iVar2 & 0xffff;`? That's a truncation (andi) — emits an andi instruction, extra.

Wait: what about the range trick — `iv2c = (s16)iVar2;` where GCC can't prove the sign bit is 0, emitting sll/sra? Then we'd have 2 extra insns, 57 vs 56. Not good.

Let me look at the actual target asm to know exactly the instruction and its operands. Maybe the "move v1,a0" could actually be produced differently, e.g., the target might have the copy from a different source. Let me dump target and mine for w1.

Use the diff output from delever_search, or better use cc1 dumps? Simplest: delever_search prints the asm diff. Let me run tryinc with a larger tail on w1 to see the full diff.
