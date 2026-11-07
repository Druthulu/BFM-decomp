---
ts: 2026-11-06T16:31:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_azC4DIqdw75i8xGnzudM
---
The shared header includes "../shared/engine_prelude.h" relative to src/ov_SC01_084/. If I copy it to dumptu/, that relative path breaks. Better approach: create dumptu/ov_SC01_084/ structure: put t.c at $D/dumptu/ov_SC01_084/t.c and copy shared header into the same dir; then "../shared/engine_prelude.h" resolves from $D/dumptu/shared/ — need that too. Hmm.

Alternative: symlink the src directory? We can write only under our shard. We could make $D/dumptu/src -> /home/musashi/bfm-decomp/src symlink, and put t.c at $D/dumptu/src/ov_SC01_084/t.c? Can't write into src (symlink target is real). 

Better: make $D/dumptu/ov_SC01_084/ containing t.c and a symlink to the real shared header, plus $D/dumptu/shared -> real src/shared symlink. Include search: TU dir is $D/dumptu/ov_SC01_084; `#include "common.h"` found via -Iinclude (repo include dir) since script runs from repo root and passes -Iinclude. `#include "../shared/engine_prelude.h"` from the shared header's location... The preprocessor resolves quoted includes relative to the *including file's directory*. If ov_SC01_084_shared.h is a symlink in $D/dumptu/ov_SC01_084, GCC may resolve relative to the symlink path or real path? Usually the directory of the file as opened (symlink path). So `../shared/engine_prelude.h` → $D/dumptu/shared/engine_prelude.h; make $D/dumptu/shared a symlink to src/shared. That works.

Simpler: just copy the src tree pieces. Actually simplest: copy src/ov_SC01_084/ov_SC01_084_jr_8017F690.c to $D/dumptu/ov_SC01_084/t.c and copy shared headers? engine_prelude.h may include many. Symlinks are easy.

But wait: do I really need dumps? Maybe I can reason without. Let's first try more C variants; dumps only if stuck. But I'm told "read dumps when unsure". The key question: why did target keep unmerged.

Alternative idea: maybe target's difference is that the then arm and else arm branch to *different* skip labels that later merge? No, both to 2bc8.

Let's think about the structure of the target again. The then arm's `j 2bb8` jumps to the call which is placed after the else arm. This is exactly what you get from:

```
if (unk70 == 0) {
    if (d >= 0x51) goto skip;
    goto docall;
} else {
    if (d >= 0x201) goto skip;
}
docall:
call
```
But GCC's first jump pass (jump_optimize) threads: since docall immediately follows the else, then-arm's `goto docall` becomes a branch to docall... Actually GCC would keep an unconditional jump (it's a real jump over the else arm). Then cross-jump merges.

Unless... the asm was in the *then* arm, so the then arm's RTL contained an asm insn right after the compare, and then cross-jump's backward scan from the end: the last insns of the two arms are [asm?, beqz?]... hmm.

Let's find out what the with-barrier body's dumps look like vs without. But barrier compiles to a zero-byte asm... in RTL it's an ASM_INPUT insn. The dump would show it.

Rather than guess, set up dumps for both and compare jump2. But the barrier version is the src (which scores 0), the v1 is ours. Let's set up the TU dump properly.

Actually the delever scratch directory may already be the spliced TU with correct includes? No, includes failed.

Let me create the symlink structure.
