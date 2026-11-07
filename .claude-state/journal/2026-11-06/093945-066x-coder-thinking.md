---
ts: 2026-11-06T16:39:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MFmD4pSVbEupQbfXX33O
---
C0535: do{}while(0) splits cse1's EBB (it emits a NOTE_INSN_BLOCK boundary? Actually a do-while creates a block). This could prevent local-alloc copy combining across the block. If I wrap the copy `self = arg0;` in `do { self = arg0; } while (0);`, the copy might stay in its own block, preventing combination with the param and forcing a separate register. Hmm, actually the do-while creates a block that cse treats as an EBB boundary. local-alloc works per basic block; a do-while(0) does NOT create a basic block (no branch in RTL after optimization) but it does create NOTE_INSN_BLOCK_BEG/END which cse uses.

The target's structure: the copy `move a1,a0` and then the entry stores. Maybe wrapping the copy could change allocation.

Let me try variants quickly with sc.sh:
1. do-while around `self = arg0;`
2. do-while around the flag load.
3. pointer self + do-while copy.

Also try C0414 (dead-reset cse-breaker): read it.
