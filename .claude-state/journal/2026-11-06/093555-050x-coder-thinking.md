---
ts: 2026-11-06T16:35:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HLLOu2P4t6DXYAk9GCKA
---
So the spliced .i gives `addu $4,$4,$0` and a different allocation than the build. So the .i must differ from the build's cpp output. Maybe the build's cpp (mipsel-linux-gnu-cpp from a different binutils?) or the real CPP variable is `$(CROSS)-cpp`. Let me check the CPP variable and whether there are extra -D flags from the Makefile, e.g., `-DF4C_IDX=...`? The function doesn't use macros.

Hmm, wait. Maybe the difference: the build compiles with `-O2` and the .c file for the build might be a *different file* than I think: build/src/ov_SC05_007/ov_SC05_007_jr_8017BEBC.o — yes same TU.

Could the build have been made with the CDK cc1? Let me check if there's a per-file choice. The Makefile line 36-37: CC1_PSX and CC1_CDK; line 1055 uses $(CC1_PSX). But maybe a target-specific var for certain files.

Alternatively, maybe the build object is stale and delever_search's "calibration" compares against the same build object but with masked diff that happens to mask the differences? The score for orig was 0 and "byte-identical". If the build object were from a different source text, orig.c wouldn't be byte-identical.

Wait — but maybe orig.c is NOT the text that produced the build: I copied lines 3916-3948 from the src, which includes the pins. The build has `move a1,a0`, which is consistent with `self = arg0 + zr` compiled *with* a1 allocation. My cc1 gives a0. So the build's cc1 differs in behavior...

Unless: the build's pipeline passes through maspsx which *reorders*? maspsx is an assembler post-processor: it expands macros, handles div, and maybe does delay-slot filling. But it can't change `addu $4,$4,$0` into `move $5,$4` (different register). Unless maspsx handles `.set noreorder` and... no.

Hold on! Maybe the difference is that the build's cc1 output goes through maspsx which *removes* the `addu $4,$4,$0`? no, the target has `move a1,a0` at the start, which is a different register.

Let me check: is build/src/ov_SC05_007/ov_SC05_007_jr_8017BEBC.o actually the object for the jr file? The TU is named `ov_SC05_007_jr_8017BEBC` — hmm, "jr_8017BEBC" suggests a segment starting at 0x8017BEBC. The object might be a *segment object* assembled from src/ov_SC05_007/ov_SC05_007_jr_8017BEBC.c. Fine.

Wait, maybe the src file I read has the body but the build object was built from a *different, older* .c, and the bank compares the object to the *original ROM* bytes, not to the src. The "build" object is the tree's compiled output. delever_search compares candidate against build/. If build/ is stale relative to src, then orig.c (current src text) would NOT score 0. But it did score 0! And the tool said "byte-identical". So build matches src text under *its* compile recipe.

So the tool's own compile recipe produces `move a1,a0` from this text, while my cc1 produces `addu $4,$4,$0`. So my invocation differs from the tool's. The tool uses `mipsel-linux-gnu-objdump` and compiles with some recipe. Let me look at how delever_search compiles a candidate (the recipe function) — maybe it uses additional flags like -fno-delayed-branch? Let me grep.
