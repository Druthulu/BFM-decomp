---
ts: 2026-11-06T21:13:57Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7FQOM6tFWjoHA4PvHbtv
---
Line 12/18/42 are for func_8017E590 (first function):
- Register 76 (idx) used 4 times across 22 insns; crosses 1 call.
- Register 79 (e) used 2 times across 4 insns; pointer.
- Register 95 (off) used 3 times across 8 insns.

So e: n_refs=2, live_length=4. off: n_refs=3, live_length=8.

Global priority = floor_log2(n_refs)*n_refs / live_length * size.
off: floor_log2(3)=1 → 1*3/8 = 0.375.
e: floor_log2(2)=1 → 1*2/4 = 0.5.
e > off! So e should be higher priority. But the order shows e last. Contradiction!

Unless allocno_live_length is not reg_live_length. Let me check: allocno_live_length[allocno] is set from reg_live_length of the pseudo. Hmm.

Wait — maybe allocno 79 in the "regs to allocate" list is not pseudo reg 79. The list shows allocno numbers? Let me check global.c line 1652: `fprintf (file, ";; %d regs to allocate:", max_allocno); for (i=0;i<max_allocno;i++) fprintf (file, " %d", allocno_reg[allocno_order[i]]);` — allocno_reg[allocno] is the pseudo reg number. So the list is pseudo reg numbers in allocation order. 79 is last.

Hmm. But priority says e higher. Unless the size: e is "pointer" (4 bytes), off is 4 bytes. Same.

Wait, maybe allocno_live_length is measured in a different unit or includes REG_EQUIV effects. Let me look at how allocno_live_length is set.

Actually — maybe e has a REG_EQUIV and is *not* allocated by global-alloc at all, but the list includes it? No, it's in the list.

Let me reconsider: maybe there are MULTIPLE allocnos for reg 79 (one per basic block)? No.

Hmm, wait: line 1019-1025 is a LATER function (func_8017E7DC?) — no, line 1019 is still within func_8017E590's flow dump? The flow dump for the first function goes from line ~1 to where the next function starts. dump_flow_info prints per function. The first function's dump includes all regs. Lines 1019+ might be another dump (flow runs multiple times, or the dump is per-function after each pass).

Let me check line 1-50 context and where the first function's dump ends.

Actually the key numbers: reg 79 used 2 times across 4 insns. reg 95 used 3 times across 8 insns. So e pri 0.5, off pri 0.375 → e first. But order says off (95) before e (79). 

Unless the priority uses allocno_size: e is pointer (size 1 word), off size 1 word. Same.

Let me re-read allocno_compare: pri = floor_log2(n_refs)*n_refs / live_length * 10000 * size. e: 1*2/4 = 0.5. off: 1*3/8 = 0.375. e > off. So e should come first.

But the "regs to allocate" order has 95 at position 8 and 79 at position 12 (last). So my assumption about which pseudo is which may be wrong. Let me verify: in the lreg dump, off = reg 95, e = reg 79. But after local-alloc/global-alloc, reg numbers may be renumbered? The greg dump line 4 is from global-alloc BEFORE renumbering, so pseudo numbers. Let me double check the greg RTL: insn 54 sets reg:SI 4 a0 (already hard). That's the .greg dump AFTER allocation. But "regs to allocate" at the top lists pseudo numbers 78,108,...,79.

Hmm wait — the greg dump shows the RTL AFTER global-alloc with hard regs substituted. But the pseudo 79 appears in the list. After allocation, reg 79 → a1.

Let me re-examine: maybe reg 79 is not e. In the .lreg dump, e = reg 79 (set at insn 73 from symbol_ref). In the greg dump, insn 73 sets reg 5 a1. So 79→a1=e. Yes.

So the order contradiction stands. Let me look at the actual allocno_live_length values — maybe they're set from reg_live_length BEFORE flow recomputes, or maybe allocno_live_length is computed differently (e.g., number of blocks?).

Let me read global.c where allocno_live_length is set.
