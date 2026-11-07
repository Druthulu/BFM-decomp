---
ts: 2026-11-06T21:55:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bmggYPxdimPhLgSkMmLl
---
The `li a3,6` is `tmp = 6;`? No — a3 = $7. Hmm, in the target at 312 `li a3,6` where a3 is used later? Let me look at the target disassembly around 306-330 to see.

Actually, the missing insn means the *target* has an extra `li a3,6`. In the target's register bank, a3 = $7. Maybe that's the `tmp = 6` where tmp is pinned to $2? No, target's tmp pin is $2=v0. Hmm.

Wait: target at 307 `li v0,6` = tmp=6 (v0=$2). Then at 312 `li a3,6`. a3 might be another variable = 6 (e.g., cnt or unk1C?). Hmm, the source at L801921F8: `tmp = 6;` then `unk34 = tmp; unk1C = 0x96; return;`.

Where's `li a3,6` from? Maybe the compiler duplicated `tmp = 6` across the two paths (the goto and the fall-in), assigning different regs? No.

Hold on: mine has `li a3,6` at 307 (delay slot) and target has `li v0,6` at 307 and `li a3,6` at 312. So both have an `li a3,6`, but the target ALSO has `li v0,6`. The extra target insn is `li v0,6`.

So in mine, `tmp=6` compiled to a3 (not v0) because the pin was removed; and the *other* li a3,6 (mine's) corresponds to target's li a3,6. Wait, mine's 307 is `li a3,6`; target's 312 is `li a3,6`. And target's 307 is `li v0,6` (extra). So mine is missing one `li` because the pin removal merged tmp=6 with the other 6.

So the source has TWO `= 6` values: `tmp = 6` and something else = 6. In the target, tmp=$2 (v0) and the other is a3. In mine, both got a3? Actually mine has only one li a3,6 — meaning the compiler CSE'd/merged the two constants into one register (a3) and reused it. The target kept them separate because tmp was pinned to v0.

So lever-free, the compiler merges `tmp=6` with the other variable's 6 → 1 ins. That's a "flow/cse constant merge". The target has two.

Hmm, this is the `tmp` pin's effect: tmp in $2 forces a separate copy.

Where is the other 6? Let me look at the target disasm around 300-320. Need the target object. The TU is src/ov_SC06_032/ov_SC06_032_jr_801919A0.c → build/src/ov_SC06_032/ov_SC06_032_jr_801919A0.o.

Let me disassemble the target function around that area. But the diff already gives: mine 306 `bnez v1,858`, 307 `li a3,6`; target 306 `bnez v1,85c`, 307 `li v0,6`, 312 `li a3,6`. Between 307 and 312 there are insns 308-311 that match. Let me get the full region from the target.

Actually, this is the region after case 8: `if (cnt == 0) goto L801921F8;` then SCAN macro then `break;`. The `li a3,6` might be inside the SCAN macro's `p+0x70 == 6` comparison? No, that's a comparison.

Hmm, `li a3,6` could be `tmp = 6` in mine and the *other* 6 is `unk1C = 0x96`? no.

Let me just disassemble the target and mine around there. But given the size and the fact that this is one of 4 items with ~30 min budget, and the residual is 135 (52 hunks), cracking it requires matching the whole bank. That seems very hard.

But wait — maybe there's a simpler interpretation: the pins dst=$3, tmp=$2 were *both* doing allocation work across the whole function. Lever-free gives a completely shifted bank. Matching 710 ins exactly without pins is likely infeasible in 30 min.

Given the shard design, maybe the expected outcome for the big ones is WALL with best 135 (or maybe a partial improvement). The instructions say: retry because they were banked PARTIAL after <30 tries; remove the kept kinds with new moves. If we can't, WALL.

Let me spend ~20-25 min trying the most promising moves on the twin pair, since a crack would be worth 2. Key lever: get dst into $3 and tmp into $2 naturally.

For tmp: tmp is a call-result-ish variable used as `tmp = *(s32*)sp10; ... = tmp; ... = tmp >> 16;`. $2 is the return-value register; if tmp were the direct result of a call, it'd be $2 naturally. But it's a load from sp10.

For dst: dst is a pointer loaded from arg0+0xD0, used as a base in stores. $3.

Alternative: maybe the pins can be replaced by *narrower* real-C moves:
- The `dst` blocks are repeated 6 times with identical code (dst=arg0+0xD0; 8 stores; dst=arg0+0xD4; 8 stores). If we made dst a `u8 *` or a struct pointer, or reused a single variable, the allocation might change.
- The C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse.

Let me try a few structural moves:
1. Make dst a `Unkstruct_800B5CB8 *` typed pointer instead of s32, with field accesses. Big rewrite; might change codegen.
2. Change `*(u16 *)(dst + 6)` etc. to use a `u16 *` local.
3. Reorder the dst blocks' statements.
4. Declare dst inside each block (scope) instead of function-level — changes qty/lifetime and possibly allocation.
5. Declare tmp inside blocks.

Actually! Declaring dst *inside* each case block (scope) vs at function top: the C variable's lifetime is the same either way in RTL (each def-use is a separate pseudo). Decl scope doesn't matter to RTL much.

The real lever for $3: the pin gave dst a hard-reg preference. Without it, local-alloc gives $3 to whichever qty wins. In the dst blocks, dst is the first value defined (`lw dst, 0xD0(s1)`) and used many times. It's a long-lived pointer in the block. local-alloc would give it a low priority (long life) → gets a callee-saved or a high-numbered reg. But target has $3.

Wait, in the target, dst is in v1 ($3) — a caller-saved scratch. If dst is long-lived within a basic block, local-alloc might still give it $3 if other regs are busy.

In mine, dst is in a2 ($6). The difference is which regs are taken by other qtys.

This is essentially the same class of wall as item 1: local-alloc qty priority. But the residual is much bigger (135), suggesting the whole bank shifted.

Hmm, but maybe the bank shift is *caused* by dst: if dst takes a2 instead of v1, then the temporaries that used a2 must move (v1→a0→a1→...). So a single wrong assignment cascades. If we can get dst into $3, everything else might fall into place (score 0). The 52 hunks are all consequences.

So the crack = get dst→$3. That's ONE qty.

Similarly tmp→$2 might be mostly redundant.

So focus: make dst get $3. How?

In the target, dst = `lw v1,0xD0(s1)`. In mine, `lw a2,0xD0(s1)`. The dst qty in the block is long-lived (8 statements). Its priority is low. To get $3, the qty must be allocated when $3 is free — but lower-priority qtys get whatever is left after higher-priority ones take the low regs. So dst gets a2 only because $3,$4,$5 were taken by higher-priority qtys (the temporaries in the same block, which are short-lived and thus higher priority).

To make dst get $3, we need... the high-priority temps to take $2,$4,$5 and leave $3. That's determined by their priorities and qty numbers.

Alternatively, make dst's qty higher priority by shortening its live range: e.g., use dst only for the first few statements then reload. But that changes code.

Hmm, what if the original source did `dst = *(s32*)(arg0+0xD0);` and then used `dst` — exactly ours. The target's allocation is a consequence of the whole block's qty set. Our reconstruction differs somewhere else in the block, causing the shift. The most likely difference: the temporaries' shapes (e.g., `*(u16 *)(*(s32 *)(dst + 0x20) + 0x10) = *(u16 *)(dst + 0xFC) + *(u16 *)(*(s32 *)(src + 0x20) + 0x10);`).

Let me compare the target's dst-block disassembly with mine to see if the *instruction sequence* matches except registers. From the diff, yes: same insns, different regs. So the RTL is the same shape; only allocation differs.

So it's purely local-alloc. The qty set is identical (same RTL), yet allocation differs?! That's impossible unless the *pin* affected it. Right: with pins, dst is $3 by declaration. Without, local-alloc decides.

So the target's original source must have had *some* hard-reg preference or a different RTL. Since the reference binary has dst in $3, and our identical RTL gives a2, the original source likely pinned it too (register asm) OR the original had a different RTL that changes the qty priorities.

Hmm wait, but maybe the original source didn't use a `dst` variable at all — it might have used `arg0->unkD0` directly in each statement, causing reloads into different regs. But the target shows dst kept in v1 across all 8 statements, so it was a variable.

Alternatively the original had TWO variables (dst for 0xD0 and dst2 for 0xD4) with separate lifetimes.

Or the original used `register s32 dst asm("$3")` — PSX-era code did sometimes use register pins in hot functions. If so, WALL.

Given the difficulty, let me do a time-boxed exploration on the twin. Try ~15-20 structural variants. If none < 135 significantly, WALL.

Let me think about what could change local-alloc enough:
- The dst blocks use `src` (a global-ish pointer) and `arg0`. In the target, src is s0? Let me see: `lw v1,32(s0)` — s0 holds src? Actually `lw v1,32(s0)` loads *(src+0x20). So src is in s0 (callee-saved, global allocno). arg0 is s1.
- dst is the only long-lived local.

What if we make dst `u8 *` instead of s32? Then `dst + 6` same, but `*(s32*)(dst+0x20)` same. Mode of dst would be pointer (SImode). Same.

What if we make dst a `Unkstruct_800B5CB8 *`? Then field accesses `dst->unkFC` etc. The struct type may change the RTL (e.g., mem/s vs mem). Might change codegen (different addressing?). But the target's insns would then need to match; the current body already matches the target insns exactly, so changing types risks breaking. But maybe the *original* used the struct type and it generates the same insns but different qty priorities (e.g., mem/s vs mem affects scheduling?).

Hmm, the current body scores 0 with pins — so its RTL shape matches the target exactly. Any structural change that keeps the same insns but changes allocation is what we want. Type changes (s32* vs struct*) could alter `mem/s` flags → scheduling → lives → allocation. That's a real lever.

Let me look at the exact statements in a dst block and try:
(a) struct-typed dst: `Unkstruct_800B5CB8 *dst;` and `dst = (Unkstruct_800B5CB8 *)*(s32*)(arg0+0xD0); dst->unk6 = ...` — but the struct's fields (unk6 etc.) may not exist. Let me check the struct definition.

Actually the body uses raw offsets like dst+6, dst+0xA, dst+0xE, dst+0x20, dst+0xFC, dst+0xFE. The struct Unkstruct_800B5CB8 likely has these as unk6, unkA, unkE, unk20, unkFC, unkFE. Let me check.

This is a lot of work. Given the time budget (already ~1h10m total), let me be strategic: spend 20 min on the twin with a handful of variants, then WALL if no crack, then do item 4 (the twin) quickly as WALL (same body, same result), and finish.

Actually wait: item 4 (80191C50) is the *twin* — same body. If I crack 801919A0, I can apply the same move to 80191C50. If not, both are WALL with best 135.

But hold on — the twin's notes say the last call differs (func_8018FE0C vs whatever). The bodies are otherwise identical. The lever-free scores may differ slightly.

Let me try a batch of variants on 801919A0:
1. dst as `u8 *`.
2. dst as `Unkstruct_800B5CB8 *` with field names.
3. dst declared inside each block (6 separate locals) — same pseudos.
4. Reuse one variable for dst and the temporary `src`? no.
5. Change `dst + 0x20` to `(*(s32 *)(dst + 0x20))` hoisted into a temp? changes code.
6. tmp as `u32` / `s16`.
7. dst as `s32` but initialized at declaration: `s32 dst = *(s32 *)(arg0 + 0xD0);`? The blocks have `dst = ...` then uses; init at decl would move the load earlier (different schedule) — but only for the first block.
8. Reorder the two halves of each block: `dst = ...0xD0` block then `dst = ...0xD4` block — already.
9. Make `src` a `u8 *`? src is used as `*(s32*)(src+0x20)`.

Let me first check the struct definition to enable (2).

Actually, a cheaper idea: the target's dst=$3 (v1) is the *lowest* caller-saved scratch. In mine dst=a2 ($6). The difference: mine's block has more high-priority qtys taking $3,$4,$5. What are they? The temps in the block: v0 ($2) used as the loaded u16 sums; v1 ($3) used as a temp in mine? Looking at mine's block:
```
148 sh v0,14(a2)      dst=a2
149 lw v1,32(s0)      temp
150 lhu v0,252(a2)
151 lhu v1,16(v1)
152 lw a0,32(a2)
153 addu v0,v0,v1
154 sh v0,16(a0)
...
```
So mine uses v1,a0 as temps; target uses a0,a1. Target: dst=v1, temps a0,a1. Mine: dst=a2, temps v1,a0. So the whole bank shifted up by 1-2. That means in mine, some other qty took $3 and $4... but the only qtys are these temps. It seems like a rotation: dst got a2 because $3,$4,$5 were "preferred" by something.

Could it be that dst's qty has a *copy suggestion* to a2 in mine? dst = lw from memory; no.

Hmm, what if `src` (s0) or `arg0` (s1) ... no.

Honestly, the most likely explanation: the reference source had `register s32 dst asm("$3")` (a pin). The prior author's notes even say "$3 (dst) and $2 (tmp) stay; dropping them shifts the dst chain into a2". The shard asks to try lever-free anyway.

Given the cost, let me try just a few variants (5-8) and then record WALL with best 135. But the WALL criteria require ≥30 scored tries. For a 710-ins function, 30 tries is doable (each ~3-5s). Let me batch ~30 quick variants mechanically.

But first, let me quickly test the struct-typed dst idea since it could genuinely change things. Let me check the struct.
