---
ts: 2026-11-06T21:03:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_nTilQEyDOi8RIdVppVir
---
A minimal TU: `#include "common.h"` then `#include "../shared/engine_prelude.h"` — the paths resolve with -Iinclude and -Isrc/shared? "common.h" from include/. "../shared/engine_prelude.h" relative to the file's dir. If I place my mini TU in .run/..., the relative path breaks.

I can instead write the mini TU with absolute-ish includes using -I: cc1_dumps_tu.sh passes -Iinclude -Isrc/shared and -I"$(dirname $tc)". If I put the TU in .run/P40/T11/W50x/<dir>/min.c, then `#include "common.h"` resolves via -Iinclude. For engine_prelude, I can write `#include "engine_prelude.h"` (found via -Isrc/shared). Good. Then the body.

But engine_prelude may include other things relative to src/shared; -Isrc/shared handles.

Let me write min.c in the item dir:
```
#include "common.h"
#include "engine_prelude.h"
extern s32 ratan2(s32,s32);
...
<body>
```
Then run cc1_dumps_tu.sh on it. But wait — the real TU has `-DINCLUDE_ASM(a,b)=` etc. Fine.

Actually, the struct is defined in include/struct_types.h, presumably included by common.h/engine_prelude. Let's just try.

Let me first test the minimal TU compiles and produces the same insn count as the real TU for the orig body. That validates the dump is faithful.

Actually, let me not over-invest. Let me try a batch of C variants first — scoring is cheap and may hit 0.

Variant ideas for item 1:
A. do-while around the copy.
B. dead-reset after the copy: `ang = a; a = 0;` — but $4=0 dead.
C. Reorder: move `d = ...` before `a = ...`? Target has andi before lbu, so d load after. Current order: a computed, then d load. Target: andi (part of a), then lbu d. So d after a. If we move d assignment before a in C, scheduling might still reorder. Probably not.
D. Declare `ang` before `a` (decl order).
E. Init `ang = 0` at decl.
F. Use `u32` for the andi source: `a = (ratan2(...) - 0x400) & 0xFFF;` already.
G. Assign ang via a second expression: `ang = a;` then use `ang` in the branch? no.
H. Make the copy go through `s16`:
```
s16 ang; ... ang = a;
```
Then res = (ang + ratan2(...)) & 0xFFF. ang s16 sign-extends when used in `ang + ...` → would emit sll/sra. Not target.

I. The target's `move s0,a0` is in the branch delay slot of beq. So the copy is scheduled into the delay slot. Maybe the C should place the copy AFTER the if? But a is clobbered by the call path. Actually on the `d==0x41` path there's a call, so a must be copied before. But the copy is unconditional at 34ac before the beq. So it must be early.

J. What if `ang` is set inside the first if only? No.

Let me think about which pass. Actually maybe the merge is done by local-alloc: the copy `ang = $4` — local-alloc may tie ang to $4? No, then it would be a0 and the andi would write a0 with no copy... but then ang=a0, and ang used across calls — conflict, so local-alloc wouldn't.

Hmm, the diff shows `andi s0,v0,0xfff` — so the andi's *destination* is s0. If a were hard $4, andi would write $4. So `a` was NOT hard $4 in the w1 build. Why? Because `register asm("$4")` is only honored when the variable is actually used in a way requiring it... Wait, but w1 still has the pin line (I only removed the keepalive). Let me check w1.c content: `grep -v keepalive` removed the keepalive line. The pin line `register s32 a __asm__("$4");` remains.

So with the pin but no asm use, the compiler apparently coalesced `a` into `ang` and allocated s0. That means the `register asm("$4")` did NOT force $4 — because GCC 2.7.2 local-alloc treats a user-specified hard reg as a preference only if... Hmm, actually there's a known behavior: `register asm` creates a hard-reg variable; but if the variable's live range can't use it or if... no.

Wait: maybe the pin DOES force $4, but then the `ang = a` copy is removed by *copy propagation* because a's value is still available: they merged the *pseudo* `ang` with the hard reg? Can't.

Let me just get the RTL. Build the minimal TU.

Actually — easier: I can run cc1_dumps_tu.sh directly on a full modified TU placed one level under src/... but I can't write to src/. However, the script's -I"$(dirname $tc)" and -Isrc/shared: if I place the TU at .run/P40/T11/W50x/<dir>/min.c and include "engine_prelude.h" via -Isrc/shared, it works. Let me try.

Let me write min.c with orig body and dump to verify 68 ins.
