---
ts: 2026-10-22T00:13:03Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_kbKwvjGI4GZ3RkXrxotG
---
All 19. The allocation is stubbornly p→v0.

Note: all my candidates have 58 ins vs the target's 54 — 4 extra! So there's ANOTHER difference beyond the register swap. Let me look at the diff again:

```
  register pairs (mine -> target, count): v1->v0 x9, v0->v1 x6
  replace mine[0:2] target[0:2]
        0  lui	v0,0x0                         | lui	v1,0x0
        1  lw	v0,0(v0)                        | lw	v1,0(v1)
  replace mine[6:7] target[6:7]
        6  lw	v1,16(v0)                       | lw	v0,16(v1)
  ...
  replace mine[22:24] target[22:23]
       22  move	v1,v0                         | beqz	v0,56bc
       23  beqz	v1,56c0                       | --
```
So mine has EXTRA `move v1,v0` instructions (4 of them: at 22, 29, 36, 43)! These are the copies of the call result into v1 (because the value v1 is the local holding the value, and the call's result is in v0 → `move v1,v0`).

So mine has 4 extra moves (the call results copied into the local) — because the local `v0` is not v0 but v1! When the local IS v0 (the call's result reg), the call's result needs no copy.

So the swap causes the 4 extra moves. If the value were in v0, everything would match.

So this is ONE issue: the local assignment order.

OK. So the question remains: how to get the value pseudo into v0.

Given the priority hypothesis (verified by func_801415C0's c/d case where c had a higher priority and got the lower reg), I need the value's priority > the pointer's.

The pointer: refs 4, live 12 → 6666.
The value: refs 3, live 6 → 5000.

To get the value to 4 refs: the value's pseudo (the post-subtraction one) has set + 2 uses = 3. Adding a 4th ref...

**IDEA**: What if the value is used in the FIRST store and the SECOND store, AND the subtraction reads it — i.e., the pseudo that holds the FINAL value has 3 refs while the pseudo that holds the LOADED value has 2. What if I make the loaded value the one with more refs?

E.g.:
```c
v0 = ((Unkstruct_80126948 *)p)->unk10;   /* loaded value: set(1) */
v0 = v0 - 3;                              /* read(2) */
p->unk10 = v0;                            /* read(3) */
p->unk14 = v0;                            /* read(4) */
```
If gcc kept ONE pseudo for v0, its refs = 5. But gcc splits into 2 pseudos (the load result and the subtraction result). Hmm, why? Because `v0 = v0 - 3` creates a new value.

Hmm! What if I write it so that gcc does the subtraction IN PLACE on the loaded pseudo? That's what "in place" means — the asm shows `addiu v0,v0,-3` (in place). So the same pseudo! Then the pseudo's refs = 5.

But the table says 3. Hmm, maybe the table's "refs" for r77 is from the .lreg dump's "Register N references" line which might be a different count.

Hmm, so maybe the value pseudo has 5 refs and live 6 → pri = 2*5/6 = 16666 > 6666 → the value should get v0 FIRST. But it doesn't!

⇒ The order is NOT by priority here?! But in func_801415C0 it appeared to be.

Hmm, let me re-check func_801415C0: locals c (pri 4285) and d (pri 3000); c got $16, d got $17. But the SOURCE order is: d is assigned first (d = b + 0x2F) then c (c = a + 0x2F). So by pseudo number, d < c → d should get $16. But c got $16. So the order was by priority ✓ (c has the higher priority).

So for 80180480, the value (higher pri?) should get v0. But the pointer got v0. So the pointer's priority must be higher than the value's.

Pointer: refs 4, live 12 → 6666.
Value: refs 3?, live 6 → 5000.

So per the table, the value has 3 refs. Hmm, and "2 bytes" hmm.

Hmm, "2 bytes" — hold on! What if r77 is NOT the value but the `0x7FFF` constant or something? Hmm.

Hmm, let me reconsider: what if r77 (2 bytes, refs 3, live 6) is a HImode pseudo — the `(*(s16 *)&D_800B9AAC) = 0x7FFF;` store? That's in the if-branch: `sh v0, 0(at)` — the value 0x7FFF (2 bytes!) is stored. Its pseudo: set (the li) + use (the store) = 2 refs, live 2. Hmm, table says 3 refs, live 6.

Hmm.

OK, let me take the direct approach: let me find which pseudo got which reg by looking at the .lreg dump. Let me extract the lreg section for the function into a file and read it. It's worth it now.

Let me write a script to extract the .lreg section for a function into a file.
