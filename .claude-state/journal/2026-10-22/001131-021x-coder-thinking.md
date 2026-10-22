---
ts: 2026-10-22T06:11:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_xprEbYOnXmTmxgoGYhvL
---
VERY interesting! Look at the "plain" (r_plain_s0) diff:

```
135  bne a3,v0,cb0 | bne a2,v0,cb4
136  sll a3,a3,0x8 | sll a2,a2,0x8
137  li a3,15      | li a2,15
138  sll a3,a3,0x8 | sll a2,a2,0x8
```

The PLAIN body (no launder at all) has EXACTLY the target's delay-slot structure! `bne; sll(delay); li 15; sll`! The only difference is the register: a3 vs a2!

So in the plain body, the sll IS in the delay slot. The problem with the plain body is the multiply order (the pan multiply hoisted ahead) and the register allocation (a3 vs a2).

And with the u16 cast, the andi took the delay slot instead.

So: the u16 cast (which fixes the multiply order) breaks the delay slot.

Hmm! So what if I find a 2nd-set spelling that fixes the multiply order WITHOUT introducing an andi?

The plain body's problems:
1. Multiply order: mine has `mult v1,a2` (the pan multiply with the magic in a2) at 126 vs the target's `mult v1,a0` (the vol multiply with the magic in a0). So the magic constant ended up in a2 and the pan multiply came first.
2. The register a3 vs a2 for sx.

The u16 cast fixed #1 (the magic in a0, the vol mult first) but introduced the andi.

Alternative 2nd-set spellings to try:
- `vol = (u16)vol;` → andi (current best, 2)
- `vol = (u8)vol;` → andi 0xff — different immediate! Maybe the scheduler treats it differently. But semantically riskier (still fine under the guard). Hmm.
- A 2nd set with NO instruction: e.g., `vol = vol;` (cse removes it, probably no 2nd set), or `if (vol) ;`? Hmm.
- `vol += 0;` → combine folds.
- `vol = vol ^ 0;` → folds.
- A do-while (no instruction) → 25, but it doesn't fix the multiply order fully? The do-while diff shows the pan multiply is still hoisted (the diff at 124-134 shows the same reordering as the plain version, roughly). Actually the do-while's diff shows a slightly different arrangement. The do-while's residual is big (25) mostly due to the multiply order and other stuff.

Hmm. Interesting: the do-while diff shows `mfhi t1 / addiu v0,a2,160 / nop / mult v0,a0` in the target at 124-127 but the do-while body has `mfhi t0` etc. So the do-while body still has the pan multiply first.

So the u16 cast is what fixed the order. Why? Because the u16 cast creates a 2nd set of vol, and... hmm, the ORDER of the two multiplies.

Wait, actually let me look at the plain body's code more carefully. In the plain body:
```
126: mult v1,a2     ; a2 = the magic constant
127: sra a0,a0,0x1f
128: sra v0,a3,0x3
129: subu a3,v0,a0
```
vs the target:
```
c70: mult v1,a0    ; a0 = the magic
c74: mfhi t1
c78: addiu v0,a2,160
c80: mult v0,a0
```
So in the plain body, the magic constant is in a2 and it's the PAN multiply that uses it (mult v1,a2 = the pan chain's multiply). And the vol multiply comes later with the magic in a0? Let me dump the plain body's full region to see.

The key issue: in the plain body, sched1 hoists the pan multiply (mult v1,a2) ahead of the vol multiply. The magic constant (0x66666667) gets duplicated into two registers (a0 and a2) — one for each multiply. In the target, there's only ONE magic constant (a0) and both multiplies use it: `mult v1,a0` (vol) then `mult v0,a0` (pan). So in the target, the two multiplies share the magic register — which means the vol multiply comes FIRST (it defines a0) and the pan multiply reuses it.

In the plain body, the pan multiply comes first and gets its own magic copy in a2, and the vol multiply uses a0.

So the difference is the ORDER of the two multiplies, and the sharing of the magic.

The u16 cast fixed this. Why? Because the u16 cast is a 2nd set of vol AFTER the vol computation; the 2nd set means vol's value is "re-defined", and the scheduler's dependency structure changes so that the vol multiply chain (which feeds the u16 cast) is scheduled first.

Hmm OK. So the u16 cast is load-bearing for the order. It also adds the andi.

Now: is there another way to get a 2nd set of vol (or otherwise order the multiplies) that doesn't add an andi?

Option: put the 2nd set on a DIFFERENT variable, e.g. `sx = (u16)sx;`? That adds an andi on a2 (or wherever sx is). Hmm, but sx's 2nd set might change the order differently. But the cast on sx is not value-preserving either (sx = (sx+0xA0)/0x14 ∈ [0, ~2290] for sx ∈ [-160, 32767]... wait sx here = (s16)sxy[0] ∈ [-32768,32767], (sx+0xA0)/0x14 could be up to (32767+160)/20 = 1646 — fits in u16. And could be negative: (-32768+160)/20 = -1630 → (u16) cast changes it! So (u16)sx is not value-preserving in general. But the guard bounds sxy[0] to [-159,159] → sx ∈ [-159,159] → (sx+160)/20 ∈ [0, 15]. So under the guard it's fine, but the compiler doesn't know.

Hmm, actually, does it matter? The C I write must be equivalent to the ROM's behavior for all inputs the function can receive. The guard is inside the function, so the values are bounded. The "value-preserving" concern is about the *emitted code* being correct for the reachable inputs. Since the guard guarantees the bound, a (u16) cast on sx is fine semantically. But the decomp project may care about faithfulness. The other G14 items used (s16)/(u16) casts justified by the value range. I'll note the reasoning.

But more importantly: does a 2nd set on sx fix the multiply order? Probably not — the issue is the vol chain vs the pan chain ordering.

Option: a 2nd set of vol that is a no-op instruction-wise. What operations are no-ops in codegen but create a 2nd set?
- `vol = vol;` → cse/copy-propagation removes it. But wait! In this project, other items found that "a real 2nd set" is what matters. `vol = vol;` would be folded by combine (it's a copy of itself → the pseudo is the same). So no.
- `do { } while (0);` → the do-while creates a barrier but no 2nd set. Score 25 (doesn't fix the order).
- A cast to a wider type: `vol = (s64)vol;` → 2 instructions (sign extension) - worse.
- `vol = (u16)vol;` → 1 andi.

Hmm, so the u16 cast is the only 1-instruction 2nd set.

BUT: what if the andi doesn't land in the delay slot? The delay-slot choice is made by the final pass. In the u16 body, the andi landed in the bne's delay slot. In the plain body, the sll landed there.

What if I could make the sll be scheduled/duplicated AND keep the u16 cast? The u16 cast's andi competes.

Hmm, what if the u16 cast is applied to a value that's not live across the branch? E.g., cast the *pan* result instead of vol: `sx = (u16)sx;`? Hmm.

Wait, actually — let me reconsider. Maybe the ordering fix doesn't need a 2nd set of vol at all. What if I change the ORDER of the source statements so that the pan chain comes after the vol chain? The source currently is:

```
sx = (s16)L.sxy[0];
av = sx;
if (sx < 0) { av = -sx; }
vol = ((0xA0 - av) * 0x7F) / 0xA0;
[launder]
sx = (sx + 0xA0) / 0x14;
...
```
So the vol computation is before the pan chain in the source. The plain body still schedules the pan multiply first. So the scheduler reorders.

What if the source had the pan chain first and vol after? Then... the scheduler might still reorder. But it's worth trying: the multiply order in the target is vol-first, matching the source order. Since sched1 (the pre-RA scheduler) does the reordering, maybe the source order matters for which one it picks.

Hmm, in the plain body, the pan multiply was hoisted ahead. The comment in the src says exactly that: "sched1 otherwise hoists the PAN multiply ahead of this one".

So what makes the difference? In the target, the vol multiply is FIRST. The launder asm (in orig.c) prevented the pan multiply from being hoisted. Why? Because the asm is an opaque barrier: after the asm, the value vol is "re-defined" (the asm's output), so the vol chain's result is consumed... hmm.

The u16 cast does the same: vol = (u16)vol re-defines vol.

Hmm, so the "2nd set" is what matters. But it adds an instruction.

Hmm, but WAIT: what if the 2nd set is on `av` instead of `vol`? av is the |X| value. `av = (u16)av;` — that would add an andi on av's register. But would it fix the order? The mechanism (a 2nd set of vol) is about vol's chain. Hmm.

What about a 2nd set of vol that produces a *different* instruction that lands elsewhere? The andi lands in the delay slot because it's cheap and available.

Hmm, hold on! Let me reconsider: in the u16 body, the andi in the delay slot is `andi a1,a1,0xffff` applied to a1 = vol. What if the andi landed in a different place — e.g., if the vol chain were scheduled later, the andi would be later too.

What if I make the u16 cast happen LATER in the source, e.g. right before the call?
```
vol = ((0xA0 - av) * 0x7F) / 0xA0;
sx = (sx + 0xA0) / 0x14;
if (sx == 0x10) { sx = 0xF; }
sx = sx << 8;
vol = (u16)vol;
func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
Hmm! But then the u16 cast is right before the mask — gcc would fold (vol & 0xFFFF) & 0xFFFF = vol & 0xFFFF → the andi would be merged with the final mask into ONE andi. That would give 191 instructions + the sll duplication = 192! And the andi would be at the end (in the jal delay slot) — exactly like the target!

But would the 2nd set still fix the multiply order? The 2nd set of vol is now after the pan chain. Hmm, the 2nd set's position in the source might matter for the scheduling. Let's try!

Also: does the "real 2nd set" need to be right after the vol computation to restore the order? Let's test.

This is a promising variant. Let me also try:
- `vol = (u16)vol;` placed between the vol computation and the pan chain (current, = the u16 body) → 2
- `vol = (u16)vol;` placed after the pan chain (before the call) → new
- `vol = (u16)vol;` placed after the shift but before the call, with the arg in a var.

Let me also consider: the andi at the end would be `(vol|0x3000|sx) & 0xFFFF` — but if vol is already masked to u16, gcc computes ((vol&0xFFFF)|0x3000|sx)&0xFFFF = (vol|0x3000|sx)&0xFFFF (as before). The target has exactly one andi at the end. 

So the plan: move the u16 cast to just before the call. Let me test.

Also worth testing: the u16 cast applied to the ARGUMENT: `func_8002D4C8(0x9E5, (u16)(vol | (0x3000 | sx)));` — that gives one andi at the end (on the whole arg) — and creates a 2nd set of the arg expression, not of vol. Would that fix the multiply order? The 2nd set of vol is what mattered... but maybe a 2nd set anywhere in the vol chain works. Actually, the (u16) cast on the arg doesn't create a 2nd set of vol. Hmm, but it might not be needed: the multiply order issue is about the vol chain's position.

Let me just test a batch:
 t1: vol = (u16)vol right before the call (after the shift).
 t2: vol = (u16)vol after the pan chain, before the shift.
 t3: arg cast: (u16)(vol | (0x3000 | sx)).
 t4: vol = (u16)vol right after the vol computation (current) but with the arg written as (vol | 0x3000 | sx).
 t5: `vol &= 0xFFFF;` compound assign (same as the cast).
 t6: `vol = vol & 0xFFFF;` (explicit and, maybe codegen differs: the andi would be `andi a1,a1,0xffff` — same).

Also: what about casting to u16 but with the cast placed right after the vol computation and ALSO the arg masked — that's the current best (2).

Let me generate these.

Another important variant: the "2nd set" could be on vol but with a *different* type that produces no instruction... e.g. `vol = (u16)(u16)vol;`? Nah.

Let me write the generator for these "t" variants.

Also, let me reconsider the whole approach: maybe there's a cleaner lever-free spelling that reproduces the target exactly. The retail source's structure for the target:

```
   c58: lui a0,0x6666 ; ori a0,a0,0x6667   <- magic in a0, defined BEFORE the vol multiply
   c60: li v0,160
   c64: subu v0,v0,a1
   ...
   c70: mult v1,a0     <- vol multiply uses a0
   c74: mfhi t1
   c78: addiu v0,a2,160  <- pan chain starts
   c80: mult v0,a0
```
So the magic constant is materialized once, before both multiplies. In the plain body, the magic is duplicated (a0 and a2) because the two chains are independent and the scheduler CSE'd them into separate registers (cse does that? no — cse would share them, but the scheduler's "birth boost" and the regalloc assign different regs since they're used at different times).

Hmm, in the target both multiplies use a0. So the magic is a single live value used twice → one register.

In the plain body, the magic is in a2 for the pan multiply and in a0 for the vol multiply (2 copies). cse would have merged them into one pseudo unless the "birth boost" of sched1 duplicated it. Right: moves.md has "sched1-birth-boost" as a known wall mechanism.

The u16 cast fixed this by making vol's chain end with a use that ties the magic's live range.

OK let me just test the variants. Let me write gen_t.py.

Variants (all keep the $5 pin, remove the launder):

t1: vol=(u16)vol moved to just before the call:
```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            sx = sx << 8;
            vol = (u16)vol;
            func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
t2: vol=(u16)vol right after the pan chain, before the shift:
```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            vol = (u16)vol;
            sx = sx << 8;
            func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
t3: arg cast (u16):
```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            sx = sx << 8;
            func_8002D4C8(0x9E5, (u16)(vol | (0x3000 | sx)));
```
t4: `vol = vol & 0xFFFF;` after the vol computation (explicit, same as the cast but maybe the C is different for cse).
t5: `vol = (u16)vol;` after the vol computation + the arg as `(vol | 0x3000 | sx) & 0xFFFF` (left-assoc).
t6: the u16 cast + the shift duplicated in both arms (s2 with u16) = r_u16_s2 = 15. skip.
t7: `vol &= 0xFFFF;` (compound) after the vol computation.
t8: vol = (u16)vol placed between the vol computation and the pan chain (current) but with the arg cast to u16 instead of & 0xFFFF:
```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            vol = (u16)vol;
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            sx = sx << 8;
            func_8002D4C8(0x9E5, (u16)(vol | (0x3000 | sx)));
```
t9: the shift first then the cast:
```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            vol = (u16)vol;
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            func_8002D4C8(0x9E5, (vol | (0x3000 | (sx << 8))) & 0xFFFF);
```
t10: the arg into a var with the u16 cast late:
```
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            sx = sx << 8;
            {
                s32 arg = (vol | (0x3000 | sx)) & 0xFFFF;
                vol = (u16)vol;      /* hmm, dead */
                func_8002D4C8(0x9E5, arg);
            }
```
Hmm, that last one is dead. Skip.

t10 alternative: cast the arg and cast vol:
```
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            sx = sx << 8;
            func_8002D4C8(0x9E5, (u16)((u16)vol | (0x3000 | sx)));
```

Let me also try moving the whole vol computation later in the source (statement order): the pan chain first, then vol. Hmm, the pan chain needs av which needs sx. So the order would be:
```
            sx = (s16)L.sxy[0];
            av = sx;
            if (sx < 0) { av = -sx; }
            sx = (sx + 0xA0) / 0x14;
            if (sx == 0x10) { sx = 0xF; }
            sx = sx << 8;
            vol = ((0xA0 - av) * 0x7F) / 0xA0;
            vol = (u16)vol;
            func_8002D4C8(0x9E5, (vol | (0x3000 | sx)) & 0xFFFF);
```
This is a "statement order" move — allowed ("real C moves: ... statement order").

Let me generate and score all of these.
