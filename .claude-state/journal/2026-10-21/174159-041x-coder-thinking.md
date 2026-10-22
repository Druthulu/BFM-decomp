---
ts: 2026-10-21T23:41:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08r
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_si6sP5NOVFiheYJWQMY1
---
There's `tools/masked_diff.py` with insns_from_object. And a tool to dump? Let me check masked_diff.py's CLI: maybe `python3 tools/masked_diff.py <obj> <fn>` dumps the function's instructions. That would give me the ROM asm (from the baseline object) — but I need the object path. The baseline object for the TU: I need rec["obj"]. The recipes file might list them: `oracle.load_recipes()` reads from somewhere (a JSON in .run/P36?). Let me find the recipes file: grep load_recipes.

Let me check tools/masked_diff.py CLI and the recipes location.
