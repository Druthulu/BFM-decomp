---
ts: 2026-11-06T14:12:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_J0ICAFVZJgkIONSkuggw
---
Global allocno priority = floor_log2(n_refs)*n_refs / live_length. Higher priority gets allocated first (and thus gets the preferred hard reg).

I need i's priority > dst's. Without asm: i n_refs=11 (if 14-3), dst=11. i live_length long, dst short. So dst wins.

To fix: increase i's n_refs or decrease i's live_length or decrease dst's n_refs or increase dst's live_length.

Wait — increasing dst's live_length would LOWER dst's priority. Could I make dst live longer without changing code? Hmm, the live_length is computed by flow.c from actual liveness. Hard to change without code.

Increasing i's n_refs by real C: any real use of i in an RTL insn adds loop_depth refs. But we can't add instructions.

Hmm, BUT: what if I restructure so that a real use of i replaces a use that currently belongs to another pseudo, without changing the instruction count? For example, the address computation `dst = src + n` uses src and n. If instead `dst` were computed using i... e.g., `dst = src + i*2 + ...`? no.

Alternatively: what if the loop is rewritten to use i for the load/store addressing and drop src/dst pointers? That changes codegen.

Let me think about the actual numbers more carefully. Let me get the c1 ref counts and live lengths. I need the dump. Let me set up the scratch TU.

Actually, wait. Maybe there's a much simpler real-C crack: change the declaration of i from `s32` to something, or reorder declarations. The tie-break in global-alloc's qsort (allocno_compare) is by priority then... let me read lines 585-620.
