---
ts: 2026-11-06T11:33:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pIgKksrinFXT4imbxMMg
---
The baseline already scores 0? That means the current src def (with pins/barrier) matches. But we need a lever-free body scoring 0. Score of orig.c is 0 because it is the current src body. We need to remove the levers and still score 0.

Wait, dt.sh says score 0. Right, that's expected for the src body. Now build a lever-free candidate.

Let me look at the target. Function: get D_801151D4 struct, compute ratan2, minus 0x400, & 0xFFF, assign to tmp ($5 pin). Then launder. Then switch on bVar1 at p+0xA9.

Lever-free version:
```c
int func_80148AFC(void *a0) {
    s32 p = (s32)a0;
    s32 iVar5 = *(s32 *)(p + 0x20);
    s32 tmp = (ratan2(...) - 0x400) & 0xFFF;
    s32 sVar3;
    u8 bVar1;
    sVar3 = tmp;
    bVar1 = *(u8 *)(p + 0xA9);
    ...
}
```

The pins: $5 for tmp (so sVar3 = tmp copy keeps tmp in $5 while sVar3 elsewhere). $3 bb, $2 c80, $2 hi.

Hmm, the case 0x53/0x73 block: c80 = 0x80 in $2, hi in $2. This is a known pattern: comparing lo != 0x80 || (hi=bb>>8) != 0x80.

Let me first just strip the levers and see the score.
