---
ts: 2026-10-17T13:30:28.634Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a626fbaaaeb671f97
model: claude-haiku-5-5[1m]
effort: medium
turnId: 4c14acd6-890f-4ac7-9b0e-e46a73139601
---
I've used 9 calls now, and the exact per-function byte-test commands live in coder logs outside the defined scope, so I shouldn't chase them further. I'll proceed to writing the report file at the appropriate path.

For the filename I'll use "retriever" as the agent and "t9-head-class-crack-workflow" as the slug, which fits within the 40-character limit. I'm tallying up the cracked head classes across commits: c8 accounts for 4 class-hashes, c13 for 6, c16 for 6, and c18 for 2, totaling 18 cracked classes out of 38 attempted, and I'll cite the coder logs as pointers for anyone wanting the raw command details.

I'm working through per-run timings and crack rates: roughly 18 coder runs spanning ~21 agent-hours, with individual blocked/successful runs ranging from 10 minutes to nearly 3 hours, yielding a 47% crack rate (18 of 38) with 20 classes still uncracked. I don't have token counts recorded in scope, so I'll note those as not found rather than guessing.

I'm also cataloging operational snags for the pilot — tooling issues like the dead permute lane needing scorer scripts instead, match_one's flag requirements, propagation refusing sibling matches, TSV editing being blocked, commit scripts auto-staging logs, and R22's serial-only concurrency constraint — plus unresolved questions around lever-only matches, the W4 signature change ripple effects, and stale calibration files. I'm starting to note which crack families actually succeeded, beginning with return-type/keepalive substitutions.

Now I'm compiling the full list of successful crack techniques — things like swapping 16-bit result variables to kill birthing boosts, reusing locals as derived pointers, moving calls into conditional tests, shrinking loop counters to s16, and various pointer/store-order tricks that defeated cross-jump or union-return issues — alongside a parallel list of failed approaches like label-sharing, alias irreducibility, cse folding quirks, and allocation tie-breaks that never panned out. I'm also flagging the declaration-scope nuance around the extern void->s32 cast appearing only in definition TUs.

I'm now assembling the actual command references and file pointers — the scorer scripts, remap utilities, log locations, and the full pipeline commands (build, calibrate, propagate, apply-body, strict residue check, gate, finish, commit) — while double-checking that delever_oracle isn't actually part of the named scope, only match_one with its specific flags. I need to keep this report under 60 lines and write it out compactly now.
