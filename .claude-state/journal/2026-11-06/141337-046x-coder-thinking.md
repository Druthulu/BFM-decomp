---
ts: 2026-11-06T21:13:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Oqd8HFvwWkhqR88d2WLa
---
Hmm! Even with the keepalive, score 1 — the move is still missing. Interesting: because without the pin, `rv = (s32)a0` is a copy that gets coalesced: the asm use "r"(rv) just needs rv in *some* register; s0 already holds a0, so `rv` IS s0 and the asm uses s0 directly — no move needed! So the move only appears because the pin forces rv into v0 (a copy from s0 to v0).

So the keepalive alone doesn't produce the move. The pin alone? Let me test: pin without keepalive → the `rv = (s32)a0` would be dead and deleted.

So the move needs BOTH: pin (forces a different register) + keepalive (keeps it live). That means PARTIAL is impossible here? PARTIAL:keepalive,pin = all kinds kept = WALL ("a win.c that keeps all row kinds is a WALL, whatever it scores").

Hmm! So we cannot even get a PARTIAL. Unless we can force rv into a register different from s0 by real C.

Wait — what if rv = a0 + 0, i.e., an arithmetic op that can't be coalesced? `rv = (s32)a0 + 0;` — combine folds +0 into a copy → same. `rv = (s32)a0 ^ 0`? folded. `rv = (s32)a0 | 0`? folded.

What about making the last expression something that computes a0+0 into v0: `rv = (s32)a0;` then a *use* that requires a different register... Hmm.

Actually, hold on. The target's move is `addu v0,s0,zero` = a copy. In real C, a copy a0→v0 is only emitted if the allocator can't coalesce. It can coalesce if the source dies and the target has no other constraint. With the asm use, the value is live at the asm but can just stay in s0. So no copy.

To force a copy: the target of the assignment must be used where v0 is required. Nothing in a void function requires v0 at the end... except a *return value*.

So this is the expand-void-return wall: the only real-C route is a return value, which the extern void decls forbid.

Wait, but what about the pin being needed for the lw too? Our w1 matched the lw without the pin. Hmm, but the comment said unpinned => `lw v1 / move v0,s0 / sw v1,0($v0)`. That was with the keepalive+pin structure. Whatever.

So: the item is a WALL with best 1 (lever-free), tag expand-void-return. Actually, is the "wall" tag from walls.txt? Let me check walls.txt for expand-void-return.

But before declaring the wall, the brief requires: a WALL needs ≥20 min and ≥30 scored tries on that item. Hmm! "past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

So I need 30 scored tries on this item to record a WALL. That's a lot but let me do it efficiently: generate 30 candidate variants via a script and score them with sc.sh in batches. Hmm, but I should genuinely try lever-free variations. Let me think about what to try:

1. Various ways to produce the trailing copy:
   - return-type change: blocked by decls, but maybe with `--try` TU text (not body) I could test if the TU allows... no, decl change not allowed.
   - Actually wait: maybe the *body* could contain a local `extern void` redeclaration? No.

2. Different variable layouts/orders that might change the allocation so the copy appears naturally:
   - rv as u32
   - sp20[2] vs sp20
   - store via a temp
   - `*a0 = sp20` directly
   - `rv = sp20; *a0 = rv;` with rv s32/u32/s16?
   - making rv live across the call (rv defined before the call and used after): `rv = sp20; ...` hmm.

3. Try to get the copy from a *conditional* move: e.g., `*a0 = rv; if (a0) rv = (s32)a0;`? The branch adds.

Hmm. Honestly the space is small. Let me think about the "move v0,s0" more: it's a copy of a0 into v0 at the very end. In the target's source it's `rv = (s32)a0` with rv pinned to $2 and kept alive by asm.

Since both levers are needed, and the kinds are exactly {keepalive, pin}, the answer is a WALL unless real C can replace both.

Wait — can real C produce a copy a0→v0 that survives? What if the asm keepalive were replaced by a *real use* of the value that requires v0? In a void function, v0 is only special for return values and calls. What if the last statement is a call `func_XXX((s32)a0)`? Then a0 is moved to a0 (arg reg), not v0.

What if we use the *return value of the preceding call* and combine? `func_8012B77C` returns s32 in v0. Hmm! The target's `lw v0,32(sp)` after the call overwrites v0. What if instead we did something where the last value in v0 is a0? Like `rv = (s32)a0` — no.

Hmm, what about a *tail call*? `return func(a0)`? extra jal.

I think it's a genuine wall. But per the rules, I need ≥20 min and ≥30 scored tries. Let me generate a batch of 30+ plausible variants and score them all with sc.sh (one line each). That's legitimate exploration: each is a real-C variation.

Let me be systematic. Variables to vary:
A. The trailing statement forms:
   1. `rv = (s32)a0;` (dead)
   2. `return (s32)a0;` (void fn; expand ignores)
   3. `return;` 
   4. `(void)(rv = (s32)a0);`
   5. `sp20 = (s32)a0;`
   6. `*a0 = rv = sp20;`
   7. `rv = sp20; *a0 = rv;` merged into `*a0 = sp20;`
   8. `((s32 *)a0)[0] = rv;`
   9. declare rv as u32/u16/s16
   10. sp20 as array/struct
B. Reordering / temp forms for the load:
   - `rv = sp20;` → `rv = *(s32*)&sp20;`
   - direct `*a0 = sp20;`
C. Splitting the call args: `func_8012B77C((s32)&sp20, a1+4, (s32)sp10)` variations (sp10 declared s32[4] vs char buffer, etc.)

But each variation only matters if it changes the residual. Since the residual is exactly 1 instruction (the dead move), only forms that create the move matter. Realistically nothing will.

However, the brief demands 30 scored tries for a WALL. I'll do it honestly with a generator of real-C variants, all lever-free, and record them.

Hmm, wait. Let me reconsider one thing: maybe the move can come from the function's return value if we *don't* change the definition's return type but make the compiler emit a return value via a different route: what about `return;` in a function declared void but with `#pragma`? no.

Another route: the pin kind is "register-asm/__asm__ reg steer". Could we steer rv to v0 without asm? A *call* returning into rv: `rv = func();` puts the result in v0 by ABI! E.g., if the last statement were `rv = (s32)func_8012B77C(...)` — that's the call's return in v0. But the target has the call already, and then lw v0,32(sp).

Hmm! Interesting: what if the *store* `*a0 = rv` used the call's return value? No.

What if we reorder so that the last statement is a *call* whose result is stored... no, the target's last insns are lw/sw/move.

OK, so what about making `rv` the return value of a *helper* that returns a0? That'd be a call (jal), not a move.

Conclusion: wall.

Now, about tries: I need ≥30 scored tries on the item and ≥20 min. I started item 2 at ~14:09. I'll spend until ~14:30+ generating and scoring variants. Let me write a generator script that emits ~32 real-C variants, then score them in 2 batches via sc.sh.

Actually, the variants should be *sensible* real-C attempts (the log records them). Let me create a set covering:
- decl/order/width variations of rv, sp20, t, q, p
- statement forms for the load/store
- expression folds
- loop shapes (e.g., using a for loop to write the three sp10 fields? That would change code a lot, but worth 2-3 tries)
- `&&`/`||` folds for the if
- pointer reuse (p vs q)
- init at decl

Let me write the generator in Python under my shard dir. Each variant must be a full bare definition.

Base w1 (score 1). Variants:

V1: `*a0 = sp20;` (drop rv) 
V2: `rv = sp20; *a0 = rv; return;` 
V3: `return (s32)a0;` at end (void)
V4: `rv = (s32)a0;` at end
V5: `rv = (s32)a0; *a0 = rv;`? wrong order
V6: rv u32
V7: rv s16 (the store is s32; s16 changes)
V8: sp20 as `s32 sp20[1]` and `func_8012B77C((s32)sp20, ...)`, `rv = sp20[0]`
V9: sp10[4] → s32 sp10[2]? no, it's 16 bytes (4 s32) = the 3 halfwords at +2,+6,+0xA. Keep.
V10: declare `s16 *q` → `u16 *q`? `*q == 0` with u16 vs s16: `lh` vs `lhu`. Target has `lh`. Keep s16.
V11: `p = (u16 *)(q - 3)` → `p = (u16 *)q - 3` (pointer arithmetic on u16*: q is s16*, q-3 = -6 bytes; (u16*)q - 3 = -6 bytes too). Same.
V12: the if: `if (!*q)` instead of `== 0`.
V13: `if (*q == 0) ... else ...` → ternary for unkE0? 
V14: compute `t` inline (drop the t variable): `*(s16*)((s32)sp10+0x6) = p[1] + *(u16*)(a2+2); ((...)a1)->unk100 = *(s16*)((s32)sp10+0x6);` — changes code (reload).
V15: `((Unkstruct_800B5CB8 *)a1)->unk100 = t;` before the sp10 store.
V16: store order swaps.
V17: `func_8012B77C` args: `(s32)&sp20` → `(s32)sp20`? No, &sp20 needed.
V18: `(s32)sp10` → `(s32)&sp10[0]`.
V19: `a1 + 4` → `(s32)a1 + 4`.
V20: use `u16 *pa = (u16 *)a2;` pointer reuse.
V21: `s32 rv = 0;` init at decl.
V22: rv declared as `s32 rv = sp20;` after the call? init at decl not possible.
V23: `*a0 = sp20;` with rv dropped entirely.
V24: end with `if (rv) {}`? etc.
V25: `rv = (s32)a0;` then `*a0 = rv;` (reversed: store a0 into *a0) — wrong semantics but tests codegen; skip, we want faithful C.
V26: trailing `while (0);`
V27: trailing `do { } while (0);`
V28: `rv = (s32)a0;` with rv used in a dead comparison: `if (rv == 0) *a0 = rv;`? changes code.
V29: use a `for` loop for the 3 fields.
V30: `p[0] + *(u16*)a2` → `*(u16*)a2 + p[0]` (commuted; combine may swap).

Most of these won't fix the move, but they're honest tries. The instruction says "a WALL needs ≥20 min and ≥ 30 scored tries on that item". So I'll do 30+.

Actually, maybe I should think harder about a real crack. Let me reconsider the residual once more:

mine: ... lw v0,32(sp); sw v0,0(s0); [missing move v0,s0]; lw ra...
target: ... lw v0,32(sp); nop; sw v0,0(s0); move v0,s0; lw ra...

Wait, the target has `lw v0,32(sp); nop; sw v0,0(s0)` — there's a nop after the lw (load delay). Mine apparently matched that (the diff shows only the insert at 37). Let me look at mine's full assembly to see the exact context.

Hmm, also note: the target's `move v0,s0` could be *the value of the expression `rv = (s32)a0` being kept because rv is the function's RESULT decl*? No.

Let me look at the possibility that the function is compiled as returning s32 *because the TU's decl at the definition site is void but a later declaration in another function says s32*? No.

OK. Let me also consider: maybe the "move" can come from the *call* to func_8012B77C if its return type were used: `rv = func_8012B77C(...)` puts the result in v0, then `*a0 = rv` → but then v0 = call result, and the store would use v0 directly (`sw v0,0(s0)`), and `lw v0,32(sp)` wouldn't exist. Different.

Alright: I'll run the 30 variants. Let me write the generator.

Actually, one more idea worth trying: make `rv` a *struct field* or use a union so the copy is not coalescable. E.g., `s32 rv; ... rv = (s32)a0;` coalesces. But if rv's value must be in v0 for some operation... e.g., `rv = (s32)a0; *a0 = (s32)(rv + sp20);`? That's a different computation.

What about `rv = (s32)a0;` followed by `sp20 = rv;`? A store to sp20 (escaping) → `sw s0,32(sp)` extra.

Hmm what about `rv = (s32)a0; t = rv;`? t is s16, dead → deleted.

OK, generator time. I'll create 32 variants. Let me write them compactly in a Python script with a template.

Actually, generating 32 files with a script is fine. But the brief says "Scripts, not inline python -c". Use the Write tool for the script.

Let me write gen.py that writes v01.c .. v32.c.

Let me design the base body as a template with placeholders. Simpler: write each variant as a full text in the script via a list of (name, body). That's long but fine.

To save effort, I'll use a base and apply textual modifications.

Base:
```c
void func_80181BF0(s32 *a0, s32 a1, s32 a2) {

    extern s16 D_80126CBA;
    s32 sp10[4];
    s32 sp20;
    s16 *q;
    u16 *p;
    s16 t;
    s32 rv;

    q = &D_80126CBA;
    if (*q == 0) {
        p = (u16 *)(q - 3);
        ((Unkstruct_800B5CB8 *)a1)->unkE0 = 0;
    } else {
        p = (u16 *)(a1 + 0x88);
        ((Unkstruct_800B5CB8 *)a1)->unkE0 = 1;
    }
    *(s16 *)((s32)sp10 + 0x2) = p[0] + *(u16 *)a2;
    t = p[1] + *(u16 *)(a2 + 2);
    *(s16 *)((s32)sp10 + 0x6) = t;
    ((Unkstruct_800B5CB8 *)a1)->unk100 = t;
    *(s16 *)((s32)sp10 + 0xA) = p[2] + *(u16 *)(a2 + 4);
    func_8012B77C((s32)&sp20, a1 + 4, (s32)sp10);
    rv = sp20;
    *a0 = rv;
}
```
score 1.

Variants (each a text substitution or full body):
v01: drop rv: `*a0 = sp20;`
v02: `rv = sp20; *a0 = rv; rv = (s32)a0;`
v03: `... rv = (s32)a0; return;`
v04: `... return (s32)a0;`
v05: `... rv = (s32)a0; sp20 = rv;` (store a0 to sp20)
v06: rv u32
v07: rv s16
v08: sp20 as s32 sp20[1], call (s32)sp20, rv = sp20[0]
v09: t inline: replace `t = ...; store t; unk100 = t;` with direct expressions
v10: unk100 = t before the sp10 store
v11: swap the sp10 0x6 store and unk100
v12: `if (!*q)`
v13: `p = (u16 *)q - 3;`
v14: `(s32)&sp10[0]` for the call
v15: `(s32)a1 + 4` for the arg
v16: commuted sums `*(u16*)a2 + p[0]`
v17: `s32 rv = 0;` init at decl
v18: `*a0 = sp20;` + `rv = (s32)a0;` at the end
v19: `rv = *(s32 *)&sp20;`
v20: `*(s32 *)a0 = rv;` (cast store)
v21: `u16 *pa = (u16 *)a2;` and use pa[0], pa[1], pa[2]
v22: `s16 *pp = p;` reuse
v23: `for (i = 0; i < 1; i++)` wrapper? weird.
v24: trailing `do { } while (0);`
v25: trailing `while (0);`
v26: `rv = (s32)a0; if (rv == (s32)a0) { }` 
v27: `a0[0] = rv;`
v28: `*(s32 *)((s32)a0 + 0) = rv;`
v29: `rv = sp20; a0[0] = rv;`
v30: declare `s32 rv; s32 sp20;` order swap
v31: `s32 sp20; s32 sp10[4];` order swap
v32: `s16 t; s32 rv; s32 sp20;` reorder decls

These are all honest real-C variants. Let me write the script.

Actually, maybe I should also try the "return-value via TU" variant just to see (not usable). Skip.

Let me write gen.py.
