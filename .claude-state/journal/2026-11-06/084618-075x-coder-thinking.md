---
ts: 2026-11-06T15:46:18Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_zpkglba08wcWYyAhkOej
---
Lines 294 and 308 are the post-switch _m launders, whose pattern differs (indented 6 spaces, and the call line differs: `((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10)); }` — maybe the call line in the post-switch block is the same but the asm indentation is 6 spaces not 10).

So remaining: m/_v (206,208) and 2 post-switch _m (294,308).

Since c2 (with those 4) scores 0, they are "non-load-bearing" in the current shape? Wait, c2 has 4 launders and scores 0 — so removing the 3 case-6/case-7 _m launders (with dead resets) fixed everything, and the other 4 launders are redundant in c2's shape. Now I need to remove them too and keep score 0.

Let me first handle the post-switch _m launders with the same dead reset. The pattern:
```
      __asm__ __volatile__("" : "=r"(_m) : "0"(_m));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t8_mac1)
      ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10)); }
```
Let me check the exact lines 293-296.
