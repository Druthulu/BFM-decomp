---
ts: 2026-10-22T21:52:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_8EpGeOpWPH91hODbbwj8
---
Now I see: without the launder, `q = &sp18` is held in s0 (`addiu s0,sp,24`, `move a2,s0`, `move a0,s0`) — the address used twice in one ebb → cse merges → held across the call (C0164 class again!). The launder gave the per-site rematerialisation `addiu a2,sp,24` / `addiu a0,sp,24`.

So this is exactly the C0164 address-hoist class. The fix I found for items 2/3: the dead-reset. Here q is used at call2 (a2) and call3 (a0). So:

```
void *q = &sp18;
call2(..., q);
q = 0;              // dead reset
q = &sp18;          // fresh
call3(q, arg1);
```
Hmm, but the target's shape:
```
11  addiu a2,sp,24     (call2's 3rd arg)
12  jal call2
13  addiu a0,a0,52    (delay)
14  addiu a0,sp,24     (call3's 1st arg, rematerialised)
15  jal call3
16  move a1,s1        (delay: arg1)
```
Wait, target has `addiu a1,sp,16` twice (8 and 9)? Yes: index 8 `addiu a1,sp,16` and index 9 `addiu a1,sp,16`. Hmm — mine has those too (8,9). Interesting: two identical addiu a1,sp,16. OK.

So the target: a2 = sp+24 before call2, a0 = sp+24 before call3 (both fresh), no s-reg for q.

Try the dead-reset:
```
    {
        void *q = &sp18;
        call2(..., q);
        q = 0;
        q = &sp18;      // hmm, this is an identity re-spelling
        call3(q, arg1);
    }
```
Better mirror of items 2/3: use a 2nd variable:
```
void *q = &sp18;
void *q2;
...
call2(..., q);
q = 0;              // dead reset
q2 = &sp18;
call3(q2, arg1);
```
The dead reset `q = 0` empties the class, then q2 = &sp18 is a fresh computation at call3. Let me test.

But wait: is `q = 0;` a "dead store"? It's plain C; used in items 2/3 as the crack. Fine.

Alternatively simpler: 
```
call2(..., &sp18);   // hmm, direct
```
Let me test the q2 variant.
