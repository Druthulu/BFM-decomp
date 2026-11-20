/* include/struct_types.h — the struct map's canonical layouts (P38 T3). One definition per type, visible to every space through common.h. Hand-edited throughout: the formerly generated blocks each open with one `provenance (<block>):` comment line (generators retired P3.45 T6). Naming law G62: Unkstruct_<addr>, unkHEX fields, 0xNN offset comments. */
#ifndef STRUCT_TYPES_H
#define STRUCT_TYPES_H

/* provenance (head_types): tools/head_types.py --header (was the head_types marker block, from .run/P37/census/struct_map.json), last ran at 1a65f29eb1 (P3.39 T3.c6, --add-pads); generator retired P3.45 T6; hand-edited since */
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

/* T18.c13: SVECTOR moved ahead of the model record (unk80 SVECTOR *; byte-neutral) */
typedef struct { short vx, vy, vz, pad; } SVECTOR;

/* RenderHead — shared render head: first 0x14 bytes of the sprite record Unkstruct_800B5BD8 (pool tag 2, src/800.c:8585-8735)
   and the model record Unkstruct_8001C9D0 (pool tag 1); slot init tags model 1 / sprite 2 (func_8012C890__1bddfa15.h:55-70). T17.c38. */
typedef struct {
    /* 0x0000 */ union { u16 u; s16 s; } unk0;
    /* 0x0002 */ union { u16 u; s16 s; } unk2;
    /* 0x0004 */ union { s32 s; u32 u; } unk4;
    /* 0x0008 */ union { s16 s; u16 u; } unk8;
    /* 0x000a */ union { s16 s; u16 u; } unkA;
    /* 0x000c */ union { s16 s; u16 u; } unkC;
    /* 0x000e */ union { u16 u; s16 s; } unkE;
    /* 0x0010 */ union { s16 s; u16 u; } unk10;
    /* 0x0012 */ union { s16 s; u16 u; } unk12;
} RenderHead; /* size = 0x14 */

typedef struct {
    /* Unkstruct_ea207b39: P3.40 T3 band rank 1119; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ RenderHead head; /* shared render head (model record, tag 1); T17.c38 */
    /* 0x0014 */ union { s16 s; u16 u; } unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ union {
        s16 s;
        u16 u;
    } unk18;
    /* 0x001a */ union {
        s16 s;
        u16 u;
    } unk1A;
    /* 0x001c */ union {
        s16 s;
        u16 u;
    } unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ union { s16 s; u16 u; } unk2A;
    /* 0x002c */ union {
        s16 s;
        u16 u;
    } unk2C;
    /* 0x002e */ union { s16 s; u16 u; } unk2E;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ u8 pad34[0x14];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0x14];
    /* 0x0068 */ s32 unk68;
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ u8 pad70[0x6];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0x4];
    /* 0x0080 */ SVECTOR *unk80;
} Unkstruct_8001C9D0; /* size = 0x84 */

typedef struct {
    /* P37 struct map: 65397 sites in 17047 bodies; evidence {'PV': 1050, 'L': 1271, 'AT': 1, 'P': 1050, 'PTR': 1, 'FLD': 14}; at guess_g_PlayerActor; resolved by tools/head_types.py (max-site split); decisions: docs/struct-map-decisions.md */
    /* T16.c5: 0x254 bytes: guess_ZeroMemory(&guess_g_PlayerActor, 0x254) (src/shared/ov/func_80145CEC__05c7cfc4.h:51) */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ union {
        s16 s;
        u16 u;
    } unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ union {
        s16 s;
        u16 u;
    } unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ union {
        s16 s;
        u16 u;
    } unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ union { s32 val; Unkstruct_8001C9D0 *m; } unk20; /* m: the model record (C0629) */
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
    /* 0x0044 */ union {
        u32 u;
        s32 s;
    } unk44;
    /* 0x0048 */ u8 pad48[0x5];
    /* 0x004d */ u8 unk4D;
    /* 0x004e */ u8 unk4E;
    /* 0x004f */ u8 unk4F;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s32 unk5C;
    /* 0x0060 */ union { u16 u; s16 s; } unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ union { u16 u; s16 s; } unk64;
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
    /* 0x00a8 */ union { u8 u; s8 s; } unkA8;
    /* 0x00a9 */ u8 unkA9;
    /* 0x00aa */ u16 unkAA;
    /* 0x00ac */ u16 unkAC;
    /* 0x00ae */ u16 unkAE;
    /* 0x00b0 */ s32 unkB0;
    /* 0x00b4 */ union { s32 val; s32 *p; } unkB4; /* p: the command stream (func_8015444C, ex Actor4C) */
    /* 0x00b8 */ union {
        u16 u;
        s16 s;
    } unkB8;
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
    /* 0x00cc */ union { u32 u; s32 s; } unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u16 unkD4;
    /* 0x00d6 */ s16 unkD6;
    /* 0x00d8 */ u8 padD8[0x2];
    /* 0x00da */ u8 unkDA;
    /* 0x00db */ u8 padDB[0x1];
    /* 0x00dc */ s8 unkDC;
    /* 0x00dd */ u8 unkDD;
    /* 0x00de */ union { s8 s; u8 u; } unkDE;
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
    /* 0x0184 */ union { s32 s; u32 u; } unk184;
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
    /* 0x01a1 */ u8 pad1A1[0x7];
    /* 0x01a8 */ u8 unk1A8;
    /* 0x01a9 */ u8 pad1A9[0x1];
    /* 0x01aa */ u8 unk1AA;
    /* 0x01ab */ u8 unk1AB;
    /* 0x01ac */ s32 unk1AC;
    /* 0x01b0 */ s32 unk1B0;
    /* 0x01b4 */ s32 unk1B4;
    /* 0x01b8 */ u16 unk1B8;
    /* 0x01ba */ u16 unk1BA;
    /* 0x01bc */ s8 unk1BC;
    /* 0x01bd */ u8 pad1BD[0x1];
    /* 0x01be */ u8 unk1BE;
    /* 0x01bf */ u8 pad1BF[0x1];
    /* 0x01c0 */ u8 unk1C0;
    /* 0x01c1 */ u8 pad1C1[0x5];
    /* 0x01c6 */ u8 unk1C6;
    /* 0x01c7 */ s8 unk1C7;
    /* 0x01c8 */ union { u16 u; s16 s; } unk1C8;
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
    /* 0x0214 */ union { u8 u; s8 s; } unk214;
    /* 0x0215 */ union { s8 s; u8 u; } unk215;
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
    /* 0x0244 */ union { u16 u; struct { u8 lo; u8 hi; } b; } unk244;
    /* 0x0246 */ u16 unk246;
    /* 0x0248 */ u16 unk248;
    /* 0x024a */ union {
        s16 s;
        u16 u;
    } unk24A;
    /* 0x024c */ u8 pad24C[0x8];
} Unkstruct_80126B58; /* size = 0x254 */

/* T16.c6: defined ahead of Unkstruct_801202A0 (moved, byte-neutral, Unkstruct_80185680_2 from below, its alias and SubStruct
   from src/shared/engine_types.h): the parent's absorbed views MainStruct / Unkstruct_801202A0 spell them. */
typedef struct {
    /* Unkstruct_91b15ded: P3.40 T3 band rank 1770; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
} Unkstruct_80185680_2; /* size = 0x8 */

/* T17.c29: the 8-byte record at (actor unk90[i].unk0 & 0xfeffffff) + 0x50 (model data the element's tagged pointer names;
   bit 24 is the tag). Reads: func_80181824 src/ov_SC03_030/ov_SC03_030_jr_8017AE2C.c: u32 +0 whole and u8 +1, s8 +3/+4/+5,
   s16 +6. */
typedef struct {
    /* 0x0000 */ union { u32 w; struct { u8 unk0; u8 unk1; u8 unk2; s8 unk3; } b; } unk0;
    /* 0x0004 */ s8 unk4;
    /* 0x0005 */ s8 unk5;
    /* 0x0006 */ s16 unk6;
} Rec_80181824; /* size = 0x8 */

/* T17.c24b: Unkstruct_8013B83C moved ahead of Unkstruct_801202A0 (byte-neutral): the actor's +0x44 union spells it. */
typedef struct {
    /* Unkstruct_630777a3: P3.40 T3 band rank 56; 399 TNC sites in 266 bodies; struct map 399 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 unk7;
} Unkstruct_8013B83C; /* size = 0x8 */

/* Unkstruct_801202A0 — the actor slot (guess_g_ObjectTable 0x801202A0 x 96, 0x10C each; P3.45 T16.c1 model).
   Common fields flat; extA/extB/extC/extD are the per-kind gap unions (`raw` + one struct member per class variant, T16.c5). */
/* T17.c20: definition = T17.c19 model (.run/3.45/t17/c19/model.md; promoted common fields +0xAA/+0xB4/+0xBC/+0xC0..+0xC4,
   +0xCC/+0xD0, gaps re-cut extB/extE/padB8/extF, sign unions per vconf.tsv, extD sign-union variants pre-declared;
   evidence: src/shared/ov/func_8017849C.h:23-29 pool walker, func_8017869C.h:7-14, func_80130D0C__0ba44c04.h:4). */
typedef struct Unkstruct_801202A0 {
    /* T16.c5 + T17.c19: actor slot; gaps extA 0x24 (0x10), extB 0xA0 (0xA), extE 0xAC (0x8), extF 0xC8 (0x4), extC 0xE0 (0x18), extD 0x100 (0xA) */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ union { u16 u; s16 s; } unk2;
    /* 0x0004 */ union { s32 val; struct { u16 lo; union { u16 u; s16 s; } hi; } i; } unk4;
    /* 0x0008 */ union { s32 val; struct { u16 lo; union { u16 u; s16 s; } hi; } i; } unk8;
    /* 0x000c */ union { s32 val; struct { u16 lo; union { u16 u; s16 s; } hi; } i; } unkC;
    /* 0x0010 */ union { s32 val; struct { u16 lo; union { u16 u; s16 s; } hi; } i; } unk10;
    /* 0x0014 */ union { s32 val; struct { u16 lo; union { u16 u; s16 s; } hi; } i; } unk14;
    /* 0x0018 */ union { s32 val; struct { u16 lo; union { u16 u; s16 s; } hi; } i; } unk18;
    /* 0x001c */ union { s32 s; u32 u; } unk1C;
    /* 0x0020 */ union { void *p; Unkstruct_8001C9D0 *m; struct Unkstruct_800B5BD8 *s; RenderHead *h; s32 val; } unk20; /* render pointer: slot init tags model 1 / sprite 2 (func_8012C890__1bddfa15.h:55-70) */
    /* 0x0024 */ union { u8 raw[0x10]; struct { u8 pad0[0x4]; s16 unk28; } kcls_08c5824beac9; struct { u8 pad0[0x8]; u16 unk2C; u16 unk2E; } kcls_ae1124e6e4cc; struct { u8 pad0[0x4]; s16 unk28; } kSC01_077_801867E0; struct { u8 unk24; u8 unk25; u8 unk26; u8 unk27; u8 pad4[0x2]; u16 unk2A; u16 unk2C; u16 unk2E; } kSC04_003_8017E040; struct { u8 pad0[0x8]; u16 unk2C; u16 unk2E; } kSC04_007_8017FF08; struct { u8 pad0[0x4]; s16 unk28; } kcls_fbecc647cdc0; struct { u8 unk24; u8 unk25; u8 unk26; u8 unk27; u8 pad4[0x2]; u16 unk2A; } kSC04_007_80180324; } extA;
    /* 0x0034 */ union { u16 u; s16 s; } unk34;
    /* 0x0036 */ union { u16 u; s16 s; } unk36;
    /* 0x0038 */ u8 pad38[0x2];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u8 pad3C[0x2];
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u8 pad40[0x2];
    /* 0x0042 */ u16 unk42;
    /* 0x0044 */ union { struct { s32 unk44; s32 unk48; } w; Unkstruct_8013B83C m; } unk44; /* m: 8-byte record copy (func_8016380C.h) */
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ union { u16 u; s16 s; } unk50;
    /* 0x0052 */ union { u16 u; s16 s; } unk52;
    /* 0x0054 */ union { u16 u; s16 s; } unk54;
    /* 0x0056 */ u8 pad56[0x2];
    /* 0x0058 */ union { s32 s; u32 u; } unk58;
    /* 0x005c */ union { s16 s; u16 u; } unk5C;
    /* 0x005e */ union { u8 b; u16 u; s16 s; } unk5E;
    /* 0x0060 */ union { s16 s; u16 u; } unk60;
    /* 0x0062 */ u16 unk62;
    /* 0x0064 */ struct Unkstruct_801202A0 *unk64;
    /* 0x0068 */ void *unk68;
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ union { u16 u; s16 s; } unk70;
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ union { s16 s; u16 u; } unk76;
    /* 0x0078 */ void *unk78;
    /* 0x007c */ s16 unk7C;
    /* 0x007e */ s16 unk7E;
    /* 0x0080 */ s16 unk80;
    /* 0x0082 */ s16 unk82;
    /* 0x0084 */ union { s16 s; u16 u; } unk84;
    /* 0x0086 */ union { u16 u; s16 s; } unk86;
    /* 0x0088 */ union { u16 u; s16 s; } unk88;
    /* 0x008a */ union { u16 u; s16 s; } unk8A;
    /* 0x008c */ union { u16 u; s16 s; } unk8C;
    /* 0x008e */ u8 pad8E[0x2];
    /* 0x0090 */ Unkstruct_80185680_2 *unk90;
    /* 0x0094 */ union { s32 s; u32 u; } unk94;
    /* 0x0098 */ union { s16 s; u16 u; } unk98;
    /* 0x009a */ s16 unk9A;
    /* 0x009c */ s32 unk9C;
    /* 0x00a0 */ union { u8 raw[0x4]; } extB; /* extB split per word (T17.c35): an s32 variant member pads a 0xA union to 0xC (C0635) */
    /* 0x00a4 */ union { u8 raw[0x4]; struct { s32 unkA4; } kSC02_000_80189304; } extB4;
    /* 0x00a8 */ union { u8 raw[0x2]; struct { s16 unkA8; } kSC02_000_80189304; } extB8;
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ union { u8 raw[0x8]; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_005_801831A4; struct { u8 pad0[0x4]; s32 unkB0; } kSC01_000_80131E00; struct { u8 pad0[0x4]; s32 unkB0; } kcls_1ffadb9a164c; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_014_80187CA8; struct { u8 pad0[0x4]; s32 unkB0; } kSC02_009_801E4C64; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_005_80182A8C; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_005_801838A8; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_090_8018745C; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_018_80183A00; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_022_8017DBA4; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_022_8017E920; struct { u8 pad0[0x4]; s32 unkB0; } kSC03_001_80187DAC; struct { u8 pad0[0x2]; s16 unkAE; } kSC04_011_801896BC; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_018_8018A61C; struct { u8 pad0[0x4]; s32 unkB0; } kSC01_005_80182000; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_005_80182EB0; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_005_801892CC; struct { u8 pad0[0x4]; s32 unkB0; } kSC02_009_801E5450; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_011_8017CF54; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_011_8017D370; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_017_8017FB00; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_026_8017DC3C; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_026_801808D0; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_027_80180FE0; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_028_801822F0; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_041_80180438; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_041_80180ED4; struct { u8 pad0[0x4]; s32 unkB0; } kSC03_001_80183C30; struct { u8 pad0[0x4]; s32 unkB0; } kSC03_001_8018444C; struct { u8 pad0[0x4]; s32 unkB0; } kSC03_001_80188518; struct { u8 pad0[0x4]; s32 unkB0; } kSC03_001_80188570; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_002_8017CF30; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_007_80181BE8; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_024_80185334; struct { s16 unkAC; s16 unkAE; } kSC03_028_80182E2C; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_028_80183020; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_028_80186754; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_092_80181694; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_093_801813E0; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_094_8017E7B0; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_105_8017E794; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_105_8017EC5C; struct { s16 unkAC; } kSC03_105_80180100; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_116_801819F4; struct { u8 pad0[0x2]; s16 unkAE; } kSC04_000_8017F1A4; struct { u8 pad0[0x2]; s16 unkAE; } kSC04_000_801803BC; struct { u8 pad0[0x2]; s16 unkAE; } kSC04_002_80184E8C; struct { u8 pad0[0x2]; s16 unkAE; } kSC04_005_8017F210; struct { u8 pad0[0x2]; s16 unkAE; } kSC04_005_801831B4; struct { u8 pad0[0x2]; s16 unkAE; } kSC04_012_8017D698; struct { u8 pad0[0x4]; s32 unkB0; } kSC04_018_8017E9C0; struct { u8 pad0[0x4]; s32 unkB0; } kSC04_018_8017EA0C; struct { u8 pad0[0x4]; s32 unkB0; } kSC04_018_8017F1C8; struct { u8 pad0[0x4]; s32 unkB0; } kSC04_018_8017F224; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_003_8017F68C; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_005_8017CBB0; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_010_80180AA0; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_010_801813F4; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_010_801828E0; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_010_801829F0; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_010_80182AC0; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_010_80183C84; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_000_801846BC; struct { s16 unkAC; } kSC06_008_8017FC84; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_008_80182838; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_008_80182E8C; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_010_801836D4; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_011_8017DAB8; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_011_8017DDD8; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_011_8017ED68; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_011_8017F09C; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_013_8017E534; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_016_8017DEC4; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_018_8017DC60; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_018_801932EC; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_022_8017F598; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_022_80180310; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_024_8017D804; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_024_80180894; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_024_8018090C; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_025_8017E290; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_025_8018129C; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_033_8017E594; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_033_8018C2D8; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_033_8018D7B4; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_033_8018D98C; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_033_8018E4A4; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_033_8018F194; struct { u8 pad0[0x2]; s16 unkAE; } kSC07_001_8017E448; struct { u8 pad0[0x2]; s16 unkAE; } kSC07_003_801A01D4; struct { u8 pad0[0x2]; s16 unkAE; } kSC07_004_801A2D78; struct { u8 pad0[0x2]; s16 unkAE; } kSC07_004_801A4420; struct { u8 pad0[0x2]; s16 unkAE; } kcls_33a5615dfde0; struct { u8 pad0[0x2]; s16 unkAE; } kcls_431f99de0b6a; struct { u8 pad0[0x2]; s16 unkAE; } kcls_592a9370d0bd; struct { u8 pad0[0x2]; s16 unkAE; } kcls_7edb30ee0251; struct { u8 pad0[0x2]; s16 unkAE; } kcls_99f444c3ad2b; struct { u8 pad0[0x2]; s16 unkAE; } kcls_b182d769c468; struct { u8 pad0[0x2]; s16 unkAE; } kcls_d736d5fea74c; struct { u8 pad0[0x2]; s16 unkAE; } kcls_ffd29a8c26ea; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_005_801822EC; struct { u8 pad0[0x4]; s32 unkB0; } kSC03_001_801853D0; struct { u8 pad0[0x2]; s16 unkAE; } kSC04_002_80180090; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_005_8017F840; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_010_80182BD0; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_008_80181EE0; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_016_8017EC50; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_029_80183A1C; struct { u8 pad0[0x2]; s16 unkAE; } kcls_f3fd007e5bd8; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_005_80184358; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_005_801851E0; struct { u8 pad0[0x4]; s32 unkB0; } kSC03_124_8017EDE8; struct { u8 pad0[0x2]; s16 unkAE; } kSC04_011_801EFC54; struct { u8 pad0[0x4]; s32 unkB0; } kSC05_017_801834F8; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_027_80184BE4; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_028_801855C8; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_035_8017E724; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_037_80182B58; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_089_801830D8; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_090_80182DB4; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_091_80183C5C; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_094_8017FAAC; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_098_801802B4; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_099_8017E518; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_100_8017FF44; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_102_80182514; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_103_8017F784; struct { u8 pad0[0x2]; s16 unkAE; } kSC03_104_80186F28; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_010_80180854; struct { u8 pad0[0x2]; s16 unkAE; } kSC05_010_80181B4C; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_000_80183088; struct { s16 unkAC; } kSC06_010_80182138; struct { s16 unkAC; } kSC06_018_8017FA90; struct { s16 unkAC; } kSC06_022_8018C8EC; struct { s16 unkAC; } kSC06_024_8018EDC4; struct { s16 unkAC; } kSC06_032_8018C77C; struct { s16 unkAC; } kSC06_033_8019041C; struct { u8 pad0[0x2]; s16 unkAE; } kSC07_003_801A3190; struct { u8 pad0[0x2]; s16 unkAE; } kSC02_005_8018550C; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_032_8019303C; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_033_8018BCD4; struct { u8 pad0[0x2]; s16 unkAE; } kSC06_033_8018E89C; struct { u8 pad0[0x2]; s16 unkAE; } kcls_b4ff33593fa2; } extE;
    /* 0x00b4 */ union { s32 s; u32 u; } unkB4;
    /* 0x00b8 */ u8 padB8[0x4];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ union { u8 u; s8 s; } unkC0;
    /* 0x00c1 */ union { u8 u; s8 s; } unkC1;
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 unkC3;
    /* 0x00c4 */ s32 unkC4;
    /* 0x00c8 */ union { u8 raw[0x4]; struct { u8 unkC8; } kMAIN_func_8002A520; struct { u8 unkC8; u8 unkC9; } kSC06_018_80183A00; struct { u8 unkC8; u8 unkC9; } kMAIN_012_80131B14; struct { u8 unkC8; u8 unkC9; } kSC02_027_80181328; struct { u8 unkC8; u8 unkC9; } kSC05_010_80181B4C; struct { u8 unkC8; u8 unkC9; } kSC06_016_8017EC50; struct { u8 unkC8; u8 unkC9; } kSC06_018_801932EC; struct { u8 unkC8; u8 unkC9; } kSC06_030_8017DF70; struct { u8 unkC8; u8 unkC9; } kSC06_033_801895AC; struct { u8 unkC8; u8 unkC9; } kSC06_033_80189B9C; struct { u8 unkC8; u8 unkC9; } kSC06_033_80189D30; struct { u8 unkC8; u8 unkC9; } kSC06_033_80189EC4; struct { u8 unkC8; u8 unkC9; } kSC06_033_8018A318; struct { u8 unkC8; u8 unkC9; } kSC06_033_8018A6F8; struct { u8 unkC8; u8 unkC9; } kSC07_003_801A3190; struct { u8 unkC8; u8 unkC9; } kSC06_033_8018AAF4; struct { u8 unkC8; u8 unkC9; } kSC02_026_8017E130; struct { u8 unkC8; u8 unkC9; } kSC02_027_80185760; struct { u8 unkC8; u8 unkC9; } kSC02_028_80186144; struct { u8 unkC8; } kSC03_028_80183020; struct { u8 unkC8; u8 unkC9; } kSC06_032_8019303C; struct { u8 unkC8; } kSC05_010_80183C84; } extF;
    /* 0x00cc */ union { s32 val; void *p; struct { s16 lo; s16 hi; } i; struct { u16 lo; u16 hi; } u; } unkCC;
    /* 0x00d0 */ union { s32 val; void *p; struct { s16 lo; s16 hi; } i; struct { u16 lo; u16 hi; } u; } unkD0;
    /* 0x00d4 */ union { struct Unkstruct_801202A0 *p; struct { u16 lo; u16 hi; } u; s32 val; struct Unkstruct_800B5BD8 *s; } unkD4; /* s: kind 418 (SC03_093-097) keeps a sprite here (func_80180208 and copies); its +0x28/+0x2A writes were extA variants until T18.c15 */
    /* 0x00d8 */ union { s32 val; void *p; struct { u16 lo; u16 hi; } u; } unkD8;
    /* 0x00dc */ union { s32 w[7]; /* 0xDC-0xF7 word view: the script interpreter (func_80178D40, ex Actor_80178D40) indexes it */ struct { union { s32 val; struct { union { s16 s; u16 u; } lo; union { u16 u; s16 s; } hi; } i; void *p; } unkDC; union { u8 raw[0x18]; struct { s32 unkE0; s32 unkE4; } kSC07_004_801AD068; struct { s16 unkE0; u8 pad2[0x6]; union { u32 u; s32 s; } unkE8; } kSC02_005_801831A4; struct { s32 unkE0; u8 pad4[0x4]; s32 unkE8; } kSC06_032_80182588; struct { union { s32 s; u32 u; } unkE0; s32 unkE4; s32 unkE8; } kSC07_003_801A01D4; struct { s32 unkE0; u8 pad4[0x4]; s32 unkE8; } kSC05_003_80180E58; struct { u8 pad0[0x8]; s32 unkE8; } kcls_0b021a360555; struct { u8 pad0[0x4]; s32 unkE4; s32 unkE8; } kcls_725f5619f306; struct { u8 pad0[0x4]; s32 unkE4; } kcls_b6ccd7c343f8; struct { s32 unkE0; s32 unkE4; } kcls_e21d5c1a17d3; struct { u8 pad0[0x4]; s32 unkE4; } kcls_fed17b629198; struct { s32 unkE0; } kSC02_039_8017DDB0; struct { u8 pad0[0x4]; s32 unkE4; s32 unkE8; } kSC06_014_8017E220; struct { union { s16 s; u16 u; } unkE0; s16 unkE2; } kSC03_117_8017E9BC; struct { s32 unkE0; s32 unkE4; u8 pad8[0x8]; s32 unkF0; } kSC01_080_8017F500; struct { u8 pad0[0x4]; s32 unkE4; s32 unkE8; u8 padC[0x8]; s32 unkF4; } kSC01_080_8017FF78; struct { s32 unkE0; } kSC06_029_80182D74; struct { s32 unkE0; s32 unkE4; s32 unkE8; u8 padC[0x8]; s32 unkF4; } kSC02_041_80181B04; struct { s32 unkE0; } kSC02_026_80182E1C; struct { s32 unkE0; } kSC07_002_80182228; struct { s32 unkE0; s32 unkE4; } kSC03_006_801838FC; struct { s32 unkE0; } kSC03_118_80184940; struct { s32 unkE0; u8 pad4[0x2]; u16 unkE6; } kSC02_011_8018C734; struct { s32 unkE0; s32 unkE4; s32 unkE8; s16 unkEC; s16 unkEE; } kSC06_018_80183A00; struct { s32 unkE0; } kSC03_105_80188040; struct { u8 pad0[0x6]; s16 unkE6; u8 pad8[0x4]; s16 unkEC; s16 unkEE; } kSC07_004_801A2D78; struct { union { s16 s; u16 u; } unkE0; } kSC03_029_80182B90; struct { s32 unkE0; } kSC03_007_8017EF98; struct { u8 pad0[0x4]; s16 unkE4; s16 unkE6; } kSC06_022_801813C8; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_801816FC; struct { s32 unkE0; } kSC06_029_8017EB24; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC02_011_80182D60; struct { u8 pad0[0x2]; s16 unkE2; u16 unkE4; u16 unkE6; u16 unkE8; s16 unkEA; s16 unkEC; s16 unkEE; s16 unkF0; union { s16 s; u16 u; } unkF2; u16 unkF4; } kSC04_011_801832DC; struct { s32 unkE0; s32 unkE4; u8 pad8[0xC]; s32 unkF4; } kSC03_105_80180100; struct { s16 unkE0; u8 pad2[0x2]; s16 unkE4; u8 pad6[0x2]; s16 unkE8; s16 unkEA; } kSC03_006_801875B4; struct { s32 unkE0; s32 unkE4; } kSC01_077_8017F6D8; struct { u8 pad0[0x8]; s32 unkE8; } kSC01_077_80183834; struct { s32 unkE0; s32 unkE4; } kSC01_077_80186574; struct { s32 unkE0; s32 unkE4; } kSC01_084_801801BC; struct { s32 unkE0; s32 unkE4; } kSC01_084_801814E8; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_80181900; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_801820E4; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_801824D0; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_80182A8C; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_80183610; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_801838A8; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_80185E80; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_8018675C; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_80186F14; struct { s32 unkE0; } kSC02_017_8017FE3C; struct { u8 pad0[0x4]; s32 unkE4; } kSC02_017_8017FE78; struct { s32 unkE0; } kSC02_026_8017E130; struct { s32 unkE0; } kSC02_031_80182078; struct { s32 unkE0; s32 unkE4; } kSC02_035_80183258; struct { s32 unkE0; } kSC02_039_8017E910; struct { s32 unkE0; s32 unkE4; } kSC03_001_8017FBC4; struct { u8 pad0[0x8]; s32 unkE8; } kSC03_001_80187994; struct { u8 pad0[0x8]; s32 unkE8; } kSC03_001_80187A64; struct { s32 unkE0; } kSC03_006_801865E8; struct { s32 unkE0; } kSC03_007_80181668; struct { s32 unkE0; } kSC03_010_8017EE30; struct { s32 unkE0; s32 unkE4; } kSC03_089_80183FF0; struct { u8 pad0[0xc]; s16 unkEC; s16 unkEE; } kSC03_089_80185880; struct { s32 unkE0; } kSC03_090_8018745C; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC03_093_801813E0; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_094_801837FC; struct { s32 unkE0; } kSC03_105_8017EC5C; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC03_107_8017D92C; struct { u8 pad0[0x8]; s32 unkE8; } kSC03_125_8017F554; struct { s32 unkE0; s32 unkE4; } kSC04_000_80180FBC; struct { u8 pad0[0x14]; s32 unkF4; } kSC04_002_80185264; struct { u8 pad0[0x8]; s32 unkE8; } kSC04_002_801853F8; struct { s32 unkE0; } kSC04_002_80185DA8; struct { s32 unkE0; } kSC04_002_80186078; struct { u8 pad0[0x14]; s32 unkF4; } kSC04_002_8018615C; struct { u8 pad0[0x8]; s32 unkE8; } kSC04_002_80187174; struct { s32 unkE0; u8 pad4[0x4]; s32 unkE8; } kSC04_002_801871EC; struct { u8 pad0[0x4]; s32 unkE4; } kSC04_006_8017F354; struct { s32 unkE0; } kSC04_011_8018914C; struct { u8 pad0[0x14]; s32 unkF4; } kSC04_016_8017DCDC; struct { s32 unkE0; s32 unkE4; } kSC05_005_8017FA1C; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC05_005_8017FABC; struct { u8 pad0[0xc]; s16 unkEC; } kSC05_005_8017FD44; struct { s32 unkE0; } kSC05_010_8018060C; struct { s32 unkE0; } kSC06_008_8017FAD4; struct { u8 pad0[0x12]; u16 unkF2; } kSC06_018_80188088; struct { s32 unkE0; } kSC06_018_801899F8; struct { s32 unkE0; } kSC06_018_8018B65C; struct { s32 unkE0; } kSC06_022_8017DBA4; struct { s32 unkE0; } kSC06_022_8017E920; struct { s32 unkE0; s32 unkE4; } kSC06_024_8017D804; struct { u8 pad0[0x8]; s32 unkE8; } kSC06_025_80181260; struct { s32 unkE0; u8 pad4[0x4]; s32 unkE8; } kSC06_029_80181848; struct { s32 unkE0; } kSC06_029_80181DF8; struct { s32 unkE0; u8 pad4[0x10]; s32 unkF4; } kSC06_029_801827D0; struct { s32 unkE0; s32 unkE4; s32 unkE8; s16 unkEC; s16 unkEE; u8 pad10[0x2]; u16 unkF2; } kSC06_029_80183D48; struct { s32 unkE0; } kSC06_029_80189B38; struct { s32 unkE0; s32 unkE4; } kSC06_033_8017DDC4; struct { s32 unkE0; } kSC07_001_8017E448; struct { s32 unkE0; } kSC07_003_801A50FC; struct { u8 pad0[0x14]; s32 unkF4; } kSC07_007_801802BC; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kcls_225ef5f3fe50; struct { s32 unkE0; } kcls_6b369e5acc38; struct { s32 unkE0; } kcls_9dcd4c27736a; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kcls_9e05b01e804c; struct { s32 unkE0; } kcls_f24504189a72; struct { u8 pad0[0x14]; s32 unkF4; } kcls_f3aff223cfe8; struct { s32 unkE0; } kSC03_024_80186BE4; struct { s32 unkE0; } kSC07_002_801827DC; struct { s32 unkE0; } kcls_25e5e01a3229; struct { s32 unkE0; } kcls_8d77555e2e34; struct { union { s32 val; struct { u16 lo; u16 hi; } i; } unkE0; u8 pad4[0x8]; s16 unkEC; s16 unkEE; u8 pad10[0x4]; s32 unkF4; } kSC06_018_801932EC; struct { u8 pad0[0x14]; s32 unkF4; } kSC06_033_80189B9C; struct { u8 pad0[0x14]; s32 unkF4; } kSC06_033_80189D30; struct { s32 unkE0; } kSC02_011_8018E678; struct { s32 unkE0; } kSC02_039_8017E758; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_041_80183AE8; struct { s32 unkE0; } kSC03_013_8017F5FC; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC03_108_8017F0B0; struct { s32 unkE0; } kSC03_112_8017EBE4; struct { s32 unkE0; s32 unkE4; s32 unkE8; s16 unkEC; } kSC05_003_8017F68C; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC07_003_801A5860; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kcls_86815c334e35; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_80181F04; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_8018203C; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_801821C8; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_80183074; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_80187D0C; struct { u8 pad0[0x8]; s32 unkE8; } kSC02_005_80187E18; struct { s32 unkE0; } kSC02_011_8018E5E4; struct { u8 pad0[0x4]; s32 unkE4; s32 unkE8; } kSC04_002_8018543C; struct { s32 unkE0; } kSC04_006_8017EB54; struct { u8 pad0[0xc]; s16 unkEC; } kSC05_005_80180DF0; struct { u8 pad0[0x8]; s32 unkE8; } kSC05_007_8017F42C; struct { s32 unkE0; } kSC06_029_80183B1C; struct { s32 unkE0; } kSC07_003_801A23FC; struct { s32 unkE0; } kSC02_000_801868D4; struct { s32 unkE0; s32 unkE4; } kSC02_005_801894C8; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC02_026_8018144C; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC02_035_8017F2A0; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC03_090_801859A8; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC03_091_80186850; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC03_094_80180628; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC03_098_80180E30; struct { s32 unkE0; } kSC06_022_80180EA4; struct { s32 unkE0; } kSC06_024_8018337C; struct { s32 unkE0; } kSC07_003_801A5638; struct { s32 unkE0; s32 unkE4; } kSC07_004_801AD1E4; struct { s32 unkE0; } kSC02_039_8017E794; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_095_8017F9A8; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_096_8017F528; struct { s32 unkE0; } kSC03_108_8017E27C; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC03_110_8017F43C; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC03_112_80181054; struct { u8 pad0[0x8]; s32 unkE8; } kSC04_007_80182B48; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC05_001_80182D7C; struct { s32 unkE0; } kSC06_018_80187924; struct { s32 unkE0; } kSC06_020_80181A94; struct { s32 unkE0; } kSC06_022_801859B8; struct { s32 unkE0; } kSC06_024_80187E90; struct { s32 unkE0; } kSC06_029_8018562C; struct { s32 unkE0; } kSC06_032_801826C8; struct { s32 unkE0; } kSC06_032_80186834; struct { s32 unkE0; } kSC06_033_801863AC; struct { s32 unkE0; s32 unkE4; s32 unkE8; } kSC07_011_8017DD78; struct { union { s32 val; struct { u16 lo; u16 hi; } i; } unkE0; union { s32 val; struct { u16 lo; u16 hi; } i; } unkE4; } kSC06_018_8018A61C; struct { u8 pad0[0x8]; s32 unkE8; } kSC04_005_801864DC; struct { s32 unkE0; s32 unkE4; } kSC06_018_8018BB18; struct { s32 unkE0; s32 unkE4; } kSC06_032_80186CF0; struct { s32 unkE0; u8 pad4[0x8]; s16 unkEC; s16 unkEE; } kSC06_032_8019303C; struct { s32 unkE0; u8 pad4[0x8]; s16 unkEC; s16 unkEE; } kSC06_033_8018BCD4; struct { s32 unkE0; s32 unkE4; } kSC03_001_80180A88; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_001_8018190C; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_001_80181ED4; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_001_80182824; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_001_8018333C; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_001_80183A88; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_001_80184210; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_001_80184900; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_001_801850A0; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_001_801862B4; struct { u8 pad0[0x14]; s16 unkF4; } kSC03_001_80187DAC; struct { u8 pad0[0x4]; s32 unkE4; } kSC03_002_80181054; struct { s32 unkE0; } kSC03_002_80181808; struct { u8 pad0[0x2]; s16 unkE2; } kSC03_010_8017F7E0; struct { u8 pad0[0x2]; u16 unkE2; s16 unkE4; } kSC03_011_8017E620; struct { u8 pad0[0x8]; s16 unkE8; } kSC03_011_8017EB4C; struct { union { u16 u; s16 s; } unkE0; u16 unkE2; u16 unkE4; u16 unkE6; u16 unkE8; } kSC03_012_8017D890; struct { s32 unkE0; } kSC03_014_80183CF0; struct { u8 pad0[0x8]; u16 unkE8; } kSC03_014_80187D80; struct { u8 pad0[0x8]; u16 unkE8; } kSC03_028_80182E2C; struct { union { u32 u; s32 s; } unkE0; union { u32 u; s32 s; } unkE4; union { u32 u; s32 s; } unkE8; } kSC03_028_80184A40; struct { s32 unkE0; } kSC03_090_80187378; struct { s32 unkE0; } kSC03_102_801809C4; struct { union { s16 s; u16 u; } unkE0; union { s16 s; u16 u; } unkE2; } kSC03_103_8017E7D0; struct { u8 pad0[0x2]; s16 unkE2; } kSC03_118_80183280; struct { s32 unkE0; } kSC03_124_8017E8AC; struct { s32 unkE0; } kSC03_125_8017EDD8; struct { u8 pad0[0x4]; s32 unkE4; } kSC04_018_80180B6C; struct { s32 unkE0; s32 unkE4; } kSC04_018_80181924; struct { u8 pad0[0x4]; s32 unkE4; } kSC04_018_80182C98; struct { u8 pad0[0x4]; s32 unkE4; } kSC04_018_80183438; struct { u8 pad0[0x4]; s32 unkE4; } kSC04_018_80183A68; struct { u8 pad0[0x4]; s32 unkE4; } kSC04_018_80184130; struct { s32 unkE0; } kSC04_020_8017EFF4; struct { s32 unkE0; } kSC05_017_8018BB38; struct { s32 unkE0; } kSC05_018_80182290; struct { u8 pad0[0x8]; u16 unkE8; } kSC06_030_801800D4; } extC; } f; } blkDC;
    /* 0x00f8 */ union { union { s32 s; u32 u; } val; struct { s16 lo; u16 hi; } i; } unkF8;
    /* 0x00fc */ union { u16 u; s16 s; u8 b; s8 sb; } unkFC;
    /* 0x00fe */ union { s16 s; u16 u; } unkFE;
    /* 0x0100 */ union { u8 raw[0xA]; struct { u8 pad0[0x4]; s16 unk104; } kSC03_011_8017EB4C; struct { union { u16 u; s16 s; } unk100; } kSC06_018_8017FBE8; struct { union { u16 u; s16 s; } unk100; s16 unk102; } kSC02_011_801894E0; struct { u8 pad0[0x2]; s16 unk102; } kSC07_000_80180200; struct { u16 unk100; } kSC02_017_8017DF34; struct { s16 unk100; s16 unk102; } kSC02_005_801831A4; struct { u8 pad0[0x6]; s16 unk106; } kcls_0b021a360555; struct { s16 unk100; s16 unk102; } kcls_e21d5c1a17d3; struct { s16 unk100; } kcls_01aff3bded90; struct { u8 pad0[0x2]; s16 unk102; } kcls_24b770e3f65a; struct { u8 pad0[0x8]; u16 unk108; } kcls_2bf2dadd09e0; struct { u8 pad0[0x8]; u16 unk108; } kcls_435526158d52; struct { s16 unk100; } kcls_62ffa82e5d5f; struct { u8 pad0[0x4]; s16 unk104; } kcls_640487f29081; struct { u8 pad0[0x6]; s16 unk106; u16 unk108; } kcls_68d72a52b3dc; struct { u8 pad0[0x6]; s16 unk106; } kcls_6d2ffa14de65; struct { u8 pad0[0x2]; s16 unk102; } kcls_7d23846950fc; struct { u8 pad0[0x2]; s16 unk102; } kcls_8dd04c3ce13b; struct { s16 unk100; } kcls_9212f2c13ba1; struct { union { u16 u; s16 s; } unk100; } kSC02_005_80184D44; struct { union { u16 u; s16 s; } unk100; s16 unk102; } kSC02_005_8018C08C; struct { union { u16 u; s16 s; } unk100; s16 unk102; } kSC02_011_8018C734; struct { union { u16 u; s16 s; } unk100; } kSC02_031_80183314; struct { union { u16 u; s16 s; } unk100; union { u16 u; s16 s; } unk102; } kSC02_035_80181E98; struct { union { u16 u; s16 s; } unk100; } kSC03_006_80182290; struct { union { u16 u; s16 s; } unk100; } kSC03_031_801815EC; struct { union { u16 u; s16 s; } unk100; } kSC03_105_8017E794; struct { union { u16 u; s16 s; } unk100; s16 unk102; } kSC04_011_8018445C; struct { union { u16 u; s16 s; } unk100; s16 unk102; s16 unk104; u8 pad6[0x2]; u16 unk108; } kSC04_016_8017DCDC; struct { s16 unk100; union { u16 u; s16 s; } unk102; } kSC06_000_801846BC; struct { union { u16 u; s16 s; } unk100; s16 unk102; } kSC06_010_80180450; struct { u16 unk100; u8 pad2[0x2]; s16 unk104; union { u16 u; s16 s; } unk106; u16 unk108; } kSC06_018_8018A61C; struct { s16 unk100; s16 unk102; union { u16 u; s16 s; } unk104; } kSC06_033_8017DDC4; struct { union { u16 u; s16 s; } unk100; union { u16 u; s16 s; } unk102; s16 unk104; u8 pad6[0x2]; u16 unk108; } kSC07_002_80182228; struct { union { u16 u; s16 s; } unk100; union { u16 u; s16 s; } unk102; s16 unk104; s16 unk106; u16 unk108; } kSC07_004_801A2D78; struct { s16 unk100; s16 unk102; } kSC03_010_8017E660; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; } kSC03_013_8017E9CC; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; } kSC01_009_8017F360; struct { u8 pad0[0x8]; u16 unk108; } kSC06_030_801800D4; struct { u8 pad0[0x4]; s16 unk104; } kSC01_005_8017FF74; struct { s16 unk100; } kSC02_028_801808D0; struct { u8 pad0[0x6]; u16 unk106; } kSC03_029_80180E94; struct { u8 pad0[0x2]; s16 unk102; } kSC06_008_80182E8C; struct { s16 unk100; s16 unk102; u8 pad4[0x2]; s16 unk106; } kSC02_016_80181AE8; struct { u16 unk100; } kcls_43c2c594289f; struct { s16 unk100; s16 unk102; } kSC03_089_80181F60; struct { s16 unk100; } kSC02_041_80180438; struct { s16 unk100; } kSC02_027_8018339C; struct { s16 unk100; s16 unk102; s16 unk104; } kSC02_005_8018550C; struct { u8 pad0[0x8]; u16 unk108; } kSC03_014_80187D80; struct { s16 unk100; } kSC07_000_8017F3C0; struct { u8 pad0[0x2]; s16 unk102; } kSC07_000_801801C4; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC03_002_8017CF30; struct { s16 unk100; s16 unk102; } kSC01_080_8017F500; struct { union { s16 s; u16 u; } unk100; s16 unk102; union { s16 s; u16 u; } unk104; } kSC02_017_80184B18; struct { union { s16 s; u16 u; } unk100; u8 pad2[0x2]; union { s16 s; u16 u; } unk104; s16 unk106; } kSC03_006_801838FC; struct { s16 unk100; union { s16 s; u16 u; } unk102; s16 unk104; } kSC03_107_8017D92C; struct { s16 unk100; s16 unk102; } kSC02_011_8018BFBC; struct { s16 unk100; s16 unk102; s16 unk104; } kSC03_007_8017E0B4; struct { union { s16 s; u16 u; } unk100; union { s16 s; u16 u; } unk102; } kSC03_007_801827CC; struct { s16 unk100; s16 unk102; } kSC06_029_8017EB24; struct { s16 unk100; s16 unk102; s16 unk104; } kSC03_007_80181668; struct { u8 pad0[0x2]; s16 unk102; } kSC03_023_8017DF1C; struct { u8 pad0[0x4]; s16 unk104; } kSC02_011_80182D60; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC04_011_801832DC; struct { u8 pad0[0x2]; s16 unk102; } kSC02_005_801824D0; struct { u8 pad0[0x8]; u16 unk108; } kSC02_017_8017FE78; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; } kSC02_035_80183258; struct { s16 unk100; } kSC02_039_8017E910; struct { u8 pad0[0x6]; s16 unk106; } kSC03_001_80187994; struct { u8 pad0[0x6]; s16 unk106; } kSC03_001_80187A64; struct { s16 unk100; u8 pad2[0x2]; s16 unk104; s16 unk106; u16 unk108; } kSC03_093_801813E0; struct { s16 unk100; u8 pad2[0x2]; s16 unk104; s16 unk106; u16 unk108; } kSC03_094_801837FC; struct { s16 unk100; s16 unk102; } kSC03_105_8017EC5C; struct { u8 pad0[0x6]; s16 unk106; } kSC03_125_8017F554; struct { u8 pad0[0x6]; s16 unk106; u16 unk108; } kSC06_018_8018B65C; struct { s16 unk100; s16 unk102; u8 pad4[0x2]; s16 unk106; u16 unk108; } kSC06_024_8017D804; struct { s16 unk100; } kSC06_029_80181848; struct { s16 unk100; s16 unk102; u8 pad4[0x2]; s16 unk106; u16 unk108; } kSC01_005_80182000; struct { u8 pad0[0x2]; s16 unk102; } kSC01_009_8017FA14; struct { u8 pad0[0x6]; s16 unk106; u16 unk108; } kSC01_009_8017FDAC; struct { u8 pad0[0x8]; u16 unk108; } kSC01_009_8017FE10; struct { s16 unk100; } kSC01_009_80182634; struct { s16 unk100; } kSC01_077_80183834; struct { u8 pad0[0x4]; s16 unk104; } kSC02_005_80182998; struct { s16 unk100; } kSC02_005_80184E30; struct { s16 unk100; s16 unk102; } kSC02_005_80185E54; struct { union { u16 u; s16 s; } unk100; } kSC02_005_80188BB4; struct { s16 unk100; s16 unk102; s16 unk104; } kSC02_005_80189AF4; struct { s16 unk100; } kSC02_005_8018A968; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; u8 pad6[0x2]; u16 unk108; } kSC02_011_8017D50C; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC02_011_8017D710; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; u8 pad6[0x2]; u16 unk108; } kSC02_011_8017DB04; struct { u8 pad0[0x8]; u16 unk108; } kSC02_011_8017E024; struct { s16 unk100; } kSC02_011_8017E220; struct { s16 unk100; } kSC02_011_80189B28; struct { s16 unk100; } kSC02_011_801900B4; struct { s16 unk100; s16 unk102; } kSC02_016_8017F1C8; struct { s16 unk100; } kSC02_017_8017FE3C; struct { u8 pad0[0x8]; u16 unk108; } kSC02_017_8018068C; struct { s16 unk100; } kSC02_017_801876AC; struct { s16 unk100; } kSC02_026_8017DFE0; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; } kSC02_026_8017E130; struct { s16 unk100; s16 unk102; } kSC02_026_8017EEB0; struct { union { u16 u; s16 s; } unk100; } kSC02_026_80182F00; struct { u8 pad0[0x2]; s16 unk102; } kSC02_026_80183CAC; struct { s16 unk100; } kSC02_026_80184494; struct { u8 pad0[0x2]; s16 unk102; } kSC02_026_80184DA4; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; } kSC02_027_80183938; struct { s16 unk100; u8 pad2[0x2]; s16 unk104; s16 unk106; } kSC02_027_80189E74; struct { s16 unk100; } kSC02_039_8017DFE8; struct { u8 pad0[0x2]; s16 unk102; } kSC02_039_8017E758; struct { s16 unk100; } kSC02_039_8017E794; struct { s16 unk100; s16 unk102; } kSC02_039_8017EE9C; struct { s16 unk100; s16 unk102; } kSC02_041_80180ED4; struct { s16 unk100; u8 pad2[0x2]; s16 unk104; } kSC03_001_8017DA48; struct { s16 unk100; } kSC03_001_8017F920; struct { s16 unk100; s16 unk102; u8 pad4[0x4]; u16 unk108; } kSC03_001_80187DAC; struct { u8 pad0[0x8]; u16 unk108; } kSC03_001_80188618; struct { u8 pad0[0x8]; u16 unk108; } kSC03_001_801886A0; struct { u8 pad0[0x2]; s16 unk102; } kSC03_002_80182298; struct { u8 pad0[0x2]; s16 unk102; } kSC03_002_801822C8; struct { s16 unk100; } kSC03_006_8018A86C; struct { s16 unk100; } kSC03_014_801848E4; struct { u8 pad0[0x8]; u16 unk108; } kSC03_014_80185144; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; } kSC03_014_80187CA8; struct { s16 unk100; } kSC03_014_80188DC4; struct { s16 unk100; } kSC03_024_801824F8; struct { s16 unk100; s16 unk102; } kSC03_024_80186A1C; struct { s16 unk100; u8 pad2[0x4]; s16 unk106; u16 unk108; } kSC03_024_80186BE4; struct { u8 pad0[0x8]; u16 unk108; } kSC03_028_80182E2C; struct { s16 unk100; } kSC03_028_80184A40; struct { s16 unk100; } kSC03_028_80186754; struct { s16 unk100; } kSC03_028_801EC450; struct { u8 pad0[0x8]; u16 unk108; } kSC03_029_80182708; struct { s16 unk100; } kSC03_030_8017FB04; struct { s16 unk100; } kSC03_089_80183FF0; struct { s16 unk100; union { s16 s; u16 u; } unk102; s16 unk104; } kSC03_101_8017FEE0; struct { s16 unk100; } kSC03_105_8017F1F8; struct { s16 unk100; } kSC03_105_801867D0; struct { s16 unk100; } kSC03_105_8018868C; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC03_107_80180428; struct { u8 pad0[0x8]; u16 unk108; } kSC03_107_801819C8; struct { s16 unk100; } kSC03_111_80180FB4; struct { s16 unk100; } kSC03_116_80180FBC; struct { s16 unk100; } kSC03_116_801814B0; struct { union { s16 s; u16 u; } unk100; u16 unk102; u8 pad4[0x2]; s16 unk106; u16 unk108; } kSC03_117_8017E9BC; struct { s16 unk100; s16 unk102; } kSC03_118_801825B0; struct { u8 pad0[0x8]; u16 unk108; } kSC03_118_80188DE4; struct { s16 unk100; s16 unk102; s16 unk104; } kSC03_121_8017F4C8; struct { s16 unk100; } kSC03_124_801814A4; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; s16 unk106; } kSC04_002_801831B8; struct { s16 unk100; } kSC04_002_80184430; struct { u8 pad0[0x6]; s16 unk106; u16 unk108; } kSC04_003_8017E040; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; } kSC04_003_8017F858; struct { u8 pad0[0x6]; s16 unk106; } kSC04_007_8017FB1C; struct { u8 pad0[0x4]; s16 unk104; } kSC04_011_80188818; struct { u8 pad0[0x8]; u16 unk108; } kSC04_011_8018914C; struct { s16 unk100; } kSC04_011_801896BC; struct { u8 pad0[0x6]; s16 unk106; u16 unk108; } kSC04_011_8018A3F0; struct { u8 pad0[0x8]; u16 unk108; } kSC04_011_8018AA34; struct { u8 pad0[0x6]; s16 unk106; u16 unk108; } kSC04_011_8018B024; struct { s16 unk100; s16 unk102; } kSC04_011_8018FCC8; struct { s16 unk100; } kSC04_015_801833C8; struct { s16 unk100; } kSC04_016_8017F4A0; struct { s16 unk100; } kSC05_000_8017DC9C; struct { s16 unk100; s16 unk102; } kSC05_001_8017FAC8; struct { s16 unk100; } kSC05_008_8017E318; struct { s16 unk100; } kSC05_008_801823B8; struct { s16 unk100; } kSC05_010_80184298; struct { s16 unk100; s16 unk102; s16 unk104; } kSC05_010_80184AA4; struct { u8 pad0[0x8]; u16 unk108; } kSC05_011_8017D4A4; struct { u8 pad0[0x8]; u16 unk108; } kSC05_011_8017D610; struct { s16 unk100; union { u16 u; s16 s; } unk102; } kSC06_000_80182950; struct { s16 unk100; } kSC06_000_80183574; struct { s16 unk100; s16 unk102; } kSC06_008_8017F9FC; struct { s16 unk100; s16 unk102; s16 unk104; } kSC06_008_80181EE0; struct { s16 unk100; s16 unk102; } kSC06_010_80183884; struct { s16 unk100; u8 pad2[0x2]; s16 unk104; } kSC06_010_80183B10; struct { s16 unk100; u8 pad2[0x2]; s16 unk104; } kSC06_010_801857F4; struct { s16 unk100; } kSC06_010_801858F4; struct { s16 unk100; } kSC06_018_80183A00; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC06_018_80187924; struct { u8 pad0[0x4]; s16 unk104; } kSC06_018_80188088; struct { s16 unk100; s16 unk102; } kSC06_018_801894B4; struct { s16 unk100; } kSC06_018_8018BB18; struct { s16 unk100; s16 unk102; } kSC06_022_8017E40C; struct { u8 pad0[0x6]; union { u16 u; s16 s; } unk106; } kSC06_022_80180310; struct { u8 pad0[0x8]; u16 unk108; } kSC06_022_801813C8; struct { s16 unk100; s16 unk102; s16 unk104; } kSC06_030_8017E120; struct { u8 pad0[0x2]; s16 unk102; } kSC06_030_8017F0A0; struct { u8 pad0[0x8]; u16 unk108; } kSC06_033_8017E594; struct { u8 pad0[0x6]; s16 unk106; u16 unk108; } kSC07_000_80180584; struct { u8 pad0[0x6]; s16 unk106; u16 unk108; } kSC07_000_80180818; struct { s16 unk100; s16 unk102; s16 unk104; u8 pad6[0x2]; u16 unk108; } kSC07_002_801827DC; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; } kSC07_002_80183A70; struct { u8 pad0[0x8]; s16 unk108; } kSC02_011_8018EBEC; struct { s16 unk100; s16 unk102; } kSC07_003_801A50FC; struct { s16 unk100; s16 unk102; s16 unk104; } kSC07_004_801A5B20; struct { s16 unk100; s16 unk102; } kSC07_004_801A77CC; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC07_004_801A8954; struct { s16 unk100; s16 unk102; s16 unk104; } kSC07_006_80189098; struct { s16 unk100; s16 unk102; } kcls_1e87b69413a8; struct { s16 unk100; s16 unk102; s16 unk104; u8 pad6[0x2]; u16 unk108; } kcls_25e5e01a3229; struct { u8 pad0[0x6]; s16 unk106; } kcls_33a5615dfde0; struct { s16 unk100; s16 unk102; } kcls_4a3ca2577184; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; } kcls_5046188d617f; struct { s16 unk100; } kcls_5e983477cf41; struct { s16 unk100; } kcls_719635c74644; struct { u8 pad0[0x4]; s16 unk104; } kcls_8074e7d22391; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; s16 unk106; } kcls_817cdb5a1717; struct { s16 unk100; u8 pad2[0x4]; s16 unk106; u16 unk108; } kcls_8d77555e2e34; struct { u8 pad0[0x6]; s16 unk106; u16 unk108; } kcls_9151cf12b140; struct { s16 unk100; s16 unk102; } kcls_993fd4d01ab4; struct { s16 unk100; } kcls_9dcd4c27736a; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; } kcls_9df4729513ee; struct { s16 unk100; } kcls_9e975aed2dc2; struct { s16 unk100; s16 unk102; } kcls_d736d5fea74c; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; } kcls_e0c08fca20f2; struct { u8 pad0[0x2]; s16 unk102; } kcls_f24504189a72; struct { s16 unk100; } kSC02_026_801808D0; struct { s16 unk100; } kSC03_092_80181694; struct { s16 unk100; s16 unk102; } kSC05_010_801828E0; struct { s16 unk100; } kSC05_010_80182AC0; struct { s16 unk100; } kSC02_000_801898C8; struct { union { s16 s; u16 u; } unk100; union { s16 s; u16 u; } unk102; s16 unk104; u16 unk106; s16 unk108; } kSC02_035_8017D548; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC03_007_80185898; struct { s16 unk100; } kSC03_092_801838CC; struct { u8 pad0[0x8]; u16 unk108; } kSC04_011_8018A748; struct { s16 unk100; s16 unk102; } kSC06_022_80180EA4; struct { s16 unk100; u8 pad2[0x6]; u16 unk108; } kSC07_010_80180138; struct { s16 unk100; s16 unk102; } kcls_b4ff33593fa2; struct { u8 pad0[0x4]; s16 unk104; } kSC01_009_8018144C; struct { u8 pad0[0x4]; s16 unk104; } kSC01_009_80181960; struct { u8 pad0[0x4]; s16 unk104; } kSC01_009_80181988; struct { u8 pad0[0x4]; s16 unk104; s16 unk106; } kSC01_009_80181C64; struct { s16 unk100; } kSC02_005_801846CC; struct { s16 unk100; } kSC02_005_801877FC; struct { s16 unk100; } kSC03_010_8017E3B8; struct { u8 pad0[0x2]; s16 unk102; } kSC03_118_801825EC; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; s16 unk106; } kSC04_002_80181F40; struct { s16 unk100; } kSC04_002_80181FE0; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; s16 unk106; } kSC04_011_801837C4; struct { u8 pad0[0x2]; s16 unk102; } kSC04_011_80188650; struct { s16 unk100; } kSC06_018_8018D40C; struct { s16 unk100; } kSC06_018_8018D514; struct { s16 unk100; } kSC06_022_8018034C; struct { s16 unk100; } kSC06_029_801DDB28; struct { u8 pad0[0x6]; s16 unk106; } kSC06_030_801806D4; struct { s16 unk100; } kSC07_004_801A5414; struct { s16 unk100; } kSC07_010_8017E3EC; struct { u8 pad0[0x8]; u16 unk108; } kSC01_009_8017FFD0; struct { u8 pad0[0x2]; s16 unk102; } kSC01_009_80182740; struct { s16 unk100; } kSC02_011_801901C0; struct { s16 unk100; } kSC02_027_80184BE4; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; s16 unk106; } kSC02_027_80185760; struct { s16 unk100; } kSC02_027_801877E4; struct { s16 unk100; } kSC02_028_801855C8; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; s16 unk106; } kSC02_028_80186144; struct { s16 unk100; } kSC02_028_801881C8; struct { s16 unk100; } kSC02_035_8017E724; struct { s16 unk100; } kSC02_037_80182B58; struct { s16 unk100; } kSC03_089_801830D8; struct { s16 unk100; } kSC03_090_80182DB4; struct { s16 unk100; } kSC03_091_80183C5C; struct { s16 unk100; } kSC03_094_8017FAAC; struct { s16 unk100; } kSC03_098_801802B4; struct { s16 unk100; } kSC03_099_8017E518; struct { s16 unk100; } kSC03_100_8017FF44; struct { s16 unk100; } kSC03_102_80182514; struct { s16 unk100; } kSC03_103_8017F784; struct { s16 unk100; } kSC03_104_80186F28; struct { s16 unk100; } kSC03_109_8017DE74; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC03_112_801840E4; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC03_117_8018316C; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC03_118_801878B8; struct { s16 unk100; } kSC04_000_80182DAC; struct { s16 unk100; } kSC04_009_8017E618; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; u16 unk108; } kSC05_004_801806FC; struct { s16 unk100; } kSC05_009_8017E55C; struct { u8 pad0[0x2]; s16 unk102; } kSC06_008_801821F8; struct { s16 unk100; } kSC06_008_80184B5C; struct { u8 pad0[0x2]; s16 unk102; } kSC06_010_801846AC; struct { u8 pad0[0x2]; s16 unk102; } kSC06_018_80182004; struct { s16 unk100; s16 unk102; } kSC06_018_801932EC; struct { u8 pad0[0x2]; s16 unk102; } kSC06_022_80189EB4; struct { s16 unk100; s16 unk102; } kSC06_024_8018337C; struct { u8 pad0[0x2]; s16 unk102; } kSC06_024_8018C38C; struct { s16 unk100; } kSC06_029_80183D48; struct { u8 pad0[0x2]; s16 unk102; } kSC06_032_80189D44; struct { s16 unk100; s16 unk102; } kSC06_032_8019303C; struct { u8 pad0[0x2]; s16 unk102; } kSC06_033_80180A8C; struct { s16 unk100; s16 unk102; } kSC06_033_8018D05C; struct { u8 pad0[0x2]; s16 unk102; } kSC06_020_80181A94; struct { u8 pad0[0x2]; s16 unk102; } kSC06_022_801859B8; struct { s16 unk100; s16 unk102; } kSC06_024_80187E90; struct { s16 unk100; } kSC06_029_8018562C; struct { s16 unk100; s16 unk102; } kSC06_032_801826C8; struct { u8 pad0[0x6]; s16 unk106; u16 unk108; } kSC06_032_80186834; struct { s16 unk100; s16 unk102; } kSC06_033_801863AC; struct { u8 pad0[0x8]; u16 unk108; } kSC02_011_8018EC28; struct { s16 unk100; } kSC02_011_80190334; struct { s16 unk100; } kSC02_027_80181858; struct { s16 unk100; } kSC02_027_80181AE4; struct { s16 unk100; } kSC02_027_80182460; struct { u8 pad0[0x2]; s16 unk102; } kSC03_002_8018225C; struct { u8 pad0[0x8]; u16 unk108; } kSC03_006_80186D18; struct { s16 unk100; } kSC03_028_80184568; struct { u8 pad0[0x8]; u16 unk108; } kSC03_029_80185378; struct { union { s16 s; u16 u; } unk100; u16 unk102; } kSC03_030_801814F4; struct { s16 unk100; } kSC03_092_80181124; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; u8 pad6[0x2]; u16 unk108; } kSC03_111_801831D0; struct { u8 pad0[0x2]; s16 unk102; s16 unk104; u8 pad6[0x2]; u16 unk108; } kSC03_113_80181E68; struct { s16 unk100; } kSC03_118_8018545C; struct { s16 unk100; } kSC04_005_801840A8; struct { s16 unk100; s16 unk102; } kSC04_008_8017E628; struct { s16 unk100; u8 pad2[0x4]; s16 unk106; u16 unk108; } kSC05_006_8017F130; struct { s16 unk100; } kSC05_010_80180108; struct { s16 unk100; } kSC05_010_801813F4; struct { s16 unk100; } kSC06_000_80186688; struct { s16 unk100; } kSC06_029_80183A1C; struct { s16 unk100; } kSC06_032_8018D15C; struct { s16 unk100; } kSC06_032_8018D264; struct { s16 unk100; } kSC06_033_8018CD5C; struct { s16 unk100; } kcls_19b9a1afce73; struct { s16 unk100; s16 unk102; s16 unk104; s16 unk106; } kcls_c4a2d38bbd6f; struct { s16 unk100; } kcls_d47f0640740a; struct { s16 unk100; } kSC06_033_8018BCD4; struct { s16 unk100; } kSC06_032_80186CF0; struct { s16 unk100; } kSC03_092_80181CD4; struct { s16 unk100; } kSC03_093_80180864; struct { s16 unk100; } kSC03_095_8017EE2C; struct { s16 unk100; } kSC03_096_8017E230; struct { s16 unk100; } kSC03_097_8018358C; struct { s16 unk100; } kSC03_101_8017F328; struct { u8 pad0[0x8]; s16 unk108; } kSC02_005_8017C0F4; struct { u8 pad0[0x6]; s16 unk106; s16 unk108; } kSC02_011_8017CF54; struct { u16 unk100; } kSC03_030_80180458; struct { u8 pad0[0x2]; s16 unk102; } kSC03_105_80180100; struct { union { u16 u; s16 s; } unk100; } kSC03_118_80184940; } extD;
    /* 0x010a */ union { s16 s; u16 u; } unk10A;
} Unkstruct_801202A0; /* size = 0x10c */

/* Unkstruct_800B5BD8 — the sprite record (0x38, guess_g_RenderWork+0x65A8; render head +0x0..+0x10 shared with the 0x84 model record
   Unkstruct_8001C9D0; P3.45 T16.c1 model). */
typedef struct Unkstruct_800B5BD8 {
    /* T16.c5: sprite record; +0x0 pool tag 2, +0x2 render kind (src/800.c:8585-8735), +0x18 scale (src/800.c:8740) */
    /* 0x0000 */ RenderHead head; /* shared render head (sprite record, tag 2); T17.c38 */
    /* 0x0014 */ union {
        s16 s;
        u16 u;
    } unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ union { s16 s; u16 u; } unk18;
    /* 0x001a */ union { s16 s; u16 u; } unk1A;
    /* 0x001c */ union { s16 s; u16 u; } unk1C;
    /* 0x001e */ union {
        s16 s;
        u16 u;
    } unk1E;
    /* 0x0020 */ union { s32 s; u32 u; } unk20;
    /* 0x0024 */ union {
        u8 u;
        s8 s;
    } unk24;
    /* 0x0025 */ union {
        u8 u;
        s8 s;
    } unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ union {
        u8 u;
        s8 s;
    } unk27;
    /* 0x0028 */ union {
        s16 s;
        u16 u;
    } unk28;
    /* 0x002a */ union {
        s16 s;
        u16 u;
    } unk2A;
    /* 0x002c */ union {
        u16 u;
        s16 s;
    } unk2C;
    /* 0x002e */ union {
        u16 u;
        s16 s;
    } unk2E;
    /* 0x0030 */ union {
        s16 s;
        u16 u;
    } unk30;
    /* 0x0032 */ union {
        s16 s;
        u16 u;
    } unk32;
    /* 0x0034 */ union {
        s32 s;
        u32 u;
    } unk34;
} Unkstruct_800B5BD8; /* size = 0x38 */

/* Unkstruct_8011DB30 — the fx record (D_8011DB30 x 128, 0x38 each; free when +0x0 == 0: src/shared/ov/func_801291C0.h:5-17). */
typedef struct {
    /* T16.c5: fx record */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ union {
        u16 u;
        s16 s;
    } unk2;
    /* 0x0004 */ union {
        union { s32 s; u32 u; } val;
        struct { u16 lo; union { s16 s; u16 u; } hi; } i;
    } unk4;
    /* 0x0008 */ union {
        union { s32 s; u32 u; } val;
        struct { u16 lo; union { s16 s; u16 u; } hi; } i;
    } unk8;
    /* 0x000c */ union {
        union { s32 s; u32 u; } val;
        struct { u16 lo; union { s16 s; u16 u; } hi; } i;
    } unkC;
    /* 0x0010 */ union {
        union { s32 s; u32 u; } val;
        struct { u16 lo; u16 hi; } i;
    } unk10;
    /* 0x0014 */ union {
        union { s32 s; u32 u; } val;
        struct { u16 lo; u16 hi; } i;
    } unk14;
    /* 0x0018 */ union {
        union { s32 s; u32 u; } val;
        struct { u16 lo; u16 hi; } i;
    } unk18;
    /* 0x001c */ union {
        s32 s;
        u32 u;
    } unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ union {
        union { s32 s; u32 u; } val;
        struct { union { u16 u; s16 s; } lo; union { u16 u; s16 s; } hi; } i;
    } unk2C;
    /* 0x0030 */ union {
        union { s32 s; u32 u; } val;
        struct { u16 lo; union { s16 s; u16 u; } hi; } i;
    } unk30;
    /* 0x0034 */ union {
        union { s32 s; u32 u; } val;
        struct { union { u16 u; s16 s; } lo; u16 hi; } i;
    } unk34;
} Unkstruct_8011DB30; /* size = 0x38 */

/* Unkstruct_8011D030 — the small object (guess_g_SmallObjectPool 0x8011D030 x 30, 0x58 each; +0x0 kind -> D_80126728 handler,
   +0x20 pointer: src/shared/ov/func_80165CA0.h:14-23). */
typedef struct {
    /* T16.c5: small object */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ union {
        u16 u;
        s16 s;
    } unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ union {
        s16 s;
        u16 u;
    } unk6;
    /* 0x0008 */ union {
        s32 val;
        struct { u16 lo; union { s16 s; u16 u; } hi; } i;
    } unk8;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ union {
        s16 s;
        u16 u;
    } unkE;
    /* 0x0010 */ union {
        s32 val;
        struct { union { u16 u; s16 s; } lo; union { s16 s; u16 u; } hi; } i;
    } unk10;
    /* 0x0014 */ union {
        s32 val;
        struct { u16 lo; union { u16 u; s16 s; } hi; } i;
    } unk14;
    /* 0x0018 */ union {
        s32 val;
        struct { u16 lo; u16 hi; } i;
    } unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void *unk20; /* holds sprite records (C0626); was s16 *; T18.c13 */
    /* 0x0024 */ union {
        u8 b;
        s16 s;
    } unk24;
    /* 0x0026 */ union {
        u16 u;
        s16 s;
    } unk26;
    /* 0x0028 */ union {
        u16 u;
        u8 b;
        s16 s;
    } unk28;
    /* 0x002a */ union {
        u16 u;
        s16 s;
    } unk2A;
    /* 0x002c */ union {
        union { s32 s; u32 u; } val;
        struct { union { s16 s; u16 u; } lo; u16 hi; } i;
    } unk2C;
    /* 0x0030 */ union {
        union { s32 s; u32 u; } val;
        struct { u16 lo; u16 hi; } i;
    } unk30;
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u8 pad38[0x20];
} Unkstruct_8011D030; /* size = 0x58 */

/* Unkstruct_80078E78 — the player record at 0x80078E78 (guess_g_PlayerRecord; 0x98 bytes; was Blk98_80029274 in src/800.c, Blk80078E78 in
   src/resident/resident_jr_800D00E4.c, u8 guess_g_PlayerRecord[] in 880 TUs). Hand-written (P38 T3): field widths are the type the
   USING TUs declare for each scalar global (.run/P38/T3/player_use_widths.py); names only where docs/memory-map.md 3.4
   or docs/actor-struct.md mark the row verified. Decisions: docs/struct-map-decisions.md. */
typedef struct {
    /* 0x0000 */ s32 unk0;          /* guess_g_PlayerRecord word 0 */
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
    /* 0x0037 */ u8 unk37;          /* guess_g_DayPeriod; not dayOfWeek (refuted, memory-map 3.4) */
    /* 0x0038 */ u8 unk38;          /* guess_g_ClockMinute low byte; s16 guess_g_ClockMinute (524 uses) spans +0x38..+0x39: union candidate */
    /* 0x0039 */ u8 hour;           /* D_80078EB1; verified live, memory-map 3.4 */
    /* 0x003a */ u16 hp_max;        /* g_PlayerHpMax; verified live */
    /* 0x003c */ s16 hp_current;    /* g_PlayerHp; verified live; s16 by 689 vs 135 uses */
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

/* T17.c24b: MATRIX moved ahead of its aliases (byte-neutral) */
typedef struct { short m[3][3]; long t[3]; } MATRIX;
/* --- lift_types.py --census (P38 T5.1.c2, batch ov-file) --- */
/* T17.c24b: survivor word view: md_MAIN_013 func_800CB2D8-family 8-word copies, SC03_030 func_8017E7D4, md_MAIN_003 D_800D942C */
typedef struct {
    /* 0x0000 */ s32 w[8];
} Blk20_8016DF5C; /* size = 0x20 */
typedef MATRIX Blk20;
typedef struct {
    /* 0x0000 */ union {
        struct { s32 w[4]; } v0;
        struct { u32 unk0; u32 unk4; u32 unk8; u32 unkC; } v1;
    } unk0;
} Blk16_8018A8B8; /* size = 0x10 */
typedef Blk16_8018A8B8 Blk16;
typedef struct { u32 addr : 24; u32 len : 8; u8 r0, g0, b0, code; } P_TAG;
typedef MATRIX Blk32;
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
typedef struct {
    /* 0x0000 */ s32 f0;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x8];
    /* 0x0018 */ s32 unk18;
} E_3B7AC_8013B7AC; /* size = 0x1c */
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
typedef struct { char s[10]; } S10_80136C90;
typedef SVECTOR Blk8; /* T17.c18: SVECTOR folded into SVECTOR */
typedef SVECTOR SVec_8016AB6C;
typedef struct {
    /* Unkstruct_2744caa4: P3.40 T3 band rank 6335; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ void *unkC;
    /* 0x0010 */ u8 pad10[0x50];
    /* 0x0060 */ s32 unk60;
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ s32 unk68;
} Unkstruct_8017FA5C; /* size = 0x6c */
typedef Unkstruct_8017FA5C S_8013BC7C;
typedef struct { s16 x, y, z; } Vec3s;
typedef struct { char b[4]; } W_8016BFD0;
typedef W_8016BFD0 W;
typedef void (*code)(unsigned short *);
typedef struct { long vx, vy, vz; unsigned char r, g, b; } GsF_LIGHT; /* PsyQ libgs.h */
struct S80190C84 {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
    s32 f10;
};
typedef struct {
    /* Unkstruct_4b28b7fb: P3.40 T3 band rank 5095; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
} Unkstruct_80180CD4; /* size = 0x8 */
typedef struct {
        u8    pad0[8];
        void *f8;
        void *fC;
    } E_13BD74;
typedef Unkstruct_8017FA5C E_13C08C;
typedef E_3B7AC_8013B7AC Ent_8013B6A0;
typedef struct {
    /* 0x0000 */ union {
        struct { s32 a; } v0;
        struct { u32 *unk0; } v1;
    } unk0;
    /* 0x0004 */ s32 b[4];
} OtBlk_80180894; /* size = 0x14 */
typedef OtBlk_80180894 Env_800D29F8;
typedef struct {
        u8  pad0[3];
        u8  code;
        s32 f4;
        s32 f8;
    } P_13BD74;
typedef E_3B7AC_8013B7AC Spr_8013B598;
typedef struct { u16 f0; u16 f2; u16 f4; } Src_8013B598_8013B598;
typedef Src_8013B598_8013B598 Src_8013B598;
typedef Src_8013B598_8013B598 Src_8013B6A0;
typedef struct { s16 vx, vy; } DVECTOR;
typedef DVECTOR DVEC2_C974_8017BA3C;
typedef MATRIX MTX_C974;
typedef struct {
    /* Unkstruct_e505dcd3: P37 struct map 868 sites in 124 bodies; evidence {'PV': 1, 'P': 1, 'L': 1}; type_folds.tsv evidence single-fn; P3.40 T2 */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_801343C4; /* size = 0x8 */
typedef Unkstruct_801343C4 Pt_8017D87C;
typedef SVECTOR SV;
typedef SVECTOR SVEC2_C974_8017BA3C;
typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 cd;
} CVECTOR;
typedef CVECTOR Blk4;
typedef CVECTOR Blk4_md_SC07_003;
typedef SVECTOR SVECTOR_800;

/* --- lift_types.py --census (P38 T5.1.c2, batch ov-block) --- */
typedef SVECTOR Blk8_md_SC03_076;
typedef struct {
    unsigned int addr : 24;
    unsigned int len : 8;
} PrimTag;
typedef PrimTag PTag;
typedef Blk16_8018A8B8 St801D9204;
typedef E4 Unkstruct_801151D0;
typedef struct {
    /* 0x0000 */ s32 a;
    /* 0x0004 */ s32 b;
    /* 0x0008 */ s32 c;
    /* 0x000c */ s32 d;
} Blk16_956C; /* size = 0x10 */
typedef Blk16_956C V32;

/* --- lift_types.py --census (P38 T5.1.c2, batch md) --- */
struct packed_word { int w; } __attribute__((packed, aligned(1)));
typedef struct packed_word Align1W_801AD068;
typedef Blk152 Blk152_8017DF40_801E48B8;
typedef Blk152 Blk152_8017DF40_801E9DF8;
typedef Blk152 Blk152_8017DF40_801EFC58;
typedef Blk152 Blk152_8017DF40_801F1738;
typedef MATRIX Blk20_800CB68C;
typedef MATRIX Blk32_CB1EC;
typedef struct {
    char c[3];
} Blk3_801E40A8;
typedef Blk3_801E40A8 Blk3_801F0F28;
typedef CVECTOR Blk4_8017DF40_801E48B8;
typedef CVECTOR Blk4_8017DF40_801E9DF8;
typedef CVECTOR Blk4_8017DF40_801EFC58;
typedef CVECTOR Blk4_8017DF40_801F1738;
typedef W_8016BFD0 Blk4_801A7358;
typedef W_8016BFD0 Blk4_801AB8C0;
typedef W_8016BFD0 Blk4_801AD31C;
typedef W_8016BFD0 Blk4_md_SC07_004_801A8228;
typedef struct {
    u32 field0;
    u32 field1;
} __attribute__((packed, aligned(1))) BlockData;
typedef BlockData Blk8_md_MAIN_027;
typedef SVECTOR Blk8_80133CD4; /* T17.c24b fold */
typedef CVECTOR Col4_8017F8BC;
typedef Col4_8017F8BC CVEC;
typedef Col4_8017F8BC CVecX;
typedef Unkstruct_801343C4 D24D0_Rect;
typedef OtBlk_80180894 Env_801E46A0;
typedef OtBlk_80180894 Env_801E9BE0;
typedef OtBlk_80180894 Env_801EFA40;
typedef OtBlk_80180894 Env_801F1520;
typedef struct { u32 tag; u32 rgb; u32 xy0, xy1, xy2; } F3_27058_t;
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
    /* 0x00 */ u32 pad;
    /* 0x04 */ u32 rgb;
    /* 0x08 */ u16 n;
    /* 0x0A */ u16 v0;
    /* 0x0C */ u16 v1;
    /* 0x0E */ u16 v2;
} Src_249F0_t;
typedef Src_249F0_t Face10_800CB1F8;
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
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 uv0;
    /* 0x0008 */ u32 uv1;
    /* 0x000c */ u32 uv2;
    /* 0x0010 */ u32 uv3;
    /* 0x0014 */ u16 n0;
    /* 0x0016 */ u16 v0;
    /* 0x0018 */ u16 v1;
    /* 0x001a */ u16 v2;
    /* 0x001c */ u16 v3;
    /* 0x001e */ u8 pad1E[0x2];
} Prim20; /* size = 0x20 */
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
typedef MATRIX Mtx32_801A2400;
typedef MATRIX Mtx32_801A3180;
typedef MATRIX Mtx32_801A3B18;
typedef MATRIX Mtx32_801A3D60;
typedef MATRIX Mtx32_801A4D58;
typedef MATRIX Mtx32_801A4DFC;
typedef MATRIX Mtx32_801A52DC;
typedef MATRIX Mtx32_801A54F0;
typedef MATRIX Mtx32_801A5698;
typedef MATRIX Mtx32_801A90D8;
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
    /* Unkstruct_c86ca6e3: P3.40 T3 band rank 666; 26 TNC sites in 13 bodies; struct map 26 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_80181FAC_2; /* size = 0x4 */
typedef struct { u32 tag; u32 rgb; u32 xy0, xy1, xy2, xy3; } F4_27200_t;
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
    /* Unkstruct_08efdfe5: P3.40 T3 band rank 269; 92 TNC sites in 19 bodies; struct map 92 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ union {
        struct { s32 unk4; } v0;
        struct { void *unk0; } v1;
    } unk4;
    /* 0x0008 */ union {
        struct { s32 unk8; } v0;
        struct { void *unk0; } v1;
    } unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ union {
        struct { s32 unk14; } v0;
        struct { void *unk0; } v1;
    } unk14;
    /* 0x0018 */ Unkstruct_80181FAC_2 *unk18;
    /* 0x001c */ union {
        struct { s32 unk1C; } v0;
        struct { void *unk0; } v1;
    } unk1C;
} Unkstruct_8017C120; /* size = 0x20 */
typedef Unkstruct_8017C120 Panel_801EFA40;
typedef Unkstruct_80181FAC_2 Prim4_801F1520;
typedef Unkstruct_8017C120 Panel_801F1520;
typedef CVECTOR Quad4_800CCAD0;
typedef struct {
    /* 0x0 */ s16 a;
    /* 0x2 */ s16 b;
    /* 0x4 */ s32 c;
} Rec8_801A026C;
typedef struct {
    /* 0x0000 */ u16 h[6];
} Rec_80166690_80166690; /* size = 0xc */
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
typedef struct { s32 vx, vy, vz; } VECTOR;
typedef struct { u16 h; } H16;
typedef H16 S16_800CF3E8;
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
typedef Unkstruct_801202A0 S34_801A1470;
typedef E4 S70;
typedef struct { s32 pad00[8]; u16 f20; } SH20;
typedef struct { u8 pad00[0x1A]; u16 f1A; } SP18;
typedef SVECTOR SV3_801A4570;
typedef Unkstruct_801343C4 SV4R_801AAA6C;
typedef VECTOR SV4_md_SC03_135_801E585C;
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
typedef struct {
    /* 0x0000 */ union {
        struct { SVEC_md_MAIN_047_800CCBC0 v0; SVEC_md_MAIN_047_800CCBC0 v1; SVEC_md_MAIN_047_800CCBC0 v2; SVEC_md_MAIN_047_800CCBC0 v3; } v0;
        struct { SVEC_md_MAIN_047_800CCBC0 unk0[4]; } v1;
        struct { s16 unk0[16]; } v2;
    } unk0;
    /* 0x0020 */ union {
        struct { CVEC c0; CVEC c1; CVEC c2; CVEC c3; } v0;
        struct { CVEC unk0[4]; } v1;
        struct { u8 unk0[16]; } v2;
    } unk20;
    /* 0x0030 */ s32 tag;
} Prim_md_MAIN_047_800CCBC0; /* size = 0x34 */
typedef SVECTOR SV_800CB4E4;
typedef SVECTOR SV_800CB910;
typedef struct {
    /* 0x0000 */ union {
        struct { char _b[8]; } v0;
        struct { u16 unk0; u16 unk2; u16 unk4; u16 unk6; } v1;
    } unk0;
} M8_801312D0; /* size = 0x8 */
typedef M8_801312D0 SV_801A1B28;
typedef SVECTOR SV_801A54F0;
typedef M8_801312D0 SV_801A8990;
typedef SVECTOR SV_801A90D8;
typedef Vec3s SV_801AA210;
typedef SVECTOR SV_801AA7E4;
typedef SVECTOR SV_801AACD4;
typedef SVECTOR SV_801AAF8C;
typedef SVECTOR SV_801ADC40;
typedef SVECTOR SVec16_801A8B64;
typedef SVECTOR SVec801A38E4;
typedef SVECTOR SVec801A5674;
typedef struct { SVec801A5674 v[2]; s32 col[2]; s32 tag; s32 pad; } Prim801A5674;
typedef SVECTOR ElemK; /* T17.c24b fold */
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
typedef SVECTOR SXY_801A8B64;
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
typedef struct { u8 pad[0x50]; s32 f50; } Struct80078E78_md_MAIN_028_800CB0D8;
typedef Vec3s Struct801AD7EC_Local;
typedef Vec3s Svec3;
typedef SVECTOR Svec_801A6184;
typedef SVECTOR Svec_801A8494;
typedef SVECTOR Svec_801AEC38;
typedef SVECTOR Svec_A8CE0;
typedef struct { u8 flag, idx, cnt, tim; Rec_80166690_80166690 e[16]; } Trail_md_MAIN_047_800CCBC0;
typedef Trail_md_MAIN_047_800CCBC0 Trail_md_MAIN_047_800CCDE8;
typedef struct {
    u16 a, b;
} U16x2;
typedef BlockData U8x;
struct UnkS1 { s32 pad0; s32 f4; s32 pad8; s32 fC; s32 pad10; s32 pad14; s32 f18; u32 f1C; };
typedef H16 Unkstruct_801AF368;
typedef struct { u32 w; }                      W_S40_8018B238_80187EA0;
typedef struct { s16 h; } Unkstruct_8017D2A4;
typedef Unkstruct_8017D2A4 Unkstruct_801E3C1C;
typedef struct { u8 pad[2]; u16 f; } Unkstruct_801E5894;
typedef Unkstruct_8017D2A4 Unkstruct_801E915C;
typedef Unkstruct_8017D2A4 Unkstruct_801EEFBC;
typedef Unkstruct_8017D2A4 Unkstruct_801F0A9C;
typedef Blk16_956C V32_800CB910;
typedef VECTOR V3_800CB634;
typedef Unkstruct_801343C4 V8_md_MAIN_044;
typedef M8_801312D0 V8_md_SC07_003;
typedef VECTOR VEC32_801ADC40;
typedef Blk16_956C VEC_801A1B28;
typedef SVECTOR Vec16_801A4FDC;
typedef SVECTOR Vec16_801A5094;
typedef Blk16_956C Vec32_801A2400;
typedef Blk16_956C Vec32_801A3180;
typedef Blk16_956C Vec32_801A4FDC;
typedef Blk16_956C Vec32_801A5094;
typedef VECTOR Vec32_801AA004;
typedef Blk16_956C Vec801A143C;
typedef SVECTOR W8_md_MAIN_025_800CB300;

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
typedef Blk16_8018A8B8 B16x;
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
struct Entry_8016E95C {
    /* 0x0000 */ u8 f0;
    /* 0x0001 */ u8 f1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ union { s16 s; u16 u; } unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x18];
}; /* size = 0x20 */
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
    u8 pad00[0x36];
    u8 field_0x36;
    u8 field_0x37;
} Blk80078E78;
typedef struct {
    /* 0x0000 */ union {
        struct { s32 w[9]; } v0;
        struct { u8 pad0[0x3]; u8 unk3; u8 pad4[0x4]; s32 unk8; s32 unkC; u16 unk10; u16 unk12; u16 unk14; u16 unk16; void (*unk18)(void); u8 pad1C[0x4]; void (*unk20)(void); } v1;
    } unk0;
} Blob36; /* size = 0x24 */
typedef Unkstruct_801343C4 COL_8001EFE0;
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
typedef Unkstruct_80181FAC_2 DV_EA14;
typedef Unkstruct_80181FAC_2 DVec_80021D38;
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
typedef struct {
    /* 0x00 */ u32 addr : 24;
    /* 0x03 */ u32 len : 8;
    /* 0x04 */ union {
        u32 code0;
        struct { u8 r0, g0, b0, code; } v1;
    } unk4;
    /* 0x08 */ s16 x0, y0;
    /* 0x0C */ u8 r1, g1, b1, pad1;
    /* 0x10 */ s16 x1, y1;
    /* 0x14 */ u8 r2, g2, b2, pad2;
    /* 0x18 */ s16 x2, y2;
    /* 0x1C */ u8 r3, g3, b3, pad3;
    /* 0x20 */ s16 x3, y3;
} DrMode_80021284; /* size = 0x24 */
typedef struct { u32 addr : 24; u32 len : 8; u32 code; } DrTpage;
typedef struct {
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 w8;
    /* 0x000c */ u8 padC[0x9];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 b16;
    /* 0x0017 */ u8 pad17[0x2];
    /* 0x0019 */ u8 b19;
    /* 0x001a */ u8 pad1A[0xe];
    /* 0x0028 */ s32 unk28;
} Dst; /* size = 0x2c */
typedef struct {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ u32 attr;
    /* 0x08 */ u8  pad08[0x18];
    /* 0x20 */ u8 *rec;
    /* 0x24 */ u8  pad24[8];
    /* 0x2C */ u16 pri;
} Ent_80021284;
typedef struct { u8 pad[4]; PTag *ot; } Env;
typedef OtBlk_80180894 Env_800D2650;
typedef OtBlk_80180894 Env_800D27DC;
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
typedef struct {                                     /* 0x24 */
    u32 tag;     /* 0x00 */
    u32 rgb0;    /* 0x04 */
    union { s16 s; u16 u; } x0, y0; /* u: PG4_80189340 (ov_SC02_000) reads */  /* 0x08 */
    u32 rgb1;    /* 0x0C */
    union { s16 s; u16 u; } x1, y1; /* u: PG4_80189340 (ov_SC02_000) reads */  /* 0x10 */
    u32 rgb2;    /* 0x14 */
    union { s16 s; u16 u; } x2, y2; /* u: PG4_80189340 (ov_SC02_000) reads */  /* 0x18 */
    u32 rgb3;    /* 0x1C */
    union { s16 s; u16 u; } x3, y3; /* u: PG4_80189340 (ov_SC02_000) reads */  /* 0x20 */
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
    /* 0x0000 */ u32 w[8];
} Blk32_801898F4; /* size = 0x20 */
typedef Ft4_800CBA18 LineG4_80016C28;
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
typedef struct Ent30D80 {
    /* 0x0000 */ s32 unk00;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unk0A;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x4];
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ u8 pad34[0x3];
    /* 0x0037 */ u8 unk37;
    /* 0x0038 */ u8 unk38;
    /* 0x0039 */ u8 pad39[0x1];
    /* 0x003a */ s16 unk3A;
    /* 0x003c */ s16 unk3C;
    /* 0x003e */ u8 pad3E[0x2];
    /* 0x0040 */ union {
        struct { void (*unk40)(s32, s32); } v0;
        struct { s32 unk0; } v1;
        struct { u32 unk0; } v2;
    } unk40;
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s16 unk48;
    /* 0x004a */ u16 unk4A;
    /* 0x004c */ u8 pad4C[0x2];
    /* 0x004e */ u8 unk4E;
    /* 0x004f */ u8 pad4F[0x1];
    /* 0x0050 */ u8 unk50;
    /* 0x0051 */ u8 unk51;
    /* 0x0052 */ u8 pad52[0x2];
} Ent30D80; /* size = 0x54 */
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
typedef Unkstruct_80181FAC_2 Poly12Pt;
typedef struct {
    u8 pad_00[0x10];
    Poly12Pt pts[12];
} Poly12Obj;
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
typedef Src_8013B598_8013B598 Pos800D20C0;
typedef CVECTOR RGBC;
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
    /* Unkstruct_2bb2ade7: P3.40 T3 band rank 2804; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ union {
        u16 u;
        s16 s;
    } unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ u32 *unkC;
    /* 0x0010 */ u8 *unk10;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 unk16;
    /* 0x0017 */ u8 unk17;
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ union {
        struct { Ramp388C unk0[3]; } v0;
        struct { u16 unk0[12]; } v1;
    } unk1C;
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 unk36;
    /* 0x0037 */ u8 pad37[0x1];
    /* 0x0038 */ u8 unk38;
    /* 0x0039 */ u8 unk39;
    /* 0x003a */ u8 unk3A[8];
    /* 0x0042 */ u8 pad42[0x2];
    /* 0x0044 */ u32 *unk44;
    /* 0x0048 */ u8 unk48;
    /* 0x0049 */ u8 pad49[0x1];
    /* 0x004a */ u16 unk4A;
    /* 0x004c */ u8 unk4C;
    /* 0x004d */ u8 unk4D;
    /* 0x004e */ u8 unk4E;
    /* 0x004f */ u8 unk4F;
    /* 0x0050 */ u16 unk50;
    /* 0x0052 */ s16 unk52;
} Unkstruct_80031BE0; /* size = 0x54 */
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
typedef F1ccRec S54;
typedef struct {
    u8 pad[0x14];
    u8 f14;   /* 0x14 */
    u8 f15;   /* 0x15 */
} S800D1938;
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
typedef M8_801312D0 SV_80021284;
typedef M8_801312D0 SV_EA14;
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
typedef struct {
    /* Unkstruct_9e228c39: P3.40 T3 band rank 51; 492 TNC sites in 123 bodies; struct map 492 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 unk6;
    /* 0x0007 */ u8 pad7[0x1];
} Unkstruct_801312D0; /* size = 0x8 */
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
    /* 0x1C */ Unkstruct_801312D0 unk1C[3];
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
    /* 0x0000 */ SV_80016C28 v[4];
    /* 0x0020 */ u32 rgb0;
    /* 0x0024 */ u32 rgb1;
    /* 0x0028 */ u32 rgb2;
    /* 0x002c */ u32 rgb3;
    /* 0x0030 */ u32 flags;
} Src_80016C28; /* size = 0x34 */
typedef struct {
    /* Unkstruct_e5142881: P3.40 T3 band rank 6123; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ SVec_80017168 unk0[3];
    /* 0x0018 */ u32 unk18;
    /* 0x001c */ union {
        s32 s;
        u32 u;
    } unk1C;
} Unkstruct_80175AB8_2; /* size = 0x20 */
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
    /* 0x0000 */ union {
        struct { SV_80017930 v[4]; } v0;
        struct { u16 unk0; u16 unk2; u8 pad4[0x4]; u16 unk8; u16 unkA; u8 padC[0x4]; u16 unk10; u16 unk12; u8 pad14[0x4]; u16 unk18; u16 unk1A; } v1;
    } unk0;
    /* 0x0020 */ u32 uv[4];
    /* 0x0030 */ u32 rgb[4];
    /* 0x0040 */ u32 flags;
    /* 0x0044 */ u8 clut;
    /* 0x0045 */ u8 pad45[0x3];
} Src_80017930; /* size = 0x48 */
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
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 rgb0;
    /* 0x0008 */ u32 rgb1;
    /* 0x000c */ u32 rgb2;
    /* 0x0010 */ u16 n0;
    /* 0x0012 */ u16 v0;
    /* 0x0014 */ u16 v1;
    /* 0x0016 */ u16 v2;
} TmdG3; /* size = 0x18 */
typedef union {
    u32 w;
    u16 h[2];
} UV16D78;
typedef UV16D78 UV16F18;
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
typedef Blk16_956C VC221A8;
typedef Blk16_956C VC_EA14;
typedef Blk16_956C VEC_8001EFE0;
typedef Blk16_956C VEC_80021284;
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
    /* 0x0000 */ s32 unk00;
    /* 0x0004 */ s32 unk04;
    /* 0x0008 */ s16 unk08;
    /* 0x000a */ s16 unk0A;
    /* 0x000c */ u8 padC[0x34];
    /* 0x0040 */ s32 unk40;
    /* 0x0044 */ u8 unk44;
    /* 0x0045 */ u8 pad45[0x3];
} Voice336A8; /* size = 0x48 */
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
typedef SVECTOR Vtx8;
typedef struct { u8 v; } W8_;
typedef Unkstruct_801343C4 XRECT;
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
typedef Unkstruct_80181FAC_2 XY221A8;
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
typedef Unkstruct_80181FAC_2 XY_8001EFE0;
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
typedef struct {
    /* 0x0000 */ u8 b[12];
} Blk12_801854C4; /* size = 0xc */
typedef struct {               /* 0x18 stride; D_800A463C + k*0x18 */
    s32 unk00;
    u8  unk04[0x14];
} Ent24;
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
typedef struct {                 /* guess_g_PlayerActor */
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

/* provenance (head_types-hand): T2 (P3.40) canonical definitions, one per `define` target of config/type_folds.tsv, flat max-site layout renamed to the target, by tools/head_types.py --type <map type> --map .run/P37/census/struct_map.json --header .run/P40/t2/per/<map type>.h, one run per type, hand-copied at 504802c32e (P3.40 T2.c2); order: by name; generator retired P3.45 T6; hand-edited since */
typedef struct {
    /* Unkstruct_8011F7A8: P37 struct map 1742 sites in 270 bodies; evidence {'L': 18, 'AT': 1}; type_folds.tsv evidence E2-anchor; P3.40 T2 */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 pad2[0x5];
    /* 0x0007 */ u8 unk7;
    /* 0x0008 */ u8 unk8;
    /* 0x0009 */ u8 pad9[0x3];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x30];
    /* 0x0048 */ Unkstruct_80078E78 unk48; /* T18.c16: 0x98 copy of guess_g_PlayerRecord (func_80175308.h:28; judge c6b); was u16 unk82 = its hp_max */
    /* 0x00e0 */ u8 padE0[0x14]; /* T18.c16: +0xE0 sub-block (was view Unkstruct_8011F888, judge c7), fields below */
    /* 0x00f4 */ s32 unkF4;
    /* 0x00f8 */ u8 padF8[0x2];
    /* 0x00fa */ s16 unkFA;
    /* 0x00fc */ u8 padFC[0x12];
    /* 0x010e */ s16 unk10E;
    /* 0x0110 */ u8 pad110[0x4];
    /* 0x0114 */ u16 unk114;
    /* 0x0116 */ u8 pad116[0x6];
    /* 0x011c */ u16 unk11C;
    /* 0x011e */ u8 pad11E[0x2];
    /* 0x0120 */ u16 unk120;
    /* 0x0122 */ u8 pad122[0x5];
    /* 0x0127 */ u8 unk127;
    /* 0x0128 */ u8 unk128;
    /* 0x0129 */ u8 pad129[0x1];
    /* 0x012a */ u8 unk12A;
    /* 0x012b */ u8 pad12B[0x1];
} Unkstruct_8011F7A8; /* size = 0x12c */


typedef struct {
    /* Unkstruct_80126948: P37 struct map 3034 sites in 848 bodies; evidence {'PV': 3, 'PTR': 6, 'L': 115, 'P': 3, 'AT': 2}; type_folds.tsv evidence flow-cluster; P3.40 T2 */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 unk4;
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ union {
        s32 val;
        struct { s16 lo; u16 hi; } i;
    } unkC;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ union {
        s16 s;
        u16 u;
    } unk18;
    /* 0x001a */ union {
        u16 u;
        s16 s;
    } unk1A;
    /* 0x001c */ union {
        u16 u;
        s16 s;
    } unk1C;
    /* 0x001e */ u8 pad1E[0x2];
    /* 0x0020 */ union {
        s16 s;
        u16 u;
    } unk20;
    /* 0x0022 */ union {
        u16 u;
        s16 s;
    } unk22;
    /* 0x0024 */ union {
        s16 s;
        u16 u;
    } unk24;
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
    /* 0x0054 */ s32 unk54;
    /* 0x0058 */ u8 pad58[0x4];
    /* 0x005c */ s32 unk5C;
    /* 0x0060 */ s32 unk60;
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ s32 unk68;
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ s32 unk70;
    /* 0x0074 */ u8 pad74[0x28];
    /* 0x009c */ s32 unk9C;
    /* 0x00a0 */ union {
        s16 s;
        u16 u;
    } unkA0;
    /* 0x00a2 */ union {
        s16 s;
        u16 u;
    } unkA2;
} Unkstruct_80126948; /* size = 0xa4 */

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

struct S8013A0A4 {
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 field_4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s32 field_8;
    /* 0x000c */ u8 unkC;
    /* 0x000d */ u8 padD[0x1];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x6];
    /* 0x0016 */ u16 field_16;
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 field_1E;
    /* 0x001f */ u8 pad1F[0x1];
    /* 0x0020 */ u8 unk20;
    /* 0x0021 */ u8 pad21[0x1];
    /* 0x0022 */ u8 unk22;
    /* 0x0023 */ u8 pad23[0x5];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 field_2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ union {
        s16 s;
        u16 u;
    } unk34;
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0x14];
}; /* size = 0x4c; T18.c16: text box record, guess_g_TextBoxes stride 0x4C (was 0x38) */

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
    /* static waypoint table (T17.c27, c25 notpool): count, then {x, z} points; read by func_80183480 (src/ov_SC03_002/ov_SC03_002_jr_80181D78.c:3932-3955), data ov_SC03_002 801BDC00 = {0xD, (-0x480,0x800), ...}; variable length, sized to the cited table (count 0xD) */
    /* 0x0000 */ s16 count;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s16 pt[0xD][2];
} Unkstruct_80183480; /* size = 0x38 */


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

/* provenance (restruct-band): T3 (P3.40) band defs by tools/restruct.py --decide-band --write, ordered by band rank, last ran at 3cf41bbd60 (P3.40 T3.c3, --ranks 1835-6676); generator retired P3.45 T6; hand-edited since */


typedef struct {
    /* 0x0000 */ u16 f0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ u8 pad30[0x1c];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ int f50;
    /* 0x0054 */ u8 pad54[0x4];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u8 pad5C[0x4];
    /* 0x0060 */ union {
        u16 u;
        s16 s;
    } unk60;
    /* 0x0062 */ union {
        u16 u;
        s16 s;
    } unk62;
    /* 0x0064 */ u8 pad64[0x2];
    /* 0x0066 */ union {
        u16 u;
        s16 s;
    } unk66;
} Ent_80164930_80164930; /* size = 0x68 */

typedef struct {
    /* Unkstruct_fc43506c: P3.40 T3 band rank 41; 504 TNC sites in 126 bodies; struct map 504 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8017BB34; /* size = 0x10 */

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

typedef Unkstruct_80126B58 Unkstruct_80172CA0; /* size = 0x218 */

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
    /* Unkstruct_39de3511: P3.40 T3 band rank 73; 372 TNC sites in 124 bodies; struct map 372 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8015E4B0; /* size = 0x14 */

typedef Unkstruct_801202A0 Unkstruct_80132144; /* size = 0x60 */

typedef struct {
    /* Unkstruct_75e9a6af: P3.40 T3 band rank 80; 369 TNC sites in 123 bodies; struct map 369 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_8016E7C8; /* size = 0x10 */

typedef struct { s16 x, y; } Pair_8013AD38;

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
    /* Unkstruct_800AF630: P3.40 T3 band rank 90; 269 TNC sites in 135 bodies; struct map 671 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 pad1[0xa3d1];
    /* 0xa3d2 */ u16 unkA3D2;
    /* 0xa3d4 */ u8 padA3D4[0x6];
    /* 0xa3da */ s16 unkA3DA;
} Unkstruct_8012956C; /* size = 0xa3dc */

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

typedef Unkstruct_80126B58 Unkstruct_8015F448_2; /* size = 0x24c */

typedef Unkstruct_80126B58 Unkstruct_80175184_2;
typedef Unkstruct_80175184_2 Unkstruct_80175184; /* size = 0x48 */

typedef struct {
    /* Unkstruct_8e3ffd0a: P3.40 T3 band rank 119; 248 TNC sites in 124 bodies; struct map 248 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_8015D380; /* size = 0x14 */

typedef Unkstruct_801202A0 Unkstruct_8012C890_3; /* size = 0x100 */

typedef Unkstruct_80126B58 Unkstruct_8016F6E0_2; /* size = 0x218 */

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

typedef Unkstruct_80135EB0 Unkstruct_80135EB0_2; /* size = 0x10 */

typedef Pair_8013AD38 Unkstruct_8013AD38_2; /* size = 0x4 */

typedef Dst Unkstruct_8017CB30; /* size = 0x2c */

typedef Dst Unkstruct_8017CC48; /* size = 0x2c */

typedef Unkstruct_80167DBC Unkstruct_80167DBC_2; /* size = 0x54 */

typedef struct {
    /* Unkstruct_be9e26b6: P3.40 T3 band rank 2264; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801833D4; /* size = 0x24 */

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

typedef Unkstruct_801397B0 Unkstruct_801397B0_5; /* size = 0x24 */

typedef Unkstruct_80126B58 Unkstruct_8015BE38; /* size = 0x4 */

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

typedef Unkstruct_80126B58 Unkstruct_8015D4E8; /* size = 0x4 */

typedef struct {
    /* T18.c16: raw byte arrays unk00/unk18/unk20 (never accessed) made pads so the 80182080/8017DA08 views fold in */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ union {
        u16 u;
        s16 s;
    } unkE;
    /* 0x0010 */ union {
        u16 u;
        s16 s;
    } unk10;
    /* 0x0012 */ union {
        u16 u;
        s16 s;
    } unk12;
    /* 0x0014 */ union {
        u16 u;
        s16 s;
    } unk14;
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Ent_8017D6EC; /* size = 0x24 */

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
    /* Unkstruct_c0f4146d: P3.40 T3 band rank 232; 124 TNC sites in 124 bodies; struct map 124 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 pad2[0x6];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ MATRIX unkC; /* T18.c16: judge c7, func_80162968.h:20 */
    /* 0x002c */ u8 pad2C[0x2c];
} Unkstruct_80162870; /* size = 0x58; was 0xc. T18.c16: resident D_8011F750 control block, ZeroMemory 0x58 (func_801627C0.h:6) */

typedef Unkstruct_8013B274 Unkstruct_8013B274_3; /* size = 0x20 */

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

typedef Dst Unkstruct_8017CA8C; /* size = 0x18 */

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

typedef Unkstruct_8011D030 Unkstruct_8016C998_2; /* size = 0x38 */

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

typedef Unkstruct_8011D030 Unkstruct_8016C188_3; /* size = 0x38 */

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

typedef Unkstruct_80126B58 Unkstruct_80172CA0_2; /* size = 0x218 */

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

typedef Unkstruct_8001C9D0 Unkstruct_80164930_2; /* size = 0x20 */

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

typedef Dst Unkstruct_80159698_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_a0778849: P3.40 T3 band rank 279; 87 TNC sites in 29 bodies; struct map 87 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
} Unkstruct_8017E0C4_2; /* size = 0xc */

typedef Unkstruct_801202A0 Unkstruct_801320D8_2; /* size = 0x60 */

typedef struct {
    /* Unkstruct_14d50973: P3.40 T3 band rank 2765; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80183D90_2; /* size = 0x1c */

typedef Unkstruct_80134C20 Unkstruct_80134C20_2; /* size = 0x18 */

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

typedef Unkstruct_8011D030 Unkstruct_8016CF04_2; /* size = 0x2c */

typedef Unkstruct_8012C890_2 Unkstruct_8012C890_4; /* size = 0x14 */

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

typedef Unkstruct_80126B58 Unkstruct_800CAE34; /* size = 0x198 */

typedef Unkstruct_801407F4 Unkstruct_801407F4_2; /* size = 0x20 */

typedef Unkstruct_8011D030 Unkstruct_801681FC_2; /* size = 0x34 */

typedef Unkstruct_80126948 Unkstruct_80174BF4_2; /* size = 0x58 */

typedef struct S8013A0A4 Unkstruct_801397B0_6; /* size = 0x38 */


typedef struct {
    /* Unkstruct_3e7d704c: P3.40 T3 band rank 322; 68 TNC sites in 17 bodies; struct map 68 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2a];
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ s32 unk30;
} Unkstruct_8017CE14; /* size = 0x34 */

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

typedef Unkstruct_8001C9D0 Unkstruct_80135480_4; /* size = 0x54 */

typedef Unkstruct_8001C9D0 Unkstruct_80135480_5; /* size = 0x54 */

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

typedef Unkstruct_8011DB30 Unkstruct_80143458_3; /* size = 0x38 */

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

typedef Dst Unkstruct_8017CEBC; /* size = 0x2c */


typedef Unkstruct_8011D030 Unkstruct_80168828_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_ee376596: P3.40 T3 band rank 362; 56 TNC sites in 7 bodies; struct map 56 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016D848_2; /* size = 0x1c */

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

typedef Unkstruct_801825C0 Unkstruct_80183560; /* size = 0x10c */

typedef struct {
    /* Unkstruct_69c5f8fc: P3.40 T3 band rank 388; 50 TNC sites in 5 bodies; struct map 50 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80184178; /* size = 0x24 */

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

typedef Unkstruct_801343C4 Unkstruct_801343C4_2; /* size = 0x8 */

typedef Unkstruct_8011D030 Unkstruct_8016C2C4_3; /* size = 0x38 */

typedef Unkstruct_8011D030 Unkstruct_80168430_2; /* size = 0x34 */

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
    /* Unkstruct_20fcc757: P3.40 T3 band rank 431; 44 TNC sites in 11 bodies; struct map 44 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801E26BC; /* size = 0x2c */

typedef struct {
    /* Unkstruct_c7bd3214: P3.40 T3 band rank 437; 44 TNC sites in 2 bodies; struct map 44 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ u8 unk12;
    /* 0x0013 */ u8 pad13[0x21];
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u8 pad38[0x14];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ s32 unk54;
} Unkstruct_8016A8FC; /* size = 0x58 */

typedef Unkstruct_801202A0 Unkstruct_8012ACA0_2; /* size = 0xa0 */

typedef Unkstruct_8001C9D0 Unkstruct_801647A4_4; /* size = 0x84 */


typedef struct {
    /* Unkstruct_4a0b4073: P3.40 T3 band rank 454; 42 TNC sites in 7 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80180C68; /* size = 0x8 */

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
} Unkstruct_801800CC;
typedef Unkstruct_801800CC Unkstruct_801825A4; /* size = 0x108 */

typedef Unkstruct_8011D030 Unkstruct_8017D030; /* size = 0x38 */

typedef Unkstruct_800B5BD8 Unkstruct_8016BBE0_3; /* size = 0x1c */

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
    /* T18.c16: SC03_105 record pool D_801BA734[0x60], stride 0x5C (T16.c8); common fields from the pool handler views
     * (judge c5); +0x20 draw block, +0x48 anim cursor (offset views hand-folded); ext50: per-kind words +0x50..+0x5B, variants
     * by pool handler; s16 unk52 (kind 6, func_8018364C) moved into ext50 */
    /* Unkstruct_40137cba: P3.40 T3 band rank 6459; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
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
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ u8 pad2A[0x2];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u8 pad32[0x2];
    /* 0x0034 */ union {
        u16 u;
        s16 s;
    } unk34;
    /* 0x0036 */ union {
        u16 u;
        s16 s;
    } unk36;
    /* 0x0038 */ union {
        u16 u;
        s16 s;
    } unk38;
    /* 0x003a */ union {
        u16 u;
        s16 s;
    } unk3A;
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ s32 unk40;
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s16 unk4C;
    /* 0x004e */ s16 unk4E;
    /* 0x0050 */ union { u8 raw[0xc]; struct { u8 pad0[0x2]; s16 unk52; } kSC03_105_80184E74; struct { s16 unk50; } kSC03_105_801848A4; struct { u8 pad0[0x4]; s16 unk54; s16 unk56; } kSC03_105_80184A60; struct { u8 pad0[0x4]; s32 unk54; } kSC03_105_80184CA8; struct { u8 pad0[0x4]; s16 unk54; s16 unk56; } kSC03_105_80184B50; } ext50;
} Unkstruct_8018364C; /* size = 0x5c */

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
    /* Unkstruct_c349a47d: P3.40 T3 band rank 511; 37 TNC sites in 37 bodies; struct map 37 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017DF48_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_d86d2aca: P3.40 T3 band rank 520; 36 TNC sites in 36 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd0];
    /* 0x00d0 */ union { s32 val; void *p; struct { s16 lo; s16 hi; } i; struct { u16 lo; u16 hi; } u; } unkD0;
    /* 0x00d4 */ u8 padD4[0xc];
    /* 0x00e0 */ s32 unkE0;
} Unkstruct_80180CCC; /* size = 0xe4 */

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
    /* Unkstruct_2c8cbc07: P3.40 T3 band rank 536; 36 TNC sites in 3 bodies; struct map 36 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
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

typedef Ent_80164930_80164930 Unkstruct_801647A4_5; /* size = 0x64 */

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

typedef Ent_80164930_80164930 Unkstruct_80164EE0_2; /* size = 0x68 */

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

typedef Unkstruct_800B5BD8 Unkstruct_8016BD78_3; /* size = 0x1c */

typedef Unkstruct_80126B58 Unkstruct_80158FA4_3; /* size = 0x19c */

typedef Unkstruct_80126B58 Unkstruct_801654A8_2; /* size = 0x1fc */

typedef Unkstruct_8001C9D0 Unkstruct_801431E8_3; /* size = 0x78 */

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
    /* Unkstruct_b41a4dad: P3.40 T3 band rank 567; 34 TNC sites in 1 bodies; struct map 34 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017E880; /* size = 0x14 */


typedef struct {
    /* Unkstruct_d3473faf: P3.40 T3 band rank 3050; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80185020; /* size = 0x18 */

typedef Dst Unkstruct_801596F0_2; /* size = 0x2c */

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

typedef Unkstruct_801202A0 Unkstruct_8017BEBC_2; /* size = 0x10c */

typedef Unkstruct_80135EB0 Unkstruct_80136824_2; /* size = 0x10 */

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

typedef Unkstruct_801202A0 Unkstruct_801427EC_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_eac0514d: P3.40 T3 band rank 629; 28 TNC sites in 28 bodies; struct map 28 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017D658; /* size = 0x4 */

typedef Unkstruct_801202A0 Unkstruct_801431E8_4; /* size = 0x100 */

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

typedef Unkstruct_800B5BD8 Unkstruct_80164BDC_3; /* size = 0x20 */

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

typedef Unkstruct_80126B58 Unkstruct_8015FAE8_2; /* size = 0x188 */

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

typedef Unkstruct_801343C4 Unkstruct_80135004_2; /* size = 0x8 */

typedef Unkstruct_80126B58 Unkstruct_8015C128_2; /* size = 0x240 */

typedef Unkstruct_8016C49C Unkstruct_8016C49C_4; /* size = 0x38 */

typedef Unkstruct_801202A0 Unkstruct_801824C8; /* size = 0x100 */

typedef Unkstruct_8016DF5C_3 Unkstruct_8016DF5C_4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2054b96e: P3.40 T3 band rank 649; 27 TNC sites in 27 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80180CCC_2; /* size = 0x14 */

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

typedef Unkstruct_8017EB8C Unkstruct_8017ED80; /* size = 0x100 */

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
    /* Unkstruct_497bd52c: P3.40 T3 band rank 710; 24 TNC sites in 8 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017D664; /* size = 0x2c */


typedef struct {
    /* Unkstruct_dc086f11: P3.40 T3 band rank 714; 24 TNC sites in 8 bodies; struct map 24 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_801805F0; /* size = 0x4 */


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

typedef Unkstruct_80135480_6 Unkstruct_80135480_7; /* size = 0x10 */

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
    /* Unkstruct_c9fa9cd6: P3.40 T3 band rank 752; 23 TNC sites in 23 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017CD9C; /* size = 0x4 */

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
} Unkstruct_8017DCF8;
typedef Unkstruct_8017DCF8 Unkstruct_80186434; /* size = 0xe0 */

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

typedef Unkstruct_8016A8FC Unkstruct_8016A8FC_3; /* size = 0x58 */

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

typedef Unkstruct_8017EB8C_2 Unkstruct_8017ED80_2; /* size = 0x20 */


typedef struct {
    /* Unkstruct_3002b31c: P3.40 T3 band rank 1825; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017BF50; /* size = 0x20 */

typedef Unkstruct_8015E4B0 Unkstruct_8015E4B0_4; /* size = 0x14 */

typedef Unkstruct_80126B58 Unkstruct_80149FB0_2; /* size = 0x1cc */

typedef struct {
    /* Unkstruct_a991abd5: P3.40 T3 band rank 820; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3c];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ s16 unk62;
} Unkstruct_80164BDC_4; /* size = 0x64 */

typedef struct {
    /* Unkstruct_b494ae08: P3.40 T3 band rank 822; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801E2670; /* size = 0x2c */

typedef struct {
    /* Unkstruct_f35eb97b: P3.40 T3 band rank 824; 21 TNC sites in 7 bodies; struct map 21 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016C2C4_4; /* size = 0x1c */

typedef Unkstruct_8011D030 Unkstruct_8016BD78_4; /* size = 0x24 */

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

typedef Unkstruct_80126B58 Unkstruct_8015C128_3; /* size = 0x240 */

typedef Unkstruct_8011D030 Unkstruct_8016A290_5; /* size = 0x38 */

typedef Unkstruct_801343C4 Unkstruct_80135004_3; /* size = 0x8 */

typedef Unkstruct_80165240 Unkstruct_80165240_2; /* size = 0x38 */

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

typedef Unkstruct_801202A0 Unkstruct_80182C98; /* size = 0x104 */

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


typedef Unkstruct_80126B58 Unkstruct_801727D0_2; /* size = 0x218 */

typedef struct {
    /* Unkstruct_0d6a98fb: P3.40 T3 band rank 859; 20 TNC sites in 5 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ s32 unk2C;
} Unkstruct_8017F1B8; /* size = 0x30 */

typedef Unkstruct_8011D030 Unkstruct_8017D408; /* size = 0x38 */

typedef struct {
    /* Unkstruct_bae7bfa4: P3.40 T3 band rank 881; 20 TNC sites in 4 bodies; struct map 20 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017E6A4; /* size = 0x14 */


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

typedef Unkstruct_80135EB0 Unkstruct_80136824_3; /* size = 0x10 */

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
} Unkstruct_8017F688;
typedef Unkstruct_8017F688 Unkstruct_80181D38; /* size = 0x24 */

typedef Unkstruct_8017F688 Unkstruct_80181914; /* size = 0x24 */

typedef Unkstruct_80126B58 Unkstruct_801727D0_3; /* size = 0x218 */

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

typedef Unkstruct_800B5BD8 Unkstruct_8017C004_3; /* size = 0x30 */

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
    /* Unkstruct_e75ec82d: P3.40 T17 drift rank 78; 12 TNC sites in 12 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x20];
    /* 0x0044 */ s32 unk44;
} Unkstruct_80165FA4_2;
typedef Unkstruct_80165FA4_2 Unkstruct_80165FA4; /* size = 0x48 */

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

typedef Unkstruct_801202A0 Unkstruct_801831C8; /* size = 0x100 */

typedef Unkstruct_8016E7C8 Unkstruct_8016E7C8_2; /* size = 0x10 */

typedef Unkstruct_8017BB34 Unkstruct_8017BA3C_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_b96ad58f: P3.40 T3 band rank 956; 18 TNC sites in 6 bodies; struct map 18 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_8017D598_2; /* size = 0x10 */

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
    /* Unkstruct_d0f7f6d1: P3.40 T3 band rank 1050; 16 TNC sites in 8 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_801805F0_2; /* size = 0x68 */

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

typedef Unkstruct_801312D0 Unkstruct_801312D0_3; /* size = 0x8 */

typedef Unkstruct_8017BB34 Unkstruct_8017BB34_2; /* size = 0x10 */

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

typedef Pair_8013AD38 Unkstruct_8013AD38_4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_e48bdacd: P3.40 T3 band rank 1064; 16 TNC sites in 4 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
} Unkstruct_8016E728; /* size = 0x18 */

typedef Unkstruct_801202A0 Unkstruct_8017F2A0; /* size = 0x10c */

typedef Unkstruct_800B5BD8 Unkstruct_80184370; /* size = 0x38 */

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

typedef Unkstruct_800B5BD8 Unkstruct_8018BAB4; /* size = 0x38 */

typedef Unkstruct_800B5BD8 Unkstruct_801887E8; /* size = 0x38 */

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

typedef Unkstruct_801202A0 Unkstruct_80184214; /* size = 0x100 */

typedef Unkstruct_800B5BD8 Unkstruct_8018AC0C; /* size = 0x38 */

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
    /* Unkstruct_34af6ee4: P3.40 T3 band rank 1089; 16 TNC sites in 1 bodies; struct map 16 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
} Unkstruct_80182BDC;
typedef Unkstruct_80182BDC Unkstruct_801838C8; /* size = 0x34 */

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

typedef Unkstruct_80182BDC Unkstruct_80185E28; /* size = 0x34 */

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

typedef Unkstruct_80182BDC Unkstruct_80183084; /* size = 0x34 */

typedef Unkstruct_80182BDC Unkstruct_801838EC; /* size = 0x34 */

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
} Unkstruct_80181AD0;
typedef Unkstruct_80181AD0 Unkstruct_801859F4; /* size = 0x10c */

typedef Unkstruct_80182BDC Unkstruct_80189FF0; /* size = 0x34 */

typedef Unkstruct_80175DA8_3 Unkstruct_80175DA8_4; /* size = 0x18 */

typedef Unkstruct_80175DA8_3 Unkstruct_80175DA8_5; /* size = 0x18 */

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

typedef Unkstruct_80182BDC Unkstruct_8018AC00; /* size = 0x34 */

typedef struct {
    /* Unkstruct_b8c0d900: P3.40 T3 band rank 1123; 15 TNC sites in 15 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017EAB4; /* size = 0x4 */

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
    /* Unkstruct_4041aa85: P3.40 T3 band rank 1129; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017C4F8; /* size = 0x20 */

typedef struct {
    /* Unkstruct_cf2b2be2: P3.40 T3 band rank 1134; 15 TNC sites in 5 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017F554; /* size = 0x4 */

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
    /* Unkstruct_8018B164: P3.40 T3 band rank 1149; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_801826E8; /* size = 0x10 */

typedef Unkstruct_8011D030 Unkstruct_8017DF10; /* size = 0x38 */

typedef struct {
    /* Unkstruct_95634e7b: P3.40 T3 band rank 1152; 15 TNC sites in 3 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801872D8; /* size = 0x100 */

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
    /* Unkstruct_06b85f92: P3.40 T3 band rank 1159; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ union {
        u16 u;
        s16 s;
    } unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s32 unk10;
} Unkstruct_8017E634; /* size = 0x14 */

typedef Unkstruct_8011D030 Unkstruct_8017C004_4; /* size = 0x38 */

typedef Unkstruct_8011D030 Unkstruct_8016C998_3; /* size = 0x38 */

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

typedef Unkstruct_8017F6D8 Unkstruct_8017F8CC; /* size = 0x90 */

typedef struct {
    /* Unkstruct_2f082b78: P3.40 T3 band rank 1167; 15 TNC sites in 1 bodies; struct map 15 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80185990; /* size = 0x38 */

typedef Unkstruct_8018234C Unkstruct_80185E34; /* size = 0x14 */

typedef Unkstruct_8017F368 Unkstruct_8018A2E0; /* size = 0x24 */

typedef Unkstruct_8018234C Unkstruct_80182498; /* size = 0x14 */

typedef Unkstruct_8018234C Unkstruct_801829F8; /* size = 0x14 */

typedef Unkstruct_8018234C Unkstruct_801860E8; /* size = 0x14 */

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

typedef Unkstruct_8018234C Unkstruct_8018B23C; /* size = 0x14 */

typedef Unkstruct_8018234C Unkstruct_8018EBCC; /* size = 0x14 */

typedef Unkstruct_8018234C Unkstruct_8018B2C4; /* size = 0x14 */

typedef Unkstruct_8018234C Unkstruct_80187314; /* size = 0x14 */

typedef Unkstruct_801312D0 Unkstruct_8017E878; /* size = 0x8 */

typedef Unkstruct_8018234C Unkstruct_80185150; /* size = 0x14 */

typedef Unkstruct_8018234C Unkstruct_80184918; /* size = 0x14 */

typedef Unkstruct_8018234C Unkstruct_801865DC; /* size = 0x14 */

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

typedef Unkstruct_8018234C Unkstruct_801844D4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_133b6f2b: P3.40 T3 band rank 1218; 14 TNC sites in 14 bodies; struct map 14 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x70];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017DC9C; /* size = 0x74 */


typedef Unkstruct_8001C9D0 Unkstruct_80142E38_3; /* size = 0x1c */

typedef Unkstruct_8001C9D0 Unkstruct_80142DC4_3; /* size = 0x1c */

typedef Unkstruct_801202A0 Unkstruct_80142A10_2; /* size = 0x100 */

typedef Unkstruct_80126B58 Unkstruct_80173220_2; /* size = 0xbc */

typedef Unkstruct_8001C9D0 Unkstruct_80158FA4_4; /* size = 0x14 */

typedef Ent_80164930_80164930 Unkstruct_80164744_2; /* size = 0x24 */

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

typedef Unkstruct_801202A0 Unkstruct_80142E38_4; /* size = 0x100 */

typedef Unkstruct_801202A0 Unkstruct_80142DC4_4; /* size = 0x100 */

typedef struct Entry_8016E95C Unkstruct_8016EBA8_2; /* size = 0x8 */

typedef struct Entry_8016E95C Unkstruct_8016E9EC_2; /* size = 0x8 */

typedef Unkstruct_8016C49C Unkstruct_8016C49C_5; /* size = 0x38 */


typedef Unkstruct_8011D030 Unkstruct_8016A290_6; /* size = 0x38 */


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

typedef Unkstruct_8017EB8C_3 Unkstruct_8017ED80_3; /* size = 0x20 */

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

typedef Unkstruct_8016DF5C_3 Unkstruct_8016DF5C_6; /* size = 0x38 */

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
    /* 0x002a */ union {
        u8 u;
        s8 s;
    } unk2A;
    /* 0x002b */ u8 pad2B[0x1];
} Unkstruct_8002C8F4; /* size = 0x2c */

typedef Unkstruct_8011D030 Unkstruct_8017D060; /* size = 0x38 */

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

typedef Unkstruct_801202A0 Unkstruct_8018164C; /* size = 0x10c */

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
    /* Unkstruct_a7c7ef1e: P3.40 T3 band rank 1360; 13 TNC sites in 1 bodies; struct map 13 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ union {
        s16 s;
        u16 u;
    } unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ union {
        s16 s;
        u16 u;
    } unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ union {
        s16 s;
        u16 u;
    } unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ union {
        s16 s;
        u16 u;
    } unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ union {
        s16 s;
        u16 u;
    } unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x6];
    /* 0x0078 */ s32 unk78;
    /* 0x007c */ u8 pad7C[0xc];
    /* 0x0088 */ u16 unk88;
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u16 unk8C;
    /* 0x008e */ u8 pad8E[0x72];
    /* 0x0100 */ union {
        s16 s;
        u16 u;
    } unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017ED0C; /* size = 0x104 */

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

typedef Ent_8017D6EC Unkstruct_8017DA08_2; /* size = 0x24 */

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
    /* Unkstruct_8905aeec: P3.40 T3 band rank 1383; 12 TNC sites in 12 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CB7F0;
typedef Unkstruct_800CB7F0 Unkstruct_80169FE0; /* size = 0x24 */

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

typedef Unkstruct_8015D380 Unkstruct_8015D380_4; /* size = 0x14 */


typedef struct {
    /* Unkstruct_26f62321: P3.40 T3 band rank 1398; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ s16 unk62;
    /* 0x0064 */ s16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_8017E778_2; /* size = 0x68 */

typedef Unkstruct_801202A0 Unkstruct_8017E520_2; /* size = 0x5c */

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
    /* Unkstruct_73782c2f: P3.40 T3 band rank 1408; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80184944; /* size = 0x24 */

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
    /* Unkstruct_c77b0c7a: P3.40 T3 band rank 1420; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x18];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 pad24[0x3];
    /* 0x0027 */ u8 unk27;
} Unkstruct_80183650_2; /* size = 0x28 */


typedef struct {
    /* Unkstruct_e923d23e: P3.40 T3 band rank 1426; 12 TNC sites in 4 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801E2D58; /* size = 0xe8 */

typedef Unkstruct_8016E728 Unkstruct_8016E728_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_469ff04b: P3.40 T3 band rank 1433; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
} Unkstruct_8017C8B0; /* size = 0x8 */

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

typedef Pair_8013AD38 Unkstruct_8013AD38_5; /* size = 0x4 */

typedef Unkstruct_8017BB34 Unkstruct_8017BB34_3; /* size = 0x10 */

typedef struct {
    /* Unkstruct_900296ab: P3.40 T3 band rank 1439; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801872D8_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_d6c1a7dd: P3.40 T3 band rank 1441; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017E69C; /* size = 0x2c */

typedef Unkstruct_801312D0 Unkstruct_801312D0_4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_0ae90e3d: P3.40 T3 band rank 1445; 12 TNC sites in 2 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E2EC0; /* size = 0x38 */

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
    /* Unkstruct_1dfe929c: P3.40 T3 band rank 3951; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801AC8B8_2; /* size = 0x30 */

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

struct Vec {
    s16 unk0;
    s16 unk2;  /* x */
    s16 unk4;
    s16 unk6;  /* y */
    s16 unk8;
    s16 unkA;  /* z */
};

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

typedef Unkstruct_80186144 Unkstruct_8017E130; /* size = 0x104 */

typedef Unkstruct_80126B58 Unkstruct_80170748; /* size = 0x218 */

typedef struct {
    /* Unkstruct_cef068ce: P3.40 T3 band rank 1527; 11 TNC sites in 11 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb0];
    /* 0x00b0 */ s32 unkB0;
} Unkstruct_8018069C; /* size = 0xb4 */

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
    /* 0x0000 */ union {
        struct { void *unk0; } v0;
        struct { s32 unk0; } v1;
    } unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x1de];
    /* 0x01e6 */ u16 unk1E6;
    /* 0x01e8 */ s32 unk1E8;
    /* 0x01ec */ s16 unk1EC;
    /* 0x01ee */ u8 pad1EE[0x2];
} Unkstruct_80038698; /* size = 0x1f0 */

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

typedef Unkstruct_801343C4 Unkstruct_8018BED0; /* size = 0x8 */

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
    /* Unkstruct_dff1fce1: P3.40 T3 band rank 1623; 11 TNC sites in 1 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x3];
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 padA[0x3];
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80181970;
typedef Unkstruct_80181970 Unkstruct_80183F3C; /* size = 0x10 */

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

typedef Unkstruct_80181970 Unkstruct_8018A860; /* size = 0x10 */

typedef Unkstruct_80181970 Unkstruct_80185458; /* size = 0x10 */

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

typedef Unkstruct_80181970 Unkstruct_80185C00; /* size = 0x10 */

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

typedef Unkstruct_80181970 Unkstruct_8018570C; /* size = 0x10 */

typedef Unkstruct_801343C4 Unkstruct_8018B028; /* size = 0x8 */

typedef Unkstruct_8011D030 Unkstruct_8017CE90_3; /* size = 0x34 */

typedef Unkstruct_80181970 Unkstruct_80184774; /* size = 0x10 */

typedef Unkstruct_80181970 Unkstruct_80183AF8; /* size = 0x10 */

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

typedef Unkstruct_80181970 Unkstruct_80181ABC_2; /* size = 0x10 */

typedef Unkstruct_80181970 Unkstruct_8018E1F0; /* size = 0x10 */

typedef Unkstruct_801343C4 Unkstruct_8018478C; /* size = 0x8 */

typedef Unkstruct_80181970 Unkstruct_80186938; /* size = 0x10 */

typedef Unkstruct_80181970 Unkstruct_8018A8E8; /* size = 0x10 */

typedef Unkstruct_801202A0 Unkstruct_80181148; /* size = 0x100 */

typedef Unkstruct_80181970 Unkstruct_8018201C; /* size = 0x10 */

typedef Unkstruct_801343C4 Unkstruct_80188C04; /* size = 0x8 */

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

typedef Unkstruct_8017DC9C Unkstruct_8017D6B0; /* size = 0x74 */

typedef struct {
    /* Unkstruct_9550c910: P3.40 T3 band rank 1630; 10 TNC sites in 10 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb0];
    /* 0x00b0 */ s32 unkB0;
} Unkstruct_80180B18; /* size = 0xb4 */

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
    /* Unkstruct_98bc2669: P3.40 T3 band rank 1641; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017DCD0_3; /* size = 0x18 */

typedef struct {
    /* Unkstruct_c511c842: P3.40 T3 band rank 1644; 10 TNC sites in 5 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x48];
    /* 0x004c */ s32 unk4C;
} Unkstruct_800CCFA8; /* size = 0x50 */

typedef Unkstruct_801202A0 Unkstruct_80182928; /* size = 0x60 */

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

typedef Unkstruct_800B5BD8 Unkstruct_8016DF5C_7; /* size = 0x38 */

typedef Unkstruct_8011D030 Unkstruct_8017E22C; /* size = 0x38 */

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

typedef Unkstruct_8011D030 Unkstruct_8017D0F8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_6ce1f507: P3.40 T3 band rank 1668; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_801813B4_2; /* size = 0x8 */

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
    /* Unkstruct_8019FF14: P3.40 T3 band rank 1680; 10 TNC sites in 2 bodies; struct map 11 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_801847C8; /* size = 0x10 */

typedef Unkstruct_80181ACC Unkstruct_8018A934; /* size = 0x10 */

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
    /* Unkstruct_d444badd: P3.40 T3 band rank 1689; 10 TNC sites in 2 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_801848CC; /* size = 0x1c */

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


typedef Unkstruct_800B5BD8 Unkstruct_80184FB0; /* size = 0x2c */

typedef struct {
    /* Unkstruct_3ed86d6d: P3.40 T3 band rank 1712; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ union {
        s16 s;
        u16 u;
    } unk2;
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

typedef Unkstruct_8017DB80 Unkstruct_8017F55C; /* size = 0x4c */

typedef Unkstruct_80135EB0 Unkstruct_80136824_5; /* size = 0x10 */

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

typedef Unkstruct_8011D030 Unkstruct_80182A40; /* size = 0x34 */

typedef Unkstruct_80135EB0 Unkstruct_80136824_6; /* size = 0x10 */

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

typedef Unkstruct_8011D030 Unkstruct_801808E0; /* size = 0x34 */

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

typedef Unkstruct_80126B58 Unkstruct_80184E84; /* size = 0xd0 */

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

typedef Unkstruct_80126B58 Unkstruct_80185D2C; /* size = 0xd0 */

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

typedef Unkstruct_80135EB0 Unkstruct_80136824_7; /* size = 0x10 */

typedef Unkstruct_8011D030 Unkstruct_801681FC_3; /* size = 0x34 */

typedef struct {
    /* Unkstruct_f8d839af: P3.40 T3 band rank 1800; 10 TNC sites in 1 bodies; struct map 10 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80180BD0; /* size = 0x104 */

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

typedef Unkstruct_8011D030 Unkstruct_80180E74; /* size = 0x34 */

typedef struct {
    /* Unkstruct_37c0f40e: P3.40 T3 band rank 1805; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_801825C4; /* size = 0x8 */

typedef Unkstruct_80126B58 Unkstruct_8015D4E8_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_687cf1dc: P3.40 T3 band rank 1807; 9 TNC sites in 9 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017D7A4_2; /* size = 0x18 */

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
    /* Unkstruct_063f5e04: P3.40 T3 band rank 1817; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ void * unk8;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ void * unk10;
    /* 0x0014 */ Rec14 **unk14;
    /* 0x0018 */ void * unk18;
} Unkstruct_8002F4E4; /* size = 0x1c */

typedef struct Entry_8016E95C Unkstruct_8016EC0C_2; /* size = 0x8 */

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

typedef Vec3s Unkstruct_80136A94_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_46c55caf: P3.40 T3 band rank 1831; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
} Unkstruct_8017E254_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_4d590a77: P3.40 T3 band rank 1833; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ u16 unk20;
    /* 0x0022 */ u16 unk22;
} Unkstruct_80175DA8_6; /* size = 0x24 */

typedef struct {
    /* Unkstruct_60a73047: P3.40 T3 band rank 1837; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801839B4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_80df96b6: P3.40 T3 band rank 1846; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x16];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ s32 unk30;
} Unkstruct_8016D688_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_83954e38: P3.40 T3 band rank 1847; 9 TNC sites in 3 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017EA88_2; /* size = 0x30 */


typedef Unkstruct_801202A0 Unkstruct_801841C8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_16b0fe1a: P3.40 T3 band rank 1862; 9 TNC sites in 2 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017EC7C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_27b35e18: P3.40 T3 band rank 1863; 9 TNC sites in 2 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5];
    /* 0x0005 */ u8 unk5;
    /* 0x0006 */ u8 pad6[0xe];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x24];
    /* 0x003c */ s32 unk3C;
    /* 0x0040 */ s32 unk40;
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_8017D04C; /* size = 0x54 */

typedef struct {
    /* Unkstruct_51f7ca50: P3.40 T3 band rank 1865; 9 TNC sites in 2 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x8];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x1e5];
    /* 0x01f5 */ u8 unk1F5;
    /* 0x01f6 */ u8 unk1F6;
    /* 0x01f7 */ u8 unk1F7;
    /* 0x01f8 */ u8 pad1F8[0x1];
    /* 0x01f9 */ u8 unk1F9;
    /* 0x01fa */ u8 pad1FA[0x2];
} Unkstruct_80039C70; /* size = 0x1fc */

typedef struct {
    /* Unkstruct_c980cfc6: P3.40 T3 band rank 1868; 9 TNC sites in 2 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u8 pad62[0x14];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ u8 pad78[0x66];
    /* 0x00de */ s16 unkDE;
    /* 0x00e0 */ u8 padE0[0x8];
    /* 0x00e8 */ u32 unkE8;
} Unkstruct_80185A04; /* size = 0xec */

typedef struct {
    /* Unkstruct_f6df88a4: P3.40 T3 band rank 1869; 9 TNC sites in 2 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017EBA0_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_02d64b2e: P3.40 T3 band rank 1870; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0xc];
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u8 pad62[0x2];
} Unkstruct_800CC024; /* size = 0x64 */

typedef struct {
    /* Unkstruct_049be2e6: P3.40 T3 band rank 1872; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
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
} Unkstruct_80034CF0_2; /* size = 0x2c */

typedef struct {
    /* Unkstruct_0dda924a: P3.40 T3 band rank 1874; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x6];
    /* 0x0014 */ u32 unk14;
    /* 0x0018 */ u8 pad18[0x1c];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x4];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u16 unk40;
    /* 0x0042 */ u8 pad42[0x2];
} Unkstruct_8017D730; /* size = 0x44 */

typedef struct {
    /* Unkstruct_0fbc9b1a: P3.40 T3 band rank 1876; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
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
} Unkstruct_8018247C_2; /* size = 0x20 */

typedef Unkstruct_801202A0 Unkstruct_801872EC; /* size = 0x44 */

typedef Unkstruct_8018BBBC Unkstruct_8017EF54; /* size = 0x100 */

typedef struct {
    /* Unkstruct_1581c34d: P3.40 T3 band rank 1879; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ u8 pad60[0x10];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x4f];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0xa];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_8018EE00; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_16479d08: P3.40 T3 band rank 1880; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
} Unkstruct_8013C414_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_1d3f916b: P3.40 T3 band rank 1884; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ s16 unk36;
} Unkstruct_80184028; /* size = 0x38 */

typedef struct {
    /* Unkstruct_22b05bdb: P3.40 T3 band rank 1888; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3c];
    /* 0x003c */ s32 unk3C;
    /* 0x0040 */ s32 unk40;
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_80188988_2; /* size = 0x54 */

typedef struct {
    /* Unkstruct_267aff0d: P3.40 T3 band rank 1890; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xbc];
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ s16 unkE2;
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ u8 padE6[0x18];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80187368; /* size = 0x100 */

typedef struct {
    /* Unkstruct_38b63f94: P3.40 T3 band rank 1897; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x48];
    /* 0x0068 */ s32 unk68;
    /* 0x006c */ u8 pad6C[0x4];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x6a];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80181C00_2; /* size = 0x100 */

typedef Unkstruct_80184028 Unkstruct_80187644; /* size = 0x38 */

typedef struct {
    /* Unkstruct_41af869e: P3.40 T3 band rank 1900; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
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
} Unkstruct_800CC7FC; /* size = 0x34 */

typedef struct {
    /* Unkstruct_50d4a234: P3.40 T3 band rank 1907; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017F5D0; /* size = 0x14 */

typedef struct {
    /* Unkstruct_51b27337: P3.40 T3 band rank 1908; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0xd8];
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ s16 unkE6;
    /* 0x00e8 */ u32 unkE8;
} Unkstruct_8018655C; /* size = 0xec */

typedef struct {
    /* Unkstruct_5353028c: P3.40 T3 band rank 1911; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x2c];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_80181CD4; /* size = 0x104 */

typedef struct {
    /* Unkstruct_5e6db546: P3.40 T3 band rank 1915; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_801840D0_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_6014b2ee: P3.40 T3 band rank 1916; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x36];
    /* 0x006c */ void * unk6C;
    /* 0x0070 */ u8 pad70[0x1a];
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ u8 pad8C[0x7e];
    /* 0x010a */ s16 unk10A;
} Unkstruct_8017F390; /* size = 0x10c */

typedef struct {
    /* Unkstruct_6085f1f2: P3.40 T3 band rank 1917; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u32 unk10;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u32 unk20;
} Unkstruct_801859F4_2; /* size = 0x24 */

typedef Unkstruct_8018BBBC Unkstruct_80181408; /* size = 0x100 */

typedef struct {
    /* Unkstruct_704ab97c: P3.40 T3 band rank 1925; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_8017DDDC; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8383a1ca: P3.40 T3 band rank 1967; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x16];
    /* 0x0076 */ u16 unk76;
    /* 0x0078 */ u8 pad78[0x49];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80185AAC; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_83d48a89: P3.40 T3 band rank 1968; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xaa];
    /* 0x00aa */ s16 unkAA;
    /* 0x00ac */ s16 unkAC;
    /* 0x00ae */ u8 padAE[0x84];
    /* 0x0132 */ s16 unk132;
    /* 0x0134 */ u8 pad134[0xd0];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ u8 pad208[0xc];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_801835F8; /* size = 0x218 */

typedef struct {
    /* Unkstruct_84b5545c: P3.40 T3 band rank 1969; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
} Unkstruct_80185810; /* size = 0xc */

typedef struct {
    /* Unkstruct_882675c9: P3.40 T3 band rank 1971; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801876EC; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8e5e92af: P3.40 T3 band rank 1975; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x1e0];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ u8 pad208[0xc];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8017E51C; /* size = 0x218 */

typedef struct {
    /* Unkstruct_8f43c45e: P3.40 T3 band rank 1976; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd4];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x2e];
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u16 unk10A;
} Unkstruct_80180614; /* size = 0x10c */

typedef struct {
    /* Unkstruct_916141bd: P3.40 T3 band rank 1977; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
} Unkstruct_8017F9B4; /* size = 0x30 */


typedef struct {
    /* Unkstruct_9bfa6ce5: P3.40 T3 band rank 1983; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ union {
        u32 u;
        s32 s;
    } unk2C;
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CE004; /* size = 0x38 */

typedef struct {
    /* Unkstruct_a9c7b32c: P3.40 T3 band rank 1991; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x74];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
} Unkstruct_80181224; /* size = 0x98 */

typedef Unkstruct_8018BBBC Unkstruct_8017ED60; /* size = 0x100 */

typedef struct {
    /* Unkstruct_b5e3940a: P3.40 T3 band rank 1995; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x8];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ s16 unkDE;
} Unkstruct_801862A4; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_b76564cb: P3.40 T3 band rank 1996; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3ffc];
    /* 0x3ffc */ u32 unk3FFC;
} Unkstruct_80015B6C; /* size = 0x4000 */

typedef Unkstruct_801202A0 Unkstruct_80185808; /* size = 0x44 */

typedef struct {
    /* Unkstruct_badef1d9: P3.40 T3 band rank 2001; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x68];
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x2];
} Unkstruct_801809E4_2; /* size = 0x90 */

typedef struct {
    /* Unkstruct_cb0b4271: P3.40 T3 band rank 2008; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x28];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x14];
    /* 0x0064 */ s32 unk64;
} Unkstruct_801871B8; /* size = 0x68 */

typedef struct {
    /* Unkstruct_d3dd2efe: P3.40 T3 band rank 2011; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x36];
    /* 0x006c */ void * unk6C;
    /* 0x0070 */ u8 pad70[0x1a];
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ u8 pad8C[0x7e];
    /* 0x010a */ s16 unk10A;
} Unkstruct_80180190; /* size = 0x10c */

typedef struct {
    /* Unkstruct_d3fdf888: P3.40 T3 band rank 2012; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ s32 unk34;
} Unkstruct_801AE734_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_d44c5b68: P3.40 T3 band rank 2013; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ union {
        struct { s32 unk20; } v0;
        struct { void *unk0; } v1;
    } unk20;
    /* 0x0024 */ u8 pad24[0xc0];
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ s16 unkE6;
    /* 0x00e8 */ s16 unkE8;
    /* 0x00ea */ u8 padEA[0x20];
    /* 0x010a */ u8 unk10A;
    /* 0x010b */ u8 unk10B;
} Unkstruct_80185648; /* size = 0x10c */

typedef struct {
    /* Unkstruct_db5f0dd0: P3.40 T3 band rank 2015; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x100];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x4];
    /* 0x0106 */ s16 unk106;
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u16 unk10A;
} Unkstruct_801806B8; /* size = 0x10c */

typedef struct {
    /* Unkstruct_dba91497: P3.40 T3 band rank 2016; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
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
} Unkstruct_801828FC; /* size = 0x104 */

typedef struct {
    /* Unkstruct_f5c6b3ab: P3.40 T3 band rank 2027; 9 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_80182FE4; /* size = 0x24 */

typedef struct {
    /* Unkstruct_5faa8eec: P3.40 T3 band rank 2036; 8 TNC sites in 8 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80180384_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_674ebb28: P3.40 T3 band rank 2038; 8 TNC sites in 8 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80180C48_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_67d88685: P3.40 T3 band rank 2039; 8 TNC sites in 8 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
} Unkstruct_80180C48_3; /* size = 0x68 */

typedef struct {
    /* Unkstruct_7001fd84: P3.40 T3 band rank 2042; 8 TNC sites in 8 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017DE18_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_e1cc5d9e: P3.40 T3 band rank 2047; 8 TNC sites in 8 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_8017E78C_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_21146e77: P3.40 T3 band rank 2049; 8 TNC sites in 4 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x200];
    /* 0x0200 */ s32 unk200;
} Unkstruct_8017D1E0; /* size = 0x204 */

typedef struct {
    /* Unkstruct_29e32a60: P3.40 T3 band rank 2051; 8 TNC sites in 4 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x200];
    /* 0x0200 */ s32 unk200;
} Unkstruct_8017E91C; /* size = 0x204 */

typedef struct {
    /* Unkstruct_60faade5: P3.40 T3 band rank 2059; 8 TNC sites in 4 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017D6D4; /* size = 0x2c */

typedef struct {
    /* Unkstruct_73dba439: P3.40 T3 band rank 2062; 8 TNC sites in 4 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0xc];
    /* 0x0020 */ void * unk20;
} Unkstruct_8017E6A4_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_f9f8dad4: P3.40 T3 band rank 2078; 8 TNC sites in 4 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017F874; /* size = 0x20 */

typedef struct {
    /* Unkstruct_42bcd6ef: P3.40 T3 band rank 2088; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x6];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801AE990; /* size = 0x18 */

typedef struct {
    /* Unkstruct_4900a7be: P3.40 T3 band rank 2091; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x54];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ void * unkD0;
} Unkstruct_801861A4; /* size = 0xd4 */


typedef struct {
    /* Unkstruct_5a3ec275: P3.40 T3 band rank 2094; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017DC54_2; /* size = 0x14 */


typedef struct {
    /* Unkstruct_7313d444: P3.40 T3 band rank 2097; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_801818A4; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8017D8A4: P3.40 T3 band rank 2112; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x9];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017D8A4_2; /* size = 0x2c */

typedef struct {
    /* Unkstruct_886af8c3: P3.40 T3 band rank 2114; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x60];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_80186AAC_3; /* size = 0x74 */

typedef struct {
    /* Unkstruct_93ff072e: P3.40 T3 band rank 2115; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801EF554; /* size = 0x2c */

typedef Dst Unkstruct_8017CF4C; /* size = 0x2c */

typedef struct {
    /* Unkstruct_ad510453: P3.40 T3 band rank 2119; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018173C; /* size = 0x24 */

typedef struct {
    /* Unkstruct_c673bfa1: P3.40 T3 band rank 2123; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017EC6C; /* size = 0x2c */

typedef struct {
    /* Unkstruct_d4c44df1: P3.40 T3 band rank 2125; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017D704; /* size = 0x20 */

typedef struct {
    /* Unkstruct_daa4c602: P3.40 T3 band rank 2126; 8 TNC sites in 2 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x1a];
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
} Unkstruct_801AA7E4_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_07904baa: P3.40 T3 band rank 2133; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x18];
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ u8 pad32[0x2];
} Unkstruct_8017D4F0_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_07e9abda: P3.40 T3 band rank 2134; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
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
} Unkstruct_8018BBCC; /* size = 0x104 */

typedef struct {
    /* Unkstruct_0acc5146: P3.40 T3 band rank 2136; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_801876A0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_124ab2d7: P3.40 T3 band rank 2138; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x54];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x5a];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801870AC; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_1b093dbd: P3.40 T3 band rank 2149; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E2CD0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_1e08eab3: P3.40 T3 band rank 2154; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EA8C0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_25046ab1: P3.40 T3 band rank 2160; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E8238; /* size = 0x38 */

typedef struct {
    /* Unkstruct_257963c2: P3.40 T3 band rank 2161; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8017EC78; /* size = 0x60 */

typedef struct {
    /* Unkstruct_25b3584d: P3.40 T3 band rank 2162; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E5358; /* size = 0x38 */

typedef struct {
    /* Unkstruct_283fe5bf: P3.40 T3 band rank 2165; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EFB58; /* size = 0x38 */

typedef struct {
    /* Unkstruct_4ae9d18e: P3.40 T3 band rank 3142; 5 TNC sites in 2 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80180BF0; /* size = 0x24 */

typedef struct {
    /* Unkstruct_31bd88e7: P3.40 T3 band rank 2170; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801805D0_3; /* size = 0x18 */

typedef struct {
    /* Unkstruct_e6bb1976: P3.40 T3 band rank 4637; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_801818B8_2;

typedef struct {
    /* Unkstruct_3f5215be: P3.40 T3 band rank 2179; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801877A8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_446af41b: P3.40 T3 band rank 2181; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x6];
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ u8 pad24[0x78];
    /* 0x009c */ s16 unk9C;
    /* 0x009e */ u8 pad9E[0x4];
    /* 0x00a2 */ s16 unkA2;
} Unkstruct_8017E26C; /* size = 0xa4 */

typedef struct {
    /* Unkstruct_45aa81e0: P3.40 T3 band rank 2183; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x6];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x8];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_80186F78_2; /* size = 0x74 */

typedef struct {
    /* Unkstruct_472db236: P3.40 T3 band rank 2186; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_801873FC; /* size = 0x10 */

typedef struct {
    /* Unkstruct_40829e79: P3.40 T3 band rank 3252; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_801AB748; /* size = 0x24 */

typedef struct {
    /* Unkstruct_50d1a592: P3.40 T3 band rank 2193; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
} Unkstruct_8017DB30_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_543d9c12: P3.40 T3 band rank 2194; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2a];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u8 pad3C[0x2];
    /* 0x003e */ u16 unk3E;
    /* 0x0040 */ u8 pad40[0x2];
    /* 0x0042 */ u16 unk42;
} Unkstruct_801809BC; /* size = 0x44 */

typedef struct {
    /* Unkstruct_5cd2d2bc: P3.40 T3 band rank 2199; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x174];
    /* 0x0198 */ s32 unk198;
    /* 0x019c */ u8 pad19C[0x68];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ s32 unk208;
    /* 0x020c */ u8 pad20C[0x8];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8017E298_3; /* size = 0x218 */

typedef struct {
    /* Unkstruct_647ab578: P3.40 T3 band rank 2204; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801A5194_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_65480f05: P3.40 T3 band rank 2205; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x10];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_80168664_2; /* size = 0x38 */

typedef Unkstruct_801870AC Unkstruct_801866C8; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_6dc88aa4: P3.40 T3 band rank 2212; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x62];
    /* 0x0086 */ u16 unk86;
} Unkstruct_801866C4; /* size = 0x88 */

typedef struct {
    /* Unkstruct_720f1d20: P3.40 T3 band rank 2215; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80180570; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8487bfc0: P3.40 T3 band rank 2231; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801F0748; /* size = 0x38 */

typedef struct {
    /* Unkstruct_852e9a48: P3.40 T3 band rank 2232; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801856A8_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_925a88c0: P3.40 T3 band rank 2236; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0xc8];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017E548; /* size = 0x100 */

typedef struct {
    /* Unkstruct_97e14640: P3.40 T3 band rank 2242; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x14];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x18];
    /* 0x0076 */ u16 unk76;
} Unkstruct_8018098C; /* size = 0x78 */

typedef struct {
    /* Unkstruct_a2bca66f: P3.40 T3 band rank 2246; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801F218C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_a2f6ce91: P3.40 T3 band rank 2247; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x28];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
} Unkstruct_8017FF4C; /* size = 0x50 */

typedef struct {
    /* Unkstruct_b2d85bda: P3.40 T3 band rank 2257; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xbc];
    /* 0x00cc */ void * unkCC;
} Unkstruct_80183920; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_b3cc392f: P3.40 T3 band rank 2258; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ s16 unk32;
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8018418C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_b4c2c9ec: P3.40 T3 band rank 2259; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x10];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x1a];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ s16 unk102;
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u16 unk106;
    /* 0x0108 */ u16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_80182940; /* size = 0x10c */

typedef struct {
    /* Unkstruct_bf8c8555: P3.40 T3 band rank 2265; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 unk8;
    /* 0x0009 */ u8 unk9;
    /* 0x000a */ u8 unkA;
    /* 0x000b */ u8 padB[0x1];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8017F7C4; /* size = 0x10 */

typedef struct {
    /* Unkstruct_c1c67bb9: P3.40 T3 band rank 2266; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x10];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_80168664_4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_c9603dce: P3.40 T3 band rank 2268; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0xc];
    /* 0x0018 */ u8 unk18;
    /* 0x0019 */ u8 pad19[0x3];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
} Unkstruct_801853F0; /* size = 0x28 */

typedef struct {
    /* Unkstruct_c9f49cb3: P3.40 T3 band rank 2269; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x8];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x6];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x1a];
    /* 0x003a */ u16 unk3A;
    /* 0x003c */ u16 unk3C;
    /* 0x003e */ u8 pad3E[0x2];
} Unkstruct_80039308_3; /* size = 0x40 */

typedef struct {
    /* Unkstruct_dc5b4390: P3.40 T3 band rank 2284; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
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
} Unkstruct_8017FC10; /* size = 0x24 */


typedef Unkstruct_8017DF78 Unkstruct_80189C7C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_e3cd5cd1: P3.40 T3 band rank 2287; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u32 unk8;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u32 unk10;
    /* 0x0014 */ u32 unk14;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u32 unk1C;
    /* 0x0020 */ u32 unk20;
} Unkstruct_8001751C; /* size = 0x24 */

typedef struct {
    /* Unkstruct_e42393ba: P3.40 T3 band rank 2288; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
} Unkstruct_8017FCF4; /* size = 0xc */

typedef struct {
    /* Unkstruct_e461a0f0: P3.40 T3 band rank 2289; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x3e];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x57];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
    /* 0x00d4 */ u8 padD4[0x34];
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ s16 unk10A;
} Unkstruct_8017E69C_2; /* size = 0x10c */

typedef struct {
    /* Unkstruct_e80871d8: P3.40 T3 band rank 2292; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80180FE8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_e9c84182: P3.40 T3 band rank 2295; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EE0C0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ec152711: P3.40 T3 band rank 2296; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x1e];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x1a];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_8001F97C; /* size = 0x54 */

typedef struct {
    /* Unkstruct_f6d9d71a: P3.40 T3 band rank 2303; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801AC8B8; /* size = 0x30 */

typedef struct {
    /* Unkstruct_f75cf4fe: P3.40 T3 band rank 2305; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0xaa];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x8];
    /* 0x00ec */ s32 unkEC;
    /* 0x00f0 */ u8 padF0[0xe];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x4];
    /* 0x0106 */ u16 unk106;
} Unkstruct_8017F984; /* size = 0x108 */

typedef struct {
    /* Unkstruct_fae13f62: P3.40 T3 band rank 2306; 8 TNC sites in 1 bodies; struct map 8 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x18];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80181F7C_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_073966ec: P3.40 T3 band rank 2310; 7 TNC sites in 7 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017E330; /* size = 0x24 */

typedef Unkstruct_80126B58 Unkstruct_80170C74_2; /* size = 0x218 */

typedef Unkstruct_800B5BD8 Unkstruct_8016BEA0_3; /* size = 0x1c */

typedef Unkstruct_80162870 Unkstruct_80162870_2; /* size = 0x58 */

typedef Unkstruct_80126B58 Unkstruct_8015879C_2; /* size = 0xac */

typedef struct {
    /* Unkstruct_7345924a: P3.40 T3 band rank 2327; 7 TNC sites in 7 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017D620; /* size = 0x4 */

typedef Unkstruct_80126B58 Unkstruct_80158814_2; /* size = 0xac */

typedef struct {
    /* Unkstruct_7d2e7f66: P3.40 T3 band rank 2330; 7 TNC sites in 7 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
} Unkstruct_80142608_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_80167AE0: P3.40 T3 band rank 2331; 7 TNC sites in 7 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80168070; /* size = 0x24 */

typedef Unkstruct_80126B58 Unkstruct_80159968_2; /* size = 0x50 */

typedef struct {
    /* Unkstruct_87dbe7e7: P3.40 T3 band rank 2333; 7 TNC sites in 7 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017DFE4; /* size = 0x4 */

typedef Unkstruct_80126B58 Unkstruct_8015E344_2; /* size = 0x238 */

typedef Unkstruct_80126B58 Unkstruct_80158F00_2; /* size = 0x19c */


typedef struct {
    /* Unkstruct_c4ff5264: P3.40 T3 band rank 2340; 7 TNC sites in 7 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8018354C; /* size = 0x4 */

typedef Unkstruct_80126B58 Unkstruct_8015FD74_2; /* size = 0x19c */

typedef struct {
    /* Unkstruct_e3275e3d: P3.40 T3 band rank 2342; 7 TNC sites in 7 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
} Unkstruct_8016C998_4; /* size = 0x38 */

typedef Unkstruct_8011D030 Unkstruct_8016BEA0_4; /* size = 0x24 */

typedef struct S8013A0A4 Unkstruct_80138BE0_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_fa1bf044: P3.40 T3 band rank 2346; 7 TNC sites in 7 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017E090; /* size = 0x24 */

typedef struct {
    /* Unkstruct_f273672e: P3.40 T3 band rank 2348; 7 TNC sites in 5 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_801EFBC0; /* size = 0x8 */

typedef struct {
    /* Unkstruct_564fe412: P3.40 T3 band rank 2349; 7 TNC sites in 4 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x27];
    /* 0x0027 */ u8 unk27;
} Unkstruct_801823B8_2; /* size = 0x28 */

typedef struct {
    /* Unkstruct_14dd603d: P3.40 T3 band rank 2353; 7 TNC sites in 2 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x10];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u8 pad62[0x2];
} Unkstruct_800CCCA0; /* size = 0x64 */

typedef struct {
    /* Unkstruct_1be1fd9f: P3.40 T3 band rank 2354; 7 TNC sites in 2 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_800CCD2C; /* size = 0x1c */

typedef struct {
    /* Unkstruct_72c800c3: P3.40 T3 band rank 2355; 7 TNC sites in 2 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ void * unk4C;
    /* 0x0050 */ u8 pad50[0x10];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u8 pad62[0x2];
} Unkstruct_800CCDD8_2; /* size = 0x64 */

typedef struct {
    /* Unkstruct_8012BB3C: P3.40 T3 band rank 2357; 7 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
} Unkstruct_800159E4; /* size = 0xc */

typedef struct {
    /* Unkstruct_98d7394c: P3.40 T3 band rank 2361; 7 TNC sites in 2 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xc0];
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ u16 unkE6;
} Unkstruct_80183940; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_05f48a2e: P3.40 T3 band rank 2368; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EFB94; /* size = 0x38 */

typedef struct {
    /* Unkstruct_08fba9e7: P3.40 T3 band rank 2369; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x78];
    /* 0x0088 */ s16 unk88;
    /* 0x008a */ s16 unk8A;
    /* 0x008c */ s16 unk8C;
    /* 0x008e */ u8 pad8E[0x186];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_801803BC; /* size = 0x218 */

typedef Unkstruct_8011D030 Unkstruct_80168430_3; /* size = 0x34 */

typedef struct {
    /* Unkstruct_0c301225: P3.40 T3 band rank 2371; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x4];
    /* 0x00d4 */ s32 unkD4;
} Unkstruct_8017D588_2; /* size = 0xd8 */

typedef struct {
    /* Unkstruct_111b9066: P3.40 T3 band rank 2374; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u8 pad4[0x8];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x2];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ s16 unk16;
} Unkstruct_800CF290; /* size = 0x18 */

typedef struct {
    /* Unkstruct_1268222e: P3.40 T3 band rank 2377; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ Unkstruct_800B5BD8 *unk20;
} Unkstruct_801A5A10; /* size = 0x24 */


typedef struct {
    /* Unkstruct_169033ea: P3.40 T3 band rank 2379; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x210];
    /* 0x0234 */ s32 unk234;
    /* 0x0238 */ s32 unk238;
    /* 0x023c */ s32 unk23C;
    /* 0x0240 */ u8 pad240[0x4];
    /* 0x0244 */ s16 unk244;
    /* 0x0246 */ s16 unk246;
    /* 0x0248 */ s16 unk248;
    /* 0x024a */ u8 pad24A[0x2];
} Unkstruct_800CCB20; /* size = 0x24c */

typedef struct {
    /* Unkstruct_1ef1d0dc: P3.40 T3 band rank 2385; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x60];
    /* 0x0084 */ s16 unk84;
    /* 0x0086 */ u8 pad86[0x4e];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x28];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801A1E94; /* size = 0x104 */

typedef struct {
    /* Unkstruct_2bd07ed1: P3.40 T3 band rank 2394; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80186D40; /* size = 0x30 */

typedef struct {
    /* Unkstruct_2ec2f0d0: P3.40 T3 band rank 2396; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017F424; /* size = 0x24 */

typedef struct {
    /* Unkstruct_30321d98: P3.40 T3 band rank 2397; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x54];
    /* 0x0064 */ void * unk64;
} Unkstruct_8017DBB0; /* size = 0x68 */

typedef Unkstruct_801202A0 Unkstruct_8018613C; /* size = 0x60 */

typedef struct {
    /* Unkstruct_33131226: P3.40 T3 band rank 2400; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ u8 padD0[0x2c];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017F12C; /* size = 0x104 */


typedef struct {
    /* Unkstruct_464f9e34: P3.40 T3 band rank 2414; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ u8 padA[0x6];
    /* 0x0010 */ s32 unk10;
} Unkstruct_8017E424; /* size = 0x14 */

typedef struct {
    /* Unkstruct_46704642: P3.40 T3 band rank 2415; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
    /* 0x00e8 */ u8 padE8[0x18];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
} Unkstruct_8017DFE8; /* size = 0x104 */

typedef struct {
    /* Unkstruct_4ad9ffa4: P3.40 T3 band rank 2417; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x50];
    /* 0x00ae */ s16 unkAE;
    /* 0x00b0 */ u8 padB0[0x11];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x3c];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801896F8; /* size = 0x104 */

typedef struct {
    /* Unkstruct_54752729: P3.40 T3 band rank 2423; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80184CE0_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_559384f6: P3.40 T3 band rank 2424; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0xa];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80184184; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_5a8aea2a: P3.40 T3 band rank 2427; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801A5AE0; /* size = 0x30 */

typedef struct {
    /* Unkstruct_5eb46dd4: P3.40 T3 band rank 2431; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_801A7B08_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_68ce80eb: P3.40 T3 band rank 2440; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EF558; /* size = 0x38 */

typedef struct {
    /* Unkstruct_6ef82e95: P3.40 T3 band rank 2442; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x8];
    /* 0x000a */ u8 unkA;
    /* 0x000b */ u8 padB[0x1];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80033324; /* size = 0x10 */

typedef Unkstruct_8011D030 Unkstruct_8016A290_7; /* size = 0x38 */

typedef struct {
    /* Unkstruct_78a7446c: P3.40 T3 band rank 2452; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ u8 pad32[0x2];
} Unkstruct_8002374C; /* size = 0x34 */

typedef struct {
    /* Unkstruct_7b6b127e: P3.40 T3 band rank 2453; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ s32 unk10;
} Unkstruct_8017EEA4_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_83e4d916: P3.40 T3 band rank 2478; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
} Unkstruct_8017D3F8; /* size = 0xc */

typedef struct {
    /* Unkstruct_a462cabd: P3.40 T3 band rank 2502; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
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
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8017EC64;
typedef Unkstruct_8017EC64 Unkstruct_801813CC; /* size = 0x60 */

typedef struct {
    /* Unkstruct_9698b06c: P3.40 T3 band rank 2492; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xa];
    /* 0x002e */ u16 unk2E;
} Unkstruct_80180FA8; /* size = 0x30 */

typedef Unkstruct_801343C4 Unkstruct_801343C4_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_98fc576e: P3.40 T3 band rank 2494; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EE11C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_9a6c309f: P3.40 T3 band rank 2496; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x6];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0xe0];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017F6EC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_9e6860a7: P3.40 T3 band rank 2498; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_80184B50; /* size = 0x14 */

typedef struct {
    /* Unkstruct_a39fca17: P3.40 T3 band rank 2501; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_800CB00C; /* size = 0x8 */

typedef Unkstruct_801343C4 Unkstruct_801343C4_4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_aac9dfbe: P3.40 T3 band rank 2506; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0xc6];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017D7F0_2; /* size = 0x100 */

typedef Unkstruct_801202A0 Unkstruct_80181A4C; /* size = 0x7c */

typedef struct {
    /* Unkstruct_aea03e0f: P3.40 T3 band rank 2509; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u8 pad5C[0x16];
    /* 0x0072 */ u16 unk72;
    /* 0x0074 */ u8 pad74[0x88];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801857BC; /* size = 0x100 */

typedef Unkstruct_80186D40 Unkstruct_8018A724; /* size = 0x30 */

typedef struct {
    /* Unkstruct_b0f595d6: P3.40 T3 band rank 2511; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u16 unk62;
} Unkstruct_80182CBC; /* size = 0x64 */

typedef struct {
    /* Unkstruct_b3d8a314: P3.40 T3 band rank 2514; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x198];
    /* 0x0198 */ s32 unk198;
    /* 0x019c */ u8 pad19C[0x70];
    /* 0x020c */ s16 unk20C;
    /* 0x020e */ u8 pad20E[0x6];
    /* 0x0214 */ s8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8017DFD8; /* size = 0x218 */

typedef struct {
    /* Unkstruct_b5ef5685: P3.40 T3 band rank 2516; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xb4];
    /* 0x00d4 */ s32 unkD4;
} Unkstruct_8017F900; /* size = 0xd8 */

typedef Unkstruct_80165240 Unkstruct_80165240_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_c3b6e777: P3.40 T3 band rank 2524; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0xaa];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x8];
    /* 0x00ec */ s32 unkEC;
    /* 0x00f0 */ u8 padF0[0xe];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80180198; /* size = 0x100 */

typedef struct {
    /* Unkstruct_c41d3753: P3.40 T3 band rank 2525; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0xe];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xc];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB56C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_c77ae9f2: P3.40 T3 band rank 2526; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ void * unk8;
    /* 0x000c */ u8 padC[0x8];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_80182F4C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_ccaa275e: P3.40 T3 band rank 2529; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80181120; /* size = 0x10 */

typedef struct {
    /* Unkstruct_cd60e28f: P3.40 T3 band rank 2530; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xf0];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u16 unk102;
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u16 unk106;
    /* 0x0108 */ u16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_8017D48C; /* size = 0x10c */

typedef struct {
    /* Unkstruct_d4aebf3b: P3.40 T3 band rank 2535; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E2FB0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_dee9911b: P3.40 T3 band rank 2540; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
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
} Unkstruct_8017F684; /* size = 0x20 */

typedef struct {
    /* Unkstruct_e071b65a: P3.40 T3 band rank 2543; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_80181EEC; /* size = 0x68 */

typedef struct {
    /* Unkstruct_e21748cc: P3.40 T3 band rank 2545; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0xc6];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0xc];
    /* 0x010a */ s16 unk10A;
} Unkstruct_80185920; /* size = 0x10c */

typedef Unkstruct_80126B58 Unkstruct_8015C128_4; /* size = 0x240 */

typedef Unkstruct_801819B4_2 Unkstruct_80187844; /* size = 0x24 */

typedef struct {
    /* Unkstruct_ecedbfff: P3.40 T3 band rank 2557; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ void * unk20;
} Unkstruct_8017F4E4; /* size = 0x24 */

typedef struct {
    /* Unkstruct_f242c635: P3.40 T3 band rank 2563; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x26];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0x20];
    /* 0x0058 */ s32 unk58;
} Unkstruct_800CB6E4_2; /* size = 0x5c */

typedef Unkstruct_80186D40 Unkstruct_80188C34; /* size = 0x30 */

typedef struct {
    /* Unkstruct_f584476d: P3.40 T3 band rank 2567; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x68];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x3];
} Unkstruct_8017DB68; /* size = 0x78 */

typedef struct {
    /* Unkstruct_ff31c9cf: P3.40 T3 band rank 2571; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801829B4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ff46df00: P3.40 T3 band rank 2572; 7 TNC sites in 1 bodies; struct map 7 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E8294; /* size = 0x38 */

typedef struct {
    /* Unkstruct_299efe9e: P3.40 T3 band rank 2574; 6 TNC sites in 6 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8017E188; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_676dc255: P3.40 T3 band rank 2575; 6 TNC sites in 6 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
} Unkstruct_8017D598_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_8014C088: P3.40 T3 band rank 2578; 6 TNC sites in 6 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x5c];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u8 pad62[0x2];
} Unkstruct_800CB098; /* size = 0x64 */

typedef struct {
    /* Unkstruct_85e75d9c: P3.40 T3 band rank 2580; 6 TNC sites in 6 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017D598_4; /* size = 0x14 */

typedef Dst Unkstruct_8017CE58; /* size = 0x2c */

typedef struct {
    /* Unkstruct_a71c5ebe: P3.40 T3 band rank 2583; 6 TNC sites in 6 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_8018026C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_3e1aee9a: P3.40 T3 band rank 2591; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80183588; /* size = 0x20 */

typedef struct {
    /* Unkstruct_531061d2: P3.40 T3 band rank 2594; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x28];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CCDE8; /* size = 0x38 */

typedef Unkstruct_8017EC6C Unkstruct_8017D5D4; /* size = 0x2c */


typedef struct {
    /* Unkstruct_5fad882a: P3.40 T3 band rank 2601; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_801835F4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_61c5067e: P3.40 T3 band rank 2602; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x70];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017FBA0; /* size = 0x74 */

typedef struct {
    /* Unkstruct_8189fe30: P3.40 T3 band rank 2615; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017DB64; /* size = 0x24 */

typedef struct {
    /* Unkstruct_8b345e65: P3.40 T3 band rank 2617; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80182330; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_916ed0e9: P3.40 T3 band rank 2619; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017E51C_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_929789e4: P3.40 T3 band rank 2620; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8017F080; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_a4ee3b22: P3.40 T3 band rank 2624; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0xc4];
    /* 0x00d0 */ void * unkD0;
} Unkstruct_801824B0; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_a5309283: P3.40 T3 band rank 2625; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x24];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80181C18_2; /* size = 0x30 */


typedef Unkstruct_80126B58 Unkstruct_80156044_3; /* size = 0x1c4 */

typedef struct {
    /* Unkstruct_dc4beb32: P3.40 T3 band rank 2636; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_801825AC; /* size = 0x4 */

typedef struct {
    /* Unkstruct_ef087877: P3.40 T3 band rank 2639; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017EA88_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_f9fb38c6: P3.40 T3 band rank 2640; 6 TNC sites in 3 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801883FC; /* size = 0x30 */

typedef struct {
    /* Unkstruct_002f378c: P3.40 T3 band rank 2642; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x94];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_80180854_3; /* size = 0x9c */

typedef struct {
    /* Unkstruct_10412b6f: P3.40 T3 band rank 2648; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x198];
    /* 0x0198 */ s32 unk198;
} Unkstruct_8017DE70; /* size = 0x19c */

typedef struct {
    /* Unkstruct_1e1b9478: P3.40 T3 band rank 2651; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80180584; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_222176ea: P3.40 T3 band rank 2654; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x52];
    /* 0x0052 */ s16 unk52;
    /* 0x0054 */ u8 pad54[0x22];
    /* 0x0076 */ s16 unk76;
    /* 0x0078 */ u8 pad78[0x64];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_80185338; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_2dd80bf7: P3.40 T3 band rank 2659; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017FBB0_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_36f8bd75: P3.40 T3 band rank 2661; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017ED88; /* size = 0x24 */

typedef struct {
    /* Unkstruct_385ad486: P3.40 T3 band rank 2662; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CB8A4_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_5730fcd6: P3.40 T3 band rank 2671; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CDCA8; /* size = 0x1c */

typedef struct {
    /* Unkstruct_292811ff: P3.40 T3 band rank 4974; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80186710; /* size = 0x18 */
typedef Unkstruct_80186710 Unkstruct_8017F2A0_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_6ff29d29: P3.40 T3 band rank 2677; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80181690; /* size = 0x20 */

typedef struct {
    /* Unkstruct_a12fb965: P3.40 T3 band rank 2700; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_80180C38; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_a85fa7fa: P3.40 T3 band rank 2702; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017EB5C; /* size = 0x2c */

typedef struct {
    /* Unkstruct_a9e252d9: P3.40 T3 band rank 2703; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017F858_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_beaf1003: P3.40 T3 band rank 2709; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xfa];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ u8 pad100[0x2];
    /* 0x0102 */ s16 unk102;
} Unkstruct_8017EEE4; /* size = 0x104 */

typedef struct {
    /* Unkstruct_c94a47df: P3.40 T3 band rank 2711; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_801822F0; /* size = 0x74 */



typedef struct {
    /* Unkstruct_e341b097: P3.40 T3 band rank 2719; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0xc];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017D764_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_ecfa9241: P3.40 T3 band rank 2724; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801E4C48; /* size = 0x2c */


typedef struct {
    /* Unkstruct_f8b8e10d: P3.40 T3 band rank 2728; 6 TNC sites in 2 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x94];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_80181584; /* size = 0x9c */

typedef struct {
    /* Unkstruct_00a016c1: P3.40 T3 band rank 2733; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_801872B4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_035b6f18: P3.40 T3 band rank 2735; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x7c];
    /* 0x00dc */ u32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1e];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017E930; /* size = 0x100 */

typedef struct {
    /* Unkstruct_04677738: P3.40 T3 band rank 2740; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_801803FC_3; /* size = 0x8 */

typedef Unkstruct_801202A0 Unkstruct_8018613C_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_0b28891c: P3.40 T3 band rank 2746; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
} Unkstruct_801875F8; /* size = 0xc */

typedef struct {
    /* Unkstruct_0bb106b3: P3.40 T3 band rank 2748; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ s32 unk1C;
} Unkstruct_80181CDC; /* size = 0x20 */

typedef struct {
    /* Unkstruct_0cbe0daf: P3.40 T3 band rank 2750; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u8 pad62[0x14];
    /* 0x0076 */ u16 unk76;
} Unkstruct_80183E20; /* size = 0x78 */

typedef struct {
    /* Unkstruct_0faa75ae: P3.40 T3 band rank 2755; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0xe];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017E89C_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_1362a09d: P3.40 T3 band rank 2761; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xe6];
    /* 0x010a */ u8 unk10A;
    /* 0x010b */ u8 unk10B;
} Unkstruct_80184B3C; /* size = 0x10c */

typedef struct {
    /* Unkstruct_1443776e: P3.40 T3 band rank 2762; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80187254; /* size = 0x1c */

typedef struct {
    /* Unkstruct_14c8a930: P3.40 T3 band rank 2764; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x51];
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ u8 pad76[0x86];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017D598_5; /* size = 0x100 */

typedef struct {
    /* Unkstruct_8b0cdd5c: P3.40 T3 band rank 2973; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ u32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ u32 unk1C;
} Unkstruct_80184BFC;
typedef Unkstruct_80184BFC Unkstruct_80185434; /* size = 0x20 */

typedef struct {
    /* Unkstruct_15054509: P3.40 T3 band rank 2767; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x174];
    /* 0x0198 */ s32 unk198;
    /* 0x019c */ u8 pad19C[0x70];
    /* 0x020c */ s16 unk20C;
    /* 0x020e */ u8 pad20E[0x6];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8017F344; /* size = 0x218 */

typedef struct {
    /* Unkstruct_17ee67a6: P3.40 T3 band rank 2771; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0xb];
    /* 0x0027 */ s8 unk27;
    /* 0x0028 */ u8 pad28[0x4];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801AC150_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_1e0cf8ee: P3.40 T3 band rank 2780; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 unkC;
    /* 0x000d */ u8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_800153A4; /* size = 0x10 */

typedef struct {
    /* Unkstruct_2026a04c: P3.40 T3 band rank 2784; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4c];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
    /* 0x0054 */ u8 pad54[0xc];
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u8 pad62[0x2];
    /* 0x0064 */ u16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_800CB4C8; /* size = 0x68 */

typedef struct {
    /* Unkstruct_2667501c: P3.40 T3 band rank 2792; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017F2B4; /* size = 0x24 */

typedef struct {
    /* Unkstruct_278aede7: P3.40 T3 band rank 2795; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_8018C7A8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_288e6d45: P3.40 T3 band rank 2798; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x60];
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u8 pad62[0x36];
    /* 0x0098 */ u16 unk98;
    /* 0x009a */ u8 pad9A[0x28];
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 padC3[0x3d];
    /* 0x0100 */ u16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801810AC; /* size = 0x104 */

typedef struct {
    /* Unkstruct_2c9cb8d9: P3.40 T3 band rank 2805; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017F078; /* size = 0x20 */

typedef struct {
    /* Unkstruct_2d747139: P3.40 T3 band rank 2806; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xe];
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x50];
    /* 0x0074 */ s32 unk74;
} Unkstruct_8001CA88; /* size = 0x78 */

typedef struct {
    /* Unkstruct_2edb2408: P3.40 T3 band rank 2808; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_80180ED0; /* size = 0x24 */

typedef struct {
    /* Unkstruct_2f31d813: P3.40 T3 band rank 2809; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0xe];
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x52];
    /* 0x0080 */ s32 unk80;
} Unkstruct_801800CC_2; /* size = 0x84 */

typedef struct {
    /* Unkstruct_30b49842: P3.40 T3 band rank 2810; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xde];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801854B8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_353d5d4f: P3.40 T3 band rank 2815; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xa];
    /* 0x002a */ u16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801AB694; /* size = 0x30 */

typedef struct {
    /* Unkstruct_39e68e03: P3.40 T3 band rank 2822; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB0C8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_3a857fa6: P3.40 T3 band rank 2823; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ u32 unk14;
} Unkstruct_800273F4; /* size = 0x18 */


typedef Unkstruct_801202A0 Unkstruct_8017C2B0_4; /* size = 0x60 */

typedef Unkstruct_80182550_2 Unkstruct_80183560_2; /* size = 0x10c */

typedef Unkstruct_801E2EC0 Unkstruct_801E8428; /* size = 0x38 */

typedef struct {
    /* Unkstruct_4b39a0f4: P3.40 T3 band rank 2847; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x10];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x4f];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x1a];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8017DC8C; /* size = 0xe0 */

typedef Unkstruct_801800CC_2 Unkstruct_801825A4_2; /* size = 0x84 */

typedef struct {
    /* Unkstruct_4cbb5c29: P3.40 T3 band rank 2849; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ union {
        s16 s;
        u16 u;
    } unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ union {
        s16 s;
        u16 u;
    } unk5C;
    /* 0x005e */ u8 pad5E[0x1a];
    /* 0x0078 */ union {
        s32 s;
        u32 u;
    } unk78;
    /* 0x007c */ u8 pad7C[0x48];
    /* 0x00c4 */ union {
        s32 s;
        u32 u;
    } unkC4;
    /* 0x00c8 */ u8 padC8[0x18];
    /* 0x00e0 */ union {
        s32 s;
        u32 u;
    } unkE0;
} Unkstruct_80182AD4; /* size = 0xe4 */

typedef Unkstruct_80184BFC Unkstruct_8018F734; /* size = 0x20 */

typedef struct {
    /* Unkstruct_4ea2930d: P3.40 T3 band rank 2855; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u32 unk2C;
} Unkstruct_800CB378; /* size = 0x30 */

typedef Unkstruct_800B5BD8 Unkstruct_801885D0; /* size = 0x20 */

typedef struct {
    /* Unkstruct_4f24b87e: P3.40 T3 band rank 2857; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0xc];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
} Unkstruct_800CB8A4_3; /* size = 0x50 */


typedef struct {
    /* Unkstruct_55311fdb: P3.40 T3 band rank 2863; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801AC940; /* size = 0x30 */

typedef struct {
    /* Unkstruct_59b0a062: P3.40 T3 band rank 2872; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x6];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
} Unkstruct_801859B4; /* size = 0x28 */

typedef struct {
    /* Unkstruct_5b98b1dd: P3.40 T3 band rank 2874; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80184688; /* size = 0x24 */

typedef Unkstruct_8011D030 Unkstruct_8017CFBC_3; /* size = 0x34 */

typedef struct {
    /* Unkstruct_5d4eadbe: P3.40 T3 band rank 2878; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8018111C_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_5dafd04b: P3.40 T3 band rank 2882; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0xa];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CB328_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_5ff9e059: P3.40 T3 band rank 2884; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80185810_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_64c6fe56: P3.40 T3 band rank 2886; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x28];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8018CCF8; /* size = 0x30 */

typedef struct {
    /* Unkstruct_687fa610: P3.40 T3 band rank 2890; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017F14C; /* size = 0x10 */

typedef Unkstruct_801202A0 Unkstruct_80183B14; /* size = 0x10c */

typedef struct {
    /* Unkstruct_6e783f7c: P3.40 T3 band rank 2897; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x108];
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ s16 unk10A;
    /* 0x010c */ s16 unk10C;
    /* 0x010e */ u16 unk10E;
    /* 0x0110 */ u16 unk110;
    /* 0x0112 */ u16 unk112;
} Unkstruct_801832BC_2; /* size = 0x114 */

typedef struct {
    /* Unkstruct_737898eb: P3.40 T3 band rank 2901; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8018734C; /* size = 0x1c */

typedef struct {
    /* Unkstruct_78f32c76: P3.40 T3 band rank 2907; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0xaa];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x8];
    /* 0x00ec */ s32 unkEC;
    /* 0x00f0 */ u8 padF0[0xe];
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_8017EF04; /* size = 0x104 */

typedef struct {
    /* Unkstruct_7b92efc1: P3.40 T3 band rank 2910; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_801A876C; /* size = 0x1c */

typedef struct {
    /* Unkstruct_7f17f0a9: P3.40 T3 band rank 2914; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_801838CC; /* size = 0x24 */

typedef struct {
    /* Unkstruct_800CBF3C: P3.40 T3 band rank 2915; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ s32 unkC;
} Unkstruct_800CAE74; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8012A1BC: P3.40 T3 band rank 2917; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80182D54; /* size = 0x18 */

typedef struct {
    /* Unkstruct_80a5dc64: P3.40 T3 band rank 2959; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xb8];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0xc];
    /* 0x00ec */ s32 unkEC;
} Unkstruct_8017ECE0; /* size = 0xf0 */

typedef struct {
    /* Unkstruct_81cc2737: P3.40 T3 band rank 2961; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_801851CC; /* size = 0x1c */

typedef struct {
    /* Unkstruct_820ad584: P3.40 T3 band rank 2962; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CB328_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_88afa2ba: P3.40 T3 band rank 2968; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x51];
    /* 0x0075 */ u8 unk75;
    /* 0x0076 */ u8 pad76[0x46];
    /* 0x00bc */ s32 unkBC;
    /* 0x00c0 */ u8 unkC0;
    /* 0x00c1 */ u8 padC1[0x3];
    /* 0x00c4 */ s32 unkC4;
} Unkstruct_8017E960; /* size = 0xc8 */

typedef struct {
    /* Unkstruct_8adeadb7: P3.40 T3 band rank 2972; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x10];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u8 pad62[0x2];
} Unkstruct_800CD204; /* size = 0x64 */

typedef struct {
    /* Unkstruct_945c3e10: P3.40 T3 band rank 2979; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x7c];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1e];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_801820B0; /* size = 0x100 */

typedef struct {
    /* Unkstruct_94bda052: P3.40 T3 band rank 2980; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0xc8];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_801AE060; /* size = 0x100 */

typedef struct {
    /* Unkstruct_94c3a162: P3.40 T3 band rank 2981; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017F24C; /* size = 0x38 */

typedef Unkstruct_8011DB30 Unkstruct_80187E60; /* size = 0x30 */

typedef struct {
    /* Unkstruct_9b563bf6: P3.40 T3 band rank 2987; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x25];
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 pad26[0x1];
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u8 pad28[0x1];
    /* 0x0029 */ u8 unk29;
    /* 0x002a */ u8 pad2A[0x2];
} Unkstruct_8017DC80; /* size = 0x2c */

typedef Unkstruct_801312D0 Unkstruct_8017E878_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_9ffa9490: P3.40 T3 band rank 2991; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3];
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u16 unk2A;
} Unkstruct_801818B8; /* size = 0x2c */

typedef Unkstruct_801818B8 Unkstruct_801819C0; /* size = 0x2c */

typedef struct {
    /* Unkstruct_a6ec58b7: P3.40 T3 band rank 2999; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018B8CC; /* size = 0x24 */

typedef Unkstruct_801875F8 Unkstruct_8018A2A0; /* size = 0xc */

typedef struct {
    /* Unkstruct_650c46f9: P3.40 T17 drift rank 29; 42 TNC sites in 1 bodies; struct map 42 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80191C50; /* size = 0x100 */

typedef struct {
    /* Unkstruct_adca0010: P3.40 T3 band rank 3009; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80180450_4; /* size = 0x20 */

typedef Unkstruct_801E2EC0 Unkstruct_801EE2B0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_b37ce79c: P3.40 T3 band rank 3014; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8018516C; /* size = 0x1c */

typedef Unkstruct_801E2E24 Unkstruct_801EFC94; /* size = 0x38 */

typedef struct {
    /* Unkstruct_bdf1e3ba: P3.40 T3 band rank 3026; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0xa];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8017E4D8; /* size = 0x20 */

typedef Unkstruct_801833D4 Unkstruct_80182C98_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_c5271182: P3.40 T3 band rank 3032; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x22];
    /* 0x0058 */ u32 unk58;
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8017F588; /* size = 0x60 */

typedef Unkstruct_8011D030 Unkstruct_8016829C; /* size = 0x38 */

typedef Unkstruct_801202A0 Unkstruct_80182ED4; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_c9d020b8: P3.40 T3 band rank 3038; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x9c];
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_80189268; /* size = 0x108 */

typedef struct {
    /* Unkstruct_cd1f888a: P3.40 T3 band rank 3043; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018BD14; /* size = 0x24 */

typedef struct {
    /* Unkstruct_cd32434f: P3.40 T3 band rank 3044; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s8 unkC;
    /* 0x000d */ s8 unkD;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80015424; /* size = 0x10 */

typedef struct {
    /* Unkstruct_d1707e96: P3.40 T3 band rank 3048; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_8018247C_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_d535e550: P3.40 T3 band rank 3052; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80185264; /* size = 0x1c */

typedef struct {
    /* Unkstruct_d5c57508: P3.40 T3 band rank 3053; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0xa];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CB1EC_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_d8201f14: P3.40 T3 band rank 3056; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ u16 unkCC;
    /* 0x00ce */ u16 unkCE;
    /* 0x00d0 */ u16 unkD0;
    /* 0x00d2 */ u8 padD2[0x2];
    /* 0x00d4 */ u16 unkD4;
    /* 0x00d6 */ u16 unkD6;
    /* 0x00d8 */ u16 unkD8;
    /* 0x00da */ u8 padDA[0x2];
} Unkstruct_8018A2D0_2; /* size = 0xdc */

typedef struct {
    /* Unkstruct_de89d80a: P3.40 T3 band rank 3063; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8017F214; /* size = 0x1c */

typedef struct {
    /* Unkstruct_dfdfde9f: P3.40 T3 band rank 3066; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017E3A0; /* size = 0x14 */

typedef Unkstruct_801E2F08 Unkstruct_801EFD70; /* size = 0x38 */

typedef struct {
    /* Unkstruct_e12c5c19: P3.40 T3 band rank 3069; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_801876EC_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_e273c072: P3.40 T3 band rank 3071; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x2];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017E1E8_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_e844d065: P3.40 T3 band rank 3077; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x44];
    /* 0x004c */ s16 unk4C;
    /* 0x004e */ u8 pad4E[0x2];
    /* 0x0050 */ u32 unk50;
} Unkstruct_8017F074; /* size = 0x54 */

typedef struct {
    /* Unkstruct_f3089bef: P3.40 T3 band rank 3086; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x74];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x1];
    /* 0x0076 */ s16 unk76;
} Unkstruct_80185BD8; /* size = 0x78 */

typedef struct {
    /* Unkstruct_f52b8157: P3.40 T3 band rank 3087; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_801AE624; /* size = 0x24 */

typedef struct {
    /* Unkstruct_f919dad4: P3.40 T3 band rank 3088; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017F630; /* size = 0x74 */

typedef Unkstruct_8011D030 Unkstruct_8017CFBC_4; /* size = 0x34 */

typedef struct {
    /* Unkstruct_fd6a380f: P3.40 T3 band rank 3100; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80182CA4_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_fe9c11cd: P3.40 T3 band rank 3103; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xe0];
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u16 unk106;
} Unkstruct_8017FE38; /* size = 0x108 */


typedef struct {
    /* Unkstruct_1d21d285: P3.40 T3 band rank 3106; 5 TNC sites in 5 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x44];
    /* 0x0044 */ u32 unk44;
} Unkstruct_800CAF88; /* size = 0x48 */

typedef struct {
    /* Unkstruct_b5e86a9c: P3.40 T3 band rank 3121; 5 TNC sites in 5 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801803DC; /* size = 0x18 */

typedef struct {
    /* Unkstruct_d0dadbb5: P3.40 T3 band rank 3123; 5 TNC sites in 5 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801803DC_2; /* size = 0x24 */

typedef Unkstruct_801202A0 Unkstruct_801834A0; /* size = 0x4 */

typedef struct {
    /* Unkstruct_ed5bd925: P3.40 T3 band rank 3127; 5 TNC sites in 5 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017FB8C_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_2947a81f: P3.40 T3 band rank 3129; 5 TNC sites in 3 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x10];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u8 pad62[0x2];
} Unkstruct_800CCD2C_2; /* size = 0x64 */

typedef struct {
    /* Unkstruct_54a669d1: P3.40 T3 band rank 3130; 5 TNC sites in 3 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
} Unkstruct_801A7C58; /* size = 0x4 */

typedef struct {
    /* Unkstruct_592f8ab5: P3.40 T3 band rank 3131; 5 TNC sites in 3 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xac];
    /* 0x00d0 */ void * unkD0;
    /* 0x00d4 */ u8 padD4[0xe];
    /* 0x00e2 */ s16 unkE2;
} Unkstruct_80182AF8; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_9b1bacb5: P3.40 T3 band rank 3139; 5 TNC sites in 3 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x6];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CB164; /* size = 0x24 */

typedef struct {
    /* Unkstruct_40a8e0e1: P3.40 T3 band rank 3141; 5 TNC sites in 2 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x3c];
    /* 0x004c */ void * unk4C;
} Unkstruct_800CC298; /* size = 0x50 */

typedef struct { SVECTOR x, y; } Pair16;

typedef struct {
    /* Unkstruct_9ed7beb4: P3.40 T3 band rank 3148; 5 TNC sites in 2 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x6c];
    /* 0x0090 */ s32 unk90;
} Unkstruct_80180EEC; /* size = 0x94 */

typedef struct {
    /* Unkstruct_e8d48208: P3.40 T3 band rank 3152; 5 TNC sites in 2 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8013D53C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_00085363: P3.40 T3 band rank 3153; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x38];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x63];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x42];
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_801887D0; /* size = 0x108 */

typedef struct {
    /* Unkstruct_000c77ef: P3.40 T3 band rank 3154; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
} Unkstruct_8018576C; /* size = 0xc */

typedef Unkstruct_801813B4_2 Unkstruct_80188C04_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_01a4b183: P3.40 T3 band rank 3156; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ u32 unk18;
    /* 0x001c */ u8 pad1C[0xc4];
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x6];
    /* 0x00e8 */ u32 unkE8;
} Unkstruct_801827A8; /* size = 0xec */

typedef struct {
    /* Unkstruct_77e65138: P3.40 T3 band rank 3317; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ void * unk0;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x6];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017E2C0;
typedef Unkstruct_8017E2C0 Unkstruct_8017F9D0; /* size = 0x18 */

typedef struct {
    /* Unkstruct_06760bbe: P3.40 T3 band rank 3164; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x8];
    /* 0x001c */ s32 unk1C;
} Unkstruct_800CB634; /* size = 0x20 */


typedef struct {
    /* Unkstruct_4df42b00: P3.40 T3 band rank 3267; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0xa];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u32 unk18;
} Unkstruct_8017DB28_2;
typedef Unkstruct_8017DB28_2 Unkstruct_8017E97C; /* size = 0x1c */

typedef struct {
    /* Unkstruct_09403b25: P3.40 T3 band rank 3169; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3];
    /* 0x0027 */ u8 unk27;
    /* 0x0028 */ s16 unk28;
    /* 0x002a */ s16 unk2A;
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017FC34_5; /* size = 0x30 */

typedef struct {
    /* Unkstruct_0964567e: P3.40 T3 band rank 3170; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801F0A98; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_0a3b8fb3: P3.40 T3 band rank 3172; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_801827DC_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_0bd942fd: P3.40 T3 band rank 3175; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x5a];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x62];
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 padC3[0x1];
} Unkstruct_801932EC; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_0bf0fd65: P3.40 T3 band rank 3177; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0xa];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_801ABEE0_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_0d29af53: P3.40 T3 band rank 3179; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801A6184; /* size = 0x24 */

typedef struct {
    /* Unkstruct_0e97d5c4: P3.40 T3 band rank 3182; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x2c];
    /* 0x0050 */ s32 unk50;
} Unkstruct_800CB300_2; /* size = 0x54 */

typedef struct {
    /* Unkstruct_0f85b744: P3.40 T3 band rank 3184; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ s32 unkE0;
} Unkstruct_8017FC04; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_97bd88b6: P3.40 T3 band rank 3395; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3e];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x62];
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 unkC3;
} Unkstruct_80180A98;
typedef Unkstruct_80180A98 Unkstruct_80186E94; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_13548020: P3.40 T3 band rank 3191; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
} Unkstruct_800CB188; /* size = 0x50 */

typedef Unkstruct_8017E2C0 Unkstruct_80183CF0; /* size = 0x18 */

typedef Unkstruct_8017DB28_2 Unkstruct_8017E6EC_3; /* size = 0x1c */

typedef Unkstruct_801813B4_2 Unkstruct_8018BED0_2; /* size = 0x8 */

typedef Unkstruct_800B5BD8 Unkstruct_8017D890_3; /* size = 0x1c */

typedef Unkstruct_8017DB28_2 Unkstruct_8017F40C; /* size = 0x1c */

typedef Unkstruct_801202A0 Unkstruct_80132018_3; /* size = 0x100 */

typedef struct {
    /* Unkstruct_1ff6c6a0: P3.40 T3 band rank 3217; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017DD28; /* size = 0x14 */

typedef struct {
    /* Unkstruct_22ed7750: P3.40 T3 band rank 3219; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x204];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ s32 unk208;
    /* 0x020c */ u8 unk20C;
    /* 0x020d */ u8 unk20D;
    /* 0x020e */ u8 pad20E[0x6];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8018141C; /* size = 0x218 */

typedef struct {
    /* Unkstruct_248a6c74: P3.40 T3 band rank 3222; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0xf0];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80180ECC; /* size = 0x100 */


typedef struct {
    /* Unkstruct_34a5d46a: P3.40 T3 band rank 3236; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801ABC04; /* size = 0x24 */

typedef Unkstruct_801202A0 Unkstruct_80180C00; /* size = 0x100 */

typedef struct {
    /* Unkstruct_37951245: P3.40 T3 band rank 3240; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ Unkstruct_801E5338 *unk20;
} Unkstruct_801E5338_2; /* size = 0x24 */


typedef struct {
    /* Unkstruct_386f55d9: P3.40 T3 band rank 3242; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8001D3FC_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_3b6a6a74: P3.40 T3 band rank 3245; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017F0E0; /* size = 0x20 */

typedef struct {
    /* Unkstruct_3cfde9ef: P3.40 T3 band rank 3247; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x68];
    /* 0x0074 */ u8 unk74;
    /* 0x0075 */ u8 pad75[0x15];
    /* 0x008a */ u16 unk8A;
    /* 0x008c */ u8 pad8C[0x72];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017E394_3; /* size = 0x100 */

typedef struct {
    /* Unkstruct_3d19880a: P3.40 T3 band rank 3248; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017ECEC_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_3e929cb7: P3.40 T3 band rank 3249; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x58];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x22];
    /* 0x008a */ u16 unk8A;
} Unkstruct_80180AA0; /* size = 0x8c */

typedef struct {
    /* Unkstruct_42273ff6: P3.40 T3 band rank 3254; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017D910; /* size = 0x20 */

typedef struct {
    /* Unkstruct_4c9d1668: P3.40 T3 band rank 3265; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_800CB188_2; /* size = 0x8 */

typedef Unkstruct_801202A0 Unkstruct_80183258; /* size = 0x10c */

typedef struct {
    /* Unkstruct_562eedd9: P3.40 T3 band rank 3272; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s16 unk20;
    /* 0x0022 */ s16 unk22;
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x2];
} Unkstruct_801853D0_2; /* size = 0x28 */

typedef struct {
    /* Unkstruct_56d5744a: P3.40 T3 band rank 3274; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u16 unk1E;
    /* 0x0020 */ u8 pad20[0x4];
    /* 0x0024 */ u16 unk24;
    /* 0x0026 */ u16 unk26;
    /* 0x0028 */ u8 pad28[0xa];
    /* 0x0032 */ u16 unk32;
} Unkstruct_800D27A0; /* size = 0x34 */

typedef struct {
    /* Unkstruct_56f2aa26: P3.40 T3 band rank 3275; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0xa];
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x8];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017DE30; /* size = 0x100 */

typedef Unkstruct_8017E2C0 Unkstruct_801809F0; /* size = 0x18 */

typedef struct {
    /* Unkstruct_5787cd64: P3.40 T3 band rank 3278; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_80188D78; /* size = 0x20 */

typedef struct {
    /* Unkstruct_584ff74e: P3.40 T3 band rank 3279; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xec];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8018C454_2; /* size = 0x100 */

typedef Unkstruct_801202A0 Unkstruct_80180CAC; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_66a23e7d: P3.40 T3 band rank 3292; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0xa];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0xc4];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x2];
    /* 0x00e2 */ s16 unkE2;
} Unkstruct_80180E00; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_6cb9ada2: P3.40 T3 band rank 3302; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x2e];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017E5D4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_6fdf368a: P3.40 T3 band rank 3304; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80180AA4; /* size = 0x14 */

typedef Dst Unkstruct_801596F0_4; /* size = 0x2c */

typedef struct {
    /* Unkstruct_7203b7b0: P3.40 T3 band rank 3308; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x10];
    /* 0x0030 */ s32 unk30;
} Unkstruct_8018071C; /* size = 0x34 */

typedef Unkstruct_801813B4_2 Unkstruct_8018478C_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_74b74e73: P3.40 T3 band rank 3313; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
} Unkstruct_800CD0CC; /* size = 0x50 */

typedef struct {
    /* Unkstruct_76b8a5d3: P3.40 T3 band rank 3315; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80182384; /* size = 0x38 */

typedef Unkstruct_80180A98 Unkstruct_80186928; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_79ddd9e8: P3.40 T3 band rank 3322; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80182318; /* size = 0x38 */

typedef struct {
    /* Unkstruct_7b347afe: P3.40 T3 band rank 3323; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xbc];
    /* 0x00e0 */ u16 unkE0;
    /* 0x00e2 */ u16 unkE2;
} Unkstruct_8017E850; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_7c5094c5: P3.40 T3 band rank 3326; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801E56A8; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_80191908: P3.40 T3 band rank 3367; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_80188FB4; /* size = 0x10 */

typedef Unkstruct_8017E2C0 Unkstruct_8018043C; /* size = 0x18 */

typedef struct {
    /* Unkstruct_8790010b: P3.40 T3 band rank 3374; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x4];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x46];
    /* 0x00ae */ s16 unkAE;
    /* 0x00b0 */ u8 padB0[0x11];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_8017D5E4; /* size = 0xc4 */


typedef Unkstruct_80185020 Unkstruct_80182C98_3; /* size = 0x18 */

typedef Unkstruct_801F0A98 Unkstruct_801F24DC; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_89f3c0a1: P3.40 T3 band rank 3381; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
} Unkstruct_801809BC_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_91c0cc97: P3.40 T3 band rank 3386; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x10];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ u8 pad62[0x2];
} Unkstruct_800CD708; /* size = 0x64 */

typedef struct {
    /* Unkstruct_947b31a5: P3.40 T3 band rank 3390; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x14];
    /* 0x0024 */ s32 unk24;
    /* 0x0028 */ s32 unk28;
    /* 0x002c */ s32 unk2C;
} Unkstruct_8017E18C_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_950d0e26: P3.40 T3 band rank 3392; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80184688_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_9937d42a: P3.40 T3 band rank 3396; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_801834E4_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_9a119754: P3.40 T3 band rank 3400; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xaa];
    /* 0x00aa */ u16 unkAA;
    /* 0x00ac */ u16 unkAC;
    /* 0x00ae */ u8 padAE[0x84];
    /* 0x0132 */ u16 unk132;
    /* 0x0134 */ u8 pad134[0xd0];
    /* 0x0204 */ s32 unk204;
} Unkstruct_801836C8; /* size = 0x208 */

typedef Unkstruct_8011D030 Unkstruct_8016D688_4; /* size = 0x34 */

typedef struct {
    /* Unkstruct_9cdc8f80: P3.40 T3 band rank 3407; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xda];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_801A4060; /* size = 0x100 */

typedef struct {
    /* Unkstruct_9f395546: P3.40 T3 band rank 3411; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801831A8_3; /* size = 0xd0 */

typedef Unkstruct_8017E2C0 Unkstruct_80183644; /* size = 0x18 */

typedef struct {
    /* Unkstruct_a24cd7d8: P3.40 T3 band rank 3415; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x188];
    /* 0x0198 */ s32 unk198;
    /* 0x019c */ u8 pad19C[0x70];
    /* 0x020c */ u8 unk20C;
    /* 0x020d */ u8 pad20D[0x3];
} Unkstruct_80183C9C; /* size = 0x210 */

typedef Unkstruct_8001C9D0 Unkstruct_8018BC10_2; /* size = 0x20 */

typedef Unkstruct_801202A0 Unkstruct_801424E4_3; /* size = 0x38 */

typedef Unkstruct_8017E2C0 Unkstruct_80180B98; /* size = 0x18 */

typedef struct {
    /* Unkstruct_abf3a4be: P3.40 T3 band rank 3426; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ u16 unk38;
    /* 0x003a */ u8 pad3A[0x2];
} Unkstruct_8017DC50_2; /* size = 0x3c */

typedef struct {
    /* Unkstruct_ae2cc4af: P3.40 T3 band rank 3433; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x94];
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u16 unkBA;
    /* 0x00bc */ u8 padBC[0x148];
    /* 0x0204 */ u32 unk204;
} Unkstruct_80182964; /* size = 0x208 */

typedef struct {
    /* Unkstruct_af3b1792: P3.40 T3 band rank 3437; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB76C_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_af53763d: P3.40 T3 band rank 3438; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8017F3D8; /* size = 0x1c */

typedef struct {
    /* Unkstruct_b1470eeb: P3.40 T3 band rank 3442; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ void * unkD0;
    /* 0x00d4 */ void * unkD4;
    /* 0x00d8 */ u8 padD8[0x10];
    /* 0x00e8 */ s32 unkE8;
} Unkstruct_80186178; /* size = 0xec */

typedef Unkstruct_800B5BD8 Unkstruct_8016DF5C_9; /* size = 0x38 */

typedef struct {
    /* Unkstruct_b99cd632: P3.40 T3 band rank 3452; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x10];
    /* 0x0060 */ u16 unk60;
    /* 0x0062 */ u8 pad62[0x2];
} Unkstruct_800CCC54; /* size = 0x64 */

typedef Unkstruct_801813B4_2 Unkstruct_8018B028_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_bc0f6f4f: P3.40 T3 band rank 3456; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017EE78; /* size = 0x20 */

typedef struct {
    /* Unkstruct_bd4679d7: P3.40 T3 band rank 3461; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801EAC10; /* size = 0xe8 */

typedef Unkstruct_8017DB28_2 Unkstruct_8017E368; /* size = 0x1c */

typedef Unkstruct_8011DB30 Unkstruct_801885D0_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_c015526a: P3.40 T3 band rank 3468; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_801860F4; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_c0f3e4d0: P3.40 T3 band rank 3469; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8018C4BC; /* size = 0x38 */

typedef struct {
    /* Unkstruct_c1510931: P3.40 T3 band rank 3470; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ s32 unk24;
} Unkstruct_80185A5C; /* size = 0x28 */

typedef struct {
    /* Unkstruct_c3918604: P3.40 T3 band rank 3472; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_801886C4; /* size = 0x60 */

typedef struct {
    /* Unkstruct_c7b1d556: P3.40 T3 band rank 3477; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x44];
    /* 0x004c */ s16 unk4C;
    /* 0x004e */ u8 pad4E[0x2];
    /* 0x0050 */ s32 unk50;
} Unkstruct_80180C34; /* size = 0x54 */

typedef struct {
    /* Unkstruct_c9a26682: P3.40 T3 band rank 3478; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
} Unkstruct_8001EFE0_2; /* size = 0xc */


typedef struct {
    /* Unkstruct_cb379f4d: P3.40 T3 band rank 3481; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800193B8; /* size = 0x24 */


typedef struct {
    /* Unkstruct_cf755340: P3.40 T3 band rank 3487; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x12];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_801822DC; /* size = 0x74 */

typedef struct {
    /* Unkstruct_d0ff3d46: P3.40 T3 band rank 3491; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
} Unkstruct_8017D77C_3; /* size = 0xc */

typedef Unkstruct_8011D030 Unkstruct_8017C218_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_d46eb2c9: P3.40 T3 band rank 3496; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB458; /* size = 0x38 */

typedef Unkstruct_8017E2C0 Unkstruct_80181C5C; /* size = 0x18 */

typedef struct {
    /* Unkstruct_da2f5cf8: P3.40 T3 band rank 3505; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017F418; /* size = 0x38 */

typedef struct {
    /* Unkstruct_da32ed4e: P3.40 T3 band rank 3506; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ void * unkC;
    /* 0x0010 */ u8 pad10[0x54];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017BEBC_5; /* size = 0x68 */

typedef struct {
    /* Unkstruct_de13e7fb: P3.40 T3 band rank 3512; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ s32 unk34;
} Unkstruct_801819D0_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_dff45fd8: P3.40 T3 band rank 3517; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ u16 unk1A;
    /* 0x001c */ u8 pad1C[0x2];
    /* 0x001e */ u16 unk1E;
    /* 0x0020 */ u8 pad20[0x2];
    /* 0x0022 */ u16 unk22;
} Unkstruct_80025A30; /* size = 0x24 */

typedef struct {
    /* Unkstruct_e2304715: P3.40 T3 band rank 3519; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x18];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8001D388; /* size = 0x24 */

typedef Unkstruct_800B5BD8 Unkstruct_8016BD78_6; /* size = 0x1c */

typedef struct {
    /* Unkstruct_e493ef8f: P3.40 T3 band rank 3524; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x6];
    /* 0x0010 */ s32 unk10;
} Unkstruct_8017E400; /* size = 0x14 */

typedef struct {
    /* Unkstruct_e4c46ce0: P3.40 T3 band rank 3526; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017EE10; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ef2ae244: P3.40 T3 band rank 3535; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ u8 padDE[0x2];
} Unkstruct_801815D4; /* size = 0xe0 */

typedef Unkstruct_8011D030 Unkstruct_8017D030_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_f751ba61: P3.40 T3 band rank 3545; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80181EEC_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_f8a83823: P3.40 T3 band rank 3547; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80023570; /* size = 0x30 */

typedef struct {
    /* Unkstruct_fa29d073: P3.40 T3 band rank 3550; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8018865C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_ff671667: P3.40 T3 band rank 3556; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x24];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017EA18; /* size = 0x30 */

typedef struct {
    /* Unkstruct_02d62862: P3.40 T3 band rank 3557; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017FBB4; /* size = 0x24 */

typedef struct {
    /* Unkstruct_25c3095b: P3.40 T3 band rank 3563; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80135480_8; /* size = 0x4 */

typedef Unkstruct_80126B58 Unkstruct_80174384; /* size = 0x218 */

typedef struct {
    /* Unkstruct_379ed340: P3.40 T3 band rank 3565; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017E9F4_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_3eab7557: P3.40 T3 band rank 3567; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80180450_5; /* size = 0x14 */

typedef Unkstruct_801202A0 Unkstruct_801312D0_6; /* size = 0xc0 */

typedef struct {
    /* Unkstruct_631ea0bd: P3.40 T3 band rank 3570; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017E294; /* size = 0x4 */

typedef struct {
    /* Unkstruct_6fc6ef3c: P3.40 T3 band rank 3573; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017EAFC_2; /* size = 0x4 */

typedef Unkstruct_801202A0 Unkstruct_80130D0C_2; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_8803b9d7: P3.40 T3 band rank 3581; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017D994_3; /* size = 0x14 */

typedef Unkstruct_801823B8_2 Unkstruct_801823B8_3; /* size = 0x28 */

typedef Unkstruct_80135480_8 Unkstruct_80135480_9; /* size = 0x4 */

typedef struct {
    /* Unkstruct_ca52e31b: P3.40 T3 band rank 3591; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_801E5514; /* size = 0x8 */

typedef struct {
    /* Unkstruct_caeb4a5e: P3.40 T3 band rank 3592; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xf8];
    /* 0x00f8 */ void * unkF8;
} Unkstruct_801869F8; /* size = 0xfc */

typedef struct {
    /* Unkstruct_cb07ad3c: P3.40 T3 band rank 3593; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8015C128_5; /* size = 0x14 */

typedef struct {
    /* Unkstruct_cd595245: P3.40 T3 band rank 3594; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd4];
    /* 0x00d4 */ s32 unkD4;
} Unkstruct_8017D9B8; /* size = 0xd8 */

typedef struct {
    /* Unkstruct_df9d0da2: P3.40 T3 band rank 3595; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80180814_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_e5f99106: P3.40 T3 band rank 3598; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8018BAE0; /* size = 0x4 */

typedef struct {
    /* Unkstruct_e9fe9e30: P3.40 T3 band rank 3599; 4 TNC sites in 4 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017FBB4_2; /* size = 0x14 */

typedef Unkstruct_801202A0 Unkstruct_8017E520_4; /* size = 0x68 */

typedef struct {
    /* Unkstruct_77442f03: P3.40 T3 band rank 3606; 4 TNC sites in 3 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x12];
    /* 0x0014 */ u32 unk14;
} Unkstruct_80037F3C; /* size = 0x18 */

typedef struct {
    /* Unkstruct_9a78fa6d: P3.40 T3 band rank 3609; 4 TNC sites in 3 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0xa];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017BEBC_6; /* size = 0x14 */


typedef struct {
    /* Unkstruct_03e804ef: P3.40 T3 band rank 3615; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x28];
    /* 0x0028 */ s32 unk28;
} Unkstruct_80180F5C; /* size = 0x2c */

typedef struct {
    /* Unkstruct_1cd2a1e2: P3.40 T3 band rank 3625; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017D174; /* size = 0x14 */

typedef struct {
    /* Unkstruct_1e09f915: P3.40 T3 band rank 3626; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
    /* 0x0068 */ u8 pad68[0xa0];
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_801805D4; /* size = 0x10c */

typedef struct {
    /* Unkstruct_2573ca2c: P3.40 T3 band rank 3630; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017CF5C; /* size = 0x2c */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_7; /* size = 0x68 */

typedef struct {
    /* Unkstruct_3b885203: P3.40 T3 band rank 3634; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0xa];
    /* 0x0014 */ void *unk14;
} Unkstruct_801809A8; /* size = 0x18 */

typedef struct {
    /* Unkstruct_3eff16be: P3.40 T3 band rank 3636; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ void * unk8;
} Unkstruct_8017F2A0_3; /* size = 0xc */

typedef struct {
    /* Unkstruct_4c920d67: P3.40 T3 band rank 3642; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017E630; /* size = 0x20 */

typedef struct {
    /* Unkstruct_524bbf00: P3.40 T3 band rank 3646; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ u8 pad50[0x12];
    /* 0x0062 */ u16 unk62;
} Unkstruct_800CB10C; /* size = 0x64 */

typedef struct {
    /* Unkstruct_53a34532: P3.40 T3 band rank 3647; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8018101C; /* size = 0x2c */


typedef struct {
    /* Unkstruct_5468ced6: P3.40 T3 band rank 3649; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x60];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017CD9C_4; /* size = 0x68 */

typedef struct {
    /* Unkstruct_5ba3efa9: P3.40 T3 band rank 3653; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x60];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017D174_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_60610e02: P3.40 T3 band rank 3655; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017EE74; /* size = 0x100 */

typedef struct {
    /* Unkstruct_60e5e941: P3.40 T3 band rank 3656; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_80181BB4_2; /* size = 0x60 */

typedef struct {
    /* Unkstruct_64340192: P3.40 T3 band rank 3657; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80182398; /* size = 0x18 */

typedef struct {
    /* Unkstruct_dd7b59d3: P3.40 T3 band rank 3846; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x24];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80185E98_2;
typedef Unkstruct_80185E98_2 Unkstruct_80188C28_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_6ec837c3: P3.40 T3 band rank 3663; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
} Unkstruct_8017DB48; /* size = 0x18 */

typedef struct {
    /* Unkstruct_7d47f3ee: P3.40 T3 band rank 3665; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x70];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017E0E0; /* size = 0x74 */

typedef struct {
    /* Unkstruct_80e7fcd8: P3.40 T3 band rank 3807; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018AA70; /* size = 0x24 */

typedef struct {
    /* Unkstruct_85ab7c25: P3.40 T3 band rank 3809; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018CF48_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_92f1ef90: P3.40 T3 band rank 3811; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017F01C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_95db3b13: P3.40 T3 band rank 3812; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80183094_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_a2095936: P3.40 T3 band rank 3817; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8017EDD8; /* size = 0x60 */

typedef struct {
    /* Unkstruct_a82d097a: P3.40 T3 band rank 3819; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80182F48_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_abb80484: P3.40 T3 band rank 3821; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_801879D8; /* size = 0x60 */

typedef struct {
    /* Unkstruct_b03bd9e5: P3.40 T3 band rank 3825; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb];
    /* 0x000b */ u8 unkB;
} Unkstruct_80189A60; /* size = 0xc */

typedef struct {
    /* Unkstruct_b34ff236: P3.40 T3 band rank 3826; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80181B48; /* size = 0x100 */

typedef struct {
    /* Unkstruct_b3ff6c62: P3.40 T3 band rank 3827; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8018C5E8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_c43b4b2c: P3.40 T3 band rank 3834; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xac];
    /* 0x00cc */ void * unkCC;
} Unkstruct_80184C60; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_c488b3d8: P3.40 T3 band rank 3835; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x50];
    /* 0x0060 */ s32 unk60;
} Unkstruct_8017C974; /* size = 0x64 */

typedef struct {
    /* Unkstruct_d2958536: P3.40 T3 band rank 3840; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_801803BC_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_d2cb32e7: P3.40 T3 band rank 3841; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017EAEC_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_d57ac907: P3.40 T3 band rank 3844; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017F3F4; /* size = 0x68 */

typedef struct {
    /* Unkstruct_dc33305f: P3.40 T3 band rank 3845; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017D294; /* size = 0x2c */

typedef struct {
    /* Unkstruct_dfcd0933: P3.40 T3 band rank 3847; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017CCF8_2; /* size = 0x2c */

typedef struct {
    /* Unkstruct_e2f95e1c: P3.40 T3 band rank 3848; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x8];
    /* 0x0014 */ u32 unk14;
    /* 0x0018 */ u8 pad18[0x1c];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80182DCC_2; /* size = 0x38 */

typedef Unkstruct_801202A0 Unkstruct_80181E30; /* size = 0x68 */

typedef struct {
    /* Unkstruct_f1aaa66b: P3.40 T3 band rank 3855; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80186A30; /* size = 0x100 */

typedef struct {
    /* Unkstruct_ffa4e764: P3.40 T3 band rank 3859; 4 TNC sites in 2 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017E7B4_3; /* size = 0x18 */

typedef struct {
    /* Unkstruct_0011fc1c: P3.40 T3 band rank 3860; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x18];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017F0EC_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_0054def0: P3.40 T3 band rank 3862; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x28];
    /* 0x002c */ s32 unk2C;
} Unkstruct_801681FC_4; /* size = 0x30 */

typedef struct {
    /* Unkstruct_02e3b826: P3.40 T3 band rank 3868; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017F138; /* size = 0x20 */

typedef struct {
    /* Unkstruct_05824760: P3.40 T3 band rank 3875; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x84];
    /* 0x0084 */ u16 unk84;
    /* 0x0086 */ u8 pad86[0x2];
} Unkstruct_80180A20; /* size = 0x88 */

typedef Unkstruct_8017FA5C Unkstruct_8017EB7C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_0816dc19: P3.40 T3 band rank 3883; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E2E00; /* size = 0x38 */

typedef struct {
    /* Unkstruct_08325987: P3.40 T3 band rank 3884; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xe6];
    /* 0x010a */ s16 unk10A;
} Unkstruct_80189148; /* size = 0x10c */

typedef Unkstruct_8017EC6C Unkstruct_8017ED40; /* size = 0x2c */

typedef struct {
    /* Unkstruct_7419a2bd: P3.40 T3 band rank 4196; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80181BA8;
typedef Unkstruct_80181BA8 Unkstruct_801849AC;
typedef Unkstruct_801849AC Unkstruct_80185690; /* size = 0x8 */

typedef struct {
    /* Unkstruct_0b51f533: P3.40 T3 band rank 3894; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x6];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x6];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x6];
    /* 0x001c */ u16 unk1C;
    /* 0x001e */ u8 pad1E[0x2];
} Unkstruct_801A5E60; /* size = 0x20 */

typedef Unkstruct_801312D0 Unkstruct_80185E34_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_0bd5033e: P3.40 T3 band rank 3897; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EF734; /* size = 0x38 */

typedef struct {
    /* Unkstruct_0ce14e7a: P3.40 T3 band rank 3901; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0xd4];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0x1c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017D638; /* size = 0x100 */

typedef struct {
    /* Unkstruct_0ce76250: P3.40 T3 band rank 3902; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017F9F4; /* size = 0x30 */

typedef struct {
    /* Unkstruct_0dbba6cf: P3.40 T3 band rank 3904; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
} Unkstruct_8018465C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_0f5929f0: P3.40 T3 band rank 3910; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
} Unkstruct_8017EDA4; /* size = 0x68 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_8; /* size = 0x68 */

typedef Unkstruct_801312D0 Unkstruct_801312D0_7; /* size = 0x8 */

typedef struct {
    /* Unkstruct_14694187: P3.40 T3 band rank 3923; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801A7200_2; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_16cb86e7: P3.40 T3 band rank 3929; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017D788_2; /* size = 0x14 */

typedef Unkstruct_8017FA5C Unkstruct_8017DC70; /* size = 0x68 */

typedef Unkstruct_8017FA5C Unkstruct_8017D604; /* size = 0x68 */

typedef struct {
    /* Unkstruct_1e54af8f: P3.40 T3 band rank 3953; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
} Unkstruct_80188BF8; /* size = 0x68 */

typedef struct {
    /* Unkstruct_1f00ee8f: P3.40 T3 band rank 3955; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_800CB06C; /* size = 0x14 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_9; /* size = 0x68 */

typedef struct {
    /* Unkstruct_206485b6: P3.40 T3 band rank 3959; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ struct Src_80167540 *unk20;
} Unkstruct_800CB2E0; /* size = 0x24 */

typedef struct {
    /* Unkstruct_20cd99be: P3.40 T3 band rank 3962; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0xe];
    /* 0x0014 */ s32 unk14;
} Unkstruct_8018A3C8_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_dd3e0e83: P3.40 T3 band rank 4608; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ u32 unk20;
    /* 0x0024 */ u32 unk24;
    /* 0x0028 */ u32 unk28;
    /* 0x002c */ u32 unk2C;
} Unkstruct_80183438;
typedef Unkstruct_80183438 Unkstruct_80186DCC; /* size = 0x30 */

typedef struct {
    /* Unkstruct_23cb57d8: P3.40 T3 band rank 3971; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x58];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ s16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_801805A0; /* size = 0xc4 */

typedef Unkstruct_8017E654_2 Unkstruct_80186144_2; /* size = 0x30 */

typedef Unkstruct_8017FA5C Unkstruct_8017DC70_2; /* size = 0x68 */

typedef Unkstruct_8017FA5C Unkstruct_8017FB84; /* size = 0x68 */

typedef struct {
    /* Unkstruct_24de9689: P3.40 T3 band rank 3978; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x90];
    /* 0x00b0 */ s32 unkB0;
} Unkstruct_801E5748; /* size = 0xb4 */

typedef Unkstruct_801312D0 Unkstruct_801865DC_2; /* size = 0x8 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_10; /* size = 0x68 */

typedef struct {
    /* Unkstruct_2a54ba0d: P3.40 T3 band rank 3991; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5e];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x4];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x59];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80184404; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_2bb663a3: P3.40 T3 band rank 3994; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x28];
    /* 0x004c */ s32 unk4C;
} Unkstruct_800CCBE4; /* size = 0x50 */

typedef struct {
    /* Unkstruct_2c2f43d1: P3.40 T3 band rank 3995; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xdc];
    /* 0x00e0 */ u16 unkE0;
    /* 0x00e2 */ u8 padE2[0x2];
} Unkstruct_80182614; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_2dcdd89a: P3.40 T3 band rank 3998; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_80189F6C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2de2eb9f: P3.40 T3 band rank 3999; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80181C04; /* size = 0x14 */

typedef struct {
    /* Unkstruct_2f8e0020: P3.40 T3 band rank 4003; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80181AC0; /* size = 0x14 */

typedef Unkstruct_80181ABC Unkstruct_80183AF8_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_31ee6c39: P3.40 T3 band rank 4006; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x54];
    /* 0x0058 */ s32 unk58;
    /* 0x005c */ u8 pad5C[0x38];
    /* 0x0094 */ s32 unk94;
    /* 0x0098 */ u8 pad98[0x64];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80183F4C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_322321fa: P3.40 T3 band rank 4007; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_801804B4; /* size = 0x20 */

typedef struct {
    /* Unkstruct_32802ab6: P3.40 T3 band rank 4009; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x80];
    /* 0x0084 */ u16 unk84;
    /* 0x0086 */ u8 pad86[0x56];
    /* 0x00dc */ u16 unkDC;
    /* 0x00de */ u8 padDE[0x2];
} Unkstruct_80180728_2; /* size = 0xe0 */

typedef Pair_8013AD38 Unkstruct_8013AD38_6; /* size = 0x4 */


typedef struct {
    /* Unkstruct_334d92ac: P3.40 T3 band rank 4013; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017DC40; /* size = 0x100 */

typedef Unkstruct_8017FA5C Unkstruct_8017D494; /* size = 0x68 */

typedef Unkstruct_80181BA8 Unkstruct_80183D30; /* size = 0x8 */

typedef struct {
    /* Unkstruct_37e14aef: P3.40 T3 band rank 4024; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
} Unkstruct_80183430; /* size = 0x68 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_11; /* size = 0x68 */

typedef struct {
    /* Unkstruct_3ca34db8: P3.40 T3 band rank 4036; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 unk3;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
} Unkstruct_8001D8C4; /* size = 0xc */

typedef Unkstruct_801818B8_2 Unkstruct_801819C0_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_40514cdc: P3.40 T3 band rank 4042; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u16 unkE;
} Unkstruct_8018985C; /* size = 0x10 */

typedef Unkstruct_801312D0 Unkstruct_8018EBCC_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_42e99720: P3.40 T3 band rank 4050; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8018B744; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_431b8c64: P3.40 T3 band rank 4051; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CD314_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_4349ad4c: P3.40 T3 band rank 4052; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xdc];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8018495C_2; /* size = 0x100 */

typedef Unkstruct_801849AC Unkstruct_8018E428; /* size = 0x8 */

typedef Unkstruct_8017FA5C Unkstruct_8017BE9C_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_ecb2a3e4: P3.40 T3 band rank 4654; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x11];
    /* 0x0027 */ u8 unk27;
} Unkstruct_80184028_2;
typedef Unkstruct_80184028_2 Unkstruct_80187644_2; /* size = 0x28 */

typedef Unkstruct_8017FF14 Unkstruct_8018F054; /* size = 0x1c */

typedef struct {
    /* Unkstruct_4871469c: P3.40 T3 band rank 4069; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_8017D918; /* size = 0xe8 */

typedef Unkstruct_80181ABC Unkstruct_80186938_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_4b0e6868: P3.40 T3 band rank 4079; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x10];
    /* 0x001c */ s32 unk1C;
} Unkstruct_801874DC; /* size = 0x20 */

typedef struct {
    /* Unkstruct_4b117cd2: P3.40 T3 band rank 4080; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x52];
    /* 0x0052 */ s16 unk52;
    /* 0x0054 */ u8 pad54[0x5a];
    /* 0x00ae */ u16 unkAE;
    /* 0x00b0 */ u8 padB0[0x14];
    /* 0x00c4 */ u32 unkC4;
    /* 0x00c8 */ u8 padC8[0x18];
    /* 0x00e0 */ u32 unkE0;
} Unkstruct_801852D8; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_4cd37aba: P3.40 T3 band rank 4085; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
    /* 0x0038 */ u8 pad38[0x58];
    /* 0x0090 */ s32 unk90;
    /* 0x0094 */ s32 unk94;
} Unkstruct_8018111C_3; /* size = 0x98 */

typedef struct {
    /* Unkstruct_4ceff2ce: P3.40 T3 band rank 4086; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x9e];
    /* 0x00ae */ s16 unkAE;
    /* 0x00b0 */ u8 padB0[0x4c];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8018415C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_4e5445de: P3.40 T3 band rank 4090; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x24];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017F04C; /* size = 0x38 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_12; /* size = 0x68 */

typedef struct {
    /* Unkstruct_50ae4f6f: P3.40 T3 band rank 4097; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
} Unkstruct_80180FF4; /* size = 0x5c */

typedef Unkstruct_8017FA5C Unkstruct_8017D5C0_2; /* size = 0x68 */


typedef Unkstruct_80181ABC Unkstruct_80185458_2; /* size = 0x8 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_13; /* size = 0x68 */

typedef struct {
    /* Unkstruct_53541cf5: P3.40 T3 band rank 4105; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xbc];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_80180A38_2; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_57e7025e: P3.40 T3 band rank 4112; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0xa];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x18];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_80186F78_3; /* size = 0x30 */

typedef struct {
    /* Unkstruct_587a6142: P3.40 T3 band rank 4114; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018741C; /* size = 0x24 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_14; /* size = 0x68 */

typedef struct {
    /* Unkstruct_5cb62c6b: P3.40 T3 band rank 4122; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2e];
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ u16 unk30;
    /* 0x0032 */ s8 unk32;
    /* 0x0033 */ u8 pad33[0x1];
} Unkstruct_80034A9C; /* size = 0x34 */

typedef struct {
    /* Unkstruct_5ff5383d: P3.40 T3 band rank 4130; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x1f0];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8017E9C0; /* size = 0x218 */

typedef struct {
    /* Unkstruct_6096751c: P3.40 T3 band rank 4132; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_801810D0_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_61c52eeb: P3.40 T3 band rank 4136; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x10];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80185B34; /* size = 0x20 */

typedef Unkstruct_801202A0 Unkstruct_8018C8D4; /* size = 0x104 */

typedef Unkstruct_801312D0 Unkstruct_80187314_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_639ed154: P3.40 T3 band rank 4144; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xc0];
    /* 0x00e4 */ s16 unkE4;
    /* 0x00e6 */ s16 unkE6;
    /* 0x00e8 */ s16 unkE8;
    /* 0x00ea */ u8 padEA[0x2];
} Unkstruct_80184FC4; /* size = 0xec */

typedef struct {
    /* Unkstruct_64994315: P3.40 T3 band rank 4149; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x6];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80187D60_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_64e098d7: P3.40 T3 band rank 4150; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x200];
    /* 0x0200 */ s32 unk200;
    /* 0x0204 */ u8 pad204[0x8];
    /* 0x020c */ s16 unk20C;
    /* 0x020e */ u16 unk20E;
} Unkstruct_8017D528; /* size = 0x210 */

typedef struct {
    /* Unkstruct_6525ce56: P3.40 T3 band rank 4151; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017E5A0; /* size = 0x10 */

typedef struct {
    /* Unkstruct_66265d26: P3.40 T3 band rank 4154; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3c];
    /* 0x0060 */ s16 unk60;
    /* 0x0062 */ s16 unk62;
    /* 0x0064 */ s16 unk64;
    /* 0x0066 */ u8 pad66[0x2];
} Unkstruct_800CDF84; /* size = 0x68 */

typedef struct {
    /* Unkstruct_672bbad8: P3.40 T3 band rank 4159; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80181F0C; /* size = 0x24 */

typedef struct {
    /* Unkstruct_6998217d: P3.40 T3 band rank 4161; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ u16 unk36;
} Unkstruct_801E5CA8_3; /* size = 0x38 */

typedef Unkstruct_800B5BD8 Unkstruct_8017C5F0_4; /* size = 0x38 */

typedef Unkstruct_801202A0 Unkstruct_801802CC_3; /* size = 0x10c */

typedef struct {
    /* Unkstruct_6df4bd63: P3.40 T3 band rank 4176; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x30];
    /* 0x0030 */ s32 unk30;
    /* 0x0034 */ s32 unk34;
    /* 0x0038 */ s32 unk38;
    /* 0x003c */ s32 unk3C;
} Unkstruct_8017D980_3; /* size = 0x40 */

typedef Unkstruct_801312D0 Unkstruct_80182498_2; /* size = 0x8 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_15; /* size = 0x68 */

typedef struct {
    /* Unkstruct_726003b7: P3.40 T3 band rank 4190; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017F8B8; /* size = 0x100 */

typedef Unkstruct_80181ABC Unkstruct_80183F3C_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_737ed1ab: P3.40 T3 band rank 4194; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017D7F8; /* size = 0x2c */

typedef Unkstruct_8017FA5C Unkstruct_8017DF84; /* size = 0x68 */

typedef struct {
    /* Unkstruct_74e2e324: P3.40 T3 band rank 4199; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x28];
    /* 0x002c */ s32 unk2C;
} Unkstruct_80168430_4; /* size = 0x30 */

typedef struct {
    /* Unkstruct_74ffc795: P3.40 T3 band rank 4200; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017EB58_2; /* size = 0x2c */

typedef struct {
    /* Unkstruct_773f51e8: P3.40 T3 band rank 4203; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd4];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ void * unkD8;
    /* 0x00dc */ u8 padDC[0x18];
    /* 0x00f4 */ s32 unkF4;
    /* 0x00f8 */ void * unkF8;
} Unkstruct_8017EBF4; /* size = 0xfc */

typedef struct { u16 x; u16 y; u16 z; s16 w; } Rec8_8018A390_8018523C;

typedef Unkstruct_8017FA5C Unkstruct_8017BE9C_3; /* size = 0x68 */

typedef struct {
    /* Unkstruct_783b9a0c: P3.40 T3 band rank 4210; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x3a];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x9e];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017EF0C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_7877f240: P3.40 T3 band rank 4213; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x74];
    /* 0x0094 */ s32 unk94;
} Unkstruct_801A312C; /* size = 0x98 */

typedef Unkstruct_80181BA8 Unkstruct_80181CF4;
typedef Unkstruct_80181CF4 Unkstruct_80185E38; /* size = 0x8 */

typedef struct {
    /* Unkstruct_79a235bd: P3.40 T3 band rank 4216; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2e];
    /* 0x002e */ s16 unk2E;
    /* 0x0030 */ s16 unk30;
    /* 0x0032 */ u8 unk32;
    /* 0x0033 */ u8 pad33[0x4];
    /* 0x0037 */ u8 unk37;
} Unkstruct_80034A54; /* size = 0x38 */

typedef struct {
    /* Unkstruct_79ecaaff: P3.40 T3 band rank 4218; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017F118; /* size = 0x2c */

typedef struct {
    /* Unkstruct_7c6ff376: P3.40 T3 band rank 4226; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0xe4];
    /* 0x00ec */ s32 unkEC;
    /* 0x00f0 */ s32 unkF0;
    /* 0x00f4 */ u8 padF4[0x10];
} Unkstruct_80181E08; /* size = 0x104 */

typedef struct {
    /* Unkstruct_7e0a6267: P3.40 T3 band rank 4229; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x24];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017DB90_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_7f939922: P3.40 T3 band rank 4235; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_8017E0E4; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_80015c90: P3.40 T3 band rank 4236; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB478; /* size = 0x38 */

typedef struct {
    /* Unkstruct_80446116: P3.40 T3 band rank 4292; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ u16 unkA;
} Unkstruct_8017E17C; /* size = 0xc */

typedef Unkstruct_8017FA5C Unkstruct_8017D604_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_80deb045: P3.40 T3 band rank 4295; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EF7E4; /* size = 0x38 */

typedef Unkstruct_801E2E04 Unkstruct_801EE1F4; /* size = 0xe8 */

typedef Unkstruct_801202A0 Unkstruct_80190574; /* size = 0x104 */

typedef struct {
    /* Unkstruct_81e8e2ab: P3.40 T3 band rank 4304; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xbc];
    /* 0x00cc */ void * unkCC;
} Unkstruct_801865B0; /* size = 0xd0 */

typedef Unkstruct_80181ABC Unkstruct_8018E1F0_2; /* size = 0x8 */

typedef Unkstruct_8017FA5C Unkstruct_8017D960_3; /* size = 0x68 */

typedef Unkstruct_801202A0 Unkstruct_80185404; /* size = 0xd0 */

typedef Unkstruct_801202A0 Unkstruct_80181924; /* size = 0x100 */

typedef struct {
    /* Unkstruct_86a7b930: P3.40 T3 band rank 4320; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x1e];
    /* 0x0024 */ s16 unk24;
    /* 0x0026 */ u8 pad26[0x2e];
    /* 0x0054 */ s32 unk54;
} Unkstruct_8003A0E4; /* size = 0x58 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_16; /* size = 0x68 */

typedef Unkstruct_80183438 Unkstruct_801879FC; /* size = 0x30 */

typedef struct {
    /* Unkstruct_a7db3447: P3.40 T3 band rank 4417; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xd8];
    /* 0x00dc */ u16 unkDC;
    /* 0x00de */ u8 padDE[0x2];
} Unkstruct_80184D3C;

typedef struct {
    /* Unkstruct_8aa45691: P3.40 T3 band rank 4331; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ u32 unk20;
} Unkstruct_80181EE8_2; /* size = 0x24 */

typedef Unkstruct_801202A0 Unkstruct_80182290; /* size = 0x104 */

typedef struct {
    /* Unkstruct_8c42a7a3: P3.40 T3 band rank 4334; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0xf2];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80182078; /* size = 0x100 */

typedef Unkstruct_80181ABC Unkstruct_8018201C_2; /* size = 0x8 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_17; /* size = 0x68 */

typedef struct {
    /* Unkstruct_8fbb3068: P3.40 T3 band rank 4344; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_8018018C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_9123a185: P3.40 T3 band rank 4346; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801EF558_2; /* size = 0x2c */

typedef Unkstruct_8017FA5C Unkstruct_8017D604_3; /* size = 0x68 */

typedef struct {
    /* Unkstruct_92f3a97c: P3.40 T3 band rank 4354; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xac];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80180E9C; /* size = 0xd0 */

typedef Unkstruct_801E26BC Unkstruct_801E26C4_2; /* size = 0x2c */

typedef struct {
    /* Unkstruct_94bba45c: P3.40 T3 band rank 4361; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
    /* 0x0030 */ s32 unk30;
} Unkstruct_80185648_2; /* size = 0x34 */

typedef struct {
    /* Unkstruct_953d49ca: P3.40 T3 band rank 4363; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x62];
    /* 0x0078 */ s32 unk78;
} Unkstruct_801866C4_2; /* size = 0x7c */

typedef Unkstruct_801849AC Unkstruct_80186B70; /* size = 0x8 */

typedef Unkstruct_80183430 Unkstruct_8018868C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_974d421c: P3.40 T3 band rank 4371; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80180A2C_2; /* size = 0x18 */

typedef Unkstruct_8017FA5C Unkstruct_8017C730_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_9d6c03ed: P3.40 T3 band rank 4388; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_801A87C4_2; /* size = 0x1c */

typedef Unkstruct_801202A0 Unkstruct_80189904; /* size = 0x100 */

typedef struct {
    /* Unkstruct_a148547a: P3.40 T3 band rank 4397; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x2];
} Unkstruct_8017E5C0; /* size = 0xc */

typedef struct {
    /* Unkstruct_a22d5ead: P3.40 T3 band rank 4400; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x58];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x74];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_80180654; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_a568b2a7: P3.40 T3 band rank 4408; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017E22C_4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_a64400a3: P3.40 T3 band rank 4411; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017FF74; /* size = 0x74 */

typedef struct {
    /* Unkstruct_a77bd662: P3.40 T3 band rank 4416; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x210];
    /* 0x0234 */ s32 unk234;
    /* 0x0238 */ s32 unk238;
    /* 0x023c */ s32 unk23C;
    /* 0x0240 */ u16 unk240;
    /* 0x0242 */ u8 pad242[0x2];
    /* 0x0244 */ u16 unk244;
    /* 0x0246 */ u16 unk246;
} Unkstruct_800CCD50; /* size = 0x248 */

typedef struct {
    /* Unkstruct_a857d2c3: P3.40 T3 band rank 4418; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801855CC_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_a96ae95c: P3.40 T3 band rank 4425; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1f4];
    /* 0x01f4 */ u8 unk1F4;
    /* 0x01f5 */ u8 pad1F5[0x3];
} Unkstruct_8003819C; /* size = 0x1f8 */

typedef Unkstruct_80181ABC Unkstruct_80181970_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_af8903cf: P3.40 T3 band rank 4439; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
    /* 0x0030 */ s32 unk30;
} Unkstruct_801853D0_3; /* size = 0x34 */

typedef struct {
    /* Unkstruct_b07361a0: P3.40 T3 band rank 4441; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ u32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ u32 unk1C;
} Unkstruct_80184C68; /* size = 0x20 */

typedef struct {
    /* Unkstruct_b09e237e: P3.40 T3 band rank 4442; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ u32 unk1C;
    /* 0x0020 */ u8 pad20[0x3e];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x62];
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 unkC3;
} Unkstruct_801849BC; /* size = 0xc4 */

typedef Unkstruct_801202A0 Unkstruct_80189DC8; /* size = 0xe0 */

typedef Unkstruct_8016C49C Unkstruct_8016D1D8_5; /* size = 0x38 */

typedef struct {
    /* Unkstruct_e0aad455: P3.40 T3 band rank 4622; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80182D18_2;
typedef Unkstruct_80182D18_2 Unkstruct_80185D2C_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_b2a57d4c: P3.40 T3 band rank 4452; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x104];
    /* 0x0108 */ s16 unk108;
    /* 0x010a */ u8 pad10A[0x2];
} Unkstruct_8017F470; /* size = 0x10c */

typedef Unkstruct_8017FA5C Unkstruct_8017C340; /* size = 0x68 */

typedef Unkstruct_8017FA5C Unkstruct_8017CD9C_5; /* size = 0x68 */

typedef Unkstruct_801202A0 Unkstruct_80142EC0_4; /* size = 0x100 */

typedef struct {
    /* Unkstruct_b6ffc3d8: P3.40 T3 band rank 4469; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801851A8_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_b752f8f5: P3.40 T3 band rank 4471; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x6];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x1c];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017F88C; /* size = 0x38 */

typedef Unkstruct_801312D0 Unkstruct_801829F8_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_b8740dea: P3.40 T3 band rank 4480; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd4];
    /* 0x00d4 */ s32 unkD4;
    /* 0x00d8 */ u8 padD8[0x30];
    /* 0x0108 */ u16 unk108;
    /* 0x010a */ u16 unk10A;
} Unkstruct_8017F39C; /* size = 0x10c */

typedef struct {
    /* Unkstruct_ba444306: P3.40 T3 band rank 4485; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0xee];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8018B698; /* size = 0x100 */

typedef Unkstruct_8017FA5C Unkstruct_8017E778_4; /* size = 0x68 */

typedef struct {
    /* Unkstruct_badd1ceb: P3.40 T3 band rank 4488; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ void * unk34;
} Unkstruct_800CB5DC; /* size = 0x38 */

typedef Unkstruct_8017FA5C Unkstruct_8017DF34; /* size = 0x68 */

typedef struct {
    /* Unkstruct_bb941644: P3.40 T3 band rank 4491; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
} Unkstruct_801840DC; /* size = 0x68 */

typedef Unkstruct_8017FA5C Unkstruct_8017C730_3; /* size = 0x68 */

typedef Unkstruct_80181ABC Unkstruct_8018A860_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_bffba6fe: P3.40 T3 band rank 4506; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
    /* 0x0030 */ s32 unk30;
} Unkstruct_801852BC_2; /* size = 0x34 */

typedef Unkstruct_80181ABC Unkstruct_80185C00_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_c0408fb7: P3.40 T3 band rank 4510; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_8017E4B4_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_c1476ec3: P3.40 T3 band rank 4515; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80182368; /* size = 0x24 */

typedef Unkstruct_8017FA5C Unkstruct_8017BE9C_4; /* size = 0x68 */

typedef Unkstruct_801312D0 Unkstruct_8018B2C4_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_c438fda2: P3.40 T3 band rank 4524; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3c];
    /* 0x003c */ s32 unk3C;
    /* 0x0040 */ u8 pad40[0x4];
    /* 0x0044 */ s32 unk44;
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ u8 pad4C[0x4];
    /* 0x0050 */ s32 unk50;
} Unkstruct_80189B74; /* size = 0x54 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_18; /* size = 0x68 */

typedef struct {
    /* Unkstruct_c7974e79: P3.40 T3 band rank 4538; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ u32 unkC;
    /* 0x0010 */ u8 pad10[0x4];
    /* 0x0014 */ u32 unk14;
} Unkstruct_80180D48; /* size = 0x18 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_19; /* size = 0x68 */

typedef struct {
    /* Unkstruct_ca033073: P3.40 T3 band rank 4547; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5e];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x62];
    /* 0x00c2 */ u8 unkC2;
    /* 0x00c3 */ u8 padC3[0x1];
} Unkstruct_8018F028; /* size = 0xc4 */

typedef Unkstruct_80183438 Unkstruct_801843D8; /* size = 0x30 */

typedef Unkstruct_8017FA5C Unkstruct_8017EC58; /* size = 0x68 */

typedef struct {
    /* Unkstruct_cca0ef5a: P3.40 T3 band rank 4556; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0xaa];
    /* 0x00e0 */ u16 unkE0;
    /* 0x00e2 */ u8 padE2[0x10];
    /* 0x00f2 */ s16 unkF2;
    /* 0x00f4 */ s16 unkF4;
    /* 0x00f6 */ u8 padF6[0x14];
    /* 0x010a */ u16 unk10A;
} Unkstruct_80187068; /* size = 0x10c */

typedef Unkstruct_801312D0 Unkstruct_80185150_2; /* size = 0x8 */

typedef Unkstruct_801312D0 Unkstruct_801860E8_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_d61d362a: P3.40 T3 band rank 4582; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x26];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8017EDF4; /* size = 0x60 */

typedef struct {
    /* Unkstruct_d6913b71: P3.40 T3 band rank 4585; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8018B9DC; /* size = 0xd0 */

typedef Unkstruct_80181CF4 Unkstruct_80185944; /* size = 0x8 */

typedef struct {
    /* Unkstruct_da92e27c: P3.40 T3 band rank 4594; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ s16 unk102;
} Unkstruct_8018FD04; /* size = 0x104 */

typedef struct {
    /* Unkstruct_dab3944e: P3.40 T3 band rank 4596; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8012E688; /* size = 0x24 */

typedef struct {
    /* Unkstruct_db20059d: P3.40 T3 band rank 4598; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x42];
    /* 0x0052 */ s16 unk52;
} Unkstruct_80182818; /* size = 0x54 */

typedef struct {
    /* Unkstruct_db4844a8: P3.40 T3 band rank 4599; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_80183100_2; /* size = 0x68 */

typedef Unkstruct_8017FA5C Unkstruct_8017D604_4; /* size = 0x68 */

typedef Unkstruct_800B5BD8 Unkstruct_8017CE90_5; /* size = 0x30 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_20; /* size = 0x68 */

typedef struct {
    /* Unkstruct_dfa0adc4: P3.40 T3 band rank 4618; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xfa];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8017FB5C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_e0b401eb: P3.40 T3 band rank 4623; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8018B830; /* size = 0x1c */

typedef Unkstruct_801312D0 Unkstruct_8018B23C_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_e5ff0dbd: P3.40 T3 band rank 4635; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x198];
    /* 0x0198 */ s32 unk198;
    /* 0x019c */ u8 pad19C[0x5c];
    /* 0x01f8 */ u32 unk1F8;
    /* 0x01fc */ u8 pad1FC[0x18];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_8017FB14_2; /* size = 0x218 */

typedef struct {
    /* Unkstruct_e9346624: P3.40 T3 band rank 4644; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x8];
    /* 0x001e */ s16 unk1E;
} Unkstruct_80180FA8_2; /* size = 0x20 */

typedef Unkstruct_8017FA5C Unkstruct_8017BEBC_21; /* size = 0x68 */

typedef Unkstruct_80181BA8 Unkstruct_8018AB20; /* size = 0x8 */

typedef Unkstruct_801312D0 Unkstruct_801844D4_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_ec762735: P3.40 T3 band rank 4652; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ s32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ void * unk20;
} Unkstruct_80188AEC; /* size = 0x24 */

typedef Unkstruct_8017FA5C Unkstruct_8017DB5C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_ee4e18bf: P3.40 T3 band rank 4657; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
} Unkstruct_80180548; /* size = 0x30 */

typedef Unkstruct_80182D18_2 Unkstruct_80184E84_2; /* size = 0x24 */

typedef Unkstruct_801202A0 Unkstruct_80181FF4; /* size = 0x10c */

typedef struct {
    /* Unkstruct_f1c5113d: P3.40 T3 band rank 4667; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u8 pad18[0x4];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0xaa];
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x2];
} Unkstruct_80181FE8_2; /* size = 0xe4 */

typedef Unkstruct_80181CF4 Unkstruct_80184174_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_f315a764: P3.40 T3 band rank 4670; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xc];
    /* 0x002c */ s32 unk2C;
    /* 0x0030 */ u8 pad30[0x4];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CDBA8; /* size = 0x38 */

typedef struct {
    /* Unkstruct_f68570ae: P3.40 T3 band rank 4680; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0x4];
    /* 0x0018 */ s32 unk18;
} Unkstruct_8017FD20; /* size = 0x1c */

typedef Unkstruct_801202A0 Unkstruct_8017F494; /* size = 0x10c */

typedef Unkstruct_8017FA5C Unkstruct_8017D960_5; /* size = 0x68 */

typedef Unkstruct_801312D0 Unkstruct_80184918_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_fc51262b: P3.40 T3 band rank 4692; 4 TNC sites in 1 bodies; struct map 4 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x94];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801846B8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_008b4333: P3.40 T3 band rank 4705; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x70];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_801820DC_2; /* size = 0x74 */

typedef struct {
    /* Unkstruct_01cc0fae: P3.40 T3 band rank 4706; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8018067C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_090d7e13: P3.40 T3 band rank 4710; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_801845B8; /* size = 0x4 */

typedef struct {
    /* Unkstruct_17220413: P3.40 T3 band rank 4713; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_801814E4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_1fc65182: P3.40 T3 band rank 4715; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80187D90; /* size = 0x38 */

typedef struct {
    /* Unkstruct_27969254: P3.40 T3 band rank 4720; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8018001C_2; /* size = 0x14 */

typedef Unkstruct_8015C128_5 Unkstruct_8015C128_6; /* size = 0x14 */

typedef struct {
    /* Unkstruct_311387d4: P3.40 T3 band rank 4722; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80181C18_3; /* size = 0x24 */

typedef Unkstruct_80126948 Unkstruct_8017496C_2; /* size = 0x8 */

typedef Unkstruct_80126B58 Unkstruct_8017D840; /* size = 0x218 */

typedef struct {
    /* Unkstruct_3a26aba6: P3.40 T3 band rank 4727; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017DB64_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_3ed5bcf3: P3.40 T3 band rank 4728; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5e];
    /* 0x005e */ u16 unk5E;
} Unkstruct_801881F8; /* size = 0x60 */

typedef struct {
    /* Unkstruct_43da0da0: P3.40 T3 band rank 4729; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_800CB1C0; /* size = 0x4 */

typedef Unkstruct_80126B58 Unkstruct_8015CC74; /* size = 0x4 */

typedef struct {
    /* Unkstruct_60399e01: P3.40 T3 band rank 4731; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017D8AC_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_78f36843: P3.40 T3 band rank 4737; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe];
    /* 0x000e */ u16 unkE;
} Unkstruct_801860F4_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_7b0c492d: P3.40 T3 band rank 4739; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_800CB214; /* size = 0x4 */

typedef struct {
    /* Unkstruct_81e26c65: P3.40 T3 band rank 4749; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80180EB0; /* size = 0x4 */

typedef Dst Unkstruct_8017CDD8_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_84ef9f1f: P3.40 T3 band rank 4751; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017E02C; /* size = 0x4 */

typedef Unkstruct_801202A0 Unkstruct_801312D0_8; /* size = 0xc0 */

typedef Unkstruct_80126B58 Unkstruct_8015E1B8_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_a67bc6f6: P3.40 T3 band rank 4758; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x98];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_8017F070; /* size = 0x9c */

typedef Unkstruct_80126B58 Unkstruct_8017DA54; /* size = 0x218 */

typedef struct {
    /* Unkstruct_b6e16d68: P3.40 T3 band rank 4763; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8016A290_8; /* size = 0x24 */

typedef Unkstruct_80126B58 Unkstruct_80174384_2; /* size = 0x218 */

typedef Unkstruct_801202A0 Unkstruct_80130D0C_3; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_c882954c: P3.40 T3 band rank 4768; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xe];
    /* 0x0032 */ s16 unk32;
} Unkstruct_8017DE80_4; /* size = 0x34 */

typedef Unkstruct_800B5BD8 Unkstruct_8018028C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_d0b9bb75: P3.40 T3 band rank 4770; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017E71C_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_ec04d972: P3.40 T3 band rank 4780; 3 TNC sites in 3 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_801834CC; /* size = 0x4 */

typedef struct {
    /* Unkstruct_00fed4e6: P3.40 T3 band rank 4783; 3 TNC sites in 2 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xba];
    /* 0x00de */ u8 unkDE;
    /* 0x00df */ u8 padDF[0x1];
} Unkstruct_801849A8; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_10a9d7fc: P3.40 T3 band rank 4786; 3 TNC sites in 2 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x58];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017F590_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_3878a39f: P3.40 T3 band rank 4788; 3 TNC sites in 2 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x27];
    /* 0x0027 */ u8 unk27;
} Unkstruct_801844AC_3; /* size = 0x28 */

typedef struct {
    /* Unkstruct_47a1e7a7: P3.40 T3 band rank 4790; 3 TNC sites in 2 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0xc];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017DD44; /* size = 0x18 */

typedef struct {
    /* Unkstruct_5ad6bad9: P3.40 T3 band rank 4793; 3 TNC sites in 2 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0xc];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017E25C; /* size = 0x18 */

typedef struct {
    /* Unkstruct_801CE2D8: P3.40 T3 band rank 4819; 3 TNC sites in 2 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x18]; /* T16.c8: element of D_801CE2D8[6], stride 0x20 */
} Unkstruct_8017EBCC_2; /* size = 0x20; was 0x8 */

typedef struct {
    /* Unkstruct_867e94a0: P3.40 T3 band rank 4820; 3 TNC sites in 2 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x3];
    /* 0x0003 */ u8 unk3;
} Unkstruct_8017E908; /* size = 0x4 */

typedef Unkstruct_801202A0 Unkstruct_8017E024; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_bedb573d: P3.40 T3 band rank 4822; 3 TNC sites in 2 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EF49C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_035989cf: P3.40 T3 band rank 4834; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80183554; /* size = 0x38 */

typedef struct {
    /* Unkstruct_033e11b3: P3.40 T3 band rank 4833; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801EFD60; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_03e3d648: P3.40 T3 band rank 4836; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x24];
    /* 0x0024 */ u8 unk24;
    /* 0x0025 */ u8 unk25;
    /* 0x0026 */ u8 unk26;
    /* 0x0027 */ u8 pad27[0x1];
} Unkstruct_80188A10; /* size = 0x28 */

typedef struct {
    /* Unkstruct_38402253: P3.40 T3 band rank 5024; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8018234C_3;
typedef Unkstruct_8018234C_3 Unkstruct_80184918_3; /* size = 0x4 */

typedef Unkstruct_801202A0 Unkstruct_8018A224; /* size = 0x5c */

typedef struct {
    /* Unkstruct_0714f1d0: P3.40 T3 band rank 4848; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
} Unkstruct_80039308_4; /* size = 0x18 */

typedef struct {
    /* Unkstruct_078410e9: P3.40 T3 band rank 4850; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8017D6CC; /* size = 0x100 */

typedef Unkstruct_80126B58 Unkstruct_8017C6F4_2; /* size = 0x210 */

typedef Unkstruct_8001C9D0 Unkstruct_8018613C_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_0b8ddc21: P3.40 T3 band rank 4868; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5e];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x9e];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80187F18; /* size = 0x100 */

typedef struct {
    /* Unkstruct_0bdaaca9: P3.40 T3 band rank 4870; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ u32 unk1C;
} Unkstruct_80180D40_2; /* size = 0x20 */

typedef Unkstruct_8018234C_3 Unkstruct_80182498_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_0ee542ad: P3.40 T3 band rank 4880; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ u8 pad1C[0x10];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_801AB748_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_106dcf6a: P3.40 T3 band rank 4886; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xdc];
    /* 0x00e0 */ s32 unkE0;
} Unkstruct_8017E448_2; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_107843e9: P3.40 T3 band rank 4887; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80182848; /* size = 0x8 */

typedef struct {
    /* Unkstruct_11c31d92: P3.40 T3 band rank 4892; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
} Unkstruct_80181B0C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_120d2015: P3.40 T3 band rank 4893; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe0];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x4];
    /* 0x00e8 */ s32 unkE8;
} Unkstruct_80181378; /* size = 0xec */

typedef struct {
    /* Unkstruct_148ef05e: P3.40 T3 band rank 4898; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017DB40; /* size = 0x38 */

typedef Unkstruct_801202A0 Unkstruct_80189C7C_2; /* size = 0xe0 */


typedef struct {
    /* Unkstruct_16c7534e: P3.40 T3 band rank 4906; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8003491C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_18a5f7a8: P3.40 T3 band rank 4911; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017E608_4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_193f6f8e: P3.40 T3 band rank 4912; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 unk0;
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 pad2[0x2];
} Unkstruct_800CAE74_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_19b1b2ab: P3.40 T3 band rank 4914; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0xa];
    /* 0x000c */ s32 unkC;
} Unkstruct_8017E558_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_1aaf10a0: P3.40 T3 band rank 4918; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8018F944; /* size = 0x20 */

typedef struct {
    /* Unkstruct_1c679ec1: P3.40 T3 band rank 4924; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8018EDB0; /* size = 0x8 */

typedef struct {
    /* Unkstruct_1cac0937: P3.40 T3 band rank 4927; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017DEF0_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_1d8a0ad1: P3.40 T3 band rank 4930; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0xa];
    /* 0x000c */ s32 unkC;
} Unkstruct_8017D994_4; /* size = 0x10 */

typedef struct {
    /* Unkstruct_1e73a90f: P3.40 T3 band rank 4933; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x2];
} Unkstruct_80015A08; /* size = 0xc */

typedef struct {
    /* Unkstruct_1e7ff09e: P3.40 T3 band rank 4934; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xec];
    /* 0x00fc */ s16 unkFC;
} Unkstruct_8017FD14_2; /* size = 0xfe */

typedef struct {
    /* Unkstruct_1e931b08: P3.40 T3 band rank 4935; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xac];
    /* 0x00ac */ s16 unkAC;
    /* 0x00ae */ u8 padAE[0x156];
    /* 0x0204 */ s32 unk204;
    /* 0x0208 */ u8 pad208[0xc];
    /* 0x0214 */ u8 unk214;
    /* 0x0215 */ u8 pad215[0x3];
} Unkstruct_801810F0; /* size = 0x218 */

typedef struct {
    /* Unkstruct_20348837: P3.40 T3 band rank 4938; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80181BBC; /* size = 0x20 */

typedef Unkstruct_80180854_3 Unkstruct_8017F7F4; /* size = 0x9c */

typedef struct {
    /* Unkstruct_21df2588: P3.40 T3 band rank 4945; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x61];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_80183228_2; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_222bf9ff: P3.40 T3 band rank 4947; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_801815AC_2; /* size = 0x68 */

typedef Unkstruct_801202A0 Unkstruct_8017FA00_2; /* size = 0x68 */

typedef Unkstruct_80136A94 Unkstruct_8017ED60_2; /* size = 0x54 */

typedef Unkstruct_80126948 Unkstruct_8017D04C_2; /* size = 0x18 */

typedef Unkstruct_80136A94 Unkstruct_8017EF54_2; /* size = 0x54 */

typedef struct {
    /* Unkstruct_25f29101: P3.40 T3 band rank 4958; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018985C_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_2626c845: P3.40 T3 band rank 4960; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
} Unkstruct_80185264_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_26304893: P3.40 T3 band rank 4961; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CB6D4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_272a0cfa: P3.40 T3 band rank 4966; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
} Unkstruct_801831C8_3; /* size = 0x68 */

typedef struct {
    /* Unkstruct_279cdc6f: P3.40 T3 band rank 4970; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xda];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80183278; /* size = 0x100 */

typedef struct {
    /* Unkstruct_2c593b26: P3.40 T3 band rank 4981; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
} Unkstruct_8017F24C_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_2d9d5b61: P3.40 T3 band rank 4985; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x16];
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s32 unk34;
} Unkstruct_800CD5F8; /* size = 0x38 */

typedef Unkstruct_801202A0 Unkstruct_80187D50; /* size = 0xec */

typedef struct {
    /* Unkstruct_2dc4f049: P3.40 T3 band rank 4988; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
} Unkstruct_80185C40; /* size = 0xc */

typedef Unkstruct_8018234C_3 Unkstruct_8018EBCC_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_2f276706: P3.40 T3 band rank 4994; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ u16 unkE;
} Unkstruct_80181AA8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_310bf565: P3.40 T3 band rank 4997; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80181614; /* size = 0x14 */

typedef struct {
    /* Unkstruct_311a66e5: P3.40 T3 band rank 4998; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8018676C_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_329c2125: P3.40 T3 band rank 5002; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x63];
    /* 0x00c1 */ s8 unkC1;
    /* 0x00c2 */ s8 unkC2;
    /* 0x00c3 */ u8 padC3[0x1];
} Unkstruct_80188F08; /* size = 0xc4 */

typedef struct {
    /* Unkstruct_33816e63: P3.40 T3 band rank 5006; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8017F458_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_338e9daa: P3.40 T3 band rank 5007; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ u32 unk1C;
} Unkstruct_8018D7F0; /* size = 0x20 */

typedef struct {
    /* Unkstruct_35144bb8: P3.40 T3 band rank 5011; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
} Unkstruct_801813F8; /* size = 0x8 */

typedef struct {
    /* Unkstruct_35b92ea5: P3.40 T3 band rank 5014; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017F344_2; /* size = 0x14 */

typedef Unkstruct_8017BB34 Unkstruct_8017BA3C_3; /* size = 0x10 */

typedef struct {
    /* Unkstruct_38cf77f7: P3.40 T3 band rank 5026; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_80183E2C_2; /* size = 0xe8 */

typedef Unkstruct_80175DA8_6 Unkstruct_80175DA8_7; /* size = 0x24 */

typedef struct {
    /* Unkstruct_39e6b9fa: P3.40 T3 band rank 5030; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017E9C0_2; /* size = 0x14 */

typedef Unkstruct_801202A0 Unkstruct_8017E930_2; /* size = 0xe0 */

typedef Unkstruct_8001C9D0 Unkstruct_80181A4C_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_3bc345ae: P3.40 T3 band rank 5040; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80184F68; /* size = 0x38 */

typedef struct {
    /* Unkstruct_3bee5967: P3.40 T3 band rank 5041; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017D518_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_3e20ede0: P3.40 T3 band rank 5050; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80180940_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_3ee3d09b: P3.40 T3 band rank 5054; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017E298_4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_3f3513b6: P3.40 T3 band rank 5055; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ void * unk20;
} Unkstruct_8018050C_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_434f55e1: P3.40 T3 band rank 5070; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_80180A38_3; /* size = 0x10 */

typedef struct {
    /* Unkstruct_458998f1: P3.40 T3 band rank 5073; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ u16 unkE4;
    /* 0x00e6 */ u16 unkE6;
    /* 0x00e8 */ u16 unkE8;
    /* 0x00ea */ u8 padEA[0x2];
} Unkstruct_801859E4; /* size = 0xec */

typedef struct {
    /* Unkstruct_45a516c9: P3.40 T3 band rank 5074; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x68];
    /* 0x0068 */ s32 unk68;
    /* 0x006c */ s32 unk6C;
    /* 0x0070 */ s32 unk70;
} Unkstruct_8018B1B4_2; /* size = 0x74 */

typedef struct {
    /* Unkstruct_569cea72: P3.40 T3 band rank 5140; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x3a];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_8017EA78;

typedef Unkstruct_80181A80 Unkstruct_8018A970; /* size = 0xc */

typedef struct {
    /* Unkstruct_4738e8a1: P3.40 T3 band rank 5079; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801E2ED8; /* size = 0xe8 */

typedef Unkstruct_8001C9D0 Unkstruct_8017C2B0_5; /* size = 0x30 */

typedef struct {
    /* Unkstruct_486e1283: P3.40 T3 band rank 5085; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s8 unk4;
    /* 0x0005 */ s8 unk5;
    /* 0x0006 */ s8 unk6;
    /* 0x0007 */ u8 pad7[0x1];
} Unkstruct_801879A8; /* size = 0x8 */

typedef Unkstruct_8017BF50 Unkstruct_8017BF70; /* size = 0x20 */

typedef struct {
    /* Unkstruct_490c8f78: P3.40 T3 band rank 5088; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u16 unkA;
} Unkstruct_8002374C_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_4b11a899: P3.40 T3 band rank 5094; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u16 unk6;
} Unkstruct_8017FCC0; /* size = 0x8 */

typedef struct {
    /* Unkstruct_4b8084bc: P3.40 T3 band rank 5096; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80181750; /* size = 0x14 */

typedef struct {
    /* Unkstruct_4bcc5186: P3.40 T3 band rank 5097; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_80181794; /* size = 0x74 */

typedef struct {
    /* Unkstruct_4c10f972: P3.40 T3 band rank 5099; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s32 unkC;
} Unkstruct_80180528; /* size = 0x10 */

typedef struct {
    /* Unkstruct_4c6c4338: P3.40 T3 band rank 5101; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x44];
    /* 0x0044 */ u32 unk44;
    /* 0x0048 */ u8 pad48[0x14f];
    /* 0x0197 */ u8 unk197;
    /* 0x0198 */ u8 pad198[0x14];
    /* 0x01ac */ u32 unk1AC;
} Unkstruct_800CAEC0; /* size = 0x1b0 */

typedef Unkstruct_801202A0 Unkstruct_801827CC; /* size = 0x24 */

typedef Unkstruct_8018234C_3 Unkstruct_80185150_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_bb9bcd8c: P3.40 T3 band rank 5562; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017EA70;
typedef Unkstruct_8017EA70 Unkstruct_8017EA88_4; /* size = 0x2c */

typedef Unkstruct_8016E7C8 Unkstruct_8018460C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_50e46746: P3.40 T3 band rank 5119; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017F1FC; /* size = 0x20 */

typedef struct {
    /* Unkstruct_5136c345: P3.40 T3 band rank 5120; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
} Unkstruct_80182318_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_51a8c66a: P3.40 T3 band rank 5124; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_80186178_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_51de1d65: P3.40 T3 band rank 5126; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0xc];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017DC7C_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_52a280b9: P3.40 T3 band rank 5129; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x94];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_801803A4; /* size = 0x9c */

typedef struct {
    /* Unkstruct_52a76bd2: P3.40 T3 band rank 5130; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x12];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017EC00_2; /* size = 0x30 */

typedef Unkstruct_8016E7C8 Unkstruct_8016A8FC_5; /* size = 0x10 */

typedef struct {
    /* Unkstruct_590435c3: P3.40 T3 band rank 5150; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017D028; /* size = 0x2c */

typedef struct {
    /* Unkstruct_5aab74be: P3.40 T3 band rank 5159; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ u8 pad14[0x20];
    /* 0x0034 */ void * unk34;
} Unkstruct_8017D588_5; /* size = 0x38 */

typedef Unkstruct_8018234C_3 Unkstruct_80187314_3; /* size = 0x4 */

typedef Unkstruct_8018234C_3 Unkstruct_801860E8_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_5b812e7b: P3.40 T3 band rank 5165; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017E498; /* size = 0x38 */

typedef struct {
    /* Unkstruct_5cf592bc: P3.40 T3 band rank 5168; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_80183D38_2; /* size = 0x74 */

typedef struct {
    /* Unkstruct_5d33085a: P3.40 T3 band rank 5169; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80183578_2; /* size = 0x4 */

typedef Unkstruct_8017BF50 Unkstruct_8017BF50_4; /* size = 0x20 */

typedef Unkstruct_8018234C_3 Unkstruct_8018B2C4_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_603c5fef: P3.40 T3 band rank 5176; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x18];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018063C_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_61e45373: P3.40 T3 band rank 5180; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x15];
    /* 0x0027 */ u8 unk27;
} Unkstruct_8018B8CC_2; /* size = 0x28 */

typedef struct {
    /* Unkstruct_6447e00c: P3.40 T3 band rank 5187; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017F028; /* size = 0x20 */

typedef struct {
    /* Unkstruct_65e1c331: P3.40 T3 band rank 5191; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe];
    /* 0x000e */ s16 unkE;
} Unkstruct_8018C334; /* size = 0x10 */

typedef struct {
    /* Unkstruct_662a86ed: P3.40 T3 band rank 5193; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
} Unkstruct_80184BAC_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_66b8ddf6: P3.40 T3 band rank 5198; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s32 unk18;
} Unkstruct_8018562C_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_68d25c55: P3.40 T3 band rank 5201; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4];
    /* 0x0028 */ u8 unk28;
    /* 0x0029 */ u8 pad29[0x3];
} Unkstruct_8018BC48; /* size = 0x2c */

typedef struct {
    /* Unkstruct_693f6d75: P3.40 T3 band rank 5202; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80180DCC; /* size = 0x14 */

typedef struct {
    /* Unkstruct_698591a4: P3.40 T3 band rank 5204; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017FD68; /* size = 0x24 */

typedef Unkstruct_80181AD0_2 Unkstruct_80181B14_3; /* size = 0xc */

typedef struct {
    /* Unkstruct_6b6555e0: P3.40 T3 band rank 5209; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ u8 padA[0x2];
} Unkstruct_8017E5D8; /* size = 0xc */

typedef struct {
    /* Unkstruct_6c66b66c: P3.40 T3 band rank 5211; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x4];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8001404C; /* size = 0x14 */

typedef Unkstruct_80183578_2 Unkstruct_80184350_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_6edae2e7: P3.40 T3 band rank 5217; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe2];
    /* 0x00e2 */ s16 unkE2;
} Unkstruct_8018214C; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_6f09fb22: P3.40 T3 band rank 5220; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8018B13C; /* size = 0x100 */

typedef Unkstruct_800B5BD8 Unkstruct_80188C34_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_70e08682: P3.40 T3 band rank 5225; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018BCA4; /* size = 0x24 */

typedef struct {
    /* Unkstruct_7175f185: P3.40 T3 band rank 5228; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0xc];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017D8B0_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_723c398f: P3.40 T3 band rank 5230; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x3c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x63];
    /* 0x00c1 */ u8 unkC1;
    /* 0x00c2 */ u8 padC2[0x2];
} Unkstruct_801846C0; /* size = 0xc4 */


typedef struct {
    /* Unkstruct_c7a2f206: P3.40 T3 band rank 5600; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E2E44;
typedef Unkstruct_801E2E44 Unkstruct_801EFCAC; /* size = 0x38 */

typedef struct {
    /* Unkstruct_75cd71ed: P3.40 T3 band rank 5240; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x10];
    /* 0x0030 */ s32 unk30;
} Unkstruct_800CE134; /* size = 0x34 */

typedef struct {
    /* Unkstruct_761c96c1: P3.40 T3 band rank 5242; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017FF70_2; /* size = 0x38 */

typedef Unkstruct_8018234C_3 Unkstruct_80185E34_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_79439ccd: P3.40 T3 band rank 5247; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0xa];
    /* 0x000c */ s32 unkC;
} Unkstruct_8017E1D4_3; /* size = 0x10 */

typedef struct {
    /* Unkstruct_79fd0640: P3.40 T3 band rank 5249; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8018CD80; /* size = 0x30 */

typedef struct {
    /* Unkstruct_7a12a802: P3.40 T3 band rank 5250; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80182240; /* size = 0x20 */

typedef struct {
    /* Unkstruct_7a434b53: P3.40 T3 band rank 5251; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_80189268_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_a60eb9bf: P3.40 T3 band rank 5497; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0xbc];
    /* 0x00dc */ s32 unkDC;
    /* 0x00e0 */ u8 padE0[0xc];
    /* 0x00ec */ s32 unkEC;
} Unkstruct_8017EC90_2; /* size = 0xf0 */

typedef struct {
    /* Unkstruct_daa0da71: P3.40 T3 band rank 5674; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8018A8B8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_7cd83848: P3.40 T3 band rank 5260; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x10];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8016D1D8_6; /* size = 0x1c */

typedef struct {
    /* Unkstruct_7ee1b646: P3.40 T3 band rank 5263; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80181B80; /* size = 0x38 */

typedef struct {
    /* Unkstruct_7f387835: P3.40 T3 band rank 5265; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ u16 unkFC;
    /* 0x00fe */ u16 unkFE;
} Unkstruct_80186384; /* size = 0x100 */

typedef struct {
    /* Unkstruct_7f457c92: P3.40 T3 band rank 5266; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CB720; /* size = 0x1c */

typedef Unkstruct_800B5BD8 Unkstruct_8018A724_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_801c016f: P3.40 T3 band rank 5369; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ u8 pad14[0x2];
    /* 0x0016 */ s16 unk16;
    /* 0x0018 */ u8 pad18[0x2];
    /* 0x001a */ s16 unk1A;
} Unkstruct_800D2318; /* size = 0x1c */

typedef struct {
    /* Unkstruct_810a5f69: P3.40 T3 band rank 5371; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0xaa];
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x2];
} Unkstruct_80182098; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_81442caa: P3.40 T3 band rank 5372; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8017C738_4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_f438f8c1: P3.40 T3 band rank 5756; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0xa];
    /* 0x000c */ s32 unkC;
} Unkstruct_8017DDE0_2;
typedef Unkstruct_8017DDE0_2 Unkstruct_8017F278_5; /* size = 0x10 */

typedef struct {
    /* Unkstruct_8466786f: P3.40 T3 band rank 5378; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801807CC_2; /* size = 0x18 */

typedef Unkstruct_8016E7C8 Unkstruct_801876E8; /* size = 0x10 */

typedef Dst Unkstruct_8017CE7C_3; /* size = 0x2c */

typedef Unkstruct_801202A0 Unkstruct_8018584C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_8838ae24: P3.40 T3 band rank 5391; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80181124; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_887a2bd7: P3.40 T3 band rank 5392; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
} Unkstruct_8018734C_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_895e85f2: P3.40 T3 band rank 5395; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
} Unkstruct_8017F418_2; /* size = 0x68 */

typedef struct {
    /* Unkstruct_8982886f: P3.40 T3 band rank 5396; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x96];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80184134; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_89bb3e23: P3.40 T3 band rank 5397; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EE234; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8a86752c: P3.40 T3 band rank 5398; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0xe];
    /* 0x0010 */ s32 unk10;
} Unkstruct_800CBBF8_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_8ad13b44: P3.40 T3 band rank 5400; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801869CC; /* size = 0x38 */

typedef Unkstruct_801202A0 Unkstruct_80183ED8; /* size = 0x100 */

typedef struct {
    /* Unkstruct_8ee2671b: P3.40 T3 band rank 5417; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x14];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80180E4C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8fb232fe: P3.40 T3 band rank 5419; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xac];
    /* 0x00b0 */ s32 unkB0;
} Unkstruct_801E5664; /* size = 0xb4 */

typedef Unkstruct_800B5BD8 Unkstruct_8017CFBC_5; /* size = 0x1c */


typedef struct {
    /* Unkstruct_91fedcf6: P3.40 T3 band rank 5426; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8018AD9C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_921b97ea: P3.40 T3 band rank 5427; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
} Unkstruct_8017E60C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_92beda11: P3.40 T3 band rank 5432; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_80180230; /* size = 0x2c */

typedef Unkstruct_801202A0 Unkstruct_8017BF50_5; /* size = 0xe0 */

typedef Unkstruct_8016E7C8 Unkstruct_801831D4; /* size = 0x10 */

typedef struct {
    /* Unkstruct_95203c5d: P3.40 T3 band rank 5450; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017EE10_2; /* size = 0x68 */

typedef Unkstruct_80175DA8_6 Unkstruct_80175DA8_8; /* size = 0x24 */

typedef struct {
    /* Unkstruct_9cc37fc9: P3.40 T3 band rank 5468; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0xc];
    /* 0x0010 */ s32 unk10;
    /* 0x0014 */ u8 pad14[0xc];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017DFB8; /* size = 0x24 */

typedef Unkstruct_8017E0C4_2 Unkstruct_80189DC8_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_9daa7bd5: P3.40 T3 band rank 5472; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017DA68; /* size = 0x20 */

typedef struct {
    /* Unkstruct_9e104065: P3.40 T3 band rank 5473; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017F124; /* size = 0x74 */

typedef Unkstruct_800B5BD8 Unkstruct_8017CFBC_6; /* size = 0x1c */

typedef struct {
    /* Unkstruct_9fbae46d: P3.40 T3 band rank 5479; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfe];
    /* 0x00fe */ s16 unkFE;
} Unkstruct_8018A970_2; /* size = 0x100 */

typedef Unkstruct_801202A0 Unkstruct_8017FCD0_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_a1751a10: P3.40 T3 band rank 5485; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xa386];
    /* 0xa3aa */ u16 unkA3AA;
} Unkstruct_80186DDC_2; /* size = 0xa3ac */

typedef struct {
    /* Unkstruct_a27c4b3e: P3.40 T3 band rank 5487; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80180AA4_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_a35ea6fa: P3.40 T3 band rank 5491; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_801887A8_2; /* size = 0x4 */

typedef Unkstruct_8011D030 Unkstruct_8016BD78_7; /* size = 0x24 */

typedef Unkstruct_801202A0 Unkstruct_8017F404; /* size = 0x20 */

typedef struct {
    /* Unkstruct_a54518e3: P3.40 T3 band rank 5495; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801E83AC; /* size = 0x38 */

typedef struct {
    /* Unkstruct_a7599968: P3.40 T3 band rank 5500; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80180574_2; /* size = 0x14 */


typedef struct {
    /* Unkstruct_a8557fe5: P3.40 T3 band rank 5504; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80180294; /* size = 0x20 */

typedef Unkstruct_8018234C_3 Unkstruct_801829F8_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_a8c89c9d: P3.40 T3 band rank 5508; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801EE2C8; /* size = 0xe8 */


typedef struct {
    /* Unkstruct_aaca7857: P3.40 T3 band rank 5510; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CD5F8_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_aad02447: P3.40 T3 band rank 5511; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ void * unk20;
} Unkstruct_80182BA0; /* size = 0x24 */

typedef struct {
    /* Unkstruct_ac408868: P3.40 T3 band rank 5516; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ s32 unk34;
} Unkstruct_80180C10; /* size = 0x38 */

typedef Unkstruct_8017FD68 Unkstruct_8017FE1C; /* size = 0x24 */

typedef struct {
    /* Unkstruct_b0a15764: P3.40 T3 band rank 5530; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x8];
    /* 0x002c */ s32 unk2C;
} Unkstruct_801805B0; /* size = 0x30 */

typedef struct {
    /* Unkstruct_b0d4b1dd: P3.40 T3 band rank 5531; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801815AC_3; /* size = 0x38 */

typedef Unkstruct_8011DB30 Unkstruct_80184FB0_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_b1f82564: P3.40 T3 band rank 5537; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ s32 unk10;
} Unkstruct_800CB00C_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_b605bb91: P3.40 T3 band rank 5551; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x58];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ void * unkCC;
} Unkstruct_80188D78_2; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_b84f78d8: P3.40 T3 band rank 5553; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_80180270; /* size = 0x74 */

typedef Unkstruct_8017F858_2 Unkstruct_80186434_3; /* size = 0x20 */

typedef struct {
    /* Unkstruct_ba4ba333: P3.40 T3 band rank 5558; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80181A4C_4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_ba8dbe56: P3.40 T3 band rank 5559; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x4];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ s32 unk14;
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_8017FA24; /* size = 0x1c */

typedef struct {
    /* Unkstruct_bacd6784: P3.40 T3 band rank 5561; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8018465C_2; /* size = 0x38 */

typedef Unkstruct_801E4C48 Unkstruct_801EA188; /* size = 0x2c */

typedef struct {
    /* Unkstruct_bd84df41: P3.40 T3 band rank 5566; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0x10];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80183228_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_bd92f711: P3.40 T3 band rank 5567; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CB30C; /* size = 0x1c */

typedef struct {
    /* Unkstruct_bd994a66: P3.40 T3 band rank 5568; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0xa];
    /* 0x000c */ s32 unkC;
} Unkstruct_8017E7E8_4; /* size = 0x10 */

typedef Unkstruct_8016E7C8 Unkstruct_8016E7C8_3; /* size = 0x10 */

typedef Unkstruct_8018234C_3 Unkstruct_8018B23C_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_c00caab0: P3.40 T3 band rank 5577; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80184914_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_c0ca44db: P3.40 T3 band rank 5579; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c8];
    /* 0x01c8 */ s16 unk1C8;
    /* 0x01ca */ u8 pad1CA[0x2];
} Unkstruct_800CCDB0_2; /* size = 0x1cc */

typedef struct {
    /* Unkstruct_c1d4477c: P3.40 T3 band rank 5581; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017FABC; /* size = 0x74 */

typedef struct {
    /* Unkstruct_c34e3aeb: P3.40 T3 band rank 5585; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80183884; /* size = 0x38 */

typedef struct {
    /* Unkstruct_c4294734: P3.40 T3 band rank 5589; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
} Unkstruct_801831FC; /* size = 0x8 */

typedef Unkstruct_8016E7C8 Unkstruct_80184350_3; /* size = 0x10 */

typedef Unkstruct_8017EC90_2 Unkstruct_8017ED48; /* size = 0xf0 */

typedef Unkstruct_801202A0 Unkstruct_8018CB70; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_c95458b0: P3.40 T3 band rank 5607; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80184084_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_ca28b908: P3.40 T3 band rank 5609; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0xa];
    /* 0x000c */ u16 unkC;
    /* 0x000e */ u8 padE[0x2];
} Unkstruct_800335B8; /* size = 0x10 */

typedef struct {
    /* Unkstruct_cb5ac82d: P3.40 T3 band rank 5612; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20e];
    /* 0x020e */ u16 unk20E;
    /* 0x0210 */ u16 unk210;
    /* 0x0212 */ u16 unk212;
} Unkstruct_80183B64; /* size = 0x214 */

typedef struct {
    /* Unkstruct_cc40fe5d: P3.40 T3 band rank 5615; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x4];
    /* 0x0008 */ u16 unk8;
    /* 0x000a */ u8 padA[0x4];
    /* 0x000e */ u16 unkE;
} Unkstruct_80014028; /* size = 0x10 */

typedef Unkstruct_80180CD4 Unkstruct_80182E80; /* size = 0x8 */

typedef Unkstruct_80136A94 Unkstruct_80181408_2; /* size = 0x54 */

typedef struct {
    /* Unkstruct_ce438861: P3.40 T3 band rank 5622; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x54];
    /* 0x0064 */ s32 unk64;
} Unkstruct_801806B8_3; /* size = 0x68 */

typedef struct {
    /* Unkstruct_cea7cc16: P3.40 T3 band rank 5625; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_8018087C; /* size = 0xe8 */

typedef Unkstruct_8016E7C8 Unkstruct_80184928_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_cf3b5d23: P3.40 T3 band rank 5629; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CBC40; /* size = 0x1c */

typedef struct {
    /* Unkstruct_d030260c: P3.40 T3 band rank 5631; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CAF94_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_d0a5c680: P3.40 T3 band rank 5632; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
} Unkstruct_80181E0C; /* size = 0x68 */

typedef struct {
    /* Unkstruct_d111b193: P3.40 T3 band rank 5634; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_8018107C_2; /* size = 0x1c */

typedef Unkstruct_801202A0 Unkstruct_8017BF70_2; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_d233d88d: P3.40 T3 band rank 5639; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x62];
    /* 0x0086 */ u16 unk86;
} Unkstruct_80185D04; /* size = 0x88 */

typedef struct {
    /* Unkstruct_d2ed620f: P3.40 T3 band rank 5642; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x10];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017E114; /* size = 0x20 */

typedef struct {
    /* Unkstruct_d35a31f4: P3.40 T3 band rank 5645; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2e];
    /* 0x0064 */ s32 unk64;
} Unkstruct_801A6D90; /* size = 0x68 */

typedef struct {
    /* Unkstruct_d477cbe6: P3.40 T3 band rank 5647; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8001CA1C; /* size = 0x24 */

typedef Unkstruct_8016E7C8 Unkstruct_80181A58; /* size = 0x10 */

typedef struct {
    /* Unkstruct_d4eaeb79: P3.40 T3 band rank 5651; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_801830F4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_d6133306: P3.40 T3 band rank 5656; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80181700; /* size = 0x14 */

typedef struct {
    /* Unkstruct_d695333b: P3.40 T3 band rank 5658; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017F7E4; /* size = 0x2c */

typedef struct {
    /* Unkstruct_d69646b2: P3.40 T3 band rank 5659; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x4c];
    /* 0x0070 */ u16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_80182CA4_3; /* size = 0x74 */

typedef struct {
    /* Unkstruct_d7646d1d: P3.40 T3 band rank 5663; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_801F1AC8; /* size = 0x2c */

typedef Unkstruct_801202A0 Unkstruct_80182658; /* size = 0x100 */

typedef Unkstruct_8018234C_3 Unkstruct_801865DC_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_ded48017: P3.40 T3 band rank 5681; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8018762C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_dfaf010e: P3.40 T3 band rank 5687; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017FB98; /* size = 0x4 */

typedef Unkstruct_801202A0 Unkstruct_80185794; /* size = 0x100 */

typedef struct {
    /* Unkstruct_e1f25d01: P3.40 T3 band rank 5694; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017E51C_4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_e24b6e5e: P3.40 T3 band rank 5696; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80181F5C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_e279798b: P3.40 T3 band rank 5698; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801E8440; /* size = 0xe8 */

typedef Unkstruct_8018A8B8 Unkstruct_8018B29C; /* size = 0x100 */

typedef struct {
    /* Unkstruct_e3e7bd8d: P3.40 T3 band rank 5701; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_801829C8; /* size = 0x74 */

typedef struct {
    /* Unkstruct_e4f18ea5: P3.40 T3 band rank 5705; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8018B1B4_3; /* size = 0x24 */

typedef Unkstruct_8011D030 Unkstruct_8017D890_4; /* size = 0x24 */

typedef struct {
    /* Unkstruct_e6a5be59: P3.40 T3 band rank 5708; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
} Unkstruct_8017E2B8; /* size = 0x8 */

typedef struct {
    /* Unkstruct_e83062c1: P3.40 T3 band rank 5711; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80184B70; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_e9ba0887: P3.40 T3 band rank 5716; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017FCFC_3; /* size = 0x14 */

typedef Unkstruct_8016D1D8_6 Unkstruct_8016D1D8_7; /* size = 0x1c */

typedef struct {
    /* Unkstruct_ecd81b24: P3.40 T3 band rank 5725; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801829AC; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_ee578f80: P3.40 T3 band rank 5734; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x28];
    /* 0x0028 */ u16 unk28;
    /* 0x002a */ u8 pad2A[0x26];
    /* 0x0050 */ s32 unk50;
} Unkstruct_800CB400; /* size = 0x54 */

typedef struct {
    /* Unkstruct_ee69dd42: P3.40 T3 band rank 5735; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6c];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_8017F198; /* size = 0x74 */

typedef struct {
    /* Unkstruct_eecf07a7: P3.40 T3 band rank 5737; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xac];
    /* 0x00b0 */ s32 unkB0;
} Unkstruct_801E5580; /* size = 0xb4 */

typedef struct {
    /* Unkstruct_f0183730: P3.40 T3 band rank 5743; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80180B90_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_f08d36f7: P3.40 T3 band rank 5746; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017DE08_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_f3c79518: P3.40 T3 band rank 5755; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801EF624; /* size = 0x38 */

typedef Unkstruct_8016E7C8 Unkstruct_8016E7C8_4; /* size = 0x10 */

typedef struct {
    /* Unkstruct_f615df36: P3.40 T3 band rank 5764; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ u16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_801833D4_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_f8634248: P3.40 T3 band rank 5772; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x40];
    /* 0x0064 */ s32 unk64;
} Unkstruct_80183E48; /* size = 0x68 */


typedef struct {
    /* 0x0000 */ s16 off00;
    /* 0x0002 */ s16 off02;
    /* 0x0004 */ s16 off04;
    /* 0x0006 */ s16 off06;
    /* 0x0008 */ u16 off08;
    /* 0x000a */ s16 off0A;
    /* 0x000c */ u16 off0C;
    /* 0x000e */ u8 padE[0x12];
} Ent8018DE64; /* size = 0x20 */

typedef Unkstruct_8018234C_3 Unkstruct_801844D4_4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_fc72510f: P3.40 T3 band rank 5788; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s16 unk6;
} Unkstruct_80188034_2; /* size = 0x8 */

typedef Unkstruct_8018000C Unkstruct_8017FE64_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_ff027315: P3.40 T3 band rank 5796; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x14];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CAF9C; /* size = 0x24 */

typedef struct {
    /* Unkstruct_05ccffc7: P3.40 T3 band rank 5805; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_80181720_4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_07610043: P3.40 T3 band rank 5806; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_8017EAEC_3; /* size = 0x24 */

typedef Unkstruct_8017DC9C Unkstruct_8017E654_3; /* size = 0x74 */

typedef struct {
    /* Unkstruct_0cde848a: P3.40 T3 band rank 5810; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x27];
    /* 0x0027 */ u8 unk27;
} Unkstruct_8018094C_3; /* size = 0x28 */

typedef struct {
    /* Unkstruct_10244dc8: P3.40 T3 band rank 5813; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017FBD8_2; /* size = 0x18 */

typedef struct {
    /* Unkstruct_10a280d4: P3.40 T3 band rank 5814; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa0];
    /* 0x00a0 */ s8 unkA0;
    /* 0x00a1 */ u8 padA1[0x3];
} Unkstruct_8017EA50; /* size = 0xa4 */

typedef struct {
    /* Unkstruct_12f4908f: P3.40 T3 band rank 5818; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_801859D0; /* size = 0x4 */

typedef struct {
    /* Unkstruct_15923234: P3.40 T3 band rank 5823; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8018C9E8; /* size = 0x14 */

typedef struct {
    /* Unkstruct_220216ff: P3.40 T3 band rank 5835; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80181EA0_4; /* size = 0x14 */

typedef Unkstruct_8017DE18_2 Unkstruct_80181E30_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_28e4ba3c: P3.40 T3 band rank 5838; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_800CB370; /* size = 0x4 */

typedef struct {
    /* Unkstruct_2f7233a9: P3.40 T3 band rank 5841; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017DCB0; /* size = 0x18 */

typedef struct {
    /* Unkstruct_32ba887b: P3.40 T3 band rank 5843; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017F3F4_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_34d6e6b7: P3.40 T3 band rank 5844; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80185E98_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_35bee02b: P3.40 T3 band rank 5846; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ u16 unk6;
} Unkstruct_80020598; /* size = 0x8 */

typedef struct {
    /* Unkstruct_3606fb45: P3.40 T3 band rank 5847; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80160138; /* size = 0x4 */

typedef struct {
    /* Unkstruct_361a3d84: P3.40 T3 band rank 5848; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017E654_4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_36bcf844: P3.40 T3 band rank 5850; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80180EAC_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_36e45215: P3.40 T3 band rank 5851; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_801807D8; /* size = 0x4 */

typedef struct {
    /* Unkstruct_3c630874: P3.40 T3 band rank 5858; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80180488; /* size = 0x14 */

typedef struct {
    /* Unkstruct_3d7ccc89: P3.40 T3 band rank 5859; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017EFFC; /* size = 0x4 */

typedef struct {
    /* Unkstruct_3f0a4cc8: P3.40 T3 band rank 5861; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_800CAFD4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_3ff429e3: P3.40 T3 band rank 5864; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5e];
    /* 0x005e */ u8 unk5E;
    /* 0x005f */ u8 pad5F[0x1];
} Unkstruct_8017FF7C; /* size = 0x60 */

typedef struct {
    /* Unkstruct_433844ff: P3.40 T3 band rank 5868; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5e];
    /* 0x005e */ u16 unk5E;
} Unkstruct_8017EDF4_2; /* size = 0x60 */

typedef struct {
    /* Unkstruct_e2ba16ca: P3.40 T3 band rank 6121; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_801816CC;
typedef Unkstruct_801816CC Unkstruct_8018266C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_558eb5f6: P3.40 T3 band rank 5876; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_800CB134; /* size = 0x4 */

typedef struct {
    /* Unkstruct_5862dcf2: P3.40 T3 band rank 5879; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_80186D00; /* size = 0x60 */

typedef struct {
    /* Unkstruct_63c7ef84: P3.40 T3 band rank 5882; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80180878; /* size = 0x38 */

typedef Unkstruct_80185E98_3 Unkstruct_80188C28_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_647c9409: P3.40 T3 band rank 5884; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x27];
    /* 0x0027 */ u8 unk27;
} Unkstruct_801844AC_4; /* size = 0x28 */

typedef struct {
    /* Unkstruct_66b2a61d: P3.40 T3 band rank 5885; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_80182EB4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_e8a51f11: P3.40 T3 band rank 6129; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_801815DC;
typedef Unkstruct_801815DC Unkstruct_8018257C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_77fb6bb9: P3.40 T3 band rank 5894; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_800CB270; /* size = 0x4 */

typedef struct {
    /* Unkstruct_88a5f226: P3.40 T3 band rank 6046; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017F01C_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_8d76f4e4: P3.40 T3 band rank 6049; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ s32 unk0;
    /* 0x0004 */ u8 pad4[0x2];
    /* 0x0006 */ s8 unk6;
    /* 0x0007 */ u8 pad7[0x1];
} Unkstruct_80181D94; /* size = 0x8 */

typedef struct {
    /* Unkstruct_8e12c8f4: P3.40 T3 band rank 6050; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80186A68; /* size = 0x24 */

typedef struct {
    /* Unkstruct_8f2f23a6: P3.40 T3 band rank 6053; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8018558C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_8f780fae: P3.40 T3 band rank 6055; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80183094_4; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_9a84f960: P3.40 T3 band rank 6064; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
} Unkstruct_80181B48_2; /* size = 0x38 */

typedef Unkstruct_8018094C_3 Unkstruct_8018094C_4; /* size = 0x28 */

typedef struct {
    /* Unkstruct_a6c59d84: P3.40 T3 band rank 6071; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
} Unkstruct_80182D04_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_abe85f83: P3.40 T3 band rank 6074; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_8017ECC0_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_afaf3b87: P3.40 T3 band rank 6076; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_80180110_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_b1865209: P3.40 T3 band rank 6079; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
} Unkstruct_80180584_2; /* size = 0x14 */

typedef Unkstruct_80126B58 Unkstruct_80171260_2; /* size = 0x218 */

typedef struct {
    /* Unkstruct_b43e8b62: P3.40 T3 band rank 6084; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_8017DB08; /* size = 0x100 */

typedef struct {
    /* Unkstruct_b6ab884d: P3.40 T3 band rank 6085; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
} Unkstruct_801805D4_3; /* size = 0x38 */

typedef Unkstruct_801202A0 Unkstruct_80183E3C; /* size = 0x9c */

typedef struct {
    /* Unkstruct_bc7d1c02: P3.40 T3 band rank 6092; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_8017E1FC; /* size = 0x14 */

typedef struct {
    /* Unkstruct_bea15431: P3.40 T3 band rank 6093; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_800CB2C8; /* size = 0x4 */

typedef Unkstruct_801202A0 Unkstruct_80182400; /* size = 0x4 */

typedef struct {
    /* Unkstruct_c5091b81: P3.40 T3 band rank 6098; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017F600; /* size = 0x4 */

typedef struct {
    /* Unkstruct_c7af14a8: P3.40 T3 band rank 6102; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80188B00_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_c9f8e50e: P3.40 T3 band rank 6103; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10a];
    /* 0x010a */ s16 unk10A;
} Unkstruct_8017F2DC; /* size = 0x10c */

typedef struct {
    /* Unkstruct_cccb6cbd: P3.40 T3 band rank 6104; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
} Unkstruct_80186A30_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_d4652835: P3.40 T3 band rank 6113; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_801817D8_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_d50ed1ff: P3.40 T3 band rank 6114; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_800CB804; /* size = 0x4 */

typedef struct {
    /* Unkstruct_d556b2e3: P3.40 T3 band rank 6115; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_8017DE80_5; /* size = 0x1c */

typedef struct {
    /* Unkstruct_d91f0b88: P3.40 T3 band rank 6118; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ u8 unkA;
    /* 0x000b */ u8 padB[0x1];
} Unkstruct_800CC0A0; /* size = 0xc */

typedef struct {
    /* Unkstruct_dbb05d45: P3.40 T3 band rank 6119; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_80182758; /* size = 0x4 */

typedef Unkstruct_80126B58 Unkstruct_8017E8AC; /* size = 0x218 */

typedef struct {
    /* Unkstruct_e54246df: P3.40 T3 band rank 6124; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_80184A5C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_e681f3f3: P3.40 T3 band rank 6125; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x80];
    /* 0x0080 */ s32 unk80;
} Unkstruct_80186A68_2; /* size = 0x84 */

typedef struct {
    /* Unkstruct_ea41ffc1: P3.40 T3 band rank 6131; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_8017E070_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_ed6b9364: P3.40 T3 band rank 6133; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017FD54_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_eee9b8ce: P3.40 T3 band rank 6134; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ s16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017E754_2; /* size = 0x30 */

typedef struct {
    /* Unkstruct_f210f055: P3.40 T3 band rank 6135; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8017F6B4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_f483c954: P3.40 T3 band rank 6139; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x36];
    /* 0x0036 */ s16 unk36;
} Unkstruct_8017EE74_2; /* size = 0x38 */

typedef Unkstruct_8016A290_8 Unkstruct_8016A290_9; /* size = 0x24 */

typedef Unkstruct_801202A0 Unkstruct_8017F2D0; /* size = 0x4 */

typedef struct {
    /* Unkstruct_f66b4593: P3.40 T3 band rank 6144; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x2];
} Unkstruct_8017F858_3; /* size = 0x30 */

typedef struct {
    /* Unkstruct_f94a7cc8: P3.40 T3 band rank 6148; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
} Unkstruct_801801E8; /* size = 0x8 */

typedef struct {
    /* Unkstruct_fa5d3825: P3.40 T3 band rank 6151; 2 TNC sites in 2 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
} Unkstruct_80180570_2; /* size = 0x5c */

typedef struct {
    /* Unkstruct_00de5650: P3.40 T3 band rank 6157; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8018379C_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_014a5c48: P3.40 T3 band rank 6159; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80182D3C_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_01e21ba1: P3.40 T3 band rank 6160; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe0];
    /* 0x00e0 */ s32 unkE0;
} Unkstruct_8017EDC0; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_01faff01: P3.40 T3 band rank 6161; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8018095C_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_02aec6cf: P3.40 T3 band rank 6163; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ s16 unk0;
    /* 0x0002 */ u8 pad2[0x2];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_80182CB8_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_02c30c25: P3.40 T3 band rank 6164; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80181388_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_02fc4654: P3.40 T3 band rank 6166; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80183B9C; /* size = 0x38 */

typedef struct {
    /* Unkstruct_036d9afc: P3.40 T3 band rank 6167; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_80180F8C_2; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_03bc8c94: P3.40 T3 band rank 6168; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
    /* 0x0008 */ u8 pad8[0x2c];
    /* 0x0034 */ s32 unk34;
} Unkstruct_8017FC10_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_03e91513: P3.40 T3 band rank 6169; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017E818; /* size = 0x2c */

typedef struct {
    /* Unkstruct_05dffe72: P3.40 T3 band rank 6177; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017FC64_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_0619a90a: P3.40 T3 band rank 6178; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8018C730; /* size = 0x68 */

typedef struct {
    /* Unkstruct_06dcba57: P3.40 T3 band rank 6180; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1f0];
    /* 0x01f0 */ s16 unk1F0;
    /* 0x01f2 */ u8 pad1F2[0x2];
} Unkstruct_80038A58; /* size = 0x1f4 */

typedef struct {
    /* Unkstruct_3413977c: P3.40 T3 band rank 6399; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017BE9C_5;
typedef Unkstruct_8017BE9C_5 Unkstruct_8017C340_2; /* size = 0x14 */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017BEBC_24; /* size = 0x14 */

typedef Unkstruct_801202A0 Unkstruct_80186D6C; /* size = 0x74 */

typedef struct {
    /* Unkstruct_0881aec4: P3.40 T3 band rank 6189; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8018A124; /* size = 0x20 */

typedef struct {
    /* Unkstruct_09e2bc6a: P3.40 T3 band rank 6192; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_801800DC; /* size = 0x68 */

typedef struct {
    /* Unkstruct_0a8ab2df: P3.40 T3 band rank 6195; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x6];
    /* 0x000a */ s16 unkA;
} Unkstruct_80180E34_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_0a950371: P3.40 T3 band rank 6196; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017DE30_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_0b238577: P3.40 T3 band rank 6200; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
} Unkstruct_801A54F0; /* size = 0x10 */

typedef struct {
    /* Unkstruct_0be55dbe: P3.40 T3 band rank 6202; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017F1B4; /* size = 0x68 */

typedef struct {
    /* Unkstruct_0df208bf: P3.40 T3 band rank 6211; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8018D4B4_2; /* size = 0x60 */

typedef struct {
    /* Unkstruct_0e36dcdf: P3.40 T3 band rank 6212; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10a];
    /* 0x010a */ s16 unk10A;
} Unkstruct_80180458; /* size = 0x10c */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017DF34_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_0e9bdb85: P3.40 T3 band rank 6216; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_80183A88; /* size = 0x8 */

typedef struct {
    /* Unkstruct_0f506ee8: P3.40 T3 band rank 6220; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
} Unkstruct_800CCE80_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_52bb97a1: P3.40 T3 band rank 6542; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017CD9C_6;
typedef Unkstruct_8017CD9C_6 Unkstruct_8017D960_6; /* size = 0x14 */

typedef struct {
    /* Unkstruct_101d63a3: P3.40 T3 band rank 6227; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80184A00; /* size = 0x20 */

typedef struct {
    /* Unkstruct_10ab5a63: P3.40 T3 band rank 6230; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ u16 unk1A;
} Unkstruct_8018854C_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_11136f52: P3.40 T3 band rank 6233; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_801805B0_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_116ee020: P3.40 T3 band rank 6236; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe8];
    /* 0x00e8 */ s32 unkE8;
} Unkstruct_80180C90_2; /* size = 0xec */


typedef struct {
    /* Unkstruct_11e694eb: P3.40 T3 band rank 6239; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s16 unkDC;
    /* 0x00de */ u8 padDE[0x2];
    /* 0x00e0 */ s16 unkE0;
    /* 0x00e2 */ u8 padE2[0x2];
} Unkstruct_80187AD0; /* size = 0xe4 */

typedef struct {
    /* Unkstruct_12495824: P3.40 T3 band rank 6241; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017EE10_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_6b96b46b: P3.40 T3 band rank 6676; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xa];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017DB28_3;
typedef Unkstruct_8017DB28_3 Unkstruct_8017E6EC_5; /* size = 0x10 */

typedef struct {
    /* Unkstruct_1320e843: P3.40 T3 band rank 6245; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_80183130_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_13f6e7b4: P3.40 T3 band rank 6249; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_8018893C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_4e4a1452: P3.40 T17 drift rank 406; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
} Unkstruct_80181BA8_3;
typedef Unkstruct_80181BA8_3 Unkstruct_801849AC_2;
typedef Unkstruct_801849AC_2 Unkstruct_8018E428_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_1697d860: P3.40 T3 band rank 6260; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd0];
    /* 0x00d0 */ void * unkD0;
    /* 0x00d4 */ void * unkD4;
} Unkstruct_8017DB54; /* size = 0xd8 */

typedef struct {
    /* Unkstruct_17784fd3: P3.40 T3 band rank 6263; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_800CB2AC_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_17901ab6: P3.40 T3 band rank 6264; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x50];
    /* 0x0070 */ s16 unk70;
    /* 0x0072 */ u8 pad72[0x2];
} Unkstruct_80181C80_3; /* size = 0x74 */

typedef struct {
    /* Unkstruct_1799a621: P3.40 T3 band rank 6265; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_80182964_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_17a90231: P3.40 T3 band rank 6266; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017E84C_2; /* size = 0x2c */

typedef struct {
    /* Unkstruct_17e659bc: P3.40 T3 band rank 6268; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_801825C8_2; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_182f0180: P3.40 T3 band rank 6270; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10a];
    /* 0x010a */ s16 unk10A;
} Unkstruct_8017D588_6; /* size = 0x10c */

typedef struct {
    /* Unkstruct_18519416: P3.40 T3 band rank 6272; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_80180F8C_3; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_185e4fd5: P3.40 T3 band rank 6274; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xf8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_801808DC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_18ac663a: P3.40 T3 band rank 6277; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_80181C58_2; /* size = 0x24 */


typedef struct {
    /* Unkstruct_1d80cdca: P3.40 T17 drift rank 377; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x40];
    /* 0x0040 */ u32 unk40;
} Unkstruct_80181BA8_2;
typedef Unkstruct_80181BA8_2 Unkstruct_80181CF4_2;
typedef Unkstruct_80181CF4_2 Unkstruct_80185E38_2; /* size = 0x44 */

typedef struct {
    /* Unkstruct_192bba8f: P3.40 T3 band rank 6282; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ void * unk64;
    /* 0x0068 */ u8 pad68[0x96];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8018B410; /* size = 0x100 */

typedef struct {
    /* Unkstruct_195f9745: P3.40 T3 band rank 6284; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_80181638_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_1a525947: P3.40 T3 band rank 6287; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x18];
    /* 0x0076 */ u16 unk76;
} Unkstruct_80183B0C; /* size = 0x78 */

typedef struct {
    /* Unkstruct_1aa2417d: P3.40 T3 band rank 6289; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xfc];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801895CC; /* size = 0x104 */

typedef struct {
    /* Unkstruct_1b2df5c8: P3.40 T3 band rank 6292; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017E3F8_3; /* size = 0x4 */

typedef struct {
    /* Unkstruct_1c207bcb: P3.40 T3 band rank 6294; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_8018445C_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_1d62d714: P3.40 T3 band rank 6298; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x198];
    /* 0x0198 */ s32 unk198;
} Unkstruct_8017F2C4; /* size = 0x19c */

typedef struct {
    /* Unkstruct_1d6fa1bd: P3.40 T3 band rank 6299; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_800D1E9C; /* size = 0x8 */

typedef struct {
    /* Unkstruct_1e1c2815: P3.40 T3 band rank 6301; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x54];
    /* 0x0054 */ s16 unk54;
    /* 0x0056 */ u8 pad56[0x2];
} Unkstruct_80183C1C; /* size = 0x58 */

typedef struct {
    /* Unkstruct_2001957c: P3.40 T3 band rank 6305; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CD708_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_21369e31: P3.40 T3 band rank 6312; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017E038; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2172b7dd: P3.40 T3 band rank 6313; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ s16 unkC;
    /* 0x000e */ s16 unkE;
} Unkstruct_80039308_5; /* size = 0x10 */

typedef struct {
    /* Unkstruct_27601871: P3.40 T3 band rank 6336; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_8017E804;
typedef Unkstruct_8017E804 Unkstruct_8017E93C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_2189dff1: P3.40 T3 band rank 6315; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8018AFDC_2; /* size = 0x60 */

typedef struct {
    /* Unkstruct_21df2541: P3.40 T3 band rank 6317; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
} Unkstruct_80182254_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_22d7c17a: P3.40 T3 band rank 6323; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017FB40; /* size = 0x68 */


typedef Unkstruct_8011D030 Unkstruct_8017E640; /* size = 0x4 */

typedef struct {
    /* Unkstruct_25a5d9e7: P3.40 T3 band rank 6331; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_801A5C44_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_271cf682: P3.40 T3 band rank 6334; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 pad8[0x6];
    /* 0x000e */ u16 unkE;
} Unkstruct_8017F900_2; /* size = 0x10 */

typedef Unkstruct_8017D174 Unkstruct_8017D174_4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_28df99cc: P3.40 T3 band rank 6342; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xf8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80185464_2; /* size = 0x100 */

typedef struct {
    /* Unkstruct_29101133: P3.40 T3 band rank 6343; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2c];
    /* 0x002c */ u16 unk2C;
    /* 0x002e */ u8 pad2E[0x52];
    /* 0x0080 */ s32 unk80;
} Unkstruct_8017E0FC_2; /* size = 0x84 */

typedef struct {
    /* Unkstruct_2a78d7b7: P3.40 T3 band rank 6347; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017C954_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_2aab1b8b: P3.40 T3 band rank 6348; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017C730_4; /* size = 0x14 */

typedef Unkstruct_80181CF4_2 Unkstruct_80185944_2; /* size = 0x44 */

typedef Unkstruct_801202A0 Unkstruct_8018BDB0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2babeabc: P3.40 T3 band rank 6353; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x12];
    /* 0x0036 */ u16 unk36;
} Unkstruct_80181AD0_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2c47d340: P3.40 T3 band rank 6357; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801809D4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2cdcc42a: P3.40 T3 band rank 6362; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801812AC_2; /* size = 0x38 */

typedef Unkstruct_80181FAC_2 Unkstruct_80181900; /* size = 0x4 */

typedef struct {
    /* Unkstruct_2e075587: P3.40 T3 band rank 6366; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_80180298_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_2e16f1a4: P3.40 T3 band rank 6369; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x5a];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8017E7EC; /* size = 0x60 */

typedef struct {
    /* Unkstruct_2f38175c: P3.40 T3 band rank 6376; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80181490_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_2f66803e: P3.40 T3 band rank 6377; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_8018BE74; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_2fc33421: P3.40 T3 band rank 6378; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x18];
    /* 0x0076 */ u16 unk76;
} Unkstruct_80183B0C_2; /* size = 0x78 */

typedef Pair_8013AD38 Unkstruct_8017CBC8; /* size = 0x4 */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017D604_5; /* size = 0x14 */

typedef struct {
    /* Unkstruct_305263bb: P3.40 T3 band rank 6382; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd8];
    /* 0x00d8 */ s32 unkD8;
    /* 0x00dc */ u8 padDC[0x1c];
    /* 0x00f8 */ s32 unkF8;
} Unkstruct_801A2318; /* size = 0xfc */

typedef struct {
    /* Unkstruct_31223b10: P3.40 T3 band rank 6385; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u8 pad2[0x4];
    /* 0x0006 */ s16 unk6;
} Unkstruct_8017F6E0_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_324e35a8: P3.40 T3 band rank 6391; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x12];
    /* 0x0028 */ s32 unk28;
} Unkstruct_8017EC68; /* size = 0x2c */

typedef Unkstruct_8017CD9C_6 Unkstruct_8017D960_7; /* size = 0x14 */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017BEBC_25; /* size = 0x14 */

typedef struct {
    /* Unkstruct_34f3dd1f: P3.40 T3 band rank 6403; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80182D0C_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_35265186: P3.40 T3 band rank 6405; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017E1AC_3; /* size = 0x18 */

typedef struct {
    /* Unkstruct_35300373: P3.40 T3 band rank 6406; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
    /* 0x0020 */ u8 pad20[0x56];
    /* 0x0076 */ u16 unk76;
} Unkstruct_80188150; /* size = 0x78 */

typedef struct {
    /* Unkstruct_353a3437: P3.40 T3 band rank 6407; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8018B648; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_35614c09: P3.40 T3 band rank 6408; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_80189D10; /* size = 0x4 */

typedef struct {
    /* Unkstruct_36dfff73: P3.40 T3 band rank 6412; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8018096C_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_37506614: P3.40 T3 band rank 6413; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_80183DE0_2; /* size = 0x1c */


typedef struct {
    /* Unkstruct_38864798: P3.40 T3 band rank 6416; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8018B798; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_3a31e14e: P3.40 T3 band rank 6420; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x100];
    /* 0x0104 */ u16 unk104;
    /* 0x0106 */ u8 pad106[0x2];
} Unkstruct_8018A61C_2; /* size = 0x108 */

typedef struct {
    /* Unkstruct_3a8af20b: P3.40 T3 band rank 6424; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_80180530_2; /* size = 0x1c */

typedef Unkstruct_801202A0 Unkstruct_80181F2C; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_3c771811: P3.40 T3 band rank 6434; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xc];
    /* 0x000c */ s32 unkC;
    /* 0x0010 */ u8 pad10[0x50];
    /* 0x0060 */ s32 unk60;
} Unkstruct_8017CF90; /* size = 0x64 */

typedef struct {
    /* Unkstruct_3ca638b8: P3.40 T3 band rank 6435; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
} Unkstruct_801840C0; /* size = 0x5c */

typedef struct {
    /* Unkstruct_3d67d0cd: P3.40 T3 band rank 6437; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80184A88_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_3da8254a: P3.40 T3 band rank 6438; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe0];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ u8 padE4[0x1c];
    /* 0x0100 */ s16 unk100;
    /* 0x0102 */ u8 pad102[0x2];
} Unkstruct_801808C4_2; /* size = 0x104 */

typedef struct {
    /* Unkstruct_3ecf0e4d: P3.40 T3 band rank 6446; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8018B780; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_3ed15a5d: P3.40 T3 band rank 6447; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u32 unk0;
    /* 0x0004 */ s32 unk4;
} Unkstruct_800CB00C_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_3f27a696: P3.40 T3 band rank 6451; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CB4F0; /* size = 0x24 */

typedef struct {
    /* Unkstruct_3f394dfd: P3.40 T3 band rank 6453; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_80184358; /* size = 0x68 */

typedef struct {
    /* Unkstruct_3f5eda85: P3.40 T3 band rank 6454; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017FA5C_2; /* size = 0x14 */

typedef Unkstruct_8015D380 Unkstruct_8015D380_7; /* size = 0x14 */

typedef struct {
    /* Unkstruct_3fa974a2: P3.40 T3 band rank 6457; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8018087C_2; /* size = 0x20 */

typedef Unkstruct_80181FAC_2 Unkstruct_8018393C; /* size = 0x4 */

typedef struct {
    /* Unkstruct_407693d1: P3.40 T3 band rank 6462; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0xc8];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_80181364; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_40a3aa17: P3.40 T3 band rank 6463; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x14];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x11];
    /* 0x0027 */ u8 unk27;
} Unkstruct_8017FBB0_3; /* size = 0x28 */

typedef Unkstruct_801202A0 Unkstruct_8017FCD0_4; /* size = 0x68 */

typedef Unkstruct_80181FAC_2 Unkstruct_80181E60; /* size = 0x4 */

typedef Unkstruct_80181FAC_2 Unkstruct_80185550; /* size = 0x4 */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017EC58_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_4352ecca: P3.40 T3 band rank 6477; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_8017EAD8_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_43eca610: P3.40 T3 band rank 6478; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801809D0_2; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_441b4103: P3.40 T3 band rank 6480; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1a];
    /* 0x001a */ s16 unk1A;
} Unkstruct_80185920_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_4439f769: P3.40 T3 band rank 6481; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8017FE78; /* size = 0x20 */

typedef struct {
    /* Unkstruct_44b51315: P3.40 T3 band rank 6483; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_8018CAF0_2; /* size = 0x8 */

typedef Unkstruct_80181CF4_2 Unkstruct_80184174_3; /* size = 0x44 */

typedef struct {
    /* Unkstruct_45a8ff1c: P3.40 T3 band rank 6489; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ u8 pad12[0x2];
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_80187288_3; /* size = 0x18 */

typedef struct {
    /* Unkstruct_4612380e: P3.40 T3 band rank 6492; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CCC54_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_4676a074: P3.40 T3 band rank 6494; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0x34];
    /* 0x0058 */ s32 unk58;
} Unkstruct_80180754; /* size = 0x5c */

typedef Unkstruct_8017DB28_3 Unkstruct_8017E97C_2; /* size = 0x10 */

typedef struct {
    /* Unkstruct_477a0e17: P3.40 T3 band rank 6498; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xd4];
    /* 0x00d4 */ s32 unkD4;
} Unkstruct_8017D7C8; /* size = 0xd8 */

typedef struct {
    /* Unkstruct_487226a9: P3.40 T3 band rank 6499; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_80182B30; /* size = 0x100 */

typedef struct {
    /* Unkstruct_48bd78e7: P3.40 T3 band rank 6500; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe0];
    /* 0x00e0 */ s32 unkE0;
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_801A293C; /* size = 0xe8 */

typedef struct {
    /* Unkstruct_494347ec: P3.40 T3 band rank 6502; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_80187110; /* size = 0x1c */

typedef Unkstruct_80181FAC_2 Unkstruct_8018A72C; /* size = 0x4 */

typedef Unkstruct_801849AC_2 Unkstruct_80185690_2; /* size = 0xc */

typedef Unkstruct_801202A0 Unkstruct_80185474; /* size = 0x38 */

typedef struct {
    /* Unkstruct_4c1de7d2: P3.40 T3 band rank 6512; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x24];
    /* 0x0024 */ s32 unk24;
} Unkstruct_8017F2B4_2; /* size = 0x28 */

typedef struct {
    /* Unkstruct_4c5d2d8b: P3.40 T3 band rank 6514; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_80185D04_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_4cbca845: P3.40 T3 band rank 6515; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017F9A8; /* size = 0x18 */

typedef struct {
    /* Unkstruct_4d2e4d41: P3.40 T3 band rank 6516; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017F5B4_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_4da6a097: P3.40 T3 band rank 6519; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80180150_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_4db0796f: P3.40 T3 band rank 6520; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xde];
    /* 0x00de */ u8 unkDE;
    /* 0x00df */ u8 padDF[0x1];
} Unkstruct_8017F07C; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_4fa57ada: P3.40 T3 band rank 6525; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ s32 unkC;
} Unkstruct_8001FC08; /* size = 0x10 */

typedef struct {
    /* Unkstruct_4fdd75c7: P3.40 T3 band rank 6526; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ s32 unk1C;
} Unkstruct_8018BF4C; /* size = 0x20 */

typedef struct {
    /* Unkstruct_508ef0ad: P3.40 T3 band rank 6529; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_80027C10_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_50e4ca73: P3.40 T3 band rank 6532; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x58];
    /* 0x0058 */ u16 unk58;
    /* 0x005a */ u16 unk5A;
} Unkstruct_80041354; /* size = 0x5c */

typedef struct {
    /* Unkstruct_50e9f891: P3.40 T3 band rank 6533; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_801891D0_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_512a9188: P3.40 T3 band rank 6534; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x15];
    /* 0x0015 */ u8 unk15;
    /* 0x0016 */ u8 pad16[0x2];
} Unkstruct_8017E770; /* size = 0x18 */


typedef Unkstruct_8017D174_2 Unkstruct_8017D174_5; /* size = 0x68 */

typedef Unkstruct_80181AD0_3 Unkstruct_801859F4_3; /* size = 0x38 */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017BEBC_26; /* size = 0x14 */

typedef struct Entry_8016E95C Unkstruct_8016E9EC_4; /* size = 0x8 */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017EB7C_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_53dda19e: P3.40 T3 band rank 6550; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
} Unkstruct_8003A0E4_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_53e0b5d7: P3.40 T3 band rank 6551; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ u16 unk5C;
    /* 0x005e */ u8 pad5E[0x1a];
    /* 0x0078 */ s32 unk78;
} Unkstruct_80186CA8; /* size = 0x7c */

typedef Unkstruct_801202A0 Unkstruct_801854D0; /* size = 0x38 */

typedef struct {
    /* Unkstruct_545430d2: P3.40 T3 band rank 6554; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80183940_2; /* size = 0x38 */

typedef Unkstruct_801202A0 Unkstruct_8018C6A4; /* size = 0x74 */

typedef struct {
    /* Unkstruct_55fd96a7: P3.40 T3 band rank 6561; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017FE08_2; /* size = 0x38 */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017D604_6; /* size = 0x14 */

typedef struct {
    /* Unkstruct_56418caf: P3.40 T3 band rank 6563; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ u32 unk1C;
    /* 0x0020 */ void * unk20;
} Unkstruct_80182938; /* size = 0x24 */


typedef struct {
    /* Unkstruct_56649365: P3.40 T3 band rank 6565; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5c];
    /* 0x005c */ s16 unk5C;
    /* 0x005e */ u8 pad5E[0x2];
} Unkstruct_8018AE6C_2; /* size = 0x60 */

typedef struct {
    /* Unkstruct_57162ba3: P3.40 T3 band rank 6566; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_800CCC54_3; /* size = 0x8 */

typedef struct {
    /* Unkstruct_5750c8af: P3.40 T3 band rank 6567; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1];
    /* 0x0001 */ u8 unk1;
    /* 0x0002 */ u8 unk2;
    /* 0x0003 */ u8 pad3[0x1];
} Unkstruct_8017EAD8_4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_58037c63: P3.40 T3 band rank 6568; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x198];
    /* 0x0198 */ s32 unk198;
} Unkstruct_8017F3E8; /* size = 0x19c */

typedef struct {
    /* Unkstruct_58689fbe: P3.40 T3 band rank 6571; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80180F60_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_586a5c08: P3.40 T3 band rank 6572; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ u16 unk6;
    /* 0x0008 */ u8 unk8;
    /* 0x0009 */ u8 pad9[0x3];
} Unkstruct_80039C70_2; /* size = 0xc */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017D604_7; /* size = 0x14 */

typedef Unkstruct_8011D030 Unkstruct_8017F0D0_2; /* size = 0x4 */

typedef Unkstruct_801849AC_2 Unkstruct_80186B70_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_5ad46320: P3.40 T3 band rank 6581; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u16 unk1A;
} Unkstruct_801A7C58_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_5ae53767: P3.40 T3 band rank 6582; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_801821D0_3; /* size = 0x1c */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017FB84_2; /* size = 0x14 */

typedef Unkstruct_80182F48_2 Unkstruct_80182554; /* size = 0x20 */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017DC70_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_5bdbcb7e: P3.40 T3 band rank 6588; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x1c];
    /* 0x0020 */ void * unk20;
} Unkstruct_801816A8_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_5c0a9ea6: P3.40 T3 band rank 6589; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
    /* 0x000c */ u8 padC[0x4];
    /* 0x0010 */ void * unk10;
} Unkstruct_8017CE58_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_5c790462: P3.40 T3 band rank 6591; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s32 unk4;
} Unkstruct_800CCBE4_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_5c9a1a28: P3.40 T3 band rank 6592; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ s16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ s16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80184298; /* size = 0x38 */

typedef struct {
    /* Unkstruct_5e04e69a: P3.40 T3 band rank 6601; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8018169C; /* size = 0x14 */

typedef struct {
    /* Unkstruct_5ea2b751: P3.40 T3 band rank 6602; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
} Unkstruct_801A4060_2; /* size = 0x1c */

typedef struct {
    /* Unkstruct_5ee2041d: P3.40 T3 band rank 6604; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x40];
    /* 0x0040 */ u32 unk40;
} Unkstruct_80182254_3; /* size = 0x44 */

typedef struct {
    /* Unkstruct_5ff880e9: P3.40 T3 band rank 6612; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_8017E9A8_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_60ab4b4e: P3.40 T3 band rank 6615; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
} Unkstruct_801820E4; /* size = 0x8 */

typedef struct {
    /* Unkstruct_6138f58c: P3.40 T3 band rank 6617; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801800DC_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_614d5c62: P3.40 T3 band rank 6618; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
} Unkstruct_801839EC; /* size = 0x14 */

typedef struct {
    /* Unkstruct_6162c31f: P3.40 T3 band rank 6620; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xa];
    /* 0x000a */ u16 unkA;
    /* 0x000c */ u8 padC[0xd2];
    /* 0x00de */ u16 unkDE;
} Unkstruct_8017DE90_2; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_6209d383: P3.40 T3 band rank 6625; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u32 unk18;
    /* 0x001c */ u8 pad1C[0x4];
    /* 0x0020 */ u32 unk20;
} Unkstruct_80185354; /* size = 0x24 */

typedef struct {
    /* Unkstruct_624e1cdf: P3.40 T3 band rank 6627; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x5e];
    /* 0x005e */ u16 unk5E;
    /* 0x0060 */ u8 pad60[0x9e];
    /* 0x00fe */ u16 unkFE;
} Unkstruct_8018BAD8; /* size = 0x100 */

typedef Unkstruct_8017BE9C_5 Unkstruct_8017D5C0_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_63db543e: P3.40 T3 band rank 6633; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_80182750; /* size = 0x38 */

typedef struct {
    /* Unkstruct_6414d7ef: P3.40 T3 band rank 6634; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_8018043C_3; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_6524b1ae: P3.40 T3 band rank 6639; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x94];
    /* 0x0098 */ s16 unk98;
    /* 0x009a */ u8 pad9A[0x2];
} Unkstruct_801E584C; /* size = 0x9c */

typedef struct {
    /* Unkstruct_6553cb2a: P3.40 T3 band rank 6641; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe0];
    /* 0x00e0 */ s32 unkE0;
} Unkstruct_80185864_3; /* size = 0xe4 */


typedef struct {
    /* Unkstruct_686ddcc6: P3.40 T3 band rank 6649; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ s32 unk1C;
} Unkstruct_80182950; /* size = 0x20 */

typedef struct {
    /* Unkstruct_688d9aac: P3.40 T3 band rank 6651; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_80183F64; /* size = 0x4 */

typedef struct {
    /* Unkstruct_69c28c66: P3.40 T3 band rank 6655; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xfc];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ u8 padFE[0x2];
} Unkstruct_80180898; /* size = 0x100 */

typedef struct {
    /* Unkstruct_69cb7daf: P3.40 T3 band rank 6656; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xb8];
    /* 0x00b8 */ u16 unkB8;
    /* 0x00ba */ u8 padBA[0x2];
} Unkstruct_8017DA30_5; /* size = 0xbc */

typedef struct {
    /* Unkstruct_69cbab7f: P3.40 T3 band rank 6657; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017FE08_3; /* size = 0x68 */

typedef struct {
    /* Unkstruct_6a63036c: P3.40 T3 band rank 6662; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xdc];
    /* 0x00dc */ s32 unkDC;
} Unkstruct_80188484; /* size = 0xe0 */

typedef struct {
    /* Unkstruct_6a88e8e5: P3.40 T3 band rank 6664; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
} Unkstruct_8018B978; /* size = 0xd0 */

typedef struct {
    /* Unkstruct_6aab2bf0: P3.40 T3 band rank 6665; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x18];
    /* 0x001c */ u32 unk1C;
} Unkstruct_8018D8A8; /* size = 0x20 */

typedef struct {
    /* Unkstruct_6b0ef22c: P3.40 T3 band rank 6669; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe4];
    /* 0x00e4 */ s32 unkE4;
} Unkstruct_80185A3C_2; /* size = 0xe8 */

typedef Unkstruct_801202A0 Unkstruct_80183104; /* size = 0x10c */

typedef struct {
    /* Unkstruct_6b77f64c: P3.40 T3 band rank 6674; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1e];
    /* 0x001e */ u16 unk1E;
} Unkstruct_800CB0C8_3; /* size = 0x20 */

/* provenance (restruct-drift): T17 (P3.40) drift defs by tools/restruct.py --decide-band --ranks drift --write, ordered by drift rank, last ran at 4771a92d03 (P3.40 T17.c6); generator retired P3.45 T6; hand-edited since */
typedef struct {
    /* Unkstruct_8a49cd6b: P3.40 T17 drift rank 1; 5 TNC sites in 1 bodies; struct map 5 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ u8 padA[0x2];
} Unkstruct_80182AC0_2; /* size = 0xc */

typedef struct {
    /* Unkstruct_c758f14a: P3.40 T17 drift rank 2; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ void * unk20;
} Unkstruct_80182AC0_3; /* size = 0x24 */


typedef struct {
    /* Unkstruct_cebbadb2: P3.40 T17 drift rank 42; 28 TNC sites in 1 bodies; struct map 30 sites; restruct.py --decide-band */
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
    /* Unkstruct_a937a51b: P3.40 T17 drift rank 44; 27 TNC sites in 1 bodies; struct map 27 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ u8 pad8[0x2];
    /* 0x000a */ s16 unkA;
    /* 0x000c */ u8 padC[0x2];
    /* 0x000e */ s16 unkE;
    /* 0x0010 */ u8 pad10[0x10];
    /* 0x0020 */ s32 unk20;
    /* 0x0024 */ u8 pad24[0xd8];
    /* 0x00fc */ s16 unkFC;
    /* 0x00fe */ s16 unkFE;
} Unkstruct_801902EC; /* size = 0x100 */

typedef struct {
    /* Unkstruct_ab1026c3: P3.40 T17 drift rank 47; 3 TNC sites in 1 bodies; struct map 9 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
    /* 0x0068 */ u8 pad68[0x64];
    /* 0x00cc */ void * unkCC;
    /* 0x00d0 */ void * unkD0;
} Unkstruct_80181C18_4; /* size = 0xd4 */

typedef Unkstruct_80182E70 Unkstruct_80182E70_2; /* size = 0x28 */


typedef struct {
    /* Unkstruct_18355f7f: P3.40 T17 drift rank 84; 12 TNC sites in 3 bodies; struct map 12 sites; restruct.py --decide-band */
    /* 0x0000 */ u16 unk0;
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ u8 pad6[0x2];
} Unkstruct_8016A290_2; /* size = 0x8 */


typedef Unkstruct_8017DC9C Unkstruct_8017DC9C_2; /* size = 0x74 */

typedef struct {
    /* Unkstruct_0d405251: P3.40 T17 drift rank 97; 10 TNC sites in 1 bodies; struct map 23 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ u32 unk4;
    /* 0x0008 */ u8 pad8[0x8];
    /* 0x0010 */ u16 unk10;
    /* 0x0012 */ u16 unk12;
} Unkstruct_8018D98C_2; /* size = 0x14 */

typedef Unkstruct_8017DC9C Unkstruct_8017D6B0_2; /* size = 0x74 */

typedef Unkstruct_8011D030 Unkstruct_8017C154_2; /* size = 0x34 */

typedef Unkstruct_80191C50 Unkstruct_4409ae68; /* size = 0x100 */

typedef Unkstruct_80181FAC_2 Unkstruct_80181854_2; /* size = 0x4 */

typedef struct {
    /* Unkstruct_b98c58c0: P3.40 T17 drift rank 170; 6 TNC sites in 1 bodies; struct map 6 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10];
    /* 0x0010 */ s16 unk10;
    /* 0x0012 */ s16 unk12;
    /* 0x0014 */ s16 unk14;
    /* 0x0016 */ u8 pad16[0x32];
    /* 0x0048 */ s32 unk48;
    /* 0x004c */ s32 unk4C;
    /* 0x0050 */ s32 unk50;
} Unkstruct_801A3BCC_2; /* size = 0x54 */

typedef struct {
    /* Unkstruct_cdaf74f9: P3.40 T17 drift rank 171; 6 TNC sites in 1 bodies; struct map 31 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ s16 unkA;
    /* 0x000c */ s16 unkC;
    /* 0x000e */ u8 padE[0xa];
    /* 0x0018 */ s16 unk18;
    /* 0x001a */ s16 unk1A;
    /* 0x001c */ s16 unk1C;
    /* 0x001e */ s16 unk1E;
    /* 0x0020 */ void * unk20;
    /* 0x0024 */ u8 pad24[0xe];
    /* 0x0032 */ u16 unk32;
    /* 0x0034 */ s32 unk34;
} Unkstruct_8001E378; /* size = 0x38 */

typedef Unkstruct_8017C8B0 Unkstruct_8017C8B0_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_0796654b: P3.40 T17 drift rank 299; 3 TNC sites in 1 bodies; struct map 3 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x4];
    /* 0x0004 */ s16 unk4;
    /* 0x0006 */ s16 unk6;
    /* 0x0008 */ s16 unk8;
    /* 0x000a */ u8 padA[0x2];
} Unkstruct_80183748; /* size = 0xc */

typedef Unkstruct_80181BA8_2 Unkstruct_801849AC_3; /* size = 0x44 */

typedef struct {
    /* Unkstruct_075703b3: P3.40 T17 drift rank 361; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x40];
    /* 0x0040 */ u32 unk40;
} Unkstruct_80183D30_2; /* size = 0x44 */

typedef struct {
    /* Unkstruct_18d781a3: P3.40 T17 drift rank 371; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
} Unkstruct_80185944_3; /* size = 0xc */

typedef struct {
    /* Unkstruct_1f9fee4a: P3.40 T17 drift rank 379; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x64];
    /* 0x0064 */ s32 unk64;
} Unkstruct_8017E038_2; /* size = 0x68 */

typedef Unkstruct_80183D30_2 Unkstruct_8018AB20_2; /* size = 0x44 */

typedef Unkstruct_80185944_3 Unkstruct_80185E38_3; /* size = 0xc */

typedef struct {
    /* Unkstruct_453f8d3e: P3.40 T17 drift rank 394; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x40];
    /* 0x0040 */ u32 unk40;
} Unkstruct_8018AA98_2; /* size = 0x44 */

typedef struct {
    /* Unkstruct_4c74c997: P3.40 T17 drift rank 403; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x27];
    /* 0x0027 */ u8 unk27;
} Unkstruct_801844AC_5; /* size = 0x28 */

typedef struct {
    /* Unkstruct_78620143: P3.40 T17 drift rank 427; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
} Unkstruct_8017E5C4; /* size = 0x4 */

typedef struct {
    /* Unkstruct_79f2176d: P3.40 T17 drift rank 429; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_801806B8_2; /* size = 0x14 */

typedef Unkstruct_80181FAC_2 Unkstruct_801819A0; /* size = 0x4 */

typedef struct {
    /* Unkstruct_94700cd1: P3.40 T17 drift rank 462; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x40];
    /* 0x0040 */ u32 unk40;
} Unkstruct_8018E428_3; /* size = 0x44 */

typedef struct {
    /* Unkstruct_9972750c: P3.40 T17 drift rank 463; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xcc];
    /* 0x00cc */ s32 unkCC;
    /* 0x00d0 */ s32 unkD0;
} Unkstruct_9972750c; /* size = 0xd4 */

typedef struct {
    /* Unkstruct_a6760af9: P3.40 T17 drift rank 472; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
} Unkstruct_80184174; /* size = 0xc */

typedef Unkstruct_80181BA8_3 Unkstruct_80181CF4_3; /* size = 0xc */

typedef struct {
    /* Unkstruct_baf62a4b: P3.40 T17 drift rank 478; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
} Unkstruct_8018AA98_3; /* size = 0xc */

typedef struct {
    /* Unkstruct_d34a6733: P3.40 T17 drift rank 495; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x8];
    /* 0x0008 */ s32 unk8;
} Unkstruct_80183D30_3;

typedef Unkstruct_80183D30_3 Unkstruct_8018AB20_3; /* size = 0xc */

typedef struct {
    /* Unkstruct_dbfaeffc: P3.40 T17 drift rank 500; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x2];
    /* 0x0002 */ u16 unk2;
    /* 0x0004 */ u8 pad4[0x30];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017FB40_2; /* size = 0x38 */

typedef struct {
    /* Unkstruct_e7933bc6: P3.40 T17 drift rank 504; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x40];
    /* 0x0040 */ u32 unk40;
} Unkstruct_80185690_3;

typedef Unkstruct_80185690_3 Unkstruct_80186B70_3; /* size = 0x44 */

typedef struct {
    /* Unkstruct_e7d442e6: P3.40 T17 drift rank 505; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x6];
    /* 0x0006 */ s16 unk6;
} Unkstruct_80187E08_2; /* size = 0x8 */

typedef struct {
    /* Unkstruct_f5f3bc95: P3.40 T17 drift rank 515; 2 TNC sites in 1 bodies; struct map 2 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CB574; /* size = 0x24 */

typedef struct {
    /* Unkstruct_0ab9aa3f: P3.40 T17 drift rank 538; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x1c];
    /* 0x001c */ u32 unk1C;
} Unkstruct_800193B8_2; /* size = 0x20 */

typedef struct {
    /* Unkstruct_23e1abc7: P3.40 T17 drift rank 571; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017E038_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_32464c12: P3.40 T17 drift rank 591; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_80186938_3; /* size = 0x14 */

typedef struct {
    /* Unkstruct_36f4e782: P3.40 T17 drift rank 597; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x10a];
    /* 0x010a */ u16 unk10A;
} Unkstruct_801854B8_2; /* size = 0x10c */

typedef struct {
    /* Unkstruct_4999a523: P3.40 T17 drift rank 616; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0xe];
    /* 0x000e */ s16 unkE;
} Unkstruct_80181F4C; /* size = 0x10 */

typedef struct {
    /* Unkstruct_7e01af3e: P3.40 T17 drift rank 681; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017FE08_4; /* size = 0x38 */

typedef struct {
    /* Unkstruct_9c29301b: P3.40 T17 drift rank 731; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ u16 unk18;
    /* 0x001a */ u8 pad1A[0x2];
} Unkstruct_8017EAD8_5; /* size = 0x1c */

typedef struct {
    /* Unkstruct_ae63d731: P3.40 T17 drift rank 756; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ s16 unk12;
} Unkstruct_801A3BCC_4; /* size = 0x14 */

typedef struct {
    /* Unkstruct_af88dbe2: P3.40 T17 drift rank 758; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CAF94_3; /* size = 0x24 */

typedef struct {
    /* Unkstruct_bc948750: P3.40 T17 drift rank 778; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_8017FB40_3; /* size = 0x38 */

typedef struct {
    /* Unkstruct_d42fa227: P3.40 T17 drift rank 806; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s32 unk18;
} Unkstruct_800CC024_3; /* size = 0x1c */

typedef struct {
    /* Unkstruct_daa42f59: P3.40 T17 drift rank 812; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ Blk16_956C *unk20;
} Unkstruct_800CB458_2; /* size = 0x24 */

typedef Unkstruct_801844AC_5 Unkstruct_801844AC_6; /* size = 0x28 */

typedef struct {
    /* Unkstruct_ed2dd796: P3.40 T17 drift rank 842; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x12];
    /* 0x0012 */ u16 unk12;
} Unkstruct_800CCD50_2; /* size = 0x14 */

typedef struct {
    /* Unkstruct_ee12f875: P3.40 T17 drift rank 844; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x18];
    /* 0x0018 */ s32 unk18;
} Unkstruct_800CC024_4; /* size = 0x1c */

typedef struct {
    /* Unkstruct_ef7597c3: P3.40 T17 drift rank 848; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x34];
    /* 0x0034 */ u16 unk34;
    /* 0x0036 */ u8 pad36[0x2];
} Unkstruct_801800DC_3; /* size = 0x38 */


typedef struct {
    /* Unkstruct_fb5661bd: P3.40 T17 drift rank 861; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x20];
    /* 0x0020 */ s32 unk20;
} Unkstruct_800CB0C8_2; /* size = 0x24 */

typedef struct {
    /* Unkstruct_fd6b5377: P3.40 T17 drift rank 864; 1 TNC sites in 1 bodies; struct map 1 sites; restruct.py --decide-band */
    /* 0x0000 */ u8 pad0[0x76];
    /* 0x0076 */ s16 unk76;
} Unkstruct_8017ED28; /* size = 0x78 */

/* --- lift_types.py --census (P38 T5.1.c2, batch all) --- */
typedef DRM DM_27058_t;
typedef DRM DM_27200_t;
typedef struct { u32 tag; u8 r0, g0, b0, code; u32 xy0, xy1, xy2; } F3_249F0_t;
typedef struct { u32 tag; u8 r0, g0, b0, code; u32 xy0, uv0, xy1, uv1, xy2, uv2; } FT3_25CBC_t;
typedef Face2 Face_26514_t;
typedef Face3 Face_268D0_t;
typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    u16 x0, y0;
    u8 u0, v0; u16 clut;
    u8 r1, g1, b1, p1;
    u16 x1, y1;
    u8 u1, v1; u16 tpage;
    u8 r2, g2, b2, p2;
    u16 x2, y2;
    u8 u2, v2; u16 pad26;
} GT3_26514_t;
typedef struct {
    u32 tag;
    u8 r0, g0, b0, code;
    u16 x0, y0;
    u8 u0, v0; u16 clut;
    u8 r1, g1, b1, p1;
    u16 x1, y1;
    u8 u1, v1; u16 tpage;
    u8 r2, g2, b2, p2;
    u16 x2, y2;
    u8 u2, v2; u16 pad26;
    u8 r3, g3, b3, p3;
    u16 x3, y3;
    u8 u3, v3; u16 pad32;
} GT4_268D0_t;
typedef DVECTOR P2_CBA44_t;
typedef struct { s32 w[4]; P2_CBA44_t o; } Base_CBA44_t;
typedef SVECTOR SV_CBA44_t;
typedef Src_249F0_t Src_27058_t;

/* PsyQ 4.0 libgpu DISPENV (tools/reference/psyq-sdk/PSX/INCLUDE/LIBGPU.H:342-348), the SetDefDispEnv return type (3.44 T8.c5).
 * disp/screen are RECTs, spelled inline: RECT lives in src/shared/engine_types.h, which not every space includes. */
typedef struct { struct { s16 x, y, w, h; } disp, screen; u8 isinter, isrgb24, pad12, pad13; } DISPENV; /* PsyQ pad0, pad1 (offset names, G62) */

#endif /* STRUCT_TYPES_H */
