---
ts: 2026-11-06T06:40:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vRiylHJFTrsPu5Uy9F3r
---
All the early diffs are just address offsets (+4). The actual insn difference is at mine[478:480] (`addiu s0,sp,24; move a1,s0` vs `addiu a1,sp,24`) — that's the extra insn. Hmm, but that's a 2-for-1 replace, which accounts for the +1.

Wait, but the offsets shift at the very beginning (mine[8] vs target[8] both at the same index, just different addresses). The address difference comes from the *branch target* b04 vs b00 — the epilogue is 4 bytes later in mine. That means the extra insn is somewhere before the epilogue but... the first diff is at index 8 with a different target address, meaning the total function is 1 insn longer (711 vs 710) — the target address b00/b04 is the epilogue.

So the real diff is the `addiu s0,sp,24; move a1,s0` vs `addiu a1,sp,24` — one extra insn there, and a corresponding `move a0,s0` vs `addiu a0,sp,24` (a replace, same count).

So mine: `addiu s0,sp,24; move a1,s0` = 2 insns; target: `addiu a1,sp,24` = 1. And mine `move a0,s0` vs target `addiu a0,sp,24`.

This is the m18 = sp18 area (RotTransSV(mm, m18, sp28)). Hmm, s0 = sp+24 = sp18? Let me look at the target asm around there.

Actually, this is about `m18 = sp18;` and `m18b = sp18;` — with the launders removed, `m18` is hoisted into s0 and then copied to a1/a0. In the target, each use is `addiu a1,sp,24` (rematerialized).

Hmm, so this is the same launder issue but for m18. The dead-reset I added only covered `mp`, not `m18`.

Let me add dead resets for `m18` too: after `RotTransSV(mm, m18, sp28);` add `m18 = 0;`. And for `mm`.

Hmm, but the target's RotTransSV call: `RotTransSV(mm, m18, sp28)` where m18 = sp18. Target has `addiu a1,sp,24` — so m18 is materialized per call.

Let me look at the target asm around 0x8e0-0x910 to see.

Actually, let me just try adding `m18 = 0;` after the RotTransSV call and `mm = 0;`.

Wait — careful: m18 is used twice: `m18 = sp18; RotTransSV(mm, m18, sp28);` and `m18b = sp18; func_8018FB5C(m18b, sp20, col);`. Hmm.

The target diff shows 2 sites: `addiu a1,sp,24` (for RotTransSV's second arg) and `addiu a0,sp,24` (for func_8018FB5C's first arg). In mine, s0 holds sp18 and is copied.

So the address sp18 is hoisted into s0 (callee-saved) and copied. Target rematerializes.

To break: a dead reset of m18 after its use? Or make m18b a fresh variable... it already is.

Hmm, but the *address* sp18 is the same in both `m18 = sp18` and `m18b = sp18`. cse merges them.

Let me try:
- d1: add `m18 = 0;` after RotTransSV and `m18b = 0;`? Hmm, m18b is used in the next call.
- d2: use `sp18` directly in both calls (no m18/m18b variables).

Let me try d2 first: `RotTransSV(mm, sp18, sp28);` and `func_8018FB5C(sp18, sp20, col);`.

Hmm, sp18 is `u16 sp18[4]` so passing it as a pointer is natural.

Let me test both.

Also, the `mm` variable: `mm = D_801CC7F4; RotTransSV(mm, m18, sp28);` — with a dead reset for mm after.

Let me generate d1 (direct sp18) and d2 (m18 dead reset) from c2.
