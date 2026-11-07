---
ts: 2026-11-06T08:03:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_c28MvIG8isnAX3d03hcY
---
Item3: keepalive `__asm__("" :: "r"(m), "r"(ang));` on m and ang. The body:
```
s32 s2 = obj->unk4C;
s32 s3 = obj->unk20;
if (s2 == 0) return;
func_80015954((s32)D_800CC290, obj + 4);
v = obj->unk60;
m = v & 0x1F;
ang = ((m << 8) & 0x7F00) >> 1;
t = obj->unkA;
__asm__("" :: "r"(m), "r"(ang));  // keepalive m, ang
obj->unkA = t - 0x10;
obj->unk60 = v + 1;
if (obj->unk50 == 0) { r = func_80047948(m << 7); } else { r = 0x1000 - func_80047948(m << 7); }
d[0] = r / 1024;
d[1] = func_8004787C(ang) / 512;
...
```
The keepalive keeps m and ang live across the stores (obj->unkA, obj->unk60) before their use in the if. Actually m is used in func_80047948(m<<7), ang in func_8004787C(ang). The keepalive is right after `t = obj->unkA;` and before the stores. Without it, the compiler might recompute or reorder.

Let me score orig (0) and w1 (remove keepalive).
