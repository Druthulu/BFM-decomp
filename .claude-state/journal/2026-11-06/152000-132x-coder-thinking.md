---
ts: 2026-11-06T22:20:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM3
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BOCRUqGsNRcIs3jYbjKB
---
Now the twins: try the do-while EBB split around the dst blocks. The dst block is 8 statements (dst = load; 3 sh; 2 sums). Wrapping it in a do{}while(0) might split the EBB and change local-alloc's allocation — potentially fixing the dst→$3 issue.

Let me test on item 2 (801919A0) with dst s32 (w0.c):
- t1: wrap the dst block (the 8 statements) in a do-while.
- t2: wrap only the first dst block.
- t3: wrap each dst block.

The dst block text (from orig):
```
        dst = *(s32 *)(arg0 + 0xD0);
        *(u16 *)(dst + 6) = sp10[0];
        *(u16 *)(dst + 0xA) = sp10[1];
        *(u16 *)(dst + 0xE) = sp10[2];
        *(u16 *)(*(s32 *)(dst + 0x20) + 0x10) =
            *(u16 *)(dst + 0xFC) + *(u16 *)(*(s32 *)(src + 0x20) + 0x10);
        *(u16 *)(*(s32 *)(dst + 0x20) + 0x12) =
            *(u16 *)(dst + 0xFE) + *(u16 *)(*(s32 *)(src + 0x20) + 0x12);
```
This appears 3 times for 0xD0 and 3 times for 0xD4 (with different arg0 offsets). I can wrap each occurrence generically: insert `do {` before `dst = ...` and `} while(0); // !FAKE` after the second sum.

Let me write a generator that wraps ALL dst blocks, or just the ones at 0xD0, or just the first.

The dst block ends with the line `            *(u16 *)(dst + 0xFE) + *(u16 *)(*(s32 *)(src + 0x20) + 0x12);` — same for all 6 blocks. So I can regex-replace.

Let me write a script using regex to wrap each `dst = *(s32 *)(arg0 + 0xD0);\n ... ;` block.

Simpler: use a Python regex matching from `        dst = *(s32 *)(arg0 + 0x[D0]0|0xD4);` through the next `0x12);` line, and wrap.

Let me test a few spans:
- u1: wrap all 6 dst blocks.
- u2: wrap only the 0xD0 blocks (3).
- u3: wrap only the first dst block.

Score. If any gives 0 → MATCH (and the twin too).
