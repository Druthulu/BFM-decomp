---
ts: 2026-10-22T20:22:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4Fg9AKX3D4uMbv5ZgJAD
---
In score-0, r80 is defined twice (insn 30 and 43)! "(set (reg/v:SI 80) ...)" at two places. So there are TWO separate pseudos numbered 80? No — r80 set at insn 30 and again at insn 43 means the address pseudo has 2 sets (not a single-set). That makes it ineligible for local-alloc (multi-set → global). Ah, and that's why global allocated it and spilled it.

So in score-0, the call-arg address pseudo is *re-set* between calls (two sets), which makes local-alloc skip it → global allocno → priority 10000? (refs 4, live 8) and it lost to... hmm, it says r80 in .greg order 78 79 80 72 with pri 10000 and conflicts a1,s0,sp. It ended up spilled (remat).

In c_struct, r80 has a single set at insn 21 → local-alloc assigns s1.

So to get the target behavior in the c_struct form, I need the address pseudo to have ≥2 sets (so local-alloc leaves it to global, which then spills/remats it) OR make it not locally allocatable.

How does score-0 get 2 sets? Because the C has scalar copies and cse created the address pseudo twice — e.g., one before the X call and one before the Z/Y calls (after the stores, since the value must be recomputed?). Let me look at insns 30 and 43 context in score-0.

Interesting. So the *natural* C that gives 2 sets is the scalar-copy form (score-0). With the block-move form, cse merged into one set.

So the goal: block-move source behavior + address pseudo with 2 sets. What makes cse set it twice? In score-0, after the copy, cse creates the address for the calls. Two sets suggests one before call X, then re-created before Z (maybe because a call clobbers... cse invalidates on calls? cse's `invalidate_memory` at calls, but a pseudo in a register isn't invalidated by a call).

Let me look at score-0's lreg around insn 30 and 43 to see the structure.
