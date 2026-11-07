---
ts: 2026-11-06T16:32:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_sD3lDQc5C05iRBqn4hl1
---
The .i preserves the body exactly (no macro expansion). So splicing is easy.

Write a dump script that:
- takes a body file, splices into a copy of t.i (replace lines 45283-45315 region by locating the function start and brace matching).
- runs cc1 with dumps.

Let me write dump.sh + splice.py under the item dir. Then inspect .lreg/.greg dumps for candidate c1 (pointer self) to see why else uses a0.

Actually, since the pinned body's .i is already at hand, I can splice any body.

Let me write splice.py: read t.i, find line starting with "void func_8017EAD8(arg0)", find the end by brace counting from the first '{' line, replace with body file content (which includes the full definition). Then write t2.i.

Then run cc1: (cd dir && tools/bin/gcc-2.7.2-psx/cc1 -quiet -O2 ... -dL (local alloc dump?) flags. The cc1_dumps_tu.sh uses -dr -ds -dj -dl -dg -df -dc -dS -dL -dR -dt -dJ -dd. -dL? Let me check gcc 2.7.2 flags: -dL = local-alloc dump? In 2.7.2: -dl = local-alloc? Hmm. Actually gcc 2.7.2 dump flags: -dL (local_alloc), -dG (global_alloc), -dR (sched2/reorg?), -dS (sched), -dt (cse2?). Let me check toplev.c flag handling.
