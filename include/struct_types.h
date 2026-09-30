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
    /* 0x0076 */ u8 pad76[0x8];
    /* 0x007e */ u16 unk7E;
    /* 0x0080 */ u8 pad80[0x8];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x1a];
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
    /* 0x00c4 */ u8 padC4[0x8];
    /* 0x00cc */ u32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u16 unkD4;
    /* 0x00d6 */ s16 unkD6;
    /* 0x00d8 */ u8 padD8[0x4];
    /* 0x00dc */ s8 unkDC;
    /* 0x00dd */ u8 unkDD;
    /* 0x00de */ s8 unkDE;
    /* 0x00df */ u8 unkDF;
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ s16 unkE2;
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ u8 padE6[0xc];
    /* 0x00f2 */ s16 unkF2;
    /* 0x00f4 */ s16 unkF4;
    /* 0x00f6 */ s16 unkF6;
    /* 0x00f8 */ u8 padF8[0x4];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x12];
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
typedef struct { s32 w[8]; } Blk20;
typedef struct { u8 b[8]; } Blk8;
typedef struct { u32 a, b, c, d; } Blk16;
typedef struct { s32 vpx, vpy, vpz, vrx, vry, vrz, rz, super; } RView;
typedef struct { u32 addr : 24; u32 len : 8; u8 r0, g0, b0, code; } P_TAG;
typedef struct { s32 w[8]; } Blk32;
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
typedef struct { s32 f0; u8 pad[0x18]; } E_3B7AC;
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
} Mtx;
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
typedef struct SVec_8016AB6C {
    s16 vx, vy, vz, pad;
} SVec_8016AB6C;
typedef struct { char pad_8013BC7C[0x68]; s32 f68; } S_8013BC7C;
typedef struct {
    u8  b0;
    u8  b1;
    u8  b2;
    u8  type;
    u32 w1;
    u32 w2;
} T3Reloc;
typedef struct { s16 x, y, z; } Vec3s;
typedef struct { char b[4]; } W;
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
    } E_13C08C;
typedef struct {
        s32 f0;
        u16 f4;
        u16 f6;
        u16 f8;
        u16 fA;
        s32 fC;
        u8  pad[0xC];
    } Ent_8013B6A0;
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
typedef struct {
        u32 *ot;            /* 0x00 */
        u32 pad[4];         /* 0x04..0x13 */
    } Env_800D29F8;
typedef struct {
        u8  pad0[3];
        u8  code;
        s32 f4;
        s32 f8;
    } P_13BD74;
typedef struct { s32 f0; u16 f4; u16 f6; u16 f8; u16 fA; s32 fC; u8 pad[0xC]; } Spr_8013B598;
typedef struct { u16 f0; u16 f2; u16 f4; } Src_8013B598;
typedef struct {
        u16 f0;
        u16 f2;
        u16 f4;
    } Src_8013B6A0;
typedef struct { s16 vx, vy; } DVEC2_C974_8017BA3C;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C974;
typedef struct {
    u16 x, y, z, w;
} Pt_8017D87C;
typedef struct { s16 vx, vy, vz, pad; } SV;
typedef struct { s16 vx, vy, vz, pad; } SVEC2_C974_8017BA3C;
typedef struct {
    u8 b[4];
} Blk4;
typedef struct { u8 d[4]; } Blk4_md_SC07_003;
typedef struct {
    s16 vx, vy, vz, pad;
} SVECTOR_800;

/* --- lift_types.py --census (P38 T5.1.c2, batch ov-block) --- */
typedef struct { u8 c[8]; } Blk8_md_SC03_076;
typedef struct { u32 addr : 24; u32 len : 8; } PTag;
typedef struct { u32 w[4]; } St801D9204;
typedef struct { s32 f; } Unkstruct_801151D0;
typedef struct { s32 vx, vy, vz, pad; } V32;

#endif /* STRUCT_TYPES_H */
