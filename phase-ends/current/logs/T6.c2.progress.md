# T6.c2 progress (handoff at context threshold; the change is complete)

## Done so far
- All DONE-WHEN items green and committed: engine + selftests (2af6b89a32, d65a011387), P1 applied (8ae05789dd), stamped (8c9489c3ac), twins doc restore (last T6.c2 commit). Full detail: phase-ends/current/logs/T6.c2.md.

## In flight
- Nothing. No patch (tree has no T6.c2 edits uncommitted).

## Hypotheses rejected with evidence
- "my fold dropped 14 twin sections": rejected; worktree at 5399745568 + fresh census also gives SHARED 14 (shared/ov/SHARED_FN objects).

## Current hypothesis
- type_census attributes cross-header bodies (#define SHARED_FN X / #include) to the name SHARED_FN; struct_twins then sees one object shared by many types and classes them SHARED, which --write leaves out of ## Twins.

## Next 5 steps
1. Expert: decide on the SHARED_FN wall (fix census attribution, or have struct_twins --write keep SHARED rows listed).
2. Until then, do not commit a struct_twins --write output; keep docs/struct-twins.md as committed.
3. Apply P2-P4 when the plan says (dry runs clean: logs t6c2_dry_P2..P4).
4. Bank gotcha: asm-labelled declarators need HF_ASM_LABEL stripping.
5. Bank decision: restruct ledger rewritten in place, never committed.

## Gotchas
- commit_task.sh auto-stages phase-ends/current/logs/* (it picked up T6.progress.md).
- tools/run.sh --bg needs a separate `--wait <name>`.

## State to carry verbatim
- P1 commit 8ae05789dd; P2 key Unkstruct_800CAE74_2; P3 keys SV4x_80184754,SV4x_80184B30; P4 key Unkstruct_800CCDB0.
