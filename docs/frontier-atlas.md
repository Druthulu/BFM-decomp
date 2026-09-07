# The Frontier Atlas (P31 T5)

> Generated at HEAD `252dc930c` by `tools/atlas.py` — REGENERATE, never edit. Groups are ADVISORY (the byte-gate is the arbiter). Calibration: warm merge at norm-ratio ≥ 0.7, kNN floor 0.55.

**Scope:** 2520 open instances / 1931 skeletons across 213 binaries (main: 151 — atlas-layer join (family maps stay non-main)).  
**Tiers:** T1.5 h_seqn merges 0 · warm merges 164 (from 3399 ratio calls) · seed sweep: 1443 skeletons carry a ≥0.55 seed from the 7700-skeleton matched pool.

## Groups by category

| cat | groups | instances | ins |
|---|--:|--:|--:|
| A-prop | 484 | 1011 | 50203 |
| cold | 678 | 678 | 75974 |
| cousin-multi | 141 | 485 | 32621 |
| main-only | 121 | 121 | 20670 |
| seeded | 167 | 217 | 12056 |
| tiny | 5 | 8 | 32 |

## Groups by lever (confidence)

| lever | groups | instances | ins |
|---|--:|--:|--:|
| extend-tell[tell] | 288 | 403 | 42420 |
| UNKNOWN[none] | 385 | 385 | 35457 |
| remap[aprop-pure] | 365 | 666 | 33878 |
| jtbl-carve[tell] | 133 | 146 | 27872 |
| integration[measured] | 14 | 38 | 6713 |
| seeded-crack[default] | 138 | 175 | 6614 |
| redraft[measured] | 51 | 134 | 6504 |
| head-crack[default] | 53 | 133 | 6400 |
| swaprepeat-tell[tell] | 40 | 53 | 5782 |
| cc1[measured] | 3 | 9 | 4563 |
| frame-172[measured] | 4 | 21 | 3976 |
| len-vein[measured] | 25 | 134 | 3323 |
| o0-lane[tell] | 14 | 19 | 3050 |
| family-sweep[default] | 45 | 97 | 2581 |
| needs-autopsy[measured] | 21 | 74 | 1049 |
| near-crack[measured] | 4 | 6 | 531 |
| plumbing[ledger] | 5 | 17 | 354 |
| s16-div-tell[tell] | 2 | 3 | 249 |
| needs-autopsy[ledger] | 3 | 4 | 219 |
| signload[measured] | 1 | 1 | 15 |
| tiny-direct[default] | 2 | 2 | 6 |

## Top 40 groups by open instructions

| gid | cat | lever | inst | ins | exemplar | seed |
|---|---|---|--:|--:|---|---|
| e8bf2260391b | cousin-multi | frame-172[measured] | 16 | 3936 | ov_SC01_077:func_8017C294 (246) |  |
| aaef26b79169 | A-prop | cc1[measured] | 3 | 2310 | ov_MAIN_012:func_80144B9C (770) | 1.00 |
| b017b7f3dac1 | seeded | cc1[measured] | 3 | 2166 | ov_SC06_010:func_8017BEBC (753) | 0.99 |
| 2cacbfbd41a5 | cousin-multi | len-vein[measured] | 85 | 1941 | ov_SC06_025:func_801808AC (41) | 0.69 |
| a6899a69a378 | A-prop | integration[measured] | 4 | 1628 | md_SC03_076:func_801EFBB4 (407) | 1.00 |
| 3ffedf1ce9c3 | cousin-multi | integration[measured] | 5 | 1395 | ov_SC01_004:func_8017EB30 (279) |  |
| 3ca25a17fe9b | A-prop | integration[measured] | 4 | 1304 | md_SC03_076:func_801F0F28 (326) | 1.00 |
| b31009fb929c | A-prop | remap[aprop-pure] | 4 | 1164 | md_SC03_076:func_801F0A9C (291) | 1.00 |
| 9c1a401f457f | main-only | jtbl-carve[tell] | 1 | 1139 | main:SaveLoadRoutine (1139) |  |
| d877f58f25f7 | A-prop | remap[aprop-pure] | 6 | 1122 | ov_SC02_037:func_8013DD68 (187) | 1.00 |
| 663648ac9cfb | A-prop | remap[aprop-pure] | 3 | 1089 | ov_MAIN_012:func_8015444C (363) | 1.00 |
| 3972eded92e6 | cousin-multi | extend-tell[tell] | 30 | 951 | ov_SC06_025:func_80182D4C (50) | 0.80 |
| 558b1ceb7ea4 | A-prop | remap[aprop-pure] | 5 | 940 | ov_SC03_107:func_8016AB6C (188) | 1.00 |
| 8a879fea07f9 | A-prop | integration[measured] | 4 | 872 | md_SC03_076:func_801F0734 (218) | 1.00 |
| 946751928cba | A-prop | remap[aprop-pure] | 6 | 762 | ov_SC02_037:func_80145CEC (127) | 1.00 |
| bb7d0989abd9 | main-only | UNKNOWN[none] | 1 | 670 | main:func_800226C0 (670) |  |
| 3485a1d085bf | main-only | jtbl-carve[tell] | 1 | 663 | main:func_8003388C (663) |  |
| c75a0ef88fd3 | cold | o0-lane[tell] | 1 | 657 | md_MAIN_003:func_800D12D0 (657) |  |
| d81c43788527 | cousin-multi | extend-tell[tell] | 6 | 614 | main:func_8001382C (103) | 0.89 |
| ad0ca118d60b | cousin-multi | head-crack[default] | 2 | 602 | ov_SC01_001:func_8017FEE0 (305) | 0.61 |
| f839f6bc5b7e | cousin-multi | redraft[measured] | 3 | 599 | ov_SC03_006:func_801823B8 (205) | 0.84 |
| 8d284618c877 | cold | jtbl-carve[tell] | 1 | 575 | md_MAIN_011:func_800CF28C (575) |  |
| df63953c182c | cold | UNKNOWN[none] | 1 | 556 | ov_SC06_024:func_8017EC4C (556) |  |
| 3c5e007c30ad | seeded | o0-lane[tell] | 1 | 555 | md_MAIN_011:func_800D1254 (555) | 0.92 |
| 4ca3c47c0040 | A-prop | remap[aprop-pure] | 1 | 551 | ov_SC05_017:func_80189240 (551) | 1.00 |
| 550895e233e4 | cousin-multi | head-crack[default] | 2 | 546 | ov_SC01_001:func_801810A4 (282) | 0.66 |
| e30972e4d8ac | cousin-multi | extend-tell[tell] | 6 | 546 | ov_SC06_018:func_80189E60 (91) | 0.64 |
| 94f25b1776a9 | cold | jtbl-carve[tell] | 1 | 541 | ov_SC01_000:func_8017D490 (541) |  |
| 3a25ed87930a | cousin-multi | jtbl-carve[tell] | 2 | 537 | ov_SC06_029:func_8017F9C0 (294) |  |
| 43fbeba73177 | cousin-multi | extend-tell[tell] | 2 | 537 | ov_SC07_002:func_80181394 (275) |  |
| 121054797c89 | A-prop | remap[aprop-pure] | 2 | 532 | ov_SC02_037:func_80130D48 (266) | 1.00 |
| 6696298f0a57 | cold | jtbl-carve[tell] | 1 | 531 | md_SC07_004:func_801A2400 (531) |  |
| f162d4d89665 | main-only | extend-tell[tell] | 1 | 518 | main:func_80039308 (518) |  |
| 6b6b49f1d255 | cold | swaprepeat-tell[tell] | 1 | 512 | ov_SC02_021:func_8017DC10 (512) |  |
| b652186dbe7a | cold | jtbl-carve[tell] | 1 | 506 | ov_SC03_024:func_801830A8 (506) |  |
| 3b86b970ec1d | cousin-multi | extend-tell[tell] | 5 | 501 | ov_SC05_005:func_8017EAEC (107) | 0.68 |
| dff1c46d6c36 | A-prop | redraft[measured] | 12 | 485 | ov_SC03_117:func_8017E118 (49) | 0.93 |
| 574dc0e1b9c5 | cold | UNKNOWN[none] | 1 | 479 | ov_SC03_121:func_8017E880 (479) |  |
| 99d5623e6bf6 | A-prop | len-vein[measured] | 5 | 470 | ov_SC06_018:func_801874E4 (94) | 1.00 |
| b6ea26c82199 | cold | UNKNOWN[none] | 1 | 469 | md_MAIN_003:func_800CF3E8 (469) |  |
