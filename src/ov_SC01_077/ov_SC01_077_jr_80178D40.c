#include "common.h"
#include "../shared/engine_core.h"

/* ==== Phase-17 canonical-sig layer (tools/derive_canonical_sigs.py) ===================
 * ONE byte-neutral canonical signature per undeclared-stub conflict callee, so the parallel
 * hand-matching wave declares each shared callee consistently and the one-big-TU build stops
 * failing on `conflicting types` (hand-matching-process.md §7c). Form: s32 return (void->s32
 * byte-neutral, §3a-1) + s32 params (matched bodies cast int->ptr), arity from Ghidra-C + asm
 * read-before-write $a0-$a3 (agree on all 14 cached; 6 stubs call-site-validated). LOCAL to
 * this TU on purpose (reach-1 names like func_801809BC differ across overlays, so NOT in the
 * shared engine_core.h). Whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9). */
extern s32 func_8016EC0C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012B4B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3); /* derive-decl, arity 4 */
extern s32 func_80169A4C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8016A8FC(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8012B8E4(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8015E1B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015EE08(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015F7D4(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80160B34(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80165140(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80161CD0(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_80175268(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8017EC7C(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801809BC(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012DE2C(s32 a0);                        /* derive-decl, arity 1 */
extern s32 func_8012DDA4(void);                          /* derive-decl, arity 0 */
extern s32 func_801759D8(void);                          /* derive-decl, arity 0 */
extern s32 func_80175820(void);                          /* derive-decl, arity 0 */
extern s32 func_801758FC(void);                          /* derive-decl, arity 0 */
/* ==== end canonical-sig layer ==================================================== */
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
struct S;
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
struct Obj;
typedef struct {
    u16 f0;
    u8 pad0[0x4e];
    int f50;
    u8 pad1[0x14];
} Ent_80164930;
typedef struct { u8 d[8]; } __attribute__((packed, aligned(1))) B8_80165140;
typedef struct { u8 d[4]; } __attribute__((packed, aligned(1))) B4;
typedef struct { B8_80165140 a; B4 b; s32 used; } Slot;
typedef struct { u16 h[6]; } Rec_80166690;   /* 12-byte sub-table record (stride 0xC) */
typedef struct {
    short v0, v1, v2, pad06, w0, w1, w2, pad0E;          /* 0x00..0x0F */
    short v3, v4, v5, pad16, w3, w4, w5, pad1E;          /* 0x10..0x1F */
    u8 c00, c01, c02, pad23;                             /* 0x20 */
    u8 c10, c11, c12, pad27;                             /* 0x24 */
    u8 c20, c21, c22, pad2B;                             /* 0x28 */
    u8 c30, c31, c32, pad2F;                             /* 0x2C */
    int tag;                                             /* 0x30 -> struct size 0x34; tag lands at sp+0x40 */
} Frame_80166690;
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
struct Fr {
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
} Thing_80168828;
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
typedef struct { char b[4]; } W;
typedef struct { s16 x, y, z; } Vec3_8016BFD0;
typedef struct {
    s16 m[9];    /* 0x00 */
    s16 pad;     /* 0x12 */
    s32 t[3];    /* 0x14, 0x18, 0x1c */
    s32 rest[8]; /* 0x20..0x3f */
} Mtx;
typedef struct {
    u8 f0, f1, f2, f3;
    struct { s16 a, b, c, d, e, g; } ent[16];
} Blk_8016CF04;                /* 4 + 16*12 = 0xC4 stride */
typedef struct {
    u16 x, y, z, xpad;      /* 0x00 : in  -> sp+0x20 */
    u16 vx, vy, vz, vpad;   /* 0x08 : out -> sp+0x28 */
} Work8016;
typedef struct { s32 w[8]; } Blk20_8016DF5C;
typedef struct { short vx, vy, vz, pad; } SVECTOR;                 /* 0x08 */
typedef struct { short m[3][3]; short pad; s32 t[3]; } MATRIX;     /* 0x20 */
typedef struct {
    SVECTOR v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;
struct Entry {
    u8 f0;
    u8 f1;
    u8 pad[0x1e];
};
typedef void (*Handler)(struct Entry *);
typedef struct {
    /* 0x00 */ s8  head[0x14];
    /* 0x14 */ s32 f14;
    /* 0x18 */ s32 f18;
    /* 0x1C */ s32 f1c;
    /* 0x20 */ s16 f20;
    /* 0x22 */ s16 f22;
    /* 0x24 */ s16 f24;
    /* 0x26 */ s16 pad26;
    /* 0x28 */ s16 f28;
    /* 0x2A */ s16 f2a;
    /* 0x2C */ s16 f2c;
} Buf;
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80189054;
extern u8 D_80188FC4;
extern u8 D_80188FA0;
extern u8 D_80188F7C;
extern u8 D_80189030;
extern u8 D_8018900C;
extern u8 D_80188FE8;
extern u8 D_80188F58;
extern void func_80145934(void);
extern u8 D_801890E4;
extern u8 D_801890C0;
extern u8 D_8018909C;
extern u8 D_80189078;
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
extern unsigned char D_801884DC[];
extern unsigned char D_8018850C[];
extern unsigned char D_8018855C[];
extern unsigned char D_8018858C[];
extern unsigned char D_801885BC[];
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
extern void (*D_8018860C[])(void *);
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
extern s32 D_801151D4;
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
extern u8 D_80126C01;
extern u16 D_80126C02;
extern u16 D_80126C06;
extern s32 D_80188654[];
extern s32 func_80148D44(void);
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
extern s32 D_801886D4[];
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
extern u8 D_8018875C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80188764;
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
s32 func_80135888(s32, s32, M2C_UNK, M2C_UNK);      /* extern */
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
extern int D_801D9618;
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
extern s32 D_801D961C;
extern void func_8014FA04(s32 a0);
extern int func_8014FBC0(void);
extern s32 func_8014FC18(u8 *self);
extern int func_8014FD54(int param_1);
extern void func_8014FCFC(void);
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
extern s32 D_80188794;
extern s32 D_80126990;
extern s32 D_80126994;
extern u8 D_80126948[];
extern s32 func_80021174(s32 a0, s32 a1);
extern s32 func_8015094C(s32 param_1);
extern void (*D_80188798[])(void);
extern void func_80150B28(int param_1);
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
extern void (*D_8018883C[])(void *);
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
extern void (*D_80188860[])(void *);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80188850;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80188874[])(void *);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80188880[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80188890[])(void *);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801888A8[])(void *);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80188898;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801888BC[])(void *);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801888D8[])(void *);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801888C8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801888EC[])(void *);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80188900[])(void *);
extern void func_80153320(void *a0);
extern void func_801533A4(s32 a0);
extern void func_8015335C(s32 a0);
extern void func_80153410(s32 *a0);
extern void func_80153490(s32 a0);
extern void func_80153550(s32 a0);
extern void func_801534D8(s32 *a0);
void func_8014ED28(s32 a0);
void func_80146D90(s32 a0);
void func_8014CC28(s32 a0);
void func_8014FA04(s32 a0);
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
extern s32 D_80188914;
extern void (*D_8018893C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018891C;
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
void func_80154C24(s32 a0, s32 *a1, s32 *a2);
void func_80154F9C(s32 a0);
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
extern int (*D_80188988[])(void);
extern s32 func_80155458(s32 param_1);
s32 func_800D02D0(u8);                              /* extern */
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018898C[])(void *);
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
extern s32 func_80161208(void);
void func_80155E30(void *a0);
extern void func_80155E30(void *a0);
extern s32 func_80161208();
extern void func_80155EA4(void *arg0);
extern void func_80155F58(void);
extern s32 func_80155F80();
extern s32 func_80155F60(void);
extern s32 func_80155F80(s32 a0);
extern int func_80155FB0(int arg, int a1);
extern int func_80155FD4(int arg, int a1);
extern void func_80156044(int param_1, int param_2);
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
extern void func_80013E94(void *a0, void *a1);
extern void func_80156A1C(s32 a0, s32 a1);
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern unsigned char D_8011520C[];
extern unsigned short D_80188DF0[];
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
extern void (*D_80188E00[])(void *);
extern void func_8014CC28(s32 a0);      /* defined  */
extern void func_8014F3E8(s32 a0);      /* declared */
extern void func_8015BDD0(s32 *a0);     /* defined  */
extern void func_801575E4(void *a0);    /* defined  */
extern void func_80157580(s32 arg0);
extern u8 D_800D4F14[];
extern void func_801599A4(void *a0);   /* canonical: void(*)(void *) */
extern void func_80159B3C(void *a0);   /* canonical: void(*)(void *) */
extern s32 func_80161208(void);        /* canonical: s32(*)(void) — call-site cast to pass arg0 */
extern void func_801576A8(void *arg0);
extern s32 func_8015773C(u8 *a0);
extern s32 func_8015771C(u8 *a0);
extern s32 func_8015773C(u8 * arg0);
extern int D_801D9650;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80188E28[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80188E08;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80188E18;
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
extern void (*D_80188E68[])(void *);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80188E70[])(void *);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80188E3C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80188E7C[])(void *);
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
extern u8 D_80188E4C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801D9658;
extern s32 D_801D9664;
extern s32 D_801D9668;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80188EB8[])(s32 *);
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
extern s32 D_80188E8C[];
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
extern s32 D_801D9660;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80189108[])(void *);
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
extern char D_80188F28[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_801891AC[])(void *);
extern void (*D_801891B8[])(void *);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80189300[])(void *);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018911C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80189308[])(void *);
extern void func_8015A2A0(s32 a0);
extern int D_8018912C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018914C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80189310[])(void *);
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
extern void (*D_8018932C[])(void);
extern s32 func_8015BE74(void);
extern void func_80161124(void *a0);
extern s32 func_8015BE94(s32 *a0);
extern s32 func_8015AE2C(void);
extern s32 func_8015BEC4(void);
extern s32 func_8015B950(void);
extern s32 func_8015BEE4(void);
extern void func_8015BF04(s32 *a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015BFF4(void *a0);
extern void func_8015BF7C(s32 *a0);
extern void func_8015C030(s32 *a0, s32 a1);
extern void func_8015BFB0(s32 *a0, s32 a1);
extern void (*D_80189338[])(void *);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80189344[])(void *);
extern void func_8015C788(s32);
extern void func_8015C750(s32 a0);
extern void func_80161240(void *a0);
extern void func_80161C24(s32, s32);
extern void (*D_801891B8[])();
extern void func_8015C944(int param_1);
extern void func_8015CB94(s32 a0);
extern void func_8015CBCC(void);
extern void func_8015CBD4(void);
extern void func_8015CBDC(void);
extern void func_8015CBE4(void);
extern void func_8015CBEC(void);
extern void func_8015CBF4(void);
extern void func_8015CBFC(void);
extern void func_8015CC04(void);
void func_80147078(s32 *a0, s16 a1);
s32 func_8015CCD0();
extern void func_8015CC0C(s32 *param_1);
extern void func_8015CC74(s32 *a0);
extern void func_8015CC40(s32 *a0);
extern void (*D_80189354[])(void);
extern void func_8015CC74(s32 * a0);
extern s32 func_8015CCD0();
extern s32 func_8015CCB0(void);
extern s32 func_801725E0(u8 *a0);
extern s32 func_8015CCD0(s32 param_1);
extern void func_8015CF24(s32 a0);
extern void func_8015D01C();
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0(s32 *a0);
extern void func_8015CF8C(s32 *a0);
extern void (*D_8018938C[])(void);
extern void func_8015CFC0(s32 * a0);
extern void func_8015CFFC(void);
extern void func_8015D01C(int param_1);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801893E8;
extern void func_8015D380(s32 a0);
extern unsigned char D_801884CC[];
extern void func_8015D414(int param_1);
extern void func_8015D57C(s32);
extern void func_8015D480(s32 *a0);
extern s32 func_8015D4E8(s16 *a0);
extern void func_8015D4B4(s16 *a0);
extern s32 (*D_801893F0[])();
extern void func_8015D524(s32 arg0);
extern void func_8015D544(s32 a0);
extern void func_801746DC(void);
extern void func_8015D57C(s32 arg0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80154150(int, int);
extern void func_80149374(int, int);
extern unsigned char D_801893FC[];
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
extern s8 D_80189438[];
extern void func_8015DCB8(s32 param_1);
s32 func_80029AAC();
extern int func_8015DD74(int arg0);
extern void func_8015DECC(s32 a0);
extern void func_8015DDF0(s32 *a0);
extern void func_8015DE58(s32 *a0);
extern void (*D_80189450[])(void);
extern void func_8015DE58(s32 * param_1);
extern void func_8015DECC(s32);
extern void func_8015DE94(s32 a0);
extern void func_8015E018(s32 a0);
extern void func_8015DF34(void *arg0);
extern int func_8015DFE4(int a0);
extern void func_8015E018(s32 param_1);
void func_8014C1A0(s32 arg0, s32 arg1);
void func_80015978(s32 a0, s32 *a1);
s32 func_80029AAC(void);
void func_8014C4AC(s32 a0, s32 a1, s32 a2, s16 *a3, s32 a4);
extern int func_8015E0D4(int a0);
extern void func_8015E22C(s32 a0);
extern void func_8015E150(s32 *a0);
extern s32 func_8015E1B8(s32 a0);
extern void func_8015E184(s32 *arg0);
extern void (*D_80189470[])(void);
extern s32 func_8015E1B8(s32 param_1);
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
extern u16 D_80189480;
extern u16 D_80189482;
extern u16 D_80189484;
extern s32 D_80189488;
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80189490;
extern void func_8015E5B0(u8 *self);
extern void func_8015E714(s32 *a0);
extern void func_8015E95C(s32);
extern void func_8015E84C(s32 *a0);
extern void func_8015E8E8(s32 *a0);
extern void func_8015E9B8(s32 *a0);
extern void func_8015E8B4(s32 *a0);
extern void (*D_801894A4[])(void);
extern void func_8015E8E8(s32 * param_1);
extern void func_8015E924(s32 a0);
extern void func_8015E95C(s32 a0);
extern s16 D_801152A0;
extern void func_80160818(s32 *a0);
extern void func_8015ED6C(s32 *a0);
extern void func_8015EE7C(s32);
extern void func_8015EDA0(s32 *a0);
extern s32 func_8015EE08(s32 a0);
extern void func_8015EDD4(s32 *arg0);
extern void (*D_801894AC[])(void);
extern void func_8015EE44(s32 a0);
extern int D_800D4C48;
extern int D_8018919C;
extern void func_8015EE7C(s32 param_1);
extern void func_8015EEE0(void *arg0);
extern void func_8015EF9C(void);
extern void func_8015F080(s32);
extern void func_8015EFA4(s32 *a0);
extern void func_8015F00C(s32 *a0);
extern void func_8015EFD8(s32 *a0);
extern void (*D_801894B4[])(void);
extern void func_8015F00C(s32 * param_1);
extern void func_8015F048(s32 a0);
extern void func_8015F080(s32 a0);
extern s32 D_80062BE8;
extern void func_8015F118(void *a0);
extern void func_8015F260(s32 *a0);
extern void func_8015F380();
extern void func_8015F2BC(s32 *a0);
extern void func_8015F324(s32 *a0);
extern void func_8015F2F0(s32 *a0);
extern void (*D_801894BC[])(void);
extern void func_8015F324(s32 * a0);
extern void func_8015F360(void);
extern s32 func_801725B8(u8 *a0);
extern void func_8015F380(void* arg0);
extern void func_8015F738(s32 *a0);
extern void func_8015F848(s32 *a0);
extern void func_8015F76C(s32 *a0);
extern s32 func_8015F7D4(s32 a0);
extern void func_8015F7A0(s32 *arg0);
extern void (*D_801894F4[])(void);
extern s32 func_8015F7D4(s32 param_1);
extern void func_8015F810(s32 *a0);
extern void func_801466F0(s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern void func_8015F89C(void *arg0);
void func_80154150(s32 a0, s32 a1);
void func_80154A74(s32 a0, s32 a1);
void func_80146C98(s32 *a0, s16 a1);
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
extern unsigned int D_80189514[];
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
extern void (*D_80189590[])(void *);
extern void func_80160138(s32 * a0);
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
extern void (*D_801895A8[])(void *);
extern void func_8016084C(s32 * a0);
extern void func_80160888(s32 *a0);
extern void func_80160A28(s32 a0);
extern void func_80160A74(s32 *a0);
extern void func_80160BB4(s32 *a0);
extern void func_80160ACC(s32 *a0);
extern s32 func_80160B34(s32 a0);
extern void func_80160B00(s32 *arg0);
extern void (*D_801895B4[])(void);
extern void func_80160B70(s32 a0);
extern void func_80160C28(void *arg0);
extern void func_80160CB4(s32 *a0);
extern void func_80160D10(void *arg0);
extern void func_80160DEC(u8 *a0);
extern void func_80160F00();
extern void func_80160E3C(s32 *a0);
extern void func_80160EA4();
extern void func_80160E70(s32 *a0);
extern void func_80160EA4(int param_1);
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
extern u16 D_801895F4[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80189658;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801D9670[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018967C[])(void);
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
extern int D_801D96C8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern s32 D_8011F750;               /* canonical: engine_core.h `extern s32 D_8011F750;` (read here as a byte) */
extern void (*D_801896C0[])(void);   /* word-stride table of dispatch fn pointers */
extern void func_801627E8(void);
extern void (*D_801896C4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801896B4;
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
extern char D_801D8BB0[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801896CC[])(void);
extern void func_80163A58(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 D_800DE5A0;
extern s32 D_800636C8;
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
extern void (*D_80189720[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801896E8;
extern u16 D_8018971C;
extern s16 D_8018971A;
extern s16 D_80189718;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018972C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801D9728;
extern u8 D_801D9729;
extern u8 D_801D972A;
extern u8 D_801D972B;
extern u8 D_801D972C;
extern u8 D_801D972D;
extern u8 D_801D972E;
extern u8 D_801D972F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern s32 (*D_8018973C[])();
extern s32 func_80164EA4(s16 *a0);
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
extern s32 D_801D9768;
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
extern void (*D_80189780[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801897FC[];
extern s32 D_8018981C[];
extern u8 D_80189898[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801898B8[];
extern u8 D_801898D8[];
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
extern s32 (*D_801898F8[])();
extern void func_80165A18(void);
extern s32 func_80165A50(s32 _arg0);
extern void func_80165AC8(void);
extern void func_80165A78(s32 arg0);
extern void (*D_80189974[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801899F0[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern s32 D_80126728;
extern void func_80165CA0(void);
M2C_UNK func_8001534C(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_801D8BC0;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern s32 (*D_801899FC[])();
extern s32 func_80166018(s16 *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern s32 (*D_80189A04[])();
extern s32 func_801663FC(s16 *a0);
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
extern s32 (*D_80189ACC[])();
extern s32 func_80166618(s16 *a0);
extern s32 (*D_80189ADC[])();
extern s32 func_80166654(s16 *a0);
extern s32 func_80017758(void *a0, void *a1);
extern u8 D_801D97E8[];
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern void func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern s32 (*D_80189AEC[])();
extern s32 func_801678B4(s16 *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern s32 (*D_80189AF8[])();
extern s32 func_80167A9C(s16 *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80189A58[];
extern u8   D_80189A6C[];
extern s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
extern void func_80166F58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_80189AB0[];
extern u8 D_80189A80[];
extern u8 D_80189A81[];
extern void func_801681FC(s32 param_1);
extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8016829C(s32 a0);
extern s32 func_80166690(s32 a0, s32 a1);
extern void func_80168328(s32 arg0);
s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_80166690(s32 a0, s32 a1);
extern void func_801683D8(s32 a0);
extern u8 D_80189ABC[];
extern u8 D_80189A94[];
extern u8 D_80189A95[];
extern void func_80168430(s32 param_1);
extern void func_801684B4(s32 a0);
extern void func_80168540(s32 a0);
extern void func_801685EC(s32 a0);
extern void func_80168640(s32 a0);
extern s32  RotMatrixX(s32 a0, void *a1);
extern void func_80168664(void *arg0);
extern s32 (*D_80189B10[])();
extern s32 func_80168744(s16 *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern s32 (*D_80189B18[])();
extern s32 func_801689D8(s16 *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern s32 (*D_80189B20[])();
extern s32 func_80168AA8(s16 *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 (*D_80189B28[])();
extern s32 func_80168D58(s16 *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern s32 func_80016A5C();
extern void func_80168F40(void *arg0);
extern s32 func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80189B38[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80189B40[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80189BF4[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80189BFC[])(void);
extern void func_80169F00(void *a0);
extern char D_80189BAC[];
extern char D_80189B6C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80189C34[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80189C40[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80189C88[])(void);
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
extern void (*D_80189D04[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801D9A88;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80189CF8[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80189D3C[];
extern unsigned short D_80189D44[];
extern unsigned short D_80189D4C[];
extern unsigned char D_801D9A90[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801D9A88;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80189D54[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
M2C_UNK func_8016BF50();                            /* extern */
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801D9BC4;
extern M2C_UNK D_801D9BC8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D9B50;
extern void (*D_80189D84[])(void);
extern void func_8016C14C(void *a0);
extern void func_8016C188(s32 param);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801D9BCC[];
extern u8 D_801D9BD4[];
extern u8 D_801D9B84[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80189D8C[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80189DA8[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80189DB0[])(void);
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
extern void (*D_80189E18[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80189DBC;
extern u8 D_80189DC8;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern s16  D_801DA2C0;
extern s16  D_801DA2C4;
extern s32  D_80189E20;
extern s32  D_80189E2C;
extern s32 func_8016DC20(s32 param_1);
extern void (*D_80189E4C[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80189E54[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016DF5C(s32 param_1);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80189EA8[])(void);
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
extern u16 D_80189EDC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80189ECC[];
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
extern s32 D_80189EF8;
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
extern void (*D_80189F70[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80189F78[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80189F80[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80189F88[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80189F90[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80189F98[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80189FA4[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80189FB0[])(void);
extern void func_8016FC90(u8 *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80189FBC[])(void);
extern void func_8016FDB4(u8 *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80189FCC[])(void);
extern void func_8016FF30(u8 *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80189FDC[])(void);
extern void func_8016FFDC(u8 *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80189FE4[])(void);
extern void func_80170150(u8 *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80189FEC[])(void);
extern void func_80170240(u8 *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80189FF4[])(void);
extern void func_801702FC(u8 *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80189FFC[])(void);
extern void func_801703E0(u8 *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018A004[])(void);
extern void func_801704B0(u8 *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018A00C[])(void);
extern void func_80170548(u8 *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018A014[])(void);
extern void func_801705F8(u8 *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018A01C[])(void);
extern void func_801706AC(u8 *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018A024[])(void *);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018A02C[])(void *);
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
extern void (*D_8018A034[])(void *);
extern void func_80170B14(int a0);
void func_8014706C(void *a0);
void func_80154274(s32 *a0, s32 a1);
s32 func_80171990(u8 *a0);
void func_80170B90(u8 *a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018A03C[])(void *);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018A044[])(void *);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018A04C[])(void *);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018A054[])(void *);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018A05C[])(void *);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018A064[])(void *);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018A06C[])(void *);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018A074[])(void *);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018A07C[])(void *);
extern void func_801711C0(void *a0);
void func_801719A4(int a0, int a1);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern s32 (*D_8018A084[])(void *);
extern s32 func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern s32 (*D_8018A08C[])(void *);
extern s32 func_801714E4(void *a0);
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
extern s32  ratan2(s32 a0, s32 a1);   /* ratan2 */
extern void func_80172170(s32 a0, s32 a1);
extern s32 func_8017209C(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_801722CC(s32 *a0);
extern void func_80172304(s32 *a0);
extern void func_80172310(u8 *a0);
extern void func_801723C4(s32 param_1, s32 param_2);
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
extern s32 (*D_8018A09C[])(void *);
extern void func_80172844(u8 *a0);
extern void func_8017280C(u8 *a0);
extern void func_8017288C(void);
extern s32 func_801728E4(void *a0);
extern void func_80172894(void *a0);
extern s32 (*D_8018A0A8[])(void *);
extern void func_80172958(u8 *a0);
extern void func_80172920(u8 *a0);
extern s16 D_80126B36;
extern void func_80172958(u8 * a0);
extern void func_801729A8(void);
extern s32 func_801729F0(void *a0);
extern s16 D_80126B34;
extern s16 D_80126B32;
extern void func_801729B0(s32 a0);
extern s32 (*D_8018A0B4[])(void *);
extern void func_80172A8C(void *a0);
extern void func_80172A2C(int param_1);
extern void func_80172ACC(u8 *a0);
extern void func_80172B0C(void);
extern s32 func_80172B44(void *a0);
extern void func_80172B14(s16 a0);
extern s32 (*D_8018A0C4[])(void *);
extern s32 D_801150F8;
extern void func_80172BC8(void *a0);
extern void func_80172B80(u8 *a0);
extern void func_80172C48(void);
extern s32 (*D_8018A0D0[])(void *);
extern s32 func_80172CA0(void *a0);
extern void func_80172D14(u8 *a0);
extern void func_80172CDC(u8 *a0);
extern void func_80172D14(u8 * a0);
extern void func_80172D60(void);
extern s32 D_80127508;
extern s32 func_80172DAC(void *a0);
extern void func_80172D68(s32 a0);
extern s32 (*D_8018A0DC[])(void *);
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
extern s32 (*D_8018A0E8[])(void *);
extern void func_801730FC(struct S801730FC *a0);
extern void func_801730B4(s32 a0);
extern void func_8017316C(void);
extern s32 func_8017319C(void *a0);
extern void func_80173174(void);
extern s32 (*D_8018A0F4[])(void *);
extern u8 D_800D5AA0[];
extern void func_80173220(void *a0);
extern void func_801731D8(s32 *a0);
extern M2C_UNK D_8018A094;
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
void func_80174684(void *);
extern void func_801734BC(s32 arg0, s32 _unused1);
extern s32 (*D_8018A100[])(void *);
extern s32 func_80173544(void *a0);
extern void func_801735B8(u8 *a0);
extern void func_80173580(u8 *a0);
extern s16 D_80126B40;
extern void func_801735EC(void *a0);
extern void func_80173648(u8 *a0);
extern void func_801736A8(void);
extern s32 func_8014C118(void *a0, s32 a1, s32 a2);
extern s32 func_801736FC(void *a0);
extern void func_801736B0(s32 a0, s32 a1);
extern s32 (*D_8018A114[])(void *);
extern void func_80173770(u8 *a0);
extern void func_80173738(u8 *a0);
extern void func_801723C4(s32 a0, s32 a1);
extern void func_801737B0(void);
extern s32 func_801737E8(void *a0);
extern void func_801737B8(s16 a0);
extern s32 (*D_8018A120[])(void *);
extern void func_8017385C(u8 *a0);
extern void func_80173824(u8 *a0);
extern void func_801738D4(void);
extern s32 func_8017390C(void *a0);
extern void func_801738DC(s16 a0);
extern s32 (*D_8018A12C[])(void *);
extern void func_80173980(u8 *a0);
extern void func_80173948(u8 *a0);
extern void func_801739D8(u8 *a0);
extern void func_80173A20(void);
extern s32 D_8012750C;
extern void func_80173A60(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80173A28(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 (*D_8018A13C[])(void *);
extern s32 func_80173B4C(void *a0);
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
extern s32 (*D_8018A15C[])(void *);
extern void func_80174318(u8 *a0);
extern void func_801742E0(u8 *a0);
extern void func_80174354(void);
extern s32 func_80174384(void *a0);
extern void func_8017435C(void);
extern s32 (*D_8018A168[])(void *);
extern void func_801743F0(u8 *a0);
extern void func_801743C0(u8 *a0);
extern void func_801743F0(u8 * a0);
extern void func_80174430(void);
extern s32 func_80174474(void *a0);
extern void func_80174438(s32 a0);
extern s32 (*D_8018A174[])(void *);
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
extern s32 (*D_8018A180[])(void *);
extern s32 func_80174808(u8 *a0);
extern void func_8017481C(void);
extern s32 func_80174888(void *a0);
extern void func_80174824(void);
extern void func_8017484C(s32 a0);
extern s32 (*D_8018A188[])(void *);
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
extern s32 (*D_8018A190[])(void *);
extern s32 func_801749C8(s32);
extern s32 func_801749A8(s32 a0);
extern s16 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern s32 func_801749C8(s32 param_1);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_8018A194[])();
extern void func_80174BF4(void * arg0);
extern s32 func_80174CB0(s32, s32);
extern s32 func_80174C60(s32 a0);
extern void func_80174C80(s32 a0);
extern s32 D_8012697C;
extern u16 D_80126980;
extern s32 func_80174F28(void *a0);
extern void func_80174E9C(s32 a0);
extern void func_80174EF0(s32 a0, s16 a1);
extern s32 (*D_8018A19C[])(void *);
extern s32 func_80175014(u8 *a0, u8 *a1, s32 a2);
extern void func_80174F64(u8 *a0);
extern void func_80174FBC(u8 *a0);
extern s32 func_8017509C(u8 *a0, s32 a1, u8 *a2, u8 *a3);
extern void func_80175184(s32 *a0);
extern void func_80175114(s32 *a0);
extern void func_80175184();
extern void func_80175150(s32 *a0);
extern void (*D_8018A1A4[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018A1AC[])(s32);
extern s32 func_80175218(void * param_1);
extern s32 func_80175268(s32 param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018A314[])();
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
extern void (*D_8018A320[])(void);
extern void func_80175690(void *a0);
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
extern M2C_UNK D_801D8E08;
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
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern int D_8018A360;
extern int D_8018A36C[];
extern void func_80178840(int param_1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern int func_801789AC(void);
extern s16 D_801DAAB8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
void func_80178BF8(s32 a0, s32 a1);
void func_80178CBC(s32 a0, s32 a1);
extern void func_80178BB8(s32 a0, s32 a1);
extern void func_80178BF8(s32 _unused0, s32 _unused1);
M2C_UNK func_80178D40(s32, s32);                    /* extern */
extern s32 D_801DA308;
extern short D_801DAB2C;
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
 *  1. NO status variable. Every case stores `(*(s16*)&D_801DAB2C) = K` DIRECTLY. The shared
 *     `sh $v0, (*(s16*)&D_801DAB2C)` at .L80179AEC is a jump2 CROSS-JUMP merge of those stores:
 *     find_cross_jump's FIRST call (minimum=1, vs the code before the target label)
 *     matches that 1 insn, and because it succeeds the jump_chain loop (minimum=2) is
 *     SKIPPED -- which is what BLOCKS the deeper, wrong 3-insn merges of the identical
 *     func_80137614 tails (cases 0/0x45/0x32). reorg then steals the `li K` back into
 *     each `j` delay slot, so it looks un-merged. A `status` pseudo instead of direct
 *     stores loses that block and costs 6 insns.
 *  2. after-switch = `D_801DA308 += 8;` (.L80179AF4) -> the out-of-range default lands
 *     there with NO explicit `default:` label.
 *  3. arg0/arg1/pv are STRUCT pointers. gcc-2.7.2 sched alias (sched.c true_dependence)
 *     only lets a MEM_IN_STRUCT varying-address load hoist above a non-MEM_IN_STRUCT
 *     fixed-address store (the (*(s16*)&D_801DAB2C) store). Raw `*(T *)(int + off)` casts get
 *     MEM_IN_STRUCT_P = 0 and block that hoist -> stray nops.
 *  4. g = &D_801DAA88 stays a plain `s16 *` (NOT a struct ptr) so its varying,
 *     non-in-struct stores keep their order w.r.t. the loads.
 *  5. Statement order inside the D_801DAA88 cases is load-bearing (sched LUID/priority):
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
 * 11. CROSS-JUMP-MERGED `(*(s16*)&D_801DAB2C) = 3` (residual #2). `if (i != 10) { (*(s16*)&D_801DAB2C) = 3;
 *     break; }` lets jump2 tail-merge the `lui/sh` into the shared .L80179AEC tail and
 *     reorg steal the `li 3` into the `bne` delay slot. Storing it unconditionally
 *     BEFORE the `if` blocks the merge and costs 3 inline insns.
 *
 * 12. THE UN-COALESCED LOOP COPY (residual #3, `addu $v1,$a0,$zero` + `addiu $a0,$v1,4`).
 *     This is loop.c's NON-REPLACEABLE DEST_REG GIV, not a source-level copy (see #10:
 *     those always die). Recipe -- BOTH halves are needed:
 *       a) make the pointer an INDEX GIV: `p5c = &D_801DA764[i5c];`  (a DEST_REG giv)
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



M2C_UNK func_80178D40(s32 arg0, s32 arg1)
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
    extern s32 D_801DA30C;
    extern s32 D_801DA720;
    extern s16 D_801DA724;
    extern s16 D_801DA728;
    extern s16 D_801DA72C;
    extern s16 D_801DA730;
    extern s32 D_801DA738;
    extern s32 D_801DA73C;
    extern s32 D_801DA74C;
    extern s16 D_801DA750;
    extern s16 D_801DA754;
    extern s32 D_801DA758;
    extern s32 D_801DA760;
    extern s32 D_801DA764[10];
    extern s32 D_801DA9A8;
    extern s16 D_801DAA88;
    extern s32 D_801DAAB4;


    SV3_80178D40 v10, v18, v20, v28, v30, v38, v40, v48;
    s32 out50[2];
    SV3_80178D40 v58, v60;
    Actor_80178D40 *pv = &(*(Actor_80178D40*)&D_80126B58);
    s32 i5b, i5c, fp5b, fp5c;
    s32 *q5b, *q5c, *p5c, *r5c;
    s16 *g = &D_801DAA88;

    switch (((Cmd_80178D40 *)arg1)->op) {
    case 1:
        func_80179B28(D_801DA720);
        D_801DA720 = func_80137614(((Cmd_80178D40 *)arg1)->a.w, D_801DA72C, D_801DA730 ? 0x48 : 0x40);
        (*(s16*)&D_801DAB2C) = 2;
        break;
    case 0:
        func_80179B28(D_801DA720);
        D_801DA720 = func_80137614(((Cmd_80178D40 *)arg1)->a.w, D_801DA724, D_801DA728 ? 0x48 : 0x40);
        (*(s16*)&D_801DAB2C) = 1;
        break;
    case 0x45:
        ((void (*)(s32))((Cmd_80178D40 *)arg1)->a.w)(((Actor_80178D40 *)arg0));
        if (D_801DA9A8 != 0) {
            func_80179B28(D_801DA720);
            D_801DA720 = func_80137614(((Actor_80178D40 *)arg0)->unkDC[1], D_801DA724, D_801DA728 ? 0x48 : 0x40);
            (*(s16*)&D_801DAB2C) = 1;
        } else {
            (*(s16*)&D_801DAB2C) = 3;
        }
        break;
    case 0x32:
        func_80179B28(D_801DA720);
        D_801DA720 = func_80137614(((Actor_80178D40 *)arg0)->unkDC[((Cmd_80178D40 *)arg1)->a.w], D_801DA724,
                                   D_801DA728 ? 0x48 : 0x40);
        (*(s16*)&D_801DAB2C) = 1;
        break;
    case 2:
        func_80179B28(D_801DA720);
        if (D_801DA738 != 0) {
            D_801DA308 = D_801DA738;
            D_801DA738 = 0;
            (*(s16*)&D_801DAB2C) = 3;
            return;
        }
        (*(s16*)&D_801DAB2C) = 6;
        break;
    case 6:
        func_80179DF8();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 3:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_80179D30(&v10);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 4:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_8012F214(((Actor_80178D40 *)arg0), &v10, &v18);
        func_80179D30(&v18);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x4C:
        func_80179D78((void *)((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x4D:
        v10.vx = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f0;
        v10.vy = 0;
        v10.vz = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f4;
        func_8012F214(((Actor_80178D40 *)arg0), &v10, &v18);
        v18.pad = ((Blk_80178D40 *)((Cmd_80178D40 *)arg1)->a.p)->f6;
        func_80179D78(&v18);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x15:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_8012F214(((Actor_80178D40 *)arg0)->unkD4, &v10, &v18);
        func_80179D30(&v18);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 5:
        func_80179DCC(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 7:
        func_80179E1C(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 8:
        func_80179E74(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 9:
        v10.vx = ((Cmd_80178D40 *)arg1)->a.uh[0];
        v10.vy = 0;
        v10.vz = ((Cmd_80178D40 *)arg1)->a.uh[1];
        func_80179EA0(&v10);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0xA:
        v10.vx = ((Actor_80178D40 *)arg0)->unk6;
        v10.vy = ((Actor_80178D40 *)arg0)->unkA;
        v10.vz = ((Actor_80178D40 *)arg0)->unkE;
        func_80179EA0(&v10);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x16: {
        Actor_80178D40 *p = ((Actor_80178D40 *)arg0)->unkD4;
        v10.vx = p->unk6;
        v10.vy = p->unkA;
        v10.vz = p->unkE;
        func_80179EA0(&v10);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    }
    case 0xB:
        func_8017A0F4();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0xC:
        func_8017A11C();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0xD:
        func_8017A180();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0xE:
        func_8017A1A8();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x10:
        func_8017A1D0();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x46:
        func_8017A1F8();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x59:
        func_8017A220();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x5A:
        func_8017A248();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x49:
        func_8017A144(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x47:
        func_8017A270();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x17:
        func_80179EE8(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x18:
        func_80179F14(((Cmd_80178D40 *)arg1)->a.h[0], ((Cmd_80178D40 *)arg1)->a.h[1]);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x19:
        func_80179F6C(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x1A:
        func_80179F98(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x51:
        func_8017A040(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x1B:
        D_801DA758 = ((Cmd_80178D40 *)arg1)->a.w;
        func_80179F44();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x1C:
        func_8017A338();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x52:
        func_8017A360();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x1D:
        func_8017A388();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x3B:
        func_8017A094(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x3C:
        func_8017A0C4(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0xF:
    case 0x3F:
        (*(s16*)&D_801DAB2C) = 4;
        D_801DA30C = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x3E:
        (*(s16*)&D_801DAB2C) = 5;
        D_801DA74C = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x40:
        D_801DA74C = (s32)func_8017A3B0;
        (*(s16*)&D_801DAB2C) = 5;
        break;
    case 0x23:
        func_8012A828(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x31:
        func_8012A828(((Actor_80178D40 *)arg0), ((Actor_80178D40 *)arg0)->unkDC[((Cmd_80178D40 *)arg1)->a.w]);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x24:
        (*(s16*)&D_801DAB2C) = 3;
        ((Actor_80178D40 *)arg0)->unk20->unk12 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x25:
        g[0] = 1;
        g[2] = ((Actor_80178D40 *)arg0)->unk20->unk12 + ((Cmd_80178D40 *)arg1)->a.uh[0];
        g[1] = 0x1E;
        (*(s16*)&D_801DAB2C) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x48:
        g[0] = 1;
        g[2] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        g[1] = 0x1E;
        (*(s16*)&D_801DAB2C) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x26:
        g[0] = 1;
        g[2] = func_8012B8A4(((Actor_80178D40 *)arg0));
        g[1] = 0x1E;
        (*(s16*)&D_801DAB2C) = 3;
        g[3] = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x3D:
        ((void(*)(void *, s32))func_8012E8E0)(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x27:
        g[0] = 2;
        g[4] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_801DAB2C) = 3;
        g[1] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x4F:
        g[5] = 1;
        g[0] = 3;
        g[6] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_801DAB2C) = 3;
        g[7] = ((Actor_80178D40 *)arg0)->unkA;
        g[8] = ((Cmd_80178D40 *)arg1)->a.uh[1];
        g[1] = 0x10;
        g[3] = 4;
        /* fallthrough */
    case 0x28:
        g[5] = 0;
        g[0] = 3;
        g[6] = ((Cmd_80178D40 *)arg1)->a.uh[0];
        (*(s16*)&D_801DAB2C) = 3;
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
        (*(s16*)&D_801DAB2C) = 3;
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
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x2A:
        g[0] = 4;
        (*(s16*)&D_801DAB2C) = 3;
        g[1] = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x1E:
        func_8017B238(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x21:
        func_8017BA3C(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B238(((Actor_80178D40 *)arg0), (s32)&D_801DA73C);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x54:
        func_8017BB34(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B238(((Actor_80178D40 *)arg0), (s32)&D_801DA73C);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x1F:
        func_8017B614(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x22:
        func_8017BA3C(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B614(((Actor_80178D40 *)arg0), (s32)&D_801DA73C);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x55:
        func_8017BB34(((Actor_80178D40 *)arg0), ((Cmd_80178D40 *)arg1)->a.w);
        func_8017B614(((Actor_80178D40 *)arg0), (s32)&D_801DA73C);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x20:
        func_8017B7A8(((Actor_80178D40 *)arg0));
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x4E:
        D_801DA760 = ((Cmd_80178D40 *)arg1)->a.w;
        func_8017B940(((Actor_80178D40 *)arg0));
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x57:
        func_8017B824();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x58:
        func_8017B880();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x2B:
        (*(s16*)&D_801DAB2C) = 3;
        ((Actor_80178D40 *)arg0)->unk2 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2C:
        (*(s16*)&D_801DAB2C) = 3;
        ((Actor_80178D40 *)arg0)->unk34 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2D:
        (*(s16*)&D_801DAB2C) = 3;
        ((Actor_80178D40 *)arg0)->unkD8 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2F:
        (*(s16*)&D_801DAB2C) = 3;
        ((Actor_80178D40 *)arg0)->unk10A = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x2E:
        (*(s16*)&D_801DAB2C) = 3;
        ((Actor_80178D40 *)arg0)->unkF8 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x11:
        func_8017A298();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x12:
        func_8017A2C0();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x13:
        func_8017A2E8();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x14:
        func_8017A310();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x33: {
        void (*f)(Actor_80178D40 *) = (void (*)(Actor_80178D40 *))((Cmd_80178D40 *)arg1)->a.w;
        D_801DAAB4 = (s32)&((Cmd_80178D40 *)arg1)[1];
        f(((Actor_80178D40 *)arg0));
        (*(s16*)&D_801DAB2C) = 3;
        break;
    }
    case 0x30:
        if (((Cmd_80178D40 *)arg1)->a.w == 0) {
            func_8012E8A8(((Actor_80178D40 *)arg0));
            (*(s16*)&D_801DAB2C) = 3;
        } else {
            func_8012E88C(((Actor_80178D40 *)arg0));
            (*(s16*)&D_801DAB2C) = 3;
        }
        break;
    case 0x4A:
        ((void(*)())func_80175414)();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x4B:
        func_80175454();
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x34:
        (*(s16*)&D_801DAB2C) = 3;
        D_801DA308 = ((Cmd_80178D40 *)arg1)->a.w;
        return;
    case 0x35:
        D_801DA738 = (s32)&((Cmd_80178D40 *)arg1)[1];
        (*(s16*)&D_801DAB2C) = 3;
        D_801DA308 = ((Cmd_80178D40 *)arg1)->a.w;
        return;
    case 0x36:
        (*(s16*)&D_801DAB2C) = 3;
        D_801DA308 += 8;
        if (((s32 (*)(s32))((Cmd_80178D40 *)arg1)->a.w)(((Actor_80178D40 *)arg0)) == 0) {
            break;
        }
        D_801DA308 = *(s32 *)(D_801DA308 + 4);
        return;
    case 0x37:
        (*(s16*)&D_801DAB2C) = 3;
        D_801DA724 = ((Cmd_80178D40 *)arg1)->a.uh[0];
        D_801DA728 = ((Cmd_80178D40 *)arg1)->a.uh[1];
        break;
    case 0x38:
        (*(s16*)&D_801DAB2C) = 3;
        D_801DA72C = ((Cmd_80178D40 *)arg1)->a.uh[0];
        D_801DA730 = ((Cmd_80178D40 *)arg1)->a.uh[1];
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
        (*(s16*)&D_801DAB2C) = 3;
        D_801DA724 = w1;
        D_801DA728 = (s16)w1 >= (s16)w2;
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
        (*(s16*)&D_801DAB2C) = 3;
        D_801DA72C = w2;
        D_801DA730 = (s16)w1 < (s16)w2;
        break;
    }
    case 0x41:
        ((void(*)(s32, s32))func_8002D4C8)(((Cmd_80178D40 *)arg1)->a.uh[0], ((Cmd_80178D40 *)arg1)->a.uh[1]);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x42:
        func_8017AD0C(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x43:
        D_801DA74C = (s32)func_8017A3D8;
        D_801DA754 = 0;
        (*(s16*)&D_801DAB2C) = 5;
        D_801DA750 = ((Cmd_80178D40 *)arg1)->a.w;
        break;
    case 0x44:
        func_8001AAD0(((Cmd_80178D40 *)arg1)->a.h[0], ((Cmd_80178D40 *)arg1)->a.h[1]);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x53:
        func_80179E48(((Cmd_80178D40 *)arg1)->a.h[0]);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x56:
        func_80179FEC(((Cmd_80178D40 *)arg1)->a.w);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    L5B_found:
        fp5b = ((Cmd_80178D40 *)arg1)->a.w;
        *q5b = fp5b;
        ((void (*)(Actor_80178D40 *))fp5b)(((Actor_80178D40 *)arg0));
        (*(s16*)&D_801DAB2C) = 3;
        break;
    case 0x5B:
        i5b = 0;
        q5b = D_801DA764;
        do {
            i5b++;
            if (*q5b == 0) {
                goto L5B_found;
            }
            q5b++;
        } while (i5b < 10);
        (*(s16*)&D_801DAB2C) = 3;
        break;
    L5C_found1:
        *q5c = 0;
        goto L5C_join;
    case 0x5C:
        i5c = 0;
        if (((Cmd_80178D40 *)arg1)->a.w != 0) {
            fp5c = ((Cmd_80178D40 *)arg1)->a.w;
            q5c = D_801DA764;
            do {
                if (*q5c == fp5c) {
                    goto L5C_found1;
                }
                i5c++;
                q5c++;
            } while (i5c < 10);
        L5C_join:
            if (i5c != 10) {
                (*(s16*)&D_801DAB2C) = 3;
                break;
            }
            i5c = 0;
            do {
                p5c = &D_801DA764[i5c];
                if (*p5c != 0) {
                    goto L5C_found2;
                }
                i5c++;
            } while (i5c < 10);
            (*(s16*)&D_801DAB2C) = 3;
            break;
        L5C_found2:
            *p5c = 0;
            goto L5D;
        }
        r5c = D_801DA764;
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
        (*(s16*)&D_801DAB2C) = 3;
        break;
    default:
        break;
    }
Lend:
    D_801DA308 += 8;
}


DEFINE_func_80179B28()  /* dedup: shared engine-core @0x80179B28 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_80179B74);

DEFINE_func_80179D30()  /* dedup: shared engine-core @0x80179D30 (src/shared) */

DEFINE_func_80179D78()  /* dedup: shared engine-core @0x80179D78 (src/shared) */

DEFINE_func_80179DCC()  /* dedup: shared engine-core @0x80179DCC (src/shared) */

DEFINE_func_80179DF8()  /* dedup: shared engine-core @0x80179DF8 (src/shared) */

DEFINE_func_80179E1C()  /* dedup: shared engine-core @0x80179E1C (src/shared) */

extern void func_80179B74(s16 *a0);

void func_80179E48(s16 a0) {
    s16 sp[2];
    sp[0] = 0x1F;
    sp[1] = a0;
    func_80179B74(sp);
}

extern void func_80179B74(s16 *a0);

void func_80179E74(s16 a0) {
    s16 sp[2];
    sp[0] = 0x4;
    sp[1] = a0;
    func_80179B74(sp);
}

DEFINE_func_80179EA0()  /* dedup: shared engine-core @0x80179EA0 (src/shared) */

DEFINE_func_80179EE8()  /* dedup: shared engine-core @0x80179EE8 (src/shared) */

extern void func_80179B74(s16 *a0);

void func_80179F14(s16 a0, s16 a1) {
    s16 sp[3];
    sp[0] = 0x13;
    sp[1] = a0;
    sp[2] = a1;
    func_80179B74(sp);
}

DEFINE_func_80179F44()  /* dedup: shared engine-core @0x80179F44 (src/shared) */

DEFINE_func_80179F6C()  /* dedup: shared engine-core @0x80179F6C (src/shared) */

DEFINE_func_80179F98()  /* dedup: shared engine-core @0x80179F98 (src/shared) */

DEFINE_func_80179FEC()  /* dedup: shared engine-core @0x80179FEC (src/shared) */

DEFINE_func_8017A040()  /* dedup: shared engine-core @0x8017A040 (src/shared) */

extern void func_80179B74(s16 *a0);
extern s32 D_801DA734;

void func_8017A094(s32 arg0) {
    s16 sp10;

    D_801DA734 = arg0;
    sp10 = 0x15;
    func_80179B74(&sp10);
}

extern void func_80179B74(s16 *a0);
extern s32 D_801DA734;

void func_8017A0C4(s32 arg0) {
    s16 sp10;

    D_801DA734 = arg0;
    sp10 = 0x16;
    func_80179B74(&sp10);
}

DEFINE_func_8017A0F4()  /* dedup: shared engine-core @0x8017A0F4 (src/shared) */

DEFINE_func_8017A11C()  /* dedup: shared engine-core @0x8017A11C (src/shared) */

extern s32 D_801DA75C;
extern void func_80179B74(s16 *a0);

void func_8017A144(s32 a0) {
    s16 sp10;
    sp10 = 0x1B;
    func_80179B74(&sp10);
    D_801DA75C = a0;
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

extern s16 D_801DA718;

s32 func_8017A3B0(void) {
    switch (D_801DA718) {
    case 0:
        return 1;
    case 1:
        return 0;
    default:
        return 1;
    }
}

// @class: regalloc-order
// @stuck: none — MATCH

extern short D_801DA754;
extern short D_801DA750;

extern int func_800D0CA0(int);
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);

int func_8017A3D8(void)
{
    switch (D_801DA754) {
    case 0:
        func_800D0CA0(1);
        D_801DA754 = D_801DA754 + 1;
        return 0;
    case 100:
    {
        register int a __asm__("$4");
        a = D_801DA750;
        if (a != -1) {
            return func_8001AAA0() != 0;
        }
        return func_800D0CE0() == 1;
    }
    default:
        D_801DA754 = D_801DA754 + 1;
        if (D_801DA754 < 0x1E) {
            return 0;
        }
        D_801DA754 = 100;
        return 0;
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017A4AC);

/* canonical: resident engine call @ 0x80059A80 (engine_core.h) */
DEFINE_func_8017AD0C()  /* dedup: shared engine-core @0x8017AD0C (src/shared) */

DEFINE_func_8017ADE8()  /* dedup: shared engine-core @0x8017ADE8 (src/shared) */

DEFINE_func_8017AE08()  /* dedup: shared engine-core @0x8017AE08 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017AE2C);

// @class: plumbing
// @stuck: none — MATCH


void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_801DA794;
    extern s16 D_801DA796;
    extern s16 D_801DA798;
    extern s16 D_801DA78C;
    extern s16 D_801DA78E;
    extern s16 D_801DA790;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801DA794, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801DA796, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801DA798, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801DA78C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801DA78E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801DA790, (s32)((s16)param_2));
}


void func_8012A418(void);                           /* extern (Phase-18 reconciled) */
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_801DA71C;
extern u16 D_801DA79C;
extern u16 D_801DA79E;
extern u16 D_801DA7A0;
extern s16 D_801DAAB8;

void func_8017B1D8(void) {
    func_8012A418();
    D_801DAAB8 = 0;
    D_801DA71C = 0;
    D_801DA79C = D_80126B5E;
    D_801DA79E = D_80126B62;
    D_801DA7A0 = D_80126B66;
}

// @class: regalloc-order — simplified sibling of matched func_8017B614.
// @stuck: none. Block-moves are align-1 struct-assigns (u8[8]) -> emit_block_move
// (unaligned lwl/lwr/swl/swr), ZERO memcpy-symbol reference, so the TU's `extern memcpy`
// (which turned the old draft's memcpy into a CALL -> DIFF 64) can't drift this.
// $16 pin + in-place re-tie keeps param_2 in $a1 until the >=0xB branch, then $s0 for loads.

typedef struct { u8 b[8]; } Blk8_8017B238;

s32 func_8017B238(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018A45C[];
    extern s16 D_801DA794;
    extern s16 D_801DA78C;
    extern u8 D_8012694C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238 *)&buf[0] = *(Blk8_8017B238 *)src;
        *(Blk8_8017B238 *)&buf[8] = *(Blk8_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_8018A45C[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018A45C[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801DA794;
        s16 *p78C = &D_801DA78C;
        *(Blk8_8017B238 *)p794 = *(Blk8_8017B238 *)&buf[0];
        *(Blk8_8017B238 *)p78C = *(Blk8_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801DAAB8 = 1;
        D_801DA71C = 0;
    }
}

// @class: struct
// @stuck: none — MATCH (74 ins)

typedef struct { s16 a, b, c, d; } SV4_8017B368;      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
typedef struct { SV4_8017B368 x, y; } Pair16;         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801DA73C;
    extern SV4_8017B368 D_801DA744;
    extern s16 D_801DA794;
    extern s16 D_801DA78C;
    extern u16 D_8018A45C;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801DA73C;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801DA744;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018A45C)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018A45C)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801DA794) = loc0;
    (*(SV4_8017B368 *)&D_801DA78C) = loc1;
    D_801DAAB8 = 1;
    D_801DA71C = 0;
}


s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801DA73C;
    extern SV4_8017B368 D_801DA744;
    extern s16 D_801DA794;
    extern s16 D_801DA78C;
    extern u16 D_8018A45C;
    extern s16 D_801DA71C;
    extern s16 D_801DAAB8;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801DA73C;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801DA744;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_8018A45C)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_8018A45C)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801DA794) = loc0;
    (*(SV4_8017B368 *)&D_801DA78C) = loc1;
    D_801DAAB8 = 1;
    D_801DA71C = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801DA794).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801DA794).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801DA794).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801DA78C).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801DA78C).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801DA78C).c;
}

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
    extern u8 D_8018A45C[];
    extern s16 D_801DA794;
    extern s16 D_801DA796;
    extern s16 D_801DA798;
    extern s16 D_801DA78C;
    extern s16 D_801DA78E;
    extern s16 D_801DA790;
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
        s32 a1addr = (s32)&D_8018A45C[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_8018A45C[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801DA794;
        s16 *p78C = &D_801DA78C;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801DA796;
            v798 = D_801DA798;
            v78C = *p78C;
            v78E = D_801DA78E;
            v790 = D_801DA790;
            __asm__ __volatile__("");
            D_801DAAB8 = 1;
            D_801DA71C = 0x1E;
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
extern s16 D_801DA71C;
extern s16 D_801DA794;
extern s16 D_801DA796;
extern s16 D_801DA798;
extern s16 D_801DA78C;
extern s16 D_801DA78E;
extern s16 D_801DA790;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801DA71C = 0;
    D_801DA794 = (s16) D_80114F30;
    D_801DA796 = (s16) D_80114F34;
    D_801DA798 = (s16) D_80114F38;
    D_801DA78C = (s16) D_80114F24;
    D_801DA78E = (s16) D_80114F28;
    D_801DA790 = (s16) D_80114F2C;
}

extern s32 D_801151D4;
extern s16 D_801DA7AC;
extern s16 D_801DA7AE;
extern s16 D_801DA7B0;
extern s16 D_801DA7B4;
extern s16 D_801DA7B6;
extern s16 D_801DA7B8;

void func_8017B824(void) {
    D_801DA7AC = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801DA7AE = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801DA7B0 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801DA7B4 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801DA7B6 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801DA7B8 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}

// @class: schedule
// @stuck: none — MATCH

extern s16 D_801DA7AC;
extern s16 D_801DA7AE;
extern s16 D_801DA7B0;
extern s16 D_801DA7B4;
extern s16 D_801DA7B6;
extern s16 D_801DA7B8;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801DA7AC;
    D_80114F34 = D_801DA7AE;
    D_80114F38 = D_801DA7B0;
    D_80114F24 = D_801DA7B4;
    D_80114F28 = D_801DA7B6;
    D_80114F2C = D_801DA7B8;
}

// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801DA794), src[8..15] -> (*(S8_8017B8E8 *)&D_801DA78C) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */

typedef struct { unsigned char b[8]; } S8_8017B8E8;


s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801DA794) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801DA78C) = ((S8_8017B8E8 *)src)[1];
}


// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801DA79C;
extern u16 D_801DA79E;
extern u16 D_801DA7A0;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801DA71C;
extern short D_801DA7A4;
extern short D_801DA7A6;
extern short D_801DA7A8;
extern s16 D_801DA794;
extern s16 D_801DA796;
extern s16 D_801DA798;
extern s16 D_801DA78C;
extern s16 D_801DA78E;
extern s16 D_801DA790;

void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801DA79C);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801DA79E);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801DA7A0);
    (*(s16 *)&D_801DA7A4) = buf[0];
    (*(s16 *)&D_801DA7A6) = buf[1];
    (*(s16 *)&D_801DA7A8) = buf[2];
    D_801DA794 = D_80114F30 + buf[0];
    D_801DA71C = 0;
    D_801DA796 = D_80114F34 + buf[1];
    D_801DA798 = D_80114F38 + buf[2];
    D_801DA78C = D_80114F24 + buf[0];
    D_801DA78E = D_80114F28 + buf[1];
    D_801DA790 = D_80114F2C + buf[2];
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

extern SV4 D_801DA73C;
extern SV4 D_801DA744;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801DA744) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801DA73C = svec;

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
    D_801DA744 = buf1;
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
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801DA744)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801DA73C) = svec;

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
    (*(SV4_8017BB34*)&D_801DA744) = buf1;
}


// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801DA764[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801DA764;
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
extern s16 D_801DA71C;
extern s16 D_801DAAB8;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801DA71C = D_801DA71C + 1;
    if (D_801DA71C >= 0x1F) {
        D_801DAAB8 = 2;
    }
}

// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801DA71C;
extern s16 D_801DAAB8;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801DA71C = D_801DA71C + 1;
    if (0x18 < D_801DA71C) {
        func_8012A4BC();
        D_801DAAB8 = 0;
    }
    return;
}

// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801DA71C;
extern void (*D_801DA760)(void);
extern short D_801DA7A4;
extern short D_801DA7A6;
extern short D_801DA7A8;
extern s16 D_801DAAB8;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801DA71C = D_801DA71C + 1;
    if (D_801DA71C >= 0x19) {
        if (D_801DA760 != 0) {
            (*D_801DA760)();
        } else {
            D_80114F30 = D_80114F30 + D_801DA7A4;
            D_80114F34 = D_80114F34 + D_801DA7A6;
            D_80114F38 = D_80114F38 + D_801DA7A8;
            D_80114F24 = D_80114F24 + D_801DA7A4;
            D_80114F28 = D_80114F28 + D_801DA7A6;
            D_80114F2C = D_80114F2C + D_801DA7A8;
            func_8012A4BC();
        }
        D_801DAAB8 = 0;
    }
}

extern s32 (*D_8018A4FC[])(void *);

s32 func_8017BE60(void *a0) {
    return D_8018A4FC[*(u8 *)((s32)a0 + 0x4)](a0);
}

DEFINE_func_8017BE9C()  /* dedup: shared engine-core @0x8017BE9C (src/shared) */

DEFINE_func_8017BEA4()  /* dedup: shared engine-core @0x8017BEA4 (src/shared) */

DEFINE_func_8017BEAC()  /* dedup: shared engine-core @0x8017BEAC (src/shared) */

DEFINE_func_8017BEB4()  /* dedup: shared engine-core @0x8017BEB4 (src/shared) */

extern s32 (*D_8018A520[])(void *);

s32 func_8017BEBC(void *a0) {
    return D_8018A520[*(u16 *)((s32)a0 + 0x2)](a0);
}

// @class: schedule
// @stuck: none — MATCH (113 ins, relocation-masked). Keys: (1) one 48-byte scratch struct {in@0x00,out@0x08,dead[8]@0x10} forces frame 0x68 with in@sp+0x20/out@sp+0x28 for free; (2) SHORT loop counter (not int) defeats gcc's shift-IV strength reduction so i increments by 1 + sll/sra per use; (3) if-body store order 0x12,0x16,0x1A puts the =0 store into the w.vy load-delay slot; (4) inverted final branch (if node!=0 {...} else func_80146C3C) makes the big block fall-through (beqz).
#include "common.h"

typedef struct {
    u16 x, y, z, xpad;      /* 0x00 : in  (Pos800D20C0, padded to 8) -> sp+0x20 */
    u16 vx, vy, vz, vpad;   /* 0x08 : out (SVECTOR)                  -> sp+0x28 */
    s32 dead[8];            /* 0x10 : reserved, unaccessed           -> sp+0x30..0x4F */
} Work8017;

extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);

extern u8 D_8018A508;

void func_8017BEF8(s32 param_1) {
    s32 obj = *(s32 *)(param_1 + 0x34);
    Work8017 w;
    short i;
    s32 e;
    s32 node;

    func_80146A6C(0x11, (void *)param_1, *(s16 *)(param_1 + 6),
                  (s16)(*(u16 *)(param_1 + 0xA) - 0x10),
                  *(s16 *)(param_1 + 0xE), 0, 0);

    w.x = *(u16 *)(param_1 + 6);
    w.y = *(u16 *)(param_1 + 0xA);
    w.z = *(u16 *)(param_1 + 0xE);
    func_800D20C0(&w.x, &w.vx, 10);
    *(s16 *)(param_1 + 6) = w.x;
    *(s16 *)(param_1 + 0xE) = w.z;
    w.vy = 0;
    func_800D23D0(&w.vx);

    i = 0;
    do {
        e = func_80146A6C(0x12, (void *)param_1, *(s16 *)(obj + 6),
                          *(s16 *)(obj + 0xA), *(s16 *)(obj + 0xE), i, 0);
        if (e != 0) {
            *(s16 *)(e + 0x12) = w.vx;
            *(s16 *)(e + 0x16) = w.vy;
            *(s16 *)(e + 0x1A) = 0;
        }
        i = i + 1;
    } while (i < 3);

    node = func_800D222C(param_1, &D_8018A508, 0xFD);
    if (node != 0) {
        *(s32 *)(param_1 + 0x20) = node;
        *(u32 *)(node + 4) = *(u32 *)(node + 4) | 0x5D000100;
        ((void (*)(void *))func_8001CF30)((void *)node);
        *(s16 *)(node + 0x18) = 0x4000;
        *(s16 *)(node + 0x1A) = 0x200;
        *(s16 *)(param_1 + 0x16) = 0x200;
        *(s16 *)(param_1 + 0x14) = 0x1000;
        *(s16 *)(node + 0x28) = 0x240;
        *(s16 *)(node + 0x2A) = 0x180;
        *(s16 *)(node + 0x10) = w.vx;
        *(s16 *)(node + 0x12) = w.vy;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


DEFINE_func_8017C0BC()  /* dedup: shared engine-core @0x8017C0BC (src/shared) */

extern s32 (*D_8018A528[])(void *);

s32 func_8017C150(void *a0) {
    return D_8018A528[*(u16 *)((s32)a0 + 2)](a0);
}

// @class: plumbing
// @stuck: none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_8018A514;

void func_8017C18C(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_8018A514, 0x18);
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

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017C294);

DEFINE_func_8017C66C()  /* dedup: shared engine-core @0x8017C66C (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (126 ins)

int func_8017C710(short *param_1, short *param_2, short *param_3, int param_4) {
    register int i2o __asm__("$5");
    register int i4o __asm__("$9");
    short sVar1; int rx, rz, uVar5;
    i4o = param_2[1];
    __asm__ __volatile__("" : : "r"(i4o));
    i2o = param_1[1]; uVar5 = 0;
    if (i2o >= i4o) {
        rx = param_1[0] - i2o * (param_2[0] - param_1[0]);
        rz = param_1[2] - i2o * (param_2[2] - param_1[2]);
    } else {
        register int den __asm__("$3");
        int p2x = param_2[0], p2z = param_2[2];
        den = i2o - i4o;
        rx = p2x + i4o * (p2x - param_1[0]) / den;
        rz = p2z + i4o * (p2z - param_1[2]) / den;
    }
    if (rx >= -0x7fff) { i2o = 0x7fff; if (rx < 0x8000) i2o = rx; }
    else i2o = -0x7fff;
    *param_3 = (short)i2o;
    if (rz >= -0x7fff) { i2o = 0x7fff; if (rz < 0x8000) i2o = rz; }
    else i2o = -0x7fff;
    param_3[2] = (short)i2o; param_3[1] = 0; sVar1 = (short)param_4;
    if ((int)*param_3 < *param_1 - param_4) { uVar5 = 0xffffffff; *param_3 = *param_1 - sVar1; }
    if (*param_1 + param_4 < (int)*param_3) { uVar5 = 0xffffffff; *param_3 = *param_1 + sVar1; }
    if ((int)param_3[2] < param_1[2] - param_4) { uVar5 = 0xffffffff; param_3[2] = param_1[2] - sVar1; }
    if (param_1[2] + param_4 < (int)param_3[2]) { uVar5 = 0xffffffff; param_3[2] = param_1[2] + sVar1; }
    return uVar5;
}


DEFINE_func_8017C908()  /* dedup: shared engine-core @0x8017C908 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017C974);

extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern s32 func_8017DA08(void *a0);
extern u8 D_80126948[];
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017D840(void) {
    D_80126954 = 0x15E;
    D_8012695C = 0x258;
    D_80126968 = 0x1C2;
    D_8012696A = 0x600;
    D_8012696C = 0;
    D_80126976 = 0x140;
    D_80126978 = 0;
    D_8012697A = 0x140;
    func_8012A018(func_8017DA08, 0);
    func_8017DA08(&D_80126948);
    func_8012A094(&D_80126948);
}

extern u8 D_8012694C;

void func_8017D8DC(void) {
    D_8012694C = 1;
}

extern u8 D_8012694C;

void func_8017D8F0(void) {
    D_8012694C = 0;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017D900);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017D98C);

extern s32 (*D_8018A530[])(void *);

s32 func_8017DA08(void *a0) {
    return D_8018A530[*(u8 *)((s32)a0 + 4)](a0);
}

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8017DAEC(s32);
extern s32 *D_80126B78;

void func_8017DA44(void *arg0) {
    s32 var_v0;
    s32 var_v0_2;

    var_v0 = -func_8004787C(M2C_FIELD(D_80126B78, s16 *, 0x12));
    if (var_v0 < 0) {
        var_v0 += 0x3F;
    }
    M2C_FIELD(arg0, s16 *, 0x2E) = (s16) (var_v0 >> 6);
    var_v0_2 = -func_80047948(M2C_FIELD(D_80126B78, s16 *, 0x12));
    if (var_v0_2 < 0) {
        var_v0_2 += 0x1F;
    }
    M2C_FIELD(arg0, s16 *, 0x32) = (s16) (var_v0_2 >> 5);
    func_8017DAEC(arg0);
}

extern s32 func_8017DAEC(s32);

s32 func_8017DACC(s32 a0) {
    return func_8017DAEC(a0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017DAEC);

extern s32 (*D_8018A588[])(void *);

s32 func_8017DCB0(void *a0) {
    return D_8018A588[*(u8 *)((s32)a0 + 0x15)](a0);
}

// @class: plumbing
// @stuck: none — MATCH (simple two-call wrapper, $s0 holds param across calls by default regalloc)

extern void func_8017DE84(void *arg0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_800167B8(s32 a0);

s32 func_8017DCEC(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_8017DE84, 0x1000000);
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}

extern s32 func_800167F0(s32 a0);

s32 func_8017DD3C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}

extern s32 (*D_8018A590[])(void *);

s32 func_8017DD60(void *a0) {
    return D_8018A590[*(u8 *)((s32)a0 + 0x15)](a0);
}

// @class: plumbing
// @stuck: callee func_8016EDEC is 3-arg canonical; called 2-arg via fn-ptr cast (matches func_80174784/824 precedent)
#include "common.h"

extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_8017E0EC(void *arg0);

s32 func_8017DD9C(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_8017E0EC, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 10;
    return 0;
}

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017DDE8(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(2);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}

extern void func_800D1EBC(void);

void func_8017DE64(void) {
    func_800D1EBC();
}

extern void (*D_8018A740[])();

void func_8017DE84(void *arg0) {
    D_8018A740[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

extern void func_8016F398(void);
M2C_UNK func_8017D900();                            /* extern */

void func_8017DEC0(void *arg0) {
    func_8016F398();
    M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    func_8017D900();
}

extern void func_80171B44(s32 *a0);
M2C_UNK func_8017D98C();                            /* extern */
extern u16 D_80126980;

void func_8017DEFC(void *arg0) {
    u16 temp_v0;

    temp_v0 = D_80126980 | 0x8000;
    D_80126980 = temp_v0;
    if (temp_v0 & 0x8000) {
        func_8017D98C();
        func_80171B44(arg0);
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}

// @class: schedule
// @stuck: none — MATCH (proxy 31/31)

extern s32 func_80171B4C(s32 a0, s32 a1);
extern s32 func_800CF854(s32);
extern s32 func_8013767C(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_8014706C(void *arg0);

extern u8 D_800D5A34[];

void func_8017DF5C(int param_1)
{
    char cVar1;

    if (func_80171B4C(param_1, 0x1E) != 0) {
        if (((int (*)(void))func_800CF854)() != 0) {
            cVar1 = 4;
        } else {
            *(int *)(param_1 + 0x198) = func_8013767C(*(int *)(param_1 + 0x198));
            ((int (*)(int, int))func_80154274)(param_1, (int)&D_800D5A34);
            ((int (*)(int))func_8014706C)(param_1);
            cVar1 = *(char *)(param_1 + 0x214) + 1;
            *(short *)(param_1 + 0x20c) = 0;
        }
        *(char *)(param_1 + 0x214) = cVar1;
    }
}

// @class: other
// @stuck: none — straightforward control flow mirroring Ghidra-C; expect MATCH

extern s32 func_8016F410(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_80147060(u8 *a0);

extern unsigned char D_8018A62C[];
extern unsigned char D_8018A69C[];
extern unsigned char D_8018A6E4[];

void func_8017DFD8(int param_1) {
    if (func_8016F410(0) != 0) {
        ((void (*)(int, void *))func_80154274)(param_1, &D_8018A62C);
    }
    if (func_8016F410(1) != 0) {
        ((void (*)(int, void *))func_80154274)(param_1, &D_8018A69C);
        *(short *)(param_1 + 0x20c) = 1;
    }
    if (*(short *)(param_1 + 0x20c) == 1 && (*(unsigned short *)(param_1 + 0xb8) & 0x8000) != 0) {
        *(short *)(param_1 + 0x20c) = 2;
        ((void (*)(int, void *))func_80154274)(param_1, &D_8018A6E4);
    }
    if (func_801399F0(*(int *)(param_1 + 0x198)) != 0) {
        func_80139914(*(int *)(param_1 + 0x198));
        ((void (*)(int))func_80147060)(param_1);
        *(char *)(param_1 + 0x214) = *(char *)(param_1 + 0x214) + 1;
    }
}

// @class: plumbing
// @stuck: none — MATCH (param_1 survives across func_8016F0E4 → lands in $s0; passed to func_80165770)

extern void func_8016F0E4(void);
extern void func_80165770(void);
extern void func_80175414(s32);

void func_8017E0B4(s32 param_1)
{
    func_8016F0E4();
    ((void (*)(s32))func_80165770)(param_1);
    ((void (*)(void))func_80175414)();
}

extern void (*D_8018A754[])();

void func_8017E0EC(void *arg0) {
    D_8018A754[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

// @class: plumbing
// @stuck: none — MATCH (18/18 via match_one); a0 reused across call, sh-in-delay-slot

extern void func_80171B44(s32 *a0);
extern void func_8017E170(s32 a0);

void func_8017E128(s32 a0)
{
    *(u8 *)(a0 + 0x214) = *(u8 *)(a0 + 0x214) + 1;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = 0x800;
    func_80171B44((s32 *)a0);
    func_8017E170(a0);
}

// @class: plumbing
// @stuck: none — MATCH (expected); simple call + conditional u8 increment

extern s32 func_80171B4C(s32 a0, s32 a1);

void func_8017E170(int param_1)
{
    if (func_80171B4C(param_1, 0x1E) != 0) {
        *(unsigned char *)(param_1 + 0x214) += 1;
    }
    return;
}

extern void func_8016F0E4(void);

void func_8017E1B4(void) {
    func_8016F0E4();
}

extern void (*D_8018A760[])();

void func_8017E1D4(void *arg0) {
    D_8018A760[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

s32 func_8017E210(u8 *a0) {
    s32 v = (s32)a0[0x214] + 1;
    a0[0x214] = (u8)v;
    return v;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017E224);

// @class: schedule
// @stuck: none — MATCH. Cross-jump/tail-merge of the two `p->0x214=...` sb stores defeated by
//         reading D_8012695C into a local temp first (holds $a0, forces incr into $v1 not $v0).
#include "common.h"

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern s32 func_8013767C(s32 a0);
extern void func_8017D8DC(void);
extern u8 D_80078EC1;
extern u8 D_801B1720;
extern s32 D_8012695C;

void func_8017E298(void *arg0) {
    s16 temp_v0;
    void *temp_a0;

    temp_v0 = func_80012B04(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x12), 0x800, 4);
    temp_a0 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (((u16) M2C_FIELD(temp_a0, s16 *, 0x12) + temp_v0) & 0xFFF);
    if (temp_v0 == 0) {
        if (D_80078EC1 == 8) {
            M2C_FIELD(arg0, s32 *, 0x198) = func_8013767C((s32) &D_801B1720);
            M2C_FIELD(arg0, u8 *, 0x214) = 0xB;
        } else {
            s32 t;
            func_8017D8DC();
            t = D_8012695C;
            M2C_FIELD(arg0, s32 *, 0x204) = 0x20;
            M2C_FIELD(arg0, s32 *, 0x208) = t;
            M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
        }
    }
}

extern s32 func_8013767C(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 D_80126958;
extern s32 D_8012695C;
extern M2C_UNK D_8018A59C;
extern M2C_UNK D_801B17AC;

void func_8017E350(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x204) - 1;
    M2C_FIELD(arg0, s32 *, 0x204) = temp_v0;
    if (temp_v0 != -1) {
        temp_v0_2 = D_80126958 + 8;
        D_80126958 = temp_v0_2;
        D_8012695C = temp_v0_2;
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x204) = 0;
    M2C_FIELD(arg0, s32 *, 0x198) = func_8013767C(&D_801B17AC);
    func_80154274(arg0, &D_8018A59C);
    M2C_FIELD(arg0, u8 *, 0x4D) = (u8) (M2C_FIELD(arg0, u8 *, 0x4D) + 1);
    M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
}

// @class: plumbing
// @stuck: none — MATCH (early-exit guard + 2 calls + struct stores + cond byte incr)

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 D_8018A5E4;
extern s32 D_8012695C;

void func_8017E3EC(s32 param_1)
{
    if (func_801399F0(*(s32 *)(param_1 + 0x198)) != 0) {
        ((s32 (*)(s32))func_80139914)(*(s32 *)(param_1 + 0x198));
        ((s32 (*)(s32, s32))func_80154274)(param_1, (s32)&D_8018A5E4);
        D_8012695C = *(s32 *)(param_1 + 0x208);
        *(s32 *)(param_1 + 0x204) = 0x20;
        *(unsigned char *)(param_1 + 0x214) = *(unsigned char *)(param_1 + 0x214) + 1;
    }
}

M2C_UNK func_8017F240();                            /* extern */

void func_8017E460(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x204) - 1;
    M2C_FIELD(arg0, s32 *, 0x204) = temp_v0;
    if (temp_v0 == -1) {
        func_8017F240();
        M2C_FIELD(arg0, s32 *, 0x204) = 0x40;
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}

extern s32 func_8013767C(s32 a0);
extern M2C_UNK D_801B17F0;

void func_8017E4B4(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x204) - 1;
    M2C_FIELD(arg0, s32 *, 0x204) = temp_v0;
    if (temp_v0 == -1) {
        M2C_FIELD(arg0, u8 *, 0x4D) = (u8) (M2C_FIELD(arg0, u8 *, 0x4D) - 1);
        M2C_FIELD(arg0, s32 *, 0x198) = func_8013767C(&D_801B17F0);
        M2C_FIELD(arg0, s32 *, 0x204) = 0x20;
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern u16 D_80126970;
extern u16 D_80126974;
extern s16 D_80126976;
extern s16 D_8012697A;

void func_8017E51C(void *arg0) {
    s16 temp_v0;
    s32 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v1;
    void *temp_a0;

    temp_v0 = func_80012B04(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x12), 0x400, 4);
    temp_a0 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (((u16) M2C_FIELD(temp_a0, s16 *, 0x12) + temp_v0) & 0xFFF);
    if (temp_v0 == 0) {
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x204);
    if (((temp_v0_2 == 0) || (M2C_FIELD(arg0, s32 *, 0x204) = (s32) (temp_v0_2 - 1), temp_v0_3 = D_80126970 - 4, temp_v1 = D_80126974 - 4, D_80126970 = temp_v0_3, D_80126976 = temp_v0_3, D_80126974 = temp_v1, D_8012697A = temp_v1, (M2C_FIELD(arg0, s32 *, 0x204) == 0))) && (temp_v0 == 0)) {
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}

// @class: plumbing
// @stuck: none — MATCH expected; mirrors DEFINE_func_80160FE0 idiom (s0=a0 saved across 3 calls)
#include "common.h"

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern s32 func_8013767C(s32 a0);
extern u8 D_801B1848;

void func_8017E604(s32 a0) {
    s32 s0 = a0;
    if (func_801399F0(*(s32 *)(s0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(s0 + 0x198));
        *(s32 *)(s0 + 0x198) = func_8013767C((s32)&D_801B1848);
        *(u8 *)(s0 + 0x214) = *(u8 *)(s0 + 0x214) + 1;
    }
}

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);

void func_8017E668(u8 *a0) {
    if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(a0 + 0x198));
        *(u8 *)(a0 + 0x214) = *(u8 *)(a0 + 0x214) + 1;
    }
}

// @class: plumbing
// @stuck: none — MATCH (expected)

extern void func_8017D8F0(void);
extern void func_8016F0E4(void);
extern void func_80165770(void);

void func_8017E6BC(s32 param_1)
{
    ((void (*)(s32))func_8017D8F0)(param_1);
    ((void (*)(s32))func_8016F0E4)(param_1);
    ((void (*)(s32))func_80165770)(param_1);
}

// @class: plumbing
// @stuck: none — MATCH (simple stub; param_1 in $s0 across calls)

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_8016F0E4(void);
extern void func_80165770(void);

void func_8017E6F4(s32 param_1) {
    if (func_801399F0(*(s32 *)(param_1 + 0x198)) != 0) {
        func_80139914(*(s32 *)(param_1 + 0x198));
        ((void (*)(s32))func_8016F0E4)(param_1);
        ((void (*)(s32))func_80165770)(param_1);
    }
    return;
}

extern void (*D_8018A790[])();

void func_8017E748(void *arg0) {
    D_8018A790[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

extern s32 func_8013767C(s32 a0);
extern void func_8017D8DC(void);
extern s16 D_80126976;
extern s16 D_8012697A;
extern M2C_UNK D_801B19C0;

void func_8017E784(void *arg0) {
    func_8017D8DC();
    D_80126976 = 0;
    D_8012697A = 0;
    M2C_FIELD(arg0, s32 *, 0x198) = func_8013767C(&D_801B19C0);
    M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
}

extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);

void func_8017E7DC(u8 *a0) {
    if (func_801399F0(*(s32 *)(a0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(a0 + 0x198));
        *(u8 *)(a0 + 0x214) = *(u8 *)(a0 + 0x214) + 1;
    }
}

// @class: plumbing
// @stuck: none — MATCH (simple 3-call stub; param saved in $s0 across first call)
extern void func_8017D8F0(void);
extern void func_8016F0E4(void);
extern void func_80165770(void);

void func_8017E830(s32 param_1)
{
    ((s32 (*)(void))func_8017D8F0)();
    ((s32 (*)(s32))func_8016F0E4)(param_1);
    ((s32 (*)(s32))func_80165770)(param_1);
}

extern void (*D_8018A79C[])();

void func_8017E868(void *arg0) {
    D_8018A79C[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

// @class: schedule
// @stuck: none — MATCH (32/32). Target reloads $a0 from $s0 before the first call (filling the jal
//   delay slot with `addu $a0,$s0,$zero`); gcc otherwise keeps param_1 live in $a0 and the slot stays a
//   nop. A zero-code `__asm__ __volatile__("" ::: "$4")` clobber barrier before the call forces the reload.

extern s32 D_801270D4;
extern s32 func_80172658(s32 *a0);
extern void func_80171B44(s32 *a0);

void func_8017E8A4(u16 *param_1)
{
    s32 cVar1;

    if (1 < (u16)(*param_1 - 0x19)) {
        if (D_801270D4 < 0x1e) {
            __asm__ __volatile__("" ::: "$4");
            if (((s32 (*)(u16 *))func_80172658)(param_1) == 0) {
                return;
            }
            *(u16 *)(*(s32 *)(param_1 + 0x10) + 0x12) = 0;
            ((void (*)(u16 *))func_80171B44)(param_1);
            cVar1 = *(u8 *)(param_1 + 0x10a) + 1;
        } else {
            cVar1 = 4;
        }
        *(s8 *)(param_1 + 0x10a) = cVar1;
    }
}

// @class: loose-typing
// @stuck: none — MATCH (unsigned short store forces ori vs sign-extending li for 0xc040)

extern s32 func_80171B4C(s32 a0, s32 a1);

void func_8017E924(int param_1)
{
    if (func_80171B4C(param_1, 8) != 0) {
        *(int *)(param_1 + 0x204) = 0x20;
        *(unsigned short *)(param_1 + 0xac) = 0xc040;
        *(unsigned short *)(param_1 + 0xaa) = 0xc040;
        *(unsigned char *)(param_1 + 0x214) = *(unsigned char *)(param_1 + 0x214) + 1;
    }
    return;
}

// @class: loose-typing
// @stuck: none — MATCH (u16 store forces ori/zero-extend of 0xC040; s16 gave addiu/li -16320)

extern s32 func_80172664(s32 *a0);

void func_8017E974(s32 param_1)
{
    if (((s32 (*)(void))func_80172664)() != 0) {
        *(u16 *)(param_1 + 0xac) = 0xc040;
        *(u16 *)(param_1 + 0xaa) = 0xc040;
    } else {
        *(u8 *)(param_1 + 0x214) = *(u8 *)(param_1 + 0x214) + 1;
    }
}

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);

void func_8017E9C0(void *arg0) {
    s32 temp_v0;
    void *temp_a0;

    temp_v0 = func_80012B04(M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x12), 0x800, 4);
    temp_a0 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_a0, s16 *, 0x12) = (s16) (((u16) M2C_FIELD(temp_a0, s16 *, 0x12) + temp_v0) & 0xFFF);
    if ((temp_v0 << 0x10) == 0) {
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}

// @class: plumbing
// @stuck: none — MATCH (expected): param saved to $s0 across first call, passed to second

extern void func_8016F0E4(void);
extern void func_80165770(void);

void func_8017EA2C(int param_1)
{
    ((void (*)(int))func_8016F0E4)(param_1);
    ((void (*)(int))func_80165770)(param_1);
}

extern s32 (*D_8018A7B0[])();

s32 func_8017EA5C(s16 *a0) {
    return D_8018A7B0[(u16)a0[1]]();
}

extern void func_8012AD44(s32 *a0, s16 a1);

void func_8017EA98(s32 *a0) {
    a0[7] = 0x10;
    func_8012AD44(a0, 1);
}

// @class: other
// @stuck: none — MATCH (27 ins, byte-identical via match_one relocation-masked)
extern int rand(void);
extern void func_8017EB2C(int a, int b);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_8017EAC0(int param_1)
{
    int i;

    i = 0;
    do {
        i = i + 1;
        func_8017EB2C(rand(), *(int *)(param_1 + 0x1C));
    } while (i < 4);
    if (func_8012BEE8(param_1) == 1) {
        ((void (*)(int))func_8012C218)(param_1);
    }
}

// @class: regalloc-order
// @stuck: none — MATCH (69 ins, relocation-masked)

extern s32 D_80126B58;
extern u8 *func_8012913C(s32 a0);
extern int rand(void);

void func_8017EB2C(int param_1, int param_2)
{
    s32 base = (s32)&D_80126B58;
    u8 *p;
    s32 s1, v;
    if ((param_1 & 1) != 0) {
        p = func_8012913C(2);
    } else {
        p = func_8012913C(1);
    }
    if (p != 0) {
        int t;
        register s32 d __asm__("$5");
        register s32 r __asm__("$2");
        t = rand();
        s1 = t - (t / 256) * 256;
        r = rand() % 640;
        d = (s32)*(u16 *)(base + 0xe) - 0x140;
        __asm__("" : "=r"(d) : "0"(d));
        d += r;
        *(s16 *)(p + 0xe) = d;
        if ((param_2 & 1) != 0) {
            *(s16 *)(p + 6) = s1 + 0x7a;
            v = (s32)*(u16 *)(base + 0xa) - 0xe0;
        } else {
            *(s16 *)(p + 6) = s1 - 0xf8;
            v = (s32)*(u16 *)(base + 0xa) - 0xc0;
        }
        *(s16 *)(p + 0xa) = v;
        *(s16 *)(p + 0x36) = (s32)*(u16 *)(base + 0xa) - 0x50;
    }
}

extern s32 (*D_8018A7B8[])();

s32 func_8017EC40(s16 *a0) {
    return D_8018A7B8[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017EC7C);

extern s32 (*D_8018A7F0[])();

s32 func_8017ED4C(s16 *a0) {
    return D_8018A7F0[(u16)a0[1]]();
}

s32 rand();                                         /* extern */

void func_8017ED88(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (rand() + 0xC000);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (((rand() & 0x3FFF) * 2) - 0x4000);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) (((rand() & 0x3FFF) * 2) - 0x4000);
}

extern s32 (*D_8018A7F8[])();

s32 func_8017EDE4(s16 *a0) {
    return D_8018A7F8[(u16)a0[1]]();
}

extern s32 func_8012AD50(void *a0);

void func_8017EE20(void *a0) {
    *(s32 *)((s32)a0 + 0x1C) = 1;
    func_8012AD50(a0);
}

// @class: other
// @stuck: none — MATCH (expect clean codegen; rand result held in $s0 across 2nd rand call)
extern int rand(void);
extern void func_8017EB2C(int a, int b);
extern s32 func_8012BEE8(s32 a0);

void func_8017EE44(int param_1)
{
    int r;

    if ((*(unsigned int *)(param_1 + 0x1c) & 0xf) == 0) {
        r = rand();
        func_8017EB2C(r, *(unsigned int *)(param_1 + 0x1c) & 1);
    }
    if (func_8012BEE8(param_1) != 0) {
        *(int *)(param_1 + 0x1c) = 0x30;
        r = rand();
        func_8017EB2C(r, rand());
    }
}

// @class: plumbing
// @stuck: none — MATCH expected; base D_8018A7C0 materialized + index*0xc added as integer arg

#include "common.h"

extern s32 rand(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8017EC7C(s32 a0);
extern u8 D_8018A7C0;

void func_8017EEC0(s32 param_1) {
    s32 iVar2 = *(s32 *)(param_1 + 0x20);

    func_8001CC3C(iVar2, (rand() & 3) * 0xc + (s32)&D_8018A7C0, 0x3F0, 0x100);
    *(u8 *)(iVar2 + 0x27) = 0x9D;
    *(u16 *)(iVar2 + 0x1A) = 0x1000;
    *(u16 *)(iVar2 + 0x18) = 0x1000;
    func_8017EC7C(param_1);
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


s32 func_8017EF50(s32 param_1)
{
    extern void func_8012931C(struct vec *a0);
    extern void func_801292C8(u8 *a0);

    register unsigned short c __asm__("$5");
    register int d __asm__("$4");
    register int g __asm__("$6");
    int a;
    int e;
    ((void (*)(int))func_8012931C)(((int)param_1));
    a = *(int *)(((int)param_1) + 0x10);
    c = *(unsigned short *)(((int)param_1) + 0x34);
    e = *(int *)(((int)param_1) + 0x2c);
    __asm__ __volatile__("" : : "r"(a));
    d = *(int *)(((int)param_1) + 0x30);
    {
        unsigned short cp1 = c + 1;
        *(int *)(((int)param_1) + 0x10) = a + e;
        *(unsigned short *)(((int)param_1) + 0x34) = cp1;
    }
    *(int *)(((int)param_1) + 8) = *(int *)(((int)param_1) + 8) + 0x10000;
    *(int *)(((int)param_1) + 0x18) = *(int *)(((int)param_1) + 0x18) + d;
    g = *(short *)(((int)param_1) + 0xa);
    if (g > *(short *)(((int)param_1) + 0x36)) {
        ((void (*)(int))func_801292C8)(((int)param_1));
    } else if (*(short *)(((int)param_1) + 0x34) == 8) {
        *(int *)(((int)param_1) + 0x2c) = -*(int *)(((int)param_1) + 0x2c);
        *(int *)(((int)param_1) + 0x30) = -*(int *)(((int)param_1) + 0x30);
        *(int *)(((int)param_1) + 0x14) = -*(int *)(((int)param_1) + 0x14);
    } else if (*(short *)(((int)param_1) + 0x34) == 0x10) {
        *(short *)(((int)param_1) + 0x34) = 0;
        *(int *)(((int)param_1) + 0x14) = -*(int *)(((int)param_1) + 0x14);
    }
}


// @class: other
// @stuck: none — MATCH expected (s0=*(p+0x20) and s1=p both call-crossing; address of D_8018A7C0 materialized + (rand()&3)*0xc)

extern int rand(void);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_8017ED88(void *arg0);

extern u8 D_8018A7C0;

void func_8017F024(int param_1)
{
    s32 p;

    p = *(s32 *)(param_1 + 0x20);
    func_8001CB6C((u8 *)p, (s32)&D_8018A7C0 + (rand() & 3) * 0xc, 0x3F0, 0x100);
    *(u8 *)(p + 0x27) = 0x9D;
    *(s16 *)(p + 0x1A) = 0x1000;
    *(s16 *)(p + 0x18) = 0x1000;
    func_8017ED88((void *)param_1);
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}

struct vec;
extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);

void func_8017F0B4(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + 0x200;
    func_8012931C((struct vec *)a0);
    if (*(s16 *)(a0 + 0xA) > *(s16 *)(a0 + 0x36)) {
        func_801292C8(a0);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017F114);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017F240);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017F290);

extern s32 (*D_8018A87C[])();

s32 func_8017F3E8(s16 *a0) {
    return D_8018A87C[(u16)a0[1]]();
}

extern s32 (*D_8018A89C[])();

s32 func_8017F424(s16 *a0) {
    return D_8018A89C[(u16)a0[1]]();
}

// @class: remat
// @stuck: none — MATCH (match_one 87/87). Levers: (1) block-scoped `s32 *pCC=&D_801270CC;` INSIDE
//   the ==4 branch forces gcc to CSE/HOLD the symbol address in a reg for the load+conditional store
//   (target: lui;addiu;lw 0($v1) ... sw 0($v1)) instead of %lo-folding each access; declaring it at
//   function top materializes it too early (before the bne) — must be block-scoped so it builds lazily.
//   (2) (s16)D_80126B66 on the u16 canonical folds to lh. (3) extern short D_8018A8FC[]; D_8018A8FC[idx]
//   %lo-folds the indexed s16 load.

extern s32 D_801270CC;
extern s32 D_801270D4;
extern short D_8018A8FC[];
extern int D_8018A8F8;
extern u16 D_80126B66;

extern void func_8017F5BC(int param_1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017F460(int param_1)
{
    int iVar1;

    if (*(unsigned char *)(param_1 + 0x70) == 4) {
        s32 *pCC = &D_801270CC;
        if (*pCC == 0 && (*(unsigned short *)(param_1 + 0x5c) & 1) != 0) {
            if (D_801270D4 == 0) {
                D_801270D4 = 1;
            }
            *pCC = 3;
            *(unsigned short *)(param_1 + 0x5c) = 0;
        }
        if (1 < D_801270CC) {
            if ((*(unsigned short *)(param_1 + 0x5c) & 1) != 0 && D_801270D4 == 0) {
                D_801270D4 = 1;
            }
            if (D_8018A8FC[(int)((unsigned int)*(unsigned short *)(param_1 + 0x70) << 0x10) >> 0x18] <= D_801270D4) {
                func_8017F5BC(param_1);
                func_8002D4C8(0x495, 0);
            }
        }
    } else {
        iVar1 = (int)(s16)D_80126B66 - (int)*(short *)(param_1 + 0xe);
        if (iVar1 < 0) {
            iVar1 = -iVar1;
        }
        if (iVar1 < D_8018A8F8) {
            func_8017F5BC(param_1);
        }
    }
}

// @class: regalloc-order
// @stuck: none — MATCH (54 ins, relocation-masked)

extern s32 func_8012C51C(void *a0, s32 a1);

void func_8017F5BC(int param_1)
{
    int iVar1;
    int c70;
    register short vf4 __asm__("$3");
    register unsigned short v5c __asm__("$2");
    struct buf_8017F5BC sp;

    *(short *)(param_1 + 2) = 2;
    *(short *)(param_1 + 0x34) = 0;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
    *(int *)(param_1 + 0xe0) = 0x100000;
    *(int *)(param_1 + 0xe4) = 0x40000;
    *(int *)(param_1 + 0x1c) = 0x10;
    c70 = *(char *)(param_1 + 0x70);
    *(int *)(param_1 + 0xdc) = 0;
    v5c = *(unsigned short *)(param_1 + 0x5c) & 0x73ff;
    *(unsigned short *)(param_1 + 0x5c) = v5c;
    __asm__ __volatile__("");
    if (c70 != 4) {
        sp.f0 = *(short *)(param_1 + 6) + 0xf0;
        sp.f2 = *(short *)(param_1 + 10);
        vf4 = *(short *)(param_1 + 0xe) + 0x20;
        sp.f6 = 0x2f;
        sp.f8 = 0x600;
        sp.fa = 0;
        sp.f10 = 0;
        sp.fe = 0;
        sp.f4 = vf4;
        iVar1 = ((int (*)(int, int))func_8012C51C)((int)&sp, param_1);
        if (iVar1 != 0) {
            *(short *)(*(int *)(iVar1 + 0x20) + 0x12) =
                *(short *)(*(int *)(param_1 + 0x20) + 0x12);
        }
    }
    return;
}

extern s32 func_8012C588(s32 a0, s32 a1);

void func_8017F694(void *arg0) {
    M2C_FIELD(arg0, s16 *, 2) = 3;
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), s16 *, 0x10) = 0x400;
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 0xCC00);
    func_8012C588(0x25, 0);
}

extern s32 (*D_8018A904[])();

s32 func_8017F6D8(s16 *a0) {
    return D_8018A904[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017F714);

// @class: struct
// @stuck: none — MATCH (26 ins)

extern void (*D_8018A934[])(void);
extern s32 func_8012B4B8(s32 a0);
extern s32 func_8012C0EC(s32 *a0);

void func_8017F780(s32 *arg0) {
    D_8018A934[*(u16 *)((s32)arg0 + 2)]();
    func_8012B4B8((s32)arg0);
    if (*(u16 *)arg0 != 0) {
        ((s32 (*)(s32))func_8012C0EC)((s32)arg0);
    }
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017F7E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017FAAC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8017FD14);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", listCdBuffer);

// @class: struct
// @stuck: none — MATCH (73 ins). §18 array %lo-fold (u8 base[] + byte-offset cast) for the
//   D_8018A940/942/944 indexed halfword reads; two-pseudo (arg=iVar3) hoists `move a0,v0`
//   before the branch; dead int[4] local reserves the 0x28 frame (16 unused bytes).
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32, void *);
extern int rand(void);
extern void *D_801D20B4;
extern u8 D_8018A800[];
extern u8 D_8018A940[];
extern u8 D_8018A942[];
extern u8 D_8018A944[];

void func_801800F8(int param_1) {
    int iVar3;
    int arg;
    u16 tmp;
    int sp10[4]; /* 16-byte stack local (dead in final codegen) -> 0x28 frame */

    iVar3 = ((s32 (*)(void))func_8012C1B8)();
    arg = iVar3;
    *(int *)(param_1 + 0x20) = iVar3;
    if (iVar3 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        ((void (*)(s32, void *))func_8001C214)(arg, &D_801D20B4);
        func_8012A828(param_1, D_8018A800);
        *(u8 *)(param_1 + 0x100) = *(u8 *)(param_1 + 0x70) & 1;
        *(u16 *)(param_1 + 0xfe) = rand() & 0x3f;
        *(u16 *)(param_1 + 0xfc) = rand() & 0x3f;
        *(u16 *)(param_1 + 6) = *(u16 *)(D_8018A940 +
            ((int)((u32)*(u16 *)(param_1 + 0x70) << 16) >> 24) * 0x10 +
            *(u8 *)(param_1 + 0x100) * 8);
        *(u16 *)(param_1 + 0xa) = *(u16 *)(D_8018A942 +
            ((int)((u32)*(u16 *)(param_1 + 0x70) << 16) >> 24) * 0x10 +
            *(u8 *)(param_1 + 0x100) * 8);
        tmp = *(u16 *)(D_8018A944 +
            ((int)((u32)*(u16 *)(param_1 + 0x70) << 16) >> 24) * 0x10 +
            *(u8 *)(param_1 + 0x100) * 8);
        *(u16 *)(param_1 + 2) = 1;
        *(int *)(param_1 + 0x1c) = 0x1e;
        *(u16 *)(param_1 + 0xe) = tmp;
    }
}

extern s32 (*D_8018AA1C[])();

s32 func_8018021C(s16 *a0) {
    return D_8018AA1C[(u16)a0[1]]();
}

extern s32 (*D_8018AA24[])();

s32 func_80180258(s16 *a0) {
    return D_8018AA24[(u16)a0[1]]();
}

extern void func_8002D4C8(s32 a0, s32 a1);

void func_80180294(void *a0) {
    u16 v0 = *(u16 *)((s32)a0 + 0x2);
    *(s32 *)((s32)a0 + 0x1C) = 0x96;
    *(u16 *)((s32)a0 + 0x2) = v0 + 1;
    func_8002D4C8(0x401, 0);
}

// @class: plumbing
// @stuck: none — MATCH (simple stub: short-circuit && guard + two tail calls)

extern s32 func_8012BEE8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8017F114(void);
extern void func_8017F290(void);

void func_801802CC(s32 *param_1)
{
    if (param_1[7] != 0 && ((s32 (*)(void))func_8012BEE8)() != 0) {
        func_8002D4C8(0xD, 0x401);
    }
    func_8017F114();
    func_8017F290();
}

// @class: other
// @stuck: none — MATCH (straight reconstruction, single $s0 call-crossing local)
extern s32 func_8012CE2C(s32 a0);
extern void func_8012CBCC(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018031C(int param_1)
{
    short sVar2;

    if (((int (*)(void))func_8012CE2C)() == 0) {
        func_8012CBCC(param_1);
    }
    sVar2 = *(short *)(param_1 + 0x84) + 1;
    *(short *)(param_1 + 0x84) = sVar2;
    if ((*(short *)(param_1 + 0xdc) != *(short *)(param_1 + 6)) ||
        (*(short *)(param_1 + 0xde) != *(short *)(param_1 + 0xe))) {
        if (0xf < sVar2) {
            func_8002D4C8(0x485, 0);
            *(short *)(param_1 + 0x84) = 0;
        }
        *(short *)(param_1 + 0xdc) = *(short *)(param_1 + 6);
        *(short *)(param_1 + 0xde) = *(short *)(param_1 + 0xe);
    }
    return;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_801803B0);

// @class: regalloc-order
// @stuck: none — MATCH

extern s32 func_8012BEE8(s32 a0);
extern int func_8012D714(int, int);
extern void func_8017F694(void *arg0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern volatile unsigned short D_80126B96;

void func_8018047C(int param_1)
{
    int iVar1;

    if ((*(char *)(param_1 + 0x70) == 4) || (iVar1 = ((int (*)(void))func_8012BEE8)(), iVar1 != 0)) {
        register int sum __asm__("$3");
        sum = *(int *)(param_1 + 0xe0);
        sum += *(int *)(param_1 + 0xe4);
        *(int *)(param_1 + 0xdc) += sum;
        *(int *)(param_1 + 0xe0) = sum;
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) = *(unsigned short *)(param_1 + 0xde);
        if (0x3ff < *(short *)(param_1 + 0xde)) {
            if (*(unsigned short *)(param_1 + 0x34) == 0 &&
                (iVar1 = func_8012D714(param_1, 2), iVar1 != 0)) {
                D_80126B96 = 0x4002;
            }
            if (2 <= *(unsigned short *)(param_1 + 0x34)) {
                ((void (*)(int))func_8017F694)(param_1);
            } else {
                register int cnt __asm__("$4");
                if (*(unsigned short *)(param_1 + 0x34) == 0) {
                    func_8002D4C8(0x487, 0);
                }
                cnt = *(unsigned short *)(param_1 + 0x34) + 1;
                *(int *)(param_1 + 0xdc) = 0x4000000;
                *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) | 0xcc00;
                *(int *)(param_1 + 0xe0) = -(*(int *)(param_1 + 0xe0) >> 1);
                *(unsigned short *)(param_1 + 0x34) = cnt;
            }
        }
    }
}

void func_80180588(void) {
}

// @class: regalloc-order
// @stuck: none — MATCH (70 ins). Twin of matched func_801807B8 + 0x70==4 branching. Two §17 levers: (1) memory barrier between the 0x5c store and the *(p+0x20+0x10)=0 store stops gcc folding the if/else 0xc800 into the bne delay slot and keeps the merged value in $v0 (the missing-instruction class); (2) pin uVar3 (the D_8018A8x symbol selected by the branch, OR'd with 0x40000000 for the 0x58 store) to $v0 so the OR is `or $v0,$v0($v0=sym),$v1(const)` — natural alloc put the symbol in $v1.

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);

extern int D_801D15C4;
extern int D_801D1CBC;
extern int D_8018A8A4;
extern int D_8018A8B4;
extern int D_8018A8C4;
extern M2C_UNK D_80186E48;

void func_80180590(int param_1)
{
    int iVar2;
    register unsigned int uVar3 __asm__("$2");
    int uVar5;
    int uVar6;
    unsigned short uVar1;

    iVar2 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar2;
    if (iVar2 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        int ppuVar4;
        ppuVar4 = (int)&D_801D15C4;
        if (*(char *)(param_1 + 0x70) == 4) {
            ppuVar4 = (int)&D_801D1CBC;
        }
        ((void (*)(int, int))func_8001C214)(iVar2, ppuVar4);
        if (*(char *)(param_1 + 0x70) != 4) {
            uVar5 = 0x168;
            uVar3 = (int)&D_8018A8A4;
            uVar6 = 0x140;
        } else {
            uVar5 = 0x7fff;
            uVar6 = 0x7fff;
            uVar3 = (int)&D_8018A8B4;
        }
        *(unsigned int *)(param_1 + 0x58) = uVar3 | 0x40000000;
        func_8001D0E8(*(int *)(param_1 + 0x20), uVar5, uVar6);
        *(int *)(param_1 + 0x78) = (int)&D_8018A8C4;
        *(char *)(param_1 + 0x75) = 4;
        func_8012A828(param_1, &D_80186E48);
        *(short *)(param_1 + 2) = 1;
        if (*(char *)(param_1 + 0x70) == 4) {
            uVar1 = *(unsigned short *)(param_1 + 0x5c) | 0x8000;
        } else {
            uVar1 = 0xc800;
        }
        *(unsigned short *)(param_1 + 0x5c) = uVar1;
        __asm__ __volatile__("" ::: "memory");
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
        func_8012B2CC(param_1);
    }
}

extern s32 D_801270C8;
extern void func_8017F714(void);

void func_801806A8(void) {
    if (D_801270C8 == 1) {
        func_8017F714();
    }
}

// @class: other
// @stuck: none — MATCH (56 ins). D_80126B96 reloaded between two stores => volatile u16; signed-short*0x10 via int temp forces lh (not lhu)

extern void func_8012CC1C(s32 arg0, s32 arg1);
extern int func_8012D714(int, int);
extern void func_8002D4C8(s32 a0, s32 a1);

extern unsigned char D_8018A92C[];
extern int D_8018A924;
extern volatile unsigned short D_80126B96;

void func_801806D8(int param_1) {
    short sVar1;
    int iVar2;

    ((int (*)(int, void *))func_8012CC1C)(param_1, &D_8018A92C);
    if (*(int *)(param_1 + 0x18) < -D_8018A924) {
        *(int *)(param_1 + 0x18) = -D_8018A924;
    }
    if (0x600000 < *(int *)(param_1 + 0x14)) {
        *(int *)(param_1 + 0x14) = 0x600000;
    }
    iVar2 = *(short *)(param_1 + 0x1a) * 0x10;
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) - iVar2;
    if (func_8012D714(param_1, 1) != 0) {
        D_80126B96 = 2;
        D_80126B96 = D_80126B96 | 0x4000;
    }
    sVar1 = *(short *)(param_1 + 0x84) + 1;
    *(short *)(param_1 + 0x84) = sVar1;
    if (sVar1 < 0x10) {
        return;
    }
    func_8002D4C8(0x48a, 0);
    *(short *)(param_1 + 0x84) = 0;
}

// @class: other
// @stuck: none — straight if/else mirroring Ghidra-C; expect MATCH

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012B030(u8 *a0);
extern void func_8012A828(s32 a0, void *a1);

extern int D_801D100C;
extern unsigned char D_8018A914[];
extern M2C_UNK D_80186E48;
extern s32 D_801270C8;

void func_801807B8(int param_1) {
    int iVar1;

    iVar1 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(iVar1, &D_801D100C);
        func_8001D0E8(*(int *)(param_1 + 0x20), 0x140, 0xF0);
        *(int *)(param_1 + 0x58) = (int)&D_8018A914 | 0x40000000;
        *(short *)(param_1 + 0x5C) = 0x800;
        ((int (*)(int))func_8012B030)(param_1);
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) - 0x200000;
        *(int *)(param_1 + 0xC) = *(int *)(param_1 + 0xC) - 0x200000;
        func_8012A828(param_1, &D_80186E48);
        *(short *)(param_1 + 2) = 1;
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) = 0;
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) = 0;
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) = 0;
        D_801270C8 = 0;
    }
}

extern void func_8002D4C8(s32 a0, s32 a1);

void func_80180898(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, s16 *, 0xFC);
    if (temp_v0 != 0) {
        temp_v0_2 = temp_v0 - 1;
        M2C_FIELD(arg0, s16 *, 0xFC) = temp_v0_2;
        if ((temp_v0_2 << 0x10) == 0) {
            func_8002D4C8(0xD, 0x401);
        }
    }
}

extern void func_8002D4C8(s32 a0, s32 a1);

void func_801808DC(void *a0) {
    *(s16 *)((s32)a0 + 0x2) = 1;
    *(s16 *)((s32)a0 + 0xFC) = 0x96;
    func_8002D4C8(0x401, 0);
}

extern void func_80180930(void);

void func_80180910(void) {
    func_80180930();
}

// @class: regalloc-order
// @stuck: none — MATCH

extern u32 D_801DA9AC;
extern u16 D_8018AA2C[];
extern u16 D_801DA9E8[];
extern s32 D_8018AA4C;

extern void func_800183E0(s32 a0);

void func_80180930(void)
{
    u32 i;
    u16 *p;
    u32 base;
    u16 *tbl;

    i = 0;
    tbl = D_8018AA2C;
    base = D_801DA9AC >> 8;
    p = D_801DA9E8;
    do {
        *p = tbl[(base + i) & 0xF] | 0x8000;
        i = i + 1;
        p = p + 1;
    } while (i < 0x10);
    func_800183E0((s32)&D_8018AA4C);
    D_801DA9AC = D_801DA9AC + 0x100;
}

// @class: regalloc-order
// @stuck: none — MATCH (relocation-masked, 70 ins). pins $s0/$s1 + precomputed a0v anchored in a zero-byte barrier fix the prologue schedule.

extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32 ratan2(s32, s32);
extern void func_8012B0B4(SVEC *, s32, s32);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012ADE4(u8 *a0);

s32 func_801809BC(s32 param_1, s32 param_2)
{
    register s32 p1 __asm__("$16") = param_1;
    register s32 p2 __asm__("$17") = param_2;
    SVEC in;
    SVEC out;
    SVEC buf;
    s32 d;
    s32 ang;
    u16 px, pz;
    s32 a0v;

    a0v = p1 + 4;
    __asm__ __volatile__("" : : "r"(p2), "r"(a0v));
    if (((s32 (*)(s32, s32))func_8012BC60)(a0v, p2 + 4) >= 0x1000) {
        return 0;
    }
    ang = ratan2((s32)*(s16 *)(p1 + 0xe) - (s32)*(s16 *)(p2 + 0xe),
                 (s32)*(s16 *)(p2 + 6) - (s32)*(s16 *)(p1 + 6));
    func_8012B0B4(&buf, (ang - 0x400) & 0xfff, 0x41);
    d = *(s32 *)&buf;
    px = *(u16 *)(p2 + 6);
    out.vx = px;
    out.vy = *(u16 *)(p2 + 0xa);
    pz = *(u16 *)(p2 + 0xe);
    out.vz = pz;
    out.vx = px + d;
    out.vz = pz + (d >> 16);
    in.vx = *(u16 *)(p1 + 0x3a);
    in.vy = *(u16 *)(p1 + 0x3e);
    in.vz = *(u16 *)(p1 + 0x42);
    if ((((s32 (*)(SVEC *, SVEC *, s32))func_8012CEB0)(&in, &out, 0) & 0x2000) == 0) {
        ((void (*)(s32))func_8012ADE4)(p1);
        return 1;
    }
    *(s16 *)(p1 + 6) = out.vx;
    *(s16 *)(p1 + 0xa) = out.vy;
    *(s16 *)(p1 + 0xe) = out.vz;
    return 1;
}

// @class: struct
// @stuck: none — MATCH expected (modeled on byte-proven DEFINE_func_8012E504 idiom: D_801202A0 base, 0x6480 end, 0x10C stride for-loop)

extern u8 D_801202A0[];
extern s32 func_801809BC(s32 a0, s32 a1);
extern s32 func_8012AE00(s32 a0);

void func_80180AD4(s32 a0) {
    s32 p;
    s32 end;
    s32 v;
    v = *(u16 *)a0;
    p = (s32)D_801202A0;
    end = (s32)D_801202A0 + 0x6480;
    for (; p != end; p += 0x10C) {
        if (p != a0) {
            if (*(u16 *)p == v) {
                if (func_801809BC(a0, p) != 0) {
                    break;
                }
            }
        }
    }
    ((void (*)(s32))func_8012AE00)(p);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_80180B64);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_80180C90);

extern s16 D_8018AACC;
extern s16 D_8018AAD0;
extern u16 D_80126B5E;
extern s32 func_80013478(s32 a0, s32 a1);
extern s32 ratan2(s32, s32);
s32 func_80180F10(s32 param_1, s32 param_2) {
    s32 local_20[2] = {0x3c100, 0x51000};
    s32 iVar1;
    s32 iVar2;
    if ((s32)((u32)*(u16 *)(param_1 + 0x70) << 0x10) >> 0x18 == 4) {
        iVar1 = ((s32 (*)(s32, void *))func_80013478)(param_1 + 4, &D_8018AACC);
        if (param_2 == 1) {
            iVar2 = ratan2((s32)*(s16 *)(param_1 + 0xe) - (s32)D_8018AAD0,
                           (s32)D_8018AACC - (s32)*(s16 *)(param_1 + 6));
            if ((((u32)iVar2 - 0x400U) & 0xfff) - 0x381 < 0xff && 0x2df < (*(s16 *)&D_80126B5E) &&
                0x3c100 < iVar1) { return 1; }
        }
        if (local_20[param_2] < iVar1 && *(s32 *)(param_1 + 0xe8) < iVar1) {
            *(s32 *)(param_1 + 0xe8) = iVar1; return 1;
        }
        *(s32 *)(param_1 + 0xe8) = iVar1;
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_8018103C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_80181948);

// @class: plumbing
// @stuck: none — MATCH expected; simple param-survives-call store sequence

extern void func_8012A828(s32 a0, void *a1);
extern char D_801B0118[];

void func_80181B58(int param_1)
{
    *(short *)(param_1 + 2) = 2;
    *(short *)(param_1 + 0x34) = 0;
    func_8012A828(param_1, &D_801B0118);
    *(int *)(param_1 + 0x1c) = 0x14;
}

// @class: plumbing
// @stuck: none — MATCH expected; param_1 survives call in $s0 naturally (single global allocno)

extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801B0D50;

void func_80181B9C(s32 param_1) {
    *(s16 *)(param_1 + 2) = 2;
    *(s16 *)(param_1 + 0x34) = 3;
    func_8012A828(param_1, &D_801B0D50);
    *(s32 *)(param_1 + 0x1c) = 0x1e;
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_80181BE4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_80181F08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_jr_80178D40", func_801820DC);

void func_80182254(s32 a0) {
    *(s16 *)(a0 + 0x2) = 4;
    *(s16 *)(a0 + 0x98) = 0;
    *(s32 *)(a0 + 0x1C) = 0;
}


