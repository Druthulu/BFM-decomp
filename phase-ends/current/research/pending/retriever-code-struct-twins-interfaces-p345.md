# struct_twins.py interfaces at HEAD (Phase 3.45 T1/T2)

task: Phase 3.45 replan planner, Interfaces for the consolidation-tool tasks (exact twins folded on shape, fragments traced to parent pointer source)
agent: retriever-code
tags: p345, struct-twins, type-census, disposition-ledger, merge-evidence, interfaces

## Answer
Full per-item answer is in the handback message. Line numbers are at HEAD as read. Old plan cites moved: CANON_HEADERS 57->58, find_definitions 69->70, build_struct_map 813->816, load_twins 1113->1116, structs_reading 1136->1139, controls 1674->1677, --write 500->2753, --show 501->2754.

## Findings
1. argparse: tools/struct_twins.py:2750-2767 (main 2750; dispatch 2768-2816).
   - --census-dir 2752 (default CENSUS_DEFAULT 88 = tc.OUT_DIR_DEFAULT); --write 2753 (rewrites ## Twins, 2812-2816); --show LHASH 2754 (per-name objects for one class, 2781-2794).
   - --inventory 2755 + --out 2756 (default INVENTORY_DEFAULT 175 = .run/3.45/t1/struct_inventory.tsv; 2775-2776).
   - --dispositions 2757, --check 2758, --ledger 2759 (2777-2778; check exits 1 per 433).
   - --links 2760, --out-dir 2761 (default LINKS_DIR 808 = .run/3.45/t2), -j 2762 (default 16), --propose 2763, --report [PATH] 2764-2765 (const REPORT_DEFAULT 2241 = docs/ops/p345-struct-merge-report.md), --policy 2766 (choices POLICIES 813 = typed|effective|views; default effective; used only with --propose). Dispatch 2773-2774.
   - --selftest 2767 (links_selftest 2689; 2771-2772).
   - --links prints summary, writes tables (2510-2538); --propose writes ledger for chosen policy (2523-2529); --report writes text (2530-2537).
2. Ledger config/struct_dispositions.tsv:
   - header columns LEDGER_COLS 178: key, kind, file_line, size, disposition, target, class, evidence, reason. Header row written 402; comment block LEDGER_HEAD 182-196.
   - writer ledger_write 398-414; checker is dispositions(check=True) 417-433 (writer branch 434-436).
   - closed dispositions DISPOSITIONS 177 = undisposed|fold|apart|no-evidence.
   - closed class CLASSES 179: fold = global|pointer|body; apart = own|conflict|size|hub; undisposed and no-evidence = `-`.
   - applied rule: APPLIED_RX 180 (reason ends `applied:<commit>`); enforced in ledger_write 407-408 (applied rows never overwritten by props); counted in links 2525-2529.
   - --check FAILS (exit 1, 433) on: missing placeholder row (430), duplicate key (dup), unknown key (have minus placeholders), malformed row or unknown disposition (ledger_read 373), and ledger_problems 380-395: class outside list, fold target not a ledger/PsyQ/ledgered key, apart without 0x address or file:line in evidence (CITE_RX 181), no-evidence without reason. undisposed rows do NOT fail (only counted, 427).
   - ledger_read 364-377 pads pre-T2.c2 rows (no class) with `-` (371-372).
3. Link classes (LINK_ORDER 822; POINTER_SUBS 812; EFF_SUBS 815; HUB_TYPE_SUBS 814) computed in links_build 1064+:
   - global 1349 (sub global-view if "cast" in view flag, else global); global refusals 1326/1339.
   - body 1391 (tiny-body refused 1393 when nins < MIN_BODY_INS 811).
   - body-view 1547, 1578 (candidates big only, 1583).
   - arg-eff 1648 (ptr call); arg 1656; assign 1684; eff-flow 1594 (ptr call), 1664-1667 (assign), 1692/1716/1730 (PF counts). Sub ret, ret-of, field, store-global, decl, view: not individually traced.
   - hub slot: hkey 1786-1795 (slot identity outside typed; h_exact+param/ret); bkey 1797; hub guard 1811-1845: slot hub if width conflict or (len(types) >= HUB_K 809 and offsets <= HUB_OFFS 810 and parts), refused reason "hub" at 1842-1843.
   - hub type: 1846-1881: HUB_TYPE_SUBS 1850, len(partners) < HUB_K 1855, refused "hub-type" 1875-1876.
   - target choice: links_render 2134-2135: min over members of (klass != PsyQ, klass != ledgered, -reach, _fl_key(file_line)) = PsyQ > ledgered > highest reach > lowest file:line.
4. Outputs (writers in links_render 2081-2226; table() local):
   - widths.tsv 2091 (type, offset, width, sign, field, cite); sizes.tsv 2094 (type, kind, cite).
   - eff.tsv 2095-2098 (slot, status, types): status = never dereferenced | no typed use | poly | effective; types = "kind: cite" joined by " | ".
   - poly.tsv 2099 (slot, types, cites); unplaced.tsv 2101.
   - links.<pol>.tsv 2115 (class, sub, A, B, cite_A, cite_B).
   - refused.<pol>.tsv 2117 (reason, class, sub, A, B, cite_A, cite_B, detail).
   - hubs.<pol>.tsv 2119 (slot, types, why, cites); hubtypes.<pol>.tsv 2122 (type, partners, links_refused, why, partner_list).
   - components.<pol>.tsv 2140 (component, members, target, merged_size, merged_layout, refused_touching, projected_reach).
   - proposals.<pol>.tsv 2174 (key, disposition, target, class, evidence, reason).
   - decl_param.tsv 2223 (name, object, i, decl, decl_type, def, def_type, resolved_<pol>); twins.tsv 2226 (lhash, names, inventory_keys, verdict_<pol>).
5. Shape helpers (.run/3.45/shape/shape.py): imports 8-9 (`import struct_twins as st`; `from struct_layout import scalar_of, PAD_RX`); uses st.type_universe() 12, st.inventory_defs(u) 13, st.tc.Resolver(u["g"]) 14, res.layout_of_fields(fields, kind, packed=) 22, res.layout(type, stars, []) 33, scalar_of 34.
   - type_universe(texts=None) struct_twins.py:219; inventory_defs(u=None) :240.
   - Resolver class struct_layout.py:211, __init__(defs_by_name) :213; layout(type_text, stars=0, dims=(), bits=None) :218; layout_of_fields(fields, kind, packed=False) :276.
   - scalar_of(t) struct_layout.py:62; PAD_RX :361 = ^pad([0-9A-F]+)$.
6. Users: inventory_users struct_twins.py:279; access_sites and h_exact at 336-337; globals/params/returns/locals = counts of object keys with kind G/P/R/L (337); columns INV_COLS 198-199; writer inventory 341 (open 346).
   - Local-source: NOT recorded in struct_twins inventory (counts only). type_census find_decls_and_flows 487 records flows with tu, fn, line: arg 563/565 (src, callee, i), assign 572/574 (dst, src text, line), ret-of 578 (dst, callee), field 590/597 (dst, base, bclass, off), return 603 (src). Single-source guard 865-890 vetoes multi-source locals. struct_twins consumes these via src_of 1411.
7. Twins: write 790-803 (heading match 792; section replaced 802). --write call 2812-2816. type_census load_twins 1116-1136; structs_reading 1139 (calls load_twins 1147; dup_classes = len(gating_rows) 1197; twins_stale count 1198); reads twins_p 1393; check_structs_verdict 2069 (viol list 2154 covers dup_classes, outside_canon, dead only). CANON_HEADERS 58; find_definitions 70; controls 1677.

## Dead ends
- No function named twins_stale or dup_classes exists; both are count keys of structs_reading (1197-1198).
- Not traced: decl/ret/field/store-global/view link sub-kinds individually.

sources: tools/struct_twins.py; tools/type_census.py; tools/struct_layout.py; .run/3.45/shape/shape.py; docs/ops/p345-t2-struct-merge-evidence.md (not read; method spec not verified).
