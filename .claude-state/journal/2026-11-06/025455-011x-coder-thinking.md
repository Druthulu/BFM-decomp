---
ts: 2026-11-06T09:54:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hhOEySjRRRTvmWZA480w
---
Now let's write a lever-free candidate. The function is void, and target has 26 instructions. Let me see what the target assembly looks like. Let me find the baseline object in build/ for this TU. Actually easier: use --keep to get candidate object, or use --explain. Let me try --explain on the function to see residual. But baseline is score 0, so no residual.

I want the target's disassembly. Let me find build/ object. Let me check what `build/` contains for this TU. Use tools/cc1_dumps_tu.sh? Simpler: run dt.sh with --keep to get candidate object and objdump? Actually candidate = same bytes as target, so disassembling the candidate object with --keep gives target instructions. Let's do that.

Actually, I can just check the diff of a lever-free candidate to see what's missing. Let me write a first candidate without pin/keepalive: declare `s32 rv;` and use it. Since it's a void function, the stores to rv are dead → eliminated. Let's see what score comes out.

But wait, we can't change signature, but maybe we can make the assignments side-effectful in real C? E.g., use a volatile local? `volatile` is a lever? Not in the kinds list (pin, launder, barrier, keepalive). Hmm, but "no new lever of any kind" — volatile would be a new lever. The kinds tracked are probably keepalive, pin, launder, barrier. A volatile qualifier might count as "barrier" kind? Let's check the kinds definitions in lever_census.py.

Let me grep.
