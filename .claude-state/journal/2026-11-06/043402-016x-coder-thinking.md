---
ts: 2026-11-06T11:34:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7ULOgoomPVM9LMWJ1qeV
---
Let me see full listings of both. Let me get the target and mine disassembly. --explain might show. Let me look at a full side-by-side. I'll write a small script? Or use --keep to get the object. Simpler: use dt.sh with a body that has no diff? Hmm.

Let me understand the target sequence from the diff context. Target insns (from target column):
- 17: andi a1,v0,0xfff
- 18,19: ?
- 20: beq v1,v0,...  (probably delay slot 21: move s1,a1)
- ...
- 44/45: j
- 46: lhu v1,174(s0)
- 47: li v0,128
- 48: andi a0,v1,0xff
- 49: bne a0,v0,...
- 50: srl v0,v1,0x8   (delay slot)
- 51: beq v0,a0,...
- 52: move v0,zero    (delay slot)
- 53: lhu a1,174(s0)
- 54: li v0,128
- 55: andi a0,a1,0xff
- 56,57: ...
- 58: subu a1,v0,a1
- 59: addu v1,s1,v0
- 60: (delay slot nop?)
- 61: andi v1,v1,0xfff
- 62: sh v1,18(s2)

Hmm the target does two separate lhu of 174(s0) — that's the barrier effect (reload after the memory clobber). Lever-free C would cse the second load... but the barrier was before sVar4 which is before the store. Actually the barrier was before `sVar4 = ratan2((*(u16*)(p+0xAE) & 0xFF) - 0x80, ...)`. Wait, no: the barrier is inside the if before the ratan2 call. The ratan2 call itself may invalidate memory (it's a function call) — so the reload could happen anyway. But cse might have the value in a pseudo already... Actually the first read of p+0xAE happens in `bb = *(u16*)(p+0xAE)` before the if. Then cse would forward `*(u16*)(p+0xAE)` into the two later reads (no intervening store, though there is a call to ratan2 — but the call args are computed before the call; the reads are call arguments, so they happen before the call).

So the target re-loads at 53 (lhu a1,174(s0)) and uses it in the call arg, while mine reuses. The barrier memory clobber prevents that cse. Removing the barrier means cse forwards the load → fewer loads → different code.

Hmm. So lever-free needs a way to prevent cse from forwarding the first load's value. Options: the first load `bb` is `u32 bb = *(u16*)(p+0xAE);` — in target, `andi a0,v1,0xff` at 48 (lo = bb & 0xFF). Then second lhu at 53.

Wait target: 46 lhu v1,174(s0); 47 li v0,128; 48 andi a0,v1,0xff; 49 bne a0,v0 (compare lo != 0x80); 50 srl v0,v1,0x8; 51 beq v0,a0 -> 331c (return 0 path); 52 move v0,zero; 53 lhu a1,174(s0); 54 li v0,128; 55 andi a0,a1,0xff; 56 subu a1,v0,a1? Hmm wait.

Actually 54 li v0,128 then maybe 55 andi a0,a1,0xff, 56 srl v1? no. Let me get the full target disassembly. Use --explain? Or tools. Let me just find the target object. Maybe tools/delever_search.py --try with --keep gives candidate object; but target is in build/. Let me find the target disassembly: likely objdump of build/src/ov_SC01_077/...o. Let me check what dt.sh prints with full tail — it truncates. Let me look at delever_search.py's --explain.
