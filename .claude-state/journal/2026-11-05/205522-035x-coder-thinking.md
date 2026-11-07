---
ts: 2026-11-06T03:55:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Fsq9B2ytqAgnYTIJ42vR
---
Target tail (from 77c8):
- li a0,8
- lh v0,46(s0)  [0x2E]
- lhu v1,14(s0) [0xE]
- subu a0,a0,v0
- lh v0,46(s0)  [0x2E] again
- sll a0,a0,0x9
- sll v0,v0,0x6
- addu v1,v1,v0
- sh v1,14(s0)
- sh a0,26(s2)
- sh a0,24(s2)

Mine (58 ins) presumably lacks the second `lh v0,46(s0)` — cse reused the first load. The barrier `__asm__("" ::: "memory")` between the `{s32 diff...}` block and the `{s32 x2 = *(s16*)(s0+0x2E); ...}` block forces the reload of 0x2E! Because a memory barrier prevents cse from reusing the earlier load.

So in target: `diff = 8 - *(s16*)(s0+0x2E); t = diff << 9;` then barrier, then `x2 = *(s16*)(s0+0x2E); *(u16*)(s0+0xE) += x2 << 6;` — the barrier prevents cse forwarding the 0x2E load, so it's loaded twice.

Wait but actually the barrier is placed after the `{s32 diff...}` block, before the x2 block. Without it, cse sees the 0x2E load and reuses it (single lh). Target has two lh. So we need a real reason for cse not to reuse. Options: a store between them that may alias? There is no store between. `t` is a local. Hmm.

Actually the target has: lh v0,46(s0) (for diff), subu, then lh v0,46(s0) again (for x2). The second load happens after `subu` but before `sll a0`. The C source has the two blocks adjacent. To force the reload in plain C: introduce a store to memory that cse can't prove doesn't alias s0+0x2E. The call? No call between. Hmm.

Wait, look at the target order: `li a0,8; lh v0,46; lhu v1,14; subu a0; lh v0,46; sll a0; sll v0; addu; sh`. So the `lhu v1,14(s0)` (the += load) happens early, before the second lh. That suggests the scheduler interleaved.

To break cse's 0x2E class: a real store that may alias. But adding a store changes code. Unless the store is already there: the `*(u16 *)((s32)s0 + 0xE) += (x2 << 6);` store is AFTER the load. cse processes in order; the second 0x2E load is before the 0xE store. So no.

Alternative: use a dead-reset (§373, C0414): a dead store that breaks cse's address class? The dead-reset technique: `pb = 0;` after a call to break cse's address class. Here, the value is a loaded s16 from memory; to make cse not reuse, we could store to the same location a value that's later overwritten? E.g., insert `*(s16*)(s0+0x2E) = *(s16*)(s0+0x2E);`? That's a self-store — would produce a sh (extra ins) but cse would then invalidate. But target has no extra store. However, the store could be eliminated by DSE? If we do a dead store to s0+0x2E and the value is dead (overwritten later)? There's no later store to 0x2E.

Hmm, but the barrier is a memory barrier — it stops cse AND sched. What real C produces two loads? A store to a location that may alias. Since s0 is a pointer (param), the compiler doesn't know it doesn't alias a global. If between the two loads there's a store to a global that could alias `*(s16*)(s0+0x2E)`... but s0 is a `s32*` from param; any store through a pointer could alias. Is there such a store between? The source order: diff block, then x2 block. The only stores are at the end.

Wait — maybe the original C didn't have the barrier; maybe the original had the two blocks in a different form where the first use was through a pointer alias that cse couldn't forward. E.g., the first block computed `diff = 8 - ((Unkstruct*)s0)->unk2E;` and the second `x2 = ((Unkstruct*)s0)->unk2E;` — same. cse would forward.

Unless the struct types differ! If the first load is through one struct type and the second through another (or a `s16*`), cse may still recognize same address+mode. In GCC 2.7.2 cse, loads are forwarded if same address expression and mode. Different types with same mode → same.

Hmm, what if the first load is `s16` and the second is `u16`? Different modes (QImode? no, HImode both). Sign doesn't matter for load.

What if the second is through a `char`/byte access? No, target lh.

Alternative: the target's second lh might be a genuine reload caused by register pressure: the first lh's value is in v0, used by subu. The second use could be a cse copy... Actually cse would replace the second load with a copy of the first pseudo, but then the value would need to stay live. In target, the second lh is a fresh load — cse didn't forward. So the barrier did it.

Real-C way to defeat cse's load forwarding: use a `volatile` load? That would emit a load and not forward. Declaring the pointer volatile: `*(volatile s16*)(s0+0x2E)`. Volatile loads are not cse'd. That's a real C qualifier, but is it a lever? Hmm. It changes the access to volatile which in the original source is unlikely. Also the target has `lhu v1,14(s0)` for the += load; the += involves a load+store; if volatile, the store would be volatile too. That's a "new lever of a kind" perhaps.

Let me think about the actual original source. This is ov_SC05_008 (a boss?). The function is a state machine. The barrier was added by the decomp author, not the original. The original compiler produced two loads. Why? Maybe because the original source had the two accesses through *different pointer variables* and GCC 2.7.2's cse couldn't prove they were the same? If the first is `*(s16*)((s32)s0 + 0x2E)` and the second is `((SomeStruct*)s0)->unk2E`, the addresses are both `s0 + 0x2E` — same RTL. cse would match.

Unless the first uses a temp pointer: `s32 *q = (s32*)s0;` no.

Hmm, what if the first access is a signed 16-bit load and the second is a 16-bit load at a *different but overlapping* address? No, target same 46(s0).

What if there's a call between them in the original, and the decompiler moved code? No.

Let me look at the target more carefully: the two lh 46(s0) are at 77cc and 77d8, with `subu a0,a0,v0` between and `lhu v1,14(s0)` before. The C source order is:
```
{ s32 diff = 8; diff -= *(s16*)(s0+0x2E); t = diff << 9; }
[barrier]
{ s32 x2 = *(s16*)(s0+0x2E); *(u16*)(s0+0xE) += (x2 << 6); }
```
Target insns: li a0,8; lh v0,46; lhu v1,14; subu; lh v0,46; sll a0; sll v0; addu; sh. So the second lh is indeed separate.

Idea: make the second access depend on a value that could alias. E.g., assign `x2 = *(s16*)((s32)s0 + 0x2E);` but first do `*(s32 *)((s32)s0 + 0x2E) = ...`? no.

Dead-reset C0414: a dead store that breaks cse's class. If we write `x2 = *(s16*)(s0+0x2E); ...` preceded by a store to a location that cse thinks aliases the load? cse's load forwarding is invalidated by any store that may alias. A store through `s0` at a different offset — cse tracks address classes; a store to `0x2E(s0)` would obviously alias; a store to `0x2C(s0)` with different mode might still alias (cse's alias for MEM of different addresses: it compares base+offset exactly? cse's canon_reg/expressions: for memory, it uses "same address and mode" for load forwarding; a store invalidates loads whose address may alias. GCC 2.7.2's cse invalidates a load if a store's address is not known distinct. `s0+0x2C` vs `s0+0x2E` — offset differs by 2, cse may or may not consider distinct.

But any such store would add an instruction to the output. Unless the store is dead and eliminated... but it'd still appear if it's a real store to memory.

Alternatively, maybe the original source simply had a call or something removed. But the decomp is byte-exact with barrier; the original source is unknown; we need any plain C that compiles to the same bytes.

Volatile idea: `s16 x2 = *(volatile s16*)((s32)s0 + 0x2E);` — the load won't be forwarded. But then the earlier load `*(s16*)(s0+0x2E)` is non-volatile; cse won't forward a volatile load from a prior non-volatile load (it just doesn't record/forward volatile). And the store `*(u16*)(s0+0xE) +=` — if x2 is volatile-loaded, the store is normal. Output: lh (volatile) + normal store. That might match exactly. But is volatile a lever? The brief says "no new lever of any kind". Hmm, volatile is arguably a codegen lever (it suppresses cse). But the kinds list is barrier/launder/pin and the allowed moves are "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)". Volatile isn't in the catalog. So I should avoid it.

Hmm. Let me reconsider: maybe the original source structure is different, e.g., the two accesses are in the same expression or the first is via `diff` computed before a function call? No.

Wait, maybe the first `lh v0,46(s0)` and the second aren't both from 0x2E. Let me re-read target:
77cc: lh v0,46(s0)   -> x = *(s16*)(s0+0x2E)
77d0: lhu v1,14(s0)  -> y = *(u16*)(s0+0xE)
77d4: subu a0,a0,v0  -> a0 = 8 - x
77d8: lh v0,46(s0)   -> x2 = *(s16*)(s0+0x2E)
77dc: sll a0,a0,0x9
77e0: sll v0,v0,0x6
77e4: addu v1,v1,v0
77e8: sh v1,14(s0)

Yes, two loads of 46(s0).

Hmm, what if the C used a union or a different access width that generates the same lh? Like reading via a `u16` and then sign-extending? A u16 load would be `lhu`. Target `lh` = sign-extended. So s16.

What if the first access is part of `diff -= *(s16*)(s0+0x2E);` where diff is `s32` — the load is HImode. Second is `s32 x2 = *(s16*)(...)`. Same.

Idea: split the pointer: first block uses `s0` as `s32*`; second block uses a `s16*` pointer variable `sp = (s16*)s0;` — cse canonicalizes addresses: `(s16*)s0 + 0x17` vs `s0 + 0x2E` — these are different RTL expressions? `s0+0x2E` as byte offset vs `(s16*)s0 + 0x17` scaled by 2 = s0+0x2E. After expansion they might be identical (MULT then PLUS folded to const). GCC folds constant offsets into a single PLUS. So same.

But what if the second access uses a char* cast: `*(s16*)((u8*)s0 + 0x2E)` — same.

Hmm. What if the second load is through a different base variable that cse can't prove equals s0, e.g., a function parameter copy `s32 s0copy = s0;`? cse would copy-propagate.

What if we use `arg` (the original param) for one and `s0` (local copy) for the other? The body has `param_1` and then `s0 = (s32*)param_1;`. In target, s0 = param. If the first uses `param_1` and the second `s0`, after copy propagation they're the same. Unless... cse's copy propagation may not merge a param with a local copy? It does.

Hmm, maybe the trick: the barrier is memory-only, so it only stops memory ops, not the sched. The double load could also arise if the first load's value dies before the second (register pressure) — but cse replaces the second with a copy and the pseudo stays live.

Wait, actually, does GCC 2.7.2 cse forward loads? Yes, cse has "cse_insn" handling MEM: it records loads in a table and can replace a later load with the register. But it only does so if the value is still available (no intervening store and the register not clobbered?). cse registers the value with a certain "reg" and replaces later uses. So without the barrier, one load.

So the original must have had something that prevented cse: likely a store or a call between them. Let me look at the actual source around: 
```
    func_80182654((s32)s0);
    {
        s32 diff = 8;
        diff -= *(s16 *)((s32)s0 + 0x2E);
        t = diff << 9;
    }
    __asm__("" ::: "memory");
    {
        s32 x2 = *(s16 *)((s32)s0 + 0x2E);
        *(u16 *)((s32)s0 + 0xE) += (x2 << 6);
    }
```
What if the original had a store between: `*(u16*)(s0+0xE) = ...`? No.

Maybe the original had the `+=` expanded as `x2 = *(s16*)(s0+0x2E); *(u16*)(s0+0xE) = *(u16*)(s0+0xE) + (x2 << 6);` and the compiler... the load of 0xE happens before the store. The store to 0xE could alias 0x2E? If cse processes the second 0x2E load BEFORE the store (source order: x2 load, then 0xE load, then store), no.

Hmm wait — what if in the original, the `+=` was written FIRST and x2 loaded after? Like:
```
*(u16 *)((s32)s0 + 0xE) += (*(s16 *)((s32)s0 + 0x2E) << 6);
```
Expansion: load 0xE, load 0x2E, shift, add, store. Target order has lhu 0xE at 77d0, then lh 0x2E at 77d8, then sll/add/store. And the FIRST lh 0x2E at 77cc is from the diff block. So yes! The compound expression `*(u16*)(s0+0xE) += (*(s16*)(s0+0x2E) << 6);` would produce: load 0xE, load 0x2E, ... in that order. But cse would still forward the second 0x2E load from the first (diff block) unless the store invalidates. The store is after.

Hmm, but the ORDER of the two loads (0xE then 0x2E) matches target: lhu v1,14 then lh v0,46. In the current source with `s32 x2 = load; += (x2<<6)`, expansion is load 0x2E then load 0xE, and the target shows load 0xE BEFORE load 0x2E. But sched1 could reorder. In mine (no barrier) the order at 44-46 was `sh v0,14(s0)` only; let me see the full mine to compare.

Let me disassemble the nopin candidate for item2.
