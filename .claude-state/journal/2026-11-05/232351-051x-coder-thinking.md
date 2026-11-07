---
ts: 2026-11-06T06:23:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Gxzcd41xfx4skIye4Qfd
---
The flow dump shows insn 164 has `(insn_list 151)` — a LOG_LINK to 151, and REG_DEAD r80. So combine folds.

To break this, insn 151 and 164 must be in different basic blocks. They're not (the notes don't split blocks).

So: I need a real block boundary between the call and the arg copy.

What creates a block boundary that survives jump_optimize? A conditional branch. In the loop body, there's the `if (i != 11)` before the call. Could we move the `if` *after* the call? No — the args.

But what if we compute the args differently: the if/else sets v0p..v3p. What if instead the call is made inside the arms? e.g.

```
if (i != 11) {
    otz = RotTransPers4((s32)pa, (s32)pa + 8, (s32)pb, (s32)pb + 8, ...);
} else {
    otz = RotTransPers4(arg0 + 0x84, ..., ...);
}
```
Then otz's set is in each arm, and the use (arg copy for func_801823D4) is after the join → different blocks! Combine can't fold across the join.

But: does that produce the same code? The target computes the args in the arms and the call at the join. Duplicating the call into both arms would double the call instructions. No good.

Hmm. Unless the compiler cross-jumps them back? Unlikely.

OK so what else creates a block boundary... A `?:` that isn't optimized. A loop.

Hmm, what if the `if (i != 11)` is *after* the RotTransPers4 call but only affects the AddPrim? No, args.

Let me reconsider: maybe the target's `move s1,v0` doesn't need a block boundary — maybe with a *different value flow* combine doesn't fold. Combine folds (set r80 v0) + (set a0 r80). What if instead the sequence is (set r80 v0) ... (set r80 (something)) ... (set a0 r80)? Two sets of r80: combine would still fold the first into its use if the use is the arg copy.

What if r80's set is a *hard register* copy? no.

What if the call result is assigned to otz via a *different* pseudo that dies: e.g. `otz = (s32)RotTransPers4(...)` where RotTransPers4 returns `s16`? A call returning HImode → the result in v0 is HI; assigning to s32 otz would emit sll/sra (sign extension). Unless the declared return type is `s32`.

Hmm, what if the call is declared to return `u8`? then andi.

OK — what if we pass the value through the *loop counter*... no.

Let me look at how the asm actually differs. The asm is an insn with a USE of r80 and a SET of r80. With the asm present, combine sees:
(set r80 v0), (asm: set r80 from use r80), (set a0 r80).
The asm prevents the fold of the first set (r80 is used by the asm).

A plain-C construct producing a USE of r80 with no cost... 

What about making r80 used by a **`REG_DEAD`-less use in a parallel**? Hmm.

What about a **call to a function with the arg being otz that gets inlined**? no inlining at -O2? gcc 2.7.2 has -finline but these are extern functions.

Hmm, what about **`otz` used as the argument to the `AddPrim` of the previous iteration**? no.

New idea: what if otz's first value is used in the **`func_8012E28C(otz, zpush)` call at the end of the loop**, i.e., reorder so that the depth-sorted value and the raw value are swapped? no.

Hmm, let me think about the possibility of making the *first* call result be used by func_801823D4 *and* by the `D_800A651C` index in a foldable way... 

Actually, WAIT. What about making the first call result live across a *call*? If otz's value is used after the func_801823D4 call, it must be in a callee-saved reg → `move s1,v0` materializes. What if the use after is `AddPrim`'s index? In the target, AddPrim's index is the *second* value (s1 after `move s1,v0` at 302c).

But what if we changed the source so that AddPrim uses the FIRST value? Then the codegen would be: otz1 = call; otz1 live across func_801823D4; ... but AddPrim needs the depth-sorted value.

Hmm, unless we assign the depth-sorted value to a *different* variable and AddPrim uses... no, target shows `move s1,v0` at 302c (the second set) and `sll a0,s1,2` for AddPrim. So AddPrim uses the second value.

OK. So the only way: otz1 has a use after the call. There is none in the target.

Hmm, but wait — the target's `move s1,v0` at 301c: what if this is NOT otz's set but a *different* pseudo? What if it's the first call's result being copied to a variable that is then used as the arg. That's what we said.

Hmm, so with the asm, r80 is set twice (call + asm). Combine can't fold.

What plain C produces an insn that sets r80 to itself? `otz = otz` folds at tree.

Hmm, what about `otz = (s32)(s16)(s32)otz`? 2 insns.

What about `otz = otz * 1`? folds.

What about `otz = otz + 0`? folds.

Tree-level folding is the enemy. Is there an expression gcc's fold() does NOT simplify? 
- `otz = otz & otz`? fold: x & x = x. 
- `otz = otz | otz`? x | x = x.
- `otz = otz ^ 0`? folds.
- `otz = otz / 1`? folds.
- `otz = -(-otz)`? folds.
- `otz = ~(~otz)`? folds.
- `otz = (otz << 0)`? folds.
- `otz = otz % 1`? → 0? 

Hmm.

What about a **cast through a union**? memory.

What about `otz = *&otz;`? For a local whose address isn't taken, gcc folds `*&x` to x at tree level. If the address IS taken elsewhere (e.g., if otz's address escapes), it becomes a memory access. 

Hmm — but what if we take the address of a *different* variable... no.

OK. What about making `otz` a **volatile**? no.

Let me reconsider the problem from the scheduler's perspective. Maybe there's another way to get `move s1,v0`: if otz's first set is in a *different* pseudo than the arg. E.g.:

```
s32 t = RotTransPers4(...);   /* t = v0 */
otz = t;                       /* otz = t (copy) */
otz = func_801823D4(otz, -0x1A);
```
RTL: (set t v0), (set otz t), (set a0 otz). Combine: fold (set otz t) into (set a0 otz)? It would produce a0=t; then fold (set t v0) into a0=v0. Unless t is used twice.

What if we use t twice: `otz = t;` and something else with t. Hmm.

What about: `otz = RotTransPers4(...); otz = func_801823D4(otz, -0x1A);` where the *second* call also gets t? no.

Let me look at this from a totally different angle: maybe I should check whether the target's 162nd instruction could be produced by a different structural choice entirely — e.g. if `otz` were assigned in the loop *condition*... 

Honestly, let me consider: does the target really come from the asm re-tie? Yes: orig.c (with asm) scores 0.

Let me try a few "long shot" candidates cheaply, scoring 6-8 at once:

L1: `do { otz = RotTransPers4(...); } while (0);` + `if (otz < 0) otz = -otz;`? no, changes.

L2: assign the call result to otz, then pass `otz` to a *dead* conditional: `if (otz == 0) { }` — test.

Hmm, these add insns.

Let me reconsider the "different basic block" idea once more: what if the RotTransPers4 call is placed inside the existing `if (i != 11)` ... no.

What about making the *loop* structure such that the call is in the loop body and the func_801823D4 call is in the *increment* part of the for? `for (; i < 12; i++, pa++, pb++) { ... }` — the increment is a separate block! But the call order would change.

Hmm! What if the func_801823D4/AddPrim/func_8012E28C tail were in the loop's *condition* or *increment* expression? That's a crazy but real C construct:

```
for (; i < 12; ) {
   ...
   otz = RotTransPers4(...);
   ... 
}
```
No.

What about moving the `otz = func_801823D4(otz, -0x1A);` into the loop's increment expression: `for (; i < 12; i++, pa++, pb++, otz = func_801823D4(otz, -0x1A))`? The increment is evaluated after the body, before the condition — the ordering would be wrong relative to AddPrim.

Hmm.

OK, let me try to think about what makes jump_optimize NOT merge the do-while(0) loop. In w2, the do-while(0) with the call inside: the loop has a back edge? The condition is 0, so the front end emits no branch at all — the loop structure exists only as notes? The dump showed LOOP_CONT and LOOP_END notes but presumably no actual branch. jump merges blocks then.

If instead we used `do { ... } while (i < 0);` the branch exists (slt/bnez), so the block boundary is real. Cost: 2 insns (slt + bnez) or 1 (bltz on i). Hmm, `while (i < 0)` with i in a register: `bltz i, loop` = 1 insn! And gcc might not prove i >= 0. So the cost could be just 1 branch insn. But then we're at 163 vs 162. Unless we remove 1 insn elsewhere... no.

Hmm, unless the branch fills a delay slot / nop. In target there might be a nop we could fill. Risky.

Let me reconsider the whole item: maybe the intended crack is different. Let me look at the item's `kinds` = launder,pin. The other similar items (func_8019059C, func_80191C50, func_801919A0 — 308/307/307 ins) are in the same family. Maybe the launder crack pattern in this family is known. Let me look at the *other* items' bodies first — maybe they have the same asm re-tie pattern and a known crack exists in moves.md. Let me check item 2 (func_8019059C) quickly: does it have the same `__asm__("" : "=r"(otz) : "0"(otz))`?

Actually, maybe I should look for the *same function family* in other shards: the jr_8019059C TU. Let me grep moves.md for these function names: func_8019059C, func_80191C50, func_80181E08, func_80183534, func_801919A0.

None appear in moves.md (I read it all; they're not there).

Let me check what the launders look like in item 2 — maybe there's a known crack pattern for "call result copied to arg".

Let me look at the def of func_8019059C (2787) and func_80191C50 (2843).
