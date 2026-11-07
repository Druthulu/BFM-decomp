---
ts: 2026-11-06T02:51:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZczF6dY3rJ90E9er6Xfz
---
The dead-reset cse-breaker: `p = expr; use; p = 0;` — cse invalidates the equivalence at the second set, and flow deletes the dead set. In our case, the pattern is a store to memory then a load from the same memory. cse forwards the store value into the load. Can we break it with a "dead reset" of the memory? E.g., after the store `unk1C = unkDC`, insert a store of a *dead value* to the same address that cse sees, then the load gets the dead value? No — that would change the value.

Hmm, cse's store-to-load forwarding: it records the store's source as the equivalent of the memory location. A second store to the same address would invalidate. If we insert a store to the same address with a value that... it must be the same value to keep semantics, and cse would then forward THAT store's value (same). Hmm.

What if we insert a store to a DIFFERENT address that cse can't prove non-aliasing, so it invalidates the memory equivalence? Then the load must be re-emitted (reload). The extra store would emit an instruction — unless it's dead and removed by flow before codegen. But a store to memory is never "dead" in gcc 2.7.2 (no DSE) — it would remain.

What if the extra store is to a *local* variable (stack) that flow deletes? A store to a local that's never read is dead; flow's dead-store elimination (delete_dead_from_cse?) might remove it. gcc 2.7.2 has `delete_dead_from_cse`? Hmm, the pass list has `delete_dead_from_cse` in cse.c which deletes dead stores of pseudos (not memory). 

Hmm. What about a dead *register* reset: `flag = 0;` (flag is a local s32 used later? `gte_stflg(&flag)` sets it and it's used in the condition). After the condition, flag is dead. Insert `flag = 0;` between the two statements: cse invalidates the equivalence for... no, flag isn't the memory location.

The cse equivalence we need to invalidate is the MEMORY (unk1C). Hmm.

Alternative: make the second statement read a *different* address expression that's actually the same but cse can't equate. For instance:
- First: `((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC;` — address = arg0 + 28 (base s1, offset 28).
- Second: `((Unk*)(arg0 + 4))->unk18 -= 1;` — same address (arg0+4+0x18 = arg0+0x1C), but the RTL would be `(plus (plus arg0 4) 24)` simplified to `(plus arg0 28)` → same rtx → forwarded.

What about using a *different type* for the second access that changes the MEM's mode? Target needs s32.

What about accessing through a `u8*` with a manual s32 read? `*(s32*)((u8*)arg0 + 0x1C) = *(s32*)((u8*)arg0 + 0x1C) - 1;` — the address expression is (plus (reg) 28) → same.

Hmm, what if the second access uses an index variable: `s32 i = 0; ... *(s32*)(arg0 + 0x1C + i) -= 1;` — the address becomes (plus (reg arg0) (plus (const 28) (reg i))) → NOT the same rtx as (plus arg0 28) → cse can't equate → reload! And the codegen: `i` would be a register holding 0; the address would be arg0 + i + 28 → an extra `addu`/`addiu` instruction! Unless i is folded to 0 by cse... cse would know i=0 and fold the address back. Hmm, but cse folds constants; `i` is a variable initialized 0, so cse (or the front end) folds `0x1C + i` to 0x1C? The front end folds constant arithmetic only if i is a constant expression; i is a variable → no. cse's constant propagation might fold the add of i (known 0) — cse does constant propagation for registers known to be constants, so it would fold to 28 → same address → forwarded. And the extra addiu? The address `arg0 + 0x1C + i` requires computing i (li 0) — an extra instruction.

Hmm.

What about the target's actual codegen: 2094 lw v0,220(s1); 2098 nop; 209c sw v0,28(s1); 20a0 lw v0,28(s1); 20a4 nop; 20a8 addiu; 20ac sw. The reload is a plain `lw v0,28(s1)`. So the original C had two distinct memory accesses that cse didn't forward. Why not? Maybe because the original used a *different expression* that cse couldn't equate, yet the codegen folded to the same address. E.g., the original might have accessed the field via a pointer variable that cse couldn't prove aliases:

```
u8 *p = arg0;   // maybe a local pointer
...
((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC;
...
((Unk*)p)->unk1C -= 1;
```
If p is a local pointer equal to arg0, cse might know p == arg0 (copy propagation in cse records p's value). Hmm, gcc 2.7.2 cse does copy propagation for pseudos.

What if the original used the *s0* variable (a different local) for one access? The target uses s1 as the base for both. s1 is the saved arg0. Hmm, the function has `u8 *s0;` (the table pointer) and arg0. The target uses s1 = arg0 (saved in the prologue). So both accesses use s1.

Maybe the original C had the store and the decrement in a different form that prevented cse: e.g., the decrement read a *different field* and stored to unk1C:
```
((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC - 1;
```
That would be lw; addiu; sw — 3 ins, not the target.

The target's reload suggests the source explicitly reloaded: e.g., `((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC; ((Unk*)arg0)->unk1C--;` — cse forwards. Unless the two statements are in different basic blocks! If there's a branch or label between them... The barrier creates an insn; a real-C equivalent could be a *conditional* that splits the block. E.g.:

```
unk1C = unkDC;
if (unk1C == unk1C) unk1C -= 1;   // folds
```
No.

What about a `do { } while (0)` between? g5/g6 didn't help.

Hmm, what if the statements are separated by a *label that's a branch target* — creating a basic block boundary. cse works on extended basic blocks (EBBs); a label that is a branch target ends the EBB, and cse does NOT propagate across EBB boundaries (cse uses basic block boundaries? cse.c works on extended basic blocks and doesn't cross labels that are jump targets). So if we put a jump target label between the store and the load, cse can't forward!

How to get a referenced label between them in C without adding instructions? Use a `goto` from *before* the store to a label *between* the two statements:

```
    goto L;
    ... (dead code)
L:
    unk1C = unkDC;
    ...
```
Hmm, the label must be between the store and the load. A `goto` to it from elsewhere. For example:

```
        } else {
            if (unk6 != 0xFF) { ... }
            unk1C = unkDC;
            if (0) goto L1;   // folds
L1:
            unk1C -= 1;
```
The label L1 unreferenced → deleted early. Need a referenced goto. A `goto L1;` from an earlier point that is actually taken would change control flow.

What about a *conditional* branch whose both paths reach the label:
```
            unk1C = unkDC;
            if (flag >= 0) goto L1;   // flag >= 0 is already known true here (the outer if)
            L1:
            unk1C -= 1;
```
The compiler doesn't know flag >= 0 is true (no VRP), so it emits a real branch → extra insns. ✗

Hmm.

What about the switch dispatch creating a label? The case labels are branch targets, but they're before the store.

Wait — maybe the original C's structure has the two statements in different cases or after a label that's a target of the `while` loop? Let me look at the target's surrounding code: the store/load sequence at 2094-20ac is after the while loop and the `if (unk6 != 0xFF)` check. Is there a label at 2094? Let me check if any branch targets 2094: from the asm, the `beq v1,v0,2094` at 206c targets 2094! Yes! At 206c: `beq v1,v0,2094` (if unk6 == 0xFF, skip the loop and go to 2094). So 2094 IS a branch target — it's the label after the loop (the `if (unk6 != 0xFF) { do {...} while }` join point). 

So the code at 2094 is the target of the beq, i.e., a label. But the store/load are both at 2094+ (after the label), so they're in the same block. The label is BEFORE the store, not between.

Hmm, but wait: cse's EBB: the label at 2094 ends the previous EBB; the store and load are after it, in the same new EBB. cse could still forward within that EBB.

What if the *original* C had the store BEFORE the loop and the load after? Target: store at 209c, load at 20a0 — both after the loop. Hmm.

Let me look at the target's code flow: 2054 lw unk1C; 205c bnez → 20ac (if unk1C != 0, decrement at 20a8-20ac); else (2054 path): the loop at 2064-2090; then 2094 lw unkDC; 209c sw unk1C; 20a0 lw unk1C; 20a8 addiu; 20ac sw. Note 20ac is shared: the bnez path jumps to 20ac with addiu in the delay slot (2060: addiu v0,-1 is the bnez delay slot). So the decrement's store at 20ac is shared between the two paths.

Interesting: the `unk1C -= 1` after the reload is merged (cross-jump) with the `unk1C -= 1` of the if-branch! Both paths decrement unk1C. That's why 20ac is shared.

Now, the barrier sits between the store and the load in the else path. Without it, cse forwards the store into the load and then the decrement becomes a single computation; the two decrement paths then... the bnez path has addiu in its delay slot; the else path would have lw unkDC; addiu; sw (and the sw shared?). Hmm.

So the target needs the else path to do: store unk1C = unkDC; reload unk1C; addiu; sw (shared store). The reload is needed because cse can't forward.

Real-C: the reload happens if cse can't prove the store and load alias. What if the store is written with a *different type* for the destination that changes MEM_IN_STRUCT/alias info? cse's alias analysis: `cse_insn` invalidates memory entries using `write_dependence_p`? In gcc 2.7.2 cse.c, the memory table entries are invalidated based on `rtx_equal_p` of the addresses or `true_dependence`. If the two addresses are rtx-equal, cse forwards. 

What if the store's address is `(plus (reg s1) (const 28))` and the load's address is `(plus (reg s1) (const 28))` — same. Any C spelling that produces the same address will forward.

So we need the two addresses to differ in RTL but codegen to the same. E.g., the store via an offset from a base register that is *not* s1 at RTL time but gets allocated to s1 later: e.g., use a local pointer `u8 *p = arg0 + 0x1C;` for the load: the load's address would be (mem (reg p)) and codegen: p = s1+28 → an addiu instruction (extra). ✗ unless reload folds the addiu into the load (base+offset) — reload can fold `(mem (reg p))` where p = s1+28 into `lw 28(s1)` if the addiu is a single-use? That's the "reload folding" optimization: if p is assigned `s1+28` and used once, reload may fold it into the memory operand! Then the load is `lw 28(s1)` and no addiu. That's plausible in gcc 2.7.2 (reload does fold address computations). 

Let me try: 
```
u8 *p = arg0 + 0x1C;
...
((Unk*)arg0)->unk1C = ((Unk*)arg0)->unkDC;
...
*(s32*)p -= 1;
```
If p is defined near the use and used once, reload folds. But cse sees the load address as (reg p) vs the store's (plus s1 28) → different → no forwarding! And if reload folds p into the load, we get the target bytes.

But p's definition `p = arg0 + 0x1C` would be emitted as an addiu unless folded. Let's test.

Also try:
- store via a pointer and load via the struct (opposite).
- Both via different pointers.

Let me test a batch.
