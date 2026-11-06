---
ts: 2026-10-22T21:17:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dIKdBExEXpHNsy06ezrS
---
So in jump2 (after the merge), only one copy of arm1's body (113 at 350). Arm3's block was merged with arm1's. So the merge happened before jump2, i.e., in jump1 (the .jump dump is *before* cross-jump? Actually the .jump dump shows both arms...). Hmm — the .jump dump shows both arms, and jump2 shows one. So the merge is in the jump_optimize pass (cross-jump) that runs... Actually there might be two jump passes: `.jump` (jump_optimize after cse) and `.jump2` (post-reload jump_optimize). The merge appears between .jump and .jump2 — but sched1, lreg, greg, reload all run in between. Cross-jump post-reload is in jump2 itself.

Actually in gcc 2.96, `jump_optimize` is called in `rest_of_compilation` both after cse (`jump_optimize (insns, 0, 0, 0)`) and at the end (`jump_optimize (insns, 0, 0, 1)`) after reload — the latter does cross-jumping. The dump `.jump` is written after the first, `.jump2` after the second. Since the merge shows in .jump2, cross-jump (in the post-reload pass) did it.

So cross-jump compares the post-reload insns. Two blocks with identical hard-reg insns get merged. So the *final* instruction streams are identical → merge. That means NO plain-C difference that produces identical instructions can prevent it, unless the RTL differs in something cross-jump checks that doesn't change the assembly.

What does find_cross_jump compare? In jump.c:
```
/* Compare the instructions of the two blocks... */
for (i = ...; i1, i2; ...) {
   if (! rtx_equiv_p (PATTERN (i1), PATTERN (i2), 0)) break;
   ...
}
```
It uses `rtx_equiv_p` which handles register renaming (different regs allowed if consistently renamed) and uses `exp_equiv_p`-like semantics with the `labels`/`renaming` table. It also requires `onlyjump_p` / same insn codes.

Important: cross-jump in jump.c `find_cross_jump` requires the insns to be `rtx_equiv_p` — including REG notes? It compares `PATTERN` only I think. Also it requires the same `INSN_CODE`? It compares `recog` results implicitly.

One thing that breaks equivalence: a REG_EQUAL/REG_EQUIV note? No, notes aren't compared.

Another thing: MEM aliasing attributes! `(mem/s:HI ...)` vs `(mem:HI ...)` — the `/s` flag differs (struct vs not). If arm1's store is `mem/s` and arm3's is plain `mem` (because written via a cast pointer `*(s16*)((u8*)a0+0x30)` instead of a struct member), then `rtx_equiv_p` would... hmm, exp_equiv_p ignores the MEM flags? Not sure.

But wait: the resulting assembly would still be identical (sh v0,48(s0)). So if I can make the two blocks differ in MEM flags, cross-jump won't merge, and the asm is the same! That's a promising, lever-free, "real C" move: write arm3's stores through a cast pointer (or the reverse).

Actually careful: the current source uses `((Unkstruct_8017CF48 *)a0)->unk30 = k;` in all arms. If I write arm3's stores via `*(s16 *)((u8 *)a0 + 0x30) = k;`, the MEM would be `mem:HI` (no /s) — different from `mem/s:HI`. Let's test if that alone (plus barrier removal) scores 0.

But also the delay-slot branch shape difference: in mine at 1444 `bnez v0,14a0` vs target `beqz v0,146c`. That's a consequence of the merge; if the merge is defeated, the branch shapes should match.

Let me test. Candidates:
w2: barrier removed; arm3 stores via cast pointers.
w3: barrier removed; arm3 stores via cast pointer only for unk30.
w4: barrier removed; arm1 stores via cast pointer.

Note: the target's arm3 must be at 14a0..14dc and arm1 at 144c. With arm1 as the fallthrough of the first test and arm3 later.

Let's write them.

Actually another subtlety: for the arm3 body, the order of stores matters. Keep the same.

Let me create w2: copy orig.c, remove barrier line, and rewrite arm3's 5 stores as `*(s16 *)((u8 *)a0 + 0xNN) = ...;`. Note the field types: unk20/unk22/unk24/unk2E/unk30 — need to check the struct to know widths. Let me check Unkstruct_8017CF48.
