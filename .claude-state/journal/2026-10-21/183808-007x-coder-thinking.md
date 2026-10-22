---
ts: 2026-10-22T00:38:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_jDa2DH6mXDy1BX8ypPcR
---
This is a launder item. The comment already explains the whole mechanism: the launder through empty asm is needed to defeat cse address unification. This is a HARD case: the launder is "NEEDED". Removing the launder means the six &buf uses unify → extra callee-saved register → +3 ins.

But there might be alternatives: instead of laundering the address, use a different spelling that gives distinct pseudos. E.g., use `buf.mt` member address? Or take the address via a pointer variable that's re-assigned: e.g.

```
s32 *pbuf = (s32 *)&buf;
func_8012EA90(a0, ang, pbuf);  // pbuf used later? 
```

Hmm. The key issue: cse unify of `&buf` across 6 sites. To get distinct pseudos without asm, we can use different spellings of the address, e.g. `(s32)&buf.mt`, `(s32)&buf.mt.t[0]`, `(s32)&buf.rest[0]`, etc. But cse may unify those to the same base anyway.

Alternative: make the pointer a variable that gets loaded each time, e.g. `p = &buf; ... use p ... p = &buf; ...`. cse would treat re-assignments as invalidating? Actually cse's copy propagation: `p = &buf` then `p` used — cse may forward &buf into uses, unifying again.

Actually the moves.md shows many "launder" cracks achieved by "real 2nd set" — e.g. `pv = *p; pv &= mask` creates a real second set which kills the birth boost. And "pointer reuse" moves.

Here the mechanism is cse address unification with >2 refs. Hmm, but key (2) says: "Plain &buf everywhere makes cse unify all six into one pseudo with >2 refs, so local-alloc's remat path (which needs reg_n_refs==2) never fires and the address is parked in an extra callee-saved register (+3 ins, frame 0x70)."

So the goal: reduce the number of refs of the address pseudo to 2, or otherwise get remat. With 6 uses, we need to split the address into 2 uses each? That is: define 3 separate address expressions each used twice? Hmm, "remat path needs reg_n_refs == 2" — so each pseudo must have exactly 2 refs.

Alternatively use a distinct spelling for each of the 6 sites so cse doesn't unify them all into one — but the key says the FIRST site un-laundered survives in the cse table and later sites unify with it. If each site has a genuinely different expression (not foldable to the same), cse won't unify.

Hmm — but if we use `&buf` at one site and `&buf.mt` at another, does cse unify? `&buf.mt` would be (plus &buf, 0) which folds to &buf. Similarly `&buf.rest[0]` = &buf + 8.

Different approach: the launder for `ang` constant is the ordering lever (key 4). Removing it means the order issue. Hmm, but key (4) says "Launder the constant too (ang) so it is likewise pre-computed, at an earlier textual position — the two empty asms cost 0 bytes and the order flips to match." So without launder of ang, the residual might be 1-2 ins off.

Actually wait — do we need the whole thing? MATCH requires score 0, i.e. exact match with target asm. Let's first look at what the score is and how scoring works.

Let me look at the other items first to prioritize, and check the target asm. Let's understand the scoring: delever_search --try TU FN file --body; score 0 = MATCH.

Let me check the whole set of items quickly — 7 items. Let me look at each source function. But sources are big files. Let me get each function's def via grep.

Let me first check the sizes/difficulty of each. Let's grep the function definitions.

Actually, a critical question: what does the target asm look like (63 ins)? Let's find the target assembly for func_8018A180 in build/.

Let me check the build dir.

Let me set up: for each item, I need:
1. the current def in src (copy to <dir>/orig.c)
2. the target asm (for comparison)

Let me look at how delever_search scores to know what "score" means. Let me read its --help/README partially. Actually let's look for a doc. Let me check tools/delever_search.py header comment.

Let me be efficient with calls. I'll run a script to extract each function def from src into the item dir as orig.c.

But careful: "no python -c one-liners; scripts, not inline". I'll write a scratch script under .run/P40/T11/G15/ (allowed: write under shard dir). Actually scratch scripts should go under .run/ — the shard dir is fine, but must be removed later? "your shard dir stays < 200 MB" and "--keep scratch is removed after use". I'll write a helper script under .run/P40/T11/G15/_tools/ maybe. Hmm, "write only under .run/P40/T11/G15/ plus appends to moves.md". So helper scripts under G15/ are OK.

Let me write a small python script to extract function defs.

First, let me understand the score metric by looking at delever_search.py's scoring function.
