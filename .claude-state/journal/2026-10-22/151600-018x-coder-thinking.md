---
ts: 2026-10-22T21:16:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PFo0hU0JZWAU2UG3AD1B
---
Now I see: in the target, arm3 (cond3 true, v2 < 0x380) at 14a0ish and arm4 at 14e0. And arm1 at 144c. In mine, arm1 merged into arm3's block (14a0).

The target's arm3 block at 14a0-14dc and arm1 at 144c-1468 are identical instruction sequences. So the ROM has both. Only the barrier separates them.

Also note the branch shapes: target arm1's test at 1444 `beqz v0,146c` (cond1 false → next test) and falls through to arm1. Mine: `bnez v0,14a0` — inverted, because arm1's block is not the fallthrough anymore (merged away, so it jumps to the shared block).

So: to defeat cross-jump, the two blocks must differ in RTL. Plain C options that keep the same instruction stream:

1. Make one arm's constant come from a variable that cse won't propagate. In the target, arm1 has `li v0,113` in the delay slot of the beqz at 1444 and then sh v0,32 — wait, target at 1444: `beqz v0,146c` with delay slot at 1448 `li v0,113`. Then 144c sh v0,32.

In mine, arm3 at 149c: `li v0,113` in delay slot of 1498 beqz, then 14a0 sh v0,32. Same.

Hmm so both arms are code-identical. The only way the ROM's compiler didn't cross-jump them: their RTL differed. Given the game's source, one likely difference: the ROM's arm1 stores `unk30 = -0x50` (literal) and arm3 stores `unk30 = k` where k is a variable... but then cross-jump compares (mem...) with (reg) — not equal → no merge! And cse wouldn't propagate if k has more than one use or is not a simple const-prop case.

But then in arm3 the li would be born at the store... unless sched1 hoists it since k's birth is at the top of the arm (a single set of k with REG_EQUAL -0x50... hmm).

OK here's the thing: with the barrier in the tree today, the score is 0 — meaning the RTL *as currently written* (with k as s16 initialized at arm top and the barrier) produces the target. So the RTL must have k as a real pseudo (not propagated) OR the barrier blocks something. Since the barrier sits between k's birth and its use, and sched1 is blocked by it...

Let me test: does removing just the barrier and keeping everything else (which I did — score 13) mean cross-jump merged? Yes. So the barrier's role is exactly cross-jump prevention.

Plain-C substitute for cross-jump prevention: make the blocks differ. The trick that works in gcc 2.96: cross-jump requires blocks to be "identical" — it uses `rtx_renaming` to map registers. Two blocks whose stores are `(mem (reg s0) (const))` vs `(mem (reg s0) (reg))` differ.

So: make arm3's last store operand a register that cse cannot fold. How? The value must be non-constant from cse's view but still compile to li -80 + sh.

Idea: `k` declared `s16 k = -0x50;` then `unk30 = k;` — cse propagates constants for pseudos? In gcc 2.96 cse, constant propagation happens for registers with a known constant value (cse's `reg_eqv` / `REG_EQUAL` notes). Actually cse's constant propagation in 2.96 is via `simplify_rtx`/`fold_rtx` — it tracks `reg -> constant` in the `table` and substitutes. Yes, fold_rtx substitutes a reg's known constant value. That requires cse to know k = -0x50, which it learns from the insn `set k, -0x50`. So cse WILL propagate.

Unless k's birth insn is not a plain set of a constant from cse's perspective — e.g. the initializer goes through a memory load, or through a sign-extension: `s16 k = (s16)-0x50;`? Still a constant.

Hmm, but with the barrier in place the tree scores 0, meaning the li is NOT at the store. Let me verify what the current tree (with barrier) generates — actually the tree builds to the ROM, so yes score 0.

So with the barrier, cse doesn't fold k into the store. Why? Because cse processes insns and the asm volatile insn blocks cse's ability? No... The asm volatile is a `(parallel ...)`/`unspec_volatile` insn; cse's table gets flushed at basic block boundaries only. Hmm.

Wait — actually maybe the mechanism is: cse DOES fold k's value into the store, giving `set (mem) (const -0x50)`... no, MIPS can't store const to mem; it would become `li v0,-80; sh v0,...` where the li is born at the store. That contradicts the target's li at 1458 (3 insns early).

Unless sched1 hoists the li. sched1 can move the li up within the block since the store depends on it. So the li could be hoisted regardless.

OK so the real question: what does the barrier do for scheduling? "§5a: born ABOVE the barrier so sched1 can hoist the li". Hmm — sched1 with an asm volatile: the asm is a scheduling barrier, insns don't move across it. But here the barrier is AFTER the k birth and BEFORE the k use, so hoisting the li up (above) is fine.

So with the barrier: k's li is a separate insn born early (at the top of arm3) and sched1 hoists/keeps it. Without the barrier: cse folds the constant into the store, so the li is born at the store and sched1 can still hoist it... but the *blocks* become identical and cross-jump merges.

So the fix: prevent cse from folding k into the store, without an asm. Ways to make cse not know the value:
- Make k's definition not a constant in cse's table: e.g. `s16 k = D_something;` no.
- Make k's value come from a computation cse can't fold: `s16 k = -0x50;` is a constant.

Alternative approach: make arm1 differ instead. E.g. write arm1's unk30 store as `unk30 = k;` too... no, then both identical again.

Better idea: change the *number* of insns in one arm so blocks can't be identical... but they must be identical in the target.

Hmm. Another plain-C route: make the two blocks not both reachable in the same basic-block shape — e.g. change the control flow so cross-jump's requirement fails. Cross-jump merges two blocks with the same successor. Arm1's block jumps to the join (after the if-chain); arm3's block also jumps to the join. Both have successor = join block, and their bodies identical.

What if arm3's body doesn't end with an unconditional jump because it falls through? Then the blocks differ structurally. In the target, arm1 ends with `j 14fc; sh v0,48` and arm3 also `j 14fc; sh v0,48`. Both have explicit j. Hmm.

Alternatively use a different code path shape: make arm3 be the *last* else so it falls through... The target has arm4 as the last with no jump (14f8 sh zero,48; 14fc sh zero,50). Yes.

So both arm1 and arm3 have `j`.

What if I restructure the if-chain (like the W01/W02 moves: "swap inner arms", "store per if-arm") to change the CFG so cross-jump can't fire? E.g. write the chain as:

if (cond1) { arm1 }
else if (cond2) { arm2 }
else if (cond3) { arm3 }
else { arm4 }

That's the current shape. Alternative: 

if (!cond1) { ... } — nested. The instruction stream must stay identical though.

Hmm, another thought: the difference could be in *which* register holds the constant. In target arm1: li v0,113 in the delay slot at 1448. In arm3: li v0,113 at 149c in the delay slot of 1498. Identical.

OK, let me think about cse differently. Cross-jump in gcc 2.96 (jump.c: `merge` / `cross_jump`) — actually cross-jumping happens in `jump_optimize_1` via `find_cross_jump` which compares `rtx_renaming`. It runs after cse1? Let me check the actual pass order for gcc 2.96: 

rest_of_compilation:
1. jump_optimize (with flag_cross_jumping? cross_jump is called in jump_optimize when `flag_cross_jumping`)
2. cse (cse1)...
Actually in gcc 2.96: `jump_optimize` is called, then `cse`, then `jump_optimize` again? Let me just check: the standard order is: ... `if (optimize > 0) { jump_optimize(...); }` then `cse_insns` then `if (optimize>0 && flag_thread_jumps) thread_jumps`. Hmm.

Rather than archaeology, let me experiment. Practical approach: try candidate bodies and score. Ideas ranked:

A. `s16 k = -0x50;` moved to the top of the function or arm with a `volatile`-free spelling... 

B. Use a pointer-based store for arm3: `*(s16 *)((u8*)a0 + 0x30) = k;` vs the struct field in arm1. Different RTL shape? Probably not.

C. Make arm1 store a *different expression* that folds to the same constant but produces a different insn sequence... it must produce exactly `li v0,-80; sh v0,48`.

D. Split the constant: `unk30 = 0 - 0x50;` folds.

E. What about the *order* of the two zero stores in arm3: `unk2E = 0; unk24 = 0;` swapped → then arm3's block insn order differs from arm1 → no cross-jump. But the target's arm3 has sh zero,36 then sh zero,46 — same as arm1 (target 145c: sh zero,36; 1460: sh zero,46). Wait, in the target arm3 at 14d0: sh zero,36; 14d4: sh zero,46 — same order. But sched1 could reorder... they're both independent stores to the same base; sched1 might keep source order. If I swap the source order in arm3, the emitted order would swap → mismatch.

Hmm, but wait! Look more carefully at the target arm3:
14c0: sh v0,32   (0x20)
14c4: li v0,1536
14c8: sh v0,34   (0x22)
14cc: li v0,-80
14d0: sh zero,36 (0x24)
14d4: sh zero,46 (0x2E)
14d8: j
14dc: sh v0,48 (0x30)

And arm1:
144c: sh v0,32
1450: li 1536
1454: sh v0,34
1458: li -80
145c: sh zero,36
1460: sh zero,46
1464: j
1468: sh v0,48

Identical. So no reordering freedom.

F. The `k` variable: what if the birth of k is not in arm3 but in a way cse treats as non-constant: `s16 k; ... k = -0x50;` same.

G. What about making k's value depend on the condition trivially, e.g. `s16 k = (s16)(0x380 - sp10.v[2] ...)`. No — value must be -0x50 always but not a constant to cse. E.g. `s16 k = -0x50 + (sp10.v[2] & 0)`? folds.

Hmm. cse fold_rtx will fold `(x & 0)` → 0. 

H. What if the constant is loaded from a global variable that holds -0x50? That changes insns (a load).

I. Reconsider: maybe cse isn't the pass; maybe it's *cross-jump comparing after sched1*? No.

Let me actually test the hypothesis that cross-jump is the culprit by finding the pass. The moves line for func_80189214 says "barrier->store per if-arm" — i.e. they cracked a barrier by writing the store in each arm. Different situation.

Let me look at the moves for a barrier used as a cross-jump barrier specifically. Search moves.md for "cross-jump".

Earlier grep showed only line 77 "no cross-jump" and the src comment "cross-jump barrier". 

Practical: let me just test a few candidates quickly with sc.sh. Candidates:

1. win2: remove barrier, and in arm1 use `-0x50` while arm3 uses `k` — already the case. No change.
2. Make arm3 store `unk30 = k;` where k is `s16 k = -0x50;` but add a second use of k elsewhere so cse's propagation... no.

3. Make arm1's store `unk30 = -0x50;` and arm3's `unk30 = k;` where k is declared as `volatile`? No, that adds loads.

4. Instead of the barrier, put a *real* difference: arm3's unk24 store as `unk24 = 0x0;`... same.

5. Use `((Unkstruct*)a0)->unk30 = k;` where k is u16 vs s16? The store insn: sh. If k is u16 the HImode reg is the same.

Hmm, let me think about what makes cse fail to fold: if the pseudo k has REG_EQUAL note with a *symbol* or is "not known constant" — cse's fold_rtx for a REG looks up `reg_eqv_table`/the `table` for a constant. It uses `REG_EQUAL` notes attached to insns. The insn `(set (reg:HI k) (const_int -80))` — cse records in the table `reg k -> -80`? cse's `insert_regs` + `expr_hash_table`: a `set` of a reg to a constant is recorded as a constant equivalence, yes.

BUT: cse only does this within an extended basic block, and it *invalidates* at calls etc. Fine.

Key trick used elsewhere in this project: make the copy escape cse by using a different machine mode (HImode SUBREG) — e.g. "u16 i; u16 j: the HImode copies of arg0/arg1 escape cse". So a HImode copy escapes cse.

So: declare k as `s32 k = -0x50;` (SImode) and store `unk30 = k;` → a truncate/store of SI reg into HI mem. Hmm, then cse might fold to `(const_int -80)` in HImode.

Alternatively store via a temp: `s16 t2 = k; unk30 = t2;` — the HImode copy escapes cse... but the copy might be eliminated as a no-op.

Actually here's the thing. What if cse DOES fold, and the merge is done by a *later* pass that compares the final insns (like cross-jump on RTL after cse). Then folding doesn't matter — the final insns are identical.

Let me just experiment empirically. Fastest: test whether a body where arm3 differs *textually* but generates the same insns avoids the merge. Test candidate: in arm3, write the stores through a local pointer variable:

```
u8 *q = (u8*)a0;
*(s16*)(q+0x20) = 0x71; ...
```
That would generate the same insns (base = s0?) maybe not — q might take another register.

Alternative empirical test: swap the arm order in the chain (put arm3 before arm1)? That changes block layout.

Honestly, let me look at what the actual ROM source likely was. This is a decomp: the current src is a reconstruction with a NEEDED DIFFERS fake. The original probably had:

```
} else if (sp10.v[2] < 0x380) {
    ... same stores ...
    ((...)a0)->unk30 = -0x50;
}
```
and arm1 also -0x50. For the compiler not to merge them, maybe the ROM's arm1 used a different *variable*, e.g. the original had `p->unk30 = -0x50;` in arm1 but in arm3 the store came from a computed value like `k = -0x50` that also got used elsewhere (e.g. passed to something). 

Wait — actually! Maybe the ROM's arm3 stores `k` where k is ALSO used later, e.g. `sp10.v[1]` related. Look at the end of the function:

```
((...)a0)->unk32 = 0;
if (sp10.v[0] < -0x400) sp10.v[0] = -0x400;
if (sp10.v[1] >= -0x101) sp10.v[1] = -0x102;
```
The target's tail: `li v0,-1024` in delay slot, `li v0,-258`. And in arm3, `li v0,-80` at 14cc... note -0x50 vs the tail constants.

Hmm! Interesting: what if in the ROM's source, arm3's k is the SAME variable as something used in the tail? Like `s16 k = -0x50;` in arm3 and... no.

Let me take a completely different approach and be empirical. I'll generate a batch of candidate bodies and score them all with sc.sh (fast, one line each). Candidates:

a) barrier removed, k decl moved to the top of the function (init at decl).
b) barrier removed, arm3 stores via `k` and arm1 stores `k`... no.
c) barrier removed, arm3 uses `s32 k = -0x50;` (SImode) then `unk30 = k;`.
d) barrier removed, arm3: `unk30 = -0x50;` written as `unk30 = (s16)-0x50;`.
e) barrier removed, arm1's unk30 = -0x50 written with a different type cast than arm3's.
f) barrier replaced by a `do {} while (0)` around the arm3 tail.
g) barrier removed + `sp10.v[2]` stored to a local first in arm3.
h) arm3 body written via a pointer `s16 *p = &((...))a0->unk20; p[0]=0x71; p[1]=0x600; p[2]=0; p[7]=0; p[8]=k;` — p[7]=0x2E, p[8]=0x30. Different RTL, same insns. This is promising: the stores would be `(mem (reg p))` with a different addressing mode, and the emitted code would use... base s0 + offsets after cse folds p back to a0+0x20? cse folds `p = a0 + 0x20` into the addresses, giving the same insns but the *blocks* after cse are identical again. Hmm, but the RTL would only become identical after cse... cross-jump runs after cse.

I think the honest approach: find which pass merges, then defeat that pass. Let me get the dumps. tools/cc1_dumps_tu.sh + alloc_table.py. Let me check cc1_dumps_tu.sh usage.

Actually there's `.run/P40/T10/hdump.sh` (header) and `tools/cc1_dumps_tu.sh`. Let me read its help.
