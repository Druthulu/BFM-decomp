---
ts: 2026-11-06T22:57:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7xj9yyvybU3jHhJSONFw
---
In w4, insn 6 sets r73 (the parameter copy) from $a1 → r73 prefers a1. So even with arg1 direct, gcc creates a parameter copy at entry (because the parameter is used in multiple blocks / across a call). So d always gets the a1 preference.

Hmm. Can we avoid the parameter copy? The parameter is used across a call, so gcc copies it to a pseudo. If the source uses arg1 in a way that... hmm.

What if d = arg1 but we write `d = arg1 & 0xFFFF`? That changes the value (and the instructions).

What if we use arg1 only ONCE after the call and the copy is coalesced... The copy is needed because $a1 is clobbered by the call.

So the a1 preference on d is unavoidable with real C.

BUT: the div's expand_preferences merges d's preference into iVar4. What if the div is NOT a single_set (i.e., the mod part is NOT deleted)? Then no merge. The mod part is dead (REG_UNUSED) → flow deletes it. Could we make the mod part live? That would add instructions.

Hmm, what if the division is written differently so the div isn't a single_set? On MIPS, `/` generates divmodsi4. If the mod is used, it's a parallel with 2 sets (not single_set) → no merge! But using the mod adds an instruction.

Hmm, wait: is the mod really deleted? Let me check the w0 lreg div insn: it shows `(parallel [(set r79 (div r78 r74)) (set r103 (mod r78 r74)) (clobber ...)])` with REG_UNUSED r103. So the mod set is still there in the lreg dump (after flow?). If it's still there, single_set returns 0 → no merge. But the preference IS there. Hmm.

Wait, maybe expand_preferences runs on the RTL where the mod has been deleted? The lreg dump is after local-alloc, before global-alloc. The greg pass runs after. The div is a parallel in the lreg dump. So single_set = 0.

Hmm, so my theory is wrong? Let me re-check: single_set returns the set if there's exactly one SET and no other side effects (clobbers OK). The parallel has 2 sets → 0.

Unless... `expand_preferences` doesn't use single_set? It does (`(set = single_set (insn)) != 0`).

Hmm. So the div doesn't merge. Then where's the a1?

Let me look for OTHER single_set insns with REG_DEAD r74 (d). The REG_DEAD r74 appears only in the divs (parallels). Hmm.

Wait, maybe the REG_DEAD r74 in the div is on the *second* set? No.

Hmm, let me look at the actual RTL of the div more carefully: `(parallel [(set (reg/v:SI 79) (div:SI (reg/v:SI 78) (reg/v:SI 74))) (set (reg:SI 103) (mod:SI ...)) (clobber ...)])`. single_set = 0.

OK so the a1 preference on iVar4 must come from elsewhere. Let me look at the insns where r78 (iVar4) is a dying src with a single_set dest:
- insn 84: `(set r100 (lt r78 2049))` — REG_DEAD? Let me check: insn 84 sets r100 = lt(r78, 2049), no REG_DEAD shown. Hmm.
- The `bltz` (insn 104): `(if_then_else (lt r78 0))` — a jump, no set.
- insn 94: `(set r101 (lt r78 -2048))` — no REG_DEAD.

Hmm.

Let me look at w0's lreg insns 84-104 for REG_DEAD r78.

Actually, let me search the w0 function for "REG_DEAD (reg/v:SI 78)".
