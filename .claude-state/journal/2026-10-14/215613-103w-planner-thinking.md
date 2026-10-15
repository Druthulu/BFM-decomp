---
ts: 2026-10-15T03:56:13.748Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7df908b0d85c75d2
model: claude-opus-5-5[1m]
effort: high
turnId: 76dfb9f8-086c-49db-b4bc-a2c84ee77998
---
I'm drafting the task list now, starting with phase-start health checks and carry cleanup, then moving into canonical-types work—first a pilot on the top 75 types, then the remaining map types in batched passes—followed by rung S re-sweeps of overlays and md files.

Then I lay out legacy declaration items and lying exceptions, missing-parameter pins into declared parameters, and oracle re-judging alongside mechanical lever classes, then head-class cracks with propagation, a singleton crack pilot as a checkpoint before the full wave, and finally the timeline series, milestone gate, and phase-close docs. I'm working out ordering dependencies—putting the timeline task early so later snapshots capture progress, splitting named items from the rest of the missing-parameter work, and sequencing lever tasks after the type work since rung S respelling could shift keys that the lever residue matches against.

Since lever cracks touch bodies rather than sites, I note that cracking can trip the per-site cast residue gate and force a re-run with the residue check, so I'm mapping out the full dependency chain—types before levers, levers before head-class work, pilot before the full wave, and everything gating the final milestone and close. I also sketch the verification commands for both the type census and lever census checks, and note the residue TSV needs to be rewritten after removals.

I'm now pinning down the exact interface surfaces in lever_census.py — the argparse setup, the strict return code logic, the strict_failures computation (ab plus direct_gte plus per-TU macro defs minus residue keys), the UNMARKED constant, the RESIDUE_COLS and parse_residue function, the residue_text writer, the cause classes, and the agent tag that notably has no corresponding ledger row or verdict entry. I'm also noting the Makefile hook and the shape of the lever_residue.tsv file itself (file, func, kind, pass, instrument, cause columns), confirmed against a live strict run.

Then I'm cross-referencing type_census.py for its output shape, restruct.py's residue_cause and canon_types logic, type_census.py's CANON_HEADERS, and the struct_map.json and body_base_type.json data files, along with restruct's CLI flags (--write-types, --audit-types, --type, --top, --space, --pointees) and the restruct_cycle.sh script. I'm pulling actual numbers from a residue_census run: 291,819 total / 13,736 types, with percentile breakdowns at 50%, 80%, and 95%, and I'm flagging the top type 80126B58 as suspicious given its 5,482/2,947 ratio compared to the others. Finally I'm looking at timeline.py's cast_rows and render_svg functions, readability_progress.py's column definitions, and progress.py's check_casts block that reads from residue_census.json.

I'm sorting out which research reports to cite — R3.40-001 through 003 are relevant, but R3.40-004 (the Blizz127 web report) wasn't actually cited for this plan even though it got pulled in by my adopt run, so I need to flag that. I'm also noting earlier phase reports R3.39-001 and R3.38-002 as useful supplementary citations for cast tooling and type_census mechanics respectively, and compiling the relevant cookbook entries (C0511 through C0528 and others) covering diagnosis, propagation lanes, dead-end ledgers, and lever-removal moves.

Pulling together the applicable rules (R22, R42, R53, and others), I'm now thinking through what the developer needs to decide: setting an agent cap for concurrent crack waves (leaning toward recommending 4 parallel agents) and possibly separate wording for lever milestone sizing if the T10 projection later exceeds that cap.

Right, the brief is asking me to supply the actual wording in my report so it can be put to the developer. My judgment: TNC elimination is realistic since it's mechanical and pilot-gated, but the lever's literal-zero target isn't achievable in a single phase — so I need to draft milestone wording specifically for that lever piece, then move to the D1 open items like ledger durability.

For P36, I'm recommending untracking it per D1, and planning a durable-copy approach: a gz snapshot of both ledgers saved to `.run/keep/` at phase start/close, kept untracked, with the developer handling off-repo backup since that's their data-retention call. I'll fold the pre-commit guard note into the developer-decides line, and merge the agent cap into the lever milestone item so I'm not presenting too many separate decisions at once.

Now I'm trying to work out what the developer means by an "uncovered" series next to raw casts in the timeline chart — I think it's meant to show that ledgering doesn't erase the underlying debt, so plotting a near-zero "uncovered" line beside the much larger raw-cast count would visually expose that the gate going green doesn't mean the casts are actually gone.

I'll skip the per-debt panels since those were deferred from T11, and keep task lines under 4000 chars. For the milestone line, I'm drafting a single statement confirming every residue item is fixed or properly tagged, verified by the type census check reaching zero TYPE-NOT-CANONICAL entries and the residue check showing zero uncovered across all four segments.

I also need to account for zero duplicate definitions, zero dead names, the lever census checks passing strictly, the legacy-T7 function fixes, the 11 ledgered lying declarations, and R22 reaching 218/218. But I'm now second-guessing the --check flag behavior, since the 3.39 plan context notes it fails on raw derefs, lying decls, and block-scope defs — I need to verify this matches the generation's done-criteria.

I should favor stating the counts rather than relying on the return code, since --check might fail due to raw casts even when the milestone numbers are correct — using --check-structs alongside the 0/0/4 counts seems safer. Per the C0526 lesson about reading a gate's predicate before zeroing its total, I'm adding to T1's done-when criteria that each milestone instrument gets verified on the start tree in both directions, per the P38 lesson.

Now I'm compiling the lever stats for Context from my run: pin, launder, keepalive, instruction, and asm-macro counts across residue rows, plus the overall totals for pins, asm, GTE levers, volatile/register needs, and residue status, confirming strict mode without residue returns rc 1.

I'm also categorizing causes by target type—head-class, singleton, missing-parameter, asm-macro-def, gte-clobber-steer, asm-body-routine—with their row and name counts, and breaking out the 3.40-agent subset by category.

Wait, the 70 figure doesn't match the 282 total—only gte-clobber-steer (60, 57 flagged) and asm-body-routine (13) sum to 70, while the other 212 rows also carry the 3.40-agent tag, so I should note that discrepancy. I'm also noting the scratch script path used to measure these lever counts, in case it needs re-running later.

Now I'm puzzling over T8's "left by the author" category (808 rows)—unclear if this marks legacy human-authored decomp sections. For re-judging, the cheap path is running the oracle removal check specifically against the "left by the author" and "not judged" rows (1,013 total), keeping whatever fails that check. There's a conflict though: P3.39 T8 claimed pins had zero removals with all 1868 judged NEEDED, yet "left by author" includes 265 missing-parameter rows that overlap with pins, so I need to reconcile that inconsistency.
