---
ts: 2026-11-06T06:06:46Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_VJr59XdWQZlpYxie17FS
---
So win.c is a bare function definition, with extern decls inside. The --body file holds the function's definition only.

Now for my items, I need to produce a body that is the current def with launder and pin removed, in real C. That means:
- remove `register ... __asm__("$N")` pin declarations
- replace asm launders with real C

Let me check the current def, then create orig.c copy. The brief says: Start from the current def in src (copy to <dir>/orig.c); diff against the current src at item start.

Let me set up item 1: copy lines 3010-3168 to orig.c. Use sed.

Actually I need to be careful: the function body includes `CAST_WIDTH`, `CAST_ALIAS`, `Unkstruct_800B5CB8` types — the --body mode compiles the function standalone? It probably needs the surrounding context... let me check how delever_search --try --body works. It likely compiles the TU with the body substituted for the function. So the body text is inserted into the TU, meaning casts/types are available. Good.

Let me check a worked notes.md for insight on methodology.
