---
ts: 2026-10-22T08:43:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM1x
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_VVyjHkjN608uUsS2GxhT
---
Now I see the RTL before allocation:

- r72 = arg (a0 → pseudo 72)
- r74 = ptr = arg->unk64 (loaded in entry)
- r75 = st (u16 load)
- r83 = zero_extend of r75 (SI) — the switch value! Note: r83 is a pseudo (not hard v1) here; in the .greg dump, insn 89 became `(set (reg:SI 3 v1) (zero_extend:SI (reg/v:HI 75)))` → r83 → v1.
- r84 = const 1, r85 = const 2
- insn 22: `(set (reg:SI 4 a0) (reg/v:SI 74))` — copy of ptr (r74) into a0 for the call → this creates the preference "74 prefers 4" (a0) → r74 → a0! That's the "preferences: 4" for r74.
- r77 = call result (v0)
- r78 = const 36864 → in .greg it became v1 (local alloc? no—r78 in dispositions "78 in 3" = v1). r79 = the slt result → v1 too.
- r73 = q copy 1 (case 2 arm): load of arg->unk64
- r76 = const 3 (HI) → in .greg: 76 in 2 (v0).

Hmm! So r76 = the constant 3 (a local pseudo in block 40) — and in .greg it got v0 (2). But in the final asm, `li v0,3` — yes! v0 = 3. OK.

And in the .greg order "73 74 76 83 72" — 76 is the const 3 pseudo, and 83 = the zero-extended switch value. Hmm, but r76 (const 3) is a local pseudo in block 40 (not global)! Yet it's in the "regs to allocate" list. Hmm — because in the .greg dump (after allocation) the numbering... hmm.

Wait, in the .greg dump, the "regs to allocate" list is printed at the START of global_alloc, and the dispositions at the end. But the pseudo numbers in the .greg dump differ from the .rtl dump? In .rtl, r73 = q copy in block 40; r76 = const 3.

In .greg: "73 conflicts: 73 76 29; 73 preferences: 4" → r73 conflicts with r76 (const 3) and sp. r73 prefers reg 4 (a0).

Where does r73's preference for a0 come from? In the .rtl, r73 = the q load in block 40. Is there a copy involving r73? In the join block (label 98), the stores use r73 and r74:

Let me see the rest of the RTL (blocks 98 and 120).

Let me print more.
