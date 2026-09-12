# T2 probe (i) — rung 1 (struct spelling) on a stratified sample; seed 37; 165 bodies; 0 s wall

Pool sizes (bodies × typed bases in the census): {}

| stratum | bodies | IDENTICAL | DIFFERS | COMPILE-ERROR/CRASH | no site / other | sites rewritten | DIFFERS closed by S2 (casts kept) | of DIFFERS with levers: S+A IDENTICAL | levers-off alone IDENTICAL | residual kinds (DIFFERS) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---|
| A-entity(0x24C) | 40 | 37 | 1 | 0 | 2 | 155 | 1/1 (2 casts kept) | 0/0 | 0/0 | {'COUNT': 1} |
| B-large-ptr-globals | 25 | 16 | 1 | 0 | 8 | 134 | 1/1 (1 casts kept) | 0/1 | 0/1 | {'COUNT': 1} |
| C-matrix/vector-shaped | 25 | 18 | 7 | 0 | 0 | 180 | 7/7 (20 casts kept) | 0/3 | 0/3 | {'ORDER': 3, 'COUNT': 4} |
| D-record-tables | 25 | 18 | 3 | 3 | 1 | 74 | 3/3 (3 casts kept) | 0/0 | 0/0 | {'COUNT': 3} |
| E-shared-header-bodies | 20 | 13 | 0 | 0 | 7 | 46 | 0/0 (0 casts kept) | 0/0 | 0/0 | {} |
| F-other-multi-body-types | 20 | 16 | 1 | 0 | 3 | 76 | 1/1 (1 casts kept) | 0/1 | 0/1 | {'COUNT': 1} |
| G-single-body-types | 10 | 8 | 0 | 0 | 2 | 51 | 0/0 (0 casts kept) | 0/0 | 0/0 | {} |
| **all** | 165 | 126 | 13 | 3 | 23 | 716 | 13/13 (27 casts kept) | 0/5 | 0/5 | |

**Rung 1 is byte-neutral on 126/139 judged bodies (90.6 %), moving 716 sites; rung S2 (a minimal set of sites kept as casts, delever's rung-B shape) closes 13 of the 13 DIFFERS bodies keeping 27 casts (139/139 = 100.0 % of judged bodies byte-identical with members everywhere but 27 sites); of the 5 DIFFERS bodies that carry marked levers, 0 become IDENTICAL with the struct AND the levers off (the struct hypothesis), of which 0 were already identical with the levers off alone (the struct did not decide those).**

Compile errors / tool errors (top): 'src/ov_SC03_124/ov_SC03_124_jr_80135D20.c:1025: void value not ignored' ×1 · 'src/ov_SC03_125/ov_SC03_125_jr_80135D20.c:788: void value not ignored ' ×1 · 'src/ov_SC03_116/ov_SC03_116_jr_80135D20.c:944: void value not ignored ' ×1

Sites skipped by the rewrite (not converted; counted): {'sign': 44, 'width': 33, 'no-field': 133, 'negative-offset': 3, 'index': 13}
Seconds per body judgement: mean 2.00, max 45.18 (headers judge every includer).

Rows: `.run/P37/probe/probe_rows.jsonl` (per body: tu, fn, base, type, rewritten, skips, verdict, residual, sa).
