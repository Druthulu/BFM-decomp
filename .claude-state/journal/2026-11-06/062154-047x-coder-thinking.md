---
ts: 2026-11-06T13:21:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_q4JAHul3EAKAakUe8JEo
---
Mine: addiu a1,sp,16 sits right before the jal (sunk to just before its use, filling the delay slot region). Target has it early (with addiu a0).

So the fix: keep the a1 setup in the earlier block. do-while around the s0 computation should do it.

Let me write variants. The relevant source block:

```
            s0 = rand();
            t = rand();
            aa = (s32)(q + 1);
            nn = (s32)buf;
            __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B t8_tus2)
            s0 &= 0x1F;
            s0 <<= 2;
            t = (t & 0x1F) - 0x50;
            s0 = s0 + t;
            d[2] = s0;
            func_80015978(aa, (s32 *)nn);
```

Variants:
1. do-while around `s0 &= ...` through `d[2] = s0;`
2. do-while around the four computation statements, store outside
3. do-while around `s0 &= 0x1F;` only
4. do-while around `nn = (s32)buf;` only (put nn in its own block!)
5. swap: put `aa` and `nn` after the s0 computation (target has them before — no)
6. `nn = (s32)&buf[0];`
7. `nn = (s32)(void *)buf;`
8. do-while around `s0 &= ...; s0 <<= 2;` only
9. do-while around `t = (t & 0x1F) - 0x50; s0 = s0 + t;`

Let me generate and score.
