# func_80181D98 (ov_SC01_080_jr_8017AE2C.c) — e19, P36 S104 T7

**Final: score 0, plain C, ZERO levers** (tree: 1 pin `$16` NEEDED, the `$17` one already removed; before → after =
1 → 0). `body.c` = `scratch/s2.c`.

(a) Residual (23, register swap): `p` (`&D_801270CC`, the switch pointer that case 2 advances by 15 and walks) took `$s0`
and the table walker `t` took `$s1`; the target has `t` = `$s0`, `p` = `$s1` (`addiu s1,s1,60` in the call's delay slot).

(b) Mechanism (`tools/alloc_table.py` on `scratch/dumps_free`, `dumps_s1`, `dumps_s2`): global allocation order,
`allocno_compare` (`global.c:594-607`) + `find_reg`'s lowest free register. Lever-free, ONE `p` carries every ref: 16
refs over 49 → 13061, above `t`'s 12/35 → 10285, so `p` is allocated first and takes `$s0`. Splitting the walk into its
own pointer `q = p + 15` gives `p` 5 refs (3333, allocated last) and `q` 11 refs/35 (9428 < `t`'s 10000): `t` is allocated
first → `$s0`, `q` (conflicts `t`) → `$s1`. `p` must ALSO land in `$s1`: it does only if `p` is still live when `t` is set
— i.e. `q = p + 15;` written AFTER `t = D_8018A278;` (`scratch/s2.c`, 0). With `q = p + 15;` before `t = …`
(`scratch/s1.c`, 12), `p` dies before `t` is born, does not conflict with it, and takes the free `$s0`. No pseudo-pseudo
preference exists for `(set q (plus p 15))` in global (`set_preference`, `global.c:1535-1546`, records hard-reg
preferences only; `expand_preferences` `:781` merges only existing hard-reg bits), so the shared `$s1` is conflict
geometry, not a tie. reorg still puts `addiu s1,s1,60` in the `jal func_80181CA4` delay slot.

(c) Moves: `s32 *q;` added; in case 2 `p += 15;` → `q = p + 15;` placed after `t = D_8018A278;`, and the loop's `*p`,
`(s32)p`, `p++` read `q`. (S103 c1/c8 "one name per value", with the placement fixing the conflict.)

(d) GENERATOR PROPOSAL: when a pointer is advanced in place (`p += K;`) before a loop that walks it and the residual is a
callee-saved swap with another loop pointer, split the advanced value into a new local `q = p + K` and try it at EACH
position up to the loop head (the split alone swaps the loop pair; the position decides whether the old pointer conflicts
with the rival and follows the new one's register).

(e) Did not work: history (186 compiles, R4/R7/R9 → 21); the split placed before `t = …` (12); `q = p + 15` before the
call `func_80181CA4()` (`scratch/s3.c`, 8 — `p` no longer crosses a call and goes to `$a1`).

(f) Method: the allocation table's conflict column settled it after the first split; the header's "natural priority
order hands `p` $s0" was right about the priority and silent on the split.

(g) Structs: no — `t` already is a struct pointer (`SpotDef_8018A278`); the decision is ref counts and a conflict, not a
memory channel.

Other copies: none (`SpotDef_` only in this TU; the one other `p += 15;` in ov_SC06_006 is lever-free and unrelated).
