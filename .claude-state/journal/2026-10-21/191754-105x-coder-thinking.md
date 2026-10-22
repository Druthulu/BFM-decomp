---
ts: 2026-10-22T01:17:54Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_bihiPJ9QoWqoAsFEd9u6
---
`sed -i '$a b'` works. Now I can append lines to moves.md with sed -i.

The line content contains special chars for sed (e.g. `|`, `/`, `$`, `&`). Using `a` with text: sed's `a` command text — backslashes and `&` are not special in the `a` text (in GNU sed, `&` is not expanded in `a` text; backslashes need care). The text contains `$2` (a literal $) — in `a` text, `$` is literal ✓. And `\` would be an escape — avoid backslashes.

My lines:
1. `pin | func_8014C308 | WALL cse-const-fold — cse/combine folds the const 1 into the 4 return copies: the v0 pseudo dies, $2 free at the compares, li v0,1 lands in the return block; best 4 (u8 boolean body) (G08b)`
2. `pin | func_8014FD54 | HANDOFF — best vP1_ret.c score 6 (39 vs 40 ins); the ROM keeps $2 reserved for the whole fn (the pin's hard reg) so the call result copies to $3 (move v1,v0); lever-free the call-result pseudo (pri 10000) takes $2; next: RESULT_DECL set before the call, or pri > call-result (G08b)`

Careful with sed: the text contains `/` (in "cse/combine") — in the `a` command, the text isn't parsed for `/` ✓ (only the command word is). But the shell quoting: I'll use single quotes around the sed script; the text has no single quotes ✓. It has `$2` — inside single quotes, the shell won't expand ✓.

Also em-dashes — fine (UTF-8).

Let me append both lines with one sed command: `sed -i '$a LINE1\nLINE2'`? GNU sed supports `\n` in the a text? In GNU sed, `a text` with embedded `\n` works: `sed -i '$a line1\nline2'`. Let me do them as two separate sed commands to be safe (chained with `;`).

Let me first delete the sedtest file (via the cleanup tool) later.

Let me append.
