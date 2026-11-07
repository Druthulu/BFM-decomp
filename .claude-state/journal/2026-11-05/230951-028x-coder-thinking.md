---
ts: 2026-11-06T06:09:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KRniExuXIlF7Zm19uFNP
---
priority = floor_log2(nrefs)*nrefs / live_length * 10000 * size.

So it's density: refs weighted by log, over live length. pp: 2 refs (set + use per loop) — actually pp set once, used once per iteration in loop 1. zpush: set once, used twice (loop1 and loop2). Live length: pp live from before loop1 to end of loop1; zpush live from before loop1 to end of loop2.

n_refs in gcc counts loop-weighted: reg_n_refs accumulates with loop depth. Let me recall flow.c: `REG_N_REFS (i) += (loop_depth + 1) * ...`? Actually `REG_N_REFS (regno) += loop_depth + 1` per reference? Something like that.

pp: set at depth 0 (+1), use inside loop depth 1 (+2) → 3. Hmm but a set also counts. Actually in flow.c: for each insn, `REG_N_REFS (regno) += (loop_depth + 1)` for each occurrence? Let me not over-theorize.

zpush: set (1) + 2 uses at depth 1 (2*2=4) = 5? pp: set 1 + use 2 = 3. live_length pp ~ 2 insns... 

Since we need pp > zpush. Give pp more refs: e.g. an extra use in the loop that costs no instruction. What about a `do { } while (0)` — no.

Idea: use pp in the else arm too? no, changes code.

Idea: make the address &p computed once and used for both pp init and loop 2's &p arg? In target, loop 2 uses `addiu a2,sp,40` directly. Hmm.

Idea: reduce zpush priority by splitting its live range: load zpush into a var used only in loop1, and another var for loop2? Would add an `lh` for loop2. Target: `move a1,s8` in loop1's tail and presumably `move a1,s8` again in loop2's tail. Two uses of one reg s8.

Idea: increase pp's nrefs via a use at depth 1 that's free: e.g. in the loop, `pp = pp;`? cse kills it.

What about declaring pp/pf as `s32 *pp = &p;` at declaration (init at decl)? That moves the set earlier, increasing live_length — bad (lower priority).

What about making zpush's *live length* longer without extra refs? live_length is already to end.

Alternatively reduce pp's live length: pp live from its set to last use. If we move `pp = &p;` right before the loop... it's already. Actually pp is set before `zpush = ...`. If pp set after zpush's load, pp's live range starts later → shorter live_length → higher priority. Currently order: i=0; pp=&p; pf=&flag; zpush=lh. Target order: addiu s7,sp,40 (pp); addiu s6,sp,44 (pf); lh s8,6(s3) (zpush). So pp is set before zpush. Live length from set to last use. pp dies at the last use in loop1; zpush dies at end of loop2. zpush's live length much longer. So density: pp should win!

Unless nrefs differ: zpush has 3 refs vs pp 2? With loop weighting zpush 1+2+2=5, pp 1+2=3. density: pp 3*log2(3)=3*1=3 / len; zpush 5*log2(5)=5*2=10 / len. len ratio: pp live from insn ~16 to 54 (38), zpush 18 to 144 (126). pp: 3/38=0.079; zpush: 10/126=0.079. Close! That's why it's a near tie.

Mine has zpush winning slightly. So a tiny change flips it. E.g., adding one more ref to pp (making 4 → 4*2=8/38=0.21) would flip decisively.

But also the pf/pp order: target pp=s7, pf=s6, and mine already pf=s6? mine[16] addiu s8,sp,40 (pp→fp). Hmm mine's pp is fp ($30), and pf presumably s7? Wait the register pairs said "s7->fp x3, fp->s7 x2" only. So pf is s6 in both. And in mine pp=fp, zpush=s7; target pp=s7, zpush=fp.

So we need pp to beat zpush. Add refs to pp.

How to add a ref with no code? Options that worked before: "do { r = p + i; } while (0)" added a ref (from the worked example: "+1 loop-weighted ref on p via do { r = p + i; } while (0) in the 0xE store"). But that added an insn? It scored 0 apparently because the computation folded into existing addressing? In that example the store `*(s16*)(r+0xE) = -0x70` — r = p+i folded into the store address. So the ref was free.

Here: can we add a free use of pp? E.g. pass `pp` to RotTransPers4 in the loop (instead of &p)? That changes target.

Hmm. Alternatively, in the else arm? no.

What about using pp in loop 2's call as `(s32)&pa[i]`... no.

What if we express the RotTransPers4 args so that one of the stack stores uses pp differently? Target: `sw s7,32(sp)` (pp stored to stack) and `sw s6,36(sp)`. Those come from expand for args 9,10 (pp,pf). So pp is genuinely used once per loop.

Alternative approach: make zpush lose refs by computing it as a u16/s16 temp? Its nrefs is what it is.

Alternative: shorten zpush's live length. If zpush were reloaded at loop 2 (second lh), live length halves but adds an insn. Unless... the `lh s8,6(s3)` appears once in target.

Alternative: change the order of pp and pf sets relative to zpush. live_length is measured in insns between first and last reference. If we set pp right before the loop (already) and zpush earlier... zpush set is after pp. Can't shorten zpush.

Hmm, what about making pp's live range *shorter*: pp's first ref is the set. If pp were set later (closer to loop), live_length shrinks → priority rises. Currently pp set at 16, loop begins at 22ish, pp dies at last iteration's use (dynamic) — static live_length counted in insn positions: from 16 to ~51. Moving the set from 16 to 20 shortens by 4.

But target order: addiu s7,sp,40 at 16 — the set is at position 16. If we move it later, the target order changes (mismatch). Hmm, but live_length may not care exactly... no, codegen order matters.

Better: add refs to pp. Is there any free use? What about `zpush` — could we pass `pp` and `pf` to func_8012E28C? No.

Alternative: the loop 2 `&p` argument: target uses `addiu a2,sp,40`. If we write `pp` there, a2 = move a2,s7. That's a mismatch... unless target's loop-2 RotTransPers calls: first call uses addiu a2,sp,40, the 2nd and 3rd use move a2,s7? Let me look at the target loop 2 fully.

Let me dump the rest (120-170).
