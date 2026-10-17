---
ts: 2026-10-17T10:58:19.302Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ae39e3e55ca2abfd6
model: claude-opus-5-5[1m]
effort: medium
turnId: 50f5af05-e353-44b9-ba7b-703e4f789154
---
CSE spans extended blocks across jumps at -O2, so the comparison register persists as the canonical one even with an explicit conditional. That means the target code should compare against the original value directly rather than through a copy, confirming it uses the absolute-value instruction pattern rather than a separate move-and-test sequence.

Thinking through the other scheduling route: if I keep the value local rather than global and untie it from the stored copy, its liveness depends on whether a later store happens before or after the abs operation. If that store has no dependency forcing it earlier, the scheduler could defer it—but I need a scenario where something forces it to come strictly after the abs operation, which would require an output dependency chain through an earlier scalar store that keeps it anchored later in the sequence.

That dependency would have to hold identically in both scheduling passes, which seems to always push it to the end rather than placing it where I want. So I'm now considering whether the anti-dependence instead comes from a load before the store—if that load is on a scalar varying address rather than an in-struct one, it would force the store after the load, with the abs operation boosted and positioned right before its first use.

Tracing the backward scheduling order with this setup, abs still ends up placed before the store, meaning the value still dies too early at abs. So this path doesn't resolve the issue either.

I need a different trick entirely: maybe make v die in two separate places by making it global or using it in another block, or force a tie-break by giving v and d the same quantity assignment, which could change which register gets freed first.

Let me reconsider the global allocation priority order itself — maybe some other variable's placement could shift things so d or v gets forced to a different register slot instead of pins being flagged forbidden.

But actually the HImode trick for v breaks correctness since it'd sign-extend when storing to the s32 result, adding extra instructions, so that path's a dead end unless usedreg resolves through a SUBREG to a different, larger backing register, which would change usize to match the full register size rather than v's nominal size.

I should also check MODES_TIEABLE_P in mips.h to confirm whether these mode combinations are actually considered tieable there.
