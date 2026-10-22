---
ts: 2026-10-22T09:34:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_0gMKLmionwG4cchOLQOR
---
KEY FINDING (reload.c side effect #2): "Pseudo-registers that are equivalent to constants are replaced with those constants if they are not in hard registers."

So a pseudo p (equivalent to the constant symbol) gets replaced with the constant at reload. That's why our tree has symbol_ref at the add (rather than a reg) — and where the swap happens.

But in the target, the pointer stayed a pseudo → so the pseudo was in a HARD register? "if they are not in hard registers" — so if the pseudo is allocated to a hard register (like a1!), it is NOT replaced by the constant!

So: in the target, the pointer pseudo was assigned to a HARD register (a1) — that's exactly what the launder asm did (it forced p into a register)! And the notes say the launder was needed.

Hmm, but "hard register" here means a pseudo that local-alloc/global-alloc assigned to a hard reg... but reload runs BEFORE local allocation? In gcc 2.7, the order: ... local-alloc → reload → reload1 → ... Actually: global allocation happens first (allocates globals to regs), then local-alloc, then reload (reload allocates pseudos to hard regs as needed), then reload1.

Hmm, in gcc 2.7: flow, global.c (global alloc), local-alloc.c, reload.c, reload1.c, flow2, reorg, sched, final.

So the "hard register" for a pseudo comes from local-alloc (pseudos that are live across calls get callee-saved regs) or from reload's own allocation.

Note: reload's replacement of constant-equivalent pseudos happens for pseudos NOT in hard registers. Our p (112) — was it in a hard register? It's used once, so local-alloc would give it a caller-saved pseudo... The pseudo 112 is not a hard reg, so it got replaced by the constant.

But hold on: the replacement is of the PSEUDO (reg 112) by the constant. In our tree the use was already a symbol_ref at the .rtl dump, i.e. BEFORE reload. So the substitution happened even earlier (expand or cse). Hmm, but the .cse dump also shows symbol_ref — so it happened at expand time (or cse's reg_equiv).

Ugh. Well: the practical question is how to make the pointer a pseudo that survives to reload as a REG.

Options:
- Make the pseudo "used more than once" so that expand/cse don't fold it: e.g. use p twice. But then the second use changes the asm (as discussed).

Hmm, BUT: what if p is used twice in a way that the second use is *folded away* by cse anyway? E.g. `p = D_80195AF6; ... = D_80195AF6[idx].f0;` — the second use doesn't involve p.

What if we write the newval load through p: `p[idx].f0`? Then p has 2 uses → the pseudo stays → but the newval address becomes (plus (reg p) (reg idx)) → reload materializes p into a reg (a1) → "addu at,a1,v0" instead of "lui at; addu at,at,v0" → the count would be 110 vs the target's 111 → mismatch.

Hmm! Unless... the target's count is 111 and ours is 111 with one insn differing. If I make p used twice, the count changes.

Wait, actually, let's think about what the target's asm shows again:
```
lui  a1,0x0        ; D_80195AF6
addiu a1,a1,0
lui  at,0x0        ; D_80195AF6
addu at,at,v0
lh   v0,0(at)
```
The a1 materialization at the arm start is the *p* pseudo in a hard reg (allocated by reload to a1, since it's used at the end of the arm). The `at` materialization is for the newval address.

Now, in our current compile, we ALSO produce "lui a1; addiu a1,a1,0" at the arm start! So our p is ALSO in a1 at the arm start. Hmm! Then why is the add's operand order different?

In ours: "lui a1; addiu a1,a1,0" (a1 = symbol) ... "addu v0,v0,a1". So a1 holds the symbol and it's the second operand. In the target: "addu v0,a1,v0" — a1 first.

So both have the pointer in a1; only the position in the add differs. So the tree order before reload differed: ours (plus (reg 118) (reg a1))? Hmm, but the .cse dump showed (plus (symbol_ref) (reg 118)) — symbol FIRST. So the swap to index-first happened in reload (side effect #1: operands may be interchanged in a commutative insn "if find_reloads thinks the instruction will compile better that way").

So reload swapped (symbol, reg118) → (reg118, symbol) → the symbol then reloaded into a1 → "addu v0,v0,a1".

In the target, no swap happened (or a different swap decision).

Reload's swap decision: find_reloads tries alternatives; when the insn is commutative (e.g. an "addu" with two reg operands — in the mips pattern, the commutative operand pair is the two sources), it tries both orders and picks the better one.

In the target: the tree was (plus (reg ptr_pseudo) (reg 118)) — both are pseudos/regs; reload allocates the pointer pseudo to a1 and the index to v0 → "addu v0,a1,v0".

Hmm, but in ours the symbol_ref is an operand that needs a reload (lui+addiu), so the "reload" of the symbol into a1 happens as part of the address computation, and the commutative swap logic decided to swap so that the symbol is second (maybe because a "base+index" convention prefers the base in the second operand? In MIPS, `addu rd, rs, rt` with a memory operand must have the memory in the second position: "lw rd, off(base)" → base is the second operand).

YES! That's the classic MIPS constraint: for commutative instructions, the memory operand must be the SECOND source operand. So reload swaps so that the operand needing a memory/reload goes second. In our case, the symbol needed a register reload (lui/addiu) — hmm, but the result was "addu v0,v0,a1" — the symbol (a1) is second ✓ consistent with the MIPS convention (the "base" second).

In the target, the pointer was already in a1 (a pseudo allocated to a1 before/at the same time) and the index in v0 → "addu v0,a1,v0" — the pointer first. So in the target, no swap was needed because the pointer pseudo was a plain reg operand.

So again: the target's pointer was a PSEUDO (not a symbol) at reload time.

Now, in OUR compile, the pointer pseudo was replaced by the constant (reload side effect #2: "Pseudo-registers that are equivalent to constants are replaced with those constants if they are not in hard registers") — wait, but our a1 materialization exists... The pseudo 112 = symbol; the symbol is needed at the add; reload replaces pseudo 112 with the constant symbol_ref in the address, then the address's constant part gets a lui/addiu into a1.

Hmm, but the "lui a1; addiu a1,a1,0" appears at the ARM START in both ours and the target — so in ours too, something materialized the symbol early into a1. What was it? In ours, the newval load's address (plus symbol idx) needs the symbol → reload creates a register for it (at) at the load. But we see BOTH a1 (at arm start) and at (for the load). So the a1 materialization in ours is... the pointer pseudo 112 being allocated to a1 and materialized at the arm start (since the pseudo is live from the arm start to the add). Then at the add, the pseudo was replaced by the constant?! That would be weird (the pseudo is in a hard reg now).

Hmm, "if they are not in hard registers" — after reload allocates the pseudo to a1, is it "in a hard register"? The replacement happens in find_reloads when REPLACE=1. The order: reload allocates regs for the insn's operands, then substitutes.

I think I'm going too deep. PRAGMATIC APPROACH: try many C spellings and see which gives "addu v0,a1,v0". The lever that worked before was the asm (making p a hard register). Lever-free alternatives to try:

1. Make the pointer used twice (newval through p) — changes count, but let me actually TEST it: maybe gcc still produces "lui at; addu at,at,v0" because p is in a1 and the newval address uses... hmm, if p is in a1 then the newval address = a1 + idx → "addu at,a1,v0" (no lui at). Count -1. Let me test anyway; maybe the compiler re-materializes.

2. Use the pointer p for BOTH the newval load and the final load, but write the newval as `D_80195AF6[idx].f0` (symbol) — p used once. Same as now.

3. Make p's assignment happen through a *function call* result? No.

4. Make p a **parameter-like** local that is live across a call: e.g. declare p before the call `func_8012AD80(a0)`? The call is in the first part of the function; p is assigned inside the else arm. Hmm, if p were declared at the top and assigned in the arm, it would be live across... no call between.

5. Force p into a callee-saved register by making it live across a call: the else arm has calls (func_8018ABE0, func_8018AEB4) BEFORE the p use. If p is assigned before those calls and used after, p must be in a callee-saved reg (s-register) → the asm would show a different register (not a1) → mismatch. Unless... hmm, in the target, a1 is used, so no.

Hmm, so how did the TARGET get a pseudo in a1?

Wait — maybe in the target, the pointer pseudo was allocated to a1 by RELOAD (not local-alloc), because the address (plus (reg p) (reg idx)) needs both operands in regs: p → a1 (reload allocates it), idx → v0. Then the tree order stays (p, idx) → "addu v0,a1,v0" ✓. And the "lui a1; addiu a1,a1,0" is the materialization of p's value (the symbol) into a1 ✓ at the arm start (reload hoisted it).

And in OURS, the tree at reload time was (plus (symbol_ref) (reg 118)) — the pseudo was already replaced by the constant BEFORE reload (at expand/cse time) → so reload sees a symbol operand → it creates a register for the symbol (a1) and, due to the commutative/MIPS convention, puts it second.

So the difference is at expand/cse time: whether the pointer pseudo survives as a REG in the address.

Why did expand fold our p into the address? Because p's value is a constant AND p is used once? Hmm, in expand (gcc 2.7) `expand_expr` REG case:

```c
    case REG:
      ...
      /* If this is a pseudo-register with a constant value, ... */
```
I recall the actual gcc 2.7 code in expand.c:

```c
      /* Handle the case of a variable that is a constant: 
	 the value is in the reg's reg_constant ... */
```
Hmm no, expand.c isn't in our reference copy. But cse.c IS, and cse does the reg_equiv substitution: cse.c's `make_regs_eqv` and the "record_eq_reg" logic replaces a reg with its reg_equiv constant. cse's reg_equiv for a pseudo set to a constant: cse.c has `record_eq_reg` with `reg_equiv` — and in cse's main loop, when it sees `(set (reg p) (const/symbol))` it records the equivalence and later replaces uses of p with the constant!

In cse.c, `reg_equiv` for a REG set to a constant: the code is in `update_eq_reg_notes` / `record_eq_reg`:

```c
      /* If we are recording a non-trivial equality, ... */
      if (GET_CODE (SET_SRC (x)) == CONST_INT ...
```
and there's the classic cse rule: "if a reg is set to a constant and it has only one use, replace the use with the constant" — that's `record_eq_reg`'s handling with `REG_EQUIV` notes and the "one set, one use" rule.

Also note from moves.md: "launder | func_801497A8 | WALL cse-const-addr — cse: single-set const addr r73 folded into lone use lbu 73(sym) even past a 2-use join label; s1 never held" — so CSE folds single-set constant addresses into uses! That's the mechanism: cse.c's rule that a pseudo set once to a constant is replaced by the constant at its use.

So: to keep the pointer as a REG, the pseudo must have MORE THAN ONE use (so cse doesn't fold it), or its set must not be a simple constant.

If p has 2 uses, the newval load must use p too — but that changes the asm as discussed... unless the second use is one that produces the same asm!

Hmm! What if the second use of p is the *same* address expression, i.e. the pointer is used twice in a way that yields the target's asm: e.g. the target's `lui a1; addiu a1,a1,0` at the arm start and the newval's `lui at` — TWO materializations of the same symbol. If p were used by both the newval load and the final load, the compiler would emit ONE materialization (into a1) and use it twice → "lui a1; addiu a1,a1,0; addu at,a1,v0; lh v0,0(at)" — that's 4 insns vs the target's 5 (lui a1, addiu a1, lui at, addu at, lh). So the count would be 110 ≠ 111. But hold on — maybe not: the target has "lui at" for the newval address because the newval expression was written on the SYMBOL directly, not through p. If I write it through p, I lose the extra lui → count 110.

Unless the p use count is 2 but one use is dead-ish... e.g. p used in a comparison that's optimized away? Any use that's eliminated by the optimizer doesn't count as a use at cse time? Actually cse's rule is about the number of *uses in the RTL*; if a use is deleted before cse, it doesn't count.

Hmm! What if p is used twice, but one use is in a *dead* expression that gets deleted early? E.g. `if (p == 0) { ... }` — no, that changes semantics/asm.

What about using p in a way that's *provably* the same but doesn't survive? E.g. `p = p;`? That's an identity — "identity-statement launders do NOT count as a crack" per the brief. Also gcc would fold it.

Alternatively: maybe we can get TWO uses of the pseudo without changing the asm: the *pointer* could be used twice in the SAME address expression: `(u8 *)p + off + 4` — one use.

Hmm, what about the index: the final address uses p once.

OK, let me look at cse.c's rule to see exactly when the constant substitution happens. Let me find the code in cse.c that replaces a reg with its reg_equiv constant. Search for "reg_equiv" and "CONSTANT" in cse.c.
