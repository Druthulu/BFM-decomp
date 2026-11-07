---
ts: 2026-11-06T20:29:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_o8KSFLtyNCZPHtj0C4sT
---
Right — nolau.c has the launder lines deleted, so the replacement string doesn't exist. Let me look at the current nolau arm text:

```
    if (((Unkstruct_800B5CB8 *)s0)->unkDC == 0) {
        register s32 q __asm__("$4") = s0;  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t8_tus2)
        s32 r = 0xFFF80000;
        ((Unkstruct_800B5CB8 *)s0)->unk2 = 7;
        func_8012B178(q, r);
        v = 0x20;
    } else {
```
So the replacement is `        s32 r = 0xFFF80000;\n        ((Unkstruct...` → `        s32 r;\n        r = 0xFFF80000;\n        ((Unkstruct...`.

Let me redo vG and vH.
