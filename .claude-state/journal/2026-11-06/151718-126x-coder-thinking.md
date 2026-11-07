---
ts: 2026-11-06T22:17:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0cq48fhUPIgpIlXH0jQN
---
o4 = 3 (same as i2). o2=9, o3=10.

So the sxy reorders change the ORDER residual but don't reach 0.

The residual is stubbornly the constant pair position. Let me look at o4's diff vs i2's — same 3?

Let me think differently: maybe the constant pair's position is determined by a *scheduling barrier* — the nop delay slots. In the target, the mask is after `lhu v0,8(sp)` (165). In mine, after `lhu v0,0(sp)` (161). The difference is 2 sxy store groups.

What if I reorder the sxy stores so the schedule naturally places the mask later? o2/o3 changed it to 9/10. Perhaps a different combination lands at 0. Let me try more reorderings of the sxy store block (there are 6 lines; permutations are many). I could brute-force a few targeted ones:
- move `*(s16 *)(pkt + 0x20) = sxy[1].vx + w;` earlier/later.
- move `*(s16 *)(pkt + 0x10) = sxy[0].vx + w;`.

Since the target's schedule is fixed, the scheduler output depends on source UIDs. A brute-force over a few permutations could find 0. Each score ~2-3s; 20 permutations ~1 min. Let me do a systematic search over the 6 sxy lines (720 permutations is too many; try moving one line at a time).

Actually, the mask placement might be determined by the *constant's* UID relative to the sxy insns. Reordering sxy lines changes the sxy UIDs, which changes the ready-list tie.

Let me brute-force: generate all permutations of the 6 sxy lines (720) — too many. Instead, try 20 random/structured permutations.

Actually, better: the target's schedule order of the sxy stores is:
```
sh v0,8(a3)    (sxy[0].vx - w)
sh v0,18(a3)   (sxy[0].vy -> 0x0A and 0x12)
sh v0,10(a3)   (sxy[0].vy)
sh v0,16(a3)   (sxy[0].vx + w)
sh v0,24(a3)   (sxy[1].vx - w)
sh v0,34(a3)   (sxy[1].vy -> 0x1A and 0x22)
sh v0,26(a3)   (sxy[1].vy)
sh v0,32(a3)   (sxy[1].vx + w)
```
Interesting: the target order interleaves the vy double-stores.

Our i2 schedule probably matches these (since only the mask differs). The mask is placed 3 slots earlier.

Hmm, what if the mask's *first use* (the packet store's and) is what anchors it? In target, the and is at 191; the mask at 166 (25 slots before). In mine, mask at 163, and at 191 (28 before). 

The scheduler hoists the constant as early as the ready list allows. The ready list at slot 163 vs 166 depends on which sxy insns are ready. If I make one more sxy insn ready before the mask, the mask slips.

Since o2/o3/o4 changed the score to 9/10/3, the tie is sensitive. Let me brute-force permutations of the 6 sxy lines and score them. 720 is too many, but I can do 30 random ones. Let me generate 24 permutations (structured: cyclic shifts and swaps) and score.

Actually, let me first check whether ANY permutation can give 0 by trying a batch of 20 random permutations. Each score ~3s → 60s. OK.

Let me write a generator that shuffles the 6 sxy lines with a fixed seed, 20 variants, plus some targeted ones. Then score. If one hits 0, great.

But careful: the sxy lines include two double-stores (`= *(s16*)(pkt+0x12) = ...`) which are single statements. Reordering is legal (independent stores). The target's instruction order must still match; sched1 will reorder them, so source order only affects UIDs/ties.

Let me do it.
