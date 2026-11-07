---
ts: 2026-11-06T18:18:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6N0bgypgnIhJldBplaoc
---
The loads are `(set (reg/v:SI 4 a0) (mem (plus (reg/v:SI 4 a0) 204)))` — the variable is pseudo 4?? Wait, `reg/v:SI 4 a0` — regno 4 = a0 hard reg. Hmm, `reg/v` is a "virtual" reg note? In GCC 2.7.2, `reg/v` means... Actually `/v` is REG_USER_VAR flag. The regno 4 means a0 is a hard reg here? No wait, "a0" printed after 4. So it IS hard reg 4. But `(set (reg/v:SI 4 a0) (mem...))` sets hard reg a0? That's weird but it's what -dg prints: the global allocno r76's members include pseudo 4? Hmm no.

Oh I see: this is the .greg dump BEFORE global allocation; the pseudos are still numbered. But the dump shows regno 4 = a0 because the body was written using... no. Hmm, `reg/v:SI 4 a0`: if regno < FIRST_PSEUDO_REGISTER (16), it prints the hard reg name. So the loads write to a0 itself! That means global-alloc has *already* assigned something? No — .greg is before allocation ("Register dispositions" lists 72 in 4 etc.).

Wait, dispositions: 72 in 4, 74 in 6, 75 in 2, 76 in 4, 78 in 5, 79 in 2. So pseudo 72 got $4, 76 got $4?? Both in 4? That's the table's reading. But the insn dump prints `reg/v:SI 4 a0` — that's odd: the insn dump is printed AFTER the dispositions? The .greg dump prints the RTL with reg_renumber applied? Hmm, GCC's greg dump prints the function after global_alloc, with the dispositions and the renumbered RTL. So the RTL shown already has hard regs: pseudo 72 → a0, 76 → a0. Wait, but then both v1... 

Hold on: the insns show `(set (reg/v:SI 4 a0) (mem (plus (reg/v:SI 4 a0) 204)))` — i.e., load a0 from a0+204. That's the score-3 build: `lw a0,204(a0)`. Yes! So pseudo 72 (the load result in block...) is in $4. And 76 also in $4? That can't be — they're the same value in different blocks (72 dies in 3 places = the join?). Hmm, maybe 72 and 76 are the same pseudo in different blocks? No.

Wait, the dispositions: "72 in 4 74 in 6 75 in 2 76 in 4 78 in 5 79 in 2". Both 72 and 76 in 4?! Global-alloc would never assign two allocnos to the same hard reg if they conflict... unless they're in the same allocno (they're not) or don't conflict. 72 conflicts list includes "72 74 75 2 5 6 29" — the conflicts list includes 76? No: "72 conflicts: 72 74 75 2 5 6 29" (no 76). And 76 conflicts: "75 76 29". So 72 and 76 do NOT conflict (different blocks/lifetimes). So both can be $4. OK.

Hmm, so there are multiple pseudos for v1: 72 (in the fall-through branch) and 76 (in the else block)? But the source uses one v1 variable... Actually gcc may split a variable into per-block pseudos? No — the variable is one pseudo. Unless the source code creates separate loads: `v1 = a0->unkCC` appears three times in the source, each with its own... no, same variable v1.

Wait — the .greg RTL shows three loads (insns 32, 40, 53) each `(set (reg/v:SI 4 a0) ...)`. All three are a0? Hmm, that means all three loads' results were already assigned to $4? But dispositions show only 72 and 76 in 4.

Hmm, maybe the dump prints the RTL twice: once before with pseudo numbers and once after with hard regs. The grep hit lines 83-136 (after dispositions). Perhaps pseudos 32/40/53 got coalesced/renumbered to 4.

Whatever — the important thing: allocno r76 has preference $4 and is allocated second; it gets $4. Which pseudo is r76? "76 conflicts: 75 76 29", refs 4 live 8, prefs 4. r72: conflicts 72 74 75 2 5 6 29, prefs 4, dies in 3 places, pointer, refs 4 live 10.

Both prefer $4 (a0) — the "preference 4" comes from record_reg_classes: the load base a0. Both are load results.

The target: one load result in $3, another in $4? Wait target has two loads: d24 `lw v1,204(a0)` and d30 `lw v1,204(a0)` — both $3. Hmm, but the .greg shows three loads (insns 32, 40, 53): block B, block C, and... the third? Maybe one is the "else" block and one is the merged fall-through... The source has 3 identical `v1 = ...` statements (one per branch) and jump2 merges two branches into one block (the two identical arms). So there are 2 blocks but 3 statements; the merged block has one load. Hmm, the .greg dump is before jump2? The order of passes: .greg is after global-alloc, which is after jump/jump2? Actually global-alloc runs after jump2 (jump2 is late, post-reload). The .greg dump shows 3 loads because the arms weren't merged yet (cross-jump happens at jump2, post-reload). Right: the 3 loads are in 3 blocks pre-reload; jump2 merges two identical arms (d24 and d30) later, leaving 2 loads.

So pre-reload there are 3 blocks each with a load of v1 (one variable, but in different blocks → local-alloc per block... yet global allocnos 72, 76 exist because v1 is live into the join).

OK. The fix: make r76 not prefer a0. r76's preference comes from the load `set (reg 76) (mem (plus (reg 4 a0) 204))` — record_reg_classes gives a preference for the base reg (a0) because it's a register operand used in an address... Actually in global-alloc.c, `record_reg_classes` for an operand that is a REG adds preferences: "If the operand is a REG, add a preference for that register"? No. The preference 4 likely comes from the fact that the insn's output could share the base reg — `record_reg_classes` has a `classes[i]` and for memory operands there's a "copy preference" when the operand is the same register? Hmm.

Actually, I recall in global-alloc.c, `record_reg_classes` computes `pref` from `REG_NOTE REG_DEAD`? Let me look at the code to understand which C spelling kills it. Search global-alloc.c for "preferences".
