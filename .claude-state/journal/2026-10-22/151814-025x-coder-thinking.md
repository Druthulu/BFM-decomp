---
ts: 2026-10-22T21:18:14Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FTBnBFRoKjvCghBblYDZ
---
Now let me write several candidates. Approach: arm3 stores via a pointer variable `s16 *p = (s16 *)((u8 *)a0 + 0x20);` and p[0..]. Hmm, that may change regs.

Better minimal: use cast stores `*(s16 *)((u8 *)a0 + 0x30) = k;` only for unk30, keeping the others as struct members. The MEM for that store: `(mem:HI (plus (reg) (const 0x30)))` without /s. If cross-jump compares with struct-store `mem/s:HI`, rtx_equiv_p → `exp_equiv_p`... In gcc 2.96, `rtx_equiv_p` handles `MEM` via `exp_equiv_p` which compares code, mode, and operands — the MEM's alias attributes are in the MEM's rtx (a `mem` has attributes like `struct` stored in the `alias` field, not as an operand). exp_equiv_p for MEM compares `MEM_ALIAS_SET`? Probably not. Hmm, might not differ.

Alternative difference: make one store use a different mode: e.g. store unk24 and unk2E as one `s32` store of 0? No — that would produce `sw` not two `sh`.

Hmm. What else does cross-jump require? It requires the blocks to have identical *number* of insns and the same successors. Also, `find_cross_jump` compares with `rtx_equiv_p(PATTERN(i1), PATTERN(i2), 0)` and it also requires the *insn codes* (`INSN_CODE`) to match? rtx_equiv_p compares patterns only; but the emitted asm is generated from the patterns, so identical patterns = identical asm. Right.

So: any RTL difference that yields the same asm. Options:
(a) register renaming: cross-jump handles renames, so no.
(b) A different but equivalent pattern that assembles to the same instruction — e.g. `(set (mem) (reg))` vs `(set (mem) (subreg:HI (reg:SI x) 0))`. In gcc 2.96 MIPS, storing an HImode pseudo → movhi. Storing a SI pseudo truncated to HI → `(set (mem:HI) (subreg:HI (reg:SI) 0))` — a different pattern! And the resulting asm might still be `sh v0,48(s0)` (possibly with the reg being the SI one, same register). That's exactly the "s16/u8 widths" move from the C0505 catalog, and the HImode-copy-escapes-cse trick used before!

So: in arm3, `unk30 = k;` with k declared `s32 k = -0x50;` (SImode). Then the store is `(set (mem/s:HI ...) (subreg:HI (reg:SI k) 0))` — different from arm1's `(set (mem/s:HI ...) (reg:HI ...))`. Wait, arm1's store of a constant would be `(set (mem/s:HI) (const_int -80))`? No — MIPS movhi: `(set (mem:HI) (const_int))` isn't a valid pattern; expand produces li into a reg. Actually with an s16 field store of constant -0x50, expand generates `(set (reg:HI 85) (const_int -80))` then `(set (mem/s:HI) (reg:HI 85))`. Hmm, in the jump dump we saw REG_EQUAL notes.

So arm1's final pattern: `movhi_internal2` with `(const_int 113)` as source — interesting: the dump shows `(const_int 113)) 163 {movhi_internal2}` — so the pattern is `(set (mem:HI) (const_int))` and movhi_internal2 handles it by loading into a scratch. Hmm, look at line 350 in jump2: `(const_int 113)) 163 {movhi_internal2}`. That means the store pattern takes the constant directly.

So if in arm3 the store source is `(subreg:HI (reg:SI k) 0)`, the pattern would differ → no cross-jump, and the asm should be `li v0,-80; sh v0,48(s0)` (movhi_internal for a reg source). But would it use $2 (v0)? The movhi_internal2 with a constant probably loads via a scratch register = $2. With a reg source, movhi_internal stores directly from the source reg. If k's SI pseudo gets allocated to v0, the asm is `li v0,-80` (from the constant load into k) then `sh v0,48(s0)`.

Hmm, but where is k's li born? `s32 k = -0x50;` at arm top → li v0,-80 born at the top; sched1 may move it. Target has it at 3 insns before the store. Risky but testable.

Let me also consider: keep `s16 k` but store through a SUBREG by declaring `s32 k`. Let's test both:

w2: barrier removed, arm3: `s32 k = -0x50; ... unk30 = k;`
w3: barrier removed, arm3: `s16 k = -0x50;` and `unk30 = (s16)k;`  (cast may not create a subreg)
w4: barrier removed, arm3 stores via `*(s16 *)((u8 *)a0 + 0x30) = k;`
w5: barrier removed, arm1's unk30 store via cast pointer (make arm1 differ instead)

Let me write these files and score with sc.sh.

Actually careful with `s32 k = -0x50;` — the value -0x50 as SI, stored into HI mem: it's a truncation; the compiler may still fold to const_int in HImode after combine. Let's just test.

Let me create the candidates with a small sed script or by Write. I'll write them with Write for clarity. To save effort, generate with a shell loop? Simpler: write a python script that reads win.c and produces variants. Let's do that — script under item dir.

Actually simplest: use sed to produce variants from win.c:
w2: replace "s16 k = -0x50;" with "s32 k = -0x50;"
w3: replace "s16 k = -0x50;" with "s16 k = -0x50;" and store `= k;` → `= (s16)k;`
w4: replace line 37 store with cast.

Let me do it with sed one-liners per file.
