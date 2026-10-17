---
ts: 2026-10-17T12:26:29.037Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7981821383929cc1
model: claude-opus-5-5[1m]
effort: medium
turnId: 6481a00e-d05d-4284-8eb3-bba059849bf7
---
I'm considering how CSE in gcc 2.7.2 handles related constant addresses sharing a symbol with different offsets—when one register holds sym+k', it can rewrite another sym+k reference as a relative adjustment instead of recomputing it. This likely explains why the offset 0x5E94 shows up as derived from D_800A5E94.

I'm now tracing which struct fields actually route through the s0 base register across the three blocks, noticing block 1 only uses the -12 and 0 offsets while blocks 2 and 3 use the full set, and trying to figure out where the "s0 = D_800A5E94" pattern first gets established via the call argument setup (a1 = s0-12, s0+4, s0+20).

I'm wondering if the sibling function func_80144B9C, which writes similar fields and calls with &D_800A5E88, would compile identically with plain global stores — and if so, I need to check how gcc 2.7.2's MIPS move expanders and CSE handle `(mem (symbol_ref))` addresses under -G0 to see if that explains why one pseudo gets materialized as the base while the rest stay as absolute lui/at stores.

Thinking through how a1 would be loaded via la as a pseudo holding the symbol, then copied across the call into s0 since it's callee-saved. That matches the target code where s0 holds 5E94 and the first call arg is s0-12, suggesting the original source took the address of D_800A5E94 and indexed it with a negative offset like p[-12].

I should check what f2's diff looks like (score 5) versus h2 (score 10) to see what pattern remains unresolved, so I'll look at f2.c and rerun the diff script on both.
