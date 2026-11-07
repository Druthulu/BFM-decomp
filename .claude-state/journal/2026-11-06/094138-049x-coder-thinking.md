---
ts: 2026-11-06T16:41:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rWUxgJqTLxNoTGRWAjNa
---
In v3 at jump1, the then arm is [slti 412; branch 413 (eq v0 0 → label 450); move a0; call; jump 421]. The else arm is [slti 432; branch 433...]. Both branches are `(eq v0 0) (label 450) (pc)` — identical form here! (The EQ form is because the then arm is `if (d < 0x51) { call; return; }` → branch to the call when true.)

At jump2, the then arm's [slti; branch; move; call; jump] got cross-jumped with the else's tail: the shared part is [move; call; jump] merged into the else arm, and the branch too. Since the branches are identical, they merged.

So in v3 both branches are EQ form, and they matched.

Now in v1 (goto docall), the then branch was `(ne v0 0) (pc) (label 452)` and else `(ne v0 0) (pc) (label 452)` — identical.

So we need the two branches to differ in form. The two forms available:
- inverted form: `(ne v0 0) (pc) (label)` → emits beqz
- normal form: `(eq v0 0) (label) (pc)` → emits beq → also beqz!

Both emit `beqz v0, label` but have different RTL. So if one arm uses the normal form and the other the inverted form, cross-jump won't match (different structure), while the emitted instructions are identical! 

How to get one arm's branch in the normal form and the other in the inverted form, both branching to skip when the condition fails?

Normal form `(eq v0 0) (label skip) (pc)` = "if v0 == 0 goto skip". v0 = (d < 0x51). So this is `if (d >= 0x51) goto skip;`... hmm both are that.

The difference between normal and inverted is which arm of the if_then_else is pc: normal means the branch target is taken when the condition is TRUE (if_then_else (cond) (label) (pc) = if cond goto label else fall through). Inverted means the condition is negated: (if_then_else (ne v0 0) (pc) (label)) = if v0 != 0 fall through else goto label = if v0 == 0 goto label.

So:
- normal with cond EQ: `if (v0 == 0) goto skip` → `if (!(d < 0x51)) goto skip` = `if (d >= 0x51) goto skip`. Emits beq v0,0,skip = beqz.
- inverted with cond NE: `if (v0 != 0) fall else goto skip` → same C, emits beq v0,0,skip = beqz.

So the same C can produce either form depending on how the tree/expand chooses! Which form is chosen depends on the if structure: e.g. `if (cond) goto X;` vs `if (!cond) goto Y;` vs `if (cond) {} else goto X;`.

For v3, the then arm's C was `if (d < 0x51) { call; return; }` → branch normal form EQ to the call when true.

In the target's then arm: `beqz v0,skip` then `j call` — this is the inverted form NE (branch to skip when false). 

So if we can get the then arm's branch in the normal EQ form while still emitting `beqz v0,skip` and a `j call`, and the else arm in the inverted form, they'd differ in RTL and not merge! But the normal EQ form emits `beq v0,0,skip` when the label is the "then" target: that's `if (v0 == 0) goto skip` i.e. `if (d >= 0x51) goto skip;` — hmm, that's the same C as the inverted form. GCC picks the form based on the surrounding structure.

Actually GCC's expand for `if (cond) goto label;` emits a conditional jump with the condition as given: `(if_then_else (cond) (label) (pc))` — normal form with cond = the truth of the comparison. For `if (d >= 0x51) goto skip`, the comparison is `d >= 0x51` → `ge (d, 0x51)`. Expand might emit `(if_then_else (lt (d) (0x51)) (pc) (label))` — inverted form of the *lt* comparison. That's what we see: `(ne v0 0) (pc) (label)` after the slti split.

Alternatively, GCC may emit the normal form `(eq v0 0) (label) (pc)` when the comparison gets reversed. Which happens for `if (d < 0x51) { ... }` where the then-block is the taken path.

Hmm, in v3 the then arm `if (d < 0x51) { call; return; }` gives `(eq v0 0) (label call) (pc)` — normal form, cond EQ, meaning "if v0==0 goto call", v0 = (d<0x51).

We want then arm: `(eq v0 0) (label skip) (pc)`? That would be "if d<0x51 is false goto skip" = if d>=0x51 goto skip. Is there C that makes GCC emit this? `if (!(d < 0x51)) goto skip;` maybe. Or `if (d < 0x51) {} else goto skip;`.

Let me test: then arm written as
```
if (d < 0x51) {
    /* nothing */
} else {
    goto skip;
}
```
Hmm, GCC may simplify.

Actually more directly: `if (!(d < 0x51)) goto skip;` might produce the normal EQ form. Or `if (d < 0x51) goto docall;` — no.

But careful: whatever we do, the target's emitted then arm is `slti v0,v1,81; beqz v0,skip; j call`. Both forms emit that. And the else arm must remain in the inverted form (it already is: `(ne v0 0) (pc) (label skip)`).

Wait, but if both arms use the same C spelling, both get the same form. We need to spell them differently. That's legitimate real C (different but equivalent spellings), not an identity launder? Hmm, `if (d >= 0x51) goto skip;` vs `if (!(d < 0x51)) goto skip;` — these are semantically identical spellings. Is that an "identity-statement launder"? The constraint says identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack. A logically-equivalent condition spelling... hmm, that's arguably a real C difference (the catalog includes `&&`/`||` folds and comparison forms). I'd say it's a legitimate spelling change if it changes the RTL. But it's borderline "identity". Let's see if it even works.

Actually, an even more natural difference: the target's then arm ends with `j call` because the call block is after the else arm. What if the *else* arm's branch is the normal form? The else arm's C is `if (d >= 0x201) goto skip;`. If we write the else as `if (!(d < 0x201)) goto skip;`... but the target's else branch is `(ne v0 0) (pc) (label)` (inverted). Changing it would still emit beqz.

Let me just experiment: try writing the then arm's condition as `if (d < 0x51) {} else goto skip;` and see if the merge is prevented.

Hmm, but actually there might be a subtlety: `if (d < 0x51) { } else { goto skip; }` — GCC's jump pass would convert the empty then to a fallthrough and invert. Let's test several spellings quickly in one batch with sc.sh:
- w1: then `if (d < 0x51) { } else { goto skip; }`
- w2: then `if (!(d >= 0x51)) goto skip;`
- w3: then `if (0x51 > d) { } else goto skip;`

Let me generate them.
