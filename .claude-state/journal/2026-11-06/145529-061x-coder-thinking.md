---
ts: 2026-11-06T21:55:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sB7NezioSsgkV5uS4cy3
---
Line 147: "pin | func_8017E204 | MATCH — the copy through an s16 temp escapes cse2's equivalence class, so v1 keeps its own register instead of being merged with v0 (G06)"

Line 216: "MATCH: s16 flag2/3/4 + w local + ot=func_800D27DC split before return — copy escapes cse as sign-extend (combine folds to move)". So "combine folds to move" — exactly our target! The sign-extend escapes cse, then combine folds it into a move. So this works when combine can't merge it into the use.

Line 203: "s16 v and the store reads v: the HImode copy t = v escapes cse, so the target's opaque move s8,v0 survives".

So the s16 trick works in many cases. Our w2/w3 failed because combine could fold the sign-extend AND merge.

Hmm, w2's RTL: `iv2c = iVar2` (insn 95) was still there after cse, plus the sign-extend (99-101). So the RTL had BOTH. Combine folded everything.

What if I write ONLY `iv2c = (s16)iVar2;` (w3) — the RTL would be `iv2c = sign_extend(subreg(iVar2))` — combine folds to `iv2c = iVar2` and merges. Same.

The key difference in func_8017E204 / func_8018302C: the copy's *use* is in a different block or the copy is wrapped in do-while. Line 219: "the copy wrapped in do-while(0) (loop-shaped live range) — or v1,v0 survives AND the slti keeps the load's reg v0". So do-while around the COPY made it survive there.

In w1 I wrapped the copy in do-while: `do { iv2c = iVar2; } while (0);` and it didn't survive. Hmm, but there the copy source iVar2 was still live and combine merged.

Wait, maybe in w1 the do-while did split the block and combine couldn't merge, but then *local-alloc coalesced* iv2c with iVar2 because... no, iVar2 lives on.

Hmm, but the result was `beq a0,v0` with no move — meaning iv2c == iVar2 in the same register. That's coalescing. Local-alloc coalesces when the source dies at the copy — iVar2 doesn't die. Unless the copy was deleted by cse2 (after the do-while was removed by jump1).

Ugh.

Let me try the *combination*: s16 temp AND do-while. Per func_8018302C: "the copy wrapped in do-while(0) (loop-shaped live range) — or v1,v0 survives AND the slti keeps the load's reg v0; s16 temp alone rewrites the slti operand".

Let me try:
w6: `do { iv2c = (s16)iVar2; } while (0);`  — hmm, iv2c int, cast s16.
w7: `{ s16 tmp; do { tmp = (s16)iVar2; } while (0); iv2c = tmp; }`

Actually let me think about what "loop-shaped live range" means: the do-while makes local-alloc treat the variable as loop-varying, giving it a higher priority, and the EBB split stops combine from merging the copy into the use.

But in w1 the do-while did nothing. Maybe because the copy was the only insn in the loop and jump1 merged. Let me check w1's cse dump to see whether the copy survived cse and whether combine killed it. If combine killed it, the do-while didn't split. Let me dump w1.

Actually, faster: let me look at func_8018302C's actual win.c to copy the shape.
