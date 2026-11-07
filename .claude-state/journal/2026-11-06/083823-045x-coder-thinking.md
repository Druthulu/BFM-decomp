---
ts: 2026-11-06T15:38:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yMrCEKRJVXRGEBc1GPTu
---
Confirmed: only difference is the add folded into the constant.

So how to get gcc to materialize the base and add per use? 

The launder is an asm re-tie. The dead-reset didn't work because the sum is a *constant expression*, and cse's hash entry for the constant is not tied to a register variable... Actually wait: in c1, cse materialized the sum into s0. The dead-reset `mb = 0` after the first call should invalidate the hash entry? It didn't.

Hmm, what if the dead-reset is on a *named derived pointer*? Let's look at find_best_addr: cse keeps a named derived pointer as a register address. Maybe:

```
u8 *mb;
mb = (u8 *)&D_800AF630;
func_8004914C(mb + 0x18);
mb = (u8 *)&D_800AF630;   /* 2nd set */
func_800491AC(mb + 0x18);
```
tested (a) no.

Let me look at this from the cse source. cse.c:2656-2721 find_best_addr. Let me read that region to understand when cse keeps a register address vs folds constant.
