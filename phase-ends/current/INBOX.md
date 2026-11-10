# INBOX

<!-- The developer writes here whenever they want; nobody asks them to. Freeform bullets.
     The loop consumes it at every task boundary (the mod), with `tools/status.py inbox-consume`,
     which prints the contents, archives them to discussions/inbox-<ts>.md and empties
     this file. Items that change the plan become plan_edit.py edits with a Changes line;
     items that change a standing fact go to HOW_WE_WORK.md.
     Routing: each bullet becomes an I<n> row in discussions/INDEX.md, deferred:<P> or now.
     First match wins: `-> 3.12` / `-> Gen 4`; `Gen N` beyond this generation; a later
     plan phase id (`3.11 ...`); the word `later` (next open phase); else now. The current
     or an earlier phase, or an id not in GENERATION_PLAN.md, routes now. -->

- <note, correction, priority change, or question>
- -> 3.44 The 356 older non-void functions with no `return` (or only a bare `return;`) left after 3.43 T3, which did only the 38 that 3.41's 112c3e4eb9 flipped (developer 2026-11-10, option A). Scan at HEAD 50da691580: 394 names / 9,009 defs; 67 names have 110-140 overlay copies (~8,600 sites), 311 are single-def. Each needs a byte-neutral `return <expr>;` or a comment saying what $v0 holds at exit; most tail-call void callees, so comments dominate. The list is kept by T3 in docs/ops/ (see T3's summary).
