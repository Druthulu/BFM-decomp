---
ts: 2026-11-06T12:04:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_eLA4RXjBP0pcUysz5oDn
---
Target:
```
5f8: sh a1,16(sp)      f.cx = arg1
5fc: addiu a1,sp,16    va = &f.cx
600: sh a2,18(sp)      f.cy = arg2
604: move a2,a1        vb = va
...
648: jal func_80149350 with a0=node, a1=va, a2=vb
64c: sb v1,84(sp)
650: addiu a0,sp,16    &f.cx for the next call
```

So the target's va = a1 and vb = a2, materialized right after the stores.

Mine:
```
addiu v0,sp,16
...
move a2,v0
...
move a1,v0
```
Mine's va is v0.

The difference: target's addiu goes to a1 (the argument register) directly; mine to v0 with copies.

In local-alloc terms, the pseudo for va should prefer a1 (the call arg). Mine picked v0. 

Why? Maybe because in mine, a1 is already occupied by something (arg1 = a1 input, still live? f.cx = arg1 at 5f8 uses a1, then a1 is free).

Hmm. If the pseudo va is born right after `f.cx = arg1` (which kills a1), local-alloc could reuse a1.

Real C: the launder is kept in p2. Its position: after `va = (u8 *)&f.cx;`.

Hmm, what if `f.cx = arg1;` and `va = ...` order changes? Let me try moving `f.cx = arg1;` after `va = ...`? That changes semantics? No: va = &f.cx doesn't depend on the value. So:
```
va = (u8 *)&f.cx;
f.cx = arg1;
launder;
f.cy = arg2;
vb = va;
launder;
```
Try.

Also try: `va` computed before `cv = ...`.

Let me also try a variant where the two stores f.cx/f.cy are adjacent (they are: 5f8, 600 in target).

Honestly, I'm running long. Item 4 is at ~20 min. Let me do a final batch of ~8 variants on p2 and ~8 lever-free, then record whatever.

Actually — wait. A thought: maybe the lever-free crack for item 4 is achievable by *reordering the f.* assignments* to match. v0 = 18 with 159 insns. p2 = 4.

Let me try on p2:
- g1: va before f.cx.
- g2: both va and vb computed before the stores.
- g3: `u8 *va, *vb;` declared on one line.
- g4: `vb = (u8 *)va;` (cast).
- g5: call args as `(u8*)&f.cx` directly (nova = 5).

And lever-free:
- h1: v0 with va before f.cx.
- h2: v0 with the two launders replaced by explicit pointer copies (va2 = va).

Let me run 8.
