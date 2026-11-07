---
ts: 2026-11-06T21:33:28Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8dMX803bRgiGAERBMTop
---
w1 (pin kept, keepalive removed): the `sll s0,s0,0x10` (d = (s16)d) is scheduled at position 17 instead of 19. In the target, the sll is at 37d8 (after andi a0 and before andi s1), i.e., position 19. Mine has it at 17 (earlier). So the keepalive asm was pinning the sll later.

This is a sched1 order issue. The moves.md C0535 (do-while EBB split) or statement order might fix it.

But note: w1 keeps the pin (kinds include pin, so w1 = PARTIAL:pin only if score 0). To get a MATCH, I need both gone and score 0.

Let me first see w3 (both gone) diff — score 21. And w2 (pin gone, keepalive kept) diff. Let me understand the structure.

Actually, the target's order:
```
37d0: addiu v0,v0,-1024
37d4: andi a0,v0,0xfff      # u5
37d8: sll s0,s0,0x10        # d = (s16)d
37dc: andi s1,s1,0xfff      # u6
37e0: bne s1,a0
37e4: sra s0,s0,0x10
```
So after the ratan2 call: addiu/andi (u5), then sll/sra (d cast), then andi (u6), then compare.

In w1: sll at 17 (before andi u6 at 19?). Let me see the full sequence. The diff says mine[17] = sll, target[19] = sll; and mine has 75 ins. So the sll moved 2 positions earlier.

The keepalive asm `__asm__("" : : "r"(u5))` was between `u5 = ...` and `d = (s16)d`. Removing it lets sched1 move the sll earlier. So the keepalive is load-bearing for scheduling.

To replace it with a real-C move, per the similar func_8012BB3C: "C0535 do-while(0) on the div block (refs 7->9) cracks the $16 pin (div=$s0) and a 2nd do-while on the cast block replaces the keepalive ang anchor". So a do-while(0) on the cast block (`d = (s16)d;`) might anchor it.

But our function's keepalive is on u5, not on d. Let me try do-while around the cast block:
```
do { d = (s16)d; } while (0);  // !FAKE: do-while
```
That might keep the sll in place.

But first, the MATCH needs both levers gone. Let me try a comprehensive approach:
- Remove both pin and keepalive (w3, score 21).
- Add do-while(0) around the div blocks (to crack the $16 pin → make d land in s0).
- Add do-while around the cast block.

Let me look at w3's diff to see what's wrong with both gone.

Let me run dt.sh on w3.
