---
ts: 2026-11-06T11:43:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_jUND0EdP6Ql9O1b0GA8G
---
Score 18, 31 vs 33 ins, with register-pair mismatches: a0->a1 x3, a1->v0 x1. So the main problem is register allocation: mine keeps a1 in a0 (coalesced with a0v), target has a1 in a1 (a real copy `move a1,a0` at entry). And a1->v0 for the load.

The `a1 = a0v + zr` opaque copy was keeping a1 in its own register. Without it, a1 coalesces with a0v (a0). Real C to force a separate copy: the HImode trick! From moves.md: HImode copies escape cse. But a1 is a pointer (s32). Hmm.

Wait — target: `move a1,a0` at entry (a1 = a0v copy), then `lh v0,208(a1)`. So a1 is a distinct register from a0. The opaque `+ zr` forced the copy. 

How to force a copy in real C? Options:
- Make a1 a different type/width? If a1 were s16... no, it's an address.
- Use a struct/union? 
- Use a volatile read? No.

Hmm. The moves.md line 202/203/217 show HImode temp copies crack opaque copies for s16/u16 values. For a pointer, maybe a different trick.

Actually, wait. The function takes `s32 a0v`. The comment says "the incoming pointer is read off $a0 (§42/§73)". So a0v is the s32 arg in a0. a1 = a0v + zr creates an opaque copy in a1. 

To get a real copy `move a1,a0` in real C, I need the compiler to keep a1 as a separate pseudo. If I write `a1 = a0v;`, gcc coalesces them (copy propagation). To prevent coalescing, make a1 used in a way that... Hmm.

What if a1 is declared as a pointer type (e.g., `u8 *a1 = (u8*)a0v;`) and the accesses use a1? The cast might not prevent coalescing.

What if a1 is assigned via a function-like opaque? No.

Hmm, but actually the register pair a0->a1 x3 means 3 insns use a0 where target uses a1. If a1 coalesces to a0, that's a functional equivalence but different encoding (a0 vs a1). The score counts these.

Could I instead change the function's parameter handling? The brief says "no signature or decl change outside the body (callers stay as they are)". The def is `s32 func_80182334(s32 a0v)`. I can't change the signature.

Hmm. But maybe I can force a1 into a different register by using it first in a way that creates a conflict. E.g., `a1 = a0v; a0v = 0;`? That would clobber. Or use a0v after assigning a1, creating a live range conflict:
```
a1 = a0v;
a2 = D_80126948;   // uses nothing
```
No conflict.

What if I reference a0v again after a1 is assigned? Then a0v and a1 are both live → separate registers. E.g.:
```
a1 = a0v;
... use a0v somewhere ...
```
But the target doesn't use a0v after the copy (all uses go through a1). If I add a use of a0v, it changes codegen.

Hmm. Alternatively, use the HImode trick on the pointer: 
```
s16 lo = (s16)a0v;   // no, truncates
```

Wait, maybe the trick is different: the comment for `cpy = d0 + zr`: "keeps the load in $a0 and the addiu operand in $v1". So d0 is loaded into a0 (from the `lh a0,208(a1)` at target[10]) and cpy into v1 (`move v1,a0` at target[15]). So `d0 + zr` forces cpy to be a separate reg (v1) from d0 (a0).

Without zr, `cpy = d0` coalesces cpy with d0. So mine uses a1 for both? The diff shows a1->v0 x1 (mine a1, target v0).

So both opaque copies need real-C equivalents. This is the classic "opaque copy" wall. moves.md has many WALLs for cse-opaque-copy (G07: func_80181E64, func_800D0D7C, func_8003DF8C). But some were later MATCHed with HImode tricks (func_8003DF8C: u16 i/j; func_80181E64: s16 v).

For s32 pointer copies, is there an HImode trick? Let me think: `a1 = a0v;` where a0v is s32. If I declare an intermediate `s16 tmp = a0v;` that truncates — wrong value.

What about using a union or bitfield? E.g., declare a1 as a pointer and copy through a `void*`? No.

Hmm, what about making the parameter itself HImode? Can't change signature.

Let me reconsider: maybe the target's `move a1,a0` isn't essential for a byte match if the function is judged by the whole object... no, score 18 means it's not matching.

Let me look at the disassembly of the target and mine to understand better. Let me get the target dis and mine dis.

Actually, let me reconsider the whole approach. This is a small function (33 ins). The opaque copies are load-bearing. The G07 WALLs for s32 opaque copies suggest it's hard. But the task expects me to try 20-30 min and possibly WALL.

Let me look at the target disassembly to see exactly what's needed. Let me dump both.

Let me get target dis for func_80182334.
