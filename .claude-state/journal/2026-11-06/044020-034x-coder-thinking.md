---
ts: 2026-11-06T11:40:20Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_wuSSahJ3aRkDqmPbxBaC
---
Line 320 is the key: `barrier,pin | func_80187EA0 | MATCH — n as s16 (outer cross-jump copy survives) + empty do-while after the loop call (reorg fills beqz slot from target) + D_801151D0 1-field struct alias (MEM_IN_STRUCT store not hoisted) (G28x)`.

That's EXACTLY my function family! func_80187EA0 is a sibling (probably the same SC03 HUD cluster). The moves: n as s16, empty do-while after the loop call, D_801151D0 1-field struct. So the empty do-while is placed AFTER the loop call (not around it). Let me parse: "empty do-while after the loop call (reorg fills beqz slot from target)".

So the structure is:
```
if (h != 0) {
    ot = call(...);
    do { } while (0);   // empty do-while AFTER the call
}
```
Hmm, "empty do-while after the loop call". So the do-while(0) is empty and placed after the call, at the END of the if-body. How does that stop the fall-through scan? The scan starts at the branch's next insn (move a0,s0), goes through the call, move s0, then hits the empty do-while's... the do-while creates a label/note after the call. If the empty do-while emits a CODE_LABEL at its position (after the call), then the scan from move a0,s0 would pass move a0,s0 (eligible) and steal it before reaching the label. Unless the empty do-while ALSO emits something at the head? 

Wait — "empty do-while after the loop call". Maybe the do-while(0) is placed such that its loop structure causes the i++ to be reordered? Or the empty do-while's loop label is at the head of the if-body somehow?

Actually, maybe the empty `do { } while (0);` after the call is optimized into a label+note that lands... Hmm. Let me look at the actual winning body for func_80187EA0! It's in another shard's dir. The brief says "moves that cracked/walls in other shards" are in moves.md, and I can look at worked examples. But I'm restricted to write only under my shard; reading another shard's win.c? The brief POINTERS say worked examples at .run/P40/T10/func_80181F4C/. It doesn't forbid reading other .run files. But the constraint says "write only under .run/P40/T11/G28y/ plus appends to moves.md". Reading is allowed. Let me find func_80187EA0's shard dir and read its win.c. That's the fastest path.

Let me search for the dir. `ls .run/P40/T11/` and find func_80187EA0. Actually it's a G28x shard (the previous one). Let me find it.
