---
ts: 2026-11-07T01:01:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ubP5Jfe6nSt8BKBWTGd4
---
To dump a header TU I'd need a spliced TU file. The header's first includer TU is src/ov_MAIN_012/ov_MAIN_012_jr_80171B4C.c which has `#include "..."`. cc1_dumps_tu.sh accepts a .c file. But the current src TU includes the header with the pinned body. To get the *lever-free* body's priorities, I'd need to splice my body in — that's what the --try scratch does. I could use `--try ... --keep` to get the candidate object, but dumps need the source.

Alternative: copy the includer TU to my item dir, replace the `#include` line with my body text, and dump that. That's exactly the T10 "inline instrument" approach. It costs ~1 min.

Is it worth it? The evidence field needs gcc pass + mechanism. I have the diff (primary evidence from this session) showing mine p=$s0 vs target p=$s3. The mechanism (allocno priority) is supported by the gcc source I read this session (allocno_compare formula at global.c:587). I can state: "global-alloc allocno_compare (global.c:587): p refs 11/live 29 pri 11379 > b 3/9 3333 → p=$s0; target p=$s3 only via the $16-$18 pins". The refs/live numbers are from the prior notes; but I could compute them from the dump.

Given the 20-min requirement, spending 2-3 min on a dump is fine and strengthens the evidence. Let me do it: create the spliced TU.

Actually, hmm: a simpler ground truth — the .lreg dump gives "Register N used R times across L insns" for each pseudo. I can splice the body into a copy of the includer TU.

Let me look at the includer TU to see how the header is included.
