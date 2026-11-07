---
ts: 2026-11-06T10:21:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_XqP23xKMNO3R3Ea1cXdQ
---
e15: the store position is FIXED (no longer in the diff), but now `lh v0,52(sp); li a2,1` moved. So the do-while fixed the store but moved other insns. Interesting! So the do-while splits the EBB, preventing the store from sinking, but the block split changes other scheduling.

Score 4 (2 insns moved). Close. Maybe combining do-while with a different placement could get 0.

Let me try: do-while around the store AND around the following statements to keep the EBB grouping? Or place the do-while differently.

Actually, the diff now: mine has `lh v0,52(sp); li a2,1` at 121-122, target has them at 124-126 (after the address setup). So in e15, those two insns are now hoisted too high. The do-while made the store's block end, and the subsequent insns got scheduled differently.

Hmm. What if the do-while wraps the store AND the 0x18 store, so the split is after both? Let me try variations:
f1: do-while wraps unk1C store + 0x18 store.
f2: do-while wraps unk1C store, and the 0x18 store moved inside.
f3: do-while wraps the address setup (func call) instead.

Let me try f1-f3 quickly. Time ~03:46. Let me allow 5 more min.
