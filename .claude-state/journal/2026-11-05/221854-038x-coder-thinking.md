---
ts: 2026-11-06T05:18:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_g65v94mkXR4mZ4WkD1IV
---
The orig RTL:
- insn 20: raw(v1) = zero_extend(load QI 78)
- insn 23: t? no — insn 23: reg80 = v1 - 16
- insn 25: t(v0) = reg80
- insn 42: raw(v1) = t(v0)      ← move v1,v0
- insn 44: raw(v1) = asm(raw)  ← the launder
- insn 47: t(v0) = raw(v1)     ← move v0,v1

So the target structure is: v1 = v0; v1 = asm(v1); v0 = v1.

Lever-free: insn 42 and 47 are copies between two pseudos. With pins they're hard regs. The launder re-sets raw.

Key: after insn 42 (raw = t), cse equates raw and t → insn 47 becomes t = t → deleted, and raw dies.

To prevent, we need something between insn 42 and 47 that re-sets raw to a value cse can't equate. The launder does that via asm. Lever-free alternatives:
(a) A real 2nd set of raw with a *different* value that happens to equal t.
(b) A use of raw that forces it alive.

Wait — here's an idea: what if we make raw alive *after* `t = raw`, e.g., the stores use raw? No — then no t = raw.

What if the order is: `t = raw;` FIRST (t = raw copy), then `raw = t`? No.

Hmm. Let's think about (a): a real 2nd set of raw to a value cse can't prove equals t, but at runtime equals t. Classic: dead-reset C0414 — but that changes the value.

What about `raw = (s16)t;` — a sign-extend set. cse: raw = (s16)t, and t is known in [0,239], so (s16)t == t → cse knows raw ≡ t? cse doesn't do range analysis; it works on REG_EQUAL notes. combine would attach REG_EQUAL to the sign_extend. Hmm, but in RTL, `(s16)t` for a value in range: combine might simplify to `t` (a copy) since it knows from nonzero_bits. If it simplifies to a copy, cse equates → dead.

What about a *zero-extend* from a QI subreg: `raw = (u8)t;` — the RTL is zero_extend(subreg(t)). combine knows t ∈ [0,239] → simplifies to t. Dead.

What if t's range is NOT known? If we could hide the guard from the optimizer... e.g., the guard `if (t < 0)` — the range [0,239] comes from t = raw - 16 with raw = lbu ∈ [0,255]. Even without the guard, t ∈ [-16,239]. So (u8)t != t possibly (if t negative) but guarded, and (s16)t == t always. Hmm, so a sign-extend is always exact for t ∈ [-16,239]. combine knows.

So we need raw to be set to a value that isn't provably t. What if we set raw to the *load* value again? e.g. `raw = *(u8*)((u8*)s1+0x24);` again — a second load! That would re-load the byte (which has been changed? no, not yet). That would emit another lbu — extra instruction. No.

Hmm.

What about making `t` a variable whose value is not known: e.g., store t into a memory location and read it back? Extra insns.

Alternative: prevent cse from merging by making raw a different MODE: e.g., declare raw as `s16` and t as `s32`? Then:
- raw = load: `s16 raw = *(u8*)...` → raw QI? No, s16 raw = lbu → raw is HImode: set (reg HI raw) (subreg (zero_extend...)). Hmm.
- t = raw - 0x10: sign_extend(HI) - 16 → addiu.
- raw = t: HImode set (subreg t) — move.
- t = raw: sign_extend → move.

Since raw is HImode and t SI, cse can't equate them (different modes → different reg_eqv classes? Actually cse's reg_eqv is indexed by regno only, not mode, but the SUBREG handling might prevent). In the func_8017E204 case, the HImode temp broke equivalence. Let's test raw as s16/u16.

Wait, we tried n5/n6 with tmp s16/u16 between raw and t, but raw stayed SI. Let me try declaring `raw` itself as s16 or u16 (not a separate tmp). Then:
- `s16 raw; raw = *(u8*)(...);` — assignment from u8 to s16: zero-extend then no sign-extend needed? raw is s16, value 0..255 fits.
- `t = raw - 0x10;` — sign-extend raw (HI) to SI.
- `raw = t;` — truncate to HI (subreg).
- `t = raw;` — sign-extend.

The sign-extend from HI in a register: `sll/sra` pair? For s16 in a register, sign-extend requires sll t,raw,16; sra t,t,16 — 2 insns! That would break the match. Unless gcc keeps the value known sign-extended.

Hmm, but func_8017E204 used s16 and the sign-extend folded into "the same instruction stream" — because the copy was `move v1,v0` with no extension (the register value was already sign-extended? no...). Actually in that case v0's value was loaded as SI and the s16 temp was a sign-extension of it, but the target's move v1,v0 suggests no extension instruction — meaning gcc knew the value was already sign-extended? Hmm, the note says "the sign-extend of the s16 temp is folded back into the same instruction stream" — meaning combine folded it.

OK let me just test raw as u16 and s16 variants.

n9: s16 raw
n10: u16 raw
n11: u8 raw with explicit `t = (u8)raw` etc. (already n2, no)

Also consider the alternative: maybe use `u16 t` for the store value? Hmm.

Let me test n9/n10.
