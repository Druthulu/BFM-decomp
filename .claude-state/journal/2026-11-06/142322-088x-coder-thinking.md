---
ts: 2026-11-06T21:23:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_OEHXeclvb3MDIO8cv89P
---
The remaining 6 extra are exactly the tp rematerialization: mine has `lui a0,0x0; lh a0,-8(a0)` vs target `lh a0,-8(s0)` — 3 pairs = 6 extra instructions. So the tp launder's effect (keep tp in s0) is the remaining issue. The f2/f3 duplicate assignments didn't break REG_EQUIV.

So I need a real-C way to keep tp in a register. This is the "const symbol ptr" rematerialization problem.

Hmm, target's s0 = tp. Mine rematerializes D_801274F0 for each of the 3 uses (lh -8, lh -6, lh -4) and the store base.

The launder forces tp into a reg. Real C: prevent REG_EQUIV rematerialization.

Idea: make tp's value not a compile-time constant. E.g., compute it as `tp = (s32)D_801274F0_8017CF48;` — constant. If instead we read a global that equals it... changes code.

Idea: use `tp` in a way that requires its address? No.

Idea: make tp a pointer and use pointer arithmetic that combine can't fold: `tp = (s32)((u8 *)D_801274F0_8017CF48);` same.

Idea: What if we pass tp to a function call? No, there's no such call.

Idea: assign tp from `base`? base is a different address.

Hmm. Actually, maybe the target keeps tp in s0 because of the *store* `*(Blk8*)tp = *(Blk8*)buf;` — a 8-byte store via a pointer. If tp is a pointer variable, the store base is a reg. Then the later `*(s16*)(tp-8)` uses the same reg. But REG_EQUIV allows rematerialization because tp is a constant. The launder breaks REG_EQUIV.

Real C to break REG_EQUIV: the assignment `tp = (s32)D_801274F0_8017CF48` is a constant symbol → REG_EQUIV. If we could make it `tp = (s32)D_801274F0_8017CF48;` then modify it once: `tp = tp + (something that's 0 at runtime but not compile-time)`. What runtime-zero can we use? 

`flag` is a runtime variable, but `flag & 0` folds. `flag - flag` folds.

What about a value known to be 0 but not folded, like `buf[0] - buf[0]`? Folds.

Hmm. What about using the low bits of a pointer: `tp = ((s32)D_801274F0_8017CF48) | 0;` folds.

There's no clean real-C way to break REG_EQUIV for a constant without changing semantics. This is likely a genuine WALL for the tp launder.

But wait — maybe the target's tp isn't D_801274F0 rematerialized but something else. Let me check: target `lh a0,-8(s0)`. s0 = ? At the epilogue, s0 is used. Earlier target `move s1,a0` (s1=a0). And s0? Let me see where s0 is set in target. The target prologue: sw s1,28; move s1,a0; sw ra,40; sw s3,36; (and maybe sw s0,32). So s0 is callee-saved. s0 = tp = D_801274F0. So target materializes D_801274F0 into s0 once.

So the tp launder is load-bearing and hard to replace. 

Given this, item 3 is a WALL. But let me try a couple more real-C ideas for tp:

Idea: use a `union` or `struct` pointer: `Blk8 *tp = (Blk8*)D_801274F0...` — same constant.

Idea: What if tp is loaded from the *code* as a function pointer? no.

Idea: assign tp from `D_801274F0_8017CF48` but with a cast through a volatile? adds load.

Idea: `tp = (s32)&D_801274F0_8017CF48;` — address-of a symbol, same.

Idea: Compute tp from `buf`: `tp = (s32)D_801274F0_8017CF48 + (buf[0] & 0)`? `buf[0] & 0` = 0, folded. `buf[0] * 0` folded.

No good.

Hmm, but wait — maybe the compiler keeps tp in a reg if tp is used MANY times (more refs → higher priority vs rematerialization). Currently tp is used: store base, tp-8 (load), tp-8 (store), tp-6 (load), tp-6 (store), tp-4 (load+store), and the final func_8017D280(a0, tp-8). That's ~8 uses. Still rematerialized.

Actually, maybe the issue is that REG_EQUIV rematerialization is chosen because the constant is "cheap" (lui+lh = 2 insns) vs keeping a callee-saved reg (save/restore). With 8 uses, keeping in a reg should win... but the register pressure (s0 needed elsewhere) might force rematerialization.

In target, s0 holds tp. In mine, s0 is used for something else (the buf address!). Remember the register pairs s0->s2 x10, s2->s0 x8. So the register assignment is shifted: mine uses s0 for buf-ish and s2 for base, target uses s0 for tp and s2 for base, s1 for a0. 

The frame: target 40, mine? Let me check. f1 mine 212 ins. The extra 6 are the tp rematerialization. If the compiler had a free callee-saved reg, it would keep tp. But all are used.

So the tp launder's role: it forces tp into a callee-saved reg, displacing something. Without it, register pressure causes rematerialization.

This is a global-alloc priority issue: tp (const, rematerializable) loses to other pseudos. The launder raises its priority (2nd set).

Real C to raise tp's priority: more refs. But cse merges duplicate assignments.

What if we use tp in an extra genuine way? E.g., `tp = (s32)D_801274F0_8017CF48; ... ` and use `tp` in a comparison that's real. But that adds code.

OK, I'll declare item 3 a WALL. But wait — the budget: item 3 started ~14:42, now ~14:55 (13 min). A WALL needs ≥20 min and ≥30 scored tries. I have ~6 tries. I need more time/tries. Let me spend more effort, or reconsider.

Actually, the rule: "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)". So I must do ≥20 min AND ≥30 tries to record a WALL. Otherwise it's not an attempt (I should keep going).

Hmm, that's demanding. Let me think harder about cracks.

Let me reconsider the tp launder. The moves log has MANY "launder->real 2nd set" MATCHes where the 2nd set is `pv = pv & 0xFF000000`. For a constant pointer, maybe the equivalent is to split the address computation: `tp = (s32)D_801274F0_8017CF48;` — what if we compute it in two steps: `tp = (s32)D_801274F0_8017CF48;` no.

Wait — maybe the real 2nd set can be a *real* operation on tp that the code needs: the code does `*(s16*)(tp - 8)`. What if we introduce `tp2 = tp - 8;` and use tp2? That's a real computation (addiu) creating a 2nd pseudo. But target uses displacements (tp-8), not a computed tp2. So no.

Alternatively, maybe the crack is to make tp's uses NOT rematerializable by using it as a *byte pointer with increments*: 
```
u8 *tp = (u8*)D_801274F0...;
*(Blk8*)tp = *(Blk8*)buf;
t0 = func(*(s16*)(tp-8), ...);
...
```
Same.

Hmm. Let me look at how the OTHER items in this shard's family (same TU ov_SC03_107) were cracked. The moves log might have entries for func_801789AC (the TU) or nearby. Let me grep moves for 801789 or 8017CF.

Also, this function might be a "twin" of another cracked function. Let me grep moves for similar structure.

Let me search moves.md for "D_801274F0" or "8017CF48" or "rematerial".
