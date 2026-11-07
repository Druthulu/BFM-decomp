---
ts: 2026-11-06T23:48:27Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_4JY9JfnTJmnEi03DPTkV
---
Interesting! Target: base is s4, mode is s3. `li s3,-1` at 10ec is in the branch delay slot of `beq v0,v1`. And `move s3,zero` at 10f4.

Wait, this is important: `li s3,-1` (mode = -1) is in the *delay slot* of the beq. So mode is set before the branch. Note: in the C, `mode = -1;` is before the `if (st != ...)`.

Also note at 10ec: `li s3,-1` — s3 = mode.

Now let's see mine (win.c). I need my own disassembly. I can use --keep to get the object. Let me do that: delever_search --try ... --keep prints the candidate object path. Let me run it.

Actually, maybe better to just think about the C.

The target is 161 insns, mine 160. The difference is the `move a3,v0`.

Where's the a3/v0? Let me find it in the target listing. Let me print more.
