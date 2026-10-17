---
ts: 2026-10-17T12:05:06.898Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a9b75b3e3c01d6fa8
model: claude-opus-5-5[1m]
effort: medium
turnId: 9b80ef94-0ae1-44c6-acfd-ddecb9279a50
---
The alias checks out structurally, but the relocation symbol differs even though the linked bytes would match—so it's not actually a clean match at the object level. This points to a more natural explanation: the original code likely had a differently-typed declaration at that address, perhaps a larger struct, which would explain the memset behavior.

For the symbol_ref question, I'm now tracing through how GCC 2.7.2's MIPS backend handles loading a symbol address directly into a hard register during call argument setup—specifically whether CSE merges these loads or treats them separately depending on how the "la" macro gets expanded during instruction splitting.

I'm also puzzled by why b.c produces an s0 pseudo while the similar code doesn't—it seems to hinge on whether expand_call precomputes the argument into a pseudo register based on some condition around constant legitimacy or flag_no_function_cse, which I need to trace through more carefully in the 2.7.2 source.

Given how many attempts I've made, I'm resigning myself to needing a non-identical rtx form here, since natural spelling of the code isn't matching. I'll try a couple more variations.

Pointing a different global for the memset buffer would require introducing a new symbol, which isn't viable without a linker alias trick. I'm concluding this class only has lever-based matches that don't even align on relocation type, so I'll move on and tally up: of the seven classes, several are confirmed matches, a few remain unresolved, and now I need to verify everything against the targets using the match script.

For match_one to work I likely need a standalone compilation unit rather than relying on prelude.h splicing — checking how a similar case handled it, it seems feeding the full translation unit file directly to match_one with the --c flag should let it extract and compile the function properly, so I'll try that with the spliced TU files.

The identity alias check adds a second lever-only match (differing only by relocation), keeping natural spellings at 18 with all seven classes now attempted. Next, I'll write the four win.c files, verify each against the regenerated targets with match_one, and compile a spliced full-TU copy of each.
