---
ts: 2026-11-06T20:03:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WzqzxdbgwuZdANKcxgGk
---
Now, strip the pin. Remove `register s32 v0 __asm__("$2");` and rename v0 to a normal var. Let's see: `v0` used as: v0 = func_8012C588(...); *p = v0; ... v0 = *(u16*)(...); ... v0 = *p; ... `((Unkstruct_800B5CB8 *)*(s32 *)(v0 + 0x20))->unk12 = ...`

Careful: v0 is used as both call result and loaded value. Just declare `s32 v0;` (no register, no asm). Let's make baseline nopin.c and score.

Actually, is `register s32 v0 __asm__("$2")` the only lever? kinds = pin. Yes. Remove register+asm → plain `s32 v0;`.

Let me create nopin.c and score.
