---
ts: 2026-11-06T06:29:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_hf0BxMl4aCbzsXPDumW5
---
In w2 (launder kept, pins removed): loop.c still hoisted the div-by-3 magic (`lui s7,0x5555; ori s7,s7,0x5556`) — so the launder does NOT block the const hoist; it blocks the array giv (no s5 pointer here). The register pairs: s4->s6 x1, s6->s7 x1 — arg0 in s6 vs s7 and half in s4 vs s6.

Hmm, w2's structure: no array pointer hoist (good), but the magic const hoisted to s7 (bad).

In the target (both levers), the magic is materialized inside the inner loop.

So: the pins block the array GIV, and something blocks the magic hoist. In w3 (pins kept, launder removed): 106 insns, score 5 — the magic wasn't hoisted there either (since 106 = target count and score 5).

So with the pins: both blocked. With neither: both hoisted.

OK so the pins are doing double duty. Fine.

Now, what plain-C construct blocks both? The goto loop (no LOOP notes) blocks both — but gave 102 insns / 44. Let me look at that diff more carefully; maybe I can fix the goto version.

Actually — hmm, wait. Let me reconsider. With goto loops, loop.c does nothing, so:
- the array address is computed per iteration: `sll v0,s3,2; lui at; addu at,at,v0; lw v0,0(at)` — the target has exactly this! 
- the magic is materialized in the inner loop — the target has this!
- BUT the target also has some loop.c moves: e.g. the target's `move $22,$2` (base = tmp) etc. Hmm.

The goto version gave 102 insns vs target 106. What are the missing 4 insns? From the diff earlier: mine has `addiu sp,sp,-72` (frame 72) vs target 80, and mine uses fewer callee-saved regs. The missing insns are the extra prologue saves (s7) and maybe a `move`.

Wait, in the goto version mine used s6 for arg0 while target uses s7. The difference: the target needs 8 callee-saved regs, mine 7.

Hmm, but also: the target's inner-loop `pos[0] -= hh / 3` uses a div-by-3 with the magic; the target computes `hh` into $16 (s0) and `sign` into $21 (s5).

Let me look at the goto version's full residual to see if it's close. Earlier diff showed lots of reordering in the outer loop body (insns 20-36 heavily reordered) — mine's order differs from target's. That's a scheduling difference caused by the different RTL (no loop.c moves).

Honestly, the goto version's body order differs a lot: e.g. mine `lw v1,0(at); move s2,zero; sll v0,v1,1; addu...` vs target `lw v0,0(at); move s1,zero; sll v1,v0,1; addu...` — those are just register names (v1/v0 swapped), plus the order is the same! Let me re-read:

mine[20:35]:
```
20  lw	v1,0(at)
21  move	s2,zero
22  sll	v0,v1,0x1
23  addu	v0,v0,v1
24  sll	v1,v0,0x9
25  addiu	s5,v1,8192
26  sll	v1,s5,0x10
27  sra	s4,v1,0x12
28  sll	v0,v0,0x1
29  addiu	v0,v0,18
30  lhu	v1,34(sp)
31  sll	s3,v0,0x1
32  sh	v0,32(sp)
33  addiu	v1,v1,-36
34  sh	v1,34(sp)
```
target[21:38]:
```
21  lw	v0,0(at)
22  move	s1,zero
23  sll	v1,v0,0x1
24  addu	v1,v1,v0
25  sll	v0,v1,0x9
26  addiu	v0,v0,8192
27  move	s6,v0
28  sll	v0,v0,0x10
29  sra	s2,v0,0x12
30  sll	v1,v1,0x1
31  addiu	v1,v1,18
32  sll	s4,v1,0x1
33  lhu	v0,34(sp)
34  sra	s5,s4,0x1f
35  sh	v1,32(sp)
36  addiu	v0,v0,-36
37  sh	v0,34(sp)
```
Very close in structure! Mine is missing:
- `move s6,v0` (base = tmp) at 27 — the copy is GONE in mine!
- `sra s5,s4,0x1f` (sign = half>>31) at 34 — moved elsewhere in mine.

So in the goto version, the `base = tmp` copy got coalesced away (since base is just tmp's value used later). In the target the copy survives because... the launder asm! The launder is `__asm__("" : "=r"(tmp) : "0"(tmp))` placed between `base = tmp` and `mod = (tmp<<16)>>18`. Hmm, in the target, `move $22,$2` (base=tmp) then #APP #NO_APP then `sll $2,$2,16`.

So the launder's real role in the target: keep the `base = tmp` copy (base in a different reg). Without it, cse/combine merges base with tmp.

Wait, but in the target, base is $22 (s6) and tmp is $2 (v0). The copy is a real `move $22,$2`. In mine (goto), base and tmp are the same pseudo → no move, and `addiu s5,v1,8192` uses v1 directly.

So: I need `base = tmp` to survive as a copy. That's a "cse-copy-merge" wall. Plain C: make base a different value, e.g., `base = u * 0x600 + 0x2000;` computed independently of tmp? That would compute it twice (2 insns).

Hmm, in the target: tmp = u*0x600+0x2000 (computed once), base = tmp (copy), then the launder, then mod = (tmp<<16)>>18.

What if I write `base = u * 0x600 + 0x2000; tmp = base; mod = (tmp << 16) >> 18;`? Then base is computed first and tmp is the copy — the target has the copy INTO base (move $22,$2 where $2=tmp). Hmm, the direction matters for which pseudo survives.

In the target: `sll $2,$2,9; addiu $2,$2,8192` — tmp computed in $2; `move $22,$2` — base = tmp. So base is a copy of tmp, and base is used later (`addu $16,$22,$16`).

Plain C: `tmp = u * 0x600 + 0x2000; base = tmp; mod = (tmp << 16) >> 18;` — exactly what we have. cse merges base and tmp (copy propagation), so base becomes tmp and the move vanishes. The launder prevented that.

To keep the copy in plain C: make tmp and base differ by a no-op computation, e.g. `base = (s32)(tmp | 0)`? combine folds. `base = tmp + 0`? folds.

Alternative: use base for the later use and tmp for the shift, and give them different *types* (e.g., base as s32, tmp as u32)? A mode difference might prevent merging: `u32 tmp; s32 base;` — cse's copy propagation across modes? Hmm, a copy between SImode regs of different signedness is the same RTX. No.

What about making `base` a pointer type? `u8 *base = (u8*)tmp;`? Hmm.

OK — hold on. Let me reconsider the whole approach. The target (score 0) has: pin $2 on tmp and hh, plus the launder. The residual pieces:
1. `move $22,$2` (base = tmp copy) — needs the launder or a real copy.
2. tmp/hh in $2 — needs the pin.
3. loop.c hoisting blocked — the pin does it.

Note item 1 and 2 are both about tmp being in $2 with base copied out.

Since the pin makes tmp a hard reg ($2), the copy `move $22,$2` is mandatory (a hard-reg variable can't be coalesced). That's the cse-copy-merge wall: with a hard reg, the copy is real; without, cse merges it.

Hmm, but the pin is a lever. Can plain C force tmp into $2 and keep the copy? 

Wait — maybe a different framing: what if `base` is a *different* variable computed from `u` independently, and `tmp` is... Let me look at the target again:

```
sll $2,$2,1       ; u*2
addu $3,$3,$2     ; u*3  (hmm)
sll $2,$3,9       ; u*3*512 = u*0x600
addu $2,$2,8192   ; + 0x2000
move $22,$2       ; base = tmp
#APP #NO_APP
sll $2,$2,16
sra $18,$2,18     ; mod = (tmp<<16)>>18
```
So tmp = u*0x600 + 0x2000, base = tmp, mod = (tmp<<16)>>18.

In mine (no levers, for loop): `sll v1,v1,9; addiu s5,v1,8192; sll v1,s5,0x10; sra s4,v1,0x12` — s5 = tmp (a register), no separate base; base == tmp == s5.

The target's `move $22,$2` exists because tmp is pinned to $2.

So the pin IS the mechanism for that copy. Plain C can't easily reproduce "copy to a hard reg" — that's exactly what the pin does.

Hmm. Unless... we make `base` live longer so that it can't be coalesced? cse merges copies regardless.

What about `base = tmp;` where base is used in the inner loop and tmp is redefined (`tmp` is assigned each outer iteration, so base's live range is the inner loop). If base and tmp are the same pseudo, then tmp's live range would extend into the inner loop, which conflicts... hmm, actually in mine base==tmp and the value is used in the inner loop, so the pseudo lives across the inner loop.

OK. Practical decision: this looks like the classic "cse-copy-merge" / "global-hardreg-reserve" wall. The pin is load-bearing for: (a) the base copy, (b) the $2 allocation, (c) blocking loop.c.

But before giving up, note w3 (pins kept, launder removed) = score 5. So the launder can be cracked with a 5-score residual. That's PARTIAL:pin with best 5 — wait, PARTIAL requires win.c scores 0 keeping only the remaining levers. w3 keeps the pins and scores 5, not 0. So w3 isn't a PARTIAL. I need a win.c with the pins kept that scores 0 — that's orig minus the launder replaced by a real-C equivalent that restores score 0.

Let me look at w3's residual (score 5): it's the launder's effect. If I can replace the launder with plain C that scores 0, we get PARTIAL:pin.

Let me see w3's diff.
