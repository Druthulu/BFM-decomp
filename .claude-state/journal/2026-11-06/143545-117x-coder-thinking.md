---
ts: 2026-11-06T21:35:45Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4uHwfRbhbgyot0VQ3oqa
---
The .greg dump has many "Register dispositions" sections (after each pass?). Let me look at the final one (the last). Let me tail the .greg file and look at the disposition list.

Actually, let me just look at the final .s to confirm d=s1. The score diff already showed it.

Let me think about the allocation differently. In the target, d=s0 and s1ang=s1. The difference between the pinned orig and w3 is only the pin. With the pin, d is forced to $16 (s0), and s1ang naturally gets s1. Without, the allocator swaps.

To force d=s0 via real C, I can try to make d's allocno get a higher priority. The alloc table:
- r74 (pri 5185, refs 7, live 27) — this is likely d (many refs, long live, dies 3 places).
- r76 (pri 8333, refs 5, live 12) — likely s1ang? But s1ang has only 2-3 refs. Hmm.
- r77 (pri 10000, refs 5, live 10, prefers s0) — ?
- r78 (pri 30000, refs 10, live 10) — probably u5 or something used in a loop? No loops. refs 10?

Wait, the priorities: pri = refs * 10000 / live roughly. r78: refs 10, live 10 → 10000? But it says 30000. The formula is (refs*10000)/live with loop weighting. Hmm, 30000 = 10*10000/10 * 3? Maybe loop depth 3.

Hmm, there are no loops in the function. But the do-while(0) variants add loop depth. w3 has no do-whiles. So r78's 30000 is odd.

Wait, w3 is the version with both levers removed (no do-whiles). So no loops. r78 refs 10 live 10 pri 30000? That doesn't fit. Unless the priority formula includes something else. Let me not over-analyze.

Let me instead try practical moves:

Move A: swap the declaration order of d and s1ang.
Move B: declare d as the first variable, s1ang later.
Move C: use `s16 d` local? No.
Move D: change the cast position.
Move E: add a do-while around the *whole* body after the call.

Actually, let me look at the target's prologue order to see the expected allocation:
```
move v0,a0
sw s0,16(sp)
move s0,a1      # d = arg1 → s0
sw ra,24(sp)
sw s1,20(sp)
...
lh s1,18(v0)    # s1ang → s1
```
So d=s0, s1ang=s1.

In w3:
```
move v0,a0
move s1,a1      # d → s1
sw ra,24(sp)
sw s0,16(sp)
sw s1,20(sp)
...
lh s0,18(v0)    # s1ang → s0
```

So the swap is exactly d↔s1ang.

Which allocno is which? Let me find in the .greg dump. Let me grep for "lh" with s0/s1 or the insn patterns. Actually, let me look at the .lreg dump (local-alloc) which lists per-block registers. But d and s1ang cross the call, so they're global.

Let me read the .greg dump's final disposition section (the last one) to see the assignments. Let me tail the file.
