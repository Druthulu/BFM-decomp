---
ts: 2026-11-06T15:55:33Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eHdN43gYFmZlDjhyNLzD
---
There's a tag `jump2-crossjump-arms` — "cross-jump merges byte-identical switch/if arms; renaming the regs gives no plain-C split". That fits the 2-output launder issue (cross-jump of the two `if (n<4)` arms).

And for the arg launder: `sched1-argcopy-hoist` fits (combine folds 1-use arg copy; sched keeps la late).

Given both are load-bearing and the walls list already has these tags, item 4 might be a WALL. But before giving up, let me try a couple more things for the arg launder since it's only score 4:

Idea: what if the arg variable is *used* by the call in a way that cse can't fold because the call's argument is an *address-of* of a local copy? no.

Idea: use `func_80052E38((void *)arg);` where arg is declared as an array? no.

Hmm, let me look at the flow dump to see whether a *different declaration order* changes the la position. Actually, the la position is the only diff. What if we make the arg assignment the LAST statement before the call but with a *second use*... 

Wait, actually: what if we assign arg and then use it in a *comparison that's real*? The function has no natural comparison.

What if `arg` is used as the argument to `func_80010A08`? no, different function.

Hmm. Let me look at what func_80052E38 does — maybe it's "SetDefDrawEnv" or similar. Not helpful.

Let me try the keepalive-free "second use" via a *dead* use that survives flow: e.g., `if (arg == 0) return;`? adds branch.

What about `func_80052E38(arg); func_80052E38(arg);`? adds a call.

OK, let me try one more idea for the arg launder: pass the address through a *local struct* field:
```
arg = &D_800AF648;
func_80052E38(arg);
```
vs
```
arg = (u8 *)&D_800AF648;
```
same.

What if we declare `extern u8 D_800AF648[]` and use `arg = D_800AF648;`? same constant.

Hmm, what if `arg` is set from a *pointer difference*: `arg = &D_800AF648 + (0);`? identity.

I'll accept that the arg launder is hard.

Actually, wait. Let me reconsider the problem: maybe the target's early la comes from a *different* C construct: what if the original source had `func_80052E38(&D_800AF648);` as the LAST statement of the prologue, and the la was *hoisted* by sched2 because of a *store* dependency? No, the la has no deps.

Hmm, let me look at the target's sched2 dump — oh wait, we don't have the target's RTL.

Let me try: what if `arg` is used to *initialize* another variable that is used? e.g. `ot = (u32)arg;`? wrong.

I think item 4 is a WALL. But let me spend a bit more time on the 2-output launders, since if I could crack those and keep the arg one, that'd be PARTIAL:launder (but c3 with arg launder kept scored 39, so the 2-output removal alone isn't 0 either).

Hmm, both must be cracked for MATCH. Given the difficulty, WALL with best lever-free 43 seems right.

But the WALL rule requires ≥20 min and ≥30 scored tries. Item 4 started at ~08:47 (orig extraction). It's 08:55 now, ~8 min. I have ~30 tries? Let me count: c1, c2, c3, va1-3 (3), vb1-4 (4), vc4-6 (3), vd1-3 (3), ve1-3 (3), vf1 (1) = 1+1+1+3+4+3+3+3+1 = 20. Need 30 and 20 min. I need ~10 more tries and ~12 more minutes. Let me keep experimenting.

More ideas for the arg launder:
- Make arg a `void *` variable.
- Set arg via a cast from `u32` with a `u32` variable.
- Use `func_80052E38((void *)&D_800AF648);` direct (no arg variable) — then there's no early la at all; the la would be at the call. Same score 4 presumably.
- Use a *struct pointer*: `arg = (u8 *)&D_800AF648;` no.

For the 2-output: 
- Swap the order of the two tails' color-load statements? That changes code.
- Use different variable names for q in the two tails (q and q2, both pinned $2?) — adding a pin is a new lever (not allowed).

Hmm, what about the `#line` trick WITHOUT the asm: the two tails' insns have the same line (900). If we give them DIFFERENT line numbers (e.g., `#line 900` for the first tail and `#line 901` for the second), cross_jump compares... only ASM_OPERANDS use file+line. Without asm, no effect. Tested.

What about a zero-byte statement that produces a different insn in each tail? e.g. `do { } while (0)` around one tail — flow deletes the loop notes; the insns identical. Probably no effect. Let me test: wrap the second tail's `if (n<4)` in a do-while (C0535) — maybe the LOOP notes persist and make the blocks non-identical? C0535 says do-while splits cse1's EBB. If the EBB split prevents the *test unification* (not cross-jump), it might help! Let me test wrapping the `if (n < 4)` in each tail with do-while(0).

Variant g1: wrap the POLY tail's if(n<4) block in do-while(0).
Variant g2: wrap both.

The do-while must have `// !FAKE: do-while`.

Let me construct. The block text (POLY tail):
```
                        if (n < 4) {
                            q = (u8 *)func_80010A08(8);
                            ...
                        }
```
Wrapping: `do { if (n < 4) { ... } } while (0);  // !FAKE: do-while`.

Let me do it for both tails in c1 (all launders removed) — but c1 has other diffs. Better on c3 (arg launder kept, 2-output removed) to isolate the 2-output fix. Let me generate g1 (wrap both tails) on c3 and score. If the cross-jump is prevented, score should drop toward 4.

Actually, the do-while around the if would put the if in a loop body; loop.c might optimize. Let me try.
