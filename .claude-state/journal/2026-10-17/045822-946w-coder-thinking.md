---
ts: 2026-10-17T10:58:22.492Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a55474736c80a3baf
model: claude-opus-5-5[1m]
effort: medium
turnId: e20d419a-4489-4243-b756-85abe7c2d13c
---
The permuter needs a pycparser-parseable base.c, and delever_permute strips attributes. I see the draft.c for P36 already exists as a full preprocessed TU, with target.o built — the only issue was calibration through match_one. I'm checking whether I can run run_masked.py directly on that directory, which requires settings.toml and compile.sh to be present there.

Looking at the directory contents, there's iso.c, levered.c, splat, target.o, tgt, and tu.c, but no base.c. Prepare likely creates its own permuter dir during run_one after calibration. I'm considering using iso.c as my base.c instead, checking its tail for func_80177B5C and whether its compile matches, and reusing the stripping function by importing it directly rather than editing the tool.
