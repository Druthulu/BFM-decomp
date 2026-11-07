---
ts: 2026-11-06T06:32:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_o0wcwf9btOtADAl7A7DM
---
Target order: 80 125 74 78 73 81 83 76 72
w3 order:       80 125 74 78 73 81 76 83 72

The difference: r83 (2564) and r76 (2127 in target / 3043 in w3) swap. In the target r83 comes before r76; in w3 r76 before r83.

r76: target 5 refs/live 47 → 2127; w3: 7 refs/live 46 → 3043.
r83: 5 refs/live 39 → 2564 in both.

So the launder changes r76's refs from 7 to 5 (live 47). With the launder, r76 has 5 refs → 2127 < 2564 (r83 first). Without, 7 refs → 3043 > 2564.

So r76 is some variable whose refs the launder reduced by 2. Which variable? r83 (5 refs, live 39) is the one that gets $21 in w3 and $20... hmm.

Let me map: with 7 callee-saved and the order, $17..$23? Wait, they all conflict with s0 ($16), so the first gets $17. Hmm, but the final has 8 callee-saved regs ($16-$23).

Order in target: 74→$17?, 78→$18, 73→$19, 81→$20, 83→$21, 76→$22, 72→$23? That doesn't match the asm ($23=s7=arg0).

Hmm, r72 (4 refs, live 63) — in the target $23 is arg0 (s7). Hmm, r72 = arg0? arg0 = the parameter a0, refs 4? In the target asm, arg0 is used in the inner call (`sw $23,20($sp)`) — yes, arg0 has few refs (2 uses + 1 copy). And live 63? arg0 is live from the prologue to the last use. Hmm, live 63 out of 106 — plausible.

OK so r72 = arg0 → $23 (s7) ✓ (last in order).
r83 = ? gets $21 = sign? In w3, r83 → $21 and sign is in $22... 

Ugh, let me just directly identify: in w3, base=$21 and sign=$22 per the diff. In the target, base=$22 and sign=$21.

In w3's order: ..., 81, 76, 83, 72 → $20?, $21, $22, $23? If the first callee-saved allocno gets $17 and they're assigned in order: 74→$17, 78→$18, 73→$19, 81→$20, 76→$21, 83→$22, 72→$23. Then in w3: $21=76, $22=83. So base=76 and sign=83?? But the diff said mine base=$21=s5 and sign=$22=s6. Hmm, that gives base=76, sign=83.

And the target order: 74,78,73,81,83,76,72 → 83→$21, 76→$22. So target: base=76→$22 (s6) ✓ matches "move $22,$2" (base in s6). sign=83→$21 (s5) ✓ matches "sra $21,$20,31".

So: base = r76, sign = r83. And the launder reduces base's refs from 7 to 5 (live 47).

So the launder reduces the ref count of `base` by 2! How? `base = tmp` — with the launder setting tmp, cse can't propagate tmp into base's uses, so base keeps its own refs... hmm, but that would *increase* base's refs, not decrease.

Whatever: in w3 (no launder) base has 7 refs; with the launder it has 5.

To make base land in $22 (after sign), base's priority must be < sign's 2564. Currently 3043. Need refs 5 (→2127) or live ≥ 55 with 7 refs (7*2/55*1e4=2545 <2564; need live ≥ 55).

base's live in w3 = 46. In the target = 47.

Hmm: 7 refs, live 55 → 2545 < 2564 ✓. So extending base's live range by 9 insns would flip it. But that also affects other things.

Alternatively, reduce base's refs by 2 — that's what the launder did.

What are base's 7 refs? `base = tmp` (set), `addu $16,$22,$16` (use inside the call arg). Hmm, only 2 in the source. 7 refs suggests gcc counts the set + uses in different blocks... The REG_N_REFS counts each mention: 1 set + 1 use = 2, but weighted by loop depth: inside a nested loop, depth 3 (outer loop + inner loop + ...). With loop notes: the outer loop depth 2, the inner 3. So a ref inside the inner loop counts 3.

base is set in the outer loop body (depth 2) and used in the inner loop (depth 3). Hmm, 2 + 3 = 5? Not 7.

With the launder: 5. Without: 7.

Hmm. Wait — maybe with the launder, base's use in the inner loop is at depth 2 because... no.

Let me try the practical route: extend base's live range. How? base = tmp is set in the outer body; its last use is in the inner loop. Live = 46. To extend to 55, I'd move the `base = tmp` earlier... it's already right after tmp.

Alternatively reduce refs: what if `base` is used once instead of... it's used once.

OK, alternative practical approach: reduce sign's priority? No, we want sign FIRST (higher priority).

Hmm, we need base < sign: base 3043 vs sign 2564. Need base ≤ 2563.

Idea: give `base` a shorter live range? live 46 → pri 3043; to get < 2564 with 7 refs: live > 54.6. So a LONGER live range helps (divides).

How to extend base's live range without changing code? The live range is from the def to the last use. If I add a use of `base` *after* the inner loop (dead?), it extends live but flow/cse would delete a dead use.

What if the `base` variable is used later legitimately? No.

Alternatively: reduce base's refs from 7 to 5 by... the launder did it. What did the launder do? It's a SET of tmp between `base = tmp` and `mod = (tmp<<16)>>18`.

Hmm — maybe the 2 extra refs in w3 come from cse's copy propagation: base = tmp, so uses of base might be rewritten... no, that would reduce base's refs.

Honestly, refs counting: reg_n_refs counts uses + sets, weighted by loop depth. base: 1 set (outer body, depth 2 → +2) + 1 use (inner loop, depth 3 → +3) = 5. That's the target's 5! And in w3: 7 = 1 set (depth 2) + 1 use (depth 3) + ...? Extra 2 refs: maybe the `move` instruction itself (a set) is counted... 

Wait: in w3, `move s5,v0` — the copy base = tmp is an insn. Its SET counts as a ref (2), and the USE of tmp counts for tmp. In the target, the same. Hmm.

Difference of exactly 2 = one ref at depth 2, or the loop depth changed.

OH! Maybe with the launder, loop.c or jump.c restructures the loop so base's use is at a different depth. Or: in w3, the `addu s0,s5,s0` (base used in the inner loop) — in the target the same.

Hmm, 7 vs 5. Maybe in w3, `base` gets an extra ref because the copy `base = tmp` is *not* the same insn: in the target, tmp is a hard reg, so `move $22,$2` is a set of a pseudo from a hard reg (1 ref for base). Same.

Alternatively the flow's loop_depth differs: with the launder asm, loop.c's move_movables hoisted an insn out of the inner loop, changing which block the base use is in (depth 3 vs 2) → refs 2+2=4? no.

I'm going too deep. DECISION TIME.

Given the evidence, item 2 has a genuine wall: plain C cannot (a) keep the `base = tmp` copy (cse merges copies; only a hard reg or asm keeps it), and the same levers block loop.c's giv/const hoisting. Without them, the body hoists the array pointer and the div-by-3 magic → 107 insns vs 106 and a different register bank.

So: item 2 = WALL. Wall tag: a new one, e.g. `cse-copy-merge-loop` — hmm. Let me pick from walls.txt: "cse-copy-merge" exists (cse merges a copy the target keeps). That's the core mechanism. But there are three coupled effects. I'll tag `cse-copy-merge` with evidence explaining the coupling, and best = 41.

Hmm, but hold on. Before declaring a wall, let me try ONE more idea that could crack the copy in plain C: what if `base` is not a copy of tmp but a *separate expression* that cse can't merge because it's computed from a different but equivalent value? E.g.:

```c
tmp = u * 0x600 + 0x2000;
base = tmp;
```
cse merges. What if:
```c
base = u * 0x600 + 0x2000;
tmp = base;
mod = (tmp << 16) >> 18;
```
cse merges too (tmp = base is a copy).

What if the two computations are textually different but equal? e.g. `base = (u * 3) * 0x200 + 0x2000;` and `tmp = u * 0x600 + 0x2000;` — cse's value numbering would see different expressions (mult by 0x600 vs mult 3 then mult 0x200) — combine might fold them to the same. That would produce TWO computations (2 extra insns). No good.

What about `base = tmp;` where tmp is `volatile`? That's a lever (barrier-ish).

OK, one more: what if base is a *pointer* (u8 *) and tmp an s32? `u8 *base = (u8 *)tmp;` — a copy between modes? Both SImode (pointers are SImode), so cse merges.

Alright. But wait — I should double check the claim "the base copy is needed". In the target, `move $22,$2` exists. If in my body base==tmp, then the register holding tmp is used in the inner loop, extending tmp's live range → different allocation. That's what we see.

Let me do one final quick experiment for a MATCH: use the goto loops (no hoisting) AND give `base` a live-range extension to see if it flips. Too speculative.

Better: accept WALL for item 2 with best 41 (w1). Hmm, but wait: is 41 really the best lever-free? The goto version scored 44; w1 (for loops, no levers) = 41. So best = 41.

Hmm, hold on. Actually, let me reconsider ONE more time whether the pins alone (without the launder) can be replaced... no, we're removing the pins.

Hmm, what about this: the pin is `register s32 tmp __asm__("$2")`. What if instead of removing the pin, we can achieve the same with a *type* trick that keeps the copy: make `base` and `tmp` different MODES, e.g. `base` as `u32` and `tmp` as `s32`. In RTL, a copy between two SImode pseudos is still merged by cse... but if one is HImode? no.

Let me try one: `u32 base;` (instead of s32). It's a 1-line change, cheap to test. cse's make_regs_eqv works on regs regardless of mode? For SImode regs of different signedness, the RTL is identical (reg:SI), so they'd merge.

OK, WALL for item 2. Actually hold on — wait. Let me reconsider the problem once more.

Actually! Let me reconsider: is `base` really only used once? In the inner loop: `func_801850D8(1, (s16)(base + rand() % mod), 0, 0, pos, arg0, ...)`. Yes, one use.

And the target keeps `move $22,$2` (base = tmp). Hmm, but if base == tmp, the compiler would just use $2... but $2 (v0) is call-clobbered and base is used inside the loop across calls, so it MUST be in a callee-saved reg. If base and tmp are the same pseudo, that pseudo (tmp) is live across the inner loop and gets a callee-saved reg — but then `mod = (tmp<<16)>>18` uses it too. In the target, tmp is in $2 (hard reg, pinned) and base in $22.

So with base==tmp (one pseudo), the pseudo lives across the inner loop → callee-saved. That's the "hoisting" I saw.

Fine. WALL.

Hmm, but hold on, let me reconsider the whole thing once more. What if `base` isn't a separate variable in the original source at all — maybe the original source computed `mod` from a variable and used a different expression for the call. But the target asm clearly shows a copy.

DECISION: item 2 → WALL, tag `cse-copy-merge` (existing), best 41, tries ~10, evidence: "plain C: base=tmp merges (cse) so the pseudo lives across the inner loop; only the $2 pin (hard reg) keeps move $22,$2, and the same pins block loop.c's array-giv + div-magic hoist (107 vs 106 ins)".

Hmm, wait. But actually, hold on. Let me reconsider whether the *launder* alone could be replaced by a *dead reset* trick to keep the copy. The launder is a SET of tmp between base=tmp and mod=... What if I write:

```c
tmp = u * 0x600 + 0x2000;
base = tmp;
tmp = u * 0x600 + 0x2000;   // recompute — cse folds it back to tmp? 
mod = (tmp << 16) >> 18;
```
cse would replace the second computation with the first value (same expression) → the copy merges again. Hmm, but the *order* would be: tmp set, base=tmp (copy), tmp set again (deleted as redundant by cse/delete_dead_from_cse?) ... 

What about: `tmp = u * 0x600 + 0x2000; base = tmp; u = u; ...` no.

What about making base a **second use that's a different value**: e.g. `base = tmp;` then `tmp = base;`? Both copies, cse merges all three.

OK. WALL. Let me record it and move on — I still have 2 items and limited time. Actually, let me do one last cheap test: the goto version + `base` used to compute something to extend its life? No. Move on.

Actually — WAIT. One more genuinely different idea, cheap to test: what if I make `tmp` **not** be a single pseudo by giving it a real second set that changes the value meaningfully and is folded? E.g.:

The target's `mod = (tmp << 16) >> 18`. What if I write `mod = (tmp << 16) >> 18;` where the shift is done on `base`? i.e. `mod = (base << 16) >> 18;` — then base is used for mod and tmp is only used for base. Hmm, that makes base the live one.

What if I write `mod = (s16)(tmp >> 2)`? Hmm: `(tmp<<16)>>18` = (s16)(tmp<<16) >> 2 = sign-extended low half >> 2. `(s16)(tmp >> 2)` is NOT the same (shifts the full 32-bit first).

Hmm: `(tmp << 16) >> 18` — this is `(s16)tmp >> 2`? No: (tmp<<16)>>18 takes bits 16..31 of tmp and shifts right 2 with sign. `(s16)tmp` takes bits 0..15. Not the same.

OK. Enough. WALL for item 2.

Hmm, although... hmm. Let me reconsider the value of pushing: the shard has 4 items; item 1 was PARTIAL, item 2 WALL. Let me make sure I don't blow the time budget. Move on to items 3 and 4, which are smaller (26 and 127 lines).

Let me record item 2: WALL, best 41, tries ~10, wall tag cse-copy-merge, evidence ≤ 140 chars.

Wait, but the brief says a WALL needs ≥20 min and ≥30 scored tries. I have ~20 min but only ~10 tries. "fewer is not an attempt". Hmm. So to record a WALL I need ≥30 scored tries.

Ugh. That's the rule: "past 30 min stop and record a wall; a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)".

So I need 30 scored tries for a WALL. That's a lot of compiles, but each is quick (~2-4 s). I can generate a batch of variants and score them with sc.sh (which does one line per candidate). That's the intended workflow.

Alternatively, I could reach PARTIAL:pin if I find a score-0 with pins kept — that requires fixing the base/sign swap (score 5). That's a "PARTIAL" which doesn't need the 30-try rule.

Given the swap is only 2 register pairs (base/sign), maybe a small perturbation flips it. Let me do a batch of variants targeting base's priority/live range:

1. Declare `base` before `tmp` in the decl list? Declaration order affects allocno numbering (tie-break), not priority. Priorities differ here.
2. Move `base = tmp;` after `step = ...`? Changes the live range start (shorter) — that LOWERS live length → raises priority (bad, we want lower).
   Actually we want base's priority LOWER → longer live range. Move `base = tmp` earlier? It's already right after tmp.
   Hmm, what about using `base` in a later statement? e.g. move `mod = (tmp<<16)>>18` before... no.
3. Reduce base's refs: hmm.

Wait — actually the numbers: w3 base r76 = 7 refs live 46 → 3043; target base r76 = 5 refs live 47 → 2127. So the target's base has 5 refs. In w3 it's 7. Both have live ~46.

So the launder reduced base's refs by 2. If I could reproduce that... 

What are the 7 refs? Let me look at the RTL: base's refs. Let me grep the w3 .lreg for r76 mentions. Quick.

Actually, thinking about it: with the launder, `base = tmp` where tmp is a hard reg → the copy is `set (reg 76) (reg $2)`. Without the launder (w3), base = tmp where tmp is a hard reg too (pins are kept in w3!). So both should be the same...

Hmm, in w3 the pin IS kept, so tmp is $2 in both. The only difference is the launder insn.

With the launder, tmp's value after the launder is a *new* value (the asm output), so `base` (assigned before) is distinct and mod uses the new tmp. In w3, mod = (tmp<<16)>>18 uses the same tmp as base.

How does that change base's REF COUNT? Maybe cse propagates: in w3, base and the tmp value are equal, so `base` could be... hmm.

Let me just look: count refs of r76 in the w3 lreg dump. If I can see which insns reference it, maybe I can restructure.

Time. Let me do this quickly.
