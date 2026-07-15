#include "common.h"
#include "../shared/engine_core.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
struct Ent_801506A4 {
    unsigned short unk0;    /* 0x0 */
    char pad[0x5A];
    unsigned short unk5C;   /* 0x5C */
    char pad2[0x12];
    short unk70;            /* 0x70 */
};
typedef struct {
    u8   pad00[0x12];
    u16  unk12;              /* 0x12 */
} Sub_80155800_80155800;
typedef struct {
    u8            pad00[0x20];
    Sub_80155800_80155800 *unk20;     /* 0x20 */
    u8            pad24[0x44 - 0x24];
    s32           unk44;     /* 0x44 */
    u8            pad48[0xB8 - 0x48];
    u16           unkB8;     /* 0xB8 */
    u8            padBA[0x1A8 - 0xBA];
    u8            unk1A8;    /* 0x1A8 */
    u8            unk1A9;    /* 0x1A9 */
    u8            unk1AA;    /* 0x1AA */
    u8            pad1AB[0x1C0 - 0x1AB];
    u8            unk1C0;    /* 0x1C0 */
    u8            pad1C1[0x234 - 0x1C1];
    u8            unk234;    /* 0x234 */
} Ent_80155800_80155800;
struct Sub_8015CD20 {
    u8 pad0[0x12];
    u16 unk12;      /* +0x12 */
};
struct Ent_8015CD20 {
    u16 unk0;       /* +0x00 */
    u8 pad2[0x1E];
    struct Sub_8015CD20 *unk20;  /* +0x20 */
    u8 pad24[0x94];
    s16 unkB8;      /* +0xB8 */
    u8 pad1BA[0x102];
    s8 unk1BC;      /* +0x1BC */
    u8 pad1BD[0x77];
    s32 unk234;     /* +0x234 */
};
typedef struct {
    u16 f0;
    u8 pad0[0x4e];
    int f50;
    u8 pad1[0x14];
} Ent_80164930_80164930;
typedef struct { u8 d[8]; } __attribute__((packed, aligned(1))) B8_80165140;
typedef struct { u8 d[4]; } __attribute__((packed, aligned(1))) B4_80165140;
typedef struct { B8_80165140 a; B4_80165140 b; s32 used; } Slot_80165140;
typedef struct { u16 h[6]; } Rec_80166690_80166690;   /* 12-byte sub-table record (stride 0xC) */
typedef struct {
    short v0, v1, v2, pad06, w0, w1, w2, pad0E;          /* 0x00..0x0F */
    short v3, v4, v5, pad16, w3, w4, w5, pad1E;          /* 0x10..0x1F */
    u8 c00, c01, c02, pad23;                             /* 0x20 */
    u8 c10, c11, c12, pad27;                             /* 0x24 */
    u8 c20, c21, c22, pad2B;                             /* 0x28 */
    u8 c30, c31, c32, pad2F;                             /* 0x2C */
    int tag;                                             /* 0x30 -> struct size 0x34; tag lands at sp+0x40 */
} Frame_80166690_80166690;
typedef struct { s32 m[8]; } Mat_80167540; /* 0x20 bytes */
struct Src_80167540 {
    u8 pad0[0x34];
    Mat_80167540 mat;          /* 0x34 */
};
struct Sub2_80167540 {
    u8 pad0[0x44];
    s32 unk44;        /* 0x44 */
};
struct Node_80167540 {
    /* 0x0 */ u16 unk0;
    u8 pad2[0x4];
    /* 0x6 */ s16 unk6;
    u8 pad8[0x2];
    /* 0xA */ s16 unkA;
    u8 padC[0x2];
    /* 0xE */ s16 unkE;
    u8 pad10[0x10];
    /* 0x20 */ struct Src_80167540 *unk20;
    u8 pad24[0x28];
    /* 0x4C */ struct Sub2_80167540 *unk4C;
};
struct Entity_80167540 {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ u16 unk2;
    u8 pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    u8 pad14[0x8];
    /* 0x1C */ s32 unk1C;
    u8 pad20[0x10];
    /* 0x30 */ s32 unk30;
    /* 0x34 */ struct Node_80167540 *unk34;
    /* 0x38 */ Mat_80167540 mat;
};
typedef struct { s16 x, y, z, pad; } SVEC_80167AE0;
struct Fr_80167AE0 {
    u8   matrix[0x20];                    /* 0x00 -> sp+0x10 */
    SVEC_80167AE0 v[4];                            /* 0x20 -> sp+0x30 */
    struct { u8 r, g, b, pad; } col[4];   /* 0x40 -> sp+0x50 */
    u32  code;                            /* 0x50 -> sp+0x60 */
};
typedef struct {
    u16 f00, f02, f04, f06;
    s16 f08;
    u16 f0a, f0c, f0e, f10, f12, f14, f16;
    u8  f18, f19, f1a, f1b, f1c, f1d, f1e, f1f, f20, f21, f22, f23;
    u32 f24;
} Thing_80168828_80168828;
typedef struct { s16 x, y, z, pad; } SVEC_8016A290;
struct Fr_8016A290 {
    SVEC_8016A290 center;                          /* 0x00 -> sp+0x10 */
    SVEC_8016A290 diff;                            /* 0x08 -> sp+0x18 */
    s32  pos[3];                          /* 0x10 -> sp+0x20 */
    s32  _pad1c;                          /* 0x1C -> sp+0x2C */
    s16  mtx[32];                         /* 0x20 -> sp+0x30 */
    SVEC_8016A290 v[4];                            /* 0x60 -> sp+0x70 */
    struct { u8 r, g, b, pad; } col[4];   /* 0x80 -> sp+0x90 */
    u32  code;                            /* 0x90 -> sp+0xA0 */
};
typedef struct SubB_8016A73C { char pad[0x20]; int unk20; } SubB_8016A73C;
typedef struct SubA_8016A73C { char pad[0x34]; SubB_8016A73C *unk34; } SubA_8016A73C;
typedef struct Mat_8016A73C { int w[8]; } Mat_8016A73C;
typedef struct Obj_8016A73C {
    short unk0;
    short unk2;
    short unk4;
    short unk6;
    short unk8;
    short unkA;
    short unkC;
    short unkE;
    char pad10[0x24];   /* 0x10 .. 0x33 */
    SubA_8016A73C *unk34;         /* 0x34 */
    Mat_8016A73C mat;             /* 0x38 .. 0x57 */
} Obj_8016A73C;
typedef struct { char b[4]; } W_8016BFD0;
typedef struct { s16 x, y, z; } Vec3_8016BFD0;
typedef struct {
    s16 m[9];    /* 0x00 */
    s16 pad;     /* 0x12 */
    s32 t[3];    /* 0x14, 0x18, 0x1c */
    s32 rest[8]; /* 0x20..0x3f */
} Mtx_8016BFD0;
typedef struct {
    u8 f0, f1, f2, f3;
    struct { s16 a, b, c, d, e, g; } ent[16];
} Blk_8016CF04_8016CF04;                /* 4 + 16*12 = 0xC4 stride */
typedef struct { short vx, vy, vz, pad; } SVECTOR_8016E7C8;                 /* 0x08 */
typedef struct { short m[3][3]; short pad; s32 t[3]; } MATRIX_8016E7C8;     /* 0x20 */
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;
struct Entry_8016E95C {
    u8 f0;
    u8 f1;
    u8 pad[0x1e];
};
typedef void (*Handler)(struct Entry_8016E95C *);
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_8018CA0C;
extern u8 D_8018C97C;
extern u8 D_8018C958;
extern u8 D_8018C934;
extern u8 D_8018C9E8;
extern u8 D_8018C9C4;
extern u8 D_8018C9A0;
extern u8 D_8018C910;
extern void func_80145934(void);
extern u8 D_8018CA9C;
extern u8 D_8018CA78;
extern u8 D_8018CA54;
extern u8 D_8018CA30;
extern void func_80145A2C(void);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
extern void func_80162120(void);
extern void func_80029124(s32, s32);
extern s32 func_80165A50(s32);
extern void func_80029514(s32);
extern u8 D_800AF630[];
extern u8 D_80078EC0;
extern s32 D_80126B58;
extern s32 func_80028FBC(void);
extern s32 func_80029000(void);
extern s32 func_80028D9C(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80145BF8(void);
extern s32 func_800291B4(s32 arg);
extern void func_800291A0(s32, s32);
extern void func_80145C54(void);
extern s32 func_80145CEC();
extern s32 func_80029178(s32 arg);
extern void func_80146014(s32 a0);
extern unsigned char D_8018BE94[];
extern unsigned char D_8018BEC4[];
extern unsigned char D_8018BF14[];
extern unsigned char D_8018BF44[];
extern unsigned char D_8018BF74[];
extern void func_80145EE8(s32 param_1);
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_80146074(void);
extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0(void);
extern void func_8014607C(void);
extern s32 *D_80126B78;
extern u8 D_80078EC1;
extern s32 D_80078EC8;
extern s32 D_80126B9C;
extern s32 D_8011F730;
extern u16 D_801152B8;
extern u16 D_8012693A;
extern u8 D_80126BE0[];
extern u8 D_801150F0[];
extern void *memcpy(void *dst, const void *src, u32 n);
extern void func_80146FC4(s32 a0);
extern void func_80150A70(s32 a0);
extern void func_80147098(s32 *a0);
extern void func_8014A638(s32 arg0);
extern s32  func_80155458(s32 a0);
extern s32  func_80029104(void);
extern void func_80029344(void);
extern void func_8014ADE0(s32 a0);
extern void func_8014B350(s32 a0);
extern void func_8014B7A4(s16 *param_1);
extern s32 func_80161D58(s32 a0);
extern void func_80161A90(s32 a0);
extern void func_8014B504(u16 *a0);
extern void func_80149BEC(s32 a0);
extern void func_8014B5D0(s32 *a0);
extern void func_8014C99C(u8 *a0);
extern void func_8014B190(s32 s0);
extern void func_80148648(s32 a0, s32 a1);
extern s32 func_80149228(s32 a0);
extern void func_8014A59C(s32 a0);
extern void func_8016F14C(void *a0);
extern void func_80154418(void *a0);
extern void func_80154BE4(s32 a0);
extern void func_80165694(s32 arg0);
extern void func_801654A8(s32 a0);
extern void func_8014A680(s32 a0);
extern void func_8014A6A8(s32 a0);
extern void func_8014A71C(s32 a0);
extern void func_80172588(s32 *a0);
extern void func_801473DC(s32 *a0);
extern void func_80015978(s32 a0, s32 *a1);
extern void (*D_8018BFC4[])(void *);
extern u8 D_80126BA4;
extern s32 D_80127098;
extern s32 D_80127094;
extern s32 D_80127090;
extern void func_80146534(void);
extern void func_8001D074(s32 a0, s32 a1);
extern void func_80146554(void);
extern void func_80146578(void);
extern void func_8001CFDC(s32, s32);
extern void func_8014659C(void);
extern void func_8001D074(s32, s32);
extern void func_801465C0(void);
extern void func_801465E4(void);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern s32 D_8011F9D0;
extern s32 func_80146608(s32 a0, s32 a1, s32 a2, s32 a3, s16 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13);
extern void func_801466B4(u16 a0, s32 a1, s32 a2, s32 a3, s32 arg5);
extern s32 D_8011F750;
extern s32 D_8011F754;
extern u8 * func_801468C8(s32 arg0, u8 arg1);
extern s32 D_8011D030;
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80146924(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg5);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80146994(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_801469C8(int a0, void *a1, int a2, int a3, u16 arg5, int arg6, int arg7, int arg8);
extern s32 func_80146B9C(void *a0);
extern void func_80146AB4(s16 a0, s32 a1, s16 a2, s16 a3, u16 a4, s32 a5, s32 a6);
extern u16 D_8011DA28;
extern s32 func_80146B9C(void * arg0);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_80146CA0(void *a0);
extern void func_80146CB4(void *a0);
extern void func_80146CC8(s32 a0);
extern void func_80146D30(s32 a0);
extern void func_80146D80(s32 *a0);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146D90(s32 a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146DF8(s32 *a0, s32 a1, s32 a2, s32 a3, s32 t0);
extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146E98(s32 a0);
extern void func_80015954(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146F58(s32 a0, s32 a1);
extern void func_80146EC0(s32 a0, s32 a1, s32 a2, s32 a3);
extern s16 func_8012A68C(void);
extern s16 func_8012A758(void);
extern void func_8004978C(s16 *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern u8 D_80126DB0[];
extern u16 D_80126DB6;
extern void func_8014704C(s32 *a0);
extern s32 func_80147054(void *a0);
extern void func_80147060(u8 * a0);
extern void func_8014706C(void *arg0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80147084(s32 *a0);
extern void func_8014708C(void *arg0);
extern s32 func_801470A0(void *a0);
extern void func_801470AC(s32 *a0);
extern void func_801470B4(s32 arg0);
extern void func_801470C0(s32 a0);
extern void func_80147118(s32 a0);
extern s16 D_80126BB8;
extern s16 D_80126BBA;
extern s16 D_80126BBC;
extern void func_80147264(s32 a0);
extern void func_80147290(void);
extern void func_801472B4(void *a0);
extern s32 func_801472C8(struct S *a0);
extern void *D_8012707C;
extern void func_801472DC(void);
extern void func_801472F0(void *a0);
extern void func_80147364(u16, s32);
extern void func_80147300(u16 arg0);
extern void func_80147324(s32 arg0);
extern void func_801473EC(s32 *a0);
extern void func_80147460(s32 a0);
extern void func_80147514();
extern void func_80147628(s32 a0);
extern void func_80147478(s32 a0);
extern void func_801474D8(s32 *a0);
extern void func_801474EC(s32 *a0);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_800129CC(s32 a0, s32 a1);
extern void func_80147514(s32 arg0);
extern void func_80013F3C(s32 a0);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);
extern void func_80147718(s32 a0);
extern void func_80147788(void *a0, s32 a1);
extern void func_801477A8(void *a0, s32 a1);
extern void func_801477C8(void *a0, s32 a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80147814(s32 a0, s32 a1);
extern void func_80147928(int a0, int a1);
extern void func_8014799C(int a0, int a1);
extern void func_80147A10(int a0, int a1);
extern void func_80147860(int a0, int a1, int a2, int a3);
extern void func_80147948(s32 a0, s32 a1, s32 a2);
extern void func_801479BC(s32 a0, s32 a1, s32 a2);
extern void func_80147A30(s32 a0, s32 a1, s32 a2);
extern void func_801478B8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147948(int a0, int a1, int a2);
extern void func_801479BC(int a0, int a1, int a2);
extern void func_80147A30(int a0, int a1, int a2);
extern void func_80147AD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80147A84(s32 arg0);
extern void func_80147C30(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80147AAC(s32 arg0);
extern void func_80147CC8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80147B5C(s32 a0, void *a1);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147D38(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern void func_80147B18(s32 a0);
extern void func_80147B5C(s32 arg0, void *arg1);
extern void func_80147C30(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147DC0(s32 a0, s32 a1);
extern void func_80147D38(s32 a0, s32 a1, s32 a2, s32 a3, void * a4);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_80147E44(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80147F78(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80147F50(s32 arg0);
extern void func_80148038(s32 a0, s32 a1);
extern s32 ratan2(s32 a0, s32 a1);
extern s32 csqrt(s32 a0);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_80148094(int param_1, short *param_2, int *param_3);
extern void func_801485B8(s32 a0, s32 a1, s32 a2);
extern void func_801484B0(s32 a0, s32 a1);
extern s32 func_80154358(void *a0);
extern void func_801484E8(s32 a0, s32 a1);
extern void func_80148534(s32 a0, s32 a1);
extern void func_8014856C(s32 a0, s32 a1);
extern void func_801485B8(s32 arg0, s32 arg1, s32 arg2);
extern void func_80148634(void *a0);
extern u8 D_800B9A64;
extern s32 func_80014DC0();
extern s32 func_80014D68();
extern s32 func_80014D94();
extern s32 func_80014CF8();
extern void func_800120DC();
extern s32 func_800CF8B4();
extern u16 func_801487F4(s32 *a0);
extern u16 func_80148800(s32 *a0);
extern u8 func_8014880C(s32 *a0);
extern u16 func_80148818(s32 *a0);
extern s32 func_80047D3C(s32 a0);
extern s32 func_80148824(void *arg0);
extern s32 func_801488A8(u8 *a0);
extern s32 func_8014891C(s32 a0);
extern s32 func_80148980(u8 *a0);
extern s32 func_801489E8(s32 a0);
extern s32 func_80148A48(s32 a0);
extern int func_80148AFC(void *a0);
extern void func_80148AAC(u8 *a0);
extern s32 func_80148C18(void);
extern s32 func_80148C20(s32 a0, s16 a1);
extern s32 func_80148C34(s32 a0, s32 a1);
extern s32 func_80148C4C(s32 a0, s32 a1);
extern s32 func_80148C64(s32 a0, s32 a1);
extern s32 func_80148C7C(void);
extern s32 func_80148C84(s32 a0, s32 a1);
extern s32 func_80148C9C(s32 a0, s32 a1);
extern s32 func_80148CB4(s32 a0, s32 a1);
extern s32 func_80148CCC(s32 a0, s32 a1);
extern s32 func_80148CE4(void);
extern s32 func_80148CEC(void);
extern s32 func_80148CF4(s32 a0, s32 a1);
extern s32 func_80148D0C(s32 a0, s32 a1);
extern s32 func_80148D24(void *a0, int a1);
extern s32 func_80148D3C(void);
extern s32 func_80148F60(void);
extern s32 func_80148F68(s32 a0);
extern s32 func_80148F74(s32 a0);
extern s32 func_80148F80(s32 a0);
extern s32 func_80148F8C(s32 a0);
extern s32 func_80148F98(void);
extern s32 func_80148FA0(s32 a0);
extern s32 func_80148FAC(s32 a0);
extern s32 func_80148FB8(s32 a0);
extern s32 func_80148FC4(s32 a0);
extern s32 func_80148FD0(void);
extern s32 func_80148FD8(void);
extern s32 func_80148FE0(s32 a0);
extern s32 func_80148FEC(s32 a0);
extern s32 func_80148FF8(s32 a0);
extern s32 func_80149004(void);
extern void func_8014900C(s32 *a0);
extern void func_80149020(s32 *a0);
extern void func_80149034(s32 *a0);
extern void func_80149048(s32 *a0);
extern void func_8014905C(u8 *a0);
extern void func_801490E0(s32 *a0, s16 a1);
extern void func_801490E8(s32 *a0, s16 a1);
extern void func_801490F0(s32 *a0, s16 a1);
extern void func_80149078(s32 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern void func_801490F8(s32 a0, s32 a1);
extern s32 func_801491C4(s32 a0);
extern s32 func_80149184(s32 a0);
extern s32 D_801151D4;
extern void func_80149204(s32 *a0);
extern void func_80149210(s32 a0, s32 a1);
extern s32 func_80149284(s32 *a0, s32 a1);
extern void func_80149350(s32 arg0);
extern void func_80149290(s32 a0);
extern void func_8012F14C(s32);
extern void func_80149374(s32 arg0, s32 arg1);
extern void func_801493D0(s32 param_1, s32 param_2, s32 param_3);
extern void func_8012F038(s32);
extern void func_8014942C(s32 arg0);
extern void func_8012EF70(s32 a0, s32 a1);
extern void func_80149544(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012EFB8(s32 a0);
extern void func_80149584(s32 arg0, s32 arg1, s32 arg2);
extern void func_8014964C(s32 param_1, s32 param_2);
extern s32 func_801496D4(void *a0);
extern void func_8015AD08();
extern void func_80149704(void);
extern void func_8015ACC4();
extern void func_80149724(void);
extern u8 D_80078EBF;
extern s32 func_80149744(struct S_80149744 *a0);
extern void func_8015F7A0();
extern void func_80149788(void);
extern void func_801653B8();
extern void func_80149864(void);
extern s16 currentLocationId;
extern s32 func_8016F1AC(void);
extern s32 func_80149884(void);
extern void func_80160B00();
extern void func_801498C0(void);
extern s32 func_80149AA8(s32 *a0);
extern s32 func_80149B54(s32 *a0);
extern void func_80146750(void *a0);
extern s32 func_801498E0(s32 *a0);
extern s32 func_8012E5CC(s32 a0, s32 a1, s32 a2);
extern void func_80147364(u16 a0, s32 a1);
extern s32 func_800CCF28(s32 a0);
extern u8 D_80126B5C;
extern s32 func_80149954(s32 s0);
extern s32 func_80149A64(s32 *a0);
extern void func_8015DAC4(s32 *a0);
extern void func_8015554C(s32 *a0);
extern void func_80149AD4(s32 *a0);
extern void func_80149B14(s32 *a0);
extern u8 func_8014BEF8(void);
extern s32 func_80149B54(s32 * arg0);
extern void func_8015DE24(s32 *a0);
extern void func_80157510(s32 *a0);
extern void func_80149BAC(s32 *a0);
extern s32 func_80029178(s32 a0);
extern s32 func_80149C08(s32 arg0);
extern void func_801577C8();
extern void func_80149C94(void);
extern void func_80157D20(void);
extern void func_80149CB4(void);
extern s32 func_80149CD4(s32 a0);
extern u8 func_8014B5B8(s32 *a0);
extern s32 func_80149D10(s32 a0);
extern s32 func_80149E94(s32 a0);
extern s32 func_80149DD8(s32 a0);
extern s32 func_80149D9C(s32 a0);
extern u8 D_801202A0[];
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_8018C08C[];
extern u8 D_80078E78[];
extern s32 func_80149FB0(s32 a0);
extern s32 func_80135260(s32, s32, s32, s32);
extern void func_8014A1B0(s32 a0, s32 a1);
extern s32 func_8014A048(s32 param_1);
extern u16 func_80156370(u16 a0);
extern void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
extern void func_8015D4B4();
extern void func_8014A218(void);
extern s32 func_8014C278(s32 a0, s32 a1, s32 a2);
extern s32 func_8014C2B0(void *a0, void *a1, s32 a2);
extern s32 func_8014A238(s32 arg0);
extern s32 func_8014A2E4(s32 a0);
extern void func_8014A380(s32 a0, s32 a1);
extern s16 D_801152B0;
extern s16 D_801152B4;
extern s32 func_8014A3E0(struct S_8014A3E0 *a0);
extern s32 func_8014A454(s32 a0);
extern s32 func_8014A4B4(void *a0);
extern void func_8015EDD4();
extern void func_8014A4FC(void);
extern s32 func_8014A674(s32 *a0);
extern s32 func_8014A69C(s32 *a0);
extern s32 func_8014A6C4(s32 a0);
extern void func_8015E184();
extern void func_8014A830(void);
extern s32 func_80029AF4(void);
extern s32 func_8014A850(s32 param_1);
extern void func_8014AA04(s32 a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern s32 func_80165A20(s32 a0);
extern void func_8014AB7C();
extern void func_8014AC10();
extern void func_8014AA28(void);
extern void func_8014AB5C(void);
extern void func_80162CCC(void);
extern void func_8014AB7C(s32 arg0);
extern void func_8014ABF0(void);
extern void func_80016714(void *a0, s32 a1);
extern void func_8014AC10(s32 arg0);
extern void func_8014ACC0(s32 a0, s32 a1);
extern void func_8014AD30(s32 a0, u16 *a1, s32 a2, s32 a3);
extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
extern void func_80146AFC(void *a0);
extern void func_8014ADA8(s32 a0, s32 a1);
extern void func_8014AD7C(s32 a0);
extern s32 D_80078E8C;
extern void func_8014B034(s32 arg0);
extern void func_8014B00C(s32 arg0);
extern void func_8014B084(void);
extern s16 D_80078E90;
extern void func_8014B034(s32 a0);
extern u16 D_80078EAC;
extern u8 D_80078EBA;
extern void func_800D10EC(void);
extern void func_8002AC98(void);
extern s32 func_8014B154(s32 *a0);
extern void func_8014B12C(void);
extern void func_8014B2F8(void);
extern void func_8014B4C4(void);
extern void func_8014B160(s32 a0);
extern s32 func_8016F1C4(void);
extern s16 D_80078E96;
extern s16 D_80078EB8;
extern u16 D_80078EA6;
extern void func_8014B2A8(void);
extern void func_8014B310(void);
extern void func_8014B2D0(void);
extern s32 D_80078E94;
extern s32 D_80078ECC;
extern void func_8014B33C(void);
extern u8 D_80062BF4[];
extern void func_8014BC80(s32 a0, s32 a1);
extern void func_80019064(void *a0);
extern s32 D_80078E98;
extern void func_80166244();
extern void func_8014B4D4(void *a0);
extern s16 D_80078E9A;
extern u8 D_80126D1C;
extern s32 D_80126D74;
extern void func_8014B598(s32 a0, s32 a1);
extern void func_8014B5B0(s32 *a0);
extern void func_8014B5C4(s32 *a0, s32 a1, s32 a2);
extern void func_8014B5D8(s32 s1);
extern s32 D_80078E9C;
extern s32 D_80078ED0;
extern void func_8014B6F0(s32 a0, s32 a1);
extern void func_8014B768(s32 a0, s32 a1);
extern void func_8014B944(s32 a0, s32 a1, s32 a2);
extern s32 D_80078EA4;
extern u16 D_80078EB2;
extern s16 D_80078EB4;
extern void func_8014BB0C(void);
extern void func_8014BB24(s32 a0, s32 a1, s32 a2);
extern void func_8014BC0C(s32 a0, s32 a1);
extern void func_8014BC44(s32 a0, s32 a1);
extern u8 D_800B9A17;
extern void func_8014BCC0(s32 a0, s32 a1);
extern u16 D_80078EB6;
extern s32 func_8014BCEC(s32 a0, s32 a1);
extern void func_8014BD24(s32 a0, s32 a1);
extern void func_8014BD60(s32 param_1, s32 param_2);
extern void func_8014BD98(s32 a0, u16 a1);
extern void func_8014BDC8(void);
extern void func_8014BDE0(void);
extern s32 func_8017267C(s32 *a0);
extern s32 func_80013294(void *a0, void *a1);
extern void func_80029ED4(s32 a0);
extern void func_8014BDE8(s32 a0);
extern void func_8014BE78(void);
extern void func_8014BE9C(void);
extern void func_80029124(s32 a0, s32 a1);
extern void func_8014BEC0(void);
extern void func_8014BF18(s32 a0);
extern void func_8014BF48(void);
extern u8 func_8014BF6C(void);
extern void func_8014BF8C(u8 arg0);
extern void func_8014BFB0(void);
extern u8 func_8014BFD4(void);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_8014C010(s32 a0, s32 a1);
extern s32 func_8014C050(s32 a0, s32 a1);
extern s32 func_8014C088(s32 a0, s32 a1);
extern s32 func_8014C0C8(s32 a0_unused, s32 a1, s32 a2);
extern s32 func_8014C118(void * a0, s32 a1, s32 a2);
extern s32 func_8014C168(s32 * param_1, s32 param_2);
extern void func_8014C1C8(s32 arg0, s32 arg1, void *arg2);
extern u8 D_8018C114[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018C11C;
extern s32 func_8014C5FC(s32 a0, s32 a1, void *a2);
extern s16 func_8014C5D0(s32 a0, s32 a1);
extern s32 func_8014C5FC(s32 a0, s32 a1, void * a2);
extern u8 D_80126D17;
extern void func_8014C6AC(void);
extern void func_8014C6C0(void);
extern u8 D_80126D1E;
extern void func_8014C6D0(void);
extern void func_8014C6E0(void);
extern s32 func_8014C860(s32 a0, s32 a1);
extern void func_8014C8C8(s32 a0, s32 *a1);
extern void func_8014C88C(s32 a0);
extern void func_8014C8C8(s32 dst, s32 * src);
extern void func_8014C8F0(s32 arg0);
extern u8 D_801151F0[];
extern s32 func_8014C918(s32 a0, s32 a1);
extern s32 D_80126B50;
extern void func_8014C968(void);
extern void func_8014C978(void);
extern s32 func_8014C98C(void);
extern void func_80139914(s32 a0);
extern s32 func_8014CA00(s32 a0);
extern u16 func_8014CA70(s32 a0, s32 a1);
extern s32 func_8014CA14(s32 a0, s32 a1);
extern u16 func_8014CAE4(s32 *a0, s32 a1);
extern s32 func_8014CA88(s32 *a0, s32 a1);
extern s32 func_8014CAFC(void);
extern s32 func_8014CB0C(void);
extern s32 func_8014CB1C(void);
extern u8 D_80126D1F;
extern s32 func_8014CB2C(void);
extern s32 func_8014CB58(void);
extern u8 D_80126D1D;
extern void func_8014CB68(void);
extern s32 func_8014CB7C(void);
extern s32 func_8014CB8C(void);
extern short D_80126C9E;
extern void func_8014CB9C(struct Packed8 *a0);
extern s32 D_80126CDC;
extern void func_8014CBD8(void);
extern s16 D_80126CC4;
extern void func_8014CBE8(void);
extern void func_8014CBF8(void *a0);
extern void func_8014D3E0(s32 a0);
extern void func_8014D04C(void);
extern void func_8014CCB4(void);
extern void func_8014CC28(s32 a0);
extern void func_8014CD0C(u8 *a0);
extern void func_8014CF04(s32 a0, void *a1, void *a2);
extern void func_8014CD80(s32 a0, void *a1, void *a2);
extern void func_8014D0A4(s32 a0);
extern void func_8014D2A0(s32 a0, void *a1, void *a2);
extern void func_8014D12C(s32 a0, void *a1, void *a2);
extern void func_8014D438(s32 a0);
extern void func_8014D3E0(s32 _arg0);
extern void func_8014D610(s32 a0, void *a1, void *a2);
extern void func_8014D4C0(s32 a0, void *a1, void *a2);
extern void func_8014D790(s32 a0);
extern void func_8014D738(void);
extern s32 func_8014DD8C(s32 a0, void *a1, void *a2);
extern void func_8014D820(s32 a0, void *a1, void *a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014DCE0(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8014DD8C(s32 arg0, void *arg1, void *arg2);
extern void func_8014DF94(s32 arg0);
extern void func_8014DF3C(void);
extern s32 func_8014E284(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E048(s32 a0, u16 *a1, u16 *a2); /* u16*: def lhu semantics (T5b reconcile; ptr param type codegen-neutral for the caller) */
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern u8 D_801152A8[];   /* canonical TU type (engine_core) — read via *(u16*) cast */
extern s16 D_801152AC;
extern s32 func_8014E048(s32 param_1, u16 * param_2, u16 * param_3);
extern void func_8014E48C(s32 a0);
extern void func_8014E434(void);
extern void func_8014E5B4(s32 a0, void *a1, void *a2);
extern s32 func_8014E514(u8 *a0, s32 a1, s32 a2);
extern void func_8014E6F8(struct SubE6F8 *a0);
extern void func_8014E6A0(void);
extern s32 func_8014E83C(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E790(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014E790(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014E83C(s32 arg0, s16 * arg1, s16 * arg2);
extern void func_8014E934(s32 _arg0);
extern s32 func_8014EA4C(void *a0, void *a1, void *a2, s32 a3);
extern s32 func_8014E98C(void *a0);
extern u16 D_800B99DA;
extern s32 D_801150D8;
extern s16 D_801152AA;
extern u8 D_80126720[];
extern s16 D_80126724;
extern s32 func_8014EA4C(void * a0, void * a1, void * a2, s32 _arg3);
extern s32 func_8014ED80(struct SubED80 *a0);
extern int D_801EE5C8;
extern void func_8014ED28(s32 _arg0);
extern s32 func_8014EE14(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014EE14(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F24C(struct SubF24C *a0);
extern void func_8014F1F4(void);
extern s32 func_8014F2E0(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014F2E0(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F4C0(void);
extern s32 func_8014F468(void);
extern int func_8014F74C();
extern int func_8014F6F4(void);
extern u8 D_800D3918[];
extern u8 D_801152A8[];
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern s32 D_801EE5CC;
extern void func_8014FA04(s32 a0);
extern s32 func_8014FBC0();
extern s32 func_8014FC18(u8 *self);
extern int func_8014FD54(int param_1);
extern void func_8014FCFC(void);
extern void func_80150170(void *a0);
extern s32 func_8014FE60(void *a0);
extern void func_8014FDF4(struct S8014FDF4 *a0);
extern s32 func_8014FE60(void *e);
extern s32 func_80134510(s32 arg);
extern s32 func_80150150(s32 a, s32 b);
extern s32 func_80150460(s32 a, s32 b);
extern void func_801504D8(u16 *a0);
extern s32 func_80150480(s32 _arg0);
extern s32 func_80150528(void *a0, void *a1, void *a2);
extern s32 func_80150528(void *arg0, void *arg1, void *arg2);
extern s32 func_801506A4(s32 a0, s32 a1);
extern s32 func_801505FC(s32 a0);
extern s32 func_801506A4(s32 arg0, s32 arg1);
extern void func_80150820(s32 a0, s32 a1);
extern void func_8015086C(int param_1);
extern s32 func_801508B4(s32 a0);
extern s32 func_8015094C(s32 a0);
extern short func_801508F8(s32 a0);
extern s32 D_8018C14C;
extern s32 D_80126990;
extern s32 D_80126994;
extern u8 D_80126948[];
extern s32 func_80021174(s32 a0, s32 a1);
extern s32 func_8015094C(s32 param_1);
extern void func_80150B9C(void);
extern s32 func_80151184(s32 a0, s32 a1, s32 a2);
extern s32 func_80150BA4(s32 a0);
extern s32 func_801619D0(void *a0);
extern void func_80150BC8(s32 *a0);
extern s32 func_80150480(s32 a0);
extern u16 D_800AE6DC;
extern void func_80150C48(s32 a0);
extern int func_80151184(int arg, int a1, int a2);
extern int func_80150CA0(int arg);
extern void func_80150EC4(s32 a, s32 b);
extern void func_80150CC4(s32 a);
extern void func_80150CE4(s32 a);
extern void func_80150D04(s32 a);
extern void func_80150D24(s32 a);
extern void func_80150D44(s32 a);
extern void func_80150D64(s32 a);
extern void func_80150D84(s32 a);
extern void func_80150DA4(s32 a);
extern void func_80150DC4(s32 a);
extern void func_80150DE4(s32 a);
extern void func_80150E04(s32 a);
extern void func_80150E24(s32 a);
extern void func_80150E44(s32 a);
extern void func_80150EC4(s32 a0, s32 a1);
extern void func_80150E64(s32 a0);
extern void func_80150E84(s32 a0);
extern void func_80150EA4(s32 a0);
extern u8 D_800AE6C0;
extern s16 D_800AE6C8;
extern s16 D_800AE6CA;
extern s16 D_800AE6CC;
extern s32 D_800AE6C4;
extern s16 D_800AE6CE;
extern u8 D_800AE6BE;
extern u8 D_801201F8[];
extern void func_80150F78(void);
extern void func_80150F80(s32 a0);
extern int func_80150FB4(int arg);
extern void func_80150FD8(s32 a0);
extern int func_80151014(int arg);
extern void func_80151038(s32 a0);
extern int func_80151070(int arg);
extern int func_80151094(int arg);
extern void func_801510B8(void);
extern void func_801510C0(void);
extern int func_801510C8(int arg);
extern int func_801510EC(int arg);
extern s32 func_8012DB84(void);
extern s32 func_80151110(void);
extern void func_80151130(void);
extern int func_80151138(int arg);
extern void func_8015115C(s32 *a0, s16 a1);
extern s32 func_80151164(s32 a0, s32 a1);
extern s32 func_80151184(s32 arg0, s32 arg1, s32 arg2);
extern void func_801511A8(u8 *a0);
extern void func_801511C4(u8 *a0);
extern int func_80151204(int arg, int a1);
extern int func_801511E0(int arg);
extern int func_80151204(int a0, int a1);
extern void func_80151238(void *a0);
extern void func_8015126C(u16 *p);
extern void func_80151780(s32 a0);
extern void func_801516F0(s32 *a0);
extern void func_8015173C(s32 *a0);
extern s16 D_8011DB1A;
extern s32 D_80127518;
extern s32 D_801151FC;
extern s32 func_801725CC(u8 *a0);
extern s32 func_80029D3C(void);
extern void func_80151878(void);
extern void func_80153B58(s32 *a0);
extern s32 func_80151880(s32 a0);
extern s32 func_801518D8(s32 a0);
extern s32 func_80151944(void);
extern s32 func_80151924(void);
extern void func_8014E934(s32 a0);
extern void func_8014F3E8(s32 a0);
extern void func_801519C8(s32 a0);
extern void func_80151980(s32 a0);
extern M2C_UNK D_800D5880;
extern s32 D_800D58AC;
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801519C8(s32 arg0);
extern void func_80151C54(s32 a0);
extern void func_801542DC(s32 *a0, s32 a1);
extern void func_8015BDD0(s32 *a0);
extern void func_80165718(s32 a0);
extern u8 D_800D46E4[];
extern void func_80151AE4(s32 arg0);
extern void (*D_8018C1F4[])(void);
extern void func_80151D24(void *a0);
extern void func_80151DB0(s32 a0);
extern void func_80151D60(void *a0);
extern s32 func_80172630(u8 *a0);
extern s32 D_80062C14;
extern void func_80151DB0(s32 param_1);
extern void func_80151E78(s32 *a0);
extern void func_80151ECC(struct S80151ECC *a0);
extern void func_80151FB4(s32 a0);
extern void func_80151F38(s32 *a0);
extern void func_801553C0(s32 a0);
extern void func_80153C18();
extern void (*D_8018C218[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018C208;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018C22C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018C238[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018C248[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018C260[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018C250;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018C274[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018C290[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018C280;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018C2A4[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018C2B8[])(void);
extern void func_80153320(void *a0);
extern void func_801533A4(s32 a0);
extern void func_8015335C(s32 a0);
extern void func_80153410(s32 *a0);
extern void func_80153490(s32 a0);
extern void func_80153550(s32 a0);
extern void func_801534D8(s32 *a0);
extern void (*D_8011DB28)(s32 a0);
extern s32 func_801536DC(s32 param_1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80153978(s32 a0, u16 *src);
extern s32 func_80133784(s32 a0, void *src, s32 dst);
extern s32 func_801539F8(s32 a0, void *a1);
extern s32 func_801539F8(s32 a0, void * a1);
extern s32 func_8016DA04(s32 a0);
extern s32 func_80153BD8(s32 a0);
extern s32 func_80153BF0(s32 a0);
extern void func_80153C18(void);
extern u16 D_8011F748;
extern void func_80153C30(void);
extern void func_80153C74(s16 a0, s16 a1);
extern s16 D_8011DB18;
extern void func_80153C44(int a0, int a1, s16 a2);
extern s16 D_8011DB0C;
extern s32 D_80115210;
extern void func_80153C8C(void);
extern void func_80153C9C(void);
extern s32 func_80153CBC(void);
extern s32 D_8018C2CC;
extern void (*D_8018C2F4[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018C2D4;
extern void func_80153D7C(s32 param_1);
extern void func_8015410C(void);
extern void func_80153E00(s32 param_1);
extern void func_80151664(void);
extern void func_80154134(u8 *a0);
extern void func_80154190(u8 *a0, s32 a1);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154218(u8 *a0, s32 a1, s32 a2);
extern void func_801541D8(u8 *a0, s32 a1, s32 a2);
extern s32 func_801549F8(s32 a0, s32 a1, s32 a2);
extern void func_801542A4();
extern void func_801542A4(s32 *a0, s32 a1);
extern void func_8015430C();
extern void func_8015430C(u8 *arg0, s32 arg1, s32 arg2);
extern void func_8015444C(void *a0, s32 *a1, s32 *a2, s32 *a3);
extern s32 func_80154358(void * arg0);
extern void func_80154AB4(s32 a0, s32 a1);
extern void func_80154B20(s32 a0, s32 a1, s32 a2);
extern void func_80154AE0(s32 a0, s32 a1, s32 a2);
extern void func_80154B7C(u8 *a0, s32 a1);
extern void func_80154B4C(u8 *a0, s32 a1);
extern void func_80154BC8(void *a0, s32 a1, s32 a2);
extern void func_80154B98(void *a0, s32 a1, s32 a2);
extern u8 D_800D8D10[];
extern s16 D_80078E9E;
extern void func_801550FC(s32 a0);
extern void func_80154ED8(s32 a0, s32 a1);
extern void func_80154F9C(s32 a0);
extern void func_800183E0(s32 a0);
extern void func_801550FC(s32 arg0);
extern void func_8001D150(s32, s32);
extern void func_8001D130(int, int);
extern void func_80155150(int param_1);
extern s32 D_800DE2A4[];
extern void func_801552F4(s32 a0);
extern void func_80155344(s32 a0);
extern s32 func_80155394(s32 *a0);
extern void func_801553A8(s32 *a0);
extern s32 func_80029178(s32);
extern int (*D_8018C340[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018C344[])(void);
extern s32 func_80161104(void);
extern void func_801555F4(void *);
extern void func_801555BC(void *a0);
extern s32 func_80155800(s32 arg0);
extern int func_80155A44(int param_1);
extern int func_80161208();
extern u8 D_800D4DA8[];
extern void func_80155B20(s32 *a0);
extern s32 D_800D4DB4;
extern void func_80155B9C(s32 a0);
extern u8 D_800D4DD4[];
extern void func_80155C0C(s32 *a0);
extern void func_8014ED28(s32 a0);
extern int func_80155FF8(int arg, int a1);
extern s32 D_800D4DF4;
extern void func_80155C64(s32 a0);
extern void func_8015E880(s32 *a0);
extern void func_80155D70(s32 param_1);
extern void func_80155E30(void *a0);
extern s32 func_80161208();
extern void func_80155EA4(void *arg0);
extern void func_80155F58(void);
extern s32 func_80155F80();
extern s32 func_80155F60(void);
extern s32 func_80155F80(s32 a0);
extern int func_80155FB0(int arg, int a1);
extern int func_80155FD4(int arg, int a1);
extern int func_80156044(int arg, int a1);
extern s32 func_80029B4C(s32 a0, s32 a1);
extern s32 func_80029BC8(s32 a0, s32 a1);
extern s32 func_80029C44(s32 a0, s32 a1);
extern s32 func_8015640C(s32 a0, s32 a1);
extern s32 rand(void);
extern u32 func_8015616C(s32 param_1, u16 param_2);
extern u16 func_80156370(u16 param_1);
extern s32 func_801564B0(s32 a0);
extern s32 func_8002A1B4(void);
extern s32 func_8002A400(void);
extern s32 func_8002A670(void);
extern s32 func_8002A8E0(void);
extern s32 D_801151E0[];
extern s32 func_801565C0(void);
extern void func_80156A14(s32 *a0);
extern void func_80156648(s32 *a0);
extern u8 D_8011DAD8[];
extern s32 func_8014C568(void *a0);
extern void func_801567BC(s32 a0);
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern unsigned char D_8011520C[];
extern unsigned short D_8018C7A8[];
extern void func_80156A1C(s32 param_1, s32 param_2);
extern s32 D_801150E0[];
extern void func_80156A88(s32 a0, s32 a1);
extern void func_80156B74(s32 param_1, u32 param_2, u8 *param_3);
extern void func_80156ECC(int param_1, int param_2, int param_3, int param_4, int param_5);
extern void func_80156FA8(s16 *param_1, s16 *param_2, s16 *param_3);
extern void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern s32 func_80135260(s32 a0, s32 a1, s32 a2, s32 a3);
extern u32 func_801571C4(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801575E4(void *a0);
extern void func_801574DC(s32 *a0);
extern void func_80157544(void *a0);
extern void (*D_8018C7B8[])(void);
extern void func_8014CC28(s32 a0);      /* defined  */
extern void func_8014F3E8(s32 a0);      /* declared */
extern void func_8015BDD0(s32 *a0);     /* defined  */
extern void func_801575E4(void *a0);    /* defined  */
extern void func_80157580(s32 arg0);
extern u8 D_800D4F14[];
extern void func_801576A8(void *arg0);
extern s32 func_8015773C(u8 *a0);
extern s32 func_8015771C(u8 *a0);
extern s32 func_8015773C(u8 * arg0);
extern int D_801EE600;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018C7E0[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018C7C0;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018C7D0;
extern void func_8015795C(int param_1);
extern void func_80161D20(s32 a0, s32 a1);
extern void func_80157A8C(s32 a0);
extern void func_8016706C(s32 a0);
extern u8 D_800D51AC[];
extern void func_80157AC8(s32 param_1);
extern void func_80157B74(int param_1);
extern void func_8016158C(void *a0);
extern void func_8015BE04(s32 *a0);
extern void func_80157BC8(s32 a0);
extern void func_80157CCC(s32 a0);
extern void func_80157DC4(void *a0);
extern void func_80157FC4(void *a0);
extern void func_80157D74(u16 *a0);
extern void (*D_8018C820[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018C828[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018C7F4;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018C834[])(void);
extern void func_8015824C(void *a0);
extern void func_801582C0(void *);
extern void func_80158288(void *a0);
extern u8 D_800D52A8[];
extern void func_801585A4(s32 *a0);
extern void func_801582C0(void *a0);
extern s32 func_801585AC(s32 *a0);
extern u8 D_800D52E8[];
extern void func_80158344(s32 *a0);
extern s32 func_801615C4(void *a0, s32 a1);
extern u8 D_8018C804;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801EE608;
extern s32 D_801EE614;
extern s32 D_801EE618;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018C870[])(s32 *);
extern void func_80158AE4(void *a0);
extern void func_80158AB4(void *a0);
extern void func_8016F264(void);
extern void func_80165840(void);
extern void func_801658DC(void);
extern void func_80165A78(s32);
extern void func_80158AE4(void * a0);
extern M2C_UNK D_800D58D8;
extern void func_80158BB0(void *arg0);
extern s32 func_80159404(s32 a0, s32 a1);
extern void func_80158C40(s32 *a0);
extern void func_80158CD8(s32 *a0);
extern s32 func_80159434(s32 a0, s32 a1);
extern void func_80158D60(s32 a0);
extern M2C_UNK D_800D5904;
extern void func_80158E24(s32 *a0);
extern s32 D_8018C844[];
extern int rand(void);
extern s32 func_8013767C(s32 a0);
extern void func_80158F00(int param_1);
extern u8 D_80110C3C[];
extern s32 func_801399F0(s32);
extern void func_80139914(s32);
extern s32 func_80159464(void);
extern void func_801594E8(s32, s32);
extern void func_80158FA4(s32 param_1);
extern s32 func_801399F0(s32 a0);
extern u8 D_80110C94[];
extern u8 D_80110CD4[];
extern void func_80159070(void *a0);
extern s32 func_80029A94(s32);
extern void func_80175454(void);
extern void func_800298BC(void *);
extern void func_8002992C(s32);
extern void func_800CF804(void);
extern void func_800CF818(void);
extern u8 D_80110D0C[];
extern void func_80159120(s32 a0);
extern void func_801592CC(s32 *a0);
extern u8 D_800AE6BD;
extern s32 D_801EE610;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018CAC0[])(void);
extern void func_80159698(void *a0);
extern s32 func_801596D4(void *a0);
extern void func_80174B6C(void);
extern void func_80129248(s16 a0);
extern void func_8013C938(void);
extern void func_8013CB20(void);
extern void func_8013C98C(void);
extern void func_8002850C(s32, s32, s32);
extern void func_80028620(s32, void *);
extern s16 D_800B9AAC[];
extern s16 D_800B9B00;
extern u16 D_801270C0;
extern u32 D_800AFAE8[];
extern char D_8018C8E0[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018CB64[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018CCB8[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018CAD4;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018CCC0[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018CAE4;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018CB04;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018CCC8[])(void);
extern void func_8015ADB0(s32);
extern void func_8015AD78(s32 a0);
extern void func_8015ADB0(s32 arg0);
extern s32 D_800D4A9C;
extern int func_8015B6F4(int param_1);
extern u8 D_800D4F8C[];
extern s32 func_8015B7B4(s32 a0);
extern u8 D_800D4BE0[];
extern s32 func_8014A51C(void);
extern s32 func_8015B858(u8 *a0);
extern s32 D_800D4B48;
extern void func_8015B8F8(s32 *a0);
extern void func_8015BD8C(s32 *a0);
extern s32 func_8015BE94();
extern void func_8015BE38(struct Obj *a0);
extern s32 func_8015BE74(void);
extern void func_80161124(void *a0);
extern s32 func_8015BE94(s32 *a0);
extern s32 func_8015AE2C();
extern s32 func_8015BEC4(void);
extern s32 func_8015B950(void);
extern s32 func_8015BEE4(void);
extern void func_8015BF04(s32 *a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015BFF4(void *a0);
extern void func_8015BF7C(s32 *a0);
extern void func_8015C030(s32 *a0, s32 a1);
extern void func_8015BFB0(s32 *a0, s32 a1);
extern void (*D_8018CCF0[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018CCFC[])(void);
extern void func_8015C788(s32);
extern void func_8015C750(s32 a0);
extern void func_8015CB94(s32 a0);
extern void func_8015CBCC(void);
extern void func_8015CBD4(void);
extern void func_8015CBDC(void);
extern void func_8015CBE4(void);
extern void func_8015CBEC(void);
extern void func_8015CBF4(void);
extern void func_8015CBFC(void);
extern void func_8015CC04(void);
extern void func_8015CC0C(s32 *param_1);
extern void func_8015CC74(s32 *a0);
extern void func_8015CC40(s32 *a0);
extern s32 func_8015CCD0();
extern s32 func_8015CCB0(void);
extern s32 func_801725E0(u8 *a0);
extern s32 func_8015CCD0(s32 param_1);
extern s32 func_8015CD20(s32 arg0);
extern void func_8015CF24(s32 a0);
extern void func_8015D01C();
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0(s32 *a0);
extern void func_8015CF8C(s32 *a0);
extern void func_8015CFFC(void);
extern void func_8015D01C(int param_1);
extern void (*D_8018CB70[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018CDA0;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018BE84[];
extern void func_8015D414(int param_1);
extern void func_8015D57C(s32);
extern void func_8015D480(s32 *a0);
extern s32 func_8015D4E8(s16 *a0);
extern void func_8015D4B4(s16 *a0);
extern void func_8015D524(s32 arg0);
extern void func_8015D544(s32 a0);
extern void func_801746DC(void);
extern void func_8015D57C(s32 arg0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80154150(int, int);
extern void func_80149374(int, int);
extern unsigned char D_8018CDB4[];
extern void func_8015D5E8(int param_1);
extern int func_8015E0D4(int);
extern void func_8015DA5C(s32 a0);
extern void func_8015DB6C(s32 a0);
extern void func_8015DA90(s32 *a0);
extern void func_8015DAF8(s32 *a0);
extern void func_8015DB6C(s32);
extern void func_8015DB34(s32 a0);
extern void func_8015DCB8(s32 a0);
extern void func_8014BD60(s32 a0, s32 a1);
extern int func_8015DD74(int);
extern void func_8015DBD4(void *arg0);
extern int func_8015DC84(int a0);
extern s8 D_8018CDF0[];
extern void func_8015DCB8(s32 param_1);
extern int func_8015DD74(int arg0);
extern void func_8015DECC(s32 a0);
extern void func_8015DDF0(s32 *a0);
extern void func_8015DE58(s32 *a0);
extern void func_8015DECC(s32);
extern void func_8015DE94(s32 a0);
extern void func_8015E018(s32 a0);
extern void func_8015DF34(void *arg0);
extern int func_8015DFE4(int a0);
extern void func_8015E018(s32 param_1);
extern int func_8015E0D4(int a0);
extern void func_8015E22C(s32 a0);
extern void func_8015E150(s32 *a0);
extern s32 func_8015E1B8(s32 a0);
extern void func_8015E184(s32 *arg0);
extern void func_8015E22C(s32);
extern void func_8015E1F4(s32 a0);
extern u8 D_800D4FF4[];
extern u8 D_800D5098[];
extern u8 D_800D5060[];
extern s32 func_8014A850(s32 a0);
extern void func_8015E40C(s32 a0);
extern void func_8015E588(void);
extern void func_8015E4B0(s32 a0);
extern void func_8015E288(s32 a0);
extern u16 D_8018CE38;
extern u16 D_8018CE3A;
extern u16 D_8018CE3C;
extern s32 D_8018CE40;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018CE48;
extern void func_8015E5B0(u8 *self);
extern void func_8015E714(s32 *a0);
extern void func_8015E95C(s32);
extern void func_8015E84C(s32 *a0);
extern void func_8015E8E8(s32 *a0);
extern void func_8015E9B8(s32 *a0);
extern void func_8015E8B4(s32 *a0);
extern void func_8015E924(s32 a0);
extern void func_8015E95C(s32 a0);
extern s16 D_801152A0;
extern void func_80160818(s32 *a0);
extern void func_8015ED6C(s32 *a0);
extern void func_8015EE7C(s32);
extern void func_8015EDA0(s32 *a0);
extern s32 func_8015EE08(s32 a0);
extern void func_8015EDD4(s32 *arg0);
extern void func_8015EE44(s32 a0);
extern int D_800D4C48;
extern int D_8018CB54;
extern void func_8015EE7C(s32 param_1);
extern void func_8015EEE0(void *arg0);
extern void func_8015EF9C(void);
extern void func_8015F080(s32);
extern void func_8015EFA4(s32 *a0);
extern void func_8015F00C(s32 *a0);
extern void func_8015EFD8(s32 *a0);
extern void func_8015F048(s32 a0);
extern void func_8015F080(s32 a0);
extern s32 D_80062BE8;
extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_80161208(void);
extern void func_8015F118(void *a0);
extern void func_8015F260(s32 *a0);
extern void func_8015F380();
extern void func_8015F2BC(s32 *a0);
extern void func_8015F324(s32 *a0);
extern void func_8015F2F0(s32 *a0);
extern void func_8015F360(void);
extern s32 func_801725B8(u8 *a0);
extern void func_8015F380(void* arg0);
extern void func_8015F738(s32 *a0);
extern void func_8015F848(s32 *a0);
extern void func_8015F76C(s32 *a0);
extern s32 func_8015F7D4(s32 a0);
extern void func_8015F7A0(s32 *arg0);
extern void func_8015F810(s32 *a0);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern void func_8015F89C(void *arg0);
extern void func_8015F948(s32 *param_1);
extern void func_8015F9A4(void *arg0);
extern void func_8015FA24(s32 arg0);
extern void func_8015FBE0(s32 *a0);
extern void func_8015FA44(s32 *a0);
extern void func_8015FAAC(s32 *a0);
extern void func_8015FA78(s32 *a0);
extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void func_8015FAE8(void *arg0);
extern void func_8015FCC8(void *param_1);
extern unsigned int D_8018CECC[];
extern void func_8015FD74(int param_1);
extern s32 func_80028DE0(void);
extern u8 func_80165700(s32 a0, s32 a1);
extern void func_8015FDCC(s32 a0);
extern u8 D_80078EC2;
extern u8 func_801656E8(s32 a0, s32 a1);
extern void func_80165670(s32 a0, s32 a1);
extern void func_8016004C(s32 a0);
extern void func_8015FF20(void *param_1);
extern void func_801601AC(s32 *a0);
extern void func_801600D0(s32 *a0);
extern void func_80160138(s32 *a0);
extern void func_80160104(s32 *a0);
extern void func_80160174(s32 *a0);
extern void func_801601E4(s32 *a0);
extern void func_80160244(s32 *a0);
extern void func_8016032C(void);
extern void func_80160410(s32 *a0);
extern void func_80160334(s32 *a0);
extern void func_8016039C(s32 *a0);
extern void func_80160368(s32 *a0);
extern void func_801603D8(s32 *a0);
extern u8 D_80062BD0;
extern void func_80160410(s32 * a0);
extern void func_801607B8(s32 *a0);
extern void func_801608C0(s32 *a0);
extern void func_801607E4(s32 *a0);
extern void func_8016084C(s32 *a0);
extern void func_80160888(s32 *a0);
extern void func_80160A28(s32 a0);
extern void func_80160A74(s32 *a0);
extern void func_80160BB4(s32 *a0);
extern void func_80160ACC(s32 *a0);
extern s32 func_80160B34(s32 a0);
extern void func_80160B00(s32 *arg0);
extern void func_80160B70(s32 a0);
extern void func_80160C28(void *arg0);
extern void func_80160CB4(s32 *a0);
extern void func_80160D10(void *arg0);
extern void func_80160DEC(u8 *a0);
extern void func_80160F00();
extern void func_80160E3C(s32 *a0);
extern void func_80160EA4();
extern void func_80160E70(s32 *a0);
extern void (*D_8018CF7C[])(void);
extern void func_80160EA4(void *a0);
extern void func_80160EE0(void);
extern void func_80160F00(void* arg0);
extern void func_800D0F4C(s32 a0);
extern u8 D_80110EC0;
extern void func_80160F70(s32 a0);
extern void func_80160FE0(s32 *a0);
extern void func_80161034(void *a0);
extern void func_80161094(s32 a0);
extern void func_801610FC(void);
extern void func_801483E8(void);
extern s32 func_80161A60(s32 a0);
extern void func_8016130C(void *a0, s32 a1);
extern void func_80161240(void *a0);
extern void func_80161374(void *a0, s32 a1);
extern void func_80161278(void *a0);
extern s32 func_801612B8(void * a0, s32 a1);
extern void func_8016163C(void *a0, s32 a1);
extern void func_80161774(void *a0, s32 a1);
extern s32 func_8016197C(s32 a0, s32 a1);
extern s32 func_80161488(void *a0);
extern void func_80161888(void *a0, s32 a1);
extern void func_801614E4(void *a0);
extern void func_8016191C(void *a0, s32 a1);
extern void func_8016151C(void *a0);
extern void func_80161554(void *a0);
extern s32 func_801615C4(void * arg0, s32 arg1);
extern s32 func_801619A4(s32 *a0);
extern s32 func_80161A00(s32 a0);
extern s32 func_80161A30(s32 a0);
extern int func_801497A8(void);
extern int func_80161BE0(void *param_1);
extern u16 D_8018CFAC[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018D010;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801EE620[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018D034[])(void);
extern void func_80162330(void *a0);
extern void func_8014706C(void *a0);
extern s32 func_8016236C(u8 *a0);
extern void func_800D0C48(s32 a0);
extern s32 func_801623B8(s32 *a0);
extern s32 func_800167F0(s32 a0);
extern s32 func_80162414(void);
extern s32 func_80162438(s32 _unused0);
extern int func_801626B8(void);
extern void func_80162714(void);
extern int D_801EE678[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018D07C[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018D06C;
extern s32 D_800B5CBC;
extern u8 D_800B5CDF;
extern s32 D_800B5CEC;
extern void func_80162870(s32 param_1);
extern void func_801628F4(s32 *a0);
extern void func_80162968(s32 param_1);
extern void func_80162AC0(s32 *a0, s8 a1);
extern s32 func_80162AE0(u8 *a0);
extern void func_80162AF4(void);
extern void func_80162CC4(void);
extern s32 D_80126D40;
extern void func_80162B1C(void);
extern void func_80162D28(s32 *a0);
extern void func_80162D88(s32 *a0);
extern void func_80162DE8(s32 *a0);
extern void func_80162E48(s32 *a0);
extern void func_80162EA8(s32 *a0);
extern void func_80162F60(s32 arg0, s32 arg1);
extern void func_80162F80(s32 arg0, s32 arg1);
extern void func_80162FA0(s32 arg0, s32 arg1);
extern void func_80162F08(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80162FC0(s32 *a0);
extern void func_80162FF4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801630C4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163194(s32 a0, s32 a1, s32 a2, s32 a3, s32 arg4);
extern void func_8016325C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80163234(s32 a0);
extern s32 D_80115100;
extern s32 func_801632E0(void);
extern s32 D_80115200;
extern s32 func_801632F0(void);
extern u16 D_80126B18[];
extern void func_80163328(void);
extern s32 func_801633A8(void);
extern s32 func_80163408(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8016345C(s32 a0, u16 a1, s32 a2, u16 a3, s32 a4);
extern char D_801EDEAC[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018D084[])(void);
extern void func_80163A58(void *a0);
extern void func_80163A94(s32 param_1);
extern void func_80163C2C(s32 param_1);
extern void func_80163EC8(s32 param_1);
extern void func_80164270(s32 *a0);
extern void func_80164418(void);
extern void func_80163764(s32 a0);
extern void func_801642AC(s32 a0);
extern void func_8016432C(s32 a0);
extern void func_80164410(void);
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164530(s32 arg0);
extern void (*D_8018D0D8[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018D0A0;
extern s16 D_8018D0D4;
extern s16 D_8018D0D2;
extern s16 D_8018D0D0;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018D0E4[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801EE6D8;
extern u8 D_801EE6D9;
extern u8 D_801EE6DA;
extern u8 D_801EE6DB;
extern u8 D_801EE6DC;
extern u8 D_801EE6DD;
extern u8 D_801EE6DE;
extern u8 D_801EE6DF;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018D0F4[])(void);
extern void func_80164EA4(void *a0);
extern void func_80165124(void *a0);
extern void func_80164EE0(int param_1);
extern s32 func_80165140(s32 a0);
extern void func_801651B8(void *a0);
extern void func_80164F44(void *arg0);
extern void func_80165024(void *a0);
extern void func_80165064(s32 *a0);
extern void func_801650C4(s32 *a0);
extern s32 func_80165140(s32 param_1);
extern s32 func_80165240(s32 a0, s32 a1, s32 a2);
extern s32 D_801EE718;
extern void func_801651B8(void * param_1);
extern u8 D_80126CF8;
extern void func_8016533C(void);
extern void func_801653F4(s32 a0);
extern void func_80165580(s32 a0);
extern void func_80165374(s32 a0);
extern void func_80165580(s32 _arg0);
extern void func_801653B8(s32 *a0);
extern s32 func_80165624(s32 a0);
extern u8 D_80078EC5;
extern void (*D_8018D138[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018D1B4[];
extern s32 D_8018D1D4[];
extern u8 D_8018D250[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018D270[];
extern u8 D_8018D290[];
extern void func_800CAF6C(void);
extern void func_80165770(void);
extern void func_801657D8(void);
extern u8 D_80078EC3;
extern void func_801657A0(void);
extern s32 D_80078EA0;
extern s32 D_80078EA8;
extern u8 D_80078EBB;
extern s32 D_80078ED4;
extern s32 D_80078ED8;
extern s32 D_80078EDC;
extern u8 D_80078EE0;
extern void func_80165874(void);
extern s8 D_80078EC4;
extern void func_801658EC(void);
extern s32 func_80165900(void);
extern s32 func_80165910(void);
extern s32 D_8012672C;
extern s32 D_8012811C;
extern s32 D_80126B08;
extern void func_80165938(void);
extern void func_80165958(void);
extern s32 func_80165978(void);
extern void func_80165988(void);
extern s32 func_801659A8(void);
extern void func_801659B8(void);
extern s32 func_801659CC(void);
extern void func_80165A18(void);
extern s32 func_80165A50(s32 _arg0);
extern void func_80165AC8(void);
extern void func_80165A78(s32 arg0);
extern void (*D_8018D32C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018D3A8[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801EDEBC;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018D3B4[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018D3BC[])(void);
extern void func_801663FC(void *a0);
extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_801665B4();
extern void func_80146C3C();
extern void func_80166438(u8 *a0);
extern s32 func_80128ED8(void *a0, void *a1);
extern void func_800D22E4(s32 a0);
extern void func_801665B4(s32 *a0);
extern void (*D_8018D484[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018D494[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018D4A4[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018D4B0[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018D410[];
extern u8   D_8018D424[];
extern s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8016829C(s32 a0);
extern s32 func_80166690(s32 a0, s32 a1);
extern void func_80168328(s32 arg0);
extern void func_801683D8(s32 a0);
extern void func_801684B4(s32 a0);
extern void func_80168540(s32 a0);
extern void func_801685EC(s32 a0);
extern void func_80168640(s32 a0);
extern s32  RotMatrixX(s32 a0, void *a1);
extern void func_80168664(void *arg0);
extern void (*D_8018D4C8[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018D4D0[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018D4D8[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018D4E0[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018D4E8[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018D4F0[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018D4F8[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018D5AC[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018D5B4[])(void);
extern void func_80169F00(void *a0);
extern char D_8018D564[];
extern char D_8018D524[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018D5EC[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018D5F8[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018D640[])(void);
extern void func_8016AB30(void *a0);
extern void func_8016B234(void);
extern void func_8016AFB0(s32 a0);
extern void func_8016B114(void *arg0);
extern s32 func_8016B448(s32, s32);
extern s32 func_8016BA48(s32 a0);
extern void func_8016B3F4(s32 a0);
extern s32 func_8016B428(s32 a0);
extern void func_8016B984(void *a0);
extern s32 func_8016B448(s32 arg0, s32 arg1);
extern void (*D_8018D6BC[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801EEA38;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018D6B0[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018D6F4[];
extern unsigned short D_8018D6FC[];
extern unsigned short D_8018D704[];
extern unsigned char D_801EEA40[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801EEA38;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018D70C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801EEB74;
extern M2C_UNK D_801EEB78;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801EEB00;
extern void (*D_8018D73C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801EEB7C[];
extern u8 D_801EEB84[];
extern u8 D_801EEB34[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018D744[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018D760[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018D768[])(void);
extern void func_8016D428(void *a0);
extern void func_8016D464(u8 *a0);
extern void func_8016D4DC(s32 a0);
extern void func_8016D5EC(s32 *a0);
extern short func_8016CBC0(void);
extern void func_8016D64C(int param_1);
extern void func_8016D778(s32 a0);
extern void func_800D20C0();
extern void func_8016D848(s32 *a0);
extern void func_8016D984(s32 *a0);
extern void func_8016DBD8(u8 *a0);
extern void (*D_8018D7D0[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018D774;
extern u8 D_8018D780;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018D804[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018D80C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018D860[])(void);
extern void func_8016E5B8(void *a0);
extern void func_8016E5F4(s32 arg0);
extern void func_8016E778();
extern void func_8016E688(void *a0);
extern void func_8016E6E4(s32 a0);
extern void func_8016E728(u8 *a0);
extern void func_8016E7C8(int param_1, short *p1, unsigned int *p2);
extern void func_8016E778(int param_1);
extern void func_8016E7C8(int param_1, short *param_2, unsigned int *param_3);
extern s32 D_80115218;
extern void func_8016E8F0(void);
extern void func_8016E918(short param_1, short param_2);
extern s32 func_8016E95C();
extern u16 D_8018D894[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018D884[];
extern void func_8016EB3C(s32 p);
extern void func_8016EBA8(u8 *param_1);
extern void func_8016ED6C(void);
extern s32 D_80126D70;
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_8016ED8C(s32 a0, s32 a1, s32 a2);
extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern void func_8016EDBC(s32 a0, s32 a1, s32 a2);
extern void func_8016EE94();
extern void func_8016EDEC(s32 _arg0, s32 _arg1, s32 _arg2);
extern void func_8016EF78(s32 a0);
extern void func_8016EE40(s32 _arg0, s32 _arg1, s32 _arg2);
extern void func_801726D0(void *a0);
extern s32 D_80126D50;
extern s32 D_80126D54;
extern u8 D_80126D6C;
extern u8 D_80126D6D;
extern u8 D_80126D6E;
extern s32 D_80126D5C;
extern s32 D_80126D60;
extern s16 D_80126D64;
extern s16 D_80126D66;
extern s16 D_80126D68;
extern s16 D_80126D6A;
extern u8 D_80126D1A;
extern s32 D_80127058;
extern s32 D_8012705C;
extern s32 D_80127060;
extern s32 D_80127064;
extern s32 D_80127068;
extern s32 D_8012706C;
extern s32 D_80127070;
extern s32 D_80127074;
extern s16 D_80126D20;
extern void func_8016EE94(s32 a0, s32 a1);
extern s32 func_8016EFC8(s32);
extern s32 func_8016EFA8(s32 a0);
extern void func_8016F094(s32 *a0);
extern s32 func_8016F0AC();
extern s32 D_8018D8B0;
extern void func_8016F250(void);
extern void func_8016F288(void);
extern void func_8016F2A8(void);
extern void func_8016F2C8(void);
extern void func_8016F2EC(void);
extern void func_8016F30C(void);
extern void func_8016F330(void);
extern void func_8016F350(void);
extern void func_8016F374(void);
extern void func_8016F388(void);
extern void func_8016F398(void);
extern s32 func_8016F44C(s32 a0);
extern void func_8016F470(s32 a0);
extern s32 func_8016F410(s32 a0);
extern void func_80175414(s32);
extern s32 func_8016F4C4(s32);
extern s32 func_8016F494(s32 a0);
extern void func_8016F0E4(void);
extern s32 func_8016F4C4(s32 param_1);
extern void func_8016F4F4(void);
extern void func_801719A4(int a0, int a1);
extern void func_800D1724(s32 a0);
extern void func_80171928(void *a0);
extern void *D_8011F738;
extern void func_8016F4FC(void *a0);
extern void func_8014708C(void *a0);
extern void func_8016F540(void *a0);
extern void func_8016F578(s32 *a0);
extern void func_8016F5B0(void *a0);
extern void func_80147060(u8 *a0);
extern void func_8016F5E0(u8 *a0);
extern void func_8016F610(void *a0);
extern void func_8016F648(void *a0);
extern void func_8016F680(void *a0);
extern void func_8016F6B0(void *a0);
extern void (*D_8018D928[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018D930[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018D938[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018D940[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018D948[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018D950[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018D95C[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018D968[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018D974[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018D984[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018D994[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018D99C[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018D9A4[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018D9AC[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018D9B4[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018D9BC[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018D9C4[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018D9CC[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018D9D4[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018D9DC[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018D9E4[])(void);
extern void func_80170810(void *a0);
extern void func_801708B0(void *a0);
extern u8 D_800D5DA8;
extern void func_8017084C(s32 a0);
extern u8 D_800D5A34[];
extern void func_80170AD8(void *a0);
extern void func_80171904(s32 a0);
extern void func_80170B48(int a0);
extern void func_80170928(void);
extern u8 D_800D59EC[];
extern void func_80170970(void);
extern u8 D_800D599C[];
extern void func_801709B8(void);
extern u8 D_800D5934[];
extern void func_80170A00(void);
extern void func_80170A48(void);
extern u8 D_800D5DC0[];
extern void func_80170A90(void);
extern void (*D_8018D9EC[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018D9F4[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018D9FC[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018DA04[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018DA0C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018DA14[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018DA1C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018DA24[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018DA2C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018DA34[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018DA3C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018DA44[])(void);
extern void func_801714E4(void *a0);
extern void func_8017162C(void *a0);
extern void func_80171520(s32 a0);
extern s32 func_801716AC(s32 a0, void *a1, s32 *a2);
extern s32 func_80012FC8(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
extern s32 func_801716AC(s32 a0, void * a1, s32 * a2);
extern int func_800D0FE0(int a0);
extern void func_801717A0(void *a0);
extern void func_8013E588(void *a0);
extern void func_801717F4(void *a0);
extern void func_80171824(void *a0);
extern void func_80171854(void *a0);
extern void func_80171884(void);
extern void func_80171A1C(u8 *a0);
extern void func_80171928(void * a0);
extern void func_8017196C(s32 *a0, s8 a1);
extern void func_80171A04(s32 *a0);
extern void func_80171A10(s32 *a0);
extern void func_80171A34(s32 *a0, s8 a1);
extern s32 func_80171A44(u8 *a0);
extern s32 func_80171A58(u8 *a0);
extern s32 func_80171A6C(u8 *a0);
extern void func_80171A80(s32 *a0, s32 a1);
extern s32 func_80171A88(s32 a0);
extern s16 func_80171AB0(s32 param_1, void * _arg1);
extern void func_80171B10(void *a0);
extern void func_80171EC8(s32 a0);
extern s32 func_80171C64(s32 param_1, s32 param_2);
extern s32 func_80171D78(s32 a0, s32 a1);
extern int func_8017250C(short *a0, short *a1);
extern s32 func_80171CC4(void * a0, void * a1);
extern s32 func_80171FFC(short *a0, short *a1, s32 a2);
extern s32 func_80171D1C(void * a0, void * a1, s32 a2);
extern s32 func_8017248C(s32 a0, s32 a1);
extern s32 func_80171E08(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_80172170(s32 a0, s32 a1);
extern s32 func_8017209C(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_801722CC(s32 *a0);
extern void func_80172304(s32 *a0);
extern void func_80172310(u8 *a0);
extern void func_801723C4(s32 param_1, s32 param_2);
extern void func_80161C24(s32, s32);
extern void func_80172414(s32 a0);
extern s32 func_801724EC(s32 a0);
extern s32 func_8017248C(s32 arg0, s32 arg1);
extern s32 func_80013450(s32);
extern s32 func_80172560(u8 *a0, u8 *a1);
extern s32 func_8017261C(u8 *a0);
extern s32 func_80172644(u8 *a0);
extern s32 func_80172670(s32 *a0);
extern s32 func_80172688(s32 *a0);
extern s32 func_80172694(s32 *a0);
extern s32 func_801726A0(s32 *a0);
extern s32 func_801726AC(s32 *a0);
extern s32 func_801726B8(s32 *a0);
extern s32 func_801726C4(s32 *a0);
extern s32 func_80172760(s32 a0);
extern s32 func_80174650(s32);
extern void (*D_80127088)(void);
extern s32 D_801270BC;
extern s16 D_80126B0C;
extern void func_801726D0(void * _arg0);
extern void func_80172710(void);
extern void func_80174684(void *);
extern void func_80172738(void);
extern s16 D_80126B30;
extern s32 func_801727D0(void *a0);
extern void func_80172780(void *a0);
extern void func_80172844(u8 *a0);
extern void func_8017280C(u8 *a0);
extern void func_8017288C(void);
extern s32 func_801728E4(void *a0);
extern void func_80172894(void *a0);
extern void func_80172958(u8 *a0);
extern void func_80172920(u8 *a0);
extern s16 D_80126B36;
extern void func_80172958(u8 * a0);
extern void func_801729A8(void);
extern s32 func_801729F0(void *a0);
extern s16 D_80126B34;
extern s16 D_80126B32;
extern void func_801729B0(s32 a0);
extern void func_80172A8C(void *a0);
extern void func_80172A2C(int param_1);
extern void func_80172ACC(u8 *a0);
extern void func_80172B0C(void);
extern s32 func_80172B44(void *a0);
extern void func_80172B14(s16 a0);
extern s32 D_801150F8;
extern void func_80172BC8(void *a0);
extern void func_80172B80(u8 *a0);
extern void func_80172C48(void);
extern void (*D_8018DA88[])(void);
extern void func_80172CA0(void *a0);
extern void func_80172D14(u8 *a0);
extern void func_80172CDC(u8 *a0);
extern void func_80172D14(u8 * a0);
extern void func_80172D60(void);
extern s32 D_80127508;
extern s32 func_80172DAC(void *a0);
extern void func_80172D68(s32 a0);
extern void func_80172E20(u8 *a0);
extern void func_80172DE8(u8 *a0);
extern void func_80172E20(u8 * a0);
extern void func_80172E8C(void);
extern void func_8017303C(void *);
extern void func_80172E94(void);
extern void func_80172ED4(void);
extern void func_80172EFC(void);
extern void func_80172F24(void);
extern u8 D_800D47F4[];
extern void func_80172F4C(void);
extern void func_80172F9C(void);
extern u8 D_800D5C6C[];
extern void func_80172FEC(void);
extern s32 func_80173078(void *a0);
extern void func_8017303C(void * a0);
extern void func_801730FC(struct S801730FC *a0);
extern void func_801730B4(s32 a0);
extern void func_8017316C(void);
extern s32 func_8017319C(void *a0);
extern void func_80173174(void);
extern u8 D_800D5AA0[];
extern void func_80173220(void *a0);
extern void func_801731D8(s32 *a0);
extern M2C_UNK D_8018DA4C;
extern void func_80173220(void * arg0);
extern void func_80173294(void);
extern void func_801732C4();
extern void func_8017329C(void);
extern void func_801732C4(s32 *a0);
extern void func_8017331C();
extern void func_801732F4(void);
extern void func_8017331C(s32 *a0);
extern void func_80173374();
extern void func_8017334C(void);
extern void func_80173374(s32 *a0);
extern void func_801733A4(void);
extern void func_801733CC(s32 a0);
extern void func_801734BC(s32 a0, s32 a1);
extern s16 D_80126B3E;
extern void func_80173460(s32 a0, s32 a1);
extern void func_801734BC(s32 arg0, s32 _unused1);
extern void (*D_8018DAB8[])(void);
extern void func_80173544(void *a0);
extern void func_801735B8(u8 *a0);
extern void func_80173580(u8 *a0);
extern s16 D_80126B40;
extern void func_801735EC(void *a0);
extern void func_80173648(u8 *a0);
extern void func_801736A8(void);
extern s32 func_8014C118(void *a0, s32 a1, s32 a2);
extern s32 func_801736FC(void *a0);
extern void func_801736B0(s32 a0, s32 a1);
extern void func_80173770(u8 *a0);
extern void func_80173738(u8 *a0);
extern void func_801723C4(s32 a0, s32 a1);
extern void func_801737B0(void);
extern s32 func_801737E8(void *a0);
extern void func_801737B8(s16 a0);
extern void func_8017385C(u8 *a0);
extern void func_80173824(u8 *a0);
extern void func_801738D4(void);
extern s32 func_8017390C(void *a0);
extern void func_801738DC(s16 a0);
extern void func_80173980(u8 *a0);
extern void func_80173948(u8 *a0);
extern void func_801739D8(u8 *a0);
extern void func_80173A20(void);
extern s32 D_8012750C;
extern void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80173A28(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void (*D_8018DAF4[])(void);
extern void func_80173B4C(void *a0);
extern void func_80173BC0(u8 *a0);
extern void func_80173B88(u8 *a0);
extern void func_80173C64(u8 *a0);
extern void func_80173E1C(s32 a0);
extern s16 D_80126938;
extern s16 D_80126B3A;
extern void func_800D128C(s32, s32);
extern void func_80174158(s32 a0);
extern void func_8002A088(s32);
extern void func_8002A2D4(s32);
extern void func_8002A544(s32);
extern void func_8002A7B4(s32);
extern s32 func_80174188(s32 a0);
extern void func_801741A8(s32 a0);
extern s32  func_800D0EC4(void);
extern void func_800D0F0C(s32, s32);
extern void func_80145EE8(s32);
extern void func_80173EF8(void *param_1);
extern s32 func_8014BCEC(s32, s32);
extern void func_801741A8(s32 _arg0);
extern s16 D_80126B3C;
extern s16 D_8011F9C8;
extern void func_801741EC(u8 *a0);
extern void func_80174274(void);
extern s32 func_801742A4(void *a0);
extern void func_8017427C(void);
extern void func_80174318(u8 *a0);
extern void func_801742E0(u8 *a0);
extern void func_80174354(void);
extern s32 func_80174384(void *a0);
extern void func_8017435C(void);
extern void func_801743F0(u8 *a0);
extern void func_801743C0(u8 *a0);
extern void func_801743F0(u8 * a0);
extern void func_80174430(void);
extern s32 func_80174474(void *a0);
extern void func_80174438(s32 a0);
extern void func_801744E0(u8 *a0);
extern void func_801744B0(u8 *a0);
extern void func_80174524(void);
extern void func_80174554();
extern void func_8017452C(void);
extern void func_80174554(s32 arg0);
extern void func_801745AC();
extern void func_80174584(void);
extern void func_801745AC(s32 *a0);
extern void func_80174604(void);
extern void func_801745DC(void);
extern void func_80174630(void);
extern s32 func_80174650(s32 _arg0);
extern void func_80174674(void);
extern void func_801746A4(void);
extern s32 func_800CF8CC(void);
extern void func_80174714(void);
extern s32 func_80174754(void);
extern s16 func_80174764(void);
extern s16 func_80174774(void);
extern s32 func_801747CC(void *a0);
extern void func_80174784(void);
extern s32 func_801747AC(s32 a0);
extern s32 func_80174808(u8 *a0);
extern void func_8017481C(void);
extern s32 func_80174888(void *a0);
extern void func_80174824(void);
extern void func_8017484C(s32 a0);
extern void func_801748C4(s32 a0);
extern void func_801748E4(void);
extern void func_8012A018(s32 a, s32 b);
extern s32 func_8017496C(void *a0);
extern s32 D_80126954;
extern s32 D_80126950;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern void func_801748EC(void);
extern s32 func_801749C8(s32);
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_8018DB4C[])();
extern void func_80174BF4(void * arg0);
extern s32 func_80174CB0(s32, s32);
extern s32 func_80174C60(s32 a0);
extern void func_80174C80(s32 a0);
extern s32 D_8012697C;
extern u16 D_80126980;
extern s32 func_80174F28(void *a0);
extern void func_80174E9C(s32 a0);
extern void func_80174EF0(s32 a0, s16 a1);
extern s32 func_80175014(u8 *a0, u8 *a1, s32 a2);
extern void func_80174F64(u8 *a0);
extern void func_80174FBC(u8 *a0);
extern s32 func_8017509C(u8 *a0, s32 a1, u8 *a2, u8 *a3);
extern void func_80175184(s32 *a0);
extern void func_80175114(s32 *a0);
extern void func_80175184();
extern void func_80175150(s32 *a0);
extern void (*D_8018DB5C[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018DB64[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018DCCC[])();
extern s32 func_801758FC(void);
extern s32 func_80175820(void);
extern s32 func_801759D8(void);
extern void func_8017553C(s32 *param);
extern void func_801757A0(s32 a0);
extern short D_800B9A02;
extern void func_80175590(void *arg0);
extern s16 D_800B9A02;
extern void func_801757A0(s32);
extern void func_80175624(void *a0);
extern void func_801757E0(int);
extern void func_80175668(void);
extern void (*D_8018DCD8[])();
extern void func_80175690(s32 *param);
extern void func_80175DA8(s32 a0);
extern void func_80175AB8(s32 a0);
extern void func_80176144(s32 a0);
extern void func_801756E4(s32 arg0);
extern void func_80175798(void);
extern void func_80176734(s32 a0);
extern void func_80176218(s32 a0);
extern void func_80176D00(s32 a0);
extern void func_801757E0(s32 a0);
extern s32 func_80178004(s32 a0, s32 a1, s32 a2);
extern u8 D_8011F7B1;
extern u16 D_8011F7B4;
extern u16 D_8011F7B6;
extern s16 D_8011F81E;
extern void *func_80177784(void *a0, s32 a1, s32 a2, s32 a3);
extern u32 func_801783D0(s32 a0, s32 a1);
extern void *func_801777BC(void *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern u16 D_8011F82C;
extern u16 D_8011F82A;
extern u32 * func_80176D94(void *param_1, u32 param_2, s16 param_3_);
extern void func_801778A8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80176FF4(s32 a0);
extern u16 D_8011F830;
extern u16 D_8011F82E;
extern u32 * func_801770E0(void *param_1, u32 param_2, s16 param_3_);
extern void func_80177340(s32 a0);
extern u8 D_8011F837;
extern u8 D_8011F7F0;
extern u8 D_8011F7AB;
extern u32 * func_8017742C(u32 *param_1, s32 param_2, s32 param_3);
extern void func_801776EC(u8 *a0);
extern void * func_80177784(void *a0, s32 a1, s32 a2, s32 a3);
extern uint * func_80177EA4(uint *param_1, int param_2, uint param_3, int param_4);
extern void func_80177F84(s32 param_1, s32 param_2);
extern u32 * func_80178298(u32 *param_1, u8 *param_2, short param_3, short param_4);
extern M2C_UNK D_801EE104;
extern void func_80178438(u16 *arg0);
extern void func_801787D4(void);
extern void func_8012A908(void);
extern void func_8017869C(s32 a0);
extern void func_80130D0C(s32 a0);
extern void func_8013E370(void);
extern s32 D_8011DB08;
extern void func_8017849C(void);
extern void func_8013E4B4(void);
extern s16 D_801270C4;
extern s32 D_801274D8;
extern s16 D_801270C2;
extern u8 D_801270C6;
extern u8 D_801270C7;
extern s32 D_801274DC;
extern s32 D_801274E0;
extern void func_80178608(void);
extern void func_80178744(s32 a0, s32 a1);
extern void func_80178840();
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern int func_801789AC(void);
extern s16 D_801EFCC0;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801EF2B8;
extern short D_801EFD34;
extern void func_80178CBC(s32 arg0, s32 arg1);
extern void func_80178D18(void);
/* ==== end §8b carried decl layer ==== */


/* func_80178D40 - 890 ins, 94-case jr switch (jtbl_801D8E24).
 * STATUS: **MATCH** -- 890/890 ins, byte-exact (masked). PIN-FREE (this body is
 * templated across 134 overlays; a pinned body would crash the sibling TUs).
 *   python3 tools/match_one.py func_80178D40 --c .run/phase26-cracks/func_80178D40.c \
 *       --asm-subdir asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_801734BC
 *   => MATCH (890 ins)
 * Jump table VERIFIED: 94 entries (= the sltiu 0x5E bound, no trailing zero pad),
 * 93 unique blocks, cases 0xF/0x3F share one block; my case->block sequence is
 * identical to jtbl_801D8E24's.
 *
 * Byte-derived structure (the levers that cracked it):
 *  1. NO status variable. Every case stores `(*(s16*)&D_801EFD34) = K` DIRECTLY. The shared
 *     `sh $v0, (*(s16*)&D_801EFD34)` at .L80179AEC is a jump2 CROSS-JUMP merge of those stores:
 *     find_cross_jump's FIRST call (minimum=1, vs the code before the target label)
 *     matches that 1 insn, and because it succeeds the jump_chain loop (minimum=2) is
 *     SKIPPED -- which is what BLOCKS the deeper, wrong 3-insn merges of the identical
 *     func_80137614 tails (cases 0/0x45/0x32). reorg then steals the `li K` back into
 *     each `j` delay slot, so it looks un-merged. A `status` pseudo instead of direct
 *     stores loses that block and costs 6 insns.
 *  2. after-switch = `D_801EF2B8 += 8;` (.L80179AF4) -> the out-of-range default lands
 *     there with NO explicit `default:` label.
 *  3. arg0/arg1/pv are STRUCT pointers. gcc-2.7.2 sched alias (sched.c true_dependence)
 *     only lets a MEM_IN_STRUCT varying-address load hoist above a non-MEM_IN_STRUCT
 *     fixed-address store (the (*(s16*)&D_801EFD34) store). Raw `*(T *)(int + off)` casts get
 *     MEM_IN_STRUCT_P = 0 and block that hoist -> stray nops.
 *  4. g = &D_801EFC90 stays a plain `s16 *` (NOT a struct ptr) so its varying,
 *     non-in-struct stores keep their order w.r.t. the loads.
 *  5. Statement order inside the D_801EFC90 cases is load-bearing (sched LUID/priority):
 *     g[0],g[2],g[1] in 0x25/0x48/0x26; g[7],g[8],g[1],g[3] in 0x4F/0x28.
 *  6. Cases 0x5B/0x5C: the loops "found" bodies are emitted BEFORE the case label ->
 *     source-level labels placed between cases + `goto`.
 *  7. Per-case temporaries are BLOCK-LOCAL (local-alloc), not function-scope.
 *  8. stack locals declared in slot order (0x10,0x18,0x20,0x28,0x30,0x38,0x40,0x48,
 *     0x50,0x58,0x60) -> frame 0x78.
 *
 * Case 0x5C -- the last 39 residuals. Four levers, all generalizable:
 *
 *  9. NO-PEEL: a `break` out of a do-while whose target COINCIDES with the loop's own
 *     natural fall-through exit makes NOTE_INSN_LOOP_BEG be followed by an
 *     unconditional jump -> jump.c `duplicate_loop_exit_test` (jump.c:599/2131) rotates
 *     the loop and peels iteration 1 (here `i` was provably 0, so the peeled `i++`
 *     const-folded to `li $a2,1` and dragged an extra lui/addiu/lw address block with
 *     it). Writing `goto L5D;` instead of `break;` -- SAME destination, different
 *     construct -- keeps the loop a plain do-while and the peel disappears.
 *     RULE: never let a loop's `break` land on the loop's own fall-through label.
 *
 * 10. SURVIVING REG-REG COPY (residual #1, `addu $v1,$v0,$zero`). A source-level
 *     `fp = q;` copy ALWAYS dies: cse.c `canon_reg` rewrites every later use of `fp`
 *     to `q` (qty_first_reg keeps the older reg) and flow deletes the now-dead set.
 *     To make a copy SURVIVE, its def and its uses must sit in different extended basic
 *     blocks -- cse resets its hash table at a label with >1 predecessor (a loop top).
 *     So: TEST THE MEM DIRECTLY, then assign the variable inside the branch body:
 *         if (arg1->a.w != 0) { fp5c = arg1->a.w; ... do { ... fp5c ... } while (); }
 *     cse folds the redundant 2nd load into `fp5c = <load temp>` (a copy) in the guard
 *     block, but CANNOT propagate it into the loop body -> the copy is emitted.
 *     (Assigning `fp5c` BEFORE the test gives one pseudo and no copy -- what we had.)
 *
 * 11. CROSS-JUMP-MERGED `(*(s16*)&D_801EFD34) = 3` (residual #2). `if (i != 10) { (*(s16*)&D_801EFD34) = 3;
 *     break; }` lets jump2 tail-merge the `lui/sh` into the shared .L80179AEC tail and
 *     reorg steal the `li 3` into the `bne` delay slot. Storing it unconditionally
 *     BEFORE the `if` blocks the merge and costs 3 inline insns.
 *
 * 12. THE UN-COALESCED LOOP COPY (residual #3, `addu $v1,$a0,$zero` + `addiu $a0,$v1,4`).
 *     This is loop.c's NON-REPLACEABLE DEST_REG GIV, not a source-level copy (see #10:
 *     those always die). Recipe -- BOTH halves are needed:
 *       a) make the pointer an INDEX GIV: `p5c = &D_801EF714[i5c];`  (a DEST_REG giv)
 *       b) make it NON-replaceable so loop.c emits `emit_insn_after(move dest,new_reg)`
 *          (loop.c:3945): record_giv (loop.c:4437) needs the giv used OUTSIDE the loop
 *          -- so the "found" body goes AFTER the loop and stores through `p5c`.
 *       c) put the BIV increment (`i5c++`) LAST in the body. loop.c inserts the reduced
 *          giv's `addiu` immediately BEFORE the biv's increment insn, so `i5c++` at the
 *          bottom puts `addiu $a0,$v1,4` in the loop-back delay slot. With `i5c++` at
 *          the TOP the giv-add lands at the top, nothing is left to fill the delay slot,
 *          and reorg STEALS the loop-top `move` into it (duplicating it: +1 insn).
 *
 * 13. Loop3 needs its OWN pointer pseudo (`r5c`, not `q5c`). `q5c` is loop1's pointer,
 *     and in loop1 $v1 is held by `fp5c` -> q5c is forced to $a0, and loop3 inherits it.
 *     Both "found" bodies then read $a0, become identical, and jump2 CROSS-JUMPS them
 *     into one block (-2 insns). A distinct pseudo frees loop3 into $v1, so found3
 *     (`sw $zero,0($v1)`) differs from found2 (`sw $zero,0($a0)`) and they stay separate.
 *     RULE: two structurally identical loops must differ in REGISTER, or cross_jump
 *     merges their tails.
 */

typedef struct { s16 vx, vy, vz, pad; } SV3_80178D40;
typedef struct { u8 pad0[0x12]; u16 unk12; } Obj20_80178D40;
typedef struct { u16 f0; u16 f2; u16 f4; u16 f6; } Blk_80178D40;

typedef struct Actor_80178D40 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u16 unk6;
    s16 unk8;
    u16 unkA;
    s16 unkC;
    u16 unkE;
    u8 pad10[0x20 - 0x10];
    Obj20_80178D40 *unk20;
    u8 pad24[0x34 - 0x24];
    s16 unk34;
    u8 pad36[0xD4 - 0x36];
    struct Actor_80178D40 *unkD4;
    s32 unkD8;
    s32 unkDC[7];
    s32 unkF8;
    u8 padFC[0x10A - 0xFC];
    s16 unk10A;
} Actor_80178D40;

typedef struct {
    s32 op;
    union {
        s32 w;
        void *p;
        s16 h[2];
        u16 uh[2];
    } a;
} Cmd_80178D40;



s32 func_80178D40(s32 arg0, s32 arg1)
{
    extern void func_80179B28(s32);
    extern s32 func_80137614(s32, s32, s32);
    extern void func_8012F214(void *, void *, void *);
    extern void func_8012F40C(void *, void *);
    extern void func_80179D30(void *);
    extern void func_80179D78(void *);
    extern void func_80179EA0(void *);
    extern void func_80179DCC(s32);
    extern void func_80179DF8(void);
    extern void func_80179E1C(s32);
    extern void func_80179E48(s32);
    extern void func_80179E74(s32);
    extern void func_80179EE8(s32);
    extern void func_80179F14(s32, s32);
    extern void func_80179F44(void);
    extern void func_80179F6C(s32);
    extern void func_80179F98(s32);
    extern void func_80179FEC(s32);
    extern void func_8017A040(s32);
    extern void func_8017A094(s32);
    extern void func_8017A0C4(s32);
    extern void func_8017A0F4(void);
    extern void func_8017A11C(void);
    extern void func_8017A144(s32);
    extern void func_8017A180(void);
    extern void func_8017A1A8(void);
    extern void func_8017A1D0(void);
    extern void func_8017A1F8(void);
    extern void func_8017A220(void);
    extern void func_8017A248(void);
    extern void func_8017A270(void);
    extern void func_8017A298(void);
    extern void func_8017A2C0(void);
    extern void func_8017A2E8(void);
    extern void func_8017A310(void);
    extern void func_8017A338(void);
    extern void func_8017A360(void);
    extern void func_8017A388(void);
    extern void func_8017A3B0(void);
    extern void func_8017A3D8(void);
    extern void func_8017AD0C(s32);
    extern void func_8017B238(void *, s32);
    extern void func_8017B614(void *, s32);
    extern void func_8017B7A8(void *);
    extern void func_8017B824(void);
    extern void func_8017B880(void);
    extern void func_8017B940(void *);
    extern void func_8017BA3C(void *, s32);
    extern void func_8017BB34(void *, s32);
    extern void func_8012A828(void *, s32);
    extern s32 func_8012B8A4(void *);
    extern void func_8012E88C(void *);
    extern void func_8012E8A8(void *);
    extern void func_8001AAD0(s32, s32);
    extern s32 D_801EF2BC;
    extern s32 D_801EF6D0;
    extern s16 D_801EF6D4;
    extern s16 D_801EF6D8;
    extern s16 D_801EF6DC;
    extern s16 D_801EF6E0;
    extern s32 D_801EF6E8;
    extern s32 D_801EF6EC;
    extern s32 D_801EF6FC;
    extern s16 D_801EF700;
    extern s16 D_801EF704;
    extern s32 D_801EF708;
    extern s32 D_801EF710;
    extern s32 D_801EF714[10];
    extern s32 D_801EFBD8;
    extern s16 D_801EFC90;
    extern s32 D_801EFCBC;


    SV3_80178D40 v10, v18, v20, v28, v30, v38, v40, v48;
    s32 out50[2];
    SV3_80178D40 v58, v60;
    Actor_80178D40 *pv = &(*(Actor_80178D40*)&D_80126B58);
    s32 i5b, i5c, fp5b, fp5c;
    s32 *q5b, *q5c, *p5c, *r5c;
    s16 *g = &D_801EFC90;

    switch (((Cmd_80178D40 *)arg1)->op) {
    case 1:
        func_80179B28(D_801EF6D0);
        D_801EF6D0 = func_80137614(((Cmd_80178D40 *)arg1)->a.w, D_801EF6DC, D_801EF6E0 ? 0x48 : 0x40);
        (*(s16*)&D_801EFD34) = 2;
        break;
    case 0:
        func_80179B28(D_801EF6D0);
        D_801EF6D0 = func_80137614(((Cmd_80178D40 *)arg1)->a.w, D_801EF6D4, D_801EF6D8 ? 0x48 : 0x40);
        (*(s16*)&D_801EFD34) = 1;
        break;
    case 0x45:
        ((void (*)(s32))((Cmd_80178D40 *)arg1)->a.w)(((Actor_80178D40 *)arg0));
        if (D_801EFBD8 != 0) {
            func_80179B28(D_801EF6D0);
            D_801EF6D0 = func_80137614(((Actor_80178D40 *)arg0)->unkDC[1], D_801EF6D4, D_801EF6D8 ? 0x48 : 0x40);
            (*(s16*)&D_801EFD34) = 1;
        } else {
            (*(s16*)&D_801EFD34) = 3;
        }
        break;
    case 0x32:
        func_80179B28(D_801EF6D0);
        D_801EF6D0 = func_80137614(((Actor_80178D40 *)arg0)->unkDC[((Cmd_80178D40 *)arg1)->a.w], D_801EF6D4,
                                   D_801EF6D8 ? 0x48 : 0x40);
        (*(s16*)&D_801EFD34) = 1;
        break;
    case 2:
        func_80179B28(D_801EF6D0);
        if (D_801EF6E8 != 0) {
            D_801EF2B8 = D_801EF6E8;
            D_801EF6E8 = 0;
            (*(s16*)&D_801EFD34) = 3;
            return;
        }
        (*(s16*)&D_801EFD34) = 6;
        break;
    case 6:
        func_80179DF8();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 3:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_80179D30(&v10);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 4:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_8012F214(((Actor_80178D40 *)arg0), &v10, &v18);
        func_80179D30(&v18);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x4C:
        func_80179D78((void *)((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x4D:
        v10.vx = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f0;
        v10.vy = 0;
        v10.vz = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f4;
        func_8012F214(((Actor_80178D40 *)arg0), &v10, &v18);
        v18.pad = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f6;
        func_80179D78(&v18);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x15:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_8012F214(((Actor_80178D40 *)arg0)->unkD4, &v10, &v18);
        func_80179D30(&v18);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 5:
        func_80179DCC(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 7:
        func_80179E1C(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 8:
        func_80179E74(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 9:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_80179EA0(&v10);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0xA:
        v10.vx = ((Actor_80178D40 *)arg0)->unk6;
        v10.vy = ((Actor_80178D40 *)arg0)->unkA;
        v10.vz = ((Actor_80178D40 *)arg0)->unkE;
        func_80179EA0(&v10);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x16: {
        Actor_80178D40 *p = ((Actor_80178D40 *)arg0)->unkD4;
        v10.vx = p->unk6;
        v10.vy = p->unkA;
        v10.vz = p->unkE;
        func_80179EA0(&v10);
        (*(s16*)&D_801EFD34) = 3;
        break;
    }
    case 0xB:
        func_8017A0F4();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0xC:
        func_8017A11C();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0xD:
        func_8017A180();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0xE:
        func_8017A1A8();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x10:
        func_8017A1D0();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x46:
        func_8017A1F8();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x59:
        func_8017A220();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x5A:
        func_8017A248();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x49:
        func_8017A144(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x47:
        func_8017A270();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x17:
        func_80179EE8(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x18:
        func_80179F14(((Cmd_80178D40 *)arg1)->a.h[0], ((Cmd_80178D40 *)arg1)->a.h[1]);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x19:
        func_80179F6C(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x1A:
        func_80179F98(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x51:
        func_8017A040(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x1B:
        D_801EF708 = ((Cmd_80178D40 *)arg1)->a.w;
        func_80179F44();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x1C:
        func_8017A338();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x52:
        func_8017A360();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x1D:
        func_8017A388();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x3B:
        func_8017A094(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x3C:
        func_8017A0C4(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0xF:
    case 0x3F:
        (*(s16*)&D_801EFD34) = 4;
        D_801EF2BC = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x3E:
        (*(s16*)&D_801EFD34) = 5;
        D_801EF6FC = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x40:
        D_801EF6FC = (s32)func_8017A3B0;
        (*(s16*)&D_801EFD34) = 5;
        break;
    case 0x23:
        func_8012A828(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x31:
        func_8012A828(((Actor_80178D40 *)arg0), ((Actor_80178D40 *)arg0)->unkDC[((Cmd_80178D40 *)arg1)->a.w]);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x24:
        (*(s16*)&D_801EFD34) = 3;
        ((Actor_80178D40 *)arg0)->unk20->unk12 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x25:
        g[0] = 1;
        g[2] = ((Actor_80178D40 *)arg0)->unk20->unk12 + ((Cmd_80178D40 *)arg1)->a.uh[0];
        g[1] = 0x1E;
        (*(s16*)&D_801EFD34) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x48:
        g[0] = 1;
        g[2] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        g[1] = 0x1E;
        (*(s16*)&D_801EFD34) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x26:
        g[0] = 1;
        g[2] = func_8012B8A4(((Actor_80178D40 *)arg0));
        g[1] = 0x1E;
        (*(s16*)&D_801EFD34) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x3D:
        ((void(*)(void *, s32))func_8012E8E0)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x27:
        g[0] = 2;
        g[4] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_801EFD34) = 3;
        g[1] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x4F:
        g[5] = 1;
        g[0] = 3;
        g[6] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_801EFD34) = 3;
        g[7] = ((Actor_80178D40 *)arg0)->unkA;
        g[8] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        g[1] = 0x10;
        g[3] = 4;
        /* fallthrough */
    case 0x28:
        g[5] = 0;
        g[0] = 3;
        g[6] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_801EFD34) = 3;
        g[7] = ((Actor_80178D40 *)arg0)->unkA;
        g[8] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        g[1] = 0x10;
        g[3] = 4;
        break;
    case 0x29:
        v20.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v20.vy = ((Actor_80178D40 *)arg0)->unkA;
        v20.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_8012F214(((Actor_80178D40 *)arg0), &v20, &v28);
        g[5] = 0;
        g[0] = 3;
        *(SV3_80178D40 *)(g + 6) = v28;
        g[1] = 0x10;
        g[3] = 4;
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x50:
        v30.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v30.vy = ((Actor_80178D40 *)arg0)->unkA;
        v30.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_8012F214(((Actor_80178D40 *)arg0), &v30, &v38);
        g[5] = 1;
        g[0] = 3;
        *(SV3_80178D40 *)(g + 6) = v38;
        g[1] = 0x10;
        g[3] = 4;
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x2A:
        g[0] = 4;
        (*(s16*)&D_801EFD34) = 3;
        g[1] = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x1E:
        func_8017B238(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x21:
        func_8017BA3C(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B238(((Actor_80178D40 *)arg0), (s32)&D_801EF6EC);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x54:
        func_8017BB34(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B238(((Actor_80178D40 *)arg0), (s32)&D_801EF6EC);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x1F:
        func_8017B614(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x22:
        func_8017BA3C(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B614(((Actor_80178D40 *)arg0), (s32)&D_801EF6EC);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x55:
        func_8017BB34(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B614(((Actor_80178D40 *)arg0), (s32)&D_801EF6EC);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x20:
        func_8017B7A8(((Actor_80178D40 *)arg0));
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x4E:
        D_801EF710 = ((Cmd_80178D40 *)arg1)->a.w;
        func_8017B940(((Actor_80178D40 *)arg0));
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x57:
        func_8017B824();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x58:
        func_8017B880();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x2B:
        (*(s16*)&D_801EFD34) = 3;
        ((Actor_80178D40 *)arg0)->unk2 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2C:
        (*(s16*)&D_801EFD34) = 3;
        ((Actor_80178D40 *)arg0)->unk34 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2D:
        (*(s16*)&D_801EFD34) = 3;
        ((Actor_80178D40 *)arg0)->unkD8 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2F:
        (*(s16*)&D_801EFD34) = 3;
        ((Actor_80178D40 *)arg0)->unk10A = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2E:
        (*(s16*)&D_801EFD34) = 3;
        ((Actor_80178D40 *)arg0)->unkF8 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x11:
        func_8017A298();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x12:
        func_8017A2C0();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x13:
        func_8017A2E8();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x14:
        func_8017A310();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x33: {
        void (*f)(Actor_80178D40 *) = (void (*)(Actor_80178D40 *))((Cmd_80178D40 *)arg1)->a.w;
        D_801EFCBC = (s32)&((Cmd_80178D40 *)arg1)[1];
        f(((Actor_80178D40 *)arg0));
        (*(s16*)&D_801EFD34) = 3;
        break;
    }
    case 0x30:
        if (((Cmd_80178D40 *)arg1)->a.w == 0) {
            func_8012E8A8(((Actor_80178D40 *)arg0));
            (*(s16*)&D_801EFD34) = 3;
        } else {
            func_8012E88C(((Actor_80178D40 *)arg0));
            (*(s16*)&D_801EFD34) = 3;
        }
        break;
    case 0x4A:
        ((void(*)())func_80175414)();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x4B:
        func_80175454();
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x34:
        (*(s16*)&D_801EFD34) = 3;
        D_801EF2B8 = ((Cmd_80178D40 *)arg1)->a.w;
        return;
    case 0x35:
        D_801EF6E8 = (s32)&((Cmd_80178D40 *)arg1)[1];
        (*(s16*)&D_801EFD34) = 3;
        D_801EF2B8 = ((Cmd_80178D40 *)arg1)->a.w;
        return;
    case 0x36:
        (*(s16*)&D_801EFD34) = 3;
        D_801EF2B8 += 8;
        if (((s32 (*)(s32))((Cmd_80178D40 *)arg1)->a.w)(((Actor_80178D40 *)arg0)) == 0) {
            break;
        }
        D_801EF2B8 = *(s32 *)(D_801EF2B8 + 4);
        return;
    case 0x37:
        (*(s16*)&D_801EFD34) = 3;
        D_801EF6D4 = ((Cmd_80178D40 *)arg1)->a.uh[0];
        D_801EF6D8 = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x38:
        (*(s16*)&D_801EFD34) = 3;
        D_801EF6DC = ((Cmd_80178D40 *)arg1)->a.uh[0];
        D_801EF6E0 = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x39: {
        s32 w1, w2;
        v40.vx = ((Actor_80178D40 *)arg0)->unk6;
        v40.vy = ((Actor_80178D40 *)arg0)->unkA;
        v40.vz = ((Actor_80178D40 *)arg0)->unkE;
        v48.vx = pv->unk6;
        v48.vy = pv->unkA;
        v48.vz = pv->unkE;
        func_8012F40C(out50, &v40);
        w1 = out50[0];
        func_8012F40C(out50, &v48);
        w2 = out50[0];
        (*(s16*)&D_801EFD34) = 3;
        D_801EF6D4 = w1;
        D_801EF6D8 = (s16)w1 >= (s16)w2;
        break;
    }
    case 0x3A: {
        s32 w1, w2;
        v58.vx = ((Actor_80178D40 *)arg0)->unk6;
        v58.vy = ((Actor_80178D40 *)arg0)->unkA;
        v58.vz = ((Actor_80178D40 *)arg0)->unkE;
        v60.vx = pv->unk6;
        v60.vy = pv->unkA;
        v60.vz = pv->unkE;
        func_8012F40C(out50, &v58);
        w1 = out50[0];
        func_8012F40C(out50, &v60);
        w2 = out50[0];
        (*(s16*)&D_801EFD34) = 3;
        D_801EF6DC = w2;
        D_801EF6E0 = (s16)w1 < (s16)w2;
        break;
    }
    case 0x41:
        ((void(*)(s32, s32))func_8002D4C8)(((Cmd_80178D40 *)arg1)->a.uh[0], ((Cmd_80178D40 *)arg1)->a.uh[1]);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x42:
        func_8017AD0C(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x43:
        D_801EF6FC = (s32)func_8017A3D8;
        D_801EF704 = 0;
        (*(s16*)&D_801EFD34) = 5;
        D_801EF700 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x44:
        func_8001AAD0(((Cmd_80178D40 *)arg1)->a.h[0], ((Cmd_80178D40 *)arg1)->a.h[1]);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x53:
        func_80179E48(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x56:
        func_80179FEC(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801EFD34) = 3;
        break;
    L5B_found:
        fp5b = ((Cmd_80178D40 *)arg1)->a.w;
        *q5b = fp5b;
        ((void (*)(Actor_80178D40 *))fp5b)(((Actor_80178D40 *)arg0));
        (*(s16*)&D_801EFD34) = 3;
        break;
    case 0x5B:
        i5b = 0;
        q5b = D_801EF714;
        do {
            i5b++;
            if (*q5b == 0) {
                goto L5B_found;
            }
            q5b++;
        } while (i5b < 10);
        (*(s16*)&D_801EFD34) = 3;
        break;
    L5C_found1:
        *q5c = 0;
        goto L5C_join;
    case 0x5C:
        i5c = 0;
        if (((Cmd_80178D40 *)arg1)->a.w != 0) {
            fp5c = ((Cmd_80178D40 *)arg1)->a.w;
            q5c = D_801EF714;
            do {
                if (*q5c == fp5c) {
                    goto L5C_found1;
                }
                i5c++;
                q5c++;
            } while (i5c < 10);
        L5C_join:
            if (i5c != 10) {
                (*(s16*)&D_801EFD34) = 3;
                break;
            }
            i5c = 0;
            do {
                p5c = &D_801EF714[i5c];
                if (*p5c != 0) {
                    goto L5C_found2;
                }
                i5c++;
            } while (i5c < 10);
            (*(s16*)&D_801EFD34) = 3;
            break;
        L5C_found2:
            *p5c = 0;
            goto L5D;
        }
        r5c = D_801EF714;
        do {
            i5c++;
            if (*r5c != 0) {
                *r5c = 0;
                goto L5D;
            }
            r5c++;
        } while (i5c < 10);
        /* fallthrough */
    case 0x5D:
    L5D:
        (*(s16*)&D_801EFD34) = 3;
        break;
    default:
        break;
    }
Lend:
    D_801EF2B8 += 8;
}


DEFINE_func_80179B28()  /* dedup: shared engine-core @0x80179B28 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80179B74);

DEFINE_func_80179D30()  /* dedup: shared engine-core @0x80179D30 (src/shared) */

DEFINE_func_80179D78()  /* dedup: shared engine-core @0x80179D78 (src/shared) */

DEFINE_func_80179DCC()  /* dedup: shared engine-core @0x80179DCC (src/shared) */

DEFINE_func_80179DF8()  /* dedup: shared engine-core @0x80179DF8 (src/shared) */

DEFINE_func_80179E1C()  /* dedup: shared engine-core @0x80179E1C (src/shared) */

DEFINE_func_80179E48()  /* dedup: shared engine-core @0x80179E48 (src/shared) */

DEFINE_func_80179E74()  /* dedup: shared engine-core @0x80179E74 (src/shared) */

DEFINE_func_80179EA0()  /* dedup: shared engine-core @0x80179EA0 (src/shared) */

DEFINE_func_80179EE8()  /* dedup: shared engine-core @0x80179EE8 (src/shared) */

DEFINE_func_80179F14()  /* dedup: shared engine-core @0x80179F14 (src/shared) */

DEFINE_func_80179F44()  /* dedup: shared engine-core @0x80179F44 (src/shared) */

DEFINE_func_80179F6C()  /* dedup: shared engine-core @0x80179F6C (src/shared) */

DEFINE_func_80179F98()  /* dedup: shared engine-core @0x80179F98 (src/shared) */

DEFINE_func_80179FEC()  /* dedup: shared engine-core @0x80179FEC (src/shared) */

DEFINE_func_8017A040()  /* dedup: shared engine-core @0x8017A040 (src/shared) */


extern void func_80179B74(s16 *a0);
extern s32 D_801EF6E4;

void func_8017A094(s32 arg0) {
    s16 sp10;

    D_801EF6E4 = arg0;
    sp10 = 0x15;
    func_80179B74(&sp10);
}



extern void func_80179B74(s16 *a0);
extern s32 D_801EF6E4;

void func_8017A0C4(s32 arg0) {
    s16 sp10;

    D_801EF6E4 = arg0;
    sp10 = 0x16;
    func_80179B74(&sp10);
}


DEFINE_func_8017A0F4()  /* dedup: shared engine-core @0x8017A0F4 (src/shared) */

DEFINE_func_8017A11C()  /* dedup: shared engine-core @0x8017A11C (src/shared) */


extern s32 D_801EF70C;
extern void func_80179B74(s16 *a0);

void func_8017A144(s32 a0) {
    s16 sp10;
    sp10 = 0x1B;
    func_80179B74(&sp10);
    D_801EF70C = a0;
}


DEFINE_func_8017A180()  /* dedup: shared engine-core @0x8017A180 (src/shared) */

DEFINE_func_8017A1A8()  /* dedup: shared engine-core @0x8017A1A8 (src/shared) */

DEFINE_func_8017A1D0()  /* dedup: shared engine-core @0x8017A1D0 (src/shared) */

DEFINE_func_8017A1F8()  /* dedup: shared engine-core @0x8017A1F8 (src/shared) */

DEFINE_func_8017A220()  /* dedup: shared engine-core @0x8017A220 (src/shared) */

DEFINE_func_8017A248()  /* dedup: shared engine-core @0x8017A248 (src/shared) */

DEFINE_func_8017A270()  /* dedup: shared engine-core @0x8017A270 (src/shared) */

DEFINE_func_8017A298()  /* dedup: shared engine-core @0x8017A298 (src/shared) */

DEFINE_func_8017A2C0()  /* dedup: shared engine-core @0x8017A2C0 (src/shared) */

DEFINE_func_8017A2E8()  /* dedup: shared engine-core @0x8017A2E8 (src/shared) */

DEFINE_func_8017A310()  /* dedup: shared engine-core @0x8017A310 (src/shared) */

DEFINE_func_8017A338()  /* dedup: shared engine-core @0x8017A338 (src/shared) */

DEFINE_func_8017A360()  /* dedup: shared engine-core @0x8017A360 (src/shared) */

DEFINE_func_8017A388()  /* dedup: shared engine-core @0x8017A388 (src/shared) */


extern s16 D_801EF6C8;

s32 func_8017A3B0(void) {
    switch (D_801EF6C8) {
    case 0:
        return 1;
    case 1:
        return 0;
    default:
        return 1;
    }
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017A3D8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017A4AC);

DEFINE_func_8017AD0C()  /* dedup: shared engine-core @0x8017AD0C (src/shared) */

DEFINE_func_8017ADE8()  /* dedup: shared engine-core @0x8017ADE8 (src/shared) */

DEFINE_func_8017AE08()  /* dedup: shared engine-core @0x8017AE08 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017AE2C);

// @class: plumbing
// @stuck: none — MATCH


void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_801EF744;
    extern s16 D_801EF746;
    extern s16 D_801EF748;
    extern s16 D_801EF73C;
    extern s16 D_801EF73E;
    extern s16 D_801EF740;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801EF744, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801EF746, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801EF748, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801EF73C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801EF73E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801EF740, (s32)((s16)param_2));
}



extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_801EF6CC;
extern u16 D_801EF74C;
extern u16 D_801EF74E;
extern u16 D_801EF750;
extern s16 D_801EFCC0;

void func_8017B1D8(void) {
    func_8012A418();
    D_801EFCC0 = 0;
    D_801EF6CC = 0;
    D_801EF74C = D_80126B5E;
    D_801EF74E = D_80126B62;
    D_801EF750 = D_80126B66;
}


// @class: regalloc-order — simplified sibling of matched func_8017B614.
// @stuck: none. Block-moves are align-1 struct-assigns (u8[8]) -> emit_block_move
// (unaligned lwl/lwr/swl/swr), ZERO memcpy-symbol reference, so the TU's `extern memcpy`
// (which turned the old draft's memcpy into a CALL -> DIFF 64) can't drift this.
// $16 pin + in-place re-tie keeps param_2 in $a1 until the >=0xB branch, then $s0 for loads.

typedef struct { u8 b[8]; } Blk8_8017B238_8017B238;

s32 func_8017B238(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018DE14[];
    extern s16 D_801EF744;
    extern s16 D_801EF73C;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_8018DE14[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018DE14[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801EF744;
        s16 *p78C = &D_801EF73C;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801EFCC0 = 1;
        D_801EF6CC = 0;
    }
}



// @class: struct
// @stuck: none — MATCH (74 ins)

typedef struct { s16 a, b, c, d; } SV4_8017B368;      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
typedef struct { SV4_8017B368 x, y; } Pair16_8017B368;         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801EF6EC;
    extern SV4_8017B368 D_801EF6F4;
    extern s16 D_801EF744;
    extern s16 D_801EF73C;
    extern u16 D_8018DE14;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801EF6EC;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801EF6F4;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_8018DE14)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_8018DE14)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801EF744) = loc0;
    (*(SV4_8017B368 *)&D_801EF73C) = loc1;
    D_801EFCC0 = 1;
    D_801EF6CC = 0;
}



INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017B490);

// @class: regalloc-order + T1 memcpy-builtin→call re-crack
// @stuck: 0 (iso). Register lever = $16 pin + in-place re-tie on the memcpy-branch src (keeps
// param_2 in $a1 until the branch, then $s0 for the loads). Block-moves are align-1 struct-assigns
// (u8[8]) so they lower via emit_block_move (movstrsi/move_by_pieces) with ZERO memcpy-symbol
// reference — TU-independent, so the sibling TU's `extern memcpy` (which disables the builtin and
// turned the old inlined block-move into a CALL) can no longer drift this.

typedef struct { u8 b[8]; } Blk8_8017B614;



s32 func_8017B614(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018DE14[];
    extern s16 D_801EF744;
    extern s16 D_801EF746;
    extern s16 D_801EF748;
    extern s16 D_801EF73C;
    extern s16 D_801EF73E;
    extern s16 D_801EF740;
    extern u8 D_8012694C;
    extern s32 D_80126998;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_8018DE14[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018DE14[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801EF744;
        s16 *p78C = &D_801EF73C;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801EF746;
            v798 = D_801EF748;
            v78C = *p78C;
            v78E = D_801EF73E;
            v790 = D_801EF740;
            __asm__ __volatile__("");
            D_801EFCC0 = 1;
            D_801EF6CC = 0x1E;
            D_80126990 = v794;
            D_80126994 = v796;
            D_80126998 = v798;
            D_80126984 = v78C;
            D_80126988 = v78E;
            D_8012698C = v790;
        }
        func_80129CF8();
    }
}




// @class: plumbing
// @stuck: none — MATCH

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8 D_8012694C;
extern s16 D_801EF6CC;
extern s16 D_801EF744;
extern s16 D_801EF746;
extern s16 D_801EF748;
extern s16 D_801EF73C;
extern s16 D_801EF73E;
extern s16 D_801EF740;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801EF6CC = 0;
    D_801EF744 = (s16) D_80114F30;
    D_801EF746 = (s16) D_80114F34;
    D_801EF748 = (s16) D_80114F38;
    D_801EF73C = (s16) D_80114F24;
    D_801EF73E = (s16) D_80114F28;
    D_801EF740 = (s16) D_80114F2C;
}




extern s32 D_801151D4;
extern s16 D_801EF75C;
extern s16 D_801EF75E;
extern s16 D_801EF760;
extern s16 D_801EF764;
extern s16 D_801EF766;
extern s16 D_801EF768;

void func_8017B824(void) {
    D_801EF75C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801EF75E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801EF760 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801EF764 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801EF766 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801EF768 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801EF75C;
extern s16 D_801EF75E;
extern s16 D_801EF760;
extern s16 D_801EF764;
extern s16 D_801EF766;
extern s16 D_801EF768;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801EF75C;
    D_80114F34 = D_801EF75E;
    D_80114F38 = D_801EF760;
    D_80114F24 = D_801EF764;
    D_80114F28 = D_801EF766;
    D_80114F2C = D_801EF768;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801EF744), src[8..15] -> (*(S8_8017B8E8 *)&D_801EF73C) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */

typedef struct { unsigned char b[8]; } S8_8017B8E8;


s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801EF744) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801EF73C) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801EF74C;
extern u16 D_801EF74E;
extern u16 D_801EF750;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801EF6CC;
extern short D_801EF754;
extern short D_801EF756;
extern short D_801EF758;
extern s16 D_801EF744;
extern s16 D_801EF746;
extern s16 D_801EF748;
extern s16 D_801EF73C;
extern s16 D_801EF73E;
extern s16 D_801EF740;

void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801EF74C);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801EF74E);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801EF750);
    (*(s16 *)&D_801EF754) = buf[0];
    (*(s16 *)&D_801EF756) = buf[1];
    (*(s16 *)&D_801EF758) = buf[2];
    D_801EF744 = D_80114F30 + buf[0];
    D_801EF6CC = 0;
    D_801EF746 = D_80114F34 + buf[1];
    D_801EF748 = D_80114F38 + buf[2];
    D_801EF73C = D_80114F24 + buf[0];
    D_801EF73E = D_80114F28 + buf[1];
    D_801EF740 = D_80114F2C + buf[2];
}



// @class: struct
// @stuck: none — MATCH (62 ins)

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);

/* short-only (align 2) struct -> the 8-byte struct copy emits lwl/lwr/swl/swr */

/* PSX MATRIX: 3x3 short rotation + pad + 3 long translation (offset 0x14) */

extern SV4 D_801EF6EC;
extern SV4 D_801EF6F4;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801EF6F4) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801EF6EC = svec;

    v0.a = -*(s16 *)(param_2 + 0xc);
    v0.b = *(u16 *)(param_2 + 8);
    v0.c = 0;
    v1.a = 0;
    v1.b = 0;
    v1.c = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))func_80049CAC)(&v0, &mtx);

    mtx.t[0] = (s32)svec.a;
    mtx.t[1] = (s32)svec.b;
    mtx.t[2] = (s32)svec.c;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    RotTransSV(&v1, &buf1, &buf2);
    D_801EF6F4 = buf1;
}


// @class: struct
// @stuck: none — MATCH (65 ins)
#include "common.h"

typedef struct { s16 a, b, c, d; } SV4_8017BB34;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8017BB34;



s32 func_8017BB34(s32 param_1, s32 param_2)
{
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801EF6F4)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801EF6EC) = svec;

    v0.a = -*(s16 *)(param_2 + 0xc);
    v0.b = *(u16 *)(param_2 + 8);
    v0.c = 0;
    v1.a = 0;
    v1.b = 0;
    v1.c = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))func_80049CAC)(&v0, &mtx);

    mtx.t[0] = (s32)svec.a;
    mtx.t[1] = (s32)svec.b;
    mtx.t[2] = (s32)svec.c;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    RotTransSV(&v1, &buf1, &buf2);
    (*(SV4_8017BB34*)&D_801EF6F4) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801EF714[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801EF714;
    do {
        if (*p != (void (*)(int))0) {
            (*p)(param_1);
        }
        i = i + 1;
        p = p + 1;
    } while (i < 10);
    return;
}




// @class: plumbing
// @stuck: none — MATCH (expected); short-typed global increment + signed compare, store-2 on overflow

extern void func_8017B0E4(int, int);
extern s16 D_801EF6CC;
extern s16 D_801EFCC0;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801EF6CC = D_801EF6CC + 1;
    if (D_801EF6CC >= 0x1F) {
        D_801EFCC0 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801EF6CC;
extern s16 D_801EFCC0;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801EF6CC = D_801EF6CC + 1;
    if (0x18 < D_801EF6CC) {
        func_8012A4BC();
        D_801EFCC0 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801EF6CC;
extern void (*D_801EF710)(void);
extern short D_801EF754;
extern short D_801EF756;
extern short D_801EF758;
extern s16 D_801EFCC0;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801EF6CC = D_801EF6CC + 1;
    if (D_801EF6CC >= 0x19) {
        if (D_801EF710 != 0) {
            (*D_801EF710)();
        } else {
            D_80114F30 = D_80114F30 + D_801EF754;
            D_80114F34 = D_80114F34 + D_801EF756;
            D_80114F38 = D_80114F38 + D_801EF758;
            D_80114F24 = D_80114F24 + D_801EF754;
            D_80114F28 = D_80114F28 + D_801EF756;
            D_80114F2C = D_80114F2C + D_801EF758;
            func_8012A4BC();
        }
        D_801EFCC0 = 0;
    }
}



extern void (*D_8018DEB4[])(void);

void func_8017BE60(void *a0) {
    D_8018DEB4[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_8017BE9C()  /* dedup: shared engine-core @0x8017BE9C (src/shared) */

DEFINE_func_8017BEA4()  /* dedup: shared engine-core @0x8017BEA4 (src/shared) */

DEFINE_func_8017BEAC()  /* dedup: shared engine-core @0x8017BEAC (src/shared) */

DEFINE_func_8017BEB4()  /* dedup: shared engine-core @0x8017BEB4 (src/shared) */


extern void (*D_8018DED8[])(void);

void func_8017BEBC(void *a0) {
    D_8018DED8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017BEF8);

DEFINE_func_8017C0BC()  /* dedup: shared engine-core @0x8017C0BC (src/shared) */


extern void (*D_8018DEE0[])(void);

void func_8017C150(void *a0) {
    D_8018DEE0[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_8018DECC;

void func_8017C18C(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_8018DECC, 0x18);
    if (r != 0) {
        *(s32 *)(a0 + 0x20) = r;
        *(u32 *)(r + 4) = *(u32 *)(r + 4) | 0x5C000140;
        func_8001CF30((void *)r);
        *(s16 *)(r + 0x10) = 0x400;
        *(s16 *)(r + 0x18) = 0x3000;
        *(s16 *)(r + 0x1A) = 0x3000;
        *(s16 *)(r + 0x28) = 0x248;
        *(s16 *)(r + 0x2A) = 0x180;
        *(s16 *)(a0 + 2) = *(s16 *)(a0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}


DEFINE_func_8017C230()  /* dedup: shared engine-core @0x8017C230 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017C294);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017C3C4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017C750);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017C9C8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017CB10);


extern void (*D_8018DFF8[])(void);

void func_8017CC90(void *a0) {
    D_8018DFF8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017CCCC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017CD18);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017CE0C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017CE8C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017CF40);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017CFAC);

extern void func_8012C218(void *a0);
    void func_8017D038(void) {
        ((void (*)(void))func_8012C218)();
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D058);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D0AC);


extern void (*D_8018E050[])(void);

void func_8017D0E8(void *a0) {
    D_8018E050[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D124);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D174);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D1D0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D254);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D3BC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D408);


extern void (*D_8018E064[])(void);

void func_8017D714(void *a0) {
    D_8018E064[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D750);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D790);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D800);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D88C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D960);


extern void (*D_8018E078[])(void);

void func_8017D9B4(void *a0) {
    D_8018E078[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017D9F0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017DAA4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017DB00);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017DC70);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017DD3C);


extern void (*D_8018E08C[])(void);

void func_8017DE98(void *a0) {
    D_8018E08C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017DED4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017DF34);


extern void (*D_8018E10C[])(void);

void func_8017EE14(void *a0) {
    D_8018E10C[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017EE50);


extern s32 func_800167F0(s32 a0);

s32 func_8017EE94(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_8018E114[])(void);

void func_8017EEB8(void *a0) {
    D_8018E114[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017EEF4);


extern void (*D_8018E11C[])(void);

void func_8017EF38(void *a0) {
    D_8018E11C[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017EF74);


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017EFB4(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017F030(void) {
        func_800D1EBC();
    }



extern void (*D_8018E128[])(void);

void func_8017F050(void *a0) {
    D_8018E128[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F08C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F0CC);

extern void func_800D1EBC(void);
    void func_8017F140(void) {
        func_800D1EBC();
    }



extern void (*D_8018E134[])(void);

void func_8017F160(void *a0) {
    D_8018E134[*(u8 *)((s32)a0 + 0x15)]();
}


s32 func_8017F19C(u8 *a0) {
        *(s32 *)(a0 + 0x28) = 0xA;
        a0[0x15] += 1;
        return 0;
    }



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017F1B8(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017F234(void) {
        func_800D1EBC();
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F254);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F27C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F2A4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F2CC);


extern void (*D_8018E1B4[])(void);

void func_8017F2F4(void *a0) {
    D_8018E1B4[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F330);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F3B0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F474);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F4AC);

extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_8018E17C;

void func_8017F59C(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018E17C, 0x1000000);
}



extern void (*D_8018E1C4[])(void);

void func_8017F5C4(void *a0) {
    D_8018E1C4[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F600);

void func_8017F63C(void) {
}

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F644);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F66C);


extern void (*D_8018E1CC[])(void);

void func_8017F72C(void *a0) {
    D_8018E1CC[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F768);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017F92C);

s32 func_8017FAF8(void) {
        return 0x18;
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017FB00);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017FB60);

void func_8017FC84(void) {
}


extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_8018E214;
    void func_8017FC8C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 3;
        func_80178CBC((int)arg0, (int)&D_8018E214);
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017FCB8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017FCFC);


extern void (*D_8018E310[])(void);

void func_8017FE3C(void *a0) {
    D_8018E310[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017FE78);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8017FF48);


extern s32 func_801805D4(void);
    void func_80180064(void) {
        func_801805D4();
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180084);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180270);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180304);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180398);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180410);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801804A8);

extern s16 func_80174764(void);
s32 func_80180530(void) {
    return ((s32 (*)(void))func_80174764)() == 1;
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180554);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180590);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801805D4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180610);


extern void (*D_8018E368[])(void);

void func_8018068C(void *a0) {
    D_8018E368[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801806C8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801807DC);

extern s32 func_8018096C(void);
    void func_8018094C(void) {
        func_8018096C();
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018096C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801809A8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180A10);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180AB8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180B00);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180C44);

extern void func_8012B260(u8 *a0);
extern void func_80180CCC(void *a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_80180C90(s32 arg0) {
    s32 var_v0;

    var_v0 = arg0;
    ((void (*)(s32 *))func_8012B260)((s32 *)var_v0);
    ((s32 (*)(s32))func_80180CCC)(var_v0);
    func_8012B178(var_v0, 0x20000);
}


void func_80180CCC(void *a0) {
        *(s32 *)((s32)a0 + 0x18) = 0;
        *(s32 *)((s32)a0 + 0x14) = 0;
        *(s32 *)((s32)a0 + 0x10) = 0;
        *(s32 *)((s32)a0 + 0x4c) = 0;
        *(s32 *)((s32)a0 + 0x44) = 0;
        *(s32 *)((s32)a0 + 0x48) = 0x1000;
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180CEC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180D8C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180EB0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180EF4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80180F8C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018104C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181090);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801810D4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181118);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801811D0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181250);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181294);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181594);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181604);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018183C);

extern void (*D_8018E52C[])(void);

void func_80181974(void *a0) {
    D_8018E52C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801819B0);

void func_80181A54(void) {
}


extern void (*D_8018E534[])(void);

void func_80181A5C(void *a0) {
    D_8018E534[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181A98);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181B0C);

extern void func_8012C098(void);
    void func_80181B48(s32 arg0) {
        s32 v0;
        if (*(s16 *)(arg0 + 0xfc) != *(s16 *)(*(s32 *)(arg0 + 0x64) + 0x36)) {
            ((void (*)(void))func_8012C098)();
        }
    }



extern void (*D_8018E54C[])(void);

void func_80181B80(void *a0) {
    D_8018E54C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181BBC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181C58);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181CF0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181D80);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181E5C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80181E98);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018209C);


extern void (*D_8018E5C4[])(void);

void func_801822A0(void *a0) {
    D_8018E5C4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801822DC);

void func_80182354(void) {
}


extern void (*D_8018E5DC[])(void);

void func_8018235C(void *a0) {
    D_8018E5DC[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern u32 D_8018E5CC;

void func_80182398(s32 arg0) {
    s32 v0 = ((s32 (*)(s32))func_8012C1B8)(arg0);
    *(s32*)((u8*)arg0 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(arg0);
    } else {
        func_8001C214(v0, 0);
        *(s16*)((u8*)arg0 + 0x2) = 1;
        *(s16*)((u8*)arg0 + 0x5C) = 0x20;
        *(s32*)((u8*)arg0 + 0x58) = (u32)&D_8018E5CC | 0x40000000;
        *(s16*)((u8*)(*(s32*)((u8*)arg0 + 0x20)) + 0x12) = *(u16*)((u8*)arg0 + 0xFC);
    }
}


void func_80182414(void) {
}


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_8018E5FC[])();

void func_8018241C(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_8018E5FC[*(u16 *)(param_1 + 2)]();
    }
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80182468);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80182558);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801825F4);

void func_80182670(void) {
}


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_8018E60C[])();

void func_80182678(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_8018E60C[*(u16 *)(param_1 + 2)]();
    }
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801826C4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80182744);

extern s32 func_8018287C(void);
    void func_801827A4(void) {
        func_8018287C();
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801827C4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80182844);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018287C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80182938);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801829F4);


extern void (*D_8018E780[])(void);

void func_80182A54(void *a0) {
    D_8018E780[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80182A90);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80182B44);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80182EB0);


// @class: struct
// @stuck: none — MATCH (array-of-fnptr %lo-fold + signed-halfword guard)

extern u16 D_801270C0;
extern void (*D_8018E90C[])();

void func_80182F58(int param_1)
{
    if (*(s16 *)&D_801270C0 != 3) {
        D_8018E90C[*(u16 *)(param_1 + 2)]();
    }
}


extern s32 func_8012AD50(void *a0);
    void func_80182FA4(s32 *param) {
        *(u16 *)((char *)param + 0x72) |= 0x1000;
        ((void (*)(void))func_8012AD50)();
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80182FD0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183168);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801831FC);


extern void (*D_8018E914[])(void);

void func_801832F4(void *a0) {
    D_8018E914[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183330);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018337C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801833FC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018347C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801835F4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183628);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018365C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183690);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801836A8);


extern void (*D_8018EE88[])(void);

void func_801836F0(void *a0) {
    D_8018EE88[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018372C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183790);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183800);


extern void (*D_8018EEE0[])(void);

void func_80183904(void *a0) {
    D_8018EEE0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183940);

extern int func_80029178(int arg);
int func_80183984(void) {
    return (func_80029178(232) & 0xFF) != 0;
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801839A8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183A3C);

extern void func_80029124(s32 arg0, s32 arg1);
    extern void func_801472F0(void *a0);
    void func_80183AD0(void) {
        func_80029124(0x96, 1);
        ((void (*)(s32))func_801472F0)(0x430);
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183AFC);

extern s32 func_8001AAA0(s32 arg);
    s32 func_80183B10(void) {
        return func_8001AAA0(0x2C) != 0;
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183B30);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183B9C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183C30);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183C6C);

extern s32 func_8012BEE8(s32);
    extern void func_8018372C(s32);
    void func_80183D30(s32 arg0) {
        if (func_8012BEE8(arg0)) {
            func_8018372C(arg0);
        }
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183D68);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183DFC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183E70);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80183FA8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184084);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801840F8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018413C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018416C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184208);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801842E0);


extern void (*D_801CC350[])(void);

void func_80184438(void *a0) {
    D_801CC350[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184474);

void func_80184510(void) {
}

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184518);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018457C);

void func_8018461C(void *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x5;
        *(s32 *)((s32)a0 + 0x1c) = 0x10;
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184630);


extern void (*D_801CC3AC[])(void);

void func_8018467C(void *a0) {
    D_801CC3AC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801846B8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184754);


extern void (*D_801CC3CC[])(void);

void func_80184878(void *a0) {
    D_801CC3CC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801848B4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018495C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184B18);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184BA4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184C28);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184C58);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184D28);

extern s32 func_8012BEE8(s32 arg);
    void func_80184D9C(void *a0) {
        if (func_8012BEE8((s32)a0)) {
            *(s16 *)((u8 *)a0 + 0x2) = 0x5;
        }
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184DD0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184E38);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80184F4C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018501C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185064);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018518C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185244);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801852D4);

extern void func_80185B5C(void);
    void func_80185300(void) {
        func_80185B5C();
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185320);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185338);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185364);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801853DC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185494);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185574);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801855CC);


void func_80185670(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 6;
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185680);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185768);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801857C4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018583C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018590C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801859C4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185AF0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185B5C);


extern s32 rand(void);
    void func_80185C68(s32 arg0) {
        if ((rand() & 1) != 0) {
            *(s16*)(arg0 + 0x2) = 0xA;
        } else {
            *(s16*)(arg0 + 0x2) = 0x3;
        }
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185CA4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185D10);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185EE4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80185F88);

extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80186100(void) {
        func_8002D4C8(0x6AA, 0);
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186124);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186168);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018626C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801862B8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801863B8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186500);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186530);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801866C8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186770);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186B08);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186B34);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186B7C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186BC4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186BF0);

extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern char D_801D61B0;

void func_80186C38(int param_1, int param_2) {
    ((int (*)(int, int *, int *, int))func_8012D5E4)(param_1, &D_801D61B0, &D_801D61B0 + 8, param_2);
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186C64);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80186FA8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187044);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187178);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187298);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801874E8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801876AC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187710);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187794);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801877C0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187814);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187840);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187868);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801878A8);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187940);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801879A4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187A24);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187A68);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187AB0);


extern void (*D_801E1D78[])(void);

void func_80187C28(void *a0) {
    D_801E1D78[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801E1D8C[])(void);

void func_80187C64(void *a0) {
    D_801E1D8C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern s32 D_801E1D64;
extern s32 D_801E1D70;
extern u8 D_800D3918[];
extern s32 D_80126D50;

void func_80187CA0(s32 param_1) {
    s32 s0 = param_1;
    s32 v;

    func_8012B14C(s0, (s32)&D_801E1D64);
    if (((s32 (*)(s32))func_8012CBF4)(s0) != 0) {
        func_80146A6C(6, (void *)s0, *(s16 *)(s0 + 0x6), *(s16 *)(s0 + 0xA),
                      *(s16 *)(s0 + 0xE), 0, 0);
        v = func_80132EF4(s0, 0x22);
        if (v != 0) {
            *(s16 *)(v + 0x34) = 0x2000;
        }
    } else {
        if (func_8012D5E4(s0, (s32)&D_801E1D70, (s32)&D_800D3918, 0x19) == 0 &&
            (*(s16 *)(s0 + 0x70) == 2 || D_80126D50 == 0) &&
            func_8012BEE8(s0) == 0) {
            return;
        }
    }
    func_8012C218((void *)s0);
}



// @class: schedule
// @stuck: none — MATCH (71 ins). Tail schedule: read out.c into an explicit temp BEFORE the 0x5a/1 const stores so gcc hoists its lhu early (load-delay filled by li 0x5a) and stores out.c last from a held reg; without the temp gcc instead deferred out.b's store. in/out are two separate SV3{s16 a,b,c} stack slots (sp+0x10, sp+0x18) for ((void (*)(int, void *, void *))func_8012F214)(a0,&in,&out). 0x34 compare reads u16 (lhu, not lh).

extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern int D_801E1D80;

void func_80187D80(int param_1)
{
    SV3 in;
    SV3 out;
    short c;

    if (*(unsigned short *)(param_1 + 0x34) == 0) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
            *(short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x12);
        ((void (*)(void))func_8012B2CC)();
        func_8012B23C(param_1);
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_801E1D80);
        in.a = 0;
        in.b = 0;
        in.c = 0x10;
        ((void (*)(int, void *, void *))func_8012F214)(param_1, &in, &out);
        *(short *)(param_1 + 6) = out.a;
        *(short *)(param_1 + 0xa) = out.b;
        c = out.c;
        *(int *)(param_1 + 0x1c) = 0x5a;
        *(short *)(param_1 + 0x34) = 1;
        *(short *)(param_1 + 0xe) = c;
    }
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) - 0x80;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 4;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 5;
    func_8012AD80(param_1);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(int))func_8012C218)(param_1);
    }
}



// @class: other
// @stuck: none — MATCH (expected); 16-bit sh stores via short* casts, s0=param_1 call-crossing

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

extern int D_801E2034;

void func_80187E9C(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801E2034);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0x34) = 0;
    }
}


extern void func_8012C098(void);
    void func_80187EF8(void) {
        func_8012C098();
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187F18);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80187F84);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018800C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188050);


void func_801880F4(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 6;
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188104);


// @class: plumbing
// @stuck: none — MATCH (18 ins): if((b&1) && p!=&sym) call(param,&sym); $a0 live, $a1=&sym fall out
extern void func_8012A828(s32 a0, void *a1);
extern void D_801E9CCC;

void func_801881B0(s32 arg0)
{
    if ((M2C_FIELD(arg0, u8 *, 0xC3) & 1) && (M2C_FIELD(arg0, void **, 0x90) != &D_801E9CCC)) {
        func_8012A828(arg0, &D_801E9CCC);
    }
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801881F8);


extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801EA154;

void func_80188240(s32 a0) {
    *(s16 *)(a0 + 0x2) = 2;
    func_8012A828(a0, &D_801EA154);
    *(s32 *)(a0 + 0x1C) = 0x14;
}



// @class: schedule
// @stuck: none — MATCH (44 ins). Two §3-T4 branch-polarity inversions: outer if(param_2>=iVar2) makes the func_80188330 else-block fall-through; inner if(param_3>=iVar2) return 0 makes the func_8012A828 body fall-through. No pins needed — natural $s1/$s0/$s2 alloc matched.
extern s32 func_8012BCCC(s32 a0);
extern void func_80188330(s32 param_1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801EA0AC;

s32 func_80188280(s32 param_1, s32 param_2, s32 param_3) {
    s32 iVar2;
    s16 sVar1;

    iVar2 = func_8012BCCC(param_1);
    if (param_2 >= iVar2) {
        func_80188330(param_1);
        return 1;
    }
    sVar1 = *(s16 *)(param_1 + 0xdc) + 1;
    *(s16 *)(param_1 + 0xdc) = sVar1;
    if (sVar1 < 0x79) {
        return 0;
    }
    if (param_3 >= iVar2) {
        return 0;
    }
    *(s16 *)(param_1 + 2) = 1;
    func_8012A828(param_1, &D_801EA0AC);
    return 1;
}



// @class: plumbing
// @stuck: none — MATCH (straightforward; callee sigs canonical from overlay)
extern void func_8012A828(s32 a0, void *a1);
extern void func_80142414(s32 a0, s16 a1);
extern u8 D_801E9E6C;

void func_80188330(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    func_8012A828(param_1, &D_801E9E6C);
    *(s32 *)(param_1 + 0x1c) = 0x1e;
    if (*(s16 *)(param_1 + 0xfc) == 0) {
        *(s16 *)(param_1 + 0xfc) = 1;
        ((void (*)(s32, s32))func_80142414)(param_1, -0x96);
    }
}


void func_8018838C(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        *(int *)((char *)a0 + 0x1c) = 0x14;
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801883A0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801883FC);


extern void (*D_801E2150[])(void);

void func_80188480(void *a0) {
    D_801E2150[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801E2198[])(void);

void func_801884BC(void *a0) {
    D_801E2198[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (clean if/else, sh into delay slot of func_8001CA88 call)

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern int func_8001CA88(int, void *);
extern void func_80143994(s32 a0, s32 a1);
extern int D_801E2158;

void func_801884F8(int param_1)
{
    int iVar1;

    iVar1 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        *(short *)(param_1 + 2) = 1;
        func_8001CA88(*(int *)(param_1 + 0x20), &D_801E2158);
        func_80143994(param_1, 0x1000);
    }
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018855C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801885B4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188620);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018875C);

extern s32 func_8012BEE8(s32 arg);
    extern void func_801883A0(s32 *a0);
    void func_801887C8(s32 *a0) {
        if (func_8012BEE8((s32)a0)) {
            func_801883A0(a0);
        }
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188800);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188864);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801888BC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188974);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801889E4);


extern void (*D_801EAE7C[])(void);

void func_80188B74(void *a0) {
    D_801EAE7C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188BB0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188C84);

void func_80188CAC(void) {
}

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188CB4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188E00);

extern void func_8012C218(void *a0);
    s32 func_80188F20(void * arg0)
    {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32 *))func_8012C218)(*(s32 **)((char *)arg0 + 0xcc));
    }


void func_80188F4C(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_80188F5C(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80188F6C);


extern s32 D_80126B58;
extern void func_8014ADA8(s32 a0, s32 a1);

void func_80188FAC(void * arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((s32)arg0 + 0xdc);
    ((void (*)(s32 *, s32))func_8014ADA8)((s32 *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
}


extern s16 func_80174764(void);
s32 func_80188FE0(void) {
    return ((s32 (*)(void))func_80174764)() == 1;
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80189004);


extern void (*D_801EAEA4[])(void);

void func_80189068(void *a0) {
    D_801EAEA4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801890A4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018912C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801891EC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018925C);


extern s32 D_801EFBC0;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_80189354(s32 a0, s32 a1) {
    D_801EFBC0 = a1;
    return func_8012C588(0x85, a0);
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80189384);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801895C8);


extern void (*D_801EB5C0[])(void);

void func_80189868(void *a0) {
    D_801EB5C0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_801898A4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80189908);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80189A68);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80189C4C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80189D08);


extern void (*D_801ECD34[])(void);

void func_80189DB4(void *a0) {
    D_801ECD34[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80189DF0);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_80189EEC);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018A17C);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018A310);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018A368);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018A3E4);

INCLUDE_ASM("asm/ov_SC02_017/nonmatchings/ov_SC02_017_jr_80178D40", func_8018A428);


