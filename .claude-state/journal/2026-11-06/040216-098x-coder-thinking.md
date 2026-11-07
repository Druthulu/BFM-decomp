---
ts: 2026-11-06T11:02:16Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_GxfSnQZbl3S2exxdK6L9
---
Let me see the target around f78-fb4:
```
f78 li v0,3
f7c bne v1,v0,fb4     (D_80115126 != 3 → else)
f80 li v0,3           (delay slot: the copy!)
f84 lui v0,D_8011511A
f88 lhu v0
f8c nop
f90 bne v0,v1,fb4     (D_8011511A != 3 → n=4)
f94 li v0,4           (delay slot)
f98 ... call ...
```
So the `li v0,3` at f80 is the outer else's `n = 3` copied into the bne delay slot (reorg copies the cross-jump target).

Interesting: the branch at f7c targets fb4, which is the shared `n = 3` code? Let me see fb4.

So the two n=3 sites (outer else and inner then) are cross-jumped; the outer else is the target, and reorg copies it into the delay slot.

For a lever-free body, the comment says a plain `n = 3` gets deleted as a noop move (because v0 already holds 3 from the compare). 

Hmm, what if we prevent the noop-move deletion by making `n` a different register... e.g., if n is a s16? Or if the value is loaded into a *different* pseudo?

Real C ideas:
- `n = 3;` where n is used later such that the move isn't a noop? The noop move is `v0 = v0`? The comment: "its value is already in $v0 from the compare constant" — so `n = 3` becomes `move n, v0` where v0 holds 3; if n is assigned to v0, it's a self-move → deleted.

If n were allocated to a different register (s1?), the move wouldn't be a self-move. Hmm, but n's qty gets v0.

What if we make n's value be used in a way that requires a different reg? E.g., n is used as a loop counter compared with i (s16).

Hmm.

What if we write `n = 3;` and then use `n` in a context that forces a copy... 

Alternatively, use a *variable* for 3 that isn't in v0: e.g., 
```
s32 k;
...
k = 3;
n = k;
```
The compare uses the constant 3; k=3 loads into some reg; n=k copies. But the target's `li v0,3` in the delay slot...

Hmm, what if the C uses `n = D_80115126;`? No.

Let me try the simple restructures and see the scores. Even if the target's exact opaque copy is unreachable, maybe a different structure yields the same bytes.

Time is short. Let me generate a few variants for this big item:
A. base.
B. `n = 3;` before the if + inside (restructure).
C. ternary: `n = D_80115126 == 3 ? (D_8011511A == 3 ? 3 : 4) : 3;`
D. `s32 three = 3;` variable used for both n assignments.
E. do-while around each `n = 3`.
F. n declared s16.
G. the memory barrier replaced by the struct alias (aD801151D0) — combine with A.

Let me build A with the struct alias first (fix issue 3), then explore the n issue.

Actually, since the item may well be a wall, let me first check the score of A+struct alias to see if issue 3 is fixed and only the RC-12 remains.

Let me create the struct alias variant:
```
extern struct { s32 v; } aD801151D0 __asm__("D_801151D0");
...
aD801151D0.v = (s32)ot;
```
And remove the `extern s32 D_801151D0;`? Keep it (it's used in func_80137D08(D_801151D0, ...)). So keep the extern s32 for the read, and add the struct alias for the store.

Let me build and score.
