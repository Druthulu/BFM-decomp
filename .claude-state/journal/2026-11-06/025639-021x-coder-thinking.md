---
ts: 2026-11-06T09:56:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_vrPh1mkWEBtcIxXIKyX7
---
Now let's strip: pins → plain, barrier removed. The barrier here is `__asm__ __volatile__("" ::: "a0")` (clobbers a0). Removing it means the a0 register isn't clobbered; also `((void (*)(s32))func_80146C3C)(s0)` is a call-site return-type cast (that's a "call-site cast" lever? It's listed in moves as MATCH). The kinds are barrier,pin only, so the call cast may stay (it's not barrier or pin; it's a launder? no, it's a call return-type cast — a lever of another kind? The constraint says "levers of other kinds the def already had (pins under other causes) may stay, never added". So we can keep the call cast).

Wait — is `((void (*)(s32))func_80146C3C)(s0)` a "pin"? The moves list says `func_80157BC8 MATCH: both $2 result pins -> call-site return-type casts`. So call-site cast is a distinct lever (not pin). It's allowed to stay.

So nopin for CD314:
- `register s32 s0 __asm__("$16");` → `s32 s0;`
- `register s32 tb __asm__("$3");` → `s32 tb;`
- delete barrier line.

Let me score that.
