---
ts: 2026-10-22T16:05:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Rluhb9qF2mMmOvsPKmWG
---
In .rtl (before any pass), insn 21 sets reg 80 = fp+16 and the movstr dest is `(mem:BLK (reg 80))`. So **expand_block_move itself** creates the destination address register (copy_addr_to_reg) and uses it as the movstr dest. Then cse substitutes reg 80's REG_EQUAL (plus fp 16) into the movstr dest and into the calls' a1 copies — but the *pseudo reg 80 remains live* (it's used by the calls, and cse's REG_EQUAL on a1 = reg80). So reg80 is a real pseudo that local-alloc assigns s1.

So the block move creates the dest address pseudo. To avoid it, we must avoid expand_block_move.

Can we force the copy to be done element-wise but from a register source? The source register only appears if the source address is not a constant-foldable expression. That's the cse-const-addr wall.

Hmm, BUT: the target's code has the source base in a1 and 8 loads with offsets, plus stores at sp offsets. That is exactly what element-wise stores from a register source would produce. How did the original (ROM) compiler get the source address into a register without an asm? Maybe the original C used a *local pointer variable assigned from a function call* or a *struct pointer* that cse couldn't fold? Or maybe the original C used a block move too and the *target* is from a different GCC? No, same compiler.

Wait — maybe the target's C used a block move into a *pointer variable* target: `*(Mat32 *)m = D_800AE620;` — we did that. Hmm.

What if the destination of the block move is written such that expand_block_move's `copy_addr_to_reg` result is the *same* pseudo as an existing one? E.g. if the destination is a *register* pointer variable that already holds the address, then expand won't create a new pseudo:

```
int *d = m;          // d = &m  (a pseudo set once)
*(Mat32 *)d = D_800AE620;   // dest (mem (reg d)) -> copy_addr_to_reg(d) = d, no new insn
RotMatrixX(..., (void *)m);  // uses &m again
```
Then d is a pseudo holding &m, used by the movstr. But then d would still be a register (s1) and the calls would use it... unless cse substitutes. Hmm, but the target has NO register holding &m. So the block move's dest base must not be a register at all. 

Wait, how does the target store the 32 bytes to m then? `sw v0,16(sp)`, `sw v1,20(sp)`... using sp offsets. So the target's block move (if any) had the dest as a sp-relative MEM without a base register. But our expand_block_move created a base register for the dest. Why? Because the destination is `(mem:BLK (plus fp 16))` — the movstrsi_internal pattern requires the destination to be `(mem:BLK (reg))`? Let's look at the mips movstrsi_internal pattern: it requires the destination address in a register (operand 0 is `(mem:BLK (match_operand 0 "register_operand"))`). So expand_block_move does copy_addr_to_reg. Then after the movstr expands (in the movstrsi_internal split), the addresses are used with offsets from that reg. But in our final code, the dest stores use sp offsets — because the movstr expansion uses the dest reg as a base with offsets... Hmm, but the movstr dest reg 80 = fp+16 was substituted by cse with (plus fp 16)? Then the expansion would use fp as base with offset 16+k. That's what the .s shows.

OK so the block move inherently creates a dest address register. So the target's C is NOT a block move (no movstr). The target must be element-wise.

So we're back to: element-wise stores from a *register-held* source base. The source base must be a pseudo. How?

The source is `&D_800AE620` — a constant. cse folds it. Unless... the source base is a *stack/parameter* value? No.

Hmm, but wait! What if the source is a *struct-typed global accessed as a whole* in a copy into a *local struct variable that then is used element-wise*? No, that's the block move again.

What if we do the copy element-wise from a struct *pointer* that is assigned from the address of a *parameter-derived* value? The address D_800AE620 is fixed.

What about making the source base a *union member* of a global: `((Mat32 *)&D_800AE620)->w0` — same constant.

What about `extern Mat32 D_800AE620;` and use `D_800AE620.w0` etc. — constant per field.

Hmm, how did the ROM compiler ever hold the base in a1? Perhaps the original C had a *local pointer variable* `p = &D_800AE620;` and the loads through it, and the compiler at -O2 (without cse's address folding?) kept it. But we know that with the launder removed, our compiler folds. Unless the *declaration* of p as a different type or the *initialization* order changes cse's decision. E.g., if `p` is assigned *inside* the if after the branch, cse's equivalence from the assignment `p = symbol_ref` is a REG_EQUAL, and find_best_addr may rematerialize.

Hmm, but the moves mention MATCHes where a real 2nd set of the pointer kills the equivalence. E.g. "pv = *p; pv &= 0xFF000000 split". Here we could give `src` a *real second set* that produces the same value:

```
src = (int *)&D_800AE620;
src = (int *)((int)src + 0);   // identity — forbidden? "identity address spellings do NOT count as a crack"
```
Hmm, identity address spellings don't count. But what about a non-identity real computation that yields the same address? Like computing the address from its parts? Not possible in C.

But wait — is the forbidden thing the *identity* itself, or is it "identity-statement launders ... do NOT count as a crack"? The intent: don't cheat with `w = (w>>16<<16)|x` etc. A real second set like `src += 0` is an identity → forbidden.

What about using the fact that `D_800AE620` is an extern `Mat32` and writing `src = &D_800AE620.w0;` — same address, cse folds.

Hmm, what if the loads are done through a *volatile* pointer? Then the compiler must reload each element but the base could be a register. Volatile changes semantics but the ROM code has no volatile. Would it generate `lui/addiu` once then `lw` from volatile? Volatile MEMs still use the same address; cse would fold the constant too. Actually with volatile, GCC might keep the base in a register? Unlikely to match exactly.

Let me look at the target's full disassembly to be sure about the loads and stores. Let me dump the target with dump.py (needs a candidate object; I can dump just the target). Then I'll see the exact target sequence including prologue.

Actually the diff already told me the target's prologue and copy. Let me get the full target listing to reason about the intended C.

Let me run dump.py with the tu and fn (no candidate).

Wait, dump.py needs `oracle.baseline_path(rec['obj'])`; recs_for for the header TU. Let me just run it.

Actually, the diff is enough: target prologue uses s1 for self, s0 for obj, and addiu a1,sp,16 at each call. Copy: lui a1; addiu a1; lw v0,0(a1); lw v1,4(a1); lw a0,8(a1); sw v0,16(sp); sw v1,20(sp); sw a0,24(sp); lw v0,12(a1); ... So the stores are at sp+16..sp+44 and loads from a1+0..a1+28. This is element-wise (or a movstr whose dest base was sp, not a reg).

Interesting: could a movstr produce stores with sp base directly if the destination address pseudo is *eliminated* by cse and the movstr expansion uses the substituted address (plus fp 16)? In our case the movstr dest was `(mem:BLK (plus fp 16))` after cse substituted reg80. Then the movstr expansion should use fp+16+off. And indeed our final code has the stores at sp offsets (matched!). The only leftover is the *pseudo reg 80* being live for the calls (a1 = reg80). cse substituted reg80 into the movstr dest but kept reg80 for the a1 copies because... the a1 copy `(set a1 (reg 80))` has REG_EQUAL; cse could have substituted reg80 there too (a1 = fp+16). Why didn't it? Because cse only substitutes a reg into a MEM address, not into a plain register copy? Actually cse would replace reg80 in `(set a1 (reg 80))` only if reg80 is not live... no, cse replaces registers with their constant equivalence in *insns* (it does replace in general: `(set a1 (reg 80))` → `(set a1 (plus fp 16))`? That would require a PLUS expression in a SET, which is fine). Hmm, cse's folding of a REG_EQUAL into a SET is done when the expression is a constant (`fold_rtx`). It doesn't replace a register with a PLUS expression generally? Actually it can, if the expression is "cheap". It did replace it in the MEM (movstr dest). Hmm, inconsistent.

So the residual reg80 exists because expand created it. If the C avoids the block move, no reg80.

Therefore: element-wise stores + register source base. How to get the source base into a register without a launder?

Idea: use a *local struct variable* as the copy source: no.

Idea: make the source base a *function of* a value that is already in a register. E.g., the function has `self` (a0) in s1. Could we compute `&D_800AE620` from... no.

Idea: use `Mat32 *src;` and set it via a *conditional*: `src = obj ? (Mat32 *)&D_800AE620 : (Mat32 *)&D_800AE620;` — cse folds the conditional (same value both arms). Forbidden as identity anyway.

Idea: set `src` twice with different expressions that are both the same constant — cse would still equate (symbol_ref). Real second set of the same constant is still a constant equivalence.

Hmm. What about making the source *not* a symbol_ref but a value loaded from memory? E.g., if there were a global pointer variable holding the address. Is there one? `D_800AE620` is `extern Mat32` (an object). No pointer alias.

But maybe we can use the *address of a member*: `(int *)&D_800AE620.w0` → same symbol.

What if we use `(int *)((char *)&D_800AE620)` → same.

OK, so real C can't avoid cse folding a constant address unless the address computation involves a non-constant. Hmm, but the moves list shows many launder MATCHes cracked by real C. E.g. func_801A31CC: "pointer reuse: a1 = (u8 *)link; *(s32 *)a1 = 0; keeps the store base in the link reg". That's when the address is a *variable* (link), not a constant. For constant addresses the wall is cse-const-addr (several WALL entries). So item 1 might be a genuine WALL for the launder... but wait, the target's code shows a register-held constant address. The ROM compiler did it. Why can't ours? Because the ROM's C had *something* that prevented cse folding.

Hmm, hold on. Maybe the ROM's C used the movstr (block move) and the target's reg was... no, target has no &m reg, but the *source* base a1 comes from a movstr source pseudo (reg 81 = symbol) — and in the target, the movstr source base is a1! In our c_struct, the movstr source is reg81 = symbol_ref (a1) — matches target! And the dest base reg80 = fp+16 is extra.

So the target could indeed be a movstr, with the *destination address not in a register*. How? If the C's copy destination were a *register pointer* that already holds sp+16... no, that'd be a reg.

OR: if the movstr's destination were written so that expand_block_move does NOT call copy_addr_to_reg because the address is already a register or a simple MEM? Let's look at GCC 2.7.2's expand_block_move: 

```
if (GET_CODE (orig_dest) == MEM && GET_CODE (XEXP (orig_dest, 0)) == PLUS && ...)
```
Actually mips expand_block_move:
```
  if (TARGET_MIPS16) ...
  /* If the move is small, use a loop... */
  ...
  if (GET_CODE (src) == MEM && GET_CODE (XEXP (src,0)) == PLUS) ...
```
Let me read the actual source: tools/bin/gcc-2.7.2-psx? The gcc source may not be present. Hmm.

But the fact: our movstr dest is `(mem:BLK (reg 80))` where reg80 = fp+16 — so expand did copy_addr_to_reg on the dest. The mips movstrsi_internal pattern's operand 0 is `(mem:BLK (match_operand:SI 0 "register_operand" "r"))` — so a register is required. And the source is `(match_operand 1 "register_operand")` too. So both must be regs.

Then the *target's* movstr would also have dest in a reg... unless the movstr was split before register allocation and the dest reg was optimized away (cse substituting it into the movstr and then the movstr split uses the expression). That's exactly what happened for the *dest* (cse substituted reg80 into the movstr), but reg80 remained live because of the 3 call uses. In the target, if the calls' address was NOT the same pseudo, reg80 would die after the movstr and the split would use fp+16 offsets... but the calls still need fp+16 (addiu a1,sp,16 each) — those are *different* pseudos created at each call (expand sets a1 = address). 

So: if the calls' `(void *)m` address expressions were created *after* the copy in a way that cse doesn't merge with the copy's dest pseudo, then reg80 dies after the movstr (dead) and the calls get fresh addiu. How to prevent cse from merging? Make the address expression in the calls differ syntactically from the copy dest. But both are &m...

Wait, maybe use a *separate array* for the outgoing copy! Look at the code: `*(Mat32 *)(obj + 0x34) = *(Mat32 *)m;` — this copies m to obj+0x34. The calls use m. What if the copy destination is a *different* local that is then... no, that changes code.

Alternatively: what if the copy is into `m` via a *pointer variable* `d` that is set *from m* and the calls use `m` directly? Then the movstr dest address pseudo = d, and the calls use &m. cse sees d = &m (REG_EQUAL) and may substitute &m into the movstr dest, but d is used only once (by the movstr) so d dies; and the calls' &m pseudo... cse might still create one reg for the 3 calls? In w1, the 3 calls each got their own addiu (no shared reg) — so cse does NOT create a reg for the call addresses when there's no store MEM sharing the address. 

So the key is: make the copy's dest address a *different pseudo* from the call addresses, so that after the movstr, no shared pseudo survives. But cse will still substitute d's equivalence into the movstr and keep d live only if used elsewhere. If d is used only by the movstr, d dies. The calls use &m directly (fresh pseudos). Then cse might merge the call addresses with the *movstr dest expression* (plus fp 16)? The movstr dest is a MEM; cse's find_best_addr could create a reg for it because the same address appears in the calls. Hmm, but in w1 the stores (MEMs at plus fp 16) + calls did not create a reg. So the memstr's MEM shouldn't either — but expand created the dest reg before cse anyway. If d is dead after the movstr, cse's substitution leaves the movstr with (plus fp 16) and d dead → deleted. Then the calls get their own addiu. That's the target!

So candidate: 
```
int *d = m;
*(Mat32 *)d = D_800AE620;
RotMatrixX(..., (void *)m);
...
```
Hmm, that's `d2` variant — I tried `{ Mat32 *d = (Mat32 *)m; *d = D_800AE620; }` and it scored 19, same. Hmm. But in d2, `d` is a local pointer to int, and the copy dest is `*d` — expand still creates a reg for the dest address (which is d itself, a register! since d is a pseudo). Actually if the dest address is `(reg d)`, expand's copy_addr_to_reg(d) = d, no new insn. Then the movstr dest is `(mem (reg d))`. cse substitutes d's equivalence (&m) into the movstr → (plus fp 16), but d remains live? d is used only by the movstr, so after substitution d is dead and deleted. Then why score 19?

Let me check d2's actual diff. Maybe the difference is elsewhere. Let me score d2 and look at the diff.

Actually all d-variants scored 19 with 86 ins, suggesting the same code. Maybe cse doesn't substitute d into the movstr dest because movstr is special. Then d stays live → s1.

Let me verify with a dump of d2. But that's another dump. Alternatively, try a variant where the copy dest is a *global* pointer variable? no.

Hmm, let me think differently: maybe make the *calls* use a separate pointer pseudo so they don't merge with the copy dest:
```
int *d = m;
*(Mat32 *)d = D_800AE620;
d = m;                  // second set — same value (identity, forbidden)
```
No.

What about passing `(void *)(d)` to the calls, where d is the same pointer used by the copy? Then d is used by the movstr and the calls → d live → reg. Same as reg80.

We need the copy dest address and the call address to be *different pseudos* with the same value, and cse must not merge them. cse will merge them if both are `(plus fp 16)` constant addresses... but in w1 it didn't create a shared reg. The difference is the movstr forces a reg.

Idea: make the copy dest address *not* `(plus fp 16)` but something cse treats differently, e.g. `(plus (reg d) 0)` where d = m? Still same after substitution.

Hmm, what if the destination is a *struct field* at a different offset, e.g. copy into `m[0..7]` where m is at fp+16 but the copy is expressed as `*(Mat32 *)(m + 0)` — same.

What if we make the copy dest address `(plus fp 12)` and then... no, must be m.

New idea: avoid the block move by making the source base a register via *another* block move that consumes the constant! E.g.:
```
Mat32 tmp;
tmp = D_800AE620;    // block move: source base reg (a1), dest = &tmp (reg!)
```
That still creates a dest reg for tmp.

Hmm.

New idea: what if we don't copy at all but use the global directly in the calls? No, the calls take m and modify it.

Let me reconsider: the target's loads from a1 with offsets 0..28 and stores to sp+16..44. What if the target C is:
```
int *p = (int *)&D_800AE620;
m[0] = p[0]; m[1] = p[1]; ... 
```
and the compiler *did* keep p in a1. Why? Because `p` is used 8 times as a *pointer dereference* and cse's find_best_addr decides whether to rematerialize the constant or use p. Our w1 (which used `src` = &D_800AE620 then src[i]) folded. What's different? In w1, `src` is pinned to $5! With the pin, the pseudo has a hard reg... but cse still folded the constant into the loads (diff shows lui/lw per load). So even a pinned pseudo gets folded by cse. Interesting.

But the launder version (asm tying src) kept it. So cse's equivalence from `src = symbol_ref` is a REG_EQUAL that find_best_addr exploits.

To defeat find_best_addr, the source value must not be a REG_EQUAL constant. A real second set that isn't constant-equivalent. But the value must still be the right address.

What if `src` is assigned from a *memory load* that contains the address? Is there a global variable holding &D_800AE620? Unlikely. But we could use a *function parameter*? No.

Hmm, hold on: what about `obj`? No.

What about deriving the address from `self`? No.

OK, maybe the ROM's C actually did have something like a *volatile* or a *union* or a *pointer cast through a struct*. But the launder in the current src is a modern reconstruction; the target was matched with the launder. The task is to find a lever-free equivalent. If it's a genuine wall, the row is WALL with best=19 (or the best lever-free score).

But wait — maybe there's another approach: make the block move's destination a *different* stack slot whose address doesn't appear in the calls, and then the calls get fresh addresses. E.g., copy into `m` (fp+16) but the *call arguments* pass a pointer computed differently... same address.

Hmm, what about using a *union* where the copy dest is member `mm` and the calls pass member `a`, and cse... tried d5, 19.

What if the calls pass `(void *)(m + i)` where i is a variable that is 0 but opaque? e.g. `(void *)(m + (self - self))`? That's an identity launder — forbidden.

Let me look at the actual d2 diff to understand. And maybe test a candidate where the copy destination is a *separate local array* that is later copied into m? Extra insns.

Alternatively: accept that the block move's dest reg is inherent, and instead make it harmless: if the dest reg (reg80 = &m) is assigned to a *caller-saved* register instead of s1, then self could take s1. The target's &m is rematerialized, so any register for it adds insns. Unless... the reg is a1 itself! If reg80 (the movstr dest) were allocated to a1, then the calls' `a1 = reg80` would be a self-move (eliminated) and each call would need... no, a1 is clobbered by the calls. Actually a1 is caller-saved and live across calls? reg80 is used after the calls (all 3 calls + the final copy) → must survive calls → callee-saved. So s-reg.

So the block move inherently costs a callee-saved reg here. The target doesn't have it → the target is not a block move.

Therefore: element-wise with a register source. And the only way to get the source into a register is to defeat cse.

Let me examine how cse decides. In cse.c, `find_best_addr` returns the address to use; if the address is a constant symbol and the MEM is used in a context... Actually the folding of `src = &D_800AE620` into `src[0]` is done by `fold_rtx` using REG_EQUAL notes, not find_best_addr. The set `src = symbol_ref` gets REG_EQUAL (symbol_ref). When cse processes `(mem (reg src))`, it substitutes the REG_EQUAL expression → `(mem (symbol_ref))`. Then it may or may not re-create a reg for it.

If `src` has *two* sets with different REG_EQUALs, cse's equivalence for src becomes invalid ("stale"), so it can't fold. The moves mention exactly this: "self-reassign stales cse (plus p K) equiv". So we need a real second set of `src` to a different value (not an identity of the same constant), such that cse invalidates the equivalence, and the final value is still &D_800AE620.

E.g.:
```
src = (int *)&D_800AE620;
...
```
What if we set `src` to a *different constant* first, then to &D_800AE620? The final set's REG_EQUAL is still the symbol. Hmm, cse tracks the *last* set; a previous different set doesn't stale the final equivalence. But: cse's `invalidate_memory`/`invalidate` on the second set would remove the first equivalence, and the second set establishes a new equivalence → folding still happens.

Unless the second set is *not* a single insn that cse can record (e.g. the value comes from a MEM load or a PHI). For example, set `src` in a branch:
```
if (obj != 0) {
    src = (int *)&D_800AE620;
    ...
}
```
That's what we have.

What about assigning src from a *conditional expression* that cse can't fold:
```
src = obj ? (int *)&D_800AE620 : (int *)&D_800AE620;
```
cse would fold the conditional at RTL? The expand of a ternary with the same value both arms → likely simplified by fold to the constant. Forbidden as identity anyway.

Hmm, what about `src = (int *)(long)&D_800AE620;` — same constant.

So the wall is real: cse-const-addr. The moves file has 6 entries of this wall for launder. Our item 1 would be another WALL. Best = 19? Hmm, but the task says "best = lowest score of a lever-free body". 19 is much better than the prior 20. But is 19 the best? Let me see if there's a variant that gets closer, e.g. score 5.

Actually wait! What about the *store* side? What if we make the destination address pseudo be *reused* as the call address but *not* callee-saved by making the copy happen *inside a nested block after the calls*? No.

Hmm, let me reconsider the whole shape: the target's copy loads from a1 (source base) and stores to sp+16... The register a1 is also used for the call args (`addiu a1,sp,16`). So a1 is reused. 

What if the C passes `m` to the calls and the copy is done with element stores from a *pointer variable* that is assigned from `D_800AE620` — and the pointer variable's live range ends before the calls. Then the pointer (a1) dies, and the calls create addiu. That's exactly the target! And the source base needs to be a register for the 8 loads. So: element stores from a register source, pointer dead before calls.

The question remains: how to make the source pointer's value not fold.

Hmm, unless... cse folds the *address* into the MEM but keeps a register because the MEM has 8 uses and find_best_addr decides the address is "expensive" when it's a symbol_ref + offset? In w1 it folded per-load (lui/lw pairs), so no.

Wait, w1's loads were `src[0]`, `src[1]`... with src pinned $5. cse folded to `(mem (symbol_ref))` each. But maybe because the *pin* made src a hard reg and cse... hmm.

Let me test a simple candidate: `int *p = (int *)&D_800AE620;` (no pin, no asm) and element loads, but with the *store order* different (e.g., load all 8 into t0..t7 then store). That was probably among gen_* (score 20/25). The prior coder tried many.

So item 1 is likely a WALL at best 19 (block-move variant) or 20. But hold on: the PARTIAL option: "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". The kind is launder only. If we keep the launder, win.c scores 0 but keeps launder → PARTIAL:launder, which is not a crack (the row kind remains). PARTIAL is for keeping *other* kinds, e.g. if the def had pin+launder and we keep pin. Here the only kind is launder, so PARTIAL would be PARTIAL:launder — pointless (that's just the original). So the result must be MATCH or WALL.

Before declaring a wall, I must spend ≥20 min and ≥30 scored tries per item. The prior coder's gen_* files count? The rule says "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". I've done ~10 tries. I should continue with real ideas, then wall.

But wait — maybe the target IS a block move after all, and the difference is the *destination*: if the block move's destination is a *register-held pointer* that is *dead*, expand won't create a new pseudo, and cse's substitution... let me actually check d2's RTL. d2 = `{ Mat32 *d = (Mat32 *)m; *d = D_800AE620; }`. Since d is a pointer pseudo assigned &m, expand_block_move sees dest = `(mem (reg d))` and calls copy_addr_to_reg(d) → d itself, no new insn. Then the movstr dest is `(mem (reg d))`. cse substitutes d's equivalence into the movstr dest → `(plus fp 16)`, and d is dead → deleted. Then the calls should be fresh. But the score is 19 → maybe d isn't dead because cse keeps `(set a1 (reg d))` with REG_EQUAL (d's equivalence), i.e. the calls use d? No, the calls use `(void *)m` which is a separate address pseudo `(plus fp 16)`, which cse merges with d's equivalence → it might rewrite the call address as reg d! That's it: cse merges the call address `(plus fp 16)` with the *register d* because d's equivalence is that address, so it uses reg d for the calls → d live across calls → s1.

Hmm, cse prefers registers over recomputation for a *constant* address? That's the cse-const-addr behavior: it creates/uses a register for a constant address when multiple uses exist. In w1, why didn't it? Because the address pseudo... In w1 there was no register holding &m at all, so cse couldn't use one.

So with any register-holding-&m present, cse uses it everywhere. So we must never have a register holding &m — meaning no block move dest pseudo.

Therefore element-wise is the only route, and the source base must be a register. Dead end unless we defeat cse's REG_EQUAL.

Hmm, what about making the source base a register via a *pointer that cse cannot fold because it's an argument to an opaque operation*... e.g., `src = (int *)&D_800AE620; src = (int *)((long)src & ~0L);` — identity, forbidden.

What about a *real* computation: `src = (int *)&D_800AE620; src = (int *)((char *)src + 0x20) - 8;` — this computes a different address then subtracts, ending at the same. That's an identity in disguise (address arithmetic that cancels) → likely considered an identity launder. The rule says "identity address spellings ... do NOT count as a crack". `+0x20-8` is an identity address spelling. Forbidden.

What about `src = (int *)((int)&D_800AE620 & -1);` — identity.

Hmm.

So item 1 is a wall? Let me check the prior coder's notes — there's no notes.md. The gen_* files show they tried a lot. Let me count gen files: ~30. Plus my ~10. So ≥30 tries.

But wait — I should double check the possibility that the target's C uses a *loop* that got unrolled... no, unrolled 3+3+2 is not a loop unroll pattern.

Another thought: maybe the target's C copies via a *pointer parameter of a struct type* from a *global struct pointer* — no.

Let me look at other shards' moves for this exact function family. The moves.md is 232 lines; let me grep for "headers1" or "P36 rung B" or "B4B8". Also check research reports? The brief says read moves.md. Let me grep for "block move", "movstr", "struct copy", "8 loads", "const-addr".

Actually, the walls.txt entry "cse-const-addr: cse folds or substitutes a constant/absolute address the target keeps base-relative" is exactly it. And the moves lines for func_80183098 (G14) etc.

Let me grep moves for "movstr" or "block".
