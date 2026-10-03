# INBOX

<!-- The developer writes here whenever they want; nobody asks them to. Freeform bullets.
     The router consumes it at the top of every loop (`tools/status.py inbox-consume`),
     which prints the contents, archives them to discussions/inbox-<ts>.md and empties
     this file. Items that change the plan become plan_edit.py edits with a Changes line;
     items that change a standing fact go to HOW_WE_WORK.md.
     Routing: each bullet becomes an I<n> row in discussions/INDEX.md, deferred:<P> or now.
     First match wins: `-> 3.12` / `-> Gen 4`; `Gen N` beyond this generation; a later
     plan phase id (`3.11 ...`); the word `later` (next open phase); else now. The current
     or an earlier phase, or an id not in GENERATION_PLAN.md, routes now. -->

- <note, correction, priority change, or question>
- Phase 3.39 first task: regenerate the timeline and README after the 3.38 close (tools/timeline.py; tools/progress.py --readme). timeline.py --check currently reports story-timeline.md STALE; README Levers should read 3,729. Commit via tools/commit_task.sh. Carried from the 3.38 close (R121).
