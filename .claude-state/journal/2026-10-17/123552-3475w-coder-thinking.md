---
ts: 2026-10-17T18:35:52.533Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: aed641f299013cd69
model: claude-opus-5-5[1m]
effort: medium
turnId: a05808f2-3ac4-478a-96ff-4005570aa66e
---
I'm confirming that all loads are plain symbolic forms and store 72 is also plain, so there's no dependency there given the varying/non-varying exclusion rule. Looking at store 138's output dependencies, I notice it connects to 82, 92, and 115 but skips 72 and 103, which is curious since those are SI stores.

To make 72 actually conflict, I'd need a later access to the same symbol D_80076244 with a matching plain form that triggers rtx_equal — but that would change the instruction count in the target, so it doesn't fit. I'm also ruling out altering the store's address to a non-plain form, since the only difference there would be a relocation symbol mismatch, which doesn't affect the dependency score. I'm also checking whether folding zero offsets could create a false plain form, but gcc would just fold that away, so that's not viable either — I need to find a way to make the loads themselves non-plain instead.

Tracing the ready list at each cycle, store 72 keeps losing priority ties to the other instructions until it's the last one left, landing it 6th from the end. For it to schedule near the top instead, something else would need to depend on it so it only becomes ready late—meaning a later load or store must conflict with it, or some other use must force the ordering.

Store 92 also reuses a register, so I'm considering whether insn 70's target pseudo gets reassigned later—maybe the same variable holds the D_800BA320 address, gets stored to unk00, then gets reassigned to idx|0x2000 for unk04. That would create an anti-dependence from 101 onto 72, and since 101 feeds further loads giving it high priority, it'd likely get scheduled early, pushing 72 toward the top.

I'm checking whether existing variables like `t` or `ent` could be reused for this double-set pattern, but both have overlapping lifetimes elsewhere that would complicate things. It's probably cleaner to just introduce a new local variable for this purpose and test both approaches.

I see why it fails: the zero-offset store (insn 72) has no dependents in sched1, so it ends up near the block end at priority 1 — but reusing its value variable for the `idx | 0x2000` store would add an anti-dependence keeping it at the top. Let me try that temp-reuse fix.
