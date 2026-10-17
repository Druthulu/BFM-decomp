---
ts: 2026-10-17T10:47:58.528Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: abb6ffee7b1153d5a
model: claude-opus-5-5[1m]
effort: medium
turnId: bd46829b-96df-48df-a479-540852ff007c
---
I'm noticing my instruction ordering differs from the target—the target initializes a2 and a3 first before computing the shift and address offsets, while mine computes the shift value first and defers the zero-move. I need to reorder these instructions to match.

The real question is whether the scheduler's backward list-scheduling in sched.c can produce the target order even if the source emission order differs, since priority depends on dependency chains: the constant-loading lui/ori pairs form a two-instruction chain while the simple moves and shift have shorter chains, which affects tie-breaking in rank_for_schedule during backward scheduling from the block's end.

Found that c29's shared-size move pushes lever-free reaches to 4, leaving a pure preheader ordering issue where only source order t3v, k, j produces correct allocation. Next I'll check how sched1 orders independent preheader instructions.
