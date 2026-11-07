---
ts: 2026-11-06T15:43:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_srnUGvVRq1bIN6T04QMl
---
vca scores 0! MATCH. The C0414 dead-reset applied to the *derived* pointer (the sum), not the base. That's the crack.

vca:
```
mb = (u8 *)&D_800AF630;
mb2 = mb + 0x18;
func_8004914C(mb2);
mb2 = 0;
func_800491AC(mb + 0x18);
```

Score 0, 397 ins. And it's real C: a named derived pointer + dead reset. No asm/pin.

Let me verify no asm in vca, save win.c, check that all three sites got the replacement (yes, src.replace replaced all 3).

Wait — the third site: after the replacement, each site has its own mb2 = mb + 0x18. Good.

Let me double-check the grep and copy to win.c.
