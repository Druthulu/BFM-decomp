---
ts: 2026-10-22T20:41:50Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CDXIf05ext5cxJ7V7Ff1
---
The prior coder tried second uses. gen_use2_dead: `q = it;` after the add — that would make it live... scored? It was in the "score 4" list? The grep -v "score 4" list didn't include gen_use2_dead, so it scored 4 too. Hmm, `q = it` — q is unused, so flow deletes it. Right, dead.

What if q is used? E.g. `q = it; ... if (q == 0) ...`? That would add code.

Hmm. Let me think about the target's structure once more. What if the target's else branch is NOT `it + 0x658C` but a *pointer* addition that gcc keeps: e.g. `p = (s32)((u8 *)it + 0x658C)` — same.

Alternatively, maybe the target's `it` in the else branch is *not* `(s32)D_80120194` but `p = (s32)D_80120194 + 0x658C` computed as two adds because the source had two statements:
```
it = (s32)D_80120194;
p = it;
p += 0x658C;
```
cse would fold p = it (constant) and p += K → constant.

What if `p` is computed from `it` via a *pointer* `it` and p is a pointer too? Hmm.

Let me try a different structural idea: what if the *test* block's reassignment is written so that gcc doesn't see it as dominating the copy? E.g., the copy block placed *before* the test label in the C but reached by a goto... it already is.

What if the source order is:
```
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) goto copy;
    ...
copy:
    p = it;
```
Same.

OK, different approach: maybe the fold can be prevented by making `it`'s assignment *not* a single set before the add. E.g., assign it twice with different constants? `it = (s32)D_80120194; it = (s32)D_80120194;` (gen_use2_dup_base, 4).

Or assign it from a *conditional*: `it = flag ? X : X;` folded.

What if `it` is assigned from `p`? no.

Let me try the "memory round-trip" idea, which is real C and might produce the right code:
```
it = (s32)D_80120194;
p = *(s32 *)&it + 0x658C;   // reload from the stack slot? it would be spilled
```
That adds a store/load. Probably 2 extra insns but might keep it in a register... gcc would optimize the round-trip away.

Another idea: use a `union` to type-pun `it` and read it back as s32 — optimized away.

What about making `it` a *global* (static) variable? Then `it = (s32)D_80120194` stores to memory; `p = it + K` loads → lui/addiu v1; sw; lw; addiu. Extra insns.

Hmm.

Let me reconsider: maybe the target's else branch has `it` live because the copy path is reachable from the else block directly! Look at the target's control flow: `4654 j 4664` (goto test). The copy block at 465c is between the j and the test block. Could the else branch's `j 4664` be a fallthrough into copy? No, it jumps to 4664.

Wait — look at 4654: `j 4664` with the delay slot at 4658 `addiu a1,v1,0x658C`. And 465c is `j 4694` (found) with delay `move a1,v1`. So the layout is: else block ends with j test (delay: p = it+K); then copy block (j found; delay: p = it); then test block.

In the source, the copy block is between `goto test` and `test:`. So the copy block is unreachable by fallthrough (j test jumps over it). Fine.

Now, in the target, at the copy block `move a1,v1` — v1 is the scan pointer (reassigned at 4664). So the first it is dead. Yet the add wasn't folded. So cse's fold decision isn't liveness-based; something else prevented it.

What else could prevent it? The launder. In the src def, the launder is right after `it = (s32)D_80120194;` and the fold is prevented. Without it, my gen_base folds.

Is there any other C-level way to make `it`'s value opaque to cse? The launder is an asm. Without asm: a `volatile` read, a function call, or a memory load.

Memory load idea: declare a *file-scope* pointer variable? We can't add declarations outside the body ("no signature or decl change outside the body"). But we can declare locals.

What about `s32 it; ... it = (s32)D_80120194;` then use `*(s32 *)(a0 + 0xA)`? no.

Hmm, what about the *function argument*: `a0` is a runtime value. `it = (s32)D_80120194 + (a0 & 0);` folds.

What about `it = (s32)D_80120194; if (a0) it = (s32)D_80120194;` — both arms same → cse merges.

I think the answer is the cse-const-addr wall. The prior coder's 35 variants + my analysis. But I must give it ≥20 min and ≥30 scored tries. Let me run a batch of ~10 new ideas quickly (each ~2s), which combined with the 35 existing scored candidates gives plenty of tries.

New batch ideas:
1. `it` live via a use that doesn't change codegen: `if (it == it) ...` folded.
2. `p = it + 0x658C` where the constant comes from a *variable*: `s32 off = 0x658C; p = it + off;`
3. `p = it + 0x658C` with `it` declared `u32`.
4. `p = (s32)((u8 *)it + 0x658C)`.
5. `it = (s32)D_80120194; p = it + 0x658C;` where `it` is a `s32` declared *inside* the else block (scope) — prior gen_decl_* tried types.
6. Make `it` the *same variable as p*: `p = (s32)D_80120194; it = p; p = it + 0x658C;`? cse folds.
7. Use a do-while(0) around the assignment: `do { it = (s32)D_80120194; } while (0);` — gcc folds the do-while away; but the loop notes might affect cse? With `// !FAKE: do-while` allowed. Hmm, do-while(0) is allowed only with the comment. It might prevent cse1 from... probably not.
8. Put the `it = ...` and the add in *different basic blocks*: e.g. 
```
it = (s32)D_80120194;
goto mid;
mid:
p = it + 0x658C;
goto test;
```
A label creates a new BB; cse1 is per-BB but has a constant table; it might not propagate across BBs! cse1 works per extended basic block. A label might split the EBB, preventing the fold. That's a real-C trick (a goto). Worth trying!
9. Similarly, insert an `if (p == 0) goto ...` between? no.
10. Use a `switch`? no.

Idea 8 is promising: the fold requires cse to know `it`'s constant at the add. If a label splits the block, cse1's table resets (unless it's a "cse basic block" with no jumps... a label alone doesn't break the EBB in gcc's cse; cse1 processes per basic block, and a label starts a new BB, so the equivalence table is per-BB → no fold across the label!). But the goto creates a jump, which definitely splits. And the target's code has a `j test` right there anyway.

But careful: adding a goto might change the codegen (an extra jump). Let's see: currently the else block ends with `j 4664` (goto test) — the C's `goto test`. If I add `goto mid; mid: p = it + K; goto test;` the compiler would emit `j mid` where mid is the next instruction → removed. The BB split remains. Worth a try.

Also idea: move the `p = it + K` *after* the test label? No, semantics.

Another variant: make the add happen in the `test` block? no.

Let me also try: `it = (s32)D_80120194;` then `p = it + 0x658C;` but with `p` assigned in a *separate statement after a label*.

Let me write the batch.
