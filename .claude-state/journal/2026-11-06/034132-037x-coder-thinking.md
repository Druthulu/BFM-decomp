---
ts: 2026-11-06T10:41:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UkiVBIPwOChDXSCRKF84
---
dw2 = 7, worse. Let me see the diff. Actually let me think differently: the issue is the store to 88 got sunk below. sched1's ordering. What if I keep the C source order but add a dependence so the store can't sink: make the unk58 store's value depend on the load? E.g., `unk58 = (s32)&D_801907C4;` — no.

Alternatively, make the *load/store of unkC4* depend on the unk58 store: e.g., compute t's store value using a variable that... no.

What about reordering the C: put `unk58 = &D_801907C4;` BEFORE `t = unkC4;`? Then the target order would be store, load, ori, sw. But target has load at 28 then store at 31 then ori. Hmm, target: load, lui/addiu, store, ori, store. The load is before the store. So C order load-then-store matches; sched1 sinks the store in mine.

Wait, why would sched1 sink the store below the ori/sw? Let me look at the full mine schedule. Mine (from the diff): position 31 is missing the sw; mine[34] has it. So mine:
```
28 lw v0,196
29 lui v1
30 addiu v1
31 ori v0,v0,2      (from target 32)
32 sw v0,196
33 li v1,16384?
34 sw v1,88
```
Hmm, actually where's `li v1,16384`? Let me dump the full listing. Let me use --keep and objdump to see the whole thing.

Actually, maybe simpler: the do-while block boundary is placed such that the store to 88 falls into the second block, and sched1 schedules the second block (ori/sw + li) and the store gets pushed after.

What if we wrap the load in do-while AND put the unk58 store before the do-while? i.e.:
```
unk58 = &D_801907C4;   // store first
do { t = unkC4; } while(0);
unkC4 = t|2;
```
Then the target order (load before store) would be wrong. No.

Alternatively, wrap the *unk58 store and the unkC4 RMW* in the do-while with the load outside? Hmm.

Let's think about what block structure gives the target. The target (with the barrier at the point before the load) has:
block A: ... unk5C = 0x8000;
[barrier]
block B: t = unkC4; unk58 = ...; unkC4 = t|2; unkC1 = 0; unkB4 = 0; ...

Within block B, sched1 schedules: load first (28), then the address for unk58 (29-30), store (31), then ori/sw (32-33), then li 16384 (34)... Wait, the target's `li v1,16384` at 35 then `sh v1,24(v0)` etc.

In mine with the do-while around just the load, the load is in block B and the store + RMW in block C. sched1 within block C: ori/sw then li then sw 88? It sank the store.

Hmm, what if I put the unk58 store BEFORE the do-while, i.e. block B: unk58 store; block C: t=load... no.

What if the do-while wraps the load AND the RMW, leaving the unk58 store between them? That's dw2 (score 7).

Let me look at dw2's diff to understand.
