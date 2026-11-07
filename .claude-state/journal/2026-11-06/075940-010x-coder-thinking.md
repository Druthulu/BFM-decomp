---
ts: 2026-11-06T14:59:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_KRaF4k7THWN98eQOz0p6
---
Now I understand. All 5 are clones of this same function from ov_SC02_026 — "MATCH (237 ins)". They have a launder: `__asm__("" : "=r"(vol) : "0"(vol));` — the lever 3 zero-byte re-tie. The task: replace it with a real C move so that the sched1 doesn't hoist the PAN multiply.

Wait — the launder here is the re-tie. There's also a pin `register void *r4 __asm__("$4")` and `register s32 av __asm__("$5")`. Those pins are "under other causes" — kinds is only "launder", so pins are non-row kinds and may stay. Good.

So I need to replace `__asm__("" : "=r"(vol) : "0"(vol));` with real C that keeps the schedule the same. From the moves: 
- func_8018AA98: MATCH: `pv &= 0xFF000000` (compound assign) = a REAL 2nd SET of the pinned pv, kills the sched1 birth boost of the pv load; plain `pv = pv & mask` (a new temp) does NOT.
- func_80181BA8: out-only launder -> real 2nd set `pv = *p; pv &= 0xFF000000; *p = pv | ...`

So the mechanism: the launder makes vol multi-set (2nd set), killing the sched1 birth boost so that the PAN multiply isn't hoisted above. Let me think: `vol = ((0xA0 - av) * 0x7F) / 0xA0;` then launder re-tie then `sx = (sx+0xA0)/0x14;`. The launder is a use+set of vol. To replace with real C: a second set of vol. E.g. `vol = vol & 0xFFFF;` — but that changes semantics? vol is passed as `(vol | (0x3000 | sx)) & 0xFFFF`, so masking vol with 0xFFFF is semantically... vol = ((0xA0 - av)*0x7F)/0xA0 where av <= 0xA0, so vol is in [0, 0x7F] — mask is a no-op semantically. But would combine/fold remove it? `vol &= 0xFFFF` on a signed int... hmm, the value is already < 0x80, but compiler doesn't know. Actually `vol & 0xFFFF` would generate an andi unless combine proves range. It's a real 2nd set.

But wait: does a real second set of vol change the instruction count? The launder is zero-byte. A `vol &= 0xFFFF` would generate an `andi` unless combine eliminates it. Hmm, the moves mention "real 2nd set `pv = *p; pv &= 0xFF000000; *p = pv | ...`" — there the second set is part of the real computation (mask needed). Here we need a zero-byte real 2nd set.

Alternative: the cookbook C0414 "dead-reset cse-breaker" — from moves: func_80180D54 MATCH: the dead-reset `p1 = 0;` between the two calls invalidates cse's equivalence. So a dead reset `vol = 0;` then `vol = ...`? Hmm, a dead store would be deleted by flow unless it's a 2nd set that stays... Actually a dead reset sets a variable to 0 and later it's overwritten — flow would delete it. But the moves say it works. Hmm, in func_80180D54 it's `p1 = 0;` between two calls — the value is used? Let's look at C0414.

Actually, the key is to kill the sched1 birth boost of the vol computation. sched1 boosts insns that birth a value... The launder re-tie gives vol a second set at the launder point, so the multiply's result is not the "birth" of vol's live range? Hmm.

Let me read cookbook C0414 and C0535, and maybe C0505.
