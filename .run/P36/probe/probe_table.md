# probe — 285 bodies sampled, 283 judged (seed 11, 2026-09-09 01:59, wall 151.4 s)

- rung A (strip-all) identical: **53 / 283** (register dropped) · 53 with `register` kept
- lever-free after rung B: **53 / 283**
- sites: 1309 usable · removed 561 (42.9 %) · needed 748
- needed by kind: {'pin': 360, 'launder': 154, 'instruction': 21, 'barrier': 127, 'register': 8, 'keepalive': 36, 'cast': 26, 'decl-body': 16}
- needed by detail (top): {'launder:': 123, 'barrier:': 82, 'pin:$2': 80, 'pin:$4': 50, 'pin:$3': 46, 'barrier:memory': 45, 'pin:$5': 37, 'keepalive:': 36, 'pin:$16': 27, 'launder:out-only': 20, 'cast:volatile s32 *': 18, 'pin:$17': 17, 'pin:$6': 15, 'instruction:addiu': 14, 'decl-body:': 14, 'pin:$0': 13, 'pin:$19': 13, 'pin:$8': 11, 'pin:$7': 10, 'pin:$9': 8, 'register:': 8, 'pin:$14': 5, 'pin:$21': 5, 'launder:LAUNDER_8018A180': 5, 'pin:$10': 4, 'pin:$12': 4, 'pin:$18': 4, 'cast:volatile s16 *': 4, 'instruction:addu': 4, 'pin:$20': 4}
- removed by kind: {'instruction': 3, 'pin': 438, 'decl-body': 11, 'register': 4, 'launder': 45, 'barrier': 27, 'keepalive': 8, 'cast': 25}
- refused (rewrite not applicable): {'instruction `sll` has no C spelling in the table': 1, 'instruction `addu` has no C spelling in the table': 1, 'instruction `li` has no C spelling in the table': 1, 'instruction `nop` has no C spelling in the table': 1, 'macro-carried instruction is residue': 2, 'no statement end for the macro use': 3}
- compiles 1660 · mean 5.87 per body · 0.225 s per compile

| kind | bodies | A identical | A (register kept) | lever-free after B | sites | removed | needed | compiles | s/compile |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| main | 40 | 6 | 6 | 6 | 272 | 146 | 126 | 328 | 0.386 |
| resident | 16 | 4 | 4 | 4 | 31 | 9 | 22 | 53 | 0.06 |
| md | 29 | 2 | 2 | 2 | 121 | 56 | 65 | 161 | 0.139 |
| shared | 40 | 7 | 7 | 7 | 164 | 65 | 99 | 216 | 0.211 |
| ov | 158 | 34 | 34 | 34 | 721 | 285 | 436 | 902 | 0.195 |

| feature | bodies | lever-free |
|---|---:|---:|
| zero | 17 | 1 |
| init | 32 | 7 |
| instr | 10 | 1 |
| cast | 22 | 1 |
| register | 12 | 3 |
| launder | 68 | 4 |
| barrier | 78 | 9 |
| keepalive | 27 | 1 |
| volatile | 40 | 11 |

**Pricing (R41; population 16,064 lever bodies / 55,913 removable sites):** T4 ≈ 94,226 compiles ≈ 5.89 CPU-h ≈ 0.49 h wall at 12 workers; residue after the mechanical ladder ≈ 13,055 bodies / 31,950 sites (the sample's rates applied to the population).
