---
ts: 2026-11-07T00:55:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ofrmctfzJY8uYNAPpDDu
---
Target: 101 ins. Register map: p=s3, a_=s2, b_=s0, c_=s1 (b=b_ is s0, c=c_ s1, a=a_ s2, p=s3). The target copies at entry:
- move s3,a0 (p)
- move s0,a2 (b_)
- move s1,a3 (c_)
- move s2,a1 (a_)

Note the order of copies: s3,a0; s0,a2; s1,a3; s2,a1. And the loop uses a0 as the "q" pointer (move a0,s3 after p+=5... wait `addiu s3,s3,20; move a0,s3` then q is a0). And a1 = q+12 (the q[3] address), a0 advances by 20 each iteration. So q lives in a0, and q+... hmm.

Also note in the loop: `addiu a1,a0,12` — a1 = q + 12 = &q[3]. Stores: sw v0,-4(a1) = q[2], sw v1,-8(a1) = q[1], sw v0,0(a1) = q[3]. So q[0] uses a0 directly.

Target loop counters: a3 = i (s16), s2 = a, s0 = b, t0 = flag, t2 = cl, a2 = n (nn?), t1/t3 = masks.

Interesting: the target's tail uses v0 = s3 (r = p = q final). And s3 is updated `move s3,a0` at loop end (p = q).

So the target: p=s3 stays as the base pointer through the loop; q=a0.

Now plain C: p has refs 11 and live 29 → priority 11379; b 3333; a 1944; c 1666. So p takes s0, b s1, a s2, c s3? Prior note says "target b=s0 c=s1 a=s2 p=s3; plain C priority p >> b > a > c". So plain C gives p=s0, b=s1, a=s2, c=s3 presumably. That's a permutation. Score 43.

To move p down: lower p's refs or live length. p's live range: p is live from entry to p=q... Actually in the target, p (s3) is live through the whole function (until move s3,a0 at loop end). Hmm.

Wait, but priority is computed by global.c over the *allocno* (pseudo). The param pseudo p spans... In plain C, p is the parameter, live whole function. Its ref count: p[0],p[2],p[1],p[3], p+=5 (read+write), q=p (read), p=q (write), then r=p... Actually in the plain-C rewrite (r4.c) p=q then r=p then r-8, r-3. So p refs: 4 stores + add + read for q + write p=q + read p for r = 8ish. Hmm notes say 11 refs/29 live.

What if we eliminate the `p = q;` assignment and the r copy: after the loop, use q directly: `*((u16*)(q-8)) += 6;`. Then p's last use is `q = p` before the loop, so p's live range shrinks to end at q=p (before loop). That would lower p's live from 29 to ~15 and thus raise its priority (live smaller → priority higher!). Priority = refs*8/live; smaller live → higher priority. That's bad.

To lower p's priority: raise live or lower refs. p's refs: each p[i] store is a ref. Hmm.

Alternatively raise b/c/a priorities: b has 3333 (refs?), a 1944, c 1666. To get b > p... p=11379 is way ahead.

Alternative: make p not a param pseudo — the param pseudo has a preference? In global.c, allocno_compare: priority = (floor(refs*8/(live+1))). Params get refs from the copy? Hmm.

Actually, maybe the trick is the opposite: make the target's order b=s0 c=s1 a=s2 p=s3 arise not from priority but from something else. The target's prologue order: sw s3 first, move s3,a0 first — that's the order the copies are emitted, which is reverse of assignment order? The prologue: sw s3; move s3,a0; sw s0; move s0,a2; sw s1; move s1,a3; sw s2; move s2,a1. So copy order p,b,c,a. That's s3 (p) first. The prologue save order: s3,s0,s1,s2 — that's the "used regs in order of first use"? Actually gcc emits saves for the callee-saved regs it uses in an order (the order the regs appear in the entry copies). Hmm: s3,s0,s1,s2 — which corresponds to copies p,b,c,a.

If the assignment were p=s0, b=s1, a=s2, c=s3, the prologue would save s0,s1,s2,s3 and copy s0,a0 etc.

So we need the register allocation permutation.

Honestly, given the prior 28 tries, this is likely a WALL. But we must do ≥30 scored tries. Let me plan a set of bodies: real C moves from C0505 catalog:

1. base void (r4.c equivalent) — score 43.
2. q used for the first stores instead of p (pointer reuse) → changes refs.
3. p eliminated: use a separate pointer for the first block, then q = that pointer + 5.
4. Split p into two variables.
5. temps for cs/cl.
6. init at decl.
7. loop shape: do-while with `// !FAKE: do-while`? Careful: do{}while(0) only with the comment. A do-while loop is a different shape; C0505 allows loop shape.
8. s16/u8 widths.
9. statement order variations.
10. &&/|| folds: `if (nn || i == 3 || i == 1)`.

Since we can run sc.sh on many candidates at once, generating 30 bodies is feasible. But the scoring is per-includer (first one), ~1-2 s each. Fine.

Item 2 first might be a quicker crack (score 1). Actually the brief says don't stop between items; order doesn't matter. Let me start with item 1 since it's first in list, but the wall clock budget is per item.

Hmm, time management: 20-30 min per item. Let's do item 1 now: start time noted. Let me record start time: 17:54 start of session. Item 1 start ~17:57.

Let me write a batch of candidates. First the base void body (r4.c style) with the launders removed. That's the "clean rewrite" that scored 43.

Wait — is r4.c lever-free? It has no pins, no asm. Yes. It scored 43 per T10 notes.

Now, in this shard, dt.sh uses recs[0] (includer MAIN_012) rather than SC03_099. The prior S07 note said MAIN_012 gave uncalibrated 77 in T10, but now calibration works (orig scores 0). Does the plain body score the same 43 on MAIN_012? Possibly different because the target object differs (same function though). The score compares function instructions of the includer's object. All includers should have identical function code. Let's check: score r4.c via dt.sh.

Let me set up the scratch: copy r4.c to the item dir as w0.c (base).

Also I should look at the diff to understand what differs. Let me score base and get the full diff (dt.sh with tail larger, say 60).

Let me do it.
