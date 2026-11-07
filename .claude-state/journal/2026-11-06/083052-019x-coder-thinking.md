---
ts: 2026-11-06T15:30:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lbkECM8NMIS7lrJPt0aS
---
So without the launder, the mp pointer takes s0 (a callee-saved register) and is copied to a0. The target uses a0 directly: `lui a0; addiu a0` and then `swl/swr` via a0 (interesting — the swl/swr is the `func_800233CC` call? no wait, the swl/swr are D_801D0FC0[0] = D_801CF0E8[0] — no. Hmm at insn 36-37 swl/swr v0,3(s0) — that's the struct copy at line 3116-3117? D_801D0FC0[0] = D_801CF0E8[0] is a Blk4 copy (4 bytes, align 1 -> swl/swr).

Wait, but target has swl/swr via a0. Hmm, so in target the base of the D_801D0FC0 store is a0. But also the call arg uses a0 with lui/addiu... Let me think: target:
- insn 26-28 in mine: lui s0; addiu s0; move a0,s0 (that's the call arg: address of D_801D0FC0 loaded into s0 then copied to a0)
- target: lui a0; addiu a0 (no move) — so the call arg is directly a0.
- Then insn 33 target: lui a0; addiu a0 — second address (for the store D_801D0FC0[0] = ...?). Wait mine at 33 has nothing and later uses s0. Hmm.

Actually let's map: mine[26:29] = lui s0 / addiu s0 / move a0,s0 -> call func_800233CC(mp,0x80). Target [26:28] = lui a0 / addiu a0 -> call. Then target [32:34] insert lui a0 / addiu a0 -> this is the reload of D_801D0FC0 for the store D_801D0FC0[0]=D_801CF0E8[0]. And mine[36:38] swl/swr v0,3(s0) uses s0.

So the difference: target uses a0 twice (rematerializes the address), mine keeps it in s0 across the call. Wait, but a0 is caller-saved and clobbered by the call; target rematerializes lui/addiu a0 after the call. Mine loads into s0 before the call and copies to a0, then reuses s0 after.

So the crack: make gcc rematerialize the address after the call rather than keeping it in s0. The launder forced mp into a register (s0) — that's exactly what creates the s0 keeping. Hmm wait, the launder forces mp into a reg, so it stays across call... and with launder, orig scores 0. So orig (with launder) matches target: s0? But target shows a0 usage. Let me re-read: with launder, score 0 means mine == target. But the diff above is for c1 (without launder). In c1, mine uses s0. In orig-with-launder, presumably it matches target which uses... a0? That's contradictory.

Wait no: maybe with the launder, mp is forced into a register chosen as a0? Let me check: `__asm__("" : "=r"(mp) : "0"(mp))` — output and input tied, so mp must be in a register, and gcc may pick a0? Actually an asm with "=r" output creates a register copy that could be in any register. If the next use is the call arg in a0, gcc may keep mp in a0. Hmm.

Actually hold on. The diff numbering differs. Let me instead dump the target disassembly and mine to compare properly. There's a tool for disassembly maybe. Let me look at what tools exist: .run/P40/T11/bin/.
