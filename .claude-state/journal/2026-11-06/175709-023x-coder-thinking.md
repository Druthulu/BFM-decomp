---
ts: 2026-11-07T00:57:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1HE0i9hF4LqPOHbZulJg
---
Priority = floor_log2(n_refs) * n_refs / live_length * 10000 * size.

For p: 11379 = floor_log2(11)*11/live*10000. floor_log2(11)=3. 3*11=33. 33/live*10000 = 11379 → live = 33*10000/11379 = 29.0. Yes! So p: n_refs=11, live=29, size=1 → 11379.

b: 3333 = 3*... floor_log2(b_refs)*b_refs/live*10000=3333. If b refs=3, floor_log2(3)=1 → 3/live*10000=3333 → live=9.0. Yes b: refs 3, live 9.

a: 1944: refs=2? floor_log2(2)=1 → 2/live*10000=1944 → live=10.29, not integer. Try refs=3: 3/live*10000=1944 → live=15.4. Hmm. refs=4: floor_log2(4)=2 → 8/live*10000=1944 → live=41.2. refs=2, live=10: 2*1/10*10000=2000. Hmm 1944: maybe 35/18*1000? Let's solve 10000*f*r/live = 1944 → f*r/live = 0.1944. r=2,f=1 → live=10.29. r=7,f=2 → 14/live=0.1944 → live=72. r=5,f=2 → 10/live=0.1944 → live=51.4. r=3,f=1 → 3/live=0.1944 → live=15.4. r=6,f=2 →12/live → live=61.7. r=4,f=2 → 8/live → 41.2. Hmm none integer. Maybe live is computed with something else, or the numbers came from a different analysis (maybe the agent measured from dumps). Whatever.

c: 1666: f*r/live=0.1666: r=3,f=1 → live=18.0 exactly (3*10000/18=1666.7→1666). Yes c: refs 3, live 18.

p: refs 11, live 29. To get p below c (1666): need floor_log2(r)*r/live*10000 < 1666. With r=11, f=3: 330000/live < 1666 → live > 198. Impossible.

So reduce p's n_refs! If p refs drop to 4 (f=2): 80000/live < 1666 → live > 48. Hmm. If p refs=2 (f=1): 20000/live < 1666 → live > 12. If p's live is 29 and refs 2 → 690. That would put p last!

p refs 11: where do they come from? Each p[i] store = 1 ref (4 stores), p += 5 = 1 read + 1 write? In flow.c, reg_n_refs increments per REG in insns, with loop_depth weighting. The 4 stores are outside the loop. p += 5 → one insn with p read and write = 1 ref? Then q = p (read), p = q (write), r = p (read).

Hmm, 11 refs. Actually reg_n_refs counts each REG rtx occurrence, including both operands. Let me count from RTL:
- p[0] store: p read ×1 (plus the `p-5` computation reads p again! `p[0] = ((u32)(p - 5) & ...)` — p appears twice: as the store base and in p-5. So 2 refs.)
- p[2] store: 1 ref (p read as base).
- p[1] store: 1.
- p[3] store: 1.
- p += 5: 1 (read+write is one REG in a plus; actually reg_n_refs counts insn-level refs? In flow.c, mark_reg_ref increments reg_n_refs by loop_depth per REG occurrence... let me check: `reg_n_refs[regno] += loop_depth` in mark_reg_ref (line 2067). It's per REG rtx found? Let me look at flow.c:2060.

Anyway p appears many times.

Big idea: reduce p's ref count by reusing q for the first block. E.g.:

```
q = p;
q[0] = ...;
...
q += 5;
```
That's just renaming, same refs on the single pseudo.

Alternative: split p's uses across two pseudos with a copy, so that neither has many refs. E.g.:
```
u32 *pp = p;  // copy
pp[0] = ...
```
Then the original p has refs 1 (the copy) and pp has the rest. But then global alloc assigns both... the copy p→pp may be coalesced? In global.c, reg_may_share / copy propagation? There's `reg_may_share` computed from copies (if p and pp are tied by a copy, they may share an allocno if their live ranges don't conflict). Line ~380: `reg_may_share[r2] = r1`. So copies may share the allocno → same n_refs sum. Hmm.

But wait, if they share an allocno, allocno_n_refs = sum = same as before. If they don't share (live ranges conflict?), then...

Hmm. But actually the parameter p is special: parameters get their own pseudo and the prologue copies from a0.

Look at the target: p is copied from a0 to s3 at entry, and p (s3) is used for the 4 stores, then `addiu s3,s3,20` (p += 5), then `move a0,s3` (q = p). So p's allocno covers the whole thing.

What if we make the first block's stores use a *different* variable from the loop's? E.g.:

```
u32 *r = p;      // the target's r?
```
Hmm.

Alternative idea: use a local pointer for the stores, and keep the parameter only for the initial value:

```
u32 *pp;
pp = p;
pp[0] = ...
...
pp += 5;
q = pp;
...
p = q;  // needed for the tail
```

Then pseudo p: refs = 1 (read in pp = p) + 1 (write p = q) = 2, live 29. Priority = 1*2/29*10000 = 689! That's below c's 1666. Then p might get s3 (the lowest-priority s reg). But pp would have high refs and take s0... but the target's b=s0. Hmm, but pp is the pointer that should be s3 in the target (p=s3 is the pointer!). Wait — in the target, the pointer *is* s3, and the stores use s3. So the pointer pseudo must get s3, i.e., the pointer must be the LOWEST priority. But the pointer has all the refs. Contradiction unless the refs are split among pseudos.

Hmm! In the target: stores use s3 directly, and q is a0 (a new pointer from move a0,s3). So the first-block stores use the same pseudo as p (s3). And p is the lowest priority? That contradicts p having 11 refs.

Unless... the target's `p` allocno is not the param pseudo: the param pseudo is a0, copied into s3 (`move s3,a0`). The source `p` param becomes the a0 pseudo; the s3 pseudo is a copy destination. Global alloc gives the *copy pair* different allocnos? In gcc 2.7.2, params are copied to a new pseudo? Actually gcc's expand_function_start: for parameters, if the param is used, it's copied into a pseudo (or kept in the hard reg if not conflicting). With -O, params live in pseudos that are copies of a0-a3. `move s3,a0` = param p's pseudo = s3, a0 is the incoming reg.

The param pseudo p has 11 refs, live 29 → 11379, the highest → gets s0 in plain C. But target gives s0 to b (refs 3, live 9 → 3333). So the target's p must have different refs/live... 

OH WAIT. Maybe in the target, the pinned body: `a=$18, b=$16, c=$17, v=$2, n=$6`. The pins make those hard regs, so they don't compete. Then global-alloc assigns s3 to p and s0... no wait, the pinned body is the TREE text and it scores 0. In the pinned body, b,c,a are hard regs s0,s1,s2. Only p and q,r,nn,t,cl,cs,col,flag,i are pseudos. Global alloc then must give p... the remaining callee-saved: s3 (since s0,s1,s2 are taken by pins). So p=s3 comes from the pins, not priority!

So the target's register assignment is *forced by the pins*. Without pins, p takes s0. To get p=s3 lever-free, we'd need the other three pseudos to have higher priority and claim s0,s1,s2. In the target, b,c,a claim s0,s1,s2. b refs 3/live 9 = 3333; c refs 3/live 18 = 1666; a refs? 

p refs 11/live 29 = 11379 >> 3333. So p must take s0. To make p take s3, we need three other pseudos with priority > 11379. With refs capped by the code, live would need to be tiny: e.g. refs 3, live 1 → 30000. Hmm.

Wait, but that's the priority of the *hard-reg candidates*: global alloc assigns hard regs in allocno_compare order; for each allocno it finds a free hard reg among the usable callee-saved. The three other pseudos (b,c,a) must be allocated BEFORE p and take s0,s1,s2.

b: refs 3, live 9 → 3333 < 11379. So p is allocated first → takes s0. That's exactly the wall: p gets s0.

Unless we can raise b/c/a's refs dramatically or shrink their live. To beat 11379: with refs 3, live must be < 3*10000/11379 = 2.6 → live ≤ 2. Impossible for b which is live across the loop.

Or reduce p's priority below 3333: need 330000/live < 3333 → live > 99. Impossible; or reduce refs: refs 4 (f=2): 80000/live < 3333 → live > 24. p's live is 29 → 2758 < 3333! refs 4 would put p below b. refs 3 (f=1): 30000/29 = 1034 < 1666, below c too.

So: if we can get p's allocno n_refs down to 3-4 while keeping live ~29, p ranks last (or third) and takes s3! That's a real lever: split p's refs across pseudos, or reduce the number of times p is mentioned.

But careful: allocno_n_refs sums over all pseudos that share the allocno (reg_may_share). If we copy p into pp and they share, no gain. If they don't share, pp takes the refs.

Hmm, but the target stores use the SAME register s3 for p and the stores, and q is a0. So in the target, p's pseudo is the one doing the stores. So to have p's refs low, the stores must use a different pseudo... but then that pseudo would get a different register than s3? Not necessarily: a different pseudo could still be allocated s3 if it has low priority.

Wait, no. The target has ONE pointer s3 used for the stores, and q=a0. Let's map: p=s3 does p[0..3] stores and p+=5, then q=a0=p+... Actually `addiu s3,s3,20; move a0,s3` — q=a0 is the incremented pointer. And the loop uses a0 as q. At the end `move s3,a0` (p=q).

So two pointer pseudos: p (s3) and q (a0). p's refs = the stores (with p-5 double use) + p+=5 + q=p read + p=q write ≈ 11. Hmm, but then p should take s0.

Unless the target's p pseudo is NOT the param pseudo: the param p is a0 (incoming). `move s3,a0` means a new pseudo for p (because p is modified by p+=5, so it can't stay in a0? Actually a0 is caller-saved and p crosses the func_80029504 call → p can't be in a0, it must be callee-saved). Global alloc: the param pseudo (from a0) gets s3? But priority says s0.

Hold on. The pins force a=s2, b=s0, c=s1. The param copies in the target: move s3,a0; move s0,a2; move s1,a3; move s2,a1. The param pseudos: p→s3, b→s0, c→s1, a→s2.

But in the pinned body, b,c,a are `register u32 b __asm__("$16")` — hard-reg vars. So the source code `b = b_;` copies the parameter b_ into hard reg s0. b_ itself is a param pseudo that might be allocated or coalesced away. Hmm, actually the target's `move s0,a2` is the b=b_ copy (b_ in a2? a2 is the incoming third arg). Wait incoming: a0=p, a1=a_, a2=b_, a3=c_. Target: move s0,a2 (b = b_, s0 = a2), move s1,a3 (c = c_), move s2,a1 (a = a_). So b_ stays in a2 (its param hard reg, caller-saved, fine because it dies right after), and s0 gets the value.

So in the pinned body, the allocnos competing for s regs: p (the param), and the temporaries. b,c,a,v,n are pinned hard.

Now what about the *lever-free* body? The param pseudos p,a_,b_,c_ all compete. Target (lever-free) wants: b_→s0? The target's registers are fixed by the target object, which came from the pinned source. So a lever-free source must produce the same allocation: p=s3, a_=s2, b_=s0, c_=s1.

But the priority says p >> b_ > a_ > c_ → p=s0, b_=s1, a_=s2, c_=s3 (plain C). So a permutation cycle.

To beat it lever-free, we need p's priority below c_'s. Options:
(a) reduce p's n_refs (split the pointer's uses among multiple pseudos that don't share allocnos).
(b) increase b_/c_/a_'s priority.

Hmm, (a): what if the first-block stores use a *separate local pointer* that is a copy of p, and the copy's live range conflicts with p (so they don't share an allocno)? reg_may_share: two pseudos sharing an allocno only if the copy is not... let me read that code.

Actually in global.c:
```
  /* If a pseudo has a copy to/from another pseudo, and the two don't conflict, they may share. */
```
Let me read lines ~340-395.

Actually, the real lever: p's 11 refs include 4 stores + p-5 double + p+=5 + q=p + p=q. If we split the pointer into two pseudos across the func_80029504() call... e.g. the stores before the call? No, the call comes first.

Hmm, what about this: the source computes `p - 5` in p[0]'s value. That's a second use of p. If we instead compute the value via a temp `t = (u32)p - 20;` then p[0] = (t & 0xffffff) | 0x3000000 — p still used twice (store base + temp). No reduction.

What if we store through q for the first block? q = p; then q[0..3] stores; q += 5; ... and the tail uses q. Then p has 1 ref (q = p) and q has ~10 refs. q is a local pseudo, live from q=p to the end. Its priority would be high → gets s0. Target wants the pointer in s3. Doesn't help.

Hmm, but wait: maybe it does help if the stores' base pseudo q gets s0 and p... no, target has the pointer in s3 and b_ in s0.

So we need b_'s pseudo (refs 3, live 9) to outrank the pointer pseudo. With the pointer at 11 refs/live 29 = 11379, impossible. With the pointer split so that no single pseudo has many refs... but the stores need a base pointer pseudo with 4+ refs, live long.

Hmm, unless the base pointer is a *parameter* whose refs are fewer... 

Alternatively raise b_'s priority: b_ refs 3, live 9. If we use b_ more times (e.g. b += 8 in the loop keeps it live anyway), refs up: b refs 5 → floor_log2(5)=2, 2*5/live. live ~9 → 11111. Still < 11379 barely. b refs 6 → f=2, 12/9*10000=13333 > 11379! So raising b's refs from 3 to 6 would make b outrank p. But does that match the target? The target b (s0) has refs 3. Adding refs to b changes the code...

Hmm wait, actually, is that true? The target b's refs are 3 in the lever-free body? The prior agent computed those from... probably from the plain-C body's RTL. In the target, b is used: `andi v0,s0,0xffff` (loop), `addiu s0,s0,8` (loop), and the initial `addiu v1,s0,15` (before loop). That's 3 uses. Each use = 1 ref, but loop uses get loop_depth weighting (reg_n_refs += loop_depth for loop uses, flow.c:2067). Loop depth 1 → each loop use counts 1? "reg_n_refs[regno] += loop_depth" — for depth-1 loop, +1. Hmm.

Anyway, the analysis says b=3333, i.e., refs 3, live 9.

So the lever would be to give b more refs... but that changes the instruction count/bytes vs target. Since the target has exactly 3 b-uses, adding refs would add instructions and not match.

Hmm, but wait: refs can be added without adding instructions? No.

What about *reducing p's refs* without changing the instructions? The p-5 double use: `p[0] = ((u32)(p-5) & 0xffffff) | 0x3000000`. Target: `addiu v1,s3,-20` (p-5 in words = -20 bytes), `and`, `or`, `sw v1,0(s3)`. So p is used twice in that statement: base and p-20.

If we write `q = p; p[0] = ...` no.

Idea: use a separate pointer variable for the first store's value: `u32 *z = p - 5;` then `p[0] = ((u32)z & 0xffffff) | 0x3000000;`. Now p has 1 ref in that statement, z has 1. z is a new pseudo with refs 1, live 1 → priority 10000 (f=0? floor_log2(1)=0 → 0!). floor_log2(1)=0, so priority 0. z would be allocated last; fine.

That reduces p's refs by 1 (11→10): floor_log2(10)=3 → 300000/29 = 10344. Still > 3333.

We need p refs ≤ 4. Not feasible without changing the pointer into multiple pseudos.

Hmm OK, what about making the *loop* use a different pointer pseudo from the pre-loop stores? In the target, the loop uses a0 (q) and the tail uses s3 (p=q). So p is only used pre-loop plus the p=q write. So p's refs in the target... in the target's RTL, the source had p as a param: stores (5 refs), p+=5, q=p, p=q. That's 8-9 refs. Hmm, but the target still put it in s3 because s0,s1,s2 were pinned.

So the lever-free problem: p must be ranked below b_ (3333). p refs 11 live 29 → 11379. Reduce p's refs to 4 (2758) or 3 (1034) — that would make p rank last. But the target's instruction stream has p used ~8 times (as s3). If p's pseudo had only 3 refs, the other uses would be on other pseudos that... could still be allocated s3! Because s3 would be taken by whichever pseudo... hmm, no: if p's refs are split among p1, p2, p3 pseudos with low individual priorities, each could take s3? No — they'd conflict (overlapping live ranges) so only one gets s3; the others would get caller-saved regs or spill. Unless they're live-range-disjoint: e.g., p1 used pre-loop, p2 in the loop... but they're all the same value flowing.

Hmm, wait: q (a0) is the loop pointer — caller-saved a0. And p (s3) is pre-loop + tail. So actually the value flows p → q → p. q is in a0 (caller-saved, local-alloc'd within the loop maybe).

So the target's structure is already: p (pre-loop+tail) and q (loop). p's uses: 4 stores + p-5 extra + p+=5 + q=p + p=q ≈ 8-9 refs, live from entry to the tail end (whole function). Live 29.

Hmm, what if we shorten p's live range? p is live to `p=q` at the end (then used for the tail). If the tail used q directly, p's last use would be `q = p` (before the loop) → live ~15, raising priority (300000/15=20000). Worse.

What if we *extend* p's live? Can't beyond the function.

So (a) reduce refs: what refs does p have?
1. p[0] store base
2. p in p-5
3. p[2] base
4. p[1] base
5. p[3] base
6. p += 5 (read)
7. p += 5 (write) — does an increment count 2 refs? In flow.c, mark_reg_ref is called per REG in the insn... let me check. flow.c:2060 area.

Let me look at flow.c mark_reg_ref.
