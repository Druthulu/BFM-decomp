---
ts: 2026-11-06T08:43:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tZPnI2RT6AGk2tf6JrTe
---
The do-while didn't prevent the merge. So combine still merges across the label? Or the do-while didn't create a label because empty body.

Let me think about what combine does: `val = nudge; val = -val;` in the same extended basic block. The do-while(0) might not create a real block if gcc removes it early.

Alternative: make the copy survive by making the two assignments *not* adjacent in RTL, e.g., an intervening instruction that isn't removable. But the target's asm contributes nothing else.

Wait — actually, what does the asm do exactly? `__asm__ __volatile__("" : : "r"(val))`. This makes `val` live at that point, so the copy `val = nudge` is emitted, and the negation operates on val. It also acts as a scheduling barrier/block boundary? An asm is a basic-block boundary for combine? Actually asm volatile is not a jump; combine treats it as an insn that can't be merged across.

Lever-free ways to prevent copy+neg merge: 
1. Make the negation's operand not a copy but a value with another use. E.g., if `nudge` is used after the negation, combine can't... no, combine would still merge val=-nudge and keep nudge for the later use? The merge is about val = nudge; val = -val → val = -nudge. If nudge is used elsewhere later, the merge is still valid.
2. Give `val` a use between the copy and the negation that forces a register: e.g., `val = nudge; func(val);` no.
3. Make the negation depend on the *old* val in a way that the copy matters: e.g., `val = nudge; val = -val;` is exactly that.

Hmm, what if we make the copy's source a *different variable* that also equals nudge? e.g.:
```c
val = nudge;
val = -val;
```
combine merges. But:
```c
val = nudge;
val = -val;
```
What if there's a *sequence point* like a function call in between? The target has no call there.

Another idea: make the negation a *different expression* that combine can't express as a merge because it involves a memory access or another value. E.g. `val = 0xFFFFFFFF + 1 - val`? no.

Hmm, maybe the real trick is different: instead of preventing the merge, make the *if* branch's assignment produce the move and the else's negation use v1. Wait, target:
- 6310 bnez v0 (rand&1)
- 6314 move v1,s1   ← delay slot, always executed
- 6318 negu v1,v1   ← else only

The move at 6314 is the if-branch's `val = nudge`. In mine, the same move exists at 6314 (since the diff shows only the negu differs). So mine: `move v1,s1` then `negu v1,s1` in the else. The target's else negates v1 (which was just set by the move).

So the difference is just the operand of negu: s1 vs v1. The copy `val = nudge` in the else is what's missing in mine. Since the delay slot already contains move v1,s1 (hoisted from the if), the target's else negu v1,v1 reuses that.

In mine, combine merged the else's copy+neg into negu v1,s1.

Can we get `negu v1,v1` without the asm? We need the else's `val = nudge` to not be merged with the negation. Since the move is already emitted (for the if branch), maybe if the source's else copy is written as `val = nudge;` and the negation as `val = -val;` — combine merges them regardless.

What if the else negation is written as `val = -nudge;` and the *if* branch copy... no, then no move in else.

What if the else uses a temp: 
```c
s32 t;
...
} else {
    val = nudge;
    t = -val;
    val = t;
}
```
combine may still collapse.

Hmm, what about `val = nudge; val = -val;` where val is *also used before* in the block? The preceding code doesn't use val.

Let me think about combine's mechanics: it merges `(set val nudge)` into `(set val (neg val))` producing `(set val (neg nudge))`. To prevent, the value `val` must be used between the two sets, or the sets must be in different blocks.

The asm creates a use. A real C use that costs no instruction... What about a *comparison whose result is used in a branch that the target has*? The target's next branch is at 6340 `beqz s2` — far away.

What about using val in the *negation expression* twice: `val = -val + 0;` → combine folds to neg. `val = -val | 0;` → fold. `val = (val ^ -1) + 1`? For a signed neg, combine might not recognize xor+add? It does: -x = ~x+1. GCC combine's simplify_rtx may handle it. But maybe not with s32 semantics? Let me test: `val = ~val + 1;` or `val = (val ^ 0xFFFFFFFF) + 1;`.

Also `val = -1 * val;` → mult by -1 → neg.
`val = val * -1;` same.
`val = 0x80000000 - val`? no.

What about `val = -(val + 0);` fold.

Another idea: make the copy go through a *different variable* that combine can't see through because of a type/size: e.g. `val = nudge;` where val is s32 and nudge is s32. If the copy were through a u32 temp: `u32 u = nudge; val = -u;` → combine merges to neg nudge.

What if the else's copy is `val = nudge;` and then the negation uses a *different* variable that aliases: no.

OK, different tack: maybe the real C is `val = nudge;` in the else but the *negation* is `val = -val;` written as a *separate statement inside a do-while with a condition*? Tried.

What about making the else branch a *loop* that runs once with a real condition: `while (1) { val = nudge; val = -val; break; }`? That creates a block boundary with a label and jump — would add insns (j). No.

Hmm, what about the `if (rand() & 1)` structure: maybe restructure to:
```c
val = nudge;
if (!(rand() & 1)) {
    val = -val;
}
```
Then: copy val=nudge before the branch (move v1,s1), then if !(rand&1) negate. The target's bnez tests rand&1; with this structure, the branch would be beqz instead of bnez unless gcc inverts. Hmm, the target is bnez v0,631c (if rand&1 → skip negation). If we write `if (!(rand() & 1)) val = -val;`, gcc emits `bnez v0, skip` — same! And the copy `val = nudge;` is before the test, so it's emitted before the branch → could be in the delay slot or before.

But the store `sw v1,16(s0)` is after. Let's think: source:
```c
val = nudge;
if (!(rand() & 1)) {
    val = -val;
}
CAST_WIDTH(s32, param_1, 0x10) = val;
```
Hmm wait, but in the original, the `if (rand() & 1) val = nudge; else { val = nudge; val = -val; }`. The else's copy is what the asm keeps. Restructuring to `val = nudge; if (!(rand()&1)) val = -val;` is semantically identical and real C! Then the copy is unconditional before the test, and combine won't merge it into the negation? It might: val = nudge; if (...) val = -val; — combine could still see the copy and the neg within the same block (the if body is a different block, so no merge across the branch!). The negation is in a separate basic block → combine can't merge. And the copy is before the branch.

That's promising and it's real C. But does it produce identical code? Target: 
```
6304 jal rand
630c andi v0,v0,1
6310 bnez v0,631c
6314 move v1,s1
6318 negu v1,v1
631c sw v1,16(s0)
```
With `val = nudge; if (!(rand()&1)) val = -val;`: the copy `move v1,s1` would be emitted before the branch (in the delay slot, reorg). Then the test: rand&1, bnez to skip. The negu in the body. Same! 

But careful: the original if/else also has `val = nudge` in the *if* branch. The restructure removes the if branch's assignment (now unconditional). The generated code should be the same.

But is this "real C moves only" and not a lever? Yes — statement restructuring.

Let me test it.

Also the `if (rand() & 1)` test: in the restructure I write `if (!(rand() & 1))`. That's a `!` fold, allowed (&&/|| folds are in the catalog).

Let me create c5:
```c
    r = rand();
    nudge = r << 4;
    if (hi == 0) {
        nudge = r << 5;
    }
    val = nudge;
    if (!(rand() & 1)) {
        val = -val;
    }
```
And keep the rest.

But note: the original `if (rand() & 1) { val = nudge; } else { val = nudge; val = -val; }` — after the restructure, `val = nudge` moves before the rand() call? No: `val = nudge;` is placed after `if (hi==0) nudge = ...` and before `if (!(rand()&1))`. But the rand() call is *inside* the if condition, so the copy happens before the call! Target has the copy AFTER the call (at 6314, after jal at 6304). Hmm: target order: jal rand (6304), andi, bnez, move v1,s1 (6314, delay slot of bnez). So the copy is after the call.

If the source is `val = nudge; if (!(rand() & 1))`, the copy is emitted before the call `rand()`. That would differ: move v1,s1 before jal. Unless the compiler/scheduler moves it after... sched1 can't move across a call (block boundary). So that would differ.

Hmm. So instead: `if (rand() & 1) { val = nudge; } else { val = nudge; val = -val; }` is required to have the copy after the call.

Alternative restructure keeping the call first:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```
What if we write:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
}
if (!(rand() & 1)) ... 
```
no, calls rand twice.

Hmm. What about:
```c
r = rand();
...
val = nudge;  /* but r was already computed? */
```
Wait — actually there are two rand() calls: `r = rand()` earlier, then `if (rand() & 1)`. The second rand is at 6304.

What if the restructure is:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```
unchanged, but the negation written differently to avoid the merge.

OK let me think again about blocking combine. Combine works on the else block: {move val,nudge; neg val}. If between them there's an insn that uses val, no merge. The asm is such an insn.

Real C: what about a *volatile-free* use that's optimized to nothing but exists at RTL time? E.g., a use in a `?:` that folds? Hmm.

What about the else block written as:
```c
val = nudge;
if (val) val = -val;
```
That adds a branch (val != 0) — extra insns.

What about `val = nudge, val = -val;` comma — same RTL.

What about making the copy conditional in a way that produces the same code:
```c
if (rand() & 1) {
    val = nudge;
} else {
    if (nudge) val = nudge; else val = nudge;
    val = -val;
}
```
adds branches.

Hmm. What about the *type* of val/nudge? If val is `s32` and nudge `s32`, the copy is a reg move. If val were `u32`, negation of u32 is still negu.

What if the copy is `val = (s32)nudge;` same.

Hmm, what about making the negation use a *different* variable that is a copy of val:
```c
s32 t;
...
} else {
    val = nudge;
    t = val;
    val = -t;
}
```
combine: t=val; val=-t → val=-val; and then val=nudge merges → -nudge. Likely same.

What if t is used later? Adds liveness.

Let me reconsider the target: maybe the target's code comes from a source where the else's copy is a *different value*: e.g. the else block in the original might be:
```c
} else {
    val = nudge;
    val = -val;
}
```
and the asm was inserted because the original binary has the move. Fine.

Since this is a "keepalive" the decompiler inserted, the crack must be found in real C. Let me look at moves.md for similar cracks: "keepalive | func_8017BF14 | WALL lreg-tie-dying-pin" etc. And "func_800CB458 MATCH: pass arg0 to func_800CAF84 (cast call) — keeps $4 live across the Struct16 copies so local-alloc gives the temps a1-a3 as target; the pin+keepalive had faked that liveness".

Hmm, here maybe the move's purpose isn't to block combine but to extend val's live range so that local-alloc assigns v1 vs s1. Wait, the register pair s1->v1 means mine uses s1 where target uses v1 for the negu operand. The target's negu v1,v1 — v1 is the result register. Mine's negu v1,s1 uses s1 (nudge's reg). The merge causes the source operand to be s1 directly. If the merge were blocked, the negu's operand would be val's register, which is v1 (since val is in v1 from the move).

So the fix is indeed to block the merge.

Idea: make the else block's negation operate on a *volatile-free* copy with a function call? no.

Idea: use `val = -val;` but make the copy `val = nudge;` a *store+load*? no.

Idea: make `val` a pointer? no.

What about `val = nudge;` then `val = -val;` where the second statement is inside a `do { } while (0)` (tried, didn't work — combine crossed it? Maybe the do-while was removed early). What about `if (1) { val = -val; }`? The constant fold removes the if but might leave a block boundary at RTL/combine time? Probably folded in cse/flow before combine? Let me test.

What about `while (0) {}` between? adds nothing.

What about a `switch`? 

Let me try a bunch:
- c5: `if (1) val = -val;`
- c6: `do { val = nudge; } while (0);` around the copy (tried, but with the neg outside — c2 was do{val=nudge;}while(0); val=-val). Let me instead put both inside: `do { val = nudge; val = -val; } while (0);` — the loop body is a block; combine works within a block so it'd still merge. Unless the do-while creates a label inside.
- c7: `goto` label between.
- c8: `val = nudge;` then `val = -val;` with `asm` replaced by a *real* statement that's a no-op: `(void)val;` (dropped), `val = val;` (dropped).

Hmm, what about making `val` used in the *condition* of the if? Like:
```c
if ((val = nudge, rand() & 1)) { ... } else { val = -val; }
```
no.

Wait — here's a thought: the else block in the target has the copy `move v1,s1` in the bnez *delay slot*. So the copy is the first insn of the else block, and reorg moved it into the branch delay slot. Then negu. If the copy were merged into the negu, we'd get negu v1,s1 (mine). To block combine, we need an insn between the copy and the negu *in the else block*, but the target has none — the copy is in the delay slot and the negu right after. So the asm's insn was a zero-instruction use that combine saw as a use of val but which emitted nothing! Yes: the asm has no instructions, but at RTL it's an insn that uses val, blocking combine.

So we need a zero-emission RTL use of val. Real C constructs that produce RTL but no code... A `(void)val` is optimized away at the tree level (no RTL). 

What about using val in a context that cse/combine can't remove but that generates no code because the result is dead... e.g., `val = -val;` then a use.

Hmm, what if the else's copy is made through a *memory* access that's optimized to a register? no.

What about the value being used in a *conditional expression* with side effects: `val ? 0 : 0;`? Folded.

What if we make the else block's negation a `val = -val` and the copy `val = nudge` where `nudge` is re-read... no.

Alternatively, prevent combine by making the copy NOT adjacent in RTL: insert the *negation of a different value* between? adds insns.

Hmm, hold on. What about the `r` variable: `r = rand(); nudge = r << 4; if (hi == 0) nudge = r << 5;`. The target at 62f8: `bnez s2, 6304; sll s1,v0,0x4; sll s1,v0,0x5` — so r is in v0, nudge in s1. Then jal rand; andi; bnez; move v1,s1; negu v1,v1.

What if the copy in the else were `val = r << 4;` (recomputing) instead of `val = nudge`? That would add shifts. No.

What about making the else's copy use a *different source register*? e.g. `val = nudge;` where nudge is s1 — fine.

Let me look at combine's behavior: `(set (reg val) (reg nudge))` followed by `(set (reg val) (neg (reg val)))`. Combine's try_combine merges if the intermediate result is used only there. If val is used *later* (it is: stored twice after), still merges.

What if the negation is written so that the *first* set is needed for something else too: e.g.
```c
val = nudge;
if (val & 0x80000000) val = -val;  // no
```

Hmm, what about a *cast through a different-width type* that forces a copy: e.g. `val = (s32)(u16)nudge;`? That changes semantics (truncation) and adds insns.

What about `val = nudge;` where nudge is `s32` and val is `s32`, but we write `val = nudge + 0;`? combine folds.

OK, maybe the real answer for this item is different: perhaps restructure the whole if/else so that the copy is *shared* and the branch structure differs. Target's bnez tests rand()&1 and jumps to the store (skipping the negu). Equivalently:

```c
val = nudge;           // after rand() call? No, before it in source
```
Hmm, but the copy must be after the call. What if:
```c
s32 t = rand();   // no, the call is in the condition
```

What about:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```
→ restructure as:
```c
val = nudge;
if (!(rand() & 1)) {
    val = -val;
}
```
Here the copy is BEFORE the rand() call in source order. But gcc might still schedule the move after the call? No, calls are barriers.

Unless... `val = nudge;` is cheap and sched1 won't move it across the call.

Hmm, but wait: in the target, is the `move v1,s1` in the delay slot of the bnez, which is after the call. If the source had the copy before the call, the code would be `move v1,s1` before `jal rand` — different.

Unless the compiler *sinks* the copy past the call? GCC doesn't move insns across calls.

So that restructure won't match.

Let me test it anyway to see the diff (cheap).

Another thought: maybe use `?:`:
```c
val = nudge;
if (!(rand() & 1)) val = -val;
```
vs target. Let me also test the "if (rand() & 1) {} else { copy; neg }" with the neg written as a call-free helper? no.

Wait, maybe there's a much simpler real-C crack: the else branch's `val = nudge;` might be removable if the negation is expressed on `nudge` but the *if* branch's copy is the one in the delay slot... no, mine already has the move at 6314.

Hmm, let me reconsider mine's exact code:
mine[50]? Let me dump mine (c1) around insns 48-53 to see the block.
