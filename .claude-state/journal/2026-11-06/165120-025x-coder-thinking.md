---
ts: 2026-11-06T23:51:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZQsGw7BHusKFZZsU7C24
---
cse_basic_block is called per extended basic block, and it processes from the block start. At the start, `new_basic_block()` is called at line 8479? Let me check whether new_basic_block is called at the beginning of each block (it is called once per cse_basic_block). Wait, new_basic_block is called at the top of cse_basic_block, so each block starts with a fresh table. But cse_main groups blocks into extended basic blocks and calls cse_basic_block with `from, to` spanning multiple blocks along a path — so equivalences CAN cross straight-line blocks.

A_hoist: q computed in the entry block, p=q in the then-arm. The path from entry to the then-arm is a straight-line path (taken branch), so cse follows it and the equivalence persists. Hence still merged.

Hmm.

OK so what C construct makes q unknown to cse? Let me think about the actual original source. Perhaps:

```
s32 *q;
q = &D_800C7C60;
...
p = q;
```
where q is *also* assigned later (dead) or is a variable that's reused. Or maybe q is a function-scope variable assigned in the if, and p is assigned elsewhere too.

Actually, what if the original is:
```
if (...) {
    p = &D_800C7C60;
    *p = val;
    D_800C7C64 = &D_800A2E20;
}
```
Then no extra move. So the extra move must come from somewhere real.

Hold on. Let me reconsider: maybe the extra move is NOT the q/p copy. Let me diff the actual instruction streams carefully. Mine 160 vs target 161, with the only count difference at mine[107:109] vs target[107:110]. That IS the move.

But maybe there's a different C that produces a move there for a different reason. E.g. if `p` is a parameter? No.

What if `p` is set in BOTH arms (then and else) — it already is (`p = 0` in else). In the target, `move a3,zero` appears at 120c in the delay slot of `bltz s3,1230`. Hmm interesting: that's the else path (p = 0). And then at 1210-1218 the then path.

What if we write `p = &D_800C7C60;` directly in the then arm (no q)? Then a3 = address directly. That's mine.

So target really has an intermediate v0.

Hmm, unless v0's value is not q but something else. `lui v0,0x0; addiu v0,v0,0` with reloc D_800C7C60. Then `move a3,v0`. So the address of D_800C7C60 is computed into v0 and copied to a3. 

Could this be because the store is `*p = val` where p was set to &D_800C7C60 but the compiler wanted v0 for something... no, the copy is explicit.

What if the C is: `p = &D_800C7C60; *p = val;` but `p` is used across a call so it must be in a callee-saved reg (a3 is caller-saved though). Hmm.

Wait, actually maybe the original C is:
```
q = &D_800C7C60;
p = q;
*q = val;
```
i.e., BOTH q and p used. Then q's use `*q = val` and p... no.

Let me try to see what C the target's RTL implies. The sequence: v0 = &D_800C7C60; a3 = v0; v0 = &D_800A2E20; store val to 0(a3); store v0 to D_800C7C64.

This looks like:
```
q = &D_800C7C60;       // v0
p = q;                  // a3
D_800C7C64 = &D_800A2E20;  // v0 (reused after q dies)
*p = val;               // sw
```
Wait, the sw is after the second lui/addiu in the listing: 121c lui v0, 1220 addiu v0, 1224 sw s2,0(a3), 1228 lui at, 122c sw v0. So order: q, p=q, r=&D_800A2E20, *p=val, D_800C7C64=r. But sched1 could reorder.

Hmm, so maybe the C is:
```
s32 *q = &D_800C7C60;
p = q;
D_800C7C64 = &D_800A2E20;
*p = val;
```
i.e. the D_800C7C64 store BEFORE *p = val! In the source, maybe:
```
p = q;
D_800C7C64 = &D_800A2E20;
*p = val;
```
Would that change the copy? No.

OK, let me try yet another angle: maybe make the store's value go through p differently. Actually, let me test a candidate where p is assigned the address through an *integer* variable that is genuinely computed, e.g.:

```
u32 q = (u32)&D_800C7C60;
p = (s32 *)(q + 0);
```
no.

Hmm, let me check: does cse1 even run before the tree-to-RTL? The `-O2`? What optimization level? Let me check the compile flags for this TU. If it's -O2, cse runs. 

Actually, maybe the answer is simpler: the target's q is a *hard register*? No.

Let me look at what `p` is used for: passed as the 4th arg to CdReadRequest. In target, at 1268 `move a2,s3` is mode (3rd arg). Where's p (4th arg)? It's a3 at 1264 jal. So a3 = p already set. Right.

Hmm OK. Let me try the approach of assigning p through a conditional/join so that cse must materialize:

```
if (cond) {
    q = &D_800C7C60;
} else {
    q = &D_800C7C60;
}
p = q;
```
jump1 merges identical arms. Then p=q copy... cse still folds.

What about:
```
q = &D_800C7C60;
if (x) { }
p = q;
```
Empty if gets deleted.

What if q is set inside a loop? no.

Hmm, what about using a `switch`? no.

OK, radically different idea: maybe the copy comes from `p` being a *narrow* pointer? No.

Let me look at the actual RTL of the target... we don't have target RTL. But maybe the project has a "matching body" for similar functions. Let me search the moves.md for "move a3,v0" or "copy" patterns... not helpful.

Alternatively, let me look at what the pin does here. The pin is `mode` in $19 (s3). Removing it swaps s3/s4. The launder creates the extra move. Both levers needed. Maybe the *pin* removal is what forces the launder removal and the swap. Let's separate: try keeping the launder but removing the pin, and vice versa, to see which residual each accounts for.

Let me test:
- G: pin removed, launder kept → score?
- H: pin kept, launder removed → score?

That tells me the independent effects.
