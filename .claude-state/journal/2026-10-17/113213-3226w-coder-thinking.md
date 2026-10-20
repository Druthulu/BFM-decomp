---
ts: 2026-10-17T17:32:13.551Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm digging into why the register allocator picks v0 instead of a1 for this value—looking at whether the mode pseudo-register and the m variable get tied together through a copy, which would explain the target's register preference.

Separately, I'm puzzled why combine didn't simplify the `andi 0xffff` into a plain move, since the nonzero bits of cnt (computed as mode&0xff + 1) should fit well within 16 bits, making the mask redundant. I suspect the zero_extend/subreg interaction with cnt is blocking combine from recognizing that bound.

I'm also considering alternatives: using a different comparison expression, reordering which variable gets copied first, or extending cnt's live range past the call to disrupt CSE's equivalence tracking. None of these seem clean without changing semantics. So I'm going to dig into GCC 2.7.2's cse.c, specifically the make_regs_eqv logic.

Tracing through the register-equivalence conditions...

So the new register only becomes canonical if it lives outside the current cse basic block and its lifetime exceeds firstr's -- I'm working through how the extended basic block boundaries (following jumps) interact with the first/last use tracking for each register.

I check whether mode's last use (the call after the join label) falls beyond block end, while noting that the m variant fails equivalence since it's a QImode subreg truncation rather than a true SImode register copy.

I'm also considering whether -fcse-follow-jumps affects this at O2, and whether swapping which branch holds the assignment changes the outcome, recalling how jump.c can hoist an if/else assignment pattern by rewriting it as a default assignment followed by a conditional override.

Trying variants like assigning mode=0 first then conditionally overwriting with cnt — but that would reorder the generated instructions differently from the target, putting the zero-move first instead of last, so it likely doesn't match unless some other optimization pass intervenes.

I'm also considering whether the shared pseudo for the first value could be register-allocated to a1 instead of v0 through global allocation's copy-preference mechanism, since in the original both mode's first set and the later use share the same pseudo.

For the u8 variant, the andi instruction that zero-extends the result for the `cnt + 1` computation might be a separate temp rather than mode itself, which would explain why mode's first set doesn't inherit v0.

I should try the e-series too, and check what happens with s32 mode when compared against a constant that CSE can't fold — using mode's register directly for that comparison would be wrong if a1 got reused.
