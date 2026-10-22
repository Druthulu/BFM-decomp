---
ts: 2026-10-22T04:27:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG08c
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_EOaTchyDlLJP8mf9D8Uh
---
No baseline snapshot → target = build/... object. So the target bytes come from the current build (which is the ROM-reconstructed tree; the function body still has the pin in src? no — src has the pinned version with `register int result __asm__("$2")`, and the build's object for that TU contains the PINNED compiled code, which equals the ROM bytes. Yes! The pin reproduces the ROM exactly, that's why the score compares against it.

So: target = build/<TU>.o compiled from the current src (pinned). I can objdump that object to see the full 40-insn target listing.

Which build object corresponds to the TU that includes src/shared/ov/func_8014FD54.h? Let me find the includers. The header is included in some TU (maybe md_MAIN_xxx or ov_SCxx). Let's grep src for the include.

Note: the `--try` for a header TU (--body) may compile the body into a stub TU. The comparison uses the baseline object's function. For header items, the target is the same in all includers.

Let me find the includerand objdump.
