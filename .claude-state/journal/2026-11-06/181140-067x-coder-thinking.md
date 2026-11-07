---
ts: 2026-11-07T01:11:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8pcMaQrdmFjFHfkmU5Rj
---
At cse and cse2, the RTL is:
```
insn 4:  r72 = a0
insn 26: a0 = r72        (call 1 arg)
call 28
insn 37: mem[r72+512] = v0
insn 43: mem[r72+516] = v0    <- base r72
insn 46: a0 = r72             <- call 2 arg
call 48
```
So at cse2 the store's base is r72 (the pseudo). Good.

But at .lreg (after sched1, local/global alloc), insn 43's base is `(reg:SI 4 a0)` and the order changed: insn 46 (a0 = r72) comes BEFORE insn 43.

So sched1 reordered insn 46 before insn 43, and then... who rewrote the base to a0? sched1 doesn't rewrite operands.

Wait — maybe it's the *local-alloc* or *global-alloc* pass: after allocation, `reg_renumber` maps r72 → 16, but the RTL shows `(reg:SI 4 a0)` for the store's base — a hard reg 4. A pass that rewrote a pseudo use to a hard reg = `reg_renumber` substitution? No, that would make it `(reg/v:SI 72)` still (dumps show pseudos as pseudos, or renumbered?).

Hmm, the .lreg dump shows insn 4 as `(set (reg/v:SI 16 s0) (reg:SI 4 a0))` in the greg dump but `(reg/v:SI 72)` in .lreg? Let me look again at the lreg output I printed: insn 4 was `(set (reg/v:SI 16 s0) (reg:SI 4 a0))`? No — in my earlier sed of .lreg I saw:

"(insn 26 19 28 (set (reg:SI 4 a0) (reg/v:SI 72)) 159 ...)"

So .lreg still shows r72 as a pseudo. But insn 43's base shows `(reg:SI 4 a0)` — a hard reg! So some pass rewrote r72 → a0 in insn 43 specifically.

Which pass? Between cse2 and lreg: loop, sched1, local-alloc, global-alloc. Hmm, could be "loop" (loop optimization) or sched1's dependency analysis? No.

Wait — maybe it's `combine` (-dc? the dump .combine). The combine pass runs after cse1? In gcc 2.7.2: cse1, loop, cse2, then combine? Let me check the dump order: e1.i.combine exists. Actually the standard order: cse, loop, cse2, ... combine? Let me check the actual .combine dump for the store.

Let me grep .combine for 516.
