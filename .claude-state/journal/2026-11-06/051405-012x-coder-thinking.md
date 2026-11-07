---
ts: 2026-11-06T12:14:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IiOCPMRHVXP9KHw9fPBS
---
Many useful moves. Let me look at the tail of moves.md (lines 280+) — it seems the file is ordered chronologically and includes more recent shards. Let me see the last ~40 lines to see recent techniques. Also walls.txt.

Actually, first let me get the baseline: stripped body score and diff. That's most informative.

Let me write a first candidate a1.c: same as orig but:
- remove register pins (pos, a1v), use plain s32 pos = arg2; and replace a1v uses with arg1? But then the launder's purpose (make a separate pseudo for arg1) is gone. Let's try `s32 a1v = arg1;` declared and assigned in declaration order matching.

Actually maybe simpler: try the most natural lever-free rewrite: 
```
s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {
    extern ...
    u16 *ac; s16 *b8; s16 *b4; s32 r;
    s32 pos; s32 a1v;
    ...
    a1v = arg1;
    pos = arg2;
```
Hmm but a1v = arg1 will be coalesced by gcc (copy propagation) into arg1. Then arg1 is used for the &1 test etc.

Alternatively, use arg1 directly and drop a1v, keep pos = arg2.

Let's test both quickly with sc.sh. Need to write files. Let me write a1.c (natural: no a1v, no pos variable, use arg2 where pos used) and a2.c (a1v=arg1, pos=arg2 as temps).

Actually wait — pos is `s32` and assigned arg2; used as pos+2, pos-2. If we replace pos with arg2 directly, arg2 is used in two branches. Fine.

Let me create these with a Python generator or just write files with Write tool. I'll use Write for each candidate.

First candidate a1.c — minimal de-lever of orig:

```c
s32 func_80136824(s32 arg0, s32 arg1, s32 arg2) {
    extern u8 D_801152A8[];
    extern s16 D_801152AA;
    extern s16 D_801152AC;
    extern s16 D_80126722;
    extern s16 D_80126724;

    u16 *ac;
    s16 *b8;
    s16 *b4;
    s32 r;
    s16 temp_v0;
    s16 temp_v1;
    s32 var_a3;
    s16 var_v0_3;
    s32 temp_a1;
    s32 var_t0;
    s32 var_v1;
    s16 *b4b;
    u16 *p;

    if (!(arg1 & 1)) {
        var_t0 = (s16) arg2 - (*(s16 **)&D_801909BC)[1];
        var_v1 = var_t0;
        var_a3 = -(*(s16 **)&D_801909C8)[1];
    } else {
        var_a3 = (*(s16 **)&D_801909C8)[1];
        var_v1 = (*(s16 **)&D_801909BC)[1] - (s16) arg2;
        var_t0 = -var_v1;
    }
    ...
```
with barriers removed and var_v0_3 = arg2 + 2 / arg2 - 2.

Hmm but the barrier in each branch likely prevents the store/`var_v0_3` computation from being scheduled before the D_801152AA store. We'll see the diff.

Let me write a1.c.
