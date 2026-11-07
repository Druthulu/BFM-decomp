---
ts: 2026-11-06T14:50:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2QNFev5OsqxIKUAAhxLG
---
Still the same. So the two-predecessor design didn't change the output (the compiler optimized it back).

Let me look at v13's asm to see if it changed at all. The diff is identical to c1, so no.

Hmm. Let me reconsider. Maybe the fold is NOT cse but the front-end or jump. Let me check the .cse2 dump of c1 vs orig for the branch count.

Actually, let me look at the .rtl dump (pre-cse) for c1's case 5. If the .rtl already has only 2 branches (folded), then the front-end did it (impossible for condition tracking) or jump.c (before cse). Let me check.

The .rtl dump is after expand and jump_optimize? Let me check the dump order in toplev.c. The .rtl dump is probably after expand (before jump). Let me find the case 5 region in c1's .rtl.

The case 5 code: `t = (s16)a1; if (t == 0) ...; if (t == 3) ...; if (t == 5) ...`. In the RTL, the comparisons are `(eq (reg t) (const 0))`, `(eq (reg t) (const 3))`, `(eq (reg t) (const 5))`.

Let me grep the c1 .rtl for `(const_int 3)` and `(const_int 5)` in if_then_else.

Hmm, let me just count `jump_insn` in the function across .rtl, .cse, .cse2, .jump2. If the count drops from .rtl to .cse, cse folded.

Let me do that.
