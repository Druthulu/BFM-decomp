---
ts: 2026-11-06T16:52:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WRmagUBOt9JqN79xMVWZ
---
No REG_ALLOC_ORDER defined for MIPS → gcc uses the default order = register numbers ascending, with some class sorting in find_free_reg (it uses `reg_alloc_order` if defined else all regs ascending by number). So s0 (16) should be first.

Unless s0 is marked as *fixed* or *not available* for global alloc: `fixed_regs[16]`? On MIPS with -msoft-float, s0 ($16) is a normal callee-saved... but wait: $16 = s0 = fp? In the O32 ABI, $16-$23 are s0-s7. Hmm.

But maybe the compiler reserves s0 for something? No, the target uses s0.

Look at the conflict lists again in no_fp: "86 conflicts: ... 2 3 4 5 29" — note 6,7 missing (a2,a3) and 16..23 missing. The conflicts listed are only regs that conflict. Since s0 (16) isn't in any conflict list, all globals could use it. The allocator assigned s1..s7 instead.

Ah — maybe because of `reg_preferred_class`: for a pointer pseudo, the preferred class might be something, and find_free_reg uses the qty's min_class. For pointer types (Pmode), maybe the preferred class excludes $16? Unlikely.

OR: the *ordering*: global-alloc allocates in priority order; the first qty gets the best register. "Best" = lowest cost. In find_free_reg, the cost of a register may include `reg_pref` preferences. If a pseudo has a preference for a specific hard reg (from copies, e.g., `fp = ...` no).

Hmm, what about this: the disposition list shows 91 in 16 (s0) as a block-local. In global-alloc, `regs_ever_live` / hard reg conflicts are computed from `hard_regs_live` at each point. Since 91 is s0 in block0 and block0 is part of the CFG, the global allocno conflict computation `find_reg` uses `regs_conflict` bitsets built from hard_reg_live... If a global's live range doesn't include block0, no conflict.

Let me just test empirically: if I remove/alter the block0 s0 user (e.g., compute &D_800AF648 differently), does fp get s0? That's a shot in the dark.

Alternative: maybe the reason is that in no_fp, the fp expression produced TWO pseudos (85, 225), and the *fp pointer pseudo* is one of them with a shorter life; its priority is lower, so it gets s5. The target's fp is a single pseudo with 17 refs.

Wait: in no_fp, which is fp? 135 has 17 refs (pinned orig: 135 in 18 = s2?). Hmm, in pinned, 135 in 18 (s2) and 86 in 17 (s1). In no_fp, 135 in 18 (s2) and 86 in 17 (s1) — same! So 135 and 86 are the same pseudos in both. What are they? 86 has 31 refs (from the lreg list: "Register 86 used 31 times across 82 insns") — that's fp probably (12 stores + ...). Hmm, 31 refs.

In no_fp, extra: 85 (7 refs, pointer) and 225. So fp's expression got split differently.

Hmm, wait: in no_fp the extra pseudos 85 and 225 appear, and 82/84 swapped registers vs pinned (82 in 19 vs 20; 84 in 20 vs 19). So the whole cascade came from those extra pseudos.

The extra pseudos likely come from the fp assignment `fp = (s8 *)prim + 0x22;` being compiled as: t = prim + 0x22 (new pseudo 225?), fp = (s8*)t. Without the pin, cse/combine splits it.

Actually, with the pin, `fp` is a register variable pinned to $16; the assignment `fp = (s8*)prim + 0x22` might generate `addiu $16, prim, 0x22` directly.

Without the pin, `fp = (s8*)prim + 0x22` should also be a single addiu into fp's pseudo.

Hmm, but the extra 85/225: 85 has 7 refs (pointer). Maybe 85 is `prim` in the loop? In pinned, prim is 134 (9 refs, 170 insns)? 

I'm spending a lot. Let me check the actual asm difference in the loop to see if the extra instructions are in the loop body or prologue. The diff showed the loop shifted by one instruction (`move a0,s7` vs `nop` and `sh` positions). The 3 extra insns (268 vs 265) include `move s3,v0` (target has it too?), `addiu s0,s3,38` vs target... 

Let me diff the full asm listings side by side to see the 3 extra instructions.
