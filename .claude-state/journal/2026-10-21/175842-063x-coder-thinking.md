---
ts: 2026-10-21T23:58:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG07r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_D3eX6GGYTa8X5wC2AZux
---
OK. Now let me be strategic. Items with `$0` zr pins (opaque copy problem): func_800D0D7C, func_80181E64, func_8003DF8C. These three likely share the same wall (the "$0-ADD OPAQUE COPY" mechanism).

Items with real register pins: func_801415C0 ($16/$17), func_8012944C ($17), func_80180480 ($3), func_800D2650 ($2/$8/$14/$3).

The latter group might be crackable via the priority-ordering lever.

Let me now quickly do func_8012944C (remove the $17 pin) — cheap test.

And func_80180480 (remove the $3 pin).

Let me set those up and score.

For func_8012944C, the body: remove `register short *p __asm__("$17");` → `short *p;`.

Let me write the candidates.
