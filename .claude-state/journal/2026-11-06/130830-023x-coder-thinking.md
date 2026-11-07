---
ts: 2026-11-06T20:08:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW49
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Ncv3cAbltFt6swcetrYs
---
Excellent. The vA candidate matches target except:
- target 2148-2154: `lw v1,0(s1); li v0,-1024; sh v0,10(v1)`
- mine: `lw v0,0(s1); nop; sh s4,10(v0)` with `li s4,-1024` hoisted at 2124.

So only the -0x400 constant hoisting differs. Everything else identical (the extra nop is the load delay slot: `lw v0,0(s1); nop; sh s4,10(v0)` — 3 insns; target `lw v1; li v0; sh v0` — 3 insns. So insn count same? mine has li s4 + sw s4 + lw s4 = 3 extra, but here mine[2150] lw v0,0(s1) then nop then sh — 3 vs target 3. And the target's register is v1 then v0.

Hmm wait, mine 2150: lw v0,0(s1); 2154: nop; 2158: sh s4,10(v0). Target 2148: lw v1,0(s1); 214c: li v0,-1024; 2150: sh v0,10(v1).

So mine loads into v0, target into v1. Then mine's -1024 in s4 (hoisted). The register diff "v0->v1 x2, s4->v0 x1".

Fix: get the `li -1024` back inside the loop into v0, and the reload into v1.

The `li s4,-1024` was hoisted by loop.c because the constant insn is inside the loop and its result is used once. Target kept it. Why? In target, the pinned $2 made the constant use $2, and loop.c's `move_movables` may refuse to hoist an insn that sets a hard register? Let me check loop.c conditions: it checks `REGNO_REG_CLASS`? Actually loop.c `move_movables` calls `maybe_never` etc. There's a condition: it won't hoist if the insn sets a register that is used elsewhere... Hmm.

More likely: the constant -1024 was in v0 in target because the *pseudo* for the constant was allocated v0 and the insn stayed. In mine, loop.c hoisted it because... hmm, why wouldn't it hoist in target too?

Let me think about loop.c: `move_movables` scans the loop, finds insns with invariant operands. For a `set` of a pseudo to a constant, it will hoist it if `reg_single_usage[regno]` (used only once in the loop) and not `loop_reg_used_before_after` etc. In target, the constant pseudo is v0 (a call-clobbered hard reg after reload? No, loop.c runs before reload). The pseudo for the constant is a normal pseudo. It should be hoisted the same in target unless the pseudo is used in a way that prevents it.

Wait — target's `li v0,-1024` — maybe in target's source, the store is `*(s16*)(v1+0xA) = -0x400;` and the constant is not a separate pseudo hoistable because... it is exactly the same as mine.

Unless the pin changes cse: the pinned variable v0 was used for the call result; the -0x400 store also uses v0? No, the pinned var v0 is `register s32 v0 __asm__("$2")` and the store `CAST_NONSTRUCT(s16, *p, 0xA) = -0x400;` doesn't mention v0. Hmm.

But with the pin, GCC cannot allocate any other value to $2, and the constant pseudo... would still be hoistable.

Hmm, so why is target different? Maybe loop.c's decision depends on register pressure: with the pinned v0 unavailable, the hoisted constant would need a callee-saved reg, and loop.c computes `loop_reg_used_before_after`/savings vs cost: it only hoists if the insn is "cheap" or the loop runs many times. The cost model: `move_movables` hoists if `loop_depth` and `insn_count * threshold`? There's a `threshold` variable adjusted by `loop_info->n_iterations`? In gcc 2.7.2 loop.c, `threshold = 5` or so and `if (insn_count > threshold) ...`. Hmm.

Actually, there's a known condition: `if (reg_single_usage[regno] && ... )` and also "don't hoist if the register is used in the loop more than once". And there's the "strength reduction"/"loop invariant" cost.

Alternatively the difference might be that in the pinned version, the constant pseudo is *shared* with something else, or cse made the constant part of an insn.

Let me test: does a variant that makes the -1024 not loop-invariant work? E.g., tie it to `i` or `off` in a value-preserving way that isn't an identity launder... The brief forbids identity-statement launders. But real C: e.g., write the store as `CAST_NONSTRUCT(s16, *p, 0xA) = -0x400 + (i & 0);` — identity, not allowed.

Real C idea: the target's `li v0,-1024` inside the loop suggests the value is materialized per iteration. What if we compute the constant from the loop's table value? No, semantics differ.

What about making the store value a variable that is assigned inside the loop but from a non-invariant operand? E.g. `s16 neg = -0x400;` then `*(s16*)... = neg;` — loop.c sees `neg = -1024` invariant, hoists.

What if the constant load is combined with the store by combine? `li v0,-1024; sh v0,10(v1)` — combine can't fold li into sh.

Hmm, what about using a cast that forces a temporary with a wider mode: `(s16)-0x400` same.

Alternative: prevent hoisting by making the loop body contain a call that clobbers? The loop already has a call. Hmm, loop.c hoists invariant constants regardless of calls, but it must place them in the preheader; the preheader here is before the loop. Since a call is in the loop, a constant in a call-clobbered reg is fine (constant is invariant). 

Wait, actually — look at where `li s4,-1024` is placed: at 2124, before the loop, in the preheader. So loop.c hoisted it. In target it stays. What makes loop.c not hoist? Let me read loop.c's move_movables for CONST_INT.

Let me grep.
