/* include/struct_types.h — the struct map's canonical layouts (P38 T3). One definition per type, visible to every space through common.h. Generated block below is written by tools/head_types.py from .run/P37/census/struct_map.json; hand-written text outside the markers survives regeneration. Naming law G62: Unkstruct_<addr>, unkHEX fields, 0xNN offset comments. */
#ifndef STRUCT_TYPES_H
#define STRUCT_TYPES_H

/* head_types:begin */
typedef struct {
    /* P37 struct map: 107580 sites in 11184 bodies; evidence {'PV': 4724, 'L': 9203, 'PTR': 9757, 'AT': 266, 'P': 4724, 'R': 86, 'FLD': 119}; at D_800B5CB8,D_800D3888,D_80181448; resolved by tools/head_types.py (max-site split); decisions: docs/struct-map-decisions.md */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u16 unk36;
    /* 0x0038 */ s16 unk38;
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u8 pad3C[0x2];
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u8 pad40[0x2];
    /* 0x0042 */ u16 unk42;
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u16 unk54;
    /* 0x0056 */ u8 pad56[0x2];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 unk5E;
    /* 0x005f */ u8 pad5F[0x1];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ s32 unk68;
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ s16 unk7C;
    /* 0x007e */ s16 unk7E;
    /* 0x0080 */ s16 unk80;
    /* 0x0082 */ s16 unk82;
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u16 unk86;
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x2];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ s16 unk9A;
    /* 0x009c */ s32 unk9C;
    /* 0x00a0 */ u8 padA0[0x4];
    /* 0x00a4 */ s32 unkA4;
    /* 0x00a8 */ s16 unkA8;
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ s16 unkAC;
    /* 0x00ae */ s16 unkAE;
    /* 0x00b0 */ s32 unkB0;
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u8 padB8[0x4];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 unkC0;
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 unkC3;
    /* 0x00c4 */ s32 unkC4;
    /* 0x00c8 */ u8 unkC8;
    /* 0x00c9 */ u8 unkC9;
    /* 0x00ca */ u8 padCA[0x2];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ s32 unkD8;
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ s32 unkE4;
    /* 0x00e8 */ s32 unkE8;
    /* 0x00ec */ s16 unkEC;
    /* 0x00ee */ s16 unkEE;
    /* 0x00f0 */ u8 unkF0;
    /* 0x00f1 */ u8 unkF1;
    /* 0x00f2 */ u16 unkF2;
    /* 0x00f4 */ s32 unkF4;
    /* 0x00f8 */ s32 unkF8;
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ s16 unk102;
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ u16 unk108;
    /* 0x010a */ s16 unk10A;
} Unkstruct_800B5CB8; /* size = 0x10c */

typedef struct {
    /* P37 struct map: 65397 sites in 17047 bodies; evidence {'PV': 1050, 'L': 1271, 'AT': 1, 'P': 1050, 'PTR': 1, 'FLD': 14}; at D_80126B58; resolved by tools/head_types.py (max-site split); decisions: docs/struct-map-decisions.md */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ s16 unk26;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ s32 unk38;
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ s16 unk3E;
    /* 0x0040 */ s16 unk40;
    /* 0x0042 */ s16 unk42;
    /* 0x0044 */ u32 unk44;
    /* 0x0048 */ u8 pad48[0x5];
    /* 0x004d */ u8 unk4D;
    /* 0x004e */ u8 unk4E;
    /* 0x004f */ u8 unk4F;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s32 unk5C;
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u16 unk64;
    /* 0x0066 */ u16 unk66;
    /* 0x0068 */ s16 unk68;
    /* 0x006a */ s16 unk6A;
    /* 0x006c */ s16 unk6C;
    /* 0x006e */ u8 pad6E[0x2];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ s16 unk72;
    /* 0x0074 */ s16 unk74;
    /* 0x0076 */ u8 pad76[0x2];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u16 unk7C;
    /* 0x007e */ u16 unk7E;
    /* 0x0080 */ u8 pad80[0x2];
    /* 0x0082 */ u16 unk82;
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u16 unk86;
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x2];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0xe];
    /* 0x00a8 */ u8 unkA8;
    /* 0x00a9 */ u8 unkA9;
    /* 0x00aa */ u16 unkAA;
    /* 0x00ac */ u16 unkAC;
    /* 0x00ae */ u16 unkAE;
    /* 0x00b0 */ s32 unkB0;
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u16 unkBA;
    /* 0x00bc */ u8 unkBC;
    /* 0x00bd */ s8 unkBD;
    /* 0x00be */ u8 unkBE;
    /* 0x00bf */ u8 unkBF;
    /* 0x00c0 */ s32 unkC0;
    /* 0x00c4 */ u8 padC4[0x4];
    /* 0x00c8 */ u8 unkC8;
    /* 0x00c9 */ u8 unkC9;
    /* 0x00ca */ u8 padCA[0x2];
    /* 0x00cc */ u32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u16 unkD4;
    /* 0x00d6 */ s16 unkD6;
    /* 0x00d8 */ u8 padD8[0x2];
    /* 0x00da */ u8 unkDA;
    /* 0x00db */ u8 padDB[0x1];
    /* 0x00dc */ s8 unkDC;
    /* 0x00dd */ u8 unkDD;
    /* 0x00de */ s8 unkDE;
    /* 0x00df */ u8 unkDF;
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ s16 unkE2;
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ u8 padE6[0x2];
    /* 0x00e8 */ s32 unkE8;
    /* 0x00ec */ s16 unkEC;
    /* 0x00ee */ s16 unkEE;
    /* 0x00f0 */ u8 padF0[0x2];
    /* 0x00f2 */ s16 unkF2;
    /* 0x00f4 */ s16 unkF4;
    /* 0x00f6 */ s16 unkF6;
    /* 0x00f8 */ u8 padF8[0x4];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x1];
    /* 0x00ff */ u8 unkFF;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
    /* 0x0108 */ u16 unk108;
    /* 0x010a */ u16 unk10A;
    /* 0x010c */ u8 pad10C[0xc];
    /* 0x0118 */ s16 unk118;
    /* 0x011a */ s16 unk11A;
    /* 0x011c */ s16 unk11C;
    /* 0x011e */ u8 pad11E[0x2];
    /* 0x0120 */ s16 unk120;
    /* 0x0122 */ s16 unk122;
    /* 0x0124 */ s16 unk124;
    /* 0x0126 */ u8 pad126[0x2];
    /* 0x0128 */ s16 unk128;
    /* 0x012a */ s16 unk12A;
    /* 0x012c */ s16 unk12C;
    /* 0x012e */ s16 unk12E;
    /* 0x0130 */ u16 unk130;
    /* 0x0132 */ s16 unk132;
    /* 0x0134 */ u8 pad134[0x2];
    /* 0x0136 */ u16 unk136;
    /* 0x0138 */ s16 unk138;
    /* 0x013a */ s16 unk13A;
    /* 0x013c */ s16 unk13C;
    /* 0x013e */ s16 unk13E;
    /* 0x0140 */ u8 pad140[0x1a];
    /* 0x015a */ u16 unk15A;
    /* 0x015c */ u8 pad15C[0x10];
    /* 0x016c */ u16 unk16C;
    /* 0x016e */ u16 unk16E;
    /* 0x0170 */ s32 unk170;
    /* 0x0174 */ s32 unk174;
    /* 0x0178 */ s32 unk178;
    /* 0x017c */ u8 pad17C[0x8];
    /* 0x0184 */ s32 unk184;
    /* 0x0188 */ s16 unk188;
    /* 0x018a */ s16 unk18A;
    /* 0x018c */ s32 unk18C;
    /* 0x0190 */ u8 pad190[0x4];
    /* 0x0194 */ u16 unk194;
    /* 0x0196 */ u8 unk196;
    /* 0x0197 */ u8 unk197;
    /* 0x0198 */ s32 unk198;
    /* 0x019c */ u8 pad19C[0x4];
    /* 0x01a0 */ u8 unk1A0;
    /* 0x01a1 */ u8 pad1A1[0x9];
    /* 0x01aa */ u8 unk1AA;
    /* 0x01ab */ u8 unk1AB;
    /* 0x01ac */ s32 unk1AC;
    /* 0x01b0 */ s32 unk1B0;
    /* 0x01b4 */ s32 unk1B4;
    /* 0x01b8 */ u16 unk1B8;
    /* 0x01ba */ u16 unk1BA;
    /* 0x01bc */ u8 pad1BC[0x4];
    /* 0x01c0 */ u8 unk1C0;
    /* 0x01c1 */ u8 pad1C1[0x5];
    /* 0x01c6 */ u8 unk1C6;
    /* 0x01c7 */ s8 unk1C7;
    /* 0x01c8 */ u16 unk1C8;
    /* 0x01ca */ s16 unk1CA;
    /* 0x01cc */ s16 unk1CC;
    /* 0x01ce */ s16 unk1CE;
    /* 0x01d0 */ s16 unk1D0;
    /* 0x01d2 */ u8 pad1D2[0x2];
    /* 0x01d4 */ s32 unk1D4;
    /* 0x01d8 */ s32 unk1D8;
    /* 0x01dc */ u8 pad1DC[0x18];
    /* 0x01f4 */ u32 unk1F4;
    /* 0x01f8 */ s32 unk1F8;
    /* 0x01fc */ s32 unk1FC;
    /* 0x0200 */ s32 unk200;
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ s32 unk208;
    /* 0x020c */ s16 unk20C;
    /* 0x020e */ s16 unk20E;
    /* 0x0210 */ s16 unk210;
    /* 0x0212 */ s16 unk212;
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ s8 unk215;
    /* 0x0216 */ u8 unk216;
    /* 0x0217 */ u8 pad217[0x1];
    /* 0x0218 */ u8 unk218;
    /* 0x0219 */ u8 pad219[0x3];
    /* 0x021c */ s32 unk21C;
    /* 0x0220 */ u8 pad220[0x1];
    /* 0x0221 */ s8 unk221;
    /* 0x0222 */ u8 pad222[0x1];
    /* 0x0223 */ u8 unk223;
    /* 0x0224 */ u8 pad224[0x10];
    /* 0x0234 */ s32 unk234;
    /* 0x0238 */ s32 unk238;
    /* 0x023c */ s32 unk23C;
    /* 0x0240 */ s32 unk240;
    /* 0x0244 */ u16 unk244;
    /* 0x0246 */ u16 unk246;
    /* 0x0248 */ u16 unk248;
    /* 0x024a */ s16 unk24A;
} Unkstruct_80126B58; /* size = 0x24c */
/* head_types:end */

/* Unkstruct_80078E78 — the player record at 0x80078E78 (0x98 bytes; was Blk98_80029274 in src/800.c, Blk80078E78 in
   src/resident/resident_jr_800D00E4.c, u8 D_80078E78[] in 880 TUs). Hand-written (P38 T3): field widths are the type the
   USING TUs declare for each scalar global (.run/P38/T3/player_use_widths.py); names only where docs/memory-map.md 3.4
   or docs/actor-struct.md mark the row verified. Decisions: docs/struct-map-decisions.md. */
typedef struct {
    /* 0x0000 */ s32 unk0;          /* D_80078E78 word 0 */
    /* 0x0004 */ u8 unk4;           /* D_80078E7C; reported: gameClock */
    /* 0x0005 */ u8 unk5;           /* D_80078E7D */
    /* 0x0006 */ u8 unk6;           /* D_80078E7E */
    /* 0x0007 */ u8 unk7;           /* D_80078E7F */
    /* 0x0008 */ s32 unk8;          /* D_80078E80; reported: storyProgress; map: pointer into Unkstruct_800B5CB8 */
    /* 0x000c */ s32 unkC;          /* D_80078E84; map: pointer into Unkstruct_800B5CB8 */
    /* 0x0010 */ s32 unk10;         /* D_80078E88; map: pointer into Unkstruct_800B5CB8 */
    /* 0x0014 */ s32 gold;          /* D_80078E8C; verified live (stored as gold/10), memory-map 3.4; code width s32 */
    /* 0x0018 */ s16 unk18;         /* D_80078E90 */
    /* 0x001a */ s16 unk1A;         /* D_80078E92 */
    /* 0x001c */ s32 unk1C;         /* D_80078E94; s16 D_80078E96 at +0x1E loses (5 uses) */
    /* 0x0020 */ s32 unk20;         /* D_80078E98; s16 D_80078E9A at +0x22 loses (1 use) */
    /* 0x0024 */ s32 unk24;         /* D_80078E9C; s16 D_80078E9E at +0x26 loses (2 uses) */
    /* 0x0028 */ s32 unk28;         /* D_80078EA0 */
    /* 0x002c */ s32 tiredness_raw; /* D_80078EA4; verified live, memory-map 3.4; u16 D_80078EA6 at +0x2E loses (8 uses) */
    /* 0x0030 */ s32 unk30;         /* D_80078EA8 */
    /* 0x0034 */ u16 dayCounter;    /* D_80078EAC; verified live + code (func_8014B084), memory-map 3.4 */
    /* 0x0036 */ u8 unk36;          /* D_80078EAE */
    /* 0x0037 */ u8 unk37;          /* D_80078EAF; not dayOfWeek (refuted, memory-map 3.4) */
    /* 0x0038 */ u8 unk38;          /* D_80078EB0 low byte; s16 D_80078EB0 (524 uses) spans +0x38..+0x39: union candidate */
    /* 0x0039 */ u8 hour;           /* D_80078EB1; verified live, memory-map 3.4 */
    /* 0x003a */ u16 hp_max;        /* D_80078EB2; verified live */
    /* 0x003c */ s16 hp_current;    /* D_80078EB4; verified live; s16 by 689 vs 135 uses */
    /* 0x003e */ u16 bp_max;        /* D_80078EB6; verified live */
    /* 0x0040 */ s16 bp_current;    /* D_80078EB8; verified live; s16 by 12 vs 3 uses */
    /* 0x0042 */ u8 dayOfWeek;      /* D_80078EBA; verified (code, func_8014B084) */
    /* 0x0043 */ u8 unk43;          /* D_80078EBB */
    /* 0x0044 */ u8 unk44;          /* no scalar global; u8 by md_MAIN_011's local player-block copies (P38 T4) */
    /* 0x0045 */ u8 unk45;          /* as unk44 */
    /* 0x0046 */ u8 unk46;          /* as unk44 */
    /* 0x0047 */ u8 unk47;          /* D_80078EBF */
    /* 0x0048 */ u8 unk48;          /* D_80078EC0 */
    /* 0x0049 */ u8 unk49;          /* D_80078EC1 */
    /* 0x004a */ u8 unk4A;          /* D_80078EC2 */
    /* 0x004b */ u8 unk4B;          /* D_80078EC3 */
    /* 0x004c */ s8 unk4C;          /* D_80078EC4 */
    /* 0x004d */ u8 unk4D;          /* D_80078EC5 */
    /* 0x004e */ s8 unk4E;          /* D_80078EC6 */
    /* 0x004f */ u8 pad4F[0x1];
    /* 0x0050 */ s32 unk50;         /* D_80078EC8 */
    /* 0x0054 */ s32 unk54;         /* D_80078ECC */
    /* 0x0058 */ s32 unk58;         /* D_80078ED0 */
    /* 0x005c */ s32 unk5C;         /* D_80078ED4 */
    /* 0x0060 */ s32 unk60;         /* D_80078ED8 */
    /* 0x0064 */ s32 unk64;         /* D_80078EDC */
    /* 0x0068 */ u8 unk68;          /* D_80078EE0 */
    /* 0x0069 */ u8 pad69[0x3];
    /* 0x006c */ s32 unk6C;         /* D_80078EE4; reported: bodyLevel */
    /* 0x0070 */ s32 unk70;         /* D_80078EE8; reported: bodyExp */
    /* 0x0074 */ s32 unk74;         /* D_80078EEC; reported: mindLevel */
    /* 0x0078 */ s32 unk78;         /* D_80078EF0; reported: mindExp; actor-struct.md's s16 step counter conflicts with code width s32 */
    /* 0x007c */ s32 unk7C;         /* D_80078EF4; reported: fusionLevel */
    /* 0x0080 */ s32 unk80;         /* D_80078EF8; reported: fusionExp */
    /* 0x0084 */ s32 unk84;         /* D_80078EFC; reported: luminaLevel */
    /* 0x0088 */ s32 unk88;         /* D_80078F00; reported: luminaExp */
    /* 0x008c */ s32 unk8C;         /* D_80078F04 */
    /* 0x0090 */ s32 posX;          /* D_80078F08; verified live + code width 4 (actor-struct.md, census control) */
    /* 0x0094 */ s32 posZ;          /* D_80078F0C; verified live + code width 4 */
} Unkstruct_80078E78; /* size = 0x98 */

/* --- lift_types.py --census (P38 T5.1.c2, batch ov-file) --- */
typedef struct { s32 w[8]; } Blk20_8016DF5C;
typedef Blk20_8016DF5C Blk20;
typedef struct {
    u8 c[8];
} Blk8_801867AC;
typedef Blk8_801867AC Blk8;
typedef struct { u32 tag; u32 w1; u32 w2; u32 w3; } Prim_1412A8;
typedef Prim_1412A8 Blk16;
typedef struct { s32 vpx, vpy, vpz, vrx, vry, vrz, rz, super; } RView;
typedef struct { u32 addr : 24; u32 len : 8; u8 r0, g0, b0, code; } P_TAG;
typedef Blk20_8016DF5C Blk32;
typedef struct Bar {
    unsigned char b0;     /* 0x0 */
    unsigned char b1;     /* 0x1 */
    unsigned char b2;     /* 0x2 */
    unsigned char tag;    /* 0x3 */
    unsigned int a;       /* 0x4 */
    unsigned int b;       /* 0x8 */
} Bar;
typedef struct { u32 w[38]; } Blk152;
typedef struct { s32 f0; } E4;
typedef struct { s32 f0; u8 pad[0x18]; } E_3B7AC_8013B7AC;
typedef E_3B7AC_8013B7AC E_3B7AC;
typedef struct Foo {
    unsigned char pad[0xc];
    unsigned int count;   /* 0xc */
    int field10;          /* 0x10 */
} Foo;
typedef struct {
    s16 m[9];    /* 0x00 */
    s16 pad;     /* 0x12 */
    s32 t[3];    /* 0x14, 0x18, 0x1c */
    s32 rest[8]; /* 0x20..0x3f */
} Mtx_8016BFD0;
typedef Mtx_8016BFD0 Mtx;
typedef struct Obj_8016AB6C {
    s32 unk0;
    s32 unk4;
    u8  pad8[0xE - 0x8];
    s16 unkE;
    u8  pad10[0x24 - 0x10];
    u8  unk24, unk25, unk26, unk27;
    u8  pad28[0x2E - 0x28];
    s16 unk2E;
    s16 unk30;
} Obj_8016AB6C;
typedef struct Ent_8016AB6C {
    u16 unk0, unk2, unk4, unk6, unk8, unkA, unkC, unkE;
    s32 unk10, unk14, unk18, unk1C;
    Obj_8016AB6C *unk20;
    s16 unk24, unk26, unk28, unk2A;
    s32 unk2C;
    s32 unk30;
} Ent_8016AB6C;
typedef struct { char s[10]; } S10_80136C90;
typedef struct { short vx, vy, vz, pad; } SVECTOR;
typedef SVECTOR SVec_8016AB6C;
typedef struct { char pad_8013BC7C[0x68]; s32 f68; } S_8013BC7C_8013BC7C;
typedef S_8013BC7C_8013BC7C S_8013BC7C;
typedef struct {
    u8  b0;
    u8  b1;
    u8  b2;
    u8  type;
    u32 w1;
    u32 w2;
} T3Reloc;
typedef struct { s16 x, y, z; } Vec3s;
typedef struct { char b[4]; } W_8016BFD0;
typedef W_8016BFD0 W;
typedef void (*code)(unsigned short *);
typedef struct { short m[3][3]; long t[3]; } MATRIX;
struct S80190C84 {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10;
};
typedef struct {
    s32 word0;
    s32 word4;
} CdFileLoc;
typedef struct {
        u8    pad0[8];
        void *f8;
        void *fC;
    } E_13BD74;
typedef struct {
        u8   pad0[8];
        void *f8;
        void *fC;
    } E_13C08C_8013C08C;
typedef E_13C08C_8013C08C E_13C08C;
typedef struct {
        s32 f0;
        u16 f4;
        u16 f6;
        u16 f8;
        u16 fA;
        s32 fC;
        u8  pad[0xC];
    } Ent_8013B6A0_8013B6A0;
typedef Ent_8013B6A0_8013B6A0 Ent_8013B6A0;
typedef struct {
        s32 f0;
        u16 f4;
        u16 f6;
        u16 f8;
        u16 fA;
        s32 fC;
        u8  pad[8];
        s32 f18;
    } Ent_8013B83C;
typedef struct 
  {
    u32 *ot;
    u32 pad[4];
  } Env_80140958;
typedef Env_80140958 Env_800D29F8;
typedef struct {
        u8  pad0[3];
        u8  code;
        s32 f4;
        s32 f8;
    } P_13BD74;
typedef Ent_8013B6A0_8013B6A0 Spr_8013B598;
typedef struct { u16 f0; u16 f2; u16 f4; } Src_8013B598_8013B598;
typedef Src_8013B598_8013B598 Src_8013B598;
typedef struct {
        u16 f0;
        u16 f2;
        u16 f4;
    } Src_8013B6A0_8013B6A0;
typedef Src_8013B6A0_8013B6A0 Src_8013B6A0;
typedef struct { s16 vx, vy; } DVECTOR;
typedef DVECTOR DVEC2_C974_8017BA3C;
typedef MATRIX MTX_C974;
typedef struct { u16 x, y, z, w; } __attribute__((aligned(2))) V;
typedef V Pt_8017D87C;
typedef SVECTOR SV;
typedef SVECTOR SVEC2_C974_8017BA3C;
typedef struct { u8 b[4]; } __attribute__((packed, aligned(1))) Block4;
typedef Block4 Blk4;
typedef struct { u8 b[4]; } B4_8017F154;
typedef B4_8017F154 Blk4_md_SC07_003;
typedef SVECTOR SVECTOR_800;

/* --- lift_types.py --census (P38 T5.1.c2, batch ov-block) --- */
typedef Blk8_801867AC Blk8_md_SC03_076;
typedef struct {
    unsigned int addr : 24;
    unsigned int len : 8;
} PrimTag;
typedef PrimTag PTag;
typedef Prim_1412A8 St801D9204;
typedef E4 Unkstruct_801151D0;
typedef struct { s32 vx, vy, vz, pad; } Vec32;
typedef Vec32 V32;

/* --- lift_types.py --census (P38 T5.1.c2, batch md) --- */
struct packed_word { int w; } __attribute__((packed, aligned(1)));
typedef struct packed_word Align1W_801AD068;
typedef struct { u8 b[4]; } B4_CB578;
typedef struct {
    u8 unk0[8];
} B8_801AEB04;
typedef struct { u8 b[8]; } B8_CB578;
typedef Blk152 Blk152_8017DF40_801E48B8;
typedef Blk152 Blk152_8017DF40_801E9DF8;
typedef Blk152 Blk152_8017DF40_801EFC58;
typedef Blk152 Blk152_8017DF40_801F1738;
typedef struct { s32 w0, w1, w2, w3; } Blk16X;
typedef struct {
    s32 a, b, c, d;
} Blk16_md_MAIN_016;
typedef Blk20_8016DF5C Blk20_800CB68C;
typedef struct {
    s32 w[8];
} Blk32_801A5194;
typedef Blk20_8016DF5C Blk32_CB1EC;
typedef struct {
    char c[3];
} Blk3_801E40A8;
typedef struct {
    char c[3];
} Blk3_801E95E8;
typedef struct { char c[3]; } Blk3_801EF448;
typedef struct {
    char c[3];
} Blk3_8017D730;
typedef Blk3_8017D730 Blk3_801F0F28;
typedef Block4 Blk4_8017DF40_801E48B8;
typedef Block4 Blk4_8017DF40_801E9DF8;
typedef Block4 Blk4_8017DF40_801EFC58;
typedef Block4 Blk4_8017DF40_801F1738;
typedef struct { char c[4]; } Blk4_801A40CC;
typedef struct {char c [ 4 ] ;} Unkstruct_801A01E8;
typedef Unkstruct_801A01E8 Blk4_801A7358;
typedef Unkstruct_801A01E8 Blk4_801AB8C0;
typedef struct { char c[4]; } Blk4_md_SC07_004_801ACE5C;
typedef Blk4_md_SC07_004_801ACE5C Blk4_801AD31C;
typedef Unkstruct_801A01E8 Blk4_md_SC07_004_801A8228;
typedef struct { u16 a, b, c, d; } Blk8_801A6AD0;
typedef struct { u16 a, b, c, d; } Blk8_801AD914;
typedef struct {
    u32 field0;
    u32 field1;
} __attribute__((packed, aligned(1))) BlockData;
typedef BlockData Blk8_md_MAIN_027;
typedef struct { char c[8]; } Blk8_md_MAIN_031;
typedef struct { char c[8]; } Blk8_md_SC07_003_801A3638;
typedef struct { u16 w0, w1, w2, w3; } Blk8_md_SC07_004_801AA9D4;
typedef struct { s32 w[4]; } Blk_800CBAD0;
typedef struct {
    s32 w[8];
} Block32;
typedef struct { s32 w[4]; } CB4A4_V4;
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} CVECTOR;              /* libgte CVECTOR */
typedef CVECTOR Col4_8017F8BC;
typedef Col4_8017F8BC CVEC;
typedef Col4_8017F8BC CVecX;
typedef struct {
    u16 r;
    u16 g;
    u16 b;
} Col6_801A2E20;
typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} SpadRect_800184F0;
typedef SpadRect_800184F0 D24D0_Rect;
typedef struct {
    s32 unk00; /* +0x00 */
    s32 unk04; /* +0x04 */
    s32 unk08; /* +0x08 */
    s32 unk0C; /* +0x0C */
    s32 unk10; /* +0x10 */
    s32 unk14; /* +0x14 */
    s32 unk18; /* +0x18 */
    s32 unk1C; /* +0x1C */
} D_800D942C_entry;
typedef struct {
    u16 f0;                                 /* 0x0 */
    u16 f2;                                 /* 0x2 */
    u16 f4;                                 /* 0x4 */
    u16 f6;                                 /* 0x6 */
} Entry8_801A5D68;
typedef Env_80140958 Env_801E46A0;
typedef Env_80140958 Env_801E9BE0;
typedef Env_80140958 Env_801EFA40;
typedef Env_80140958 Env_801F1520;
typedef struct {          /* flat tri packet, 0x14 bytes */
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgb0;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u32 xy1;
    /* 0x10 */ u32 xy2;
} F3P_800CB1F8;
typedef struct {
    u8  addr[3];
    u8  len;
    u8  r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
    s16 x2, y2;
    s16 x3, y3;
} F4_80016450;
typedef F4_80016450 F4_801AB21C;
typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u32 rgb;
    /* 0x08 */ u16 n0;
    /* 0x0A */ u16 v0;
    /* 0x0C */ u16 v1;
    /* 0x0E */ u16 v2;
} Face10_800CB1F8;
typedef struct {                                     /* 0x14 */
    u32 w0;      /* 0x00 */
    u32 rgb;     /* 0x04 */
    u16 n0;      /* 0x08 */
    u16 v0;      /* 0x0A */
    u16 n1;      /* 0x0C */
    u16 v1;      /* 0x0E */
    u16 n2;      /* 0x10 */
    u16 v2;      /* 0x12 */
} Face2;
typedef Face2 Face14_800CB5D0;
typedef struct {
    u32 pad0;  /* 0x00 */
    u32 uv0;   /* 0x04 */
    u32 uv1;   /* 0x08 */
    u32 uv2;   /* 0x0C */
    u32 uv3;   /* 0x10 */
    u16 n0;    /* 0x14 */
    u16 v0;    /* 0x16 */
    u16 v1;    /* 0x18 */
    u16 v2;    /* 0x1A */
    u16 v3;    /* 0x1C */
    u16 pad_1E;  /* 0x1E */
} Prim20;
typedef Prim20 Face20_800CBA18;
typedef Face2 FaceF4_800CB3C0;
typedef struct {                                     /* 0x18 */
    u32 w0;      /* 0x00 */
    u32 rgb;     /* 0x04 */
    u16 n0;      /* 0x08 */
    u16 v0;      /* 0x0A */
    u16 n1;      /* 0x0C */
    u16 v1;      /* 0x0E */
    u16 n2;      /* 0x10 */
    u16 v2;      /* 0x12 */
    u16 n3;      /* 0x14 */
    u16 v3;      /* 0x16 */
} Face3;
typedef Face3 FaceGT4_800CB7BC;
typedef struct {                                        /* 0x24 */
    u32 unk00;
    u32 uv0;
    u32 uv1;
    u32 uv2;
    u32 uv3;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
    u16 n3, v3;
} FaceGT4;
typedef FaceGT4 FaceGT4_800CBE28;
typedef struct {                                     /* 0x1C */
    u32 w0;      /* 0x00 */
    u32 w1;      /* 0x04 */
    u32 w2;      /* 0x08 */
    u32 w3;      /* 0x0C */
    u16 n0;      /* 0x10 */
    u16 v0;      /* 0x12 */
    u16 n1;      /* 0x14 */
    u16 v1;      /* 0x16 */
    u16 n2;      /* 0x18 */
    u16 v2;      /* 0x1A */
} FaceT3;
typedef struct { void (*fn)(void); } FnEntry;
typedef struct {          /* libgpu POLY_FT4, 0x28 bytes */
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgb;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u32 uv0;
    /* 0x10 */ u32 xy1;
    /* 0x14 */ u32 uv1;
    /* 0x18 */ u32 xy2;
    /* 0x1C */ u32 uv2;
    /* 0x20 */ u32 xy3;
    /* 0x24 */ u32 uv3;
} Ft4_800CBA18;
typedef struct {                                     /* 0x28 */
    u32 tag;     /* 0x00 */
    u32 rgb0;    /* 0x04 */
    s16 x0, y0;  /* 0x08 */
    u16 u0, cl;  /* 0x0C */
    u32 rgb1;    /* 0x10 */
    s16 x1, y1;  /* 0x14 */
    u16 u1, tp;  /* 0x18 */
    u32 rgb2;    /* 0x1C */
    s16 x2, y2;  /* 0x20 */
    u16 u2, pd;  /* 0x24 */
} GT3P;
typedef struct {
    u32 pad00;      /* 0x00 */
    u32 unk04;      /* 0x04 */
    u32 unk08;      /* 0x08 */
    u32 unk0C;      /* 0x0C */
    u32 unk10;      /* 0x10 */
    u32 unk14;      /* 0x14 */
    u32 unk18;      /* 0x18 */
    u32 unk1C;      /* 0x1C */
    u32 unk20;      /* 0x20 */
    u32 unk24;      /* 0x24 */
    u32 unk28;      /* 0x28 */
    u32 unk2C;      /* 0x2C */
    u32 unk30;      /* 0x30 */
    s16 unk34;      /* 0x34 */
    u8  unk36;      /* 0x36 */
    u8  unk37;      /* 0x37 */
    s16 unk38;      /* 0x38 */
    s16 unk3A;      /* 0x3A */
    s16 unk3C;      /* 0x3C */
    s16 unk3E;      /* 0x3E */
    s16 unk40;      /* 0x40 */
    u8  unk42;      /* 0x42 */
    u8  unk43;      /* 0x43 */
    u8  unk44;      /* 0x44 */
    u8  unk45;      /* 0x45 */
    u8  unk46;      /* 0x46 */
    u8  unk47;      /* 0x47 */
    u8  unk48;      /* 0x48 */
    u8  unk49;      /* 0x49 */
    u8  unk4A;      /* 0x4A */
    u8  unk4B;      /* 0x4B */
    u8  unk4C;      /* 0x4C */
    u8  pad4D[3];   /* 0x4D */
    u32 unk50;      /* 0x50 */
    u32 unk54;      /* 0x54 */
    u32 unk58;      /* 0x58 */
    u32 unk5C;      /* 0x5C */
    u32 unk60;      /* 0x60 */
    u32 unk64;      /* 0x64 */
    u8  unk68;      /* 0x68 */
    u8  pad69[3];   /* 0x69 */
    u32 unk6C;      /* 0x6C */
    u32 unk70;      /* 0x70 */
    u32 unk74;      /* 0x74 */
    u32 unk78;      /* 0x78 */
    u32 unk7C;      /* 0x7C */
    u32 unk80;      /* 0x80 */
    u32 unk84;      /* 0x84 */
    u32 unk88;      /* 0x88 */
    u32 unk8C;      /* 0x8C */
    u32 unk90;      /* 0x90 */
    u32 unk94;      /* 0x94 */
} Gs_80078E78_init;
typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s16 unk34;
    u8 unk36;
    u8 unk37;
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    u8 unk68;
    u8 pad69[3];
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    s32 unk90;
    s32 unk94;
} Gs_80078E78_md_MAIN_011;
typedef struct {
    u16 hB0;
    u16 hB2;
    u32 hpad;
} HB;
typedef struct { s32 w[4]; } M16;
typedef struct M4_801A0168 {
    u8 unk0[4];
} M4_801A0168;
typedef struct { u8 unk0[4]; } M4_801AE734;
typedef struct {
    u8 unk0[4];
} M4_801AEB04;
typedef MATRIX MATRIX_801EDED4;
typedef MATRIX MATRIX_801EDED4_801E2B14;
typedef MATRIX MATRIX_801EDED4_801E5124;
typedef MATRIX MATRIX_801EDED4_801E8054;
typedef MATRIX MATRIX_801EDED4_801E805C;
typedef MATRIX MATRIX_801EDED4_801EA664;
typedef MATRIX MATRIX_801EDED4_801EDED4;
typedef MATRIX MATRIX_801EDED4_801EF99C;
typedef MATRIX MATRIX_801EDED4_801F04DC;
typedef MATRIX MATRIX_801EDED4_801F1F94;
typedef MATRIX MATRIX_md_SC07_003;
typedef MATRIX MTX_800CB4E4;
typedef MATRIX MTX_800CB910;
typedef MATRIX MTX_800CBD54;
typedef MATRIX MTX_801A1B28;
typedef MATRIX MTX_801A8990;
typedef MATRIX MTX_801AA7E4;
typedef MATRIX MTX_801AACD4;
typedef MATRIX MTX_801AAF8C;
typedef MATRIX MTX_801ADC40;
typedef MATRIX MTX_C974_801E3540;
typedef MATRIX MTX_C974_801E8A80;
typedef MATRIX MTX_C974_801EE8E0;
typedef MATRIX MTX_C974_801F03C0;
typedef MATRIX MTX_CB578;
typedef MATRIX MTX_CF90_801A3624;
typedef MATRIX MTX_md_MAIN_039;
typedef struct {
    u8 mat[0x14];
    u32 zz[3] __attribute__((aligned(4)));
} __attribute__((packed)) MZ;
typedef struct { s32 w0, w4, w8, wC; s16 h10, hpad; s32 t0, t1, t2; } Mat32;
typedef Mat32 Mat32_801A4EBC;
typedef struct { s16 m[16]; } Mat801A8E34;
struct Mid { u32 gray[4]; u32 code; u8 bmode; };
typedef Blk20_8016DF5C Mtx32_801A2400;
typedef Blk20_8016DF5C Mtx32_801A3180;
typedef MATRIX Mtx32_801A3B18;
typedef Blk20_8016DF5C Mtx32_801A3D60;
typedef MATRIX Mtx32_801A4D58;
typedef MATRIX Mtx32_801A4DFC;
typedef MATRIX Mtx32_801A52DC;
typedef MATRIX Mtx32_801A54F0;
typedef MATRIX Mtx32_801A5698;
typedef Blk20_8016DF5C Mtx32_801A90D8;
typedef MATRIX Mtx32b;
struct B  { s32 w[8]; s32 tail[2]; };
typedef struct B Mtx40;
typedef MATRIX MtxX;
typedef MATRIX Mtx_800CD27C;
typedef struct {
    Mtx_800CD27C mt; /* 0x00 */
    s32 rest[2];     /* 0x20..0x27 — frame padding, never touched */
} MtxBuf_800CD27C;
typedef MATRIX Mtx_801A6184;
typedef MATRIX Mtx_801AEC38;
typedef struct { s16 m[3][3]; s16 t[3]; s16 pad[4]; } Mtx_A8CE0 __attribute__((aligned(8)));
typedef struct { s32 next; u8 pad[0xC]; } Node_801F28E0;
typedef Node_801F28E0 Node_801E5AAC;
typedef Node_801F28E0 Node_801F0E9C;
typedef struct {
    u8 pad[0xE0];
    s32 dE0;  /* 0xE0 */
    s32 dE4;  /* 0xE4 */
} Obj_801AD068;
typedef struct { s32 a; s32 b[4]; } OtBlk_80180894;
typedef OtBlk_80180894 OtBlk_8018A974_801AADA8;
typedef PrimTag PTag293C;
typedef PrimTag PTag_800CF3E8;
typedef P_TAG PTag_801AEC38;
typedef PrimTag PTag_801E46A0;
typedef PrimTag PTag_801E9BE0;
typedef PrimTag PTag_801EFA40;
typedef PrimTag PTag_801F1520;
typedef PrimTag P_TAG_md_MAIN_007_800CF6D0;
typedef struct {
    u16 v;                                  /* 0x0 */
    u16 pad;                                /* 0x2 */
} Pair4_801B02DC;
typedef struct {          /* flat quad packet, 0x18 bytes */
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgb0;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u32 xy1;
    /* 0x10 */ u32 xy2;
    /* 0x14 */ u32 xy3;
} PktF4_800CB3C0;
typedef struct {
    u32 tag;
    u32 rgb0, xy0;
    u32 rgb1, xy1;
    u32 rgb2, xy2;
    u32 rgb3, xy3;
} PktGT4_800CB7BC;
typedef struct {                                        /* 0x34 */
    u32 tag;
    u32 rgb0, xy0, uv0;
    u32 rgb1, xy1, uv1;
    u32 rgb2, xy2, uv2;
    u32 rgb3, xy3, uv3;
} PktGT4;
typedef PktGT4 PktGT4_800CBE28;
typedef struct {          /* flat gouraud tri packet, 0x1C bytes */
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgb0;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u32 rgb1;
    /* 0x10 */ u32 xy1;
    /* 0x14 */ u32 rgb2;
    /* 0x18 */ u32 xy2;
} Prim1C_800CB5D0;
typedef struct {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    s32 f10;
} Prim293C;
typedef struct { u16 f0; u16 f2; } Prim4_801E46A0;
typedef struct {
    s16 f0;                     /* 0x00 */
    s16 f2;                     /* 0x02 */
    void *f4;                   /* 0x04 */
    void *f8;                   /* 0x08 */
    s16 fC;                     /* 0x0C */
    s16 fE;                     /* 0x0E */
    s16 f10;                    /* 0x10 */
    s16 f12;                    /* 0x12 */
    void *f14;                  /* 0x14 */
    Prim4_801E46A0 *f18;        /* 0x18 */
    void *f1C;                  /* 0x1C */
} Panel_801E46A0;
typedef struct { u16 f0; u16 f2; } Prim4_801E9BE0;
typedef struct { u16 f0; u16 f2; } Prim4_801EFA40;
typedef Panel_801E46A0 Panel_801EFA40;
typedef struct { u16 f0; u16 f2; } Prim4_8017DD28;
typedef Prim4_8017DD28 Prim4_801F1520;
typedef Panel_801E46A0 Panel_801F1520;
typedef struct Prim801A2014 {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 f06;
    /* 0x08 */ s16 f08;
    /* 0x0A */ s16 f0A;
    /* 0x0C */ s16 f0C;
    /* 0x0E */ s16 f0E;
    /* 0x10 */ s32 f10;
} Prim801A2014;
typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
} Quad4_800CCB14;
typedef Quad4_800CCB14 Quad4_800CCAD0;
typedef struct {
    /* 0x0 */ s16 a;
    /* 0x2 */ s16 b;
    /* 0x4 */ s32 c;
} Rec8_801A026C;
typedef struct { u16 a, b, c, d; } Rec8_801A57E8;
typedef struct { u16 f0, f1, f2, f3, f4, f5; } Rec_md_MAIN_047_800CCBC0;
typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s16 unk34;
    u8 unk36;
    u8 unk37;
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 pad4D[3];
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    u8 unk68;
    u8 pad69[3];
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    s32 unk90;
    s32 unk94;
} S1254;
typedef struct { s32 f10, f14, f18; } S12_801AD700;
typedef struct { s32 f10, f14, f18; } S12_801AD914;
typedef struct { u16 h; } H16;
typedef H16 S16_800CF3E8;
typedef struct { s32 w[4]; } S16_md_MAIN_014_800CB254;
typedef struct {
    s8 pad00[4];
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s16 unk34;
    u8 unk36;
    u8 unk37;
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    u8 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    s32 unk90;
    s32 unk94;
} S2BC4;
typedef struct { u8 pad_0[0x34]; u16 st; } Ent34;
typedef Ent34 S34_801A1470;
typedef struct { char c[4]; } S4_800CD054;
typedef struct { s16 unk00; s16 unk02; s16 unk04; } S6;
typedef E4 S70;
typedef struct { s32 pad00[8]; u16 f20; } SH20;
typedef struct { u8 pad00[0x1A]; u16 f1A; } SP18;
typedef SVECTOR SV3_801A4570;
typedef struct {
    u16 x;      /* +0x0 */
    u16 y;      /* +0x2 */
    u16 num;    /* +0x4 */
    u16 count;  /* +0x6 */
} SV4_801AAB28;
typedef SV4_801AAB28 SV4R_801AAA6C;
typedef struct { s32 x, y, z; } VEC_8017DF28;
typedef VEC_8017DF28 SV4_md_SC03_135_801E585C;
typedef SVECTOR SVEC2;
typedef SVECTOR SVEC8_800CB1F8;
typedef SVECTOR SVEC8_800CB3C0;
typedef SVECTOR SVEC8_800CB5D0;
typedef SVECTOR SVEC8_800CB7BC;
typedef SVECTOR SVEC8_800CBA18;
typedef SVECTOR SVEC8_800CBE28;
typedef SVECTOR SVECTOR_801A52DC;
typedef struct {
    SVECTOR_801A52DC v[4];
    s32 f0;
    s32 f1;
    s32 f2;
    s32 f3;
    s32 f4;
} Prim_801A52DC;
typedef SVECTOR SVECTOR_801EDED4;
typedef SVECTOR SVECTOR_801EDED4_801E2B14;
typedef SVECTOR SVECTOR_801EDED4_801E5124;
typedef SVECTOR SVECTOR_801EDED4_801E8054;
typedef SVECTOR SVECTOR_801EDED4_801E805C;
typedef SVECTOR SVECTOR_801EDED4_801EA664;
typedef SVECTOR SVECTOR_801EDED4_801EDED4;
typedef SVECTOR SVECTOR_801EDED4_801EF99C;
typedef SVECTOR SVECTOR_801EDED4_801F04DC;
typedef SVECTOR SVECTOR_801EDED4_801F1F94;
typedef SVECTOR SVEC_md_MAIN_047_800CCBC0;
typedef struct { SVEC_md_MAIN_047_800CCBC0 v0, v1, v2, v3; CVEC c0, c1, c2, c3; s32 tag; } Prim_md_MAIN_047_800CCBC0;
typedef SVECTOR SV_800CB4E4;
typedef SVECTOR SV_800CB910;
typedef struct { u16 vx, vy, vz, pad; } SVECTOR_8017E6D8;
typedef SVECTOR_8017E6D8 SV_801A1B28;
typedef SVECTOR SV_801A54F0;
typedef SVECTOR_8017E6D8 SV_801A8990;
typedef SVECTOR SV_801A90D8;
typedef struct {
    s16 vx, vy, vz;
} UVec_8017DB64;
typedef UVec_8017DB64 SV_801AA210;
typedef SVECTOR SV_801AA7E4;
typedef SVECTOR SV_801AACD4;
typedef SVECTOR SV_801AAF8C;
typedef SVECTOR SV_801ADC40;
typedef SVECTOR SVec16_801A8B64;
typedef SVECTOR SVec801A38E4;
typedef struct { s16 x, y, z, w; } V8_80184F90_801844C8;
typedef V8_80184F90_801844C8 SVec801A5674;
typedef struct { SVec801A5674 v[2]; s32 col[2]; s32 tag; s32 pad; } Prim801A5674;
typedef struct { s16 m[4]; } SVec801A8E34;
typedef SVECTOR SVecX;
typedef struct { SVecX v[4]; CVecX c[4]; s32 code; s32 pad_34; } PrimX;
typedef SVECTOR SVec_801A2400;
typedef SVECTOR SVec_801A3180;
typedef SVECTOR SVec_801A39D0;
typedef SVECTOR SVec_801A3B18;
typedef SVECTOR SVec_801A4680;
typedef struct {
    SVECTOR v[4];                       /* 0x00 */
    s16 u0, t0, u1, t1, u2, t2, u3, t3;       /* 0x20 */
    u32 bcast;                                /* 0x30 */
    s32 tag;                                  /* 0x34 */
    u8  code;                                 /* 0x38 */
    u8  pad39[7];                             /* 0x39 -> 0x40 */
} Prim_80183F84;
typedef Prim_80183F84 Prim_801A4680;
typedef SVECTOR SVec_801A5698;
typedef SVECTOR SVec_801A5CE8;
typedef struct { s32 pad00[8]; s32 f20; } SW20;
typedef V8_80184F90_801844C8 SXY_801A8B64;
typedef struct S_D2394 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s16 f18;
    s16 f1A;
    s16 f1C;
    s16 f1E;
    s16 f20;
    s16 f22;
    s16 f24;
    s16 f26;
    s32 f28;
    s16 f2C;
    s16 f2E;
    s16 f30;
    s16 f32;
    s32 f34;
    s32 f38;
} S_D2394;
typedef struct S_D2394B {
    s32 f0;
    s32 f4;
} S_D2394B;
typedef struct {
    s32 pad00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s16 unk34;
    u8 unk36;
    u8 unk37;
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    u8 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    s32 unk90;
    s32 unk94;
} S_md_MAIN_011_800D0BDC;
struct S_md_MAIN_033_800CB3D8 { s32 f[8]; };
typedef struct {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10;
} Spawn801A143C;
typedef struct {
    u8 pad0, pad1, pad2, len;
    u32 tpage;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 u0, v0;
    u16 clut;
    s16 w, h;
} Sprt24;
typedef struct {
    s8 pad00[0x18];
    u16 u18[2];
    s8 pad1C[0xC];
    s32 f28;
    u16 u2C;
    u16 u2E;
    s32 pad30;
    s32 f34;
} St;
typedef struct {
    s32 pad00;
    s32 f04; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18;
    s32 f1C; s32 f20; s32 f24; s32 f28; s32 f2C; s32 f30;
    u16 f34;
    u8 f36; u8 f37;
    u16 f38; u16 f3A; u16 f3C; u16 f3E; u16 f40;
    u8 f42; u8 f43; u8 f44; u8 f45; u8 f46; u8 f47; u8 f48; u8 f49; u8 f4A; u8 f4B; u8 f4C;
    s32 f50; s32 f54; s32 f58; s32 f5C; s32 f60; s32 f64;
    u8 f68;
    s32 f6C; s32 f70; s32 f74; s32 f78; s32 f7C; s32 f80; s32 f84; s32 f88; s32 f8C; s32 f90; s32 f94;
} St78;
typedef struct {
    s8 pad00[0x12];
    s16 f12;
    s8 pad14[6];
    s16 f1A;
    s32 f1C;
    s8 pad20[8];
    u16 f28;
    u16 f2A;
    s8 pad2C[4];
    u32 f30;
} St_md_MAIN_029;
typedef struct { s32 w[4]; } Struct16;
typedef struct { u8 pad[0x50]; s32 f50; } Struct80078E78_md_MAIN_028_800CB0D8;
typedef Vec3s Struct801AD7EC_Local;
typedef UVec_8017DB64 Svec3;
typedef V8_80184F90_801844C8 Svec_801A6184;
typedef V8_80184F90_801844C8 Svec_801A8494;
typedef V8_80184F90_801844C8 Svec_801AEC38;
typedef V8_80184F90_801844C8 Svec_A8CE0;
typedef struct { u8 flag, idx, cnt, tim; Rec_md_MAIN_047_800CCBC0 e[16]; } Trail_md_MAIN_047_800CCBC0;
typedef Trail_md_MAIN_047_800CCBC0 Trail_md_MAIN_047_800CCDE8;
typedef struct {
    u16 a, b;
} U16x2;
typedef struct {
    u16 a, b;
} U16x2L;
typedef struct {
    u16 a, b;
} U16x2N;
typedef struct {
    u16 a, b, c, d;
} U16x4;
typedef BlockData U8x;
struct UnkS1 { s32 pad0; s32 f4; s32 pad8; s32 fC; s32 pad10; s32 pad14; s32 f18; u32 f1C; };
typedef H16 Unkstruct_801AF368;
typedef struct { u32 v; } Unkstruct_801AF368_2;
typedef struct { s16 h; } Unkstruct_8017D2A4;
typedef Unkstruct_8017D2A4 Unkstruct_801E3C1C;
typedef struct { u8 pad[2]; u16 f; } Unkstruct_801E5894;
typedef Unkstruct_8017D2A4 Unkstruct_801E915C;
typedef Unkstruct_8017D2A4 Unkstruct_801EEFBC;
typedef Unkstruct_8017D2A4 Unkstruct_801F0A9C;
typedef struct { s32 vx, vy, vz, vw; } V32_800CB4E4;
typedef Vec32 V32_800CB910;
typedef struct { s32 vx, vy, vz; } VECTOR;
typedef VECTOR V3_800CB634;
typedef V V8_md_MAIN_044;
typedef SVECTOR_8017E6D8 V8_md_SC07_003;
typedef struct { s16 a, b, c, d; } V8x_801A3788;
typedef VECTOR VEC32_801ADC40;
typedef Vec32 VEC_801A1B28;
typedef SVECTOR Vec16_801A4FDC;
typedef SVECTOR Vec16_801A5094;
typedef Vec32 Vec32_801A2400;
typedef Vec32 Vec32_801A3180;
typedef Vec32 Vec32_801A4FDC;
typedef Vec32 Vec32_801A5094;
typedef VECTOR Vec32_801AA004;
typedef Vec32 Vec801A143C;
typedef struct { s32 m[4]; } Vec801A8E34;
typedef struct {
    u16 a;
    u16 b;
    u16 c;
    u16 d;
} Vec8_801A0E28;
typedef struct {
    u16 a;
    u16 b;
    u16 c;
    u16 d;
} Vec8_801A1924;
typedef struct { u16 a, b, c, d; } Vec8_md_SC07_003_801A3334;
typedef struct { s32 w0, w1, w2, w3, w4, w5, w6, w7; } W8__md_MAIN_044;
typedef Blk8_801867AC W8_md_MAIN_025_800CB300;
typedef struct Work_md_MAIN_046 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 pad04[3];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 pad1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 pad24[132];
    /* 0x234 */ s32 unk234;
    /* 0x238 */ s32 unk238;
    /* 0x23C */ s32 unk23C;
} Work_md_MAIN_046;
typedef struct { s32 w[4]; } func_800CB164_Blk16;
typedef struct { s32 w[4]; } func_800CB4D8_Blk16;

/* --- lift_types.py --census (P38 T5.1.c2, batch main) --- */
typedef struct {
    u8 b0;
    u8 pad[25];
} A098Rec;
typedef struct {
    u8 *stream;
    u8 pad04[0x16];
    A098Rec rec[1];
} A098Ctx;
typedef Prim_1412A8 B16x;
typedef struct { u8 b0, b1, b2, b3; } BYTES_800CFAD0;
typedef struct {
    u32 a, b, c;
} Blk12;
typedef struct { u8 b[128]; } Blk128u;
typedef struct {
    /* 0x00 */ u8  pad00[4];
    /* 0x04 */ u8  unk04;
    /* 0x05 */ u8  pad05[11];
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ u8  pad14[2];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u8  pad18[8];
} C24;
typedef C24 Blk28;
typedef struct {
    u32 w[0x2DC / 4];
} Blk2DC;
typedef struct { s32 w[8]; } Blk32_80017E8C;
typedef struct { u8 b[32]; } Blk32u;
typedef struct {
    s32 w[9];
} Blk36_800296F8;
typedef struct { u8 b[41]; } Blk41;
typedef struct Blk48_30D80 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u8 pad04[0x3D];
    /* 0x41 */ u8 unk41;
    /* 0x42 */ u8 pad42[6];
} Blk48_30D80;
typedef struct {
    char c[4];
} Blk4_80029774;
typedef struct {
    u8 pad00[0x36];
    u8 field_0x36;
    u8 field_0x37;
} Blk80078E78;
typedef struct {
    s32 w[9];
} Blob36;
typedef V COL_8001EFE0;
typedef Col4_8017F8BC CVecDA34;
typedef struct { s32 stat; u32 val; } CardSlot;
typedef struct { s32 m[3][3]; s32 t[3]; } MATRIX_L48;
typedef MATRIX_L48 CdReq_800_c;
typedef struct {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8  w;
    /* 0x03 */ u8  h;
    /* 0x04 */ s16 x;
    /* 0x06 */ u16 y;
    /* 0x08 */ u16 u;
    /* 0x0A */ u16 v;
} Cell_EA14;
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8  pad18[0xC];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8  pad28[0xC];
    /* 0x34 */ u8  unk34;
    /* 0x35 */ u8  unk35;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  pad37[9];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8  unk4C;
    /* 0x4D */ u8  unk4D;
    /* 0x4E */ u8  unk4E;
    /* 0x4F */ u8  unk4F;
    /* 0x50 */ u8  pad50[2];
    /* 0x52 */ u8  unk52;
    /* 0x53 */ u8  unk53;
} Chan32A74;
typedef struct {
    /* 0x00 */ u8 pad00[0x0A];
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u8 pad0C[0x28];
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 pad36[0x1C];
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 pad53[1];
} Chan336A8;
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8  pad18[0x0C];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8  pad28[0x0C];
    /* 0x34 */ u8  unk34;
    /* 0x35 */ u8  unk35;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  pad37[9];
    /* 0x40 */ void (*unk40)(u8 *, s32);
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u16 unk48;
    /* 0x4A */ u16 unk4A;
    /* 0x4C */ u8  unk4C;
    /* 0x4D */ u8  unk4D;
    /* 0x4E */ u8  unk4E;
    /* 0x4F */ u8  unk4F;
    /* 0x50 */ u8  pad50[2];
    /* 0x52 */ u8  unk52;
    /* 0x53 */ u8  unk53;
} Chan388C;
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  unk09;
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  unk0B;
    /* 0x0C */ u8  unk0C;
    /* 0x0D */ u8  unk0D;
    /* 0x0E */ u8  pad0E[2];
    /* 0x10 */ s32 unk10;
} Cmd388C;
typedef struct { u32 tag; u32 code0; } DRM;
typedef struct { u16 vx, vy; } DVec_80183DA4;
typedef DVec_80183DA4 DV_EA14;
typedef DVec_80183DA4 DVec_80021D38;
typedef struct {
    /* 0x00 */ u16 type;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 x;
    /* 0x06 */ u16 y;
    /* 0x08 */ u16 w;
    /* 0x0A */ u16 h;
    /* 0x0C */ void *data;
} DispItem_800184F0;
typedef struct {
    /* 0x00 */ s16 flag;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ DispItem_800184F0 *list;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u8 unk0C;
    /* 0x0D */ u8 unk0D;
    /* 0x0E */ u16 unk0E;
} DispSlot_800184F0;
typedef DispSlot_800184F0 DispSlot_800184F0_80014588;
typedef struct { u32 addr : 24; u32 len : 8; u32 code0; } DrMode_80021284;
typedef struct { u32 addr : 24; u32 len : 8; u32 code; } DrTpage;
typedef struct {
    u8  pad0[8];
    s32 w8;
    u8  pad_C[10];
    u8  b16;
    u8  pad17[2];
    u8  b19;
} Dst;
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u16 unk10;
} Dst17DC4;
typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u32 attr;
    /* 0x08 */ u8  pad08[0x18];
    /* 0x20 */ u8 *rec;
    /* 0x24 */ u8  pad24[8];
    /* 0x2C */ u16 pri;
} Ent_80021284;
typedef struct { u8 pad[4]; PTag *ot; } Env;
typedef Env_80140958 Env_800D2650;
typedef Env_80140958 Env_800D27DC;
typedef struct F1ccRec {
    u8 pad[0x0E];
    u8 flg[8];
    u8 unk16[0x24];
    u8 flg3A[8];     /* S54's flg */
    u8 tail[0x12];
} F1ccRec;
typedef F1ccRec F150Rec;
typedef struct F1ccSlot {
    u8 pad[0x20];
    u32 u20;
    u32 u24;
    u32 u28;
    u32 u2C;
    u16 u30;
    u8 mid[5];
    u8 u37;
    u8 u38;
    u8 tail[0x1B];
} F1ccSlot;
typedef F1ccSlot F150Slot;
typedef struct {
    u32 tag;    /* 0x00 */
    u32 rgbc0;  /* 0x04 */
    u32 xy0;    /* 0x08 */
    u32 xy1;    /* 0x0C */
    u32 xy2;    /* 0x10 */
} F3_80017168;
typedef struct {
    u32 tag;
    u32 rgbc;
    u32 xy0;
    u32 xy1;
    u32 xy2;
    u32 xy3;
} F4_80017294;
typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgbc;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u8  u0;
    /* 0x0D */ u8  v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ u32 xy1;
    /* 0x14 */ u8  u1;
    /* 0x15 */ u8  v1;
    /* 0x16 */ u16 tpage;
    /* 0x18 */ u32 xy2;
    /* 0x1C */ u8  u2;
    /* 0x1D */ u8  v2;
    /* 0x1E */ u16 pad_1E;
} FT3_16D78;
typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 rgbc;
    /* 0x08 */ u32 xy0;
    /* 0x0C */ u8  u0;
    /* 0x0D */ u8  v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ u32 xy1;
    /* 0x14 */ u8  u1;
    /* 0x15 */ u8  v1;
    /* 0x16 */ u16 tpage;
    /* 0x18 */ u32 xy2;
    /* 0x1C */ u8  u2;
    /* 0x1D */ u8  v2;
    /* 0x1E */ u16 pad_1E;
    /* 0x20 */ u32 xy3;
    /* 0x24 */ u8  u3;
    /* 0x25 */ u8  v3;
    /* 0x26 */ u16 pad_26;
} FT4_16F18;
typedef struct {
    s32 unk00;                  /* 0x00 */
    u32 rgb;                    /* 0x04 */
    u16 n0;                     /* 0x08 */
    u16 v0;                     /* 0x0A */
    u16 v1;                     /* 0x0C */
    u16 v2;                     /* 0x0E */
    u16 v3;                     /* 0x10 */
    u16 pad;                    /* 0x12 */
} Face;
typedef struct {                                        /* 0x1C */
    u32 unk00;
    u32 uv0;
    u32 uv1;
    u32 uv2;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
} FaceGT3;
typedef struct {
    s32 (*f[3])(u8 *);
} FnTbl;
typedef struct {
    void (*fn[3])(void *);
} FnTbl3;
typedef Ft4_800CBA18 Ft4;
typedef struct {                                     /* 0x1C */
    u32 tag;
    u32 rgb0;
    s16 x0, y0;
    u32 rgb1;
    s16 x1, y1;
    u32 rgb2;
    s16 x2, y2;
} G3P;
typedef struct {
    u32 tag;    /* 0x00 */
    u32 rgbc0;  /* 0x04 */
    u32 xy0;    /* 0x08 */
    u32 rgbc1;  /* 0x0C */
    u32 xy1;    /* 0x10 */
    u32 rgbc2;  /* 0x14 */
    u32 xy2;    /* 0x18 */
} G3_800173DC;
typedef struct {                                     /* 0x24 */
    u32 tag;     /* 0x00 */
    u32 rgb0;    /* 0x04 */
    s16 x0, y0;  /* 0x08 */
    u32 rgb1;    /* 0x0C */
    s16 x1, y1;  /* 0x10 */
    u32 rgb2;    /* 0x14 */
    s16 x2, y2;  /* 0x18 */
    u32 rgb3;    /* 0x1C */
    s16 x3, y3;  /* 0x20 */
} G4P;
typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    s16 x0, y0;
    u8 r1, g1, b1, pad_F;
    s16 x1, y1;
    u8 r2, g2, b2, pad_17;
    s16 x2, y2;
    u8 r3, g3, b3, pad_1F;
    s16 x3, y3;
} POLY_G4;              /* libgpu POLY_G4; SDK pad1..pad3 spelled by offset (pad-name invariant) */
typedef POLY_G4 PG4_8017FD50;
typedef PG4_8017FD50 G4_80017778;
typedef struct {
    u8 addr0, addr1, addr2, len;
    u32 code0;
} GDrMode;
typedef struct {
    s32 unk0;
    u32 rgb;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
    u16 n3, v3;
} GFace;
typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    u32 xy0;
    u32 rgb1;
    u32 xy1;
    u32 rgb2;
    u32 xy2;
    u32 rgb3;
    u32 xy3;
} GPolyG4;
typedef struct {
    u32 tag;    /* 0x00 */
    u32 rgb0;   /* 0x04 */
    s16 x0, y0; /* 0x08 */
    u8 u0, v0;  /* 0x0C */
    u16 clut;   /* 0x0E */
    u32 rgb1;   /* 0x10 */
    s16 x1, y1; /* 0x14 */
    u8 u1, v1;  /* 0x18 */
    u16 tpage;  /* 0x1A */
    u32 rgb2;   /* 0x1C */
    s16 x2, y2; /* 0x20 */
    u8 u2, v2;  /* 0x24 */
    u16 pad_26;   /* 0x26 */
    u32 rgb3;   /* 0x28 */
    s16 x3, y3; /* 0x2C */
    u8 u3, v3;  /* 0x30 */
    u16 pad_32;   /* 0x32 */
} GT4_80017930;
typedef struct {
    /* 0x0 */ u32 xy;
    /* 0x4 */ s16 z;
    /* 0x6 */ s16 pad;
} V16F18;
typedef V16F18 GTEOutV;
typedef SVECTOR GTESVec;
typedef SVECTOR GVec8;
typedef struct {                                      /* 0x10 LINE_F2 */
    u8  addr[3];
    u8  len;
    u8  r0, g0, b0, code;
    s16 x0, y0;
    s16 x1, y1;
} LineF2_80015F04;
typedef struct {
    u32 tag;   /* 0x00 */
    u32 rgb0;  /* 0x04 */
    u32 xy0;   /* 0x08 */
    u32 rgb1;  /* 0x0C */
    u32 xy1;   /* 0x10 */
} LineG2_80016A7C;
typedef struct {
    u32 tag;    /* 0x00 */
    u32 rgb0;   /* 0x04 */
    u32 xy0;    /* 0x08 */
    u32 rgb1;   /* 0x0C */
    u32 xy1;    /* 0x10 */
    u32 rgb2;   /* 0x14 */
    u32 xy2;    /* 0x18 */
    u32 otz;    /* 0x1C */
} LineG3_80016B60;
typedef struct {
    u32 tag;    /* +0x00 */
    u32 rgb0;   /* +0x04 */
    u32 xy0;    /* +0x08 */
    u32 rgb1;   /* +0x0C */
    u32 xy1;    /* +0x10 */
    u32 rgb2;   /* +0x14 */
    u32 xy2;    /* +0x18 */
    u32 rgb3;   /* +0x1C */
    u32 xy3;    /* +0x20 */
    u32 term;   /* +0x24 */
} LineG4;
typedef LineG4 LineG4_80016C28;
typedef MATRIX MATRIX_8001EFE0;
typedef struct {                                                 /* 0x50 */
    u32 flg;
    MATRIX_8001EFE0 coord;
    MATRIX_8001EFE0 workm;
    void *rotate;
    void *super;
    void *sub;
} COORD2_8001EFE0;
typedef MATRIX MTX_139C8;
typedef MATRIX MTX_8001FC08;
typedef struct { MTX_8001FC08 a; MTX_8001FC08 b; } MTX2_8001FC08;
typedef struct {
/* 0x00 */ s32 attr;
/* 0x04 */ s32 u04;
/* 0x08 */ s32 u08;
/* 0x0C */ s32 u0C;
/* 0x10 */ s32 u10;
/* 0x14 */ s32 u14;
/* 0x18 */ MTX_8001FC08 m0;
/* 0x38 */ MTX_8001FC08 m1;
/* 0x58 */ s32 f;
/* 0x5C */ MTX2_8001FC08 mm;
/* 0x9C */ s32 u9C;
/* 0xA0 */ s32 uA0;
/* 0xA4 */ s32 uA4;
/* 0xA8 */ s16 *lp;
/* 0xAC */ s32 cnt;
} LOC_8001FC08;
typedef MATRIX MTX_80020248;
typedef MATRIX MT_EA14;
typedef MATRIX MX221A8;
typedef struct {
    /* 0x00 */ s32 flg;
    /* 0x04 */ MX221A8 coord;
    /* 0x24 */ MX221A8 workm;
    /* 0x44 */ void *rotate;
    /* 0x48 */ void *super;
    /* 0x4C */ void *sub;
} CD221A8;
struct MainSlot { s32 unk0; s32 unk4; s32 unk8; };
typedef MATRIX MtxDA34;
typedef MATRIX Mtx_80021D38;
typedef struct {
    /* 0x0 */ u8  b0;
    /* 0x1 */ u8  b1;
    /* 0x2 */ u8  b2;
    /* 0x3 */ s8  t[3];
    /* 0x6 */ u16 h;
} OBJ598;
typedef struct {
/* 0x00 */ u16 h00;
/* 0x02 */ u16 mode;
/* 0x04 */ u32 attr;
/* 0x08 */ s16 x;
/* 0x0A */ s16 y;
/* 0x0C */ s16 z;
/* 0x0E */ u16 h0E;
/* 0x10 */ s16 rot[3];
/* 0x16 */ u16 h16;
/* 0x18 */ s16 scale[3];
/* 0x1E */ u16 h1E;
/* 0x20 */ u32 objs;
/* 0x24 */ s32 *list;
/* 0x28 */ s32 w28;
/* 0x2C */ u16 flags;
/* 0x2E */ u16 idx;
/* 0x30 */ s32 w30;
/* 0x34 */ MTX2_8001FC08 mm;
/* 0x74 */ s32 w74;
/* 0x78 */ s32 w78;
/* 0x7C */ s32 w7C;
/* 0x80 */ s32 w80;
} OBJ_8001FC08;
typedef struct {
    /* 0x0 */ u32 xy;
    /* 0x4 */ s16 z;
    /* 0x6 */ s16 rot[3];
} OBJ_80020248;
typedef struct {
    /* 0x0 */ u32 xy;
    /* 0x4 */ u16 unk4;
    /* 0x6 */ u16 unk6;
} OBJ_80020A28;
typedef struct {
    u8  pad00[0x15];
    u8  field_0x15;   /* 0x15 */
    u8  pad16[0x12];
    s32 field_0x28;   /* 0x28 */
} Obj800D302C;
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u8  pad08[6];
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ u8  pad10[14];
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ u8  *unk20;
    /* 0x24 */ u8  pad24[8];
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ s32 unk34;
} Obj_215F4;
typedef struct 
{
  u16 unk0;
  u16 x;
  u16 y;
  u16 unk6;
  s32 value;
  u8 flags;
} Obj_80015760;
typedef struct Obj_800_b_2 {
    /* 0x00 */ u8 unk00[0xA];
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u8 unk12[0x12];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u8 unk32[0x5];
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 unk3E[0x13];
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 unk52[2];
} Obj_800_b_2;
typedef OtBlk_80180894 OtBlk_80016450;
typedef OtBlk_80180894 OtBlk_80016450_80015F04;
typedef struct {
    u32 tag;
    u8  r0, g0, b0, code;
    s16 x0, y0;
    u8  r1, g1, b1, pad_F;
    s16 x1, y1;
    u8  r2, g2, b2, pad_17;
    s16 x2, y2;
} POLY_G3;              /* libgpu POLY_G3; SDK pad1/pad2 spelled by offset (pad-name invariant) */
typedef POLY_G3 PG3;
typedef struct {
    u32 tag;                    /* 0x00 */
    u8  r0, g0, b0, code;       /* 0x04 */
    s16 x0, y0;                 /* 0x08 */
    s16 x1, y1;                 /* 0x0C */
    s16 x2, y2;                 /* 0x10 */
    s16 x3, y3;                 /* 0x14 */
} POLY_F4;
typedef PrimTag PTag_8001BC6C;
typedef PrimTag PTag_8001D3FC;
typedef PrimTag PTag_80021284;
typedef PrimTag PTag_80023570;
typedef PrimTag PTag_80023BF0;
typedef PrimTag PTag_800D2650;
typedef PrimTag PTag_800D27DC;
typedef PrimTag PTag_800D29F8;
typedef PrimTag P_TAG_800CFAD0;
typedef struct {                                        /* 0x28 */
    u32 tag;
    u32 rgb0, xy0, uv0;
    u32 rgb1, xy1, uv1;
    u32 rgb2, xy2, uv2;
} PktGT3;
typedef struct { u16 x, y; } Pt_80015F04;
typedef Pt_80015F04 Poly12Pt;
typedef struct {
    u8 pad_00[0x10];
    Poly12Pt pts[12];
} Poly12Obj;
typedef struct {
    /* 0x00 */ u32 addr : 24;
    /* 0x03 */ u32 len : 8;
    /* 0x04 */ u8 r0, g0, b0, code;
    /* 0x08 */ s16 x0, y0;
    /* 0x0C */ u8 r1, g1, b1, pad1;
    /* 0x10 */ s16 x1, y1;
    /* 0x14 */ u8 r2, g2, b2, pad2;
    /* 0x18 */ s16 x2, y2;
    /* 0x1C */ u8 r3, g3, b3, pad3;
    /* 0x20 */ s16 x3, y3;
} PolyG4_80021284;
typedef struct {
    u32 c0;             /* 0x04 r0,g0,b0,code */
    s16 x0, y0;         /* 0x08 */
    u32 c1;             /* 0x0C */
    s16 x1, y1;         /* 0x10 */
    u32 c2;             /* 0x14 */
    s16 x2, y2;         /* 0x18 */
    u32 c3;             /* 0x1C */
    s16 x3, y3;         /* 0x20 */
} PolyG4_800D29F8;
typedef struct {
    u16 x;      /* +0x0 */
    u16 y;      /* +0x2 */
    u16 z;      /* +0x4 */
} Pos_8017DC24;
typedef Pos_8017DC24 Pos800D20C0;
typedef struct {
    u32 unk0;
    u32 rgbc;
    u16 n0, v0, n1, v1, n2, v2;
} Prim_800;
typedef struct { u8 r, g, b, code; } C_8017DCC0;
typedef C_8017DCC0 RGBC;
typedef struct {            /* 0x24 — POLY_G4 */
    u32  tag;
    RGBC c0;
    u32  xy0;
    RGBC c1;
    u32  xy1;
    RGBC c2;
    u32  xy2;
    RGBC c3;
    u32  xy3;
} PG4;
typedef struct {
    /* 0x00 */ u16 cur;
    /* 0x02 */ u16 step;
    /* 0x04 */ u16 tgt;
    /* 0x06 */ u8  act;
    /* 0x07 */ u8  pad07;
} Ramp388C;
typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ u8  pad02[6];
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u8  pad0A[2];
    /* 0x0C */ u32 *unk0C;
    /* 0x10 */ u8  *unk10;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8  unk16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ Ramp388C unk1C[3];
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  pad37[1];
    /* 0x38 */ u8  unk38;
    /* 0x39 */ u8  unk39;
    /* 0x3A */ u8  unk3A[8];
    /* 0x42 */ u8  pad42[2];
    /* 0x44 */ u32 *unk44;
    /* 0x48 */ u8  unk48;
    /* 0x49 */ u8  pad49[1];
    /* 0x4A */ u16 unk4A;
    /* 0x4C */ u8  unk4C;
    /* 0x4D */ u8  unk4D;
    /* 0x4E */ u8  unk4E;
    /* 0x4F */ u8  unk4F;
    /* 0x50 */ u16 unk50;
    /* 0x52 */ s16 unk52;
} Ent388C;
typedef struct Rec12_800_b_2 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  pad09[3];
} Rec12_800_b_2;
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u8  unk06;
    /* 0x07 */ u8  unk07;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  unk09;
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  unk0B;
    /* 0x0C */ u8  pad0C[4];
    /* 0x10 */ s32 unk10;
} Rec32A74;
typedef struct {
    u16 id;   /* 0x00 */
    u8  w;    /* 0x02 */
    u8  h;    /* 0x03 */
    s16 dx;   /* 0x04 */
    u16 dy;   /* 0x06 */
    u16 px;   /* 0x08 */
    u16 py;   /* 0x0A */
} RecDA34;
typedef struct {
        s16 flag;
        s16 pad02;
        s32 id;
        u16 x;
        u16 y;
        u8 c;
        u8 d;
        u16 pad0E;
    } Rec_800;
typedef struct {
        u8 pad[0xA1A8];
        Rec_800 rec[0x20];
    } Base;
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u8  pad04[6];
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  pad0B[1];
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u8  unk0E[8];
} Req32A74;
typedef struct {
    /* 0x00 */ u8 pad00[0x16];
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 pad17[1];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ u16 unk1C[12];
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 pad39[1];
    /* 0x3A */ u8 unk3A[8];
} Req336A8;
typedef struct {
    s16 v;
    s16 pad[2];
} ResMapCol;
typedef F1ccRec S54;
typedef struct {
    u8 pad[0x14];
    u8 f14;   /* 0x14 */
    u8 f15;   /* 0x15 */
} S800D1938;
typedef struct {
    u8 pad[0x27];
    u8 f27;   /* 0x27 */
} S800D21C4;
typedef struct {
    /* 0x00 */ s32 f0;
    /* 0x04 */ s32 f4;
    /* 0x08 */ s32 f8;
    /* 0x0C */ s32 fC;
    /* 0x10 */ s32 f10;
    /* 0x14 */ s32 f14;
    /* 0x18 */ s32 f18;
} S800D22E4;
typedef struct {            /* 0x20 — source quad description */
    u32  unk0;
    RGBC c0;
    RGBC c1;
    RGBC c2;
    RGBC c3;
    u16  n;
    u16  v0;
    u16  v1;
    u16  v2;
    u16  v3;
    u16  unk1E;
} SRCQ;
typedef SVECTOR SV221A8;
typedef SVECTOR SVEC8_80025818;
typedef SVECTOR SVEC8_80025EB8;
typedef SVECTOR SVEC8_80026128;
typedef SVECTOR SVEC8_800262D8;
typedef SVECTOR SVECTOR800277DC;
typedef SVECTOR SVECTOR_80013294;
typedef SVECTOR SVECTOR_80016B60;
typedef SVECTOR SVECTOR_80024BC0;
typedef SVECTOR SVEC_8001EFE0;
typedef SVECTOR SVEC_80023BF0;
typedef SVECTOR SVEC_80025000;
typedef SVECTOR SVEC_800275BC;
typedef SVECTOR SV_215F4;
typedef V16F18 SV_80016A7C;
typedef SVECTOR SV_80016C28;
typedef SVECTOR SV_80017778;
typedef SVECTOR SV_80017930;
typedef SVECTOR SV_80021174;
typedef SVECTOR_8017E6D8 SV_80021284;
typedef SVECTOR_8017E6D8 SV_EA14;
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ SV_EA14 unk08;
    /* 0x10 */ u8 unk10[8];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u8 unk1C[4];
    /* 0x20 */ u8 *unk20;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u16 unk28;
    /* 0x2A */ u16 unk2A;
    /* 0x2C */ u16 unk2C;
} Ent_EA14;
typedef V16F18 SVec3_800173DC;
typedef SVECTOR SVecDA34;
typedef V16F18 SVec_80017168;
typedef SVECTOR SVec_80021D38;
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u32 flags;
    /* 0x08 */ SVec_80021D38 pos;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u16 sx;
    /* 0x1A */ u16 sy;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8 *pts;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u16 depth;
    /* 0x2E */ u16 unk2E;
} Obj_80021D38;
typedef struct {
    u16 state;      /* 0x00 */
    u16 unk02;
    u16 id;         /* 0x04 */
    u16 group;      /* 0x06 */
    u16 unk08;
    s8  unk0A;
    u8  unk0B;
    u8  pad0C[0xA];
    u8  active;     /* 0x16 */
    u8  pad17[0x3D];
} Sl;
typedef struct Slot54View {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ s8  unk0A;
    /* 0x0B */ u8  unk0B;
    /* 0x0C */ u8  pad0C[0x48];
} Slot54View;
typedef struct Snd54Sub {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ u8  unk06;
    /* 0x07 */ u8  pad07;
} Snd54Sub;
typedef struct Snd54 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u8  pad0A[2];
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8  unk16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ Snd54Sub unk1C[3];
    /* 0x34 */ s16 unk34;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  unk37;
    /* 0x38 */ u8  unk38;
    /* 0x39 */ u8  unk39;
    /* 0x3A */ u8  unk3A[8];
    /* 0x42 */ u8  pad42[6];
    /* 0x48 */ u8  unk48;
    /* 0x49 */ u8  pad49[7];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
} Snd54;
typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u8  r0, g0, b0, code;
    /* 0x08 */ s16 x0, y0;
    /* 0x0C */ u8  u0, v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ u16 w, h;
} Sprt_80017B98;
typedef struct {
    u8  pad0[2];
    u8  b2;
    u8  b3;
} Src;
typedef struct {
    u8  pad0;
    u8  pad1;
    u8  pad2;
    u8  code;   /* +0x03 */
    u32 rgb1;   /* +0x04 */
    u32 rgb2;   /* +0x08 */
    u32 rgb3;   /* +0x0C */
    u32 term;   /* +0x10 */
    u32 rgb0;   /* +0x14 */
    u16 i0;     /* +0x18 */
    u16 i1;     /* +0x1A */
    u16 i2;     /* +0x1C */
    u16 i3;     /* +0x1E */
} SrcQ;
typedef struct {
    SV_80016A7C v[2];  /* 0x00 */
    u32 rgb0;          /* 0x10 */
    u32 rgb1;          /* 0x14 */
    u32 attr;          /* 0x18 */
} Src_80016A7C;
typedef struct {
    SVECTOR_80016B60 v[3];  /* 0x00 */
    u32 rgb0;               /* 0x18 */
    u32 rgb1;               /* 0x1C */
    u32 rgb2;               /* 0x20 */
    u32 flags;              /* 0x24 */
} Src_80016B60;
typedef struct {
    SV_80016C28 v[4]; /* 0x00 */
    u32 rgb0;          /* 0x20 */
    u32 rgb1;          /* 0x24 */
    u32 rgb2;          /* 0x28 */
    u32 rgb3;          /* 0x2C */
    u32 flags;         /* 0x30 */
} Src_80016C28;
typedef struct {
    SVec_80017168 v[3];  /* 0x00 */
    u32 rgbc;            /* 0x18 */
    u32 attr;            /* 0x1C */
} Src_80017168;
typedef struct {
    SVec3_800173DC v0;      /* 0x00 */
    SVec3_800173DC v1;      /* 0x08 */
    SVec3_800173DC v2;      /* 0x10 */
    u32 rgbc0;               /* 0x18 */
    u32 rgbc1;               /* 0x1C */
    u32 rgbc2;               /* 0x20 */
    u32 attr;                /* 0x24 */
} Src_800173DC;
typedef struct {
    SV_80017778 v[4]; /* 0x00 */
    u32 rgb[4];        /* 0x20 */
    u32 flags;          /* 0x30 */
} Src_80017778;
typedef struct {
    SV_80017930 v[4]; /* 0x00 */
    u32 uv[4];        /* 0x20 */
    u32 rgb[4];       /* 0x30 */
    u32 flags;        /* 0x40 */
    u8 clut;          /* 0x44 */
} Src_80017930;
typedef struct {
    /* 0x00 */ u16 x;
    /* 0x02 */ u16 y;
    /* 0x04 */ s32 otz;
    /* 0x08 */ u16 w;
    /* 0x0A */ u16 h;
    /* 0x0C */ u16 u;
    /* 0x0E */ u16 v;
    /* 0x10 */ u8  r;
    /* 0x11 */ u8  g;
    /* 0x12 */ u8  b;
    /* 0x13 */ u8  pad13;
    /* 0x14 */ u32 flags;
    /* 0x18 */ u8  tp;
    /* 0x19 */ u8  pad19[3];
} Src_80017B98;
typedef struct {
    u8 pad00[0x34];
    s16 field_0x34;    /* 0x34 */
} Struct80078E78;
typedef struct {
    u8 pad_0[0x15];
    u8 field_0x15;  /* 0x15 */
    u8 pad16[0x3];
    u8 field_0x19;  /* 0x19 */
} Struct800D2E20;
typedef struct {
    u8 pad00[0x15];    /* 0x00..0x14 */
    u8 field_0x15;     /* 0x15 */
    u8 pad16[0x3];     /* 0x16..0x18 */
    u8 field_0x19;     /* 0x19 */
} Struct800D2E6C;
typedef struct {
    u8 pad00[0x15];
    u8 field_0x15;   /* 0x15 */
    u8 pad16[0x12];
    s32 field_0x28;  /* 0x28 */
} Struct800D2FEC;
typedef struct {
    u8 pad_0[0x15];
    u8 field_0x15;
    u8 pad16[0x3];
    u8 field_0x19;
} Struct800D3104;
typedef Struct800D2E6C Struct800D3120;
typedef struct {
    s16 unk00;
    u8  pad02[4];
    u16 unk06;
} StructA4E88;
typedef struct {
    u16 value;
    u8 pad[14];
} Entry_D_801949C8;
typedef Entry_D_801949C8 T16;
typedef struct {
    u32 hdr;
    u32 rgb0;
    u32 rgb1;
    u32 rgb2;
    u16 n0, v0;
    u16 n1, v1;
    u16 n2, v2;
} TPRIM_80025818;
typedef struct {               /* TMD G4 flat-normal primitive, 0x20 bytes */
    u32 tag;                   /* 0x00 */
    u32 c0;                    /* 0x04 */
    u32 c1;                    /* 0x08 */
    u32 c2;                    /* 0x0C */
    u32 c3;                    /* 0x10 */
    u16 n0;                    /* 0x14 */
    u16 v0;                    /* 0x16 */
    u16 v1;                    /* 0x18 */
    u16 v2;                    /* 0x1A */
    u16 v3;                    /* 0x1C */
    u16 pad;                   /* 0x1E */
} TPRIM_800275BC;
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 x;
    /* 0x06 */ u16 y;
    /* 0x08 */ u16 w;
    /* 0x0A */ u16 h;
    /* 0x0C */ void *data;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
} TexInfo_800184F0;
typedef struct {
    u8  pad[0x5C];
    s32 t5C;  /* 0x5C */
    s32 t60;  /* 0x60 */
    s32 t64;  /* 0x64 */
} Tgt800D20C0;
typedef struct {
    u32 pad0;
    u32 rgb0;
    u32 rgb1;
    u32 rgb2;
    u16 n0;
    u16 v0;
    u16 v1;
    u16 v2;
} TmdG3;
typedef union {
    u32 w;
    u16 h[2];
} UV16D78;
typedef UV16D78 UV16F18;
typedef struct {
    u8 pad00[0x16];
    u8 unk16;
} Unk;
typedef Unkstruct_8017D2A4 Unkstruct_800A46D2;
typedef V16F18 V0_80017294;
typedef struct {
    V0_80017294 v[4];  /* 0x00 */
    u32 rgbc;           /* 0x20 */
    u32 flags;           /* 0x24 */
} Src_80017294;
typedef V16F18 V16D78;
typedef struct {
    /* 0x00 */ V16D78  v[3];
    /* 0x18 */ UV16D78 uv[3];
    /* 0x24 */ u32     rgbc;
    /* 0x28 */ u32     attr;
    /* 0x2C */ u8      clut;
} S16D78;
typedef struct {
    /* 0x00 */ V16F18   v[4];
    /* 0x20 */ UV16F18  uv[4];
    /* 0x30 */ u32      rgbc;
    /* 0x34 */ u32      attr;
    /* 0x38 */ u8       clut;
} S16F18;
typedef Vec32 VC221A8;
typedef Vec32 VC_EA14;
typedef Vec32 VEC_8001EFE0;
typedef Vec32 VEC_80021284;
typedef struct { u32 w; } VMask;
typedef struct {
    s32 x, y, z, w;
} Vec4_800128EC;
typedef SVECTOR Vec8_800;
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u8  pad10[4];
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8  pad16[2];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8  pad1A[2];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8  pad20[0x1A];
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ u16 unk3C;
    /* 0x3E */ u8  pad3E[2];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  unk45;
    /* 0x46 */ u8  pad46[2];
} Voice32A74;
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ u8 pad0C[0x34];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45[3];
} Voice336A8;
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ u8  pad10[4];
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8  pad16[2];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8  pad1A[2];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8  pad20[0x1A];
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8  pad3E[2];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  unk45;
    /* 0x46 */ u8  pad46[2];
} Voice388C;
typedef struct VoiceF80 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ u8  pad0C[0x34];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  pad45[3];
} VoiceF80;
typedef SVECTOR Vtx8;
typedef struct { u8 v; } W8_;
typedef SpadRect_800184F0 XRECT;
typedef struct CdReq {
/* 0x00 */ s32   state;
/* 0x04 */ s32   unk04;
/* 0x08 */ s32   phase;
/* 0x0C */ s32   unk0C;
/* 0x10 */ s32   unk10;
/* 0x14 */ s32   texIdx;
/* 0x18 */ s32   unk18;
/* 0x1C */ s32   unk1C;
/* 0x20 */ XRECT rect;
/* 0x28 */ XRECT *rectp;
/* 0x2C */ s32   count;
/* 0x30 */ s32   busy;
/* 0x34 */ s32   list;
/* 0x38 */ s32   sink;
/* 0x3C */ s32   dest;
/* 0x40 */ s32   unk40[6];
/* 0x58 */ s32   words;
/* 0x5C */ s32   drain;
/* 0x60 */ s32   unk60[2];
/* 0x68 */ u8    mask[0x40];
/* 0xA8 */ u8    flags;
/* 0xA9 */ u8    unkA9;
/* 0xAA */ u8    bit;
/* 0xAB */ u8    byteIdx;
/* 0xAC */ s32   unkAC[3];
/* 0xB8 */ s32   size;
/* 0xBC */ s32   posInt;
} CdReq;
typedef Pt_80015F04 XY221A8;
typedef struct {
    /* 0x00 */ u8 pad00[0x10];
    /* 0x10 */ XY221A8 pt[1];
} Src221A8;
typedef struct {
    /* 0x00 */ u8 pad00[8];
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ u8 pad0E[2];
    /* 0x10 */ s16 unk10[4];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u8 pad1C[4];
    /* 0x20 */ Src221A8 *unk20;
    /* 0x24 */ u8 pad24[4];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u16 unk2E;
    /* 0x30 */ u8 pad30[4];
    /* 0x34 */ MX221A8 unk34;
    /* 0x54 */ MX221A8 unk54;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ void *unk78;
} Obj221A8;
typedef DVec_80183DA4 XY_8001EFE0;
struct func_8002EE64_b { u8 c; };
typedef struct {
    /* 0x000 */ u8 *ptr;
    /* 0x004 */ u8 pad_004[0x1D0 - 0x004];
    /* 0x1D0 */ s32 unk1D0;
    /* 0x1D4 */ u8 pad_1D4[0x1E4 - 0x1D4];
    /* 0x1E4 */ s16 unk1E4;
    /* 0x1E6 */ s16 unk1E6;
    /* 0x1E8 */ u8 pad_1E8[0x1F9 - 0x1E8];
    /* 0x1F9 */ u8 unk1F9;
} func_8003A234_Ctx;

/* --- lift_types.py --census (P38 T5.1.c2, batch headers) --- */
typedef struct {
    /* 0x00 */ u8 *unk00;
    /* 0x04 */ u8  pad04[2];
    /* 0x06 */ u8  unk06;
    /* 0x07 */ u8  unk07;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  pad09[3];
} A12;
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  unk0B;
} B12;
typedef struct {                 /* table entry (ent), D_80078E50-shaped */
    u8   _0[3]; u8 f3; u8 _4[4]; s32 f8; s32 fC;
    u16  f10, f12, f14, f16;
    void (*f18)(void); u8 _1C[4]; void (*f20)(void);
} ENT;
typedef struct {              /* base 0x80064D49, stride 0x0C */
    u8  unk00;
    u8  pad[11];
} Elm12;
typedef struct {               /* 0x18 stride; D_800A463C + k*0x18 */
    s32 unk00;
    u8  unk04[0x14];
} Ent24;
typedef struct Ent30D80 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u8 pad04[6];
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u8 pad0C[0x34];
    /* 0x40 */ void (*unk40)(s32, s32);
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u8 pad48[6];
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 pad4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
} Ent30D80;
typedef struct { u8 pad0[0x12]; u16 unk12; } Obj20_80178D40;
typedef Obj20_80178D40 F20T;
typedef H16 H2;
typedef struct {                 /* func_801457A4 buffer (hdr) */
    s16 f0, f2, f4, f6, f8, fA;
    u8  fC, fD, fE, _F;
    s16 f10, f12, f14; u8 f16, f17, f18, _19;
    s16 f1A, f1C, f1E; u8 f20, f21, f22, _23;
    u16 f24, f26; u32 f28, f2C, f30, f34;
    u16 f38, f3A, f3C, f3E;
    u8  f40[12];
    u32 f4C, f50, f54, f58, f5C, f60, f64;
    u8  _68[0x20];
    u32 f88, f8C, f90, f94, f98, f9C, fA0, fA4, fA8;
    u8  _AC[8];
    u32 fB4, fB8, fBC, fC0, fC4, fC8;
    u8  _CC[8];
    u32 fD4, fD8;
} HDR;
typedef struct {                 /* D_80126B58 */
    u8   _0[6]; u16 f6;
    u8   _8[2]; u16 fA;
    u8   _C[2]; u16 fE;
    u8   _10[0x10];
    F20T *f20;                   /* 0x20 pointer field */
    u8   _24[0x29]; u8 f4D;
    u8   _4E[0x3A];
    u16  f88, f8A, f8C; u8 _8E[2]; u16 f90, f92, f94;
    u8   _96[0x1A]; s32 fB0;
    u8   _B4[0x18]; s32 fCC;
    u8   _D0[0x84];
    u16  f154, f156, f158; u8 _15A[2]; u16 f15C, f15E, f160;
    u8   _162[0x36]; s32 f198, f19C;
    u8   _1A0[0x48]; s32 f1E8;
    u8   _1EC[4]; s32 f1F0;
} P10;
typedef struct { u8 _0[0x3A]; u16 f3A; u8 _3C[2]; u16 f3E; } P14;
typedef struct {                 /* D_800AE6A8 */
    u8   _0[4]; s32 f4; s32 f8; s32 fC;
    u8   _10[4]; u8 f14; u8 _15; u8 f16; u8 _17; u8 f18;
    u8   _19[3]; s32 f1C;
    u16  f20, f22, f24, f26;
} P18;
typedef struct { u8 _0[0xA0]; u8 fA0; } P1C;
typedef struct Rec14 {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u32 unk10;
} Rec14;
typedef struct Owner4EE8 {
    /* 0x00 */ u8 pad00[0x14];
    /* 0x14 */ Rec14 **unk14;
} Owner4EE8;
typedef struct {
    u8  unk00;
    u8  unk01[11];
} Rsc12;
typedef struct {
    s32 unk00;
    u8  unk04;
    u8  unk05;
    u8  unk06;
    u8  unk07;
    u8  unk08;
    u8  unk09;
    u8  unk0A;
    u8  unk0B;
    s32 unk0C;
} Rsc16;
typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    s16 unk0C;
    s16 unk0E;
    u8  unk10;
    u8  unk11;
    u8  unk12;
    u8  unk13;
    s32 unk14;
} Rsc24;
typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    u8  unk0C;
    u8  unk0D;
    u8  unk0E;
    u8  unk0F;
} Slot16;
typedef struct {              /* base 0x80076240, stride 0x10 */
    u16 unk00;
    u16 unk02;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
} Slot16A;
typedef struct Slot54 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ s8  unk0A;
} Slot54;
typedef struct Slot_800_shared {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u8 unk08[0xC];
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 unk16[2];
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8 unk1A[0x26];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45[3];
} Slot_800_shared;
typedef Unkstruct_8017D2A4 W16;
typedef E4 W32;
typedef struct { u8  v; } W8;

/* --- T2 (P3.40) canonical definitions: one per `define` target of config/type_folds.tsv, flat max-site layout from
   .run/P37/census/struct_map.json, renamed to the target. Generator: tools/head_types.py --type <map type>
   --map .run/P37/census/struct_map.json --header .run/P40/t2/per/<map type>.h
   --decisions .run/P40/t2/per/<map type>.md, one run per type (hand-copied; outside the head_types markers). Order: by name. --- */
typedef struct {
    /* Unkstruct_8011F7A8: P37 struct map 1742 sites in 270 bodies; evidence {'L': 18, 'AT': 1}; type_folds.tsv evidence E2-anchor; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x7];
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ u8 unk8;
    /* 0x0009 */ u8 pad9[0x3];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x6a];
    /* 0x0082 */ u16 unk82;
    /* 0x0084 */ u8 pad84[0x98];
    /* 0x011c */ u16 unk11C;
    /* 0x011e */ u8 pad11E[0x2];
} Unkstruct_8011F7A8; /* size = 0x120 */

typedef struct {
    /* Unkstruct_1fa9e810: P37 struct map 3144 sites in 131 bodies; evidence {'L': 1}; type_folds.tsv evidence E2-anchor; merges Unkstruct_1255bbfd (2091 sites, fields disjoint; added T2.c4); P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x12];
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x6];
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u8 pad3E[0x2];
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 pad42[0x5];
    /* 0x0047 */ u8 unk47;
    /* 0x0048 */ u8 unk48;
    /* 0x0049 */ u8 pad49[0x1];
    /* 0x004a */ u8 unk4A;
    /* 0x004b */ u8 pad4B[0x1];
} Unkstruct_8011F888; /* size = 0x4c */

typedef struct {
    /* Unkstruct_80126948: P37 struct map 3034 sites in 848 bodies; evidence {'PV': 3, 'PTR': 6, 'L': 115, 'P': 3, 'AT': 2}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 pad5[0x3];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ u16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x2];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u16 unk38;
    /* 0x003a */ u8 pad3A[0x2];
    /* 0x003c */ s32 unk3C;
    /* 0x0040 */ s32 unk40;
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0x8];
    /* 0x005c */ s32 unk5C;
    /* 0x0060 */ s32 unk60;
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ s32 unk68;
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ s32 unk70;
    /* 0x0074 */ u8 pad74[0x28];
    /* 0x009c */ s32 unk9C;
    /* 0x00a0 */ s16 unkA0;
    /* 0x00a2 */ s16 unkA2;
} Unkstruct_80126948; /* size = 0xa4 */

typedef struct {
    /* Unkstruct_a5d21dec: P37 struct map 4340 sites in 124 bodies; evidence {'L': 2, 'PV': 1, 'P': 1, 'R': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ u16 unk36;
    /* 0x0038 */ u8 pad38[0x18];
    /* 0x0050 */ u16 unk50;
    /* 0x0052 */ u16 unk52;
    /* 0x0054 */ u16 unk54;
    /* 0x0056 */ u8 pad56[0xe];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ s32 unk68;
    /* 0x006c */ u8 pad6C[0x4];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x4];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0xc];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x4e];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8012C890; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d12e3a28: P37 struct map 1364 sites in 124 bodies; evidence {'L': 2, 'PV': 1, 'P': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
} Unkstruct_8012C890_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_0b30043d: P37 struct map 1128 sites in 376 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_801320D8; /* size = 0x60 */

typedef struct {
    /* Unkstruct_e505dcd3: P37 struct map 868 sites in 124 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_801343C4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_23e45db5: P37 struct map 1512 sites in 126 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80134C20; /* size = 0x18 */

typedef struct {
    /* Unkstruct_1e86c313: P37 struct map 882 sites in 126 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_80135004; /* size = 0x8 */

typedef struct {
    /* Unkstruct_80135260: P37 struct map 390 sites in 130 bodies; evidence {'PV': 143, 'P': 143, 'L': 145}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80135260; /* size = 0x8 */

typedef struct {
    /* Unkstruct_f49880fd: P37 struct map 2000 sites in 125 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2a];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_80135480; /* size = 0x54 */

typedef struct {
    /* Unkstruct_cb638a45: P37 struct map 6477 sites in 381 bodies; evidence {'PV': 6, 'P': 6, 'L': 6}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80135EB0; /* size = 0x10 */

typedef struct {
    /* Unkstruct_919ca3ea: P37 struct map 1230 sites in 123 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80136824; /* size = 0x10 */

typedef struct {
    /* Unkstruct_ed8f1335: P37 struct map 2356 sites in 124 bodies; evidence {'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 unkE;
    /* 0x000f */ u8 unkF;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 unk14;
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 unk16;
    /* 0x0017 */ u8 pad17[0x1];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ s32 unk20;
} Unkstruct_801397B0; /* size = 0x24 */

typedef struct {
    /* Unkstruct_4db8cec8: P37 struct map 1240 sites in 124 bodies; evidence {'L': 2, 'PV': 1, 'P': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 pad21[0x1];
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x5];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u8 pad2C[0x4];
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801397B0_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_80139C7C: P37 struct map 2111 sites in 265 bodies; evidence {'PV': 6, 'P': 6, 'L': 6}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0xc];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 pad21[0x1];
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ u16 unk24;
    /* 0x0026 */ u16 unk26;
    /* 0x0028 */ u8 pad28[0x4];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0x8];
    /* 0x0040 */ s32 unk40;
} Unkstruct_80139C7C; /* size = 0x44 */

typedef struct {
    /* Unkstruct_f896d121: P37 struct map 2108 sites in 124 bodies; evidence {'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_8013B274; /* size = 0x20 */

typedef struct {
    /* Unkstruct_47470ce3: P37 struct map 1404 sites in 117 bodies; evidence {'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_801407F4; /* size = 0x20 */

typedef struct {
    /* Unkstruct_f0bc3b7a: P37 struct map 1240 sites in 124 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x1e];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ u8 pad94[0x4];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x62];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80142608; /* size = 0x100 */

typedef struct {
    /* Unkstruct_301381d4: P37 struct map 1116 sites in 124 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80143458; /* size = 0x38 */

typedef struct {
    /* Unkstruct_f9a7989e: P37 struct map 1179 sites in 131 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8014358C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_12f4cee2: P37 struct map 786 sites in 131 bodies; evidence {'L': 1, 'FLD': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 pad24[0x3];
    /* 0x0027 */ u8 unk27;
} Unkstruct_8014358C_2; /* size = 0x28 */

typedef struct {
    /* Unkstruct_801463A0: P37 struct map 907 sites in 210 bodies; evidence {'PTR': 1, 'L': 9}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0xa];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x1a];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_801463A0; /* size = 0x54 */

typedef struct {
    /* Unkstruct_859b4fab: P37 struct map 910 sites in 130 bodies; evidence {'L': 2, 'PV': 1, 'P': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x85];
    /* 0x00a9 */ u8 unkA9;
    /* 0x00aa */ u16 unkAA;
    /* 0x00ac */ u8 padAC[0x2];
    /* 0x00ae */ u16 unkAE;
} Unkstruct_80148AFC; /* size = 0xb0 */

typedef struct {
    /* Unkstruct_92677d11: P37 struct map 861 sites in 123 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x1e];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x210];
    /* 0x0234 */ s32 unk234;
    /* 0x0238 */ s32 unk238;
    /* 0x023c */ s32 unk23C;
} Unkstruct_8015C128; /* size = 0x240 */

typedef struct {
    /* Unkstruct_dac960ce: P37 struct map 4464 sites in 124 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x34];
    /* 0x0044 */ u32 unk44;
    /* 0x0048 */ u8 pad48[0x70];
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u16 unkBA;
    /* 0x00bc */ u8 padBC[0x102];
    /* 0x01be */ u8 unk1BE;
    /* 0x01bf */ u8 pad1BF[0x85];
    /* 0x0244 */ u8 unk244;
    /* 0x0245 */ u8 unk245;
    /* 0x0246 */ u16 unk246;
    /* 0x0248 */ u16 unk248;
    /* 0x024a */ u16 unk24A;
} Unkstruct_8015F448; /* size = 0x24c */

typedef struct {
    /* Unkstruct_4692fc17: P37 struct map 1612 sites in 124 bodies; evidence {'L': 2, 'FLD': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80164930; /* size = 0x20 */

typedef struct {
    /* Unkstruct_6d3f3f5d: P37 struct map 889 sites in 127 bodies; evidence {'L': 2}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x1a];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u32 unk24;
    /* 0x0028 */ u32 unk28;
    /* 0x002c */ u32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ u32 unk34;
} Unkstruct_80165240; /* size = 0x38 */

typedef struct {
    /* Unkstruct_b5c0372a: P37 struct map 1441 sites in 131 bodies; evidence {'L': 2, 'PV': 1, 'P': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u8 unk12;
    /* 0x0013 */ u8 pad13[0x1d];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u8 pad38[0x14];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_801670E4; /* size = 0x58 */

typedef struct {
    /* Unkstruct_30b21035: P37 struct map 3100 sites in 124 bodies; evidence {'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x2];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
    /* 0x0038 */ s16 unk38;
    /* 0x003a */ s16 unk3A;
    /* 0x003c */ s16 unk3C;
    /* 0x003e */ u8 pad3E[0x12];
    /* 0x0050 */ s32 unk50;
} Unkstruct_80167DBC; /* size = 0x54 */

typedef struct {
    /* Unkstruct_a459e3e5: P37 struct map 1220 sites in 122 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_801681FC; /* size = 0x34 */

typedef struct {
    /* Unkstruct_ffd2397c: P37 struct map 854 sites in 122 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xa];
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_80168430; /* size = 0x34 */

typedef struct {
    /* Unkstruct_86465c2c: P37 struct map 861 sites in 123 bodies; evidence {'L': 2}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
} Unkstruct_80168828; /* size = 0x20 */

typedef struct {
    /* Unkstruct_3f697924: P37 struct map 875 sites in 125 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x20];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016A290; /* size = 0x38 */

typedef struct {
    /* Unkstruct_4e09b6d9: P37 struct map 1572 sites in 131 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x14];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 pad25[0x1];
    /* 0x0026 */ u16 unk26;
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u8 pad32[0x2];
} Unkstruct_8016B234; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8016B4F8: P37 struct map 1 sites in 1 bodies; evidence {'L': 2, 'R': 1}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x2];
    /* 0x001e */ s16 unk1E;
} Unkstruct_8016B4F8; /* size = 0x20 */

typedef struct {
    /* Unkstruct_4857195e: P37 struct map 1107 sites in 123 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x6];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x4];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x6];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x12];
    /* 0x0030 */ u32 unk30;
} Unkstruct_8016BFD0; /* size = 0x34 */

typedef struct {
    /* Unkstruct_cd1bacd2: P37 struct map 1764 sites in 126 bodies; evidence {'L': 3, 'PV': 1, 'P': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016C188; /* size = 0x38 */

typedef struct {
    /* Unkstruct_a41ec127: P37 struct map 882 sites in 126 bodies; evidence {'L': 2, 'PV': 1, 'P': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016C2C4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_85709988: P37 struct map 889 sites in 127 bodies; evidence {'L': 1, 'FLD': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ u16 unk36;
} Unkstruct_8016C49C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_568f7bda: P37 struct map 1875 sites in 125 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ u8 pad2A[0x6];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ void * unk34;
} Unkstruct_8016C998; /* size = 0x38 */

typedef struct {
    /* Unkstruct_110cf29e: P37 struct map 1250 sites in 125 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0xe];
    /* 0x002a */ s16 unk2A;
} Unkstruct_8016CF04; /* size = 0x2c */

typedef struct {
    /* Unkstruct_198fc7cc: P37 struct map 2580 sites in 129 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u8 pad2A[0x2];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016D1D8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8016DF5C: P37 struct map 5 sites in 1 bodies; evidence {'L': 1}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DF5C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_f8ed2b9f: P37 struct map 4061 sites in 4061 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x216];
    /* 0x0216 */ u8 unk216;
    /* 0x0217 */ u8 pad217[0x1];
} Unkstruct_8016F6E0; /* size = 0x218 */

typedef struct {
    /* Unkstruct_a8d34bce: P37 struct map 1948 sites in 1948 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x214];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_801727D0; /* size = 0x218 */

typedef struct {
    /* Unkstruct_297e7547: P37 struct map 1240 sites in 124 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 pad5[0x7];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x8];
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ u8 pad34[0x20];
    /* 0x0054 */ s32 unk54;
} Unkstruct_80174BF4; /* size = 0x58 */

typedef struct {
    /* Unkstruct_0a8f505b: P37 struct map 790 sites in 83 bodies; evidence {'PV': 27, 'P': 27, 'L': 27}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x10];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x6c];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x4];
    /* 0x00d8 */ void * unkD8;
    /* 0x00dc */ void * unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u8 pad100[0x6];
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ s16 unk10A;
} Unkstruct_8017BEBC; /* size = 0x10c */

typedef struct {
    /* Unkstruct_57a28935: P37 struct map 3271 sites in 196 bodies; evidence {'PV': 134, 'P': 134, 'L': 134}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x5];
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x2];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ u8 pad34[0x8];
    /* 0x003c */ s32 unk3C;
    /* 0x0040 */ s32 unk40;
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0x48];
    /* 0x009c */ s32 unk9C;
    /* 0x00a0 */ u16 unkA0;
    /* 0x00a2 */ u16 unkA2;
} Unkstruct_8017CF48; /* size = 0xa4 */

typedef struct {
    /* Unkstruct_17738e2c: P37 struct map 876 sites in 33 bodies; evidence {'PV': 25, 'P': 25, 'L': 27}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x5];
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x2];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ u8 pad34[0x4];
    /* 0x0038 */ s16 unk38;
    /* 0x003a */ s16 unk3A;
    /* 0x003c */ s32 unk3C;
    /* 0x0040 */ s32 unk40;
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0x48];
    /* 0x009c */ s16 unk9C;
    /* 0x009e */ s16 unk9E;
    /* 0x00a0 */ s16 unkA0;
    /* 0x00a2 */ s16 unkA2;
} Unkstruct_8017D120; /* size = 0xa4 */

/* T3 (P3.40) band defs:begin — restruct.py --decide-band --write; generated, ordered by band rank */
typedef struct {
    /* Unkstruct_2ac2250b: P3.40 T3 band rank 2; 786 TNC sites in 131 bodies; struct map 786 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa9];
    /* 0x00a9 */ u8 unkA9;
    /* 0x00aa */ u16 unkAA;
    /* 0x00ac */ u8 padAC[0x2];
    /* 0x00ae */ u16 unkAE;
} Unkstruct_80148E54; /* size = 0xb0 */

typedef struct {
    /* Unkstruct_d827da45: P3.40 T3 band rank 3; 774 TNC sites in 258 bodies; struct map 774 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8015DCB8; /* size = 0x14 */

typedef struct {
    /* Unkstruct_36c327cf: P3.40 T3 band rank 5; 762 TNC sites in 127 bodies; struct map 762 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
} Unkstruct_80175AB8; /* size = 0x18 */

typedef struct {
    /* Unkstruct_ebcdd1a9: P3.40 T3 band rank 6; 756 TNC sites in 126 bodies; struct map 756 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
} Unkstruct_8015094C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_27a19d58: P3.40 T3 band rank 7; 750 TNC sites in 125 bodies; struct map 750 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_80135480_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_38975874: P3.40 T3 band rank 8; 744 TNC sites in 124 bodies; struct map 744 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x12];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x52];
    /* 0x0080 */ void * unk80;
} Unkstruct_801647A4; /* size = 0x84 */

typedef struct {
    /* Unkstruct_64375b18: P3.40 T3 band rank 9; 744 TNC sites in 124 bodies; struct map 744 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x72];
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x1c];
    /* 0x0090 */ void * unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x2];
    /* 0x009a */ s16 unk9A;
    /* 0x009c */ s32 unk9C;
} Unkstruct_8012ACA0; /* size = 0xa0 */

typedef struct {
    /* Unkstruct_72479d90: P3.40 T3 band rank 10; 744 TNC sites in 124 bodies; struct map 744 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x68];
    /* 0x0078 */ s32 unk78;
} Unkstruct_8015D5E8; /* size = 0x7c */

typedef struct {
    /* Unkstruct_76b1caf3: P3.40 T3 band rank 11; 744 TNC sites in 124 bodies; struct map 744 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 pad3[0x1];
} Unkstruct_8016EB3C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_6f21e02b: P3.40 T3 band rank 12; 711 TNC sites in 79 bodies; struct map 711 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x54];
    /* 0x0078 */ s32 unk78;
} Unkstruct_8015D738; /* size = 0x7c */

typedef struct {
    /* Unkstruct_8016BBE0: P3.40 T3 band rank 13; 695 TNC sites in 139 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016BBE0; /* size = 0x1c */

typedef struct {
    /* Unkstruct_896c95f7: P3.40 T3 band rank 15; 665 TNC sites in 133 bodies; struct map 665 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8012E364; /* size = 0x60 */

typedef struct {
    /* Unkstruct_fdd04bae: P3.40 T3 band rank 18; 650 TNC sites in 130 bodies; struct map 650 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ s16 unk36;
} Unkstruct_801424E4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_27c177f1: P3.40 T3 band rank 19; 645 TNC sites in 129 bodies; struct map 645 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x12];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ s32 unk30;
} Unkstruct_8016D688; /* size = 0x34 */

typedef struct {
    /* Unkstruct_eb8b6fbf: P3.40 T3 band rank 20; 645 TNC sites in 129 bodies; struct map 645 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x7e];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80132018; /* size = 0x100 */

typedef struct {
    /* Unkstruct_187abeff: P3.40 T3 band rank 22; 630 TNC sites in 126 bodies; struct map 630 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ u8 pad30[0x30];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ s16 unk62;
    /* 0x0064 */ u8 pad64[0x2];
    /* 0x0066 */ s16 unk66;
} Unkstruct_80164EE0; /* size = 0x68 */

typedef struct {
    /* Unkstruct_4f9f60b8: P3.40 T3 band rank 23; 630 TNC sites in 126 bodies; struct map 630 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x5a];
    /* 0x0076 */ s16 unk76;
} Unkstruct_801431E8; /* size = 0x78 */

typedef struct {
    /* Unkstruct_578311f7: P3.40 T3 band rank 24; 630 TNC sites in 126 bodies; struct map 630 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x2];
    /* 0x001e */ s16 unk1E;
} Unkstruct_8016C188_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_7a31a22f: P3.40 T3 band rank 25; 630 TNC sites in 126 bodies; struct map 630 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x174];
    /* 0x0198 */ s32 unk198;
} Unkstruct_80158FA4; /* size = 0x19c */

typedef struct {
    /* Unkstruct_ad0948d5: P3.40 T3 band rank 26; 625 TNC sites in 125 bodies; struct map 625 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016BBE0_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_fccefc1f: P3.40 T3 band rank 27; 625 TNC sites in 125 bodies; struct map 625 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_8016BD78; /* size = 0x1c */

typedef struct {
    /* Unkstruct_af1e9d57: P3.40 T3 band rank 28; 620 TNC sites in 248 bodies; struct map 620 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2c];
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0xc];
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u16 unk62;
} Unkstruct_801647A4_2; /* size = 0x64 */

typedef struct {
    /* Unkstruct_172cbd29: P3.40 T3 band rank 29; 620 TNC sites in 124 bodies; struct map 620 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x1f6];
    /* 0x01f8 */ s32 unk1F8;
} Unkstruct_801654A8; /* size = 0x1fc */

typedef struct {
    /* Unkstruct_b500a675: P3.40 T3 band rank 30; 620 TNC sites in 124 bodies; struct map 620 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801596F0; /* size = 0x2c */

typedef struct {
    /* Unkstruct_c5b84dea: P3.40 T3 band rank 31; 620 TNC sites in 124 bodies; struct map 620 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8016DA7C; /* size = 0x24 */

typedef struct {
    /* Unkstruct_fb1c8e17: P3.40 T3 band rank 32; 620 TNC sites in 124 bodies; struct map 620 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DF5C_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_aaf4c4dd: P3.40 T3 band rank 33; 615 TNC sites in 615 bodies; struct map 615 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80159698; /* size = 0x18 */

typedef struct {
    /* Unkstruct_01082f7a: P3.40 T3 band rank 36; 520 TNC sites in 520 bodies; struct map 520 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8015E1B8; /* size = 0x4 */

typedef struct {
    /* Unkstruct_30befa8c: P3.40 T3 band rank 37; 520 TNC sites in 130 bodies; struct map 520 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80142EC0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_db475375: P3.40 T3 band rank 38; 516 TNC sites in 129 bodies; struct map 516 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ u16 unk36;
} Unkstruct_8016D1D8_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_290ce261: P3.40 T3 band rank 39; 504 TNC sites in 126 bodies; struct map 504 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801431E8_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d6100faa: P3.40 T3 band rank 40; 504 TNC sites in 126 bodies; struct map 504 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0xc];
    /* 0x001e */ s16 unk1E;
} Unkstruct_80164BDC; /* size = 0x20 */

typedef struct {
    /* Unkstruct_fc43506c: P3.40 T3 band rank 41; 504 TNC sites in 126 bodies; struct map 504 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8017BB34; /* size = 0x10 */

typedef struct {
    /* Unkstruct_7cb40b10: P3.40 T3 band rank 42; 500 TNC sites in 500 bodies; struct map 500 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_801427EC; /* size = 0x4 */

typedef struct {
    /* Unkstruct_2a236a98: P3.40 T3 band rank 43; 500 TNC sites in 125 bodies; struct map 500 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8016A290_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_4e843375: P3.40 T3 band rank 44; 500 TNC sites in 125 bodies; struct map 500 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8016A290_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_2191b495: P3.40 T3 band rank 45; 496 TNC sites in 124 bodies; struct map 496 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_80143458_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_494cef68: P3.40 T3 band rank 46; 496 TNC sites in 124 bodies; struct map 496 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x182];
    /* 0x0184 */ u32 unk184;
} Unkstruct_8015FAE8; /* size = 0x188 */

typedef struct {
    /* Unkstruct_6216dfea: P3.40 T3 band rank 47; 496 TNC sites in 124 bodies; struct map 496 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ u16 unk36;
} Unkstruct_80144364; /* size = 0x38 */

typedef struct {
    /* Unkstruct_66c4b257: P3.40 T3 band rank 48; 496 TNC sites in 124 bodies; struct map 496 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
} Unkstruct_801397B0_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_6feef4cf: P3.40 T3 band rank 49; 496 TNC sites in 124 bodies; struct map 496 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ u16 unk36;
} Unkstruct_80144880; /* size = 0x38 */

typedef struct {
    /* Unkstruct_7a201374: P3.40 T3 band rank 50; 492 TNC sites in 123 bodies; struct map 492 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ s32 unk28;
} Unkstruct_80176218; /* size = 0x2c */

typedef struct {
    /* Unkstruct_9e228c39: P3.40 T3 band rank 51; 492 TNC sites in 123 bodies; struct map 492 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_801312D0; /* size = 0x8 */

typedef struct {
    /* Unkstruct_48c11385: P3.40 T3 band rank 52; 441 TNC sites in 21 bodies; struct map 441 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017DCEC; /* size = 0x68 */

typedef struct {
    /* Unkstruct_a55a221e: P3.40 T3 band rank 53; 428 TNC sites in 428 bodies; struct map 428 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x214];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_80172CA0; /* size = 0x218 */

typedef struct {
    /* Unkstruct_80176734: P3.40 T3 band rank 54; 416 TNC sites in 133 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x28];
    /* 0x0028 */ s32 unk28;
} Unkstruct_80176734; /* size = 0x2c */

typedef struct {
    /* Unkstruct_f9be7d6a: P3.40 T3 band rank 55; 405 TNC sites in 45 bodies; struct map 405 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x54];
    /* 0x0078 */ s32 unk78;
} Unkstruct_8015D738_2; /* size = 0x7c */

typedef struct {
    /* Unkstruct_630777a3: P3.40 T3 band rank 56; 399 TNC sites in 266 bodies; struct map 399 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 pad1[0x3];
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 pad5[0x3];
} Unkstruct_8013B83C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_6fb60628: P3.40 T3 band rank 57; 399 TNC sites in 133 bodies; struct map 399 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8016C49C_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8011F7F0: P3.40 T3 band rank 58; 399 TNC sites in 133 bodies; struct map 399 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1e];
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ u8 pad20[0xe];
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u8 pad30[0x10];
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 pad42[0x2];
} Unkstruct_80175DA8; /* size = 0x44 */

typedef struct {
    /* Unkstruct_80164BDC: P3.40 T3 band rank 59; 388 TNC sites in 128 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0xc];
    /* 0x001e */ s16 unk1E;
} Unkstruct_80164BDC_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_0dc81dc1: P3.40 T3 band rank 60; 387 TNC sites in 129 bodies; struct map 387 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016D1D8_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_8c2ab96e: P3.40 T3 band rank 61; 384 TNC sites in 128 bodies; struct map 384 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8016EC0C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_3c0c25b7: P3.40 T3 band rank 64; 381 TNC sites in 127 bodies; struct map 381 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
} Unkstruct_8016C49C_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_53412f36: P3.40 T3 band rank 67; 378 TNC sites in 126 bodies; struct map 378 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ u16 unk20;
    /* 0x0022 */ u16 unk22;
} Unkstruct_80175DA8_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_8dd0822e: P3.40 T3 band rank 68; 378 TNC sites in 126 bodies; struct map 378 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8017BA3C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_a9ad0f6a: P3.40 T3 band rank 69; 378 TNC sites in 126 bodies; struct map 378 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016C2C4_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_b36b9c5c: P3.40 T3 band rank 70; 378 TNC sites in 126 bodies; struct map 378 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
} Unkstruct_80169BBC; /* size = 0x1c */

typedef struct {
    /* Unkstruct_d0754cca: P3.40 T3 band rank 72; 375 TNC sites in 125 bodies; struct map 375 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8016BD78_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_39de3511: P3.40 T3 band rank 73; 372 TNC sites in 124 bodies; struct map 372 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8015E4B0; /* size = 0x14 */

typedef struct {
    /* Unkstruct_7f39c942: P3.40 T3 band rank 74; 372 TNC sites in 124 bodies; struct map 372 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
} Unkstruct_8016DC20; /* size = 0x1c */

typedef struct {
    /* Unkstruct_7fd6458b: P3.40 T3 band rank 75; 372 TNC sites in 124 bodies; struct map 372 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3c];
    /* 0x003c */ s32 unk3C;
} Unkstruct_8015E4B0_2; /* size = 0x40 */

typedef struct {
    /* Unkstruct_8260f98a: P3.40 T3 band rank 76; 372 TNC sites in 124 bodies; struct map 372 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016B5C0; /* size = 0x1c */

typedef struct {
    /* Unkstruct_89f82b52: P3.40 T3 band rank 77; 372 TNC sites in 124 bodies; struct map 372 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x44];
    /* 0x0044 */ u32 unk44;
    /* 0x0048 */ u8 pad48[0x64];
    /* 0x00ac */ u16 unkAC;
    /* 0x00ae */ u8 padAE[0x11a];
    /* 0x01c8 */ s16 unk1C8;
    /* 0x01ca */ u8 pad1CA[0x2];
} Unkstruct_80149FB0; /* size = 0x1cc */

typedef struct {
    /* Unkstruct_1b4331f0: P3.40 T3 band rank 79; 369 TNC sites in 123 bodies; struct map 369 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_80132144; /* size = 0x60 */

typedef struct {
    /* Unkstruct_75e9a6af: P3.40 T3 band rank 80; 369 TNC sites in 123 bodies; struct map 369 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_8016E7C8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_bf723e51: P3.40 T3 band rank 82; 364 TNC sites in 14 bodies; struct map 364 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x12];
    /* 0x0030 */ s32 unk30;
} Unkstruct_801805C8; /* size = 0x34 */

typedef struct {
    /* Unkstruct_5f78a994: P3.40 T3 band rank 83; 336 TNC sites in 24 bodies; struct map 336 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017BEF8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_09b02bee: P3.40 T3 band rank 84; 300 TNC sites in 75 bodies; struct map 300 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
} Unkstruct_8013AD38; /* size = 0x4 */

typedef struct {
    /* Unkstruct_33ccb6b5: P3.40 T3 band rank 86; 294 TNC sites in 98 bodies; struct map 294 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80169F3C; /* size = 0x24 */

typedef struct {
    /* Unkstruct_1ef3b11b: P3.40 T3 band rank 87; 280 TNC sites in 10 bodies; struct map 280 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x50];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x62];
    /* 0x00d4 */ void * unkD4;
    /* 0x00d8 */ void * unkD8;
    /* 0x00dc */ u8 padDC[0x20];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0xa];
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ s16 unk10A;
} Unkstruct_8017C41C; /* size = 0x10c */

typedef struct {
    /* Unkstruct_80129CF8: P3.40 T3 band rank 88; 273 TNC sites in 90 bodies; struct map 273 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x188];
    /* 0x0188 */ u16 unk188;
    /* 0x018a */ u16 unk18A;
    /* 0x018c */ u8 pad18C[0xc];
    /* 0x0198 */ s32 unk198;
    /* 0x019c */ u16 unk19C;
    /* 0x019e */ u16 unk19E;
    /* 0x01a0 */ u8 pad1A0[0xa208];
    /* 0xa3a8 */ u16 unkA3A8;
    /* 0xa3aa */ u16 unkA3AA;
    /* 0xa3ac */ u16 unkA3AC;
    /* 0xa3ae */ u16 unkA3AE;
    /* 0xa3b0 */ u16 unkA3B0;
    /* 0xa3b2 */ u8 padA3B2[0x2];
    /* 0xa3b4 */ u16 unkA3B4;
    /* 0xa3b6 */ u16 unkA3B6;
    /* 0xa3b8 */ u16 unkA3B8;
    /* 0xa3ba */ u16 unkA3BA;
    /* 0xa3bc */ u16 unkA3BC;
    /* 0xa3be */ u16 unkA3BE;
    /* 0xa3c0 */ u16 unkA3C0;
    /* 0xa3c2 */ u16 unkA3C2;
    /* 0xa3c4 */ u8 padA3C4[0x2];
    /* 0xa3c6 */ u16 unkA3C6;
    /* 0xa3c8 */ u16 unkA3C8;
    /* 0xa3ca */ u16 unkA3CA;
    /* 0xa3cc */ u16 unkA3CC;
    /* 0xa3ce */ u16 unkA3CE;
    /* 0xa3d0 */ u16 unkA3D0;
    /* 0xa3d2 */ u16 unkA3D2;
    /* 0xa3d4 */ u16 unkA3D4;
    /* 0xa3d6 */ u8 padA3D6[0x2];
    /* 0xa3d8 */ s16 unkA3D8;
    /* 0xa3da */ s16 unkA3DA;
    /* 0xa3dc */ s16 unkA3DC;
    /* 0xa3de */ s16 unkA3DE;
    /* 0xa3e0 */ u8 padA3E0[0x3];
    /* 0xa3e3 */ u8 unkA3E3;
    /* 0xa3e4 */ u8 padA3E4[0x4];
    /* 0xa3e8 */ s32 unkA3E8;
    /* 0xa3ec */ u8 padA3EC[0x48];
    /* 0xa434 */ u8 unkA434;
    /* 0xa435 */ u8 padA435[0x3];
} Unkstruct_80010178; /* size = 0xa438 */

typedef struct {
    /* Unkstruct_a2d6c72b: P3.40 T3 band rank 89; 273 TNC sites in 21 bodies; struct map 273 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x8c];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017ECD4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_800AF630: P3.40 T3 band rank 90; 269 TNC sites in 135 bodies; struct map 671 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 pad1[0xa3d1];
    /* 0xa3d2 */ u16 unkA3D2;
    /* 0xa3d4 */ u8 padA3D4[0x6];
    /* 0xa3da */ s16 unkA3DA;
} Unkstruct_8012956C; /* size = 0xa3dc */

typedef struct {
    /* Unkstruct_8012C1DC: P3.40 T3 band rank 91; 268 TNC sites in 134 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8012C1DC; /* size = 0x24 */

typedef struct {
    /* Unkstruct_1db7b82d: P3.40 T3 band rank 93; 266 TNC sites in 133 bodies; struct map 266 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8012E364_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_6bd63257: P3.40 T3 band rank 94; 266 TNC sites in 133 bodies; struct map 266 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8012E364_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_30ffce68: P3.40 T3 band rank 98; 262 TNC sites in 131 bodies; struct map 262 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0x89];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80143D28; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_3816caab: P3.40 T3 band rank 99; 260 TNC sites in 130 bodies; struct map 260 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80142EC0_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_ac2c8f05: P3.40 T3 band rank 100; 260 TNC sites in 130 bodies; struct map 260 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x16c];
    /* 0x016c */ u16 unk16C;
    /* 0x016e */ u8 pad16E[0x2];
} Unkstruct_80150B28; /* size = 0x170 */

typedef struct {
    /* Unkstruct_985493b9: P3.40 T3 band rank 101; 256 TNC sites in 128 bodies; struct map 256 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a8];
    /* 0x01a8 */ u8 unk1A8;
    /* 0x01a9 */ u8 pad1A9[0x17];
    /* 0x01c0 */ u8 unk1C0;
    /* 0x01c1 */ u8 pad1C1[0x3];
} Unkstruct_80156044; /* size = 0x1c4 */

typedef struct {
    /* Unkstruct_c21b1a66: P3.40 T3 band rank 102; 255 TNC sites in 255 bodies; struct map 255 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 pad5[0x3];
} Unkstruct_8017496C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_746c35d0: P3.40 T3 band rank 103; 252 TNC sites in 126 bodies; struct map 252 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80158FA4_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_5d117345: P3.40 T3 band rank 105; 252 TNC sites in 21 bodies; struct map 252 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x8c];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017EC08; /* size = 0x100 */

typedef struct {
    /* Unkstruct_ae2d1f2a: P3.40 T3 band rank 106; 252 TNC sites in 7 bodies; struct map 252 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x34];
    /* 0x0044 */ u32 unk44;
    /* 0x0048 */ u8 pad48[0x70];
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u16 unkBA;
    /* 0x00bc */ u8 padBC[0x102];
    /* 0x01be */ u8 unk1BE;
    /* 0x01bf */ u8 pad1BF[0x85];
    /* 0x0244 */ u8 unk244;
    /* 0x0245 */ u8 unk245;
    /* 0x0246 */ u16 unk246;
    /* 0x0248 */ u16 unk248;
    /* 0x024a */ u16 unk24A;
} Unkstruct_8015F448_2; /* size = 0x24c */

typedef struct {
    /* Unkstruct_576bfafb: P3.40 T3 band rank 111; 248 TNC sites in 248 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x40];
    /* 0x0044 */ u32 unk44;
} Unkstruct_80175184; /* size = 0x48 */

typedef struct {
    /* Unkstruct_28d9f75d: P3.40 T3 band rank 112; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x44];
    /* 0x0044 */ u32 unk44;
    /* 0x0048 */ u8 pad48[0x14f];
    /* 0x0197 */ u8 unk197;
} Unkstruct_80165B28; /* size = 0x198 */

typedef struct {
    /* Unkstruct_3ec1f7d3: P3.40 T3 band rank 113; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8016EBA8; /* size = 0x8 */

typedef struct {
    /* Unkstruct_539a2ae1: P3.40 T3 band rank 114; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80142E38; /* size = 0x100 */

typedef struct {
    /* Unkstruct_5f2977df: P3.40 T3 band rank 115; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8014305C; /* size = 0x1c */

typedef struct {
    /* Unkstruct_65a4104e: P3.40 T3 band rank 116; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb8];
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u8 padBA[0x2];
} Unkstruct_80173220; /* size = 0xbc */

typedef struct {
    /* Unkstruct_830ea620: P3.40 T3 band rank 117; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb4];
    /* 0x00b4 */ u32 unkB4;
    /* 0x00b8 */ u8 padB8[0x9];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_8012F8C8; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_8d9788e9: P3.40 T3 band rank 118; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_801397B0_4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_8e3ffd0a: P3.40 T3 band rank 119; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_8015D380; /* size = 0x14 */

typedef struct {
    /* Unkstruct_9fb4bfac: P3.40 T3 band rank 120; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80142E38_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_a34caab1: P3.40 T3 band rank 121; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80142DC4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_a45ed457: P3.40 T3 band rank 122; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
} Unkstruct_8013B274_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_ca3ab5df: P3.40 T3 band rank 123; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80142DC4_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d294081d: P3.40 T3 band rank 124; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80164744; /* size = 0x24 */

typedef struct {
    /* Unkstruct_f6997d4b: P3.40 T3 band rank 125; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8015D380_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_82fd4ac2: P3.40 T3 band rank 126; 247 TNC sites in 247 bodies; struct map 247 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 pad2[0x2];
} Unkstruct_8017553C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_0aa75240: P3.40 T3 band rank 127; 246 TNC sites in 123 bodies; struct map 246 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x32a];
    /* 0x032a */ s16 unk32A;
} Unkstruct_80176218_2; /* size = 0x32c */

typedef struct {
    /* Unkstruct_68acbe6c: P3.40 T3 band rank 128; 246 TNC sites in 123 bodies; struct map 246 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5d];
    /* 0x005d */ u8 unk5D;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_80176218_3; /* size = 0x60 */

typedef struct {
    /* Unkstruct_9f3ec286: P3.40 T3 band rank 129; 246 TNC sites in 123 bodies; struct map 246 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xf8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80142A10; /* size = 0x100 */

typedef struct {
    /* Unkstruct_b10794ea: P3.40 T3 band rank 130; 246 TNC sites in 123 bodies; struct map 246 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8016E9EC; /* size = 0x8 */

typedef struct {
    /* Unkstruct_4130873d: P3.40 T3 band rank 131; 245 TNC sites in 7 bodies; struct map 245 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ u16 unk36;
    /* 0x0038 */ u8 pad38[0x18];
    /* 0x0050 */ u16 unk50;
    /* 0x0052 */ u16 unk52;
    /* 0x0054 */ u16 unk54;
    /* 0x0056 */ u8 pad56[0xe];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ s32 unk68;
    /* 0x006c */ u8 pad6C[0x4];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x4];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0xc];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x4e];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8012C890_3; /* size = 0x100 */

typedef struct {
    /* Unkstruct_f20178fa: P3.40 T3 band rank 134; 237 TNC sites in 79 bodies; struct map 237 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8015D738_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_520ce05f: P3.40 T3 band rank 135; 228 TNC sites in 228 bodies; struct map 228 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x216];
    /* 0x0216 */ u8 unk216;
    /* 0x0217 */ u8 pad217[0x1];
} Unkstruct_8016F6E0_2; /* size = 0x218 */

typedef struct {
    /* Unkstruct_a82a43aa: P3.40 T3 band rank 136; 224 TNC sites in 28 bodies; struct map 224 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8017DF78; /* size = 0x10 */

typedef struct {
    /* Unkstruct_4a619ff2: P3.40 T3 band rank 140; 210 TNC sites in 21 bodies; struct map 210 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0xa];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017DCEC_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_7c055e94: P3.40 T3 band rank 141; 204 TNC sites in 12 bodies; struct map 204 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80135EB0_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_51b35d2d: P3.40 T3 band rank 142; 202 TNC sites in 101 bodies; struct map 202 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017CB70; /* size = 0x2c */

typedef struct {
    /* Unkstruct_801439FC: P3.40 T3 band rank 143; 199 TNC sites in 147 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801439FC; /* size = 0x18 */

typedef struct {
    /* Unkstruct_eadcd5d5: P3.40 T3 band rank 144; 198 TNC sites in 18 bodies; struct map 198 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xdc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017D804; /* size = 0x100 */

typedef struct {
    /* Unkstruct_4ae47845: P3.40 T3 band rank 145; 192 TNC sites in 48 bodies; struct map 192 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
} Unkstruct_8013AD38_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_a00e0c6e: P3.40 T3 band rank 147; 190 TNC sites in 95 bodies; struct map 190 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017CB30; /* size = 0x2c */

typedef struct {
    /* Unkstruct_bd4a4f6c: P3.40 T3 band rank 148; 183 TNC sites in 61 bodies; struct map 183 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017CC48; /* size = 0x2c */

typedef struct {
    /* Unkstruct_8e763649: P3.40 T3 band rank 149; 175 TNC sites in 7 bodies; struct map 175 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x2];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
    /* 0x0038 */ s16 unk38;
    /* 0x003a */ s16 unk3A;
    /* 0x003c */ s16 unk3C;
    /* 0x003e */ u8 pad3E[0x12];
    /* 0x0050 */ s32 unk50;
} Unkstruct_80167DBC_2; /* size = 0x54 */

typedef struct {
    /* Unkstruct_7079957f: P3.40 T3 band rank 151; 168 TNC sites in 21 bodies; struct map 168 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017DCEC_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_a2d44c90: P3.40 T3 band rank 156; 156 TNC sites in 4 bodies; struct map 156 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x96];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ s32 unkD8;
    /* 0x00dc */ u8 padDC[0x4];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x8];
    /* 0x00ec */ s32 unkEC;
    /* 0x00f0 */ u8 padF0[0xe];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ u8 pad100[0x2];
    /* 0x0102 */ u16 unk102;
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ s16 unk106;
} Unkstruct_8017EF34; /* size = 0x108 */

typedef struct {
    /* Unkstruct_d0faeda3: P3.40 T3 band rank 157; 153 TNC sites in 17 bodies; struct map 153 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017D7D0; /* size = 0x14 */

typedef struct {
    /* Unkstruct_ea987c97: P3.40 T3 band rank 158; 153 TNC sites in 3 bodies; struct map 153 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x44];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x6a];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ s16 unkDE;
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x2];
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ s16 unkE6;
    /* 0x00e8 */ s16 unkE8;
    /* 0x00ea */ u8 padEA[0x2];
    /* 0x00ec */ s16 unkEC;
    /* 0x00ee */ s16 unkEE;
    /* 0x00f0 */ s16 unkF0;
    /* 0x00f2 */ u8 padF2[0x2];
    /* 0x00f4 */ s16 unkF4;
    /* 0x00f6 */ s16 unkF6;
    /* 0x00f8 */ s16 unkF8;
    /* 0x00fa */ u8 padFA[0x2];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_801825C0; /* size = 0x10c */

typedef struct {
    /* Unkstruct_3b68bc3b: P3.40 T3 band rank 160; 150 TNC sites in 6 bodies; struct map 150 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x28];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017EB8C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_80176218: P3.40 T3 band rank 165; 142 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x32a];
    /* 0x032a */ s16 unk32A;
} Unkstruct_80176218_4; /* size = 0x32c */

typedef struct {
    /* Unkstruct_38a68e34: P3.40 T3 band rank 167; 140 TNC sites in 10 bodies; struct map 140 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x64];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5e];
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x8];
    /* 0x00dc */ void * unkDC;
} Unkstruct_8017C130; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_8937c16a: P3.40 T3 band rank 169; 135 TNC sites in 45 bodies; struct map 135 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8015D738_4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_bb764c0e: P3.40 T3 band rank 170; 135 TNC sites in 15 bodies; struct map 135 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017BF88; /* size = 0x38 */

typedef struct {
    /* Unkstruct_913e79ea: P3.40 T3 band rank 178; 133 TNC sites in 133 bodies; struct map 133 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x32];
    /* 0x0032 */ u16 unk32;
} Unkstruct_80176734_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_cd605c73: P3.40 T3 band rank 179; 133 TNC sites in 7 bodies; struct map 133 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 unkE;
    /* 0x000f */ u8 unkF;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 unk14;
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 unk16;
    /* 0x0017 */ u8 pad17[0x1];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ s32 unk20;
} Unkstruct_801397B0_5; /* size = 0x24 */

typedef struct {
    /* Unkstruct_1c3d008e: P3.40 T3 band rank 180; 132 TNC sites in 132 bodies; struct map 132 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8015BE38; /* size = 0x4 */

typedef struct {
    /* Unkstruct_cb6870d9: P3.40 T3 band rank 181; 132 TNC sites in 6 bodies; struct map 132 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017EB8C_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_775ff288: P3.40 T3 band rank 183; 131 TNC sites in 131 bodies; struct map 131 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x28];
    /* 0x0028 */ s32 unk28;
} Unkstruct_80176734_3; /* size = 0x2c */

typedef struct {
    /* Unkstruct_302ac0d3: P3.40 T3 band rank 184; 130 TNC sites in 130 bodies; struct map 130 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb8];
    /* 0x00b8 */ s32 unkB8;
} Unkstruct_8015CA28; /* size = 0xbc */

typedef struct {
    /* Unkstruct_364b9046: P3.40 T3 band rank 185; 130 TNC sites in 130 bodies; struct map 130 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8015D4E8; /* size = 0x4 */

typedef struct {
    /* Unkstruct_8099f052: P3.40 T3 band rank 186; 130 TNC sites in 130 bodies; struct map 130 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80148AFC_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_1e51e8dd: P3.40 T3 band rank 188; 130 TNC sites in 10 bodies; struct map 130 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017DA08; /* size = 0x24 */

typedef struct {
    /* Unkstruct_28565378: P3.40 T3 band rank 189; 129 TNC sites in 1 bodies; struct map 129 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u16 unk36;
    /* 0x0038 */ u8 pad38[0x20];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x6];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x4];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x42];
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u8 padB8[0x4];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 unkC0;
    /* 0x00c1 */ u8 padC1[0xb];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x28];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u16 unk106;
} Unkstruct_8017EF3C; /* size = 0x108 */

typedef struct {
    /* Unkstruct_6462c414: P3.40 T3 band rank 191; 128 TNC sites in 128 bodies; struct map 128 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a0];
    /* 0x01a0 */ u8 unk1A0;
    /* 0x01a1 */ u8 pad1A1[0x3];
} Unkstruct_801659DC; /* size = 0x1a4 */

typedef struct {
    /* Unkstruct_ceffcaee: P3.40 T3 band rank 193; 128 TNC sites in 4 bodies; struct map 128 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x4];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u8 pad3C[0x2];
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 unk42;
    /* 0x0043 */ u8 pad43[0x7];
    /* 0x004a */ u8 unk4A;
    /* 0x004b */ u8 pad4B[0x1];
} Unkstruct_80176218_5; /* size = 0x4c */

typedef struct {
    /* Unkstruct_c71d4e66: P3.40 T3 band rank 194; 127 TNC sites in 127 bodies; struct map 127 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ s32 unk34;
} Unkstruct_80166994; /* size = 0x38 */

typedef struct {
    /* Unkstruct_3fb9e45a: P3.40 T3 band rank 198; 126 TNC sites in 126 bodies; struct map 126 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x198];
    /* 0x0198 */ s32 unk198;
} Unkstruct_80158F00; /* size = 0x19c */

typedef struct {
    /* Unkstruct_6983585f: P3.40 T3 band rank 199; 126 TNC sites in 126 bodies; struct map 126 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa8];
    /* 0x00a8 */ u8 unkA8;
    /* 0x00a9 */ u8 padA9[0x3];
} Unkstruct_8015879C; /* size = 0xac */

typedef struct {
    /* Unkstruct_b690623c: P3.40 T3 band rank 200; 126 TNC sites in 126 bodies; struct map 126 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa8];
    /* 0x00a8 */ s8 unkA8;
    /* 0x00a9 */ u8 padA9[0x3];
} Unkstruct_80158814; /* size = 0xac */

typedef struct {
    /* Unkstruct_8d78c711: P3.40 T3 band rank 206; 126 TNC sites in 21 bodies; struct map 126 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_8017E52C; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_267e7190: P3.40 T3 band rank 207; 126 TNC sites in 7 bodies; struct map 126 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
    /* 0x001c */ u32 unk1C;
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u32 unk24;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x1a];
    /* 0x0048 */ u32 unk48;
    /* 0x004c */ u32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_8017E2EC_3; /* size = 0x54 */

typedef struct {
    /* Unkstruct_58539f7b: P3.40 T3 band rank 208; 126 TNC sites in 6 bodies; struct map 126 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x6];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0xe];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ u8 pad78[0x84];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x4];
    /* 0x0102 */ s16 unk102;
} Unkstruct_80181720; /* size = 0x104 */

typedef struct {
    /* Unkstruct_901b89cb: P3.40 T3 band rank 209; 126 TNC sites in 6 bodies; struct map 126 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ s32 unk30;
} Unkstruct_80169BBC_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_000b7e6b: P3.40 T3 band rank 210; 125 TNC sites in 125 bodies; struct map 125 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8016A290_4; /* size = 0x24 */

typedef struct {
    /* Unkstruct_0dd56c5b: P3.40 T3 band rank 211; 125 TNC sites in 125 bodies; struct map 125 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80135480_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_72699c5a: P3.40 T3 band rank 212; 125 TNC sites in 125 bodies; struct map 125 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016BEA0; /* size = 0x1c */

typedef struct {
    /* Unkstruct_e5aea286: P3.40 T3 band rank 214; 125 TNC sites in 125 bodies; struct map 125 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8016BEA0_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_8014964C: P3.40 T3 band rank 218; 125 TNC sites in 58 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
} Unkstruct_80149184; /* size = 0xc */

typedef struct {
    /* Unkstruct_13259012: P3.40 T3 band rank 219; 125 TNC sites in 25 bodies; struct map 125 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc0];
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_8017C5F0; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_b0b781df: P3.40 T3 band rank 220; 125 TNC sites in 5 bodies; struct map 125 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 unk21;
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 unk29;
    /* 0x002a */ u8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
    /* 0x002c */ u8 unk2C;
    /* 0x002d */ u8 unk2D;
    /* 0x002e */ u8 unk2E;
    /* 0x002f */ u8 pad2F[0x1];
    /* 0x0030 */ s32 unk30;
} Unkstruct_80183D98; /* size = 0x34 */

typedef struct {
    /* Unkstruct_f5341aa7: P3.40 T3 band rank 221; 125 TNC sites in 5 bodies; struct map 125 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017DCD0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_6041cf7d: P3.40 T3 band rank 225; 124 TNC sites in 124 bodies; struct map 124 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80138BE0; /* size = 0x8 */

typedef struct {
    /* Unkstruct_66e810b1: P3.40 T3 band rank 226; 124 TNC sites in 124 bodies; struct map 124 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80144458; /* size = 0x14 */

typedef struct {
    /* Unkstruct_706b3809: P3.40 T3 band rank 227; 124 TNC sites in 124 bodies; struct map 124 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x198];
    /* 0x0198 */ s32 unk198;
} Unkstruct_8015FD74; /* size = 0x19c */

typedef struct {
    /* Unkstruct_74a0deaa: P3.40 T3 band rank 228; 124 TNC sites in 124 bodies; struct map 124 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18c];
    /* 0x018c */ void * unk18C;
} Unkstruct_8015E4B0_3; /* size = 0x190 */

typedef struct {
    /* Unkstruct_86d4fb80: P3.40 T3 band rank 229; 124 TNC sites in 124 bodies; struct map 124 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc1];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80130D0C; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_91e4f527: P3.40 T3 band rank 230; 124 TNC sites in 124 bodies; struct map 124 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x215];
    /* 0x0215 */ u8 unk215;
    /* 0x0216 */ u8 pad216[0x2];
} Unkstruct_80170C74; /* size = 0x218 */

typedef struct {
    /* Unkstruct_c0f4146d: P3.40 T3 band rank 232; 124 TNC sites in 124 bodies; struct map 124 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
} Unkstruct_80162870; /* size = 0xc */

typedef struct {
    /* Unkstruct_d1120cee: P3.40 T3 band rank 233; 124 TNC sites in 124 bodies; struct map 124 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x234];
    /* 0x0234 */ s32 unk234;
} Unkstruct_8015E344; /* size = 0x238 */

typedef struct {
    /* Unkstruct_eea43f32: P3.40 T3 band rank 234; 124 TNC sites in 124 bodies; struct map 124 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 pad2[0x2];
} Unkstruct_80162834; /* size = 0x4 */

typedef struct {
    /* Unkstruct_691f6d48: P3.40 T3 band rank 235; 123 TNC sites in 123 bodies; struct map 123 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x30];
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ u8 pad32[0x2];
} Unkstruct_80131B14; /* size = 0x34 */

typedef struct {
    /* Unkstruct_6bc12d82: P3.40 T3 band rank 236; 123 TNC sites in 123 bodies; struct map 123 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4d];
    /* 0x004d */ u8 unk4D;
    /* 0x004e */ u8 pad4E[0x2];
} Unkstruct_80159968; /* size = 0x50 */

typedef struct {
    /* Unkstruct_df18f392: P3.40 T3 band rank 237; 123 TNC sites in 123 bodies; struct map 123 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xbc];
    /* 0x00bc */ s32 unkBC;
} Unkstruct_801312D0_2; /* size = 0xc0 */

typedef struct {
    /* Unkstruct_f3677181: P3.40 T3 band rank 240; 119 TNC sites in 7 bodies; struct map 119 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_8013B274_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_83b2414b: P3.40 T3 band rank 242; 116 TNC sites in 29 bodies; struct map 116 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ u8 padD0[0xc];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8017E0C4; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_9283fa69: P3.40 T3 band rank 243; 114 TNC sites in 6 bodies; struct map 114 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017D77C; /* size = 0x24 */

typedef struct {
    /* Unkstruct_4867f356: P3.40 T3 band rank 244; 113 TNC sites in 113 bodies; struct map 113 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8012BF4C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_13ebb38c: P3.40 T3 band rank 245; 111 TNC sites in 111 bodies; struct map 111 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017CA8C; /* size = 0x18 */

typedef struct {
    /* Unkstruct_265500c8: P3.40 T3 band rank 246; 111 TNC sites in 37 bodies; struct map 111 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x48];
    /* 0x006c */ void * unk6C;
} Unkstruct_8017DF48; /* size = 0x70 */

typedef struct {
    /* Unkstruct_f246bc17: P3.40 T3 band rank 247; 108 TNC sites in 54 bodies; struct map 158 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8015D1B8; /* size = 0x14 */

typedef struct {
    /* Unkstruct_0d90d181: P3.40 T3 band rank 249; 108 TNC sites in 12 bodies; struct map 108 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_80182238; /* size = 0x10 */

typedef struct {
    /* Unkstruct_10e0a2f9: P3.40 T3 band rank 250; 108 TNC sites in 12 bodies; struct map 108 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x6];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
} Unkstruct_8017DA20; /* size = 0x30 */

typedef struct {
    /* Unkstruct_9e08e3ca: P3.40 T3 band rank 251; 108 TNC sites in 12 bodies; struct map 108 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x6];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017E62C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d28ffcc5: P3.40 T3 band rank 252; 108 TNC sites in 12 bodies; struct map 108 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80181ACC; /* size = 0x10 */

typedef struct {
    /* Unkstruct_c25820a5: P3.40 T3 band rank 254; 105 TNC sites in 21 bodies; struct map 105 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017E55C; /* size = 0x74 */

typedef struct {
    /* Unkstruct_f34b9d0a: P3.40 T3 band rank 257; 105 TNC sites in 7 bodies; struct map 105 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ u8 pad2A[0x6];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ void * unk34;
} Unkstruct_8016C998_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_0fe1ce67: P3.40 T3 band rank 258; 100 TNC sites in 25 bodies; struct map 100 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017C5F0_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_80169584: P3.40 T3 band rank 259; 100 TNC sites in 7 bodies; struct map 37 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 unk21;
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ s8 unk24;
    /* 0x0025 */ s8 unk25;
    /* 0x0026 */ s8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
    /* 0x0028 */ s8 unk28;
    /* 0x0029 */ s8 unk29;
    /* 0x002a */ s8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
    /* 0x002c */ u8 unk2C;
    /* 0x002d */ u8 unk2D;
    /* 0x002e */ u8 unk2E;
    /* 0x002f */ u8 pad2F[0x1];
    /* 0x0030 */ s32 unk30;
} Unkstruct_80169408; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8012AAAC: P3.40 T3 band rank 260; 100 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8012AAAC; /* size = 0x24 */

typedef struct {
    /* Unkstruct_1981c749: P3.40 T3 band rank 262; 98 TNC sites in 7 bodies; struct map 98 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016C188_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_7375e8b4: P3.40 T3 band rank 263; 96 TNC sites in 16 bodies; struct map 96 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x74];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_80181B14; /* size = 0x9c */

typedef struct {
    /* Unkstruct_e296aef0: P3.40 T3 band rank 264; 96 TNC sites in 8 bodies; struct map 96 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0x24];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u8 pad64[0x12];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ u8 pad78[0x4];
    /* 0x007c */ u16 unk7C;
    /* 0x007e */ u16 unk7E;
    /* 0x0080 */ u16 unk80;
    /* 0x0082 */ u8 pad82[0x3f];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80181D54; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_59ae0ebd: P3.40 T3 band rank 265; 96 TNC sites in 6 bodies; struct map 96 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ s32 unk2C;
} Unkstruct_8016986C; /* size = 0x30 */

typedef struct {
    /* Unkstruct_bbee8810: P3.40 T3 band rank 266; 96 TNC sites in 3 bodies; struct map 96 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x4];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u8 pad3C[0x2];
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 unk42;
    /* 0x0043 */ u8 pad43[0x7];
    /* 0x004a */ u8 unk4A;
    /* 0x004b */ u8 pad4B[0x1];
} Unkstruct_80176218_6; /* size = 0x4c */

typedef struct {
    /* Unkstruct_f14f8515: P3.40 T3 band rank 268; 93 TNC sites in 93 bodies; struct map 93 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x214];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_80172CA0_2; /* size = 0x218 */

typedef struct {
    /* Unkstruct_08efdfe5: P3.40 T3 band rank 269; 92 TNC sites in 19 bodies; struct map 92 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ void * unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017C120; /* size = 0x20 */

typedef struct {
    /* Unkstruct_1b45a45c: P3.40 T3 band rank 271; 91 TNC sites in 26 bodies; struct map 91 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x6];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017DB6C; /* size = 0x34 */

typedef struct {
    /* Unkstruct_3f8b03c2: P3.40 T3 band rank 272; 91 TNC sites in 7 bodies; struct map 91 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80164930_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_9f5d31c0: P3.40 T3 band rank 273; 90 TNC sites in 15 bodies; struct map 90 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x68];
    /* 0x0078 */ s32 unk78;
} Unkstruct_800CB13C; /* size = 0x7c */

typedef struct {
    /* Unkstruct_6d80f28f: P3.40 T3 band rank 274; 90 TNC sites in 6 bodies; struct map 90 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ s32 unk2C;
} Unkstruct_80168BDC; /* size = 0x30 */

typedef struct {
    /* Unkstruct_a5bbafb7: P3.40 T3 band rank 275; 90 TNC sites in 6 bodies; struct map 90 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x3a];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x16];
    /* 0x0088 */ s16 unk88;
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x2];
} Unkstruct_8017F6D8; /* size = 0x90 */

typedef struct {
    /* Unkstruct_39b92382: P3.40 T3 band rank 278; 88 TNC sites in 88 bodies; struct map 88 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80159698_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_a0778849: P3.40 T3 band rank 279; 87 TNC sites in 29 bodies; struct map 87 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
} Unkstruct_8017E0C4_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_10efdbf5: P3.40 T3 band rank 281; 84 TNC sites in 28 bodies; struct map 84 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x6a];
    /* 0x00dc */ void * unkDC;
} Unkstruct_8017DF78_2; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_c2653ba4: P3.40 T3 band rank 282; 84 TNC sites in 28 bodies; struct map 84 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_801320D8_2; /* size = 0x60 */

typedef struct {
    /* Unkstruct_392ae8b5: P3.40 T3 band rank 283; 84 TNC sites in 21 bodies; struct map 84 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017EC08_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_3baee09b: P3.40 T3 band rank 284; 84 TNC sites in 21 bodies; struct map 84 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017ECD4_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_05f8cfd1: P3.40 T3 band rank 285; 84 TNC sites in 7 bodies; struct map 84 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80134C20_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_c950b0bb: P3.40 T3 band rank 286; 84 TNC sites in 6 bodies; struct map 84 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017EB8C_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_f2b955d7: P3.40 T3 band rank 287; 80 TNC sites in 8 bodies; struct map 80 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0xe];
    /* 0x002a */ s16 unk2A;
} Unkstruct_8016CF04_2; /* size = 0x2c */

typedef struct {
    /* Unkstruct_27c22f85: P3.40 T3 band rank 288; 80 TNC sites in 5 bodies; struct map 80 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x7c];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u8 pad8C[0x72];
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u8 pad100[0x4];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_8017D85C; /* size = 0x10c */

typedef struct {
    /* Unkstruct_98b1b56b: P3.40 T3 band rank 289; 80 TNC sites in 5 bodies; struct map 80 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x7a];
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x70];
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u8 pad100[0x4];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_8017D7A4; /* size = 0x10c */

typedef struct {
    /* Unkstruct_f07b6e23: P3.40 T3 band rank 290; 79 TNC sites in 79 bodies; struct map 79 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8015D738_5; /* size = 0x14 */

typedef struct {
    /* Unkstruct_b4cc0f74: P3.40 T3 band rank 291; 78 TNC sites in 26 bodies; struct map 78 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80169F3C_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_864f58e5: P3.40 T3 band rank 293; 78 TNC sites in 6 bodies; struct map 78 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ s32 unk2C;
} Unkstruct_80169058; /* size = 0x30 */

typedef struct {
    /* Unkstruct_2701e787: P3.40 T3 band rank 294; 78 TNC sites in 2 bodies; struct map 78 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80183E70; /* size = 0x20 */

typedef struct {
    /* Unkstruct_b0aa4651: P3.40 T3 band rank 295; 77 TNC sites in 7 bodies; struct map 77 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0xc];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0xa];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x5];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017E2EC_4; /* size = 0x30 */

typedef struct {
    /* Unkstruct_c7eaf654: P3.40 T3 band rank 296; 77 TNC sites in 7 bodies; struct map 77 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
} Unkstruct_8012C890_4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_c06cf426: P3.40 T3 band rank 297; 75 TNC sites in 25 bodies; struct map 75 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
} Unkstruct_8017E75C; /* size = 0x5c */

typedef struct {
    /* Unkstruct_93fb8c48: P3.40 T3 band rank 298; 75 TNC sites in 3 bodies; struct map 75 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u16 unk1E;
    /* 0x0020 */ u16 unk20;
    /* 0x0022 */ u8 pad22[0x6];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u8 pad32[0xa];
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u16 unk3E;
} Unkstruct_8017D8AC; /* size = 0x40 */

typedef struct {
    /* Unkstruct_1b26d8d0: P3.40 T3 band rank 299; 74 TNC sites in 37 bodies; struct map 74 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0xc];
    /* 0x0020 */ void * unk20;
} Unkstruct_8017DF48_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_b0eb75ed: P3.40 T3 band rank 302; 72 TNC sites in 36 bodies; struct map 72 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x44];
    /* 0x0044 */ u32 unk44;
    /* 0x0048 */ u8 pad48[0x14f];
    /* 0x0197 */ u8 unk197;
} Unkstruct_800CAE34; /* size = 0x198 */

typedef struct {
    /* Unkstruct_3943fde0: P3.40 T3 band rank 303; 72 TNC sites in 24 bodies; struct map 72 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_8017BEF8_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_6465e7d2: P3.40 T3 band rank 304; 72 TNC sites in 24 bodies; struct map 72 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017BEF8_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_dc8adc57: P3.40 T3 band rank 305; 72 TNC sites in 24 bodies; struct map 72 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017C18C; /* size = 0x24 */

typedef struct {
    /* Unkstruct_24f6eb1d: P3.40 T3 band rank 306; 72 TNC sites in 18 bodies; struct map 72 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x6e];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x24];
    /* 0x00f4 */ s16 unkF4;
    /* 0x00f6 */ u8 padF6[0x8];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80182258; /* size = 0x100 */

typedef struct {
    /* Unkstruct_5608c495: P3.40 T3 band rank 307; 72 TNC sites in 18 bodies; struct map 72 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x26];
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x6];
    /* 0x0034 */ s32 unk34;
} Unkstruct_80166994_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_7c36534f: P3.40 T3 band rank 309; 72 TNC sites in 6 bodies; struct map 72 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
} Unkstruct_8017C558; /* size = 0x24 */

typedef struct {
    /* Unkstruct_df0196de: P3.40 T3 band rank 310; 72 TNC sites in 6 bodies; struct map 72 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_801407F4_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_8016C74C: P3.40 T3 band rank 311; 72 TNC sites in 5 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8016C74C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8012D714: P3.40 T3 band rank 312; 72 TNC sites in 1 bodies; struct map 72 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_8012D714; /* size = 0x10 */

typedef struct {
    /* Unkstruct_ed47e86f: P3.40 T3 band rank 315; 70 TNC sites in 14 bodies; struct map 70 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0xf8];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80181474; /* size = 0x104 */

typedef struct {
    /* Unkstruct_455149aa: P3.40 T3 band rank 316; 70 TNC sites in 7 bodies; struct map 70 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_801681FC_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_5ff9ca42: P3.40 T3 band rank 317; 70 TNC sites in 7 bodies; struct map 70 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 pad5[0x7];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x8];
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ u8 pad34[0x20];
    /* 0x0054 */ s32 unk54;
} Unkstruct_80174BF4_2; /* size = 0x58 */

typedef struct {
    /* Unkstruct_6ad37606: P3.40 T3 band rank 318; 70 TNC sites in 7 bodies; struct map 70 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 pad21[0x1];
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x5];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u8 pad2C[0x4];
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801397B0_6; /* size = 0x38 */

typedef struct {
    /* Unkstruct_d5449da2: P3.40 T3 band rank 319; 70 TNC sites in 7 bodies; struct map 70 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xda];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80180A9C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_fc186b3d: P3.40 T3 band rank 320; 70 TNC sites in 7 bodies; struct map 70 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x1e];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ u8 pad94[0x4];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x62];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80142608_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_279958f8: P3.40 T3 band rank 321; 68 TNC sites in 17 bodies; struct map 68 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x16];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8017CE2C; /* size = 0x1c */

typedef struct {
    /* Unkstruct_3e7d704c: P3.40 T3 band rank 322; 68 TNC sites in 17 bodies; struct map 68 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2a];
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017CE14; /* size = 0x34 */

typedef struct {
    /* Unkstruct_80c580cf: P3.40 T3 band rank 323; 68 TNC sites in 17 bodies; struct map 68 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xcc];
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x8];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8017CE2C_2; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_670cb989: P3.40 T3 band rank 324; 68 TNC sites in 4 bodies; struct map 68 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x6];
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u8 pad3E[0x2];
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 pad42[0x8];
    /* 0x004a */ u8 unk4A;
    /* 0x004b */ u8 pad4B[0x1];
} Unkstruct_80176218_7; /* size = 0x4c */

typedef struct {
    /* Unkstruct_801C8B80: P3.40 T3 band rank 329; 65 TNC sites in 3 bodies; struct map 65 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_8017E520; /* size = 0x1c */

typedef struct {
    /* Unkstruct_3fdae64b: P3.40 T3 band rank 330; 64 TNC sites in 16 bodies; struct map 64 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017EA54; /* size = 0x20 */

typedef struct {
    /* Unkstruct_763f320d: P3.40 T3 band rank 331; 64 TNC sites in 4 bodies; struct map 64 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2a];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_80135480_4; /* size = 0x54 */

typedef struct {
    /* Unkstruct_bc33ef75: P3.40 T3 band rank 332; 64 TNC sites in 4 bodies; struct map 64 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2a];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_80135480_5; /* size = 0x54 */

typedef struct {
    /* Unkstruct_80184154: P3.40 T3 band rank 333; 64 TNC sites in 3 bodies; struct map 75 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80135888; /* size = 0x10 */

typedef struct {
    /* Unkstruct_56b7fef3: P3.40 T3 band rank 334; 63 TNC sites in 7 bodies; struct map 63 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x60];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80144880_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_5a291eab: P3.40 T3 band rank 335; 63 TNC sites in 7 bodies; struct map 63 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x6];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x6];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x6];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x12];
    /* 0x0030 */ u32 unk30;
} Unkstruct_8016BFD0_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_a3ed13c3: P3.40 T3 band rank 336; 63 TNC sites in 7 bodies; struct map 63 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80143458_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_c291be73: P3.40 T3 band rank 337; 63 TNC sites in 7 bodies; struct map 63 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x22];
    /* 0x0094 */ s32 unk94;
} Unkstruct_8017EE0C; /* size = 0x98 */

typedef struct {
    /* Unkstruct_cfde75d8: P3.40 T3 band rank 338; 63 TNC sites in 7 bodies; struct map 63 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x10];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x18];
    /* 0x0076 */ u16 unk76;
} Unkstruct_80180068; /* size = 0x78 */

typedef struct {
    /* Unkstruct_f6f81ab3: P3.40 T3 band rank 339; 63 TNC sites in 7 bodies; struct map 63 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_8016D848; /* size = 0x24 */

typedef struct {
    /* Unkstruct_801290DC: P3.40 T3 band rank 340; 61 TNC sites in 28 bodies; struct map 61 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_80015954; /* size = 0x8 */

typedef struct {
    /* Unkstruct_7d6d7355: P3.40 T3 band rank 341; 61 TNC sites in 15 bodies; struct map 61 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x96];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ u8 padD0[0xc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80180450; /* size = 0x100 */

typedef struct {
    /* Unkstruct_bcddb785: P3.40 T3 band rank 342; 61 TNC sites in 6 bodies; struct map 61 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x96];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x2c];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801823B8; /* size = 0x104 */

typedef struct {
    /* Unkstruct_2ad245f8: P3.40 T3 band rank 343; 60 TNC sites in 20 bodies; struct map 60 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801809C4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_19b9ce89: P3.40 T3 band rank 344; 60 TNC sites in 15 bodies; struct map 60 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_801819B4; /* size = 0x20 */

typedef struct {
    /* Unkstruct_90f25f7a: P3.40 T3 band rank 345; 60 TNC sites in 4 bodies; struct map 60 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017F368; /* size = 0x24 */

typedef struct {
    /* Unkstruct_8013C414: P3.40 T3 band rank 346; 60 TNC sites in 2 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_8013C414; /* size = 0x1c */

typedef struct {
    /* Unkstruct_3e8a6c2f: P3.40 T3 band rank 347; 60 TNC sites in 1 bodies; struct map 60 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ void * unk14;
    /* 0x0018 */ u32 unk18;
    /* 0x001c */ u32 unk1C;
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ u32 unk28;
    /* 0x002c */ u32 unk2C;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ u8 pad34[0x3];
    /* 0x0037 */ u8 unk37;
    /* 0x0038 */ u8 unk38;
    /* 0x0039 */ u8 pad39[0x1];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u8 pad3E[0x2];
} Unkstruct_800316F8; /* size = 0x40 */

typedef struct {
    /* Unkstruct_21be1b26: P3.40 T3 band rank 351; 57 TNC sites in 19 bodies; struct map 57 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801807AC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_2a174c8c: P3.40 T3 band rank 352; 57 TNC sites in 19 bodies; struct map 57 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8018090C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_80169228: P3.40 T3 band rank 354; 57 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ u32 unk2C;
} Unkstruct_80169228; /* size = 0x30 */

typedef struct {
    /* Unkstruct_911046c5: P3.40 T3 band rank 355; 56 TNC sites in 14 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017CEBC; /* size = 0x2c */

typedef struct {
    /* Unkstruct_1a19d743: P3.40 T3 band rank 356; 56 TNC sites in 8 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_801824A8; /* size = 0x60 */

typedef struct {
    /* Unkstruct_2aecfdfe: P3.40 T3 band rank 357; 56 TNC sites in 8 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ void * unkD0;
} Unkstruct_80180384; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_7c491eb4: P3.40 T3 band rank 358; 56 TNC sites in 8 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
} Unkstruct_80168828_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_d9f13019: P3.40 T3 band rank 359; 56 TNC sites in 8 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x22];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8018242C; /* size = 0x60 */

typedef struct {
    /* Unkstruct_2f6545d5: P3.40 T3 band rank 360; 56 TNC sites in 7 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017FC34; /* size = 0x24 */

typedef struct {
    /* Unkstruct_aa25e09b: P3.40 T3 band rank 361; 56 TNC sites in 7 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x60];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80144364_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_ee376596: P3.40 T3 band rank 362; 56 TNC sites in 7 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016D848_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_5f3d8197: P3.40 T3 band rank 363; 56 TNC sites in 4 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017CABC; /* size = 0x38 */

typedef struct {
    /* Unkstruct_c4e7e885: P3.40 T3 band rank 364; 56 TNC sites in 4 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x32];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ u8 pad94[0x38];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801818C4; /* size = 0x104 */

typedef struct {
    /* Unkstruct_eb818155: P3.40 T3 band rank 365; 56 TNC sites in 4 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x4];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u8 pad3C[0x2];
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 unk42;
    /* 0x0043 */ u8 pad43[0x7];
    /* 0x004a */ u8 unk4A;
    /* 0x004b */ u8 pad4B[0x1];
} Unkstruct_80176218_8; /* size = 0x4c */

typedef struct {
    /* Unkstruct_f44280b8: P3.40 T3 band rank 366; 56 TNC sites in 4 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DF5C_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_61819d2b: P3.40 T3 band rank 367; 55 TNC sites in 11 bodies; struct map 55 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xd8];
    /* 0x00dc */ void * unkDC;
    /* 0x00e0 */ u8 padE0[0x28];
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_8017D0D0; /* size = 0x10c */

typedef struct {
    /* Unkstruct_c74d0854: P3.40 T3 band rank 368; 55 TNC sites in 7 bodies; struct map 55 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ u8 pad28[0x2];
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u8 pad2C[0x2];
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s32 unk30;
} Unkstruct_801A788C; /* size = 0x34 */

typedef struct {
    /* Unkstruct_a29197c4: P3.40 T3 band rank 369; 55 TNC sites in 5 bodies; struct map 55 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xdc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017ED90; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d4dc76db: P3.40 T3 band rank 370; 55 TNC sites in 5 bodies; struct map 55 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8017E910; /* size = 0x8 */

typedef struct {
    /* Unkstruct_80cf9c96: P3.40 T3 band rank 371; 54 TNC sites in 9 bodies; struct map 54 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x9e];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017D62C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_f5cfde35: P3.40 T3 band rank 372; 54 TNC sites in 9 bodies; struct map 54 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x6];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x2];
    /* 0x001e */ s16 unk1E;
} Unkstruct_8017DE80; /* size = 0x20 */

typedef struct {
    /* Unkstruct_e42c91df: P3.40 T3 band rank 373; 54 TNC sites in 6 bodies; struct map 54 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x6];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u8 pad38[0x14];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_800CAF90; /* size = 0x58 */

typedef struct {
    /* Unkstruct_df84c730: P3.40 T3 band rank 374; 54 TNC sites in 3 bodies; struct map 54 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2a];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x2];
} Unkstruct_8017E1C8; /* size = 0x90 */

typedef struct {
    /* Unkstruct_80131B14: P3.40 T3 band rank 375; 54 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x30];
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ u8 pad32[0x2];
} Unkstruct_80131B14_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8016AE5C: P3.40 T3 band rank 376; 54 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x24];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_8016AE5C; /* size = 0x28 */

typedef struct {
    /* Unkstruct_f913eb84: P3.40 T3 band rank 379; 52 TNC sites in 6 bodies; struct map 52 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x6];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u8 pad38[0x14];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_800CB8A0; /* size = 0x58 */

typedef struct {
    /* Unkstruct_2c747a46: P3.40 T3 band rank 380; 52 TNC sites in 4 bodies; struct map 52 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x60];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x74];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ s16 unkDE;
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x2];
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ s16 unkE6;
    /* 0x00e8 */ s16 unkE8;
    /* 0x00ea */ u8 padEA[0x2];
} Unkstruct_80182550; /* size = 0xec */

typedef struct {
    /* Unkstruct_c1cdd7e1: P3.40 T3 band rank 381; 51 TNC sites in 17 bodies; struct map 51 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2a];
    /* 0x002e */ u16 unk2E;
} Unkstruct_8017D440; /* size = 0x30 */

typedef struct {
    /* Unkstruct_dda4bd99: P3.40 T3 band rank 382; 51 TNC sites in 17 bodies; struct map 51 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8018000C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_bec8b087: P3.40 T3 band rank 383; 51 TNC sites in 4 bodies; struct map 51 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x1a];
    /* 0x0050 */ u16 unk50;
    /* 0x0052 */ s16 unk52;
    /* 0x0054 */ u16 unk54;
    /* 0x0056 */ u8 pad56[0x42];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x36];
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0xe];
    /* 0x00e2 */ s16 unkE2;
    /* 0x00e4 */ u8 padE4[0xe];
    /* 0x00f2 */ s16 unkF2;
    /* 0x00f4 */ u16 unkF4;
    /* 0x00f6 */ u8 padF6[0x14];
    /* 0x010a */ s16 unk10A;
} Unkstruct_80182DCC; /* size = 0x10c */

typedef struct {
    /* Unkstruct_3a99e296: P3.40 T3 band rank 384; 51 TNC sites in 3 bodies; struct map 51 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x6];
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u8 pad3E[0x2];
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 pad42[0x8];
    /* 0x004a */ u8 unk4A;
    /* 0x004b */ u8 pad4B[0x1];
} Unkstruct_80176218_9; /* size = 0x4c */

typedef struct {
    /* Unkstruct_27681926: P3.40 T3 band rank 386; 51 TNC sites in 1 bodies; struct map 51 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x44];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x6a];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ s16 unkDE;
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x2];
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ s16 unkE6;
    /* 0x00e8 */ s16 unkE8;
    /* 0x00ea */ u8 padEA[0x2];
    /* 0x00ec */ s16 unkEC;
    /* 0x00ee */ s16 unkEE;
    /* 0x00f0 */ s16 unkF0;
    /* 0x00f2 */ u8 padF2[0x2];
    /* 0x00f4 */ s16 unkF4;
    /* 0x00f6 */ s16 unkF6;
    /* 0x00f8 */ s16 unkF8;
    /* 0x00fa */ u8 padFA[0x2];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_80183560; /* size = 0x10c */

typedef struct {
    /* Unkstruct_e35f0318: P3.40 T3 band rank 387; 50 TNC sites in 10 bodies; struct map 50 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xe4];
    /* 0x00e8 */ s32 unkE8;
} Unkstruct_8017E220; /* size = 0xec */

typedef struct {
    /* Unkstruct_69c5f8fc: P3.40 T3 band rank 388; 50 TNC sites in 5 bodies; struct map 50 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80184178; /* size = 0x24 */

typedef struct {
    /* Unkstruct_273cb953: P3.40 T3 band rank 390; 50 TNC sites in 1 bodies; struct map 50 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x8];
    /* 0x0058 */ s32 unk58;
} Unkstruct_800CB4A4; /* size = 0x5c */

typedef struct {
    /* Unkstruct_8c9be6f1: P3.40 T3 band rank 391; 49 TNC sites in 7 bodies; struct map 49 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_8017FC34_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_9ef73b29: P3.40 T3 band rank 392; 49 TNC sites in 7 bodies; struct map 49 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_8016D984; /* size = 0x20 */

typedef struct {
    /* Unkstruct_bea1441f: P3.40 T3 band rank 393; 49 TNC sites in 7 bodies; struct map 49 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_801343C4_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_d6aa5eeb: P3.40 T3 band rank 394; 49 TNC sites in 7 bodies; struct map 49 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016C2C4_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_dd157155: P3.40 T3 band rank 395; 49 TNC sites in 7 bodies; struct map 49 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xa];
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_80168430_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_7cefcdf4: P3.40 T3 band rank 400; 48 TNC sites in 16 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xf8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80181784; /* size = 0x100 */

typedef struct {
    /* Unkstruct_82412cce: P3.40 T3 band rank 401; 48 TNC sites in 16 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0xa];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x18];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80181B14_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_4f4360ab: P3.40 T3 band rank 402; 48 TNC sites in 12 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017DA20_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_f5670c09: P3.40 T3 band rank 403; 48 TNC sites in 12 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x94];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x64];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017E6EC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_0882b0df: P3.40 T3 band rank 404; 48 TNC sites in 8 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 pad3[0x1];
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 pad7[0x1];
} Unkstruct_8017DF44; /* size = 0x8 */

typedef struct {
    /* Unkstruct_0b5a176e: P3.40 T3 band rank 405; 48 TNC sites in 8 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xda];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801824A8_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_1cc25077: P3.40 T3 band rank 406; 48 TNC sites in 8 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8017C2B0; /* size = 0x60 */

typedef struct {
    /* Unkstruct_24f8758c: P3.40 T3 band rank 407; 48 TNC sites in 6 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xda];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_801809E8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_35c0172b: P3.40 T3 band rank 408; 48 TNC sites in 6 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017D9CC; /* size = 0x38 */

typedef struct {
    /* Unkstruct_481facb1: P3.40 T3 band rank 409; 48 TNC sites in 6 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0xa];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0xb];
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u8 pad28[0x4];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017F4F0; /* size = 0x30 */

typedef struct {
    /* Unkstruct_801647A4: P3.40 T3 band rank 411; 48 TNC sites in 4 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2c];
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0xc];
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u16 unk62;
} Unkstruct_801647A4_3; /* size = 0x64 */

typedef struct {
    /* Unkstruct_802381a4: P3.40 T3 band rank 412; 48 TNC sites in 4 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_801407F4_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_cf435a0d: P3.40 T3 band rank 413; 48 TNC sites in 3 bodies; struct map 48 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x7];
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
} Unkstruct_80175DA8_3; /* size = 0x18 */

typedef struct {
    /* Unkstruct_9f24dca3: P3.40 T3 band rank 416; 47 TNC sites in 1 bodies; struct map 47 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ s32 unk2C;
} Unkstruct_80035270; /* size = 0x30 */

typedef struct {
    /* Unkstruct_8016A08C: P3.40 T3 band rank 417; 46 TNC sites in 3 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8016A08C; /* size = 0x24 */

typedef struct {
    /* Unkstruct_801A9DA8: P3.40 T3 band rank 420; 46 TNC sites in 2 bodies; struct map 46 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x22];
    /* 0x003c */ s16 unk3C;
    /* 0x003e */ s16 unk3E;
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 pad42[0x2];
} Unkstruct_80182564; /* size = 0x44 */

typedef struct {
    /* Unkstruct_114c89fb: P3.40 T3 band rank 421; 45 TNC sites in 45 bodies; struct map 45 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8015D738_6; /* size = 0x14 */

typedef struct {
    /* Unkstruct_b8cbc3e7: P3.40 T3 band rank 422; 45 TNC sites in 15 bodies; struct map 45 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_800CB13C_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_12c13978: P3.40 T3 band rank 423; 45 TNC sites in 9 bodies; struct map 45 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x86];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x54];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_8017E470; /* size = 0x108 */

typedef struct {
    /* Unkstruct_38a569fe: P3.40 T3 band rank 424; 45 TNC sites in 9 bodies; struct map 45 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017E470_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_6c0d6e07: P3.40 T3 band rank 425; 45 TNC sites in 9 bodies; struct map 45 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x18];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801832BC; /* size = 0x30 */

typedef struct {
    /* Unkstruct_a6da5fb5: P3.40 T3 band rank 427; 45 TNC sites in 9 bodies; struct map 45 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
} Unkstruct_8017DE80_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_f2b0d39e: P3.40 T3 band rank 428; 45 TNC sites in 9 bodies; struct map 45 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
} Unkstruct_8017F5B4; /* size = 0xc */

typedef struct {
    /* Unkstruct_20fcc757: P3.40 T3 band rank 431; 44 TNC sites in 11 bodies; struct map 44 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801E26BC; /* size = 0x2c */

typedef struct {
    /* Unkstruct_86ba6f11: P3.40 T3 band rank 432; 44 TNC sites in 4 bodies; struct map 44 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2e];
    /* 0x0052 */ s16 unk52;
    /* 0x0054 */ u8 pad54[0x8];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x4];
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u8 pad64[0x78];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8017E800; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_f998acc8: P3.40 T3 band rank 433; 44 TNC sites in 4 bodies; struct map 44 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x6];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x14];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017E9D8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8d11a07a: P3.40 T3 band rank 436; 44 TNC sites in 2 bodies; struct map 44 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xf];
    /* 0x000f */ u8 unkF;
    /* 0x0010 */ u8 unk10;
    /* 0x0011 */ u8 unk11;
    /* 0x0012 */ u8 unk12;
    /* 0x0013 */ u8 unk13;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 unk18;
    /* 0x0019 */ u8 unk19;
    /* 0x001a */ u8 unk1A;
    /* 0x001b */ u8 pad1B[0x1];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 unk21;
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ s16 unk26;
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 unk29;
    /* 0x002a */ u8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
} Unkstruct_8017DE08; /* size = 0x30 */

typedef struct {
    /* Unkstruct_c7bd3214: P3.40 T3 band rank 437; 44 TNC sites in 2 bodies; struct map 44 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u8 pad38[0x14];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_8016A8FC; /* size = 0x58 */

typedef struct {
    /* Unkstruct_801696D8: P3.40 T3 band rank 444; 43 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_801696D8; /* size = 0x4 */

typedef struct {
    /* Unkstruct_80169A4C: P3.40 T3 band rank 445; 43 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_80169A4C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_8017D0BC: P3.40 T3 band rank 446; 43 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8017D0BC; /* size = 0x8 */

typedef struct {
    /* Unkstruct_143528d1: P3.40 T3 band rank 450; 42 TNC sites in 7 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
} Unkstruct_8015094C_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_1b0c625f: P3.40 T3 band rank 451; 42 TNC sites in 7 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x72];
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x1c];
    /* 0x0090 */ void * unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x2];
    /* 0x009a */ s16 unk9A;
    /* 0x009c */ s32 unk9C;
} Unkstruct_8012ACA0_2; /* size = 0xa0 */

typedef struct {
    /* Unkstruct_2840bf59: P3.40 T3 band rank 452; 42 TNC sites in 7 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x12];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x52];
    /* 0x0080 */ void * unk80;
} Unkstruct_801647A4_4; /* size = 0x84 */

typedef struct {
    /* Unkstruct_35d9e411: P3.40 T3 band rank 453; 42 TNC sites in 7 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 pad3[0x1];
} Unkstruct_8016EB3C_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_4a0b4073: P3.40 T3 band rank 454; 42 TNC sites in 7 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80180C68; /* size = 0x8 */

typedef struct {
    /* Unkstruct_c0de1569: P3.40 T3 band rank 455; 42 TNC sites in 7 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x68];
    /* 0x0078 */ s32 unk78;
} Unkstruct_8015D5E8_2; /* size = 0x7c */

typedef struct {
    /* Unkstruct_d64bf38e: P3.40 T3 band rank 456; 42 TNC sites in 7 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 pad24[0x3];
    /* 0x0027 */ u8 unk27;
} Unkstruct_80143458_4; /* size = 0x28 */

typedef struct {
    /* Unkstruct_ec5ba1f9: P3.40 T3 band rank 457; 42 TNC sites in 7 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x6];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x4];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8012C890_5; /* size = 0x14 */

typedef struct {
    /* Unkstruct_34c1dcce: P3.40 T3 band rank 458; 42 TNC sites in 6 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_80181058; /* size = 0x74 */

typedef struct {
    /* Unkstruct_7e1ff0ab: P3.40 T3 band rank 459; 42 TNC sites in 3 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x6];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x12];
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ u8 pad34[0xc];
    /* 0x0040 */ s32 unk40;
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s16 unk48;
    /* 0x004a */ u16 unk4A;
    /* 0x004c */ u8 pad4C[0x2];
    /* 0x004e */ u8 unk4E;
    /* 0x004f */ u8 pad4F[0x523];
    /* 0x0572 */ s16 unk572;
} Unkstruct_80030CA4; /* size = 0x574 */

typedef struct {
    /* Unkstruct_a8fa1cfd: P3.40 T3 band rank 461; 42 TNC sites in 3 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x4];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u8 pad3C[0x2];
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 unk42;
    /* 0x0043 */ u8 pad43[0x7];
    /* 0x004a */ u8 unk4A;
    /* 0x004b */ u8 pad4B[0x1];
} Unkstruct_80176218_10; /* size = 0x4c */

typedef struct {
    /* Unkstruct_1859e627: P3.40 T3 band rank 466; 42 TNC sites in 1 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x3];
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x38];
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u8 padB8[0x4];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 unkC0;
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
    /* 0x00c4 */ s32 unkC4;
    /* 0x00c8 */ u8 padC8[0x4];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ s32 unkD8;
    /* 0x00dc */ u8 padDC[0x22];
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u8 pad100[0x6];
    /* 0x0106 */ u16 unk106;
} Unkstruct_801825A4; /* size = 0x108 */

typedef struct {
    /* Unkstruct_b0e6aaa8: P3.40 T3 band rank 470; 42 TNC sites in 1 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x3];
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x38];
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u8 padB8[0x4];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 unkC0;
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
    /* 0x00c4 */ s32 unkC4;
    /* 0x00c8 */ u8 padC8[0x4];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ s32 unkD8;
    /* 0x00dc */ u8 padDC[0x22];
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u8 pad100[0x6];
    /* 0x0106 */ u16 unk106;
} Unkstruct_801800CC; /* size = 0x108 */

typedef struct {
    /* Unkstruct_295eefc9: P3.40 T3 band rank 474; 40 TNC sites in 8 bodies; struct map 40 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x16];
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017D030; /* size = 0x38 */

typedef struct {
    /* Unkstruct_60978331: P3.40 T3 band rank 475; 40 TNC sites in 8 bodies; struct map 40 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x16];
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017C218; /* size = 0x38 */

typedef struct {
    /* Unkstruct_89230a8b: P3.40 T3 band rank 476; 40 TNC sites in 8 bodies; struct map 40 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016BBE0_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_e64a17bb: P3.40 T3 band rank 477; 40 TNC sites in 8 bodies; struct map 40 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0xc];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_8017E270; /* size = 0x1c */

typedef struct {
    /* Unkstruct_5bc690ce: P3.40 T3 band rank 478; 40 TNC sites in 5 bodies; struct map 40 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
} Unkstruct_80184178_2; /* size = 0x28 */

typedef struct {
    /* Unkstruct_7d3d5730: P3.40 T3 band rank 479; 40 TNC sites in 5 bodies; struct map 40 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x52];
    /* 0x0080 */ void * unk80;
} Unkstruct_8017D364; /* size = 0x84 */

typedef struct {
    /* Unkstruct_bb893dc2: P3.40 T3 band rank 480; 40 TNC sites in 5 bodies; struct map 40 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_80180774; /* size = 0x1c */

typedef struct {
    /* Unkstruct_e18858bb: P3.40 T3 band rank 492; 39 TNC sites in 13 bodies; struct map 39 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 pad3[0x1];
} Unkstruct_80181FAC; /* size = 0x4 */

typedef struct {
    /* Unkstruct_8011DB30: P3.40 T3 band rank 493; 39 TNC sites in 6 bodies; struct map 39 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x6];
    /* 0x0034 */ s32 unk34;
} Unkstruct_80129010; /* size = 0x38 */

typedef struct {
    /* Unkstruct_6561942c: P3.40 T3 band rank 494; 39 TNC sites in 2 bodies; struct map 39 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u16 unk36;
    /* 0x0038 */ u16 unk38;
    /* 0x003a */ u8 pad3A[0x6];
    /* 0x0040 */ void * unk40;
    /* 0x0044 */ u8 pad44[0xc];
    /* 0x0050 */ s16 unk50;
    /* 0x0052 */ u8 pad52[0x2];
} Unkstruct_801848A4; /* size = 0x54 */

typedef struct {
    /* Unkstruct_3017c2ce: P3.40 T3 band rank 495; 39 TNC sites in 1 bodies; struct map 39 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x30];
    /* 0x0054 */ u16 unk54;
    /* 0x0056 */ u8 pad56[0xe];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x4];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_80180CD0; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_80162B1C: P3.40 T3 band rank 497; 39 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_80162B1C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_8016C374: P3.40 T3 band rank 498; 39 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 pad3[0x1];
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 pad7[0x1];
} Unkstruct_8016C374; /* size = 0x8 */

typedef struct {
    /* Unkstruct_fa6a240a: P3.40 T3 band rank 499; 39 TNC sites in 1 bodies; struct map 39 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x30];
    /* 0x0054 */ u16 unk54;
    /* 0x0056 */ u8 pad56[0xe];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x4];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_801831A8; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_402d5bed: P3.40 T3 band rank 500; 38 TNC sites in 2 bodies; struct map 38 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x1b];
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u8 pad28[0x4];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017C004; /* size = 0x30 */

typedef struct {
    /* Unkstruct_418d842f: P3.40 T3 band rank 504; 38 TNC sites in 1 bodies; struct map 38 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 unk21;
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 unk29;
    /* 0x002a */ u8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
    /* 0x002c */ u8 unk2C;
    /* 0x002d */ u8 unk2D;
    /* 0x002e */ u8 unk2E;
    /* 0x002f */ u8 pad2F[0x1];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ u8 pad34[0x18];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
    /* 0x0058 */ s16 unk58;
    /* 0x005a */ s16 unk5A;
} Unkstruct_800CBB38; /* size = 0x5c */

typedef struct {
    /* Unkstruct_8016E460: P3.40 T3 band rank 506; 38 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_8016E460; /* size = 0x4 */

typedef struct {
    /* Unkstruct_0cb871b6: P3.40 T3 band rank 508; 37 TNC sites in 37 bodies; struct map 37 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017E150; /* size = 0x100 */

typedef struct {
    /* Unkstruct_173085c7: P3.40 T3 band rank 509; 37 TNC sites in 37 bodies; struct map 37 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017E160; /* size = 0x100 */

typedef struct {
    /* Unkstruct_9476510e: P3.40 T3 band rank 510; 37 TNC sites in 37 bodies; struct map 37 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6c];
    /* 0x006c */ s32 unk6C;
} Unkstruct_8017E160_2; /* size = 0x70 */

typedef struct {
    /* Unkstruct_c349a47d: P3.40 T3 band rank 511; 37 TNC sites in 37 bodies; struct map 37 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017DF48_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_eeb6e459: P3.40 T3 band rank 512; 37 TNC sites in 37 bodies; struct map 37 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6c];
    /* 0x006c */ s32 unk6C;
} Unkstruct_8017E150_2; /* size = 0x70 */

typedef struct {
    /* Unkstruct_f1ccc010: P3.40 T3 band rank 519; 37 TNC sites in 1 bodies; struct map 37 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ u8 padDE[0x2];
} Unkstruct_801809E4; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_d86d2aca: P3.40 T3 band rank 520; 36 TNC sites in 36 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd0];
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0xc];
    /* 0x00e0 */ s32 unkE0;
} Unkstruct_80180CCC; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_873f5fac: P3.40 T3 band rank 521; 36 TNC sites in 18 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017DE04; /* size = 0x100 */

typedef struct {
    /* Unkstruct_11ee7826: P3.40 T3 band rank 522; 36 TNC sites in 12 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_8017E394; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_6b078fb7: P3.40 T3 band rank 523; 36 TNC sites in 12 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x7];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x2];
} Unkstruct_80181A80; /* size = 0xc */

typedef struct {
    /* Unkstruct_7b1fbef7: P3.40 T3 band rank 524; 36 TNC sites in 12 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801E2D84; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_9fca4706: P3.40 T3 band rank 525; 36 TNC sites in 12 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
} Unkstruct_8018152C; /* size = 0xc */

typedef struct {
    /* Unkstruct_e4ecef8e: P3.40 T3 band rank 526; 36 TNC sites in 12 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8018085C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_6c7ce87a: P3.40 T3 band rank 527; 36 TNC sites in 9 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0xd4];
    /* 0x010a */ s16 unk10A;
} Unkstruct_80181FD8; /* size = 0x10c */

typedef struct {
    /* Unkstruct_74ab7b09: P3.40 T3 band rank 529; 36 TNC sites in 6 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x8];
    /* 0x0058 */ s32 unk58;
} Unkstruct_8017D598; /* size = 0x5c */

typedef struct {
    /* Unkstruct_f55bba44: P3.40 T3 band rank 530; 36 TNC sites in 6 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80181720_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_fbdfa700: P3.40 T3 band rank 531; 36 TNC sites in 6 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ s32 unk10;
} Unkstruct_801810CC; /* size = 0x14 */

typedef struct {
    /* Unkstruct_174b5bb5: P3.40 T3 band rank 532; 36 TNC sites in 4 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x7e];
    /* 0x00dc */ void * unkDC;
} Unkstruct_8017D994; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_58159bec: P3.40 T3 band rank 533; 36 TNC sites in 4 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x54];
    /* 0x0078 */ s32 unk78;
} Unkstruct_8015D738_7; /* size = 0x7c */

typedef struct {
    /* Unkstruct_84b84ec0: P3.40 T3 band rank 534; 36 TNC sites in 4 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ s32 unkE4;
    /* 0x00e8 */ u8 padE8[0x16];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017D940; /* size = 0x104 */

typedef struct {
    /* Unkstruct_8b67203e: P3.40 T3 band rank 535; 36 TNC sites in 4 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xa];
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x6];
    /* 0x0034 */ void * unk34;
} Unkstruct_8017E7E8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2c8cbc07: P3.40 T3 band rank 536; 36 TNC sites in 3 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ u8 pad28[0x4];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u8 pad38[0x4];
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 pad42[0x2];
} Unkstruct_8017FED8; /* size = 0x44 */

typedef struct {
    /* Unkstruct_8014D0A4: P3.40 T3 band rank 537; 36 TNC sites in 3 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x8];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x16];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ u8 pad76[0x2];
} Unkstruct_8014D0A4; /* size = 0x78 */

typedef struct {
    /* Unkstruct_4f43e65d: P3.40 T3 band rank 538; 36 TNC sites in 2 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u16 unk1E;
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u16 unk26;
} Unkstruct_80182E70; /* size = 0x28 */

typedef struct {
    /* Unkstruct_55091836: P3.40 T3 band rank 539; 36 TNC sites in 2 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2a];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x2];
} Unkstruct_8017E30C; /* size = 0x90 */

typedef struct {
    /* Unkstruct_8014E98C: P3.40 T3 band rank 540; 36 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8014E98C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_9bbcaf82: P3.40 T3 band rank 542; 36 TNC sites in 1 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017F328; /* size = 0x4 */

typedef struct {
    /* Unkstruct_0ee56838: P3.40 T3 band rank 544; 35 TNC sites in 14 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2c];
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0xc];
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u16 unk62;
} Unkstruct_801647A4_5; /* size = 0x64 */

typedef struct {
    /* Unkstruct_cccfcd0c: P3.40 T3 band rank 545; 35 TNC sites in 14 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
} Unkstruct_801805F8; /* size = 0x20 */

typedef struct {
    /* Unkstruct_87aa7990: P3.40 T3 band rank 546; 35 TNC sites in 10 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x18];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017C154; /* size = 0x34 */

typedef struct {
    /* Unkstruct_0c6e7dca: P3.40 T3 band rank 547; 35 TNC sites in 7 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ u8 pad30[0x30];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ s16 unk62;
    /* 0x0064 */ u8 pad64[0x2];
    /* 0x0066 */ s16 unk66;
} Unkstruct_80164EE0_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_3001ac7d: P3.40 T3 band rank 548; 35 TNC sites in 7 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8016DA7C_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_32a2c356: P3.40 T3 band rank 549; 35 TNC sites in 7 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017BFEC; /* size = 0x14 */

typedef struct {
    /* Unkstruct_4e0e6475: P3.40 T3 band rank 550; 35 TNC sites in 7 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x2];
    /* 0x001e */ s16 unk1E;
} Unkstruct_8016C188_4; /* size = 0x20 */

typedef struct {
    /* Unkstruct_b25210d1: P3.40 T3 band rank 551; 35 TNC sites in 7 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_8016BD78_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_b338c0f0: P3.40 T3 band rank 552; 35 TNC sites in 7 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x174];
    /* 0x0198 */ s32 unk198;
} Unkstruct_80158FA4_3; /* size = 0x19c */

typedef struct {
    /* Unkstruct_c7d2756c: P3.40 T3 band rank 553; 35 TNC sites in 7 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x1f6];
    /* 0x01f8 */ s32 unk1F8;
} Unkstruct_801654A8_2; /* size = 0x1fc */

typedef struct {
    /* Unkstruct_cc71edc1: P3.40 T3 band rank 554; 35 TNC sites in 7 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xda];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017E7B4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_f2c9d3fd: P3.40 T3 band rank 555; 35 TNC sites in 7 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x5a];
    /* 0x0076 */ s16 unk76;
} Unkstruct_801431E8_3; /* size = 0x78 */

typedef struct {
    /* Unkstruct_3c3a6f6b: P3.40 T3 band rank 556; 35 TNC sites in 5 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x40];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u8 pad5C[0x38];
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x6a];
    /* 0x0102 */ u16 unk102;
} Unkstruct_801816E8; /* size = 0x104 */

typedef struct {
    /* Unkstruct_d51d00ac: P3.40 T3 band rank 557; 35 TNC sites in 5 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801819B4_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_e3957e19: P3.40 T3 band rank 558; 35 TNC sites in 5 bodies; struct map 35 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xa];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x2c];
    /* 0x0048 */ s32 unk48;
} Unkstruct_8017DCD0_2; /* size = 0x4c */

typedef struct {
    /* Unkstruct_de9440dd: P3.40 T3 band rank 560; 34 TNC sites in 17 bodies; struct map 34 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xd8];
    /* 0x00dc */ void * unkDC;
} Unkstruct_8017CE98; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_8015D57C: P3.40 T3 band rank 561; 34 TNC sites in 5 bodies; struct map 34 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x54];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x80];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8015D57C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_afac3864: P3.40 T3 band rank 562; 34 TNC sites in 2 bodies; struct map 34 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x44];
    /* 0x00ac */ u16 unkAC;
    /* 0x00ae */ u8 padAE[0x4e];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8018CF48; /* size = 0x100 */

typedef struct {
    /* Unkstruct_e1cfd5b7: P3.40 T3 band rank 563; 34 TNC sites in 2 bodies; struct map 34 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x40];
    /* 0x004c */ u16 unk4C;
    /* 0x004e */ u16 unk4E;
} Unkstruct_800226C0; /* size = 0x50 */

typedef struct {
    /* Unkstruct_529c856c: P3.40 T3 band rank 565; 34 TNC sites in 1 bodies; struct map 34 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x3c];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u8 pad62[0x14];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ u8 pad78[0x54];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ void * unkD4;
    /* 0x00d8 */ u8 padD8[0x4];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ s16 unkDE;
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x6];
    /* 0x00e8 */ u32 unkE8;
} Unkstruct_80183218; /* size = 0xec */

typedef struct {
    /* Unkstruct_8013A530: P3.40 T3 band rank 566; 34 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 pad21[0x1];
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ u16 unk24;
    /* 0x0026 */ u16 unk26;
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u16 unk36;
} Unkstruct_8013A530; /* size = 0x38 */

typedef struct {
    /* Unkstruct_b41a4dad: P3.40 T3 band rank 567; 34 TNC sites in 1 bodies; struct map 34 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017E880; /* size = 0x14 */

typedef struct {
    /* Unkstruct_cd745fee: P3.40 T3 band rank 568; 34 TNC sites in 1 bodies; struct map 34 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x10];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x36];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x4];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0xf];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x2];
} Unkstruct_8017DB30; /* size = 0x88 */

typedef struct {
    /* Unkstruct_673daca6: P3.40 T3 band rank 569; 33 TNC sites in 11 bodies; struct map 33 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017CE7C; /* size = 0x2c */

typedef struct {
    /* Unkstruct_b1c8de1f: P3.40 T3 band rank 570; 33 TNC sites in 4 bodies; struct map 33 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u16 unk1E;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8001DA34; /* size = 0x38 */

typedef struct {
    /* Unkstruct_cf488289: P3.40 T3 band rank 571; 33 TNC sites in 3 bodies; struct map 33 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_80184E5C; /* size = 0x28 */

typedef struct {
    /* Unkstruct_622bda7b: P3.40 T3 band rank 574; 32 TNC sites in 16 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5e];
    /* 0x005e */ u8 unk5E;
    /* 0x005f */ u8 pad5F[0xa1];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801812E8; /* size = 0x104 */

typedef struct {
    /* Unkstruct_6d21f423: P3.40 T3 band rank 575; 32 TNC sites in 8 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa];
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ u32 unk30;
} Unkstruct_8017C100; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8d69bbd5: P3.40 T3 band rank 576; 32 TNC sites in 8 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_8017E94C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_f529730a: P3.40 T3 band rank 577; 32 TNC sites in 8 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xa];
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017E15C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_05ff3a03: P3.40 T3 band rank 578; 32 TNC sites in 4 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017D414; /* size = 0x20 */

typedef struct {
    /* Unkstruct_1cf8bb6d: P3.40 T3 band rank 579; 32 TNC sites in 4 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8018342C; /* size = 0x30 */

typedef struct {
    /* Unkstruct_603968bf: P3.40 T3 band rank 580; 32 TNC sites in 4 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x16];
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ s32 unk34;
} Unkstruct_80180F98; /* size = 0x38 */

typedef struct {
    /* Unkstruct_62a84f20: P3.40 T3 band rank 581; 32 TNC sites in 4 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
} Unkstruct_8017F200; /* size = 0x28 */

typedef struct {
    /* Unkstruct_814e6287: P3.40 T3 band rank 583; 32 TNC sites in 4 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2c];
    /* 0x0050 */ u16 unk50;
    /* 0x0052 */ u16 unk52;
    /* 0x0054 */ u16 unk54;
    /* 0x0056 */ u8 pad56[0x76];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ s8 unkFC;
    /* 0x00fd */ u8 padFD[0x3];
} Unkstruct_8018C3C4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_e773df21: P3.40 T3 band rank 584; 32 TNC sites in 4 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2c];
    /* 0x0050 */ u16 unk50;
    /* 0x0052 */ u16 unk52;
    /* 0x0054 */ u16 unk54;
    /* 0x0056 */ u8 pad56[0x76];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ s8 unkFC;
    /* 0x00fd */ u8 padFD[0x3];
} Unkstruct_8018620C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_feaec7f3: P3.40 T3 band rank 585; 32 TNC sites in 4 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x10];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ void * unk34;
} Unkstruct_8017E23C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8013AD38: P3.40 T3 band rank 586; 32 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
} Unkstruct_8013AD38_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_36be0ff5: P3.40 T3 band rank 587; 32 TNC sites in 1 bodies; struct map 32 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x4];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u8 pad3C[0x2];
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 unk42;
    /* 0x0043 */ u8 pad43[0x7];
    /* 0x004a */ u8 unk4A;
    /* 0x004b */ u8 pad4B[0x1];
} Unkstruct_80176218_11; /* size = 0x4c */

typedef struct {
    /* Unkstruct_80166994: P3.40 T3 band rank 588; 31 TNC sites in 6 bodies; struct map 31 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ u8 pad32[0x2];
    /* 0x0034 */ s32 unk34;
} Unkstruct_80166994_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2e1bf188: P3.40 T3 band rank 590; 31 TNC sites in 3 bodies; struct map 31 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ u8 pad60[0x1c];
    /* 0x007c */ u16 unk7C;
    /* 0x007e */ u16 unk7E;
    /* 0x0080 */ u16 unk80;
    /* 0x0082 */ u8 pad82[0x5e];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x1a];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_801819F4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_5e11ac10: P3.40 T3 band rank 592; 31 TNC sites in 1 bodies; struct map 31 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x18];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x8];
    /* 0x010a */ s16 unk10A;
} Unkstruct_80180D4C; /* size = 0x10c */

typedef struct {
    /* Unkstruct_8013AF20: P3.40 T3 band rank 593; 31 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_8013AF20; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8016AFB0: P3.40 T3 band rank 594; 31 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x1c];
    /* 0x0024 */ s8 unk24;
    /* 0x0025 */ s8 unk25;
    /* 0x0026 */ s8 unk26;
    /* 0x0027 */ s8 unk27;
} Unkstruct_8016AFB0; /* size = 0x28 */

typedef struct {
    /* Unkstruct_8017742C: P3.40 T3 band rank 595; 31 TNC sites in 1 bodies; struct map 31 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_8017742C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_dcdc4c4a: P3.40 T3 band rank 596; 31 TNC sites in 1 bodies; struct map 31 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 unk5E;
    /* 0x005f */ u8 pad5F[0x1];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u8 pad62[0x2];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0xe];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u16 unk7C;
    /* 0x007e */ u16 unk7E;
    /* 0x0080 */ u16 unk80;
    /* 0x0082 */ u16 unk82;
    /* 0x0084 */ u8 pad84[0x3d];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 padC3[0x5];
    /* 0x00c8 */ u8 unkC8;
    /* 0x00c9 */ u8 unkC9;
    /* 0x00ca */ u8 padCA[0x2];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ s32 unkD4;
} Unkstruct_8018E188; /* size = 0xd8 */

typedef struct {
    /* Unkstruct_eb128ef9: P3.40 T3 band rank 597; 31 TNC sites in 1 bodies; struct map 31 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017F950; /* size = 0x4 */

typedef struct {
    /* Unkstruct_734426a1: P3.40 T3 band rank 598; 30 TNC sites in 11 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017DC60; /* size = 0x24 */

typedef struct {
    /* Unkstruct_185a5cd8: P3.40 T3 band rank 599; 30 TNC sites in 6 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x24];
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ u8 pad28[0x4];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017FE60; /* size = 0x34 */

typedef struct {
    /* Unkstruct_39065d2b: P3.40 T3 band rank 600; 30 TNC sites in 6 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80181720_3; /* size = 0x18 */

typedef struct {
    /* Unkstruct_430245e5: P3.40 T3 band rank 601; 30 TNC sites in 6 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x24];
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ u8 pad28[0x4];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017FE60_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_7fad9e88: P3.40 T3 band rank 602; 30 TNC sites in 6 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801596F0_2; /* size = 0x2c */

typedef struct {
    /* Unkstruct_96b0f897: P3.40 T3 band rank 603; 30 TNC sites in 6 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ s8 unk24;
    /* 0x0025 */ s8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_8017C558_2; /* size = 0x28 */

typedef struct {
    /* Unkstruct_fdfd2eba: P3.40 T3 band rank 604; 30 TNC sites in 6 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80180A5C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_801B7930: P3.40 T3 band rank 605; 30 TNC sites in 5 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2c];
    /* 0x0050 */ s16 unk50;
    /* 0x0052 */ s16 unk52;
    /* 0x0054 */ s16 unk54;
    /* 0x0056 */ u8 pad56[0x2];
} Unkstruct_8017CA80; /* size = 0x58 */

typedef struct {
    /* Unkstruct_a41467ef: P3.40 T3 band rank 606; 30 TNC sites in 5 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017FB10; /* size = 0x38 */

typedef struct {
    /* Unkstruct_9b7683f5: P3.40 T3 band rank 608; 30 TNC sites in 3 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DC20_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_a932ec9a: P3.40 T3 band rank 609; 30 TNC sites in 3 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x10];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x6c];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x4];
    /* 0x00d8 */ void * unkD8;
    /* 0x00dc */ void * unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u8 pad100[0x6];
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ s16 unk10A;
} Unkstruct_8017BEBC_2; /* size = 0x10c */

typedef struct {
    /* Unkstruct_dfb4dd0b: P3.40 T3 band rank 610; 30 TNC sites in 3 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DC20_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_fb720423: P3.40 T3 band rank 611; 30 TNC sites in 3 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x96];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x2c];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_801844AC; /* size = 0x108 */

typedef struct {
    /* Unkstruct_fc0c80b5: P3.40 T3 band rank 612; 30 TNC sites in 3 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80136824_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_0c4497da: P3.40 T3 band rank 613; 30 TNC sites in 2 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017C004_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_29aa6cb3: P3.40 T3 band rank 614; 30 TNC sites in 1 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ u16 unkCC;
    /* 0x00ce */ u16 unkCE;
    /* 0x00d0 */ u16 unkD0;
    /* 0x00d2 */ u8 padD2[0x2];
    /* 0x00d4 */ u16 unkD4;
    /* 0x00d6 */ u16 unkD6;
    /* 0x00d8 */ u16 unkD8;
    /* 0x00da */ u8 padDA[0x12];
    /* 0x00ec */ u8 unkEC;
    /* 0x00ed */ u8 unkED;
    /* 0x00ee */ u8 unkEE;
    /* 0x00ef */ u8 padEF[0x1];
    /* 0x00f0 */ u8 unkF0;
    /* 0x00f1 */ u8 unkF1;
    /* 0x00f2 */ u8 unkF2;
    /* 0x00f3 */ u8 padF3[0x1];
    /* 0x00f4 */ u8 unkF4;
    /* 0x00f5 */ u8 unkF5;
    /* 0x00f6 */ u8 unkF6;
    /* 0x00f7 */ u8 padF7[0x1];
    /* 0x00f8 */ u8 unkF8;
    /* 0x00f9 */ u8 unkF9;
    /* 0x00fa */ u8 unkFA;
    /* 0x00fb */ u8 padFB[0x1];
    /* 0x00fc */ s32 unkFC;
} Unkstruct_8018A2D0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_420c143e: P3.40 T3 band rank 615; 30 TNC sites in 1 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 unk5E;
    /* 0x005f */ u8 pad5F[0x1];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u8 pad62[0x14];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u16 unk7C;
    /* 0x007e */ u16 unk7E;
    /* 0x0080 */ u16 unk80;
    /* 0x0082 */ u16 unk82;
    /* 0x0084 */ u8 pad84[0x3d];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 padC3[0x5];
    /* 0x00c8 */ u8 unkC8;
    /* 0x00c9 */ u8 unkC9;
    /* 0x00ca */ u8 padCA[0x2];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ s32 unkD8;
} Unkstruct_8018D870; /* size = 0xdc */

typedef struct {
    /* Unkstruct_4ee753b5: P3.40 T3 band rank 616; 30 TNC sites in 1 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0xa];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x44];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x74];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ s32 unkE4;
    /* 0x00e8 */ s32 unkE8;
    /* 0x00ec */ u8 padEC[0x10];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ u8 pad100[0x2];
    /* 0x0102 */ u16 unk102;
} Unkstruct_801845A4; /* size = 0x104 */

typedef struct {
    /* Unkstruct_65d4e72f: P3.40 T3 band rank 617; 30 TNC sites in 1 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x40];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ u8 pad78[0x1c];
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x36];
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0xe];
    /* 0x00e2 */ s16 unkE2;
    /* 0x00e4 */ u8 padE4[0xe];
    /* 0x00f2 */ s16 unkF2;
    /* 0x00f4 */ u8 padF4[0x2];
    /* 0x00f6 */ u16 unkF6;
} Unkstruct_801827DC; /* size = 0xf8 */

typedef struct {
    /* Unkstruct_892963a7: P3.40 T3 band rank 618; 30 TNC sites in 1 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017FEE0; /* size = 0x4 */

typedef struct {
    /* Unkstruct_c0f6351c: P3.40 T3 band rank 619; 30 TNC sites in 1 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x16];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ u8 pad78[0x54];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8017F0EC; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_8434e89c: P3.40 T3 band rank 620; 29 TNC sites in 29 bodies; struct map 29 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
} Unkstruct_8017E230; /* size = 0xc */

typedef struct {
    /* Unkstruct_c089a0d8: P3.40 T3 band rank 621; 29 TNC sites in 29 bodies; struct map 29 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017DC94; /* size = 0x100 */

typedef struct {
    /* Unkstruct_db4f55d6: P3.40 T3 band rank 622; 29 TNC sites in 29 bodies; struct map 29 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8017E230_2; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_50f68901: P3.40 T3 band rank 623; 29 TNC sites in 1 bodies; struct map 29 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x36];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x24];
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x32];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801867D0; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_5a3343f7: P3.40 T3 band rank 624; 29 TNC sites in 1 bodies; struct map 29 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 unk5E;
    /* 0x005f */ u8 pad5F[0x1];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u8 pad62[0x14];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ s16 unk7C;
    /* 0x007e */ s16 unk7E;
    /* 0x0080 */ s16 unk80;
    /* 0x0082 */ s16 unk82;
    /* 0x0084 */ u8 pad84[0x3d];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 padC3[0x5];
    /* 0x00c8 */ u8 unkC8;
    /* 0x00c9 */ u8 unkC9;
    /* 0x00ca */ u8 padCA[0x2];
} Unkstruct_8017DAC8; /* size = 0xcc */

typedef struct {
    /* Unkstruct_801298F4: P3.40 T3 band rank 625; 29 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 pad7[0x1];
} Unkstruct_801298F4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_e9e806d6: P3.40 T3 band rank 626; 29 TNC sites in 1 bodies; struct map 29 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_801809B0; /* size = 0x4 */

typedef struct {
    /* Unkstruct_554506a0: P3.40 T3 band rank 627; 28 TNC sites in 28 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_801427EC_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_8018B868: P3.40 T3 band rank 628; 28 TNC sites in 28 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801805EC; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_eac0514d: P3.40 T3 band rank 629; 28 TNC sites in 28 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017D658; /* size = 0x4 */

typedef struct {
    /* Unkstruct_0bcc9b5c: P3.40 T3 band rank 630; 28 TNC sites in 7 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
} Unkstruct_801397B0_7; /* size = 0x4 */

typedef struct {
    /* Unkstruct_3260335f: P3.40 T3 band rank 631; 28 TNC sites in 7 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801431E8_4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_47df6752: P3.40 T3 band rank 632; 28 TNC sites in 7 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80180068_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_66dce0a0: P3.40 T3 band rank 633; 28 TNC sites in 7 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017E7B4_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_772293b4: P3.40 T3 band rank 634; 28 TNC sites in 7 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0xc];
    /* 0x001e */ s16 unk1E;
} Unkstruct_80164BDC_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_96c78f07: P3.40 T3 band rank 635; 28 TNC sites in 7 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017EE0C_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_c6c4d4ad: P3.40 T3 band rank 636; 28 TNC sites in 7 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ u16 unk36;
} Unkstruct_80144364_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_d415eb36: P3.40 T3 band rank 637; 28 TNC sites in 7 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ u16 unk36;
} Unkstruct_80144880_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_f4527717: P3.40 T3 band rank 638; 28 TNC sites in 7 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x182];
    /* 0x0184 */ u32 unk184;
} Unkstruct_8015FAE8_2; /* size = 0x188 */

typedef struct {
    /* Unkstruct_3791ac8b: P3.40 T3 band rank 639; 28 TNC sites in 6 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x10];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x2e];
    /* 0x0052 */ u16 unk52;
    /* 0x0054 */ u8 pad54[0x1c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x72];
    /* 0x00e4 */ u16 unkE4;
    /* 0x00e6 */ u16 unkE6;
    /* 0x00e8 */ u16 unkE8;
    /* 0x00ea */ u8 padEA[0x2];
} Unkstruct_80181FE8; /* size = 0xec */

typedef struct {
    /* Unkstruct_1b628dd2: P3.40 T3 band rank 640; 28 TNC sites in 4 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_80135004_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_347d3efa: P3.40 T3 band rank 641; 28 TNC sites in 4 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x1e];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x210];
    /* 0x0234 */ s32 unk234;
    /* 0x0238 */ s32 unk238;
    /* 0x023c */ s32 unk23C;
} Unkstruct_8015C128_2; /* size = 0x240 */

typedef struct {
    /* Unkstruct_4634c976: P3.40 T3 band rank 642; 28 TNC sites in 4 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ u16 unk36;
} Unkstruct_8016C49C_4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_4fee4baf: P3.40 T3 band rank 644; 28 TNC sites in 2 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x48];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2a];
    /* 0x0088 */ s16 unk88;
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x2e];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 padC0[0x3c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801824C8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_8014FDF4: P3.40 T3 band rank 645; 28 TNC sites in 2 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x68];
    /* 0x0078 */ s16 unk78;
    /* 0x007a */ s16 unk7A;
    /* 0x007c */ s16 unk7C;
    /* 0x007e */ u16 unk7E;
} Unkstruct_8014FE60; /* size = 0x80 */

typedef struct {
    /* Unkstruct_d853e02a: P3.40 T3 band rank 646; 28 TNC sites in 2 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x48];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2a];
    /* 0x0088 */ s16 unk88;
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x2e];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 padC0[0x3c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801817DC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_e78224c1: P3.40 T3 band rank 647; 28 TNC sites in 2 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DF5C_4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2054b96e: P3.40 T3 band rank 649; 27 TNC sites in 27 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80180CCC_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8016B5C0: P3.40 T3 band rank 650; 27 TNC sites in 9 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016B5C0_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_8e4f57db: P3.40 T3 band rank 651; 27 TNC sites in 9 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801819D0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_e2d847b5: P3.40 T3 band rank 652; 27 TNC sites in 9 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80181904; /* size = 0x38 */

typedef struct {
    /* Unkstruct_f2e0775b: P3.40 T3 band rank 653; 27 TNC sites in 9 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801834E4; /* size = 0x24 */

typedef struct {
    /* Unkstruct_8017CE7C: P3.40 T3 band rank 654; 27 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017CE7C_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_fe2e4b7e: P3.40 T3 band rank 656; 27 TNC sites in 3 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x1e];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x60];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x76];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8018BBBC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_13429122: P3.40 T3 band rank 657; 27 TNC sites in 1 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xda];
    /* 0x00de */ s16 unkDE;
} Unkstruct_801810A4; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_53ef864a: P3.40 T3 band rank 658; 27 TNC sites in 1 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
} Unkstruct_801A5194; /* size = 0x68 */

typedef struct {
    /* Unkstruct_66219633: P3.40 T3 band rank 659; 27 TNC sites in 1 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x60];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x46];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x28];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017F278; /* size = 0x100 */

typedef struct {
    /* Unkstruct_80137840: P3.40 T3 band rank 660; 27 TNC sites in 1 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ u8 unkC;
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x1];
    /* 0x001f */ s8 unk1F;
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 pad21[0x1];
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 unk23;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0x8];
    /* 0x0040 */ s32 unk40;
    /* 0x0044 */ s16 unk44;
    /* 0x0046 */ s16 unk46;
    /* 0x0048 */ s16 unk48;
    /* 0x004a */ s16 unk4A;
} Unkstruct_80137840; /* size = 0x4c */

typedef struct {
    /* Unkstruct_005270f7: P3.40 T3 band rank 662; 26 TNC sites in 13 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
} Unkstruct_8017D928; /* size = 0x30 */

typedef struct {
    /* Unkstruct_295f71fe: P3.40 T3 band rank 663; 26 TNC sites in 13 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8017E514; /* size = 0x60 */

typedef struct {
    /* Unkstruct_2a4353d5: P3.40 T3 band rank 664; 26 TNC sites in 13 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017D4D8; /* size = 0x18 */

typedef struct {
    /* Unkstruct_358862c5: P3.40 T3 band rank 665; 26 TNC sites in 13 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ void * unkCC;
} Unkstruct_8017E420; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_c86ca6e3: P3.40 T3 band rank 666; 26 TNC sites in 13 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_80181FAC_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_fdb96c5d: P3.40 T3 band rank 667; 26 TNC sites in 13 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
} Unkstruct_8017DC14; /* size = 0x8 */

typedef struct {
    /* Unkstruct_8014C050: P3.40 T3 band rank 668; 26 TNC sites in 12 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8014C050; /* size = 0x38 */

typedef struct {
    /* Unkstruct_61c869c7: P3.40 T3 band rank 669; 26 TNC sites in 10 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_8017E8FC; /* size = 0x8 */

typedef struct {
    /* Unkstruct_09212b79: P3.40 T3 band rank 670; 26 TNC sites in 6 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x2];
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801A788C_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_066aa265: P3.40 T3 band rank 671; 26 TNC sites in 4 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x2];
    /* 0x001e */ u16 unk1E;
} Unkstruct_800CC424; /* size = 0x20 */

typedef struct {
    /* Unkstruct_2a2cd96e: P3.40 T3 band rank 672; 26 TNC sites in 4 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0xb];
    /* 0x0027 */ s8 unk27;
    /* 0x0028 */ u8 pad28[0x4];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801A57E8; /* size = 0x30 */

typedef struct {
    /* Unkstruct_801424E4: P3.40 T3 band rank 673; 26 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ s16 unk36;
} Unkstruct_801424E4_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_b3466dc5: P3.40 T3 band rank 674; 26 TNC sites in 2 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3];
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017DC20; /* size = 0x30 */

typedef struct {
    /* Unkstruct_be720178: P3.40 T3 band rank 675; 26 TNC sites in 2 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x4];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x64];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x1c];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017E654; /* size = 0x104 */

typedef struct {
    /* Unkstruct_7a666ee7: P3.40 T3 band rank 677; 26 TNC sites in 1 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x12];
    /* 0x0030 */ s32 unk30;
} Unkstruct_8018514C; /* size = 0x34 */

typedef struct {
    /* Unkstruct_80155150: P3.40 T3 band rank 678; 26 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x24];
    /* 0x0024 */ s32 unk24;
} Unkstruct_80155150; /* size = 0x28 */

typedef struct {
    /* Unkstruct_c710d681: P3.40 T3 band rank 679; 26 TNC sites in 1 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x12];
    /* 0x0030 */ s32 unk30;
} Unkstruct_8018A950; /* size = 0x34 */

typedef struct {
    /* Unkstruct_272a749d: P3.40 T3 band rank 680; 25 TNC sites in 25 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017C738; /* size = 0x4 */

typedef struct {
    /* Unkstruct_efef92f0: P3.40 T3 band rank 681; 25 TNC sites in 25 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017E75C_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_1eddbc07: P3.40 T3 band rank 682; 25 TNC sites in 5 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8017F750; /* size = 0x8 */

typedef struct {
    /* Unkstruct_24f0cde9: P3.40 T3 band rank 683; 25 TNC sites in 5 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x3c];
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x24];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x32];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801819DC; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_3b3229e8: P3.40 T3 band rank 684; 25 TNC sites in 5 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x48];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_801809C4_2; /* size = 0x74 */

typedef struct {
    /* Unkstruct_7c843ade: P3.40 T3 band rank 685; 25 TNC sites in 5 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8017E910_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_df955c8f: P3.40 T3 band rank 686; 25 TNC sites in 5 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0xc];
    /* 0x00e0 */ s32 unkE0;
} Unkstruct_80182034; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_42e78f76: P3.40 T3 band rank 688; 25 TNC sites in 2 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x30];
    /* 0x0098 */ u16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_801813E8; /* size = 0x9c */

typedef struct {
    /* Unkstruct_80163764: P3.40 T3 band rank 689; 25 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x5a];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_80163764; /* size = 0x60 */

typedef struct {
    /* Unkstruct_8017D254: P3.40 T3 band rank 690; 25 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017D254; /* size = 0x30 */

typedef struct {
    /* Unkstruct_801D98C8: P3.40 T3 band rank 691; 25 TNC sites in 2 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_80132288; /* size = 0x10 */

typedef struct {
    /* Unkstruct_d60e0c97: P3.40 T3 band rank 692; 25 TNC sites in 2 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x12];
    /* 0x0086 */ u16 unk86;
    /* 0x0088 */ s16 unk88;
    /* 0x008a */ u8 pad8A[0x2];
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x6e];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8018099C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_0fd7b585: P3.40 T3 band rank 693; 25 TNC sites in 1 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 unk21;
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ s8 unk24;
    /* 0x0025 */ s8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 unk29;
    /* 0x002a */ u8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
    /* 0x002c */ u8 unk2C;
    /* 0x002d */ u8 unk2D;
    /* 0x002e */ u8 unk2E;
    /* 0x002f */ u8 pad2F[0x1];
    /* 0x0030 */ u32 unk30;
} Unkstruct_800CB8A0_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_13c0fd50: P3.40 T3 band rank 694; 25 TNC sites in 1 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x8c];
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_80187288; /* size = 0x108 */

typedef struct {
    /* Unkstruct_33b5698a: P3.40 T3 band rank 696; 25 TNC sites in 1 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ u8 unkC;
    /* 0x000d */ u8 unkD;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ u8 unk14;
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ u8 unk1C;
    /* 0x001d */ u8 unk1D;
    /* 0x001e */ u8 pad1E[0x6];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 pad26[0x2];
} Unkstruct_8001D3FC; /* size = 0x28 */

typedef struct {
    /* Unkstruct_48daf429: P3.40 T3 band rank 697; 25 TNC sites in 1 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017E9F4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_794b3e4e: P3.40 T3 band rank 698; 25 TNC sites in 1 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 unk21;
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 unk29;
    /* 0x002a */ u8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
    /* 0x002c */ u8 unk2C;
    /* 0x002d */ u8 unk2D;
    /* 0x002e */ u8 unk2E;
    /* 0x002f */ u8 pad2F[0x1];
    /* 0x0030 */ s32 unk30;
} Unkstruct_8018A194; /* size = 0x34 */

typedef struct {
    /* Unkstruct_7a91c991: P3.40 T3 band rank 699; 25 TNC sites in 1 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x8c];
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_80187C6C; /* size = 0x108 */

typedef struct {
    /* Unkstruct_80148094: P3.40 T3 band rank 700; 25 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80148094; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8014FA70: P3.40 T3 band rank 701; 25 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8014FA70; /* size = 0x8 */

typedef struct {
    /* Unkstruct_80166438: P3.40 T3 band rank 702; 25 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ s8 unk24;
    /* 0x0025 */ s8 unk25;
    /* 0x0026 */ s8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_80166438; /* size = 0x28 */

typedef struct {
    /* Unkstruct_8016A8FC: P3.40 T3 band rank 703; 25 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_8016A8FC_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_847d421d: P3.40 T3 band rank 704; 25 TNC sites in 1 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x28];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017ED80; /* size = 0x100 */

typedef struct {
    /* Unkstruct_ba558fd0: P3.40 T3 band rank 706; 25 TNC sites in 1 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x2];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
    /* 0x0038 */ s16 unk38;
    /* 0x003a */ s16 unk3A;
    /* 0x003c */ s16 unk3C;
    /* 0x003e */ u8 pad3E[0x12];
    /* 0x0050 */ s32 unk50;
} Unkstruct_801833A0; /* size = 0x54 */

typedef struct {
    /* Unkstruct_c8c0b83f: P3.40 T3 band rank 707; 25 TNC sites in 1 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u16 unk1E;
    /* 0x0020 */ u16 unk20;
    /* 0x0022 */ u8 pad22[0x2];
    /* 0x0024 */ u16 unk24;
    /* 0x0026 */ u16 unk26;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u32 unk30;
    /* 0x0034 */ u32 unk34;
} Unkstruct_8017E37C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ea9bcf2b: P3.40 T3 band rank 708; 25 TNC sites in 1 bodies; struct map 25 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 unk21;
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ s8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ s8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 unk29;
    /* 0x002a */ u8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
    /* 0x002c */ u8 unk2C;
    /* 0x002d */ u8 unk2D;
    /* 0x002e */ u8 unk2E;
    /* 0x002f */ u8 pad2F[0x1];
    /* 0x0030 */ u32 unk30;
} Unkstruct_800CAF90_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_13343280: P3.40 T3 band rank 709; 24 TNC sites in 8 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x18];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017C2B0_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_497bd52c: P3.40 T3 band rank 710; 24 TNC sites in 8 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017D664; /* size = 0x2c */

typedef struct {
    /* Unkstruct_56f3659b: P3.40 T3 band rank 711; 24 TNC sites in 8 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017C218_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8018AB40: P3.40 T3 band rank 712; 24 TNC sites in 8 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80180B28; /* size = 0x14 */

typedef struct {
    /* Unkstruct_95024eb4: P3.40 T3 band rank 713; 24 TNC sites in 8 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
} Unkstruct_80181A1C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_dc086f11: P3.40 T3 band rank 714; 24 TNC sites in 8 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_801805F0; /* size = 0x4 */

typedef struct {
    /* Unkstruct_f2605de5: P3.40 T3 band rank 715; 24 TNC sites in 8 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_801824A8_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_ff6e7a32: P3.40 T3 band rank 716; 24 TNC sites in 8 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017D030_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_20fd02ad: P3.40 T3 band rank 717; 24 TNC sites in 6 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ s16 unk1E;
} Unkstruct_801812B8; /* size = 0x20 */

typedef struct {
    /* Unkstruct_7d3a62f3: P3.40 T3 band rank 718; 24 TNC sites in 6 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
} Unkstruct_801812B8_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_f4e02f3e: P3.40 T3 band rank 719; 24 TNC sites in 6 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801EDA64; /* size = 0x2c */

typedef struct {
    /* Unkstruct_09f627da: P3.40 T3 band rank 720; 24 TNC sites in 4 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_80182550_2; /* size = 0x10c */

typedef struct {
    /* Unkstruct_6d529f22: P3.40 T3 band rank 721; 24 TNC sites in 4 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_80135480_6; /* size = 0x10 */

typedef struct {
    /* Unkstruct_734b40c3: P3.40 T3 band rank 722; 24 TNC sites in 4 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80183650; /* size = 0x24 */

typedef struct {
    /* Unkstruct_897d2b6c: P3.40 T3 band rank 723; 24 TNC sites in 4 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ void * unk34;
} Unkstruct_8017E874; /* size = 0x38 */

typedef struct {
    /* Unkstruct_948e9174: P3.40 T3 band rank 724; 24 TNC sites in 4 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_80135480_7; /* size = 0x10 */

typedef struct {
    /* Unkstruct_a7263ffe: P3.40 T3 band rank 725; 24 TNC sites in 4 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801832EC; /* size = 0x18 */

typedef struct {
    /* Unkstruct_bd029ddc: P3.40 T3 band rank 726; 24 TNC sites in 4 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x63];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x1c];
    /* 0x00de */ s16 unkDE;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80189518; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d2617969: P3.40 T3 band rank 727; 24 TNC sites in 4 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017E778; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ec463357: P3.40 T3 band rank 728; 24 TNC sites in 4 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8017E0D8; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_dc3e0cd3: P3.40 T3 band rank 731; 24 TNC sites in 3 bodies; struct map 30 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xe6];
    /* 0x010a */ u16 unk10A;
} Unkstruct_801804D8; /* size = 0x10c */

typedef struct {
    /* Unkstruct_9f88e5a6: P3.40 T3 band rank 733; 24 TNC sites in 2 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ void * unk8;
    /* 0x000c */ u8 padC[0x40];
    /* 0x004c */ s16 unk4C;
    /* 0x004e */ u8 pad4E[0x2];
} Unkstruct_8017EEA4; /* size = 0x50 */

typedef struct {
    /* Unkstruct_cecd643b: P3.40 T3 band rank 734; 24 TNC sites in 2 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_801407F4_4; /* size = 0x20 */

typedef struct {
    /* Unkstruct_19ec998d: P3.40 T3 band rank 735; 24 TNC sites in 1 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x8];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x50];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017DF7C; /* size = 0x74 */

typedef struct {
    /* Unkstruct_2bbc8bfb: P3.40 T3 band rank 737; 24 TNC sites in 1 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80180B44; /* size = 0x20 */

typedef struct {
    /* Unkstruct_2f8b026c: P3.40 T3 band rank 738; 24 TNC sites in 1 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801919A0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_7a349a9f: P3.40 T3 band rank 740; 24 TNC sites in 1 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x36];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x8c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80180450_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_8012D098: P3.40 T3 band rank 742; 24 TNC sites in 1 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_8012D098; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8013361C: P3.40 T3 band rank 743; 24 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8013361C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_932f21ef: P3.40 T3 band rank 745; 24 TNC sites in 1 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_801A38E4; /* size = 0x10 */

typedef struct {
    /* Unkstruct_d8b33af2: P3.40 T3 band rank 747; 24 TNC sites in 1 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80191C50; /* size = 0x100 */

typedef struct {
    /* Unkstruct_ec4f6440: P3.40 T3 band rank 748; 24 TNC sites in 1 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ u8 pad60[0x10];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x76];
    /* 0x00e8 */ s32 unkE8;
    /* 0x00ec */ u8 padEC[0x10];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80180F70; /* size = 0x100 */

typedef struct {
    /* Unkstruct_f22d4e63: P3.40 T3 band rank 750; 24 TNC sites in 1 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x62];
    /* 0x0098 */ u16 unk98;
    /* 0x009a */ u8 pad9A[0x64];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017F6D8_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_c9fa9cd6: P3.40 T3 band rank 752; 23 TNC sites in 23 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017CD9C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_80146128: P3.40 T3 band rank 753; 23 TNC sites in 18 bodies; struct map 844 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x4];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0xc];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x1a];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_80146128; /* size = 0x54 */

typedef struct {
    /* Unkstruct_801269F0: P3.40 T3 band rank 754; 23 TNC sites in 7 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x12];
    /* 0x001e */ u8 unk1E;
    /* 0x001f */ u8 pad1F[0x1];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 pad21[0xb];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ s16 unk36;
} Unkstruct_801379FC; /* size = 0x38 */

typedef struct {
    /* Unkstruct_80168780: P3.40 T3 band rank 755; 23 TNC sites in 4 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ s32 unk2C;
} Unkstruct_80168780; /* size = 0x30 */

typedef struct {
    /* Unkstruct_80137DD4: P3.40 T3 band rank 757; 23 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_80137DD4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_3c1452ef: P3.40 T3 band rank 758; 23 TNC sites in 1 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x8c];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ s16 unk102;
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_8017E6F4; /* size = 0x108 */

typedef struct {
    /* Unkstruct_4a83d106: P3.40 T3 band rank 759; 23 TNC sites in 1 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x16];
    /* 0x0088 */ s16 unk88;
    /* 0x008a */ u8 pad8A[0x2];
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x4e];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017E254; /* size = 0x100 */

typedef struct {
    /* Unkstruct_80139680: P3.40 T3 band rank 760; 23 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x14];
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ u8 pad34[0x8];
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u16 unk3E;
} Unkstruct_80139680; /* size = 0x40 */

typedef struct {
    /* Unkstruct_80148648: P3.40 T3 band rank 761; 23 TNC sites in 1 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0xa7];
    /* 0x00a9 */ u8 unkA9;
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ s16 unkAC;
    /* 0x00ae */ u16 unkAE;
    /* 0x00b0 */ u8 padB0[0x100];
    /* 0x01b0 */ s32 unk1B0;
    /* 0x01b4 */ u8 pad1B4[0x11];
    /* 0x01c5 */ u8 unk1C5;
    /* 0x01c6 */ u8 pad1C6[0x2];
} Unkstruct_80148648; /* size = 0x1c8 */

typedef struct {
    /* Unkstruct_8014ED80: P3.40 T3 band rank 762; 23 TNC sites in 1 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x34];
    /* 0x0044 */ u32 unk44;
    /* 0x0048 */ u8 pad48[0x12c];
    /* 0x0174 */ void * unk174;
    /* 0x0178 */ void * unk178;
} Unkstruct_8014EE14_2; /* size = 0x17c */

typedef struct {
    /* Unkstruct_8016B114: P3.40 T3 band rank 763; 23 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x24];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_8016B114; /* size = 0x28 */

typedef struct {
    /* Unkstruct_8017C064: P3.40 T3 band rank 764; 23 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017C064; /* size = 0x30 */

typedef struct {
    /* Unkstruct_8017D140: P3.40 T3 band rank 765; 23 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017D140; /* size = 0x30 */

typedef struct {
    /* Unkstruct_8017DD5C: P3.40 T3 band rank 766; 23 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017DD5C; /* size = 0x30 */

typedef struct {
    /* Unkstruct_8017E078: P3.40 T3 band rank 767; 23 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017E078; /* size = 0x30 */

typedef struct {
    /* Unkstruct_9e84a4a2: P3.40 T3 band rank 769; 23 TNC sites in 1 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u8 pad28[0x4];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
} Unkstruct_80023BF0; /* size = 0x34 */

typedef struct {
    /* Unkstruct_c7e6bead: P3.40 T3 band rank 770; 23 TNC sites in 1 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80180514; /* size = 0x4 */

typedef struct {
    /* Unkstruct_e21c56fe: P3.40 T3 band rank 771; 23 TNC sites in 1 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xec];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u16 unk102;
} Unkstruct_80183D5C; /* size = 0x104 */

typedef struct {
    /* Unkstruct_a9099fd2: P3.40 T3 band rank 772; 22 TNC sites in 22 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8017E270_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_d52ef42e: P3.40 T3 band rank 773; 22 TNC sites in 22 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8017E270_3; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_af4c56e2: P3.40 T3 band rank 774; 22 TNC sites in 11 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017D0D0_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_7a3b0903: P3.40 T3 band rank 775; 22 TNC sites in 5 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
} Unkstruct_80180030; /* size = 0x8 */

typedef struct {
    /* Unkstruct_8016F094: P3.40 T3 band rank 776; 22 TNC sites in 5 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x44];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ u8 pad48[0x68];
    /* 0x00b0 */ s32 unkB0;
    /* 0x00b4 */ u8 padB4[0x18];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x62];
    /* 0x0132 */ s16 unk132;
    /* 0x0134 */ u8 pad134[0x2];
    /* 0x0136 */ s16 unk136;
    /* 0x0138 */ u8 pad138[0xc0];
    /* 0x01f8 */ s32 unk1F8;
    /* 0x01fc */ u8 pad1FC[0x8];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ s32 unk208;
    /* 0x020c */ s8 unk20C;
    /* 0x020d */ u8 pad20D[0x7];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8016F094; /* size = 0x218 */

typedef struct {
    /* Unkstruct_8bbe2e25: P3.40 T3 band rank 777; 22 TNC sites in 5 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x78];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u8 pad8A[0x52];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80181928; /* size = 0x100 */

typedef struct {
    /* Unkstruct_08006f79: P3.40 T3 band rank 782; 22 TNC sites in 2 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_801813B4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_20cd197c: P3.40 T3 band rank 783; 22 TNC sites in 2 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x1a];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0x94];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8018A6F8; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_3f3719e8: P3.40 T3 band rank 784; 22 TNC sites in 2 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0xaa];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x1a];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ s16 unk102;
} Unkstruct_801801D8; /* size = 0x104 */

typedef struct {
    /* Unkstruct_59c78b20: P3.40 T3 band rank 785; 22 TNC sites in 2 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80186AAC; /* size = 0x30 */

typedef struct {
    /* Unkstruct_aac77141: P3.40 T3 band rank 786; 22 TNC sites in 2 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017CE90; /* size = 0x34 */

typedef struct {
    /* Unkstruct_b4eff166: P3.40 T3 band rank 788; 22 TNC sites in 2 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x70];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x6a];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ s16 unkDE;
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x1a];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017E204; /* size = 0x104 */

typedef struct {
    /* Unkstruct_0ca670d8: P3.40 T3 band rank 789; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_8017E1D4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_180c2b13: P3.40 T3 band rank 790; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_8017F278_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_385b5ddf: P3.40 T3 band rank 791; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x10];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x4];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x60];
    /* 0x00dc */ u16 unkDC;
    /* 0x00de */ u16 unkDE;
} Unkstruct_80186434; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_8013AB54: P3.40 T3 band rank 794; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc0];
    /* 0x00c0 */ s16 unkC0;
    /* 0x00c2 */ s16 unkC2;
    /* 0x00c4 */ s16 unkC4;
    /* 0x00c6 */ s16 unkC6;
    /* 0x00c8 */ s16 unkC8;
    /* 0x00ca */ s16 unkCA;
    /* 0x00cc */ s16 unkCC;
    /* 0x00ce */ s16 unkCE;
    /* 0x00d0 */ s16 unkD0;
    /* 0x00d2 */ u8 padD2[0x2];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ s32 unkD8;
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ s16 unkE2;
} Unkstruct_8013AB54; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_818437f6: P3.40 T3 band rank 796; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x16];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u8 pad8A[0x2];
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x4e];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017E0FC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_994585f7: P3.40 T3 band rank 798; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x10];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x4];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x60];
    /* 0x00dc */ u16 unkDC;
    /* 0x00de */ u16 unkDE;
} Unkstruct_8017DCF8; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_9f8bd029: P3.40 T3 band rank 800; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_8017DDE0; /* size = 0x1c */

typedef struct {
    /* Unkstruct_a50f89d6: P3.40 T3 band rank 801; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xf];
    /* 0x000f */ u8 unkF;
    /* 0x0010 */ u8 unk10;
    /* 0x0011 */ u8 unk11;
    /* 0x0012 */ u8 unk12;
    /* 0x0013 */ u8 unk13;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 unk18;
    /* 0x0019 */ u8 unk19;
    /* 0x001a */ u8 unk1A;
    /* 0x001b */ u8 pad1B[0x1];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 unk21;
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ s16 unk26;
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 unk29;
    /* 0x002a */ u8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
} Unkstruct_801813E8_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_c64f55fd: P3.40 T3 band rank 802; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_8017D994_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_c8dcd8a0: P3.40 T3 band rank 803; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_8017E7E8_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_cca1dd32: P3.40 T3 band rank 804; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u8 pad38[0x14];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_8016A8FC_3; /* size = 0x58 */

typedef struct {
    /* Unkstruct_d06a4b40: P3.40 T3 band rank 805; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xf];
    /* 0x000f */ u8 unkF;
    /* 0x0010 */ u8 unk10;
    /* 0x0011 */ u8 unk11;
    /* 0x0012 */ u8 unk12;
    /* 0x0013 */ u8 unk13;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 unk18;
    /* 0x0019 */ u8 unk19;
    /* 0x001a */ u8 unk1A;
    /* 0x001b */ u8 pad1B[0x1];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 unk21;
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ s16 unk26;
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 unk29;
    /* 0x002a */ u8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
} Unkstruct_8017D3A0; /* size = 0x30 */

typedef struct {
    /* Unkstruct_eb402ce6: P3.40 T3 band rank 806; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x20];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x14];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017DAF4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_edd75494: P3.40 T3 band rank 807; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017ED80_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_f39cd143: P3.40 T3 band rank 808; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_8017E558; /* size = 0x1c */

typedef struct {
    /* Unkstruct_f72d9284: P3.40 T3 band rank 809; 22 TNC sites in 1 bodies; struct map 22 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xf];
    /* 0x000f */ u8 unkF;
    /* 0x0010 */ u8 unk10;
    /* 0x0011 */ u8 unk11;
    /* 0x0012 */ u8 unk12;
    /* 0x0013 */ u8 unk13;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 unk18;
    /* 0x0019 */ u8 unk19;
    /* 0x001a */ u8 unk1A;
    /* 0x001b */ u8 pad1B[0x1];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 unk21;
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x1];
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ s16 unk26;
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 unk29;
    /* 0x002a */ u8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
} Unkstruct_8017E4E0; /* size = 0x30 */

typedef struct {
    /* Unkstruct_0d5633d9: P3.40 T3 band rank 810; 21 TNC sites in 21 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8012BF4C_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_3448be93: P3.40 T3 band rank 811; 21 TNC sites in 21 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_80180D5C; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_5b4b4171: P3.40 T3 band rank 812; 21 TNC sites in 21 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017C378; /* size = 0x14 */

typedef struct {
    /* Unkstruct_bd661e00: P3.40 T3 band rank 814; 21 TNC sites in 21 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_8017E55C_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_3f7e9522: P3.40 T3 band rank 816; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017C3EC; /* size = 0x20 */

typedef struct {
    /* Unkstruct_6c1f9b52: P3.40 T3 band rank 817; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8015E4B0_4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_939ba7f7: P3.40 T3 band rank 818; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80169F3C_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_a6ba0b39: P3.40 T3 band rank 819; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x44];
    /* 0x0044 */ u32 unk44;
    /* 0x0048 */ u8 pad48[0x64];
    /* 0x00ac */ u16 unkAC;
    /* 0x00ae */ u8 padAE[0x11a];
    /* 0x01c8 */ s16 unk1C8;
    /* 0x01ca */ u8 pad1CA[0x2];
} Unkstruct_80149FB0_2; /* size = 0x1cc */

typedef struct {
    /* Unkstruct_a991abd5: P3.40 T3 band rank 820; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3c];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ s16 unk62;
} Unkstruct_80164BDC_4; /* size = 0x64 */

typedef struct {
    /* Unkstruct_b26d67c8: P3.40 T3 band rank 821; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8017C738_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_b494ae08: P3.40 T3 band rank 822; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801E2670; /* size = 0x2c */

typedef struct {
    /* Unkstruct_ed7bab12: P3.40 T3 band rank 823; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_80180C68_2; /* size = 0x74 */

typedef struct {
    /* Unkstruct_f35eb97b: P3.40 T3 band rank 824; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016C2C4_4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_f3e6be71: P3.40 T3 band rank 825; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8016BD78_4; /* size = 0x24 */

typedef struct {
    /* Unkstruct_fd5b6129: P3.40 T3 band rank 826; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3c];
    /* 0x003c */ s32 unk3C;
} Unkstruct_8015E4B0_5; /* size = 0x40 */

typedef struct {
    /* Unkstruct_2f48b0cc: P3.40 T3 band rank 827; 21 TNC sites in 6 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017DBD4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_77805655: P3.40 T3 band rank 828; 21 TNC sites in 4 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0xa];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
} Unkstruct_8001D3FC_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_22643710: P3.40 T3 band rank 830; 21 TNC sites in 3 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x1e];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x210];
    /* 0x0234 */ s32 unk234;
    /* 0x0238 */ s32 unk238;
    /* 0x023c */ s32 unk23C;
} Unkstruct_8015C128_3; /* size = 0x240 */

typedef struct {
    /* Unkstruct_297f9976: P3.40 T3 band rank 831; 21 TNC sites in 3 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ void * unkD0;
} Unkstruct_80181C18; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_517e665b: P3.40 T3 band rank 832; 21 TNC sites in 3 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80184294; /* size = 0x30 */

typedef struct {
    /* Unkstruct_5f854648: P3.40 T3 band rank 833; 21 TNC sites in 3 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_8016DC20_4; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8e626ec3: P3.40 T3 band rank 835; 21 TNC sites in 3 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x20];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016A290_5; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8ff30046: P3.40 T3 band rank 836; 21 TNC sites in 3 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u16 unk62;
} Unkstruct_80181114; /* size = 0x64 */

typedef struct {
    /* Unkstruct_df35ceac: P3.40 T3 band rank 837; 21 TNC sites in 3 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_8016DC20_5; /* size = 0x10 */

typedef struct {
    /* Unkstruct_f8b98731: P3.40 T3 band rank 838; 21 TNC sites in 3 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_80135004_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_fed713f2: P3.40 T3 band rank 839; 21 TNC sites in 3 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x1a];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u32 unk24;
    /* 0x0028 */ u32 unk28;
    /* 0x002c */ u32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ u32 unk34;
} Unkstruct_80165240_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_3c5479cb: P3.40 T3 band rank 840; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ s32 unk30;
} Unkstruct_80169BBC_3; /* size = 0x34 */

typedef struct {
    /* Unkstruct_4767ecf3: P3.40 T3 band rank 841; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x3a];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x6a];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8017DB90; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_56817d59: P3.40 T3 band rank 842; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x1a];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x3a];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_801902EC; /* size = 0x74 */

typedef struct {
    /* Unkstruct_581ad46c: P3.40 T3 band rank 843; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x48];
    /* 0x0048 */ s16 unk48;
    /* 0x004a */ s16 unk4A;
    /* 0x004c */ s16 unk4C;
    /* 0x004e */ u8 pad4E[0x4e];
    /* 0x009c */ s32 unk9C;
    /* 0x00a0 */ s32 unkA0;
} Unkstruct_8003DC90; /* size = 0xa4 */

typedef struct {
    /* Unkstruct_8012A988: P3.40 T3 band rank 845; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x70];
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x1c];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x27];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_8012A988; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_8f3a6533: P3.40 T3 band rank 846; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0xa];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u8 pad30[0x48];
    /* 0x0078 */ void * unk78;
    /* 0x007c */ u8 pad7C[0x4];
    /* 0x0080 */ void * unk80;
} Unkstruct_8001EFE0; /* size = 0x84 */

typedef struct {
    /* Unkstruct_97de538e: P3.40 T3 band rank 847; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x2];
    /* 0x00e2 */ s16 unkE2;
} Unkstruct_8017F6C0; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_a3f03b5a: P3.40 T3 band rank 848; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
} Unkstruct_80034DFC; /* size = 0x30 */

typedef struct {
    /* Unkstruct_abbd01f8: P3.40 T3 band rank 849; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x6];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0xe];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ u8 pad78[0x84];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x4];
    /* 0x0102 */ s16 unk102;
} Unkstruct_80182C98; /* size = 0x104 */

typedef struct {
    /* Unkstruct_b32a74aa: P3.40 T3 band rank 850; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x1e];
    /* 0x0086 */ u16 unk86;
} Unkstruct_80186518; /* size = 0x88 */

typedef struct {
    /* Unkstruct_bd10d5ad: P3.40 T3 band rank 851; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u16 unk2E;
} Unkstruct_8017FBE8; /* size = 0x30 */

typedef struct {
    /* Unkstruct_da8a53dd: P3.40 T3 band rank 852; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xcc];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ u8 padDE[0x2];
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x6];
    /* 0x00e8 */ s32 unkE8;
} Unkstruct_80185B38; /* size = 0xec */

typedef struct {
    /* Unkstruct_e54b8731: P3.40 T3 band rank 854; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ void * unkD0;
} Unkstruct_8018DB40; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_ec4bdb1c: P3.40 T3 band rank 855; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x36];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x24];
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x34];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_8018624C; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_fa89527d: P3.40 T3 band rank 856; 21 TNC sites in 1 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x4];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801A4ACC; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_9d63a75c: P3.40 T3 band rank 857; 20 TNC sites in 20 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x214];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_801727D0_2; /* size = 0x218 */

typedef struct {
    /* Unkstruct_123354be: P3.40 T3 band rank 858; 20 TNC sites in 10 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_80181854; /* size = 0x4 */

typedef struct {
    /* Unkstruct_0d6a98fb: P3.40 T3 band rank 859; 20 TNC sites in 5 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ s32 unk2C;
} Unkstruct_8017F1B8; /* size = 0x30 */

typedef struct {
    /* Unkstruct_4b4cce64: P3.40 T3 band rank 860; 20 TNC sites in 5 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_801803F8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_6f17232d: P3.40 T3 band rank 862; 20 TNC sites in 5 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017D9C8; /* size = 0x4 */

typedef struct {
    /* Unkstruct_d1cca146: P3.40 T3 band rank 863; 20 TNC sites in 5 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x6e];
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x88];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8018137C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_eb589292: P3.40 T3 band rank 864; 20 TNC sites in 5 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x4];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017F750_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_f8e95d5c: P3.40 T3 band rank 865; 20 TNC sites in 5 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017ED3C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_1d2b7b12: P3.40 T3 band rank 866; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017F2E8; /* size = 0x14 */

typedef struct {
    /* Unkstruct_34bca5e0: P3.40 T3 band rank 867; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017E4C8; /* size = 0x20 */

typedef struct {
    /* Unkstruct_358e9b5c: P3.40 T3 band rank 868; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x16];
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017D408; /* size = 0x38 */

typedef struct {
    /* Unkstruct_41dc373a: P3.40 T3 band rank 869; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x30];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ u8 pad4C[0x48];
    /* 0x0094 */ s32 unk94;
} Unkstruct_80181574; /* size = 0x98 */

typedef struct {
    /* Unkstruct_44cf89ff: P3.40 T3 band rank 870; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x86];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x54];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ s16 unk102;
} Unkstruct_8017E4C8_2; /* size = 0x104 */

typedef struct {
    /* Unkstruct_623a3b5c: P3.40 T3 band rank 871; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xe0];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_80181B60; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_6d0f0e4d: P3.40 T3 band rank 872; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DF5C_5; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8012C1B8: P3.40 T3 band rank 873; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0xe];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80180648; /* size = 0x30 */

typedef struct {
    /* Unkstruct_801380E0: P3.40 T3 band rank 874; 20 TNC sites in 4 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_801380E0; /* size = 0x14 */

typedef struct {
    /* Unkstruct_872734a8: P3.40 T3 band rank 875; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ u32 unk64;
    /* 0x0068 */ u8 pad68[0x98];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
} Unkstruct_801813BC; /* size = 0x104 */

typedef struct {
    /* Unkstruct_8f430fe6: P3.40 T3 band rank 876; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_8017E874_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_9d16c59d: P3.40 T3 band rank 877; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017C3C4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_a5f4d703: P3.40 T3 band rank 878; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0xb];
    /* 0x0027 */ u8 unk27;
} Unkstruct_8017F3E0; /* size = 0x28 */

typedef struct {
    /* Unkstruct_acbb6eed: P3.40 T3 band rank 879; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x4];
    /* 0x00d8 */ void * unkD8;
    /* 0x00dc */ u8 padDC[0x20];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80184B80; /* size = 0x100 */

typedef struct {
    /* Unkstruct_b73d2fc5: P3.40 T3 band rank 880; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_80181490; /* size = 0x10 */

typedef struct {
    /* Unkstruct_bae7bfa4: P3.40 T3 band rank 881; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017E6A4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_c17a6d01: P3.40 T3 band rank 882; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8017D890; /* size = 0x1c */

typedef struct {
    /* Unkstruct_c58b6dc0: P3.40 T3 band rank 883; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017F3E0_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_e68116b1: P3.40 T3 band rank 884; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x16];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8018064C; /* size = 0x1c */

typedef struct {
    /* Unkstruct_4c86fdf0: P3.40 T3 band rank 885; 20 TNC sites in 3 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x66];
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ u8 pad8C[0x70];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0xc];
    /* 0x010a */ u16 unk10A;
} Unkstruct_80183280; /* size = 0x10c */

typedef struct {
    /* Unkstruct_7edee2c6: P3.40 T3 band rank 886; 20 TNC sites in 3 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x24];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ u8 pad4C[0x18];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x96];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80181164; /* size = 0x100 */

typedef struct {
    /* Unkstruct_8014E48C: P3.40 T3 band rank 887; 20 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8014E48C; /* size = 0x60 */

typedef struct {
    /* Unkstruct_16638474: P3.40 T3 band rank 888; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8018D04C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_424f9baf: P3.40 T3 band rank 889; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x5c];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x1a];
    /* 0x008a */ s16 unk8A;
} Unkstruct_80183094; /* size = 0x8c */

typedef struct {
    /* Unkstruct_427b76ed: P3.40 T3 band rank 890; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80136824_3; /* size = 0x10 */

typedef struct {
    /* Unkstruct_6cbdb807: P3.40 T3 band rank 891; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80188EAC; /* size = 0x20 */

typedef struct {
    /* Unkstruct_80136334: P3.40 T3 band rank 892; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80136334; /* size = 0x10 */

typedef struct {
    /* Unkstruct_801365B8: P3.40 T3 band rank 893; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_801365B8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_80136824: P3.40 T3 band rank 894; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80136824_4; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8014D790: P3.40 T3 band rank 895; 20 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8014D790; /* size = 0x8 */

typedef struct {
    /* Unkstruct_8016DA7C: P3.40 T3 band rank 896; 20 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0xb];
    /* 0x0027 */ u8 unk27;
} Unkstruct_8016DA7C_3; /* size = 0x28 */

typedef struct {
    /* Unkstruct_80174BF4: P3.40 T3 band rank 897; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 pad5[0x7];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x8];
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ u8 pad34[0x20];
    /* 0x0054 */ s32 unk54;
} Unkstruct_80174BF4_3; /* size = 0x58 */

typedef struct {
    /* Unkstruct_81debdbd: P3.40 T3 band rank 899; 20 TNC sites in 2 bodies; struct map 770 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_801365B8_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8fe8cdc9: P3.40 T3 band rank 900; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
} Unkstruct_801AA7E4; /* size = 0x34 */

typedef struct {
    /* Unkstruct_930b8654: P3.40 T3 band rank 901; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
} Unkstruct_80180850; /* size = 0x2c */

typedef struct {
    /* Unkstruct_c125112d: P3.40 T3 band rank 902; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x18];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x12];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x2];
} Unkstruct_8017D764; /* size = 0x88 */

typedef struct {
    /* Unkstruct_f11a121e: P3.40 T3 band rank 903; 20 TNC sites in 2 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0xf0];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80180A80; /* size = 0x100 */

typedef struct {
    /* Unkstruct_110c9a81: P3.40 T3 band rank 904; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0xa];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ s32 unk34;
} Unkstruct_801815A0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_1a6b0aea: P3.40 T3 band rank 905; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
} Unkstruct_800359B0; /* size = 0x4 */

typedef struct {
    /* Unkstruct_1b40c5d8: P3.40 T3 band rank 906; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x68];
    /* 0x0088 */ s16 unk88;
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x2];
} Unkstruct_8018081C; /* size = 0x90 */

typedef struct {
    /* Unkstruct_2c30f5eb: P3.40 T3 band rank 908; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x1c];
    /* 0x0052 */ u16 unk52;
    /* 0x0054 */ u8 pad54[0x1c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017EAA0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_2faf43be: P3.40 T3 band rank 909; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0xa];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017E120; /* size = 0x24 */

typedef struct {
    /* Unkstruct_6562717a: P3.40 T3 band rank 911; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80181D38; /* size = 0x24 */

typedef struct {
    /* Unkstruct_99859c36: P3.40 T3 band rank 917; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x48];
    /* 0x0048 */ s16 unk48;
    /* 0x004a */ s16 unk4A;
    /* 0x004c */ s16 unk4C;
    /* 0x004e */ u8 pad4E[0x4e];
    /* 0x009c */ s32 unk9C;
    /* 0x00a0 */ s32 unkA0;
} Unkstruct_8003DF8C; /* size = 0xa4 */

typedef struct {
    /* Unkstruct_a40b513c: P3.40 T3 band rank 918; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x14];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x44];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x1c];
    /* 0x0084 */ u16 unk84;
    /* 0x0086 */ u8 pad86[0x4a];
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_80181F7C; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_cdb1551e: P3.40 T3 band rank 919; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80181914; /* size = 0x24 */

typedef struct {
    /* Unkstruct_d765b8d3: P3.40 T3 band rank 920; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017D77C_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_e5248276: P3.40 T3 band rank 921; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017F688; /* size = 0x24 */

typedef struct {
    /* Unkstruct_ebf1f108: P3.40 T3 band rank 922; 20 TNC sites in 1 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x2];
    /* 0x00e2 */ s16 unkE2;
} Unkstruct_801806F8; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_b0a0ff87: P3.40 T3 band rank 923; 19 TNC sites in 19 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x214];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_801727D0_3; /* size = 0x218 */

typedef struct {
    /* Unkstruct_adca0c01: P3.40 T3 band rank 925; 19 TNC sites in 2 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ u8 pad2A[0x2];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u8 pad32[0x2];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ s16 unk38;
    /* 0x003a */ u8 pad3A[0x16];
    /* 0x0050 */ void * unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_80184CA8; /* size = 0x58 */

typedef struct {
    /* Unkstruct_e8b5a8f7: P3.40 T3 band rank 926; 19 TNC sites in 2 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x54];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x10];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x6a];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1e];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017FB00; /* size = 0x100 */

typedef struct {
    /* Unkstruct_0019050d: P3.40 T3 band rank 927; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u8 pad64[0x4a];
    /* 0x00ae */ u16 unkAE;
    /* 0x00b0 */ u8 padB0[0x4c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80192CB4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_0cb7c1c4: P3.40 T3 band rank 928; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x8];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x3c];
    /* 0x00ae */ s16 unkAE;
    /* 0x00b0 */ u8 padB0[0x4];
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u8 padB8[0x4];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 unkC0;
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
    /* 0x00c4 */ s32 unkC4;
    /* 0x00c8 */ u8 padC8[0x4];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2e];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80185C7C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_1a0ee182: P3.40 T3 band rank 929; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80180594; /* size = 0x38 */

typedef struct {
    /* Unkstruct_22f6bb31: P3.40 T3 band rank 930; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x22];
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x4c];
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ s16 unkE6;
    /* 0x00e8 */ s16 unkE8;
    /* 0x00ea */ u8 padEA[0x20];
    /* 0x010a */ s16 unk10A;
} Unkstruct_801A48A8; /* size = 0x10c */

typedef struct {
    /* Unkstruct_6f42d339: P3.40 T3 band rank 932; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x1b];
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u8 pad28[0x4];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017C004_3; /* size = 0x30 */

typedef struct {
    /* Unkstruct_80162968: P3.40 T3 band rank 933; 19 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80162968; /* size = 0x14 */

typedef struct {
    /* Unkstruct_80165CA0: P3.40 T3 band rank 934; 19 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_80165CA0; /* size = 0x20 */

typedef struct {
    /* Unkstruct_80166054: P3.40 T3 band rank 935; 19 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80166054; /* size = 0x14 */

typedef struct {
    /* Unkstruct_846b6187: P3.40 T3 band rank 936; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017DF78_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_a24a264d: P3.40 T3 band rank 937; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u8 pad64[0x4a];
    /* 0x00ae */ u16 unkAE;
    /* 0x00b0 */ u8 padB0[0x4c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80192F64; /* size = 0x100 */

typedef struct {
    /* Unkstruct_c1e4c504: P3.40 T3 band rank 938; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u8 pad64[0x4a];
    /* 0x00ae */ u16 unkAE;
    /* 0x00b0 */ u8 padB0[0x4c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8018ECA0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_c2240754: P3.40 T3 band rank 939; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x6];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x4];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ u8 pad34[0x18];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_800CB304; /* size = 0x58 */

typedef struct {
    /* Unkstruct_cbd76164: P3.40 T3 band rank 940; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x12];
    /* 0x0024 */ u16 unk24;
    /* 0x0026 */ u16 unk26;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ u32 unk34;
} Unkstruct_8017E37C_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ea7ca79f: P3.40 T3 band rank 941; 19 TNC sites in 1 bodies; struct map 19 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x28];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801805D0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_0db48c0b: P3.40 T3 band rank 942; 18 TNC sites in 18 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017DE04_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_f429b2c3: P3.40 T3 band rank 944; 18 TNC sites in 18 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x20];
    /* 0x0044 */ s32 unk44;
} Unkstruct_80165FA4; /* size = 0x48 */

typedef struct {
    /* Unkstruct_aa38f4d7: P3.40 T3 band rank 945; 18 TNC sites in 10 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x10];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0xc];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ void * unkCC;
} Unkstruct_801825C8; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_0167d1dd: P3.40 T3 band rank 947; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xf8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80180BE4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_01d60b7e: P3.40 T3 band rank 948; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801831C8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_0e192ec3: P3.40 T3 band rank 949; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
} Unkstruct_80168BDC_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_3ae09f72: P3.40 T3 band rank 950; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
} Unkstruct_8017C1EC; /* size = 0x5c */

typedef struct {
    /* Unkstruct_527c6fbe: P3.40 T3 band rank 951; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_80183FD0; /* size = 0x10 */

typedef struct {
    /* Unkstruct_623cc8ef: P3.40 T3 band rank 952; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_8016E7C8_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_7ad7090e: P3.40 T3 band rank 953; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017E1AC; /* size = 0x68 */

typedef struct {
    /* Unkstruct_a8aa1fdd: P3.40 T3 band rank 954; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
} Unkstruct_8017E1AC_2; /* size = 0x5c */

typedef struct {
    /* Unkstruct_abe3f1fb: P3.40 T3 band rank 955; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8017BA3C_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_b96ad58f: P3.40 T3 band rank 956; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_8017D598_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_f64af735: P3.40 T3 band rank 958; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
} Unkstruct_80169BBC_4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_fae0dcfe: P3.40 T3 band rank 959; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ u32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_80182EC4; /* size = 0x60 */

typedef struct {
    /* Unkstruct_8014A1B0: P3.40 T3 band rank 961; 18 TNC sites in 5 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x154];
    /* 0x0178 */ s32 unk178;
} Unkstruct_8014A1B0; /* size = 0x17c */

typedef struct {
    /* Unkstruct_80154218: P3.40 T3 band rank 962; 18 TNC sites in 4 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb0];
    /* 0x00b0 */ void * unkB0;
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u16 unkBA;
    /* 0x00bc */ u8 unkBC;
    /* 0x00bd */ s8 unkBD;
    /* 0x00be */ u8 padBE[0x1e];
    /* 0x00dc */ s8 unkDC;
    /* 0x00dd */ u8 padDD[0x3];
} Unkstruct_80154218; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_80ef6348: P3.40 T3 band rank 963; 18 TNC sites in 4 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80013ED0; /* size = 0x14 */

typedef struct {
    /* Unkstruct_16c54ab1: P3.40 T3 band rank 964; 18 TNC sites in 3 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E2F08; /* size = 0x38 */

typedef struct {
    /* Unkstruct_3ebc8abb: P3.40 T3 band rank 966; 18 TNC sites in 3 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017D3A0_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_4e29d0ec: P3.40 T3 band rank 967; 18 TNC sites in 3 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x48];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_80136A94; /* size = 0x54 */

typedef struct {
    /* Unkstruct_562a3515: P3.40 T3 band rank 968; 18 TNC sites in 3 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E2E24; /* size = 0x38 */

typedef struct {
    /* Unkstruct_579f3479: P3.40 T3 band rank 969; 18 TNC sites in 3 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x28];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u8 pad2A[0x2];
    /* 0x002c */ void * unk2C;
    /* 0x0030 */ void * unk30;
} Unkstruct_8017C234; /* size = 0x34 */

typedef struct {
    /* Unkstruct_5f4424a4: P3.40 T3 band rank 970; 18 TNC sites in 3 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80182B10; /* size = 0x1c */

typedef struct {
    /* Unkstruct_71cf429a: P3.40 T3 band rank 971; 18 TNC sites in 3 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x48];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_80182B68; /* size = 0x74 */

typedef struct {
    /* Unkstruct_8068cd43: P3.40 T3 band rank 973; 18 TNC sites in 3 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_801825C0_2; /* size = 0x10c */

typedef struct {
    /* Unkstruct_c7796f28: P3.40 T3 band rank 975; 18 TNC sites in 3 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80184DD8; /* size = 0x24 */

typedef struct {
    /* Unkstruct_c8c00571: P3.40 T3 band rank 976; 18 TNC sites in 3 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_80168F40; /* size = 0x1c */

typedef struct {
    /* Unkstruct_2d360687: P3.40 T3 band rank 978; 18 TNC sites in 2 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xa];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x26];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x46];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0xc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80183DE0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_8013B274: P3.40 T3 band rank 981; 18 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
} Unkstruct_8013B274_4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_8017869C: P3.40 T3 band rank 982; 18 TNC sites in 2 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017869C; /* size = 0x30 */

typedef struct {
    /* Unkstruct_b5bd9af7: P3.40 T3 band rank 984; 18 TNC sites in 2 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x38];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x3];
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ u8 pad76[0x56];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ s32 unkD8;
    /* 0x00dc */ void * unkDC;
    /* 0x00e0 */ u8 padE0[0x1e];
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u8 pad100[0x6];
    /* 0x0106 */ u16 unk106;
} Unkstruct_80181EF4; /* size = 0x108 */

typedef struct {
    /* Unkstruct_d610c483: P3.40 T3 band rank 987; 18 TNC sites in 2 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x54];
    /* 0x0078 */ s32 unk78;
} Unkstruct_8015D738_8; /* size = 0x7c */

typedef struct {
    /* Unkstruct_0fadb41c: P3.40 T3 band rank 988; 18 TNC sites in 1 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ s16 unk36;
} Unkstruct_8017FBB0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_3beae931: P3.40 T3 band rank 990; 18 TNC sites in 1 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x3];
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ u8 pad76[0x2];
} Unkstruct_80180A2C; /* size = 0x78 */

typedef struct {
    /* Unkstruct_76468d22: P3.40 T3 band rank 992; 18 TNC sites in 1 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ void * unk34;
} Unkstruct_800CB328; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8013AA24: P3.40 T3 band rank 993; 18 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ s16 unk26;
} Unkstruct_8013AA24; /* size = 0x28 */

typedef struct {
    /* Unkstruct_801536DC: P3.40 T3 band rank 994; 18 TNC sites in 1 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x90];
    /* 0x00a0 */ s16 unkA0;
    /* 0x00a2 */ s16 unkA2;
    /* 0x00a4 */ s16 unkA4;
    /* 0x00a6 */ u8 padA6[0x38];
    /* 0x00de */ u8 unkDE;
    /* 0x00df */ u8 padDF[0x1];
} Unkstruct_801536DC; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_93c0ef5d: P3.40 T3 band rank 995; 18 TNC sites in 1 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
    /* 0x001c */ u32 unk1C;
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u32 unk24;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x1a];
    /* 0x0048 */ u32 unk48;
    /* 0x004c */ u32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_801AF368_3; /* size = 0x54 */

typedef struct {
    /* Unkstruct_9c0e73df: P3.40 T3 band rank 996; 18 TNC sites in 1 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x74];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ s32 unkE4;
    /* 0x00e8 */ s32 unkE8;
    /* 0x00ec */ u8 padEC[0x14];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80184A40; /* size = 0x104 */

typedef struct {
    /* Unkstruct_a80c1474: P3.40 T3 band rank 997; 18 TNC sites in 1 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2a];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x2];
} Unkstruct_8017F670; /* size = 0x90 */

typedef struct {
    /* Unkstruct_f4bc0253: P3.40 T3 band rank 998; 18 TNC sites in 1 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x46];
    /* 0x00ae */ s16 unkAE;
    /* 0x00b0 */ u8 padB0[0x1c];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80183D90; /* size = 0x100 */

typedef struct {
    /* Unkstruct_6a6bc658: P3.40 T3 band rank 1001; 17 TNC sites in 3 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0xd];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB190; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ae0e4ff1: P3.40 T3 band rank 1002; 17 TNC sites in 3 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x8];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0xc];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801AE734; /* size = 0x24 */

typedef struct {
    /* Unkstruct_34fc1067: P3.40 T3 band rank 1003; 17 TNC sites in 2 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe2];
    /* 0x00e2 */ s16 unkE2;
    /* 0x00e4 */ u16 unkE4;
    /* 0x00e6 */ u16 unkE6;
    /* 0x00e8 */ u16 unkE8;
    /* 0x00ea */ s16 unkEA;
    /* 0x00ec */ s16 unkEC;
    /* 0x00ee */ s16 unkEE;
    /* 0x00f0 */ s16 unkF0;
    /* 0x00f2 */ u8 padF2[0x10];
    /* 0x0102 */ s16 unk102;
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_801836D4; /* size = 0x108 */

typedef struct {
    /* Unkstruct_b222c27e: P3.40 T3 band rank 1004; 17 TNC sites in 2 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_8017E4DC; /* size = 0x10 */

typedef struct {
    /* Unkstruct_0fad7940: P3.40 T3 band rank 1005; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_8017FD54; /* size = 0x1c */

typedef struct {
    /* Unkstruct_1229edb3: P3.40 T3 band rank 1006; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801807DC; /* size = 0x104 */

typedef struct {
    /* Unkstruct_24e3564c: P3.40 T3 band rank 1007; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 pad1[0x3];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x22];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017E1E8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_49f558f2: P3.40 T3 band rank 1009; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x6];
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u8 pad3E[0x2];
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 pad42[0x8];
    /* 0x004a */ u8 unk4A;
    /* 0x004b */ u8 pad4B[0x1];
} Unkstruct_80176218_12; /* size = 0x4c */

typedef struct {
    /* Unkstruct_4a0f6043: P3.40 T3 band rank 1010; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x6];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0xc];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
} Unkstruct_800CB168; /* size = 0x2c */

typedef struct {
    /* Unkstruct_5d748c66: P3.40 T3 band rank 1011; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
} Unkstruct_801AD31C; /* size = 0x30 */

typedef struct {
    /* Unkstruct_7c88b621: P3.40 T3 band rank 1012; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd4];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x26];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ s16 unk10A;
} Unkstruct_8017F790; /* size = 0x10c */

typedef struct {
    /* Unkstruct_7e0f92a8: P3.40 T3 band rank 1013; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80185864; /* size = 0x100 */

typedef struct {
    /* Unkstruct_8012AF0C: P3.40 T3 band rank 1014; 17 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
} Unkstruct_8012AF0C; /* size = 0x5c */

typedef struct {
    /* Unkstruct_8014F74C: P3.40 T3 band rank 1017; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x78];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0xb2];
    /* 0x0140 */ u16 unk140;
    /* 0x0142 */ u16 unk142;
    /* 0x0144 */ u16 unk144;
    /* 0x0146 */ s16 unk146;
    /* 0x0148 */ u8 pad148[0x24];
    /* 0x016c */ u16 unk16C;
    /* 0x016e */ u16 unk16E;
} Unkstruct_8014F74C; /* size = 0x170 */

typedef struct {
    /* Unkstruct_8014FE60: P3.40 T3 band rank 1018; 17 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8014FE60_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_80150170: P3.40 T3 band rank 1019; 17 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80150170; /* size = 0x8 */

typedef struct {
    /* Unkstruct_80154358: P3.40 T3 band rank 1020; 17 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80154358; /* size = 0x24 */

typedef struct {
    /* Unkstruct_8016D848: P3.40 T3 band rank 1021; 17 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016D848_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_8017C0BC: P3.40 T3 band rank 1022; 17 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ s8 unk24;
    /* 0x0025 */ s8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_8017C0BC; /* size = 0x28 */

typedef struct {
    /* Unkstruct_8017C538: P3.40 T3 band rank 1023; 17 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ s8 unk24;
    /* 0x0025 */ s8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_8017C538; /* size = 0x28 */

typedef struct {
    /* Unkstruct_8017CF9C: P3.40 T3 band rank 1024; 17 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ s8 unk24;
    /* 0x0025 */ s8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_8017CF9C; /* size = 0x28 */

typedef struct {
    /* Unkstruct_8017DC00: P3.40 T3 band rank 1025; 17 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ s8 unk24;
    /* 0x0025 */ s8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_8017DC00; /* size = 0x28 */

typedef struct {
    /* Unkstruct_836e753e: P3.40 T3 band rank 1026; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x60];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x74];
    /* 0x00dc */ u32 unkDC;
    /* 0x00e0 */ u32 unkE0;
    /* 0x00e4 */ u32 unkE4;
    /* 0x00e8 */ u32 unkE8;
    /* 0x00ec */ u8 padEC[0xc];
    /* 0x00f8 */ u32 unkF8;
    /* 0x00fc */ u8 padFC[0x4];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801847E8; /* size = 0x104 */

typedef struct {
    /* Unkstruct_8c5c463c: P3.40 T3 band rank 1027; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u8 unkC;
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 unkE;
    /* 0x000f */ u8 padF[0x1];
    /* 0x0010 */ u32 unk10;
    /* 0x0014 */ u8 unk14;
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 unk16;
    /* 0x0017 */ u8 pad17[0x1];
    /* 0x0018 */ u32 unk18;
    /* 0x001c */ u8 unk1C;
    /* 0x001d */ u8 unk1D;
    /* 0x001e */ u8 unk1E;
    /* 0x001f */ u8 pad1F[0x1];
} Unkstruct_80185910; /* size = 0x20 */

typedef struct {
    /* Unkstruct_964c5cbf: P3.40 T3 band rank 1028; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xbc];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x1a];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80184CE0; /* size = 0x104 */

typedef struct {
    /* Unkstruct_9670d9cd: P3.40 T3 band rank 1029; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8018568C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_9c5cfebf: P3.40 T3 band rank 1030; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x36];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x24];
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x34];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ u8 padD0[0x4];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x26];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80186DDC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_a7423757: P3.40 T3 band rank 1031; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80185C14; /* size = 0x100 */

typedef struct {
    /* Unkstruct_aaa7b943: P3.40 T3 band rank 1032; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 unk14;
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 unk16;
    /* 0x0017 */ u8 pad17[0x1];
    /* 0x0018 */ u8 unk18;
    /* 0x0019 */ u8 unk19;
    /* 0x001a */ u8 unk1A;
    /* 0x001b */ u8 pad1B[0x1];
    /* 0x001c */ u8 unk1C;
    /* 0x001d */ u8 unk1D;
    /* 0x001e */ u8 unk1E;
    /* 0x001f */ u8 pad1F[0x1];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801AEC38; /* size = 0x24 */

typedef struct {
    /* Unkstruct_ba7ae413: P3.40 T3 band rank 1033; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80185A3C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_c277e06d: P3.40 T3 band rank 1034; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xbc];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ void * unkD0;
    /* 0x00d4 */ u8 padD4[0x20];
    /* 0x00f4 */ s16 unkF4;
    /* 0x00f6 */ u8 padF6[0x8];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_801A9674; /* size = 0x100 */

typedef struct {
    /* Unkstruct_cec8dea5: P3.40 T3 band rank 1035; 17 TNC sites in 1 bodies; struct map 17 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x10];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x48];
    /* 0x0068 */ s32 unk68;
    /* 0x006c */ u8 pad6C[0x74];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x18];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80180A38; /* size = 0x100 */

typedef struct {
    /* Unkstruct_bb132bdb: P3.40 T3 band rank 1036; 16 TNC sites in 16 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017DEEC; /* size = 0x14 */

typedef struct {
    /* Unkstruct_c2c52253: P3.40 T3 band rank 1037; 16 TNC sites in 16 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017DEEC_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_3196997f: P3.40 T3 band rank 1039; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80180C48; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_341b338c: P3.40 T3 band rank 1040; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x24];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80180384_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_3e180fd2: P3.40 T3 band rank 1041; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80181A1C_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_801B68F8: P3.40 T3 band rank 1045; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x6];
    /* 0x0010 */ s32 unk10;
} Unkstruct_80182998; /* size = 0x14 */

typedef struct {
    /* Unkstruct_82e49cb7: P3.40 T3 band rank 1046; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb0];
    /* 0x00b0 */ s32 unkB0;
} Unkstruct_80180EDC; /* size = 0xb4 */

typedef struct {
    /* Unkstruct_8e967cce: P3.40 T3 band rank 1047; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ u8 pad32[0x2];
} Unkstruct_8017E270_4; /* size = 0x34 */

typedef struct {
    /* Unkstruct_9d167fd3: P3.40 T3 band rank 1048; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80180EDC_2; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_a06e8395: P3.40 T3 band rank 1049; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017FC8C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_d0f7f6d1: P3.40 T3 band rank 1050; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_801805F0_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_da515265: P3.40 T3 band rank 1051; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017DE18; /* size = 0x68 */

typedef struct {
    /* Unkstruct_130cefa2: P3.40 T3 band rank 1052; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x8e];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
} Unkstruct_80182820; /* size = 0x98 */

typedef struct {
    /* Unkstruct_17ab65b3: P3.40 T3 band rank 1053; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x198];
    /* 0x0198 */ s32 unk198;
    /* 0x019c */ u8 pad19C[0x78];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8017E668; /* size = 0x218 */

typedef struct {
    /* Unkstruct_18f2a97e: P3.40 T3 band rank 1054; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017F2E8_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_2f64088a: P3.40 T3 band rank 1055; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017E9D8_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_38d91708: P3.40 T3 band rank 1056; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8018084C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_3d50e0ac: P3.40 T3 band rank 1057; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
} Unkstruct_8017FF14; /* size = 0x1c */

typedef struct {
    /* Unkstruct_44dfd11a: P3.40 T3 band rank 1058; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
} Unkstruct_80181ABC; /* size = 0x8 */

typedef struct {
    /* Unkstruct_52071e31: P3.40 T3 band rank 1059; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_801312D0_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_5f443f36: P3.40 T3 band rank 1060; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8017BB34_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_860bb85f: P3.40 T3 band rank 1061; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x52];
    /* 0x0052 */ u16 unk52;
    /* 0x0054 */ u8 pad54[0x5a];
    /* 0x00ae */ u16 unkAE;
    /* 0x00b0 */ u8 padB0[0x14];
    /* 0x00c4 */ u32 unkC4;
    /* 0x00c8 */ u8 padC8[0x18];
    /* 0x00e0 */ u32 unkE0;
} Unkstruct_801809C0; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_914a65c2: P3.40 T3 band rank 1062; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ s32 unk28;
} Unkstruct_80176218_13; /* size = 0x2c */

typedef struct {
    /* Unkstruct_ca552600: P3.40 T3 band rank 1063; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
} Unkstruct_8013AD38_4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_e48bdacd: P3.40 T3 band rank 1064; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
} Unkstruct_8016E728; /* size = 0x18 */

typedef struct {
    /* Unkstruct_00108303: P3.40 T3 band rank 1067; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 pad24[0x50];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x89];
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
} Unkstruct_8017F2A0; /* size = 0x104 */

typedef struct {
    /* Unkstruct_56651d10: P3.40 T3 band rank 1069; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x16];
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ s32 unk34;
} Unkstruct_80184370; /* size = 0x38 */

typedef struct {
    /* Unkstruct_70a4ea70: P3.40 T3 band rank 1070; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x3a];
    /* 0x0070 */ u8 unk70;
    /* 0x0071 */ u8 pad71[0x6b];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ u8 padDE[0x2];
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u16 unkE2;
} Unkstruct_8017EDBC; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_74462600: P3.40 T3 band rank 1071; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 pad24[0x50];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x89];
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
} Unkstruct_8017D710; /* size = 0x104 */

typedef struct {
    /* Unkstruct_8014E6F8: P3.40 T3 band rank 1072; 16 TNC sites in 2 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8014E790; /* size = 0x60 */

typedef struct {
    /* Unkstruct_80156044: P3.40 T3 band rank 1073; 16 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a8];
    /* 0x01a8 */ u8 unk1A8;
    /* 0x01a9 */ u8 pad1A9[0x17];
    /* 0x01c0 */ u8 unk1C0;
    /* 0x01c1 */ u8 pad1C1[0x3];
} Unkstruct_80156044_2; /* size = 0x1c4 */

typedef struct {
    /* Unkstruct_80169F3C: P3.40 T3 band rank 1074; 16 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80169F3C_4; /* size = 0x24 */

typedef struct {
    /* Unkstruct_86aaa851: P3.40 T3 band rank 1075; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x4];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8018D04C_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_9ab16e04: P3.40 T3 band rank 1076; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x16];
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8018BAB4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_9ff35be8: P3.40 T3 band rank 1077; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x16];
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ s32 unk34;
} Unkstruct_801887E8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_b4a5162f: P3.40 T3 band rank 1078; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x82];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x4];
    /* 0x00e8 */ s32 unkE8;
} Unkstruct_801A3334; /* size = 0xec */

typedef struct {
    /* Unkstruct_c272eaa4: P3.40 T3 band rank 1079; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017E654_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_c407f9e6: P3.40 T3 band rank 1080; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_800CB6A0; /* size = 0x4 */

typedef struct {
    /* Unkstruct_d3c12cc8: P3.40 T3 band rank 1081; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ void * unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x92];
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_80186AAC_2; /* size = 0x108 */

typedef struct {
    /* Unkstruct_d4b8c80d: P3.40 T3 band rank 1082; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2c];
    /* 0x0050 */ u16 unk50;
    /* 0x0052 */ u16 unk52;
    /* 0x0054 */ u16 unk54;
    /* 0x0056 */ u8 pad56[0x76];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ s8 unkFC;
    /* 0x00fd */ u8 padFD[0x3];
} Unkstruct_80184214; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d67021cf: P3.40 T3 band rank 1083; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x16];
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8018AC0C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_d6ec8d68: P3.40 T3 band rank 1084; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017E1D4_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_db4c3bfd: P3.40 T3 band rank 1085; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x4];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80188EAC_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_eb4178f1: P3.40 T3 band rank 1086; 16 TNC sites in 2 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xbc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801805C0; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_1a4dc512: P3.40 T3 band rank 1087; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017F278_3; /* size = 0x18 */

typedef struct {
    /* Unkstruct_237ef32c: P3.40 T3 band rank 1088; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_801838C8; /* size = 0x34 */

typedef struct {
    /* Unkstruct_34af6ee4: P3.40 T3 band rank 1089; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_80182BDC; /* size = 0x34 */

typedef struct {
    /* Unkstruct_457d0fc8: P3.40 T3 band rank 1090; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ s32 unk34;
} Unkstruct_80187D60; /* size = 0x38 */

typedef struct {
    /* Unkstruct_4d10c2ff: P3.40 T3 band rank 1092; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_80185E28; /* size = 0x34 */

typedef struct {
    /* Unkstruct_69f13275: P3.40 T3 band rank 1093; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801805D0_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_7076f01e: P3.40 T3 band rank 1094; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u16 unk20;
    /* 0x0022 */ u16 unk22;
} Unkstruct_8001F730; /* size = 0x24 */

typedef struct {
    /* Unkstruct_8012DBD0: P3.40 T3 band rank 1095; 16 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x58];
    /* 0x0058 */ u32 unk58;
} Unkstruct_8012DBD0; /* size = 0x5c */

typedef struct {
    /* Unkstruct_80151C54: P3.40 T3 band rank 1096; 16 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80151C54; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8016986C: P3.40 T3 band rank 1097; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ s32 unk2C;
} Unkstruct_8016986C_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_80184B14: P3.40 T3 band rank 1098; 16 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80184B14; /* size = 0x14 */

typedef struct {
    /* Unkstruct_804a6d36: P3.40 T3 band rank 1099; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x18];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x52];
    /* 0x0080 */ s32 unk80;
} Unkstruct_8017EF3C_2; /* size = 0x84 */

typedef struct {
    /* Unkstruct_8304e594: P3.40 T3 band rank 1100; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_80183084; /* size = 0x34 */

typedef struct {
    /* Unkstruct_86026b01: P3.40 T3 band rank 1101; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8018A21C; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8e9de8e4: P3.40 T3 band rank 1103; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017EBD0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_8f13b578: P3.40 T3 band rank 1104; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_801838EC; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8f77f5b0: P3.40 T3 band rank 1105; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x24];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ u8 pad4C[0x18];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x8];
    /* 0x010a */ u16 unk10A;
} Unkstruct_801859F4; /* size = 0x10c */

typedef struct {
    /* Unkstruct_a1a10e07: P3.40 T3 band rank 1106; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x6];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x52];
    /* 0x0080 */ void * unk80;
} Unkstruct_8017DA90; /* size = 0x84 */

typedef struct {
    /* Unkstruct_a263a9d7: P3.40 T3 band rank 1107; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u8 pad38[0x80];
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u16 unkBA;
    /* 0x00bc */ u8 padBC[0x178];
    /* 0x0234 */ s32 unk234;
} Unkstruct_80190538; /* size = 0x238 */

typedef struct {
    /* Unkstruct_a4c1fb3e: P3.40 T3 band rank 1108; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_80189FF0; /* size = 0x34 */

typedef struct {
    /* Unkstruct_ad845dfe: P3.40 T3 band rank 1109; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8018A6A4; /* size = 0x20 */

typedef struct {
    /* Unkstruct_b0c86da2: P3.40 T3 band rank 1110; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x7];
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
} Unkstruct_80175DA8_4; /* size = 0x18 */

typedef struct {
    /* Unkstruct_be980b33: P3.40 T3 band rank 1111; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x24];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ u8 pad4C[0x18];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x8];
    /* 0x010a */ u16 unk10A;
} Unkstruct_80181AD0; /* size = 0x10c */

typedef struct {
    /* Unkstruct_c9ba2334: P3.40 T3 band rank 1113; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x60];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x74];
    /* 0x00dc */ u32 unkDC;
    /* 0x00e0 */ u32 unkE0;
    /* 0x00e4 */ u32 unkE4;
    /* 0x00e8 */ u32 unkE8;
    /* 0x00ec */ u8 padEC[0xc];
    /* 0x00f8 */ u32 unkF8;
} Unkstruct_80184914; /* size = 0xfc */

typedef struct {
    /* Unkstruct_cb187d55: P3.40 T3 band rank 1114; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0xa];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ s32 unk34;
} Unkstruct_801816A8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_e15dc0d9: P3.40 T3 band rank 1115; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x7];
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
} Unkstruct_80175DA8_5; /* size = 0x18 */

typedef struct {
    /* Unkstruct_e62c0143: P3.40 T3 band rank 1117; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017F15C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_e85749d1: P3.40 T3 band rank 1118; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x6];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x110];
    /* 0x011a */ u16 unk11A;
} Unkstruct_801864A8; /* size = 0x11c */

typedef struct {
    /* Unkstruct_ea207b39: P3.40 T3 band rank 1119; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ u8 pad30[0x50];
    /* 0x0080 */ s32 unk80;
} Unkstruct_8001C9D0; /* size = 0x84 */

typedef struct {
    /* Unkstruct_f406805c: P3.40 T3 band rank 1120; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x54];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x1];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ u8 pad78[0x10];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x2];
} Unkstruct_80180854; /* size = 0x90 */

typedef struct {
    /* Unkstruct_fb44a0ca: P3.40 T3 band rank 1121; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8018AC00; /* size = 0x34 */

typedef struct {
    /* Unkstruct_14c07fa4: P3.40 T3 band rank 1122; 15 TNC sites in 15 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017BF88_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_b8c0d900: P3.40 T3 band rank 1123; 15 TNC sites in 15 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017EAB4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_80186D88: P3.40 T3 band rank 1124; 15 TNC sites in 9 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0xb];
    /* 0x0027 */ u8 unk27;
} Unkstruct_8017EF48; /* size = 0x28 */

typedef struct {
    /* Unkstruct_1d9ee4d6: P3.40 T3 band rank 1125; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_8017E67C; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_2ed78455: P3.40 T3 band rank 1126; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xf8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80181884; /* size = 0x100 */

typedef struct {
    /* Unkstruct_378da863: P3.40 T3 band rank 1127; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xd8];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1e];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017E18C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_3e2c8a1b: P3.40 T3 band rank 1128; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x76];
    /* 0x00d4 */ s32 unkD4;
} Unkstruct_8017FD08; /* size = 0xd8 */

typedef struct {
    /* Unkstruct_4041aa85: P3.40 T3 band rank 1129; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017C4F8; /* size = 0x20 */

typedef struct {
    /* Unkstruct_7e6b8bbc: P3.40 T3 band rank 1131; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2c];
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0x4];
    /* 0x0058 */ s32 unk58;
} Unkstruct_8017D364_2; /* size = 0x5c */

typedef struct {
    /* Unkstruct_86cb5e3b: P3.40 T3 band rank 1132; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8017FD34; /* size = 0x60 */

typedef struct {
    /* Unkstruct_95815b41: P3.40 T3 band rank 1133; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80180EE0; /* size = 0x8 */

typedef struct {
    /* Unkstruct_cf2b2be2: P3.40 T3 band rank 1134; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017F554; /* size = 0x4 */

typedef struct {
    /* Unkstruct_d289c585: P3.40 T3 band rank 1135; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017C18C_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_d46c00a4: P3.40 T3 band rank 1136; 15 TNC sites in 5 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x3a];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x4];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ u8 pad78[0x4a];
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 padC3[0x1];
} Unkstruct_80180854_2; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_d4dbf8e4: P3.40 T3 band rank 1137; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
} Unkstruct_8017ED6C; /* size = 0xc */

typedef struct {
    /* Unkstruct_d66f68f0: P3.40 T3 band rank 1138; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x12];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017FD34_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_d9c6cdd8: P3.40 T3 band rank 1139; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017FB10_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_08fc9de7: P3.40 T3 band rank 1140; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x52];
    /* 0x0080 */ s32 unk80;
} Unkstruct_8017F5B8; /* size = 0x84 */

typedef struct {
    /* Unkstruct_150b9e52: P3.40 T3 band rank 1141; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x72];
    /* 0x00e4 */ u16 unkE4;
    /* 0x00e6 */ u16 unkE6;
    /* 0x00e8 */ u16 unkE8;
    /* 0x00ea */ u8 padEA[0x2];
} Unkstruct_8018260C; /* size = 0xec */

typedef struct {
    /* Unkstruct_29970fd4: P3.40 T3 band rank 1142; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801838EC_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_33f2fe18: P3.40 T3 band rank 1143; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x16];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017E0F4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_4d0ffcbc: P3.40 T3 band rank 1146; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x52];
    /* 0x0052 */ s16 unk52;
    /* 0x0054 */ u8 pad54[0xa];
    /* 0x005e */ u8 unk5E;
    /* 0x005f */ u8 pad5F[0x65];
    /* 0x00c4 */ s32 unkC4;
    /* 0x00c8 */ u8 padC8[0x42];
    /* 0x010a */ s16 unk10A;
} Unkstruct_80182190; /* size = 0x10c */

typedef struct {
    /* Unkstruct_80128D60: P3.40 T3 band rank 1147; 15 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x27];
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
} Unkstruct_80018450; /* size = 0x2c */

typedef struct {
    /* Unkstruct_8013C360: P3.40 T3 band rank 1148; 15 TNC sites in 3 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
} Unkstruct_8013C360; /* size = 0x8 */

typedef struct {
    /* Unkstruct_8018B164: P3.40 T3 band rank 1149; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_801826E8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_829d67bd: P3.40 T3 band rank 1150; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x16];
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017DF10; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8eb3c8ae: P3.40 T3 band rank 1151; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x63];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x3a];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8018561C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_95634e7b: P3.40 T3 band rank 1152; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801872D8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_9b28d391: P3.40 T3 band rank 1153; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x40];
    /* 0x0044 */ u32 unk44;
} Unkstruct_80159A20; /* size = 0x48 */

typedef struct {
    /* Unkstruct_ac4f58a7: P3.40 T3 band rank 1154; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017EA88; /* size = 0x74 */

typedef struct {
    /* Unkstruct_deb6c0fc: P3.40 T3 band rank 1155; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x7c];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1e];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80180388; /* size = 0x100 */

typedef struct {
    /* Unkstruct_80147478: P3.40 T3 band rank 1156; 15 TNC sites in 2 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80147478; /* size = 0x18 */

typedef struct {
    /* Unkstruct_8e24ca3f: P3.40 T3 band rank 1157; 15 TNC sites in 2 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xb8];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ s16 unkDE;
} Unkstruct_8018340C; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_06713e44: P3.40 T3 band rank 1158; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8017EE3C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_06b85f92: P3.40 T3 band rank 1159; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s32 unk10;
} Unkstruct_8017E634; /* size = 0x14 */

typedef struct {
    /* Unkstruct_0855ec00: P3.40 T3 band rank 1161; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017C004_4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_17856fae: P3.40 T3 band rank 1162; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ u8 pad2A[0x6];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ void * unk34;
} Unkstruct_8016C998_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_1a7cfd37: P3.40 T3 band rank 1163; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_8018234C; /* size = 0x14 */

typedef struct {
    /* Unkstruct_1ff45a51: P3.40 T3 band rank 1165; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x3a];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x16];
    /* 0x0088 */ s16 unk88;
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x2];
} Unkstruct_8017F8CC; /* size = 0x90 */

typedef struct {
    /* Unkstruct_2ad5c3ce: P3.40 T3 band rank 1166; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x60];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x2];
} Unkstruct_8017FD30; /* size = 0x88 */

typedef struct {
    /* Unkstruct_2f082b78: P3.40 T3 band rank 1167; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80185990; /* size = 0x38 */

typedef struct {
    /* Unkstruct_399b7cfc: P3.40 T3 band rank 1168; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8017EA24; /* size = 0x8 */

typedef struct {
    /* Unkstruct_45afe83a: P3.40 T3 band rank 1169; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_80185E34; /* size = 0x14 */

typedef struct {
    /* Unkstruct_50c9071c: P3.40 T3 band rank 1171; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8017DB00; /* size = 0x8 */

typedef struct {
    /* Unkstruct_5da4baab: P3.40 T3 band rank 1172; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x1a];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x3a];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8018C2D8; /* size = 0x74 */

typedef struct {
    /* Unkstruct_6a371132: P3.40 T3 band rank 1174; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0xa];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
} Unkstruct_8018E4A4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_6bb403bf: P3.40 T3 band rank 1175; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018A2E0; /* size = 0x24 */

typedef struct {
    /* Unkstruct_71b0019b: P3.40 T3 band rank 1176; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_80182498; /* size = 0x14 */

typedef struct {
    /* Unkstruct_80147118: P3.40 T3 band rank 1181; 15 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80147118; /* size = 0x20 */

typedef struct {
    /* Unkstruct_8014F4C0: P3.40 T3 band rank 1183; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x78];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0xb2];
    /* 0x0140 */ u16 unk140;
    /* 0x0142 */ u16 unk142;
    /* 0x0144 */ u16 unk144;
    /* 0x0146 */ s16 unk146;
    /* 0x0148 */ u8 pad148[0x24];
    /* 0x016c */ u16 unk16C;
    /* 0x016e */ u16 unk16E;
} Unkstruct_8014F4C0; /* size = 0x170 */

typedef struct {
    /* Unkstruct_8016DB34: P3.40 T3 band rank 1184; 15 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0xb];
    /* 0x0027 */ s8 unk27;
} Unkstruct_8016DB34; /* size = 0x28 */

typedef struct {
    /* Unkstruct_80175590: P3.40 T3 band rank 1185; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 pad2[0x3];
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 pad7[0x1];
    /* 0x0008 */ u8 unk8;
    /* 0x0009 */ u8 pad9[0x3];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
} Unkstruct_80175590; /* size = 0x18 */

typedef struct {
    /* Unkstruct_801756E4: P3.40 T3 band rank 1186; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 pad2[0x3];
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 pad7[0x1];
    /* 0x0008 */ u8 unk8;
    /* 0x0009 */ u8 pad9[0x3];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
} Unkstruct_801756E4; /* size = 0x18 */

typedef struct {
    /* Unkstruct_8017C800: P3.40 T3 band rank 1187; 15 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017C800; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8017D618: P3.40 T3 band rank 1188; 15 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017D618; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8017D6E0: P3.40 T3 band rank 1189; 15 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017D6E0; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8017D8DC: P3.40 T3 band rank 1190; 15 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017D8DC; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8017D9F0: P3.40 T3 band rank 1191; 15 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017D9F0; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8017E4F8: P3.40 T3 band rank 1193; 15 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017E4F8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8017E814: P3.40 T3 band rank 1194; 15 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017E814; /* size = 0x10 */

typedef struct {
    /* Unkstruct_80186764: P3.40 T3 band rank 1195; 15 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80186764; /* size = 0x24 */

typedef struct {
    /* Unkstruct_80235db6: P3.40 T3 band rank 1196; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_801829F8; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8bc474bf: P3.40 T3 band rank 1197; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8017E710; /* size = 0x8 */

typedef struct {
    /* Unkstruct_8d985b81: P3.40 T3 band rank 1198; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_801860E8; /* size = 0x14 */

typedef struct {
    /* Unkstruct_928c6836: P3.40 T3 band rank 1199; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x28];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0xc6];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017F704; /* size = 0x100 */

typedef struct {
    /* Unkstruct_9c9f82d8: P3.40 T3 band rank 1200; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_8018B23C; /* size = 0x14 */

typedef struct {
    /* Unkstruct_a319d628: P3.40 T3 band rank 1201; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80190E64; /* size = 0x104 */

typedef struct {
    /* Unkstruct_a3cdafa1: P3.40 T3 band rank 1202; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_8018EBCC; /* size = 0x14 */

typedef struct {
    /* Unkstruct_ad070241: P3.40 T3 band rank 1203; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_8018B2C4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_ad0c90a7: P3.40 T3 band rank 1204; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_80187314; /* size = 0x14 */

typedef struct {
    /* Unkstruct_b50b4dd5: P3.40 T3 band rank 1205; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80180020; /* size = 0x24 */

typedef struct {
    /* Unkstruct_c746796b: P3.40 T3 band rank 1206; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8017E878; /* size = 0x8 */

typedef struct {
    /* Unkstruct_c88972e4: P3.40 T3 band rank 1208; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x10];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8018C2D8_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_c9955074: P3.40 T3 band rank 1209; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8017DE10; /* size = 0x8 */

typedef struct {
    /* Unkstruct_ce308c00: P3.40 T3 band rank 1210; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_80185150; /* size = 0x14 */

typedef struct {
    /* Unkstruct_dba9b1e4: P3.40 T3 band rank 1211; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8017FBC8; /* size = 0x8 */

typedef struct {
    /* Unkstruct_de69545a: P3.40 T3 band rank 1212; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_80184918; /* size = 0x14 */

typedef struct {
    /* Unkstruct_e0c0f795: P3.40 T3 band rank 1213; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_801865DC; /* size = 0x14 */

typedef struct {
    /* Unkstruct_f025e695: P3.40 T3 band rank 1214; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x64];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x6e];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80182FCC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_f2a63be1: P3.40 T3 band rank 1215; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8017C95C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_f4799d35: P3.40 T3 band rank 1216; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8017D370; /* size = 0x8 */

typedef struct {
    /* Unkstruct_f9fa14ab: P3.40 T3 band rank 1217; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_801844D4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_133b6f2b: P3.40 T3 band rank 1218; 14 TNC sites in 14 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x70];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017DC9C; /* size = 0x74 */

typedef struct {
    /* Unkstruct_7b905f67: P3.40 T3 band rank 1219; 14 TNC sites in 14 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x40];
    /* 0x0044 */ u32 unk44;
} Unkstruct_80175184_2; /* size = 0x48 */

typedef struct {
    /* Unkstruct_b01f36f3: P3.40 T3 band rank 1220; 14 TNC sites in 14 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 pad2[0x2];
} Unkstruct_8017553C_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_17f4e125: P3.40 T3 band rank 1221; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8014305C_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_2f976935: P3.40 T3 band rank 1222; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x98];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_8017FEF0; /* size = 0x9c */

typedef struct {
    /* Unkstruct_368ec773: P3.40 T3 band rank 1223; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80142E38_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_3e37801a: P3.40 T3 band rank 1224; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80142DC4_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_3f866305: P3.40 T3 band rank 1225; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_801397B0_8; /* size = 0x4 */

typedef struct {
    /* Unkstruct_4b0676c5: P3.40 T3 band rank 1226; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_8017BEBC_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_4f63b2e2: P3.40 T3 band rank 1227; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xf8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80142A10_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_54d78cde: P3.40 T3 band rank 1229; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80181A98; /* size = 0x38 */

typedef struct {
    /* Unkstruct_5bee0a35: P3.40 T3 band rank 1230; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
} Unkstruct_8013B274_5; /* size = 0x4 */

typedef struct {
    /* Unkstruct_5e4d5267: P3.40 T3 band rank 1231; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb8];
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u8 padBA[0x2];
} Unkstruct_80173220_2; /* size = 0xbc */

typedef struct {
    /* Unkstruct_690b2981: P3.40 T3 band rank 1232; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80158FA4_4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_75ace660: P3.40 T3 band rank 1233; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80164744_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_881ad763: P3.40 T3 band rank 1234; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80180A9C_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_890d5f38: P3.40 T3 band rank 1235; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8017FC34_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_8bcd4bad: P3.40 T3 band rank 1236; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017BEBC_4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_a9323cad: P3.40 T3 band rank 1237; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80142E38_4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d43a5e52: P3.40 T3 band rank 1239; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80142DC4_4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_db705b9d: P3.40 T3 band rank 1241; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80180C68_3; /* size = 0x18 */

typedef struct {
    /* Unkstruct_db994e6c: P3.40 T3 band rank 1242; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8016EBA8_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_f4f51141: P3.40 T3 band rank 1243; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017DD8C; /* size = 0x74 */

typedef struct {
    /* Unkstruct_fd7248ff: P3.40 T3 band rank 1244; 14 TNC sites in 7 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8016E9EC_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_80187E78: P3.40 T3 band rank 1245; 14 TNC sites in 3 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017B368; /* size = 0x14 */

typedef struct {
    /* Unkstruct_1110c071: P3.40 T3 band rank 1246; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_800CC6C4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_196a09c8: P3.40 T3 band rank 1247; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ u16 unk36;
} Unkstruct_8016C49C_5; /* size = 0x38 */

typedef struct {
    /* Unkstruct_1f2a9dcf: P3.40 T3 band rank 1248; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8018CF48_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_38474edb: P3.40 T3 band rank 1249; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x4c];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x50];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017FC50; /* size = 0x100 */

typedef struct {
    /* Unkstruct_4ab05c7d: P3.40 T3 band rank 1250; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ void * unkD0;
} Unkstruct_80188C28; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_555fd776: P3.40 T3 band rank 1251; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x20];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016A290_6; /* size = 0x38 */

typedef struct {
    /* Unkstruct_6d7c51ea: P3.40 T3 band rank 1252; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u8 pad4[0x8];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u16 unk1E;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
} Unkstruct_80185680; /* size = 0x28 */

typedef struct {
    /* Unkstruct_8013A380: P3.40 T3 band rank 1253; 14 TNC sites in 2 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x28];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
} Unkstruct_8013A448; /* size = 0x2c */

typedef struct {
    /* Unkstruct_8015E4B0: P3.40 T3 band rank 1254; 14 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18c];
    /* 0x018c */ void * unk18C;
} Unkstruct_8015E4B0_6; /* size = 0x190 */

typedef struct {
    /* Unkstruct_89fa0292: P3.40 T3 band rank 1255; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80180D70; /* size = 0x8 */

typedef struct {
    /* Unkstruct_a2363aaa: P3.40 T3 band rank 1257; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ void * unkD0;
} Unkstruct_80185E98; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_ab7fd576: P3.40 T3 band rank 1258; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4e];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x7c];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_80185B5C; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_ab85a5ff: P3.40 T3 band rank 1259; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x42];
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u8 padB8[0x4];
    /* 0x00bc */ void * unkBC;
    /* 0x00c0 */ u8 unkC0;
    /* 0x00c1 */ u8 padC1[0x3];
    /* 0x00c4 */ u32 unkC4;
    /* 0x00c8 */ u8 padC8[0x1c];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_8018037C; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_b52d7a0c: P3.40 T3 band rank 1260; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ u8 padDE[0x1e];
    /* 0x00fc */ s8 unkFC;
    /* 0x00fd */ s8 unkFD;
    /* 0x00fe */ s8 unkFE;
    /* 0x00ff */ s8 unkFF;
} Unkstruct_801864C0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_e46e123b: P3.40 T3 band rank 1261; 14 TNC sites in 2 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80182904; /* size = 0x30 */

typedef struct {
    /* Unkstruct_12278071: P3.40 T3 band rank 1262; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x64];
    /* 0x0088 */ s16 unk88;
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x176];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ u8 pad208[0x4];
    /* 0x020c */ s16 unk20C;
    /* 0x020e */ u8 pad20E[0x6];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_801808B0; /* size = 0x218 */

typedef struct {
    /* Unkstruct_1eae68c7: P3.40 T3 band rank 1265; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x64];
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 padC3[0x1];
} Unkstruct_8017F98C; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_2172841f: P3.40 T3 band rank 1266; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0xa8];
    /* 0x00e0 */ u32 unkE0;
} Unkstruct_8018833C; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_231433a9: P3.40 T3 band rank 1267; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ u8 padDE[0x2];
} Unkstruct_80180D54; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_36731042: P3.40 T3 band rank 1270; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0xa8];
    /* 0x00e0 */ u32 unkE0;
} Unkstruct_80187DD0; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_39a3a135: P3.40 T3 band rank 1271; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x4];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x46];
    /* 0x00ae */ s16 unkAE;
    /* 0x00b0 */ u8 padB0[0x11];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_8017EBA0; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_3a117f34: P3.40 T3 band rank 1272; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x48];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2a];
    /* 0x0088 */ s16 unk88;
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x2e];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 padC0[0x3c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80180CF0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_5282139d: P3.40 T3 band rank 1276; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801840D0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_717e9f7b: P3.40 T3 band rank 1277; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x4];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u8 pad3C[0x2];
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 unk42;
    /* 0x0043 */ u8 pad43[0x7];
    /* 0x004a */ u8 unk4A;
    /* 0x004b */ u8 pad4B[0x1];
} Unkstruct_80176218_14; /* size = 0x4c */

typedef struct {
    /* Unkstruct_752bee1e: P3.40 T3 band rank 1278; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017ED80_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_7bcac396: P3.40 T3 band rank 1279; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0xc6];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80180568; /* size = 0x100 */

typedef struct {
    /* Unkstruct_7ff48181: P3.40 T3 band rank 1280; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x197];
    /* 0x0197 */ u8 unk197;
    /* 0x0198 */ u8 pad198[0x9c];
    /* 0x0234 */ u16 unk234;
    /* 0x0236 */ u16 unk236;
    /* 0x0238 */ u16 unk238;
    /* 0x023a */ u16 unk23A;
} Unkstruct_800CB0B0; /* size = 0x23c */

typedef struct {
    /* Unkstruct_8012FB54: P3.40 T3 band rank 1282; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8c];
    /* 0x00ac */ u16 unkAC;
    /* 0x00ae */ u8 padAE[0x6];
    /* 0x00b4 */ s32 unkB4;
} Unkstruct_8012FB54; /* size = 0xb8 */

typedef struct {
    /* Unkstruct_801325B8: P3.40 T3 band rank 1283; 14 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_801325B8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_80143EBC: P3.40 T3 band rank 1284; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80143EBC; /* size = 0x1c */

typedef struct {
    /* Unkstruct_80164418: P3.40 T3 band rank 1285; 14 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_80164418; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8016D778: P3.40 T3 band rank 1286; 14 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
} Unkstruct_8016D778; /* size = 0x38 */

typedef struct {
    /* Unkstruct_80183814: P3.40 T3 band rank 1287; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x9a];
    /* 0x00aa */ u16 unkAA;
    /* 0x00ac */ u16 unkAC;
    /* 0x00ae */ u16 unkAE;
    /* 0x00b0 */ u8 padB0[0x154];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ s32 unk208;
} Unkstruct_80183814; /* size = 0x20c */

typedef struct {
    /* Unkstruct_816db408: P3.40 T3 band rank 1288; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x4c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x6];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80188AE4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_84847bcd: P3.40 T3 band rank 1289; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x74];
    /* 0x00dc */ u32 unkDC;
    /* 0x00e0 */ u32 unkE0;
    /* 0x00e4 */ u32 unkE4;
    /* 0x00e8 */ u32 unkE8;
    /* 0x00ec */ u8 padEC[0xc];
    /* 0x00f8 */ s32 unkF8;
} Unkstruct_801887A8; /* size = 0xfc */

typedef struct {
    /* Unkstruct_87debfca: P3.40 T3 band rank 1290; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ void * unk34;
} Unkstruct_800CAFA0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8e0cbd66: P3.40 T3 band rank 1292; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x28];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x3e];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x3];
} Unkstruct_8018036C; /* size = 0x78 */

typedef struct {
    /* Unkstruct_95d86c43: P3.40 T3 band rank 1294; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0xa8];
    /* 0x00e0 */ u32 unkE0;
} Unkstruct_80181F40; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_a4eefc31: P3.40 T3 band rank 1295; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ u8 pad100[0xa];
    /* 0x010a */ s16 unk10A;
} Unkstruct_801A5138; /* size = 0x10c */

typedef struct {
    /* Unkstruct_a676dcd2: P3.40 T3 band rank 1297; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_800CB3CC; /* size = 0x58 */

typedef struct {
    /* Unkstruct_aadc2a27: P3.40 T3 band rank 1298; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
} Unkstruct_80185520; /* size = 0x2c */

typedef struct {
    /* Unkstruct_aaf75fad: P3.40 T3 band rank 1299; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0xa8];
    /* 0x00e0 */ u32 unkE0;
} Unkstruct_80186858; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_b4867293: P3.40 T3 band rank 1300; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017BEF8_4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_bd433a07: P3.40 T3 band rank 1301; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0xa8];
    /* 0x00e0 */ u32 unkE0;
} Unkstruct_80182B74; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_bff02e0e: P3.40 T3 band rank 1302; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ u8 pad34[0x18];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_800CD314; /* size = 0x58 */

typedef struct {
    /* Unkstruct_ccb0b783: P3.40 T3 band rank 1303; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ s32 unkE4;
    /* 0x00e8 */ u8 padE8[0x16];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017D79C; /* size = 0x104 */

typedef struct {
    /* Unkstruct_d1717cc1: P3.40 T3 band rank 1304; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB68C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_d512a49b: P3.40 T3 band rank 1305; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DF5C_6; /* size = 0x38 */

typedef struct {
    /* Unkstruct_dc28137d: P3.40 T3 band rank 1306; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x32];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ u8 pad94[0x38];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80180DD8; /* size = 0x104 */

typedef struct {
    /* Unkstruct_e295fc6d: P3.40 T3 band rank 1307; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x6];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u8 pad2C[0x4];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB228; /* size = 0x38 */

typedef struct {
    /* Unkstruct_f30a0055: P3.40 T3 band rank 1309; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0xa8];
    /* 0x00e0 */ u32 unkE0;
} Unkstruct_80185E64; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_fd46ba46: P3.40 T3 band rank 1310; 14 TNC sites in 1 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x6c];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x48];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x1c];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80184A1C; /* size = 0x104 */

typedef struct {
    /* Unkstruct_2d4c10ce: P3.40 T3 band rank 1312; 13 TNC sites in 13 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80180B08; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_6c3d629b: P3.40 T3 band rank 1313; 13 TNC sites in 13 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb0];
    /* 0x00b0 */ s32 unkB0;
} Unkstruct_80180B08_2; /* size = 0xb4 */

typedef struct {
    /* Unkstruct_92c402ee: P3.40 T3 band rank 1314; 13 TNC sites in 8 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x3];
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 pad6[0x14];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0xa];
    /* 0x0026 */ s16 unk26;
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ u8 unk2A;
    /* 0x002b */ u8 pad2B[0x1];
} Unkstruct_8002C8F4; /* size = 0x2c */

typedef struct {
    /* Unkstruct_8012F274: P3.40 T3 band rank 1315; 13 TNC sites in 4 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80015954_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_d13bbdc9: P3.40 T3 band rank 1316; 13 TNC sites in 4 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB8A4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8017D060: P3.40 T3 band rank 1317; 13 TNC sites in 3 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xa];
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017D060; /* size = 0x38 */

typedef struct {
    /* Unkstruct_27677965: P3.40 T3 band rank 1318; 13 TNC sites in 2 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x24];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ u8 pad4C[0x18];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x96];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8018111C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_62f89823: P3.40 T3 band rank 1319; 13 TNC sites in 2 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_801E38B4; /* size = 0x10 */

typedef struct {
    /* Unkstruct_80149290: P3.40 T3 band rank 1320; 13 TNC sites in 2 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80149290; /* size = 0x24 */

typedef struct {
    /* Unkstruct_8014DF94: P3.40 T3 band rank 1321; 13 TNC sites in 2 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x78];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0xe2];
    /* 0x0170 */ s32 unk170;
} Unkstruct_8014DF94; /* size = 0x174 */

typedef struct {
    /* Unkstruct_b2ec798a: P3.40 T3 band rank 1322; 13 TNC sites in 2 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x3a];
    /* 0x0070 */ s8 unk70;
    /* 0x0071 */ u8 pad71[0x6b];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_8017F460; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_00d35f61: P3.40 T3 band rank 1323; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_80182B44; /* size = 0x38 */

typedef struct {
    /* Unkstruct_0c93be84: P3.40 T3 band rank 1324; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017D924; /* size = 0x100 */

typedef struct {
    /* Unkstruct_127c20f0: P3.40 T3 band rank 1325; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017FA00; /* size = 0x74 */

typedef struct {
    /* Unkstruct_12d5eb0f: P3.40 T3 band rank 1326; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x12];
    /* 0x0030 */ s32 unk30;
} Unkstruct_800CB6FC; /* size = 0x34 */

typedef struct {
    /* Unkstruct_14444989: P3.40 T3 band rank 1327; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x5c];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x1a];
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ u8 pad8C[0xc];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x42];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80182E54; /* size = 0x100 */

typedef struct {
    /* Unkstruct_17a4ec27: P3.40 T3 band rank 1328; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x12];
    /* 0x0030 */ s32 unk30;
} Unkstruct_800CB780; /* size = 0x34 */

typedef struct {
    /* Unkstruct_20b6f280: P3.40 T3 band rank 1329; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x16];
    /* 0x0036 */ u16 unk36;
    /* 0x0038 */ u8 pad38[0x4c];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x2];
} Unkstruct_8018139C; /* size = 0x88 */

typedef struct {
    /* Unkstruct_25c77a6c: P3.40 T3 band rank 1330; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80180B1C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_381553ef: P3.40 T3 band rank 1331; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd4];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x26];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x4];
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ s16 unk10A;
} Unkstruct_8017F9F8; /* size = 0x10c */

typedef struct {
    /* Unkstruct_48ecee82: P3.40 T3 band rank 1333; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017F26C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_4d0cabfe: P3.40 T3 band rank 1334; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_80181A30; /* size = 0x38 */

typedef struct {
    /* Unkstruct_5505f3cf: P3.40 T3 band rank 1335; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x12];
    /* 0x0030 */ s32 unk30;
} Unkstruct_800CB988; /* size = 0x34 */

typedef struct {
    /* Unkstruct_5a409cad: P3.40 T3 band rank 1336; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6c];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x4];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0xf];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x76];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017D564; /* size = 0x100 */

typedef struct {
    /* Unkstruct_80144988: P3.40 T3 band rank 1339; 13 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_80144988; /* size = 0x1c */

typedef struct {
    /* Unkstruct_80149228: P3.40 T3 band rank 1340; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xac];
    /* 0x00ac */ u16 unkAC;
    /* 0x00ae */ u8 padAE[0x12e];
    /* 0x01dc */ s32 unk1DC;
    /* 0x01e0 */ s32 unk1E0;
    /* 0x01e4 */ s16 unk1E4;
    /* 0x01e6 */ u16 unk1E6;
} Unkstruct_80149228; /* size = 0x1e8 */

typedef struct {
    /* Unkstruct_80152AC8: P3.40 T3 band rank 1341; 13 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80152AC8; /* size = 0x14 */

typedef struct {
    /* Unkstruct_80152C80: P3.40 T3 band rank 1342; 13 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80152C80; /* size = 0x14 */

typedef struct {
    /* Unkstruct_80152FBC: P3.40 T3 band rank 1343; 13 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80152FBC; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8015327C: P3.40 T3 band rank 1344; 13 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8015327C; /* size = 0x14 */

typedef struct {
    /* Unkstruct_80153550: P3.40 T3 band rank 1345; 13 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80153550; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8015E5B0: P3.40 T3 band rank 1346; 13 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8015E5B0; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8016432C: P3.40 T3 band rank 1347; 13 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4c];
    /* 0x004c */ s32 unk4C;
} Unkstruct_8016432C; /* size = 0x50 */

typedef struct {
    /* Unkstruct_80169058: P3.40 T3 band rank 1348; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ s32 unk2C;
} Unkstruct_80169058_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_80169E44: P3.40 T3 band rank 1349; 13 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
} Unkstruct_80169E44; /* size = 0x1c */

typedef struct {
    /* Unkstruct_8017E404: P3.40 T3 band rank 1351; 13 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_8017E404; /* size = 0x10 */

typedef struct {
    /* Unkstruct_831d7626: P3.40 T3 band rank 1352; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x1a];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x58];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x24];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8018164C; /* size = 0x104 */

typedef struct {
    /* Unkstruct_850152e8: P3.40 T3 band rank 1353; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3];
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80180780; /* size = 0x30 */

typedef struct {
    /* Unkstruct_88698751: P3.40 T3 band rank 1354; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x1a];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0x14];
    /* 0x0068 */ s32 unk68;
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ s32 unk70;
} Unkstruct_801A5194_2; /* size = 0x74 */

typedef struct {
    /* Unkstruct_8b7c03b1: P3.40 T3 band rank 1355; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x4];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x64];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x1c];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80186668; /* size = 0x104 */

typedef struct {
    /* Unkstruct_8f7087f8: P3.40 T3 band rank 1356; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ void * unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80182080; /* size = 0x18 */

typedef struct {
    /* Unkstruct_95572fbb: P3.40 T3 band rank 1357; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 unkE;
    /* 0x000f */ u8 unkF;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 unk14;
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 unk16;
    /* 0x0017 */ u8 pad17[0x1];
} Unkstruct_8001E7E0; /* size = 0x18 */

typedef struct {
    /* Unkstruct_9692d5cd: P3.40 T3 band rank 1358; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_800CBCD4; /* size = 0x18 */

typedef struct {
    /* Unkstruct_9fd4c30d: P3.40 T3 band rank 1359; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0xe];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_800CB300; /* size = 0x30 */

typedef struct {
    /* Unkstruct_a7c7ef1e: P3.40 T3 band rank 1360; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x6];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0xc];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x72];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017ED0C; /* size = 0x104 */

typedef struct {
    /* Unkstruct_a9f85bea: P3.40 T3 band rank 1361; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_801856A8; /* size = 0x68 */

typedef struct {
    /* Unkstruct_ac014cfb: P3.40 T3 band rank 1362; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80188094; /* size = 0x30 */

typedef struct {
    /* Unkstruct_b231e0d2: P3.40 T3 band rank 1363; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x6];
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801A7B08; /* size = 0x30 */

typedef struct {
    /* Unkstruct_b8ee369e: P3.40 T3 band rank 1365; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x12];
    /* 0x0030 */ s32 unk30;
} Unkstruct_800CBA0C; /* size = 0x34 */

typedef struct {
    /* Unkstruct_b9a191e3: P3.40 T3 band rank 1366; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801807DC_2; /* size = 0x104 */

typedef struct {
    /* Unkstruct_bbda9820: P3.40 T3 band rank 1367; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xdc];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u16 unk102;
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u16 unk106;
    /* 0x0108 */ u16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_8017D4AC; /* size = 0x10c */

typedef struct {
    /* Unkstruct_bd7fd1da: P3.40 T3 band rank 1368; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017DA08_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_bee7cd42: P3.40 T3 band rank 1369; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x6];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0xc];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x72];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80186D20; /* size = 0x104 */

typedef struct {
    /* Unkstruct_c496aba3: P3.40 T3 band rank 1370; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017FCD0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_d4ff024c: P3.40 T3 band rank 1371; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017F154; /* size = 0x30 */

typedef struct {
    /* Unkstruct_dcd970c9: P3.40 T3 band rank 1372; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x54];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x67];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u16 unkE0;
    /* 0x00e2 */ u8 padE2[0x1a];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80182CA4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_e20df749: P3.40 T3 band rank 1373; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x1a];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x58];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x24];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017F794; /* size = 0x104 */

typedef struct {
    /* Unkstruct_e70b3bf7: P3.40 T3 band rank 1374; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x36];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x5c];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x4];
    /* 0x00d8 */ s32 unkD8;
} Unkstruct_80185380; /* size = 0xdc */

typedef struct {
    /* Unkstruct_e79def2b: P3.40 T3 band rank 1375; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017F6D8_3; /* size = 0x30 */

typedef struct {
    /* Unkstruct_e8825d7e: P3.40 T3 band rank 1376; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8018D7B4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ed8bbfcb: P3.40 T3 band rank 1377; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0xf6];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ s16 unk102;
} Unkstruct_801821DC; /* size = 0x104 */

typedef struct {
    /* Unkstruct_f2f45e97: P3.40 T3 band rank 1378; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8018797C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_f6ea8157: P3.40 T3 band rank 1379; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0xe];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB138; /* size = 0x38 */

typedef struct {
    /* Unkstruct_f810c15e: P3.40 T3 band rank 1380; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x5c];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x1a];
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ u8 pad8C[0xc];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x42];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80183FF8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_251ec6f2: P3.40 T3 band rank 1381; 12 TNC sites in 12 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80169FE0; /* size = 0x24 */

typedef struct {
    /* Unkstruct_5d09b9c5: P3.40 T3 band rank 1382; 12 TNC sites in 12 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_801E2F58; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8905aeec: P3.40 T3 band rank 1383; 12 TNC sites in 12 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CB7F0; /* size = 0x24 */

typedef struct {
    /* Unkstruct_ef20b21c: P3.40 T3 band rank 1384; 12 TNC sites in 12 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
} Unkstruct_8017E62C_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_033cac2e: P3.40 T3 band rank 1385; 12 TNC sites in 8 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x1e0];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ s16 unk208;
    /* 0x020a */ u8 pad20A[0x6];
    /* 0x0210 */ s16 unk210;
    /* 0x0212 */ u8 pad212[0x2];
} Unkstruct_8017E6A4_2; /* size = 0x214 */

typedef struct {
    /* Unkstruct_262174be: P3.40 T3 band rank 1387; 12 TNC sites in 6 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ s32 unk2C;
} Unkstruct_80168D94; /* size = 0x30 */

typedef struct {
    /* Unkstruct_420d9d57: P3.40 T3 band rank 1388; 12 TNC sites in 6 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd4];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ s32 unkD8;
} Unkstruct_8017BF34; /* size = 0xdc */

typedef struct {
    /* Unkstruct_c3f8c316: P3.40 T3 band rank 1390; 12 TNC sites in 6 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_801809E8_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_c8c82228: P3.40 T3 band rank 1391; 12 TNC sites in 6 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_801810CC_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_d0ccd528: P3.40 T3 band rank 1392; 12 TNC sites in 6 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8015D380_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_f6186e59: P3.40 T3 band rank 1393; 12 TNC sites in 6 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_8015D380_4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_060ad5fb: P3.40 T3 band rank 1394; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
} Unkstruct_8018241C; /* size = 0xc */

typedef struct {
    /* Unkstruct_0f5e6903: P3.40 T3 band rank 1396; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xf8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801857AC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_210d7138: P3.40 T3 band rank 1397; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017E3F0; /* size = 0x10 */

typedef struct {
    /* Unkstruct_26f62321: P3.40 T3 band rank 1398; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ s16 unk62;
    /* 0x0064 */ s16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_8017E778_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_2837a77b: P3.40 T3 band rank 1399; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_8017CABC_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_38aa232e: P3.40 T3 band rank 1400; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x6a];
    /* 0x00dc */ void * unkDC;
} Unkstruct_8017C234_2; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_44dca889: P3.40 T3 band rank 1401; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
} Unkstruct_8017E520_2; /* size = 0x5c */

typedef struct {
    /* Unkstruct_4ae06554: P3.40 T3 band rank 1402; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8017CB10; /* size = 0x1c */

typedef struct {
    /* Unkstruct_62f0f31c: P3.40 T3 band rank 1405; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017D588; /* size = 0x2c */

typedef struct {
    /* Unkstruct_661472cb: P3.40 T3 band rank 1406; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017E800_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_72f09473: P3.40 T3 band rank 1407; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
} Unkstruct_80182038; /* size = 0xc */

typedef struct {
    /* Unkstruct_73782c2f: P3.40 T3 band rank 1408; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80184944; /* size = 0x24 */

typedef struct {
    /* Unkstruct_778c4bd1: P3.40 T3 band rank 1409; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x32];
    /* 0x0052 */ u16 unk52;
} Unkstruct_8017DC44; /* size = 0x54 */

typedef struct {
    /* Unkstruct_8014A238: P3.40 T3 band rank 1410; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8014C2B0; /* size = 0x24 */

typedef struct {
    /* Unkstruct_82763c45: P3.40 T3 band rank 1411; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_8017DD0C; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_8bba59d8: P3.40 T3 band rank 1412; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_80180FB8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_a148f540: P3.40 T3 band rank 1415; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_80182358; /* size = 0x10 */

typedef struct {
    /* Unkstruct_b02d5cf5: P3.40 T3 band rank 1416; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
} Unkstruct_80181AD0_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_b7f46087: P3.40 T3 band rank 1417; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017F200_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_b9ff3f4f: P3.40 T3 band rank 1418; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_80180814; /* size = 0x60 */

typedef struct {
    /* Unkstruct_c0793fe6: P3.40 T3 band rank 1419; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017CABC_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_c77b0c7a: P3.40 T3 band rank 1420; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x18];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 pad24[0x3];
    /* 0x0027 */ u8 unk27;
} Unkstruct_80183650_2; /* size = 0x28 */

typedef struct {
    /* Unkstruct_cff4a9b7: P3.40 T3 band rank 1421; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017C234_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_d950796b: P3.40 T3 band rank 1422; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
} Unkstruct_8016C49C_6; /* size = 0x1c */

typedef struct {
    /* Unkstruct_e46c3995: P3.40 T3 band rank 1423; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017D408_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_e5179617: P3.40 T3 band rank 1424; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8015D738_9; /* size = 0x14 */

typedef struct {
    /* Unkstruct_e595cd7c: P3.40 T3 band rank 1425; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_801806B4; /* size = 0x20 */

typedef struct {
    /* Unkstruct_e923d23e: P3.40 T3 band rank 1426; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801E2D58; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_ffbaa385: P3.40 T3 band rank 1427; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ void * unk20;
} Unkstruct_8017D890_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_0863226d: P3.40 T3 band rank 1428; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ s32 unk28;
} Unkstruct_80176218_15; /* size = 0x2c */

typedef struct {
    /* Unkstruct_1cac4eee: P3.40 T3 band rank 1430; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
} Unkstruct_8018D674; /* size = 0x20 */

typedef struct {
    /* Unkstruct_3bf51b83: P3.40 T3 band rank 1432; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
} Unkstruct_8016E728_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_469ff04b: P3.40 T3 band rank 1433; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
} Unkstruct_8017C8B0; /* size = 0x8 */

typedef struct {
    /* Unkstruct_47310de0: P3.40 T3 band rank 1434; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
} Unkstruct_8017DAB8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_557374b8: P3.40 T3 band rank 1435; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
} Unkstruct_8017E9E8; /* size = 0x8 */

typedef struct {
    /* Unkstruct_624a5139: P3.40 T3 band rank 1436; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801E2E04; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_66a62d05: P3.40 T3 band rank 1437; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
} Unkstruct_8013AD38_5; /* size = 0x4 */

typedef struct {
    /* Unkstruct_6b193407: P3.40 T3 band rank 1438; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8017BB34_3; /* size = 0x10 */

typedef struct {
    /* Unkstruct_900296ab: P3.40 T3 band rank 1439; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801872D8_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_d512cb89: P3.40 T3 band rank 1440; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3e];
    /* 0x0062 */ u16 unk62;
} Unkstruct_8017E71C; /* size = 0x64 */

typedef struct {
    /* Unkstruct_d6c1a7dd: P3.40 T3 band rank 1441; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017E69C; /* size = 0x2c */

typedef struct {
    /* Unkstruct_e7e98ad9: P3.40 T3 band rank 1443; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017E634_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_eed2d08e: P3.40 T3 band rank 1444; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_801312D0_4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_0ae90e3d: P3.40 T3 band rank 1445; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E2EC0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_1ab05c25: P3.40 T3 band rank 1446; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x94];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x62];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80182380; /* size = 0x100 */

typedef struct {
    /* Unkstruct_1c90124a: P3.40 T3 band rank 1447; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
} Unkstruct_801877B8; /* size = 0xc */

typedef struct {
    /* Unkstruct_33c37bb4: P3.40 T3 band rank 1448; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017CFBC; /* size = 0x34 */

typedef struct {
    /* Unkstruct_688c4b2b: P3.40 T3 band rank 1449; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x12];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CAFA8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8012ACA0: P3.40 T3 band rank 1450; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x72];
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x1c];
    /* 0x0090 */ void * unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x2];
    /* 0x009a */ s16 unk9A;
    /* 0x009c */ s32 unk9C;
} Unkstruct_8012ACA0_3; /* size = 0xa0 */

typedef struct {
    /* Unkstruct_80142EC0: P3.40 T3 band rank 1451; 12 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80142EC0_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_80146578: P3.40 T3 band rank 1452; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0xb];
    /* 0x0027 */ u8 unk27;
} Unkstruct_800CDAB4; /* size = 0x28 */

typedef struct {
    /* Unkstruct_80160D10: P3.40 T3 band rank 1453; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x42];
    /* 0x0044 */ u32 unk44;
    /* 0x0048 */ u8 pad48[0x164];
    /* 0x01ac */ s32 unk1AC;
} Unkstruct_80160D10; /* size = 0x1b0 */

typedef struct {
    /* Unkstruct_8016EB3C: P3.40 T3 band rank 1454; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 pad3[0x1];
} Unkstruct_8016EB3C_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_92c41126: P3.40 T3 band rank 1456; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
} Unkstruct_8017FE9C; /* size = 0x30 */

typedef struct {
    /* Unkstruct_b131d1c9: P3.40 T3 band rank 1457; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u8 pad2A[0x2];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CAF84; /* size = 0x38 */

typedef struct {
    /* Unkstruct_bab14d81: P3.40 T3 band rank 1458; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80182D04; /* size = 0x100 */

typedef struct {
    /* Unkstruct_04d66b95: P3.40 T3 band rank 1459; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0xc6];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0xc];
    /* 0x010a */ s16 unk10A;
} Unkstruct_80185744; /* size = 0x10c */

typedef struct {
    /* Unkstruct_0880cc51: P3.40 T3 band rank 1460; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x32];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_80186518_2; /* size = 0x54 */

typedef struct {
    /* Unkstruct_0bb2ec4f: P3.40 T3 band rank 1461; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017FBE8_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_0c533db0: P3.40 T3 band rank 1462; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xe];
    /* 0x002e */ s16 unk2E;
} Unkstruct_80185B78; /* size = 0x30 */

typedef struct {
    /* Unkstruct_1284bfec: P3.40 T3 band rank 1464; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x64];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x46];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_801ABEE0; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_14456127: P3.40 T3 band rank 1465; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801AC150; /* size = 0x30 */

typedef struct {
    /* Unkstruct_27104fdd: P3.40 T3 band rank 1467; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x38];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x56];
    /* 0x0102 */ s16 unk102;
} Unkstruct_80186144; /* size = 0x104 */

typedef struct {
    /* Unkstruct_2d71c45b: P3.40 T3 band rank 1469; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x10];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x30];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x20];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_801896EC; /* size = 0x108 */

typedef struct {
    /* Unkstruct_32f6aa1b: P3.40 T3 band rank 1470; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0xae];
    /* 0x00e4 */ s32 unkE4;
    /* 0x00e8 */ s32 unkE8;
    /* 0x00ec */ u8 padEC[0x8];
    /* 0x00f4 */ s32 unkF4;
    /* 0x00f8 */ s32 unkF8;
} Unkstruct_801803AC; /* size = 0xfc */

typedef struct {
    /* Unkstruct_366f4902: P3.40 T3 band rank 1471; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x8c];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017EAD8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_39c20c19: P3.40 T3 band rank 1472; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
} Unkstruct_8017DA30; /* size = 0xc */

typedef struct {
    /* Unkstruct_3e02d9b0: P3.40 T3 band rank 1474; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x10];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x30];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x20];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_8017E418; /* size = 0x108 */

typedef struct {
    /* Unkstruct_41259856: P3.40 T3 band rank 1476; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x60];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x1a];
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u8 pad8C[0x70];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017E3F8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_4574a649: P3.40 T3 band rank 1477; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0x24];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u8 pad64[0x12];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ u8 pad78[0x4];
    /* 0x007c */ u16 unk7C;
    /* 0x007e */ u16 unk7E;
    /* 0x0080 */ u16 unk80;
    /* 0x0082 */ u8 pad82[0x3f];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80181EC0; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_486e29dc: P3.40 T3 band rank 1479; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x60];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017ED94; /* size = 0x74 */

typedef struct {
    /* Unkstruct_5c683fed: P3.40 T3 band rank 1482; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017EB78; /* size = 0x1c */

typedef struct {
    /* Unkstruct_613e79a6: P3.40 T3 band rank 1483; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ void * unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x7];
    /* 0x0037 */ u8 unk37;
    /* 0x0038 */ u8 unk38;
    /* 0x0039 */ u8 pad39[0x3];
} Unkstruct_80031988; /* size = 0x3c */

typedef struct {
    /* Unkstruct_6163e9cd: P3.40 T3 band rank 1484; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xb8];
    /* 0x00dc */ u16 unkDC;
    /* 0x00de */ u8 padDE[0x1e];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ s16 unk102;
} Unkstruct_8017F8C0; /* size = 0x104 */

typedef struct {
    /* Unkstruct_6b51180d: P3.40 T3 band rank 1485; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
} Unkstruct_8001E668; /* size = 0xc */

typedef struct {
    /* Unkstruct_6be86b17: P3.40 T3 band rank 1486; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x10];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x30];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x20];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_8017EAD8_2; /* size = 0x108 */

typedef struct {
    /* Unkstruct_6c4ef16a: P3.40 T3 band rank 1487; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xac];
    /* 0x00d0 */ void * unkD0;
    /* 0x00d4 */ void * unkD4;
} Unkstruct_80187D68; /* size = 0xd8 */

typedef struct {
    /* Unkstruct_76c4a960: P3.40 T3 band rank 1489; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x48];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x17];
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ u8 pad76[0x38];
    /* 0x00ae */ s16 unkAE;
    /* 0x00b0 */ u8 padB0[0x4];
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u8 padB8[0x4];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 unkC0;
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
    /* 0x00c4 */ u32 unkC4;
} Unkstruct_8018C14C; /* size = 0xc8 */

typedef struct {
    /* Unkstruct_79d93a54: P3.40 T3 band rank 1490; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ u16 unkDC;
    /* 0x00de */ u16 unkDE;
    /* 0x00e0 */ u16 unkE0;
    /* 0x00e2 */ u16 unkE2;
} Unkstruct_8017E830; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_7caa7a07: P3.40 T3 band rank 1491; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_801407F4_5; /* size = 0x20 */

typedef struct {
    /* Unkstruct_80134C20: P3.40 T3 band rank 1492; 12 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80134C20_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_80147AD4: P3.40 T3 band rank 1493; 12 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
} Unkstruct_80147B5C; /* size = 0xc */

typedef struct {
    /* Unkstruct_801490F8: P3.40 T3 band rank 1494; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x100];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ s16 unk102;
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ s16 unk10A;
    /* 0x010c */ s16 unk10C;
    /* 0x010e */ u8 pad10E[0x2];
} Unkstruct_801490F8; /* size = 0x110 */

typedef struct {
    /* Unkstruct_8014B190: P3.40 T3 band rank 1495; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x42];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ u8 pad48[0x20];
    /* 0x0068 */ s16 unk68;
    /* 0x006a */ s16 unk6A;
    /* 0x006c */ s16 unk6C;
    /* 0x006e */ u8 pad6E[0x2];
} Unkstruct_8014B190; /* size = 0x70 */

typedef struct {
    /* Unkstruct_8014FC18: P3.40 T3 band rank 1496; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x15c];
    /* 0x016c */ s16 unk16C;
    /* 0x016e */ s16 unk16E;
} Unkstruct_8014FC18; /* size = 0x170 */

typedef struct {
    /* Unkstruct_80152790: P3.40 T3 band rank 1497; 12 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80152790; /* size = 0x14 */

typedef struct {
    /* Unkstruct_87e6f11a: P3.40 T3 band rank 1499; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ void * unk34;
} Unkstruct_800CB1EC; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8835c7dd: P3.40 T3 band rank 1500; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x44];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ s32 unkD8;
    /* 0x00dc */ u8 padDC[0x22];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801884AC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_8fa685cb: P3.40 T3 band rank 1501; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017F5D8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_90949990: P3.40 T3 band rank 1502; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xbc];
    /* 0x00e0 */ u16 unkE0;
    /* 0x00e2 */ u16 unkE2;
    /* 0x00e4 */ u16 unkE4;
    /* 0x00e6 */ u8 padE6[0x2];
} Unkstruct_8017DEF0; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_973a4ec7: P3.40 T3 band rank 1503; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
} Unkstruct_8018D870_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_983100bc: P3.40 T3 band rank 1504; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x6];
    /* 0x0034 */ s32 unk34;
} Unkstruct_801A7200; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ac3bf629: P3.40 T3 band rank 1508; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017F27C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_ae0bb75c: P3.40 T3 band rank 1509; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
} Unkstruct_8017D8A4; /* size = 0xc */

typedef struct {
    /* Unkstruct_b3b748f4: P3.40 T3 band rank 1510; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x58];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0xc];
    /* 0x00dc */ u16 unkDC;
    /* 0x00de */ u16 unkDE;
} Unkstruct_801855EC; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_b5cc2bd1: P3.40 T3 band rank 1511; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ u32 unk1C;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_800CB2AC; /* size = 0x34 */

typedef struct {
    /* Unkstruct_bb03db5f: P3.40 T3 band rank 1512; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ u8 padDE[0x2];
} Unkstruct_801808B8; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_c5ab3889: P3.40 T3 band rank 1514; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x20];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
} Unkstruct_8018537C; /* size = 0x50 */

typedef struct {
    /* Unkstruct_cac7cf16: P3.40 T3 band rank 1516; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u16 unk36;
} Unkstruct_8017FE0C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_cd20be21: P3.40 T3 band rank 1518; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_801407F4_6; /* size = 0x20 */

typedef struct {
    /* Unkstruct_d28af915: P3.40 T3 band rank 1520; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u32 unk14;
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u32 unk1C;
    /* 0x0020 */ u16 unk20;
    /* 0x0022 */ u16 unk22;
} Unkstruct_8017FD14; /* size = 0x24 */

typedef struct {
    /* Unkstruct_dbaaae20: P3.40 T3 band rank 1521; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u32 unk10;
    /* 0x0014 */ u32 unk14;
    /* 0x0018 */ u32 unk18;
} Unkstruct_8017C954; /* size = 0x1c */

typedef struct {
    /* Unkstruct_e51b12fe: P3.40 T3 band rank 1522; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x38];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x56];
    /* 0x0102 */ s16 unk102;
} Unkstruct_8017E130; /* size = 0x104 */

typedef struct {
    /* Unkstruct_e743637d: P3.40 T3 band rank 1523; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x6];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_80186070; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_fbf8ca27: P3.40 T3 band rank 1524; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x63];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80182780; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_fdc967cd: P3.40 T3 band rank 1525; 12 TNC sites in 1 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x50];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x67];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801811E0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_19f70992: P3.40 T3 band rank 1526; 11 TNC sites in 11 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x216];
    /* 0x0216 */ u8 unk216;
    /* 0x0217 */ u8 pad217[0x1];
} Unkstruct_80170748; /* size = 0x218 */

typedef struct {
    /* Unkstruct_cef068ce: P3.40 T3 band rank 1527; 11 TNC sites in 11 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb0];
    /* 0x00b0 */ s32 unkB0;
} Unkstruct_8018069C; /* size = 0xb4 */

typedef struct {
    /* Unkstruct_fde49abf: P3.40 T3 band rank 1528; 11 TNC sites in 11 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8017D8B0; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_8790e462: P3.40 T3 band rank 1529; 11 TNC sites in 6 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_801E2D50; /* size = 0x8 */

typedef struct {
    /* Unkstruct_320604e3: P3.40 T3 band rank 1530; 11 TNC sites in 3 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x28];
    /* 0x0034 */ void * unk34;
    /* 0x0038 */ u16 unk38;
    /* 0x003a */ u8 pad3A[0x2];
    /* 0x003c */ s32 unk3C;
    /* 0x0040 */ s32 unk40;
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_80180F38; /* size = 0x58 */

typedef struct {
    /* Unkstruct_8017C294: P3.40 T3 band rank 1531; 11 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017C294; /* size = 0x20 */

typedef struct {
    /* Unkstruct_21610a20: P3.40 T3 band rank 1532; 11 TNC sites in 2 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xd8];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ s32 unkE4;
    /* 0x00e8 */ u8 padE8[0x16];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ u8 pad100[0x4];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_80182D60; /* size = 0x108 */

typedef struct {
    /* Unkstruct_511f884b: P3.40 T3 band rank 1533; 11 TNC sites in 2 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_800CCDD8; /* size = 0x30 */

typedef struct {
    /* Unkstruct_564f88ec: P3.40 T3 band rank 1534; 11 TNC sites in 2 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x18];
    /* 0x00e8 */ u16 unkE8;
    /* 0x00ea */ u8 padEA[0x16];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_801870BC; /* size = 0x108 */

typedef struct {
    /* Unkstruct_0148fdb9: P3.40 T3 band rank 1537; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ void * unk0;
    /* 0x0004 */ u8 pad4[0x1e2];
    /* 0x01e6 */ u16 unk1E6;
} Unkstruct_80038698; /* size = 0x1e8 */

typedef struct {
    /* Unkstruct_0199ed36: P3.40 T3 band rank 1538; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
} Unkstruct_801AC9CC; /* size = 0x34 */

typedef struct {
    /* Unkstruct_09903e63: P3.40 T3 band rank 1540; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_801850B4; /* size = 0x20 */

typedef struct {
    /* Unkstruct_10b484e5: P3.40 T3 band rank 1542; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u16 unk36;
    /* 0x0038 */ u16 unk38;
    /* 0x003a */ u8 pad3A[0x2];
} Unkstruct_801847B8; /* size = 0x3c */

typedef struct {
    /* Unkstruct_1348690e: P3.40 T3 band rank 1543; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x3];
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u8 pad32[0x2];
} Unkstruct_8001E7E0_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_13f561ce: P3.40 T3 band rank 1544; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017F32C; /* size = 0x34 */

typedef struct {
    /* Unkstruct_15bbf9df: P3.40 T3 band rank 1545; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x70];
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x46];
    /* 0x00e0 */ s32 unkE0;
} Unkstruct_801A143C; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_16216bd1: P3.40 T3 band rank 1546; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xcc];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8017DC50; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_18077216: P3.40 T3 band rank 1547; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x1a];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x58];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x24];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80184374; /* size = 0x104 */

typedef struct {
    /* Unkstruct_1841e3d2: P3.40 T3 band rank 1548; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8018BED0; /* size = 0x8 */

typedef struct {
    /* Unkstruct_1b66e18d: P3.40 T3 band rank 1551; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80180850_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2df26cae: P3.40 T3 band rank 1554; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0xa6];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_80181B68; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_2feb4547: P3.40 T3 band rank 1555; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_801A4ACC_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_32e6160f: P3.40 T3 band rank 1556; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x24];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ u8 pad4C[0x18];
    /* 0x0064 */ void * unk64;
    /* 0x0068 */ u8 pad68[0x28];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ u8 pad94[0x4];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_8018A314; /* size = 0x9c */

typedef struct {
    /* Unkstruct_352e1bfb: P3.40 T3 band rank 1558; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017CE90_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_39cee70d: P3.40 T3 band rank 1559; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80183F3C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_3fd41a25: P3.40 T3 band rank 1560; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_800CD884; /* size = 0x20 */

typedef struct {
    /* Unkstruct_56e5f18d: P3.40 T3 band rank 1561; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x10];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x54];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ s16 unk106;
} Unkstruct_8017EC00; /* size = 0x108 */

typedef struct {
    /* Unkstruct_596100e0: P3.40 T3 band rank 1562; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x94];
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u8 padBA[0x152];
    /* 0x020c */ u16 unk20C;
    /* 0x020e */ u16 unk20E;
    /* 0x0210 */ u16 unk210;
    /* 0x0212 */ u8 pad212[0x2];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8017FC64; /* size = 0x218 */

typedef struct {
    /* Unkstruct_5a5806c6: P3.40 T3 band rank 1563; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80187D68_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_5bfa0c36: P3.40 T3 band rank 1564; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8018B7F8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_679e688a: P3.40 T3 band rank 1565; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8018A860; /* size = 0x10 */

typedef struct {
    /* Unkstruct_6c79da93: P3.40 T3 band rank 1566; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80185458; /* size = 0x10 */

typedef struct {
    /* Unkstruct_6ca32a4c: P3.40 T3 band rank 1567; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u16 unk1E;
} Unkstruct_800CD054; /* size = 0x20 */

typedef struct {
    /* Unkstruct_6da9d6cb: P3.40 T3 band rank 1568; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x10];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x30];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x20];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_80180530; /* size = 0x108 */

typedef struct {
    /* Unkstruct_71ff8b80: P3.40 T3 band rank 1569; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xbc];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x4];
    /* 0x00e8 */ s32 unkE8;
} Unkstruct_80180F60; /* size = 0xec */

typedef struct {
    /* Unkstruct_75700975: P3.40 T3 band rank 1570; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x6e];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801843C0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_795fdfb3: P3.40 T3 band rank 1571; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x2c];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ u8 pad4C[0x80];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80186C4C; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_7a8b97b2: P3.40 T3 band rank 1572; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80185C00; /* size = 0x10 */

typedef struct {
    /* Unkstruct_7ee684e6: P3.40 T3 band rank 1573; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x74];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x56];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ s16 unkDE;
} Unkstruct_8018031C; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_7f0d0f0b: P3.40 T3 band rank 1574; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8018570C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_80151664: P3.40 T3 band rank 1575; 11 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80151664; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8015E40C: P3.40 T3 band rank 1576; 11 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18c];
    /* 0x018c */ s32 unk18C;
} Unkstruct_8015E40C; /* size = 0x190 */

typedef struct {
    /* Unkstruct_8017C69C: P3.40 T3 band rank 1577; 11 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_8017C69C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_8017C730: P3.40 T3 band rank 1578; 11 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017C730; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8017D4B4: P3.40 T3 band rank 1579; 11 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_8017D4B4; /* size = 0x68 */

typedef struct {
    /* Unkstruct_8017D57C: P3.40 T3 band rank 1580; 11 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_8017D57C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_8017D778: P3.40 T3 band rank 1581; 11 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_8017D778; /* size = 0x68 */

typedef struct {
    /* Unkstruct_8017D88C: P3.40 T3 band rank 1582; 11 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_8017D88C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_8017E394: P3.40 T3 band rank 1583; 11 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_8017E394_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_8017E6B0: P3.40 T3 band rank 1584; 11 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ u16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_8017E6B0; /* size = 0x68 */

typedef struct {
    /* Unkstruct_80180B84: P3.40 T3 band rank 1585; 11 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2c];
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0x4];
    /* 0x0058 */ s32 unk58;
} Unkstruct_80180B84; /* size = 0x5c */

typedef struct {
    /* Unkstruct_803d7ccb: P3.40 T3 band rank 1587; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_800CBD90; /* size = 0x28 */

typedef struct {
    /* Unkstruct_81c01ca9: P3.40 T3 band rank 1588; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8018B028; /* size = 0x8 */

typedef struct {
    /* Unkstruct_844eaa16: P3.40 T3 band rank 1589; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x1a];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0x94];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8018E9BC; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_859951da: P3.40 T3 band rank 1590; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x3a];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x5e];
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0xc];
    /* 0x00e0 */ s32 unkE0;
} Unkstruct_80187038; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_86d76362: P3.40 T3 band rank 1591; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa];
    /* 0x002e */ s16 unk2E;
} Unkstruct_801813D0; /* size = 0x30 */

typedef struct {
    /* Unkstruct_8a4a5fbb: P3.40 T3 band rank 1592; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017CE90_3; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8ae88080: P3.40 T3 band rank 1593; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x10];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x54];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ s16 unk106;
} Unkstruct_80183DD4; /* size = 0x108 */

typedef struct {
    /* Unkstruct_8afa63cb: P3.40 T3 band rank 1594; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xbc];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x4];
    /* 0x00e8 */ s32 unkE8;
} Unkstruct_80180E58; /* size = 0xec */

typedef struct {
    /* Unkstruct_8b3486d2: P3.40 T3 band rank 1595; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80184774; /* size = 0x10 */

typedef struct {
    /* Unkstruct_92e55ccd: P3.40 T3 band rank 1598; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017F47C; /* size = 0x30 */

typedef struct {
    /* Unkstruct_99aecb33: P3.40 T3 band rank 1600; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80183AF8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_99afef23: P3.40 T3 band rank 1601; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
} Unkstruct_8013C414_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_9a0fe437: P3.40 T3 band rank 1602; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x14];
    /* 0x0086 */ s16 unk86;
    /* 0x0088 */ u8 pad88[0x2c];
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u8 padB8[0x4];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ s8 unkC0;
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80183B58; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_a22f5b19: P3.40 T3 band rank 1603; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2e];
    /* 0x0052 */ u16 unk52;
    /* 0x0054 */ u8 pad54[0x7c];
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_8018247C; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_a3eef837: P3.40 T3 band rank 1604; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8018454C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_a766b421: P3.40 T3 band rank 1605; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0xc];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0xa];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x5];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801AF368_4; /* size = 0x30 */

typedef struct {
    /* Unkstruct_ac9b50be: P3.40 T3 band rank 1607; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80181ABC_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_ad1be4aa: P3.40 T3 band rank 1608; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8018E1F0; /* size = 0x10 */

typedef struct {
    /* Unkstruct_b45cf7ff: P3.40 T3 band rank 1609; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8018478C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_be916389: P3.40 T3 band rank 1610; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa];
    /* 0x002e */ s16 unk2E;
} Unkstruct_80180628; /* size = 0x30 */

typedef struct {
    /* Unkstruct_bfc7363b: P3.40 T3 band rank 1611; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80186938; /* size = 0x10 */

typedef struct {
    /* Unkstruct_c29b7e2c: P3.40 T3 band rank 1612; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
} Unkstruct_8003602C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_c773b252: P3.40 T3 band rank 1613; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xdc];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80188BEC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_c7daf3f3: P3.40 T3 band rank 1614; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8018A8E8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_cb4d8913: P3.40 T3 band rank 1615; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0xc6];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801819B8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_cdeb5be1: P3.40 T3 band rank 1616; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x68];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x52];
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x1a];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80182D70; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d405cd40: P3.40 T3 band rank 1617; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xdc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80181148; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d4cbdca3: P3.40 T3 band rank 1618; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ u32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x5e];
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x4e];
    /* 0x00e8 */ u32 unkE8;
} Unkstruct_80181BE8; /* size = 0xec */

typedef struct {
    /* Unkstruct_d560d36c: P3.40 T3 band rank 1619; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x1a];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x58];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x24];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80183088; /* size = 0x104 */

typedef struct {
    /* Unkstruct_dbaa7154: P3.40 T3 band rank 1620; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0xc4];
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x6];
    /* 0x00e8 */ s32 unkE8;
} Unkstruct_80182810; /* size = 0xec */

typedef struct {
    /* Unkstruct_de093421: P3.40 T3 band rank 1621; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8018201C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_de64d3f4: P3.40 T3 band rank 1622; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_80188C04; /* size = 0x8 */

typedef struct {
    /* Unkstruct_dff1fce1: P3.40 T3 band rank 1623; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80181970; /* size = 0x10 */

typedef struct {
    /* Unkstruct_e2c0b690: P3.40 T3 band rank 1624; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3e];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x10];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x30];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017D4CC; /* size = 0x104 */

typedef struct {
    /* Unkstruct_fb8516db: P3.40 T3 band rank 1627; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xe0];
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u16 unk106;
    /* 0x0108 */ u16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_801853D0; /* size = 0x10c */

typedef struct {
    /* Unkstruct_fbaf8a7b: P3.40 T3 band rank 1628; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x1a];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x58];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x24];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017FC14; /* size = 0x104 */

typedef struct {
    /* Unkstruct_504621c1: P3.40 T3 band rank 1629; 10 TNC sites in 10 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x70];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017D6B0; /* size = 0x74 */

typedef struct {
    /* Unkstruct_9550c910: P3.40 T3 band rank 1630; 10 TNC sites in 10 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb0];
    /* 0x00b0 */ s32 unkB0;
} Unkstruct_80180B18; /* size = 0xb4 */

typedef struct {
    /* Unkstruct_98c6907e: P3.40 T3 band rank 1631; 10 TNC sites in 10 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80181C00; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d861b998: P3.40 T3 band rank 1633; 10 TNC sites in 10 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80180B18_2; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_ec1f7354: P3.40 T3 band rank 1634; 10 TNC sites in 10 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_8017ED94_2; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_e64bd744: P3.40 T3 band rank 1635; 10 TNC sites in 8 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801875E4; /* size = 0x18 */

typedef struct {
    /* Unkstruct_9fda9ff5: P3.40 T3 band rank 1636; 10 TNC sites in 7 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x52];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ u8 pad78[0x36];
    /* 0x00ae */ s16 unkAE;
} Unkstruct_80184884; /* size = 0xb0 */

typedef struct {
    /* Unkstruct_0f314160: P3.40 T3 band rank 1637; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
} Unkstruct_8017F1B8_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_143ad064: P3.40 T3 band rank 1638; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ u16 unk36;
} Unkstruct_80181654; /* size = 0x38 */

typedef struct {
    /* Unkstruct_77c79f05: P3.40 T3 band rank 1639; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x1e];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80183D98_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_91523b09: P3.40 T3 band rank 1640; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017C6CC; /* size = 0x20 */

typedef struct {
    /* Unkstruct_98bc2669: P3.40 T3 band rank 1641; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017DCD0_3; /* size = 0x18 */

typedef struct {
    /* Unkstruct_a60d032a: P3.40 T3 band rank 1642; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x50];
    /* 0x0060 */ s32 unk60;
} Unkstruct_8017C59C; /* size = 0x64 */

typedef struct {
    /* Unkstruct_b96ecadb: P3.40 T3 band rank 1643; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017CF50; /* size = 0x24 */

typedef struct {
    /* Unkstruct_c511c842: P3.40 T3 band rank 1644; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x48];
    /* 0x004c */ s32 unk4C;
} Unkstruct_800CCFA8; /* size = 0x50 */

typedef struct {
    /* Unkstruct_e7cd4a0f: P3.40 T3 band rank 1645; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017F254; /* size = 0x4 */

typedef struct {
    /* Unkstruct_ec645f46: P3.40 T3 band rank 1646; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017D75C; /* size = 0x1c */

typedef struct {
    /* Unkstruct_f52f39a7: P3.40 T3 band rank 1647; 10 TNC sites in 5 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8015D1B8_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_801307B0: P3.40 T3 band rank 1648; 10 TNC sites in 3 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x5e];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 padC0[0x1];
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_801307B0; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_ad8fd3cb: P3.40 T3 band rank 1649; 10 TNC sites in 3 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80182FD0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_bcbf56fd: P3.40 T3 band rank 1650; 10 TNC sites in 3 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80181EA0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_209a33b3: P3.40 T3 band rank 1651; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_80182928; /* size = 0x60 */

typedef struct {
    /* Unkstruct_26d74bfe: P3.40 T3 band rank 1652; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017C2B0_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_2bb689cd: P3.40 T3 band rank 1653; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017CECC; /* size = 0x14 */

typedef struct {
    /* Unkstruct_2ffba7cd: P3.40 T3 band rank 1654; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ void * unk0;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x1a8];
    /* 0x01ba */ u8 unk1BA;
    /* 0x01bb */ u8 pad1BB[0x21];
    /* 0x01dc */ void * unk1DC;
    /* 0x01e0 */ void * unk1E0;
    /* 0x01e4 */ u8 pad1E4[0x8];
    /* 0x01ec */ s16 unk1EC;
    /* 0x01ee */ u8 pad1EE[0x4];
    /* 0x01f2 */ s16 unk1F2;
} Unkstruct_80039308; /* size = 0x1f4 */

typedef struct {
    /* Unkstruct_32ee51b3: P3.40 T3 band rank 1655; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x86];
    /* 0x00aa */ s16 unkAA;
} Unkstruct_8017F858; /* size = 0xac */

typedef struct {
    /* Unkstruct_346c325c: P3.40 T3 band rank 1656; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DF5C_7; /* size = 0x38 */

typedef struct {
    /* Unkstruct_35b3bfcb: P3.40 T3 band rank 1657; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x16];
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017E22C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_3b4fc0c7: P3.40 T3 band rank 1659; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
} Unkstruct_80180E54; /* size = 0xc */

typedef struct {
    /* Unkstruct_4533e7f7: P3.40 T3 band rank 1660; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x8];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
} Unkstruct_8017DCAC; /* size = 0x30 */

typedef struct {
    /* Unkstruct_50771325: P3.40 T3 band rank 1662; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017BFEC_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_5c8ba99a: P3.40 T3 band rank 1664; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0xc];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x89];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017DC54; /* size = 0x100 */

typedef struct {
    /* Unkstruct_5d30794f: P3.40 T3 band rank 1665; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xee];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80183094_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_6a46c7bf: P3.40 T3 band rank 1666; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017EA84; /* size = 0x14 */

typedef struct {
    /* Unkstruct_6b708c56: P3.40 T3 band rank 1667; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x16];
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u8 pad2C[0x8];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017D0F8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_6ce1f507: P3.40 T3 band rank 1668; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_801813B4_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_6e10d0d7: P3.40 T3 band rank 1669; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017F0F4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_765fcc7b: P3.40 T3 band rank 1670; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_80181C3C; /* size = 0x60 */

typedef struct {
    /* Unkstruct_7c8c5f8a: P3.40 T3 band rank 1671; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ u8 padC2[0x40];
    /* 0x0102 */ s16 unk102;
} Unkstruct_8017E754; /* size = 0x104 */

typedef struct {
    /* Unkstruct_7eeaf79a: P3.40 T3 band rank 1672; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x1e0];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ u16 unk208;
    /* 0x020a */ u8 pad20A[0x2];
} Unkstruct_8017EAEC; /* size = 0x20c */

typedef struct {
    /* Unkstruct_80132018: P3.40 T3 band rank 1675; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x7e];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80132018_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_801596F0: P3.40 T3 band rank 1676; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801596F0_3; /* size = 0x2c */

typedef struct {
    /* Unkstruct_8015F118: P3.40 T3 band rank 1677; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x42];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ u8 pad48[0x70];
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u8 padBA[0xf0];
    /* 0x01aa */ u8 unk1AA;
    /* 0x01ab */ u8 pad1AB[0x1];
} Unkstruct_8015F118; /* size = 0x1ac */

typedef struct {
    /* Unkstruct_801654A8: P3.40 T3 band rank 1678; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x1f6];
    /* 0x01f8 */ s32 unk1F8;
} Unkstruct_801654A8_3; /* size = 0x1fc */

typedef struct {
    /* Unkstruct_8017D800: P3.40 T3 band rank 1679; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x11];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x6];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xa];
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x6];
    /* 0x0034 */ void * unk34;
} Unkstruct_8017D800; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8019FF14: P3.40 T3 band rank 1680; 10 TNC sites in 2 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_801847C8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_801D42F8: P3.40 T3 band rank 1681; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
} Unkstruct_80128EA8; /* size = 0x8 */

typedef struct {
    /* Unkstruct_801EADEC: P3.40 T3 band rank 1682; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8018A934; /* size = 0x10 */

typedef struct {
    /* Unkstruct_a1a2fb67: P3.40 T3 band rank 1683; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
} Unkstruct_8018312C; /* size = 0x30 */

typedef struct {
    /* Unkstruct_bbeb8174: P3.40 T3 band rank 1684; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb0];
    /* 0x00b0 */ u32 unkB0;
    /* 0x00b4 */ u8 padB4[0x18];
    /* 0x00cc */ u32 unkCC;
    /* 0x00d0 */ u8 padD0[0x13c];
    /* 0x020c */ u16 unk20C;
    /* 0x020e */ u16 unk20E;
    /* 0x0210 */ u16 unk210;
    /* 0x0212 */ u8 pad212[0x2];
} Unkstruct_8017F1A4; /* size = 0x214 */

typedef struct {
    /* Unkstruct_c1767d9d: P3.40 T3 band rank 1685; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x44];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80188B00; /* size = 0x100 */

typedef struct {
    /* Unkstruct_c34ce9a0: P3.40 T3 band rank 1686; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_801817D8; /* size = 0x74 */

typedef struct {
    /* Unkstruct_c60226e1: P3.40 T3 band rank 1687; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017EA44; /* size = 0x4 */

typedef struct {
    /* Unkstruct_c657d338: P3.40 T3 band rank 1688; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x48];
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_801806F0; /* size = 0x74 */

typedef struct {
    /* Unkstruct_d444badd: P3.40 T3 band rank 1689; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_801848CC; /* size = 0x1c */

typedef struct {
    /* Unkstruct_d7053746: P3.40 T3 band rank 1690; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x14];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xdc];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801803AC_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_ed75b904: P3.40 T3 band rank 1691; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801848CC_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_f4b1969b: P3.40 T3 band rank 1692; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DF5C_8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_fbe6574a: P3.40 T3 band rank 1693; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x32];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ u8 pad94[0x4];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x62];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80182128; /* size = 0x100 */

typedef struct {
    /* Unkstruct_0043257d: P3.40 T3 band rank 1694; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_8017EAE8; /* size = 0x34 */

typedef struct {
    /* Unkstruct_02737357: P3.40 T3 band rank 1695; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ u16 unk98;
    /* 0x009a */ u8 pad9A[0x10];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x30];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x20];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_80182258_2; /* size = 0x108 */

typedef struct {
    /* Unkstruct_09cde07e: P3.40 T3 band rank 1696; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x14];
    /* 0x0038 */ s16 unk38;
    /* 0x003a */ s16 unk3A;
    /* 0x003c */ s16 unk3C;
    /* 0x003e */ s16 unk3E;
    /* 0x0040 */ s16 unk40;
    /* 0x0042 */ s16 unk42;
    /* 0x0044 */ s16 unk44;
    /* 0x0046 */ s16 unk46;
    /* 0x0048 */ s16 unk48;
    /* 0x004a */ u8 pad4A[0x2];
} Unkstruct_8017DB80; /* size = 0x4c */

typedef struct {
    /* Unkstruct_10f02e24: P3.40 T3 band rank 1697; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x74];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x4c];
    /* 0x00e6 */ s16 unkE6;
    /* 0x00e8 */ u8 padE8[0x10];
    /* 0x00f8 */ u16 unkF8;
    /* 0x00fa */ u8 padFA[0x2];
} Unkstruct_801A2F34; /* size = 0xfc */

typedef struct {
    /* Unkstruct_178b9a24: P3.40 T3 band rank 1698; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 pad29[0x3];
} Unkstruct_8017EFA8; /* size = 0x2c */

typedef struct {
    /* Unkstruct_178d6db3: P3.40 T3 band rank 1699; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x32];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x29];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_8017EF64; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_17b7dcea: P3.40 T3 band rank 1700; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u8 pad2A[0x2];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_80187780; /* size = 0x38 */

typedef struct {
    /* Unkstruct_24f47f07: P3.40 T3 band rank 1701; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x14];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x30];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x8c];
    /* 0x00dc */ u16 unkDC;
    /* 0x00de */ s16 unkDE;
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ s16 unkE2;
} Unkstruct_801857B0; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_276e78ba: P3.40 T3 band rank 1702; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x38];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x56];
    /* 0x0102 */ s16 unk102;
} Unkstruct_80185760; /* size = 0x104 */

typedef struct {
    /* Unkstruct_292dd4e8: P3.40 T3 band rank 1703; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80182D18; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_2a3e079e: P3.40 T3 band rank 1704; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x78];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x42];
    /* 0x00dc */ u32 unkDC;
} Unkstruct_801845F4; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_300c8ec4: P3.40 T3 band rank 1706; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80183880; /* size = 0x24 */

typedef struct {
    /* Unkstruct_36f5296b: P3.40 T3 band rank 1708; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ s16 unk1E;
} Unkstruct_801843FC; /* size = 0x20 */

typedef struct {
    /* Unkstruct_38c67d8d: P3.40 T3 band rank 1709; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
} Unkstruct_80034CF0; /* size = 0x30 */

typedef struct {
    /* Unkstruct_3d076998: P3.40 T3 band rank 1710; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018A008; /* size = 0x24 */

typedef struct {
    /* Unkstruct_3e29979b: P3.40 T3 band rank 1711; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
} Unkstruct_80184FB0; /* size = 0x2c */

typedef struct {
    /* Unkstruct_3ed86d6d: P3.40 T3 band rank 1712; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x52];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x50];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801810B0; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_3fbbed98: P3.40 T3 band rank 1713; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x2c];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_80163EC8; /* size = 0x54 */

typedef struct {
    /* Unkstruct_41022da9: P3.40 T3 band rank 1714; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u8 pad2A[0x2];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017F76C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_4a4aee9c: P3.40 T3 band rank 1715; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xe4];
    /* 0x00e8 */ u16 unkE8;
    /* 0x00ea */ u8 padEA[0x2];
} Unkstruct_80182E2C; /* size = 0xec */

typedef struct {
    /* Unkstruct_4c5ca0cf: P3.40 T3 band rank 1716; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80186F7C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_4d17021f: P3.40 T3 band rank 1717; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80191C50_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_519c6d09: P3.40 T3 band rank 1718; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x30];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ u8 pad48[0x28];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x3];
} Unkstruct_80180C04; /* size = 0x78 */

typedef struct {
    /* Unkstruct_54b60592: P3.40 T3 band rank 1719; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u32 unk1C;
} Unkstruct_8018B1B4; /* size = 0x20 */

typedef struct {
    /* Unkstruct_554b018e: P3.40 T3 band rank 1720; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x14];
    /* 0x0038 */ s16 unk38;
    /* 0x003a */ s16 unk3A;
    /* 0x003c */ s16 unk3C;
    /* 0x003e */ s16 unk3E;
    /* 0x0040 */ s16 unk40;
    /* 0x0042 */ s16 unk42;
    /* 0x0044 */ s16 unk44;
    /* 0x0046 */ s16 unk46;
    /* 0x0048 */ s16 unk48;
    /* 0x004a */ u8 pad4A[0x2];
} Unkstruct_800CBD54; /* size = 0x4c */

typedef struct {
    /* Unkstruct_56cd2eda: P3.40 T3 band rank 1722; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u16 unk36;
    /* 0x0038 */ u16 unk38;
    /* 0x003a */ u8 pad3A[0x4];
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ s32 unk40;
} Unkstruct_8018526C; /* size = 0x44 */

typedef struct {
    /* Unkstruct_5a1a4e78: P3.40 T3 band rank 1723; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xb8];
    /* 0x00dc */ u16 unkDC;
    /* 0x00de */ u8 padDE[0x2];
} Unkstruct_8017FC6C; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_5b76ab05: P3.40 T3 band rank 1724; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x14];
    /* 0x0038 */ s16 unk38;
    /* 0x003a */ s16 unk3A;
    /* 0x003c */ s16 unk3C;
    /* 0x003e */ s16 unk3E;
    /* 0x0040 */ s16 unk40;
    /* 0x0042 */ s16 unk42;
    /* 0x0044 */ s16 unk44;
    /* 0x0046 */ s16 unk46;
    /* 0x0048 */ s16 unk48;
    /* 0x004a */ u8 pad4A[0x2];
} Unkstruct_8017F55C; /* size = 0x4c */

typedef struct {
    /* Unkstruct_5c507f5a: P3.40 T3 band rank 1725; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x18];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x12];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x2];
} Unkstruct_8017DC7C; /* size = 0x88 */

typedef struct {
    /* Unkstruct_5f684e2f: P3.40 T3 band rank 1726; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80136824_5; /* size = 0x10 */

typedef struct {
    /* Unkstruct_60947fc1: P3.40 T3 band rank 1727; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xe];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x94];
    /* 0x00b4 */ s32 unkB4;
    /* 0x00b8 */ u8 padB8[0x8];
    /* 0x00c0 */ u8 unkC0;
    /* 0x00c1 */ u8 padC1[0x3b];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801883E4; /* size = 0x104 */

typedef struct {
    /* Unkstruct_60d7c8a6: P3.40 T3 band rank 1728; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x6];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0xb];
    /* 0x0027 */ u8 unk27;
} Unkstruct_801E5CA8; /* size = 0x28 */

typedef struct {
    /* Unkstruct_62067ed2: P3.40 T3 band rank 1729; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x16];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ u8 pad78[0x36];
    /* 0x00ae */ s16 unkAE;
    /* 0x00b0 */ u8 padB0[0x11];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x3e];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80180424; /* size = 0x104 */

typedef struct {
    /* Unkstruct_63afaf32: P3.40 T3 band rank 1730; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u32 unk10;
    /* 0x0014 */ u32 unk14;
    /* 0x0018 */ u32 unk18;
} Unkstruct_8017EF68; /* size = 0x1c */

typedef struct {
    /* Unkstruct_6704cf08: P3.40 T3 band rank 1731; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_80182A40; /* size = 0x34 */

typedef struct {
    /* Unkstruct_68c3bfe5: P3.40 T3 band rank 1732; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x10];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x30];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x20];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_80185574; /* size = 0x108 */

typedef struct {
    /* Unkstruct_68eca67e: P3.40 T3 band rank 1733; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801AE138; /* size = 0x30 */

typedef struct {
    /* Unkstruct_6a63fdfd: P3.40 T3 band rank 1734; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80136824_6; /* size = 0x10 */

typedef struct {
    /* Unkstruct_6bb67f73: P3.40 T3 band rank 1735; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x96];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x14];
    /* 0x00e8 */ u32 unkE8;
    /* 0x00ec */ u8 padEC[0x18];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_80182998_2; /* size = 0x108 */

typedef struct {
    /* Unkstruct_7296fdb1: P3.40 T3 band rank 1736; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x14];
    /* 0x0038 */ s16 unk38;
    /* 0x003a */ s16 unk3A;
    /* 0x003c */ s16 unk3C;
    /* 0x003e */ s16 unk3E;
    /* 0x0040 */ s16 unk40;
    /* 0x0042 */ s16 unk42;
    /* 0x0044 */ s16 unk44;
    /* 0x0046 */ s16 unk46;
    /* 0x0048 */ s16 unk48;
    /* 0x004a */ u8 pad4A[0x2];
} Unkstruct_8017FA1C; /* size = 0x4c */

typedef struct {
    /* Unkstruct_770d286e: P3.40 T3 band rank 1737; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x8];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
} Unkstruct_800CD390; /* size = 0x28 */

typedef struct {
    /* Unkstruct_793e2b7d: P3.40 T3 band rank 1738; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x8a];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017E3B0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_7a540d33: P3.40 T3 band rank 1739; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ u8 padA[0xa];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x38];
    /* 0x0050 */ u32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_80039308_2; /* size = 0x58 */

typedef struct {
    /* Unkstruct_7a75fb71: P3.40 T3 band rank 1740; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x74];
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_80186FA4; /* size = 0x9c */

typedef struct {
    /* Unkstruct_7af83d02: P3.40 T3 band rank 1741; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x10];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ void * unk34;
    /* 0x0038 */ u8 pad38[0x14];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_800CB6E4; /* size = 0x58 */

typedef struct {
    /* Unkstruct_7b704daa: P3.40 T3 band rank 1742; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_801808E0; /* size = 0x34 */

typedef struct {
    /* Unkstruct_7e921c92: P3.40 T3 band rank 1743; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x10];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x54];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ s16 unk102;
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_8017E47C; /* size = 0x108 */

typedef struct {
    /* Unkstruct_80130A18: P3.40 T3 band rank 1745; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x4e];
    /* 0x00ac */ s16 unkAC;
    /* 0x00ae */ u8 padAE[0x13];
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80130A18; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_80132288: P3.40 T3 band rank 1746; 10 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s32 unk14;
} Unkstruct_80132288_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_80149450: P3.40 T3 band rank 1747; 10 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80149450; /* size = 0x24 */

typedef struct {
    /* Unkstruct_8014E048: P3.40 T3 band rank 1748; 10 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x18];
    /* 0x002c */ s32 unk2C;
} Unkstruct_8014E048; /* size = 0x30 */

typedef struct {
    /* Unkstruct_801775E0: P3.40 T3 band rank 1749; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 pad7[0x3];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_801775E0; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8017C24C: P3.40 T3 band rank 1750; 10 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017C24C; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8017C710: P3.40 T3 band rank 1751; 10 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017C710; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8017C8D0: P3.40 T3 band rank 1752; 10 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017C8D0; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8017C910: P3.40 T3 band rank 1753; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_8017C910; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8017CA80: P3.40 T3 band rank 1754; 10 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017CA80_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8017D5C0: P3.40 T3 band rank 1756; 10 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017D5C0; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8017D728: P3.40 T3 band rank 1757; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_8017D728; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8017D7F0: P3.40 T3 band rank 1758; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_8017D7F0; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8017D898: P3.40 T3 band rank 1759; 10 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017D898; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8017D9EC: P3.40 T3 band rank 1760; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_8017D9EC; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8017DB00: P3.40 T3 band rank 1761; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_8017DB00_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8017E608: P3.40 T3 band rank 1762; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_8017E608; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8017E924: P3.40 T3 band rank 1763; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_8017E924; /* size = 0x34 */

typedef struct {
    /* Unkstruct_8018419C: P3.40 T3 band rank 1764; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xd8];
    /* 0x00dc */ u16 unkDC;
    /* 0x00de */ u16 unkDE;
    /* 0x00e0 */ u16 unkE0;
    /* 0x00e2 */ u8 padE2[0x2];
} Unkstruct_8018419C; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_89a4a7d8: P3.40 T3 band rank 1767; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x28];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x20];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801808F0; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_90095b2e: P3.40 T3 band rank 1769; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DC20_6; /* size = 0x38 */

typedef struct {
    /* Unkstruct_91b15ded: P3.40 T3 band rank 1770; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
} Unkstruct_80185680_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_968b7d91: P3.40 T3 band rank 1771; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x17];
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ u8 pad76[0x2];
} Unkstruct_801A6038; /* size = 0x78 */

typedef struct {
    /* Unkstruct_9aa05a79: P3.40 T3 band rank 1772; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80184E84; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_a1be47f8: P3.40 T3 band rank 1774; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DC20_7; /* size = 0x38 */

typedef struct {
    /* Unkstruct_a201ac84: P3.40 T3 band rank 1775; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u8 pad2A[0x2];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_80186D9C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ac4a90d5: P3.40 T3 band rank 1776; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x1c];
    /* 0x00de */ u16 unkDE;
    /* 0x00e0 */ s32 unkE0;
} Unkstruct_8017FA84; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_b006998e: P3.40 T3 band rank 1777; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0xf0];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801804EC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_b0370f24: P3.40 T3 band rank 1778; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8016DC20_8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_b06821f2: P3.40 T3 band rank 1779; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x32];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x29];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80186594; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_bf87f947: P3.40 T3 band rank 1781; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801851A8; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_c4305460: P3.40 T3 band rank 1782; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u16 unk2E;
} Unkstruct_8017FB38; /* size = 0x30 */

typedef struct {
    /* Unkstruct_c6961e2c: P3.40 T3 band rank 1783; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xaa];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ s16 unkAC;
    /* 0x00ae */ u8 padAE[0xea];
    /* 0x0198 */ s32 unk198;
    /* 0x019c */ u8 pad19C[0x68];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ u8 pad208[0x4];
    /* 0x020c */ s16 unk20C;
    /* 0x020e */ u8 pad20E[0x6];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8017E94C_2; /* size = 0x218 */

typedef struct {
    /* Unkstruct_cc4e3a55: P3.40 T3 band rank 1786; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x10];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80186AA8; /* size = 0x20 */

typedef struct {
    /* Unkstruct_cfe7e109: P3.40 T3 band rank 1787; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x6];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 unk27;
} Unkstruct_801813D0_2; /* size = 0x28 */

typedef struct {
    /* Unkstruct_d095aeb9: P3.40 T3 band rank 1788; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0xf0];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801807C0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_d302dfde: P3.40 T3 band rank 1789; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80185D2C; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_d4df67e9: P3.40 T3 band rank 1790; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x10];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x6];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x45];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_801808A4; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_d81052a3: P3.40 T3 band rank 1791; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x10];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ u8 padAC[0x30];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x20];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
    /* 0x0104 */ s16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_8017E528; /* size = 0x108 */

typedef struct {
    /* Unkstruct_dd00531d: P3.40 T3 band rank 1792; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x32];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x29];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80186F78; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_dd2b983d: P3.40 T3 band rank 1793; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0xa];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801E5338; /* size = 0x30 */

typedef struct {
    /* Unkstruct_e36255ef: P3.40 T3 band rank 1795; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80136824_7; /* size = 0x10 */

typedef struct {
    /* Unkstruct_e60dba52: P3.40 T3 band rank 1796; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_801919A0_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_e8712b9d: P3.40 T3 band rank 1797; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x8];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_801681FC_3; /* size = 0x34 */

typedef struct {
    /* Unkstruct_f2d0d9b3: P3.40 T3 band rank 1798; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0xca];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80180E64; /* size = 0x104 */

typedef struct {
    /* Unkstruct_f8d839af: P3.40 T3 band rank 1800; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80180BD0; /* size = 0x104 */

typedef struct {
    /* Unkstruct_fa48502a: P3.40 T3 band rank 1801; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x30];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ u8 pad48[0x28];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x3];
} Unkstruct_80182AFC; /* size = 0x78 */

typedef struct {
    /* Unkstruct_ffb68512: P3.40 T3 band rank 1802; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ u8 pad60[0x10];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x14];
    /* 0x0086 */ u16 unk86;
    /* 0x0088 */ u8 pad88[0x39];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80184728; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_ffb84f0c: P3.40 T3 band rank 1803; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x1c];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u32 unk30;
} Unkstruct_80180E74; /* size = 0x34 */

typedef struct {
    /* Unkstruct_170c4a59: P3.40 T3 band rank 1804; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
} Unkstruct_801821D0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_37c0f40e: P3.40 T3 band rank 1805; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_801825C4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_3bdb24d4: P3.40 T3 band rank 1806; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8015D4E8_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_687cf1dc: P3.40 T3 band rank 1807; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017D7A4_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_80143BDC: P3.40 T3 band rank 1808; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8017EF48_2; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_81bf0484: P3.40 T3 band rank 1809; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd0];
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_8017D8DC_2; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_b404b668: P3.40 T3 band rank 1810; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017E84C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_e97825ee: P3.40 T3 band rank 1812; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017CE64; /* size = 0x4 */

typedef struct {
    /* Unkstruct_ef167027: P3.40 T3 band rank 1813; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80182258_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_80171CC4: P3.40 T3 band rank 1815; 9 TNC sites in 4 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80171D78; /* size = 0x8 */

typedef struct {
    /* Unkstruct_01e8e293: P3.40 T3 band rank 1816; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
} Unkstruct_8017FED8_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_063f5e04: P3.40 T3 band rank 1817; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ void * unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ void * unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ void * unk18;
} Unkstruct_8002F4E4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_09dd512c: P3.40 T3 band rank 1818; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20e];
    /* 0x020e */ s16 unk20E;
} Unkstruct_8017C6B8; /* size = 0x210 */

typedef struct {
    /* Unkstruct_0b401a82: P3.40 T3 band rank 1819; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8016EC0C_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_1a281108: P3.40 T3 band rank 1820; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017EBB8; /* size = 0x74 */

typedef struct {
    /* Unkstruct_1b6768c1: P3.40 T3 band rank 1821; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x48];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_8018BBBC_2; /* size = 0x54 */

typedef struct {
    /* Unkstruct_1dd4c8ed: P3.40 T3 band rank 1822; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
} Unkstruct_8018020C; /* size = 0xc */

typedef struct {
    /* Unkstruct_1fb0e670: P3.40 T3 band rank 1823; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe0];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x4];
    /* 0x00e8 */ s32 unkE8;
} Unkstruct_80181954; /* size = 0xec */

typedef struct {
    /* Unkstruct_1fec88a7: P3.40 T3 band rank 1824; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x20];
    /* 0x0034 */ void * unk34;
} Unkstruct_8017E948; /* size = 0x38 */

typedef struct {
    /* Unkstruct_3002b31c: P3.40 T3 band rank 1825; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017BF50; /* size = 0x20 */

typedef struct {
    /* Unkstruct_31970a2a: P3.40 T3 band rank 1826; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80184958; /* size = 0x10 */

typedef struct {
    /* Unkstruct_399c59f3: P3.40 T3 band rank 1827; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6e];
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x8c];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80181E18; /* size = 0x104 */

typedef struct {
    /* Unkstruct_4310cdde: P3.40 T3 band rank 1830; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80136A94_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_46c55caf: P3.40 T3 band rank 1831; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
} Unkstruct_8017E254_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_47b10064: P3.40 T3 band rank 1832; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016DC20_9; /* size = 0x1c */

typedef struct {
    /* Unkstruct_4d590a77: P3.40 T3 band rank 1833; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ u16 unk20;
    /* 0x0022 */ u16 unk22;
} Unkstruct_80175DA8_6; /* size = 0x24 */

typedef struct {
    /* Unkstruct_4e0daa82: P3.40 T3 band rank 1834; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80187E08; /* size = 0x100 */
/* T3 band defs:end */

#endif /* STRUCT_TYPES_H */
