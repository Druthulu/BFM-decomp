---
ts: 2026-11-06T16:39:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Q7yce8ffAsDvIZYAdjt1
---
In win.c RTL, block0 uses 73 (self) for the stores. Then block1 uses? Let's see further. But in the final asm, block0 (entry) uses a1 (72?) — `move $5,$4` and `lh $2,170($5)` and stores use $5=a1. So 73→a1 in block0? But dispositions said 73 in 4 (a0), 72 in 5 (a1). Contradiction unless regmove swapped or the asm's `$5` corresponds to 73.

Hmm, maybe I misread dispositions: "72 in 5  73 in 4" — 72=a1, 73=a0. But asm block0 uses $5 for the stores (73's uses). So either regmove changed it, or the disposition dump is before regmove.

Where does regmove run? regmove pass runs after global_alloc, before reload. Yes, gcc 2.7.2 has regmove (flag_regmove). regmove may reallocate copies. Ugh.

OK, empirical is the way. The core requirement: the body must produce, at the end, `move a1,a0` and use a1 everywhere. The pinned version achieves it by making self an arithmetic result. Since we can't pin, maybe we can make the arithmetic result opaque: e.g., `self = arg0 + flag * 0;`? Not foldable? combine can't prove flag*0? It can: multiply by 0 folds.

`self = arg0 + (flag - flag);` → not foldable at combine? It might: combine's simplify_rtx doesn't know flag-flag=0 (no value range). So RTL: sub t,flag,flag; add self,arg0,t. That's 2 extra instructions. Not acceptable.

We need zero-cost. What about a *volatile-free* trick: `self = (s32)(arg0 + 0u);` folds.

Hmm, what about making the parameter's pseudo not exist: if the parameter is used exactly once and only in an arithmetic op... In orig, param pseudo 72 exists too (insn 4), but then combine folded 73 = 72+$0 into a move, and local-alloc combined 73 into 72's qty? The result: only one global pseudo.

In win.c, after combine folds 73=72 (it's already a copy), local-alloc combines them in some blocks but not all, producing the split.

What if we avoid the copy entirely and use `arg0` directly in the then block and `self` elsewhere? Hmm.

Alternative approach: give the parameter and self *different modes* so the copy isn't combinable by local-alloc's MODES_TIEABLE_P check. E.g., make `self` a pointer (Pmode=SImode) — same mode. Hmm.

What about making the parameter `s32 arg0` but `self` an `unsigned` — same SImode.

Hmm.

Let's revisit: is `move a1,a0` really required to be a *separate* self pseudo? The target's move could come from the source having a local pointer copy. The register a1 is used for all accesses; a0 is free for mask. So the target's self is a pseudo in a1.

Maybe a different route: make the mask NOT be a0 but something else, and let self be a0? No — target is fixed: self in a1, mask in a0.

What determines that self=a1? In global-alloc, self conflicts with a0 because... in orig "73 conflicts: 73 2 3 4 29" — 73 conflicts with 4 (a0) because insn 4 sets 72 from a0 and 73=72+$0 uses 72... hmm.

In win.c, 73 conflicts WITHOUT 4 ("73 conflicts: 72 73 2 3 29") so 73 can take a0. In orig, 73 conflicts WITH 4, so 73 must avoid a0 → a1.

Why does 73 conflict with a0 in orig? Because the live range of a0 (hard reg 4) extends over insn 11 (the `self = arg0 + zr`), since 73's def uses 72 which is defined from a0 at insn 4 and dies at insn 11. In win.c, 73's def at insn 11 is a copy from 72, and local-alloc combined 73 with 72's qty for that block, so the global allocno 73 doesn't conflict with a0 (it was coalesced?).

Hmm.

Let me try simple variants empirically now that the dump harness works:
- V1: `self = arg0 + 0;` (combine folds; probably same as copy)
- V2: declare self as `u32` and use `(Unkstruct*)(self)` casts (same)
- V3: make self the *first* use: `flag = ((Unkstruct*)arg0)->unkAA;` and then `self = arg0;`? That changes order.
- V4: use `arg0` in an expression that creates a pseudo: e.g., `self = (s32)(arg0 + (flag & 0));`? extra.
- V5: `self = arg0;` but make self `register`? `register` vars are not forbidden? Brief says "no `register` vars". Right, forbidden.

Hmm. What about making the *parameter* not be used directly: e.g., assign `arg0 = arg0;`? no.

What about making the function body use `self` in a way that forces the copy to be live across both blocks: e.g., compute `flag` from self (it does). Hmm.

Wait — in win.c, block0's stores use 73 (self). The split: block0 (entry) uses 73, block1 (then) uses 72, block2 (else) uses 73. The final asm shows entry using a1 and then using a1, else a0. So regmove reassigned 73→a1 in entry? Let me look at the flow dump / greg more carefully. Actually the asm: `move $5,$4` is insn 4 (72=a0 → a1), and entry stores use $5 — but RTL says entry uses 73. So 73 must be $5 in entry. Dispositions said 73 in 4. Unless regmove swapped 72/73: regmove can rewrite `set 73,72` as `set 72,73` and swap uses. That's likely! regmove optimizes copy insns.

The final asm then: 72=a0? no...

Whatever. Let me try a different structural approach: keep self as s32 and make the then block use self too. It does. Hmm.

Let me think about what source the *original game* had. The target code:
```
move a1,a0
lh v0,170(a1)
sh zero,92(a1)
sh zero,152(a1)
bnez v0, else
sw zero,28(a1)
then:
li a0,-129
lw v1,32(a1)
lw v0,220(a1)
lhu v1,24(v1)
and v0,v0,a0
sw v0,220(a1)
j end
sh v1,256(a1)
else:
lw v0,32(a1)
lw v1,220(a1)
lhu v0,24(v0)
ori v1,v1,0x80
sw v1,220(a1)
sh v0,260(a1)
```

This looks like the original C had `arg0` as a struct pointer parameter; gcc created a copy into a1 because... hmm, why would it copy the param at all? Possibly the original source used the parameter in a loop or the compiler needed it in a callee-saved? No calls.

Actually, maybe the original source's parameter was `s32 arg0` and the code used a local `u8 *p = (u8*)arg0;` — a pointer local, and register allocation put the pointer in a1.

Given the pins were added by a previous agent to force this, we need a lever-free equivalent.

Since combine runs before local-alloc and folds `+0`/`|0`, what about an operation that combine does NOT fold but the assembler/maspsx turns into nothing? Hmm.

What about `self = arg0; self = self;`? Two copies; local-alloc/combine may eliminate one.

What about using the parameter in a conditional: `self = flag ? arg0 : arg0;` → folds.

What about `self = *(s32 *)&flag`... no.

Alternative: make the *else* block use a1 by keeping self live there via a different mechanism: the else block's `q`/`g` computations could use `self` where self is a pointer that's not coalescible because the parameter pseudo is dead. Hmm, but the parameter pseudo dies after the copy.

Wait — maybe the trick is to make the parameter *unused after the copy* AND make the copy not combinable by local-alloc because the copy's source (72) is not local to the block? local-alloc only combines when ureg is local or hard. 72 is a global pseudo (live across blocks? 72 is defined at entry and used at the copy; dead after). It's block-local to block0 → combinable.

Hmm, what if the copy is NOT in block0 but in each block? e.g.:
```
if (flag == 0) { self = arg0; ... } else { self = arg0; ... }
```
Then two copies, each block-local; local-alloc combines each with the hard reg a0 in the else (a0 free) → else uses a0. Same issue.

What if the parameter is used in both arms so it stays live? no.

Different idea: change which register the mask goes to, not self. Target has mask in a0 and self in a1. What if in our lever-free body, self is in a0 and mask in a1? Then the asm would be `move a0,a0`? no, self would just be a0 with no move (or move a0,a0 eliminated). Target's first instruction is `move a1,a0`, which requires self≠a0.

Could we get `move a1,a0` by making self a *second* pseudo that global-alloc must put in a1 because a0 is occupied by the mask at that point? The mask is computed later. Hmm.

What if the mask is computed at function entry (before the copy)? Then a0 = mask, and the copy self=arg0 would need... but arg0 is a0 too, overwritten. Order: `mask = ~0x80;` before `self = arg0;` would clobber a0 before the copy — wrong.

What if the copy is `self = arg0` but arg0's pseudo is live in both arms? For instance, the else arm uses `arg0` (the param) directly for something. Then the param pseudo is live across, and self's copy would be... Hmm, target's else uses a1 only.

OK let me look at this from a different angle: the C0535 cookbook mentions do{}while(0) tricks. Let me read C0535 and C0414.
