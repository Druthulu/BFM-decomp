---
ts: 2026-11-06T16:38:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BIDpejApaXYLwzQ6b6on
---
In orig: 72 = param pseudo (a0), 73 = self = 72 + zr (plus). Then combine folds plus with $0 → move. So 73 is a genuine distinct pseudo. Global-alloc assigns 72 (conflicts with a0 → a1) and 73 (conflicts ... a0? "73 conflicts: 73 2 3 4 29" includes 4) → so 73 can't be a0 either? Hmm, then 73=a1 and 72=?? The dispositions said "73 in 5" and only 1 reg to allocate (73). So 72 was coalesced/deleted.

In win.c, 72→a1 and 73→a0 (2 regs to allocate).

Key difference: in orig, insn 11 is `73 = 72 + $0` (arithmetic), in win.c insn 11 is `73 = 72` (copy). Local-alloc's copy combination then merges 73 into 72 for some blocks, and global-alloc assigns differently.

So: to reproduce, we need `self` to be computed by a non-copy arithmetic op that folds to a move in combine but isn't a copy in cse/local-alloc. The `+ zr` with the $0 pin did that. Without a pin, what arithmetic expression is: (a) no extra instruction after combine, (b) not a plain copy.

Options: `self = arg0 | 0;` → RTL `ior 73,72,0`; combine folds to copy? combine runs BEFORE local-alloc? Pass order: cse1, jump, sched1, regclass, local_alloc, global_alloc, ... combine is after? Let me check toplev order: In gcc 2.7.2, combine runs after global_alloc? Actually combine is before sched2, after reload? No: combine runs after global_alloc (combine.c says it runs after register allocation? No — combine runs before reload but after global alloc? Hmm. Standard order in 2.7.2: ... cse, loop, cse2, flow, combine, sched, local-alloc? Let me check toplev.

From the earlier snippet at line ~3049: local_alloc. Let me find where combine is called relative.
