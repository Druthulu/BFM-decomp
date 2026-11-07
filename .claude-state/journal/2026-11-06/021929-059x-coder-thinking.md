---
ts: 2026-11-06T09:19:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DZ4zVQ82NlKKT8ZBPiKy
---
Target's loop: i counter in v1 (addiu v1,v1,1 in the bnez delay slot), s0 = e (base+4), s1 = base. Loop end: `addiu s0,s0,24; slti v0,v1,64; bnez v0,loop; addiu s1,s1,24`. So both base and e are updated (e = base+4 kept as separate pointer!). This means the source likely was:

```c
for (i = 0; i < 0x40; i++) {
    e = (Sub_80180A54 *)(base + 4);
    ...
    base += 0x18;
}
```
and the compiler kept e = base+4 in a register (s0) and base in s1, updating both by 24 each iteration. That's the cse "base+4" registered as a cse address pseudo (constant address). In mine, cse folded it.

What makes cse register the base+4 address? cse's `cse_process_notes`/`cse_basic_block` decides to allocate a register for a constant address if it's used enough times and register pressure allows: in cse.c, `gen_lowpart_if_possible`/`cse_reg_info` — the decision is in `cse_main`: `max_qty`... Let me look at cse.c's rule for registering constant addresses. There's a heuristic: if the address is used >= 2 times (or `cse_insn` with `n_sets`?) it creates a REG. Actually cse.c has `record_jump_equiv` etc. The relevant part: `cse_insn` when a source is a constant address: `if (GET_CODE (src) == SYMBOL_REF || LABEL_REF ... )` and `have_reg_qty`... Let me grep cse.c for "reg_qty" and the comment about "this insn is the only use".

Actually, cse only puts a constant address in a register if it appears more than once in the same basic block: cse scans the block; for a (plus base const) it creates a REG only if the same address is used >= 2 times? The e accesses: e->flag (lh 2(s0)), e->flag=1 (sh), e->ptr, e->param, e->y, e->x, e->size, e->id — that's many uses of base+4+K for various K, not the same address. But the *base+4* itself isn't an address that's directly used; each access is base+4+off.

Hmm, so cse registered `e` = base+4 as a pseudo? cse doesn't do that; combine/loop might. Actually the `addiu s0,s1,4` at entry then `s0 += 24` each iteration looks like the compiler's *induction variable* handling: `e` is a derived induction variable. In mine, e = base+4 got folded into each access because... hmm, but then why does target keep it?

Wait — target computes `addiu s0,s1,4` BEFORE the loop (at 31ec, before the loop head at 31f4). So e = base+4 hoisted out of the loop and incremented by 24. That's loop.c's induction variable optimization! loop.c found `e` (or the address base+4) as a derived induction variable and strength-reduced it, creating an extra biv.

Mine: `move s0,s1` at [12] — s0 = base (same reg as s1?). Hmm, that means mine also has s0 as a biv but equal to base, and offsets +4 folded.

So in mine, loop.c derived `e` but folded to base (e = base+4, so it used base+4-4? no...). Actually mine: s0 = base, accesses at 6(s0) = base+6 = e->flag. So mine's e was replaced by base with offset+4 folded. So loop.c chose not to create a separate biv for e, instead reusing base.

Why? Loop.c's `strength_reduce` finds bivs; `e = base + 4` where base is itself a biv. loop.c may combine. The pin's presence changes register pressure → loop.c's decision to create an extra biv depends on `loop_regs`/`max_regs`? Hmm, loop.c has a check: it only strength-reduces if the number of registers needed is acceptable (`n_times_set`?).

Actually loop.c has `maybe_gain`/`insn_has_...`. There's a known behavior: loop.c's `strength_reduce` creates a new register for the derived biv only if `! loop_has_call`? No, there are calls here.

Hmm, this is the "loop-extra-iv" wall from moves.md (G08b func_8017849C): "loop.c adds an extra induction variable: one more callee-saved reg, frame and bank order change". Here it's the reverse: target HAS the extra IV (e), mine doesn't.

Interesting: with the pin, target has the extra IV; lever-free, mine doesn't. So lever-free we'd need to force loop.c to keep the extra IV via real C. Real-C move: make `e` a pointer that is also used as the *call argument base*: `func_80016714((u8*)e - 4, 0x18)` — hmm.

Or restructure to use e directly in the loop increment: 
```c
base = D_801DA130;
for (i = 0; i < 0x40; i++) {
    e = (Sub_80180A54 *)(base + 4);
    ...
    base += 0x18;
}
```
is the current source. What if the source instead does:
```c
e = (Sub_80180A54 *)(base + 4);
for (...) { ...; e = (Sub_80180A54 *)((u8*)e + 0x18); }
```
Hmm, that's a different IV structure (e as the primary biv) — loop.c would then keep e as a biv. But the call needs base = e-4; the source writes base += 0x18 separately.

Actually — maybe simplest: `func_80016714(base, 0x18)` → the target uses s1 (base) for the call. If we write the call as `func_80016714((u8 *)e - 4, 0x18)`, the compiler needs e in a reg (s0) and base = e-4 (addiu -4) — but target uses s1=base directly. Hmm.

Alternatively, declare `e` as the loop's pointer and base as derived:
```c
u8 *base;
Sub_80180A54 *e;
base = D_801DA130;
e = (Sub_80180A54 *)(base + 4);
for (i = 0; i < 0x40; i++) {
    if (e->flag == 0) { ... }
    base += 0x18;
    e = (Sub_80180A54 *)(base + 4);
}
```
The compiler would still CSE base+4.

Hmm. Let me just try a handful of variants and score. Time is limited; item 4 is at score 10 (very close), so worth a few tries.

Variants:
v1: call with e: `func_80016714((u8 *)e - 4, 0x18);`
v2: `base = (u8*)e - 4;` no.
v3: change loop to use `e` as the loop variable:
```c
base = D_801DA130;
e = (Sub_80180A54 *)(base + 4);
for (i = 0; i < 0x40; i++) {
    if (e->flag == 0) {...}
    base += 0x18;
    e = (Sub_80180A54 *)(base + 4);
}
```
v4: make e point to base and access e[1]? no.

Actually, maybe the target's extra IV comes from the *pin* increasing register pressure, forcing loop.c to... no, extra IV increases pressure.

Let me look at loop.c's decision: `strength_reduce` → `find_and_verify_loops`... The derived biv is created by `record_biv` for `e = base + 4`? No — the register s0 is a *biv* (basic induction variable) for e, with `add_val 24`. loop.c's `strength_reduce` in `loop.c` calls `record_biv` on insns of form `e = base + const` inside the loop, and combines bivs: `combine_bivs` — it combines a biv with its parent if `v->mult_val` etc. There's a heuristic `loop_invariant_p`? Hmm.

Wait, actually the addiu s0,s1,4 at 31ec is OUTSIDE the loop (before it). That's loop.c's "biv initialization hoisted"? The loop structure in the source is a for loop; loop.c converts. In mine, `move s0,s1` before the loop then s0 = base and accesses at +6... So mine created a biv for base+4 but then `combine_bivs` folded it to base (since e = base+4 with mult_val 1, add_val 4 — combining gives base with add_val 4, which is expressed as offsets in the accesses!). Target did NOT combine. Why? `combine_bivs` has a condition: `if (v->mult_val != 1 || v->add_val ...)`. Let me read combine_bivs in loop.c.
