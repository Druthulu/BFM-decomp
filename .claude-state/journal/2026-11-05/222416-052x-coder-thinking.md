---
ts: 2026-11-06T05:24:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_14FZJlN1ofpavFXYMUKM
---
Interesting. The target uses a0 for iVar2 (the loaded s16) in two places, with `move v0,a0` in the beqz delay slot, and `bgez a0`. Mine uses v0.

So the target: `lh a0,16(v1)` (iVar2 in a0), `beqz a0`, delay slot `move v0,a0`, `bgez a0`. So iVar2 is in a0 (arg register) and a copy in v0 is made for... hmm.

The pin is iVar1 $3 (v1). The target has iVar2 in a0. Mine puts iVar2 in v0.

Let's understand: `tmp = iVar2;` — in the target, tmp is v0 (the copy `move v0,a0`). And iVar2 is a0.

So in the target, iVar2 lives in a0 and tmp in v0 (the copy). The launder forces tmp to be a separate value.

Without the launder, cse merges tmp with iVar2 → one pseudo in v0.

To keep them separate: need a real 2nd set of tmp. `tmp = iVar2` then the launder re-sets tmp. A lever-free 2nd set... e.g. `tmp = (s16)iVar2;`? Or do-while? Hmm.

But also the register: target iVar2 in a0. Why a0? Because a0 is free after the two calls (a0 was the argument). local-alloc gives v0 to tmp and a0 to iVar2? Hmm, local-alloc uses caller-saved regs: $2,$3,$4..$7? Actually for local-alloc, the allocatable regs in a block are $2,$3 (v0,v1) and $4..$7? No — local-alloc only allocates *caller-saved* regs ($2,$3,$4,$5,...) within a basic block; but a0 is $4. Since v1 holds the pinned iVar1, v0 and a0 are available.

In mine: iVar2/tmp merged into v0; a0 free.

So if we split iVar2 and tmp, tmp could go to v0 and iVar2 to a0 — matching! The target's `move v0,a0` is `tmp = iVar2`.

So the crack is the same class as item 1: keep the copy `tmp = iVar2` alive. The launder did it. Lever-free: a real 2nd set of tmp, or the HImode/do-while trick.

But careful: here `tmp = iVar2;` is a copy and then tmp is modified (tmp += 0x80). So cse merges iVar2 and tmp only if the copy is a no-op; but tmp is modified later in both arms, so tmp and iVar2 have different values after. Hmm, then why does cse merge them?

Let me think: `tmp = iVar2; if (iVar2 < 0) { tmp += 0x80; ...} else { tmp -= 0x80; ...}`. After the copy, tmp is modified in both arms. cse sees `tmp = iVar2` — it can propagate iVar2 into the uses of tmp before tmp's redefinition. The use of tmp inside each arm is `tmp += 0x80` which is a read-modify-write; cse replaces the read with iVar2 → `iVar2 + 0x80` into tmp → then tmp = iVar2 copy is dead (if no other use) → deleted. Then the code uses iVar2 in place of tmp.

So the target keeps `move v0,a0` = tmp = iVar2, and the arms compute from tmp (v0) not iVar2 (a0).

To keep the copy: make the value "not equivalent" — the launder did that. Lever-free: make tmp a different mode? `tmp` is s32, iVar2 is s32. If tmp were s16, then `tmp += 0x80` would be HImode arithmetic → extra sll/sra. Hmm.

What about `tmp = (s16)iVar2;` — HImode copy: `tmp = (s16)iVar2` where tmp is s32: sign-extend; combine folds to copy, cse might not equate (cross-mode via subreg). The moves.md trick: `tmp=(s16)t; u=tmp;` keeps a copy. Here it's `tmp = (s16)iVar2;` then tmp is used. Let's try.

Also the dead-reset trick, do-while, etc.

Let me try a batch:
a1: `tmp = (s16)iVar2;` (both sites)
a2: `tmp = (u16)iVar2;`
a3: do-while around `tmp = iVar2;`
a4: `tmp = iVar2; do { } while (0);`
a5: dead reset? `tmp = iVar2; tmp = tmp | 0;` folds.

Also maybe s16 tmp declaration.

Let me generate with sed. The two launder lines are already removed in n1. The copies are `tmp = iVar2;` at two places (identical lines). Let me check occurrences.

n1 has:
```
        tmp = iVar2;
        if (iVar2 < 0) {
```
twice. sed replace_all.
