---
ts: 2026-11-06T22:47:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5KWEA6XDLmVUZ1IGjbrc
---
21 minutes elapsed. I've done about 10-12 scored tries. I need ≥30 for a WALL, and ideally a MATCH.

Let me reconsider. The w6 mask-in-place + do-while gives d=$s0 and s1ang=$s1, with u5=$v1 and iVar4=$a1. The target wants u5=$a0, iVar4=$v1.

The difference is the preference on iVar4 for a1. If I can eliminate that preference, the target's allocation should follow.

Where does the preference come from? Let me look at expand_preferences more carefully — the merge is:
```
if (REG_NOTE_KIND == REG_DEAD && GET_CODE(XEXP(link,0)) == REG && reg_allocno[src] >= 0 && !CONFLICT)
```
For insn 100: dest r77 (iVar4), dying r76 (u5) and r79 (t). It merges iVar4's prefs with u5's and t's.

u5 (r76) = (and r99 4095) at insn 52, with REG_DEAD r99. r99 = (plus $v0 -1024) at insn 51. r99 is an allocno? r99 is a local pseudo? Let me check: r99 "used 2 times across 2 insns in block 0" — local-alloc'd to $v0. So reg_allocno[r99] = -1 → no merge.

t (r79) = (plus r75 4096) at insn 88, no REG_DEAD; at insn 98 `(set r79 (plus r75 -4096))` with REG_DEAD r75 (s1ang, local) → no merge.

So iVar4's prefs come from u5 and t — both none. Then why a1?

Unless the merge is with a *hard reg* that's an allocno? No.

Hmm, maybe I have the wrong insn. Let me look at the w0 function's insns 100 and the REG_DEAD notes. In w0, insn 100 is `(set r78 (minus r76 r77))` with REG_DEAD r76 and r77. r77 = u6 (allocno, prefers s0). So iVar4 (r78) should merge s0's preference. But the dump says a1!

Wait, unless the order of expand_preferences matters: it iterates insns in order and merges iteratively. The merge is symmetric (IOR both ways). So iVar4 and u6 merge their preference sets → iVar4 gets s0 and u6 gets whatever iVar4 has.

Where would a1 come from in this connected component? Maybe from another allocno connected via a chain: u6 (r77) is set by `(set r77 (and r75 4095))` with REG_DEAD r75 (local) → no. Hmm.

I'm clearly missing a merge. Let me just instrument: I could write a small script to simulate expand_preferences on the lreg dump? That's too much.

ALTERNATIVE PLAN: Accept that the preference exists and find a C formulation where iVar4 doesn't have it. Since the preference propagates through REG_DEAD merges in expand_preferences, and the target has none, maybe the target's chain is broken because d is pinned (r74 not an allocno) — but the merge that gives a1 must involve r74.

Let me test the hypothesis: if r74 (d) is the source of the a1 preference, then making d NOT a copy from $a1 would break it. In w4, d = arg1 directly (the parameter pseudo r73). The greg showed r77 prefers a1 too. But maybe the parameter pseudo's copy at entry (r73 = $a1 implicit) sets the preference.

Hmm, what if d is initialized from arg1 through an intermediate that isn't a hard reg? Like `d = arg1 + 0`? That would add an instruction.

What if we load d from a memory location? No.

Hmm, what if the cast `d = (s16)d` is moved to the top (right after d = arg1)? Then the copy chain: d = (s16)arg1 → sll/sra. The preference for a1 would be set on the temp, not d. But the instruction order changes (the sll at entry instead of after the call). Unless... hmm, the target has the sll after the call.

OK, let me try a different tack: maybe the u5/iVar4 assignment can be fixed by raising u5's priority above iVar4. In the target, iVar4 (30000) is first and gets $v1 (no preference); u5 (7142) gets $a0. In w6, iVar4 (30000) first, prefers a1 → $a1; u5 (7142) → $v1.

If u5 had a preference for $a0, it might get it even after iVar4. Preferences win over the alloc order? In find_reg, the preferred regs are tried first. So if u5 preferred $a0, it would get $a0.

Where could u5 get a preference for $a0? u5 = (ratan2(...) - 0x400) & 0xFFF. If we write it so that the value is set from a hard reg $a0... Hmm, the ratan2 call's result is in $v0. No.

What if u5 is computed as `arg0 - something`? No.

Hmm.

What about making iVar4 NOT the first in the .greg order, so u5 is allocated before iVar4? If u5 (7142) were allocated first, it'd take $v0? (prefers v0, but v0 is taken by r99/r80...). Hmm.

This is getting really hard. Let me consider the possibility that this is genuinely a WALL and I should record it with ≥30 tries. But the brief says W50x already walled it as PARTIAL:pin. My job is to try to crack it. If I can't, I record a WALL with the best lever-free score.

The best lever-free score so far: w6 = 38 (but with d/s1ang correct!), w7 = 33, w0 = 38. Wait, w7 = 33 is the best! Let me double check: w7 (mask-in-place, no do-while) = 33, 74 ins. Hmm, the WALL row's "best = lowest score of a lever-free body".

But wait, I need to be careful: the WALL must be lever-free (no pins/keepalives). w7 is lever-free. Score 33.

Hmm, but before giving up, let me try a few more variants:
1. w8: mask-in-place + do-while but with the u6 variable kept for the compare (maybe the preference chain changes).
2. w9: separate the divisor into a different form.
3. w10: reorder declarations.
4. Try `s16 s1ang`.
5. Try the div do-while (C0535) on the div block as in func_8012BB3C.

Actually, the sibling func_8012BB3C (line 316) cracked its pin with "do-while(0) on the div block (refs 7->9)". Let me look at its win.c to see the exact move.
