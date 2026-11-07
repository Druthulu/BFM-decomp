---
ts: 2026-11-06T07:42:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_M0DRAV4knBp0DBnXkQCE
---
Now compare the lreg final assignments for the two. Let me extract the ";; Register N in M." lines and the "Register N used ..." lines around block 0 for both. Better: find which pseudo is twicep (loaded from 180(sp)) and which is w3c (loaded from 0(s5)). Let me grep the RTL for "0 (s5)" etc.

Alternative approach: use diff of the .lreg sections. Let me extract each function's lreg section and diff. The dumps are large; let me write a small script or use awk to extract the section to a temp file and diff.

Actually, let me think about the real C instead. The key: without the keepalive, w3c reuses s5. With the keepalive, twicep's pseudo stays live so w3c gets a0.

The real C must keep twicep's pseudo live past w3c's death without emitting an instruction. Is there a real-C construct that references a parameter again but is optimized to no instruction? For example, `L.w3C = *(u32 *)twicep;` — that's a third load (would emit lw). No.

What if the original had `w3c = *(u32 *)twicep;` AFTER the GTE block? No, target loads at 40.

Hmm, wait. Let me reconsider: maybe the keepalive's real effect is on the *asm's operand register allocation*: `"r"(twicep)` requires a register for twicep at that point. The compiler could reload twicep from the stack into a scratch. But instead it kept s5. This extends s5's live range. In the natural original, maybe there's a value in s5 that IS used after the GTE block — but not twicep; perhaps `L.w38`'s value? No, L.w38 is stored.

What if the original source had a *different variable* assigned from twicep and used later, e.g.:
```
L.w38 = *(u32 *)twicep;
w3c = *(u32 *)twicep;
...
L.w3C = w3c;
w3c = (u32)L.o1;
```
No.

Let me look at the target's s5 liveness from the *original* binary: s5 is saved at entry and restored at exit; its value is used at insns 37 and 40 (`lw v0,0(s5)`, `lw a0,0(s5)`). After 40, s5 is dead. So in the real original code, s5 is dead after insn 40. Yet w3c gets a0. So the reason w3c gets a0 is NOT s5 liveness! Then why does the keepalive change it?

Because the keepalive changes the *allocation priorities* or the qty ordering. Specifically, adding a use of twicep increases twicep's refs (n_refs), changing qty_compare priorities in the block, which changes which quantity gets which register. The target's natural allocation gives w3c a0 without needing twicep live. So the lever-free body's allocation differs due to a qty priority/order difference caused by the missing use.

So I need a real-C change that flips w3c from s5 to a0. The relevant block: local-alloc allocates quantities in block 0. The quantities include w3c (birth 40, death 59), and maybe s5 is free at 40 in the natural code. Wait, but I argued s5 is live until 40. If s5 dies at insn 40, is it live AT insn 40? The load uses s5 at 40, so yes, s5 is live at 40. w3c is born at 40 (defined by that load). local-alloc's find_free_reg for w3c uses born_index = 2*insn_number? Let me check `reg_is_born` and post_mark_life. The birth/death indices are 2*insn_number and 2*insn_number+1 to handle birth/death at the same insn. If w3c is born at the same insn where s5 dies, the `used` check `regs_live_at[ins]` for ins in [born, dead) — born_index=2*40? s5 live_at includes 40? Depends on REG_DEAD note on the load: `(REG_DEAD s5)` on insn 40 means s5 dies at 40. `reg_is_born` marks birth at 2*insn; death at 2*insn+1? Let me look at the code around 1450-1520 to understand the ordering.

Actually, local-alloc's block_alloc iterates quantities in priority order and marks life with post_mark_life. The reuse of a dying register at the same insn is a known thing: local-alloc can reuse a register that dies in the same insn (the REG_DEAD is on that insn). In target it does NOT reuse s5 for w3c, so w3c got a0 (a lower-priority or different reg). In mine it reuses s5. The difference: qty ordering. In target, some other quantity (maybe another temp) took a0 first, pushing w3c elsewhere? No, target w3c IS a0.

Hmm, target w3c = a0, mine w3c = s5. If the allocator iterates in priority order, w3c's priority is the same in both. The register it gets depends on which regs are free at its range. In mine, a0..a3/v0/v1 are all occupied at w3c's range? Then it takes s5 (callee). In target, a0 is free, so it takes a0. Why would a0 be occupied in mine but free in target? Because in mine, the register allocator assigned some other quantity to a0 across w3c's range. The keepalive's use of twicep changed the allocation of that other quantity.

Wait, maybe in mine the GTE macro temp `t4/t5/t6` or the `v0` pointers occupy a0..a3 across w3c's range, and the keepalive changes that. Hmm.

Let me diff the lreg sections to see the actual allocations. Let me extract both sections and compare the ";; Register N in M." lines and the "Register N used" lines. I'll write a script to print the mapping for block 0 quantities in both. Actually alloc_table prints per-pseudo hard reg from .lreg. Let me diff the alloc_table outputs for orig and w1, focusing on the difference.
