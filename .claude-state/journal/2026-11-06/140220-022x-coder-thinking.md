---
ts: 2026-11-06T21:02:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oibPC2cSH2diUszhuXzw
---
--keep keeps the per-call scratch and prints the candidate object path. That lets me get the candidate TU and object. Let me run with --keep on win.c.

Actually, a simpler path: I need the local-alloc/global-alloc dump for the candidate. With --keep, I get the scratch TU path; then run cc1_dumps_tu.sh on it. But the scratch TU may be a spliced TU. Let me try.

Actually, let me first think about whether I even need the dump. Score 4 with only 5 instruction diffs, all a0/a1. This is a classic register-pair swap. Let me try more real-C moves that could shift local-alloc priority.

Priority = floor_log2(n_refs) * n_refs * size / live_length.

For off: n_refs? In RTL before allocation, off is a pseudo defined by sll and used twice (addu at, addu v0) → maybe n_refs=3 (1 def + 2 uses)? Actually reg_n_refs counts uses, and defs? Let me check: `reg_n_refs` incremented per use and per set? In flow, reg_n_refs is number of references. So off: def(sll) + use(addu at) + use(addu v0) = 3 refs. e: def(lui/addiu = 1 ref?) + use(addu v0) = 2 refs. Hmm.

live_length: off born at sll, dies at last use; e born at addiu, dies at use. 

Priority off = floor_log2(3)*3*size/live_off = 1*3*4/live_off.
Priority e = 1*2*4/live_e.
If live_off ~ live_e, off has higher priority → gets first pick. Target gives off a1, so off picked a1, not a0. Interesting! So maybe the allocator's first pick for this qty is a1, not a0, due to qty's preferred register or allocation order of hard regs.

In local-alloc, the allocation iterates over qty_order (sorted by priority) and for each qty finds a free hard reg starting from... let me look at the alloc loop. Let me read local-alloc.c around line 1500-1700.

Actually wait — maybe the difference isn't priority but a *preference*: local-alloc assigns a hard reg that a qty is tied to (via REG_DEAD notes / copies). The sll result off might be preferred a1 because... hmm.

Let me just read the allocation code.
