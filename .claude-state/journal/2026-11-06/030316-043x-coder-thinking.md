---
ts: 2026-11-06T10:03:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3lTuqiBbPnooPL2h8MxV
---
Not defined, so it uses the default in regclass.c/global.c. Let me check global.c's default REG_ALLOC_ORDER. Actually let me not go too deep; the empirical approach is better.

The key: we need to flip the allocation priority of `f` vs the giv pointer. Real-C moves: add references to f, or reduce references to the giv.

In the loop, `f = 1;` happens in a branch. The giv is `D_801AECD8[i1]` — an array pointer computed by strength reduction.

What if we express the loop differently so that f gets more refs or is born earlier/later? E.g.:
- `f = (*(u16 *)(D_801AECD8[i1] + 2) == 5) | f;` — that makes f assigned each iteration (more refs, but different codegen).
- Use `if (...) { f = 1; }` → same.

Alternatively, reduce the giv's refs: use the index directly with a multiply instead of strength reduction? That changes instructions.

Hmm. What did the keepalive actually do? It added a use of i1 in the loop. Since i1 is the base of the giv, adding refs to i1 might change the giv's derived-priority.

Let me look at global.c to understand: the priority of a pseudo = sum over refs of (ref count * loop depth weight). The giv pseudo (pointer) is created by loop.c strength reduction and has its own refs. Adding a use of i1 adds refs to i1, not the giv.

But target: i1 in a0 (both), so i1 vs giv is fine. The difference is f vs giv.

Hmm, wait. Maybe the keepalive's effect is different: `__asm__("" :: "r"(i1))` creates an asm insn that USES i1, making i1's live range span the whole loop body. Without it, maybe the giv and f are allocated differently through local-alloc interactions.

Let me try simple experiments on item 4:
1. Move the `f = 0;` before the loop (already).
2. Change `if (...) f = 1;` to `f = (*(u16 *)(D_801AECD8[i1] + 2) == 5);`? That changes f's value per iteration (f = 0 when not 5), which is semantically different! The original: f=0 initially, set to 1 if any matches. `f = cond` each iteration would reset to 0. Not equivalent.

But we could write `if (cond) f = 1;` — same.

3. Use a different loop shape: `for (i1 = 0; i1 < 5; i1++) { if (...) { f = 1; } }` — same.

4. Add a reference to f: e.g. `f = f;`? dead.

5. Use `f |= cond` — `f |= (*(u16 *)(D_801AECD8[i1] + 2) == 5);` — that's `f = f | cond`, which sets f to 0 or 1 each iteration. Original semantics: f stays 1 once set; `f |= cond` gives the same final result (f becomes 1 if any match, and remains 1 since 1|anything=1). Yes! Equivalent: f starts 0, each iteration f |= (cond ? 1 : 0). Final f = 1 iff any cond true. Same. And codegen: `or`/`slt` vs branch? Let's see. Hmm, `f |= (x == 5)` — the compiler might do `xor a2` + `sltu` + `or`, or a branch. Might differ.

6. Add a do-while(0) wrapper with i1 use (C0535): `do { } while (0)` doesn't use i1. To add a use, we'd need a real statement involving i1 that doesn't change codegen. Hmm — that's essentially a keepalive.

But wait: C0535 says do-while splits cse1 EBB. Not about refs.

The real issue: "greg-ref-count" walls (moves lines 16, 51, 60, 73). Those are walls. But item 4's diff is only a 2-register swap with identical instruction count — promising.

Let me try a few variants and score them. First, let me understand the exact loop code in target and mine.

Target case-1 loop:
```
2ea4: move v1,zero      ; f = 0
2ea8: move a0,zero      ; i1 = 0
2eac: li a2,5
2eb0: lui a1, D_801AECD8
2eb4: addiu a1,a1,0
2eb8: lw v0,0(a1)       ; p = D_801AECD8[i1]
2ebc: nop
2ec0: lhu v0,2(v0)      ; *(u16*)(p+2)
2ec4: nop
2ec8: bne v0,a2,2ed4
2ecc: nop
2ed0: li v1,1           ; f = 1
2ed4: addiu a0,a0,1     ; i1++
2ed8: slti v0,a0,5
2edc: bnez v0,2eb8
2ee0: addiu a1,a1,4     ; giv++
```

Mine (from diff): f=a1, i1=a0, giv=v1, so:
```
move a1,zero   ; f=0
move a0,zero   ; i1=0
li a2,5
lui v1, D_801AECD8
addiu v1,v1,0
L: lw v0,0(v1)
...
li a1,1  ; f=1
addiu a0,a0,1
slti v0,a0,5
bnez v0,L
addiu v1,v1,4
```

So f and giv swapped. To flip: make f's priority higher than giv's, or giv's lower.

Ideas:
a) Declare `f` earlier in the declaration list? Decl order affects local-alloc qty order, not global priority (refs). f is used in case 1 only.
b) Split f into a variable used more (e.g., a second reference): `if (cond) f = 1;` gives f 2 refs (set + read at `f != 1`). If we add another read of f (e.g., `if (D_801151FC == 0 && f == 0)`), that's a change but equivalent (f != 1 vs f == 0 — f is 0/1 so equivalent!). `if (D_801151FC == 0 && f != 1)` → could write `if (D_801151FC == 0 && f == 0)`. Same semantics since f∈{0,1}. Codegen might be identical or a ref more/less. Actually `f != 1` and `f == 0` generate the same compare. No extra ref.

c) Make f's birth later or its live range shorter? Priority = refs weighted by loop depth. f is live across the whole function (from case 1 to the `f != 1` use in the same block). Hmm.

d) Reduce the giv's refs: the giv has refs at lw, addiu (increment). If we avoid strength reduction by using `D_801AECD8[i1]` in a way that loop.c can't reduce... e.g., use a different expression `*(s32 *)((u8 *)D_801AECD8 + i1*4)`. loop.c would still reduce.

e) Use `f` in the loop condition somehow? e.g. `for (i1 = 0; i1 < 5 && !f; i1++)` — changes control flow.

f) The moves.md technique for greg-ref-count: "keepalive adds refs so pb takes a2 first". Here we need the opposite: reduce giv refs or boost f.

Let me look at global.c's priority computation to reason. Actually, empirical sweeps are cheaper.

Let me set up a batch of candidates for item 4. Since sc.sh scores one line per file, I can generate many variants with a script. The brief says scratch scripts under .run/ with the Write tool.

But first, let me think about what real-C moves could shift f vs giv.

Idea: make `f` a `u8`/`s16`? The original `s32 f`. If f is `u8`, HImode copies... might change codegen (extra andi). Probably worse.

Idea: move the `f = 0;` initialization to the declaration (`s32 f = 0;`)? But it's inside case 1. If f is declared at function top with `= 0`, that adds an initialization at function entry — codegen change (move at top). Target has `move v1,zero` inside case 1. So no.

Idea: use `f = 0;` then `for (...) if (cond) { f = 1; }` — current.

Idea: change the order: `if (cond) { f = 1; }` vs `f = cond ? 1 : f;`? That's `f = cond ? 1 : f` — same semantics, codegen: a conditional move (no cmov on MIPS) → branch or `slt`+`or`. Might change.

Idea: `f += cond`? no.

Idea: compute f via a separate loop variable: `s32 n = 0; for (...) if (cond) n++; f = n != 0;` — changes codegen.

Hmm. Let me look at the actual global.c priority formula and see what the keepalive did quantitatively.

Actually, let me try a more targeted approach: emulate the keepalive's effect with real C. The keepalive `"r"(i1)` adds a use of i1 inside the loop. A real C statement using i1 that generates no extra code... e.g., `if (i1 < 0) {}`? dead. Hmm.

What about making the loop body use i1 directly instead of the giv: `if (*(u16 *)(D_801AECD8[i1] + 2) == 5)`. It already does. loop.c strength-reduces it into a giv.

What if we prevent strength reduction by using the index in a non-linear way? E.g., `D_801AECD8[i1]` where i1 is `s16`? Then the address computation differs.

Alternatively, add a second use of i1: `if (*(u16 *)(D_801AECD8[i1] + 2) == 5 || i1 == 99) f = 1;` — adds a compare, changes code.

Hmm.

Wait — maybe the register swap can be fixed by *declaration order* / *variable reuse*. The global-alloc priority is refs-based, but the tie-break and assignment order also depend on the order pseudos are created (regno order?). In global.c, `allocno_compare` sorts by floor_log2(refs*loop weights) and then by birth/... Let me read global.c's allocno_compare in the reference.
