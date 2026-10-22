---
ts: 2026-10-22T05:13:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_AmJjG11tKsy4dRaqDEAw
---
Now I see the target (91 ins):

- s1 = the base p (D_801202A0 + 0x2A0 → `lui s1,0x8012; addiu s1,s1,672` = 0x2A0 ✓), incremented in the loop (`addiu s1,s1,268` at the end) ✓.
- s0 = q = s1 + 84 (0x54) ✓, incremented in the loop (`addiu s0,s0,268`) ✓.
- s2 = the counter i ✓.
- So p = s1, q = s0, i = s2 — 3 callee-saved ✓ and the frame is 32 bytes ✓.

The load temps: `lw v0,-80(s0)`, `lw v1,-76(s0)`, `lw a0,-72(s0)` — the three loads into $2/$3/$4 ✓ (the "load temps take $4/$3" note: the third is a0=$4).

And `lbu v0,108(s0)` (c6c → $2!), `lui v1,0x8012; lw v1,-9464(v1)` (tbl → $3).

So in the target: c6c in $2 (v0), tbl in $3 (v1), and the three s32 loads in $2/$3/$4 (v0/v1/a0).

In mine (nopin): the frame is 40 (4 callee-saved: s0,s1,s2,s3) and the bank order differs.

Why does mine need 4 callee-saved? Mine: s1 = the base, s0 = base+14?? Hmm, "addiu s0,s1,14".

Hmm! 14 = 0x0E. Hmm. Hmm, `*(s16 *)&D_801270C0` hmm no.

Hmm, wait: maybe in mine, s0 = p + 0x0E?? Hmm. Hmm, hmm: `lhu v0,30(s0)` in mine vs `lhu v0,30(s0)` in the target — the target's `lhu v0,30(s0)` is `*(u16 *)(q + 0x1E)` = q+0x1E = (p+0x54)+0x1E = p+0x72. Hmm, but the target has `lhu v0,30(s0)` = q+30 = q+0x1E ✓ (q is in s0 ✓).

And mine[22] `lhu v0,100(s0)` vs target `lhu v0,30(s0)`: so in mine, the base for that load is s0 = p + 0x54 + ... hmm: mine's s0 = s1 + 14 → hmm, if mine's s0 = p + 0x54 and s1 = p, then `lhu v0,100(s0)` would be q + 100 ✗ (the target has 30).

Hmm, so mine's s0 ≠ q. Let me reconsider: mine's s0 = s1 + 14. If s1 = p, then s0 = p + 0x0E. And the load `lhu v0,100(s0)` = p + 0x0E + 100 = p + 0x72 = q + 0x1E ✓ (since q = p + 0x54, q + 0x1E = p + 0x72 ✓). So mine's s0 = p + 0x0E and the load uses offset 100 (0x64) → p+0x0E+0x64 = p+0x72 ✓.

So gcc chose a different base+offset split for the same address! That's a "reload/address" difference. Interesting: gcc 2.7.2's address selection picks the base and offset; the target uses s0 (q) with offset 0x1E; mine uses s0 (= p+0x0E) with offset 0x64.

Hmm, so mine created a NEW pointer p+0x0E (s0) — that's the extra callee-saved reg!

Why would gcc create p+0x0E? Hmm, because of some address like `*(u16 *)(q + 0x1E)` = p + 0x72 → gcc chose the base p+0x0E with offset 0x64?? That's weird. Hmm, p+0x0E — hmm, what address is p+0x0E? Hmm.

Hmm, maybe it's from `*(s16 *)&D_801270C0`? no.

Hmm, whatever: the key is that mine has an extra live pointer.

This is a deep rabbit hole. Given ~45 min of remaining budget realistically (and item 5 still to do), let me make a judgement call:

For item 4, the previous shard already established the wall (greg-alloc-order) with lots of tries. The lever-free baseline is 36. Let me spend ~20 min on a few targeted attempts, then record a WALL.

Targeted attempts for item 4:
(a) The bank order: the target has q=s0, p=s1, i=s2. The allocation order of the callee-saved regs follows the priority. To flip p and q: q must have a higher priority than p. q's refs vs p's refs.

Hmm: in the source, `p` is used a lot (in the loop body: `*(u16*)p`, `func_8017869C((s32)p)`, `*(u16*)p*4`, `func_80130D0C((s32)p)`) and `q` is used in the stores.

Hmm, q is used in MANY places (q-0x1C, q-0x50, q+0x6C, q-0x18, q-0x4C, q-0x14, q-0x48, q-0x34, q-0x4E, q-0x4, q-0x4A, q, q-0x46) — many more than p! So q should have a higher priority → q should get s0 ✓. But lever-free, p gets s0.

Hmm! Why? Because of the live ranges: p is live across the whole loop (it's the base), while q's live range... hmm, both are live across the loop.

Hmm, in gcc's global allocation, the callee-saved regs are allocated to the globals by priority (refs/live). q has more refs → higher pri → q should get s0.

Unless... the loop's strength reduction changed things: gcc's loop.c may have replaced `q` with an induction variable and `p` with another.

Hmm, the diff showed mine has `addiu s0,s1,14` — so gcc created a third pointer. That's loop.c's "pointer induction variable" optimization: it may have introduced a new induction variable (p+0x0E) to share the increment with p.

Hmm! Interesting: the target's loop increments s0 (q) and s1 (p) separately: `addiu s0,s0,268` and `addiu s1,s1,268` (at the loop end, the target has `addiu s1,s1,268` AFTER the loop — hmm, at 801785cc, outside the loop!).

Look at the target's loop end:
```
801785bc: addiu s2,s2,1
801785c0: addiu s0,s0,268     <- q += 0x10C
801785c4: slti v0,s2,96
801785c8: bnez v0,801784c8    <- loop back
801785cc: addiu s1,s1,268     <- p += 0x10C (AFTER the loop!)
```
So in the target, `p += 0x10C` is done ONCE after the loop (peeled!) — because `p` is not used after the last iteration? Hmm, interesting: the loop body uses `p` (lhu v0,0(s1) and the calls), so p must be updated each iteration... but the target only increments s1 after the loop!

Hmm, that's a loop rotation: the increment of p is at the bottom (after the loop test) → i.e. the loop is:
```
loop:
  ...body uses s1 (p)...
  i++; q += 0x10C;
  if (i < 0x60) goto loop;
p += 0x10C;   (after)
```
Hmm, but then p wouldn't advance during the iterations ✗ — unless the body uses the ORIGINAL p? No, the body uses `lhu v0,0(s1)` — hmm.

Hmm, wait: maybe the source's loop increments p at the END (after the body) and the compiler... hmm, the target's `addiu s1,s1,268` at 801785cc is after the loop's back-edge branch. So during iterations 1..95, s1 stays constant?!

Hmm, that means the ROM's loop body always uses the SAME p?! That can't be right semantically... unless the ROM's loop is different: maybe the source is:

```
do {
   ...
   i++;
   q += 0x10C;
   p += 0x10C;
} while (i < 0x60);
```
Hmm, then p is incremented each iteration.

Hmm, but the ROM shows `addiu s1,s1,268` only after the loop. Hmm! Unless gcc recognized that p is only USED in the loop body... hmm, and moved the increment? That would be wrong.

OHHH. I bet the ROM's loop is:
```
loop:
  body (uses s1 = p, s0 = q)
  i++; q += 0x10C;
  if (i < 0x60) { p += 0x10C; goto loop; }   -- hmm
```
Hmm, the `addiu s1,s1,268` at 801785cc is right after the `bnez` — so it's the fall-through path (the loop exit) → p += 0x10C happens on exit only.

Hmm, so during the loop, p is constant?! But the body uses `lhu v0,0(s1)` (p[0]) and passes p to functions. If p never changes, the loop would repeat the same work 96 times ✗ — that can't be the ROM's semantics.

Hmm, unless the loop's back edge is at 801785c8 → 801784c8 (the top) and the increment of s1 is missing in the loop... Let me re-read:

```
801785bc: addiu s2,s2,1      <- i++
801785c0: addiu s0,s0,268    <- q += 0x10C
801785c4: slti v0,s2,96
801785c8: bnez v0,801784c8   <- if (i < 96) goto top
801785cc: addiu s1,s1,268    <- p += 0x10C  (fall-through = the exit path)
```
Hmm, so p is incremented only on the exit path. That means during the loop, p is CONSTANT. Hmm, but the body uses `lhu v0,0(s1)` at the top (801784c8) and `move a0,s1` for the calls.

Wait — unless the loop body's use of p is at the TOP of the loop and the increment is at the BOTTOM, i.e. the source is:

```
do {
   body(p, q);
   i++;
   q += 0x10C;
   p += 0x10C;
} while (i < 0x60);
```
Then p is incremented at the bottom of each iteration ✓. But the ROM shows the p increment AFTER the branch (on the exit path only) ✗.

Hmm, unless gcc 2.7.2's loop rotation moved the p increment: hmm, that's the "loop rotation" optimization: rotating the loop so that the increment happens at the top. If the loop is rotated, the increment would be at the TOP, not after the loop.

Hmm, hold on: maybe the ROM's loop structure is:
```
801784c8: (top) lhu v0,0(s1) ... body ...
```
and the p increment is at the BOTTOM but the compiler placed it in the exit path because... hmm.

OH WAIT. Maybe I've got it backwards: maybe the increment `addiu s1,s1,268` at 801785cc is the p increment for the NEXT iteration... no, it's after the loop exit.

Hmm, hmm. Let me look at the loop top: 801784c8 `lhu v0,0(s1)`. So p (s1) is read at the top. If p were incremented at the bottom of the body, the read at the top of the next iteration would see the incremented value ✓. But the increment is on the exit path → so the value read at the top is the same every iteration ✗.

Unless... the loop's back edge is to 801784c8 and the increment at 801785cc is executed only when the loop exits — so p changes only after the loop. Then the ROM's loop body would use a constant p. Semantically wrong for the game, but this IS the ROM's bytes... Hmm, but the ROM is the game's actual code — it can't be wrong.

Hmm! Unless the source is:
```
do {
    ...
    i++;
    q += 0x10C;
    p += 0x10C;
} while (i < 0x60);
```
and gcc's loop optimization recognized that `p` is dead after the last iteration... no, p is used in the body.

Hmm, hold on: what if the ROM's `p` (s1) is NOT the loop's p? Let me re-read the source:

```
p = (u8 *)D_801202A0;
...
q = p + 0x54;
do {
    if (*(u16 *)p != 0 && ...) {
        func_8017869C((s32)p);
        ...
        (*(void (**)(s32))(tbl + *(u16 *)p * 4))((s32)p);
        ...
    }
    i++;
    q += 0x10C;
    p += 0x10C;
} while (i < 0x60);
```
So p IS incremented each iteration. But the ROM shows it only after the loop. Hmm, that means the ROM's loop body uses a CONSTANT p?! That would be a ROM bug...

Unless the compiler did something clever: maybe gcc 2.7.2 recognized that `p` is only USED at the top of the loop body (`lhu v0,0(s1)`) and the calls... hmm, the calls take p as an argument (`move a0,s1`) — a call could modify p? No, p is a local.

Hmm, wait. Let me re-read the target listing again:

```
801784c8: lhu v0,0(s1)      <- *(u16*)p
801784cc: nop
801784d0: beqz v0,801785bc  <- if (*(u16*)p == 0) goto the loop end
801784d4: li v0,1
...
80178500: jal func_8017869C ; move a0,s1     <- func_8017869C(p)
...
80178550: lhu v0,0(s1)      <- *(u16*)p again
...
8017856c: jalr v0 ; move a0,s1               <- indirect call with p
...
801785bc: addiu s2,s2,1
801785c0: addiu s0,s0,268
801785c4: slti v0,s2,96
801785c8: bnez v0,801784c8
801785cc: addiu s1,s1,268
```
Hmm, so s1 (p) is incremented ONLY after the loop. So during the 96 iterations, p is constant?! But the loop reads `*(u16*)p` and calls functions with p...

That means the ROM's behavior is: the loop body runs with p = the base each time, and p is advanced once at the end. That IS the ROM's behavior — hmm, that seems like a compiler bug... OR the source is different from what the current src says!

AH — that's the point: the src's current body has `p += 0x10C;` INSIDE the loop, and the pinned version reproduces the ROM. So the pinned version must produce the same ROM bytes. Since the ROM has the p increment after the loop, the pinned version must have the p increment outside the loop... but the src has it inside!

Hmm, so the pinned src does NOT reproduce the ROM? But the score compares against the build object (the current src's compiled bytes) — which IS the ROM (the project rebuilds the ROM byte-identically). Hmm, so the current src (with the pins) compiles to the ROM bytes.

So gcc 2.7.2, given `p += 0x10C` inside the loop and p used in the body, moved the increment out of the loop?! That's a "loop invariant"/"dead" optimization: hmm.

OH WAIT. I bet I know: gcc's loop optimization recognized that `p` is dead after the last iteration... no. Hmm, alternatively: the loop is a `do-while` and gcc rotated it: the increment of p at the bottom of the body, when rotated to the top, would be before the body... The ROM's structure has the body at the top and the increments at the bottom (s2 and s0) — so the loop is NOT rotated for q and i.

Hmm, but for p: the increment is at the very bottom, AFTER the loop test. That's weird.

Hmm, unless gcc 2.7.2's loop.c did "loop unrolling/peeling" of the last iteration: the last iteration (i == 96) is peeled off the loop, and in that peeled iteration p is incremented... hmm, no: the peeled copy would contain the whole body.

Hmm, alternatively the source's loop might be:
```
while (i < 0x60) {
    ...
    i++; q += 0x10C; p += 0x10C;
}
```
Hmm.

OK, this level of detail is beyond what I need. Let me instead focus on the practical: the lever-free body scores 36 and the previous shard hit a wall.

Given my remaining time budget, let me allocate: item 4 → ~20 min of attempts; item 5 → ~20 min; then the writeup.

For item 4, the highest-value lever given the notes: the callee-saved bank order (p,q,i) and the extra pointer.

Idea A: the source has `p` used in the loop body and incremented at the end; gcc created an extra pointer (p+0x0E) in the lever-free version. Hmm, where does p+0x0E come from? Hmm! `*(u16 *)(q + 0x1E)` = q+0x1E = p+0x72. Hmm, p+0x0E?

Hmm, hmm: 0x0E... hmm, `*(s16 *)(q - 0x4E)` hmm no.

Hmm, p + 0x0E: hmm, could it be from `*(u16 *)(q + 0x1E)` where q = p + 0x54 → p + 0x72 = (p + 0x0E) + 0x64 ✓ — so gcc chose the base p+0x0E with offset 0x64. Why p+0x0E? Because gcc's address selection prefers a base+offset where the offset fits in 16 bits (it always does) hmm, or prefers a "loop-invariant base" with a smaller offset? Hmm, p+0x0E is not a loop-invariant base (it's p + a constant, and p changes each iteration → p+0x0E is also an induction variable → gcc would need to increment it too → an extra induction variable → the extra callee-saved reg!).

So the lever-free version created an extra induction variable. Hmm, that's a loop.c artifact.

Idea B: force the address form by writing the source differently: e.g. `*(u16 *)(p + 0x72)` instead of `*(u16 *)(q + 0x1E)`. Then gcc would use p + 0x72 directly ✓ (no extra induction variable!). Hmm, but the source's `q + 0x1E` is what the ROM has (the target's `lhu v0,30(s0)` uses s0=q with offset 30 ✓ → the target uses q as the base ✓).

Hmm, so the target uses q as the base and mine uses p+0x0E. To make mine use q, maybe express the addresses via q consistently (as the source does) — it already does.

Hmm, mine's `lhu v0,100(s0)` — with s0 = p+0x0E, offset 100 = 0x64 ✓ = p+0x72.

Hmm, so gcc chose to use the "p+0x0E" base for the q+0x1E load. Why? Because gcc's "address selection" (final.c / reload.c) picks the base that minimizes the offset or the number of instructions. With q = p+0x54 (an induction variable with its own register), q+0x1E = (p+0x54)+0x1E needs the offset 0x1E ✓ (fits). So why p+0x0E?

Hmm, unless mine's s0 IS q and my arithmetic is off: mine[11] `addiu s2,s1,84` (q = s1+84 → s2 = q) and mine[12] `addiu s0,s1,14` (s0 = s1 + 14). Hmm, so mine has BOTH q (s2) and p+0x0E (s0)?? and p (s1).

So mine's registers: s1 = p, s2 = q, s0 = p+0x0E, s3 = the counter. Hmm, 4 callee-saved ✓ (the frame is 40 ✓).

And the target: s1 = p, s0 = q, s2 = the counter.

So in mine, the extra p+0x0E exists and q got s2 instead of s0.

Hmm, so where does p+0x0E come from? Some address in the source: p + 0x0E? Hmm: `*(u16 *)(q + 0x1E)` = p + 0x72; `*(u16 *)(q - 0x4E)` = p + 6; `*(u16 *)(q - 0x4A)` = p + 0x0A; `*(u16 *)(q - 0x46)` = p + 0x0E !!! ✓✓

There it is: `*(u16 *)(q - 0x46)` = p + 0x0E. So gcc chose the base p+0x0E for that address (offset 0 → `lhu v0,0(s0)` ✓ — mine[69] `lhu v0,0(s0)` ✓✓).

So gcc created an induction variable p+0x0E for the address q-0x46 — because the offset -0x46 from q doesn't fit in a 16-bit signed? It does (-70). Hmm, but with q = p+0x54, q-0x46 = p+0x0E: gcc's address selection may prefer a base whose offset is small.

Hmm, whatever the reason, the target uses s0 (q) with offset -0x46 (`lhu v0,-70(s0)` ✓ from the target listing: `9602ffba lhu v0,-70(s0)` ✓).

So the target uses q as the base for q-0x46 ✓, while mine uses p+0x0E.

How to make gcc use q as the base? Hmm, by making the p+0x0E base less attractive. Hmm, gcc's address selection in reload.c picks the base with the "best" (shortest offset) — the offset -0x46 (=-70) fits in 16 bits ✓, so why p+0x0E?

Hmm, maybe because the target's version had `q` as a hard-reg pseudo (the pin!) → the address had to use q ✓✓✓. Right! The pin on q ($16) forces the address to use s0.

So: lever-free, gcc creates p+0x0E as an extra induction variable. Hmm.

To avoid it: express the address as `*(u16 *)(q - 0x46)` (as now) hmm. Or use `p + 0x0E`?? Then gcc would use p as the base with offset 0x0E — but the target uses q with -0x46 ✗ (a different address form → a mismatch).

Hmm. So the target's address forms require q to be a fixed register.

Hmm, so this item needs the q pin (or an equivalent mechanism) → it's a WALL for the "all three pins" requirement, but maybe a PARTIAL is possible: "PARTIAL:pin" with the q pin kept and the other two dropped → the previous shard's vP1_keepq = 9 (not 0). Hmm, 9 ≠ 0.

So even the partial isn't at 0. Hmm, vA2_q_tbl = 5 (keeps the q and tbl pins), vA8_u8 = 5, vA9_temp_first = 5.

So the best partial is 5.

Hmm, the moves file says the G08 wall for this item.

Given the difficulty, my G08b contribution: try a handful of new lever-free spellings, record the best (probably 36 or better), and the wall.

Let me try a few targeted things for item 4:
1. The address form: keep `q - 0x46` but ALSO try writing the loads as `*(u16 *)(q + 0x1E)` variants... hmm.
2. Try making `p` and `q` related differently: e.g. `q = p + 0x54` → maybe use a separate `u8 *base` for the initial value so that p's live range is shorter.
3. Try the loop counter as a pointer-based induction variable.
4. Try swapping the order of `q += 0x10C; p += 0x10C;`.
5. Try the loop as a `while` loop instead of do-while.
6. Try `for (i = 0; i < 0x60; i++)`.
7. Try declaring the block-local temps (`tbl`, `c6c`) differently.

Hmm, item 4's best lever-free might improve from 36 via the loop shape. The loop shape is in the catalog ✓.

Let me try a batch:
n1: `for (i = 0; i < 0x60; i++) { ... }` with the increments at the end.
n2: the loop as `while (i < 0x60) { ... }`.
n3: the loop body in a block with the temps declared at the top of the function.
n4: `tbl`/`c6c` declared at the top of the function.
n5: the `q - 0x46` address written as `p + 0x0E`? (would change the address form but maybe avoid the extra IV... the target uses q-0x46 → ✗ mismatch, but let me see the score).
n6: the c6c load moved (statement order).
n7: `i` as a `s32` counter vs `u16`? The target's `slti v0,s2,96` (signed compare with 96) — i is s32 ✓.

Let me do a batch of 8 and see if any beats 36.

Time: 23:20. Let me generate and score.
