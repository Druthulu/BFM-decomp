---
ts: 2026-10-22T01:29:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_7vgYtMIxlmGLJgwpkRQx
---
Hmm, all ≥10 (c1 was 9). The best is still c1 (9).

Interesting: the score class changed from "REG-caller" (c1) to "MIXED" for most.

Hmm, the class "MIXED" suggests a different kind of difference. Let me look at the diff for the best of these (v01 = 10, MIXED) vs c1 (9, REG-caller). Hmm, c1 is still the best.

Hmm, let me think about the mechanism differently. The two residuals:
1. The reloads: a5 → v1 (target) vs t0 (mine); a6 → t0 (target) vs v1 (mine).
2. The byte/const: the const → v0 (target) vs v1 (mine); the byte → v1 (target) vs v0 (mine).

Hmm! Interesting: in the target, $v1 is used for BOTH a5 (early) and the byte (later); $v0 for cw and the constant 8.

In mine: $v0 = the byte, $v1 = 8, $t0 = a5, $v1 = a6 (hmm, both a5 and a6 in t0/v1).

Hmm! Note: in the target, a5 goes to $v1 and a6 to $t0; in mine a5 → $t0 and a6 → $v1.

Hmm, what determines which caller-saved reg the reload picks? In gcc's reload.c, the reload's destination reg is chosen among the "reload regs" (the caller-saved regs available), and there's a preference for keeping the "preferred" reg.

Hmm! $t0 is special in MIPS (gcc reserves t0 for the multiply/divide results? hmm, actually gcc's MIPS has "t0" as a "scratch" for mult/div — the `mult`/`div` insns write to $t0/$t1). Hmm! In the target there are no mult/div in this function.

Hmm. Let me look at the diff of v01 to see what changed vs c1 (the class changed to MIXED).

Hmm, time is short (19:35ish). Let me think about the highest-value approach.

Given the two cracks came from the HImode-copy trick, let me think about what HImode trick applies here:
- The `s_a6 = a6` copy: the source is the stack param (a pseudo, loaded by a reload). If `s_a6` were u16/s16 → an HImode copy → hmm, the copy's value is `code = s_a6 | cw` → with s_a6 as u16, the OR would be 32-bit (the promotion) ✓ hmm, and the reload of a6 into s_a6's reg... hmm, the reload is into the pseudo directly (no separate copy) hmm.

Hmm, wait: in the target, `lw t0,20(sp)` (the a6 reload) then `or t6,t0,v0` — so the a6 value is reloaded into $t0 and used directly ✓ (no copy of a6 into s_a6!). So s_a6 and the reload are coalesced ✓.

In mine: `lw v1,20(sp)` (a6 → v1) then `or t6,v1,v0` ✓ — also coalesced ✓. So the only difference is WHICH reg the reload picked (v1 vs t0).

Hmm! So the reload's reg choice is the residual. And the byte/const swap is another local-alloc choice.

Hmm, so both residuals are "which caller-saved reg" choices. The lever: the number of live values / the order.

Hmm! IDEA: what if the reload order changes? The reloads are processed in the RTL order. In the target: a5's reload first (16(sp)), then a6's (20(sp)) — the same as mine ✓. Hmm, but the reg assignment differs.

Hmm, hmm. In gcc's reload.c, `reload1` is called for each reload in order; `choose_reload_reg` picks a reg from `reg` (the reload's reg list, in preference order) that doesn't conflict. The preference order for MIPS: hmm.

Hmm, if the preference order is [v0, v1, ..., t0, t1...], then the first reload (a5) would get v0 — hmm, but $v0 is used for cw (the lui v0,0x6400) → a conflict → so a5 gets v1 ✓ (target!) hmm, and a6 gets... the next free: v2? hmm, the target has t0.

Hmm! In mine, a5 got t0 and a6 got v1. Hmm, so in mine the assignment order was different.

Hmm, hmm. Let me look at the actual diff of v01 (MIXED, 10) — hmm, that's worse than c1 (9).

Hmm, let me look at c1's diff again:
```
  register pairs (mine -> target, count): v1->v0 x3, t0->v1 x2, v1->t0 x2, v0->v1 x2
  replace mine[1:3] target[1:3]
        1  lw	t0,16(sp)                       | lw	v1,16(sp)
        2  lw	v1,20(sp)                       | lw	t0,20(sp)
  replace mine[7:9] target[7:9]
        7  or	t6,v1,v0                        | or	t6,t0,v0
        8  addiu	v0,t0,256                    | addiu	v0,v1,256
  replace mine[58:60] target[58:60]
       58  lbu	v0,0(a1)                       | lbu	v1,0(a1)
       59  li	v1,8                            | li	v0,8
  replace mine[61:64] target[61:64]
       61  sh	v1,-2(t0)                       | sh	v0,-2(t0)
       62  sh	v1,0(t0)                        | sh	v0,0(t0)
       63  sb	v0,-5(t0)                       | sb	v1,-5(t0)
```
So: mine has a5→t0, a6→v1, cw→v0 (the lui v0,0x6400 is the same in both ✓), the byte→v0, the const→v1.
Target: a5→v1, a6→t0, the byte→v1, the const→v0.

So mine's t0/v1 are used for the reloads and v0/v1 for the byte/const; the target's v1/t0 for the reloads and v0/v1 for the byte/const.

Interesting: in the target, the byte is in $v1 and the constant in $v0. In mine, the byte is in $v0 and the constant in $v1.

Hmm! So the byte/const swap is a LOCAL-ALLOC order issue (like func_80180480!) and the reload swap is a RELOAD issue.

Hmm, so two separate flips needed.

Hmm, let me focus on the byte/const flip first (it's a local-alloc order like 80180480). The lever there: the pseudo creation order or the priority.

In mine: the byte's pseudo gets $v0 (the first local reg) and the constant gets $v1. In the target: the constant gets $v0 and the byte $v1.

⇒ The constant's pseudo must be created FIRST (or have a higher priority).

The source order:
```c
param_2 = param_2 + 1;
sVar2 = 8;             <- the constant (sVar2's second set)
bVar1 = *param_2;      <- the byte
```
Hmm! But sVar2's FIRST set is at the loop top: `sVar2 = *(short *)param_2;` → so sVar2's pseudo is created FIRST (at the loop top) ✓ and the byte's pseudo later.

Hmm! So sVar2's pseudo has a lower number ✓ but it gets $v1 in mine ✗.

Hmm, so it's the priority again: the byte (shorter live) wins.

Hmm! To flip: the byte's live must be LONGER than the constant's, or the constant's refs more.

The byte's live: from the lbu to the sb. The constant's: from the li to the second sh.

In the source:
```c
            ((u8 *)param_1)[0xC] = *param_2;
            param_2 = param_2 + 1;
            sVar2 = 8;
            bVar1 = *param_2;
            param_2 = param_2 + 1;
            *(short *)((u8 *)param_1 + 0xE) = clut;
            ((u8 *)param_1)[0xD] = bVar1;         <- the byte's use
            *(short *)((u8 *)param_1 + 0x10) = sVar2;   <- the constant's use 1
            *(short *)((u8 *)param_1 + 0x12) = sVar2;   <- the constant's use 2
```
So: the byte's use comes BEFORE the constant's uses → the byte's live is SHORTER ✓ (as I said).

⇒ To make the constant's live shorter, its uses must come earlier — but the source order determines the code order ✗ (the target's code has the sh 0x10, sh 0x12 before the sb 0xD? hmm!).

Let me check the target's code order at 61-63: `sh v0,-2(t0)` (0x10), `sh v0,0(t0)` (0x12), `sb v1,-5(t0)` (0xD). So the target's ORDER is: the constant's stores (0x10, 0x12) BEFORE the byte's store (0xD)!

And in mine: `sh v1,-2(t0)`, `sh v1,0(t0)`, `sb v0,-5(t0)` — the same ORDER ✓ (the scheduler reordered the stores: the source has the sb (0xD) before the sh's (0x10, 0x12) but the code has the sh's first ✓).

OK so the order matches ✓; only the regs differ.

So: in the target, the constant's pseudo (created first at the loop top) got $v0 and the byte $v1. In mine, the byte got $v0.

Hmm! Since the constant's pseudo (sVar2) is created at the LOOP TOP (its first set is `sVar2 = *(short *)param_2`), and the byte's pseudo is created later → by pseudo number, sVar2 should get $v0 ✓ TARGET. But mine gives the byte $v0 ✗.

Hmm! Unless the priority overrides (as in func_801415C0 where the higher-priority local got the lower reg ✓). So in mine, the byte has the higher priority.

The byte: refs 2 (set + 1 use), live = from the lbu to the sb (in the code: the lbu at 58 and the sb at 63 → but the live is computed on the pre-schedule RTL).

The constant (sVar2): refs 3 (set + 2 uses) hmm, plus the loop-top set and the switch use → 5 refs; live = from the li to the last sh.

pri(byte) = 1*2/live_byte; pri(const) = 2*5/live_const = 10/live_const.

If live_const ≈ 10 → pri = 1000; pri(byte) = 2/live_byte ≈ 2/4 = 500. Hmm, then the constant would win ✗ (mine gives the byte $v0).

Hmm, my estimates are off. Let me get the real numbers with the alloc table (the dump machinery works). Hmm, but the TU is huge (resident_jr_800D128C.c) — the dump would be big but the alloc table reads the function's section ✓. Hmm, the standalone TU approach worked for 80180480 ✓. Let me do that for 800D2650: a standalone TU with the candidate + padding, then the alloc table.

Hmm, but the standalone TU's register allocation might differ from the real one (the earlier standalone dump for 80180480 gave confusing results). Hmm.

Hmm, time. Let me think about the most promising lever for the byte/const flip:

The constant's live range is long because it's set at the li and used in two stores at the end. The byte's live is short.

To flip, I want the constant's live SHORTER or the byte's LONGER:
- The byte's live: from the lbu to the sb. If the byte were loaded EARLIER (e.g. at the loop top), its live would be longer ✓ → its priority would drop → the constant wins ✓.

Hmm! Can the byte be loaded earlier? `bVar1 = *param_2;` — the byte is read from param_2 AFTER `param_2 = param_2 + 1`. Hmm, so it's read at a specific point. Semantically, could the byte be read at the loop top? The source reads `((u8 *)param_1)[0xC] = *param_2;` then `param_2 = param_2 + 1;` then `bVar1 = *param_2;` — so the byte is the SECOND byte of the param_2 sequence. Hmm, reading it earlier would read a different byte ✗.

Hmm. Unless... hmm.

- The constant's live: from the li to the last sh. If the li were LATER (closer to the stores), the live would be shorter ✓. The li is `sVar2 = 8;` — it could be moved down to just before its first use ✓✓ (semantically fine — sVar2 is not used between)! Hmm, but the source has `sVar2 = 8;` before `bVar1 = *param_2;` and the stores come later. Moving `sVar2 = 8;` to just before `*(short *)((u8 *)param_1 + 0x10) = sVar2;` → the constant's live = from the li to the last sh (2 uses) → shorter ✓✓.

Hmm! But the code order: the target has `li v0,8` at 59 (right after the lbu at 58) → so the li is EARLY in the code ✗. Hmm! If I move the assignment later in the source, the li would move later in the code ✗ (the target has it early).

Hmm, unless the scheduler moves it back. Hmm, the li is a constant materialization — sched1 might hoist it? Hmm.

Hmm, so the target's code has the li early (at 59) and the byte's lbu at 58 — hmm, so both are early and the CONSTANT is in $v0 (created first ✓) and the byte in $v1.

Hmm, so in the target, the ORDER of the pseudo creation (sVar2 first, then bVar1) → the reg assignment follows the pseudo order ✓ (not the priority!). And in mine, the byte won $v0 ✗.

Hmm! Hmm, so what made mine differ? Hmm.

Hmm, hmm: in mine, the li is at 59 and the lbu at 58 — hmm, the same order as the target ✓. Hmm, but the regs are swapped.

Hmm! So the pseudo creation order is the same, but the assignment differs → so it IS the priority.

Hmm, in the target: the constant (sVar2) has the higher priority → $v0. In mine: the byte has the higher priority → $v0.

Hmm, so the priorities differ between the two compilations?! The only difference is the source spelling... hmm, in c1 vs the target. Hmm.

Hmm, hmm! Hold on: maybe the difference is that in the target, sVar2's pseudo has MORE refs (because the switch's use of sVar2 is in the same iteration). Hmm, the same in mine.

Hmm. Hmm, let me just try the "move the constant's assignment later" idea and a few other live-range tweaks:
- w-a: `sVar2 = 8;` moved to just before the 0x10 store.
- w-b: `bVar1 = *param_2;` moved earlier (right after `((u8*)param_1)[0xC] = *param_2;`? no — the byte is read after the increment).
- w-c: `sVar2 = 8;` moved to just after `bVar1 = *param_2;` (i.e. the order swapped — tried in v02 → 10).
- w-d: the constant in its own variable (tried, r1 → 17).

Hmm, hmm.

Let me step back and consider the TIME. It's ~19:40. I've spent 3.5h. The developer's rule for a WALL: ≥20 min and ≥30 tries. func_800D2650 currently has 6 + 23 = 29 scored tries. One more try → 30 ✓. And the time: 18:19 → 19:40 = 81 min ✓.

So I can record a WALL for func_800D2650 with 30 tries ✓ and 81 min ✓.

But let me try a few more promising things first — the HImode trick on the two locals:
- What if bVar1 were `u8` ✓ (already) and the constant `sVar2` were... hmm.

Hmm, let me think about the reload swap once more. The target: a5 → $v1, a6 → $t0. Mine: a5 → $t0, a6 → $v1.

Hmm! What if the source used a5 and a6 in a different order? (PRE_B/PRE_D — tried: v02/v04 → 10, v06/v08 → 13.) Hmm.

Hmm, what if `s_a6` were eliminated (code = a6 | cw) — tried (PRE_E = v05/v07 → 10/13).

Hmm.

OK, let me try a couple of things aimed at the byte/const flip and the reload flip:
1. The `clut` variable's type (int vs u32 vs s32) — clut is in t5 ✓ (matches) hmm.
2. `code` as u32 vs s32 ✓ (u32).
3. `cw` as u32 vs s32 — hmm! `cw` is in $v0 (the lui) ✓ matches.
4. The order of the declarations: `u32 s_a6` before `u32 code` ✓.
5. The declaration order of the locals: s_a6/code/cw/clut/bVar1/sVar2 — permuting could change the pseudo order! Hmm! The pseudo creation order follows the RTL, not the declarations. Hmm.

Hmm, hmm. What about the HImode trick on `bVar1`? It's already u8 (HImode) hmm. And sVar2 is short (HImode) hmm. Both HImode.

Hmm! What if the byte were a `char` (signed) vs u8? Hmm, the load would be `lb` vs `lbu` ✗ (the target has lbu).

Hmm.

OK. Let me try a focused batch: vary the ORDER of the three "pre" statements in all 6 permutations, and the position of `sVar2 = 8` (3 positions), and the type of `clut` (3) → ~30 variants. Then score and take the best.

Let me write it.

Actually, let me first check the diff of v01 (MIXED, 10) to see whether the class change tells me something (MIXED = a mix of diff kinds). Hmm, c1 = 9 (REG-caller) is better.

Hmm, let me instead try the permutations — that's the most likely lever for the reg assignment order.

Let me write the batch: the "pre" block in all 6 orders of the three statements (cw=0x64000000, s_a6=a6, code=s_a6|cw, cw=a5+0x100, clut=...) hmm, the statements are dependent (cw is reused). Let me define the pre-block as a sequence of 5 statements with dependencies:
 A: cw = 0x64000000;
 B: s_a6 = a6;
 C: code = s_a6 | cw;   (needs cw=A and s_a6=B)
 D: cw = a5 + 0x100;   (overwrites cw)
 E: clut = (cw << 6) | 0x16;  (needs cw=D)

Valid orders: A before C; B before C; D before E; and A before D (since D overwrites cw, C must come before D).
So the constraints: A < C, B < C, C < D, D < E. That's a chain: A,B < C < D < E. The orders are the interleavings of {A,B} before C: 2 orders (AB or BA) → only 2 valid orders! Hmm, that's what I tried (PRE_A and PRE_C).

Hmm, unless I use different variables (e.g. a separate variable for the second cw) → then the constraints loosen ✓.

Let me use a separate variable `cw2` for the a5 value:
 A: cw = 0x64000000;
 B: s_a6 = a6;
 C: code = s_a6 | cw;
 D: cw2 = a5 + 0x100;
 E: clut = (cw2 << 6) | 0x16;
Now the orders: all interleavings of A,B,C with D,E anywhere after... hmm, but D and E must be in order (D<E) and E must be before the loop ✓.

Hmm, but using cw2 instead of cw changes the code (an extra register for cw2? hmm, cw2 is short-lived → it'd be a caller-saved reg ✓ maybe the same reg).

Hmm. Let me try:
 P1: A,B,C,D,E (the original)
 P2: B,A,C,D,E
 P3: A,C,B,D,E — hmm, C needs B ✗.
 P4: D,E,A,B,C (a5 first)
 P5: D,A,E,B,C hmm, E needs D ✓
 P6: A,B,D,E,C hmm, C needs A and B ✓ and C < D is not needed now (different variables) ✓
 P7: D,E,B,A,C
 P8: B,D,E,A,C

Let me generate ~8 orders × 4 other tweaks = 32variants.

Let me write it.
