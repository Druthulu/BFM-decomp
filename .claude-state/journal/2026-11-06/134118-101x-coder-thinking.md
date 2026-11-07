---
ts: 2026-11-06T20:41:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rYkGcFQoNefhQlksPFXl
---
vH: `and a0,s0,a0` (with li a0,-4) instead of `move a0,s0` — 2 insns vs 1, so it's +1 insn (70 vs 69). Score 3. It's a mask, not value-preserving in general (well, it is for a 4-aligned pointer, but it's a change and emits an extra insn).

Hmm, but score 3 with 70 insns. The remaining diff: only the `li a0,-4; and` vs `move`. So if we could get the copy to be a `move` (not an and), we'd be at 0!

So the structure is otherwise correct! The `ent` pseudo is now distinct (allocated a0), and the schedule matches. We just need the operation to be a plain `move` (1 insn).

So we need a distinct-pseudo operation that compiles to a single move and isn't copy-propagated.

`and` with -4 is 2 insns (li + and). What about an operation that's a single insn and value-preserving: 
- `ent = (s32)a0 + 0` → folded to a copy (propagated).
- `ent = (s32)a0 | 0` → folded.
- `ent = (s32)a0 & -1` → folded.
- `ent = (s32)a0 ^ 0` → folded.

Hmm, what about `ent = (s32)a0 & 0xFFFFFFFF`? folded.

What about a shift: `ent = (s32)a0 << 0`? folded.

What about `ent = (s32)a0; ent = (s32)a0;`? no.

Hmm. But wait — the and version scored 3 with the register allocation RIGHT. The only difference is li+and vs move. What if we use a mask that the compiler can do in one insn and that's value-preserving for a pointer? On MIPS, `andi` can mask with a 16-bit immediate; -4 (0xFFFFFFFC) doesn't fit, so it needs li+and. What about `& 0xFFFC`? That's not value-preserving for a pointer (0x80xxxxxx & 0xFFFC loses high bits).

What about an operation with a register: `ent = (s32)a0 + zr` is the pin.

Hmm, what if we use a *signed shift pair*: `ent = ((s32)a0 << 2) >> 2;` — for a 4-aligned pointer, this preserves the value? No: shifting left by 2 loses the top bits (0x80xxxxxx << 2 overflows). No.

What about `ent = (s32)((u32)a0 & 0xFFFFFFFC)` — same as vH.

What if we use a cast that requires a move: `ent = (s32)(long)a0;`? On this target, `long` is 32-bit → no-op.

What about `ent = (s32)((u32)a0 >> 0);`? folded.

Hmm, so we need a value-preserving single-instruction operation. What operations are single-instruction and value-preserving on a 32-bit value?
- `move` (copy) — but copies are propagated.
- `addu a,b,$0` — needs the zero register (the pin).
- `or a,b,$0` — same.
- `and a,b,-1` — 2 insns (li + and).
- `xor a,b,$0` — same.

Hmm, what if the compiler can use a *register* known to be zero? E.g., `ent = (s32)a0 | (s32)(v[0] & 0);`? folded.

What about an operation with a value the compiler knows is 0 but must materialize: e.g., `ent = (s32)a0 + (s32)(v[0] - v[0]);`? If v[0] is loaded once, cse folds v[0]-v[0] to 0 → copy. If loaded twice, it's subu + addu (2 insns).

Hmm.

What about using the *constant 0* through a variable: `s32 zero = 0; ent = (s32)a0 + zero;` → the compiler propagates the constant 0 → folded to a copy → propagated.

Hmm.

Wait — but maybe the target's `move a0,s0` IS the pin's `addu a0,s0,$0` printed as `move`! The disassembler prints `addu a0,s0,zero` as `move a0,s0`. So the pin's add with $0 assembles to the same instruction as a move (addu dst,src,$0). That's why the target shows `move a0,s0`.

So we need an operation that assembles to `addu a0,s0,$0` — i.e., add with the zero register. In C without a register pin, we can't reference $0... unless the compiler materializes a zero in a register and adds. But gcc will fold `x + 0`.

So: `ent = (s32)a0 + <opaque 0>` where the opaque 0 compiles to a register holding 0. The compiler would need to load 0 into a register — that's `move tmp,$0` (1 insn) + addu (1 insn) = 2 insns. Unless the zero register is used directly.

So the pin on $0 is the only way to get `addu a0,s0,$0` in one insn without a materialized zero. 

Hmm, but wait: what about an expression where the compiler uses $0 directly for a zero operand? E.g., `ent = (s32)a0 + (s32)0;` folds. The compiler won't emit `addu x,y,$0` for `y + 0` because it folds.

What about `ent = (s32)((u32)a0 | 0u);` folds.

So the wall: the pin on $0 is load-bearing; a lever-free body can't produce `addu a0,s0,$0` because any add-with-zero folds to a copy, which cse propagates.

But hold on — the vH mask gives score 3 with 70 insns; the only difference is li+and vs move. What if we find a *single-instruction* value-preserving operation that isn't propagated? 

What about a *sign-extend* of a sub-word value that is a no-op... `ent = (s32)(s16)(s32)a0`? For a pointer 0x80xxxxxx, s16 truncation changes it.

What about `ent = (s32)((u32)a0 ^ 0x80000000) ^ 0x80000000;`? Two xors (2 insns) and folded.

What about `ent = (s32)a0 & 0xFFFFFFFC | ((s32)a0 & 3);`? That's a reassembly — 4 insns.

Hmm.

What about making `ent` an s32 and doing `ent = (s32)a0;` but preventing propagation by using `ent` in a way that requires a distinct pseudo... 

Wait — actually, maybe we can exploit the do-while: cse1's copy propagation is per-EBB. If `ent = a0` is in one EBB and the uses in another, cse still propagates via the register value table across blocks (cse1 handles jumps within the EBB and resets at labels). The do-while introduces a label. If the definition is BEFORE the label and the uses after, cse's value table is reset at the label → no propagation!

vB put the assignment inside the do-while (after the label) and the uses too. Let me try: assignment before the do-while, uses inside? The do-while currently wraps the first two stores. The assignment `s32 ent = ...` is before the do-while. The uses are inside the do-while and after.

cse1 processes the whole function's EBBs; the value table persists across the do-while? A do-while creates a loop; cse1 sees the jump and the label. At the label, cse invalidates the table (or keeps values that are unchanged). Since `ent` is not modified, cse could keep it... but copy propagation of a pseudo requires `reg_eqv` tracking.

Hmm, vB (assignment inside the do-while, first use inside) still gave 7. So cse propagated anyway (the assignment and first uses are in the same block).

Let me test: assignment OUTSIDE the do-while, and check whether the copy survives. That's the baseline (7) — the assignment is before the do-while. So no.

What if we put the assignment inside the do-while and move ALL uses inside too? The uses after the do-while (the many stores) would then be outside → ent live across the loop end. Copy-prop within the block still kills it.

Hmm.

OK, let me consider: is vH's 3 an acceptable crack? No: `& 0xFFFFFFFC` changes the value (though for a valid pointer it's the same) and adds an insn. It's also an identity-style launder (masking a pointer to its alignment). The brief bans identity-statement launders. And the insn count differs (70 vs 69), so it's not a match anyway.

What about a *single-instruction* op: `ent = (s32)a0 + (s32)(u8)0;`? folds.

Hmm, let me think about MIPS single-instruction value-preserving ops:
- `sll a,b,0` — gcc folds.
- `sra a,b,0` — folds.
- `ori a,b,0` — folds.
- `xori a,b,0` — folds.
- `andi a,b,-1` — doesn't fit the immediate.
- `addiu a,b,0` — folds (this is `addiu a0,s0,0`, which the disassembler would print as `addiu a0,s0,0`, not `move`).

Hmm, the target's instruction is `move a0,s0` = `addu a0,s0,zero`. So we need addu with $0.

What about a C expression that makes gcc emit `addu a,b,$0`? E.g., `ent = (s32)a0 + (s32)(0 & *(volatile s32*)...)` no.

OK — so item 4 is likely a WALL too: the $0 pin is load-bearing; real C can't force a non-propagated register copy, and the mask alternative costs an extra insn.

But wait — vH gives 3, which is better than 7 but not 0. For a WALL, best = lowest score of a lever-free body. vH is lever-free? It removed the pin and used `& 0xFFFFFFFC`. It's a real C body with no lever kinds. But is it a "crack"? No (score 3). So the best lever-free score is 3, not 7. Hmm, the WALL "best" should be the lowest score of a lever-free body — vH is lever-free (no pin/asm/barrier/launder) and scores 3. So best = 3.

But vH's `& 0xFFFFFFFC` is an identity-ish mask... The brief says identity-statement launders do NOT count as a crack. But for a WALL's "best", we report the best lever-free score. vH is a lever-free body (no row-kind levers), scoring 3. I'd report best 3.

Hmm, but is the mask a "new lever of any kind"? It's a real C expression (a mask), but it's an identity for aligned pointers — arguably a launder-equivalent. The expert might call it a new lever. To be safe, maybe I should report best 7 (the clean lever-free body) or 3 (the masked one). The WALL definition: "best = lowest score of a lever-free body". A body with an identity mask is not a lever of the pin/launder/barrier kind; but "no new lever of any kind" forbids adding levers. A mask is a C expression, not a lever per se... but it's clearly the kind of identity trick the brief bans ("identity-statement launders ... do NOT count as a crack").

I'll report best 3 with a note that the mask is value-preserving only for aligned pointers and not counted as a crack; the clean lever-free best is 7.

Hmm, actually let me try a few more things before deciding. Maybe there's a legitimate single-instruction value-preserving op that yields `move`.

Idea: use a *bitfield* or a cast through an enum? no.

Idea: `ent = (s32)a0;` where a0 is used via a different type that requires a conversion instruction... 

Idea: what if `ent` is `u32` and `a0` is `void *` — same.

Idea: what about `ent = (s32)a0 + (s32)v[3];` where v[3] is uninitialized? No.

Idea: what about using `v[0]` (loaded) as an addend: `ent = (s32)a0 + (s32)(v[0] - v[0]);`? Let me test — if gcc doesn't fold it (because v[0] is a memory load and it might not prove equality across two loads... cse would). It would emit `lhu`, `subu` (2 insns) → no.

Idea: `ent = (s32)a0 + (s32)(v[0] & 0);` — folds to 0 → copy.

Hmm.

Idea: use a *global* variable that's known zero at compile time: `ent = (s32)a0 + D_...` — a load.

OK. Another angle: maybe we can avoid the copy entirely and get the target's code by having the compiler use a0 for the base for a *different* reason. The target's `move a0,s0` is at ed4c; all subsequent stores use a0. What if the source used `a0` (the parameter) directly and the compiler, after the RotTransSV call, decided to move it to a0 because... no, it would keep it in s0.

What if the parameter's pseudo were dead after the first part, and a new variable `ent` (assigned from a0) were the only live thing? Still copy-prop.

Hmm, what if `ent` is assigned from `a0` *after* a0 is modified? Can't modify a0 (the parameter).

What if we pass `a0` to a function that... no.

OK, I'm fairly convinced this is a WALL. Let me spend a bit more time on a couple of ideas and then wall with best 3 (or 7).

Wait, actually — hold on. What about the `& 0xFFFFFFFC` scoring 3 with the RIGHT allocation? The only diff is li+and vs move. What if we use a mask that fits in an immediate and is value-preserving for the actual pointer? The pointer a0 is a heap/RAM pointer (0x80xxxxxx or similar). `andi` with a 16-bit immediate would clear the high bits — not value-preserving.

What about `ent = (s32)a0 & 0xFFFFFFFC` — 2 insns. Could the compiler use a single `andi` if the mask fits? No.

What if we use `ent = (s32)a0 & -4;`? same 2 insns (li -4, and).

Hmm, what if we use a *shift* that's a single insn and preserves the value for a known-aligned pointer: `ent = (s32)a0 << 0`? folded. `ent = (s32)((u32)a0 >> 0)`? folded.

What about `ent = (s32)a0 - 0;`? folded to a copy.

OK. What about making the compiler emit `addu a0,s0,$0` via a *pointer difference*: `ent = (s32)((u8 *)a0 - (u8 *)0);`? Pointer minus null — gcc might emit `subu a0,s0,$0` (1 insn, = move!). Let me test! `(u8*)a0 - (u8*)0` → gcc's pointer arithmetic: `(char*)a0 - (char*)0` might be folded to a0 or emit subu with zero. Worth a try.

Similarly `ent = (s32)(a0 + 0)` folds.

Let me test a few:
vI: `s32 ent = (s32)((u8 *)a0 - (u8 *)0);`
vJ: `s32 ent = (s32)((u32)a0 - (u32)0);`
vK: `s32 ent = (s32)a0 - (s32)0;`
vL: `s32 ent = (s32)((s32)a0 + (s32)((void *)0 == 0 ? 0 : 0));`? folds.

Let me try vI, vJ, vK.

Also vM: `ent = (s32)a0 ^ (s32)((u32)a0 & 0);` folds.

Let me test.
