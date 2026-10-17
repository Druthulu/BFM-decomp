---
ts: 2026-10-17T12:12:57.520Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a56c959d43d67f5c6
model: claude-opus-5-5[1m]
effort: medium
turnId: 0c52f25b-3226-4f4e-bcd1-94c2abf6159e
---
The headers are already lever-free, a different class, so these aren't copies. I'm planning a general remap script: for each crack, take the exemplar translation unit and function, then for each copy remap the sibling body using the exemplar's before state and the after state extracted just from the definition in win.c, skipping any includes or extern declarations. I'll reuse the scan_text approach to isolate just the definition portion.

Listing out the exemplar functions per crack ID, then checking the remap_body signature before writing the actual script.

I'll generalize remap_b.py to map each crack's exemplar body onto every copy's own body using its own names/addresses, writing one body file per copy. For the four s32-return classes I'll first update each copy's prototypes to `extern s32` across its overlay (since the new return type won't compile against old prototypes), then bank with `--apply-body --dirty-ok`, reverting prototype edits for any copy that fails the byte-check, and rely on the full gate to confirm prototype-only changes in non-result-using TUs don't shift bytes.
