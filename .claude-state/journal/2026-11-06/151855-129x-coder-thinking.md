---
ts: 2026-11-06T22:18:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aINFvRwYNg4dzgTVzwTN
---
Current 15:18. Item 1 work: 14:37-14:51 (14 min) + resumed at ~15:10 to 15:18 (8 min) = ~22 min. Meets ≥20 min, and ~60 scored tries now. 

Now, since i2 = 3 is so close, maybe I should update item 1's result? It's still a WALL (best 3 now, not 13). Wait — i2 is a lever-free body scoring 3! That's a big improvement. The WALL's best should be 3. And win.c should be i2 (score 3).

Hmm, but is i2 semantically correct? It's the same code wrapped in do{}while(0) — yes, semantically identical. And it has `// !FAKE: do-while` as required. No levers. So best = 3.

Can I get 0? The residual is the constant pair schedule. Let me think once more.

The 3 mismatches:
mine: lui a1,0xff @150; ori @154; nop @158
target: nop @150; lui @154; ori @158

So mine's pair is 4 scorer-slots earlier. The scorer's indices differ from raw disasm indices (they exclude some insns like nops? no...). Anyway.

To shift the pair 4 slots later, I need the scheduler to place it later. The scheduler places insns by priority; the constant's priority is low. It's placed when the ready list has it as the best candidate. If I *increase* the priority of other insns available at those slots, they'd be scheduled first, pushing the constant later.

The mask is used at the `and` (late). Its critical path is short. Other sxy insns have their own paths.

What if the mask's use is made *earlier* (so its priority rises and it's scheduled later? no—higher priority means scheduled earlier).

Hmm, actually a low-priority insn is scheduled late; the constant at 163 is already later than many. The target has it at 166 (later still). So we need to lower its priority further or add competing insns.

Idea: make the mask's first use later by moving the packet store's `and` later. The `and v0,v0,a1` is at 191. If the packet store expression were computed later... it's already late.

Idea: the mask constant is `0xFFFFFF` (24 bits). What if we use a mask that requires a different materialization sequence? E.g., `0xFFFFFF` = lui 0xff; ori 0xffff. If we wrote `(u32)pkt & 0xFFFFFF` as `((u32)pkt << 8) >> 8` → sll/srl (2 insns, different schedule) — would change the instructions (target has and). No.

Idea: change the *other* constant 0xFF000000's position? The target has `lui a2,0xff00` at 176. Mine matches.

What if we reorder the two masks in the expression: `(*(u32*)pkt & 0xFF000000) | (X & 0xFFFFFF)` — the 0xFFFFFF is second. In the RTL, the constant r193 is created early (insn 401) because expand processes the expression. The scheduler places it.

Let me look at the .sched dump for i2 to see the mask's position and the surrounding ready list. But matching the target's schedule requires the target RTL, which we don't have. However, the target's *disassembly* tells us the desired position.

Honestly, a 3-position sched1 tie is a classic wall. The wall tag "sched1-ready-order" or "sched1-const-pair-hoist" fits. But is there a wall tag for "const pair scheduled early"? "sched1-const-pair-hoist: sched1 hoists a constant pair above the store the target keeps first (O01x)". Yes! That's exactly it: sched1 hoists the constant pair above the stores the target keeps first. The target keeps the mask materialization later (after the sxy stores), sched1 hoists it above them.

Wait, but the target ALSO has the mask before the sxy stores? Target: lui at 166, which is *within* the sxy stores (153-177). The target's mask is at 166, after the first 3 sxy groups. Mine at 163, after the first 2. So sched1 hoists it one group earlier. The tag "sched1-const-pair-hoist" fits.

But hold on — maybe a different do-while span could place the mask after the 3rd sxy group. o2/o3 (sxy reorders) gave 9/10. The permutations didn't reach 0.

Let me try one more: combine i2 with a reordering of the `pkt[0x14]...` block or the `pkt[0xC]/w2` block to shift the ready list. m4 (w2 do-while) = 7; m2 (p14 do-while) = 4.

What if we wrap the p14 block in a do-while *and* keep i2? m2 = 4 (one worse). Hmm.

What about wrapping the `w2` block with a do-while and the otp block (m4 + i2)? m4 already includes i2 (m4 = i2 + w2 do-while) = 7.

So i2 alone = 3 is best.

Given the wall criteria are met for item 1 (≥20 min, ≥30 tries), I'll record WALL with best 3, wall tag sched1-const-pair-hoist, evidence describing the 3-position ORDER residual.

Wait — but should I record it as a WALL or keep trying? The residual is 3 ORDER positions, not 0. A WALL is correct if I can't crack it. I've done ~60 tries and 22 min. Let me do a few more targeted attempts, then record.

One more idea: the do-while boundary. What if we use `do { ... } while (0)` around the *sxy store block* (m1=11) or around a *subset* (3 of the 6 lines)? The mask's placement depends on the EBB. Let me try wrapping the last 3 sxy lines (sxy[1]) in a do-while, keeping i2's otp do-while. That might shift the mask by one group.

Also wrap the first 3 sxy lines.

Let me test s1..s4:
- s1: i2 + do-while around the first 3 sxy lines.
- s2: i2 + do-while around the last 3 sxy lines.
- s3: i2 + do-while around the p14 block (m2=4, already).
- s4: i2 + do-while around the w2 block (m4=7, already).

Let me test s1/s2.
