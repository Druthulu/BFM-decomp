---
ts: 2026-11-06T10:48:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4MYmNC3TtgToLTKzhMgr
---
v_addr4: score 2, correct regs (t v0, a v1), only the store sank (position 34 vs 31).

So the persistent issue: the store to 88 sinks. In block2 the source order is: a=...; unk58=a; unkC4=t|2. sched1 emits: lui, addiu, ori, sw 196, ..., sw 88.

To force the store earlier: what if the ori is *after* in a separate block? I.e., wrap the store in a do-while with the address:
```
do { a = (s32)&D_801907C4; unk58 = a; } while(0);
unkC4 = t | 2;
```
Then block2 = [a, sw], block3 = [ori, sw]. Within block2, order: lui, addiu, sw. 

t is defined in block1 and used in block3 → global. a is local to block2 → gets a free reg. Global t gets v0 → a v1. And the store is alone with the address → no sink.

Let me test: v_addr5.

But careful: does the do-while around the address+store introduce a nop like v_dw5 did? v_dw5 wrapped a single store and added a nop. Hmm, that nop was actually a load-delay nop (the load followed by ori). Not from the do-while. So fine.

Let me test v_addr5.
