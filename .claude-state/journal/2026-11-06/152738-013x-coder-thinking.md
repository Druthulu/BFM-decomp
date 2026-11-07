---
ts: 2026-11-06T22:27:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ywj13tLwSbtU0bsH6hfl
---
So mine: d -> $s1, s1ang -> $s0, and iVar4 -> $a1 vs target $v1. Wait: target `sra s0,s0,0x10` is the cast d=(s16)d, so target d=$s0. Mine `sra s1,v0,0x10` — d=$s1, and arg1 was copied to v0? Hmm, mine: `sra s1,v0,0x10`, meaning d = (s16)(arg1 in v0). Target: `sra s0,s0,0x10` — arg1 already in s0? Actually the pin version had d in $16 pinned, so `move s0,a1` maybe.

Mine: s1ang = $s0 (`subu v1,a0,s1` uses s1 for s1ang? wait target `subu v1,a0,s1` uses a0 and s1; a0 = ... hmm).

Let me be careful. Target:
- `sra s0,s0,0x10` → d in s0
- `subu v1,a0,s1` → a0 holds u5-ish? Hmm, u5 = (ratan2(...) - 0x400) & 0xFFF. Then `u6 = s1ang & 0xFFF`; `iVar4 = u5 - u6`. So `subu v1,a0,s1`: v1 = iVar4, a0 = u5, s1 = u6 (s1ang). So s1ang=$s1, u5=$a0, iVar4=$v1.
- Mine: `subu a1,v1,s0`: a1 = iVar4, v1 = u5, s0 = s1ang. So u5=$v1, s1ang=$s0.

Interesting. In the pinned/target version, u5 is in $a0 (arg0 reg? no, arg0 is used early for loads). Anyway.

So the register assignment difference: mine d=$s1, s1ang=$s0, u5=$v1, iVar4=$a1. Target d=$s0, s1ang=$s1, u5=$a0, iVar4=$v1.

Hmm, this is more than just d/s1ang swap: u5 also differs ($v1 vs $a0) and iVar4 ($a1 vs $v1). That's because global-alloc priority ordering among the .greg set.

The target: u5 in $a0. Since $a0 is caller-saved and arg0 is dead after the loads... u5's live range starts at the ratan2 result. Hmm.

Actually, let's think about it differently: with the pin, d occupies $s0 from the start, so $s0 is taken; s1ang gets $s1. u5 gets $a0? That's because ratan2 returns in $v0, then `-0x400 & 0xFFF`... the result copy goes to a caller-saved reg.

Without pin: d is not hard-reserved at entry, so allocation order changes: s1ang gets $s0 (local-alloc? since s1ang is block-local? No, s1ang is used across the function — it's global). Hmm.

Key: the target has d in $s0. In the pinned version d is pinned from entry, so `move s0,a1` at entry presumably (or the arg copy coalesced into s0).

For a lever-free MATCH, we need global-alloc to pick d → $s0 and s1ang → $s1.

Global-alloc assigns in priority order (global.c: allocno priority). Let me dump the alloc table for w0 and for prev_win (pin kept) to see priorities and the order.

Let me run hdump.sh. It needs an includer TU. tryinc.py rotates includers; dt.sh uses the default order (first includer). For hdump, the TU must be a real file path containing `#include "../shared/ov/func_8012B8E4.h"`. Which includer TU does dt.sh use? delever_search recs_for gives includer recipes. Let me find one TU file. Let me look at delever_search quickly or find a file that includes this header.
