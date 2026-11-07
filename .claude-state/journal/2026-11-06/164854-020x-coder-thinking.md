---
ts: 2026-11-06T23:48:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_u8s4k8nna6h3UC758Tfl
---
Target at 1210-1218:
```
lui v0, D_800C7C60
addiu v0,v0,0
move a3,v0
```
then 121c: lui v0, D_800A2E20; addiu v0; 1224: sw s2,0(a3); 1228: lui at D_800C7C64; 122c: sw v0,0(at).

So indeed q (D_800C7C60 address) in v0, then p (a3) = q. The launder created a new pseudo for q. Then `p = q`.

Note v0 is reused for D_800A2E20 too.

So I need a copy `p = q` where q is a fresh pseudo. Hmm.

Also note: the store uses s2 = val; and D_800C7C64 store uses v0. 

Now, mine (win.c) presumably:
```
lui a3, D_800C7C60
addiu a3,a3,0
lui v0, D_800A2E20 ...
sw s2,0(a3)
```
160 insns.

To create the extra copy without asm: we need `p = q` to survive as a separate register assignment.

What if p is assigned a value that isn't just q? E.g. `p = q;` where q is `volatile`? no.

Think about C-level: the frontend (cc1's `expand_expr` / `store_expr`) may copy through a temp if types differ. What if q is declared `u32 *` and p `s32 *`? Both SImode pointers; a conversion might still be a no-op copy... Actually in C, assigning `u32*` to `s32*` without cast is a warning but generates no code (same mode). The RTL would be `set (reg p) (reg q)` where q = address. Then cse1 could still merge.

The real difference with asm: the asm makes q have TWO sets (the address set and the asm set), so cse1 won't propagate the address into q's uses... Actually more precisely, with two sets cse can't treat q as equivalent to the constant address across the block.

But here's the thing: mine has q as a single-set pseudo, so cse replaces p's uses with q... wait, but then p and q become the same register and there'd be no copy. Then how does p end up in a3 and the address in a3?

In mine: `lui a3; addiu a3` then `sw s2,0(a3)`. So p=a3 directly holds the address. Fine.

Target: q=v0 (fresh pseudo, used once), p=a3.

So I need q to be a distinct pseudo with a real set that cse won't propagate. A real 2nd set of q. What if:

```
s32 *q = &D_800C7C60;
p = q;
*q = val;
q = p;      // real 2nd set, value-preserving but through p
```
Hmm, q=p after the store is dead. cse1: q set twice → the second set breaks equivalence. But would it affect the first `p = q`? cse1 processes insns in order. At `p = q`, it makes p≡q. Then uses of p get q. Then `*q = val` uses p→q. So p is eliminated, q keeps the address, and we get `lui/addiu` into q's reg (a3?) then sw. Hmm, so p wouldn't be a separate reg.

Wait, I need to think about which pseudo survives. In target, the asm output q_new is a fresh pseudo distinct from q_old. The address is computed into q_new (v0) and then `p = q_new` is a copy that combine keeps (p has 2 uses: store and call arg). So both regs exist.

Hmm, why doesn't combine merge p and q_new? Because p is used twice (store + call arg). Combine merges a copy into the *first* use if the copy's dest dies there; p doesn't die.

Wait, but if p is used twice, then why doesn't cse1 merge p≡q_new (making them one pseudo)? Because... hmm, cse1 does make_regs_eqv for copies. `p = q` is a copy, so cse1 would equate p and q_new, then the store and call arg both use the same reg. Then there'd be no copy in the output. But target HAS the copy. So cse1 did NOT equate them.

Why not? Because in the target RTL, `q_new = q_old` is not a plain copy — it's an asm insn. cse1 doesn't touch asm insns (they're volatile/barriers). The asm output q_new is a separate pseudo. Then `p = q_new` IS a copy, and cse1 would equate p and q_new... unless cse1 doesn't do that. Hmm.

Wait, but actually `p = q_new` — after the asm, cse1 sees `set (reg p) (reg q_new)`. make_regs_eqv(p, q_new). Then the store `set (mem (reg p))` becomes (mem q_new). Hmm, then the store address would be v0, not a3. But target has sw s2,0(a3). So they weren't merged.

Unless... combine (later) propagated and then the copy remained because of something. Ugh.

Actually, maybe cse1 only merges when one of the regs is *known equivalent to a constant/address*? Let me recall cse.c's make_regs_eqv: it's called from `cse_insn` when the source is a register and the destination is a register (a copy). It equates them only if... let me check the code around line 826-840 mentioned in the moves.
