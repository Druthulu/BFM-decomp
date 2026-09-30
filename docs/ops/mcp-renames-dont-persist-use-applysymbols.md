# mcp-renames-dont-persist-use-applysymbols

**Fact (2026-09-04, P31 S78):** 47 renames made through the headless GhidrAssistMCP server
(`batch_rename`/`rename_symbol`, all reported success) were GONE after `tools/ghidra_mcp_stop.sh`
("Save succeeded", DB grew 9.9→10.4 MB). R9's read-only re-open caught it. Cause not isolated (single
instance, normal stop sequence; Phase 3 had verified the same flow). The fix that worked first time:
`tools/ghidra_apply_symbols.sh [PROG] [symbols…]` → `tools/ghidra_scripts/ApplySymbols.java`, a headless
postScript that mirrors `config/symbols.us.txt` into the program with a real save (73 renamed,
R9-verified ×4). Also: gate worktrees carry no `.run/obj40`, so main's LINKED (SDK-object) build path is
only ever checked by an in-tree `make build BINARY=main` — it had been red at HEAD for a day unnoticed.

**Why:** the curated text file is the source of truth (R15); an MCP write that never persisted looks
identical to one that did until a fresh open reads the DB (R9). A gate that always takes the fallback
path is blind to the path the contract cares about (R34).

**How to apply:** for symbol renames, edit `config/symbols.us.txt` (no `name:` tokens in comments —
splat parses them as attributes), run `lint_symbol_refs.py` and read its WHOLE output (verbatim
`__asm__` bodies spell `\tfunc_X`), then `ghidra_mcp_stop.sh` → `ghidra_apply_symbols.sh` →
`ghidra_mcp_verify.sh <addr> <name>`. After any change to `psyq_identify`/`psyq_integrate`/the splat
yaml: in-tree `make build BINARY=main` WITH `.run/obj40`, then the fresh-extract fallback WITHOUT it.
See [[exonerate-the-instrument]], [[check-against-a-known-true-case]].
