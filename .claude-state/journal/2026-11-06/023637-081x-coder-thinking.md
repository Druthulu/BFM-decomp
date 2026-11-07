---
ts: 2026-11-06T09:36:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG25x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_koi8dMF9teH3z7sHu9aY
---
Now I see the mechanism precisely:

In **orig** (with keepalive):
- insn 86: `(set (mem:HI (plus (reg/v 74) 392)) (const_int 0))` — store via s0 (reg 74).
- insn 88: the asm operands using reg 74.
- insn 99: `(set (reg:SI 4 a0) (reg/v:SI 74))` — the copy a0=s0, with REG_DEAD on 74.
- insn 91: load +68 via a0.

In **win** (keepalive removed):
- The copy `(set (reg:SI 4 a0) (reg/v:SI 74))` was *moved earlier* (before insn 86) — see the first lines: `(reg/v:SI 74)) ... REG_DEAD (reg/v:SI 74)` at the top of the window, which is the copy. Then insn 86 uses a0 for the store.

So it's local-alloc/copy-prop: the copy a0=s0 is placed before the store, and then the store's base (reg 74) is replaced by a0.

Actually more precisely: in win, the insn order is: [copy a0=74], insn 86 (store via a0), ... In orig: insn 86 (store via 74), asm, copy a0=74.

This is the "copy propagation" pass (regmove? or local-alloc's copy preference). The copy insn is `(set (reg 4 a0) (reg 74))`; local-alloc may propagate a0 into uses of 74 if 74 dies at the copy (REG_DEAD). In orig, 74 dies at insn 99 (the copy) too, but there's an asm use at 88 *between* the store and the copy — wait, in orig 74's uses: insn 86 (store), 88 (asm), 99 (copy). The copy is the last use (REG_DEAD at 99). Could local-alloc still propagate a0 into the store (insn 86)? It would have to move the copy before 86 and before the asm (88). Moving the copy before the asm would change the asm's operand? No, the asm uses 74 directly. Hmm, but then 74 would be dead after 88, and the copy a0=74 at 99 would read a dead value! That's why it can't: the asm at 88 uses 74 *after* the copy would be moved. So the asm anchors the copy after it.

In win, there's no asm; 74's uses are 86 and the copy; the copy can move before 86, and then 86 uses a0.

So the real C needs *some* use of s0 between the store and the copy, i.e., between the `*(u16*)(s0+0x188)=0` store and the call `func_801553C0(s0)`. The RMW `*(u32*)(s0+0x44) = *(u32*)(s0+0x44) & ~4;` is between them in source, but the compiler rewrote it to a0 (after moving the copy up). So the RMW does NOT anchor the copy — because the RMW's uses of 74 can also be rewritten to a0 (all uses after the copy).

The asm anchors because it *reads* 74 in a way that can't be rewritten (asm operands are fixed).

So: any real C use of s0 between the store and the copy that the compiler *cannot* rewrite to a0 would anchor the copy. But the compiler rewrites all normal uses. Hmm — unless the use is a *store through s0* with a different offset? Also rewritable.

Wait, but why can the compiler rewrite the RMW uses but not move the copy before the store? Let me think: local-alloc's copy propagation only rewrites uses *after* the copy insn. If the copy is before the store, the store can be rewritten. The decision of where to put the copy: sched1 or local-alloc.

In win, the copy was placed before the store. In orig, after the asm. So the anchor is the asm.

Real C: is there a genuine construct that anchors? A function call with s0 as an argument would force a copy at that point — but the RMW is before the call and its uses got rewritten to a0... 

Actually, maybe the real C had TWO calls or a use of s0 in a call argument before the RMW. No.

Hmm, what if the RMW's base were a *volatile* pointer? Then the compiler couldn't rewrite? Volatile isn't a lever per se (it's a real C qualifier), but the target's code doesn't show volatile semantics differences. Using volatile on the store would prevent optimization... Actually if we declare the RMW as volatile, the compiler must load/store in order; the base reg could still be a0 though. Hmm.

What if the store `*(u16*)(s0+0x188)=0` were written *after* the RMW in source? Then the copy could still move up. Tested (t3) = 2.

What if we introduce a genuine use of s0 *after* the call? No.

OK, what about this: the target's `move a0,s0` is at 38, between the store (37) and the load (39). If we write the RMW with an explicit *cast of s0 through a pointer variable* defined between the store and the RMW... e.g.:

```
*(u16 *)(s0 + 0x188) = 0;
{
    u32 *p = (u32 *)s0;      // genuine use of s0 here!
    *p = (*p & 0xFFFFFFFB) ... // no, p+0x44
}
```
The initialization `u32 *p = (u32*)s0;` is a real use of s0 at that point. If p is a pseudo assigned a0 (copy preference to the call arg? no), the copy a0=s0 might be born at p's definition — which is exactly where the target's copy is (after the store)! And then p's uses (the RMW) use a0. That matches: store via s0 (before p), copy at p's def, RMW via a0.

But wait: p = (u32*)s0 is a copy of s0. The compiler may coalesce p with s0 (no copy) unless p is tied to a0. In the target, the copy exists because of the call arg. With p defined after the store, the copy would be born there (sched1 might still hoist it above the store... but if p's definition is a real instruction (move a0,s0) that the scheduler could hoist...).

Hmm, sched1 could hoist the copy above the store since independent. But in the target it didn't. In the orig, the asm anchored it.

Let me just try: p = (u32 *)s0; use p for the RMW. And also a variant with p used for the store too.

Also try: `u32 v = *(u32 *)(s0 + 0x44);` between the store and the RMW (a real s0 use):
```
*(u16 *)(s0 + 0x188) = 0;
v = *(u32 *)(s0 + 0x44);       // real use of s0 after the store
*(u32 *)(s0 + 0x44) = v & 0xFFFFFFFB;
func_801553C0(s0);
```
Target's RMW: `lw v0,68(a0); and; sw 68(a0)` — the load uses a0. If we write the load via s0, would the compiler rewrite it to a0? It could. But the load is a real use of s0 at that point; if the copy is hoisted above it, the load uses a0 — same as target. And the store at 37 would then also use a0 (since the copy is above it) — that's the bug. Hmm, the copy position is what matters.

Let me just try several anchor ideas and score:
v1: `u32 *p = (u32 *)s0; *p = (*p & ~4)` — wait, p+0x44: `u32 *p = (u32 *)(s0 + 0x44); *p &= 0xFFFFFFFB;`
v2: `u32 *p = (u32 *)s0; p[0x11] &= 0xFFFFFFFB;`
v3: split load/store with v44 reuse? semantics risk.
v4: `s32 s0b = s0;` right after the store, then use s0b for the RMW: `*(u32*)(s0b+0x44) = ...` and the call uses s0b? Hmm, the target's copy is a0=s0 for the call. If we introduce s0b = s0 after the store and use s0b for the RMW and the call, the copy might be born at s0b's definition.
v5: `u32 *p = (u32 *)(s0 + 0x44); *p = *p & 0xFFFFFFFB;` with the pointer defined after the store.

Let me try.
