---
ts: 2026-11-06T08:48:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_r4q0eiWu1mnSGGfa70dA
---
So with off kept alone: t4 is correct (v1), but the a0-copy/t3 swap remains (score 7).
With t3 kept alone: t3/a0-copy correct, t4 wrong (v0 instead of v1).

The full target needs both effects:
1. t3's live range extended (to lower its priority below the a0 copy's, giving a0-copy a2 and t3 a3).
2. r84 (off*4 address temp) live across the t4 load so t4 gets v1.

Real C that does both without asm: We need a *real use* of t3 after its store (extending its live range), and a real use of the address temp (off) across the t4 load.

Hmm! Interesting: what if we compute the fifth load using t3 or the h computation using t3? No...

What about: `sp10[3] = t3;` moved later (after h[0]/h[1])? That would extend t3's live range across the h updates naturally. But target's instruction order has sw t3 before lw t4. sched1 orders; a store to stack vs loads... Let's test: move `sp10[3] = t3;` to after h[1] (before h[2]) or after t4 load. In c1 I moved it after t4's load → lost the nop. Let me try moving it after h[0] or h[1]:

- d1: stores t0,t1,t2; t4 load; sp10[4]=t4; h[0]; sp10[3]=t3; h[1]; h[2]...
Hmm, but the store order matters: the call reads sp10[0..4]. Moving sp10[3]'s store later is semantically fine.

But also we need r84 live across the t4 load. If the fifth load (using off) is moved earlier or its address reused... 

Actually wait: in the t3-kept-only variant, why did t4 get v0? Because r84 (address temp) dies at the t4 load. In the off-kept variant, r84 lives past the t4 load (asm uses it) → t4 → v1. For real C, we need r84/off to be used after the t4 load. If we move the fifth load earlier (before some stores), then off's last use is earlier, no.

What if we use `off` for an h[] address computation? E.g., h[0] address... no.

What if the *fifth load* is written to use off in a way that requires off live after? no, the load is its last use.

Alternative for t4→v1: t4's priority is 10000 (2 refs, live 2). If t4's live length were 1? Can't. If t4's refs were 1 (store only)? no.

Hmm, what makes t4 take v0 vs v1: the availability of v0 at its allocation. In the t3-kept variant, v0 is free when t4 is allocated (r84 dead). If we make another pseudo with higher priority than t4 take v0... e.g., the a0 copy? No, it's 3703.

What about r84's live length: if r84's priority stays 12000 (highest) and its live range extends past t4's birth, t4 → v1.

Real C idea: compute the fifth load's address from a variable that is also used later. E.g.:

```
    off = a1 * 20;
    ...
    h = (u16*)sp10;
    ...
```
What if we use `off` in a *second* real place that the compiler folds into an existing instruction — for instance the h[] computation could index sp10 with off? No, that changes code.

Hold on. Maybe a cleaner real-C restructure: make t4's load happen through the same expression as t3's and move the store. Hmm.

Let me look at this from the "what does the target source plausibly look like" angle. The original body was hand-tuned with asm levers; the real C may differ structurally. The target's code: the 5 loads are at off*4 + symbols; the stores are after. The h updates use a0. This looks like:

```
void func_8017F6B0(void *a0, s32 a1) {
    s32 sp10[5];
    s32 off = a1 * 20;
    u16 *h;
    sp10[0] = *(s32*)((char*)&D_801A5460 + off);
    ...
```
If we write the loads directly into sp10 (no temps), then the "temps" are the memory stores... The target has registers for the loaded values then stores them. gcc would load into a temp and store. The temp's live range: from load to store (live 5). Same.

Wait, maybe the real C uses a *local struct copy* or array assignment. Hmm.

Let me think about the t4 v1 requirement differently: target t4 = v1 = same reg as t0 (t0=v1). If t4 and t0 were the SAME pseudo (reuse a temp), then t4 would naturally be v1 (t0's reg). I.e., reuse `t0` for the fifth load:

```
    t0 = *(s32 *)((char *)&D_801A5470 + off);
    sp10[4] = t0;
```
But then the pseudo's live range spans from the first load to the fifth store: refs 4, live ~17 → pri 2*4/17 = 4705. That changes allocation order: t0 would be allocated before t1/t2/t3, taking a0 maybe. Hmm, but target has t0=v1 and t4=v1 — could be a coincidence or could be a single pseudo! Let's test: reuse t0 for the fifth load.

Actually wait: in the target, if t0's pseudo spans both loads, the value is overwritten; the register stays v1 throughout. The emitted code: lw v1 (t0), ... sw v1,16(sp), ..., lw v1 (5th), nop, sw v1,32(sp). Yes! That's consistent with a single pseudo in v1! And its live range would span from insn 24 to 59, refs 4, live ~17.

But hold on: would local-alloc give it v1? pri = 2*4/live. If live 17 → 4705 > 4000 → it'd be allocated before t1,t2,t3: it'd take... v0 is taken by r84 (12000), so v1. Yes! t0/t4 single pseudo → v1. 

And the t3 issue: with t0 spanning to the fifth store, the pseudo r74 has pri 4705. Then t1,t2,t3 (4000) get a0,a1,a2 in qty order → t3 still a2. Hmm, but target wants t3=a3 and a0-copy=a2.

Unless the t3 keepalive's effect is needed: extend t3's live range so its pri < a0-copy's. But with the real-C reuse of t0, maybe the t3 keepalive is not needed because... let me think: the a0 copy r72 (3703) vs t3 (4000). Still t3 first.

Hmm. So we need t3's priority lowered. In the target's actual RTL, t3's live length must be ≥6 (pri 3333) for the a0 copy to win a2. How?

What if t3's store is moved after the fifth load in the source, and the *single t0/t4 pseudo* changes the scheduling such that sched1 keeps the store after? Hmm.

Alternatively: maybe the source reuses t3 for the fifth load too? No, then t3 would be the one spanning.

Wait, maybe I should reconsider: in target, maybe t3 is NOT live 5. What if the target's t3 load/store are further apart in the pre-sched1 RTL? The live lengths we compare are from MY dumps; the target's source may produce different RTL.

Let me try the "reuse t0 for the fifth load" candidate and see the score.
