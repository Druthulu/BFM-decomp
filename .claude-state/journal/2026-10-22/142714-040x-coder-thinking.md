---
ts: 2026-10-22T20:27:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16b
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_MPDWHmc0UcrBtjWIOLQG
---
Confirmed: per-load lui. So direct symbol reads don't create a base.

Therefore the target's single base means the source address was in a *register* held across the loads — i.e., the C had a pointer variable whose value cse couldn't fold. Since cse folds constants, the only way is that the pointer is not a compile-time constant.

Unless... the movstr route (c_struct) DOES give one base — because the movstr needs a base. And there the dest also gets a base. Hmm.

But wait: what if the source is a movstr (giving the one-base source) and the dest stores are scalar (constant offsets) — is that possible? The movstr writes via its dest address; if the dest is a local array at a known frame offset, the stores are direct. In c_struct's output, the dest stores ARE direct sp offsets. So the movstr's dest address pseudo was only needed for... the base register r80 that cse created for fp+16.

Hmm, r80 = fp+16 with a single set, used in `set a1, r80` three times (the calls). So the movstr dest didn't need a pseudo (stores are constant). cse created r80 for the *call args* — 3 uses of the constant fp+16 as a value. Why? cse's constant substitution for a register-valued use: `set a1, (const fp+16)` would be a `addiu a1,sp,16` — cheap. cse chose to create a base register because the constant is used 3 times (cse's `cse_insn` does create a register when a constant is used more than once and it's a "cheap" address? It has the `do_not_record` / `n_uses` heuristic).

But in score-0 the same 3 uses got folded as constants into a1! The difference must be the *form* of the constant: in score-0 the call arg was `(void *)m` where m is an `int[8]` array → the address expression is `(plus fp 16)` directly. In c_struct, the call arg is the same `(void *)m`! Both identical C for the calls. So the difference is upstream: in c_struct, the movstr RTL contains a pseudo for the dest address (maybe `(mem:BLK (reg 80))`), and cse then sees the constant fp+16 already materialized in a register at insn 21, and reuses it for the calls. In score-0, no such pseudo exists, so cse folds the constant into a1.

So: the movstr's dest address pseudo is what creates r80. cse equates it with the call-arg constant and reuses it. To break that, the movstr's dest address must be a *different* value than fp+16 — e.g., if m were at fp+16 but the movstr dest were expressed as a pointer variable with a different pseudo... cse would still equate.

Alternatively: make the movstr's dest a pseudo that is *not* a constant (opaque). Can't.

Alternatively: make the calls use a *different* address expression that cse can't equate: e.g., the calls take `(void *)(m + 0)` → same. 

What if m is declared as a 2-element array of Mat32 and the copy goes to m[0] but calls pass m[0]? Same.

Hmm. What if the copy dest is m but the calls pass `(void *)(&m[0] + 0)`? identity.

What if the calls pass `(void *)(int)m`? Same value, maybe a different RTL form? `(void *)(int)m` where m is an array → pointer to int → int → pointer. Identity-ish. Probably folded.

OK, what if the movstr's dest address is a pseudo that cse can't reuse because it's *set twice*? In score-0 the address had no pseudo. In c_struct r80 is single-set.

Idea: make the copy use a pointer variable `dp = (Mat32 *)m;` where dp is set *before* the copy, and the calls use m. Then cse: dp is a single-set pseudo with constant value fp+16; the movstr uses dp as dest → stores via (mem (reg dp)); cse then substitutes dp's constant into the stores (making them direct fp offsets) and also into the call args → folding to a1 like score-0! Wait, that's c_d3 which scored 19. Hmm, c_d3 is `Mat32 *d = (Mat32 *)m; *d = D_800AE620;` and calls `(void *)m`. It scored 19, so cse created r80 anyway.

Why? Because the movstr's dest is `(mem:BLK (reg d))` and the loads/stores generated use d as a base; cse's `make_regs_eqv` or constant substitution then has d's constant in the table and creates a base... Ugh.

Let me test whether the difference is cse1 vs cse2. In score-0 the address got folded (constant) into a1; in c_struct a pseudo was created. The movstr generates stores at expand time (before cse1), so cse1 sees them. In score-0 the scalar stores also exist before cse1. So both have fp+16 stores before cse1. The difference: in c_struct the *source* is a mem:BLK movstr and the dest address maybe an explicit pseudo (expand_block_move uses `(mem:BLK (reg))`? If the dest is a pseudo, cse records it).

Hmm, and cse1's handling: it sees `(set (reg 80) (plus fp 16))` at insn 21 (from expand's movstr dest address) and then sees the call-arg `set a1, (plus fp 16)`; cse replaces the call-arg with reg 80 (equivalence). That's the mechanism.

So if the movstr's dest address pseudo were created *after* the call args... impossible.

Alternative: prevent cse from creating the dest pseudo by making the movstr dest address a *hard register*? e.g., copy into m via a pointer pinned to a hard reg? A pin is a lever — but wait, the kinds row is only "launder". Pins "under other causes may stay, never added". So I can't ADD a pin (never added). Hmm: "levers of other kinds the def already had (pins under other causes) may stay, never added". So no new pin.

OK so what real C gives: (a) source base in a register, (b) no dest pseudo for the calls, (c) scalar stores?

Maybe the target's source isn't a movstr; maybe the source pointer is held in a register because the C *loads the address through a pointer that the compiler keeps* — e.g. `src` is a **function-local static**? No.

Hmm, what about a *volatile* global? No.

What about the global being declared as a struct and accessed via a local pointer *parameter*? no.

What if the copy source is an *array of ints* and the loop is unrolled by the compiler with a biv? Target has constant offsets, so unrolled.

Wait wait. Let me re-read the target: 
```
lui a1,0x0
addiu a1,a1,0
lw v0,0(a1)
lw v1,4(a1)
lw a0,8(a1)
sw v0,16(sp)
...
```
This is EXACTLY what gcc 2.7.2 emits for `*(Mat32 *)m = D_800AE620;` (movstr/block move). And score-0 (with levers) produces the same output. The prior coder found c_struct = same output except the s1 address pseudo. So the target source IS the movstr form (or the levers reproduce it).

Given the score-0 body with levers produces the target exactly, the levers are compensating for exactly this. The launder on `src` prevents cse from folding src into the loads; with the pin $5, src is a1. So the target could equally be the scalar form + a way to keep src in a register.

Since a *pin* is an existing lever (not allowed to add), but... wait! The kinds file says only "launder". The def ALREADY has pins $16 and $5. "levers of other kinds the def already had (pins under other causes) may stay, never added" — the $5 pin is already in the def and can stay! So I can keep the $5 pin and the $16 pin; I only must remove the launder. The question is how to remove the launder's *effect* (cse folding) with real C.

The launder forces `src` to be a real register value that cse can't replace. With the pin, src is $5=a1. Removing the launder: cse sees `src` = constant &D_800AE620 and substitutes it into each load.

What if the source pointer is *read from memory*: e.g., `src = *(int **)something`? There's no such thing.

What if the copy is written so that cse cannot fold because the loads are through a *different* pointer whose value is a parameter of an inline... no.

Hmm, but here's a thought: cse folds a constant into an insn only if the constant is "cheaper" or the register is not needed. There's a known trick: use the address in a comparison or arithmetic that forces a register. E.g., `src = (int *)&D_800AE620; ... if (src) ...`? cse would fold the comparison away.

What if we make the source pointer an argument to a call? no.

Alternatively, use the pin to hold the *destination* m address? No new pins.

Let's reconsider the movstr route but with the *dest address pseudo* not created: use `Mat32 m;` and copy with `m = D_800AE620;` — c_d4 = 19 (same). 

What if the copy is `*(Mat32 *)&m = D_800AE620;`? same.

What if the destination is not an array but a *struct member of a local struct with a flexible offset*: e.g. `struct { int a[8]; } s; *(Mat32 *)s.a = D_800AE620;` — the address is fp+16 anyway.

What if m is placed at a *non-constant* offset? Impossible for locals.

Hmm, what if we pass `(void *)m` to the calls but the copy destination is a *union member* that cse treats as a different address object (e.g., a union with two members: one Mat32 and one int[8], and the copy uses the int array cast, the calls use the Mat32 member)? Both have the same address → cse equates.

What if the call argument is `m` but m is a *pointer* to a local array: `int buf[8]; int *m = buf;` then the copy `*(Mat32 *)buf = ...` and calls `(void *)m`? cse equates m and &buf.

The key is cse's equivalence: any two expressions with the same value get merged. The only way to break it is to have the same value produced by *different RTL* that cse can't equate (e.g., one via a hard reg, one via a constant). Since a pin on the *destination* would do it (pinned hard reg not equivalent to the constant)... but no new pins.

Hold on — is a pin on m's address an "added lever"? The constraint says pins "may stay, never added". So no.

What about `register int *mp __asm__("$X")` — no.

Hmm, so is this item actually a WALL? The prior coder spent 28 min and 40 tries. The residual mechanism is clear: cse merges the movstr dest address pseudo with the call-arg constant, and local-alloc gives it s1 (single set), whereas the target keeps the call arg as a folded constant (addiu per call) and no extra callee-saved reg. That's the `cse-const-addr` wall tag family (cse folds/substitutes a constant address the target keeps base-relative) — but here it's the inverse: cse creates a base register where the target rematerializes.

Wall tag: maybe `cse-const-addr` or a new one like `lreg-addr-base-reg`. Evidence: alloc table: r80 (fp+16) single-set, local-alloc s1; score-0 body has no address pseudo (a1 folded per call).

Before walling, a couple more ideas that are cheap:

Idea A: make the address pseudo's value NOT a plain constant by using an array with a runtime length? no.

Idea B: make the calls' argument come from a *struct copy* of m into another local? no.

Idea C: reorder: do the calls BEFORE the copy? No, semantics.

Idea D: Do the copy AFTER the calls? Semantics change (RotMatrix modifies m). No.

Idea E: Use `m` as a `Mat32` and pass `(void *)&m` but make the copy `m = D_800AE620;` — 19.

Idea F: What if the copy is `*(Mat32 *)m = D_800AE620;` and the calls are made with a *pointer to the first element* computed via a real second set: `int *mp; mp = m; mp += 0;`? cse kills += 0.

Idea G: `mp = m; mp = (int *)((char *)mp + (t0 - t0));` — identity arithmetic, disallowed/optimized.

Idea H: make the call-arg expression involve a *different object* with the same address, like a union: `union { int a[8]; Mat32 m; } u;` copy to u.m, calls with u.a. c_d5 = 19.

Idea I: What if the three calls take *different* address expressions that cse folds differently: e.g. RotMatrixX(..., (void *)(m)), RotMatrixZ(..., (void *)(m+0)), ... all same.

Idea J: Make the movstr dest address be m+4? i.e., copy into m shifted: no, changes layout.

Idea K: Copy with two 16-byte block moves from two halves, dest m and m+4: two dest pseudos (fp+16, fp+32); cse creates bases for both? The call args (fp+16) would merge with the first → same problem.

Idea L: What if the copy is done as 8 scalar stores *after* the call-arg address is materialized (i.e., the calls' address expression appears before the copy in the source)? The order matters: the target's copy comes first. If I write:
```
mp = m;              // set a1/addr pseudo before the copy
*(Mat32 *)m = D_800AE620;
RotMatrixX(..., mp);
```
cse might fold mp... Actually v7 was similar (`mp = m; copy; mp = m;`) = 19.

Idea M: Let the calls use the *pinned $5 source register* after the copy! Since $5 is a pin that already exists, and the source address is dead after the copy, the C could reuse `src` for the destination: `src = (int *)m;` (a real second set of src, which is a hard reg!). Then the calls pass `(void *)src`, and `src` is a hard register ($5=a1), not a pseudo → no allocno, no s1! And the movstr dest is m (fp+16) with constant stores.

C:
```
src = (int *)&D_800AE620;      // no launder
*(Mat32 *)m = *(Mat32 *)src;   // movstr from src (a1)
src = (int *)m;                // real second set: src = m (hard $5)
RotMatrixX(..., (void *)src);
```
Since src is a hard reg, `set a1, fp+16` per call → addiu a1,sp,16! And the copy: `*(Mat32 *)m = *(Mat32 *)src;` — a struct copy from a pointer → movstr with source base in a1. That could produce exactly the target!

But wait: does the *first* statement `src = (int *)&D_800AE620;` get folded by cse into the copy's source? The movstr's source is `(mem:BLK (reg src))`; cse might substitute the constant → `*(Mat32*)m = *(Mat32*)&D_800AE620` → same as c_struct, source via a symbol base (fine, one lui a1). Either way the source base is a1 (hard reg $5 pinned). Then `src = (int *)m;` is a second set of the hard reg → a1 = fp+16 → the calls use a1. 

This is promising! It uses the existing $5 pin (allowed to stay) and real C (no launder).

But careful: is using the pinned register for a *second* purpose a "launder"? No — it's real C reusing a variable. And the $5 pin is pre-existing, not added.

Let me also consider that the movstr with a hard-reg source might force a different pattern. Test it.

Variants:
w1:
```
src = (int *)&D_800AE620;
*(Mat32 *)m = *(Mat32 *)src;
src = (int *)m;
RotMatrixX(..., (void *)src);
```
w2: same but copy `*(Mat32 *)m = D_800AE620;` (source direct symbol).
w3: copy via t0..t2 scalar from src (like src body without launder) then `src = (int *)m` — scalar loads from src (pinned) might not fold because src is a hard reg? n1 showed folding happened even with the pin... because cse substituted the constant value into the loads, ignoring the hard reg. Hmm, n1's loads were `lui v0; lw v0,12(v0)` — cse replaced src with the constant. So the pin doesn't stop folding for scalar loads. But for a *movstr* (mem:BLK), cse doesn't split the base, so the source stays as a base reg.

So w1/w2 (movstr) + `src = (int *)m` for the calls.

Note: if cse substitutes src's constant in the movstr source, the source base is a symbol pseudo (like c_struct's a1). Fine — target has a1.

Then the calls: `set a1, (reg src)` where src is hard $5... cse sees src's value = fp+16 (constant) and may fold the constant into a1 → `addiu a1,sp,16`. Either way a1, not a pseudo. 

Let me test w1, w2, and also w4: after the copy, `src = m;` written as `src = &m[0];` etc. (same).

Also: after `src = (int *)m;`, the final store `*(Mat32 *)(obj+0x34) = *(Mat32 *)m;` uses m's address for loads — direct fp offsets.

Let me write these.
