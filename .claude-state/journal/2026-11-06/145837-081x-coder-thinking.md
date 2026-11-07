---
ts: 2026-11-06T21:58:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_i19Xo8ydGRCbzwUf4yTS
---
The full t09 diff (17 hunks). The residual:
- 8 sites `lh` vs `lw` (dst s16 narrowing).
- `lw a2,16(sp)` vs `lw v0,16(sp)` etc. (tmp register).
- `li a2,6` vs `li v0,6` (tmp).
- scheduling of `sh` at 535/536.

So t09's dst bank is correct (dst=v1) but the *loads* are lh (wrong width) and tmp is in a2 instead of v0.

If we can fix the lh→lw without losing the allocation, and tmp→v0, we'd be close.

Idea: declare dst as `s16` but make the load a full word by loading through a pointer cast that forces lw: e.g., `dst = *(s16 *)(arg0 + 0xD0)` is lh; `dst = (s16)(*(s32 *)(arg0 + 0xD0))` should emit lw then the s16 truncation is free if the register is used as s16... but the target uses lw with the full value. Since dst is only used in `dst + N` address computations, if dst is s16, the address computation would sign-extend (extra insn). But the diff shows mine's dst block instructions otherwise match target (dst=v1, addresses like 252(v1)). So the s16 dst's address computation uses the full register value? Let me check: `lh v1,208(s1)` loads a halfword sign-extended into v1 (32-bit). Then `dst+0xFC` = addiu. So the pointer value is the sign-extended halfword — semantically different from the word, but the instruction count matches.

To get `lw` with the same allocation: maybe declare dst as `s32` but add a cast that makes the *qty* size 1 word (same) — no.

The allocation effect of s16 is due to qty_size/mode (HImode). qty_size for HImode is 1 (words), same as SImode. Hmm, but the load width changed.

Maybe the real reason t09's bank matched is the extra `lh` (one fewer... no, same insn count).

Let me try: dst as `s16` with the load spelled `dst = *(s32 *)(arg0 + 0xD0);` gives lh. What if I spell `dst = (s16)*(s32 *)(arg0 + 0xD0);`? Same.

What if dst is `u16`? t11 = 25 too (dst u16). Let me check t11's diff: likely `lhu` vs `lw`.

What about dst as `long` (i=7)? t07 = 135. int (t05) = 135.

Hmm. So only the 16-bit/8-bit dst types improve. They change the load width.

Now, is there a way to get the dst bank right with dst s32? The bank difference is caused by qty mode/size. For HImode, qty_size=1; for SImode, 1. Hmm.

Wait — maybe the improvement isn't from the load width but from the *number of pseudos*: with dst s16, the load `lh` result is a HImode pseudo, and the address uses SUBREG. That changes the tie structure and priorities.

Let me look at t09's allocation: dst is v1 ($3) — exactly the target! And the target has dst in v1 with `lw`. So the target's dst was a SImode qty in $3. In t09, the HImode qty got $3.

So the qty that got $3 in t09 is the `lh` result (HImode). In target it's a `lw` result (SImode). Different mode but same allocation. If we could keep the SImode load but make the qty behave like HImode... no.

Alternative: use the s16 trick but add a *real* full-word load: load into a temp s32, then `dst = tmp_s16;`? That adds a move.

Hmm, what if `dst` is declared `s16` but the loads are written as `dst = *(s32 *)(arg0 + 0xD0);` and we add `(void)`? no.

Wait, actually, maybe the target's dst IS a 16-bit variable in the original source! The decomp author may have reconstructed it as s32, but the original could have been `s16 dst` used as an offset/pointer. If the original were s16, the compiler would emit `lh`, but the target has `lw`. So no.

Let me try a different tack: keep dst s32 and find what else changes the allocation. The s16 variant's *tmp* stayed s32 and tmp ended in a2 (target v0). The tmp pin removal also matters.

Let me test combinations:
- dst s16 + tmp u32/u16/etc. (to fix tmp→v0).
- dst s32 + tmp types (t10=tmp s16 122, t12=tmp u16 117, t14=tmp u8 137; t04=tmp u32 135, t06=tmp int 135, t08=tmp long 135).

Hmm, tmp types alone didn't help much (135/117/122). But combined with dst s16, maybe tmp gets v0.

Let me generate combos: dst in {s16,u16,u8} × tmp in {s32,u32,int,long,s16,u16,u8}. 21 combos. Score them.

Also try dst `u8` + tmp variants (t13 = dst u8 = 25).

Let me also reconsider: the `lh` vs `lw` residual might be fixable by making the *loads* full-word while dst stays 16-bit: e.g., `dst = *(s32 *)(arg0 + 0xD0);` already is full-word; the compiler narrows it because dst is 16-bit and the uses only need the low 16 bits? But the uses are addresses (32-bit). Hmm, `dst + 0xFC` as a 16-bit signed value: the compiler sign-extends dst to 32 bits for the address. If it can prove the high bits don't matter... it emitted `lh` (sign-extend load) — so it treats dst as a 16-bit signed pointer offset. The address `dst + 0xFC` uses the sign-extended value. So the compiler considers the high bits of the original word irrelevant. That's semantically wrong for a pointer, but matches instruction-wise except the load width.

Could we force `lw` by making dst's high bits matter, e.g., using `(u32)dst` in an address? `*(u16 *)((u32)dst + 6)` — the cast to u32 would zero-extend (for u16 dst) → `lhu`/`lw`? Hmm.

Try: dst as `u16` and addresses cast `(u32)dst + 6`: the compiler would zero-extend dst (andi 0xffff) → extra insn. No.

Try: dst as `s16` but address via `(s32)dst`: sign-extend (sll/sra) → extra.

So the s16 path adds an extra insn somewhere? But t09 has 710 ins (same as target) and score 25. The lh is a single insn replacing lw — same count.

Hmm, what if we declare dst as `s32` and *assign* it through an s16-typed expression to change the qty? e.g., `dst = (s16)(*(s32 *)(arg0 + 0xD0));` — this loads lw then truncates. If the truncation is free (the value is only used as... no, as a pointer it needs full 32 bits, so the compiler would sign-extend after truncation → extra).

Let me just test combos and see if any hits 0. Generate 21 combos.

Also, the tmp residual: in t09, tmp is in a2 (target v0). With tmp as u32/u16 maybe it lands in v0. Let me test.

Let me generate combos and score.
