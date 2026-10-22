---
ts: 2026-10-22T00:32:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_E52KoZZMegVBKNrhDq9q
---
Only binaries, no source. So no cse.c to read.

OK, empirical it is. Let me think about what distinguishes the two loads in c1's output:
- x load: `lh v0,0(s1)` (reg used)
- y load: `lui v1,0x0; lh v1,4(v1)` (constant rematerialized)

Wait, actually, maybe the reason is different: maybe cse decided to rematerialize the y address because the *base reg* s1 is "not available" at that point in the RTL — e.g. the s1 pseudo was *clobbered* by the call? No, s1 is callee-saved.

Hmm! Here's a thought: the *pre-call* y load at 1478 (target: lh v1,4(s1)) — in c1, the y load at that point is `lui v1; lh v1,4(v1)`. And the x load at 145c is `lh v0,0(s1)`.

So even *before* the call, the y load rematerializes while the x load uses the reg. This is a pure cse decision: for the location D_80126B5E+4, the constant address is preferred; for D_80126B5E, the reg is preferred.

AH, I think I understand now! cse's find_best_addr: for the address (reg cam)+4, the *base* is a pseudo (cam) whose value is the constant D_80126B5E. cse considers "the reg holds a constant" → it can rematerialize the *final* address (D_80126B5E+4) as a constant. The cost of the constant address: `lui`+`addiu` = 2 instructions... but cse's cost model in 2.7.2 counts the *number of instructions* differently: for a constant address it may count 1 (a single "load" pseudo insn) vs the reg-based address which requires the reg to be *live* — and if the reg is a pseudo that gets a hard reg, using it costs 0.

Hmm, but for the x load (offset 0) the same logic would apply and it chose the reg. The ONLY difference is the offset. So maybe: cse prefers to rematerialize when the address has a nonzero offset, because the reg+offset form would need an extra addiu? But `lh v1,4(s1)` doesn't need an addiu — the offset is folded into the load. But in the RTL, the address is (reg cam) + 4 — a separate ADD! GCC's RTL for `cam->y` where cam is a pointer: the address is (reg cam) + 4, which in RTL is a separate `plus` insn unless folded into the MEM's offset. MIPS's `mips_address_operand` folds (reg + const) into the MEM offset. So the reg+4 form costs 0 extra instructions after folding.

Hmm, but cse's find_best_addr works on the *unfolded* RTL: it sees the address as a REG+CONST expression, and to use it, the reg must be in a hard reg. Whereas the constant address is a single MEM with a symbol+offset.

I recall in cse.c:

```c
static int
find_best_addr (struct cse *cse, rtx mem, enum rtx_code code)
{
  ...
  for (reg = REG_N_REGS (cse->x); reg--; )
    {
      ...
      if (reg_equiv_content[reg] == 0)
	continue;
      ...
      /* Do not accept a register whose contents are not a constant,
	 unless we are sure that the register is not going to be
	 clobbered. */
      ...
      if (GET_CODE (reg_equiv_content[reg]) == CONST_INT
	  && GET_CODE (mem) == MEM
	  && GET_MODE (mem) == ...)
```
Hmm, there IS a known behavior: cse's find_best_addr prefers a register whose content is a CONST_INT over... hmm.

I recall this specific code in cse.c (2.7.2):
```c
      /* If this is a constant address, and the constant is in a register,
	 then the register is the better choice only if ... */
      if (GET_CODE (reg_equiv_content[reg]) == CONST_INT
	  && GET_CODE (mem) == MEM
	  && GET_MODE (mem) == GET_MODE (reg_equiv_content[reg]))
	{
	  /* The constant is in a register; the address is a constant;
	     prefer the register if the offset is 0 ... */
	}
```
Honestly I recall there IS a rule about "the address must be exactly the constant in the reg" — i.e. cse will use the reg only if the address equals the reg's content *exactly* (offset 0), otherwise it prefers the constant address! That matches the observation perfectly: x (offset 0) → reg; y (offset 4) → constant.

If that's the rule, then to get `lh v1,4(s1)` we need the *address* to be exactly the reg's content, i.e. the reg must hold D_80126B5E+4 — but the target has ONE reg (s1) holding D_80126B5E and the load uses offset 4. Hmm, that contradicts: with the lever, the reg's content is *unknown* (opaque), so the "constant" rule doesn't apply and cse uses the reg + offset.

So: the rule is "if the reg's content is a known constant and the address is a constant, prefer the constant address (rematerialize)". With the lever, the reg's content is unknown → cse can't rematerialize → uses the reg+offset.

Therefore, in plain C, the reg's content must be unknown to cse. The pointer's value must be non-constant. The ONLY sources of a non-constant pointer value in plain C: a load from memory, a call, a parameter, or a computation the compiler can't fold.

Can we get a *load* that costs 0 extra instructions? Hmm! What about this: the *address* D_80126B5E is a global. What if the pointer is obtained by loading from a global that *contains* the address... doesn't exist.

BUT: what about a *pointer to a global* that is at the same address? Hmm.

What about using a *union* or a *cast* that GCC treats as a load: e.g. `cam = *(Cam183098 **)&D_80126B5E;` — that LOADS the u16 value at D_80126B5E as a pointer! Wrong semantics.

Hmm.

What about the *parameter*? The camera address is fixed...

What about a *computation* the compiler can't fold but which is a no-op: e.g. `(Cam183098 *)((u32)&D_80126B5E - (u32)&D_80126B5E + (u32)&D_80126B5E)` → folded.

Everything with a constant folds.

CONCLUSION: for THIS function, the lever-free version cannot keep the address in a register... unless the loads are restructured so that cse doesn't need to choose between a constant and a reg!

IDEA: what if the y load's address is *the same reg* but the *location* is tracked differently... e.g. what if we load x and y as a *pair* (a 32-bit or 64-bit load)? E.g. `u32 xy = *(u32 *)cam;`? That loads 4 bytes (x and part of y?) — the struct has x at 0 and y at 4, so a 32-bit load at 0 gives x (2 bytes) + 2 bytes of padding. Not equivalent. And the target has separate lh loads.

IDEA: what if the y load is done from a *pointer that is a copy of cam*:
```
Cam183098 *cam = (Cam183098 *)&D_80126B5E;
...
Cam183098 *cam2 = cam;   /* hmm, a copy: the reg's content is still known */
```
No.

Hmm, what about making the *base* pointer's value opaque by *adding* to it: e.g. `cam = (Cam183098 *)&D_80126B5E;` then use `cam` for x and `cam + 1`?? no.

Hmm, what if the offset is applied to the *pointer* rather than the address: e.g. `((Cam183098 *)((u8 *)cam + 4))->y` — no, that changes the offset.

What if the y load is `*(s16 *)((u8 *)cam + 4)` and the x load is `*(s16 *)((u8 *)cam + 0)`? Same as now.

OK, so maybe: what if we could make the *y* address NOT a constant, i.e. the offset 4 is not constant? Then the address = reg + reg → cse can't rematerialize → uses the reg. But we'd need the offset value 4 in a register at runtime. The target has no such instruction. Unless the offset comes from a register that already holds 4... e.g. some other constant in the code? The code has constants like 0x1F, 0x3F, 0xF, 0x7F, 0x4000, 0xC000, 0x10, 0x20... no 4.

Hmm, BUT: what if the offset is *derived* from the pointer itself in a way that's free? E.g. the y load at (char*)cam + 4 where 4 = sizeof of something? no.

What if the "offset" is a *negative* offset from a different base? E.g. y is at D_80126B62 = D_80126B5E+4. If the base reg held D_80126B62 (the y address) and the x load used offset -4 → the address would be reg-4 → still reg+const → cse rematerializes the constant for the x load (and the x load currently matches the target!).

Hmm! Interesting: the target has BOTH loads via s1 with offsets 0 and 4. So the base is D_80126B5E.

OK so I'm fairly convinced: item 2 is a WALL, unless there's a trick I haven't thought of.

Hmm, wait. Let me reconsider the cse rule. Let me test the hypothesis directly: if the rule is "cse prefers the constant address when the reg's content is a known constant and the offset ≠ 0", then a *different* way to express the y load might avoid the constant: e.g. if the load's address is (reg cam) + 4 where the *reg* is a HARD reg (not a pseudo) at that point. In cse, the "reg_equiv_content" is only known for pseudos. If cam's value is in a hard reg (like s1) already, cse's find_best_addr would use it directly (no content known) → it would use s1+4!

So: if the pointer were forced into a hard register *before* cse runs... cse runs before register allocation, so everything is a pseudo. Hmm.

But wait: cse's find_best_addr is about *pseudo* regs. It looks at the regs in the cse block's reg_equiv table.

Hmm, so what makes the reg's content "unknown" in cse? The asm. Or... a *call*! If the pointer is set BEFORE a call and used AFTER, cse's reg_equiv for that pseudo is invalidated (the call clobbers memory, and the pseudo's content is unknown after the call? no — the pseudo is a *value* in a reg; a call clobbers caller-saved regs, so the pseudo must be in a callee-saved reg; its content is still known to cse).

Hmm, but here's the thing: the *pre-call* y load (at 1478) also rematerializes in c1. So it's not about the call.

Let me test the hypothesis with a tiny experiment: does the x/y asymmetry persist if I swap the roles (make the first load base+4)? Meh.

Let me try a few candidate formulations quickly (each ~40s):
c2: y loaded via a u16 pointer with index 2: `u16 *c16 = (u16 *)&D_80126B5E; ... c16[2]`.
c3: y loaded as `*(s16 *)((u8 *)cam + 4)`.
c4: cam declared as `u16 *` and x = cam[0], y = cam[2].
c5: the y access via a *second* struct pointer: `Cam183098 *camy = (Cam183098 *)((u8 *)cam + 4);` — no, that changes the offset to 8.

Hmm, c3/c4 are the same thing.

Let me think about cse's rule differently: maybe cse's preference is: "if the reg's content is a constant, and the *address* is also a constant, use the constant address *unless* the reg's content equals the address exactly". In that case, for the y load the reg's content (D_80126B5E) ≠ the address (D_80126B5E+4) → use the constant.

So to get reg+4, the reg's content must be *unknown* or the address must not be a known constant.

Hmm, so what if the base pointer's value is *not* known because it's derived from a *struct member* of a local? no.

What if the base pointer is derived from the *parameter*? Like: what if the function's param_1 were the camera pointer? No.

Hmm, hold on! What about this: make the base pointer's value *opaque* by deriving it from a *load of the parameter*? E.g. `cam = (Cam183098 *)((u8 *)&D_80126B5E + (param_1 - param_1))` → folded.

What about `cam = (Cam183098 *)(u32)&D_80126B5E | 0`? folded.

What about using *pointer arithmetic on a null-ish pointer*? no.

OK, what about the *asm-free* way to make a value opaque: an *uninitialized* variable read? UB.

What about `cam = (Cam183098 *)&D_80126B5E;` where the *type* is a `const` pointer? no effect.

Hmm hm. What about the possibility that the *whole approach* is different: maybe the crack is to make the *loads* use the *same* address by loading the pair as one 64-bit? no.

Let me now consider: maybe the y load's address could be *reg+4* if the reg's content is unknown — and the reg's content could be unknown if the pointer is assigned from a *load of a pointer stored in the sp arrays*? no.

I think item 2 is a WALL (cse-const-addr). The tag exists already: `cse-const-addr` (from walls.txt: "cse folds or substitutes a constant/absolute address the target keeps base-relative"). That's exactly this mechanism!

So for item 2: WALL cse-const-addr, best score 10 (c1). tries: let me try 2-3 more variants first to be fair (the brief wants a few tries).

Let me try:
c2: `u16 *c16 = (u16 *)&D_80126B5E;` with `c16[0]`, `c16[2]`.
c3: the loads via `*(s16 *)((u8 *)cam + 4)`.
c4: cam assigned twice (real 2nd set): `cam = (Cam183098 *)&D_80126B5E;` at the top and again after the switch? Hmm, "real 2nd set" — cse would fold it, but the *pseudo* then has 2 sets, and cse's find_best_addr might behave differently! Worth a try.

Let me write c2, c3, c4 and batch them.

Actually, for c4, the "real 2nd set" idea is the moves.md-proven approach for launder cracks. Let me put the 2nd set right where the asm was:
```
cam = (Cam183098 *)&D_80126B5E;
cam = (Cam183098 *)&D_80126B5E;
```
Hmm, that's an identity assignment (self-assign) — "identity-statement launders do NOT count as a crack". But this is a test to understand the mechanism; if it works, I'd need a *real* second set. Hmm, but what would be a "real" second set of a pointer? E.g.:
```
cam = (Cam183098 *)&D_80126B5E;
...
```
Hmm.

Let me test c4 with the plain double assignment to learn the mechanism (diagnostic), and c2/c3 as genuine alternatives.

Let me write them.
