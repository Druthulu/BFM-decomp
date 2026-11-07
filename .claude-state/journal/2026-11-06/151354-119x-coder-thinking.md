---
ts: 2026-11-06T22:13:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_cDsak5Dfn62OGMM8m1zv
---
All mask spellings give 3. The ORDER residual persists.

The residual is a sched1 placement of the constant materialization. Since the mask is a constant, combine/sched1 decide when to materialize it. The target has it later.

Let me look at the exact instruction positions. The scorer says:
- mine[150] = lui a1,0xff vs target[150] = nop
- mine[154] = ori a1,a1,0xffff vs target[154] = lui a1,0xff
- mine[158] = nop vs target[158] = ori a1,a1,0xffff

So the scorer's indices are a subset (maybe it strips nops or counts differently). The pattern: the `lui` is 4 slots earlier in mine.

In the target: nop, ..., lui (at 154), ..., ori (at 158). In mine: lui (150), ori (154), nop (158). So mine's materialization is exactly 2 instructions earlier (lui at 150 vs 154, ori at 154 vs 158).

This is a sched1 ordering: the constant is independent, so sched1 places it in the first available slot. The target placed it 2 slots later, meaning some dependency or priority difference.

How to make the constant later? If the constant were materialized *inside* the do-while block closer to its use, sched1 might still hoist it. The scheduler uses insn priority (critical path). The constant's use is far away, so low priority → should be placed late, not early. Yet mine places it early.

Maybe the difference is the EBB: the do-while creates an EBB boundary; the constant is in the second EBB. Hmm.

What if we make the mask a *variable* initialized earlier? `u32 m = 0xFFFFFF;` then use `m`. That creates a pseudo with a longer life; sched1 might schedule it differently. Let me try: declare `s32 m8 = 0xFFFFFF;` before the tail and use `((u32)pkt & m8)`. But that changes the RTL (a variable instead of a constant) — likely different code (lui/ori still, but the pseudo might be kept). Actually the constant still materializes the same way.

Alternatively, force the constant later by making it depend on the otp load: e.g., `(*otp & 0xFF000000) | ((u32)pkt & (0xFFFFFF | (oidx & 0)))` — an identity launder (not allowed).

Hmm, what about reordering the *statement* so the mask appears after the otp address computation? It already does.

Let me look at the target's schedule around there to see what precedes. Let me get the target listing around the same region (tgt_f.dis / t.txt from item 1 earlier — I have t.txt with the target). Let me print t.txt lines 140-175.
