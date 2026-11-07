---
ts: 2026-11-06T05:12:34Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_pn46wGoBKbyFVjRS07nq
---
w4 changed the code (extra `move v1,v0`, `sll/sra`, frame 40). Not good.

So u3 (the cast) is the only one that works. Let me reconsider whether the cast is acceptable.

Hmm, wait. Let me reconsider the problem: maybe there's a completely different C shape for block 3 that naturally produces the reload. What if we write the inner check as a *separate statement* using a variable assigned before the store:

```
s16 lim;
if ((s16)D_80078EA6 < 0x80) {
    lim = D_80078EA6;       // load 1
    D_80078EA4 += a1;
    if (lim >= 0x81) ...    // reuse, no reload
}
```
No.

What if we write the condition using the *loaded value from the first check* but with a cast that changes the mode... no.

Hmm, what about making the store's *value* depend on the first load so that cse must reload? No.

Let me reconsider the actual mechanism of the cast. Let me look at the .cse dump of u3 vs u2 to see what differs. That will tell me if it's the alias set.

Actually, let me try a different type cast that is less "identity": `*(s16 *)((u8 *)&D_80078EA6 + 0)` — more identity.

What about reading EA6 as part of a *struct*: `((struct { u16 a; } *)&D_80078EA6)->a`? Same address, same type → probably same alias set.

Hmm.

OK, alternative approach to force a reload without casts: **make the first comparison not use a load at all**. E.g., if the first comparison could use a value already in a register from earlier... no.

What if we reorder so the first load happens *after* the store? The target has it before.

Hmm.

Let me reconsider: maybe the target's reload can be produced by *splitting the basic block at a CODE_LABEL*, and a real C way to get a label between the store and the load is a `goto` that survives. What if the goto target is referenced by the enclosing if's else? Consider:

```
if ((s16)D_80078EA6 < 0x80) {
    D_80078EA4 += a1;
    goto check2;
} else {
    goto after;
}
check2:
if ((s16)D_80078EA6 >= 0x81) ...
after:
```
This adds jumps. No.

What about a label at the start of the inner if that is referenced by a *branch from the outer if*? Hmm.

Actually — here's a thought: the C construct `if (...) { ... } else { ... }` where the else is empty and the label... no.

Let me look at the problem from the target's perspective once more. The target's third block:
```
6110: lui v0; lh v0 (EA6)
611c: slti v0,v0,128
6120: beqz v0, 6160 (join)
6124: nop
6128: lui v0; lw v0 (EA4)   <- hmm, actually let me re-read
```
Wait, I should look at the actual target's third block. Earlier output at 6128+ was cut. Let me look at it. Actually the diff showed target[43:45] = lui v0; lh v0 for the first load, and target[55:59] = lui v0; lh v0; nop; slti v0,v0,129 for the reload. So yes, two loads.

Hmm OK. Let me consider: is the cast really forbidden? Let me re-read the exact brief line:

"identity-statement launders (`w = (w>>16<<16)|x`, identity address spellings) do NOT count as a crack"

The examples are *value* launders. "identity address spellings" = writing the same address in a different way (e.g., `&arr[0]` vs `arr`, or `(char*)&x`). The intent: don't claim a crack when your only change is a no-op spelling that happens to change codegen.

Our u3's change is `(s16)D_80078EA6` → `(s16)*(s16 *)&D_80078EA6`. That IS an identity address spelling. I think it would be judged a launder.

Hmm. But without it, we can't force the reload. Unless...

Wait, maybe I can force the reload by making the *store* a different alias class. What if the store is `D_80078EA4 += a1;` but I add a *real* second store that the target also has? No.

Hmm, let me reconsider the whole third block. The source:
```
if ((s16)D_80078EA6 < 0x80) {
    D_80078EA4 += a1;
    if ((s16)D_80078EA6 >= 0x81) {
        D_80078EA4 = 0x800000;
    }
}
```
The target reloads EA6 for the inner check. What if we restructure this to make the reload natural: e.g., swap the conditions?

```
if ((s16)D_80078EA6 < 0x80) {
    D_80078EA4 += a1;
    if ((s16)D_80078EA6 < 0x81) {
        goto skip;
    }
    D_80078EA4 = 0x800000;
skip:;
}
```
Different code shape.

What if the inner check is written on a *different* variable that requires a load: e.g., a local `s16 t = D_80078EA6;` declared AFTER the store:
```
D_80078EA4 += a1;
t = D_80078EA6;    // cse reuses the earlier load? The earlier load's value is in a pseudo; assigning to t copies it. No reload.
```
Hmm.

What if the first check's load is *destroyed* by the store? The store to EA4 doesn't touch EA6.

I think the type-pun is the only lever-free way, which means it's effectively a WALL for a strict reading... but wait, the task's whole point is to remove levers; the project must have a policy on alias-set casts. Let me search the cookbook for "alias" more broadly and for "cse" entries about reload after a store.

Let me grep the cookbook index for entries mentioning "reload" and "cse".
