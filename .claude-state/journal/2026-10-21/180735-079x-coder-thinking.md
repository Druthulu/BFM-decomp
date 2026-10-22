---
ts: 2026-10-22T00:07:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_n5UXLz97ke946qQI7I4F
---
No change. The pseudo number doesn't drive it.

Let me get the alloc table to understand. Let me create a scratch TU = the real TU with my candidate spliced in, then dump.

Actually, maybe simpler: create a STANDALONE TU with just this function (plus padding), like I did for func_801415C0. The function's local allocation shouldn't depend on the rest of the TU (it's a per-function decision). Let me do that — much faster than dumping the 5900-line TU.

The standalone TU needs: the externs (D_800B9AAC, D_800B9B00, D_801151D4, the functions), the Unkstruct_80126948 type, and the function.

The type Unkstruct_80126948 is defined in some shared header. Let me find it. If I include "common.h" and the struct types... hmm, the struct is probably in src/shared/engine_types.h.

Let me check where Unkstruct_80126948 is defined.

Also note: the standalone TU changes the calls' addresses but not the function's codegen. However, the function calls other functions — in the real TU, those calls exist; in my standalone TU, the externs suffice.

Hmm, but there's a catch: the target's code has `jal 0 <func_8017AE2C>` with relocs — the scorer compares instruction WORDS, and the reloc target isn't part of the word (jal's target field is 0 with a reloc). ✓ So the standalone TU is fine.

Let me find the structdefinition.
