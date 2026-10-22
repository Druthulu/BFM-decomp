---
ts: 2026-10-22T12:53:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_zZBrYrpCoRWohEHUMIvA
---
Line 1607: "VAR is a MEM that used to be a pseudo register with mode PROMOTED_MODE." — so in GCC 2.x, REGISTER VARIABLES ARE PSEUDO REGISTERS! Yes: `allocate_variable` for a register decl creates a pseudo reg (`reg` field of the DECL), and `expand_expr` for such a variable returns the pseudo.

So: `register s32 it;` → the variable IS a pseudo register in RTL. Then `it = (s32)D_80120194` → (set (pseudo it) (symbol_ref)). This pseudo has 1 set → cse adds a REG_EQUAL note → the use (plus pseudo const) gets the constant substituted → the same fold!

Hmm. Unless the pseudo has 2 sets.

Hmm, so what made the ORIGINAL produce the unfolded form?

Wait... maybe the original DIDN'T have the fold because in the original, the address was NOT a constant! What if the original source was:

```c
it = (s32)D_80120194;
```
where `D_80120194` was declared as `extern u8 D_80120194[];` — hmm.

Hmm hold on, what about `&D_80120194` where the symbol is in a *different section* requiring a longer address sequence? No.

**KEY IDEA**: What if the original code loaded the address from a global POINTER variable? Like:

```c
extern u8 *D_80120194_ptr;
it = (s32)D_80120194_ptr;
```
Then the target would show a `lw` — it doesn't.

**ANOTHER KEY IDEA**: What if the target's `lui v1; addiu v1` pair comes from the *loop* pseudo needing a register, and the base &D_80120194 is folded into the SAME lui/addiu? Look at the target:

```
4178: lui v1, hi(D_80120194)
417c: addiu v1,v1,lo(D_80120194)
```
This is a plain materialization of D_80120194 (no addend). If the base had been folded, we'd see the addend in the addiu.

So in the target, the base pseudo holds the address in a REGISTER.

**What if the original source had `it` used in a MEM?** e.g. `*(u16*)it` — the base of a MEM can't be a constant... wait, it CAN (a constant address MEM). But if `it` is a pseudo holding the address, using it as a MEM base gives `lhu v0, 0(v1)` — the base must be a register (the address of a MEM with a constant offset can also be a constant address, and GCC folds that too).

Hmm! But actually: a MEM with a *register* base and a 0 offset vs a constant address: GCC prefers the register form when the base is already in a register (no extra lui/addiu). So if the base pseudo is in a reg (because it was forced), the lhu uses it.

**AH WAIT!!!** Here's the thing! What if the ORIGINAL source was:

```c
it = (s32)D_80120194;
p = it + 0x658C;
```
and the compiler was GCC 2.7.2 but the FOLD happened at a later stage than I think, and the reason the target has the base in a reg is that the *base pseudo* was ALSO used as a MEM base somewhere... no.

Hmm, hold on. Let me look at the target's C750 (the sibling with base used 3 times) to see the pattern there — it'll confirm the "uses" theory. Let me dump C750's target.

Actually, let me instead test the "2 uses" hypothesis directly in C2D0: modify the source so the base is used twice in a semantically-neutral way? We can't.

Hmm, hmm. Let me think about the ORIGINAL source differently. What if the original was:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
zero:
    return 0;
}
```

Hmm what if the original had `p` as a POINTER and `it` as a pointer, and the comparison `it == p` compared pointers... same.

**COMPLETELY DIFFERENT IDEA**: What if the original source declared the variables in a different ORDER or used different types such that the base's pseudo is a *pointer* whose value is loaded via `expand_expr` from an ADDR_EXPR that is NOT folded because the symbol is a `u8[]` (incomplete type) and the code takes `&D_80120194` — hmm.

Let me try the EXPERIMENT route: check what happens if the base variable is declared `register s32 it;` (a pseudo in RTL). Maybe GCC's cse REG_EQUAL note is only added for MEM-based loads, not for pseudo sets! Look at the cse code: the REG_EQUAL note is added when "n_sets == 1 && src_const && GET_CODE (dest) == REG && GET_CODE (src_const) != REG". This applies to a pseudo set to a constant too. Hmm, but then `equiv_constant` returns the constant for that pseudo → the fold.

BUT: the REG_EQUAL note is what the *register allocator* uses to substitute the constant at the use (in `reload`/`regmove`?). Hmm, equiv_constant is used in cse to replace operands during cse itself.

Honestly, EXPERIMENT: try `register s32 it;` — but wait, that's a "register var" which the constraints forbid adding? Hmm: "no `register` vars, no `__asm__`" — I'd rather not.

BUT hold on! What about the existing `register int obj __asm__("$16")` in item 1 (8012B4B8)? That's a pin.

Hmm, let me re-read the constraint text once more: "CONSTRAINTS: MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added; write only under .run/... ; no make, no git, no commit; no signature or decl change outside the body (callers stay as they are); no `register` vars, no `__asm__`; `do{}while(0)` only with `// !FAKE: do-while`; ..."

Hmm, "no `register` vars, no `__asm__`" in a list of constraints on the body I write. But the def already has `register int obj __asm__("$16")` in item 1 — for item 1, the launder is the `__asm__("" : "=r"(src) : "0"(src))` line, and the pins stay (allowed by the earlier clause). But if I keep the pin, I'd violate "no register vars, no __asm__" literally...

I think the intent is: the NEW body must not introduce levers (register/asm) — the existing pins are allowed to stay (explicitly stated). Since the row kind is only "launder", I keep the pins.

Hmm, but for item 2 (C2D0) there are no pins; the only levers are the 2 launders. If I add a `register` variable, that's adding a pin-ish lever → not allowed. So I need a non-register, non-asm solution.

OK so let me think about what else could force the address into a register.

**IDEA: use the address TWICE in a way that is value-preserving but not dead.** For instance, the source could compute p in two steps:
```c
it = (s32)D_80120194;
p = it + 0x658C;
```
What if instead:
```c
it = (s32)D_80120194;
p = it;
p += 0x658C;
```
Then `it` is used once (p = it) and p has 2 sets. The fold: p = it (a copy) then p += const. The copy `p = it` — cse would make p equivalent to it → the constant → fold again probably.

**IDEA: make the base's value escape into a comparison.** Hmm.

**IDEA: What if the ORDER of the two address materializations matters?** In the target, the base &D_80120194 is materialized FIRST (at the function entry, before the jump to test). And &D_801202A0 is materialized at 4190 (in the test block). This ordering is natural.

**IDEA: What if the original source used a DIFFERENT variable for the base that is also used in the `copy:` block?**

Hmm, let me look at the loop again:
```
copy:  return it;      /* it = the found entry */
```
Wait, actually, hmm! What if the original source was:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    ...
```
where `it` in `copy: return it;` refers to the ORIGINAL base value (i.e., the source's `it` was NOT reassigned at test; instead a different variable was used for the loop)? But the target's copy block returns v1 = the loop pointer.

Hmm, hold on! Let me re-examine. Is v1 at 418c really the loop pointer? At 418c we have `move v0,v1`. The predecessors of 4188 (the j) are 41a8 (beqz v0 → 4188). At 41a8, v1 = the current pointer (the one just loaded: `lhu v0,0(v1)`). So yes, v1 = the loop pointer at that point.

But hmm, what if the register allocator assigned v1 to the *base* pseudo and the loop pointer is in a different reg? Look: at 41a0 `lhu v0,0(v1)` — the loop pointer is v1. And 41b0 `addiu v1,v1,268` — the loop pointer is v1. So the loop pointer is v1. And at 418c, `move v0,v1` = the loop pointer. OK.

So the base pseudo (&D_80120194) is ALSO v1 (at 4178-4184). Two different pseudos sharing v1 (non-overlapping live ranges). And the base's single use is the addiu.

Hmm, so GCC allocated a pseudo to v1 ($23, a callee-saved reg) even though its live range is 2 instructions. That's odd for a single-use pseudo — unless the pseudo was FORCED into a register (e.g. by the asm, or because it was a "hard reg" pseudo).

**AH, THAT'S IT!** In the target, maybe the base pseudo IS a hard-reg pseudo! Look at item 1 (8012B4B8): `register int *src __asm__("$5")` — a pin. And in C2D0 there's no pin... but the target uses v1 = $23 for the base. Hmm, $23 is a callee-saved reg, unusual for a short-lived value.

Hmm, but wait: in the target, the base and the loop pointer share v1. If the base were a hard-reg pseudo ($23), then the loop pointer would also be $23 (they'd conflict? no, the hard-reg pseudo reserves $23 for the whole function!). Hmm, in the target the loop pointer is also v1 — consistent with a hard-reg pin on $23 for the loop pointer!

Interesting!! What if the ORIGINAL source had `register s32 it __asm__("$23")`? Hmm, but that's a pin (asm) — not allowed for us.

Hmm, but hold on: the base is used once and lives 2 instructions; GCC would put it in a caller-saved reg (a0) if it were a normal pseudo. The target has it in v1 (callee-saved). That's evidence for a hard-reg pin on $23 in the original source!

And in C750, the base (used 3 times, long live range) → global-alloc → callee-saved reg v1. That's the same $23! So in C750, the base got $23 by global-alloc (long live range → callee-saved). And in C2D0 the base got $23 too — but a 2-instruction live range would normally get a caller-saved reg.

So the ORIGINAL C2D0 source probably had the base pinned to $23! Hmm, but that's an asm pin → not allowed for our MATCH.

Hmm, wait. But then the current source (with the launder) reproduces the target exactly (score 0), and the launder (not a pin) is enough to get $23. Because the launder's copy pseudo is a REG that... hmm, why would it get $23?

Hmm, let's think: the launder creates a copy pseudo of the address. The copy pseudo's value is a REG (the address pseudo). At the RTL level: pseudo_addr = symbol_ref; pseudo_copy = pseudo_addr (a copy). cse: the copy pseudo has 1 set (from pseudo_addr) → qty_const? pseudo_addr's qty_const = symbol_ref (a constant) → so the copy's value is also known → equiv_constant(copy) = symbol_ref → fold again?! But it didn't fold (the target has the base in a reg).

Hmm, because the asm is volatile and its output can't be substituted (the asm's output is used as an input to the asm itself... the "0" constraint ties it). The asm's operands are not substituted by cse (asm operands are opaque). So the copy pseudo's value is unknown to cse (it's defined by the asm) → not foldable → it stays a REG → and `p = it + 0x658C` uses it → the copy pseudo is in a reg.

Then global-alloc: the copy pseudo (live 4178-4184) — hmm, but it got $23.

Hmm, and where did the `lui v1; addiu v1` come from? The asm's INPUT operand is `it` (the value before the asm) — the address pseudo → reload materializes the constant into a register → lui/addiu into whatever reg the input pseudo gets.

OK. So the mechanism is clear: the asm makes the value opaque, so cse can't fold, and the constant must be materialized in a register.

Now, in plain C, how can we make GCC treat the address as opaque (unknown value) so it can't fold? Options:
(a) The address comes from memory (a load) → but then the target would have a load instruction. Unless the load is folded... no, a load is an instruction.
(b) The value is modified by an operation whose result GCC can't see: e.g. `it = it + 0;`? GCC folds that (and it's an identity launder anyway).
(c) The value passes through a function call: `it = identity((s32)D_80120194);` — an extra call instruction. No.
(d) The value is in a struct in memory: `it = s->field;` → a load. No.

Hmm, so how did the ORIGINAL get it? The original probably had a PIN (register asm) — but the original is the ROM's code, compiled from the game's source, which certainly didn't have `register __asm__` (that's a GCC extension the decompiler added). The game's original source was plain C!

So the game's plain C produced this code. Which means: in the game's source, the base address was NOT a compile-time constant!!!

Hmm! How can &D_80120194 not be a constant? ... It IS a constant in any C program.

UNLESS the game's source did something like:

```c
it = (s32)(u8 *)D_80120194;
```
no.

Hmm, but wait: maybe the game's compiler (gcc 2.7.2 for PSX, or maybe a different compiler/flags) did NOT fold this. Maybe the fold we see is due to the *flags* used by our pipeline (-O2 -G0 etc.) or the -fno-builtin etc.

Hmm, actually here's a thought: maybe the fold is due to `combine` or `jump` and the original had slightly different code.

OK, let me look at this from the "what can I control" angle. What if the base value is used in a context where GCC MUST keep it in a register: **as the base of a MEM with a non-constant offset**? Not available.

**What if the base value is compared with something?** E.g., `if (it == p)` — hmm! What if the source had a comparison involving the base?

Hmm, hold on! What about the second symbol D_801202A0? In the target it's materialized in v1 (a reg) and used as a MEM base (lhu v0,0(v1)) and in the beq. Its materialization is plain (lui/addiu, no addend) because it's a MEM base — a MEM with a constant address would be `lhu v0, D_801202A0` — but the target has `lhu v0,0(v1)`. So GCC chose the register form for the MEM base. That means the pseudo for D_801202A0 was NOT folded into a constant address... but it was materialized with lui/addiu (that's the constant materialization!). So the pseudo holds the constant &D_801202A0 in a register, and the MEM uses (reg + 0).

Interesting: so for the second symbol, GCC did NOT fold the constant into the MEM address. Why? Because the pseudo's value is used in TWO places (the MEM and the beq) → so it needs a register → and the MEM base is the register.

And for the first symbol, used ONCE (in a plus), GCC folded it.

So the difference is the number of uses! For the second symbol: 2 uses → reg. For the first: 1 use → folded.

So the ORIGINAL source must have used the base &D_80120194 at least TWICE! And the second use must be value-preserving.

Where could a second use of the base hide? Options:
- `p = it + 0x658C` and the loop bound compared against the base? The target's loop compares `it != p` where p = base + 0x658C. Hmm.
- What if the original computed p as `it + 0x658C` where `it` is the base AND the copy block returned the base? No (we established it returns the loop pointer).

Hmm! Wait. What if the original source was:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
```
and ALSO the loop's start was `it = (s32)D_801202A0` — hmm.

What if the ORIGINAL source expressed the loop as:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    it += 0x10C;       /* it = D_801202A0 */
    goto test;
test:
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
```
Then the base &D_80120194 has 2 uses: `p = it + 0x658C` and `it += 0x10C` (the second set of `it`). In RTL: pseudo_base = symbol_ref (1 set) → the second use reads the pseudo...

Hmm, but here's the thing: with 2 uses, cse's REG_EQUAL note is still added (n_sets == 1 for the pseudo), but the *use count* matters for reload: reload's decision to rematerialize a constant into a register vs. substitute at the use. In reload.c, there's a heuristic: if the pseudo is used more than once, keep it in a register.

BUT: the second use here (`it += 0x10C` → `plus(pseudo_base, 268)`) — if the base were substituted by the constant at that use, we'd get a constant address (symbol_ref + 0x10C) = D_801202A0 — and then the second materialization `lui v1; addiu v1` for D_801202A0 would be a *folded* constant address (with addend 0x10C) → `lui v1, hi(D_80120194); addiu v1,v1,0x10C` — but the target shows `lui v1, hi(D_801202A0); addiu v1,v1,lo(D_801202A0)` — the reloc is on D_801202A0, not D_80120194! So the second materialization is of the D_801202A0 symbol. So the original source DID assign D_801202A0 directly.

OK so the original had `it = (s32)D_801202A0` (a separate constant) AND the base used twice?

Hmm, what if the original was:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    if (it == p) goto zero;
```
and the base's second use is in `copy: return it;`?!?! Wait — what if in the ORIGINAL, the `copy:` block returned the BASE (not the loop pointer)?? Let's check the target again very carefully:

```
4188: j 41bc        <- the "copy" block: return it
418c: move v0,v1
```
The predecessors of 4188: 41a8 (beqz v0,4188) — the branch from the loop body when *it == 0.

At that moment, v1 = the pointer being tested. So `move v0,v1` returns the tested pointer.

Hmm, so it returns the loop pointer. But hmm — what if the source's `copy: return it;` returned the base because the source had TWO variables: `base` and `it`? Then the source would be:

```c
    base = (s32)D_80120194;   /* hmm */
    p = base + 0x658C;
    ...
copy:
    return it;    /* the loop pointer */
```
That's what we have; the base is used once.

BUT what if the ORIGINAL source was:
```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    return it;      /* the BASE, because `it` was never reassigned! */
test:
    ...
```
i.e., the loop used a DIFFERENT variable (say `q`), and the copy block returned the base `it`!? Then the base would be live across the whole function → a register → and the target's `move v0,v1` at 418c would return the BASE (&D_80120194)!

Hmm! But then the target's copy block would return &D_80120194, not the found entry. Is that semantically sensible? The function scans for a zero u16 and returns... the base? Hmm, that's plausible for a "find the end of the list" function? Hmm.

But we can't distinguish from the target: `move v0,v1` where v1 could be either the base or the loop pointer, since both are v1!

Hmm!! Wait, but if `copy: return it;` returned the base, then the base's live range spans from 4178 to 418c → spanning blocks → global-alloc → callee-saved $23 = v1! THAT EXPLAINS WHY THE BASE IS IN v1 (a callee-saved reg)!!! A 2-instruction live range would get a caller-saved reg (a0/a1)!

So the ORIGINAL source likely was:

```c
s32 func_8012C2D0(void) {
    s32 p;
    s32 it;      /* the base */
    s32 q;       /* the loop pointer */
    it = (s32)D_80120194;
    p = it + 0x658C;
    goto test;
copy:
    return it;    /* the base! */
test:
    q = (s32)D_801202A0;
    if (q == p) goto zero;
body:
    if (*(u16 *)q == 0) goto copy;
    q += 0x10C;
    if (q != p) goto body;
zero:
    return 0;
}
```

Hmm! But wait: in the target, the loop pointer is ALSO v1. If the base (live across the function) is v1, the loop pointer can't also be v1 (they overlap in live range: the base is live from 4178 to 418c, the loop pointer from 4190 to 418c — they overlap at 418c!). Two overlapping live ranges can't share a register!

Unless the copy block's `move v0,v1` uses the LOOP pointer (live 4190→418c) and the base is dead after 4184. So they don't overlap: base live 4178-4184, loop ptr live 4190-418c. They can share v1. OK.

So if the base were live until 418c (returned at copy), it would overlap with the loop pointer at 418c → they'd need different registers → the target would show two different regs. The target shows only v1 in the copy block. So the base is NOT live at the copy block. => `copy: return it;` returns the LOOP pointer. Confirmed.

So the base is live only 4178-4184 and is in v1 ($23, callee-saved) — for a 2-instruction live range, that's abnormal for a normal pseudo. Global-alloc assigns callee-saved regs to long-lived/global values; a 2-insn value would be local-alloc ($a0-$a3, $t, $v).

Hmm, unless the pseudo was FORCED into $23 by a pin in the original source.

Hmm, BUT: there's another possibility: GCC's local-alloc vs global-alloc. The base pseudo is used in the entry block only, but its live range crosses... hmm.

Wait, actually let me reconsider. Maybe the pseudo is a *global* allocno because it's live across the `goto test` jump? No, it's dead before that.

Hmm, what if the pseudo IS live across blocks in the original: e.g. `it` (the base) is live at `copy:` — no, we ruled that out.

OK, alternative explanation for v1: the *loop pointer* pseudo is a global allocno (live across blocks) → v1 ($23). And the base pseudo is ALSO v1 because... they're not overlapping, and global-alloc can reuse the same reg for non-overlapping globals? Hmm, global-alloc assigns distinct regs to different allocnos even if their live ranges don't overlap (it doesn't do interference-based reuse across allocnos; but it does consider "conflict" — the global allocator computes conflicts via the flow graph; non-overlapping globals don't conflict, so they CAN share a reg).

Hmm, but the base's pseudo — is it a global allocno? If the base pseudo's live range is within one basic block (the entry block), it'd be a local allocno → local-alloc would give it a caller-saved reg (a0/a1/t0). But the target has it in v1.

UNLESS: the base pseudo was merged with the loop pointer pseudo by the register allocator (they don't conflict). local-alloc vs global-alloc: a local allocno (v-class) can't be allocated to a global-allocated reg ($23) — the local allocator uses the "local" reg class ($v0-$v1, $a0-$a3, $t). Hmm, in GCC's local-alloc, the local registers are allocated from the call-saved/hosted set: it prefers $v0/$v1 (the "local" regs) then a0-a3, t0-t9.

But actually: the local allocator in GCC 2.x allocates local allocnos from a set of regs determined by `LOCAL_REGNO`... and it can also allocate from the global regs if they're free? There's a mechanism: local-alloc can use a hard reg assigned to a global allocno if the local's live range doesn't conflict ("hard reg conflict"). Hmm, in GCC 2.x's local-alloc there's `local_alloc` which tries "the reg is not used by any global allocno whose live range overlaps".

So the base pseudo (local) could be allocated $23 if the global $23 (the loop pointer) doesn't conflict in live range. Hmm, but the loop pointer's live range is 4190-418c and the base's is 4178-4184 — they don't overlap, so the local could take $23.

Hmm, plausible! But then in MY compile (folded), the base has no pseudo at all.

OK. Let me now think about what actually can make GCC keep the address in a register in plain C.

Since the fold is cse's equiv_constant substitution (or reload's rematerialization), the fix is to make the pseudo's value non-constant. The pseudo's value is the constant because the ONLY definition is the constant.

**What if the variable is assigned the address in a way that involves a non-constant operation?** E.g.:

```c
it = (s32)D_80120194;
```
The RHS is a constant. What if instead:

```c
it = (s32)(D_80120194 + (0 * something));
```
folded.

**What if the address is computed as `&D_80120194[0]` where the array is accessed through a pointer variable?** no.

**What if the value passes through a struct copy in memory?** → a load.

**What if the value is the result of a comparison or arithmetic with a runtime value?** We have no runtime values in this function... except `param_1` in item 1!

Hmm, in C2D0 there are no runtime values at all. So any "opaque" computation must involve something.

Hmm, what about the *self-modifying* trick: `it = (s32)D_80120194;` where D_80120194 is declared as `extern u8 D_80120194[];` — what if we declare it as `extern volatile u8 D_80120194[];`? Then `&D_80120194[0]` is still a constant address (volatile affects loads, not the address). And changing the extern declaration is a decl change outside the body → not allowed.

OK, so what if we use the ADDRESS of the array in a context that GCC must keep in a register...

**!!! IDEA !!!**: What about `sizeof`? No.

**!!! IDEA 2 !!!**: What about making `it` a *pointer to a pointer*? no.

**!!! IDEA 3 !!!**: What about using a `switch`/`case` with the address? no.

**!!! IDEA 4 !!!**: The KEY realization: maybe we can make the fold impossible by making the *offset* non-constant instead of the base! I.e.:

```c
it = (s32)D_80120194;
p = it + off;    /* off is a runtime value */
```
But the target's offset is the constant 25996. So `off` must be 0x658C at runtime — it could come from a runtime computation! E.g., in C2D0 there are no runtime values... but we could compute 0x658C from something? No, that's absurd.

Hmm, BUT: what if the offset comes from a *load* — no.

**!!! IDEA 5 !!!**: What if the base+offset is expressed as a pointer difference: `p = (s32)((u8 *)D_801202A0 + 0x6480)`? Then GCC folds it to a constant address (D_801202A0 + 0x6480) → lui/addiu with addend 0x6480 → the reloc would be on D_801202A0, but the target's reloc is on D_80120194 → mismatch.

Hmm, unless... hmm! Interesting: what if the target's `lui v1, hi(D_80120194); addiu v1,v1,lo(D_80120194)` is *the folded constant address* of something? No: the target's addiu a0,v1,25996 is a separate instruction, so the base is in a reg.

**!!! IDEA 6 !!!**: What about making the *base* a value that GCC knows is a constant but must keep in a reg because it's used in a MEM with a *variable* offset? Not available.

**!!! IDEA 7 !!!**: What about the "u8/u16 cast" trick: make the base's pseudo hold a SUBREG or a converted value. E.g.:

```c
u32 base = (u32)D_80120194;
```
The cast u32→u32 is a no-op.

What about:
```c
long long it = (long long)D_80120194;   /* 64-bit! */
p = (s32)(it + 0x658C);
```
Ooh, a 64-bit intermediate! In GCC 2.7.2 on MIPS, `long long` is supported (with -mips1? yes, GCC 2.7 supports long long via TImode). The addition in TImode would be a 64-bit add (daddu/addiu + handling). That would generate extra instructions. Not matching.

What about a *float*? `float f = (float)D_80120194;` — no, precision.

**!!! IDEA 8 !!!**: What about the s16/u16 trick applied to the OFFSET? E.g.:

```c
it = (s32)D_80120194;
p = it + (s16)0x658C;    /* 0x658C doesn't fit in s16 */
```
0x658C = 25996 > 32767 → doesn't fit in s16. As u16: 25996 fits! `p = it + (u16)0x658C;` → the u16 value is a constant 25996 → folded.

Hmm, but the HImode trick worked in other cases because the *conversion* (sign/zero extension) is a separate insn that escapes cse's constant folding: e.g. `flag = (s16)1` → the value is a HImode constant → cse's equiv_constant returns a HImode constant → then the use is a zero/sign extension → the extension is an "insn" (sll/andi) rather than a folded constant.

In our case: `p = it + (u16)0x658C` — the u16 constant 25996 is used in an add → the add would be `addiu a0, v1, 25996`?? Hmm! Wait: if the offset is a HImode constant, the add becomes (plus (reg v1) (reg u16const)) → the u16 constant is materialized in a register (as `li t0, 25996` or `ori`) → the add would be `addu a0, v1, t0` → NOT `addiu a0,v1,25996`. Doesn't match.

Hmm. Unless GCC's combine folds (plus reg (const 25996 in HImode)) back into an addiu. Probably it does fold the constant back (combine's simplify_rtx on (plus (reg) (const_int)) → an addiu). Yes, combine would fold it back to addiu. Hmm! But then the base would still be folded by cse...

Hmm, the HImode trick in the other cases worked because the *value* (e.g. flag=1) was compared/tested, not added.

OK, let me step back and consider the "2 uses" approach again, since that's how the sibling C750 works (base used 3 times → reg, no launder needed).

For C2D0, can we express the same computation with the base used twice, in a way that's faithful? What if:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    ...
copy:
    return it;
```
Hmm, `copy: return it;` — the loop pointer.

What if we split into two variables:
```c
    base = (s32)D_80120194;
    p = base + 0x658C;
    ...
```
and use `base` twice: e.g. `if (base == base)`? Silly.

Hmm, what about the LOOP structure: the loop condition `it != p`. What if we wrote the loop bound as the base + offset each time? I.e.:

```c
    base = (s32)D_80120194;
    p = base + 0x658C;
    ...
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
```
p is used twice (the test and the loop) — but p's value is the constant address (folded) → the compare `it != p` would be `bne v1, <const addr>` → the mips backend would materialize the constant address... hmm! In the target, the compare is `bne v1,a0` — p is in a0 (a register).

So in the target, p IS in a register (a0). And p = base + 0x658C where base is in v1.

So both the base AND p are in registers. The base in v1 ($23) and p in a0 ($4).

Hmm! If GCC had folded the base's address into p's computation, p would be the constant address (materialized as lui/addiu) and the compare would be against a0 (the materialized constant) — which is what MY version has (a0 = the folded address, beq a0,v1). Hmm! But in my version the compare is `beq a0,v1` (operands swapped) vs the target's `beq v1,a0`.

Hmm, the operand order! Interesting: in the target, `beq v1,a0` = (it, p) in source order. In mine, `beq a0,v1` = (p, it) — swapped! Why would GCC swap? Because in my version, p is a *constant* (folded) and it is a reg — GCC's `reverse_condition`... hmm, the swap happens in `final.c`/`jump.c` when the operands are commuted for the branch. Actually GCC 2.7's `emit_cmp`/`branch` may swap to put the register operand first? Both are registers here.

Hmm, in the target `beq v1,a0` — v1 is the loop pointer (it) and a0 is p. In mine `beq a0,v1` — a0 is p (the folded constant) and v1 is it. So in mine the operands are (p, it) = the source order is `it == p` → (it, p) = (v1, a0) = `beq v1,a0`... but mine shows `beq a0,v1`! So mine REVERSED the operand order relative to the source, and the target did NOT.

Wait, is that right? Source: `if (it == p) goto zero;` → beq it, p. Target: beq v1,a0 → it=v1, p=a0 ✓ (source order). Mine: beq a0,v1 → p=a0, it=v1 ✗ (reversed).

Why? Because in mine, `it` at that point... hmm, in mine the loop pointer is v1 too. So mine reversed the comparison operands. GCC's `reverse_condition` is applied when the comparison is "reversible" — e.g. `if (a == b)` where the branch is a conditional jump: GCC emits `beq a,b` or `bne a,b`. It doesn't swap operands... but `emit_cmp` with `EQ_EXPR` and the operands (reg, reg) → the branch is emitted as `beq reg1, reg2`.

Hmm, so why the swap? Maybe because in mine, the `it` value at the compare is NOT v1 but something else... Let me re-read my candidate's disassembly:

```
4190: lui v1, hi(D_801202A0)
4194: addiu v1,v1,lo
4198: beq a0,v1,41bc
41a0: lhu v0,0(v1)
```
So at 4198, it = v1 (the loop pointer) and p = a0. The source order is (it, p) = (v1, a0) → `beq v1,a0`. But GCC emitted `beq a0,v1`. So GCC swapped. Why? Because of the "commutative operand canonicalization" in cse/combine: `eq` with two registers — combine canonicalizes the operand order by some criterion (e.g. by register number!). In the target: beq v1,a0 (v1=23, a0=4) — the HIGHER reg number first? In mine: beq a0,v1 (4, 23) — the LOWER first. Inconsistent!

Hmm, so combine's canonicalization order depends on something else. Hmm, whatever.

Anyway: the difference boils down to the base being in a register.

Let me try the "2 uses" experiment: write a candidate where the base is used twice in a value-preserving way, e.g.:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    if (it == (s32)D_80120194) { ... }   /* extra compare - changes code */
```
No good.

Hmm, what about using the base in a way that's dead but counted as a use? Like:

```c
    it = (s32)D_80120194;
    p = it + 0x658C;
    q = it;      /* dead copy: q is never used */
```
The dead copy creates a second USE of the base pseudo (not a second set). If GCC's decision to keep the constant in a register depends on the use count, this could work! In GCC's reload, `reg_equiv`/rematerialization: reload decides per reload; if the pseudo's value is a constant and it's used once, reload substitutes the constant at the use site (that's `reload`'s "reg_equiv" handling: `reload_reg` → if the value is a constant, it may create a "rematerialization" insn in the reg instead of substituting).

Hmm, in the target the constant IS materialized in a register (lui/addiu). So reload materialized it. In mine it was substituted at the use.

GCC's reload: for a pseudo whose value is a constant (via REG_EQUAL note), reload has two options: (1) substitute the constant into the insn (if the insn can take a constant), or (2) put the constant in a register. The choice is in reload.c's `reload_reg`: it checks `reg_equiv_contain_p` and whether the operand is a "constant" that the machine can handle.

For `plus(reg, const)`: the machine (mips) can do addiu with a 16-bit constant. But the constant here is a SYMBOL address + 25996 — i.e., (plus symbol_ref const). The mips backend's `mips_operands` handles (plus (symbol_ref) (const_int)) as an address operand → so it CAN take it → substitution.

Hmm, but why did the target keep it in a reg? Because in the target, the value was NOT known to be a constant (the asm made it opaque). ARGH. Circular.

So the ONLY way to reproduce is to make the value opaque to GCC's optimizer.

Ways to make a value opaque in plain C:
1. asm (forbidden).
2. volatile (a lever; also `volatile` on a local variable's *address* wouldn't help).
3. A value that comes from memory (a load) — but that adds an instruction.
4. A value from a function call — adds instructions.
5. **A value whose definition is in a different basic block / from a phi** — GCC 2.7 has no phis.

Hmm, 6: **A value that is the result of an operation GCC can't simplify**: e.g. `it = (s32)D_80120194;` → what if we compute it as `it = (s32)D_80120194; it = it + 0;`? Folded (and identity).

7: **A value stored to and loaded from memory**: `*(int*)&mem = ...` → volatile needed.

Hmm, 8: **A global variable**! If we write to a *global* (not local) variable, the value must be stored in memory and reloaded → the load gives an unknown value → opaque! But that changes the program's semantics (writes to a global) and the object would have an extra store/load. Unless the global is a scratch variable that's... no, extra instructions.

Hmm. But WAIT: what about a global that GCC can prove is only written here? The store+load would be real instructions. No.

9: **A function parameter**? No params in C2D0.

Hmm, 10: **A static local variable**? Same as global.

11: What about the *address of a local* (a stack address)? Not constant, but it's a different address.

Hmm. So how did the ORIGINAL produce this?!

Let me reconsider: maybe the original DIDN'T have a constant address at the base. Let me re-read the target's relocations:

```
4178: 3c030000 lui v1,0x0     R_MIPS_HI16 D_80120194
417c: 24630000 addiu v1,v1,0  R_MIPS_LO16 D_80120194
```
So the address of D_80120194 is materialized in v1.

Now, in the ORIGINAL source, this materialization could come from:
(a) `it = (s32)D_80120194;` (a constant) — would be folded at the use.
(b) `it = (s32)&D_80120194[0];` same.
(c) The address is loaded from memory — no (that'd be an lw).
(d) `it` is a *pointer* variable that was assigned from a global pointer variable — no lw in the target.

Hmm, so (a) or (b), and the fold didn't happen in the original.

MAYBE the original was compiled with a different gcc version! The ROM's code was compiled by Sony's gcc 2.7.2 (or 2.6?) for PSX. Our pipeline uses gcc 2.7.2. If the fold behavior differs between 2.6 and 2.7...

Hmm, but the project has matched thousands of functions with this pipeline, so the compiler is right.

Hmm, hold on. What if the difference is the ORDER of the two statements, or the presence of the `goto`?

Let me try: what if the source's first statement is `p = it + 0x658C` where `it` was assigned EARLIER... no.

**NEW IDEA**: What if the original source had the base as a *pointer* and the copy block's `return it;` returned the base (as I hypothesized), with the loop using a different variable? We ruled it out because of the register overlap. But let me re-examine: if the base is live 4178→418c and the loop pointer is live 4190→418c, they overlap at 418c → they'd need different regs. The target uses v1 for both... unless the loop pointer is NOT v1 at 418c! At 418c, `move v0,v1` — the value copied could be the base (v1) while the loop pointer is in another reg at that point? But at 41a0 the loop pointer is v1 (`lhu v0,0(v1)`), and 41b0 `addiu v1,v1,268`. So at 418c, v1 = the loop pointer (the last def of v1 before 418c is at 41b0). If the base were also live at 418c, it would be in a different reg, and the `move v0,v1` would be the base's value only if v1 held the base — contradiction. So the copy block returns the loop pointer. Confirmed. The base is dead after 4184.

OK so how the heck did the original keep the base in a register?!

Hmm, wait. What if the base pseudo's value was NOT a constant because the original source obtained the address differently — e.g., via a *pointer-to-pointer* indirection that GCC folded...

What if the original source was:
```c
    it = (s32)D_80120194;
```
where `D_80120194` was declared as `extern u8 D_80120194[];` in the game's source BUT the game's source had it as a `static` array? Then the address is still constant.

Hmm, what if the original source's base came from a *function-local static* or a *computed* value?

Hmm, let me look at the sibling function C750's IF branch target to see if its base (used 3 times) is materialized the same way (lui v1; addiu v1) — if yes, then the "N uses" theory holds and the original C2D0 must have had 2 uses.

Let me dump C750's target.
