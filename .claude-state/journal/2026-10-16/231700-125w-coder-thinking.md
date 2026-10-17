---
ts: 2026-10-17T05:17:00.024Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a7f214c1b8ceabcd8
model: claude-opus-5-5[1m]
effort: medium
turnId: edd2b196-9038-4e7d-9ca7-b103d9ac818f
---
I'm tracing that func_80185578 appears identically in both SC03_014 and SC03_015, confirming it's a genuine shared source file compiled into both builds rather than coincidental byte overlap, while the SC06_022 overlay has distinct bytes entirely.

Now I realize the "5 same-address copies" from legacy T7 don't actually hold up — my hash comparisons show those are different functions with different sizes, so only the SC03_014/015 pair is a real copy with one shared source. The remaining work is checking that each definition's signature matches its callers' arity and return type within its own binary, especially flagging cases like SC02_011 where a caller passes extra arguments, and SC04_002 where a caller seems short.

I'm planning a scratch tool that, given a function and a binary directory, lists the definition's signature alongside all declarations and call sites within that binary's source tree, accounting for shared headers across directories. Starting my pass with func_80188DF4.
