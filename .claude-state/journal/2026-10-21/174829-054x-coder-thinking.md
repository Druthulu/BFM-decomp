---
ts: 2026-10-21T23:48:29Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_CNI8aK3DJNWt6aoWbBEg
---
Score 5. Only 3 real diffs (the 2 j-target addresses are just reloc differences from the 4-byte shift — those are "COUNT" artifacts of the address change; the score counts them).

Actually score 5: the diff has 3 replace hunks. The `bnez`/`j` differences are just branch targets shifting (because the target has 1 more insn). So the real residual is the missing `move s0,v0` (2 insns: lui/addiu into v0 + move).

So I need: `lui v0; addiu v0,v0,0; move s0,v0` instead of `lui s0; addiu s0,s0,0`.

The launder does it. How to do it in real C?

The key: gcc must materialize the address into a temp and copy it. The copy must not be coalesced.

Ideas:
1. The copy's source must have 2+ sets → then local-alloc can't merge. But the source would be live longer.
   Hmm, actually: what if the source has 2 sets where the second set is right before the copy?
   ```
   u16 *pb = &D_800B99DC;   // set 1
   ... (something)
   pb = &D_800B99DC;        // set 2  (identity)
   p = pb;
   ```
   ✗ identity.

2. What if the source is a value that requires computation, e.g. `pb = &D_800B99DC + 0`? no.

3. **What if the address is computed inside a loop-invariant expression that gcc's loop.c hoists into a preheader as a separate copy?** The comment mentions "loop.md L4 preheader-copy"! So in the ORIGINAL game code, `p` was probably assigned inside the loop or the address was recomputed in the loop, and loop.c hoisted it to the preheader as a copy. That's why there's a copy!

Hmm! So maybe the original C was:
```
for (...) { ... *p ... }
```
with p assigned in the loop body, and loop.c hoisted the invariant `p = &D_800B99DC` out of the loop into the preheader, creating a copy (the preheader copy) — and the hoisted value went into v0 while the loop's p went into s0.

Hmm, but in our def, p is assigned before the loop. If we move the assignment INTO the loop (so loop.c hoists it), we might get the preheader copy naturally!

The comment says: "loop.md L4 preheader-copy: the target materializes &D_800B99DC into $v0 and then `addu $s0,$v0,$zero`."

So: if the C is:
```
for (; i < 4; i++) {
    p = &D_800B99DC;   /* inside the loop */
    ...
}
```
then loop.c would hoist the invariant assignment to the preheader, creating a copy: the preheader computes the value into a temp (v0) and copies it into the loop's p (s0). Hmm, actually loop.c's "hoist" would create: preheader: `v0 = &D_800B99DC; s0 = v0`? Hmm, more likely: the hoisted expression is computed in the preheader and the loop's assignment becomes a copy inside the loop...

Hmm, but the target has the copy at 17-19 which is BEFORE the loop (the loop starts at 22/31). Hmm, wait, where's the loop? The target's structure: insn 31 `addiu a0,s3,-2`, 36 `jal func_80049CAC`, ... 95 `bnez v0,3180` (loop back to 31). So the loop body is 31..96, and the preheader is 0..30.

So insns 17-19 (the v0 materialization + move s0,v0) are in the PREHEADER. And s0 is used inside the loop (lhu v0,0(s0) at 32, 38, 63, 87).

So: the preheader materializes the address into v0 and copies it to s0, and s0 is the loop-carried value.

So the original C probably had:
```
for (...) {
    p = &D_800B99DC;    /* loop-invariant, hoisted to the preheader */
    ...uses p...
}
```
and loop.c hoisted it, creating a preheader copy: the value computed in the preheader into a temp, copied into the loop's register. Hmm, or: loop.c hoists the assignment to the preheader, and the copy is from the preheader's computation to the loop's p.

Hmm, but our def has p assigned before the loop and gcc coalesces. What if we move the assignment INTO the loop? Then:
- p = &D_800B99DC inside the loop → loop.c sees it as loop-invariant → hoists it to the preheader, and the loop keeps a copy.

Let me just TRY it:
```
    for (; i < 4; i++) {
        s32 c0;
        p = &D_800B99DC;
        *q = *p & 0xFFF;
        ...
```
Hmm, but the target's preheader also has `q = &D_801E87B2` (s3) and `r = &D_8018F078` (s2) materialized directly into $s regs. So q and r are also loop-invariant but their assignments are in the preheader (not hoisted from inside the loop).

Hmm, so if p's assignment is inside the loop, it gets hoisted → maybe with a copy.

Actually, hmm, in the target, is the preheader copy a consequence of the hoisting? loop.c's "hoist" of `p = &D_800B99DC` would create in the preheader: `p = &D_800B99DC` (the hoisted statement) and inside the loop the original statement is deleted (replaced by the hoisted value). Then the preheader would just be `lui s0; addiu s0,s0,0` (coalesced into s0). Hmm.

But loop.c might instead create a "copy" in the preheader: the invariant expression is computed into a temp and copied to the loop's register. That's "L4 preheader-copy" per the comment.

Let me just try it empirically! x2: move `p = &D_800B99DC;` inside the loop.

Note: the def's `D_801E86BC = (*p & 1) + 3;` uses p BEFORE the loop. So p must be assigned before that. Hmm! That use is before the loop: `D_801E86BC = (*p & 1) + 3;`.

In the target, insn 22 `lhu v0,0(s0)` — that's the `(*p & 1)` load, in the preheader, using s0. So p is live before the loop.

So p is assigned before the loop and used before the loop. Then the preheader copy must come from somewhere else.

Hmm! Wait. Let me re-read the target:
```
15 lui s3,0x0  ; HI16 D_801E87B2
16 addiu s3,s3,0
17 lui v0,0x0  ; HI16 D_800B99DC
18 addiu v0,v0,0
19 move s0,v0
20 lui s2,0x0  ; HI16 D_8018F078
21 addiu s2,s2,0
22 lhu v0,0(s0)
```
So: q=&D_801E87B2 → s3; p=&D_800B99DC → v0 then s0; r=&D_8018F078 → s2.

Why is p different from q and r? Because p is USED in the preheader (insn 22 `lhu v0,0(s0)`) and also in the loop. Hmm, and q and r are used only in the loop.

Hmm, so the difference: p is used before the loop AND in the loop → the "preheader copy" is a copy of the value into the loop's register.

Hmm, so the mechanism might be: gcc's loop.c, when the loop's live-in value is used in the preheader... hmm.

Actually here's a cleaner theory: in the ORIGINAL C, the assignment `p = &D_800B99DC` was INSIDE the loop, and the use `*p & 1` was also inside the loop. But the target has the load at 22 in the preheader... hmm, is 22 in the preheader? The loop back-edge is at 95 (`bnez v0,3180`) → 3180 = insn 31. So the loop body is 31..96, and the preheader is 0..30. Insn 22 (`lhu v0,0(s0)`) is in the preheader.

Hmm, so `*p & 1` is in the preheader.

Hmm OK, so where does the copy come from? Let's think about gcc's local-alloc again. The value &D_800B99DC is used:
- at 22 (preheader, `lhu v0,0(s0)`) — needs s0 to be live
- in the loop (crosses calls) — needs s0.

So s0 must be live from 19 through the whole loop. Fine.

The v0 materialization: the address is a symbol_ref → gcc needs to materialize it into a register. If the register is s0, we'd get `lui s0; addiu s0,s0,0`. The target instead materializes into v0 and copies to s0.

What makes gcc materialize a symbol address into a temp and then copy? In gcc's mips backend, `mips_split_symbol` / the "address" handling: when a symbol address is needed, gcc emits lui+addiu into a register. If the destination is a pseudo, gcc's reload may need the value in a specific reg.

Hmm! **What if the address's pseudo is a "CONST" pseudo (a symbol_ref) and the copy is a "reg_equiv" copy?** In gcc, a pseudo assigned a symbol_ref becomes a "CONST" pseudo with reg_equiv = the symbol_ref. local-alloc then has to materialize it. When the pseudo is in a hard register...

Hmm, here's a thought: **if the symbol address is used in a context requiring a specific register (like a call argument), gcc might materialize it into a temp reg and copy**.

Hmm, actually! Look at the target: `lui v0; addiu v0,v0,0; move s0,v0`. What if this is the result of the address being used in TWO places: once where a caller-saved reg is OK (v0) and once where it must be in an $s reg (s0)? E.g. if the address is ALSO passed to a call as an argument!

Hmm, is &D_800B99DC passed to a call? Looking at the target: `func_80049CAC((s32)q - 2, (s32)&D_801E8788)` — that's D_801E8788, a different symbol.

Hmm.

OK, let me try a bunch of variants empirically:
x2: p = &D_800B99DC inside the loop.
x3: keep p before the loop but ALSO assign it inside the loop (two sets).
x4: use a temp pb without the asm: `{ u16 *pb = &D_800B99DC; p = pb; }` (the block scope, but no asm). — This is just x1 semantically (gcc will coalesce), but the SCOPE might matter! In x1, p = &D_800B99DC is a direct assignment; in x3, the copy pb → p might not be coalesced because pb is in a different block scope... hmm, actually the block scope is what the original had. Let me test it: remove only the asm, keeping the block and the copy.

That's the most obvious first test! The original:
```
    {
        u16 *pb = &D_800B99DC;
        __asm__("" : "=r"(pb) : "0"(pb));
        p = pb;
    }
```
Remove just the asm line → the copy pb → p remains. Maybe gcc doesn't coalesce it (pb is a separate pseudo with a short range; the copy p = pb; coalescing depends on priorities).

Let me test x3 = orig minus the asm line.

That's cheap. Let me do it.
