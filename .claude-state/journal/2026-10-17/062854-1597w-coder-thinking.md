---
ts: 2026-10-17T12:28:54.100Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a04bcca3508c8aa5c
model: claude-opus-5-5[1m]
effort: medium
turnId: b53b24c7-146b-4600-ac40-c2f9f65331a4
---
The pin comment is stale after banking but I should preserve it rather than drop it. I need to check whether the typedef union line before the def gets captured by scan_text when extracting from win.c, and verify this against the SC03_099 reference file, then plan the typedef insertion across the six W4 copy translation units and their six extern-only sibling TUs.

For each file, I'll insert the W4 union typedef before the first extern function declaration, replace those declarations to return W4 instead of taking a pointer argument, and update callers to assign the function's return value through a cast pointer instead of passing the pointer directly. Apply-body's "IDENTICAL on object(s)" check should validate the whole translation unit including callers, so I just need the caller edits done before running apply-body, and the pointer-to-return-value cast should correctly handle the extern declaration mismatch too — I still need to confirm the sp20 removal detail in the body file.
