---
ts: 2026-10-21T23:36:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_kfTDM919OrURlCW3SPaw
---
Original with launder = 0. Good.

So the launder is what makes gcc produce `addiu a0,sp,16 / addiu a1,sp,24` (recomputed) rather than keeping sp+24 in s0.

Wait, that's counterintuitive. Let me think about why. Without the launder, gcc has p0=sp+16, p1=sp+24. It computes p0 into a0 (addiu a0,sp,16) and p1 into s0 (addiu s0,sp,24) then move a1,s0? Hmm, mine had `sw s0,32(sp); addiu s0,sp,24; move a1,s0` — so s0 = sp+24, a1 = s0, and later a0 = s0 for call 2.

Hmm, so without launder gcc allocates s0 to hold sp+24 (a "pseudo" CSE) — because the value is used twice (a1 for call 1, a0 for call 2) and holding it in a callee-saved reg avoids recompute. But target recomputes it (addiu a0,sp,24 at 15).

With the launder... hmm, the launder is `asm("": "=r"(p1): "0"(p1))`. That forces p1 into a register and the asm output is a *new* pseudo. So the asm result p1' is in a register; then p1' used in call 1 (a1). But gcc then re-derives p1 for the second use?

Hmm, actually the launder breaks the CSE: the asm output pseudo is a fresh value; but gcc then uses p1 (the original) for `func_800D23D0(sp10 + 4)`? No, that uses sp10+4 directly, a separate expression. But gcc's CSE would unify sp+24 for both p1 and sp10+4.

Hmm, so with the launder, gcc computes: a1 = p1_laundered (addiu a1,sp,24 at insn 4 — computed fresh), and later a0 = sp10+4 (addiu a0,sp,24 at 15). Without launder, gcc CSEs them into s0.

Hmm wait, but the launder asm's "0" output is tied to the input p1 which is sp+24. The asm forces a register copy. But gcc put it directly in a1? That means gcc allocated p1 to a1.

OK whatever the mechanism — the point is the launder changed something. Let's figure out what real-C change could produce the target without asm.

Observation: the target computes sp+24 twice — once in the delay slot region as a1, once as a0 for call 2. The key difference from mine: mine CSE'd them into s0.

To break the CSE in real C, we need the two expressions to be *different* as far as gcc is concerned, but produce the same address. Options:
1. Use a union/aliasing trick.
2. Compute p1 as `sp10 + 4` and separately `sp10 + 4` — same.
3. Use different types so the address arithmetic differs: e.g. `p1 = (u16 *)((u8 *)sp10 + 8)` vs `sp10 + 4`. Both are sp+24. But gcc's CSE works on the address expression, and (u8*)sp10 + 8 vs sp10+4 would be different expressions but GCC would fold both to sp+24 as an ADDR_EXPR constant offset → they'd be the same "pseudo" only if the base is the same DECL. Hmm, gcc's CSE is on the rtx tree; `sp10 + 4` and `(u8*)sp10 + 8` produce different trees (different types/scale) but simplify to the same constant address. But then they'd be different pseudos? Actually RTL simplification would canonicalize both to (plus (reg sp) (const 24)) since the DECL is the same. So no.

4. Make the array be addressed through a different pointer variable: `u16 *base = sp10;` then `p1 = base + 4;` and `func_800D23D0(base + 4)`. The base is a pointer variable (in a register) — then p1 = base+4 needs an add; and the second use base+4 again... gcc would CSE again.

5. Different key: the target's first computation of sp+24 is at insn 4 (before the sw ra/s3/s2/s1 saves at 6-9) and the second at 15 (delay slot of jal). Between them, the call at 12 happens. So the second is after a call. In the target, the value is NOT live across the call in a callee-saved reg — it's recomputed. But gcc chose s0 (callee-saved) to hold it. gcc avoids rematerialization of the address across calls because rematerializing is "free" but keeping in s0 costs a store/load of s0... Actually gcc chose to keep it, adding `sw s0,32(sp)` + `lw s0,32(sp)`.

The real question: what C construct makes gcc rematerialize the address instead of keeping it in a callee-saved register?

The launder asm achieves it. Alternatives:
- A second call between them that clobbers... no, s0 is callee-saved.
- The address is derived from `sp` directly (frame pointer) → gcc knows sp doesn't change, and the address is a "constant" relative to sp, so it can rematerialize. But gcc chose to keep it in s0 anyway, apparently because of the "address of local array" being address-taken (escapes) → gcc treats it as a MEM whose address is a constant; it can rematerialize.

Hmm. Actually why does gcc keep it in s0 at all? Because there's an optimization: the address is used twice, once before the call and once after; gcc's CSE creates a pseudo and the register allocator assigns it a callee-saved reg since it must survive the call. Rematerializing would be 1 instruction (addiu) vs keeping (sw+lw = 2). But addiu a0,sp,24 is 1 instruction and the target does that. So why did gcc prefer s0?

Maybe because the pseudo was in the "address of stack slot" set and gcc's reg allocator decided to keep. Hmm.

Alternative approach: make the two uses *distinct* in C such that gcc can't CSE them, e.g. by having the second use read the pointer from memory: `func_800D23D0(*(u16 **)&someVar)`? Hmm.

Actually — the launder! Notice: in the target, the FIRST use (a1 for call 1) and the SECOND use (a0 for call 2) are both sp+24. In the original C: `func_800D20C0(p0, p1, 1)` and `func_800D23D0(sp10 + 4)`. These are two different expressions: p1 (a variable) and sp10+4. GCC can't CSE them because p1 is a variable whose value was laundered by asm (the asm output is a distinct pseudo from the address constant). Hmm, but the asm output p1 is tied to input p1 via "0" constraint, so p1's value is the address.

Hmm. Without the asm, p1 = sp10+4 is a constant address, and sp10+4 is the same constant → CSE.

So: to break CSE in real C, we need p1 to be an opaque value. Options:
- Store p1 into a stack slot and reload it? Then a1 = lw from stack. That gives different insn, not `addiu a1,sp,24`.
- Use a `volatile` local? `volatile u16 *p1 = sp10 + 4;` then a1 = p1 → gcc loads from the stack slot. Not addiu.

Hmm. What if the array is at a different offset so p1 and sp10+4 differ?

Wait. Let's reconsider. Maybe the trick is different: what if we make the *first* call's second arg and the second call's arg be two DIFFERENT stack offsets in gcc's view, but the target shows both sp+24...

Hmm, target shows a1 = sp+24 and a0 = sp+24. So the same address. But gcc must not CSE them.

Idea: pointer arithmetic with different types where the final address is the same but gcc's canonicalization differs. E.g.:
  p1 = (u16 *)((u8 *)sp10 + 8);
  func_800D23D0((u16 *)((u8 *)sp10 + 8));
Both are address_plus_const with the same base DECL sp10 and const 8 — canonicalized identically after simplification? The type differs (u8* vs u16*), but simplify_rtx folds both to (plus (symbol_ref sp10) (const 24)) with the same mode. Hmm, in RTL, the address of a stack slot is (symbol_ref) with a frame offset, and pointer arithmetic yields (plus (symbol_ref) (const)). Both same → CSE'd.

Idea: use a struct/union where two different members alias? Same base, different offsets → different addresses, no.

Idea: give the compiler two distinct base objects at the same address — e.g. two separate arrays? No, they'd be at different addresses.

Hmm. What about the direction: maybe instead of breaking the CSE, we make gcc not want to keep the value in a callee-saved register. E.g., if the value were used only before the call... no, it's used after.

What if we make the address depend on something that's cheap to rematerialize but that gcc's regalloc treats as rematerializable? Actually gcc DOES have a "rematerialization" concept: constants and simple address computations are rematerializable. The question is why gcc picked s0.

Maybe the reason is: the pseudo holding sp+24 was assigned to s0 by the register allocator because it was live across the call at 12 and also across insn 4→15. But gcc usually prefers to rematerialize... apparently not here.

Hmm, let me look at what happens with a different arrangement: what if the second call `func_800D23D0(sp10 + 4)` is written differently, e.g. `func_800D23D0(p1)` — then both uses are p1, and gcc keeps p1 in s0 across → mine-like. Not helpful.

Alternatively: what if we change the ORDER of the two calls? No, must match target.

OK, another angle: what if the first call's second argument is not sp10+4 but something else that the target shows as sp+24... it IS sp+24.

Let me look at the delay-slot structure: target insn 14 jal, 15 addiu a0,sp+24 (delay slot). So a0 is computed in the delay slot, before the call executes. That means gcc scheduled the address computation into the delay slot. For that, the value must be ready before the call. If gcc kept sp+24 in s0, it would emit `move a0,s0` in the delay slot (1 insn) — cheaper. It chose addiu, meaning the value was NOT in a register at that point, i.e. gcc rematerialized it there.

In mine, the delay slot of the jal at 14 would be `move a0,s0` presumably.

So the question stands: what makes gcc rematerialize?

Observation: in the target, sp+24 is ALSO computed at insn 4 for a1. So gcc DID have a register for it? No — at insn 4, `addiu a1,sp,24` computes it directly into a1, no register.

So in the target, sp+24 never lives in a register! It's computed twice into argument registers. That's what the launder achieved.

Now, in mine, gcc created a pseudo for sp+24 and put it in s0. Why? Because CSE found two identical expressions. With the launder, p1's value is the asm output pseudo (not a constant address) so CSE couldn't unify p1 with sp10+4.

So the real-C way to break unification: make the two expressions have different rtx trees that don't fold to the same thing. Since the target shows the same address sp+24, they must fold to the same address but gcc must not unify them.

Option: use a union/aliasing: e.g.
```
union { u16 a[6]; u32 b; } u;
```
Hmm.

Option: use an `offsetof`-style: p1 = &sp10[4] vs second call arg = *(u16 **)(&sp10) ... no.

Option: Use a pointer variable that is assigned in a way that gcc treats as a separate value but the register allocator can rematerialize...

Hmm, hold on. Let's reconsider: maybe the CSE isn't the issue at all. Let's check whether a1.c actually shows `move a0,s0` in the delay slot. Let me look at my candidate's disassembly. delever_search with --body prints the diff; I could get my full asm. Let's check if there's a way to dump "mine" asm. The tool prints diffs only. Maybe there's an option.

Let me look at tools/delever_search.py --help to see options.

Actually, the R3.40-013 helpers mentioned: .run/P40/T10/tryinc.py, hdump.sh, tools/cc1_dumps_tu.sh, tools/alloc_table.py. And "delever_search.py --try <TU> <fn> <file> --body" with R-rules. Let me check --help for the R rules (R2/R3/R4...).

Let me look at the tool's help.
