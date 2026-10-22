---
ts: 2026-10-22T00:14:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG11
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ax56DxXircUW1f5ngOoD
---
Now I see the candidate's structure clearly:

MINE:
```
198 lui a2,0x6666
199 ori a2,a2,0x6667
200 addiu a0,a3,160     ; PAN dividend
201 mult a0,a2
202 li v0,160           ; VOL numerator start
203 subu v0,v0,a1
204 mfhi a3              ; (mfhi of the PAN mult, sunk here)
205 sll v1,v0,0x7
206 subu v1,v1,v0
207 mult v1,a2
208 sra a0,a0,0x1f
209 sra v0,a3,0x3
210 subu a3,v0,a0
211 sra v1,v1,0x1f
212 mfhi t1
213 sra v0,t1,0x6
214 subu a1,v0,v1
```

TARGET:
```
198 lui a0,0x6666
199 ori a0,a0,0x6667
200 li v0,160
201 subu v0,v0,a1
202 sll v1,v0,0x7
203 subu v1,v1,v0
204 mult v1,a0
205 mfhi t1
206 addiu v0,a2,160
207 nop
208 mult v0,a0
209 sra v1,v1,0x1f
210 sra a0,t1,0x6
211 subu a1,a0,v1
212 sra v0,v0,0x1f
213 mfhi a2
214 sra v1,a2,0x3
215 subu a2,v1,v0
```

So the target: VOL chain fully first (numerator, mult, mfhi), then PAN chain (addiu, nop, mult), then the results interleaved (sign extraction and subtractions).

Mine: PAN's addiu+mult first, then the VOL numerator, then mfhi of the PAN mult, then the rest.

So the difference: the *order of the two chains* (mine interleaves them: PAN's mult, then VOL's numerator, then PAN's mfhi, then VOL's mult...). It's the sched1 interleaving.

In the target, the two chains are NOT interleaved: VOL's mult+mfhi are adjacent (204,205), and PAN's addiu+mult are adjacent (206,207,208) — and the two mfhi's are separated (205 and 213).

So the target's schedule: VOL numerator → VOL mult → VOL mfhi → PAN addiu → PAN mult → [VOL sign, VOL result] → [PAN sign, PAN mfhi, PAN result].

Mine: PAN addiu → PAN mult → VOL numerator → PAN mfhi → VOL mult → ...

The launder's effect: it makes the VOL chain a "unit" that sched1 keeps together? Hmm.

Since the launder sits between the vol statement and the pan statement in the source, and gcc's asm is a scheduling barrier, the pan chain (after the asm) can't move before the asm, so the pan chain stays after the whole vol chain.

Without the barrier, sched1 interleaves.

So I need a real dependency ordering the PAN chain after the VOL chain. The only clean way: make the pan's dividend depend on the vol's computation... but semantically impossible.

Hmm, BUT: what about the *magic constant*? Both chains use the magic M. In the target, the magic is in a0 and both mults use a0. The mults are ordered: VOL's mult (204) then PAN's mult (208). Since both read the same constant, no dependency.

What if I write the pan division differently so that gcc uses a *different* magic constant, e.g. by writing the pan as an unsigned division or by a different spelling? Then there'd be two lui/ori pairs — the target has one → mismatch.

Hmm. What if the pan division is written to reuse the same magic via a *shared expression*? E.g. compute the magic as a variable? We can't name the magic constant; gcc derives it.

OK, different approach: what if the vol chain's *result* is used by the pan chain in a way that folds away? E.g.:
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = (sx + 0xA0) / 0x14;
```
What if instead:
```
sx = (sx + 0xA0) / 0x14;
vol = ((0xA0 - av) * 0x7F) / 0xA0;
```
(E1, gave 33).

What if the *order of the two statements* is vol first but with the pan's dividend computed inside the vol statement? no.

Alternative: maybe the "no new lever" constraint allows a plain C construct that creates a scheduling dependency: e.g. a comma expression? Or an assignment that the compiler keeps?

What about making the pan's dividend depend on the vol's *numerator* through a mathematically-neutral transformation that gcc folds? E.g.:
`sx = (sx + 0xA0) / 0x14;` → we want the addiu to be *after* the vol chain.

Hmm, what if we use a temporary for the pan dividend that is assigned from a value that the vol chain produces, in a way that the compiler folds? Like:

```
s32 q = 0xA0;               /* the constant */
vol = ((q - av) * 0x7F) / q;
sx = (sx + q) / 0x14;
```
Hmm! Interesting: sharing the constant `q` between the two divisions. But gcc's magic for /0xA0 and /0x14 are the same value (0x66666667) but derived from different divisors — sharing a variable wouldn't share the magic.

But wait — this changes the divisors? No, same divisors.

Hmm, but the *order* effect: with a shared variable q, the two chains both read q → still independent.

Let me think about what makes sched1 keep the VOL chain together: in the target, the VOL chain (200-205) is contiguous. gcc's sched1 wouldn't keep them contiguous unless there's a "birth" priority: the first chain is placed first, then the second.

Actually, maybe the real difference is this: the launder creates a pseudo (the asm output) whose birth is the asm. The asm is a zero-byte insn but counts as an insn in the block. So the block has: [vol chain][asm][pan chain][or]. The scheduler's "birth" of the asm output pseudo is the asm insn; the OR reads it. So the OR depends on the asm, which depends on vol. The pan chain is independent of the OR's other operand...

But the key: the asm is a scheduling BARRIER in gcc (asm insns are barriers for the reorder passes: in gcc 2.7's `reorder`/`sched` the ASM insn is given a huge priority / is not moved). So the pan chain cannot be moved above the asm, and since the pan chain is after the asm in the RTL order, it stays after the vol chain.

Without the asm, sched1 (which is the "pre-reload" reorder) is free to move the pan chain up.

So to reproduce this in plain C, I need the pan chain to be *dependent* on the vol chain, or to be in a position that can't be moved.

Idea: What if the pan's dividend is computed from a variable that the vol chain also writes? Not semantically possible...

BUT WAIT. What about the *nesting*: `vol` is used in the OR, and `sx` (pan) is used in the OR too. What if we restructure the OR as:

```
s32 arg;
arg = vol | (0x3000 | sx);
```
The target's code: "ori a1,a1,0x3000" (vol|0x3000) then "or a1,a1,a2" (|pan<<8). So the OR reads both.

Hmm, what if the pan is folded INTO the vol's expression? Like:
```
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
already.

Idea: use a *comma/sequence* that forces order: In C, `a = (b, c)` — gcc might keep the order. E.g.:

```
sx = (sx + 0xA0) / 0x14;
```
What if I write the pan computation as a function argument? No.

Idea: use the *result* of the vol chain in a comparison that the compiler keeps but which doesn't change semantics... any such use adds instructions.

Hmm, but hold on: what if the constraint's "real C moves" include making the *vol* computation part of an expression that the pan depends on through a *no-op* that gcc folds? gcc folds all no-ops.

What about `volatile`? That's a lever of another kind (not in the row kinds: pin, launder, barrier, keepalive). Constraint: "no new lever of any kind" — volatile is a "lever"? The lever census kinds are: pin, barrier, launder, keepalive, instruction, gte-lever, asm-body. `volatile` is not in AB_KINDS. Hmm, "no new lever of any kind" might include volatile as a lever in the census? The census's AB_KINDS = {"pin", "barrier", "launder", "keepalive", "instruction", "gte-lever", "asm-body"} — volatile isn't there. But R126 mentions "a byte-needed `volatile`" as class C/D. Risky: adding volatile would change the generated code anyway (it forces reloads).

OK, let me think about the *other* direction: maybe the answer is to make the VOL chain the one that's "born" later so that the ORDER comes out right.

Hmm, alternatively: maybe I can make the two chains NOT share the match_scratch by making gcc emit two different magics — no.

Let me look at this from the "what did the original game source look like" angle: the target code is the ORIGINAL game's compiled code (from the game's own source, compiled with gcc 2.7.2 by the original developers? No — the target is the original game binary, compiled by the original Sony compiler, not gcc 2.7.2!).

WAIT. That's crucial! The target is the ORIGINAL GAME's assembly (compiled with the original toolchain), and we're trying to reproduce it with gcc 2.7.2. The banked body (with the launder) reproduces it byte-for-byte. So the launder is a *hack* to make gcc 2.7.2 produce the original order.

So the question is: what source construct makes gcc 2.7.2 schedule it that way? The original source might have had the pan division *before* the vol division, or the pan's dividend computed in a separate statement later.

Since the original code has the VOL chain fully first and then the PAN chain, and gcc 2.7.2 (without the barrier) interleaves them...

Hmm, what if the original source computed the pan dividend LATER, e.g.:

```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = (sx + 0xA0) / 0x14;
```
The pan's addiu is in the target at 206, right before its mult. gcc's sched1 sank it there.

What if the original source was:
```
sx = sx + 0xA0;      /* separate statement */
sx = sx / 0x14;
```
Then the addiu is a separate statement; the compiler would compute the addiu early (sched1 hoists it) unless... v2 (pd temp) gave no change (30).

Hmm, what if the pan's dividend is *not* a simple add but depends on the sign handling, e.g. in the original source the pan might be computed as `sx = (sx + 0xA0) / 0x14` where sx is the *unsigned* 16-bit value + 0xA0? Hmm: in the target, the pan dividend is a2+160 where a2 = the sign-extended sx (which is negative in the fall-through path!). So pan = (sx+160)/20 with sx possibly negative.

Hmm wait, that means in the fall-through (sx<0) path, the pan is computed from a NEGATIVE sx. And the target computes "sra v0,v0,0x1f" (sign of the dividend) for the correction. OK.

So the source is as we have it.

Now, how to reproduce the ORDER in gcc 2.7.2 without a barrier?

Let me think about gcc 2.7's sched1 (the "pre-reload" scheduler). It's `sched1` in the reorder pass. Its priority function (in sched.c, `rts_prio` / `init_priority`): each insn's priority is computed from REG_N_REFS of its operands and the number of references, and the "birth" of a pseudo gets a boost? The moves.md mentions "sched1-birth-boost: birthing-insn priority boost against a local-alloc constant".

So the birth of match_scratch: the FIRST mfhi (in the RTL order) is the birth. In the RTL (pre-sched) order, the vol's mfhi comes first (source order). The birth boost would then favor the VOL chain... but the observed behavior is the opposite (PAN first). So the birth boost isn't what decides; the boost applies to the *birthing insn* — the mfhi that first defines match_scratch. If the vol's mfhi is the birth, then the vol's mfhi gets boosted, which should make the vol chain win. But mine has PAN first!

Unless the RTL order after expand is: the pan's division chain first! Why? Because gcc's expand_div is called on the expressions in some order, or because the *statement order* in the RTL is determined by the order of the expanded insns which might be reordered by an earlier pass.

Hmm! Actually, maybe the order in the RTL is: gcc expands the whole function's expressions; the two divisions are expanded in the order they appear in the *expression tree* of the statement. In my source, vol's statement comes first. So the vol's chain should be first in the RTL.

Then sched1 (the reorder) moved the pan's chain up. Why? Because the pan chain's insns have higher priority. The pan's chain: addiu v0,a3,160 (uses a3 = sx, which has many refs?) and mult.

Hmm, in the target, the vol's chain is first — the same source, but with the barrier.

So the barrier prevents the reorder. Without it, the reorder moves the pan chain up.

Which means: the pan chain has higher priority than the vol chain. The pan chain's dividend uses sx (a3/a2 = the sign-extended value) — sx has several refs (the compare, the addiu, the shift, the or). The vol chain's dividend uses av (a1, pinned $5 — a hard reg, which has FEWER refs?).

The launder changes: the OR now reads the asm's output pseudo instead of vol. Hmm, and vol gets an extra ref (the asm's input "0"(vol)). So vol's REG_N_REFS goes from 1 to 2 → the vol chain's priority rises → vol wins. THAT's the mechanism!

So to reproduce: give `vol` an extra reference in the source, without changing the generated code!

How? A second *use* of vol that the compiler folds into the same instruction? Hmm. E.g.:

```
func_8002D4C8(0xA9B, (vol | (0x3000 | sx)) & 0xFFFF);
```
If we write:
```
s32 arg = vol | (0x3000 | sx);
func_8002D4C8(0xA9B, arg & 0xFFFF);
```
vol still has 1 use.

What about a use of vol that is *free* in terms of instructions: e.g. `vol = vol;`? That's an identity statement — explicitly disallowed as a "launder" ("identity-statement launders do NOT count as a crack"). Hmm, but would it even help? `vol = vol;` is a self-assignment; gcc would remove it (it's a no-op) — no extra ref.

What about using vol in a way that produces no code but counts as a use: e.g. `if (vol) { }`? gcc removes it. `(void)vol;`? removed.

Hmm, what about using vol in the *same* expression twice in a way that folds: e.g. `vol | vol`? changes semantics.

What about: `vol2 = vol;` and then use vol2 in the OR — that's the "real 2nd set" pattern (vol2 = vol creates a copy — but gcc would coalesce the copy → no extra insn, and it creates a second set!). Hmm: `s32 vol2 = vol;` — gcc's cse would propagate vol2 = vol and eliminate the copy, making vol2 an alias (same reg). That gives vol a second *set*? Not exactly; it gives vol2 a set (copy of vol) and the OR reads vol2. The "real 2nd set" pattern in moves.md was exactly like this ("launder->real 2nd set pv &= 0xFF000000" — there the second set was a real computation).

But: would `s32 vol2 = vol;` create a real dependency/priority change? In gcc's RTL, vol2 = vol is a copy insn (reg = reg) that gets coalesced/removed. Before removal, the OR reads vol2, so the chain vol → copy → or. The copy insn is a real insn in the RTL that sched1 must schedule (it gets removed later by copy propagation). This might create exactly the same scheduling constraint as the asm! And it's a "real 2nd set" in the C0505 catalog sense (temps!).

Hmm, but the constraint says "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". A copy `vol2 = vol` is an identity statement... but it's not laundering *within* a variable; it's creating a temp. Hmm, the spirit of the rule: don't fake a launder with a no-op statement. A copy to a temp is exactly the "real 2nd set" recipe that other shards used successfully ("launder->real 2nd set").

Hmm, but a pure copy might be optimized away by gcc before scheduling, making it a no-op.

Let me just try it! Variants:
W1: `s32 vol2 = vol;` then use vol2 in the OR.
W2: `vol = vol;`? (identity — probably not allowed and likely useless)
W3: Give vol a second use in a *real* way: hmm.

Actually here's a cleaner idea in the same spirit: the "real 2nd set" for the VOL value: split the *use* of vol into two parts:
```
s32 arg;
arg = vol | 0x3000;      /* hmm, the target has "ori a1,a1,0x3000" */
arg = arg | sx;          /* the target has "or a1,a1,a2" */
func_8002D4C8(0xA9B, arg & 0xFFFF);
```
That doesn't give vol a second use.

OK here's another thought: give the *pan* fewer refs or the vol chain higher priority by changing the *sx* uses. E.g. sx is used in: `sx < 0` compare, `sx + 0xA0`, `sx == 0x10`, `sx << 8`, and the OR. If we reduce sx's refs (e.g. compute the compare differently), the pan chain's priority drops.

Hmm, but the target has exactly these uses.

Let me just try W1 (vol2 = vol copy) and a few others. Experiments are cheap (~30 s each).

Let me prepare several variants and score them:
W1: add `s32 vol2;` decl; after vol's computation: `vol2 = vol;` and use vol2 in the OR.
W2: `sx` used once less: e.g. replace `if (sx < 0) { av = -sx; }` with `av = sx; if (av < 0) { av = -av; }`? that changes the compare to av (same value) — might change the register assignment (av is $5 pinned; the compare would use a1). Hmm, that changes code.
W3: give the pan dividend via av: no.

Let me also consider: maybe the fix is to make the VOL chain's *numerator* computation (li v0,160; subu v0,v0,a1; sll; subu) come earlier/later...

Let me look at the target order again:
```
198 lui a0,0x6666
199 ori a0,a0,0x6667     <- magic first
200 li v0,160
201 subu v0,v0,a1
202 sll v1,v0,0x7
203 subu v1,v1,v0
204 mult v1,a0
205 mfhi t1
206 addiu v0,a2,160
207 nop
208 mult v0,a0
209 sra v1,v1,0x1f
210 sra a0,t1,0x6
211 subu a1,a0,v1
212 sra v0,v0,0x1f
213 mfhi a2
214 sra v1,a2,0x3
215 subu a2,v1,v0
```
Note "addiu v0,a2,160; nop; mult v0,a0" — the nop is because mult has a delay (the mult can't be in the addiu's delay slot; gcc's reorg/sched inserts a nop). In mine, "addiu a0,a3,160; mult a0,a2" — no nop! So in mine the mult IS in the addiu's delay slot (reorg stole it). Interesting.

In the target, the addiu+mult are separated by a nop. That's the "reorg" (delay slot filling) pass: in the target the addiu is followed by a nop because... hmm.

Also note in the target, the chain "mult v1,a0; mfhi t1" is adjacent, and "mult v0,a0" is followed by "sra v1,v1,0x1f" (not mfhi). So the mfhi of the second mult (a2) is at 213, well after.

This is a delicate schedule. Reproducing it exactly without the barrier may be impossible... but the task expects a lever-free body; maybe for this item the answer is a WALL. But let me try a few things first.

Let me try these variants:
W1: vol2 = vol copy (extra set).
W2: Move the vol computation to be the last statement before the call, with the pan computed before it (E1, 33 — no).
W3: Change the vol numerator spelling: "vol = ((0xA0 - av) * 0x7F) / 0xA0" → "vol = (av * 0x7F) / 0xA0" hmm not the same. What about "vol = (0xA0 - av) * 0x7F / 0xA0" (same). Or "vol = ((0xA0 - av) * 127) / 160" — same value, different literal spelling! The magic computation might differ? No, same.

Hmm, but wait: the target's numerator is "160 - av" (li v0,160; subu v0,v0,a1). My source says "(0xA0 - av) * 0x7F" — the compiler computed 160-av as "li 160; subu" (constant minus variable → subu v0,v0,a1). Same.

W4: Since the target's `sx` is in a2 and mine in a3, maybe the register difference is what causes the chain order. The register difference arises from local-alloc's qty ordering. What if I make the *pan* result use a different variable so that a2 is free for sx? E.g. currently sx holds both the pan and (later) the shifted value. The target: sx in a2, pan result in a2 (reused), pan<<8 in a2.

In mine: sx in a3, pan result in a3. So the same structure, just a3 vs a2. The difference: local-alloc gave the block-local temps a3 instead of a2. The other block-local temp in that area is v0/v1.

Hmm, in the target, a2 holds sx — a2 is a *saved* register ($6 = s2?) no: a0=$4, a1=$5, a2=$6, a3=$7. These are all caller-saved arg registers. local-alloc assigns temps to $2-$7 (v0,v1,a0,a1,a2,a3) in some order.

In the target: sx → a2 ($6); the magic constant → a0 ($4)!; av → a1 ($5, pinned); vol result → a1 ($5); pan result → a2 ($6).

Hmm interesting: the magic constant is in a0 ($4) in the target, but in a2 ($6) in mine. And in the target a0 is free after the call arg (a0 = 2715 at 221).

So local-alloc's qty assignment differs. In the target, the magic (a0) has the LOWEST priority (a0 is the first caller-saved temp?), then a1 (av, pinned), a2 (sx).

In mine: magic in a2, sx in a3.

So the local-alloc order differs: target: a0=magic, a1=av(pinned), a2=sx; mine: a1=av(pinned), a2=magic, a3=sx.

The magic's position: in the target it's the FIRST (a0) — i.e. the magic pseudo has the highest qty priority (allocated first). In mine it's second (a2).

Why? The magic (match_scratch) is a pseudo with a short live range but many refs? In the target, the magic is used by both mults; in mine, also both. Hmm, but the *order* of the mults affects the live range: in the target, the magic's live range spans from 198 to 208 (covering both mults) — one contiguous range. In mine, the magic (a2) is defined at 198 and used at 201 and 207 — also contiguous.

Hmm, the difference could be that in mine the magic's live range is longer/shorter.

This is getting deep. Let me consider: maybe the whole thing hinges on the ORDER of the two divisions in the source, and the "9 spellings" in the comment were all "vol first" variants. My E1 (pan first) gave 33 — let me look at E1's dump to see if the order flipped. That would tell me whether the source order controls the chain order at all.

Let me regenerate E1 (cand.c) and dump it. I have the sed command. Then dump the candidate object.

Actually, let me be smarter: let me try a batch of variants and dump only the interesting ones.

Given the time budget, maybe I should consider that item 1 might be a WALL and move on to the other 7 items (which may be easier), then come back.

Let me look at the other items' launders first to see if some are trivially fixable (e.g. the "real 2nd set" pattern). Let me look at each item's src def and the launder line.

Let me grep the launder lines in each of the 7 remaining TUs. Efficient: for each item, find the function and the launder.

Let me do that now — it may reveal easy wins, and I can come back to item 1.
