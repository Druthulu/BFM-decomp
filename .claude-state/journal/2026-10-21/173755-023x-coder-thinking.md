---
ts: 2026-10-21T23:37:55Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG10r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_stO7X8qJUJeves5SrcOB
---
Key: "A named derived pointer `q = p - k` that cse keeps as a REGISTER address (`find_best_addr`, `cse.c:2656-2721`) — the `la` lever."

Hmm. Also "Refused as closes: ... a pointer alias invented only to dodge cse." — so inventing a pointer alias just to dodge cse is refused! That's a constraint on what counts as a real crack.

Hmm. That's a problem for our approach. So the "spelling the same address differently to dodge cse" approach is refused as a close. But we need to be careful — the refusal is about "a pointer alias invented only to dodge cse" (i.e. inventing an alias with no source justification).

Hmm, wait. Let me reconsider the whole thing. Maybe there's a cleaner structural change: what if the *order* of statements changes so that gcc naturally emits both addiu's?

Actually, let me reconsider: maybe the real difference is that in the target, the pointer sp+24 is computed in a1 directly and the value is never in a register. The launder forces that.

Hmm, what if the actual original source (game code) looked different? The target is the original game binary. The original game C probably was:

```
func_800D20C0(sp10, sp10+4, 1);
func_800D23D0(sp10+4);
```
with sp10 a local array — and the real compiler (id for MIPS, maybe a different gcc) produced the target. Our gcc 4.x-ish produces s0-held. Hmm.

But the point of this exercise: the def in src was reverse-engineered with a launder; we want a lever-free C that still scores 0.

Let me reconsider the diff. Actually wait, I should double check: what does the diff look like more fully? "mine 120 ins, target 119" and register pairs s1->s0 x13, s0->s1 x8. The whole function is 119 ins, and the diff is 29 — that's a lot of differences, more than just the s0 thing. Because a1.c differs from the target in the loop structure too? Let's see: the target has the loop with `do { } while (i <= 0)` executed once... Actually target insn 50-55:
```
50 move s1,v0
51 sll v0,v0,0x10
52 blez v0,5f94  (loop back to 27)
53 nop
54 j 60e4
55 nop
```
So it's a loop. And the source has `i = i+1; } while (i <= 0);` with i an s16. Target: `addiu v0,s1,1; ... sll v0,v0,0x10; blez v0` — so the comparison uses s16 semantics.

OK. So the differences in mine vs target: since mine has s0 = sp+24 (extra sw/lw of s0) and the target uses s0 = param_1, all the `s0`/`s1` references differ → the diff tool reports many mismatches.

Actually the diff tool probably aligns by register equivalence. "register pairs (mine -> target, count): s1->s0 x13, s0->s1 x8" — it found 13 places where mine uses s1 and target uses s0, etc. So it's a register permutation issue: mine has s0↔s1 swapped relative to target.

Hmm! That's interesting. mine: s0 = sp+24 (callee-saved), s1 = param_1. target: s0 = param_1, s1 = loop counter. So mine's s1 = param_1 ↔ target's s0, and mine's s0 = sp+24 ↔ target's s1 = the loop counter (s1=zero at insn 25, move s1,v0 at 50).

So if we could make gcc keep sp+24 out of a register, mine would have s0=param_1, s1=loop counter, matching target.

So the key fix is exactly: prevent the sp+24 value from living in a callee-saved register.

Ideas within the "real C" catalog:
- "A named derived pointer `q = p - k` that cse keeps as a REGISTER address — the `la` lever." Hmm.
- §349: re-assign a base pointer so n_times_set > 1 → kills the address GIV → rematerialised addiu.

Let's think about §349's mechanism: a pointer variable `p` (holding a base address) is re-assigned at the end of the loop body → n_times_set > 1 → the address is no longer a single GIV → gcc must recompute the address from the base each time → rematerialised `addiu $aN,$sp,K`.

In our case, is there a "base pointer variable"? The address sp+24 is derived from the frame (sp10's slot). There's no pointer variable; gcc invented a pseudo for the address.

Hmm, but what if we introduce one? E.g.:
```
u16 sp10[6];
u16 *p1 = sp10 + 4;
func_800D20C0(sp10, p1, 1);
func_800D23D0(p1);
```
Here p1 is a pointer variable. gcc's local-alloc: p1 is a local whose value is the address sp+24. It might allocate it to a register (s0) and keep it across the call → same problem. Or gcc might see p1's value is a constant and rematerialize.

Hmm, actually gcc for a local variable with a constant address value: local-alloc might decide to keep it in memory (stack) or in a reg. With `n_times_set=1` and the value being a constant, gcc's reg allocator would rematerialize it into a register each use — that would give `addiu a0,sp,24` at both places! And no s0 needed.

But in a1.c, we have p0/p1 assigned then used, and the diff showed gcc DID keep it in s0. Hmm, but that's without the asm. The asm is what forced the register.

Wait, I need to recheck: a1.c has p0/p1 as variables with launder removed, and gcc kept sp+24 in s0. So gcc chose a register for the derived pointer. That's the "derived pointer kept as a REGISTER address" — the `la` lever per C0505: "A named derived pointer `q = p - k` that cse keeps as a REGISTER address (find_best_addr, cse.c:2656-2721) — the `la` lever."

Hmm! "the `la` lever" — meaning the ORIGINAL had an `la` macro (load address) that was a lever. Here the lever is the launder.

OK. Let me consider: maybe the fix is to make p1 a *volatile* pointer? No, volatile would force a memory load.

Alternative: make the pointer's assignment happen twice (n_times_set > 1) in a way that's a real structural change. E.g.:

```
u16 *p1;
p1 = sp10 + 4;
func_800D20C0(sp10, p1, 1);
p1 = sp10 + 4;      // ← hmm identity
func_800D23D0(p1);
```
Identity again.

But what about §349 style: re-assign the base pointer to a *different* thing at a point. Hmm.

Alternatively: what if we make the first call's second argument use a *different array element* spelling that is genuinely a different object?

Hold on. Let me reconsider the target semantics once more. Maybe I mis-assumed the stack layout. Target: a0 = sp+16, a1 = sp+24, and the stores `sh zero,20(sp)`, `sh zero,18(sp)`, `sh zero,16(sp)`, and `lhu v0,26(sp)` (sp10[5] = sp+16+10 = sp+26 ✓). So sp10 is at sp+16, 6 halfwords → sp+16..sp+27. p1 = sp10+4 = sp+24 ✓.

OK so both uses are sp+24.

Now here's a thought: what if the *second* call's argument is spelled via a pointer that was *modified* in between? Like the original game code might have had `p = sp10+4; ... func_800D20C0(p0,p,1); ... func_800D23D0(p+0);`. Then p+0 == p. gcc: p+0 folds to p. Hmm, and the "second set" of p... 

Actually! §145(b): "ANY second SET of a pseudo in the address's equivalence chain (in-place `p += K`, `p = r;` copy, or an asm re-tie) kills the fold; the pass is cse and the gate is invalidate's reg_tick++".

So `p += 0;` — an in-place add of 0! That creates a second set of p. Is that an "identity-statement launder"? Hmm, `p += 0` is an identity... The brief's list of forbidden: "identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack". The example given `w = (w>>16<<16)|x` is an identity *value* statement. And "identity address spellings" would be e.g. writing the same address two different ways.

Hmm, `p += 0` is a pointer-bump that the cookbook explicitly lists as a legit "second set" technique (§145(b)), and moves.md line 44 shows "p = *abase; p += 0x2D (self-reassign stales cse (plus p K) equiv, bump chain stays addiu)" — a MATCH there. And the W01 move "field post-decrement per arm (f--; ...)".

But `p += 0` might compile to nothing (gcc folds += 0). Let's test empirically.

Honestly, the fastest path: try a bunch of candidates and see which scores 0. Let me set up an efficient loop.

Let me write candidate c1..cN and score them. Scoring takes ~10-20s each apparently (the earlier run took a bit). Let me time it.

Let me first check: what compile flags / how long? The earlier scoring call seemed quick enough.

Let me create candidates. I'll use the Write tool for each candidate (it's my own file, under .run).

Candidate list for 80180D54:

c1: p1 as a derived pointer with two sets:
```
u16 *p1 = sp10 + 4;
func_800D20C0(sp10, p1, 1);
func_800D23D0(p1);
```

c2: same but p1 = sp10+4 spelled via u8* cast for one use.

c3: p1 declared, assigned, then `p1 = p1 + 0;`? hmm.

c4: Use a separate pointer variable for the second call assigned from the first: `u16 *q = p1;`

c5: change the order: `func_800D23D0(sp10 + 4);` first? No, order matters.

c6: make sp10 a pointer to a static? No, must stay local (stack).

Hmm wait. Actually, here's another thought. What if we give the array a *different declaration* so that gcc treats the address differently. E.g., declare `u16 sp10[6]` vs `u16 sp10[8]`? The layout would change (sp10 at sp+16 with 8 halfwords = 16 bytes → sp+16..sp+31, and the frame size changes). Target frame is 56 bytes; if sp10 is 8 halfwords, gcc might place it elsewhere. Risky but the frame layout is determined by gcc. Actually, wait — the target's stack layout IS the constraint. Changing the array size changes offsets of other locals (there are none besides the frame). Actually the frame is 56 bytes: sp+16..sp+27 is sp10, sp+32 s0, sp+36 s1, sp+40 s2, sp+44 s3, sp+48 ra. So sp10 exactly 12 bytes at sp+16.

If I make sp10 `u16 sp10[6]` — matches.

But hmm, what if I introduce a second local to shift things? No.

Let me think about the "p1 in a register" issue differently. What if we make the pointer value such that gcc *must* recompute: e.g. if the pointer is stored in memory (a stack slot) and reloaded? That gives `lw` insns, not matching.

OK here's another idea: what if the value is used in a way that forces it to be an *argument register* directly. In the target, a1 = sp+24 at insn 4 and a0 = sp+24 at insn 15. In the C, the a1 is set up at insn 3-5 region and the a0 at 15. The gcc scheduling put `addiu a1,sp,24` at insn 4 and `addiu a0,sp,24` at 15.

If gcc had a pseudo for sp+24 live across the call, it would need a callee-saved reg. gcc prefers to avoid that if the value is rematerializable. In mine it did use s0. Why? Maybe because in mine, `sp10 + 4` is used at TWO places (call1 arg and call2 arg) → cse creates a pseudo → the pseudo is a "reg_equiv" of a constant → local-alloc decides to put it in a callee-saved reg because it's live across a call and rematerialization... 

Hmm. Actually gcc's `local-alloc` has a pass that decides "rematerializable" for pseudos whose value is a constant. The address (plus (frame_pointer) (const 24)) — is it treated as a constant? In gcc, `plus` of frame_pointer and const is a valid rematerializable expression. local-alloc's `reg_equiv` for such a pseudo... it should be remat.

But here the pseudo's value came from an *explicit* local variable assignment (p1 = sp10+4), so local-alloc treats p1 as a local variable with a value → "find_best_addr" / the `la` lever.

Hmm, so maybe in a1.c, gcc assigned p1 to s0 because p1 is a variable (not a constant). In b1.c (no p0/p1 vars at all, direct `sp10` and `sp10+4`), the address would be a pure constant expression → rematerializable → `addiu a1,sp,16` and `addiu a0,sp,24` recomputed! That's exactly b1.c. Let me score b1.c! b1.c uses `func_800D20C0(sp10, sp10 + 4, 1);` and `func_800D23D0(sp10 + 4);`.

That might be the winner! The b1 candidate = drop the launder AND drop the p0/p1 variables, using the array directly. That's a "real C move" (declaration/scope simplification). Let me score b1 and b2.

Wait, but a1.c (with p0/p1 vars, no launder) scored 29. b1.c has no p0/p1. Let me score b1.c.

Hmm, but b1.c might have the same issue: `sp10 + 4` in two places → cse → pseudo. But it's a pure constant address, so remat.

Let's just test.
