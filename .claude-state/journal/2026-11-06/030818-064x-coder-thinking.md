---
ts: 2026-11-06T10:08:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Uvhk3zi7WlTWZFvfGSvd
---
Started 02:54, now 03:07 → 13 min on item 1. I have ~17 more min before the 30-min wall. I need ≥30 scored tries total for this item if WALL.

Let me try a batch of variants to reach 30 tries and maybe crack it. Let me write a generator script that produces many variants from nopin.c by applying combinations of moves, then sc.sh them all.

Variants to generate:
1. Decl order: tb before t.
2. Types: u16 t, u16 tb.
3. Different struct access spellings.
4. Statement reorder (put unk50 before unk54).
5. Direct store variants.
6. Call arg spellings (arg0, s0, casts).
7. Reuse t for all three.
8. Separate u at various scopes.
9. Init at decl.
10. Compound assignments.

But honestly, to crack this I need the right insight. Let me think harder about the tb-global idea combined with scheduling.

Actually — wait. What if I make tb's store use the loaded value directly AND give tb a second def via the unk50 chain? Specifically, target: unk54 in v1, unk50 in v0. What if the SAME variable tb is used for unk54 and then... no, reg is fixed.

Alternative insight: maybe I can make t get v0 by making tb NOT local via making the block span differently. The local/global decision: reg_basic_block[i] >= 0 && reg_n_deaths[i]==1. If tb is used in two blocks (reg_basic_block=-1), it's global.

Can I make tb used in a second block without changing code? What if I reference tb in the `else` branch that's not taken? That adds code.

Hmm, what about the initial `if (cnt < 0x20)`. tb is used only inside. 

What if I declare tb at function scope and assign it inside the block, then... it's still one block.

OK, different idea: make local-alloc assign tb to v1 by giving a *higher-priority* local qty v0 in tb's range. What if the `li a0,2274` (call arg) were a pseudo? It's a constant → hard a0.

What if I introduce a temp for the call arg: `s32 arg = 0x8E2; func_80147324(arg);` — that adds a qty that takes v0 during 56-60, overlapping tb → tb → v1! But it adds an instruction? `li a0,2274` becomes `li <reg>,2274; move a0,<reg>` → extra insn. Bad.

Hmm.

What if the store `sw zero,48(s0)` is made via a variable `s0->unk30 = 0;` already. 

Let me look at the actual local qty list for block 2 and their assignments to find a qty that could take v0 before tb. From the lreg: "Basic block 2: first insn 30, last 95" and "Registers live at start: 29 30 72 77". Local qtys assigned in block 2: r75 (v0), r79 (v0), r80 (v0), r87 (v0), r88 (v0), r89 (v0), r92-97 (v0), r100 (v0), r101 (v0). Most got v0 because their live ranges don't overlap tb's.

tb (r75) is in v0 and lives 53-58. If I could make one of those v0 qtys live across tb's birth, tb would go v1.

The qty r87/r88 (blk 2, live 3, pri 6666) — born maybe at 60+. Hmm.

This is very deep. Let me consider the alternative: maybe there's a much simpler formulation of this block that the original author over-complicated. The target code:
```
lw v0,76(s0)     ; t = unk4C
lw v1,84(s0)     ; tb = unk54
sh v0,6(s0)      ; unk6 = t
lw v0,80(s0)     ; t = unk50
sh v1,14(s0)     ; unkE = tb
addiu v0,v0,-8   ; 
sh v0,10(s0)     ; unkA = t-8
```
Wait, let me re-read the target order from the dump:
52 lw v0,76; 53 lw v1,84; 54 sh v0,6; 55 lw v0,80; 56 li a0,2274; 57 sw zero,48; 58 sh v1,14; 59 addiu v0,v0,-8; 60 jal; 61 sh v0,10.

So: load t(76), load tb(84), store t→6, load t(80), li a0, sw 0, store tb→14, addiu, jal, sh t-8→10.

This matches source order roughly:
t=unk4C; s0->unk6=t; tb=unk54; s0->unkE=tb; s0->unk30=0; t=unk50; s0->unkA=t-8; func(0x8E2);

Hmm target: store unkE at 58 (after sw 48 at 57), addiu at 59. Source order: unkE store before unk30=0. But target has unk30=0 (57) before unkE store (58). So sched1 reordered.

OK. Given the complexity, and that this is the smallest item, let me try a broad batch of ~25 variants to reach the try count and possibly get lucky. I'll write a generator.

Let me create a script gen_cd314.py that writes variants to files vN.c, then sc.sh them.

Actually simpler: I'll write the variants by hand in a script with replacements. Let me define the base = nopin.c and apply transformations.

Transformations:
A. swap decl order t/tb.
B. u16 for t.
C. u16 for tb.
D. remove t reuse: separate u (done, v4).
E. direct stores (v3).
F. reorder statements (unk50 before unk54).
G. call arg arg0.
H. call arg with cast (s32)(s0).
I. tb assigned from unk54 twice.
J. use a second temp for tb.
K. init t at decl.

Let me write a generator producing combinations and score all. But each variant needs to compile. Let me do it.

Actually, wait. Let me reconsider the "move a0,s0" issue first, because it's 1 diff and maybe easy: the copy pseudo reg73 coalesces to a0. If I make the call take `s0` in a way that creates a conflict with a0... 

What if the last statement is `func_80146C3C((u8 *)(s0 ^ 0));`? Fold.

What if I pass `(u8 *)s0` but ALSO keep s0 alive afterward? No.

The copy pseudo reg73: where does it come from? GCC creates a copy when the argument is a variable whose type differs or when it needs a fresh reg. Since func_80146C3C takes u8*, passing (u8*)s0 (s32) requires a conversion — but pointer/int are same size, no conversion. Hmm. reg73 might be the "s0" variable itself! Wait, alloc_table said r72 is the pointer crossing calls (s0?), r73 prefers a0. Let me check: in the lreg RTL, the call arg is `reg/v:SI 73`. And insn 131 `a0 = reg73`. So reg73 is the variable used as the argument. Is reg73 the `s0` variable? The prologue `s0 = arg0` — which pseudo? Let me look at the lreg RTL start.

If reg73 IS the s0 variable, then insn 131 `a0 = reg73` is the arg setup, and global-alloc gave reg73 → a0 (preference), making it a self-move. But reg73 is used elsewhere (the struct accesses use reg 72 or 73?). Hmm, alloc_table: r72 = "16 times across 43 insns; crosses 2 calls; pointer" → that's `s0` (the arg0 pointer, used in struct accesses). r73 = 2 refs live 5 prefers a0. So r73 is a small pseudo, likely the argument copy.

Where's the copy created? `((void (*)(s32))func_80146C3C)(s0)` — the cast to s32 might create a conversion copy. With plain `func_80146C3C((u8*)s0)` v5 still nop, but maybe v5's reg73 is still created.

Let me check: maybe the copy is due to the call requiring the arg in a register that isn't the variable's; GCC's expand_call copies the arg into a fresh pseudo. It always does? In the target, s0 is a hard reg so the copy is real.

Hmm. What if the call arg is a *compound expression* of s0 that forces materialization, e.g. `(u8 *)(s0 | 0)`? Folded. `(u8 *)(s0 + 0)`? folded.

What if I use `arg0` (the parameter) instead of s0? `func_80146C3C((u8 *)arg0);` — arg0's pseudo might be different and not coalesce to a0. Let me try.

Also `func_80146C3C((u8 *)(s32)arg0)`.

Let me generate a batch now.
