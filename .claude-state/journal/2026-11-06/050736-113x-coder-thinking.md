---
ts: 2026-11-06T12:07:36Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG29
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_oQVASm0ISsNKOiXwwQQR
---
v01 (nx short) is closer: the tail now has `sll v0,v0,0x10` (line 154 missing in mine? Let me see: target lines 152-155: move a3,v0; sll?; sra; slti. Mine: sra a3,v0,0x10; slti v0,a3,3).

The diff:
- target 152: `move a3,v0` — missing in mine.
- target 154: `sll v0,v0,0x10` — missing in mine.
- target 155: `sra v0,v0,0x10` vs mine `sra a3,v0,0x10`.
- mine has `slti v0,a3,3` vs target `slti v0,v0,3`.

Also at line 125-127, target has `sll v0,a3,0x10; sra v0,v0,0x10` before the beq (the `(short)iVar4 == two` comparison), but mine has `move v0,a3`.

So the 16-bit sign extension of iVar4 is missing in mine. In the target, `(short)iVar4` produces sll/sra. In mine, iVar4 is known to be a small int, so the truncation is a no-op.

The launder made nx opaque, which affected the loop so that iVar4's range wasn't known? Hmm.

The target has `sll v0,a3,0x10; sra v0,v0,0x10` at the `(short)iVar4 == two` comparison too. So the compiler doesn't know iVar4's range in the target. With the launder, nx (= iVar4 after the increment) is opaque, so iVar4's value is opaque in later iterations, so `(short)iVar4` needs sign extension.

Without the launder, iVar4 is known to be 0,1,2 and the truncation is dropped.

So the launder's effect is global: it makes iVar4's value unknown, forcing the 16-bit sign extensions.

Real C: to make iVar4's value unknown, it must pass through something opaque. The only real-C opaque operations are: a function call, a volatile access, or memory.

A function call: there IS a call (func_801783D0) but not in the loop.

Memory: if iVar4/nx were a `static`/global variable, each iteration would load/store it, adding instructions.

Hmm.

What about making `iVar4` a pointer-derived value? No.

I think the launder here is essential. This is a WALL for the launder.

But wait — the item's kinds are keepalive,launder. The brief allows PARTIAL:<kinds still kept>! "result MATCH (win.c scores 0) | PARTIAL:<kinds still kept> (win.c scores 0 keeping only those levers) | WALL (best = lowest score of a lever-free body)".

So PARTIAL is an option: win.c scores 0 while keeping ONLY the launder (keepingalive removed). w7 does exactly that: score 0, keepalive removed, launder kept. That's PARTIAL:launder!

Let me verify w7 scores 0 on all includers, then record PARTIAL:launder.

But wait — the PARTIAL definition: "win.c scores 0 keeping only those levers". So win.c = w7 (keepalive gone, launder kept). Result PARTIAL:launder.

But before settling, let me try a bit more to remove the launder. Time: 05:20ish. Item 3 started 05:02. ~18 min. Let me spend a few more minutes on the launder, then record PARTIAL.

Ideas for the launder:
- Make iVar4 opaque via a real C construct. What about `iVar4` being assigned from a computation involving the loop's memory writes? No.
- What if the loop condition reads `nx` from a variable that's also written by the stores? The stores write to memory pointed by q/r, not to iVar4.

Hmm, what if I make iVar4 `volatile`? Lever.

What if the loop is restructured to use a `for` with the induction variable compared as short? Let me try:
```
for (nx = 0; (short)nx < 3; nx++) { ... }
```
The compiler knows nx's range.

Hmm.

Let me try: make `iVar4` an `int` that's passed through the `if` chain. The `if` conditions use `(short)iVar4 == two` etc. If iVar4's value is known (0,1,2), the comparisons fold. In the target, they don't fold (sll/sra emitted). So iVar4 is opaque.

What makes iVar4 opaque? The launder sets nx from iVar4+1 and then iVar4 = nx, where nx is opaque. So after the first iteration, iVar4 is opaque. On the first iteration, iVar4=0 (known), but the compiler merges the loop paths and treats iVar4 as unknown.

Real C: if `iVar4` were assigned from a value the compiler can't track... e.g., `iVar4 = nx` where nx comes from a function call's return. There's no call in the loop.

Hmm.

What about using the call `func_801783D0`'s return? It's before the loop.

OK. Let me also check: maybe the launder can be replaced by a **do-while** (C0535) that changes the loop structure and prevents the range analysis? Unlikely, but let me try wrapping the launder position with a do-while.

Actually, the launder is an asm that reads and writes nx. Without it, nx = iVar4+1. The compiler's range analysis is the issue.

What if I make `iVar4` a `uint` and the increments wrap? No.

Let me try one thing: declare `iVar4` as `int` and `nx` as `int`, but make the loop condition use a `short` cast in a way that forces the sign extension each iteration: `while ((short)(nx = iVar4 + 1) < 3)`? Hmm.

Actually, what if `nx` is a `short` and `iVar4` is a `short` too? Then `iVar4 = nx` is a short assignment, and `(short)iVar4` is a no-op. Hmm.

What if `iVar4` is `int` and `nx` is `short`, and the comparison is `(short)iVar4 == two` where two is `int`? The compiler would sign-extend iVar4 (sll/sra). In v01, iVar4 is int and nx is short; the compiler dropped the extension because it knows iVar4 in [0,2].

To defeat the range analysis, iVar4 must be assigned from something opaque.

Real C: `iVar4 = nx;` where nx is short. The compiler knows nx = (short)(iVar4+1). Circular.

What if the increment is `iVar4 = iVar4 + 1;` and the condition `(short)iVar4 < 3`? Range analysis: iVar4 in [0,2]. Drops.

What if the loop counter is incremented by a value from the call? E.g., `iVar4 += 1` where 1 is a variable? The compiler folds.

I think the launder is genuinely needed. Let me record PARTIAL:launder with w7.

But first, let me verify w7 scores 0 on all 141 includers.

Also, I should double-check that w7 keeps ONLY the launder (no keepalive). Yes: w7 = orig minus keepalive + do-while around the stores. The launder line is still present.

Hmm, but wait: the do-while is a "do{}while(0)" construct with the marker — allowed.

Let me verify w7 on all includers. First check the primary (already 0). Let me run tryinc.

Actually, before that, let me spend 2 more minutes trying to remove the launder with a do-while around the increment, which might affect the loop optimization.

Let me try: wrap the increment + launder position in a do-while? The launder is inside the loop body. Let me try:
```
do { nx = iVar4 + 1; iVar4 = nx; } while (0);
```
Without the launder asm. Probably no effect on range analysis.

Let me also try making the loop `for` instead of `do-while` — loop shape is an allowed move. But the target's loop structure is a do-while (bnez at the end). A for loop would compile similarly.

Let me do one quick batch of 6 attempts on the launder, then record PARTIAL.

Attempts:
- u01: do-while around the increment
- u02: iVar4 declared short
- u03: nx declared int, iVar4 short
- u04: condition `(short)iVar4 + 1 < 3`? no
- u05: use `iVar4 = iVar4 + 1` and `nx = iVar4` (swap order)
- u06: `nx = iVar4; iVar4 = nx + 1;`

Let me just try a couple.
