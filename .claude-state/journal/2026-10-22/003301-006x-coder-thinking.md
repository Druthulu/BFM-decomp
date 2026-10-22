---
ts: 2026-10-22T06:33:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_fYKhzmXaZ2nnndqVR6HP
---
Item 3: func_8018FB5C, kinds=launder. The lever here is the launder on `rgb` — `__asm__("" : "=r"(rgb) : "0"(rgb))` which is a zero-byte 2nd SET that kills the sched1 birthing boost.

So the lever-free replacement: give rgb a real 2nd set. Options from moves.md: "real 2nd SET" via compound assign, e.g. `rgb = rgb;`? no that's identity. From G11: "pv &= 0xFF000000 (compound assign) = a REAL 2nd SET of the pinned pv, kills the sched1 birth boost". Also `u16`/`s16` cast: "v = (s16)v;" — but that's an identity if v is already s16. Here rgb is s32 and arg2 is s32. A cast `rgb = (u16)rgb` would change value. But the store `*(s32 *)(...+4) = rgb` — in the target, what value? Since the target's asm ties rgb to rgb, the value is unchanged. But we need the compiled code to be identical, so we can't truncate.

Hmm. But wait — `rgb = arg2;` then a second set. What about `rgb = arg2 | 0;`? That's a combine-folded identity — but does it count as a "real 2nd SET"? The lever here isn't a launder in the sense of the constraint "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". Hmm, that's about laundering to fake a crack.

Actually here we need to REMOVE the launder, i.e., produce a body that scores 0 without the asm. The asm's purpose: creates a second set of rgb, which kills sched1's birthing boost so that the load `*(u32*)temp_v0` (tag0) ordering works out.

So we need a plain C way to give rgb two sets. Options:
- `rgb = arg2;` ... then `rgb = rgb + 0;` — folded by combine → no 2nd set.
- Use a s16/u16 temp? changes value.
- Reassign rgb from a different source: e.g. `rgb = arg2;` then later `rgb = arg2;` again → two sets of the same value! But gcc's cse would merge two identical assignments of arg2 into one set... Actually gcc would likely CSE `rgb = arg2` twice into one. Hmm, but cse does merge. But the mov notes said "the plain copy t = v is dissolved by cse/combine".

Alternatively: `rgb = arg2;` and then read it via a different expression. Actually the store `*(s32*)(temp_v0+4) = rgb` is the only use. In the target, the order is: `addiu a1,zero,0x10; jal func_80010A08` then store 3, then store rgb.

Actually maybe simpler: don't introduce a variable at all: `*(s32 *)((u8 *)temp_v0 + 4) = arg2;` — then the value comes directly from a2 (arg2 in $a2). But arg2 is arg... Hmm but the target has `rgb` with pin $4 — wait, `register u32 tag0 __asm__("$4")` and `register s32 rgb __asm__("$16")`. rgb is pinned to $16! So rgb lives in $16 (s0) and tag0 in $4 (a0). The pin is a lever of kind "pin", but the row kind is "launder" — pins under other causes may stay. Actually wait, are the pins part of the row kinds? kinds=launder only. The constraint says: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added". So the existing pins may stay! Great — that simplifies: I keep `register s32 rgb __asm__("$16")` and `register u32 tag0 __asm__("$4")`, and remove only the launder asm.

But hold on: the launder is on rgb: `__asm__("" : "=r"(rgb) : "0"(rgb));` after `rgb = arg2;`. Removing it gives rgb one set (arg2), which regains the sched1 birthing boost → different code.

Hmm, but note the pin is on a variable, and the launder is "zero-byte 2nd SET: kills the sched1 birthing boost". With the pin to $16, does sched1's birthing boost still matter? The launder asm adds an extra set of rgb, so rgb has 2 defs. Without it, 1 def → sched1 boosts it.

Alternative lever-free real 2nd set: since rgb is pinned to $16 as s32, maybe `rgb = arg2;` then `rgb = rgb;`? cse would fold. Or use a compound assign with a zero: `rgb += 0;` → combine folds.

What about `rgb = arg2;` followed by `rgb = (s32)(u32)rgb;`? That's identity but a cast — combine may fold (nonzero_bits). Hmm.

Actually the moves.md G14 entry: "the 12 launders on v -> six 'v = (s16)v;' real 2nd sets (v is a sign-extended s16, so the cast is a no-op)". So a self-assignment cast to a narrower type is a "real 2nd set" that preserves value when the value fits. Here rgb = arg2, s32. If we cast to s16, the value changes (upper bits lost) — the store would store the truncated value, differing semantically from target... but the compiled output is what matters for scoring? No — scoring compares compiled instructions against target. The target stores the full s32. If we truncate, the code will differ (extra sign-extension instructions). Unless... the target's store is of the full arg2.

Hmm, what about a cast that is a no-op: `rgb = (s32)(s16)...` no.

What about declaring rgb as u32 instead of s32 and doing `rgb = arg2;`? The value is the same bits. A cast `(u32)rgb` is a no-op in gcc (same mode). Self-assign `rgb = (u32)rgb;` might be folded by combine (copy propagation). Actually the point in G14 was that (s16)v creates a *different mode* (HI mode) copy, so it isn't a plain copy → survives cse as a real set. That requires the value to fit in s16 semantics.

Here we need value-preserving. rgb = arg2 (s32). What is arg2's actual range? Unknown.

Alternative: two sets via different expressions:
```
rgb = arg2;
...
rgb = arg2;   /* again */
```
Does gcc's cse merge them? cse would find both are copies of arg2 → they'd be merged into one pseudo. Likely yes (cse phase 1/2 handles copies).

Alternative approach: since the asm ties rgb's output to input, it's a no-op except for adding a set. Perhaps the equivalent plain-C: assign rgb from a temp that itself is assigned twice. E.g.

```
s32 rgb2 = arg2;
rgb = rgb2;
```
That's still 1 set for rgb.

Hmm. Another angle: maybe we don't need a second set at all — maybe the difference the launder causes can be achieved another way. Let me first just try: remove the asm and score it. Maybe the score is 0 anyway (maybe the launder is not needed in this function; the "NEEDED DIFFERS" comment is a generic marker). Let's just test.

Let me check how dt.sh works and what a score means. Let's just try.

First: create orig.c from the src def. The brief says: copy the current def in src to <dir>/orig.c. Note orig.c for the completed item has a "bare definition" body (no includes). The body passed to delever_search --body is a full function definition text.

Let me look at the delever_search tool briefly to understand --body format.

Actually the win.c from func_80181F4C shows format: a bare function definition with extern decls inside.

Let me create the item dir files and try.

Plan for item 3:
- orig.c = the src function body (as bare definition, including the extern decls and pins).
- cand01.c = same but with the launder asm removed.

Let me write these files. First let me check the exact def text and copy it precisely.

The def spans lines 11235-11283. Let me extract with sed into orig.c and then edit.

Note the type declarations used: OtBlk_80182890_8018FB5C — is that defined in the TU? The extern decl `extern OtBlk_80182890_8018FB5C D_800A651C_v[] __asm__("D_800A651C");` refers to a struct type. When compiled as a standalone body, is the type available? delever_search --body probably injects the body into the TU, so types are available. Let's check how it works.

Let me look at tools/delever_search.py usage quickly (just the --body handling).
