---
ts: 2026-10-17T15:45:12.044Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae6f058bb8615c3ec
model: claude-opus-5-5[1m]
effort: high
turnId: 747feadd-bdf1-4a7e-b93c-524c55511a38
---
I'm checking whether T13's dependencies should actually include T17, since T17 owns the fleet TNC zero check and the drift task changes suggest T13 depends on that work, but T13's listed deps only cover T5, T6, T11, and T12.

Since T13 is already being touched, adding T17 to its deps seems like a reasonable correctness fix, and I could note the rationale briefly in the plan's Changes section since there's no dedicated notes field. T7 through T9 are all marked done, so now I'm turning to the research side—checking what `lever_census --residue` actually enforces, specifically whether it's a tool-applied rule requiring every row to have a wall cause, and whether the existing cause column already supports that check.

Looking at the cause classes in lever_census.py, I see values like "singleton" and "head-class <hash>" that aren't actual compiler walls, which means enforcing "no row without a wall cause" likely requires a code change—something like a new `--require-wall` flag that validates causes against a defined wall vocabulary. This probably needs its own task or an addition to T13, so I need to dig into how lever_census parses residue and writes causes, and figure out whether all 2,309 rows across the different survivor categories (head-class, missing-parameter, gte, asm-macro, etc.) actually need a named wall assigned.

I'm also noting I should spawn retriever-code to check lever_census's residue handling and current cause distribution, plus retriever-digest to see how T7/T8/T9 survivors' instruments and causes are documented. And there's still the cast-gate leftover work — three K&R-empty lying decls and one unbacked CAST_NONSTRUCT — that needs a home in the new task.

I also want to check the planner card slice, the 3.40 phase entry in GENERATION_PLAN, the triage state from launch.py's deferred items, and the AUDIT.md tool candidates list, plus earlier planner notes in the journal, running these reads in parallel while the retrievers are working.
