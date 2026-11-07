---
ts: 2026-11-06T12:11:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_DuNhbFv79YwGC14TLa7J
---
Now the results row for item 4. best=2, tries=~70, wall=sched1-birth-order.

Evidence: "do-while around 0x10 store fixes the sink; sched still puts lui v0,0x20 (unk14) before li a0,2432 (call arg) — target reverses them; only a memory barrier holds it. Best 2"

Trim to ≤140: "do-while around the 0x10 store fixes the sink; sched still puts lui v0,0x20 before li a0,2432 (target reverses); only a memory barrier holds it. Best 2" ~140.

Let me count tries accurately: orig(1)+nopin(1)+gen(5)+gen2(4)+gen3(6)+gen4(4)+gen5(3)+gen6(2)+gen7(2)+gen8(3)+gen9(3)+gen10(4)+gen11(3)+gen12(2)+gen13(2)+gen14(4)+gen15(2)+gen16(5)+gen17(4)+gen18(3)+gen19(4)+gen20(3)+gen21(3) = let me sum: 1+1=2;+5=7;+4=11;+6=17;+4=21;+3=24;+2=26;+2=28;+3=31;+3=34;+4=38;+3=41;+2=43;+2=45;+4=49;+2=51;+5=56;+4=60;+3=63;+4=67;+3=70;+3=73. So ~73 tries.

Let me put 73.

Let me append the results row (separate step).

Time: ~05:11. Item 4 started ~04:56 → 15 min. The writeup will bring it to ~05:16.

Let me append results.
