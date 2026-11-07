---
ts: 2026-11-06T12:17:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XCocgSBljpPAdN1ApDEu
---
Everything sits at 7 (except f2/f6). The statement order in C barely matters — sched1 reorders. So the residual is a register-allocation fact: vh needs a0, vv2 a1, and the schedule.

Let me check whether the f-variants' residual is identical to v3's. Probably yes (same signature). Let me check one, f3 (no temps).

Also, maybe I should reconsider: perhaps the residual is caused by the do-while around the store adding loop notes (which change ref weights for q/attr/tpage) — no, cluster A got fixed and B's residual existed before too.

Idea: the asm's real effect: it makes vh/vv2/vw live ACROSS the asm statement, so the register allocator must give vh and vv2 different registers, and vw too. But more importantly, sched1 must place the asm; the asm is a scheduling barrier? `__asm__("")` without volatile — it's a non-volatile asm with operands. Does it act as a scheduling barrier? In gcc 2.7.2, asm insns are "asm_insn" and sched1 treats them as having a latency... An asm with outputs/inputs constrains. It also can't be moved across other memory ops? Actually the asm has no memory clobber, so it's just a USE of those three regs. That forces all three to be live at that point → the allocator gives each a register and their priorities rise.

So real-C equivalent: make each of vh, vv2, vw live at the same point by adding a real use. E.g., compute all three before the stores, then store them all after:

```
v0.vx = p->unk8;        // a load
vv2 = p->unkA;
vw = rec >> 16;
vh = rec >> 24;
v0.vy = vv2;
v0.vz = sz;
v1.vx = vw & 0xFF;
v1.vy = vh;
v1.vz = sz;
```
That's f5-ish. Hmm.

Wait, but with the asm, the order in target: srl vh at 373 comes BEFORE the load lhu a1 at 376, and vw's srl at 375 between them. In the asm version, the asm sits after all the stores, so it doesn't directly force the srl order.

Alternatively: maybe the residual is entirely about which register (a0 vs v0) vh/vv2 get. Let's look at the f3 (no temps) diff.

Let me check f3 and f5 diffs.
