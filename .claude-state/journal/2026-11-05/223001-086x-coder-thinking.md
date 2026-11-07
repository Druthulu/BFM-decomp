---
ts: 2026-11-06T05:30:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FyH8nIhYwu99tawjZKxU
---
None cracked; best stays 10. The base (nobar) is 10. The residual is the early-return block merge and the delay-slot fill.

Let me look closer at the residual with a promising variant (score 10) — v_base is identical to nobar. The diff showed:
- mine: `beqz v0, 5f98` (branch to the shared return-0 block at 5f98) vs target `bnez v0, 5f3c` + fallthrough `j 5fe8; move v0,zero`.
- mine's default/case paths jump to a shared 5fe0 epilogue via `j 5fe0; move v0,zero` where target has `j 5fe8`.

Wait, the addresses differ by the function layout. Let me get the diff for v_base again and think.

The core: mine has ONE shared `return 0` block (at 5f98 in the nobar object: `j 5fe0; move v0,zero`) that all return-0 paths branch/jump to. Target has TWO separate return-0 sites: the early-exit (`j 5fe8; move v0,zero` at 5f34) and the default (`j 5fe8; move v0,zero` at 5f68). Actually target: early exit at 5f34 `j 5fe8; move v0,zero`, default at 5f68 `j 5fe8; move v0,zero`, case4-fail at 5f7c `j 5fe8; nop`? Let me re-read target:

```
5f2c: bnez v0,5f3c      # if (x <= 0x4000) goto body
5f30: li v0,3           # delay slot (for body compare)
5f34: j 5fe8            # else return 0
5f38: move v0,zero      # delay slot
5f3c: body...
5f50: beq v1,v0,5f84    # case 3
5f54: slti v0,v1,4
5f58: beqz v0,5f70
5f5c: li v0,2
5f60: beq v1,v0,5f90    # case 2
5f64: li v0,1           # delay slot
5f68: j 5fe8            # default return 0
5f6c: move v0,zero
5f70: li v0,4
5f74: beq v1,v0,5fa8    # case 4
5f78: move v0,zero      # delay slot
5f7c: j 5fe8            # default return 0
5f80: nop               # delay
...
5f90: lhu v1,52(a0)     # case 2
5f98: beq v1,v0,5fb8    # if (p->0x34 == 1) goto hit
5f9c: move v0,zero      # delay
5fa0: j 5fe8            # return 0
5fa4: nop
5fa8: lhu v0,52(a0)     # case 4
5fb0: bnez v0,5fe8      # if (p->0x34 != 0) return 0
5fb4: move v0,zero      # delay
5fb8: hit...
```
So the target has THREE distinct `j 5fe8; move v0,zero` return-0 sites (5f34, 5f68, 5f7c/5fa0), i.e., the `return 0` statements were NOT merged by cross-jump. The barrier prevented jump2's cross-jump from merging them.

Mine: `5f2c: beqz v0,5f98` where 5f98 is a shared return-0 block `j 5fe0; move v0,zero`. So mine merged the early return with the default.

To prevent cross-jump in pure C... cross-jump merges identical blocks. The blocks `return 0` are identical. To keep them separate, make them *not identical*: e.g., different return values spelled differently? `return 0;` vs `return (s32)0;` — same code.

Hmm, what if the early return is `return 0;` and the default is `return 0;` — identical. Cross-jump merges. The barrier prevents it. A real C move that prevents cross-jump: make one path return a different constant that happens to be 0 at runtime? E.g., `return st & 0;`? That emits an `andi`. No.

Alternatively, make the CFG such that cross-jump doesn't apply: e.g., if the early-exit block is not a simple `return 0` but has a label that is targeted by a jump... Hmm.

Actually, cross-jump (jump2) merges blocks only when they're at the end of the function and reachable by jumps. The barrier asm creates a non-jump insn between, blocking the merge.

Could we make the early return not a bare block by writing `if (x > 0x4000) { return 0; } else { ... }`? The else block then is the body. Cross-jump might still merge the return-0 with the default.

This looks like the `jump2-crossjump-arms` / `jump2-crossjump-fallthrough` wall family. There's a wall tag `jump2-crossjump-arms`: "cross-jump merges byte-identical switch/if arms (incl. j+delay store); renaming the regs gives no plain-C split (T11 G18 func_8017D508)". And `jump2-crossjump-fallthrough`.

So item 5 is likely a WALL: `jump2-crossjump-arms` (the `return 0` blocks merge without the barrier).

But hold on — the target has the return-0 blocks *separate*, so the barrier is what keeps them separate. In pure C, jump2 merges them. So WALL.

Hmm, but wait: could we use a real function call or a `volatile`? No levers.

Before concluding, let me try more variants that change the *shape* so cross-jump has nothing to merge:
- Make the early return `return func_8012BD14(...) & 0;`? adds code.
- Use a `do { ... } while (0)` block with `break`? That might change the CFG.
- Put the early return inside a loop `do { if (x > 0x4000) break; ... } while(0); return 0;` — hmm, `do{}while(0)` needs the !FAKE comment and is allowed (C0535). That creates a loop structure that jump2 might not cross-jump.
- Use `goto` to a label placed right before the final `return 0`.

Let me try a few more shapes. Also, the residual after the merge is only 10 (mine 58 vs target 60) — the merge saves 2 insns. If we could block the merge, we might get 0.

Let me think about cross-jump: it merges two blocks if they are identical and one is a "cross-jump" candidate. The `return 0` at the early exit and the `return 0` at the default both become `j epilogue; move v0,zero`. Cross-jump finds them and merges into one shared block.

What if the early return's epilogue path is a *fall-through* rather than a jump? E.g., restructure so the early-exit block is at the very end (after the body). Like:
```
if (x <= 0x4000) {
   ... body ...
   func_80178BF8();
   return func_80172710;
}
return 0;
```
That's variant inv1 — score 11, and it put the early return at the end. Hmm, but target has the early return at the *beginning* (j 5fe8). So inv1's layout differs (score 11).

Let me look at inv1's diff to see how close. Actually score 11 with mine 61 vs target 60.

Let me try: `do { if (x > 0x4000) break; ... } while (0); return 0;` and `goto`-based.

Also: maybe use a `switch` with a `default:` that does `return 0` and an early `if` that does `return 0` — already.

What about making the default return `return (s32)func_80172710 & 0;`? no.

Let me try the do-while(0) shape and a few goto shapes. Also try placing the early check *after* loading p/st (so the early return block isn't identical to the default? no, it's still `return 0`).

Cross-jump merges only the *blocks*, so both returns are merged regardless of position.

Hmm, what if one return-0 path has an extra harmless statement that survives, e.g., the default path writes something? No.

OK, item 5 likely WALL. But let me do a few more tries to be fair, and importantly, count tries: I've scored 21 variants. I need ≥30 scored tries. Let me add ~12 more variants.

Let me also reconsider: the target's early-exit is at 5f34 `j 5fe8; move v0,zero` and the default at 5f68 `j 5fe8; move v0,zero` — identical 8 bytes! Why didn't cross-jump merge them in the target? Because the asm barrier sits between (the asm is after the early return, before the switch). Actually cross-jump works within the function; the barrier insn `#APP #NO_APP` between them blocks it. Right.

So the wall mechanism: jump2 cross-jump merges the byte-identical `return 0` blocks; only an asm insn between them stops it. That's `jump2-crossjump-arms`.

Can pure C place a non-jumpable insn between? Any real instruction that must execute between them would change semantics/codegen. E.g., a store. No.

Alternatively: can we make the two blocks *not identical* in a way that produces the same bytes? E.g., if the early return is `return 0;` and the default is `return 0;` — identical. If the default is reached after `st` is dead, maybe the register allocator gives a different reg? No, v0 for return.

I'm fairly confident item 5 = WALL jump2-crossjump-arms.

But wait — let me reconsider the *other* diff in item 5: the delay-slot placement. Even if cross-jump were blocked, the delay slots differ. But those are consequences of the merge.

Let me try a few more variants including do-while(0), then move on.

Actually, let me reconsider the target: the early return is `bnez v0,5f3c` — a *branch* into the body, with the return-0 as fall-through. In mine: `beqz v0,5f98` — branch to the return-0 block, with the body as fall-through. This inversion is due to the target's block ordering: the compiler put the return-0 as fall-through. If we restructure the source as `if (x <= 0x4000) { body } else return 0;` — that's inv1. inv1 scored 11. Let me look at inv1's diff.

Let me check a few residuals.
