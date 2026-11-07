---
ts: 2026-11-06T16:56:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0aXVMN9f3DWZQR6XGEg7
---
Wait, the date says 09:56, not 10:16. So item 2 took 12 minutes, not 32. Good — my sense of elapsed time was off (the date at item 2 start was 09:44, now 09:56). So I have budget for item 2 up to 10:14; I've only used 12 min and 30 tries. The WALL requires ≥20 min AND ≥30 tries. I have 30 tries but only 12 min. Hmm, "a WALL needs ≥ 20 min and ≥ 30 scored tries on that item (fewer is not an attempt)."

So I can't declare a WALL yet at 12 min. I should spend ~8 more minutes trying. Let me use the time productively on the most promising angle.

The closest is no_t0c (5). Or no_ot (8). Let me think harder about no_ot: block-local ot takes t0.

Actually, wait: in the target, is ot block-local? ot is loaded and used in the same block (before the loop). Yes. The target's cnt is global (across branches). Local-alloc assigns block-locals first, taking t0. In the target, the block-local ot got t1 — because the pin. Lever-free, the local takes the first free caller-saved reg (t0). To make ot get t1, t0 must be taken by another block-local at ot's allocation point. E.g., if `sc` or `d` or another temp holds t0 with a longer life in that block.

Priority: the qty priority decides order. If another block-local has higher priority, it gets t0. In the target, t0 is cnt (global), so no local holds t0. In mine, ot (2 refs, life 2) has priority 1.0; other locals like `sc` (defs/uses), `t` etc. may have lower priority.

If we extend ot's life (move its load earlier but still in the same block), its priority drops, and another local (e.g., sc) might take t0 instead. But then cnt (global) still gets t1. Not helpful.

Alternatively, make ot's priority lower than cnt's *global* allocation? Local-alloc runs before global; globals don't participate in local-alloc. So a global can never win t0 against a block-local unless the block-local is dead where... Actually local-alloc gives t0 to the local; then global-alloc sees t0 used in that block and, if cnt's live range overlaps that block, cnt conflicts with t0 → t1.

So to get cnt=t0, NO block-local in cnt's live range may use t0. The ot local uses t0. So we need ot to get t1 or another reg.

How? Give t0 to another local that dies before cnt's birth? No — the conflict is about liveness; if a local uses t0 before cnt's birth (cnt born at the call), cnt doesn't conflict with it! Wait: cnt is born at `move cnt,v0` (after RotTransPers). ot is loaded AFTER cnt's birth. If ot used t0, cnt (live from birth) conflicts → cnt can't use t0.

If instead ot were loaded BEFORE cnt's birth, ot could use t0 without conflicting with cnt, and cnt could then get t0 after ot dies! But moving the ot load before the call changes the instruction order... unless sched1 sinks it back to after (it did: ot_mid stayed 8, meaning the load was still after the div).

Hmm, sched1 sank it back to the same place. Then the allocator still saw ot after cnt's birth.

What if we make ot use a register that's not t0 by giving it a *copy preference*? E.g., `ot = something` where the source is in t1? no.

Alternative: make ot a global (live across the branches) so it's not block-local: then global-alloc allocates cnt and ot by priority; cnt (more refs) gets t0 first, ot gets t1! That's exactly what we want.

How to make ot live across a branch without changing instructions? Use ot inside the loop (the target doesn't, but maybe a use that's dead/free). E.g., `AddPrim(ot, prim)` in the loop instead of otAddr? That would change the add (otAddr = ot+cnt). Hmm, if the loop used ot directly, we'd need to keep ot live — but then the addu would use ot... The target uses otAddr (s6) in the loop: `addu a0,s6,...`? Let me check the target loop's AddPrim: `move a0,s6`? From the earlier diff: target `move a0,s6` and `move a1,s3`. So otAddr=s6, prim=s3.

What if the source uses ot in the loop in a *dead* way, e.g., `if (ot == 0) {}`? That's a branch (instructions).

Hmm, what about declaring ot as `s32 ot` and using it in the loop's AddPrim as `AddPrim(otAddr, prim)` — no.

Alternatively make cnt block-local? cnt is live across the two early-return branches. If the early returns were restructured so cnt doesn't cross a branch... The target has them (`blez t0, end`, `bltz v0, end`).

OK, maybe try: make ot live across the branch by loading it before `if (cnt <= 0) return;` — that's ot_early (score 21, worse: the load stayed early and changed code order). sched1 didn't sink it because it was before a branch.

Hmm, but what if the load is placed just before the branch, and sched1 sinks it into the block? It scored 21, meaning the order changed (the load appears earlier). Not good.

What about making ot live across the branch via a use after the branch but with the load where it is? E.g.:
```
ot = load;
...
if (...) return;  // no
```
The load is already after the branches.

Alternative: give ot a longer life by using it after the loop, e.g., `AddPrim(otAddr, buf)` at the end uses otAddr; could we write `AddPrim(ot + cnt, buf)` and drop otAddr? Then ot is live from its load to the end (crossing the loop) → global! And otAddr would disappear... but the target has otAddr (s6) used in the loop, so removing otAddr changes codegen (the addu would be recomputed?). Let's think: `otAddr = ot + cnt;` then the loop uses otAddr and the final AddPrim uses otAddr. If we remove otAddr and use `ot + cnt` at each AddPrim (2 uses), the compiler would compute ot+cnt twice or CSE it into a register. Might still produce one addu.

Actually, a cleaner idea: keep otAddr but also use `ot` after the loop in a zero-cost way? Any use costs an instruction.

Hmm, what if we swap the roles: `otAddr` is the long-lived global (it is: used in the loop) and `ot` is only the load temp. In the target, ot is in t1 and otAddr in s6. If ot dies at the addu, it's block-local. Yes.

So the only way ot gets t1 is if t0 is occupied by something else at ot's allocation. What if we make the *sc division* use a temp that holds t0 longer? The div sequence uses t0/t1/at/a1... The div's divisor is cnt (t0 in target). In mine, cnt=t1.

Wait — in the target, the div uses t0 for cnt. So t0 is occupied by the *global* cnt across the block. In mine, cnt=t1 because ot took t0. Circular.

What if we make cnt's allocation happen before ot's by making cnt block-local? cnt is global due to the branches. Hmm.

What if we make the *branch structure* such that cnt doesn't cross a branch: e.g., compute `cnt = cnt << 2;` before the checks? The source: cnt = RotTransPers(...); if (cnt<=0) return; if (flag<0) return; cnt <<= 2. cnt crosses both branches.

What if we restructure to `if (cnt <= 0 || L.flag < 0) return;`? That's one branch (still crosses).

The target has two separate branches, so cnt must be global there too. And the target's cnt=t0 as a global. The global allocator assigned cnt t0 because t0 wasn't taken by a local in its range — because ot was pinned to t1!

Lever-free, ot (local, 2 refs) takes t0. For cnt to get t0, ot must not be allocated t0. 

What if ot is *not* a separate variable: inline the load into otAddr:
```
otAddr = *(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + cnt;
```
Then there's no ot variable; the load temp is part of the address/add. The target has `lw t1,0(at)` then `addu s6,t1,t0` — so the load result is in t1 and the add uses it. With the inline form, the load's temp might get t0 or t1 depending on allocation. The temp has 1 ref (used in the add) and a very short life → highest priority → it would take t0, and cnt (global) t1. Still the same problem!

Unless... the load temp's qty is combined with the addu's destination.

Hmm, what if we make the addu use ot's value as the *first* operand: `otAddr = ot + cnt` vs `cnt + ot`? Commutative; gcc may swap to put the temp second. In the target, `addu s6,t1,t0` = ot + cnt (t1=ot, t0=cnt). So ot is the first operand.

Let me try the inline variant and a couple of others:
- inline otAddr.
- `otAddr = cnt + ot;`
- declare ot as u32.
- compute `otAddr = ot; otAddr += cnt;`

Let me test these (with fp and t0c pinned, so a score of 0 would be PARTIAL:$16).
