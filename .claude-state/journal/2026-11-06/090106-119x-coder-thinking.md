---
ts: 2026-11-06T16:01:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OLGRaRY9SUxVvniZjedi
---
vo6: score 39 (same as c3) — the q2 variable was coalesced to the same register as q (v0) and cross_jump still merged. So no crack.

Time ~09:03. Item 4 ~16 min. Let me do 2 more tries and then finalize at 20 min.

Let me try one more cross-jump idea: make the *branch condition* differ by using a different variable for the test that's a *loaded* value in one tail? no.

Try o7: in the LINE tail, use `if (n < 4)` but with a `s16` cast: `if ((s16)n < 4)` — HImode compare (slti with a sign-extend?) might differ. Adds.

Try o8: reorder the two tails' color-load statements in the LINE tail (swap `poly->r1 = c[-4]` order)? changes code.

Honestly, let me finalize the WALL now. The rule says ≥20 min AND ≥30 tries; I have 35+ tries and ~16 min. The wall rule is a guard against premature walls. I've genuinely tried 35+ distinct bodies. Let me spend a few more minutes on one last idea, then finalize.

Actually, let me reconsider the arg launder once more with a fresh eye: the target's la is first because the set survived. The launder is an asm. What real C keeps a single-use constant set alive? 

**A `volatile` read of the variable!** If arg is `u8 * volatile`, the read `func_80052E38(arg)` becomes a load from the stack (2 insns: lw). We tested vd2 → 348 ins (score 37). Worse.

**A `const` variable?** tested.

**Taking the address of arg?** adds.

**Making arg a parameter?** no.

OK. WALL.

Wait — one more: what if `arg` is used in the *call* and the call is `func_80052E38(arg)` but arg is declared as a *struct pointer* and the call takes it... no.

Let me finalize.

Actually, hold on. Let me reconsider the possibility that the *original source* didn't need the early la at all, and the target's early la is an artifact of a *different* register allocation where a0 was free. What if we change the register allocation so that the arg copy naturally lands early? The la position is LUID-based. Hmm.

What if we move the `func_80052E38(arg)` call *before* the `ot = ...` statement but keep the pointer setups before it? Source:
```
arg = ...;
r = ...; mlo; mhi; c; va; vb;
func_80052E38(arg);
ot = ...;
```
Then the call is statement 8 (before ot). The target has ot before the call. But sched2 might reorder the ot computation (memory loads) before the call? The call has a memory clobber, so the ot loads can't move across it — they'd stay after the call → wrong. Unless the ot computation doesn't actually depend on memory... it loads D_800B9A02 and D_800A6610 (memory), so it can't move before a call.

So no.

What if the call is moved before the pointer setups but after ot? vh1 → score 12.

Let me check vh1's diff more: the la is first (good) but the spills/setups order broke. What if I ALSO keep a duplicate setup before the call to fix the order? No.

Hmm, what if I reorder so the call is after ot but the *pointer setups* stay before ot (source order), i.e.:
```
arg = ...;
ot = ...;      <- move ot before the setups? 
```
No, target has setups before ot.

The target order: arg, r, mlo, mhi, c, va, vb, ot, call. The la is at arg's position (first). So the set must survive.

OK, final answer for item 4: WALL, best 43, tag jump2-crossjump-arms (with the arg launder as the secondary combine-argcopy-sink).

Hmm, but the WALL rule requires 20 min. Let me wait until ~09:07 by doing a few more tests. Let me test o7 (s16 cast) and o8 (q2 pinned? no new pins).

Actually, let me use the time to test one *promising* idea for the arg launder: the `do{}while(0)` around the *call* (j6 gave score 10 ORDER, 346 ins — the la position might have changed!). Let me check j6's diff: score 10, so the la moved but something else broke. Let me disassemble j6.

If j6's la is first and only a minor order diff remains, maybe a tweak fixes it.

Let me check.
