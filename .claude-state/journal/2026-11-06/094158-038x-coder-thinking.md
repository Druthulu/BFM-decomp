---
ts: 2026-11-06T16:41:58Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PHwGq4cKhfdIZlTCLIBQ
---
All 8. The structural variants don't change allocation.

Let me think once more about what pseudo could occupy $2. 

AH WAIT. What about the **second argument setup** `addiu a1,sp,32`? The address `sp+32` is computed into a pseudo. If that pseudo were in $2... but it's an argument → $5.

What about the **stack slot address for sp28**? Different block.

Hmm, what about making the call's result *also* used as an argument to the next call? No.

Let me look at this from the global-alloc angle: what if ret is NOT local to the block but global, and global-alloc assigns $3 due to its copy preference? Global-alloc's copy preference for the call result is $2. Hmm.

Actually, let me test whether a *global* ret (live across blocks) could get $3. If ret is live across the branch into the else-if block (block 3?), the target's ret is local... but maybe global-alloc with a copy pref to $2 and $2 being unavailable (because the call result pseudo is also...). Hmm.

Let me try: use ret in the switch blocks (e.g., in a dead-ish way) to make it global. But that would add instructions.

Alternatively: maybe the original source had `ret` declared as a **static/global**? No.

Let me look at the actual ROM's other functions in md_MAIN_041 for a similar call+test pattern and see how they look. Actually, let me look at the decomp's neighboring functions to see the code style — maybe there's a helper macro. 

Time check: I've spent ~25 min on item 1. Let me count tries: 13 + 5 + 8 = 26 scored candidates (plus orig). I need ≥30 for a WALL. Let me do one more batch of ~8 quick variants and then wall it if nothing.

Batch 4 ideas:
1. ret u32, m u32.
2. ret u16 with the andi on a SImode copy: `m = ret & 0x8000` where m s32.
3. `s32 m = ret & 0x8000;` at decl (init at decl) — with ret assigned later.
4. `u16 ret; u16 m;` with `if ((u32)ret == 0)`.
5. Use `s32 ret; u16 h; h = (u16)ret;` and test h (branch on h) — no.
6. `volatile` no.
7. Two separate variables: `s32 r0 = func(...); s32 ret = r0; m = ret & 0x8000;` with r0 used in the andi? no.
8. What about `if (ret == 0)` where ret is a **s16** and the comparison is `if (ret == 0)` — we saw 10.
9. `s32 ret; ... if (!(ret & 0xFFFFFFFF))` — folded.
10. Try `ret` as `u32` and the andi mask as `0x8000u`.

Also: what if `m` is declared as a **pointer-width bitfield** or a struct field so that the andi's output is a *memory*? No.

Hmm, actually let me revisit one thing: the target's `andi v0,v1,0x8000` writes $2, which was the call result's reg. In local-alloc, after the call result pseudo (ret) is allocated $2, the andi's output m could reuse $2 only if ret is dead. In the target, ret is in $3, so $2 is free from the start for m. So m gets $2 as the first free register. That means ret is NOT in $2.

The ONLY way ret avoids $2 is if $2 is occupied over ret's live range. Q = zero_extend (r16).

Is there another construct that creates a Q in $2 over that range with no extra instruction? 

What if the call's *return value* is used twice: once as HImode and once as SImode? The HImode use would create a subreg, and the zero-extend... 

Hmm, actually: what if `ret` is u16 and the branch tests `ret` — the zero_extend Q appears. The extra `andi 0xffff` is because of the HImode compare. BUT what if the branch tests a **u32 variable that holds the zero-extended value already**? Like:

```c
u16 ret;
s32 r;
r = func(...);       // r = $2
ret = (u16)r;        // HImode copy: move $3,$2 (r live? no) ...
if (ret == 0) ...
```
Hmm.

What if:
```c
u16 h;
s32 ret;
ret = func(...);      // ret = $2
h = (u16)ret;         // HImode copy: move $3,$2? (ret live -> yes)
if (h == 0) ...       // zero-extend -> andi $4,$3,0xffff; beqz $4
```
Extra.

What if the branch is on `ret` (SImode) and h is used elsewhere (to occupy $3)? Then ret=$2, h=$3 → move $3,$2 for h; branch beqz $2. Target branches $3. No.

Hmm hmm.

What if the order is reversed: h = (u16)call; ret = h (extend)? 

Let me try yet another idea: **the call result assigned to `m` and `ret` derived via `m` but the andi reads ret**. 

```c
s32 m;
s32 ret;
m = func(...);     // m copy sugg $2
ret = m;           // if m lives -> ret gets another reg
if (ret == 0) {} else if ((m = ret & 0x8000) != 0) ...
```
For m to live across `ret = m`, m must be used after. What if the branch is `if (m == 0)`? Then the branch tests $2. No.

What if there's an intermediate: `m = func(...); ret = m; if (ret == 0) {} else if ((m = ret & 0x8000) != 0)` and m's REG_DEAD at `ret = m` is suppressed because m is used in the *switch* later? no.

I think I should try the u16 variants more systematically since r16 got closest. The missing piece: the zero-extend pseudo. What if we make the zero-extend insn *unnecessary* by having the branch compare the SImode `ret` (not the u16)?

What if we have BOTH: `u16 h` (occupies $2 via the zero-extend) and `s32 ret` (the branch operand)? For the zero-extend to exist, some code must use h in an SImode context. And the branch must test ret. E.g.:

```c
u16 h;
s32 ret;
ret = func(...);     // ret=$2?
h = (u16)ret;        // HImode copy -> move $3,$2? or tie
m = h & 0x8000;      // andi ...
if (ret == 0) ...    // beqz ret
else if (m != 0) ...
```
Hmm, `ret = func(...)` gives ret the copy sugg $2; h = (u16)ret is a subreg copy → move? The HImode pseudo h... Then the andi on h: `andi $?,h,0x8000`. The branch on ret. Allocation: ret=$2 (copy sugg), h maybe $3.

Target needs ret=$3. So h must take $2. h's copy from ret is a pseudo-pseudo copy; if ret dies there (no), tie. ret is used at the branch so it doesn't die → h gets a copy suggestion to ret's reg ($2)? For pseudo-pseudo, combine_regs either ties or returns 0 (no suggestion). Let me re-read: pseudo-pseudo, if the source dies → tie; else return 0. So no suggestion. So h gets allocated by priority: ret (copy sugg) first → $2; h → $3. Not target.

What if h's copy is from the call result directly (hard $2)? `h = (u16)func(...)` gives h a copy suggestion $2! Then ret = h (extend) — ret is SImode from h, needs zero_extend (extra insn). Hmm: 
```c
u16 h = (u16)func(...);   // h: move $3,$2? or tie to $2
s32 ret = h;              // zero_extend -> andi $?,h,0xffff
if (ret == 0) ...
```
Extra.

I think the zero-extend is unavoidable for the HImode route.

Let me now consider that maybe the item is a WALL and the wall tag would be something like "lreg-copy-pref-call-result" — but the moves/walls list has "global-copy-pref" for a similar case. Actually there's a wall tag "lreg-copy-pref-dying-base" and "lreg-tie-dying-pin". Ours: the call-result pseudo's copy preference gives it $2; the target needs it in $3 (i.e., $2 occupied). The nearest tag: `global-copy-pref`? That's global-alloc. Ours is local-alloc: `lreg-copy-pref-...`. Let me name it `lreg-copy-pref-call-result` or reuse `lreg-copy-pref-dying-base`. Hmm, the brief says wall = a tag from walls.txt or a new `<pass>-<what>`. I can create `lreg-callresult-copy-pref`.

But before declaring, I need ≥30 scored tries (I have ~26) and ≥20 min (yes). Let me do 6-8 more variants to be safe and give the best shot.

More variants (batch 4):
1. `s32 ret; s32 m;` with `m = ret & 0x8000;` and branch on `ret` — hoist (done, 9).
2. `u32 ret`.
3. `s32 ret; u16 m;` andi HImode.
4. `s32 ret;` no m, `if (ret & 0x8000)`.
5. `s32 ret; s32 m;` with `if (ret == 0) {} else if ((m = ret & 0x8000) != 0)` but ret declared `volatile`? no.
6. `s32 ret; s32 m;` where m is `static`? no.
7. `s32 ret; s32 m;` with `ret = func(...); if (ret == 0) {} else if ((m = ret & 0x8000) != 0)` and an extra `if (ret)` no.

Hmm, let me think about the *and* being written as `ret % 0x10000 >= 0x8000`? no.

What about using `(ret << 16) >> 16`? no.

Let me try the **u16 with the branch on a zero-extended SImode temp that is NOT an extra insn**: what if the zero-extend is combined into the branch's delay slot? No.

Actually, hold on! What if we write the test as `if (ret == 0)` where ret is `u16` but the *comparison operand* is the SImode value `m`... no.

New idea: what if the C uses a **signed s16** and the test is `if (ret < 0 || ret > 0)`... no.

Let me try `u16 ret` with the test `if ((s32)ret < 1)` and `if (ret == 0u)`.

And one more idea: `u16 ret` and the test `if (ret == 0)` but declare ret as `unsigned short` via a typedef that gcc treats as... same.

Honestly, let me try the u16 route with `m` SImode (w1_r16 was m s32 → 104 ins, 7). The diff showed `andi $2,$3,0xffff` and `beqz $2`. What if `m` is s32 and the branch uses `(u32)ret`... same.

Hmm, what about making the branch use the *raw* register by comparing to a HImode constant that is 0 but written as `(u16)0`? same.

Let me look at the zero_extend: it's `zero_extend:SI (subreg:HI (reg:SI 77) 0)`. The mips.md zero_extendhisi2 pattern might generate `andi` (as we saw). What if instead the HImode value were *signed* (sign_extend) → sll/sra (2 insns).

What if the HImode value is known to be zero-extended because it came from an `and` with 0xFFFF? We can try:

```c
u16 ret;
s32 t;
t = func(...);          // t = $2
ret = (u16)(t & 0xFFFF); // hmm
if (ret == 0) ...
```
The `t & 0xFFFF` in SImode then truncated to u16 → gcc folds the truncation of the andi: `(subreg:HI (and:SI t 0xffff))`. In RTL simplification, a truncation of an and with 0xffff might be simplified to just the subreg (the and is redundant), losing the knowledge. OR it might keep the andi and then know the upper bits. Let me just test:

Variant: `u16 ret; s32 t; t = func(...); ret = t & 0xFFFF; if (ret == 0) {} else if ((m = ret & 0x8000) != 0)...`

Hmm, but then the andi 0xffff would appear (as part of ret's definition) — target has no such insn. Unless gcc folds it into the copy and keeps a plain move while still knowing... unlikely.

What if `ret = t & 0x8000`? no.

OK let me just run 8 more variants and then wall. Actually, let me reconsider the problem completely differently:

**What if the target's move v1,v0 is a copy of the call result to a variable that is used in the SWITCH blocks (dead) and flow didn't delete it?** Let's look at the target: is v1 used anywhere after 354? Let me scan the target for v1 ($3):
- 34c move v1,v0
- 350 beqz v1
- 354 andi v0,v1
- 3a8 move v1,v0 (after func_801632F0! `3a8: move v1,v0`) — that's the switch value copied to v1.
So $3 is reused for the switch value. So ret isn't live past 354.

OK so ret dies at 354.

Now, **what if `m` is the call result's *other* copy**... no.

Let me try to see if the *pinned* build's lreg dump shows the pins as hard regs and whether the copy move is `(set (reg 3) (reg 2))`. That would confirm. Let me dump orig.c quickly (it's cheap) — actually not needed.

Let me think about the `sp20` array: `s32 sp20[2];` and `(s32) sp20` is passed. The address computation `addiu $5,$sp,32` — the pseudo for sp is $fp.

Hmm, what about the `sp28` variable? It's in the switch blocks.

What if I move `sp28`'s address computation... no.

OK, let me try one specific promising thing: **make ret live across the call** (so global-alloc handles it and gives $3?). For ret to be live across the call, it must be set before and used after. E.g., initialize ret before the call? `ret = 0;` then `ret = func(...)` — the init is dead (flow deletes). 

What about `ret = a0;` before? no.

Hmm, what about making the call result assigned to a variable that already has a value (init at decl)? `s32 ret = 0; ret = func(...)` — flow deletes the 0.

I'll run the last batch.

Actually, wait! Let me reconsider the **`m` copy suggestion** approach once more, because priority math said m (20000) > ret (15000) if suggestions are equal. How can m get a copy suggestion to $2? A copy from a hard reg $2. The only $2 source is the call result. What if m is assigned the call result and ret is assigned... 

```c
s32 t;
s32 ret;
s32 m;
t = func(...);        // t: copy sugg $2
m = t;                // m: pseudo copy; t dies here? t is used at ret=t too...
ret = t;
```
Hmm, order: if `m = t` and `ret = t` both, t dies at the last. At `m = t`, t doesn't die → no tie, no sugg. At `ret = t`, t dies → ret ties to t. So t and ret share $2; m separate.

What if `m = t` is last: at `m = t`, t dies → m ties to t ($2). Same.

What if we want m to get a *copy suggestion* to $2: only a hard→pseudo copy does that. So m = (some hard reg value). Only the call result is hard $2.

So: `m = func(...)` gives m the copy sugg $2. Then ret must be a copy of m that survives (m live after). If m is live after the copy, it's used at the andi. Then the andi reads m ($2). Target's andi reads $3. UNLESS the andi's input is ret and m is live for another reason...

What if m is used in the branch? `if (m == 0)` → branch on $2. No.

What if m is used in BOTH: `if (m != 0)` and the andi? Target's branch is on ret=$3.

Argh.

What if ret is derived from m via a **HImode copy**, making the move v1,v0 and ret HImode; then the branch on ret needs a zero-extend (extra). No.

Let me try one more creative shape: use a **union** to read the call result as u16 for the test and as s32 for the andi, with the union forcing a stack store? No.

I'll do the final batch and wall it.

Actually, hold on. Let me reconsider the possibility that `m` gets $2 as a **hard-reg copy from the call result** and `ret` is the andi input. Here's a shape:

```c
s32 m;
s32 ret;
m = func_801638A0(...);   // m: copy sugg $2 -> m = $2
ret = m + 0;              // combine folds? maybe not: +0 with a pseudo is folded by combine
if (ret == 0) ...
```
`m + 0` is folded at tree/fold level.

What about `ret = m | 0`? folded.

What about `ret = m ^ 0`? folded.

What about `ret = m * 1`? folded.

What about a **bitfield**: `ret = (m << 0)`? folded.

What about `ret = m` but m used at the andi:
```c
m = func(...);        // m = $2 (copy sugg)
ret = m;              // copy
m = ret & 0x8000;     // andi writes m, reads ret
if (ret == 0) ... else if (m != 0) ...
```
At `ret = m`: m doesn't die? m's next use is... `m = ret & 0x8000` is a *set*, not a use. So m dies at `ret = m` → tie ret to m → both $2. Hmm.

Unless there's a use of m between. What if the branch tests m? no.

What if we use `m` in the andi as an input too: `m = m & ret & 0x8000`? That's `and $2,$2,$3` then andi? Two insns.

OK. Let me also try: **`ret` used as the call's argument in the else arm**? no.

Let me run batch 4 (8 variants), then wall.

Batch 4:
1. u32 ret, u32 m.
2. s32 ret, u16 m.
3. s32 ret, m; branch `if (ret == 0) {} else if ((m = ret & 0x8000))` with ret declared `u32`.
4. `u16 ret; s32 m;` + `if ((u32)ret == 0)`.
5. `u16 ret; s32 m;` + `if (ret < 1)`.
6. `u16 ret; u16 m;` + `if (ret == 0)`.
7. `u16 ret; s32 m;` + `if (ret == 0u)`.
8. `u16 ret; s32 m;` + `if ((s32)(u16)ret == 0)`.

Let me generate these quickly by editing w1_r16's text.
