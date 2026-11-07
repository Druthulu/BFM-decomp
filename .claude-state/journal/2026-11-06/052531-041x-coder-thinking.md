---
ts: 2026-11-06T12:25:31Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_QDbAy2dxLIUDlIx1G1LD
---
Best remains 3. The tie persists in vA/vC/vF/vG/vM. vN (pos pin dropped) = 9 — interesting, so the pin matters.

Let me think differently about the tie. In target, var_v0_3 = v0. What if we give var_v0_3 a REAL second use that forces it into v0? Hmm.

What if var_v0_3 is assigned from a function of pos that gcc computes into v0 because... 

New idea: what if `pos` is used in the tail via `p`? The variable `p` is a u16* set inside the 0x8000 branch. If `pos` were used as an offset into p... no.

Another idea: maybe the tie disappears if `pos` is NOT pinned but allocated t4 naturally AND is live-out. Since the pin's qty_phys_sugg is unconditional, maybe without the pin and with pos live... but pos can't be live.

Hmm, wait. Let me revisit: is it possible that the target's `pos` is live because of the ORDER of the store? In target:
```
cf4: j d14
cf8: addiu v0,t4,2      <- var_v0_3
cfc: (else arm)
d14: sh v0,2(v1)
```
pos (t4) is dead after cf8. So in target, pos IS dead at the addiu, yet the addiu went to v0. So the tie was suppressed for another reason: the pin's qty_phys_sugg should have invited the tie... but the target had the KEEPALIVE making pos live. Right.

So in target, pos was live past the addiu (into the join block, where the keepalive is). Confirmed.

Therefore, lever-free needs pos live past. Only a real use.

Hmm, is there any real use of pos in the join block? What about the return value? The function returns 1. What if we return `1` computed as something involving pos? No.

What if the D_801152AA store is moved after the join store, and the join uses pos? no.

OK — maybe a different C shape entirely: what if the addiu's result is not tied because it's a 3-operand expression with pos NOT dying? E.g., use pos in the join store's address: `b4b[pos - pos + 1] = var_v0_3;` — identity launder.

Alright. Let me now consider that maybe the target's tail can be produced by a different arrangement where pos's last use is naturally in the join block. What if the source computes `var_v0_3` in the join from the CONSTANT and uses pos there:

```
if (arg1 & 1) { b4b = D_801909C4; D_801152AA = 0xFFF; }
else { b4b = D_801909C4; D_801152AA = -0xFFF; }
b4b[1] = pos + ((arg1 & 1) ? 2 : -2);
```
vI scored 24. Not good.

What if the join block is where pos dies but the tie is suppressed because the addiu's src is pos and pos is live-out of the join? No.

Let me try: use `pos` in the tail's LAST statement legitimately by rewriting the tail to compute the midpoints with pos as a dead value... no.

I'm now going to accept the WALL for item 1 after a few more tries, but the WALL needs ≥30 scored tries. I have: a1, a2, a3, a4, b1, b2, b3 (7) + 15 variants = 22. Plus orig? Let me generate ~10 more variants to cross 30.

Actually, wait. Before walling, let me reconsider the problem from scratch with a key question: is the keepalive really needed, or was it there because of the pin's qty_phys_sugg? The keepalive keeps pos live past the temp. If I REMOVE the pin on pos AND keep pos live via a real use... there's no real use.

Hmm, but here's a thought: what if pos is not a copy of arg2 but arg2 itself, and the ADD uses arg2 at the END of the join where arg2 is still live because of the `(s16)arg2` uses in the FIRST branch (the division branch at the top)? No, those are before.

What if we reorder the function so the `(s16)arg2` computation happens AFTER the addiu? The division branch is early; the addiu is late. If arg2 were used after the addiu (e.g., recompute something), arg2 stays live. But arg2's uses are all before.

Hmm! What if `pos` is used in the tail through the D_80126720 computation... no.

OK, let me try one more idea: the `b4b[1] = var_v0_3;` store uses b4b. What if the store is `b4b[1] = var_v0_3;` and then the tail computes `D_80126724` using `p` — the variable p was set in the 0x8000 branch. No pos.

Let me look at whether there's another way to keep the addiu out of pos's reg: make var_v0_3's destination register a HARD reg via... no asm allowed.

Give up on MATCH for item 1; try for a PARTIAL: we need a win.c scoring 0. The original scores 0 with all kinds. A PARTIAL with all kinds is degenerate but valid? "PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers)". If we keep only the keepalive (drop barrier+launder), does it score 0? Let me test that: orig minus barriers minus launder, keeping the keepalive. Earlier b3 = launder+keepalive (barriers dropped) = 12; and orig-barriers-launder = ? Let me test.

Actually, more useful: test each single-kind body for score 0:
- keepalive only: orig - barriers - launder
- barrier only: orig - keepalive - launder
- launder only: b1 = 11 (already)
- keepalive+barrier: orig - launder
- launder+barrier: b2 = 3
- launder+keepalive: b3 = 12

If "orig - launder" (barrier+keepalive) scores 0, that's a PARTIAL:barrier,keepalive. Let me test. And "keepalive only".

This is quick.
