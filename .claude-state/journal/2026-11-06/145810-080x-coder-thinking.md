---
ts: 2026-11-06T21:58:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FFSHHzZcUBCdAii1jc9M
---
t09 is actually `dst` as s16 (not tmp u32)! My index mapping was wrong because the dst loop i=1..7 uses types in order: s32,u32,int,long,s16,u16,u8 → t05 is s16, t07 is u8. Hmm but t09 diff shows dst s16.

Wait, the loop:
```
for t in types:
    i += 1; w('t%02d.c' % i, src.replace('    s32 dst;', '    %s dst;' % t))
    i += 1; w('t%02d.c' % i, src.replace('    s32 tmp;', '    %s tmp;' % t))
```
So i=1: dst s32; i=2: tmp s32; i=3: dst u32; i=4: tmp u32; i=5: dst int; i=6: tmp int; i=7: dst long; i=8: tmp long; i=9: dst s16; i=10: tmp s16; i=11: dst u16; i=12: tmp u16; i=13: dst u8; i=14: tmp u8.

So t09 = dst s16 → score 25! t11 = dst u16 → 25. t13 = dst u8 → 25.

So making `dst` a **16-bit or 8-bit type** gives 710 ins and score 25! That's because `dst` is only used as a pointer; declaring it s16/u16/u8 changes the load width? No — `dst = *(s32 *)(arg0+0xD0)` assigns a word to a 16-bit var (truncation). But the target's `lh v1,208(s1)`? Wait the diff showed mine `lh` vs target `lw`. So with dst s16, the compiler loads a halfword! That means the source line `dst = *(s32 *)(arg0 + 0xD0);` got optimized: since dst is s16 and used as an address (`dst + 0xFC`), the upper bits are truncated, so the compiler narrows the load to `lh`. That changes semantics/insns — but the target has `lw`. So score 25 not 0.

Hmm, but score 25 is a big improvement. The residual: 8 sites of lh vs lw, plus the tmp/v0 differences.

What if we keep dst s32 but change the *use* so the allocation matches? The s16 trick changed the load width (wrong).

The improvement came from dst s16 changing the qty sizes (HImode) and thus allocation. But it introduces lh/lw mismatches.

Let me look at the whole t09 diff to see the full residual (17 hunks). Maybe a hybrid: declare dst s32 but cast to s16 somewhere? No.

Alternative: `dst` as `s32` but the load `*(s32*)` — the target needs lw. What if we make dst s16 for allocation purposes but force the load to be a full word via a cast: `dst = (s16)*(s32 *)(arg0 + 0xD0);`? Then the load is lw and the value truncated to 16 bits. But then `dst + 0xFC` would be a 16-bit sign-extended value — target uses the full 32-bit pointer. Semantics differ, and codegen: `lw` then `sll/sra` to sign-extend → extra insns. No.

Hmm. But wait — the target's dst is a full pointer. Declaring it s16 is semantically wrong but the compiler still produced 710 ins close to target. The 25 residual is because of lh vs lw.

What if the target's original source actually declared `dst` as s32 but the allocation matched because of the *pin*? We're trying to avoid the pin.

Let me see the full t09 diff and think. Actually, maybe combining "dst s16" with a cast on the load to force lw would give the right allocation AND right insns? Let's test: `dst = (s16)(*(s32 *)(arg0 + 0xD0));` — the load is lw, then the assignment to an s16 variable truncates (but since it's used as a pointer, the compiler might sign-extend on use: `sll dst,16; sra dst,16` — extra). Hmm.

Actually, if `dst` is s16 and we write `dst = *(s32 *)(arg0 + 0xD0);`, GCC narrows the load to `lh` (as seen). If we cast the *load result* to s32 then assign: `dst = (s32)*(s32 *)(arg0 + 0xD0);` — still assigning to s16, truncation, compiler may still narrow.

What if we declare `dst` as `s16` but store the pointer through a union? Too weird.

Alternative: declare dst `s32` and use a *separate* s16 variable only for the allocation effect? no.

Let me look at the residual more: the 25 might be reducible to 0 with the right combination. The pairs: a2->v0 x11, v0->v1 x8. So the remaining mismatches are around the tmp/case-8 region (the `lw 16(sp)` / `li`), plus the lh/lw sites (8).

Let me get the full t09 diff.
