---
ts: 2026-11-06T06:36:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FSR9U9V89rMEtTbPNpT0
---
No luck; v0/v13/v14 all 13.

The v1↔a0 swap. Let me look at the alloc table for v0 to see the pseudos. That needs a dump of the spliced TU. Cost: one dump + alloc_table.

Alternatively, try a few more variations: declare oidx before/after other variables, or change the tag expression.

The two competing pseudos: 
- temp for `*(u32 *)pkt` load (used in `and`, `or`, `sw`).
- oidx (used in the address of D_800A6614 and the `addu`).

Target: tag temp = a0, oidx = v1.

Local-alloc: qty priority = refs/live. If the tag temp has fewer refs or longer live, it gets a later reg. Hmm, target gives v1 to oidx (earlier/first reg) and a0 to the tag temp. So oidx has higher priority than the tag temp.

In mine, the tag temp gets v1 (higher priority) and oidx a0.

To flip: increase oidx's refs or shorten its live range; decrease the tag temp's.

The tag temp: `*(u32 *)pkt` loaded, then `& 0xFF000000`, `| ...`, `sw`. Live range is short (3 insns).

oidx: assigned then used in 2 places (address computations). Live range longer.

Hmm. In the target, oidx is v1 — the first caller-saved local reg after v0.

What if we make the tag temp longer-lived or split it? E.g. write the tag update as a compound assignment `*(u32 *)pkt &= 0xFF000000;` then `|= ...`? That'd be 2 loads/stores.

What about reordering the tail: compute `otp` first, then the pkt update? That changes the codegen order (target does pkt update first).

Hmm.

What about making `oidx` used once more? E.g. declare `s32 oidx` and use it in both address expressions — already 2 uses.

Hmm, what if the mask constant `0xFF000000` is a variable? no.

Let me look at the alloc table — it's the reliable way. Splice v0 into the TU and dump.

Actually, time: I'm ~70 min in on 2 items. Item 2 has PARTIAL:pin with score 0 (b2.c). That's a valid, good result. Let me try maybe 2 more quick things then record.

Quick idea: swap the declaration order of `oidx` and other locals. Or move `oidx`'s declaration.

Actually, here's a thought: maybe the tag temp and oidx swap because of the *load order*: `lw v1,0(a3)` (tag) comes before `lw v1,20(sp)` (g.otz) in the target — the tag load is first. In mine, `lw v1,0(a3)` then `lw a0,20(sp)`. So the assignment order is: tag temp created first, then oidx. In the source, `oidx = g.otz << 2;` comes BEFORE the pkt update. But the compiler emitted the tag load first, then oidx's computation — because the tag load is hoisted.

Hmm, in the target the tag load `lw a0,0(a3)` is at 6e68 and `lw v1,20(sp)` at 6e78 — tag first.

So in both, the order is tag-temp then oidx. Yet the target gives the tag a0 and oidx v1.

Local-alloc assigns registers to locals by qty order: higher priority first gets $2, then $3, ... Actually local_alloc assigns each qty the first free register in its preferred class order (v0, v1, a0, a1...). Hmm, so if the tag temp is allocated first it'd get v1 ($3) since v0 ($2) may be taken. And oidx next gets a0 ($4). That's MY result. The target is the opposite, meaning oidx was allocated FIRST (or has a preference).

Hmm, maybe in the target oidx's qty is created earlier (the pseudo is born at line 93, before the tag temp at line 94) — the pseudo *number* order determines the qty creation order in local-alloc (qtys are sorted by... hmm, by block and then regno?).

Actually local-alloc's `qty_cmp` uses: `if (qty1->n_refs * qty1->live_length ...)` hmm, it's `qty_compare_1` which compares `(int) ((qty2->n_refs * qty2->live_length) ...)`. Let me recall: local-alloc.c qty_compare_1:
```
  if (qty1->n_refs != qty2->n_refs) ...
```
Hmm, I'd need to look. But the alloc_table.py tool shows local pseudos too (the .lreg table) — it printed "53 pseudo(s) in the .lreg table". That's for the whole function.

Given time, let me just try: make `oidx`'s live range shorter or its refs higher. E.g. use oidx twice in the same expression? Or compute `oidx` later (v12 = worse).

Alternative: make the tag temp's live range longer by using it later... no.

Let me try declaring oidx with an initializer at decl (`s32 oidx = g.otz << 2;`) — that moves the assignment earlier (before the stores), changing the live range.

And try moving `oidx = g.otz << 2;` right after the mulc division (earlier).

Let me try 3 variants and then record.

Actually, better: let me just check the local-alloc rule quickly to know what to change. grep local-alloc.c qty_compare.
