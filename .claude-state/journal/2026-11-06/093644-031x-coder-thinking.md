---
ts: 2026-11-06T16:36:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_st7uRVe4XhDfSEQqub9q
---
In r16: `move $3,$2` (ret=77 in $3), `andi $2,$3,0xffff` (78 in $2!), then `beq $2,$0`, delay slot `andi $2,$3,0x8000` (m=75 in $2). So m tied with the zero_extend pseudo 78? Actually m got $2 which was 78's reg. Interesting.

So the zero-extend 78 got $2 and m got $2 (after 78 dies). ret 77 = $3.

Now, the target wants: `move $3,$2` then `beq $3,$0` then `andi $2,$3,0x8000`.

So if we eliminate the zero_extend (78) and make the branch test ret (77) directly, we get exactly the target! The zero_extend is the only extra.

So: can we write `u16 ret` such that the `ret == 0` test doesn't zero-extend? The zero_extend comes from promoting HImode to SImode for the comparison. If the comparison is done in HImode, gcc would use `beqz` on the HImode reg directly? Let's check: a HImode `(eq (reg:HI) (const_int 0))` — mips.md's branch patterns handle HImode? gcc might still extend. Hmm.

Actually, wait: the zero_extend exists because the comparison is SImode (gcc promotes HImode to int). What if we compare in a way that stays HImode? C always promotes. 

Alternative: make ret SImode but ensure the *definition* copy is untieable. The definition copy is `(set (reg:SI 74) (reg:SI 2 v0))` — combine_regs returns 0 for hard→pseudo (records a suggestion). The copy survives automatically! In win0 the copy DID survive as an RTL insn but was... wait, in win0 (natural), the .s showed no move: ret=v0. Let me re-check. The win0 diff showed mine[16] beqz v0 and andi v0,v0 — no move. But the RTL had insn 53 `(set (reg/v:SI 74) (reg:SI 2 v0))` with REG_DEAD v0. That insn would be a `move $2,$2`? gcc's local-alloc gives 74 the reg v0 (suggestion) and then the move becomes a self-move, deleted. Right: combine_regs records a copy suggestion; then allocation gives 74 = v0; the move is a no-op and removed.

In r16, the copy is `(set (reg:SI 77) (reg:SI 2 v0))` — 77 is HImode? No, 77 is SI (it's the full register holding the u16). The suggestion is still v0. Why did 77 get $3? Because 77 has more refs? Or because the zero_extend's pseudo 78 took $2? Hmm, in r16, 78 (zero_extend result) is allocated... Let's see: 78 has refs 2 (def + branch), live 2 insns → high priority; it's allocated first and takes $2. Then 77's copy suggestion v0 is taken → 77 gets $3.

So in r16, the reason ret got $3 is that the zero_extend pseudo 78 grabbed $2 first! That's a lucky artifact.

For the SImode case, if we introduce another pseudo that grabs $2 before ret... e.g., a pseudo with a copy suggestion to v0 and higher priority. Then ret would get $3 (or another). But the branch must test ret and the andi read ret. If ret gets $3 and another pseudo gets $2, then the andi output m could tie with ret ($3)... wait no, m ties with ret only if ret dies at the andi; in win0 they tied. Hmm, in win0: 74 and 75 tied, and 74 got v0 → both v0. If 74 got v1 (because v0 taken by another pseudo), then 75 would tie to 74 = v1, giving `andi v1,v1,0x8000` — not target.

Unless the tie at the andi is broken. In r16, the tie was broken because 77 (ret) was also used by the zero_extend at insn 57 — no wait, the REG_DEAD at insn 65 is still there.

Hmm, why didn't 75 tie with 77 at insn 65 in r16? Let me check combine_regs conditions: `reg_qty[sreg] >= -1` — sreg is 75 (the setreg). Hmm, the call is combine_regs(r1=77 usedreg, r0=75 setreg...). Wait, in the tie loop: `win = combine_regs (r1, r0, may_save_copy, ...)` where r1 = operand i (input 77), r0 = operand 0 (output 75). So usedreg=77, setreg=75.

Conditions: `reg_qty[ureg] < 0` → 77 has qty (born at 53), OK. `sreg >= FIRST_PSEUDO && reg_qty[sreg] == -1` → 75's qty must not be -1. If 75 was already given qty -1 (meaning "not allocatable")? Hmm, -1 means "not to be allocated"? Actually reg_qty values: -1 = not local to block? -2 = not yet born. 75 is born at insn 65; during the scan at insn 65, reg_is_born is called for the set? Let me check: in block_alloc's scan, before the tie loop it calls reg_is_set? Let me look at the surrounding code for how qty is assigned.

Actually the key condition `reg_qty[sreg] == -1`: if 75 was already "dead" (qty -1) at this point, no tie. Hmm.

Wait — maybe in r16, 75 is not tied because the andi's operand 0 constraint: andsi3 might have a `=r` constraint and the input `r`, fine.

Hmm, but there's another condition: `MODES_TIEABLE_P (GET_MODE (usedreg), GET_MODE (setreg))` — usedreg is `(reg:SI 77)` and setreg `(reg/v:SI 75)` — both SI. Tieable.

So why no tie in r16? Let me look at the block structure: in r16, the andi is at insn 65 in block 2, and 77's death at 65. Hmm, unless the REG_DEAD is `(expr_list:REG_DEAD (reg:SI 77) (nil))` attached to insn 65 — yes it is.

Hmm, wait: maybe 75's qty is not yet assigned at insn 65 because the set is processed after the tie loop? In block_alloc, the loop does the tie analysis and `reg_is_set`/`reg_is_born` handling. Let me read the part after the tie loop in the same insn iteration.
