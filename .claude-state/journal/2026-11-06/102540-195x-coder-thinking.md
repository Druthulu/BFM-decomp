---
ts: 2026-11-06T17:25:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mDedR48nSp14NRc8SyY2
---
141 includers. orig scores 0 on includer 0. Now create nopin.c (drop the $2 pin) and score on includer 0.

The header body (166 lines) has one pin: `register s32 sh16 __asm__("$2");` and the uses:
```
            if (r[0x49] == 5) {
                sh16 = angle << 16;
            } else {
                if (func_8014CB7C() == 0) {
                    goto LAB_8015152c;
                }
                sh16 = p[0x79] << 16;
            }
            p[0x79] = (u16)(((sh16 >> 16) + (s32)((u32)sh16 >> 31)) >> 1);
```
The pin forces sh16 into $2 (v0). The use is a shift/arithmetic.

Lever-free: need sh16 in v0 naturally.

Let me score nopin.
