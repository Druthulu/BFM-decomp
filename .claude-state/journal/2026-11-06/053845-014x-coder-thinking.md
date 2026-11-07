---
ts: 2026-11-06T12:38:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_muD0z5sac03qV2m4Dq1W
---
Score 38 with all barriers gone. That's a big delta. Let me do them one at a time to see which barrier contributes what. Actually more efficient: remove one at a time and score.

But each try is ~ maybe 10-20 s. 4 tries = fine.

Actually, let me think about what barriers do:

Barrier 1: `dxv = rec->dx;` then barrier then `pxv = ...unk28;` — forces dxv load before pxv load. Without it, sched1 reorders.

Barrier 2: after `prim[7] |= ...` before `ua = ub = ...` — separates the store from the ua computation.

Barrier 3: inside else `ua = ub;` — the if/else tc branch: `if (tc) ua = ub - 0x100; else ua = ub;` — a barrier inside the else forces something.

Barrier 4: between `ott = ...` and `mFF = 0xFF000000;` — forces ott computation before li mFF.

Hmm, barrier 4 relates to the pins m24/mFF: the two `li a2,0xff00...`. Note the pin is `register u32 mFF __asm__("$6")` — so mFF is pinned to $6 = a2. In the diff, `lui a2,0xff00` moved. So the barrier keeps the mFF load in order.

Let me test each barrier separately.
