---
ts: 2026-10-22T00:12:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_YOvmVosk8OgY4Buuif9s
---
v1 and v2 both 30 — no change. Let me check v3, and then look at the diff of v1 to see whether the chain order changed at all.

Hmm, both 30 and mine 236 ins: the same residual.

Let me think differently. The core problem: two division chains sharing the magic constant; sched1 orders PAN first.

The launder makes VOL first. What else could make the VOL chain first in plain C?

Idea: make the VOL chain's *result* have more uses so its priority is higher. E.g. use `vol` twice — but that changes code... unless the second use is free. Hmm: `vol` is used once in the OR.

Idea: make the PAN chain's *result* have fewer refs or be born later.

Alternative: maybe the trick is that the two chains must not share the magic constant — i.e., the pan division should use a different divisor spelling so gcc emits a different magic. But the target has ONE lui/ori (0x66666667) used twice. Hmm, so both use the same constant.

Wait, actually let me re-read the target:
```
198: lui a0,0x6666
199: ori a0,a0,0x6667
...
202: mult v1,a0
203: mfhi t1
204: addiu v0,a2,160
205: nop
206: mult v0,a0
```
Hmm, "mult v1,a0" and "mult v0,a0": both multiply by a0 = 0x66666667. But hold on: is that really the same constant? For /160: M = 0x66666667, shift 6 (since 0x66666667 * 160 ≈ 2^38). For /20: M = 0xCCCCCCCC? Let's compute: unsigned div by 20: M = ceil(2^32/20) = 214748365 = 0xCCCCCCCD, shift 32. Hmm. But signed division by 20 in gcc 2.7 uses a different scheme.

Hmm, and the shift: for the VOL chain the result was `sra a0,t1,0x6` (shift 6) and for the PAN chain `sra v1,a2,0x3` (shift 3).

So: chain1 (VOL): mult v1 (dividend v1), mfhi t1, sra t1,6 → /160 style. chain2 (PAN): mult v0 (=a2+160), mfhi a2, sra a2,3 → /20 style.

For signed division by 20, gcc 2.7: M = 0x66666667, shift = 3? Let me verify: the classic gcc-2.7 signed division by 20 sequence is:
```
mult dividend, 0x66666667
mfhi t
sra t, t, 3        (?)
subu quot, dividend, t  ... 
```
Hmm, the actual known gcc-2.7 signed div by 20:
```
   mult   $4,$3
   mfhi   $5
   sra    $5,$5,3
   subu   $2,$4,$5
```
Hmm no. The standard for signed division by 20 with M=0x66666667, shift 5: 0x66666667*20 = 0xCCCCCCCD*... let me just compute: 0x66666667 = 1717986919. ×20 = 34359738380 = 2^35 + 12. So M*20 ≈ 2^35 → the product's high word (after shifting right by 3 from bit 35) gives x/20. So the "shift 3" version: (x * M) >> 35 = x/20 approximately. Yes! So for /20, gcc uses M=0x66666667 and a total shift of 35 (i.e. mfhi then sra 3).

For /160: 0x66666667 × 160 = 274877907040 = 2^38 + 96 → (x*M)>>38 = x/160. mfhi gives bits 32-63, then sra 6 → bits 38+. Yes! So both use M=0x66666667 with different final shifts. Coincidence: 160 = 8×20, and the magic for /160 is the same M with a 3-bit higher shift. gcc computes the magic for 160 as 0x66666667 (since 160 = 2^5*5, and the magic for 5 is 0xCCCCCCCD... hmm).

Anyway, the point: gcc materializes the constant 0x66666667 once and uses it for both.

Now, in mine (without the launder), the order is: PAN chain first (mult a0,a2 with a0 = a3+160 = PAN dividend, mfhi a3, sra v0,a3,3, subu a3,v0,a0 → PAN result a3), then VOL chain (mult v1,a2 → mfhi t1 → sra v0,t1,6 → subu a1,v0,v1 → VOL result a1).

Wait, in mine the magic is in a2 (lui a2,0x6666; ori a2,a2,0x6667) and the VOL chain's dividend is v1 — in the target the VOL chain's dividend is also v1! And the PAN chain's dividend: target v0 (=a2+160), mine a0 (=a3+160). And the results: target PAN in a2, mine PAN in a3.

So the register allocation differs: the target uses a2 for the PAN result, mine uses a3.

Note that in the target, a2 holds sx (the sign-extended value) and the PAN result *reuses* a2! ("mfhi a2" — a2 is overwritten by the PAN result after sx's last use). And in mine, a3 holds sx (mine: sra a3,v0,0x10) and a3 is reused for the PAN result.

So the difference is mostly: in the target, sx lives in a2; in mine, sx lives in a3, and the chain order differs.

Hmm! So maybe the root cause is the register assignment of sx (a2 vs a3), and the chain order is a consequence (or vice versa).

In the target: `sra a2,v0,0x10` — sx in a2, and av = a1 (move a1,a2; negu a1,a2). In mine: `sra a3,v0,0x10` — sx in a3, av = a1 (move a1,a3; negu a1,a3).

So the difference is which register sx gets: a2 vs a3. a2 = $6, a3 = $7.

Local-alloc assigns a2/a3 to the block's temporaries. Hmm.

But the bigger issue: the chain ORDER differs (that's a scheduling difference, and 236 vs 237 instructions — the target has an extra instruction!). Which instruction is missing in mine? The target has "addiu v0,a2,160; nop; mult v0,a0" = 3 ins + nop; mine has "addiu a0,a3,160; mult a0,a2" = 2 ins. So the target has an extra "nop"! Because in the target, the `mult` is in a delay slot? No — the "nop" after addiu suggests the addiu is followed by a nop because the mult couldn't be placed in the delay slot (mult has a 5-cycle latency, so the nop is needed).

In mine, the addiu is directly followed by mult with no nop → different scheduling.

OK. So the core: sched1's ordering of the two chains. The launder prevents it.

Let me think about what actually differs in gcc's dataflow: with the launder, the OR reads the asm output pseudo. gcc's sched1 priority: for each insn, priority = sum over operands of REG_N_REFS(operand) etc. The chain that's "born" first...

Alternatively, maybe I can force the order by making the PAN chain's *dividend* computation depend on the vol chain in a way that folds. Hmm: (sx + 0xA0) — the addiu. What if the source wrote the pan as `(sx + 0xA0) / 0x14` where sx is the variable that was JUST assigned from the vol chain? no.

New idea: what if we swap which computation is "vol" and which is "pan" in the source? I.e., the game code might have been:
```
sx = (sx + 0xA0) / 0x14;   /* pan first in source */
...
vol = ((0xA0 - av) * 0x7F) / 0xA0;
```
and the target's generated order is VOL first. But E1 (that exact reorder) gave 33.

Hmm, E1 gave 33 with 235 ins. Different residual.

Let me look at E1's diff to learn. Let me regenerate E1 and dump the diff. Actually, let me look at v1's diff (decl swap) — same score 30, so no change.

Let me try a different tack: check whether the *order* is controlled by which chain's mfhi is the "birth" of match_scratch. The birth = the first mfhi in the pre-sched order = the source order. In the source, vol's division comes first → vol's mfhi is the birth → the birth boost (per moves.md: "sched1-birth-boost: birthing-insn priority boost against a local-alloc constant") applies to the BIRTH insn, i.e. vol's mfhi, boosting it. But mine has PAN first! So in mine, the birth is PAN's mfhi?? That would mean the source order in the compiled code is PAN first — i.e. gcc's expand reordered the divisions?!

Hmm! Interesting: maybe gcc's expand_div emits the divisions in a different order, or the *scheduler* reorders.

Wait, maybe I have the source order wrong: in the source, `vol = ((0xA0 - av) * 0x7F) / 0xA0;` comes first, then `sx = (sx + 0xA0) / 0x14;`. So vol's division is first. In mine, the PAN chain is first in the output. So the scheduler swapped them (as the lever comment says: "sched1 ... always hoisted the PAN multiply ahead of this one").

And in the target (with the launder), the VOL chain stays first (the barrier prevents the swap).

So the question stands: how to prevent the swap in plain C.

Since the swap is a sched1 decision based on priority, and the launder's presence changes the priority of the vol chain's insns (the asm adds a ref to vol, boosting the vol chain's priority)...

So: to boost the vol chain's priority in plain C, give `vol` MORE USES! E.g., if vol had 2 uses, its REG_N_REFS increases → the chain's priority rises → the vol chain might win.

How to give vol a second use without changing the generated code? Hmm: `func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);` — one use.

What if we write it as:
```
s32 arg;
arg = vol | (0x3000 | sx);
func_8002D4C8(0xA9B, arg & 0xFFFF);
```
That doesn't add a use of vol.

Alternatively, boost the priority of the *chain* by other means: e.g. the vol chain's operands: av (hard reg $5, pinned) and 0x7F. The pan chain's operand: sx.

Hmm, what if we give `sx` more uses (lower priority)? sx is used in: the comparison `sx < 0`, the pan dividend, the `if (sx == 0x10)`, the shift, and the OR. Lots.

What if we reduce the *vol* chain's priority? No, we want to increase it.

Hmm, what about the "birth boost" from moves.md: "sched1-birth-boost: birthing-insn priority boost against a local-alloc constant". The birth of match_scratch is the first mfhi. If the birth insn gets a boost, then the vol chain (whose mfhi is the birth, in source order) would be boosted... but mine has PAN first, so the birth is PAN's mfhi. Contradiction unless the pre-sched order isn't the source order.

Hmm wait, maybe gcc's expand_div for `/0xA0` and `/0x14`: the "vol" division ((0xA0-av)*0x7F)/0xA0 — the numerator is a multiply; the division by 0xA0=160 → magic. The pan division (sx+0xA0)/0x14=20 → magic.

In the *pre-sched* RTL, the order would be: vol's chain (mult for the numerator 0x7F*(0xA0-av), then the div-by-160 chain), then pan's chain.

But in mine's output the PAN chain comes first. So sched1 moved it.

OK let me try to look at the actual RTL dumps. The brief mentions `tools/cc1_dumps_tu.sh` and `tools/alloc_table.py` and `.run/P40/T10/hdump.sh`. A dump would show the pre-sched order and the priority decisions. That's the "read dumps when unsure" advice. But dumps are expensive (disk, time).

Alternative pragmatic approach: try more C-level variants, especially ones that change the *number of refs* of vol and sx:

(a) Use vol in a way that adds a ref without adding code: e.g. `if (vol < 0) ...`? That adds code. No.

(b) Change the ORDER of the source so vol's division comes first but with its result used earlier?

(c) Make the pan division a *separate* statement with an explicit temp: `sx = (sx + 0xA0) / 0x14;` → `sx = (sx + 0xA0) / 0x14;` hmm v2 tried a temp for the dividend (pd). No change.

(d) Maybe the fix is about the *multiply* 0x7F: "vol = ((0xA0 - av) * 0x7F) / 0xA0" — the numerator multiply (by 0x7F) is a separate mult from the division's mult. In the target, the first chain is `mult v1,a0` where v1 = the numerator product (0x7F*(0xA0-av)) — so the numerator multiply is NOT a separate mult; it's folded: gcc computes (0x7F * x) * M >> 38? Hmm, that would be two mults. Unless gcc strength-reduces: (x*127)/160 → mult by (127*M)>>... Since 127*M might overflow 32 bits, gcc can't fold. Hmm, but the target shows only 2 mults total: `mult v1,a0` and `mult v0,a0`. So the numerator multiply by 0x7F must be folded into one of them! I.e. gcc computed v1 = 0x7F*(0xA0-av) as... hmm, that would need a mult.

Wait: maybe "mult v1,a0" IS the numerator multiply: v1 = (0xA0-av) [in v1] × 0x7F?? no, a0 = 0x66666667.

Hmm. Let me reconsider: maybe the vol formula in the target is different: maybe vol = ((0xA0 - av) * 0x7F) / 0xA0 is computed as: t = 0xA0 - av; then vol = (t * 0x7F) / 0xA0. gcc: t*0x7F is a mult by 127 (cheap: multu? no, 127 = 128-1 → shift-sub!). Hmm, 0x7F = 127. gcc might compute t*127 as (t<<7)-t. But the target shows no such instructions...

I'm clearly misreading the diff alignment. Let me get the actual target disassembly. Let me find the baseline object and objdump it. Which objdump? The project uses a mips toolchain: tools/psyq? Let me find the baseline object for this TU: search build/ for the object.

Let me use tools/masked_diff.py's insns_from_object via a tool that dumps... `tools/objdiff_report.py`? Let me check for a dump CLI: `tools/asm-differ`?

Quicker: find the baseline .o and use the mips objdump from the toolchain (HOW_WE_WORK.md names it). Let me grep HOW_WE_WORK.md for objdump.

Alternatively use `tools/match_one.py`? Let me check tools/match_one.py's CLI — it might print a diff of two objects.

Let me grep for "objdump" in HOW_WE_WORK.md.
