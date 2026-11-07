---
ts: 2026-11-06T12:24:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bYNAbxbQPBU9YWms5ICU
---
Now edit c1: remove zr pin and use s16 casts for the copies; remove asms.

Note `n` values 1..3; `(s16)n` — gcc might know n's range? Probably not, but combine can reduce sign_extend of a reg when it knows the value fits... Actually combine reduces `(sign_extend:SI (subreg:HI (reg:SI n)))` to `addu` only if n's range fits in 16 bits — gcc 2.7.2 tracks ranges poorly. In func_8017E1AC, flag was u8 so it worked. Here n s32. Try `(s16)n` anyway; if it emits sll/sra, try making n a s16 variable: `s16 n;` then `cnt = n;` → sign_extend known-truncated? A s16 variable in a register is stored as sign-extended 32-bit value, so `cnt = n` is just a copy (no extension insn) — and since n is a distinct variable, copy-prop may coalesce. Hmm.

Actually wait: the copies are needed to prevent qty merge. The lever-free alternative from the notes: "P40 T10, lever-free: `flag2 = (s16)flag;`". Let's try.

Also note [3] uses the zr copy for cnt (v0 copy) and lim (s2 copy). Let me try c1 with (s16) casts.

For the [5] +1 ref on lim: maybe make lim used twice in loop condition, e.g. `while ((s32)i < lim)` → keep, but add something real: `i < lim` where lim is read twice? Could do `lim = cnt;` and condition `(s32)i < lim` — one ref. An extra read: `while (((s32)i < lim) && (lim != 0))`? That's fake-ish but real C (the second is redundant but a real condition; would add a branch though — no, gcc would delete it? not necessarily). Hmm, priority calc counts refs in the RTL; a dead-but-present comparison adds insns too, which lowers density.

Alternative: declare lim as s16 → but target uses $s2 as loop bound.

Let me first test c1 and see the diff. Do the edits.
