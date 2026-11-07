---
ts: 2026-11-06T10:24:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Lt2qaYNiJltQ8wwfaSje
---
do-while around the 0x18 store adds an instruction (189). So do-while isn't free — it changes codegen (maybe the store in the delay slot is lost).

The do-while around the unk1C store (e15) gave 188 insns (no extra) and fixed the store but moved lh/li.

Let me revisit e15: can I combine e15 with a change that keeps lh/li in place? lh/li are `v.vz` and `a2=1`. They got hoisted before the address setup. In target they're after. If I make lh depend on the address setup... The address setup writes a0 (and s0). lh v0,52(sp) is independent.

What if the 0x18 store's source `v.vz << 9` is computed after the address setup because it uses a0? `CAST_WIDTH(s32, (u8 *)a0, 0x18)` uses a0 for the address. The store's address depends on a0. The address setup also uses... a0? `addiu a0,sp,48` SETS a0 (for the call). So the store `sw v0, 0x18(a0)` and `addiu a0,sp,48` both involve a0 → a WAR dependency (the store reads a0, then a0 is overwritten). That should keep the store before `addiu a0,sp,48`! But sched1 ignores WAR (anti) dependencies? Actually sched1 does consider anti-dependencies in some cases.

In target, the store is before the address setup. In mine, after. If there's a WAR dep, the scheduler shouldn't move the store after a0 is redefined... but it did (the store at 123 is after addiu a0,sp,48 at 121). Hmm, so the store's address must not use a0 at that point — maybe it uses a different register (a saved pointer). Indeed `sw v0,28(s2)` — s2 is the pointer, not a0. So no WAR.

OK, so the store uses s2 (the pointer saved in callee-saved s2). No dependency with the address setup.

I think this is genuinely a barrier-requiring wall. Let me record it.

Actually — one more idea: the store `unk1C = m` writes to the same struct as the later `--unk1C`. If I write the store and then read it back through a pointer that the compiler must keep ordered... e13 tried (dead read).

What about making the store part of the same expression as the next statement: `CAST_WIDTH(...0x18) = (v.vz << 9);` no.

I'll record WALL with best 2. Wall tag: `sched-store-sink` (new). Evidence: sched1/sched2 sink the dead unk1C store below the &v/&v2 address setup (target: store at 120, mine 123); only the memory-clobber barrier holds it; do-while(0) splits the EBB and fixes the store but hoists lh/li (score 4) and do-while around the 0x18 store costs an insn (189).

Let me verify the time: item started 03:13, now ~03:28 → 15 min. Hmm, still under 20. Let me spend 5 more minutes doing a few more tries (I have plenty of tries: nopin + c25 + c8 + d12 + e15 + f3 + g5 ≈ 66).

Actually the "≥20 min" is about genuine effort; I've done a thorough investigation with alloc tables and sched dumps. Let me do 5 more minutes of tries and then record at 03:33.

Let me try a couple more real-C ideas:
h1: split the 0x18 store's computation into a temp: `s32 vz = v.vz << 9;` before the store. This might change scheduling.
h2: `s32 vz = v.vz; ... CAST(...) = vz << 9;`
h3: move the `unk30 = 0x88` store to just before unk1C=m.
h4: reorder: move `q = r2 & 0x803C; unk28 = q;` before `CAST_WIDTH(...0x2C) = ...`.
h5: use a local `Blk20 *p = &mtx` etc.

Let me try h1-h4.
