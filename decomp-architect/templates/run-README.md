# `.run/` — scratch, with dated exceptions

*Installed by decomp-architect (Step 4) on {{INSTALL_DATE}} for {{PROJECT_NAME}}. This folder is the project-local replacement for
the system temp directory: no project data lives outside the repository, ever. Build and extract logs, signature dumps,
permuter and compile scratch, agent work directories, per-session probes — everything a rerun can reproduce lives here and
is never committed. `make clean` never touches it; pruning it is a hand decision.*

**It is ignored by contents, not as a directory.** The `.gitignore` rule is `/.run/*` rather than `/.run/`, because git will
not look inside an excluded directory and no `!` re-include could then work. That form lets the irreplaceable part be
tracked by exception. Each exception is a three-line idiom under a dated comment naming the phase, the session and the rule
that justified it:

```
# P<N> <task> (<session>, <date>): the recorded contract run's per-step logs. Evidence, tracked.
!/.run/P<N>/
/.run/P<N>/*
!/.run/P<N>/verify/
/.run/P<N>/verify/*
!/.run/P<N>/verify/*.log
```

**The test for an exception:** commit what a rerun CANNOT reproduce — hand or frontier-model analysis, the harness that
produced a verdict, a ledger, the recorded contract run — and leave what a script regenerates (compiler dumps, build logs,
drafts, compile directories) ignored. Work that turns out to be irreplaceable gets its dated `!` block the day it is
recognised as such, not at the phase close.

**Per-session layout.** A session or wave gets one directory, `.run/<session>/`; each agent works in its own
`work/<binary>-<address>/` under it and may clean only that; deliverables (drafts, verdict lines, reports) go to a
`drafts/`, `verdicts/` or `reports/` directory no agent owns; an agent never runs `find`, `rm` or `mv` outside its own work
directory; an agent's final message is one JSON line, with the prose in `reports/<function>.md`.

**Two fail-safes.** Never `git clean -x` or `git clean -fdx` in this tree: the game-derived data (the dump, memory images,
the reverse-engineering database, the vendor SDK) is ignored-but-present on the maintainer's disk, and a `-x` clean deletes
it. And a tracked `.run/` file is PUBLISHED: it is subject to the ROM firewall like anything else — a listing of the target's
instructions is game-derived even inside a notes file, and the audit's content check looks for exactly that.
