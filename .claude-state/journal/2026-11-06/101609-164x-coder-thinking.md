---
ts: 2026-11-06T17:16:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_v2oX2iCPSZSjPjHlUbgs
---
All 21. The mask consistently goes to t7.

Let me examine the actual mask materialization and check whether the mask's register is chosen by local-alloc or by *combine*. The mask's RTL is:
```
(insn 571 (set (reg/v:SI 87) (const_int 16711680)) movsi_internal2)
(insn 572 (set (reg/v:SI 87) (ior (reg 87) 65535)) iorsi3)
```
This is a two-insn constant materialization. Local-alloc allocates 87.

Hmm, what if the issue is that the mask pseudo 87 is *created late* (its first use is at UID 429? no, its def is at 571). 

Wait — maybe the order is: local-alloc processes qtys by priority, but the mask's qty might have a *hard reg suggestion* from a copy or from `qty_phys_sugg`. Hmm.

Let me try a completely different lever: make the mask NOT a separate variable but a *pointer* to a constant? no.

Alternatively, accept 21 but try to see if there's an alternate *body shape* that matches. Since 21 instructions differ (10 ands + lui/ori + 6 stores? no, the 0x8E store), maybe a different structure could produce the target bytes by luck. Unlikely.

Let me try one more class: change the six packet blocks' *constant materialization order* by reordering the source statements within each packet (e.g., put the `*q = const` store after the p[3]=5 etc.). The sched1 hoisting order of the constants depends on the source order. If the 0x8E constant is materialized at a different time relative to the mask, the register choice may flip.

The target's constants in order: 0x8A (a2), 0x8C (t0), 0x8E (t7), 0x9A (s5), 0x9C (s6?), 0x9E. The mask is materialized at insn 16 (after the constants at 5-15). So the mask's materialization comes after all constants.

If we could make the mask materialize BEFORE the constants (e.g., by moving `m24 = 0xFFFFFF;` to the top of the source), sched1 might place it earlier. a2/a3 tried; score 23. Let me look at a3's mask position: maybe it moved to insn 5 but still t7.

Actually, if the mask were materialized first (before the constants), local-alloc's allocation order might still be priority-based, but the *conflict* structure changes: the mask's live range would start earlier, overlapping more constants.

Hmm.

Let me try a different thing: change the *constant* 0xE100008E to a value that materializes with 3 insns (e.g., 0xE100008E + arg1*0? no).

I think I should try the possibility that the mask's allocation is decided by *combine* creating a REG_EQUIV constant that local-alloc treats specially. There's a local-alloc concept: `qty_const` / `qty_phys_reg` and `reg_equiv_constant`. A pseudo with REG_EQUIV (const) can be rematerialized; local-alloc may allocate it at its *use* rather than keeping a register. The constant 117 has REG_EQUAL (not REG_EQUIV). The mask also has REG_EQUAL.

Hmm.

Let me look at local-alloc.c for "qty_const" / priority. Actually, let me look at the sort: maybe `qty_compare_1` is only used for qtys without suggested regs, and there's a separate `qty_sugg_compare_1` for those with suggestions. The mask might have a suggestion.

Honestly, the fastest path: test whether the mask's register depends on the *number of refs* by making the mask used only 3 times (fewer) and seeing if it changes. If it stays t7, the driver isn't priority.

Let me do that experiment (use 0xFFFFFF inline for 9 of 12 uses, keep m24 for 3).

Actually, d1/d2 (6 inline, 6 m24) still gave 21 — the mask stayed t7 with only 6 uses. So the ref count doesn't matter. The mask's allocation is stable at t7.

So what would make it t6? In the target, the pin. Maybe the ONLY way. But the task says to find a lever-free body — some items are walls.

Let me check: with the pin, is the mask allocated t6 and everything else unchanged? Yes (orig scores 0).

I'll record item 3 as a WALL (best 21), after ≥20 min and ≥30 tries. I have ~25 tries and 10 min. Let me continue trying for 10 more minutes with other angles to be diligent, since 21 is close and maybe a structural change flips it.

Other angles:
1. Move the mask's definition into the *last block* differently: e.g., compute `m24` as part of the first and: `p0->unk0 = (p0->unk0 & 0xFF000000) | (*ot & (m24 = 0xFFFFFF));` — an assignment expression. Might change the pseudo's birth.
2. Use a `for` loop over the six packets with the mask... changes structure.
3. Change the mask's uses to use a local copy per statement: `u32 mm = m24;` inside each statement — extra copies.
4. Use `m24` declared inside the last block scope (after obase): `{ u32 m24 = 0xFFFFFF; ... }`.
5. Make the mask a *global* variable: `extern u32 m24;`? That would load from memory — different instructions.

Let me try 1 and 4.
