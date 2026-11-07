---
ts: 2026-11-07T00:09:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9PeWKl2E1jA7CKUr69ES
---
All 39. The t copy never survives. This is the cse-copy-merge wall, and the param regs are global-pri-bank-order.

I've done 29 + 12 = 41 tries on item 2. Time: 17:01 → ~17:25 = 24 min. Good.

Let me record item 2 as WALL. best = 31 (perm_1432) — but wait, "best = lowest score of a lever-free body". perm_1432 is lever-free (no pins, no launder) and scores 31. So best = 31.

Hmm, but wait: is perm_1432 lever-free? Yes, it's derived from win.c which has no asm. Good.

wall tag: which? The dominant issue is cse-copy-merge (t) and global-pri-bank-order (params). I'll use `cse-copy-merge` as the primary tag... Hmm, the format allows "a tag from walls.txt or a new `<pass>-<what>`". Since both apply, let me use `cse-copy-merge` (the t/iVar4 copies) — actually the bigger contributor with the best body might be different. Let me think: with the best lever-free body (perm_1432, 31), the residual has both. 

The wall field takes one tag. I'll use `cse-copy-merge` since the t/iVar4 copy merge is the structural blocker (present in all 5 blocks) and the param order is secondary. Hmm, but actually the param permutation was 19 with the t pin held, and the t issue 15 with params pinned. Both.

Actually, let me reconsider: maybe I should report the wall as `cse-copy-merge` and mention the param order in evidence.

Let me write the row:
`func_8012DBD0__func_8012DBD0  src/shared/ov/func_8012DBD0.h  func_8012DBD0  launder,pin  WALL  31  41  cse-copy-merge  ...`

evidence: "cse merges `iVar5 = t` / `iVar4 = t` so t folds into iVar5 (mine lh s1 vs target lh v0; move s1,v0); 12 t spellings all 39; param pri order also inverted (best perm_1432 31)"

That's ~180 chars. Need ≤140. Trim:
"cse merges iVar5=t / iVar4=t (mine lh s1; target lh v0 + move s1,v0); 12 t spellings all 39; param allocno order also inverted (best perm 31)"

~150. Trim more:
"cse merges iVar5=t/iVar4=t: mine lh s1, target lh v0+move s1,v0; 12 t spellings all 39; param order inverted too (best perm 31)"

~135. Good.

Hmm, wait. Before recording, let me reconsider whether I should keep trying. Item 2 is a header with 141 includers — even if I cracked it on k=0, verifying 141 includers would be expensive. The task says MATCH only if score 0 on every includer. A WALL here is plausible.

But let me reconsider the param order once more, since a smarter move might exist. Actually, let me check: is the param order really a separate wall, or would fixing the t copies also fix the params (since allocation changes)? Possibly. But since I can't fix t, it doesn't matter.

Let me record WALL and move to item 3. Time is ticking (4 items).

Actually, hold on. Let me reconsider ONE more idea for t, because it's the crux. The target's t is a HARD REG v0. cse doesn't merge pseudos with hard regs the same way... Actually, let me test a different hypothesis: maybe the copy survives because t is *multi-set* AND the sets are in different blocks. cse1 processes per extended basic block; t is set in block 1 and again in block 2 etc. Within block 1, t is set once.

Hmm, but the target's block 1 copy survives. So no.

Let me check whether the RTL even has `iVar5 = t` after cse in the pinned body. Let me look at the .lreg dump of the pinned body for the move.

Actually — the pinned body's assembly has `move s1,v0`. So yes, the copy is in the RTL.

OK here's the thing: with t pinned to v0, cse's make_regs_eqv(iVar5, t) — t is a hard reg. Looking at make_regs_eqv's canonicalization: "Prefer fixed hard registers to anything. Prefer pseudo regs to other hard regs." v0 is not fixed. So the else branch: "If NEW is a hard reg (known to be non-fixed), insert at end. Otherwise, insert before any non-fixed hard regs that are at the end."

NEW = iVar5 (pseudo). So it's inserted before non-fixed hard regs at the end. The canonical (first) might remain t. Then uses of iVar5 → t? That would give `lh v0` and all iVar5 uses in v0. But the target has iVar5 in s1!

So cse did NOT equate them. Which means `insert_regs` wasn't called with a matching class. Why? Because `t = (mem)` and `iVar5 = t`: the class lookup for the source register t... 

Hmm, maybe cse doesn't propagate a copy from a HARD register into a pseudo when the hard reg is "modified"? 

Whatever. The empirical result: with t pinned, the copy survives; without, it merges.

Hmm, is there a C way to make t a hard reg naturally? No.

OK, let me look at it from yet another angle: what if the copy `move s1,v0` is NOT from `iVar5 = t` but from something else? Let me look at the C again:

```
iVar5 = t;
if (t < 0) {
    iVar5 = -iVar5;
}
```
The target: `bgez v0; move s1,v0; negu s1,s1`.

If instead the C were:
```
if (t < 0) {
    iVar5 = -t;
} else {
    iVar5 = t;
}
```
Then: `bgez v0, else; negu s1,v0; j; else: move s1,v0`. Not matching (target has move in the delay slot and negu after).

Hmm, target: `bgez v0,5aec` (if t>=0 skip); delay slot `move s1,v0`; `negu s1,s1`. So: iVar5 = t; if (t < 0) iVar5 = -iVar5. Exactly the C.

So the copy iVar5=t is essential and cse merges it lever-free.

Unless... the C could make iVar5 = t via a *different* variable that's already needed. Hmm.

What if we write:
```
iVar5 = t;
```
but `t` is declared `s32 t;` and assigned from the load — cse merges.

What if `t` were declared `u32 t;`? Then `iVar5 = t` is an unsigned→signed copy. Same mode. cse merges.

What if `t` is `s16`? Then iVar5 = t needs sign extension → `sll/sra` or the load result already sign-extended. Hmm, the target's `lh v0` already sign-extends. If t is s16, then `iVar5 = t` is HImode→SImode. In RTL: `set (reg iVar5) (sign_extend (reg t))`? But gcc might emit `move` if it knows the reg already holds a sign-extended value. Hmm, risky.

Let me try it: declare t as s16 and iVar4 as s32. Actually, the header says `s32 t`. Let me try `s16 t` and see.

Actually wait — the loads: `t = (s32)*(s16 *)(uVar3 + 4);` if t is s16, the cast to s16 would be a truncation. The load is lh (sign-extended). Assigning to s16 t... hmm, gcc would do lh then maybe nothing.

Let me just try a few type variants: t as s16, u16, u32; iVar5 as u32.

Also try iVar5 declared u16 (the target stores param_2/3 as u16...). Hmm.

Let me do a quick batch of type variants. If nothing, record WALL.

Actually, time check: ~17:26. Item 2 at 25 min. Let me do ONE more quick batch (4 variants) and then record.
