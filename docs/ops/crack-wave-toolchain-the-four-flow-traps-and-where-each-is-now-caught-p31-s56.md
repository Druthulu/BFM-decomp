### Crack-wave toolchain — the four flow traps, and where each is now caught (P31 S56)

Every one of these was a capability that was **silently off**: the tool ran, exited zero, and
reported a true number about a scope narrower than the caller believed. None was found by the
byte-gate, because the byte-gate is a perfect correctness oracle and a null coverage oracle (R34).
Each now asserts its own coverage (R32) or cannot be mis-called (R33).

| trap | what it cost | where it is caught NOW |
|---|---|---|
| **`wave_snapshot.py` assumed `asm/<bin>/nonmatchings/<bin>/`** — right only for single-TU binaries; every split-TU overlay lives under its own TU stem. Found 9 of 75 wave-Z targets. Its R32 assertion fired correctly, so the snapshot step got hand-rolled instead — **and the S46 validity gate living inside it came off the path for waves T–Z.** | 6 waves ran with no phantom-target check | `wave_snapshot` now honors the card's `sub` (then the old convention, then a single-hit glob). NC: 9/9 legacy targets byte-identical, 66/66 split-TU recovered. |
| **The S46 validity gate was only reachable through the snapshot step.** Its own comment says "a gate that is a separate command is a gate someone forgets" — and then a path bug forgot it. | S46 measured ~29 phantom targets × 3 tiers = 87 wasted agents, 9.7M tokens | Wired into **`build_wave_atlas`**, where cards are BORN, with an `--allow-invalid` escape. `validate_targets._key` also accepts the card spelling `fn` (it knew only `name`/`n`, so every card-shaped dict silently read MALFORMED). |
| **`family_sweep --hseq --only` is keyed on the FAMILY EXEMPLAR address**, but the natural thing to pass after a wave is the addresses you just banked — which are family *members*. Strictly keyed, that selects almost nothing and reports success. | wave Z: 15 addrs → 2 families → **3 banked**. Re-derived through membership: 21 families / 196 open members → **50 banked**. A 17× miss that looked like work. | `--only` now resolves member addrs to their family, **always prints the coverage line** (`N addrs -> M families, K unresolved`), and REFUSES when it resolves to zero families. |
| **`decl_prior._ASM_SYM`'s leading `\b` bound to the whole alternation**, demanding a word boundary before `%` — impossible in a `.s`, where that position follows a space. The `%hi/%lo` arm had **never fired**: the card's promised GLOBAL-TYPE row was 0 of 1,210 across four waves. | four waves of cards missing every data-symbol prior | Fixed (cookbook §204-E). NC over 75 wave-Z targets: `jal` 306 → 306 **zero regressions**, data **0 → 299** symbols recovered. |

**A fifth, in the banking driver rather than the wave tools:** when two slate-mates share a typedef,
`harvest_verify.strip_provided_typedefs` drops the duplicate from both drafts and the one surviving
definition sits wherever its owner splices — so if the *other* function is earlier in ADDRESS order,
its externs reference a type the file has not defined yet (`parse error before '<symbol>'`, which
reads like a codegen residual). `pregate_check` modelled the driver faithfully but never checked the
consequence; it now reports `[DROP-RISK] §203 USE-BEFORE-TYPEDEF` with the fix (hoist to the top of
the TU — never rename in one draft, which gives one symbol two types and just moves the failure).
NC: flags the known-bad pre-hoist splice, 0 false positives on the post-hoist file and on all 7 other
wave-Z TUs (the first draft of the check read a typedef named in its own *comment* as a use — it now
searches a comment-blanked copy with offsets preserved).

**The standing lesson for this flow:** after any wave step that reports a count, ask what
denominator that count is a fraction of. `3 banked` and `50 banked` were the same tool, same tree,
same day — the only difference was whether the scope was asserted.


