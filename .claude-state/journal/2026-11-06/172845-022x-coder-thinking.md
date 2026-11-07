---
ts: 2026-11-07T00:28:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CsaIoOre7OC6jfYQ0p74
---
Target: 
- First use (2db8-2dc4): lui v0; lw v0; lhu v1,42(s0); lhu a0,18(v0).
- Second use (2dd8-2de4): lui v0; lw v0; lw v1,44(s0); lhu v0,18(v0); bnez v1; sh v0,42(s0) in delay slot.

So indeed two separate pointer loads. Note also 2d98: lw a1,32(s0) (obj) early — obj loaded before the first use. And note the sh a4a20014 (store to obj+0x14) at 2dd4.

So the target's source order: after the call, loads svec_out fields, then obj = a0->unk20 at 2d98 (early, before the unk2A/pointer loads), then the first pointer load + lhu 42(s0), then lhu 20(a1) + subu + addu + sh.

Interesting: `lw a1,32(s0)` comes at 2d98, right after `lhu v0,24(sp)` — so obj is loaded early. That's because the src body computes `obj = a0->unk20;` as a statement before the big expression. Good, my w1 has that too.

Now in my w1 the first pointer load went to a2 at insn 18-19 (early, before lhu v1,42(s0)) — sched1 hoisted it. In the target, the pointer load (lui v0/lw v0) is right after lhu v1,42(s0)... no wait, target order at 2db8-2dc4: lui v0, lw v0, lhu v1,42(s0), lhu a0,18(v0). So the pointer load is BEFORE lhu v1,42(s0). And in mine, lui a2; lw a2; lhu v1,42(s0) — same relative order! The difference is only the register (a2 vs v0) and that mine does it once.

Wait, the diff hunk 1 says "delete mine[18:21] target[18:18]" with mine 18,19,20 = lui a2; lw a2; lhu v1,42(s0) vs target nothing at those positions. Hmm, that's because the target's lines shifted: target has extra instructions at 25-29 (3 extra: lui, lw) so alignment. The diff alignment is confusing; the real difference: mine 67 ins, target 68 ins; mine has one fewer pointer load (2 vs 3 pointer loads... target has 2 loads: 2db8/2dbc and 2dd8/2ddc = 2 pairs = 4 insns; mine has 1 pair = 2 insns; difference = 2 insns, but mine has 67 vs 68 = 1 fewer, plus a nop difference).

So essentially the only real difference: the second pointer load pair missing in mine → my second use reads lhu v0,18(a2) with a2 cached, and the delay slot gets a nop.

So I need real C that forces a reload of D_80126B78's pointer value between the two uses.

Given cse's invalidate_memory only removes in_memory entries when `all`, or `nonscalar && in_struct`, or addr varies:
- `(mem (symbol_ref D_80126B78))`: addr doesn't vary → only `all` removes it.
- `all` is set by: a call, or an asm with memory clobber (line 7246, 7981 contexts).

So the only real-C way to invalidate is a call. But the target has no call between the two uses... unless the target's own compile had cse NOT record the symbol load in the table in the first place.

Hmm! Alternative: maybe cse doesn't record it because of `dest` handling — cse records a load only if it's "cheap enough"? In cse_insn, a MEM load is recorded in the table always (with hash). Hmm.

Wait, maybe the issue isn't cse but combine or reload. Let's think: maybe cse DID record it, but the value in v0 was clobbered — v0 is call-clobbered but there's no call. However! Look: at 2dc8 `lhu v0,20(a1)` — v0 is reused for the a1 load in the target. And in the target's second use, the pointer goes to v0 again. In mine, the pointer is in a2 (callee... no, a2 is caller-saved) — local-alloc chose a2 and reused it.

So the difference could be *register allocation*: with the cse-cached value, local-alloc must keep it live across the store; it picks a2. In the target, cse didn't cache, so no live value, and v0 is free.

So the question remains: how does the original source prevent cse from caching the symbol load? Let me check whether cse's table records `(mem (symbol_ref))`. Actually, in cse_insn, for a load, `if (dest)` it calls `insert` on the full SET source... hmm, cse records the *source expression* (the MEM) as an expression with its value = the destination register.

But here's a subtlety: cse records the value only if the SET is a simple set whose source is a "stable" expression; `(mem (symbol_ref))` is fine.

Hmm, but wait — cse1 is run *before* flow? Order: cse1, then flow, then combine, then cse2? Actually in gcc 2.7.2, cse runs twice: cse1 and cse2 (after loop). Also there's "delete_dead_from_cse".

Another thought: the store `sh v0,20(a1)` — a1 is a register, so the address varies → any store invalidates entries with varying address, but not the symbol entry.

BUT the *store to 42(s0)* (`sh v0,42(s0)`) is the second use's destination.

Hmm what about `lw v1,44(s0)` — a0->unk2C read.

OK so what real C could break cse between the two uses? The catalog's C0414 "dead-reset cse-breaker": a dead store to a variable that cse sees as a memory write at a *varying* address? No, it breaks the equivalence of the *register* (2nd set).

Hmm! Maybe the mechanism is different: cse's `(mem (symbol_ref))` entry has value reg a2. If the value register gets a second set (e.g., the temp is reassigned), cse's table entry remains but points to a reg whose value changed — cse handles that via reg_tick. If the reg holding the cached value gets modified, the entry is removed (that's the "2nd set kills" mechanism). So: if the source uses a *local variable* for the pointer value and assigns it twice, e.g.:

```
s32 *gp = D_80126B78;   // load 1
...use gp...
gp = D_80126B78;        // 2nd set: cse would replace with a copy from the cached reg... 
```
cse would still substitute the cached reg for the second load (a copy), not a reload. Unless the second assignment's value is different.

Hmm, alternatively: what if the two uses read DIFFERENT symbols/addresses in the original source? E.g., the target's source might read `D_80126B78` and the second might read through a pointer that was computed... no, both lui/lw D_80126B78 with the same relocation.

Wait, actually — maybe in the target's compile the first load is recorded, but the SECOND load is issued because cse's entry was invalidated by the `sh v0,20(a1)` store? Let's check: does cse invalidate a symbol MEM on a nonscalar store? `p->in_struct` — what sets in_struct? Let me look at how in_struct is computed in insert: `p->in_struct = (MEM_P (exp) && ... )`? Let me grep.
