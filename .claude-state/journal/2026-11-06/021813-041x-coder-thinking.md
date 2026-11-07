---
ts: 2026-11-06T09:18:13Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Tp0FxlcpRbU62p9z8JvI
---
Only my line. Let me think about real-C constructions that add a legitimate use of bVar1 after the test without changing output.

Idea: express the +0xa negation using bVar1 twice via a conditional that has a redundant-looking but semantically required form. E.g.:

```
if ((bVar1 & 0x10) != 0) {
    *(s16 *)(param_1 + 0xa) = -sVar5;
}
```

What if instead:
```
s16 v = sVar5;
if ((bVar1 & 0x10) != 0) v = -sVar5;
*(s16 *)(param_1 + 0xa) = v;
```
Then the andi is used once still.

What if:
```
if ((bVar1 & 0x10) != 0) {
    sVar5 = -sVar5;
}
*(s16 *)(param_1 + 0xa) = sVar5;
```
Same.

Hmm what if the test is `(bVar1 & 0x10) != 0` where bVar1 is *reloaded*? Like `if ((*(u8*)(iVar11+0x22) & 0x10) != 0)`. That reloads from memory (extra lbu) — target doesn't have it.

OK, different tactic: maybe we can satisfy "keepalive kind gone" while keeping bVar1 live via the *other* keepalives' real replacements. The three keepalives are separate lines; maybe a real C use of bVar1 can be found in the fc keepalive's replacement (line 64: `__asm__("" :: "r"(fc))`). What if we combine: keep fc and bVar1 alive with a real expression involving both, e.g. the call argument? `func_8013AA24(iVar11, param_1)` — target insns 102-104: `move a0,s8; jal; move a1,a2`. The call args are iVar11 and param_1.

Hmm what about the return value? The function is void.

Let me examine the *fc* keepalive (w3) and *iVar7/t* keepalive (w2) diffs to see the patterns; maybe there's a general trick: use a variable in a later expression where the target keeps it.

w2: `__asm__("" :: "r"(iVar7), "r"(t));` inside the else-if branch (fc > limit). iVar7 = fc + zr. The asm keeps iVar7 and t alive. Target uses: 91 slt v0,a0,a1; 93 addiu v0,v1,-1024; ... where a1 = fc? Let me see w2 diff.
