---
ts: 2026-10-17T14:10:48.216Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm realizing that in v1 the pointer was hoisted to the top with absolute stores, while in v0 it stayed relative to its declaration since CSE couldn't see across blocks and there was no equivalence tracked due to the double assignment — meaning p's value was genuinely unknown at the store sites because it was set late.

I'm checking whether a branch separates the first and second lh loads — there isn't one, so I'm exploring whether p could be assigned from something CSE can't fold, like a static initializer or a call's return value, but those don't fit the real C code. The only way this makes sense is if p is set before a label (like after the guard's return), making it live across the calls and forcing it into a callee-saved register — which raises the question of whether the original dispatch is even passing the parameter through a0/s0 as I assumed.

Tracing the register assignments, I see the parameter does live in s0 through the jalr, and p's live range starts afterward — meaning both are in the same block with no intervening label, so CSE should know p is a constant and fold it. That makes me reconsider whether the fold actually happens in CSE itself versus combine or an equivalence-update pass, especially for the non-zero offset stores where a (plus reg const) address might just be cheaper than a (plus symbol const) one.

I'm now wondering what could hide the constant from CSE even with two sets and no REG_EQUIV note present — maybe it's a loop boundary, since cse_end_of_basic_block behaves differently when following jumps at NOTE_INSN_LOOP_BEG markers in this older GCC version.

I'm checking whether a `do {} while(0)` triggers that loop-note invalidation, but the earlier dw0 test case didn't break the address CSE there, so it probably doesn't apply. I'm also considering whether p's constant equivalence depends on where p is assigned — maybe reused from a parameter, or set from a dispatch call return — but none of these seem to fit, so this test case still looks like a dead end.

With about 6 of 40 minutes used, I want to try a few quick variations: a static/global pointer initialization, an index computation that folds to zero, or a pointer difference expression that CSE might collapse into a symbolic constant. The array-versus-individual-variable distinction seems irrelevant here.

I'm also wondering whether the stores used an explicit pointer variable for one axis while others used separate global symbols directly, which could explain why constant folding behaved differently for p in the original Psy-Q gcc build—maybe this came from an inlined function where the parameter became a pseudo that CSE could see through.

Trying several more variants: a volatile pointer declared on the stack, indexed offset stores, or integer-cast pointer arithmetic with OR'd offsets—all of these produce different byte patterns than the original, so none match.

I keep coming back to v0's score of 39 and v1b's 22 as my best leads, trying to combine v1b's non-bumped absolute stores with better scheduling to see if I can push the match higher.

Let me set up a systematic sweep: varying where initialization occurs (declaration, after dispatch, after index, after the first rotate), how the pointer gets bumped (in-place, plus-offset, or assigned inline in the argument), and which variable carries it (a local pointer vs. the a0 parameter) — that's 24 combinations to test.
