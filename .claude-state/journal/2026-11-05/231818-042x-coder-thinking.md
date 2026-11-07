---
ts: 2026-11-06T06:18:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_JCpFYRCdApUMMfz9gQm4
---
In w4 the loop-2 registers got shifted (i and otz swapped: s2↔s1). The extra do-while changed ref weights globally.

Hmm. So the second do-while is too disruptive.

Alternative approach for the otz copy: prevent combine's fold with an insn that survives cse2 but is cheap and folds in combine.

What survives cse2 but combine removes? For instance, a *comparison* result: 
```
if (otz == 0) { }
```
No.

Actually, what about a `REG_DEAD`-avoiding trick: make otz's value used twice *within the same statement* in a foldable way. E.g.:

```
otz = func_801823D4(otz, -0x1A);
```
becomes
```
otz = func_801823D4(otz + (i - i), -0x1A);
```
tree folds.

Hmm.

What about using `otz` as the second argument too? `func_801823D4(otz, -0x1A)` → target args: a0=otz, a1=-26. No.

New idea: What if the *first* assignment is not a direct call result but is computed in a way that leaves a real insn: e.g.

```
otz = RotTransPers4(...);
otz = func_801823D4(otz, -0x1A);
```
What if we instead write:
```
{
    s32 r = RotTransPers4(...);
    otz = r;
    otz = func_801823D4(otz, -0x1A);
}
```
RTL: (set r v0), (set otz r), (set a0 otz). Combine folds all into a0=v0? Yes likely.

Hmm.

OK, what about a completely different approach to the target shape: in the target, otz's set is materialized. What if otz is *live across the func_801823D4 call*? Then combine can't fold (the value is needed after the call). E.g.:

```
otz = RotTransPers4(...);
func_801823D4(otz, -0x1A);      /* result discarded */
```
no, changes semantics/insns.

Alternatively, restructure so the arg copy comes from a value that's live: e.g.
```
otz = RotTransPers4(...);
t = otz;         /* copy */
otz = func_801823D4(t, -0x1A);
```
Then t is live only to the call. combine folds t.

Hmm.

What about `otz = RotTransPers4(...)` then use `otz` in the AddPrim *before*? no.

Let me look at this from another angle: what if we DON'T need otz's first set at all — maybe the target's `move s1,v0` is the assignment of the *global* pseudo otz, and if otz were assigned from the call result directly in a way that global-alloc keeps... The fold is a combine optimization on dead values. Since otz's first value dies at the copy, combine folds. The only way to stop it is to keep the value alive.

What if otz's first value is used in the loop *condition*? no.

What if we make the *second* call's argument not the only use: add a use in the following `AddPrim`? The AddPrim uses the *second* otz.

Hmm, what about swapping the order: compute otz = func_801823D4(RotTransPers4(...), -0x1A) — that folds both.

OK here's another thought: maybe instead of preventing the fold, we can make the target's insn appear from a different source: the target has an extra `move s1,v0`. What if we make the *first* call's result stored to a variable that is used later in a cheap way... 

Actually! What about `otz` being used as the second argument to `func_801823D4` in a swapped way? No.

Let me look at the actual target source: the asm re-tie is `__asm__("" : "=r"(otz) : "0"(otz));`. Is there a *real C* 2nd set that's free? "§189-C form" per the comment. §189-C might be documented in the cookbook. Let me grep the cookbook for "189".

Let me grep cookbook INDEX for relevant techniques: "re-tie", "second set", "move pair".
