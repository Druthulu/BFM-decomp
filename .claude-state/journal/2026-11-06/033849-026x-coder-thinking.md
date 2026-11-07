---
ts: 2026-11-06T10:38:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XWv2lcAsfufDQMtyNnt9
---
Target: `move s0,a0` in the jal delay slot (after `jal func_8012C1B8`). Interesting: the move is placed in the delay slot of the first call.

So the C has `s0 = a0` before the call; the compiler (reorg) put the copy into the call's delay slot. In mine (nopin), the copy is `move s1,a0` before, and then `move s0,s1` after the jal. So there are two copies in mine.

The reason for the second copy: hmm. Since the target has a *pinned* s0 ($16), the copy is `move s0,a0` (hard reg). Without a pin, the local pseudo should get $s0 or $s1. But we see two moves.

Let me look at the first-call delay slot in mine: `ed4: jal`; `ed8: sw s0,16(sp)` — wait, in mine the delay slot after jal is `sw s0,16(sp)`?? Look at the mine listing:
```
ec4 addiu sp,-32
ec8 sw s1,20(sp)
ecc move s1,a0
ed0 sw ra,24(sp)
ed4 jal
ed8 sw s0,16(sp)     <- delay slot
edc move s0,s1
ee0 bnez v0
```
So the save of s0 was moved into the delay slot, and the copy `move s0,s1` after.

Two pseudos: P1 (s1) = a0, P2 (s0) = P1. P2 is used later. Where does P2 come from? 

OH! I think I get it: `s0` is a local variable, and `s0 = a0` assigns the *parameter* to it. But maybe gcc's flow: the local `s0` is a REG (global allocno), assigned $s0. The parameter a0 pseudo assigned $s1 (because $s0 taken by the local). Then the copy local = a0 becomes `move s0,s1`? But that would be `move s0,s1` only, no `move s1,a0`. Unless the parameter itself was first copied... 

The `move s1,a0` must be a copy from hard reg a0 to the parameter's allocno $s1 (a hard-reg copy is emitted when the pseudo gets a different reg than the incoming arg). Then `move s0,s1` is the C copy. And the early uses `sw v0,32(s1)` and `move a0,s1` use the *parameter* pseudo (s1), not the local! That means gcc's copy propagation replaced uses of the local with the parameter? No — uses of s0 before the copy... 

Wait: `((Unkstruct*)s0)->unk20 = v0;` comes BEFORE the if. In the C, s0 = a0 at the top, then this store. If gcc keeps s0 as a copy and the store uses the parameter pseudo (s1), that's copy propagation (canonicalizing uses of the copy to the source). Then `func_8012CAE4(s0)` also uses s1. But later uses (in the else branch) use s0 (the local). Hmm, copy propagation would be consistent.

Actually here's a cleaner explanation: global-alloc's copy coalescing created a tie between the parameter and the local for the early block, but the local also has uses in another block where it needed $s0... no.

Let me step back and try practical variants. Cheap. Try:

(a) init at declaration: `void *s0 = a0;`
(b) use `s32 s0` instead of `void *s0` (the target treats it as an address; orig used void*).
(c) declare the local AFTER the externs but same.
(d) Instead of a local copy, cast the parameter: keep `a0` as the pointer but ensure it's saved: e.g., `void *s0; s0 = a0;` is what we have.

Also consider: maybe use `void *s0 = a0;` with `s0` used only in the else branch? The if branch call `func_8012CAE4(s0)` — if we pass `a0` there instead (a0 is still live? no, clobbered by the call func_8012C1B8). Hmm.

Actually wait. What if we avoid the local entirely and let the *parameter* be the saved value by using a struct pointer parameter? Can't change signature.

Let me try the variant where the first store uses `a0` cast to the struct pointer? a0 is the parameter; after the call it's dead. Hmm, but the store happens after the call, so a0 is clobbered. Must use the saved copy.

Let me just try a handful of variants and score them. I'll write a small script to generate variants? Better: create files with the Write tool for clarity, but that's many. Let me use a Python generator script under the item dir that emits variants, then sc.sh them all. That's efficient.

Variants for the s0 double-copy:
1. `void *s0 = a0;`
2. `s32 s0 = (s32)a0;` and use `(Unkstruct_800B5CB8 *)s0` everywhere (already casts), `*(s32 *)(s0 + 0x20)`.
3. `void *s0; s0 = a0;` but with the store moved after the if? no.
4. Use two locals? no.

Also maybe the issue is that `v0` local is initialized from the call and used; the register pressure... 

Let me also test: does the double copy disappear if we remove the `s32 v0;` local and use the call result directly? `((Unkstruct*)s0)->unk20 = func_8012C1B8();` then `if (...)`. Hmm.

Let me generate variants. But first let me understand what "s1->s0 x2" means: 2 register-pair mismatches.

Time budget: 20-30 min per item. I'm ~10 min in. Let me be efficient.

Let me write a variant generator for this item with several spellings, then score all at once with sc.sh.

Variant set:
A. init-at-decl.
B. `s32 s0 = (s32)a0;` uses `(Unkstruct*)(s0)` and `s0 + 0x20`, `func_8012A828(s0, ...)`.
C. keep `void *s0;` but move `s0 = a0;` to after the extern decls (already) — skip.
D. no local: `#define`? no.
E. use the parameter name directly in the first store by assigning s0 after? Not valid.

Hmm, wait. What about the possibility that the second copy is the *result of the barrier's presence*? In nopin the barrier is still there. win0 also had 66. nobar (pins kept, no barrier) = 63. So the barrier is not it.

Let me check: maybe the double copy comes from `s32 v0;` being a local named v0, which gcc treats as... no, it's just a name.

Hmm! Actually here's a real possibility: `void *s0;` — the name `s0` is a *fixed register name* in the gcc backend? In gcc 2.7.2 MIPS, `$16` is s0. But a C identifier `s0` isn't special.

Wait, but there's `register void *s0 __asm__("$16")` in orig. My sed replaced the declaration line. But maybe there are other references to `s0` as a *register* elsewhere... no.

Let me look at the actual behavior: could the second move be due to the *type* of the parameter? `void *a0` and the cast `(Unkstruct_800B5CB8 *)s0`. Both pointer types.

Try variant: declare the local as `Unkstruct_800B5CB8 *s0;` and assign `s0 = (Unkstruct_800B5CB8 *)a0;`, then use s0 directly (no casts) — this is a classic "field-direct" move from the cookbook (W02: field-direct &= and -- on s0->unkAC). That changes many expressions though. The target code accesses via s0 offsets; using a typed pointer would produce the same offsets. And `*(s32*)((s32)s0+0x20)` becomes... hmm, unk20 is a member of the struct.

Let me look at Unkstruct_800B5CB8 definition to know the members. It's probably in include/ or the TU.
