---
ts: 2026-11-06T05:38:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_T88nYZR2Hq3Niglxy8Zp
---
s1 compile error (probably my replacement of the else-arm's closing brace failed or the structure is off). s2 = 18 (same as a1).

Time 22:38. Started 22:24 → 14 min. Hmm, the clock is barely moving because each batch is fast.

I need ≥20 min of wall time. Let me continue investigating for ~6 more minutes of real time.

Let me try a genuinely different idea I haven't: what if the copy is `tmp = iVar2;` and I add a **`(s16)` cast on the store value in a way that creates a second set**? No.

Hmm, let me look at the problem from the "what would the original source look like" angle. This is decompiled code; the real source probably was:

```c
void func_80181784(s32 a0) {
    s32 *p;
    s16 v;
    s32 t;
    ...
}
```

Hmm, what if `tmp` was originally a *different type*, like `s16 tmp`? Then `tmp += 0x80` in HImode... no.

What if the original used a `struct` with the s16 field? e.g.:
```c
((Unk*)iVar1)->unk10 = ...;
```

Hmm.

Actually — let me reconsider. What if the target's `move v0,a0` comes from the *initialization of a variable in a different scope*, e.g.:

```c
if (iVar2 != 0) {
    s32 tmp = iVar2;
```
m2 tried scoped tmp → 23 (66 ins, worse).

What if `tmp` is initialized at declaration at the top: `s32 tmp = iVar2;`? Can't (iVar2 defined later).

What about `s32 tmp = 0;` at the top? Adds li.

OK. Let me try the exact original with the launder replaced by a *real* 2nd set of tmp that's value-preserving. The launder re-sets tmp = tmp. A real 2nd set could be `tmp = tmp;`? Deleted. `tmp = (s16)tmp;`? a1-like (that's a1 but on tmp instead of iVar2).

Let me try: keep `tmp = iVar2;` and add `tmp = (s16)tmp;` right after. This is a real 2nd set of tmp (a sign-extend), cse might fold it. Let's see.

Also: `tmp = iVar2 & 0xFFFF;`? For iVar2 in s16 range, `& 0xFFFF` changes negatives... but as analyzed, only the low 16 bits matter for the stores and the shifted comparisons. Hmm, `tmp * 0x10000` with tmp = (iVar2 & 0xFFFF): same low bits. And `tmp += 0x80` then `(s16)tmp` store — same low 16 bits. And `tmp -= 0x80` — same. So `tmp = iVar2 & 0xFFFF;` is semantically equivalent for this function! And it's a real operation (andi). But gcc might fold `iVar2 & 0xFFFF` — for iVar2 in [-32768,32767], the andi is NOT identity for negatives, so gcc can't fold it. It would emit an andi 0xffff — an extra instruction! Unless combine can fold the andi into something.

Hmm, but wait: maybe gcc can see that the value is used only via `(s16)tmp` and the shifted compare, and optimize the andi away? Risky.

Let me try it anyway — score will tell.

Let me also try `tmp = (u16)iVar2;` (a1-like but on the value). Same thing.

Let me run these two.
