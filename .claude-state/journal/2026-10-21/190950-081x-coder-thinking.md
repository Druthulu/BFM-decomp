---
ts: 2026-10-22T01:09:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_jR0Is1urIw3OHwUNidZI
---
The header is self-contained (it has the externs).

Now, for the alloc table, I can create a small .c file:
```c
#include "common.h"
#include "../shared/engine_prelude.h"
extern void func_80149290(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
int func_8014FD54(int param_1) { ...my body... }
```
and run cc1_dumps_tu.sh on it with DUMP_ROOT set to my item dir. But the script uses `$DUMP_ROOT` env var — I can set it in the command: `DUMP_ROOT=/abs/path bash tools/cc1_dumps_tu.sh <file> <tag>`. Env var prefix in the command — the classifier might allow it (it's a single command).

But first: is the alloc table worth it? The question is how to make the RESULT_DECL win $2. Let me think about gcc 2.7.2's actual allocation rules:

In gcc 2.7.2's global.c, the pseudo allocation order is by priority; the RESULT_DECL is a pseudo with a preference for the return register. The call result pseudo also prefers the return register.

The note said: the call-result pseudo (refs 4, live 7 → pri 11428) vs the RESULT_DECL (refs 3, live 4 → pri 7500).

Hmm, "refs 4" for the call result but pri 11428 = 8*10000/7. So refs=8.

To beat it: the RESULT_DECL needs pri > 11428 → refs*10000/live > 11428. With live 4: refs ≥ 5.

The RESULT_DECL's refs: how many times the RESULT_DECL is referenced = the number of sets of the RESULT_DECL (each `return X` = 1 set). So I need 5 returns?! That would change the code.

Hmm, unless the live range can be shortened: live 3 → refs ≥ 4 (4*10000/3 = 13333 ✓); live 2 → refs ≥ 3 (15000 ✓).

The RESULT_DECL's live range: [the first set .. the end of the function]. In the target, the first set is at ins 28 and the function ends at ins 39 → live ≈ 11 insns. But the note says live 4 — maybe "live" counts something else (the number of insns in the live range in the RTL, which could be ~11).

Hmm, pri = refs*10000/live. With refs 3 and live 4 → 7500. So "live 4" must be the RTL live range length ≈ 4 insns. Hmm, that means the RESULT_DECL is set very late in ours.

So in ours, the RESULT_DECL's live range is 4 (short) → pri 7500. In the target, the RESULT_DECL is set early (ins 28) → a longer live range → a LOWER priority?! Then how did the target's RESULT_DECL win $2?

Unless the priority ordering isn't what decides. Hmm.

Let me reconsider: maybe in the target, the call-result pseudo ISN'T competing for $2 — maybe the call result went to $3 for a different reason: e.g. the call's return-value pseudo has a preference for $2, but the RESULT_DECL... hmm.

Wait. Actually, maybe the difference is the "hard reg" copy: the previous coder's note said the pinned `result` variable was a HARD REG $2. In the pinned version, the RESULT_DECL's copy `move RESULT_DECL, result($2)` — with result being a hard reg $2 and the RESULT_DECL preferring $2 → the copy is elided → the RESULT_DECL is $2 ✓ and the call result... hmm.

In the pinned (original) version, the target's code is reproduced. The key difference in the pinned version: the RESULT_DECL and the pinned `result` var are both $2 → so $2 is RESERVED for the result from the function's start (the pinned var's live range starts at its first set...). Hmm, in the target, the pinned `result` var's set: `result = 0` at ins 28 (the delay slot) and `result = (byte == 0x15)` at ins 33.

Hmm, so $2's occupancy starts at ins 28 in the target too.

OK, so why does the target's call result go to $3?

Hmm! Maybe because of the CALL at ins 22: the call clobbers $v1-$v0? No, $v1 ($3) is callee-SAVED. So the call result can't be in $3 ($3 = s1/v1 is callee-saved — the call would preserve it, but the call result is in $2 by the ABI).

AH WAIT. That's the key! The call's result comes in $2 ($v0). If the call-result pseudo were allocated $3 ($v1, callee-saved), then the value must be copied from $2 to $3 — and the copy must happen BEFORE any call... but the copy happens right after the call ✓ (no call in between) — fine, the value in $3 survives until the end (it's callee-saved, and the function's epilogue restores $3? hmm, $3 = s1? no: $3 = $v1 is a SAVED register? In MIPS O32: $v0-$v1 = $2,$3 are CALLER-saved (temporaries). $s0-$s7 = $16-$23 are callee-saved. So $3 = $v1 = caller-saved → the call result can't live in $3 across a call — but there's no call after ✓.

So the target's `move v1,v0` puts the call result in $3 ($v1) — a caller-saved reg, fine.

So the question stands: why $3 and not $2?

Because $2 was reserved for the RESULT_DECL! And in ours, the RESULT_DECL's live range is short (4) so $2 was free at the call... no wait, $2 is where the call result IS.

Hmm, let me think about it as: the call result pseudo is allocated a reg; the RESULT_DECL is allocated a reg; both prefer $2. One gets $2.

In the target: the RESULT_DECL got $2 (the return value is computed in $2: `lbu v0`, `xori v0`, `sltiu v0` ✓ — those are $2 = the RESULT_DECL's reg).
In ours: the call result got $2 and the RESULT_DECL got... hmm, in ours (P1), the return value is computed in $2 too? Let me check P1's diff: mine[24] `beqz v0` — so mine's ins 24-26 test $2 (the call result) and the byte computation would be in $2 as well? P1's diff only showed ins 24-28 and 31-32 differing; the rest matched — so mine's ins 29-30 = `lbu v0,30(sp)` ✓ (the same $2) and ins 33 `sltiu v0,zero,v0` ✓. So in ours, $2 holds the call result (ins 24-27) and later the return value (ins 29-33) — sequentially ✓, and the RESULT_DECL is $2 too.

So the difference is just whether the call result is copied out to $3.

In the target, the call result is copied to $3 → the call-result pseudo got $3 → the RESULT_DECL got $2 → and the call-result pseudo was NOT coalesced with the `ret` variable (or `ret` IS the call-result pseudo in $3 and the copy is the reload copy from $2).

In ours, the call-result pseudo got $2 and `ret` was coalesced with it (no copy).

So: in the target, the RESULT_DECL won $2 over the call-result pseudo.

To flip this in ours, the RESULT_DECL must have a higher priority. The note says the RESULT_DECL has refs 3, live 4 → pri 7500; the call result refs 8, live 7 → pri 11428.

Hmm, since the target's code has the same structure, its ref counts should be identical... unless the ref counts depend on the SPELLING (e.g. the number of times the RESULT_DECL is referenced = the number of `return` statements in the source, and the call result's refs = the number of uses).

So the game's source probably had MORE return statements (or the same) — hmm.

Let me approach empirically: try to raise the RESULT_DECL's refs by adding return statements, and see if the score improves. The constraint is that the instruction count must stay 40 and the shape identical. Hmm.

What if the source is:
```
ret = func_80133784(1, buf1, (int)buf2);
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        return byte != 0x15;
    }
    return 0;
}
return 0;
```
= P1: 3 returns.

What about:
```
ret = func_80133784(1, buf1, (int)buf2);
if (ret == 0) {
    return 0;
} else if ((ret & 0x8000) == 0) {
    return 0;
} else {
    return byte != 0x15;
}
```
Same 3 returns.

Hmm, what if the byte comparison is split into two returns?
```
b = *(u8*)((char*)buf2+6);
if (b == 0x15) return 0;
return 1;
```
→ the code: lbu, xori?, beq/bne, li ✗ (the target has sltiu).

Hmm. Unless... `return b != 0x15` vs `return (b ^ 0x15) != 0`: the latter → `xori` then `sltiu`? Hmm: `b ^ 0x15` → xori; `!= 0` → sltu? For an unsigned comparison `!= 0`, gcc emits `sltu v0,zero,v0` ✓ (the target's ins 33 = `sltiu v0,zero,v0` — sltiu!). Hmm, `sltiu` is the unsigned "less than immediate" — for `x != 0` with x unsigned, gcc 2.7.2 emits `sltiu v0,zero,v0`? That's "set if 0 < x unsigned" ✓ (sltiu reg,zero,reg) — yes ✓.

So `return (b ^ 0x15) != 0` would give: lbu, xori, sltiu ✓ — the same 3 instructions! And it might have a different ref structure. Hmm, but that's the same as `b != 0x15` (gcc computes b^0x15 then !=0). Actually `b != 0x15` → gcc: xori then sltiu ✓ — the same.

OK, so how do I get more RESULT_DECL refs? What if the source returns 0 in a way that has 2 sets? E.g.:

```
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        return byte != 0x15;
    }
    return 0;
} else {
    return 0;
}
```
P1 has the same 3.

Hmm, what if we write:
```
result = 0;
if (ret != 0) {
    if ((ret & 0x8000) != 0) {
        result = byte != 0x15;
    }
}
return result;
```
= nopin (2 sets: the init and the value) → pri lower.

Hmm, so the target's 3 RESULT_DECL sets come from 3 returns ✓ (as in P1).

So the ref counts are the same in P1 and the target?! Then the priority difference must come from the CALL RESULT pseudo's refs/live — which depend on the source's use of the call result. In the target, the call result is copied to $3 → so the call-result pseudo is $3 and `ret` is coalesced with it.

Hmm, so what's different? In the target, the call-result pseudo has a preference for $2 but got $3. That means $2 was NOT available for it — the RESULT_DECL took it. And the RESULT_DECL's priority must have been higher in the target's source.

So the target's source must have a different RESULT_DECL ref count than P1's. With P1's 3 returns... hmm, unless the number of refs isn't the number of returns but the number of REFERENCES to the RESULT_DECL pseudo in the RTL — including the copies. Each `return X` → `move RESULT_DECL, X` = 2 refs (dst + src) → 3 returns = 6 refs? And the call result: 8 refs.

Hmm, with 6 refs and live 4 → pri 15000 ✓ > 11428! Hmm, that contradicts the note (3 refs).

I'm over-modeling. Let me just try to shift the allocation empirically with a few variants and observe the diff. Specifically, try to make the call result live in $3 by adding pressure on $2 at the call point: e.g. introduce a variable that's live across the call and allocated $2.

Hmm! What about `param_1`? In the target, param_1 is copied to s0 ($16) at ins 2 and reloaded at ins 11 (`move a0,s0`). So param_1 is in $16 ✓ (both in ours and the target, since the diff didn't show ins 2/11).

Hmm, what if the source kept param_1 in a variable (rather than letting gcc put it in s0)? E.g. `int p = param_1;` → gcc would still use $16 probably.

What about the buffers? buf1 is at sp+16 and buf2 at sp+24 ✓.

Hmm, what if the source declares a variable that is live across the call and would take $2? E.g.:

```
int ret;
int keep = 5;    /* live across the call → takes a reg */
```
That would add instructions ✗ (unless dead-code eliminated — but then it's not live).

Hmm.

Let me try the alloc-table route after all: dump the cc1 allocation for P1 and see the priorities. Then I can reason precisely.

To dump: create a .c file with the function (my body) + the needed includes, then run cc1_dumps_tu.sh with DUMP_ROOT under my item dir. Then run tools/alloc_table.py.

The .c file needs: common.h? The header uses s32/u8 types → those come from common.h/engine_prelude.h. Let me write:

```c
#include "common.h"
#include "../shared/engine_prelude.h"
extern void func_80149290(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
int func_8014FD54(int param_1) { ...P1 body... }
```
Hmm, the include paths: cc1_dumps_tu.sh uses `-Iinclude -I$(dirname tc) -Isrc/shared`. My file lives in .run/P40/T11/G08b/func_8014FD54__func_8014FD54/ → the include "../shared/engine_prelude.h" would resolve relative to that dir ✗. But `-Isrc/shared` is there ✓ → I can write `#include "engine_prelude.h"`. And "common.h" resolves via -Iinclude ✓.

Let me write the file and run the dump. Note: the dump dir must be under my shard dir (absolute path) and I must delete it after reading (disk cap).

Let me do it.
