---
ts: 2026-11-06T08:38:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tL2nSm0ZQKFW8OHbVWex
---
r72 = a0 param copy (live 27). r77 = used 2 times across 5 insns: that's a load pseudo (t?); which one? t0..t3 are used twice (load then store), t4 too. All have refs 2 live 5 except some. Wait 75,76,77 each 2/5. Hmm. Actually loads: r75,r76,r77,...? Let's read more of the dump to map.

Actually the interesting registers: 75,76,77 have pri 4000 and got a0,a1,a2. r74 (v1) 2/10 is `off` (used 5 times? no, off used in 5 address computations... it's used 5 times, so r72? hmm).

Wait r72 used 5 times = a0 copy used 5 times? The a0 copy is used in 3 lhu's + move a1,a3 = 4 times. Hmm, maybe a0 copy used 5 times (h[0],h[1],h[2] uses = 3, plus func call arg = 1, = 4). Or the a0 param is used... Let me look at the actual insns. Let me read further.

But stepping back: the practical approach is search over real-C variations. The key numbers: r72 pri 3703 vs r77 pri 4000 in w1; need to flip so that r72 > r77 (or reduce r77's priority below r72).

Real C options to lower t3's (or whichever) priority: t3's live length is 5. Extend it to 6+ by moving its store after t4's load in source. Then live = 6? pri = 2*2/6 = 3333 < 3703 → r72 wins a2. Let's try reordering:

```
    t4 = *(s32 *)((char *)&D_801A5470 + off);
    sp10[0] = t0;
    sp10[1] = t1;
    sp10[2] = t2;
    sp10[3] = t3;
    sp10[4] = t4;
```
Hmm that changes live ranges of all: t0,t1,t2 extend to the stores. But target order: loads t0,t1,t2,t3 then stores t0..t3 then load t4. If source order loads t0..t4 then stores, sched1 may reorder to target.

Alternative minimal: just move `sp10[3] = t3;` after the t4 load:
```
    t0=...; t1=...; t2=...; t3=...;
    sp10[0]=t0; sp10[1]=t1; sp10[2]=t2;
    t4 = ...;
    sp10[3]=t3;
    sp10[4]=t4;
```
t3 live extends across t4 load → live 6 maybe. And instruction order may change: target has sw t3 before lw t4. Hmm, then the emitted order might differ. But sched1 can reorder the store before the load (store after load in source, scheduler may move). Risky but try.

Another approach: shorten a0-copy's live range? Can't.

Or raise a0-copy's refs: use `a0` (or its copy) one more time in a real expression without extra insns? Any extra use adds an insn unless folded. Hmm: currently `h[0] = h[0] + ((Unkstruct_800B5CB8 *)a0)->unk6;` and h[1] uses CAST_ALIAS(a0,0xA) and h[2] unkE. Each uses the a0 copy. If we instead write the pointer arithmetic via a temp: e.g., `p = (Unkstruct_800B5CB8 *)a0;` and use p... that's the same pseudo.

Hmm, what about `off`'s role: in w2, off keepalive gives a0-copy pri 3333 and t3-like pri 1666, and a0 copy wins. So extending off's live range lowered both but t3's much more (live 5→18?). Wait, the off keepalive shouldn't affect t3's live range at all. Unless the pseudo r77 in w2 is a different variable. Let me identify pseudos by reading the lreg dump sections. Let me read w1 lreg 23786-23920 fully.
