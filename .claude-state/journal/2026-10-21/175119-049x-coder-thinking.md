---
ts: 2026-10-21T23:51:19Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_7JIBvuBgfvb0ukDDcHzJ
---
All stuck at 17/41 ins with the same mapping. The const temp still lands in $2.

Hmm. Let me reconsider: maybe the priority isn't qty but something else, e.g. the pseudo's "reg" preference (from global-alloc) or the order in the block.

Alternative hypothesis: local-alloc allocates $2 to the pseudo that is live at the block's start / has the longest life, and the const temp (live across the whole chain) wins. The "1"-pseudo in mine is set inside the chain.

Hmm, in the target, the "1"-pseudo is ALSO set inside the chain (ins 23) but it got $2 because of the pin.

So maybe with the pin removed, we need the "1"-pseudo to be live at the block start too — i.e., set BEFORE the const temp's first use. But the target has the "1" set at ins 23 (after the first compare)! Because the set was sunk into the delay slot.

Hmm, so in the target the "1"-pseudo's set is inside the chain but the pseudo is allocated $2 by force (pin).

Without the pin, we need gcc to allocate $2 to a pseudo whose set is in the middle of the block. Since local-alloc works per block and the block is the whole innermost if-block, all pseudos in it compete.

What determined the const temp winning $2 in my compiles? Perhaps the "birth order" (the order in which pseudos are born / their pseudo numbers). The const temp v1 is declared AFTER v0 in the source (v0 first, then v1) — hmm, and v0 is the one that should win $2. But v1 won. So it's not decl order (or it's reversed).

Wait, maybe the relevant thing: local-alloc's `find_reg` tries the pseudo's "reg" preference, which for a pseudo used in a compare might be... Hmm.

Another thought: maybe the issue is that the "1"-pseudo is a *constant* (1) — gcc's RTL has `(set (reg v0) (const_int 1))` → in local-alloc, a pseudo whose value is a constant might be "ignored" for allocation and later materialized into $2? Hmm.

Let me look at this from a completely different angle: what did the *other* shards do for similar "pin $2 on a constant-return" cases? moves.md line 43: "pin | func_80157BC8 | MATCH — both $2 result pins -> call-site return-type casts ((s32 (*)(s32))f)(a0)". Line 91: "pin | func_80185E38 | MATCH: $2 pin -> v temp + early return `if (v == 0) return 3; return 4;`". Line 122: "pin | func_801890C4 | MATCH — v0 reuse for rand() dropped: (s16)(rand() % 5 + 4) inline arg (or own r temp)".

Line 91 is instructive: the $2 pin was a *result* pin; the crack was to restructure returns so the value ends up in $2 naturally.

For our case, the "1" is a result value returned in 4 arms.

Hmm, here's an idea: what if the "1"-pseudo is used in a way that requires a *copy* to $2 (i.e., it's returned in a context where the value must be in $2)? gcc knows the return value must be in $2 — but only at the return points. If the pseudo is returned directly (`return v0`), gcc emits a copy to $2 unless the pseudo IS $2. So gcc has a preference: when a pseudo is returned, the copy-preference makes global-alloc give it $2! But that's a *copy preference*, handled by global-alloc for globals; for locals, local-alloc's `find_reg` may honor copy preferences (the "reg" field / preferences).

In mine, the pseudo returned is in $3 → gcc inserted the copy (the "j RET; li v0,1" pattern shows the value was materialized in $2 at the return). Hmm, actually in mine the "1" pseudo is in $3 and the return copies it to $2 → but the diff showed mine[31] `j 6ac4` + mine[32] `li v0,1` — a constant set, not a copy. So gcc constant-folded: the pseudo holds the constant 1 → the return becomes `li v0,1` — so the "1"-pseudo was NOT kept at all (folded into the return).

So the "1"-pseudo in my compile is a constant → gcc materializes it directly in $2 at the return. So there's no pseudo competing for $2 at all! The $2 register is then free for the const temp.

That's the key insight: in the pinned version, `v0` is a HARD REG pseudo ($2), so `v0 = 1` is a real set of $2 → the scheduler places `li v0,1` in a delay slot, and the returns are just `jr $ra` (no copy). Without the pin, the pseudo is a regular pseudo holding the constant 1, and gcc's RTL expansion puts `li v0,1` at the return points (folding).

So how do we get a *pseudo* (not constant-folded) whose set is materialized once and whose uses are direct returns?

Trick: make the value non-constant, so the pseudo survives! E.g.:
```c
v0 = 1;
```
→ constant. What if we make it `v0 = (s32)(u16)arg3 & 0;`? Silly.

Better: make the "1" come from a computation that gcc keeps as a pseudo, e.g. `v0 = arg2 & 0`? Hmm, but then the value is 0 not 1.

Hmm, what about: the value 1 as the result of a comparison: e.g. `v0 = (arg2 == arg2);`? gcc folds.

What if we use a value that gcc can't fold but is still 1 at runtime? E.g. `v0 = 1 & (s32)(u8)arg3;`? Not 1.

Hmm. Alternatively, keep the pseudo alive by using it in a non-foldable way: e.g.
```c
v0 = 1;
if (arg2 == v1) return v0;
```
gcc's RTL: v0 = 1 (const), then uses → the copy to $2 at each return. But gcc folded the copy into `li v0,1` at the return → the "1" pseudo never gets a register. To prevent the folding, the pseudo must be live across the block (used in multiple places) — it is (4 returns) but gcc's "jump threading"/"combine" merged them.

Hmm, but the target has ONE `li v0,1` shared by 4 returns, in the delay slot of the first branch. In the pinned version, since v0 is a hard reg, the set is a real RTL insn and the scheduler sank it into a delay slot.

To get the same without a hard reg: we need a pseudo whose set is a single RTL insn and whose 4 uses are direct returns of that pseudo (so gcc doesn't need a copy). If the pseudo were in $2, the returns would be direct. But if gcc folds the constant...

Idea: make the value 1 NOT a compile-time constant, e.g. `v0 = (arg3 & 0) + 1`? gcc folds `arg3 & 0` → 0 → 1. Hmm.

What about making the value come from a volatile load? That's a barrier lever — not allowed.

What about `v0 = 1;` where v0 is declared `volatile`? barrier. No.

Alternative: make the "1" a value that's provably 1 but not constant-foldable at RTL level: e.g. `v0 = (s32)(u8)(*(volatile u8 *)&D_8011D030)`? no, volatile = barrier.

Hmm, what about using a *global* variable's value? Not constant.

OK here's another thought: the return value 1 could be produced by an expression that gcc keeps as a pseudo: e.g. `v0 = (arg2 == 9) | 1`? = 1 always, folded.

Hmm, what if the returns are `return v0;` where v0 = 1 but v0 is ALSO used in a way that isn't a return? E.g. the final expression `v0 = *(s32 *)(arg0+0x178) != arg1;` (variant F) — then v0 has two values → the pseudo is a real variable, and gcc must keep it in a register. In variant F the score was 18 (worse) — hmm, because the final expression's structure changed.

Wait, variant F changed the final return into `v0 = ...; return v0;` — and the target's final expression is `lw v0,376(a0); xor v0,v0,a1; sltu v0,zero,v0` — the sltu result is in $2. In variant F, the pseudo for the final value would be in some register and copied to $2. Score 18 (one worse than 17).

Hmm. Let me look at variant F's diff to see what changed. Actually, let me think about the deeper structure.

In the TARGET: the "1" is materialized ONCE (ins 23) in $2 and the 4 returns are direct `jr $ra` (via branches to RET). For gcc to do that, the pseudo holding 1 must be allocated $2 (the return reg) and NOT folded.

In the target (pinned), v0 = hard reg $2 → set is `li $2,1` (a real insn, no pseudo) → placed once, and the returns are just branches to the epilogue. The scheduler sank it to a delay slot.

Without the pin: to have a single `li v2,1` shared by the returns, we need a pseudo allocated to $2 whose value is 1. But gcc folds constant pseudos...

UNLESS the pseudo is not constant-foldable. What if the "1" is produced by an operation that gcc keeps? e.g. `v0 = 1;` where the assignment is inside a condition? Hmm.

What about: `v0 = (s32)(u16)1;`? Still constant.

What about making the pseudo's value come from a *parameter* in a way that's provably 1? e.g. `v0 = (arg2 == arg2) ? 1 : 1;` folded.

Hmm, what about: `v0 = 1; v0 += 0;`? gcc folds.

Alternatively: accept that the "1" is folded into each return (4 × `li v0,1`) — no, the target has one.

Hmm, wait. Maybe there's a different C shape that yields one `li $2,1` naturally: what if the function's return value is computed once and returned via a single exit? Like:

```c
s32 func_8014C308(...) {
    ...
    if (...) {
        ...
        if (arg2 == 9 || arg2 == 0x11 || arg2 == 0x29 || arg2 == 0xA) {
            return 1;
        }
        return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
    }
    return 0;
}
```
Then gcc would compute a boolean: `sltiu`/`sltu` etc. → different bytes (the target compares with beq against 4 constants).

Hmm.

Let me step back and consider: is the target's `li v0,1` really the "1" value? What if the `li v0,1` in the target is a *different* value — e.g. part of the ROM's own code where the "1" comes from elsewhere? The ROM's 4 returns of "1" share it. Yes it's the "1".

OK so the question is how to get gcc to emit ONE `li $2,1` in a delay slot, lever-free.

Idea: use a *pointer dereference* of a constant? no.

Idea: the value 1 could come from a variable that gcc can't fold but is 1 at runtime: e.g. `v0 = (s32)(u8)arg1[0x5E] ...` no.

Hmm, what about this: the ROM's `li v0,1` in the delay slot of the branch — a delay-slot fill by sched1 of the SET of a pseudo. For gcc to have a pseudo set to schedule, the pseudo must exist (not folded). gcc folds `v0 = 1` only when the pseudo's value is a constant AND the pseudo is only used in "copy to return reg" contexts? Hmm, actually gcc's RTL for `v0 = 1; return v0;` is: `(set (pseudo v0) (const_int 1))` then `(set (reg 2) (pseudo v0))`. Then combine/jump-threading: the copy `(set (reg 2) (pseudo v0))` can be forwarded → `(set (reg 2) (const_int 1))` and the pseudo's set becomes dead → removed. That's exactly what happened in my compile (4 × li v0,1? no — mine had ONE `li v0,1`!).

Wait, mine had ONE `li v0,1` (mine[32]) — so gcc did NOT fold into 4 separate returns; it created a single set in the return-1 block. Interesting. So mine: the "1" pseudo's set was materialized once (as `li v0,1` in the delay slot of the `j`) — that's the copy-to-$2 of the pseudo, i.e. gcc kept the pseudo's set and the copy merged into one insn.

So in mine, the pseudo IS materialized once but in the return-1 block (a separate block), whereas the target materializes it once in the delay slot of the first compare's branch (so all 4 returns share it and no separate block is needed).

The difference: in the target, the pseudo is allocated $2 (so the "copy" is a no-op: the pseudo IS $2 — because it's pinned!). So the set `li $2,1` is the pseudo's own set, placed wherever sched1 wants (the delay slot), and the returns need no copy.

In mine, the pseudo is in $3, so the return needs a copy to $2; gcc placed the copy (materialized as `li $2,1`) in the return-1 block, which is why the block structure differs (an extra block, 41 ins).

So the crux remains: get the pseudo into $2.

Now: local-alloc must give $2 to that pseudo. The competing pseudo is the const temp. But maybe the const temp is NOT a pseudo in my compile — hmm, it is (it's in $2!).

Wait a moment! In mine, the const temp is in $2 (v0) and the "1"-pseudo is in $3 (v1). But the "1"-pseudo's *copy* to $2 (the return) is materialized as `li v0,1`. Fine.

So the question stands: why did the const temp get $2? Because of qty (8 refs vs 5) or life length.

How to make the "1"-pseudo win? Boost its qty: it has 4 uses (returns) + 1 set = 5. If the pseudo were used more times, qty grows. Hmm, what if we make the returns use it more, e.g. `return v0 + 0;`? That adds a copy per return.

Alternative: reduce the const temp's qty below 5: the const temp has 4 sets + 4 uses = 8. If we could make it 2 sets + 2 uses = 4 < 5 → the "1" wins. E.g. use TWO temps alternating? No, that increases total but each temp's qty is what matters:
```c
v1 = 9; if (arg2 == v1) return v0;
v2 = 0x11; if (arg2 == v2) return v0;
v3 = 0x29; if (arg2 == v3) return v0;
v1 = 0xA; if (arg2 == v1) return v0;
```
→ v1: 2 sets + 2 uses = 4; v2: 2; v3: 2. Each < 5 ✓. But gcc may coalesce them into one pseudo anyway (they're all "arg2 == const" comparisons — the temps are equivalent-ish? no, different constants; but gcc's "combine" might reuse a pseudo for a dead one).

Variant E (4 temps) gave the same 17 → gcc coalesced them or the allocation still prefers the const temp.

Hmm, in variant E, was the const temp coalesced into one pseudo? The score was identical to nopin (17, 41 ins, same pairs) → yes, same code.

gcc 2.7.2's "combine" merges pseudos that are equivalent (same value) — different constants aren't equivalent. But "cse" might reuse the register... The allocation result was identical, suggesting one pseudo again.

Hmm, actually maybe gcc's local-alloc gives $2 to whichever pseudo is live at the block start. In variant E, at the block start, v0 ("1"), v1 (9) are live. The const temp v1 is live from its set to its use; the other temps are born later. So at the block start only v1 and v0 are live; local-alloc allocates registers to all live pseudos in the block, ordered by qty... 

If ordered by qty: v1 (in E: qty 2) vs v0 (qty 5) → v0 should win $2! But the result was unchanged. So the order is NOT by qty, or v0's qty isn't 5, or the const pseudo isn't what I think.

Alternative hypothesis: local-alloc allocates the hard reg to the pseudo that is live at the block start AND has the earliest "birth" (the first set in the block). Hmm, in the source, `v0 = 1` comes before `v1 = 9`, so v0 is born first → v0 should get $2. But it didn't!

Unless gcc's RTL order differs: gcc's "expand" may reorder the sets? Hmm.

Hmm, what if the const temp is NOT a pseudo but is directly a hard reg because of the comparison pattern: `if (arg2 == v1)` where v1 = 9 → gcc creates a compare pseudo `cmp` and the `li` for the constant... The `li v0,9` in mine is a set of the pseudo v1 → allocated $2.

Hmm, let me get the alloc table for this function to see the pseudo priorities! tools/alloc_table.py <tag> [fn] [dump_root] — needs cc1 dumps. The brief mentions tools/cc1_dumps_tu.sh for TU dumps. That's the principled way (R32: "the table settles arguments the residual cannot"). Let me try it: cc1_dumps_tu.sh with the TU and output under my item dir, then alloc_table.py.

Cost: the dump may be large (cc1 dumps for a big TU). Disk is capped but I can delete after reading. Time: a few minutes maybe.

Let me check cc1_dumps_tu.sh usage.

Actually, let me reconsider the whole approach: maybe I'm overcomplicating. Let me look at how the "1"-pseudo could get $2 by a *different* C structure: what if the function returns the value 1 through the *return register* directly because the comparison result is used?

Alternative idea: what if the "1" isn't a variable but the return value comes from `(s32)(arg2 == arg2)`? no.

Another thought: what if we write the four returns as `return 1;` and the target's single `li v0,1` comes from gcc's "jump threading" merging the four arms into one block? Hmm! Let's think: with `return 1;` in each arm, gcc creates 4 blocks each with `li v0,1; jr $ra`. Then "cross-jump"/"jump threading" might merge them into one shared block → one `li v0,1` + `jr $ra`, with 4 branches to it. That would give: `beq a2,v1,RET1` ×4 where RET1 = `li v0,1; jr $ra`... but the target has the `li v0,1` in the DELAY SLOT of the first branch (ins 23) and the branches go directly to `jr $ra` (ins 37). So the shared return block in the target = just `jr $ra` (the epilogue), and the `li v0,1` is elsewhere (delay slot of the first beq).

With `return 1;` ×4: gcc would create the `li v0,1` in each arm (4 of them) — unless it merges.

Hmm, but here's the thing: the target's `li v0,1` in the delay slot of the FIRST branch means it's executed on BOTH paths (delay slot semantics) — so the value is set once for all subsequent uses. That's a scheduler artifact of a single set dominating.

So the C must have ONE set of the value. So the value must be a variable set once. Which means the pseudo must be a real variable (not folded). And it must be allocated $2.

Hmm, so how do we prevent gcc from folding `v0 = 1` into the returns? In mine it did fold (the set was materialized at the return). But that's fine — the problem is only the register.

Let me try yet another angle: make the const temp NOT a pseudo but a hard-reg-friendly form... 

What if the comparison is done with a *different* pseudo type? E.g. compare as `if (arg2 == 9)` (const) → gcc creates a constant comparison: `li v?,9; beq` — the constant needs a register (the target uses $3 for it). In variant A (inline constants) the result was identical to nopin → gcc's "combine" turned the 4 constants into one pseudo? Hmm, or the allocation just gave $2 to one of them.

Hmm, let me test a variant where the comparisons use *different* constants that can't be shared, e.g. `arg2 == 9`, `arg2 == 0x11`, ... — that IS variant A. Same result.

OK, let me try the alloc table approach to understand the allocation. Actually, a cheaper diagnostic: the "register pairs (mine -> target, count): v0->v1 x3" tells me mine's $2 == target's $3 in 3 places.

Let me try a few "boost the 1-pseudo" experiments:

X1: give the "1"-pseudo more refs by returning it in more places:
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
if (v0) return v0;     /* extra use */
return ...;
```
Hmm, that changes the code (extra branch).

X2: use `v0` in the comparison chain: e.g. `if (arg2 == v1) return v0;` → what if the comparison is `if (arg2 == v1 + v0 - 1)`? Hacky, changes bytes.

X3: Change the ORDER: put the const temp's first use before v0's set? e.g.
```c
v1 = 9;
if (arg2 == v1) return 0;   /* hmm, changes the returned value (ROM returns 1 here) */
```
No: the ROM returns 1 for arg2==9.

X4: What about declaring the const temp as a *parameter-like* variable... 

X5: What about making the "1"-pseudo the one that's used in the FINAL expression too (variant F, score 18) — the extra ref (qty 7) still lost.

Hmm, so qty isn't the criterion (else F's 7 would still lose to 8, consistent, and E's split would have won).

So what IS the criterion? In variant E, v0 (qty 5) vs v1..v4 (qty 2 each) → the const temp still won $2. So it's NOT qty-based. It must be life-length / block-start liveness.

At the start of the innermost block, the live pseudos are: v0 (the "1", set first in the source) and v1 (the const temp 9, set second). Hmm, but if the criterion were "born first", v0 would win.

Unless gcc's RTL for the block starts with the const temp's set! Why? Because gcc's "expand" may sink the `v0 = 1` set? Or because the "v0 = 1" set, being a constant, was folded into the uses (the returns) and thus NOT a set at all at the block start. In mine, the "1"-pseudo's set exists only at the return (folded). So at the block start, the only pseudo is the const temp → it gets $2 ✓✓.

That's consistent with everything: in mine the "1" is folded into the returns (no pseudo set at the block start), so the const temp wins $2. In the target, the pin forces $2 for the "1", so the const temp gets $3.

So to crack it, I need the "1" to be a REAL pseudo set at the block start (not folded), so that it competes for $2 and (being born first / having priority) wins.

How to prevent gcc from folding `v0 = 1` into the returns? If the pseudo's value can't be forwarded... The forwarding happens because the uses are "copy to return reg" and the value is a constant.

Trick: make the value 1 come from a non-constant expression that gcc keeps: e.g. `v0 = (s32)(u16)(u8)1;`? folded.

What if the value is 1 but produced by a runtime op: e.g. `v0 = (arg2 == 9) ? 1 : 0;` — folded? gcc's fold would simplify `arg2 == 9 ? 1 : 0` to `arg2 == 9` (a comparison) — that changes the code entirely.

What about `v0 = 1;` where v0 is a *global* variable? Not allowed (no signature/decl changes? a static local?).

What about: `v0 = 1;` and then use v0 in a context that isn't a return — e.g. in the final expression:
```c
v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
```
(that's variant F: v0 has two sets → the pseudo is real). But F scored 18.

Hmm, but maybe F's problem is elsewhere (the final expression's codegen). Let me look at F's diff to see.

Actually, maybe a cleaner approach for F: keep the final return as `return *(s32 *)((u8 *)arg0 + 0x178) != arg1;` but make the "1"-pseudo real by another means: e.g. use v0 in the mask test:

```c
if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
    v0 = 1;
    v1 = 9;
    if (arg2 == v1) return v0;
    ...
```
Hmm.

Alternative: make the "1"-pseudo's set non-constant by using a *volatile-free* trick: `v0 = 1 + (arg2 - arg2);`? gcc folds (arg2-arg2)=0.

`v0 = 1 + (arg2 & 0);`? folded.

What about `v0 = (s32)(u8)0x01;` folded.

Hmm, what about using the parameter arg3 (which is used in the mask): `v0 = (arg3 & 0) | 1;`? gcc folds arg3&0 → 0 → 1.

The only way to keep a non-constant pseudo is to have a real runtime dependency. But the ROM's value is literally 1.

Hmm, so maybe the trick is different: maybe the "1" doesn't need to be a pseudo at all! What if the C returns the constant 1 directly in each arm, and gcc's jump-threading merges the four `li v0,1` into one? Let me test:

```c
if (arg2 == v1) return 1;
```
×4 → 4 blocks with `li v0,1; jr $ra`. Jump threading might merge them into a common block. The target has one `li v0,1` in a delay slot — a merged block would have `li v0,1` INSIDE the block (not a delay slot).

Hmm, but the delay slot placement: if the shared block is "li v0,1; jr $ra", the branches to it would be `beq a2,v1,BLOCK`. The target's branches go to +0x94 = the `jr $ra` only (ins 37) — and the `li v0,1` is at ins 23 (delay slot of the first beq). So in the target, the "li v0,1" is NOT in a shared block; it's a sunk set.

Since the ROM's PsyQ compiler produced this, the original source probably had the assignment in a place where the set could be sunk into the delay slot.

Hmm, so which C source gives gcc 2.7.2 a "set of a pseudo" to sink into a delay slot? A pseudo whose value is 1 but which is used later... The key: gcc's scheduler can sink a SET into a delay slot if the set is not needed before. If the set is folded into the uses (as a constant copy), there's no set to sink.

For a pseudo to have a real set, the source must assign a non-constant OR the pseudo must be used in a way that prevents folding.

AH WAIT. What about the `s16`/`u16` trick from moves.md! "s16 flag = 1 test not folded by cse" (line 48: "pin | func_80180C04 | MATCH — $0 zr pin dropped, flag declared s16: HImode flag=1 test not folded by cse"). So declaring the variable as s16 makes the copy a HImode copy (a real insn `move`/`sext`) which escapes folding!

So: declare the "1"-variable as `s16` or `u16`! Then `v0 = 1` is a HImode set (a real pseudo set, e.g. `li v?,1` in HImode) and the return needs a sign/zero extension to $2 — hmm, that would add an extension insn (`sext`/`zext` → `sll`/`sra` or `move`), which the target doesn't have.

Hmm. Variant B (s16 v0) gave 17 (same as nopin) — so it didn't change anything?! If v0 were s16, the return `return v0` would sign-extend → extra insn. But the score stayed 17 with 41 ins. So gcc folded it back (s16 1 → s32 1). Hmm, so gcc 2.7.2 folded the HImode copy.

OK. Let me try the alloc table approach — it's the principled route and the brief points to it (tools/cc1_dumps_tu.sh + tools/alloc_table.py). Let me check the scripts' usage.

Actually hold on. Let me reconsider the problem completely.

What if the pin can be replaced by a *different* but equivalent lever-free construct that still forces $2? No — any hard-reg assignment is a pin.

Alternatively: maybe the crack is to restructure so that the value 1 is NOT needed as a variable at all: e.g. the ROM's `li v0,1` might correspond to something else in a different C formulation... e.g. the ROM's `li v0,1` could be the set of a pseudo that holds the *comparison result* of something.

Hmm! What if the C is:
```c
if (arg2 == v1) return v0;
```
where v0 = 1 — and gcc's version without the pin would set $2 = 1 in each arm... 

Let me look at the ROM's structure once more: the 4 comparisons branch to the epilogue (jr $ra) directly, and the "1" is set once in the delay slot of the first branch. For gcc to branch directly to the epilogue, the return value must already be in $2 at the branch. So the pseudo holding 1 was in $2 ✓ (the pin).

Without the pin, gcc has to decide the pseudo's register. For the returns to be direct branches (no copy), the pseudo must be $2.

So: the pseudo must be allocated $2, and it must exist (not folded). 

To make it exist as a real pseudo: its value must not be a compile-time constant. But the ROM's value is 1...

UNLESS the value is computed at runtime but is 1: e.g. `v0 = (arg2 == arg2)` → folded to 1 by gcc? gcc would fold `x == x` to 1 (it's a valid fold). 

What about `v0 = (s32)(u8)(s32)arg2 == (s32)(u8)arg2`? folded.

Hmm, what about a value that depends on a *volatile* read? Not allowed (barrier).

What about `v0 = 1;` but with the variable declared `volatile`? = barrier lever. Not allowed.

Hmm hmm. What about: the pseudo is real because it's used in TWO different blocks (live across a branch)? E.g. the "1"-pseudo is set before a branch and used after it — then it can't be folded into each use. But the target's set is at ins 23 and used in arms after it — all in the same block chain.

Actually! Think about it: in mine, gcc created the "return-1 block" and materialized `li v0,1` there. The pseudo was folded at the copy sites. But if the pseudo were live across a branch (used on both sides), the set couldn't be folded into the uses → it'd be a real pseudo → allocated a register → and gcc would prefer $2 because the copy preference (pseudo returned → $2) is honored by global-alloc/local-alloc!

So: can I restructure so the "1"-pseudo is live across a branch? E.g.:

```c
v0 = 1;
v1 = 9;
if (arg2 == v1) { ... return v0; }
```
The uses are in the "then" arms — all dominated by the set.

What if the set is BEFORE the first branch and there's a use after the branch? Like:

```c
v0 = 1;
if (arg2 == 9) return v0;     /* use in the then-arm */
...
```
Hmm, the use is in the then-arm of the branch → the pseudo is live across the branch (the set dominates the branch, the use is on one side) → gcc can still fold the copy into the use (the copy is on the path).

Hmm, gcc folds `set $2, const` — the question is whether gcc's RTL keeps a pseudo set at all. With `v0 = 1; ... return v0;`, gcc's RTL: pseudo v0 = 1; then in the return block: set $2 = v0. GCC's "combine" replaces the pseudo's set with the constant in the copy → the pseudo dies → the set is removed. Then the copy becomes `set $2, 1` in the return block (each return block separately). But mine had only ONE `li v0,1` — because the four returns were merged into one block by cross-jump (they all branch to the same block) → the copy was in the shared block → one `li v0,1` ✓.

So in mine, the value 1 is materialized in the shared return-1 block. In the target, it's materialized in the delay slot of the first branch, and the returns go directly to the epilogue.

The difference: in the target, the pseudo was $2 so the copy was a no-op and the set was the pseudo's own set (schedulable into a delay slot). In mine, the copy is materialized in the return block.

So again: I need a REAL pseudo holding 1 in $2.

How about making the pseudo's value come from a *parameter* in a way that's 1 but opaque to gcc? Hmm, e.g. `v0 = (s32)(arg3 == arg3);` — gcc folds.

What if the value is 1 at runtime but not provably so? Then the ROM's bytes wouldn't be `li v0,1`. So the ROM's value IS the constant 1 → the ROM's compiler also had a constant → it materialized `li v0,1` once.

So in the ROM (PsyQ gcc), the same folding happened, and the set was placed in a delay slot. The PsyQ compiler is gcc 2.x too — so the difference between mine and the ROM is the PIN (hard reg) → the pseudo is $2 → the "copy" is eliminated → the set is the pseudo's set → schedulable → delay slot.

CONCLUSION: without a hard-reg pin, gcc will materialize the constant 1 in the return block (like mine) — UNLESS the pseudo survives as a real variable.

Hmm, but wait: moves.md has plenty of MATCHes for "pin" items where the pin was a $2 pin on a *variable* (not a constant). E.g. line 43: "$2 result pins -> call-site return-type casts" (the pin was on a call result). Line 91: "$2 pin -> v temp + early return".

So the pins in this project are often on variables that hold runtime values. Here the pin is on a variable holding the constant 1 — that's a "constant pin", unusual. Let me check: is the pinned v0 really holding 1 only? Yes: `v0 = 1; ... return v0;`.

Hmm, so what makes the ROM use $2 for the "1"? Because the returns need the value in $2 and there's only one materialization.

Idea: what if we make the "1"-value a variable that gcc keeps in a register because it's ALSO used to compute something else? For example, the ROM's final expression `lw v0,376(a0); xor v0,v0,a1; sltu v0,zero,v0` — the final value is ALSO in $2! So in the ROM, TWO different values live in $2 (the "1" and the final comparison result) — they're not live simultaneously.

So in the ROM, the "1"-pseudo is $2 and the final-result pseudo is also $2 (sequentially). Since the final result is a comparison result (a pseudo), it's real.

What if I write the C so that the "1" is a real pseudo by making the FINAL expression reuse the same variable? Like variant F (v0 reused) — but F scored 18.

Let me look at F's diff to understand what went wrong. Actually, let me think: in F, the final expression `v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1; return v0;` → v0 is a real pseudo (2 sets). The "1" set and the final set are both of v0. gcc: v0 = 1 (const), v0 = (load != arg1). The "1" is still folded into the return copies. Hmm, so the "1" is still not a real pseudo.

OK OK. Let me try the alloc table / cc1 dumps to understand exactly what gcc does, and see if there's a lever. But honestly, maybe a better approach: think about what OTHER C shapes could produce the ROM bytes.

Alternative shape: what if the "1" is not a variable but the function's return value comes from a *comparison* that's always true? E.g.:

```c
if (arg2 == 9) return 1;
```
→ each arm materializes `li v0,1`. The ROM has one.

What if the arms are joined: e.g.
```c
if (arg2 == 9 || arg2 == 0x11 || arg2 == 0x29 || arg2 == 0xA) return 1;
```
→ gcc would compute a chain of compares: `beq a2,v1,B1; ...` with a common "return 1" block → the common block has `li v0,1; jr $ra`. The ROM's `li v0,1` is in a delay slot, not in a block. Hmm, but if the common block is reached only via the last branch... hmm.

Hmm! What about this shape:
```c
v1 = 9;
if (arg2 == v1) goto ret1;
v1 = 0x11;
if (arg2 == v1) goto ret1;
...
ret1: return 1;
```
That gives a shared block with `li v0,1`.

The ROM: the `li v0,1` is in the delay slot of the FIRST branch. That's the scheduler placing a set into a delay slot. For gcc to have a set to place, the value must be in a pseudo (not folded). 

Hmm, so the ROM's source likely had the "1" in a variable that gcc kept. E.g. the PsyQ source might have been:

```c
int v0 = 1;   /* a variable */
```
and gcc 2.x (the old MIPS one) did NOT fold the constant copy into the uses when the variable is a *global* or has a "reg" preference...

Hmm! What if the variable is declared such that gcc keeps it in memory or as a pseudo? E.g. if the variable is NOT optimized away (address taken?) — address-taken would force memory (bad).

What if the variable is declared `volatile`? → memory ops (bad).

Hmm, what if the variable's uses are in different blocks such that the set must dominate? It does.

OK — radical idea: maybe the "li v0,1" is NOT the value 1 at all, but the ROM's `v0` is used for something else and the "return 1" comes from... no, the returns are `jr $ra` with v0 = 1.

Let me look at the problem from the "what did the C look like" angle: the current src (pinned) compiles byte-exactly, and the pin is what makes the difference. The task is to find a lever-free body. If none exists, the answer is a WALL with a tag. Given 7 items and time, maybe item 3 is a WALL. But let me spend a bit more effort: the moves.md has a tag "expand-void-return" and "cse-copy-merge" etc.

Before giving up on item 3, let me try a couple of quick things:
1. `s16`/`u16` for the const temp (v1) → the compare in HImode; maybe the const temp becomes a different pseudo class (not competing for $2).
   Actually: `if (arg2 == v1)` with v1 as s16 → the comparison `arg2 == (s16)v1` → HImode compare → `sltu`/`beq` with a sign-extended value → different bytes (the target has `beq a2,v1`).
2. Make the const temp's *value* not a pseudo: e.g. compare with a constant expression that gcc materializes directly into the compare: `if (arg2 == 9)` → gcc creates `li v?,9; beq` — the `li` needs a register; gcc might use a "compare with constant" optimization: `beq` requires a register operand, so a temp reg is needed. The temp could be allocated to $3 if the "1" takes $2.

Variant A was exactly this and gave the same result. Hmm, but maybe in variant A gcc used ONE pseudo for all four constants (via combine) → same as before.

Let me test variant A more aggressively: use four DIFFERENT constant values in a way that gcc can't merge... they're already different (9, 0x11, 0x29, 0xA).

Hmm, so in variant A, gcc created 4 separate pseudos (one per constant) — and yet the allocation was the same ($2 for the first?). The "pairs v0->v1 x3" means 3 mismatched pairs — the compare registers.

Wait, maybe in variant A, gcc DID create 4 pseudos but local-alloc gave them all $2 (the first one) because they're short-lived and the allocator reuses $2. Then the "1"-pseudo (folded, no register) → nothing else. So the result: 4 × `li v0,X; beq a2,v0` with v0 = $2. The target has `li v1,X` with $3.

So the allocation question is: which register does the *constant temp* get? In the target it's $3 (v1). In mine it's $2 (v0).

Since the "1"-pseudo is folded away in mine, $2 is free for the const temp. In the target, $2 is taken by the "1"-pseudo (hard reg) → the const temp gets $3.

So to crack: I need SOMETHING to occupy $2. What occupies $2 in a normal compile? The return value register! gcc's convention: the return value goes in $2 (v0). If the function's return value is a *pseudo* that lives across the block, gcc's copy-preference would give it $2.

So: make the "1"-value a real pseudo (not folded). How? 

IDEA: Make the "1"-pseudo's value be the result of an operation that gcc keeps: e.g., compute the "1" as `1` but from a variable that's used elsewhere... 

IDEA 2: What if the function returns a value computed from a variable in a way that the "1" is a copy of it? E.g. the source could be:
```c
v0 = 1;
```
where v0 is assigned from a *parameter*: e.g. `v0 = (arg2 == 9) | 1;`? folded.

IDEA 3: What if the return value isn't 1 but the comparison result, and the ROM's `li v0,1` comes from a different formulation? E.g. what if the source is:
```c
if (arg2 == v1) return 1;
```
and gcc's *cross-jump* merged the four return blocks into one (giving one `li v0,1` in the shared block) — and then the scheduler moved that `li v0,1`... no, the scheduler can't move a set out of a block into a delay slot of a branch in a DIFFERENT block. Actually it CAN: sched1 moves instructions within a block; the delay slot of the beq at ins 22 belongs to the block containing that beq. If the `li v0,1` were in the shared return block, it couldn't move to ins 23.

So the `li v0,1` at ins 23 is in the SAME block as the beq at ins 22. So in the ROM's source, the "1" is set in the block that contains the first comparison — i.e., the innermost if-block ✓ (as in the current src: `v0 = 1; v1 = 9; if (arg2 == v1) return v0;`).

So in the ROM, the value 1 is a real set in that block. With the pin it's $2. Without the pin, gcc folded it.

To keep it as a real set, the pseudo must not be foldable into the uses. When gcc folds `set ret_reg, const` — that's the COPY folding (the pseudo's set was already removed, leaving copies). The pseudo's set removal happens in "combine"/"jump" — the pseudo dies.

To keep the pseudo alive, the pseudo must have a USE that isn't a copy-to-return. So the "1"-pseudo must be used somewhere else, e.g. in the final expression:

```c
v0 = 1;
...
return *(s32 *)((u8 *)arg0 + 0x178) != arg1;
```
→ if the final expression were `v0 = ...; return v0;` then v0 has 2 sets → the "1" set is still foldable (it's dead after). Hmm, the "1" set dies (its only use was the returns). But gcc's constant propagation would replace the "1"-pseudo's uses with the constant 1 → the set dies → same folding.

So the ONLY way to keep the "1" as a real pseudo is to have a use that can't take the constant... which is impossible if the value is 1 and the uses are returns.

WAIT. Unless the uses are not copies! What if the return is `return v0;` where v0 is $2 (the return reg) — the copy is a no-op. Circular.

Hmm, what if the function's return type were different, e.g. the function returned a struct? No.

Hmm, what if the value 1 is stored into a variable that is ALSO used to compute the final result? E.g.:

```c
v0 = 1;
...
v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
return v0;
```
gcc: v0 = 1 (const) → the first use (returns) → constant-propagated → v0's first set dies; v0's second set remains. Same as before.

OK so a pure-C "1" can't stay a pseudo. 

Therefore: the ROM's `li v0,1` in the delay slot implies the ROM's compiler had a pseudo in $2 — i.e., the ROM's source had a variable holding 1 that stayed a pseudo. How? If the variable's set is NOT constant-foldable because... it's assigned from a *function call*? No.

OR: if the variable was declared with a specific type/register hint? That's a pin.

OR: if the "1" was the result of a comparison that gcc kept as a pseudo! E.g. the source might be:

```c
if (arg2 == v1) return 1;
```
where the `1` is the *comparison result* of something like `(arg2 == v1)`. Hmm.

Hmm, what if the source is:
```c
v0 = (arg2 == v1);   /* no */
```

Let me look at the ROM's value semantics again: the returns return 1 in 4 cases. What if the original source was:

```c
if (arg2 == 9 || arg2 == 0x11 || arg2 == 0x29 || arg2 == 0xA) return 1;
```
Hmm, the ROM's structure: `li v1,9; beq a2,v1,RET; li v0,1; li v1,17; beq...`. If the source were the ||-chain, gcc would compute a boolean: `sltiu $2, $a2, 10` etc. — no.

OK, radical alternative: maybe the "1" in the ROM is the value of a variable that is set from a *comparison* of the mask test:
```c
v0 = ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0);   /* v0 = 1 */
```
That's a comparison result → a real pseudo! And its value is 1 on this path ✓. And it's in the block... but it's in the OUTER block (before the if). Hmm, the mask test is the if condition: `if ((... & ...) == 0) { ... }` → the comparison result is used by the branch. gcc computes it into a register ($2 in the ROM: ins 19 `and v0,v0,v1` then ins 20 `bnez v0` — so the comparison result is in $2 as the AND result!). Hmm interesting: ins 17-19: `lh v0,174(a1); andi v1,a3,0xffff; and v0,v0,v1` → the AND result in $2 ($v0), and ins 20 `bnez v0` tests it. So the "comparison result" is the AND itself (not a separate seteq).

So in the ROM, $2 at that point holds the AND result, and the mask test's "== 0" is a branch on it. And later `li v0,1` reuses $2 ✓ (the same register, sequentially).

So what if the "1" came from the mask test being 0 — i.e., the source is:
```c
v0 = (*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0;   /* = 1 */
```
Then v0's set would be in the OUTER block (before the branch), not inside. The ROM has `li v0,1` inside (after the first compare). Hmm, but gcc could sink it into the inner block (since it's only used there) — actually gcc would place the set in the block where it's used (the inner block) — YES! RTL expansion places the set at the start of the block where the pseudo is defined... hmm, if v0 is defined in the outer block (before the branch) and used in the inner block, gcc keeps the set in the outer block (dominance) — unless it "sinks" it into the inner block (gcc does sink stores into the block where they're used when the value isn't needed elsewhere — "store motion"/RTL sink). Hmm, in the ROM the `li v0,1` is at ins 23 — inside the inner block ✓ but AFTER the first compare (ins 21-22) — so it was sunk even further, into the delay slot.

Hmm, this is very speculative.

Let me take the empirical route: try a set of variants around this hypothesis:
W1: `v0 = ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0);` then use v0 as the return value, with the inner block's compares. i.e.:

```c
if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
    v0 = 1;   /* hmm */
```
Let me write it as:
```c
    s32 v0;
    ...
    v0 = (*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0;
    if (v0) {
        v1 = 9;
        if (arg2 == v1) return v0;
        ...
```
Hmm! But then v0 is 1 on the taken path ✓ and 0 on the other path. The returns return v0 = 1 ✓. And v0's set is a real pseudo (a comparison result) ✓ → allocated $2 (the copy preference!) ✓.

But the ROM's `li v0,1` vs a comparison result: the comparison `x & y == 0` would be materialized as... the ROM has `and v0,v0,v1` (the AND result) then `bnez v0` — so the "== 0" was folded into the branch. If v0 = (and == 0) were a real variable, gcc would compute `sltu`/`seq`... e.g. `sltiu v0,v0,1` → extra instruction ✗ (the ROM has no such insn).

Hmm. Unless gcc keeps it as `and` + branch... no, if v0 is used as a value, gcc must materialize the boolean.

Hmm. Unless the "1" is materialized as `li v0,1` — i.e. the boolean was folded to the constant 1 in the taken path (because the branch already established it's 0 → the boolean is 1 → gcc propagates the constant 1 into the block!) — that's "jump threading"/"condition propagation": inside the `if (x == 0)` block, gcc knows the condition is true → if v0 = (x==0), gcc replaces v0 with 1 → the set folds to the constant 1 → back to square one.

Ugh! Unless gcc doesn't propagate because v0's set is in the outer block... The value 1 would be known → the pseudo's set becomes `li v0,1` — a REAL insn (not folded away!) because the pseudo has uses in the inner block. Hmm! Maybe. The folding I feared (copy-to-return folding) happens only when the pseudo's set is dead. Here the pseudo v0 = 1 is used in 4 returns; if gcc keeps the set (as `li v0,1`) and the uses are copies to $2... circular again: the copy `set $2, v0` where v0 = 1 → combine → `set $2, 1` → v0's set dies.

ARGH. Unless v0 is allocated $2 (the copy preference) — which is what we want, but the allocation decision happens AFTER combine. In gcc's flow: RTL optimization (combine) runs BEFORE register allocation. So the copies are folded first, then the allocation. So the "1"-pseudo always dies. Hence the "1" is always materialized at the return site.

CONCLUSION: For the ROM's bytes (one `li v0,1` in a delay slot, returns directly to the epilogue), the "1" must be in $2 — which requires either a hard-reg pin or... the returns being structured so that the value is set once.

Hmm, wait! What if the returns are structured as a single return at the end with a flag? Like:

```c
if (arg2 == 9 || arg2 == 0x11 || ...) { v0 = 1; }
return v0;
```
Hmm, but the ROM's structure branches to the epilogue directly.

Hmm, what about this: the ROM's four branches all go to the SAME epilogue block (jr $ra). In mine, the four branches go to a shared "return-1" block (j RET; li v0,1). The difference is that in mine there's an extra `j` + the li.

What if the C were shaped so that the value is set BEFORE the branches and the branches go directly to the epilogue? I.e. the "1" is set once before the first compare, in the same block:

```c
v0 = 1;      /* set before the compares */
v1 = 9;
if (arg2 == v1) return v0;
```
Then gcc: v0 = 1 (pseudo, folded) → the copies at the 4 return sites → 4 × `li $2,1`?? But the returns are in different blocks (each `if` arm) → cross-jump merges them into one block → one `li $2,1` + `jr $ra`... which is what mine did (the return-1 block). But the ROM's `li v0,1` is at ins 23 (in the chain block), not in the return block.

So the ROM's structure = the "1" set is in the chain block, and the returns branch directly to the epilogue. This is exactly what happens when the pseudo is $2 (hard reg): the set `li $2,1` is in the chain block, and the returns are just `jr $ra` (no copy).

Without the pin, gcc materializes the constant at the return block. The ONLY difference is where the constant is materialized.

Hmm, unless... we can make the C have the "1" materialized in the chain block naturally! What if the "1" is used in the chain block in a way that requires materialization there? E.g.:

```c
v0 = 1;
v1 = 9;
if (arg2 == v1) return v0;
v1 = 0x11;
...
```
The "1" is only used in the returns. But what if we ALSO use it in the chain, e.g. as a comparison? That changes the bytes.

Hmm, what if the returns are replaced by a structure where the value is computed once and there's ONE return at the end?

```c
if (...mask...) {
    v1 = 9;
    if (arg2 == v1) { v0 = 1; goto done; }   /* hmm */
    ...
}
```
Then the "1" set would be in each arm → 4 sets ✗.

Hmm, what if:
```c
    v0 = 1;
    v1 = 9;
    if (arg2 == v1) return v0;
```
The gcc "jump threading"/"cross-jump" merges the 4 return blocks. The merged block gets the copy `li $2,1`. Then sched1 might move the `li $2,1` INTO the delay slot of the branch that jumps to it? No — the merged block is a separate block; the `li $2,1` is inside it.

BUT: what if the merged block IS the chain block? I.e., if the returns were "fall-through" style...

Hmm, let me think about the ROM's block structure again:
```
20 bnez v0, +0x90        ; (mask != 0) → return 0
21 li v1,9               ; delay slot
22 beq a2,v1,+0x94       ; (arg2 == 9) → RET
23 li v0,1               ; delay slot of ins 22
24 li v1,17
25 beq a2,v1,+0x94
26 li v1,41
27 beq a2,v1,+0x94
28 li v1,10
29 beq a2,v1,+0x94
30 nop
31 lw v0,376(a0)
```
Notice: ins 23 `li v0,1` is the delay slot of ins 22, and ins 24 `li v1,17` is a separate instruction (not a delay slot of anything — wait, ins 24 is at +0x60, and ins 25 (beq) is at +0x64 → ins 24 is NOT in a delay slot (the delay slot of ins 22 is ins 23). Hmm, so ins 24 `li v1,17` is a normal instruction in the block, and ins 26 `li v1,41` is the delay slot of ins 25's beq.

So the block: [21 li v1,9][22 beq][23 li v0,1][24 li v1,17][25 beq][26 li v1,41][27 beq][28 li v1,10][29 beq][30 nop][31 lw v0,376(a0)][32 nop][33 xor][34 j][35 sltu].

Interesting: the delay slots are: ins 21 (of the bnez at 20), ins 23 (of the beq at 22), ins 26 (of the beq at 25), ins 28 (of the beq at 27), ins 30=nop (of the beq at 29), ins 32 (of the load at 31), ins 35 (of the j at 34).

So the "li v1,X" instructions: ins 21 (delay), ins 24 (NOT a delay slot!), ins 26 (delay), ins 28 (delay). Hmm, ins 24 is a plain instruction — because the beq at 25's delay slot was taken by ins 26 (li v1,41). So the scheduler distributed the "li v1" sets: one plain + three delay slots.

And the "li v0,1" (ins 23) is a delay slot.

So the ROM's chain is: v1 = 9 (ins 21); compare; v1 = 17 (ins 24, plain); compare (ins 25) with delay slot v1 = 41 (ins 26); compare (ins 27) with delay slot v1 = 10 (ins 28); compare (ins 29) with nop delay.

OK. So the ROM's structure is what gcc produces with the pin.

Now, in MY compile the structure was:
```
20 bnez v0,6ac4, delay: move v0,zero
22 li v0,9
23 beq a2,v0,6aa4, delay: li v0,17
26 li v0,41 (delay of 25)
28 li v0,10 (delay of 27)
29 bne a2,v0,6aac   (inverted!)
30 nop
31 j 6ac4, delay: li v0,1
```
Hmm, mine's chain has "li v0,X" in $2 and the last compare is inverted (bne) and there's an extra block.

So mine differs in: (a) the const temp's register, (b) the delay slot of the bnez at 20 (move v0,zero vs li v0,9), (c) the last compare's polarity, (d) the extra return block.

(c) and (d) are consequences of (a)/(b).

Honestly, this looks like a hard nut. Let me consider the possibility that this item is a WALL. But before that, let me try 2-3 more shapes:

Shape X: reorder the source so the const temp's first set is NOT in the delay slot of the mask branch. E.g. move `v1 = 9;` BEFORE the mask test? Not possible (it's inside the block).

Shape Y: Use `&&`/`||` folds: e.g.
```c
if (((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) && (arg2 == 9 || ...
```
changes structure.

Shape Z: What if we use a *nested* if structure to make the last compare a `beq` (not inverted)? In mine the last compare was inverted because the "return 1" block was placed after it. Hmm.

Shape W: swap the order of the two inner tests? no.

Let me try a different tactic: give the "1"-pseudo a hard-ish preference by making it the value of a *comparison* used in the returns:
```c
v0 = (arg2 == v1);   /* no */
```

Hmm, let me look at this from the "what C would the ROM's author have written" angle. The ROM's code: returns 1 if arg2 ∈ {9, 17, 41, 10} (with the mask condition), else returns (arg0+0x178 != arg1). The original source probably looked like:

```c
if (*(u16 *)(arg1) == 0) return 0;
...
if ((*(s16 *)(arg1+0xAE) & arg3) == 0) {
    int a = 1;
    switch (arg2) {
    case 9: case 0x11: case 0x29: case 0xA: return a;
    }
    return *(s32 *)(arg0+0x178) != arg1;
}
return 0;
```
Hmm, a switch would produce a jump table.

Or:
```c
    int a = 1;
    if (arg2 == 9) return a;
    if (arg2 == 0x11) return a;
    ...
```
Same as the current src.

OK, let me try the alloc table to see what gcc thinks. Actually, let me try a cheaper experiment first: does the ORDER of the four compares matter for the allocation? No.

Let me try: what if the "1"-pseudo is declared as `s16` AND the returns are `return v0;` — variant B gave 17 (same). Because gcc folded the extension.

What if the "1"-pseudo is declared as `u32`? same as s32.

Hmm, what if we make the const temp `s16` so the comparison is HImode: `if (arg2 == (s16)v1)`? The target has `beq a2,v1` (32-bit compare) ✗.

Let me try the alloc table for real. Steps:
1. tools/cc1_dumps_tu.sh — let me read its usage.

Actually, time check: I've used ~25 min on item 3. The budget is 20-30 min per item. 7 items → ~3.5 hours. I should manage time: give item 3 a few more experiments, then move on.

Let me try ONE more idea for item 3, which is the "return value in $2 via a real pseudo" idea, but with the trick of using the *final* expression's variable:

What if the source is:
```c
if ((*(s16 *)((u8 *)arg1 + 0xAE) & (u16)arg3) == 0) {
    v0 = 1;
    v1 = 9;
    if (arg2 == v1) return v0;
    ...
    v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
    return v0;
}
```
= variant F (18).

What if instead the final expression uses a SEPARATE variable and v0 (the "1") is used to compute it? e.g.
```c
    v0 = 1;
    ...
    v1 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
    return v1;
```
Hmm, v1 is the const temp — reusing it would break the chain? The chain is done by then. Let me think: `v1 = (load != arg1); return v1;` — the const temp v1 would then have 5 sets... and the target's final expression computes into $2 (`xor v0,v0,a1; sltu v0,zero,v0` — the result in $2 = v0!). Hmm, interesting: in the target, the final comparison result is in $2 (v0) — the same register as the "1"! So maybe in the ROM's source, the final result IS assigned to the same variable as the "1"?! I.e. the source might be:

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
v0 = *(s32 *)((u8 *)arg0 + 0x178) != arg1;
return v0;
```
= variant F! And F scored 18 (one worse than 17). Hmm, but F's structure might be right in the tail. Let me look at F's diff in detail — maybe F is close and a small tweak fixes it.

Let me get F's fulldiff.
