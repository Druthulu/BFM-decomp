---
ts: 2026-10-22T00:07:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_3WWmANN0tea5HZ4I1kET
---
All 19. The v0/v1 swap persists.

Let me think about the "local-alloc order" differently. Since p is created first and gets v0, maybe gcc's local-alloc sorts by live length: p's live is longer (from insn 1 to 11) and the value's live is shorter (6 to 11). If sorted by DECREASING live length, p would go first → p gets v0 ✓ (mine). To flip, the value's live must be LONGER than p's.

The value's live: from its definition (`lw v0,16(v1)`) to its last use (`sw v0,20(v1)`).
p's live: from `lw v1,0(v1)` to `sw v0,20(v1)`.

To make the value's live longer, its definition must be EARLIER. Hmm — the value is defined by the load which needs p. ✗

To make p's live SHORTER: p's definition (the load) is first... its last use is the last store. Hmm.

Hmm! What if p is NOT needed for the last store? E.g. what if the stores use a different expression that doesn't need p's register but the same address? Like `*(s32 *)((u8 *)D_801151D4 ...)` hmm, no: the stores are through p.

Hmm, what if the pointer is re-loaded for the last store? `((Unkstruct_80126948 *)D_801151D4)->unk14 = v0;` — semantically WRONG (D_801151D4's value vs address).

OK. Alternative: make the value's live longer by using the value BEFORE... hmm, the value is defined by the load.

Hmm, what if the value's live extends by keeping it alive longer — e.g., using v0 after the stores? The last use of v0 in the source is the unk14 store. If I add a use of v0 after (e.g. `if (v0 == 0) ...`), the live extends but the code changes ✗.

Hmm, what about making the value pseudo live longer by moving its DEFINITION earlier — impossible.

So: if local-alloc sorts by decreasing live length, I need value_live > p_live.

value_live = (last use of v0) - (def of v0).
p_live = (last use of p) - (def of p).

The def of p is 2 insns before the def of v0 (lui, lw, lw). The last uses are the same instruction (`sw v0,20(v1)`).

So p_live = value_live + 2 always. To make value_live > p_live, the value's def must move earlier relative to p's last use. Impossible.

UNLESS the value has a longer life because it's ALSO used later... no.

Hmm, so if the sort is by decreasing live length, we can never flip. So the sort must be by something else (allocno order).

Hmm, but wait: the moves.md wall "lreg-v0-local-first" says: "local-alloc gives block-local cmp temps v0 before global ret(r77) is allocated; target needs ret in v0 live across blocks". So local-alloc gives v0 to the "block-local cmp temps" — i.e., locals get v0 first.

And in the target here, the value pseudo got v0 and the pointer v1. So the value pseudo must be "first" in local-alloc's order.

Hmm, in the target, maybe the pointer pseudo is NOT a local but a global? Hmm: if p crossed a call it'd be global → callee-saved. The target has p in v1 (caller-saved) so p is local.

Hmm, so in the target, BOTH are locals and the value got v0.

Hmm, so the local-alloc order isn't purely by allocno.

Let me reconsider: maybe local-alloc sorts by (local_size desc, then live length desc)? Then p (longer live) would be first ✗. By live length ASC? Then the value (shorter live) is first → value gets v0 ✓ TARGET! But mine gave p → v0 ✗.

Hmm, contradiction. Unless my live-length estimates are wrong.

Hmm, let me just get the alloc table for this function! I have the machinery (cc1_dumps_tu.sh + alloc_table.py). The TU is src/ov_SC07_010/ov_SC07_010_jr_8017AE2C.c — a real TU (huge). The dump would be for the whole TU. Hmm, cc1_dumps_tu.sh takes a file; I can pass the real TU file. But I need MY candidate, not the current src (which has the pin).

Hmm: I can create a scratch copy of the TU with the candidate body spliced in. The TU is 5900+ lines — I'd need to copy it. Copying is denied via `cp`... but I can use python (run.sh) to copy and splice. Hmm, that's a big file copy — fine.

Actually, simpler: the alloc table would tell me the refs/live and the ORDER for the two pseudos. Let me do it — it's the sanctioned diagnostic.

Plan:
1. Write a python script that reads src/ov_SC07_010/ov_SC07_010_jr_8017AE2C.c, replaces the function definition (from "void func_80180480(s32 a0) {" to the matching "}") with the candidate body, and writes it to <itemdir>/tu_c1.c.
2. Run cc1_dumps_tu.sh on it (DUMP_ROOT under the item dir).
3. Run alloc_table.py.
4. Delete the dumps.

But the padding check: the real TU is huge → fine.

Hmm, but the dump of a 5900-line TU with all those functions might be slow but OK.

Hmm, wait. Actually, the whole TU has ~100 functions; the dumps would be big but fine.

Hmm, but actually: is it worth it? The alloc table gives refs/live/priority for the locals and the ORDER. It would tell me the rule. But the .lreg dump shows local-alloc's pseudo→reg assignment, and the .greg dump shows global-alloc's.

Hmm, but the alloc_table tool focuses on globals. For locals it prints "hard" from the .lreg dump.

Alternatively, I could use the .lreg dump directly: it shows the RTL after local allocation, with the pseudo names replaced by hard regs. Not helpful for the ORDER.

Hmm, what I really want is the local-alloc ORDER. gcc 2.7's local.c doesn't print an order line.

Hmm. Let me think about the time budget. I've spent ~2h. I have 4 items left to do (80181E64, 800D2650, 8003DF8C, 801415C0) plus 2 partially done (80180480, 800D0D7C).

Let me prioritize: 
- func_80180480: close (score 19, only a reg swap).
- func_800D2650: 4 pins — probably hard.
- func_80181E64, func_8003DF8C: $0 zr opaque copies — likely hard (same as 800D0D7C).
- func_801415C0: the local/global allocation issue.

Let me spend a bit more on 80180480 since it's so close.

IDEA for 80180480: what if the pointer p is used only ONCE in a way that lets gcc... hmm.

IDEA: What if I write the stores using the pointer value loaded inline, and keep p only for the load? Hmm:
```c
p = D_801151D4;
v0 = ((Unkstruct_80126948 *)p)->unk10;
v0 = v0 - 3;
((Unkstruct_80126948 *)p)->unk10 = v0;
((Unkstruct_80126948 *)p)->unk14 = v0;
```
Hmm.

IDEA: What if the VALUE is stored to a variable that is created FIRST by declaring the value first and using an initializer? C89: declarations with initializers are allowed at the top.
```c
s32 v0;
s32 p;
p = D_801151D4;
v0 = ...
```
Already tried (e1) — no change.

Hmm, so declaration order doesn't matter (pseudo creation order is by RTL).

IDEA: What if the two stores are done via a struct assignment? e.g.
```c
*(s32 *)((char *)p + 0x10) = v0;
*(s32 *)((char *)p + 0x14) = v0;
```
(f4 — no change).

IDEA: What if the value variable is `s16`?? no.

IDEA: **What if the pointer is dereferenced via a `char *` and the offset is added to the pointer first?** e.g.
```c
p = D_801151D4;
v0 = *(s32 *)((u8 *)p + 0x10);
```
That's f4 ✗ no change.

Hmm, let me look at the actual difference in the generated code between mine and the target once more:
mine: `lui v0,0x0; lw v0,0(v0)` (p in v0), `lw v1,16(v0)` (value in v1).
target: `lui v1,0x0; lw v1,0(v1)` (p in v1), `lw v0,16(v1)` (value in v0).

The ONLY difference is which reg. Everything else identical.

Since both pseudos are locals, local-alloc picked v0 for the first-created pseudo. To flip, I need the value pseudo created first.

**!!!!!!!!!!!! NEW IDEA !!!!!!!!!!!!**
What if the pointer's value is NOT loaded from memory but the SOURCE reads it via a different expression that makes the load happen INSIDE the value's expression, so the pointer pseudo is a TEMP created after the value pseudo? Impossible — the load must precede.

**!!!!!!!!!!!! NEW IDEA 2 !!!!!!!!!!!!**
What if I make the pointer a **hard reg** by... no.

**!!!!!!!!!!!! NEW IDEA 3 !!!!!!!!!!!!**
What if the pointer pseudo's live range is EXTENDED to after the call, making it a global? Then global-alloc would give it a callee-saved reg ✗.

**!!!!!!!!!!!! NEW IDEA 4 !!!!!!!!!!!!**
What if the VALUE is a global (crosses a call) and the pointer is local? Then global-alloc gives the value a callee-saved reg ✗ (target: v0).

Hmm, all wrong.

**!!!!!!!!!!!! NEW IDEA 5 !!!!!!!!!!!!**
Hmm! What if there are MORE locals, and the extra local takes v0 — then the pointer would take v1 and the value v2? ✗ (target: value in v0).

Hmm. So the value MUST get v0.

Hmm, so the value pseudo must be allocated before the pointer pseudo.

WAIT!!! What if the value pseudo's ALLOCNO is lower because the value's RTL is emitted before the pointer's? The RTL emission order follows the source order of the statements. So if the source computes the VALUE before the POINTER... but the value depends on the pointer!

UNLESS the source uses a DIFFERENT source of the pointer value for the first load! Like:

```c
v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;   /* WRONG semantics */
```
✗.

Hmm, unless D_801151D4 IS the pointer... wait! Let me re-check: `p = D_801151D4;` — D_801151D4 is `extern s32 D_801151D4;`. So p = the s32 VALUE stored at D_801151D4. The target: `lui v1; lw v1,0(v1)` → v1 = *(D_801151D4) ✓.

So the value of p is a runtime pointer. And `((Unkstruct_80126948 *)p)->unk10` = *(p + 16).

Hmm, so the pointer load must come first. ✗

Hmm, unless... gcc's RTL for the second load is `lw v0, 16(v1)` where v1 is p's pseudo. The pseudo v0 is created at that point.

Hmm, unless gcc reuses p's pseudo for the value?! No.

OK, alternative: maybe local-alloc's order is by allocno but the allocnos are assigned in a different way. Hmm.

Let me try a completely different tactic: what if I add an extra use of the value BEFORE the pointer is defined? Impossible.

Hmm, what if the pointer is defined EARLIER and the value's use is later? That's the current state.

Hmm, so with p created first, p gets v0. To get the value in v0, p must get v1 — meaning p is allocated second.

**What if there were a THIRD local created before p?** Then that local would get v0, p would get v1, and the value v2 ✗.

Hmm, unless the third local is dead/merged.

Hmm! What if the third local is the value itself, created before p? 

```c
s32 v0;
s32 p;
v0 = 0;             /* v0's pseudo created first! */
p = D_801151D4;
v0 = ((Unkstruct_80126948 *)p)->unk10;
```
Then v0's pseudo is created first → v0 gets v0 (reg 2) and p gets v1 (reg 3) ✓✓✓!!! And the extra `v0 = 0` would be dead code → gcc removes it, but the pseudo number might already be assigned! 

Hmm, does gcc assign pseudo numbers at expand time (before dead-code removal)? Yes — pseudos are numbered during expand. So `v0 = 0` creates pseudo N (the first), then p's pseudo N+1, then the value's pseudo... hmm, wait: if `v0 = 0` is dead, gcc's flow/jump would eliminate it, but the pseudo number was already assigned to v0's pseudo. Then when the real value is assigned to v0, gcc reuses the same pseudo (v0 is the same variable!) → the pseudo keeps its low number ✓.

So: `v0 = 0;` first would make v0's pseudo the FIRST local → v0 gets the first local reg (v0=$2) ✓, and p gets v1 ($3) ✓.

But will the extra `v0 = 0;` be eliminated? gcc's flow analysis will see the set is dead (overwritten before use) → the jump pass removes it → no extra instruction ✓. Hmm, but it might affect the local-alloc (the pseudo's live range starts at the dead set). Hmm, if the set is removed, the live range starts at the real def.

Hmm, but the pseudo NUMBER is what matters for the allocno order. Hmm, but is local-alloc's order by pseudo number? I'm not sure, but it's worth testing!

Hmm, but hold on: is `v0 = 0;` "a new lever"? It's a dead store — the "identity-statement launder" rule says identity statements don't count as a crack. A dead assignment `v0 = 0;` is similar in spirit (a no-op statement). Hmm. It's a "real C move"? The C0505 catalog mentions "temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl". A dead store isn't in the catalog. Hmm. But if it produces byte-identical code, it's arguably a legitimate spelling. Hmm, risky. It's effectively a "statement order" move.

Hmm, but hmm: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack" — that's specifically about laundering a VALUE (a pseudo laundering to break cse). A dead store isn't laundering a value.

Let me try it and see if it works. If it does, I'll consider whether it's acceptable. Actually, a cleaner variant: initialize at declaration!
```c
s32 v0 = 0;
s32 p;
```
Hmm, but then the init is at declaration → gcc might keep the pseudo's number early ✓ and the dead store removed ✓. That's a legit "init at decl" move from the C0505 catalog! 

Hmm, but careful: `s32 v0 = 0;` then `v0 = ...` — gcc's expand creates the pseudo for v0 with the init at the function start. The init is dead → removed.

Hmm, but does the dead init affect the pseudo's live range start? If removed, no.

Let me test: g1 = c1 with `s32 v0 = 0;` at the top.

Hmm, but actually: will the dead store `v0 = 0` really be removed? gcc's "jump"/"flow" pass removes a set whose value is unused. Yes, typically.

Hmm, but the local-alloc might then see the pseudo's live range as starting at the real def. But the pseudo NUMBER is what I hope matters.

Let me test it. Also test the variant with an explicit `v0 = 0;` statement.

Let me also think: maybe the local-alloc order isn't by pseudo number but by something else, and this won't work. Empirical test is cheap.

Let me write g1, g2, g3:
g1: `s32 v0 = 0;` at declaration.
g2: `v0 = 0;` as a statement before `p = D_801151D4;`.
g3: `p` declared with an initializer: `s32 p = D_801151D4;` and `s32 v0 = 0;` — hmm, order.

Let me write them.
