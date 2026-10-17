---
ts: 2026-10-17T16:55:51.897Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: ab7c1b2050f875aa7
model: claude-opus-5-5[1m]
effort: medium
turnId: e9067380-d3b2-4c4e-97d8-f140a92e4fcf
---
I'm trying to figure out why combine might be rejecting the merge of these two instructions—looking at whether it's a 16-bit masking operation feeding into a subsequent arithmetic instruction, and whether the register tying is causing the mismatch.

Let me consider other possibilities: maybe cse keeps a different pseudo canonical, or the copy originates from a call return value or reload inheritance scenario, or there's a live range conflict across a conditional path where one variable gets reassigned later. I'm sketching out what the underlying source code might look like to produce this exact pattern.

Maybe the test happens before the copy, inside a conditional block, where the temp is checked then copied to v1 in the then-branch, followed by the subtraction — so combine's ability to merge depends on whether v1 dies right after that subtraction, which it should regardless of whether the sign-extension is a separate temp or the same variable.

I'm checking the time budget and deciding to look at the second site (0x108) since it might be easier and shares the same mechanism. The 0x106 site shows the identical pattern — load, branch-if-zero, move, decrement — suggesting a systematic source idiom, maybe something like a field being checked for nonzero then decremented as a signed 16-bit value.

I'm working through how gcc would expand an assignment-in-condition like `if ((v1 = p->f) != 0)` — the compiler likely sign-extends the memory load into a promoted temporary, tests that temporary, then reuses it for the subtraction via CSE rather than reloading from memory.

The tricky part is making the copy survive instead of being eliminated: if v1's canonical register ends up being the longer-lived one, CSE would rewrite the test and subtraction onto it directly, deleting the separate copy insn as dead — so I need the subtraction's source to escape substitution some other way.

Another path: maybe the copy isn't visible to cse because it only emerges after combine simplifies a sign-extension shift pair back into a plain copy, something cse never saw. That means combine itself would need to create the equivalence post-hoc, and I'd need to trace how combine's instruction ordering affects when that simplification happens relative to insn 26.

I'm running low on time here, so let me just try a few more quick ideas on the decrement-via-field case instead.

I'm wondering if the merge of insn 23 into 26 could still work even if v1 stays live afterward, say if it's reused in a comparison rather than dying right there.

I'm leaning toward accepting this is a wall for now, but want to first double-check the REG_EQUAL theory—specifically whether combine rejects the merge because the RTL isn't equal in some subtle way.

Checking another angle: combine won't merge across a call if the insn's cuid exceeds the last call cuid, but there are no calls between these insns here. I'm also ruling out jump or volatile concerns, and considering recording this as a wall under a "combine-copy-merge" tag, since combine appears to fold the copy of v1 into the decrement while v1 dies, leaving only the hard-register escape—worth testing against the moves.md hint about the HImode copy escaping CSE equivalence.

That escape idea was really about CSE. Now I'm testing a variant where an s16 copy is declared before the branch so it escapes CSE's register-class equivalence, forcing the comparison to stay on v0 while the copy sits in one block and gets used in another—blocking combine from merging across blocks, similar to the earlier cross-block idea but driven by CSE escape rather than calls. I sketch loading v0 from memory, copying it into an s16 h before the branch, then using h minus one inside the branch, reasoning that the sign-extension truncation needed for s16 from s32 won't be a trivial equivalence, so combine would just simplify it to a copy within block A before the use happens in block B.
