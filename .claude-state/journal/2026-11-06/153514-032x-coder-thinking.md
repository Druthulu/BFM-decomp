---
ts: 2026-11-06T22:35:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM4
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_o78xo3RblAfHws9MniaT
---
45 — worse, same instruction count. Let me see the diff. Actually the local-alloc issue remains.

Let me dump w3's alloc to see if s1ang is still local. Actually, instruction count is 75, so the scheduler reordered. Let me check the alloc table quickly.

Actually, let me think differently. Let me look at what r75 is exactly and whether there's a way to make it not block-local via a source construct that doesn't add instructions.

The pseudo r75 is the result of `sign_extend(mem)` = the s1ang load. It's used once (the andi). To make it global, it must be referenced in 2+ blocks. Any extra reference adds an instruction unless cse eliminates the computation but keeps the value live... 

Wait! Here's an idea: what if the second reference is a *copy* that gets coalesced? E.g., `u6 = s1ang & 0xFFF;` and later in another block `t = s1ang;` — the copy `t = s1ang` would be an instruction unless coalesced. If coalesced (same reg), the copy disappears at regalloc... but the copy instruction is still in the RTL when local-alloc decides. Hmm, local-alloc sees the copy and may coalesce (reg_is_set / combine_regs). The copy would be in another block, making s1ang global (referenced in 2 blocks). Then global-alloc allocates s1ang raw (pri 2857) and d (pri 10000) — d first → $s0, s1ang → $s1. Then the copy `t = s1ang` might be coalesced away by global-alloc (copy propagation) → no extra instruction! 

But wait, the copy has a use of t that must do something. If t is unused, flow deletes the copy. Hmm. If t is used, extra instructions.

Unless the copy is coalesced into an existing pseudo that then... Hmm.

Alternative: make s1ang raw be *tied* to another pseudo via a copy that is eliminated by coalescing. For example, `u6 = s1ang & 0xFFF` where the andi output u6. If we instead write:
```
t = s1ang;          // copy in block 0? no
```
Hmm.

What if the second use is `u6 = s1ang & 0xFFF` in block 0 and the *first* use is elsewhere? 

Let me think about the register allocator's copy coalescing: global-alloc has `combine_regs` for copies (REG_NO_CONFLICT / copy coalescing). In global-alloc, a copy `a = b` can be coalesced if the allocnos don't conflict. That removes the move.

So idea: add a copy in a later block from s1ang to a variable that is then used identically to u6, such that the copy coalesces and the later code is the same. For example:

```
u6 = s1ang & 0xFFF;     // block 0
if (u6 == u5) return 0;
iVar4 = u5 - u6;
...
```
Add in block 2: `iVar4 = u5 - u6;` — no new.

Hmm.

What if we write the compare using a variable that copies s1ang:
```
u6 = s1ang & 0xFFF;
if (u6 == u5) return 0;
...
```
No.

OK here's a cleaner idea: use s1ang in the second if's block via a copy that coalesces:
```
if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }
if (iVar4 < -0x800) { t = (s32)s1ang & 0xFFF; iVar4 = u5 - t; }
```
The `(s32)s1ang` is a nop (no instruction) — it's the same pseudo. Then `& 0xFFF` is an extra andi in the second block, not cse-merged (multiple preds). That's an extra instruction (76). Unless... the second andi gets combined/eliminated? No.

Hmm, what if the second block's expression can *replace* the first computation, i.e., compute u6 in the second block and make the compare use a copy that's coalesced? The compare in block 0 needs the value.

Wait, actually: what if the compare is written as `if ((s1ang & 0xFFF) == u5) return 0;` and the *second* block uses `u6 = s1ang & 0xFFF;` where u6 is used in block 2. cse2 merges (w2) → block-local.

What if the second use is in the second-if block (multiple preds), and the FIRST (compare) computation is in block 0. Then s1ang is referenced in block 0 and block 5 (second if) → global. The second andi is an extra instruction. BUT maybe the second andi can be eliminated by combine: `(s1ang & 0xFFF) - 0x1000` → no.

Alternatively, the second block could use s1ang in a way that's already an instruction: `t = u6 - 0x1000` uses u6. If u6 is *not* available (because s1ang is global and u6...). Hmm.

Let me reconsider: maybe we don't need s1ang raw to be global. Maybe we need r75 to take $s1 because of a *suggestion*. The suggestion mechanism: if s1ang raw is used in an insn with a hard register operand that's tieable, it suggests that hard reg. Which hard regs appear in block 0? $2 (v0), $4 (a0), $5 (a1), $3 (v1), $16 (s0, the pin), $17 (s1). Without the pin, the available hard regs in the insns are $2,$3,$4,$5,$31.

Hmm, what if the s1ang load's result is tied to a hard reg... no.

Wait — what about `qty_phys_copy_sugg`: if a pseudo is copied to/from a hard reg. The andi `u6 = s1ang & 0xFFF`: if the output u6 were tied to a hard reg... no.

Hmm, but there's another suggestion: `qty_phys_sugg` is also set by `find_free_reg`'s `qty_alternate_class`? No.

Let me look at `find_free_reg` and how suggestions are used: "Try to put each quantity in a suggested physical register, if it has one. This may cause registers to be allocated that otherwise wouldn't be". So if r75 had a suggestion for $s1, it'd take $s1.

Where else do suggestions come from? In `block_alloc`, `alloc_qty_for_scratch` and the operand scanning: for each insn operand that is a hard reg, if the corresponding operand is a pseudo and tieable, suggest. Let me look at the code that fills qty_phys_sugg in block_alloc (around line 1123-1460).
