---
ts: 2026-11-06T10:49:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CrWDxYZyrMME36leOxVK
---
v_addr5: order perfect, regs swapped (t v1, a v0). Because t is global and global-alloc gave it v1 (not v0). Hmm! In v_addr4, t global got v0. In v_addr5, t global got v1.

Difference: v_addr5 has a separate do-while block for [a, store]; v_addr4 has them in the same block as the RMW. Hmm.

Global-alloc assigns hard regs to global allocnos by priority order; there might be other global allocnos (e.g., the pointer a0 in s0, v0 result). The available regs for a global are s-regs and caller-saved. t is global; it can get v0 or v1. In v_addr4 it got v0; in v_addr5 it got v1.

This is frustratingly sensitive. Let me try combining: keep t in block1, a+store in block2, RMW in block3, but make t's global allocation win v0 by... decl order? In v_addr5 I declared `s32 t; s32 a;`. Global-alloc's priority for t: refs*size/live. Hmm.

Alternative: swap which variable is global. What if `a` is computed in block1 (with the load) and t used later? No.

Let me think about global-alloc ordering. In global.c, `allocno_compare` uses floor_log2(n_refs)*n_refs / live_length. For t (global): refs=2, live across 2 blocks. For the address a: local. Only t is global here (besides a0/v0). a0 is global too (used in the entry block and the else block? a0 is used after the call in the else block; a0 = s0 allocated). Actually a0's pseudo is global (live across calls/blocks) and gets s0.

So global allocnos: a0 (→s0), v0 (the call result, →v0 or s0?), t. v0's pseudo (the result of func_8012C1B8) is used for the call arg and the comparison and stored to unk20. Its live range is short (block 1). Hmm, but it's used in the `if` block and then in the else block (func_8001CA1C(v0,...)), so it's global.

So t competes with v0 for $2/$3. In the target, t (pinned to $2) got v0. Lever-free, v0's pseudo might take $2 first (it has more refs), and t gets $3 (v1). In v_addr4 t got v0 — maybe because v0's pseudo was allocated $2 and t took... hmm, if v0's pseudo took $2, t should get $3 in both.

I'm going too deep. Time check: I need to be mindful. Let me check the clock and consider whether to accept a WALL for this item and move on.

Actually — wait. Let me reconsider the problem from the target's structure once more. In the target, is t really a local allocno? The barrier splits the EBB for cse, but local-alloc uses basic blocks (calls split). Since the else block starts after the last call, the barrier is inside that block. So t and a are in the SAME basic block in the target → both local → the qty priority decides: a's live range is shorter (a dies at the store which comes before the ori) → a should get v0. But t got v0!

Unless the barrier is NOT inside the same basic block: maybe an asm volatile with a memory clobber creates a basic block boundary via `INSN_VOLATILE` or because it's treated like a call. Let me check find_basic_blocks more carefully: the code at line ~449 checks `prev_code == CALL_INSN || prev_code == JUMP_INSN`. An asm volatile is an INSN, not a CALL_INSN. Hmm.

But wait: maybe gcc turns a volatile asm into a CALL_INSN? No.

Hmm, but actually maybe the barrier matters via `flow.c`'s `life_analysis`: volatile insns... no.

Let me test the hypothesis directly: if the barrier splits the basic block, then with the barrier t is in block B and a in block B too (both after the barrier). No.

Unless the barrier is placed BEFORE the load and the address `lui/addiu` is emitted *before* the barrier? No, the address comes from the store after.

OK. Let me try to see the actual alloc table for the orig. Use tools/cc1_dumps_tu.sh on the real TU to get .lreg (local-alloc) dumps. The TU is src/ov_SC03_028/ov_SC03_028_jr_801887A8.c. cc1_dumps_tu.sh takes a .c file and dumps with -dl (local-alloc). That gives the alloc table for the whole TU. Then I can compare with a candidate.

That's a solid grounded approach. But the dump is for the whole TU (5000 lines) — output files under a dump dir. I can grep them. Let me do it for the original TU first, then for my candidate (I'd need to splice the candidate into a copy of the TU — 5184 lines; I can create it under the item dir with the extract/splice. But cc1_dumps_tu needs includes to resolve: the file is in .run/..., and `-Isrc/shared` plus `-I$(dirname $tc)` — the TU's includes are relative to src/ov_SC03_028/. Let me check the TU's includes: probably `#include "common.h"` and `#include "../shared/..."`. The script adds -Isrc/shared and -Iinclude. A copy under .run would need -Isrc/ov_SC03_028 for its own includes. Hmm.

Alternative: the --try scratch TU is written under .run/P36/engine/score/... and compiled with the right -I flags. I could keep it: --keep prints only the object. But the scratch TU file remains? `score_file` removes the scratch dir unless --keep. With --keep it stays at .run/P36/engine/score/<alias>__<fn>/p<pid>/<basename>.c. That's the spliced TU! Then I can run cc1_dumps_tu.sh on that file with DUMP_ROOT under my item dir. The script adds -Iinclude -I"$(dirname $tc)" -Isrc/shared. The scratch TU's own includes (e.g., "../shared/ov/..."?) — the original TU includes "../shared/..."? Let me check the includes of the TU. If it includes "../shared/..." then from .run/... it won't resolve with -Isrc/shared (the script adds -Isrc/shared so `#include "shared/..."` works, but `../shared/` from .run/... would be .run/P36/shared). The script comment says S103: "a TU's `#include "../shared/..."` resolves from any directory one level under src/" — i.e., a scratch copy must be one level under src/. So .run/... won't work directly. But maybe the script's -Isrc/shared handles `#include "shared/x.h"` only.

Hmm, let me check what the TU includes.
