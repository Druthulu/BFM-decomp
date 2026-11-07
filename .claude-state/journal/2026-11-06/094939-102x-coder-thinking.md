---
ts: 2026-11-06T16:49:39Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_865BzJmfHWNsHsjvZlIU
---
The spliced body from no_fp.c has `gte_SetRotMatrix(m);` — the body I extracted (orig.c, from the src file lines 3782-3924) contains the macro call, not the expansion. Since the .i is already preprocessed, the macro name in the spliced text is NOT expanded by cc1 (it's a function call to an undeclared function → implicit int, and the TU declares it? It generated `jal gte_SetRotMatrix`).

So my dump harness for item 2 is unfaithful for the macro calls. I need to expand the body's macros first (cpp) before splicing, or splice into the .c and cpp.

Fix: in splice.py, run cpp on the body? The body uses macros from headers. Simplest: build the body text as it appears in the .i by extracting the original .i region and applying text replacements? Better: generate the full .c candidate (the real TU with the body replaced) and cpp it. But the real TU is in src/ (can't write). I can copy the TU text into my item dir and cpp with the right include paths: the TU has `#include "../shared/..."` relative to src/ov_SC06_011 — if I copy to .run/..., those includes break.

Alternative: cpp the body snippet alone with the same includes: `mipsel-linux-gnu-cpp -lang-c -Iinclude ... body.c` — the body references types (Unkstruct...) declared in headers, but as a standalone file the macros in the body expand. The body's `gte_SetRotMatrix(m)` would expand if gte_inline.h is included; but the body file doesn't include it. I can prepend `#include "gte_inline.h"`? The macro definitions are in include/gte_inline.h. The TU includes it via some header. Prepending an include of gte_inline.h to the body snippet would expand the macros.

Simplest robust fix: take the ORIGINAL .i (already fully preprocessed) and build candidate .i files by replacing the *corresponding* region with a re-cpp'd body. I.e., cpp the body snippet with `-include` of the headers it needs.

What does the body need? It uses: Unkstruct types? No — this function uses plain types, gte macros, RotTransSV, RotTransPers, AddPrim (a macro!), func_* calls, D_ globals, GetTPage.

AddPrim is also a macro (from include/libgs.h presumably). The body I have has `AddPrim(otAddr, prim);` — in the .i it's expanded.

So the body needs the same headers the TU includes. Let me check the TU's includes.
