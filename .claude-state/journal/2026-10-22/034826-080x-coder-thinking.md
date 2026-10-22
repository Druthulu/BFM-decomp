---
ts: 2026-10-22T09:48:26Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_BEK2a3YFLA4KvwrFeQhj
---
The papermario tree is a partial gcc (missing c-type.c and expand.c). But tools/reference/gcc-2.7.2/ has expr.c, cse.c, combine.c — also partial.

Let me check expr.c (the RTL expander) — maybe the constant substitution is there. In gcc 2.7, `expand_expr` lives in expr.c? No — in gcc 2.7, expand.c contains expand_expr; but older versions had it in expr.c! In gcc 2.5/2.6, expr.c had expand_expr. Let me grep expr.c for "case REG:" with constanthandling.
