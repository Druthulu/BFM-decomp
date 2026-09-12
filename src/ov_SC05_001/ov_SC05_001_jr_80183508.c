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
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80187FA0;
extern u8 D_80187F10;
extern u8 D_80187EEC;
extern u8 D_80187EC8;
extern u8 D_80187F7C;
extern u8 D_80187F58;
extern u8 D_80187F34;
extern u8 D_80187EA4;
extern void func_80145934(void);
extern u8 D_80188030;
extern u8 D_8018800C;
extern u8 D_80187FE8;
extern u8 D_80187FC4;
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
extern unsigned char D_80187428[];
extern unsigned char D_80187458[];
extern unsigned char D_801874A8[];
extern unsigned char D_801874D8[];
extern unsigned char D_80187508[];
extern void func_80145EE8(s32 param_1);
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_80146074(void);
extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0();
extern void func_8014607C(void);
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
extern void (*D_80187558[])(void *);
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
extern s32 D_80187620[];
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
extern u8 D_801876A8[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_801876B0;
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
extern int D_801B4A00;
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
extern s32 D_801B4A04;
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
extern s32 D_801876E0;
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
extern void (*D_80187788[])(void);
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
extern void (*D_801877AC[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018779C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_801877C0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_801877CC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801877DC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801877F4[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801877E4;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80187808[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80187824[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80187814;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80187838[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018784C[])(void);
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
extern s32 D_80187860;
extern void (*D_80187888[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80187868;
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
extern int (*D_801878D4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801878D8[])(void);
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
extern unsigned short D_80187D3C[];
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
extern void (*D_80187D4C[])(void);
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
extern int D_801B4A38;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80187D74[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80187D54;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80187D64;
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
extern void (*D_80187DB4[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80187DBC[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80187D88;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80187DC8[])(void);
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
extern u8 D_80187D98;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801B4A40;
extern s32 D_801B4A4C;
extern s32 D_801B4A50;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80187E04[])(s32 *);
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
extern s32 D_80187DD8[];
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
extern s32 D_801B4A48;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80188054[])(void);
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
extern char D_80187E74[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_801880F8[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018824C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80188068;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80188254[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80188078;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80188098;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018825C[])(void);
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
extern void (*D_80188284[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80188290[])(void);
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
extern void (*D_80188104[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80188334;
extern void func_8015D380(s32 a0);
extern unsigned char D_80187418[];
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
extern unsigned char D_80188348[];
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
extern s8 D_80188384[];
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
extern u16 D_801883CC;
extern u16 D_801883CE;
extern u16 D_801883D0;
extern s32 D_801883D4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_801883DC;
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
extern int D_801880E8;
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
extern unsigned int D_80188460[];
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
extern void (*D_80188510[])(void);
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
extern u16 D_80188540[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_801885A4;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801B4A58[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_801885C8[])(void);
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
extern int D_801B4AB0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80188610[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80188600;
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
extern char D_801B421C[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80188618[])(void);
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
extern void (*D_8018866C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80188634;
extern s16 D_80188668;
extern s16 D_80188666;
extern s16 D_80188664;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80188678[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801B4B10;
extern u8 D_801B4B11;
extern u8 D_801B4B12;
extern u8 D_801B4B13;
extern u8 D_801B4B14;
extern u8 D_801B4B15;
extern u8 D_801B4B16;
extern u8 D_801B4B17;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80188688[])(void);
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
extern s32 D_801B4B50;
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
extern void (*D_801886CC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80188748[];
extern s32 D_80188768[];
extern u8 D_801887E4[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80188804[];
extern u8 D_80188824[];
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
extern void (*D_801888C0[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018893C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801B422C;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80188948[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80188950[])(void);
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
extern void (*D_80188A18[])(void);
extern void func_80166618(void *a0);
extern void (*D_80188A28[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994(s32 param_1, int param_2, int param_3, int param_4);
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80188A38[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80188A44[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_801889A4[];
extern u8   D_801889B8[];
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
extern void (*D_80188A5C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80188A64[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80188A6C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80188A74[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80188A7C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80188A84[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80188A8C[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80188B40[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80188B48[])(void);
extern void func_80169F00(void *a0);
extern char D_80188AF8[];
extern char D_80188AB8[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80188B80[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80188B8C[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80188BD4[])(void);
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
extern void (*D_80188C50[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801B4E70;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80188C44[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80188C88[];
extern unsigned short D_80188C90[];
extern unsigned short D_80188C98[];
extern unsigned char D_801B4E78[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801B4E70;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80188CA0[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801B4FAC;
extern M2C_UNK D_801B4FB0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801B4F38;
extern void (*D_80188CD0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801B4FB4[];
extern u8 D_801B4FBC[];
extern u8 D_801B4F6C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80188CD8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80188CF4[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80188CFC[])(void);
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
extern void (*D_80188D64[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80188D08;
extern u8 D_80188D14;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80188D98[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80188DA0[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80188DF4[])(void);
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
extern u16 D_80188E28[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80188E18[];
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
extern s32 D_80188E44;
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
extern void (*D_80188EBC[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80188EC4[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80188ECC[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80188ED4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80188EDC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80188EE4[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80188EF0[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80188EFC[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80188F08[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80188F18[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80188F28[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80188F30[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80188F38[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80188F40[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80188F48[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80188F50[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80188F58[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80188F60[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80188F68[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80188F70[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80188F78[])(void);
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
extern void (*D_80188F80[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80188F88[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80188F90[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80188F98[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80188FA0[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80188FA8[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80188FB0[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80188FB8[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80188FC0[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80188FC8[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80188FD0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80188FD8[])(void);
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
extern void (*D_8018901C[])(void);
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
extern M2C_UNK D_80188FE0;
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
extern void (*D_8018904C[])(void);
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
extern void (*D_80189088[])(void);
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
extern void (*D_801890E0[])();
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
extern void (*D_801890F0[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_801890F8[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_80189260[])();
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
extern void (*D_8018926C[])();
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
extern M2C_UNK D_801B4474;
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
extern s16 D_801B5F90;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801B56F0;
extern short D_801B6004;
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
extern s32 D_801B5B1C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801B5B44;
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
extern s16 D_801B5B00;
extern s32 func_8017A3B0(void);
extern short D_801B5B3C;
extern short D_801B5B38;
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
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801B5B04;
extern u16 D_801B5B84;
extern u16 D_801B5B86;
extern u16 D_801B5B88;
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
extern s16 D_801B5B7C;
extern s16 D_801B5B7E;
extern s16 D_801B5B80;
extern s16 D_801B5B74;
extern s16 D_801B5B76;
extern s16 D_801B5B78;
extern void func_8017B7A8(void);
extern s16 D_801B5B94;
extern s16 D_801B5B96;
extern s16 D_801B5B98;
extern s16 D_801B5B9C;
extern s16 D_801B5B9E;
extern s16 D_801B5BA0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801B5B8C;
extern short D_801B5B8E;
extern short D_801B5B90;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801B5B24;
extern SV4 D_801B5B2C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801B5B4C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801B5B48)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80189448[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BEBC(s32 arg0);
extern void func_8017CD9C(void *a0);
extern void (*D_80189480[])(void);
extern void func_8017CDD8(void *a0);
extern void func_8017CE14(void *a0);
extern void func_8017D0F8(int);
extern void func_8017CE64(int param_1);
extern void func_8017CEC0(Ent_8017BFE0_8017CEC0 *param_1);
extern void func_8017CF44(void *a0);
extern void func_8017D0AC(int param_1);
extern void func_8017D0F8(int param_1);
extern void (*D_80189494[])(void);
extern void func_8017D404(void *a0);
extern void func_8017D440(void *a0);
extern void func_8017D480(void *a0);
extern void func_8017D4F0(void *a0);
extern void func_8017D57C(void *a0);
extern void func_8017D650(void *a0);
extern void (*D_801894A8[])(void);
extern void func_8017D6A4(void *a0);
extern void func_8017D6E0(void *a0);
extern void func_8017D7F0(void *a0);
extern void func_8017D794(void *a0);
extern void func_8017D960(s32 param_1, s32 param_2);
extern void func_8012CAE4(void *a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern void func_8017DA90(s32 a0);
extern void func_8017D960(s32 a0, s32 a1);
extern void func_8012BD14(s32 a0);
extern void func_8017DE1C(s32 a0);
extern void func_8017E094(s32 a0);
extern s16 func_80128CFC(u16 a0);
extern void func_8017E1DC(s32 a0);
extern void (*D_801895C0[])(void);
extern void func_8017E35C(void *a0);
extern void func_8017E398(void);
extern void func_8017E3E4(void *a0);
extern void func_8017E4D8(void *a0);
extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8017E558(s32 a0);
extern void func_8017E60C(s32 a0);
extern void func_8017E678(s32 a0);
extern void func_8012C218(void*);
extern void func_8017E704(void);
extern void func_8017E724(s32 a0);
extern void (*D_8018963C[])(void);
extern void func_8017E778(void *a0);
extern void func_8017E9A8(void);
extern s32 func_8017E7B4(s32 a0);
extern int func_8017E7F8(void);
extern void func_8017E9D0(void);
extern s32 func_8017E81C(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017E85C(u8 *a0);
extern void func_800D1EBC(void);
extern void func_8017E8D8(s32 arg0);
extern void (*D_80189650[])(void);
extern void func_8017E8F8(void *a0);
extern s32 func_8017E934(s32 a0);
extern void (*D_8018967C[])(void);
extern void func_8017EAB0(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8018115C(u16 *r, s16 *m);
extern void func_8017EC3C(s32 param_1, s32 param_2, s16 *param_3);
extern s32 func_800495EC(s32 a0, s32 a1, s32 a2);
extern u32 func_8017EF88(s16 *param_1, s16 *param_2, s16 *param_3);
extern void (*D_80189740[])(void);
extern void func_8017F3A8(void *a0);
extern void (*D_80189848[])(void);
extern void func_8017F928(void *a0);
extern void (*D_8018989C[])(void);
extern void func_8017FAC8(void *a0);
extern void func_8017FFF8(void *a0);
extern void (*D_80189AE0[])(void);
extern void func_80180224(void *a0);
extern void (*D_80189AF8[])(void);
extern void func_80180260(void *a0);
extern void (*D_80189B18[])(void);
extern void func_801803F8(void *a0);
extern void func_801807E8(void);
extern void func_801807F0(void);
extern void func_8018086C(void);
extern s32 D_80126CD4;
extern void func_8018098C(s32 arg0);
extern void func_80180AA4(void *a0);
extern s32 func_80180AAC(void);
extern void func_80029124(s32 arg0, s32 arg1);
extern void func_80180AB4(u8 *a0);
extern void (*D_801A8434[])(void);
extern void func_80180AEC(void *a0);
extern void func_80180B70(s32 a0);
extern void func_80180B28(s32 a0);
extern void (*D_801A849C[])(void);
extern void func_80180D78(void *a0);
extern void func_80180FFC(s32 param_1, s32 *param_2);
extern void func_80180F98(s32 a0, void *a1, void *a2);
extern void func_80180FFC(s32 param_1, s32 *param_2);
extern s16 func_80181340(u32 a0);
extern s32 func_801813FC(u32 a0v);
extern void (*D_801A8E54[])(void);
extern void func_801814A8(void *a0);
extern void func_8012A828(s32 *a0, s32 a1);
extern void func_80181874(short *a0);
extern s32 func_8012BCCC(s32 a0);
extern void func_8001C924(s32 a0, void *a1);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_801818A4(s32 a0);
extern s32 func_8012BEE8(s32 arg);
extern void func_801819E8(void *a0);
extern void func_80182944(s32 a0);
extern void func_80181C98(s32 a0);
extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern void func_80181E08(void *a0);
extern void func_80181F94(s32 arg0);
extern void func_801822B0(s32 param_1);
extern void func_80182354(s32 *a0);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_80182364(s32 param_1);
extern void func_80182530(s32 param_1);
extern void func_80182908(s32 arg0);
extern void func_80182FB4(s32 param_1);
/* ==== end §8b carried decl layer ==== */


/* func_80183508 — ov_SC03_108 `_jr_8017BEBC`, 231 ins, frame 0x18.  MATCH (match_one, masked).
 *
 *   python3 tools/match_one.py func_80183508 --c .run/wave3/func_80183508/func_80183508.c \
 *       --asm-subdir asm/ov_SC03_108/nonmatchings/ov_SC03_108_jr_8017BEBC
 *
 * Enemy state machine.  5-entry jtbl_801A04F8 (asm/ov_SC03_108/data/tail18.data.s:16)
 * over `*(u16 *)(param_1 + 0x34)`, minval 0 / maxval 4, no holes, default -> TAIL.
 * Shape template: func_8017F2E8 in this SAME TU (src/ov_SC03_108/ov_SC03_108_jr_8017BEBC.c:3752)
 * — same `if (*(s16 *)(p+0xa) >= 0x10) { func_80184580(p); return; }` guard, same
 * `switch (*(u16 *)(p+0x34))` dispatch, same 0x100000 clamp tail, same goto-label idiom.
 *
 * The mid-function `jr $v0` at 8017F894 IS the jump table; the four labels that are
 * reached from more than one arm (STATE4 @8017FADC, EXIT_808B4 @8017FB68,
 * SET_HIT @8017FB80, L_B88 @8017FB88) must be written as gotos INSIDE the switch
 * body, at exactly these source positions, or the block order drifts.
 *
 * THE ONE NON-OBVIOUS BIT — the signed-direction compare at 8017F938..8017F968.
 *   Both arms load [0xa] first, then [0xfe], and both emit the *identical*
 *   `slt $v0, $v0, $v1`; only the two `lh` destinations swap.  That fixes the
 *   source shape as  arm1 = `a <  b`  /  arm2 = `a >  b`  (operands evaluated
 *   left-to-right in both; GT is canonicalised to `slt dst, op1, op0`).  Writing
 *   `b < a` for arm2 loads [0xfe] first — wrong.
 *   With the plain shape, local-alloc gives BOTH arms a->$v1 / b->$v0; the target
 *   wants a->$v0 / b->$v1 in the `< 0` arm only (3-ins REGALLOC-PERM residual).
 *   Measured, none of these move it: ternary, `!(a >= b)`, casts to s32, a temp
 *   for `a` alone, two temps, function-scope temps, a temp in the *other* arm,
 *   swapping the local decl order, or inverting the outer test (that one flips
 *   bgez->bltz).  `b > a` in arm1 gets the registers right but swaps the two
 *   loads (2-ins SCHEDULE residual) and a barrier on it does not recover them.
 *   What works is lengthening `a`'s live range past the second load with the
 *   TU's own no-op asm barrier — the same lever func_8017F2E8 already uses at
 *   line 3823 (`__asm__ __volatile__("" : "=r"(sum) : "0"(sum));`).  Register
 *   pins (`register s32 __asm__("$2")/("$3")`) also match, but the barrier is
 *   the weaker, in-TU-idiomatic tool, so it is what ships.
 *
 * INTEGRATION SURFACE (§161c) — every block-scope decl below AGREES with the host TU:
 *   func_80184580  file-scope  `void (void *)`      TU:4132   (after this fn — decl needed)
 *   func_8012B178  block-scope `void (s32,s32)`     TU:3755
 *   func_8012CBA4  block-scope `s32  (s32)`         TU:3756/3962
 *   func_8012B23C  block-scope `void (s32)`         TU:3761/3963
 *   func_80143B6C  block-scope `s32  (s32,s32)`     TU:3762/3965
 *   func_80131E00  block-scope `void (s32,s32)`     TU:3763/3966
 *   func_8012B2CC  FILE-scope  `void (s32)`         TU:2536/3420  (already visible; identical)
 *   func_8012CBF4 / func_8012CBCC / func_8012D624 / D_80126B96 / D_80126B9A
 *       do not appear in this TU at all — new decls, no conflict.  The
 *       D_80126B96 `u16` / D_80126B9A `s16` spellings are copied verbatim from
 *       the already-matched siblings (src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c:3499
 *       and :3918-area).
 */

void func_80183508(s32 param_1)
{
    extern void func_80184580(s32 a0);
    extern s32 func_8012CBF4(s32 a0);
    extern s32 func_8012CBA4(s32 a0);
    extern s32 func_8012CBCC(s32 a0);
    extern s32 func_8012D624(s32 a0, s32 a1, s32 a2);
    extern void func_8012B2CC(s32 a0);
    extern void func_8012B178(s32 a0, s32 a1);
    extern void func_8012B23C(s32 a0);
    extern s32 func_80143B6C(s32 a0, s32 a1);
    extern void func_80131E00(struct S80131E00 *a0, s32 a1);
    extern u16 D_80126B96;
    extern s16 D_80126B9A;

    s32 iVar1;
    s16 cond;

    if (*(s16 *)(param_1 + 0xa) >= 0x10) {
        func_80184580((void *)param_1);
        return;
    }

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        iVar1 = func_8012CBF4(param_1);
        if ((iVar1 & 0xff) == 0x1a) {
            goto EXIT_808B4;
        }
        if ((iVar1 & 0x4000) != 0) {
            goto STATE4;
        }
        if (func_8012D624(param_1, 0x20, 5) == 1) {
            D_80126B96 = 0x11;
            D_80126B9A = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
            *(s32 *)(param_1 + 0x48) = 0x18000;
            *(u16 *)(param_1 + 0x34) += 1;
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + 0x800;
            func_8012B2CC(param_1);
            func_8012B178(param_1, 0xFFF00000);
            goto TAIL;
        }
        if (*(s32 *)(param_1 + 0x14) < 0) {
            /* the barrier keeps [0xa] live across the [0xfe] load so local-alloc
             * hands it $v0 (see the header note); without it the two lh regs swap. */
            s32 ta = *(s16 *)(param_1 + 0xa);
            cond = ta < *(s16 *)(param_1 + 0xfe);
        } else {
            cond = *(s16 *)(param_1 + 0xa) > *(s16 *)(param_1 + 0xfe);
        }
        if (cond) {
            *(s32 *)(param_1 + 0x48) = 0x18000;
            *(u16 *)(param_1 + 0x34) += 1;
        }
        *(s32 *)(param_1 + 0x1c) += 1;
        goto TAIL;

    case 1:
        iVar1 = func_8012CBF4(param_1);
        if ((iVar1 & 0xff) == 0x1a) {
            goto EXIT_808B4;
        }
        if ((iVar1 & 0x2000) != 0) {
            *(u16 *)(param_1 + 0x34) += 1;
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0;
            *(s32 *)(param_1 + 0x1c) = 0;
            goto TAIL;
        }
        if ((iVar1 & 0x4000) == 0) {
            goto L_B88;
        }
        goto STATE4;

    case 2:
        *(s32 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x10) * 15 / 16;
        *(s32 *)(param_1 + 0x18) = *(s32 *)(param_1 + 0x18) * 15 / 16;
        iVar1 = func_8012CBA4(param_1);
        if ((iVar1 & 0xff) == 0x1a) {
            goto EXIT_808B4;
        }
        if ((iVar1 & 0x6000) == 0) {
            *(s32 *)(param_1 + 0x1c) = 0;
            *(u16 *)(param_1 + 0x34) += 1;
            goto TAIL;
        }
        if (*(s32 *)(param_1 + 0x1c) % 3 == 0) {
            func_80143B6C(param_1, 1);
        }
        *(s32 *)(param_1 + 0x1c) += 1;
        if (*(s32 *)(param_1 + 0x1c) < 0x10) {
            goto TAIL;
        }
        goto SET_HIT;

    case 3:
        iVar1 = func_8012CBCC(param_1);
        if ((iVar1 & 0xff) == 0x1a) {
            goto EXIT_808B4;
        }
        if ((iVar1 & 0x4000) == 0) {
            goto L_AF8;
        }
    STATE4:
        func_8012B23C(param_1);
        *(u16 *)(param_1 + 0x34) = 4;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0;
        goto TAIL;
    L_AF8:
        if ((iVar1 & 0x2000) == 0) {
            goto L_B88;
        }
        *(s16 *)(param_1 + 2) = 1;
        func_80143B6C(param_1, 1);
        goto TAIL;

    case 4:
        if (*(s32 *)(param_1 + 0x1c) % 3 == 0) {
            func_80143B6C(param_1, 1);
        }
        iVar1 = func_8012CBA4(param_1);
        if ((iVar1 & 0xff) != 0x1a) {
            goto L_B78;
        }
    EXIT_808B4:
        func_80184580((void *)param_1);
        return;
    L_B78:
        if ((iVar1 & 0x2000) == 0) {
            goto L_B88;
        }
    SET_HIT:
        *(s16 *)(param_1 + 2) = 1;
        goto TAIL;
    L_B88:
        *(s32 *)(param_1 + 0x1c) += 1;
        if (*(s32 *)(param_1 + 0x1c) >= 0x3c) {
            func_80131E00(param_1, 0xd);
        }
    }
TAIL:
    if (0x100000 < *(s32 *)(param_1 + 0x14)) {
        *(s32 *)(param_1 + 0x14) = 0x100000;
    }
}

extern s32 rand(void);

void func_801838A4(s32 arg0) {
    s32 t;

    *(s32 *)(arg0 + 0x48) = 0x4000;
    *(s16 *)(arg0 + 0x2) = 7;
    *(s32 *)(arg0 + 0x1C) = 0x50;
    t = rand();
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x14) = t - (t / 4096) * 4096;
}


void func_80183908(s32 arg0)
{
    extern s32 func_8004787C(s32 a0);
    extern void func_8012AD80(s32 a0);
    extern s32 func_8012D624(s32 a0, s32 a1, s32 a2);
    extern s32 func_8012BEE8(s32 a0);
    extern void func_80184634(s32 a0);
    extern u16 D_80126B96;
    extern s16 D_80126B9A;

    s32 var;
    s32 r;
    u16 x;

    var = *(s32 *)(arg0 + 0x20);
    r = func_8004787C((*(s32 *)(arg0 + 0xE4) << 6) & 0x7C0);
    x = (r >> 3) + 0xE00;
    *(u16 *)(var + 0x1C) = x;
    *(u16 *)(var + 0x18) = x;
    *(u16 *)(var + 0x1A) = (r >> 1) + 0x800;
    func_8012AD80(arg0);
    if (func_8012D624(arg0, 0x20, 5) == 1) {
        D_80126B96 = 0x11;
        D_80126B9A = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
    }
    if (func_8012BEE8(arg0)) {
        func_80184634(arg0);
    } else {
        *(s32 *)(arg0 + 0xE4) += 1;
    }
}


extern s32 func_8012BE54(void *a0);
extern void func_8012B21C(void *a0);
extern void func_8012E88C(u8 *a0);
extern s32 func_80143994(s32 a0, s32 a1);

void func_801839D4(void *arg0) {
    void *s0;
    s32 temp_v0;

    s0 = arg0;
    temp_v0 = func_8012BE54(arg0);
    if (temp_v0 > 0x40000) {
        return;
    }
    *(s16 *)((s32)s0 + 2) = 9;
    func_8012B21C(s0);
    func_8012E88C((u8 *)s0);
    *(s32 *)((s32)s0 + 0xCC) = func_80143994((s32)s0, 0x1000);
}




/* TU decls copied verbatim: func_8004787C ov_SC03_112_jr_801817E0.c:2197,
 * func_8012EFB8 :330, func_8002D4C8 :52.  func_8012CBF4 / func_80143B6C are
 * block-scope in the neighbour func_801817E0 (:2794 / :2801) — same spelling. */
extern s32 func_8004787C(s32 a0);
extern void func_8012EFB8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80183A30(s32 param_1)
{
    extern s32 func_8012CBF4(s32 a0);
    extern s32 func_80143B6C(s32 a0, s32 a1);

    /* block-scope so it cannot collide with engine_types.h's SVECTOR_8016E7C8;
     * the 8-byte (vx,vy,vz,pad) shape is what puts `in` at 0x10(sp) and
     * `out` at 0x18(sp). */
    typedef struct { short vx, vy, vz, pad; } SVec_80181D08;

    s32 sp20;
    s32 ret;
    SVec_80181D08 in;
    SVec_80181D08 out;
    s16 t;

    sp20 = *(s32 *)(param_1 + 0x20);
    ret = func_8004787C((*(s32 *)(param_1 + 0xE4) << 6) & 0x7C0);
    *(s16 *)(sp20 + 0x18) = *(s16 *)(sp20 + 0x1C) = (ret >> 3) + 0xE00;
    *(s16 *)(sp20 + 0x1A) = (ret >> 1) + 0x800;

    if (func_8012CBF4(param_1) & 0x2000) {
        *(s16 *)(param_1 + 2) = 1;
        func_80143B6C(param_1, 1);

        in.vx = *(u16 *)(param_1 + 6);
        in.vy = *(u16 *)(param_1 + 0xA);
        in.vz = *(u16 *)(param_1 + 0xE);
        ((void (*)())func_8012EFB8)(&in, &out);

        /* |vx| < 0xB5 && |vy| < 0x8D, spelled as the two sign-split tests the
         * target carries (a ternary, not abs(): gcc folds `v >= 0 ? v : -v`
         * into abssi2).  A ternary CONDITION gives each arm its own
         * `slt; bnez BODY; j TAIL` (expr.c do_jump COND_EXPR), which
         * cross-jump cannot merge; reorg then flips the vx arm, whose delay
         * slot stayed empty, to `beqz TAIL; j CONT` (reorg.c:3821). */
        if ((out.vx >= 0 ? out.vx < 0xB5 : -out.vx < 0xB5)
            && (out.vy >= 0 ? out.vy < 0x8D : -out.vy < 0x8D)) {
            /* `t` must be s16, not s32: the target sign-extends once (sll/sra 16) for
             * both clamp tests and keeps the RAW value in $a1 (`addu $a1,$v0,$zero`).
             * With an s32 temp gcc coalesces the two and drops that move (-1 ins). */
            t = (out.vx * 64) / 180 + 0x40;
            if (t < 0) {
                t = 0;
            } else if (t >= 0x80) {
                t = 0x7F;
            }
            func_8002D4C8(0x832, (t | 0x2000) & 0xFFFF);
        }
    }

    *(s32 *)(param_1 + 0xE4) += 1;
}


#include "common.h"

extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8012E9C0(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern s32 func_8018466C(void *arg0);
extern void func_80184430(s32 *a0);
extern u8 D_801AE478[];
extern u8 D_801AE488[];
extern u8 D_801AE498[];
extern s32 D_801AE350;

void func_80183BB0(s32 param_1)
{
    s32 tbl;

    func_80184430((s32 *)param_1);
    switch (*(u16 *)(param_1 + 0x5e)) {
    case 1:
        if (*(s16 *)(param_1 + 0x60) == 0) {
            *(u16 *)(param_1 + 0x76) = *(u16 *)(param_1 + 0x76) - *(s16 *)(param_1 + 0x60);
            if ((s32)(*(u16 *)(param_1 + 0x76) << 16) <= 0) {
                func_80131E00(param_1, 0xe);
            }
            func_8012E9C0(param_1);
            *(s16 *)(param_1 + 0x34) = 3;
            return;
        }
        tbl = (s32)D_801AE478;
        break;
    case 8:
        tbl = (s32)D_801AE488;
        break;
    case 5:
    case 0x1d:
    case 0x20:
        tbl = (s32)D_801AE498;
        break;
    case 0x32:
    default:
        tbl = (s32)D_801AE478;
        break;
    }
    func_8012B14C(param_1, tbl);
    ((void (*)(s32, void *))func_8012A828)((s32)param_1, &D_801AE350);
    *(s16 *)(param_1 + 0x34) = 0;
    func_8018466C(param_1);
}


#include "common.h"

/* func_80183C9C — ov_SC05_001 `_jr_80183508`, 196 ins, frame 0x18.  MATCH (match_one, masked).
 *
 *   .venv/bin/python tools/match_one.py func_80183C9C \
 *       --c .run/pool_1/opus/func_80183C9C.c \
 *       --asm-subdir asm/ov_SC05_001/nonmatchings/ov_SC05_001_jr_80183508
 *
 * Enemy state machine — the SAME shape as func_80183508 in this very TU (:2839):
 * the `if (*(s16 *)(p+0xa) >= 0x10) { func_80184580(p); return; }` guard, a 5-entry
 * jump table over `*(u16 *)(p + 0x34)`, the goto-label idiom, and the 0x100000 clamp
 * tail.  This one's tail additionally calls func_8018466C(p) before the clamp, and
 * the default arm falls straight into it.
 *
 * jtbl_801B4850 (asm/ov_SC05_001/data/tail18.data.s:9) — minval 0 / maxval 4, no
 * holes, default -> TAIL.  Its five words are in strictly ASCENDING address order
 * (80183CFC / DA0 / E6C / EC8 / EEC), so the arms are emitted in case order 0..4
 * and the source case order is the literal one.
 *
 * Four labels are reached from more than one arm and therefore MUST be written as
 * gotos at exactly these source positions or the block order drifts:
 *   EXIT    (.L80183F10, from cases 0/1 and case 4)   -> func_80184580(p); return;
 *   HITSTUN (.L80183F28, from cases 1/2/3 and case 4) -> func_80131C78(p);
 *   L_F54   (.L80183F54, from case 2 and case 4)
 *   TAIL    (.L80183F78, from every arm and the default)
 * Per §162 the surviving copy of a merged tail is the LATER one, and every one of
 * these `j`s is FORWARD into the last-emitted arm (case 4) — consistent with the
 * canonical copy living inside case 4, which is how it is spelled below.
 *
 * ---- THE ONE LEVER (90 mismatched / LENGTH-DRIFT -7 -> MATCH) ---------------
 * COOKBOOK §5a — cross-jump tail-merge, and it fires in the direction §5a warns
 * about: MY build was SHORTER than the target.  Case 1's counter tail
 *     x = ++p->0x1c;  if (x < 0x10) goto TAIL;  goto HITSTUN;
 * is byte-identical to the WHOLE of case 3's body — same 9 instructions, same two
 * exit labels — so gcc-2.7.2's `find_cross_jump` merged them (one copy survives,
 * the other arm gets a `j` + delay nop: 18 -> 11, exactly the -7 drift).  The
 * original binary keeps BOTH copies.  There is no `-fno-crossjumping` before gcc
 * 3.3, so the only lever is §5a's zero-byte barrier: `find_cross_jump` sets
 * `lose = 1` on ANY volatile asm, so one empty `__asm__ __volatile__("")` inside
 * one twin makes the two RTL streams unequal and both copies survive.
 *
 * PLACEMENT IS LOAD-BEARING, and this is the part §5a does not spell out.  The
 * barrier must sit at the very END of the twin, immediately before the shared
 * `goto TAIL` — i.e. INSIDE the `if`.  find_cross_jump walks the two streams
 * BACKWARD from the converging `j`, so a barrier at the TOP of the block is walked
 * past: the seven insns below it still match and gcc merges those instead, leaving
 * the drift only slightly smaller.  Put at the bottom the walk fails at offset 0
 * and the suffix never reaches §50-B's `minimum` floor.  Plain `("")` is used, not
 * `("" ::: "memory")` — §5a's own note — because the memory clobber would pin the
 * store ordering in the arms that schedule `sw 0x1c` against `sh 0x34`.
 * Cost: zero bytes.  A future reader WILL try to delete it; it is worth 7 ins.
 *
 * INTEGRATION SURFACE (§161c) — every block-scope decl below AGREES with this TU:
 *   func_80184580  DEFINED here `void (s32)`  TU:3482 (+ file-scope decl TU:3457)
 *                  — note func_80183508 (TU:2841) spells it `void (void *)` at ITS
 *                    own block scope; block scopes do not conflict, and the (s32)
 *                    spelling is the one that agrees with the definition.
 *   func_8018466C  file-scope `s32 ()`            TU:3150/3198 (unspecified — §195-A,
 *                  never "fix" it; redeclared here exactly as func_801840AC does)
 *   func_8012CC64  block-scope `s32  (s32,void*)` TU:3253
 *   func_8012CC1C  block-scope `s32  (s32,void*)` TU:3254
 *   func_8012B23C  block-scope `void (s32)`       TU:3256
 *   func_80131C78  block-scope `void (s32)`       TU:3257
 *   func_80143B6C  block-scope `s32  (s32,s32)`   TU:3258
 *   func_80131E00  block-scope `void (s32,s32)`   TU:3259 (file-scope `void ()` at
 *                  TU:2781/3146 — compatible, C89 unspecified-vs-prototype)
 *   D_801AE3A8     block-scope `s32`              TU:3260, passed as &D_801AE3A8
 *
 * SYMBOL AUDIT (law 1c — match_one masks jal/HI16/LO16, so this was checked by
 * hand AND by diffing the object's reloc order against the target's):
 *   80184580 jtbl D_801AE3A8 8012CC64 8012B23C | D_801AE3A8 8012CC1C 8012B23C
 *   80143B6C | D_801AE3A8 8012CC64 80143B6C 80143B6C 8012B23C | D_801AE3A8
 *   8012CC1C 80184580 80131C78 80143B6C 80131E00 8018466C  — identical, in order.
 */

void func_80183C9C(s32 param_1)
{
    extern void func_80184580(s32 a0);
    extern s32 func_8018466C(void *arg0);
    extern s32 func_8012CC64(s32 a0, void *a1);
    extern s32 func_8012CC1C(s32 a0, void *a1);
    extern void func_8012B23C(s32 a0);
    extern void func_80131C78(s32 a0);
    extern s32 func_80143B6C(s32 a0, s32 a1);
    extern void func_80131E00(struct S80131E00 *a0, s32 a1);
    extern s32 D_801AE3A8;

    s32 iVar1;

    if (*(s16 *)(param_1 + 0xa) >= 0x10) {
        func_80184580(param_1);
        return;
    }

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) -= 0x100;
        iVar1 = func_8012CC64(param_1, &D_801AE3A8);
        if ((iVar1 & 0xff) == 0x1a) {
            goto EXIT;
        }
        if ((iVar1 & 0x2000) != 0) {
            *(u16 *)(param_1 + 0x34) += 1;
            *(s32 *)(param_1 + 0x1c) = 0;
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0;
            goto TAIL;
        }
        if ((iVar1 & 0x4000) != 0) {
            *(u16 *)(param_1 + 0x34) = 4;
            *(s32 *)(param_1 + 0x1c) = 0;
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0;
            func_8012B23C(param_1);
            goto TAIL;
        }
        *(s32 *)(param_1 + 0x1c) += 1;
        if (*(s32 *)(param_1 + 0x1c) >= 0x3c) {
            *(u16 *)(param_1 + 0x34) = 2;
        }
        goto TAIL;

    case 1:
        *(s32 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x10) * 15 / 16;
        *(s32 *)(param_1 + 0x18) = *(s32 *)(param_1 + 0x18) * 15 / 16;
        iVar1 = func_8012CC1C(param_1, &D_801AE3A8);
        if ((iVar1 & 0xff) == 0x1a) {
            goto EXIT;
        }
        if ((iVar1 & 0x6000) == 0) {
            *(u16 *)(param_1 + 0x34) += 1;
            *(s32 *)(param_1 + 0x1c) = 0;
            func_8012B23C(param_1);
            goto TAIL;
        }
        if ((*(s32 *)(param_1 + 0x1c) & 3) == 0) {
            func_80143B6C(param_1, 1);
        }
        *(s32 *)(param_1 + 0x1c) += 1;
        if (*(s32 *)(param_1 + 0x1c) < 0x10) {
            goto TAIL;
        }
        goto HITSTUN;

    case 2:
        iVar1 = func_8012CC64(param_1, &D_801AE3A8);
        if ((iVar1 & 0x2000) != 0) {
            func_80143B6C(param_1, 1);
            goto HITSTUN;
        }
        if ((iVar1 & 0x4000) == 0) {
            goto L_F54;
        }
        *(u16 *)(param_1 + 0x34) = 4;
        func_80143B6C(param_1, 1);
        func_8012B23C(param_1);
        goto TAIL;

    case 3:
        *(s32 *)(param_1 + 0x1c) += 1;
        if (*(s32 *)(param_1 + 0x1c) < 0x10) {
            /* §5a ZERO-BYTE CROSS-JUMP BARRIER — LOAD-BEARING, DO NOT DELETE.
             * This whole arm is byte-identical to case 1's counter tail; without
             * this line find_cross_jump merges the two and the function comes out
             * 7 instructions short.  Emits no machine code.  See the header. */
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
            goto TAIL;
        }
        goto HITSTUN;

    case 4:
        iVar1 = func_8012CC1C(param_1, &D_801AE3A8);
        if ((iVar1 & 0xff) != 0x1a) {
            goto L_F20;
        }
    EXIT:
        func_80184580(param_1);
        return;
    L_F20:
        if ((iVar1 & 0x2000) == 0) {
            goto L_F38;
        }
    HITSTUN:
        func_80131C78(param_1);
        goto TAIL;
    L_F38:
        if ((*(s32 *)(param_1 + 0x1c) & 3) == 0) {
            func_80143B6C(param_1, 1);
        }
    L_F54:
        *(s32 *)(param_1 + 0x1c) += 1;
        if (*(s32 *)(param_1 + 0x1c) >= 0x3c) {
            func_80131E00(param_1, 0xd);
        }
    }
TAIL:
    func_8018466C(param_1);
    if (0x100000 < *(s32 *)(param_1 + 0x14)) {
        *(s32 *)(param_1 + 0x14) = 0x100000;
    }
}


extern s32 D_801AE350;
extern s32 func_8018466C(void *arg0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern void func_80184430(s32 *a0);

void func_80183FAC(s32 *a0) {
    func_80184430(a0);
    func_8018466C((s32)a0);
    ((void (*)(s32, void *))func_8012A828)((s32)a0, &D_801AE350);
    func_8002D4C8(0xA74, 0);
}


extern void func_80184430(s32 *a0);
    extern s32 func_8018466C(void *arg0);
    void func_80183FF8(s32 *a0) {
        func_80184430(a0);
        func_8018466C((s32)a0);
    }




void func_80184028(s32 param_1)
{
    extern void func_80184430(s32 *a0);
    extern void func_8012B14C(s32 a0, s32 a1);
    extern void func_8012A828(s32*, s32);
    extern s32 func_8018466C(void *arg0);
    extern s32 D_801AE350;
    extern s32 D_801AE4A8;
    extern s32 D_801AE4B8;

    s32 s0 = param_1;

    *(u8 *)(s0 + 0xC2) = 0;
    *(u8 *)(s0 + 0xC3) = 0;
    func_80184430((s32 *)param_1);

    if (*(u16 *)(s0 + 0x5E) == 9 || *(u16 *)(s0 + 0x5E) == 0x1C) {
        func_8012B14C(s0, (s32)&D_801AE4A8);
    } else {
        func_8012B14C(s0, (s32)&D_801AE4B8);
    }

    ((void (*)(s32, void *))func_8012A828)(s0, (void *)&D_801AE350);
    func_8018466C(s0);
}



void func_801840AC(s32 param_1) {
    extern void func_80184580(s32 a0);
    extern s32 func_8018466C(void *arg0);
    extern void func_8012DBD0(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 func_8012CC64(s32 a0, void *a1);
    extern s32 func_8012CC1C(s32 a0, void *a1);
    extern s32 func_8012CBA4(s32 a0);
    extern void func_8012B23C(s32 a0);
    extern void func_80131C78(s32 a0);
    extern s32 func_80143B6C(s32 a0, s32 a1);
    extern void func_80131E00(struct S80131E00 *a0, s32 a1);
    extern s32 D_801AE3A8;

    u8 bVar1;
    s32 uVar3;
    s32 pad[2];

    if (0xf < *(s16 *)(param_1 + 0xa)) {
        ((void (*)(void *))func_80184580)((void *)param_1);
        return;
    }

    if ((*(s32 *)(param_1 + 0x10) != 0) || (*(s32 *)(param_1 + 0x18) != 0)) {
        func_8012DBD0(param_1, 0x50,
                      *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + 0x800, 0x1D);
    }

    bVar1 = *(u8 *)(param_1 + 0xc2);
    switch (bVar1) {
    case 0:
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) -= 0x100;
        *(s32 *)(param_1 + 0x1c) += 1;
        if (0x28 < *(s32 *)(param_1 + 0x1c)) {
            goto LAB_80180730;
        }
        uVar3 = func_8012CC64(param_1, &D_801AE3A8);
        if ((uVar3 & 0x4000) != 0) {
            goto LAB_80180644;
        }
        if ((uVar3 & 0x2000) != 0) {
            if ((uVar3 & 0xff) == 0x1a) {
                goto LAB_8018066C;
            }
            *(u8 *)(param_1 + 0xc2) = 2;
            func_80143B6C(param_1, 1);
            *(s32 *)(param_1 + 0x14) = 0xFFF30000;
            *(s32 *)(param_1 + 0x1c) = 0;
        }
        goto LAB_80180740;

    case 2: {
        s32 saved14;

        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) -= 0x100;
        *(s32 *)(param_1 + 0x1c) += 1;
        if (0x28 < *(s32 *)(param_1 + 0x1c)) {
            goto LAB_80180730;
        }
        saved14 = *(s32 *)(param_1 + 0x14);
        uVar3 = func_8012CC64(param_1, &D_801AE3A8);
        if ((uVar3 & 0x4000) != 0) {
            goto LAB_80180644;
        }
        if ((uVar3 & 0x2000) != 0) {
            if ((uVar3 & 0xff) == 0x1a) {
                goto LAB_8018066C;
            }
            func_80143B6C(param_1, 1);
            *(s32 *)(param_1 + 0x14) = saved14;
            *(u8 *)(param_1 + 0xc2) = 3;
            *(s32 *)(param_1 + 0x1c) = 0;
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0;
        }
        goto LAB_80180740;
    }

    case 3:
        *(s32 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x10) * 15 / 16;
        *(s32 *)(param_1 + 0x18) = *(s32 *)(param_1 + 0x18) * 15 / 16;
        if ((*(u8 *)(param_1 + 0xc3) & 1) == 0) {
            goto CASE3_CC64;
        }
        uVar3 = func_8012CC1C(param_1, &D_801AE3A8);
        if ((uVar3 & 0x6000) != 0) {
            goto CASE3_TAIL;
        }
        goto LAB_80180730;

    CASE3_CC64:
        uVar3 = func_8012CC64(param_1, &D_801AE3A8);
        if ((uVar3 & 0x4000) == 0) {
            goto CASE3_NO4000;
        }
    LAB_80180644:
        func_8012B23C(param_1);
        *(u8 *)(param_1 + 0xc2) = 4;
        goto LAB_80180740;

    CASE3_NO4000:
        if ((uVar3 & 0x2000) == 0) {
            goto CASE3_TAIL;
        }
        if ((uVar3 & 0xff) != 0x1a) {
            goto CASE3_SETFLAG;
        }
    LAB_8018066C:
        ((void (*)(void *))func_80184580)((void *)param_1);
        return;

    CASE3_SETFLAG:
        *(u8 *)(param_1 + 0xc3) = *(u8 *)(param_1 + 0xc3) | 1;

    CASE3_TAIL:
        if ((*(u32 *)(param_1 + 0x1c) & 3) == 3) {
            func_80143B6C(param_1, 1);
        }
        *(s32 *)(param_1 + 0x1c) += 1;
        if (*(s32 *)(param_1 + 0x1c) < 0x11) {
            goto LAB_80180740;
        }
        if ((uVar3 & 0x6000) == 0) {
            goto LAB_80180730;
        }
        goto CASE34_TAIL;

    case 4:
        uVar3 = func_8012CBA4(param_1);
        if ((uVar3 & 0x2000) == 0) {
            goto CASE4_COUNTER;
        }

    CASE34_TAIL:
        func_80131C78(param_1);
        goto LAB_80180740;

    CASE4_COUNTER:
        if ((*(u32 *)(param_1 + 0x1c) & 3) == 3) {
            func_80143B6C(param_1, 1);
        }
        *(s32 *)(param_1 + 0x1c) += 1;
        if (*(s32 *)(param_1 + 0x1c) < 0x3d) {
            goto LAB_80180740;
        }
        goto LAB_80180730;

    default:
        goto LAB_80180740;
    }

LAB_80180730:
    func_80131E00(param_1, 0xd);
    return;

LAB_80180740:
    func_8018466C(param_1);
    return;
}




void func_80184430(s32 *a0)
{
    extern void func_8012B2CC(s32 a0);
    extern void func_8012B23C(s32 a0);

    s32 ptr;

    *(u16 *)((s32)a0 + 0x5C) = *(u16 *)((s32)a0 + 0x5C) & 0xFFFE;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = (*(u16 *)((s32)a0 + 0x62) + 0x800) & 0xFFF;
    ptr = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(ptr + 0x14) = 0;
    *(u16 *)(ptr + 0x10) = 0;
    *(s32 *)((s32)a0 + 0x1C) = 0;
    func_8012B2CC((s32)a0);
    func_8012B23C((s32)a0);
}


extern void func_8012A828(s32*, s32);
extern s32 func_8012B030(u8 *a0);

void func_80184494(void *a0) {

    extern u8 D_80185D94[];
    s32 ptr;
    u16 val;

    *(u16 *)((s32)a0 + 2) = 1;
    ptr = *(s32 *)((s32)a0 + 0x78);
    val = *(u16 *)(ptr + 2);
    *(u16 *)((s32)a0 + 0x5C) = val;
    ((void (*)(s32, void *))func_8012A828)((s32)a0, D_80185D94);
    func_8012B030((u8 *)a0);
}


void func_801844E0(void *a0) {
        s32 v1 = *(s32 *)((s32)a0 + 0x20);
        *(s32 *)((s32)a0 + 0x1C) = 0x1E;
        *(s16 *)((s32)a0 + 0x5C) = 0;
        *(s16 *)(v1 + 0x10) = 0;
    }


extern void func_8002A04C(s32);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012E8C4(s32 a0);
extern void func_80184580(s32 a0);
extern void func_80184750(s32);

void func_801844F8(s32 a0) {
    s32 s0 = a0;
    func_8012E8C4(s0);
    if (func_8012BEE8(s0)) {
        ((void (*)(void *))func_80184750)((void *)s0);
        ((s32 (*)(void *))func_8002A04C)((void *)s0);
        ((void (*)(void *))func_80184580)((void *)s0);
    }
}


extern void func_80184750(s32 arg0);
extern void func_8002A04C(s32 a0);
extern void func_80184580(s32 a0);

void func_80184548(s32 arg0) {
    func_80184750(arg0);
    ((s32 (*)(s32))func_8002A04C)(arg0);
    func_80184580(arg0);
}


void func_80184580(s32 a0) {
    extern void func_8012E8A8(u8 *a0);
    extern void func_8012B2CC(s32 a0);
    extern void func_801439C0(u8 *a0);
    extern void func_80184634(s32 a0);

    s32 s0 = a0;
    u16 flags;
    s32 hit;

    flags = *(u16 *)(s0 + 0x70);
    if ((flags & 2) != 0) {
        if ((flags & 0x10) != 0) {
            *(u16 *)(s0 + 2) = 8;
            *(u8 *)(s0 + 0xC1) = 0;
            *(u16 *)(s0 + 0x5E) = 0;
            *(u16 *)(s0 + 0x5C) = *(u16 *)(*(s32 *)(s0 + 0x78) + 2);
            func_8012E8A8((u8 *)a0);
            *(u16 *)(s0 + 6) = *(u16 *)(s0 + 0x88);
            *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0x8A);
            *(u16 *)(s0 + 0xE) = *(u16 *)(s0 + 0x8C);
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
            *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0;
            func_8012B2CC(s0);
            hit = *(s32 *)(s0 + 0xCC);
            if (hit != 0) {
                func_801439C0((u8 *)hit);
            }
            return;
        }
    }
    func_80184634(s0);
}



extern void func_80016714(void *a0, s32 a1);
    extern void func_8012C098(void *a0);
    void func_80184634(s32 param_1) {
        s32 iVar1;
        iVar1 = *(s32 *)(param_1 + 0xd0);
        ((void (*)(s32 *, s32))func_80016714)((s32 *)iVar1, 0x38);
        ((void (*)(s32))func_8012C098)(param_1);
    }


extern u8 D_800AF630[];
extern u8 D_801AE3A0[];
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8004787C(s32 a0);

typedef struct { s16 a, b, c, d; } V8x_8018466C;

s32 func_8018466C(void *arg0)
{
    s32 s1 = (s32)arg0;
    s32 s2 = (s32)D_800AF630;
    u8 buf[16];
    s32 r;
    s32 s0;
    s32 setMask;

    if (*(s32 *)(s1 + 0xD0) == 0) {
        return;
    }

    s0 = *(s32 *)(s1 + 0xD0);

    func_8012F214((s32)arg0, (s32)D_801AE3A0, (s32)buf);

    *(V8x_8018466C *)((u8 *)s0 + 8) = *(V8x_8018466C *)buf;

    setMask = 0x80000000;
    if (*(s32 *)(*(s32 *)(s1 + 0x20) + 4) < 0) {
        *(s32 *)((u8 *)s0 + 4) |= setMask;
    } else {
        *(s32 *)((u8 *)s0 + 4) &= 0x7FFFFFFF;
    }

    r = func_8004787C(((*(u16 *)(s2 + 0xA3AA) * 7) << 3) & 0x7F8);
    r = (r >> 4) + 0x455;
    *(s16 *)((u8 *)s0 + 0x1A) = r;
    *(s16 *)((u8 *)s0 + 0x18) = r;
}


extern s32 func_8012C51C(void *a0, s32 a1);
extern void func_8012B0B4(u32 *a0, s32 a1, s32 a2);

void func_80184750(arg0)
s32 arg0;
{
    struct { s16 f0, f2, f4, f6, f8, fA, fC, fE; s32 f10; } s;
    u32 buf[2];
    s32 i;
    u32 *bp;
    s32 x;

    i = 0;
    bp = buf;

    s.f6 = 0x33;
    s.fA = 0;
    s.f8 = 0;
    s.f10 = 0;
    s.fE = 0;
    s.fC = 0x7FFF;

    for (; i < 5; i++) {
        func_8012B0B4(bp, rand() % 4096, rand() % 64);
        x = *(s32 *)buf;
        s.f0 = *(u16 *)(arg0 + 6) + x;
        s.f2 = *(u16 *)(arg0 + 0xA) - 0x60;
        s.f4 = *(u16 *)(arg0 + 0xE) + (x >> 16);
        func_8012C51C(&s, arg0);
    }
}


extern u16 D_800B99DA;
extern u8 D_801AE326;
extern u8 D_801AE360;
extern u8 D_801AE361;
extern u8 D_801AE362;

void func_80184848(s32 arg0) {
    s32 r;
    s32 x;
    s32 col0;
    s32 col1;
    s32 col2;
    u8 *p;
    s32 i;
    s32 off;

    r = func_8004787C((((D_800B99DA << 3) - D_800B99DA) << 3) & 0x7F8);
    x = (((((r << 1) + r) << 3) + r) << 2) >> 12;
    col0 = x + 100;
    col1 = x - 126;
    col2 = ((((((r << 3) - r) << 3) - r) << 1) >> 12) + 100;
    i = 0;
    p = &D_801AE326;
    off = 0;
    do {
        i++;
        p[off - 2] = col0;
        p[off - 1] = col1;
        p[off] = col2;
        off += 16;
    } while (i < 3);
    D_801AE360 = col0 - 50;
    D_801AE361 = col1 - 50;
    D_801AE362 = col2 - 50;
    *(s32 *)(arg0 + 0x1C) += 1;
}



extern void (*D_801AEAF8[])(void);

void func_80184920(void *a0) {
    D_801AEAF8[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 rand(void);

void func_8018495C(s32 param_1)
{
    *(s32 *)(param_1 + 0x1C) = rand();
    *(u16 *)(param_1 + 0x2) += 1;
    *(u16 *)(param_1 + 0xFE) = *(u16 *)(param_1 + 0xFC) + (rand() % 16) + 0x10;
}


extern s32 func_8012BE54(void*);
extern void func_80184AF8(s32 arg0);

void func_801849C4(s32 param_1) {
    if (((s32 (*)(s32))func_8012BE54)(param_1) < 0x100001) {
        if ((*(s32 *)(param_1 + 0x1C) % *(s16 *)(param_1 + 0xFC)) == 0) {
            func_80184AF8(param_1);
            func_8012C658(0x183, 1, param_1);
            *(s16 *)(param_1 + 0xFE) = *(u16 *)(param_1 + 0xFC) + rand() % 16 + 0x10;
        }
        if ((*(s32 *)(param_1 + 0x1C) % *(s16 *)(param_1 + 0xFE)) == 0) {
            func_80184AF8(param_1);
            func_8012C658(0x183, 1, param_1);
        }
    }
    *(s32 *)(param_1 + 0x1C) += 1;
}


extern void func_8012B0B4(u32 *a0, s32 a1, s32 a2);

void func_80184AF8(s32 arg0) {
    s32 sp10[2];
    s32 temp;

    func_8012B0B4(sp10, rand() % 0x1000, 0x30);
    temp = sp10[0];
    *(s16 *)(arg0 + 6) = *(u16 *)(arg0 + 0x88) + temp;
    *(s16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0x8C) + (temp >> 16);
}



extern void (*D_801B267C[])(void);

void func_80184B68(void *a0) {
    D_801B267C[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_801850C4(s32 arg0);
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_8018511C(s32 arg0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80184BA4(s32 a0) {
    extern u8 D_801B2630[];
    extern u8 D_801B263C[];
    s32 s0;
    u16 t;
    u16 u;
    u16 v;

    s0 = func_801850C4(a0);
    if ((s0 == 1) || (s0 = ((s32 (*)(void))func_8012C194)(), s0 == 0)) {
        ((void (*)(s32))func_8012CAE4)(a0);
    } else {
        *(s32 *)(a0 + 0xCC) = s0;
        func_8001CC3C(s0, (s32)D_801B2630, 0x214, 0x168);
        *(s32 *)(s0 + 0x4) = 0x50000000;
        *(u8 *)(s0 + 0x27) = 0x24;
        func_80128EA8(s0, a0 + 0xDC, (s32)D_801B263C);
        func_8018511C(a0);
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
extern void func_8018511C(s32 arg0);
extern void func_80185198(void *arg0);

void func_80184CA0(s32 arg0) {
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
            func_8018511C(arg0);
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
    func_80185198((void *)arg0);
}




extern s32 rand(void);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8018511C(s32 arg0);
extern void func_80185198(void *arg0);

void func_80184F30(s32 arg0) {

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
        func_8018511C(arg0);
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
    func_80185198((void *)arg0);
}



/* func_801850C4 — "is another entity of type 0x35C sharing my 0x64 owner?"
 *
 * Walks the 0x60-entry entity table at D_801202A0 (stride 0x10C) with an int
 * counter (the target keeps the count in $a2 and `slti ...,0x60`, so it is a
 * counted loop, NOT the D_80126720 pointer-bound idiom the sibling walkers
 * use).  Returns 1 for the first entry whose u16 kind == 0x35C, whose word at
 * 0x64 equals the caller's word at 0x64, and which is not the caller itself.
 */
s32 func_801850C4(s32 arg0) {
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

void func_8018511C(s32 arg0) {
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



/* func_80185198 — guard-then-free tail (cookbook §71 sibling shape:
 * src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c func_80144458 tail, and
 * src/ov_SC03_099/ov_SC03_099_jr_80140608.c:2432 func_80016714(x, 0x38)). */

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_80185198(void *arg0) {
    void *temp_a0;

    temp_a0 = *(void **)((char *)arg0 + 0xCC);
    if (temp_a0 != NULL) {
        func_80016714(temp_a0, 0x38);
    }
    func_8012C218(arg0);
}



/* Sibling shape: DEFINE_func_80143BDC() in src/shared/engine_core.h (cookbook §71) */

extern s32 func_8012C51C(void *a0, s32 a1);


void func_801851DC(s32 a0, u16 *a1, s16 a2) {
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



extern void (*D_801B29B8[])(void);

void func_8018523C(void *a0) {
    D_801B29B8[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conform VERBATIM to the ones already present in
 * src/ov_SC03_014/ov_SC03_014_jr_801848E4.c (lines 58, 2524, 2527, 3139,
 * 3222, 3244, 3245).  Type mismatches are resolved by casting AT THE USE. */
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80029178(s32 arg);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32*, s32);
/* not declared anywhere in the TU */
extern void func_80185924(void *a0);

void func_80185278(void *a0) {

    extern s32 D_801B2710[];
    extern u8 D_801B26A8[];
    extern u8 D_80185D94[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801B26A8);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801B2710[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_80185924);
        *(s32 *)((s32)a0 + 0xCC) = res2;
    } else {
        val = *(s16 *)((s32)a0 + 0x70);
        val |= 0x4000;
        *(s16 *)((s32)a0 + 0x70) = val;
    }

    res2 = func_8012C658(0x8F, *(s16 *)((s32)a0 + 0x70), (s32)a0);
    *(s32 *)((s32)a0 + 0x6C) = res2;

    if (res2 == 0) {
        func_8012CAE4(a0);
    } else {
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_80185D94);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_8018534C(void *a0) {
    void *p1, *p2;
    u16 val;
    long x;

    p1 = *(void **)(a0 + 0x20);
    p2 = *(void **)(a0 + 0x6C);
    val = *(u16 *)(p1 + 0x12);
    p2 = *(void **)(p2 + 0x20);
    val += 0x800;
    val &= 0xFFF;
    *(u16 *)(p2 + 0x12) = val;
    x = 2;
    *(u16 *)(a0 + 0x2) = x;
    return x;
}


void func_80185374(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_8018537C(void *a0) {

    extern s32 D_801B28F4;
    extern s32 D_801B28E0;
    extern s32 D_801B28DC;
    extern s32 D_801B2974;
    extern s32 D_801B2908;
    extern s32 D_801B27D4[];
    extern s32 D_801B2858[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801B28F4 = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801B28DC = 0;
                D_801B28E0 = D_801B2858[v0];
            } else {
                D_801B28E0 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801B2858[v0], 1);
                D_801B28DC = 2;
            }
        } else {
            D_801B28F4 = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801B28DC = 0;
            D_801B28E0 = D_801B27D4[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801B2908);
    } else {
        p = &D_801B2974;
        *p = *(s32 *)((char *)s0 + 0x0);
        func_80178CBC((s32)a0, (s32)(p - 7));
    }

    *(u16 *)(a0 + 0x2) = 4;
    *(u16 *)(a0 + 0x70) |= 0x8000;
}




/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (lines 43, 45, 58, 65, 2528, 2538, 2712, 3177, 3282).
 * Type mismatches resolved by casting AT THE USE (func_80178D18). */
extern s32 func_801789AC(s32 arg0);
extern void func_80178D18(void);
extern s32 func_80029178(s32 arg);
extern void func_80029514(s32);
extern void func_80029124(s32, s32);
extern void func_80145EE8(s32 param_1);
extern void func_8012C218(void *a0);
extern s32 func_801856CC(void);

void func_801854C8(void *arg0) {

    extern s32 D_801B2710[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801B2710[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801B2710[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_801856CC() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}



extern void func_8012C218(void *a0);
    s32 func_801855E8(void * arg0)
    {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32 *))func_8012C218)(*(s32 **)((char *)arg0 + 0xcc));
    }


void func_80185614(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_80185624(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_80185634(void *a0) {

    extern s32 D_801B2710[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801B2710[idx], 1);
}



extern s32 D_80126B58;
extern void func_8014ADA8(s32 a0, s32 a1);

void func_80185674(void * arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((s32)arg0 + 0xdc);
    ((void (*)(s32 *, s32))func_8014ADA8)((s32 *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
}


extern s16 func_80174764(void);
s32 func_801856A8(void) {
    return ((s32 (*)(void))func_80174764)() == 1;
}




extern s32 func_80029178(s32 arg);

s32 func_801856CC(void) {

    extern s32 D_801B2710[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801B2710[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



extern void (*D_801B29E0[])(void);

void func_80185730(void *a0) {
    D_801B29E0[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);

void func_8018576C(void *a0) {

    extern u8 D_801B26DC[];
    extern u8 D_801B30A0[];
    extern u8 D_801B2E80[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801B26DC) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801B30A0);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801B2E80);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32*, s32);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801857F4(void *a0) {

    extern u8 D_801B2E90[];
    extern u8 D_801B2F98[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801B2E90);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801B2F98);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_801858B4 — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801B30A0, else
 * D_801B2E80), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `((void (*)(s32, void *))func_8012A828)(entity, D_801B30A0 / D_801B2E80)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32*, s32);

void func_801858B4(void *a0) {

    extern u8 D_801B30A0[];
    extern u8 D_801B2E80[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801B30A0);
        } else {
            ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801B2E80);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801B29D0[];
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172710(void);
extern s32 func_80178BF8();

s32 aF8018A224() __asm__("func_80185924");

s32 aF8018A224(param_1)
    void *param_1;
{
    s32 *m;
    s32 obj;
    s32 sv0[2];
    s32 sv1[2];
    s32 flag;

    m = (s32 *)((u8 *)D_80126B78 + 0x34);
    obj = *(s32 *)((s32)param_1 + 0x64);

    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

    RotTransSV(D_801B29D0, sv0, &flag);
    RotTransSV(D_801B29D0 + 8, sv1, &flag);

    if (func_80135888(*(s32 *)(obj + 0x20), *(s32 *)(obj + 0x58), (s32)sv0, (s32)sv1) == 0) {
        return 0;
    }
    if (func_8012BDBC(obj, 0x300) == 0) {
        return 0;
    }
    *(s16 *)(obj + 0x2) = 3;
    func_80178BF8();
    return (s32)func_80172710;
}






