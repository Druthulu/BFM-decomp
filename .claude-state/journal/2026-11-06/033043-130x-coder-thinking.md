---
ts: 2026-11-06T10:30:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG27x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_WMBcp89IU6rVKLFGaVxR
---
s15 and s23 are identical to base (no change) → skipped. So 23 files created. Let me score them.

Note: some variants like s13/s14/s17/s18 add `(void)` casts or volatile — those might be considered levers (volatile is a real C type qualifier, but s14 `*(volatile s32*)a0` might change code). Let me just score them; they're all lever-free in the sense of no pin/keepalive/asm.

Wait, s14 uses `volatile` — that's a real C type. But it might be considered a "barrier"-like lever. The kinds for item 1 are keepalive,pin. volatile isn't a listed lever, but "no new lever of any kind". Hmm, volatile could be seen as a barrier. Let me drop s14 to be safe. Actually, the scoring is just for tries; if s14 scores 0, I'd need to judge whether it's a lever. Let me keep it but note.

Let me score all.
