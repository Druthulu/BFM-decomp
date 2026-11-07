---
ts: 2026-11-06T11:38:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6IrJFeMbFBreZ24maVcV
---
Key insight: "When all instructions have a latency of 1, there is no need to move any instructions. Subtracting one here ensures that in such cases all instructions will end up with a priority of one, and hence no scheduling will be done."

So with all unit latencies, priority is 1 for everything and order is source order (via rank_for_schedule tie-break classes). But in our case, the diff shows movement, meaning some insns have insn_cost > 1 — on r3000, memory ops (loads) have latency 2 (load delay). So `lw t1,16(sp)` (w_ load) has cost 2, making dependent adds priority 2 > stores 1. That's why the loads and their users got hoisted.

Target, with barriers, has loads scheduled after stores (source order). In target: lw t1,16(sp) at 3894 comes after the byte stores; the load's own priority: `lw` priority = max over LOG_LINKS (the stack pointer? no) = 1. Then addu x depends on it: priority = priority(lw) + insn_cost(lw, ...) - 1 = 1 + 2 - 1 = 2. So addu has priority 2 > byte stores 1. Within the target's EBB2, the addu should be scheduled first, but it isn't — because the lw is a dependency and rank_for_schedule class: "Choose the insn from the highest numbered class if different" — class 1 = data dependent on last scheduled, class 2 = anti/output, class 3 = independent. Hmm, but priority is compared first.

Wait, in target EBB2, order: lw t1(w_), lw a2(tag), addu s1, sh, sh, sh, lw t1(h_), and, addu s2, ...

Hmm priority(addu) = 2, priority(lw)=1. So the ready list initially has lw t1 and lw a2 (both ready, priority 1). It picks... highest priority, ties broken by rank_for_schedule. After scheduling lw t1, the addu becomes ready with priority 2, and would be picked next (highest). Indeed target picks lw a2 next, then addu. Hmm, lw a2 has priority 1 but was picked over addu (priority 2)? Unless rank_for_schedule class ordering overrides? No, priority is compared first: "if (value = INSN_PRIORITY (tmp) - INSN_PRIORITY (tmp2)) return value;" — but which is x/y? The sort function orders ready list by preference. Hmm.

Wait, maybe the load latency on r3000: insn_cost for a load might be 1? Then addu priority 1. And the scheduling difference in mine comes from the tie-break classes (data dependent on last scheduled). Hmm.

Let me look at insn_cost in mips.md / mips.c. But maybe more productive: what made mine reorder? In mine, after `sh s1,8(v0)` (store), the next was `lw t1,16(sp)`. Hmm.

Honestly, rather than reverse-engineer, let's do experiments. The lever-free target requires the early block's stores to come before the adds. What real C move can achieve it? Possibly splitting the EBB with a construct that does NOT create a loop.

Options that create a basic-block boundary without a loop:
- `if (cond) { ... } else { ... }` where cond is a real condition? Not present.
- A `&&` fold? 
- A goto/label: `goto L; ... L:` — creates an unconditional jump; jump opt removes it. Does it split sched1's blocks? Basic blocks are computed from labels/jumps. An unconditional jump to the very next insn: cfg may create a block boundary at the label. jump.c's `delete_unreachable_blocks` / `jump_optimize` might merge them before sched1. Hmm, but the do-while's back edge label splits.

Actually wait: does a do-while(0) create a loop that survives until after sched1? The loop is a branch to a label with constant condition 0 → jump opt removes the branch at `jump_optimize` (before sched1? sched1 runs after jump? Pass order in 2.7.2: cse, loop, cse2, ... jump, ... sched1 before local-alloc? Actually sched.c runs `schedule_insns` twice: once after cse/loop (sched1) and once after reload (sched2).

Hmm, the do-while's loop notes remain (loop.c ran earlier? loop.c runs after cse1, before sched1). do-while creates LOOP_BEG/END notes at cfg construction; loop.c then sees a loop with a constant trip and may do things (that's the regalloc change we saw: refs += loop_depth).

Alternatively use `if (0) {}`? constant folded early.

Let me try a different real-C move: compute the adds in a way that they depend on a store. Hmm.

Alternative idea: maybe the target's order can be obtained by *statement order* changes that alter the dependency graph. E.g., in mine, the first statement in EBB1 after p+=8 is `p[3] = 8` (sb), then vx=x (move), p[7]=0x38. In mine the adds are hoisted before these stores. What if we make the adds textually later AND give the stores higher priority by increasing their dependency depth? For example, chain the byte stores through a single temp: `u8 *q = p; q[3] = 8;` no.

Actually, here's a thought: what if the stores to p[4..6] etc. are done via `p[4] = c1;` where c1..c6 are function parameters in registers s3-s8. In target these stores are scheduled right after the moves of vx/vy and before the loads. Their priority is 1. The loads (w_, h_) priority 1. Ties broken by rank_for_schedule: class 3 (independent) all, then maybe by "source order" via `INSN_LUID`? Let me read the rest of rank_for_schedule.
