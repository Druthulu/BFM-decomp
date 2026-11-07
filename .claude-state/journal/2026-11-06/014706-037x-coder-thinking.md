---
ts: 2026-11-06T08:47:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_kOb8v5P1qIEQ8RcjW9Dj
---
Still merged. The merge is happening in cse/combine regardless of block structure? Wait, in c7 the negation is in the then block and the copy is in both branches — still merged within the then block.

Key question: how did the original avoid the merge? Maybe the original's `val = nudge` in the else was not adjacent to the negation because of an intervening *use of val* that the compiler kept.

Hmm, what if the original else was:
```c
} else {
    val = nudge;
    CAST_WIDTH(s32, param_1, 0x10) = val;   // a store that later got removed? no, target has no store there
```

What if the original used the same variable for nudge and val? E.g., the original might be:
```c
nudge = ...
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```

Alternatively, maybe the original's else is:
```c
} else {
    val = nudge;
    val = -nudge;   // !!! negates nudge, not val
}
```
Then combine: val=nudge; val=-nudge → val=-nudge, and the copy val=nudge is dead → removed. That gives mine.

What if the original is:
```c
} else {
    val = -nudge;
    val = nudge;   // no
```

Hmm. What if the copy is from a *different* variable that aliases: e.g. `val = nudge;` where nudge is `s32` and val is `s32`, but the negation is `val = -val;` — merge. 

What if val is **u32** and the negation is `val = -val;` (neg on unsigned = negu) — merge.

Let me look at the actual RTL/combine behavior: maybe combine doesn't merge if the copy's destination is used *between* in a way cse leaves. Let me try to see the cc1 dumps: tools/cc1_dumps_tu.sh can dump the RTL passes for the TU. That would tell me exactly what pass merges. The brief says dumps go under the item dir and must be deleted after reading.

But before that: let me think about what makes the target. Since the target was compiled from the *original* source by the same compiler, and the current src (with asm) reproduces it, the original source had something that kept the two insns.

Maybe the original source's else had a *different computation*:
```c
} else {
    val = nudge;
    val = -val;
}
```
Hmm.

What if the original had:
```c
if (rand() & 1) {
    val = nudge;
} else {
    val = nudge;
    val = -val;
}
```
but with `val` being used in the `rand() & 1` condition? no.

What if the copy is `val = nudge;` and the negation is `val = -val;` but there's a *label* from a loop:
```c
do {
    val = nudge;
    val = -val;
} while (0);
```
Tested (c2 variant) — score 1.

Hmm, maybe the merge is happening in cse (copy propagation) rather than combine: cse sees val=nudge and substitutes nudge at the use, deleting the copy. To block cse, the value must not be a simple register copy? cse propagates register copies too.

What about making `nudge` and `val` different *widths*: e.g. `nudge` s32, `val` s32.

OK, let me look at the dumps. Use tools/cc1_dumps_tu.sh on the TU with the c1 candidate? The tool dumps the TU as-is from src. I'd need to compile with the candidate body. Hmm — maybe delever_search has an option to dump passes. Let me check cc1_dumps_tu.sh usage.
