# Disc ledger — the completeness partition (L1)

> `tools/disc_audit.py` (`make audit-disc`). Walks the DISC IMAGE, not our configs;
> classifies WHOLE payloads (no window) at BOTH the raw and LZSS-decompressed layer.
> `claimed-by` is derived from `config/check.<bin>.sha` — the build's own
> byte-identity gate (R33). Residue is a DEFECT (R32), not a rounding note.

**Disc:** 416,021,760 bytes · 4 tracks · 1,291 payloads examined

| bucket | bytes | share |
|---|---:|---:|
| onboarded-code | 50,839,845 | 12.22% |
| unclaimed-code | 38,852 | 0.01% |
| classified-data | 134,017,708 | 32.21% |
| audio-video | 184,338,000 | 44.31% |
| filesystem-metadata | 46,787,355 | 11.25% |
| **TOTAL** | **416,021,760** | 100.00% |

**Residue: 0 bytes — PARTITION HOLDS**

## L2 review queue — 80 oracle disagreement(s)

> L1 = statistical heuristic (valid>=0.90 AND jr>=0.01). L2 = independent boundary
> carving (sig_image `func_end` walk). R34: the two are made to ARGUE; a disagreement
> is a review item, never silently resolved. L1=data/L2=code is the DANGEROUS
> direction — that is missed code.

| file | entry | type | bytes | L1 | L2 | fns carved | valid/jr |
|---|---|---|---:|---|---|---:|---|
| SC06.CD/6 | 0 | 4 | 854,543 | data | code | 3 | 0.87/0.0118 |
| SC03.CD/6 | 0 | 4 | 849,759 | data | code | 3 | 0.87/0.0130 |
| SC07.CD/6 | 1 | 4 | 844,311 | data | code | 3 | 0.84/0.0116 |
| SC01.CD/9 | 0 | 4 | 832,263 | data | code | 3 | 0.85/0.0121 |
| SC01.CD/1 | 0 | 4 | 831,599 | data | code | 3 | 0.74/0.0119 |
| SC04.CD/11 | 0 | 4 | 824,663 | data | code | 3 | 0.79/0.0136 |
| SC02.CD/17 | 0 | 4 | 818,143 | data | code | 3 | 0.89/0.0134 |
| SC03.CD/28 | 0 | 4 | 804,015 | data | code | 3 | 0.88/0.0133 |
| SC02.CD/11 | 0 | 4 | 801,063 | data | code | 3 | 0.89/0.0145 |
| SC03.CD/7 | 0 | 4 | 799,087 | data | code | 3 | 0.88/0.0131 |
| SC03.CD/14 | 0 | 4 | 798,439 | data | code | 3 | 0.87/0.0135 |
| SC03.CD/15 | 0 | 4 | 798,439 | data | code | 3 | 0.87/0.0135 |
| SC02.CD/0 | 0 | 4 | 788,239 | data | code | 3 | 0.90/0.0136 |
| SC02.CD/3 | 0 | 4 | 788,239 | data | code | 3 | 0.90/0.0136 |
| SC05.CD/18 | 0 | 4 | 780,087 | data | code | 3 | 0.83/0.0137 |
| SC02.CD/5 | 0 | 4 | 772,865 | data | code | 3 | 0.87/0.0152 |
| SC06.CD/22 | 0 | 4 | 762,135 | data | code | 3 | 0.89/0.0139 |
| SC06.CD/29 | 0 | 4 | 761,911 | data | code | 3 | 0.90/0.0140 |
| SC03.CD/30 | 0 | 4 | 760,560 | data | code | 3 | 0.90/0.0131 |
| SC06.CD/24 | 0 | 4 | 759,823 | data | code | 3 | 0.89/0.0141 |
| SC01.CD/77 | 0 | 4 | 731,607 | data | code | 3 | 0.89/0.0141 |
| SC03.CD/94 | 0 | 4 | 700,735 | data | code | 3 | 0.89/0.0147 |
| SC03.CD/91 | 0 | 4 | 697,735 | data | code | 3 | 0.90/0.0151 |
| SC07.CD/0 | 0 | 4 | 691,087 | data | code | 3 | 0.89/0.0146 |
| SC02.CD/26 | 0 | 4 | 688,487 | data | code | 3 | 0.90/0.0150 |
| SC01.CD/5 | 0 | 4 | 679,689 | data | code | 3 | 0.88/0.0147 |
| SC01.CD/6 | 0 | 4 | 679,689 | data | code | 3 | 0.88/0.0147 |
| SC03.CD/93 | 0 | 4 | 673,159 | data | code | 3 | 0.89/0.0152 |
| SC03.CD/90 | 0 | 4 | 670,775 | data | code | 3 | 0.90/0.0157 |
| SC05.CD/10 | 0 | 4 | 655,063 | data | code | 3 | 0.89/0.0158 |
| SC03.CD/105 | 0 | 4 | 609,223 | data | code | 3 | 0.89/0.0171 |
| SC06.CD/30 | 0 | 4 | 597,807 | data | code | 3 | 0.84/0.0164 |
| SC03.CD/121 | 0 | 4 | 552,535 | data | code | 3 | 0.90/0.0178 |
| SC01.CD/8 | 0 | 4 | 504,967 | data | code | 3 | 0.88/0.0192 |
| MAIN.CD/10 | 1 | 1 | 365,404 | data | code | 3 | 0.72/0.0016 |
| SC07.CD/4 | 1 | 1 | 365,152 | data | code | 3 | 0.84/0.0035 |
| SC07.CD/3 | 1 | 1 | 345,132 | data | code | 3 | 0.57/0.0012 |
| SC02.CD/9 | 0 | 1 | 70,784 | data | code | 3 | 0.70/0.0023 |
| SC05.CD/26 | 2 | 1 | 43,816 | data | code | 3 | 0.88/0.0060 |
| SC04.CD/27 | 2 | 1 | 43,776 | data | code | 3 | 0.88/0.0060 |
| SC03.CD/76 | 2 | 1 | 43,760 | data | code | 3 | 0.88/0.0060 |
| SC03.CD/138 | 2 | 1 | 40,164 | data | code | 3 | 0.79/0.0037 |
| SC05.CD/29 | 2 | 1 | 39,396 | data | code | 3 | 0.79/0.0031 |
| SC04.CD/30 | 2 | 1 | 39,356 | data | code | 3 | 0.79/0.0032 |
| SC03.CD/79 | 2 | 1 | 39,340 | data | code | 3 | 0.79/0.0032 |
| SC03.CD/135 | 2 | 1 | 34,828 | data | code | 3 | 0.87/0.0076 |
| SC05.CD/27 | 2 | 1 | 32,792 | data | code | 3 | 0.79/0.0043 |
| SC03.CD/77 | 2 | 1 | 32,768 | data | code | 3 | 0.79/0.0043 |
| SC04.CD/28 | 2 | 1 | 32,752 | data | code | 3 | 0.79/0.0043 |
| SC03.CD/136 | 2 | 1 | 32,712 | data | code | 3 | 0.79/0.0043 |
| SC05.CD/25 | 2 | 1 | 30,848 | data | code | 3 | 0.82/0.0053 |
| SC03.CD/134 | 2 | 1 | 30,808 | data | code | 3 | 0.82/0.0053 |
| SC04.CD/26 | 2 | 1 | 30,808 | data | code | 3 | 0.82/0.0053 |
| SC03.CD/75 | 2 | 1 | 30,792 | data | code | 3 | 0.82/0.0053 |
| SC05.CD/23 | 2 | 1 | 29,168 | data | code | 3 | 0.79/0.0038 |
| SC04.CD/24 | 2 | 1 | 29,120 | data | code | 3 | 0.79/0.0038 |
| SC03.CD/73 | 2 | 1 | 29,112 | data | code | 3 | 0.79/0.0038 |
| SC03.CD/132 | 2 | 1 | 29,080 | data | code | 3 | 0.79/0.0039 |
| SC05.CD/24 | 2 | 1 | 27,352 | data | code | 3 | 0.83/0.0042 |
| SC04.CD/25 | 2 | 1 | 27,312 | data | code | 3 | 0.83/0.0042 |
| SC03.CD/74 | 2 | 1 | 27,296 | data | code | 3 | 0.83/0.0042 |
| SC03.CD/133 | 2 | 1 | 27,272 | data | code | 3 | 0.83/0.0043 |
| MAIN.CD/11 | 1 | 1 | 24,240 | data | code | 3 | 0.95/0.0035 |
| MAIN.CD/0 | 0 | 1 | 19,996 | data | code | 3 | 0.73/0.0022 |
| MAIN.CD/1 | 1 | 1 | 19,996 | data | code | 3 | 0.73/0.0022 |
| SC05.CD/28 | 2 | 1 | 15,732 | data | code | 3 | 0.84/0.0069 |
| SC04.CD/29 | 2 | 1 | 15,692 | data | code | 3 | 0.84/0.0069 |
| SC03.CD/78 | 2 | 1 | 15,676 | data | code | 3 | 0.84/0.0069 |
| SC03.CD/137 | 2 | 1 | 15,652 | data | code | 3 | 0.83/0.0069 |
| MAIN.CD/7 | -1 | -1 | 9,600 | data | code | 3 | 0.99/0.0079 |
| SC03.CD/54 | 0 | 1 | 8,220 | data | code | 3 | 0.73/0.0034 |
| MAIN.CD/38 | 1 | 1 | 7,232 | data | code | 3 | 0.85/0.0111 |
| MAIN.CD/15 | 1 | 1 | 6,768 | data | code | 3 | 0.86/0.0118 |
| SC03.CD/53 | 0 | 1 | 6,616 | data | code | 3 | 0.65/0.0091 |
| MAIN.CD/25 | 1 | 1 | 6,396 | data | code | 3 | 0.87/0.0188 |
| MAIN.CD/13 | 1 | 1 | 6,100 | data | code | 3 | 0.78/0.0105 |
| MAIN.CD/32 | 1 | 1 | 5,572 | data | code | 3 | 0.87/0.0072 |
| SC03.CD/56 | 0 | 1 | 3,680 | data | code | 3 | 0.53/0.0043 |
| MAIN.CD/20 | 1 | 1 | 3,244 | data | code | 3 | 0.84/0.0173 |
| SLUS_007.26 | - | - | 413,696 | code | data | 0 | 0.96/0.0143 |

## Code payloads — 5 UNCLAIMED of 220

| file | entry | type | bytes | bucket | claimed-by | valid/jr |
|---|---|---|---:|---|---|---|
| MAIN.CD/7 | -1 | -1 | 9,600 | unclaimed-code | UNCLAIMED | 0.99/0.0079 L2=3 |
| MAIN.CD/9 | 0 | 1 | 2,544 | unclaimed-code | UNCLAIMED | 0.99/0.0189 L2=3 |
| SC03.CD/53 | 0 | 1 | 6,616 | unclaimed-code | UNCLAIMED | 0.65/0.0091 L2=3 |
| SC03.CD/54 | 0 | 1 | 8,220 | unclaimed-code | UNCLAIMED | 0.73/0.0034 L2=3 |
| SC03.CD/56 | 0 | 1 | 3,680 | unclaimed-code | UNCLAIMED | 0.53/0.0043 L2=3 |
| MAIN.CD/0 | 0 | 1 | 19,996 | onboarded-code | md_MAIN_001 | 0.73/0.0022 L2=3 |
| MAIN.CD/1 | 1 | 1 | 19,996 | onboarded-code | md_MAIN_001 | 0.73/0.0022 L2=3 |
| MAIN.CD/10 | 1 | 1 | 365,404 | onboarded-code | resident | 0.72/0.0016 L2=3 |
| MAIN.CD/11 | 1 | 1 | 24,240 | onboarded-code | md_MAIN_011 | 0.95/0.0035 L2=3 |
| MAIN.CD/12 | 1 | 1 | 383,783 | onboarded-code | ov_MAIN_012 | 0.99/0.0250 L2=3 |
| MAIN.CD/13 | 1 | 1 | 6,100 | onboarded-code | md_MAIN_013 | 0.78/0.0105 L2=3 |
| MAIN.CD/14 | 1 | 1 | 2,088 | onboarded-code | md_MAIN_014 | 0.99/0.0249 L2=3 |
| MAIN.CD/15 | 1 | 1 | 6,768 | onboarded-code | md_MAIN_015 | 0.86/0.0118 L2=3 |
| MAIN.CD/16 | 1 | 1 | 1,928 | onboarded-code | md_MAIN_016 | 0.99/0.0270 L2=3 |
| MAIN.CD/17 | 1 | 1 | 1,492 | onboarded-code | md_MAIN_017 | 0.97/0.0268 L2=3 |
| MAIN.CD/18 | 1 | 1 | 2,712 | onboarded-code | md_MAIN_018 | 0.96/0.0162 L2=3 |
| MAIN.CD/19 | 1 | 1 | 6,760 | onboarded-code | md_MAIN_019 | 0.94/0.0130 L2=3 |
| MAIN.CD/20 | 1 | 1 | 3,244 | onboarded-code | md_MAIN_020 | 0.84/0.0173 L2=3 |
| MAIN.CD/21 | 1 | 1 | 1,936 | onboarded-code | md_MAIN_021 | 0.99/0.0227 L2=3 |
| MAIN.CD/22 | 1 | 1 | 4,072 | onboarded-code | md_MAIN_022 | 1.00/0.0324 L2=3 |
| MAIN.CD/23 | 0 | 1 | 388 | onboarded-code | md_MAIN_023 | 0.99/0.0619 L2=3 |
| MAIN.CD/24 | 0 | 1 | 332 | onboarded-code | md_MAIN_024 | 0.99/0.0723 L2=3 |
| MAIN.CD/25 | 1 | 1 | 6,396 | onboarded-code | md_MAIN_025 | 0.87/0.0188 L2=3 |
| MAIN.CD/26 | 1 | 1 | 3,600 | onboarded-code | md_MAIN_026 | 0.99/0.0267 L2=3 |
| MAIN.CD/27 | 1 | 1 | 5,272 | onboarded-code | md_MAIN_027 | 0.98/0.0220 L2=3 |
| MAIN.CD/28 | 1 | 1 | 4,460 | onboarded-code | md_MAIN_028 | 0.99/0.0197 L2=3 |
| MAIN.CD/29 | 1 | 1 | 1,984 | onboarded-code | md_MAIN_029 | 0.98/0.0222 L2=3 |
| MAIN.CD/3 | 1 | 1 | 121,884 | onboarded-code | md_MAIN_003 | 0.83/0.0021 L2=0 |
| MAIN.CD/30 | 1 | 1 | 1,876 | onboarded-code | md_MAIN_030 | 0.98/0.0213 L2=3 |
| MAIN.CD/31 | 1 | 1 | 5,044 | onboarded-code | md_MAIN_031 | 0.97/0.0143 L2=3 |
| MAIN.CD/32 | 1 | 1 | 5,572 | onboarded-code | md_MAIN_032 | 0.87/0.0072 L2=3 |
| MAIN.CD/33 | 1 | 1 | 3,264 | onboarded-code | md_MAIN_033 | 0.99/0.0233 L2=3 |
| MAIN.CD/34 | 1 | 1 | 7,444 | onboarded-code | md_MAIN_034 | 0.92/0.0150 L2=3 |
| MAIN.CD/35 | 1 | 1 | 1,248 | onboarded-code | md_MAIN_035 | 0.97/0.0513 L2=3 |
| MAIN.CD/36 | 1 | 1 | 4,916 | onboarded-code | md_MAIN_036 | 0.99/0.0228 L2=3 |
| MAIN.CD/37 | 1 | 1 | 2,904 | onboarded-code | md_MAIN_037 | 0.90/0.0234 L2=3 |
| MAIN.CD/38 | 1 | 1 | 7,232 | onboarded-code | md_MAIN_038 | 0.85/0.0111 L2=3 |
| MAIN.CD/39 | 1 | 1 | 5,700 | onboarded-code | md_MAIN_039 | 0.97/0.0182 L2=3 |
| MAIN.CD/4 | 0 | 1 | 121,884 | onboarded-code | md_MAIN_003 | 0.83/0.0021 L2=0 |
| MAIN.CD/40 | 1 | 1 | 3,956 | onboarded-code | md_MAIN_040 | 0.98/0.0192 L2=3 |
| MAIN.CD/41 | 1 | 1 | 4,100 | onboarded-code | md_MAIN_041 | 0.97/0.0146 L2=3 |
| MAIN.CD/42 | 0 | 1 | 636 | onboarded-code | md_MAIN_042 | 1.00/0.0252 L2=3 |
| MAIN.CD/43 | 0 | 1 | 3,912 | onboarded-code | md_MAIN_043 | 1.00/0.0235 L2=3 |
| MAIN.CD/44 | 0 | 1 | 8,920 | onboarded-code | md_MAIN_044 | 0.98/0.0197 L2=3 |
| MAIN.CD/45 | 0 | 1 | 5,432 | onboarded-code | md_MAIN_045 | 0.97/0.0155 L2=3 |
| MAIN.CD/46 | 0 | 1 | 7,612 | onboarded-code | md_MAIN_046 | 0.94/0.0205 L2=3 |
| MAIN.CD/47 | 0 | 1 | 3,272 | onboarded-code | md_MAIN_047 | 1.00/0.0147 L2=3 |
| MAIN.CD/8 | 1 | 1 | 840 | onboarded-code | md_MAIN_008 | 1.00/0.0286 L2=3 |
| SC01.CD/0 | 0 | 4 | 513,935 | onboarded-code | ov_SC01_000 | 0.95/0.0187 L2=3 |
| SC01.CD/1 | 0 | 4 | 831,599 | onboarded-code | ov_SC01_001 | 0.74/0.0119 L2=3 |
| SC01.CD/4 | 0 | 4 | 426,615 | onboarded-code | ov_SC01_004 | 0.97/0.0227 L2=3 |
| SC01.CD/5 | 0 | 4 | 679,689 | onboarded-code | ov_SC01_006 | 0.88/0.0147 L2=3 |
| SC01.CD/6 | 0 | 4 | 679,689 | onboarded-code | ov_SC01_006 | 0.88/0.0147 L2=3 |
| SC01.CD/74 | 0 | 4 | 474,135 | onboarded-code | ov_SC01_074 | 0.96/0.0205 L2=3 |
| SC01.CD/77 | 0 | 4 | 731,607 | onboarded-code | ov_SC01_077 | 0.89/0.0141 L2=3 |
| SC01.CD/8 | 0 | 4 | 504,967 | onboarded-code | ov_SC01_008 | 0.88/0.0192 L2=3 |
| SC01.CD/80 | 0 | 4 | 654,839 | onboarded-code | ov_SC01_080 | 0.94/0.0154 L2=3 |
| SC01.CD/84 | 0 | 4 | 653,983 | onboarded-code | ov_SC01_084 | 0.90/0.0158 L2=3 |
| SC01.CD/9 | 0 | 4 | 832,263 | onboarded-code | ov_SC01_009 | 0.85/0.0121 L2=3 |
| SC02.CD/0 | 0 | 4 | 788,239 | onboarded-code | ov_SC02_003 | 0.90/0.0136 L2=3 |
| SC02.CD/11 | 0 | 4 | 801,063 | onboarded-code | ov_SC02_011 | 0.89/0.0145 L2=3 |
| SC02.CD/15 | 0 | 4 | 427,335 | onboarded-code | ov_SC02_015 | 0.98/0.0226 L2=3 |
| SC02.CD/16 | 0 | 4 | 575,871 | onboarded-code | ov_SC02_016 | 0.93/0.0177 L2=3 |
| SC02.CD/17 | 0 | 4 | 818,143 | onboarded-code | ov_SC02_017 | 0.89/0.0134 L2=3 |
| SC02.CD/21 | 0 | 4 | 440,135 | onboarded-code | ov_SC02_021 | 0.97/0.0222 L2=3 |
| SC02.CD/26 | 0 | 4 | 688,487 | onboarded-code | ov_SC02_026 | 0.90/0.0150 L2=3 |
| SC02.CD/27 | 0 | 4 | 731,367 | onboarded-code | ov_SC02_027 | 0.90/0.0147 L2=3 |
| SC02.CD/28 | 0 | 4 | 701,671 | onboarded-code | ov_SC02_028 | 0.91/0.0154 L2=3 |
| SC02.CD/3 | 0 | 4 | 788,239 | onboarded-code | ov_SC02_003 | 0.90/0.0136 L2=3 |
| SC02.CD/31 | 0 | 4 | 588,215 | onboarded-code | ov_SC02_031 | 0.91/0.0174 L2=3 |
| SC02.CD/35 | 0 | 4 | 616,687 | onboarded-code | ov_SC02_035 | 0.91/0.0164 L2=3 |
| SC02.CD/37 | 0 | 1 | 661,903 | onboarded-code | ov_SC02_037 | 0.91/0.0152 L2=3 |
| SC02.CD/39 | 0 | 4 | 494,759 | onboarded-code | ov_SC02_039 | 0.95/0.0195 L2=3 |
| SC02.CD/4 | 0 | 4 | 451,183 | onboarded-code | ov_SC02_004 | 0.97/0.0213 L2=3 |
| SC02.CD/41 | 0 | 4 | 595,327 | onboarded-code | ov_SC02_041 | 0.91/0.0172 L2=3 |
| SC02.CD/5 | 0 | 4 | 772,865 | onboarded-code | ov_SC02_005 | 0.87/0.0152 L2=3 |
| SC02.CD/9 | 0 | 1 | 70,784 | onboarded-code | md_SC02_009 | 0.70/0.0023 L2=3 |
| SC03.CD/1 | 0 | 4 | 815,887 | onboarded-code | ov_SC03_001 | 0.91/0.0141 L2=3 |
| SC03.CD/10 | 0 | 4 | 491,639 | onboarded-code | ov_SC03_010 | 0.96/0.0201 L2=3 |
| SC03.CD/100 | 0 | 4 | 657,423 | onboarded-code | ov_SC03_100 | 0.90/0.0155 L2=3 |
| SC03.CD/101 | 0 | 4 | 483,535 | onboarded-code | ov_SC03_101 | 0.97/0.0209 L2=3 |
| SC03.CD/102 | 0 | 4 | 596,687 | onboarded-code | ov_SC03_102 | 0.91/0.0167 L2=3 |
| SC03.CD/103 | 0 | 4 | 642,175 | onboarded-code | ov_SC03_103 | 0.91/0.0156 L2=3 |
| SC03.CD/104 | 0 | 4 | 623,423 | onboarded-code | ov_SC03_104 | 0.91/0.0168 L2=3 |
| SC03.CD/105 | 0 | 4 | 609,223 | onboarded-code | ov_SC03_105 | 0.89/0.0171 L2=3 |
| SC03.CD/107 | 0 | 1 | 474,087 | onboarded-code | ov_SC03_107 | 0.97/0.0211 L2=3 |
| SC03.CD/108 | 0 | 4 | 497,999 | onboarded-code | ov_SC03_108 | 0.95/0.0196 L2=3 |
| SC03.CD/109 | 0 | 4 | 467,799 | onboarded-code | ov_SC03_109 | 0.96/0.0207 L2=3 |
| SC03.CD/11 | 0 | 4 | 500,395 | onboarded-code | ov_SC03_011 | 0.95/0.0202 L2=3 |
| SC03.CD/110 | 0 | 4 | 500,615 | onboarded-code | ov_SC03_110 | 0.95/0.0197 L2=3 |
| SC03.CD/111 | 0 | 4 | 596,527 | onboarded-code | ov_SC03_111 | 0.93/0.0168 L2=3 |
| SC03.CD/112 | 0 | 4 | 544,759 | onboarded-code | ov_SC03_112 | 0.95/0.0186 L2=3 |
| SC03.CD/113 | 0 | 4 | 514,967 | onboarded-code | ov_SC03_113 | 0.95/0.0192 L2=3 |
| SC03.CD/114 | 0 | 4 | 530,191 | onboarded-code | ov_SC03_114 | 0.93/0.0182 L2=3 |
| SC03.CD/115 | 0 | 4 | 446,439 | onboarded-code | ov_SC03_115 | 0.97/0.0222 L2=3 |
| SC03.CD/116 | 0 | 4 | 457,719 | onboarded-code | ov_SC03_116 | 0.98/0.0213 L2=3 |
| SC03.CD/117 | 0 | 4 | 681,967 | onboarded-code | ov_SC03_117 | 0.92/0.0150 L2=3 |
| SC03.CD/118 | 0 | 4 | 706,295 | onboarded-code | ov_SC03_119 | 0.90/0.0152 L2=3 |
| SC03.CD/119 | 0 | 4 | 706,295 | onboarded-code | ov_SC03_119 | 0.90/0.0152 L2=3 |
| SC03.CD/12 | 0 | 4 | 446,471 | onboarded-code | ov_SC03_012 | 0.98/0.0216 L2=3 |
| SC03.CD/121 | 0 | 4 | 552,535 | onboarded-code | ov_SC03_121 | 0.90/0.0178 L2=3 |
| SC03.CD/124 | 0 | 4 | 763,023 | onboarded-code | ov_SC03_124 | 0.91/0.0144 L2=3 |
| SC03.CD/125 | 0 | 4 | 639,975 | onboarded-code | ov_SC03_125 | 0.92/0.0162 L2=3 |
| SC03.CD/126 | 0 | 4 | 424,405 | onboarded-code | ov_SC03_126 | 0.97/0.0229 L2=3 |
| SC03.CD/13 | 0 | 4 | 545,791 | onboarded-code | ov_SC03_013 | 0.94/0.0183 L2=3 |
| SC03.CD/132 | 2 | 1 | 29,080 | onboarded-code | md_SC03_132 | 0.79/0.0039 L2=3 |
| SC03.CD/133 | 2 | 1 | 27,272 | onboarded-code | md_SC03_133 | 0.83/0.0043 L2=3 |
| SC03.CD/134 | 2 | 1 | 30,808 | onboarded-code | md_SC03_134 | 0.82/0.0053 L2=3 |
| SC03.CD/135 | 2 | 1 | 34,828 | onboarded-code | md_SC03_135 | 0.87/0.0076 L2=3 |
| SC03.CD/136 | 2 | 1 | 32,712 | onboarded-code | md_SC03_136 | 0.79/0.0043 L2=3 |
| SC03.CD/137 | 2 | 1 | 15,652 | onboarded-code | md_SC03_137 | 0.83/0.0069 L2=3 |
| SC03.CD/138 | 2 | 1 | 40,164 | onboarded-code | md_SC03_138 | 0.79/0.0037 L2=3 |
| SC03.CD/14 | 0 | 4 | 798,439 | onboarded-code | ov_SC03_015 | 0.87/0.0135 L2=3 |
| SC03.CD/15 | 0 | 4 | 798,439 | onboarded-code | ov_SC03_015 | 0.87/0.0135 L2=3 |
| SC03.CD/2 | 0 | 4 | 670,199 | onboarded-code | ov_SC03_002 | 0.91/0.0157 L2=3 |
| SC03.CD/23 | 0 | 4 | 461,871 | onboarded-code | ov_SC03_023 | 0.97/0.0211 L2=3 |
| SC03.CD/24 | 0 | 4 | 628,471 | onboarded-code | ov_SC03_024 | 0.91/0.0168 L2=3 |
| SC03.CD/28 | 0 | 4 | 804,015 | onboarded-code | ov_SC03_028 | 0.88/0.0133 L2=3 |
| SC03.CD/29 | 0 | 4 | 727,279 | onboarded-code | ov_SC03_029 | 0.93/0.0146 L2=3 |
| SC03.CD/3 | 0 | 4 | 424,485 | onboarded-code | ov_SC03_003 | 0.97/0.0229 L2=3 |
| SC03.CD/30 | 0 | 4 | 760,560 | onboarded-code | ov_SC03_030 | 0.90/0.0131 L2=3 |
| SC03.CD/31 | 0 | 4 | 647,503 | onboarded-code | ov_SC03_031 | 0.94/0.0155 L2=3 |
| SC03.CD/6 | 0 | 4 | 849,759 | onboarded-code | ov_SC03_006 | 0.87/0.0130 L2=3 |
| SC03.CD/7 | 0 | 4 | 799,087 | onboarded-code | ov_SC03_007 | 0.88/0.0131 L2=3 |
| SC03.CD/73 | 2 | 1 | 29,112 | onboarded-code | md_SC03_073 | 0.79/0.0038 L2=3 |
| SC03.CD/74 | 2 | 1 | 27,296 | onboarded-code | md_SC03_074 | 0.83/0.0042 L2=3 |
| SC03.CD/75 | 2 | 1 | 30,792 | onboarded-code | md_SC03_075 | 0.82/0.0053 L2=3 |
| SC03.CD/76 | 2 | 1 | 43,760 | onboarded-code | md_SC03_076 | 0.88/0.0060 L2=3 |
| SC03.CD/77 | 2 | 1 | 32,768 | onboarded-code | md_SC03_077 | 0.79/0.0043 L2=3 |
| SC03.CD/78 | 2 | 1 | 15,676 | onboarded-code | md_SC03_078 | 0.84/0.0069 L2=3 |
| SC03.CD/79 | 2 | 1 | 39,340 | onboarded-code | md_SC03_079 | 0.79/0.0032 L2=3 |
| SC03.CD/89 | 0 | 4 | 649,159 | onboarded-code | ov_SC03_089 | 0.91/0.0159 L2=3 |
| SC03.CD/90 | 0 | 4 | 670,775 | onboarded-code | ov_SC03_090 | 0.90/0.0157 L2=3 |
| SC03.CD/91 | 0 | 4 | 697,735 | onboarded-code | ov_SC03_091 | 0.90/0.0151 L2=3 |
| SC03.CD/92 | 0 | 4 | 569,135 | onboarded-code | ov_SC03_092 | 0.93/0.0182 L2=3 |
| SC03.CD/93 | 0 | 4 | 673,159 | onboarded-code | ov_SC03_093 | 0.89/0.0152 L2=3 |
| SC03.CD/94 | 0 | 4 | 700,735 | onboarded-code | ov_SC03_094 | 0.89/0.0147 L2=3 |
| SC03.CD/95 | 0 | 4 | 474,431 | onboarded-code | ov_SC03_095 | 0.95/0.0209 L2=3 |
| SC03.CD/96 | 0 | 4 | 468,983 | onboarded-code | ov_SC03_096 | 0.95/0.0210 L2=3 |
| SC03.CD/97 | 0 | 4 | 535,927 | onboarded-code | ov_SC03_097 | 0.94/0.0194 L2=3 |
| SC03.CD/98 | 0 | 4 | 644,959 | onboarded-code | ov_SC03_098 | 0.90/0.0158 L2=3 |
| SC03.CD/99 | 0 | 4 | 619,271 | onboarded-code | ov_SC03_099 | 0.91/0.0162 L2=3 |
| SC04.CD/0 | 0 | 4 | 536,319 | onboarded-code | ov_SC04_000 | 0.95/0.0190 L2=3 |
| SC04.CD/10 | 0 | 4 | 423,407 | onboarded-code | ov_SC04_010 | 0.97/0.0229 L2=3 |
| SC04.CD/11 | 0 | 4 | 824,663 | onboarded-code | ov_SC04_011 | 0.79/0.0136 L2=3 |
| SC04.CD/12 | 0 | 4 | 438,503 | onboarded-code | ov_SC04_012 | 0.96/0.0221 L2=3 |
| SC04.CD/15 | 0 | 4 | 660,103 | onboarded-code | ov_SC04_015 | 0.92/0.0158 L2=3 |
| SC04.CD/16 | 0 | 4 | 541,063 | onboarded-code | ov_SC04_016 | 0.95/0.0181 L2=3 |
| SC04.CD/18 | 0 | 4 | 784,847 | onboarded-code | ov_SC04_019 | 0.92/0.0146 L2=3 |
| SC04.CD/19 | 0 | 4 | 784,847 | onboarded-code | ov_SC04_019 | 0.92/0.0146 L2=3 |
| SC04.CD/2 | 0 | 4 | 628,191 | onboarded-code | ov_SC04_002 | 0.91/0.0168 L2=3 |
| SC04.CD/20 | 0 | 4 | 607,831 | onboarded-code | ov_SC04_020 | 0.92/0.0169 L2=3 |
| SC04.CD/21 | 0 | 4 | 424,405 | onboarded-code | ov_SC04_021 | 0.97/0.0229 L2=3 |
| SC04.CD/24 | 2 | 1 | 29,120 | onboarded-code | md_SC04_024 | 0.79/0.0038 L2=3 |
| SC04.CD/25 | 2 | 1 | 27,312 | onboarded-code | md_SC04_025 | 0.83/0.0042 L2=3 |
| SC04.CD/26 | 2 | 1 | 30,808 | onboarded-code | md_SC04_026 | 0.82/0.0053 L2=3 |
| SC04.CD/27 | 2 | 1 | 43,776 | onboarded-code | md_SC04_027 | 0.88/0.0060 L2=3 |
| SC04.CD/28 | 2 | 1 | 32,752 | onboarded-code | md_SC04_028 | 0.79/0.0043 L2=3 |
| SC04.CD/29 | 2 | 1 | 15,692 | onboarded-code | md_SC04_029 | 0.84/0.0069 L2=3 |
| SC04.CD/3 | 0 | 4 | 473,751 | onboarded-code | ov_SC04_003 | 0.97/0.0211 L2=3 |
| SC04.CD/30 | 2 | 1 | 39,356 | onboarded-code | md_SC04_030 | 0.79/0.0032 L2=3 |
| SC04.CD/4 | 0 | 4 | 572,159 | onboarded-code | ov_SC04_004 | 0.92/0.0179 L2=3 |
| SC04.CD/5 | 0 | 4 | 631,255 | onboarded-code | ov_SC04_005 | 0.90/0.0166 L2=3 |
| SC04.CD/6 | 0 | 4 | 482,423 | onboarded-code | ov_SC04_006 | 0.95/0.0204 L2=3 |
| SC04.CD/7 | 0 | 4 | 580,151 | onboarded-code | ov_SC04_007 | 0.92/0.0177 L2=3 |
| SC04.CD/8 | 0 | 4 | 439,143 | onboarded-code | ov_SC04_008 | 0.97/0.0220 L2=3 |
| SC04.CD/9 | 0 | 4 | 459,031 | onboarded-code | ov_SC04_009 | 0.97/0.0213 L2=3 |
| SC05.CD/0 | 0 | 4 | 469,759 | onboarded-code | ov_SC05_000 | 0.96/0.0206 L2=3 |
| SC05.CD/1 | 0 | 4 | 581,295 | onboarded-code | ov_SC05_001 | 0.95/0.0177 L2=3 |
| SC05.CD/10 | 0 | 4 | 655,063 | onboarded-code | ov_SC05_010 | 0.89/0.0158 L2=3 |
| SC05.CD/11 | 0 | 4 | 479,367 | onboarded-code | ov_SC05_011 | 0.94/0.0201 L2=3 |
| SC05.CD/17 | 0 | 4 | 809,007 | onboarded-code | ov_SC05_017 | 0.91/0.0141 L2=3 |
| SC05.CD/18 | 0 | 4 | 780,087 | onboarded-code | ov_SC05_018 | 0.83/0.0137 L2=3 |
| SC05.CD/19 | 0 | 4 | 424,405 | onboarded-code | ov_SC05_019 | 0.97/0.0229 L2=3 |
| SC05.CD/2 | 0 | 4 | 491,111 | onboarded-code | ov_SC05_002 | 0.96/0.0199 L2=3 |
| SC05.CD/23 | 2 | 1 | 29,168 | onboarded-code | md_SC05_023 | 0.79/0.0038 L2=3 |
| SC05.CD/24 | 2 | 1 | 27,352 | onboarded-code | md_SC05_024 | 0.83/0.0042 L2=3 |
| SC05.CD/25 | 2 | 1 | 30,848 | onboarded-code | md_SC05_025 | 0.82/0.0053 L2=3 |
| SC05.CD/26 | 2 | 1 | 43,816 | onboarded-code | md_SC05_026 | 0.88/0.0060 L2=3 |
| SC05.CD/27 | 2 | 1 | 32,792 | onboarded-code | md_SC05_027 | 0.79/0.0043 L2=3 |
| SC05.CD/28 | 2 | 1 | 15,732 | onboarded-code | md_SC05_028 | 0.84/0.0069 L2=3 |
| SC05.CD/29 | 2 | 1 | 39,396 | onboarded-code | md_SC05_029 | 0.79/0.0031 L2=3 |
| SC05.CD/3 | 0 | 4 | 543,095 | onboarded-code | ov_SC05_003 | 0.94/0.0183 L2=3 |
| SC05.CD/4 | 0 | 4 | 487,887 | onboarded-code | ov_SC05_004 | 0.96/0.0202 L2=3 |
| SC05.CD/5 | 0 | 4 | 564,951 | onboarded-code | ov_SC05_005 | 0.93/0.0177 L2=3 |
| SC05.CD/6 | 0 | 4 | 425,991 | onboarded-code | ov_SC05_006 | 0.98/0.0228 L2=3 |
| SC05.CD/7 | 0 | 4 | 478,631 | onboarded-code | ov_SC05_007 | 0.96/0.0208 L2=3 |
| SC05.CD/8 | 0 | 4 | 496,019 | onboarded-code | ov_SC05_008 | 0.97/0.0205 L2=3 |
| SC05.CD/9 | 0 | 4 | 453,359 | onboarded-code | ov_SC05_009 | 0.97/0.0215 L2=3 |
| SC06.CD/0 | 0 | 4 | 565,295 | onboarded-code | ov_SC06_000 | 0.95/0.0190 L2=3 |
| SC06.CD/10 | 0 | 4 | 568,103 | onboarded-code | ov_SC06_010 | 0.96/0.0177 L2=3 |
| SC06.CD/11 | 0 | 4 | 539,647 | onboarded-code | ov_SC06_011 | 0.93/0.0183 L2=3 |
| SC06.CD/13 | 0 | 4 | 469,679 | onboarded-code | ov_SC06_013 | 0.96/0.0207 L2=3 |
| SC06.CD/14 | 0 | 4 | 496,839 | onboarded-code | ov_SC06_014 | 0.96/0.0198 L2=3 |
| SC06.CD/15 | 0 | 4 | 444,583 | onboarded-code | ov_SC06_015 | 0.97/0.0218 L2=3 |
| SC06.CD/16 | 0 | 4 | 491,799 | onboarded-code | ov_SC06_016 | 0.96/0.0207 L2=3 |
| SC06.CD/18 | 0 | 4 | 711,239 | onboarded-code | ov_SC06_018 | 0.91/0.0150 L2=3 |
| SC06.CD/20 | 0 | 4 | 600,215 | onboarded-code | ov_SC06_020 | 0.92/0.0168 L2=3 |
| SC06.CD/22 | 0 | 4 | 762,135 | onboarded-code | ov_SC06_022 | 0.89/0.0139 L2=3 |
| SC06.CD/24 | 0 | 4 | 759,823 | onboarded-code | ov_SC06_024 | 0.89/0.0141 L2=3 |
| SC06.CD/25 | 0 | 4 | 565,551 | onboarded-code | ov_SC06_025 | 0.93/0.0182 L2=3 |
| SC06.CD/27 | 0 | 4 | 479,959 | onboarded-code | ov_SC06_027 | 0.96/0.0201 L2=3 |
| SC06.CD/29 | 0 | 4 | 761,911 | onboarded-code | ov_SC06_029 | 0.90/0.0140 L2=3 |
| SC06.CD/30 | 0 | 4 | 597,807 | onboarded-code | ov_SC06_030 | 0.84/0.0164 L2=3 |
| SC06.CD/32 | 0 | 4 | 692,247 | onboarded-code | ov_SC06_032 | 0.92/0.0154 L2=3 |
| SC06.CD/33 | 0 | 4 | 691,863 | onboarded-code | ov_SC06_033 | 0.92/0.0152 L2=3 |
| SC06.CD/6 | 0 | 4 | 854,543 | onboarded-code | ov_SC06_006 | 0.87/0.0118 L2=3 |
| SC06.CD/8 | 0 | 4 | 534,239 | onboarded-code | ov_SC06_008 | 0.96/0.0190 L2=3 |
| SC07.CD/0 | 0 | 4 | 691,087 | onboarded-code | ov_SC07_000 | 0.89/0.0146 L2=3 |
| SC07.CD/1 | 0 | 4 | 535,991 | onboarded-code | ov_SC07_001 | 0.93/0.0183 L2=3 |
| SC07.CD/10 | 1 | 4 | 529,391 | onboarded-code | ov_SC07_010 | 0.94/0.0191 L2=3 |
| SC07.CD/11 | 1 | 4 | 426,919 | onboarded-code | ov_SC07_011 | 0.98/0.0230 L2=3 |
| SC07.CD/2 | 0 | 4 | 491,391 | onboarded-code | ov_SC07_002 | 0.98/0.0210 L2=3 |
| SC07.CD/3 | 1 | 1 | 345,132 | onboarded-code | md_SC07_003 | 0.57/0.0012 L2=3 |
| SC07.CD/4 | 1 | 1 | 365,152 | onboarded-code | md_SC07_004 | 0.84/0.0035 L2=3 |
| SC07.CD/6 | 1 | 4 | 844,311 | onboarded-code | ov_SC07_006 | 0.84/0.0116 L2=3 |
| SC07.CD/7 | 1 | 4 | 653,791 | onboarded-code | ov_SC07_007 | 0.91/0.0160 L2=3 |
| SC07.CD/8 | 0 | 4 | 452,079 | onboarded-code | ov_SC07_008 | 0.97/0.0211 L2=3 |
| SC07.CD/9 | 0 | 4 | 507,007 | onboarded-code | ov_SC07_009 | 0.95/0.0192 L2=3 |
| SLUS_007.26 | - | - | 413,696 | onboarded-code | us | 0.96/0.0143 L2=0 |
