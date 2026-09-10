#include "common.h"
#include "../shared/engine_prelude.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;
typedef void (*Handler)(struct Entry_8016E95C *);
typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
} SubRec_801EB5C8_8017DC38; /* 0x1C */
typedef struct {
    u16 g0;
    u16 g2;
    s32 g4;
    s32 g8;
    s32 gC;
    SubRec_801EB5C8_8017DC38 subs[16];
} GroupRec_801EB5C8_8017DC38; /* 0x1D0 */
typedef struct { s16 v[4]; } Blk8_80126940_8017E8DC;
typedef struct { s16 m[3][3]; s32 t[3]; } Mtx_8017E95C;
typedef struct { s16 vx, vy, vz, pad; } SIn_8017E95C;
typedef struct { u16 vx, vy, vz, pad; } SOut_8017E95C;
typedef struct { u16 vx, vy, vz, pad; } Ang_8017E95C;
typedef struct Sub8017EBC4 {
    /* 0x00 */ u8 pad000[0x12];
    /* 0x12 */ s16 unk_012;
} Sub8017EBC4;
typedef struct Obj8017EBC4 {
    /* 0x000 */ u8 pad000[0x02];
    /* 0x002 */ s16 unk_002;
    /* 0x004 */ u8 pad004[0x06];
    /* 0x00A */ u16 unk_00A;
    /* 0x00C */ u8 pad00C[0x10];
    /* 0x01C */ s32 unk_01C;
    /* 0x020 */ Sub8017EBC4 *unk_020;
    /* 0x024 */ u8 pad024[0x52];
    /* 0x076 */ s16 unk_076;
    /* 0x078 */ u8 pad078[0x84];
    /* 0x0FC */ s16 unk_0FC;
    /* 0x0FE */ u8 pad0FE[0x02];
    /* 0x100 */ s16 unk_100;
    /* 0x102 */ u8 pad102[0x08];
    /* 0x10A */ s16 unk_10A;
} Obj8017EBC4;
typedef struct {
    void *tag;
    s16 flag;
} Rec_80181170;
typedef struct { void *tag; s16 flag; u8 b6; u8 b7; } Rec_80181DF8;
typedef struct { char c[8]; } Blk8_801828E4;
typedef struct {
    s16 vx, vy, vz, pad;
} SVector_80182BC8;
typedef struct {
    s16 unused0;  /* 0x0 */
    s16 unused2;  /* 0x2 */
    s16 min_x;    /* 0x4 */
    s16 max_x;    /* 0x6 */
    s16 min_y;    /* 0x8 */
    s16 max_y;    /* 0xA */
    s16 min_z;    /* 0xC */
    s16 max_z;    /* 0xE */
} Box_80182BC8;
typedef struct { s16 vx, vy, vz, pad; } SVEC_80183534;
typedef struct { u16 vx, vy, vz, pad; } DVEC_80183534;
typedef struct {
    s16 vx, vy, vz, pad;
} Vec8_80183D84;
typedef struct { s16 vx, vy, vz, pad; } SVec_80184564;
typedef struct {
    s16 unused0;  /* 0x0 */
    s16 unused2;  /* 0x2 */
    s16 min_x;    /* 0x4 */
    s16 max_x;    /* 0x6 */
    s16 min_y;    /* 0x8 */
    s16 max_y;    /* 0xA */
    s16 min_z;    /* 0xC */
    s16 max_z;    /* 0xE */
} Box_80184564;
typedef struct {
    s16 vx, vy, vz, pad;
} SVec_80185214;
typedef struct {
    s16 u, v;
} UV_80185214;
typedef struct {
    SVec_80185214 v[4];  /* 0x00-0x1F */
    UV_80185214 uv[4];   /* 0x20-0x2F */
    u32 rgb[4];          /* 0x30-0x3F */
    u32 flags;           /* 0x40 */
    u8 clut;             /* 0x44 */
} Prim_80185214;
typedef struct { s16 vx, vy, vz, pad; } SV;
typedef struct { s16 vx, vy, vz, pad; } SV_801857A4;
typedef struct {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u8  r0, g0, b0, code;
    /* 0x08 */ s16 x0, y0;
    /* 0x0C */ u8  u0, v0;
    /* 0x0E */ u16 clut;
    /* 0x10 */ s16 x1, y1;
    /* 0x14 */ u8  u1, v1;
    /* 0x16 */ u16 tpage;
    /* 0x18 */ s16 x2, y2;
    /* 0x1C */ u8  u2, v2;
    /* 0x1E */ u16 pad2;
    /* 0x20 */ s16 x3, y3;
    /* 0x24 */ u8  u3, v3;
    /* 0x26 */ u16 pad3;
} FT4_801857A4; /* 0x28 */
typedef struct { s16 vx, vy; } DVec_59F4;
typedef struct { s16 vx, vy, vz, pad; } SVec_59F4;
typedef struct { s16 vx, vy, vz, pad; } SVECTOR_8018656C;
typedef struct {
    s16 vx, vy, vz, pad;
} SV_80188D90;
typedef struct {
    SV_80188D90 v[4];       /* 0x00 */
    u8          c[4][4];    /* 0x20 */
    u32         code;       /* 0x30 */
    u8          tail[0x24]; /* 0x34 */
} Prim_80188D90;            /* 0x58 */
typedef struct {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
} Pos16_8018743C;
typedef struct { s16 vx, vy, vz, pad; } SVec_80187A04;
typedef struct { s16 m[3][3]; s32 t[3]; } Mat_80187A04;
typedef struct { s32 vx, vy, vz; } Vec_80187A04;
typedef struct {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
} Node_80189244;
typedef struct {
    Node_80189244 unk00[52];   /* 0x000 .. 0x19F */
    s16 unk1A0;
    s16 unk1A2;
    s16 unk1A4;
    s16 unk1A6;
    s16 unk1A8;
    s16 unk1AA;
    s32 unk1AC;
} Obj_80189244;
typedef struct { s16 vx, vy, vz, pad; } SV_189440;
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_8018EAA0;
extern u8 D_8018EA10;
extern u8 D_8018E9EC;
extern u8 D_8018E9C8;
extern u8 D_8018EA7C;
extern u8 D_8018EA58;
extern u8 D_8018EA34;
extern u8 D_8018E9A4;
extern void func_80145934(void);
extern u8 D_8018EB30;
extern u8 D_8018EB0C;
extern u8 D_8018EAE8;
extern u8 D_8018EAC4;
extern void func_80145A2C(void);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
extern void func_80162120(void);
extern void func_80029124(s32, s32);
extern s32 func_80165A50(s32);
extern void func_80029514(s32);
extern u8 D_800AF630[];
extern u8 D_80078EC0;
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
extern unsigned char D_8018DF28[];
extern unsigned char D_8018DF58[];
extern unsigned char D_8018DFA8[];
extern unsigned char D_8018DFD8[];
extern unsigned char D_8018E008[];
extern void func_80145EE8(s32 param_1);
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_80146074(void);
extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0();
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
extern void (*D_8018E058[])(void *);
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
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80149374(s32 arg0, s32 arg1);
extern void func_801493D0(s32 param_1, s32 param_2, s32 param_3);
extern void func_8012F038(int param_1, short *param_2, short *param_3);
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
extern void func_8012E5CC(s32 param_1, u16 param_2, u16 param_3);
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
extern s32 D_8018E120[];
extern u8 D_80078E78[];
extern s32 func_80149FB0(s32 a0);
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
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
extern u8 D_8018E1A8[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018E1B0;
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
extern s32 func_8014CF04(s32 a0, s32 a1, void *a2);
extern void func_8014CD80(s32 a0, void *a1, void *a2);
extern void func_8014D0A4(s32 a0);
extern s32 func_8014D2A0(s32 a0, void *a1, void *a2);
extern s32 func_8014D12C(s32 a0, void *a1, void *a2);
extern void func_8014D438(s32 a0);
extern void func_8014D3E0(s32 _arg0);
extern void func_8014D610(s32 a0, void *a1, void *a2);
extern s32 func_8014D4C0(s32 a0, void *a1, void *a2);
extern void func_8014D790(s32 a0);
extern void func_8014D738(void);
extern s32 func_8014DD8C(s32 a0, void *a1, void *a2);
extern s32 func_8014D820(s32 a0, u16 *a1, u16 *a2);
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
extern s32 D_801150D8;
extern s16 D_801152AA;
extern u8 D_80126720[];
extern s16 D_80126724;
extern s32 func_8014EA4C(void * a0, void * a1, void * a2, s32 _arg3);
extern s32 func_8014ED80(struct SubED80 *a0);
extern int D_801DBA30;
extern void func_8014ED28(s32 _arg0);
extern s32 func_8014EE14(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014EE14(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F24C(struct SubF24C *a0);
extern void func_8014F1F4(void);
extern s32 func_8014F2E0(s32 a0, s16 *a1, s16 *a2);
extern s32 func_8014F2E0(s32 arg0, s16 * arg1, s16 * arg2);
extern s32 func_8014F4C0();
extern s32 func_8014F468(void);
extern int func_8014F74C();
extern int func_8014F6F4(void);
extern u8 D_800D3918[];
extern u8 D_801152A8[];
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern s32 D_801DBA34;
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
extern s32 D_8018E1E0;
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
extern s32 func_8014F3E8(s32 a0);
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
extern void (*D_8018E288[])(void);
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
extern void (*D_8018E2AC[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018E29C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018E2C0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018E2CC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018E2DC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018E2F4[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018E2E4;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018E308[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018E324[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018E314;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018E338[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018E34C[])(void);
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
extern s32 D_8018E360;
extern void (*D_8018E388[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018E368;
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
extern int (*D_8018E3D4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018E3D8[])(void);
extern s32 func_80161104(void);
extern void func_801555F4(void *);
extern void func_801555BC(void *a0);
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
extern s32 func_8014C568(s16 *a0, s16 *a1);
extern void func_801567BC(s32 a0);
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern unsigned char D_8011520C[];
extern unsigned short D_8018E83C[];
extern void func_80156A1C(s32 param_1, s32 param_2);
extern s32 D_801150E0[];
extern void func_80156A88(s32 a0, s32 a1);
extern void func_80156B74(s32 param_1, u32 param_2, u8 *param_3);
extern void func_80156ECC(int param_1, int param_2, int param_3, int param_4, int param_5);
extern void func_80156FA8(s16 *param_1, s16 *param_2, s16 *param_3);
extern void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern u32 func_801571C4(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801575E4(void *a0);
extern void func_801574DC(s32 *a0);
extern void func_80157544(void *a0);
extern void (*D_8018E84C[])(void);
extern void func_8014CC28(s32 a0);      /* defined  */
extern s32 func_8014F3E8(s32 a0);      /* declared */
extern void func_8015BDD0(s32 *a0);     /* defined  */
extern void func_801575E4(void *a0);    /* defined  */
extern void func_80157580(s32 arg0);
extern u8 D_800D4F14[];
extern void func_801576A8(void *arg0);
extern s32 func_8015773C(u8 *a0);
extern s32 func_8015771C(u8 *a0);
extern s32 func_8015773C(u8 * arg0);
extern int D_801DBA68;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018E874[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018E854;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018E864;
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
extern void (*D_8018E8B4[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018E8BC[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018E888;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018E8C8[])(void);
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
extern u8 D_8018E898;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801DBA70;
extern s32 D_801DBA7C;
extern s32 D_801DBA80;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018E904[])(s32 *);
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
extern s32 D_8018E8D8[];
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
extern s32 D_801DBA78;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018EB54[])(void);
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
extern char D_8018E974[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018EBF8[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018ED4C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018EB68;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018ED54[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018EB78;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018EB98;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018ED5C[])(void);
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
extern s32 func_8015B950(s32 arg0);
extern s32 func_8015BEE4(void);
extern void func_8015BF04(s32 *a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015BFF4(void *a0);
extern void func_8015BF7C(s32 *a0);
extern void func_8015C030(s32 *a0, s32 a1);
extern void func_8015BFB0(s32 *a0, s32 a1);
extern void (*D_8018ED84[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018ED90[])(void);
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
extern void (*D_8018EC04[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018EE34;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018DF18[];
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
extern unsigned char D_8018EE48[];
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
extern s8 D_8018EE84[];
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
extern u16 D_8018EECC;
extern u16 D_8018EECE;
extern u16 D_8018EED0;
extern s32 D_8018EED4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018EEDC;
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
extern int D_8018EBE8;
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
extern unsigned int D_8018EF60[];
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
extern void (*D_8018F010[])(void);
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
extern u16 D_8018F040[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018F0A4;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801DBA88[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018F0C8[])(void);
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
extern int D_801DBAE0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018F110[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018F100;
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
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u16 * a5);
extern void func_8016345C(s32 a0, u16 a1, s32 a2, u16 a3, s32 a4);
extern char D_801DB0B4[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018F118[])(void);
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
extern void (*D_8018F16C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018F134;
extern s16 D_8018F168;
extern s16 D_8018F166;
extern s16 D_8018F164;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018F178[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801DBB40;
extern u8 D_801DBB41;
extern u8 D_801DBB42;
extern u8 D_801DBB43;
extern u8 D_801DBB44;
extern u8 D_801DBB45;
extern u8 D_801DBB46;
extern u8 D_801DBB47;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018F188[])(void);
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
extern s32 D_801DBB80;
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
extern void (*D_8018F1CC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018F248[];
extern s32 D_8018F268[];
extern u8 D_8018F2E4[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018F304[];
extern u8 D_8018F324[];
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
extern void (*D_8018F3C0[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018F43C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801DB0C4;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018F448[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018F450[])(void);
extern void func_801663FC(void *a0);
extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_801665B4();
extern void func_80146C3C();
extern void func_80166438(u8 *a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_800D22E4(s32 a0);
extern void func_801665B4(s32 *a0);
extern void (*D_8018F518[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018F528[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018F538[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018F544[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018F4A4[];
extern u8   D_8018F4B8[];
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
extern void (*D_8018F55C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018F564[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018F56C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018F574[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018F57C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018F584[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018F58C[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018F640[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018F648[])(void);
extern void func_80169F00(void *a0);
extern char D_8018F5F8[];
extern char D_8018F5B8[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018F680[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018F68C[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018F6D4[])(void);
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
extern void (*D_8018F750[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801DBEA0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018F744[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018F788[];
extern unsigned short D_8018F790[];
extern unsigned short D_8018F798[];
extern unsigned char D_801DBEA8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801DBEA0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018F7A0[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801DBFDC;
extern M2C_UNK D_801DBFE0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801DBF68;
extern void (*D_8018F7D0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801DBFE4[];
extern u8 D_801DBFEC[];
extern u8 D_801DBF9C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018F7D8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018F7F4[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018F7FC[])(void);
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
extern void (*D_8018F864[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018F808;
extern u8 D_8018F814;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018F898[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018F8A0[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018F8F4[])(void);
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
extern u16 D_8018F928[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018F918[];
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
extern s32 D_8018F944;
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
extern void func_80175414(s32 _arg0);
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
extern void (*D_8018F9BC[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018F9C4[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018F9CC[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018F9D4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018F9DC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018F9E4[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018F9F0[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018F9FC[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018FA08[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018FA18[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018FA28[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018FA30[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018FA38[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018FA40[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018FA48[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018FA50[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018FA58[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018FA60[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018FA68[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018FA70[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018FA78[])(void);
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
extern void (*D_8018FA80[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018FA88[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018FA90[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018FA98[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018FAA0[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018FAA8[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018FAB0[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018FAB8[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018FAC0[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018FAC8[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018FAD0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018FAD8[])(void);
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
extern void (*D_8018FB1C[])(void);
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
extern M2C_UNK D_8018FAE0;
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
extern void (*D_8018FB4C[])(void);
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
extern void (*D_8018FB88[])(void);
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
extern s32 func_801749C8();
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_8018FBE0[])();
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
extern void (*D_8018FBF0[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018FBF8[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_8018FD60[])();
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
extern void (*D_8018FD6C[])();
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
extern M2C_UNK D_801DB30C;
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
extern s32 func_801789AC(s32 arg0);
extern s16 D_801E2118;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801DC720;
extern short D_801E218C;
extern void func_80178CBC(s32 arg0, s32 arg1);
extern void func_80178D18(void);
extern s32 func_80178D40(s32 arg0, s32 arg1);
extern void func_80179B28(s32 a0);
extern void func_80179B74(u16 *p);
extern void func_80179D30(u16 *a0);
extern void func_80179D78(u16 *a0);
extern void func_80179DCC(short a0);
extern void func_80179DF8(void);
extern void func_80179E1C(short a0);
extern void func_80179E48(s16 a0);
extern void func_80179E74(s16 a0);
extern void func_80179EA0(u16 *a0);
extern void func_80179EE8(short a0);
extern void func_80179F14(s16 a0, s16 a1);
extern void func_80179F44(void);
extern void func_80179F6C(short a0);
extern void func_80179F98(u16 *a0);
extern void func_80179FEC(u16 *a0);
extern void func_8017A040(u16 *a0);
extern s32 D_801DCB4C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801DCB74;
extern void func_8017A144(s32 a0);
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
extern s16 D_801DCB30;
extern s32 func_8017A3B0(void);
extern void func_80172310(u8*);
extern void func_80172780(void*);
extern void func_80172894(void*);
extern void func_801729B0(s32);
extern void func_80172B14(s16);
extern void func_80172C50(u16 *);
extern void func_80172D68(s32);
extern void func_801733FC(s16, u16 *);
extern void func_80173460(s32, s32);
extern void func_801734BC(s32, s32);
extern void func_801736B0(s32, s32);
extern void func_801737B8(s16);
extern void func_801738DC(s16);
extern void func_80173A28(s32, s32, s32, s32, s32, s32);
extern void func_80174438(s32);
extern void func_8017A4AC(void);
extern s32 func_8017AD0C(s32 arg0);
extern s32 func_8017AD0C(s32);
extern s32 func_8017ADE8(s32 a0);
extern s32 func_8017AE08(void);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012BE98(s32 a0, u16 *a1);
extern s16 D_801E20E8;
extern s16 D_801E20EA;
extern s16 D_801E20F4;
extern void func_8017AE2C(s32 param_1);
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801DCB34;
extern u16 D_801DCBB4;
extern u16 D_801DCBB6;
extern u16 D_801DCBB8;
extern void func_8017B1D8(void);
extern s32 func_8017B238(s32 param_1, s32 param_2);
extern s32 func_8017B368(s32 param);
extern s32 func_8017B614(s32 param_1, s32 param_2);
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern u8 D_8012694C;
extern s16 D_801DCBAC;
extern s16 D_801DCBAE;
extern s16 D_801DCBB0;
extern s16 D_801DCBA4;
extern s16 D_801DCBA6;
extern s16 D_801DCBA8;
extern void func_8017B7A8(void);
extern s16 D_801DCBC4;
extern s16 D_801DCBC6;
extern s16 D_801DCBC8;
extern s16 D_801DCBCC;
extern s16 D_801DCBCE;
extern s16 D_801DCBD0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801DCBBC;
extern short D_801DCBBE;
extern short D_801DCBC0;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801DCB54;
extern SV4 D_801DCB5C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801DCB7C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801DCB78)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018FF48[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BF34(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8017BF08(void *a0, void *a1, s32 a2, s32 a3);
extern void (*D_8018FFA8[])(void);
extern void func_8017C114(void *a0);
extern s32 D_801DCCA0;
extern void func_8017C8D0(void);
extern void func_8017C954(s32 arg0);
extern void (*D_8018FFB0[])(void);
extern void func_8017DBFC(void *a0);
extern void func_8017DC38(s32 param_1);
extern void func_8017DDE0(void *arg0);
extern s32 func_80017E30(void *a0, void *a1);
extern void func_80016ED4(void *a0);
extern void func_8017DF74(s32 a0, s32 a1);
extern void func_8002931C(void);
extern void func_8017E22C(void);
extern void (*D_80190028[])(void);
extern void func_8017E24C(void *a0);
extern void func_8017E408(void);
extern s32 func_8017E288(s32 a0);
extern s32 func_8017E2CC(void);
extern void (*D_80190030[])(void);
extern void func_8017E2F0(void *a0);
extern void func_8017E430(void);
extern s32 func_8017E32C(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017E36C(u8 *a0);
extern s32 func_800D1EBC(void);
extern void func_8017E3E8(void);
extern M2C_UNK D_801901CC;
extern void (*D_801901D8[])(void);
extern void func_8017E458(void *a0);
extern void func_8017E494(u8 *a0);
extern void func_800CCB78(s32 a0);
extern u16 D_800B99DA;
extern void func_8017E584(s32 param_1);
extern u8 D_8019003C[];
extern void func_8017E610(void);
extern void func_8017E640(void);
extern s32 D_801900D8;
extern void func_8017E680(void);
extern u8 D_80190148[];
extern void func_8017E6B0(void);
extern void func_8012A094(s32 a0);
extern void func_8017E800(void *a0);
extern s32 func_8017E6E0(s32 a0);
extern void func_8017E770(void);
extern void (*D_801901E0[])(void);
extern s32 ratan2(s32, s32);
extern void func_8017E95C();
extern void func_8017E83C(s32 a0);
extern void func_8017E8DC(s32 a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8018ABC0(u16 *r, s16 *m);
extern void func_8017E95C(s32 param_1, s16 *param_2, s16 *param_3, s32 param_4);
extern void (*D_801906C4[])(void);
extern void func_8017EB24(void *a0);
extern u8 D_801A0720[];
extern s32 D_8019EA38[]; /* §183 TYPE-adopted-TU: TU spells this s32[] */
extern u8 D_80190450;
extern u8 D_80190451;
extern u8 D_80190452;
extern u16 D_80190490[]; /* §183 TYPE-adopted-TU */
extern s32 D_801DDB28;              /* §183 TYPE-adopted-TU */
extern s32 D_801DDB2C[5];           /* §183 TYPE-adopted-TU */
extern void *D_801DDBF0;            /* §183 unified with func_80181170 */
extern void *D_801DDBF4;            /* §183 TYPE-adopted-TU */
extern u16 D_801DDBF8[];            /* §183 TYPE-adopted-TU */
extern u16 D_801DEBF8[];            /* §183 TYPE-adopted-TU */
extern s32 D_801DFD38[];
extern s32 D_801DFD4C;
extern s32 D_801DFD50;
extern s32 func_8012C1B8(void);     /* §183 SIGNATURE-adopted-TU */
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);        /* §183 SIGNATURE-adopted-TU */
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2); /* §183 SIGNATURE-adopted-TU */
extern void func_8001C97C(void *a0);
extern s32 func_8012C194(void);
extern void StoreImage(void *a0, void *a1);
extern void func_80016450(s32 a0, s32 a1);
extern void func_8017EBC4(Obj8017EBC4 *a0);
extern void (*D_80190534[])(void);
extern void func_8017EDA8(s32 param_1);
extern void func_8017EE10(s32 param_1);
extern void func_8017EEFC(void);
extern void func_8017EF04(s32 a0);
extern void func_8017EF34(s32 param_1);
extern void func_8017F300(s32 a0);
extern void func_8017F330(s32 param_1);
extern void func_8017F970(s32 arg0);
extern void func_8017F984(s32 arg0);
extern void func_8017F9C0(s32 param_1);
extern void func_80180030(void *a0, s32 a1);
extern void func_8017FE58(void *fp, s32 count);
extern void *func_80185C6C(); /* TU idiom: calls go through a (s32,s32) fn-ptr cast */
extern s32 func_80013478(s32 a0, s32 a1);
extern void (*D_80190218[])(void);
extern s32 D_801DDB2C[5];
extern s32 aF80180030();
extern void func_80180198(s32 a0);
extern void *func_80185C6C();
extern void func_801856A4(s32 *a0, s32 a1); /* §183 SIGNATURE-adopted-TU */
extern u8 D_80190240[];
extern u8 D_80190728[];
extern void func_801804C8(s32 a0);
extern s32 D_801DDB2C[];
extern u16 D_801DDBF8[];
extern u16 D_801DEBF8[];
extern u16 D_80190490[];
extern void func_8018615C(void);
extern void func_800599B8(void *a0, void *a1);
extern void func_8017C068(void);
extern void func_801808C4(s32 a0);
extern void func_8012BEE8(void);
extern s32 func_8012E544(s32 arg);
extern void func_8002959C(void);
extern s32 func_80178B18(s32 arg, s32 arg2);
extern s16 D_801904F4[];
extern s16 D_80190510[];
extern void *D_80190680;
extern u8 D_8019060C[];
extern void func_801809D4(s32 param_1);
extern void func_80180E58(void);
extern s32 func_80180E60(s32 param_1);
extern void func_8018612C(void);
extern void func_80180EA8(void);
extern s32 func_8018B1E0(s32 arg);
extern void func_80180EC8(void);
extern s32 func_8018B20C(void);
extern void func_80180EE8(void);
extern s32 D_801904D4[];
extern s32 D_801DFD8C;
extern s32 D_801DFD90;
extern void func_8018180C(void *a0);
extern void func_80180F08(void);
extern void func_8018618C(s16 arg0);
extern void func_80180F4C(void);
extern s32 func_80180F88(s32 arg0);
extern s32 func_80181268(s32 a0);
extern u8 D_80190348[];
extern void *D_801DDBF4;
extern s32 func_80180FE0(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern u8 D_80190348[];   /* §183 unified with func_80180FE0 */
extern D80190448_t D_80190448;
extern void *D_801DDBF0;
extern void func_80181170(void);
extern u8 D_8019072C[];
extern s32 func_801812AC(s32 a0);
extern s32 func_80181334(void);
extern void func_800599B8(void*, void*);
extern u16 D_800B99D8;
extern void func_80181378(void *a0);
extern u8 *func_8012913C(s32 a0);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_801814B0(u16 *param_1, s32 param_2);
extern s16 D_801904C6;
extern s16 D_801904CE;
extern s32 func_80012CB8(s32 a0, s32 a1, s32 a2);
extern void func_80181708(int param_1);
extern void (*D_8019073C[])(void);
extern code_fn D_801907B4[];
extern s32 func_80181DF8(s32 a0);
extern void func_80181848(int param_1);
extern s32 D_80190780;
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_80181D94(s32 a0);
extern s32 func_80182334();
extern void func_80181898(s32 param_1);
extern void func_80181964(s32 arg0);
extern void func_80181AC0(s32 param_1);
extern void func_80181C04(s32 param_1);
extern void func_80181D40(s32 param_1);
extern void (*D_80190238[])(void);
extern void func_801856A4(s32 *a0, s32 a1);
extern void func_80181D94(s32 param_1);
extern void func_801856C0(s32 *a0);
extern void func_80182388(s32 a0, s32 a1);
extern void func_801825D8(s32 a0, s32 a1);
extern u8  D_800AF648;
extern s32 D_801903C8;
extern s32 D_801902C0;
extern u16 D_801904AC[];
extern u8  D_801DFD94[];
extern u8  D_801DFD96[];
extern u8  D_801DFD98[];
extern s32 D_801DFDA8;
extern s32 D_801DFDAC;
extern s32 D_801DFDB0;
extern s32 D_801DFDB4[];
extern s32 D_801DFDB6[];
extern s32 D_801DFDB8[];
extern s32 D_801DFDC8[];
extern s32 func_80181DF8(s32 param_1);
extern s32 func_80182334(s32 a0);
extern s32 func_8012B77C(s32 out, s32 from, s32 to);
extern u8 D_801DFD94[];   /* §183 TYPE-adopted-TU */
extern s32 D_801DFDB4[];  /* §183 TYPE-adopted-TU */
extern void func_801825D8(s32 arg0, s32 arg1);
extern void (*D_801908F8[])(void);
extern void func_801827D0(void *a0);
extern s32 func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 D_8019EA7C[];
extern u8 D_80190808[];
extern void func_80182BC8();
extern void func_8018280C(s32 param_1);
extern Blk8_801828E4 D_801DDB48;
extern s32 D_8019EA38[];
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_801828E4(s32 param_1);
extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern void func_80182BC8(s32 a0);
extern void (*D_80190940[])(void);
extern void func_80182D74(void *a0);
extern void func_8001CD9C(int a0, void *a1);
extern void func_801834D8(void *a0, s32 a1);
extern void *D_801DFDD4[][8];
extern u8 D_80190900[];
extern void func_80182DB0(void *a0);
extern void func_801833FC(void *a0);
extern void func_80183478(void *a0, s32 a1);
extern void func_80183534(s32 arg0, SVEC_80183534 *arg1, SVEC_80183534 *arg2, s32 *arg3);
extern s32 func_80183848(s32 a0, s32 a1, s32 a2);
extern void func_801838BC(short *param_1, short *param_2);
extern void (*D_801909E4[])(void);
extern void func_80183A1C(void *a0);
extern u16 D_801909B0;
extern u8 D_80190970[];
extern void func_80183A58(s32 param_1);
extern void func_8012E9C0(int param_1);
extern void func_80183B1C(s32 param_1);
extern s16 D_8019044A;
extern s16 D_8019044C;
extern void func_80183CB8(s32 param_1);
extern void (*D_80190A00[])(void);
extern void func_80183D48(void *a0);
extern Vec8_80183D84 D_801DFE94[];
extern Vec8_80183D84 D_801DFEDC[];
extern Vec8_80183D84 D_801DFED4;
extern Vec8_80183D84 D_801DFF1C;
extern s32 D_801DFF24;
extern s32 D_801DFF28;
extern void func_80183D84(u8 *a0);
extern void func_80184464(void *a0);
extern s32 func_8018452C(void);
extern void func_80184C68(u8 *v, s32 idx);
extern void func_80184E6C(s32 *a0, s32 *a1);
extern void func_80184564(s32 param_1);
extern void func_80184EA0(s32 arg0);
extern void (*D_80190A18[])(void);
extern void func_80184EC0(void *a0);
extern void func_80184EFC(s32 a0);
extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_80185214(s32 a0);
extern void func_80184FF8(s32 param_1);
extern void func_80017910(void *a0, s32 a1);
extern void RotMatrixY(s32 r, void *m);
extern void func_800176F0(void *a0);
extern Blk20 D_800AE620;
extern void func_801852E4(s32 arg0);
extern void (*D_80190A20[])(void);
extern void func_8018562C(void *a0);
extern void (*D_80190A28[])(void);
extern void func_80185668(void *a0);
extern void func_801857A4();
extern void func_801859F4(SVec_59F4 *vtx, u32 tx, u32 ty, u32 cx, u16 cy, u8 uw, u8 vh, s32 zoff, s32 depth);
extern u8 D_801DDB50[];
extern void * func_80185C6C();
extern void func_80185C88(void *arg0);
extern u8 D_801A0734[];             /* no fleet decl; spelled like the TU's D_801A0720 */
extern void func_80185D44(void *a0);
extern void func_8012BE54(s32 a0);   /* canonical void -> cast at use site (TU convention, engine_core.h) */
extern s32 func_8001AAA0(s32 arg);
extern void func_80185E00(void *a0);
extern void (*D_80190A30[])(void);
extern void func_80185F08(void *a0);
extern void func_80185F44(void);
extern void func_80186044(void *a0);
extern s32 func_8012AD50(void *arg0);
extern s32 D_80126B58;
extern void func_80185F4C(void *a0);
extern s32 func_8012AD50(void *a0);
extern void func_801860EC(s32 *a0);
extern void func_80186124(void);
extern s32 func_8012E544(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8018619C(void);
extern void func_8018653C(s32 *a0, s32 *a1);
extern void func_801861A4(s32 param_1);
extern s32 func_80186470(s32 a0, s32 a1, s16 a2, s16 a3, s32 a4);
extern void func_80186214(s32 param_1);
extern s32 func_8018656C(s32 *);
extern void func_8018641C(s32);
extern s32 func_8012C588(s32, s32);
extern void func_801862C0(s32 param_1);
extern u32 D_801DFF68;
extern void func_801863C8(s32);
extern void func_80186334(s32 param_1);
extern void func_801863C0(void);
extern void func_801863C8(s32 param_1);
extern void func_8018641C(s32 param_1);
extern void func_8012BE54(s32 a0);
extern s32 func_800132BC(SVECTOR_8018656C *a0, SVECTOR_8018656C *a1);
extern s32 func_8018656C(s32 *a0);
extern void (*D_80192174[])(void);
extern void func_80186674(void *a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 D_801DFF6C;
extern s32 D_801DFF70;
extern s32 D_801DFF74;
extern s32 D_801DFF78;
extern s32 D_801DFF7C;
extern s32 D_801DFF80;
extern s32 D_801DFF84;
extern s32 D_801DFF88;
extern s16 D_801DFFDC;
extern s32 D_80191474;
extern void func_801866B0(s32 param_1);
extern u16 D_801922AC;
extern u16 D_801922AE;
extern u16 D_801922B0;
extern u16 D_801922B4;
extern u16 D_801922B6;
extern u16 D_801922B8;
extern u8 D_801922BC[];
extern signed char D_8018F650[];
extern signed char D_8018F664[];
static inline void setup_80188D90(s32 a0, void *mtx);
extern void func_801867D0(s32 param_1);
extern void func_80186960(void);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801B956C;
extern void (*D_801D4D0C)();
extern void func_80186980(s32 param_1);
extern void func_801869F8(s32 param_1);
extern void func_80186A28(s32 param_1);
extern void func_80186A58(s32 param_1);
extern void func_80186A88(s32 param_1);
extern s32 D_801BC8A4[];
extern void func_8001C924(void *a0, s32 *a1);
extern s32 func_80186AB8(void);
extern s32 D_801DFF8C[];
extern u8 D_801DFF9C[];
extern s32 D_801BCF0C;
extern void func_80186B00(void);
extern u8 D_8018CCE8;
extern void func_8012CBCC(s32 a0);
extern s32 func_80186B6C(void);
extern s32 func_80186BD4(void);
extern void func_8012E88C(u8 *a0);
extern void func_80186BEC(void);
extern void func_8012E8A8(u8 *a0);
extern void func_80186C14(void);
extern s32 func_80186C3C(s32 param_1);
extern s32 func_80186C88(void);
extern s32 D_801DFFB8;
extern s32 D_801BF990[];
extern u8 D_801DFFD4[];
extern s32 D_801BF2BC;
extern void func_80186CC4(void);
extern void func_80186D30(void);
extern s32 func_80186D64(void);
extern u16 D_80191234;
extern s32 D_801C2AA4;
extern void func_80186DA0(void);
extern s32 D_801C2AEC;
extern u16 D_8019123C;
extern u16 D_8019123E;
extern u16 D_80191240;
extern s32 func_80143B6C(s32 a0, s32 a1);
extern s32 func_80186E18(s32 a0);
extern void func_80186F9C(void);
extern s32 func_80186FC4(void);
extern void func_8018702C(s32 a0);
extern s32 func_8018B1E0(s32);
extern void func_80187094(void);
extern void func_801870B4(void);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern s32 func_801870D4(s32 arg0);
extern s32 func_80187148(s32 arg0);
extern s32 func_8012BA10(s32 a0, s32 a1);
extern s32 func_801871E8(void);
extern u16 D_8019126C;
extern s32 func_80187230(s32 arg0);
extern void func_800D0C48(s32 arg);
extern void func_801872C4(void);
extern s32 func_801872E4(void);
extern s32 D_801B25D0;
extern s32 D_8018CCC4;
extern void func_80187D64(s32 arg0);
extern s32 func_80187304(void);
extern void func_8018736C(void);
extern u8 D_801B2B80;
extern void func_80187394(void);
extern s32 func_801873F4(void);
extern s16 D_80191254[];
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern s32 func_80013350(s32 a0, s32 a1);
extern s32 func_8018743C(void);
extern Vec_80187A04 D_8019217C;
extern void RotMatrixY(s32 a0, void *a1);
extern s32 func_80187A04(void);
extern void func_80187B30(void);
extern void func_80187B58(void);
extern void func_80187B80(void);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_80187C2C(void);
extern s32 func_80187CE4(void);
extern s32 D_80126B60;
extern s32 D_80126B64;
extern u16 D_8019218C[];
extern u16 D_8019125C;
extern u16 D_8019125E;
extern u16 D_80191260;
extern u16 D_80191264;
extern u16 D_80191266;
extern u16 D_80191268;
extern void func_801885C0();
extern s32 func_80187E84(s32 arg);
extern void func_801881D8(void);
extern int D_801DFF70;
extern u16 D_8019126E;
extern u16 D_80191270;
extern Rec12 D_8019219C[];
extern void func_80188240(void);
extern s32 func_8018BFC8(s32 a0, s32 a1);
extern s16 D_801921AC[3];
extern void func_801883A0(void);
extern u8 D_801B23E8[];
extern u8 D_801B27B8[];
extern void func_801883FC(void);
extern s32 func_8017C8E4(void);
extern s32 func_80188470(void);
extern s16 D_801921B4[];
extern void func_80188490(void);
extern void func_80188548(void);
extern s32 func_8012BB3C(s32 a0, s32 a1, u32 a2, s32 a3);
extern s32 func_80188568(s32 arg0);
extern void func_801885C0(s32 *a0, s32 *a1);
extern void func_8018865C(void);
extern void func_8018884C(void);
extern void func_8012A018(s32 a0, s32 a1);
extern void func_80188BB0();
extern s8 D_801913F4[];
extern s32 D_801DFFE0;
extern s32 D_801DFFE4;
extern s32 D_801DFFE8;
extern s32 D_801DFFEC;
extern void func_801888A8(void);
extern void func_80188904(void);
extern void func_80188960(void);
extern void func_80188988(int param_1);
extern u16 D_801913E4[];
extern u16 D_801913EC[];
extern void func_80188A90(int param_1);
extern void (*D_801921BC[])(void);
extern void func_80188BB0(void *a0);
extern void (*D_801921C8[])(void);
extern void func_80188BEC(void *a0);
extern void (*D_801921D0[])(void);
extern void func_80188C28(void *a0);
extern void (*D_801921D8[])(void);
extern void func_80188C64(void *a0);
extern void (*D_801921E0[])(void);
extern void func_80188CA0(void *a0);
extern void (*D_80192210[])(void);
extern void func_80188CDC(void *a0);
extern void (*D_80192298[])(void);
extern void func_80188D18(void *a0);
extern void (*D_801922A4[])(void);
extern void func_80188D54(void *a0);
extern void func_80188D90(s32 a0);
extern void (*D_801922C4[])(void);
extern void func_80188D90();
extern void func_80189148(void *arg0);
extern void (*D_801922EC[])(void);
extern void func_801891D0(void *a0);
extern void func_80189244(Obj_80189244 *p);
extern void RotMatrixZ(s32 r, void *m);
extern void func_80189440(s32 arg0, SV_189440 *v);
/* ==== end §8b carried decl layer ==== */


/* func_801898CC — ov_SC06_029 / ov_SC06_029_jr_8017C954 (155 ins, 5-way jtbl switch).
 * Every symbol below is spelled from this .s's own relocation lines (D_800B99DA,
 * D_801E0001, D_801DFFDC, func_8002D4C8, func_8012913C, rand, func_8012BEE8,
 * func_80016714, func_8012C218).
 *
 * INTEGRATION FIX (this is why the previous attempt gated as "won't compile
 * standalone"): the body was already byte-correct (match_one closeness 0), but it
 * declared `extern s32 func_8012BEE8(void *a0);` and tested its return value. This
 * TU declares that callee `extern void func_8012BEE8(void);` at file scope (lines
 * 4905 / 7479 / 8782 / …), so the block-scope decl was a conflicting-types error the
 * moment the draft landed in the file. Fixed the same way every other banked
 * function in this TU does it (see the func_8017EF34 / func_8017F330 headers): keep
 * the callee decl copied VERBATIM from the TU and route the a0-passing,
 * value-returning call through the TU's own function-pointer cast. The cast is
 * byte-neutral — the emitted `jal func_8012BEE8` is unchanged.
 *
 * D_801E0001 is the one symbol this TU never declares; it is a `.byte` at 0x801E0001
 * in asm/ov_SC06_029/data/tail19.data.s and the .s writes it with `sb`, hence u8.
 * `pad[4]` is load-bearing: it sizes the frame to the target's 0x38. */
void func_801898CC(s32 param_1)
{
    extern u16 D_800B99DA;
    extern u8 D_801E0001;
    extern s16 D_801DFFDC;
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern u8 *func_8012913C(s32 a0);
    extern s32 rand(void);
    extern void func_8012BEE8(void);
    extern void func_80016714(void *a0, s32 a1);
    extern void func_8012C218(void *a0);

    s32 sub;
    s32 ent;
    s16 r;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 pad[4];

    sub = *(s32 *)(param_1 + 0xCC);

    if ((D_800B99DA & 1) == 0) {
        D_801E0001 = 0x20;
    } else {
        D_801E0001 = 0;
    }

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        if ((*(u16 *)&D_801DFFDC) != 1) {
            return;
        }
        *(u32 *)(sub + 4) &= 0x7FFFFFFF;
        *(u16 *)(param_1 + 0x34) += 1;
        func_8002D4C8(0xCA1, 0);
        return;
    case 1:
        r = *(u16 *)(sub + 0xE) - 0x40;
        *(s16 *)(sub + 0xE) = r;
        if (r >= -0x2FF) {
            return;
        }
        *(s16 *)(sub + 0xE) = -0x300;
        *(u16 *)(param_1 + 0x34) += 1;
        return;
    case 2:
        if ((*(u16 *)&D_801DFFDC) != 2) {
            return;
        }
        *(s32 *)(param_1 + 0x1C) = 0x20;
        *(u16 *)(param_1 + 0x34) += 1;
        return;
    case 3:
        *(s16 *)(sub + 0xA) = *(u16 *)(sub + 0xA) - 0x40;
        if (((s32 (*)(void *))func_8012BEE8)((void *)param_1) != 0) {
            func_80016714((void *)sub, 0x38);
            func_8012C218((void *)param_1);
        }
        return;
    case 4:
        if ((D_800B99DA & 1) != 0) {
            return;
        }
        ent = (s32)func_8012913C(0x22);
        if (ent != 0) {
            a = rand();
            *(s16 *)(ent + 6) = (a % 128) - 0x40;
            b = rand();
            *(s16 *)(ent + 0xA) = (b % 128) - 0x182;
            c = rand();
            *(s16 *)(ent + 0xE) = (c % 128) - 0x40;
            d = rand();
            e = rand();
            *(u16 *)(ent + 0x34) = (((d % 5) << 12) + 0x3000) | (e & 1);
            *(u16 *)(*(s32 *)(ent + 0x20) + 0x2C) = 0xC008;
        }
        if (((s32 (*)(void *))func_8012BEE8)((void *)param_1) != 0) {
            func_80016714((void *)sub, 0x38);
            func_8012C218((void *)param_1);
        }
        return;
    }
}



extern void (*D_801922F4[])(void);

void func_80189B38(void *a0) {
    D_801922F4[*(u16 *)((s32)a0 + 0x2)]();
}


extern u16 D_80126B5E;
extern u16 D_80126B66;

void func_80189B74(void *a0) {
    s16 *p;

    p = (s16 *)&D_80126B5E;
    *(s32 *)((s32)a0 + 0x48) = p[0];
    p = (s16 *)&D_80126B66;
    *(s32 *)((s32)a0 + 0x50) = p[0];
    p = (s16 *)&D_80126B5E;
    *(s32 *)((s32)a0 + 0x3C) = p[0];
    p = (s16 *)&D_80126B66;
    *(s32 *)((s32)a0 + 0x44) = p[0];
}


#include "common.h"
#include "../shared/engine_prelude.h"

extern Blk20 D_800AE620;
extern u8 D_801B5EC8;
extern u8 D_801B90F4;

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012E8A8(u8 *a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);

void func_80189BB4(void *a0) {
    Blk20 mtx;
    s32 v0;

    mtx = D_800AE620;
    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        s32 vec[3];

        func_8001C214(v0, (s32)&D_801B5EC8);
        func_8012A828((s32)a0, &D_801B90F4);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0xA00;
        func_8012E8A8((u8 *)a0);
        RotMatrixY(0x200, &mtx);
        vec[0] = 0;
        vec[1] = (s32)0xFE000000;
        vec[2] = (s32)0xFC800000;
        func_800484EC((s32)&mtx, (s32)vec, (s32)a0 + 4);
        func_8012B2CC((s32)a0);
        *(s32 *)((s32)a0 + 0x6C) = func_8012C588(0x382, (s32)a0);
        func_8012B178((s32)a0, (s32)0xFFFC0000);
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


void func_80189CE4(void) {
}

#include "common.h"



extern Blk20 D_800AE620;
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8012E8A8(u8 *a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern s32 D_801BF2BC;
extern s32 D_801C2994;

void func_80189CEC(void *a0)
{
    Blk20 blk;
    s32 v0;
    s32 v1;
    s32 arr[3];

    blk = D_800AE620;
    v0 = func_8012C1B8();
    *(s32 *)((u8 *)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, (s32)&D_801BF2BC);
    func_8012A828((s32)a0, &D_801C2994);
    v1 = *(s32 *)((u8 *)a0 + 0x20);
    *(u16 *)(v1 + 0x12) = 0x600;
    func_8012E8A8((u8 *)a0);
    RotMatrixY(-0x200, &blk);
    arr[0] = 0x00280000;
    arr[1] = (s32)0xFE000000;
    arr[2] = (s32)0xFC800000;
    func_800484EC((s32)&blk, (s32)arr, (s32)((u8 *)a0 + 4));
    func_8012B2CC((s32)a0);
    func_8012B178((s32)a0, (s32)0xFFFC0000);
    *(u16 *)((u8 *)a0 + 2) = *(u16 *)((u8 *)a0 + 2) + 1;
}


void func_80189E10(void) {
}

#include "common.h"

typedef struct { s32 w[8]; } Mtx8_80189E18;

extern Blk20 D_800AE620;
extern u8 D_801C5C70[];
extern u8 D_801C8E38[];

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012E8A8(u8 *a0);
extern void RotMatrixY(int r, void *m);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_80189E18(s32 param_1)
{
    Mtx8_80189E18 mtx;
    s32 sp30[3];
    s32 v0;

    mtx = (*(Mtx8_80189E18 *)&D_800AE620);

    v0 = func_8012C1B8();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }

    func_8001C214(v0, (s32)D_801C5C70);
    func_8012A828(param_1, D_801C8E38);

    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = 0x600;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) | 0x10;
    func_8012E8A8((u8 *)param_1);

    RotMatrixY(-0x200, &mtx);

    sp30[0] = -0x280000;
    sp30[1] = -0x2000000;
    sp30[2] = -0x3800000;
    func_800484EC((s32)&mtx, (s32)sp30, param_1 + 4);

    func_8012B2CC(param_1);

    func_8012B178(param_1, -0x40000);

    *(u16 *)(param_1 + 2) += 1;
}


void func_80189F50(void) {
}

#include "common.h"
#include "../shared/engine_types.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012E8A8(u8 *a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

extern Blk20 D_800AE620;
extern u8 D_801CBE14;
extern u8 D_801CEE2C;

void func_80189F58(s32 param_1)
{
    Blk20 localMatrix;
    VECTOR localVec;
    s32 v0;

    localMatrix = D_800AE620;
    v0 = func_8012C1B8();
    *(s32 *)((u8 *)param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
    } else {
        func_8001C214(v0, (s32)&D_801CBE14);
        func_8012A828(param_1, (void *)&D_801CEE2C);
        *(u16 *)(*(s32 *)((u8 *)param_1 + 0x20) + 0x12) = 0xA00;
        func_8012E8A8((u8 *)param_1);
        RotMatrixY(0x200, &localMatrix);
        localVec.vx = 0;
        localVec.vy = 0xFE000000;
        localVec.vz = 0xFC800000;
        func_800484EC((s32)&localMatrix, (s32)&localVec, param_1 + 4);
        func_8012B2CC(param_1);
        func_8012B178(param_1, 0xFFFC0000);
        *(s32 *)((u8 *)param_1 + 0x1c) = 0x20;
        *(u16 *)((u8 *)param_1 + 2) += 1;
    }
}


void func_8018A07C(void) {
}

#include "common.h"
#include "../shared/engine_prelude.h"

extern Blk20 D_800AE620;
extern s32 D_801A7A34;
extern u8 D_801B23E8[];

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012E8A8(u8 *a0);

void func_8018A084(void *a0) {
    Blk20 mtx;
    s32 v0;
    s32 v1;
    s32 vec[3];

    mtx = D_800AE620;

    v0 = func_8012C1B8();
    *(s32 *)((u8 *)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, (s32)&D_801A7A34);
    func_8001D0E8(*(s32 *)((u8 *)a0 + 0x20), 0x7FFF, 0x7FFF);

    v1 = *(s32 *)((u8 *)a0 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x10;
    v1 = *(s32 *)((u8 *)a0 + 0x20);
    *(u16 *)(v1 + 0x1C) = 1;
    *(u16 *)(v1 + 0x1A) = 1;
    *(u16 *)(v1 + 0x18) = 1;
    func_8012A828((s32)a0, &D_801B23E8);
    func_8012E8A8((u8 *)a0);

    *(s16 *)((u8 *)a0 + 0xA) = -0x102;
    *(s16 *)((u8 *)a0 + 0x2) = (*(u16 *)((u8 *)a0 + 0x2)) + 1;
}


#include "common.h"

/* func_8018A180 — MATCH (63 ins, frame 0x68).
 *
 * @class: cse-address-unify (§153) + SCHEDULE-REORDER
 * @keys:
 *  (1) FRAME: `buf` is a 0x20-byte MATRIX but the frame needs 0x28 of space for it
 *      (vars 0x10..0x60, $s0@0x60/$ra@0x64, frame 0x68).  Modelled the way the already-
 *      matched sibling func_8016BFD0 does it (see src/shared/engine_types.h Mtx_8016BFD0):
 *      pad the buffer TYPE, not the frame — MtxBuf = { Mtx mt; s32 rest[2]; }.  The
 *      wholesale copy then has to go through `buf.mt` so it stays 8 lw/sw pairs.
 *  (2) &buf is used at SIX call sites.  Plain `&buf` everywhere makes cse unify all six
 *      into one pseudo with >2 refs, so local-alloc's remat path (which needs
 *      reg_n_refs==2) never fires and the address is parked in an extra callee-saved
 *      register (+3 ins, frame 0x70).  Fix: launder the address through an empty asm at
 *      every site EXCEPT the last.
 *      The asm must be NON-volatile (`__asm__("" : "=r"(x) : "0"(x))`, no
 *      `__volatile__`).  A volatile asm is a scheduling barrier: it pins everything
 *      textually after it to schedule after it, which drags `sw $ra,0x64($sp)` and
 *      `lui $v0,0x60000000` to the wrong side of the first call setup.  A non-volatile
 *      asm still defeats cse (an ASM_OPERANDS is not a foldable expression, and the
 *      "0" tie makes the asm CLOBBER the pseudo, so the (plus $sp,0x38) equivalence
 *      is invalidated at each site) while staying freely schedulable.
 *  (3) Exactly ONE site must stay un-laundered, and it has to be the LAST one.
 *      - If the last site is laundered too, its asm output pseudo does not coalesce into
 *        $a1 and you get a spurious `addiu $v0,$sp,0x38 / move $a1,$v0` (+1 ins).
 *      - If the FIRST site is the un-laundered one instead, its (plus $sp,0x38) pseudo
 *        survives in the cse table and every later laundered site's asm INPUT unifies
 *        with it — back to the callee-saved parking (67 ins).
 *  (4) Last 2-instruction residual: the first call's `addiu $a1,$zero,0xE` must be
 *      emitted BEFORE `addiu $a2,$sp,0x38`.  The stmt-expr for arg3 forces arg3 to be
 *      pre-computed during argument evaluation, which lands its insn ahead of the plain
 *      constant's move-to-hardreg.  Launder the constant too (`ang`) so it is likewise
 *      pre-computed, at an earlier textual position — the two empty asms cost 0 bytes and
 *      the order flips to match.
 */

typedef struct {
    s16 vx, vy, vz, pad;
} SVec_8018A180;

typedef struct {
    s16 m[9];    /* 0x00 */
    s16 pad;     /* 0x12 */
    s32 t[3];    /* 0x14, 0x18, 0x1c */
} Mtx_8018A180;

typedef struct {
    Mtx_8018A180 mt;  /* 0x00 */
    s32 rest[2];      /* 0x20..0x27 — frame padding, never touched */
} MtxBuf_8018A180;

typedef struct {
    SVec_8018A180 v[4]; /* 0x00..0x1f */
    s32 rgb;            /* 0x20 */
    s32 tag;            /* 0x24 */
} Prim_8018A180;

extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80017274(s32 a0, s32 a1);
extern SVec_8018A180 D_801921E8;
extern SVec_8018A180 D_801921F0;
extern SVec_8018A180 D_801921F8;
extern SVec_8018A180 D_80192200;

/* §153 address launder — NON-volatile on purpose (see key (2) above). */
#define LAUNDER_8018A180(p) \
    ({ s32 _m = (s32)(p); __asm__("" : "=r"(_m) : "0"(_m)); _m; })

void func_8018A180(s32 a0) {
    Prim_8018A180 prim;
    MtxBuf_8018A180 buf;
    s32 iVar1;

    prim.rgb = 0x282828;
    prim.tag = 0x60000000;
    {
        s32 ang = 0xE;
        __asm__("" : "=r"(ang) : "0"(ang));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
        func_8012EA90(a0, ang, (s32 *)LAUNDER_8018A180(&buf));  // !FAKE: launder via LAUNDER_8018A180 — NEEDED DIFFERS (P36 rung B tus9)
    }
    func_8012F14C(LAUNDER_8018A180(&buf), (s32)&D_801921E8, (s32)&prim.v[0]);  // !FAKE: launder via LAUNDER_8018A180 — NEEDED DIFFERS (P36 rung B tus9)
    func_8012F14C(LAUNDER_8018A180(&buf), (s32)&D_801921F0, (s32)&prim.v[1]);  // !FAKE: launder via LAUNDER_8018A180 — NEEDED DIFFERS (P36 rung B tus9)
    func_8012F14C(LAUNDER_8018A180(&buf), (s32)&D_801921F8, (s32)&prim.v[2]);  // !FAKE: launder via LAUNDER_8018A180 — NEEDED DIFFERS (P36 rung B tus9)
    func_8012F14C(LAUNDER_8018A180(&buf), (s32)&D_80192200, (s32)&prim.v[3]);  // !FAKE: launder via LAUNDER_8018A180 — NEEDED DIFFERS (P36 rung B tus9)

    prim.v[0].vy = 0;
    prim.v[1].vy = 0;
    prim.v[2].vy = 0;
    prim.v[3].vy = 0;

    iVar1 = *(s32 *)(a0 + 0x20);
    buf.mt = *(Mtx_8018A180 *)(iVar1 + 0x34);
    buf.mt.t[1] = -0x82;
    func_80017274((s32)&prim, (s32)&buf);
}

#undef LAUNDER_8018A180


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80132288(int *param_1, int *param_2, int param_3);
extern void func_8012A828(s32 a0, void *a1);

extern void *D_801CFCA4;
extern u8 D_801DFFF0[];
extern void (*D_80192260[])(void);
extern void (*D_80190EDC[])();

void func_8018A27C(int param_1)
{
    s32 p1;
    void **ptr;
    s32 v0;

    v0 = func_8012C1B8();
    p1 = param_1;
    *(s32 *)(p1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)p1);
    } else {
        ptr = &D_801CFCA4;
        func_8001C214(v0, (s32)ptr);
        func_80132288((int *)&D_801DFFF0, (int *)D_80192260, (s32)*ptr);
        func_8012A828(p1, &D_80190EDC);
        *(u16 *)(p1 + 2) += 1;
    }
}


typedef struct { u16 h0, h1, h2, h3; } Blk8_8018A314;

extern void (*D_801D4D0C)();

void func_8018A314(s32 arg0)
{
    s32 *v1;
    s32 a0;
    s32 v0;

    v1 = *(s32 **)(arg0 + 0x64);
    a0 = *(s32 *)(arg0 + 0x20);

    *(s32 *)(arg0 + 0x4) = v1[1];
    *(s32 *)(arg0 + 0x8) = v1[2];
    *(s32 *)(arg0 + 0xC) = v1[3];

    *(Blk8_8018A314 *)(a0 + 0x10) = *(Blk8_8018A314 *)(v1[8] + 0x10);

    if (*(s32 *)(arg0 + 0x90) == (s32)&D_801D4D0C && *(s16 *)(arg0 + 0x98) == 0) {
        *(s32 *)(arg0 + 0x48) = 0x2000;
        *(s32 *)(arg0 + 0x1C) = 0x80;
        v0 = *(u16 *)(arg0 + 0x2);
        *(u16 *)(arg0 + 0x2) = v0 + 1;
        func_8002D4C8(0xB5C, 0);
    }
}


extern void func_8012AD80(s32 a0);
extern void func_8013240C(s32 a0);
extern void func_8012BEE8(void);
extern void func_8012C218(void *a0);
extern u8 D_801DFFF0[];

void func_8018A3CC(s32 param_1) {
    func_8012AD80(param_1);
    func_8013240C((s32)&D_801DFFF0);
    if (((s32 (*)(void *))func_8012BEE8)((void *)param_1) != 0) {
        func_8012C218((void *)param_1);
    }
}


#include "common.h"



extern Blk20 D_800AE620;
extern s16 D_801D4F0C;

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_8018A41C(void *a0) {
    Blk20 mtx;
    s32 v0;
    s32 vec[3];

    mtx = D_800AE620;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, (s32)&D_801D4F0C);
    func_8001D0E8(*(s32 *)((u8 *)a0 + 0x20), 0x7FFF, 0x7FFF);

    if (*(s16 *)((u8 *)a0 + 0x70) == 0) {
        RotMatrixY(0x200, &mtx);
        *(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) = 0xA00;
    } else {
        RotMatrixY(-0x200, &mtx);
        *(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) = 0x600;
    }

    vec[0] = 0;
    vec[1] = -0x1E00000;
    vec[2] = -0x4200000;
    func_800484EC((s32)&mtx, (s32)vec, (s32)((u8 *)a0 + 4));
    func_8012B2CC((s32)a0);
    func_8012E8A8((u8 *)a0);
    func_8012B178((s32)a0, 0xFFFC0000);

    *(u16 *)((u8 *)a0 + 2) = *(u16 *)((u8 *)a0 + 2) + 1;
}


void func_8018A564(void) {
}

void func_8018A56C(void *a0) {
    extern s32 func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C810(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
    extern void func_8012E8A8(u8 *a0);
    extern s32 D_801D812C[];
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((u8 *)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C810(v0, (s32)D_801D812C);
    func_8001D0E8(*(s32 *)((u8 *)a0 + 0x20), 0x7FFF, 0x7FFF);
    func_8012E8A8((u8 *)a0);

    *(u16 *)((u8 *)a0 + 2) = *(u16 *)((u8 *)a0 + 2) + 1;
    *(s32 *)((u8 *)a0 + 0x48) = 0xC000;
}


void func_8018A5E8(void) {
}

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern u16 D_800DF2E0;
extern u16 D_8019127C[];
extern u16 D_801922CC[];

void func_8018A5F0(s32 a0)
{
    register s32 s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 s1 __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B tus9)
    s32 sub;
    u32 flags;
    u16 half;

    s1 = a0;
    sub = ((s32 (*)(void))func_8012C1B8)();
    s0 = sub;
    *(s32 *)(s1 + 0x20) = s0;
    if (s0 == 0) {
        func_8012CAE4((void *)s1);
        return;
    }

    func_8001C810(s0, (s32)&D_800DF2E0);
    *(s32 *)(s0 + 0x80) = (s32)&D_8019127C;

    flags = *(u32 *)(s0 + 4);
    half = *(u16 *)(s0 + 0x2C);
    *(u16 *)(s0 + 0x1C) = 0;
    *(u16 *)(s0 + 0x1A) = 0;
    *(u16 *)(s0 + 0x18) = 0;
    *(u32 *)(s0 + 4) = flags | 0x60000000;
    *(u16 *)(s0 + 0x2C) = half | 0xB0;

    sub = *(u16 *)(s1 + 2);
    sub = sub + 1;
    *(s32 *)(s1 + 0xDC) = (*(s16 *)(s1 + 0x70) * 8) + (s32)&D_801922CC;
    *(u16 *)(s1 + 2) = sub;
}


extern void func_8012BEE8(void);

void func_8018A6A4(s32 p) {
    s32 o;
    s32 tbl;
    s32 lim1, lim2;
    s16 t1, t2, lv1, lv2;
    s32 pad[3];

    (void)&pad;
    o = *(s32 *)(p + 0x20);
    if (*(u16 *)(p + 0x34) == 0) {
        t1 = *(u16 *)(o + 0x1C) + 0x800;
        tbl = *(s32 *)(p + 0xDC);
        *(s16 *)(o + 0x1C) = t1;
        *(s16 *)(o + 0x18) = t1;
        lim1 = *(s16 *)tbl;
        lv1 = lim1;
        if (lim1 < t1) {
            *(s16 *)(o + 0x1C) = lv1;
            *(s16 *)(o + 0x18) = lv1;
        }
        t2 = *(u16 *)(o + 0x1A) + 0x800;
        *(s16 *)(o + 0x1A) = t2;
        lim2 = *(s16 *)(tbl + 2);
        lv2 = lim2;
        if (lim2 < t2) {
            *(s16 *)(o + 0x1A) = lv2;
            *(s32 *)(p + 0x1C) = *(s16 *)(tbl + 4);
            *(u16 *)(p + 0x34) += 1;
        }
    } else if (((s32 (*)(void))func_8012BEE8)() != 0) {
        t1 = *(u16 *)(o + 0x1C) + 0x400;
        *(s16 *)(o + 0x1C) = t1;
        *(s16 *)(o + 0x18) = t1;
        if (t1 >= 0x7001) {
            *(s16 *)(o + 0x1C) = 0x7000;
            *(s16 *)(o + 0x18) = 0x7000;
        }
        t2 = *(u16 *)(o + 0x1A) + 0x100;
        *(s16 *)(o + 0x1A) = t2;
        if (t2 >= 0x7001) {
            *(s16 *)(o + 0x1A) = 0x7000;
        }
    }
}


#include "common.h"

extern s32 func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_800233CC(void *, unsigned short);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_80189244();

extern s32 D_801E0000;
extern s32 D_801E0004;
extern u8 D_801E0040;

void func_8018A7C4(s32 a0)
{
    s32 obj;
    s32 i;
    s32 *base;
    u8 *puVar2;

    if ((*(u16 *)(a0 + 0x70) & 1) != 0) {
        obj = func_8012C194();
        if (obj == 0) {
            func_8012CAE4((void *)a0);
            return;
        }
        *(s32 *)(a0 + 0xCC) = obj;
        base = &D_801E0000;
        func_800233CC(base, 0x80);
        *base = 0x00402040;
        D_801E0004 = 0;
        func_8001CD50(obj, (s32)base);
        *(s16 *)(obj + 0x10) = -0x400;
        *(u16 *)(obj + 0x2C) = 0xC008;
        *(s16 *)(obj + 0xA) = -0x102;
        *(u32 *)(obj + 4) |= 0xD0000000;
        *(u16 *)(a0 + 2) += 2;
    } else {
        *(s16 *)(a0 + 0xA) = -0x102;
        *(u16 *)(a0 + 2) += 1;
        i = 0;
        puVar2 = &D_801E0040;
        do {
            func_80189244(puVar2);
            i = i + 1;
            puVar2 = puVar2 + 0x1B0;
        } while (i < 0xF);
    }
}


/* func_8018A8D4 — tier 1 (structural transcription)
 * Overlay ov_SC06_029, carve region ov_SC06_029_jr_8017C954.
 * Real asm: asm/ov_SC06_029/nonmatchings/ov_SC06_029_jr_8017C954/func_8018A8D4.s
 * (0x128 bytes / 74 instructions — NOT ov_SC03_124 / 598 instructions as the
 * dispatch prompt claimed; that path does not exist. The address 0x8018A8D4
 * is reused by an unrelated, much larger function in a different overlay
 * [asm/ov_SC06_029 vs a stale ov_SC03_124 carve reference], and the Ghidra
 * seed at .run/ghidra_c/func_8018A8D4.c decompiles this exact 74-insn body
 * line-for-line, confirming this is the intended target. See report.)
 *
 * State machine on the u16 field at +0x34 of the object pointed to by
 * param_1, gated by the global mode/phase counter (*(u16 *)&D_801DFFDC), plus a
 * countdown/countup timer at +0xE0. Falls through into a fixed 15-iteration
 * dispatch loop over an array of 0x1B0-byte elements starting at D_801E0040.
 */

extern s16 D_801DFFDC;
extern u8 D_801E0040;
extern void func_8012C218(void *a0);
extern void func_80189440();

void func_8018A8D4(s32 param_1)
{
    u16 uVar1;
    s32 iVar3;
    s32 i;
    u8 *puVar2;

    uVar1 = *(u16 *)(param_1 + 0x34);
    switch (uVar1) {
    case 0:
        if ((*(u16 *)&D_801DFFDC) != 3) {
            return;
        }
        iVar3 = *(s32 *)(param_1 + 0xE0) + 1;
        *(s32 *)(param_1 + 0xE0) = iVar3;
        if (iVar3 >= 10) {
            *(s32 *)(param_1 + 0xE0) = 10;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        }
        break;
    case 1:
        if ((*(u16 *)&D_801DFFDC) == 4) {
            *(u16 *)(param_1 + 0x34) = uVar1 + 1;
        }
        break;
    case 2:
        iVar3 = *(s32 *)(param_1 + 0xE0) - 1;
        *(s32 *)(param_1 + 0xE0) = iVar3;
        if (iVar3 < 1) {
            func_8012C218((void *)param_1);
            return;
        }
        break;
    }

    i = 0;
    puVar2 = &D_801E0040;
    do {
        func_80189440((void *)param_1, puVar2);
        i = i + 1;
        puVar2 = puVar2 + 0x1B0;
    } while (i < 0xF);
}



/* func_8018A9FC — tiny matrix wrapper.
 * 0x20-byte local scratch matrix at sp+0x10 (frame 0x40 = 0x10 outgoing args
 * + 0x20 matrix + 0x10 for $s0/$s1/$s2/$ra).
 *   func_80013F3C(&m);            identity/init
 *   func_8018AA60((s16)a0, &m);   rotate by a *sign-extended halfword* angle
 *   ApplyMatrixSV(&m, a1, a2);
 * The `sll/sra 16` pair lands AFTER the first call (a0 lives in $s0 across it),
 * which is the cast-at-use-site form: an s32 parameter narrowed at the call.
 */

extern void func_80013F3C(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_8018AA60();

void func_8018A9FC(s32 a0, void *a1, void *a2) {
    s32 m[8];

    ((void (*)(void *))func_80013F3C)((void *)m);
    ((void (*)(s32, void *))func_8018AA60)((s16)a0, (void *)m);
    ApplyMatrixSV((void *)m, a1, a2);
}



void func_8018AA60(s32 param_1, s32 *param_2)
{
    s32 s0;
    s32 s1;
    s32 cos_val;
    s16 sin_val;
    s32 v1;
    s16 matrix_stack[16];

    s1 = (s32)param_2;
    s0 = param_1 & 0xFFF;

    cos_val = func_8018AE60(s0);
    sin_val = func_8018ADA4(s0);

    /* Build rotation matrix on stack */
    v1 = 0x7FF8;
    *(short *)((s32)matrix_stack + 0x04) = sin_val;
    *(short *)((s32)matrix_stack + 0x00) = cos_val;
    *(short *)((s32)matrix_stack + 0x02) = 0;
    *(short *)((s32)matrix_stack + 0x06) = 0;
    *(short *)((s32)matrix_stack + 0x08) = v1;
    *(short *)((s32)matrix_stack + 0x0A) = 0;
    *(short *)((s32)matrix_stack + 0x0C) = -sin_val;
    *(short *)((s32)matrix_stack + 0x0E) = 0;
    *(short *)((s32)matrix_stack + 0x10) = cos_val;

    __asm__ volatile (
        "lw $12, 0(%0);"
        "lw $13, 4(%0);"
        "ctc2 $12, $0;"
        "ctc2 $13, $1;"
        "lw $12, 8(%0);"
        "lw $13, 12(%0);"
        "lw $14, 16(%0);"
        "ctc2 $12, $2;"
        "ctc2 $13, $3;"
        "ctc2 $14, $4;"
        "addiu $2, $sp, 0x10;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0);"
        "addiu $2, $sp, 0x12;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, %0, 0x2;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2);"
        "addiu $2, $sp, 0x14;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu %0, %0, 4;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0)"
        : "=r"(s1)
        : "0"(s1)
        : "$12", "$13", "$14", "$2"
    );
}



void func_8018ABC0(u16 *r, s16 *m) {
    s16 cx;
    s16 sx;
    s16 cy;
    s16 sy;
    s16 cz;
    s16 sz;
    s32 sxsy;
    s32 cxcz;
    s32 cxsz;

    cx = func_8018AE60(r[0] & 0xFFF);
    sx = func_8018ADA4(r[0] & 0xFFF);
    cy = func_8018AE60(r[1] & 0xFFF);
    sy = func_8018ADA4(r[1] & 0xFFF);
    cz = func_8018AE60(r[2] & 0xFFF);
    sz = func_8018ADA4(r[2] & 0xFFF);

    cxsz = (cx * sz) >> 15;
    cxcz = (cx * cz) >> 15;
    sxsy = (sx * sy) >> 15;

    m[0] = (cz * cy) >> 15;
    m[1] = ((sxsy * cz) >> 15) - cxsz;
    m[2] = ((cxcz * sy) >> 15) + ((sx * sz) >> 15);
    m[3] = (sz * cy) >> 15;
    m[4] = ((sxsy * sz) >> 15) + cxcz;
    m[5] = ((cxsz * sy) >> 15) - ((sx * cz) >> 15);
    m[6] = -sy;
    m[7] = (cy * sx) >> 15;
    m[8] = (cy * cx) >> 15;
}



/* func_8018ADA4 — quadrant-folded sine lookup over a 0x400-entry u16 table.
 *
 * asm evidence:
 *   Q0 (a<0x400)          : lh   tbl[a]
 *   Q1 (a-0x400 < 0x400)  : lh   tbl[0x7FF - a]
 *   Q2 (a-0x800 < 0x400)  : lhu  tbl[a - 0x800], negu, sll/sra 16
 *   Q3 (a-0xC00 < 0x400)  : lhu  tbl[0xFFF - a],  negu, sll/sra 16
 *   else                  : NO value is produced at all (see below)
 *
 * The `lhu` + `negu` + 16-bit sign-extend in Q2/Q3 pins BOTH types:
 *   - the table element is UNSIGNED (zero-extending load feeding the negate), and
 *   - the result is truncated back to 16 bits => the function returns s16.
 * (An s16 table would give `lh`; an s32 return would drop the sll/sra pair.)
 *
 * Q2's base is D_801D5914 == D_801D6914 - 0x1000: gcc folded the `- 0x800`
 * element offset into the symbol addend and indexes with the raw parameter
 * (`sll $v0, $a0, 1`). Writing `tbl[a0 - 0x800]` reproduces that exactly.
 *
 * LOAD-BEARING: there is deliberately NO trailing `return 0;`.  The original
 * falls off the end of a non-void function, so the out-of-range path returns
 * whatever `$v0` happens to hold — which is the failing `sltiu` result, i.e. 0.
 * That is why the target's last test is `beqz $v0, .L8018BA04` + a bare `nop`
 * delay slot (gcc may not clobber $v0 on the taken edge) with no `move $v0,
 * $zero` anywhere.  Adding `return 0;` costs 2 instructions AND lets
 * find_cross_jump tail-merge the Q2/Q3 `negu; sll; sra` tails (cookbook §5a):
 * 45 ins / 19 mismatched instead of MATCH.
 */


s16 func_8018ADA4(u32 a0)
{

    extern u16 D_801D6914[];
    if (a0 < 0x400) {
        return D_801D6914[a0];
    }
    if (a0 - 0x400 < 0x400) {
        return D_801D6914[0x7FF - a0];
    }
    if (a0 - 0x800 < 0x400) {
        return -D_801D6914[a0 - 0x800];
    }
    if (a0 - 0xC00 < 0x400) {
        return -D_801D6914[0xFFF - a0];
    }
}



/* func_8018AE60 — quarter-table cosine lookup (sibling of func_8018B950, the sine).
 *
 * The four `lui/addu/l[h|hu] %lo(...)` bases in the target are all the SAME 0x400-entry
 * signed s16 quarter table at ((s16 *)D_801D6914); gcc folds the per-quadrant constant index
 * offset into the symbol:
 *   ((s16 *)D_801D6914)[a - 0x400]  ->  base ((s16 *)D_801D6914)-0x800 = D_801D6114, index a*2
 *   ((s16 *)D_801D6914)[a - 0xC00]  ->  base ((s16 *)D_801D6914)-0x1800 = D_801D5114, index a*2
 * so no extra externs are needed for D_801D6114 / D_801D5114.
 *
 * Types: the positive quadrants return the `lh` value straight through (already
 * sign-extended, no sll/sra); the negative quadrants take an explicit (s16) cast on
 * the negation, which forces the truncate -> the return's sign-extend becomes the
 * `sll 16 / sra 16` pair, and combine downgrades those loads to `lhu`.  Writing the
 * arms as four flat `return`s (not one shared s16 local) keeps the extension OFF the
 * positive quadrants; cross-jump then merges the two `sll/sra` tails.
 *
 * The tail has NO `return 0`.  A trailing `return 0` costs an extra `move $v0,$zero`
 * block AND lets dbr steal `sll $v0,$a0,1` into the final beqz delay slot (target has
 * a `nop` there).  Falling off the end keeps `expand_function_end`'s `(use $v0)` live
 * over the epilogue, so the delay slot stays empty and the branch lands straight on
 * the shared `jr $ra` with the `sltiu` zero already in $v0 — which IS the 0 the
 * caller observes.  Same shape as the sibling func_8018B950.
 */


s32 func_8018AE60(u32 a0v)
{

    extern u16 D_801D6914[];
    if (a0v < 0x400) {
        return ((s16 *)D_801D6914)[0x3FF - a0v];
    }
    if (a0v - 0x400 < 0x400) {
        return (s16)-((s16 *)D_801D6914)[a0v - 0x400];
    }
    if (a0v - 0x800 < 0x400) {
        return (s16)-((s16 *)D_801D6914)[0xBFF - a0v];
    }
    if (a0v - 0xC00 < 0x400) {
        return ((s16 *)D_801D6914)[a0v - 0xC00];
    }
    /* no trailing `return 0`: gcc's end-of-function (use $v0) keeps the return
     * register live over the epilogue, so dbr cannot steal `sll $v0,$a0,1` into
     * the beqz delay slot, and the 0 the caller sees is the sltiu result. */
}



extern void (*D_801D7288[])(void);

void func_8018AF0C(void *a0) {
    D_801D7288[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_801465C0(void);
extern void func_80146C3C(void);

extern void func_8001CBDC(s32 a0, s32 a1, s32 a2, s32 a3);



void func_8018AF48(void *a0) {

    extern s16 D_801D7114[][2];
    extern u8 D_801D7140[];
    extern EffectSlot4_8018AF48 D_801D714C[];
    extern u8 D_801D7178[];
    extern EffectSlot4_8018AF48 D_801D71B0;
    extern EffectSlot4_8018AF48 D_801D71D8;
    extern EffectSlot4_8018AF48 D_801D71DC;
    extern EffectSlot4_8018AF48 D_801D720C;
    extern EffectSlot4_8018AF48 D_801D7210;
    extern EffectSlot4_8018AF48 D_801D7240;
    extern EffectSlot4_8018AF48 D_801D7244;
    extern EffectSlot4_8018AF48 D_801D7274;
    extern EffectSlot4_8018AF48 D_801D7278;
    void *s0;
    void *s1;

    s1 = ((void *(*)(void))func_801465C0)();
    if (s1 != 0) {
        s32 idx;
        u8 uVar1;

        *(s32 *)((s32)a0 + 0x20) = (s32)s1;
        idx = *(s32 *)((s32)a0 + 0x2C);
        func_8001CBDC((s32)s1, (s32)D_801D7178, D_801D7114[idx][0], D_801D7114[idx][1]);
        uVar1 = D_801D7140[*(s32 *)((s32)a0 + 0x2C)];
        *(s16 *)((s32)s1 + 0x2C) = 3;
        *(u8 *)((s32)s1 + 0x27) = uVar1;
        *(s16 *)((s32)a0 + 0x6) = 0;
        *(s16 *)((s32)a0 + 0xA) = 0x50;

        /* The shift chain below needs a BASIC-BLOCK BOUNDARY before every copy
           except the first: gcc-2.7.2 CSE is per-extended-BB, and inside one BB
           it reuses the previous copy's DESTINATION address register as the next
           copy's SOURCE address (costing the lui/addiu pair the target emits).
           `if (c) X else X` supplies the boundary and is cross-jumped away by
           jump2 AFTER regalloc, so it costs 0 instructions (128/128).

           The FIRST copy must stay in block 1 with the `lw 0x2C` / `li 0x50`
           pair, or the index pseudo crosses a block and becomes a GLOBAL allocno
           (regalloc map K8) -- local-alloc then hands $v0 to the 0x50 constant
           and global-alloc is left with $v1 (the REGALLOC-PERM $v0<->$v1 swap).
           Both must be LOCAL qtys in the same block for the target's assignment.
           Its destination is therefore spelled as an INTERIOR ADDRESS of the
           neighbouring symbol (idiom 7): `&D_801D7274 + 4 == &D_801D7278`, a
           CSE-distinct rtx, so the next copy still recomputes its source
           address. Both spellings relocate to 0x80196E94. */
#define COND (*(s32 *)((s32)a0 + 0x2C) > 0)
        *(EffectSlot4_8018AF48 *)((s32)&D_801D7274 + 4) = D_801D714C[*(s32 *)((s32)a0 + 0x2C)];
        if (COND) { D_801D7274 = D_801D7278; } else { D_801D7274 = D_801D7278; }
        if (COND) { D_801D7244 = D_801D7274; } else { D_801D7244 = D_801D7274; }
        if (COND) { D_801D7240 = D_801D7244; } else { D_801D7240 = D_801D7244; }
        if (COND) { D_801D7210 = D_801D7240; } else { D_801D7210 = D_801D7240; }
        if (COND) { D_801D720C = D_801D7210; } else { D_801D720C = D_801D7210; }
        if (COND) { D_801D71DC = D_801D720C; } else { D_801D71DC = D_801D720C; }
#undef COND
        D_801D71D8 = D_801D71DC;
        D_801D71B0 = D_801D71D8;

        *(s16 *)((s32)a0 + 0x2) = *(s16 *)((s32)a0 + 0x2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(a0);
    }
}


extern void func_8018B188();
    void func_8018B148(void) {
        func_8018B188();
    }


extern void func_80146C3C(void);
    void func_8018B168(void) {
        func_80146C3C();
    }



extern void func_80017254(void *a0);
extern void func_800176F0(void *a0);

void func_8018B188(void) {

    extern u8 D_801D7190[];
    extern u8 D_801D71B8[];
    u8 *p;
    s32 i;

    func_80017254(D_801D7190);
    i = 0;
    p = D_801D71B8;
    do {
        func_800176F0(p);
        i++;
        p += 0x34;
    } while (i < 4);
}


extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_8018B1E0(s32 a0) {
    return func_80146994(0x28, 0, a0, 0);
}



extern s32 func_8014C050(s32 a0, s32 a1);

void aF8018B20C(void) __asm__("func_8018B20C");
void aF8018B20C(void)
{

    extern s32 D_80126B58;
    s32 t;

    t = func_8014C050((s32)&D_80126B58, 0x28);
    if (t != 0) {
        *(u16 *)(t + 2) += 1;
    }
}



extern void func_80019064(void *a0);

void func_8018B250(void *a0) {

    extern u8 D_801D7294;
    extern void (*D_801D72BC[])(void *);
    func_80019064(&D_801D7294);
    D_801D72BC[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014E934(s32 _arg0);
extern s32 func_8014F3E8(s32 a0);


void func_8018B2A8(s32 a0)
{
    s32 s0 = a0;
    func_8014E934(a0);
    func_8014CC28(s0);
    func_8014F3E8(s0);
    func_8018B2F8(s0);
    func_80147324(0x92F);
    func_80146CA0((void *)s0);
}




extern void func_80147324(s32 a0);
extern int func_801511E0(int);
extern void func_80154274(s32*, s32);
extern void func_80149020(s32*);
extern void func_8018B50C(void);
extern s32 func_80172630(u8*);
extern void func_80146CA0(void*);
extern u8 D_801D729C[];

void func_8018B2F8(s32 p)
{
    func_80147324(0x451);
    ((void (*)(s32))func_801511E0)(p);
    ((void (*)(s32, s32))func_80154274)(p, (s32)D_801D729C);
    ((void (*)(s32))func_80149020)(p);
    *(u8 *)(p + 0xDE) = 0x1E;
    *(u8 *)(p + 0xDF) = 0;
    func_8018B50C();
    ((void (*)(s32))func_80172630)(p);
    ((void (*)(s32))func_80146CA0)(p);
}



/* func_8018B364 @ ov_SC02_016 (subseg ov_SC02_016_jr_8017DC70) — 85 ins.
 *
 * GATE: .venv/bin/python tools/match_one.py func_8018B364 --binary ov_SC02_016 \
 *         --src .run/wave-s40/ov_SC02_016/func_8018B364.c
 *
 * Exemplar of an OPEN-ONLY h_norm cluster (9 members). Real TU is
 * src/ov_SC02_016/ov_SC02_016_jr_8017DC70.c — the immediate NEXT function in that
 * file, func_8018B4B8 (already MATCHed, see its comment there), confirms:
 *   - actor pointer arg is plain `s32 a0`
 *   - func_80172630 canon extern: `extern s32 func_80172630(u8 *a0);` (cast at call)
 *   - func_80159B3C canon extern: `extern void func_80159B3C(void *a0);` (cast at call)
 *   - func_80165718 canon extern: `extern void func_80165718(s32 a0);` (no cast)
 *   - func_80146A6C canon extern (used 30+ times fleet-wide):
 *       extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
 *
 * `func_8018B530` is DEFINED in this same TU (a few lines below the INCLUDE_ASM
 * stub for this function) — a simple "find a free slot, mark it used" scan
 * returning the slot index or -1.
 *
 * Body shape (byte-confirmed against the .s, no residual after first draft):
 *   func_80015978(a0+4, buf)     -- fills a 3-short (SVECTOR-shaped) local from
 *                                    the actor's position substruct at a0+4; this
 *                                    exact `s16 buf[4]; func_80015978(a0+4,(s32*)buf);`
 *                                    idiom is the established fleet form (see
 *                                    engine_core.h DEFINE_func_8014A380/8016D778/
 *                                    8017C908 dedup macros).
 *   buf[1] -= 0x40                -- immediately after the call. The readback here
 *                                    is `lhu` (not `lh`) even though buf is a SIGNED
 *                                    s16 array: gcc-2.7.2 always emits `lhu` for a
 *                                    plain HImode load that feeds straight into an
 *                                    `sh` store (cookbook: "It does NOT cost you the
 *                                    lhu on readback" bullet, P30 wave 4). No cast
 *                                    needed, no separate unsigned local needed.
 *   do { ... } while (++i < 3)    -- the asm has NO initial top-of-loop test before
 *                                    label .L80182318 (s3=0 set, then falls straight
 *                                    into the body) -- a genuine do-while in the
 *                                    source, not a for-loop gcc happened to rotate.
 *   if (func_8018B530() >= 0) { func_80146A6C(0x51,...); 3x rand(); func_80146A6C(0x52,...); }
 *      - the three back-to-back `rand()` calls assign straight to 3 locals in
 *        source order; gcc's own delay-slot filler moves each captured value into
 *        a callee-saved reg ($s0/$s1) via the NEXT call's branch-delay slot
 *        (standard call-crossing-value idiom, cookbook "ORDER" register-allocation
 *        entry) -- no manual reordering needed, plain sequential C reproduces it.
 *      - the final random offset is computed into a **s16 local** (not s32): the
 *        assignment truncates+sign-extends via `sll/sra` in-register (matches the
 *        target's `sll $s0,$s0,16 / sra $s0,$s0,16` with NO memory round-trip,
 *        because the s16 value is used immediately as a call argument rather than
 *        stored to a separate memory slot).
 *   cnt = *(u8*)(a0+0xDE); *(u8*)(a0+0xDE) = cnt + 0xff; if (cnt == 0) { ... } else { ... }
 *      - `lbu` (not `lb`) for the read: the "feeds only a truncated store + an
 *        equality-to-zero test" idiom, so either signedness of the C type reads
 *        identically; u8 chosen to match the common counter-byte convention used
 *        elsewhere in this TU.
 *      - THE ONE non-obvious lever: write the decrement as `cnt + 0xff`, not
 *        `cnt - 1`. Both are mathematically identical mod 256 (only the low byte
 *        survives the `sb`), and both compile to a single `addiu`, but gcc-2.7.2
 *        picks a DIFFERENT immediate encoding for each source spelling: `cnt - 1`
 *        emits `addiu $v0,$v1,-1` (imm 0xFFFF, sign-extended -1); `cnt + 0xff`
 *        emits `addiu $v0,$v1,0xFF` (imm 0x00FF, the literal as typed) — which is
 *        what the target has. Confirmed the signedness of `cnt` (s8 vs u8) makes
 *        no difference here; the literal's own spelling is the lever. New
 *        cookbook idiom candidate (not in §31 as of this match).
 */

extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8018B530(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern int rand(void);
extern void func_8018B4B8(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern s32 func_80172630(u8 *a0);

void func_8018B364(s32 param_1)
{
    s16 buf[4];
    s32 i;
    s32 iVar1;
    s32 uVar3;
    s32 uVar4;
    s32 uVar5;
    s16 rnd;
    u8 cnt;

    func_80015978(param_1 + 4, (s32 *)buf);
    buf[1] -= 0x40;

    i = 0;
    do {
        iVar1 = func_8018B530();
        if (iVar1 >= 0) {
            func_80146A6C(0x51, (void *)param_1, buf[0], buf[1], buf[2], iVar1, 0);

            uVar3 = rand();
            uVar4 = rand();
            uVar5 = rand();
            rnd = (uVar3 & 3) * 0x400 + (uVar4 & 3) * 0xfa + (uVar5 & 3) * 0x44;
            func_80146A6C(0x52, (void *)param_1, 0, -0x20, 0x10, rnd, 0);
        }
        i++;
    } while (i < 3);

    cnt = *(u8 *)(param_1 + 0xde);
    *(u8 *)(param_1 + 0xde) = cnt + 0xff;
    if (cnt == 0) {
        func_8018B4B8(param_1);
        func_80159B3C((void *)param_1);
        func_80165718(param_1);
    } else {
        func_80172630((u8 *)param_1);
    }
}


extern void func_80147324(s32 a0);
extern void func_80147364(u16, s32);
extern void func_8014BC44(s32 a0, s32 a1);

/* func_8018B4B8 — actor "enter state 0x92F/0x930" stub: two sound/state pokes,
 * the standard `func_8014BC44(actor, actor->0xF2)` animation kick, set 0xA8 = 0x20,
 * then hand the actor to func_80151664.
 *
 * Two load-bearing derivations (both byte-verified against the .s):
 *
 *  1. The final call TAKES THE ACTOR. The .s sets `addu $a0,$s0,$zero` immediately
 *     before `jal func_80151664`, but the whole fleet declares
 *         extern void func_80151664(void);
 *     (16 TUs + engine_core.h:2924; ov_SC02_016_after.c:3151 records that a
 *     `void func_80151664(s32)` definition is `conflicting types` everywhere).
 *     So: cookbook idiom 9 — cast at the CALL SITE, never touch the decl:
 *         ((void (*)(s32))func_80151664)(a0)
 *     The .run/ghidra_c seed shows `FUN_80151664()` with no argument and is WRONG
 *     here; the .s wins. This is the single instruction the previous draft missed.
 *
 *  2. `sb $v0, 0xA8($a0)` uses $a0 — NOT $s0 — as its base, and lands in the jal's
 *     delay slot. That needs no local-variable lever (no `s32 s0 = a0;` as the
 *     sibling DEFINE_func_80152790 template uses): the arg copy into $a0 is emitted
 *     ahead of the store, so the store simply addresses off the live copy, and
 *     reorg.c then lifts the last pre-jal insn into the delay slot. Writing a
 *     separate pointer local here would only add a pseudo.
 *
 * Declaration surface (D2 pass over the whole TU, one grep):
 *   func_80147364  -> ov_SC02_016_jr_8017DC70.c:194,360  extern void (u16, s32)
 *   func_80147324  -> :196,777                           extern void (s32)
 *   func_8014BC44  -> :486                                extern void (s32, s32)
 *   func_80151664  -> :880                                extern void (void)  [re-declared
 *                     identically below, which is a legal duplicate declaration]
 *   func_8018B4B8  -> only the INCLUDE_ASM at :3587; no prior prototype anywhere in
 *                     ov_SC02_016 or include/. (The ov_SC03_09x definitions of this
 *                     name are other overlays sharing the VA — different binaries.)
 * Recompiled with those four prototypes prepended: still MATCH (21 ins).
 */

extern void func_80151664(void);

void func_8018B4B8(s32 a0)
{
    func_80147364(4, 0x92F);
    func_80147324(0x930);
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(a0);
}



void func_8018B50C(void)
{
    extern u8 D_801E19A3;
    s32 i = 19;
    u8 *p = &D_801E19A3;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}




s32 func_8018B530(void)
{

    extern u8 D_801E1990[];
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801E1990;
    do {
        if (*p == 0) {
            *p = v;
            ret = i;
            goto done;
        }
        i++;
        p++;
    } while (i < 20);
    ret = -1;
done:
    return ret;
}



extern void (*D_801D72C8[])(void);

void func_8018B574(void *a0) {
    D_801D72C8[*(u16 *)((s32)a0 + 0x2)]();
}






// @class: regalloc-order
// @stuck: none — MATCH (83 ins). $s3 is a dual-copy of iVar3 used only in the ==0 tail block; natural C coalesces to one $s0, so pin iVar3=$s0 and iVar3b=$s3 (different hard regs prevent gcc coalescing the copy). Also: outer+inner branch polarity inverted (if!=0 / if!=0 puts both short blocks at the tail as beqz targets); base = (int)D_801E19A4 + idx*0x40 (materialize form, arg to callees).

extern void func_801465C0(void);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_8018B7A4(void*);
extern void func_8018B774(s32*);
extern int rand(void);

void func_8018B5B0(int param_1)
{

    extern unsigned char D_801E19A4[];
    int iVar3;
    int iVar3b;
    int iVar5;
    short sVar2;

    iVar5 = (int)D_801E19A4 + *(int *)(param_1 + 0x2c) * 0x40;
    iVar3 = ((int (*)(void))func_801465C0)();
    iVar3b = iVar3;
    *(int *)(param_1 + 0x20) = iVar3;
    if (iVar3 != 0) {
        ((void (*)(int, int))func_8001CD9C)(iVar3, iVar5);
        ((void (*)(int, int))func_800233CC)(iVar5, 0x10);
        ((void (*)(int))func_8018B7A4)(iVar5);
        *(unsigned int *)(iVar3 + 4) = *(unsigned int *)(iVar3 + 4) | 0x50000000;
        if (*(int *)(param_1 + 0x2c) != 0) {
            sVar2 = (rand() & 3) * 0x800 + 0x1000;
            *(short *)(iVar3 + 0x1a) = sVar2;
            *(short *)(iVar3 + 0x18) = sVar2;
            *(unsigned short *)(param_1 + 0x12) = (rand() & 0xf) + 3;
            if ((rand() & 1) != 0) {
                *(short *)(param_1 + 0x12) = -*(short *)(param_1 + 0x12);
            }
            *(unsigned short *)(param_1 + 0x1a) = (rand() & 0xf) + 3;
            if ((rand() & 1) != 0) {
                *(short *)(param_1 + 0x1a) = -*(short *)(param_1 + 0x1a);
            }
        } else {
            *(short *)(iVar3b + 0x1a) = 0x4000;
            *(short *)(iVar3b + 0x18) = 0x4000;
        }
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    } else {
        ((void (*)(int))func_8018B774)(param_1);
    }
}




extern s32 func_8018B7B8(s32 *a0, s32 a1);
extern void func_8018B774(s32 *a0);

void func_8018B6FC(s32 *a0)
{

    extern unsigned char D_801E19A4[];
    s32 param;
    s32 table_base;

    param = *(s32 *)((s32)a0 + 0x2c);
    table_base = (s32)D_801E19A4 + param * 0x40;

    if (param != 0) {
        *(s16 *)((s32)a0 + 0x6) += *(s16 *)((s32)a0 + 0x12);
        *(s16 *)((s32)a0 + 0xE) += *(s16 *)((s32)a0 + 0x1A);

        if (func_8018B7B8(a0, table_base) == 0) {
            return;
        }
    }

    func_8018B774(a0);
}



















extern void func_80146C3C(void);
void func_8018B774(s32 *param_1)
{

    extern s8 D_801E1990;
  int new_var;
register s32 p __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
s32 r;
  p = (s32) (&D_801E1990);
  r = param_1[0x2c / 4];
  new_var = r;
  p += new_var;
  *((s8 *) p) = 0;
  ((void (*)(void)) func_80146C3C)();
}



void func_8018B7A4(void *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0xF0F0F0;
        *(s32 *)((s32)a0 + 0x4) = 0;
    }




/* func_8018B7B8 — scroll/advance one "text-ish" byte pair and pack it into a
 * 24-bit-ish word. Returns 1 when the decoded value is <= 0 (nothing written),
 * else stores the packed word through a1 and returns 0.
 *
 * Signature matches the in-TU forward declaration emitted by the func_80182678
 * draft: extern s32 func_8018B7B8(s32 *a0, s32 a1);
 *
 * Two derivations that mattered (both byte-verified against the .s):
 *  - Both `-0x20` subtractions and the `sll $v0,$a2,16` in the bnez delay slot
 *    are reorg.c fill-from-target duplicates, NOT source duplication: one
 *    `t -= 0x20` after the if reproduces them exactly.
 *  - `(t << 8) | (t | 0xFF0000)` written as ONE expression is reassociated by
 *    fold()'s associate/split_tree step into `t | ((t<<8) | 0xFF0000)`, which
 *    swaps $v0/$v1 on the two temps. Splitting it into three statements gives
 *    fold nothing to reassociate and reproduces the target's temp lifetimes
 *    (local-alloc's qty_compare gives the SHORT-lived temps the lower reg, so
 *    the long-lived `x` correctly lands in $v1 and the pair in $v0).
 */
s32 func_8018B7B8(s32 *a0, s32 a1) {
    s32 t;
    s32 ret;

    if (*(s32 *)((s32)a0 + 0x30) == 0) {
        t = *(u8 *)(a1 + 1);
    } else {
        t = *(u8 *)(a1 + 2);
    }
    t -= 0x20;
    ret = 1;
    if (t > 0) {
        if (*(s32 *)((s32)a0 + 0x30) == 0) {
            s32 x = t << 8;
            s32 y = t | 0xFF0000;
            t = x | y;
        } else {
            t = (t << 16) | 0xFFFF;
        }
        *(s32 *)a1 = t;
        ret = 0;
    }
    return ret;
}



extern void (*D_801D7300[])(void);

void func_8018B820(void *a0) {
    D_801D7300[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146E90(s32 *a0, s32 a1);

void func_8018B85C(s32 param_1)
{
    u8 pad[0x28];
    func_801495C4(*(s32 *)(param_1 + 0x34), param_1 + 0x4);
    func_80146E90((s32 *)param_1, 3);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}




extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();
extern void func_8018B8F8(s32 param_1);

void func_8018B8A8(s32 param) {
    if (func_80146E98(param) != 0) {
        ((void (*)(s32))func_80146C3C)(param);
    } else {
        func_8018B8F8(param);
    }
}


void func_8018B8F0(void) {
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8018BA5C();

void func_8018B8F8(s32 param_1) {

    extern u32 *D_801D72F8[];
    extern Blk8 D_801D7314[];
    s32 buf[2];
    Blk8 A;
    Blk8 B;
    Blk8 C;
    Blk8 D;
    u32 *basep;
    s32 i;
    s32 j;

    basep = D_801D72F8[*(s32 *)(param_1 + 0x30)];
    *(s16 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x2c);
    func_80015978(param_1 + 4, buf);
    for (j = 0; j < 4; j++) {
        *(s16 *)&A = 0;
        *((s16 *)&A + 1) = 0;
        *((s16 *)&A + 2) = 0;
        B = A;
        C = A;
        for (i = 0; i < 4; i++) {
            D = D_801D7314[i];
            *(s16 *)(param_1 + 0x12) = i + j;
            func_8018BA5C(param_1, buf, &A, &B, &C, &D, param_1 + 0x10, basep + i);
        }
    }
}


#include "common.h"
#include "../shared/engine_types.h"



// @class: regalloc-order
// @stuck: none — MATCH (223 ins). Giant GTE coord transform. Two levers: (1) vy = {int t=vy-0x10; t+(r&0x1f);}
//   blocks the (r&0x1f)-16 reassoc that materialized -0x10 via `li 0xfff0` (+1 ins); (2) inline the one-shot
//   r0_00+1 stsv arg so it stays a $v0 temp instead of stealing a saved reg from the reused pSVar6.

   /* 8, align 2 -> lwl/lwr copy */
  /* 0x20 */
    /* 4, align 1 -> lwl/lwr */

extern void func_80013F3C(s32);
extern void RotMatrixZ(s32, void *);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern int rand(void);
extern void func_80017714(void *);

extern SVECTOR_8017E6D8 D_801E1EA4[4];
extern struct PW8017E6D8 D_801E1EC4;
extern struct PW8017E6D8 D_801E1EC8;
extern u8 D_801E1ECC, D_801E1ECD, D_801E1ECE, D_801E1ED0, D_801E1ED1, D_801E1ED2;
extern int D_801E1ED4;


/* GTE VARIANT `gte_rt_m`: memory beyond Sony's `gte_rt` — a scheduling steer, its uses are marked (P36 T5) */
#define gte_rt_m()  __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 0, 0\n" \
    : : : "memory")


void func_8018BA5C(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d,
                   SVECTOR_8017E6D8 *e, SVECTOR_8017E6D8 *f, s16 *g, struct PW8017E6D8 *h)
{
    MATRIX_8017E6D8 m;
    SVECTOR_8017E6D8 *r0_00;
    SVECTOR_8017E6D8 *pSVar6;
    SVECTOR_8017E6D8 *r0;
    int r;
    int mask;

    func_80013F3C((s32)&m);
    RotMatrixZ(g[0], &m);
    m.t[0] = b[0];
    m.t[1] = b[1];
    m.t[2] = 0;
    func_8004914C(&m);
    func_800491AC(&m);

    r0_00 = &D_801E1EA4[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801E1ED4 = 0x50000000;
        D_801E1ECC = 0;
        D_801E1ECD = 0;
        D_801E1ECE = 0;
        D_801E1ED0 = 0;
        D_801E1ED1 = 0;
        D_801E1ED2 = 0;
    }
    D_801E1EC4 = h[0];
    D_801E1EC8 = h[1];

    f->vx = f->vx + c->vx;
    f->vy = f->vy + c->vy;
    r = rand();
    mask = f->pad & r;
    if (*(u16 *)(a + 0x12) & 1)
        f->vx = f->vx + mask;
    else
        f->vx = f->vx - mask;
    r = rand();
    { int t = f->vy - 0x10; f->vy = t + (r & 0x1f); }

    gte_ldv0(c);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    gte_stsv(r0_00);

    gte_ldv0(f);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    gte_stsv(r0_00 + 1);

    gte_ldv0(d);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    r0 = r0_00 + 2;
    gte_stsv(r0);

    *d = *f;
    r = rand();
    d->vx = d->vx - (f->pad & r);

    gte_ldv0(d);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    pSVar6 = r0_00 + 3;
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    gte_ldv0(e);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    gte_stsv(r0);

    *e = *f;
    r = rand();
    e->vx = e->vx + (f->pad & r);

    gte_ldv0(e);
    gte_rt_m();  // !FAKE: gte via gte_rt_m — memory beyond Sony's `gte_rt` (P36 T5 gte2)
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    *c = *f;
}




extern void (*D_801D7358[])(void);

void func_8018BDD8(void *a0) {
    D_801D7358[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018BE14(s32 a0) {
    extern u8 D_801D7334;
    extern void func_8018BE68(s32 a0);
    s32 s0 = a0;
    *(s32 *)(s0 + 0x1B4) = (s32)&D_801D7334;
    func_8014E934(a0);
    func_8014CC28(s0);
    func_8014F3E8(s0);
    func_8018BE68(s0);
    func_80146CA0((void *)s0);
}


extern u8 D_80062BF4[];
extern void func_80019064(void *a0);
extern void func_80149020(s32 *a0);
extern void func_80147324(s32 a0);
extern int func_801511E0(int arg);
extern s32 func_80012A60(s32 a0, s32 a1);
extern M2C_UNK D_800D5880;
extern s32 D_800D58AC;
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_8018BE68(s32 param_1)
{
    short ret;

    func_80019064(D_80062BF4);
    func_80149020((s32 *)param_1);
    func_80147324(0x451);
    func_801511E0(param_1);
    ret = func_80012A60(*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), *(s16 *)(param_1 + 0xF4));
    if (ret > 0x400) {
        func_80154274((s32 *)param_1, (s32)&D_800D5880);
    } else {
        func_80154274((s32 *)param_1, (s32)&D_800D58AC);
    }
    func_80154A74(param_1, 0x16);
    func_80149020((s32 *)param_1);
    func_80146CA0((void *)param_1);
}


#include "common.h"

extern void func_80149020(s32 *a0);
extern void func_8018BF88(s32 a0);
extern void func_80159B3C(void *a0);
extern M2C_UNK D_800D5880;
extern void func_801542DC(s32 *a0, s32 a1);
extern u8 D_800D46E4[];
extern void func_80165718(s32 a0);

void func_8018BF1C(s32 arg0)
{
    func_80149020(arg0);
    *(s32 *)(arg0 + 0x1B0) = 0x12C;
    func_8018BF88(arg0);
    func_80159B3C((void *)arg0);
    if (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D5880) {
        ((void (*)(s32, s32, s32))func_801542DC)(arg0, (s32)D_800D46E4, 0xE);
    }
    func_80165718(arg0);
}


extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80151664(void);

void func_8018BF88(s32 a0)
{
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(a0);
}



extern s32 D_801E2018;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_8018BFC8(s32 a0, s32 a1) {
    D_801E2018 = a1;
    return func_8012C588(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801E2018;
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80134510(s32 arg);

// @class: regalloc-order
// @stuck: none — MATCH (145/145 ins, match_one confirmed)




s32 func_8018BFF8(s32 param_1) {

    extern M2C_UNK D_8018C894;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801D9948;
    extern char * D_801D997C;
    extern char D_801E1FF8[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801D9948) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_8018C894));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801E2018, &s60);
    s50 = s60;
    sStack_58.vz = 0x1800;
    sStack_58.vy = 0x1800;
    sStack_58.vx = 0x1800;
    ((void (*)(void *, void *))func_80017DC4)(&sStack_58, auStack_48);
    RotMatrixZ(rand() & 0xfff, auStack_48);
    MulMatrix0(iVar8, auStack_48, iVar5 + 0x34);
    ((void (*)(void *, s32))func_80017E68)(&s50, iVar5 + 0x34);

    /* pool-alloc: gcc routes the loaded pointer through a caller-saved reg ($v0)
       before the callee-saved home ($s1) — pin it to reproduce the extra move. */
    {
        register char *tmp __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
        tmp = D_801D997C;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801D997C = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801E1FF8 < puVar4) {
        D_801D997C = D_801E1FF8 - 0x120;
    }
    func_800D20C0(&s60, &sStack_58, 7);
    func_800D23D0(&sStack_58);
    ((void(*)(void *, void *))RotMatrixYXZ)(&sStack_58, puVar2);
    ((void (*)(void *, s32))func_80017E68)(&s60, (s32)puVar2);

    uVar3 = *(u16 *)((char *)&s50 + 2);
    if (((s32 (*)(void *))func_80134510)(&s50) != 0 &&
        (s32)(s16)uVar3 - (s32)*(s16 *)((char *)&s50 + 2) < 0x80) {
        *(s16 *)((char *)&s50 + 2) = *(s16 *)((char *)&s50 + 2) - 4;
        {
            register char *tmp __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
            tmp = D_801D997C;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801D997C = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801E1FF8 < puVar4) {
            D_801D997C = D_801E1FF8 - 0x120;
        }
        func_800D23D0(&(*(s32 *)&D_801152A8));
        ((void(*)(void *, void *))RotMatrixYXZ)(&(*(s32 *)&D_801152A8), puVar2);
        ((void (*)(void *, s32))func_80017E68)(&s50, (s32)puVar2);
    }
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


extern s32 func_80017758(void *a0, void *a1);
extern void func_8012C218(void *a0);


// @class: regalloc-order
// @stuck: none — MATCH (168 ins). Keys: (1) pin param->$s1 via `register int self __asm__("$17")=param_1`
//   (natural alloc put the short loop-counter in $s1); (2) block2's guarded dest via a test-temp
//   `td=load; if(td){dest=td; ...}` forces the range-split `lw $a1; addu $s3,$a1,$0` the target has;
//   (3) counter is `short i` do-while (keeps the `addu $s2,$v0,$0` raw-copy + sll16/sra16 compare);
//   (4) gcc-2.7.2 loads s8/s16 via lbu/lhu+shift-extend (not lb/lh) so `signed char *p; *(s16*)buf=*p++`
//   emits lbu;sll24;sra24;sh; (5) else-branch zero-byte asm barrier forces `addu $a0,$s1,$0` (else gcc
//   reuses the still-live incoming $a0 with a nop delay slot).

s32 func_8018C23C(s32 param_1) {

    extern signed char D_801D9934[];
    int self = ((int)param_1);
    int iVar6;
    int iVar1;
    unsigned char buf[0x34];
    signed char *p;
    short i;
    int dest;
    int td;
    unsigned short t;

    do { iVar1 = *(int *)(self + 0x1c); } while (0);
    iVar6 = *(int *)(self + 0x20);
    *(int *)(self + 0x1c) = iVar1 + 1;
    if (iVar1 < 2) {
        p = D_801D9934;
        i = 0;
        dest = *(int *)(self + 0xcc);
        t = *(unsigned short *)(self + 0x70);
        *(short *)(buf + 0x0c) = 0;
        *(short *)(buf + 0x0a) = 0;
        *(short *)(buf + 0x08) = 0;
        *(short *)(buf + 0x1c) = 0;
        *(short *)(buf + 0x14) = 0;
        *(short *)(buf + 0x04) = 0;
        buf[0x22] = 0;
        buf[0x21] = 0;
        buf[0x20] = 0;
        buf[0x2a] = 0;
        buf[0x29] = 0;
        buf[0x28] = 0;
        buf[0x2e] = 0;
        buf[0x2d] = 0;
        buf[0x2c] = 0;
        *(int *)(buf + 0x30) = 0x50000000;
        buf[0x25] = t;
        buf[0x26] = t;
        buf[0x24] = t;
        do {
            *(short *)(buf + 0x00) = *p++;
            *(short *)(buf + 0x02) = *p++;
            *(short *)(buf + 0x10) = *p++;
            *(short *)(buf + 0x12) = *p++;
            *(short *)(buf + 0x18) = *p++;
            *(short *)(buf + 0x1a) = *p--;
            func_80017758(buf, (void *)dest);
            i++;
        } while (i < 4);

        td = *(int *)(self + 0xd0);
        if (td != 0) {
            dest = td;
            p = D_801D9934;
            i = 0;
            t = *(unsigned short *)(self + 0x70);
            *(short *)(buf + 0x0c) = 0;
            *(short *)(buf + 0x0a) = 0;
            *(short *)(buf + 0x08) = 0;
            *(short *)(buf + 0x1c) = 0;
            *(short *)(buf + 0x14) = 0;
            *(short *)(buf + 0x04) = 0;
            buf[0x22] = 0;
            buf[0x21] = 0;
            buf[0x20] = 0;
            buf[0x2a] = 0;
            buf[0x29] = 0;
            buf[0x28] = 0;
            buf[0x2e] = 0;
            buf[0x2d] = 0;
            buf[0x2c] = 0;
            *(int *)(buf + 0x30) = 0x50000000;
            buf[0x25] = t;
            buf[0x26] = t;
            buf[0x24] = t;
            do {
                *(short *)(buf + 0x00) = *p++;
                *(short *)(buf + 0x02) = *p++;
                *(short *)(buf + 0x10) = *p++;
                *(short *)(buf + 0x12) = *p++;
                *(short *)(buf + 0x18) = *p++;
                *(short *)(buf + 0x1a) = *p--;
                func_80017758(buf, (void *)dest);
                i++;
            } while (i < 4);
        }
        do { *(short *)(self + 0x70) = *(short *)(self + 0x70) >> 1; } while (0);
        *(unsigned short *)(iVar6 + 0x2c) |= 1;
    } else {
        func_8012C218((void *)self);
    }
}



extern void (*D_801D9980[])(void);

void func_8018C4DC(void *a0) {
    D_801D9980[*(u16 *)((s32)a0 + 0x2)]();
}








