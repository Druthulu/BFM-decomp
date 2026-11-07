---
ts: 2026-11-06T14:59:48Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SpZujLboesGzEowCn1b9
---
Good — moves.md gives many launder-crack mechanisms. Key patterns:
- `pv = *p; pv &= 0xFF000000;` split (real 2nd set)
- `do { } while (0)` for launders
- pointer reuse / reassignment
- dead-reset
- `x = (s16)x` real 2nd set

Let me check if the shared function (func_8017FBEC / 80186074 / 801886FC — same 237 ins body) has a known crack in moves.md. Also func_8017ED5C appears at line 24 as a WALL for W03 — but our item is func_8017F2D4 in the same file, different function. And func_8017DE00... let me grep moves for these names.
