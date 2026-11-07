---
ts: 2026-11-06T05:17:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_TWyWZsSmgpQA3yzuK81a
---
No change. do-while didn't help. Hmm.

Let me think again. Maybe the copies are eliminated by combine/cse before... Actually let me look at what the target's RTL would be with pins vs lever-free. Maybe a different angle: the pin forced raw into $3 (v1) and t into $2 (v0). The moves are `move v1,v0` and `move v0,v1`. 

What if we can get the same instruction sequence by *not* having raw/t at all, but instead having the store value go through an extra copy? E.g.:

Target:
```
addiu v0,v1,-16   t = raw - 16   (v1 = raw)
bgez v0
move v1,v0        (raw = t)
...
move v0,v1        (t = raw)
sb v0,38(s1)
```

The last move `move v0,v1` copies from v1 (raw) to v0 (t). The store value is t.

Alternative source that yields this: 
```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) {...}
raw = t;
*(u8*)(s1+0x24) = *(u8*)(s1+0x25) = *(u8*)(s1+0x26) = raw;   // store raw (v1) directly
```
That gives only `move v1,v0` then stores from v1. Not target (target stores from v0).

Hmm what if:
```c
raw = t;
t = raw + 0;  // no
```

What if we reverse the roles: store value is `raw` but gcc copies to v0? 

Honestly, the two moves are a pure artifact of two hard-reg variables. Lever-free plain C collapses copies. But the task insists a lever-free MATCH exists (these items are given with kinds and expected to be crackable or a WALL). WALL is acceptable if we can't. But we should try hard.

Wait — maybe there's another lever-free move: make raw and t have *different types that are both integer* such that the copies survive as real instructions because of mode conversion, e.g. `raw` s32 and `t` s16? Let's think: t = raw - 0x10 in HImode? Target addiu is SI.

Hmm, what about `raw` being `s32` and `t` being `s32` but the copy going through a `u8` cast where gcc can't prove range because the guard is on t but the value stored is... 

Actually! Reconsider: what if the *store* is the key. In target, `sb v0,...` stores t. If instead we store `raw` and gcc needs to truncate raw to QI, and raw is in v1, then we'd have `sb v1` — not target.

Let me look at the actual cse2 dump for the pinned orig to see the insn structure, then compare to lever-free. Maybe there's something else: the launder is `__asm__("" : "=r"(raw) : "0"(raw))` — an asm with tied output. Its RTL effect: raw is set (output) from raw (input). This is a real insn that defines raw. So after the asm, raw is a new value. Then `t = raw` is a copy. 

A lever-free equivalent "real 2nd set" of raw: `raw = t;` followed by something that re-sets raw to the same value in a way gcc can't fold. In the catalog, e.g., `pv &= 0xFF000000` — a compound assignment that is a real 2nd set. Here we need raw = t and then t = raw. What if we do:

```c
raw = t;
raw = raw | 0;   // folds
```

What about `raw = t; raw = (u8)raw;` — truncation to u8 of a value in [0,239] — combine folds.

What if the value range ISN'T provable: e.g., t comes from `raw - 0x10` where raw is s32 from lbu. raw ∈ [0,255] so t ∈ [-16,239]. The guard `if (t<0) return` narrows to [0,239]. GCC's cse uses `REG_EQUAL` notes from combine. If the guard were before... 

What if we compute t differently so its range isn't known: `t = (raw & 0xFF) - 0x10`? Same.

What if raw is loaded as s8 (signed byte)? `raw = *(s8*)(s1+0x24)` would use lb (sign-extend) — target has lbu. No.

Hmm. What if t is computed as `t = raw - 0x10;` where raw is a *parameter-like* value gcc can't range-analyze? The load gives range.

What if we load raw, then compare, and compute t twice?
```c
raw = *(u8*)(s1+0x24);
if (raw - 0x10 < 0) { call; return; }
t = raw - 0x10;
raw = t;
t = raw;
```
Here t = raw - 0x10 is computed after the guard; the guard's condition is a separate computation. gcc would CSE the two `raw - 0x10` into one. Hmm.

What about making the compare use a different form: `if ((s32)raw < 0x10)`. Then t = raw - 0x10 computed after. The range of t is still known from the branch (raw ≥ 16).

I think the fundamental issue is gcc knows t ≥ 0 and t ≤ 255, so (u8)t round-trip is a no-op.

BUT: what if the store value needs a *sign* extension, i.e., t could be negative? If the guard is `if (t < 0) return;` then no.

Wait, wait. Let's re-examine the target: is it possible that the moves aren't a round-trip of the same value? `move v1,v0` then `move v0,v1` — between them there's the branch and the call path. On the *fall-through* path (bgez taken), the delay slot executes move v1,v0, then at 4fc move v0,v1. So yes round trip.

Unless... the delay slot `move v1,v0` is `raw = t` and the 4fc `move v0,v1` is `t = raw`, both from source.

OK so let me consider: is a WALL acceptable here? Yes: "WALL (best = lowest score of a lever-free body)". The budget: 20-30 min per item, WALL needs ≥20 min and ≥30 scored tries. So for each item I can either crack it or record a WALL after 30 tries. With 5 items, that's potentially 150+ tries. That's a lot but feasible if I batch candidates.

But before giving up on item 1, let me try a few more mechanisms. Actually, let me reconsider the whole structure. Maybe the source isn't `raw = t; t = raw;` at all. Let me look at the pinned orig's RTL dump to see exactly what the launder+pin produce, then think about what plain C could produce the same.

Actually, the key insight might be different: maybe `raw` and `t` are not copies of each other in the intended source; maybe the target's `move v1,v0` / `move v0,v1` come from gcc's *hard register* allocation with the pins. The pins are the lever. Removing them collapses. To reproduce with plain C we need two variables that gcc keeps in separate registers with a copy between them — the classic way is to make them different modes (HImode copy trick) as in func_8017E204.

In func_8017E204: v0 is a loaded value (SI), t is s16 temp, v1 = t. The copy v1 = t stays. So the chain is: v0 → (s16)t → v1. cse doesn't equate v0 and v1.

Our target: raw → t and t → raw. Suppose we use:
```c
raw = load;
t = raw - 0x10;
if (t<0) ...
s16 tmp = (s16)t;   // HImode copy
raw = tmp;          // raw = (s32)tmp: sign-extend... 
t = raw;
```
Hmm, but target's moves are between v1 and v0 only, no third register.

Alternatively:
```c
raw = load;
t = raw - 0x10;
if (t<0) ...
tmp = (s16)t;    // tmp in v1, t in v0: move v1,v0
t = tmp;         // t = tmp: move v0,v1
```
This gives exactly two moves: tmp←t and t←tmp! And no raw needed for the store. But then what about raw? raw is used in addiu only. And tmp (s16) in v1.

Wait, but the target's `move v1,v0` is in the delay slot and `move v0,v1` after. In this spelling: `tmp = (s16)t;` then `t = tmp;` — two copies of the same value. Does cse merge them? `tmp` is HImode; `t = tmp` is a sign-extend SI. cse might equate t with tmp's... In func_8017E204, `t = (s16)v0; v1 = t;` kept ONE copy (v1 = t) — the HImode copy `t = (s16)v0` itself became part of the register allocation (v0's value sign-extended into t's reg? Actually the note says the sign-extend folded into the same instruction stream).

Hmm. In our case, we want BOTH copies to survive. In func_8017E204 only the second (v1 = t) survived as a move; the first `t = (s16)v0` was a sign-extend that... the target's move v1,v0 is one instruction, so the sign-extend+copy collapsed into one move.

So for us: `tmp = (s16)t` would be a move (if t's value known in s16 range), and `t = tmp` another move. Two moves! Registers: t v0 (original), tmp v1. That matches `move v1,v0` (tmp=t) and `move v0,v1` (t=tmp). 

But wait, we still need raw. In the target, raw is the variable loaded and used in addiu. If we drop raw and just use the load expression: `t = *(u8*)(s1+0x24) - 0x10;` then the lbu goes directly into... the addiu would be `addiu v0, vX, -16` where vX is the load's register. Target: `lbu v1,36(s1)` then `addiu v0,v1,-16`. So the loaded value must be in v1. If raw is gone, the lbu result pseudo would be... could still be v1. Hmm, the temp from lbu is a pseudo; local-alloc assigns.

Then after: `tmp = (s16)t; t = tmp;`. But the store uses t (v0). 

Actually wait: does the addiu need to be `addiu v0,v1,-16`? If the loaded byte pseudo is in v1 and t in v0, yes.

So candidate:
```c
s32 t; s16 tmp;
...
t = *(u8 *)((u8 *)s1 + 0x24) - 0x10;
if (t < 0) { ... }
tmp = (s16)t;
t = tmp;
stores(t);
```
Hmm but then the `move v1,v0` would be tmp = t. Registers: t in v0 (from addiu dest), tmp in v1. But the lbu dest needs to be v1 too — is it a different pseudo? The lbu result is a temporary that feeds addiu; it can be in v1. tmp is a different pseudo also in v1 (not live simultaneously? lbu temp dies at addiu; tmp born after). Yes, local-alloc could reuse v1.

But hold on: the target's lbu is `lbu v1,36(s1)` and then `addiu v0,v1,-16`. If t = load - 16 is combined, the RTL would be: (set (reg 84) (mem QI)) then (set t (plus (zero_extend reg84) -16)). The QI load pseudo 84 might be in v1. OK.

But we lose `raw` as a variable. That's fine — the target doesn't show raw separately except as the load reg.

Let me try this. Also variant keeping raw:
```c
raw = *(u8*)((u8*)s1 + 0x24);
t = raw - 0x10;
if (t<0) ...
tmp = (s16)t;
t = tmp;
```

Hmm, but then raw is dead after addiu. Fine.

Let me create candidates:
n5: as above with raw.
n6: without raw.
n7: `s16 tmp; tmp = (s16)t; raw = tmp; t = raw;`
n8: `t = (s16)t;` self-assign? Hmm: `t = (s16)t;` is a real 2nd set (sign-extend). But since t ≥ 0 and small, combine may fold. Actually a self-cast: `t = (s16)t;` — cse sees a set of t from t; might not delete (it's an assignment, but cse deletes redundant sets: set t = t is a no-op). With the cast, if the value is already in range, it folds.

Let me test n5 and n6.

Also consider using `u8`/`u16` temp:
n9: `u16 tmp; tmp = (u16)t; t = tmp;`

Let's do n5-n9.
