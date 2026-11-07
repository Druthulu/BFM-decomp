---
ts: 2026-11-06T17:27:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_RGVUOJ7Pu8vG3HttEPK2
---
All 7. The allocation of sh16 (v1 vs v0) is stable.

Time: 10:27, item 4 started 10:25:37 → 1.6 min. Budget 20-30.

Let me try to understand the sh16 allocation with a dump. The function is in a header instantiated in a TU; the dump harness would need the includer TU with the header inlined (hdump.sh from T10). Let me use `.run/P40/T10/hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag>`.

hdump.sh: `hdump.sh <includer TU> <header basename> <body.c> <outdir> <tag>`: inline body in place of the header include, dump passes, alloc table. It needs an absolute outdir under my shard.

Let me try it on includer 0 (src/ov_MAIN_012/ov_MAIN_012_jr_801458E0.c, header func_8015126C.h).

But first: the header's include line in the TU is `#include "../shared/ov/func_8015126C.h"`. hdump asserts that. Let me run it.

Actually, the function is 254 ins with many calls; the allocation of sh16 is the only residual. The pin comment says "!FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t8_hdr1)". So a previous agent needed the pin. Our job: find a lever-free equivalent.

sh16 in v0: the target's sll writes v0. Without the pin, sh16 gets v1.

Idea: make sh16's def and use such that v0 is preferred: v0 is the "return value" register; the function returns void. Local-alloc gives v0 to the highest-priority qty.

Idea: increase sh16's refs by using it in the comparison? no.

Idea: use a *different* variable for the two assignments but the same? no.

Idea: make the temps' priority lower by lengthening their lives: e.g., compute `(u32)sh16 >> 31` early (before the if)? It depends on sh16.

Hmm, what about restructuring the expression so fewer temps are needed? The target's temps: sra v1 (>>16), srl v0 (>>31), addu v1, sra v1, sh. In the target, sh16=v0 and the temp v1. The >>31 temp is in v0? No: `srl v0,v0,0x1f` — that's a temp in v0, but sh16 was in v0 and this is its last use (redefinition). So the temp takes v0 after sh16 dies. Then addu v1,v1,v0 (sum into v1), sra v1, store v1.

In mine: sh16=v1; sra v0,v1,16 (temp v0); srl v1,v1,31 (reuses v1 after sh16's last use); addu v0,v0,v1; sra v0; store v0.

So the pattern is symmetric: the first temp gets the reg freed by sh16's death.

To match, sh16 must be v0. Priority: sh16 has refs 4 (2 defs + 2 uses), life from the first def to the last use. The temps have 2 refs each.

Let me try making sh16 *s16* and see... no (semantics).

What about making the angle path and the p[0x79] path use different variables? e.g.:
```
s32 shA, shB;
if (r[0x49] == 5) { shA = angle << 16; sh16 = shA; } else { ... shB = p[0x79] << 16; sh16 = shB; }
```
Adds copies → changes instructions.

Hmm, what if the two assignments are written as a conditional expression?
```
sh16 = (r[0x49] == 5) ? (angle << 16) : (func_8014CB7C() ? (p[0x79] << 16) : goto...);
```
Can't with the goto.

What if we restructure to avoid the goto:
```
if (r[0x49] == 5) {
    sh16 = angle << 16;
} else if (func_8014CB7C() != 0) {
    sh16 = p[0x79] << 16;
} else {
    goto LAB_8015152c;
}
```
That's the same CFG; the code might differ slightly (jump threading). Try it.

Also try: `sh16 = angle << 16;` in the first arm vs `sh16 = (s32)((u32)angle << 16);` (same).

Let me try a batch:
w1: else-if restructure.
w2: sh16 as u32.
w3: sh16 declared inside the if block? It's declared at function top; moving it into the enclosing block changes the pseudo birth.
w4: sh16 as `s32 sh16 = 0;` init? adds.

Let me test w1, w2, w3.
