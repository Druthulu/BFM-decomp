---
ts: 2026-11-06T17:02:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW47
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_HumaCOA689VGgtV36Gl3
---
Without the a0 pin: 22 — worse. The pin is needed (other-kind lever, allowed to stay).

So z01 (3) is the best. Hmm, one instruction off.

Let me think about the `addiu s1,sp,32` once more. In y01 it doesn't appear. The difference is the struct assignment vs hand-expanded copy. 

Idea: use the hand-expanded copy but WITHOUT the s-launder, and instead make the copy read from a *struct variable* copy:
```
Blk20 s = D_800AE620;   // struct assignment to a local
t0 = s.w[0]; ...
```
That adds a 32-byte local (frame). No.

Idea: `m = D_800AE620;` then immediately `q = &m; q = 0;` — tested (aa01, 3).

Idea: maybe the s1 cache comes from the *RotMatrixY* argument being &m and the *func_800484EC* argument being &m, and cse's `find_best_addr` deciding to keep it. If I make the func_800484EC call's first argument a *different* pointer variable that is assigned after the call... no.

Hmm, what about making the RotMatrixY argument a *pointer to a different member* so the address expression differs? e.g., `RotMatrixY(ang & 0xFFF, &m);` vs `func_800484EC((s32)&m, ...)`. Same.

What if I pass `(s32)&m` to RotMatrixY too (cast), so both are `(s32)&m`? Same.

Let me try: make the RotMatrixY call use a `Blk20 *` cast from a `s32` variable:
```
s32 ma = (s32)&m;
RotMatrixY(ang & 0xFFF, (void *)ma);
func_800484EC(ma, ...);
```
Then `ma` is a variable holding &m; the compiler would keep it in a register (s1) — worse.

What if the two uses are in *different blocks* so cse can't merge across? They're already in the same block.

OK. Given time constraints (item 4 needs 20 min for a WALL; started 09:56, now 10:08 = 12 min), let me continue a bit more with different ideas, or accept a WALL with best 3.

Actually — wait. Let me reconsider the problem: maybe the struct assignment isn't needed at all. The s-launder's job is to keep the D_800AE620 base in a register. What if instead of `s = &D_800AE620` (constant), we use a *global variable* that holds the address? E.g., there might be a symbol. No.

What if we read the 8 words via an array of a type that forces a register base: `u32 *s = (u32 *)&D_800AE620;` then `t0 = s[0];` — cse remats.

What if we make the base pointer a *function parameter* of an inner block? No.

What if we use a `union`? no.

Hmm, here's an idea: the target's copy block has the base in a2 and reads with displacements. The struct assignment produces exactly that. So the struct assignment is the right replacement. The only issue is the &m cache, which is a *separate* cse decision.

In y01, the q dead-reset killed the &m cache. In z01, why doesn't it? Let me check if z01's q block is actually present. z01 was derived from y01: y01 has the q block with `q = 0;`. Yes.

Hmm, let me look at z01's source to be sure.

Actually, maybe the difference is that in z01 the struct assignment `m = D_800AE620;` is a *single statement* that cse processes, and cse's `cse_insn` for the block move might set up the &m equivalence differently.

Let me try: do the struct copy through a *local struct variable* that is then... no.

Let me try adding a dead-reset of the address right after the copy using a pointer that is *the same type* and used as the store base:
```
Blk20 *mp = &m;
*mp = D_800AE620;
mp = 0;
```
ab01 = 3 (the reset didn't help).

Hmm, what if the reset is *before* the RotMatrixY but the RotMatrixY uses mp (not &m)? 
```
Blk20 *mp = &m;
*mp = D_800AE620;
RotMatrixY(ang & 0xFFF, mp);
mp = 0;
func_800484EC((s32)&m, ...);
```
This keeps mp live across... no, mp dies before the call? mp=0 after RotMatrixY, so mp is live across the RotMatrixY call → cse keeps &m in a callee-saved reg for mp? But mp dies at mp=0 right after the call, so no need to keep it across. Hmm, but the call clobbers caller-saved regs, so mp must be in a callee-saved reg during the call if live after. Since mp=0 is after the call, mp is live across the call → s1. Then the func_800484EC's &m remats. But the `move a1,s1` would appear instead of `addiu a1,sp,32`. Not target.

The target has `addiu a1,sp,32` in the delay slot. So the RotMatrixY arg is rematerialized, not a variable.

So we need cse to remat at BOTH calls. The struct copy shouldn't create a cached &m.

Let me try making the struct copy destination address not look like &m: copy to `m` via a cast, e.g., `*(Blk20 *)&m = D_800AE620;`? Same address.

What about copying to a *member*: `m.w[0] = D_800AE620.w[0]; ...` (hand-expanded) — that's the original, which needs the s-launder.

Hmm, wait: the original hand-expanded copy reads `s->w[i]` where `s = &D_800AE620`. Without the s-launder, cse remats the source base (6 extra). What if we write the source as a *struct assignment* but the destination as hand-expanded? E.g., `m = D_800AE620;` is the only way to get the source base in a register.

Alternatively: `m = *(Blk20 *)&D_800AE620;` — same.

What if we copy via a local pointer with a *volatile* qualifier on the pointer only (not the target)? `Blk20 *volatile s` — that forces s to memory. no.

OK, let me accept the WALL with best 3, but first let me try 2-3 more: 
- ag01: `m = D_800AE620;` + RotMatrixY direct + func_800484EC direct (no q at all) → ac01 = 3.
- ag02: `m = D_800AE620;` + q block for RotMatrixY + q block for func_800484EC (two separate blocks).
- ag03: reorder: move the q block before... no.

Actually, maybe the &m cache is unavoidable with the struct assignment because the copy's `sw` instructions use sp+32 and cse records the address constant, then the RotMatrixY arg materializes it and cse keeps it for the second call. The q reset doesn't kill the *address* equivalence.

To kill the address equivalence, I'd need a store to m between the two uses (kills the address? no, addresses aren't killed by stores).

What if I add a second struct assignment between the calls? `m = D_800AE620;` again after RotMatrixY — that would emit another 32-byte copy (wrong).

What if the func_800484EC call uses `&m` but m is accessed through a *different* object? no.

OK: WALL, best 3, tag? The residual is a cse decision: cse keeps &m in a callee-saved register across the RotMatY call where the target rematerializes. That's `cse-const-addr` (cse folds/substitutes a constant/absolute address the target keeps base-relative) — inverse. Or `cse-hardreg-copy-forward`. Hmm. The tag list: `cse-const-addr` — "cse folds or substitutes a constant/absolute address the target keeps base-relative". Here cse *caches* a stack address the target rematerializes. Close enough? Or `cse-fixed-global-cache`.

Actually, let me check the new walls.txt (it changed).

But hold on — the item's levers are keepalive,launder. I removed all of them (the q launder via dead-reset, the s launder via struct assignment, the keepalive via the struct assignment replacing the hand-expanded copy). The remaining score-3 residual is a cse/regalloc artifact. A WALL with best 3.

But the 20-min rule: item 4 started ~09:56, now ~10:09 = 13 min. I need ~7 more minutes. Let me use them to try a few more ideas.

Idea: use the struct assignment but pass a *different* expression for func_800484EC that's not CSE-able with &m: e.g., `func_800484EC((s32)&m, (s32)vec, (s32)vec)` → `func_800484EC((s32)&m.w[0], ...)` tried (ad03, 3). What about `(s32)(&m) + 0`? folds. `(s32)&m | 0`? folds.

Idea: use a union to alias m so the address expression differs: declare `union { Blk20 b; s32 v[8]; } u;` and use `&u.b` for RotMatrixY and `&u.v[0]` for func_800484EC. Different expressions, same address → cse might remat both. But the frame/decl changes.

Hmm, risky.

Idea: the target's `addiu a0,sp,32` is computed BEFORE the RotMatrixY call (sched hoisted). If the source order puts the func_800484EC call's &m after the RotMatrixY call, cse would still CSE it. 

Idea: make the RotMatrixY call's second arg a *separate* variable that is NOT &m but a copy: `void *q = &m; RotMatrixY(...,q);` and then `func_800484EC((s32)&m,...)` — z01 = 3.

I think the cse cache is driven by the *struct assignment's* address materialization. Let me try one thing: perform the struct assignment BEFORE the `ang = rand();` call, so a call intervenes between the copy and the &m uses. That might kill the cached register. But it changes the schedule/order → likely worse.

Alternatively, perform the struct assignment in a separate block scope `{ Blk20 tmp; ... }` no.

Let me try: move `m = D_800AE620;` earlier (right after the p setup), so calls intervene. The target's copy block is after `ang = rand()` (e20). If I move it earlier, the bytes change. Not good.

OK, let me try the union idea and a couple more, then finalize.

Actually — wait! Let me reconsider the &m cache. What if it's caused by `vec`? The target: `addiu a1,sp,16; move a2,a1`. Mine same. The s1 holds &m.

What if I name the &m pointer for func_800484EC *before* the RotMatrixY call in source, so cse sees the same variable... no.

Let me try the "dead-reset of the address expression" trick: after the struct copy, add a *store* to m (e.g., `m.w[0] = m.w[0];`)? That would be a load+store (2 insns).

Hmm.

Let me look at the walls.txt update and check the time. Then try 3 more variants and finalize.
