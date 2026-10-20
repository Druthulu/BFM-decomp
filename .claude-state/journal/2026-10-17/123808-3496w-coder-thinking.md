---
ts: 2026-10-17T18:38:08.429Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a0b7566fdaca12346
model: claude-opus-5-5[1m]
effort: medium
turnId: 5fa06e7a-0d54-4425-8d05-7af8227a2b37
---
I'm examining why the target sequence keeps the load and store order tied to register v0's reuse, while my version hoists the load above the store since it uses a different register — trying to figure out if the pinned hardware register creates an anti-dependency that forces the scheduler to preserve that ordering.

I'm wondering if the pinned register scheduling avoids reordering because gcc's dependency analysis treats hard-register assignments specially across the block, maybe tied to how the call's return value in $2 creates an implicit ordering constraint even though nothing downstream reads it. This feels like a dead end without deeper digging into sched_analyze internals, so I'm considering other angles — maybe declaring t differently or computing it from a different source entirely.

Actually I think the real culprit might be local-alloc's quantity allocation order, which assigns registers by priority (based on reference count and live range length) rather than by birth order. The constant 1 has a very short live range, so it gets higher priority and lands in v0, while t's longer live range should've earned a different register — this priority-based allocation is probably what's driving the different register assignment I'm seeing.

Memrefs comparing the same base register with different constant offsets won't conflict unless the pointer arithmetic routes through a separate pseudo, which cse might still fold back into the same base anyway. Volatile would act as a barrier but I want to avoid introducing a new lever like that. The real issue is sched1's priority: the load-feeds-addiu-feeds-store chain has the longest latency, so it gets scheduled first as the critical path, whereas in the target that chain only gets computed later.

I'm wondering if making t's computation chain shorter or dependent on a different store could help — maybe by having the unk98 store's constant 1 shared with another later store (like unk1C) so it stays live longer, changing how the scheduler orders things.

I'll try a few cheap experiments: reordering the unk98 store to come after the t block, computing t inside the if-branch directly, or trying CAST macros to influence scheduling.
