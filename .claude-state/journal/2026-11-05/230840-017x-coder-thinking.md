---
ts: 2026-11-06T06:08:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VOU6fGygDdN4DdH3HWvV
---
Now clear. Roles:
- a0 param: mine s1, target s0.
- loop ptr s2: mine s0, target s2.
- ent (s16 *): mine s2, target s1 (`addiu s2,s0,4` mine / `addiu s1,s2,4` target — that's ent = (s16*)(s2+2)).

So the allocation order in target: a0 $16, ent $17, loopptr $18. Mine: loopptr $16, a0 $17, ent $18.

Interesting: the target's allocation order by priority: a0 highest, ent next, loop ptr last. Mine: loopptr, a0, ent.

Hmm, in the target the loop pointer s2 got $18... wait the pin was $18! The pin forced the loop pointer to $18. Right — orig has `register u16 *s2 __asm__("$18")`. So in the target the loop pointer is $18 = s2. So target allocation: a0 $16, ent $17, loopptr $18 (pinned).

Lever-free: loopptr got $16, a0 $17, ent $18. So we need a0 to outrank loopptr, and ent to outrank loopptr. Or generally the natural ordering with loopptr last.

Why does the loop ptr have such high priority? It's in a loop (weighted refs). Options:
(a) Make the loop pointer not a loop variable per loop.c (goto loop → no LOOP notes), so refs are unweighted. That's a known move: `do-while` → `goto` loop kills loop notes. That would drop the loop weighting. But careful: loop.c might also matter for other things in this function. Let's try the goto-loop rewrite: 

```c
if (s2 != s5) {
    s3 = a0 + 4;
    do {
        ent = (s16 *)(s2 + 2);
        ...
        s2 += 0x86;
    } while (s2 != s5);
}
```
→
```c
if (s2 != s5) {
    s3 = a0 + 4;
loop:
    ent = (s16 *)(s2 + 2);
    ...
    s2 += 0x86;
    if (s2 != s5) goto loop;
}
```

That's real C, no levers. This kills the LOOP notes so the refs are unweighted. But a0 is referenced 55 times, so a0 would then outrank loopptr.

Hmm, but the priority formula in global.c: floor_log2(nrefs)*... Actually allocno priority = (n_refs * 10000 / live_length) roughly. Let me recall gcc 2.7 global.c:

```
/* Compute the priority number for each allocno. */
...
priority = (n_refs * 10000) / live_length  ... 
```
Actually in global.c:
```
static void
compute_priorities ()
{
  ...
      int n_refs = allocno->n_refs;
      ...
      if (n_refs <= 0) ...
      if (n_refs < 4) ... 
      /* Penalize pseudos live across calls... */
      ...
      priority = (int) ((double) n_refs / (live_length) * 10000) ...
```
Hmm, I recall:
```
	  /* The number of refs is multiplied by the loop depth. */
	  ...
	  allocno->priority = ((double) n_refs / (double) live_length) * 10000;
```
Something like that. n_refs is weighted by loop depth (REG_N_REFS incremented with loop_depth? In flow.c, `REG_N_REFS (regno) += loop_depth` maybe).

Actually gcc's flow.c: `REG_N_REFS (i) += (basic_block_live_at_start ? ... : 1)`. In regclass/global, `n_refs = REG_N_REFS (regno)` where flow counts each ref, weighted: in flow.c `count_reg_usage`? Hmm, `REG_N_REFS (reg) += loop_depth + 1;` I believe: in `mark_regs_live_at_end`/`record_reg_ref`? Let me check tools/reference/gcc-2.7.2/flow.c if needed.

Anyway, empirical approach: try the goto loop first.

Actually wait — maybe simpler: does the loop weighting even matter? loopptr live length is short (loop only, from `s2 = D_801202A0` to end of loop) — about 40 insns with ~8 refs weighted 2x. a0 lives the whole function (281 ins) with 55 refs. Priority = nrefs*10000/live_length. a0: 55*10000/281 ≈ 1957. loopptr: 8 refs weighted 2 = 16*10000/40 = 4000. So loopptr wins. With goto loop: 8*10000/40 = 2000 — still slightly above a0's 1957. Hmm, close.

Hmm. But wait, target order was a0 $16, ent $17, loopptr pinned $18. Lever-free with no loop: a0 1957, ent?, loopptr 2000. loopptr would still beat a0 barely. Risky.

Alternative: reduce loopptr's live range or refs? Or increase a0's refs. Or... hmm.

Another thought: the target's ent is $17 and loopptr $18. Lever-free mine: ent $18 (last). ent's refs: `ent = (s16*)(s2+2)` once, used in 2 calls (func_8012BC60, func_8012B6D4). It's inside the loop → weighted. ent: 3 refs, live range inside loop ~15 insns → 3*2*10000/15 = 4000. Hmm that would beat loopptr. But mine gave ent $18 (lowest)... 

Hmm, my model of priority is off. Let me check global.c compute_priorities in the reference.

Let me read tools/reference/gcc-2.7.2/global.c compute_priorities.

Actually, I should be careful about time: 20-30 min per item, 4 items. Let me be efficient but correct.

Let me look at global.c.
