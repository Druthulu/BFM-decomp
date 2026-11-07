---
ts: 2026-11-06T11:42:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2liNECx2JVCOqgoreUDf
---
Good: sc.sh gives one line per candidate. So I can generate 30 candidates in one file set and score them in one command.

But each --try runs a full TU compile of 800.c (18k lines). That's maybe 2-4 s each. 30 = ~2 min. OK.

Design: write a generator script under my item dir that emits variants v01..v30 combining real-C moves:
- statement order permutations of the second group
- temp introductions (xs/ys)
- decl order
- widths (s16/u8)
- pointer reuse (q = p+8 etc.)
- init at decl
- &&/|| folds (not applicable)
- do-while placements
- goto loop (no)

Then score all, pick best, iterate.

Given "real C moves only", the space is large. Let me be systematic for this function.

Key residual (v0 score 30): the target's EBB2 ordering vs mine. The biggest lever might be making the second group's stores' priority match. Hmm.

Alternative idea: maybe restructure the whole function to use a different pointer: e.g. `u8 *q = p + 8;` then write q[...] and keep p for the tag. Then the tag2 load `*(u32*)p` must still alias q[3]? If q = p + 8, then *p vs q[3] don't alias (offset 8+3=11 vs 0..3) — gcc might not know. That changes dependencies and could produce different order! In the target, the tag load (lw a2,0(v0)) happens after the byte stores — a pure scheduling choice (priority 1 tie broken by LUID). If the load's LUID is earlier than the stores... it's later in source, so LUID later, fine.

Hmm, wait. Let me look at where mine and target diverge in LUID terms. In mine, sh s1,8 (vx) is at position 50 (before sb p3 at 59). In source, vx store is after the c stores. So sched1/sched2 moved the vx store BEFORE the c stores and the p[3] store. Why would it? Because in sched1 the store's priority is 5 (equal) and LUID should keep source order... unless the store to 8(v0) was scheduled early because of a hazard/anti-dep thing.

Hmm, actually maybe the culprit is sched2 with "launching X before Y with 1 stalls" (the load-delay hazard). sched2 uses the actual pipeline hazards: store after load, etc.

Honestly, empirical search is the way. Let me write a generator with ~30 variants and score. If none hits 0, record WALL with best.

Actually wait. Before the brute force, let me reconsider the problem: the barrier's effect is essentially an ordering fence. A real C construct with a similar fence effect... What about the *pins* we keep? A `register u32 mFF __asm__("$7")` pin makes mFF a hard reg, adding constraints.

Hmm, what about the launder replacement: `x = x;`? No-op, deleted.

C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse. So the expected crack (if any) comes from these. Since the item is a singleton with barrier,launder, and the original def had 4 barriers + 2 launders, the "real" body probably used some structure.

Let me try a specific promising move: **pointer reuse**: use `vx`/`vy` differently — e.g. compute the second group's stores through a pointer `q = p + 8` and keep the first group through p+8 as well. Or: keep `p` at the packet start and use `p[0xB]`, etc. (offset arithmetic). That changes the address computations (addiu chains) and thus scheduling.

Actually, here's a cleaner idea matching the source's intent: `p += 8;` then the second group uses p. What if instead we do the first group with p+8 inline and then `p += 8` right before the tag load? Then the stores' addresses are `p+0xB` etc. with p = packet start. The addiu p,p,8 would be born later. Hmm, target has addiu v0,v0,8 at 3834 early.

I'll brute force with a generator. Let me define the variant axes and generate ~40 files:

Axis 1: base = v0.
Axis 2: wrap first/middle/last groups in do-while (3 axes, combos).
Axis 3: move `vx = x; vy = y;` position.
Axis 4: use temp `s32 xs = x + w_, ys = y + h_;` instead of in-place adds.
Axis 5: store the tag2 load at different source positions (must stay after p[3] store; try after the c stores / after vx/vy stores).
Axis 6: split the tag store into a temp (`u32 t = (tag2 & mFF) | ...; *(u32*)p = t;`).
Axis 7: reorder the c stores (4 groups) among themselves.
Axis 8: `pmask` computed at declaration (init at decl).
Axis 9: pointer reuse: q = p + 8.
Axis 10: widths: `*(u16 *)` instead of `*(s16 *)`.

That's a big space; I'll generate a reasonable set of ~36 and score them all in one sc.sh call. Then pick the best and hill-climb.

Let me write a Python generator under G30/func_80015B6C__800/gen.py that writes files into subdir `cand/`. The brief says scripts under .run/, fine.

Actually careful about disk: 40 candidate files, each ~2KB. Fine.

Let me design the generator with a template and parameter dicts.

Template pieces (lever-free):
```
    otp = D_800A651C[D_800B9A02].a;
    p = (u8 *)func_80010A08(0x34);
    mFF = 0xFF000000;

    p[3] = 1;
    *(u32 *)(p + 4) = 0xE1000000;
    *(u32 *)p = (*(u32 *)p & mFF) | (((Unkstruct_80015B6C *)otp)->unk3FFC & 0xFFFFFF);
    ((Unkstruct_80015B6C *)otp)->unk3FFC = (((Unkstruct_80015B6C *)otp)->unk3FFC & mFF) | ((u32)p & 0xFFFFFF);

    p += 8;
    ...
```

Variant knobs:
- tagload_pos: where `tag2 = *(u32 *)p;` goes: after vx/vy stores (base), or after p[7] store, or after the c stores, or right before x += w_ (same as base).
- add_style: 'inplace' (x += w_; y += h_;) or 'temp' (s32 xs, ys computed at their use) or 'direct' (store `x + w_` in both places, letting cse make one add).
- split_tagstore: `u32 nt = (tag2 & mFF) | ...; *(u32*)p = nt;`
- order of c-store groups: [4,0xC,0x14,0x1C] permutations (say 4 orders).
- dowhile masks: none, first, mid, last, first+mid, first+last, mid+last, all.
- q pointer: use q = p+8 for the first group, p advanced after.

That's a lot; pick combos.

Given each score costs ~3-5 s, 40 candidates ≈ 3 min. OK.

Actually, hold on. Let me reconsider the value: The item is 1 of 4 and the budget is 20-30 min each. Total session maybe 2 hours. I've spent ~20 min on item 1. Let me do the generator burst now (one command, ~3-4 min), then decide.

Let me write the generator.
