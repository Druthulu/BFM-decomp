#include "common.h"
#include "../shared/engine_core.h"


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
/* ==== end §8b carried decl layer ==== */


// @class: inlined-helper (cookbook §82.1)
// @stuck: none — MATCH (238/238 ins, match_one confirmed, symbol order verified)
// Key: region 1 re-materialises `addiu $aN,$sp,0x88` / `...,0x90` at call sites SEPARATED BY A
//   `jal`. Per §82.1 (`&X` for any non-first local always makes a pseudo and CSE always merges
//   two of them; expr.c:6260 ADDR_EXPR -> force_operand(...,NULL)), that duplication is only
//   reachable if those sites are NOT in the same function body => the setup block was a
//   `static inline` helper. Probed: at -O2 a flat body hoists &buf2/&vec into $s0/$s1 (+$s2 for
//   the param) — 241/242 ins, +3/+4 — and NO barrier reaches it (empty asm, "memory" clobber,
//   volatile array, real BB splits were all ablated and all still hoisted).
// Corollary that falls out of the same law: `mtx` is the caller's FIRST local (virtual-stack-vars
//   offset 0), so `&mtx` is a bare reg and re-materialises as `addiu $a1,$sp,0x10` in the loops;
//   it only lands in $s0 for region 1 because it crosses the inline boundary AS A POINTER PARAM.
#include "common.h"

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80017758(void *a0, void *a1);
extern u16 D_800B99DA;
extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern u16 D_801922AC;
extern u16 D_801922AE;
extern u16 D_801922B0;
extern u16 D_801922B4;
extern u16 D_801922B6;
extern u16 D_801922B8;
extern u8 D_801922BC[];
extern signed char D_8018F650[];
extern signed char D_8018F664[];

typedef struct {
    s16 vx, vy, vz, pad;
} SV_80188D90;

typedef struct {
    SV_80188D90 v[4];       /* 0x00 */
    u8          c[4][4];    /* 0x20 */
    u32         code;       /* 0x30 */
    u8          tail[0x24]; /* 0x34 */
} Prim_80188D90;            /* 0x58 */

static inline void setup_80188D90(s32 a0, void *mtx) {
    s16 buf2[4];
    s16 vec[4];
    s32 diff[3];

    func_8012F214(a0, (s32)D_801922BC, (s32)buf2);
    func_800D20C0(buf2, vec, 8);
    func_80017E68(buf2, mtx);

    vec[0] = D_801922AC - D_801922B4;
    vec[1] = D_801922AE - D_801922B6;
    vec[2] = D_801922B0 - D_801922B8;
    ApplyMatrixSV((void *)(*(s32 *)(a0 + 0x20) + 0x34), vec, vec);
    func_800D23D0(vec);
    RotMatrixYXZ(vec, mtx);

    diff[0] = D_801269A4 - buf2[0];
    diff[1] = D_801269A8 - buf2[1];
    diff[2] = D_801269AC - buf2[2];
    ApplyTransposeMatrixLV(mtx, diff, diff);
    vec[2] = -ratan2(diff[0], diff[1]);
    RotMatrixYXZ(vec, mtx);
}


void func_801867D0(s32 param_1) {
    extern void func_8012E88C(u8 *a0);
    extern void func_8012AD80(s32 a0);
    extern void func_8012B23C(s32 a0);
    extern s32 func_801789AC(s32 arg0);
    extern void func_80178D18(void);
    extern void func_8012C218(void *a0);
    extern void func_80029514(s32 a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_800D1724(s32 a0);
    extern s32 D_801DFF6C;
    extern s32 D_801DFF70;
    extern s32 D_801DFF74;
    extern s32 D_801DFF80;
    extern s32 D_801DFF84;
    extern s16 D_8018FFFC;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 1:
        func_8012E88C((u8 *)D_801DFF6C);
        func_8012E88C((u8 *)D_801DFF70);
        func_8012E88C((u8 *)D_801DFF74);
        func_8012E88C((u8 *)D_801DFF80);
        func_8012E88C((u8 *)D_801DFF84);
        *(s32 *)(param_1 + 0x1C) = 0x48;
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        func_8002D4C8(0xBD2, 0);
        break;
    case 2:
        func_8012AD80(D_801DFF6C);
        func_8012AD80(D_801DFF70);
        func_8012AD80(D_801DFF74);
        func_8012AD80(D_801DFF80);
        func_8012AD80(D_801DFF84);
        break;
    case 0:
    case 3:
    case 5:
    case 6:
        break;
    case 4:
        if (*(s16 *)(D_801DFF6C + 0x98) == 0) {
            func_8012B23C(D_801DFF6C);
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        }
        break;
    }

    if (func_801789AC(param_1) == 1) {
        func_80029514(0x636);
        ((void (*)(s32))func_80178D18)(param_1);
        func_8012C218((void *)param_1);
        func_800D1724((s32)&D_8018FFFC);
    }
}


extern void func_8012BEE8(void);
void func_80186960(void) {
    func_8012BEE8();
}


extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801B956C;
extern s32 D_801DFF6C;
extern void (*D_801D4D0C)();

void func_80186980(s32 param_1) {
    func_8012A828(D_801DFF6C, *(void **)(param_1 + 0xF8));
    if (*(s32 *)(param_1 + 0xF8) == (s32)&D_801B956C) {
        if (*(s32 *)(D_801DFF6C + 0x6C) != 0) {
            func_8012A828(*(s32 *)(D_801DFF6C + 0x6C), &D_801D4D0C);
        }
    }
}


extern s32 D_801DFF70;
extern void func_8012A828(s32 a0, void *a1);

void func_801869F8(s32 param_1) {
    func_8012A828(D_801DFF70, *(void **)(param_1 + 0xF8));
}


extern s32 D_801DFF74;
extern void func_8012A828(s32 a0, void *a1);

void func_80186A28(s32 param_1) {
    func_8012A828(D_801DFF74, *(void **)(param_1 + 0xF8));
}


extern s32 D_801DFF78;
extern void func_8012A828(s32 a0, void *a1);

void func_80186A58(s32 param_1) {
    func_8012A828(D_801DFF78, *(void **)(param_1 + 0xF8));
}


extern s32 D_801DFF7C;
extern void func_8012A828(s32 a0, void *a1);

void func_80186A88(s32 param_1) {
    func_8012A828(D_801DFF7C, *(void **)(param_1 + 0xF8));
}


extern s32 D_801DFF6C;
extern s32 D_801BC8A4[];
extern void func_8001C924(void *a0, s32 *a1);

s32 func_80186AB8(void) {
    s32 v0;

    if (*(s32 *)(D_801DFF6C + 0x94) == 0x16) {
        func_8001C924((void *)*(s32 *)(D_801DFF6C + 0x20), D_801BC8A4);
        v0 = 1;
    } else {
        v0 = 0;
    }
    return v0;
}


extern s32 D_801BC8A4[];
extern s32 D_801DFF8C[];
extern u8 D_801DFF9C[];
extern s32 D_801BCF0C;
extern s32 D_801DFF6C;
extern void func_8001C924(void *a0, s32 *a1);

void func_80186B00(void) {
    s32 off;
    for (off = 0; off < 0x2C; off += 4) {
        *(s32 *)((u8 *)&D_801DFF8C + off) = *(s32 *)((u8 *)&D_801BC8A4 + off);
    }
    *(s32 *)&D_801DFF9C = D_801BCF0C;
    func_8001C924((void *)*(s32 *)(D_801DFF6C + 0x20), (s32 *)((u8 *)&D_801DFF9C - 0x10));
}


#include "common.h"

extern s32 D_801DFF6C;
extern u8 D_8018CCE8;

extern void func_8012CBCC(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

s32 func_80186B6C(void) {
    s32 v0;
    s32 v1;

    if ((((s32 (*)(s32))func_8012CBCC)(D_801DFF6C) & 0x2000) != 0) {
        func_8013C9C4(&D_8018CCE8);
        v0 = -0x180;
        v1 = D_801DFF6C;
        *(u16 *)(v1 + 0x6) = v0;
        *(u16 *)(v1 + 0xE) = v0;
        func_8002D4C8(0xB96, 0);
        return 1;
    }
    return 0;
}


extern s32 D_801DFF6C;

s32 func_80186BD4(void) {
    return *(s16 *)(D_801DFF6C + 0x98) == 0;
}


extern s32 D_801DFF78;
extern void func_8012E88C(u8 *a0);

void func_80186BEC(void) {
    ((void (*)(s32))func_8012E88C)(*(s32 *)&D_801DFF78);
}


extern s32 D_801DFF78;
extern void func_8012E8A8(u8 *a0);

void func_80186C14(void) {
    ((void (*)(s32))func_8012E8A8)(D_801DFF78);
}


extern void func_8012AD80(s32 a0);
extern s32 D_801DFF78;

s32 func_80186C3C(s32 param_1)
{
    s16 v;
    func_8012AD80(D_801DFF78);
    v = *(u16 *)(param_1 + 0x10A) - 1;
    *(u16 *)(param_1 + 0x10A) = v;
    return v == 0;
}


extern s32 D_801DFF78;

s32 func_80186C88(void) {
    if (*(s16 *)(D_801DFF78 + 0x98) == 0 || *(u16 *)(D_801DFF78 + 0x72) & 0x4000) {
        return 1;
    }
    return 0;
}


extern s32 D_801DFFB8;
extern s32 D_801BF990[];
extern u8 D_801DFFD4[];
extern s32 D_801DFF70;
extern s32 D_801BF2BC;

extern void func_8001C924(void *a0, s32 *a1);

void func_80186CC4(void) {
    s32 off;

    for (off = 0; off < 0x24; off += 4) {
        *(s32 *)((u8 *)&D_801DFFB8 + off) = *(s32 *)((u8 *)&D_801BF2BC + off);
    }
    *(s32 *)&D_801DFFD4 = D_801BF990[0];
    func_8001C924((void *)*(s32 *)(D_801DFF70 + 0x20), (s32 *)((u8 *)&D_801DFFD4 - 0x1C));
}


extern void func_8001C924(void *a0, s32 *a1);
extern s32 D_801DFF70;
extern s32 D_801BF2BC;

void func_80186D30(void) {
    func_8001C924((void *)*(s32 *)(D_801DFF70 + 0x20), &D_801BF2BC);
}


extern s32 D_801DFF74;

s32 func_80186D64(void) {
    if (*(s16 *)(D_801DFF74 + 0x98) == 0 || *(u16 *)(D_801DFF74 + 0x72) & 0x4000) {
        return 1;
    }
    return 0;
}


#include "common.h"

extern s32 D_801DFF70;
extern u16 D_80191234;
extern s32 D_801C2AA4;
extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_80186DA0(void) {
    *(s16 *)(*(s32 *)(D_801DFF70 + 0x20) + 0x12) = func_8012B744((void *)(D_801DFF70 + 4), &D_80191234);
    func_8012B2CC(D_801DFF70);
    func_8012B178(D_801DFF70, -0x100000);
    *(s32 *)(D_801DFF70 + 0x48) = 0xC000;
    *(s16 *)(D_801DFF70 + 0x34) = 0;
    func_8012A828(D_801DFF70, &D_801C2AA4);
}


#include "common.h"

extern s32 D_801DFF70;
extern s32 D_801C2AA4;
extern s32 D_801C2AEC;
extern u16 D_8019123C;
extern u16 D_8019123E;
extern u16 D_80191240;
extern u8 D_8018CCE8;

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012CBCC(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

s32 func_80186E18(s32 a0) {
    register s32 state __asm__("$4");

    state = D_801DFF70;
    if (*(s32 *)(state + 0x90) == (s32)&D_801C2AA4 && *(s16 *)(state + 0x98) == 0) {
        func_8012A828(state, &D_801C2AEC);
    }

    state = D_801DFF70;
    *(u16 *)(*(s32 *)(state + 0x20) + 0x10) += 0x20;

    if (*(u16 *)(state + 0x34) != 0) {
        s32 v1;

        if ((((s32 (*)(void))func_8012CBCC)() & 0x2000) == 0) {
            return 0;
        }

        v1 = D_801DFF70;
        *(u16 *)(*(s32 *)(v1 + 0x20) + 0x10) = 0;
        *(u16 *)(*(s32 *)(v1 + 0x20) + 0x12) = 0xA00;
        *(u16 *)(v1 + 0x34) = 0;
        *(u16 *)(v1 + 0x6) = D_8019123C;
        *(u16 *)(v1 + 0xA) = D_8019123E;
        *(u16 *)(v1 + 0xE) = D_80191240;
        func_8013C9C4(&D_8018CCE8);
        func_8002D4C8(0xB97, 0);
        *(s32 *)(a0 + 0xD4) = D_801DFF70;
        return 1;
    } else {
        s32 v0;

        if ((((s32 (*)(void))func_8012CBCC)() & 0x2000) == 0) {
            return 0;
        }

        v0 = D_801DFF70;
        *(s32 *)(v0 + 0x14) = 0xFFF30000;
        *(u16 *)(v0 + 0x34) = *(u16 *)(v0 + 0x34) + 1;
        func_8013C9C4(&D_8018CCE8);
        func_80143B6C(D_801DFF70, 1);
        func_8002D4C8(0xB97, 0);
        return 0;
    }
}


extern s32 D_801DFF7C;
extern void func_8012E88C(u8 *a0);

void func_80186F9C(void) {
    ((void (*)(s32))func_8012E88C)(D_801DFF7C);
}


extern s32 D_801DFF7C;

s32 func_80186FC4(void) {
    u16 *obj = (u16 *)*(s32 *)(D_801DFF7C + 0x20);

    obj[0xC] = obj[0xC] + 0xC0;
    obj[0xD] = obj[0xD] + 0xC0;
    obj[0xE] = obj[0xE] + 0xC0;

    if (*(s16 *)&obj[0xC] >= 0x3000) {
        obj[0xE] = 0x3000;
        obj[0xD] = 0x3000;
        obj[0xC] = 0x3000;
        return 1;
    }
    return 0;
}


void func_8018702C(s32 a0) {
    extern u16 D_8019122C[];
    extern s32 D_801DFF74;
    extern void func_8012B2CC(s32 a0);
    s32 prim;
    s32 tbl;
    s32 v0;

    prim = D_801DFF74;
    tbl = (s32)D_8019122C;
    v0 = *(s16 *)(a0 + 0x10A) << 3;
    *(s16 *)(prim + 6) = *(u16 *)(tbl + v0);
    *(s16 *)(prim + 0xA) = *(u16 *)(tbl + v0 + 2);
    *(s16 *)(prim + 0xE) = *(u16 *)(tbl + v0 + 4);
    *(s16 *)(*(s32 *)(prim + 0x20) + 0x12) = *(u16 *)(tbl + v0 + 6);
    func_8012B2CC(prim);
}


extern s32 func_8018B1E0(s32);
void func_80187094(void) {
    ((void (*)(int))func_8018B1E0)(0x6);
}


extern s32 func_8018B20C(void);
void func_801870B4(void) {
    ((void (*)(void))func_8018B20C)();
}


extern s32 D_801DFF70;
extern s32 D_801DFF6C;
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);

s32 func_801870D4(s32 arg0) {
    s32 temp;
    s32 ret;

    temp = func_8012B6D4((s16 *)(D_801DFF70 + 4), (s16 *)(D_801DFF6C + 4));
    ret = func_8012B608(*(s16 *)(*(s32 *)(D_801DFF70 + 0x20) + 0x12), temp, 0x8);
    *(u16 *)(*(s32 *)(D_801DFF70 + 0x20) + 0x12) += ret;
    return ret == 0;
}


extern s32 D_801DFF70;
extern s32 D_801DFF7C;
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);

s32 func_80187148(s32 arg0) {
    s32 temp;
    s32 ret;

    temp = func_8012B6D4((s16 *)(D_801DFF70 + 4), (s16 *)(D_801DFF7C + 4));
    ret = func_8012B608(*(s16 *)(*(s32 *)(D_801DFF70 + 0x20) + 0x12), temp, 0x8);
    *(u16 *)(*(s32 *)(D_801DFF70 + 0x20) + 0x12) += ret;
    if (ret == 0) {
        *(s32 *)(arg0 + 0xD4) = D_801DFF7C;
        return 1;
    }
    return 0;
}


extern s32 D_801DFF70;
extern s32 func_8012BA10(s32 a0, s32 a1);

s32 func_801871E8(void) {
    s32 ret;
    void *a1;

    ret = func_8012BA10(D_801DFF70, 8);
    a1 = *(void **)(D_801DFF70 + 0x20);
    *(u16 *)(a1 + 0x12) += ret;
    return ret == 0;
}


extern s32 D_801DFF70;
extern u16 D_8019126C;
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);

s32 func_80187230(s32 arg0) {
    s32 ret;

    ret = func_8012B608(*(s16 *)(*(s32 *)(D_801DFF70 + 0x20) + 0x12),
                        func_8012B744((void *)(D_801DFF70 + 4), &D_8019126C), 4);
    *(u16 *)(*(s32 *)(D_801DFF70 + 0x20) + 0x12) += ret;
    if (ret == 0) {
        *(s32 *)(arg0 + 0xD4) = D_801DFF70;
        return 1;
    }
    return 0;
}


extern void func_800D0C48(s32 arg);
    void func_801872C4(void) {
        func_800D0C48(0x1);
    }


extern s32 func_8001AAA0(s32 arg);
    s32 func_801872E4(void) {
        return func_8001AAA0(0x95) != 0;
    }


extern s32 D_801DFF7C;
extern s32 D_801B25D0;
extern s32 D_8018CCC4;
extern void func_8013C9C4(void *a0);
extern void func_80187D64(s32 arg0);

s32 func_80187304(void) {
    if (*(s16 *)(D_801DFF7C + 0x98) == 0) {
        if (*(s32 *)(D_801DFF7C + 0x90) == (s32)&D_801B25D0) {
            func_8013C9C4(&D_8018CCC4);
            func_80187D64(D_801DFF7C);
        }
        return 1;
    }
    return 0;
}


extern s32 D_801DFF74;
extern void func_8012E8A8(u8 *a0);

void func_8018736C(void) {
    ((void (*)(s32))func_8012E8A8)(D_801DFF74);
}


#include "common.h"

extern s32 D_801DFF7C;
extern u8 D_801B2B80;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);

void func_80187394(void)
{
    s32 p;
    s32 v1;

    p = D_801DFF7C;
    v1 = *(s32 *)((u8 *)p + 0x20);
    *(s16 *)((u8 *)p + 6) = -0x100;
    *(s16 *)((u8 *)p + 0xA) = -0x302;
    *(s16 *)((u8 *)p + 0xE) = -0x1C0;
    *(s16 *)(v1 + 0x12) = 0x200;
    func_8012A828(p, &D_801B2B80);
    func_8012B2CC(D_801DFF7C);
}


extern s32 D_801DFF74;
extern s32 func_8012BA10(s32 a0, s32 a1);

s32 func_801873F4(void) {
    s32 ret;
    void *a1;

    ret = func_8012BA10(D_801DFF74, 8);
    a1 = *(void **)(D_801DFF74 + 0x20);
    *(u16 *)(a1 + 0x12) += ret;
    return ret == 0;
}


#include "common.h"

extern s32 D_801DFF88;
extern s32 D_801DFF74;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_80191254[];

extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_8012B77C(s32 out, s32 from, s32 to);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012E88C(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_80013350(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);

typedef struct {
    s16 f0, f2, f4, f6, f8, fA, fC, fE;
} Pos16_8018743C;

s32 func_8018743C(void) {
    s32 vec[4];              /* sp+0x10 */
    s32 mtx[8];              /* sp+0x20 */
    s16 sv[4];               /* sp+0x40 */
    Pos16_8018743C from;     /* sp+0x48 */
    Pos16_8018743C to;       /* sp+0x58 */
    s32 ang[2];              /* sp+0x68 */
    s32 w;
    s32 n;

    if (*(u16 *)(D_801DFF88 + 0x34) == 0) {
        func_8012EC04(D_801DFF74, 4, mtx);
        func_8012F14C((s32)mtx, (s32)D_80191254, (s32)sv);

        *(s16 *)(D_801DFF88 + 0x6) = D_80126B5E;
        from.f2 = D_80126B5E;
        *(s16 *)(D_801DFF88 + 0xA) = D_80126B62 - 0x30;
        from.f6 = D_80126B62 - 0x30;
        *(s16 *)(D_801DFF88 + 0xE) = D_80126B66;
        from.fA = D_80126B66;
        to.f2 = sv[0];
        to.f6 = sv[1];
        to.fA = sv[2];
        func_8012B77C((s32)ang, (s32)&from, (s32)&to);

        w = ang[0];
        *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x12) = w >> 16;
        sv[0] = w;
        sv[1] = w >> 16;
        sv[2] = 0;
        vec[0] = 0;
        vec[1] = -0x100000;
        vec[2] = -0x180000;
        func_80049CAC((s32)sv, (s32)mtx);
        func_800484EC((s32)mtx, (s32)vec, D_801DFF88 + 0x10);
        func_8012E88C((u8 *)D_801DFF88);

        *(s32 *)(D_801DFF88 + 0x1C) = 0;
        *(s16 *)(D_801DFF88 + 0x34) = *(u16 *)(D_801DFF88 + 0x34) + 1;
        func_8002D4C8(0xBD7, 0);
        return 0;
    }

    *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x10) + 0x100;
    n = *(s32 *)(D_801DFF88 + 0x1C) + 1;
    *(s32 *)(D_801DFF88 + 0x1C) = n;
    if ((n & 0xF) == 0) {
        func_8002D4C8(0xBD6, 0);
    }
    func_8012AD80(D_801DFF88);
    if (func_80013350(D_801DFF88 + 4, D_801DFF74 + 4) >= 0x4001) {
        return 0;
    }
    *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x10) = 0x800;
    *(s16 *)(D_801DFF88 + 0x6) = 0x16F;
    *(s16 *)(D_801DFF88 + 0xA) = -0x264;
    *(s16 *)(D_801DFF88 + 0x34) = 0;
    *(s16 *)(D_801DFF88 + 0xE) = -0x1DA;
    func_8012B2CC(D_801DFF88);
    return 1;
}


#include "common.h"

extern s32 D_801DFF88;
extern u32 D_801DFF68;
extern s32 D_8018CCC4;
extern u8  D_801202A0[];
extern u16 D_8019127C[];
extern u16 D_801912AC;
extern u16 D_801912AE;
extern u16 D_801912B0;
extern u16 D_80191274;
extern u16 D_80191276;
extern u16 D_80191278;

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32  func_8012CC40(s32 a0, s16 *a1);
extern void func_8013C9C4(void *a0);
extern s32  func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8012C218(void *a0);
extern s32  func_8012C588(s32 a0, s32 a1);

void func_80187660(s32 arg0)
{
    s16 sp10[3];
    s32 i;
    u8 *p;
    s16 t;

    switch (*(u16 *)(D_801DFF88 + 0x34)) {
    case 0:
        func_8002D4C8(0xBD7, 0);
        *(s16 *)(D_801DFF88 + 0x10A) = 1;
        *(s16 *)(D_801DFF88 + 0x34) = *(u16 *)(D_801DFF88 + 0x34) + 1;
        /* fallthrough */
    case 1:
        func_8012AD80(D_801DFF88);
        if (*(s32 *)(D_801DFF88 + 0x14) >= 0) {
            *(s16 *)(D_801DFF88 + 0x34) = *(u16 *)(D_801DFF88 + 0x34) + 1;
            *(u16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x2C) |= 0x10;
            *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x10) = 0;
            *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x18) =
                *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x1A) =
                    *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x1C) = 0x4000;
            *(s16 *)(D_801DFF88 + 0x6) = 0;
            *(s16 *)(D_801DFF88 + 0xE) = 0;
            D_801912B0 = 0x80;
            D_801912AE = 0x80;
            D_801912AC = 0x80;
        }
        break;
    case 2:
        sp10[2] = 0;
        sp10[0] = 0;
        sp10[1] = 0x80;
        if (func_8012CC40(D_801DFF88, sp10) & 0x2000) {
            *(s16 *)(D_801DFF88 + 0x34) = *(u16 *)(D_801DFF88 + 0x34) + 1;
            func_8013C9C4(&D_8018CCC4);
            *(u16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x2C) |= 0xA0;
            *(s32 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x80) = (s32)&D_8019127C;
            *(u32 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x4) |= 0x50000000;
            for (i = 0; i < 4; i++) {
                func_8012C658(0x3C7, i, arg0);
            }
            func_8002D4C8(0x81D, 0);
        }
        break;
    case 3:
        t = D_801912B0 + 8;
        D_801912B0 = t;
        D_801912AE = t;
        D_801912AC = t;
        if (t >= 0x101) {
            *(s16 *)(D_801DFF88 + 0x34) = *(u16 *)(D_801DFF88 + 0x34) + 1;
        }
        break;
    case 4:
        t = D_801912B0 - 8;
        D_801912B0 = t;
        D_801912AE = t;
        D_801912AC = t;
        if (t < -0x80) {
            *(s16 *)(D_801DFF88 + 0x34) = *(u16 *)(D_801DFF88 + 0x34) + 1;
            *(u16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x2C) &= 0xFF4F;
            *(u32 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x4) &= 0xEFFFFFFF;
            *(s16 *)(D_801DFF88 + 0x6) = D_80191274;
            *(s16 *)(D_801DFF88 + 0xA) = D_80191276;
            *(s16 *)(D_801DFF88 + 0xE) = D_80191278;
            *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x10) = -0x200;
            *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x12) = -0x80;
            *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x14) = 0x400;
            *(s16 *)(D_801DFF88 + 0x10A) = 0;
            func_8012B2CC(arg0);
            func_8012E8A8((u8 *)D_801DFF88);
            i = 0;
            p = D_801202A0;
            do {
                if (*(u16 *)p == 0x3C7) {
                    func_8012C218(p);
                }
                p += 0x10C;
                i++;
            } while (i < 0x60);
            D_801DFF68 = 1;
            func_8012C588(0x3D3, arg0);
            func_8012C658(0x3D3, 1, arg0);
        }
        break;
    }
}


#include "common.h"

/* Local struct shapes only for byte-match purposes (spelled fresh; not declared elsewhere
 * in this TU, so no canonical-name collision per rule 2). */
typedef struct { s16 vx, vy, vz, pad; } SVec_80187A04;
typedef struct { s16 m[3][3]; s32 t[3]; } Mat_80187A04;
typedef struct { s32 vx, vy, vz; } Vec_80187A04;

extern u16 D_80126B5E;
extern u16 D_80126B66;
extern s32 D_801DFF88;
extern Blk20 D_800AE620;
extern Vec_80187A04 D_8019217C;

extern s32 func_8012B744(void *a0, void *a1);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);

s32 func_80187A04(void)
{
    extern void func_8012BE54(s32 a0);   /* canonical void -> cast at use */
    extern void func_8012E8A8(u8 *a0);

    SVec_80187A04 sv;
    Mat_80187A04 m;
    Vec_80187A04 out;
    s32 angle;

    sv.vx = D_80126B5E;
    sv.vz = D_80126B66;

    m = (*(Mat_80187A04 *)&D_800AE620);

    angle = func_8012B744((void *)(D_801DFF88 + 4), &sv);

    RotMatrixY(angle, &m);

    func_800484EC((s32)&m, (s32)&D_8019217C, (s32)&out);

    *(s32 *)(D_801DFF88 + 4) += out.vx;
    *(s32 *)(D_801DFF88 + 8) += out.vy;
    *(s32 *)(D_801DFF88 + 0xC) += out.vz;

    if (((s32 (*)(s32))func_8012BE54)(D_801DFF88) < 0x191) {
        func_8012E8A8((u8 *)D_801DFF88);
        func_8002D4C8(4, 0x449);
        return 1;
    }

    return 0;
}


extern s32 D_801DFF88;
extern void func_8012E88C(u8 *a0);

void func_80187B30(void) {
    ((void (*)(s32))func_8012E88C)(D_801DFF88);
}


extern s32 D_801DFF88;
extern void func_8012E8A8(u8 *a0);

void func_80187B58(void) {
    ((void (*)(s32))func_8012E8A8)(D_801DFF88);
}


extern s32 D_801DFF74;
extern s32 D_801DFF88;
extern s32 D_801DFF80;
extern s32 D_801DFF84;
extern s16 D_80191254[];
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8012C218(void *a0);

void func_80187B80(void) {
    s32 mtx[8];  /* sp+0x10 */
    u16 sv[4];   /* sp+0x30 */

    func_8012EC04(D_801DFF74, 4, mtx);
    func_8012F14C((s32)mtx, (s32)D_80191254, (s32)sv);

    *(s16 *)(D_801DFF88 + 0x6) = sv[0] - 0x17;
    *(s16 *)(D_801DFF88 + 0xA) = sv[1] - 7;
    *(s16 *)(D_801DFF88 + 0xE) = sv[2] - 3;
    *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x10) = 0x400;
    *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x12) = -0x400;
    func_8012B2CC(D_801DFF88);

    func_8012C218((void *)D_801DFF80);
    func_8012C218((void *)D_801DFF84);
}


extern s32 D_801DFF74;
extern s32 D_801DFF88;
extern s16 D_80191254[];
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);

void func_80187C2C(void) {
    s32 mtx[8];  /* sp+0x10 */
    u16 sv[4];   /* sp+0x30 */
    s32 ang[3];  /* sp+0x38 */

    func_8012EC04(D_801DFF74, 4, mtx);
    func_8012F14C((s32)mtx, (s32)D_80191254, (s32)sv);

    *(s16 *)(D_801DFF88 + 0x6) = sv[0];
    *(s16 *)(D_801DFF88 + 0xA) = sv[1];
    *(s16 *)(D_801DFF88 + 0xE) = sv[2];
    *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x10) = 0;
    *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x12) = 0;
    func_8012B2CC(D_801DFF88);

    ang[2] = 0;
    ang[0] = 0;
    ang[1] = -0x300000;
    func_8012B14C(D_801DFF88, (s32)ang);

    *(s32 *)(D_801DFF88 + 0x48) = 0x18000;
    *(s16 *)(*(s32 *)(D_801DFF88 + 0x20) + 0x10) = 0x800;
}


extern s32 D_801DFF7C;
extern s32 D_801DFF6C;
extern s32 D_8018CCC4;
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80187D64(s32 arg0);
extern void func_8012E8A8(u8 *a0);

s32 func_80187CE4(void) {
    s32 a0 = D_801DFF7C;
    s16 v = *(u16 *)(a0 + 0xA) + 0x14;
    *(s16 *)(a0 + 0xA) = v;
    if (v >= -130) {
        *(s16 *)(a0 + 0xA) = -130;
        func_80187D64(a0);
        ((void (*)(s32))func_8012E8A8)(D_801DFF6C);
        func_8013C9C4(&D_8018CCC4);
        func_8002D4C8(0xB5F, 0);
        return 1;
    }
    return 0;
}


#include "common.h"
#include "/home/musashi/bfm-decomp/src/shared/engine_core.h"

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern u8 *func_8012913C(s32 a0);
extern s32 rand(void);

void func_80187D64(s32 arg0) {
    s16 ang[3];   /* sp+0x10..0x15 */
    s16 vec[3];   /* sp+0x18..0x1D */
    s32 buf[8];   /* sp+0x20 .. sp+0x3F, filled by func_8012EC04 */
    s32 i;
    u8 *ent;

    ang[1] = 0x20;
    ang[0] = 0;
    ang[2] = -0xC;
    func_8012EC04(arg0, 0xE, (s32 *)buf);
    func_8012F14C((s32)buf, (s32)ang, (s32)vec);

    for (i = 0; i < 0x10; i++) {
        ent = func_8012913C(0x22);
        if (ent != 0) {
            s32 s0 = i << 9;
            *(s16 *)(ent + 0x6) = vec[0];
            *(s16 *)(ent + 0xA) = vec[1];
            *(s16 *)(ent + 0xE) = vec[2];
            *(s32 *)(ent + 0x10) = func_80047948(s0) * 320;
            *(s32 *)(ent + 0x18) = func_8004787C(s0) * 320;
            *(s16 *)(ent + 0x34) = (((rand() % 3) << 12) + 0x4000) | 1;
            *(u16 *)(*(s32 *)(ent + 0x20) + 0x2C) = 0xC004;
        }
    }
}



extern Blk20 D_800AE620;
extern s32 D_80126B58;
extern s32 D_80126B60;
extern s32 D_80126B64;
extern s32 *D_80126B78;
extern u16 D_800B99DA;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_8019218C[];
extern u16 D_8019125C;
extern u16 D_8019125E;
extern u16 D_80191260;
extern u16 D_80191264;
extern u16 D_80191266;
extern u16 D_80191268;
extern s32 D_801DFF70;
extern s32 D_801DFF6C;

extern void func_801885C0();
extern s32 func_8012B744(void *a0, void *a1);
extern void RotMatrixY(s32 r, void *m);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 func_80013478(s32 a0, s32 a1);

s32 func_80187E84(s32 arg) {
    Blk20 m;
    s32 vout[4];
    s32 *b58p = &D_80126B58;

    if (*(s16 *)(arg + 0xFE) == 0) {
        s32 *ent = b58p + 1;
        u16 *rotA = &D_8019125C;

        m = D_800AE620;
        RotMatrixY(func_8012B744((void *)ent, (void *)rotA), &m);
        func_800484EC((s32)&m, (s32)&D_8019218C, (s32)vout);
        b58p[1] += vout[0];
        D_80126B60 += vout[1];
        D_80126B64 += vout[2];
        *(u16 *)((s32)D_80126B78 + 0x12) += 0x200;
        if ((D_800B99DA & 1) == 0) {
            func_801885C0((s32)ent, (s32)vout);
        }
        if (func_80013478((s32)ent, (s32)rotA) < 0x401) {
            D_80126B5E = *rotA;
            D_80126B62 = D_8019125E;
            D_80126B66 = D_80191260;
            *(u16 *)(arg + 0xFE) += 1;
        }
    }

    if (*(s16 *)(arg + 0x100) == 0) {
        u16 *rotB = &D_80191264;

        m = D_800AE620;
        RotMatrixY(func_8012B744((void *)(D_801DFF70 + 4), (void *)rotB), &m);
        func_800484EC((s32)&m, (s32)&D_8019218C, (s32)vout);
        *(s32 *)(D_801DFF70 + 4) += vout[0];
        *(s32 *)(D_801DFF70 + 8) += vout[1];
        *(s32 *)(D_801DFF70 + 0xC) += vout[2];
        *(u16 *)(*(s32 *)(D_801DFF70 + 0x20) + 0x12) += 0x200;
        if ((D_800B99DA & 1) == 0) {
            func_801885C0(D_801DFF70 + 4, (s32)vout);
        }
        if (func_80013478(D_801DFF70 + 4, (s32)rotB) < 0x401) {
            *(u16 *)(D_801DFF70 + 6) = *rotB;
            *(u16 *)(D_801DFF70 + 0xA) = D_80191266;
            *(u16 *)(D_801DFF70 + 0xE) = D_80191268;
            *(u16 *)(arg + 0x100) += 1;
        }
    }

    if (*(s16 *)(arg + 0xFE) != 0) {
        if (*(s16 *)(arg + 0x100) == 0) {
            return 0;
        }
        *(s32 *)(arg + 0xD4) = D_801DFF6C;
        return 1;
    }

    return 0;
}


extern u16 D_800B99DA;
extern s32 D_8018CCC4;
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801881D8(void) {
    if ((D_800B99DA % 60) == 0) {
        func_8013C9C4(&D_8018CCC4);
        func_8002D4C8(0xB5F, 0);
    }
}


#include "common.h"





extern Blk20 D_800AE620;
extern int D_801DFF70;
extern u16 D_8019126C;
extern u16 D_8019126E;
extern u16 D_80191270;
extern Rec12 D_8019219C[];

extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 func_8012B744(void *a0, void *a1);
extern void RotMatrixY(s32 a0, void *a1);
extern s32 func_80013478(s32 a0, s32 a1);
extern s32 func_80143B6C(s32 a0, s32 a1);

void func_80188240(void)
{
    Blk20 localMat;
    VECTOR outVec;

    u16 *rotPtr = &D_8019126C;

    localMat = D_800AE620;

    RotMatrixY(func_8012B744((void *)(D_801DFF70 + 4), rotPtr), &localMat);

    func_800484EC((s32)&localMat, (s32)D_8019219C, (s32)&outVec);

    *(s32 *)(D_801DFF70 + 4) += outVec.vx;
    *(s32 *)(D_801DFF70 + 8) += outVec.vy;
    *(s32 *)(D_801DFF70 + 0xC) += outVec.vz;

    if (func_80013478(D_801DFF70 + 4, (s32)rotPtr) < 0x401) {
        *(s16 *)(D_801DFF70 + 6) = *rotPtr;
        *(s16 *)(D_801DFF70 + 0xA) = D_8019126E;
        *(s16 *)(D_801DFF70 + 0xE) = D_80191270;
    }

    if ((*(s32 *)(D_801DFF70 + 0x94) & 7) == 0) {
        func_80143B6C(D_801DFF70, 0);
    }
}


extern s32 D_801DFF78;
extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_8018BFC8(s32 a0, s32 a1);
extern s16 D_801921AC[3];

void func_801883A0(void) {
    s16 vec[3];   /* sp+0x10..0x15 */
    s32 buf[8];   /* sp+0x18..0x37 */

    func_8012EA90(*(s32 *)&D_801DFF78, 4, (s32 *)buf);
    func_8012F14C((s32)buf, (s32)D_801921AC, (s32)vec);
    func_8018BFC8(*(s32 *)&D_801DFF78, (s32)vec);
}


extern s32 D_801DFF7C;
extern void func_8002D4C8(s32 a0, s32 a1);
extern u8 D_801B23E8[];
extern u8 D_801B27B8[];

void func_801883FC(void)
{
    s32 base;

    base = D_801DFF7C;
    if ((*(s32 *)(base + 0x94) == 7 && *(s32 *)(base + 0x90) == (s32)&D_801B23E8) ||
        ((*(s32 *)(base + 0x94) == 0xA || *(s32 *)(base + 0x94) == 0x42) &&
         *(s32 *)(base + 0x90) == (s32)&D_801B27B8))
    {
        func_8002D4C8(0xBD4, 0);
    }
}


extern s32 func_8017C8E4(void);
    s32 func_80188470(void) {
        return func_8017C8E4() != 0;
    }


extern s32 D_801DFF74;
extern s32 D_801DFF7C;
extern s16 D_801921B4[];
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_80188490(void) {
    s32 buf[8];
    s16 out[4];
    s32 q;

    if (*(s32 *)(D_801DFF7C + 0x94) >= 0x23) {
        func_8012EC04(D_801DFF7C, 0xE, buf);
        func_8012F14C((s32)buf, (s32)D_801921B4, (s32)out);
        if (out[1] + 0x102 >= 0) {
            q = ((out[1] + 0x102) << 12) / 103;
        } else {
            q = ((-0x102 - out[1]) << 12) / 103;
        }
        if ((u32)(q - 1) < 0xFFF) {
            *(s16 *)(*(s32 *)(D_801DFF74 + 0x20) + 0x1A) = q;
        }
    }
}


extern s16 D_801DFFDC;
    void func_80188548(void) {
        D_801DFFDC += 1;
    }


extern s32 *D_80126B78;
extern u8 D_80126B5C;
extern s32 func_8012BB3C(s32 a0, s32 a1, u32 a2, s32 a3);

s32 func_80188568(s32 arg0) {
    s32 r;
    r = func_8012BB3C((s32)&D_80126B5C, *(s32 *)(arg0 + 0xD4) + 4,
                      ((s16 *)D_80126B78)[9], 8);
    ((s16 *)D_80126B78)[9] += r;
    return (s16)r == 0;
}


void func_801885C0(s32 *a0, s32 *a1)
{
    u8 *ent;

    ent = func_8012913C(0x22);
    if (ent != 0) {
        *(s32 *)(ent + 0x4) = a0[0];
        *(s32 *)(ent + 0x8) = a0[1];
        *(s32 *)(ent + 0xC) = a0[2];
        *(s32 *)(ent + 0x10) = -(a1[0] >> 1);
        *(s32 *)(ent + 0x18) = -(a1[2] >> 1);
        *(u16 *)(ent + 0x34) = 0x3000;
        *(u16 *)(*(s32 *)(ent + 0x20) + 0x2C) = 0xC004;
    }
}


#include "common.h"

extern s16 D_801DFFDC;
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018865C(void)
{
    /* function-local type/decl layer (byte-neutral): keeps the file-scope
     * environment of ov_SC06_029_jr_8017C954.c untouched. */
    typedef struct { s32 w[8]; } B20;              /* == shared Blk20  */
    typedef struct { s32 vx, vy, vz, pad; } V32;   /* == shared Vec32  */

    extern u16 D_800B99DA;
    extern Blk20 D_800AE620;
    extern int rand(void);
    extern void RotMatrixZ(s32, void *);
    extern u8 *func_8012913C(s32);

    V32 vec;   /* sp+0x10 */
    B20 mtx;   /* sp+0x20 */
    s32 i;
    s32 ang;
    s32 zz;
    s32 p;
    s32 r0, r1;

    if ((*(u16 *)&D_801DFFDC) < 3) {
        if ((D_800B99DA & 1) != 0) {
            return;
        }
    } else {
        if ((D_800B99DA & 3) == 0) {
            return;
        }
    }

    ang = -0xC0;
    zz = -0x40;
    i = 0;
    vec.vx = 0;
    vec.vz = 0;
    do {
        mtx = (*(B20 *)&D_800AE620);
        RotMatrixZ(ang, &mtx);
        vec.vy = ((rand() % 9) << 16) - 0x300000;
        p = ((s32 (*)(s32))func_8012913C)(0x22);
        if (p != 0) {
            *(s16 *)(p + 6) = zz;
            *(s16 *)(p + 0xA) = -0x102;
            *(s16 *)(p + 0xE) = (rand() % 128) - 0x40;
            r0 = rand();
            r1 = rand();
            *(s16 *)(p + 0x34) = (((r0 % 4) << 12) + 0x4000) | (r1 & 1);
            *(s32 *)(*(s32 *)(p + 0x20) + 4) |= 0x60000000;
            func_800484EC((s32)&mtx, (s32)&vec, p + 0x10);
        }
        i++;
        ang += 0x80;
        zz += 0x20;
    } while (i < 4);
}


void func_8018884C(void) {
    extern s8 D_801912F4[];
    extern s32 D_801DFFE0;
    extern s32 D_801DFFE4;
    extern s32 D_801DFFE8;
    extern s32 D_801DFFEC;
    extern void func_8012A018(s32 a0, s32 a1);
    extern void func_80188BB0();

    s32 base = (s32)&D_801912F4;
    D_801DFFE4 = base + 8;
    D_801DFFE0 = base;
    D_801DFFE8 = base - 0x10;
    D_801DFFEC = base - 8;
    func_8012A018((s32)func_80188BB0, 0);
}


extern void func_8012A018(s32 a0, s32 a1);
extern void func_80188BB0();
extern s8 D_801913F4[];
extern s32 D_801DFFE0;
extern s32 D_801DFFE4;
extern s32 D_801DFFE8;
extern s32 D_801DFFEC;

void func_801888A8(void) {
    s32 base = (s32)&D_801913F4;
    D_801DFFE4 = base + 8;
    D_801DFFE0 = base;
    D_801DFFE8 = base - 0x10;
    D_801DFFEC = base - 8;
    func_8012A018((s32)func_80188BB0, 1);
}


void func_80188904(void) {
    extern s32 D_80191424;
    extern s32 D_801DFFE0;
    extern s32 D_801DFFE4;
    extern s32 D_801DFFE8;
    extern s32 D_801DFFEC;
    extern void func_8012A018(s32 a0, s32 a1);
    extern void func_80188BB0();

    D_801DFFE0 = (s32)&D_80191424;
    D_801DFFE4 = (s32)&D_80191424 + 8;
    D_801DFFE8 = (s32)&D_80191424 - 0x20;
    D_801DFFEC = (s32)&D_80191424 - 0x18;
    func_8012A018((s32)func_80188BB0, 1);
}


extern void func_8012A018(s32 a, s32 b);
    extern void func_80188BB0();
    void func_80188960(void) {
        ((void (*)(void *, s32))func_8012A018)((void *)func_80188BB0, 0x2);
    }


void func_80188988(int param_1) {
    extern s32 D_801DFFE0;
    extern s32 D_801DFFE4;
    extern s32 D_801DFFE8;
    extern s32 D_801DFFEC;
    extern s32 func_80012CB8(s32 a0, s32 a1, s32 a2);
    register s16 *psVar1 __asm__("$5");
    s16 *psVar2;
    s16 *psVar3;
    s16 *psVar5;
    s16 sVar4;

    psVar1 = (s16 *)D_801DFFE0;
    psVar2 = (s16 *)D_801DFFE4;
    *(s32 *)(param_1 + 0x4C) = psVar1[1];
    *(s32 *)(param_1 + 0x50) = psVar1[2];
    *(s32 *)(param_1 + 0x40) = psVar2[1];
    psVar3 = (s16 *)D_801DFFE8;
    *(s32 *)(param_1 + 0x44) = psVar2[2];
    sVar4 = func_80012CB8(*psVar3, *psVar1, 0x80);
    ((struct { s32 f; } *)(param_1 + 0x48))->f += sVar4;
    sVar4 = func_80012CB8(*(s16 *)D_801DFFEC, *(s16 *)D_801DFFE4, 0x80);
    psVar5 = (s16 *)D_801DFFE0;
    *(s32 *)(param_1 + 0x3C) += sVar4;
    if (psVar5[0] < *(s32 *)(param_1 + 0x48)) {
        *(s32 *)(param_1 + 0x48) = psVar5[0];
    }
    if (*(s16 *)D_801DFFE4 < *(s32 *)(param_1 + 0x3C)) {
        *(s32 *)(param_1 + 0x3C) = *(s16 *)D_801DFFE4;
    }
}


extern u16 D_801913E4[];
extern u16 D_801913EC[];
extern s32 D_801DFFE0;
extern s32 D_801DFFE4;
extern s32 D_801DFFE8;
extern s32 D_801DFFEC;
extern s32 func_80012CB8(s32 a0, s32 a1, s32 a2);

void func_80188A90(int param_1) {
    s16 *psVar1;
    s16 *psVar2;
    s16 *psVar5;
    s16 sVar4;

    psVar2 = (s16 *)D_801DFFE4;
    psVar1 = (s16 *)D_801DFFE0;
    *(s32 *)(param_1 + 0x48) = psVar1[0];
    *(s32 *)(param_1 + 0x50) = psVar1[2];
    *(s32 *)(param_1 + 0x3C) = psVar2[0];
    D_801DFFE8 = (s32)&D_801913E4;
    *(s32 *)(param_1 + 0x44) = psVar2[2];
    D_801DFFEC = (s32)&D_801913E4 + 8;
    sVar4 = func_80012CB8((s16)D_801913E4[1], psVar1[1], 0x80);
    ((struct { s32 f; } *)(param_1 + 0x4C))->f += sVar4;
    sVar4 = func_80012CB8(*(s16 *)(D_801DFFEC + 2), *(s16 *)(D_801DFFE4 + 2), 0x80);
    psVar5 = (s16 *)D_801DFFE0;
    *(s32 *)(param_1 + 0x40) += sVar4;
    if (*(s32 *)(param_1 + 0x4C) < psVar5[1])
        *(s32 *)(param_1 + 0x4C) = psVar5[1];
    if (*(s32 *)(param_1 + 0x40) < *(s16 *)(D_801DFFE4 + 2))
        *(s32 *)(param_1 + 0x40) = *(s16 *)(D_801DFFE4 + 2);
}



extern void (*D_801921BC[])(void);

void func_80188BB0(void *a0) {
    D_801921BC[*(u8 *)((s32)a0 + 0x4)]();
}



extern void (*D_801921C8[])(void);

void func_80188BEC(void *a0) {
    D_801921C8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801921D0[])(void);

void func_80188C28(void *a0) {
    D_801921D0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801921D8[])(void);

void func_80188C64(void *a0) {
    D_801921D8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801921E0[])(void);

void func_80188CA0(void *a0) {
    D_801921E0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80192210[])(void);

void func_80188CDC(void *a0) {
    D_80192210[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80192298[])(void);

void func_80188D18(void *a0) {
    D_80192298[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801922A4[])(void);

void func_80188D54(void *a0) {
    D_801922A4[*(u16 *)((s32)a0 + 0x2)]();
}

void func_80188D90(s32 a0) {
    u8 mtx[0x20];
    Prim_80188D90 p;
    signed char *q;
    s32 i;

    setup_80188D90(a0, mtx);

    p.v[0].vz = p.v[2].vz = p.v[3].vz = 0;
    p.v[1].vx = p.v[1].vy = p.v[1].vz = 0;
    if (D_800B99DA & 1) {
        p.c[1][0] = 0xA0;
    } else if (D_800B99DA & 2) {
        p.c[1][0] = 0xC0;
    } else {
        p.c[1][0] = 0x80;
    }
    p.c[0][0] = p.c[0][1] = p.c[0][2] = 0;
    p.c[2][0] = p.c[2][1] = p.c[2][2] = 0;
    p.c[3][0] = p.c[3][1] = p.c[3][2] = 0;
    p.code = 0x50000000;
    p.c[1][1] = p.c[1][2] = p.c[1][0] >> 2;

    q = D_8018F650;
    for (i = 0; i < 4; i++) {
        p.v[0].vx = *q++;
        p.v[0].vy = *q++;
        p.v[2].vx = *q++;
        p.v[2].vy = *q++;
        p.v[3].vx = *q++;
        p.v[3].vy = *q--;
        func_80017758(&p, mtx);
    }

    q = D_8018F664;
    p.v[0].vy = p.v[2].vy = p.v[3].vy = 0;
    p.v[1].vx = p.v[1].vy = 0;
    p.v[1].vz = -0x20;
    for (i = 0; i < 4; i++) {
        p.v[0].vx = *q++;
        p.v[0].vz = *q++;
        p.v[2].vx = *q++;
        p.v[2].vz = *q++;
        p.v[3].vx = *q++;
        p.v[3].vz = *q--;
        func_80017758(&p, mtx);
        if (i == 1) {
            p.v[1].vz = 0x20;
            q += 2;
        }
    }
    q += 2;

    p.v[0].vx = 0;
    p.v[0].vz = -0x20;
    p.c[0][0] = p.c[1][0];
    p.c[0][1] = p.c[0][2] = p.c[1][1];
    for (i = 0; i < 2; i++) {
        p.v[2].vx = *q++;
        p.v[2].vz = *q++;
        p.v[3].vx = *q++;
        p.v[3].vz = *q++;
        func_80017758(&p, mtx);
    }
}


extern void (*D_801922C4[])(void);
extern void func_80188D90();

void func_80189148(void *arg0) {
    D_801922C4[*(u16 *)((s32)arg0 + 2)]();
    if ((*(s32 *)(*(s32 *)((s32)arg0 + 0x20) + 4) >= 0) &&
        (*(s16 *)((s32)arg0 + 0x10A) == 0) &&
        (*(u16 *)arg0 != 0)) {
        func_80188D90(arg0);
    }
}


#include "common.h"

extern void (*D_801922EC[])(void);

void func_801891D0(void *a0) {
    D_801922EC[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) + *(u16 *)(*(s32 *)((s32)a0 + 0xDC) + 0x6);
    }
}


#include "common.h"

extern s32 rand(void);

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

void func_80189244(Obj_80189244 *p) {
    s32 i;
    s32 angle;
    s32 t1;
    s32 t2;
    s32 t3;

    angle = 0;
    for (i = 0; i < 0x34; i++) {
        p->unk00[i].unk00 = 0;
        p->unk00[i].unk04 = 0;
    }

    for (i = 51; i > 0; i -= 2) {
        p->unk00[i].unk02 = angle;
        p->unk00[i - 1].unk02 = angle;
        /* NOTE (§178): written as `angle + (-8 - r)` on purpose. The natural
         * `angle - 8 - (rand() % 8)` is reassociated by fold into
         * `angle - (r + 8)`, which costs one extra insn and loses the
         * `addiu $a0,$s1,-8` branch-delay fill. */
        angle = angle + (-8 - (rand() % 8));
    }

    p->unk1A2 = rand() % 4096;
    p->unk1A0 = (rand() % 48) + 48;

    t1 = rand() % 16;
    p->unk1A4 = (rand() & 1) ? t1 : -t1;

    t2 = rand() % 64;
    p->unk1A6 = (rand() & 1) ? t2 : -t2;

    t3 = rand() % 384;
    p->unk1A8 = (rand() & 1) ? t3 : -t3;

    p->unk1AA = 2;
    p->unk1AC = (rand() % 64) + 64;
}


#include "common.h"

/* func_80189440 - ov_SC06_029 - "25-quad ribbon/trail emitter".
 *
 * Shifts the x coordinate of a 52-entry SVECTOR strip down by one pair, feeds a
 * new head pair from a sine table (func_80047948), builds a local MATRIX from
 * D_800AE620 + RotMatrixZ, composes it with the camera matrix D_800AF648 by
 * hand (three rtir column rotations + one rt on the translation vector), then
 * emits 25 gouraud quads (POLY_G4, code 0x3A) into the double-buffered OT
 * D_800A6610[D_800B9A02 << 14], each followed by an 8-byte DR_MODE packet
 * (0xE100004A), exactly like this TU's func_80184C68.
 */

typedef struct { s16 vx, vy, vz, pad; } SV_189440;

extern s32 func_80047948(s32 a0);
extern void RotMatrixZ(s32 r, void *m);

#define gte_ldv0(r0) __asm__ volatile ("lwc2 $0, 0( %0 );" "lwc2 $1, 4( %0 )" : : "r"(r0))

#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_rt() __asm__ volatile ("nop;nop;mvmva 1, 0, 0, 0, 0")
#define gte_rtir() __asm__ volatile ("nop;nop;mvmva 1, 0, 3, 3, 0")

#define gte_stsxy(r0) __asm__ volatile ("swc2 $14, 0( %0 )" : : "r"(r0) : "memory")

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_stotz(r0) __asm__ volatile ("swc2 $7, 0( %0 )" : : "r"(r0) : "memory")

#define gte_stflg(r0) __asm__ volatile ("cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"(r0) : "$12", "memory")

#define gte_SetRotMatrix(r0) __asm__ volatile ( \
    "lw $12, 0( %0 );"                          \
    "lw $13, 4( %0 );"                          \
    "ctc2 $12, $0;"                             \
    "ctc2 $13, $1;"                             \
    "lw $12, 8( %0 );"                          \
    "lw $13, 12( %0 );"                         \
    "lw $14, 16( %0 );"                         \
    "ctc2 $12, $2;"                             \
    "ctc2 $13, $3;"                             \
    "ctc2 $14, $4"                              \
    : : "r"(r0) : "$12", "$13", "$14" )

#define gte_SetTransMatrix(r0) __asm__ volatile ( \
    "lw $12, 20( %0 );"                           \
    "lw $13, 24( %0 );"                           \
    "ctc2 $12, $5;"                               \
    "lw $14, 28( %0 );"                           \
    "ctc2 $13, $6;"                               \
    "ctc2 $14, $7"                                \
    : : "r"(r0) : "$12", "$13", "$14" )

#define gte_ldclmv(r0) __asm__ volatile (        \
    "lhu $12, 0( %0 );"                          \
    "lhu $13, 6( %0 );"                          \
    "lhu $14, 12( %0 );"                         \
    "mtc2 $12, $9;"                              \
    "mtc2 $13, $10;"                             \
    "mtc2 $14, $11"                              \
    : : "r"(r0) : "$12", "$13", "$14" )

#define gte_stclmv(r0) __asm__ volatile (        \
    "mfc2 $12, $9;"                              \
    "mfc2 $13, $10;"                             \
    "mfc2 $14, $11;"                             \
    "sh $12, 0( %0 );"                           \
    "sh $13, 6( %0 );"                           \
    "sh $14, 12( %0 )"                           \
    : : "r"(r0) : "$12", "$13", "$14", "memory" )

#define gte_ldlvnl(r0) __asm__ volatile (        \
    "lhu $13, 4( %0 );"                          \
    "lhu $12, 0( %0 );"                          \
    "sll $13, $13, 16;"                          \
    "or $12, $12, $13;"                          \
    "mtc2 $12, $0;"                              \
    "lwc2 $1, 8( %0 )"                           \
    : : "r"(r0) : "$12", "$13" )

#define gte_stlvnl(r0) __asm__ volatile (        \
    "swc2 $25, 0( %0 );"                         \
    "swc2 $26, 4( %0 );"                         \
    "swc2 $27, 8( %0 )"                          \
    : : "r"(r0) : "memory" )

void func_80189440(s32 arg0, SV_189440 *v)
{
    /* block-scope copies so the draft compiles standalone under match_one; the
     * TU's ../shared/engine_core.h already provides both -- delete when banking. */
    typedef struct { u32 addr : 24; u32 len : 8; u8 r0, g0, b0, code; } P_TAG;
    typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX;
    typedef struct { s32 w[8]; } Blk20;

    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];

    MTX m;
    s32 flag, flag2, otz;
    SV_189440 *p;
    u32 *ot;
    u32 *otp;
    u8 *pkt;
    u8 *q;
    s32 col;
    u32 dr;
    s32 i, j, x, z;

    for (i = 0x32, p = &v[0x32]; i >= 2; i -= 2) {
        *(u16 *)&p[0].vx = *(u16 *)&p[-2].vx;
        *(u16 *)&p[1].vx = *(u16 *)&p[-1].vx;
        p -= 2;
    }

    j = func_80047948(v[0x34].vy);
    x = (v[0x34].vx * j) >> 12;
    *(u16 *)&v[0x34].vy = *(u16 *)&v[0x34].vy + *(s32 *)&v[0x35].vz;
    v[0].vx = x - *(u16 *)&v[0x35].vy;
    v[1].vx = *(u16 *)&v[0x35].vy + x;

    col = *(s32 *)(arg0 + 0xE0);
    m = *(MTX *)&D_800AE620;
    ot = (u32 *)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    RotMatrixZ(v[0x35].vx, &m);
    m.t[0] = v[0x34].vz;
    m.t[1] = -0xF2;
    m.t[2] = v[0x34].pad;

    gte_SetRotMatrix(&D_800AF648);
    gte_ldclmv(&m.m[0][0]);
    gte_rtir();
    gte_stclmv(&m.m[0][0]);
    gte_ldclmv(&m.m[0][1]);
    gte_rtir();
    gte_stclmv(&m.m[0][1]);
    gte_ldclmv(&m.m[0][2]);
    gte_rtir();
    gte_stclmv(&m.m[0][2]);
    gte_SetTransMatrix(&D_800AF648);
    gte_ldlvnl(&m.t[0]);
    gte_rt();
    gte_stlvnl(&m.t[0]);
    gte_SetRotMatrix(&m);
    gte_SetTransMatrix(&m);

    for (i = 0, p = v; i < 0x19; ) {
        pkt = D_800A5E60;
        D_800A5E60 = pkt + 0x24;
        pkt[3] = 8;
        *(u32 *)(pkt + 4) = col;
        pkt[7] = 0x3A;
        *(u32 *)(pkt + 0xC) = col;
        *(u32 *)(pkt + 0x14) = col;
        *(u32 *)(pkt + 0x1C) = col;

        gte_ldv3(p, p + 1, p + 2);
        gte_rtpt();
        gte_stflg(&flag);
        gte_stsxy3(pkt + 8, pkt + 0x10, pkt + 0x18);
        gte_ldv0(p + 3);
        gte_rtps();
        gte_stflg(&flag2);
        flag |= flag2;
        gte_stsxy(pkt + 0x20);
        gte_avsz4();
        gte_stotz(&otz);

        if ((flag & ~0x1000) == 0) {
            z = otz + 1;
            if (z >= 0x1000) {
                z = 0xFFF;
            }
            otp = (u32 *)(z * 4 + (u32)ot);
            q = D_800A5E60;
            ((P_TAG *)pkt)->addr = ((P_TAG *)otp)->addr;
            /* LEVER 1 (cookbook §193-F / §148-A2, the loop.c hoist arithmetic).
             * The target hoists ALL THREE loop constants into the preheader
             * ($t0=0xFFFFFF, $t2=0xFF000000, $t3=0xE100004A).  Written inline at
             * its store, 0xE100004A is a movable of `life 1, savings 1`, and
             * `-dL` reads `Loop from 202 to 420: 85 real insns` with the
             * threshold already decayed to 52 by the two mask hoists:
             * 52*1*1 = 52 < 85  ->  "not desirable", so it stayed in the body and
             * the whole $a3/$t0../$t3 file shifted down one register.
             * Materialising it HERE and consuming it at the store below widens
             * `lifetime` to >=2 (52*1*2 = 104 >= 85) and loop.c moves it -- and
             * because loop.c emits its hoists immediately before loop_start, in
             * movable order, it lands AFTER the two masks, exactly as in the
             * target.  A source-level `dr = 0xE100004A;` in the PREHEADER does
             * not work: it would emit BEFORE the i/p inits and the hoists. */
            dr = 0xE100004A;
            D_800A5E60 = q + 8;
            ((P_TAG *)otp)->addr = (u32)pkt;
            q[3] = 1;
            *(u32 *)(q + 4) = dr;
            ((P_TAG *)q)->addr = ((P_TAG *)otp)->addr;
            ((P_TAG *)otp)->addr = (u32)q;
        }
        /* LEVER 2: `i++` must be written HERE, ahead of the colour step, not
         * left to the `for` increment.  The tail block ties on priority --
         * lw->addu and addiu->slti->bnez are both chains of 3 -- so
         * `rank_for_schedule` falls through to INSN_LUID (source order).  With
         * the increment last, sched1 issues the `lw` first and fills the load
         * delay with it; the target issues `addiu $t1,$t1,1` first and leaves a
         * real `nop` in the load-delay slot (the -1 instruction). */
        i++;
        col += *(s32 *)(arg0 + 0xE0);
        p += 2;
    }
}
