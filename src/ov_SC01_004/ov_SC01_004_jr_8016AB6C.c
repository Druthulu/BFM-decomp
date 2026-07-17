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
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80181754;
extern u8 D_801816C4;
extern u8 D_801816A0;
extern u8 D_8018167C;
extern u8 D_80181730;
extern u8 D_8018170C;
extern u8 D_801816E8;
extern u8 D_80181658;
extern void func_80145934(void);
extern u8 D_801817E4;
extern u8 D_801817C0;
extern u8 D_8018179C;
extern u8 D_80181778;
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
extern unsigned char D_80180BDC[];
extern unsigned char D_80180C0C[];
extern unsigned char D_80180C5C[];
extern unsigned char D_80180C8C[];
extern unsigned char D_80180CBC[];
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
extern void (*D_80180D0C[])(void *);
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
extern s32 D_80180DD4[];
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
extern u8 D_80180E5C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80180E64;
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
extern int D_8018EF68;
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
extern s32 D_8018EF6C;
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
extern s32 D_80180E94;
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
extern void (*D_80180F3C[])(void);
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
extern void (*D_80180F60[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80180F50;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80180F74[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80180F80[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80180F90[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80180FA8[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80180F98;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80180FBC[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80180FD8[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80180FC8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80180FEC[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80181000[])(void);
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
extern s32 D_80181014;
extern void (*D_8018103C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018101C;
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
extern int (*D_80181088[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018108C[])(void);
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
extern unsigned short D_801814F0[];
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
extern void (*D_80181500[])(void);
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
extern int D_8018EFA0;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80181528[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80181508;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80181518;
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
extern void (*D_80181568[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80181570[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018153C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018157C[])(void);
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
extern u8 D_8018154C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_8018EFA8;
extern s32 D_8018EFB4;
extern s32 D_8018EFB8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801815B8[])(s32 *);
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
extern s32 D_8018158C[];
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
extern s32 D_8018EFB0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80181808[])(void);
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
extern char D_80181628[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_801818AC[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80181A00[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018181C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80181A08[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018182C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018184C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80181A10[])(void);
extern void func_8015ADB0(s32);
extern void func_8015AD78(s32 a0);
extern void func_8015ADB0(s32 arg0);
extern s32 func_80161A60(s32 a0);
extern s32 func_801619A4(s32 *a0);
extern s32 func_80149C08(s32 a0);
extern s32 func_8015B6F4(s32 a0);
extern s32 func_8015B7B4(s32 a0);
extern void func_8015B8F8(s32 *a0);
extern void func_800CCCC0(s32 a0);
extern s32 func_8015B858(u8 *a0);
extern s32 func_800CF8B4(void);
extern void func_80147A84(s32 a0);
extern s32 func_80172644(u8 *a0);
extern void func_800CCB78(s32 a0);
extern s32 func_80161488(void *a0);
extern void func_8015CC40(s32 *a0);
extern void func_8015CF8C(s32 *a0);
extern s32 func_8015AE2C();
extern s32 D_800D4A9C;
extern int func_8015B6F4(int param_1);
extern u8 D_800D4F8C[];
extern u8 D_800D4BE0[];
extern s32 func_8014A51C(void);
extern s32 D_800D4B48;
extern void func_8015BD8C(s32 *a0);
extern s32 func_8015BE94();
extern void func_8015BE38(struct Obj *a0);
extern s32 func_8015BE74(void);
extern void func_80161124(void *a0);
extern s32 func_8015BE94(s32 *a0);
extern s32 func_8015BEC4(void);
extern s32 func_8015B950(void);
extern s32 func_8015BEE4(void);
extern void func_8015BF04(s32 *a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015BFF4(void *a0);
extern void func_8015BF7C(s32 *a0);
extern void func_8015C030(s32 *a0, s32 a1);
extern void func_8015BFB0(s32 *a0, s32 a1);
extern void (*D_80181A38[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80181A44[])(void);
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
extern s32 func_8015CCD0();
extern s32 func_8015CCB0(void);
extern s32 func_801725E0(u8 *a0);
extern s32 func_8015CCD0(s32 param_1);
extern s32 func_8015CD20(s32 arg0);
extern void func_8015CF24(s32 a0);
extern void func_8015D01C();
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0(s32 *a0);
extern void func_8015CFFC(void);
extern void func_8015D01C(int param_1);
extern void (*D_801818B8[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80181AE8;
extern void func_8015D380(s32 a0);
extern unsigned char D_80180BCC[];
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
extern unsigned char D_80181AFC[];
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
extern s8 D_80181B38[];
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
extern u16 D_80181B80;
extern u16 D_80181B82;
extern u16 D_80181B84;
extern s32 D_80181B88;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80181B90;
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
extern int D_8018189C;
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
extern unsigned int D_80181C14[];
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
extern void (*D_80181CC4[])(void);
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
extern void func_8016130C(void *a0, s32 a1);
extern void func_80161240(void *a0);
extern void func_80161374(void *a0, s32 a1);
extern void func_80161278(void *a0);
extern s32 func_801612B8(void * a0, s32 a1);
extern void func_8016163C(void *a0, s32 a1);
extern void func_80161774(void *a0, s32 a1);
extern s32 func_8016197C(s32 a0, s32 a1);
extern void func_80161888(void *a0, s32 a1);
extern void func_801614E4(void *a0);
extern void func_8016191C(void *a0, s32 a1);
extern void func_8016151C(void *a0);
extern void func_80161554(void *a0);
extern s32 func_801615C4(void * arg0, s32 arg1);
extern s32 func_80161A00(s32 a0);
extern s32 func_80161A30(s32 a0);
extern int func_801497A8(void);
extern int func_80161BE0(void *param_1);
extern u16 D_80181CF4[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80181D58;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_8018EFC0[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80181D7C[])(void);
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
extern int D_8018F018[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80181DC4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80181DB4;
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
extern char D_8018E30C[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80181DCC[])(void);
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
extern void (*D_80181E20[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80181DE8;
extern s16 D_80181E1C;
extern s16 D_80181E1A;
extern s16 D_80181E18;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80181E2C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_8018F078;
extern u8 D_8018F079;
extern u8 D_8018F07A;
extern u8 D_8018F07B;
extern u8 D_8018F07C;
extern u8 D_8018F07D;
extern u8 D_8018F07E;
extern u8 D_8018F07F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80181E3C[])(void);
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
extern s32 D_8018F0B8;
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
extern void (*D_80181E80[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80181EFC[];
extern s32 D_80181F1C[];
extern u8 D_80181F98[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80181FB8[];
extern u8 D_80181FD8[];
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
extern void (*D_80182074[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801820F0[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_8018E31C;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801820FC[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80182104[])(void);
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
extern void (*D_801821CC[])(void);
extern void func_80166618(void *a0);
extern void (*D_801821DC[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801821EC[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801821F8[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80182158[];
extern u8   D_8018216C[];
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
extern Blk20 D_800AE620;
extern s32  RotMatrixX(s32 a0, void *a1);
extern void func_80168664(void *arg0);
extern void (*D_80182210[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80182218[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80182220[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80182228[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80182230[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80182238[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80182240[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801822F4[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801822FC[])(void);
extern void func_80169F00(void *a0);
extern char D_801822AC[];
extern char D_8018226C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80182334[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80182340[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern s32 func_80016A5C();
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80182388[])(void);
extern void func_8016AB30(void *a0);
/* ==== end §8b carried decl layer ==== */


/* func_8016AB6C (ov_SC01_077 jr family, 188 ins, jtbl_801D8BC8) — Phase 26 crack
 * PIN-FREE.  Status: **MATCH (188 ins)**, jtbl VERIFIED exact.
 *
 * jtbl_801D8BC8 = 8 entries, bound `sltiu $v0,$v1,8`, default -> after-switch join.
 *   case 0->+0x88  1->+0xA8  2->+0x110  3->+0x130  4->+0x110  5->+0xA8  6->+0x178  7->+0x178
 * My .rodata relocs (8x R_MIPS_32 vs .text) are byte-identical to that:
 *   88 a8 110 130 110 a8 178 178   (objdump -r/-s -j .rodata .run/match/func_8016AB6C/t.o)
 *
 * ============================================================================
 * LEVER 9 — THE CALL-SINK (the last 2 ins; NEW, generalizable).  See cookbook §48-B.
 * ============================================================================
 * FINAL RESIDUAL was 2 ins (idx 141/143): both present and byte-correct, only transposed
 * around `jal func_8001CE28`:
 *     mine  : addu $a1,$s0,$zero ; jal ; [delay] addu $a0,$s2,$zero
 *     target: addu $a0,$s2,$zero ; jal ; [delay] addu $a1,$s0,$zero
 *
 * It was NOT a scheduling residual (sched1 already emitted a0-then-a1, per calls.c:1878
 * which loads arg regs in ASCENDING arg order).  It was a REGALLOC residual:
 *
 *   The old shape `f(A,LIT); p = LIT;` created TWO pseudos: a block-local arg pseudo
 *   (reg145/150, holding the symbol) and a GLOBAL allocno `p` (reg79) fed by a copy at the
 *   end of each arm.  greg dump said:  `;; 79 preferences: 5 16`.
 *     - $5  copy-pref  <- the join's arg move  (set (reg:SI 5 a1) (reg 79))
 *     - $16 copy-pref  <- the arms' copies     (set (reg 79) (reg145))  ... because
 *       set_preference (global.c:1535) applies reg_renumber[], so a LOCALLY-allocated
 *       pseudo counts as its hard reg.
 *   find_reg's copy-preference override (global.c:~1000) scans hard regs `for (i = 0; i <
 *   FIRST_PSEUDO_REGISTER; i++)` — plain ASCENDING regno, NOT reg_alloc_order.  So $5 beats
 *   $16, deterministically.  The ONLY way $16 wins is if $5 is already in `used` when that
 *   scan runs, and the only reachable way to do that is
 *       allocno_calls_crossed[p] > 0  ->  find_reg sets used1 = call_used_reg_set (global.c:906)
 *       -> AND_COMPL(hard_reg_copy_preferences, used) strips $5 -> $16 is all that's left.
 *   reg79 crossed NO call (def after func_80024054, last use before func_8001CE28), so $5 won.
 *   p in $a1 => the arms' copies became `move $5,$16`, cross_jump merged them to the top of
 *   the join (ahead of the a0 move), and reorg then slotted the a0 move.
 *
 * THE FIX — SINK THE CALL INTO THE ARMS (byte-proven, close=2 -> MATCH):
 *     BEFORE                                     AFTER
 *     if (c) { s3 = f(A1,P1)+3; p = P1; }        if (c) { s3 = f(A1,P1)+3; g(obj,P1); }

 *     else   { s3 = f(A2,P2)+9; p = P2; }        else   { s3 = f(A2,P2)+9; g(obj,P2); }
 *     g(obj, p);                                 // no join copy, no `p` at all
 *   Duplicating the call kills the cross-block pseudo `p` entirely.  The pointer is now a
 *   BLOCK-LOCAL pseudo per arm (lreg: "Register 144 used 3 times across 12 insns in block 13;
 *   crosses 1 call; pointer") -> LOCAL-alloc, crosses a call -> $s0, exactly as before, so the
 *   load-bearing "$16 occupant" that pushes arg0 off $s0 onto $s1 (lever 3) is PRESERVED.
 *   greg goes from "9 regs to allocate: ... 79 ..." to "8 regs to allocate:" (79 gone), and
 *   dispositions are unchanged: arg0=$s1, obj=$s2, var_s3=$s3, var_s0=$s0.
 *   The duplicated `[addu $a0,$s2][addu $a1,$s0][jal g]` tail is IDENTICAL in both arms after
 *   reload (same hard regs!), so jump2's cross_jump re-merges it into a single join block —
 *   ZERO extra bytes — and dbr then fills the jal slot with the nearest insn above it, which
 *   is now the a1 move.  Target shape, exactly.
 *
 * GENERAL RULE: when a value is defined in both arms of an if/else and consumed only by a
 * call in the join, gcc's join-copy makes it a global allocno whose ascending-scan copy-pref
 * hands it the ARG register.  If the target instead keeps it in a callee-saved reg, DUPLICATE
 * THE CALL INTO BOTH ARMS — cross_jump gives the bytes back for free, and the value demotes to
 * a call-crossing block-local, which local-alloc parks in $s0.  (Inverse of §48-A1: A1 sinks an
 * INIT to shorten a live range; this sinks the CONSUMER to delete the allocno outright.)
 *
 * LEVERS PROVEN HERE (see the report / cookbook):
 *  1. LOOP ROTATION (§46 L1, exact trigger): stmt.c:2255 expand_end_loop scans forward from the
 *     loop start label and stops at the FIRST CODE_LABEL, but sets last_test_insn on any
 *     unconditional `jump end_label` — which is exactly what `break` emits.  So `break` out of
 *     the first test rotates the loop (peels the test into a preheader).  `goto lout;` jumps to a
 *     USER label, not end_label, so last_test_insn stays 0 and the loop is NOT rotated.
 *     (`do{}while()` alone does NOT help: expand_exit_loop_if_false ends with a CODE_LABEL, so
 *     expand_end_loop's "already ends in a bare condjump" guard never fires.)
 *     Bonus: the unrotated loop is what keeps the s16 re-sign-extension INSIDE the loop
 *     (sll16/sra16 for the AND, and `sra 20` reusing that same `sll 16` for the >>4).
 *  2. `var_v1 = -0x1000;` AFTER the call, not before -> it no longer crosses the call -> $v1
 *     instead of a callee-saved reg.
 *  3. THE $s0/$s1 DIAL (new): `f(A,B); p = B;`  (literal args, then assign p from the SAME
 *     literal AFTER the call) makes cse rewrite `p = B` as a COPY of the call's arg pseudo.
 *     That arg pseudo is then live across the call yet stays BLOCK-LOCAL -> local_alloc gives it
 *     $s0 -> every global allocno live there now conflicts with hard reg $16 -> the big pointer
 *     (arg0) is pushed off $s0 onto $s1 and the whole allocation flips.  Writing `p = B; f(A,p);`
 *     instead merges them into ONE global allocno, no local, and arg0 takes $s0.  (99 -> 54.)
 *  4. §46 L2 refinement: a SAME-mode copy always dies (cse canon_reg/qty_first_reg).  A
 *     DIFFERENT-mode copy `(set (reg:QI x) (subreg:QI (reg:SI y)))` is not a plain reg-reg copy,
 *     so cse cannot merge the qtys and the copy insn SURVIVES.  That is how `var_c2 = var_s0;`
 *     materialises the target's `addu $v0,$s0,$zero`.  (187 -> 188 ins.)
 *  5. ANTI-DEP PINS A COPY EARLY: sched deterministically SINKS a copy to just before its
 *     consumers.  Reusing the SAME local (var_s0) as the if/else scratch, copying it out, then
 *     redefining var_s0 creates a WAR dep that pins the copy ahead of the redefinition — which
 *     also removes the live-range overlap so both share $s0.  (54 -> 22.)
 *  6. `t = x+1; x = t+1;` is folded by cse to `x = x+2`.  `t = x+1; x = t; x++;` keeps
 *     `addiu t,x,1 ; addiu x,t,1`.  (22 -> 21.)
 *  7. STORE-SINK: to get "compute chain A first, store A last", put A's store FIRST in the
 *     source — the backward list scheduler sinks a store (no dependents) but keeps the compute
 *     order.  (21 -> 8.)
 *  8. DELAY SLOT = source order: reorg takes the closest eligible insn before the jal, and the
 *     backward scheduler puts the HIGHEST-LUID (latest in source) of the tied independents
 *     nearest the call.  `var_s0 = 3;` written AFTER the call statement (sched still hoists it
 *     above the call — pseudos may cross calls at sched1) puts `addiu $s0,$zero,3` in the delay
 *     slot instead of the a1=0 arg move.  (8 -> 2.)
 */
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

typedef struct SVec_8016AB6C {
    s16 vx, vy, vz, pad;
} SVec_8016AB6C;



s32 func_8016AB6C(s32 arg0) {
    extern s32 func_801783D0(s32 a0, s32 a1);
    extern s32 func_80024054(u8 *a0, u8 *a1);
    extern void func_8001CE28(Obj_8016AB6C *a0, u8 *a1);
    extern u8 D_80182348[];
    extern u8 D_80182358[];
    extern u8 D_8018F388[];
    extern u8 D_8018F3B0[];

    SVec_8016AB6C sp10;
    SVec_8016AB6C sp18;
    s16 var_s0;
    s16 var_v1;
    s16 var_s3;
    s16 tmp;
    s32 temp_v0;
    u32 r;
    u8 var_c2;
    Obj_8016AB6C *obj;

    temp_v0 = func_801783D0(((Ent_8016AB6C *)arg0)->unk30, 0);
    var_s0 = 3;
    var_v1 = -0x1000;
    ((Ent_8016AB6C *)arg0)->unk30 = temp_v0;
    do {
        if (temp_v0 & var_v1) {
            goto lout;
        }
        var_s0--;
        var_v1 >>= 4;
    } while (var_s0 >= 0);
lout:
    switch (((Ent_8016AB6C *)arg0)->unk2C) {
    case 0:
        ((Ent_8016AB6C *)arg0)->unk26 = 1;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x60;
        ((Ent_8016AB6C *)arg0)->unkA -= 0x20;
        break;
    case 1:
    case 5:
        ((Ent_8016AB6C *)arg0)->unk14 = 0xFFF60000;
        r = ((u32(*)())rand)();
        tmp = var_s0 + 1;
        var_s0 = tmp;
        ((Ent_8016AB6C *)arg0)->unk10 = (r & 0xF) - 8 << 0xF;
        ((Ent_8016AB6C *)arg0)->unk18 = ((r >> 4) & 0xF) - 8 << 0xF;
        ((Ent_8016AB6C *)arg0)->unk26 = 4;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x80;
        ((Ent_8016AB6C *)arg0)->unk30 |= 0xA << (tmp * 4);
        break;
    case 2:
    case 4:
        ((Ent_8016AB6C *)arg0)->unk26 = 4;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x80;
        ((Ent_8016AB6C *)arg0)->unkA -= 0x18;
        break;
    case 3:
        tmp = var_s0 + 1;
        var_s0 = tmp;
        var_s0++;
        ((Ent_8016AB6C *)arg0)->unk26 = 4;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x80;
        ((Ent_8016AB6C *)arg0)->unkA -= 0x18;
        ((Ent_8016AB6C *)arg0)->unk30 = (((Ent_8016AB6C *)arg0)->unk30 | (0xF << (tmp * 4))) * 0x10;
        break;
    case 6:
    case 7:
        obj = ((Obj_8016AB6C *(*)(s32))func_801465C0)(temp_v0);
        if (obj == 0) {
            ((void(*)(Ent_8016AB6C *))func_80146C3C)(((Ent_8016AB6C *)arg0));
            return;
        }
        sp10.vx = ((Ent_8016AB6C *)arg0)->unk6;
        sp10.vy = ((Ent_8016AB6C *)arg0)->unkA - 0x18;
        sp10.vz = ((Ent_8016AB6C *)arg0)->unkE;
        ((void(*)(SVec_8016AB6C *, SVec_8016AB6C *, s32))func_800D20C0)(&sp10, &sp18, 6);
        ((Ent_8016AB6C *)arg0)->unk6 = sp10.vx;
        ((Ent_8016AB6C *)arg0)->unkA = sp10.vy;
        ((Ent_8016AB6C *)arg0)->unkE = sp10.vz;
        if (((Ent_8016AB6C *)arg0)->unk2C == 6) {
            var_s3 = func_80024054(D_80182348, D_8018F388) + 3;
            func_8001CE28(obj, D_8018F388);
        } else {
            var_s3 = func_80024054(D_80182358, D_8018F3B0) + 9;
            func_8001CE28(obj, D_8018F3B0);
        }
        obj->unkE = var_s3;
        obj->unk4 |= 0x04000000;
        if (((Ent_8016AB6C *)arg0)->unk2C == 6) {
            obj->unk27 = 0xB5;
            var_s0 = 0x70;
        } else {
            obj->unk27 = 0xAE;
            var_s0 = 0xB0;
        }
        var_c2 = var_s0;
        var_s0 = var_s3 >> 2;
        obj->unk2E = -8;
        obj->unk30 = 0;
        obj->unk26 = var_c2;
        obj->unk25 = var_c2;
        obj->unk24 = var_c2;
        ((Ent_8016AB6C *)arg0)->unk20 = obj;
        break;
    }
    ((Ent_8016AB6C *)arg0)->unk2A = 4 - (var_s0 * 4);
    ((Ent_8016AB6C *)arg0)->unk28 = var_s0;
    ((Ent_8016AB6C *)arg0)->unk1C = 0xB;
    ((Ent_8016AB6C *)arg0)->unk2++;
}


INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016AE5C);

DEFINE_func_8016AFB0()  /* dedup: shared engine-core @0x8016AFB0 (src/shared) */

DEFINE_func_8016B114()  /* dedup: shared engine-core @0x8016B114 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016B234);

DEFINE_func_8016B3F4()  /* dedup: shared engine-core @0x8016B3F4 (src/shared) */

DEFINE_func_8016B428()  /* dedup: shared engine-core @0x8016B428 (src/shared) */

DEFINE_func_8016B448()  /* dedup: shared engine-core @0x8016B448 (src/shared) */


extern void (*D_80182404[])(void);

void func_8016B4BC(void *a0) {
    D_80182404[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @stuck: none — MATCH

extern void func_80015978(s32 a0, s32 *a1);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B984(void *a0);
extern void func_8016B91C(int);
extern int D_8018F3D8;

void func_8016B4F8(int param_1)
{
    int iVar1;
    int uVar2;
    volatile int buf[2];

    ((void (*)(int, void *))func_80015978)(param_1 + 4, &D_8018F3D8);
    if (func_8016B9F8(param_1) == 0) {
        *(int *)(param_1 + 0x18) = 0;
        *(int *)(param_1 + 0x14) = 0;
        *(int *)(param_1 + 0x10) = 0;
        iVar1 = func_8016B834(param_1, 0);
        *(int *)(param_1 + 0x10) = iVar1;
        if (iVar1 != 0) {
            iVar1 = func_8016B834(param_1, 1);
            *(int *)(param_1 + 0x14) = iVar1;
            if (iVar1 != 0) {
                iVar1 = func_8016B834(param_1, 2);
                *(int *)(param_1 + 0x18) = iVar1;
                if (iVar1 != 0) goto success;
            }
        }
    }
    ((void (*)(int))func_8016B984)(param_1);
    return;
success:
    func_8016B91C(param_1);
    uVar2 = *(int *)(param_1 + 0x2c);
    if (uVar2 == 0) {
        uVar2 = 0xf0;
    } else {
        uVar2 = 0x2d0;
    }
    *(int *)(param_1 + 0x1c) = uVar2;
    uVar2 = *(unsigned short *)(param_1 + 2);
    uVar2 = uVar2 + 1;
    *(unsigned short *)(param_1 + 2) = uVar2;
}



// @class: schedule
// @stuck: none — MATCH


extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B984(void *a0);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);

extern s16 D_801823F8[];

void func_8016B5C0(s32 param_1) {
    s32 iVar4;
    s32 iVar2;
    s32 iVar5;
    s16 sVar1;
    s16 *psVar5;
    s32 i;

    iVar4 = *(s32 *)(param_1 + 0x18);
    if (((s32 (*)(void))func_8016B9F8)() != 0) {
        goto L984;
    }
    sVar1 = *(s16 *)(iVar4 + 0x1a) + 0x200;
    *(s16 *)(iVar4 + 0x1a) = sVar1;
    *(s16 *)(iVar4 + 0x18) = sVar1;
    if (*(s32 *)(param_1 + 0x2c) == 0) {
        iVar2 = *(s32 *)(param_1 + 0x1c);
    } else {
        iVar2 = *(s32 *)(param_1 + 0x1c) / 3;
    }
    iVar5 = *(s32 *)(param_1 + 0x1c) + -0x20;
    *(s32 *)(param_1 + 0x1c) = iVar5;
    if (iVar5 >= 0) {
        goto LOOP;
    }
L984:
    ((void (*)(s32))func_8016B984)(param_1);
    return;
LOOP:
    i = 0;
    psVar5 = D_801823F8;
    do {
        func_8016B6BC(param_1, iVar2, (s32)*psVar5, (s32)(s16)i);
        psVar5 = psVar5 + 1;
        i = i + 1;
    } while (i < 6);
    func_8016B91C(param_1);
    return;
}


INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016B6BC);


// @class: schedule
// @stuck: none — MATCH (statement order: compute puVar2 base before puVar3 table lookup so param*0x40+base schedule into prologue, leaving the 0x2c load-delay nop)
extern void func_801465C0(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);

extern int *D_8018243C[];
extern unsigned short D_80182444[];
extern unsigned short D_8018244C[];
extern unsigned char D_8018F3E0[];

int func_8016B834(int param_1, int param_2) {
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_8018F3E0 + param_2 * 0x40);
    puVar3 = D_8018243C[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_80182444[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_8018244C[param_2];
    }
    return iVar1;
}


DEFINE_func_8016B91C()  /* dedup: shared engine-core @0x8016B91C (src/shared) */

DEFINE_func_8016B964()  /* dedup: shared engine-core @0x8016B964 (src/shared) */

DEFINE_func_8016B984()  /* dedup: shared engine-core @0x8016B984 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (result is func_8012EFB8's return saved in $s0 across the func_80015954 call; the save-move fills the 2nd call's delay slot. func_80015954's return is discarded.)


extern s32 D_8018F3D8;
extern void func_8012EFB8(s32 a0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016B9F8(s32 param_1)
{
    s32 buf[2];
    u32 v;

    v = ((u32 (*)(s32 *, s32 *))func_8012EFB8)(&D_8018F3D8, buf);
    ((void (*)(s32 *, s32 *))func_80015954)(buf, (s32 *)(param_1 + 4));
    return (v & 0xffffefff) != 0;
}


DEFINE_func_8016BA48()  /* dedup: shared engine-core @0x8016BA48 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016BA68);

DEFINE_func_8016BADC()  /* dedup: shared engine-core @0x8016BADC (src/shared) */


extern void (*D_80182454[])(void);

void func_8016BBA4(void *a0) {
    D_80182454[*(u16 *)((s32)a0 + 0x2)]();
}


// @class: plumbing
// @stuck: none — MATCH (56 ins, match_one relocation-masked)




s32 func_8016BBE0(s32 param_1) {
    extern void func_8016BF34(void *a0);
    extern void func_8016BF50(s32);
    extern void func_8001CF00(s32);
    extern M2C_UNK D_8018F514;
    extern u8 D_8018F515;
    extern u8 D_8018F516;
    extern M2C_UNK D_8018F518;
    extern u8 D_8018F519;
    extern u8 D_8018F51A;

    int iVar1;
    int temp;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    *(int *)(((int)param_1) + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32))func_8016BF34)(((int)param_1));
        func_8016BF50(((int)param_1));
        func_8001CF00(iVar1);
        *(s16 *)(iVar1 + 0x10) = 0;
        temp = *(int *)(((int)param_1) + 0x2c);
        *(s16 *)(iVar1 + 0x14) = 0;
        *(s16 *)(iVar1 + 0x1a) = 0;
        *(s16 *)(iVar1 + 0x18) = 0;
        *(s16 *)(iVar1 + 0x12) = temp * 0x555;
        *(s16 *)(((int)param_1) + 0x10) = 0;
        *(s16 *)(((int)param_1) + 0x14) = 0;
        (*(u8 *)&D_8018F514) = 0x20;
        D_8018F515 = 0x20;
        D_8018F516 = 0;
        (*(u8 *)&D_8018F518) = 0xc0;
        D_8018F519 = 0xc0;
        D_8018F51A = 0;
        *(u16 *)(((int)param_1) + 2) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)(((int)param_1));
    }
}



extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_8018F514;
extern M2C_UNK D_8018F518;

void func_8016BCC0(void *arg0) {
    u16 temp_a2;
    u16 temp_v0;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x20);
    func_8016BF50();
    temp_a2 = M2C_FIELD(arg0, u16 *, 0x10) + 0x60;
    M2C_FIELD(arg0, u16 *, 0x10) = temp_a2;
    temp_v0 = M2C_FIELD(temp_s0, u16 *, 0x1A) + temp_a2;
    M2C_FIELD(temp_s0, u16 *, 0x1A) = temp_v0;
    M2C_FIELD(temp_s0, u16 *, 0x18) = temp_v0;
    M2C_FIELD(temp_s0, u16 *, 0x12) = (u16) ((M2C_FIELD(temp_s0, u16 *, 0x12) + 0x71) & 0xFFF);
    func_8016BFA8(arg0, &D_8018F514, &D_8018F518, temp_s0 + 0x18);
    if ((s16) M2C_FIELD(temp_s0, u16 *, 0x1A) >= 0x1001) {
        M2C_FIELD(temp_s0, u16 *, 0x18) = 0x1000U;
        M2C_FIELD(temp_s0, u16 *, 0x1A) = 0x1000U;
        func_80146E90(arg0, M2C_FIELD(arg0, s32 *, 0x30));
        M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) + 1);
    }
}


// @class: struct
// @stuck: none — MATCH (74 ins, relocation-masked)




s32 func_8016BD78(s32 param_1)
{
    extern void func_8016BF50(void);
    extern u8 D_8018F515;
    extern u8 D_8018F516;
    extern u8 D_8018F519;
    extern u8 D_8018F51A;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    func_8016BF50();

    p1 = &(*(u8 *)&D_8018F514);
    if (*p1 != 0) *p1 -= 4;
    if (D_8018F515 != 0) D_8018F515 -= 4;
    if (D_8018F516 != 0) D_8018F516 -= 4;
    p2 = &(*(u8 *)&D_8018F518);
    if (*p2 != 0) *p2 -= 4;
    if (D_8018F519 != 0) D_8018F519 -= 4;
    if (D_8018F51A != 0) D_8018F51A -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}



// @class: plumbing
// @stuck: none — MATCH

s32 func_8016BEA0(s32 param_1)
{
    extern void func_8016BF50(void);

    int iVar2;
    unsigned short uVar1;

    iVar2 = *(int *)(((int)param_1) + 0x20);
    func_8016BF50();
    uVar1 = *(unsigned short *)(((int)param_1) + 0x10) - 0x18;
    *(unsigned short *)(((int)param_1) + 0x10) = uVar1;
    *(unsigned short *)(iVar2 + 0x1a) = *(unsigned short *)(iVar2 + 0x1a) + uVar1;
    *(unsigned short *)(iVar2 + 0x12) = (*(unsigned short *)(iVar2 + 0x12) + 0x22) & 0xfff;
    ((void (*)(int, void *, void *, int))func_8016BFA8)(((int)param_1), &(*(int *)&D_8018F514), &(*(int *)&D_8018F518), iVar2 + 0x18);
    if (*(short *)(iVar2 + 0x1a) < 0) {
        ((void (*)(int))func_80146C3C)(((int)param_1));
    }
}



DEFINE_func_8016BF34()  /* dedup: shared engine-core @0x8016BF34 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016BF50);


extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_8018F4A0;

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {
    func_8016BFD0(a0, a1, a2, a3, &D_8018F4A0);
}


// @class: struct
// @stuck: none — MATCH (95 ins). Keys: (1) 4-byte unaligned copies via `struct{char b[4];}`
//   assignment -> lwl/lwr/swl/swr with reload; (2) 0x40-byte stack buffer `buf` (Mtx_8016BFD0 padded to
//   0x40, not 0x20) sets the frame to 0x70 and lands v1/v2 at sp+0x50/0x58; (3) func_80017714(a4)
//   takes param_5 as an arg -> gcc materializes `addu $a0,$s0,$zero` and stores the 4 zeros via $a0.

typedef struct { char b[4]; } W_8016BFD0;
typedef struct { s16 x, y, z; } Vec3_8016BFD0;
typedef struct {
    s16 m[9];    /* 0x00 */
    s16 pad;     /* 0x12 */
    s32 t[3];    /* 0x14, 0x18, 0x1c */
    s32 rest[8]; /* 0x20..0x3f */
} Mtx_8016BFD0;



void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4) {
    extern void func_80017714();
    extern s32 D_80182464;
    extern s32 D_8018246C;
    extern s32 D_80182474;
    extern s32 D_8018247C;

    Mtx_8016BFD0 buf;
    Vec3_8016BFD0 v1;
    Vec3_8016BFD0 v2;
    s32 iVar5 = *(s32 *)(a0 + 0x20);

    *(u32 *)((s32)a4 + 0x30) = 0x50000000;
    *(W_8016BFD0 *)((s32)a4 + 0x20) = *(W_8016BFD0 *)a1;
    *(W_8016BFD0 *)((s32)a4 + 0x24) = *(W_8016BFD0 *)a1;
    *(W_8016BFD0 *)((s32)a4 + 0x28) = *(W_8016BFD0 *)a2;
    *(W_8016BFD0 *)((s32)a4 + 0x2c) = *(W_8016BFD0 *)a2;

    v1.x = *(u16 *)(a0 + 6);
    v1.y = *(u16 *)(a0 + 0xa);
    v1.z = *(u16 *)(a0 + 0xe);
    ((void(*)())func_8012EFB8)(&v1, &v1);
    ((void(*)())func_80013F3C)(&buf);
    ((void(*)())func_800123F0)(&buf, (s32)*(s16 *)(iVar5 + 0x12));

    v2.x = *(u16 *)(a3 + 0);
    v2.y = *(u16 *)(a3 + 2);
    v2.z = *(u16 *)(a3 + 4);
    ((void(*)())func_80020F34)(&buf, &v2);

    buf.t[0] = v1.x;
    buf.t[1] = v1.y;
    buf.t[2] = v1.z;
    ((void(*)())func_8012F14C)(&buf, &D_80182464, (s32)a4);
    ((void(*)())func_8012F14C)(&buf, &D_8018246C, (s32)a4 + 8);
    ((void(*)())func_8012F14C)(&buf, &D_80182474, (s32)a4 + 0x10);
    ((void(*)())func_8012F14C)(&buf, &D_8018247C, (s32)a4 + 0x18);

    *(s16 *)((s32)a4 + 4) = 0;
    *(s16 *)((s32)a4 + 0xc) = 0;
    *(s16 *)((s32)a4 + 0x14) = 0;
    *(s16 *)((s32)a4 + 0x1c) = 0;
    func_80017714(a4);
}




extern void (*D_80182484[])(void);

void func_8016C14C(void *a0) {
    D_80182484[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_801465C0(void);
extern void func_80149350(s32 arg0);

void func_8016C188(s32 param)
{
    register s32 s1 __asm__("$17");
    register s32 s2 __asm__("$18");
    register u8 *s0 __asm__("$16");
    u16 buf[3];
    s16 *pBCC;
    s16 *pBD4;
    s32 t34;

    extern void func_80015954(s32, s32);
    extern s32 func_8016C374(s32, s32, s32, s32);
    extern void func_80146C3C(void);
    extern void func_8001CD9C(s32, void *);
    extern void func_800233CC(void *, unsigned short);
    extern u8 D_8018F4D4[];
    extern s16 D_8018F51C;
    extern s16 D_8018F51E;
    extern s16 D_8018F520;
    extern s16 D_8018F524;
    extern s16 D_8018F526;
    extern s16 D_8018F528;

    s1 = param;
    s2 = ((s32 (*)(void))func_801465C0)();
    *(s32 *)(s1 + 0x20) = s2;
    if (s2 != 0) {
        *(u16 *)(s1 + 0x12) = *(u16 *)(s1 + 0x6);
        *(u16 *)(s1 + 0x16) = *(u16 *)(s1 + 0xA);
        *(u16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0xE);
        t34 = *(s32 *)(s1 + 0x34);
        buf[0] = *(u16 *)(s1 + 0x12);
        buf[1] = *(u16 *)(s1 + 0x16);
        buf[2] = *(u16 *)(s1 + 0x1A);
        ((void (*)(s32, void *, void *))func_80149350)(t34, buf, buf);
        ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
        s0 = D_8018F4D4;
        ((void (*)(s32, void *))func_8001CD9C)(s2, s0);
        *(s16 *)(s2 + 0x1E) = 0xCCC;
        *(s32 *)(s2 + 4) = *(s32 *)(s2 + 4) | 0x50000000;
        ((void (*)(void *, s32))func_800233CC)(s0, 0x80);
        *(s16 *)(s2 + 0x1A) = 0;
        *(s16 *)(s2 + 0x18) = 0;
        *(s16 *)(s1 + 0x10) = 0;
        pBCC = &D_8018F51C;
        pBD4 = &D_8018F524;
        *pBCC = 0x20;
        D_8018F51E = 0x20;
        D_8018F520 = 0;
        *pBD4 = 0xC0;
        D_8018F526 = 0xC0;
        D_8018F528 = 0;
        ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, pBCC, pBD4, s0);
        *(u16 *)(s1 + 2) = *(u16 *)(s1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}



// @class: schedule
// @stuck: none — MATCH (44 ins; pins $s0/$s1 + hoist call-arg into a temp so its load fills the buf-store delay slot)


extern void func_80149350(s32 arg0);
extern void func_80015954(s32 a0, s32 a1);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);

extern u8 D_8018F51C[];
extern u8 D_8018F524[];
extern u8 D_8018F4D4[];

void func_8016C2C4(s32 param)
{
    register s32 s1 __asm__("$17");
    register s32 s0 __asm__("$16");
    u16 buf[3];
    s16 v;
    s32 r;
    s32 arg;

    s1 = param;
    s0 = *(s32 *)(s1 + 0x20);
    arg = *(s32 *)(s1 + 0x34);
    buf[0] = *(u16 *)(s1 + 0x12);
    buf[1] = *(u16 *)(s1 + 0x16);
    buf[2] = *(u16 *)(s1 + 0x1a);
    ((void (*)(s32, void *, void *))func_80149350)(arg, buf, buf);
    ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
    v = *(s16 *)(s1 + 0x10) + 0x10;
    *(s16 *)(s1 + 0x10) = v;
    v = *(s16 *)(s0 + 0x1a) + v;
    *(s16 *)(s0 + 0x1a) = v;
    *(s16 *)(s0 + 0x18) = v;
    r = ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, D_8018F51C, D_8018F524, D_8018F4D4);
    if (r == 0) {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}


DEFINE_func_8016C374()  /* dedup: shared engine-core @0x8016C374 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (172/172, relocation-masked)



s32 func_8016C49C(s32 param_1_arg) {
    extern s32 VectorNormalSS(void *, void *);
    extern void func_8001CD9C(s32, void *);
    extern void func_8016CF04(s32, s32);
    extern u8 D_8018F530[];
    extern u8 D_8018F5F0;

    register u16 *param_1 __asm__("$17") = ((u16 *)param_1_arg);
    int iVar5;
    int iVar6;
    u16 sv[4];
    s32 mat[8];
    short sVar1;

    iVar5 = *(int *)(param_1 + 0x18);
    iVar6 = *(int *)(param_1 + 0x1a);
    param_1[0x14] = *(u16 *)(iVar5 + 0x36);
    if ((*(u32 *)(param_1 + 0x16) & 0x8000) == 0) {
        short iVar4 = 0;
        u16 *psVar3 = (u16 *)&D_8011D030;
        do {
            if (psVar3 != param_1 && *psVar3 == 0x30) {
                ((void(*)(void *))func_80146C3C)(psVar3);
            }
            iVar4 = iVar4 + 1;
            psVar3 = psVar3 + 0x2c;
        } while (iVar4 < 0x1e);
        D_8018F530[1] = 0xff;
        D_8018F530[2] = 0x10;
        D_8018F530[0] = 0x10;
        D_8018F530[6] = 0;
        D_8018F530[5] = 0;
        D_8018F530[4] = 0;
        ((void(*)(void *, s32))func_800233CC)(D_8018F530, 10);
        sv[0] = *(u16 *)(iVar5 + 6) - *(u16 *)(iVar6 + 6);
        {
            int t = *(u16 *)(iVar6 + 0xa) + 0x28;
            sv[1] = *(u16 *)(iVar5 + 0xa) - t;
        }
        sv[2] = *(u16 *)(iVar5 + 0xe) - *(u16 *)(iVar6 + 0xe);
        VectorNormalSS(sv, sv);
        param_1[3] = *(u16 *)(iVar5 + 6) + ((s16)sv[0] >> 9);
        param_1[5] = *(u16 *)(iVar5 + 0xa) + (((s16)sv[1] >> 9) - 0x28);
        param_1[7] = *(u16 *)(iVar5 + 0xe) + ((s16)sv[2] >> 9);
        ((void(*)(void *))func_800D23D0)(sv);
        sv[0] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, param_1 + 0x1c);
        ((void(*)(void *, s32))func_80016714)(&D_8018F5F0, 0x620);
        ((s32(*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x32, param_1, 0, 0, 0, 0, *(int *)(param_1 + 0x18));
        sVar1 = 5;
    } else {
        int iVar5b = ((s32(*)())func_801465C0)();
        u32 uVar2;
        if (iVar5b == 0) {
            return;
        }
        func_8001CD9C(iVar5b, D_8018F530);
        *(u32 *)(iVar5b + 4) |= 0x50000000;
        uVar2 = ((int(*)())rand)();
        sv[0] = (uVar2 & 0x7f) * 8 - 0x80;
        sv[1] = ((uVar2 & 0x7f00) >> 4) - 0x400;
        sv[2] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, mat);
        ((void(*)(void *, void *))func_80048EAC)(param_1 + 0x1c, mat);
        sv[1] = 0;
        sv[0] = 0;
        sv[2] = 0xb;
        ((void(*)(void *, void *, void *))ApplyMatrixSV)(mat, sv, sv);
        param_1[9] = sv[0];
        param_1[0xb] = sv[1];
        param_1[0xd] = sv[2];
        *(int *)(param_1 + 0x10) = iVar5b;
        *(int *)(param_1 + 0xe) = 8;
        func_8016CF04((s32)param_1, 0);
        *(int *)(param_1 + 0x16) = 0;
        sVar1 = param_1[1] + 1;
    }
    param_1[1] = sVar1;
}



DEFINE_func_8016C74C()  /* dedup: shared engine-core @0x8016C74C (src/shared) */

DEFINE_func_8016C83C()  /* dedup: shared engine-core @0x8016C83C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016C998);


extern void (*D_8018248C[])(void);

void func_8016CB84(void *a0) {
    D_8018248C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016CBC0);

/* func_8016CF04 returns short (case 2: 1 if the decremented f2 hit 0, else 0; all other
 * paths return 0 via the addu $v0,$zero,$zero at 0x8016D154). The TU/engine_core.h declare
 * it `void` in 4 DEFINE_ macros + one block-scope decl in func_8016C49C; the real apply is the
 * byte-neutral engine_core.h void->short flip (every caller discards or ptr-casts the return,
 * cf. func_8016D5EC's `(s16)(...)` cast). The //@EDIT lines above are the rtu_match proxy for
 * that flip. Body verified 166/166 in isolation AND in a whole-TU compile w/ the reconciled hdr. */
typedef struct {
    u8 f0, f1, f2, f3;
    struct { s16 a, b, c, d, e, g; } ent[16];
} Blk_8016CF04_8016CF04;                /* 4 + 16*12 = 0xC4 stride */

short func_8016CF04(s32 param_1, s32 param_2) {
    extern Blk_8016CF04_8016CF04 D_8018F5F0[];


    Blk_8016CF04_8016CF04 *p = &D_8018F5F0[*(short *)(((int)param_1) + 0x2a)];
    u16 rot[4];
    u16 out[4];
    s32 mtx[8];

    switch (((short)param_2)) {
    case 0:
        p->f2 = 0;
        p->f1 = 0;
        p->f3 = 0xf0;
        break;
    case 1:
        p->f1 = p->f1 + 1;
        if ((u8)p->f1 >= 0x10)
            p->f1 = 0;
        if ((u8)p->f2 < 0xf)
            p->f2 = p->f2 + 1;
        break;
    case 2: {
        u8 c = p->f2 - 1;
        p->f2 = c;
        if (c == 0) {
            p->f0 = 0;
            return 1;
        }
        p->f3 = p->f3 - 0xf;
        return 0;
    }
    }

    rot[0] = *(s32 *)(((int)param_1) + 0x10) >> 12;
    rot[1] = *(s32 *)(((int)param_1) + 0x14) >> 12;
    rot[2] = *(s32 *)(((int)param_1) + 0x18) >> 12;
    func_800D23D0(rot);
    RotMatrixYXZ(rot, mtx);
    rot[0] = 9;
    rot[1] = 0;
    rot[2] = 0;
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].a = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].b = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].c = *(u16 *)(((int)param_1) + 0xe) + out[2];
    rot[0] = -rot[0];
    rot[1] = -rot[1];
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].d = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].e = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].g = *(u16 *)(((int)param_1) + 0xe) + out[2];
    return 0;
}




extern void (*D_801824A8[])(void);

void func_8016D19C(void *a0) {
    D_801824A8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016D1D8);


extern void (*D_801824B0[])(void);

void func_8016D428(void *a0) {
    D_801824B0[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016D464()  /* dedup: shared engine-core @0x8016D464 (src/shared) */

DEFINE_func_8016D4DC()  /* dedup: shared engine-core @0x8016D4DC (src/shared) */

DEFINE_func_8016D5EC()  /* dedup: shared engine-core @0x8016D5EC (src/shared) */

DEFINE_func_8016D64C()  /* dedup: shared engine-core @0x8016D64C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016D688);

DEFINE_func_8016D778()  /* dedup: shared engine-core @0x8016D778 (src/shared) */

DEFINE_func_8016D848()  /* dedup: shared engine-core @0x8016D848 (src/shared) */

DEFINE_func_8016D984()  /* dedup: shared engine-core @0x8016D984 (src/shared) */

DEFINE_func_8016DA04()  /* dedup: shared engine-core @0x8016DA04 (src/shared) */


// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8016DBD8(u8 *a0);
extern void (*D_80182518[])(int);

void func_8016DA30(int param_1)
{
    ((void (*)(void))func_8016DBD8)();
    D_80182518[*(unsigned short *)(param_1 + 2)](param_1);
}




// @class: plumbing
// @stuck: none — MATCH (clean if/else, one call-crossing local; bnez polarity = if(iVar1==0) fall-through)

extern void func_801465C0(void);
extern void func_80146C3C(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

extern u8 D_801824BC;
extern u8 D_801824C8;

void func_8016DA7C(s32 param_1)
{
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    if (iVar1 == 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    } else {
        *(s32 *)(param_1 + 0x20) = iVar1;
        ((void (*)(s32, s32, s32, s32))func_8001CC3C)(iVar1, (s32)&D_801824BC, 0x250, 0x100);
        *(u8 *)(iVar1 + 0x27) = 0x90;
        *(u16 *)(iVar1 + 0x18) = 0x3000;
        *(u16 *)(iVar1 + 0x1a) = 0x4000;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        func_80128EA8(iVar1, param_1 + 0x24, (s32)&D_801824C8);
        *(s32 *)(param_1 + 0x10) = 0;
        *(s32 *)(param_1 + 0x14) = 0xfff40000;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
}


DEFINE_func_8016DB34()  /* dedup: shared engine-core @0x8016DB34 (src/shared) */

DEFINE_func_8016DBD8()  /* dedup: shared engine-core @0x8016DBD8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016DC20);


extern void (*D_8018254C[])(void);

void func_8016DEA4(void *a0) {
    D_8018254C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016DEE0()  /* dedup: shared engine-core @0x8016DEE0 (src/shared) */


extern void (*D_80182554[])(void);

void func_8016DF20(void *a0) {
    D_80182554[*(u16 *)((s32)a0 + 0x2)]();
}


extern Blk20 D_800AE620;
extern s32 D_8011D030;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_801465C0(void);
extern void func_80146C3C(void);

typedef struct { s32 w[8]; } Blk20_8016DF5C;



void func_8016DF5C(s32 param_1)
{
    extern void func_8016E3CC(void *a0);
    extern void RotMatrixY(s32 a0, void *a1);
    extern u8 D_8018FC18;
    extern u8 D_8018FC19;
    extern u8 D_8018FC1A;
    extern u8 D_8018FC1C;
    extern u8 D_8018FC1D;
    extern u8 D_8018FC1E;

    s32 iVar8;
    short sVar1;

    iVar8 = *(s32 *)((u8 *)((void *)param_1) + 0x34);
    if ((*(u32 *)((u8 *)((void *)param_1) + 0x2c) & 0x8000) == 0) {
        unsigned short uVar7 = 0;
        u16 *psVar6 = (u16 *)&D_8011D030;
        register s32 iNew __asm__("$17");
        s32 base;
        do {
            if (psVar6 != (u16 *)((void *)param_1) && (*psVar6 == 0x41 || *psVar6 == 0x48)) {
                ((void (*)(void *))func_80146C3C)(psVar6);
            }
            uVar7++;
            psVar6 += 0x2c;
        } while (uVar7 < 0x1e);
        iNew = ((s32(*)())func_801465C0)();
        if (iNew == 0) {
            return;
        }
        base = (s32)&D_8018FC18;
        D_8018FC1A = 0xc0;
        *(u8 *)base = 0xc0;
        D_8018FC19 = 0;
        D_8018FC1E = 0;
        D_8018FC1D = 0;
        D_8018FC1C = 0;
        ((void(*)(void *, unsigned short))func_800233CC)((void *)base, 0x40);
        func_8001CD50(iNew, base);
        *(s32 *)(iNew + 0x34) = (s32)((u8 *)((void *)param_1) + 0x38);
        *(s16 *)(iNew + 0x1a) = 0;
        *(s16 *)(iNew + 0x18) = 0;
        *(u32 *)(iNew + 4) = *(u32 *)(iNew + 4) | 0x50000000;
        func_8016E3CC(((void *)param_1));
        {
            register s32 t10 __asm__("$3");
            t10 = 0x10;
            *(s32 *)((u8 *)((void *)param_1) + 0x20) = iNew;
            *(s32 *)((u8 *)((void *)param_1) + 0x1c) = t10;
        }
        sVar1 = *(u16 *)((u8 *)((void *)param_1) + 2) + 1;
    } else {
        short asStack_60[20];
        Blk20_8016DF5C localMatrix;
        s32 uVar2;

        asStack_60[0] = 0;
        asStack_60[1] = 0;
        asStack_60[2] = 0x20;
        localMatrix = (*(Blk20_8016DF5C*)&D_800AE620);
        uVar2 = ((s32(*)())rand)();
        RotMatrixY((uVar2 & 0x7f00) >> 3, &localMatrix);
        ApplyMatrixSV(&localMatrix, asStack_60, asStack_60);
        *(s16 *)((u8 *)((void *)param_1) + 6) = D_80126B5E + asStack_60[0];
        *(s16 *)((u8 *)((void *)param_1) + 0xa) = D_80126B62 - ((u16)uVar2 & 0x3f);
        *(s16 *)((u8 *)((void *)param_1) + 0xe) = D_80126B66 + asStack_60[2];
        *(Blk20_8016DF5C *)((u8 *)((void *)param_1) + 0x38) = *(Blk20_8016DF5C *)((u8 *)iVar8 + 0x38);
        *(s32 *)((u8 *)((void *)param_1) + 0x2c) = 0x1000;
        *(s32 *)((u8 *)((void *)param_1) + 0x30) = 0xff;
        *(s32 *)((u8 *)((void *)param_1) + 0x1c) = 0x10;
        __asm__ __volatile__("" ::: "memory");
        sVar1 = 4;
    }
    *(s16 *)((u8 *)((void *)param_1) + 2) = sVar1;
}


DEFINE_func_8016E1CC()  /* dedup: shared engine-core @0x8016E1CC (src/shared) */

DEFINE_func_8016E26C()  /* dedup: shared engine-core @0x8016E26C (src/shared) */

DEFINE_func_8016E2E8()  /* dedup: shared engine-core @0x8016E2E8 (src/shared) */

DEFINE_func_8016E358()  /* dedup: shared engine-core @0x8016E358 (src/shared) */

DEFINE_func_8016E3CC()  /* dedup: shared engine-core @0x8016E3CC (src/shared) */

DEFINE_func_8016E460()  /* dedup: shared engine-core @0x8016E460 (src/shared) */


extern void (*D_801825A8[])(void);

void func_8016E5B8(void *a0) {
    D_801825A8[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8016E5F4()  /* dedup: shared engine-core @0x8016E5F4 (src/shared) */

DEFINE_func_8016E688()  /* dedup: shared engine-core @0x8016E688 (src/shared) */

DEFINE_func_8016E6E4()  /* dedup: shared engine-core @0x8016E6E4 (src/shared) */

DEFINE_func_8016E728()  /* dedup: shared engine-core @0x8016E728 (src/shared) */

DEFINE_func_8016E778()  /* dedup: shared engine-core @0x8016E778 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (74 ins); register pin $s2 forces &prim into a saved reg (§17)

typedef struct { short vx, vy, vz, pad; } SVECTOR_8016E7C8;                 /* 0x08 */
typedef struct { short m[3][3]; short pad; s32 t[3]; } MATRIX_8016E7C8;     /* 0x20 */

typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;


void func_8016E7C8(int param_1, short *param_2, unsigned int *param_3)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern void func_80016ED4(void *a0);
    extern SVECTOR_8016E7C8 D_80182568[4];
    extern s32 D_80182588;
    extern s32 D_80182590;
    extern s32 D_80182598;
    extern s32 D_801825A0;

    Prim_8016E7C8 prim;
    MATRIX_8016E7C8 m;
    SVECTOR_8016E7C8 tmp;
    register Prim_8016E7C8 *pp __asm__("$18");   /* $s2 — force &prim into a saved reg */

    ((void (*)(void *, void *))func_80017DC4)(param_2, &m);
    m.t[0] = *(short *)(param_1 + 6);
    m.t[1] = *(short *)(param_1 + 10);
    m.t[2] = *(short *)(param_1 + 14);
    func_8004914C(&m);
    func_800491AC(&m);
    pp = &prim;
    RotTransSV(&D_80182568[0], pp, &tmp);
    RotTransSV(&D_80182568[1], &prim.v[1], &tmp);
    RotTransSV(&D_80182568[2], &prim.v[2], &tmp);
    RotTransSV(&D_80182568[3], &prim.v[3], &tmp);
    prim.v[0].vz = 3;
    prim.f5 = 0x50000000;
    prim.f0 = D_80182588;
    prim.f1 = D_80182590;
    prim.f2 = D_80182598;
    prim.f3 = D_801825A0;
    prim.f4 = *param_3;
    prim.f6 = 0x27;
    func_80016ED4(pp);
}



DEFINE_func_8016E8F0()  /* dedup: shared engine-core @0x8016E8F0 (src/shared) */

DEFINE_func_8016E918()  /* dedup: shared engine-core @0x8016E918 (src/shared) */

// @class: struct
// @stuck: none — MATCH (36/36 ins, match_one relocation-masked)


struct Entry_8016E95C {
    u8 f0;
    u8 f1;
    u8 pad[0x1e];
};

typedef void (*Handler)(struct Entry_8016E95C *);


s32 func_8016E95C() {
    extern Handler D_801825E8[];

    struct Entry_8016E95C *p;
    for (p = ((struct Entry_8016E95C *)&D_80115218); p < &((struct Entry_8016E95C *)&D_80115218)[4]; p++) {
        if (p->f0 != 0) {
            D_801825E8[p->f1](p);
        }
    }
}



INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016E9EC);


// @class: struct
// @stuck: none — MATCH (31/31 ins, match_one verified)

extern u16 D_801825DC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EAC0(Wave *param_1)
{
    unsigned char bVar1;

    param_1->f4 = param_1->f4 + D_801825DC[param_1->f2];
    ((void (*)(void *, int))func_8016EC0C)(param_1, 0x80);
    bVar1 = param_1->f2 + 1;
    param_1->f2 = bVar1;
    if (5 < bVar1) {
        param_1->f2 = 0x20;
        param_1->f1 = param_1->f1 + 1;
    }
}



// @class: loose-typing
// @stuck: none — MATCH (u8 v + 0xFF emits addiu 0xFF; v-1 would emit -1/0xffff)

extern u8 D_801825CC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EB3C(s32 p) {
    u8 v;

    ((void (*)(s32, s32))func_8016EC0C)(p, D_801825CC[*(u8 *)(p + 2) & 3]);

    v = *(u8 *)(p + 2);
    *(u8 *)(p + 2) = v + 0xFF;
    if (v == 0) {
        *(u8 *)(p + 2) = 5;
        *(u8 *)(p + 1) = *(u8 *)(p + 1) + 1;
    }
}



// @class: struct
// @stuck: none — MATCH (25 ins). %lo-fold via extern u16 D_801825DC[]; predecrement emitted as +0xFF (u8 promote→sb low byte), not -1.

extern u16 D_801825DC[];

extern s32 func_8016EC0C(s32 a0, s32 a1);

void func_8016EBA8(u8 *param_1)
{
    u8 c;

    *(u16 *)(param_1 + 4) =
        *(u16 *)(param_1 + 4) - D_801825DC[param_1[2]];
    ((void (*)(u8 *, int))func_8016EC0C)(param_1, 0x80);
    c = param_1[2];
    param_1[2] = c + 0xFF;
    if (c == 0) {
        param_1[0] = 0;
    }
}


INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016EC0C);

DEFINE_func_8016ED6C()  /* dedup: shared engine-core @0x8016ED6C (src/shared) */

DEFINE_func_8016ED8C()  /* dedup: shared engine-core @0x8016ED8C (src/shared) */

DEFINE_func_8016EDBC()  /* dedup: shared engine-core @0x8016EDBC (src/shared) */

DEFINE_func_8016EDEC()  /* dedup: shared engine-core @0x8016EDEC (src/shared) */

DEFINE_func_8016EE40()  /* dedup: shared engine-core @0x8016EE40 (src/shared) */

DEFINE_func_8016EE94()  /* dedup: shared engine-core @0x8016EE94 (src/shared) */

DEFINE_func_8016EF78()  /* dedup: shared engine-core @0x8016EF78 (src/shared) */

DEFINE_func_8016EFA8()  /* dedup: shared engine-core @0x8016EFA8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016EFC8);

DEFINE_func_8016F094()  /* dedup: shared engine-core @0x8016F094 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH

s32 func_8016F0AC()
{
    extern void func_8016F0E4(void);


    ((void (*)(void *))func_8016F0E4)(&D_80126B58);
    ((void (*)(void *))func_80165770)(&D_80126B58);
}



INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8016F0E4);

DEFINE_func_8016F14C()  /* dedup: shared engine-core @0x8016F14C (src/shared) */

DEFINE_func_8016F1AC()  /* dedup: shared engine-core @0x8016F1AC (src/shared) */


// @class: schedule
// @stuck: none — MATCH

extern s32 D_801825F8;
extern s32 D_80126B58;
extern s16 currentLocationId;

s32 func_8016F1C4(void) {
    s32 *p;
    s32 cur;
    s32 loc;
    s32 v;
    s32 *base = &D_80126B58;

    p = &D_801825F8;
    cur = *p;
    if (cur != 0) {
        loc = currentLocationId;
        p = p + 1;
        for (;;) {
            if (loc == cur) {
                return 1;
            }
            cur = *p;
            p = p + 1;
            if (cur == 0) {
                break;
            }
        }
    }
    v = base[0x7E];
    if (((v & 0x80FFFFFF) != 0) && ((v & 0x10000000) != 0)) {
        return 0;
    }
    return base[0x7E] & 0x80FFFFFF;
}


DEFINE_func_8016F250()  /* dedup: shared engine-core @0x8016F250 (src/shared) */

DEFINE_func_8016F264()  /* dedup: shared engine-core @0x8016F264 (src/shared) */

DEFINE_func_8016F288()  /* dedup: shared engine-core @0x8016F288 (src/shared) */

DEFINE_func_8016F2A8()  /* dedup: shared engine-core @0x8016F2A8 (src/shared) */

DEFINE_func_8016F2C8()  /* dedup: shared engine-core @0x8016F2C8 (src/shared) */

DEFINE_func_8016F2EC()  /* dedup: shared engine-core @0x8016F2EC (src/shared) */

DEFINE_func_8016F30C()  /* dedup: shared engine-core @0x8016F30C (src/shared) */

DEFINE_func_8016F330()  /* dedup: shared engine-core @0x8016F330 (src/shared) */

DEFINE_func_8016F350()  /* dedup: shared engine-core @0x8016F350 (src/shared) */

DEFINE_func_8016F374()  /* dedup: shared engine-core @0x8016F374 (src/shared) */

DEFINE_func_8016F388()  /* dedup: shared engine-core @0x8016F388 (src/shared) */

DEFINE_func_8016F398()  /* dedup: shared engine-core @0x8016F398 (src/shared) */

DEFINE_func_8016F410()  /* dedup: shared engine-core @0x8016F410 (src/shared) */

DEFINE_func_8016F44C()  /* dedup: shared engine-core @0x8016F44C (src/shared) */

DEFINE_func_8016F470()  /* dedup: shared engine-core @0x8016F470 (src/shared) */

DEFINE_func_8016F494()  /* dedup: shared engine-core @0x8016F494 (src/shared) */

DEFINE_func_8016F4C4()  /* dedup: shared engine-core @0x8016F4C4 (src/shared) */

DEFINE_func_8016F4F4()  /* dedup: shared engine-core @0x8016F4F4 (src/shared) */

DEFINE_func_8016F4FC()  /* dedup: shared engine-core @0x8016F4FC (src/shared) */

DEFINE_func_8016F540()  /* dedup: shared engine-core @0x8016F540 (src/shared) */

DEFINE_func_8016F578()  /* dedup: shared engine-core @0x8016F578 (src/shared) */

DEFINE_func_8016F5B0()  /* dedup: shared engine-core @0x8016F5B0 (src/shared) */

DEFINE_func_8016F5E0()  /* dedup: shared engine-core @0x8016F5E0 (src/shared) */

DEFINE_func_8016F610()  /* dedup: shared engine-core @0x8016F610 (src/shared) */

DEFINE_func_8016F648()  /* dedup: shared engine-core @0x8016F648 (src/shared) */

DEFINE_func_8016F680()  /* dedup: shared engine-core @0x8016F680 (src/shared) */

DEFINE_func_8016F6B0()  /* dedup: shared engine-core @0x8016F6B0 (src/shared) */


extern void (*D_80182670[])(void);

void func_8016F6E0(void *a0) {
    D_80182670[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F71C()  /* dedup: shared engine-core @0x8016F71C (src/shared) */

DEFINE_func_8016F764()  /* dedup: shared engine-core @0x8016F764 (src/shared) */


extern void (*D_80182678[])(void);

void func_8016F798(void *a0) {
    D_80182678[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F7D4()  /* dedup: shared engine-core @0x8016F7D4 (src/shared) */

DEFINE_func_8016F804()  /* dedup: shared engine-core @0x8016F804 (src/shared) */


extern void (*D_80182680[])(void);

void func_8016F834(void *a0) {
    D_80182680[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F870()  /* dedup: shared engine-core @0x8016F870 (src/shared) */

DEFINE_func_8016F8AC()  /* dedup: shared engine-core @0x8016F8AC (src/shared) */


extern void (*D_80182688[])(void);

void func_8016F8E4(void *a0) {
    D_80182688[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016F920()  /* dedup: shared engine-core @0x8016F920 (src/shared) */

DEFINE_func_8016F95C()  /* dedup: shared engine-core @0x8016F95C (src/shared) */


extern void (*D_80182690[])(void);

void func_8016F9C4(void *a0) {
    D_80182690[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FA00()  /* dedup: shared engine-core @0x8016FA00 (src/shared) */

DEFINE_func_8016FA44()  /* dedup: shared engine-core @0x8016FA44 (src/shared) */


extern void (*D_80182698[])(void);

void func_8016FA84(void *a0) {
    D_80182698[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FAC0()  /* dedup: shared engine-core @0x8016FAC0 (src/shared) */

DEFINE_func_8016FB10()  /* dedup: shared engine-core @0x8016FB10 (src/shared) */

DEFINE_func_8016FB50()  /* dedup: shared engine-core @0x8016FB50 (src/shared) */


extern void (*D_801826A4[])(void);

void func_8016FB7C(void *a0) {
    D_801826A4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FBB8()  /* dedup: shared engine-core @0x8016FBB8 (src/shared) */

DEFINE_func_8016FC24()  /* dedup: shared engine-core @0x8016FC24 (src/shared) */

DEFINE_func_8016FC64()  /* dedup: shared engine-core @0x8016FC64 (src/shared) */


extern void (*D_801826B0[])(void);

void func_8016FC90(void *a0) {
    D_801826B0[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FCCC()  /* dedup: shared engine-core @0x8016FCCC (src/shared) */

DEFINE_func_8016FD08()  /* dedup: shared engine-core @0x8016FD08 (src/shared) */

DEFINE_func_8016FD7C()  /* dedup: shared engine-core @0x8016FD7C (src/shared) */


extern void (*D_801826BC[])(void);

void func_8016FDB4(void *a0) {
    D_801826BC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FDF0()  /* dedup: shared engine-core @0x8016FDF0 (src/shared) */

DEFINE_func_8016FE2C()  /* dedup: shared engine-core @0x8016FE2C (src/shared) */

DEFINE_func_8016FE78()  /* dedup: shared engine-core @0x8016FE78 (src/shared) */

DEFINE_func_8016FED0()  /* dedup: shared engine-core @0x8016FED0 (src/shared) */


extern void (*D_801826CC[])(void);

void func_8016FF30(void *a0) {
    D_801826CC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8016FF6C()  /* dedup: shared engine-core @0x8016FF6C (src/shared) */

DEFINE_func_8016FFA8()  /* dedup: shared engine-core @0x8016FFA8 (src/shared) */


extern void (*D_801826DC[])(void);

void func_8016FFDC(void *a0) {
    D_801826DC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170018()  /* dedup: shared engine-core @0x80170018 (src/shared) */

DEFINE_func_80170068()  /* dedup: shared engine-core @0x80170068 (src/shared) */

DEFINE_func_801700B8()  /* dedup: shared engine-core @0x801700B8 (src/shared) */

DEFINE_func_80170100()  /* dedup: shared engine-core @0x80170100 (src/shared) */


extern void (*D_801826E4[])(void);

void func_80170150(void *a0) {
    D_801826E4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017018C()  /* dedup: shared engine-core @0x8017018C (src/shared) */

DEFINE_func_801701C8()  /* dedup: shared engine-core @0x801701C8 (src/shared) */


extern void (*D_801826EC[])(void);

void func_80170240(void *a0) {
    D_801826EC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017027C()  /* dedup: shared engine-core @0x8017027C (src/shared) */

DEFINE_func_801702B8()  /* dedup: shared engine-core @0x801702B8 (src/shared) */


extern void (*D_801826F4[])(void);

void func_801702FC(void *a0) {
    D_801826F4[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170338()  /* dedup: shared engine-core @0x80170338 (src/shared) */

DEFINE_func_80170374()  /* dedup: shared engine-core @0x80170374 (src/shared) */


extern void (*D_801826FC[])(void);

void func_801703E0(void *a0) {
    D_801826FC[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017041C()  /* dedup: shared engine-core @0x8017041C (src/shared) */

DEFINE_func_8017044C()  /* dedup: shared engine-core @0x8017044C (src/shared) */


extern void (*D_80182704[])(void);

void func_801704B0(void *a0) {
    D_80182704[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801704EC()  /* dedup: shared engine-core @0x801704EC (src/shared) */

DEFINE_func_8017051C()  /* dedup: shared engine-core @0x8017051C (src/shared) */


extern void (*D_8018270C[])(void);

void func_80170548(void *a0) {
    D_8018270C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170584()  /* dedup: shared engine-core @0x80170584 (src/shared) */

DEFINE_func_801705C0()  /* dedup: shared engine-core @0x801705C0 (src/shared) */



extern void (*D_80182714[])(void);

void func_801705F8(void *a0) {
    D_80182714[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170634()  /* dedup: shared engine-core @0x80170634 (src/shared) */

DEFINE_func_80170670()  /* dedup: shared engine-core @0x80170670 (src/shared) */


extern void (*D_8018271C[])(void);

void func_801706AC(void *a0) {
    D_8018271C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801706E8()  /* dedup: shared engine-core @0x801706E8 (src/shared) */

DEFINE_func_80170718()  /* dedup: shared engine-core @0x80170718 (src/shared) */


extern void (*D_80182724[])(void);

void func_80170748(void *a0) {
    D_80182724[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170784()  /* dedup: shared engine-core @0x80170784 (src/shared) */

DEFINE_func_801707D4()  /* dedup: shared engine-core @0x801707D4 (src/shared) */


extern void (*D_8018272C[])(void);

void func_80170810(void *a0) {
    D_8018272C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017084C()  /* dedup: shared engine-core @0x8017084C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_801708B0);

DEFINE_func_80170928()  /* dedup: shared engine-core @0x80170928 (src/shared) */

DEFINE_func_80170970()  /* dedup: shared engine-core @0x80170970 (src/shared) */

DEFINE_func_801709B8()  /* dedup: shared engine-core @0x801709B8 (src/shared) */

DEFINE_func_80170A00()  /* dedup: shared engine-core @0x80170A00 (src/shared) */

DEFINE_func_80170A48()  /* dedup: shared engine-core @0x80170A48 (src/shared) */

DEFINE_func_80170A90()  /* dedup: shared engine-core @0x80170A90 (src/shared) */


extern void (*D_80182734[])(void);

void func_80170AD8(void *a0) {
    D_80182734[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170B14()  /* dedup: shared engine-core @0x80170B14 (src/shared) */

DEFINE_func_80170B48()  /* dedup: shared engine-core @0x80170B48 (src/shared) */

DEFINE_func_80170B90()  /* dedup: shared engine-core @0x80170B90 (src/shared) */


extern void (*D_8018273C[])(void);

void func_80170BD8(void *a0) {
    D_8018273C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170C14()  /* dedup: shared engine-core @0x80170C14 (src/shared) */

DEFINE_func_80170C44()  /* dedup: shared engine-core @0x80170C44 (src/shared) */


extern void (*D_80182744[])(void);

void func_80170C74(void *a0) {
    D_80182744[*(u8 *)((s32)a0 + 0x215)]();
}


DEFINE_func_80170CB0()  /* dedup: shared engine-core @0x80170CB0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_80170CF0);


extern void (*D_8018274C[])(void);

void func_80170D68(void *a0) {
    D_8018274C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170DA4()  /* dedup: shared engine-core @0x80170DA4 (src/shared) */

DEFINE_func_80170DE0()  /* dedup: shared engine-core @0x80170DE0 (src/shared) */


extern void (*D_80182754[])(void);

void func_80170E34(void *a0) {
    D_80182754[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170E70()  /* dedup: shared engine-core @0x80170E70 (src/shared) */

DEFINE_func_80170EAC()  /* dedup: shared engine-core @0x80170EAC (src/shared) */


extern void (*D_8018275C[])(void);

void func_80170EFC(void *a0) {
    D_8018275C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170F38()  /* dedup: shared engine-core @0x80170F38 (src/shared) */

DEFINE_func_80170F74()  /* dedup: shared engine-core @0x80170F74 (src/shared) */


extern void (*D_80182764[])(void);

void func_80170FB0(void *a0) {
    D_80182764[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80170FEC()  /* dedup: shared engine-core @0x80170FEC (src/shared) */

DEFINE_func_80171028()  /* dedup: shared engine-core @0x80171028 (src/shared) */


extern void (*D_8018276C[])(void);

void func_80171064(void *a0) {
    D_8018276C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801710A0()  /* dedup: shared engine-core @0x801710A0 (src/shared) */

DEFINE_func_801710DC()  /* dedup: shared engine-core @0x801710DC (src/shared) */


extern void (*D_80182774[])(void);

void func_80171120(void *a0) {
    D_80182774[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_8017115C()  /* dedup: shared engine-core @0x8017115C (src/shared) */

DEFINE_func_8017118C()  /* dedup: shared engine-core @0x8017118C (src/shared) */


extern void (*D_8018277C[])(void);

void func_801711C0(void *a0) {
    D_8018277C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_801711FC()  /* dedup: shared engine-core @0x801711FC (src/shared) */

DEFINE_func_80171238()  /* dedup: shared engine-core @0x80171238 (src/shared) */


extern void (*D_80182784[])(void);

void func_80171260(void *a0) {
    D_80182784[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_8017129C);

DEFINE_func_80171384()  /* dedup: shared engine-core @0x80171384 (src/shared) */


extern void (*D_8018278C[])(void);

void func_801714E4(void *a0) {
    D_8018278C[*(u8 *)((s32)a0 + 0x216)]();
}


DEFINE_func_80171520()  /* dedup: shared engine-core @0x80171520 (src/shared) */

DEFINE_func_8017162C()  /* dedup: shared engine-core @0x8017162C (src/shared) */

DEFINE_func_801716AC()  /* dedup: shared engine-core @0x801716AC (src/shared) */

DEFINE_func_801717A0()  /* dedup: shared engine-core @0x801717A0 (src/shared) */

DEFINE_func_801717F4()  /* dedup: shared engine-core @0x801717F4 (src/shared) */

DEFINE_func_80171824()  /* dedup: shared engine-core @0x80171824 (src/shared) */

DEFINE_func_80171854()  /* dedup: shared engine-core @0x80171854 (src/shared) */

DEFINE_func_80171884()  /* dedup: shared engine-core @0x80171884 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_801718AC);

DEFINE_func_80171904()  /* dedup: shared engine-core @0x80171904 (src/shared) */

DEFINE_func_80171928()  /* dedup: shared engine-core @0x80171928 (src/shared) */

DEFINE_func_8017196C()  /* dedup: shared engine-core @0x8017196C (src/shared) */

DEFINE_func_8017197C()  /* dedup: shared engine-core @0x8017197C (src/shared) */

DEFINE_func_80171990()  /* dedup: shared engine-core @0x80171990 (src/shared) */

DEFINE_func_801719A4()  /* dedup: shared engine-core @0x801719A4 (src/shared) */

DEFINE_func_80171A04()  /* dedup: shared engine-core @0x80171A04 (src/shared) */

DEFINE_func_80171A10()  /* dedup: shared engine-core @0x80171A10 (src/shared) */

DEFINE_func_80171A1C()  /* dedup: shared engine-core @0x80171A1C (src/shared) */

DEFINE_func_80171A34()  /* dedup: shared engine-core @0x80171A34 (src/shared) */

DEFINE_func_80171A44()  /* dedup: shared engine-core @0x80171A44 (src/shared) */

DEFINE_func_80171A58()  /* dedup: shared engine-core @0x80171A58 (src/shared) */

DEFINE_func_80171A6C()  /* dedup: shared engine-core @0x80171A6C (src/shared) */

DEFINE_func_80171A80()  /* dedup: shared engine-core @0x80171A80 (src/shared) */

DEFINE_func_80171A88()  /* dedup: shared engine-core @0x80171A88 (src/shared) */

DEFINE_func_80171AB0()  /* dedup: shared engine-core @0x80171AB0 (src/shared) */

DEFINE_func_80171B10()  /* dedup: shared engine-core @0x80171B10 (src/shared) */

DEFINE_func_80171B44()  /* dedup: shared engine-core @0x80171B44 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_80171B4C);

DEFINE_func_80171C64()  /* dedup: shared engine-core @0x80171C64 (src/shared) */

DEFINE_func_80171CC4()  /* dedup: shared engine-core @0x80171CC4 (src/shared) */

DEFINE_func_80171D1C()  /* dedup: shared engine-core @0x80171D1C (src/shared) */

DEFINE_func_80171D78()  /* dedup: shared engine-core @0x80171D78 (src/shared) */

DEFINE_func_80171E08()  /* dedup: shared engine-core @0x80171E08 (src/shared) */

DEFINE_func_80171EC8()  /* dedup: shared engine-core @0x80171EC8 (src/shared) */


extern s32 func_8017248C(s32, s32);
extern s32 ratan2(s32, s32);
extern void func_80172170(s32, s32);
extern void func_80146D90(s32);

s32 func_80171FFC(short *a0, short *a1, s32 a2)
{
    s32 r;

    r = func_8017248C((s32)a0, (s32)a1);
    if (r != 0) {
        func_80146D90((s32)a0);
        return r;
    }
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        (ratan2(a1[0] - a0[3], a1[2] - a0[7]) + 0x800) & 0xFFF;
    func_80172170((s32)a0, a2 & 0xFF);
    return 0;
}


DEFINE_func_8017209C()  /* dedup: shared engine-core @0x8017209C (src/shared) */

DEFINE_func_80172170()  /* dedup: shared engine-core @0x80172170 (src/shared) */

DEFINE_func_801722CC()  /* dedup: shared engine-core @0x801722CC (src/shared) */

DEFINE_func_80172304()  /* dedup: shared engine-core @0x80172304 (src/shared) */

DEFINE_func_80172310()  /* dedup: shared engine-core @0x80172310 (src/shared) */

DEFINE_func_80172358()  /* dedup: shared engine-core @0x80172358 (src/shared) */

DEFINE_func_801723C4()  /* dedup: shared engine-core @0x801723C4 (src/shared) */

DEFINE_func_80172414()  /* dedup: shared engine-core @0x80172414 (src/shared) */

DEFINE_func_8017248C()  /* dedup: shared engine-core @0x8017248C (src/shared) */

DEFINE_func_801724EC()  /* dedup: shared engine-core @0x801724EC (src/shared) */

DEFINE_func_8017250C()  /* dedup: shared engine-core @0x8017250C (src/shared) */

DEFINE_func_80172560()  /* dedup: shared engine-core @0x80172560 (src/shared) */

DEFINE_func_80172588()  /* dedup: shared engine-core @0x80172588 (src/shared) */

DEFINE_func_80172590()  /* dedup: shared engine-core @0x80172590 (src/shared) */

DEFINE_func_801725A4()  /* dedup: shared engine-core @0x801725A4 (src/shared) */

DEFINE_func_801725B8()  /* dedup: shared engine-core @0x801725B8 (src/shared) */

DEFINE_func_801725CC()  /* dedup: shared engine-core @0x801725CC (src/shared) */

DEFINE_func_801725E0()  /* dedup: shared engine-core @0x801725E0 (src/shared) */

DEFINE_func_801725F4()  /* dedup: shared engine-core @0x801725F4 (src/shared) */

DEFINE_func_80172608()  /* dedup: shared engine-core @0x80172608 (src/shared) */

DEFINE_func_8017261C()  /* dedup: shared engine-core @0x8017261C (src/shared) */

DEFINE_func_80172630()  /* dedup: shared engine-core @0x80172630 (src/shared) */

DEFINE_func_80172644()  /* dedup: shared engine-core @0x80172644 (src/shared) */

DEFINE_func_80172658()  /* dedup: shared engine-core @0x80172658 (src/shared) */

DEFINE_func_80172664()  /* dedup: shared engine-core @0x80172664 (src/shared) */

DEFINE_func_80172670()  /* dedup: shared engine-core @0x80172670 (src/shared) */

DEFINE_func_8017267C()  /* dedup: shared engine-core @0x8017267C (src/shared) */

DEFINE_func_80172688()  /* dedup: shared engine-core @0x80172688 (src/shared) */

DEFINE_func_80172694()  /* dedup: shared engine-core @0x80172694 (src/shared) */

DEFINE_func_801726A0()  /* dedup: shared engine-core @0x801726A0 (src/shared) */

DEFINE_func_801726AC()  /* dedup: shared engine-core @0x801726AC (src/shared) */

DEFINE_func_801726B8()  /* dedup: shared engine-core @0x801726B8 (src/shared) */

DEFINE_func_801726C4()  /* dedup: shared engine-core @0x801726C4 (src/shared) */

DEFINE_func_801726D0()  /* dedup: shared engine-core @0x801726D0 (src/shared) */

DEFINE_func_80172710()  /* dedup: shared engine-core @0x80172710 (src/shared) */

DEFINE_func_80172738()  /* dedup: shared engine-core @0x80172738 (src/shared) */

DEFINE_func_80172760()  /* dedup: shared engine-core @0x80172760 (src/shared) */

DEFINE_func_80172780()  /* dedup: shared engine-core @0x80172780 (src/shared) */



s32 func_801727D0(void *a0) {

    extern void (*D_8018279C[])(void);
    D_8018279C[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_8017280C()  /* dedup: shared engine-core @0x8017280C (src/shared) */

DEFINE_func_80172844()  /* dedup: shared engine-core @0x80172844 (src/shared) */

DEFINE_func_8017288C()  /* dedup: shared engine-core @0x8017288C (src/shared) */

DEFINE_func_80172894()  /* dedup: shared engine-core @0x80172894 (src/shared) */



s32 func_801728E4(void *a0) {

    extern void (*D_801827A8[])(void);
    D_801827A8[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172920()  /* dedup: shared engine-core @0x80172920 (src/shared) */

DEFINE_func_80172958()  /* dedup: shared engine-core @0x80172958 (src/shared) */

DEFINE_func_801729A8()  /* dedup: shared engine-core @0x801729A8 (src/shared) */

DEFINE_func_801729B0()  /* dedup: shared engine-core @0x801729B0 (src/shared) */



s32 func_801729F0(void *a0) {

    extern void (*D_801827B4[])(void);
    D_801827B4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172A2C()  /* dedup: shared engine-core @0x80172A2C (src/shared) */

DEFINE_func_80172A8C()  /* dedup: shared engine-core @0x80172A8C (src/shared) */

DEFINE_func_80172ACC()  /* dedup: shared engine-core @0x80172ACC (src/shared) */

DEFINE_func_80172B0C()  /* dedup: shared engine-core @0x80172B0C (src/shared) */

DEFINE_func_80172B14()  /* dedup: shared engine-core @0x80172B14 (src/shared) */



s32 func_80172B44(void *a0) {

    extern void (*D_801827C4[])(void);
    D_801827C4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172B80()  /* dedup: shared engine-core @0x80172B80 (src/shared) */

DEFINE_func_80172BC8()  /* dedup: shared engine-core @0x80172BC8 (src/shared) */

DEFINE_func_80172C48()  /* dedup: shared engine-core @0x80172C48 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_80172C50);


extern void (*D_801827D0[])(void);

void func_80172CA0(void *a0) {
    D_801827D0[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172CDC()  /* dedup: shared engine-core @0x80172CDC (src/shared) */

DEFINE_func_80172D14()  /* dedup: shared engine-core @0x80172D14 (src/shared) */

DEFINE_func_80172D60()  /* dedup: shared engine-core @0x80172D60 (src/shared) */

DEFINE_func_80172D68()  /* dedup: shared engine-core @0x80172D68 (src/shared) */



s32 func_80172DAC(void *a0) {

    extern void (*D_801827DC[])(void);
    D_801827DC[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_80172DE8()  /* dedup: shared engine-core @0x80172DE8 (src/shared) */

DEFINE_func_80172E20()  /* dedup: shared engine-core @0x80172E20 (src/shared) */

DEFINE_func_80172E8C()  /* dedup: shared engine-core @0x80172E8C (src/shared) */

DEFINE_func_80172E94()  /* dedup: shared engine-core @0x80172E94 (src/shared) */

DEFINE_func_80172ED4()  /* dedup: shared engine-core @0x80172ED4 (src/shared) */

DEFINE_func_80172EFC()  /* dedup: shared engine-core @0x80172EFC (src/shared) */

DEFINE_func_80172F24()  /* dedup: shared engine-core @0x80172F24 (src/shared) */

DEFINE_func_80172F4C()  /* dedup: shared engine-core @0x80172F4C (src/shared) */

DEFINE_func_80172F9C()  /* dedup: shared engine-core @0x80172F9C (src/shared) */

DEFINE_func_80172FEC()  /* dedup: shared engine-core @0x80172FEC (src/shared) */

DEFINE_func_8017303C()  /* dedup: shared engine-core @0x8017303C (src/shared) */



s32 func_80173078(void *a0) {

    extern void (*D_801827E8[])(void);
    D_801827E8[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801730B4()  /* dedup: shared engine-core @0x801730B4 (src/shared) */

DEFINE_func_801730FC()  /* dedup: shared engine-core @0x801730FC (src/shared) */

DEFINE_func_8017316C()  /* dedup: shared engine-core @0x8017316C (src/shared) */

DEFINE_func_80173174()  /* dedup: shared engine-core @0x80173174 (src/shared) */



s32 func_8017319C(void *a0) {

    extern void (*D_801827F4[])(void);
    D_801827F4[*(u8 *)((s32)a0 + 0x214)]();
}


DEFINE_func_801731D8()  /* dedup: shared engine-core @0x801731D8 (src/shared) */


extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
extern M2C_UNK D_80182794;

void func_80173220(void * arg0)
{
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x4000) {
        func_80147324(0x516);
        func_80019064(&D_80182794);
    }
    if (M2C_FIELD(arg0, u16 *, 0xB8) & 0x8000) {
        func_80171A1C(arg0);
        func_80174650(arg0);
    }
}


DEFINE_func_80173294()  /* dedup: shared engine-core @0x80173294 (src/shared) */

DEFINE_func_8017329C()  /* dedup: shared engine-core @0x8017329C (src/shared) */

DEFINE_func_801732C4()  /* dedup: shared engine-core @0x801732C4 (src/shared) */

DEFINE_func_801732F4()  /* dedup: shared engine-core @0x801732F4 (src/shared) */

DEFINE_func_8017331C()  /* dedup: shared engine-core @0x8017331C (src/shared) */

DEFINE_func_8017334C()  /* dedup: shared engine-core @0x8017334C (src/shared) */

DEFINE_func_80173374()  /* dedup: shared engine-core @0x80173374 (src/shared) */

DEFINE_func_801733A4()  /* dedup: shared engine-core @0x801733A4 (src/shared) */

DEFINE_func_801733CC()  /* dedup: shared engine-core @0x801733CC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_004/nonmatchings/ov_SC01_004_jr_8016AB6C", func_801733FC);

DEFINE_func_80173460()  /* dedup: shared engine-core @0x80173460 (src/shared) */

