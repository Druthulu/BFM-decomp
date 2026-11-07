---
ts: 2026-11-06T12:33:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7UMzKqZeVhLBRTQiOdFk
---
The volatile store produces `lui v0; addiu v0; sw s0,0(v0)` (3 insns) vs target `lui at; sw s0,0(at)` (2 insns, %lo in the store). So volatile changes the addressing. Not a match.

Is there a non-volatile way to keep the order? The scheduler's alias analysis: D_801151D0 is a scalar; the array store is mem/s. If we make the D_801151D0 access go through a pointer whose alias set is unknown, sched2 won't hoist. My gp attempt didn't work (4). Let me check why: maybe gcc folded gp. Let me look at w4's diff.

Actually w4 = 4 (ORDER), same as s3. So the pointer didn't change the alias analysis (folded).

What if the pointer is stored in a variable that gcc can't track, e.g., a parameter? No parameters.

What if we use a union? Hmm.

What if we make the D_801151D0 store's ADDRESS depend on a value loaded from the array, e.g.:
```
D_801151D0 = (s32)(ot + (D_800AE7B8[*pb].f4[2] & 0));
```
identity launder.

What if the store VALUE depends on the array element: `D_801151D0 = (s32)(ot) | (D_800AE7B8[*pb].f4[2] & 0xFF000000 & 0);` — identity.

No.

What about reordering the C so the store naturally follows the RMW in the RTL? It already does; sched2 hoists it.

Could we make the RMW and the store touch the same alias set legitimately? The RMW writes D_800AE7B8[*pb].f4[2] (a mem/s). If D_801151D0 were also accessed as mem/s... e.g., store through a struct pointer:
```
((s32 *)&D_801151D0)[0] = (s32)ot;
```
Same alias (scalar). Hmm.

What if we store `D_801151D0` via the SAME pointer type as the array element: `*(s32 *)&D_801151D0 = (s32)ot;` — still scalar MEM.

OK, memory barrier = WALL sched2-store-hoist.

Let me finalize item 2 as PARTIAL:barrier,pin with win.c = w2.c. But wait — the barrier kind is kept in w2 (both barriers). The pin is kept. Keepalive cracked. 

Actually, hold on: w2 still contains the memory-clobber barrier and the empty barrier. Fine.

Let me verify win.c = w2 and it scores 0. Then record.

Hmm, but before that: the keepalive crack used a do-while. Note w1 (keepalive → do-while around `lim = cnt + zr`) also scores 0; w2 drops the `+zr` on lim too. Which is "better"? w2 keeps only the pin (cnt = n + zr). Both are PARTIAL:barrier,pin. w2 is cleaner (fewer asm uses). Use w2.

Actually, one more consideration: the result PARTIAL:<kinds still kept> — w2 keeps barrier and pin. So PARTIAL:barrier,pin.

Let me copy w2 → win.c, verify, and count tries: orig(1), s1-s5 (5), w1-w7 (7), x1-x8 (8), y1-y3 (3) = 24. Hmm, need ≥30 tries for a WALL, but this is a PARTIAL with a score-0 win.c, so the WALL requirement (≥30 tries) applies to WALL results. For PARTIAL, the requirement is that win.c scores 0. Still, let me add a few more tries to be safe and to look for a better crack. Let me try a few more barrier ideas quickly (cheap).

Ideas for barrier [4]:
- Put the call inside a nested `if (1)`? folds.
- Make the condition branch use `== 0` with a goto? 
- Use a while loop with the condition inside?
- Try making the if body start with a `panel` use... 

Actually, let me try: swap the order of the call's first two arguments in C? No, changes code.

What about the `i` increment: `i = i + 1;` — what if we write `i++;` or `i += 1;`? Same.

What about `panel += 0x20;` written before the if? Changes code.

Let me try: `if (...) { ot = xf8017E1D4(ot, panel, (s32)i); }` with the body wrapped in a do-while AND the condition in a temp:
```
{ s16 v = *(s16 *)((u8 *)D_80115158 + ((s32)i << 1)); if (v != 0) {...} }
```
The load would go to a temp v; target loads into v0 and tests v0. Might be the same.

I think 24-30 tries is enough given the result is a PARTIAL (the ≥30 requirement is for WALL). But the brief says "a WALL needs ≥20 min and ≥30 scored tries"; for PARTIAL there's no such requirement, but the wall field for a PARTIAL row also needs a tag. I'll include both wall tags in the wall column: `dbr-delay-fill;sched2-store-hoist` (the kinds still kept).

Let me do a handful more tries anyway to be thorough and see if the barrier falls. Let me try:
z1: condition temp
z2: do-while around the whole if
z3: `if (...) { } else { call }` — done (x6=4)
z4: goto-style:
```
if (*(s16 *)(...) == 0) goto skip;
ot = xf8017E1D4(ot, panel, (s32)i);
skip: ;
```
This changes the control flow shape but might alter reorg. Let me try.

z5: move the load into a temp with a cast: `s16 v = *(s16 *)(...);`

Let me run these.
