---
ts: 2026-10-17T15:48:00.651Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a92213cdfb705eea6
model: claude-haiku-5-5[1m]
effort: medium
turnId: 0b9dc8f2-e929-4e44-bc4f-f3370b69571f
---
I'm noting that strict mode only sets rc=1 on failure, and residue-unused doesn't affect rc at all—when strict runs without --residue, residue_rows is empty so that check trivially passes. I'm also tracking that cause classes only get emitted as asm-macro-def with detail, gte-clobber-steer, asm-body-routine, or missing, based on whether a row's key is found in the data.

I realize `--write-residue` preserves existing rows verbatim via setdefault and only regenerates new ones, which matters for how the delever ledger passes through.

Now I'm stuck on counting rows in the TSV—2,309 of them is too many to read manually, and I don't have a Bash tool to script it. I only have Read, Write, Grep, Glob, and SubagentHandback, so I need to find a way to get counts using Grep's count mode instead of executing a script.

I'm weighing whether Grep -o on the cause/kind columns would dump too many lines into context, and realizing I don't even know the kind vocabulary yet, so I should first extract the distinct kinds from the ledger before trying to count by pattern.

I'll switch to running a batch of parallel count-mode Grep calls instead — one for total rows, several for each known kind (pin, asm-macro, asm-body, gte-lever, gte, gte-unsigned), and several more for cause prefixes and instrument-outcome phrases like "oracle DIFFERS on removal" or "not judged" — since count mode on a whole file gives a clean single number per pattern without flooding context.

Getting all distinct full cause strings isn't really feasible with the tools available, so I'll be upfront about that limitation and instead offer a script the caller could run themselves. For the compiler-pass check, I'll grep for pass-related keywords like cse, sched1, sched2, local-alloc, reload, flow, jump2, noting that "GTE" and "asm" show up lowercase within other cause labels, and I'll pull a few sample lines with head_limit to confirm. I also want to glance at the Makefile context around lines 308-310 and check whether any existing tests reference lever_census, since the only test coverage seems to be the built-in selftest mode.

I notice that none of the existing cause strings actually name a specific compiler pass -- they're generic class labels like missing-parameter or asm-macro-def -- and parse_residue currently does zero validation on cause vocabulary, column count, or emptiness, just silent padding. If I wanted to enforce a wall-naming rule, the cleanest spot would be inside main() right after residue_rows loads, adding a filter for bad causes and setting rc=1 accordingly -- and I should flag that residue-unused counts currently don't affect rc either, which means "OK" can print even with residue-unused flagged, a real gap worth noting. Also worth remembering: the --residue flag requires an explicit path argument, so omitting it silently yields empty residue_rows.
