---
ts: 2026-11-06T11:41:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XuK4JwJcDchsFXW8JRre
---
Excellent! This technique is exactly for the sched1 reordering. Let me try wrapping the Blk8 copies (or the whole store group) in `do{}while(0)`.

The symptom here is different: sched1 hoists/interleaves the Blk8 copy. But a do-while block split might prevent the hoisting across.

Let me try several placements:
- do-while around Blk8#1 only
- around the group A stores + Blk8#1
- around the whole body
- around each group

Let me test.
