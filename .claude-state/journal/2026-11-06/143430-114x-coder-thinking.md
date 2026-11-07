---
ts: 2026-11-06T21:34:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mRJCCmWvf1Q80NGHVh4z
---
func_8012BB3C is a similar but different function (4 args, different structure). Its header still has the levers (pin $16, keepalive on ang) — so the G27x crack was not banked (it was a WALL, per moves.md). The moves.md line says the do-while moves cracked the $16 pin and replaced the keepalive anchor, but a residual remained (extendhisi2 temp). So it was a WALL.

For our func_8012B8E4, the structure is a bit different. Let me analyze more carefully.

Our target's key allocation: d → s0 ($16), s1ang → s1 ($17). Without the pin, d → s1, s1ang → s0. So we need d in s0.

The pin forces d to $16. Without it, the allocator picks s1 for d. To make d get s0 via real C, we can change the *priority* of d vs s1ang. s1ang is `*(s16 *)(*(s32 *)(arg0+0x20)+0x12)` — a load, used in `u6 = s1ang & 0xFFF` and the compare. d (arg1) is used in the two divisions and the cast.

In w3, d → s1 (refs: arg1 copy + cast + 2 divs = ~4-5 refs). s1ang → s0 (refs: load + andi + compare = ~3). Hmm, d has more refs but got s1. Global-alloc priority might favor the other.

Wait, in w3 the register pairs show s1->s0 x6, s0->s1 x4. So mine uses s1 where target uses s0 (6 times: d's uses) and s0 where target uses s1 (4 times: s1ang's uses). So indeed d=s1, s1ang=s0.

To swap, we need d's allocation priority to beat s1ang's, or add refs to d. The C0535 do-while(0) on the div block should add refs to d (loop depth). But w5 (div do-while) = 21 (same as w3) — maybe the do-while didn't add refs because the div block is already in an if/else and the do-while(0) is optimized away before flow? Hmm.

Actually, C0535 says do-while(0) splits cse1's EBB. The ref-weight mechanism (loop_depth) applies in flow's `REG_N_REFS` for loops. A do-while(0) might not create a real loop (it's optimized). Let me check: in the worked example func_80181F4C, `do { r = p + i; } while (0);` gave "+1 loop-weighted ref on p". So flow counts the do-while as a loop (loop_depth+1) for refs. It worked there.

For d, we need more refs. d is used in both divisions. Adding a do-while around each division adds 1 ref per use? Let me check the w5 asm: maybe the do-while didn't change the allocation because d already had enough/not enough.

Let me look at the w5 diff to see if the allocation changed.

Actually, let me reconsider: maybe the issue is not just allocation but the keepalive's scheduling anchor. In w1 (pin kept, keepalive gone), the only diff is the sll order. So with the pin, everything else is right except the sll. That means:
- If I can fix the sll order with a real-C move, w1 would score 0 → PARTIAL:pin (pin kept, keepalive removed).
- For a MATCH, I also need to remove the pin and get d→s0 via real C.

The PARTIAL:pin path might be easier. Let me first crack the sll order in w1.

w1 diff: `sll s0,s0,0x10` at position 17 instead of 19. The target has it after andi u5 and before andi u6. In w1, it's before andi u5? Let me see the full w1 asm.

Actually, the diff:
```
delete mine[17:18] target[17:17]:  sll s0,s0,0x10
insert mine[20:20] target[19:20]:  sll s0,s0,0x10
```
So mine has sll at 17, target at 19 (0-indexed). Positions: target 17=andi a0 (u5), 18=sll, 19=andi s1 (u6)? Let me look at the target instruction list positions. The target:
0 addiu sp
1 move v0,a0
2 sw s0,16
3 move s0,a1
4 sw ra,24
5 sw s1,20
6 lh v1,14(v0)
7 lui a0
8 lh a0,0(a0)
9 lh a1,6(v0)
10 lw v0,32(v0)
11 subu a0,v1,a0
12 lui v1
13 lh v1,0(v1)
14 lh s1,18(v0)
15 jal
16 subu a1,v1,a1
17 addiu v0,v0,-1024
18 andi a0,v0,0xfff
19 sll s0,s0,0x10
20 andi s1,s1,0xfff
21 bne
22 sra s0,s0,0x10

Hmm, the diff indices are for the sequence matcher, not raw positions. Let me just dump w1's asm.

The point: the keepalive asm was anchoring the sll after the andi. Removing it lets sched1 move the sll earlier (before andi u5?). To anchor it with real C, use a do-while around `d = (s16)d;`? Let me test w7 = w1 + do-while on cast. But w6 (w3 + cast do-while) = 38, which is worse. Maybe on w1 it helps.

Let me test w7 = w1 (pin kept, keepalive gone) + cast do-while.

Also, let me test w8 = w1 + do-while on the div block (to see if it changes the sll order).

Let me create these.

Actually, wait. Let me reconsider the whole approach. The do-while(0) in w6 made things worse (38). Let me look at what w6's diff is. But first, let me try simpler scheduling moves for w1:
- Reorder statements: move `d = (s16)d;` after `u6 = s1ang & 0xFFF;`? The target has the sll between andi u5 and andi u6, so `d = (s16)d` is before `u6 = ...` in C (as in orig). The order in C is: u5=..., keepalive, d=(s16)d, u6=..., if. Without keepalive, sched1 moves sll earlier. 
- Add a real use of u5 after the cast? That's a launder.

Hmm. The keepalive is on u5 (not d). Its removal causes the sll (d cast) to move. Why? Because the asm on u5 is a scheduling barrier (asm has priority 1 and can't be reordered across easily). Removing it lets sched1 reorder the independent sll.

Real-C move to replace a scheduling barrier: C0414's dead-reset or C0535's do-while. The do-while(0) around the cast block might act as a barrier.

Let me test w7 = w1 + do-while around `d = (s16)d;`. And w8 = w1 + do-while around the div blocks.

Let me create and score.
