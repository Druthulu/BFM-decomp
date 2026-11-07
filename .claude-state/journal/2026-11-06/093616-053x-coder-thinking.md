---
ts: 2026-11-06T16:36:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OlDpiPEewDPPpq7MKRUx
---
Our TU is an -O2 file. So flags same.

So why does the tool's pipeline produce the target bytes? Because the pipeline includes **maspsx**. maspsx might do register-related transformations? Unlikely. But maybe maspsx's `--expand-div`... no div here.

Wait — actually, maybe the difference is that the tool's `--try --body` replaces the function in the *real TU text* and compiles the whole TU. My splice compiled the whole TU too (t.i = whole TU). Hmm.

Unless... my cpp output differs: I used `-Isrc/shared -Isrc` extra, and crucially the Makefile's CPPFLAGS does NOT include `-Isrc/shared`. The file includes "../shared/..." relative to src/ov_SC05_007 → src/shared. Same.

Let me directly compare: run the Makefile's recipe for this TU but to a scratch output, without writing build/. Use `make -n` to get the recipe, then run it manually with output redirected. Actually delever_oracle's recipe is exactly that; let me just query the recipe via the module? Easier: `make -n build/src/ov_SC05_007/ov_SC05_007_jr_8017BEBC.o`.

But maybe simplest: compile the real src file with the full pipeline (including maspsx + as) to a scratch .o in my item dir and objdump it. If that matches the build, then my dump approach just needs maspsx.

Actually! That's likely it: maspsx is an *assembler macro* pass. But the register difference can't come from maspsx...

Hmm, unless the `addu $4,$4,$0` line is transformed by maspsx into `move $5,$4`? No way.

Let me check whether cc1's output for the real source (not my spliced .i) differs. Maybe my splice is subtly wrong: e.g., the .i contains the function inside a `#pragma` or the function body I spliced lacks the trailing blank lines that affect... no.

Wait, maybe the issue is the *line markers*: `# 3970 "src/..."` after my splice. Irrelevant.

Let me try: compile the real TU's .i WITHOUT splicing (my t.i is exactly the cpp of the real src). Run cc1 on t.i and compare. If t.i's output also gives addu $4,$4,$0, then the difference is in the pipeline (maspsx), not my splice.
