---
ts: 2026-11-06T12:04:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG30
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BzQFe4pLUyPZ2FSaZ52k
---
Not better.

Let me look at the target more closely around the start to see the exact sequence. Maybe the address materialization is really about `va` being computed before `f.cy = arg2`.

Target (from the p2 diff):
```
18: addiu a1,sp,16   (va)
19-20: (something)
21: move a2,a1       (vb)
```
Mine:
```
18: addiu v0,sp,16
20: move a2,v0
25: move a1,v0
```

So target: va=a1, vb=a2=a1. Mine: va=v0, vb=a2=v0, then a1=v0 at the call.

The call's a1 argument: mine copies at the call; target already has a1.

Why? Local-alloc: the pseudo va is used at the call as a1. If va's pseudo is allocated to a1, no copy. Mine allocated va to v0 and copied — because a1 was taken? a1 might be used by something else in between.

What real-C move changes this? Making va's live range shorter or longer? Or eliminating the other a1 uses.

Hmm, what does a1 hold between? In mine, a1 = something else (the `c` values? the vec stores?). 

This is deep. Time: item 4 ~15 min. Tries so far: v0, p1, p2 (3), 5, 2 = 10. Need 30 for a WALL, or find a MATCH/PARTIAL.

Hmm, let me reconsider the lever-free v0 (18, 159 ins): the diff showed a big prologue reorder (s2/lui/li) and the same address issue.

Let me try more structural variants for the lever-free body (v0), e.g.:
- `u8 *va, *vb;` decl order
- move the `va = (u8*)&f.cx` to the call site
- use `&f.cx` directly in the call

And for p2, try:
- va/vb declared as `void *`
- `va = (u8 *)&f.cx; vb = va;` without f.cy between (d=7)
- reorder the f.cx/f.cy assignments.

Actually, let me look at the whole target function to understand the structure and see if there's a natural C shape. Let me dump it.
