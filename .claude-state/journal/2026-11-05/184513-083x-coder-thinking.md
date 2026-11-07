---
ts: 2026-11-06T01:45:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_CW0mmxFriKGwdsgEmV6I
---
This is the "move x=a into both arms" optimization, not ours.

I need to stop and be pragmatic. Time check: item 1 started ~18:28; now maybe 18:50+. Budget 20-30 min per item, 5 items. I should be efficient.

Let me reconsider the problem from the target's perspective: the original C produced target. The current src needed a barrier because a naive transcription merges. Our job: find real C that prevents the merge.

New idea: instead of making zero's block end differently, make the *dec* block's store not match zero's store by making dec's store use a different address expression that still emits `sw v0,28(s0)`. At jump2, both are (mem (plus s0 28)) — same.

But what if dec's store address is computed through a different base register *at jump2* that reload later coalesces to s0? Post-reload, no.

OK here's another angle: the cross-jump is between dec's block (ending with jump to epilogue) and the *label's physical predecessor*. If zero's store were not immediately before the label — e.g., if the `sh zero,244` came AFTER the `sw` — then i2 = sh zero,244 which differs from dec's store → no match. But target order is li; sh; sw. Could the compiler reorder the source order sh; sw to li; sh; sw? Target IS li; sh; sw. If source writes `unk1C = 0x1D; sh = 0;`, the compiler emits li v0,29; sw v0,28; sh zero,244. That's li; sw; sh — different from target. So no.

Unless sched1 reorders the two stores: writing sw then sh, sched1 might swap them to sh then sw? Both are stores to the same base with different offsets; sched1 (pre-reload) could reorder independent stores. Hmm, plausible? Target has sh before sw. If the original source had the assignments in the order sw then sh, sched1 could have reordered... but stores are usually kept in order due to aliasing (both mem in struct, varying offsets → they may alias). sched's true_dependence for struct members with different offsets: it may consider them non-aliasing? In gcc 2.7.2, MEM_IN_STRUCT_P with constant offsets — the aliasing check may still say they alias. Risky.

Let me try the simplest experiments and let the scorer tell me. I'll write a batch of ~10 variants and score them all. Variants to try:

1. `return;` at end of zero (done: 9)
2. reorder zero's last two stores: `unk1C = 0x1D; CAST_WIDTH(s16,a0,0xF4)=0;`
3. `t = 0x1D; unk1C = t;`
4. do-while around the store: `do { unk1C = 0x1D; } while (0);`
5. `((Unk*)a0)->unk1C = 0x1D; return;` with a `goto` structure: `goto zero; ... zero: ...; goto end; end: ;`? 
6. Use `if (1) return;` at end.
7. Make zero's block end with `return;` inside an if: `if (1) { ...; return; }`.
8. Move the zero block earlier in the source (before dec) so zero isn't last? That changes layout drastically.

Actually, let's revisit: what if the original source's zero block was NOT at the end but the last statement was a `return;` and the epilogue label placement... The target physical layout is determined by block order which follows the order of labels/branches. zero is the target of `beqz v0, zero` and appears last.

Hmm, wait. Let me reconsider the whole thing. Maybe the original C didn't have the `goto zero` structure at all! The src is a *reconstruction* with goto labels. The target's structure has zero as the fall-through block at the end. The original source may have been:

```
if (t == 0) { ...zero code...; return; }  // or without return
```
Hmm, but the target zero block at 17d0 starts with `move a0,s0; jal func_80185D3C` — it's reached by beqz from the `t==0` test.

The key insight might be: the original C has the zero block ending with a `return;` that the compiler *keeps* as a jump because the epilogue label is NOT immediately after at jump2 — e.g., because the original has the zero block NOT last but with a `goto`/label arrangement such that the epilogue is shared differently. But the target layout shows zero last.

Alternatively: maybe the original C's zero block ends with a `return;` and the compiler's jump-to-next deletion doesn't fire because there's a NOTE_INSN_LOOP_END or a BARRIER between. Hmm.

Let me just look at how OTHER cracked functions in this project dealt with the same "trailing store shared with a return block" cross-jump. Search moves.md/src for "cross-jump" MATCH entries with details. Line 77: "barrier: swap inner arms if(!overshot){store;ret=1;}else ret=0 (no cross-jump)". Line 240 is a WALL.

Search src comments for "cross-jump" + "cracked" or "instead". Maybe the cookbook has a real-C cross-jump defeat: §5a. Let me grep the cookbook index around line 515-545 and §34/§162.
