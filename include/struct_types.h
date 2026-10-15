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

#endif /* STRUCT_TYPES_H */
