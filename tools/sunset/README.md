# tools/sunset — tools retired at Phase 33.5 (2026-09-07), for the owner's review

*Moved here with `git mv` (history kept) after the tool census proved each had no live consumer, under the owner's criterion: a tool that was
required to finish the decomp is judged on its value to a FUTURE decomp — still needed (it stayed live), superseded by a better tool (retired, the
successor named), or a one-off (retired, its product named). The dictionary rows are `config/tool_dictionary.tsv`; the index lists them under
"Retired". Deletion is the owner's decision, after review; nothing here is a reference.*

| File | Verdict | Successor or product | ☐ reviewed |
|---|---|---|---|
| `audit_header_sigs.py` (was `tools/audit_header_sigs.py`) | SUPERSEDED | tools/conform_decls.py | ☐ |
| `bank_exemplar.py` (was `tools/bank_exemplar.py`) | SUPERSEDED | tools/gate_stage.py | ☐ |
| `bisect_slate.py` (was `tools/bisect_slate.py`) | SUPERSEDED | tools/gate_main_parallel.py | ☐ |
| `build_wave.py` (was `tools/build_wave.py`) | SUPERSEDED | tools/draw_waves.py | ☐ |
| `build_wave_args.py` (was `tools/build_wave_args.py`) | SUPERSEDED | tools/wave_args.py | ☐ |
| `canon_draft_decls.py` (was `tools/canon_draft_decls.py`) | SUPERSEDED | tools/sig_unify.py | ☐ |
| `exemplar_miner.py` (was `tools/exemplar_miner.py`) | SUPERSEDED | tools/atlas.py | ☐ |
| `fix_header_decl.py` (was `tools/fix_header_decl.py`) | SUPERSEDED | tools/conform_decls.py | ☐ |
| `gen_engine_decls.py` (was `tools/gen_engine_decls.py`) | SUPERSEDED | tools/conform_decls.py | ☐ |
| `glm_parallel.sh` (was `tools/glm_parallel.sh`) | SUPERSEDED | tools/ox_campaign.py | ☐ |
| `glm_reconcile.py` (was `tools/glm_reconcile.py`) | ONE-OFF | the measured verdict that the declaration wall is a reconciliation problem, plus the captured reasoning distilled into the cookbook (Phase 23 T10.7 A/B) | ☐ |
| `idiom_loop.py` (was `tools/idiom_loop.py`) | SUPERSEDED | tools/idiom_serial.py | ☐ |
| `jr_isolate.py` (was `tools/jr_isolate.py`) | SUPERSEDED | tools/jr_isolate_all.py | ☐ |
| `bounce_drafter_on_queue.sh` (was `tools/lanes/bounce_drafter_on_queue.sh`) | SUPERSEDED | tools/lanes/relaunch_drafter_shell.sh | ☐ |
| `launch_ox.sh` (was `tools/lanes/launch_ox.sh`) | ONE-OFF | the sharded overnight campaign run it launched (its key file, endpoint and model are that campaign's) | ☐ |
| `toolwork.sh` (was `tools/lanes/toolwork.sh`) | ONE-OFF | the tooling-design briefs it ran against an external model (its key, endpoint and model are that era's) | ☐ |
| `lenmiss_route.py` (was `tools/lenmiss_route.py`) | ONE-OFF | the routed outcome of one length-drift near-miss pile (it consumes that audit's classified ledger) | ☐ |
| `p16_known_answer.py` (was `tools/p16_known_answer.py`) | SUPERSEDED | tools/p16_improve.py | ☐ |
| `plumbing_groups.py` (was `tools/plumbing_groups.py`) | SUPERSEDED | tools/gate_triage.py | ☐ |
| `reconcile_slate.py` (was `tools/reconcile_slate.py`) | SUPERSEDED | tools/pregate_check.py | ☐ |
| `recover_drafts.py` (was `tools/recover_drafts.py`) | SUPERSEDED | tools/agent_drafts_restore.py | ☐ |
| `residual_rules.py` (was `tools/residual_rules.py`) | SUPERSEDED | tools/residual_rules_b.py | ☐ |
| `rtu_shadow.py` (was `tools/rtu_shadow.py`) | ONE-OFF | the measured gate-inversion decision (whether the cheap real-unit check should become the gate's stage 0) | ☐ |
| `scan_leftovers.py` (was `tools/scan_leftovers.py`) | SUPERSEDED | tools/integration_resolver.py | ☐ |
| `sweep_citations.py` (was `tools/sweep_citations.py`) | SUPERSEDED | tools/gccmap_cites.py | ☐ |
| `symcheck.py` (was `tools/symcheck.py`) | SUPERSEDED | tools/reloc_verify.py | ☐ |
| `t5_bank.sh` (was `tools/t5_bank.sh`) | SUPERSEDED | tools/gate_wave.py | ☐ |
| `t5_distill_args.py` (was `tools/t5_distill_args.py`) | SUPERSEDED | tools/distill_scan.py | ☐ |
| `t5_targets.py` (was `tools/t5_targets.py`) | SUPERSEDED | tools/draw_waves.py | ☐ |
| `t7_bank.py` (was `tools/t7_bank.py`) | SUPERSEDED | tools/gate_stage.py | ☐ |
| `treelock.sh` (was `tools/treelock.sh`) | SUPERSEDED | tools/shared_lock.py | ☐ |
| `verify_map_findings.py` (was `tools/verify_map_findings.py`) | ONE-OFF | the machine-checked verdicts of one codegen-map audit (docs/gcc-2.7.2-map/regalloc.md) | ☐ |
| `wall_taxonomy.py` (was `tools/wall_taxonomy.py`) | SUPERSEDED | tools/frontier_classify.py | ☐ |
| `warmstart.py` (was `tools/warmstart.py`) | SUPERSEDED | tools/permuter_sweep.py | ☐ |
| `dedup_propagate.py` (was `tools/dedup_propagate.py`) | SUPERSEDED | tools/share_body.py (P35 T6: the include-at-site share; --reexemplar, --repair-registry) | ☐ |
| `dedup_extend.py` (was `tools/dedup_extend.py`) | SUPERSEDED | tools/share_body.py (add_members_surgical moved verbatim; the extend bucket) | ☐ |
| `macro_draft.py` (was `tools/macro_draft.py`) | ONE-OFF | the per-function headers under src/shared/ (P35 T4) — no macro body to materialize | ☐ |
| `test_reconcile_ledger.py` (was `tools/test_reconcile_ledger.py`) | ONE-OFF | the S45p7 reconcile-ledger proof, retired with dedup_propagate | ☐ |
