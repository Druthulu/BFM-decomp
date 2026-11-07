---
ts: 2026-11-07T00:08:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_xbWsOuxOSQZdEmY3mTKA
---
perm_1324: pairs v1->v0 x4, s3->s2 x2, s2->s3 x2, s1->v0 x1. So it fixed the s4/s5 swap (p2/p3) but not s2/s3 (p1/p4) and the t issue.

Hmm. So perm_1324 (copy order p1,p3,p2,p4) gives p2/p3 right but p1/p4 wrong.

We need p1 > p4. In perm_1324, order p1,p3,p2,p4: p4 copied last → highest pri → s2. p1 copied first → s3. Still wrong.

To make p1 > p4, p1 must be copied later than p4. Let me try orders where p4 comes before p1 and p2 before p3: e.g. p4,p2,p3,p1 → 4231 (score 34), p2,p4,p3,p1 → 2431 (39), p3,p4,p2,p1 → 3421 (32).

Hmm, none gave <31.

The problem: making p1's copy later changes the emitted copy order (which sched1 might or might not restore).

Wait — actually, maybe the param priorities aren't only about copy order. Let me reconsider. Maybe the live lengths are dominated by the LAST use, and the last uses are in the loop at different positions:
- p1 used in func_80013350(param_1+4, iVar1+4) — deep in the loop
- p2 used in *(u16*)(iVar1+0x60) = param_2 — inside the innermost if
- p3 used in *(u16*)(iVar1+0x62) = param_3 — same place
- p4 used in *(u16*)(iVar1+0x5e) = param_4 — same place, and also earlier in the `if (*(u16*)(iVar1+0x5e) != param_4)` test

Hmm.

OK, let me step back and think about the t issue first, since it's 15 points and affects allocation.

The target: t=v0, iVar4=v1. Lever-free we need t distinct from iVar5 and iVar4.

KEY INSIGHT attempt: In the target, `t` is loaded into v0 and `iVar4` into v1 — BOTH are loaded before the copies. The C is:
```
t = load+4;
iVar4 = load+6;
iVar5 = t;
if (t < 0) iVar5 = -iVar5;
if (iVar4 < 0) iVar4 = -iVar4;
```
So `t` and `iVar4` are loaded into v0/v1. Then `iVar5 = t` copies v0→s1.

For cse to keep the copy, t must be distinct from iVar5. Hmm.

What if I make `t` a *different type*: e.g., `s32 t;` but declare `iVar5` as `u32`? Then `iVar5 = t` is a same-mode copy.

Hmm, what if I write `iVar5 = (s32)t;`? Same.

OK here's an idea: use the C0414 dead-reset on `t` right after the copy:
```
t = load+4;
iVar4 = load+6;
iVar5 = t;
t = 0;    // dead reset — but t is reused later, so this isn't dead!
```
t IS reused later (`t = load+8`). So `t = 0` is dead until the next set. flow might delete it (dead store). If deleted, no effect.

Hmm. What if the dead reset is on iVar5 instead? no.

Let me think about cse1's behavior again: `t = load` (set t). `iVar4 = load` (set iVar4). `iVar5 = t` → make_regs_eqv(iVar5, t). Then `if (t < 0)` uses t → replaced by the canonical (t or iVar5). `iVar5 = -iVar5` sets iVar5 → breaks eqv.

So after `iVar5 = t`, cse replaces uses of iVar5 with t (or vice versa) until the next set. The load result lives in one register.

In the target, the load is in v0 and there's a copy to s1. So cse did NOT merge. Which means in the target's RTL, at `iVar5 = t`, t had no valid qty.

How? If `t` was set by the load and then... the load is a MEM reference. cse records the load result as a qty for t. Hmm.

Unless the target's C has `iVar5 = t` BEFORE the load?! Like:
```
iVar5 = t = load+4;
```
no.

Hmm, wait. Let me reconsider the target assembly:
```
lh v0,4(a0)      ; t = load
lh v1,6(a0)      ; iVar4 = load
bgez v0, 5aec    ; if (t < 0)
move s1,v0       ; iVar5 = t   [delay slot]
negu s1,s1       ; iVar5 = -iVar5
```
Wait — `bgez v0, 5aec; move s1,v0`. So the branch tests t (v0), and the delay slot does iVar5 = t. Then negu s1. So `if (t < 0) iVar5 = -iVar5;` where iVar5 = t was moved in the delay slot.

Hmm, but in C: `iVar5 = t; if (t < 0) iVar5 = -iVar5;`. The copy happens before the test. The delay slot placement is sched1/reorg.

So there IS a copy iVar5 = t. For it to exist, t ≠ iVar5 in the RTL.

Hmm OK. What if the C is actually:
```
iVar5 = *(s16*)(uVar3+4);   // direct load to iVar5
```
and then `if (iVar5 < 0) iVar5 = -iVar5;` → `lh s1,4; bgez s1; negu s1`. That's mine. So the target's extra move means an intermediate.

What if the intermediate is NOT a C variable but the result of the cast `(s32)*(s16*)`? In gcc, a signed halfword load into an SImode register: `lh` directly. No intermediate.

Hmm, what if the original used a u16 load then a cast? `t = *(u16*)(uVar3+4); iVar5 = (s16)t;`? That would be `lhu` then `sll/sra` or `seh`. Not matching.

Hmm, what if the target's `t` is a hard register from a REAL Sony macro? The pin comment says NEEDED DIFFERS, meaning the body differs without it — the decomp author's guess.

So the original source might have had a different structure entirely. But our job is to find ANY lever-free C that matches. 

Let me think about what makes a copy survive: the register allocator coalescing. Actually, maybe cse DOES merge t and iVar5, but then the register allocator *splits* them because iVar5 is live across calls (s1) and t is a short temp. If cse merges them into ONE pseudo, that pseudo is live from the load to the end (across calls) → gets s1. So the load goes to s1 directly. That's mine.

So the merge is the issue.

Lever-free way to prevent the merge: make `iVar5 = t` not a simple copy. E.g., `iVar5 = t + 0` → combine folds. `iVar5 = t | 0` → folds.

Hmm, what about `iVar5 = (t < 0) ? t : t;` → folds.

What about making t a different *mode*: `iVar5 = (s32)(s16)t;`? If t is s32, the cast is a no-op. If t is s16, then `lh` loads into s16 and the conversion to s32... hmm.

What if t is declared `s16`? Then:
- `t = (s16)*(s16*)(uVar3+4);` — the load result is s16.
- `iVar5 = t;` — s16 → s32 conversion, which in RTL is a sign-extend (but gcc knows the load already sign-extended, so it might just use the reg).

Hmm, actually in gcc 2.7.2, `t` as s16 would be HImode in a register. `iVar5 = t` would need a sign extension. The target has a plain `move s1,v0`, no shift. So not s16.

Hmm.

What about the *launder* on iVar4 — the same problem. With pins kept and launder removed, score 2 (tiny). So the launder's effect is small when the pins are there.

Let me focus: the biggest contributor is the param permutation (19 with t pinned) + t (15 with params pinned).

Given the difficulty, this looks like another global-pri-bank-order wall. But let me try a bit more.

Let me reconsider the t problem with a different angle: what if `t` is used in a way that makes it multi-set within the block so cse can't equate? E.g.:

```
t = load+4;
iVar4 = load+6;
iVar5 = t;
if (t < 0) { iVar5 = -iVar5; }
```

What if I write:
```
t = load+4;
iVar5 = t;
t = load+6;
iVar4 = t;
if (iVar5 < 0) iVar5 = -iVar5;
if (iVar4 < 0) iVar4 = -iVar4;
```
Reordering: t is set twice before the copy... Hmm, `iVar5 = t` after the first set; then `t = load+6` re-sets t. cse: at `iVar5 = t`, t has the load+4 qty → merge. Hmm.

What if `t` is set from a different value first:
```
t = load+4;
t = load+4;   // dead duplicate
iVar5 = t;
```
flow deletes the first? Then no.

Hmm.

What about: make `iVar5`'s initialization not a direct copy. E.g.:
```
iVar5 = t;
if (t < 0) iVar5 = -t;
```
Then `iVar5 = -t` computes from t. cse: `iVar5 = t` merges. Hmm.

What if:
```
if (t < 0) iVar5 = -t; else iVar5 = t;
```
This is an if/else. cse: in the then-arm, `iVar5 = -t`; in the else, `iVar5 = t`. The join: iVar5 set in both arms. Hmm, the target has `move s1,v0` in the delay slot then `negu s1,s1` — that's `iVar5 = t; if (t<0) iVar5 = -iVar5;` pattern, not if/else (if/else would be `negu s1,v0` in one arm and `move s1,v0` in the other).

Hmm.

OK, let me look at the ACTUAL gcc behavior: maybe cse does NOT merge because `t` is a *multi-set* pseudo across the function (5 sets), and cse's make_regs_eqv requires... no, cse works per block.

Hmm, wait. Let me re-examine: does cse merge `iVar5 = t` when t is loaded from memory? Let me check cse.c: make_regs_eqv is called from cse_insn when the source is a REG. But before that, cse_insn may substitute the source. If t's qty is known (the load result), the copy `iVar5 = t` makes them equivalent.

Actually, in the ORIGINAL body (with pins), the t pin forces t into a hard reg, so cse can't merge a hard reg with a pseudo? Actually make_regs_eqv with a hard reg... the canonical preference is hard regs first. Hmm.

Whatever. Let me try a practical approach: search over C variants for the t block and see if any gives the copy. Variants:
1. t declared s32, load into t, copy to iVar5 (current) → merged.
2. Reorder statements.
3. Use separate variables for each load (t1..t5).
4. Use iVar4 as the temp and iVar5 direct.

Hmm, let me look at the target more: in blocks 2-5, `lh v0,8(a0); ... move v1,v0` — so iVar4 = t (v1 = v0). Here t=v0 and iVar4=v1. cse: `t = load+8; iVar4 = t;` → merge would give one reg. But the target keeps two. So the copy survives here too.

Since the launder is only in block 1, blocks 2-5 have no lever — yet the copies survive in the TARGET. In the target, t is pinned to v0, so t is a hard reg; iVar4 (pseudo) can't merge with a hard reg? Actually make_regs_eqv(new=iVar4, old=t): if old is a hard reg (v0) and it's not fixed... v0 is call-clobbered but allocatable. Hmm, "Prefer fixed hard registers to anything" — v0 is not fixed (it's allocatable). The code: `firstr < FIRST_PSEUDO_REGISTER && FIXED_REGNO_P(firstr)` — v0 is not FIXED (FIXED_REGNO_P(v0) is false for v0? Actually on MIPS, $0 is fixed; v0/v1 are not fixed). So it goes to the else branch: "If NEW is a hard reg (known to be non-fixed), insert at end." Hmm.

Hmm, the canonicalization might keep them separate... but make_regs_eqv still makes them equivalent (they share a qty). Then uses get the canonical. If the canonical is the hard reg v0, then iVar5's uses → v0. Then iVar5 wouldn't be s1.

But the target has iVar5=s1 and t=v0 as separate! So cse did NOT merge.

OK, let me just check the cse dump of the ORIGINAL (pinned) body to see what happened. Actually, better: let me test lever-free variants empirically.

Let me try: separate load temps for each block:
```
s32 t1, t2, t3, t4, t5, t6;
t1 = load+4;
t2 = load+6;
iVar5 = t1;
if (t1<0) iVar5=-iVar5;
if (t2<0) iVar4=-t2;
...
```
Hmm, but the C structure is fixed by the target.

Hmm hold on. Let me reconsider the target's block 1:
```
lh v0,4(a0)     ; load+4 → v0
lh v1,6(a0)     ; load+6 → v1
bgez v0, ...
move s1,v0      ; iVar5 = v0
negu s1,s1
bgez v1, ...
nop
negu v1,v1      ; iVar4 = -iVar4 (v1)
```
Note: iVar4 is in v1 and negu v1,v1 — so iVar4 was loaded directly into v1 and negated in place. No copy for iVar4 in block 1! The launder pseudo is v1 itself.

And iVar5: move s1,v0. So only iVar5 gets a copy.

Blocks 2-5:
```
lh v0,8(a0)     ; load → v0 (t)
nop
bgez v0, ...
move v1,v0      ; iVar4 = v0 (v1)
negu v1,v1
slt v0,s1,v1
```
Here iVar4 = t (copy), and t = v0.

So in blocks 2-5, `iVar4 = t` is a copy from v0 to v1. In block 1, iVar4 is loaded directly into v1 (no copy) because the C is `iVar4 = (s32)*(s16*)(uVar3 + 6);` (direct load, not via t).

So:
- Block 1: iVar4 = direct load +6 → v1 (negated in place). t = load +4 → v0, then iVar5 = t.
- Blocks 2-5: t = load +N → v0, iVar4 = t → v1, negate v1.

So the target's copies:
- `iVar5 = t` in block 1 (move s1,v0)
- `iVar4 = t` in blocks 2-5 (move v1,v0)

Both are copies from t (v0). And t is v0.

For the copies to exist, t must be distinct from iVar5/iVar4 in the RTL.

Hmm, but in block 1, `iVar5 = t` — and iVar4 is a direct load. So the C is:
```
t = (s32)*(s16 *)(uVar3 + 4);
iVar4 = (s32)*(s16 *)(uVar3 + 6);
iVar5 = t;
if (t < 0) { iVar5 = -iVar5; }
if (iVar4 < 0) { iVar4 = -iVar4; }
[launder iVar4]
if (iVar5 < iVar4) { iVar5 = iVar4; }
```
Yes, that matches the header C.

So the target keeps `iVar5 = t` as a copy. cse merges it in my version.

Hmm. Is it possible that the target's t is NOT merged because t is assigned 5 times (multi-set) and cse's `reg_tick`/`reg_invalid` machinery marks t as "invalid" after multiple sets within the block? No.

Hmm, let me look at the cse dump of the ORIGINAL pinned body to understand. Let me dump the original (pinned) and look at the .cse file for func_8012DBD0. Actually, that's the target-matching version, so its cse dump will show the copies.

Actually, I realize the difference might be in `iVar5 = t` where t is a hard reg: cse's make_regs_eqv with a hard reg. Let me check: when OLD is a hard reg that is not fixed, and NEW is a pseudo... the else branch inserts NEW before non-fixed hard regs at the end. The canonical might remain t (hard). Then uses of iVar5 → t (v0). Hmm, but iVar5 needs s1 for the loop. Then reload/global-alloc... hmm, but cse is before allocation; iVar5 would become equivalent to v0 and its uses rewritten to v0. That would break the loop.

So cse must not be merging. Let me look at the actual cse dump.

Actually — maybe the answer is simpler: `iVar5 = t` where t is a hard reg. cse's cse_insn has a check: it only records equivalences for REG sources if `REGNO_QTY_VALID_P`. Hmm.

Let me just look at the .cse dump of the pinned body (which matches the target). Let me splice orig.c and dump.

Hmm, time. Let me consider the alternative: maybe this is just a hard wall. But let me spend a few more minutes.

Actually, let me try a very different idea for the whole item: what if the params don't need to be copied at all? The C does `param_1 = arg0;` etc. — 4 copies. In the target, these copies exist (move s2,a0 etc.). So they're needed.

Hmm, what if we use the parameters directly (no param_N variables)? Then the args are used directly, but the target has copies. So no.

OK. Let me look at the cse dump for the pinned original to understand the t behavior. That's the key.

Actually, let me try a simpler experiment first: in the lever-free body, replace `iVar5 = t;` with `iVar5 = t + 0;`? No, folds.

Hmm, what about `iVar5 = t;` → `iVar5 = (s32)t;`? Same.

What if I declare t as `volatile`? That's a barrier lever — not allowed.

What if I use a union to load? no.

Let me look at the cse dump. Splice orig.c into the TU and dump.
