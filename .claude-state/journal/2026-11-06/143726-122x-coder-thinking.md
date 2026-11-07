---
ts: 2026-11-06T21:37:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7o3coA7Y2pfKf8zjcWsR
---
insn 20: s1ang loaded into s0. There's no explicit preference shown in the RTL; the "preferences: 16" comes from global-alloc's copy/preference analysis. Maybe from the fact that insn 20's result is used by insn 57 (andi) and the branch, and local-alloc had assigned s0 to the block-local version. Hmm.

Actually, the preference might come from `reg_preferred_class` or from a `REG_EQUAL`. Not worth chasing.

Practical approach: raise d's priority above 77's (10000). d's pri = refs*10000/live (roughly). d: 7 refs, live 27 → 2592? But the table says 5185, so maybe live is counted differently (loop-weighted). Anyway.

If I add a do-while around the divisions, d's refs increase by loop_depth per use. Let me check whether w5 actually changed d's refs. Let me dump w5 and check the alloc table. Quick: hdump w5.

Actually, let me try a more direct approach: make d's live range shorter. d is live from insn 6 to the divisions. If I move the `d = arg1` assignment later (just before the divisions), d's live range shortens → pri rises. But the target has `move s0,a1` early (prologue), so d must be assigned early. Hmm.

Alternatively, add refs: use d in the comparison? No.

Let me try the do-while with more nesting and check. Also try wrapping the whole post-call computation in a do-while.

Let me create variants:
- w10: w3 + `do { do { q = iVar4 / d; if (q == 0) q = 1; } while (0); } while (0);` in the >=0 arm, similar in else.
- w11: w3 + wrap the cast in a nested do-while.
- w12: w3 + wrap the entire body after the call in do-while.
- w13: w3 with `d` declared as the last variable (decl order).
- w14: w3 with `d` declared first (before s1ang).

Let me write these and score.

Actually, the func_8012BB3C note says "do-while(0) on the div block (refs 7->9) cracks the $16 pin (div=$s0)". So refs 7->9 was enough there. Our d has refs 7. Adding 2 refs → 9, pri = 9*10000/27 = 3333 < 10000. Still lower than 77. Hmm, but the formula might use live differently. In func_8012BB3C, div's live was shorter.

Wait, maybe I have the wrong variable. Let me reconsider: 77 (in s0) — is it s1ang or u6? insn 20 sets s0 = s1ang load. insn 57 sets s0 = s0 & 0xFFF (u6). So allocno 77 is s1ang AND u6 (they're the same pseudo? u6 = s1ang & 0xFFF, so u6 is a new pseudo). Hmm, insn 57 is `(set (reg/v:SI 16 s0) (and (reg/v:SI 16 s0) ...))` — in-place andi, so u6 and s1ang are the same allocno (s1ang is updated in place: `s1ang = s1ang & 0xFFF`? No, the C is `u6 = s1ang & 0xFFF;`). But the RTL shows in-place `s0 = s0 & 0xFFF`, meaning cse/combine merged u6 into s1ang (s1ang dead after). So allocno 77 = s1ang (dead after the andi), used in the compare.

So 77's live range: insn 20 (load) to insn 57 (andi) — 37 insns? But the table says live 10. Hmm, maybe the andi is near the compare.

Anyway, 77's pri 10000 (refs 5, live 10). d's pri 5185 (refs 7, live 27).

To beat 77, d needs pri > 10000. Since live 27 is fixed (d must live from prologue to divisions), d needs refs > 27. That's a lot of do-while nesting. Unlikely.

Alternative: lower 77's priority by increasing its live range. If s1ang's live range were longer (e.g., used after the divisions), its pri drops. But that changes the code.

Alternative: remove 77's preference for s0. If 77 had no preference, it might get s1 (lower allocno? 77 is allocated before 74, so 77 picks first among available: s0 or s1). With preference s0, it takes s0; without, it might take s1 (then d gets s0). How to remove the preference? The preference likely comes from local-alloc's assignment of s1ang to s0 in block 0 (before global). Hmm.

Actually, the `.greg order: 78 80 79 77 76 74` — 77 is allocated 4th, 74 6th. Available callee-saved at that point: s0, s1 (since 78,79,80 took v1,v1,v0; 76 took a0). 77 gets s0 (preference), 74 gets s1. If 77 had no preference, global-alloc's tie-break might still give it s0 (the first available). So the preference might not be decisive.

Hmm. To make d get s0, d must be allocated before 77. That needs d's pri > 77's (10000) or d's allocno number lower (tie-break: lower allocno wins). d is allocno 74, 77 is allocno 77. Lower allocno wins ties! But their priorities differ (5185 vs 10000), so 77 goes first.

If I can make d's priority equal or higher... Let me check the priority formula in global.c. In GCC 2.7.2, `allocno_priority` = `(floor_log2 (allocno_refs * 10000 / (allocno_live_length + 1)))`? Or `allocno_refs * 10000 / live_length`. Let me check global.c.

Actually, the alloc_table.py computes pri from the dump. Let me look at alloc_table.py's formula or the .greg dump's "Register N used ..." lines. The .lreg dump has "Register 74 used 7 times across 27 insns". The priority = refs * 10000 / live? 7*10000/27 = 2592, but table says 5185 ≈ 7*10000/13.5. Hmm, maybe live is halved or the formula is different.

Let me read global.c's priority computation. But this is a deep rabbit hole.

Given the time, let me consider: the PARTIAL:pin (w7) is a valid result. The brief says PARTIAL is acceptable. The MATCH would require cracking a global-alloc priority swap, which is a known wall family (lreg-qty-priority, global-pri-bank-order, global-pri-refs). 

But let me try a few more real-C moves before settling:
1. Add do-while nesting to raise d's refs.
2. Change d's declaration position.
3. Make s1ang's live range longer by reordering (e.g., compute u6 later).

Let me try the do-while nesting (w10) and check the alloc table.

Actually, a cleaner idea: make d's live range SHORTER by moving the `d = arg1` assignment later. But the target has it in the prologue. However, if the C assigns `d = arg1;` later (just before the cast), the prologue wouldn't have `move s0,a1`. The target has `move s0,a1` at position 3. So d must be assigned early.

What if we keep the early copy but make the *cast* the first use? The live range is from the copy to the last use. Can't shorten without moving uses.

Hmm. What if we split d into two variables: `d1 = arg1;` (early) and use d1 only in the divisions, with the cast on a separate variable? The target casts d (s0). 

Alternatively, make s1ang's priority lower by extending its live range: use s1ang again after the divisions? That adds code.

I think this is a global-alloc priority wall. Let me do a few quick tries, then record PARTIAL:pin.

Wait — actually, let me reconsider. The pin is $16 (s0). In w3, d gets s1 because 77 (s1ang) has higher priority. What if I change the C so s1ang is computed LATER (after the divisions)? The target computes s1ang before the call (lh s1,18(v0) at position 14). So it's early. Can't move.

What if I make d's priority higher by giving it more refs via real C? The do-while trick. Let me test if nested do-whiles change the alloc. Let me dump w5's alloc table quickly (it's cheap with hdump).

Let me dump w5.
