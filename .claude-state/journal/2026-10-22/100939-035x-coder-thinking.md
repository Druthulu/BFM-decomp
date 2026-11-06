---
ts: 2026-10-22T16:09:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CvulsYjBZ6nICCjIkQc0
---
`extern u8 D_80120194[];` so `(s32)D_80120194` is the *address* (array decays to pointer, cast to s32). So:
- it = &D_80120194
- p = it + 0x658C  (= &D_80120194 + 0x658C = 0x80120720)
- test: it = &D_801202A0; if (it == p) goto zero;   [p = 0x80120720, &D_801202A0 — not equal? D_801202A0 != D_80120720. Hmm, then why compare?]

Wait: D_80120194 + 0x658C = 0x80120720. And D_801202A0. Not equal. Hmm, but the code checks `if (it == p) goto zero`. Maybe D_801202A0 is the same as p? 0x80120194 + 0x658C = 0x80120720 ≠ 0x801202A0. So the comparison is never true? Weird, but it's decompiled code; maybe the constants differ in the target. Whatever — the score says 19/19 ins with only register swaps, so the shape is right.

Now the residual: mine puts &D_80120194 in a0 and &D_801202A0 in v1; target the opposite. Also mine computes `addiu a0,a0,25996` at insn 1 (folded p into a0?) — let me get the full listing.

Let me dump both. I'll create a fresh candidate object with --keep and copy it immediately, then use dump.py. But the --keep scratch may be stale again. Instead, I can use the fact that gen_base is a body; I can build a TU myself like I did for item 1 and dump the .s (not RTL) — cc1_dumps_tu.sh gives the .s, which is enough to see the instruction order. Let me do that: TU = the includer ov_MAIN_012.c, with the header replaced by my body (in $d/shared/ov/), TU copy in $d/tu_dump/ov.c. Then read the .s for func_8012C2D0. That's clean and cheap.

Actually simpler: use `--try --keep` and immediately copy cand.o, then dump.py with it. But the stale issue... The stale was because p6 was reused by another process? Let me instead do the TU route since it worked.

Let me set it up for item 2 with the best lever-free candidate (gen_base). Then look at the .s.

Actually, do I even need it? The diff tells: mine[0..1] lui a0,%hi(D_80120194+0x658C); addiu a0,a0,%lo(0x658C)... Hmm, `addiu a0,a0,25996` with 25996=0x658C — and %hi of D_80120194 would be 0x8012 (lui a0,0x8012), then addiu a0,a0,0x658C gives 0x8012 + 0x658C? No: lui a0,0x8012 sets a0 = 0x80120000; addiu a0,a0,0x658C = 0x8012658C. That's not right either. The dumps mask relocations as 0 in the disassembly? In the diff, `addiu a0,a0,25996` — maybe the reloc %lo(D_80120194) is shown as the addend 25996? Hmm, weird.

Actually, objdump of a relocatable object shows `addiu a0,a0,0` with a reloc, not 25996. Unless the compiler emitted `lui a0,%hi(D_80120194)` then `addiu a0,a0,%lo(D_80120194)` where the disassembler resolved %lo? The diff shows target[1] `addiu v1,v1,0` — so target's is 0, mine's is 25996. So mine[1] = addiu a0,a0,25996 → mine's *addend* is 0x658C, i.e. mine computed `&D_80120194 + 0x658C` = p as a constant into a0 at insns 0-1! And then mine[2] == target[2] which would be `lw a0,0(a0)`? No...

Let me just dump the .s. Do it.
