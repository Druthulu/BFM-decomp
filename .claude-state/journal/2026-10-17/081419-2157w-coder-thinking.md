---
ts: 2026-10-17T14:14:19.447Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abe7336983cc0fdaf
model: claude-opus-5-5[1m]
effort: medium
turnId: ad81449e-f0c8-40b2-83c6-f273f94996ed
---
I'm noticing some dead computations that look like they build a sprite rectangle's bottom-right corner (u1, v1), but the results get overwritten immediately in the target code. This suggests the original source assigned these to variables used later, and some dead-code elimination pass after flow analysis stripped those uses out.

I'm considering whether combine deletes an unused consumer, or whether jump2/reorg removes unreachable code after a branch becomes known — tracing through the gcc 2.7 pass order (rtl → jump → cse → loop → cse2 → flow → combine → sched → local-alloc → global → reload → sched2 → jump2 → dbr) to figure out which stage could leave a computation live at flow time but strip its use afterward. I also briefly consider whether a `register` variable with inline asm keepalive semantics could explain it.

Then I think about whether a store into an unread local struct/array field could survive, but recall gcc 2.7's flow pass doesn't do dead-store elimination on frame memory, so that path doesn't fit either. I'm now circling back to whether flow's dead-set deletion for pseudos could be suppressed by some quirk like a REG_RETVAL/libcall note or a user variable marked volatile.

I consider other ways the arithmetic result could appear dead and get dropped — as the condition of an empty if block that jump optimization strips early, or as an ignored expression statement where gcc's expand_expr skips computing the value entirely. I also think about a volatile memory read keeping the load alive while the subsequent address arithmetic becomes dead and gets removed, but the target still contains both the addu and addiu, so that doesn't match. This pushes me toward the idea that the arithmetic must still be live when flow runs, meaning whatever consumes it gets eliminated afterward — by combine, scheduling, reload, or the second jump/delayed-branch pass — and I start considering what combine specifically might do to erase that consumer.

Looking more carefully, I'm trying to connect this to the actual texture-mapping context: su+w-1 and sv+h-1 represent right/bottom texcoords, and the loop stores u0-u3 using an SR3 offset plus uu, with poly[-1].u3 set from su plus another SR3 offset afterward — so I'm trying to figure out where exactly u+w-1 would get consumed, possibly in some clamping or min operation downstream.

Given the time spent (~8 minutes on S20) and the remaining candidate levers (zr pin at 35 points solo, L48 at 14, L64/L81 at 10 each, L124 at 8), I'm recognizing this likely won't fully close in the remaining budget, but I want to test a couple quick hypotheses before logging results. My first hypothesis: replacing the zr pin so that su is computed as a copy of t plus zero, making it a straightforward register move that gets coalesced naturally rather than reusing t's register directly — solo this could be worth something.

Looking at the target assembly, su ends up as a copy of t followed by an add, with t staying live afterward because it's used again elsewhere, which forces separate registers naturally. This all depends entirely on whether those "dead" computations are treated as real, live code — if they were genuine computations, the register allocation here would make complete sense. My second hypothesis is that these dead computations might actually be loop bounds or variables that became dead only after a later optimization pass, but that doesn't fit since the loop runs before the flow analysis in question.

I'm now considering reload-pass scenarios, where a value feeding only into an insn that reload later deletes — like a no-op move into a pseudo with no hard register, or an assignment to a pseudo equivalent to a stack-slot parameter. Another angle: variables used only inside an if-statement where both branches are identical, so cross-jumping after jump2 merges the branches and deletes the comparison/jump insn, but its input operands remain behind as "dead" uses.

Cross-jumping itself seems tied to a later pass (jump2, controlled by a flag), not the initial jump1 pass — jump1 mainly handles the simpler `if (x) goto L; L:` pattern rather than fully identical branch bodies.

If cross-jumping deletes the branch while keeping the comparison's inputs intact, that matches the target sequence where lbu/addu/addiu persist but the compare/branch vanish. I'm trying to match that to the `if (tpage & 0x10)` check for sv, wondering if the dead computation for `t+w-1` corresponds to an analogous `su + w - 1 > 255` check with identical if/else arms that got cross-jumped away.

But that feels invented rather than something a real compiler would produce naturally. I'm considering instead that the source might have used a macro like `setUVWH` storing into struct fields that were later overwritten, except gcc 2.7 doesn't eliminate dead memory stores — unless the struct was small enough to be kept entirely in registers.

A two-byte struct could live in a single pseudo register, with field assignments becoming bit-insertions that read-modify-write that pseudo. If the whole struct is later overwritten wholesale, those chained insertions become dead and flow analysis could delete them entirely.

I'm overanalyzing S20, which is a long shot anyway. The current best recorded score stands at b0 43, with no clean path to improve it through lever-free tricks—the identical-arms diagnostic idea is a dead end since it's invalid as a "close." I'm weighing whether to revisit S16 or spend a modest effort trying alternate S20 levers, like replacing dead keepalive computations with genuine uses feeding into other logic.

I decide calling S20 a wall is reasonable given the evidence, though the stated budget says I should use the full time rather than stop early. I'll spend a bit more time checking whether gcc's flow analysis deletes dead instructions before reload, since that affects whether the dead-computation trick is even viable.

I'm also considering registered variables pinned to hard registers, which flow won't delete sets for since they're fixed — but that's forbidden here. So the dead computation must instead be consumed by an insn that combine later eliminates: if a consumer merges and the value dies there, combine deletes the producer, not what we want. What I need is a case where the consumer insn gets simplified away by cse while the producer remains untouched.

I'm testing cases like truncating a shifted value to a narrower type, which combine might simplify into storing a zero constant directly — but that doesn't obviously fit the target pattern either. I'm also scanning through the loop body's constant assignments and reload sequences, looking for an insn where the destination is overwritten before use.

Let me pivot to the S16 problem: whether cse can recognize that pointer p stays a compile-time constant only works cleanly when assigned directly from a symbol reference, but if p is instead computed through pointer arithmetic involving a table base and offset difference, cse's ability to fold that back down to a symbolic constant may break — that's a lead worth pursuing further.

I've hit the S16 wall now. Time to write up the log: roughly 283 tries for S04 (including 240 permutations), 20 for S08, 207 for S12, 28 for S16, and 8 for S20, spanning about 10, 8, 13, 12, and 12 minutes respectively.

S20's keepalives force dead computations that plain C can't preserve—compiler flow deletes unused arithmetic results before combine, which is a hard wall. I'm closing S20 and writing up the log.
