---
ts: 2026-11-06T15:26:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_q5uiNEitJ8BIbOxVp2Sj
---
Key: "launder on the trip count n -> n = (s16)n at both sites (a real 2nd set, value-preserving for n in {16,20})". And "the 12 launders on v -> six 'v = (s16)v;' real 2nd sets (v is a sign-extended s16, so the cast is a no-op)".

So a value-preserving narrow cast `(s16)v` works as a real 2nd set when v's value is known to fit in s16 (or is already sign-extended). 

For `flags`: value is a call return (s32), full 32-bit. `(s16)flags` would truncate. Not value-preserving.

Hmm. But maybe we can find a value-preserving 2nd set differently. `flags = (s32)(u16)flags`? truncates.

What about `ret`? ret is 0 or 1 — definitely fits in s16! So `fire` could be `s16 fire = ret;`? But that changes the type and codegen: `if (fire != 0)` with s16 would be `sll/sra` or `lh`. Hmm, actually if `fire` is s16 and assigned from s32 ret, it'd be truncated to HImode. The target's move is `move v0,s2` (word move). A s16 variable stored in a register still uses SImode ops in gcc if not in memory... Actually HImode pseudos on mips get loaded with lh/sll+sra when converting. `s16 fire = ret;` → the assignment would need truncation: `sll v0,s2,16; sra v0,v0,16` — 2 insns. Target has just `move v0,s2`. Hmm, unless the compiler knows ret is 0/1.

But wait — the "real 2nd set" trick isn't about changing `fire`; it's about adding a second set to the *laundered variable* (here `ret`) so the equivalence breaks. In func_801813B0: the launder was on v; replaced with `v = (s16)v;` — a real 2nd set of v that is value-preserving, no code emitted. Here the launder is on `ret` with `fire = ret` as the copy. So: replace `__asm__(ret)` with `ret = (s16)ret;`? That's not value-preserving for a general s32 ret. But ret is only ever set to 0 or 1 in this function (ret = 0, ret = 1). So `ret = (s16)ret;` is value-preserving! And it's a real 2nd set of ret, which should kill the copy-propagation and keep the `move`.

But would `(s16)ret` emit sll/sra? gcc knows ret ∈ {0,1}? It might not. `ret = (s16)ret` on an s32 variable: the cast to s16 then implicit conversion back to s32 → sign extension. If gcc can't prove it's within range, it emits sll/sra (2 insns). Unless... in func_801813B0, "v is a sign-extended s16, so the cast is a no-op" — gcc knew v's mode was HImode already.

Alternatively `ret = ret & 0xFFFF`? not value-preserving in general but here ret∈{0,1}. But the compiler doesn't know that; it would emit `andi`. Hmm, but a dead-ish second set that's actually value-preserving: `ret = ret | 0;` folds.

Wait, the point of a "real 2nd set" is that it emits nothing OR emits the right thing. In func_8017D73C: "the launder on the trip count n -> n = (s16)n at both sites (a real 2nd set, value-preserving for n in {16,20})". So the cast emits sll/sra? Let's check: if n is s32 and we do `n = (s16)n`, gcc must sign-extend. On MIPS, `sll/sra` pair. But the target apparently doesn't have those — maybe the original expression kept n in HImode naturally so the cast is a no-op.

Hmm. Let me think of another route for the fire copy: restructure so that `ret` is genuinely used after `fire`, forcing a copy:

```
s32 fire = ret;
if (fire != 0) {
    func_80146A6C(...);
}
```
If I add a use of `ret` after the if, the compiler can't merge. But adding a use changes codegen (unless it's dead). E.g.:

```
{
    s32 fire = ret;
    if (fire != 0) { ... }
    ret = ret;  // ?
}
```
Hmm.

What if the block is: `if (ret != 0) { ... }` written as two separate tests:
```
s32 fire = ret;
if (fire != 0) { func_80146A6C(...); }
```
The copy is merged because ret is dead after. What if `ret` is used *before* the copy too? It is: ret is assigned in multiple branches. Hmm.

Key: copy propagation merges a copy when the destination is only used... Actually `flags = raw` + uses of flags → cse replaces uses with raw if raw is not redefined. For fire: `fire = ret; if (fire)`: cse replaces fire with ret. To block: make ret "not available" at that point, e.g. a 2nd set of ret between the copy and the use? That doesn't make sense (ret would change).

Alternative: reverse the roles. The target has `move v0,s2` = copy ret into a NEW pseudo. The launder ties ret's output, forcing ret to be *defined* at that point (an output constraint), which makes ret not a simple copy source... Actually the asm `"=r"(ret) : "0"(ret)` is an output+input tie: it forces ret into a register, defines it. That's a real second SET of ret (opaque). So the fix in other cases: replace with a real 2nd set of ret, value-preserving.

Since ret ∈ {0,1}, `ret = (s16)ret;` might work if gcc treats it as a no-op. Let's just try a bunch:
- `ret = ret & 1;` (value-preserving since ret∈{0,1}) — emits andi probably.
- `ret = (s16)ret;`
- `ret = (u16)ret;`
- `ret = ret ? 1 : 0;` — folds? maybe emits sltu... no, for {0,1} unknown.

Hmm, what about making `fire` the one with a real 2nd set? `s32 fire = ret; if (fire != 0)` — a 2nd set of fire, e.g. `fire = fire;` no.

Let me just experiment. Also for `flags`: since the launder's effect is that flags is "defined" at that point (a real second set), maybe replace with a real 2nd set of flags that is value-preserving... `flags = flags;` no. But note flags' uses are `& 0x8000` and `& 0x6000`. What if we mask flags at the set: `flags = raw & 0xFFFF;`? Not value-preserving (uses only mask 0xE000 bits, so actually for the later uses only bits 0x8000/0x6000 matter!). The uses of flags: `m = flags & 0x8000;` and `(flags & 0x6000) != 0x2000`. Both only look at bits 0xE000. So `flags = raw & 0xE000` would be *observably equivalent*... but it changes codegen: an extra andi, and the target doesn't have it. Hmm, but cse might fold the masks: `(raw & 0xE000) & 0x8000` → `raw & 0x8000` — cse/combine can fold consecutive ands! That would be free. And it creates a real 2nd set (the andi might fold away, but the RTL set is there).

Hmm, but would `flags = raw & 0xE000` keep a separate pseudo? The value differs from raw, so cse can't substitute raw for flags at the `& 0x8000` use... but combine can fold `(raw & 0xE000) & 0x8000` into `raw & 0x8000`, then cse substitutes raw → back to one pseudo. The order: cse runs before combine. cse1 would see `flags = raw & 0xE000` then uses `flags & 0x8000` — cse records flags' value as an expression; it may not substitute.

Alternatively `flags = raw & 0xFFFFFFFF` folds to raw.

OK let me think about what actually keeps a copy alive in gcc: making the value live in two places because it's used in a way requiring the register... The launder is a hack; the real-C equivalent used by the project in these cases is a "real 2nd set" of the variable. For flags, the 2nd set must be *after* the copy and *before* the uses, with a value-preserving op.

Idea: `flags = raw; ... if (m != 0 || (flags & 0x6000) != 0x2000)` — what if instead we recompute flags' value from raw at the second site? No.

Let me look at what the launder actually does in RTL: `(insn (set (reg flags) (asm_operands ...)))` with the input tied to flags. This is a USE of the incoming flags (value) and a DEF of flags. So after the asm, flags is a new value (opaque), and cse cannot know flags == raw. So the *value* is preserved at runtime but opaque to the compiler.

A real-C "2nd set" that is opaque and value-preserving: `flags = flags;` gets deleted. But what about a self-assignment that gcc can't delete? E.g. `flags = (flags ^ 0)`? folds.

Hmm what about the §373 dead-reset trick: set a *different* variable to 0 to empty the cse equivalence class. E.g. `raw = 0;` after the copy would kill cse's equivalence between flags and raw! Because raw is redefined. And raw is used in the first if... but order: `raw = call(); flags = raw; raw = 0;` would break the first test (uses raw). Unless we restructure the first test to use `flags`... but target's first test uses $v0.

Wait — maybe reorder: the first test's andi reads the call's return. What if we write:

```
raw = call();
if ((raw & 0x6000) != 0x2000) {...}
flags = raw;   // after the if
```
Then raw is redefined? No. But then flags is a copy of raw at the join, and raw is dead → cse merges → one pseudo, but the merged pseudo's live range is from call to second if, crossing calls → global $s1, and the first andi would be on $s1. Same as now.

Hmm.

What about using the dead-reset on raw after the copy but keeping the first test on the call value via a different local:

```
s32 raw = call();
s32 raw2 = raw;      // local copy for the test
flags = raw;         // global copy
raw = 0;             // dead-reset: kills cse's raw/flags equivalence
if ((raw2 & 0x6000) != 0x2000) ...
```
Then raw2 is a local copy used once → $v0; flags is global → $s1; raw dead. Hmm, this adds a copy but it may coalesce. The dead-reset `raw = 0;` kills the equivalence between flags and raw... but cse has flags ≡ raw (copy), then raw is set to 0 → the equivalence is invalidated. Then flags' uses can't be replaced by raw. 

But `raw = 0` is a dead store (raw never used after) → flow/cse deletes it! Unless... hmm, cse's invalidate happens when it processes the set; if a later pass deletes the dead set, the equivalence was already broken? cse1 runs, then other passes. The dead store deletion (flow) happens after cse1? Order: cse1, ... flow, ... combine, ... cse2. cse1 would process `raw = 0` and invalidate. Then flow deletes the dead store. cse2 would then re-establish? cse2 doesn't do copy propagation the same way.

Actually C0414 "dead-reset cse-breaker" is exactly this and cracked 3 launders. So the dead-reset is a legitimate move here.

So: `raw = 0;` after `flags = raw;`? But raw is used in the first test AFTER. So put the dead-reset after the first test:

```
raw = call();
flags = raw;
if ((raw & 0x6000) != 0x2000) { ... }
raw = 0;   // dead reset (raw never used again)
m = flags & 0x8000;
if (m != 0 || (flags & 0x6000) != 0x2000) ...
```
Would this work? cse's equivalence flags ≡ raw is established at the copy. The first if is in the same block? The `if` splits blocks. Hmm — cse1 processes the first block: raw = call; flags = raw; andi raw... then at the end of the block the equivalence may be saved in the table for successor blocks (cse1 propagates through EBBs). Then after the join block, `raw = 0` invalidates raw ≡ flags, so flags' uses stay as flags. 

The dead store `raw = 0` — will it survive to codegen? flow's dead code elimination removes stores to dead pseudos. But if it's removed, the cse damage is already done (cse1 already ran). Since cse1 runs before flow? Let me check gcc 2.7.2 pass order in toplev.c: ... cse (cse1) ... then later flow, combine, ... So yes cse1 before flow. The dead store gets removed by flow later. But cse2 might re-merge? cse2 is after flow and combine; cse2 does not do copy propagation across blocks as aggressively, and there's no copy insn left. Should be fine.

But wait: is `raw = 0` even needed after the first if? The equivalence between raw and flags at the join: if the first `if` body has calls, cse may invalidate at calls anyway... apparently not, since without the launder it merges.

Let me try this variant. Also for `fire`: a dead-reset of `ret`? ret is used by `fire = ret`. `fire = ret; ret = 0; if (fire != 0)` — ret dead after, so the set is dead; cse1 would invalidate ret's equivalence... but the copy `fire = ret` already happened. The merge of fire into ret: cse replaces `fire` uses with ret. If ret is then set to 0, cse's equivalence is broken → fire's use can't be ret. And the dead store is removed later. That's exactly the "dead-reset" trick.

So: replace asm with `ret = 0;`? But ret holds the value used by... no, `fire = ret` copies it. Then ret = 0 kills the class. Hmm but flow might delete `ret = 0` and then... cse1 already processed. But actually the *merge* may not be a cse transformation at all — it might be copy propagation in `flow`/`combine`/reg-alloc coalescing. Let me just test empirically.

Let me create more variants:
- a5: `raw = 0;` after the first if (before `m = flags & 0x8000;`), and `ret = 0;` after `s32 fire = ret;`.
- a6: only flags fix.
- a7: only ret fix.

Note the source already has `s32 fire = ret;` then asm then if. I'll place `ret = 0;` between fire=ret and the if.

Careful: `ret` is used after? No. `fire` used in if. OK.

Let me add these variants to gen.py.
