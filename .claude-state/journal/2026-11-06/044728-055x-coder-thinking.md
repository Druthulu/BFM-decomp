---
ts: 2026-11-06T11:47:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hl0JcDTOmUKhuHWZUH3D
---
No improvement. The copies still fold. v_dwa1 = 19 (32 ins) — the do-while added an insn but didn't keep the copy in the right way.

Let me reconsider. This is looking like a wall. But let me try a fundamentally different approach: maybe I can restructure so the copies aren't needed. Wait — the target HAS the copies. To match, I need them. If real C can't produce them, it's a wall.

But before declaring WALL, let me check: maybe there's a way to make a1 a distinct pseudo via a function call boundary. The function is a leaf (no calls). But what if I introduce a call? No, would change code.

What about using `alloca` or a nested function? No.

Let me reconsider the target's register allocation once more. The target:
- insn 0: move a1,a0 (a1 = a0v)
- insn 1: lh v0,208(a1)
- ...
- insn 16: move v1,a0 (cpy = d0)

What if these moves are NOT from opaque copies but from the natural code, and the `+zr` levers were actually doing something else? The header says they're the opaque copies. And the baseline (with levers) matches. So they are.

Hmm. Let me try the exact `+ zr` semantics differently: maybe a real-C expression that's equivalent to `x + 0` but not folded. E.g., `a1 = a0v + (0 & something)`. No.

What about `a1 = a0v | 0`? Folds.

What about `a1 = a0v * 1`? Folds.

What about `a1 = a0v ^ 0`? Folds.

What about a conditional that's always the same: `a1 = (a0v ? a0v : 0)`? gcc might not fold and would emit a compare... adds insns.

Hmm. What about reading a0v through a union member? 

Let me think about `a1 = a0v` where a0v is the parameter. What if I use the parameter in a `?:` or `&&`? 

Actually, maybe the key is the `move a1,a0` is a "copy" that survives because a0v is the incoming argument (hard reg $a0) and a1 is a pseudo, and local-alloc's copy preference would normally coalesce them, BUT if a1's register class or usage differs... 

Let me look at the actual alloc: maybe if a1 is used as a `u8*` and also as an `s32` (mixed), the modes... no.

Let me try a completely different tack: since the function is small, maybe there's an alternate C form that yields the same instructions without explicit copies. For example, if the parameter `a0v` is used directly but the compiler happens to copy it because of a loop or a call... 

Wait — the target has `move a1,a0` at insn 0, and ALL body accesses use a1. The parameter a0v is only read at insn 0. This is exactly a copy. The compiler emitted a copy because the source had an opaque copy. Without it, gcc uses a0 directly.

Is there ANY real C that makes gcc copy an argument into a new pseudo and use the new pseudo? Yes: if the argument is used after a call (the arg reg is clobbered). But no call here.

Or if the argument's value is needed in a narrower mode. No.

I think this is a genuine cse-copy-merge wall. The G07/G08/G22x walls confirm this class. Let me do a few more attempts to reach 30 tries, then WALL.

Actually, wait. Let me reconsider the possibility that the two moves can be produced by DIFFERENT constructs:
- `move a1,a0`: maybe from `a1 = a0v;` where a1 is `volatile`? No.
- What if the function parameter is re-declared as a local via a K&R-style? No.

Let me look at the target's `move v1,a0` (cpy). The source `cpy = d0`. If cpy were used in a way that requires it after d0 is dead... d0 is used in the `slt` AFTER cpy is set (insn 19 uses a0=d0). So d0 is live at cpy's set. cpy is used at insn 21 (addiu v0,v1,2). So both d0 and cpy live simultaneously → separate registers possible. But cse makes them eqv (cpy = d0 copy) → same pseudo → same reg. The `+ zr` prevented the eqv.

Real C to prevent eqv: a mode change. cpy could be s16 (HImode) — v_cpy16 didn't help (score 18). Let me check why. With cpy s16, `cpy = d0` is a truncation to s16, then `v0 = cpy + 2` sign-extends. But the target's cpy is s32 (`addiu v0,v1,2` no sign-extend). Hmm, but the HImode copy might still produce a move + sign-extend (2 insns) — wrong.

What if cpy is `s32` but assigned via `(s32)(s16)d0`? d0 is s16, so `(s32)(s16)d0` = d0 (no-op). Folds.

What if cpy is `u16` and `d0` is s16? `cpy = d0` truncates... 

Hmm.

Let me look at the actual v_cpy16 disassembly to understand.

Actually, let me step back and count. I've scored: orig baseline (1) + nopin (1) + 8 (batch1) + 5 (batch2) + 8 (batch3) = 23 bodies. I need ≥30 for a WALL. Let me do a few more targeted batches, then WALL.

But actually, let me reconsider whether the WALL is the right outcome or whether there's a cleverer move. Let me look at how the ORIGINAL `+ zr` works at the RTL level and whether a real-C equivalent exists.

`a1 = a0v + zr` where zr is `register s32 zr __asm__("$0")`. In RTL: `(set a1 (plus a0v (reg:SI 0)))`. The `(reg:SI 0)` is $zero. gcc's combine/optabs see a PLUS with a register operand 0 → emits `addu a1,a0,zero` (move). But cse doesn't treat `(plus a0v (reg 0))` as a copy of a0v because reg 0 is a hard reg with its own qty? Actually cse knows reg 0 is constant 0? Maybe not. So it stays.

Real C equivalent of `x + (reg 0)`: `x + zero_register`. In C, there's no way to reference $zero except asm or `0`. `x + 0` folds.

Unless... the value 0 comes from a variable that gcc can't prove is 0. E.g., a function parameter that's 0? No.

Or `x + (y & 0)` where y is opaque? Folds to x (since &0 = 0).

Hmm. What about `x + (y - y)`? Folds.

I think it's genuinely opaque-only.

Let me do a few more tries with different structures, then WALL. Let me try:
- Splitting d0 into a separate variable read via a union member (maybe the union changes the qty).
- Making a1 from a union/struct.
- `a1 = (u8*)(a0v);` with a0v used in the else reload (so a0v stays live).
- Using `a0v` directly for the reload `d0` (so a0v live longer → maybe a1 separate).

Actually, that last one is promising for (a): if the ELSE reload uses `a0v` instead of `a1`, then a0v is live until the else (after a1 is defined), forcing a1 to NOT coalesce with a0v. But then the reload address would be `(plus a0 0xD0)` instead of `(plus a1 0xD0)` — target uses a1. Hmm, unless after forcing a1 separate, the reload can still use a1 and a0v is used elsewhere harmlessly.

Wait, the target's reload is `lh a0,208(a1)` — uses a1. So I can't use a0v for the reload.

But maybe I can make a0v live via a harmless use that doesn't change codegen. E.g., a use in a branch that's folded? Folded uses don't keep it live.

Hmm.

What if the parameter is used to compute a1 and ALSO passed... no.

Let me try: make the top load use `a0v` (so a0v is live after a1=a0v), and see if a1 becomes separate. If a1 becomes separate but the load uses a0v, the insn would be `lh v0,208(a0)` vs target `lh v0,208(a1)`. But maybe after forcing a1 separate, I can switch the load back to a1 while keeping a0v live another way. This is a multi-step. Let me just try a variant where the top load uses a0v and see the allocation.

Actually, simpler: let me try `a1 = a0v;` then `a1 = a1 + 0;`? identity, deleted.

OK let me try a batch:
- v_live: use a0v in the top compare: `if (*(s16 *)(a0v + 0xD0) < 0x28)` and `v0 = *(s16*)(a1+0xD0)+8`? That mixes. Hmm, then a0v live at the compare (before a1 use). But a1 = a0v is before. So a0v live after a1=a0v → a1 separate. But then the compare uses a0v → `lh v0,208(a0)` (wrong vs target a1). 

Unless I put `a1 = a0v;` AFTER the compare:
```
v0 = *(s16*)(a0v + 0xD0);   // uses a0v
a1 = a0v;                    // copy after
if (v0 < 0x28) { v0 = ... } 
```
Then the compare uses v0, and a1 is defined after. But a1's uses are later. a0v live only at the first load. a1 defined after → they don't conflict (a0v dead when a1 defined) → coalesce still possible? Coalescing merges if live ranges don't overlap; here a0v dies before a1 is born → they CAN coalesce. Hmm.

To force separation, a0v must be live AT a1's definition and after. So a0v used after a1=a0v. 

What if the else reload uses a0v (live into the else) and everything else uses a1? Then a0v is live from entry through the else reload. a1 defined at entry, live throughout. They overlap → no coalesce. And the else reload uses a0v → `lh a0,208(a0)`? No, it'd be `lh a0,208(a0)` using $a0 = a0v. Target uses a1. Wrong register for that load.

But maybe the reload could be `d0 = *(s16*)(a0v + 0xD0)` where a0v is in $a0, and the target has `lh a0,208(a1)`. So $a1 vs $a0. Different.

Hmm. But wait — if a1 is a separate pseudo, it might get $a1. And a0v stays $a0. The reload using a0v → `lh a0,208(a0)`. Target → `lh a0,208(a1)`. Different by one register.

Not good.

OK. Let me consider that this is a WALL. But the brief says a WALL needs ≥20 min and ≥30 scored tries. Let me reach 30+ tries with meaningful attempts, document, and move on. I've got 23. Let me do 2-3 more batches (10+ tries) with plausible moves, then WALL.

Actually, let me reconsider the possibility that the function is crackable via a very different body shape that produces the copies naturally. Let me look at how func_80145C54 (cse-copy-merge WALL) and func_8018xxxx siblings look. But time.

Let me try a batch of structural variants:
- v_top_a0v: top compare via a0v, rest via a1.
- v_split_ptr: two pointer vars a1 and a3.
- v_union: d0 read via union member.
- v_ternary: n/a
- v_dw2: do-while around the whole else block.
- v_cond: use a conditional to create a copy.

Let me also try the "dead reset" C0414 more precisely: the dead-reset is `p1 = 0;` between two calls that invalidates cse equivalence. Here, a dead reset of d0 or a1 before the copy might break the eqv. I tried `cpy = 0; cpy = d0;` (18). What about `a1 = 0; a1 = a0v;`? (18). 

Let me try resetting the SOURCE: `a0v = a0v;`? identity.

Hmm.

Let me look at the exact cse-copy-merge wall from G22x and see if there's a known crack. walls.txt: "cse-copy-merge cse merges a copy the target keeps in its own reg (G22x)". So G22x had this wall. No crack mentioned.

Given the strong evidence this is a wall, and the time, let me do a final batch of ~8 variants to reach 30+, then declare WALL with the best score.

Wait — actually, let me reconsider. The best lever-free score so far is 10 (v_vol, 34 ins) and 17 (v_dwcpy, 31 ins). The WALL "best = lowest score of a lever-free body". The lowest score is 10 (v_vol). But v_vol uses `volatile` — is volatile a lever? The brief's kinds are barrier,pin. `volatile` is real C, not a barrier/pin. But it added insns. The WALL best should be the lowest score among lever-free bodies. v_vol = 10 is the lowest. But is v_vol "lever-free"? It has no pin/barrier. It uses `volatile s16` read — that's real C. But it's arguably a launder/barrier-like construct. Hmm. The constraint says "no new lever of any kind". Is `volatile` a lever? The kinds list doesn't include it, but "no new lever of any kind" is broad. `volatile` is a memory-access qualifier; it's a legitimate C construct but often used as a lever. I'd say it's a lever (it changes codegen to force memory access). To be safe, I'll consider the best non-volatile lever-free body: v_dwcpy = 17 (31 ins) or nopin = 18. Hmm, v_dwcpy uses a do-while (with !FAKE comment) which is allowed. So best = 17.

Actually, let me reconsider whether v_vol's 10 is better. The score metric: lower is better, 0 = match. v_vol=10 < 17. But if volatile is disallowed, use 17. The brief says "best = lowest score of a lever-free body". I'll report the best legitimate lever-free score. Let me note both.

Hmm, but let me not give up yet. Let me try a few more creative variants. In particular, the reload (c) might be crackable, and maybe with the reload fixed the score drops to ~4-6, still not 0 (copies). But a PARTIAL is not applicable here (kinds are barrier,pin; I'd need to keep only those levers — i.e., a body that scores 0 while keeping barrier/pin). PARTIAL:<kinds still kept> means win.c scores 0 keeping only those levers. So PARTIAL would be if I found a score-0 body that still uses barrier or pin. That's not the goal (the goal is MATCH = kinds gone). PARTIAL is a fallback where you can't remove the levers but can reduce to fewer. Not useful here.

Let me try more variants to see if I can crack it. Let me focus on the copies.

New idea for `move a1,a0`: What if a1 is assigned from a0v inside a `do { ... } while(0)` that also does the first load, so the copy and load are in a separate EBB? C0535 splits cse1 EBB. Let me try wrapping the entry load and copy in a do-while.

Actually, the copy `a1 = a0v` is at the very top; wrapping it in a do-while(0) might keep it as a separate EBB. Let me try:
```
do {
    a1 = a0v;
    v0 = *(s16 *)(a1 + 0xD0);
    ...
} while (0);
```
Hmm.

Let me try a batch:
- v_dwent: do{a1=a0v; v0=load;}while(0)
- v_dwent2: do{a1=a0v;}while(0) (already 19)
- v_dwelse: do{ else body }while(0)
- v_ptr2: a1=(u8*)a0v; a2 uses a1...
- v_live_reload: reload via a0v while a1 separate (mixed)

Let me also try making the parameter `a0v` a `u8*`? Can't change signature.

Let me try the do-while around the else body and around the entry.

Actually, let me look at what C0535 did exactly (do{}while(0) around two copies splits cse1's EBB so sched1 keeps their birth order). It's about copies. Let me wrap the two copies in do-whiles at their EBBs.

I already did do{a1=a0v}while(0) → 19. And do{cpy=d0}while(0) → 17. Hmm, v_dwcpy=17 is better than 18! Let me look at v_dwcpy's diff — maybe it kept cpy's copy. Let me check its disassembly.

Let me dump v_dwcpy.
