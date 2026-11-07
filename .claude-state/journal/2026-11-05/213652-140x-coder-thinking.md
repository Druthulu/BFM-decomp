---
ts: 2026-11-06T04:36:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zJE04EFxWAnVsIVD8j03
---
z12 = 19, z13 = 6. Still z8/z13 at 6.

Time 21:36. Item 4 started ~21:22 → 14 min. Need 20 min (~21:42). Let me try a few more ideas on z8's remaining diff (p load after addiu + nop).

Idea: make the p load's priority higher by adding a second use of p in the same block. E.g., after the p load, use p in a computation that's dead? no.

Idea: make the addiu's priority 1 by moving its dependent (the store) to another block. The store is shared.

Idea: make the addiu depend on the p load so it can't be scheduled first: `v = v + 0x600;` → the constant 0x600 could be loaded from a global? no.

Idea: use `v = v + 0x600` where 0x600 is `(s32)p & 0`? folds.

Idea: reorder so the p load is born AFTER the addiu and the LUID tie-break... but the class difference (addiu class 1) still wins.

Hmm, what if the p load is made data-dependent on the addiu? `p = model;` after `v = v + 0x600;` — no dependency.

What if we make the store's address use p and the store's value use v, and place the addiu BEFORE the p load in source, so the addiu's LUID is lower? The class: after the last chain insn (sll), the addiu is class 1 (data), the lw is class 3. Class 3 wins (higher number). Wait, re-read: "Choose the insn from the highest numbered class if different." Class 3 (independent) is highest. So the lw (class 3) SHOULD win over the addiu (class 1)! But z8 has addiu first. So in z8, the lw must be class 1 or 2, or its priority is lower.

The lw's class relative to the last scheduled insn (sll): find_insn_list(lw, LOG_LINKS(sll)) — is there a dependence? The sll (v0 = v0<<5) and the lw (v1 = mem) — no data dep. But there might be an anti-dep: the lw writes v1 (p), and the sll reads... v0, not v1. So class 3. Priority: the lw's dependent is the sh (in another block) → priority 1. The addiu's dependent is the sh (same block? if the sh is in another block, the addiu's priority is also 1!). If both priorities are 1, the class decides: lw class 3 > addiu class 1 → lw first. But z8 has addiu first. So the sh must be in the same block as the addiu (priority 2) but not the lw? Impossible—same block.

Unless the lw's LOG_LINKS include a dependence that makes it class 2 (anti/output) with the last insn. The last scheduled before the lw might be the addu (not the sll): if the order is sll, addu, sll, then the last is sll. Hmm.

Wait, maybe the lw is scheduled before the sll in the ready list but blocked by a function unit hazard, and the trace... Let me just dump z8's sched trace for that block and see the ready list. That would tell me exactly. Let me dump z8 with cc1_dumps_tu.sh (the scratch TU from the last --keep is z8? The last --keep was z13? No, I ran --keep for z8 earlier, then dt.sh (no keep) for z9..z13 except z8's --keep. The last --keep was z8's disassembly. But then I ran --keep? No. So the scratch TU is z8. Let me dump and read the block trace.

Actually, time is short (need ~6 min). The dump takes 1-2 min. Let me do it: dump z8, find the block with the `<0x11` arm, read the ready list.
