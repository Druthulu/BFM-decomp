---
ts: 2026-11-06T16:29:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VquZEnsLFyXjM3nsjyta
---
Differences:
1. Then-arm: target v1 = p (lw v1,32), v0 = f. Mine: v0 = p, v1 = f. So the allocation of p and f swapped.
2. Else-arm: target uses a1 (self) while mine uses a0. That's because in mine the else block re-loads self from a0 (the original param), while target uses a1 (the copy). In target, `self` variable lives in a1 and both arms use a1. In mine, the then arm uses a1 but the else arm uses a0 — meaning local-alloc decided the self pseudo in else arm... hmm. Actually with the pins: zr pin forced `self = arg0 + zr` -> move a1,a0 and self was a real variable in a1. Without pin, the compiler still made move a1,a0 (good) for the then arm, but the else arm used a0 directly (because `self` var was optimized: cse/combine replaced self with arg0 in one arm?). Hmm actually target: else-arm `lw v1,32(a1)` uses self copy; mine uses a0. So the target keeps `self` live across both arms in a1.

Wait in target, then-arm also uses a1. So self=a1 in both. Mine: then a1, else a0. Interesting: the else arm's use of self got cse'd to arg0? Because self = arg0 and the store to unkDC happens... in then arm, the stores to self->unkDC may clobber? No.

Why does mine use a0 in else arm? Because the else block is reached by bnez from top; at that point a0 still holds arg0. Local-alloc assigned the else's self pseudo to a0 since it's not live across (the then block's copy a1 is separate). Target forced the same variable? Actually target: self copy in a1 at top, used in else. That means the self pseudo is live from entry through the join, allocated a1 (because a0 is... free? a0 used for mask in then). Hmm.

With pins, `self = arg0 + zr` makes self a separate pseudo whose addition result is a new register; cse cannot equate it with arg0 (addition, even by zr pinned reg, is opaque). So self is a real var used in both arms → a1. Without zr pin, `self = arg0` is a copy → cse makes self equivalent to arg0, so uses in the else arm can be rewritten to arg0 (a0), while the then arm keeps a1 due to... hmm, then arm uses a1 because the mask took a0? Let's think: in then arm, mask=~0x80 goes to a0 (li a0,-129), so self (which was copied to a1 at entry) is used there as a1 because a0 gets clobbered by mask? Actually the copy `move a1,a0` at entry exists in both. In mine, then-arm uses a1, else uses a0.

To keep self distinct from arg0 without a pin: use a real C construct that creates a new pseudo not equivalent by cse. Options:
- s16/u8 width: `self = (s32)(u16)arg0`? That adds instructions.
- Make self a local copy via a different expression that cse cannot fold: e.g., `self = arg0 + 0;` combine will fold. 
- Declare self as `s32 self = arg0;` and take its address? no.
- Use `self = arg0;` but then prevent cse equivalence: a use of self in a context that differs in mode... e.g. declare `u32 self` and use with pointers? cse may still equate.
- The classic: keep self live across a call — no calls here.
- Use a struct pointer typed variable: `Unkstruct_8017EAD8_2 *self = (Unkstruct_8017EAD8_2 *)arg0;` — then self is a pointer pseudo; cse may still equate to arg0 via (reg) copy propagation. But the pointer pseudo and arg0 differ in mode (Pmode vs SImode) so cse won't equate! That's a real C move: declare `Unkstruct_8017EAD8_2 *self` pointer. Then all uses `self->unkAA` etc. This changes the pseudo class. Likely gives self its own register.

Then the target has `lh v0,170(a1)` for flag: u16 field loaded sign-extended? unkAA declared s16 presumably. Fine.

Then arm allocation: target p in v1, f in v0. Mine p v0, f v1. Allocation order in local-alloc: whichever pseudo gets assigned first. The declaration order p then f: mine gave p v0? Actually local-alloc allocates in pseudo order; here p and f... The target likely had f allocated v0 and p v1. Since pins were f in $2 (v0) and g in $3 (v1)! Ah right: pin f=$2 gives f in v0, pin g=$3 gives g in v1. So target allocation is driven by the pins directly. Without pins we must reach the same allocation by C means: order/priority. p and f both defined in the then arm. Which is allocated first? local-alloc iterates by regno (pseudo number), so earlier-declared/earlier-created pseudo first. If p is created first, it would get v0... but target has f in v0. Hmm, in the original with pins, f was pinned to $2 so p got v1. Without pin: mine gave p v0, f v1 — p first.

To get f v0, p v1: create f's pseudo first (declare/assign f before p), i.e., `f = self->unkDC;` before `p = self->unk20;`? But the instructions order must be p's lw then f's lw: target has lw v1,32 (p) then lw v0,220 (f). Hmm target instruction order is p load first, f load second, yet f in v0 and p in v1.

Local-alloc assigns registers by pseudo regno order, not by use order. So the pseudo creation order (declaration/assign order in C) determines. If f assigned earlier in C but the scheduling reorders the loads (sched1 hoists), we can have load p first but pseudo f has lower regno.

But wait: if p is declared/assigned first in C, its load comes first too. sched1 might reorder anyway. Alternatively, declare `s32 f; s32 p;` order reversed but assign p first? Pseudo regnos are created by gcc's expand as variables are used/declared. Hmm, local variables in gcc 2.7.2: pseudos are created when the decl is referenced (expand_decl creates registers for each local variable at function entry? Actually expand_decl allocates pseudo regs for all locals at declaration point in the function's BLOCK, when the block is entered). Yes — in gcc, `expand_decl` for a local var creates a pseudo register at the point of declaration (block entry). So declaration order matters: declare f before p → f lower regno.

Currently the then-block declares p then f. So f gets higher regno and v1. Swap: declare `s32 f; s32 p;` then assign p first, f second? The loads: `p = self->unk20; f = self->unkDC;` — sched1 may reorder but the target has p load first then f load; if C order is p then f that's natural.

But wait, local-alloc assignment: both p and f are in the same basic block, p's live range starts at p's load (first) and ends at the store sh v1,256 (last, near the j delay slot). f's live range starts at f's load and ends at sw v0,220 (before). Actually p's last use is `sh v1,256(a1)` which is the delay slot of j — later than f's sw. Hmm, local-alloc processes pseudos in regno order and assigns free registers; priority? In gcc 2.7.2 local-alloc assigns in order of pseudo regno (or by qty). If p declared first, p gets v0, f gets v1. Target wants f v0, p v1 → declare f first.

Also mask: mask declared at function top (s32 mask) and assigned in then arm; it got a0 in both. Fine.

Else-arm: g needs v1, q needs v0 in target? Target else:
```
lw v0,32(a1)   ; q = self->unk20 -> v0
lw v1,220(a1)  ; g = self->unkDC -> v1
lhu v0,24(v0)
ori v1,v1,0x80
sw v1,220
sh v0,260
```
So q in v0, g in v1 — same as original pin g=$3 (v1). Declaration order q then g gives q v0, g v1? Mine else gave q v0? Mine: `lw v1,32(a0)` = q in v1, `lw v0,220(a0)` = g in v0. Wait mine else: lw v1,32(a0) → v1=q, lw v0,220(a0) → v0=g. So mine q=v1,g=v0. Because q declared first → should be v0... hmm but here mask/a0? In else arm, registers v0,v1 both free. q first (lower regno) should get v0. But mine gave q v1. Hmm, why? Because local-alloc assigns by regno order: q's pseudo maybe created later? Both q and g declared in else block at entry.

Hmm wait, mine's else-arm operands use a0 as base (self==arg0), and register allocation... Let me think about which is q: `lw v1,32(a0)` loads self->unk20 into v1; `lhu v1,24(v1)` then `sh v1,260` → that's q in v1. `lw v0,220(a0)` then ori, sw → g in v0. So yes q=v1, g=v0.

In the pinned original, g=$3 pinned to v1 and q got v0. So target q=v0,g=v1. Mine is the opposite. So in mine, q got v1 and g got v0 — that suggests local-alloc order gave g first (lower pseudo). q declared before g... unless the register pressure/qty ordering. Hmm, local-alloc in 2.7.2 assigns in order of `allocno` priority? Actually local_alloc processes `reg_qty` sorted by quantity? Let me recall: local_alloc() in local-alloc.c 2.7.2: it sorts by `regno`? It calls `qsort(reg_qty, n_quantities, sizeof qty, qty_cmp)` — qty_cmp compares `qty_n_refs`? Let me check tools/reference/gcc-2.7.2/local-alloc.c.

Hmm, actually there's a `qty_cmp` sorting by size then refs? Let me look.

But first, an important observation: in mine, the else arm's base is a0 while target a1. The a0 use is likely because cse/reg-prop equated self with arg0 in that arm. If we make self a pointer pseudo (different mode) we may fix base to a1 and also change allocation.

Let me check local-alloc.c qty ordering quickly.
