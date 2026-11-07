---
ts: 2026-11-06T11:34:40Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_NhCeQ0fAGe866kwsPPX4
---
Target: the loads are into v0,v1,a0,a1 then a2,a3,t0,t1,t2 — exactly the pin registers $2..$5 = v0..a3, plus temps t0,t1,t2 for r8,r9,r10. So the pins forced r2..r5 to v0..a3.

The stores at the end use a2,a3,t0,t1,t2 (the r6,r7,r8,r9,r10 values, which live across the barrier) and v0,v1,a0,a1 (the second group r2..r5).

So target allocation:
- First group: r2..r5 in v0,v1,a0,a1 (pinned).
- Second group loads r2..r5 again into v0,v1,a0,a1.
- r6,r7,r8,r9,r10 in a2,a3,t0,t1,t2.

Without pins, I need to naturally get this. Key: the values must be in these registers. Since it's all one basic block (no branches), local-alloc/global-alloc assigns registers by priority.

Hmm. This is a "copy" function; the register assignment depends on live ranges. The first group r2..r5 die at the first store group (4 stores). Then r6,r7,r8,r9,r10 are live until the end. Then r2..r5 get new values.

Target has r6,r7,r8,r9,r10 in a2,a3,t0,t1,t2, and the second r2..r5 in v0,v1,a0,a1.

Now the order of stores at the end: a2,a3,t0,t1,t2 (r6..r10) then v0,v1,a0,a1 (r2..r5). Note in source, D_80126978=r6... come before D_80126970=r2...

Now how does gcc assign? Global alloc priority based on ref count and live length. All these vars have 2 refs each (one set, one use). The order of allocation: global-alloc processes in order of priority; ties broken by ... Let me think.

Actually the key insight: the target is the ORIGINAL compiler output. The original source likely declared the variables in a certain order, and the pins in the current def were added to force matching. We need to find real C that naturally produces this.

Let's think about what the original C might have been. The function copies from D_80120200 block to D_80126950 etc. Perhaps the original used `register` variables? No.

Hmm, this is the "headers1" rung B item; pins were needed. To delever we need real C.

Idea: maybe the original source used explicit typed local variables without any pins, and the natural allocation gives v0,v1,a0,a1 for the first group because they're set first and used first (local-alloc assigns in order?). Let me just test: my w1 had the loads all in one statement line, and got t3..t6 for the second Blk8 copy etc.

Let me actually look at w1's disassembly to compare. Let me dump it.
