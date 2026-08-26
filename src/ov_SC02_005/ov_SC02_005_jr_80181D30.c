#include "common.h"
#include "../shared/engine_core.h"

/* HOISTED (P31 S54): these three typedefs were defined further down the file, BELOW the
 * INCLUDE_ASM lines of stubs that need them. harvest_verify strips a draft's own copy of any
 * typedef the TU already provides, which left the name undefined at the earlier insertion
 * point (pregate_check: TYPEDEF-USED-ABOVE-DEFINITION). Typedefs emit no code, so moving them
 * to the top is byte-neutral -- proven by the gate, not asserted. */
typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
} D_80195AF6_t;

typedef struct {
    u8 pad[4];
    s32 field_4;
} SubStruct;

typedef struct {
    u8 pad_00[0x20];
    SubStruct *f_20;
    u8 pad_24[0xA8];
    void *f_CC;
    void *f_D0;
    void *f_D4;
    u8 pad_D8[0x10];
    s32 f_E8;
} MainStruct;


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
typedef struct { u32 w0, w1, w2; } PrimCF90;
typedef struct { u8 *vtx; u32 f4; u32 xx, yy, zz; PrimCF90 *prim, *end; } CellCF90;
typedef struct { s16 vx, vy; } DVEC2_CF90;
typedef struct { s16 vx, vy, vz, pad; } SVEC2_CF90;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_CF90;
typedef struct { u32 tag, rgbc; s16 x0, y0, x1, y1, x2, y2; } PF3_CF90;
typedef struct { u32 tag, rgbc; s16 x0, y0, x1, y1, x2, y2, x3, y3; } PF4_CF90;
typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1; s16 x2, y2; u16 uv2, p2; } PFT3_CF90;
typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1; s16 x2, y2; u16 uv2, p2; s16 x3, y3; u16 uv3, p3; } PFT4_CF90;
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80192E18;
extern u8 D_80192D88;
extern u8 D_80192D64;
extern u8 D_80192D40;
extern u8 D_80192DF4;
extern u8 D_80192DD0;
extern u8 D_80192DAC;
extern u8 D_80192D1C;
extern void func_80145934(void);
extern u8 D_80192EA8;
extern u8 D_80192E84;
extern u8 D_80192E60;
extern u8 D_80192E3C;
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
extern unsigned char D_801922A0[];
extern unsigned char D_801922D0[];
extern unsigned char D_80192320[];
extern unsigned char D_80192350[];
extern unsigned char D_80192380[];
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
extern void (*D_801923D0[])(void *);
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
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_80192498[];
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
extern u8 D_80192520[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80192528;
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
extern u16 D_800B99DA;
extern s32 D_801150D8;
extern s16 D_801152AA;
extern u8 D_80126720[];
extern s16 D_80126724;
extern s32 func_8014EA4C(void * a0, void * a1, void * a2, s32 _arg3);
extern s32 func_8014ED80(struct SubED80 *a0);
extern int D_801E3128;
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
extern s32 D_801E312C;
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
extern s32 D_80192558;
extern s32 D_80126990;
extern s32 D_80126994;
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
extern void (*D_80192600[])(void);
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
extern void (*D_80192624[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80192614;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80192638[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80192644[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80192654[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8019266C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8019265C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80192680[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8019269C[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8019268C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801926B0[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801926C4[])(void);
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
extern s32 D_801926D8;
extern void (*D_80192700[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801926E0;
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
extern int (*D_8019274C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80192750[])(void);
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
extern s32 func_8014C568(s16 *a0, s16 *a1);
extern void func_801567BC(s32 a0);
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern unsigned char D_8011520C[];
extern unsigned short D_80192BB4[];
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
extern void (*D_80192BC4[])(void);
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
extern int D_801E3160;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80192BEC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80192BCC;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80192BDC;
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
extern void (*D_80192C2C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80192C34[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80192C00;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80192C40[])(void);
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
extern u8 D_80192C10;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801E3168;
extern s32 D_801E3174;
extern s32 D_801E3178;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80192C7C[])(s32 *);
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
extern s32 D_80192C50[];
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
extern s32 D_801E3170;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80192ECC[])(void);
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
extern char D_80192CEC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80192F70[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_801930C4[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80192EE0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_801930CC[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80192EF0;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80192F10;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_801930D4[])(void);
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
extern void (*D_801930FC[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80193108[])(void);
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
extern void (*D_80192F7C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801931AC;
extern void func_8015D380(s32 a0);
extern unsigned char D_80192290[];
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
extern unsigned char D_801931C0[];
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
extern s8 D_801931FC[];
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
extern u16 D_80193244;
extern u16 D_80193246;
extern u16 D_80193248;
extern s32 D_8019324C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80193254;
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
extern int D_80192F60;
extern void func_8015EE7C(s32 param_1);
extern void func_80159B70(void*);
extern void (*D_80192F7C[])(void*);
extern void func_8015EEE0(void* arg0);
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
extern unsigned int D_801932D8[];
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
extern void (*D_80193388[])(void);
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
extern u16 D_801933B8[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8019341C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801E3180[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80193440[])(void);
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
extern int D_801E31D8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80193488[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80193478;
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
extern char D_801E26F8[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80193490[])(void);
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
extern void (*D_801934E4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801934AC;
extern s16 D_801934E0;
extern s16 D_801934DE;
extern s16 D_801934DC;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_801934F0[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E3238;
extern u8 D_801E3239;
extern u8 D_801E323A;
extern u8 D_801E323B;
extern u8 D_801E323C;
extern u8 D_801E323D;
extern u8 D_801E323E;
extern u8 D_801E323F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80193500[])(void);
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
extern s32 D_801E3278;
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
extern void (*D_80193544[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801935C0[];
extern s32 D_801935E0[];
extern u8 D_8019365C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8019367C[];
extern u8 D_8019369C[];
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
extern void (*D_80193738[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801937B4[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801E2708;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801937C0[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801937C8[])(void);
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
extern void (*D_80193890[])(void);
extern void func_80166618(void *a0);
extern void (*D_801938A0[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801938B0[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801938BC[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8019381C[];
extern u8   D_80193830[];
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
extern void (*D_801938D4[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801938DC[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801938E4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801938EC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_801938F4[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_801938FC[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80193904[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801939B8[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801939C0[])(void);
extern void func_80169F00(void *a0);
extern char D_80193970[];
extern char D_80193930[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_801939F8[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80193A04[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80193A4C[])(void);
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
extern void (*D_80193AC8[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E3598;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80193ABC[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80193B00[];
extern unsigned short D_80193B08[];
extern unsigned short D_80193B10[];
extern unsigned char D_801E35A0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E3598;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80193B18[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E36D4;
extern M2C_UNK D_801E36D8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E3660;
extern void (*D_80193B48[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E36DC[];
extern u8 D_801E36E4[];
extern u8 D_801E3694[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80193B50[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80193B6C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80193B74[])(void);
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
extern void (*D_80193BDC[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80193B80;
extern u8 D_80193B8C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80193C10[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80193C18[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80193C6C[])(void);
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
extern u16 D_80193CA0[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80193C90[];
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
extern s32 D_80193CBC;
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
extern void (*D_80193D34[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80193D3C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80193D44[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80193D4C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80193D54[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80193D5C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80193D68[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80193D74[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80193D80[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80193D90[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80193DA0[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80193DA8[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80193DB0[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80193DB8[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80193DC0[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80193DC8[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80193DD0[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80193DD8[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80193DE0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80193DE8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80193DF0[])(void);
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
extern void (*D_80193DF8[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80193E00[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80193E08[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80193E10[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80193E18[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80193E20[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80193E28[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80193E30[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80193E38[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80193E40[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80193E48[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80193E50[])(void);
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
extern void (*D_80193E94[])(void);
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
extern M2C_UNK D_80193E58;
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
extern void (*D_80193EC4[])(void);
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
extern void (*D_80193F00[])(void);
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
extern s32 D_80126950;
extern void func_801748EC(void);
extern s32 func_801749C8();
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_80193F58[])();
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
extern void (*D_80193F68[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80193F70[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_801940D8[])();
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
extern void (*D_801940E4[])();
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
extern M2C_UNK D_801E2950;
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
extern s16 D_801E4BD8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801E3E18;
extern short D_801E4C4C;
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
extern s32 D_801E4244;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E426C;
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
extern s16 D_801E4228;
extern s32 func_8017A3B0(void);
extern short D_801E4264;
extern short D_801E4260;
extern int func_800D0CA0(int);
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);
extern int func_8017A3D8(void);
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
extern s16 D_801E4BA8;
extern s16 D_801E4BAA;
extern s16 D_801E4BB4;
extern void func_8017AE2C(s32 param_1);
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801E422C;
extern u16 D_801E42AC;
extern u16 D_801E42AE;
extern u16 D_801E42B0;
extern void func_8017B1D8(void);
extern s32 func_8017B238(s32 param_1, s32 param_2);
extern s32 func_8017B368(s32 param);
extern s32 func_8017B490(s32 param);
extern s32 func_8017B614(s32 param_1, s32 param_2);
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern u8 D_8012694C;
extern s16 D_801E42A4;
extern s16 D_801E42A6;
extern s16 D_801E42A8;
extern s16 D_801E429C;
extern s16 D_801E429E;
extern s16 D_801E42A0;
extern void func_8017B7A8(void);
extern s16 D_801E42BC;
extern s16 D_801E42BE;
extern s16 D_801E42C0;
extern s16 D_801E42C4;
extern s16 D_801E42C6;
extern s16 D_801E42C8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801E42B4;
extern short D_801E42B6;
extern short D_801E42B8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801E424C;
extern SV4 D_801E4254;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801E4274[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801E4270)(void);
extern void func_8017BD50(int param_1);
extern void (*D_801942C0[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BF14(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8017BEC0(s32 arg0, s32 arg1, s16 arg2);
extern void func_8017BEE8(void *a0, void *a1, s32 a2, s32 a3);
extern s32 func_8012C750(s32 a0);
extern void func_8017BF9C(s32 a0, s32 a1);
extern void func_8017BFF0(s32 a0, s32 a1, s32 a2);
extern void func_8017C048(void);
extern void (*D_80194320[])(void);
extern void func_8017C0F4(void *a0);
extern void func_8017C130(void *a0);
extern void func_800176F0(void *a0);
extern void func_8017C41C(void *a0);
extern void ReadRotMatrix(void *a0);
extern void PushMatrix(void);
extern void func_8004974C(void *a0, void *a1);
extern void PopMatrix(void);
extern void func_8017CC88(u16 *a0, void *a1);
extern int func_8017CD2C(short *param_1, short *param_2, short *param_3, int param_4);
extern void ReadGeomOffset(s32 *a0, s32 *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8004921C(s32 a0, s32 a1);
extern void func_8017CF24(s32 a0, s32 a1);
extern void func_8017CF90(s32 arg0);
extern void func_8017DF00(void);
extern void func_8017DF28(void);
extern void func_8017DF50(void);
extern void func_8012A094(s32 a0);
extern void func_8017E97C(void *a0);
extern void func_8017DF78(void);
extern Vec8_8017E0B4 D_801E2D70;
extern Vec8_8017E0B4 D_801E2D78;
extern s32 D_80126E60[];
extern s32 D_80126E6C;
extern s32 D_80126E9C;
extern s32 D_80126EA0;
extern s32 D_80126EA4;
extern s32 D_80126EA8;
extern s32 D_80126EAC;
extern s32 D_80126EB0;
extern void func_8012A100(s8 a0);
extern void func_8017E0B4(void);
extern void func_8017E190(void);
extern void func_8017E26C(void);
extern void func_8017E348(void);
extern void func_8017E5AC(void);
extern void func_8017E5CC(void);
extern void func_8017E664(void);
extern void func_8017E8E4(void);
extern void func_8017EB30(void);
extern void (*D_8019439C[])(void);
extern void func_8017F010(void *a0);
extern void func_8017F428(void *arg0);
extern s32 func_8017F04C(s32 param_1);
extern s32 func_8017F09C(void);
extern void (*D_801943A4[])(void);
extern void func_8017F0C0(void *a0);
extern s32 func_8017F0FC(u8 *a0);
extern void (*D_80194454[])(void);
extern void func_8017F1DC(void *a0);
extern void func_8017F218(u8 *a0);
extern void func_8017F320(s32 param_1);
extern void (*D_80194464[])(void);
extern void func_8017F358(void *a0);
extern void func_8017F3C4(int param_1);
extern void func_8017F408(void);
extern void (*D_80194470[])(void);
extern void func_8017F428(void *a0);
extern s32 D_801270C8;
extern void func_8017F6A4(void);
extern void func_8017F674(void);
extern void func_8017FA3C(void);
extern void func_8017FA0C(void);
extern void (*D_801944E8[])(void);
extern void func_80180380(void *a0);
extern void func_801804AC(void);
extern void aF801804D4();
extern void func_80180A7C(void);
extern void func_80180AA4(void *a0);
extern void func_80180AE0(void *a0);
extern void func_80180C04(void *a0);
extern void func_80180C64(void*);
extern void func_80180C3C(void);
extern void (*D_8019455C[])(void);
extern void func_80180C64(void *a0);
extern void func_8017E798(void *a0);
extern void func_80181028(void *a0);
extern void func_801812DC(void*);
extern void func_801812B4(void);
extern void (*D_8019458C[])(void);
extern void func_801812DC(void *a0);
extern void func_80181318(void *a0);
extern void func_80147060(u8*);
extern void func_8018166C(s32 a0);
extern s32 func_8018169C(s32 a0, s32 a1);
extern s32 func_801816CC(s32 a0, s32 a1);
/* ==== end §8b carried decl layer ==== */

extern void func_80182998(void);
extern s32 func_80185D84(s32);
extern void func_80186304();
extern void func_8018AD8C(s32, s32);
extern void func_801862E0(s32 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_801862F0(void * arg0);
extern void func_8018ADF0(s32);
extern void func_801838A8(u8*);

void func_80181D30(u8* arg0) {
    if (*(u32*)(arg0 + 0xE8) & 0x60000) {
        func_80182998();
        return;
    }

    switch (*(u16*)(arg0 + 0x34)) {
        case 0:
            if (((s32 (*)(u8*))func_80185D84)(arg0) != 0) {
                func_80186304(arg0, 4, 2);
                (*(u16*)(arg0 + 0x34))++;
            }
            break;
        case 1:
            if (*(s32*)(arg0 + 0x94) == 3) {
                func_8018AD8C(*(s16*)(arg0 + 0xE0), 7);
                ((void (*)(u8*))func_801862E0)(arg0);
                *(s32*)(arg0 + 0x1C) = 4;
                (*(u16*)(arg0 + 0x34))++;
                func_8002D4C8(0x4F5, 0);
            }
            break;
        case 2:
            if (((s32 (*)(u8*))func_8012BEE8)(arg0) != 0) {
                ((void (*)(u8*))func_801862F0)(arg0);
                (*(u16*)(arg0 + 0x34))++;
                func_8002D4C8(0x4F6, 0);
            }
            break;
        case 3:
            if (*(s16*)(arg0 + 0x98) == 0) {
                func_80186304(arg0, 5, 2);
                *(s32*)(arg0 + 0x1C) = 0x1A;
                (*(u16*)(arg0 + 0x34))++;
            }
            break;
        case 4:
            if (((s32 (*)(u8*))func_8012BEE8)(arg0) != 0) {
                func_80186304(arg0, 6, 2);
                (*(u16*)(arg0 + 0x34))++;
            }
            break;
        case 5:
            if (*(s32*)(arg0 + 0x94) == 9) {
                ((void (*)(u8*))func_801862E0)(arg0);
                func_8018ADF0(*(s16*)(arg0 + 0xE0));
                *(s32*)(arg0 + 0x1C) = 0x10;
                (*(u16*)(arg0 + 0x34))++;
            }
            break;
        case 6:
            if (((s32 (*)(u8*))func_8012BEE8)(arg0) != 0) {
                ((void (*)(u8*))func_801862F0)(arg0);
                (*(u16*)(arg0 + 0x34))++;
            }
            break;
        case 7:
            if (*(s16*)(arg0 + 0x98) == 0) {
                func_801838A8(arg0);
            }
            break;
    }
}


extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B200(u8 *a0);
extern void func_80181F68(void *a0);
extern s16 D_801E43A8;
extern s16 D_801E43B0;

void func_80181F04(void *a0) {
    s32 s0 = (s32)a0;
    s32 temp;
    u16 h1;
    u16 h2;

    func_8012B200((u8 *)s0);
    temp = *(s32 *)(s0 + 0xE8);
    h1 = *(u16 *)(s0 + 6);
    h2 = *(u16 *)(s0 + 0xE);
    temp &= ~1;
    D_801E43A8 = h1;
    *(s32 *)(s0 + 0xE8) = temp;
    D_801E43B0 = h2;
    func_8012AD44((s32 *)s0, 6);
    func_80181F68((void *)s0);
}


void func_80181F68(void *a0) {
        *(s16 *)((s32)a0 + 0x34) = 0;
    }


extern void func_80186304();

s32 func_80181F70(void *arg0)
{
    func_80186304((u8 *)arg0, 0x10, 0);
    *(u16 *)((s32)arg0 + 0x34) = 1;
}


void func_80181FA8(u8 *arg0) {
    func_80186304(arg0, 0x11, 0);
    func_80186C70(arg0);
    *(u16 *)((s32)arg0 + 0x34) = 2;
}


extern s32 D_801270C8;
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80181FE8(void *arg0) {
    if (*(s16 *)((s32)arg0 + 0xE0) >= 0) {
        D_801270C8 = 0x1B;
    }
    *(s32 *)((s32)arg0 + 0x14) = 0xFFC80000;
    *(s16 *)((s32)arg0 + 0x34) = 3;
    *(s32 *)((s32)arg0 + 0x1C) = 8;
    func_8002D4C8(0x508, 0);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018203C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80182098);

#include "common.h"

extern u16 D_801E43B4;
extern s32 D_801270C8;
extern u8 D_80195AFA[];
extern u8 D_8019103C;
extern void func_8018A1D8(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_80186304();
extern s32 func_801873FC(s32 a0);
extern u16 D_80126B96;
extern s16 D_80126B98;
extern void func_8002D4C8(s32 a0, s32 a1);

s32 func_801820E4(void *arg0)
{
    s16 idx;
    register u16 cnt asm("v0");

    idx = *(s16 *)((u8 *)arg0 + 0xE0);
    if (idx >= 0) {
        cnt = D_801E43B4;
        D_801270C8 = *(s16 *)((u8 *)D_80195AFA + idx * 8);
        D_801E43B4 = cnt + 1;
        *(u32 *)((u8 *)arg0 + 0xE8) = (*(u32 *)((u8 *)arg0 + 0xE8) & ~0x400) | 0x800;
    }
    func_8018A1D8((s32)arg0);
    func_8012B23C((s32)arg0);
    func_8013C9C4(&D_8019103C);
    func_80186304(arg0, 0x12, 0);
    *(s16 *)((u8 *)arg0 + 0x34) = 6;
    *(u32 *)((u8 *)arg0 + 0xE8) |= 0x20;
    if (func_801873FC((s32)arg0) != 0) {
        D_80126B96 = 0x4002;
        D_80126B98 = 10;
    }
    func_8002D4C8(0x501, 0);
}


void func_801821C8(s32 *arg0) {
    u16 t;
    u32 s1;

    func_801862E0(arg0);
    func_80186CA8((void *)arg0);

    t = *(u16 *)((s32)arg0 + 0xDC);
    t = t - 1;
    *(s16 *)((s32)arg0 + 0xDC) = t;

    if (*(s32 *)((s32)arg0 + 0xE8) & 0x800) {
        goto L224;
    }
    if (*(s16 *)((s32)arg0 + 0x76) >= 0x81) {
        goto L224;
    }
    if (t << 16) {
        s1 = 0x10;
    } else {
        s1 = 0x20;
    }
    goto L244;

L224:
    s1 = 0x60;
    if (*(s16 *)((s32)arg0 + 0xDC) != 0) {
        s1 = 0x30;
    }
    func_801840E8(*(s32 *)((s32)arg0 + 0xD4));

L244:
    if (*(s32 *)((s32)arg0 + 0xE8) & 0x2000) {
        *(s32 *)((s32)arg0 + 0x1C) = s1 >> 1;
    } else {
        *(s32 *)((s32)arg0 + 0x1C) = s1;
    }
    *(u16 *)((s32)arg0 + 0x34) = 7;
}


extern void func_801862F0(void * arg0);
    void func_80182284(s32 arg0) {
        s32 temp_s0 = arg0;
        ((void (*)(void))func_801862F0)();
        *(s16 *)(temp_s0 + 0x34) = 0x8;
    }


extern void func_8012B23C(s32 a0);

void func_801822B4(s32 arg0) {
    func_8012B23C(arg0);
    func_8017DF50();
    func_801838A8((u8 *)arg0);
}


#include "common.h"

extern u16 D_801E4BBC;
extern u8 D_80062BDC;
extern u8 D_80195B2C[];

extern void func_80019064(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B23C(s32 a0);
extern void func_80183B0C(void);
extern void func_80186304();
extern void func_80186C0C(void *a0);
extern void func_80186C70(void *a0);
extern void func_80186CA8();
extern void func_80186D74(void);
extern void func_80186F14(void *a0);

void func_801822EC(u8 *arg0) {
    s32 done = 0;

    switch (*(u16 *)(arg0 + 0x34)) {
        case 0:
            if (*(s16 *)(arg0 + 0x98) == 0) {
                if (D_801E4BBC == 1) {
                    func_80186304(arg0, 0x14, 1);
                    func_80186C70(arg0);
                    (*(u16 *)(arg0 + 0x34))++;
                } else {
                    done = 1;
                }
            }
            break;
        case 1:
            *(u16 *)(*(s32 *)(*(s32 *)(arg0 + 0xCC) + 0x20) + 0x12) -= 0x55;
            *(u32 *)(arg0 + 0xE8) &= ~0x20;
            if ((*(s32 *)(arg0 + 0x94) & 3) == 0) {
                if (*(s16 *)(arg0 + 0x98) == 1) {
                    func_80019064(&D_80062BDC);
                    func_8002D4C8(0x4F1, 0);
                    *(u32 *)(arg0 + 0xE8) |= 0x20;
                }
            }
            if (*(s16 *)(arg0 + 0x98) == 0) {
                done = 1;
                func_80183B0C();
                func_80186CA8(arg0);
                *(u32 *)(arg0 + 0xE8) &= ~0x20;
            }
            break;
    }

    if (done) {
        u32 temp;
        s32 v0_val;

        func_8012B23C((s32)arg0);

        *(u32 *)(arg0 + 0xE8) |= 1;
        func_80186304(arg0, 0, 0);

        temp = *(u32 *)(arg0 + 0xE8);
        if (temp & 0x2000) {
            *(u32 *)(arg0 + 0x1C) = 0x10;
        } else {
            *(u32 *)(arg0 + 0x1C) = 0x20;
        }

        v0_val = (s32)D_80195B2C | 0x40000000;
        *(u32 *)(arg0 + 0x58) = v0_val;
        *(s16 *)(arg0 + 0x5C) = 0;
        *(s16 *)(arg0 + 0xAE) = -1;

        func_8012AD44((s32 *)arg0, 1);
        func_80186F14((void *)arg0);

        *(u32 *)(arg0 + 0xE8) &= ~4;
        func_80186C0C((void *)arg0);
        func_80186D74();
    }
}


#include "common.h"

extern s32 func_8012CBCC(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B23C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80186304();
extern void func_8018A3B4(void *a0);
extern s32 func_8018ACB4(void *a0);
extern void func_8018AEB4(s32 a0, s32 a1);
extern s32 func_8018675C(void *a0);
extern void func_80186F58(void *a0);
extern void func_80184C20(s32 a0);
extern void func_80186BB8();
extern void func_80186CA8();
extern void func_80186D00(void);
extern void func_801900F4(void);
extern void func_80184184(s32 a0);
extern u16 D_801E4BBC;
extern u8 D_80195B3C[];

void func_801824D0(s32 s0) {
    u32 flags;
    s16 mode;

    if ((*(u32 *)(s0 + 0xE8) & 0x408) == 0) {
        if (*(s16 *)(s0 + 0xDC) != 0) {
            if (((s32 (*)(void))func_8012CBCC)() != 0) {
                mode = *(s16 *)(s0 + 0xDC);
                if (mode != 1) {
                    if (mode == 2) {
                        *(s32 *)(s0 + 0x14) = 0xFFF80000;
                    }
                } else {
                    *(s32 *)(s0 + 0x14) = 0;
                    *(s32 *)(s0 + 0x1C) = 0;
                }
                *(u16 *)(s0 + 0xDC) = *(u16 *)(s0 + 0xDC) - 1;
                func_8018A3B4((void *)s0);
            }
        } else {
            func_8012CBCC(s0);
            if ((*(s32 *)(s0 + 0x1C) & 3) == 0) {
                func_8018A3B4((void *)s0);
            }
            *(s32 *)(s0 + 0x1C) = *(s32 *)(s0 + 0x1C) + 1;
        }

        if (D_801E4BBC == 1) {
            s32 ret = func_8018ACB4((void *)s0);
            if (ret > 0) {
                func_8018AEB4(ret, 1);
            }
        }
        if (func_8018675C((void *)s0) != 0) {
            *(s32 *)(s0 + 0x18) = 0;
            *(s32 *)(s0 + 0x10) = 0;
        }
        return;
    }

    if (func_8012CBCC(s0) == 0) {
        return;
    }

    flags = *(u32 *)(s0 + 0xE8);
    if (flags & 0x400) {
        *(u32 *)(s0 + 0xE8) = flags & ~1;
        func_80186304((u8 *)s0, 0xD, 2);
        func_8012AD44((s32 *)s0, 9);
        *(u8 *)(s0 + 0xC1) = 0;
        *(s16 *)(s0 + 0xFE) = 0;
        func_80186CA8((void *)s0);
        *(s16 *)(s0 + 0x102) = 0xD;
    } else {
        func_8012B23C(s0);
        *(u32 *)(s0 + 0xE8) = *(u32 *)(s0 + 0xE8) & ~1;
        func_80186F58((void *)s0);
        *(s16 *)(*(s32 *)(*(s32 *)(s0 + 0xCC) + 0x20) + 0x12) = 0;
        func_80184C20(*(s32 *)(s0 + 0xD0));
        *(u32 *)(s0 + 0x58) = (s32)D_80195B3C | 0x40000000;
        *(s16 *)(s0 + 0x5C) = 0xA00;
        *(u32 *)(s0 + 0xE8) |= 4;
        func_8012AD44((s32 *)s0, 8);
        func_80186304((u8 *)s0, 0x13, 2);
        func_80186BB8((void *)s0);
        func_80186D00();
        switch (D_801E4BBC) {
        case 1:
            func_801900F4();
            break;
        case 2:
            func_80184184(*(s32 *)(s0 + 0xD4));
            *(s16 *)(s0 + 0x5C) = 0x800;
            break;
        }
    }
    func_8002D4C8(4, 0x50F);
    func_8002D4C8(0x507, 0);
}


extern void func_80186304();

void func_80182740(void *arg0) {
    s32 s0;

    __asm__ __volatile__("" : "=r"(s0) : "0"((s32)arg0));
    *(u32 *)(s0 + 0x18) = 0;
    if (*(u32 *)(s0 + 0xE8) & 0x2000) {
        *(u32 *)(s0 + 0x10) = 0x38000;
    } else {
        *(u32 *)(s0 + 0x10) = 0x1C000;
    }
    func_80186304((u8 *)s0, 1, 0);
    *(s16 *)(s0 + 0xE0) = -1;
}


#include "common.h"

extern void func_80186304();

void func_801827A8(void *a0) {
    s32 s0 = (s32)a0;

    *(u32 *)(s0 + 0x18) = 0;

    if (*(u32 *)(s0 + 0xE8) & 0x2000) {
        *(u32 *)(s0 + 0x10) = 0xFFFC8000;
    } else {
        *(u32 *)(s0 + 0x10) = 0xFFFE4000;
    }

    func_80186304((u8 *)s0, 2, 0);
    *(s16 *)(s0 + 0xE0) = -1;
}


#include "common.h"

extern void func_80186304();
extern s32  func_80186144(void *a0, s32 a1);
extern u16 D_801E4BBC;

void func_80182810(void *arg0) {
    s32 p = (s32)arg0;
    s32 v1;
    s32 t;

    v1 = *(s32 *)(p + 0xE8);
    if (v1 & 0x800) {
        if (v1 & 0x2000) {
            *(s32 *)(p + 0x10) = 0xFFFC8000;
        } else {
            *(s32 *)(p + 0x10) = 0xFFFE4000;
        }
        *(s32 *)(p + 0x18) = 0;
        *(s16 *)(p + 0xE0) = func_80186144((void *)p, 5);
    } else {
        if (v1 & 0x2000) {
            *(s32 *)(p + 0x18) = 0x38000u;
        } else {
            *(s32 *)(p + 0x18) = 0x1C000u;
        }
        *(s32 *)(p + 0x10) = 0;
        *(s16 *)(p + 0xE0) = -1;
    }
    t = D_801E4BBC;
    *(s32 *)(p + 0xE8) = *(s32 *)(p + 0xE8) | 0x1000;
    if (t == 1) {
        func_80186304((u8 *)p, -3, 0);
    } else {
        func_80186304((u8 *)p, 3, 0);
    }
}


#include "common.h"

extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186F14(void *a0);

void func_801828D8(void *arg0) {
    s32 s0 = (s32)arg0;
    u32 v;

    v = *(u32 *)(s0 + 0xE8);
    *(u32 *)(s0 + 0xE8) = v | 1;
    func_8012AD44((s32 *)s0, 2);
    func_80186F14((void *)s0);
}


#include "common.h"

extern void (*D_80191060[])(void);
extern s32 func_8012CBA4(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018655C(s32 a0);

void func_80182918(s32 a0) {
    s32 *s0 = (s32 *)a0;

    func_8012CBA4(a0);

    if (s0[0x94/4] == 1 || s0[0x94/4] == 0xD) {
        if (((s16 *)s0)[0x98/2] == 1) {
            func_8013C9C4(D_80191060);
            func_8002D4C8(0x4F1, 0);
            func_8002D4C8(0x50B, 0);
        }
    }

    func_8018655C((s32)s0);
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186304();
extern void func_80184C20(s32 a0);
extern void func_80186F58(void *a0);
extern void func_8018AAAC(void);

/* DECL RECONCILIATION (§183 TYPE-adopted-TU, wave Z): the TU already declares
 * `extern void func_80182998(void);` (line 2799) and calls it with no argument
 * (line 2812, inside func_80181D30, where $a0 still holds the caller's arg0).
 * The body genuinely reads its incoming $a0, so the parameter is recovered at
 * the USE SITE with a $4-pinned register variable copied ONCE into a normal
 * local (the copy is what lets gcc park it in $s0 across the calls — reading
 * `a0r` directly would re-read $4 after every jal).  Byte-identical to the
 * `void func_80182998(void *arg0)` spelling: MATCH (61 ins), so the TU needs
 * no edit and func_80181D30 needs no re-verification. */
void func_80182998(void) {
    register void *a0r __asm__("$4");
    void *arg0 = a0r;
    s32 flags;

    func_8012B23C((s32)arg0);
    *(u32 *)((s32)arg0 + 0xE8) &= ~1;
    func_80186F58(arg0);
    *(s16 *)(*(s32 *)(*(s32 *)((s32)arg0 + 0xCC) + 0x20) + 0x12) = 0;
    func_80184C20(*(s32 *)((s32)arg0 + 0xD0));
    func_8018AAAC();
    func_8012AD44((s32 *)arg0, 0xB);

    if (*(u32 *)((s32)arg0 + 0xE8) & 0x1000) {
        *(s16 *)((s32)arg0 + 0x104) = *(s32 *)((s32)arg0 + 0x1C);
    }

    flags = *(u32 *)((s32)arg0 + 0xE8);
    if ((flags & 0x60000) == 0x60000) {
        func_80186304((u8 *)arg0, 0x19, 2);
        *(s16 *)((s32)arg0 + 0x34) = 2;
    } else if (flags & 0x20000) {
        func_80186304((u8 *)arg0, 0x15, 2);
        *(s16 *)((s32)arg0 + 0x34) = 0;
    } else {
        func_80186304((u8 *)arg0, 0x17, 2);
        *(s16 *)((s32)arg0 + 0x34) = 1;
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80182A8C);

extern void func_80186178(s32 *a0);
extern void func_8012B23C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186304();

void func_80182D80(s32 arg0) {
    func_80186178((s32 *)arg0);
    func_8012B23C(arg0);
    func_8012AD44((s32 *)arg0, 0xC);
    func_80186304((u8 *)arg0, 0, 2);
}


extern void func_8018622C();

void func_80182DCC(void *a0) {
    func_8018622C(a0);
    *(u32 *)((s32)a0 + 0x14) = 0x100000;
    *(u16 *)((s32)a0 + 0x34) = 1;
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_80186304();
extern void func_8018A1D8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 D_801270C8;
extern u8 D_8019103C;

void func_80182E04(s32 arg0)
{
    func_8012B23C(arg0);
    func_8013C9C4(&D_8019103C);
    func_80186304((u8 *)arg0, 0, 2);
    *(s16 *)(arg0 + 0x34) = 2;
    D_801270C8 = 0x15;
    func_8018A1D8(arg0);
    func_8002D4C8(0x4FB, 0);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80182E78);

#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_80186304();
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186F14(void *a0);
extern u8 D_80195B2C[];
extern void func_8017BEE8(void *a0, void *a1, s32 a2, s32 a3);
extern u16 D_801E4398;
extern u16 D_801E439C;
extern s32 D_801E43C0;
extern s32 D_801E43C4;
extern void func_80185764();

void func_80182EB0(void) {
    register void *a0r __asm__("$4");
    s32 s0 = (s32)a0r;
    u32 temp;
    s32 v0_val;

    func_8012B23C(s0);

    *(u32 *)(s0 + 0xE8) |= 1;
    func_80186304((u8 *)s0, 0, 0);

    temp = *(u32 *)(s0 + 0xE8);
    if (temp & 0x2000) {
        *(u32 *)(s0 + 0x1C) = 0x10;
    } else {
        *(u32 *)(s0 + 0x1C) = 0x20;
    }

    v0_val = (s32)D_80195B2C | 0x40000000;
    *(u32 *)(s0 + 0x58) = v0_val;
    *(s16 *)(s0 + 0x5C) = 0;
    *(s16 *)(s0 + 0xAE) = -1;

    func_8012AD44((s32 *)s0, 1);
    func_80186F14((void *)s0);

    func_8017BEE8(&D_801E4398, &D_801E439C, 0, 0x60);
    D_801E43C0 = 0;
    D_801E43C4 = 0;
    func_80185764();
}


extern void func_8012B23C(s32 a0);

void func_80182F78(s32 arg0)
{
    func_8012B23C(arg0);
    *(s32 *)(arg0 + 0x10) = 0xFFE80000;
    *(s16 *)(arg0 + 0x34) = 0;
}


extern void func_8012B23C(s32 a0);
extern s16 D_801E43A8;
extern s16 D_801E43AC;
extern s16 D_801E43B0;

void func_80182FAC(s32 *s0)
{
    u16 var_a8;
    u16 var_ac;
    u16 var_b0;

    var_a8 = D_801E43A8;
    var_ac = D_801E43AC;
    var_b0 = D_801E43B0;

    *(u16 *)((u8 *)s0 + 6) = var_a8;
    *(u16 *)((u8 *)s0 + 0xA) = var_ac;
    *(u16 *)((u8 *)s0 + 0xE) = var_b0;
    func_8012B23C((s32)s0);

    *(s32 *)((u8 *)s0 + 0x10) = 0xFFE80000;
    *(u16 *)((u8 *)s0 + 0x34) = 1;
}


extern void func_8012B200(u8 *a0);
extern void func_801862E0(s32 *a0);
extern void func_80189FC4(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018300C(void *arg0) {
    func_8012B200((u8 *)arg0);
    func_801862E0((s32 *)arg0);
    *(s16 *)((u8 *)arg0 + 0x34) = 2;
    *(s32 *)((u8 *)arg0 + 0x1C) = 0x10;
    func_80189FC4((s32)arg0);
    func_8002D4C8(0x503, 0);
}


void func_80183060(void *a0) {
        *(short *)((char *)a0 + 0x34) = 0x3;
        *(int *)((char *)a0 + 0x1c) = 0x20;
    }


void func_80183074(s32 *a0) {
    extern s32 D_801270C8;
    extern s32 D_80196288[];
    D_801270C8 = 0x20;
    *(s16 *)((s32)a0 + 0x34) = 0x5;
    *(s32 *)((s32)a0 + 0x1C) = 0x70;
    *(s32 *)((s32)a0 + 0xE8) &= ~0x4000;
    func_8012C588(0x75, (s32)a0);
    func_80189FA4(a0);
    func_80019064(&D_80196288);
    func_8002D4C8(0x50D, 0);
}


extern u16 D_801E43C8;
extern void func_8018A7D8(u16 *a0, u16 *a1, s16 *a2, s32 a3);

func_801830F4(s32 a0, s32 a1)
{
    u16 a1arr[4];
    s16 a2arr[3];

    a1arr[0] = *(u16 *)(a0 + 6) - 0x40;
    a1arr[1] = *(u16 *)(a0 + 0xA) - 0x80;
    a1arr[2] = *(u16 *)(a0 + 0xE);
    a1arr[3] = 0x6000;
    a2arr[2] = 0x80;
    a2arr[0] = 0x80;
    a2arr[1] = 0x40;

    func_8018A7D8(&D_801E43C8, a1arr, a2arr, a1 & 0xFFFF);
}


void func_80183160(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x8;
        *(s16 *)((char *)a0 + 0x34) = 0x6;
    }


extern s32 D_801270C8;
extern void func_8002AB64(void);

s32 func_80183174(void *arg0) {
    D_801270C8 = 0x22;
    *(s16 *)((s32)arg0 + 0x34) = 7;
    func_8002AB64();
}


extern void func_80183218(void *arg0);
extern void func_80186600(s32 a0);
extern void func_80186DE8(s32 a0);
extern void (*D_801962C0[])(void *);

void func_801831A4(void *a0)
{
    func_80186600(a0);
    func_80183218(a0);
    ((void (**)(void *))D_801962C0)[*(u16 *)((s32)a0 + 2)](a0);
    func_80186DE8(a0);
}


void func_80183200(void *a0) {
        *(s8 *)((s32)a0 + 0xc1) = 0;
        *(s16 *)((s32)a0 + 0x5e) = 0;
        *(u16 *)((s32)a0 + 0x5c) &= 0xfffe;
    }


#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018415C(void *a0);
extern void func_8012B23C(s32 a0);
extern void func_80186F58(void *a0);
extern void func_80184C20(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186304();
extern void func_80186BB8();
extern void func_80186D00(void);
extern void func_801900F4(void);
extern void func_80184184(s32 a0);
extern void func_8018AAAC(void);
extern void func_8017DF50(void);
extern s32  func_80186144(void *a0, s32 a1);
extern void func_80186ADC(s32 a0);
extern u16 D_801E4398;
extern u16 D_801E4BBC;
extern u8  D_80195B3C[];

void func_80183218(void *arg0) {
    s32 p = (s32)arg0;
    s32 flags;
    s32 t;
    s32 w;

    if (*(u16 *)(p + 0x2) != 0) {
        flags = *(s32 *)(p + 0xE8);
        if (flags & 0x10) {
            t = *(u16 *)(p + 0x76) - *(u16 *)(p + 0x60);
            *(u16 *)(p + 0x76) = t;
            *(s32 *)(p + 0xE8) = flags & ~0x10;
            w = *(s16 *)(p + 0x76);
            D_801E4398 = t;
            if (w < 0) {
                D_801E4398 = 0;
                *(s16 *)(p + 0x76) = 0;
            }
            *(s16 *)(p + 0x60) = 0;
            func_8002D4C8(0x4F3, 0);

            if (*(s16 *)(p + 0x76) == 0) {
                *(u32 *)(p + 0xE8) &= 0xFFF1FFFF;
                func_8018415C(*(void **)(p + 0xD4));

                if (*(u32 *)(p + 0xE8) & 0x8) {
                    func_8012B23C(p);
                    *(u32 *)(p + 0xE8) &= ~1;
                    func_80186F58((void *)p);
                    *(s16 *)(*(s32 *)(*(s32 *)(p + 0xCC) + 0x20) + 0x12) = 0;
                    func_80184C20(*(s32 *)(p + 0xD0));
                    *(s32 *)(p + 0x58) = (s32)D_80195B3C | 0x40000000;
                    *(s16 *)(p + 0x5C) = 0xA00;
                    *(u32 *)(p + 0xE8) |= 4;
                    func_8012AD44((s32 *)p, 8);
                    func_80186304((u8 *)p, 0xA, 2);
                    func_80186BB8((void *)p);
                    func_80186D00();
                    switch (D_801E4BBC) {
                    case 1:
                        func_801900F4();
                        break;
                    case 2:
                        func_80184184(*(s32 *)(p + 0xD4));
                        *(s16 *)(p + 0x5C) = 0x800;
                        break;
                    }
                } else {
                    *(u32 *)(p + 0xE8) &= ~1;
                    *(s16 *)(*(s32 *)(*(s32 *)(p + 0xCC) + 0x20) + 0x12) = 0;
                    func_80184C20(*(s32 *)(p + 0xD0));
                    func_8018AAAC();
                    func_80186F58((void *)p);
                    func_8012B23C(p);
                    *(s32 *)(p + 0x18) = 0xA8000;
                    *(s16 *)(p + 0xDC) = 2;
                    *(s32 *)(p + 0x14) = 0xFFF40000;
                    func_80186304((u8 *)p, 0xC, 3);
                    func_8012AD44((s32 *)p, 0xA);
                    if (D_801E4BBC == 2) {
                        func_8017DF50();
                        if (*(u32 *)(p + 0xE8) & 0x800) {
                            s32 t = *(s32 *)(p + 0x18);
                            *(s32 *)(p + 0x18) = 0;
                            *(s32 *)(p + 0x10) = -t;
                            *(s16 *)(p + 0xE0) = func_80186144((void *)p, 5);
                        }
                    }
                    func_80186BB8((void *)p);
                    func_8002D4C8(0x50F, 0);
                }
            }
        }
    }

    if (*(s16 *)(p + 0xDE) != 0) {
        if (--*(s16 *)(p + 0xDE) == 0) {
            func_80186ADC(p);
        }
    }
}


extern void func_801804AC(void);
extern void func_801858C4();

void func_801834C8(void *arg0)
{
    *(u8 *)((s32)arg0 + 0xC1) = 3;
    *(s32 *)((s32)arg0 + 0x1C) = 0x10;
    *(u16 *)((s32)arg0 + 0x5C) &= 0xF5FE;
    *(s16 *)((s32)arg0 + 0x98) = 0;
    *(s32 *)((s32)arg0 + 0x58) = 0;
    *(u32 *)((s32)arg0 + 0xE8) &= 0xFFFEFFFF;
    func_801804AC();
    ((void (*)(void))func_801858C4)();
}


#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80186304();

void func_80183524(s32 arg0) {
    func_8012BEE8(arg0);
    if (*(s32 *)(arg0 + 0x1C) == 1) {
        func_80186304((u8 *)arg0, 0xB, 2);
    }
    if (*(u16 *)(arg0 + 0x72) & 0x4000) {
        func_8002D4C8(0x4ED, 0);
    }
}


extern void func_80186304();
extern void func_8012B200(u8 *a0);
extern void func_80132DC4(s32 a0, s32 a1, s32 a2);
extern u16 D_801E4BBC;
extern u16 D_80195ADC[];
extern void func_8018A968(s32 a0);

void func_80183584(void *arg0) {
    s32 s0 = (s32)arg0;
    u16 t;

    func_80186304((u8 *)arg0, 0xC, 2);
    func_8012B200((u8 *)s0);
    func_80132DC4(s0, (s32)&D_80195ADC[D_801E4BBC * 4], 0x300);
    *(u8 *)(s0 + 0xC1) = 4;
    *(u8 *)(s0 + 0xC2) = 0;
    t = D_801E4BBC;
    *(u16 *)(s0 + 0x5C) &= ~1;
    if (t == 0) {
        func_8018A968(*(s32 *)(s0 + 0xCC));
    }
}


#include "common.h"

extern u16 D_801E4BBC;
extern s32 D_801E43A0;
extern s16 D_801E43A8;
extern s16 D_801E43AC;
extern s16 D_801E43B0;

extern s16 D_80195AC6[];
extern u16 D_80195ADC[];
extern s16 D_80195AE0[];
extern s16 D_80195AEC;
extern s32 D_80195B1C[];

extern void func_8012CBF4(s32 a0);
extern s32 func_8012CBA4(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80186304();
extern void func_80182F78();
extern void func_8018A3B4(void *a0);
extern void func_80186CA8();
extern void func_8018592C(u8 *arg0);

void func_80183610(u8 *arg0) {
    s16 temp;
    u16 t6;
    u16 tA;
    u16 tE;

    switch (arg0[0xC2]) {
    case 0:
        func_8012CBF4((s32)arg0);
        if (D_801E4BBC == 2) {
            if (*(s16 *)(arg0 + 6) <= D_80195AEC) {
                arg0[0xC1] = 0;
                *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = -0x400;
                func_8012AD44((s32 *)arg0, 0xD);
                t6 = *(u16 *)(arg0 + 6);
                tA = *(u16 *)(arg0 + 0xA);
                tE = *(u16 *)(arg0 + 0xE);
                D_801E43A8 = t6;
                D_801E43AC = tA;
                D_801E43B0 = tE;
                func_80182F78(arg0);
            }
        } else if (*(s16 *)(arg0 + 0xE) >= D_80195AE0[D_801E4BBC * 4]) {
            func_8012B23C((s32)arg0);
            ((s16 *)arg0)[3] = D_80195ADC[D_801E4BBC * 4];
            *(s32 *)(arg0 + 0x18) = 0x180000;
            ((s16 *)(*(s32 *)(arg0 + 0x20)))[9] = 0;
            D_801E43A0 |= D_80195B1C[D_801E4BBC];
            arg0[0xC2]++;
        }
        break;
    case 1:
        if ((((s32 (*)(s32))func_8012CBF4)((s32)arg0) & 0x2000) != 0) {
            *(s32 *)(arg0 + 0x14) = 0;
            *(s32 *)(arg0 + 0x4C) = -0x4000;
            *(s16 *)(arg0 + 0x98) = 0;
            *(s32 *)(arg0 + 0x1C) = 0;
            arg0[0xC2]++;
            func_8002D4C8(0x507, 0);
        }
        break;
    case 2:
        func_8012CBA4((s32)arg0);
        *(s32 *)(arg0 + 0x1C) += 1;
        if ((*(s32 *)(arg0 + 0x1C) & 1) == 0) {
            func_8018A3B4(arg0);
        }
        temp = D_80195AC6[D_801E4BBC * 2];
        if (*(s16 *)(arg0 + 0xE) >= temp) {
            *(s16 *)(arg0 + 0xE) = temp;
            *(s16 *)(arg0 + 6) = -0x80;
            arg0[0xC2]++;
            func_8012B23C((s32)arg0);
            *(s32 *)(arg0 + 0x1C) = 0x10;
        }
        break;
    case 3:
        if (func_8012BEE8((s32)arg0) != 0) {
            *(s32 *)(arg0 + 0xE8) &= ~1;
            func_80186304(arg0, 0xD, 2);
            func_8012AD44((s32 *)arg0, 9);
            arg0[0xC1] = 0;
            *(s16 *)(arg0 + 0xFE) = 0;
            func_80186CA8(arg0);
            func_8018592C(arg0);
        }
        break;
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_801838A8);

#include "common.h"

extern void func_80187348(s32 a0, s32 a1);
extern void func_80187280(s32 a0, s32 a1);
extern void func_801851E0(s32 a0);

extern s32 D_801E43DC;
extern s32 D_801E43E0;
extern s32 D_801E43E4;
extern s32 D_801E43E8;
extern volatile s32 D_801E43EC;
extern volatile s32 D_801E43F0;
extern volatile s32 D_801E43F4;
extern volatile s32 D_801E43F8;

extern u16 D_80195E44[];
extern u16 D_80195E78[];
extern u16 D_80195EAC[];
extern u16 D_80195EE0[];

void func_80183B0C(void)
{
    func_80187348(D_801E43EC, 9);
    func_80187348(D_801E43F0, 10);
    func_80187348(D_801E43F4, 11);
    func_80187348(D_801E43F8, 12);

    func_80187280(D_801E43DC, 5);
    func_80187280(D_801E43E0, 6);
    func_80187280(D_801E43E4, 7);
    func_80187280(D_801E43E8, 8);

    func_801851E0(D_801E43DC);
    func_801851E0(D_801E43E0);
    func_801851E0(D_801E43E4);
    func_801851E0(D_801E43E8);

    *(u16 *)(D_801E43EC + 0x76) = D_80195E44[0];
    *(u16 *)(D_801E43F0 + 0x76) = D_80195E78[0];
    *(u16 *)(D_801E43F4 + 0x76) = D_80195EAC[0];
    *(u16 *)(D_801E43F8 + 0x76) = D_80195EE0[0];

    *(u16 *)(D_801E43EC + 0x5C) = 0x8400;
    *(u16 *)(D_801E43F0 + 0x5C) = 0;
    *(u16 *)(D_801E43F4 + 0x5C) = 0x8400;
    *(u16 *)(D_801E43F8 + 0x5C) = 0;
}


extern u16 D_80126614;
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);
extern void func_8001C1E4(s32);

s32 func_80183C7C(void *a0) {
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;
    u16 *s0 = &D_80126614;
    s32 s1 = (s32)a0;

    if (*s0 != 0) {
        return 0;
    }

    buf.f04 = 0;
    buf.f02 = 0;
    buf.f00 = 0;
    buf.f06 = 0x40;
    buf.f0A = 0;
    buf.f08 = 0;
    buf.f0E = 0;
    buf.f10 = 0;

    s0 = (u16 *)func_8012C890((s32)&buf, (s32)s0, s1);
    if (s0 != 0) {
        ((void (*)(s32, s32))func_8001C1E4)(*(s32 *)((u8 *)s0 + 0x20), *(s32 *)((u8 *)s1 + 0x20));
    }
    return (s32)s0;
}



extern void (*D_80196320[])(void);

void func_80183D18(void *a0) {
    D_80196320[*(u16 *)((s32)a0 + 0x2)]();
}


extern void (*D_80196328[])(void);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80183D54(s32 a0) {
    *(u8 *)(a0 + 0xC1) = 0;
    *(u16 *)(a0 + 0x5E) = 0;
    *(u32 *)(a0 + 0x58) = (s32)D_80196328 | 0x40000000;
    func_8012AD44((s32 *)a0, 1);
}


#include "common.h"

extern u16 D_801D323A;
extern u16 D_800B99D8;
extern u16 D_801E4BBC;
extern u8 D_801E44A0;
extern u8 D_801E44A1;

extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);

void func_80183D90(void *arg0) {
    s16 sv0[4];
    s16 sv1[4];
    u8 *p = (u8 *)arg0;
    s32 s1;
    u16 f;
    s32 t;
    s32 x, y;
    u16 g;

    D_801D323A += 0x40;
    func_80132784((s32)arg0, *(s32 *)(p + 0x64), 0x15);

    f = *(u16 *)(p + 0xFC);
    if (f & 3) {
        if (f & 1) {
            if (*(s16 *)(p + 0xE) > 0) {
                *(s16 *)(p + 0xE) = *(s16 *)(p + 0xE) - 4;
            } else {
                *(u16 *)(p + 0xFC) = f & 0xFFFE;
                *(s16 *)(p + 0xAE) = 0;
            }
        } else {
            if (*(s16 *)(p + 0xE) < 0x18) {
                *(s16 *)(p + 0xE) = *(s16 *)(p + 0xE) + 4;
            } else {
                *(u16 *)(p + 0xFC) = f & 0xFFFD;
            }
        }
    }

    s1 = *(s32 *)(p + 0xCC);
    if (s1 == 0) {
        return;
    }

    if (*(s16 *)(p + 0xE) >= 0x13 || *(s32 *)(*(s32 *)(p + 0x20) + 4) < 0) {
        *(s32 *)(s1 + 4) |= 0x80000000;
    } else {
        *(s32 *)(s1 + 4) &= 0x7FFFFFFF;
        func_8004914C((void *)(*(s32 *)(p + 0x20) + 0x34));
        func_800491AC((void *)(*(s32 *)(p + 0x20) + 0x34));

        sv0[0] = 0;
        sv0[1] = 0x18;
        sv0[2] = -0x68;
        RotTransSV(sv0, (void *)(s1 + 8), sv1);

        t = *(s16 *)(p + 0xE);
        if (t < 8) {
            *(s16 *)(s1 + 0x1A) = (8 - t) * 0x240;
            *(s16 *)(s1 + 0x18) = (8 - t) * 0x240;
        } else {
            *(s16 *)(s1 + 0x1A) = 0;
            *(s16 *)(s1 + 0x18) = 0;
        }

        g = D_800B99D8;
        if (g & 0x20) {
            s32 v = g & 0x1F;
            y = v | 0x20;
            x = v * 4 + 0x70;
        } else {
            s32 v = g & 0x1F;
            y = 0x40 - v;
            x = 0xF0 - v * 4;
        }

        if (D_801E4BBC == 2) {
            s32 q = *(s16 *)(*(s32 *)(p + 0x64) + 0x76);
            if (q < 0x41) {
                if (q < 0x19) {
                    D_801E44A0 = x;
                    D_801E44A1 = y;
                } else {
                    D_801E44A0 = x;
                    D_801E44A1 = x;
                }
                return;
            }
        }
        D_801E44A0 = y;
        D_801E44A1 = x;
    }
}


#include "common.h"

typedef struct { u8 b[4]; } Blk4_80183FCC;

extern void func_8001C924(s32 a0, void *a1);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8001CD9C(int a0, void *a1);
extern void func_8001D074(s32 a0, s32 a1);
extern void func_801840E8(s32 a0);

extern u8 D_801F12E8;
extern u8 D_801D3230;
extern u16 D_801D323A;
extern u8 D_801E44A0;
extern u8 D_801E44A4;
extern u8 D_801E2E70;
extern u8 D_801E2E74;

void func_80183FCC(s32 param_1)
{
    u8 *s2;
    s32 s0;

    func_8001C924(*(s32 *)(param_1 + 0x20), &D_801F12E8);

    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (s32)&D_801D3230;
    D_801D323A = 0;

    *(u16 *)(param_1 + 0xE) = 0x18;
    if (*(u16 *)(param_1 + 0xFC) & 1) {
        func_801840E8(param_1);
    }

    func_80132784(param_1, *(s32 *)(param_1 + 0x64), 0x15);

    s2 = &D_801E44A0;
    func_800233CC(s2, 0x28);

    *(Blk4_80183FCC *)s2 = *(Blk4_80183FCC *)&D_801E2E70;
    *(Blk4_80183FCC *)&D_801E44A4 = *(Blk4_80183FCC *)&D_801E2E74;

    s0 = ((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
    *(s32 *)(param_1 + 0xCC) = s0;
    if (s0 != 0) {
        func_8001CD9C(s0, s2);
        *(u16 *)(s0 + 0x2C) = 0xC010;
        *(u32 *)(s0 + 4) |= 0xD0000000;
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);

void func_801840E8(s32 a0)
{
    if (*(u32 *)(*(s32 *)(a0 + 0x64) + 0xE8) & 2) {
        if (*(s16 *)(a0 + 0xE) == 0x18) {
            *(u16 *)(a0 + 0xFC) |= 1;
            func_8002D4C8(0x50A, 0);
        }
    } else {
        *(u16 *)(a0 + 0xFC) |= 1;
    }
}


void func_8018415C(void *a0) {
        s32 v0;
        if (*(s16 *)((s32)a0 + 0xe) == 0) {
            *(s16 *)((s32)a0 + 0xae) = -1;
            v0 = *(u16 *)((s32)a0 + 0xfc);
            *(u16 *)((s32)a0 + 0xfc) = v0 | 2;
        }
    }


void func_80184184(s32 a0) {
    s32 a1;

    a1 = *(s32 *)(a0 + 0x20);
    *(u8 *)(a0 + 0xC1) = 0;
    *(u16 *)(a0 + 0x5E) = 0;
    *(s32 *)(a0 + 0x1C) = 0x18;
    *(u32 *)(a1 + 4) |= 0x80000000;
    *(u16 *)(a0 + 2) = 4;
    if (*(s32 *)(a0 + 0xCC) != 0) {
        *(u16 *)*(s32 *)(a0 + 0xCC) = 0;
    }
    func_8002D4C8(0x509, 0);
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018A7D8(u16 *a0, u16 *a1, s16 *a2, s32 a3);

extern u16 D_801E43C8;
extern s16 D_8019633C;
extern s16 D_8019633E;
extern s16 D_80196340;
extern s16 D_80196342;
extern s16 D_80196344;
extern s16 D_80196346;

void func_801841E0(void *a0) {
    if (*(u16 *)((u8 *)a0 + 0x34) == 0) {
        if (func_8012BEE8((s32)a0) != 0) {
            *(u16 *)((u8 *)a0 + 0x34) = *(u16 *)((u8 *)a0 + 0x34) + 1;
        } else {
            void *p20;
            u16 flags;
            u16 a1arr[4];
            s16 a2arr[3];

            p20 = *(void **)((u8 *)a0 + 0x20);
            flags = *(u16 *)((u8 *)p20 + 0x2C);
            *(u16 *)((u8 *)p20 + 0x2C) = flags & 0xFFFE;

            func_80132784((s32)a0, *(s32 *)((u8 *)a0 + 0x64), 0x15);

            a1arr[0] = *(s32 *)((u8 *)*(void **)((u8 *)a0 + 0x20) + 0x48) + 0x70;
            a1arr[1] = *(s32 *)((u8 *)*(void **)((u8 *)a0 + 0x20) + 0x4C) - 0x10;
            a1arr[2] = *(s32 *)((u8 *)*(void **)((u8 *)a0 + 0x20) + 0x50);
            a1arr[3] = 0x3000;

            a2arr[0] = (D_8019633E - D_8019633C) >> 1;
            a2arr[1] = (D_80196342 - D_80196340) >> 1;
            a2arr[2] = (D_80196346 - D_80196344) >> 1;

            func_8018A7D8(&D_801E43C8, a1arr, a2arr, 0);

            if ((D_801E43C8 & 3) != 0) {
                return;
            }
            func_8002D4C8(0x4F4, 0);
        }
    }
}



extern void (*D_801963E8[])(void);

void func_8018431C(void *a0) {
    D_801963E8[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_801E44E0;
extern s32 D_801963D0;
extern s32 *D_801D6D94;
extern void func_801858C4();
void func_80184358(u8 *arg0) {
    register u8 *a0 __asm__("$4") = arg0;
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    v0 = *(u16 *)(a0 + 0x5C);
    v1 = *(s32 *)(a0 + 0x64);
    *(u16 *)(a0 + 0x5C) = v0 & 0xFFFE;
    v0 = *(s32 *)(v1 + 0xE8);
    if (v0 & 2) {
        *(u8 *)(a0 + 0xC1) = 1;
        *(s32 *)(a0 + 0x1C) = 8;
        func_80185A04(a0, *(s32 *)(a0 + 0x64), *(s16 *)(a0 + 0x60));
        func_801858C4(a0);
    } else {
        *(u8 *)(a0 + 0xC1) = 0;
        *(s16 *)(a0 + 0xAE) = -1;
        func_8012AD44((s32 *)a0, 3);
        func_80132288(&D_801E44E0, &D_801963D0, (s32)D_801D6D94);
        func_801858C4(a0);
        func_8002D4C8(0x4F2, 0);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8013240C(s32 a0, s32 a1, u32 a2);
extern s32 D_801E44E0;

void func_80184404(s32 a0) {
    register s32 s0 __asm__("$16") = a0;
    register s32 temp_a0 __asm__("$4") = a0;
    s32 a1;
    s32 v0;
    u32 a2 = 0x15;

    a1 = *(s32 *)(s0 + 0x64);
    v0 = *(s32 *)(a1 + 0xE8);

    if ((v0 & 0x2) == 0) {
        func_8013240C((s32)&D_801E44E0, a1, 0x15);
        temp_a0 = s0;
        a1 = *(s32 *)(s0 + 0x64);
        a2 = 0;
    }

    func_80132784(temp_a0, a1, a2);

    v0 = func_8012BEE8(s0);
    if (v0 != 0) {
        *(u8 *)(s0 + 0xC1) = 0;
        *(u16 *)(s0 + 0x5E) = 0;
    }
}


extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B200(u8 *a0);
extern s32 D_801963FC;

void func_80184480(s32 arg0) {
    s32 s0 = arg0;

    *(s32 *)(s0 + 0x58) = (s32)&D_801963FC;
    *(u16 *)(s0 + 0x5C) = 0x8C00;
    func_8012AD44((s32 *)s0, 1);
    func_8012B200((u8 *)s0);
    *(s32 *)(s0 + 0xC) = 0;
    *(s32 *)(s0 + 8) = 0;
    *(s32 *)(s0 + 4) = 0;
}


void func_801844D4(s32 arg0) {
    s32 self = arg0;
    s32 v0;
    s32 v1;

    func_8012AD44((s32 *)self, 2);
    v0 = *(s32 *)(self + 0x64);
    v0 = *(s32 *)(v0 + 0x20);
    v0 = *(u16 *)(v0 + 0x12);
    *(s16 *)(self + 0xFE) = 0x10;
    *(s16 *)(self + 0xFC) = v0 + 0x200;
    v1 = func_8012C658(0x53, 6, self);
    *(s32 *)(self + 0xCC) = v1;
    if (v1 != 0) {
        *(s32 *)(v1 + 0xCC) = *(s32 *)(*(s32 *)(self + 0x64) + 0xCC);
    }
}


#include "common.h"

/* File-local mirror types: match_one compiles standalone with -Iinclude
 * only, so the TU's real Blk20 (src/shared/engine_types.h) is not
 * reachable here. These mirror its exact byte layout. */
typedef struct { s32 w[8]; } Blk20_8018454C;
typedef struct { s16 vx, vy, vz, pad; } SVec3_8018454C;

extern Blk20 D_800AE620;
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void RotMatrixY(s32 a0, void *a1);

#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_ldv0(r0)  __asm__ __volatile__( \
    "lwc2 $0, 0(%0)\n" \
    "lwc2 $1, 4(%0)\n" \
    : : "r"(r0) : "memory")

#define gte_rtv0()  __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 3, 0\n" \
    : : : "memory")

#define gte_stlvnl(r0)  __asm__ __volatile__( \
    "swc2 $25, 0(%0)\n" \
    "swc2 $26, 4(%0)\n" \
    "swc2 $27, 8(%0)\n" \
    : : "r"(r0) : "memory")

void func_8018454C(s32 a0)
{
    s32 self;
    Blk20_8018454C mat;
    SVec3_8018454C vec;
    s32 res[3];
    u16 counter;
    s16 angle;

    self = a0;
    mat = (*(Blk20_8018454C *)&D_800AE620);

    func_80132784(self, *(s32 *)(*(s32 *)(self + 0x64) + 0xCC), 6);

    counter = *(u16 *)(self + 0x34);
    if (counter == 0) {
        angle = *(s16 *)(self + 0xFE);
        if (angle < 0xA0) {
            *(s16 *)(self + 0xFE) = angle + 5;
        } else {
            *(u16 *)(self + 0x34) = counter + 1;
        }
    }

    {
        s32 facing = (*(u16 *)(self + 0xFC) - 0x100) & 0xFFF;
        *(u16 *)(self + 0xFC) = facing;
        RotMatrixY(facing, &mat);
    }

    vec.vy = 0;
    vec.vx = 0;
    vec.vz = *(u16 *)(self + 0xFE);

    gte_SetRotMatrix(&mat);
    gte_ldv0(&vec);
    gte_rtv0();
    gte_stlvnl(res);

    *(s32 *)(*(s32 *)(self + 0x20) + 0x48) += res[0];
    *(s32 *)(*(s32 *)(self + 0x20) + 0x4C) += res[1];
    *(s32 *)(*(s32 *)(self + 0x20) + 0x50) += res[2];
}


#include "common.h"

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
} D_80195AF4_t;
extern D_80195AF4_t D_80195AF4[];


extern D_80195AF6_t D_80195AF6[];

extern s16 D_80126CB4;
extern s16 D_80126CB8;
extern u16 D_801E4BBC;
extern void *func_8018ABE0(s32 a0);
extern void func_80132DC4(s32 a0, s32 a1, s32 a2);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_801846CC(void *a0)
{
    struct {
        s16 f0;
        s16 f2;
        s16 f4;
        u8 pad[8];
    } local;

    *(u16 *)((u8 *)a0 + 0x100) = *(u16 *)((u8 *)(*(void **)((u8 *)a0 + 0x64)) + 0xE0);
    *(s16 *)((u8 *)a0 + 0x6) = *(s32 *)((u8 *)(*(void **)((u8 *)a0 + 0x20)) + 0x48);
    *(s16 *)((u8 *)a0 + 0xA) = *(s32 *)((u8 *)(*(void **)((u8 *)a0 + 0x20)) + 0x4C);
    *(s16 *)((u8 *)a0 + 0xE) = *(s32 *)((u8 *)(*(void **)((u8 *)a0 + 0x20)) + 0x50);

    if (*(s16 *)((u8 *)a0 + 0x100) < 0) {
        local.f0 = D_80126CB4;
        local.f2 = *(u16 *)((u8 *)(*(void **)((u8 *)a0 + 0x64)) + 0xA);
        local.f4 = D_80126CB8;
    } else {
        if (D_801E4BBC == 1) {
            void *p = func_8018ABE0(*(s16 *)((u8 *)a0 + 0x100));
            local.f0 = *(u16 *)((u8 *)p + 0x6);
            local.f2 = *(u16 *)((u8 *)p + 0xA) + 0x80;
            local.f4 = *(u16 *)((u8 *)p + 0xE);
        } else {
            local.f0 = D_80195AF4[*(s16 *)((u8 *)a0 + 0x100)].f0;
            local.f2 = *(u16 *)((u8 *)(*(void **)((u8 *)a0 + 0x64)) + 0xA);
            local.f4 = D_80195AF6[*(s16 *)((u8 *)a0 + 0x100)].f0;
        }
    }

    if (*(s32 *)((u8 *)(*(void **)((u8 *)a0 + 0x64)) + 0xE8) & 0x2000) {
        func_80132DC4((s32)a0, (s32)&local, 0x480);
    } else {
        func_80132DC4((s32)a0, (s32)&local, 0x400);
    }
    func_8012AD44((s32 *)a0, 3);
}


/* func_80184828 (ov_SC02_005, TU src/ov_SC02_005/ov_SC02_005_jr_80181D30.c) — MATCH 111/111.
 *
 * Second-pass repair of the pass-1 NEAR (closeness 33, "schedule-load-gap").  The pass-1 draft
 * had the whole structure right; the residual was 33 ins in the final else-arm tail (2 gas
 * load-delay nops + everything downstream of them).  Three levers, applied in this order:
 *
 *  1. STATEMENT ORDER (sched.md S1) — the `D_801270C8 = ...f4` store must come BEFORE
 *     `D_801E43B4 += 1`.  Pass-1 had them the other way, which serialised the two independent
 *     chains onto ONE scratch register ($v0) and cost both load-delay nops.  33 -> 5.
 *     (Swept all 30 legal permutations of {s1=1, sh 0xE, f4 store, D_801E43B4 RMW} incl. a
 *      split read/write of the RMW: the whole family plateaus at 5.  Order alone cannot finish.)
 *
 *  2. MEM_IN_STRUCT_P ON THE 0xE STORE (sched.md §1 item 1 / §30 store-vs-load flag) — the
 *     residual-4 was a clean 2-block swap: target 79..83 = lh 0x100 / lui+lhu D_801E43B4 /
 *     li $s1 / sh 0xE, mine had {li,sh} and {lui,lhu} transposed.  No statement order can
 *     reach it (LUID model is self-contradictory: the 0x100 reload only EXISTS because the
 *     0xE store precedes it and defeats cse, yet the schedule wants the store's LUID higher).
 *     Spelling the 0xE store as a struct-field write — `((struct S0E *)((u8*)a0+0xE))->v` —
 *     sets MEM_IN_STRUCT_P on that MEM, which changes the sched dependence/hazard classing
 *     against the plain-cast `lh 0x100` load and lands the target's exact order.  5 -> 1.
 *     NOTE both arms of `D_801E4BBC == 1` use the struct spelling; the other arm is unaffected.
 *
 *  3. THE ADDU OPERAND ORDER (cookbook §164-03 + §164-02/§153) — last residual was
 *     `addu $v0,$v0,$a1` vs target `addu $v0,$a1,$v0` (sides wrong, registers right).
 *     BOTH halves are needed and neither works alone:
 *       (a) §164-03: hoist the scale into its own local (`off = idx * 8;`) so expand's
 *           `both_summands` "put a multiplication first" canonicalisation cannot fire;
 *       (b) §164-02/§153: `__asm__("" : "=r"(p) : "0"(p))` launders `p` out of cse's
 *           constant-equivalence class.  `p = D_80195AF6` is a bare `la sym`, so `insert`
 *           gives its quantity qty_const and `fold_rtx` (cse.c:5282-5289) swaps any
 *           commutative rtx whose operand 0 is constant-equivalent — i.e. it forces
 *           index-first for EITHER source spelling.  Killing qty_const restores Fix A1.
 *     The launder is an #APP scheduling barrier, so its PLACEMENT is load-bearing: it must be
 *     inside the innermost if-body, at or above `s1 = 1` (swept 90 order x position combos;
 *     12 MATCH, all with the launder in the body and `H` (the 0xE store) before `off`).
 *     1 -> MATCH.
 *
 * Symbols: all 15 relocations spelled from the target .s.  TU-conformance checked:
 *   func_8012AD80(s32) :2610, func_8013C9C4(void*) :1308, func_8012B2CC(s32) :2528,
 *   D_801270C8 s32 :2741, D_80126B96 u16 :3142 — copied verbatim.  The TU has no prior
 *   declaration of func_80184828, so the void* signature is free (no DEF-side wall).
 *   Local typedefs are address-suffixed to avoid colliding with the TU's carried decl layer.
 */
#include "common.h"

typedef struct {
    s16 vx, vy, vz, pad;
} SVec_80184828;

struct S0E_80184828 { s16 v; };

extern void func_8012AD80(s32 a0);
extern s32 func_80187508();
extern u16 D_80126B96;
extern s16 D_80126B98;
extern u16 D_801E4BBC;
extern void *func_8018ABE0(s32 a0);
extern void func_8018AEB4(s32 a0, s32 a1);
extern u16 D_801E43B4;
extern s32 D_801270C8;
extern void func_801849E4(void *a0);
extern void func_8013C9C4(void *a0);
extern void (*D_80191060[])(void);
extern void func_8012B2CC(s32 a0);

extern D_80195AF6_t D_80195AF6[];

void func_80184828(void *a0)
{
    struct {
        SVec_80184828 v1;
        SVec_80184828 v2;
        u8 pad[8];
    } local;
    s32 s2;
    s32 off;
    s32 s1;

    local.v1.vx = *(u16 *)((u8 *)a0 + 0x3A);
    local.v1.vy = *(u16 *)((u8 *)a0 + 0x3E);
    local.v1.vz = *(u16 *)((u8 *)a0 + 0x42);
    func_8012AD80((s32)a0);
    local.v2.vx = *(u16 *)((u8 *)a0 + 0x6);
    local.v2.vy = *(u16 *)((u8 *)a0 + 0xA);
    local.v2.vz = *(u16 *)((u8 *)a0 + 0xE);

    if (*(s16 *)((u8 *)a0 + 0xA) < -0x800) {
        s2 = 0;
    } else {
        s2 = 1;
        *(s16 *)((u8 *)a0 + 0xA) = -0x800;
        *(s32 *)((u8 *)a0 + 0x14) = 0;
    }

    s1 = 0;
    if (*(s16 *)((u8 *)a0 + 0x100) < 0) {
        if (func_80187508(a0) != 0) {
            u16 *p96 = &D_80126B96;
            *p96 |= 0x4000;
            D_80126B98 = 10;
        }
    } else {
        if (D_801E4BBC == 1) {
            s16 newval = *(s16 *)((u8 *)func_8018ABE0(*(s16 *)((u8 *)a0 + 0x100)) + 0xE);
            if (newval >= *(s16 *)((u8 *)a0 + 0xE)) {
                ((struct S0E_80184828 *)((u8 *)a0 + 0xE))->v = newval;
                s1 = 1;
                func_8018AEB4(*(s16 *)((u8 *)a0 + 0x100), 0);
            }
        } else {
            D_80195AF6_t *p = D_80195AF6;
            s16 newval = D_80195AF6[*(s16 *)((u8 *)a0 + 0x100)].f0;

            if (newval >= *(s16 *)((u8 *)a0 + 0xE)) {
                __asm__("" : "=r"(p) : "0"(p));
                s1 = 1;
                ((struct S0E_80184828 *)((u8 *)a0 + 0xE))->v = newval;
                off = *(s16 *)((u8 *)a0 + 0x100) * 8;
                D_801270C8 = *(s16 *)((u8 *)p + off + 4);
                D_801E43B4 += 1;
            }
        }
    }

    if (s2 || s1) {
        func_801849E4(a0);
        func_8013C9C4(&(*(s32 *)D_80191060));
    }
    func_8012B2CC((s32)a0);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_801849E4);

extern void func_8012AD44(s32 *a0, s16 a1);

void func_80184A34(void *arg0) {
    *(u16 *)((s32)arg0 + 0xDC) = *(u16 *)((s32)arg0 + 0x6);
    *(u16 *)((s32)arg0 + 0xDE) = *(u16 *)((s32)arg0 + 0xA);
    *(u16 *)((s32)arg0 + 0xE0) = *(u16 *)((s32)arg0 + 0xE);
    func_8012AD44((s32 *)arg0, 5);
    *(u16 *)((s32)arg0 + 0x34) = 4;
    *(s32 *)((s32)arg0 + 0x1C) = 5;
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B200(u8 *a0);
extern s32 D_801963FC;

struct S34_80184A8C { u16 v; };

void func_80184A8C(void *a0) {
    s32 s0;
    s32 ret;
    s32 p64;

    ret = func_8012BEE8((s32)a0);
    s0 = (s32)a0;
    if (ret != 0) {
        u16 timer;

        p64 = *(s32 *)(s0 + 0x64);
        *(s32 *)(s0 + 0xC) = 0;
        *(s32 *)(s0 + 0x8) = 0;
        *(s32 *)(s0 + 0x4) = 0;
        func_80132784(s0, *(s32 *)(p64 + 0xCC), 6);

        timer = *(u16 *)(s0 + 0x34);
        if (timer != 0) {
            s32 ptr;
            s32 tmp[3];

            timer -= 1;
            ((struct S34_80184A8C *)(s0 + 0x34))->v = timer;
            __asm__ __volatile__("" ::: "memory");

            tmp[0] = (*(s16 *)(s0 + 0xDC) - *(s32 *)(*(s32 *)(s0 + 0x20) + 0x48)) >> 2;

            ptr = *(s32 *)(s0 + 0x20);
            tmp[1] = (*(s16 *)(s0 + 0xDE) - *(s32 *)(ptr + 0x4C)) >> 2;

            ptr = *(s32 *)(s0 + 0x20);
            tmp[2] = (*(s16 *)(s0 + 0xE0) - *(s32 *)(ptr + 0x50)) >> 2;

            timer = *(u16 *)(s0 + 0x34);
            ptr = *(s32 *)(s0 + 0x20);
            *(s32 *)(ptr + 0x48) = *(s32 *)(ptr + 0x48) + tmp[0] * timer;

            timer = *(u16 *)(s0 + 0x34);
            ptr = *(s32 *)(s0 + 0x20);
            *(s32 *)(ptr + 0x4C) = *(s32 *)(ptr + 0x4C) + tmp[1] * timer;

            timer = *(u16 *)(s0 + 0x34);
            ptr = *(s32 *)(s0 + 0x20);
            *(s32 *)(ptr + 0x50) = *(s32 *)(ptr + 0x50) + tmp[2] * timer;
        } else {
            s32 cbptr;

            cbptr = *(s32 *)(s0 + 0xCC);
            if (cbptr != 0) {
                *(u16 *)(cbptr + 0xFC) = 1;
                *(s32 *)(s0 + 0xCC) = 0;
            }
            *(s32 *)(s0 + 0x58) = (s32)&D_801963FC;
            *(u16 *)(s0 + 0x5C) = 0x8C00;
            func_8012AD44((s32 *)s0, 1);
            func_8012B200((u8 *)s0);
            *(s32 *)(s0 + 0xC) = 0;
            *(s32 *)(s0 + 0x8) = 0;
            *(s32 *)(s0 + 0x4) = 0;
        }
    } else {
        s32 flagptr;
        u16 flagval;

        flagptr = *(s32 *)(s0 + 0x20);
        flagval = *(u16 *)(flagptr + 0x2C);
        *(u16 *)(flagptr + 0x2C) = flagval | 1;
    }
}


extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B200(u8 *a0);
extern s32 D_801963FC;

void func_80184C20(s32 a0) {
    s32 s0;

    s0 = a0;
    a0 = *(s32 *)(s0 + 0xCC);
    if (a0 != 0) {
        *(u16 *)(a0 + 0xFC) = 1;
        *(s32 *)(s0 + 0xCC) = 0;
    }
    *(s32 *)(s0 + 0x58) = (s32)&D_801963FC;
    *(u16 *)(s0 + 0x5C) = 0x8C00;
    func_8012AD44((s32 *)s0, 1);
    func_8012B200((u8 *)s0);
    {
        s32 p64;

        p64 = *(s32 *)(s0 + 0x64);
        *(s32 *)(s0 + 0xC) = 0;
        *(s32 *)(s0 + 0x8) = 0;
        *(s32 *)(s0 + 0x4) = 0;
        func_80132784(s0, *(s32 *)(p64 + 0xCC), 6);
    }
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern u8 D_80196414[];

s32 func_80184CA4(void *arg0)
{
    s32 s0 = (s32)arg0;

    *(s16 *)(s0 + 6) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x48);
    *(s16 *)(s0 + 0xA) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x4C);
    *(s16 *)(s0 + 0xE) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x50);
    func_8012B23C(s0);
    *(s32 *)(s0 + 0x10) = 0x00040000;
    *(s32 *)(s0 + 0x14) = 0xFFF80000;
    *(s32 *)(s0 + 0x18) = 0xFFFC0000;
    *(s32 *)(s0 + 0x78) = (s32)&D_80196414;
    func_8012AD44((s32 *)s0, 6);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80184D24(void *arg0) {
        ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 0x7);
    }



extern void (*D_80196470[])(void);

void func_80184D44(void *a0) {
    D_80196470[*(u16 *)((s32)a0 + 0x2)]();
}



void func_80184D80(void *a0) {
        *(s8 *)((s32)a0 + 0xc1) = 0;
        *(s16 *)((s32)a0 + 0x5e) = 0;
        *(u16 *)((s32)a0 + 0x5c) &= 0xfffe;
    }


#include "common.h"

extern void func_8012B200(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80132DC4(s32 a0, s32 a1, s32 a2);

void func_80184D98(void *arg0) {
    s32 s0 = (s32)arg0;
    s16 t;
    struct {
        s16 x;
        s16 y;
        s16 z;
    } local;

    func_8012B200((u8 *)s0);
    local.x = *(u16 *)(*(s32 *)(s0 + 0x64) + 6) - 0x40;
    t = *(u16 *)(*(s32 *)(s0 + 0x64) + 0xA) - 0x80;
    *(u16 *)(s0 + 0x100) = t;
    local.y = t;
    local.z = *(u16 *)(*(s32 *)(s0 + 0x64) + 0xE);
    func_80132DC4(s0, (s32)&local, 0x500);
    *(u16 *)(s0 + 0x5C) &= ~1;
    *(u8 *)(s0 + 0xC1) = 4;
    *(u8 *)(s0 + 0xC2) = 0;
    func_8002D4C8(0x505, 0);
}


extern void func_8012CBF4(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_8012B200(u8 *a0);
extern void func_8018AF58(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u16 D_801E4398;
extern u8 D_8019103C;

void func_80184E30(s32 arg0) {
    s32 s0 = arg0;
    s16 t;
    s32 p64;

    func_8012CBF4(arg0);
    t = *(s16 *)(s0 + 0x100);
    if (t < *(s16 *)(s0 + 0xA)) {
        p64 = *(s32 *)(s0 + 0x64);
        *(s16 *)(s0 + 0xA) = t;
        D_801E4398 = 0;
        *(s16 *)(p64 + 0x34) = 4;
        *(s32 *)(p64 + 0x1C) = 0x30;
        *(u16 *)(p64 + 0x76) = 0;
        func_8013C9C4(&D_8019103C);
        func_8012B200((u8 *)s0);
        *(u8 *)(s0 + 0xC1) = 0;
        *(u16 *)(s0 + 0x5E) = 0;
        func_8018AF58(s0);
        func_8002D4C8(0x506, 0);
    }
}


#include "common.h"

extern void func_8012CAE4(void *a0);
extern void func_8012C1B8(void);
extern void func_8001C2C4(s32 a0);
extern s32 func_8012AD50(void *a0);

extern u16 D_80195B4C[];
extern u16 D_80195B68[];

typedef struct {
    u8 pad[0x34];
} D_80195D74_Entry;
extern D_80195D74_Entry D_80195D74[];

extern void (*D_80196490[])(void);

void func_80184EC0(void *a0)
{
    u16 f70;
    s16 idx;
    u16 *tbl;
    s32 flags;
    s32 c1b8;
    s32 f64;
    u16 traw;
    u16 tval;

    f70 = *(u16 *)((u8 *)a0 + 0x70);
    if (f70 >= 0x13) {
        func_8012CAE4(a0);
        return;
    }

    if ((s16)f70 >= 0xD) {
        tbl = D_80195B68;
        f70 -= 0xD;
    } else {
        tbl = D_80195B4C;
    }

    idx = *(s16 *)((u8 *)a0 + 0x70);
    if (func_8012C354((s32)a0, (s32)&D_80195D74[idx]) == 0) {
        return;
    }

    flags = *(s32 *)((u8 *)a0 + 0xC4);
    *(u8 *)((u8 *)a0 + 0xC0) = 1;
    *(s32 *)((u8 *)a0 + 0xBC) = (s32)D_80196490;
    *(s32 *)((u8 *)a0 + 0xC) = 0;
    *(s32 *)((u8 *)a0 + 0x8) = 0;
    *(s32 *)((u8 *)a0 + 0x4) = 0;
    *(s32 *)((u8 *)a0 + 0xB4) = 0;
    *(u8 *)((u8 *)a0 + 0xC1) = 0;
    *(u8 *)((u8 *)a0 + 0x75) = 8;
    *(s32 *)((u8 *)a0 + 0xDC) = 0;
    *(s16 *)((u8 *)a0 + 0x100) = 0;
    *(s32 *)((u8 *)a0 + 0xC4) = flags | 2;

    c1b8 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)a0 + 0x20) = c1b8;
    if (c1b8 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C2C4(c1b8);

    f64 = *(s32 *)((u8 *)a0 + 0x64);
    *(s32 *)((u8 *)a0 + 0xCC) = f64;

    traw = tbl[f70];
    tval = traw & 0xFFFF;

    if (tval >= 0x16) {
        s32 f64b = *(s32 *)((u8 *)a0 + 0x64);
        s32 inner;
        *(s16 *)((u8 *)a0 + 0xFC) = traw - 0x16;
        inner = *(s32 *)((u8 *)f64b + 0xCC);
        *(s16 *)((u8 *)a0 + 0xFE) = 1;
        *(s32 *)((u8 *)a0 + 0x64) = inner;
    } else {
        *(s16 *)((u8 *)a0 + 0xFC) = traw;
        *(s16 *)((u8 *)a0 + 0xFE) = 0;
        if (tval == 4 || tval == 9 || tval == 0xE || tval == 0x13) {
            *(s16 *)((u8 *)a0 + 0xFE) = 2;
        }
    }

    func_8012AD50(a0);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80185060);

extern void func_8012AD44(s32 *a0, s16 a1);

void func_801851E0(s32 a0)
{
    *(s32 *)(a0 + 0xDC) = 1;
    *(u8 *)(a0 + 0xC1) = 0;
    *(s16 *)(a0 + 0xAE) = -1;
    func_8012AD44((s32 *)a0, 2);
}


#include "common.h"

/* func_80185214 — ov_SC02_005 (jr_80181D30 TU), 110 ins, byte-exact.
 *
 * Second-pass crack.  Structure was already right in pass 1; the whole residual
 * (25 ins) was register-allocation + list-scheduling.  Four levers, in order of
 * how much each bought:
 *
 *  1. state pinned to $4, and the `state << 3` result pinned to $2 (`idx`).
 *     With ONLY the $4 pin, gcc reuses the dead hard reg for the shift result
 *     (`sll $a0,$a0,3`); the target wants a fresh `$v0`.  Pinning the shift
 *     destination is what forces `sll $v0,$a0,3` + `addu $at,$at,$v0`.
 *     (Dropping the $4 pin instead moves `state` to $a1 — worse.)
 *
 *  2. `lo`/`hi` temps around each subtraction, and — load-bearing — a SEPARATE
 *     pair (`lo2`/`hi2`) for the second block.  Reusing lo/hi merges the pseudo
 *     webs and flips the subu operands to `subu $v1,$a2,$v1` (+11 ins).  The
 *     `hi` (pointer-chased) load is written BEFORE the `lo` load in block 2 —
 *     that ordering is what yields `lh $v1,0xE($a0)` / `lh $a2,0xE($v0)`.
 *
 *  3. `p = self` placed between the two operand loads and the subtraction: the
 *     target materialises `addu $a0,$s0,$zero` only at its first use, so the
 *     0x14 store and the 0xCC/0x6 loads still address off $s0.
 *
 *  4. §17 scheduling barrier (`__asm__ __volatile__("")`) between the 0x10
 *     fixed-point block and its store.  Without it sched1 hoists block-2's
 *     `lhu 0x70` / `lh 0xE` up into the load-delay slots of block 1 and the
 *     whole tail drifts (20 ins wrong).  Zero bytes emitted.
 */

extern s32 D_801E4474[];
extern s32 D_801E4418[];
extern u8 D_801E4AA0[];
extern u8 D_801E4AA4[];
extern u8 D_80063548[];

extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8012B21C(void *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801853CC(s32 a0);

void func_80185214(s32 arg0) {
    register s32 self __asm__("$16");
    register s32 state __asm__("$4");
    register s32 idx __asm__("$2");
    s32 acc;
    s32 lo;
    s32 hi;
    s32 lo2;
    s32 hi2;
    void *tgt;

    self = arg0;
    state = *(s16 *)(self + 0x70);

    if (state < 12) {
        s32 p;

        if (*(s16 *)(self + 0xFE) == 1) {
            acc = D_801E4474[*(s16 *)(self + 0xFC)];
        } else {
            acc = D_801E4418[*(s16 *)(self + 0xFC)];
        }

        idx = state << 3;
        *(s32 *)(D_801E4AA0 + idx) = acc;
        *(s32 *)(D_801E4AA4 + (*(s16 *)(self + 0x70) << 3)) = 0;

        *(s32 *)(*(void **)(self + 0x20) + 0x24) =
            (s32)(D_801E4AA0 + (*(s16 *)(self + 0x70) << 3));

        *(s32 *)(*(void **)(self + 0x20) + 0x20) = (s32)D_80063548;

        func_80132784(self, *(s32 *)(self + 0x64), *(u16 *)(self + 0xFC));

        *(s16 *)(self + 0x6) = *(s32 *)(*(void **)(self + 0x20) + 0x48);
        *(s16 *)(self + 0xA) = *(s32 *)(*(void **)(self + 0x20) + 0x4C);
        *(s16 *)(self + 0xE) = *(s32 *)(*(void **)(self + 0x20) + 0x50);
        *(s16 *)(self + 0x102) = *(u16 *)(self + 0xA);

        func_8012B21C((void *)self);

        *(s32 *)(self + 0x14) = 0xFFE80000;

        lo = *(s16 *)(self + 0x6);
        hi = *(s16 *)(*(s32 *)(self + 0xCC) + 0x6);
        p = self;
        acc = lo - hi;
        acc = (acc << 12) + ((*(u16 *)(p + 0x70) & 7) << 16) + 0x40000;
        __asm__ __volatile__("");
        *(s32 *)(p + 0x10) = acc;

        tgt = *(void **)(p + 0xCC);
        hi2 = *(s16 *)((s32)tgt + 0xE);
        lo2 = *(s16 *)(p + 0xE);
        acc = lo2 - hi2;
        *(s16 *)(p + 0x100) = *(u16 *)(p + 0x70);
        acc = (acc << 12) - ((*(u16 *)(p + 0x70) & 7) << 16) + 0x20000;
        *(s32 *)(p + 0x18) = acc;

        func_8012AD44((s32 *)p, 3);
    } else {
        *(s32 *)(*(void **)(self + 0x20) + 4) |= 0x80000000;
        func_801853CC(self);
    }
}


void func_801853CC(s32 a0) {
    func_8012AD44((s32 *)a0, 4);
}


extern void func_80186A04(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void func_80185060(s32 a0, s32 a1);
extern void func_80186B08(s32 param_1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801853EC(s32 arg0) {
    register s32 s0 __asm__("$16");
    register s32 r76 __asm__("$2");
    register s32 r60 __asm__("$6");
    register s32 flags __asm__("$3");
    s32 cnt;

    s0 = arg0;
    r76 = *(u16 *)(s0 + 0x76);
    r60 = *(u16 *)(s0 + 0x60);
    cnt = r76 - r60;
    flags = *(u16 *)(s0 + 0x5C) & 0xFFFE;
    *(u16 *)(s0 + 0x76) = cnt;
    *(u16 *)(s0 + 0x5C) = flags;
    func_8016AA50(arg0, *(s16 *)(s0 + 0x60));

    if (*(s16 *)(s0 + 0x76) <= 0) {
        *(u16 *)(s0 + 0x5E) = 0;
        func_80185060(arg0, 1);
        func_80186B08(arg0);
    } else {
        *(u8 *)(s0 + 0xC1) = 1;
        *(s32 *)(s0 + 0x1C) = 8;
        func_80186A04(arg0);
    }

    if (*(u16 *)(s0 + 0x5E) != 0x1D) {
        func_8002D4C8(0x4F3, 0);
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_80186B08(s32 param_1);
extern void func_80186424(s32 arg0);
extern u16 D_801E43BC;

void func_8018548C(void *a0)
{
    u8 flags;

    if (func_8012BEE8((s32)a0) != 0) {
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(u16 *)((s32)a0 + 0x5E) = 0;
        func_80186B08((s32)a0);
    }

    func_80186424((s32)a0);

    flags = *(u8 *)((s32)a0 + 0x74);
    if (flags != 0) {
        if (*(u16 *)((s32)a0 + 0xFE) & 1) {
            D_801E43BC = D_801E43BC | flags;
        }
    }
}


#include "common.h"

extern void (*D_801964A8[])(void);
extern void func_80186424(s32 arg0);
extern void func_80132F40(s32 arg0);
extern void func_80186F60(s32 arg0);
extern void func_801865D0(void *arg0);
extern void func_80189E34(s32 arg0, s32 arg1);
extern void func_8018A0E4(s32 arg0);
extern u16 D_801E43BC;
extern u16 D_801E4BBC;
extern u16 D_800B99D8;

void func_8018550C(void *a0)
{
    s32 flags;
    u8 v1;

    D_801964A8[*(u16 *)((u8 *)a0 + 0x2)]();

    flags = *(s32 *)(*(s32 *)((u8 *)a0 + 0xCC) + 0xE8);

    if ((flags & 0x8000) == 0) {
        func_80186424((s32)a0);

        v1 = *(u8 *)((u8 *)a0 + 0x74);
        if (v1 != 0) {
            if (*(u16 *)((u8 *)a0 + 0xFE) & 0x1) {
                D_801E43BC = D_801E43BC | v1;
            }
        }

        if (*(s16 *)((u8 *)a0 + 0x70) == 0x11) {
            if (*(u16 *)((u8 *)a0 + 0x5C) & 0x400) {
                func_80132F40((s32)a0);
            }
        }

        if ((*(u16 *)((u8 *)a0 + 0xFE) & 0x2) && (flags & 0x20)) {
            func_80186F60((s32)a0);
        } else if ((*(u16 *)((u8 *)a0 + 0xFE) & 0x1) && (flags & 0x100)) {
            func_801865D0(a0);
        }

        if (flags & 0x10000) {
            if ((D_800B99D8 & 0x3) == 0) {
                if ((rand() & 0x1F) == (*(s16 *)((u8 *)a0 + 0x70) & 0x1F)) {
                    func_80189E34((s32)a0, D_801E4BBC);
                }
            }
        } else if (flags & 0x4000) {
            if ((D_800B99D8 % 60) == (*(s16 *)((u8 *)a0 + 0x70) * 2)) {
                func_8018A0E4((s32)a0);
            }
        }
    }
}


#include "common.h"



extern void func_801858C4();
extern void func_80185858();

extern Blk8 D_801E2E9C;
extern Blk8 D_801E2EA4;

void func_801856E4(void)
{
    Blk8 blk1;
    Blk8 blk2;

    blk1 = D_801E2E9C;
    blk2 = D_801E2EA4;

    ((void (*)(void))func_801858C4)();
    func_80185858(0x11, &blk1, &blk2);
}


#include "common.h"



extern void func_801858C4();
extern void func_80185858();

extern Blk8 D_801E2EAC;
extern Blk8 D_801E2EB4;
extern Blk8 D_801E2EBC;
extern Blk8 D_801E2EC4;

void func_80185764(void *a0)
{
    Blk8 blk1;
    Blk8 blk2;

    func_801858C4(a0);

    blk1 = D_801E2EAC;
    blk2 = D_801E2EB4;
    func_80185858(8, &blk1, &blk2);

    blk1 = D_801E2EBC;
    blk2 = D_801E2EC4;
    func_80185858(0xA, &blk1, &blk2);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80185858);

#include "common.h"

extern void func_8012C218(void *a0);
extern s32 D_801E43C0;
extern s32 D_801E43C4;

void func_801858C4(void) {
    s32 *ptr = &D_801E43C0;

    if (*ptr != 0) {
        func_8012C218((void *)*ptr);
        *ptr = 0;
    }
    if (D_801E43C4 != 0) {
        func_8012C218((void *)D_801E43C4);
        D_801E43C4 = 0;
    }
}


#include "common.h"

extern u16 D_801E4BBC;
extern u16 D_801E4398;
extern u16 D_801E439C;
extern s16 D_80195B24[];

extern void func_8017BFF0(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801900E0(void);
extern void func_8018AB84(void);

void func_8018592C(u8 *arg0) {
    s16 val;
    register u8 *a2 __asm__("$6");
    register u32 idx __asm__("$4");
    register s32 flags __asm__("$3");

    a2 = arg0;
    flags = *(s32 *)(a2 + 0xE8);
    idx = D_801E4BBC;
    *(s16 *)(a2 + 0x102) = 0;
    flags &= ~8;
    *(s32 *)(a2 + 0xE8) = flags;

    if (idx < 2) {
        D_801E4BBC++;
    }

    val = D_80195B24[D_801E4BBC];
    *(s16 *)(a2 + 0x76) = val;
    D_801E439C = val;
    D_801E4398 = val;

    func_8017BFF0((s32)&D_801E4398, (s32)&D_801E439C, 0x60);

    switch (D_801E4BBC) {
        case 1:
            func_8002D4C8(0x11, 0);
            func_801900E0();
            break;
        case 2:
            func_8018AB84();
            break;
    }
}


extern s32 func_80185A88();

void func_80185A04(s32 param_1, s32 param_2, s16 param_3) {
    s32 ret;

    if ((*(u32 *)(param_2 + 0xE8) & 4) == 0) {
        *(u32 *)(param_2 + 0xE8) |= 0x10;
        ret = func_80185A88(param_2, param_3);
        *(u16 *)(param_2 + 0x60) = *(u16 *)(param_2 + 0x60) + ret;
        func_8016AA50(param_1, (s16)ret);
        *(s16 *)(param_2 + 0xDE) = 8;
        func_801869E0((s32 *)param_2);
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80185A88);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80185B38);





extern s32 D_801270CC;

s32 func_80185D6C() {
    return ((MainStruct *)D_801270CC)->f_E8 & 4;
}


s32 func_80185D84(s32 arg0) {
    s32 var;

    var = *(s32 *)(arg0 + 0xCC);
    func_80185DD0(0, (u16 *)(*(s32 *)(var + 0x20) + 0x12), 0x100);
    return *(s16 *)(*(s32 *)(var + 0x20) + 0x12) == 0;
}


#include "common.h"

void func_80185DD0(s32 target, u16 *cur, s32 step)
{
    s32 t;
    s32 diff;
    s32 mag;

    t = (target - *cur) & 0xFFF;
    if (t < 0x800) {
        diff = t;
    } else {
        diff = t | 0xF000;
    }
    mag = diff;
    if ((s16)diff < 0) {
        mag = -diff;
    }
    __asm__ __volatile__("" : "=r"(diff) : "0"(diff) : "memory");
    if ((s16)mag > (u16)step) {
        if ((s16)diff < 0) {
            *cur = *cur - step;
        } else {
            *cur = *cur + step;
        }
    } else {
        *cur = target;
    }
}


#include "common.h"

extern u16 D_801E4BBC;
extern s32 D_801959E0[];

u16 func_80185E54(s32 arg0)
{
    u16 val;

    val = D_801E4BBC;
    *(s16 *)(arg0 + 0x102) = 0;
    val = *(u16 *)D_801959E0[val];
    *(u16 *)(arg0 + 0x100) = val;
    return val;
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80185E80);

extern s32 func_80132E6C(s16 *a0);
extern s16 D_80126CB8;

s32 func_801860F4(s16 *arg0) {
    s32 ret;
    s32 lim;
    s32 cmp;

    ret = func_80132E6C(arg0);
    lim = D_80126CB8;
    if (*(s16 *)((s32)arg0 + 0xE) < lim) {
        cmp = 0;
    } else {
        cmp = ret >= 0x6400;
    }
    return cmp;
}


typedef struct {
    s16 f0;
    s16 f1;
    s16 f2;
    s16 f3;
} TBL_80186144;

extern TBL_80186144 D_80195AF8[];

extern u16 D_801E43B4;

s32 func_80186144(void *a0, s32 a1)
{
    s16 idx = D_801E43B4;

    if (D_80195AF8[idx].f0 == a1)
        return idx;
    return -1;
}


#include "common.h"

/* §183 TYPE-adopted-TU.  The destination TU spells this symbol
 *     extern MainStruct *D_801E43A4;
 * (just above func_8018622C).  Both typedefs below are VERBATIM copies of the TU's
 * own definitions — §183.1 name/shape trap respected: same name => same body — so
 * gate_main's strip_dup_typedefs reuses the file's copy and drops these.
 * NOTE FOR THE BANKER: this only works once the TU's SubStruct/MainStruct block sits
 * ABOVE the func_80186178 INCLUDE_ASM stub (TU line 4347); see the immovable report. */




extern MainStruct *D_801E43A4;

void func_80186178(s32 *a0)
{
    register s32 *a1 asm ("$5") = a0;
    register s32 a2 asm ("$6") = 0x80000000;
    register s32 *a0_reg asm ("$4");
    s32 *v0;
    s32 *v1;
    s32 v2;

    // First: access at 0x20
    v1 = *(s32 **)((char *)a1 + 0x20);
    *(s32 *)((char *)v1 + 0x4) |= a2;

    // Second: access at 0xCC
    v0 = *(s32 **)((char *)a1 + 0xCC);
    v1 = *(s32 **)((char *)v0 + 0x20);
    *(s32 *)((char *)v1 + 0x4) |= a2;

    // Fourth (source-order moved up): global load. Placing this statement
    // here — between the 0xCC and 0xD0 blocks — lets gcc's scheduler thread
    // the two-instruction lui/lw address computation into the 0xD0 block's
    // load-delay slots instead of stalling on nops (T2: source order drives
    // scheduling for independent setup). Also frees $a0 (dead after the
    // a1=a0 copy) via an explicit register pin, matching the target's reuse
    // of $a0 for the global pointer.
    a0_reg = (s32 *)D_801E43A4;   /* §183 cast at the USE SITE, not on the decl */

    // Third: access at 0xD0
    v0 = *(s32 **)((char *)a1 + 0xD0);
    v1 = *(s32 **)((char *)v0 + 0x20);
    *(s32 *)((char *)v1 + 0x4) |= a2;

    // Fourth cont'd: from global (no 0x20 indirection, just 0xCC then 0x4)
    v1 = *(s32 **)((char *)a0_reg + 0xCC);
    *(s32 *)((char *)v1 + 0x4) |= a2;

    // Fifth: conditional at 0xD4
    v2 = *(s32 *)((char *)a1 + 0xE8);
    if ((v2 & 0x2) == 0) {
        v0 = *(s32 **)((char *)a1 + 0xD4);
        v1 = *(s32 **)((char *)v0 + 0x20);
        *(s32 *)((char *)v1 + 0x4) |= a2;
    }
}


#include "common.h"



extern MainStruct *D_801E43A4;

void func_8018622C(MainStruct *a0) {
    register MainStruct *a1 __asm__("$5");
    register SubStruct *v1 __asm__("$3");
    register s32 v0 __asm__("$2");
    s32 a2;

    a1 = a0;
    a2 = 0x7FFFFFFF;

    v1 = a1->f_20;
    v0 = v1->field_4;
    v0 &= a2;
    v1->field_4 = v0;

    v0 = (s32)a1->f_CC;
    v1 = ((MainStruct *)v0)->f_20;
    v0 = v1->field_4;
    v0 &= a2;
    v1->field_4 = v0;

    v0 = (s32)a1->f_D0;
    v1 = ((MainStruct *)v0)->f_20;
    v0 = v1->field_4;

    a0 = D_801E43A4;
    v0 &= a2;
    v1->field_4 = v0;

    v1 = (SubStruct *)a0->f_CC;
    v0 = v1->field_4;
    v0 &= a2;
    v1->field_4 = v0;

    v0 = a1->f_E8;
    if ((v0 & 0x2) == 0) {
        v0 = (s32)a1->f_D4;
        v1 = ((MainStruct *)v0)->f_20;
        v0 = v1->field_4;
        v0 &= a2;
        v1->field_4 = v0;
    }
}


void func_801862E0(s32 *a0) {
        s32 v0 = *(s32 *)((s32)a0 + 0xCC);
        *(s16 *)((s32)a0 + 0x98) = 0;
        *(s16 *)(v0 + 0x98) = 0;
    }


void func_801862F0(void * arg0) {
        *(short *)((char *)arg0 + 0x98) = 1;
        *(short *)(*(int *)((char *)arg0 + 0xcc) + 0x98) = 1;
    }


extern void *D_801959EC[];
extern void *D_801959F0[];
extern void func_80132EC4(void *a0, s16 a1);
extern void func_8012A860(void *a0, s32 a1);

void func_80186304(param_1, param_2, param_3)
void *param_1;
s32 param_2;
s16 param_3;
{
    void **s0;
    s32 sp4;
    register s32 base __asm__("$2");

    sp4 = 0;
    if (param_2 < 0) {
        param_2 = -param_2;
        sp4 = 1;
    }
    if (param_2 < 0x1A) {
        if (param_3 == 0) {
            param_3 = 2;
            if (*(u32 *)((u8 *)param_1 + 0xE8) & 0x2000) {
                param_3 = 1;
            }
        }
        base = (s32)&D_801959EC;
        s0 = (void **)(base + param_2 * 8);
        func_80132EC4(*s0, param_3);
        if (sp4 != 0) {
            func_8012A860(param_1, (s32)*s0);
        } else {
            func_8012A828((s32)param_1, *s0);
        }
        base = (s32)&D_801959F0;
        s0 = (void **)(base + param_2 * 8);
        func_80132EC4(*s0, param_3);
        if (sp4 != 0) {
            func_8012A860(*(void **)((u8 *)param_1 + 0xCC), (s32)*s0);
        } else {
            func_8012A828((s32)*(void **)((u8 *)param_1 + 0xCC), *s0);
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80186424);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018655C);

extern s32 func_8012D714(s32 param_1, u32 param_2);
    extern u16 D_80126B96;
    void func_801865D0(void *arg0) {
        if (func_8012D714((s32)arg0, 0x5)) {
            D_80126B96 = 0x4005;
        }
    }


#include "common.h"

extern s32 func_8012B864(s32 a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_80186F9C(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s16 D_801E43B8;

void func_80186600(s32 a0) {
    register s32 flags __asm__("$5");
    register s32 v0 __asm__("$2");
    s32 s1;

    flags = *(s32 *)(a0 + 0xE8);
    s1 = *(s32 *)(a0 + 0xCC);
    D_801E43B8 = 0;

    if (flags & 1) {
        if (flags & 0x200) {
            s16 fE6 = *(s16 *)(a0 + 0xE6);

            if (fE6 >= 0x55) {
                s16 fE4 = *(s16 *)(a0 + 0xE4);

                if (fE4 != 0) {
                    s32 p = *(s32 *)(s1 + 0x20);
                    u16 t;
                    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + 0x100;
                    t = *(u16 *)(a0 + 0xE4);
                    D_801E43B8 = 0x100;
                    *(s16 *)(a0 + 0xE4) = t - 1;
                } else {
                    v0 = flags & ~0x300;
                    *(s32 *)(a0 + 0xE8) = v0;
                    *(s16 *)(a0 + 0xE6) = 0;
                }
            } else {
                if (fE6 < 0x48) {
                    if ((fE6 & 7) == 0) {
                        func_80186F9C(a0, 0x16);
                        func_80186F9C(a0, 0x19);
                        func_8002D4C8(0x4F0, 0);
                    }
                } else if (fE6 == 0x54) {
                    v0 = flags | 0x100;
                    *(s32 *)(a0 + 0xE8) = v0;
                    func_8002D4C8(0x4EC, 0);
                }
                *(s16 *)(a0 + 0xE6) = *(u16 *)(a0 + 0xE6) + 1;
            }
        } else {
            s32 v0;
            s32 p1;
            s32 p2;
            s32 p3;
            s32 r;

            v0 = func_8012B864(a0);
            p1 = *(s32 *)(s1 + 0x20);
            p2 = *(s32 *)(a0 + 0x20);
            r = func_8012B608(*(s16 *)(p1 + 0x12) + *(s16 *)(p2 + 0x12), v0, 8);
            p3 = *(s32 *)(s1 + 0x20);
            {
                u16 t2 = *(u16 *)(p3 + 0x12);
                D_801E43B8 = r;
                *(u16 *)(p3 + 0x12) = t2 + r;
            }
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018675C);

extern u16 D_801E4BBC;
extern s32 D_80195AD0[];
extern s32 D_80195AD2[];

s32 func_8018687C(s32 a0)
{
    if (*(u32 *)(a0 + 0xE8) & 0x800) {
        return 0;
    }

    if (*(s32 *)(a0 + 0x10) > 0) {
        if (*(s16 *)(D_80195AD2 + D_801E4BBC) < *(s16 *)(a0 + 6)) {
            *(s16 *)(a0 + 6) = *(s16 *)(D_80195AD2 + D_801E4BBC);
            return 1;
        }
    }

    if (*(s32 *)(a0 + 0x10) >= 0) {
        return 0;
    }

    if (*(s16 *)(a0 + 6) >= *(s16 *)(D_80195AD0 + D_801E4BBC)) {
        return 0;
    }
    *(s16 *)(a0 + 6) = *(s16 *)(D_80195AD0 + D_801E4BBC);
    return 1;
}


#include "common.h"

extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

s32 func_8018692C(s32 arg0) {
    extern s32 D_801E43CC[];
    extern s32 D_801E4400[];

    s32 count = 0;
    s32 i = 0;
    s32 *p = D_801E43CC;

    for (; i < 13; i++, p++) {
        if ((*p = func_8012C658(0x49, i, arg0)) == 0) {
            count++;
        }
    }

    i = 0;
    p = D_801E4400;
    for (; i < 6; i++, p++) {
        if ((*p = func_8012C658(0x49, i + 13, arg0)) == 0) {
            count++;
        }
    }

    return count;
}


















extern s32 D_80196208;
void func_801869E0(s32 *param_1)
{
  s32 *new_var;
  new_var = (s32 *) (((char *) param_1) + 0x20);
  *((s32 *) ((*new_var) + 0x80)) = (s32) (&D_80196208);
  new_var = (s32 *) ((*((s32 *) ((*((s32 *) (((char *) param_1) + 0xcc))) + 0x20))) + 0x80);
  *new_var = *((s32 *) ((*((s32 *) (((char *) param_1) + 0xcc))) + 0x20));
  param_1++;
  param_1--;
  *((s32 *) ((*new_var) + 0x80)) = (s32) (&D_80196208);
}

#include "common.h"

extern s32 D_801E43A0;
extern u16 D_80195B4C[];
extern s32 D_801961B8;
extern s32 D_801961E0;

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 val;
} Entry_80186A04;

void func_80186A04(s32 arg0) {
    s16 idx;
    s32 flags;
    u32 key;
    Entry_80186A04 *t0;
    Entry_80186A04 *a2;
    Entry_80186A04 *p;
    s32 a1;
    s32 j;
    s16 v0;

    idx = *(s16 *)(arg0 + 0x70);
    if (idx >= 14) {
        return;
    }
    flags = D_801E43A0;
    if ((flags >> (idx + 1)) & 1) {
        return;
    }
    key = D_80195B4C[idx];
    if (key >= 0x16) {
        t0 = (Entry_80186A04 *)&D_801961E0;
        key -= 0x16;
    } else {
        t0 = (Entry_80186A04 *)&D_801961B8;
    }
    /* zero-byte allocno-priority ref-boost (cookbook regalloc "ref-boost", global.c:594):
     * lifts `key`'s n_refs 7 -> 8 across the floor_log2 step so it allocates before the
     * table base -> key=$a3 / base=$t0 as in the target. Emits no instruction. */
    __asm__("" :: "r"(key));
    for (a1 = 0; a1 < 4; a1++) {
        a2 = &t0[a1];
        v0 = a2->val;
        if (v0 != -1) {
            if (v0 == (s32)(key & 0xFFFF)) {
                return;
            }
            if (!((s32)(key & 0xFFFF) < v0)) {
                continue;
            }
            for (j = 3; a1 < j; j--) {
                p = &t0[j];
                p->val = p[-1].val;
            }
        }
        a2->val = key;
        return;
    }
}


extern s32 D_801961B8;
    extern s32 D_801961E0;
    void func_80186ADC(s32 arg0) {
        *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x80) = &D_801961B8;
        *(s32 *)(*(s32 *)(*(s32 *)(arg0 + 0xcc) + 0x20) + 0x80) = &D_801961E0;
    }


#include "common.h"

extern u16 D_80195B4C[];
extern s32 D_801961B8;
extern s32 D_801961E0;

void func_80186B08(s32 param_1)
{
    s16 idx;
    u16 val;
    u8 *base;
    int i;
    int j;

    idx = *(s16 *)(param_1 + 0x70);

    if (idx >= 14)
        return;

    val = D_80195B4C[idx];

    if (val >= 0x16) {
        base = (u8 *)&D_801961E0;
        val -= 0x16;
    } else {
        base = (u8 *)&D_801961B8;
    }

    val &= 0xFFFF;

    for (i = 0; i < 4; i++) {
        if (*(s16 *)(base + i * 8 + 6) == val) {
            for (j = i; j < 4; j++) {
                *(u16 *)(base + j * 8 + 6) = *(u16 *)(base + j * 8 + 14);
            }
            return;
        }
    }
}


void func_80186BB8(void) {
    typedef struct {
        u8 pad[0x5C];
        u16 f5C;
    } F5C_S;
    extern F5C_S *D_801E43CC[];
    extern s8 D_80195ABC[];
    s32 i;
    s32 c;

    i = 0;
    c = D_80195ABC[0];
    while (c >= 0) {
        *(s16 *)((s32)D_801E43CC[c] + 0xAE) = -1;
        i++;
        c = D_80195ABC[i];
    }
}


void func_80186C0C(void *a0) {
    typedef struct { u8 pad[0x5C]; u16 f5C; } F5C_S;
    extern F5C_S *D_801E43CC[];
    extern s8 D_80195ABC[];
    s32 i;
    s32 ent;
    s32 c;

    for (i = 0; (c = D_80195ABC[i]) >= 0; i++) {
        ent = (s32)D_801E43CC[c];
        if (*(s32 *)(ent + 0xDC) == 0) {
            *(u16 *)(ent + 0xAE) = 0;
        }
    }
}


typedef struct {
    u8 pad[0x5C];
    u16 f5C;
} F5C_S;

extern F5C_S *D_801E43CC[];

void func_80186C70(void *a0) {
    s32 i;
    for (i = 0; i < 0x13; i++) {
        D_801E43CC[i]->f5C &= ~0x400;
    }
}


extern F5C_S *D_801E43CC[];

void func_80186CA8(void *a0) {
    s32 i;
    s32 *p;

    i = 0;
    p = ((s32 *)D_801E43CC);
    while (i < 0x13) {
        s32 ent = *p;
        if (*(u16 *)(*(s32 *)(ent + 0x78) + 2) & 0x400) {
            *(u16 *)(ent + 0x5C) |= 0x400;
        }
        i++;
        p++;
    }
}


extern s32 D_801E43DC;
extern s32 D_801E43E0;
extern s32 D_801E43E4;
extern s32 D_801E43E8;

void func_80186D00(void) {
    *(u16 *)(D_801E43DC + 0x5C) &= ~0x800;
    *(u16 *)(D_801E43E0 + 0x5C) &= ~0x800;
    *(u16 *)(D_801E43E4 + 0x5C) &= ~0x800;
    *(u16 *)(D_801E43E8 + 0x5C) &= ~0x800;
}








extern s32 D_801E43DC;
extern s32 D_801E43E0;
extern s32 D_801E43E4;
extern s32 D_801E43E8;

void func_80186D74(void)
{
    *(u16 *)(D_801E43DC + 0x5C) |= 0x800;
    *(u16 *)(D_801E43E0 + 0x5C) |= 0x800;
    *(u16 *)(D_801E43E4 + 0x5C) |= 0x800;
    *(u16 *)(D_801E43E8 + 0x5C) |= 0x800;
}


#include "common.h"

extern s32 D_801E43A0;
extern void func_80186F9C(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186DE8(s32 a0) {
    register s32 v0 __asm__("$2");
    s16 state;
    s32 flags;
    s32 a2;

    state = *(s16 *)(a0 + 0xFC);
    if (state == 0) {
        return;
    }
    flags = *(s32 *)(a0 + 0xE8);
    state = state - 1;
    *(s16 *)(a0 + 0xFC) = state;
    if (flags & 0x40) {
        if (state != 0) {
            return;
        }
        v0 = flags & ~0x40;
        *(s32 *)(a0 + 0xE8) = v0;
        v0 = 8;
        *(s16 *)(a0 + 0xFC) = v0;
        return;
    }
    if (flags & 0x200) {
        *(s16 *)(a0 + 0xFC) = 0;
        return;
    }
    a2 = D_801E43A0;
    if ((a2 & 0x1540) == 0x1540) {
        *(s16 *)(a0 + 0xFC) = 0;
        return;
    }
    if (state != 0) {
        return;
    }
    v0 = flags | 0x40;
    *(s32 *)(a0 + 0xE8) = v0;
    v0 = 0xC;
    *(s16 *)(a0 + 0xFC) = v0;
    if ((a2 & 0x40) == 0) {
        func_80186F9C(a0, 5);
    }
    if ((D_801E43A0 & 0x100) == 0) {
        func_80186F9C(a0, 0xA);
    }
    if ((D_801E43A0 & 0x400) == 0) {
        func_80186F9C(a0, 0xF);
    }
    if ((D_801E43A0 & 0x1000) == 0) {
        func_80186F9C(a0, 0x14);
    }
    func_8002D4C8(0x4F0, 0);
}


extern s32 D_801E43A0;

void func_80186F14(void *a0)
{
    if (*(s16*)((s32)a0 + 0xFC) == 0 &&
        (D_801E43A0 & 0x1540) != 0x1540) {
        *(s16*)((s32)a0 + 0xFC) = 8;
        *(s32*)((s32)a0 + 0xE8) &= ~0x40;
    }
}


void func_80186F58(void *a0) {
        *(s16 *)((s32)a0 + 0xFC) = 0;
    }


void func_80186F60(s32 a0) {
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 func_8012D714();
    if (func_8012D714(a0, 1)) {
        D_80126B96 = 0x4002;
        D_80126B98 = 10;
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80186F9C);

extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80187070(s32 arg0) {
    s32 self = arg0;
    s32 v1;

    v1 = func_8012C658(0x56, 5, self);
    if (v1 != 0) {
        *(s32 *)(v1 + 0xCC) = *(s32 *)(self + 0xCC);
    }
}


#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018A7D8(u16 *a0, u16 *a1, s16 *a2, s32 a3);

/* D_80195B78 / D_80195B7A / D_80195B7C / D_80195B7E are each their own top-level data
 * symbol in asm/ov_SC02_005/data/tail.data.s (separate dlabel/enddlabel entries), but the
 * function indexes each with a 16-byte runtime stride (sll ...,4). Model each as an array
 * of a 16-byte-stride row so gcc emits the shift and keeps the relocation on the symbol
 * itself rather than folding an offset into a neighbour's %lo. */
typedef struct {
    s16 v;
    u8 pad[14];
} Row16_t;
extern Row16_t D_80195B78[];
extern Row16_t D_80195B7A[];
extern Row16_t D_80195B7C[];
extern Row16_t D_80195B7E[];

void func_801870BC(void *a0) {
    s32 v1;
    s32 v2;
    u16 a1arr[4];
    s16 a2arr[3];
    s16 idx;

    a1arr[0] = *(s32 *)((u8 *)*(void **)((u8 *)a0 + 0x20) + 0x48) + 0x10;

    v1 = *(s32 *)((u8 *)*(void **)((u8 *)a0 + 0x20) + 0x4C);
    a1arr[1] = v1;

    v2 = *(s32 *)((u8 *)*(void **)((u8 *)a0 + 0x20) + 0x50);
    a1arr[3] = 0x3000;
    a1arr[2] = v2 - 0x10;

    if (*(s16 *)((u8 *)a0 + 0x70) == 3) {
        a1arr[1] = v1 - 0x60;
        a1arr[2] = v2 - 0x20;
    }

    idx = *(s16 *)((u8 *)a0 + 0x70);
    a2arr[0] = (D_80195B7A[idx].v - D_80195B78[idx].v) >> 1;

    idx = *(s16 *)((u8 *)a0 + 0x70);
    a2arr[1] = (D_80195B7E[idx].v - D_80195B7C[idx].v) >> 1;
    a2arr[2] = 0x20;

    func_8018A7D8((u16 *)((u8 *)a0 + 0xE8), a1arr, a2arr, 0);

    if (*(s16 *)((u8 *)a0 + 0x104) != 0) {
        if ((*(u16 *)((u8 *)a0 + 0xE8) & 3) == 0) {
            func_8002D4C8(0x4F4, 0);
        }
    }
}


extern void GsMapModelingData(u32 *);
extern u32 D_801BD9D4[];
extern u8 D_801961BE[];
extern u8 D_801961E6[];

void func_801871E4(void)
{
    u32 *p;
    s32 v;
    s32 i;

    p = D_801BD9D4;
    if (*p != 0) {
        do {
            GsMapModelingData((u32 *)((*p & 0x80FFFFFF) + 4));
            p++;
        } while (*p != 0);
    }
    for (v = -1, i = 0; i < 0x20; i += 8) {
        *(s16 *)&D_801961BE[i] = v;
        *(s16 *)&D_801961E6[i] = v;
    }
}


extern s32 D_801E43A0;
extern s32 D_801E4418[];
extern s32 D_801E4474[];
extern u16 D_80195B4A[];
extern u32 D_801BD9D4[];
extern s32 D_80195CA4[];

void func_80187280(s32 arg0, s32 arg1) {
    u16 var;
    u16 i;
    s32 *p;

    var = arg1;
    if (var < 14) {
        if (var != 0) {
            i = D_80195B4A[var];
            p = D_801E4418;
            if (i >= 0x16) {
                p = D_801E4474;
                i = i - 0x16;
            }
            arg1--;
            if (i == 5) {
                p[5] = 0x1000000;
            } else {
                p[i] = D_801BD9D4[arg1 & 0xFFFF];
            }
            *(s32 *)(arg0 + 0x58) = ((((arg1 & 0xFFFF) << 4) + (u32)D_80195CA4)) | 0x40000000;
        }
        D_801E43A0 |= 1 << var;
    }
}


extern u16 D_80195B4A[];
extern s32 D_801B82F4;
extern s32 D_801BB8DC;
extern u8 D_80195B64;
extern s32 D_801E4418[];
extern s32 D_801E4474[];
extern s32 D_801E43A0;

void func_80187348(s32 a0, s32 a1) {
    u32 a2;
    u16 idx;
    s32 *tab;
    s32 *base;
    s32 flags;

    a2 = a1 & 0xFFFF;
    if (a2 < 14) {
        if (a2 != 0) {
            tab = D_801E4418;
            idx = D_80195B4A[a2];
            base = &D_801B82F4;
            if (idx >= 22) {
                tab = D_801E4474;
                base = &D_801BB8DC;
                idx = idx - 22;
            }
            tab[idx] = base[idx];
            *(s32 *)(a0 + 0x58) = ((a2 << 4) + (s32)&D_80195B64) | 0x40000000;
        }
        flags = D_801E43A0;
        *(s32 *)(a0 + 0xDC) = 0;
        D_801E43A0 = flags & ~(1 << a1);
    }
}


#include "common.h"

/* func_801873FC -- ov_SC02_005 / ov_SC02_005_jr_80181D30
 * Fresh crack (mass lane, no matched exemplar; skeleton-similar seed func_801818D8 in
 * ov_SC03_006 shares the paired-point/func_8012DEB8-collision-test shape but is unrolled,
 * not looped -- structure only, not source).
 *
 * entity->0x58 is a tagged pointer into a box-like struct (min/max x/y/z), recovered with the
 * project's standard masked-pointer idiom (cookbook: src/ov_SC06_029/..._jr_8017C954.c func_80182BC8,
 * src/ov_SC01_077/..._jr_8012ACE0.c func_8012D098) -- entity->0x58 & 0xFFFFFFF | 0x80000000, with
 * %lo(D_8000000N) being literal byte offsets N (4,6,8,0xA,0xC,0xE), NOT real linker symbols.
 * The box fields are read via BOTH lhu (plain copy into a u16 local field: box->min_x/min_z/max_z)
 * and lh (the max_x-min_x width calc, signed) -- same field, different access width per call site,
 * so raw *(u16*)/(s16*) pointer casts are used rather than one consistently-typed struct.
 *
 * Loop tests 3 x-samples (min_x, min_x+step, min_x+2*step where step=(max_x-min_x)>>1) against two
 * fixed z planes (min_z via p1, max_z via p2) at both y=min_y and y=max_y, via func_8012DEB8
 * (fleet-modal (s32,(s32,s32,s32)), no TU-local declaration found -- decl_prior fleet, n=1442).
 * Returns 1 on the first nonzero collision result, else 0.
 */

extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 w;
} Vec4h_801873FC;

s32 func_801873FC(s32 a0) {
    Vec4h_801873FC p1;
    Vec4h_801873FC p2;
    u8 *box;
    s32 step;
    s32 x;
    s32 i;

    box = (u8 *)((*(u32 *)(a0 + 0x58) & 0xFFFFFFF) | 0x80000000);

    p1.x = *(u16 *)(box + 4);
    p1.z = *(u16 *)(box + 0xC);
    p2.x = *(u16 *)(box + 4);
    p2.z = *(u16 *)(box + 0xE);
    step = (u32)(*(s16 *)(box + 6) - *(s16 *)(box + 4)) >> 1;

    for (i = 0; i < 3; i++) {
        p1.y = p2.y = *(u16 *)(box + 8);
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
            return 1;
        }

        p1.y = p2.y = *(u16 *)(box + 0xA);
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2)) {
            return 1;
        }

        x = p1.x + step;
        p1.x = x;
        p2.x = x;
    }

    return 0;
}


extern s32 D_801963FC;
extern s32 func_80187560();

s32 func_80187508(s32 param_1)
{
    s32 ret;

    if (func_80187560(param_1, (s32)&D_801963FC, -8) == 0) {
        ret = func_80187560(param_1, (s32)&D_801963FC, -0x28);
    } else {
        ret = 1;
    }
    return ret;
}


#include "common.h"

typedef struct {
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
    /* 0x4 */ u16 z;
    /* 0x6 */ u16 w;
} Vec4h_80187560;

extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);

s32 func_80187560(s32 a0, s32 a1, s32 a2) {
    Vec4h_80187560 p1;
    Vec4h_80187560 p2;
    s32 result;

    p1.x = *(u16 *)(a0 + 0x6) + *(u16 *)(a1 + 0x4);
    p2.x = *(u16 *)(a0 + 0x6) + *(u16 *)(a1 + 0x6);
    p1.y = p2.y = a2 + (*(u16 *)(a0 + 0xA) + *(u16 *)(a1 + 0xA));

    p1.z = p2.z = *(u16 *)(a0 + 0xE) - 0x30;
    if (func_8012DF34(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.z = p2.z = *(u16 *)(a0 + 0xE) - 0x10;
    if (func_8012DF34(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.z = p2.z = *(u16 *)(a0 + 0xE) + 0x10;
    if (func_8012DF34(a0, (s32)&p1, (s32)&p2)) {
        result = 1;
        goto save;
    }

    p1.z = p2.z = *(u16 *)(a0 + 0xE) + 0x30;
    result = func_8012DF34(a0, (s32)&p1, (s32)&p2) != 0;

save:
    return result;
}


extern void func_8018B16C(s32 a0, s32 a1, s32 a2);

typedef struct { char b[8]; } Blob8_80187664;

extern Blob8_80187664 D_801E2EF0;

void func_80187664(s32 arg0)
{
    Blob8_80187664 tmp;

    tmp = D_801E2EF0;
    func_8018B16C(arg0, 6, (s32)&tmp);
}


#include "common.h"

/* D_801E2EF8: 8-byte, alignment-1 blob -- copied with lwl/lwr + swl/swr
 * (gcc's emit_block_move for align < 4), same idiom as the banked twin
 * func_8018A47C's D_801E2F28. */
typedef struct { char b[8]; } Blob8_801876B0;

extern Blob8_801876B0 D_801E2EF8;
extern u8 D_801202A0[];
extern void func_8018B16C(s32 a0, s32 a1, s32 a2);

void func_801876B0(s32 arg0)
{
    Blob8_801876B0 tmp;
    u8 *p;
    s32 i;

    tmp = D_801E2EF8;

    if (arg0 == 0) {
        for (i = 0, p = D_801202A0; i < 0x60; i++, p += 0x10C) {
            if (*(u16 *)p == 0x49 && *(s16 *)(p + 0x70) == 3) {
                arg0 = (s32)p;
                *(s16 *)(p + 0x104) = 1;
            }
        }
    }

    if (arg0 != 0) {
        func_8018B16C(arg0, 8, (s32)&tmp);
    }
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_80186304();
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186F14(void *a0);
extern u8 D_80195B2C[];

void func_80187768(void *a0) {
    s32 s0 = (s32)a0;
    u32 temp;
    s32 v0_val;

    func_8012B23C(s0);

    *(u32*)(s0 + 0xE8) |= 1;
    func_80186304((u8*)s0, 0, 0);

    temp = *(u32*)(s0 + 0xE8);
    if (temp & 0x2000) {
        *(u32*)(s0 + 0x1C) = 0x10;
    } else {
        *(u32*)(s0 + 0x1C) = 0x20;
    }

    v0_val = (s32)D_80195B2C | 0x40000000;
    *(u32*)(s0 + 0x58) = v0_val;
    *(s16*)(s0 + 0x5C) = 0;
    *(s16*)(s0 + 0xAE) = -1;

    func_8012AD44((s32*)s0, 1);
    func_80186F14((void*)s0);
}


extern void func_80182998(void);
extern void func_8018655C(s32 a0);
extern void func_801838A8(u8* a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012CE2C(s32 a0);
extern s32 func_8012CBCC(s32 a0);

void func_801877FC(s32 s0) {
    if (func_8012CE2C(s0) == 0) {
        ((void (*)(s32))func_8012CBCC)(s0);
    }

    if (*(u32 *)(s0 + 0xE8) & 0x60000) {
        ((void (*)(s32))func_80182998)(s0);
        return;
    }

    ((void (*)(s32))func_8018655C)(s0);

    if (*(s16 *)(s0 + 0x100) > 0) {
        *(s16 *)(s0 + 0x100) = *(s16 *)(s0 + 0x100) - 1;
    }

    if (((s32 (*)(s32))func_8012BEE8)(s0) != 0) {
        ((void (*)(u8 *))func_801838A8)((u8 *)s0);
    }

    if ((*(s32 *)(s0 + 0x94) == 4) || (*(s32 *)(s0 + 0x94) == 0xC)) {
        if (*(s16 *)(s0 + 0x98) == 1) {
            func_8002D4C8(0x4F7, 0);
        }
    }
}


void func_801878C0(void *arg0) {
    s32 s0 = (s32)arg0;

    func_80182810((void *)s0);
    if (*(u32 *)(s0 + 0xE8) & 0x2000) {
        *(u32 *)(s0 + 0x1C) = 0x18;
    } else {
        *(u32 *)(s0 + 0x1C) = 0x30;
    }
    func_801828D8((void *)s0);
    *(u32 *)(s0 + 0xE8) = *(u32 *)(s0 + 0xE8) & 0xFFFFFF7F;
}

extern void func_80182810();
extern void func_801828D8();


void func_8018791C(void *a0) {
    s32 s0 = (s32)a0;

    if (*(u32 *)(s0 + 0xE8) & 0x60000) {
        func_80182998();
        return;
    }

    func_80182918(s0);

    if (!(*(u32 *)(s0 + 0xE8) & 0x1000)) {
        if (*(s16 *)(s0 + 0x100) > 0) {
            *(s16 *)(s0 + 0x100) = *(s16 *)(s0 + 0x100) - 1;
        }
    }

    if (func_8018687C((void *)s0) || func_8018675C((void *)s0) || func_8012BEE8(s0)) {
        *(u32 *)(s0 + 0xE8) = *(u32 *)(s0 + 0xE8) & ~0x1000;
        func_801838A8((u8 *)s0);
    }
}


extern void func_80181900(void *a0);
    void func_801879DC(void *a0) {
        *(s32 *)((s32)a0 + 0xE8) |= 1;
        *(s16 *)((s32)a0 + 0xE0) = -1;
        ((void (*)(void *))func_80181900)(a0);
    }


extern void func_80181900(void*);
    void func_80187A0C(s32 *a0) {
        *(s32 *)((s32)a0 + 0xE8) &= ~1;
        ((void (*)(void))func_80181900)();
    }


extern void func_80186F58();
extern void func_80186304();
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80187A38(void *arg0) {
    *(u32 *)((s32)arg0 + 0xE8) |= 1;
    func_80186F58(arg0);
    func_80186304((u8 *)arg0, 0xE, 2);
    func_8012AD44((s32 *)arg0, 4);
}


#include "common.h"

extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80186F58(void *a0);

void func_80187A8C(void *arg0) {
    *(u32 *)((s32)arg0 + 0xE8) &= ~1;
    func_8012AD44((s32 *)arg0, 5);
    func_80186F58(arg0);
}


extern void func_8017DF00(void);
extern void func_80181F04(void *arg0);

void func_80187AD0(s32 arg0) {
    s32 temp_s0 = arg0;
    ((void (*)(void))func_80181F04)();
    *(s16 *)(temp_s0 + 0xDC) = 2;
    *(s16 *)(temp_s0 + 0xE0) = -1;
    ((void (*)(void))func_8017DF00)();
}


extern void func_80181F04(void *arg0);
extern void func_8017DF00(void);

void func_80187B0C(s32 arg0) {
    s32 temp_s0 = arg0;
    ((void (*)(void))func_80181F04)();
    *(s16 *)(temp_s0 + 0xDC) = 3;
    *(s16 *)(temp_s0 + 0xE0) = -1;
    ((void (*)(void))func_8017DF00)();
}


extern void func_80181F04(void *arg0);
extern void func_8017DF28(void);

void func_80187B48(s32 arg0) {
    s32 temp_s0 = arg0;
    ((void (*)(void))func_80181F04)();
    *(s16 *)(temp_s0 + 0xDC) = 1;
    ((void (*)(void))func_8017DF28)();
}


extern s32 func_80185D84(s32 a0);
extern s32 func_80181F70();
void func_80187B7C(int param_1)
{
    if (((int (*)(void))func_80185D84)() != 0) {
        ((void (*)(int))func_80181F70)(param_1);
    }
}


extern void func_80181FA8();
    void func_80187BB4(s32 arg0) {
        if (*(s16 *)((char *)arg0 + 0x98) == 0) {
            ((void (*)(void))func_80181FA8)();
        }
    }


extern void func_80181FE8();
    void func_80187BE4(s32 *a0) {
        if (*(s32 *)((char *)a0 + 0x94) == 0xB) {
            ((void (*)(void))func_80181FE8)();
        }
    }


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018A174(s32 a0);
extern void func_8018203C(s32 a0);

void func_80187C14(s32 a0) {
    s32 temp;

    func_8012AD80(a0);
    if (func_8012BEE8(a0) == 0) {
        temp = *(s32 *)(a0 + 0x1C);
        if (temp % 3 == 1) {
            func_8018A174(a0);
        }
    }
    if (*(s16 *)(a0 + 0xA) < -0xB00) {
        func_8018203C(a0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_80182098(void *a0);
void func_80187C9C(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_80182098)(param_1);
    }
}


extern s32 func_8012CBCC(s32 a0);
extern s32 func_801820E4(void *a0);
void func_80187CD4(int param_1)
{
    if (((int (*)(void))func_8012CBCC)() != 0) {
        ((void (*)(int))func_801820E4)(param_1);
    }
}


extern void func_801821C8(s32 *a0);
void func_80187D0C(s32 *a0) {
    *(s32 *)((char *)a0 + 0xE8) &= ~0x20;
    if (*(s32 *)((char *)a0 + 0x94) == 6) {
        func_801821C8(a0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_80182284(s32 arg0);
extern void func_8018415C(void *a0);

void func_80187D4C(s32 param_1) {
    if (func_8012BEE8(param_1) != 0) {
        func_80182284(param_1);
        func_8018415C(*(void **)(param_1 + 0xD4));
    }
}




void func_80187D90(void *a0) {

    extern void (*D_80196250[])(void);
    D_80196250[*(u16 *)((s32)a0 + 0x34)]();
}


extern void func_80182998(void);
extern void func_801838A8(u8*);

void func_80187DCC(u8 *arg0) {
    if (*(u32 *)(arg0 + 0xE8) & 0x60000) {
        func_80182998();
        return;
    }

    if (!(*(u32 *)(arg0 + 0xE8) & 0x200)) {
        func_801838A8(arg0);
    }
}


#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern u16 D_801E4BBC;

extern s32 func_80184CA4();
extern void func_801856E4(void);

void func_80187E18(u8 *arg0) {
    if (*(u16 *)(arg0 + 0x34) == 0) {
        if (D_801E4BBC == 2) {
            if (*(s32 *)(arg0 + 0x94) == 0xC) {
                if (*(s16 *)(arg0 + 0x98) == 1) {
                    func_80184CA4(*(s32 *)(arg0 + 0xD0));
                    *(u16 *)(arg0 + 0x5C) |= 0x200;
                }
            }
        } else {
            if (*(s32 *)(arg0 + 0x94) == 0xA) {
                if (*(s16 *)(arg0 + 0x98) == 1) {
                    func_8002D4C8(0xA2F, 0);
                }
            }
        }
        if (*(s16 *)(arg0 + 0x98) == 0) {
            (*(u16 *)(arg0 + 0x34))++;
            *(s32 *)(arg0 + 0x1C) = 0;
            *(s32 *)(arg0 + 0xE8) |= 0x10000;
        }
    } else {
        if (func_8012BEE8((s32)arg0) != 0) {
            func_801856E4();
            *(s32 *)(arg0 + 0x1C) = 0x180;
        }
    }
}



extern void func_8012CBF4(s32 a0);
    extern void func_80182E04();
    void func_80187F1C(void *a0) {
        if ((((s32 (*)(s32))func_8012CBF4)((s32)a0) & 0x2000) != 0) {
            ((void (*)(s32))func_80182E04)((s32)a0);
        }
    }



extern s32 D_801270C8;
extern void func_80182EB0(void);

void func_80187F58(void) {
    if (D_801270C8 == 22) {
        func_80182EB0();
    }
}


void func_80187F88(void) {
}



extern void func_8012CBF4(s32 a0);
    extern void func_80182EB0(void);
    void func_80187F90(void *a0) {
        if ((((s32 (*)(s32))func_8012CBF4)((s32)a0) & 0x2000) != 0) {
            ((void (*)(s32))func_80182EB0)((s32)a0);
        }
    }


extern s32 D_801270C8;
extern void func_80182E78(void *a0);
extern void func_80182DCC(void *a0);

void func_80187FCC(void *a0)
{
    s32 *p = &D_801270C8;

    if (*p == 22) {
        func_80182E78(a0);
    }
    if (*p == 20) {
        func_80182DCC(a0);
    }
}




void func_8018802C(void *a0) {

    extern void (*D_80196274[])(void);
    D_80196274[*(u16 *)((s32)a0 + 0x34)]();
}


extern void func_8012AD80(s32 a0);
extern void func_80182FAC();
extern s32 D_801270C8;

void func_80188068(void *a0) {
    func_8012AD80((s32)a0);
    if (D_801270C8 == 0x1F) {
        func_80182FAC((s32)a0);
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_801880AC);

extern s32 func_801830F4(s32 arg0, s32 a1);

void func_8018810C(void *a0) {
    func_801830F4((s32)a0, 1);
    if (func_8012BEE8((s32)a0) != 0) {
        func_80183060(a0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern u16 D_801E4398;

void func_80188150(void *a0) {
    s32 s0 = (s32)a0;

    func_8012BEE8(s0);
    if (*(s32 *)(s0 + 0x1C) == 1) {
        *(u16 *)(s0 + 0x76) = 0x1E;
        D_801E4398 = 0x1E;
    }
}


extern s32 func_801830F4(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80183074(s32 *a0);

void func_80188194(s32 a0) {
    ((void (*)(s32 *, s32))func_801830F4)((s32 *) a0, 0);
    if ((*(u32 *) ((char *) a0 + 0x1C) & 3) == 0) {
        func_8002D4C8(0x504, 0);
    }
    if (func_8012BEE8(a0) != 0) {
        func_80183074((s32 *) a0);
    }
}


#include "common.h"





extern void func_80186178(s32 *a0);
extern void func_8012C218(void *a0);
extern s32 func_801830F4(s32, s32);
extern s32 func_8012BEE8(s32 a0);
extern void func_80183160(void *a0);
extern void func_80019064(void *a0);
extern MainStruct *D_801E43A4;
extern s32 D_80062BC0;

void func_801881F4(s32 a0) {
    s32 s0 = a0;

    if (*(s32 *)(s0 + 0x1C) == 0x68) {
        *(s32 *)(s0 + 0xE8) |= 0x8000;
        func_80186178((s32 *)s0);
        if (D_801E43A4 != 0) {
            func_8012C218((void *)D_801E43A4);
        }
    }

    ((void (*)(void *, s32))func_801830F4)((void *)s0, 0);

    if (func_8012BEE8(s0) != 0) {
        func_80183160((void *)s0);
    } else if ((*(s32 *)(s0 + 0x1C) & 7) == 0) {
        func_80019064(&D_80062BC0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_80183174(void *a0);
void func_801882A8(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_80183174)(param_1);
    }
}


void func_801882E0(void) {
}



void func_801882E8(void *a0) {

    extern void (*D_801962A0[])(void);
    D_801962A0[*(u16 *)((s32)a0 + 0x34)]();
}


#include "common.h"

extern void (*D_80196184[])(void);
extern s32 D_801961E0;
extern s32 D_801E4490;
extern s32 D_801E448C;

void func_80188324(s32 a0) {
    s32 v0, v1;
    s32 ret;

    ret = func_8012C354(a0, (s32)D_80196184);
    if (!ret)
        return;

    *(u8 *)(a0 + 0xC1) = 0;
    func_8012AD44((s32 *)a0, 1);

    func_8012B200(a0);

    /* Structure updates */
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x28) = (0xE0 << 16) | 0xE0;

    v0 = *(s32 *)(a0 + 0x20);
    v1 = *(u16 *)(v0 + 0x2C);
    *(u16 *)(v0 + 0x2C) = v1 | 0x80;

    v0 = *(s32 *)(a0 + 0x20);
    *(s32 *)(v0 + 0x80) = (s32)&D_801961E0;

    *(u8 *)(a0 + 0x75) = 8;
    D_801E4490 = 0x1000000;
    D_801E448C = 0x1000000;
}


extern s32 *D_80126B78;
extern s16 D_801E43B8;
extern u16 D_801E43BC;

void func_801883C4(void)
{
    s32 p;
    s32 t;

    if (*(s16 *)&D_801E43BC != 0) {
        p = (s32)D_80126B78;
        t = *(u16 *)(p + 0x12) + *(u16 *)&D_801E43B8;
        *(u16 *)&D_801E43BC = 0;
        *(u16 *)(p + 0x12) = t;
    }
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_80183D54(s32 a0);
extern void func_80132288(s32 *a0, s32 *a1, s32 a2);
extern s32 D_80196348;
extern s32 D_8019637C;
extern s32 D_801963B8;
extern s32 D_801E44E0;
extern s32 *D_801D6D94;

void func_80188404(void *a0)
{
    if (func_8012C354((s32)a0, (s32)&D_80196348) == 0) {
        func_8012CAE4(a0);
        return;
    }
    *(s32 *)((s32)a0 + 0xC) = 0;
    *(s32 *)((s32)a0 + 0x8) = 0;
    *(s32 *)((s32)a0 + 0x4) = 0;
    func_80132784((s32)a0, *(s32 *)((s32)a0 + 0x64), 0);
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x28) = 0xE000E0;
    *(u8 *)((s32)a0 + 0xC0) = 1;
    *(s32 *)((s32)a0 + 0xBC) = (s32)&D_8019637C;
    *(s32 *)((s32)a0 + 0xB4) = 0;
    *(u8 *)((s32)a0 + 0x75) = 8;
    *(s32 *)((s32)a0 + 0xC4) |= 2;
    func_80183D54((s32)a0);
    func_80132288(&D_801E44E0, &D_801963B8, (*(s32 *)&D_801D6D94));
}


#include "common.h"

extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8013240C(s32 a0, s32 a1, u32 a2);
extern s32 D_801E44E0;

void func_801884C8(s32 a0) {
    ((void (*)(s32))func_8013240C)((s32)&D_801E44E0);
    func_80132784(a0, *(s32 *)(a0 + 0x64), 0);
}


#include "common.h"

extern void func_8013240C(s32 a0, s32 a1, u32 a2);
extern void func_80183FCC();
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern s32 D_801E44E0;
extern u32 D_801E44EC;
extern void (*D_80196338[])(void);

void func_8018850C(s32 *s0) {
    s32 *v1;

    v1 = (s32 *)*(s32 *)((u8 *)s0 + 0x20);
    *(u16 *)((u8 *)v1 + 0x2C) |= 1;
    ((void (*)(s32))func_8013240C)((s32)&D_801E44E0);

    if (D_801E44EC & 0x4000) {
        v1 = (s32 *)*(s32 *)((u8 *)s0 + 0x64);
        *(u32 *)((u8 *)v1 + 0xE8) |= 2;
        func_80183FCC((s32)s0);
        *(u8 *)((u8 *)s0 + 0xC1) = 0;
        *(u16 *)((u8 *)s0 + 0x5E) = 0;
        func_8012AD44(s0, 2);
        *(s32 *)((u8 *)s0 + 0x58) = (s32)&D_80196338 | 0x40000000;
        func_80132784((s32)s0, *(s32 *)((u8 *)s0 + 0x64), 0x15);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80184480(s32 a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern u8 D_801BB8F4[];
extern u8 D_8019640C[];
extern u8 D_80196448[];

void func_801885BC(void *a0) {
    s32 v0;
    register void *s0 __asm__("$16");
    s0 = a0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)s0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        *(u32 *)D_8019640C = *(u32 *)D_801BB8F4;
        func_8001C214(*(s32 *)((u8 *)s0 + 0x20), (s32)D_8019640C);
        *(s32 *)(*(s32 *)((u8 *)s0 + 0x20) + 0x28) = 0xE000E0;
        func_80184480((s32)s0);
        *(u8 *)((u8 *)s0 + 0xC0) = 1;
        *(s32 *)((u8 *)s0 + 0xB4) = 4;
        *(s32 *)((u8 *)s0 + 0xBC) = (s32)D_80196448;
        *(s16 *)((u8 *)s0 + 0xAE) = -1;
        *(u8 *)((u8 *)s0 + 0x75) = 8;
        *(u32 *)((u8 *)s0 + 0xC4) |= 2;
        *(u8 *)((u8 *)s0 + 0xC1) = 0;
        *(s32 *)((u8 *)s0 + 0xC) = 0;
        *(s32 *)((u8 *)s0 + 8) = 0;
        *(s32 *)((u8 *)s0 + 4) = 0;
        func_80132784((s32)s0, *(s32 *)(*(s32 *)((u8 *)s0 + 0x64) + 0xCC), 6);
    }
}


extern void func_80132784(s32 a0, s32 a1, u32 a2);

void func_80188690(void *a0) {
    func_80132784((s32)a0, *(s32 *)(*(s32 *)((u8 *)a0 + 0x64) + 0xCC), 6);
}


void func_801886BC(void) {
}

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_801886C4);

extern s32 D_801270C8;

void func_80188720(void *a0) {
    if (D_801270C8 == 31) {
        *(u16 *)((s32)a0 + 0x5C) |= 0x200;
    }
}


#include "common.h"

extern s32 D_801E43A0;
extern void func_80185060(s32 a0, s32 a1);

void func_8018874C(s32 arg0) {
    s16 idx;
    s32 flags;
    s32 st;

    idx = *(s16 *)(arg0 + 0x70);
    if (idx < 13) {
        flags = D_801E43A0;
        if (((flags >> (idx + 1)) & 1) != 0) {
            func_80185060(arg0, 0);
        }
    }
    st = *(s32 *)(*(s32 *)(arg0 + 0xCC) + 0xE8);
    if (st & 0x8000) {
        func_80185214(arg0);
    }
}


void func_801887CC(s32 arg0) {
    register s32 self __asm__("$16");
    s16 var;

    self = arg0;
    var = *(s16 *)(self + 0x100);
    if (var != 0) {
        *(s16 *)(self + 0x100) = var - 1;
        func_801870BC(arg0);
    }

    if (*(s32 *)(*(s32 *)(self + 0xCC) + 0xE8) & 0x8000) {
        func_80185214(self);
    }
}


#include "common.h"

extern void func_80189F84(s32 arg0);
extern void func_8012AD80(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_801853CC(s32 a0);

void func_80188830(s32 a0) {
    s16 v0;
    void *v1;
    u16 hw;

    if (*(s16 *)((u8 *)a0 + 0x70) < 12) {
        v1 = *(void **)((u8 *)a0 + 0x20);
        *(u16 *)((u8 *)v1 + 0x14) += 0x300;

        v1 = *(void **)((u8 *)a0 + 0x20);
        *(u16 *)((u8 *)v1 + 0x10) += 0x100;

        hw = *(u16 *)((u8 *)a0 + 0x100);
        hw++;
        *(u16 *)((u8 *)a0 + 0x100) = hw;

        if ((hw & 3) == 0) {
            func_80189F84(a0);
        }

        func_8012AD80(a0);

        if (*(s16 *)((u8 *)a0 + 0xA) >= *(s16 *)((u8 *)a0 + 0x102)) {
            func_8012B200((u8 *)a0);
            func_801853CC(a0);
        }
    }
}


#include "common.h"

extern void func_8018A0E4(s32 arg0);
extern u16 D_800B99D8;

void func_801888EC(void *a0)
{
    if (*(s16 *)((u8 *)a0 + 0x70) < 12 && (D_800B99D8 & 0xF) == (*(s16 *)((u8 *)a0 + 0x70) & 0xF)) {
        func_8018A0E4((s32)a0);
    }
}


extern void func_80181900(void*);
    void func_8018893C(s32 arg0) {
        *(s32 *)(arg0 + 0xe8) &= ~1;
        ((void (*)(void))func_80181900)();
    }


extern void func_8012B23C(s32 a0);
extern void func_801822B4(s32 a0);

void func_80188968(s32 arg0)
{
    if (*(s16 *)(arg0 + 0x98) == 0)
    {
        func_8012B23C(arg0);
        if ((*(s16 *)(arg0 + 0xE0) < 0) && (*(s16 *)(arg0 + 0xDC) != 0))
        {
            *(u16 *)(arg0 + 0x34) = 0;
            return;
        }
        func_801822B4(arg0);
    }
}



extern void (*D_801964BC[])(void);

void func_801889D4(void *a0) {
    D_801964BC[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80143994(s32 a0, s32 a1);

void *func_80188A10(void *a0) {
    void *r;
    void *v1;

    r = (void *)((s32 (*)(s32, s32))func_80143994)((s32)a0, 0x7FFF);
    if (r != 0) {
        v1 = *(void **)((u8 *)r + 0xCC);
        *(u16 *)((u8 *)r + 0) = 0x69;
        if (v1 != 0) {
            *(u8 *)((u8 *)v1 + 0x26) = 0xC8;
            *(u8 *)((u8 *)v1 + 0x25) = 0xC8;
            *(u8 *)((u8 *)v1 + 0x24) = 0xC8;
        }
    }
    return r;
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80188A5C(void *arg0) {
        ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 1);
    }


#include "common.h"

extern s32 func_8012D714(s32 param_1, u32 param_2);
extern u16 D_80126B96;
extern s16 D_80126B98;
extern s32 func_8012CBCC(s32 a0);
extern void func_8018A658(s32 a0);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s16 D_80126CB8;
extern void func_8018AC10(s32 a0);

extern u8 D_8019103C;

void func_80188A7C(void *a0)
{
    if (func_8012D714((s32)a0, 2) != 0) {
        u16 *p96 = &D_80126B96;
        D_80126B98 = 10;
        *p96 |= 0x4000;
    }

    if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) < 0x400) {
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) =
            *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) + 0x100;
    }
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) + 0x40;

    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        if (func_8012CBCC((s32)a0) != 0) {
            func_8018A658((s32)a0);
            func_8013C9C4(&D_8019103C);
            *(s32 *)((s32)a0 + 0x48) = 0;
            *(s32 *)((s32)a0 + 0x10) = 0;
            *(s32 *)((s32)a0 + 0x14) = 0;
            *(s32 *)((s32)a0 + 0x18) = (s32)0xFFD80000;
            *(u16 *)((s32)a0 + 0x34) = *(u16 *)((s32)a0 + 0x34) + 1;
            func_8002D4C8(0x4FC, 0);
        }
        break;
    case 1:
        func_8012AD80((s32)a0);
        if ((*(s16 *)((s32)a0 + 0xE) - D_80126CB8) < -0x180) {
            func_8018AC10((s32)a0);
        }
        break;
    }
}



extern void (*D_801964FC[])(void);

void func_80188BB4(void *a0) {
    D_801964FC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8012AD50(void *a0);
extern s32 func_80143970(s32 a0);

extern u8 D_80196544;
extern u8 D_80196578;
extern s32 D_80196514[];
extern s32 D_80196518[];
extern s16 D_80196534[];
extern s16 D_80196536[];

void func_80188BF0(void *a0)
{
    /* Target frame is 0x28 (vars=16) vs this body's natural 0x18 (vars=0) -- a 16-byte
     * orphan-slot gap (cookbook §162i1/§172) with no $sp reference to the excess in the
     * target .s. No candidate source expression accounts for it, so this is a dead pad
     * in declaration position, not a real local. */
    s32 pad[4];
    s32 idx;
    s32 v0;

    if (func_8012C354((s32)a0, (s32)&D_80196544) == 0) {
        return;
    }

    if (*(s16 *)((u8 *)a0 + 0x70) != 0) {
        *(s16 *)((u8 *)a0 + 0x5C) = 0;
    } else {
        s32 flags = *(s32 *)((u8 *)a0 + 0xC4);
        *(u8 *)((u8 *)a0 + 0xC0) = 1;
        *(s32 *)((u8 *)a0 + 0xBC) = (s32)&D_80196578;
        *(s32 *)((u8 *)a0 + 0xB4) = 0;
        *(u8 *)((u8 *)a0 + 0xC1) = 0;
        *(s16 *)((u8 *)a0 + 0xAE) = -1;
        *(u8 *)((u8 *)a0 + 0x75) = 0;
        *(s32 *)((u8 *)a0 + 0xC4) = flags | 2;
    }

    *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x28) = 0xE000E0;
    func_8012B23C((s32)a0);

    *(s32 *)((u8 *)a0 + 0x14) = 0xFFEC0000;

    idx = (*(u16 *)(*(s32 *)((u8 *)a0 + 0x64) + 0x100) & 1)
        + ((*(u16 *)((u8 *)a0 + 0x70) & 1) << 1);

    *(s32 *)((u8 *)a0 + 0x10) = D_80196514[idx * 2];
    *(s32 *)((u8 *)a0 + 0x18) = D_80196518[idx * 2];
    *(s16 *)((u8 *)a0 + 0xFC) = D_80196534[idx * 2];
    *(s16 *)((u8 *)a0 + 0xFE) = D_80196536[idx * 2];

    v0 = func_80143970((s32)a0);
    *(s32 *)((u8 *)a0 + 0xCC) = v0;
    *(s16 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x12) = -0x200;
    func_8012AD50(a0);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80188D1C);

extern void func_80188F38(void);
    void func_80188F08(u8 *a0) {
        *(s8 *)(a0 + 0xC1) = 0;
        *(s8 *)(a0 + 0xC2) = 0;
        *(u16 *)(a0 + 0x5C) &= 0xFFFE;
        func_80188F38();
    }


#include "common.h"



extern Blk20 D_800AE620;
extern s32 *D_80126B78;
extern s32 D_801965A0;
extern void func_8012B21C(void *a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80188F38(void)
{
    register s32 a0 __asm__("$4");
    s32 self;
    Blk20 m;
    s32 p;

    self = a0;
    m = D_800AE620;
    *(u16 *)(self + 0x5C) = 0;
    func_8012B21C((void *)self);

    p = (s32)D_80126B78;
    RotMatrixY(*(s16 *)(p + 0x12), &m);
    func_800484EC((s32)&m, (s32)&D_801965A0, self + 0x10);
    func_8012AD44((s32 *)self, 3);
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_801892CC(s32 a0);
extern void func_8018A47C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012BE54(s32 a0);       /* canonical void -> cast at use */
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012C218(void *a0);

void func_80188FF0(s32 a0) {
    s32 v0;

    func_8012AD80(a0);
    v0 = func_801892CC(a0);

    if (*(s16 *)(a0 + 0x100) == 0 && v0 != 0) {
        *(s16 *)(a0 + 0x102) = 2;
        *(u16 *)(a0 + 0x100) += 1;
    } else if (*(s16 *)(a0 + 0x102) != 0) {
        if (--*(s16 *)(a0 + 0x102) == 0) {
            *(s32 *)(a0 + 0x1C) = 0x18;
            *(s16 *)(a0 + 0x34) = 3;
            *(s16 *)(a0 + 0x100) = -1;
            *(s32 *)(a0 + 0x10) = -(*(s32 *)(a0 + 0x10) >> 1);
            *(s32 *)(a0 + 0x18) = -(*(s32 *)(a0 + 0x18) >> 1);
            *(s32 *)(a0 + 0x14) += -0x80000;
        }
    }

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (*(s16 *)(a0 + 0xA) >= -0x7FF) {
            func_8018A47C(a0);
            *(s32 *)(a0 + 0x14) = -0x80000;
            *(u16 *)(a0 + 0x34) += 1;
            func_8002D4C8(0xA2E, 0);
        }
        break;
    case 1:
        if (*(s16 *)(a0 + 0xA) >= -0x7FF) {
            *(s32 *)(a0 + 0x48) = 0;
            *(u16 *)(a0 + 0x34) += 1;
        }
        break;
    case 2:
        if (((s32 (*)(s32))func_8012BE54)(a0) > 0x100000) {
            func_8012C218((void *)a0);
        }
        break;
    case 3:
        if (*(s16 *)(a0 + 0xA) >= -0x7FF) {
            func_8012B200((u8 *)a0);
        }
        if (*(s32 *)(a0 + 0x1C) & 1) {
            *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
        } else {
            *(s32 *)(*(s32 *)(a0 + 0x20) + 4) &= 0x7FFFFFFF;
        }
        if (func_8012BEE8(a0) != 0) {
            func_8012C218((void *)a0);
        }
        break;
    }
}



extern void (*D_801965B0[])(void);

void func_80189204(void *a0) {
    D_801965B0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 *D_80126B78;

void func_80189240(s32 a0)
{
    *(u16 *)(a0 + 0x5C) &= 0xFFFE;
    *(u16 *)(a0 + 0x104) = *(u16 *)((s32)D_80126B78 + 0x12);
}


extern s32 *D_80126B78;

void func_80189268(s32 a0)
{
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = 0;
    if (*(u16 *)(*(s32 *)(a0 + 0x64) + 0x100) & 1) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
            *(u16 *)(a0 + 0x104) + *(u16 *)((s32)D_80126B78 + 0x12);
    } else {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
            *(u16 *)(a0 + 0x104) - *(u16 *)((s32)D_80126B78 + 0x12);
    }
}


/* func_801892CC (ov_SC02_005 / ov_SC02_005_jr_80181D30.c, 127 ins) — MATCH.
 *
 * Fresh crack (mass lane). Sweep of the 0x60-entry / stride-0x10C D_801202A0
 * entity table: for every entry whose type word (+0x00) is 0x49, ray-test the
 * two transformed segments (o0->o1 at height D_801964F4, o2->o3 at height
 * D_801964F6) against it; on a hit, latch state 0x1D + the hit point.
 *
 * Three levers were load-bearing (all byte-verified):
 *  1. §176 giv-base: write EVERY entry access as an offset off the SINGLE
 *     pointer `p` (p+0x20 .. p+0xAE, including p+0x80). A source-level second
 *     pointer `q = p + 0x80` makes `*(s16*)q` a DIRECT use of q, which drops
 *     0x80 out of the giv candidate set — combine_givs then bases the giv at
 *     0x7E and keeps q alive as a 3rd induction pointer (129 ins, 69 off).
 *     With 0x80 in the set, gcc picks 0x80 as the representative on its own.
 *  2. The paired-store spelling `v0.a = v1.a = 0; v0.c = v1.c = 0; v0.b = 0;`
 *     reproduces the target's 0x18/0x10/0x1C/0x14/0x12 sh order exactly; three
 *     plain per-struct statements give source order and 5 mismatches.
 *  3. §S1 sched2 LUID: `count = 0; p = D_801202A0;` must sit AFTER the first
 *     func_8012F214 call — the block's leading run is emitted in ascending
 *     LUID (a0,a1,a2,count,lui,addiu,i), so any earlier position puts
 *     `move count,zero` in the bgez delay slot (4 off).
 *     ⚠ A `register s32 count __asm__("$21")` pin ALSO reaches the right
 *     allocation, but a hard-reg pseudo cannot be scheduled across the `jal`,
 *     so it re-pins count to the block head and freezes the residual at 4.
 *     Dropping the pin lets natural allocation land count in $s5 anyway.
 */
#include "common.h"

extern u8 D_801202A0[];
extern u16 D_801964F4;
extern u16 D_801964F6;
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
extern void func_8002D4C8(s32 a0, s32 a1);

typedef struct { s16 a, b, c, d; } SV892CC;

s32 func_801892CC(s32 arg0)
{
    SV892CC v0;
    SV892CC v1;
    SV892CC o0;
    SV892CC o1;
    SV892CC o2;
    SV892CC o3;
    u8 *p;
    u16 *hit;
    s32 i;
    s32 count;

    if (*(s16 *)(arg0 + 0x100) < 0) {
        return 0;
    }

    v0.a = v1.a = 0;
    v0.c = v1.c = 0;
    v0.b = 0;
    v1.b = D_801964F4;
    func_8012F214(arg0, (s32)&v0, (s32)&o0);
    count = 0;
    p = D_801202A0;

    func_8012F214(arg0, (s32)&v1, (s32)&o1);
    v1.b = D_801964F6;
    func_8012F214(arg0, (s32)&v0, (s32)&o2);
    func_8012F214(arg0, (s32)&v1, (s32)&o3);

    for (i = 0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p != 0x49) {
            continue;
        }
        hit = func_80135260(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58), (s16 *)&o0, (s16 *)&o1)
                  ? (u16 *)&o1
                  : (u16 *)0;
        if (func_80135260(*(s32 *)(p + 0x20), *(s32 *)(p + 0x58), (s16 *)&o2, (s16 *)&o3)) {
            hit = (u16 *)&o3;
        }
        if (hit == (u16 *)0) {
            continue;
        }
        if (*(s16 *)(p + 0xAE) == 0 && *(u16 *)(p + 0x5E) != 0x1D) {
            u16 f = *(u16 *)(p + 0x5C);
            if ((f & 0xC000) == 0x8000) {
                *(s16 *)(p + 0x5C) = f | 1;
                *(s16 *)(p + 0x60) = 8;
                *(s16 *)(p + 0x62) = 0;
                *(s16 *)(p + 0x5E) = 0x1D;
                *(s16 *)(p + 0x7C) = hit[0];
                *(s16 *)(p + 0x7E) = hit[1];
                *(s16 *)(p + 0x80) = hit[2];
            }
        }
        count++;
    }
    if (count != 0) {
        func_8002D4C8(0xA2D, 0);
    }
    return count;
}



extern void (*D_801965C0[])(void);

void func_801894C8(void *a0) {
    D_801965C0[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80132784(s32 a0, s32 a1, u32 a2);

void func_80189504(void *a0) {
    func_80132784((s32)a0, *(s32 *)((u8 *)a0 + 0xCC), *(u16 *)((u8 *)a0 + 0x70));

    *(s32 *)((u8 *)a0 + 0xDC) =
        (*(s32 *)(*(s32 *)(*(s32 *)((u8 *)a0 + 0x64) + 0x20) + 0x48) -
         *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x48)) >> 4;
    *(s32 *)((u8 *)a0 + 0xE0) =
        (*(s32 *)(*(s32 *)(*(s32 *)((u8 *)a0 + 0x64) + 0x20) + 0x4C) -
         *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x4C)) >> 4;
    *(s32 *)((u8 *)a0 + 0xE4) =
        (*(s32 *)(*(s32 *)(*(s32 *)((u8 *)a0 + 0x64) + 0x20) + 0x50) -
         *(s32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x50)) >> 4;
}



extern void (*D_801965D4[])(void);

void func_801895A4(void *a0) {
    D_801965D4[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801895E0(void *a0) {
    s32 *p;
    s32 n;
    s32 arr[3];

    p = *(s32 **)((s32)a0 + 0x2C);
    n = *(s16 *)((s32)a0 + 0x30) + 1;
    arr[0] = *(s32 *)((s32)p + 0xDC);
    arr[1] = *(s32 *)((s32)p + 0xE0);
    arr[2] = *(s32 *)((s32)p + 0xE4);

    *(s16 *)((s32)a0 + 0x06) =
        arr[0] * n + *(s32 *)(*(s32 *)((s32)p + 0x20) + 0x48) - (arr[0] >> 1);
    *(s16 *)((s32)a0 + 0x0A) =
        arr[1] * n + *(s32 *)(*(s32 *)((s32)p + 0x20) + 0x4C) - (arr[1] >> 1);
    *(s16 *)((s32)a0 + 0x0E) =
        arr[2] * n + *(s32 *)(*(s32 *)((s32)p + 0x20) + 0x50) - (arr[2] >> 1);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018968C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_801898F4);


extern void (*D_8019660C[])(void);

void func_80189AF4(void *a0) {
    D_8019660C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80189B30);


extern void (*D_801966A0[])(void);

void func_80189C90(void *a0) {
    D_801966A0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801966B8[])(void);

void func_80189CCC(void *a0) {
    D_801966B8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80196760[])(void);

void func_80189D08(void *a0) {
    D_80196760[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801967C4[])(void);

void func_80189D44(void *a0) {
    D_801967C4[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801967CC[])(void);

void func_80189D80(void *a0) {
    D_801967CC[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80196814[])(void);

void func_80189DBC(void *a0) {
    D_80196814[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80196868[])(void);

void func_80189DF8(void *a0) {
    D_80196868[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern u8 *func_8012913C(s32 a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern u16 D_800B99DC;

void func_80189E34(s32 arg0, s32 arg1)
{
    register u8 *s2 __asm__("$18") = (u8 *)arg0;
    register u8 *s1 __asm__("$17");
    s32 raw;
    s32 s0;
    s16 v[4];
    u16 out[4];
    s32 obj;
    s16 flagval;

    raw = *(s32 *)(s2 + 0x58);
    s0 = 0;
    if (raw != 0) {
        s0 = (raw & 0xFFFFFFF) | 0x80000000;
    }

    s1 = func_8012913C(0x18);
    if (s1 != NULL && s0 != 0) {
        v[0] = 0;
        v[1] = *(u16 *)((u8 *)s0 + 8);
        v[2] = 0;

        func_8004914C((void *)(*(s32 *)(s2 + 0x20) + 0x34));
        func_800491AC((void *)(*(s32 *)(s2 + 0x20) + 0x34));

        RotTransSV(v, v, out);

        obj = *(s32 *)(s1 + 0x20);
        *(s16 *)(s1 + 6) = v[0];
        *(s16 *)(s1 + 0xA) = v[1];
        *(s16 *)(s1 + 0xE) = v[2];
        *(u16 *)(obj + 0x2C) = 0xC020;

        if (D_800B99DC & 1) {
            flagval = -0x2000;
            obj = *(s32 *)(s1 + 0x20);
            *(s16 *)(obj + 0x1C) = flagval;
        } else {
            obj = *(s32 *)(s1 + 0x20);
            flagval = 0x2000;
            *(s16 *)(obj + 0x1C) = flagval;
        }
        *(s16 *)(obj + 0x1A) = flagval;
        *(s16 *)(obj + 0x18) = flagval;
    }
}


extern s32 func_80132EF4(s32 a0, s32 a1);
    void func_80189F44(s32 arg0) {
        ((void (*)(s32, s32))func_80132EF4)(arg0, 0x16);
    }


extern u8 *func_8012913C(s32 a0);
    void func_80189F64(void) {
        ((void (*)(s32))func_8012913C)(0x15);
    }


extern s32 func_80132EF4(s32 a0, s32 a1);
    void func_80189F84(s32 arg0) {
        ((void (*)(s32, s32))func_80132EF4)(arg0, 0xC);
    }


extern s32 func_80132EF4(s32 a0, s32 a1);
    void func_80189FA4(void *a0) {
        ((void (*)(void *, int))func_80132EF4)(a0, 0x13);
    }


#include "common.h"

extern u8 *func_8012913C(s32 a0);
extern void func_80129350(s32 a0, s32 a1);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

typedef struct { s32 w[4]; } Blk16_801E2F08;

extern Blk16_801E2F08 D_801E2F08;
extern Blk20 D_800AE620;

void func_80189FC4(s32 a0) {
    Blk20 localMat;
    Blk16_801E2F08 blk16;
    s32 i;
    u8 *s0;

    blk16 = D_801E2F08;

    for (i = 0; i < 8; i++) {
        s0 = func_8012913C(0xC);
        if (s0 != NULL) {
            func_80129350((s32)s0, a0);
            *(s16 *)(s0 + 0x34) = -1;
            *(u16 *)(s0 + 0x6) -= 0x40;
            *(u16 *)(s0 + 0xA) -= 0x40;
            localMat = D_800AE620;
            RotMatrixY(i << 9, &localMat);
            func_800484EC((s32)&localMat, (s32)&blk16, (s32)(s0 + 0x10));
        }
    }
}


extern u8 *func_8012913C(s32 a0);

void func_8018A0E4(s32 arg0)
{
    u8 *ptr;
    s32 val;

    ptr = func_8012913C(0xC);
    if (ptr != NULL) {
        *(u16 *)(ptr + 0x6) = *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x48) + 0x50;
        *(u16 *)(ptr + 0xA) = *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x4C) - 0x40;
        val = *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x50);
        *(u32 *)(ptr + 0x14) = 0xFFF00000;
        *(u32 *)(ptr + 0x18) = 0;
        *(u32 *)(ptr + 0x10) = 0;
        *(s16 *)(ptr + 0x34) = -0x5000;
        *(u16 *)(ptr + 0xE) = val;
    }
}


void func_8018A174(s32 arg0) {
    u8 *ptr;
    s32 i;
    s16 val;

    i = 0;
    val = 0x4000;
    do {
        ptr = func_8018A30C(arg0, i);
        if (ptr != NULL) {
            *(s16 *) (ptr + 0x34) = val;
        }
        i++;
    } while (i < 4);
}


#include "common.h"

/* File-local mirror types: match_one compiles standalone with -Iinclude
 * only, so the TU's real Blk20 (src/shared/engine_types.h) is not
 * reachable here. These mirror the exact byte layout (same pattern as
 * the already-banked func_8018AF58/func_8018A4C4 in this TU).
 * DECL RECONCILIATION (§183 TYPE-adopted-TU, wave Z): the Blk20 typedef is
 * spelled with the AMBIENT name and the exact engine_types.h body, because
 * this TU already declares `extern Blk20 D_800AE620;` at file scope above
 * the splice point (lines 3664/5193/5527) and any private struct name there
 * is a hard `conflicting types` error — block-scoping it errors too (tested
 * against the pinned cc1).  canon_sig_reconcile strips a draft typedef whose
 * name AND body match engine_types.h, so the duplicate definition disappears
 * at bank time and the ambient Blk20 is used. */
typedef struct { s32 w[4]; } Blk16_8018A1D8;


extern Blk16_8018A1D8 D_801E2F18;
extern Blk20 D_800AE620;

extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern u8 *func_8018A30C(s32 a0, s32 a1);

void func_8018A1D8(s32 a0)
{
    Blk16_8018A1D8 fixedVec;
    s32 outVec[3];
    Blk20 localMatrix;
    s32 i, j;
    u8 *p;

    fixedVec = D_801E2F18;

    for (i = 0; i < 8; i++) {
        localMatrix = D_800AE620;
        RotMatrixY(i << 9, &localMatrix);
        func_800484EC((s32)&localMatrix, (s32)&fixedVec, (s32)outVec);

        for (j = 0; j < 4; j++) {
            p = func_8018A30C(a0, j);
            if (p != NULL) {
                *(s32 *)(p + 0x10) = outVec[0];
                *(s32 *)(p + 0x14) = outVec[1];
                *(s32 *)(p + 0x18) = outVec[2];
            }
        }
    }
}


#include "common.h"

extern u8 *func_8012913C(s32 a0);
extern void func_80129350(s32 a0, s32 a1);

u8 * func_8018A30C(s32 a0, s32 a1) {
    u8 *s0;

    s0 = func_8012913C(0xC);
    if (s0 != NULL) {
        func_80129350((s32)s0, a0);
        if (a1 & 1) {
            *(u16 *)(s0 + 0x6) += 0x68;
        } else {
            *(u16 *)(s0 + 0x6) -= 0x68;
        }
        if (a1 & 2) {
            *(u16 *)(s0 + 0xE) += 0x68;
        } else {
            *(u16 *)(s0 + 0xE) -= 0x68;
        }
    }
    return s0;
}


extern s32 func_80132EF4(s32 a0, s32 a1);

void func_8018A3B4(void *a0) {
    u8 *v1;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            v1 = (u8 *)func_80132EF4((s32)a0, 0xC);
            if (v1 != NULL) {
                *(u16 *)(v1 + 6) = (i != 0) ? *(u16 *)(v1 + 6) + 0x68 : *(u16 *)(v1 + 6) - 0x68;
                *(u16 *)(v1 + 0xE) = (j != 0) ? *(u16 *)(v1 + 0xE) + 0x82 : *(u16 *)(v1 + 0xE) - 0x1A;
                *(u16 *)(v1 + 0xA) -= 0x10;
            }
        }
    }
}


#include "common.h"

/* 8-byte, alignment-1 blob: the target copies it with lwl/lwr + swl/swr,
 * which is gcc's emit_block_move for align < 4. */

extern Blob8_8018A47C D_801E2F28;
extern void func_8018A6A0();

void func_8018A47C(s32 a0) {
    Blob8_8018A47C tmp;

    tmp = D_801E2F28;
    func_8018A6A0(a0, &tmp);
}


#include "common.h"

/* Local idiom types (match_one compiles standalone with -Iinclude only, so
 * types normally sourced from src/shared/engine_types.h are kept file-local
 * here, mirroring the already-banked func_8018AF58 in this TU). */

/* D_801E2F30: 8-byte, alignment-1 blob -- copied with lwl/lwr + swl/swr
 * (gcc's emit_block_move for align < 4). Holds 3 x u16 (+ pad). */
typedef struct { char b[8]; } Blob8_8018A4C4;

/* D_801E2F38: 16-byte, word-aligned blob -- copied with plain lw/sw. */
typedef struct { s32 w[4]; } Blk16_8018A4C4;

/* (*(Blk20_8018A4C4 *)&D_800AE620): 32-byte MATRIX-shaped blob (9 x s16 rot + pad + 3 x s32 trans),
 * copied with plain lw/sw -- same shape as the TU's existing Blk20. */
typedef struct { s32 w[8]; } Blk20_8018A4C4;

extern Blob8_8018A4C4 D_801E2F30;
extern Blk16_8018A4C4 D_801E2F38;
extern Blk20 D_800AE620;

extern u8 *func_8012913C(s32 a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018A4C4(s32 a0)
{
    Blk20_8018A4C4 localMat;
    s32 pad[4];
    Blob8_8018A4C4 blobA;
    Blk16_8018A4C4 blobB;
    s32 i;
    u8 *s0;

    blobA = D_801E2F30;
    blobB = D_801E2F38;

    /* gte_SetTransMatrix(&((SomeObj *)a0->0x20)->mat34) -- ctc2 into the GTE
     * translation-vector control regs (5,6,7) from a MATRIX's t[0..2], which
     * live at offset 0x34+0x14/0x18/0x1c inside the object pointed to by
     * a0's field 0x20. Written as raw asm: the target's .s marks these ctc2
     * lines "handwritten instruction" (not a normal codegen mnemonic). */
    __asm__ __volatile__(
        "lw $12, 20(%0)\n"
        "lw $13, 24(%0)\n"
        "ctc2 $12, $5\n"
        "lw $14, 28(%0)\n"
        "ctc2 $13, $6\n"
        "ctc2 $14, $7\n"
        :
        : "r"((u8 *)*(s32 *)(a0 + 0x20) + 0x34)
        : "$12", "$13", "$14", "memory"
    );

    for (i = 0; i < 8; i++) {
        s0 = func_8012913C(0xC);
        if (s0 != NULL) {
            *(u16 *)(s0 + 0x6) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48) + *(u16 *)&blobA.b[0];
            *(u16 *)(s0 + 0xA) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C) + *(u16 *)&blobA.b[2];
            *(u16 *)(s0 + 0xE) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50) + *(u16 *)&blobA.b[4];

            localMat = (*(Blk20_8018A4C4 *)&D_800AE620);
            RotMatrixY(i << 9, &localMat);
            func_800484EC((s32)&localMat, (s32)&blobB, (s32)(s0 + 0x10));
        }
    }
}



/* 8-byte, alignment-1 blob: the target copies it with lwl/lwr + swl/swr,
 * which is gcc's emit_block_move for align < 4. */

extern void func_8018A6A0();

void func_8018A658(s32 a0) {

    extern Blob8_8018A47C D_801E2F48;
    Blob8_8018A47C tmp;

    tmp = D_801E2F48;
    func_8018A6A0(a0, &tmp);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018A6A0);

void func_8018A7D0(void) {
}

#include "common.h"

extern u8 *func_8012913C(s32 a0);

void func_8018A7D8(u16 *a0, u16 *a1, s16 *a2, s32 a3) {
    u8 *s0;
    s16 mask;
    s32 pad[2];

    mask = (1 << a3) - 1;
    if ((*a0 & mask) == 0) {
        s0 = func_8012913C(0xD);
        if (s0 != 0) {
            *(s16 *)(s0 + 0x6) = a1[0] + rand() % (a2[0] * 2) - a2[0];
            *(s16 *)(s0 + 0xA) = a1[1] + rand() % (a2[1] * 2) - a2[1];
            {
                s32 r = rand();
                s32 t = a2[2];
                s32 base = a1[2];
                *(s32 *)(s0 + 0x18) = 0;
                *(s32 *)(s0 + 0x14) = 0;
                *(s32 *)(s0 + 0x10) = 0;
                *(s16 *)(s0 + 0xE) = base + r % (t * 2) - t;
            }
            *(s16 *)(s0 + 0x34) = a1[3];
        }
    }
    *a0 = *a0 + 1;
}


#include "common.h"

extern s32 func_8012C51C(void *a0, s32 a1);
extern s16 D_80195AC6[];
extern u16 D_80195AD6;
extern s32 D_801E4A58[];

typedef struct {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s32 field_10;
} LocalStruct_8018A968;

/* register pins reproduce the target's density-priority regalloc order (cookbook, banked
 * twin md_SC07_004:func_801AD7EC): pos/idx are read+written every iteration (highest density)
 * -> $s0/$s1; p0/p1/i/tab are read/written once per iteration -> $s2/$s3/$s4/$s6; self is the
 * cross-call-live copy of a0 -> $s5. Statement order mirrors the target's prologue schedule. */
void func_8018A968(s32 a0)
{
    register s32 pos __asm__("$16");
    register s32 idx __asm__("$17");
    register s32 *p0 __asm__("$18");
    register s32 *p1 __asm__("$19");
    register s32 i __asm__("$20");
    register s32 self __asm__("$21") = a0;
    register u16 *tab __asm__("$22");
    LocalStruct_8018A968 local;
    s32 v0;
    s32 v1;
    register s32 *pbase __asm__("$2");
    register u16 tmp __asm__("$3");

    i = 0;
    tab = &D_80195AD6;
    pbase = D_801E4A58;
    p1 = pbase + 1;
    idx = 0;
    p0 = pbase;

    tmp = *(u16 *)D_80195AC6;

    local.field_2 = -0x8C0;
    local.field_6 = 0x57;
    local.field_A = 0;
    local.field_8 = 0;
    local.field_E = 0;
    local.field_10 = 0;

    pos = tmp - 0xA8;

    for (; i < 6; i++) {
        v0 = tab[0];
        local.field_4 = pos;
        v0 = v0 + 0xE4;
        local.field_0 = v0;
        v1 = func_8012C51C(&local, 0);
        *p0 = v1;
        if (v1 != 0) {
            *(s32 *)(v1 + 0x64) = self;
            *(s16 *)(v1 + 0x100) = idx;
        }

        v0 = tab[-1];
        local.field_4 = pos;
        v0 = v0 - 0x114;
        local.field_0 = v0;
        v1 = func_8012C51C(&local, 0);
        *p1 = v1;
        if (v1 != 0) {
            *(s32 *)(v1 + 0x64) = self;
            *(s16 *)(v1 + 0x100) = idx + 1;
        }

        pos += 0x150;
        p1 += 2;
        idx += 2;
        p0 += 2;
    }
}


extern s32 D_801E4A84;

void func_8018AA88(void) {
    s32 i;
    s32 *ptr;

    i = 11;
    ptr = &D_801E4A84;
    do {
        *ptr = 0;
        ptr--;
    } while (--i >= 0);
}


extern s32 D_801E4A58[];
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8012B23C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_8018AAAC(void) {
    s32 *p;
    s32 i;
    s32 ent;

    i = 0;
    p = D_801E4A58;
    do {
        ent = *p;
        if (ent != 0 && *(u16 *)(ent + 2) == 2) {
            func_80132784(ent, *(s32 *)(ent + 0x64), *(u16 *)(ent + 0xFE));
            *(s16 *)(ent + 6) = *(s32 *)(*(s32 *)(ent + 0x20) + 0x48);
            *(s16 *)(ent + 0xA) = *(s32 *)(*(s32 *)(ent + 0x20) + 0x4C);
            *(s16 *)(ent + 0xE) = *(s32 *)(*(s32 *)(ent + 0x20) + 0x50);
            func_8012B23C(ent);
            *(s32 *)(ent + 0x10) = 0x100000;
            *(s32 *)(ent + 0x14) = 0xFFE00000;
            *(s32 *)(ent + 0x18) = 0xFFFC0000;
            *(s32 *)(ent + 0x1C) = 0x20;
            func_8012AD44((s32 *)ent, 5);
        }
        i++;
        p++;
    } while (i < 12);
}


#include "common.h"

extern void func_8012C218(void *a0);
extern s32 D_801E4A58[];

void func_8018AB84(void) {
    s32 *p;
    s32 i;
    s32 val;

    i = 0;
    p = D_801E4A58;
    do {
        val = *p;
        if (val != 0) {
            *p = 0;
            func_8012C218((void *)val);
        }
        i++;
        p++;
    } while (i < 12);
}


extern s32 D_801E4A58[];

void *func_8018ABE0(s32 a0)
{
    if ((u32)(a0 & 0xFFFF) < 12) {
        return D_801E4A58[(s16)a0];
    }
    return 0;
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018AC10);

s32 func_8018AC48(s32 a0) {
    extern s32 D_801E4A58[];
    s32 i;
    s32 *p;
    s32 ent;

    for (i = 0, p = D_801E4A58; i < 12; i++, p++) {
        ent = *p;
        if (ent == 0) {
            continue;
        }
        if (*(s16 *)(ent + 0xFC) != 0) {
            continue;
        }
        if ((u16)(*(u16 *)(a0 + 0xE) - *(u16 *)(ent + 0xE) - 0xC1) < 0xFF) {
            return i;
        }
    }
    return -1;
}


extern s32 D_801E4A58[];

s32 func_8018ACB4(void *a0) {
    s32 i;
    s32 *p;
    s32 ent;

    for (i = 0, p = D_801E4A58; i < 12; i++, p++) {
        ent = *p;
        if (ent == 0) {
            continue;
        }
        if (*(s16 *)(ent + 0xFC) != 0) {
            continue;
        }
        if ((u16)(*(u16 *)(ent + 0xE) - *(u16 *)(a0 + 0xE) - 0x81) < 0x1F) {
            return i;
        }
    }
    return -1;
}


extern s32 D_801E4A58[];

s32 func_8018AD20(s32 a0) {
    s32 i;
    s32 *p;
    s32 ent;
    s32 res;

    for (i = 0, p = D_801E4A58; i < 6; i++, p += 2) {
        res = i * 2;
        ent = *p;
        if (ent == 0) {
            continue;
        }
        if (*(s16 *)(ent + 0xFC) != 0) {
            continue;
        }
        if ((u16)(*(u16 *)(a0 + 0xE) - *(u16 *)(ent + 0xE) + 3) < 7) {
            return res;
        }
    }
    return -1;
}


#include "common.h"

extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8018A4C4(s32 a0);
extern s32 D_801E4A58[];

void func_8018AD8C(s32 arg0, s32 arg1)
{
    s32 s0 = D_801E4A58[arg0];

    if (s0 != 0) {
        *(s16 *)(s0 + 0xFE) = arg1;
        *(s32 *)(s0 + 0xC) = 0;
        *(s32 *)(s0 + 8) = 0;
        *(s32 *)(s0 + 4) = 0;
        *(s16 *)(s0 + 0xFC) = 1;
        func_8012AD44((s32 *)s0, 2);
        func_8018A4C4(s0);
    }
}


#include "common.h"

extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012B200(u8 *a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern s32 D_801E4A58[];

void func_8018ADF0(s32 arg0) {
    s32 s0 = D_801E4A58[arg0];

    if (s0 != 0) {
        func_80132784(s0, *(s32 *)(s0 + 0x64), *(u16 *)(s0 + 0xFE));
        *(s16 *)(s0 + 6) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x48);
        *(s16 *)(s0 + 0xA) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x4C);
        *(s16 *)(s0 + 0xE) = *(s32 *)(*(s32 *)(s0 + 0x20) + 0x50) - 0x10;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0x100;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0x200;
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x14) = 0;
        func_8012B200((u8 *)s0);
        *(s32 *)(s0 + 0x18) = 0xFFE00000;
        *(s32 *)(s0 + 0x14) = 0x200000;
        *(s32 *)(s0 + 0x10) = 0xFFF00000;
        func_8012AD44((s32 *)s0, 3);
    }
}


#include "common.h"

extern void func_8001C924(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 D_801E4A58[];
extern u8 D_801964D4[];

void func_8018AEB4(s32 a0, s32 a1)
{
    s32 s0;
    s32 s1;
    s32 v1;

    s0 = D_801E4A58[a0];
    if (s0 != 0) {
        s1 = a1;
        *(s16 *)(s0 + 0xFC) = 1;
        func_8001C924(*(s32 *)(s0 + 0x20), D_801964D4);
        func_8012AD44((s32 *)s0, 4);
        func_8012C658(0x60, s1, s0);
        if (s1 != 0) {
            v1 = func_80132EF4(s0, 0xC);
            if (v1 != 0) {
                *(u16 *)(v1 + 0xA) += 0x60;
            }
        }
    }
}


#include "common.h"

/* Local idiom types (mirrors the TU's own MTX_CF90 pattern / shared Vec32,
 * kept file-local since match_one compiles standalone with -Iinclude only). */
typedef struct { s16 m[3][3]; s32 t[3]; } Mtx8_8018AF58;
typedef struct { s32 vx, vy, vz, pad; } Vec32_8018AF58;

extern Blk20 D_800AE620;
extern Blk16_801E2F08 D_801E2F08;

extern u8 *func_8012913C(s32 a0);
extern void func_80129350(s32 a0, s32 a1);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018AF58(s32 a0)
{
    Mtx8_8018AF58 localMatrix;
    Vec32_8018AF58 fixedVec;
    s32 i;
    u8 *p;

    fixedVec = (*(Vec32_8018AF58 *)&D_801E2F08);

    for (i = 0; i < 8; i++) {
        p = func_8012913C(0xC);
        if (p != NULL) {
            func_80129350((s32)p, a0);
            localMatrix = (*(Mtx8_8018AF58 *)&D_800AE620);
            RotMatrixY(i << 9, &localMatrix);
            func_800484EC((s32)&localMatrix, (s32)&fixedVec, (s32)p + 0x10);
        }
    }
}


#include "common.h"



/* D_801E2F00: 8-byte, alignment-1 blob -- copied with lwl/lwr (gcc's
 * emit_block_move for align < 4), same idiom as the TU's other Blob8
 * globals (func_8018A4C4's D_801E2F30). Holds 3 x s16 angle (+ pad); the
 * middle field is overwritten right after the copy and re-biased each
 * loop iteration below. */
typedef struct { char b[8]; } Blob8_8018B058;
extern Blob8_8018B058 D_801E2F00;

/* Vec32-shape local (matches the TU's Vec32_8018AF58 pattern): 3 x s32 +
 * pad, passed by address to func_800484EC as its translation-vector arg. */
typedef struct { s32 vx, vy, vz, pad; } Vec32_8018B058;

extern u8 D_80196870[];

extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8004978C(s16 *a0, void *a1);
extern void func_8012B23C(s32 a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018B058(s32 a0)
{
    Blob8_8018B058 angle;
    Vec32_8018B058 vec;
    MTX_CF90 mtx;
    s32 i;
    s32 s0;

    angle = D_801E2F00;

    vec.vx = *(s32 *)(a0 + 0x10) >> 2;
    vec.vy = (s32)0xFFF40000;
    vec.vz = *(s32 *)(a0 + 0x18) >> 2;
    *(s16 *)&angle.b[2] = -0x100;

    for (i = 0; i < 4; i++) {
        s0 = func_8012C658(0x54, D_80196870[i], 0);
        if (s0 != 0) {
            *(s32 *)(s0 + 4) = *(s32 *)(a0 + 4);
            *(s32 *)(s0 + 8) = *(s32 *)(a0 + 8);
            *(s32 *)(s0 + 0xC) = *(s32 *)(a0 + 0xC);
            func_8004978C((s16 *)&angle, &mtx);
            func_8012B23C(s0);
            func_800484EC((s32)&mtx, (s32)&vec, s0 + 0x10);
        }
        *(s16 *)&angle.b[2] += 0x200;
    }
}


#include "common.h"



extern Blk20 D_800AE620;
extern u16 D_800B99DC;
extern u16 D_800B99D8;
extern u8 D_80196880[];
extern u8 D_80196874[];

extern void RotMatrixY(s32 a0, void *a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012B23C(s32 a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_8018B16C(s32 a0, s32 a1, s32 a2)
{
    register s32 s0 __asm__("$16");
    register s32 i __asm__("$17");
    Blk20 localMatrix;

    localMatrix = D_800AE620;

    s0 = (s32)&D_800B99DC;
    RotMatrixY(*(u16 *)s0, &localMatrix);
    *(u16 *)s0 = *(u16 *)s0 + D_800B99D8;

    if (a1 > 0) {
        i = 0;
        do {
            s0 = func_8012C658(0x54, *(s32 *)(D_80196880 + i), 0);
            if (s0 != 0) {
                *(s16 *)(s0 + 6) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48) + *(u16 *)(a2 + 0);
                *(s16 *)(s0 + 0xA) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C) + *(u16 *)(a2 + 2);
                *(s16 *)(s0 + 0xE) = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50) + *(u16 *)(a2 + 4);
                func_8012B23C(s0);
                func_800484EC((s32)&localMatrix, (s32)(D_80196874 + i), s0 + 0x10);
            }
            i += 0x10;
        } while (i < (a1 << 4));
    }
}


void func_8018B2DC(void)
{
    extern u8 D_801E44F7;
    s32 i = 7;
    u8 *p = &D_801E44F7;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}


#include "common.h"

extern u8 D_801E44F0[];

s32 func_8018B300(void)
{
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801E44F0;
    do {
        if (*p == 0) {
            *p = v;
            ret = i;
            goto done;
        }
        i++;
        p++;
    } while (i < 8);
    ret = -1;
done:
    return ret;
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018B344);

#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80188A5C(void *arg0);

extern u8 D_801BB8F8[];
extern u8 D_801964C4[];
extern M2C_UNK D_80190C0C;
extern u8 D_801964DC[];

void func_8018B368(void *a0) {
    s32 v0;
    register void *s0 __asm__("$16");
    s0 = a0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)s0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        *(s32 *)D_801964C4 = *(s32 *)D_801BB8F8;

        func_8001C214(*(s32 *)((u8 *)s0 + 0x20), (s32)D_801964C4);

        *(s32 *)(*(s32 *)((u8 *)s0 + 0x20) + 0x28) = 0xB000D0;

        func_8012A828((s32)s0, (void *)&D_80190C0C);

        *(s32 *)((u8 *)s0 + 0x58) = (s32)D_801964DC;

        *(s16 *)((u8 *)s0 + 0x5C) = 0xC00;

        *(s16 *)((u8 *)s0 + 0xFC) = 0;
        func_80188A5C(s0);
    }
}


void func_8018B408(void) {
}

extern void func_80132784(s32 a0, s32 a1, u32 a2);
    void func_8018B410(u8 *a0) {
        ((void (*)(u8 *, u8 *, u16))func_80132784)(a0, *(u8 **)(a0 + 0x64), *(u16 *)(a0 + 0xfe));
    }


void func_8018B438(void) {
}

extern void func_8012AD80(s32 a0);
extern void func_8018AC10(s32 a0);
extern s32 func_8012BEE8(s32 a0);

void func_8018B440(s32 a0) {
    if (func_8012BEE8(a0) != 0) {
        func_8018AC10(a0);
    } else {
        func_8012AD80(a0);
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48) = *(s16 *)(a0 + 6);
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C) = *(s16 *)(a0 + 0xA);
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50) = *(s16 *)(a0 + 0xE);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) | 1;
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_8018B4D0(s32 a0) {
    if (((s32 *)a0)[0x1C / 4] & 1) {
        s32 *ptr1 = (s32 *)((s32 *)a0)[0x20 / 4];
        s32 field1 = ptr1[1];
        field1 |= 0x80000000;
        ptr1[1] = field1;
    } else {
        s32 *ptr2 = (s32 *)((s32 *)a0)[0x20 / 4];
        s32 field2 = ptr2[1];
        field2 &= 0x7FFFFFFF;
        ptr2[1] = field2;
    }

    if (func_8012BEE8(a0) != 0) {
        func_8012C218((void *)a0);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern u8 *func_8012913C(s32 a0);

void func_8018B554(s32 a0) {
    s32 v0;
    s32 i;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    func_8001C2C4(v0);

    for (i = 0; i < 0xF; i++) {
        v0 = (s32)func_8012913C(0xB);
        if (v0 != 0) {
            *(s32 *)(v0 + 0x2C) = a0;
            *(u16 *)(v0 + 0x30) = i;
        }
    }

    *(u16 *)(a0 + 0x2) += 1;
    *(u16 *)(a0 + 0x34) = 0;
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018B5E0);

extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void (*D_801965C8[])(void);
extern void func_801895E0();

void func_8018B638(s32 arg0) {
    s32 iVar1;

    iVar1 = *(s32 *)(arg0 + 0x20);
    ((void (*)(s32, s32, s32, s32))func_8001CC3C)(iVar1, (s32)&D_801965C8, 0x2BC, 0x1B0);
    *(u8 *)(iVar1 + 0x27) = 0x59;
    ((void (*)(s32))func_801895E0)(arg0);
    *(u16 *)((s32)arg0 + 2) += 1;
}


extern void func_801292C8(u8 *a0);
extern void func_801895E0();

void func_8018B6A0(s32 arg0) {
    if (*(s16 *)(*(s32 *)(arg0 + 0x2C) + 0xFC) != 0) {
        func_801292C8((u8 *)arg0);
    } else {
        func_801895E0(arg0);
    }
}


#include "common.h"

extern void func_8001CB6C(u8*, s32, s32, s32);
extern u8 D_80196614[];
extern u8 D_80196620[];
extern u8 D_80196660[];

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018B6E8(s32 param_1) {
    s32 temp;
    s32 var;

    temp = *(s32 *)(param_1 + 0x20);
    func_8001CB6C((u8 *)temp, (s32)&D_80196614, 0x320, 0x100);
    var = *(s32 *)(param_1 + 0x34);
    *(u16 *)(temp + 0x1C) = 0x2800;
    *(u16 *)(temp + 0x1A) = 0x2800;
    *(u16 *)(temp + 0x18) = 0x2800;
    *(u8 *)(temp + 0x27) = 0x5F;
    *(u32 *)(temp + 0x34) = var;
    *(u32 *)(temp + 4) |= 0x50000000;
    if (*(s16 *)(temp + 0x1E) != 0) {
        func_80128EA8(temp, param_1 + 0x24, (s32)&D_80196660);
    } else {
        func_80128EA8(temp, param_1 + 0x24, (s32)&D_80196620);
    }
    *(u16 *)(param_1 + 2) += 1;
}


extern s32 func_80128ED8(s32, s32*);
extern void func_801292C8(u8*);

void func_8018B7A4(s32 param_1)
{
    if (func_80128ED8(*(s32 *)(param_1 + 0x20), (s32 *)(param_1 + 0x24)) != 0) {
        if (*(s32 *)(param_1 + 0x2C) != 0) {
            *(s16 *)(*(s32 *)(param_1 + 0x2C) + 0xFC) = 1;
        }
        func_801292C8((u8 *)param_1);
    }
}


#include "common.h"

extern u8 D_800D387C[];
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018B7F8(s32 param_1)
{
    extern u8 D_80196710[];
    extern u8 D_801966C0[];
    s32 p;
    u16 v;
    s32 a0;
    s32 a1;
    s32 a2;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_800D387C;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x9c;

    v = *(u16 *)(param_1 + 0x34) & 0x7fff;
    if (v != 0) {
        p = *(s32 *)(param_1 + 0x20);
        *(u16 *)(p + 0x1a) = v;
    } else {
        p = *(s32 *)(param_1 + 0x20);
        v = 0x6000;
        *(u16 *)(p + 0x1a) = v;
    }
    *(u16 *)(p + 0x18) = v;

    a1 = param_1 + 0x24;
    if (*(s16 *)(param_1 + 0x34) & 0x8000) {
        a0 = *(s32 *)(param_1 + 0x20);
        a2 = (s32)D_80196710;
    } else {
        a0 = *(s32 *)(param_1 + 0x20);
        a2 = (s32)D_801966C0;
    }
    func_80128EA8(a0, a1, a2);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801921F8;

void func_8018B8CC(s32 param_1)
{
    func_8001CB6C((u8 *)*(s32 *)(param_1 + 0x20), (s32)&D_801921F8, 0x250, 0x1A0);
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) = 0x60000000;
    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x14;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0x400;
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


extern s32 D_801270C8;
extern void func_801292C8(u8 *a0);

void func_8018B93C(void) {
    if (*(s32 *)&D_801270C8 == 0x13) {
        ((void (*)(void))func_801292C8)();
    }
}


#include "common.h"

extern void func_801439FC(s32 a0);

void func_8018B96C(s32 a0) {
    s32 v0;
    s32 v1;
    s32 s0;
    s32 pad[2];

    v0 = *(s32 *)(*(s32 *)(a0 + 0x64) + 0x20);
    v0 = *(s32 *)(v0 + 4);
    s0 = *(s32 *)(a0 + 0xCC);
    if (v0 < 0) {
        *(u32 *)(s0 + 4) |= 0x80000000;
    } else {
        func_801439FC(a0);
    }

    v0 = *(s32 *)(a0 + 0x64);
    *(u16 *)(s0 + 0x14) = *(u16 *)(*(s32 *)(v0 + 0x20) + 0x12);

    v0 = *(s32 *)(a0 + 0x64);
    v1 = *(u16 *)(s0 + 0xA) - *(u16 *)(v0 + 0xA);
    if ((u16)(v1 + 0x20) >= 0x421) {
        *(s16 *)(s0 + 0x1A) = 0;
        *(s16 *)(s0 + 0x18) = 0;
    } else {
        v1 = v1 << 16;
        v1 = v1 >> 11;
        v0 = -0x8000 - v1;
        *(s16 *)(s0 + 0x1A) = v0;
        *(s16 *)(s0 + 0x18) = v0;
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 rand(void);

extern u8 D_801966A8[];
extern u8 D_801966B0[];
extern M2C_UNK D_80190C0C;

void func_8018BA38(s32 param_1)
{
    register s32 s0 __asm__("$16");
    register s32 a0 __asm__("$4");
    s32 pad[4];
    s32 ret;

    ret = ((s32 (*)(void))func_8012C1B8)();
    s0 = param_1;
    a0 = ret;
    *(s32 *)(s0 + 0x20) = ret;
    if (a0 == 0) {
        func_8012CAE4((void *)s0);
        return;
    }
    func_8001C214(a0, (*(u16 *)(s0 + 0x70) & 1) ? (s32)D_801966B0 : (s32)D_801966A8);
    func_8012A828((s32)s0, (void *)&D_80190C0C);
    *(s16 *)(s0 + 0xFC) = rand() & 0x3F0;
    *(s16 *)(s0 + 0xFE) = rand() & 0x3F0;
    *(s32 *)(s0 + 0x1C) = 0x60;
    *(s16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_8018BAE4(s32 arg0) {
    s32 s0;
    s32 a0;
    s32 a1;

    s0 = arg0;
    a0 = *(s32 *)(s0 + 0x20);
    *(u16 *)(a0 + 0x12) = *(u16 *)(a0 + 0x12) + *(u16 *)(s0 + 0xFC);
    a1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(a1 + 0x10) = *(u16 *)(a1 + 0x10) + *(u16 *)(s0 + 0xFE);
    func_8012AD80(s0);
    if (*(s16 *)(s0 + 0xA) >= -0x7FF) {
        func_8012C218((void *)s0);
    }
}


extern void func_8012931C(void *);
extern s32 func_80128ED8(s32, s32*);
extern void func_801292C8(u8*);

void func_8018BB58(s32 a0) {
    s32 s0 = a0;
    func_8012931C((void *)a0);
    if (((s32 (*)(s32, void *))func_80128ED8)(*(s32 *)(s0 + 0x20), (void *)(s0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(s0);
    }
}


#include "common.h"

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 D_80196768;
extern s32 D_80196774;

void func_8018BB9C(s32 param_1)
{
    s32 v0;
    s32 v1;

    // *(u32*)(*(s32*)(param_1 + 0x20) + 0x20) = (u32)&D_80196768;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_80196768;

    // *(u32*)(*(s32*)(param_1 + 0x20) + 4) |= 0x50000000;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    // *(u8*)(*(s32*)(param_1 + 0x20) + 0x27) = 0x90;
    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x90;

    // v0 = *(u16*)(param_1 + 0x34) & 0x7FFF;
    v0 = *(u16 *)(param_1 + 0x34) & 0x7FFF;

    if (v0) {
        v1 = *(s32 *)(param_1 + 0x20);
        *(s16 *)(v1 + 0x1A) = v0;
    } else {
        v1 = *(s32 *)(param_1 + 0x20);
        v0 = 0x3000;
        *(s16 *)(v1 + 0x1A) = v0;
    }

    *(s16 *)(v1 + 0x18) = v0;

    // func_80128EA8(*(u32*)(param_1 + 0x20), param_1 + 0x24, (s32)&D_80196774);
    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24, (s32)&D_80196774);

    // *(u16*)(param_1 + 0x2) = *(u16*)(param_1 + 0x2) + 1;
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}


extern void func_8012931C(void *);
extern s32 func_80128ED8(s32, s32*);
extern void func_801292C8(u8*);

void func_8018BC48(s32 a0) {
    func_8012931C((void *)a0);
    if (((s32 (*)(s32, void *))func_80128ED8)(*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(a0);
    } else {
        *(u8 *)(*(s32 *)(a0 + 0x20) + 0x27) = *(u8 *)(a0 + 0x28) - 0x70;
    }
}


extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 D_801967D4;

void func_8018BCA4(s32 param_1)
{
    func_80128D60(*(s32 *)(param_1 + 0x20), (s32 *)(param_1 + 0x24), &D_801967D4);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}


extern s32 func_80128DB4(s32 a0, s32 *a1);
    s32 func_8018BCEC(void *a0) {
        ((void (*)(void *, void *))func_80128DB4)(*(void **)((char *)a0 + 0x20), (void *)((char *)a0 + 0x24));
    }


#include "common.h"

extern u8 D_8019681C[];
extern u8 D_80196828[];

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018BD14(s32 param_1)
{
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_8019681C;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x65;

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24, (s32)&D_80196828);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(u8*);
void func_8018BD90(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(a0);
    }
}


#include "common.h"

/* ---- externs ------------------------------------------------------------ */
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8012AD44(s32 *a0, s16 a1);

extern u8 D_801E4918;
extern u8 D_801E491C;
extern u8 D_801E2F50;
extern u8 D_801E2F54;

/* align-1 4-byte block: lowers via emit_block_move (unaligned lwl/lwr + swl/swr)
 * with ZERO memcpy-symbol reference (house idiom, cf. func_8018CE04) */
typedef struct { u8 b[4]; } Blk4_8018BDD0;

void func_8018BDD0(s32 param_1)
{
    func_800233CC(&D_801E4918, 0x50);

    *(Blk4_8018BDD0 *)&D_801E4918 = *(Blk4_8018BDD0 *)&D_801E2F50;
    *(Blk4_8018BDD0 *)&D_801E491C = *(Blk4_8018BDD0 *)&D_801E2F54;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0xD0000000;
    *(s16 *)(param_1 + 0xA) = -0x20;
    *(s16 *)(param_1 + 0xE) = -0x20;
    *(s16 *)(param_1 + 6) = 0;

    /* store lands in the jal delay slot (executes before the callee) */
    *(s32 *)(param_1 + 0x1C) = 0xA;
    func_8012AD44((s32 *)param_1, 1);
}


#include "common.h"

extern u16 D_80126B5E;
extern u16 D_80126B66;

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_80132784(s32 a0, s32 a1, u32 a2);

void func_8018BE88(s32 arg0) {
    s32 self = arg0;
    s32 i;

    *(s16 *)(self + 0x6) = 0;
    *(s16 *)(self + 0xA) = 0;
    *(s16 *)(self + 0xE) = -0x30;
    func_80132784(self, *(s32 *)(self + 0xCC), *(u16 *)(self + 0x70));

    *(s16 *)(self + 0x6) = *(s32 *)(*(void **)(self + 0x20) + 0x48);
    *(s16 *)(self + 0xA) = *(s32 *)(*(void **)(self + 0x20) + 0x4C);
    *(s16 *)(self + 0xE) = *(s32 *)(*(void **)(self + 0x20) + 0x50);
    i = 0;

    *(u32 *)(*(s32 *)(self + 0x20) + 4) |= 0x80000000;

    for (; i < 8; i++) {
        func_8012C658(0x55, i, self);
    }

    func_8002D4C8(0x4EF, 0);

    {
        s32 t = *(s16 *)&D_80126B5E;
        s32 u = *(s16 *)(self + 0x6);
        *(s32 *)(self + 0x14) = 0;
        *(s32 *)(self + 0x10) = (t - u) << 13;
    }

    {
        s32 t = *(s16 *)&D_80126B66;
        s32 u = *(s16 *)(self + 0xE) + 0x20;
        *(s32 *)(self + 0x1C) = 4;
        *(s32 *)(self + 0x18) = (t - u) << 13;
    }

    func_8012AD44((s32 *)self, 2);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018BF88(u8 *a0) {
        *(s32 *)(a0 + 0x1c) = 0x20;
        *(s16 *)(a0 + 0x102) |= 2;
        ((void (*)(void *, s32))func_8012AD44)(a0, 0x3);
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018BFBC);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018BFDC(u8 *a0) {
        *(u16 *)(a0 + 0x102) |= 0x1;
        ((void (*)(void *, s32))func_8012AD44)(a0, 0x5);
    }


#include "common.h"

extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_8018C008(s32 arg0) {
    s32 self = arg0;
    s32 i;

    *(u16 *)(self + 0xE) -= 0x14;
    *(u16 *)(self + 0x100) = 0;

    for (i = 0; i < 8; i++) {
        if (func_8012C658(0x55, i + 8, self) != 0) {
            *(u16 *)(self + 0x100) += 1;
        }
    }

    func_8012AD44((s32 *)self, 6);
}



extern void (*D_801968F4[])(void);

void func_8018C08C(void *a0) {
    D_801968F4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern short D_80196B30;

void func_8018C0C8(void *arg0) {
    *(s16 *)((char *)arg0 + 0x5C) = 0;
    func_8012A828((s32)arg0, (void *)&D_80196B30);
    func_8012AD44((s32 *)arg0, 2);
}



extern void (*D_80196B80[])(void);

void func_8018C108(void *a0) {
    D_80196B80[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern void func_80189F44(s32 arg0);
extern s32 D_80196AE8;

void func_8018C144(void *a0) {
    u16 v0, v1;

    *(s16 *)((s32)a0 + 0x5C) = 0;

    v1 = *(u16 *)((s32)a0 + 0x5E);
    if (v1 != 0xC) {
        goto else_block;
    }

    func_8012A828((s32)a0, (void *)&D_80196AE8);
    v0 = *(u16 *)((s32)a0 + 0x70);
    *(u8 *)((s32)a0 + 0xC1) = 1;
    if ((v0 & 0x8) == 0) {
        goto skip_call;
    }

    func_80189F44((s32)a0);

skip_call:
    func_8002D4C8(0x4FE, 0);
    return;

else_block:
    *(s16 *)((s32)a0 + 0x5E) = 0;
    *(u8 *)((s32)a0 + 0xC1) = 0;
}


extern void func_8012C218(void *a0);

void func_8018C1C0(void *a0) {
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        void *v1 = *(void **)((s32)a0 + 0x64);
        *(s16 *)((s32)v1 + 0x100) -= 1;
        func_8012C218((void *)a0);
    }
}


#include "common.h"

extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern u16 D_80126B96;
extern s16 D_80126B98;

void func_8018C204(void *a0) {
    extern u16 D_80196B60;
    extern u16 D_80196B62;
    s16 p1[4];
    s16 p2[4];

    p1[2] = 0;
    p1[0] = 0;
    p2[2] = 0;
    p2[0] = 0;
    p1[1] = D_80196B60;
    p2[1] = D_80196B62;

    if (func_8012DEB8((s32)a0, (s32)p1, (s32)p2)) {
        D_80126B98 = 5;
        D_80126B96 |= 0x4200;
    }
}



extern void (*D_80196B8C[])(void);

void func_8018C274(void *a0) {
    D_80196B8C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

// @stuck: none — MATCH (42 ins), iteration 1, rtu_match clean.
// Saturating add of a 3-byte RGB triple by a signed delta.
// Idioms: (1) `s8` by-value param => entry `sll/sra 24` for the sign test only;
//   combine folds the extension back out of `~a1`/`-a1`/`a0[i]+a1` because every
//   consumer is 8-bit (andi 0xFF / sb), so $a1 is used RAW after the test.
// (2) branch sense read off the target `sltu` operand ORDER (§3-T4): positive arm
//   `sltu lim,p[i]` => store when `p[i] <= lim`; negative arm `sltu p[i],lim`
//   => store when `p[i] >= lim`.
// (3) the third `if` written out in BOTH arms; jump.c cross-jumps the identical
//   tails into the shared `j .L8018C344` (§5a) — do not hoist it after the if/else.
void func_8018C2B0(u8 *a0, s8 a1) {
    u8 lim;

    if (a1 == 0) {
        return;
    }
    if (a1 > 0) {
        lim = ~a1;
        if (a0[0] <= lim) {
            a0[0] = a0[0] + a1;
        }
        if (a0[1] <= lim) {
            a0[1] = a0[1] + a1;
        }
        if (a0[2] <= lim) {
            a0[2] = a0[2] + a1;
        }
    } else {
        lim = -a1;
        if (a0[0] >= lim) {
            a0[0] = a0[0] + a1;
        }
        if (a0[1] >= lim) {
            a0[1] = a0[1] + a1;
        }
        if (a0[2] >= lim) {
            a0[2] = a0[2] + a1;
        }
    }
}



extern void (*D_80196B98[])(void);

void func_8018C358(void *a0) {
    D_80196B98[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012AD44(s32 *a0, s16 a1);

void func_8018C394(s32 *a0) {
    s32 *v0;

    v0 = *(s32 **)(((u8 *)a0) + 0x20);
    *(s16 *)(((u8 *)v0) + 0x1C) = 0;
    *(s16 *)(((u8 *)v0) + 0x1A) = 0;
    *(s16 *)(((u8 *)v0) + 0x18) = 0;
    func_8012AD44(a0, 1);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018C3C4(void * arg0) {
        *(s8 *)((char *)arg0 + 0xfc) = 0x8;
        ((void (*)(s32, s32))func_8012AD44)((int)arg0, 0x2);
    }


















extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_801270C8;
void func_8018C3EC(void)
{
  int new_var;
  D_801270C8 = 0x21;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 0x3);
  new_var = 0 & 0xFFu;
}


extern void (*D_80196BA0[])(void);

void func_8018C418(void *a0) {
    D_80196BA0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* MTX_CF90-shape: rotation 3x3 (s16) + translation (s32 x3), 0x20 bytes total.
 * Matches the buffer func_8004978C(angle*, mtx*) fills (rotation only) and
 * that the GTE SetRotMatrix/SetTransMatrix ctc2 sequence below consumes. */


extern void func_8004978C(s16 *a0, void *a1);

void func_8018C454(void *a0)
{
    u8 *s0 = (u8 *)a0;
    MTX_CF90 mtx;
    s16 angle[3];
    s16 vec0[4];
    s32 flags;

    angle[2] = 0;
    angle[0] = 0;
    angle[1] = *(u16 *)(*(s32 *)(s0 + 0x64) + 0xFE)
             + ((*(u16 *)(s0 + 0x70) & 7) << 9);

    vec0[1] = 0;
    vec0[0] = 0;
    vec0[2] = *(u16 *)(*(s32 *)(s0 + 0x64) + 0xFC);

    mtx.t[0] = *(s16 *)(*(s32 *)(s0 + 0x64) + 0x6);
    mtx.t[1] = *(s16 *)(*(s32 *)(s0 + 0x64) + 0xA);
    mtx.t[2] = *(s16 *)(*(s32 *)(s0 + 0x64) + 0xE);

    func_8004978C(angle, &mtx);

    __asm__ __volatile__(
        "lw $12, 0(%0)\n"
        "lw $13, 4(%0)\n"
        "ctc2 $12, $0\n"
        "ctc2 $13, $1\n"
        "lw $12, 8(%0)\n"
        "lw $13, 12(%0)\n"
        "lw $14, 16(%0)\n"
        "ctc2 $12, $2\n"
        "ctc2 $13, $3\n"
        "ctc2 $14, $4\n"
        "lw $12, 20(%0)\n"
        "lw $13, 24(%0)\n"
        "ctc2 $12, $5\n"
        "lw $14, 28(%0)\n"
        "ctc2 $13, $6\n"
        "ctc2 $14, $7\n"
        : : "r"(&mtx) : "$12", "$13", "$14");

    __asm__ __volatile__(
        "lwc2 $0, 0(%0)\n"
        "lwc2 $1, 4(%0)\n"
        "nop\n"
        "nop\n"
        "mvmva 1, 0, 0, 0, 0\n"
        : : "r"(vec0) : "memory");

    __asm__ __volatile__(
        "swc2 $25, 0(%0)\n"
        "swc2 $26, 4(%0)\n"
        "swc2 $27, 8(%0)\n"
        : : "r"(s0 + 4) : "memory");

    __asm__ __volatile__(
        "cfc2 $12, $31\n"
        "nop\n"
        "sw $12, 0(%0)\n"
        : : "r"(&flags) : "$12", "memory");

    *(s32 *)(s0 + 4) <<= 16;
    *(s32 *)(s0 + 8) <<= 16;
    *(s32 *)(s0 + 0xC) <<= 16;
}




void func_8018C598(void *a0, s32 a1, s32 a2, s32 *a3, u16 a4, u16 a5)
{
    s32 v0;
    s32 v1;

    v0 = func_8012C588(0x7A, (s32)a0);
    if (v0 == 0) goto L_end;
    *(Blk8 *)(v0 + 0x50) = *(Blk8 *)(a1 + 0);
    v1 = *(s32 *)(v0 + 0x20);
    *(Blk8 *)(v1 + 0x10) = *(Blk8 *)(a2 + 0);
    *(u32 *)(v0 + 0x1C) = a5;
    if (a4 != 0) {
        *(u16 *)(v0 + 0xFC) = a4;
    } else {
        *(u16 *)(v0 + 0xFC) = 1;
    }
    *(u32 *)(v0 + 0xCC) = (s32)a3;
L_end:
    *a3 = v0;
}



extern void (*D_80196BB0[])(void);

void func_8018C66C(void *a0) {
    D_80196BB0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA88(s32 a0, void *a1);
extern void func_8018BDD0();
extern void func_8018C008();
extern u8 D_801E4918;

void func_8018C6A8(void *a0)
{
    s32 v0;

    *(s32 *)((u8 *)a0 + 0x20) = v0 = ((s32 (*)(void))func_8012C1B8)();

    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001CA88(v0, &D_801E4918);

        if (*(s16 *)((u8 *)a0 + 0x70) != 0) {
            *(s16 *)((u8 *)a0 + 0xFC) = 0;
            *(s16 *)((u8 *)a0 + 0xFE) = 0;
            *(s16 *)((u8 *)a0 + 0x102) = 0;
            func_8018BDD0(a0);
        } else {
            *(s32 *)((u8 *)v0 + 0x4) |= 0x80000000;
            *(s16 *)((u8 *)a0 + 0xFC) = 0x58;
            *(s16 *)((u8 *)a0 + 0xFE) = 0x100;
            *(s16 *)((u8 *)a0 + 0x102) = 0x2;
            func_8018C008(a0);
        }
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern s32 func_80185D6C();
extern void func_8018BE88(s32 a0);

/* 0x801E4918 is an 8-byte block; splat renders the +4/+5 bytes with the
 * next symbol's name (D_801E491C / D_801E491C+1), but the codegen proves
 * ONE base symbol: gcc materialises exactly one `la` per symbol that has a
 * non-foldable address reference, and the target has exactly one (`la $a0,
 * D_801E4918`) covering all four bytes.  Two separate symbols always cost a
 * second `la` (measured: every 2-symbol spelling loses 10-17 instructions of
 * shape).  Declared as the TU already declares it (`extern u8 D_801E4918;`,
 * cf. lines 6425 / 6556) — the array spelling is a HARD conflicting-types
 * error against that file-scope scalar decl. */
extern u8 D_801E4918;

void func_8018C758(void *a0) {
    s32 s0 = *(s32 *)((u8 *)a0 + 0x20);   /* the entity's 0x20 record */
    s32 v0;

    /* Clearing bit31 of rec->0x4 is written as read / mask / store with a
     * ZERO-BYTE sched2 fence between the mask and the store.  Without it,
     * sched2's backward list scheduler picks the call's `move $a0,$s1`
     * (equal priority 1, higher LUID) over the `ori` at the T-5 step and the
     * pair comes out `lui/ori/lw` + a load-delay nop (62 ins).  The fence
     * makes the store depend on it, which defers `move $a0`/the call, so the
     * step order becomes `and`, `ori`, `lw`, `lui` -> emitted
     * `lui / lw / ori / and`, exactly the target.  Placing the fence AFTER
     * the store instead also fixes the order but then the fence is the last
     * insn before the jal and reorg.c:stop_search_p refuses to look past an
     * ASM_INPUT, so the `sw` never reaches the call's delay slot. */
    v0 = *(s32 *)(s0 + 0x4) & 0x7FFFFFFF;
    __asm__ __volatile__("");
    *(s32 *)(s0 + 0x4) = v0;

    if (func_80185D6C(a0) != 0) {
        func_8012C218(a0);
    } else if (func_8012BEE8((s32)a0) != 0) {
        func_8018BE88((s32)a0);
    } else {
        /* p is what forces `la $a0, D_801E4918` (offset 0).  A direct
         * `D_801E4918 += 0x10` folds to the VAR_DECL and emits the inline
         * %hi/%lo form, which hands the single `la` to the +1 byte instead —
         * the mirror image of the target. */
        u8 *p = (u8 *)&D_801E4918;

        v0 = *(u16 *)(s0 + 0x1C) - 0x180;
        *(u16 *)(s0 + 0x1C) = v0;
        *(u16 *)(s0 + 0x1A) = v0;
        *(u16 *)(s0 + 0x18) = v0;

        p[0] += 0x10;
        ((u8 *)&D_801E4918)[1] += 0x10;
        ((u8 *)&D_801E4918)[4] += 0x10;   /* = D_801E491C     */
        ((u8 *)&D_801E4918)[5] += 0x8;    /* = D_801E491C + 1 */

        func_80132784((s32)a0, *(s32 *)((u8 *)a0 + 0xCC), *(u16 *)((u8 *)a0 + 0x70));
    }
}


extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8018BF88(u8 *a0);

void func_8018C84C(s32 a0)
{
    s16 temp;
    u16 temp2;
    u16 cnt;
    s32 t;
    s32 u;

    func_8012AD80(a0);
    temp = *(s16 *)(a0 + 0xFC);
    if (temp < 0x80)
    {
        *(s16 *)(a0 + 0xFC) = temp + 0x10;
    }
    temp2 = *(u16 *)(a0 + 0xFE);
    *(u16 *)(a0 + 0xFE) = temp2 - 0x40;
    if (func_8012BEE8(a0) != 0)
    {
        if (*(u16 *)(a0 + 0x34) == 0)
        {
            *(s32 *)(a0 + 0x10) = (*(s16 *)&D_80126B5E - *(s16 *)(a0 + 6)) << 14,
            *(s32 *)(a0 + 0x14) = (*(s16 *)(*(s32 *)(a0 + 0x64) + 0xA) - *(s16 *)(a0 + 0xA)) << 14;
            cnt = *(u16 *)(a0 + 0x34) + 1;
            t = *(s16 *)&D_80126B66;
            u = *(s16 *)(a0 + 0xE) + 0x20;
            *(s32 *)(a0 + 0x1C) = 4;
            *(u16 *)(a0 + 0x34) = cnt;
            *(s32 *)(a0 + 0x18) = (t - u) << 14;
        }
        else
        {
            func_8018BF88(a0);
        }
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8018BFBC(s32 a0);

void func_8018C928(int param_1)
{
    *(unsigned short *)(param_1 + 0x102) |= 4;
    *(unsigned short *)(param_1 + 0xFE) -= 0x40;
    if (func_8012BEE8(param_1) != 0) {
        func_8018BFBC(param_1);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8018BFDC(u8 *a0);

void func_8018C978(s32 arg0)
{
    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        if (*(s16 *)(arg0 + 0xFC) >= 0x51) {
            *(s16 *)(arg0 + 0xFC) -= 2;
        } else {
            *(s32 *)(arg0 + 0x1C) = 0xA0;
            *(u16 *)(arg0 + 0x34) += 1;
        }
        break;
    case 1:
        if (func_8012BEE8(arg0) != 0) {
            func_8018BFDC((u8 *)arg0);
        }
        break;
    }

    *(u16 *)(arg0 + 0xFE) -= 0x40;
}


extern void func_8012C218(void *a0);
    void func_8018CA1C(void) {
        ((s32 (*)(void))func_8012C218)();
    }


extern s32 D_801270C8;
extern void func_8012C218(void *a0);

void func_8018CA3C(s32 a0) {
    if (*(s16 *)(a0 + 0x100) == 0) {
        D_801270C8 = 13;
        func_8012C218((void *)a0);
    }
}


#include "common.h"

/* Fleet-canonical prototypes (ov_SC02_005 / ov_SC03_006 file-scope spelling).
 * func_8012C1B8 is canonically `void` returning; the value in $v0 is taken via a
 * cast at the call site, exactly as the banked family exemplar in
 * src/ov_SC03_006/ov_SC03_006_jr_80140608.c does. */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012AD50(void *a0);

extern s32 D_80196910;
extern s32 D_80196B68;
extern s32 D_80196B58;
extern s32 D_80196A60;

void func_8018CA74(s32 param_1)
{
    register s32 d __asm__("$16") = param_1;
    register s32 obj __asm__("$17");
    /* $a1 pin on the shared `1`: without it the const-1 pseudo and the 0xC4
     * pseudo both land in $v0 (disjoint ranges after sched1), which pins the
     * 0xC4 load below the two sb's in sched2. See notes in the wave report. */
    register u8 one __asm__("$5");
    s32 ret;
    s32 c4v;
    u16 aev;
    u16 f70v;

    ret = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(d + 0x20) = ret;
    obj = ret;
    if (ret == 0) {
        func_8012CAE4((void *)d);
        return;
    }
    func_8001CA1C(obj, (s32)&D_80196910);
    *(s16 *)(obj + 0x1c) = 0x2800;
    *(s16 *)(obj + 0x1a) = 0x2800;
    *(s16 *)(obj + 0x18) = 0x2800;
    *(s32 *)(d + 0xbc) = (s32)&D_80196B68;
    *(s32 *)(d + 0x58) = (s32)&D_80196B58 | 0x20000000;
    c4v = *(s32 *)(d + 0xc4);
    one = 1;
    *(u8 *)(d + 0xc0) = one;
    *(u8 *)(d + 0x75) = one;
    *(s32 *)(d + 0xb4) = 0;
    *(u8 *)(d + 0xc1) = 0;
    *(s32 *)(d + 0xc4) = c4v | 2;
    *(s32 *)(*(s32 *)(d + 0x20) + 4) |= 0x50000000;
    aev = *(u16 *)(d + 0xae);
    *(s16 *)(d + 0x5c) = 0;
    aev |= 0xfffd;
    *(s16 *)(d + 0xae) = (s16)aev;
    func_8012A828(d, &D_80196A60);
    f70v = *(u16 *)(d + 0x70);
    *(s16 *)(d + 0x98) = 1;
    f70v &= 7;
    *(s32 *)(d + 0x94) = f70v;
    func_8012AD50((void *)d);
}


extern void func_8018C204(void *a0);
extern void func_8018C0C8(void *a0);

void func_8018CB70(void *arg0) {
    void *v0;
    u16 s1;

    v0 = *(void **)((u8 *)arg0 + 0x64);
    s1 = *(u16 *)((u8 *)v0 + 0x102);

    if (s1 & 4) {
        func_8018C204(arg0);
    }
    if (s1 & 2) {
        *(u16 *)((u8 *)arg0 + 0x5C) |= 0x8000;
    }
    func_8018C454(arg0);
    if (s1 & 1) {
        func_8018C0C8(arg0);
    }
}


extern void func_8012C218(void *a0);
    void func_8018CBF8(s32 *a0) {
        if (*(s16 *)((char *)a0 + 0x98) == 0) {
            ((void (*)(void))func_8012C218)();
        }
    }


#include "common.h"

typedef struct { u8 b[4]; } Blk4_8018CC28;

/* ---- externs ------------------------------------------------------------ */
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *a0, unsigned short a1);

extern u8 D_801E4958[];
extern u8 D_801E495C;
extern u8 D_801E2F58;
extern u8 D_801E2F5C;

void func_8018CC28(s32 param_1)
{
    func_8001CD50(*(s32 *)(param_1 + 0x20), (s32)&D_801E4958);

    *(u16 *)(param_1 + 0xA) -= 0x100;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0x400;
    *(s16 *)(param_1 + 0x2C) = 0x8;

    func_800233CC(&D_801E4958, 0x8);

    *(Blk4_8018CC28 *)&D_801E4958 = *(Blk4_8018CC28 *)&D_801E2F58;
    *(Blk4_8018CC28 *)&D_801E495C = *(Blk4_8018CC28 *)&D_801E2F5C;

    *(u16 *)(param_1 + 2) += 1;
}


#include "common.h"

/* ---- externs ------------------------------------------------------------ */
extern void func_800233CC(void *a0, unsigned short a1);

extern u8 D_801E4958[];

void func_8018CCF8(s32 param_1)
{
    u8 *s0 = &(*(u8 *)D_801E4958);

    *(u16 *)(param_1 + 0x2C) = *(u16 *)(param_1 + 0x2C) + 0x20;
    func_8018C2B0(s0, -4);
    func_8018C2B0(s0 + 4, -4);
    func_800233CC(s0, *(u16 *)(param_1 + 0x2C));

    if (*(s16 *)(param_1 + 0x2C) >= 0x380) {
        s32 v0;

        v0 = *(u16 *)(param_1 + 2);
        *(s16 *)(param_1 + 2) = v0 + 1;
    }
}


#include "common.h"

extern u8 D_801E4958[];
extern void func_801292C8(u8 *a0);
extern void func_8018C2B0(u8 *a0, s8 a1);
extern void func_800233CC(void *a0, unsigned short a1);

void func_8018CD80(s32 param_1)
{
    u8 *p;

    *(u16 *)(param_1 + 0x2C) -= 0x20;
    if (*(s16 *)(param_1 + 0x2C) <= 0) {
        ((void (*)(void))func_801292C8)();
        return;
    }

    p = D_801E4958;
    func_8018C2B0(p, -4);
    func_8018C2B0(p + 4, -4);
    func_800233CC(p, *(u16 *)(param_1 + 0x2C));
}


#include "common.h"

/* ---- externs ------------------------------------------------------------ */
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *a0, unsigned short a1);

extern u8 D_801E4918;
extern u8 D_801E491C;
extern u8 D_801E2F60;
extern u8 D_801E2F64;

/* align-1 4-byte block: lowers via emit_block_move (unaligned lwl/lwr + swl/swr)
 * with ZERO memcpy-symbol reference, so the TU's `extern memcpy` cannot turn
 * this into a CALL.  (house idiom, cf. func_8017B238 / func_8017B614) */

void func_8018CE04(s32 param_1)
{
    func_8001CD50(*(s32 *)(param_1 + 0x20), (s32)&D_801E4918);

    *(u16 *)(param_1 + 0xA) -= 0x100;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0x400;
    *(s16 *)(param_1 + 0x2C) = 0x10;

    func_800233CC(&D_801E4918, 0x10);

    *(Blk4_8018CE04 *)&D_801E4918 = *(Blk4_8018CE04 *)&D_801E2F60;
    *(Blk4_8018CE04 *)&D_801E491C = *(Blk4_8018CE04 *)&D_801E2F64;

    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1E) = 0xC00;
    *(u16 *)(param_1 + 2) += 1;
}


extern void func_8018C2B0(u8 *a0, s8 a1);
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_801292C8(u8 *a0);
extern u8 D_801E491C;

void func_8018CEE0(void *param_1)
{
    s16 sp18;
    u8 *s0;

    sp18 = *(s16 *)((s32)param_1 + 0x2C);
    if (sp18 < 0x700) {
        s0 = &D_801E491C;
        *(s16 *)((s32)param_1 + 0x2C) = sp18 + 0x30;
        func_8018C2B0(s0, -4);
        func_800233CC(s0 - 4, *(u16 *)((s32)param_1 + 0x2C));
    } else {
        func_801292C8(param_1);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8018C394(s32 *a0);

extern u8 D_801F1988;
extern u8 D_801F2138;

void func_8018CF58(s32 param_1)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }

    ((void (*)(s32, s32))func_8001C810)(v0, (s32)&D_801F1988);

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0xCC) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        v0 = *(s32 *)(param_1 + 0x20);
        *(s16 *)v0 = 0;
        return;
    }

    ((void (*)(s32, s32))func_8001C810)(v0, (s32)&D_801F2138);

    *(s16 *)(param_1 + 0xA) -= 0x100;
    *(u8 *)(param_1 + 0xC0) = 0;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x10;
    *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(param_1 + 0xCC) + 0x2C) |= 0x10;

    func_8018C394((s32 *)param_1);
}


#include "common.h"

extern void func_8018C3C4(void *arg0);

void func_8018D04C(s32 param_1)
{
    s32 a1;
    u16 v0;
    u16 v1;

    a1 = *(s32 *)(param_1 + 0xCC);
    v1 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
    if (v1 < 0x5000) {
        s32 p20;

        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = v1 + 0x100;

        p20 = *(s32 *)(param_1 + 0x20);
        v1 = *(u16 *)(p20 + 0x18);
        *(u16 *)(p20 + 0x1C) = v1;
        *(u16 *)(p20 + 0x1A) = v1;

        v0 = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = v0 + 0x100;

        *(u16 *)(a1 + 0x12) = *(u16 *)(a1 + 0x12) - 0x100;

        *(u16 *)(a1 + 0x8) = *(u16 *)(param_1 + 0x6) + *(u16 *)(param_1 + 0x50);
        *(u16 *)(a1 + 0xA) = *(u16 *)(param_1 + 0xA) + *(u16 *)(param_1 + 0x52);
        *(u16 *)(a1 + 0xC) = *(u16 *)(param_1 + 0xE) + *(u16 *)(param_1 + 0x54);

        *(u16 *)(a1 + 0x18) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x18);
        *(u16 *)(a1 + 0x1A) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1A);
        *(u16 *)(a1 + 0x1C) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x1C);
    } else {
        func_8018C3C4((void *)param_1);
    }
}


#include "common.h"

extern void func_8017C048(void);
extern s32 func_8012BEE8(s32 a0);
/* §183 SIGNATURE-cast-at-call.  The destination TU DEFINES this function at line 6190
 * as `void func_8018C3EC(void)` — an explicit ZERO-parameter prototype, ABOVE this
 * insertion point — so the unspecified-list escape (`extern void func_8018C3EC();`)
 * does NOT save the one-argument call: gcc-2.7.2 rejects it with "too many arguments
 * to function `func_8018C3EC'".  Adopt the TU's prototype and cast at the call site
 * through a function pointer (the same idiom the TU's own func_8018C3EC body uses on
 * func_8012AD44).  Byte-identical — re-verified MATCH 54/54. */
extern void func_8018C3EC(void);
extern void func_80016450(s32 a0, s32 a1);

void func_8018D144(s32 param_1)
{
    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
    {
        u8 v0 = *(u8 *)(param_1 + 0xFC) + 0x10;
        *(u8 *)(param_1 + 0xFC) = v0;
        if (v0 >= 0xF1) {
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x80000000;
            *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) |= 0x80000000;
            *(s32 *)(param_1 + 0x1C) = 8;
            *(u16 *)(param_1 + 0x34) += 1;
            func_8017C048();
        }
        break;
    }
    case 1:
        if (func_8012BEE8(param_1) != 0) {
            ((void (*)(s32))func_8018C3EC)(param_1);
        }
        break;
    }

    func_80016450(*(u8 *)(param_1 + 0xFC), 1);
}


extern void func_8012C218(void *a0);
extern void func_80016450(s32 a0, s32 a1);

void func_8018D21C(void *a0) {
    u8 v;

    v = *(u8 *)((s32)a0 + 0xFC) - 3;
    *(u8 *)((s32)a0 + 0xFC) = v;
    if (v >= 9) {
        func_80016450(v, 1);
    } else {
        func_8012C218((void *)a0);
    }
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001C1E4(s32 a0);
extern s32 func_8012AD50(void *a0);
extern s16 D_801BDCD0;

void func_8018D270(void *a0) {
    register s32 v0 __asm__("$2");
    s32 v1;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;

    if (!v0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801BDCD0);

        v0 = *(s32 *)((s32)a0 + 0x20);
        *(s32 *)((s32)v0 + 0x20) = (s32)a0 + 0xDC;

        {
            register s32 a1_val __asm__("$5") = *(s32 *)((s32)*(s32 *)((s32)a0 + 0x64) + 0x20);
            if (a1_val) {
                func_8001C1E4(*(s32 *)((s32)a0 + 0x20));
                *(s16 *)((s32)a0 + 0xE) = 0;
                *(s16 *)((s32)a0 + 0xA) = 0;
                *(s16 *)((s32)a0 + 0x6) = 0;
            }
        }

        v0 = *(s32 *)((s32)a0 + 0x20);
        *(s32 *)((s32)v0 + 0x4) |= 0x80000000;
        func_8012AD50(a0);
    }
}


void func_8018D318(s32 a0) {
    if (*(s16 *)(a0 + 0xFC) != 0) {
        *(s16 *)(a0 + 0xFC) = *(s16 *)(a0 + 0xFC) - 1;
        if (*(s16 *)(a0 + 0xFC) != 0) {
            return;
        }
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) &= 0x7FFFFFFF;
    } else {
        if (func_8012BEE8(a0) != 0) {
            s32 cc = *(s32 *)(a0 + 0xCC);
            if (cc != 0) {
                *(s32 *)cc = 0;
            }
            func_8012C218((void *)a0);
        } else {
            if (*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) == 0) {
                *(u16 *)(a0 + 6) = *(u16 *)(*(s32 *)(a0 + 0x64) + 6);
                *(u16 *)(a0 + 10) = *(u16 *)(*(s32 *)(a0 + 0x64) + 10);
                *(u16 *)(a0 + 14) = *(u16 *)(*(s32 *)(a0 + 0x64) + 14);
            }
            {
                s32 r = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20);
                *(u16 *)r -= 2;
                if ((s16)(*(u16 *)r) < -0x20) {
                    *(u16 *)r = 0;
                }
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) += 0x40;
            }
        }
    }
}


extern s32 D_801270C8;
extern s32 func_8012C750(s32 a0);

void func_8018D43C(void) {
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;

    D_801270C8 = 0;
    buf.f06 = 0x52;
    buf.f04 = 0;
    buf.f02 = 0;
    buf.f00 = 0;
    buf.f0A = 0;
    buf.f08 = 0;
    buf.f0E = 0;
    buf.f10 = 0;
    func_8012C750((s32)&buf);
}


extern s32 D_801270C8;
extern s32 func_8012C750(s32 a0);

void func_8018D488(void) {
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;

    D_801270C8 = 0;
    buf.f06 = 0x52;
    buf.f04 = 0;
    buf.f02 = 0;
    buf.f00 = 0;
    buf.f08 = 1;
    buf.f0A = 0;
    buf.f0E = 0;
    buf.f10 = 0;
    func_8012C750((s32)&buf);
}


extern void (*D_80196C64[])(void);
extern s16 D_80196C44[];
extern u16 D_800B99DA;
extern s32 D_801270C8;
extern void MoveImage(void *a0, s32 a1, s32 a2);

struct imgrect { u16 x; u16 y; u16 w; u16 h; };

void func_8018D4D8(void *param_1)
{
    D_80196C64[*(u16 *)((char *)param_1 + 2)]();
    if (D_801270C8 < 0x17) {
        struct imgrect img;
        u16 *src = (u16 *)((char *)D_80196C44 + (*(u16 *)&D_800B99DA & 7) * 4);
        img.x = src[0];
        img.y = src[1];
        img.w = 6;
        img.h = 0x28;
        MoveImage(&img, 0x298, 0x1C0);
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018D574);

#include "common.h"

extern s32 func_8012C750(s32 a0);
extern s32 func_8012C51C(void *a0, s32 a1);

typedef struct {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s32 field_10;
} LocalStruct;

void func_8018D608(s32 a0)
{
    s32 s0;
    s32 *counter;
    LocalStruct local_struct;
    s32 v0;
    u16 *val;

    s0 = a0;
    counter = (s32 *)(s0 + 0x1C);

    (*counter)--;

    if (*counter != 0) {
        return;
    }

    local_struct.field_6 = 0x58;
    local_struct.field_0 = -0x50;
    local_struct.field_2 = -0x802;
    local_struct.field_4 = -0xF80;
    local_struct.field_A = 0;
    local_struct.field_8 = 0;
    local_struct.field_C = 0;

    v0 = func_8012C750((s32)&local_struct);

    local_struct.field_6 = 0x59;
    local_struct.field_0 = -0x70;
    local_struct.field_4 = 0;
    local_struct.field_2 = 0;
    local_struct.field_E = 0;
    local_struct.field_10 = 0;

    func_8012C51C(&local_struct, v0);

    val = (u16 *)(s0 + 0x2);
    (*val)++;
}


#include "common.h"

extern s32 D_801270C8;
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern s32 func_8012C750(s32 a0);

void func_8018D6B0(s32 a0) {
    s32 v1;
    struct {
        u16 f0;
        s16 f1;
        u16 f2;
        s16 f3;
        s16 f4;
        s16 f5;
        s16 f6;
        s16 f7;
        s32 f8;
    } local_var;

    v1 = D_801270C8;
    if (v1 != 8) {
        return;
    }

    local_var.f0 = D_80126B5E;
    local_var.f2 = D_80126B66;
    local_var.f3 = 0x5A;
    local_var.f1 = -0x940;
    local_var.f6 = 0xC0;
    local_var.f5 = 0;
    local_var.f4 = 0;
    local_var.f7 = 0;
    local_var.f8 = 0;

    func_8012C750((s32)&local_var);

    ((u16 *)a0)[1]++;
}


#include "common.h"

extern s32 D_801270C8;
extern s32 func_8012C750(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018D73C(void *a0)
{
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;

    if (D_801270C8 == 0x12) {
        buf.f06 = 0x5E;
        buf.f04 = 0;
        buf.f02 = 0;
        buf.f00 = 0;
        buf.f0A = 0;
        buf.f0C = 0;
        buf.f08 = 0xF5C0;
        buf.f0E = 0;
        buf.f10 = 0;

        func_8012C750((s32)&buf);

        buf.f08 = 0xF7C0;
        func_8012C750((s32)&buf);

        func_8002D4C8(0x8, 0x2);
        func_8002D4C8(0x50C, 0);

        *(u16*)((u8*)a0 + 0x2) += 1;
    }
}


void func_8018D7DC(void *a0) {
        *(s16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }


extern s32 D_801270C8;
extern s32 func_8012C750(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8013C9C4(void *a0);
extern void func_8018EA04(s32 a0);
extern u8 D_80196BEC[];

void func_8018D7F0(void *a0)
{
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;

    if (D_801270C8 != 0x14) {
        s32 v = *(u32 *)((s32)a0 + 0x1C);
        *(u32 *)((s32)a0 + 0x1C) = v - 1;
        if ((v & 7) == 0) {
            func_8013C9C4(&D_80196BEC);
        }
    } else {
        buf.f06 = 0x5C;
        buf.f00 = 0;
        buf.f02 = 0;
        buf.f04 = 0;
        buf.f0A = 0;
        buf.f08 = 0;
        buf.f0C = 0;
        buf.f0E = 0;
        buf.f10 = 0;

        func_8012C750((s32)&buf);

        func_8018EA04(1);

        func_8002D4C8(0x4FA, 0);

        *(u16 *)((s32)a0 + 2) += 1;
    }
}


extern s32 D_801270C8;
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018EA04(s32 a0);

void func_8018D8A8(void *a0)
{
    if (D_801270C8 == 0x15) {
        func_8018EA04(2);
        func_8002D4C8(5, 0);
        *(u32 *)((s32)a0 + 0x1C) = 0xE;
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


void func_8018D904(void *a0) {
        *(s16 *)((s32)a0 + 0x2) += 1;
    }


extern void func_8018F414(void);
extern s32 D_801270C8;

void func_8018D918(void *a0) {
    if (D_801270C8 >= 0x16) {
        func_8018F414();
        *(u16 *)((s32)a0 + 0x2) += 1;
    }
}


#include "common.h"

extern s32 func_8012C588(s32 a0, s32 a1);

void func_8018D964(void *a0)
{
    func_8012C588(0x68, (s32)a0);
    *(u16 *)((s32)a0 + 0x2) += 1;
}


extern s32 D_801270C8;
extern s32 func_8012C750(s32 a0);

void func_8018D9A4(void *a0)
{
    struct {
        u16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;
    s16 i;

    if (D_801270C8 == 0x18) {
        i = 0;
        buf.f06 = 0x5D;
        buf.f04 = 0;
        buf.f02 = 0;
        buf.f00 = 0;
        buf.f0A = 0;
        buf.f0C = 0;
        buf.f0E = 0;
        buf.f10 = 0;

        do {
            buf.f08 = i;
            func_8012C750((s32)&buf);
            i++;
        } while (i < 4);

        *(u16 *)((s32)a0 + 2) += 1;
    }
}


extern void func_80180A7C(void);
extern s32 D_801270C8;

void func_8018DA40(void *a0) {
    if (D_801270C8 == 0x1B) {
        func_80180A7C();
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


extern void func_8018F704(void);
extern s32 D_801270C8;

void func_8018DA8C(void *a0) {
    if (D_801270C8 == 0x21) {
        func_8018F704();
        *(u16 *)((s32)a0 + 2) += 1;
    }
}


void func_8018DAD8(void) {
}


extern void (*D_80196C9C[])(void);

void func_8018DAE0(void *a0) {
    D_80196C9C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_80196C14;

void func_8018DB1C(s32 arg0) {
    *(s32 *)(arg0 + 0x58) = &D_80196C14;
    *(s32 *)(arg0 + 0x1C) = 0x18;
    *(s16 *)(arg0 + 0x2) += 1;
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012C1B8(void);
extern void func_8001C97C(s32 *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001C1E4(s32);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80143994(s32 a0, s32 a1);

extern s32 D_80196BBC;
extern u8 D_801D852C[];
extern u8 D_801D8B8C[];
extern M2C_UNK D_80190C0C;
extern s32 D_800636C8;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_80126B6A;
extern u16 D_80126B72;

void func_8018DB40(void *a0) {
    void *s1;
    void *s2;
    void *s0;
    s32 v0;

    s1 = a0;
    v0 = *(s32 *)((u8 *)s1 + 0x1C);
    s2 = *(void **)((u8 *)s1 + 0x20);

    if (v0 != 0) {
        *(s32 *)((u8 *)s1 + 0x1C) = v0 - 1;
        return;
    }

    if (s2 == 0) {
        s32 *p = &D_80196BBC;
        *p = (s32)D_801D852C;
        if (func_8012C354((s32)s1, (s32)(p - 1)) == 0) {
            return;
        }
    }

    s2 = (void *)((s32 (*)(void))func_8012C1B8)();
    if (s2 == 0) {
        return;
    }

    s0 = D_801D8B8C;
    func_8001C97C((s32 *)s0);
    func_8001C214((s32)s2, (s32)s0);

    *(s16 *)((u8 *)s2 + 0x12) = -0x200;
    ((void (*)(s32, s32))func_8001C1E4)((s32)s2, *(s32 *)((u8 *)s1 + 0x20));

    *(s32 *)((u8 *)s2 + 0x20) = (s32)&D_800636C8;
    *(s16 *)((u8 *)s2 + 0xA) = -0x38;
    *(void **)((u8 *)s1 + 0xD0) = s2;
    func_8012A828((s32)s1, (void *)&D_80190C0C);

    if (*(s16 *)((u8 *)s1 + 0x70) != 0) {
        u16 t2;
        u16 t70;
        *(s16 *)((u8 *)s1 + 0x6) = -0x80;
        *(s16 *)((u8 *)s1 + 0xA) = -0xA40;
        __asm__ __volatile__("" ::: "memory");
        t2 = *(u16 *)((u8 *)s1 + 0x2);
        t70 = *(u16 *)((u8 *)s1 + 0x70);
        t2 = t2 + 2;
        *(u16 *)((u8 *)s1 + 0xE) = t70;
        *(u16 *)((u8 *)s1 + 0x2) = t2;
    } else {
        register s32 g __asm__("$2");
        *(s16 *)((u8 *)s1 + 0x6) = D_80126B5E;
        *(s16 *)((u8 *)s1 + 0xA) = D_80126B62 - 0x200;
        g = D_80126B66;
        *(s16 *)((u8 *)s1 + 0xE) = g;
        g = D_80126B6A;
        *(s16 *)((u8 *)s1 + 0x16) = 4;
        *(s16 *)((u8 *)s1 + 0x12) = (s16)g >> 1;
        *(s16 *)((u8 *)s1 + 0x1A) = (s16)D_80126B72 >> 1;
        *(s32 *)((u8 *)s1 + 0xCC) = ((s32 (*)(s32, s32))func_80143994)((s32)s1, 0x3000);
    }

    *(u16 *)((u8 *)s1 + 0x2) = *(u16 *)((u8 *)s1 + 0x2) + 1;
}


#include "common.h"

extern s32 func_8012D714(s32 a0, u32 a1);
extern u16 D_80126B96;
extern s16 D_80126B98;
extern void func_8012AD80(s32 a0);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8001C97C(s32 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u8 D_801D9044;

void func_8018DCD8(s32 a0)
{
    s32 s3;
    s16 i;

    s3 = *(s32 *)(a0 + 0x20);
    if (func_8012D714(a0, 2) != 0) {
        D_80126B96 = 0x4001;
        D_80126B98 = 5;
    }
    func_8012AD80(a0);
    if (*(s16 *)(a0 + 0xA) >= -0x802) {
        *(s16 *)(a0 + 0xA) = -0x802;
        **(s16 **)(a0 + 0xD0) = 0;
        for (i = 0; i < 8; i++) {
            func_8012C658(99, i, a0);
            func_8012C658(100, i, a0);
        }
        func_8001C97C((s32 *)&D_801D9044);
        *(s32 *)(s3 + 0x24) = &D_801D9044;
        *(s32 *)(a0 + 0x1C) = 0x10;
        func_8002D4C8(0x4FF, 0);
        *(u16 *)(a0 + 2) += 1;
    } else {
        *(s32 *)(a0 + 0x14) += 0x1C000;
    }
}


extern void func_801439C0(u8 *a0);
extern void func_8012C218(void *a0);

void func_8018DDFC(void *a0) {
    s32 var;
    void *p;

    var = *(s32 *)((s32)a0 + 0x1C);
    var = var - 1;
    *(s32 *)((s32)a0 + 0x1C) = var;
    if (var == -1) {
        p = *(void **)((s32)a0 + 0xD0);
        if (p != NULL) {
            *(s16 *)((s32)p + 0) = 0;
        }
        func_801439C0((u8 *)*(s32 *)((s32)a0 + 0xCC));
        func_8012C218((void *)a0);
    }
}


extern s32 D_801270C8;
extern void func_801439C0(u8 *a0);
extern void func_8012C218(void *a0);

void func_8018DE5C(void *a0) {
    void *p;

    if (D_801270C8 > 0x15) {
        p = *(void **)((s32)a0 + 0xD0);
        if (p != NULL) {
            *(s16 *)((s32)p + 0) = 0;
        }
        func_801439C0((u8 *)*(s32 *)((s32)a0 + 0xCC));
        func_8012C218((void *)a0);
    }
}


void func_8018DEB8(s16 param_1) {
    struct {
        s16 f00, f02, f04, f06, f08, f0A, f0C, f0E;
        u32 f10;
    } buf;

    buf.f0A = 0;
    buf.f0C = 0;
    buf.f04 = 0;
    buf.f02 = 0;
    buf.f00 = 0;
    buf.f0E = 0;
    buf.f10 = 0;

    switch (param_1) {
    case 0:
        func_8018EA04(3);
        break;
    case 1:
        func_8018EA04(4);
        buf.f04 = 0xB80;
        break;
    case 2:
        func_8018EA04(5);
        buf.f00 = -0xC00;
        buf.f04 = 0xC00;
        break;
    }

    buf.f06 = 0x5C;
    buf.f08 = param_1 + 1;
    func_8012C750((s32)&buf);
}



extern void (*D_80196CB0[])(void);

void func_8018DF88(void *a0) {
    D_80196CB0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018DFC4);

void func_8018E22C(void) {
}

extern void func_8012C218(void *a0);

void func_8018E234(void *a0) {
    s32 var;
    void *p;

    var = *(s32 *)((s32)a0 + 0x1C);
    p = *(void **)((s32)a0 + 0x20);
    var = var - 1;
    *(s32 *)((s32)a0 + 0x1C) = var;
    if (var != 0) {
        if (var < 0x10) {
            *(s32 *)((s32)p + 4) ^= 0x80000000;
        }
    } else {
        func_8012C218((void *)a0);
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);

void func_8018E288(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x1C);

    if (v1 < 0x24) {
        v1 = v1 + 1;
        *(s32 *)((s32)a0 + 0x1C) = v1;
        if (v1 == 1) {
            return;
        }
        if (*(s16 *)((s32)a0 + 0x70) == 4) {
            if (*(s16 *)((s32)a0 + 0xA) < -0x800) {
                void *p;

                *(s32 *)((s32)a0 + 0x48) = 0x1C000;
                func_8012AD80((s32)a0);

                p = *(void **)((s32)a0 + 0x20);
                *(s16 *)((s32)p + 0x10) -= (*(s32 *)((s32)a0 + 0x18) << 4) >> 16;

                p = *(void **)((s32)a0 + 0x20);
                *(s16 *)((s32)p + 0x14) -= (*(s32 *)((s32)a0 + 0x10) << 4) >> 16;
            }
        } else {
            if (*(s16 *)((s32)a0 + 0x6) < -0x5FF || *(s16 *)((s32)a0 + 0xA) < -0x7FF) {
                if (*(s16 *)((s32)a0 + 0xA) >= -0x3FF) {
                    func_8012C218((void *)a0);
                } else {
                    void *p;
                    s32 t;

                    *(s32 *)((s32)a0 + 0x48) = 0x1C000;
                    func_8012AD80((s32)a0);

                    p = *(void **)((s32)a0 + 0x20);
                    *(s16 *)((s32)p + 0x10) -= (*(s32 *)((s32)a0 + 0xDC) << 4) >> 16;

                    if (*(s16 *)((s32)a0 + 0x70) != 7) {
                        t = *(s32 *)((s32)a0 + 0x10);
                    } else {
                        t = *(s32 *)((s32)a0 + 0x18);
                    }
                    p = *(void **)((s32)a0 + 0x20);
                    *(s16 *)((s32)p + 0x12) += (t << 4) >> 16;
                }
            }
        }
    } else {
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        *(s16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) - 1;
    }
}



extern void (*D_80196CC0[])(void);

void func_8018E400(void *a0) {
    D_80196CC0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018E43C(void *a0) {
        *(s16 *)((s32)a0 + 0x2) += 1;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018E450);

void func_8018E6D4(void) {
}

extern void func_8012C218(void *a0);

void func_8018E6DC(void *a0) {
    s32 var;
    void *p;

    var = *(s32 *)((s32)a0 + 0x1C);
    p = *(void **)((s32)a0 + 0x20);
    var = var - 1;
    *(s32 *)((s32)a0 + 0x1C) = var;
    if (var != 0) {
        if (var < 0x10) {
            *(s32 *)((s32)p + 4) ^= 0x80000000;
        }
    } else {
        func_8012C218((void *)a0);
    }
}


extern void func_8012AD80(s32 a0);

void func_8018E730(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x1C);

    if (v1 < 0x28) {
        v1 = v1 + 1;
        *(s32 *)((s32)a0 + 0x1C) = v1;
        if (v1 == 1) {
            return;
        }
        if (*(s16 *)((s32)a0 + 0xA) < -0x800) {
            void *p;

            *(s32 *)((s32)a0 + 0x48) = 0x38000;
            func_8012AD80((s32)a0);

            p = *(void **)((s32)a0 + 0x20);
            *(s16 *)((s32)p + 0x10) -= (*(s32 *)((s32)a0 + 0x18) << 4) >> 16;

            p = *(void **)((s32)a0 + 0x20);
            *(s16 *)((s32)p + 0x14) -= (*(s32 *)((s32)a0 + 0x10) << 4) >> 16;
        }
    } else {
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        *(s16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) - 1;
    }
}




extern Blk20 D_800AE620;
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 VectorNormalSS(void *a0, void *a1);
extern s32 func_8012C750(s32 a0);
extern void RotMatrixY(s32 a0, void *a1);

void func_8018E7E4(arg0, arg1, arg2, arg3, count)
    s32 arg0;
    void *arg1;
    void *arg2;
    void *arg3;
    s16 count;
{
    Blk20 mat;
    u16 vec[3];
    s16 out[3];
    s16 i;
    s32 prim;
    s32 val;

    mat = D_800AE620;
    RotMatrixY(*(s16 *)((s32)arg1 + 0xC), &mat);
    for (i = 0; i < count; i++) {
        vec[0] = *(u16 *)((s32)arg2 + i * 12);
        vec[1] = *(u16 *)((s32)arg2 + i * 12 + 2);
        vec[2] = *(u16 *)((s32)arg2 + i * 12 + 4);
        ApplyMatrixSV(&mat, vec, out);
        *(u16 *)((s32)arg1 + 0) = *(u16 *)((s32)arg0 + 6) + out[0];
        *(u16 *)((s32)arg1 + 2) = *(u16 *)((s32)arg0 + 0xA) + out[1];
        *(u16 *)((s32)arg1 + 4) = *(u16 *)((s32)arg0 + 0xE) + out[2];
        *(u16 *)((s32)arg1 + 0xE) = i;
        prim = func_8012C750((s32)arg1);
        if (prim != 0) {
            out[0] = vec[0] - *(u16 *)((s32)arg3 + 0);
            out[1] = vec[1] - *(u16 *)((s32)arg3 + 2);
            out[2] = vec[2] - *(u16 *)((s32)arg3 + 4);
            VectorNormalSS(out, out);
            ApplyMatrixSV(&mat, out, out);
            val = (out[0] << 9) + (out[0] << 8);
            *(s32 *)(prim + 0x10) = val;
            val = (out[1] << 9) + (out[1] << 8);
            *(s32 *)(prim + 0xDC) = val;
            *(s32 *)(prim + 0x14) = val;
            val = (out[2] << 9) + (out[2] << 8);
            *(s32 *)(prim + 0x18) = val;
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018EA04);

void func_8018EB60(s16 arg0, u16 *arg1, void *arg2, s16 arg3) {
    u8 *s0;
    u32 r;
    s16 rot[3];
    s16 mat[16];
    s16 *m;
    s16 i;
    s32 bound;

    i = 0;
    if (arg0 > 0) {
        m = &mat[0];
        bound = arg0;
        do {
            s0 = func_8012913C(0xA);
            if (s0 != 0) {
                r = rand();
                rot[0] = (r & 0x7F) * 8 + 0xF40;
                rot[1] = arg3 + ((r & 0x7F00) >> 5);
                rot[2] = 0;
                RotMatrixYXZ(rot, m);
                ApplyMatrixSV(m, arg2, rot);
                *(u16 *)(s0 + 6) = arg1[0] + rot[0];
                *(u16 *)(s0 + 0xA) = arg1[1] + rot[1];
                *(u16 *)(s0 + 0xE) = arg1[2] + rot[2];
                *(s32 *)(s0 + 0x10) = rot[0] << 11;
                *(s32 *)(s0 + 0x14) = rot[1] << 11;
                *(s32 *)(s0 + 0x18) = rot[2] << 11;
            }
            i++;
        } while (i < bound);
    }
}



extern void (*D_80196CD4[])(void);

void func_8018ECB8(void *a0) {
    D_80196CD4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_800D387C[];

void func_8018ECF4(s32 arg0) {
    s32 iVar1;

    iVar1 = *(s32 *)(arg0 + 0x20);
    ((void (*)(s32, s32, s32, s32))func_8001CC3C)(iVar1, (s32)&D_800D387C, 0x270, 0x120);
    *(u8 *)(iVar1 + 0x27) = 0x9C;
    *(u16 *)(iVar1 + 0x1A) = 0x7000;
    *(u16 *)(iVar1 + 0x18) = 0x7000;
    *(u8 *)(iVar1 + 0x26) = 0x90;
    *(u8 *)(iVar1 + 0x25) = 0x90;
    *(u8 *)(iVar1 + 0x24) = 0x90;
    *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
    *(s16 *)(arg0 + 0x2C) = 0x46;
    *(s16 *)(arg0 + 0x2) += 1;
}


#include "common.h"

extern void func_8012931C(void *);
extern void func_801292C8(u8 *a0);

void func_8018ED84(s32 arg0) {
    s32 v0;
    s32 s0;
    s32 pad[4];

    v0 = *(u16 *)(arg0 + 0x2C) - 1;
    *(u16 *)(arg0 + 0x2C) = v0;
    s0 = *(s32 *)(arg0 + 0x20);
    if ((s16)v0 == -1) {
        func_801292C8((u8 *)arg0);
        return;
    }
    func_8012931C((void *)arg0);
    v0 = *(u8 *)(s0 + 0x26) - 2;
    *(u8 *)(s0 + 0x26) = v0;
    *(u8 *)(s0 + 0x25) = v0;
    *(u8 *)(s0 + 0x24) = v0;
}



extern void (*D_80196CDC[])(void);

void func_8018EDF8(void *a0) {
    D_80196CDC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B14C(s32 a0, s32 *a1);
extern s32 rand(void);
extern M2C_UNK D_80190C0C;
extern s32 D_80196BBC;
extern u8 D_801D9134[];

void func_8018EE34(s32 param_1)
{
    s32 *pb;
    s32 sp10[3];

    if (*(s32 *)(param_1 + 0x1C) != 0) {
        (*(s32 *)(param_1 + 0x1C))--;
        return;
    }
    pb = &D_80196BBC;
    pb[0] = (s32)&D_801D9134;
    if (func_8012C354(param_1, (s32)(pb - 1)) == 0) {
        return;
    }
    func_8012A828(param_1, (void *)&D_80190C0C);
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0x70) * 0x200;
    func_8012B2CC(param_1);
    sp10[0] = 0;
    sp10[1] = 0xFFF20000;
    sp10[2] = ((rand() & 0xF) + 0x28) * -0x1000;
    func_8012B14C(param_1, sp10);
    *(s32 *)(param_1 + 0x48) = 0x1C000;
    *(u16 *)(param_1 + 0xDC) = (rand() & 0x7F) - 0x40;
    *(s32 *)(param_1 + 0x1C) = 0x12;
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern void func_8012AD80(s32 a0);

void func_8018EF20(void *a0) {
    s32 *p = *(s32 **)((s32)a0 + 0x20);
    s32 t;

    func_8012AD80((s32)a0);
    *(s16 *)((s32)p + 0x14) = *(u16 *)((s32)p + 0x14) + *(u16 *)((s32)a0 + 0xDC);

    t = *(s32 *)((s32)a0 + 0x1C) - 1;
    *(s32 *)((s32)a0 + 0x1C) = t;
    if (t == -1) {
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }
}


extern void func_8012C218(void *a0);
    void func_8018EF90(void) {
        ((void (*)(void))func_8012C218)();
    }



extern void (*D_80196CE8[])(void);

void func_8018EFB0(void *a0) {
    D_80196CE8[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012AD80(s32 a0);
extern void func_8012B14C(s32 a0, s32 *a1);
extern s32 rand(void);

extern M2C_UNK D_80190C0C;
extern s32 D_80196BBC;
extern u8 D_801D91CC[];

void func_8018EFEC(s32 param_1)
{
    register s32 s0 __asm__("$16");
    s32 *pb;
    s32 p;
    s32 t;
    s32 sp10[3];

    if (*(s32 *)(param_1 + 0x1C) != 0) {
        (*(s32 *)(param_1 + 0x1C))--;
        return;
    }
    pb = &D_80196BBC;
    pb[0] = (s32)&D_801D91CC;
    if (func_8012C354(param_1, (s32)(pb - 1)) != 0) {
        func_8012A828(param_1, (void *)&D_80190C0C);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0x70) * 0x200;
        func_8012B2CC(param_1);
        sp10[0] = 0;
        sp10[1] = 0xFFF00000;
        sp10[2] = ((rand() & 0xF) + 0x58) * 0x10000;
        func_8012B14C(param_1, sp10);
        func_8012AD80(param_1);
        p = *(s32 *)(param_1 + 0x20);
        t = *(u16 *)(param_1 + 6);
        *(u16 *)((u8 *)p + 8) = t;
        *(s32 *)((u8 *)p + 0x48) = (s16)t;
        p = *(s32 *)(param_1 + 0x20);
        t = *(u16 *)(param_1 + 0xA);
        *(u16 *)((u8 *)p + 0xA) = t;
        *(s32 *)((u8 *)p + 0x4C) = (s16)t;
        p = *(s32 *)(param_1 + 0x20);
        t = *(u16 *)(param_1 + 0xE);
        *(u16 *)((u8 *)p + 0xC) = t;
        *(s32 *)((u8 *)p + 0x50) = (s16)t;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 1;
        *(s32 *)(param_1 + 0x14) = 0xFFEE0000;
        *(s32 *)(param_1 + 0x48) = 0x1C000;
        *(s32 *)(param_1 + 0x10) >>= 4;
        *(s32 *)(param_1 + 0x18) >>= 4;
        *(u16 *)(param_1 + 0xDC) = (rand() & 0x1FF) - 0x100;
        *(s32 *)(param_1 + 0x1C) = 0x14;
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
    }
}


void func_8018F164(void *a0) {
    s32 *p = *(s32 **)((s32)a0 + 0x20);
    s32 t;

    func_8012AD80((s32)a0);
    *(s16 *)((s32)p + 0x10) = *(u16 *)((s32)p + 0x10) + *(u16 *)((s32)a0 + 0xDC);

    t = *(s32 *)((s32)a0 + 0x1C) - 1;
    *(s32 *)((s32)a0 + 0x1C) = t;
    if (t == -1) {
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }
}


extern void func_8012C218(void *a0);
    void func_8018F1D4(void) {
        ((s32 (*)(void))func_8012C218)();
    }



extern void (*D_80196CF4[])(void);

void func_8018F1F4(void *a0) {
    D_80196CF4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8001C2C4(s32 a0);
extern void func_8018F2C4(s32 a0);

extern s32 D_801270CC;
extern u8 D_80196C24[];

void func_8018F230(void *param_1)
{
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)param_1 + 0x20) = v0;
    if (v0 != 0) {
        func_8001C2C4(v0);
        *(s32 *)((s32)param_1 + 0x58) = (s32)D_80196C24 | 0x10000000;
        *(u16 *)((s32)param_1 + 0x5C) = 0x800;
        func_8018F2C4((s32)param_1);
        *(u16 *)((s32)param_1 + 0xDE) = *(u16 *)(*(s32 *)&D_801270CC + 6);
        *(s16 *)((s32)param_1 + 0xA) = -0x880;
        __asm__ __volatile__("" ::: "memory");
        *(u16 *)((s32)param_1 + 0xDC) = *(u16 *)(*(s32 *)&D_801270CC + 0xE);
        *(u16 *)((s32)param_1 + 2) += 1;
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_8018F2C4);

extern void func_8013C414(void *a0, void *a1);
extern s32 D_8019AA5C;
extern s32 D_801D91D4;

void func_8018F414(void) {
    func_8013C414(&D_8019AA5C, &D_801D91D4);
}


extern void func_8013C414(void *a0, void *a1);
    extern s32 D_8019AA5C;
    extern s32 D_801DA5FC;
    void func_8018F444(void) {
        func_8013C414(&D_8019AA5C, &D_801DA5FC);
    }


extern void func_8013C414(void *a0, void *a1);
    extern s32 D_8019AA5C;
    extern s32 D_801DB658;
    void func_8018F474(void) {
        func_8013C414(&D_8019AA5C, &D_801DB658);
    }


extern void func_8013C414(void *a0, void *a1);
extern s32 D_8019AA5C;

void func_8018F4A4(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801DC180;
    func_8013C414(&D_8019AA5C, &D_801DC180);
}


extern void func_8013C414(void *a0, void *a1);
extern s32 D_8019AA5C;
extern s32 D_801DCD04;

void func_8018F4D4(void) {
    func_8013C414(&D_8019AA5C, &D_801DCD04);
}


extern void func_8013C414(void *a0, void *a1);
extern s32 D_8019AA5C;
extern s32 D_801DD2D4;

void func_8018F504(void) {
    func_8013C414(&D_8019AA5C, &D_801DD2D4);
}


extern void func_8013C414(void *a0, void *a1);
    extern s32 D_8019AA5C;
    extern s32 D_801DDD30;
    void func_8018F534(void) {
        func_8013C414(&D_8019AA5C, &D_801DDD30);
    }



extern void func_8013C414(void *a0, void *a1);
extern s32 D_8019AA5C;

void func_8018F564(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801DE674;
    func_8013C414(&D_8019AA5C, &D_801DE674);
}


extern void func_8013C414(void *a0, void *a1);
    extern s32 D_8019AA5C;
    extern s32 D_801DF3B4;
    void func_8018F594(void) {
        func_8013C414(&D_8019AA5C, &D_801DF3B4);
    }


extern void func_8013C360(void *a0);
    extern s32 D_801D91D4;
    void func_8018F5C4(void) {
        func_8013C360(&D_801D91D4);
    }


extern void func_8013C360(void *a0);
    extern s32 D_801DA5FC;
    void func_8018F5EC(void) {
        func_8013C360(&D_801DA5FC);
    }


extern void func_8013C360(void *a0);
    extern s32 D_801DB658;
    void func_8018F614(void) {
        func_8013C360(&D_801DB658);
    }


extern void func_8013C360(void*);
void func_8018F63C(void) {

    extern s32 D_801DC180;
    ((s32 (*)(s32 *))func_8013C360)(&D_801DC180);
}


extern void func_8013C360(void *a0);
    extern s32 D_801DCD04;
    void func_8018F664(void) {
        func_8013C360(&D_801DCD04);
    }


extern void func_8013C360(void *a0);
    extern s32 D_801DD2D4;
    void func_8018F68C(void) {
        func_8013C360(&D_801DD2D4);
    }


extern void func_8013C360(void *);
    extern s32 D_801DDD30;
    void func_8018F6B4(void) {
        func_8013C360(&D_801DDD30);
    }


extern void func_8013C360(void*);
void func_8018F6DC(void) {

    extern s32 D_801DE674;
    ((s32 (*)(s32 *))func_8013C360)(&D_801DE674);
}


extern void func_8013C360(void*);
void func_8018F704(void) {

    extern s32 D_801DF3B4;
    ((s32 (*)(s32 *))func_8013C360)(&D_801DF3B4);
}


#include "common.h"

/* Fleet-canonical prototypes (ov_SC02_005 house style, per func_8018C6A8 /
 * func_8018CA74 in this same TU): func_8012C1B8 is `void` returning; the
 * value in $v0 is taken via a cast at the call site. */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_80028620(s32, void *);
extern s32 func_800CF854(void);

extern s32 D_800A5E88;
extern s32 D_800A5E8C;
extern s32 D_800A5E90;
extern u8  D_800A5E94;
extern u8  D_800A5E95;
extern u8  D_800A5E96;

extern s32 D_800A5E9C;
extern s32 D_800A5EA0;
extern u8  D_800A5EA4;
extern u8  D_800A5EA5;
extern u8  D_800A5EA6;

extern s32 D_800A5EAC;
extern s32 D_800A5EB0;
extern u8  D_800A5EB4;
extern u8  D_800A5EB5;
extern u8  D_800A5EB6;

void func_8018F72C(void *a0)
{
    s32 v0;
    register s32 *s0 __asm__("$16");
    register s32 s1v __asm__("$17");
    register s32 s2v __asm__("$18");
    register s32 a0v __asm__("$4");
    s32 e9c, eac;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)a0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    *(s16 *)((u8 *)a0 + 0x2) = 1;
    *(u32 *)(*(s32 *)((u8 *)a0 + 0x20) + 0x4) |= 0x80000000;

    __asm__("la %0, D_800A5E88" : "=r"(s0));
    s0[0] = 0;
    D_800A5E8C = 0xA;
    D_800A5E90 = -0xA;
    D_800A5E94 = 0xCC;
    D_800A5E95 = 0x99;
    D_800A5E96 = 0x99;
    func_80028620(0, s0);

    a0v = 1;
    e9c = -0xE;
    __asm__ __volatile__("" ::: "memory");
    s0[4] = 0;
    __asm__ __volatile__("" ::: "memory");
    D_800A5E9C = e9c;
    D_800A5EA0 = -0x8;
    s2v = 0x33;
    D_800A5EA4 = s2v;
    D_800A5EA5 = 0x19;
    s1v = 0x4C;
    D_800A5EA6 = s1v;
    func_80028620(a0v, &s0[4]);

    a0v = 2;
    eac = 0x14;
    __asm__ __volatile__("" ::: "memory");
    s0[8] = 0;
    __asm__ __volatile__("" ::: "memory");
    D_800A5EAC = eac;
    D_800A5EB0 = 0xF;
    D_800A5EB4 = s1v;
    D_800A5EB5 = s2v;
    D_800A5EB6 = 0x7F;
    func_80028620(a0v, &s0[8]);

    if (func_800CF854()) {
        *(s16 *)((u8 *)a0 + 0x2) = 0xA;
    }
}


#include "common.h"

extern void func_80028620(s32, void *);
extern u8 D_80126D6C;
extern s32 D_800A5E90;
extern s32 D_800A5EA0;
extern s32 D_800A5EB0;

void func_8018F894(void *a0) {
    s32 *s0;

    if (D_80126D6C != 3) {
        return;
    }

    s0 = (s32 *)&D_800A5E90;
    *(s16 *)((s32)a0 + 2) = 2;
    *s0 = 10;
    func_80028620(0, (void *)((s32)s0 - 8));

    D_800A5EA0 = 8;
    func_80028620(1, (void *)((s32)s0 + 8));

    D_800A5EB0 = -15;
    func_80028620(2, (void *)((s32)s0 + 0x18));
}


extern s32 D_801270C8;

void func_8018F91C(s32 param_1)
{
    if (D_801270C8 == 8) {
        *(s16 *)(param_1 + 2) = 3;
        *(s32 *)(param_1 + 0x1C) = 0x12;
    }
}


#include "common.h"

extern void func_80028620(s32, void *);
extern s32 D_800A5E88;
extern s32 D_800A5E8C;
extern s32 D_800A5E90;
extern u8 D_800A5E94;
extern u8 D_800A5E95;
extern u8 D_800A5E96;
extern s32 D_800A5EA0;
extern u8 D_800A5EA5;
extern s32 D_800A5EAC;
extern s32 D_800A5EB0;
extern u8 D_800A5EB4;
extern u8 D_800A5EB5;
extern u8 D_800A5EB6;

void func_8018F944(void *a0)
{
    s32 v0;
    s32 eac;
    register s32 *s0 __asm__("$16");
    register s32 a0v __asm__("$4");

    v0 = *(s32 *)((u8 *)a0 + 0x1C) - 1;
    *(s32 *)((u8 *)a0 + 0x1C) = v0;
    if (v0 != 0) {
        return;
    }

    *(s16 *)((u8 *)a0 + 0x2) = 4;
    __asm__("la %0, D_800A5E88" : "=r"(s0));
    s0[0] = 0;
    D_800A5E8C = -4;
    D_800A5E90 = -4;
    D_800A5E94 = 0xFF;
    D_800A5E95 = 0x4C;
    D_800A5E96 = 0;
    func_80028620(0, s0);

    D_800A5EA0 = -0xE;
    D_800A5EA5 = 0;
    func_80028620(1, &s0[4]);

    a0v = 2;
    eac = 0xA;
    __asm__ __volatile__("" ::: "memory");
    s0[8] = 0;
    __asm__ __volatile__("" ::: "memory");
    D_800A5EAC = eac;
    D_800A5EB0 = eac;
    D_800A5EB4 = 0xCC;
    D_800A5EB5 = 0x99;
    D_800A5EB6 = 0x99;
    func_80028620(a0v, &s0[8]);
}


#include "common.h"

extern s32 rand(void);
extern void func_80028620(s32, void *);
extern s32 D_801270C8;
extern s32 D_800A5E88;
extern s32 D_800A5E90;
extern s32 D_800A5EA0;
extern s32 D_800A5EB0;

void func_8018FA34(s32 *a0)
{
    s32 v0;
    s32 *s0;
    s32 *s1;
    /* Pin the 2nd func_80028620's first-arg (0) to its hard call reg so it
     * materializes as a real SET (survives cse/const-prop), and pair it with
     * the zero-byte scheduling barriers below. Without these, gcc-2.7.2's
     * sched1 sinks the independent addr-calc / const-0 arg-setup PAST the
     * rand()-result andi/addiu chain (S2-adjacent "class3 tie" residual,
     * cookbook §25 / gcc-2.7.2-map/sched.md S1/S6); the target schedules
     * each independent op BEFORE the dependent chain that follows it. */
    register s32 a0v __asm__("$4");

    s1 = a0;
    v0 = rand();
    s0 = (s32 *)&D_800A5E88;
    __asm__ __volatile__("" ::: "memory");
    v0 &= 0x1F;
    v0 -= 0x10;
    s0[0] = v0;

    v0 = rand();
    a0v = 0;
    __asm__ __volatile__("" ::: "memory");
    v0 &= 0x1F;
    v0 -= 0x14;
    D_800A5E90 = v0;

    func_80028620(a0v, s0);

    if (D_801270C8 != 0xA) {
        return;
    }

    *(s16 *)((u8 *)s1 + 0x2) = 0x5;
    D_800A5EA0 = 0xE;
    func_80028620(1, &s0[4]);

    D_800A5EB0 = -0xA;
    func_80028620(2, &s0[8]);
}


#include "common.h"

extern void func_80028620(s32, void *);
extern s32 D_801270C8;
extern s32 D_800A5E88;
extern s32 D_800A5E90;
extern s32 D_800A5EA0;
extern s32 D_800A5EB0;

void func_8018FAE0(s32 a0) {
    register s32 *s0 __asm__("$16");
    register s32 *s1 __asm__("$17");
    s32 v0;

    s1 = (s32 *)a0;
    s0 = &D_800A5E88;

    v0 = rand();
    s0[0] = (v0 & 0x1F) - 0x10;

    v0 = rand();
    D_800A5E90 = (v0 & 0x1F) - 0xC;

    func_80028620(0, s0);

    if (D_801270C8 == 0xB) {
        *(s16 *)((u8 *)s1 + 2) = 6;
        D_800A5EA0 = -0xE;
        func_80028620(1, (void *)((u8 *)s0 + 0x10));
        D_800A5EB0 = 0xA;
        func_80028620(2, (void *)((u8 *)s0 + 0x20));
    }
}


#include "common.h"

extern s32 rand(void);
extern void func_80028620(s32, void *);
extern s32 D_801270C8;
extern s32 D_800A5E88;
extern s32 D_800A5E90;
extern s32 D_800A5EA0;
extern s32 D_800A5EB0;

void func_8018FB8C(void *a0) {
    register s32 *s0 __asm__("s0");
    register s32 a0v __asm__("a0");
    s32 *s1 = (s32 *)a0;
    s32 tmp;

    tmp = rand();
    s0 = (volatile s32 *)&D_800A5E88;
    tmp = (tmp & 0x1F) - 0x10;
    s0[0] = tmp;
    tmp = rand();
    __asm__("addu %0,$zero,$zero" : "=r"(a0v));
    tmp = (tmp & 0x1F) - 0x14;
    D_800A5E90 = tmp;

    func_80028620(a0v, s0);

    if (D_801270C8 == 0xC) {
        *(s16 *)((s8 *)s1 + 2) = 0x7;
        D_800A5EA0 = 0xE;
        func_80028620(1, (void *)((s32)s0 + 0x10));
        __asm__("" : "=r"(s0) : "0"(s0));
        D_800A5EB0 = -0xA;
        func_80028620(2, (void *)((s32)s0 + 0x20));
    }
}


#include "common.h"

/* Tag renamed per the project convention (src/shared/engine_types.h already carries
 * struct B16_801856E4, B16_80185794, ...): the destination TU pulls in engine_types.h,
 * which defines `struct B16 { s32 w[4]; };` at line 295, so a file-scope `struct B16`
 * contributed by this draft is a hard "redefinition of `struct B16'" at cc1.  A unique
 * per-function tag is the sanctioned spelling. */
struct B16_8018FC38 { s32 w[4]; };

/* §183 TYPE-adopted-TU: the destination TU already declares this symbol
 * `extern s32 D_800A5E88;` at file scope ABOVE this insertion offset (the
 * func_8018FA34 / func_8018FAE0 / func_8018FB8C group all spell it that way), so
 * the TU's spelling is adopted verbatim here and the 16-byte view is applied by a
 * cast AT THE USE SITE.  `&D_800A5E88` is unchanged by the move, so §183.3's
 * scalar-vs-array base-register trap does not apply — verified MATCH 43/43. */
extern s32 D_800A5E88;
extern s32 D_800A5E90;
extern s32 D_800A5EA0;
extern s32 D_800A5EB0;
extern void func_80028620(s32, void *);
extern u8 D_80126D6C;

void func_8018FC38(s32 a0) {
    s32 s1 = a0;
    struct B16_8018FC38 *s0;
    s32 v0;

    v0 = rand();
    s0 = (struct B16_8018FC38 *)&D_800A5E88;
    v0 = (v0 & 0x1F) - 0x10;
    s0->w[0] = v0;
    v0 = rand();

    a0 = 0;
    v0 = (v0 & 0x1F) - 0xC;
    D_800A5E90 = v0;
    __asm__("" : "=r"(a0) : "0"(a0));

    func_80028620(a0, s0);
    __asm__("" : "=r"(s0) : "0"(s0));

    if (D_80126D6C == 0xD) {
        *(s16*)(s1 + 0x2) = 0x8;
        D_800A5EA0 = -0xE;
        func_80028620(1, &s0[1]);

        D_800A5EB0 = 0xA;
        func_80028620(2, &s0[2]);
    }
}


#include "common.h"

extern s32 rand(void);
extern void func_80028620(s32, void *);
extern s32 D_801270C8;
extern s32 D_800A5E88;
extern s32 D_800A5E8C;
extern s32 D_800A5E90;
extern u8  D_800A5E94;
extern u8  D_800A5E95;
extern u8  D_800A5E96;
extern s32 D_800A5EA0;
extern u8  D_800A5EA5;
extern s32 D_800A5EAC;
extern s32 D_800A5EB0;
extern u8  D_800A5EB4;
extern u8  D_800A5EB5;
extern u8  D_800A5EB6;

void func_8018FCE4(void *a0)
{
    void *s1;
    s32 *s0;
    s32 v0;
    s32 eac;
    register s32 a0v __asm__("$4");

    s1 = a0;
    v0 = rand();
    s0 = (s32 *)&D_800A5E88;
    __asm__ __volatile__("" ::: "memory");
    v0 = (v0 & 0x1F) - 0x10;
    s0[0] = v0;

    v0 = rand();
    a0v = 0;
    __asm__ __volatile__("" ::: "memory");
    v0 = (v0 & 0x1F) - 0x14;
    D_800A5E90 = v0;

    func_80028620(a0v, s0);

    if (D_801270C8 == 0xD) {
        *(s16 *)((u8 *)s1 + 2) = 9;
        s0[0] = 0;
        D_800A5E8C = 0xA;
        D_800A5E90 = -0xA;
        D_800A5E94 = 0xCC;
        D_800A5E95 = 0x99;
        D_800A5E96 = 0x99;
        func_80028620(0, s0);

        D_800A5EA0 = -8;
        D_800A5EA5 = 0x19;
        func_80028620(1, &s0[4]);

        a0v = 2;
        eac = 0x14;
        __asm__ __volatile__("" ::: "memory");
        __asm__("" : "=r"(s0) : "0"(s0));
        s0[8] = 0;
        __asm__ __volatile__("" ::: "memory");
        D_800A5EAC = eac;
        D_800A5EB0 = 0xF;
        D_800A5EB4 = 0x4C;
        D_800A5EB5 = 0x33;
        D_800A5EB6 = 0x7F;
        func_80028620(a0v, &s0[8]);
    }
}


#include "common.h"

extern void func_80028620(s32, void *);
extern u8 D_80126D6C;
extern s32 D_800A5E90;
extern s32 D_800A5EA0;
extern s32 D_800A5EB0;

void func_8018FE18(void *a0) {
    if (D_80126D6C == 0x11) {
        s32 *s0 = &D_800A5E90;

        *(s16 *)((s32)a0 + 0x2) = 0xA;
        *s0 = 0xA;
        func_80028620(0, (void *)((s32)s0 - 0x8));

        D_800A5EA0 = 0x8;
        func_80028620(1, (void *)((s32)s0 + 0x8));

        D_800A5EB0 = -0xF;
        func_80028620(2, (void *)((s32)s0 + 0x18));
    }
}


#include "common.h"

extern s32 D_801270C8;

extern s32 D_800A5E88;
extern s32 D_800A5E8C;
extern s32 D_800A5E90;
extern u8  D_800A5E94;
extern u8  D_800A5E95;
extern u8  D_800A5E96;

extern s32 D_800A5E9C;
extern s32 D_800A5EA0;
extern u8  D_800A5EA4;
extern u8  D_800A5EA5;
extern u8  D_800A5EA6;

extern s32 D_800A5EAC;
extern s32 D_800A5EB0;
extern u8  D_800A5EB4;
extern u8  D_800A5EB5;
extern u8  D_800A5EB6;

extern void func_80028620(s32, void *);

void func_8018FEA0(void *a0)
{
    register s32 *s0 __asm__("$16");
    register s32 s1v __asm__("$17");
    register s32 s2v __asm__("$18");
    register s32 s3v __asm__("$19");
    register s32 a0v __asm__("$4");
    s32 eb0;

    if (D_801270C8 >= 0x14) {
        a0v = 0;
        __asm__("la %0, D_800A5E88" : "=r"(s0));

        *(s16 *)((u8 *)a0 + 0x2) = 0xB;

        s3v = 0x16;
        s0[0] = 0;
        D_800A5E8C = s3v;
        D_800A5E90 = 0;
        D_800A5E94 = 0xB2;
        D_800A5E95 = 0x66;
        s1v = 0x33;
        D_800A5E96 = s1v;
        func_80028620(a0v, s0);

        a0v = 1;
        s0[4] = 0;
        D_800A5E9C = -0xE;
        D_800A5EA0 = -0xE;
        D_800A5EA4 = s1v;
        D_800A5EA5 = 0;
        s2v = 0x4C;
        D_800A5EA6 = s2v;
        func_80028620(a0v, &s0[4]);

        a0v = 2;
        eb0 = 0xF;
        __asm__ __volatile__("" ::: "memory");
        s0[8] = 0;
        __asm__ __volatile__("" ::: "memory");
        D_800A5EB0 = eb0;
        D_800A5EAC = s3v;
        D_800A5EB4 = s2v;
        D_800A5EB5 = s1v;
        D_800A5EB6 = 0x7F;
        func_80028620(a0v, &s0[8]);
    }
}


#include "common.h"

extern void func_80028620(s32, void *);
extern s32 D_801270C8;
extern u8 D_800A5E94;
extern u8 D_800A5E96;
extern s32 D_800A5E9C;
extern s32 D_800A5EA0;
extern s32 D_800A5EAC;
extern s32 D_800A5EB0;

void func_8018FFC4(void *a0) {
    u8 *s0;

    if (D_801270C8 != 0x1B) {
        return;
    }

    s0 = &D_800A5E94;
    *(s16 *)((s32)a0 + 2) = 0xC;
    *s0 = 0xFF;
    D_800A5E96 = 0;
    func_80028620(0, (void *)((s32)s0 - 0xC));

    D_800A5E9C = 0;
    D_800A5EA0 = -0x18;
    func_80028620(1, (void *)((s32)s0 + 4));

    D_800A5EAC = 0xB;
    D_800A5EB0 = 0x1C;
    func_80028620(2, (void *)((s32)s0 + 0x14));
}


void func_80190068(s32 *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0xC;
    }



extern void (*D_80196CFC[])(void);

void func_80190074(void *a0) {
    D_80196CFC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_800CF854(void);

s32 func_801900B0(void) {
    register s32 r __asm__("$2");
    s32 v;

    v = ((s32 (*)(void))func_800CF854)();
    r = v ? 9 : 8;
    return r;
}



extern s32 D_801E4C40;

void func_801900E0(void) {
    D_801E4C40 = 1280;
}



extern s32 D_801E4C40;

void func_801900F4(void) {
    D_801E4C40 = 3796;
}



extern void (*D_80196EA4[])(void);

void func_80190108(void *a0) {
    D_80196EA4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"


extern void func_801465C0(void);
extern void func_80146C3C(void);

extern void func_8001CBDC(s32 a0, s32 a1, s32 a2, s32 a3);

extern s16 D_80196D30[][2];
extern u8 D_80196D5C[];
extern EffectSlot4 D_80196D68[];
extern u8 D_80196D94[];

extern EffectSlot4 D_80196DCC;
extern EffectSlot4 D_80196DF4;
extern EffectSlot4 D_80196DF8;
extern EffectSlot4 D_80196E28;
extern EffectSlot4 D_80196E2C;
extern EffectSlot4 D_80196E5C;
extern EffectSlot4 D_80196E60;
extern EffectSlot4 D_80196E90;
extern EffectSlot4 D_80196E94;

void func_80190144(void *a0) {
    register void *s0 __asm__("$16");
    register void *s1 __asm__("$17");

    s0 = a0;
    s1 = ((void *(*)(void))func_801465C0)();
    if (s1 != 0) {
        s32 idx;
        u8 uVar1;

        *(s32 *)((s32)s0 + 0x20) = (s32)s1;
        idx = *(s32 *)((s32)s0 + 0x2C);
        func_8001CBDC((s32)s1, (s32)D_80196D94, D_80196D30[idx][0], D_80196D30[idx][1]);
        uVar1 = D_80196D5C[*(s32 *)((s32)s0 + 0x2C)];
        *(s16 *)((s32)s1 + 0x2C) = 3;
        *(u8 *)((s32)s1 + 0x27) = uVar1;
        *(s16 *)((s32)s0 + 0x6) = 0;
        *(s16 *)((s32)s0 + 0xA) = 0x50;

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
           neighbouring symbol (idiom 7): `&D_80196E90 + 4 == &D_80196E94`, a
           CSE-distinct rtx, so the next copy still recomputes its source
           address. Both spellings relocate to 0x80196E94. */
#define COND (*(s32 *)((s32)s0 + 0x2C) > 0)
        *(EffectSlot4 *)((s32)&D_80196E90 + 4) = D_80196D68[*(s32 *)((s32)s0 + 0x2C)];
        if (COND) { D_80196E90 = D_80196E94; } else { D_80196E90 = D_80196E94; }
        if (COND) { D_80196E60 = D_80196E90; } else { D_80196E60 = D_80196E90; }
        if (COND) { D_80196E5C = D_80196E60; } else { D_80196E5C = D_80196E60; }
        if (COND) { D_80196E2C = D_80196E5C; } else { D_80196E2C = D_80196E5C; }
        if (COND) { D_80196E28 = D_80196E2C; } else { D_80196E28 = D_80196E2C; }
        if (COND) { D_80196DF8 = D_80196E28; } else { D_80196DF8 = D_80196E28; }
#undef COND
        D_80196DF4 = D_80196DF8;
        D_80196DCC = D_80196DF4;

        *(s16 *)((s32)s0 + 0x2) = *(s16 *)((s32)s0 + 0x2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(s0);
    }
}


extern void func_80190384(void);
    void func_80190344(void) {
        func_80190384();
    }


extern void func_80146C3C(void);
    void func_80190364(void) {
        func_80146C3C();
    }


#include "common.h"

extern void func_80017254(void *a0);
extern void func_800176F0(void *a0);
extern u8 D_80196DAC[];
extern u8 D_80196DD4[];

void func_80190384(void) {
    u8 *p;
    s32 i;

    func_80017254(D_80196DAC);
    i = 0;
    p = D_80196DD4;
    do {
        func_800176F0(p);
        i++;
        p += 0x34;
    } while (i < 4);
}


extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
    void func_801903DC(void *arg0) {
        ((void (*)(s32, s32, s32, s32))func_80146994)(0x28, 0, arg0, 0);
    }


#include "common.h"

extern s32 D_80126B58;
extern s32 func_8014C050(s32 a0, s32 a1);

void func_80190408(void) {
    s32 t;

    t = func_8014C050((s32)&D_80126B58, 0x28);
    if (t != 0) {
        *(u16 *)(t + 2) += 1;
    }
}



extern void (*D_80196F00[])(void);

void func_8019044C(void *a0) {
    D_80196F00[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_801904B8(s32 arg);
    extern void func_80146CA0(void *a0);
    void func_80190488(s32 arg0) {
        func_801904B8(arg0);
        ((void (*)(s32))func_80146CA0)(arg0);
    }


#include "common.h"

extern void func_80019064(void *a0);
extern int func_801511E0(int arg);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80149020(s32 *a0);
extern void func_80147324(s32 arg0);
extern void func_80146CA0(void *a0);
extern s32 D_80062C14;
extern s32 D_80196EB0;

s32 func_801904B8(s32 arg) {
    s32 *s0 = (s32 *)arg;

    func_80019064(&D_80062C14);
    func_801511E0((int)s0);
    func_80154274(s0, (s32)&D_80196EB0);
    ((s32 *)s0)[0x8d] = 0;
    func_80154A74((s32)s0, 0x1c);
    func_801477E8(s0, 0xffe00000);
    func_80149020(s0);
    func_80147324(0x451);
    func_80146CA0(s0);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_80181D30", func_80190538);

extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80151664(void);

void func_8019084C(s32 a0)
{
    s32 s0 = a0;

    func_8014BC44(s0, *(s16 *)(s0 + 0xF2));
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    *(u8 *)(s0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(s0);
}







