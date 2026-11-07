---
ts: 2026-11-06T05:16:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WDgVvNntl39wNwSpB766
---
So the pattern: `s16 t; t = (s16)v0; v1 = t;` keeps a copy. The HImode copy escapes cse's equivalence class.

In our case, we need raw and t (SI) copies. Apply the same idea:

```c
s16 tmp;
...
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) {...}
tmp = (s16)t;    // HImode copy of t
raw = tmp;       // raw = tmp  → move v1,v0?
t = raw;         // ?
```

Hmm, but we need TWO moves: move v1,v0 then move v0,v1. If we do `tmp = (s16)t; raw = tmp; t = raw;` — that adds a temp and possibly extra instructions.

Wait, actually maybe simpler: the target's structure could be produced with:
```c
raw = t;   // with raw being a separate variable that cse won't merge
t = raw;
```

Let's use the s16 trick on the *second* copy: 
```c
raw = t;          // move v1,v0 (raw gets t's reg?)
...
t = (s16)raw;     // HImode copy escapes → move v0,v1
```
But if raw and t were merged by cse at `raw = t`, then t = (s16)raw is trivial and combine folds.

The key is to break equivalence at `raw = t`. Use a temp:
```c
s16 tmp;
tmp = (s16)t;   // HImode copy: t → tmp
raw = tmp;      // raw = tmp (SI copy of HImode-extended value?)
t = raw;
```
Hmm that's 3 copies.

Alternatively, maybe the target really doesn't have raw/t as I think. Let me reconsider: maybe `raw` is `u8` and `t` is s32, and the copies are:
- insn 38: raw(QI) = subreg(t) — QI copy
- insn 40: t = zero_extend(raw) — SI conversion

In the target asm: move v1,v0 then move v0,v1. That's exactly a QI copy then a zero_extend. But cse folded the zero_extend because it knew t was already the zero-extended value.

What if t is *not* provably equal? E.g., if t could be negative? No, it's guarded.

What if instead of `if (t < 0) return;` we use `if (t >= 0) { ... }`? Same.

Hmm what if we make the compare on `raw` instead: `if ((s32)raw - 0x10 < 0)`. Then t = raw - 0x10... same.

Let me think about the *cse2* mechanism from the example: "the HImode copy escapes cse's equivalence class". In that example, `t = (s16)v0; v1 = t;` — the s16 temp breaks the equivalence between v0 and v1. Here we want to break raw ≡ t.

Try:
```c
u8 raw;
s32 t;
s16 tmp;
...
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) { ... }
tmp = (s16)t;    // copy t into s16 temp
raw = tmp;       // raw = tmp
t = raw;         // t = raw
```
That's potentially 2-3 moves. Too many.

Alternatively maybe only ONE of the moves matters for the score: recall the diff says mine 46 vs target 47, and there are "insert target[11:15]" (move v1,v0 + jal + move a0,s0 + j) and "replace mine[12:16] target[16:17]" (mine jal,nop,j,nop vs target move v0,v1). The COUNT score 12 counts differences. We need the exact target.

Let's think about the register allocation too: target has p in a0, raw in v1, t in v0. If raw and t are separate pseudos and both live, local-alloc: which gets $2 first? Probably t (defined later? or higher ref count). In the example above, v0 got the original, v1 the copy.

Actually here's an idea: maybe the source is:

```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) { call; return; }
raw = (u8)t;      // truncate to u8
t = (s32)raw;     // zero-extend
```

We tried u8 raw. Let me try explicit casts without declaring raw u8 (raw stays s32):
```c
raw = t;
t = (u8)raw;
```
Hmm, `t = (u8)raw` where raw is s32: zero_extend of subreg. If raw = t (SI), cse equates raw ≡ t, then (u8)raw → (u8)t, and since t ∈ [0,0xEF], combine folds to t. Gone.

The key question: how to prevent cse from equating raw and t at `raw = t`?

Use a QI/HI intermediate:
```c
u8 tmp;
tmp = (u8)t;     // QI copy of t
raw = tmp;       // SI zero-extend of tmp
t = raw;
```
Then: tmp = QI(t) [move], raw = zero_extend(tmp) [move], t = raw [merged]. That's 2 moves: move v?,v0 and move v?,v?.

Actually in RTL: `tmp:QI = subreg(t)`, `raw:SI = zero_extend(tmp)`, `t = raw`. If cse can't equate raw with t (because of the QI hop), we get 2 moves. That's promising! Registers: t in v0, tmp maybe v1, raw maybe v1 (after tmp dies). The target has move v1,v0 then move v0,v1: tmp/raw in v1, t in v0. 

So the body:
```c
raw = *(u8*)((u8*)s1 + 0x24);
t = raw - 0x10;
if (t < 0) { ... return; }
tmp = (u8)t;
raw = tmp;
t = raw;
```
Hmm, but then `raw = tmp` is zero-extend and `t = raw` copy. Let's just try variants. Let me create several candidates and score them in one batch.

Candidates:
n3: u8 tmp; tmp = (u8)t; raw = tmp; t = raw;
n4: s16 tmp; tmp = (s16)t; raw = tmp; t = raw;
n5: raw = t; t = (u8)raw;  (explicit)
n6: u8 tmp; raw = t; t = tmp = raw;? 
n7: s16 tmp; raw = (s16)t; t = raw;

Let me think about n4: `tmp = (s16)t; raw = tmp; t = raw;` — tmp HI, raw SI, t SI. That's 3 copies, likely 3 moves.

Better: only need 2 moves. Target: move v1,v0 (raw=t) and move v0,v1 (t=raw). With the QI hop: tmp=QI(t) is move (1), raw=tmp is zero_extend→move (2), t=raw merges (0). Total 2 moves. Register: t v0; tmp and raw coalesce into v1. Target: raw v1, t v0. The first move's dest v1, second move's dest v0. Yes matches!

But would the QI zero_extend be a separate move or fold? `raw = tmp` where tmp is u8 → zero_extend; combine may convert zero_extend of a QI pseudo into... it needs an andi unless it knows. But raw's value = t known in range; hmm, but raw is u8-typed? If raw is s32 and tmp is u8, raw = tmp requires zero_extend → could emit andi 0xff. That would be wrong (extra insn). Unless combine can prove range.

Alternatively declare raw as u8 too: `u8 raw, tmp;` then `raw = tmp` is a QI copy (move), `t = raw` is zero_extend of u8 → might add andi.

Hmm. In the n2 RTL, we saw:
- insn 38: raw(QI 75) = subreg(t 76)  [movqi]
- insn 40: t(SI 76) = zero_extend(raw QI 75)  [zero_extendqisi2]

and cse folded insn 40 to nothing (t unchanged) and kept insn 38, then insn 43 = subreg(t) for the store value, coalesced with t.

So in n2, the QI copy raw=t survived RTL but got coalesced at allocation (raw dead after). Actually insn 38 was `raw = subreg(t)`; raw is used only by insn 40. After insn 40 is optimized away, raw is dead → insn 38 dead → deleted? But final asm... let me check the final asm for n2 to see. Score 46 = no moves.

Actually from lreg dump: insn 43 sets reg79 = subreg(t) and stores use reg79. reg79 was coalesced with t. And raw(75) is gone.

So cse merged raw and t via the zero_extend (insn 40 deleted as redundant). We need the zero_extend to NOT be deleted. It was deleted because cse knew t == zero_extend(subreg(t)).

So the QI hop from t to tmp then raw doesn't help either if cse propagates.

Hmm, what made func_8017E204 work: `t = (s16)v0; v1 = t;` where v0 and v1 are both SI. The HImode copy `t = (s16)v0` is a sign_extend, and `v1 = t` is a copy. cse couldn't equate v0 and v1 because t is HImode (different mode, so reg_eqv classes differ). The copy v1 = t stays because t is a different pseudo (HImode) — cse doesn't track cross-mode equality.

Apply to us: we want raw and t to stay separate. Do:
```c
s16 tmp;
tmp = (s16)t;   // HImode copy of t
raw = tmp;      // raw = (s32)tmp  — sign_extend
t = raw;
```
Hmm, same cross-mode issue: `raw = tmp` sign-extends tmp; cse tracks raw ≡ tmp? No, modes differ (raw SI, tmp HI). Then t = raw: t SI = raw SI → cse equates t with raw! Then t and raw merge (both SI), and the stores use either. Hmm, but then `raw = tmp` remains as a real move into raw's reg, and `t = raw` merges. That gives ONE move (raw = tmp). Plus tmp = (s16)t gives another move (tmp = t). So 2 moves: tmp←t and raw←tmp. Registers: t v0, tmp v1, raw v1 (coalesced). The moves: move v1,v0 (tmp=t), move v1,v1? No — if raw and tmp coalesce, raw=tmp is the same register, so the copy is deleted (move v1,v1). Hmm, that gives only 1 move.

Unless raw doesn't coalesce with tmp because raw = sign_extend(tmp) needs a separate... no, sign-extend from HI in the same reg is just a copy.

This is getting complicated. Let me think about what instruction sequence we need exactly:

```
lbu v1,36(s1)      raw = load
lw a0,76(s0)       p = load
addiu v0,v1,-16    t = raw - 16
bgez v0, L
move v1,v0         raw = t
jal ...
move v0,v1         t = raw
sb v0,38(s1)
```

The last two: `move v1,v0` then `move v0,v1`. Semantically a round trip. Two different registers. In plain C, gcc will always collapse a round-trip copy. UNLESS the two variables have different modes or one has a constraint.

So realistically: raw and t must have different modes such that the round trip isn't collapse-able. E.g.:
- raw: QI (u8)
- t: SI

Then:
- raw = load (lbu) → raw in QI.
- t = raw - 16: zero_extend raw, addiu.
- raw = t: QI copy (truncate) — move v1,v0.
- t = raw: zero_extend — move v0,v1.

The problem: cse deletes the zero_extend since t is known equal. But is it known? t = raw - 16, raw ∈ [0,255] so t ∈ [-16,239]; guarded t ≥ 0 so t ∈ [0,239]. Then (u8)t == t, and zero_extend(t) == t. GCC's cse uses REG_EQUAL / equivalence; combine's nonzero_bits. It figured it out.

Can we defeat it? Use `u8 raw` but make the range not provable: e.g., raw = load; t = raw - 16; if (t < 0) ... The guard is what gives the range. If the guard were `if (raw < 0x10) return;` instead — same range info.

What if the compare is on a *different* expression so gcc doesn't propagate the range to t? E.g.:

```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (raw < 0x10) { call; return; }   // compare raw, not t
raw = t;
t = raw;
```
Then t = raw-16 is known ≥ 0 only if raw ≥ 16 (from the branch). GCC might still track. Hmm, but the compare instruction would be on raw: target has bgez v0 where v0 = t. If we compare raw, the asm would be slti/bge. Not matching.

Alternative: break cse with a do-while(0) around something? C0535 says do{}while(0) splits cse1 EBB. If we split the EBB between `raw = t` and `t = raw`, cse might not merge them! Wait, cse processes extended basic blocks; a NOTE_INSN_BLOCK boundary (from do-while) splits the ebb so cse's equivalence table is flushed. Then `raw = t` and `t = raw` are in different ebbs → the second copy isn't known equal.

Hmm! That's C0535: "do{}while(0) splits cse1 EBB; cracked a sched1-birth-order item". Let's try:

```c
raw = t;
do { } while (0);   // !FAKE: do-while
t = raw;
```
But wait, a do-while(0) around a *statement*: `do { t = raw; } while (0);` splits the block. Does cse flush its table at block boundaries? In gcc 2.7.2 cse.c, `NOTE_INSN_BLOCK_BEG/END` may call `invalidate_from`? Actually cse's `cse_insn` handles notes: `case NOTE_INSN_EH_REGION_BEG...`; but for basic block boundaries, cse is run per extended basic block and flushes at `NOTE_INSN_LOOP_BEG` etc.? The moves.md says do-while(0) splits cse1 EBB — evidenced.

But careful: the do-while around `t = raw` — the empty loop body. The loop notes... gcc may mark it as a loop (NOTE_INSN_LOOP_BEG) — but for `do { } while (0)`, loop.c probably removes it. And the body with one statement.

Let's just try. Also alternative: put the two copies in separate do-while blocks.

Also we must keep raw alive. Actually, the real problem is also that raw is dead after `t = raw`. If cse can't equate them, `raw = t` is a real move and `t = raw` a real move.

Let's test candidates:
- n3: do-while split: `raw = t; do { t = raw; } while (0);`
- n4: `do { raw = t; } while (0); t = raw;`
- n5: both in separate do-whiles.

Hmm, but note: with the *pins* the launder is `__asm__("" : "=r"(raw) : "0"(raw))` between `raw = t` and `t = raw`. Its effect: makes raw a new value, so t = raw is a copy. The equivalent lever-free mechanism could be the do-while EBB split.

Let's test a batch. I'll write n3-n6 and use sc.sh.

Also consider: register allocation. Target raw v1, t v0. Without pins, which pseudo gets v0? In n1, raw/t merged into one pseudo in v0 and p got v1. If we now have raw and t separate: t is used by the bgez and stores (more refs) → t likely gets v0. raw gets v1. p gets a0? p is live from lw at insn 8 (scheduled) but allocated: p used only after; local-alloc might give p a0 if a0 is free. Let's see.

Let me write the candidates.
