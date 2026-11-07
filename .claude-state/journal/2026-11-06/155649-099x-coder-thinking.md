---
ts: 2026-11-06T22:56:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fGOJsGmWor4Iu5WE1PDI
---
Now I have 31 scored tries. The best lever-free score is 25 (w19, s16 d) — but that's structurally different. Among the "faithful" bodies, w7 = 33.

Hmm, wait. Let me reconsider the WALL criteria: "WALL (best = lowest score of a lever-free body)". So the best is 25 (w19).

But actually, before I wall it, let me reconsider one more idea that might crack it: the u5/iVar4 shift in w6. Let me check whether the shift is really caused by the a1 preference, and whether making iVar4 not prefer a1 is possible via a source change that keeps the insns.

Hmm, actually, let me look at the w6 target-diff again: the register pairs were "a1->v1 x20, v1->a0 x5, v0->s0 x2". So mine: a1 where target v1 (20 occurrences = iVar4/q), v1 where target a0 (5 = u5), v0 where target s0 (2 = ?).

The v0->s0 x2: mine has v0 where the target has s0. That's probably the arg0 copy (mine $v0 vs target... no). Hmm.

OK. Let me make a final decision: record a WALL with best 25 (w19). But wait — is w19 a legitimate lever-free body? It changes `s32 d` to `s16 d`, which changes the semantics (d truncated at assignment, and each div sign-extends). The score is 25. The WALL's "best" should be the lowest score of a lever-free body — yes.

Hmm, but I worry the expert would prefer the "faithful" best (w7=33 or w0=38). The results row format: `dir file func kinds result best tries wall evidence`. For WALL, best = lowest score of a lever-free body. I'll report best 25 and mention the faithful best 33 in the evidence? The evidence is ≤140 chars: "gcc pass + mechanism". Let me put the mechanism.

Actually, hold on. Let me reconsider w19: is it really lever-free? Yes, no pins/asm. It's a width move (C0505 catalog: s16/u8 widths). So it's legitimate.

Hmm, but the score 25 might be misleading (the s16 changes the div to sign-extend each time). Let me double-check w19's diff: it has `sll v0,s1,0x10; sra v0,v0,0x10; div ... v0` — the div operand differs. The score counts the differing instructions. It's not a match.

OK, let me now decide: WALL. But the brief's expectation was to try to crack it. I've done 31 tries. Let me do a couple more high-value attempts, then wall.

One more idea: the target's u5=$a0 and iVar4=$v1. In w6, u5=$v1 and iVar4=$a1. The .greg order w6: iVar4 (30000) → a1; r79 (20000) → v0; r78 (17500) → a1; d (10000) → s0; u5 (7142) → v1; s1ang (6363) → s1.

If iVar4 didn't prefer a1, it would take $v0 (first free)? But $v0 is taken by r99 (40000, the call result temp). Hmm, r99 = $v0 (40000, 4 refs/2 live, block 0). So iVar4 would take $v1. Then u5 would take $a0. That matches the target!

So the ONLY blocker is iVar4's a1 preference. If I can eliminate it...

The preference a1 on iVar4. Let me think about `expand_preferences` again with the correct understanding: the RTL at global-alloc time has local pseudos renumbered to hard regs. The `d = arg1` insn: d is a global pseudo (r74), arg1 is $a1 → set_preference(r74, $a1) → r74 prefers a1.

Then expand_preferences: for each insn with a single_set dest that's an allocno and a REG_DEAD src that's an allocno:
- insn 81: `(set r77 (minus r76 r75))` no REG_DEAD (r75 is local→hard $s0, and the note may be REG_DEAD $s0).
- insn 90: `(set r77 (minus r76 r79))` REG_DEAD r79 (allocno) → merge r77↔r79.
- insn 100: `(set r77 (minus r76 r79))` REG_DEAD r76, r79 → merge.

So r77 gets r79's prefs. r79 (t): `(set r79 (plus r75 4096))` — r75 is now a hard reg ($s0) → no allocno. Hmm.

Hmm, so where does r79 get v0? "79 preferences: 2". Hmm.

Wait, maybe the r75 in insn 88/98 is NOT renumbered because s1ang is global? In w0, s1ang is local → renumbered to $s0. So r75 doesn't exist as a pseudo in the global pass.

Hmm, so r79's v0 preference comes from... the `plus` src? set_preference(r79, plus) → no.

I'm stuck. Let me try an empirical approach: if the a1 preference on iVar4 comes from `d = arg1`, then removing the d copy should remove it. w4 (arg1 direct) — did it have the preference? Yes, r77 prefers a1. Hmm, but in w4, the divisor is the parameter pseudo (r73). Where's the a1 preference from then? The parameter's initial assignment... maybe gcc sets a preference for the parameter's incoming hard reg.

Hmm, in w4, `d` doesn't exist; arg1 is the parameter pseudo. At entry, the parameter is in $a1. Is there an insn `(set r73 (reg $a1))`? The parameter's RTL is just `(reg r73)` used directly; no copy. So no set_preference. Yet r77 prefers a1.

So the a1 preference does NOT come from d = arg1! It comes from somewhere else entirely.

Where else is $a1 used? The call: `subu $5,$3,$5` sets $a1 from a minus. Hmm, set_preference($a1, minus) → src is minus, not a reg → no.

Hmm, what about the `lh $5,6($2)` (extendhisi2 into $a1)? That's `(set (reg $a1) (sign_extend (mem)))`. set_preference($a1, sign_extend) → src is sign_extend, not a REG → no.

Hmm. But wait — maybe `set_preference` is called with the src being the *mem*? No, GET_CODE(src) == MEM → return.

I'm really stuck on the mechanism. Let me try gdb or a debug print? That's heavy.

Alternative empirical test: does the a1 preference disappear if I remove the call's second argument? No, can't change the function.

Hmm, let me try: what if the a1 preference comes from the REG_DEAD merge at the *call* insn? The call is a parallel with a single set ($v0 = call) and a clobber $ra. single_set returns the v0 set (clobbers ignored). dest = $v0 (hard) → set_preference($v0, call) → no. The REG_DEAD notes on the call: $a0, $a1 (the arguments die). expand_preferences: the condition requires `GET_CODE(SET_DEST(set)) == REG && reg_allocno[dest] >= 0` — dest is $v0 (hard) → reg_allocno[$v0] < 0 → skip. So no.

Hmm.

What about the insn `(set (reg $a1) (minus ...))` at insn 45: mark_reg_set is called with setter → set_preference($a1, minus) → src minus → no. But mark_reg_set also handles the hard reg $a1's liveness.

Hmm.

Let me look at the w0 greg dump's preference lines again: "77 preferences: 16", "78 preferences: 5", "79 preferences: 5", "80 preferences: 2". 

r80 (4 refs/4, prefers v0) — what is r80? It's the pseudo that's 4 refs/4 insns. Hmm, maybe the pointer or a call arg.

r80 prefers v0. Where from? set_preference(r80, ...) from a hard reg $v0. The call result! Maybe `(set r80 (reg $v0))` — a copy of the call result. Hmm.

OK, let me look at the w0 lreg for r80.
