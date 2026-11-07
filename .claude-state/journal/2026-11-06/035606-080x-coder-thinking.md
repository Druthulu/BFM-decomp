---
ts: 2026-11-06T10:56:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jhHP3nwMVYrmANVnVbQB
---
Now item 2: func_80189F7C. Its orig has the `s32 v1; v1 = 0x4000;` structure. Let me first score the same best candidates adapted to it. The item dir is .run/P40/T11/G28x/func_80189F7C__ov_SC03_028_jr_801887A8.

Its orig.c I extracted earlier. Let me generate the equivalent variants: parameter-direct (a0), pins/barrier removed, plus do-while variants.

Let me write a generator for this item too, but first check the orig.

Actually the twin's C is nearly identical except: v1 = 0x4000 used for the three 0x4000 stores, different globals (D_801908C4, D_801908D0, D_8019095C), and func_8012A828 cast.

Let me create the parameter-direct base and score it, then try the do-while variants.

Time budget for item 2: start now (~04:07), 20-30 min.

Let me build the base with sed similar to before, plus the v1 variable handling. The orig has:
```
        register s32 t __asm__("$2");
        s32 v1;
...
        __asm__("" ::: "memory");
        v1 = 0x4000;
        t = ((Unkstruct*)s0)->unkC4;
```
So the barrier is before v1 = 0x4000.

Let me create the lever-free base: remove pins (s0 and t), use a0 directly, remove the barrier. Keep v1 = 0x4000.

Then score. Then apply do-while variants.

Let me do it.
