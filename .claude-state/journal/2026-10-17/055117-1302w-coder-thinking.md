---
ts: 2026-10-17T11:51:17.630Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a4daaa68013ad062c
model: claude-opus-5-5[1m]
effort: medium
turnId: 271cef5f-aa35-4bfd-88b6-c572019ec154
---
I'm wondering if gcc 2.7.2's scheduler avoided reordering around hard-register sets, possibly tied to how SCHED_GROUP_P pins a USE following a hard-register set like the return value assignment before insn 96's store.

Let me reconsider whether the loaded value could have been in v0 before scheduling—perhaps because the call returns a struct via a hidden pointer, with v0 holding the struct address rather than the value itself, which wouldn't match a load from offset 32 on the stack.

I'm testing two possible signatures: one where the outer function directly returns the call result as a W4 struct, and another where it's written through a pointer passed in a0. Both need to be checked against how the scheduler would treat the v0 dependency.

I also need to find the extern declaration for func_8012B77C before the definition, but since other call sites in the translation unit might use a different argument count, I should grep for all its usages before changing the signature to avoid breaking those callers.
