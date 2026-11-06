---
ts: 2026-10-22T20:49:53Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_anHy3IBbMe4zXFgi1QDx
---
Wait, the time is 14:49, not 14:57. My estimates were off — the clock: item 2 started 14:36, now 14:49 = 13 min. Hmm, that's under 20 min for the WALL requirement ("a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)"). Tries: 55 (35 prior + 20 mine) — satisfies ≥30 tries. But minutes = 13. Hmm. The rule: "Budget 20-30 min wall per item (date at start/end); past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries".

I have ≥30 tries but only 13 min. I should spend ~7 more minutes on this item to meet the 20-minute bar, OR consider that the prior coder's work on this item (the gen_* files, created 07:13) counts toward the item's time — they were made in the earlier run. The brief's carry mentions only func_8012B4B8's earlier time. But the item clearly had prior work (35 candidates). The time spent generating them isn't recorded here.

To be safe and honest, let me spend a few more minutes trying ideas, which also improves the chance of a crack. I already recorded the row; I can update it later if I find better (the brief says exactly one row per item; I can rewrite the row if needed — I'd have to edit results.tsv, which is my file under the shard. Allowed).

Let me think of more ideas for the REG_EQUAL fold:

The note is on the `p = it + K` insn. Reload rematerializes the constant. What if the add's *operand* is not a symbol but a *register that reload must keep*, e.g. `it` assigned from a symbol but then *used in a compare before the add* — that doesn't stop the note.

What if `it`'s value is assigned from a *conditional expression involving a0*, e.g. `it = (a0 == a0) ? (s32)D_80120194 : 0;` — folded.

What if the else branch's it is assigned *inside an if*:
```
it = (s32)D_80120194;
if (*(u16 *)(a0 + 0xA) & 0x400) it += 0;  // adds code
```
no.

What about making `p`'s definition have no note because the add is not a simple plus: e.g. `p = it - (-0x658C);` — gcc canonicalizes to plus.

What about `p = it + 0x658C;` where `it` is declared `u32` and p `s32`: the note would still be const.

What if the add is `p = it + 0x658C` and `it` is a *pointer to a function*? no.

What if we add a *use* of `it` that is a memory store the compiler can't remove, placed after the add but before the jump? e.g. `*(s32 *)(a0 + 0x40) = it;` — that's a real store (changes code + semantics).

What if we use the *flag* store? no.

Alternatively, prevent reload from rematerializing by making the constant "expensive": reload rematerializes constants only if `CONST_OK_FOR...`? A symbol+offset is rematerializable. If the add were `it + K` where K is a *variable* (not constant), no note — but then addu with the variable (n2's invalid case; with a real variable it'd need to hold K somewhere).

What if the variable holding K is assigned from a *symbol* too? `off = (s32)&D_801202A0 - ...`? The difference of two symbols isn't a link-time constant → gcc can't fold it! E.g.:

```
s32 off = (s32)D_801202A0 - (s32)D_80120194;  // not a constant at compile time
```
Hmm, but then off is a runtime subtraction (2 insns) and the add is addu. Code changes.

What if `off` is a *parameter*? no.

OK, what about attacking the note differently: cse1 adds the note; cse2 might use it. If the value p were *killed* before use (e.g., redefined), the note wouldn't matter. The compare uses p...

What if I reorder so that `p` is used before the note's fold? no.

Let me try the "p = it + K" where `it` is assigned from a symbol *and* used in a way that makes gcc not treat it as a constant: specifically, take the address through a *dereference of a pointer variable*: 
```
s32 *ip;
ip = (s32 *)&D_80120194;   // ip is a pointer to the symbol
it = (s32)ip;              // cast pointer to int
p = it + 0x658C;
```
cse folds ip to the constant.

What about `it = (s32)(u8 *)&D_80120194;`? same.

Hmm.

What about using the *second* launder site: the def has a launder at `it = (s32)D_801202A0;` too. Why? To stop folding of `beq v1,a1` maybe. Removing both is needed.

I'll try a couple of "different constant" ideas and then stop:
- q1: `p = it + 0x658C - 0;`? folded.
- q2: `p = it + (s32)0x658C;`? folded.
- q3: use `it` as `long` (32-bit?) — gen_decl_long tried.
- q4: compute p via `it ^ 0` then add? folded.
- q5: `p = it + 0x658C;` with a `volatile` local `s32 t; t = it; p = t + K;` — adds a store/load (2 insns) but t's value is a memory load → no note → `lw t; addiu`. Score would be ~6. Not better than 4.

Hmm, what about making the *definition* of p be a memory value that reload can't rematerialize... 

Actually! Idea: if p is used as a *call argument* (a1) and in compares, reload rematerializes because the constant is cheap. What if p's uses include one that requires a *register-to-register copy* (e.g., `a2 = p`)? The call uses a2=0. No.

Let me try: does `it` being live at the add matter? p2/p4 tried `it = base`. Let me try making `it` live *after* the add with a use in the copy block *of the first it* — semantically wrong but let's see if the fold disappears (diagnostic):

```
else {
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    p = it;      // this uses the reassigned it
```
The compiler sees copy dominated by test's reassignment.

What if the copy block's `p = it` is *before* the test label in a way that... no.

Diagnostic: change the copy block to `p = it + 0;`? no.

Let me try a *different structural* idea: move the `p = it + K` computation to *after* the `test:` label, before the compare, using a saved it? no.

Honestly, the wall is solid. The 20-minute rule: I have 13 min + the prior coder's 35 candidates (unknown time, but clearly substantial). I'll spend 7 more minutes on a batch of 8-10 variants to be safe, then finalize.

Let me generate a batch exploring:
r1: `p = it + 0x658C;` with it declared `s32 it = (s32)D_80120194;` (init at decl, in the else block).
r2: same but `register s32 it`.
r3: `p = (s32)((u8 *)it) + 0x658C;`
r4: `p = it + 0x658C; if (0) p = 0;` (dead code, maybe blocks the note? no)
r5: two statements: `it = (s32)D_80120194; p = it; p += 0x658C;` (=n5, 4)
r6: `p = it + 0x658C;` where it is assigned from `(s32)(D_80120194)` and D_80120194 is cast through `(void *)`? same.
r7: `it = (s32)D_80120194; if (a0) {} p = it + 0x658C;` — an empty if might split the BB? `if (a0) {}` is optimized away but may create a BB split before the fold → cse1 per-BB → no note! Worth trying.
r8: `it = (s32)D_80120194; if (a0) goto test; p = it + 0x658C; goto test;` — adds a real branch (2 insns), probably worse but tests BB splitting.

r7 is interesting. Also:
r9: `it = (s32)D_80120194; if (a0 == -1) { p = 0; } p = it + 0x658C;` — changes code.

Let me try r1, r2, r3, r7, and a variant where the add is in the test block:
r10:
```
else { it = (s32)D_80120194; goto mid2; mid2: p = it + 0x658C; goto test; }
```
(= n1, 4).

And r11: put a `do { } while (0);` between the assignment and the add (a loop note between them).
r12: `while (0) { }`? optimized.

Let me test r1,r2,r3,r7,r11.
