---
ts: 2026-11-06T07:25:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_yQX0uWIJmLUylhcgRO3Y
---
Target uses a1,a2,a3 for the copies because a0 is... wait, look: target at start does `move s0,a0` then `lw s1,52(s0)` — no use of a0 afterwards until `li a0,75`. So a0 is free after the move! Yet target uses a1,a2,a3 for the loads, not a0,a1,a2.

Hmm, so it's not that a0 is live. Then why does local-alloc assign a1,a2,a3? Interesting: In target, the first group: `lw v1,52(v0); lw a1,56(v0); lw a2,60(v0); lw a3,64(v0)` then stores. In mine (lever-free), it uses a0,a1,a2 (3 regs) for the 4 loads? Actually mine[10:13] lw a0/a1/a2 then... let me see mine full listing. Let me dump my candidate w1.o. But dt.sh didn't --keep. Let me run with --keep on w1.

Actually the diff showed mine at 10-12: a0,a1,a2, and target a1,a2,a3. The target's first load is v1 (into a callee-saved? no v1 is caller). Wait target loads 4 values: v1, a1, a2, a3. Mine: v1, a0, a1, a2? The diff only showed 3 lines per group because v1 matched.

So target uses a1,a2,a3 plus v1; mine uses a0,a1,a2 plus v1. Why does the target start at a1? Because a0 is reserved for something. In the target, `li a0,75` at insn 32 is the id value set early. Maybe local-alloc assigned the pseudo for `id` to a0 and it's live from... no, li a0,75 occurs late.

Wait, maybe global-alloc allocated a0 to the `keep_a0` pseudo? But target is the real bytes; the pin/keepalive in our source is a FAKE lever to reproduce target. The target's natural C presumably keeps a0 occupied. What holds a0 in the target between the move and `li a0,75`? Nothing in the listing. Registers don't need to hold anything; allocation is determined by pseudo lifetimes. The set of pseudos and their live ranges differ.

Possibility: In target, arg0 (a0) is NOT copied to s0 immediately in terms of pseudo allocation: the pseudo `arg0` might be used directly and s0 is a separate variable. Actually target `move s0,a0` at insn 2 means s0 = arg0, so arg0 pseudo's only use is that move; its live range ends there. So a0 free.

Hmm, then why a1,a2,a3? Maybe because the target has an extra live quantity using a0 across the copy region — the `id`? `li a0,75` at insn 32. If `id = 0x4B` were hoisted to before the copies, it would occupy a0 through the copy region, making the copies use a1-a3. But the li instruction is at 32, after the jal. However the pseudo `id` could be allocated to a0 and its live range start at the def (li at 32). No.

Alternatively, local-alloc allocation order: quantities are sorted by qty (refs/live length). The choice of which reg each gets depends on the pseudo set. Maybe the target has one MORE quantity in that region (4 loads + 4 stores?). Both have same instruction count 49.

Let me compare mine full listing vs target. Let me dump w1 with --keep.
