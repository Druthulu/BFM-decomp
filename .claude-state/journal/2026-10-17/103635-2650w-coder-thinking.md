---
ts: 2026-10-17T16:36:35.207Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac8178896d2313b85
model: claude-opus-5-5[1m]
effort: medium
turnId: 589d16b4-5a62-4ce6-8a45-63d170f3cb6e
---
I'm wondering if the three blocks reflect an unrolled loop, and considering whether using distinct symbol expressions for each address could prevent the compiler's CSE from merging them while still producing identical assembly.

Tracing how cse.c would weigh a pseudo register against the symbol_ref directly, since on MIPS the symbol_ref costs more (lui/addiu) so the register substitution wins unless that register gets invalidated by an intervening call clobber. This makes me wonder if the original code skipped an intermediate local variable entirely, passing the symbol address straight into a hard argument register instead.

I'm wondering whether `la` as a macro lets gcc 2.7's MIPS movsi accept a symbol_ref source directly into a1. Thinking through calls.c logic, maybe constant args skip precomputation into a pseudo unless they're non-legitimate constants, in which case they get forced into a register first.

Let me just try removing the m variable and passing the address directly in all the groups instead.
