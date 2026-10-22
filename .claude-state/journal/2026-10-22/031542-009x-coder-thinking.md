---
ts: 2026-10-22T09:15:42Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_ViPpRduLEckqaiSvXPNh
---
The regex matched a call site "func_8018483C(a0);" inside func_801847B8. Need to require the match be at column 0 and start with a type (not just ident) — i.e., the function name must not be the first token. Let me fix: require that the name is preceded by a type-ish token: regex `^(?!func_8018483C\b)[A-Za-z_][\w ]*\*?\s*func_8018483C\s*\(` — simpler: require the line to match `^\w+\s+[\w *]*func_NAME\s*\(` and the name not at position 0.

Simplest: match `^[^f]*\bfunc_NAME\s*\(` but need type before. Use: line starts with non-space, and the token before the name is a type keyword/identifier. Check that line[:m.start()] contains at least one word char and the name isn't atindex 0.
