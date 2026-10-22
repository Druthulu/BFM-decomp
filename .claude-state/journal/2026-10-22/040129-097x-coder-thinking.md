---
ts: 2026-10-22T10:01:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_2a1GKRPvCqSqf7nQAtXz
---
This is deep. Let me step back and be pragmatic about the remaining items. I have 4 items to go and limited time. Let me allocate:

- 8018483C: ~30 min
- 8017DA30: ~30 min
- 8017D81C: ~30 min
- 8018389C: ~30 min

For each: read notes (done for all), generate a batch of 15-25 variants informed by the mechanism, score them, and record the result.

Since the mechanism understanding is now decent (cse/combine folding constants; pointer materialization), let me design variants that exploit "the value must be in a reg" ideas:

For 8018483C (need "lui v0; addiu v0; move s0,v0"):
Ideas:
1. Make the pointer's value come from a source that is not a compile-time constant, but is still correct: e.g. the address of a *struct member*? no.
2. Use the pointer in a way that forces a copy: e.g. assign p twice (v11 tried: "the address assigned twice" → 5).
3. Use `p` in a *conditional* expression: `p = cond ? &D_800B99DC : &D_800B99DC;` → gcc folds.
4. Use a *pointer difference*: no.
5. Use the address through a *cast to void* and back: laundering.
6. Use the pointer as the base of a load in a *different* place where the register is caller-saved: e.g. `D_801E86BC = (*(u16 *)&D_800B99DC & 1) + 3;` (v9) — that gave the load base v0 (115 insns).
   Hmm! v9's count matched (115). What if we combine v9's "address used twice" with something that makes the materialization go into v0 and copy to s0?
   In v9, the materialization went into s0 (lui s0) — the same as the base version.

7. What if p is assigned from a *volatile* global? no.

8. What if the address expression is `&D_800B99DC[0]` where D_800B99DC is an array of u16? Hmm: `p = &D_800B99DC[0];` — the address of the array = the symbol. Same.

9. What if the pointer is obtained by *casting a function pointer*? no.

10. What if the pointer is assigned inside the loop? no.

11. What if p is a *struct member* (a local struct field holding the pointer)? → the value would be in memory → load.

12. What if the pointer is assigned from a *call*? no.

Hmm, 13: what if the *order* is: p is assigned the address BEFORE the early return, so the constant is materialized in the preheader into a caller-saved reg (v0) and then copied to s0 after the branch? Let me think: if p = &D_800B99DC is before the branch, the value is live across the branch → p in s0, and the materialization happens in the preheader → "lui v0; addiu v0" in the preheader, and after the branch "move s0,v0"?? Hmm, but the branch's delay slot... The target has the materialization AFTER the branch. Hmm, but the materialization is at 3144 which is after the bnez at 3130 (target 32a8 = the return path). So the fall-through block starts at 3138.

Hmm, but if p were assigned before the branch, the materialization would be in the preheader (before 3130) ✗.

14. What if the pointer is assigned in a *nested block* that ends? e.g. inside the `if` block? no.

OK, let me try a completely different idea: maybe the copy "move s0,v0" is not about the pointer at all! What if it's the *address* being computed as `&D_800B99DC` and p being a *different* variable that is copied... Hmm.

Alternatively — maybe the original source had the pointer value in a variable that was ALSO used as a *call argument* somewhere (making it caller-saved at that point) — e.g. `func_80049CAC((s32)q - 2, (s32)&D_801E8788)` — no, that's a different symbol.

Hmm, let me look at the whole target asm for func_8018483C to see if &D_800B99DC appears twice (e.g. as a call argument).

From the earlier dump: D_800B99DC appears at 3144/3148 (lui v0/addiu v0) and D_800B99D8 at 315c (a different symbol).

So &D_800B99DC appears once. The value is materialized into v0, copied to s0, and used as a load base.

So the ONLY uses of p are the loads/stores through s0.

So the copy s0 = v0 is pure register allocation: gcc chose to materialize the constant into v0 and copy to s0 rather than materializing directly into s0. Why? Because the pseudo p was allocated s0, but the *constant materialization* was assigned to a different pseudo (v0) that was then copied.

In gcc, the constant materialization happens in local-alloc/reload: `(set (reg p) (symbol_ref))` — reload would emit "lui s0; addiu s0,s0,0" directly into s0 (the reload reg = p's reg). To get v0 + move, the RTL must be `(set (reg v0) (symbol_ref))` + `(set (reg s0) (reg v0))` — two insns, where v0 is a pseudo allocated to v0 (a caller-saved reg, live only briefly).

That RTL arises from the source `p = pb` where pb is a separate pseudo — i.e. the front end created two variables. And then cse folded pb's use into the constant, making the copy `(set (reg p) (symbol_ref))`.

So to keep the copy, cse must NOT fold pb's use into the constant. When does cse not fold? If pb's set insn has a REG_EQUAL note or ... hmm.

Actually, maybe the fold happens not in cse but in the FRONT END: the front end's `expand_expr` for a VAR_DECL with a constant initializer might directly use the constant. Hmm, but the .rtl dump for item 1 showed a set insn for p...

Hmm, wait: for item 8018483C, let me just DUMP the RTL and see whether the copy insn exists at the RTL level (pre-cse) and where it disappears. That's the fastest way to find the fold site. Let me do that: dump the candidate for x3 (pb temp + p = pb, no asm).

Let me do it — the dump takes ~30s.
