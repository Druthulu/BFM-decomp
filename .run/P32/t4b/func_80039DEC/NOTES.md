# func_80039DEC (main/800_c, 74 ins, K&R def with narrow s16 params) — S83 hand analysis (residual 2: a2's raw-preserve copy
in $t1 vs the target's $a3; a1's copy is $t0 in both)
Target: `addu $a3,$a2,$zero` (raw a2 kept), `sll/sra $a2` (sign-extend in place), … `addu $t0,$a1,$zero` (raw a1 in a delay
slot), later `sb $a3` ×2 (the raw a2 byte stored) and `sll $v0,$t0,16` (a1 promoted per branch). The target uses $a3 for NOTHING
else; the draft never uses $a3 at all — so in the draft global-alloc skipped $a3 for a2_raw (took $t1) and for a1_raw (took $t0)
alike: global.c find_reg's FIRST pass avoids hard regs with local_reg_n_refs>0 (regs any block-local pseudo occupies); in the
target a2_raw got $a3 → no local pseudo sat in $a3 there. Find which block-local temp the draft puts in $a3 (compile the draft
with `-dl -dg` via tools/cc1_dumps.sh, read "Register dispositions" for `in 7`), and remove/reshape it (the pinned $2/$3/$4
temps `pc/bc/pd/bd/kind` and `cnt`/`tmp` are the candidates — the pins themselves may be what pushes a local into $a3).
TU: the prototype at 800_c.c is now `extern void func_80039DEC();` (committed e39229051) — rtu_match in the real TU works.
