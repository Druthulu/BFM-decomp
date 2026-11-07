---
ts: 2026-11-06T21:44:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hAVyICymRHqBj1wNaB4t
---
This is the global-alloc table (allocno_compare priority), not local-alloc qty table. The function has 13 global allocnos? Hmm. But our pseudos in the tail are block-local, handled by local-alloc (lreg dump).

Wait — the tail block might be a single basic block, and local-alloc assigns. The alloc_table shows global allocnos (those live across blocks). The tail values r116 (v0, refs1), etc. are local.

Let me look at the .lreg dump for the local allocation. The .lreg dump prints local-alloc's decisions? gcc -dl prints local-alloc RTL before/after? Let me grep the dump for "qty" or the register assignment.

Actually the alloc_table covers globals only. For local, we need the .lreg dump: it prints the RTL after local register allocation? Let me look at the file size and grep for our insns.

Alternatively, use the qty priorities directly from local-alloc's own debug output? local-alloc.c has no priority dump unless -dl prints. Let me check what -dl prints: "dump_local_alloc" prints the RTL after local_alloc with hard regs. So we can see which pseudo got what, but not the priority arithmetic.

But we can compute: from the .flow dump, get reg_n_refs; from the .lreg (or .sched) the live ranges.

Hmm, this is getting deep. Time budget: 20-30 min per item, 4 items. I've spent ~10 min on item 1. Let me be efficient.

Alternative pragmatic approach: try a handful of structural variants quickly. Since each score takes ~1-2s.

Let me think about what could give oidx higher priority. The simplest arithmetic: n_refs oidx 4 vs packet 3, or oidx life shorter.

Wait, actually — maybe the reference didn't compute oidx once. Look at target: at 203 `addu v1,v1,v0` reuses v1 (oidx) *after* it was already used at 184. So oidx is live across the packet store. Fine.

What if the reference source declared oidx and used it in the *first* store with a different expression that adds a ref, e.g., `D_800A6614[oidx + ...]` where `oidx` is used as `(oidx + (tag<<14))` — no.

Hmm, let me reconsider the packet word. In the target, the packet word pseudo is in a0 and its uses: 190 `and a0,a0,a2` and 193 `or a0,a0,v0`. But wait, is the value loaded at 174 actually used at 190? Yes a0.

n_refs: 1 def + 2 uses = 3. Live 174..193 = 19.

oidx: def at 178? Actually the def is the `sll v1,v1,2` at 182, but the source register (otz load) is at 178. In RTL, oidx's pseudo is defined by the shift at 182. So birth=182, death=203 → life 21. refs 3. pri 3/21=0.143 vs packet 3/19=0.158. Packet still higher.

Unless flow's n_refs counts the *use in an address* differently... no.

Hmm, what if in the reference, the packet word has only 2 refs because combine merged the `and`+`or` into one use? No, both needed.

Let me actually look at the .flow dump n_refs for our body and identify the pseudos. The .flow dump prints register numbers with "Register N used ...". Let me grep for "Register" in .flow. But mapping to our tail requires the RTL. Let me look at .sched (after sched1, before local-alloc) RTL for the tail, find the pseudos, then .flow gives n_refs.

That's a lot. Given time, maybe a cleverer empirical approach: try variations and see if score drops.

Variation 1: change the packet-word expression to use a temporary declared `u32` (SImode) - already effectively.

Variation 2: split the final expression: instead of `*otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);` — the reference target at 205-209 matches.

Variation 3: reorder the two address computations: compute `otp` BEFORE the packet store. Source:
```
otp = (u32 *)&D_800A6614[oidx + ...];
*(u32 *)pkt = ...;
*otp = ...;
```
Hmm that changes store order.

Variation 4: Make `oidx` used *earlier* (birth earlier) so its life is longer → worse. No.

Variation 5: Make oidx's death earlier by computing the second address before the packet store: then oidx death ~185 instead of 203, life 182-185=3 → priority 3/3=1 → oidx gets $2 even. But then the address (otp) would be computed early and live long (the otp pointer), taking another reg. The target computes otp late (194+). So no.

Variation 6: The tag load appears twice (181, 200). In the reference it's twice too. Each is a 1-ref temp with pri 0.

Hmm.

Let me reconsider: maybe the reference's oidx is NOT a local qty; maybe oidx got allocated by global-alloc because the tail block is entered from two paths (the `if` returns). No, the tail is a single block after all branches.

Wait, actually the function has early returns; the tail block is the merge. oidx is defined and used entirely within the tail block → local-alloc.

Let me look at the .lreg dump to see the actual local allocation and its order. Maybe there's a "qty" listing. Let me grep.
