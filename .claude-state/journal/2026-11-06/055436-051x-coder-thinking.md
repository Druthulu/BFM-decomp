---
ts: 2026-11-06T12:54:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RTwxFLzAplUVNriWaz35
---
sched1 (schedule_insns at 3033) runs after cse/loop/jump_optimize (2827-2929). So labels from a do-while would be removed by jump_optimize if they're redundant... but C0535 says do-while splits cse1's EBB, which is BEFORE jump_optimize. So after jump_optimize, the label may be gone → no effect on sched1.

But item 1's do-while DID change sched1's output. So it wasn't removed — probably because the do-while created a real loop structure (NOTE_INSN_LOOP_BEG/END) that survives, and loop.c or sched uses it. Actually a `do{}while(0)` loop with a constant condition: loop.c's `loop_optimize` would see a loop with a false exit condition; it might not remove it (infinite/zero-trip loops are kept). The `while(0)` means the loop body executes once and then the condition fails. gcc 2.7.2 probably keeps the branch but jump_optimize deletes the jump-to-next-insn. Hmm, but then the "loop" notes remain → the BB might be split at the LOOP_BEG/END notes? Basic block boundaries are computed from code labels and jumps, not notes. Hmm.

Wait, maybe sched1's `schedule_insns` uses `NOTE_INSN_LOOP_BEG`? No.

Hmm, but empirically item 1's do-while worked. Maybe the mechanism in item 1 was: the do-while kept `sp10[4] = t` in a "loop" so flow.c gave the store's *register* extra refs? No, the change was a nop placement.

Actually in item 1, maybe the do-while produced an extra label/BB, splitting the block so sched ran on two blocks. Since it worked, something like that.

So here, let me try wrapping the y store with a `break`:
```
do { sh y; break; } while (0);
```
Hmm, `break` inside do-while(0) → the code becomes `sh; goto end; end:` — jump_optimize deletes.

Alternatively use `if (1) { ... } else { ... }`? Folded.

OK. Let me think about a completely different real-C lever for the birth boost: `birthing_insn_p(PATTERN(prev))`. Let me read it — maybe it returns true only for insns that set a *pseudo* in a way... If the constant were loaded into a *hard* register... no pins allowed to be added (well, pins are allowed to stay, not be added).

Hmm, what if the constant build is a *move from another register* instead of lui/ori? E.g. if 0x64808080 were already in a register from earlier in the function (live across), the store would be a plain `sw` from that register. But then the target's lui/ori wouldn't exist. Target has lui/ori.

OK so: the target has lui/ori and the sh in one block, ordered sh-then-lui. Lever-free, sched1's birth boost hoists the lui above the sh. That's a wall: `sched1-birth-boost`.

But hold on — is the birth boost really the cause? `birthing_insn_p` — let me read it to be sure. And note the boost only applies to predecessors with 0 REG_DEAD notes. Let me check.
