---
ts: 2026-11-06T09:57:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2D646tHrxFNcjDjVpary
---
Now clear. Differences:
1. Lines 52-55, 58-59: the `t`/`tb` values. Source:
```
t = s0->unk4C;   // lw t, 76(s0)
s0->unk6 = t;    // sh t, 6(s0)
tb = s0->unk54;  // lw tb, 84(s0)
s0->unkE = tb;   // sh tb, 14(s0)
...
t = s0->unk50;   // lw t, 80(s0)
s0->unkA = t - 8; // addiu t-8; sh
```
Target: unk4C→v0, store v0; unk54→v1, store v1; unk50→v0, addiu v0,v0,-8.
Mine: unk4C→v1, unk54→v0, unk50→v1.

So target reuses v0 for t (both unk4C and unk50) and v1 for tb. Mine has t in v1 and tb in v0. Why? local-alloc picks register by... The load order: mine loads unk4C into v1 then unk54 into v0 — target loads unk4C into v0 then unk54 into v1. Both insns in same block. This is local-alloc's allocation order: local-alloc assigns quantities in order of first use/reg_qty. The first pseudo gets v0 normally? Actually for a load, the destination gets... Hmm.

In mine, unk4C (t first assignment) got v1, and unk54 (tb) got v0. Why would the first get v1? Because t is used later again (unk50 assignment), so t's live range extends and perhaps... no, local-alloc doesn't know beyond block.

Actually the difference may be that `t` is live across the whole block in mine? No.

Alternatively, the allocation is influenced by the fact that the barrier clobbered a0 in the original, and... no, the difference is v0/v1 only.

Hmm. Let's think about local-alloc (GCC 2.7.2 local-alloc.c). It allocates registers for pseudos within a basic block, using `reg_qty` and qty ordering. The block: after the store to 26(a2), we have:
- lw t,76(s0)
- sh t,6(s0)
- lw tb,84(s0)
- li a0,2274
- sw zero,48(s0)
- sh tb,14(s0)
- addiu v0,t,-8  (well, t-8)
- jal ...
- sh t-8,10(s0)

local-alloc's block_alloc processes quantities in order of... it combines quantities and assigns regs. The first allocated gets the lowest available reg? It scans insns in order and for each quantity allocates the first free reg from the `regs_live_at` etc. Actually local-alloc uses `qty_phys_reg` chosen by `find_free_reg` starting from 0.

Given target has t in v0 (first pseudo allocated v0), mine has t in v1. Perhaps because in mine the pseudo `t` conflicts with something that occupies v0? At line 52, is v0 live? Looking at mine line 51: `sh v0,26(a2)` — v0 is used there (dead after). So at line 52 v0 becomes free. Both should allocate v0.

Wait, but mine's line 52 lw v1: maybe `t` was allocated v1 because at line 52, v0 is still live from line 51's sh? No, sh uses it.

Hmm, but local-alloc considers all insns in block. Let me think of the quantity priority: local-alloc `block_alloc` iterates over quantities sorted by `qty_n_refs`? Actually in 2.7.2 local-alloc.c, `block_alloc` scans insns in order, and for each quantity not yet allocated, it calls `find_free_reg` with `qty_phys_reg`. Hmm.

Wait, actually the block here is the `if ((cnt & 7) == 0)` body. Let me reconsider: the "t" pseudo has 2 defs (unk4C and unk50) and 2 uses. tb has 1 def 1 use. In local-alloc, quantities that are live at block start/end are excluded. 

The ordering: local-alloc processes `qty` in order of `qty_first_insn`? Let me look at the 2.7.2 source at tools/reference/gcc-2.7.2/local-alloc.c.

Actually — key insight: `t` gets v1 in mine but v0 in target. The difference between mine and target source is only the pins and barrier. Removing the pin `s0 __asm__("$16")` → s0 is now a normal global allocno (or maybe local?). Hmm, but s0 is live across calls so it's global-alloc → s0 in $16 naturally. Removing `tb __asm__("$3")` → tb is local.

Hmm wait — the original had tb pinned to $3 (v1). So target tb is in v1 and t in v0. Lever-free, mine gives t v1 and tb v0. So the pin forced tb=v1; without it, the allocator picks differently: tb got v0 and t got v1.

So we need a real-C move that makes local-alloc prefer v0 for t (the first-defined one). Options:
- Declare tb before t? The declaration order affects global alloc but not local (block-local). Actually local-alloc quantity order may follow the order quantities were created (by insn scanning) — t first.
- Make tb's def happen later so t gets v0 first? t is already first.

Hmm, mine gives t=v1 even though t's def is first. That means local-alloc did NOT give the first-defined quantity v0. Why? Possibly because `t` is "qty" that has a conflict... Let me look at the actual 2.7.2 local-alloc algorithm.

Actually, a simpler hypothesis: the two loads are in the same block, and local-alloc's `block_alloc` first scans and records quantities. `t` and `tb` — t is defined at insn 52, tb at 53. But t is also used at 54 (sh) and 58? no. Then redefined at 55 (lw t,80). tb used at 58 (sh). 

Wait mine line 54 `sh v1,6(s0)` uses t (v1). line 55 `lw v1,80(s0)` redefines t (v1). So t in v1. tb in v0 at line 53 `lw v0,84`, line 58 `sh v0,14`.

local-alloc gives t=v1, tb=v0. That's odd: t defined first should get first free reg v0... unless the allocator processes in reverse or by priority.

Let me look at local-alloc.c in the reference.
