---
ts: 2026-11-06T06:17:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_AoDeGKwJPFdl6o5NSwX1
---
Excellent! Score dropped 74 → 11, and now a0 is in $16 (s0) matching. Remaining: mine s1→target s2 x11, mine s2→target s1 x3. That's the loopptr/ent swap I predicted: mine loopptr=$17(s1), ent=$18(s2); target loopptr=$18(s2), ent=$17(s1).

So I need loopptr priority below ent's (2500). Currently loopptr pri 7714 (9 refs, live 35). Options:
1. Increase ent's refs above loopptr: ent needs 5 refs at live 12 (8333) — but adding refs changes code? The `ent` variable could be used more, e.g., `ent` recomputed... Hmm.
2. Decrease loopptr's refs. loopptr is `s2` with 9 refs. Hmm.

Wait — actually, what about live length? Let me recompute with the current candidate: dump again and see the actual priorities now. The address pseudo is gone, so maybe live lengths changed.

Let me re-dump with the new candidate.

Actually, cheaper: let me reason about what plain-C shapes could shift these.

Observation: ent = (s16 *)(s2 + 2) — a *derived* pointer. If instead the code used `s2 + 2` inline at both call sites (no ent variable), then:
- refs to s2 increase (+2), and a new temp would be created for each call arg.
Target's code has `addiu s1,s2,4` — ent in $17. So ent exists as a register in the target.

Alternatively, make ent's live range shorter? ent live 12 with 3 refs → 2500. If ent's live length were 9: 1*3/9*1e4=3333 > 2500. Hmm, ent is born at `addiu s1,s2,4` and dies at the second call.

Alternatively increase ent's refs by one: 4 refs, live 12 → floor_log2(4)=2 → 2*4/12*1e4 = 6667 < 7714. Still less. 5 refs → 8333 > 7714. So ent needs 5 refs (from 3).

Hmm, adding 2 refs to ent in real C... e.g., `ent[0]` read? That would add an instruction.

Other direction: lower loopptr. 9 refs/35 live. If live were 40: 3*9/40*1e4 = 6750 — still > 2500. Need live > 108 or refs 4.

Reduce refs: `s2 += 0x86` + test = the loop increment/test. What if the loop is rewritten so s2 is used fewer times? E.g., the comparison `s2 != s5` happens twice (entry test and loop end). Could write the loop as a for? Hmm.

Alternative: what if the loop pointer and end pointer are compared differently... 

Hold on. Let me reconsider: is the target's ent really $17? In the target the pin is on s2 = $18, so global-alloc assigned a0→$16 (pri 19178), ent→$17 (2500), loopptr pinned $18. So yes.

So in the target, without the pin, the allocator would have given loopptr $17 and ent $18 — but the pin reserved $18 for loopptr, so ent got $17. Meaning: the pin is load-bearing for the ent/loopptr *order*, and we need a plain-C way to get loopptr into $18.

Options:
(a) Give loopptr a *lower* priority than ent.
(b) Make ent take $17 by copy preference: ent could prefer $17? No.
(c) Change the loop so the loop pointer variable has a longer live length.

What if the loop pointer variable s2 is used *outside* the loop too, extending its live length? Not really; it's assigned right before.

What about: declare the loop pointer as a different variable that's also used for the `unkCC = (s32)s2` store... already.

Hmm, what about making s5 (the end pointer) the loop pointer and s2 the increment... no.

Let me look at the actual refs count: 9 refs, live 35. What if the code used `s2` in a way that increases live length without adding instructions? Live length counts insns where it's live: from first def to last use. Currently 35.

Alternatively, make ent's live range shorter so its priority rises: ent 3 refs live 12 → 2500. If live 9 → 3333; still < 7714.

To beat 7714 with 3 refs: 3/live*1e4 > 7714 → live < 3.9. Impossible (ent has 3 refs so live ≥ 3; at live 3: 1*3/3*1e4 = 10000 > 7714!). But live 3 means the two call uses are adjacent — no.

With 4 refs: 2*4/live*1e4 > 7714 → live < 10.4. Possible if ent's life is ≤ 10 insns.
With 5 refs: live < 13.
With 6 refs: 2*6/live → live < 15.6.

Currently ent live = 12. With 5 refs, pri = 8333 > 7714 → ent gets $17. So adding 2 refs to ent, keeping live 12, works.

But how to add refs without changing the instruction sequence? A ref must be a real use in the RTL that combine/cse doesn't delete. E.g., `ent` used in a third call? No.

Hmm, what about reducing loopptr's refs? 9 refs at live 35. Refs come from each mention. Let me look at the RTL: s2's uses:
1. `s2 = (u16*)D_801202A0` (set)
2. `s5 = s2 + 0x3240` (use)
3. `if (s2 != s5)` (use)
4. `ent = (s16*)(s2+2)` (use)
5. `*s2 == 0xF2` (use)
6. `unkCC = (s32)s2` (use)
7. `s2 += 0x86` (use + set = 2 refs)
8. `if (s2 != s5)` (use)

That's 9 refs (set counts as 1, s2 += 0x86 counts 2).

If the increment were written as `s2 = s2 + 0x86` — same. 

What if the loop uses a *different* variable for the address, e.g. iterate over an index? Then the loop pointer register would be different.

Hmm, alternatively: what if we make the loop *not* weighted (goto already) but extend live length by moving the `s5 = s2 + 0x3240` computation earlier? Live length = number of insns from first to last live. Moving the initialization earlier extends it. E.g., compute s5 at the top of the function? Then live = whole function ~200 → pri = 3*9/200*1e4 = 1350 < 2500. That would put loopptr below ent! And ent (2500) > 1350 → ent $17, loopptr $18.

But moving `s5 = s2 + 0x3240` earlier changes the instruction order/schedule — the target has `lui s2; addiu s2; addiu s5,s2,25728` right there in the block. So moving it earlier would produce different insns. Not good.

Alternatively extend loopptr's live length by... hmm.

OK, different idea: increase ent's refs by 2 in a way that produces no extra instructions. For example, if `ent` is used as the arg to *three* calls instead of two? No, only two calls take it.

What about the second call `func_8012B6D4((s16 *)s3, ent)`: the `(s16 *)s3` cast. If instead we pass `ent`... no, semantics.

Hmm, what about making ent a *u16 pointer* and casting at use: `u16 *ent = s2 + 1;` then `func_8012BC60((void*)s3, (void*)ent)` and `func_8012B6D4((s16*)s3, (s16*)ent)` — each cast is a no-op in the RTL, so refs stay 3.

What about using ent in the `*s2 == 0xF2` test? E.g., `if (ent[-1] == 0xF2)`? That's the same load, but reads via ent → ent gets a ref, and s2 loses one! Actually `*(s2)` becomes `ent[-1]` = load at (s2+2)-2 = s2. Same address, same insn (lhu 0(s2)). But then s2's ref count drops by 1 and ent's rises by 1. Hmm, but the address computation `ent = s2+2` still exists.

Actually wait — would gcc compute `ent[-1]` as (ent-2) or fold to s2? ent = s2+2, so ent[-1] = s2. In RTL after cse it's the same MEM. The refs would be attributed to the pseudo in the RTL: if the RTL is `(mem (plus (reg ent) (const -2)))` then ent has a ref. But cse might fold it back.

Hmm, this is getting deep. Let me instead check the actual current priorities by dumping the new candidate. It's cheap and gives exact numbers.
