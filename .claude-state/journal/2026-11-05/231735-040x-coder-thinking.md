---
ts: 2026-11-06T06:17:35Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_PFnGQHxswVKmVYsMouuR
---
At cse2 (before combine), the RTL is exactly what we want:
- insn 151: (set r80 (reg v0)) — otz = call result
- insn 164: (set a0 (reg r80)) — arg copy

So combine then folds 151+164 into a0=v0. We need to block combine.

Combine's try_combine can combine insn 151 with 164 (i3) if... there's a note between them (LOOP_CONT/LOOP_END) but that doesn't block.

What blocks combine: an insn between them that uses r80 (a use, making r80 not dead). Since the target's asm did exactly that.

Idea: what if we insert a *use* of otz that is a no-op insn at RTL but not removable by cse2? For example `(set r80 (plus r80 0))` — cse2 might keep it? Then combine would fold it.

Hmm — what about a *comparison* whose result is used: e.g.

```
if (otz == otz) { }   /* never taken? */
```
adds branches.

What about the classic "do { } while (0)" *with* a use in the condition: `do { } while (otz, 0);` — the front end might emit a test.

Alternatively — think about what real C construct produces `(set otz v0)` followed by a *use* of otz and then `(set a0 otz)`. 

What if the argument expression is a bit more complex: `func_801823D4(otz, -0x1A)` where the call's first arg is `otz`. The RTL for the arg is (set a0 otz).

What if we make the source: `otz = RotTransPers4(...); otz = otz;`? The front end folds a self-assignment (tree-level).

What about `otz = RotTransPers4(...); otz += 0;`? folds.

What about `otz = RotTransPers4(...); otz = otz | 0;`? folds at tree.

Hmm, so we need an RTL-level use. What about `otz = RotTransPers4(...); if (otz) {}`? An empty if — the tree may keep the condition (side-effect-free → folded away).

OK, what about a real use that costs no *insn* because it merges: e.g. using otz in the loop condition? `for (; i < 12; )` no.

What about making `otz` used in a store that already exists: the stack arg store? no.

Hmm, let me reconsider: maybe instead of blocking the fold, we can make the *target* shape arise differently. In the target, the arg copy is `move a0,s1` — i.e. otz is in s1. If combine folds, we get `move a0,v0` (1 insn). Target has 2 insns. So we must keep otz's set.

What if otz were used *after* the arg copy in the same expression: `func_801823D4(otz, -0x1A)` — what if we write `func_801823D4(otz, otz - otz - 0x1A)`? tree folds.

What about using otz in the second argument's *type cast*: no.

New idea: use a **different variable for the second call's result** so otz's first value lives on... no.

New idea: **make the first call's result assigned to two variables**: 
```
s32 t = RotTransPers4(...);
otz = t;
```
Then RTL: (set t v0), (set otz t), (set a0 otz). Combine would fold both copies into a0=v0. Worse.

New idea: make otz's set *not* directly from v0: e.g. `otz = RotTransPers4(...) + 0;`? folds at tree. `otz = (s32)((u32)RotTransPers4(...))`? no-op.

Hmm what about `otz = RotTransPers4(...); otz = (s16)otz;` → sll/sra = 2 extra insns; target would have 164. No.

Wait — maybe a cheaper variant: `otz = (u16)RotTransPers4(...)`? = andi 1 insn. Still +1.

Hmm, what about a *use* of otz in the argument of the second call in a way that produces the a0 copy plus a cheap fold... 

Let me look at how other items in this project solved the "move pair" problem without asm. moves.md line 219: "pin | func_8018302C | MATCH: the copy wrapped in do-while(0) (loop-shaped live range) — or v1,v0 survives AND the slti keeps the load's reg v0; s16 temp alone rewrites the slti operand". So wrapping the copy in do-while(0) made `or v1,v0` survive! That's the same class: a copy that combine would fold, kept by do-while(0).

Also line 146: "pin | func_8017CE7C | MATCH — do-while(0) around the tail gives the byte temp a loop-shaped live range".

So: wrap the *use* (the func_801823D4 call statement) in do-while(0), or wrap the copy.

In my w2 I wrapped the RotTransPers4 call. Let me instead wrap the second call statement:
```
do {
    otz = func_801823D4(otz, -0x1A);
} while (0);
```
This puts the a0 copy inside a loop block, separated from otz's set in the previous block by LOOP_BEG. Combine can't cross the loop boundary (probably).

But it also affects pp's ref boost? pp's use is in the RotTransPers4 call. If I remove the do-while there, pp loses the boost. So keep both do-whiles:
```
do { otz = RotTransPers4(..., pp, pf); } while (0);   // pp ref boost + block split
do { otz = func_801823D4(otz, -0x1A); } while (0);   // block split for the copy
```

But careful: the second do-while changes loop depth for other pseudos (e.g. otz's use). Let's test.

Let me create w4.c: both wraps.

Actually, maybe simpler: wrap ONLY the second call and see if pp's priority still works... no, pp needs the first wrap. Let's test w4 (both).

Also try w5: first wrap around the RotTransPers4 call, and put the a0 copy inside an `if` — no.

Let's generate w4 and score.
