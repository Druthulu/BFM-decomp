---
ts: 2026-11-06T01:46:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6HTnPZOylFL4X5Zm5xZa
---
Yes, .rtl is after RTL generation (before passes).

I'm spending too long. Let me take the pragmatic experimental route: try a variety of real-C shapes and let the scorer tell me. Since each score run takes ~1-2 s, I can try many.

Key promising ideas:
A. Make zero's block end with a *conditional* jump (reorg can then delete it as jump-to-next, since the condjump deletion path at line 664 deletes condjumps to the following insn!). `if (cond) return;` where cond is known... hmm.

Actually the condjump-to-next deletion at 664: `if (reallabelprev == insn && condjump_p (insn)) { delete_jump(insn); }`. For a condjump at the end of zero's block whose target label is right after: delete_jump removes the jump. But then the block's fall-through goes to the label. And the cross-jump at jump2 would see zero's block ending with... after deletion, the last insn before the label would be the store again. Unless the condjump survives until jump2. The deletion happens in the first pass.

B. Make zero's block end with an instruction that reorg later deletes/moves but jump2 sees. E.g., a `nop`-like insn: an empty statement doesn't emit. A `(use ...)` insn? Hmm.

C. Make zero's store's *address* structurally different from dec's at jump2 while emitting the same bytes. E.g., zero: `((Unk*)(a0 + 0))->unk1C = 0x1D;`? Same.

D. Change dec's block so its store is not the last insn before the jump at jump2 — e.g., dec's store followed by another insn. Target dec: lw; nop; addiu; j; sw. If dec had an extra insn between addiu and j that reorg moved... e.g., `unk1C = unk1C - 1;` and then something that emits nothing. Hmm.

E. Use a volatile? Not allowed (lever).

F. Maybe the real C for the zero block doesn't store `0x1D` directly but computes it: `unk1C = (s32)0x1D;` same. What about `unk1C = t + 0x1D;` where t==0? Then RTL differs: (plus reg 29) — but then the store value would be a register different from the li constant... codegen: li v0,29; sw — same bytes but at jump2 the store's source reg differs from... no, still (reg v0) after alloc.

G. What if zero's store is the *same pseudo* as dec's store in RTL but a different instruction... no.

H. THE LABEL TRICK: find_cross_jump's i2 walk skips CODE_LABELs. But what about a NOTE? It skips notes too. Hmm. What about an insn that is a `(use (reg))`? find_cross_jump's loop: p1/p2 compared; a USE insn doesn't decrement minimum (`if (GET_CODE (p1) != USE && != CLOBBER)`). But it still must MATCH (the loop breaks if p1/p2 differ)! So if we place a USE insn after zero's store (before the label) that dec's block lacks, i2 = USE, i1 = store → differ → break → no merge! And USE insns emit no code!

How to get a USE insn after the store? A function argument that is used? `(use (reg))` insns are emitted by expand_function_end for the return value or by... Hmm, for a void function with no return value, there's a `(use (reg 31))`? Actually expand_function_end emits `(use (return_reg))` only if the function returns a value. Our function is void.

But maybe we can create a USE insn via C: a call's argument? No, that's a real move.

I. What about `asm("")` — that's the barrier, not allowed.

J. What if the last block's store is followed by a *call* that is dead-code-eliminated... no, calls aren't removed.

K. What if the zero block's store comes BEFORE the sh, and sched1 reorders? Let me just test variant: `unk1C = 0x1D; CAST_WIDTH(s16,a0,0xF4)=0;` and see the score. If sched1 swaps them to sh;sw, we win (the label's predecessor becomes sh... wait no: if the emitted order is sh;sw, that's target and sw is still last. Hmm no.

Actually! If we write the source as `unk1C = 0x1D;` FIRST and `sh=0` SECOND, then the natural emit order is li; sw; sh. The label's predecessor would be `sh zero,244`, which dec's block lacks → no merge. Then sched1 might reorder sh and sw (both stores, independent) to produce target's li; sh; sw. Does sched1 reorder stores? It can if it thinks they don't alias. Both are struct member stores with constant offsets 28 and 244 to the same base → true_dependence might say they don't alias (different constant offsets, MEM_IN_STRUCT_P). gcc's true_dependence: for two MEMs with constant different addresses, it can prove no alias if both have constant addresses and no overlap — yes! `true_dependence` checks `rtx_equal_p` or, when both are MEM with constant addresses in the same object, uses `anti_dependence`/`output_dependence` with `addr_different_p`. There is a function `addr_different_p` that handles constant offsets from the same base. So sched1 could reorder them.

But would it? sched1 (pre-reload) builds deps; if no dep, it may reorder based on priorities. Target order sh;sw vs source sw;sh. sched1 tends to keep order unless there's a reason. Hmm.

Actually wait — maybe the original source had the assignments in the target's order but with the *sh* being a separate statement whose position... ugh.

Let me just test a batch of variants. Time to be empirical. I'll create variants and score in one command.

Variants:
v1: reorder (sw then sh)
v2: t temp for the constant
v3: do-while around store
v4: pointer for the store
v5: store via *(s32*)(a0+0x1C)
v6: `unk1C = 0x1D; return;` inside `if (1) {}` 
v7: make zero's store use `((Unk*)a0)->unk1C = v;` where v = 0x1D assigned earlier (before the if)
v8: split the store into two? no.

Also consider the dec block: maybe make dec's store's *value* come from a different expression: `unk1C = unk1C - 1` vs `--unk1C`. Same.

Let me write a script to generate variants from orig and score them all.
