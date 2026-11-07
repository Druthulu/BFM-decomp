---
ts: 2026-11-06T12:56:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9qEG71eqmJXflZFlMYed
---
No luck. The do-while doesn't stop cse's hard-reg forward (cse1's EBB split is about CSE, but the do-while may not split here).

Let me think about gcc's treatment again. Actually, maybe the pin isn't dropped by cse but by `local-alloc`'s `reg_equiv`/copy coalescing... 

Let me test the hypothesis differently: is `ba` even in $5 in c1? The asm shows `addu $4,$3,$4` then the loop uses $5 for src. So ba → $4 directly.

Hmm, what if the pin is honored but then the *hard reg 5* gets a value that's dead, and cse replaces `(reg:4) ← (reg:5)` with `(reg:4) ← expr`?

In cse.c, hard regs ARE tracked. To prevent it, the copy must not be a simple reg-reg set... 

What if `dst = ba;` is written as `dst = (u16 *)((u32)ba);`? A cast — same.

What if the loop's first use of dst is `*dst = tv;` — cse could still forward.

What if we make ba's value opaque: `ba = (u16 *)(tmp + (u8 *)dp);` → the value is a sum. cse forwards.

OK, alternative approach: since the pins may stay and the ONLY missing thing is that ba must be materialized in $5, maybe we can write the C so that ba's value is used twice — e.g. in the loop, write `*dst = tv;` where dst... no.

Hmm, what about using `ba` in the loop instead of `dst`: 
```
dst = ba;
do {
    tv = *src; src++;
    *dst = tv; dst++;
    ...
```
What if the loop is written with `ba` and dst only for the second store? That changes the codegen.

Wait — maybe the answer is much simpler: maybe the original's launder was needed because `dst = ba` is a copy between two hard regs, and gcc's `local-alloc` merges them. The launder kept ba live. Without the launder, gcc coalesces.

What if I make `dst = ba` NOT a copy but a re-computation? Like `dst = (u16 *)(tmp + (u8 *)dp);` — then ba is dead entirely (and its pin is irrelevant) → code: `addu a0,...` — that's what mine does, and it's 1 insn short.

So the target genuinely has 2 insns: `addu a1,...` + `move a0,a1`, which requires ba in a1 to be live/used.

Lever-free: give ba a second real use that costs nothing. Ideas:
- `if (ba != 0) { ... }` — adds a branch.
- Use ba in the loop condition: `} while (iVar2 < 0xc);` → no.
- `src = ba;` no (that's i3, 19).

Hmm, what if the second use is in the `local[2] = 2; local[3] = 0xc;` region? No.

What if `dst = ba;` is followed by a use of ba that gcc deletes as dead? No, then it's deleted.

What if we declare `dst` pinned to $4 and initialize it via the *declaration*: `register u16 *dst __asm__("$4") = ba;`? Hmm! Init-at-decl of a hard-reg variable. That might emit the move differently.

Or: `dst = ba + 0;`?

Honestly, maybe a better approach: the `ba` pin may be dropped and the difference is only 1 insn + renames. What if we DON'T use ba at all (drop the variable) and instead write `dst = (u16 *)(tmp + (u8 *)dp);`? Then mine = 157 ins? Worse.

Alternatively, keep ba's pin effective by making ba used by an *asm-free* construct that gcc can't remove: e.g., store ba somewhere? No.

Hmm, hold on: maybe the pin IS honored, and the issue is that cse *renamed* the copy: in c1's asm, is there any `$5` assignment? `addu $5,$5,2` in the loop is src. The `la $4,D_80127548` etc.

Wait, actually — maybe the pin on ba is honored but the *variable* ba and the value `(u16 *)(tmp + (u8 *)dp)` are in $5, then `dst = ba` copies $5→$4, and cse deleted the copy by propagating $5's value into $4 and deleting the (now dead) $5 store. That's exactly cse's "store forwarding" for hard regs (cse.c does handle hard regs: it records `reg` equivalences, and for a hard reg it only deletes the set if... hmm, cse never deletes a set to a hard reg unless it's dead and the reg is not live... it does: "if (reg is dead after this insn and the value is used later, forward").

To block it: make $5 live after the copy. Lever-free: a second use of ba after `dst = ba`... 

What if the loop condition used ba? no.

What if `ba` were used to compute something dead? deleted.

OK — maybe use `ba` in the `func_800599B8(local)` call? no.

Alternatively: does the target's `move a0,a1` survive because $5 is live across the loop? In the target, after `move a0,a1` ($4=dst), $5 (ba) is dead. So cse should have folded it there too... unless the launder asm made ba "used" (the asm's input), keeping it live.

Yes — that's exactly it: the launder's `"r"(ba)` makes ba live AT the asm point, so cse can't delete the store to $5 (the asm reads it). Since the asm is after `ba = ...` and before `dst = ba`, ba is live across both.

So lever-free: we need ba live at some point after the assignment... i.e., a real use.

Hmm what about the `decoy` variable: `decoy = (s32)ba;` — a real copy (1 insn). No.

Let me look at the problem from the other side: what if we accept `addu a0,...` (no move) and instead make the target's shape come out by using `dst` differently? No, the target's insns are fixed.

Alternatively: maybe make the ba computation produce the value in $5 and use `dst = ba` where dst is pinned... and prevent cse by making the ba assignment not a "simple" expression: e.g. `ba = (u16 *)((u8 *)dp + tmp);` (same) or `ba = (u16 *)(tmp + (s32)(u8 *)dp);` — same rtx.

What if `tmp` is reused after (so the expression isn't the same)? 

Hmm, cse's forwarding for hard regs: `set (reg 5) X` then `set (reg 4) (reg 5)`: cse replaces (reg 5) with X in the second insn and then, since (reg 5) is dead, deletes the first set. For this to be blocked, either X must be non-forwardable (e.g., a volatile/memory ref?) or (reg 5) must be live later.

Hmm! What if the value assigned to ba involves a *memory load* that cse can't duplicate? e.g. `ba = (u16 *)(D_80127548[1] + ...)`? That changes the code.

Honestly, this item might also be a WALL. But wait — maybe there's a smarter framing: the target's `move a0,a1` could also be explained WITHOUT the pin: if `dst` is pinned to $4 and `ba` is NOT pinned, gcc would put ba in a1 anyway (as a pseudo) and emit `move a0,a1`... and the pseudo would be dead after → cse would forward. Same.

Hmm, but what if `dst`'s pin were the only pin and `ba` were an ordinary pointer: `dst = ba;` → gcc emits `addu a1,...` (ba in a1) then `move a0,a1`? Only if ba's pseudo is in a1 and used. cse would forward it into the move and delete.

Unless the move `dst = ba` where dst is a hard reg $4: cse records `$4 = expr`. That's 1 insn. So we'd get `addu a0,...` — same as mine.

So the target's extra insn requires ba live across the copy. The launder asm did that.

Lever-free way to keep a value live without emitting insns: a `use` in the RTL — the C-level equivalents: an asm (no), a volatile access (no)...

Hmm, what about `dst = ba; ... ; if (0) *ba = 0;`? Dead code eliminated.

What about assigning ba to something that's used later? e.g. `src = ba` (i3 → 19).

OK, so item 3 is likely a WALL too. But wait — let me reconsider the kinds: keepalive,launder. The launder here is `"=r"(decoy) : "r"(ba)`. Maybe its purpose is different from what I assumed, and the +1 insn difference is a *consequence* of keeping ba live.

Hmm, but hold on: maybe I should reconsider whether the `ba` pin can be made to work by *moving* the pin's use: e.g. `register u16 *ba __asm__("$5")` and write the loop using `ba` directly for the first store and dst for the rest? Let me look at the target loop:

```
1000: lhu v0,0(a2)     ← src (a2)
1004: addiu a2,a2,2
1008: addiu t0,t0,1
100c: sh v0,0(a0)      ← dst (a0)
1010: addiu a0,a0,2
1014: lhu v0,0(a2)
1018: addiu a2,a2,106
101c: sh v0,0(a0)
1020: slti v0,t0,12
1024: bnez v0,1000
1028: addiu a0,a0,2
```
Only dst is used in the loop. So ba's only use is `dst = ba`.

Therefore the target's `move a0,a1` requires ba live at the copy — the asm did it.

Given the constraints (no asm), I could try:
- Make `dst` NOT pinned and `ba` pinned: then `dst = ba` = `move <pseudo>,a1` and the loop uses the pseudo. The pin on dst may stay though (it's a pin, allowed) but I could also remove it? Removing a pin is allowed (removing levers is fine; only ADDING is prohibited). But the target needs dst in $4 (a0).

Hmm, what if dst keeps its pin and ba's value is used at the copy... 

Let me try a completely different micro-shape: `dst = ba; do { ... } while` where the first loop statement uses `ba`? no.

Honestly, time: it's 05:58; item 3 started ~05:52. Only 6 min in. I have 20-30 min. Let me try a few more ideas:

(A) Make `ba` be used by the store `*dst = tv` indirectly? no.

(B) What if the copy `dst = ba` is written as `dst = (u16 *)(tmp + (u8 *)dp);` and ba is separately used: `if (ba) {}`? Adds a branch.

(C) What if `ba` is declared `volatile`? no.

(D) What if we make `ba` a *parameter-like* alias used in the second half of the loop: e.g. write the second store as `*(ba + k) = tv;`? That changes the loop's addressing but might be equivalent: `*dst = tv` after `dst++` = `ba[1]`. Hmm! The loop:
```
tv = *src; src++;
*dst = tv; dst++;      → ba[0]
tv = *src; src += 0x35;
*dst = tv; dst++;      → ba[1]
```
If written as `*ba = tv; *(ba+1) = tv;` — the target's asm uses `addiu a0,a0,2` (dst increments), so dst is a pointer. Using ba[1] would emit `sh v0,2(a1)` — different.

(E) Accept and record a WALL? Let me first check how the launder/keepalive affect the *other* diffs (the c36/dcount swap and prologue order) — those might be fixable, leaving only the 1-insn ba issue.

Actually, maybe I should reconsider the whole thing: what if the correct lever-free approach is to keep `decoy` and the launder's *effect* via real C — e.g., the original author's `decoy` was a launder to make `ba` opaque. A real-C equivalent: use a *union* or a cast through a different pointer type to break cse: e.g.

```
u8 *pb2 = (u8 *)dp;      /* extra */
ba = (u16 *)(tmp + (u32)pb2);
```
no.

(F) What if the cse forward is blocked because the *destination* $4 is also live-in? Hmm: cse's deletion of `set (reg 5) X` requires (reg 5) dead. If $5 were live-in at the loop (it's src!), then... AH WAIT. In the target, src is in **a2** and ba in **a1**. In mine, src is in a1! So in mine, a1 ($5) is live in the loop as src → but that's AFTER the copy.

Hmm, here's a thought: if src were in a2 (as the target wants), then a1 would be free... and the copy `move a0,a1` would still be deletable.

Let me approach differently: maybe if I fix the src register (a1→a2), the whole thing cascades. src's register is a local-alloc choice. In the target, src = a2 because... the copy loop's live-in includes a1 (ba) at the block start, so src can't take a1 → a2. In mine, ba's value was folded into a0, so a1 is free at the block start → src takes a1.

So both diffs stem from the same root: cse deleting the $5 set.

So: WALL unless I find a lever-free way to keep ba live.

Hmm, one idea: what if `ba` is assigned to a *pinned* variable and the copy is not a direct copy: `dst = (u16 *)(tmp + (u8 *)dp);` where the expression is computed once into ba and reused... 

What if I write:
```
ba = (u16 *)(tmp + (u8 *)dp);
dst = ba;
```
and ALSO make the loop's increment use ba? no.

What if the launder is replaced by a real *store* of ba to a local variable that is later used? e.g. `u16 *bsave = ba;` (1 insn) — no.

OK, what about the "keepalive" asm on c36/dcount: does removing it cause the c36/dcount swap? Maybe those two diffs are separable: the c36/dcount swap (v0/v1) might be fixable by making one of them used twice.

Let me try: `df = c36 - dcount;` → the target has c36 in v0 (allocated first?). The keepalive `("r"(c36), "r"(dcount))` added a ref to both. Without it, both have 1 use. 

What if `c36` is used twice: `tmp = (df << 1) + df;` where df... no.

Try: `df = c36 - dcount;` and then use c36 again? e.g. `c36` isn't used again in the target's code.

Hmm, in the target: `li v0,36` — the constant goes straight to v0 (c36=v0), then `subu v0,v0,v1`. In mine: `li v1,36; subu v1,v1,v0`.

So c36 must be in v0 and dcount in v1. Since both are single-use, the allocator assigns... maybe decl order or statement order matters (h1 tried swapping the assignments — no change).

What if `dcount = *dp;` comes after `c36 = 0x24;` AND `df` is computed as `c36 - dcount`? Tried (h1, no change).

What about making dcount s32 vs u32? `dcount` is s32. The load `lw` → s32.

What if `c36` is `s32 c36 = 0x24;` (init at decl)? Tried (h3, 18).

Hmm.

Given the difficulty and that both remaining issues trace to the asm, let me try a couple of long-shot ideas and then record a WALL with best 18.

Long shots:
1. Wrap `dst = ba;` and the loop in a do-while(0) — tried i2 (18).
2. Use `ba` in the loop's second store: `*dst = tv;` → no.
3. Move the `src = base;` copy INTO the dst block (so src is born after ba's copy).
4. Make the loop a for loop.
5. `dst = (u16 *)ba;`

Actually — WAIT. What about the simplest possible thing: what if the two asm (launder + keepalive) are replaced by a single *real* use of `ba` in the copy loop's condition or in `iVar2`? 

Or... what if `dst = ba` is written as `dst = (u16 *)(tmp + (u8 *)dp);` and we keep `ba` as a variable used in the store: `*dst = tv` uses dst...

Hmm, let me think about `decoy`: the launder output `decoy` is a dead pseudo that the keepalive then uses. In the target's asm, where does decoy live? The target: after `ffc: move a0,a1`, no extra insn. So decoy was allocated a register but emitted nothing (the asm is zero bytes). Fine.

New idea: maybe a *dead store* to a local keeps ba live? Like `u16 *save = ba;` — that's a real move (1 insn).

OK: what if `dst = ba` is replaced by `dst = ba = (u16 *)(tmp + (u8 *)dp);`? Then ba is assigned and dst gets the value — cse forwards to `addu $4,...` and ba's set is dead. Same.

I'll try 4 quick variants and then decide.

Actually, hold on. Let me reconsider the problem: is the ba pin really honored in the target because of the launder, or is the pin honored and the copy just not folded because of the *order* (ba computed, then `dst = ba` immediately)? Mine: `addu $4,$3,$4` — that's ba's expression going into $4. So the pin IS being ignored (not just cse-forwarded; the assignment's destination is $4).

Hmm! If cse forwarded, we'd see `addu $4,...` — same. OK, consistent with cse forwarding.

Test: does the pin work when ba has a later use? i3 (`src = ba;` after) gave 19 — so the code changed. Let me look at i3's asm: if it has `addu $5,...; move $4,$5; move $5,...` etc.

Let me just try the most promising: use `ba` in the `src` assignment instead of `base`:
```
src = base;
...
ba = ...;
dst = ba;
```
→ i3 was `src = base` moved after ba. Hmm.

What about `src = (u16 *)base;` no.

Let me try: make the loop use `ba` for the first store and dst for the rest? Actually, look at the target loop's first store: `sh v0,0(a0)` — dst.

Alternatively, maybe write the copy block as:
```
dst = ba;
do {
   ...
} while (iVar2 < 0xc);
```
and add `ba = ba;`? cse deletes it.

Let me try one thing: `dst = (u16 *)((u8 *)ba);` — a cast might not be forwarded by cse? It's the same rtx (a pointer cast doesn't change the reg). Hmm.

What about `dst = ba + 0;`? cse folds.

Time to make a decision: this item looks like a WALL of the same family: "the launder/keepalive asm kept the pinned $5 value live; lever-free cse folds the $5 set into the $4 copy". Tag: `cse-hardreg-forward`? walls.txt has `cse-store-forward` (cse1/combine). Let me use `cse-store-forward` or a new `cse-hardreg-copy-forward`.

Hmm, but before giving up, let me quickly test the hypothesis that a `do{}while(0)` around the whole tail block (from `ba = ...` through the loop) stops cse1's EBB. cse1 splits EBBs at labels/branches — a do-while(0) creates a loop note but maybe no label. C0535 says it does split cse1's EBB.

Let me try wrapping the entire `{ dp = ...; ...; }` block in a do-while(0) and also try wrapping from `ba = ...` to the end.

And one more idea: what if the *second* `dst++` store is written as `*dst = tv; dst++;` (as now) but the first store uses `ba`: no.

Let me do the two do-while variants.
