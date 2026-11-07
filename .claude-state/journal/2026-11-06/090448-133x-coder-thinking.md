---
ts: 2026-11-06T16:04:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IdJWTx8Bt0DaItCMBj3u
---
c2 (`u = t`) → 40 ins (2 fewer): combine merged `u = t; t = u - 1` into `t = t - 1` (one addiu), eliminating u. So u's copy is needed.

So we need `u = t` to survive as a copy. The target has `move v1,v0` then `addiu v0,v1,-1`. For the copy to survive, combine must not merge it. The original used `u = t + zr` with zr = $0 (a hard register addend) — the moves catalog says: "WALL cse-copy-merge — target `move v1,v0` is `plus v,$0`: a hard-reg addend combine cannot fold, so cse keeps the copy; a C-level zero is a constant -> combine folds -> cse propagates (best 2)". That's exactly our situation! From moves line 134: func_8018302C WALL cse-copy-merge — "target `move v1,v0` is `plus v,$0`: a hard-reg addend combine cannot fold...".

But there's a MATCH for a similar case: func_80182ED4 "MATCH: copy hoisted above the branch via s16 temp (tmp=(s16)t; u=tmp) — HImode copy escapes cse equivalence class, so or v1,v0 survives in the bnez delay slot" (moves line 217). And func_8003DF8C MATCH: "u16 i; u16 j: the HImode copies of arg0/arg1 escape cse, so the target's opaque $a3/$t0 parameter copies survive (score 0)".

So the technique: use an s16/u16 temp for the copy: `u = (s16)t;` or declare u as s16/u16. The HImode copy escapes cse/combine's equivalence class, keeping the move.

Let me test:
c3: `u = (s16)t;` (u is s32).
c4: declare u as `s16 u;` and `u = t;`.
c5: declare u as `u16 u;`.

The target's `move v1,v0` — a plain 32-bit move. If u is s16, the assignment `u = t` would be a HImode store (sh to stack?) unless u stays in a register. Hmm. The moves say "u16 i; u16 j: the HImode copies of arg0/arg1 escape cse, so the target's opaque $a3/$t0 parameter copies survive (score 0)" — so HImode locals can live in registers and produce moves.

But our u is used in `t = u - 1` (arithmetic). If u is s16, `u - 1` would be HImode arithmetic then converted — might add insns. Let me test c3/c4/c5.

Actually, the cleanest: keep u s32 but write `u = (s16)t;` — a cast to s16 then assigned to s32: the RTL would be a sign-extend (HImode copy), which escapes cse. The target has `move v1,v0` (no sign-extend). Hmm, but if the value is already sign-extended... combine might fold `(s16)t` to a move if t is known non-negative? t's value at that point: t = unk84 (nonzero, could be anything). So `(s16)t` would need a sll/sra pair — extra insns. Unless u is declared s16.

Let me test c4 (u s16) and c5 (u u16) and c3 (cast).
