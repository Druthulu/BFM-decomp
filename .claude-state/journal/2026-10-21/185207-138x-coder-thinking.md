---
ts: 2026-10-22T00:52:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_673wg43WRRCgXnVMGPos
---
func_8017D96C (score 3): the differences are:
1. The `move v1,v0` is one slot later in mine (an ORDER difference).
2. `lh v1,32(s0)` vs `lw v1,32(s0)` — a *width* difference! The target loads a *word* (lw) at 32(s0) and mine loads a halfword (lh).

The 2nd difference is interesting: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` — unk20 is at offset 0x20 = 32. The target loads it as a *word* (lw) and mine as a halfword (lh)?! Hmm, that means in the target, `e` (used as a pointer: CAST_WIDTH(s32, e, 4)) is a word. Hmm, but the source has `e = ...->unk20` where unk20 is a pointer (s32) → a word load. Why would mine load a halfword?

Because of my cast! `e = (s16)e;` — the cast makes e an s16, so the later use `CAST_WIDTH(s32, e, 4)` loads... hmm, CAST_WIDTH(s32, e, 4) = *(s32*)(e + 4) — the *load* at 32(s0) is `e = unk20` (the field load) — hmm, s0 is the param, so 32(s0) is unk20 (offset 0x20). The target loads it with `lw` (a word) and mine with `lh` (a halfword)!

So in mine, the *value* loaded is used as a halfword — because the cast (s16)e made the compiler think only the low half matters? Hmm, that would be a *semantic* difference! The cast truncates e to 16 bits, and then the use `CAST_WIDTH(s32, e, 4)` (a pointer deref) uses the truncated value → the pointer would be wrong!

Hmm!! So the cast on `e` is NOT value-preserving: e is a *pointer* (unk20), and (s16)e truncates the pointer! That's a semantic change. Hmm!

But wait, in the *target* the load is `lw` (the full word) and in mine `lh` — so my version is broken (it loads only the low half of the pointer). Hmm, but the score is 3 (only 3 differences) — the tool compares instructions; the semantics differ but the instructions nearly match.

Hmm! That's a problem: the "MATCH" for this item via the cast would be semantically wrong. Hmm. But hold on — the score-3 variant is the dow+cast one; the difference `lh` vs `lw` means the instructions differ, so it's not a match anyway. Good.

But hmm, this makes me worry about the *other* cast-based matches:
- func_8017D73C: `n = (s16)n` where n ∈ {16,20} → value-preserving ✓ (n is a count, not a pointer).
- func_8017D9D8: `v0 = (s16)v0` where v0 = a sign-extended s16 field → value-preserving ✓.

OK good.

For func_8017D96C, the launders are on `v1` (the mode) and on `e` (a pointer!). The cast on e is not value-preserving → I must avoid casting e.

The first launder is on v1 (mode = the field & 3 → v1 ∈ {0,1,2,3}) → a cast (s16) on v1 is value-preserving ✓.

So let me try: the cast only on v1 (the first asm) + the do-while, and for the second asm (on e) something else. The combos replaced ALL asms with the cast → the e cast broke it.

Let me create per-asm variants: cast on the first asm only, do-while on the second, etc. Let me build a "per-position" combo generator: for each subset of positions, apply {dow} or {dow+cast}.

Since there are 2 asms → 4 combinations × (dow, dow+cast) per position → let me generate 2^2 × 2^2 = 16 combos + a few frame variants.

Let me write a generic "per-position" generator (posgen.py) that takes the item and produces variants where each asm position independently gets one of {dow, dow+cast(s16), dow+cast(u16), cast(s16), cast(u16), nothing}. For 2 asms: 6×6 = 36 variants. For 1 asm: 6. For many asms (12 in func_801813B0): 6^12 — too many; cap it.

Let me write posgen.py with a cap (e.g. all combinations if the product ≤ 64, else a sampled set).

Let me do that — it's the most promising general tool now.
