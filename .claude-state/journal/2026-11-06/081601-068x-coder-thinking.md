---
ts: 2026-11-06T15:16:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_upWWuRNqIHPcPKM7OYli
---
All still fold — the front end removes the no-op set before cse.

So the value-preserving set doesn't survive. g1 (compare a1) is the only near-crack (score 1) but the register differs.

Let me think about g1 more: `if (a1 != 3)`. The register allocation put a1 in s1 (callee-saved) because a1 is live from function entry (the parameter) across... wait, a1 is the second parameter; it's used at the start `if ((s16)a1 != 0)` and in case 5. In the target, a1 is in v0 (caller-saved) — hmm, v0 holds a1 at 6d8? Let me check the prologue: at 5d0 `bnez v0` ... Actually let me look at the function start.

The target's `sra s0,v0,0x10` at 6d8: v0 = a1's register at that point. So the compiler put a1 in v0. In g1, comparing a1 against 3 keeps a1 live through the branch → gcc put it in s1 (callee-saved) because it's live across the calls in the earlier cases? Hmm.

Wait — a1 is used in many cases; the function is big. The register holding a1 must be callee-saved if live across calls. In the target, a1 is in v0 which is caller-saved — so a1 is NOT live across calls in the target; it's re-loaded? No — a1 is a parameter, used at various points. Let me check: the function uses `a1` in case 1,2 (`(s16)a1 != 0`), case 3, case 4, case 5, case 6, case 7, case 9, case 0. Those are in different switch arms; a1 is live across the whole switch (from entry to whichever arm). But there are calls in the arms... Since a1 is used after calls? In case 5: `t = (s16)a1` happens before the calls in that arm. In case 9: `b = D_801CD9A4[(s16)a1]` before the call. So a1 might not be live across any call — each arm uses it early. So gcc could put a1 in v0 (caller-saved) if its live range doesn't cross a call.

In g1, the compare `a1 != 3` is placed *after* the `func_800291B4` call? No — the compare is before sel_094's call. Hmm, but the t==5 test and the t!=3 test are before any call in that arm. Wait, the branch at 704 comes before the jal at 71c. So a1's live range extends to 704, still before the call. Why s1 then?

Because in g1, a1's live range now extends into the `if (t==5)` block, which is *after* the earlier `if (t == 0)` path... no calls there either. Hmm.

Maybe because a1 is live across the `func_800291B4` call in *another* case arm, and the register allocator assigns one register for a1's whole live range across the switch (it's live from entry to each use; uses in different arms). If a1 is live at a point where a call happens (e.g., in case 5's later code `func_800291B4(D_80183478[t])` — a1 is used after? No). Hmm, but a1 is live across the entire switch (any arm may use it), including arms with calls before the use? Let me check case 9: `b = D_801CD9A4[(s16)a1]; if ((func_800291B4(b + 0x62) & 0x40) == 0)` — a1 used before the call. Case 7: `r = func_8014168C(1); ... D_801CD870 = ((r+1)<<8)|(a1+1);` — a1 used AFTER the call! So a1 IS live across a call in case 7. Therefore a1 must be in a callee-saved register in both target and mine!

But the target's `sra s0,v0,0x10` — v0 there might not be a1; maybe a1 was copied to v0 earlier? Hmm, at 5d0 `bnez v0` — let me look at the prologue.

Let me dump the target's first 40 instructions.
