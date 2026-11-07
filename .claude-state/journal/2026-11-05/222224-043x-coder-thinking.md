---
ts: 2026-11-06T05:22:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_N3I3WhOMywfmKrnCgYd0
---
v3's asm:
```
4d8 lbu v0,36(s1)     ← mine: v0, target v1
4e0 addiu v0,v0,-16   ← mine: v0,v0; target v0,v1
4e8 move v1,v0        ✓
4fc move v0,v1        ✓
```
So the copies are right; only the load destination register differs. raw at the lbu is v0 in mine. But raw is later v1 (the move v1,v0 writes v1). Hmm, interesting: raw is one pseudo? raw = lbu (v0), then raw = t (move v1,v0 → so raw is v1 there!). Wait, that means raw's live range got split: the lbu result is one pseudo (in v0) and raw is another (v1) after the copy. Actually the `raw = t` copy makes raw a new value; the RTL would be: load → reg A; t = A - 16; raw = t; ... So reg A is the load result, and raw is a different pseudo assigned v1. In the target, the load result A is v1 and the addiu dest t is v0.

Mine: A in v0, t in v0 (they coalesce! addiu v0,v0). Target: A in v1, t in v0.

So we need the load result A and t in different registers: A=v1, t=v0. A dies at the addiu; t born at addiu. They can share v0 — that's what mine does. In the target, A is v1 because... the pinned raw forced the zero-extend into v1, and then the addiu reads v1.

How to get A into v1? local-alloc assigns $2 (v0) to the pseudo with highest priority in the block. Both A and t are candidates. t is used by the branch and the stores; A is used once. So t gets v0, and A should get... v1! But mine gave A v0 too because they don't conflict (A dies at the addiu, t born at the addiu — actually they can share).

Hmm, local-alloc assigns registers per "qty"; A and t can share a qty if their live ranges don't overlap. The addiu is `t = A - 16`: A is dead at the addiu (last use), t is born at the addiu. In local-alloc, the qty for A dies at the addiu and t is born at it — they can share.

To force A into v1, we could make A live a bit longer or make t born earlier... Actually what if we keep `raw` as the load destination and *don't* copy: 

Hmm. What if the addiu is written as `t = raw - 0x10` where raw remains live after? Then raw (A) is live past the addiu → conflicts with t → different registers. And then raw = t later. That's the original n1 shape, where A and raw were merged.

Wait, in v3 the source is `raw = *(u8*)...; t = raw - 0x10; raw = t; ...`. Here `raw` is reassigned, so the RTL might have raw as one pseudo (v1 after the copy) and the load result as another (A). Hmm.

What if we avoid the extra pseudo: `t = *(u8*)(s1+0x24) - 0x10;` directly, then `raw = t; if...; t = raw;` — then A = load result, t = A - 16. A dies at addiu, t born → can share v0. Same problem.

What we need: A in v1 while t is v0. That means A must NOT be coalescable with t. A is the addiu's source, t is the dest. In local-alloc, the addiu `t = A + const`: A's qty dies at this insn; t's qty starts. They can share a register only if... hmm, actually in local-alloc, qty sharing happens when live ranges don't overlap. A's death and t's birth at the same insn: gcc's local-alloc uses the insn's luid; a register dies AT the insn and another is born AT the insn — they can share.

But in the target, they don't. Why? Because the pinned raw made the addiu's source a hard reg (v1) and the dest pinned v0. Lever-free, gcc merges.

So: can plain C make A and t different? If the addiu's source value is used again later (live past the addiu), it can't share with t. In v3, is the load result A used again? No, raw is reassigned from t.

What if the source is:
```c
t = raw - 0x10;
```
where raw is the loaded value and raw is NOT reassigned before the branch. Then A (=raw) is live? raw's last use is the addiu → dead. So no.

What if raw is used after the branch too, e.g.:
```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
raw = t;    // reassign
```
raw is one pseudo? The RTL for the assignment `raw = t` reuses the same pseudo (raw). So raw's live range: from lbu to... the lbu defines raw, the addiu uses it, then `raw = t` redefines it. Local-alloc can split: the qty for raw (first def) dies at addiu. So it can share with t.

Hmm, but in v3, mine put the *load* in v0 (shared with t) and raw (after copy) in v1. Target: load in v1, raw (after copy) in v1 (same reg), t in v0.

So in the target, the load result and the post-copy raw are the SAME register v1. That's because the pinned raw is a single hard reg.

In v3 mine, the load result went to v0 (merged with t) and raw to v1. The difference is just which pseudo gets v0.

Can we make the load result avoid v0? If the load result's live range overlapped t's... They don't.

Idea: make the load result used *after* the addiu, so it conflicts with t and gets v1. For example, use the loaded byte in a second computation that doesn't add instructions. Hmm.

What if the source is:
```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
raw = t;
if (t < 0) { ... }
t = raw;
```
The load result raw is used only at the addiu. What if we write `t = raw - 0x10` and also use `raw` in a comparison, e.g., the branch tests `raw`:
```c
if (raw < 0x10) { call; return; }
```
Then the compare uses raw (live past addiu), and t = raw - 16. But the compare instruction: target has bgez v0 (t). If we compare raw, gcc emits `slti` or `bge`. Actually `if (raw < 0x10)` where raw is u8 → `sltiu v0,raw,16` then bnez. That's 2 insns vs target's bgez. Not matching.

Hmm, but we could compare `t` while keeping raw alive elsewhere... 

What about: `if (t < 0)` uses t; raw is dead. 

Alternative: use the loaded value in the *store*? The stores store t.

Hmm. What if the load is written as a separate variable that is used twice: e.g.
```c
u8 b = *(u8*)(s1+0x24);
t = b - 0x10;
raw = t;
if (t < 0) ...
t = raw;
```
b dies at addiu.

OK, what about making the *addiu* not merge with the load by using a different expression: `t = raw - 0x10;` vs `t = (s32)raw - 0x10;`. Same.

Alternatively, can we get the target by making t NOT coalesce with A? If t's live range started before the addiu... no.

Hmm, wait. Actually, maybe the answer is in the *order*: if the load result A is live across a call... no.

Let me look at what determines the qty order. In local-alloc, the qty priority: pseudos with more references and longer live ranges get priority. Both A and t are in the entry block. t is referenced by the branch, the stores (via subregs), and the move. A is referenced once. So t wins v0. Then A should get v1 (the next free reg). But mine gave A v0 — because A and t share a qty (their live ranges don't overlap). So it's not a priority question: they share.

To prevent sharing, A must be live when t is live. A is live from lbu to addiu. t from addiu onward. If the addiu is the same instruction, A dies there. If we could make A live one insn longer... e.g., if the addiu is `t = raw - 0x10` and then `raw = t` — A (raw's first def) is dead at addiu.

What if we restructure: `t = raw - 0x10;` and then use `raw` in `raw = t` — no, that's a def.

Hmm what about: `raw = *(u8*)(s1+0x24); t = raw - 0x10; if (raw < 0x10) ...` no.

Alternatively, maybe use a *different* intermediate: 
```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
raw = t;
```
What if instead:
```c
t = *(u8*)(s1+0x24);
raw = t - 0x10;
t = raw;   // hmm
```
No, the addiu dest would be raw.

Hold on. Let me reconsider: in the target, the addiu is `addiu v0,v1,-16`: dest v0 (t), source v1 (raw). In mine (v3): `addiu v0,v0,-16`. The difference is only the source register. Since A dies at the addiu, sharing is allowed. GCC 2.7.2's local-alloc: does it allow a register to be reused at the same insn for a dying source and a born dest? Yes (it's the standard `addiu v0,v0,-16` idiom).

To break it, the source must be live after. Since the source value (the loaded byte) isn't used after, we need it to be. Could we make the *second* copy read the original raw? No.

What if we make the branch condition use raw instead of t but in a form that still emits bgez v0? E.g., `if (raw < 0x10)`. For u8 raw, gcc emits `sltiu`+`bnez`... unless raw is s32: `if (raw < 0x10)` → `slti v0,raw,0x10; bnez`. Not bgez.

Hmm, but what if the compare is `if (raw - 0x10 < 0)` and t = raw - 0x10 is also used? gcc would CSE the subtraction: one addiu into t, compare t. Then raw is dead at the addiu again.

What if the compare happens BEFORE the subtraction:
```c
raw = *(u8*)(s1+0x24);
if (raw < 0x10) { call; return; }
t = raw - 0x10;
raw = t;
t = raw;
```
Then the compare uses raw (live past... well, raw is live until `raw = t`). And the addiu comes after. But the compare form differs (slti+bnez vs bgez).

Hmm. What if we compare `t` but t is computed from raw before:
```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) {...}
```
raw dead at addiu.

Unless raw is used in the *return* path? e.g. `func_80146CA0((s32*)arg0)` — could we pass raw? No, the target passes arg0.

Hmm, what if the load result is used to compute BOTH t and something else that folds away? Like `raw = *(u8*)...; t = raw - 0x10;` — if raw were also stored... no.

Alternative approach: don't fight the load register; instead check whether the *target* could be matched with the load in v0 if the copy were different. But the target's bytes are fixed: lbu v1, addiu v0,v1. We must match.

OK here's another thought: what if `raw` is the variable that receives the load AND is the one used in the addiu, and it's live across the branch because we DON'T reassign it before the branch:

```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
if (t < 0) { ... return; }
raw = t;
t = raw;
```
Here raw is live from lbu to the addiu only (dead after addiu until redefined). Same as before. The reassignment is after the branch. Hmm, in v3 the reassignment was before the branch, which made raw live across the branch (from the reassignment to `t = raw`). That gave the moves.

In v3, the load result A dies at the addiu. What if we make the load result the SAME pseudo as the post-branch raw? I.e., don't reassign raw, but make raw = t a separate variable. Hmm.

What if:
```c
raw = *(u8*)(s1+0x24);
t = raw - 0x10;
raw = t;     // raw redefined; in RTL this is the same pseudo raw (set twice)
if (t < 0) {...}
t = raw;
```
RTL: raw (def 1 = lbu), t = raw - 16, raw (def 2 = t), branch, t = raw.
Local-alloc can split raw into two live ranges: [lbu, addiu] and [copy, t=raw]. The first range dies at addiu; the second starts at the copy. Both can share a register? They're the same pseudo; local-alloc splits into qtys. The first qty can share v0 with t. The second qty (raw after copy) needs a different reg than t (both live from the copy to `t = raw`)... 

In mine, raw's second qty = v1 and the load result = v0. Target wants the load result = v1 (same as raw's second qty!). Hmm, can we force raw's two qtys into the same register? If raw's first qty (load) and second qty (copy) got the same reg v1, then t (v0) is the only one in v0, and the addiu would be v0,v1. That's the target!

How to make raw's first qty prefer v1? Copy preferences: the second qty gets v1 because of the copy `raw = t`? Hmm, actually the copy `raw = t` has a preference for t's reg (v0) but conflicts with t's live range after → so it takes v1.

The first qty (load) has no preference. It got v0 because v0 was free at that point (t not yet live... wait, t is live from the addiu). Hmm.

If we could give the load qty a preference for v1... e.g., if the load result were copied to/from something in v1. 

What if we write:
```c
t = raw - 0x10;
```
where raw's first def is the load — no preference.

What if we do `raw = *(u8*)...; raw = raw;`? no.

Hmm, what about the ordering of the statements: `p = *(void**)(arg0+0x4C);` is loaded at 4dc (between lbu and addiu). p is a different pseudo.

Let me look at local-alloc's qty assignment more concretely. Actually, maybe simpler: try declaring things in different orders or adding a second use of raw that doesn't add instructions.

IDEA: what if raw is used in the `if` condition instead of t, but written as `if (t < 0)` where t = raw - 0x10... no.

IDEA 2: What if the *load* is assigned to `t` first and raw gets the subtract:
```c
t = *(u8*)(s1+0x24);
raw = t - 0x10;
if (raw < 0) ...
```
But target's bgez is on v0 and the stores use v0=t. Hmm, in the target t is the result of the subtract (v0) and raw is the byte (v1). So raw is the byte.

IDEA 3: Add a use of raw after the addiu that folds into an existing instruction. For example, `raw = t` could be written as `raw = raw - 0x10 + 0x10;`? That's two insns.

Hmm, what about making the addiu's source be a *sign-extended* raw so the value in v1 is a different pseudo... no.

Let me look at v3's RTL to see the exact pseudo structure, then think about the qty.

Actually, maybe there's a much simpler knob: the ORDER of the statements `raw = *(u8*)(s1+0x24);` and `p = *(void**)(arg0+0x4C);`. Or declaring `raw` before `p`. Hmm.

Or: what if we swap the roles so the byte load goes to v1 naturally because v0 is occupied at that point? E.g., if `t`'s value is computed before the load? Can't — t depends on raw.

What if p's load takes v0? Then the byte load might take v1. p = *(void**)(arg0+0x4C) is loaded at 4dc in the target, in a0. In mine also a0. Hmm.

Let me look at v3's RTL and local-alloc dump to understand. Let me dump v3.

Actually — a cheaper experiment: try swapping the two load statements' order, try declaring p before/after, try making raw `u8` in v3 (width change might alter qty priority), and try the do-while on the first copy.

Let me batch:
w1: v3 + raw as u8
w2: v3 with p load before raw load (statement order) — in orig p load is second.
w3: v3 with `t = (s32)raw - 0x10`
w4: v3 with `raw = t;` inside do-while
w5: v3 but `raw = *(u8 *)((u8 *)s1 + 0x24);` moved after p load (already is)
w6: v3 with t declared u16? no.

Also: what if raw's second assignment is `raw = (u8)t;`? That's a QI truncation — might give a different qty.

Let me try these.
