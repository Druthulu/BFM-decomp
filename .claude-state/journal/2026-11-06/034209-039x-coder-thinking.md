---
ts: 2026-11-06T10:42:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_fm5ljAlkAhWrAUAIFtAw
---
7. Let me see the diff quickly.

Hmm, I'm burning time. Let me reconsider.

Maybe instead of do-while tricks, find the natural C shape that produces the target. Recall the target was produced WITH the barrier. The barrier split the block. The natural lever-free shape might be a different statement order that sched1 naturally produces the target schedule.

Let me think about what the target schedule looks like relative to source:
Source (C): 
```
unk2 = 1;
unkC0 = 1;
unkBC = &D_801907D4;
unk5C = 0x8000;
t = unkC4;
unk58 = &D_801907C4;
unkC4 = t | 2;
unkC1 = 0;
unkB4 = 0;
... 
```
Target schedule: same order, except the t load is right after unk5C (same as source), and the address lui/addiu for unk58 after the load. So the target is just the source order, with sched1 not reordering. Mine (v_dw): source order except sw 88 sunk.

So sched1 wants to sink the store. Why? Because the store's priority is lower. In sched1, priority is computed from dependence height; a store with no dependents has low priority. The ori/sw chain has the load as a predecessor... hmm.

What if we make the unk58 store depend on the load in a benign way? E.g., store a value that includes t in a way that doesn't change semantics? Can't.

What if the unk58 store's *address* depends on t? No.

Alternative: what if we swap the source order: unk58 store BEFORE t = unkC4, but the target has the load first. Then sched1 might hoist the load above the store (it's independent), giving the target order! Let's test: 
```
unk5C = 0x8000;
unk58 = &D_801907C4;
t = unkC4;
unkC4 = t | 2;
```
If sched1 hoists the load above the store (no dependence), we'd get load, then lui/addiu/sw, then ori/sw = target! And no do-while needed? But earlier (v_param, no do-while) the load got hoisted way up to position 19, above the unk2/unkC0/unkBC stores. Hmm, but with the store order changed, maybe the load lands differently.

Hmm, sched1 hoists the load as early as it can. In v_param it went to 19 (right after the calls, before the li/sh/sb/lui-addiu stores). So it'd still go there.

Unless the load is blocked by a store that may alias. What if we place a *store through an unknown pointer* before the load? No.

OK here's another thought: what if the load uses a pointer variable that could alias the stores? gcc 2.7.2 alias sets: MEMs through different pointer *types* get different alias sets. All stores are through `Unkstruct_800B5CB8 *`. If the load is through `s32 *` (a different type), the alias sets differ → conflict → no hoisting above the stores! But my v_cast did exactly that: `*(s32 *)((s32)a0 + 0xC4)` — but `(s32)a0` cast to integer then to s32* — the address is an integer constant expression; gcc might give it alias set 0 or a generic one.

Hmm, v_cast scored the same as v_param (11), load still at 19. So the alias sets didn't stop it. Because the address is `(plus reg const)` and the dependence check proves the addresses distinct by comparing the constant offsets — the alias set check in true_dependence: gcc 2.7.2's true_dependence does:
```
if (alias_sets_conflict_p(...)) { if (fixed_address_object_p) ...; if (GET_CODE(x)=='const') ...; else if (rtx_equal...) ...; else if (GET_CODE(x)==GET_CODE(y) && GET_CODE(x)==PLUS) { compare } }
```
Actually it compares the two addresses structurally: both are `(plus (reg) (const))` with the same reg → not equal → no dependence. So offset-based disambiguation wins.

So to block hoisting, the base regs must differ: e.g., load through a *copy* of the pointer in another pseudo? If the load's base is a different pseudo (e.g., `p = a0; t = p->unkC4;`), gcc's alias analysis with different regs: `(plus (reg p) 196)` vs `(plus (reg s0) 92)` — if p and s0 are different pseudos, gcc can't prove they're distinct → assumes dependence → the load can't move above the stores! But after register allocation p and s0 would be the same reg (or a copy). Hmm, but if p is a copy of a0, cse would merge them.

Unless p is an opaque copy (launder) — not allowed.

Hmm.

Alternative: use `s0->unkC4` where s0 is... 

Wait wait. Let's revisit: in v_param (no do-while), the load was at 19 — but what exactly is at 18-19? Let me dump the full v_param listing to see which stores precede. Maybe the load was hoisted above the *call*, i.e., into the block before. Let me check.
