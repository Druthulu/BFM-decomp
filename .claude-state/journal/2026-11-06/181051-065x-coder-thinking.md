---
ts: 2026-11-07T01:10:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rEmxXOWgnAondQ9v1qBR
---
Now I understand. The RTL (post-alloc, pre-reload):
- r72 (the s0 pseudo) → $16 ("72 in 16"), crosses 1 call.
- r74 (v0?) → $2 ("74 in 2").

Note "Register dispositions: 72 in 16, 74 in 2" — so r72 = $16 already.

insn 4: set $16 = $4 (a0) — the copy.
insn 26: set $4 = $16 (the call arg copy for func_80171990? No, this is before call 28 to func_8017EE68). Hmm, insn 26 is `set (reg 4 a0) (reg 16 s0)` — the argument setup for call func_8017EE68?? But the source calls func_8017EE68(a0) — the param a0, not s0!

Wait: `((void (*)(void *))func_8017EE68)(a0);` — the arg is a0 (the param). But the RTL shows `$4 = $16` (a0 = s0) before call 28. That's because the copy `s0 = a0` (insn 4) plus... hmm, no: the param a0 is copied to s0 (insn 4), and then for the call, a0 must be set to the arg value = a0 (the original param). But the original a0 was overwritten? No: insn 4 sets s0 = a0 (a0 unchanged). Then insn 26 sets a0 = s0 — a redundant copy (a0 already == s0)! That's gcc's "parameter copy" handling: the param pseudo is a0, and after the copy the value is in s0; the call needs the param value in a0, so it copies back.

Interesting: this back-copy `$4 = $16` is what enables the store substitution. In the target (pinned), the same RTL exists? The pinned body has `s0` = hard $16, so insn 4 is `set (reg 16) (reg 4)` — same. Then insn 26 `set (reg 4) (reg 16)`. Same.

So both bodies have this. The difference must be in a later pass.

Let me look at the final code again: mine has
```
jal func_8017EE68
move $16,$4       <- insn 4 moved into the delay slot
...
move $4,$16       <- insn 26 (the back-copy for call 2)
jal func_80171990
sw $2,516($4)
```
So the second store uses $4 — after the `move $4,$16`. A pass replaced $16 with $4 in the store.

In the target:
```
jal func_8017EE68
move $16,$4
...
move $4,$16
jal func_80171990
sw $2,516($16)
```
Hmm, is that right? The target's dump I inferred only from the one differing instruction: target[10] = sw v0,516(s0). So yes.

Which pass could replace $16 with $4? Let me check the .sched2 or .dbr dump. Since the store is in the delay slot, and dbr fills delay slots... Let me look at the pass dumps: e1.i.sched2 (post-reload sched) and e1.i.dbr.

Let me grep the .dbr dump for 516.

Actually, maybe it's the *delay slot filler* in reorg: it fills the jal's delay slot with the store, and when moving an insn, it might substitute? No.

Wait — maybe the substitution happened at the *source level*: the store's base is new_var, and new_var is a copy of s0. If cse folded new_var → the pseudo r72 ($16), the store would use $16.

But mine uses $4. So the store's base pseudo is NOT r72 — it's something in $4? But "Hard regs used: 2 4 16 31" and only 2 pseudos (72, 74). $4 is the param hard reg.

So the store's base was rewritten to $4 by a pass. Let me find which one by diffing the dumps. The .cse2 dump is post-reload cse? The order of dumps: .cse (cse1), .cse2 (cse2). cse2 runs after... In gcc 2.7.2, cse2 is run after reload? No — cse2 runs after the first cse, before loop. Hmm, the dump names: .i.cse, .i.cse2, .i.loop, .i.lreg, .i.greg, .i.sched, .i.sched2, .i.dbr.

The order in gcc: cse1, loop, cse2 (after loop), then sched1, local-alloc, global-alloc, reload, sched2, dbr, jump2.

So cse2 is before allocation. The store base rewrite to $4 must happen after allocation: in sched2 or dbr? Neither rewrites operands... unless it's the "flow" pass after reload? Or `reorg` (dbr) does copy propagation? Hmm.

Actually! gcc 2.7.2 has a post-reload pass `flow` (life analysis) and `jump2`, and `sched2`. But operand rewriting post-reload can happen in `reorg.c` (the delay-slot filler): when it moves an insn into a delay slot, it may use `reg_used_between_p`... no rewriting.

Hmm, wait. Maybe the store's RTL operand WAS $4 from the start (pre-reload), i.e., the store's base pseudo was r? Let me look at the .lreg RTL for the store. Let me grep the .lreg dump around 516.

Let me look at the .i.lreg dump for the store instructions.
