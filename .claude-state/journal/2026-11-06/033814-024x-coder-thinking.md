---
ts: 2026-11-06T10:38:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UaLvJKMWznFyoPSncqXk
---
Now I see: `move s1,a0` at prologue, `move s0,s1` after the jal (in the delay slot region). s1 is used for the early uses (`sw v0,32(s1)`, `move a0,s1`), and s0 for all later uses. So the pointer is copied: s1 (early) → s0 (later). Why? Because the local `s0` variable... 

AH WAIT. I see it now: the assignment `s0 = a0` is a copy. Then the value used is the local `s0`. But gcc's global-alloc assigned the *parameter* pseudo (a0) to $s1 (because it's live until... it's used in the copy at top and maybe later? no). And the local pseudo to $s0. The copy `move s1,a0` is `s0 = a0` where the local got s1?! Then `move s0,s1` is another copy.

Hmm, actually: `move s1,a0` then uses of s1 for early uses. So s1 = the local variable s0. Then `move s0,s1` creates a copy of the local into s0, and later uses use s0. That's a copy of a variable into another register. That's characteristic of gcc's *loop/global* code deciding the pseudo needs to be in a different register after the branch — no.

OR: it's the `register void *s0 __asm__("$16")` removal leaving `s0` as a *local register variable*? No.

Wait, maybe the sed replacement left the `register` keyword? I replaced the whole line with `void *s0;`. Let me double check nopin.c line 3: "    void *s0;" yes.

Hmm, why would gcc copy the local into another reg? Because of the `if` — the value is live across a branch and the local-alloc/global-alloc decided... Actually this is exactly the "global-alloc copy" pattern: when a pseudo is live across a call and in a branch, global alloc may split into two allocnos with a copy. But gcc 2.7.2 doesn't split.

Another thought: the *parameter* a0 is copied into the local at the top. But then `((Unkstruct*)s0)->unk20 = v0;` and the if. Maybe gcc's expand created a copy of the local for the "struct" accesses because of aliasing? No.

Wait — look at the C: `s0` is `void *` and casts are `(Unkstruct_800B5CB8 *)s0`, `(s32)s0`. The `(s32)s0` conversion in `*(s32 *)((s32)s0 + 0x20)` and `func_8012A828((s32)s0, ...)`. Casting pointer→s32 shouldn't copy.

Hmm, could the second copy be a *reload* of the callee-saved register? No, it's in the prologue.

Let me test: what if I use a parameter-local with a different name and initialize at declaration? Let me just try a few variants quickly:

V1: `void *s0 = a0;` (init at decl)
V2: keep assignment but move the declaration of v0 etc.
V3: `void *s0; ... s0 = a0;` with the assignment *after* the extern declarations (already).

Actually here's a thought: in the orig with the pin, `s0` is hard reg $16 — a *fixed* register. References are hard-reg. There's no copy. Without the pin, gcc expands `s0 = a0` and then all uses of s0. The local s0 gets $s0 (or $s1). The `move s1,a0` and `move s0,s1` pair means there are two pseudos: P_a (→s1) and P_b (→s0), with P_b = P_a. Where does P_b come from? Possibly from the *first* store `((Unkstruct*)s0)->unk20 = v0;` where the struct pointer is a separate pseudo? No, it's the same s0.

Hmm, hold on: maybe it's because `v0` is a *local variable* named v0 that holds the call result, and gcc assigned v0→$2. Then `sw v0,32(s1)` — the store uses s1 for the base. Then `if (v0 == 0)`. Then in the else branch, the code uses `s0`. The register allocator (global) sees the s0 pseudo live across the branch/calls; local-alloc within the entry block allocated the copy destination to s1, and the global pass allocated the same pseudo elsewhere to s0, inserting a copy at the block boundary? That is: the s0 pseudo has a long live range spanning basic blocks; global-alloc assigns it one reg; but local-alloc already assigned the *copy* in the entry block... In gcc 2.7.2, global-alloc runs before local-alloc? Order: global alloc, then local alloc. Local-alloc doesn't reassign global allocnos. Hmm, but the entry block copy is where the parameter is copied.

You know what? This pattern (`move s1,a0` ... `move s0,s1`) is exactly what happens when the C has TWO variables: the parameter a0 and a local. If the local were assigned to $s1 and then a *second* local copies it... but our C has one local.

Unless the sed produced `void *s0;` where s0 shadows... no.

Let me test the simplest thing: change the C to use a fresh local name and initialize at declaration, and see if the double copy persists. Let me also test using `s32` arithmetic.

Actually, maybe I should look at the orig's assembly to see the target's prologue: target has `sw s0,16(sp); move s0,a0; sw ra,20(sp); jal; ...` — the copy `move s0,a0` is in the delay slot of the jal? Let me dump the target (baseline object). Find the baseline path. oracle.baseline_path(rec["obj"]) — let me grep for the build object for this TU.
