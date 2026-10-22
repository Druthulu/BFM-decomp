---
ts: 2026-10-22T00:44:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_2Qfspwf1uoSoK1odPBgF
---
match_one.py compiles a standalone C (externs + def) and diffs against an asm .s. Our functions are in src/shared/ov/*.h with a "pinned triple"?? The shared ov headers were derived from the ROM; the target object is build/'s object (the fleet build). The baseline is build/<obj>.

For my purposes: I want the target's instruction listing for func_8014C308. The baseline object for the first includer recipe: rec["obj"] e.g. "build/ov_SC03_099/ov_SC03_099.o". I can find the object and disassemble with objdump directly (objdump is a shell command, allowed?). Let me try: find the obj path. I need recs. Simpler: search build/ for the object containing the symbol.

Let me try: `nm build/...` — need path. Which includer is recs[0]? Unknown order. Let me grep the recipes file for the header.

Alternatively use objdump on all build objects and grep for func_8014C308. Let me check build/ exists.
