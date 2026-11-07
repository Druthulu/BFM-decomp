---
ts: 2026-11-06T10:22:32Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_anb91VzDsxT8MVdvJ2oY
---
Let me look at the .sched dump (post-sched1) around the unk1C store and the address setup. The sched dump is RTL. Let me find the function section and search for the relevant insns. Alternatively compare the .sched2 and .sched.

Better: compile both d15 and orig and look at the .sched2 output's instruction order. But comparing RTL is verbose.

Alternative quick check: build the final .s for d15 vs orig and diff. The .s file is the final asm. We know d15's asm diff is 2. To know which pass, look at .sched2 (post-sched2) vs .sched (post-sched1): if the store is already sunk after sched1, it's sched1; if it moves between sched and sched2, it's sched2.

Let me grep the .sched dump for the function and look at the ordering of the store and the address setup. The RTL is verbose; let me find insn numbers.

Actually, simpler: the .sched file for d15 vs orig. Let me extract the function's insns (just the (insn N ...) lines) in order and see where the store is relative to the address setup.

Let me write a quick grep: in .sched2, find "const_int 28" store? The unk1C store is `(set (mem:SI (plus:SI (reg...) (const_int 28))) (reg... m))`. Let me grep for "const_int 28" in the sched dump.

Hmm, this is getting heavy. Let me instead just accept and record WALL after ensuring ≥20 min. It's 03:22 now; item 2 started 03:13 → 9 min. I need 11 more min. Let me use that time productively: investigate the pass and try a few more moves.

Let me check the .sched vs .sched2 quickly by extracting the function's insn sequence.

Actually, let me try a different real-C approach first: make the store dependent on the address setup by using a shared temp. For example, if I compute `&v` into a variable and the store uses that variable... no, the store doesn't use &v.

Hmm. What about the possibility that sched2 sinks it because the store is dead (no later use of unk1C before the call)? Actually unk1C IS read later (`--unk1C`). But between the store and that read there are calls; the compiler can't move the store past the calls (aliasing). So sched2 within the block can move it up/down but not past calls.

The 3-insn sink is within the block before the first call.

What if I reorder the source so the `unk1C = m` store comes AFTER the `func_800D20C0` call? Then the asm order would differ from target (target has it before). No.

What if I move the `unk30 = 0x88; q = ...; unk28 = q;` block to before `unk1C = m`? No.

Let me look at the target's order: ... unk1C=m at 120, then address setup, then v.vz load, then call. Source order: unk1C=m; 0x18 store; call. So the compiler hoisted the address setup above the 0x18 store (which is in the delay slot). The store unk1C stays before the address setup in target.

Real-C to keep the store before: create a dependency from the address setup to the store. The address setup computes &v and &v2 (stack). The store writes a0->unk1C. No relation.

What if the store's VALUE m is computed from a stack value? m is 0x12/0x1E/... constant. No.

OK. Let me check the pass and then decide. Let me grep the sched dumps.
