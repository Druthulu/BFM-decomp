---
ts: 2026-10-22T16:16:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_w0o7W0zJNwDju6fBhWeO
---
Still score 1. The branch operand order isn't controlled by the source order then. Let me look at the actual instruction: mine[8] beq a0,v1; target[8] beq v1,a0. Which registers hold what? Let me dump the .s for q9 and check. Maybe it's not the `it == p` branch but a different beq at index 8. Let me dump q9's .s.

From the base .s earlier: the `beq $4,$3,$L480` is at test. In q9 the register assignment may differ: maybe it=v1 and p=a0, and GCC emits beq a0,v1. Target beq v1,a0.

GCC's branch expansion: `beq` operands are (reg1, reg2). For `if (it == p)`, expand_if expands the condition; it may order operands by some canonicalization (e.g., putting the "constant" second, or swapping if one is a REG_EQUAL?). To force the order, maybe use `if (it == p)` vs `if (p == it)` — tried, same. Hmm.

Maybe the difference is which *register* each value is in! "register pairs a0->v1 x1, v1->a0 x1" — maybe mine's it is in a0 and p in v1, and the target's it in v1, p in a0. Then the branch encodings are both in source order (beq it,p): mine beq a0,v1 (it=a0,p=v1), target beq v1,a0 (it=v1,p=a0). So it's a *register allocation* difference: mine assigns it→a0, p→v1; target it→v1, p→a0. That's a swap of which pseudo gets which reg.

So the branch order follows the registers. We need it in v1 and p in a0. In q9, mine has it in a0 and p in v1. Earlier (base), mine had it in v1 at test and p in a0 — and the branch was beq a0,v1 (i.e., it=v1, p=a0, source order? beq a0,v1 would be p,it). Hmm.

Let me dump q9's .s to see the actual registers.

Target:
```
lui v1,%hi(D_80120194)
addiu v1,v1,%lo
j test
addiu a0,v1,25996      # p = it + K  (it=v1, p=a0)
test:
la v1, D_801202A0      # it=v1
beq v1,a0,zero
move v0,zero
body:
...
```
q9's C: it=A; goto test; test: p = it+K; it=B; if (it==p)...
The compiler must keep it=A in a register across the goto (live into test) → it gets a reg; p gets another. Mine: maybe it=a0, p=v1? The diff says mine[8] beq a0,v1 vs target beq v1,a0, so in mine it=a0, p=v1 (beq it,p). We want it=v1, p=a0.

Register allocation: both are caller-saved. GCC's local-alloc assigns regs by priority/order. The difference from the target might be caused by the *order of the sets*: in the target, it=A is set first (birth earlier) → gets v1? and p later → a0. In q9, it=A is set first too. Hmm.

Wait, maybe the target's C has the p computation *before* the it=B assignment (yes) and the it=A assignment *inside the test block*? Let me re-read the target: insns [0..1] it=A; [2] j test; [3] addiu a0,v1,K (delay slot). So it=A is in the entry block, p computed in the delay slot. q9's C has it=A in entry, goto, p in test — matches.

Now, which register for it vs p: GCC's global alloc picks. In mine it=a0. Could the difference be that in the target, `it` is live *longer* (from entry through the delay slot) and p is born later? Both live across the j. 

Hmm, maybe the difference is that in the target, the `it` pseudo is *the same* pseudo as the test's it (reassigned), so its allocation is influenced by later uses (lhu, +=, compare) — it must survive the calls? no calls. The register for the it pseudo is chosen considering all its uses; the it pseudo (same variable) is in v1 throughout. In mine, same. So why a0?

Local-alloc assigns registers to pseudos; the it pseudo's first use is in entry, p's first use in test. The allocator might prefer... Let me look at what determines it. Perhaps a *declaration order* change (declare p before it) would flip the allocation. The prior coder's gen_order_swap scored 4 (with the old structure). With q9's structure, try swapping declarations.

Also try: remove the separate `p` declaration by computing p into a variable declared later, or reorder the assignment so p is set before it (can't, p needs it).

Let me test:
- q19: q9 with `s32 it; s32 p;` (swap decls)
- q20: q9 with `it` declared first but p assigned via a temp?
- q21: q9 with the `test:` block reordered: `it = B; p = it + K;`? That would compute p from B — wrong. p must be from A.
- q22: q9 but with `p` declared as `s32 p;` inside the test block? No, p is used later.

Let me dump q9's .s to confirm the registers, then try declaration swaps.

Actually the fastest: try a handful of variants and score. Let me include:
q19: swap decls (`s32 it; s32 p;`)
q20: declare p at the top but assign after goto; same as q9 (decl order p,it is q9). q9 has `s32 p; s32 it;`. Target? Let me try it,p.
q21: use `int` for both.
q22: p computed as `it + 0x658C` but with p declared `s32 p = 0;` (init at decl) — may change priority.
q23: add a `s32 zero = 0;`? no.

Let me also check the register assignment logic: maybe the *use* in the delay slot (addiu a0,v1,K) is scheduled there, and local-alloc assigned p→a0 because p's birth is the addiu in the delay slot... In mine, maybe the addiu is `addiu v1,a0,K`? The diff only shows insn 8 differing, so instructions 0-7 and 9-18 are identical! Wait, if the diff shows only insn 8 differing, then mine's insns 0..7 match the target: [0] lui v1? Let me check: the diff only lists insn 8, so all other instructions are identical, including registers! That means mine's it IS in v1 and p in a0 (same as target) for all other instructions, and only the beq's *operand order* differs!

So the register pairs "a0->v1 x1, v1->a0 x1" refer to the single beq instruction having its two operands swapped. So mine: beq a0,v1; target: beq v1,a0, while everything else matches. So the registers are it=v1, p=a0 in both; the branch just encodes the operands in the opposite order.

So I need GCC to emit beq v1,a0 for `if (it == p)`. Mine emits beq a0,v1. Since everything else matches, the C is right except the branch operand order. GCC canonicalizes the comparison operands: in `expand_if`, for an EQ, it may swap to put the operand with the "lower" something first, or use `swap_condition`/`canonicalize_comparison`. There might be a way to influence it: compare via `if (p == it)` — tested (q14, score 1). Both give the same encoding? Maybe the encoding is determined by the *register numbers*: GCC's `gen_condjump`... Hmm.

In MIPS, `beq $rs,$rt` is symmetric semantically; the assembler encodes in the given order. GCC's `emit_jump_insn` for a branch uses `gen_rtx_IF_THEN_ELSE (EQ, op0, op1)` in the order from the C tree. But GCC may canonicalize `(eq (reg a) (reg b))` by swapping to put the smaller register number first? If mine has it=v1($3), p=a0($4) and emitted beq $4,$3, that's putting the larger first (a0=4 first). Target beq $3,$4 (smaller first). Hmm, GCC's `swap_condition` + `canonicalize_comparison`? 

Maybe the difference comes from *which pseudo is the first operand in the RTL*: `if (it == p)` → (eq it p); `if (p == it)` → (eq p it). If GCC doesn't canonicalize, the source order maps directly to the encoding. Then `if (p == it)` should give beq a0,v1... which is what mine already is. And `if (it == p)` gives beq v1,a0 = target. But q9 uses `if (it == p)` and got beq a0,v1! So GCC swapped it.

Hmm, why? Because `it` is a pseudo that is *set later* in the same block (it = B before the compare). The comparison is `(eq it p)` but at RTL the `it` used is the newly set pseudo. GCC's `expand_expr` for EQ calls `canonicalize_comparison`? Or the MIPS `branch_zero` pattern... The dump earlier showed `(if_then_else (eq:SI (reg/v:SI 16 s0) (const_int 0)))` for the obj test. For reg-reg compares, mips has `branch_zero` only; a general EQ between two regs is expanded via `seq` + branch zero, or mips.md has `beq` patterns. 

Maybe the operand order is decided by `REGNO` ordering in `gen_branch`: GCC's `emit_conditional_branch` might call `swap_operands` to put... 

Let me look at the target's .s vs q9's .s side by side to be sure. Let me dump q9's .s and compare with the target listing from the diff. Actually the diff already tells: only insn 8 differs, operands swapped.

How to flip? Options:
- Compare with the operands in the other order in a way GCC won't canonicalize: e.g. `if (p == it)` gave the same (q14: score 1). Hmm, q14 = 1, and maybe it's the same swapped order. Let me check q14's diff: maybe it's also beq a0,v1.
- Use `if ((it ^ p) == 0)` — extra insns.
- Use `if (it <= p && it >= p)` — extra.
- Use `if (!(it != p))` — same.
- Use a `switch`? no.

Maybe the branch operand order follows the *allocation order* of the pseudos: GCC's `gen_rtx` order is preserved, but the *reorg* pass may swap operands to fill the delay slot? No.

Hold on: maybe the target's C has the comparison written as `if (p == it)`. And mine (q9, `if (it == p)`) emits beq a0,v1. If the encoding is source order, then target's C would be `if (p == it)` with p=a0 first → beq a0,v1 — that's mine's, not target's. So target's C = `if (it == p)` and encoding = source order = beq v1,a0. Mine with the same source got beq a0,v1. So something in mine swapped.

What could swap? The `it` pseudo at the compare is the *result of `it = (s32)D_801202A0`* (a fresh pseudo). Maybe GCC's `combine` or `cse` rewrote the comparison. Or `expand` used `canonicalize_comparison` which orders by... In GCC 2.7.2, `expand_expr` for a comparison of two registers: `if (GET_CODE (op0) == REG && GET_CODE (op1) == REG)` — it may swap so that the "more constant-like" operand is second. Both are regs.

Alternatively, the branch is generated by `gen_branch` from mips.md's `branch` pattern with `(match_operand 0 "cmp_op")`. The order comes from the RTL.

Could the difference be in *which value is in which register at the compare*? The diff says the beq operands are a0,v1 vs v1,a0. If in mine the compare is `(eq p it)` — maybe because the C is `if (it == p)` but the *pseudo numbering*... no.

Let me look at the .s and the .sched/.cse dumps for q9 to see the comparison order. Then try `if (p == it)` and check whether the encoding flips (it didn't: score 1). Let me diff q14's instruction list to see if it's the same beq.

Actually, maybe the trick is the *order of the sets*: in mine, `it = B` comes before `p = it + K`? No — q9's C: test: p = it + K; it = B; if (it == p). But the target: test: it = B; beq it,p — with p computed in the delay slot *before* the test label. So the target's p computation is textually before `it = B`, but scheduled into the delay slot of the j. Mine (q9): p = it + K in the test block, then it = B, then compare — the p computation is in the same block as it = B. The scheduler placed p in the delay slot too (since only insn 8 differs, the addiu must be in the delay slot in mine as well). So the RTL order is the same.

So the only difference is the EQ operand order. How does GCC decide? In `expand_expr` (expr.c) for `EQ_EXPR`, there's:
```
if (GET_CODE (op0) == REG && GET_CODE (op1) == REG) ...
```
and in `do_jump`/`expand_cond`, there's code:
```
if (! (GET_CODE (op0) == REG || ...))
```
Hmm. Actually, GCC's `expand_cond` → `do_jump` → for EQ: `if (GET_CODE (op0) == REG && GET_CODE (op1) == REG) { ... }`. In 2.7.2's do_jump:
```
    case EQ:
      ...
      if (GET_CODE (op0) == REG && GET_CODE (op1) == REG) {
          ...
      }
      /* Fall through */
```
The operands come from `expand_expr (TREE_OPERAND (exp, 0), ...)` — source order. But `fold` may canonicalize the tree: for `it == p`, the tree is `(eq it p)`; no canonicalization.

But wait — there's `swap_condition` used when the target only has a branch for the reversed condition. MIPS has both beq/bne, so no.

Hmm, maybe the register *numbers* matter via `gen_rtx`? No.

Let me look at q9's .cse2/.sched to see the EQ operand order in the RTL, and compare with what would produce beq v1,a0. If the RTL is `(eq (reg 3) (reg 4))`, the .s would be beq $3,$4. Mine is beq $4,$3 → RTL (eq reg4 reg3). So the RTL order is p,it. Which means the tree was `p == it`?? But q9's C says `if (it == p)`. Unless GCC canonicalized the tree in `fold` (fold-const.c) — for comparisons, fold does `swap_tree_comparison` when the first operand is a constant. Not here.

OR: the `it` in the comparison is the *value set by `it = (s32)D_801202A0`*, and GCC's expand may have... 

Let me just try more spellings empirically:
- `if (p == it)` (q14): 1.
- `if ((s32)it == p)`: same.
- `if (it == (s32)p)`.
- Use a helper local: `s32 q = it; if (q == p)` — adds a move? maybe coalesced.
- `if (it - p == 0)` (q16): 1.
- `if (p - it == 0)` (q18): 1.
All 1. Maybe all produce the same encoding because GCC canonicalizes.

Maybe the difference is the *comparison's* operand order in the target arises from the target's C being `if (p == it)` and the *registers* being the other way: target's p=a0, it=v1, beq v1,a0 = (it,p) order. So target's C = `if (it == p)`. Mine = same → beq a0,v1 = (p,it). So GCC swapped in mine.

Why would GCC swap? Maybe because `it` is the *same pseudo* that was just set from a symbol and has a REG_EQUAL? The MIPS `beq` pattern might swap if one operand has a REG_EQUAL/constant? Both regs.

Hmm, could `combine` have swapped? The compare might be combined with the `it += 0x10C` or the `it = B` set? Let me look at the .combine/.cse dumps for the EQ.

Let me dump q9 and grep the RTL for the EQ.
