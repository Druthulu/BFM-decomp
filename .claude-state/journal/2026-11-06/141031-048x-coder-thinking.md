---
ts: 2026-11-06T21:10:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wCqeK3Hxig9iWvz3EQVK
---
Global priority = floor_log2(n_refs) * n_refs / live_length * size.

allocno_live_length is the number of instructions the allocno is live (from flow). For off: live 54→81, ~27 (in insn count, not doubled). For e: 73→81, ~8.

pri_off = 1*3/27 = 0.111; pri_e = 1*2/8 = 0.25. e > off → e allocated first. But global-alloc's assignment: which reg does the first allocno get? Global-alloc assigns registers based on available regs and preferences, not simply first-free-in-order. The first allocated (highest priority) gets its most preferred reg, which could be a1 based on conflicts/preferences.

Hmm, target: e gets a0, off a1. If e is allocated first (higher priority), it would take a0 (its lowest available). That matches target! But mine has off getting a0, meaning off allocated first in mine. So in mine off has higher priority.

Why would off have higher priority in mine? If e's live_length is longer in mine. In target, the launder created a 2nd set of e *after* lim, extending e's live range? No, extending would LOWER priority.

Wait, the launder `e = (s16*)D_801E8F78; asm(e);` — the asm def/use. This creates an additional allocno? Actually the tied asm might make e's live range *shorter* by splitting? Hmm.

Alternatively, the launder's asm def is a 2nd set that creates a *new* allocno for the asm output tied to e... and the tie forces the reg. The important effect: the asm output is tied to the input, so the final e value is in the same reg, and the asm insn is placed right after the def, so e's live length is the same.

Hmm, but n_refs increases: the asm uses e (input) and defines e (output) → n_refs = 4 (set@73, use@asm, set@asm, use@81). live length same. pri = floor_log2(4)*4/8 = 2*4/8 = 1.0. off = 0.111. So e strongly first → a0. Yes!

So the launder raises e's refs from 2 to 4, making it win. Without it, e pri = 0.25, off = 0.111. e should STILL win (0.25 > 0.111). But it doesn't. So my live_length estimate for e or off must be off.

Maybe allocno_live_length for e is much longer. e is REG_EQUIV; maybe flow extends e's live range to the whole block or function because of the REG_EQUIV? Or maybe e's live length counts from an earlier point.

Actually — maybe e is NOT the allocno that got a1. Let me verify by looking at the greg dump: insn 73 sets reg:SI 5 a1 = symbol. That's e. Yes.

Alternatively, maybe off and e have equal priority (both floor_log2=1) and the tie-break is by allocno number: lower allocno number first. allocno numbers assigned in order of first appearance. off (reg 95) appears before e (reg 79)? Hmm, allocno numbers are per pseudo, assigned by scanning. If tie, lower allocno gets sorted first → gets a0. off appears first (insn 54) → lower allocno → off first → a0. That would explain mine!

And with the launder, e's n_refs=4 → floor_log2(4)=2, pri doubles → e wins regardless.

So indeed we need to raise e's refs (or lower off's) to break the tie.

Let me compute more carefully whether they tie. pri = floor_log2(n_refs)*n_refs/live_length*size.
off: n_refs=3, floor_log2(3)=1 → 3/live_off.
e: n_refs=2, floor_log2(2)=1 → 2/live_e.
For a tie, 3/live_off = 2/live_e → live_off/live_e = 1.5. If live_off=27, live_e=18? Hmm live_e would need to be 18. e lives from 73 to 81 = 8 insns. Not 18. Unless allocno_live_length is computed differently (e.g., doubled by REG_EQUIV note: reg_live_length *= 2 in local-alloc, but that's local). Global uses reg_live_length from flow.

Hmm wait, maybe e's live length is longer because the REG_EQUIV symbol is used at insn 70 (lim address)? No, that's the symbol_ref directly, not reg 79.

I'm not going to fully resolve the model. Let me instead try to break the tie by making e's n_refs = 4 or by making off's n_refs=2, without changing code.

Idea: make off n_refs=2 (def + 1 use) by having the lim address NOT use off. But target's lim address DOES use off (addu at,at,a1). So off has 2 uses in target. Hmm, unless in the target RTL, the lim address uses the symbol+off and cse created off, so off has 2 uses. So off n_refs=3 in target too.

So target e must have n_refs ≥ 3 or 4 to win. With launder it's 4.

Real C 2nd set of e: we need a def that's live. Let me think about using e in the lim load in a way that yields target's exact code. What if we write:

```
lim = ((s16 (*)[2])e)[idx][0];
```
but force the address to be sym+off (not e+off) by... hmm, the compiler chose e+off (146). What if we compute lim via the symbol but ALSO reference e in the same statement such that it's a real use? e.g.:
```
lim = D_801E8F78[idx][0];
```
doesn't use e.

What if we make e's value depend on idx so it's not REG_EQUIV, and use it for both? No.

Alternative: raise off's priority DOWN by increasing its live length. If off is used later in the block, live length grows. But that adds code. Unless the use is a copy that's eliminated.

Hmm, what if off is defined EARLIER? If we compute `off = idx * 4` and then use `off` in the lim load — off is born at 54. To make off born earlier, idx must be available earlier. idx is loaded from D_801E8F50[param_2] after the func_80029504 call. Can't.

What if we lower off's n_refs to 2 by making the lim load use the symbol with idx*4 computed inline (not via off), so off is only used in the condition? Then off n_refs = 2 (def + use). But then the sll for lim would be separate from off's sll → extra instruction. Unless cse shares them, which brings back 3 refs.

Wait — maybe the target's `sll a1` is shared, and off has 2 uses. So off n_refs=3.

OK, let me try making e's n_refs=3 via a 2nd use (not def): use e twice. The two textual loads `*(s16*)((u8*)e+off+2)` get merged by cse. What if the first test uses e in a way that's a separate use but cse can't merge? E.g., test `*(s16*)((u8*)e+off+2) == 0` and the second `(func(*(s16*)((u8*)e+off+2)) & 0xFF) == 0`. cse merges the load. But what if we write the second as `((s16*)((u8*)e+off))[1]`? Same address, cse merges.

What if we make the first test use a *different* but equivalent expression that cse doesn't recognize, e.g. `*(s16*)((u8*)e + (off + 2))` vs `*(s16*)((u8*)e + off + 2)` — same RTL.

Hmm.

Different idea: use a real 2nd set of e that produces the SAME instruction because the compiler folds it. For instance:
```
e = (s16 *)D_801E8F78;
if (t < lim) {
    e = (s16 *)D_801E8F78;  // 2nd set
    if (...) idx = -1;
}
```
The 2nd set is dead (e not used after the inner if). But wait — the inner condition uses e AFTER the 2nd set! So the 2nd set is live. And the FIRST set (before the if) becomes dead (not used before the 2nd set). So flow removes the first, leaving one set inside the if. That would place e's def after the branch — wrong code. Score would change.

What if the first set is used before the 2nd? Only if the lim load uses e. Circular.

Hmm, let me try yet another angle: maybe the fix isn't about e at all but about the *order* of the `if` arms or a different structural change that makes off and e allocate oppositely. For instance, swap `off` and `lim` computations so that off is born later (shorter live) — then off priority rises further, worse. We want off priority lower or e higher.

Let me look at whether `idx` could be used instead of off in one place to reduce off's refs... but target uses off twice.

Actually, let me re-examine: is it possible the target's a1 is NOT off but something else? At insn 70 `sign_extend (mem (plus (reg 95) (symbol_ref)))`. reg 95 = idx*4. The address is (reg 95 + sym). In target asm: `lui at,sym; addu at,at,a1`. So a1 = reg 95 = off. Yes.

Let me try: make `off` live longer by moving its definition before `lim`? It already is. What if we move `lim` computation before `off`, and compute `off` as `idx * 4` after? Then off born later, live shorter → higher priority → off gets a0 (worse). No.

What if we make `off` a `s32` that's assigned in a way that extends its life to the end of the block? E.g., after the `if (t<lim)` block, use off in the `if (idx >= 0)` block. Any use adds code.

Wait, maybe use off in a *dead* way that flow keeps? Flow deletes dead code. But a use inside a conditional that's unreachable? Flow might keep it. E.g., `if (0) { p = D_801E8F98[off]; }` — flow removes constant conditions. 

Hmm.

Let me try the opposite: make e have n_refs=3 by giving it a use that produces no instruction. For example, use e in the lim load address AND the condition, but structure so the address isn't shared. What if the lim load is written as `lim = D_801E8F78[idx][0]` (symbol) and the condition uses `e` — that's current. e has 1 use.

What if we add a use of e in the `if (idx >= 0)` arm that combines with an existing address? e.g. `p = D_801E8F98[idx]` → could we write `p = (void*)((u8*)D_801E8F98 + off)`? That uses off (not e) and changes code.

Hmm.

Let me try declaring e as `register`? Not allowed.

Let me try: e assigned via a pointer arithmetic that isn't folded: `e = (s16 *)((u32)D_801E8F78 & 0xFFFFFFFF);` — identity mask, might be folded by combine. Actually a `& 0xFFFFFFFF` on a 32-bit value... combine might keep an AND. Test.

Or `e = (s16 *)(u32)D_801E8F78;` — cast, folded.

Let me try making e's type `u32` (integer) and casting at use:
```
u32 e;
e = (u32)D_801E8F78;
... *(s16*)((u8*)e + off + 2) ...
```
The mode is SI either way. But maybe the "size" differs? No.

Let me try a batch: void*, u32, s32, and a compound `e = D_801E8F78 + 0`.

Also try moving the e assignment to right after `t = func_80029504();` (earlier) — changes live length (longer → lower pri) — wrong direction.

And try moving e's assignment INTO the `if (t < lim)` but before the inner if — that would place it after beqz, wrong.

Let me test the type variants.
