---
ts: 2026-11-06T17:06:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_88AuIUDW2f3T9AJpx0aI
---
Key rule: "Among pseudos, if NEW will live longer than any other reg of the same qty, and that is beyond the current basic block, make it the new canonical replacement."

In z6: the copy is `n(78) = q(77)`. new=78, old=77. 78 lives longer (it's used later: n >>= 2 etc.) and its last use is beyond the current block? The EBB here is the whole function body (straight-line). Hmm, cse_basic_block_end. If 78's last use is within the block, the condition fails and the canonical stays 77. But cse made 78 canonical. So 78's last use must be beyond cse_basic_block_end (the end of the current EBB).

Why would the EBB end before 78's last use? Because of the branch at 134! The branch splits the EBB: cse processes EBBs. The EBB containing the copy ends at the branch. So 78's last use (after the branch) is beyond the EBB end → 78 becomes canonical.

In the target (pinned), n is a hard reg, so make_regs_eqv prefers pseudos: "Prefer pseudo regs to other hard regs." With old=77 (pseudo) and new=16 (hard reg), the hard reg goes to the end of the class, and the canonical stays 77. That's why the target's branch tests q(77).

So: to keep the canonical as q, n must NOT be a pseudo that lives longer beyond the EBB. If n were... hmm.

Alternatively, make the copy the other way: `q = n`? No.

What if we make n's last use within the same EBB as the copy? The EBB ends at the branch (134). n's uses after the branch are in the next EBB. If we avoid the branch splitting (i.e., no branch between the copy and the uses), then 78's last use is within the block → not canonical → the branch stays on q.

How to avoid the branch? Use a branchless computation of `if (q < 0) n = q + 3;`! E.g. `n = q + ((q >> 31) & 3);`? Hmm, that's `q + 3` if negative else q — but the target has a branch (bgez). So no.

Hmm, wait: the target's branch IS there. In the target, the copy `n = q` is before the branch, and the branch tests q. The cse didn't rewrite because n is a hard reg.

So we need n to be a pseudo but not become canonical. The rule: n becomes canonical if its last use is beyond the EBB end. The EBB here: the branch at 134 ends it. n's last use is at 144 (after the branch) — beyond. So n becomes canonical.

Unless n's last use is BEFORE the branch. That means n's whole live range is in the first EBB: i.e., the copy and all uses of n before the branch. But the uses (>>2, <<2, q-n) are after the branch.

Hmm, so with the natural C, cse always rewrites. But the pinned version doesn't.

What if we reorder so the branch comes AFTER the n computations? The target's code has the branch early. 

Hmm, what if the source's if is written to make the branch not split the EBB in cse's view? cse's EBB ends at any label with multiple predecessors / a branch target. The branch at 134 targets label 137, which is a join point (both paths). cse's `cse_basic_block` splits at the target label. So the EBB ends.

Alternatively, make the copy happen AFTER the branch (in the EBB after): e.g. `if (q < 0) n = q + 3; else n = q;` — the copy `n = q` is in the else arm, after the branch. Then cse's first EBB (up to the branch) doesn't contain the copy. But the compiler may hoist the copy before the branch (as z8 showed: move s0,v0 before the bgez).

In z8 the copy was hoisted. Hmm.

Let me look at z8's cse: maybe the copy is still before.

Alternative idea: prevent cse from merging by making q and n different *modes* — e.g., q is s32 and n is s32; no.

What if n is assigned from q via a `+ 0`? That's an identity launder — forbidden.

Hmm, what if the *branch condition* uses a value cse can't substitute: e.g. `if (q < 0)` where q was loaded from memory (not a register copy)? No.

Let me consider: maybe the original source didn't use `q = rand()` into a variable at all. E.g. `m = (rand() % 4) << 16;` — the `%` expansion's q is the call result (v0), and the temp is a copy. The copy temp's last use is after the branch → it'd become canonical and the branch would test the temp. But the target's branch tests v0 (the call result). Since v0 is a HARD register (the call result), make_regs_eqv prefers the pseudo temp over the hard reg... wait, "Prefer pseudo regs to other hard regs" — so the temp (pseudo) would become canonical and the branch would test the temp. But the target tests v0 (hard). Hmm, that contradicts!

Unless the branch condition `ge:SI (reg v0)` — v0 is hard; the temp is a pseudo. cse's make_regs_eqv(new=temp, old=v0): firstr = v0 (hard, not fixed? v0 is call-clobbered, not FIXED). The rule: prefer fixed hard regs; prefer pseudos to other hard regs. So new=temp (pseudo) should become canonical... but the target keeps v0.

Hmm, wait: the target's RTL at .rtl would be `(set (reg temp) (reg v0))` and the branch on v0. cse's make_regs_eqv(new=temp, old=v0): new is a pseudo, old is a hard reg. The condition for making new canonical: `(new >= FIRST_PSEUDO_REGISTER && (firstr < FIRST_PSEUDO_REGISTER || ...))` — firstr = v0 (hard, < FIRST_PSEUDO) → TRUE. So the pseudo temp WOULD become canonical and the branch rewritten to test the temp. But the target doesn't. So maybe the target's original source doesn't have a copy at all!

If the source is `q = rand(); ...` and the temp is q itself... Hmm.

Let me reconsider: in the target's RTL, maybe the `%` temp and q are the SAME pseudo, i.e., the expansion is `if (q < 0) q = q + 3; ...` — but q is used later at `subu s0,v0,s0`, which uses v0 (the original q). So q is preserved separately.

Hold on: the target's subu uses v0 = the original q, and s0 = the rounded value. So there ARE two values: q (v0) and temp (s0). The branch tests v0.

With the pinned source, the temp is the hard reg n, so cse prefers the pseudo q over the hard reg n (hard regs go last) → the branch stays on q. That's consistent.

With an unpinned pseudo temp, cse would make the temp canonical (pseudo preferred over hard v0) and the branch would test the temp. That's what mine does.

So the target's shape requires the temp to be a HARD REGISTER (or a fixed reg) — which is exactly the pin! Unless... the temp is a hard register naturally, e.g. `at`? No.

Hmm, wait: what if the temp is a *parameter* or a value in a fixed register? No.

So this looks like a genuine WALL: the pin is load-bearing because cse's canonicalization prefers the pseudo over the hard call-result register. Hmm, but maybe there's another way: make the temp's live range not extend beyond the EBB (so it doesn't become canonical). Then the canonical stays v0 and the branch tests v0. But the temp's uses are after the branch...

Unless the branch is placed AFTER the temp's uses. Target's branch is before. Hmm.

What if we avoid cse's EBB split by making the branch a *different* construct that doesn't create a join label? The branch creates a join. Any if creates a join.

OK, let me consider: maybe the target's temp (s0) is a hard reg because the original source had a `register` variable? No, the original is compiled from the game's C, which likely didn't use register pins... but the game's code was compiled from C that could have had `register` variables (the compiler honors them). Hmm! The original 1998 source might well have used `register` declarations. But our task forbids `register` vars.

Given the constraints (no register, no asm), this may be a WALL. The wall tag: "global-hardreg-reserve" or "cse-copy-merge" or "lreg-qty-priority". The mechanism: cse's make_regs_eqv canonicalizes the pseudo temp over the hard call-result reg (cse.c:840), rewriting the branch to the temp; the target keeps the branch on $v0, which needs the temp to be a hard reg (the pin).

Before declaring a wall, let me try a couple more ideas:

1. Make the temp's last use before the branch by restructuring: what if the branch is on `n` after all? No, target tests v0.

2. Use `q` twice so cse prefers... no.

3. Make the copy `temp = q` occur *after* the branch: e.g. `if (q < 0) { n = q + 3; } else { n = q; }` — z8. Let me check z8's cse to see if the copy is after the branch in RTL.

Let me check z8's rtl dump quickly. Actually z8's score was 10 with `bgez s0`, same problem.

4. What if we make n a *global* variable (not local)? Then it's memory, not a register. No.

5. What if the copy is done through a union/bitfield? No.

6. What if the comparison is `if (q < 0)` but q is re-loaded? No.

I think this is a wall. The budget requires ≥20 min and ≥30 scored tries for a WALL. I've done ~12 tries and 18 min. Hmm, "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I must do at least 30 tries and 20 min to record a WALL. Otherwise it's not an attempt (I can't record it?).

I have ~10 more minutes and 18 more tries needed. Let me generate a batch of variants and score them in one command (sc.sh accepts multiple files). I can write many candidate files quickly and score them all. Let me do that — it's efficient.

Variants to try (all lever-free, real C):
a) `n = q; if (q < 0) n = q + 3;` with n used for the result and m kept (z6-like) — done.
b) different declaration orders (n before q, etc.)
c) different variable names/order of the two computations (swap vel X and vel Z order).
d) use `s16`/`u8` widths.
e) reorder the statements (statement order).
f) compute the sign first.
g) merge the two computations into a helper macro? no.
h) `for` loop over the two velocities with a table of offsets — might unroll? no, gcc won't unroll.
i) different comparison spellings.

Let me focus on the register/cse aspect: the cse canonicalization depends on the EBB end. What if we move the `if (q < 0)` *after* the shifts? No, semantics.

What if we write the expansion as a `while`/`do` that changes the EBB structure? E.g. `do { n = q; if (q < 0) n = q + 3; n >>= 2; n <<= 2; } while (0);` — the do-while creates a loop note and a label, which might split the EBB so that the copy and its uses are in the same EBB and the branch's target is inside... Hmm, could work! The do-while(0) with the `// !FAKE: do-while` marker is allowed.

Let me try: wrap the n computation in do{}while(0). The loop label at the end might change cse's EBB boundaries.

Also try: `for (;;) { ...; break; }`.

Let me generate a batch of ~10 variants and score them all.

Variants:
1. do-while(0) around the n computation (both).
2. for(;;){...break;} around it.
3. swap the order of the two velocity computations.
4. declare n as u32 but keep sra by using `(s32)n >> 2`? changes insns.
5. `if (q < 0) n = q + 3; else n = q;` (z8).
6. `n = q; if (q < 0) n += 3;` — `+=` instead of `= q + 3`. Might change cse: `n += 3` is a use of n.
7. `n = q; if (q < 0) n = q + 3;` but with the shifts written as `n /= 4; n *= 4;`? `/4` → sra 2 (same), `*4` → sll 2. But the C `q % 4` semantics: (q/4)*4. `n = n / 4 * 4;` — different C but same insns? Actually `n/4` for signed → sra 2; `*4` → sll 2. Same. Try it.
8. Write the modulo as `n = q % 4;` (natural) with n used for the result (z5-ish).
9. Write `m = (q - (q % 4)) << 16;` with the temp inline? The `%` temp is compiler-generated.
10. Change the order: compute `n` before `q`? no.

Let me write a script generating these variants from orig (removing the pin) and score them all at once.

Actually, I realize the key insight from the cse source: the temp becomes canonical if its last use is beyond the EBB end. What if the *uses* of n are in the same EBB as the copy? The EBB ends at the branch's target label (137). The uses at 139-144 are after the label → different EBB. If we could make the branch's target label be AFTER the uses... The branch is `if (q >= 0) goto L` where L is the join. If we invert the condition and the structure so the label is after all uses? E.g.:

```
if (q < 0) n = q + 3; else n = q;
```
The join label is after the else, before the uses. Same.

What if we write it without a join:
```
if (q < 0) { n = q + 3; } else { n = q; }
```
same.

Hmm, what if the branch's target is the very end of the function? no.

Let me just run the batch and see if any variant scores 0. I'll create 12 variants.

Also, the WALL budget: I need 30 scored tries. The batch gives me many. Let me count tries carefully later.

Let me write the batch generator.
