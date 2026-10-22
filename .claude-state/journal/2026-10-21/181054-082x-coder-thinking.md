---
ts: 2026-10-22T00:10:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_lN5xr5JUoCdr2KtNrzEA
---
Hmm, "Register dispositions:" is empty for our function (it printed for pad_fn_14). And "Hard regs used: 2 3 4 5 16 31" — so v0($2), v1($3), a0($4), a1($5), s0($16), ra.

So the locals got v0 and v1, and the globals got s0 ($16) for r74 (a0's copy) and $17 for r72? Hmm, "Hard regs used" doesn't list 17 ($17). So r72 was allocated $17? No — 17 is $17, not listed. Hmm, the list is "2 3 4 5 16 31" → $2,$3,$4,$5,$16,$31. So only ONE callee-saved ($16).

So the globals: r74 → $16, r72 → ??? Hmm, r72 has pri 750, crosses 11 calls — hmm, it must be in a callee-saved reg. But $17 isn't in the list. Hmm, so maybe r72 = the `a0` param in $16, and r74 = ... hmm.

Whatever. Let me now try the decisive experiment differently: let me test whether the local-alloc order is by priority by making a change that alters the pointer's priority a lot.

Hmm, time. Let me step back and consider the overall budget. I've spent 2.5h on 3 items (1 MATCH). 4 items remain. The remaining ones are likely harder.

Let me reconsider the approach for func_80180480: what if I make the POINTER's live range longer so its priority drops below the value's?

The pointer's live = 12 (per the table, r73). The value's live = 6.

Hmm, what if the pointer is loaded EARLIER in the RTL — i.e., before the frame setup? It already is (the load is first).

Hmm, the pointer's live 12 vs the value's 6: the difference is 6 (the load + frame setup + the value's load). Makes sense.

To lower the pointer's priority: refs 4 → floor(log2 4)=2 → 2*4/live. With live 12 → 6666.
- If refs were 3: 1*3/12 = 2500 < 5000 ✓ (the value's priority). So reducing the pointer's refs to 3 would flip it!

How to reduce the pointer's refs from 4 to 3? The pointer is used 3 times (unk10 read, unk10 write, unk14 write) + 1 set = 4. Hmm.

Hmm! What if the pointer's set is merged with the address computation (no separate pseudo)? Hmm.

What if the pointer were used only 2 times? E.g., if the two stores were merged... they're at different offsets.

Hmm, what if the pointer's value were loaded directly into the address (no separate pointer pseudo)? I.e., the source never names p:
```c
v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;  /* wrong semantics */
```
✗.

Hmm. OK, alternative: raise the value's refs from 3 to 4:
The value's refs = set(1) + use(2) + use(3). The two uses are the two stores. Hmm, we need a 4th.

**IDEA**: What if the value is also used as the value of the FIRST store computed as `v0` and the second as `v0` — that's 2 uses. What if the source wrote:
```c
v0 = ((Unkstruct_80126948 *)p)->unk10;
v0 = v0 - 3;
((Unkstruct_80126948 *)p)->unk10 = v0;
((Unkstruct_80126948 *)p)->unk14 = v0;
```
Hmm. What if instead:
```c
v0 = ((Unkstruct_80126948 *)p)->unk10 - 3;
((Unkstruct_80126948 *)p)->unk10 = v0;
((Unkstruct_80126948 *)p)->unk14 = v0;
```
Then the value pseudo = the addiu result: refs = set(1) + 2 uses = 3, and the load pseudo = 2 refs. Hmm.

Hmm! What if the value's live is SHORTER? Live 6 → 4 would give 3/4*1e4 = 7500 > 6666 ✓. The value's live = from the def to the last use. Its def is the addiu (in the target: `addiu v0,v0,-3` at 5674) and the last use is `sw v0,20(v1)` at 5680 → 6 insns.

Hmm, if the two stores were ADJACENT (sw unk10, sw unk14 back to back), the live would be 2 → pri 15000 ✓✓. But the target has the jal between them! (`jal` at 567c, then `sw v0,20(v1)` in the delay slot). Hmm, the sw is in the delay slot, so it's 1 insn after the addiu... but the jal is in between (the delay slot instruction executes before the call).

So in the target, the value's live spans the jal (the value must live across the call? no — the store is in the delay slot, so the value is dead before the call).

Hmm, the live length counts insns: def at 5674, uses at 5678 and 5680 → live = 5680-5674+1 = 7? The table says 6.

If I moved the two stores adjacent in the source (before the call), the value's live would be shorter → higher priority → the value gets v0 ✓! But would the code still match? The target's layout:
```
5674: addiu v0,v0,-3
5678: sw v0,16(v1)
567c: jal func_8013D13C
5680: sw v0,20(v1)   (delay slot)
```
The source order is: store unk10, store unk14, then the call. The scheduler moved the second store into the delay slot. If I reorder the source to store unk14 FIRST then unk10, the target's order would change ✗.

Hmm, but the source order is already unk10 then unk14 (matching). So the source has them adjacent — and gcc's scheduler moved the second into the delay slot ✓ (that's what happened in mine too: mine[10]=`sw v1,20(v0)` before the jal? Let me check mine's layout).

From the c1 diff: mine[11]=`sw v1,20(v0)`, mine[12]=`bnez v0`. Hmm, and the jal? Let me look at mine's full asm.

OK, the source has them adjacent, so the value's live is already short. The table says live 6 for r77 and 12 for r73.

Hmm, so which is the pointer? r73 (live 12) = the pointer ✓ (loaded first, used last). r77 (live 6, refs 3, "2 bytes") = the value.

"2 bytes" — hmm, that's the local_size in bytes. A 32-bit value would be 4 bytes. Unless the value pseudo is 2 bytes...

OH WAIT!!! Maybe r77 is the value BEFORE the subtraction: the `lw v0,16(v1)` loads a 32-bit value... hmm.

Hmm, "2 bytes" — maybe the alloc_table tool prints the local_size for locals from the .lreg dump, and "2 bytes" refers to something else.

Let me stop analyzing and EXPERIMENT with the priority lever: I need the VALUE's priority > the POINTER's. The value: refs 3, live 6 → 5000. The pointer: refs 4, live 12 → 6666.

Options:
(a) value refs 4 → 2*4/6 = 13333 ✓
(b) value live ≤ 4 → 3/4*1e4 = 7500 ✓
(c) pointer refs 3 → 1*3/12 = 2500 ✓
(d) pointer live ≥ 18 → 2*4/18 = 4444 ✓

Option (d): the pointer's live ≥ 18! How? The pointer's live = from its def to its last use. If the pointer were loaded EARLIER (e.g., at the very top before the frame setup) — it is. Hmm, the live is measured in the RTL insn count. The pointer's def is at RTL insn ~2 and its last use at ~13 → live 12.

To make it 18, the pointer's def must be ~6 insns earlier relative to its use. Hmm, the frame setup (4 insns: addiu sp, sw s0, move s0,a0, sw ra) is between. Hmm.

Hmm! What if `a0` is NOT copied to s0 (so the frame is smaller)? Then the pointer's live would be shorter ✗ (we want longer).

Hmm, what if the pointer's load is BEFORE the frame setup AND the frame setup is longer? The frame setup includes `sw s0,16(sp); move s0,a0; sw ra,20(sp)` — the `move s0,a0` is the copy of a0 into s0. Hmm.

Hmm, the target's layout:
```
lui v1,0x0
lw v1,0(v1)
addiu sp,sp,-24
sw s0,16(sp)
move s0,a0
sw ra,20(sp)
lw v0,16(v1)
li a0,10
addiu v0,v0,-3
sw v0,16(v1)
jal func_8013D13C
sw v0,20(v1)   (delay slot)
bnez v0,...
```
So the pointer's live spans from insn 1 to insn 11 → 11-12 ✓ (matches live 12).

And the value's live: from insn 6 (lw v0) to insn 11 → 6 ✓.

So to make the value's live ≤ 4, the value's def must be at insn ≥ 8. But the def is the load which must come after the pointer's load... The distance between them is fixed by the frame setup (4 insns).

Hmm, unless the frame setup were LONGER (more insns between the pointer's load and the value's load) — that would make the value's live SHORTER (since the value's live is measured from its def, not to the end). Hmm no: the value's live = last_use - def. If the frame setup grows, the def moves later but the last use also moves later by the same amount → live unchanged. Hmm, no: live = (last use index) - (def index). If the frame setup (between them) grows, both shift equally → live unchanged. Hmm, but the live length counts only the value's own range.

Hmm, so the value's live = the number of insns from the load to the last store = 6 (lw, li, addiu, sw, jal, sw).

To reduce it: fewer insns between the load and the last store. The `li a0,10` and the `jal` are in between. Hmm, the `li a0,10` is the call argument (scheduled before the addiu) — it's the call's argument setup, which happens early.

Hmm, what if the call `func_8013D13C(10)` were spelled so that the `li a0,10` comes later? It's scheduled early by sched1.

Hmm. This is a rabbit hole.

Option (a): value refs 4. The value's refs = set + 2 uses. Hmm.

Hmm, what if the value is stored via a temp so that there are more refs?

Option (c): pointer refs 3. The pointer's refs = set(1) + 3 uses. If one use could be removed... The three uses: read unk10, write unk10, write unk14. Hmm.

WAIT!!! What if the pointer's SET is merged with one of its uses? E.g. if the pointer's value were used directly as the address (no separate pointer pseudo), then... hmm.

Hmm, what if the source loads the pointer TWICE (once for the read, once for the stores)? Then there would be 2 pointer pseudos:
```c
v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;   /* hmm, wrong semantics */
```
✗.

OK, option (d) revisited: the pointer's live ≥ 18. The pointer's live = from its def to its last use. What if the pointer were loaded MUCH earlier — e.g., the load is the FIRST thing and the last use is at the end. Currently: def at 1, last use at 11 → 11.

Hmm, in the target the pointer's last use is the delay-slot store (insn 11). To make the live longer, we'd need the last use later. But the stores are early in the function.

Hmm! What if the pointer is ALSO used later in the function? There's no later use.

OK... hmm.

Let me question the "order by priority" hypothesis. Maybe the order is by allocno, and the way to flip is to make the VALUE pseudo have a lower allocno — which requires the value's RTL to come first.

Hmm! **What if the value is loaded from a DIFFERENT but equivalent expression that doesn't involve the pointer pseudo?** The value is `*(p + 16)` where p = *(D_801151D4). As an expression: `*(*(s32*)&D_801151D4 + 16)`. The RTL: load p (pseudo A), then load the value (pseudo B). A is created first ✗.

Hmm, so the value's pseudo is always second.

⇒ Under the allocno hypothesis, this item is a WALL. Under the priority hypothesis, it's reachable but I haven't found the lever.

Let me test the priority hypothesis decisively with a quick experiment: change the pointer's refs (e.g., add a use of p that's free? no)...

Hmm, how about this: **make the pointer's live longer by moving the pointer's load before the `s0` copy** — no.

Hmm, let me try: what if `a0` is NOT copied to s0 but kept... no, the target has s0.

OK, alternative decisive test: make the VALUE's live shorter by using a different formulation. What if the value's last use comes right after its def? E.g. if the second store (`unk14 = v0`) were moved to just after the first store in the source... it already is.

Hmm, the value's live = 6 because of: lw v0 (def), li a0, addiu v0, sw v0, jal, sw v0. The jal is between the two stores in the SCHEDULED code, but in the SOURCE they're adjacent! So the live length (computed by gcc's flow analysis on the pre-scheduling RTL) would be: def (lw), addiu (v0 = v0-3), sw, sw → live ~4!

Hmm, but the table says 6. Hmm, the alloc_table's "live" is REG_LIVE_LENGTH from the .lreg dump (after scheduling?). Hmm.

OK. Let me try the EXPERIMENT: add a use of the value in the source that doesn't change the code but adds a ref. Hmm, what if the second store is written as:
```c
((Unkstruct_80126948 *)p)->unk14 = v0;
```
Hmm.

You know what? Let me try a completely different source formulation that might change everything: write the two stores as a STRUCT copy? Hmm.

Let me try: what if the value is stored via a `u32 *` cast:
```c
*(u32 *)((u8 *)p + 0x10) = v0;
*(u32 *)((u8 *)p + 0x14) = v0;
```
(f4 — tried, no change).

Hmm.

Let me try: what if the two stores use a pointer variable `q` derived from p:
```c
s32 p;
u32 *q;
p = D_801151D4;
v0 = ((Unkstruct_80126948 *)p)->unk10;
v0 = v0 - 3;
q = (u32 *)((u8 *)p + 0x10);
*q = v0;
*(q + 1) = v0;
```
Hmm, that creates an extra pointer pseudo (q) and changes the addressing (`sw v0,0(q); sw v0,4(q)`) ✗ (the target has `sw v0,16(v1)`).

OK. Let me now consider the possibility that the difference is in the ORDER of local-alloc being by "local_size" then "reg_last_freq" — hmm.

DECISION: Time to move on. Let me record func_80180480 as a WALL (best 19) with the tag "lreg-v0-local-first" (an existing wall tag!) — the mechanism: "local-alloc gives the pointer pseudo (created first) $v0; the target needs the value pseudo in $v0 and the pointer in $v1".

Hmm, but wait. Before giving up, let me try ONE more class of variants: what if the pointer pseudo is NOT created first because the pointer is loaded into a variable that is ALSO used as a call argument later? no.

Hmm, hold on! Let me reconsider the whole thing: what if the ORIGINAL source didn't have a pointer variable at all, but instead the code was:

```c
v0 = ((Unkstruct_80126948 *)(*(s32 *)&D_801151D4))->unk10;
```
Hmm, that's a nested deref — the RTL: load the pointer (pseudo A), then load the value (pseudo B). A first ✗.

Hmm, what if the ORIGINAL used `*(s32 *)&D_801151D4` directly in an expression that gcc evaluates as: `lui v1; lw v1,0(v1); lw v0,16(v1)` — the same.

OK. So the pointer pseudo is always first. ⇒ The target's allocation (pointer in v1) is NOT reachable in gcc 2.7.2 by reordering the source... UNLESS the priority changes.

Let me try the priority lever ONE more time with a targeted change: increase the value's refs by making the value's copy have 3 uses. Hmm.

WAIT!!! What about this: the value is stored to unk10 and unk14. What if the source stored the value to unk10 via an expression that reads v0 twice? no.

Hmm, what about the POINTER's refs: 4 (1 set + 3 uses). What if the pointer's SET could be merged with a use — e.g., if the source loaded the pointer and immediately used it:

```c
p = D_801151D4;
v0 = ((Unkstruct_80126948 *)p)->unk10;
```
The set of p is a separate insn. Hmm.

Hmm, unless: what if `p` is not a variable but the expression `*(s32 *)&D_801151D4` is used 3 times? Then gcc's CSE would create ONE pseudo for the load (shared) → same as p. The pseudo's refs: set(1) + 3 uses = 4. Same.

OK.

FINAL IDEA for this item: **what if the value's pseudo gets priority > the pointer's by making the value's live SHORTER via a different expression**:

```c
v0 = ((Unkstruct_80126948 *)p)->unk10;
v0 = v0 - 3;
```
The value's live: from the load to the last store. In the RTL (pre-schedule): lw v0; addiu v0; sw v0; sw v0 → live 4. Hmm! But the table says 6. Hmm, maybe the table's "live" for r77 is something else.

Hmm, honestly, maybe r77 (refs 3, live 6, 2 bytes) is NOT the value. Let me get the definitive mapping: let me dump the .lreg section and look for the pseudo numbers with their assigned regs.

The .lreg dump (local-alloc output) prints the RTL with the pseudos REPLACED by hard regs? Or still as pseudos? In gcc 2.7, the -dl dump prints the function's RTL after local allocation with the pseudos still as pseudos? The alloc_table tool says "the hard register it got" comes "from either dump or from the order line" — so the .lreg dump does show the hard reg for each pseudo.

Let me look at the .lreg section for func_80180480 and find the insns with pseudos 73 and 77.

Let me write a small script to print the lreg section lines that mention "reg:SI 73" / "reg:SI 77" etc. Actually simpler: print the whole lreg section for the function (it may be long, ~200 lines). Let me print it to a file and read it.

Hmm, time. Let me do it — it's one script call.

Actually, let me reconsider the time budget seriously. It's 2.5h+ in. Remaining: func_80181E64, func_800D2650, func_8003DF8C, func_801415C0 (4 items) + finalize 80180480, 800D0D7C, 8012944C (done) + write results.tsv, moves.md, and the log.

Let me allocate: ~1h for the remaining 4 items (quick attempts), then finalize.

Let me prioritize the ones most likely to crack:
- func_800D2650 (4 pins) — hard.
- func_80181E64, func_8003DF8C ($0 zr) — hard (opaque copy).
- func_801415C0 — hard (local/global allocation).

Hmm, all hard. Let me at least do quick attempts on each.

But first, let me finish func_80180480 with one more idea: since the target has the pointer in v1 and the value in v0, and mine has them swapped, maybe I can flip by making the POINTER a pseudo that is created first but has a LOWER priority...

AH WAIT!!! **IDEA**: What if the pointer is used 3 times but I can make the pointer's live LONGER by loading the pointer EARLIER — specifically, what if the pointer is loaded BEFORE the `a0` copy into s0? That's already the case in the layout (the load is at the top).

Hmm, the pointer's live = 12 in the table. Hmm, what if I make it 18+?

The pointer's live in the RTL: def at insn k, last use at insn k+11.

What if there were more insns between the pointer's def and its last use? The value's def+uses are in between (5 insns) plus the frame setup (4).

Hmm, what if the FRAME setup were longer? E.g. if the function saved more registers... The frame setup: `addiu sp,sp,-24; sw s0,16(sp); move s0,a0; sw ra,20(sp)` = 4 insns.

Hmm, if the frame setup were LONGER (say 8 insns), the pointer's live would grow by 4 → 16. Still < 18. Hmm, and the value's live would stay 6 (both def and use shift).

Hmm! But a longer frame setup would change the code ✗ (the target has 4 insns).

Hmm, hmm.

**IDEA**: what if the pointer's live is extended by making the pointer's LAST USE later — e.g., by using p in the LAST statement? The target's last statements are `func_8012BF4C((s32 *)a0, 0x1E); func_8012AD50((void *)a0);`. If p were used there, the code would change ✗.

OK. Let me accept: for func_80180480, try a couple of quick priority experiments, else WALL.

Quick experiments:
i1: `s32 p; u32 v0;` (u32 value) — hmm, e5 was u32/u32 → no change.
i2: Make the pointer `s32` but the accesses through `u32 *`:
i3: Swap which variable holds what: rename so the "value" is created first — impossible.

Hmm.

OK, let me try the LAST idea: the alloc_table showed the value pseudo r77 as "2 bytes". What if the value pseudo is actually the LOAD's result (a 32-bit value)... and "2 bytes" is a red herring.

Let me do the decisive dump reading. Let me print the lreg section for the function to a file and look at it. 5 minutes.

Actually, let me try something much more likely to be productive: let me check whether the ORDER of the two stores in the source changes things. What if the source stores unk14 first and unk10 second? The target's insns: `sw v0,16(v1)` (unk10) at 5678 and `sw v0,20(v1)` (unk14) at 5680. So unk10 first. If I swap them, the code order changes ✗ (score would go up).

Hmm.

Let me try the "value live shorter" idea concretely: what if the value's last use is EARLIER? I.e., store unk14 BEFORE unk10 — no (order).

Hmm, what if the value's DEF is later? The value's def is the load of unk10. Hmm, what if the source loaded unk10 later:
```c
p = D_801151D4;
v0 = ((Unkstruct_80126948 *)p)->unk10 - 3;
```
Then the def is the addiu (after the load) → live = from the addiu to the last store = 3-4! pri = 3/4*1e4 = 7500 > 6666 ✓✓✓

That's e2! e2 gave score 19 (no change). Hmm. But maybe e2's value pseudo has different refs.

Hmm, e2 = `v0 = ((Unkstruct_80126948 *)p)->unk10 - 3;`. The value pseudo: set(1) + 2 uses = 3 refs, live ~4 → pri = 1*3/4*1e4 = 7500 > 6666. It should have flipped! But the score was 19 (same). Hmm, so either the order isn't by priority, or my ref/live numbers are off.

Let me actually verify e2's generated asm to see if the regs flipped. Let me disassemble e2.

Hmm, e2 scored 19 = same as c1. If the regs had flipped, the score would be different (maybe lower or higher). So no flip.

⇒ The local-alloc order is NOT by priority. It's by pseudo number (allocno).

⇒ To flip, the value's pseudo number must be lower than the pointer's.

Hmm! Pseudo numbers are assigned at expand time. The pointer's pseudo is created first... BUT WAIT: is that true? Pseudo numbers in gcc are assigned in `expand_expr`/`assign_pseudo_numbers` — actually gcc assigns pseudo numbers lazily via `gen_reg_rtx` in the order they're created during expand.

The pointer's pseudo is created when `p = D_801151D4` is expanded (the load's destination).
The value's pseudo is created when `v0 = p->unk10` is expanded.

So the pointer's pseudo < the value's pseudo. Always.

⇒ The ONLY way to flip: make the value's pseudo created FIRST. Impossible with this source shape...

UNLESS the value's pseudo is created before the pointer's because the pointer's load result is not a pseudo but... hmm.

WAIT!!! What if the pointer is NOT stored in a variable at all, and the three uses each load it separately? Then the pointer's pseudo would be created 3 times — but CSE merges them into one (the first one) → still first.

Hmm, what if the pointer is used ONCE (for the load) and the stores use a different expression? Then the pointer pseudo would be created first anyway.

⇒ Hmm, so how did the TARGET get the pointer in v1?

OHHH!!! WAIT. What if in the target, the POINTER is not a pseudo at all but a HARD REG (v1)?! The original compiler might have kept the pointer in a caller-saved reg. But for gcc 2.7.2, the pointer is a pseudo → allocated first → v0.

Hmm, so what if we could make gcc put the pointer in a HARD REG? Hmm, that's a pin ✗.

Hmm, hmm.

OK, alternative: what if the VALUE's pseudo is created first because the VALUE is the one that's loaded from a global and the POINTER is derived from it?! I.e., swap the semantics: what if `D_801151D4` is not a pointer-to-pointer but...

Hold on, let me re-read the target:
```
lui v1,0x0
lw v1,0(v1)       <- v1 = *(D_801151D4)
lw v0,16(v1)      <- v0 = v1->unk10
```
Yes.

Hmm, so in the target the pointer is v1 (the second reg).

Hmm, what if in the ORIGINAL source, the pointer was a VARIABLE THAT IS USED LATER, making it a global? No — v1 is caller-saved.

Hmm, what if the original compiler (SCEI) just allocated differently? Yes, probably. The target is from the original compiler, and gcc 2.7.2 can't reproduce it without a pin. Hmm, but the project expects these to be crackable ("singleton crack shard").

Hmm, hold on. Let me reconsider: maybe local-alloc's order is NOT by pseudo number but by the order in `local_reg` array which is built by scanning... Let me actually TEST the hypothesis by a cheap experiment: create a variant with THREE locals where the third is created between p and v0, and see where each lands.

E.g.:
```c
s32 p;
s32 w;
s32 v0;
p = D_801151D4;
w = p;             /* hmm, extra move */
```
✗ extra insn.

Hmm, what about:
```c
p = D_801151D4;
v0 = ((Unkstruct_80126948 *)p)->unk10;
```
What if I write the load as `v0 = ((Unkstruct_80126948 *)p)->unk10;` vs `v0 = *(s32 *)&((Unkstruct_80126948 *)p)->unk10;` — same.

Hmm.

Let me try a DIFFERENT tactic: what if the pointer is accessed via a `short *`-style cast so that gcc creates an extra address pseudo BETWEEN the pointer and the value? E.g.:
```c
v0 = *(s32 *)(p + 4);    /* p is s32, so p+4 = byte offset 16 */
```
Hmm! `p + 4` (as s32*) = byte offset 16 ✓. The RTL: `lw v0, 16(p)` — gcc folds the offset into the mem. Probably no extra pseudo.

Hmm.

What if the offset is not a constant multiple? e.g. `*(s32 *)((u8 *)p + 0x10)` → `lw v0, 16(p)` — same.

Hmm.

OK: DIFFERENT IDEA — **what if the pointer pseudo is created first but gets a LOWER "priority" so that the VALUE (created second) gets the better reg?** The "better reg" for locals: gcc's local-alloc assigns from a list of local regs in preference order; the order of the locals processed determines who gets the first choice. If the order is by priority DESC, I showed e2 (which should have raised the value's priority) didn't flip. Hmm, unless e2 didn't actually change the priority.

Let me VERIFY by dumping e2's alloc table and comparing r73/r77's numbers with c1's. If the numbers changed as I predicted but the allocation didn't flip, then the order is by pseudo number (confirmed). If the numbers didn't change, my model is wrong.

Let me do that: dump e2's TU and get the alloc table. That's ~2 tool calls. Worth it? Hmm.

Hmm, time. Let me make a decision: I'll do ONE diagnostic (dump e2's alloc table) and if it doesn't immediately give a lever, I'll record a WALL for 80180480 and move on.

Actually, let me instead try a much more promising practical approach: **the "split the value" trick from moves.md**: "pin | func_8017F794 | MATCH — split reused v0 (call result, then unk1C cmp value) into own var t: shorter-lived pseudos, s0 ptr wins s0 in greg (G04)".

Hmm, that's about globals.

And: "pin | func_80185E38 | MATCH — $2 pin -> v temp + early return `if (v == 0) return 3; return 4;`".

Hmm.

Let me try the diagnostic dump. Actually no — let me try a couple more cheap variants FIRST (each is 1 tool call for gen+score, or I can use a single gen script with many variants).

Variants to try (all keep the code identical):
j1: value as `u32`, pointer as `s32` (e5 was both u32).
j2: pointer used via `u8 *`: `v0 = *(s32 *)((u8 *)p + 0x10);` (f4 ✗ tried).
j3: the value's subtraction written as `v0 = v0 + (-3);`.
j4: `v0 = ((Unkstruct_80126948 *)p)->unk10; v0 -= 3;`
j5: declare the value as `int` vs `s32` (same).
j6: the pointer as `void *`: `void *p; p = D_801151D4; v0 = ((Unkstruct_80126948 *)p)->unk10;` — hmm, the cast from void* is fine. The RTL: the same.
j7: the pointer as `char *`.

Hmm, j6/j7 change the pseudo's mode? No, all pointers are SI.

Hmm, none of these will change the pseudo order.

⇒ The pseudo order is fixed ⇒ the only lever is the priority (if the order is by priority) — which e2 suggests isn't it.

Hmm, hold on. Let me reconsider e2's result: e2 scored 19 — the same as c1. But maybe e2's diff is different in a way that coincidentally has the same score? Let me look at e2's diff quickly. If e2 flipped the regs but introduced another difference... hmm, unlikely (same score = same count of mismatches).

Let me just dump e2's alloc table — decisive. Two calls.

Hmm, actually, I realize there might be a MUCH simpler explanation I've been missing: maybe gcc's local-alloc assigns the FIRST local to the FIRST reg in the "local reg order", and for MIPS that order might be v0, v1, ... but the target's value got v0. What if in the TARGET's original source, the value pseudo WAS created first because the original source loaded the value BEFORE the pointer — impossible — OR because the original source used a DIFFERENT variable order...

Hmm, hold on!! What if the original source was:

```c
v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;
```
Hmm, that changes semantics... unless D_801151D4 is a pointer variable whose VALUE is the pointer. Hmm! What if the original source had `D_801151D4` declared as a POINTER (e.g. `extern Unkstruct_80126948 *D_801151D4;`)? Then `D_801151D4` IS the pointer and `D_801151D4->unk10` = `lw v0, 16(v1)` where v1 = D_801151D4 (the global's value, loaded into a reg).

But the target shows `lui v1; lw v1,0(v1)` — the pointer is LOADED from the global ✓ (so D_801151D4 is a global holding a pointer). And the source `p = D_801151D4` loads it ✓.

So if the source were `v0 = ((Unkstruct_80126948 *)D_801151D4)->unk10;` — that would be the ADDRESS of D_801151D4, not its value. The target loads the value. So the source must dereference the global's value.

OK. So the pointer pseudo is unavoidable and first.

⇒ Therefore, for gcc 2.7.2, the pointer gets v0 (first local) — UNLESS the local-alloc's order is by priority.

Let me do the decisive diagnostic (dump e2's alloc table). If e2's numbers show the value with a higher priority yet still allocated second, then the order is by pseudo number and this is a WALL (the target's allocation is unreachable).

Hmm, but hold on — even if the order is by pseudo number, there might be a trick: what if the pointer pseudo is created first but is NOT a local (e.g., it's a global)? Then the value (local) would get v0 and the pointer would get a callee-saved reg ✗ (target: v1).

Hmm, what if the pointer is a local but the VALUE is a global? Then the value gets a callee-saved reg ✗.

OK. So: the target has BOTH in caller-saved regs, with the value in v0 and the pointer in v1. For gcc 2.7.2's local-alloc, the first-created local gets v0. So the value must be created first. IMPOSSIBLE with this source shape...

...UNLESS the pointer's load result is not a pseudo but a hard reg! When does gcc put a loaded value directly in a hard reg? When the pseudo is a "local" and the load is the FIRST insn and the pseudo's live range is short... no, gcc always uses pseudos and allocates later.

Hmm, hold on, hold on. What if the pointer pseudo's live range is SO SHORT that gcc's local-alloc... no.

Hmm, what if the pointer is used only ONCE? Then... hmm! What if the source is written so the pointer is used ONCE and the stores use a DIFFERENT pointer expression that's ALSO a load? Then there'd be 2 pointer pseudos (the second created after the value) and the second one would get v1!!! Hmm!! But the extra load would add instructions ✗ (cse would merge them).

Hmm, unless the CSE merges them into the FIRST pseudo (the one created first) → back to square one.

OK, DECISION: let me do the e2 alloc-table diagnostic to confirm the mechanism, then record the wall. Actually, let me skip the diagnostic and instead try the ONE remaining plausible lever: **the value's priority via refs**, by checking whether the order is by priority using a cheap trick: make the pointer's live longer by loading the pointer BEFORE the function's prologue... it already is.

Ugh.

Hmm, hmm. Actually, WAIT. What about this: **the "li a0,10" (the call argument) is scheduled before the addiu. What if the call argument were set up differently so that the scheduler doesn't need to hoist `li a0,10`?** That affects the value's live (6 → 5) but not enough.

Hmm.

Hmm, let me reconsider the local-alloc order question with the data I have: for func_801415C0 (the earlier item), the locals were c (live 7) and d (live 10) and they got $16 and $17 respectively: c (shorter live) got the LOWER reg. If the order were by pseudo number, c (created first: c = a + 0x2F comes before d? no! d = b + 0x2F comes FIRST in the source). Hmm: in func_801415C0's source, d is assigned before c. So d's pseudo < c's pseudo. But c got $16 (the first reg) and d got $17. So the order was NOT by pseudo number — it was by priority (c: pri 4285 > d: pri 3000) ✓✓✓

So local-alloc DOES order by priority! Great — that means for func_80180480, the priority lever should work, and my ref/live model must be off.

Let me recompute for func_80180480: the locals are the pointer (r73: refs 4, live 12, pri 6666) and the value (r77: refs 3, live 6, pri 5000).

To flip: the value's priority must exceed 6666.
- With refs 3: need live ≤ 4 (3/4*1e4 = 7500).
- With refs 4: 2*4/6 = 13333 ✓.
- With refs 5: 2*5/live.

Hmm, e2 (`v0 = ...unk10 - 3`) should have made the value's live shorter (the def is the addiu). Let me check e2's alloc table! If e2's value pseudo has live 4 and pri 7500 > 6666, then the order should flip... but e2 scored the same 19. Hmm, maybe e2's value pseudo has refs 2 (set + 2 uses = 3) hmm.

Let me just dump e2's table. Let me do it.

Plan: create tu_e2.c (same as tu_c1.c but with e2's body), dump, alloc_table.

Let me write a script that generates the TU from a body file automatically. Actually, let me write a generic helper: "mkTU.py <itemdir> <body.c> <tu.c>" that extracts the function body from the body file and wraps it with the needed includes/externs. Hmm, the externs differ per item.

Simpler: for this item, write tu_e2.c manually (like tu_c1.c with the e2 change).

Let me do it.
