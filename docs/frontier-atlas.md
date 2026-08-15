# The Frontier Atlas (P31 T5)

> Generated at HEAD `commit:2390` by `tools/atlas.py` — REGENERATE, never edit. Groups are ADVISORY (the byte-gate is the arbiter). Calibration: warm merge at norm-ratio ≥ 0.7, kNN floor 0.55.

**Scope:** 11484 open instances / 7036 skeletons across 213 binaries (main: 920 — atlas-layer join (family maps stay non-main)).  
**Tiers:** T1.5 h_seqn merges 2 · warm merges 904 (from 19808 ratio calls) · seed sweep: 4739 skeletons carry a ≥0.55 seed from the 3065-skeleton matched pool.

## Groups by category

| cat | groups | instances | ins |
|---|--:|--:|--:|
| A-prop | 393 | 2031 | 87338 |
| cold | 2255 | 2255 | 183323 |
| cousin-multi | 1556 | 5743 | 252128 |
| main-only | 444 | 444 | 38404 |
| seeded | 339 | 846 | 29888 |
| tiny | 99 | 165 | 840 |

## Groups by lever (confidence)

| lever | groups | instances | ins |
|---|--:|--:|--:|
| head-crack[default] | 1090 | 3532 | 151743 |
| UNKNOWN[none] | 1986 | 1986 | 139174 |
| extend-tell[tell] | 579 | 1035 | 77588 |
| jtbl-carve[tell] | 190 | 281 | 45673 |
| redraft[measured] | 267 | 1042 | 44517 |
| family-sweep[default] | 200 | 827 | 28246 |
| integration[measured] | 48 | 503 | 21880 |
| seeded-crack[default] | 256 | 562 | 16919 |
| len-vein[measured] | 148 | 666 | 14310 |
| plumbing[ledger] | 38 | 191 | 9474 |
| swaprepeat-tell[tell] | 70 | 119 | 9316 |
| o0-lane[tell] | 31 | 69 | 6564 |
| cc1[measured] | 12 | 104 | 6382 |
| needs-autopsy[measured] | 52 | 264 | 5095 |
| cc1[ledger] | 14 | 65 | 4586 |
| frame-172[measured] | 8 | 32 | 4078 |
| needs-autopsy[ledger] | 9 | 33 | 3914 |
| near-crack[measured] | 9 | 60 | 1492 |
| tiny-direct[default] | 74 | 106 | 536 |
| s16-div-tell[tell] | 4 | 6 | 419 |
| signload[measured] | 1 | 1 | 15 |

## Top 40 groups by open instructions

| gid | cat | lever | inst | ins | exemplar | seed |
|---|---|---|--:|--:|---|---|
| 315ee3ad198d | cousin-multi | integration[measured] | 255 | 5884 | ov_SC01_084:func_80180CBC (31) | 0.72 |
| e8bf2260391b | cousin-multi | frame-172[measured] | 16 | 3936 | ov_SC01_077:func_8017C294 (246) |  |
| 14bc91cb76b0 | cousin-multi | redraft[measured] | 112 | 2879 | main:func_8001FB8C (31) | 0.72 |
| 4a254010e122 | A-prop | needs-autopsy[ledger] | 4 | 2444 | ov_SC03_001:func_801898E4 (611) | 1.00 |
| aaef26b79169 | A-prop | cc1[measured] | 3 | 2310 | ov_MAIN_012:func_80144B9C (770) | 1.00 |
| e776626310f6 | A-prop | jtbl-carve[tell] | 4 | 2204 | ov_SC03_001:func_8018C000 (551) | 1.00 |
| b017b7f3dac1 | seeded | cc1[measured] | 3 | 2166 | ov_SC06_010:func_8017BEBC (753) | 0.99 |
| c27045659e64 | cousin-multi | head-crack[default] | 16 | 2129 | main:func_80025000 (163) |  |
| 372e98dadcb4 | cousin-multi | o0-lane[tell] | 3 | 1628 | md_MAIN_011:func_800D1254 (555) |  |
| a6899a69a378 | A-prop | integration[measured] | 4 | 1628 | md_SC03_076:func_801EFBB4 (407) | 1.00 |
| cd028c385150 | seeded | integration[measured] | 6 | 1466 | ov_SC07_006:func_8017F9AC (275) | 0.79 |
| 3ffedf1ce9c3 | cousin-multi | integration[measured] | 5 | 1395 | ov_SC01_004:func_8017EB30 (279) |  |
| 4a2cb925563f | cousin-multi | redraft[measured] | 35 | 1380 | ov_SC02_011:func_80189B64 (47) | 0.75 |
| 77b0d495606f | A-prop | plumbing[ledger] | 7 | 1316 | ov_MAIN_012:func_8016AB6C (188) | 1.00 |
| 77a971161066 | A-prop | cc1[ledger] | 7 | 1309 | ov_MAIN_012:func_8013DD68 (187) | 1.00 |
| 3ca25a17fe9b | A-prop | integration[measured] | 4 | 1304 | md_SC03_076:func_801F0F28 (326) | 1.00 |
| b31009fb929c | A-prop | jtbl-carve[tell] | 4 | 1164 | md_SC03_076:func_801F0A9C (291) | 1.00 |
| 9c1a401f457f | main-only | jtbl-carve[tell] | 1 | 1139 | main:SaveLoadRoutine (1139) |  |
| 663648ac9cfb | A-prop | jtbl-carve[tell] | 3 | 1089 | ov_MAIN_012:func_8015444C (363) | 1.00 |
| 1d9aada32e7d | cousin-multi | len-vein[measured] | 44 | 1076 | md_MAIN_003:func_800D2454 (31) | 0.79 |
| 1ff75ac372d6 | A-prop | len-vein[measured] | 4 | 1049 | ov_SC03_028:func_80180494 (270) | 0.95 |
| 93cd03e11398 | A-prop | cc1[ledger] | 11 | 1035 | ov_SC06_032:func_801820C4 (113) | 1.00 |
| 499aeb359ebe | A-prop | len-vein[measured] | 9 | 1021 | ov_SC01_084:func_8017DECC (125) | 0.89 |
| 4109ef56e262 | A-prop | jtbl-carve[tell] | 3 | 987 | ov_MAIN_012:func_8013C414 (329) | 1.00 |
| 435e948b661b | A-prop | extend-tell[tell] | 18 | 979 | ov_SC03_100:func_8017EC84 (67) | 0.84 |
| 75f80de517ba | A-prop | family-sweep[default] | 12 | 964 | md_SC03_079:func_801EFB94 (87) | 0.94 |
| 4f680d0642d8 | A-prop | extend-tell[tell] | 8 | 914 | ov_SC02_011:func_80182B88 (118) | 0.99 |
| dd647efa7db9 | cousin-multi | extend-tell[tell] | 8 | 912 | main:func_8001E378 (188) | 0.59 |
| 9ec470fd06a4 | A-prop | family-sweep[default] | 19 | 908 | ov_SC02_026:func_80182318 (52) | 0.85 |
| c4949914e999 | A-prop | plumbing[ledger] | 7 | 889 | ov_MAIN_012:func_80145CEC (127) | 1.00 |
| 8a879fea07f9 | A-prop | integration[measured] | 4 | 872 | md_SC03_076:func_801F0734 (218) | 1.00 |
| 861af215f885 | cousin-multi | head-crack[default] | 3 | 853 | ov_SC01_001:func_8017F328 (307) |  |
| ab2d7c7ccb56 | A-prop | jtbl-carve[tell] | 3 | 816 | ov_MAIN_012:func_8013B83C (272) | 1.00 |
| b608b4411778 | cousin-multi | integration[measured] | 73 | 815 | md_SC07_003:func_801A38A8 (15) | 0.90 |
| 79d4e25b5763 | cousin-multi | o0-lane[tell] | 2 | 811 | md_MAIN_011:func_800D0BDC (414) |  |
| 78627a0eec5d | cousin-multi | redraft[measured] | 10 | 810 | ov_SC01_004:func_8017D964 (84) | 0.62 |
| b1509c2e091c | A-prop | integration[measured] | 3 | 798 | ov_MAIN_012:func_80130D48 (266) | 1.00 |
| 97e813dd2393 | cousin-multi | integration[measured] | 4 | 784 | ov_SC03_108:func_8017FFD0 (196) | 0.65 |
| 55dc506d7ba5 | cousin-multi | head-crack[default] | 5 | 783 | main:func_80025504 (197) |  |
| dcc70a8601c4 | cousin-multi | head-crack[default] | 15 | 767 | ov_SC03_028:func_8018966C (63) | 0.67 |
