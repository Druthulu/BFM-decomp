---
ts: 2026-10-17T11:11:30.515Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm thinking about why combine's AND simplification didn't trigger here—it comes down to whether the nonzero-bits tracking for `m` (zero-extended from a 16-bit load) is actually valid, since that tracking depends on the register being set exactly once and combine correctly recording that fact.

Since `m`'s load and the AND instruction sit in different basic blocks separated by a branch, I suspect combine never links them via LOG_LINKS, meaning it never even attempts try_combine on that pair—so the redundant mask simply survives untouched.

Now I'm wondering if MIPS's PROMOTE_MODE behavior explains why a u16 local variable stored directly compiles down to a plain move instead of an andi: if MIPS promotes sub-word locals to SImode registers, the zero-extension from HImode to SImode on a register copy might just collapse to a move rather than needing an explicit mask.

So I'm trying other ways to break the equivalence CSE sees between k and m while still forcing a plain move instruction — like reloading from memory through an intervening aliasing store, or assigning k from m through a different casting path that wouldn't trigger a sign-extend sequence.

Another idea is placing `k = m` in a separate block from the hoisted computation, but then I realize CSE's extended basic blocks with follow-jumps might still merge the fallthrough path through the conditional branch, so that trick probably wouldn't isolate them either.

Also worth checking: whether loop.c versus cse2's timing matters for when the hoisted insn is created versus reprocessed, and whether m being a hard register changes anything — but that seems unlikely to help. The more promising angle is manipulating which value becomes the equivalence "head" based on last-use cuids: if m's last use occurs later than k's, m stays the head register, and the hoisted computation would end up reading m directly instead of k.

I'm trying mismatched-mode cases too — if k is a narrower HImode copy of SImode m, cse might record the subreg equivalence rather than a plain reg-reg one, which would block substitution since the copy source isn't a bare REG, so m wouldn't get replaced by k in the shift expression.

With MIPS's PROMOTE_MODE applying even to locals (no PROMOTE_FOR_CALL_ONLY), a u16 variable k actually lives in an SImode pseudo holding a zero-extended value, so `k = m` becomes a zero_extend/mask operation rather than a clean move — meaning it'd need an andi unless combine simplifies it further, similar to the earlier u16 case.

So the reason the copy collapsed into a simple move is that CSE spans the same extended block (no intervening label between the earlier load and the preheader), letting it know m's value is already a zero-extended halfword load from memory, so it can fold the mask-with-0xffff operation away entirely using that equivalence.

I should just test concrete type combinations against the K3 and D_8011516A array access to see which variant actually reproduces this move pattern — trying u16/u16, s16/s16, and u16 with s32 combinations.

The remaining copy compiles as `andi a3,v1,0xffff` rather than `move` since combine can't simplify it when the zero-extending load is in a different basic block. I'll explore width variants of k and m to find a copy CSE won't equate but that still emits as a move.
