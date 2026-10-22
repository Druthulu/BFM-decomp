---
ts: 2026-10-22T09:40:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YVSs3MM3WJ9UweBLLx6C
---
Now I see: at 2b7c "lh a0,256(s0)" → a0 = unk100 (loaded before the branch at 2b84). So in the else arm (2bbc), a0 = unk100 (not v0!). Then:

2bc8: bne v1,v0 (D_801E4BBC == 1?) → 2c0c
2bcc: sll v0,a0,0x3   (unk100*8)
2bd0: jal func_8018ABE0
2bd4: nop
2bd8: lh v0,14(v0)
2bdc: lh v1,14(s0)
2be0: move a1,v0
2be4: slt v0,v0,v1
2be8: bnez v0 → 2c68
2bec: nop
2bf0: lh a0,256(s0)     ; a0 = unk100 again
2bf4: li s1,1
2bf8: sh a1,14(s0)
2bfc: jal func_8018AEB4
2c00: move a1,zero
2c04: j 2c68
2c08: nop
--- else arm (2c0c):
2c0c: lui a1,0x0        ; &D_80195AF6
2c10: addiu a1,a1,0
2c14: lui at,0x0        ; &D_80195AF6
2c18: addu at,at,v0     ; at = &D_80195AF6 + v0
2c1c: lh v0,0(at)       ; newval

Hmm, v0 at 2c18! What is v0? At 2bbc-2bc0, v1 = D_801E4BBC value; v0 = ? From 2b94 "beqz v0" path... but we came from 2b84 bgez a0 → 2bbc. At that point v0 = ? The last write to v0 before 2bbc: 2b74 "li v0,-2048" (in the if-branch) or 2b58 "lh v0,10(s0)". Hmm, at 2b84 the branch is "bgez a0" → so unk100 >= 0.

Hmm, so what is v0 at 2c18? If the newval address = &D_80195AF6 + v0, and the element stride is 8, then v0 must be unk100*8. But there's no sll before 2c18!

Hmm, unless the address is D_80195AF6 + unk100 (i.e. the source is different!). Look: maybe the newval load is NOT `D_80195AF6[idx].f0` but something else, e.g. `*(s16 *)((u8 *)D_80195AF6 + idx)`. Hmm.

Wait, maybe v0 = unk100*8 was computed earlier and kept in v0 across the branch! Look at 2bcc: "sll v0,a0,0x3" — that's in the D_801E4BBC==1 arm (the func_8018ABE0 call), not in the else arm. Hmm, but v0 might be computed in a common block... no, 2bcc is after the branch at 2bc8.

Hmm, so in the else arm (2c0c), what is v0? Let's trace: the else arm is reached from 2bc8 (bne v1,v0 → 2c0c). Before 2bc8: 2bbc "lui v1" / 2bc0 "lhu v1,0(v1)" (v1 = D_801E4BBC) / 2bc4 "li v0,1" / 2bc8 "bne v1,v0,2c0c". So v0 = 1 at 2bc8!

So at 2c0c, v0 = 1 → "addu at,at,v0" = &D_80195AF6 + 1?? That would load the s16 at byte offset 1 — weird.

Hmm, that can't be right. Unless the "addu at,at,v0" is not what I think. Let me re-read: 2c18: 00220821 → opcode: 0x00220821 = addu $2,$1,$0 → addu at,at,v0 ✓ (at=$1, v0=$2). Hmm, but at 2c14 "lui at,0x0" with HI16 D_80195AF6.

Wait — maybe the lh at 2c1c has the LO16 relocation for D_80195AF6 (I saw "2c1c: R_MIPS_LO16 D_80195AF6"), meaning the displacement of the lh is the low part of the symbol, i.e. the address is `at + 0(lo)`. And "addu at,at,v0" adds v0.

Hmm so the address = D_80195AF6 + v0 where v0 should be the index*8.

Unless... the else arm is entered from 2bc8 with v0=1?? That's broken. Let me look again at 2bc4: "24020001 li v0,1" then 2bc8 "14620010 bne v1,v0,2c0c". So if D_801E4BBC != 1 → go to 2c0c with v0 = 1.

Then at 2c0c-2c1c: the newval load address = &D_80195AF6 + v0(=1)?? That's D_80195AF6+1 → lh → the s16 at offset 1 — misaligned. Weird but this is decompiled game code; the "f0" field of D_80195AF6[idx] where idx... hmm.

Hold on, maybe I misread the branch: "bne v1,v0,2c0c" — v1 = D_801E4BBC, v0 = 1. If D_801E4BBC != 1 → branch to 2c0c. Yes.

Hmm, so where does the index come from? unk100 is in a0 (loaded at 2b7c). The else arm at 2c0c doesn't reload unk100 until 2c34 ("lh v0,256(s0)").

So the newval load at 2c1c uses v0 = 1 as the offset?! That means the address is &D_80195AF6 + 1?? That can't be right semantically.

Unless the decompiled source's `D_80195AF6[unk100].f0` is wrong and the real code is different! Hmm, but our compile produces the same asm (except one insn) — so our source produces "addu at,at,v0" too, with v0 = 1 at that point?! That means OUR compile also computes the newval address as symbol + 1.

Hmm! Wait. Maybe v0 at 2c18 is NOT 1: the "li v0,1" at 2bc4 might be in the delay slot of the branch at 2bc8? The delay slot instruction after "bne v1,v0,2c0c" at 2bc8 is at 2bcc: "sll v0,a0,0x3" — which is the delay slot of the branch at 2bc8! So the branch at 2bc8 has delay slot "sll v0,a0,0x3" → v0 = unk100*8 ✓✓.

So v0 = unk100*8 when branching to 2c0c (the delay slot executes in both cases). Then at 2c18: "addu at,at,v0" = &D_80195AF6 + unk100*8 ✓ — the element stride 8 ✓.

And in the fall-through case (D_801E4BBC == 1), v0 = unk100*8 is used at 2bcc?? no wait: the delay slot instruction is at 2bcc = "sll v0,a0,0x3" — it executes in BOTH cases (delay slot). In the fall-through case (2bc4 li v0,1 → 2bc8 bne not taken → 2bcc delay slot executes → v0 = unk100*8) then 2bd0 jal func_8018ABE0 — hmm, but then the jal's argument a0 = unk100 ✓ and v0 = unk100*8 is dead there.

OK so now: in the else arm, at 2c18, v0 = unk100*8 — the SHIFTED index. So the newval address = &D_80195AF6 + unk100*8 (the element address) and lh at +0 → newval = D_80195AF6[idx].f0 ✓.

So in the target, the index unk100*8 is computed ONCE (in the branch delay slot) and used both for the newval address and later for the final address (at 2c48 "sll v0,v0,0x3" — wait, that's another shift!).

Hmm, at 2c34: "lh v0,256(s0)" (reload unk100) then 2c48 "sll v0,v0,0x3" → v0 = unk100*8 again. So the target computes unk100*8 twice: once in the delay slot (for the newval address) and once after the reload.

OK. So now, in the newval address, the tree is (plus symbol v0) where v0 = unk100*8 — a scaled index! And the target does NOT swap it: "addu at,at,v0" = (plus symbol idx) — symbol first ✓.

But OUR compile produced "addu at,at,v0" too (same) — so ours also has symbol-first there. And the final add in ours is "addu v0,v0,a1" (index first) while the target is "addu v0,a1,v0".

Hmm OK. So both the newval add and the final add have the same shape (plus symbol scaled-index) in the target, but ours differ! In ours the newval is (plus symbol idx) and the final is (plus idx symbol).

What's different between the two in ours? The newval's idx comes from a different computation path (the delay slot one) vs the final's.

Hmm, so it's not a systematic canonicalization — it's something local. Interesting.

In the target, the final add's pointer is in a1 — a REG. In ours, the final add's pointer is a1 too (materialized) but in the second position.

Hmm, so both have the pointer materialized into a1 in a register. The difference is the operand ORDER in the add. So at reload time, the tree in the target was (plus (reg a1) (reg v0)) and in ours (plus (reg v0) (reg a1)).

Wait, but that means in OURS the tree at reload time was (plus (reg idx) (reg ptr)) — index first! But the .cse dump showed (plus (symbol) (reg 118)) — symbol first. So the swap to index-first happened between cse and reload. Which pass? reload.c! (the commutative swap in find_reloads, side effect #1).

So: in ours, at reload time, the tree was (plus (symbol) (reg idx)) and reload swapped it to (plus (reg idx) (reg symbol)). Why? Because the symbol needs a reload (lui+addiu) and reload's commutative handling prefers to put the reloaded operand... hmm, it chose to swap.

And in the target, the tree was (plus (reg ptr) (reg idx)) — no swap needed.

Hmm, so in the target the pointer was a REG at reload time. In ours it was a SYMBOL_REF at reload time (cse substituted it).

So: cse's simplify_addr replaced the base REG with the constant in ours. In the target, cse did NOT do that.

WHY? Look at cse.c:2282: `base = qty_const[reg_qty[REGNO(base)]]` — the base must be a REG with a known constant. In the target, the pointer pseudo p... hmm, if the target's pointer pseudo had a constant equivalent, cse would substitute it too.

UNLESS in the target, the pointer pseudo was NOT recorded in cse's qty_const as a constant! Recall the recording condition (cse.c:1375): `if (elt->is_const && classp && GET_CODE (classp->exp) == REG && GET_CODE (x) != REG)` — i.e. when a reg is set to a constant, cse records qty_const for the class head.

Hmm, both should be the same...

UNLESS the target's pointer pseudo was NOT set to the symbol by an insn, but rather the symbol was the pseudo's initial value (e.g. the pseudo was a "constant reg" from the start)? Hmm.

OR: in the target, the address was NOT (plus (reg p) (reg off)) but something where the base was already a symbol (never a reg).

Hmm! What if in the target, the tree was (plus (symbol_ref) (reg idx)) at cse time (because the ORIGINAL SOURCE wrote the address with the symbol directly, e.g. `D_80195AF6 + ...`), and cse had nothing to substitute; and reload... hmm, but then reload would swap it as in ours.

Ugh, but ours ALSO has (plus symbol idx) at cse time and reload swapped it.

Wait, maybe I should check: what does reload do with (plus (symbol) (reg))? It creates a register for the symbol (a1) — the "lui a1; addiu a1,a1,0" — and then the add is (plus (reg a1) (reg idx)) or (plus (reg idx) (reg a1)) depending on the swap decision.

In the target, the same situation → the add kept the symbol first.
In ours → swapped.

The difference must be in the *reload decision*, which depends on the allocation context (which registers are free, the order of reloads, etc.). Since both our body and the target's have the same overall structure... hmm, but they're not identical: ours has the pointer as a local `p` variable (used once) and the target's original source might have differed in ways we can't know.

Hmm, hmm. But the project's def (with the launder) DOES produce the target. So the launder changes the tree to (plus (reg p) (reg idx)) (p is a hard-reg pseudo due to the asm) → no swap → target ✓.

So the question is: how to get the pointer into a REG at reload time without the asm lever?

Insight: cse's simplify_addr substitutes the base reg with its constant. But look at the condition at cse.c:2277-2284: it requires `qty_const != 0` and `REGNO_QTY_VALID_P (REGNO (base))` and `qty_mode[reg_qty[REGNO(base)]] == GET_MODE(base)`.

`REGNO_QTY_VALID_P` — the reg must have a valid quantity. Quantities are assigned by flow analysis: a reg that is used in a way that requires a distinct quantity (e.g. used with different modes, or set in multiple places) gets its own quantity. If the pointer pseudo has its own quantity and a constant equivalent → substitution.

Hmm, what if the pointer pseudo's *mode* at the use differs from the mode at the set? E.g. if p is declared as `u8 *p` (mode = pointer, same). Hmm.

What if the pointer is used in a *64-bit* context? no.

What if the pointer pseudo is set to the symbol in one place and the symbol_ref is used elsewhere...

Hmm, what about this: the substitution happens in simplify_addr, which is called from cse's `simplify_mem`/`fold_rtx`? For our MEM source (the load's address), cse calls `fold_rtx (dest, insn)` for MEM destinations; for sources, cse calls `simplify_rtx`? Hmm. The .cse dump shows the substitution already.

Practical approach: try to make cse NOT substitute by making the pointer's *class* not constant. How about: the pointer is assigned the symbol AND the symbol is also used directly elsewhere in the same function (the newval load uses D_80195AF6 directly!). That doesn't affect p's class.

What if p is assigned in a way that yields TWO sets: e.g.
```c
D_80195AF6_t *p;
p = D_80195AF6;   /* one set */
```
vs. the initializer (also one set).

What if p is set to the symbol AND to itself?

Hmm, what if p is a **register variable**? Not allowed (register vars are a lever? "no `register` vars" per the constraints).

What if the pointer's value is used in a context where the *mode* differs: e.g. `p` used as `s32` somewhere: `D_801270C8 = *(s16 *)((u8 *)p + off + 4);` — the pointer is used in pointer mode.

Hmm, what about making the pointer a **u64**? no.

What about: the address is computed as `(u8 *)p + off + 4` where p is `D_80195AF6_t *` — the cast (u8*)p is a no-op. But what if p were declared as `s32 p = (s32)D_80195AF6;`? Then the address = (u8 *)(s32)p + off → the cast from s32 to a pointer: gcc 2.7 would emit (set p (symbol_ref))? The mode of p is SI, and the symbol in SI mode... gcc 2.7 might keep (symbol_ref) with a "CONST" wrapper. Then the address's base = (reg p) with mode SI → the qty_mode check requires qty_mode == GET_MODE(base) = SI ✓ → substitution still happens. Hmm.

Wait — actually! Look at the qty_mode check: `qty_mode[reg_qty[REGNO(base)]] == GET_MODE(base)`. If the pointer is set as a pointer (mode = pointer, which in gcc 2.7 is a 32-bit integer mode — same as SI) — same.

Hmm.

OK, radical alternative: maybe the trick is to make the ADDRESS NOT have the pointer as the base, but rather have the tree be (plus (symbol) (reg idx)) where the symbol is NOT substituted by cse because the base was never a reg — and then prevent reload from swapping.

Reload's swap: it swaps when it "thinks the instruction will compile better that way". The swap happens for commutative insns to try alternatives. In our case, the add's operands: (symbol → needs reload into a reg) and (reg idx). Reload tries the unswapped order first; if the allocation is bad, it tries swapped.

Hmm, so both orders are tried and the better one wins. In the target, the unswapped won; in ours, the swapped won. The difference might be the register pressure/allocation context!

So maybe a small change elsewhere in the body could flip the allocation decision so that the unswapped order wins. E.g. changing the order of statements, or the number of live values. Hmm, but the rest of the function must match exactly.

Hmm! But wait: in the target, the pointer at the add was a PSEUDO (not a symbol) — because "lui a1; addiu a1,a1,0" appears at the ARM START (2c0c-2c10), i.e. the pointer was materialized into a1 early and kept there across the arm. If the pointer had been a symbol_ref at reload time, reload would materialize it right before the add (at 2c48-ish), not at the arm start.

In ours, we ALSO have "lui a1; addiu a1,a1,0" at the arm start! So in ours too, something was materialized into a1 early. What? Possibly the newval address's symbol (reload creates a reg for the symbol in the address at 2c14 → but that's `at` in the target). Hmm, in ours: "lui a1; addiu a1,a1,0; lui at; addu at,at,v0; lh v0,0(at)". So a1 = symbol (materialized early), at = symbol (for the newval address).

In the target: same! "lui a1; addiu a1,a1,0; lui at; addu at,at,v0; lh v0,0(at)".

So both have a1 = symbol materialized at the arm start. In the target, a1 is the pointer used at the final add; in ours, a1 is also used at the final add (as the second operand). So in ours, a1 IS the pointer register (materialized early, used late) — the only difference is the operand position!

So in ours, the pointer IS a pseudo in a1 (allocated by reload, materialized early). But at the add, the tree had (plus (symbol) (reg idx)) → hmm, if the pointer pseudo were in a1, the tree would be (plus (reg a1) (reg idx))...

Unless: the "lui a1; addiu a1" in ours comes from the *symbol* being materialized for the newval address (which needs a reg) — but that's `at` in both. Hmm, so what is a1 in ours?

Let me look at OUR full asm and compare with the target's side by side. Earlier I printed our candidate asm lines 55-95 and the target's 55-105 — they matched except the one add. Let me diff them properly to see if there are other differences (the score says 1 mismatch, so they're identical except that insn).

So both have "lui a1; addiu a1,a1,0" at the arm start and use a1 in the final add. In ours the add is "addu v0,v0,a1", in the target "addu v0,a1,v0".

So the trees at reload time differ only in operand order: ours (plus (reg idx) (reg a1)), target (plus (reg a1) (reg idx)).

And the cse dump of ours shows (plus (symbol_ref) (reg 118)) — symbol first. So the swap happened in reload: reload swapped the symbol-first into index-first.

In the target, the tree at cse time was presumably (plus (reg p) (reg idx)) — with p a pseudo — so reload had no symbol to reload and no swap was needed.

So: in the target, the pointer pseudo was NOT replaced by the constant by cse. Why?

Hmm! Maybe because in the target's original source, the pointer was NOT a local variable at all but the address was written as `D_80195AF6 + ...`? Hmm, but then the tree would be (plus (symbol) (reg idx)) — symbol first — and reload would swap it like ours.

Unless the original source wrote the address as `(u8 *)&D_80195AF6[0] + off + 4` hmm same.

Wait wait wait. What if the original source's pointer was a *parameter*? No.

What if the original had `p` as a *global* pointer variable? Then p's value is a load — no.

Hmm, what if in the target the pointer came from the *same* expression as the newval (i.e. the compiler CSE'd them)? E.g. if the source was:

```c
D_80195AF6_t *p = D_80195AF6;
s16 newval = p[idx].f0;
...
D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
Then p has 2 uses → cse does NOT substitute the constant (because the quantity has multiple uses? hmm, actually cse's qty_const substitution in simplify_addr doesn't depend on the number of uses...).

Hmm, but the resulting asm for that source: the newval address = (plus (reg p) (reg idx)) → p materialized into a1 → "addu at,a1,v0"? But the target has "lui at; addu at,at,v0" — a separate materialization of the symbol into `at`! So p was NOT used for the newval address in the target.

Unless gcc materialized the symbol twice: once into a1 (for p) and once into at (for the address) — that happens if the *symbol* is needed in two places: e.g. the address (plus (symbol) (reg idx)) [needs the symbol in a reg: at] and the final add (plus (reg p) (reg idx)) [needs p in a reg: a1] — that's exactly the target's asm: TWO materializations of the same symbol!

So in the target: the newval address used the SYMBOL directly (folded), and the final add used a PSEUDO p (not folded). Both materialize the symbol, hence two lui/addiu pairs ✓✓.

So in the target, cse substituted the symbol into the NEWVAL address (where the base is the symbol directly — no substitution needed) but did NOT substitute p's value into the final address.

So the difference is entirely about p: in the target, p's pseudo was NOT replaced by the constant; in ours it was.

Now: WHY? The cse substitution happens in simplify_addr when the base REG has a constant equivalent (qty_const). The recording of qty_const happens when the reg is set to a constant.

Hmm, unless in the target the pointer pseudo was set to the symbol in a way that cse did NOT record as a constant — e.g. if the set was `(set (reg p) (symbol_ref))` where the symbol_ref has a different mode, or if there were TWO sets.

OR: the target's p was NOT set to the symbol by an insn at all! What if p's value came from a *pseudo initialized* by the front end with a "const" — i.e. the front end created the pseudo with the constant value directly? Hmm, in gcc 2.7, a local variable initialized with a constant address: the front end creates a VAR_DECL; expand creates a pseudo and a set insn `(set (reg p) (symbol_ref))` — as we saw (insn 176 in our dump). And cse records qty_const.

So the target should behave the same... unless the target's original source had the pointer as a **parameter** of an inlined function? no.

Hmm hold on, maybe I have it backwards! Maybe in the target the pointer pseudo p was NOT the base of the address; instead the address was built as (plus (symbol) (reg idx)) — i.e. the ORIGINAL SOURCE wrote the address with the SYMBOL, and the "p" variable in our decomp is an artifact!

But then in the target, the final add would be (plus (symbol) (reg idx)) → reload materializes the symbol into a reg → and the swap question arises again (same as ours). BUT: the difference between the newval address and the final address in the target would then be: newval = symbol + idx*8 (the idx scaled by 8 from the delay slot) vs final = symbol + idx*8 + 4.

Hmm! Wait: in the target, the final add's index is v0 = unk100*8 (from "sll v0,v0,0x3" at 2c48) and the add is "addu v0,a1,v0" with a1 = the symbol. And the newval add: "addu at,at,v0" with at = symbol and v0 = unk100*8 (from the delay slot). Both are (plus symbol scaled-index)! One has the symbol first (at,at,v0 = symbol first? "addu at,at,v0" → dest=at, op1=at(the symbol), op2=v0 → (plus symbol idx) ✓ symbol first) and the other (addu v0,a1,v0 → dest v0, op1=a1(symbol), op2=v0(idx) → (plus symbol idx) ✓ symbol first).

So in the TARGET, BOTH adds are (plus symbol idx) — symbol first! And in OURS, the newval add is (plus symbol idx) [symbol first ✓] but the final add is (plus idx symbol) [swapped].

So the target has a1 = the symbol materialized at the arm start (2c0c) and used at 2c4c; ours has a1 = the symbol materialized at the arm start too, but the add order is swapped.

So the trees are the same shape; only reload's swap decision differs! In the target, reload did NOT swap; in ours, it DID.

Why? Because in ours, the base was substituted by cse (the pseudo → symbol), while in the target the base was... hmm, in the target the base must ALSO have been substituted (since the symbol appears in the tree).

Hmm, unless in the target the base was a symbol from the START (the source wrote the symbol directly), and in ours it became a symbol via cse's substitution. Would reload treat them differently? Maybe! If the tree is (plus (symbol_ref) (reg idx)) in both cases, no difference.

BUT: there's a subtlety — cse's substitution replaces the base reg with the symbol INSIDE the MEM address, and the MEM's address then becomes (plus (symbol) (reg idx)). If instead the source wrote the symbol directly, the address would be... the same.

Hmm, so why the different reload decisions?

Maybe the difference is not in the tree but in the ALLOCATION: reload's swap decision depends on which registers are available and what else is live. In the target, at the final add, the live values were: a0 (unk100), s1, s2, a1(ptr)... In ours: same.

Wait, maybe the difference is the *number of instructions* or the ordering: in ours, the "lui a1; addiu a1" materialization happens at the arm start — meaning reload created a1 for the pointer early. In the target, the same. So reload allocated a1 for the symbol in both.

Hmm, so in the target reload did NOT swap, in ours it did. The swap decision in reload (find_reloads) tries the alternatives and picks based on "how many reloads are needed" and the register allocation quality. If in ours the unswapped order would need MORE reloads (e.g. because the index reg v0 is needed elsewhere), reload would swap.

Specifically: in the unswapped order (symbol first), reload needs a register for the symbol → a1 (free) and the index → v0 (free?). In the swapped order, the symbol → a1 as well. Hmm, same.

Honestly, maybe the real difference is something else entirely: maybe in the target the pointer pseudo was NOT substituted by cse, and the "lui a1; addiu a1" at the arm start came from the *pseudo* p being allocated to a1 by reload (a pseudo needs a reg: reload allocates a1 and materializes the symbol). While the newval address's symbol → `at`. Then the final add's tree = (plus (reg a1) (reg v0)) → no symbol in the tree → no swap → "addu v0,a1,v0" ✓.

And in OURS, the tree at reload time = (plus (symbol_ref) (reg 118)) → reload needs to materialize the symbol → and its commutative handling swapped the operands (perhaps because for a commutative MIPS insn the "memory-ish/base" operand should be second — the symbol is like a base!).

So the crux remains: keep p as a pseudo (don't let cse substitute the constant).

So: how did the target keep p as a pseudo? Because cse's simplify_addr substitution requires the base REG to have a constant equivalent (qty_const). qty_const is recorded when cse sees the reg set to a constant.

Hmm, in our compile cse DID record it. What's different in the target?

IDEA: What if the pointer pseudo in the target was set to the symbol by an insn that cse didn't see as a "set to constant" — e.g. if the set was `(set (reg p) (symbol_ref))` where the symbol_ref is in a *different mode* than the reg? Hmm.

IDEA 2: What if the target's pointer p was set to the symbol BEFORE a call and used after — no.

IDEA 3: What if p's set insn was in a different basic block and cse's flow analysis... no.

IDEA 4: What if the target's source had the pointer variable declared as `D_80195AF6_t *p = D_80195AF6;` but the USE was through a cast that changed the mode: e.g. `(u8 *)p` — the cast is a no-op in pointer mode.

Hmm, what if the use was `(u8 *)(s32)p`? Then the base reg's mode at the use would be SI (integer) while the set was in pointer mode → in gcc 2.7, pointer mode == SI? For MIPS, Pmode = SImode. So no difference.

IDEA 5: What if the pointer was used as a *base* of a MEM whose mode differs...

IDEA 6: What if the source used a **pointer-to-pointer** or a struct member?

Hmm, let me look at this from the "what does cse's simplify_addr do" angle again:

```c
  if (GET_CODE (base) == REG
      && qty_const != 0
      && REGNO_QTY_VALID_P (REGNO (base))
      && qty_mode[reg_qty[REGNO (base)]] == GET_MODE (base)
      && qty_const[reg_qty[REGNO (base)]] != 0)
    base = qty_const[reg_qty[REGNO (base)]];
```

`REGNO_QTY_VALID_P (REGNO (base))` — the reg must have a valid quantity. In gcc 2.7's flow analysis, each reg gets a quantity; `REGNO_QTY_VALID_P` is true if the reg has a quantity (reg_qty[regno] valid). Hmm, for a pseudo used in a single set and single use, the quantity is shared.

`qty_mode[reg_qty[REGNO(base)]] == GET_MODE(base)` — the quantity's mode must match the base's mode. If the pseudo's quantity has a different mode than the use... e.g. if the pseudo p was used in TWO different modes (pointer mode and integer mode), flow would give it TWO quantities (reg_qty differs) — hmm, but then the quantity at the use site is the one for that mode.

Interesting: `qty_const[reg_qty[REGNO(base)]]` — the constant is recorded per quantity. So if p's quantity (in pointer mode) has a constant equivalent, substitution happens.

What if p is used in a context where the MODE is different from the mode in which it was set? E.g. p set as a pointer (Pmode = SI) and used as... same.

OK, let me try yet another approach — EMPIRICAL: try to make the substitution not happen by using p in a way that cse can't fold, e.g.:

(a) Use p in TWO places (newval + final). Then cse's qty_const is still recorded, but maybe the *use count* matters elsewhere (in cse's main loop, a reg with a constant equivalent is replaced by the constant only in certain cases).

Actually! Remember the moves.md note: "cse: single-set const addr r73 folded into lone use lbu 73(sym) even past a 2-use join label; s1 never held" — "single-set ... folded into LONE use". So the fold happens for a LONE use! With 2 uses, cse might NOT fold!

That's the classic gcc rule: cse replaces a reg with its constant equivalent only if the reg has a single use (otherwise the constant would be recomputed). Actually the rule in gcc's cse (the `is_const` class handling): when a reg is set to a constant, cse can replace uses with the constant; but for regs with multiple uses it must keep the set.

So: if p has 2 uses, the substitution might not happen → p stays a pseudo → the add would be (plus (reg p) (reg idx)) → "addu v0,a1,v0" ✓ TARGET!

And the second use must not change the asm! The newval load currently uses the symbol directly: `D_80195AF6[idx].f0`. If I change it to `p[idx].f0`, the address becomes (plus (reg p) (reg idx)) → the newval load's address would use p (in a1) instead of materializing the symbol into `at` → we'd lose "lui at" → count 110 ✗.

Hmm! But wait: what if the second use of p is in a context that produces the same asm? Hmm.

What if p is used twice in the SAME final expression? E.g. `(u8 *)p + off + 4` uses p once. What about `*(s16 *)((u8 *)p + off + 4)` — one use.

Hmm, what if we add a second use of p that produces NO code: e.g. `p = p;`? Not allowed (identity laundering) and also it's a self-assignment (gcc folds it, and it doesn't create a second use at cse time... actually `p = p;` creates a set insn (set p p) — hmm, that's a use+set; cse would then see p set twice).

What about using p in a comparison that's always true: `if (p != D_80195AF6) { }`? gcc would fold it (both are the same constant) → no use remains.

Hmm, what if p is used in a context that generates a *different but harmless* instruction? The count must stay 111 and all insns identical. Ugh.

Hmm, BUT: maybe the second use could REPLACE the symbol use in the newval load, and the "lui at" could still appear! Let's think: if the newval address = (plus (reg p) (reg idx)) with p in a1 → "addu at,a1,v0" (no lui at). The target has "lui at; addu at,at,v0" — so the target's newval address has the symbol in `at`.

Unless the newval load's index (idx*8) is a different value than p+idx*8...

Hmm, hold on! What if we use p twice in a way that BOTH uses are the same address expression, and cse's CSE then shares? Like:
```c
D_801270C8 = *(s16 *)((u8 *)p + off + 4);
```
plus another use of p that produces the same address...

Hmm.

Alternatively: what if we give p a second use that is FREE because it's in a dead branch? E.g.
```c
if (0) { D_801270C8 = *(s16 *)((u8 *)p + off + 4); }
```
gcc removes the dead branch early (before cse) → no second use at cse time. Hmm.

What about a use in a *constant expression* context that survives to cse but generates no code? E.g. `off = (u32)(p - p);`? Hmm, that's a laundering-ish identity. `p - p` = 0 → gcc folds it to 0 at expand → no use.

Hmm. What about the "sizeof"-style tricks? no.

Let me reconsider: maybe cse's fold requires the reg to have a LONE use *in the whole function* or in the block. If p had 2 uses but one of them is in a different basic block... hmm, the fold in simplify_addr is per-address.

Hmm, let me look at the actual cse code that decides to substitute. The relevant part might be in cse's main loop: "record_eq_reg" / the `is_const` class. Let me look at cse.c around line 1375 again and the `is_const` flag semantics, plus where qty_const is used for substitution in the main loop (not simplify_addr).

Actually, we know the substitution happened via simplify_addr (base replacement). Let me look at the caller of simplify_addr to see if there's a use-count condition. Let me find calls to simplify_addr in cse.c.
