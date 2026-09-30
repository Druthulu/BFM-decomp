# Struct-map decisions — the head types (P38 T3)

## Canonical file set

TODO(T3 expert)

## Resolution rule

TODO(T3 expert)

## Unkstruct_80078E00 (the player block)

TODO(T3 expert)

## Per-offset records

Written by `tools/head_types.py` (max-site split). Losers' sites keep their casts; the byte oracle judges them later.
Summary fields: `overlaps` = candidates dropped because a heavier non-overlapping set won; `misaligned` = candidates dropped
for `off % min(w,4) != 0` (or an 8-byte field off 8-alignment); `union_candidates` = offsets whose resolution is
`union-candidate (deferred)`.

<!-- head_types:begin -->
Source: `.run/P37/census/struct_map.json` head `42a9cd7f5`.

### Unkstruct_800B5CB8

`fields=101 kept_sites=75717 dropped_sites=25393 conflict_offsets=50 overlaps=167 misaligned=4 union_candidates=27`

- `0x000: chosen 2u n=367; losers: 4s n=25@0x000, 4p n=10@0x000, 2s n=38@0x000, 1u n=24@0x000, 1u n=11@0x001; resolution: split`
- `0x001: chosen none (inside 2u@0x000); losers listed there; resolution: split`
- `0x002: chosen 2s n=3260; losers: 2u n=2271@0x002, 1u n=7@0x002, 1u n=9@0x003; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x004: chosen 2s n=61; losers: 4s n=1376@0x004, 4u n=538@0x004, 2u n=26@0x004, 1s n=2@0x004; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x006: chosen 2u n=1597; losers: 2s n=696@0x006; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x008: chosen 2u n=480; losers: 4s n=466@0x008, 4u n=9@0x008, 2s n=36@0x008; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x00C: chosen 2u n=470; losers: 4s n=399@0x00C, 4u n=6@0x00C, 2s n=22@0x00C, 1u n=16@0x00C, 1u n=12@0x00D; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x010: chosen 2u n=1925; losers: 4s n=2139@0x010, 4u n=8@0x010, 4p n=3@0x010, 2s n=935@0x010; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x012: chosen 2u n=4483; losers: 2s n=2789@0x012; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x014: chosen 4s n=1156; losers: 4u n=13@0x014, 2s n=416@0x014, 2u n=310@0x014, 2s n=280@0x016; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x018: chosen 2u n=1062; losers: 4s n=2122@0x018, 4u n=13@0x018, 2s n=778@0x018; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x01C: chosen 4s n=7913; losers: 4u n=59@0x01C, 2s n=306@0x01C, 2u n=160@0x01C, 1u n=5@0x01C, 2s n=133@0x01E, 1s n=1@0x01F; resolution: split`
- `0x020: chosen 4s n=13163; losers: 4u n=73@0x020, 4p n=389@0x020, 1u n=6@0x020, 1u n=8@0x021, 1u n=12@0x022, 1u n=5@0x023; resolution: split`
- `0x024: chosen 1u n=10; losers: 4s n=111@0x024, 4u n=1@0x024, 4p n=7@0x024, 2s n=5@0x024, 2u n=1@0x024; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x026: chosen 1u n=11; losers: 2s n=5@0x026, 2u n=3@0x026; resolution: split`
- `0x028: chosen 2s n=26; losers: 4s n=31@0x028, 4u n=3@0x028, 2u n=20@0x028, 1u n=1@0x028; resolution: split`
- `0x02C: chosen 2u n=728; losers: 4s n=141@0x02C, 4u n=5@0x02C, 4p n=15@0x02C, 2s n=87@0x02C; resolution: split`
- `0x030: chosen 4s n=31; losers: 2s n=7@0x030, 2u n=18@0x030, 2s n=11@0x032; resolution: split`
- `0x034: chosen 2u n=2952; losers: 4s n=46@0x034, 4u n=8@0x034, 4p n=4@0x034, 2s n=804@0x034; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x038: chosen 2s n=1; losers: 4s n=175@0x038, 2u n=1@0x038; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x03E: chosen 2u n=352; losers: 4s n=125@0x03C; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x042: chosen 2u n=352; losers: 4s n=176@0x040; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x044: chosen 4s n=46; losers: 2u n=8@0x044; resolution: split`
- `0x048: chosen 4s n=418; losers: 2u n=13@0x04A; resolution: split`
- `0x050: chosen 4s n=126; losers: 2s n=7@0x050, 2u n=13@0x050, 2s n=48@0x052; resolution: split`
- `0x05C: chosen 2u n=947; losers: 4s n=1@0x05C, 2s n=531@0x05C; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x05E: chosen 1u n=295; losers: 2s n=138@0x05E, 2u n=234@0x05E; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x070: chosen 2s n=1813; losers: 4s n=1@0x070, 2u n=938@0x070, 1s n=4@0x070, 1u n=12@0x070; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x080: chosen 2s n=292; losers: 4s n=94@0x080, 4u n=3@0x080, 4p n=22@0x080, 2u n=26@0x080; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x0CC: chosen 4s n=1172; losers: 4u n=23@0x0CC, 4p n=269@0x0CC, 2s n=2@0x0CC, 2u n=5@0x0CC, 2u n=5@0x0CE; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x0D0: chosen 4s n=464; losers: 4p n=75@0x0D0, 2s n=2@0x0D0, 2u n=7@0x0D0, 2s n=3@0x0D2; resolution: split`
- `0x0D4: chosen 4s n=184; losers: 4p n=24@0x0D4, 2u n=5@0x0D4, 2u n=5@0x0D6; resolution: split`
- `0x0D8: chosen 4s n=93; losers: 4p n=12@0x0D8, 2s n=2@0x0D8, 2u n=5@0x0D8; resolution: split`
- `0x0DC: chosen 4s n=487; losers: 4u n=7@0x0DC, 4p n=79@0x0DC, 2s n=155@0x0DC, 2u n=76@0x0DC, 2s n=105@0x0DE; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x0E0: chosen 4s n=511; losers: 4u n=283@0x0E0, 2s n=69@0x0E0, 2u n=52@0x0E0, 2u n=74@0x0E2; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x0E4: chosen 4s n=282; losers: 4u n=6@0x0E4, 2s n=46@0x0E4, 2u n=55@0x0E4, 2u n=40@0x0E6; resolution: split`
- `0x0E8: chosen 4s n=313; losers: 4u n=58@0x0E8, 2s n=65@0x0E8, 2u n=10@0x0E8, 2s n=58@0x0EA; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x0EC: chosen 2s n=36; losers: 4s n=43@0x0EC, 4u n=1@0x0EC, 4p n=1@0x0EC, 2u n=6@0x0EC, 1u n=5@0x0EC, 1u n=5@0x0ED; resolution: split`
- `0x0EE: chosen 2s n=17; losers: 2u n=5@0x0EE, 1u n=5@0x0EE; resolution: split`
- `0x0F0: chosen 1u n=5; losers: 4s n=22@0x0F0, 2s n=5@0x0F0; resolution: split`
- `0x0F2: chosen 2u n=16; losers: 2s n=6@0x0F2, 1u n=5@0x0F2; resolution: split`
- `0x0F4: chosen 4s n=35; losers: 4p n=1@0x0F4, 2s n=26@0x0F4, 2u n=17@0x0F4, 1u n=5@0x0F4, 1u n=5@0x0F5, 2s n=8@0x0F6, 2u n=7@0x0F6, 1u n=6@0x0F6; resolution: split`
- `0x0F6: chosen none (inside 4s@0x0F4); losers listed there; resolution: split`
- `0x0F8: chosen 4s n=21; losers: 4p n=5@0x0F8, 2s n=9@0x0F8, 2u n=8@0x0F8, 1u n=5@0x0F8, 1u n=5@0x0F9, 2s n=5@0x0FA, 2u n=3@0x0FA, 1u n=5@0x0FA; resolution: split`
- `0x0FA: chosen none (inside 4s@0x0F8); losers listed there; resolution: split`
- `0x0FC: chosen 2s n=1922; losers: 4s n=5@0x0FC, 2u n=740@0x0FC, 1u n=31@0x0FC, 1u n=4@0x0FD; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x0FE: chosen 2s n=1470; losers: 2u n=690@0x0FE, 1u n=7@0x0FE, 1u n=4@0x0FF; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x100: chosen 2s n=691; losers: 4u n=8@0x100, 2u n=588@0x100, 1u n=5@0x100, 1u n=2@0x101; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x102: chosen 2s n=364; losers: 2u n=280@0x102, 1s n=4@0x102, 1u n=17@0x102, 1u n=2@0x103; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x104: chosen 2s n=311; losers: 1u n=6@0x105; resolution: split`
- `0x108: chosen 2u n=173; losers: 2s n=166@0x108, 1u n=36@0x108, 1u n=21@0x109; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`

### Unkstruct_80126B58

`fields=152 kept_sites=61599 dropped_sites=1713 conflict_offsets=50 overlaps=71 misaligned=5 union_candidates=4`

- `0x004: chosen 2u n=5; losers: 4s n=12@0x004; resolution: split`
- `0x006: chosen 2s n=237; losers: 2u n=178@0x006; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x008: chosen 2u n=5; losers: 4s n=15@0x008; resolution: split`
- `0x00C: chosen 2u n=5; losers: 4s n=13@0x00C; resolution: split`
- `0x010: chosen 4s n=464; losers: 4p n=2@0x010, 2s n=10@0x010, 2u n=283@0x010, 2u n=22@0x012; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x014: chosen 4s n=440; losers: 4u n=2@0x014, 2u n=6@0x014, 2u n=6@0x016; resolution: split`
- `0x018: chosen 4s n=438; losers: 4u n=2@0x018, 2u n=8@0x018, 2u n=8@0x01A; resolution: split`
- `0x024: chosen 2s n=20; losers: 4s n=142@0x024, 2u n=2@0x024; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
- `0x028: chosen 4s n=12; losers: 2s n=11@0x028, 2u n=1@0x028, 1u n=2@0x028; resolution: split`
- `0x02C: chosen 4s n=4448; losers: 4u n=8@0x02C, 2s n=3@0x02C, 2s n=135@0x02E; resolution: split`
- `0x030: chosen 4s n=171; losers: 4u n=4@0x030, 1u n=2@0x030; resolution: split`
- `0x044: chosen 4u n=1744; losers: 4s n=331@0x044, 2s n=1@0x044, 2s n=1@0x046; resolution: split`
- `0x04D: chosen 1u n=13; losers: 4s n=49@0x04C; resolution: split`
- `0x054: chosen 4s n=2151; losers: 1u n=4@0x054; resolution: split`
- `0x058: chosen 4s n=2145; losers: 4u n=1@0x058, 4p n=6@0x058, 2s n=6@0x058, 2u n=4@0x058, 1u n=3@0x058, 1u n=3@0x059, 2s n=7@0x05A, 2u n=5@0x05A, 1u n=3@0x05A, 1u n=1@0x05B; resolution: split`
- `0x05A: chosen none (inside 4s@0x058); losers listed there; resolution: split`
- `0x05C: chosen 4s n=404; losers: 2s n=3@0x05C, 2u n=1@0x05C, 1u n=3@0x05C, 1u n=3@0x05D, 2s n=2@0x05E, 2u n=1@0x05E, 1u n=3@0x05E, 1u n=1@0x05F; resolution: split`
- `0x05E: chosen none (inside 4s@0x05C); losers listed there; resolution: split`
- `0x060: chosen 2u n=72; losers: 4s n=1@0x060, 2s n=38@0x060; resolution: split`
- `0x066: chosen 2u n=10; losers: 1u n=2@0x067; resolution: split`
- `0x0AE: chosen 2u n=14; losers: 2s n=1@0x0AE, 1u n=4@0x0AE; resolution: split`
- `0x0FC: chosen 2s n=3; losers: 4u n=2@0x0FC; resolution: split`
- `0x204: chosen 4s n=26; losers: 2s n=3@0x206; resolution: split`
- `0x208: chosen 4s n=4; losers: 2u n=1@0x20A; resolution: split`
- `0x20C: chosen 2s n=28; losers: 2u n=21@0x20C, 1s n=1@0x20C, 1u n=11@0x20C, 1s n=4@0x20D; resolution: split`
- `0x218: chosen 1u n=3; losers: 4s n=1@0x218; resolution: split`
- `0x234: chosen 4s n=5937; losers: 4u n=1@0x234, 2u n=6@0x234, 2u n=138@0x236; resolution: split`
- `0x238: chosen 4s n=1475; losers: 4u n=2@0x238, 2u n=2@0x238, 2u n=2@0x23A; resolution: split`
- `0x240: chosen 4s n=274; losers: 2u n=4@0x240; resolution: split`
- `0x244: chosen 2u n=409; losers: 2s n=142@0x244, 1s n=1@0x244, 1u n=5@0x244, 1s n=1@0x245; resolution: union-candidate (deferred: rewriter spells flat members only, restruct.py member_spelling) -> split`
<!-- head_types:end -->
