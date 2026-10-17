---
ts: 2026-10-17T10:55:15.011Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: affd4bdd851658ceb
model: claude-opus-5-5[1m]
effort: medium
turnId: 3036a8ad-ba82-454c-8ac7-51f507a74f6e
---
The remaining differences are just relocation immediates, confirming the opcodes match and the target schedule is barrier-free with the base opaque to CSE and scheduling. Now I need to figure out how to make an `la` load into a pseudo register that CSE and scheduling treat as opaque, using plain C without asm, volatile, builtins, or pinning -- starting with whether combine-time simplification without REG_EQUAL could prevent CSE from folding it.

I'm working through which RTL simplifications CSE's fold_rtx can't do but combine's simplify_rtx can, scanning things like AND with -1, IOR/PLUS/MINUS with zero, zero-extension of a subreg, and distributive law transformations — trying to find an operation on a symbol reference that stays opaque to CSE while still being something combine would normally simplify away.

I'm also considering real-world analogues like a KSEG0 pointer conversion via masking with 0x80000000/0x1FFFFFFF, but that changes the value unless the compiler knows the symbol's address bits, so it wouldn't get optimized away by either pass — it'd just leave extra instructions. I ruled out constant-indexed array access since CSE would fold it, and local stack array round-trips since CSE tracks stack memory but leaves dead stores, which would introduce extra instructions rather than eliminate them.

Looking at a union of same-mode fields next — since all members are SImode, the union could live in a single register and accesses through different members would just be reg-to-reg, which CSE could see through cleanly. I'm now wondering about PARALLEL insns with multiple SETs, like a divmod operation producing both quotient and remainder — that's another path where CSE's single-set requirement might matter.

I'm shifting to trace reg_n_sets: it's computed by reg_scan, and I need to check whether it's recalculated after cse1 or flow passes before sched uses it, since that count feeding REG_EQUAL's n_sets==1 check could be the real crux.

The one-slot shift leaves only relocation immediates as differences, which match_one already masks—so the target is just a `base` schedule opaque to cse and sched's alias oracle, with no barriers. Next I'll check where `reg_n_sets` is counted to see if a set dying before sched1 still counts.
