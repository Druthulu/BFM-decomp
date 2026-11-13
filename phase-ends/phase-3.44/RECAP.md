## Recap
Phase 3.44 (Signatures from evidence) is closed with its milestone met. The gate passed at 8bac8eee31: R22 218/218 run alone; tools-health OK, now including the signature gate; sig_evidence --check 0 failed, 0 unused, 0 unledgered; type_census unledgered lying 0; share_census strict OK; lever_census --check --strict --residue OK; ghidra_rebuild --proof PROOF PASS on all six programs; doc_links and audit_public clean; ledger_backup run (archive commit 05feeb4, unpushed).

What it built: tools/sig_evidence.py, an asm signature census over all 218 binaries (about 17 s at -j 16; 92,716 classes: used 11,345, unused 18,026, unknown 63,345, each unknown with a reason). --compare checks every C declaration and definition against it under six rules, and --check verifies every ledger cite against the bytes. The 198,029 disagreements T4 measured went to 0 unledgered:
- T5: return widths (116 names after the asm-label fix), with RET_AS marked casts backed by config/ret_view_casts.tsv;
- T6: `()` declarations, with KR_AS backed by config/kr_view_casts.tsv;
- T7: 392 non-void functions with no return, given a byte-neutral return, void, or a `$v0 at exit:` comment;
- T8: void-read, arity, arg-over, and the PsyQ declarations aligned to the PsyQ 4.0 headers.
3,264 ledger rows remain, all facts about the shipped game (mostly SHARED-DECL-SPLIT `()` declarations). The signature gate runs inside tools-health and adds about 86 s. Other work: type_census's struct_map tie-break was fixed so its counts are deterministic (T2); tools/scratch_cmp.py was promoted from twelve coder copies (T12); the readability series gained names columns and signature columns, each with a README graph (T13, T14); the day-1 guide gained 3.43's naming lessons and 3.44's measurement and prevention lessons; story §10, retrospective §7 and the wiki run to Phase 44, and the wiki has a modder section on reading the census.

Open items:
- 88 RETURN-LIE dedup rows are now cleared for sharing; recommended to retarget to 3.46 (layout) rather than 3.45.
- lever_census.py:864-875 has the same cache-order nondeterminism T2 fixed (C0582).
- The ram_probe scenario list (R128) is still owed to the developer.
- After the close, Claude runs tools/ghidra_mcp_start.sh and asks the developer for /mcp.
- The developer pushes the repo and the archive clone (05feeb4).
