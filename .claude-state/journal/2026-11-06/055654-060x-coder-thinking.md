---
ts: 2026-11-06T12:56:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_h1WXvf1ZlthPEzGpjzXJ
---
Most of the diffs are branch target offsets that shift because of the 4 missing insns. The real difference is at mine[112:114] vs target[112:118]:

mine:
```
112 bgez v0,47c0
113 (delay)
114 ...
```
target:
```
112 bltz v0,47c8
113 (delay)
114 beqz v0,4aa8
115 nop
116 j 47d8
117 nop
```

So the target has an extra `beqz v0, 4aa8` (the "break" branch to the epilogue) plus a `j` to the join, and the condition is inverted (bltz vs bgez). This is the cross-jump story: the target has 4 more instructions because the two arms are NOT merged.

Let me look at the source: 

```
if (*(s16 *)(s0 + 0x6) - ((Unk*)b58)->unk6 >= 0) {
    if (*(s16 *)(s0 + 0x6) - ((Unk*)b58)->unk6 >= 0x80) {
        break;
    }
    <BARRIER>
} else {
    if (((Unk*)b58)->unk6 - *(s16 *)(s0 + 0x6) >= 0x80) {
        break;
    }
}
```

The two arms: 
- then-arm: if (d >= 0x80) break;  (where d = unk6diff)
- else-arm: if (-d >= 0x80) break;

Both are "if (x >= 0x80) goto epilogue". The cross-jump merges them (they're the same code shape).

The target (with the barrier) keeps them separate: 
target at 112: `bltz v0,47c8` — hmm.

Let me get the target listing around 100-130 to understand.

The real-C route: make the two arms structurally different so cross-jump can't merge them, without the asm. E.g., write the else-arm's condition in a different form: `if (((Unk*)b58)->unk6 - *(s16*)(s0+0x6) >= 0x80)` → maybe `if (*(s16*)(s0+0x6) - b58->unk6 <= -0x80)`. That would produce a different instruction sequence (slti vs ...). But the target has specific instructions.

Alternatively invert the outer test: `if (diff < 0) { else-arm } else { then-arm }` — that flips the branch polarity.

Let me look at the target asm region.
