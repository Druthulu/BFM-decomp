---
ts: 2026-11-06T16:40:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_UzSpOCUbGT1zJNK9Zi3S
---
The moves entry "launder,pin | func_800CB2C8" is probably from a different overlay with the same address (many overlays). Not worth chasing.

Let me focus: I'll do a bigger empirical batch with structural variants, and if nothing cracks within the time budget, record a WALL.

But first, let me reconsider one promising mechanism: **make ret live across a block boundary while keeping the andi in the same block**. If ret is live into the block *after* the andi... but there is no use.

What about `m` being used in BOTH arms? In the target, m is used only at the bnez. 

Hmm, actually let me re-read the target once more for the andi's input. `354: 30628000 andi v0,v1,0x8000`. Hmm, could v1 at this point be something other than ret? At 34c `move v1,v0` sets v1=ret. Nothing else writes v1 before 354. So v1=ret.

OK here's one more idea that might work: **use a s16/u16 comparison to create Q, and get the branch to use the raw register by comparing against a HImode constant that gcc treats as SImode**. 

Actually, wait. What if the branch condition is `if (ret == 0x10000)`? no.

What if we use a **bit test**: `if (ret & 0x10000)`? no.

Hmm, let me look at the *branch* RTL in the target-equivalent: `beqz v1` is a `branch_zero` on SImode. 

Let me try: ret is `s32`, and the C is:
```c
if ((ret & 0xFFFFFFFF) == 0)
```
folded to ret==0.

What about `if ((u32)ret == 0u)`? same.

What about `if (!(ret | 0))`? folded.

What about `if (ret == (s32)0)`? same.

Let me try a **different comparison that still emits beqz**: `if (ret <= 0 && ret >= 0)`? two branches.

OK, let me also try: **make the call result flow through the stack**: no.

Let me try a batch of structural variants now (10 candidates):

1. nested if: `if (ret != 0) { if ((m = ret & 0x8000) != 0) {...} else {...} }`
2. `if (ret) {...} else { if ((m=ret&0x8000))...}` — wait the target's ret==0 goes to the tail, and the m-handling is in the ret!=0 path. So nested: `if (ret != 0) { if (m) A else B }`.
3. ret declared u32.
4. ret = func at decl.
5. m as a struct member? no.
6. `switch (ret) { case 0: break; default: if (...) ... }`.
7. early goto: `if (ret == 0) goto tail;` with tail label.
8. `m = ret & 0x8000` with `if (ret) { if (m) ... }` (hoisted m, nested).
9. `do { ret = func(); } while(0);` — C0535 EBB split.
10. `do { m = ret & 0x8000; } while(0);` — tried (9).
11. `if (ret == 0) {} else if ((m = ret & 0x8000) != 0) {...} else {...}` with ret as `s32` and an extra unused variable.
12. Call-site cast: `ret = ((s32 (*)(u8*, s32))func_801638A0)((u8*)a0, (s32)sp20);`

Let me write these.

Actually, one more important idea: **the zero_extend pseudo Q might come from a different expression**: `if ((ret & 0xFFFF) == 0)` generates andi $2,$3,0xffff → Q=$2, then beqz $2. Target branches on $3 though. BUT what if we then write the branch as `if (ret == 0)` and use the `(ret & 0xFFFF)` for something else? no.

Hmm, what about `if (ret == 0)` where ret is u16 BUT the branch is compiled via a *HImode* compare that uses `beqz` because gcc knows the value is zero-extended from an `andi`. For instance:

```c
u16 ret;
ret = (u16)(func(...) & 0xFFFF);  // explicit andi: andi $2,$2,0xffff; then move? 
```
Hmm: `ret = (u16)(t & 0xFFFF)` — the tree would be a truncation of an andi; gcc folds to just the truncation? The andi 0xffff is redundant for HImode. gcc might emit nothing extra and know the upper bits are zero! Then `if (ret == 0)` → beqz directly (no zero_extend) because gcc knows from the andi... but the andi may be folded away, losing the knowledge.

Hmm, what if we use a mask that's not 0xFFFF, e.g., `u16 ret = t & 0x7FFF;`? Then the andi is needed (0x7fff) and gcc knows the upper bits are zero → the HImode compare to 0 can use beqz! Let's think: `m` mask is 0x8000 though. Hmm, but what if the variable ret is masked with 0xFFFF explicitly: `ret = t & 0xFFFF` where t is SImode and ret u16 → gcc emits `andi $3,$2,0xffff` (one insn) and then the compare is beqz on $3 with no extension. Then:
- t = call result $2.
- ret = t & 0xffff → `andi $3,$2,0xffff`? Wait, would the copy move $3,$2 be there? No, the andi's output would be a pseudo that gets $3 (or $2). Hmm, and then we'd have an extra andi anyway. And the target has no andi 0xffff.

OK, that doesn't help because the target has no extra insn at all.

Let me now also consider: maybe the target's `move v1,v0` can be produced by the *and* itself if the andi's output is $2 and input is $3, i.e., we need ret=$3. And ret=$3 requires $2 occupied. 

WAIT. What about the branch's *delay slot*? The target's `andi v0,v1,0x8000` is in the beqz delay slot. Before the branch, `move v1,v0`. What if in the original the code was:

```c
ret = func(...);
if (ret == 0) {
    m = 0;  // ??
}
```
no.

Let me just run the structural batch and see. Time check: started 09:26, now maybe 09:45. I should keep to ~30 min per item. Let me move faster.

Actually, let me reconsider the budget: 20-30 min wall per item, 3 items. Total ~90 min. It's fine.

Let me write batch 3 with 12 variants.
