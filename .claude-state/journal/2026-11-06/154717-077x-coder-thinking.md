---
ts: 2026-11-06T22:47:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_YqWsOXPzaNoLFB8y3tFJ
---
REG_DEAD r74 appears at lines 232 (the div parallel), 355, 398 (the second div parallel). All parallels.

So the a1 preference on r77 doesn't come from r74.

Hmm, let me reconsider. Maybe the preference comes from the `hard_reg_full_preferences` being merged via `expand_preferences` where the dest is r77 and the dying src is r79, and r79's preference is from r75 (s1ang), and s1ang's preference is... Let me check: is there an insn setting s1ang (r75) from a hard reg? s1ang = `lh` (extendhisi2) — no.

Hmm, wait: maybe the a1 preference comes from the *mask-in-place* insn: `(set r75 (and r75 4095))`. set_preference(r75, and) → src is an AND, not a reg → no.

OK, I'm burning too much time on the mechanism. Let me instead test the hypothesis empirically: if I remove the preference, does the score improve? I can't directly remove preferences via C.

But here's an idea: the preference a1 on iVar4 comes from a merge chain involving s1ang (r75). s1ang crosses the call and its preference might be a1 because... hmm.

Alternatively, maybe the preference is a *consequence* of the do-while/mask-in-place and not fundamental. In the target, iVar4 has no preference.

Let me test: what if I use a different variable for the mask (keep u6) so the merge chain differs? E.g., w8 = mask-in-place but with the compare/arms using a separate variable u6 that is a copy of s1ang after the mask:
```
s1ang = s1ang & 0xFFF;   // reassign (globalises)
u6 = s1ang;              // copy (coalesced)
if (u6 == u5) return 0;
...
```
Hmm, the copy might be coalesced.

Actually, let me look at the target's RTL for iVar4's preference: none. In the pinned build, d is pinned so r74 doesn't exist as an allocno; the preferences are different.

Hmm, hold on. Let me reconsider the problem completely. What if the preference is caused by the *mask-in-place* changing the merge chain? Let me check w0 (u6, no mask-in-place): "78 preferences: 5" (iVar4 prefers a1). So w0 also has it. And the target (pin) has no preference on iVar4.

In w0, the chain: s1ang (r75) is local (not an allocno) → its preferences don't merge into global allocnos? Actually expand_preferences only merges allocnos (reg_allocno >= 0). r75 is local → reg_allocno[r75] = -1? Hmm, local pseudos are allocated by local-alloc; in global-alloc they have reg_renumber set (hard reg) → reg_allocno = -1.

So in w0, the merge chain for iVar4: insn 100 `(set r78 (minus r76 r77))` REG_DEAD r76 (u5) and r77 (u6). u6 (r77) is a global allocno. So iVar4 merges with u6's preferences. u6 prefers s0 (from its tie with s1ang? "77 preferences: 16"). Hmm, so iVar4 would prefer s0, not a1.

Wait, w0's greg: "78 preferences: 5" and "79 preferences: 5". Hmm.

Let me look at w0's greg dump preferences directly.
