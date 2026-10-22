---
ts: 2026-10-22T01:08:41Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Q50fb8NaV4XC72qudwQp
---
Now the remaining 5 items: func_80191020 (2), func_8017D96C (2), func_8017EA24 (3), func_80183098 (5), func_8018C730 (6).

Let me apply the "k sites" insight to func_8017D96C / func_8017EA24 (2 asm sites): the count matters! For D96C, the sites are 2: the v1 site and the e site. The best was "cast-dow" (2) and "cast-dowcast" (1, but the e cast truncates a pointer).

Hmm, with the "count" insight: maybe replacing the *same* site multiple times helps! E.g. the v1 site with 2 casts, or the e site with a do-while + N casts.

Hmm, for the e site (a pointer), a cast truncates → not faithful. But what about *multiple* do-while(0)s at the e site? Or a do-while + a real 2nd set of e (a re-computation: `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` — the same value ✓)!

That's the "real 2nd set" move: at the e site, `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` re-reads the same field → the same value ✓ (the field isn't modified in between — hmm, in the case1 branch: `e = unk20;` then the do-while then `e = unk20;` — between them, `func_8001C810(...)` was called *before* the assignment. Hmm, the call is before the first assignment. So the re-read gives the same value unless the callee modified it — the callee is called before, so ✓).

Let me try for D96C/EA24:
- site 1 (v1): `v1 = (s16)v1;` (a real 2nd set; v1 = mode ∈ {0,1,2,3} ✓ value-preserving) and/or a do-while.
- site 2 (e): `e = ((Unkstruct_800B5CB8 *)s0)->unk20;` (a real 2nd set, the same value ✓) and/or a do-while.

Let me generate these variants and score. Let me write a generator for the two sibling items.

Also, for func_8018C730 (score 6): the lever materializes a dead constant (the function address) in v0. Hmm, with the "do-while" insight: the do-while scored 6 too. The problem: the constant must be *materialized* in v0 at the return — the only way is a return value (a void function drops it). Hmm.

Hmm! What if the *asm's* constant input is replaced by a real use of the function address? E.g. `ret = (s32)func_80172710;` — a dead assignment → GCC removes it. Hmm.

Hmm, what if the value is *used* in a way that keeps it in v0 at the return: e.g. the function's last statement is a *call* whose argument is the address? No, the target has no such call.

Hmm: the target's then-branch: `lui v0; addiu v0,v0` (= &func_80172710) then `j` to the epilogue. And the else branch: `move v0,zero`. So v0 holds the "return value" — the function is void in C but the game's asm returns a pointer!

Hmm! Since the *signature* can't change (the constraint), hmm.

Wait — can it? "no signature or decl change outside the body (callers stay as they are)". The declaration `void func_8018C730(s32 a0r);` is outside the body. The *definition* is the body (the whole function text is what I replace!). Hmm: the "body" in the brief = "a lever-free body of `func`" — the function definition (as a bare definition). So the signature *is* part of what I write! Hmm, but the constraint says "no signature or decl change outside the body (callers stay as they are)" — the callers stay as they are, i.e. I must not change the *callers*; but the function's own signature... hmm, if I changed `void func_8018C730(s32)` to `s32 func_8018C730(s32)`, the callers (which ignore the return value) would still compile (in C, calling a function that returns a value and ignoring it is fine) — but the *declaration* in the TU (outside the body) would conflict → a compile error! Unless the TU's declaration is also void → a conflict → compile error.

So the signature must stay void. Then how to materialize the constant in v0?

Hmm: `ret = (s32)func_80172710;` where ret is a local → dead → removed. Hmm, but what if `ret` is *volatile*? Then the store would be emitted (a sw) → not the target.

Hmm, what if the assignment is to a *global*? → a sw. No.

Hmm, what if the value is passed as an argument to a call that the target has? The target's then-branch: `jal func_80188E1C` (func_80178BF8) with a0 = s0 (the param) — hmm, `move a0,s0` is in the delay slot of the jal. Hmm, and the *first* call is func_8012BD14 with a0 = unk64.

Hmm, what if the address were used as the *argument* of a call? The target's calls: func_8012BD14(unk64) and func_80178BF8() (no args). Hmm, so no.

Hmm, so the constant is materialized but unused — only an asm can do that. Hmm, unless...

Hmm! What about the *do-while* + a real use: e.g.
```
ret = (s32)func_80172710;
do { } while (0);
return;
```
The assignment is still dead → removed.

Hmm, what if the *function* ends with `return;` and the value is in a variable that's... no.

OK, item func_8018C730 might be a WALL (flow-unused-result). But wait: the *else* branch's `move v0,zero` is also dead — the target has it. In plain C, `return 0;` in a void function → no code. So both are dead in C.

Hmm, so the whole function's difference (5 instructions: lui+addiu+j? hmm) is the dead-constant materialization. Hmm, the score was 6 (mine 18, target 23).

Hmm, the do-while scored 6 too. Hmm.

So: is there ANY plain-C way to make gcc materialize a constant into v0 at the end of a void function? Hmm...

What if the function *returns* a value in a way GCC keeps? E.g. `return (s32)func_80172710;` in a void function → GCC 2.7.2 gives a warning and drops the value (we tested: 18 ins).

Hmm, what if the function is declared `void` but the *body* uses a `return expr;`... same.

What about the *else* branch: `ret = 0;` → dead.

Hmm, so item func_8018C730 = WALL (flow-unused-result). But I need ≥30 scored tries and ≥20 min. Let me generate a bunch of variants for it (the do-while, the casts, the frame, the return-value forms, etc.) — the combos gave 24. Let me run the posgen + a few more to reach 30+.

Let me now do a batch: posgen for func_8018C730, func_80183098, func_80191020, func_8017EA24, and the D96C/EA24 "real 2nd set" variants.

Let me write the D96C/EA24 generator (the real 2nd sets) and run posgen for the rest, then score everything in one background batch.
