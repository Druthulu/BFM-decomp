---
ts: 2026-10-17T08:17:01.226Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ac33bcc12f95b099e
model: claude-opus-5-5[1m]
effort: medium
turnId: 516610ee-47dc-40f0-aaa6-3a60ec3251d5
usage: {input: 14, cacheRead: 368975, cacheWrite: 6799, output: 2068}
---

T7 asked a question, and I answered it myself because it stays inside the milestone. T7 is now going on.

**What T7 finished.** T7 changes compiler pins into real declared function parameters. That part is done, and each batch rebuilt all 218 binaries byte-identical (218/218). The pin rows that still lack a declared parameter fell from 546 to 384. Of those, 383 are scratch registers the function writes before it reads, so there is no incoming value to declare. The last one, func_8017EC90, stays because dropping its pin changes the compiled bytes. Each of these rows records why it was refused, and the strict lever check passes.

**What blocked it.** One check still failed: the check that every remaining raw cast site is backed by a recorded decision. Five sites in two overlay functions failed it, func_80182998 and func_80185AC0. These sites read a signed field through a cast macro. Their decisions were recorded back when the value was a local variable, and now that it is a parameter the census calls it `param:X` instead of `local:X`. The matcher in `tools/restruct.py` treated those as two different values, so the old records no longer counted. The fix is a small change in `tools/`, which wasn't in T7's list of files.

**What I decided.** T7 may make that change, as its expert recommended. A recorded decision now counts when the value has the same name and the only difference is local versus parameter. The field offset and the reason the site was kept must match too, and nothing broader is accepted. After the edit it rebuilds the tool's corpus and runs the tools health check. Then it re-runs the five sites, the cast check and the full 218/218 build check. The other option was to rewrite those five sites in the source just to get past the matcher, so I didn't take it. The permission is recorded in the plan's change log.
