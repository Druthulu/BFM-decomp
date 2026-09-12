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
typedef struct { u32 w0, w1, w2; } PrimC59C;
typedef struct { u8 *vtx; u32 f4; u32 xx, yy, zz; PrimC59C *prim, *end; } CellC59C;
typedef struct { s16 vx, vy; } DVEC2_C59C;
typedef struct { s16 vx, vy, vz, pad; } SVEC2_C59C;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0, x1, y1, x2, y2; } PF3_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0, x1, y1, x2, y2, x3, y3; } PF4_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1; s16 x2, y2; u16 uv2, p2; } PFT3_C59C;
typedef struct { u32 tag, rgbc; s16 x0, y0; u32 uvc0; s16 x1, y1; u32 uvp1; s16 x2, y2; u16 uv2, p2; s16 x3, y3; u16 uv3, p3; } PFT4_C59C;
typedef struct { char c[8]; } Blk8_8017DCF4;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8017DE40;
typedef struct { s16 a, b, c, d; } SV4_8017DE40;
typedef struct { s16 vx, vy, vz, pad; } SVEC_E83C;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8017EA48;
typedef struct { s16 a, b, c, d; } SV4_8017EA48;
typedef struct { s16 a, b, c, d; } SV4_FC6C;
typedef struct { s16 vx, vy, vz, pad; } SVEC_80064;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_8018256C;  /* 0x20 */
typedef struct { s16 a, b, c, d; } SV4_8018256C;
typedef struct { s16 a, b, c, d; } SV4_801836B8;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_801836B8;
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80189910;
extern u8 D_80189880;
extern u8 D_8018985C;
extern u8 D_80189838;
extern u8 D_801898EC;
extern u8 D_801898C8;
extern u8 D_801898A4;
extern u8 D_80189814;
extern void func_80145934(void);
extern u8 D_801899A0;
extern u8 D_8018997C;
extern u8 D_80189958;
extern u8 D_80189934;
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
extern unsigned char D_80188D98[];
extern unsigned char D_80188DC8[];
extern unsigned char D_80188E18[];
extern unsigned char D_80188E48[];
extern unsigned char D_80188E78[];
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
extern void (*D_80188EC8[])(void *);
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
extern u8 func_80014DC0(u32 a0);
extern u16 func_80014D68(u32 a0);
extern s32 func_80014D94(s32 a0);
extern u8 func_80014CF8(u32 a0, u32 a1);
extern void func_800120DC(u16 *arg0, u16 *arg1);
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
extern void func_801577C8(s32 arg0);
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
extern s32 D_80188F90[];
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
extern u8 D_80189018[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80189020;
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
extern int D_801E8B30;
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
extern s32 D_801E8B34;
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
extern s32 D_80189050;
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
extern s32 func_80151944(void *a0);
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
extern void (*D_801890F8[])(void);
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
extern void (*D_8018911C[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018910C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80189130[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018913C[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018914C[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80189164[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80189154;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80189178[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80189194[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80189184;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801891A8[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801891BC[])(void);
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
extern s32 D_801891D0;
extern void (*D_801891F8[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801891D8;
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
extern int (*D_80189244[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80189248[])(void);
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
extern unsigned short D_801896AC[];
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
extern void (*D_801896BC[])(void);
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
extern int D_801E8B68;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_801896E4[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_801896C4;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_801896D4;
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
extern void (*D_80189724[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018972C[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_801896F8;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80189738[])(void);
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
extern u8 D_80189708;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801E8B70;
extern s32 D_801E8B7C;
extern s32 D_801E8B80;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80189774[])(s32 *);
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
extern s32 D_80189748[];
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
extern s32 D_801E8B78;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_801899C4[])(void);
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
extern char D_801897E4[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80189A68[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80189BBC[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_801899D8;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80189BC4[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_801899E8;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80189A08;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80189BCC[])(void);
extern void func_8015ADB0(s32);
extern void func_8015AD78(s32 a0);
extern void func_8015ADB0(s32 arg0);
extern s32 D_800D4A9C;
extern int func_8015B6F4(int param_1);
extern u8 D_800D4F8C[];
extern s32 func_8015B7B4(s32 a0);
extern u8 D_800D4BE0[];
extern s32 func_8014A51C(int param_1);
extern s32 func_8015B858(u8 *a0);
extern s32 D_800D4B48;
extern void func_8015B8F8(s32 *a0);
extern void func_8015BD8C(s32 *a0);
extern s32 func_8015BE94();
extern void func_8015BE38(struct Obj *a0);
extern s32 func_8015BE74(void);
extern void func_80161124(void *a0);
extern s32 func_8015BE94(s32 *a0);
extern s32 func_8015AE2C(s32 arg0);
extern s32 func_8015BEC4(void);
extern s32 func_8015B950(s32 arg0);
extern s32 func_8015BEE4(void);
extern void func_8015BF04(s32 *a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015BFF4(void *a0);
extern void func_8015BF7C(s32 *a0);
extern void func_8015C030(s32 *a0, s32 a1);
extern void func_8015BFB0(s32 *a0, s32 a1);
extern void (*D_80189BF4[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80189C00[])(void);
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
extern void func_8015D01C(int param_1);
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0(s32 *a0);
extern void func_8015CF8C(s32 *a0);
extern void func_8015CFFC(void);
extern void func_8015D01C(int param_1);
extern void (*D_80189A74[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80189CA4;
extern void func_8015D380(s32 a0);
extern unsigned char D_80188D88[];
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
extern unsigned char D_80189CB8[];
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
extern s8 D_80189CF4[];
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
extern u16 D_80189D3C;
extern u16 D_80189D3E;
extern u16 D_80189D40;
extern s32 D_80189D44;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80189D4C;
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
extern int D_80189A58;
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
extern unsigned int D_80189DD0[];
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
extern void func_80160EA4(void *a0);
extern void func_80160E70(s32 *a0);
extern void (*D_80189E80[])(void);
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
extern void func_801483E8(unsigned char *self);
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
extern int func_801497A8(s32 *a0);
extern int func_80161BE0(void *param_1);
extern u16 D_80189EB0[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80189F14;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801E8B88[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80189F38[])(void);
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
extern int D_801E8BE0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80189F80[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80189F70;
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
extern char D_801E83A8[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80189F88[])(void);
extern void func_80163A58(void *a0);
extern void func_80163A94(s32 param_1);
extern void func_80163C2C(s32 param_1);
extern void func_80163EC8(s32 param_1);
extern void func_80164270(s32 *a0);
extern void func_80164418(s32 s0);
extern void func_80163764(s32 a0);
extern void func_801642AC(s32 a0);
extern void func_8016432C(s32 a0);
extern void func_80164410(void);
extern s32 func_80012DBC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164530(s32 arg0);
extern void (*D_80189FDC[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80189FA4;
extern s16 D_80189FD8;
extern s16 D_80189FD6;
extern s16 D_80189FD4;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80189FE8[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E8C40;
extern u8 D_801E8C41;
extern u8 D_801E8C42;
extern u8 D_801E8C43;
extern u8 D_801E8C44;
extern u8 D_801E8C45;
extern u8 D_801E8C46;
extern u8 D_801E8C47;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80189FF8[])(void);
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
extern s32 D_801E8C80;
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
extern void (*D_8018A03C[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018A0B8[];
extern s32 D_8018A0D8[];
extern u8 D_8018A154[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018A174[];
extern u8 D_8018A194[];
extern void func_800CAF6C(s32 *a0);
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
extern void (*D_8018A230[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018A2AC[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801E83B8;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018A2B8[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018A2C0[])(void);
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
extern void (*D_8018A388[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018A398[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994(s32 param_1, int param_2, int param_3, int param_4);
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018A3A8[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018A3B4[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018A314[];
extern u8   D_8018A328[];
extern s32 func_80167DBC(s32 arg0, s32 arg1, s32 arg2);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern void func_80168070(s32 param_1, s16 *param_2, s16 *param_3, void *param_4);
extern s32 func_80166994(s32 param_1, int param_2, int param_3, int param_4);
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
extern void (*D_8018A3CC[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018A3D4[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018A3DC[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018A3E4[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018A3EC[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018A3F4[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018A3FC[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018A4B0[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018A4B8[])(void);
extern void func_80169F00(void *a0);
extern char D_8018A468[];
extern char D_8018A428[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018A4F0[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018A4FC[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018A544[])(void);
extern void func_8016AB30(void *a0);
extern void func_8016B234(s32 param_1);
extern void func_8016AFB0(s32 a0);
extern void func_8016B114(void *arg0);
extern s32 func_8016B448(s32, s32);
extern s32 func_8016BA48(s32 a0);
extern void func_8016B3F4(s32 a0);
extern s32 func_8016B428(s32 a0);
extern void func_8016B984(void *a0);
extern s32 func_8016B448(s32 arg0, s32 arg1);
extern void (*D_8018A5C0[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E8FA0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018A5B4[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018A5F8[];
extern unsigned short D_8018A600[];
extern unsigned short D_8018A608[];
extern unsigned char D_801E8FA8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E8FA0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018A610[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E90DC;
extern M2C_UNK D_801E90E0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E9068;
extern void (*D_8018A640[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E90E4[];
extern u8 D_801E90EC[];
extern u8 D_801E909C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018A648[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018A664[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018A66C[])(void);
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
extern void (*D_8018A6D4[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018A678;
extern u8 D_8018A684;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018A708[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018A710[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018A764[])(void);
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
extern u16 D_8018A798[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018A788[];
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
extern s32 D_8018A7B4;
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
extern void (*D_8018A82C[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018A834[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018A83C[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018A844[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018A84C[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018A854[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018A860[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018A86C[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018A878[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018A888[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018A898[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018A8A0[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018A8A8[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018A8B0[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018A8B8[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018A8C0[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018A8C8[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018A8D0[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018A8D8[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018A8E0[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018A8E8[])(void);
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
extern void (*D_8018A8F0[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018A8F8[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018A900[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018A908[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018A910[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018A918[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018A920[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018A928[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018A930[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018A938[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018A940[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018A948[])(void);
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
extern void (*D_8018A98C[])(void);
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
extern M2C_UNK D_8018A950;
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
extern void (*D_8018A9BC[])(void);
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
extern void (*D_8018A9F8[])(void);
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
extern void (*D_8018AA50[])();
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
extern void func_80175184(s32* arg0);
extern void func_80175114(s32 *a0);
extern void func_80175184(s32* arg0);
extern void func_80175150(s32 *a0);
extern void (*D_8018AA60[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018AA68[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_8018ABD0[])();
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
extern void (*D_8018ABDC[])();
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
extern M2C_UNK D_801E8600;
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
extern void func_80178840(int param_1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_801789AC(s32 arg0);
extern s16 D_801EB250;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801E9820;
extern short D_801EB2C4;
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
extern s32 D_801E9C4C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E9C74;
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
extern s16 D_801E9C30;
extern s32 func_8017A3B0(void);
extern short D_801E9C6C;
extern short D_801E9C68;
extern int func_800D0CA0(int);
extern int func_8001AAA0(s32 arg0);
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
extern s16 D_801EB220;
extern s16 D_801EB222;
extern s16 D_801EB22C;
extern void func_8017AE2C(s32 param_1);
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801E9C34;
extern u16 D_801E9CB4;
extern u16 D_801E9CB6;
extern u16 D_801E9CB8;
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
extern s16 D_801E9CAC;
extern s16 D_801E9CAE;
extern s16 D_801E9CB0;
extern s16 D_801E9CA4;
extern s16 D_801E9CA6;
extern s16 D_801E9CA8;
extern void func_8017B7A8(void);
extern s16 D_801E9CC4;
extern s16 D_801E9CC6;
extern s16 D_801E9CC8;
extern s16 D_801E9CCC;
extern s16 D_801E9CCE;
extern s16 D_801E9CD0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801E9CBC;
extern short D_801E9CBE;
extern short D_801E9CC0;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801E9C54;
extern SV4 D_801E9C5C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801E9C7C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801E9C78)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018ADB8[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void ReadRotMatrix(void *a0);
extern void PushMatrix(void);
extern void func_8004974C(void *a0, void *a1);
extern void PopMatrix(void);
extern void func_8017C294(u16 *a0, void *a1);
extern int func_8017C338(short *param_1, short *param_2, short *param_3, int param_4);
extern void ReadGeomOffset(s32 *a0, s32 *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8004921C(s32 a0, s32 a1);
extern void func_8017C530(s32 a0, s32 a1);
extern void func_8017C59C(s32 arg0);
extern void func_8017D4C4();
extern void func_8017D468(s32 a0);
extern s32 D_8018CE04;
extern void func_8017D4C4(void);
extern s32 D_8018CEA4;
extern void func_8017D4EC(void);
extern s32 D_8018CF30;
extern void func_8017D514(void);
extern s32 D_8018CFA8;
extern void func_8017D53C(s32 param_1);
extern s32 D_8018D048;
extern void func_8017D564(void *a0);
extern s32 D_8018D0C0;
extern void func_8017D58C(void);
extern s32 D_8018D160;
extern void func_8017D5B4(s32 a0);
extern s32 D_8018D200;
extern void func_8017D5DC(void);
extern s32 D_8018D2B4;
extern void func_8017D604(s32 arg0);
extern s32 D_8018D340;
extern void func_8017D62C(s32 arg0);
extern s32 D_8018D3CC;
extern void func_8017D654(s32 a0);
extern s32 D_8018D480;
extern void func_8017D67C(s32 *a0);
extern s32 D_8018D50C;
extern void func_8017D6A4(void *a0);
extern s32 D_8018D598;
extern void func_8017D6CC(void);
extern void func_8017D6F4(void);
extern void func_8017D740(void);
extern void func_8017D7E4(void);
extern s32 D_8018CAA8;
extern void func_8017D7EC(s32 param_1);
extern s32 D_8018CB84;
extern void func_8017D814(void *param_1);
extern s32 D_8018CCC4;
extern void func_8017D83C(s32 arg0);
extern void (*D_8018BBCC[])(void);
extern void func_8017D864(void *a0);
extern void func_8017DBB4(void);
extern s32 func_8017D8A0(s32 a0);
extern s32 func_8017D8E4(void);
extern void (*D_8018BBD4[])(void);
extern void func_8017D908(void *a0);
extern void func_800D1E28(void);
extern s32 func_80183F7C(void);
extern void func_8001BFD0(void);
extern s32 func_8017D944(u8 *a0);
extern void (*D_8018BBE0[])(void);
extern void func_8017D9D0(void *a0);
extern s32 func_8017DA0C(u8 *a0);
extern void (*D_8018BBEC[])(void);
extern void func_8017DA9C(void *a0);
extern void func_8017DBDC(void);
extern s32 func_8017DAD8(s32 a0);
extern s32 func_8017DB18(u8 *a0);
extern void func_800D1EBC(void);
extern void func_8017DB94(s32 a0);
extern s16 D_801274E8;
extern s16 D_8018BC30;
extern void func_8017DCF4(void);
extern void func_8017DD44(void);
extern void (*D_8018BC38[])(void);
extern void func_8017DDE4(void *a0);
extern void func_8017DE40(s32 param_1);
extern void func_8017DE20(void *a0);
extern s16 D_8018BC3C[];
extern s16 D_80126940;
extern s16 D_80126942;
extern s16 D_80126944;
extern s16 D_801274EC;
extern void func_8017DE40(s32 param_1);
extern void (*D_8018BD14[])(void);
extern void func_8017E0B4(void *a0);
extern s32 func_8017EF1C(s32 a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern u16 D_801274E4[];
extern u8 D_8018BC50[];
extern u8 D_8018BC84[];
extern short D_801BB024;
extern void func_8017E124(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8017E218(s32 s0);
extern void func_8012A828(s32, void*);
extern void func_8017E294(void * arg0);
extern s32 func_8017EE50(s32 arg0);
extern void func_8017E2C0(s32 a0);
extern s32 func_8012BEE8(s32 arg);
extern void func_8017E33C(void *a0);
extern void func_8012B23C(s32 a0);
extern s32 func_8017EA04(s32);
extern s32 D_801BB0FC;
extern void func_8017E370(void *a0);
extern s32 func_8017EA48(s32);
extern void func_8017EC90(s32 a0, s32 a1);
extern s32 func_8017E83C(s32 a0);
extern s32 func_8012E778(s32 a0, s32 a1);
extern void func_8017E3C0(void *a0);
extern void func_8017E4C8(s32 param_1);
extern void func_8017E56C(s32 *a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8017E57C(s32 param_1);
extern u8 D_801BB2BC[];
extern s32 func_8012BCCC(s32 a0);
extern void func_8017E654(s32 param_1);
extern void func_8017E730(void *a0);
extern void func_8017E748(void *arg0);
extern void func_8018732C(s32 a0, u16 *a1, s16 a2);
extern void func_8017E750(s32 a0);
extern void func_8017E7B4(int param_1);
extern void func_8012CBA4(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern s32  func_8012BC60(void *a0, void *a1);
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32  func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern s32 func_8017E83C(s32 arg0);
extern s32 func_8017EA04(s32 arg0);
extern MTX_8017EA48 D_800AE620;
extern SV4_8017EA48 D_8018BD34[];
extern s32 D_801270C8[];
extern s16 D_80126B98;
extern s16 D_80126B9A;
extern void RotMatrixY(s32 a0, void *a1);
extern s32 func_8017EF68(void);
extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);
extern s32 func_8017EA48(s32 param_1);
extern void func_8002A04C(s32 a0);
extern void func_8012C098(void *param_1);
extern void func_8017EE20(s32 arg0);
extern s32 func_8017EE50(s32 arg0);
extern s32 func_8012B864(s32 a0);
extern s32 func_8017EEA4(s32 a0);
extern void (*D_8018BEF0[])(void);
extern void func_8017EF98(void *a0);
extern s32 func_80180454(s32 a0);
extern u8 D_8018BD54[];
extern u8 D_8018BE58[];
extern u8 D_801BE488[];
extern void func_8017EFD4(s32 a0);
extern void func_8017F0C8(s32 s0);
extern void func_8017F164(s32 param_1);
extern s32 func_801802A4(s32 a0);
extern void func_8017F1F8(s32 a0);
extern void func_8017F258(void *a0);
extern s32 func_80180064(s32 arg0, s32 arg1);
extern void func_8018022C(s32 a0);
extern void func_8017F2B4(s32 a0);
extern void func_8017F414(void *a0);
extern s32 func_80143BDC(u16 *a0);
extern void func_8017FE04(s32 a0);
extern void func_8017F444(s32 param_1);
extern u8 D_801BE658[];
extern void func_8017F658(void *a0);
extern s32 D_801BE580;
extern s32 func_80180064(s32 a0, s32 a1);
extern void func_8017F8AC(s32 a0);
extern void func_8017F920(s32 param_1);
extern void func_8017F95C(s32 a0);
extern u8 D_8018BF30[];
extern u8 D_8018BF3C[];
extern u8 D_801BEC20[];
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8017F99C(s32 param_1);
extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8012CC64(s32 a0, s32 a1);
extern u8 D_8018BF48[];
extern void func_8017FA84(void *a0);
extern u8 D_8018BE48[];
extern u8 D_8018BE50[];
extern u8 *func_8017FD6C(s32 a0, s32 a1, s32 a2);
extern void func_8017FC6C(s32 s2);
extern u32 D_8018BD88[];
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern u8 * func_8017FD6C(s32 a0, s32 a1, s32 a2);
extern s16 D_80126CB4;
extern s16 D_80126CB6;
extern s16 D_80126CB8;
extern s32  func_80180AF4(void);
extern s32  func_80134510(s32 a0);
extern s32  func_801803DC(s32 a0);
extern void func_8012CC1C(s32 arg0, s32 arg1);
extern s32  func_8012AF0C(s32 a0, s32 a1);
extern void func_80180388(s32);
extern s32 func_801802A4(s32 a0);
extern void func_80180388(s32 arg0);
extern void (*D_8018BF50[])(void);
extern void func_801804A0(void *a0);
extern void func_801804DC(s32 a0);
extern s32 func_801806B8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801292C8(u8 *a0);
extern void func_8012931C(u8 *a0);
extern u8 D_8018BF58[];
extern u8 D_8018BF60[];
extern void func_80180598(void *a0);
extern s32 *D_80126B90;
extern s32 func_80180838(void *a0, s32 a1, s32 a2);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3); /* TU:588  verbatim */
extern void func_80020F34(s32 a0, s32 a1);                 /* TU:1661 verbatim */
extern void RotTransSV(void *a0, void *a1, void *a2);      /* TU:3119 verbatim */
extern void func_80020DA4(s32 a0, s32 a1);
extern u8 D_8018BF68[];
extern void (*D_8018BFC8[])(void);
extern void func_80180990(void *a0);
extern void func_801809CC(void *a0);
extern s32 func_80180A00(void *arg0);
extern u32 D_8018BFA8[];
extern u32 D_8018BFC0;
extern void func_80180A58(s32 a0, u8 *a1);
extern void func_80180B24(s32 arg0);
extern void func_80180BF8(void *arg0);
extern void func_80180C48(s32 a0);
extern void func_8012C218(void *a0);
extern u8 D_8018BFE0[];
extern u8 D_8018C014[];
extern u8 D_801B101C[];
extern u8 D_80126B5C;
extern s32 D_80126B64;
extern void func_80180C74(s32 a0);
extern void func_80180E3C(s32 a0);
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern u8 D_8018C03C[];
extern void func_80181544(s32 a0);
extern void (*D_8018C08C[])(void);
extern void (*D_8018C074[])(void);
extern void func_80181668(s32 a0);
extern void func_801816EC(s32 a0);
extern void func_8018178C(s32 a0);
extern u8 D_801B0DA4[];
extern u8 D_801B0DD4[];
extern void func_80181954(s32 a0);
extern void func_80181A44(s32 a0);
extern void func_80181B04(s32 a0);
extern void (*D_8018C0EC[])(void);
extern void func_80181BE8(void *a0);
extern void func_80181C24(s32 a0);
extern void func_80181CB4(void);
extern void (*D_8018C150[])(void);
extern void func_80181CBC(void *a0);
extern void (*D_8018C104[])(void);
extern u8 D_80187704[];
extern s32 func_80181E30(void *);
extern void func_80181CF8(s32 a0);
extern void func_80181DB0(void);
extern void func_80181DB8(int param_1);
extern void func_80181DF0(s32 a0);
extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8(void);
extern s32 func_80181E30(void *a0);
extern void (*D_8018C230[])(void);
extern void func_80181E8C(void *a0);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(int, int);
extern int D_8018C220;
extern int *D_8018C1F0[];
extern void func_80181EC8(int param_1);
extern void func_801820AC(s32 param_1);
extern void func_801820DC(s32 a0);
extern void func_80182148(int param_1);
extern void func_80182214(s32 param_1);
extern void func_801822B8(s32 *a0);
extern void func_801822C8(s32 param_1);
extern void D_801CAB58;
extern void func_80182374(s32 arg0);
extern void func_80182420(s32 arg0);
extern u8 D_801CAFE0;
extern void func_80182468(s32 a0);
extern s32 func_801824A8(s32 s0);
extern void func_80142414(s32 a0, s16 a1);
extern u8 D_801CACF8;
extern void func_801824FC(s32 param_1);
extern void func_80182558(void *a0);
extern void func_8004914C(void *a0);                                   /* TU:3117 verbatim */
extern void func_800491AC(void *a0);                                   /* TU:3118 verbatim */
extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);                      /* TU:4488 verbatim */
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5); /* fleet modal x2820 */
extern void func_8002D4C8(s32 a0, s32 a1);                             /* TU:57   verbatim */
extern s32 func_8012BEE8(s32 a0);                                      /* TU:4320 verbatim */
extern void func_8012A828(s32 a0, void *a1);                           /* TU:4575 verbatim */
extern s32 D_80126B58;          /* TU:53   verbatim */
extern s32 D_801270C8[];        /* TU:4480 verbatim */
extern u8 D_801152A8[];         /* TU:597  verbatim */
extern void D_801CAB58;         /* TU:5246 verbatim */
extern SV4_8018256C D_8018C340[];        /* overlay-local canned SVECTOR pair */
extern void func_8018256C(s32 param_1);
extern void (*D_8018C350[])(void);
extern void func_801827CC(void *a0);
extern u8 D_801CB130[];
extern u8 D_8018C374[];
extern void func_8018283C(s32 *self);
extern void (*D_8018C37C[])(void);
extern void func_801829DC(void *a0);
extern void func_80182A18(int param_1);
extern void func_80182AC4(s32 param_1);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_80182558(void*);
extern void func_80182BA4(int param_1);
extern u8 D_8018C248[];
extern u32 D_8018C2B0;
extern u8 D_801CAF38[];
extern void func_80182BFC(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern int D_8018C36C[];
extern void func_80182D04(int param_1);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_80182F00(void *a0);
extern void func_8002AC00(s32 a0);
extern void func_80182F24(void *arg0);
extern void func_80182FB8(s32 param_1);
extern void func_80183004(s32 a0);
extern void func_80182F74(s32 *a0);
extern u16 D_801E42B0;
extern void func_80182FB8(s32 param_1);
extern s32  func_8012CE2C(s32 a0);
extern u8   D_801E3AE0[];
extern void func_80183004(s32 a0);
extern void func_801832B4(s32 a0);
extern void func_8012CBA4(s32 a0);   /* raw-void TU decl; cast to (s32(*)(s32)) at the call site, law 4 */
extern void func_80182D88(s32 a0);
extern void func_80183284(short *a0);
extern s32 D_8018C50C;
extern void func_801830C0(s32 param_1);
extern u8 D_801E4B08[];
extern u8 D_801E3B88[];
extern u8 D_801E3C10[];
extern s32  func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern s32  func_80143B6C(s32 a0, s32 a1);
extern void func_80183670(s32 a0, s32 a1, s32 a2, void *a3);
extern u8  D_801E3CE0[];
extern u8  D_8018C514[];
extern s32 D_8018C510;
extern s32 D_801E9CD8;
extern void func_8018335C(s32 a0);
extern SV4_801836B8 D_8018C524[];
extern void func_801836B8(s32 param_1, s32 param_2);
/* ==== end §8b carried decl layer ==== */


extern void func_801836B8(s32 a0, s32 a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern s32 func_8012CBCC(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern void func_80182D88(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);

extern s32 D_801E9CD8;
extern short D_801E3998;
extern u8 D_801E38F0[];
extern u8 D_801E3DA8[];

void func_80183894(s32 param_1) {
    s32 pv = param_1;
    s32 flag;
    s32 t;

    switch (*(u16 *)(pv + 0x34)) {
    case 0:
        if (*(s32 *)(pv + 0x1C) == 7) {
            func_801836B8(pv, 0xB);
        }
        break;
    case 1:
        t = func_8012B8E4(pv, 6);
        *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) += t;
        break;
    case 2:
        if (*(s32 *)(pv + 0x1C) == 10) {
            func_801836B8(pv, 0xB);
        }
        break;
    case 3:
        if (*(s32 *)(pv + 0x1C) % 10 == 0) {
            D_801E9CD8 += 0x10000;
        }
        func_8012B178(pv, D_801E9CD8);

        if ((*(u16 *)(pv + 0x86) & 1) != 0) {
            t = ((s32 (*)(s32))func_8012CBA4)(pv) & 0x2000;
            flag = 0;
            if (t == 0) {
                func_8012ADE4((u8 *)pv);
                flag = 1;
            }
        } else {
            t = func_8012CBCC(pv) & 0x2000;
            flag = 0;
            if (t != 0) {
                *(u16 *)(pv + 0x86) |= 1;
            }
        }

        func_80182D88(pv);
        func_801836B8(pv, 0x11);

        t = *(u16 *)(pv + 0xFE) - 1;
        *(u16 *)(pv + 0xFE) = t;
        if ((s16)t <= 0) {
            func_80143B6C(pv, 0);
            *(u16 *)(pv + 0xFE) = -(D_801E9CD8 / 0x10000);
        }

        if (flag == 1) {
            *(u16 *)(pv + 0x2) = 4;
            *(u16 *)(pv + 0x34) = 0;
            func_8012A828(pv, &D_801E3998);
        }
        break;
    case 4:
        break;
    }

    if (func_8012BEE8(pv) != 0) {
        switch (*(u16 *)(pv + 0x34)) {
        case 0:
            if (func_8012BD3C(pv, 0x400, 0x4000) != 0) {
                *(u16 *)(pv + 0x34) += 1;
                func_8012A828(pv, &D_801E38F0);
                *(s32 *)(pv + 0x1C) = 10;
            } else {
                *(u16 *)(pv + 0x2) = 4;
                *(u16 *)(pv + 0x34) = 0;
                func_8012A828(pv, &D_801E3998);
            }
            break;
        case 1:
            *(u16 *)(pv + 0x34) = 2;
            *(s32 *)(pv + 0x1C) = 0x18;
            func_8012A828(pv, &D_801E3DA8);
            break;
        case 2:
        case 4:
            *(u16 *)(pv + 0x2) = 4;
            *(u16 *)(pv + 0x34) = 0;
            func_8012A828(pv, &D_801E3998);
            break;
        case 3:
            *(s32 *)(pv + 0x1C) = 10;
            *(u16 *)(pv + 0x34) += 1;
            break;
        }
    }
}


#include "common.h"

extern s32 func_800291B4(s32 arg);
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern s32 func_8012B030(u8 *a0);

extern u16 D_801274E4[];
extern u8 D_8018C394[];
extern u8 D_8018C4CC[];

void func_80183B58(s32 a0)
{
    s32 s0;
    s32 v0;
    s32 v1;
    u32 field70;
    /* $2 pin: idx1's post-shift value must land in $v0 so the 104-multiply
       chain is forced into $v1 (target's register choice). */
    s32 idx1;
    s32 prod1;
    s32 idx2;

    s0 = a0;
    v1 = func_800291B4(0xCC) & 0xFF;

    /* Hand-written if/elseif chain (order 6, 0xC, 7, 0xD) -- NOT a switch:
       a switch compiles to a binary-search slti tree, which is the wrong
       shape. The duplicated arm bodies are tail-merged by cross_jump into
       the single physical blocks .L80183B98 / .L80183BB0 (law 22 / §193-C). */
    if (v1 == 6) {
        v0 = *(u16 *)(s0 + 0x70) & 1;
    } else if (v1 == 0xC) {
        v0 = *(u16 *)(s0 + 0x70) & 2;
        v0 = v0 != 0;
    } else if (v1 == 7) {
        v0 = *(u16 *)(s0 + 0x70) & 1;
    } else if (v1 == 0xD) {
        v0 = *(u16 *)(s0 + 0x70) & 2;
        v0 = v0 != 0;
    } else {
        v0 = 0;
    }

    if (v0 == 0) {
        D_801274E4[0] |= 1;
        return;
    }

    field70 = *(u16 *)(s0 + 0x70);
    idx1 = (field70 & 0xF00u) >> 8;
    /* prod1 is its own named statement so the 5-insn 104-multiply chain
       expands HERE, i.e. before the `if` below emits idx2's andi/sltu.
       Folding it into the call argument sinks the chain past the andi/sltu
       (the first-pass 6-instruction SCHEDULE-REORDER residual). */
    prod1 = idx1 * 104;
    /* if/else (not `!= 0`): jump_optimize's "if (..) x=1; else x=0" rewrite
       runs emit_store_flag on the already-materialised AND *register*, giving
       andi + sltu. Written as `(field70 & 0x1000) != 0` the single-bit path
       fires instead and emits srl + andi. */
    if (field70 & 0x1000) {
        idx2 = 1;
    } else {
        idx2 = 0;
    }
    v0 = func_8012C354(s0, (s32)D_8018C394 + prod1 + idx2 * 52);
    if (v0 == 0) {
        return;
    }

    *(s8 *)(s0 + 0xC0) = 1;
    *(s32 *)(s0 + 0xB4) = -1;
    *(s8 *)(s0 + 0xC1) = 0;
    *(s32 *)(s0 + 0xBC) = (s32)D_8018C4CC;
    func_80143970(s0);
    func_8012B030((u8 *)s0);
    *(s16 *)(s0 + 0x86) = 1;
    *(s16 *)(s0 + 0x2) = 1;
}



extern void (*D_8018C534[])(void);

void func_80183C94(void *a0) {
    D_8018C534[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012CBF4(s32 a0);
extern void func_80183004(s32 a0);

void func_80183CD0(s32 a0)
{
    func_8012CBF4(a0);
    if (*(u16 *)(a0 + 0x72) & 0x4000) {
        func_80183004(a0);
    }
}


#include "common.h"

extern s32 func_8012BCCC(s32 a0);
extern void func_801832B4(s32 a0);
extern s32 rand(void);
extern void func_8012B23C(s32 a0);
extern s32 func_8012CE2C(s32 a0);
extern void func_8012A828(s32 a0, void *a1);

extern u8  D_801E3AE0[];

void func_80183D14(s32 a0) {
    s32 v0;
    s32 v1;
    s32 rv;

    if (*(u16 *)(a0 + 0x34) != 0) {
        return;
    }
    v0 = *(u16 *)(a0 + 0x72);
    if ((v0 & 0x4000) == 0) {
        return;
    }

    v0 = func_8012BCCC(a0);
    if (v0 <= 0x10000) {
        func_801832B4(a0);
        return;
    }

    *(s16 *)(a0 + 0x2) = 3;
    *(u16 *)(a0 + 0x34) = 0;
    {
        s32 magic = 0xAA10;
        *(s16 *)(a0 + 0x5C) = magic;
    }
    *(s32 *)(a0 + 0x1C) = (rand() & 0x1F) + 0x28;
    rv = rand() & 0x3FF;
    v1 = rv - 0x200;
    if (v1 >= 0) {
        v1 = rv + 0x100;
    } else {
        v1 = rv - 0x500;
    }
    v0 = *(s32 *)(a0 + 0x20);
    v0 = *(u16 *)(v0 + 0x12);
    v0 = (v0 + v1) & 0xFFF;
    *(s16 *)(a0 + 0xFC) = v0;
    func_8012B23C(a0);
    if (func_8012CE2C(a0) != 0) {
        v0 = *(u16 *)(a0 + 0x86) | 1;
    } else {
        v0 = *(u16 *)(a0 + 0x86) & 0xFFFE;
    }
    *(u16 *)(a0 + 0x86) = v0;
    func_8012A828(a0, (void *)D_801E3AE0);
}


#include "common.h"

extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_8018C510;
extern u8 D_801E4B08[];
extern u8 D_801E3B88[];

void func_80183E18(void *a0) {
    s32 s0 = (s32)a0;

    *(u16 *)((s32)a0 + 2) = 2;
    func_8012B2CC(s0);
    func_8012B23C(s0);
    func_8012B178(s0, D_8018C510);
    if ((*(u16 *)(s0 + 0x70) & 0x200) != 0) {
        func_8012A828(s0, (void *)D_801E4B08);
    } else {
        func_8012A828(s0, (void *)D_801E3B88);
    }
    *(s32 *)(s0 + 0x1C) = 0x88;
}


extern void func_8012CBA4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern s32 rand(void);
extern void func_8012B23C(s32 a0);
extern s32 func_8012CE2C(s32 a0);
extern void func_8012A828(s32 a0, void *a1);

extern u8 D_801E3AE0[];

void func_80183E9C(s32 a0) {
    s32 s0 = a0;
    s32 v0;
    s32 v1;
    s32 rv;

    func_8012CBA4(s0);
    if (func_8012BEE8(s0) != 0 || func_8012BCCC(s0) < 0x3001) {
        *(s16 *)(s0 + 2) = 3;
        *(u16 *)(s0 + 0x34) = 0;
        *(u16 *)(s0 + 0x5C) = 0xAA10;
        *(s32 *)(s0 + 0x1C) = (rand() & 0x1F) + 0x28;
        rv = rand() & 0x3FF;
        v1 = rv - 0x200;
        if (v1 >= 0) {
            v1 = rv + 0x100;
        } else {
            v1 = rv - 0x500;
        }
        v0 = *(s32 *)(s0 + 0x20);
        v0 = *(u16 *)(v0 + 0x12);
        *(s16 *)(s0 + 0xFC) = (v0 + v1) & 0xFFF;
        func_8012B23C(s0);
        if (func_8012CE2C(s0) != 0) {
            *(u16 *)(s0 + 0x86) |= 1;
        } else {
            *(u16 *)(s0 + 0x86) &= 0xFFFE;
        }
        func_8012A828(s0, D_801E3AE0);
    }
}


extern s32 resLoad_lastId;
extern s32 func_80183FB4(s32 arg0);

s32 func_80183F7C(void) {
    return (u32)(func_80183FB4(func_80029504()) ^ resLoad_lastId) != 0;
}




















s32 func_80183FB4(s32 arg0)
{
  s32 ret;
 ret = 0x74; if (0x2ee > arg0) { ret = 0xB;
  }
  else
  {
  }
  return ret;
}


extern void func_8013CB84(void);
    void func_80183FCC(void) {
        func_8013CB84();
    }



extern void (*D_8018C574[])(void);

void func_80183FEC(void *a0) {
    D_8018C574[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern u8 D_80126B5C;
extern void func_80015978(s32 a0, s32 *a1);
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void func_80184560(s32 a0);   /* slate-wide spelling (func_80184278); cast at call */
extern s32 func_8012AD50(void *a0);
extern s32 rand(void);

/* MATCH (82 ins, relocation-masked; all 27 relocs verified against the target .s).
 *
 * The whole 17-instruction entry-block residual of the first pass was ONE alias fact,
 * not scheduling or regalloc:
 *
 *   sched.c:817 true_dependence()/anti_dependence() drop the dependence between a
 *   MEM_IN_STRUCT_P reference at a VARYING address (non-QImode) and a non-MEM_IN_STRUCT
 *   reference at a FIXED address.  The four D_801EB1xx stores are plain extern scalars
 *   (fixed SYMBOL_REF address, MEM_IN_STRUCT_P == 0), so if the a0-derived reads carry
 *   MEM_IN_STRUCT_P the scheduler may hoist ALL of them above ALL of the stores -- which
 *   is exactly the target's opening block (lh 0xFC / lh 0x70 / lw 0xDC all before the
 *   first store, three simultaneously-live temps in $v0/$v1/$a2, and the a1 arg setup
 *   free to float to the top of the block).
 *
 *   expr.c:4567-4577 sets MEM_IN_STRUCT_P on an INDIRECT_REF only when the address
 *   TREE is a PLUS_EXPR.  `*(s16 *)(a0 + 0x70)` is INDIRECT_REF(NOP_EXPR(PLUS_EXPR)) --
 *   the NOP sits on top, so the flag is NOT set and every load stays pinned below the
 *   preceding store.  `((s16 *)a0)[0x70/2]` is build_array_ref -> INDIRECT_REF(PLUS_EXPR)
 *   with the NOP inside, so the flag IS set.  Identical addressing bytes, opposite
 *   scheduling freedom.  Rewriting the three entry-block reads in the [] form took the
 *   residual 17 -> 4; the last 4 were the $v0/$a2 assignment of the two independent
 *   stores, fixed by emitting D_801EB130 before D_801EB134 in source order.
 *
 * The loads inside the loop are deliberately left in the raw `*(T *)(p + K)` form -- that
 * region was already byte-identical and granting them MEM_IN_STRUCT_P would re-open it.
 */
void func_80184028(s32 a0) {
    extern s32 D_801EB130;
    extern s16 D_801EB134;
    extern s32 D_801EB138;
    extern s32 D_801EB13C;
    extern u8 D_8018C554[];
    extern u8 D_8018C55C[];
    extern s8 D_801E9CE0;
    extern s8 D_801E9D2F;

    s16 buf[4];
    s32 i;
    s8 *p;
    u8 *obj;

    /* [] form (not *(T *)(a0 + K)) -- see the MEM_IN_STRUCT_P note above. */
    D_801EB130 = ((s16 *)a0)[0xFC / 2];
    D_801EB134 = ((s32 *)a0)[0xDC / 4];
    D_801EB138 = (s32)(D_8018C554 + ((s16 *)a0)[0x70 / 2] * 4);
    D_801EB13C = (s32)(D_8018C55C + ((s16 *)a0)[0x70 / 2] * 8);

    func_80015978((s32)&D_80126B5C, (s32 *)buf);
    buf[1] = *(u16 *)(a0 + 0xA);

    p = &D_801E9D2F;
    for (i = 0x4F; i >= 0; i--) {
        *p = 0;
        p--;
    }

    for (i = 0; i < D_801EB130; i++) {
        obj = func_801290DC(0x61, (u8 *)buf);
        if (obj != 0) {
            *(&D_801E9CE0 + i) = 1;
            *(s32 *)(obj + 0x34) = i;
            func_80184560((s32)obj);
            *(u16 *)(obj + 0xA) += (rand() & 0xF) * 3 * 16;
        }
    }

    func_8012AD50((void *)a0);
}


void func_80184170(s32 a0) {
    extern u8 D_80126B5C;
    extern s8 D_801E9CE0;
    extern s32 D_801EB130;
    extern u8 *func_801290DC(s32 a0, u8 *a1);

    s16 buf[4];
    s32 i;
    s32 slot;
    u8 *obj;

    slot = -1;
    func_80015978((s32)&D_80126B5C, (s32 *)buf);
    buf[1] = *(u16 *)(a0 + 0xA);

    for (i = 0; i < D_801EB130; i++) {
        if (slot != -1) break;
        if (*(u8 *)(&D_801E9CE0 + i) == 0) {
            slot = i;
        }
    }

    if (slot != -1) {
        obj = func_801290DC(0x61, (u8 *)buf);
        if (obj != 0) {
            *(&D_801E9CE0 + slot) = 1;
            *(s32 *)(obj + 0x34) = slot;
        }
    }
}



extern void (*D_8018C57C[])(void);

void func_8018423C(void *a0) {
    D_8018C57C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);
extern void func_80184560(s32);
extern s32 rand(void);
extern u8 D_801E9D30[];
extern s32 D_801EB13C;

void func_80184278(int param_1)
{
    s32 p;
    s32 idx;
    s32 dst;
    s32 ptr;
    s32 r;
    s32 v;
    s32 c1, c2, c3, c4;
    s32 s0v;
    s32 v1a;

    p = *(s32 *)(param_1 + 0x20);
    idx = *(s32 *)(param_1 + 0x34);
    dst = (s32)(D_801E9D30 + idx * 0x40);

    func_8001CD9C(p, (void *)dst);
    func_800233CC((void *)dst, 0x10);

    r = rand();
    r = (r & 7) + 1;
    *(s32 *)(dst + 0) = (r << 7) | ((r << 23) | (r << 15));
    *(s32 *)(dst + 4) = 0;

    *(s32 *)(p + 4) = *(s32 *)(p + 4) | 0x50000000;

    func_80184560(param_1);

    r = rand();
    v = (r & 3) * 1365;
    ptr = D_801EB13C;
    *(s16 *)(p + 0x1A) = v;
    *(s16 *)(p + 0x18) = v;

    *(s16 *)(param_1 + 0x12) = *(u16 *)(param_1 + 6) + *(u16 *)(ptr + 2);
    v1a = *(u16 *)(param_1 + 0xE) + *(u16 *)(ptr + 6);
    *(s16 *)(param_1 + 0x10) = 0;
    *(s16 *)(param_1 + 0x18) = 0;
    *(s16 *)(param_1 + 0x1A) = v1a;

    c1 = rand();
    c2 = rand();
    c3 = rand();
    c4 = rand();

    s0v = ((c1 & 3) << 10) + ((c2 & 0x1F) << 5) + ((c3 & 3) << 8) + (c4 & 0xFF);
    *(s16 *)(p + 0x12) = s0v;

    r = rand();
    *(s16 *)(param_1 + 0x2E) = (r & 7) * 11;

    r = rand();
    *(s16 *)(param_1 + 0x2C) = (r & 0x1F) + 4;
    *(s16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


typedef struct { s16 vx, vy, vz, pad; } SVEC2_C59C_8017D9CC;
typedef struct { s16 vx, vy; } DVEC2_C59C_8017D9CC;



typedef struct {
    s16 vx, vy, vz;
} UVec_8017DB64;

void func_80184410(int param_1)
{
    extern s16 D_801EB134;
    extern s32 D_801EB13C;

    UVec_8017DB64 v;
    int p;
    s32 ptr;
    u16 *o;

    p = *(int *)(param_1 + 0x20);
    o = (u16 *)param_1;
    v.vy = 0;
    v.vx = 0;
    v.vz = o[0x16];
    func_800139C8(*(short *)(p + 0x12) = *(unsigned short *)(p + 0x12) + o[0x17], &v, &v);

    o[3] = o[9] + v.vx;
    o[7] = o[0xD] + v.vz;
    o[5] = o[5] + o[0xB];
    ptr = D_801EB13C;
    o[8] = o[8] + *(unsigned short *)ptr;
    o[9] = o[9] - o[8];
    o[0xC] = o[0xC] + *(unsigned short *)(ptr + 2);
    o[0xD] = o[0xD] - o[0xC];

    if (D_801EB134 < *(short *)(param_1 + 0xA)) {
        o[1] = o[1] + 1;
    }
}


extern void func_801846EC(s32 *param_1);
extern u8 D_801E9D30[];

void func_80184500(s32 param_1) {
    s32 rec;
    s32 val;

    rec = (s32)(D_801E9D30 + *(s32 *)(param_1 + 0x34) * 0x40);
    val = *(u8 *)rec;
    val = val - 8;
    if (val > 0) {
        goto join;
    }
    func_801846EC(param_1);
join:
    if (val <= 0) {
        return;
    }
    val = (val << 16 | val << 8) | val;
    *(s32 *)rec = val;
}


typedef struct { s16 vx, vy; } DVEC2_C59C_8017DBEC;



extern s32 rand(void);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 D_801EB138;

typedef struct {
    s16 vx, vy, vz, pad;
} UVec_8017DED4;

void func_80184560(s32 param_1)
{
    UVec_8017DED4 v;
    s16 lim;

    v.vx = ((rand() & 1) << 8) + ((rand() & 0x1F) << 3) + (rand() & 0x1F);
    v.vz = 0;
    v.vy = 0;

    func_800139C8(((rand() & 3) << 10) + ((rand() & 0x1F) << 5) + ((rand() & 3) << 8) + (rand() & 0xFF), &v, &v);

    if (v.vx > *(s16 *)D_801EB138) {
        lim = *(s16 *)D_801EB138;
        v.vx = v.vx - lim;
    } else if (v.vx < -*(s16 *)D_801EB138) {
        lim = *(s16 *)D_801EB138;
        v.vx = lim + v.vx;
    }

    if (v.vz > *(s16 *)(D_801EB138 + 2)) {
        lim = *(s16 *)(D_801EB138 + 2);
        v.vz = v.vz - lim;
    } else if (v.vz < -*(s16 *)(D_801EB138 + 2)) {
        lim = *(s16 *)(D_801EB138 + 2);
        v.vz = lim + v.vz;
    }

    *(u16 *)(param_1 + 6) += v.vx;
    *(u16 *)(param_1 + 0xA) += v.vy;
    *(u16 *)(param_1 + 0xE) += v.vz;

    *(u16 *)(param_1 + 0x16) = (rand() & 7) + 8;
}



















extern void func_801292C8(u8*);
void func_801846EC(s32 *param_1)
{
    extern s8 D_801E9CE0;

    *(&D_801E9CE0 + param_1[0x34 / 4]) = 0;
    func_801292C8((u8 *)param_1);
}


void func_8018471C(s32 a0) {
    extern s32 func_800291B4(s32 arg);
    extern s32 func_80029178(s32 arg);
    extern void func_8012CAE4(void *a0);
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern void (*D_8018C588[])(void);
    extern u8 D_8018C778[];
    extern s16 D_801EB140;
    extern s16 D_801EB144;
    extern s32 D_801EB148;
    extern s32 func_80143994(s32 a0, s32 a1);
    extern void MoveImage(void *a0, s32 a1, s32 a2);

    s16 i;
    s32 v0;
    s32 v1;
    s32 vp;
    u16 sp10[4];

    if ((u8)func_800291B4(0x89) != 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    for (i = 0;;) {
        if ((u8)func_80029178(i + 0x40) == 0) {
            func_8012CAE4((void *)a0);
            return;
        }
        i = i + 1;
        if ((s16)i >= 0xD) {
            break;
        }
    }

    if (*(s32 *)(a0 + 0x20) != 0) {
        return;
    }
    if (func_8012C354(a0, (s32)D_8018C778) == 0) {
        return;
    }

    func_8012A828(a0, (void *)&D_8018C588);

    vp = *(s32 *)(a0 + 0x20);
    *(u16 *)(vp + 0x2C) |= 0x10;

    vp = *(s32 *)(a0 + 0x20);
    *(s16 *)(vp + 0x1C) = 0x3800;
    *(s16 *)(vp + 0x1A) = 0x3800;
    *(s16 *)(vp + 0x18) = 0x3800;

    *(s32 *)&D_801EB140 = *(s16 *)(a0 + 0x88) << 16;
    *(s32 *)&D_801EB144 = *(s16 *)(a0 + 0x8A) << 16;
    D_801EB148 = *(s16 *)(a0 + 0x8C) << 16;

    *(s32 *)(a0 + 0xCC) = func_80143994(a0, 0x4000);

    *(s16 *)(a0 + 0xF8) = 3;

    sp10[0] = 0x2A8;
    sp10[1] = 0x188;
    sp10[2] = 0xC;
    sp10[3] = 0x28;
    MoveImage(sp10, 0x2B4, 0x188);

    sp10[0] = 0x248;
    sp10[1] = 0x1C0;
    MoveImage(sp10, 0x2A8, 0x188);

    v1 = *(u16 *)(a0 + 2);
    v0 = *(u16 *)(a0 + 0xA);
    v1 = v1 + 1;
    v0 = v0 - 0x400;
    *(u16 *)(a0 + 0xA) = v0;
    *(u16 *)(a0 + 2) = v1;
}


#include "common.h"

extern void func_8012A828(s32 a0, void * a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_801858D4(s32 a0, s16 a1, s16 a2);
extern void func_80185948(s16 *a0);
extern s32 func_8012BB3C(s32 arg0, s32 arg1, u32 arg2, s32 arg3);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_80185DD8(void);

/*
 * §136 note (the lever that closed this one): the copy-loop counter and the 8/2
 * selector passed as func_8012BB3C's 4th argument are ONE `short` local, not two.
 *   - As two locals, combine's set_nonzero_bits_and_sign_copies sees the selector
 *     pseudo set only to 8 and 2, proves num_sign_bit_copies >= 17, and DELETES the
 *     `sll/sra 16` argument sign-extension  =>  LENGTH-DRIFT -2.
 *   - Sharing the pseudo with the loop's `i = i + 1` makes the union of sets
 *     unprovable, so the extension survives -- and the merged (longer) live range is
 *     what takes $a3 while the two loop-invariant base addresses take $a1/$a2.
 */
void func_801848BC(s32 a0) {

    extern void (*D_8018C610[])(void);
    extern s16 D_801EB140;
    extern s32 D_801EB14C;
    extern s32 D_801EB154;
    s32 v0;
    s32 v1;

    v0 = *(s32 *)(a0 + 0x1C);
    v1 = -1;
    v0 = v0 - 1;
    *(s32 *)(a0 + 0x1C) = v0;

    if (v0 == v1) {
        s32 t;
        s16 i;
        s32 ret;
        s32 ang;

        func_8012A828(a0, (void *)&D_8018C610);

        t = *(u16 *)(a0 + 0x10A) + 1;
        *(u16 *)(a0 + 0x10A) = t;

        if ((t & 3) != 0) {
            if (*(s16 *)(a0 + 0x104) == 0) {
                s32 r = rand();
                s32 x;
                s32 y;

                x = *(s16 *)(a0 + 0x88) - 0x200;
                x += (r & 0x7F) << 3;
                D_801EB14C = x << 16;

                y = *(s16 *)(a0 + 0x8C) - 0x200;
                y += (u32)(r & 0x7F00) >> 5;
                D_801EB154 = y << 16;
            } else {
                func_80185948((s16 *)a0);
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0xC00;
            }
        } else {
            for (i = 0; i < 2; i++) {
                ((s32 *)&D_801EB14C)[i] = ((s32 *)&D_801EB140)[i];
            }
        }

        i = 8;
        if (*(s16 *)(a0 + 0x108) >= 0xD) {
            i = 2;
        }

        ret = func_8012BB3C(a0 + 4, (s32)&D_801EB14C,
                            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), i);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + ret;

        ang = -6 - *(u16 *)(a0 + 0x104);
        func_801858D4(a0, (s16)ang, 0x50);

        if (*(s16 *)(a0 + 0x104) != 0) {
            func_80146A6C(2, (void *)a0, 0, 0, 0, 3,
                (*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF) | 0x30009000);
        }

        *(s16 *)(a0 + 0x108) = 0;
        if ((s16)func_80185DD8() == 0) {
            *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) | 0x200;
        }
        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
    } else {
        s16 d = *(s16 *)(a0 + 0x102);

        if (d != 0) {
            s32 r2 = func_8012B8E4(a0, d);

            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r2;
        }
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, void * a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_801858D4(s32 a0, s16 a1, s16 a2);
extern void func_80185948(s16 *a0);
extern s32 func_8012BB3C(s32 arg0, s32 arg1, u32 arg2, s32 arg3);
extern s32 func_80185DD8(void);
extern s32 func_8012BC60(void *a0, void *a1);
extern s32 func_8012B864(s32 a0);
extern s32 func_8012BD14(s32 a0);
extern void func_8012B200(u8 *a0);
extern s32 func_80185B48(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80185A24(s32 a0);
extern unsigned char D_8018C750[];
extern void (*D_8018C588[])(void);
extern void (*D_8018C610[])(void);
extern s32 D_801EB14C;

/*
 * Three load-bearing details (byte-proven, single-axis A/B, pinned triple):
 *
 *  1. `s32 dead[4];`  -- cookbook §162i1/§164-53 dead BLKmode local reserving the
 *     target's vars area (frame 0x48).  Same device as func_80184E8C above.
 *
 *  2. `fire = ret + zr;` with `register s32 zr __asm__("$0");` -- cookbook RC-12's
 *     pin-free zero-register add.  The target keeps a REAL `addu $v0,$s2,$zero`
 *     copy of the flag at the join before `beqz $v0` (reorg then steals it into the
 *     two `bnez`/`beqz` delay slots that branch there, so it is worth +2 ins and
 *     shifts every branch offset in the tail).  A plain `if (ret != 0)` -- and a
 *     plain `fire = ret;` temp -- both lose the copy to cse's canon_reg: 226 ins,
 *     LENGTH-DRIFT/-2, closeness 69.  The `+ zr` add is a real RTL insn cse cannot
 *     fold away.  Pinning `ret` itself to `$18` instead REGRESSES (closeness 77).
 *
 *  3. `ang = -0xE - spd;` hoisted ABOVE the `*(s16 *)(a0 + 0x104) == 0` guard --
 *     that source position is what makes gcc emit `addiu $v0,$zero,-0xE` early,
 *     fill the guard's delay slot with `subu $a1,$v0,$s1`, and re-home the
 *     func_8012B864 result into $a0 (`addu $a0,$v0,$zero`).  Computing it inline at
 *     the call site instead: OPCODE-MIXED, closeness 12.
 *     Note the two constants really are different: the 0x12 store takes t - 0x800,
 *     the func_801858D4 argument takes -0xE - spd.
 */
void func_80184AFC(s32 a0) {
    s32 dead[4];
    s32 ret;
    s32 v;
    s32 spd;
    s32 t;
    s16 rc;
    u16 fire;

    ret = 0;
    if ((*(u16 *)(a0 + 0x5C) & 0x200) != 0) {
        if ((s16)func_80185DD8() != 0) {
            *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFDFF;
        }
    }

    func_80185A24(a0);

    v = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v;
    if (v != 0) {
        if ((v & 3) == 0) {
            if (func_8012BC60((void *)(a0 + 4), (void *)&D_801EB14C) < 0x900) {
                *(s32 *)(a0 + 0x1C) = 1;
            }
        }
        if (*(s16 *)(a0 + 0x106) == 0) {
            s32 r;
            s32 p;
            s32 ang;
            r = func_8012BB3C(a0 + 4, (s32)&D_801EB14C,
                              *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), 8);
            p = *(s32 *)(a0 + 0x20);
            *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + r;
            ang = -6 - *(u16 *)(a0 + 0x104);
            func_801858D4(a0, (s16)ang, 0);
        }
        if (*(s16 *)(a0 + 0x104) != 0) {
            if (*(s32 *)(a0 + 0x90) == (s32)&D_8018C610 &&
                (u32)*(s32 *)(a0 + 0x94) < 0xB) {
                *(s32 *)(a0 + 0x94) = *(s32 *)(a0 + 0x94) + 1;
            }
            if ((*(s32 *)(a0 + 0x1C) & 3) == 0) {
                ret = 1;
            }
        }
    } else {
        s16 u;
        func_8012B200((u8 *)a0);
        func_8012A828(a0, (void *)&D_8018C588);
        *(s32 *)(a0 + 0x1C) = 0x14 - (*(s16 *)(a0 + 0x104) << 1);
        if (func_8012BD14(a0) <= 0x23FFF) {
            *(s16 *)(a0 + 0x102) = 0xA - *(u16 *)(a0 + 0x104);
        } else {
            *(s16 *)(a0 + 0x102) = 0;
        }
        u = *(s16 *)(a0 + 0x104);
        if (u != 0) {
            u = u - 4;
            *(s16 *)(a0 + 0x104) = u;
            if (u < 0) {
                *(s16 *)(a0 + 0x104) = 0;
            }
        }
        *(s16 *)(a0 + 2) = 3;
    }

    rc = (s16)((s32 (*)(s32))func_80185B48)(a0);
    if (rc != 0) {
        if (rc < 0) {
            return;
        }
        if (*(s16 *)(a0 + 0xFE) == 0) {
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = -*(u16 *)(a0 + 0x62);
            func_801858D4(a0, -0x1E, 0);
            func_80185948((s16 *)a0);
            *(s16 *)(a0 + 0x104) = 0xA;
            ret = 1;
        } else {
            *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFDFF;
            func_8012B200((u8 *)a0);
            func_8012A828(a0, (void *)D_8018C750);
            *(s32 *)(a0 + 0x1C) = 0x10;
            *(s16 *)(a0 + 2) = 0xA;
            return;
        }
    } else {
        s32 d = func_8012BD14(a0);
        if (d < 0x10000) {
            spd = 0;
            if (d >= 0x6400) {
                spd = (func_8012BDBC(a0, 0x500) != 0) << 2;
            } else if (d >= 0x2400) {
                if (func_8012BDBC(a0, 0x680) != 0) {
                    spd = 7;
                }
            } else {
                spd = 0xA;
            }
            if (spd != 0) {
                s32 ang;
                func_80185948((s16 *)a0);
                t = func_8012B864(a0);
                ang = -0xE - spd;
                if (*(s16 *)(a0 + 0x104) == 0) {
                    ret = 1;
                    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t - 0x800;
                }
                *(s16 *)(a0 + 0x104) = spd;
                func_801858D4(a0, ang, 0);
            }
        }
    }

    fire = ret + 0;
    if (fire != 0) {
        func_80146A6C(2, (void *)a0, 0, 0, 0, 3,
                      ((*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800) & 0xFFF) | 0x30009000);
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B200(u8 *a0);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_8012CBA4(s32 a0);
extern s32 func_80185B48(s32 a0);
extern s32 func_80185D3C(void *a0, s16 a1);
extern s32 func_80185DD8(void);
extern unsigned char D_8018C700[];
extern unsigned char D_8018C750[];

void func_80184E8C(s32 a0) {
    /* LOAD-BEARING (cookbook §162i1 / §164-53): dead BLKmode local reserving the
     * target's vars area.  vars = 0x38 - ROUND8(args 0x10) - ROUND8(4*regs 8) = 0x20. */
    s32 pad[8];
    s16 v;
    s32 t;
    s32 r;

    if ((*(u16 *)(a0 + 0x5C) & 0x200) != 0) {
        if ((s16)func_80185DD8() != 0) {
            *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFDFF;
        }
    }

    v = (s16)((s32 (*)(s32))func_80185B48)(a0);
    if (v != 0) {
        if (v < 0) {
            return;
        }
        *(s16 *)(a0 + 0xF4) = 1;
        *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFDFF;
        func_8012A828(a0, (void *)D_8018C750);
        *(s32 *)(a0 + 0x1C) = 0x10;
        *(s16 *)(a0 + 2) = 0xA;
        return;
    }

    if (*(s16 *)(a0 + 0x76) == 0) {
        *(s16 *)(a0 + 0x5C) = 0;
        *(s16 *)(a0 + 0x5E) = 0;
        func_8012A828(a0, (void *)D_8018C700);
        *(s32 *)(a0 + 0x1C) = 8;
        *(s16 *)(a0 + 0xF8) = 0x14;
        *(s16 *)(a0 + 2) = 0x11;
        return;
    }

    t = *(s32 *)(a0 + 0x1C);
    if (t == 0) {
        goto zero;
    }
    if (t >= 0x1E) {
        goto dec;
    }
    if (*(s16 *)(a0 + 0xFE) < 3) {
        goto second;
    }
    if (func_8012BD3C(a0, 0x400, 0x10000) != 1) {
        goto second;
    }
shared:
    *(s16 *)(a0 + 0xF4) = 0;
    *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFDFF;
    func_8012A828(a0, (void *)D_8018C700);
    *(s32 *)(a0 + 0x1C) = 8;
    *(s16 *)(a0 + 2) = 0xB;
    return;
second:
    if (func_8012BD3C(a0, 0x2C0, 0x31000) != 1) {
        goto turn;
    }
    if ((s16)((s32 (*)(void *, s32))func_80185D3C)((void *)a0, 1) != 0) {
        goto shared;
    }
    *(s32 *)(a0 + 0x1C) = 8;
    *(s16 *)(a0 + 0xF4) = 0;
    *(s16 *)(a0 + 2) = 0xE;
    *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFDFF;
    return;
turn:
    r = func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
dec:
    *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
    return;
zero:
    if ((s16)((s32 (*)(void *, s32))func_80185D3C)((void *)a0, 1) == 0) {
        func_8012B178(a0, 0xFFFD0000);
        func_8012CBA4(a0);
    }
    func_8012B200((u8 *)a0);
    *(s16 *)(a0 + 0xF4) = 0;
    *(s32 *)(a0 + 0x1C) = 0x1D;
    /* LOAD-BEARING (cookbook §5a): zero-byte cross-jump barrier. Without it
     * find_cross_jump merges this block's trailing `sw $v0,0x1C($s0)` with the
     * identical one ending the `dec:` block -> LENGTH-DRIFT -2. Do not remove. */
    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
}


#include "common.h"

extern s32 func_80185B48(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
extern void func_80185E30(void *a0);
extern void (*D_8018C588[])(void);

/*
 * Four load-bearing details (each single-axis A/B'd against match_one; the
 * function is 95/95 byte-exact only with all four):
 *
 *  1. `s32 pad[4];` -- cookbook §162i1/§164-53 dead BLKmode local reserving the
 *     target's vars area, the same device func_80184E8C uses above in this TU.
 *     vars = 0x38 - ROUND8(args 0x10) - ROUND8(4*5 saved regs = 0x18) = 0x10.
 *     Without it the frame is -0x30 and every sw/lw offset is wrong.
 *
 *  2. `__asm__ __volatile__("" : "=r"(cc) : "0"(cc));` after the first
 *     func_8012D624 call.  It is zero bytes and does BOTH jobs the target needs:
 *       (a) §5a cross-jump barrier -- find_cross_jump bails on a volatile asm, so
 *           gcc keeps BOTH copies of the `func_8012D624(a0,0xC0,0x30)` tail
 *           instead of tail-merging them (that merge costs 6 instructions);
 *       (b) it re-SETS cc, which kills the jump equivalence cse recorded at the
 *           `bne` above, so the deliberately-redundant `beq $s1,$s2` survives
 *           instead of folding to an unconditional `j`.  That surviving beq is
 *           also what keeps cc live across the call -> cc earns $s1, the saved
 *           set grows to s0-s3+ra, and the frame reaches 0x38.
 *     Laundering `one` instead of `cc` here emits `beq $s2,$s1` (operands
 *     swapped, closeness 1).  Laundering at the join instead of inside the arm
 *     loses the jump-threading (closeness 1 the other way).
 *
 *  3. `if (cc != one) goto second;` -- the explicit goto reproduces jump1's
 *     thread_jumps redirect (the bne skips PAST the redundant beq to
 *     .L8018512C).  Written as a plain `if (cc == one) { ... }` the bne lands on
 *     the beq instead: same length, one wrong branch word.
 *
 *  4. `__asm__ __volatile__("");` before `one = 1;` -- zero-byte sched1 fence
 *     (§194-A) that keeps the `addiu $s2,$zero,1` from floating above the call
 *     and its sll/sra.  `one` is pinned to $18 because otherwise the allocator
 *     hands cc/$s2 and one/$s1, i.e. the pair swapped.
 *
 *  Every read-modify-write below is written in-place (`t = load; t += K;`)
 *  rather than `t = load + K;` -- §219: the in-place form reuses the load's
 *  register (`addiu $v0,$v0,0x200`), the other allocates a fresh one.
 *  q/u are separate locals from p/t on purpose: sharing them puts the head
 *  block's pointer in $v1 and its value in $v0, the reverse of the target.
 */
void func_801850B4(s32 a0) {
    s32 pad[4];
    s32 p;
    s32 q;
    s32 u;
    s32 t;
    s32 hold;
    register s32 one __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus9)
    s32 cc;

    func_80185B48(a0);
    if (*(s32 *)(a0 + 0x1C) != 0) {
        q = *(s32 *)(a0 + 0x20);
        u = *(u16 *)(q + 0x12);
        hold = u + 0x100;
        u -= 0x380;
        *(u16 *)(q + 0x12) = u;
        cc = (s16)func_8012BD3C(a0, 0x100, 0x9000);
        one = 1;
        if (cc != one) {
            goto second;
        }
        func_8012D624((void *)a0, 0xC0, 0x30);
        __asm__ __volatile__("" : "=r"(cc) : "0"(cc));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
        if (cc == one) {
            goto rejoin;
        }
    second:
        p = *(s32 *)(a0 + 0x20);
        *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + 0x800;
        if (func_8012BD3C(a0, 0x100, 0x9000) == one) {
            func_8012D624((void *)a0, 0xC0, 0x30);
        }
    rejoin:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = hold;
        if (*(s32 *)(a0 + 0x1C) >= 5) {
            p = *(s32 *)(a0 + 0x20);
            t = *(u16 *)(p + 0x1C);
            t += 0x200;
            *(u16 *)(p + 0x1C) = t;
            *(u16 *)(p + 0x18) = t;
            p = *(s32 *)(a0 + 0x20);
            t = *(u16 *)(p + 0x1A);
            t -= 0x100;
        } else {
            p = *(s32 *)(a0 + 0x20);
            t = *(u16 *)(p + 0x1C);
            t -= 0x600;
            *(u16 *)(p + 0x1C) = t;
            *(u16 *)(p + 0x18) = t;
            p = *(s32 *)(a0 + 0x20);
            t = *(u16 *)(p + 0x1A);
            t += 0x300;
        }
        *(u16 *)(p + 0x1A) = t;
        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
    } else {
        func_8012A828(a0, (void *)D_8018C588);
        *(s32 *)(a0 + 0x1C) = 0;
        func_80185E30((void *)a0);
    }
}


extern u8 D_80126B5C;
extern s32 D_80126B64;
extern void (*D_8018C728)(s32);
extern unsigned char D_8018C700[];
extern unsigned char D_8018C7DC[];
extern s32 func_80185B48(s32 a0);
extern void func_80185E68(s32 a0);
extern void func_80185E3C(void *a0);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B864(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

/* §42c-6 / cookbook-index L15: this TU declares `extern s32 func_80185230(void);`
 * and calls it `func_80185230();`.  An ANSI `void func_80185230(s32)` definition
 * hard-errors twice (conflicting types, then too-few-arguments), so the incoming
 * $a0 is captured into a normal pseudo instead — the copy gets a callee-saved
 * home ($s0), which is exactly what the target prologue does. */
s32 func_80185230(void) {
    s32 a0v;
    s32 arg0 = a0v;
    s32 g1;
    s32 g2;
    s32 t;
    s16 h;
    s32 c1;
    s32 c2;
    s16 i;

    if (*(u16 *)(arg0 + 2) == 0xC) {
        g1 = *(s32 *)&D_80126B5C;
        g2 = D_80126B64;
    } else {
        g1 = 0;
        g2 = -0x5000000;
    }

    func_80185B48(arg0);
    func_8012AD80(arg0);

    if (*(s16 *)(arg0 + 0x16) > 0) {
        func_80185E68(arg0);
    }

    if (*(s16 *)(arg0 + 0xA) < -2) {
        t = *(s32 *)(arg0 + 0x1C);
        if (t == 0) {
            func_80146A6C(2, (void *)arg0, 0, 0, 0, 3, 0x30000000);
            h = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A);
            if (h != 0x3800) {
                *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = h - 0x400;
            }
            if (*(s16 *)(arg0 + 0x16) > 0) {
                *(s32 *)(arg0 + 0x1C) = 1;
                func_8012A828(arg0, &D_8018C728);
            }
            *(s32 *)(arg0 + 0x10) = (g1 - *(s32 *)(arg0 + 4)) >> 5;
            *(s32 *)(arg0 + 0x18) = (g2 - *(s32 *)(arg0 + 0xC)) >> 5;
        } else {
            if (t < 0xD) {
                h = func_8012B864(arg0);
                *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = h;
                *(s32 *)(arg0 + 0x10) = (g1 - *(s32 *)(arg0 + 4)) / 0xB;
                *(s32 *)(arg0 + 0x18) = (g2 - *(s32 *)(arg0 + 0xC)) / 0xB;
            }
            *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;
        }
    } else {
        func_8002D4C8(0xB2D, 0);
        i = 0;
        func_8013C9C4(&D_8018C7DC);
        c2 = 3;
        c1 = 0x3000A000;
        g1 = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
        do {
            func_80146A6C(2, (void *)arg0, 0, 0, 0, c2, (g1 & 0xFFF) | c1);
            g1 = g1 + 0x200;
            i = i + 1;
        } while (i < 8);
        *(s16 *)(arg0 + 0xA) = -2;
        func_8012B200((u8 *)arg0);
        func_8012A828(arg0, D_8018C700);
        *(s32 *)(arg0 + 0x1C) = 8;
        *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
    }

    func_80185E3C((void *)arg0);
}


#include "common.h"

extern s32 func_80185B48(s32 a0);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012B864(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s16 func_80185B20(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern unsigned char D_8018C700[];

void func_801854A4(s32 a0) {
    s32 v0;

    func_80185B48(a0);

    v0 = *(s32 *)(a0 + 0x1C);
    if (v0 != 0) {
        s32 t;
        s32 p;
        s32 ret;

        if (v0 >= 5) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0xA0;
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) += 0x140;
        }

        p = *(s32 *)(a0 + 0x20);
        t = 0x3800 - *(s16 *)(p + 0x1A);
        t = t >> 1;
        t += 0x3800;
        *(s16 *)(p + 0x1C) = t;
        *(s16 *)(p + 0x18) = t;

        ret = func_8012B8E4(a0, 4);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + ret;

        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
    } else {
        s32 old;
        s32 ret;
        s32 p;

        p = *(s32 *)(a0 + 0x20);
        old = *(u16 *)(p + 0x10);
        *(u16 *)(p + 0x10) = 0;
        ret = func_8012B864(a0);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = ret;
        func_8012B2CC(a0);

        func_8012B178(a0, 0xFFE20000);

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = old;
        func_8012B2CC(a0);

        func_8012A828(a0, D_8018C700);

        func_80185B20(a0);

        func_80146A6C(2, (void *)a0, 0, 0, 0, 3,
            ((*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800) & 0xFFF) | 0x30009000);

        *(s32 *)(a0 + 0x1C) = 0xC;
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    }
}


#include "common.h"

extern s32 func_80185B48(s32 a0);
extern s16 func_80185B20(s32 a0);
extern s32 func_8012BE54(s32 a0);
extern s32 func_8012B864(s32 a0);
extern u16 D_80126B94;
extern u16 D_80126B96;
extern s16 D_80126B98;
extern s16 D_80126B9A;
extern void (*D_8018C588[])(void);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_80185620(s32 a0) {
    s16 flag;
    s32 v1;
    s32 t;

    func_80185B48(a0);
    flag = func_80185B20(a0);
    v1 = func_8012BE54(a0);

    if (v1 < 0x4000) {
        D_80126B96 = 0x4004;
        D_80126B94 |= 1;
        D_80126B9A = func_8012B864(a0);
        D_80126B98 = 0x30;
    }

    if (flag == 0) {
        t = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = t;
        if (t == -1 || *(u16 *)(a0 + 0x5E) != 0) {
            func_8012A828(a0, (void *)&D_8018C588);
            *(s32 *)(a0 + 0x1C) = 4;
            *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
        }
    } else {
        func_8012A828(a0, (void *)&D_8018C588);
        *(s32 *)(a0 + 0x1C) = 4;
        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
    }

    {
        s32 r = (rand() & 0xFF) + 0x780;
        s32 p = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        func_80146A6C(2, (void *)a0, 0, 0, 0, 3, ((p + r) & 0xFFF) | 0x30009000);
    }
}


#include "common.h"

extern s32 rand(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_800D0C48(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s16 D_8018C7F0[];




void func_8018574C(s32 arg0) {
    s32 obj;
    s32 rnd;
    s32 idx;
    s32 s2;
    s16 t;
    SVECTOR sv;
    MATRIX mtx;

    obj = *(s32 *)(arg0 + 0x20);
    t = *(u16 *)(obj + 0x1C) - 0x100;
    *(u16 *)(obj + 0x1C) = t;
    *(u16 *)(obj + 0x1A) = t;
    *(u16 *)(obj + 0x18) = t;

    rnd = rand();

    idx = rnd & 0x1E;
    {
        s16 *tp = &D_8018C7F0[idx];
        s2 = func_8012C658(tp[0], tp[1], arg0);
    }
    if (s2 != 0) {
        s32 f = *(u16 *)(s2 + 0xA);
        f = f - 0x10;
        f = f - (*(s32 *)(arg0 + 0x1C) << 2);
        *(u16 *)(s2 + 0xA) = f;

        sv.vx = (rnd & 0xFF) - 0x3FC;
        sv.vy = (s16)rnd >> 3;
        sv.vz = 0;
        RotMatrixYXZ(&sv, &mtx);

        sv.vy = 0;
        sv.vx = 0;
        sv.vz = -0x1A;
        ApplyMatrixSV(&mtx, &sv, &sv);

        *(u16 *)(s2 + 0x12) = sv.vx;
        *(u16 *)(s2 + 0x16) = sv.vy;
        *(u16 *)(s2 + 0x1A) = sv.vz;
    }

    *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) - 1;
    if (*(s32 *)(arg0 + 0x1C) == 0) {
        *(s32 *)(arg0 + 0x1C) = 0x1E;
        func_800D0C48(1);
        *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
    }
}



extern void (*D_8018C830[])(void);

void func_80185898(void *a0) {
    D_8018C830[*(u16 *)((s32)a0 + 0x2)]();
}




/* func_801858D4 -- ov_SC03_002 / ov_SC03_002_jr_8017AE2C
 *
 * func_8012B0B4 (the polar->cartesian helper) is NOT declared anywhere in this TU
 * (grep of the WHOLE file: 0 hits for "8012B0B4", including below the splice point),
 * so the project-canonical engine-core prototype is used VERBATIM and no conflict
 * is possible.  It writes ONE packed u32 (lo half = x, hi half = z) through param_1.
 *
 * Three non-obvious shape choices, all byte-forced:
 *
 *  1. `u32 buf[4]` (16 bytes of locals) -- NOT the 8-byte scratch the sibling
 *     func_8012B0B4 callers use.  frame = args(0x10) + var(0x10) + gp(0xC) = 0x2C
 *     -> rounded 0x30, putting $s0/$s1/$ra at 0x20/0x24/0x28 exactly as the target.
 *     An 8-byte buffer gives 0x28 (§135-6, the dead-locals/frame-padding lever).
 *
 *  2. The two reads of buf must be TWO DISTINCT memory refs (`*(s16*)buf` and
 *     `*(s32*)buf`) AND the store to a0+0x10 must sit BETWEEN the SImode load and
 *     its `>> 16` in SOURCE order.  gcc-2.7.2's combine narrows `(mem:SI >> 16)`
 *     into a sign-extending `lh` at +2 (that is §135-11 / T5 seen from the other
 *     side); can_combine_p refuses to sink the load across the intervening store,
 *     which is what keeps the target's `lw 0x10($sp)` + `sra 16`.  Every ordering
 *     that puts the two shifts adjacent to their loads collapses to 28 ins.
 *
 *  3. The `$2` pin on `hi`.  Post-sched1 the block is
 *        lh(lo) lw(hi) sll(lo) sw(0x10) sra(hi) sll(hi) sw(0x18)
 *     so local-alloc's qty densities (local-alloc.c:1579 qty_compare,
 *     floor_log2(refs)*refs/(death-birth)) are lo = 2*4/5 = 16000 vs
 *     hi = 2*6/9 = 13333 -> lo allocates FIRST and takes $v0, the mirror image of
 *     the target.  sched1 normalises every statement permutation to the same
 *     stream, so the §136 local-variable lever is inert here (8 no-pin variants
 *     tested -- decl order, scope, split temps, s16/u16 lo, `* 0x1000`, an early
 *     `t = a2`: all land on the identical 7-insn $v0<->$v1 permutation).  Pinning
 *     the SImode load to $v0 short-circuits the density contest (RC-3): its init
 *     is `pinned = expr`, so it computes directly into the hard reg with NO extra
 *     move, $v0 is live across lo's whole range so lo is pushed to $v1, and the
 *     shift results are born after $v0 dies and reclaim it.
 */

extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);

void func_801858D4(s32 a0, s16 a1, s16 a2) {
    u32 xz;

    func_8012B0B4(&xz, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), a1 << 4);

    *(s32 *)(a0 + 0x10) = (s16)xz << 12;
    *(s32 *)(a0 + 0x18) = ((s32)xz >> 16) << 12;
    if (a2 != 0) {
        *(s32 *)(a0 + 0x1C) = a2;
    }
}


extern s32 func_8012B6D4(s16 *a0, s16 *a1);

void func_80185948(s16 *a0) {

    extern u8 D_80126B5C;
    extern s16 D_801EB140;
    extern s32 D_801EB14C;
    extern s32 D_801EB154;
    extern u8 D_8018C7AC[];
    extern s16 D_8018C7CC[];
    extern s16 D_8018C7CE[];
    /* The target frame is 0x28 with only $s0/$s1/$ra saved at 0x18/0x1C/0x20, i.e. 8 bytes
       of locals sit below the register save area and are never touched. The original source
       declared a local it no longer uses; the same fossil is visible in the neighbours
       (func_8017C594 carries 16 such bytes). gcc-2.7.2 still reserves the slot. */
    s32 sp10[2];
    s32 a, b, t, r, off, x, y;

    a = (func_8012B6D4((s16 *)&D_80126B5C, &D_801EB140) >> 7) & 0x18;
    b = func_8012B6D4(a0 + 2, &D_801EB140);
    t = a | ((b >> 9) & 7);
    off = D_8018C7AC[t] << 2;
    r = rand();

    /* The struct reads are plain INDIRECT_REFs, not ARRAY_REFs: an `a0[0x46]` here sets
       MEM_IN_STRUCT_P, which lets gcc-2.7.2's true_dependence() drop the dependence against
       the constant-address store and hoist the second `lh` above `sw D_801EB14C`. */
    x = *(s16 *)((s32)a0 + 0x88) + *(s16 *)((u8 *)D_8018C7CC + off) - 0x100;
    x += (r & 0x7F) << 2;
    D_801EB14C = x << 16;

    y = *(s16 *)((s32)a0 + 0x8C) + *(s16 *)((u8 *)D_8018C7CE + off) - 0x100;
    y += (unsigned)(r & 0x7F00) >> 6;
    D_801EB154 = y << 16;
}


extern void func_8012CBA4(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern s32 func_80185D3C(void *a0, s16 a1);

s32 func_80185A24(s32 arg0) {
    s32 ret;
    s32 raw;
    u16 flags;
    s32 h;

    ret = 0;
    raw = ((s32 (*)(s32))func_8012CBA4)(arg0);
    flags = raw;
    if ((raw & 0x6000) != 0x2000) {
        func_8012ADE4((u8 *)arg0);
        if (*(s32 *)(arg0 + 0x1C) > 8) {
            *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) - 8;
        }
    }
    h = (s16)flags;
    if (((h & 0x8000) != 0) || ((flags & 0x6000) != 0x2000)) {
        if (*(s16 *)(arg0 + 0x106) == 0) {
            *(s16 *)(arg0 + 0x106) = (h < 0) ? -0x100 : 0x100;
        }
        if (*(s32 *)(arg0 + 0x1C) > 4) {
            *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) - 4;
        }
        ret = 1;
        *(u16 *)(arg0 + 0x108) = *(u16 *)(arg0 + 0x108) + 1;
    } else {
        *(u16 *)(arg0 + 0x106) = 0;
    }
    return (s16)(ret | ((s32 (*)(void *, s32))func_80185D3C)((void *)arg0, 0));
}


#include "common.h"

extern void func_8012CBA4(s32 a0);

s16 func_80185B20(s32 a0) {
    s32 mask = ((s32 (*)(s32))func_8012CBA4)(a0) & 0x8000;
    s16 v = mask;
    return v;
}


#include "common.h"

/* Already declared at file scope in the destination TU (adopted verbatim):
 *   extern void MoveImage(void *a0, s32 a1, s32 a2);          (line 71)
 *   extern void func_8016AA50(s32 param_1, s32 param_2);      (line 1792)
 * They are repeated here only so this draft compiles standalone. */
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_8016AA50(s32 param_1, s32 param_2);

/* NOTE for banking: src/ov_SC03_007/ov_SC03_007_jr_8017AE2C.c currently carries
 * "extern void func_80185B48(s32 a0);" (file scope, ~line 6008).  The target
 * assembly returns a value in $v0 (0 / 1 / -1), so that extern must become
 * "extern s32 func_80185B48(s32 a0);".  The one call site (func_80186584)
 * discards the result, so the change is behaviour-neutral. */

/* DEF-SIDE ALIAS (§37/§124, applied P31 S55 recovery). The TU declares this
 * `extern void func_80185B48(s32 a0);` at two file-scope points and its one call site discards the
 * result, but the target genuinely sets $v0 on every path — a definition's own signature has no
 * cast escape, so the definition takes a private C identifier bound to the real link name. The TU
 * is left untouched; no rebuild risk to its other functions. */

s32 func_80185B48(s32 a0)
{

    /* House style of this TU: per-function block-scope externs (cf. func_801848BC). */
    extern void func_8012B200(u8 *a0);
    extern void func_8012A828(s32 a0, void *a1);
    extern void (*D_8018C678[])(void);

    s16 rect[4];   /* sp+0x10 : MoveImage RECT { x, y, w, h } */
    s32 ret;
    s32 spd;
    s16 tmr;
    s16 st;
    s32 hp;
    s32 mode;      /* reused: entity mode (0x5E), then the 0xFE sub-state */

    ret = 0;
    mode = *(u16 *)(a0 + 0x5E);
    if (mode != 0) {
        /* 0x60 (s16) * (*(s32*)(a0+0x78))->0x30 (s16), 12.4 -> integer */
        spd = (*(s16 *)(a0 + 0x60) * *(s16 *)(*(s32 *)(a0 + 0x78) + 0x30)) >> 12;
        if (spd <= 0) {
            spd = 1;
        }

        if (mode == 0xA) {
            *(s16 *)(a0 + 0xF4) = 1;
            *(s16 *)(a0 + 0x5E) = 0;
            *(s32 *)(a0 + 0x1C) = 0x14;
            *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFDFF;
            func_8012B200((u8 *)a0);
            func_8012A828(a0, (void *)&D_8018C678);
            *(s16 *)(a0 + 0x2) = 7;
            return -1;
        }

        if (spd != 0) {
            tmr = *(s16 *)(a0 + 0xFA);
            if (tmr == 0) {
                func_8016AA50(a0, spd);

                hp = *(u16 *)(a0 + 0x76) - spd;
                *(s16 *)(a0 + 0x76) = hp;
                if ((s16)hp < 0) {
                    *(s16 *)(a0 + 0x76) = 0;
                }

                *(s16 *)(a0 + 0xFA) = 8;
                st = *(s16 *)(a0 + 0xFE);
                mode = st;
                switch (mode) {
                case 0:
                    if (*(s16 *)(a0 + 0x76) < 0x7D0) {
                        s16 nxt = st + 1;
                        *(s16 *)(a0 + 0xFE) = nxt;
                        rect[0] = 0x2B4;
                        rect[1] = 0x188;
                        rect[2] = 0xC;
                        rect[3] = 0x28;
                        MoveImage(rect, 0x2A8, 0x188);
                    }
                    ret = 1;
                    break;
                case 1:
                    if (*(s16 *)(a0 + 0x76) < 0x640) {
                        st = st + 1;
                        *(s16 *)(a0 + 0xFE) = st;
                        *(s16 *)(a0 + 0xF8) = 5;
                        return -1;
                    }
                    ret = 1;
                    break;
                case 2:
                    if (*(s16 *)(a0 + 0x76) < 0x3E8) {
                        *(s16 *)(a0 + 0xFE) = st + 1;
                    }
                    ret = 1;
                    break;
                default:
                    ret = 1;
                    break;
                }
            } else {
                tmr = tmr - 1;
                *(s16 *)(a0 + 0xFA) = tmr;
                if (tmr == 0) {
                    *(s16 *)(a0 + 0x60) = 0;
                    *(s16 *)(a0 + 0x5E) = 0;
                }
            }
        }
    }

    return ret;
}



s32 func_80185D3C(void *a0, s16 a1)
{
    s32 ret = 0;
    s16 x;
    s16 f;

    x = *(s16 *)((s32)a0 + 6);
    if (x < -381) {
        if (a1 == 0) {
            *(s16 *)((s32)a0 + 6) = -381;
        }
        ret = 1;
    } else if (x >= 382) {
        if (a1 == 0) {
            *(s16 *)((s32)a0 + 6) = 381;
        }
        ret = 1;
    }

    f = a1;
    x = *(s16 *)((s32)a0 + 14);
    if (x < -1661) {
        if (f == 0) {
            *(s16 *)((s32)a0 + 14) = -1661;
        }
        ret = 1;
    } else if (x >= -898) {
        if (f == 0) {
            *(s16 *)((s32)a0 + 14) = -899;
        }
        ret = 1;
    }

    return ret;
}


s32 func_80185DD8(void)
{
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    s16 v1;
    s32 result;

    v1 = *(s16 *)&D_80126B5E;
    result = 0;
    if (v1 < -0x17D) {
        result = 1;
    } else if (v1 >= 0x17E) {
        result = 1;
    }
    v1 = *(s16 *)&D_80126B66;
    if (v1 < -0x67D) {
        result = 1;
    } else if (v1 >= -0x382) {
        result = 1;
    }
    return result;
}


void func_80185E30(void *a0) {
        *(short *)((char *)a0 + 0x2) = *(unsigned short *)((char *)a0 + 0xf8);
    }


void func_80185E3C(void *arg0) {
    s32 neg;
    short val;

    neg = -2;
    val = 0x4000 - ((neg - (s32)*(unsigned short *)((char *)arg0 + 0xA)) << 4);
    arg0 = *(void **)((char *)arg0 + 0xCC);
    arg0 = *(void **)((char *)arg0 + 0xCC);
    *(short *)((char *)arg0 + 0x1A) = val;
    *(short *)((char *)arg0 + 0x18) = val;
}


extern s32 *D_80126B78;
extern u16 D_80126B62;
extern u16 D_80126B94;
extern u16 D_80126B96;
extern s16 D_80126B98;
extern s16 D_80126B9A;
extern s32 func_8012BE54(s32 a0);

void func_80185E68(s32 a0) {
    if ((u16)(D_80126B62 - *(u16 *)(a0 + 0xA) + 0x2F) < 0x6F &&
        func_8012BE54(a0) < 0x3840) {
        D_80126B96 = 0x4002;
        D_80126B94 |= 1;
        D_80126B9A = *(u16 *)((s32)D_80126B78 + 0x12);
        D_80126B98 = 0x40;
    }
}


extern void func_800D0C48(s32 a0);
extern u16 D_80126B5E;
extern u16 D_80126B66;

void func_80185EF8(s32 arg0) {
    s32 dist;

    dist = (*(s16 *)(arg0 + 6) - *(s16 *)&D_80126B5E) * (*(s16 *)(arg0 + 6) - *(s16 *)&D_80126B5E)
         + (*(s16 *)(arg0 + 0xE) - *(s16 *)&D_80126B66) * (*(s16 *)(arg0 + 0xE) - *(s16 *)&D_80126B66);
    if (dist > 0xFFFF) {
        return;
    }
    *(s32 *)(arg0 + 0x1C) = 0x19;
    func_800D0C48(1);
    *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
}


extern int func_8001AAA0(s32 arg0);

void func_80185F84(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x1C) - 1;
    M2C_FIELD(arg0, s32 *, 0x1C) = temp_v0;
    if (temp_v0 == -1) {
        M2C_FIELD(arg0, s32 *, 0x48) = 0x38000;
        M2C_FIELD(arg0, s32 *, 0x1C) = 0x10;
        ((void (*)(s32))func_8001AAA0)(0x9C);
        M2C_FIELD(arg0, s16 *, 0x2) = 0xC;
    }
}


void func_80185FE0(s32 a0) {
    extern void (*D_8018C588[])(void);
    extern s32 func_80185DD8(void);
    extern void func_8012B200(u8 *a0);
    extern void func_8012A828(s32 a0, void *a1);

    if ((s16)func_80185DD8() == 0) {
        *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) | 0x200;
    }
    func_8012B200((u8 *)a0);
    func_8012A828(a0, (void *)&D_8018C588);
    if (*(u16 *)(a0 + 0x5E) == 0 && *(s16 *)(a0 + 0xF4) == 0) {
        *(s32 *)(a0 + 0x1C) = 0x3B;
    } else {
        *(s32 *)(a0 + 0x1C) = 0x1D;
    }
    *(u16 *)(a0 + 2) += 1;
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);

void func_80186074(void *a0) {
    s32 sp10[3];
    extern s32 func_80185D3C(void *a0, s16 a1);
    extern void func_80185E3C(void *a0);
    s32 t;

    t = *(u16 *)((s32)a0 + 0x5E);
    if ((t == 9) | (t == 0x11)) {
        func_8002D4C8(0x829, 0);
        *(u16 *)((s32)a0 + 0x5E) = 0;
        sp10[0] = 0;
        sp10[1] = 0xFFFC0000;
        sp10[2] = 0x30000;
        func_8012B14C((s32)a0, sp10);
        *(s32 *)((s32)a0 + 0x48) = 0x12000;
        *(u16 *)((s32)a0 + 0x108) = 0;
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(u16 *)((s32)a0 + 2) = 8;
    }
    func_80185D3C(a0, 0);
    func_80185E3C(a0);
}


void func_8018611C(void *a0) {
    s32 sp10[3];
    extern s32 func_8012CBCC(s32 a0);
    extern void func_8012B200(u8 *a0);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 func_80185D3C(void *a0, s16 a1);
    extern void func_80185E3C(void *a0);
    extern void (*D_8018C678[])(void);
    s32 t;
    s32 st;

    if (func_8012CBCC((s32)a0) & 0x2000) {
        func_80146A6C(2, a0, 0, 0, 0, 3, 0x30000000);
        t = *(s32 *)((s32)a0 + 0x1C) + 1;
        *(s32 *)((s32)a0 + 0x1C) = t;
        if (t == 1) {
            sp10[0] = 0;
            sp10[1] = 0xFFFD0000;
            sp10[2] = 0x20000;
            func_8012B14C((s32)a0, sp10);
            return;
        }
        func_8012B200((u8 *)a0);
        func_8012A828((s32)a0, (void *)&D_8018C678);
        st = *(u16 *)((s32)a0 + 2);
        st = st + 1;
        *(u16 *)((s32)a0 + 0xF6) = *(u16 *)((s32)a0 + 0x76) - 8;
        *(u16 *)((s32)a0 + 0x98) = 0;
        *(u16 *)((s32)a0 + 2) = st;
        *(s32 *)((s32)a0 + 0x1C) = 0x50;
    }
    func_80185D3C(a0, 0);
    func_80185E3C(a0);
}


#include "common.h"

extern s32 func_80185B48(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012BD14(s32 a0);
extern void func_80185E30(void *a0);
extern void (*D_8018C588[])(void);

void func_80186200(s32 a0) {
    s32 v1;

    func_80185B48(a0);
    if (*(s32 *)(a0 + 0x1C) != 0) {
        if (*(s16 *)(a0 + 0x98) == 0) {
            if (*(s16 *)(a0 + 0x76) < *(s16 *)(a0 + 0xF6)) {
                *(s32 *)(a0 + 0x1C) = 0x14;
            }
            if (*(s32 *)(a0 + 0x1C) == 0x14) {
                *(s16 *)(a0 + 0x98) = 1;
            }
        }
        *(s32 *)(a0 + 0x1C) -= 1;
    } else {
        func_8012A828(a0, (void *)D_8018C588);
        v1 = 0x14 - (*(s16 *)(a0 + 0x104) << 1);
        *(s32 *)(a0 + 0x1C) = v1;
        if (func_8012BD14(a0) <= 0xFFFF) {
            *(s16 *)(a0 + 0x102) = 0xA - *(u16 *)(a0 + 0x104);
        } else {
            *(s16 *)(a0 + 0x102) = 0;
        }
        if (*(s16 *)(a0 + 0x104) != 0) {
            if ((s16)(*(s16 *)(a0 + 0x104) -= 4) < 0) {
                *(s16 *)(a0 + 0x104) = 0;
            }
        }
        func_80185E30((void *)a0);
    }
}


#include "common.h"

extern s32 func_80185B48(s32 a0);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_8012AD80(s32 a0);

void func_80186310(s32 a0) {
    s32 v0;

    func_80185B48(a0);

    v0 = *(s32 *)(a0 + 0x1C);
    if (v0 != 0) {
        s32 t;
        s32 p;

        if (v0 >= 5) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) - 0x800;
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) + 0xC00;
        }

        p = *(s32 *)(a0 + 0x20);
        t = 0x3800 - *(s16 *)(p + 0x1A);
        t = t >> 1;
        t += 0x3800;
        *(s16 *)(p + 0x1C) = t;
        *(s16 *)(p + 0x18) = t;

        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
    } else {
        *(s32 *)(a0 + 0x14) = 0xFFB80000;
        *(s32 *)(a0 + 0x48) = 0x38000;
        func_80146A6C(2, (void *)a0, 0, 0, 0, 3, 0x30000000);
        func_8012AD80(a0);
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    }
}


extern s32 func_80185B48(s32 a0);
extern void func_80185E68(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80185E30(void *a0);
extern void (*D_8018C588[])(void);

void func_80186408(s32 a0) {
    s32 v0;

    func_80185B48(a0);

    v0 = *(s32 *)(a0 + 0x1C);
    if (v0 != 0) {
        s32 t;
        s32 p;

        func_80185E68(a0);

        v0 = *(s32 *)(a0 + 0x1C);
        if (v0 >= 5) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) - 0x800;
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) + 0x800;
        }

        p = *(s32 *)(a0 + 0x20);
        t = 0x3800 - *(s16 *)(p + 0x1A);
        t = t >> 1;
        t += 0x3800;
        *(s16 *)(p + 0x1C) = t;
        *(s16 *)(p + 0x18) = t;

        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
    } else {
        func_8012A828(a0, (void *)D_8018C588);
        func_80185E30((void *)a0);
    }
}


#include "common.h"

extern s32 func_80185B48(s32 a0);
extern s16 func_80185B20(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8012B200(u8 *a0);
extern void func_80185E30(void *a0);

void func_801864D8(s32 a0) {
    func_80185B48(a0);
    func_80185B20(a0);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0xA0;
    *(s32 *)(a0 + 0x18) >>= 1;
    func_80146A6C(2, (void *)a0, 0, 0, 0, 3,
        ((*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF) | 0x30009000));
    if (--*(s32 *)(a0 + 0x1C) == 0) {
        func_8012B200((u8 *)a0);
        func_80185E30((void *)a0);
    }
}


#include "common.h"

extern s32 func_80185B48(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8012AD80(s32 a0);

void func_80186584(s32 a0) {
    s32 v0;

    func_80185B48(a0);

    v0 = *(s32 *)(a0 + 0x1C);
    if (v0 != 0) {
        s32 t;
        s32 p;

        if (v0 >= 5) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) - 0x800;
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) + 0xC00;
        }

        p = *(s32 *)(a0 + 0x20);
        t = 0x3800 - *(s16 *)(p + 0x1A);
        t = t >> 1;
        t += 0x3800;
        *(s16 *)(p + 0x1C) = t;
        *(s16 *)(p + 0x18) = t;

        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
    } else {
        *(s32 *)(a0 + 0x14) = 0xFFB80000;
        *(s32 *)(a0 + 0x48) = 0x38000;
        func_80146A6C(2, (void *)a0, 0, 0, 0, 3, 0x30000000);
        func_8012AD80(a0);
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    }
}


extern s32 func_80185230(void);
    void func_8018667C(void) {
        func_80185230();
    }


#include "common.h"

extern s32 func_80185B48(s32 a0);
extern void func_80185E68(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80185E30(void *a0);
extern void (*D_8018C588[])(void);

void func_8018669C(s32 a0) {
    s32 v0;

    func_80185B48(a0);

    v0 = *(s32 *)(a0 + 0x1C);
    if (v0 != 0) {
        s32 t;
        s32 p;

        func_80185E68(a0);

        v0 = *(s32 *)(a0 + 0x1C);
        if (v0 >= 5) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) - 0x800;
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) + 0x800;
        }

        p = *(s32 *)(a0 + 0x20);
        t = 0x3800 - *(s16 *)(p + 0x1A);
        t = t >> 1;
        t += 0x3800;
        *(s16 *)(p + 0x1C) = t;
        *(s16 *)(p + 0x18) = t;

        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 1;
    } else {
        func_8012A828(a0, (void *)D_8018C588);
        func_80185E30((void *)a0);
    }
}


extern void MoveImage(void *a0, s32 a1, s32 a2);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);

void func_8018676C(s32 a0) {
    s16 rect[4];
    s32 v0;
    s32 v1;

    v0 = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), 0, 4);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + v0;
    v1 = *(s32 *)(a0 + 0x1C);
    *(s32 *)(a0 + 0x1C) = v1 + 1;
    if (v1 >= 0x15) {
        rect[0] = 0x248;
        rect[1] = 0x1C0;
        rect[2] = 0xC;
        rect[3] = 0x28;
        MoveImage(rect, 0x2A8, 0x188);
        *(u16 *)(a0 + 0x2) += 1;
        *(s32 *)(a0 + 0x1C) = 0x28;
    }
}




extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_800D0CE0(void);
extern void (*D_8018C610[])(void);

void func_80186818(s32 a0)
{
    s32 s0;
    s32 v0;
    u16 *p;


    if (*(s32 *)(a0 + 0x1C) < 0xF) {
        v0 = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), 0xA00, 4);
        p = *(u16 **)(a0 + 0x20);
        p[9] = p[9] + v0;
    }

    v0 = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v0;
    if (v0 != 0) {
        return;
    }

    func_8012B178(a0, 0xFFF40000);
    func_8012A828(a0, (void *)D_8018C610);
    *(s32 *)(a0 + 0x1C) = 0x2D;
    func_800D0CE0();
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
}


extern void func_8002AC00(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8012C218(void *a0);
extern void func_8002A04C(s32 a0);
extern void func_8012AD80(s32 a0);

void func_801868C8(void *a0)
{
    if (--*(s32 *)((s32)a0 + 0x1C) != -1) {
        func_8012AD80((s32)a0);
        if (*(u32 *)((s32)a0 + 0x94) < 0xB) {
            *(u32 *)((s32)a0 + 0x94) += 1;
        }
        if ((*(s32 *)((s32)a0 + 0x1C) & 3) == 0) {
            func_80146A6C(2, (void *)a0, 0, 0, 0, 2, 0);
        }
    } else {
        func_8002AC00(0x27);
        if (*(s32 *)((s32)a0 + 0x78) != 0) {
            func_8002A04C((s32)a0);
        }
        func_8012C218(a0);
    }
}



extern void (*D_801E4D70[])(void);

void func_80186984(void *a0) {
    D_801E4D70[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: iv-combine
// @unstuck(P36): none — MATCH (49 ins). gcc folds (v0+0x1800)-0x1000 -> v0+0x800; re-tie barrier on the WORKING reg v0 (NOT a saved local) forces the target chain v0=base+0x1800; s2=copy; v0-=0x1000; s1=v0<<5. NO register pins (pins re-trigger the lhu/lh dual-load CSE collapse and shrink the frame; natural alloc gives s0-s3 + frame 0x38).
extern int rand(void);
extern u8 *func_8012913C(s32 a0);

extern unsigned short D_801E4D50[];

void func_801869C0(s32 param_1, s32 param_2)
{
    int s3;
    unsigned short s0;
    int s1;
    s16 v0;
    int iVar3;

    s0 = D_801E4D50[*(short *)(param_1 + 0xfc)];
    s3 = param_2;
    if (((short *)D_801E4D50)[*(short *)(param_1 + 0xfc)] == 0) {
        *(short *)(param_1 + 0xfc) = 0;
        s0 = D_801E4D50[0];
    }
    *(short *)(param_1 + 0xfc) = *(short *)(param_1 + 0xfc) + 1;
    v0 = (rand() & 3) * 0x400 + 0x1800;
    s1 = (v0 - 0x1000) * 0x20;
    iVar3 = ((int (*)(int))func_8012913C)(4);
    if (iVar3 != 0) {
        *(short *)(iVar3 + 6) = s3;
        *(short *)(iVar3 + 0xa) = s0;
        *(short *)(iVar3 + 0xe) = 0;
        *(int *)(iVar3 + 0x10) = s1;
        *(short *)(iVar3 + 0x2c) = (v0);
    }
}



extern void (*D_801E4D84[])(void);

void func_80186A84(void *a0) {
    D_801E4D84[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: regalloc-order
// @unstuck(P36): none — MATCH

extern void func_801869C0(s32, s32);
extern s32 func_8012AD50(void *a0);

void func_80186AC0(int param_1) {
    short uVar1;

    *(short *)(param_1 + 0xfc) = 0;
    *(int *)(param_1 + 0x1c) = 1;
    uVar1 = *(unsigned short *)(param_1 + 0x70) & 7;
    *(short *)(param_1 + 0xfe) = (uVar1 < 2) ? 0x1e : 0xf;
    if (uVar1 != 0) {
        func_801869C0(param_1, -0x80);
        func_801869C0(param_1, -0x30);
        func_801869C0(param_1, 0x20);
        func_801869C0(param_1, 0x70);
        func_801869C0(param_1, 0xc0);
    }
    if (1 < uVar1) {
        func_801869C0(param_1, -0x58);
        func_801869C0(param_1, -0x8);
        func_801869C0(param_1, 0x48);
        func_801869C0(param_1, 0x98);
        func_801869C0(param_1, 0xe8);
    }
    ((void (*)(int))func_8012AD50)(param_1);
}



// @class: regalloc-order
// @unstuck(P36): none — MATCH (param_1 naturally lands in $s0 across the call, mirrors sibling func_80184AEC)

extern s32 func_8012BEE8(s32 a0);
extern void func_801869C0(s32, s32);

void func_80186BA8(s32 arg0) {
    if (func_8012BEE8(arg0)) {
        *(s32 *)(arg0 + 0x1c) = (s32)*(s16 *)(arg0 + 0xfe);
        func_801869C0(arg0, 0x110);
    }
}



// @class: plumbing
// @unstuck(P36): none — MATCH (expected)
extern void func_8001CB00(int param_1, void *src, int len, int n);

extern unsigned char D_801E4D78;

void func_80186BE8(int param_1)
{
    unsigned short uVar1;
    int iVar2;

    iVar2 = *(int *)(param_1 + 0x20);
    func_8001CB00(iVar2, &D_801E4D78, 0x280, 0x100);
    *(unsigned int *)(iVar2 + 4) = *(unsigned int *)(iVar2 + 4) | 0x70000000;
    uVar1 = *(unsigned short *)(param_1 + 0x2c);
    *(unsigned char *)(iVar2 + 0x27) = 0x9e;
    *(unsigned short *)(iVar2 + 0x2c) = 4;
    *(unsigned short *)(iVar2 + 0x1c) = uVar1;
    *(unsigned short *)(iVar2 + 0x1a) = uVar1;
    *(unsigned short *)(iVar2 + 0x18) = uVar1;
    *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    return;
}



extern void func_801292C8(u8 *a0);

void func_80186C70(u8 *a0) {
    *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x4) - *(s32 *)(a0 + 0x10);
    if (*(s16 *)(a0 + 0x6) < -0x110) {
        func_801292C8(a0);
    }
}



extern void (*D_801E4DD8[])(void);

void func_80186CB8(void *a0) {
    D_801E4DD8[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80187214(s32 arg0);
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_8018726C(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186CF4(s32 a0) {
    extern u8 D_801E4D8C[];
    extern u8 D_801E4D98[];
    s32 s0;
    u16 t;
    u16 u;
    u16 v;

    s0 = func_80187214(a0);
    if ((s0 == 1) || (s0 = ((s32 (*)(void))func_8012C194)(), s0 == 0)) {
        ((void (*)(s32))func_8012CAE4)(a0);
    } else {
        *(s32 *)(a0 + 0xCC) = s0;
        func_8001CC3C(s0, (s32)D_801E4D8C, 0x214, 0x168);
        *(s32 *)(s0 + 0x4) = 0x50000000;
        *(u8 *)(s0 + 0x27) = 0x24;
        func_80128EA8(s0, a0 + 0xDC, (s32)D_801E4D98);
        func_8018726C(a0);
        *(u16 *)(s0 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA);
        t = *(u16 *)(a0 + 0xE);
        *(u16 *)(s0 + 0x1A) = 0x2000;
        *(u16 *)(s0 + 0x18) = 0x2000;
        *(u16 *)(s0 + 0x2C) = 0xC010;
        *(u16 *)(s0 + 0xC) = t;
        v = *(u16 *)(a0 + 0x2) + 1;
        u = *(u16 *)(*(s32 *)(a0 + 0x64) + 0x36);
        *(s32 *)(a0 + 0x1C) = 0x180;
        *(u16 *)(a0 + 0x2) = v;
        *(u16 *)(a0 + 0x10A) = u;
        func_8002D4C8(0xAA0, 0);
    }
}




extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8018726C(s32 arg0);
extern void func_801872E8(void *arg0);

void func_80186DF0(s32 arg0) {
    s32 p;
    s32 q;
    s32 r;
    s32 t0;
    s32 u0;
    s32 t1;
    s32 u1;
    s32 t2;
    s32 t3;
    s32 t4;
    u16 v;
    u16 w;

    p = *(s32 *)(arg0 + 0x64);
    if (*(s16 *)(arg0 + 0x10A) == *(s16 *)(p + 0x36) && *(s16 *)(p + 0x76) > 0) {
        if (*(s32 *)(arg0 + 0x1C) == (*(s32 *)(arg0 + 0x1C) / 0x30) * 0x30 &&
            *(u8 *)(p + 0xC1) == 0) {
            *(s16 *)(p + 0x60) = 0xA;
            *(u16 *)(p + 0x5C) |= 1;
            v = *(u16 *)(*(s32 *)(p + 0x20) + 0x12);
            *(s16 *)(p + 0x5E) = 1;
            *(u16 *)(p + 0x62) = v + 0x800;
            *(u16 *)(p + 0x7C) = *(u16 *)(arg0 + 0x6);
            *(u16 *)(p + 0x7E) = *(u16 *)(arg0 + 0xA);
            *(u16 *)(p + 0x80) = *(u16 *)(arg0 + 0xE);
        }
        if ((*(s32 *)(arg0 + 0x1C) & 7) == 0) {
            q = func_80132EF4(arg0, 0x22);
            if (q != 0) {
                t0 = rand();
                u0 = *(u16 *)(q + 0x6) - 0x10;
                *(u16 *)(q + 0x6) = u0 + (t0 & 0x1F);
                t1 = rand();
                u1 = *(u16 *)(q + 0xE) - 0x10;
                *(u16 *)(q + 0xE) = u1 + (t1 & 0x1F);
                *(u16 *)(q + 0xA) -= 0x20;
                t2 = rand();
                *(s32 *)(q + 0x14) = -0x40000 - ((t2 % 3) << 16);
                t3 = rand();
                t4 = rand();
                *(s16 *)(q + 0x34) = ((t3 % 0x1800 + 0x1000) & ~0xF) | (t4 & 1);
                *(u16 *)(*(s32 *)(q + 0x20) + 0x2C) = 0xC010;
                *(s32 *)(*(s32 *)(q + 0x20) + 0x4) |= 0x40000000;
            }
        }
        r = *(s32 *)(arg0 + 0xCC);
        if (r != 0) {
            func_80128ED8((void *)r, (void *)(arg0 + 0xDC));
            func_8018726C(arg0);
            *(u16 *)(r + 0x8) = *(u16 *)(arg0 + 0x6);
            *(u16 *)(r + 0xA) = *(u16 *)(arg0 + 0xA);
            w = *(u16 *)(arg0 + 0xE);
            *(u16 *)(r + 0x18) += 0x15;
            *(u16 *)(r + 0x1A) += 0x15;
            *(u16 *)(r + 0xC) = w;
        }
        if (*(u16 *)(p + 0x5E) == 0x23) {
            *(u16 *)(arg0 + 0x2) += 1;
        }
        if (func_8012BEE8(arg0) == 0) {
            return;
        }
    }
    func_801872E8((void *)arg0);
}




extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8018726C(s32 arg0);
extern void func_801872E8(void *arg0);

void func_80187080(s32 arg0) {

    extern u16 D_800B99DA;
    s32 p;
    s32 q;
    s32 t0;
    s32 u0;
    s32 t1;
    s32 u1;
    s32 t2;

    p = *(s32 *)(arg0 + 0xCC);
    if (p != 0) {
        func_80128ED8((void *)p, (void *)(arg0 + 0xDC));
        func_8018726C(arg0);
        *(u16 *)(p + 0x8) = *(u16 *)(arg0 + 0x6);
        *(u16 *)(p + 0xA) = *(u16 *)(arg0 + 0xA);
        *(u16 *)(p + 0xC) = *(u16 *)(arg0 + 0xE);
        *(u16 *)(p + 0x18) -= 0x200;
        *(u16 *)(p + 0x1A) -= 0x200;
        if (*(s16 *)(p + 0x18) >= 0) {
            if (D_800B99DA % 5 == 0) {
                q = func_80132EF4(arg0, 0x22);
                if (q != 0) {
                    t0 = rand();
                    u0 = *(u16 *)(q + 0x6) - 0x10;
                    *(u16 *)(q + 0x6) = u0 + (t0 & 0x1F);
                    t1 = rand();
                    u1 = *(u16 *)(q + 0xE) - 0x10;
                    *(u16 *)(q + 0xE) = u1 + (t1 & 0x1F);
                    *(u16 *)(q + 0xA) -= 0x20;
                    t2 = rand();
                    *(s32 *)(q + 0x14) = -0x40000 - ((t2 % 4) << 16);
                    *(s16 *)(q + 0x34) = rand() % 0x1800 + 0x2000;
                    *(u16 *)(*(s32 *)(q + 0x20) + 0x2C) = 0xC010;
                }
            }
            return;
        }
    }
    func_801872E8((void *)arg0);
}



/* func_80187214 — "is another entity of type 0x35C sharing my 0x64 owner?"
 *
 * Walks the 0x60-entry entity table at D_801202A0 (stride 0x10C) with an int
 * counter (the target keeps the count in $a2 and `slti ...,0x60`, so it is a
 * counted loop, NOT the D_80126720 pointer-bound idiom the sibling walkers
 * use).  Returns 1 for the first entry whose u16 kind == 0x35C, whose word at
 * 0x64 equals the caller's word at 0x64, and which is not the caller itself.
 */
s32 func_80187214(s32 arg0) {
    extern u8 D_801202A0[];
    u8 *p;
    s32 i;

    p = D_801202A0;
    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)p == 0x35C && *(s32 *)(arg0 + 0x64) == *(s32 *)(p + 0x64) &&
            arg0 != (s32)p) {
            return 1;
        }
        p += 0x10C;
    }
    return 0;
}



extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8018726C(s32 arg0) {
    s32 buf[8];
    u16 out[4];
    s32 p;

    p = *(s32 *)(arg0 + 0x64);
    if (*(s16 *)(p + 0x36) == *(s16 *)(arg0 + 0x10A)) {
        func_8012EC04(p, *(s16 *)(arg0 + 0xFC), buf);
        ((void (*)(s32 *, s32, u16 *))func_8012F14C)(buf, arg0 + 0x88, out);
        *(u16 *)(arg0 + 0x6) = out[0];
        *(u16 *)(arg0 + 0xA) = out[1];
        *(u16 *)(arg0 + 0xE) = out[2];
    }
}



/* func_801872E8 — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_801872E8(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}



/* Sibling shape: DEFINE_func_80143BDC() in src/shared/engine_core.h (cookbook §71) */

extern s32 func_8012C51C(void *a0, s32 a1);


void func_8018732C(s32 a0, u16 *a1, s16 a2) {
    struct S80190C84 sp;
    u16 t;
    sp.f0 = a1[0];
    sp.f2 = a1[1];
    t = a1[2];
    sp.f6 = 0x35C;
    sp.fA = 0;
    sp.f8 = 0;
    sp.fE = a2;
    sp.f10 = 0;
    sp.fC = 0x7FFF;
    sp.f4 = t;
    func_8012C51C(&sp, a0);
}






