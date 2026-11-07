---
ts: 2026-11-06T16:43:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nxHHu6gAf5PHOk0K60JZ
---
t3_e4 scores 0 — MATCH! e4 is:
```
        s32 q;
        s32 g;
        q = *(u16 *)(((Unkstruct_8017EAD8_2 *)arg0)->unk20 + 0x18);
        g = ((Unkstruct_8017EAD8_2 *)arg0)->unkDC;
        g |= 0x80;
        ((Unkstruct_8017EAD8_2 *)arg0)->unkDC = g;
        ((Unkstruct_8017EAD8_2 *)arg0)->unk104 = q;
```
Combined with t3 (split p into t/v) and the no-self head.

Wait, but t3_e4.c was generated as t3 then-arm + e4 else-arm. Let me verify it's the file I think: in the loop, I generated t3.c for each e then copied it to t3_$e.c. But the generation writes ALL t1..t7 with the given else; t3.c gets overwritten each time, and I copy it. So t3_e4.c = HEAD + t3 + ELSE[e4]. Yes.

Let me confirm the final file and re-score with dt, then check the assembly matches the target, and verify no lever lines remain (grep for asm/register).

Also verify the result against the item's `kinds` = pin: the body must have no pins. Our win.c has no `__asm__`, no `register`. Good.

But: is the body "lever-free" of the pin kind? Yes.

Now, the resulting body uses `arg0` directly and a local `t`/`v` split. Let me look at the full t3_e4.c.
