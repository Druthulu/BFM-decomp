# Disc ledger — the completeness partition (L1)

> `tools/disc_audit.py` (`make audit-disc`). Walks the DISC IMAGE, not our configs;
> classifies WHOLE payloads (no window) at BOTH the raw and LZSS-decompressed layer.
> `claimed-by` is derived from `config/check.<bin>.sha` — the build's own
> byte-identity gate (R33). Residue is a DEFECT (R32), not a rounding note.

**Disc:** 416,021,760 bytes · 4 tracks · 1,291 payloads examined

| bucket | bytes | share |
|---|---:|---:|
| onboarded-code | 32,564,876 | 7.83% |
| unclaimed-code | 1,700,049 | 0.41% |
| classified-data | 150,631,480 | 36.21% |
| audio-video | 184,338,000 | 44.31% |
| filesystem-metadata | 46,787,355 | 11.25% |
| **TOTAL** | **416,021,760** | 100.00% |

**Residue: 0 bytes — PARTITION HOLDS**

## Code payloads — 34 UNCLAIMED of 139

| file | entry | type | bytes | bucket | claimed-by | valid/jr |
|---|---|---|---:|---|---|---|
| MAIN.CD/12 | 1 | 1 | 383,783 | unclaimed-code | UNCLAIMED | 0.99/0.0250 |
| MAIN.CD/14 | 1 | 1 | 2,088 | unclaimed-code | UNCLAIMED | 0.99/0.0249 |
| MAIN.CD/16 | 1 | 1 | 1,928 | unclaimed-code | UNCLAIMED | 0.99/0.0270 |
| MAIN.CD/17 | 1 | 1 | 1,492 | unclaimed-code | UNCLAIMED | 0.97/0.0268 |
| MAIN.CD/18 | 1 | 1 | 2,712 | unclaimed-code | UNCLAIMED | 0.96/0.0162 |
| MAIN.CD/19 | 1 | 1 | 6,760 | unclaimed-code | UNCLAIMED | 0.94/0.0130 |
| MAIN.CD/21 | 1 | 1 | 1,936 | unclaimed-code | UNCLAIMED | 0.99/0.0227 |
| MAIN.CD/22 | 1 | 1 | 4,072 | unclaimed-code | UNCLAIMED | 1.00/0.0324 |
| MAIN.CD/23 | 0 | 1 | 388 | unclaimed-code | UNCLAIMED | 0.99/0.0619 |
| MAIN.CD/24 | 0 | 1 | 332 | unclaimed-code | UNCLAIMED | 0.99/0.0723 |
| MAIN.CD/26 | 1 | 1 | 3,600 | unclaimed-code | UNCLAIMED | 0.99/0.0267 |
| MAIN.CD/27 | 1 | 1 | 5,272 | unclaimed-code | UNCLAIMED | 0.98/0.0220 |
| MAIN.CD/28 | 1 | 1 | 4,460 | unclaimed-code | UNCLAIMED | 0.99/0.0197 |
| MAIN.CD/29 | 1 | 1 | 1,984 | unclaimed-code | UNCLAIMED | 0.98/0.0222 |
| MAIN.CD/30 | 1 | 1 | 1,876 | unclaimed-code | UNCLAIMED | 0.98/0.0213 |
| MAIN.CD/31 | 1 | 1 | 5,044 | unclaimed-code | UNCLAIMED | 0.97/0.0143 |
| MAIN.CD/33 | 1 | 1 | 3,264 | unclaimed-code | UNCLAIMED | 0.99/0.0233 |
| MAIN.CD/34 | 1 | 1 | 7,444 | unclaimed-code | UNCLAIMED | 0.92/0.0150 |
| MAIN.CD/35 | 1 | 1 | 1,248 | unclaimed-code | UNCLAIMED | 0.97/0.0513 |
| MAIN.CD/36 | 1 | 1 | 4,916 | unclaimed-code | UNCLAIMED | 0.99/0.0228 |
| MAIN.CD/37 | 1 | 1 | 2,904 | unclaimed-code | UNCLAIMED | 0.90/0.0234 |
| MAIN.CD/39 | 1 | 1 | 5,700 | unclaimed-code | UNCLAIMED | 0.97/0.0182 |
| MAIN.CD/40 | 1 | 1 | 3,956 | unclaimed-code | UNCLAIMED | 0.98/0.0192 |
| MAIN.CD/41 | 1 | 1 | 4,100 | unclaimed-code | UNCLAIMED | 0.97/0.0146 |
| MAIN.CD/42 | 0 | 1 | 636 | unclaimed-code | UNCLAIMED | 1.00/0.0252 |
| MAIN.CD/43 | 0 | 1 | 3,912 | unclaimed-code | UNCLAIMED | 1.00/0.0235 |
| MAIN.CD/44 | 0 | 1 | 8,920 | unclaimed-code | UNCLAIMED | 0.98/0.0197 |
| MAIN.CD/45 | 0 | 1 | 5,432 | unclaimed-code | UNCLAIMED | 0.97/0.0155 |
| MAIN.CD/46 | 0 | 1 | 7,612 | unclaimed-code | UNCLAIMED | 0.94/0.0205 |
| MAIN.CD/47 | 0 | 1 | 3,272 | unclaimed-code | UNCLAIMED | 1.00/0.0147 |
| MAIN.CD/8 | 1 | 1 | 840 | unclaimed-code | UNCLAIMED | 1.00/0.0286 |
| MAIN.CD/9 | 0 | 1 | 2,544 | unclaimed-code | UNCLAIMED | 0.99/0.0189 |
| SC02.CD/37 | 0 | 1 | 661,903 | unclaimed-code | UNCLAIMED | 0.91/0.0152 |
| SC03.CD/107 | 0 | 1 | 474,087 | unclaimed-code | UNCLAIMED | 0.97/0.0211 |
| SC01.CD/0 | 0 | 4 | 513,935 | onboarded-code | ov_SC01_000 | 0.95/0.0187 |
| SC01.CD/4 | 0 | 4 | 426,615 | onboarded-code | ov_SC01_004 | 0.97/0.0227 |
| SC01.CD/74 | 0 | 4 | 474,135 | onboarded-code | ov_SC01_074 | 0.96/0.0205 |
| SC01.CD/80 | 0 | 4 | 654,839 | onboarded-code | ov_SC01_080 | 0.94/0.0154 |
| SC01.CD/84 | 0 | 4 | 653,983 | onboarded-code | ov_SC01_084 | 0.90/0.0158 |
| SC02.CD/15 | 0 | 4 | 427,335 | onboarded-code | ov_SC02_015 | 0.98/0.0226 |
| SC02.CD/16 | 0 | 4 | 575,871 | onboarded-code | ov_SC02_016 | 0.93/0.0177 |
| SC02.CD/21 | 0 | 4 | 440,135 | onboarded-code | ov_SC02_021 | 0.97/0.0222 |
| SC02.CD/27 | 0 | 4 | 731,367 | onboarded-code | ov_SC02_027 | 0.90/0.0147 |
| SC02.CD/28 | 0 | 4 | 701,671 | onboarded-code | ov_SC02_028 | 0.91/0.0154 |
| SC02.CD/31 | 0 | 4 | 588,215 | onboarded-code | ov_SC02_031 | 0.91/0.0174 |
| SC02.CD/35 | 0 | 4 | 616,687 | onboarded-code | ov_SC02_035 | 0.91/0.0164 |
| SC02.CD/39 | 0 | 4 | 494,759 | onboarded-code | ov_SC02_039 | 0.95/0.0195 |
| SC02.CD/4 | 0 | 4 | 451,183 | onboarded-code | ov_SC02_004 | 0.97/0.0213 |
| SC02.CD/41 | 0 | 4 | 595,327 | onboarded-code | ov_SC02_041 | 0.91/0.0172 |
| SC03.CD/1 | 0 | 4 | 815,887 | onboarded-code | ov_SC03_001 | 0.91/0.0141 |
| SC03.CD/10 | 0 | 4 | 491,639 | onboarded-code | ov_SC03_010 | 0.96/0.0201 |
| SC03.CD/100 | 0 | 4 | 657,423 | onboarded-code | ov_SC03_100 | 0.90/0.0155 |
| SC03.CD/101 | 0 | 4 | 483,535 | onboarded-code | ov_SC03_101 | 0.97/0.0209 |
| SC03.CD/102 | 0 | 4 | 596,687 | onboarded-code | ov_SC03_102 | 0.91/0.0167 |
| SC03.CD/103 | 0 | 4 | 642,175 | onboarded-code | ov_SC03_103 | 0.91/0.0156 |
| SC03.CD/104 | 0 | 4 | 623,423 | onboarded-code | ov_SC03_104 | 0.91/0.0168 |
| SC03.CD/108 | 0 | 4 | 497,999 | onboarded-code | ov_SC03_108 | 0.95/0.0196 |
| SC03.CD/109 | 0 | 4 | 467,799 | onboarded-code | ov_SC03_109 | 0.96/0.0207 |
| SC03.CD/11 | 0 | 4 | 500,395 | onboarded-code | ov_SC03_011 | 0.95/0.0202 |
| SC03.CD/110 | 0 | 4 | 500,615 | onboarded-code | ov_SC03_110 | 0.95/0.0197 |
| SC03.CD/111 | 0 | 4 | 596,527 | onboarded-code | ov_SC03_111 | 0.93/0.0168 |
| SC03.CD/112 | 0 | 4 | 544,759 | onboarded-code | ov_SC03_112 | 0.95/0.0186 |
| SC03.CD/113 | 0 | 4 | 514,967 | onboarded-code | ov_SC03_113 | 0.95/0.0192 |
| SC03.CD/114 | 0 | 4 | 530,191 | onboarded-code | ov_SC03_114 | 0.93/0.0182 |
| SC03.CD/115 | 0 | 4 | 446,439 | onboarded-code | ov_SC03_115 | 0.97/0.0222 |
| SC03.CD/116 | 0 | 4 | 457,719 | onboarded-code | ov_SC03_116 | 0.98/0.0213 |
| SC03.CD/117 | 0 | 4 | 681,967 | onboarded-code | ov_SC03_117 | 0.92/0.0150 |
| SC03.CD/118 | 0 | 4 | 706,295 | onboarded-code | ov_SC03_119 | 0.90/0.0152 |
| SC03.CD/119 | 0 | 4 | 706,295 | onboarded-code | ov_SC03_119 | 0.90/0.0152 |
| SC03.CD/12 | 0 | 4 | 446,471 | onboarded-code | ov_SC03_012 | 0.98/0.0216 |
| SC03.CD/124 | 0 | 4 | 763,023 | onboarded-code | ov_SC03_124 | 0.91/0.0144 |
| SC03.CD/125 | 0 | 4 | 639,975 | onboarded-code | ov_SC03_125 | 0.92/0.0162 |
| SC03.CD/126 | 0 | 4 | 424,405 | onboarded-code | ov_SC03_126 | 0.97/0.0229 |
| SC03.CD/13 | 0 | 4 | 545,791 | onboarded-code | ov_SC03_013 | 0.94/0.0183 |
| SC03.CD/2 | 0 | 4 | 670,199 | onboarded-code | ov_SC03_002 | 0.91/0.0157 |
| SC03.CD/23 | 0 | 4 | 461,871 | onboarded-code | ov_SC03_023 | 0.97/0.0211 |
| SC03.CD/24 | 0 | 4 | 628,471 | onboarded-code | ov_SC03_024 | 0.91/0.0168 |
| SC03.CD/29 | 0 | 4 | 727,279 | onboarded-code | ov_SC03_029 | 0.93/0.0146 |
| SC03.CD/3 | 0 | 4 | 424,485 | onboarded-code | ov_SC03_003 | 0.97/0.0229 |
| SC03.CD/31 | 0 | 4 | 647,503 | onboarded-code | ov_SC03_031 | 0.94/0.0155 |
| SC03.CD/89 | 0 | 4 | 649,159 | onboarded-code | ov_SC03_089 | 0.91/0.0159 |
| SC03.CD/92 | 0 | 4 | 569,135 | onboarded-code | ov_SC03_092 | 0.93/0.0182 |
| SC03.CD/95 | 0 | 4 | 474,431 | onboarded-code | ov_SC03_095 | 0.95/0.0209 |
| SC03.CD/96 | 0 | 4 | 468,983 | onboarded-code | ov_SC03_096 | 0.95/0.0210 |
| SC03.CD/97 | 0 | 4 | 535,927 | onboarded-code | ov_SC03_097 | 0.94/0.0194 |
| SC03.CD/98 | 0 | 4 | 644,959 | onboarded-code | ov_SC03_098 | 0.90/0.0158 |
| SC03.CD/99 | 0 | 4 | 619,271 | onboarded-code | ov_SC03_099 | 0.91/0.0162 |
| SC04.CD/0 | 0 | 4 | 536,319 | onboarded-code | ov_SC04_000 | 0.95/0.0190 |
| SC04.CD/10 | 0 | 4 | 423,407 | onboarded-code | ov_SC04_010 | 0.97/0.0229 |
| SC04.CD/12 | 0 | 4 | 438,503 | onboarded-code | ov_SC04_012 | 0.96/0.0221 |
| SC04.CD/15 | 0 | 4 | 660,103 | onboarded-code | ov_SC04_015 | 0.92/0.0158 |
| SC04.CD/16 | 0 | 4 | 541,063 | onboarded-code | ov_SC04_016 | 0.95/0.0181 |
| SC04.CD/18 | 0 | 4 | 784,847 | onboarded-code | ov_SC04_019 | 0.92/0.0146 |
| SC04.CD/19 | 0 | 4 | 784,847 | onboarded-code | ov_SC04_019 | 0.92/0.0146 |
| SC04.CD/2 | 0 | 4 | 628,191 | onboarded-code | ov_SC04_002 | 0.91/0.0168 |
| SC04.CD/20 | 0 | 4 | 607,831 | onboarded-code | ov_SC04_020 | 0.92/0.0169 |
| SC04.CD/21 | 0 | 4 | 424,405 | onboarded-code | ov_SC04_021 | 0.97/0.0229 |
| SC04.CD/3 | 0 | 4 | 473,751 | onboarded-code | ov_SC04_003 | 0.97/0.0211 |
| SC04.CD/4 | 0 | 4 | 572,159 | onboarded-code | ov_SC04_004 | 0.92/0.0179 |
| SC04.CD/5 | 0 | 4 | 631,255 | onboarded-code | ov_SC04_005 | 0.90/0.0166 |
| SC04.CD/6 | 0 | 4 | 482,423 | onboarded-code | ov_SC04_006 | 0.95/0.0204 |
| SC04.CD/7 | 0 | 4 | 580,151 | onboarded-code | ov_SC04_007 | 0.92/0.0177 |
| SC04.CD/8 | 0 | 4 | 439,143 | onboarded-code | ov_SC04_008 | 0.97/0.0220 |
| SC04.CD/9 | 0 | 4 | 459,031 | onboarded-code | ov_SC04_009 | 0.97/0.0213 |
| SC05.CD/0 | 0 | 4 | 469,759 | onboarded-code | ov_SC05_000 | 0.96/0.0206 |
| SC05.CD/1 | 0 | 4 | 581,295 | onboarded-code | ov_SC05_001 | 0.95/0.0177 |
| SC05.CD/11 | 0 | 4 | 479,367 | onboarded-code | ov_SC05_011 | 0.94/0.0201 |
| SC05.CD/17 | 0 | 4 | 809,007 | onboarded-code | ov_SC05_017 | 0.91/0.0141 |
| SC05.CD/19 | 0 | 4 | 424,405 | onboarded-code | ov_SC05_019 | 0.97/0.0229 |
| SC05.CD/2 | 0 | 4 | 491,111 | onboarded-code | ov_SC05_002 | 0.96/0.0199 |
| SC05.CD/3 | 0 | 4 | 543,095 | onboarded-code | ov_SC05_003 | 0.94/0.0183 |
| SC05.CD/4 | 0 | 4 | 487,887 | onboarded-code | ov_SC05_004 | 0.96/0.0202 |
| SC05.CD/5 | 0 | 4 | 564,951 | onboarded-code | ov_SC05_005 | 0.93/0.0177 |
| SC05.CD/6 | 0 | 4 | 425,991 | onboarded-code | ov_SC05_006 | 0.98/0.0228 |
| SC05.CD/7 | 0 | 4 | 478,631 | onboarded-code | ov_SC05_007 | 0.96/0.0208 |
| SC05.CD/8 | 0 | 4 | 496,019 | onboarded-code | ov_SC05_008 | 0.97/0.0205 |
| SC05.CD/9 | 0 | 4 | 453,359 | onboarded-code | ov_SC05_009 | 0.97/0.0215 |
| SC06.CD/0 | 0 | 4 | 565,295 | onboarded-code | ov_SC06_000 | 0.95/0.0190 |
| SC06.CD/10 | 0 | 4 | 568,103 | onboarded-code | ov_SC06_010 | 0.96/0.0177 |
| SC06.CD/11 | 0 | 4 | 539,647 | onboarded-code | ov_SC06_011 | 0.93/0.0183 |
| SC06.CD/13 | 0 | 4 | 469,679 | onboarded-code | ov_SC06_013 | 0.96/0.0207 |
| SC06.CD/14 | 0 | 4 | 496,839 | onboarded-code | ov_SC06_014 | 0.96/0.0198 |
| SC06.CD/15 | 0 | 4 | 444,583 | onboarded-code | ov_SC06_015 | 0.97/0.0218 |
| SC06.CD/16 | 0 | 4 | 491,799 | onboarded-code | ov_SC06_016 | 0.96/0.0207 |
| SC06.CD/18 | 0 | 4 | 711,239 | onboarded-code | ov_SC06_018 | 0.91/0.0150 |
| SC06.CD/20 | 0 | 4 | 600,215 | onboarded-code | ov_SC06_020 | 0.92/0.0168 |
| SC06.CD/25 | 0 | 4 | 565,551 | onboarded-code | ov_SC06_025 | 0.93/0.0182 |
| SC06.CD/27 | 0 | 4 | 479,959 | onboarded-code | ov_SC06_027 | 0.96/0.0201 |
| SC06.CD/32 | 0 | 4 | 692,247 | onboarded-code | ov_SC06_032 | 0.92/0.0154 |
| SC06.CD/33 | 0 | 4 | 691,863 | onboarded-code | ov_SC06_033 | 0.92/0.0152 |
| SC06.CD/8 | 0 | 4 | 534,239 | onboarded-code | ov_SC06_008 | 0.96/0.0190 |
| SC07.CD/1 | 0 | 4 | 535,991 | onboarded-code | ov_SC07_001 | 0.93/0.0183 |
| SC07.CD/10 | 1 | 4 | 529,391 | onboarded-code | ov_SC07_010 | 0.94/0.0191 |
| SC07.CD/11 | 1 | 4 | 426,919 | onboarded-code | ov_SC07_011 | 0.98/0.0230 |
| SC07.CD/2 | 0 | 4 | 491,391 | onboarded-code | ov_SC07_002 | 0.98/0.0210 |
| SC07.CD/7 | 1 | 4 | 653,791 | onboarded-code | ov_SC07_007 | 0.91/0.0160 |
| SC07.CD/8 | 0 | 4 | 452,079 | onboarded-code | ov_SC07_008 | 0.97/0.0211 |
| SC07.CD/9 | 0 | 4 | 507,007 | onboarded-code | ov_SC07_009 | 0.95/0.0192 |
| SLUS_007.26 | - | - | 413,696 | onboarded-code | us | 0.96/0.0143 |
