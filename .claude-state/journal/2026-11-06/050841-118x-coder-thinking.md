---
ts: 2026-11-06T12:08:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5CtWDRqI7YwgRpDWhYdo
---
All still 2. The li/lui swap persists. 

Let me look at v_both_argfirst's diff — maybe the aa variable changed something. All 2.

Hmm. The remaining swap is `lui v0,0x20` (unk14 value) vs `li a0,2432`. Let me think.

Target:
29 sw v0,16(s0)
30 li a0,2432
31 lui v0,0x20
32 sw v0,20(s0)

Mine:
29 sw v0,16(s0)
30 lui v0,0x20
31 li a0,2432
32 sw v0,20(s0)

So target computes li a0 (call arg) before lui v0 (unk14 value). Mine computes lui v0 before li a0.

sched2 priority. The li a0 is needed at the jal (37). The lui v0 is needed at the sw unk14 (32). The lui v0 is "more urgent" (needed at 32 vs 37). So sched2 schedules lui v0 first. Target schedules li a0 first.

Hmm. To flip, I need to make li a0 more urgent or lui v0 less. 

What if I reorder the source tail so unk14 is computed LATER? The target has unk14 (lui v0,0x20) at 31, after li a0. In mine, unk14 at 30. 

What if I move the unk14 store AFTER the 0x18 store in source? v_both_perm1 = 2 (same). Hmm.

What if I move unk14 much later (e.g., after unk48)? Let me try.

Actually, the target order: unk14 (31-32), unk48 (33,36), 0x18 (35), unk1C (38 delay). Source order: unk14, 0x18, unk48, unk1C. The sched interleaves.

Mine: li a0 at 31 (one late). If I could make the unk14 value (lui v0,0x20) schedule after li a0...

Let me try reordering the source so unk14 comes after 0x18/unk48. v_both_perm1 swapped unk14 and 0x18 → 2. Let me try moving unk14 to the end (before the call).

Let me test:
- v_both_unk14_late: unk14 store just before the call.
- v_both_unk14_after48: unk14 after unk48.

Let me also reconsider: maybe the li a0 is one late because of the do-while around the store creating a boundary. The do-while's end label is after the store. sched2 can't move the li a0 before the label? Wait, the do-while is around the STORE only:
```
do { CAST_WIDTH(0x10) = v; } while (0);
```
The loop's latch label is after the store. Then the tail. sched2 treats the label as a boundary? If so, the li a0 (in the tail) can't move before the label, so it's after the store (correct) but also after the lui v0,0x20 (which is also in the tail). Hmm.

Wait, the lui v0,0x20 is in the tail (unk14 store). If the tail is one sched region, sched2 orders li a0 and lui v0 within it. Mine puts lui v0 first. Target puts li a0 first.

Let me try moving the unk14 store to after the 0x18 and unk48 stores, so its lui is computed later.

Let me test a few permutations.

Time: 05:08:33. Item 4 ~12.5 min. Let me continue. We're close (score 2). If I can get 0, it's a MATCH!

Let me test permutations.
