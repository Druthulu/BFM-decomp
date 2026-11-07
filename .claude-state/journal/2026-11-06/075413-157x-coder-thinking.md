---
ts: 2026-11-06T14:54:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO02x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0B7OChjF9HDWlr2xMezq
---
Line 3142: `jump_optimize (insns, 1, 1, 0)` — the second jump_optimize, post-reload. This is the jump2 pass. It's called after reload. So jump2 is the culprit.

Now, jump_optimize with the flags (1,1,0): let me check the signature. The first arg after insns is `insn`? Let me look at the signature.

Actually, the key: jump_optimize does value tracking? Let me look at how it folds `bne t,3` given t==5. Hmm.

Actually, maybe it's not a known-value fold at all. Let me look at the jump2 dump's case 5 region in MINE vs ORIG more carefully. In mine, after `bne t,5,L71`, there's an unconditional `jump`. In orig, there's the asm then `bne t,3,L73`. 

The unconditional jump in mine: maybe it's the `goto sel_094` from the C! Let me re-read the C:
```
if (t == 5) {
    if (t != 3) {
        goto sel_094;
    }
sel_054:
    ...
```
The `if (t != 3) goto sel_094;` — after `if (t == 5)`, the compiler knows t==5, so `t != 3` is true, so the goto is unconditional. But this fold could happen at the C level (front-end) or in jump.

Wait — the front-end doesn't know t==5 (it doesn't track conditions). So the RTL has `bne t,3,sel_094`. The first jump_optimize didn't fold it (both .jump dumps have 3 branches). The second jump_optimize folded it in c1.

Hmm, so jump2 does value tracking. Let me look at jump.c's `jump_optimize` for value tracking. Actually, maybe jump2 uses `reg_last_set`/`reg_last_set_value` (like cse) to know t==5? Let me search jump.c for "reg_last_set" or "equiv".

Actually, there's a simpler explanation: the second jump_optimize's `thread_jumps` follows the CFG: the `bne t,5,L71` jumps to L71 (after the block). The fall-through goes to the `bne t,3,L73`. thread_jumps might redirect... no.

Hmm, let me look at the jump2 dump for the `(insn_list 246)` and `(insn_list 256)` — these are the LOG_LINKS. The `bne t,5` has insn_list 256, and `bne t,3` has insn_list 260 (in orig). The LOG_LINKS connect to the comparison's operands.

Let me look at jump.c's value tracking. Actually, in gcc 2.7.2, `jump_optimize` has a section that uses `reg_last_set` and `reg_last_set_value` to simplify comparisons — it's the `find_insert_position` / "known value" code. Let me grep.

Actually, I recall gcc 2.7.2's jump.c has `jump_optimize` doing "if (x == c1) ... if (x == c2)" simplifications via `record_jump_equiv`? No, that's cse.

Hmm. Let me search jump.c for "last_set" or "known".
