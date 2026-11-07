---
ts: 2026-11-06T03:16:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vY6ndzMybzFDJWPFITRH
---
q10/q11 use `d - 0x200 > 0` → addiu -512; blez. Same as q9. So the score 3 is from the different test form, and importantly the tails did NOT merge (113 ins!). So `d - 0x200 > 0` produces a different instruction (addiu/blez) which prevents the cross-jump, but the target wants slti/beqz.

Hmm! So a test form that produces `slti v0,v0,513; beqz` but is *different in RTL* from `d > 0x200`... 

What if one arm uses `d > 0x200` (slti 513; beqz) and the other uses `d - 0x200 > 0`? The latter gives addiu/blez. ✗

What if one arm uses `d > 0x200` and the other uses `0x200 < d`? Let me check: `0x200 < d` → slti 513? The front end canonicalizes `0x200 < d` to `d > 0x200` → same.

What about `d >= 0x201`? Same slti 513. And q variants with t2='d >= 0x201' gave 6 (merged). Hmm.

What about `(s32)d > 512`? Same.

Hmm, what about `d > 512` written with a hex vs decimal? Same.

So the only way to get slti 513 is `d > 512`-equivalent; all such forms canonicalize to the same RTL → merge.

Wait — q10 used t1='d >= 0x201'? Let me look at what q10 actually is. My generator: for outer in ['d >= 0','!(d < 0)','0 <= d'], for t1 in [...], for t2 in [...]. q9, q10, q11 are the 9th,10th,11th combos. Let me check q10's test expressions.
