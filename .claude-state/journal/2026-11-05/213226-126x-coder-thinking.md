---
ts: 2026-11-06T04:32:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG20
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tVNCUWKVhkS42Hyej7pH
---
z1 = 27, 108 ins (count matches!) but score 27. Not better than 14.

Let me try z4: do-while around the obj->1C load + multiply to prevent the p load from filling the delay slot? The p load is after the do-while; if the do-while creates a block boundary, the p load can't move above it. But the obj->1C load is inside the do-while, so its delay slot is inside the block. Hmm, the p load is after the loop end. If sched treats the loop end as a boundary, the p load stays after. Let me try: wrap `v = *(s32*)(obj+0x1C)*3*32;` in do-while (w6 did that = 14). It didn't help.

Let me try wrapping the obj->1C load and the multiply AND the add in a do-while, with the p load outside (after). w6 wrapped only the multiply. Let me wrap lines 59-61 (mult, p, add)? No, p must be outside.

Try z2: wrap the multiply+add in do-while, p load after:
```
do { v = mult; v = v + 0x600; } while (0);
p = model;
```
Then the p load is after the loop. The chain is inside. sched of the loop body: the addiu's delay... The p load can't move above the loop boundary. But the obj->1C load's delay slot is inside the loop; the only insns inside are the chain. The p load is outside → the delay slot would be a nop (target!) or the sll. Let me test.

Build z2 from w4: wrap lines 59 and 61 (mult and add) in do-while, with p (line 60) moved after the loop. Let me write:
```
            do {
            v = *(s32 *)(obj + 0x1C) * 3 * 32;
            v = v + 0x600;
            } while (0);  // !FAKE: do-while
            p = ((Unkstruct_800B5CB8 *)a0)->unk20;
```
Skip lines 56-61 (comments, mult, p, add) and print this at 55? Wait line 55 is the store. Let me skip 56-61 and print the new body at 56.

Let me do it.
