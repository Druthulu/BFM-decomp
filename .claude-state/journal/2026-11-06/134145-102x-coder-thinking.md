---
ts: 2026-11-06T20:41:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_10cq0txag3uA4Kem3nOe
---
All 7 (folded to copies, propagated).

Let me think about vH again: `ent = (s32)a0 & 0xFFFFFFFC` gave score 3 with the correct allocation. The residual is the li+and vs move. 

What if we could make the mask a *single* instruction that's value-preserving? On MIPS, `andi` with a 16-bit unsigned immediate. What if the pointer is known to be in a small range? No.

What if we use `ent = (s32)a0 & 0xFFFFFFFC;` and the compiler knows a0 is 4-aligned (from the function signature/usage)? It doesn't.

What if we use `ent = (s32)a0 >> 0;`? folded.

Hmm, what about `ent = (s32)a0 * 1;`? folded.

What about `ent = (s32)a0 + (s32)(v[0] & 0);`? folded.

OK, let me consider whether a completely different placement of the copy could avoid the extra move in mine. In the baseline (7), mine has all stores on s0 and a `move a0,s0` before the final call (in the delay slot). The target has the move early and the stores on a0.

What if we write the final call as `func_80188650((void *)a0)` (the parameter) and the stores on `ent` (= a0, propagated)? Same thing.

What if we introduce a *second* parameter-like variable via the do-while scope that forces a0? Hmm.

What if the stores use `a0` directly (the parameter) and the call uses `a0`, so no copy is needed? Then the compiler would still use s0 (the parameter's home) and add a move for the call. Same as baseline.

Unless we can make the parameter's pseudo NOT need a callee-saved copy... e.g., if a0 were used only after the last call before RotTransSV. But a0 is used at the start (before the calls) too.

Hmm.

What if we split: use `a0` at the start (stored to s0), and after RotTransSV use a *new* variable that the compiler allocates a0? That's ent, propagated.

OK. What if we make the copy a *real* one by using the value in a way that the compiler can't propagate: e.g., store ent into a global/stack slot and reload? adds insns.

What about using `ent` in a *comparison* whose result is used? adds.

Let me try one more idea: make the copy via a *struct field*: e.g., a local struct with an s32 field, `ent = s.field` where s.field was assigned a0 — stack.

Hmm.

What about the `do{}while(0)` structure: if `ent` is assigned inside a do-while and used ONLY after the do-while, maybe cse1's loop handling prevents propagation. Let me test that specifically (vF was a compile error because of the declaration placement). Let me fix vF: declare `s32 ent;` with the other declarations, then `do { ent = (s32)a0; } while (0);  // !FAKE: do-while` as a statement, then the rest.

vF: replace `s32 ent = (s32)a0;` with `s32 ent;` and insert the do-while assignment... The declarations are inside the block:
```
    {
        register s32 zr ...
        s32 ent = (s32)a0 + zr;
        s32 v2;
```
I can replace `s32 ent = (s32)a0;` with `s32 ent;` and then add `do { ent = (s32)a0; } while (0);` after the declarations (before the existing do-while). The existing do-while starts after the declarations.

Let me construct:
```
        s32 ent;
        s32 v2;
        s32 t1;
        s32 one;

        do { ent = (s32)a0; } while (0);  // !FAKE: do-while
        do {  // !FAKE: ...
```
Let me test.

Also: what if the assignment is inside the do-while that already exists, but the uses after the do-while? I.e., move `ent = a0` into the existing do-while (vB did that) — the uses inside the do-while too. Let me instead put ONLY the assignment in the existing do-while and move the stores out? That changes the structure.

Let me test the "separate do-while for the assignment" idea.
