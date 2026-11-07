---
ts: 2026-11-06T05:12:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PHNKA1N0wA8Si9OhZSwB
---
Now the target:

```
4d8 lbu v1,36(s1)     raw -> v1
4dc lw a0,76(s0)      p -> a0
4e0 addiu v0,v1,-16   t -> v0
4e4 bgez v0, 4fc      if (t >= 0) goto 4fc
4e8 move v1,v0        raw = t (delay slot!)
4ec jal func_80146CA0
4f0 move a0,s0
4f4 j 560             return
4f8 nop
4fc move v0,v1        t = raw
500 sb v0,38(s1)      *(s1+0x26) = t
504 sb v0,37(s1)      *(s1+0x25) = t
508 sb v0,36(s1)      *(s1+0x24) = t
```

Interesting: the store order in target is +0x26, +0x25, +0x24 (reverse of the chained assignment, which writes 0x24 first? Actually the chain `a = b = c = t` evaluates c first then b then a, so the stores are 0x26, 0x25, 0x24 — right, matches).

So the target needs:
- raw in v1, t in v0, p in a0.
- `move v1,v0` in the bgez delay slot.
- `move v0,v1` after.

So semantically: raw and t are distinct registers, both copies present. The `raw = t; t = raw;` pair. But note: `raw` is not used after `t = raw` — raw is dead! So `raw = t` is dead unless it's in the delay slot (scheduled). And `t = raw` is a copy.

Hmm, in plain C without pins, gcc's cse will equate raw and t after `raw = t`. Then `t = raw` becomes `t = t` (deleted). So we lose both.

How did the original avoid this? The launder (`__asm__("" : "=r"(raw) : "0"(raw))`) makes raw a new value, breaking the equivalence. Then `t = raw` is a real copy from the laundered raw.

Lever-free: we need a real 2nd set of raw (like the moves catalog: `pv &= 0xFF000000` real 2nd set). But here `raw = t` IS a real 2nd set... but cse merges because they're equal. A "real 2nd set" that makes raw ≠ t: e.g. `raw = t + 0;`? combine folds. `raw = t | 0`? folds.

What about a genuine value-preserving transformation that gcc can't fold at cse stage? Ideas from catalog:
- `do { } while (0)` doesn't create a value.
- HImode copy: if raw is `u8`/`s16`, then `raw = t` is a QImode/HImode subreg set, which cse treats differently (a SUBREG copy escapes the equivalence class sometimes). moves.md line 202: "u16 i; u16 j: the HImode copies of arg0/arg1 escape cse, so the target's opaque $a3/$t0 parameter copies survive". And line 147: "the copy through an s16 temp escapes cse2's equivalence class".

So: declare raw as `u8` (or s16). Then:
- `raw = *(u8*)(s1+0x24)` — lbu into QImode raw.
- `t = raw - 0x10` — t s32; raw zero-extended.
- `raw = t` — QImode set (subreg).
- `t = raw` — zero-extend.

Would cse equate raw(QI) and t(SI)? cse's make_regs_eqv is per-mode? Actually cse uses `reg_eqv` tables by mode; SUBREG handling. Hmm.

But there's a subtlety: if raw is u8, then `t = raw - 0x10` requires the u8 in a register; lbu gives that. And `raw = t` truncates to u8. Then `t = raw` zero-extends. If gcc knows t ≥ 0 and ≤ 0xFF... `t = raw - 0x10` with raw ≤ 0xFF, and after the if t ≥ 0, so t ∈ [0, 0xEF], so truncation to u8 is exact and zero-extension is exact. So moves only. 

Register allocation: raw is live from lbu to `t = raw`. t live from addiu to stores. p loaded at 4dc and used much later. Hmm, would p get a0? p is used at `lw v0,32(a0)` (4fc... wait 50c: lw v0,32(a0)). p lives across the first call — so it's in a0 (caller-saved)?? a0 is not callee-saved! p is used after the first call... wait no: at 4fc-508 the stores, then 50c `lw v0,32(a0)` uses p. But the first call (jal at 4ec) is only on the t<0 path which returns, so p is dead on that path. gcc doesn't know... it does: on the return path p isn't used. So p can be in a0 because the call path doesn't continue. OK.

So p in a0 is natural if raw is v1 and t v0? Hmm, in mine p got v1 because raw/t merged to v0.

Let's think: what determines v0 vs v1 for t and raw? local-alloc qty priorities. With raw and t separate pseudos: raw = lbu (QI), t = addiu. Both live in the entry block. local-alloc assigns $2 (v0) first to... the one with higher priority. In target raw got v1 and t got v0.

Let's just try the u8 raw variant and see.

Actually wait — a subtlety: with raw as u8, the source `raw = t;` where t is s32 — assignment to u8. And then `t = raw`. Let's try.

Also there's the question of whether the u8 conversion adds an andi. Let's test.

Let me write n2.c.
