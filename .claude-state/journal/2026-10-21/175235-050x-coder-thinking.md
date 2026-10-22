---
ts: 2026-10-21T23:52:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_tCR0MBnec9UcdqisfK05
---
Variant F: mine[33] `lw v0,376(a1)` — a1 instead of a0! Because the final expression uses arg0 but with v0 reused... hmm, `lw v0,376(a1)`?! That's odd — oh, the args: in F the final expression is `v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;` → lw from arg0 = a0. But it shows a1. Hmm, maybe the compiler swapped the arguments? Whatever.

Key: F's structure still has the "j + li v0,1" block (mine[31:33]) and the const temp in $2.

I'm now fairly convinced this item needs the const temp to be in $3 — i.e. something must occupy $2 in the chain block.

IDEA: What if the "1"-value is a real pseudo because the four returns are NOT `return v0` but `return v0` where v0's set is in a *different* block than some uses...

Alternatively: what if we ADD a use of the "1"-pseudo in the chain block that produces NO extra instructions? For instance, using it in a comparison that gcc folds... no.

Hmm, here's a thought: what if the "1"-pseudo's set is `v0 = 1;` but v0 is ALSO the variable that holds the final result, i.e. variant F, AND the final expression is arranged so that gcc keeps v0 as a real variable with two sets? In F, gcc still folded.

Let me try the opposite: use a DIFFERENT variable for the final result and keep v0 = 1 with an extra use:
```c
v0 = 1;
v1 = 9;
if (arg2 == v1) return v0;
...
v2 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
return v2;
```
Then v0 (the "1") has 1 set + 4 uses, and the returns copy it to $2 (foldable). Same as before.

Hmm.

What if the returns are written as `return (s32)v0;`? same.

Let me try the "cc1 dump + alloc table" route to see what the actual priorities are. It's the tool the brief points to. But it may take a while (dumps for a big TU). Let me check the script.

Actually, hold on. Let me reconsider the problem: maybe the intended crack for this item is much simpler and I'm missing it. Let me look at the pin: `register s32 v0 __asm__("$2")`. The lever-free alternative that keeps $2 for v0: what if v0's value is not a constant but the FUNCTION'S RETURN VALUE is used differently...

Hmm, hmm. What about the observation that the ROM's `li v0,1` sits in a delay slot — that's a *sched1* artifact (delay slot filling). In the pinned version, the "1" set is a hard-reg set. What if we could get the same delay-slot placement with a pseudo by making the "1" set NOT foldable...

AH WAIT. What about making the value 1 come from a *variable read* that gcc can't fold — e.g. from a global that's declared `extern s32 D_8011D030;`? The ROM's `li v0,1` is a constant, so no.

Hmm, what about the possibility that the "1" is NOT a separate variable but the *return value of a comparison* like `arg2 == v1` where v1 is a constant... no, that returns 1 only if equal.

Let me reconsider: maybe the ROM's `li v0,1` corresponds to a source like:

```c
v0 = 1;
```
where v0 is declared as a *global-ish* variable? Hmm.

What if v0 is a `static` variable? Then it'd be in memory ✗.

OK, let me try the alloc table route quickly; if it doesn't reveal an easy lever, I'll record a WALL for item 3 (tag something like "lreg-const-fold" or "cse-const-fold") and move on to the other items (6 more). Time is precious: 6 items × 30 min = 3 hours.

Actually, WAIT. Let me reconsider one thing: the target's `li v0,1` in the delay slot of the FIRST branch (ins 22). In mine, the "1" is materialized in the return block. What if I restructure the C so that the "return v0" arms come BEFORE... no.

What if the four `if (arg2 == v1) return v0;` are replaced by a single test that gcc computes into a pseudo?

Hmm, what about this shape:
```c
v0 = 1;
v1 = 9;
if (arg2 == v1) goto ret;
v1 = 0x11;
if (arg2 == v1) goto ret;
v1 = 0x29;
if (arg2 == v1) goto ret;
v1 = 0xA;
if (arg2 == v1) goto ret;
return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
ret:
return v0;
```
This is the same as before (gcc merges).

What if instead:
```c
    v1 = 9;
    if (arg2 == v1) { v0 = 1; goto ret; }   /* v0 set in each arm */
```
→ 4 sets ✗.

Hmm what about the possibility that the ROM's source used a SWITCH with a jump table? The ROM's chain of beq suggests if-chains.

Let me try ONE more experiment batch for item 3 (cheap, parallel):
P1: v0 as the variable holding the final result AND the "1" (variant F) but with the final expression written as `*(s32 *)((u8 *)arg0 + 0x178) != arg1` assigned to v0 via a separate temp:
```c
v0 = 1;
...
v1 = *(s32 *)((u8 *)arg0 + 0x178);
return v1 != arg1;
```
P2: the "1" via a *parameter* comparison that gcc keeps: skip.
P3: put `v0 = 1;` AFTER the first compare (statement order):
```c
v1 = 9;
if (arg2 == v1) return v0;   /* v0 uninitialized! */
```
Not valid.

Hmm, P3': what if the first arm returns a literal 1 and the rest return v0?
```c
v1 = 9;
if (arg2 == v1) return 1;
v0 = 1;
v1 = 0x11;
if (arg2 == v1) return v0;
...
```
Then the first arm's `return 1` materializes `li v0,1` in that arm's block ✗ (the ROM has the li in the delay slot).

Hmm, but wait! What if gcc merges the first arm's `li v0,1` block with the others via cross-jump? Then all four arms have `li v0,1` → merged into one block → the shared block has `li v0,1; jr $ra`. The ROM's structure: the `li v0,1` is NOT in a shared block; it's in the chain block (delay slot). Hmm, but if the shared return block is placed right after the chain... the `li v0,1` would be at the start of that block, not in the chain.

I think the ROM's exact shape requires the hard reg.

DECISION: Let me spend 5 more minutes on item 3 with the cc1 alloc table (to see if there's an easy lever), then move on.

Hmm, actually — hold on. Let me reconsider the problem from the "what does the pin buy" angle once more, but for the *other* direction: what if we make the CONST temp the pinned-like one... no.

Alternatively: what if we could get gcc to allocate $2 to the const temp and $3 to the "1"? That's the opposite of the target ✗.

Alternatively: what if we get rid of the const temp entirely and let the comparisons use $3 naturally? For the const temp to get $3, $2 must be occupied by something else at that point. What occupies $2 in a normal compile? The return value. So the function's return value must be live across the chain — i.e. a pseudo holding the return value.

What if the function computes the result into a variable and returns it at the end?
```c
s32 func_8014C308(...) {
    s32 v0;
    ...
    if (mask == 0) {
        v1 = 9;
        if (arg2 == v1) { v0 = 1; goto out; }
        v1 = 0x11;
        if (arg2 == v1) { v0 = 1; goto out; }
        v1 = 0x29;
        if (arg2 == v1) { v0 = 1; goto out; }
        v1 = 0xA;
        if (arg2 == v1) { v0 = 1; goto out; }
        v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
    } else {
        v0 = 0;
    }
out:
    return v0;
}
```
Here v0 is a real variable (live across the chain) → allocated $2 (copy preference: it's the returned pseudo!) → and the const temp gets $3 ✓✓✓. But the "1" would be materialized in each arm (4 × `li v0,1`) ✗ — unless gcc's cross-jump merges the four arms into one block (they're identical: `v0 = 1; goto out`) → merged into one `li v0,1` block ✓!!

Then the structure: the chain block has the beq's; the merged arm block has `li v0,1; j out`?? Hmm, the target has the branches going DIRECTLY to the epilogue (jr $ra) — with a `goto out` structure, the branches would go to the "out" block which does `jr $ra` — and the merged arm block would be `li v0,1; j out` — an extra jump ✗.

Hmm, but if the "out" block IS the epilogue (`jr $ra`), and the arms are `v0 = 1; goto out` → each arm: `li v0,1; j out`. Cross-jump merges the 4 arms → `li v0,1; j out` (1 block) — that's 2 insns (li + j) vs the target's structure where the branches go straight to the epilogue and the li is in the delay slot.

The target: 4 branches → jr $ra directly, with the li in the delay slot of the first branch. So the "1" is set BEFORE the branches (in the chain block) — meaning the source sets the value before testing, not in the arms.

So: the value 1 must be set before the first compare, in the chain block, and the arms must branch to the epilogue. That's the pinned structure. And the reason the arms can branch directly to the epilogue is that the value is already in $2.

So we need: (i) the "1" set once in the chain block (before the compares), (ii) allocated to $2, (iii) the arms branch directly to the epilogue.

For (i) the source must be `v0 = 1;` before the compares (as now).
For (ii): the pseudo must survive to allocation → its uses must not be foldable copies.

Hmm, (ii) is the crux. The copies `set $2, v0` are foldable because v0's value is the constant 1.

BUT: what if the arms don't return v0 but return the pseudo directly... same.

Hmm, what if the pseudo v0's uses are `return v0;` in FOUR DIFFERENT blocks, and gcc's cross-jump does NOT merge them (because they're not identical — e.g. if each arm has a different extra code)? Then each arm has `li $2,1` ✗ (4 li's).

Hmm, what if the value returned is not constant but the same *variable* whose value is set once... circular.

OK: what if the "1" is not 1 but the value of a comparison that's provably 1 in that path? E.g. the mask test: `(x & y) == 0` is true → the boolean is 1 → gcc propagates the constant 1 → folded ✗.

What if the value is the result of a comparison gcc CAN'T fold, e.g. `(arg2 == 9)` — no, that's 0/1 depending.

Hmm, the ROM's value is exactly 1 in those arms. If the source were `return (arg2 == arg2);` gcc folds to 1.

What if the source were `return (s32)(u8)(arg3 & 1) | 1;`? Not 1.

I think the ROM's "1" is a literal.

So the crack requires gcc to keep a constant-1 pseudo in $2. gcc's copy-folding kills it... UNLESS the pseudo is used in a context that isn't a copy — like a STORE to memory? no.

Hmm, hold on! What about this: the four arms return v0, and there's ONE more use of v0 somewhere that forces it to be a real variable: e.g., the final expression `return *(s32 *)((u8 *)arg0 + 0x178) != arg1;` — what if we write it as:

```c
v0 = 1;
v1 = 9;
if (arg2 == v1) return v0;
v1 = 0x11;
if (arg2 == v1) return v0;
v1 = 0x29;
if (arg2 == v1) return v0;
v1 = 0xA;
if (arg2 == v1) return v0;
return v0 & (*(s32 *)((u8 *)arg0 + 0x178) != arg1);
```
Hmm, that adds an `and` ✗.

What about `return (*(s32 *)((u8 *)arg0 + 0x178) != arg1) ? v0 : 0;`? adds a branch ✗.

Hmm.

What about making the "1"-pseudo's set be the value of a comparison whose result is 1 but in a way gcc keeps as a pseudo: e.g. `v0 = (arg2 == v1) | 1;`? = 1 always, folded to 1 ✗.

Honestly: gcc will always fold a constant.

=> The ONLY way: the value must be a non-constant that happens to be 1. Not possible.

=> Therefore the ROM's `li v0,1` came from a hard-reg pseudo (a pin) in the ORIGINAL ROM build too! I.e., the ROM's original source (before decomp) used a variable that the compiler kept in $2 — maybe because the ORIGINAL source had a `register` declaration or because the ROM's compiler was different (the ROM is compiled with a different toolchain than gcc 2.7.2!).

Hmm, the ROM is the original game code (PsyQ SDK). The decomp uses gcc 2.7.2 (mips-linux). The ROM's code was compiled by the PsyQ compiler (also gcc-based, from the SNES-era toolchain? No — this is a PSX game). PSX games use the Sony/Nintendo compilers (based on gcc 2.x for the MIPS R3000? The PSX SDK's compiler is a modified gcc 2.7.2 for MIPS little-endian? Actually the PSX toolchain (ccpsx) is based on gcc 2.7.2 with an lcc-based frontend? No, ccpsx is based on GCC 2.7.2 with the MIPS assembler).

So the ROM's compiler ≈ gcc 2.7.2 → similar behavior. So the ROM's `li v0,1` in the delay slot with the value in $2 came from the ROM's source having a variable in $2 that gcc kept. How? If the ROM's source had the "1" as a variable that was ALSO used in a non-copy way...

OR: the ROM's source had the return value computed like:
```c
return 1;
```
in each arm, and the ROM's compiler merged the four arms' `li v0,1` into ONE via cross-jump, and then sched1 moved that `li v0,1` into the delay slot of a branch in the chain block?! Cross-jump merging creates a shared block; sched1 (per-block scheduling) can't move an insn across blocks. But "reorg" or "jump threading" might have restructured so that the shared block's `li v0,1` ended up in the chain block...

Hmm! Actually, here's a cleaner idea: what if the ROM's source had the four arms each `return 1;` and the compiler merged the four `li v0,1` into one, placing that block right after the chain? Then the branches would be `beq a2,v1,SHARED` and the shared block = `li v0,1; jr $ra`. But the ROM's branches go to +0x94 = the `jr $ra` alone, and the `li v0,1` is at ins 23 (before the 2nd/3rd/4th compares) — so the shared "li v0,1" block is NOT after the chain; it's in the middle.

Unless the ROM's chain is: [li v1,9][beq → RET][li v0,1][li v1,17][beq → RET]... — the `li v0,1` is a delay slot. If the source were:
```c
v1 = 9;
if (arg2 == v1) return 1;
v1 = 0x11;
if (arg2 == v1) return 1;
```
with `return 1` (constant), then each arm has `li v0,1; jr $ra` → merged into one shared block → 4 branches to it → the shared block = `li v0,1; jr $ra` (2 insns) placed after the chain. The ROM's branches go directly to `jr $ra` at +0x94 with the `li v0,1` in the middle of the chain — so the "li v0,1" is NOT in a shared return block. => The value 1 was set ONCE before the arms (in the chain block) and the arms branch directly to the epilogue.

So the ROM's source: a variable holding 1, set once in the chain block, and the arms return it. And the compiler kept it in $2 (the return reg) as a REAL pseudo (not folded).

For the ROM's compiler to keep it as a real pseudo, the value must not be foldable into the copies... Hmm, in the ROM's compiler, the copies `set $2, v0` where v0 is a pseudo with value 1 — the same folding would apply. So the ROM's compiler would also fold it!

=> Therefore, in the ROM's source, the "1" was NOT a variable holding the constant 1 — it was something else that yields 1.

What yields exactly 1 in all four arms and is materialized once? A comparison! E.g.:

```c
if (arg2 == 9 || arg2 == 0x11 || arg2 == 0x29 || arg2 == 0xA) return 1;
```
Hmm, that computes a boolean → but the ROM has no boolean computation; the ROM branches directly to the epilogue with v0=1 set before the branches.

Hmm, what if the ROM's source is:

```c
    v0 = 1;
    v1 = 9;
    if (arg2 == v1) return v0;
```
and the ROM's compiler (gcc 2.7.2 for PSX) did NOT fold the copy because... the copy `set $2, v0` is folded by "combine" into `set $2, 1` and the pseudo's set removed. Then the four arms each have `li $2,1` → merged by cross-jump into one shared block `li $2,1; jr $ra` → the branches go there. But the ROM's branches go to +0x94 = jr $ra and the li is in the chain block...

UNLESS the shared block IS at +0x94 and the "li v0,1" I see at ins 23 is a *different* thing! Let me re-examine: what if ins 23 `li v0,1` is the delay slot of the beq at ins 22, and the shared return block at +0x94 is `jr $ra` only — meaning the four arms branch to a block with just `jr $ra`, so v0 must ALREADY be 1 → the value was set before the branches ✓ (as I concluded).

OK so both compilers would need a real pseudo in $2.

Hmm, unless the ROM's compiler's "combine" didn't fold because the pseudo was assigned in a way that...

WAIT!!! What if the pseudo's value is NOT a constant in the ROM's source, because the source is:

```c
v0 = 1;
```
where "1" is a *macro* or a variable?? E.g. `v0 = g_someFlag;` — no, the ROM has `li v0,1`.

Hmm, what if the source is `v0 = (s32)sizeof(x) - 3;`? folded to 1.

What if the source is `v0 = 1;` and the compiler kept it because the pseudo was declared `register`?! The ROM's original source might have had `register int v0 asm("$2")` — no, PSX games don't use asm registers.

Hmm, hold on: maybe the ROM's source had the "1" assigned to a variable that is ALSO used as a *loop counter* or something...

Let me try yet another interpretation: maybe the "1" pseudo in the ROM is not `v0 = 1` but the result of the comparison `arg2 == v1`!? Look: the branches `beq a2,v1,RET` — if the source were:

```c
v1 = 9;
if (arg2 == v1) return 1;
```
the compiler needs v0=1 on that path. Alternatively:
```c
if (arg2 == v1) { v0 = 1; return v0; }
```
same.

What if the source is:
```c
switch (arg2) {
case 9: case 0x11: case 0x29: case 0xA: return 1;
}
```
→ gcc 2.7 would generate a comparison chain (not a jump table for 4 sparse cases) — and each case would have `li v0,1` → merged by cross-jump into one block → the branches would go to that block (which contains `li v0,1; jr $ra`) — but the ROM's `li v0,1` is in the chain block, not a separate block.

Hmm, unless the merge placed the shared block's `li v0,1` in the delay slot of the last branch...

Honestly: the ROM's structure with `li v0,1` in the delay slot of the FIRST branch is exactly what a scheduler does when the set is in the chain block and the branches follow. So the set IS in the chain block in the ROM's source. And the source sets a variable to 1 there. And the compiler kept it as a real pseudo.

Could the ROM's compiler have kept it because the variable's address was taken? no (memory).

Could it be that the ROM's variable was `char`/`short`? A HImode copy: `set $2, v0` where v0 is HImode → the copy is `move`/`sext` — gcc 2.7 might not fold a HImode pseudo's const set into the copy! That's the moves.md trick ("s16 flag = 1 test not folded by cse" / "HImode copy escapes cse")!

So: declaring the "1"-variable as s16 or u16 might make the copy non-foldable → the pseudo survives → allocated $2 → the set `li v?,1`... but then the return needs a sign/zero extension → an extra insn ✗. Hmm, but maybe the extension is free: `li $2, 1` + no extension needed since the value is 1 and the extension of 1 is 1 — gcc's "combine" would fold the extension of a constant ✓ → folded again.

Hmm, but variant B (s16 v0) gave exactly the same 17/41. So no.

OK, I've spent a lot on item 3. Let me make a decision: record item 3 as a WALL with a tag, and move on to the other 6 items, then come back if time permits.

Hmm, but wait. Before that, let me try the alloc table — it's the tool the brief points to for exactly this, and it might reveal that the const temp's pseudo is a "global" (cross-block) pseudo whose allocation is decided by global-alloc, where the priority (floor(log2 refs)*refs/live*1e4) decides. If the const temp is global (live across blocks) and the "1"-pseudo is local, then global-alloc takes $2 for the const temp (global pseudos get preference) — and the "1" (local) gets $3.

In the ROM, the "1" IS in $2 → so the "1" pseudo was global too (or hard-reg).

If the "1"-pseudo were global (live across a block boundary), global-alloc would compete with the const temp on priority (refs/live). The "1"-pseudo: refs 5 (1 set + 4 uses), live range = the whole chain; the const temp: refs 8, live = the whole chain. Priority = floor(log2(refs)) * refs / live * 1e4:
- "1": floor(log2(5))=2 → 2*5/live
- const: floor(log2(8))=3 → 3*8/live
So const wins ✓ (consistent with mine).

To flip: increase the "1"-pseudo's refs (need floor(log2(refs))*refs to exceed 3*8=24 → refs=9 gives 3*9=27 > 24 ✓, or refs=5..7 give 2*refs=10..14 ✗).

So if the "1"-pseudo had 9 refs, it would win! Can I get 9 refs? The "1"-pseudo: 1 set + N uses. Uses = the 4 returns (4) = 5 refs. To get 9 refs, I'd need 8 uses. Hmm: what if each return uses it twice? `return v0 + v0;`? That changes semantics (2) and adds an add ✗.

What if the value is used in a comparison in each arm? e.g. `if (arg2 == v1) return v0;` → 4 uses. Hmm.

Alternatively reduce the const temp's priority: floor(log2(refs))*refs/live — reduce the const temp's refs (8 → 4: floor(log2(4))=2 → 2*4=8 < 2*5=10 ✓ then the "1" wins!). The const temp with 4 refs = 2 sets + 2 uses. Hmm, we need the const temp to be set only twice and used twice. But there are 4 different constants!

Unless... two of the four compares use the SAME constant variable but the constant is set twice? Like:
```c
v1 = 9;
if (arg2 == v1) return v0;
v1 = 0x11;
if (arg2 == v1) return v0;
v1 = 0x29;
if (arg2 == v1) return v0;
v1 = 0xA;
if (arg2 == v1) return v0;
```
= 4 sets + 4 uses = 8 refs.

What if the constants were compared in a different way, e.g. using a *range* check? `if ((u32)(arg2 - 9) < 2)`? Different bytes.

Hmm, what if two of the compares used a constant directly (no temp) — variant A — but gcc merged them into one pseudo. Hmm, but if gcc's combine merged them, then the pseudo's refs would be 4 sets + 4 uses = 8 anyway.

Hmm, what if the const temp is used only twice because two compares are folded into one? E.g. `if (arg2 == 9 || arg2 == 0x11)` → gcc computes two compares (needs 2 temps).

OK, so the priority arithmetic suggests: the "1"-pseudo needs ~9 refs, or the const temp ~4.

Hmm, how about this: make the "1"-pseudo's live range SHORTER than the const temp's? The priority formula divides by "live". If the "1"-pseudo is live only in the later part (e.g. set after the first compare) while the const temp is live across the whole chain, then the "1"'s priority = 2*refs/live_1 could exceed the const's 3*8/live_c. E.g. if live_1 = 4 and live_c = 40: "1" = 2*5/4 = 2.5; const = 3*8/40 = 0.6 → "1" wins ✓.

But the ROM's structure has the "1" set at ins 23 (after the first compare) — i.e., the "1"-pseudo's live range starts late! ✓ That's consistent with the ROM: v0's live range = from ins 23 to the end (short-ish) while the const temp's live range = the whole chain.

So the ROM's source might have had the "1" set AFTER the first compare! I.e.:
```c
v1 = 9;
if (arg2 == v1) return 1;    /* hmm, the first arm needs the value */
v0 = 1;
```
No: the first arm (arg2==9) returns the value → the value must be set before it.

Hmm, but in the ROM the `li v0,1` is in the delay slot of the first branch → it executes BEFORE the branch takes effect ✓ so it's set before the first arm's return ✓. So the set is before the first branch in the block, but the scheduler placed it after the branch instruction (in the delay slot). The pseudo's live range starts at the set (ins 23) — but the branch at ins 22 is BEFORE the set. Hmm, so the live range starts at ins 23.

But the ARM at ins 22 (arg2 == 9) returns v0 — which is set at ins 23 (after) ✗ semantically!? Ugh, the delay-slot semantics: the branch at ins 22 is evaluated, then the delay slot (ins 23) executes, then the transfer happens. So on the taken path, v0 = 1 is set ✓ (the delay slot executes before the jump). So it's semantically fine ✓.

OK so in the ROM, the "1" is set in the chain block and its live range covers the arms.

Alright. Let me now try the alloc table to see the actual numbers, then decide. Actually, the alloc table needs cc1 dumps (gcc -fdump-rtl-...). The brief says: "tools/cc1_dumps_tu.sh + tools/alloc_table.py (TU dumps)". Let me check cc1_dumps_tu.sh usage — it might take a while (dumping a big TU). And the disk cap.

Time check: I've spent ~30 min. Let me be decisive: I'll try 2 quick variants (increasing the "1"-pseudo's refs via a legit route) and if they fail, record a WALL for item 3 and move on.

Quick variants to try:
Q1: Make the const temp's live range longer/shorter? Hmm.
Q2: Use a *separate* variable for the "1" and let the final expression use another variable:
```c
    s32 v0;   /* the 1 */
    s32 v1;   /* const temp */
    s32 v2;   /* final */
    ...
            v0 = 1;
            v1 = 9;
            if (arg2 == v1) return v0;
            v1 = 0x11;
            if (arg2 == v1) return v0;
            v1 = 0x29;
            if (arg2 == v1) return v0;
            v1 = 0xA;
            if (arg2 == v1) return v0;
            v2 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
            return v2;
```
That's basically the original + a temp for the final result. The "1" pseudo: 5 refs; the const temp: 8. Probably no change.

Q3: Increase the "1"-pseudo's refs by making the mask test use it? e.g.
```c
    if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
```
Hmm.

Q4: What if we swap the roles: make the const temp the "returned" value? no.

Let me try Q2 and one more:
Q5: `v0` declared `s32` but assigned in a way that keeps it a pseudo: `v0 = 1;` → try `v0 = (s32)(u32)1;`? folded.

I think Q2 is the most promising (a separate final-result temp changes the const temp's qty? no...).

Hmm, actually, let me reconsider: maybe I should try making the const temp have FEWER refs by using a *constant* for two of the compares in a way gcc keeps separate. Variant A did that and gcc merged them. Hmm, but did it? The result was identical to nopin. Let me look at variant A's diff to see if the const temp is one pseudo or four. If four pseudos and yet the allocation is the same, then the criterion isn't qty.

Let me check variant A's diff quickly (it's cheapand informative).
