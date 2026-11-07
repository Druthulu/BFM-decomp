---
ts: 2026-11-06T15:25:02Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_V4c3k5yV558hlIei5G2R
---
Target: 
```
jal call
sw s1,68(sp)   (delay slot)
move s1,v0      <- flags = raw (global $s1)
andi v0,v0,0x6000  <- raw used directly
li v1,8192
beq v0,v1
andi v0,s1,0x8000   <- delay slot
```

So there are two pseudos: raw in $v0 (dies), flags in $s1. Good.

Now, what real C makes gcc keep both? The launder forces the copy to a register. Without it, cse's copy propagation removes `flags` (substitutes raw), then allocates one pseudo.

Key insight: the copy `flags = raw` is deleted by copy propagation (flow's? cse's?), and uses of flags become raw. To keep it, we need the copy not to be "provably" a copy... 

Idea: make `flags` be assigned *conditionally* or via a different expression that has the same value but cse can't see as a copy. E.g.:

```
raw = call();
flags = raw & 0xFFFF8000 | (raw & 0x7FFF);
```
that's identity-ish and folds.

Better idea: split the first test differently. What if we compute the flag bits into a *separate variable* and keep flags as the full value?

Alternatively — what about making flags a value derived by an actual second computation that is not a copy but is naturally CSE'd away only partly. Hmm.

Think about the "real 2nd set" trick: `flags = raw;` then later `flags = flags | 0;`? no.

What about the C0414 dead-reset: insert `raw = 0;` after the copy, *before* the first test? But raw is needed for the first test. Unless we reorder: use flags for the first test and raw... no, target first test uses $v0 which is the call return. The andi happens in the delay slot of the *previous* instruction; raw's pseudo is the call result.

Wait — actually the target's raw pseudo may be simply the call result as used by the first `if`, and flags is the copy. In C: `raw = call(); flags = raw; if ((raw & 0x6000) ...)`. If copy propagation merges, we get one pseudo. To prevent merging while keeping semantics, we can make `flags` not a copy of `raw` but an independently-computed equivalent... impossible in general.

Alternative: make raw not a variable at all but the call expression used directly:
```
flags = ((s32 (*)(s32))func_8012CBA4)(a0);
if ((flags & 0x6000) != 0x2000) ...
```
Then flags is used in the first test and later — one pseudo. Target has andi on $v0 (call return) for the first test. Hmm, but maybe the target's $v0 for the first test is a *local* pseudo that's the call result, and $s1 is a global pseudo that's also the call result (same value, copied). This is exactly two pseudos.

What if I use the *call expression twice*? No.

What about: `raw = call(); flags = raw;` and then force `raw` to die early by using it in a way that... Actually the real issue is copy propagation making them one. Copy propagation happens in cse/flow only if the copy's source is not modified between. Here they'd merge into one pseudo with a single live range. But the target's two pseudos have overlapping live ranges! raw lives from call to andi; flags from copy (right after) to later. They overlap → they can't be the same pseudo; and they're two pseudos by construction. gcc's copy propagation would replace flags uses with raw, making flags dead, leaving one pseudo — that's what happens without the asm.

So: how to make flags not appear as a copy of raw to cse but still be the same value? 

Trick used elsewhere: `flags = raw;` then `raw = something else` (a real 2nd set of raw) *before* the first test uses... no, the first test uses raw's value.

Wait — re-read the source: the first if tests `raw`, and raw is not used after. What if instead we test `flags` in the first if and use raw...? Then it's the same.

Alternative approach: restructure the code so that the *first* test uses the call result in an expression that doesn't create a variable:

```
flags = ((s32 (*)(s32))func_8012CBA4)(a0);
if ((flags & 0x6000) != 0x2000) { ... }
```
Then flags lives from call to second if → global $s1. The first andi would read $s1 (since flags is global). Target reads $v0. So no.

Hmm, but wait: maybe the target's structure is: the call result is used for the first test, and a *second* copy is created for the later use. The copy is only needed because the value must survive the calls. What if we write:

```
raw = call();
if ((raw & 0x6000) != 0x2000) {
    ...calls...
    flags = raw;    // <-- copy made AFTER the calls, inside the if?
}
```
No, flags is used after the if in both paths.

What if flags is assigned in both arms of the first if? e.g.
```
raw = call();
if ((raw & 0x6000) != 0x2000) {
   flags = raw;
   ...calls...
} else {
   flags = raw;
}
m = flags & 0x8000; ...
```
Then flags has two sets (one per arm) — real 2nd set (well, two sets). Copy propagation might still merge. But the target's `move s1,v0` is right after the call, before the first test. Hmm, and target shows the move at 1f04 right after the call — so the copy is at the top, unconditional.

OK so the copy must be unconditional right after the call. The only way to keep gcc from propagating: an opaque operation. The launder is exactly that. Real C alternatives that are not "levers":
- volatile? That's a barrier kind.
- A function call? No.

Hmm, but the moves list has examples where a launder was replaced by a "real 2nd set" of the same variable. Here flags is set once. What if we make flags set twice with the same value such that cse can't merge: `flags = raw; flags = flags;` — second is identity, deleted.

`flags = raw; if (0) flags = 0;` — flow deletes.

What about `flags = raw; flags = raw + 0;`? constant fold to raw, then copy prop.

What about making `flags` a *different mode*: `u32 flags; ... flags = raw;` same mode. `s16 flags = raw` — truncation, changes value.

Hmm. What about splitting the first test to use a different variable that is genuinely separate:

```
raw = call();
flags = raw;
if (((raw & 0x6000) != 0x2000)) ...
```

The merge: cse's reg_eqv maps flags→raw. But note: the uses of flags are AFTER the if. If cse only works within EBBs, the merge must be at the RTL copy-propagation level in flow (or the `reg_eqv` in cse1 across EBB?). Actually there's a known pass: `combine`/`cse` also do copy propagation globally? In gcc 2.7.2, `flow` does dead code elimination, `combine` does copy prop within extended basic blocks, and `cse` too. But the launder is needed here per the comment, so plain C does merge.

Let me just try many real-C variants empirically. Time budget: 20-30 min per item, 5 items. That's ~2.5 hours. Let me be efficient.

Let me check how the current score-0 body with asm compares: score 0 presumably. Let's verify orig.c scores 0 (as a sanity check).
