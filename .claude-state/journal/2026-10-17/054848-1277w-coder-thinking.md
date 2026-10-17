---
ts: 2026-10-17T11:48:48.231Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a8e969c8cbf9244d6
model: claude-opus-5-5[1m]
effort: medium
turnId: 150f717e-3914-450b-b185-2137b70bb2af
---
This looks like the same allocno structure referenced earlier, where s7 and s8 likely point to the sz0 and sz1 fields within the g struct, based on the field offsets I'm working out.

I'm trying to figure out exactly which gte register (SZ0, SZ1, etc.) maps to which struct field by comparing the swc2 instruction order between my version and the target, since the ordering of stsz3/stsz4 operand emission could explain the difference. Based on the register numbering ($16=SZ0, $17=SZ1, $18=SZ2), I'm recalculating the struct layout — otz at sp+220, flag at 224, opz at 228, sz0 at 232, sz1 at 236, sz2 at 240 — to match where the swc2 stores are landing.

This confirms it's a priority tie between the live ranges of &g.sz1 and &g.sz2, mirroring the earlier header example, so I need a plain C way to either shorten sz2's live range or extend sz1's to flip which one wins the tie and gets created first.

Wait, since both pseudos are live across the whole loop, adding one insn there bumps both lengths by 1 — 784/783, and the priority ratio shifts due to integer rounding: 3*13*10000/784 rounds to 497 but /783 rounds to 498. So the lever isn't about which range grows, it's about exploiting rounding from any instruction-count change in the shared live range — even a no-op copy insn that later gets deleted could do it.

I'm trying to figure out whether such an extra insn survives long enough to affect flow's live-length computation, given that combine and flow run in a particular order in gcc 2.7, and whether a temp assignment that isn't eliminated before flow analysis would leave a trace in reg_live_length.

Testing the launders: removing both gives output 3 matching the expected order, while removing just one still leaves a mismatch around lines 42-44. So the launders seem to act as a pair, and I want to try removing both together with the barrier to see how close that gets to the residual difference.
