## Recap
Phase 3.41 made the type checks meaningful and mirrored the canonical types into Ghidra. `type_census --check` used to fail on all ~176k raw casts, so it could never pass. It now asserts the done-criteria: no unlisted duplicate struct layouts, no definitions outside the canonical headers, no dead names, controls 4/4, and no unledgered lying declaration. Raw casts are still printed and stay gated by `--check-casts --residue`, and the check runs inside `make tools-health`. Return-type lies, where a declaration's return type disagrees with the definition, are now detected. They went from 273 functions over 100,266 declaration lines to 19 functions over 9,302 lines. Each of the 19 is a width or sign mismatch kept in config/lying_exceptions.tsv with the instruction that moves. `lever_census --check` now requires every `// !FAKE:` marker to name its instrument (1,853 attributed, 0 bare). A new tool, tools/ghidra_types.py, writes 7,151 canonical types (structs, typedefs, unions) from the headers into per-program Ghidra rows. Their field offsets and sizes equal gcc's, a staleness `--check` sits in tools-health, and all six rebuild proofs pass. The live Ghidra database holds the types, and the developer confirmed COORD2_8001EFE0 is right. Three 3.40 tool bugs were fixed. The readability series and README graph now show return lies, and the day-1 guide teaches one shared prototype header. Story §10, retrospective §7 and the wiki run to Phase 41.

Milestone gate at f4b1fbad3d, from a clean tree: R22 218/218 run alone; tools-health OK; type_census --check --check-structs --check-casts --residue rc 0; lever_census --check --strict --residue rc 0; doc_links --strict 0; ghidra_rebuild --proof PROOF PASS for all six programs.

Open items:
- The developer pushes the archive clone (b9534ed) and the repo.
- The MCP Ghidra is stopped; restart it with tools/ghidra_mcp_start.sh, then the developer runs /mcp.
- .run/P41 holds ~2.4 GB of scratch plus the 1 GB ghidra.bak, which the developer keeps for now.
- For 3.43: 37 s32 definitions with no return statement, and the 9 expand-hardreg-var wall tags.
- The PA3 wait-for bug report is the developer's to file.
