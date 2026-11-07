---
ts: 2026-11-06T12:54:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SvOQTCo7R527Xj03aQNN
---
`birthing_insn_p` — an insn that births a register (sets a pseudo/reg). adjust_priority: for a predecessor with 0 REG_DEAD notes that is a birthing insn, its priority is raised to max_priority. So birthing insns get scheduled early (hoisted).

The lui/ori: the lui sets v1 (a birthing insn? `birthing_insn_p` checks if the pattern sets a register that is not dead...). The sh doesn't set a register. So the lui/ori get the birth boost, the sh doesn't → the lui/ori hoist above the sh. That's the `sched1-birth-boost` wall tag.

In the target, the barrier splits the block so the boost can't cross it.

Can real C change which insn is "birthing"? The sh is a store; never birthing. So the constant pair will always be boosted above it within the same block. That suggests a WALL for the barrier-free body... unless we split the block by some other means.

What splits a basic block for sched1 (which runs per basic block, not EBB)? In sched.c, `schedule_region`/`sched_analyze` is called per basic block: `schedule_block` is called from `schedule_insns` for each basic block (BASIC_BLOCK vector). A basic block ends at a jump/label. In our join block, no labels in the middle.

Can we introduce a label in the middle with plain C? A `goto` to a label, or a `do{}while(0)` (which creates a label for `break`). C0535 says do-while splits cse1's EBB. For *sched*, a do{}while(0) becomes a jump to a label... but gcc's jump optimization removes it before sched? The order: cse1, loop, cse2, jump_optimize (jump.c), sched1... Actually sched1 runs after jump_optimize? The pass order in toplev.c: ... jump_optimize (1), cse (2)... Let me not guess.

Empirically, item 1's do-while DID change the schedule. So a do-while can affect sched1. Why didn't it here? Because in item 1 the do-while wrapped the store whose delay slot was filled. Here I wrapped various statements and got different scores (4, 6) but not better.

Hmm, d_Y (do-while around the y store) = 2, unchanged. So the do-while there was optimized away completely before sched? Possibly because it contains a single statement with no branch.

Wait, in item 1, the do-while around `sp10[4] = t` (a single store) DID change the output. Hmm.

Actually in item 1, the do-while kept the store from being moved into the load delay slot. Maybe the mechanism is different: do{}while(0) creates a LOOP note (NOTE_INSN_LOOP_BEG/END). loop.c sees a "loop" of one basic block; it can't do anything. But the loop note affects... `loop_depth` for ref weights? That's flow. Hmm.

Let me try: in this item, wrap the *y store* AND the constant store in the same do-while but with the C400/C78 outside? Tried v2 (Y+C400+C78+C64+CE) = 2.

Let me try wrapping only Y+C64:
- r1: do { Y; C64 } while(0)
That would put the constant build in the same "loop" as the sh. Hmm, might not help.

Another idea: put the C64 store in a `do { ... } while (0)` where the loop body is just it (d_C64 = 6, worse).

Let me try r1 (Y+C64).

Also try: an if statement around the C64 store that is always true but opaque? e.g. `if (j >= 0) { ... }` — the compiler would fold it.

Another lever: what if the y store is moved AFTER the C64 pair in source but sched moves it back? p1 (C64 first) gave 15.

Hmm. Let me reconsider — is it possible that the target's sh is in a *different* basic block after all, i.e. the join block starts at 62c and the sh at 62c IS the first insn of the join block, and the lui at 630 is also in it. So they're in the same block. Yes.

Unless... the sh at 62c is the *delay slot* of the j from arm0? No, the j at 5e0 targets 62c with delay at 5e4.

OK so within one block, the birth-boosted lui/ori hoist above the non-birthing sh. In the target the barrier prevented it. So a lever-free body is impossible unless we split the block.

Can we split the block with real C? Options:
- A conditional that the compiler cannot fold: e.g. `if (D_80115116 & 0x1000) {}` — a real branch, would add instructions.
- A function call — no.
- A `goto` label: 
```
  sh y;
  goto L;
L:
  ...
```
jump_optimize would delete the goto (it's a jump to the next insn). Probably removed before sched.

Hmm, what about a do-while(0) with a `break`? e.g.
```
do { sh y; break; } while (0);   // !FAKE: do-while
```
This creates a conditional structure? `break` inside do-while(0) → an unconditional jump to the loop end label. jump_optimize might simplify it to nothing. But C0535 says do-while splits cse1's EBB — meaning it survives as a label until cse1 at least. sched1 runs after cse1? Let me check the pass order in toplev.c.

Let me grep toplev.c for the order.
