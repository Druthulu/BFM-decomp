---
ts: 2026-10-17T06:18:51.806Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0517ed1d1bb7f9bc
model: claude-opus-5-5[1m]
effort: medium
turnId: f9047d91-6ccc-4e9c-9be7-6616c974f0fb
---
These cast-calls likely live in a shared header for those two bodies, which tells me func_80149CB4's actual signature takes two parameters rather than one. This means the fix cascades up a level: I need to update the function's declaration to take both params and update all its callers' cast-calls to become plain calls instead—mechanical but affects one header broadly.

Rather than doing that by hand across 2179 declarations, I'm realizing rung D can handle this too: since the definition lives in a shared header and I'm not touching --all-defs, the signature rewrite tool should be able to update the header definition and cascade the declaration fixes across the includer binaries automatically. That's much cleaner than a manual sed job across the whole fleet—order matters though, since the callers need to pass the right two arguments once the body itself does.

But func_80157D20's own declaration in that header is still `(void)`, which breaks calling it with two arguments, and its real two-arg signature can't land until its own rung D pass runs—creating a circular dependency. I'm resolving this by using an interim K&R-style untyped declaration as a bridge: hand-edit func_80149CB4.h to declare func_80157D20 with no fixed parameter list and write its body to just forward the call, treating this cascade fix as a caller-side edit similar to how the func_801A6A18 cascade was handled previously.

Now I need to check whether the 2179 existing `(void)` declarations of func_80149CB4 scattered across roughly 1300 files will conflict with the new two-parameter definition—since declaring it as void but defining it with two parameters in the same translation unit is a type mismatch. I'm considering a fleet-wide sed replacement of those declarations to match the new signature, but first I need to verify all 2179 instances actually refer to this same function rather than a different one at the same overlay slot in other binaries.

I'm weighing whether to use the signature-scoped rewrite tool for func_80149CB4, since it handles declaration rewrites within scope and logs anything out of scope, but I also need the body itself to pass through the new arguments, which requires the broader body-rewrite option rather than just the header-only pass.

Mapping out the plan: first K&R-normalize the void-style declarations of func_80157D20 and the two header definitions down to plain `()`, leaving the two-parameter declarations untouched since both can coexist in the same translation unit. Then I'll handle the cast-calls to func_80149CB4 as a follow-up batch once its signature rung is applied, converting them to plain calls alongside the caller edits.

I'm then running rung D on the two header definitions, verifying the body passthrough is unaffected since argument handling stays the same, and applying rung D to the remaining binaries so their K&R declarations become proper prototypes — followed by manually aligning any leftover K&R declarations elsewhere to match the two-parameter form, then repeating the same approach for func_80168828.

Since func_801691B8.h's binaries are a subset, I'll rewrite it too. While waiting on the background work, I'll start preparing batch 2 analysis covering more names: main at 80029E30, 800CC024, 800CD1A8, 800CCD50 (md SET cases), 80182998, 80182334, 8017F258, 80180ED4, 80151664 (shared), and 80181B14.
