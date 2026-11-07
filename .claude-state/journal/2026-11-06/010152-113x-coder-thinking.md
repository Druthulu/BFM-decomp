---
ts: 2026-11-06T08:01:52Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_27bwKJ7q1fMW2OnECdRy
---
The gte_stsv macro clobbers $12,$13,$14 (t4,t5,t6) and memory. It takes r0 as a register operand. So w3c must be in a register at the gte_stsv. The target uses a0.

The `gte_ldv0(L.v48)` takes the ADDRESS of L.v48 as a register operand. In target, `addiu v0,sp,72; lwc2 $0,0(v0)`. So the macro's operand address goes to v0.

Hmm, the asm operands' register allocation is done by reload, not local/global-alloc. The "r"(r0) constraint just needs any register; reload picks. For gte_stsv, w3c is a pseudo allocated earlier; if it's in a0, the asm uses a0.

OK. Let me consider the possibility that the original code used a DIFFERENT gte macro variant, e.g. `gte_stsv` vs a variant, or that the pointer is passed differently. The source uses `gte_stsv((u16 *)w3c)`. If the original used `gte_stsv(L.o1)` (the array decays to a pointer), the pointer address would be computed where the macro is (at the first gte block). Target: `addiu a0,sp,16` at insn 60 — that's BEFORE `addiu v0,sp,72` (the v48 address at ~62). The first gte_stsv is after the first gte block (~75). So the pointer is computed at 60, before the first gte_ldv0. The source computes it at line 452 (before the gte block). So it's a named variable. Fine.

Let me try the "L.o1 decay without variable" variant anyway, plus one where the pointer is a u16* initialized at the declaration point (C89 block).

Actually, let me step back and consider the score-1 candidate's mechanism more carefully. The engine's path: introduce a temp for v48[0] (`u16 tmp0`) + width change. The width change "u32->u16" suggests the temp was declared u32 then narrowed to u16. A u32 temp assigned `*(u16*)vsrc` then stored to a u16 field: the u32→u16 narrowing changes a SUBREG. This could change the qty ordering in the block, flipping the w3c allocation. Since the score was 1 (one insn off), maybe a slightly different combination gives 0.

Given the engine explored 324 compiles and got 1, and I've tried ~60, maybe the item is a WALL with best 5 (lever-free) but there's a near-MATCH at 1 with a temp+width move. The task says WALL (best = lowest score of a lever-free body). Our best lever-free body is 5. But is the temp+width move "lever-free"? Yes, real C. Score 1 isn't 0, so not a MATCH.

Hmm, but the goal is to find a score-0 lever-free body. The engine's best 1 is tantalizing. Let me try to reproduce a score-1 on the current body by trying width changes on various temps combined with the temp48 move. The width move candidates after the temp move were u16->s32/s16/u8, all scoring 6-7. Maybe the engine's body had the temp as u32. Let me manually create a u32 temp48 and then narrow it:
```
u32 tmp0;
tmp0 = *(u16 *)vsrc;
L.v48[0] = tmp0;
```
and then a variant with `u16 tmp0` — both. Let me test u32 temp48 and u32 temp with explicit cast, plus u8/s16/u32 temps for v48[0] and v48[1].

Actually, the engine's second move "R12 width tmp0 u32->u16 @413" — @413 is the struct field `s16 o1[4]`. Maybe "tmp0" is not our temp but a generator-named temp created from the width move on the struct field? The move format "R12 width <name> <old>-><new> @<line>" where <name> is the variable being changed and @line is where. If the name is tmp0, the width change is on tmp0. But the first move created tmp0 at @443. Then changing tmp0 u32->u16 at @413 (its declaration line, which in the engine's body was line 413). In the current body, the temp's declaration would be at line 412 (before the struct). Indeed the current candidate names show "R12 width tmp0 u16->s32 @412" — the declaration line is 412. So in the engine's body, the temp was declared at line 413 and created as u32; then narrowed to u16. The engine's body version is 1 line off (maybe the file had an extra blank line at P36 time).

So the engine's candidate = temp48 with u32 declared, narrowed to u16. In the current body, "R8 temp tmp0 @443" creates u16 directly. I need to create u32 tmp0 manually. Let me test:
```
u32 tmp0;
...
tmp0 = *(u16*)vsrc;
L.v48[0] = tmp0;
```
Then score. And maybe the score-1 was with the width narrowed to u16 (same as our u16 temp). Let me test u32 temp (which is the "before width" state) and see its score; then the narrowed u16 = our v43_temp48 (score 6). Hmm, the engine's narrowed state scored 1, ours scores 6 — so the body differs elsewhere.

Wait, maybe the engine's first move created a temp at a DIFFERENT statement. The trace's first move is "R8 temp tmp0 @443". In the engine's body, @443 might be `L.v48[0] = ...` (line 443 in the current body). Yes. So same move. Then the width change u32->u16. Our temp is created as u16 by the generator; the engine created it as u32 (maybe the generator's default) and then narrowed. The final text might be identical (`u16 tmp0`)! But scores differ (1 vs 6)? That can't be unless the body differs elsewhere.

Hmm, maybe the engine's "R8 temp" created `u32 tmp0` and the width move at @413 changed a DIFFERENT variable named tmp0? Confusing.

Let me just try to see if the current body can reach 1 with any temp+width combo. Let me test u32 temp48 and u16 temp48 (done, 6), and temps for other v48/v50/v58 elements, with widths. Let me generate a batch.
