---
ts: 2026-11-06T08:59:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_raCWli3EMh9BKM5kpsgC
---
c2: score 22, 507 ins — the dead product is deleted. So flow removes it.

Now, the product must be used. What real use could exist without changing the target code?

Idea: use it as the value of `otz` *after* gte_stszotz? That would overwrite otz and change the code (the `if (otz > 0 ...)` uses otz).

Idea: use it in the `w` computation? `w = (u32)p & 0xFFFFFF;` — adding the product would change the tag.

Hmm.

Wait — maybe the target's dead product is the *result of an expression that gcc kept because it feeds a `mult` that is part of a `(set (reg) (mult))` with the HI/LO clobber*. Let me check flow.c in 2.7.2 for how dead sets are removed. If the deletion is `delete_dead_insns` in flow.c and it checks `insn_dead_p` which returns false for insns with `reg_mentioned_p (hard_frame_pointer)`... Hmm.

Actually, let me reconsider: in c2, the whole expression is removed by the *tree optimizer* or by `flow`? If it's removed by flow's dead-code pass, then any C-level dead assignment is removed. But maybe a *store to a variable whose address is taken* is kept.

Test: make the product's destination a variable whose address escapes: 
```c
s32 tt;
s32 *tp = &tt;   // address taken
...
tt = (a[2]-z)*buf[5];
```
Would flow keep the set because the address escaped? flow's dead-store elimination for a register set: if the register is dead and the set has no side effects, it deletes. Address-taken doesn't matter for a register.

But if the destination is a *stack slot* (because the address is taken), the assignment becomes a store to memory, which flow doesn't delete. But that store would appear in the target — it doesn't.

Hmm, what if the store goes to a stack slot that the target's frame... the target's frame is fixed (sp-56?). Adding a stack variable might change the frame size → score > 0.

OK so a real use is needed. Let me think about what the original programmer might have written that produces a dead multiply. 

The multiply is `(a[2] - z) * buf[5]`. `buf` is filled by `func_8017E410(mode1, buf)`. Maybe buf[5] is a scale. The original code might be:

```c
z2 = (a[2] - z) * buf[5] / something;
```
Hmm.

Or maybe the original code was:
```c
v[0].vy = v[1].vy = z;
v[2].vy = v[3].vy = *(u16 *)((s32)a + 0x8);
func_8017E410(mode1, buf);
...
```
What if the original had `v[0].vy = v[1].vy = (a[2]-z)*buf[5]`? No, the target's v[].vy stores are from z (s3).

Hold on. Let me look at the target's first block around the v[] setup and the call. Maybe the product's result is *stored* somewhere before the call and the target's mflo t1 is a leftover... no.

Alternative: maybe the value IS used, but by the GTE macro `gte_ldv3c(&v[0])` — the macro might load vectors from memory; no register use.

Hmm, what about `gte_rtpt()`? It's `cop2 0x0180001` — no GPR.

Let me look at the exact target region again with the source mapping. The 5 insns are at target[84-88] (before the lwc2 loads at 89+). Source-wise they're between `func_8017E410(mode1, buf)` and `gte_ldv3c(&v[0])`.

What if the original C computed `buf[5]` usage as part of a *store to buf*? e.g. `buf[5] = (a[2]-z)*buf[5];` — a store to buf[5] (stack). The target has no store. 

What if the original code was `v[0].vy = v[1].vy = z;` where z = ... hmm, the product uses z AFTER z -= 0x80. 

Actually, wait! Let me re-read the source order:
```c
v[0].vx = v[2].vx = *(u16 *)((s32)a + 0x10);
v[1].vx = v[3].vx = *(u16 *)((s32)a + 0x12);
v[0].vz = v[2].vz = *(u16 *)((s32)a + 0x14);
v[1].vz = v[3].vz = *(u16 *)((s32)a + 0x16);
z -= 0x80;
v[0].vy = v[1].vy = z;
v[2].vy = v[3].vy = *(u16 *)((s32)a + 0x8);
func_8017E410(mode1, buf);
asm((a[2] - z) * buf[5]);
```
The target's insns 84-88 (lw a[2]; lw buf[5]; subu; mult; mflo) come after the call. So (a[2]-z) uses the decremented z.

What if the original had:
```c
v[0].vy = v[1].vy = z;
v[2].vy = v[3].vy = *(u16 *)((s32)a + 0x8);
func_8017E410(mode1, buf);
p->something = (a[2] - z) * buf[5];
```
No store.

Hmm, maybe the original code used the product in a *condition* that the compiler folded because of a known value? E.g. `if ((a[2]-z)*buf[5] > 0x7FFFFFFF)`? no.

Let me look at the second loop for a similar computation to see if the decompiler used an asm there too. In the loop (3284-3344), after `func_8017E410(mode, buf);` there's no product. So the first block's product is special.

What if the product was originally used to *sort* the sprite (otz-based insertion)? The tag/ot code: `p->tag = (p->tag & 0xFF000000) | (*otp & 0xFFFFFF); *otp = (*otp & 0xFF000000) | w;` — the OT insertion uses otz as the index. Hmm.

Wait — maybe the product was used in `idx = otz; if (a[8]) idx -= 0x40;`? no.

Let me look at the ORIGINAL binary's *source-level* intent: the 5 insns produce t1 (dead). Could the original C have been:

```c
s32 depth = (a[2] - z) * buf[5];
...
if (depth > 0) { ... }
```
with the `if` optimized away because... no, a runtime condition can't be optimized away.

Unless the original had `if (depth)` where depth was known... no.

Hmm, is it possible the original was:
```c
v[2].vy = v[3].vy = (a[2] - z) * buf[5] >> something;
```
No: v[2].vy stores are `lh` from a+8? Let me check the target: at 1bd0-1bf0 we saw stores sh v0,26(sp) etc. Let me look at the v[] setup in the target.

Let me dump target insns 60-95 to map the v[] stores.
