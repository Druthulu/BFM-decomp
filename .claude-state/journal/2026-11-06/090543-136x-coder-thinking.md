---
ts: 2026-11-06T16:05:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_x8WtHcJNtZaks2a64YnD
---
Target:
```
lh v0,132(s0)      ; t = unk84
nop
bnez v0,6398       ; if (t != 0) -> else
move v1,v0         ; DELAY SLOT: u = t  (the copy in the delay slot!)
...
[else at 6398? actually 6398 is the else]
...
addiu v0,v1,-1     ; t = u - 1
```
Wait, the branch `bnez v0,6398` jumps to 6398 which is... let me map. The else branch is at 6398. The delay slot is `move v1,v0`. Then the if-body runs (the func_80133784 stuff), and at the end `j 639c; li v0,30`. The else at 6398: `addiu v0,v1,-1; sh v0,132(s0)`. Hmm, the addresses are confusing, but the structure:

- t = unk84 (lh v0)
- if (t == 0) { ... } else { u = t; t = u - 1; }
- The `move v1,v0` is in the bnez delay slot (executed always, or only on the taken path? MIPS delay slots execute always unless nullified). The move computes u = t before the branch — it's the `u = t` copy, scheduled into the delay slot.

So the target has `u = t` as a real copy that survives. The move is in the delay slot.

In c1 (with zr as an uninitialized variable): `addu v0,v0,v1` (u = t + zr, zr in v1) in the delay slot — wrong.

In c2 (`u = t`): combine merged u into t, removing the copy.

So we need the copy to survive as `move v1,v0`. Why did combine merge in c2? Because u's only use is `t = u - 1`, and `u = t` is a copy → combine substitutes u → t, and the copy dies.

The original used `u = t + zr` with zr a hard register ($0), which combine can't fold (a hard-reg addend). So the copy survives. Without a pin, how?

Options from the moves:
- func_80182ED4 MATCH: "copy hoisted above the branch via s16 temp (tmp=(s16)t; u=tmp) — HImode copy escapes cse equivalence class, so or v1,v0 survives in the bnez delay slot".
- func_8018302C WALL: "target move v1,v0 is plus v,$0: a hard-reg addend combine cannot fold; a C-level zero is a constant -> combine folds -> cse propagates (best 2)".

Our target IS `plus $0` (move = addu with $0), and best is 2 — matching the WALL. But wait, maybe the move could be `or v1,v0,$0` from an HImode copy? The disassembly prints `move` for both addu and or. Let me check the actual instruction encoding? The target's `move v1,v0` — could be `addu v1,v0,$0` or `or v1,v0,$0`. The HImode copy trick produces `or v1,v0,$0`? Hmm.

The c5 (u u16) produced `andi v0,v0,0xffff` — not it. c4 (u s16) produced 43 ins.

Let me try the func_80182ED4 trick exactly: `tmp = (s16)t; u = tmp;` where tmp is a separate variable. That's a copy chain. Let me test:
```
s32 u; s16 tmp;
...
} else {
    tmp = (s16)t;
    u = tmp;
    t = u - 1;
}
```
Hmm, that adds a variable and maybe a move.

Actually the moves line says "copy hoisted above the branch via s16 temp (tmp=(s16)t; u=tmp)". Let me look at that function's win.c for the exact spelling. func_80182ED4 is in another shard/dir. Let me search for its win.c.
