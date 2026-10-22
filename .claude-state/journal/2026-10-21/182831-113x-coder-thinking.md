---
ts: 2026-10-22T00:28:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Rdr5lpx19Nqdex9DY6B8
---
V3: 9 (75 ins) — the same as V2. The temps still take $2/$3.

I notice: in the target, the loads are `lh a0,6(s0)` and `lh v1,160(s0)` — the FIRST temp in $4 (a0) and the second in $3 (v1). In mine: the first in $3, the second in $2.

Interesting: in the target, the temps take $4 and $3 — i.e. the allocator skipped $2 (reserved) and used $4/$3 ✓. In mine, the temps took $3/$2 (the first two free regs) ✗.

So if the RESULT_DECL's $2 were reserved from the block start, the temps would take $4/$3 ✓.

The RESULT_DECL's set is at the `li v0,1` (ins 55 in the target). Hmm, in the target the FIRST load pair (ins 51-52) comes BEFORE the set (ins 55) yet they're in $4/$3 ✗ (not $2).

So in the ROM, $2 was reserved for the whole block ✓ (the hard reg).

For lever-free: the RESULT_DECL (a global allocated $2) must be considered live from the block start. gcc's local-alloc reserves the hard regs of globals live in the block. The RESULT_DECL's live range: hmm, if the RESULT_DECL's set is at ins 55, it's not live at ins 51 ✗ → $2 is free for the temps ✗.

Hmm, unless the RESULT_DECL is live from the block start because of the EARLY `return 0;` in the source (the `if (q < 0x40 ...) return 0;` path) — hmm, that's a different block/path ✓ so the RESULT_DECL is set there too → its live range covers the whole function ✓ → so in the tail block, the RESULT_DECL IS live (from the function's start) → $2 should be reserved ✓✓.

Hmm! But the observed behavior contradicts that. Hmm, unless gcc's local-alloc treats the RESULT_DECL's set in the tail block as a new "birth" (local-alloc works on the pseudo's live range within the block: the RESULT_DECL's live range in the tail block starts at its set).

Hmm, the alloc table says the RESULT_DECL (r103) has "live 3" — hmm, that's short → so gcc thinks it's live only 3 insns ✓ (not the whole function) → so the early `return 0` didn't extend it (the two sets are in disjoint paths → the allocno's live length is the max over the paths? hmm).

OK, item 5 = WALL (best 9). I've got solid evidence.

Let me now consider whether to keep going on item 9 or stop. Item 9's residue: the callee-saved bank permutation (t/r and the loop counter). The lever-free allocation differs from the ROM's in which pseudo gets $16/$18/$19.

Per the priority formula: t (refs 4, live long) vs r (refs 3, live short) vs i (the loop counter).

In the ROM: t → $18, r → $16, i → $19.
Lever-free: t → $16, r → $18, i → $19?

From the Q1 diff (i pinned): the target had t → $18 and r → $16; mine (i pinned, t free) had t → $16 and r → $18.

So the ROM's order (by priority): r ($16) > t ($18) > i ($19)? Hmm, that means r has the HIGHEST priority ✗ (r has fewer refs).

Hmm, unless the callee-saved regs are allocated in the OPPOSITE order (the lowest priority gets $16). In gcc's global-alloc, the callee-saved regs are allocated to the globals in the order of the .greg "order" line — hmm.

Hmm, whatever: the ROM's assignment (r=$16, t=$18) vs the lever-free (t=$16, r=$18) — a swap. The tie-break/priority decides. To flip, `r` needs more refs or `t` fewer.

`r`'s refs: `r = rand() & 7;` + 2 uses = 3.
`t`'s refs: the call + 3 uses = 4.

Hmm, what if `r` were used 4 times? E.g. if the source computed the two products with a shared temp... hmm.

What if `t` had 3 refs? t is used 3 times (t != 0, t+0x10, t+0x18) — the ROM needs those ✓.

Hmm, what if the source assigned `t` to a variable that's used twice by combining the two stores?
```c
            t = func_8012C658(0x265, 2, a0);
            if (t != 0) {
                r = rand() & 7;
                *(s32 *)(t + 0x10) = ...;
                *(s32 *)(t + 0x18) = ...;
            }
```
The ROM's code: `move s2,v0` (t → $18) then the stores use $18 ✓ (`sw v0,16(s2)` — the target's store base is s2 = t ✓).

Hmm, what if the source used a pointer temp:
```c
            t = func_8012C658(0x265, 2, a0);
            if (t != 0) {
                r = rand() & 7;
                t2 = t;
                *(s32 *)(t2 + 0x10) = ...;
                *(s32 *)(t2 + 0x18) = ...;
            }
```
✗ (an extra copy).

OK. Item 9 = WALL.

Let me now spend a little effort double-checking that my two MATCH items are complete and correct, and then finalize.

Actually, one more consideration for the MATCH items: the brief says "MATCH = the kinds in <dir>/kinds gone". For items 6/7, kinds = "pin" ✓ and the pin is gone ✓ (no `register ... __asm__` in win.c) ✓. Let me verify there's no "register"/"__asm__" in the win.c files ✓ (I wrote them without).

Also: "Lever-free = ... no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." My win.c for items 6/7: no __asm__, no volatile, no barriers ✓. Hmm, the call-site cast — is that a "lever"? It's not in the taxonomy (pin/launder/barrier/keepalive) ✓ and moves.md records it as a MATCH lever ✓.

Hmm, one thing to double check: the `((s32 (*)(void *))func_80161418)` cast — gcc might warn "cast from function pointer of type 'void (*)(void *)' to 's32 (*)(void *)'"? No warning for function pointer casts ✓.

Let me also verify: does the win.c body keep the `reserved[4]` array + `(void)reserved`? ✓ yes (kept from the original). Hmm, the `reserved` array is a padding artifact to match the frame size ✓ (it's in the original) ✓.

Now let me finalize the deliverables and write the report. Let me do a final listing of the shard dir + a final check of results.tsv + the moves.md tail.

Also, I should double check that I haven't broken anything outside my shard: I only wrote under .run/P40/T11/G08/, .run/P40/T11/moves.md, and phase-ends/current/logs/T11.cG08r.md ✓.

Let me do the final checks.
