---
ts: 2026-10-17T11:41:40.258Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7979eba5885c3edf
model: claude-opus-5-5[1m]
effort: medium
turnId: 921e828f-1fac-424f-94a0-d040638a6158
---
Comparing costs, the register form is cheaper than the constant-symbol form, so find_best_addr would favor keeping the register. That means the folding likely happens somewhere else, perhaps during RTL expansion or within CSE's fold_rtx when it processes the PLUS expression and canon_reg substitutes the base register with its known constant equivalent.

Actually, the more likely culprit is reload rematerialization: since base is a pseudo holding the address of a static/global variable, it would get a REG_EQUIV constant note, and if local/global allocation decides not to give it a hard register across the call, reload could rematerialize the constant directly at the use site instead of restoring it from a saved register — which matches the generated lui/lhu sequence using a fresh register.

To defeat this, I'd want base to be set more than once, or derived in a way that isn't foldable to a pure constant, so update_equiv_regs won't attach a REG_EQUIV note and the pseudo gets normal register allocation instead of being rematerialized at each use.

I'm checking whether global_alloc actually substitutes constants only when the pseudo got no hard register, and recalling that update_equiv_regs marks reg_live_length as -1 for registers equivalent to memory or constants so global allocation skips assigning them a hardware register.

I should test with a dump whether base gets allocated normally when it's set twice—like being assigned an address and then decremented by a constant offset—to see if CSE would fold that into a single constant and thus affect the set count.

But in the target's assembly for arr, the constant did fold cleanly, so cse must not have seen the base as a known constant there — meaning the base assignment and use likely sit in different EBBs, perhaps split across a label boundary like an if/else or a loop structure, rather than cse simply being blind to it. I'm wondering if the extern declaration style matters here too, though that seems less likely than a control-flow split explanation.

I've spent roughly half an hour on this exercise already, including four tries plus this analysis, so per the no-gain rule I'll try a few more concrete variations — setting the base twice naturally, declaring it as an array extern — then stop if nothing changes.
