---
ts: 2026-11-06T09:34:17Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_s9TTyB5Z9slUW5ynrFyT
---
Wait, w4 makes mlo u16 — but mlo = 0xFFFFFF wouldn't fit; it's used as a mask so the value changes → wrong codegen (but it's still a real-C variant; it'd score worse). Hmm, a u16 mlo = 0xFFFF would change the mask semantics — that's not a plausible real-C move for matching. Let me keep it anyway as a scored try? It changes semantics; better drop w4 and use another variant. Let me replace w4 with `u32 mlo;` → `u32 mlo, c80...` no.

Actually the catalog says widths s16/u8 — c80/cFF/cDF as u8 is plausible (they're byte constants). mlo as u32 is right.

Let me change w4 to: declare `mlo` as `u32` but init at decl (`u32 mlo = 0xFFFFFF;` and remove the `mlo = 0xFFFFFF;` line) — init at decl is in the catalog. Similarly c80 = 0x80 at decl. That requires removing the assignment lines. Let me implement w4 as init-at-decl for mlo, c80, cFF.

Simpler: keep 6*4 = 24 variants; that's under 30. Let me do 6 decl orders × 5 widths with w4 = init-at-decl (mlo/c80/cFF) and w5 = c80/cFF/cDF as u16. Let me rewrite.
