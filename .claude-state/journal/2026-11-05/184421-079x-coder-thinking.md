---
ts: 2026-11-06T01:44:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dVXD33i9hJXdd2r39gQw
---
Not it.

Time is passing. Let me reconsider strategy: instead of reverse-engineering which pass deletes the trailing return jump, note that vA's trailing `return;` did NOT survive. Why? Look at vA .rtl: jump 368 to label 374. At the first jump pass, line 656: `reallabelprev = prev_active_insn (JUMP_LABEL (insn))`. For insn 368 (the last jump), JUMP_LABEL=374; prev_active_insn(374) = insn 368? prev_active_insn skips notes, so prev of label 374 is note 372 (FUNCTION_END) then note 371 (BLOCK_END) then jump 368. So reallabelprev == 368 == insn! Then line 664: `if (reallabelprev == insn && condjump_p (insn))` — not condjump, so skipped.

Then line 656's redirect check: `next_active_insn(JUMP_LABEL(insn)) == 0` — label 374 is last in the function but the TU continues with other functions, so next_active_insn(374) = first insn of the next function → not 0. So no redirect.

Hmm, but wait: maybe func_80184E8C is the LAST function in the TU! The TU is ov_SC03_007_jr_80183894.c. Let me check: is func_80184E8C the last function defined in the file? The file is 5785 lines; func_80184E8C at 4089-4177, and there are more functions after (the `#include "common.h"` at 4183 then more). So not last.

Hmm, so why is the jump gone?

Let me look at what the .rtl dump shows after the jump: barrier 369, notes, label 374. And the .jump dump: insn 366, note 371, label 374. So the jump 368 and barrier 369 were deleted, and FUNCTION_END note 372 too.

Wait — maybe the jump was converted to a RETURN insn by line 656 (next_active_insn(JUMP_LABEL) == 0?) — no, next function follows.

Hmm, hold on: maybe the insns of *different functions* are not linked at this point? rest_of_compilation is called per function; get_insns() returns only the current function's insns! Yes! `insns = get_insns()` — the RTL chain contains only the current function. The next function is compiled separately. So next_active_insn(label 374) == 0 → line 656 fires → redirect_jump(insn, NULL_RTX) → the jump becomes a RETURN insn. And for ALL the other jumps to 374 too? They also have next_active_insn(374)==0. So all returns would become RETURN insns, giving `jr ra` everywhere. But the target has `j 180c`. Contradiction!

Unless... `redirect_jump (insn, NULL_RTX)` is guarded by something. Let me read lines 645-665 fully.
