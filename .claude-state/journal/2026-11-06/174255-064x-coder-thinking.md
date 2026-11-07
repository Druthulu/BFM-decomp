---
ts: 2026-11-07T00:42:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SYOf9cvU0Ob8o4FMEqkV
---
Now I see. The trace shows: insn 53 is NOT in the ready list at the start of the block — it appears only at T-5 with priority 0x7f000001 (a huge value = 2147483649?). Hmm: "53 (7f000001)" means priority 0x7f000001 = 2130706433? That's `INSN_PRIORITY` printed in hex? No — the ready list prints `(priority)` in hex? It shows "75 (2)" and "73 (7f000001)". 7f000001 looks like a special marker.

Hmm, ";; launching 53 before 70 with no stalls at T-5" — so insn 53 IS scheduled at T-5 (early), and "blocking insn 53 for 1 cycles, now 68 65 62 59 56" — wait, confusing.

Actually the trace is in reverse order? "ready list at T-5: 65 62 59 56 68 53" then "launching 53 before 70" — the trace prints in a weird order.

The key: 53 IS scheduled (launched) at T-5, before 70. But the final insn order in the dump shows 53 after 65!

Hmm, wait. Maybe I misread the dump order. The dump order (the insn chain) showed: 56 → 59 → 62 → 65 → 53 → 68. But the trace says 53 launched at T-5 before 70...

Hmm, the trace lists T-1..T-15 for the block from 33 to 79. At T-2 the ready list has 56,59,62,65,70,75 → chosen 75 (priority 2). T-3: chosen 73 (priority 2)... 

Hold on, this looks like the schedule runs BACKWARD in the trace listing (T-1 is the last cycle?). "ready list at T-1: 79, now 79" — 79 is the jump insn (the last insn of the block). So T-1 = the first cycle? and the block's last insn 79 is scheduled at T-1? That's backwards: it's listing the schedule from the end backwards.

Hmm: "total time = 15". So the block takes 15 cycles, and the trace lists T-1 (cycle 1?) ... Actually the printout might be reversed because the scheduler prints "ready list at T-n" where n counts down.

Let me interpret: the insns are scheduled in order: 79 (jump, T-1), then 75 (T-2), then 73 (T-3), then 70 (T-4), then 53 (T-5), then 68 (T-6), then 65 (T-7), 62 (T-8), 59 (T-9), 56 (T-10), 50 (T-11)...

That doesn't match the insn chain order (56,59,62,65,53,68,70,73,75,79).

Hmm, the chain order in the dump: (insn 56 50 59), (insn 59 56 62), (insn 62 59 65), (insn 65 62 53), (insn 53 65 68), (insn 68 53 70), (insn 70 68 73), (insn 73 70 75), (insn 75 73 79), (jump_insn 79 75 80).

So the emitted order is 56,59,62,65,53,68,70,73,75,79.

The trace suggests the scheduling decision order was: 79 first? No — sched1 schedules forward; the "T-n" labels are the clock countdown: the block is scheduled from the top; "ready list at T-1" is the initial state.

I think the trace is printed in reverse (the scheduler prints at each step, and the file shows the earliest step last?). Let's not over-analyze.

Key insight from the trace: ";; launching 53 before 70 with no stalls at T-5" and ";; blocking insn 53 for 1 cycles, now 68 65 62 59 56" — insn 53 was *blocked* (queued) for 1 cycle. So 53 became ready but was queued due to a hazard, letting 68, 65, 62, 59, 56 go first.

So the load 53 was blocked by an actual hazard (the load delay?) — `actual_hazard(unit, insn, clock, 0)` returned nonzero. That's why it went after the stores.

Why would a load be blocked? On MIPS1, a load has a "blockage" of 1 cycle: the load's result isn't available for 1 cycle. In `actual_hazard_this_instance`, the hazard is computed against the last insns.

The barrier (asm) changes this: with the asm before it, the load's hazard computation differs (the asm blocks 1 cycle, etc.).

OK. Practical approach: since this is a scheduling-order/hazard issue, the real-C moves that change it:
- change the *order of statements* (source order) — but sched1 reorders anyway.
- introduce a dependence.
- change register pressure/units.

Hmm, what if I move `val = D_801B7A84;` to AFTER the stores in the source? Then sched1 might hoist it... or not. In mine the source order is before the stores and sched1 sinks it. If the source order were after, sched1 might keep it after (bad) or hoist (unlikely).

What about making the load's result needed earlier — e.g., a dependence from the load to the *first* store? That would force the load first. But the stores store constants.

Alternatively, make the stores depend on the load's *address chain*: e.g., compute a pointer from val? No, semantics.

Hmm, what about the ORDER of the two calls and p: In the target, the sequence after the second call is: load val, li 1, three stores, *p=0, sw v1, addiu, sw.

What if the source is:

```
func_8013C0F8((s32)&D_801A64C8);
p = &D_801B7930;
func_8017F53C((s32)p);
val = D_801B7A84;
D_801B7948 = 0;
...
```

What if instead we write the stores in a different source order or use a different construct that changes the hazard counts?

Idea: the hazard blocking is about the load being blocked for 1 cycle. `queue_insn` blocks it. Then the scheduler picks other insns. With the asm, the asm insn is scheduled and blocks the pipeline for a cycle, changing the phase.

Real C alternative: change the *number* of insns before the load in the block so the load lands on a different clock phase! E.g., if the block starts with one more insn (a `move`), the load might not be blocked. But we can't add insns (target count fixed).

Hmm, but we CAN change which insns are in the block before the load: e.g., the `lui s0` (p = &D_801B7930) is before the second call. That's fixed.

Hmm, what about the svec/`li v0,1` at 83d4 (the switch compare)? That's in a different block.

Let me think about `actual_hazard`: it checks `function_units[unit].blockage` for the insn being scheduled against the units of the last `blockage` insns. For a load (unit = "load" or the ALU?), on MIPS1 there's one unit? The MIPS1 machine description (mips.md) defines a `cpu` unit and possibly a "load" unit. Let me look at what units mips.md defines for the PSX config.

Actually, let me test empirically instead. Candidate ideas for the ORDER:
1. Move `val = D_801B7A84;` after the three stores but before `*p = 0;`.
2. Move it after `*p = 0;`.
3. Move it before `p = &D_801B7930;`.
4. Move it before the calls (init at decl).
5. `s32 val = D_801B7A84;` init at decl inside the case.
6. Add `val` usage ordering: `D_801B7A84 = val + 1;` (same).
7. Swap the store order.
8. Wrap the stores in do-while(0).
9. Use `p[0] = 0` vs `*p = 0`.
10. Declare p before val / val before p (decl order).
11. Use a separate `s32 *q = &D_801B7948;` chain.

Also for the REG issue (v0 vs v1): decl order, scope.

Let me generate a batch and score. Since the source has 2 levers, both must be gone; a single candidate must fix both aspects.

Note w3 (barrier only) gives the right ORDER but wrong REG (v1 vs v0). So if I find a real-C that fixes the order, I still need to fix the register.

Let me first try to find a real-C that fixes the order (score should become REG-caller 6 or better).

Batch:
- w10: val load moved after the three stores (before *p=0)
- w11: val load moved after *p=0
- w12: val load moved before p=&D_801B7930
- w13: val load moved before the first call
- w14: `s32 val = D_801B7A84;` at decl (inside case, before the calls)
- w15: decl order val then p
- w16: do-while(0) around the three stores
- w17: do-while(0) around *p=0
- w18: p[0] = 0 instead of *p = 0
- w19: reorder: D_801B7988 = 1 before *p = 0
- w20: `val = D_801B7A84; D_801B7988 = 1; D_801B7948 = 0; ...` (move the li's statement up)

Let me write a generator script for item 2.
