---
ts: 2026-11-06T15:44:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HBlNsHFyjcorVdX3PRei
---
This function has multiple launders:
- case 6: two `_m = (s32)&D_801C8344; asm` (lines 3036, 3051), and a third one at 3064 without asm (line 3064-3065 has no launder).
- case 7: 3101 (no launder, `_m = 0;` dead reset!), 3116 (launder), 3128 (no launder).
- case 7 tail: 3156 (launder m=&D_801C836C), 3158 (launder _v=(s32)v18).
- post-switch: 3244, 3258 (launders), 3270 (no launder).

So the launders here are on `_m` (the address of D_801C8344, the light matrix) and on RotTransSV args.

Note line 3101-3103: 
```
{ s32 _m = (s32)&D_801C8344;
  ((void (*)(s32, s32, s32))func_8012F14C)(..., _m, ...);
  _m = 0; }
```
This is already the C0414 dead-reset! So the pattern for the launders is likely the same: `_m = 0;` after the call.

And line 3154-3159:
```
{ void *m = &D_801C836C;
  s32 _v;
  asm("" : "=r"(m) : "0"(m));
  _v = (s32)v18;
  asm("" : "=r"(_v) : "0"(_v));
  RotTransSV(m, (void *)_v, &flag); }
```
Here the launders are on m and _v. These need different treatment.

Let me first check the baseline: extract the function (2948-... end). Let me find the end line. The function continues; let me read to its end.
