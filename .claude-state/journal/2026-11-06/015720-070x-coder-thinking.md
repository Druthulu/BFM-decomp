---
ts: 2026-11-06T08:57:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_iNdu5OaTexwhfndUuZIq
---
Confirmed: `mflo t1` and t1 is never used. The target computes a dead product. flow normally deletes dead results, but the asm kept it (flow sees the asm as a use).

So the crack: real C that computes this dead product. The decompiler's own note in the source says the asm is a keepalive. How did the original binary get this dead computation? The original source must have used the product somewhere that the compiler later optimized away — but the product stayed! E.g., the original could be:

```c
z = ...;
func_8017E410(mode1, buf);
if ((a[2] - z) * buf[5]) { }   // ??? 
```
No.

Or the product was part of a store that was removed? Hmm.

The moves.md entries show `flow-unused-result` as a wall (target computes results that are never used; flow deletes). So this item is likely that wall. But maybe there's a real C form that keeps it.

Think: what real C computes `(a[2]-z)*buf[5]` and keeps the multiply but drops the use? If the result is stored to a *volatile*? no.

If the product is used in a *condition*: `if ((a[2]-z)*buf[5])` — that would add a branch. Target has no branch.

If the product is assigned to a variable used later — the target shows t1 unused, so no.

Unless the use was a *store to memory* that flow deleted? flow doesn't delete stores.

Hmm, but wait: maybe the target's mflo t1 IS the result of something else — e.g., the asm's operand computation. Since the asm is the current source, yes.

For the crack we need the exact same 5 insns. Options:
- The product's value feeds a call argument? The next call is gte_ldv3c (a macro, no call) and gte_rtpt (no call). The next real call in this block? None until func_8017E410 already happened.

Hmm, `func_8017E410(mode1, buf)` is called just before. The product uses buf[5] which was just filled by that call. In the target, the multiply happens right after the call and before the GTE loads.

What if the original source passed this product to something that got inlined? no.

Maybe the original source was:
```c
s32 t = (a[2] - z) * buf[5];
...
```
and `t` used in a place that the compiler optimized... but then flow would keep t's set if used.

Alternatively, maybe the original source had the product used in a *ternary* whose result feeds the GTE macro? e.g. gte_ldv3c takes an address.

Hmm, what does buf contain? `func_8017E410(mode, buf)` fills buf[0..5] — probably a matrix/params. The product (a[2]-z)*buf[5] — maybe a depth-related computation.

Look at the second loop: it also calls func_8017E410(mode, buf) but has NO such product. So the product appears only in the first block.

Since flow deletes unused results (the wall `flow-unused-result`), maybe this is a genuine WALL. But the shard's job is to try 20-30 min.

Let me think about C constructs where flow does NOT delete the result:
- flow deletes dead sets in `flow_analysis`? Actually it's `dce`/`flow` that removes dead code. A set to a *hard register* might not be deleted? Hmm.
- If the result is stored to a stack slot: `s32 t = ...;` where t's address is taken? no.
- If the result feeds a `__builtin`? no.

What if the product is computed as part of a **store to a dead stack slot**? e.g., `buf[5] = (a[2]-z)*buf[5];` — that's a store (target has no store).

What if the product's result is used in a *cast to void*? deleted.

What if the multiply is a side effect: `rand()`-like? no.

Hmm, what if the original expression was part of a **return value** that is dead? no.

Let me look at what the *decompiler* did: it inserted `__asm__ __volatile__ ("" :: "r"(expr))`. The expression has no side effects. The original binary has these 5 insns. So the original C must have had a real use that the current compiler would keep... but the decompiler couldn't find it, hence the asm. Unless the original used the result in a way that *changes* semantics (a store) — but the target has no store.

Wait — maybe the result IS used but the use was optimized into something else. Let me check t1's use: in MIPS, t1 is $9. Maybe later some instruction uses $9? grep showed no t1 in the target listing. So dead.

So the original binary has a dead multiply. This can happen in real C only if the compiler kept a dead computation — e.g., if the value was used in a `setjmp`-like context or if the compiler's DCE didn't catch it. In GCC 2.7.2, dead code elimination (flow) removes dead sets, but only within a basic block? flow's dead code elimination is per-block. Hmm, here the mflo is in the same block as the following code, so it'd be deleted.

But the original programmer's C compiled with gcc 2.7.2 produced these insns. So there must be a construct. What about a **volatile** read? The multiply's operands: a[2] (s2+8) and buf[5] (sp+68). If the product were assigned to a `volatile` variable, the store would remain (volatile store) — target has no store. If the *operands* were volatile, the loads would remain but the multiply... no, the multiply would be dead.

Hmm, wait: what if the multiply is not dead but feeds a *conditional branch* that was later optimized? No branch in target.

What if the product feeds an *asm-like* thing... that's the asm.

Alternatively — maybe the target's mflo t1 is actually used as the **GTE load data**? The GTE loads at 1c5x are `lwc2 $0,0(v0)` etc. from sp+16 (the v[] array). Not t1.

Hmm, hold on: maybe `t1` is $9 and the subsequent `addiu v0,sp,16` ... no use.

OK, so this looks like a genuine flow-unused-result wall: the target keeps a dead product; flow deletes it in lever-free C. Unless we can find a real C use.

Idea: use the product in a way that flow keeps because the destination is a *global* or memory. What if the original was:
```c
D_something = (a[2] - z) * buf[5];
```
then the store would be in the target. It's not.

Idea: the product feeds `gte_stszotz`? no.

Let me look at the moves.md entries for flow-unused-result to see if any were cracked:
- "keepalive | func_8017C730 | WALL flow-unused-result — target computes (s16)hmid into a0 that is never read; flow deletes the set and the hmid spill (frame -8): 99 on both includers (W05)"
- walls.txt: flow-unused-result — "flow deletes results the target computes but never uses (T10 S20, func_80188C04 family)".

Also "keepalive | func_80184D28 | MATCH — keepalive replaced by return v0" (W04) and "func_801810F8 MATCH: obase set right after pbase and used for the first load too".

For our case, the dead product has no natural use.

Hmm, but wait: maybe the product can be used *in place of something already in the code*. The expression is `(a[2] - z) * buf[5]`. Is `z` used later? Yes, z -= 0x80 after the stores. And `a[2]` is loaded again in the loop. buf[5] is used in the uv computations: `p->uv2 = ((buf[3] + buf[5]) << 8) | buf[2];` — buf[5] IS used later! And `a[2]` is used at `v[2].vy = ... = *(u16*)((s32)a + 0x8)` (a[2]). And z is used.

So the product `(a[2]-z)*buf[5]` is computed dead. But its operands are live.

Could we use the product as part of the uv computation? E.g., `p->uv2 = ((buf[3] + buf[5]) << 8) | buf[2];` — no.

Hmm, what if the original code was something like:
```c
p->uv2 = ((buf[3] + buf[5]) << 8) | (buf[2] + (a[2]-z)*buf[5]*0);
```
no.

What if the original code had the product as an *index* that was folded? e.g. `buf[(a[2]-z)*buf[5] * 0]`? folded.

Let me think about the *GTE* macros: gte_ldv3c(&v[0]) loads 3 vectors. Hmm.

What if the original had `gte_stotz` or something using the product? No.

Let me check the frame: buf is at sp+0x48? The lw v1,68(sp) = buf[5] at sp+0x44. In the source, buf is `u32 buf[6]` at sp+0x48? Earlier: `addiu v0,sp,72` = sp+0x48 = buf (the otz store? `gte_stszotz(&otz)` where otz is at sp+72=0x48). Hmm, so buf might be at sp+0x2C or so. Whatever.

Given the wall list explicitly includes `flow-unused-result` with exactly this mechanism, and the target keeps a dead result, this might be the intended wall. But the shard's list says the item kind is keepalive, and the brief says WALL is acceptable with evidence.

But before giving up, let me try a few real-C forms:

1. Store the product to a local that's never read but is *volatile*: `volatile s32 t = ...;` → store remains (not in target). No.
2. Use the product in a condition that folds: `if ((a[2]-z)*buf[5]) ;` → adds branch.
3. Assign to `otz`? otz is used (gte_stszotz(&otz) writes it). If we compute `otz = (a[2]-z)*buf[5];` before gte_stszotz, then gte_stszotz overwrites otz → the set is dead → flow deletes. But maybe flow doesn't delete because otz's address is taken (gte_stszotz(&otz) takes the address)! If a variable's address is taken, flow may keep the set because the store could be visible? Actually otz is a local whose address escapes to gte_stszotz (an asm-like macro or a function?). gte_stszotz is a macro using mfc2 and a store to *otz. If we assign otz before, the assignment is a stack store; flow might keep it if the address escapes. But target has no such store.

Hmm wait, maybe the target's `mflo t1` IS dead but flow can't delete it because... it's a hard-register set? mflo writes $9 (t1). If the C used a *hard register* variable... but no new levers allowed.

4. What if the product is used in an expression whose result is used: e.g. `v[0].vx = v[2].vx = ...` no.

Hmm, what about this: the target's multiply computes `(a[2]-z)*buf[5]` — maybe the original C was:
```c
p->tag = ... | ((a[2]-z)*buf[5] & 0xFFFFFF)?
```
No, the tag code is different.

Wait, let me reconsider: maybe the 5 insns are not dead in the original source; maybe they feed a value that the *current* decompiled body computes differently. Look at the target insns 84-88 and what follows:
```
84 lw v0,8(s2)
85 lw v1,68(sp)
86 subu v0,v0,s3
87 mult v0,v1
88 mflo t1
89 addiu v0,sp,16
90 lwc2 $0,0(v0)
...
```
Then the GTE ops. t1 = $9. Is $9 used by any GTE instruction? `lwc2 $0..$5` load the vectors. `gte_rtpt` (cop2 0x0180001) uses the loaded vectors. Then `gte_stsxy3(&p->x0,...)` → swc2. No t1.

So t1 is truly dead. Unless the GTE instruction `mult`/`mflo` is a *multiply* that the original source used for a *delay*? no.

Conclusion: it's a dead product. In GCC 2.7.2, how could a dead multiply survive? If the multiply result was used in a *branch that was deleted later*? For instance:

```c
if ((a[2]-z)*buf[5] > 0) {
    ... 
}
```
where the branch was folded... no.

OR the original C had the product as an argument to an *inline function* that gcc inlined and then DCE'd partially? GCC 2.7.2 doesn't inline (no -finline-functions at -O2? it does inline small functions with -O2? GCC 2.7.2 has -finline-functions enabled at -O2? I think -O2 enables -finline-functions in older GCCs. Hmm! If the original called a small static function that was inlined, the product could remain with the rest optimized.

But we must match with the current source's includes.

Alternatively, the original might have had `buf[5]` used in a context that got optimized to a multiply whose result is stored to a *dead stack slot that was later removed* — no.

Let me look at how other shards handled `flow-unused-result` walls. grep moves.md for flow-unused-result MATCH.
