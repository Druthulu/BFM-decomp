---
ts: 2026-11-06T05:43:09Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1Y4zrqr31MOTJIE7fSPX
---
22:43 — 19 min on item 2. Let me do one or two more and then record the WALL at 22:45.

dd2 = 14 (hoisted u16 copy).

Let me do one final try: the exact launder replacement via a real 2nd set that preserves value: `tmp = (s16)tmp;` after the copy (t1 = 18). Hmm.

What about a do-while around the *arms* (s1 failed to compile). Let me fix s1 and try it — a do-while around the arms might split blocks and change iVar1's liveness.

Let me construct s1 carefully by hand-editing.

n1 body:
```
    if (iVar2 != 0) {
        tmp = iVar2;
        if (iVar2 < 0) {
            tmp += 0x80;
            ...
        } else {
            tmp -= 0x80;
            ...
        }
        iVar1 = ((Unkstruct_800B5CB8 *)a0)->unk20;
    }
```
s1: wrap the whole body in do{}while(0):
```
    if (iVar2 != 0) {
        do {
        tmp = iVar2;
        if (iVar2 < 0) {
            ...
        } else {
            ...
        }
        } while (0);  // !FAKE: do-while
        iVar1 = ...
    }
```
Let me do this with python on the exact text.

Time is short; let me just do it and then write up.
