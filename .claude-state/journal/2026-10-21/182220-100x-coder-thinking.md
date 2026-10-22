---
ts: 2026-10-22T00:22:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_FJcBKrUEteW6DTwOVSmz
---
A8 (u8 c6c): same 5. A7 (order): 10, 92 ins ✗.

Hmm. The residue in A2/A8: the q-0x48 load and the c6c load are in swapped registers ($2/$4) and the load ORDER differs.

In the target: `lw a0,-72(s0)` (q-0x48) then `lbu v0,108(s0)` (c6c) — so the q-0x48 load comes FIRST.
In mine: `lbu a0,108(s0)` (c6c) then `lw v0,-72(s0)` (q-0x48).

So in mine the source order is preserved (c6c's load first), and in the target the scheduler hoisted the q-0x48 load above the c6c load.

Hmm, in the source the q-0x48 load is LAST (in the `*(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);` statement) and the c6c load is earlier. The ROM hoisted the q-0x48 load to before the c6c load.

Why would sched1 hoist it? Because the load is independent and the block had a free slot? Hmm.

Hmm, since the source order in the ROM's compilation had them swapped, maybe the ROM's SOURCE had the q-0x48 load before the c6c load! I.e. the source might be:

```c
            func_8017869C((s32)p);
            *(s32 *)(q - 0x1C) = *(s32 *)(q - 0x50);
            *(s32 *)(q - 0x14) = *(s32 *)(q - 0x48);     ← hmm, but then the store order changes
            c6c = *(u8 *)(q + 0x6C);
            *(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C);
            tbl = D_8011DB08;
```
I tried that (A7) → 10, 92 ins ✗ (the store order changed the code).

Hmm. What if only the LOADS are reordered but not the stores? I.e. use a temp:
```c
            t = *(s32 *)(q - 0x48);       /* the load first */
            c6c = *(u8 *)(q + 0x6C);
            ...
            *(s32 *)(q - 0x14) = t;        /* the store later */
```
→ the temp `t` would be a user variable (low allocno) → it might get $2 ✓ and c6c $3? Hmm, but the ROM has the q-0x48 value in $4 (a0) and c6c in $2.

Hmm, so in the ROM: the q-0x48 value → $4, c6c → $2.

With a temp `t` (declared after c6c?), the allocation might give t → $2 ✗.

Hmm. What if the temp is declared BEFORE c6c? Then c6c gets $2 ✓ and t gets $3/$4 ✓!

Let me try:
```c
            s32 t;                /* declared first */
            s32 c6c;
            ...
            t = *(s32 *)(q - 0x48);
            c6c = *(u8 *)(q + 0x6C);
            *(s32 *)(q - 0x18) = *(s32 *)(q - 0x4C);
            tbl = D_8011DB08;
            *(s32 *)(q - 0x14) = t;
```
Hmm, but then the store `*(s32 *)(q - 0x14) = t;` uses the temp → gcc emits `sw t,-20(s0)` ✓ (the same instruction as the ROM's `sw a0,-20(s0)`) ✓ and the load `lw t,-72(s0)` ✓.

Hmm, but the ORDER of the load and the c6c load: mine would be t's load first ✓ (the source order) ✓ matching the ROM ✓✓.

And the registers: t (declared first) → $2? ✗ (the ROM has t in $4 and c6c in $2). Hmm. But maybe with the priorities, c6c wins $2 (it's tested immediately).

Let me try both variants (t declared first / t declared after c6c) on the A2 base (q+tbl pins kept).

Let me write them.
