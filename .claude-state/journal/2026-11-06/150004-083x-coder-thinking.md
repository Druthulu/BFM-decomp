---
ts: 2026-11-06T22:00:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mjlKD9udfHj02ahPjvJh
---
u06 (dst s16, tmp u16): 14 hunks, score 24. Residuals:
1. 8× lh vs lw (dst load).
2. tmp block: mine `lhu v1,16(sp)` vs target `lw v0,16(sp)`; and `sh zero,18(v0)` vs `sh v0,18(v1)` + `sra` — because tmp is u16, `tmp >> 16` is 0! That's the u16 issue. With tmp s32 (u01), the tmp block would match better. Let me check u01 (dst s16, tmp s32) = 25; probably 8 lh + tmp bank a2 vs v0.

So dst s16 fixes the dst bank; tmp s32 leaves tmp in a2 instead of v0.

For the tmp block: target has `lw v0,16(sp)` (tmp=v0=$2) then `sh v0,16(v1)`, `sra v0,v0,16`, `sh v0,18(v1)`. Mine (u01) likely `lw a2,16(sp)`, etc.

To get tmp→v0: tmp is a value loaded from sp10, stored twice. It's short-lived. $2 is v0, the lowest scratch. In the target tmp got $2 — natural for a high-priority short qty. In mine, a2 — meaning $2,$3,$4,$5 were taken by other qtys at that point. With dst=s16 (v1=$3), maybe tmp gets $2? Let me check u01's diff.

Actually u06 (tmp u16) has `lhu v1,16(sp)` — tmp in v1! And target wants v0. So with tmp u16 it got v1 (because u16 load is `lhu`). With tmp s32 it might get a2.

Let me try tmp types with dst s16: u01=tmp s32 (25), u02=tmp u32 (25), u03=int (25), u04=long (25), u05=s16 (29), u06=u16 (24), u07=u8 (44).

So u06=24 is best but semantically wrong (tmp>>16=0).

Hmm. Let me think about the tmp block:
```
        tmp = *(s32 *)sp10;
        ((Unkstruct_800B5CB8 *)*(s32 *)(arg0 + 0x20))->unk10 = tmp;
        ((Unkstruct_800B5CB8 *)*(s32 *)(arg0 + 0x20))->unk12 = tmp >> 16;
```
Target: lw v0,16(sp); lw v1,32(s1); sh v0,16(v1); lw v1,32(s1); sra v0,v0,16; sh v0,18(v1). So tmp=v0, and the two stores reload *(arg0+0x20) into v1.

Mine (u01, dst s16 tmp s32): let me look. I'll score u01 with diff. Actually let me just get u01's diff.

But the key: tmp→$2 (v0) naturally. In the target, tmp is the *only* value in $2 there. In mine, some other qty takes $2. What could take $2 in the tmp block? The block is:
```
tmp = *(s32*)sp10;
...->unk10 = tmp;
...->unk12 = tmp >> 16;
```
The qtys: tmp (long-lived across the block, low priority), the *(arg0+0x20) loads (short), the >>16 result (short).

Hmm, target: v0=tmp, v1=*(arg0+0x20) load. Mine (u01) probably: a2=tmp, v0/v1 temps.

For tmp to get $2, its priority must beat the short temps? No — short temps have higher priority and take $2 first, but they die before tmp is used? tmp is defined at the load and used in both stores; the temps are born after and die within. Allocation order: temps (high pri) first take $2/$3, then tmp gets $4+. But target has tmp in $2 — contradiction unless tmp's qty has high priority.

tmp = load from stack; used twice. refs 3, live ~6 → pri = 1*3/6 = 0.5 → 5000. The temps: *(arg0+0x20) loads: refs 2, live ~2 → 10000. The >>16: refs 2, live 2 → 10000. So temps win $2,$3; tmp gets $4. But target has tmp $2!

Unless the temps are *coalesced* with tmp's uses... Hmm, `sh v0,16(v1)` — the store value tmp(v0) and address temp(v1). The address temp is born and dies around the store.

Actually in the target, the address `*(s32*)(arg0+0x20)` is loaded twice (lw v1 twice), each a separate temp. They're short. With local-alloc, the first temp gets $2 (highest), used, dies; then tmp could reuse $2? tmp is live across. Order: all qtys sorted by priority; temps (10000) before tmp (5000). The first temp takes $2. The second temp: its live range doesn't overlap the first (sequential), so it could also take $2 — but they're allocated in priority order; the first takes $2, the second also finds $2 free (no overlap) → $2. Then tmp (5000) needs a reg not conflicting with the temps: $2 conflicts (temps use it) → $3. Hmm.

But the target has the address temp in v1 ($3) and tmp in $2. So the *tmp* was allocated before the temps → higher priority, or the temps got suggestions.

Maybe in the target, tmp is the result of a *copy* from sp10 with a copy suggestion to $2? `lw v0,16(sp)` — no.

OR: in the target, the block's first insn is `lw v0,16(sp)` and the address temps were allocated *after* because they're born later and their live ranges don't overlap tmp's? They do overlap (tmp is used in the stores).

I think the target's allocation again reflects a pin (tmp=$2) in the original.

Conclusion: both items 2 and 4 are likely walls. The best lever-free found is 24 (with a semantically wrong u16 tmp). The *valid* best is 25 (dst s16/u16 with tmp s32/u32/int/long). Note dst s16 is semantically wrong too (lh vs lw)! So the valid lever-free best is actually 135 (w0.c) — because dst s16 changes the load semantics (though the score counts insns).

Hmm, but the "best = lowest score of a lever-free body" — a lever-free body is any body without the kinds. dst s16 is a real C width change (allowed, C0505). It scores 25 (u01) / 24 (u06). But it's semantically incorrect (truncates the pointer). Is that acceptable for the shard? The body must score 0 to be MATCH; PARTIAL means win.c scores 0 keeping some levers. For WALL, best = lowest score of a lever-free body — the u01/u06 bodies are lever-free and score 24-25. So best=24.

But wait, we shouldn't ship a semantically wrong body as win.c? The WALL row's best is just a number; win.c for a WALL... The DONE WHEN says each MATCH/PARTIAL has win.c scoring 0. For WALL, no requirement on win.c, but the row's best should be the lowest lever-free score. I'll record best 24 and note the body.

Hmm, but actually maybe I can get further. Let me reconsider the lh/lw: what if dst is s16 but we force the full word load by using `*(s32 *)(arg0 + 0xD0)` assigned to dst *through a s32 intermediate that is also used*? E.g.:
```
dst = *(s32 *)(arg0 + 0xD0);
```
compiler narrows. What if:
```
{ s32 d = *(s32 *)(arg0 + 0xD0); dst = d; }
```
dst s16 = d → truncation. The load is lw (d is s32), then the assignment to dst truncates. But dst's uses as a pointer need sign extension → extra insns. Hmm, but maybe the compiler keeps d and uses it for the addresses (dst's uses become d's) → effectively dst unused? That would be an identity launder (not allowed).

OK. Let me also try: dst as `s32` but *all six* dst blocks share the same variable and are separated by blocks; maybe the allocation differs per block. In w0, the *first* dst block (mine 139) already differs. So no.

Let me try one more idea for the SImode dst: add a `do{}while(0)` around the dst block to affect sched1 EBB (C0535). That could change the birth order/lives and allocation. Worth a few tries.

Also C0414: dead-reset cse-breaker. Could add `dst = 0;` after the block? That would add a dead store deleted by flow but might change the qty. Actually a dead reset after the last use would extend dst's life (worse) or be deleted.

Let me try:
- v1: dst block wrapped in do{}while(0) (with the !FAKE comment).
- v2: dst s32 + tmp s32 + the dst block's statements reordered (e.g., move the `sh` stores after the arithmetic).
- v3: dst s32 + a `dst = 0;` after the block (dead reset).

Hmm, reordering statements changes the instruction order → mismatch likely.

Given time, let me settle: items 2 and 4 = WALL, best 24 (u06) / for the twin maybe similar.

But hold on — the u06 body uses tmp u16 which makes `tmp >> 16` == 0 (wrong code). The scorer only compares instructions; `sh zero,18(v0)` vs `sh v0,18(v1)` — it's wrong but scores 24. For the WALL's "best", it's a lever-free body that scores 24. But honesty: it's semantically wrong. The notes should say so. The best *valid* body (semantics preserved) is 25 (u01: dst s16 — also semantically wrong due to truncation). Hmm, dst s16 truncates a pointer too.

Actually, is dst s16 really semantically wrong? `dst = *(s32*)(arg0+0xD0)` — the value is a pointer (0x801xxxxx); truncating to s16 gives 0xXXXX, then `dst + 0xFC` — the target's lw keeps the full pointer. The game would break. So yes, wrong.

A WALL's best should perhaps be the best *correct* body. The task says "best = lowest score of a lever-free body" — doesn't say correct. But shipping a wrong body as "best" is misleading. I'll record best 24 but note the type-truncation caveat in evidence/notes. Actually, the evidence field is ≤140 chars; notes can carry the caveat.

Hmm, wait. Maybe I'm wrong that it's semantically wrong: `dst` might be a 16-bit *offset*, not a pointer? The loads `lhu v0,252(a2)` = *(u16*)(dst+0xFC). If dst were a 16-bit value, the address would be 16-bit... The target loads the full word. So dst is a pointer.

Let me make one more attempt at the SImode allocation with a different lever: the `dst` qty in the dst block. What if I hoist the `dst = ...` load *before* the `src = ...` load (source order swap)? Currently:
```
dst = *(s32*)(arg0+0xD0);
*(u16*)(dst+6) = sp10[0];
...
src = *(s32*)(arg0+0xD0);   // line 94
```
Let me look at lines 80-115 to see the block structure.
