---
ts: 2026-11-06T06:09:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_m66HajKa7JkYY2WfDsxw
---
p1's RTL:
- insn 4: reg72 = a0 (the parameter)
- insn 11: reg73 = reg72 (a copy!) — this is the `s0 = (s32)a0;` assignment.
- insn 18: store to (reg73+32)
- insn 27: a0 = reg73

So there are TWO pseudos: reg72 (the parameter) and reg73 (the s0 variable). The copy at insn 11 is `s0 = (s32)a0`.

In the target (orig), s0 is hard $16, so the copy is `move $16, a0` (the prologue move).

In p1, reg72 and reg73 are both cross-call allocnos → two callee-saved regs (s0, s1). gcc assigned reg72=$16 and reg73=$17, with `move s1,s0`.

To fix: make gcc coalesce reg72 and reg73 (so only one register). They're connected by a copy `s0 = (s32)a0`, so global_alloc should coalesce them... but it didn't (reg72 crosses calls? The parameter a0 is used... hmm).

Actually, reg72 is the parameter; it's used at insn 11 only (the copy) — so it dies at insn 11. Why would it cross calls? The conflict list says 72 conflicts with 2,3,4,29 — the call-clobbered regs. So reg72 is live across a call? It's live from insn 4 to 11, and there's a call at insn 14 — no, insn 11 is before the call. Hmm, so it shouldn't conflict with $2.

Wait, maybe global.c's conflict computation marks it. Hmm.

Hmm, actually, the conflict "72 conflicts: ... 2 3 4 29" might be because reg72 is the *incoming argument* and conflicts with the hard regs it's copied from? Hmm.

Let me think differently: the target (orig) has s0 as a hard reg, so no issue. Lever-free, we want ONE callee-saved register.

Idea: avoid the separate `s0` variable — use `a0` directly? But a0 is caller-saved and the pointer is used across calls; gcc would copy it to a callee-saved reg anyway.

Idea: make the copy `s0 = (s32)a0` fold by using `a0` directly in the code (casting each use). Then there's only one pseudo (the parameter), which gcc will copy to a callee-saved reg once (the prologue `move s0,a0`). That's the target!

Let me try: replace `s0` with `(s32)a0` everywhere? Hmm, but `s0` is used as a pointer in casts.

Simpler: `s32 s0 = (s32)a0;`? Same.

Hmm, why doesn't gcc coalesce reg72 and reg73? Because reg72 (the parameter) is live across... let me look: insn 4 sets reg72, insn 11 reads it. No call in between. So no conflict with $2.

Hmm, but the conflict list says 72 conflicts with 2,3,4,29. That's odd. Maybe global.c adds conflicts for the parameter with the hard regs it's already in? Hmm.

Actually, maybe the copy at insn 11 (`reg73 = reg72`) is a `movsi` and global.c's `qty_phys_copy_sugg` should coalesce. The preferences show "74 preferences: 2 4" but nothing for 72/73.

Hmm. Let me try a different approach: eliminate the copy by declaring the parameter as `s32` (not void*)? The function signature is `void func_8017EF9C(void *a0)`. The body does `s0 = (s32)a0;`. If we changed the signature to `s32 a0`, that'd be a signature change — not allowed (callers stay as they are). Hmm, but the brief says "no signature or decl change outside the body".

What if we keep `void *a0` but use a0 directly (no s0 variable)? E.g., `#define s0 ((s32)a0)`? That's textual. The body would then use `(s32)a0` everywhere; gcc would have one pseudo (the parameter) and copy it to a callee-saved reg for the calls. The prologue would be `move s0,a0` (or similar) and the calls `move a0,s0`.

But the target's body has `s0` used for the struct accesses: `((Unkstruct_800B5CB8 *)s0)->unk20`. If we write `((Unkstruct_800B5CB8 *)(s32)a0)->unk20` everywhere, gcc sees a0 cast — same pseudo.

Let me try that: replace all `s0` with `(s32)a0` in the body (after removing the `s32 s0; s0 = (s32)a0;` declaration). Hmm, but the `(s32)a0` cast in each use is fine.

Actually simpler: keep `s0` but write `void *s0 = a0;` — a pointer variable assigned from a0. Then the copy is pointer-to-pointer. gcc might coalesce better. Let me test.

Or: use a0 directly by renaming: remove the s0 declaration and replace `s0` with `a0` in the body, adding casts where needed. The body uses `(Unkstruct_800B5CB8 *)s0` (a cast from s32) — with a0 being void*, `(Unkstruct_800B5CB8 *)a0` works directly. And `(s32)(s0 + 0x58)` → `(s32)((s32)a0 + 0x58)`. Hmm.

Let me look at all the s0 uses:
1. `((Unkstruct_800B5CB8 *)s0)->unk20 = ...`
2. `if (((Unkstruct_800B5CB8 *)s0)->unk20 == 0)`
3. `func_8012CAE4((s32 *)s0);`
4. `func_8001C2C4(((Unkstruct_800B5CB8 *)s0)->unk20);`
5. `v1 = D_80184CA8[((Unkstruct_800B5CB8 *)s0)->unk70];`
6. `((Unkstruct_800B5CB8 *)s0)->unkFE = ...`
7. `((Unkstruct_800B5CB8 *)s0)->unk100 = ...`
8. `v0 = ((Unkstruct_800B5CB8 *)s0)->unk20;`
9. `v1 = ((Unkstruct_800B5CB8 *)s0)->unk100;`
10. `((Unkstruct_800B5CB8 *)*(s32 *)(s0 + 0x20))->unk10 = 0x400;`  ← s0 + 0x20 (s32 arithmetic)
11. `func_8012B2CC(s0);`
12. `loc[2] = D_80184D0C[((Unkstruct_800B5CB8 *)s0)->unk100];`
13. `func_8012B14C(s0, (s32)&loc[0]);`
14. `*(s32 *)(s0 + 0x58) = v0;`
15. `*(s32 *)(s0 + 0x1C) = *(s16 *)(s0 + 0x70);`
16. `func_8012AD50((void *)s0);`

If I replace `s0` with `(s32)a0`, uses like `(s32)((s32)a0 + 0x20)` work.

Hmm, but the `void *a0` parameter: `((Unkstruct_800B5CB8 *)a0)` is fine.

Let me try replacing `s0` with `(s32)a0` textually and removing the declaration. Actually, to keep it readable, maybe declare `void *s0 = a0;` — let me test both.

Test 1: `void *s0 = a0;` (pointer variable).
Test 2: replace all s0 with `(s32)a0`.

Let me do test 2 first since it avoids the copy entirely.

Hmm, careful: `func_8012CAE4((s32 *)s0)` → `(s32 *)(s32)a0` — fine.

Let me generate.

Also, the pins: v1 $3 and s0 $16. For the v1 pin, I'll handle later.

Let me generate q1 = orig with pins removed, launder removed (pa0→s0), and s0→(s32)a0.

Hmm, that's a lot of edits. Let me do it with python: take n2.c (pins removed, pa0=s0) and then remove `s32 s0; s0 = (s32)a0;` and replace `s0` with `(s32)a0`.

Wait, n2.c still has `s32 pa0; pa0 = s0;`. Let me start from p1.c (pa0 removed) and then do the s0 elimination.

p1.c:
```c
void func_8017EF9C(void *a0) {
    s32 loc[5];
    s32 s0;
    s0 = (s32)a0;
    ...
```
Replace `    s32 s0;\n    s0 = (s32)a0;\n` with nothing, then replace all `s0` with `(s32)a0`.

Careful: the text `s0` might appear in other identifiers (e.g., `D_80184...`? no). Let me check: "s0" appears in the source as a standalone variable. Any other occurrence? `loc` no. OK.

But `(s32)a0` inside `((Unkstruct_800B5CB8 *)(s32)a0)` — fine.

Let me do it.
