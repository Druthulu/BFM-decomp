# T20.c17 progress (handoff notice arrived after the last change was in hand; the task finished green)
## done so far
All 83 batch_r2 rows + Blk12 applied and committed (635e8a2232..329c1c0843); a4_status.py `pending 0`. Log:
phase-ends/current/logs/T20.c17.md; notes .run/3.45/t20/c17/notes.md.
## in flight
nothing; no patch.
## hypotheses rejected with evidence
- R38 as one A_B8 array: frame 40 -> 48 (asm diff); kept typed field-offset aliases.
- `(&LOBU(x))[i]` for crossing flag arrays: addu operand swap at 8 sites; 12-byte union arms identical.
## current hypothesis
n/a
## next 5 steps
1. Expert: bank the traps in the log (cookbook). 2. Next wave per plan.
## gotchas
see log Traps.
## state to carry verbatim
HEAD 329c1c0843; ratchet pending_types 525.
