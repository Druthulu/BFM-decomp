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
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80195B0C;
extern u8 D_80195A7C;
extern u8 D_80195A58;
extern u8 D_80195A34;
extern u8 D_80195AE8;
extern u8 D_80195AC4;
extern u8 D_80195AA0;
extern u8 D_80195A10;
extern void func_80145934(void);
extern u8 D_80195B9C;
extern u8 D_80195B78;
extern u8 D_80195B54;
extern u8 D_80195B30;
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
extern unsigned char D_80194F94[];
extern unsigned char D_80194FC4[];
extern unsigned char D_80195014[];
extern unsigned char D_80195044[];
extern unsigned char D_80195074[];
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
extern void (*D_801950C4[])(void *);
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
extern s32 D_8019518C[];
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
extern u8 D_80195214[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8019521C;
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
extern int D_801D3D70;
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
extern s32 D_801D3D74;
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
extern s32 D_8019524C;
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
extern void (*D_801952F4[])(void);
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
extern void (*D_80195318[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80195308;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8019532C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80195338[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80195348[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80195360[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80195350;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80195374[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80195390[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80195380;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801953A4[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801953B8[])(void);
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
extern s32 D_801953CC;
extern void (*D_801953F4[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801953D4;
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
extern int (*D_80195440[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80195444[])(void);
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
extern unsigned short D_801958A8[];
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
extern void (*D_801958B8[])(void);
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
extern int D_801D3DA8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_801958E0[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_801958C0;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_801958D0;
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
extern void (*D_80195920[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80195928[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_801958F4;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80195934[])(void);
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
extern u8 D_80195904;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801D3DB0;
extern s32 D_801D3DBC;
extern s32 D_801D3DC0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80195970[])(s32 *);
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
extern s32 D_80195944[];
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
extern s32 D_801D3DB8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80195BC0[])(void);
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
extern char D_801959E0[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80195C64[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80195DB8[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80195BD4;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80195DC0[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80195BE4;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80195C04;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80195DC8[])(void);
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
extern void (*D_80195DF0[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80195DFC[])(void);
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
extern void (*D_80195C70[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80195EA0;
extern void func_8015D380(s32 a0);
extern unsigned char D_80194F84[];
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
extern unsigned char D_80195EB4[];
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
extern s8 D_80195EF0[];
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
extern u16 D_80195F38;
extern u16 D_80195F3A;
extern u16 D_80195F3C;
extern s32 D_80195F40;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80195F48;
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
extern int D_80195C54;
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
extern unsigned int D_80195FCC[];
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
extern void (*D_8019607C[])(void);
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
extern u16 D_801960AC[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80196110;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801D3DC8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80196134[])(void);
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
extern int D_801D3E20[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8019617C[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8019616C;
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
extern char D_801D34A0[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80196184[])(void);
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
extern void (*D_801961D8[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801961A0;
extern s16 D_801961D4;
extern s16 D_801961D2;
extern s16 D_801961D0;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_801961E4[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801D3E80;
extern u8 D_801D3E81;
extern u8 D_801D3E82;
extern u8 D_801D3E83;
extern u8 D_801D3E84;
extern u8 D_801D3E85;
extern u8 D_801D3E86;
extern u8 D_801D3E87;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_801961F4[])(void);
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
extern s32 D_801D3EC0;
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
extern void (*D_80196238[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801962B4[];
extern s32 D_801962D4[];
extern u8 D_80196350[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80196370[];
extern u8 D_80196390[];
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
extern void (*D_8019642C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801964A8[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801D34B0;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801964B4[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801964BC[])(void);
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
extern void (*D_80196584[])(void);
extern void func_80166618(void *a0);
extern void (*D_80196594[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801965A4[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801965B0[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80196510[];
extern u8   D_80196524[];
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
extern void (*D_801965C8[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801965D0[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801965D8[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801965E0[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_801965E8[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_801965F0[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_801965F8[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801966AC[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801966B4[])(void);
extern void func_80169F00(void *a0);
extern char D_80196664[];
extern char D_80196624[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_801966EC[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_801966F8[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80196740[])(void);
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
extern void (*D_801967BC[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801D41E0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801967B0[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_801967F4[];
extern unsigned short D_801967FC[];
extern unsigned short D_80196804[];
extern unsigned char D_801D41E8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801D41E0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8019680C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801D431C;
extern M2C_UNK D_801D4320;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D42A8;
extern void (*D_8019683C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801D4324[];
extern u8 D_801D432C[];
extern u8 D_801D42DC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80196844[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80196860[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80196868[])(void);
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
extern void (*D_801968D0[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80196874;
extern u8 D_80196880;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80196904[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8019690C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80196960[])(void);
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
extern u16 D_80196994[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80196984[];
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
extern s32 D_801969B0;
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
extern void (*D_80196A28[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80196A30[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80196A38[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80196A40[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80196A48[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80196A50[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80196A5C[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80196A68[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80196A74[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80196A84[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80196A94[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80196A9C[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80196AA4[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80196AAC[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80196AB4[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80196ABC[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80196AC4[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80196ACC[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80196AD4[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80196ADC[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80196AE4[])(void);
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
extern void (*D_80196AEC[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80196AF4[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80196AFC[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80196B04[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80196B0C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80196B14[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80196B1C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80196B24[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80196B2C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80196B34[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80196B3C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80196B44[])(void);
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
extern void (*D_80196B88[])(void);
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
extern M2C_UNK D_80196B4C;
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
extern void (*D_80196BB8[])(void);
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
extern void (*D_80196BF4[])(void);
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
extern s32 func_801749C8(s32);
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_80196C4C[])();
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
extern void (*D_80196C5C[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80196C64[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_80196DCC[])();
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
extern void (*D_80196DD8[])();
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
extern M2C_UNK D_801D36F8;
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
extern s16 D_801D5B28;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801D4A60;
extern short D_801D5B9C;
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
extern s32 D_801D4E8C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801D4EB4;
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
extern s16 D_801D4E70;
extern s32 func_8017A3B0(void);
extern short D_801D4EAC;
extern short D_801D4EA8;
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
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801D4E74;
extern u16 D_801D4EF4;
extern u16 D_801D4EF6;
extern u16 D_801D4EF8;
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
extern s16 D_801D4EEC;
extern s16 D_801D4EEE;
extern s16 D_801D4EF0;
extern s16 D_801D4EE4;
extern s16 D_801D4EE6;
extern s16 D_801D4EE8;
extern void func_8017B7A8(void);
extern s16 D_801D4F04;
extern s16 D_801D4F06;
extern s16 D_801D4F08;
extern s16 D_801D4F0C;
extern s16 D_801D4F0E;
extern s16 D_801D4F10;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801D4EFC;
extern short D_801D4EFE;
extern short D_801D4F00;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801D4E94;
extern SV4 D_801D4E9C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801D4EBC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801D4EB8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80196FB4[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80196FCC[])(void);
extern void func_8017BEBC(void *a0);
extern void func_8017C090(void *a0);
extern void func_8017C24C(s32 arg0);
extern void func_8002931C(void);
extern int func_8017D12C(int arg);
extern void (*D_80197048[])(void);
extern void func_8017D14C(void *a0);
extern void func_8017D3B8(void);
extern s32 func_8017D188(s32 a0);
extern s32 func_8017D1CC(void);
extern void (*D_80197050[])(void);
extern void func_8017D1F0(void *a0);
extern void func_8017D3E0(void);
extern s32 func_8017D22C(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017D26C(u8 *a0);
extern void func_800D1EBC(void);
extern void func_8017D2E8(void);
extern void (*D_8019705C[])(void);
extern void func_8017D308(void *a0);
extern s32 func_8017D344(s32 a0);
extern M2C_UNK D_8019706C;
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_8017D4A0(void *a0);
extern void func_8017D408(void);
extern void (*D_80197080[])(void);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017D648(s32 param_1, s16 *param_2);
extern void (*D_80197088[])(void);
extern void func_8017D8F8(void *a0);
extern s32 func_8017DC58(void);
extern void func_8012DFD4(void *a0);
extern void func_8017DC60(void *a0);
extern void func_8017DE64(s32 a0);
extern void func_8017DEA4(void);
extern void func_8017DEAC(void *a0);
extern void func_8017DF04(s32 a0);
extern void func_8017E134(s32 a0);
extern void func_8017E188(void);
extern s32 func_8017E1AC(void);
extern void (*D_8019714C[])(void);
extern void func_8017E1F0(void *a0);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_8017E420(void*);
extern void func_8017E3F0(int);
extern void func_8017E22C(int param_1);
extern s32 func_8017E434(s32 *a0, s32 a1);
extern void func_8017E378(s32 *a0);
extern void aF8017E3F0();
extern void func_8017E420(void *a0);
extern void (*D_80197184[])(void);
extern void func_8017E49C(void *a0);
extern void func_8017E4D8(s32 param_1);
extern void func_8017E574(s32 param_1);
extern void func_8017E524(s32 param);
extern void func_8017E56C(void);
extern u32 *D_8019717C[];
extern Blk8 D_80197198[];
extern void func_8017E6D8();
extern void func_80013F3C(s32);
extern void RotMatrixZ(s32, void *);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern void func_80017714(void *);
extern SVECTOR_8017E6D8 D_801D542C[4];
extern struct PW8017E6D8 D_801D544C;
extern struct PW8017E6D8 D_801D5450;
extern u8 D_801D5454, D_801D5455, D_801D5456, D_801D5458, D_801D5459, D_801D545A;
extern int D_801D545C;
extern void func_8017E6D8(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d, SVECTOR_8017E6D8 *e, SVECTOR_8017E6D8 *f, s16 *g, struct PW8017E6D8 *h);
extern void aF8017ED80(void *param_1) __asm__("func_8017EB8C");
extern void aF8017ED80(void *param_1);
extern void aF8017EF54();
extern s32  func_8012C588(s32 a0, s32 a1);
extern u8  *func_8012913C();
extern void func_8017EB8C(s32);
extern void func_8017EF0C(s32 a0);
extern void func_8012B1B4(void*, void*);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern void func_8012BE54(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8017EA54(s32 a0, s32 a1);
extern void func_8017F0F4(s32 a0);
extern void func_80180354(s32, s32);
extern void func_8012B370(int a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8017F430(s32 param_1);
extern void (*D_801AAF88[])(void);
extern void func_8017F8E0(void *a0);
extern void (*D_801AAFA8[])(void);
extern void func_8017FA90(void *a0);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8017FB54(void *a0);
extern void func_8017ED60(void);
extern void func_8017FB8C(s32 *param);
extern void func_8017FBB4(s32 arg0);
extern void func_8017EB8C(s32 arg0);
extern void func_8017FD20(s32 *a0);
extern void func_8017FD54(u8 *param_1);
extern s32 D_801D55A0;
extern void func_80180354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern s32 func_80180384(s32 param_1);
extern s32 func_801805C8(s32 param_1);
extern void (*D_801ACD5C[])(void);
extern void func_80180868(void *a0);
extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);
extern int func_801808A4(int param_1, short param_2);
extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 a0);
extern void func_80180AB4(s32 a0);
extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);
extern void func_80180EB8(int param_1);
extern int  func_8012C354();
extern void func_800599B8();
extern void func_8001C214();
extern void func_80143970();
extern void func_8012B030();
extern void func_8012A828();
extern void func_8012B23C();
extern int  func_8012C658();
extern void func_8012C218();
extern void func_8012CAE4();
extern u8 D_801AD470[];
extern u8 D_801AD3B4[];
extern u8 D_801AD374[];
extern u8 D_801AD3BC[];
extern u8 D_801AD394[];
extern u8 D_801B16DC[];
extern u8 D_801B498C[];
extern u8 D_801AD4B0[];
extern void func_8018102C(int param_1);
extern void func_801811DC(s32 a0);
extern void func_8004914C();
extern void func_800491AC();
extern u8 *func_8012913C(s32 a0);
extern void func_8012A828(s32 a0, void * a1);
extern void func_80181468(s32 a0);
extern void func_8018192C(s32 a0);
extern s32 func_801823F0(void);
extern void func_80181AFC(s32 a0);
extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void *param_1);
extern int func_80143C74(short *, int);
extern void func_80181CEC(s32 a0);
extern unsigned char D_801AD450[];
extern void func_80182004(int param_1);
extern void func_801821FC(s32 a0);
extern void (*D_801AD568[])(short *);
extern void func_80182644(short *param_1);
extern void func_80182854(s32 a0);
extern void (*D_801AD5E0[])(s32);
extern s32 func_80143C74();
extern void func_80182C98(s32 a0);
extern void func_80128EA8();
extern void func_8012931C();
extern void func_801292C8();
extern int  func_8012D664();
extern u8  D_801AD3C4;
extern u8  D_801AD3D0;
extern u16 D_80126B96;
extern void func_80182EA8(s32 arg0);
extern void func_801832EC(s32 a0);
extern void func_80183444(void *a0);
extern void func_80183554(void);
extern void func_80183630(s32 a0);
extern void func_8012B370(int);
extern void func_801836F0(void);
extern void func_80183710(void *a0);
extern void func_80183824(void);
extern void func_80183920(s32 a0);
extern void func_801839E0(void);
extern Elem52_801B5094 D_801B5094[];
extern u8 D_801B522C[];
extern u8 D_801B51B4[];
extern u8 D_801CC180[];
extern u16 D_801CC674;
extern u16 D_801CC4CC;
extern s32 func_8012C354(s32 a0, void *a1);
extern s32 func_80143994(s32 a0, s32 a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012CAE4(s32 a0);
extern void func_8012B030(s32 a0);
extern void func_80183A70(s32 param_1);
extern u8 D_801CCCA0[];
extern void func_80183CDC(s32 param_1);
extern void func_80183F10(s32 param_1);
extern void func_8001C924(s32 a0, void *a1);
extern s32  func_8012BEE8();
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8018765C(s32 a0);
extern void func_80013350(s32 a0, void *a1);
extern u8 D_801BB67C;
extern u8 D_801B7EB8;
extern u8 D_801CC1E8[];
extern u8 D_801CD0E8[];
extern void func_8018457C(s32 p);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern void func_80142414(s32 a0, s16 a1);
extern void func_80184844(s32 p);
extern void func_80184904(s32 param_1);
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012E778(int param_1, int param_2);
extern s32  func_8012BCCC(s32 a0);
extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8018931C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_80189E60(s32 a0, s32 a1);
extern u8 D_801B4F5C[];
extern u8 D_801B5174[];
extern u8 D_801CC530[];
extern u8 D_801CC598[];
extern u8 D_801CC868[];
extern u8 D_801CC920[];
extern void func_80184C74(s32 p);
extern u8 D_801CC7A0[];
extern void func_80185268(s32 param_1);
extern u8 D_801B5164[];
extern void func_801877E4(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_80189284(void *a0, s32 a1, s32 a2);
extern s32  func_8012BEE8();   /* TU-canonical: an earlier call site passes zero args */
extern void func_80185320(s32 p);
extern void func_8012A828(s32, void*);
extern void func_801854C0(short *a0);
extern void func_80189380(s32 a0, void *a1, void *a2, s32 a3);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern u8 D_801CC3D0[];
extern u8 D_801CC358[];
extern u8 D_801B517C[];
extern u8 D_801B518C[];
extern void func_801854F8(s32 p);
extern u8        D_801B5184;
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern void func_80189380(s32, void*, void*, s32);
extern void func_8018931C(s32, void*, s32, s32, s32, s32);
extern s32  func_80013478(s32 a0, s32 a1);
extern void func_8018598C(s32 param_1);
extern void func_80187038(void);
extern void func_80185DA8(s32 arg0);
extern void func_80186EF4(s32 a0);
extern s32  func_8012DBD0(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32  func_8012CBF4(s32 a0);
extern s32  func_8012CBA4(s32 a0);
extern s32  func_80143B6C(s32 a0, s32 a1);
extern void func_80131E00();
extern void func_80131C78(s32 a0);
extern u8 D_801CCD68[];
extern void func_80186270(s32 a0);
extern void func_80189E60(s32 arg0, s32 arg1);
extern void func_80186ED4(s32 arg0);
extern void func_801874E4(s32 a0, s32 a1);
extern s32 D_801CD170;
extern void func_80186F78(s32 param_1);
extern s32 func_801893CC(s32 a0, s32 a1);
extern s32 func_80187250(s32 p);
extern s32  func_8012BC60(void *a0, void *a1);
extern s32  func_8012CEB0(void *a0, void *a1, s32 a2);
extern void func_8012ADE4(u8 *a0);
extern void func_80187320(s32 a0);
extern s32 func_800132BC(void *a0, void *a1);
extern s16 D_801B53B4[][4];
extern s32 D_801D55A8;
extern s32 func_80187844(s32 a0, s32 a1);
extern void (*D_801B53F4[])(void);
extern void func_80187924(void *a0);
/* ==== end §8b carried decl layer ==== */

#include "common.h"

/* ov_SC06_018 :: func_80187AEC  — actor state machine, jump-table switch on the
 * u16 state word at +0x34.  Jump table = jtbl_801D3AF0 (6 entries, 0..5), which
 * is DEFINED in asm/ov_SC06_018/data/tail18.data.s — this .s carries no data of
 * its own (§160c), so plain `extern`s are correct here.
 *
 * Family exemplar: reach x6.  Keys (all byte-forced, do NOT "clean up"):
 *
 * (1) §161a — the table is indexed from ZERO (`lhu 0x34 ; sltiu <6 ; sll 2`, no
 *     `addiu -1`) and jtbl entry[0] = 0x80187B3C is a REAL body, so `case 0:`
 *     carries the first arm.  No empty `case 0: break;` construction is needed
 *     (that idiom is only for tables whose entry[0] is the epilogue).
 *
 * (2) `s32 pad[1];` is LOAD-BEARING.  The target frame is 0x20 (args 0x10 +
 *     ra/s0 at 0x18/0x1C) but nothing else ever touches $sp — i.e. the original
 *     had one more local that optimisation left unreferenced.  Without it the
 *     frame compiles to 0x18 and the 6 prologue/epilogue immediates are wrong.
 *     Size matters: 4 bytes -> 0x20 (right), 8 bytes -> 0x28 (wrong).
 *     Same idiom as func_80187DD0 in this TU (`s32 pad[2];`).
 *
 * (3) Case 0's 0x102 write must be TWO separate stores in an if/else, not
 *     `uVar = 0x400; if (...) uVar = 0xC00; store;`.  With a live temp gcc keeps
 *     the value in $a0 and reuses it for the later `+0x400`; the target instead
 *     re-LOADS `lhu 0x102($s0)`.  Two stores kill the temp, the cross-jumper
 *     re-merges the single `sh`, and the reload comes back (cf. §160d).
 *
 * (4) Case 0's `iVar >= 4` test is written the "wrong" way round on purpose:
 *     the >= 4 arm is the fall-through in the target, the div arm is the branch
 *     target.  Writing `if (iVar < 4) {div} else {...}` swaps the two blocks.
 *
 * (5) Case 1 re-reads `*(s16 *)(param_1 + 0x70)` at BOTH tests instead of using
 *     one local.  A local gives `andi $v0,$v1,0x8000` (dir kept in $v1, 184
 *     ins); the two reads make cse copy the loaded value out first —
 *     `addu $v0,$v1,$zero ; andi $v1,$v1,0x8000` — which is the 185th
 *     instruction and also lets the delay-slot filler steal `andi $v1,$v0,0xF`.
 *
 * (6) func_8012CC40 is fleet-canonical `void`; its $v0 is used here, so it is
 *     called through a cast (§17a-1) rather than being re-declared.
 */

extern void func_8012CC40(s32 arg0, s32 arg1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32  func_80143B6C(s32 a0, s32 a1);       /* fleet-canonical */
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012E8C4(u8 *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_80189000(s32 a0, s32 a1);
extern s32  func_8018944C(s32 a0, s32 a1, s32 a2);
extern void func_8012C218(void *a0);

extern u8 D_801B5400;

void func_80187AEC(s32 param_1)
{
    s32 iVar;
    s32 t;
    u16 st;
    u16 uVar1;
    s32 pad[1];   /* see key (2): forces the 0x20 frame — never referenced */

    if (0xf < *(s16 *)(param_1 + 0xA)) {
        func_8012C218((void *)param_1);
        return;
    }
    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + *(u16 *)(param_1 + 0xFC);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + *(u16 *)(param_1 + 0xFE);
        if ((((s32 (*)(s32, s32))func_8012CC40)(
                 param_1,
                 ((*(u16 *)(param_1 + 0x70) & 0xF) * 8) + (s32)&D_801B5400) &
             0x2000) == 0) {
            return;
        }
        iVar = *(s32 *)(param_1 + 0x1C) + 1;
        *(s32 *)(param_1 + 0x1C) = iVar;
        if (iVar >= 4) {
            if ((*(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) & 0xFFFU) > 0x800U) {
                *(u16 *)(param_1 + 0x102) = 0xC00;
            } else {
                *(u16 *)(param_1 + 0x102) = 0x400;
            }
            t = *(u16 *)(param_1 + 0x70) & 0xF;
            if (t < 4 && t != 0) {
                *(u16 *)(param_1 + 0x102) = *(u16 *)(param_1 + 0x102) + 0x400;
            }
            *(s32 *)(param_1 + 0x1C) = 0x1E;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        } else {
            *(s32 *)(param_1 + 0x14) = -(0x80000 / iVar);
            func_80143B6C(param_1, 1);
        }
        return;
    case 1:
        iVar = func_8012B608((s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10),
                             (s32)*(s16 *)(param_1 + 0x102), 4);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + iVar;
        if (func_8012BEE8(param_1) == 0) {
            return;
        }
        st = *(u16 *)(param_1 + 0x34);
        *(s32 *)(param_1 + 0x1C) = 0x1E;
        *(u16 *)(param_1 + 0x34) = st + 1;
        if ((*(s16 *)(param_1 + 0x70) & 0x8000) != 0) {
            *(u16 *)(param_1 + 0x34) = st + 2;
        } else if ((*(s16 *)(param_1 + 0x70) & 0xF) == 4) {
            *(u16 *)(param_1 + 0x34) = 4;
            *(s32 *)(param_1 + 0x1C) = 0x1E;
        }
        return;
    case 2:
        func_8012E8C4((u8 *)param_1);
        if (func_8012BEE8(param_1) == 1) {
            func_8012C218((void *)param_1);
        }
        return;
    case 3:
        if (*(s16 *)(*(s32 *)(param_1 + 0x64) + 0x36) != *(s16 *)(param_1 + 0x10A) &&
            *(s32 *)(param_1 + 0xE0) == 0) {
            *(s32 *)(param_1 + 0x1C) = 0x1E;
            uVar1 = 2;
            if ((*(u16 *)(param_1 + 0x70) & 0xF) == 4) {
                uVar1 = 4;
            }
            *(u16 *)(param_1 + 0x34) = uVar1;
            *(s32 *)(param_1 + 0xE0) = 1;
        }
        return;
    case 4:
        if (func_8012BEE8(param_1) != 0) {
            *(s32 *)(param_1 + 0x1C) = 0xA;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            func_8012E8A8((u8 *)param_1);
            func_80189000(param_1, 1);
        }
        return;
    case 5:
        if (func_8018944C(param_1, 0x60, 0xA0) == 1) {
            func_8012C218((void *)param_1);
        }
        return;
    }
}


#include "common.h"

extern void func_8012C218(void *a0);
extern void func_8012E8A8(u8 *a0);

/* §48-C2: lwl/lwr/swl/swr block copy == a plain struct assign of a 2-byte-aligned struct */

void func_80187DD0(s32 param_1)
{
    s32 t1 = *(s32 *)(param_1 + 0x64);
    s32 pad[2];

    if (*(s16 *)(t1 + 0x36) != *(s16 *)(param_1 + 0x10A)) {
        func_8012C218((void *)param_1);
        return;
    }
    {
        if ((*(u32 *)(t1 + 0xE0) & 4) != 0) {
            func_8012E8A8((u8 *)param_1);
            return;
        }
        {
            s32 a2 = *(s32 *)(*(s32 *)(t1 + 0x20) + 0x20);
            s32 a3 = param_1 + 0xFC;

            if (a2 != 0) {
                if ((a2 & 0x1000000) != 0) {
                    s32 a1 = a2 & 0xFEFFFFFF;
                    register u32 v0 __asm__("$2");
                    u32 a0;
                    u32 v1a;
                    u32 v1b;
                    u32 v0b;
                    u32 v1;

                    *(u16 *)(param_1 + 0x102) = *(u16 *)(a1 + 0x66);

                    v0 = *(u32 *)(a1 + 0x60);
                    a0 = *(u8 *)(a1 + 0x61);
                    v1a = (v0 & 0xF) << 8;
                    a0 = a0 | v1a;
                    v1b = ((s32)v0 >> 16) & 0xFF;
                    v0b = (v0 & 0xF0) << 4;
                    v1 = v1b | v0b;
                    *(u16 *)(param_1 + 0x104) = (u16)a0;
                    *(u16 *)(param_1 + 0x106) = (u16)v1;

                    *(s16 *)(param_1 + 0xFC) = (s8)*(u8 *)(a1 + 0x63);
                    *(s16 *)(param_1 + 0xFE) = (s8)*(u8 *)(a1 + 0x64);
                    *(s16 *)(param_1 + 0x100) = (s8)*(u8 *)(a1 + 0x65);
                } else {
                    *(UAlign12 *)(param_1 + 0xFC) = *(UAlign12 *)(a2 + 0x90);
                }
                *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = a3;
            }

            if ((*(u32 *)(t1 + 0xE0) & 0x80) != 0) {
                if (*(u16 *)(param_1 + 0x34) == 0) {
                    s16 sVar2 = *(u16 *)(param_1 + 0x108) + 0x40;
                    *(s16 *)(param_1 + 0x108) = sVar2;
                    if (sVar2 > 0x200) {
                        *(u16 *)(param_1 + 0x108) = 0x200;
                        *(s16 *)(param_1 + 0x34) = *(s16 *)(param_1 + 0x34) + 1;
                    }
                } else {
                    u16 uVar3 = *(u16 *)(param_1 + 0x108) - 0x80;
                    *(u16 *)(param_1 + 0x108) = uVar3;
                    if ((s16)uVar3 < 0) {
                        *(u16 *)(param_1 + 0x108) = 0;
                        *(u16 *)(param_1 + 0x34) = 0;
                        *(u32 *)(t1 + 0xE0) = *(u32 *)(t1 + 0xE0) & ~0x80;
                    }
                }
            }

            *(u16 *)(a3 + 6) = *(u16 *)(a3 + 6) + *(u16 *)(param_1 + 0x108);

            *(u32 *)(param_1 + 4) = *(u32 *)(t1 + 4);
            *(u32 *)(param_1 + 8) = *(u32 *)(t1 + 8);
            *(u32 *)(param_1 + 0xC) = *(u32 *)(t1 + 0xC);

            *(UAlign8 *)(param_1 + 0x50) = *(UAlign8 *)(t1 + 0x50);

            {
                s32 dst = *(s32 *)(param_1 + 0x20);
                s32 src = *(s32 *)(t1 + 0x20);
                *(UAlign8 *)(dst + 0x10) = *(UAlign8 *)(src + 0x10);
            }
            {
                s32 dst = *(s32 *)(param_1 + 0x20);
                s32 src = *(s32 *)(t1 + 0x20);
                *(UAlign8 *)(dst + 0x18) = *(UAlign8 *)(src + 0x18);
            }
            {
                s32 src = *(s32 *)(t1 + 0x20);
                s32 dst = *(s32 *)(param_1 + 0x20);
                *(u32 *)(dst + 4) = *(u32 *)(src + 4);
            }
            {
                s32 src = *(s32 *)(t1 + 0x20);
                s32 dst = *(s32 *)(param_1 + 0x20);
                *(u16 *)(dst + 0x2C) = *(u16 *)(src + 0x2C);
            }
        }
    }
}



extern void (*D_801B554C[])(void);

void func_80188088(void *a0) {
    D_801B554C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

/* Sibling-search (cookbook §160g): every declaration below is TU-canonical, lifted verbatim
 * from src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c (the destination TU):
 *   func_8012C354  -- decl at TU:2846 "extern s32 func_8012C354(s32 a0, void *a1);"
 *   func_8012CAE4  -- decl at TU:2849 "extern void func_8012CAE4(s32 a0);"
 *   func_80143994  -- decl at TU:2847 "extern s32 func_80143994(s32 a0, s32 a1);"
 *   func_80188B00  -- ALREADY DEFINED in this TU at :3492 "void func_80188B00(s32 p)" (banked)
 *   func_8012C1B8  -- TU-canonical `void (void)` at :4123/:3929, called via the established
 *                     cast-through-function-pointer idiom (§161c) seen in this TU's own
 *                     func_80189A34 (:4138) and func_801894F0 (:3948) -- byte-identical spawn
 *                     idiom, same handle-alloc-then-null-check shape as our case 2.
 *   func_8001CA1C  -- not yet declared in THIS TU; canonical form taken from the sibling TU
 *                     ov_SC06_018_jr_80140608.c:1704 "extern void func_8001CA1C(s32 a0, s32 a1);"
 *   func_80188234  -- INCLUDE_ASM in this TU at :3206 (still unmatched); called here with the
 *                     object pointer and its own return discarded, so declared void(s32).
 * D_801B545C / D_801B5490 / D_801B5430 are new (undeclared anywhere in src/); declared as
 * plain byte arrays per this TU's own convention for opaque data blobs (e.g. D_801AD470[]
 * at TU:2791) -- only their address is used (func_8012C354's a1 is void*, func_8001CA1C's a1
 * is a raw s32 cast of the address), so element type is codegen-irrelevant.
 */
extern s32 func_8012C354(s32 a0, void *a1);
extern void func_8012CAE4(s32 a0);
extern s32 func_80143994(s32 a0, s32 a1);
extern void func_80188234(s32 a0);
extern void func_8012C1B8(void);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_80188B00(s32 p);

extern u8 D_801B545C[];
extern u8 D_801B5490[];
extern u8 D_801B5430[];

void func_801880C4(s32 a0) {
    s32 v1;
    s32 obj;

    v1 = *(u16 *)(a0 + 0x70) & 0xF;
    switch (v1) {
    case 0:
        if (func_8012C354(a0, D_801B545C) == 0) {
            return;
        }
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = a0 + 0xE8;
        *(u16 *)(a0 + 0x104) = 0x78;
        func_80188234(a0);
        func_80143994(a0, 0x1800);
        return;
    case 1:
        if (func_8012C354(a0, D_801B5490) == 0) {
            return;
        }
        *(u16 *)(a0 + 0x104) = 0xA0;
        if ((*(s16 *)(a0 + 0x70) & 0x8000) == 0) {
            *(s16 *)(a0 + 0x2) = 3;
            return;
        }
        *(s16 *)(a0 + 0x2) = 5;
        func_80143994(a0, 0x1800);
        return;
    case 2:
        obj = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(a0 + 0x20) = obj;
        if (obj == 0) {
            func_8012CAE4(a0);
            return;
        }
        func_8001CA1C(obj, (s32)D_801B5430);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x14CC;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x1199;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x58000000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
        func_80188B00(a0);
        return;
    default:
        return;
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC", func_80188234);

extern void func_8012C218(void *a0);
extern s32  func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80189000(s32 a0, s32 a1);
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BEE8(s32 a0);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_8012CBF4(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern u8  *func_8012913C(s32 a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

extern u8 D_801B54C4;
extern u8 D_801B5578[];
extern u16 D_80126CB4;
extern u16 D_80126CB6;
extern u16 D_80126CB8;

void func_8018829C(s32 param_1) {
    u16 uVar1;

    if (0xf < *(s16 *)(param_1 + 0xA)) {
        func_8012C218((void *)param_1);
        return;
    }

    {
        s32 base = (s32)&D_801B54C4;
        s32 r = func_8012D5E4(param_1, base, base + 8, 0x78);
        if (r == 1 || (*(u16 *)(param_1 + 0x5C) & 1) != 0) {
            func_80189000(param_1, 1);
            func_8012C218((void *)param_1);
            return;
        }
    }

    uVar1 = *(u16 *)(param_1 + 0x34);
    switch (uVar1) {
    default:
        return;
    case 0:
        {
            s32 sVar3 = func_8012B608((s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10), 0, 0x18);
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + sVar3;
        }
        {
            s32 r = func_8012CBF4(param_1);
            if (r != 0) {
                goto LAB_8018847c;
            }
        }
        {
            s32 r = func_8012BEE8(param_1);
            if (r == 0) return;
        }
        *(u16 *)(param_1 + 0xF4) = D_80126CB4;
        *(u16 *)(param_1 + 0xF6) = D_80126CB6;
        {
            u16 tmp = D_80126CB8;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            *(s32 *)(param_1 + 0x1C) = 0x3C;
            *(u16 *)(param_1 + 0xF8) = tmp;
        }
        return;
    case 1:
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) += func_8012B8E4(param_1, 0x20);
        {
            s32 r = func_8012BEE8(param_1);
            if (r != 0) {
                *(s32 *)(param_1 + 0x1C) = 0x5A;
                *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            }
        }
        break;
    case 2:
        break;
    }

    *(u16 *)(param_1 + 0xF2) = *(u16 *)(param_1 + 0xF2) - 0x100;
    func_8012B178(param_1, 0xFFEC0000);
    {
        s32 r = func_8012CBF4(param_1);
        if (r != 0) goto LAB_8018847c;
    }
    if (*(u16 *)(param_1 + 0x34) != 2) goto LAB_80188494;
    {
        s32 r = func_8012BEE8(param_1);
        if (r != 1) goto LAB_80188494;
    }
LAB_8018847c:
    *(u16 *)(param_1 + 2) = 9;
    func_80189000(param_1, 1);
    return;
LAB_80188494:
    {
        s32 iv = (s32)func_8012913C(0x80);
        if (iv == 0) return;
        {
            u16 out[4];
            ((void (*)(s32, void *, void *))func_8012F214)(param_1, D_801B5578, out);
            *(u16 *)(iv + 6) = out[0];
            *(u16 *)(iv + 0xA) = out[1];
            *(u16 *)(iv + 0xE) = out[2];
        }
        return;
    }
}


extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_801884F4(s32 param_1) {
    s32 obj;

    obj = *(s32 *)(param_1 + 0x64);
    *(s32 *)(param_1 + 0x48) = 0xC000;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(obj + 0x20) + 0x12);
    func_8012B2CC(param_1);
    func_8012B178(param_1, 0x20000);
    *(u16 *)(param_1 + 2) = 4;
    *(s32 *)(param_1 + 0x1C) = 0;
    *(u16 *)(param_1 + 0x34) = 0;
}


#include "common.h"

extern void func_8012C218(void *a0);
extern s32  func_8012BD14(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012CC64(s32 a0, s32 a1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32  func_80143B6C(s32 a0, s32 a1);   /* fleet-canonical */
extern void func_80189000(s32 a0, s32 a1);

extern u8 D_801B54E4;

void func_80188554(s32 param_1) {
    s32 v0;
    s32 iVar;

    if (0xf < *(s16 *)(param_1 + 0xA)) {
        func_8012C218((void *)param_1);
        return;
    }
    v0 = func_8012BD14(param_1);
    if (v0 < 0x1001) {
        goto LAB_tail;
    }
    if (*(u16 *)(param_1 + 0x34) == 0) {
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) - 0x40;
        v0 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801B54E4);
        if ((v0 & 0x2000) == 0) {
            return;
        }
        iVar = *(s32 *)(param_1 + 0x1c) + 1;
        *(s32 *)(param_1 + 0x1c) = iVar;
        if (iVar >= 4) {
            u16 tmp = *(u16 *)(param_1 + 0x34);
            *(s32 *)(param_1 + 0x1c) = 0xA;
            *(u16 *)(param_1 + 0x34) = tmp + 1;
            return;
        }
        *(s32 *)(param_1 + 0x14) = -(0x80000 / iVar);
        func_80143B6C(param_1, 1);
        return;
    }
    if (func_8012BEE8(param_1) != 1) {
        return;
    }
LAB_tail:
    *(u16 *)(param_1 + 2) = 9;
    func_80189000(param_1, 0);
}


void func_8018868C(s32 arg0) {
    s32 temp;
    temp = *(s32 *)(arg0 + 0x64);
    *(u16 *)(arg0 + 2) = 6;
    *(u16 *)(arg0 + 0x34) = 0;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(temp + 0x20) + 0x12);
}


// @class: struct
// @stuck: none — MATCH (276 ins, relocation-masked). Verified BOTH standalone (match_one) and
//          spliced into src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c (whole-TU cc1 -O2 clean,
//          masked structured_diff 0/276).
// Keys: (1) the first func_8012C218 call gets a NOP delay slot because reload_cse_regs deletes the
//           redundant `move a0,s1` -- $a0 still holds the incoming param on the fall-through path
//           (no CODE_LABEL between the prologue and the jal). The second call site is behind a
//           label, so the move survives. Source is the natural `func_8012C218((void *)param_1)` at
//           BOTH sites -- do NOT write a zero-arg call (it also breaks in-TU: the composite type
//           from the earlier file-scope `extern void func_8012C218(void *a0);` rejects 0 args).
//       (2) case 0's guard is an `||` with an early return -- that is what puts `beqz -> fail` then
//           `beq -> ok` (an `&&` would emit `bne -> fail`).
//       (3) `register s32 sVar2 __asm__("$2")` holds the p+0x34 reload in cases 1/2 so the two arms
//           cross-jump into the shared .L80188928 tail.
//       (4) `__asm__ __volatile__("")` after the func_8012C658 arm forces the `lw v1,0x1C(s1)`
//           reload before the cross-jumped `li v0,9` (§21 zero-byte re-tie).
//       (5) `-((iVar3 << 0x10) / 0x22)` reproduces the 0x78787879/sra-4 magic-divide by 34 + negu.
//       (6) `*p * 0xc` then `>>4` with the manual `if (x<0) x+=0xf` is the /16 rounding form.

extern void func_8012C218(void *a0);
extern void func_80189380(s32, void*, void*, s32);
extern s32  func_80013328(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CC64(s32 a0, s32 a1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32 func_8012C658(s32, s32, s32);
extern s32  func_80143B6C(s32 a0, s32 a1);   /* fleet-canonical */
extern s32  func_8012BEE8(s32 a0);
extern void func_80016714(void*, s32);
extern void func_80189000(s32 a0, s32 a1);

extern u8 D_801CD278;
extern u8 D_801B54EC;
extern u8 D_801B54F4;
extern u8 D_801B54E4;

void func_801886B0(s32 param_1) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_80126B5C;
    u16 uVar1;
    register s32 sVar2 __asm__("$2");
    s32 iVar3;
    s32 iVar4;
    s32 iVar5;
    u32 uVar4;
    s32 psVar5;
    u16 buf[8];
    s32 vec[3];

    if (0xf < *(s16 *)(param_1 + 0xA)) {
        func_8012C218((void *)param_1);
        return;
    }
    uVar1 = *(u16 *)(param_1 + 0x34);
    switch (uVar1) {
    case 0:
        psVar5 = *(s32 *)(param_1 + 0x64);
        if ((*(u16 *)psVar5 == 0) ||
            (*(s32 *)(psVar5 + 0x90) != (s32)&D_801CD278)) {
            func_8012C218((void *)param_1);
            return;
        }
        if (*(s32 *)(psVar5 + 0x94) < 0x11) {
            ((void (*)(void *, void *, void *, s32))func_80189380)((void *)psVar5, (void *)&D_801B54EC, buf, 5);
            *(s16 *)(param_1 + 6) = buf[0];
            *(s16 *)(param_1 + 0xA) = buf[1];
            *(s16 *)(param_1 + 0xE) = buf[2];
            return;
        }
        ((void (*)(void *, void *, void *, s32))func_80189380)((void *)psVar5, (void *)&D_801B54F4, buf, 4);
        ((void (*)(void *, void *, void *, s32))func_80189380)((void *)psVar5, (void *)&D_801B54F4, &buf[4], 5);
        *(s16 *)(param_1 + 6) =
            (s16)((*(s16 *)&buf[0] + *(s16 *)&buf[4]) >> 1);
        *(s16 *)(param_1 + 0xA) =
            (s16)((*(s16 *)&buf[1] + *(s16 *)&buf[5]) >> 1);
        *(s16 *)(param_1 + 0xE) =
            (s16)((*(s16 *)&buf[2] + *(s16 *)&buf[6]) >> 1);
        if (*(s32 *)(psVar5 + 0x94) != 0x19) {
            return;
        }
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        vec[0] = 0;
        vec[1] = 0xfff40000;
        iVar3 = func_80013328((s32)&D_80126B5C, param_1 + 4);
        vec[2] = -((iVar3 << 0x10) / 0x22);
        func_8012B14C(param_1, (s32)vec);
        *(s32 *)(param_1 + 0x48) = 0xc000;
        return;
    case 1:
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + 0x80;
        iVar3 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801B54E4);
        if (iVar3 == 0) {
            return;
        }
        sVar2 = *(u16 *)(param_1 + 0x34);
        *(s32 *)(param_1 + 0x1c) = 0;
        *(u16 *)(param_1 + 0x34) = sVar2 + 1;
        return;
    case 2:
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + 0x40;
        uVar4 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801B54E4);
        if ((uVar4 & 0x2000) == 0) {
            return;
        }
        iVar4 = *(s32 *)(param_1 + 0x1c) + 1;
        *(s32 *)(param_1 + 0x1c) = iVar4;
        if (iVar4 >= 4) {
            sVar2 = *(u16 *)(param_1 + 0x34);
            *(s32 *)(param_1 + 0x1c) = 0x1e;
            *(u16 *)(param_1 + 0x34) = sVar2 + 1;
            return;
        }
        iVar3 = *(s32 *)(param_1 + 0x10) * 0xc;
        if (iVar3 < 0) {
            iVar3 = iVar3 + 0xf;
        }
        *(s32 *)(param_1 + 0x10) = iVar3 >> 4;
        iVar5 = *(s32 *)(param_1 + 0x18) * 0xc;
        if (iVar5 < 0) {
            iVar5 = iVar5 + 0xf;
        }
        *(s32 *)(param_1 + 0x18) = iVar5 >> 4;
        *(s32 *)(param_1 + 0x14) = -(0x80000 / *(s32 *)(param_1 + 0x1c));
        func_80143B6C(param_1, 1);
        return;
    case 3:
        uVar4 = *(u32 *)(param_1 + 0x1c);
        if ((uVar4 - 0xe < 0xb) && ((uVar4 & 1) == 0)) {
            ((void (*)(s32, s32, s32))func_8012C658)(0x2a8, (s32)*(s16 *)(param_1 + 0x104), param_1);
            *(u16 *)(param_1 + 0x104) = *(u16 *)(param_1 + 0x104) + 1;
            __asm__ __volatile__("");
            uVar4 = *(u32 *)(param_1 + 0x1c);
        }
        if (uVar4 == 9) {
            *(u32 *)(*(s32 *)(param_1 + 0xcc) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0xcc) + 4) & 0x7fffffff;
            *(s16 *)(*(s32 *)(param_1 + 0xcc) + 8) = *(u16 *)(param_1 + 6);
            *(s16 *)(*(s32 *)(param_1 + 0xcc) + 0xa) =
                *(u16 *)(param_1 + 0xa) - 0x24;
            *(s16 *)(*(s32 *)(param_1 + 0xcc) + 0xc) = *(u16 *)(param_1 + 0xe);
        }
        if (*(s32 *)(param_1 + 0x1c) - 4U < 6) {
            *(s16 *)(*(s32 *)(param_1 + 0xcc) + 0x18) =
                *(u16 *)(*(s32 *)(param_1 + 0xcc) + 0x18) + 0x200;
            *(s16 *)(*(s32 *)(param_1 + 0xcc) + 0x1a) =
                *(u16 *)(*(s32 *)(param_1 + 0xcc) + 0x1a) + 0x200;
        }
        iVar3 = func_8012BEE8(param_1);
        if (iVar3 != 1) {
            return;
        }
        ((void (*)(s32, s32))func_80016714)(*(s32 *)(param_1 + 0xcc), 0x38);
        *(s16 *)(param_1 + 2) = 9;
        func_80189000(param_1, 0);
        return;
    }
    return;
}


#include "common.h"

extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern void func_8012B260(u8 *a0);

void func_80188B00(s32 p) {
    s32 g10[4];   /* sp+0x10 */
    u16 g20[4];   /* sp+0x20 */
    s32 buf28[8]; /* sp+0x28 */
    u16 v;

    g10[2] = 0xFFF00000;
    g10[1] = 0;
    g10[0] = 0;
    g20[0] = 0x10;
    v = *(u16 *)(*(s32 *)(*(s32 *)(p + 0x64) + 0x20) + 0x12) +
        *(u16 *)(p + 0xFC);
    g20[1] = v;
    *(u16 *)(p + 0xFE) = v;
    g20[2] = 0;
    ((void (*)(void *, void *))func_80049CAC)(g20, buf28);
    ((void (*)(void *, void *, s32))func_800484EC)(buf28, g10, p + 0x10);
    *(u16 *)(p + 2) = 8;
    *(s32 *)(p + 0x1C) = 0x40;
    ((void (*)(s32))func_8012B260)(p);
}


#include "common.h"

/* SVECTOR/MATRIX are already typedef'd (unsuffixed) in src/shared/engine_types.h,
 * pulled into the real TU via "../shared/engine_core.h" (see e.g. func_8017D648,
 * func_80184C74, func_8018CD04 in this same TU). match_one compiles this file
 * standalone (-Iinclude only, no src/shared on the path), so the two typedefs
 * are reproduced locally here with byte-identical layout for iteration; DROP
 * these two typedefs when splicing the body into the real TU (it already has
 * them) -- keep everything else verbatim.
 */



/*
 * func_80188B9C  (ov_SC06_018, TU ov_SC06_018_jr_8017C24C, 110 ins)
 *
 * Exemplar of an OPEN-ONLY h_norm cluster (6 members).  Draft built from the
 * TU's own already-matched neighbours:
 *   - func_80188E10 (same TU, ~L7813): the Ent struct field shapes (f20/f58
 *     collision volumes, f70 sub-kind) and the func_80135888(D_80126B78,
 *     D_80126B90, &a, &b) collision-probe idiom, plus the
 *     func_8012F568(1, 1, *(s16*)(self->f20 + 0x12), arg3, &b, D_801152A8)
 *     "punt" call shape (byte-identical arg pattern to this fn's else-arm).
 *   - func_80184C74 (same TU, ~L6582): the *exact* gte_SetRotMatrix /
 *     gte_SetTransMatrix inline-asm expansion, including the operand form
 *     `*(s32 *)(p + 0x20) + 0x34` for gte_SetTransMatrix (this fn's operand
 *     is byte-identical to that one).
 *   - func_8017D648 (same TU, ~L3340): func_80049CAC(SVECTOR*, MATRIX*)
 *     call shape (build rotation matrix from an angle SVECTOR) using the
 *     TU's bare (unsuffixed) SVECTOR/MATRIX typedefs from engine_types.h.
 *   - ov_SC03_099_jr_80140608.c func_80143D28: param_1 typed plain `s32`,
 *     `*(s32*)(param_1+0x20)` field-20 pointer idiom, `*(s16*)(param_1+0xfe)`
 *     field, and the func_8012BEE8(param_1)/func_8012C218((void*)param_1)
 *     tail-call pair -- byte-identical shape to this fn's tail.
 *
 * Frame is 0x78; locals mat/sv/b/c/flag occupy sp+0x20..sp+0x60 with NO gap
 * (0x20+4*8 = 0x40 bytes), so declaration order below IS the frame layout
 * (cookbook L5-style rule): mat first (lowest addr, sp+0x20), then sv
 * (sp+0x40), b (sp+0x48, RotTransSV out #1), c (sp+0x50, RotTransSV out #2),
 * flag (sp+0x58, RotTransSV's shared 3rd/"flag" arg).
 */

extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8   D_801152A8[];
extern SVECTOR D_801B54D4[];

extern void func_80049CAC(s32 a0, s32 a1);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32  func_8012CBF4(s32 a0);
extern s32  func_8012BEE8();
extern void func_8012C218(void *a0);
extern s32  func_80132EF4(s32 a0, s32 a1);
extern s32  func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

#define gte_SetRotMatrix(r0) __asm__ volatile (  \
    "lw $12, 0( %0 );"                           \
    "lw $13, 4( %0 );"                           \
    "ctc2 $12, $0;"                              \
    "ctc2 $13, $1;"                              \
    "lw $12, 8( %0 );"                           \
    "lw $13, 12( %0 );"                          \
    "lw $14, 16( %0 );"                          \
    "ctc2 $12, $2;"                              \
    "ctc2 $13, $3;"                              \
    "ctc2 $14, $4"                               \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile ( \
    "lw $12, 20( %0 );"                          \
    "lw $13, 24( %0 );"                          \
    "ctc2 $12, $5;"                              \
    "lw $14, 28( %0 );"                          \
    "ctc2 $13, $6;"                              \
    "ctc2 $14, $7"                               \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "$13", "$14" )

void func_80188B9C(s32 param_1)
{
    MATRIX mat;
    SVECTOR sv;
    SVECTOR b;
    SVECTOR c;
    SVECTOR flag;
    s32 iVar;

    sv.vx = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10);
    sv.vy = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12);
    sv.vz = 0;
    func_80049CAC((s32)&sv, (s32)&mat);

    gte_SetRotMatrix(&mat);
    gte_SetTransMatrix(*(s32 *)(param_1 + 0x20) + 0x34);

    RotTransSV(&D_801B54D4[0], &b, &flag);
    RotTransSV(&D_801B54D4[1], &c, &flag);

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&b, (s32)&c) != 0) {
        s16 sVar1 = *(s16 *)(param_1 + 0xFE);
        func_8012F568(1, 1, sVar1, 0x50, (s32)&c, (s32)D_801152A8);
    } else {
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) - 0x100;
        iVar = func_8012CBF4(param_1);
        if (iVar != 0) {
            s16 sVar1 = *(s16 *)(param_1 + 6);
            s16 sVar2 = *(s16 *)(param_1 + 0xA);
            s16 sVar3 = *(s16 *)(param_1 + 0xE);
            func_80146A6C(6, (void *)param_1, sVar1, sVar2, sVar3, 0, 0);
            iVar = func_80132EF4(param_1, 0x22);
            if (iVar != 0) {
                *(u16 *)(iVar + 0x34) = 0x2000;
            }
        } else {
            iVar = func_8012BEE8(param_1);
            if (iVar == 0) {
                return;
            }
        }
    }
    func_8012C218((void *)param_1);
}


extern void func_8012E8A8(u8*);

void func_80188D54(void *a0)
{
    ((void (*)(void *))func_8012E8A8)(a0);
    *(u32 *)(a0 + 0x1C) = 0xA;
    *(u16 *)(a0 + 0x5C) = 0;
    *(u16 *)(a0 + 0x2) = 0xA;
}


void func_80188D90(s32 a0)
{
    extern s32 func_8012D624(s32 a0, s32 a1, s32 a2);
    extern s32 func_8018944C(s32 a0, s32 a1, s32 a2);
    extern void func_8012C218(void *a0);
    extern u16 D_80126B96;

    if (*(u16 *)(a0 + 0x70) & 1) {
        if (func_8012D624(a0, 0x60, *(s16 *)(a0 + 0x104)) == 1) {
            D_80126B96 = 0x4001;
        }
    }
    if (func_8018944C(a0, 0x60, *(s16 *)(a0 + 0x104)) == 1) {
        func_8012C218((void *)a0);
    }
}


/* func_80188E10 @ ov_SC06_018 (subseg ov_SC06_018_jr_8017C24C) — 124 ins. MATCH.
 *
 * GATE: .venv/bin/python tools/match_one.py func_80188E10 \
 *         --c .run/wave-s40/ov_SC06_018/func_80188E10.c \
 *         --asm-subdir asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_8017C24C
 *
 * ------------------------------------------------------------------ what it is
 * "Try to hand this object off to another live entity of kind 0x282."
 *   1. Build two 8-byte position vectors off `self` via func_8012F214 (the
 *      fleet's local->world transform; see the ov_SC02_026 walker family,
 *      e.g. src/ov_SC03_103/ov_SC03_103_jr_8017C294.c:4106 func_8017EC0C, which
 *      is the byte-matched sibling this draft's types were lifted from).
 *   2. Keep a third copy of the destination vector (`c = b`) — 8 bytes at
 *      align 2, so gcc emits the inline lwl/lwr + swl/swr block move, exactly
 *      the "8 bytes, align 2 -> lwl/lwr/swl/swr copy" note carried in that
 *      sibling.  This is why `c` must be a STRUCT ASSIGN, not a memcpy.
 *   3. If the global-collision probe func_80135888(D_80126B78, D_80126B90, &a, &b)
 *      says the move is blocked, punt to func_8012F568 and return 1.
 *   4. Otherwise walk the 0x60-entry / 0x10C-stride entity table D_801202A0
 *      looking for a 0x282 entity that (a) matches `kind` (or, when
 *      kind == 0xFFFF, only self->f70), (b) is not `self`, and (c) passes the
 *      same collision probe against its own f20/f58 volumes.  First hit gets
 *      state 9 and func_80189000(e, 0); return 1.  No hit -> 0.
 *
 * ---------------------------------------------------------------- the levers
 * L1  ARG 5 IS A `u16` (stack slot 0x60(sp) read with `lhu`).  The redundant
 *     `andi $v1,$s2,0xffff` in the target is gcc's zero_extendhisi2 for the
 *     HImode->SImode widening at `kind != 0xFFFF`; it comes free with a plain
 *     ANSI `u16` param and CANNOT be reproduced from an `s32`/`s16` param.
 *     That same zero-extended $v1 is then reused as the loop compare operand
 *     (`addu $s4,$v1,$zero`), which is why the kind test inside the loop must
 *     be written against `kind` itself and not a re-cast copy.
 *
 * L2  `i` MUST BE INITIALISED IN EACH LOOP'S for-INIT, NOT ONCE BEFORE THE
 *     `if`.  This is the whole match.  <-- the only residual v1 had.
 *     With `e = ...; i = 0; if (kind != 0xFFFF) {...}` the draft is 124/124
 *     instructions with FOUR bytes wrong: `kind` lands in $s4 instead of $s2
 *     (and the two prologue `sw`s swap slots to follow it).  Reason (regalloc.md
 *     K3/K5, class RC-3): `kind` is the lowest-density allocno (2 refs over a
 *     ~50-insn range) so it is assigned LAST, and find_reg then takes the
 *     LOWEST-numbered non-conflicting callee-saved register.  Hoisting `i = 0`
 *     above the `andi` that reads `kind` makes `i`'s live range OVERLAP
 *     `kind`'s, so $s2 becomes a conflict and $s4 is the next free slot.
 *     Sinking `i = 0` into both for-inits removes the overlap -> $s2.
 *     The single `addu $s2,$zero,$zero` you see in the delay slot of the
 *     `beq` is dbr: it lifts the fall-through arm's `i = 0` into the slot and
 *     drops the other arm's copy as redundant (both arms set it before any
 *     use, so it is safe on both paths).  Do NOT "simplify" it back to one
 *     shared initialiser — that is the 4-byte regression.
 *
 * L3  THE ARMS ARE `!=` FIRST.  `if (kind != 0xFFFF) {kind-or-self loop}
 *     else {self-only loop}` gives `beq $v1,$v0,<else>` with the kind-aware
 *     loop falling through, which is the target order.  Writing it as
 *     `if (kind == 0xFFFF)` emits `bne` and swaps the two bodies.
 *
 * L4  BOTH ARMS' HIT-BLOCKS ARE TEXTUALLY IDENTICAL, which lets jump.c's
 *     cross-jump tail-merge collapse them: the second loop's
 *     `bnez $v0,.L80188F5C` branches into the FIRST loop's
 *     `sh 9; jal func_80189000; return 1` block.  Keep them identical.
 *
 * L5  LOCAL DECL ORDER IS THE FRAME LAYOUT (regalloc.md K1/K7): `a`,`b`,`c`
 *     land at 0x18 / 0x20 / 0x28, immediately above the 0x18-byte outgoing-arg
 *     area that func_8012F568's 6 arguments force.  Frame 0x50.  Reordering
 *     the three declarations shifts every sp displacement.
 *
 * L6  `e != self` is a POINTER compare against the `self` param (`beq $s1,$s3`),
 *     so `self` must be typed as the same Ent pointer, not an s32.
 *
 * ---------------------------------------------------------------- banking note
 * The real TU src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c already declares
 * `extern u8 D_801202A0[];` (L384), `extern s32 func_80135888(s32,s32,s32,s32);`
 * (L589), `extern void func_8012F214(s32,s32,s32);` (L2641),
 * `extern void func_80189000(s32 a0, s32 a1);` (L7388, and DEFINES it at L7711)
 * and `extern u8 D_801152A8[];` (L598) — all fleet-canonical and identical to
 * the spellings below, so only the two `D_80126B7 8/90` pointer externs
 * (canonical form `extern s32 *D_80126B78;`, 3297 fleet occurrences) and the
 * two local typedefs need to travel.  Uniquify the typedef names per §120 if
 * the TU already carries a V4/Ent (it carries neither of these two spellings).
 *
 * SIBLINGS (the 5 other h_norm members): every DATA symbol this body touches —
 * D_801202A0, D_801152A8, D_80126B78, D_80126B90 — is RESIDENT (fixed VA, not
 * per-overlay tail.data), and three of the four callees (func_8012F214,
 * func_80135888, func_8012F568) are resident too.  The ONLY per-overlay symbol
 * is func_80189000, and in this overlay it is defined in the SAME TU
 * (ov_SC06_018_jr_8017C24C.c:7711).  So the §40 remap for the siblings is
 * expected to be near-identity: re-point func_80189000 at each sibling's own
 * address and check that sibling TU's canonical spellings for the four externs
 * before sweeping (§56b — carry the TU's types, not this draft's).
 */

typedef struct { u16 x, y, z, w; } V4_80188E10;

typedef struct {
    u16 f0;                     /* 0x00  entity kind; 0x282 is the one we want */
    s16 f2;                     /* 0x02  state -> 9 on a hit                   */
    u8  p04[0x20 - 0x04];
    s32 f20;                    /* 0x20  collision volume A                    */
    u8  p24[0x58 - 0x24];
    s32 f58;                    /* 0x58  collision volume B                    */
    u8  p5C[0x70 - 0x5C];
    s16 f70;                    /* 0x70  sub-kind / owner tag                  */
    u8  p72[0x10C - 0x72];      /* stride 0x10C, 0x60 entries (0x6480)         */
} Ent_80188E10;

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_80189000(s32 a0, s32 a1);

extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8   D_801152A8[];
extern u8   D_801202A0[];

s32 func_80188E10(Ent_80188E10 *self, s32 arg1, s32 arg2, s32 arg3, u16 kind) {
    V4_80188E10 a;              /* 0x18(sp) */
    V4_80188E10 b;              /* 0x20(sp) */
    V4_80188E10 c;              /* 0x28(sp) */
    Ent_80188E10 *e;
    s32 i;

    func_8012F214((s32)self, arg1, (s32)&a);
    func_8012F214((s32)self, arg2, (s32)&b);
    c = b;                                              /* L2: lwl/lwr block move */
    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&a, (s32)&b) != 0) {
        func_8012F568(1, 1, *(s16 *)(self->f20 + 0x12), arg3, (s32)&b, (s32)D_801152A8);
        return 1;
    }
    e = (Ent_80188E10 *)D_801202A0;
    if (kind != 0xFFFF) {                               /* L3 */
        for (i = 0; i < 0x60; i++, e++) {               /* L2: i=0 HERE, not above */
            if (e->f0 == 0x282 && (e->f70 == kind || e->f70 == self->f70) && e != self &&
                func_80135888(e->f20, e->f58, (s32)&a, (s32)&c) != 0) {
                e->f2 = 9;                              /* L4: keep identical */
                func_80189000((s32)e, 0);
                return 1;
            }
        }
        return 0;
    } else {
        for (i = 0; i < 0x60; i++, e++) {               /* L2 */
            if (e->f0 == 0x282 && e->f70 == self->f70 && e != self &&
                func_80135888(e->f20, e->f58, (s32)&a, (s32)&c) != 0) {
                e->f2 = 9;                              /* L4: keep identical */
                func_80189000((s32)e, 0);
                return 1;
            }
        }
        return 0;
    }
}


#include "common.h"

extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern s32 func_8012C658(s32, s32, s32);
extern void func_80189E60(s32 a0, s32 a1);
extern s32 rand(void);

void func_80189000(s32 a0, s32 a1) {
    s32 buf10[8];    /* sp+0x10 (0x20) - func_80049CAC out / func_800484EC in */
    s32 g40[4];      /* sp+0x30, only [0..2] used - func_800484EC vec3 arg */
    u16 g30[4];      /* sp+0x40, only [0..2] used - func_80049CAC vec3 arg */
    unsigned int buf48[2]; /* sp+0x48 (8) - func_8012B0B4 output */
    unsigned int *p48;
    s32 i;
    s32 baseY;
    s32 e;
    u32 uVar;
    s32 scratch;
    s32 tmp;

    i = 0;
    p48 = buf48;
    baseY = 0x100;
    do {
        e = func_80132EF4(a0, 0x23);
        if (e != 0) {
            *(s16 *)(e + 0x34) = rand() % 0x4000 + 0x1000;
            *(u16 *)(*(s32 *)(e + 0x20) + 0x2c) = 0xc008;

            func_8012B0B4(p48, rand() % 0x1000, rand() % 0x58);

            tmp = *(s32 *)buf48;
            *(s16 *)(e + 6) = *(s16 *)(e + 6) + (s16)tmp;
            *(s16 *)(e + 0xe) = *(s16 *)(e + 0xe) + (s16)(tmp >> 16);

            tmp = rand();
            scratch = tmp % 0x80;
            uVar = rand();
            g30[0] = (uVar & 1) == 0 ? -scratch + 0x400 : scratch + 0x400;

            scratch = rand() % 0xc0;
            uVar = rand();
            g30[1] = (uVar & 1) != 0 ? baseY + scratch : baseY - scratch;

            g30[2] = 0;
            g40[1] = 0;
            g40[0] = 0;
            g40[2] = (rand() % 4 + 3) << 16;

            ((void (*)(void *, void *))func_80049CAC)(g30, buf10);
            ((void (*)(void *, void *, s32))func_800484EC)(buf10, g40, e + 0x10);
        }
        i++;
        baseY += 0x200;
    } while (i < 8);

    e = func_80132EF4(a0, 0x23);
    if (e != 0) {
        *(u16 *)(e + 0x34) = 0x7ff1;
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2c) = 0xc004;
        *(s32 *)(e + 0x14) = 0xfffb0000;
    }

    i = 0;
    do {
        func_8012C658(0x29d, (u16)a1, a0);
        i++;
    } while (i < 4);

    func_80189E60(a0, 0x95e);
}


s32 func_80189284(void *a0, s32 a1, s32 a2) {
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern s32 func_8012B70C(s16 *a0, s16 *a1);
    u16 buf[3];
    s32 d;

    buf[0] = D_80126B5E;
    buf[1] = D_80126B62;
    buf[2] = D_80126B66;
    d = (func_8012B70C((s16 *)a0, (s16 *)buf) - (s16)a1) & 0xFFF;
    if (d < 0x800) {
        return d < (s16)a2;
    } else {
        return (0x1000 - d) < (s16)a2;
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC", func_8018931C);

extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_80189380(s32 a0, void *a1, void *a2, s32 a3) {
    s32 buf0;
    s32 buf1;
    s32 buf2;
    s32 temp[8];
    func_8012EC04(a0, a3, temp);
    func_8012F14C((s32)temp, (s32)a1, (s32)a2);
}



extern s32 func_8012B6D4(s16 *a0, s16 *a1);

// @class: branch-polarity
// @stuck: none — MATCH (32 ins), iteration 2. §3-T4: gcc-2.7.2 lays this out as
// "branch TO the then-arm, fall through to the else", so the source condition is
// `d < 0x800` (the bnez sense read off the target opcode), NOT Ghidra's inverted
// arm order. The wrong polarity also cost one instruction (match_one printed
// LENGTH-DRIFT/-1): with the arms swapped, the `sll $v0,$s0,16` of the s16 param
// lands in the branch delay slot and is SHARED by both arms; the correct polarity
// puts `addiu $v1,$zero,0x1000` there and each arm gets its own sll/sra.
// a1 is an ANSI s16 param (sign-extended at each use, once per arm) — not K&R §43.
s32 aF801893CC(s32 a0, s16 a1) __asm__("func_801893CC");
s32 aF801893CC(s32 a0, s16 a1)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_80126B5C;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 *D_80126B78;
    s32 d;

    d = (func_8012B6D4((s16 *)&D_80126B5C, (s16 *)(a0 + 4)) -
         *(s16 *)((s32)D_80126B78 + 0x12)) & 0xFFF;
    if (d < 0x800) {
        return d < a1;
    } else {
        return (0x1000 - d) < a1;
    }
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_80132EF4(s32 a0, s32 a1);

s32 func_8018944C(s32 param_1, s32 a1, s32 a2)
{
    s32 e;

    if (func_8012BEE8(param_1) != 0) {
        e = func_80132EF4(param_1, 0x22);
        if (e != 0) {
            *(u16 *)(e + 0x34) = 0x7FFF;
            *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = 0xC006;
            *(s32 *)(e + 0x14) = 0xFFFE0000;
        }
        return 1;
    }
    return 0;
}



extern void (*D_801B5580[])(void);

void func_801894B4(void *a0) {
    D_801B5580[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 rand(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern u8 D_801B5588[];

void func_801894F0(s32 param_1) {
    s32 unused[2]; /* dead 8-byte local — frame padding (cookbook idiom 6) */
    s32 obj;
    s16 raw;
    s32 r;
    s32 sgn;
    s32 v;
    u8 *tbl;
    s16 *p;
    s32 q;
    s32 w;

    obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj == 0) {
        func_8012CAE4(param_1);
        return;
    }
    *(s32 *)(param_1 + 0x20) = obj;
    func_8001C214(obj, 0);

    raw = rand();
    r = raw;
    *(u16 *)(obj + 0x2C) = *(u16 *)(obj + 0x2C) | 0x10;
    v = r % 384 + 0x400;
    *(s16 *)(obj + 0x1C) = v;
    *(s16 *)(obj + 0x1A) = v;
    *(s16 *)(obj + 0x18) = v;
    sgn = -1;
    if (raw & 1) {
        sgn = 1;
    }
    *(s16 *)(obj + 0x10) = sgn * (r % 128) - 0x300;
    *(s16 *)(obj + 0x12) = r % 4096;
    *(s32 *)(param_1 + 0x48) = 0xC000;
    *(u16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x19;
    func_8012B2CC(param_1);
    func_8012B178(param_1, -0xC0000 - ((r % 8) << 16));
    *(s32 *)(param_1 + 0x1C) = 0x3C;
    *(s16 *)(param_1 + 0xFE) = rand() & 0xF0;
    *(s16 *)(param_1 + 0x100) = rand() & 0x1F0;
    *(s16 *)(param_1 + 0x102) = rand() & 0x30;
    tbl = &D_801B5588[(*(u16 *)(param_1 + 0x70) & 0xF) * 4];

    p = (s16 *)(param_1 + 0xDC);

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q - 0x18;
    } else {
        w = q - 0x18;
    }
    p[0] = w;
    p[1] = 0;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q - 0x18;
    } else {
        w = q - 0x18;
    }
    p[2] = w;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[4] = w;
    p[5] = 0;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q - 0x18;
    } else {
        w = q - 0x18;
    }
    p[6] = w;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q - 0x18;
    } else {
        w = q - 0x18;
    }
    p[8] = w;
    p[9] = 0;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[10] = w;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[12] = w;
    p[13] = 0;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[14] = w;

    *((u8 *)p + 0x20) = tbl[0];
    *((u8 *)p + 0x21) = tbl[1];
    *((u8 *)p + 0x22) = tbl[2];
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


#include "common.h"

extern s32  func_8012CBF4(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);   /* TU-canonical (ov_SC06_018_jr_8017C24C L5455) */
extern void func_80017274(s32 a0, s32 a1);

void func_80189954(s32 param_1) {
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + *(u16 *)(param_1 + 0xFE);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + *(u16 *)(param_1 + 0x100);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + *(u16 *)(param_1 + 0x102);

    if (func_8012CBF4(param_1) != 0 || func_8012BEE8(param_1) != 0) {
        func_8012C218((void *)param_1);
    } else {
        func_80017274(param_1 + 0xDC, *(s32 *)(param_1 + 0x20) + 0x34);
    }
}



extern void (*D_801B55A0[])(void);

void func_801899F8(void *a0) {
    D_801B55A0[*(u16 *)((s32)a0 + 0x2)]();
}


/* func_80189A34 (ov_SC06_018, TU ov_SC06_018_jr_8017C24C) -- 125 ins, match_one MATCH.
 *
 * Template: the sibling TU ov_SC06_032_jr_8017C24C's func_80184294 (same jr_8017C24C TU
 * name in another overlay) supplied the whole spawn idiom -- func_8012C1B8 handle alloc,
 * func_8001C214(obj,0), the rand()%N +- sign pairs, func_8012B0B4 into a stack buf,
 * func_8012B2CC, the +0x1C state / +0x2 substate epilogue (cookbook §71).
 *
 * Two levers were needed on top of a straight transcription:
 *
 * 1. TWO SEPARATE handle locals (`obj` / `o2`), cookbook §76.  Reusing ONE local for the
 *    prologue handle AND the later `*(s32*)(param_1+0x20)` reload makes it a GLOBAL allocno
 *    (live across calls) -> `move $s3,$v0` + the +0x20 store falls out of the `bnez` delay
 *    slot -> LENGTH-DRIFT +1 and 108 mismatches.  With two locals `obj` stays a LOCAL
 *    allocno in $v0, the store fills the delay slot, and only the reload gets $s3.
 *
 * 2. STATEMENT ORDER 0x6 / 0xE / 0xA, NOT 0x6 / 0xA / 0xE (sched.md §S1, LUID tie-break).
 *    The three post-func_8012B0B4 field updates all tie at the same sched1 priority, so the
 *    ready-list order is source order: writing the +0xE update (which owns the `sra $a1,16`)
 *    before the +0xA update puts `sra` ahead of `addiu $v1,-0x10` exactly as the target has
 *    it.  sched2 then re-sorts the three `sh` stores back to 6 / A / E, so the source order
 *    is NOT the emitted store order -- do not "fix" this back.
 *    Boost-based variants do NOT work here: `hi = t >> 16` as a fresh single-set local is
 *    birthing-boosted (§S2) and sinks to its consumer, landing on the same wrong order as
 *    the inline form (5 placements tested); killing the boost with `t >>= 16` (6 off) or by
 *    reusing the multi-set `v` (13 off) is worse.  The plain A/C/B permutation is the fix.
 *
 * Declarations are the TU-canonical ones already present in ov_SC06_018_jr_8017C24C.c, so
 * this drops in without a loose-typing conflict; func_8012C1B8's canon is `void (void)`, hence
 * the ov_SC06_032 cast-through-function-pointer idiom for the return value.
 *
 * No overlay-local data symbols are referenced (everything is param_1-relative or a fixed
 * shared-engine callee), so the 5 h_norm siblings are a verbatim copy -- no symbol remap.
 */
#include "common.h"

extern s32  rand(void);
extern void func_8012C1B8(void);   /* TU-canonical (ov_SC06_018_jr_8017C24C) */
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);  /* TU-canonical */
extern void func_8012B2CC(s32 a0);

void func_80189A34(s32 param_1) {
    u32 buf[2];
    s32 obj;
    s32 o2;
    s32 base;
    s32 off;
    s32 v;
    s32 t;

    obj = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = obj;
    if (obj == 0) {
        func_8012CAE4(param_1);
    } else {
        func_8001C214(obj, 0);
        if ((*(s16 *)(param_1 + 0x70) & 0x8000) == 0) {
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = -0x80 - (rand() % 0x300);
            o2 = *(s32 *)(param_1 + 0x20);
            off = rand() % 0xC0;
            base = *(s16 *)(param_1 + 0x70) * 0x300 + 0x180;
            if (rand() & 1) {
                v = base + off;
            } else {
                v = base - off;
            }
            *(s16 *)(o2 + 0x12) = v;
            func_8012B0B4(buf, *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + 0x800,
                          rand() % 0x10 + 8);
            t = buf[0];
            *(u16 *)(param_1 + 0x6) = *(u16 *)(param_1 + 0x6) + t;
            *(u16 *)(param_1 + 0xE) = *(u16 *)(param_1 + 0xE) + (t >> 16);
            *(u16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x10;
            func_8012B2CC(param_1);
            *(s32 *)(param_1 + 0x1C) = 4;
            *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
        } else {
            *(s16 *)(param_1 + 0xDC) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xCC);
            *(s16 *)(param_1 + 0xDE) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xCE);
            *(s16 *)(param_1 + 0xE0) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xD0);
            *(s16 *)(param_1 + 0xE4) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xD4);
            *(s16 *)(param_1 + 0xE6) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xD6);
            *(s16 *)(param_1 + 0xE8) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xD8);
            *(s16 *)(param_1 + 0x2) = 2;
            *(s32 *)(param_1 + 0x1C) = 8;
        }
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern s32 func_80017758(void *a0, void *a1);

void func_80189C28(void *a0)
{
    u8 buf[0x34];

    if (*(u16 *)((u8 *)a0 + 0x34) == 0) {
        *(s32 *)((u8 *)a0 + 0xE0) = *(s32 *)((u8 *)a0 + 0xE0) - 0x14;
        if (func_8012BEE8((s32)a0) != 0) {
            *(u16 *)((u8 *)a0 + 0x34) = *(u16 *)((u8 *)a0 + 0x34) + 1;
        }
    } else {
        s32 v1 = *(s32 *)((u8 *)a0 + 0x64);
        if (*(s32 *)(*(s32 *)(v1 + 0x20) + 4) < 0 || *(u16 *)v1 == 0) {
            func_8012C218(a0);
            return;
        }
    }

    *(s16 *)(buf + 0x00) = 4;
    *(s16 *)(buf + 0x08) = -4;
    {
        s16 c = 0xC;
        *(s16 *)(buf + 0x02) = 0;
        *(s16 *)(buf + 0x04) = 0;
        *(s16 *)(buf + 0x0A) = 0;
        *(s16 *)(buf + 0x0C) = 0;
        *(s16 *)(buf + 0x10) = c;
    }
    *(s16 *)(buf + 0x12) = 0;
    {
        s32 t1 = *(s32 *)((u8 *)a0 + 0xE0);
        s32 t2;
        *(s16 *)(buf + 0x18) = -0xC;
        *(s16 *)(buf + 0x1A) = 0;
        *(s16 *)(buf + 0x14) = t1;
        t2 = *(s32 *)((u8 *)a0 + 0xE0);
        *(s32 *)(buf + 0x30) = 0x50000000;
        *(u8 *)(buf + 0x22) = 0x80;
        *(u8 *)(buf + 0x21) = 0x80;
        *(u8 *)(buf + 0x20) = 0x80;
        *(u8 *)(buf + 0x26) = 0x80;
        *(u8 *)(buf + 0x25) = 0x80;
        *(u8 *)(buf + 0x24) = 0x80;
        *(u8 *)(buf + 0x2A) = 0x30;
        *(u8 *)(buf + 0x29) = 0x30;
        *(u8 *)(buf + 0x28) = 0x30;
        *(u8 *)(buf + 0x2E) = 0x30;
        *(u8 *)(buf + 0x2D) = 0x30;
        *(u8 *)(buf + 0x2C) = 0x30;
        *(s16 *)(buf + 0x1C) = t2;
    }

    func_80017758(buf, (u8 *)(*(s32 *)((u8 *)a0 + 0x20)) + 0x34);
}


#include "common.h"

/* TU-canonical declarations (law 2) — verbatim from
 * src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c (L2761/2988/etc for func_8012C218,
 * L1752 for func_80017758). */
extern void func_8012C218(void *a0);
extern s32 func_80017758(void *a0, void *a1);

/* Same-TU spelling already used at L4773 for this exact symbol (block-scoped
 * extern, address-of use — matches this function's need exactly). */


/* Isomorphic twin: ov_SC06_032:func_80184B08 (skeleton similarity 1.0, byte-
 * identical instruction stream). Copied verbatim with only the symbol/function
 * name unchanged (all callee/global symbols are shared across overlays). */
void func_80189D64(void *a0)
{
    extern Blk20_8018AF88 D_800AE620;
    s32 c;

    if (*(u16 *)((u8 *)a0 + 0x34) == 0) {
        *(u16 *)((u8 *)a0 + 0xCC) = *(u16 *)(*(s32 *)((u8 *)a0 + 0x64) + 0xCC);
        *(u16 *)((u8 *)a0 + 0xCE) = *(u16 *)(*(s32 *)((u8 *)a0 + 0x64) + 0xCE);
        *(u16 *)((u8 *)a0 + 0xD0) = *(u16 *)(*(s32 *)((u8 *)a0 + 0x64) + 0xD0);
        *(u16 *)((u8 *)a0 + 0xD4) = *(u16 *)(*(s32 *)((u8 *)a0 + 0x64) + 0xD4);
        *(u16 *)((u8 *)a0 + 0xD6) = *(u16 *)(*(s32 *)((u8 *)a0 + 0x64) + 0xD6);
        *(u16 *)((u8 *)a0 + 0xD8) = *(u16 *)(*(s32 *)((u8 *)a0 + 0x64) + 0xD8);
        *(u16 *)((u8 *)a0 + 0x34) += 1;
    }

    *(s32 *)((u8 *)a0 + 0xFC) = 0x50000000;

    c = *(s32 *)((u8 *)a0 + 0x1C);
    {
        u8 v = (u8)(c * 30);

        *(u8 *)((u8 *)a0 + 0xEC) =
        *(u8 *)((u8 *)a0 + 0xED) =
        *(u8 *)((u8 *)a0 + 0xEE) =
        *(u8 *)((u8 *)a0 + 0xF0) =
        *(u8 *)((u8 *)a0 + 0xF1) =
        *(u8 *)((u8 *)a0 + 0xF2) =
        *(u8 *)((u8 *)a0 + 0xF4) =
        *(u8 *)((u8 *)a0 + 0xF5) =
        *(u8 *)((u8 *)a0 + 0xF6) =
        *(u8 *)((u8 *)a0 + 0xF8) =
        *(u8 *)((u8 *)a0 + 0xF9) =
        *(u8 *)((u8 *)a0 + 0xFA) = v;
    }

    func_80017758((u8 *)a0 + 0xCC, &D_800AE620);

    {
        s32 d = *(s32 *)((u8 *)a0 + 0x1C) - 1;

        *(s32 *)((u8 *)a0 + 0x1C) = d;
        if (d == 0) {
            func_8012C218(a0);
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC", func_80189E60);


extern void (*D_801B55AC[])(void);

void func_80189FCC(void *a0) {
    D_801B55AC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018A008(s32 param_1) {
    s32 t;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_800D387C;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x9c;

    t = *(s32 *)(param_1 + 0x20);
    *(u16 *)(t + 0x1a) = 0x2000;
    *(u16 *)(t + 0x18) = 0x2000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x24) = 0xff;
    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x25) = 0;
    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x26) = 0;

    func_80128EA8(*(s32 *)(param_1 + 0x20), param_1 + 0x24, (s32)&D_800D3888);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


#include "common.h"

extern void func_8012931C(s32 a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(s32 a0);

void func_8018A0B8(s32 param_1) {
    s32 q;
    u8 a;
    u8 b;
    u16 h;

    q = *(s32 *)(param_1 + 0x20);

    a = *(u8 *)(q + 0x24) - 0x20;
    *(u8 *)(q + 0x24) = a;
    if (a < 0x80) {
        *(u8 *)(q + 0x24) = 0x80;
    }

    b = *(u8 *)(q + 0x25) + 0x20;
    *(u8 *)(q + 0x25) = b;
    if (b > 0x80) {
        *(u8 *)(q + 0x25) = 0x80;
    }

    h = *(u16 *)(q + 0x1A) + 0x400;
    *(u8 *)(q + 0x26) = *(u8 *)(q + 0x25);
    *(u16 *)(q + 0x1A) = h;
    *(u16 *)(q + 0x18) = h;

    func_8012931C(param_1);

    if (func_80128ED8((void *)q, (void *)(param_1 + 0x24)) != 0) {
        func_801292C8(param_1);
    }
}


void func_8018A170(s32 a0)
{
    extern void func_8012B23C(void *a0);
    extern void func_8012CBCC(s32 a0);
    extern u8 *func_8012913C(s32 a0);
    extern void func_8012C218(void *a0);
    s32 s0 = a0;
    s32 ret;
    u16 val;

    if (*(u16 *)(s0 + 2) == 0) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        func_8012B23C((void *)s0);
        *(s32 *)(s0 + 0x1C) = 1;
        return;
    }

    *(s32 *)(s0 + 0xDC) = *(s32 *)(s0 + 0x14);
    ret = ((s32 (*)(s32))func_8012CBCC)(s0);
    if (ret != 0 && (ret & 0x6000) != 0) {
        s32 cnt = *(s32 *)(s0 + 0x1C) - 1;
        *(s32 *)(s0 + 0x1C) = cnt;
        if (cnt == 0) {
            goto L8018A270;
        }
        *(s32 *)(s0 + 0x14) = -*(s32 *)(s0 + 0xDC) >> 2;
    }

    val = *(u16 *)(s0 + 0xFC) + 1;
    *(u16 *)(s0 + 0xFC) = val;
    if ((val & 1) != 0) {
        s32 np = (s32)func_8012913C(0x23);
        if (np != 0) {
            *(u16 *)(np + 6) = *(u16 *)(s0 + 6);
            *(u16 *)(np + 0xA) = *(u16 *)(s0 + 0xA);
            {
                u16 t = *(u16 *)(s0 + 0xE);
                *(u32 *)(np + 0x18) = 0;
                *(u32 *)(np + 0x14) = 0;
                *(u32 *)(np + 0x10) = 0;
                *(u16 *)(np + 0x34) = 0x3000;
                *(u16 *)(np + 0xE) = t;
            }
        }
    }

    if (*(s16 *)(s0 + 0xA) < 0x20) {
        return;
    }

L8018A270:
    func_8012C218((void *)s0);
}


typedef struct { s32 a; s32 b[4]; } OtBlk_8018A974_8018EB08_8018A28C;   /* == engine_types.h OtBlk (0x14) */

/* func_8018A28C — ov_SC06_032 / ov_SC06_032_jr_80182890, 122 ins.
 *
 * State entry dispatcher: switch on (flags@0x70 & 3), where cases {0,2} take the
 * "spawn child object" arm and cases {1,3} take the "allocate display object" arm;
 * both then fall into a shared tail that primes the display object at +0x20.
 *
 * The 4-way compare tree (beq 1 / slti 2 / beqz 0 / beq 2 / beq 3 / j default) is
 * gcc-2.7.2's balanced case tree for the four labels 0..3 with two shared bodies.
 */


extern int  func_8012C354();
extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012C1B8(void);
extern void func_8012CAE4();
extern void func_8001C214();
extern s32  func_8012AD50(void *arg0);
extern void func_8018C310(void);
extern void func_8018AB00(void);
extern void func_8018A474(void *arg0);

void func_8018A28C(s32 param_1) {

    extern u8 D_801CD3B0[];
    extern u8 D_801CD3C0[];
    extern u8 D_801CD3D8[];
    extern u8 D_801D1094[];
    s32 obj;
    s32 g;

    switch (*(u16 *)(param_1 + 0x70) & 3) {
    case 0:
    case 2:
        if (((s32 (*)(s32, u8 *))func_8012C354)(param_1, D_801CD3D8) == 0) {
            return;
        }
        *(s32 *)(param_1 + 0xCC) =
            func_8012C658(0x2E4, (*(u16 *)(param_1 + 0x70) & 2) | 1, param_1);
        *(u16 *)(param_1 + 0x104) = *(u16 *)(param_1 + 0x70) & 0x102;
        *(u16 *)(param_1 + 0x70) = *(u16 *)(param_1 + 0x70) & 1;
        if (*(u16 *)(param_1 + 0x104) & 0x100) {
            func_8018C310();
            func_8018AB00();
        }
        *(u8 *)(param_1 + 0xC0) = 1;
        *(u8 **)(param_1 + 0xBC) = D_801CD3C0;
        *(s32 *)(param_1 + 0xB4) = 0;
        *(u8 *)(param_1 + 0xC1) = 0;
        *(s16 *)(param_1 + 0xAE) = 0x6918;
        *(u32 *)(param_1 + 0xC4) |= 2;
        break;

    case 1:
    case 3:
        obj = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(param_1 + 0x20) = obj;
        if (obj == 0) {
            ((void (*)(s32))func_8012CAE4)(param_1);
            return;
        }
        ((void (*)(s32, u8 *))func_8001C214)(obj, D_801D1094);
        *(u16 *)(param_1 + 0x104) = *(u16 *)(param_1 + 0x70) & 2;
        *(u16 *)(param_1 + 0x70) = *(u16 *)(param_1 + 0x70) & 1;
        *(u16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0xA0;
        break;
    }

    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x10;
    /* one cached base for the three 0xE00 stores: the target loads 0x20($s0)
     * only once here, so the source must hold it in a pseudo (any indirect
     * store invalidates the CSE of the load in gcc-2.7.2). */
    g = *(s32 *)(param_1 + 0x20);
    *(s16 *)(g + 0x1C) = 0xE00;
    *(s16 *)(g + 0x1A) = 0xE00;
    *(s16 *)(g + 0x18) = 0xE00;
    *(u8 *)(param_1 + 0x75) = 0;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x80;
    *(u8 **)(*(s32 *)(param_1 + 0x20) + 0x80) = D_801CD3B0;
    if (*(s16 *)(param_1 + 0x70) != 0 && *(s16 *)(param_1 + 0x104) != 0) {
        func_8018A474((void *)param_1);
    } else {
        func_8012AD50((void *)param_1);
    }
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018A474(void *arg0) {
        *(s16 *)((char *)arg0 + 0x108) = 0;
        ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 2);
    }


extern s32 func_8012BEE8(s32 a0);

void func_8018A498(s32 param_1) {
    extern s32 D_801CF2BC;
    extern void func_8018A5D8();
    extern void func_8018AC58();
    extern void func_8018ACD4();
    extern void func_8001C924(s32 a0, void *a1);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
    s32 st;

    st = *(u16 *)(param_1 + 0x34);
    if (st != 1) {
        if (st < 2 && st == 0) {
            if (func_8012BEE8(param_1) != 0) {
                func_8001C924(*(s32 *)(param_1 + 0x20), &D_801CF2BC);
                if (*(s32 *)(param_1 + 0xCC) != 0) {
                    func_8018A5D8(*(s32 *)(param_1 + 0xCC));
                }
                func_8012C658(0x304, 0, param_1);
                func_8012C658(0x304, 1, param_1);
                func_8012C658(0x304, 2, param_1);
                func_8012C658(0x304, 3, param_1);
                func_8012C658(0x304, 4, param_1);
                func_8012C658(0x304, 5, param_1);
                func_8018ACD4(param_1);
                *(s32 *)(param_1 + 0x1c) = 0x40;
                *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
                func_8002D4C8(0x9BA, 0);
            }
            func_8018AC58(param_1);
        }
    } else {
        func_8018AC58(param_1);
        if (func_8012BEE8(param_1) != 0) {
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        }
    }
}


extern void func_8012B23C(void *);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_8018A5D8(s32 param_1)
{
    func_8012B23C((void *)param_1);
    *(s32 *)(param_1 + 0x14) = 0xFFD80000;
    *(s32 *)(param_1 + 0x1C) = 0x10;
    func_8012AD44((s32 *)param_1, 4);
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC", func_8018A61C);

extern s32 D_801CD3B8;

void func_8018A688(void *arg) {
    u8 *p = (u8 *)arg;
    s32 q = *(s32 *)(p + 0x78);
    s32 cc = *(s32 *)(p + 0xCC);
    f64 frame_pad;
    s32 dec;
    s32 t;
    s32 i;
    s32 n;

    __asm__ volatile("" : : "m"(frame_pad));
    if (q != 0) {
        dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
        if (dec < 1) {
            dec = 1;
        }
    }
    if (*(s16 *)(p + 0x76) != 0) {
        func_8016AA50((s32)p, dec);
        t = *(u16 *)(p + 0x76) - dec;
        *(u16 *)(p + 0x76) = t;
        if ((s16)t < 0) {
            *(u16 *)(p + 0x76) = 0;
        }
        i = 0;
        *(u16 *)(p + 0x10A) = rand() & 0x3F0;
        n = (rand() & 3) + 1;
        if (n != 0) {
            do {
                func_8012C658(0x304, i + 0x10, (s32)p);
                i++;
            } while (i < n);
        }
    }
    *(u8 *)(p + 0xC1) = 1;
    *(u16 *)(p + 0x5C) &= 0xFFFE;
    *(u32 *)(*(s32 *)(p + 0x20) + 0x80) = (u32)&D_801CD3B8;
    if (cc != 0) {
        *(u32 *)(*(s32 *)(cc + 0x20) + 0x80) = (u32)&D_801CD3B8;
    }
    *(u16 *)(p + 0xFE) = 8;
    if (*(s16 *)(p + 0x76) == 0) {
        *(u16 *)(p + 0x5C) = 0x800;
    }
    func_8002D4C8(0xAAC, 0);
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_8018A7C8(void *a0)
{
    extern u8 D_801CD3B0[];
    s32 a1;

    a1 = *(s32 *)((s32)a0 + 0xCC);
    if (a1 != 0) {
        u16 v = *(u16 *)((s32)a0 + 0xFE) & 1;
        *(u16 *)(a1 + 0x54) = v;
        *(u16 *)(a1 + 0x50) = v;
        *(u16 *)((s32)a0 + 0x54) = v;
        *(u16 *)((s32)a0 + 0x50) = v;
    }
    if (*(s16 *)((s32)a0 + 0xFE) != 0) {
        *(s16 *)((s32)a0 + 0xFE) = *(s16 *)((s32)a0 + 0xFE) - 1;
    } else {
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(u16 *)((s32)a0 + 0x5E) = 0;
        *(u32 *)(*(s32 *)((s32)a0 + 0x20) + 0x80) = (u32)D_801CD3B0;
        if (a1 != 0) {
            *(u32 *)(*(s32 *)(a1 + 0x20) + 0x80) = (u32)D_801CD3B0;
        }
        if (*(s16 *)((s32)a0 + 0x76) == 0) {
            *(s32 *)((s32)a0 + 0x1C) = 4;
            func_8012AD44((s32 *)a0, 3);
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC", func_8018A86C);

/* func_8018A974 — allocates a semi-trans LineF2 GPU packet, projects two
 * world-space points via RotTransPers, and (if both are on-screen with
 * non-negative depth-clip flags) links the packet into the current
 * double-buffer's OT at the first point's depth, then notifies via
 * func_80016638.
 *
 * STEP 0 sibling search (§160g) — three already-MATCHED exemplars supplied
 * the whole shape, none needed independent discovery:
 *
 *   1. src/shared/engine_core.h DEFINE_func_8012D3B4() — identical prologue
 *      (temp_v0=func_80010A08(0x10); word4=arg2; func_8004914C/func_800491AC
 *      (&D_800AF648); two RotTransPers calls with the exact
 *      `(d>0) && (flag>=0) && (RotTransPers(...)>0) && (flag>=0)` guard) but
 *      calls a real `SetLineF2()` (code 0x40, no semi-trans) and a real
 *      `AddPrim()` (single evaluation).  Our target's asm has NEITHER a
 *      `jal SetLineF2` NOR a `jal AddPrim` — both are fully inlined, which
 *      is the key structural difference this draft encodes (code 0x42 =
 *      semi-trans LineF2 needs hand-set fields; AddPrim needs the classic
 *      macro body since a *variable* depth offset appears nowhere in the
 *      real AddPrim()-calling siblings).
 *
 *   2. src/ov_SC03_119/ov_SC03_119_jr_8017FB84.c func_80185944 — byte-MATCH
 *      (177/177 ins).  Its header names this exact tail idiom: "link-ins
 *      the packet into the current double-buffer's OT (the PSY-Q `addPrim`
 *      macro pair) and calls func_80016638", with `func_80016638(&D_800A6518
 *      [*bidx*20], depth, 1)` as its literal call form (there depth=0x10
 *      constant, here depth=temp_v0_2).  Confirms the "3 lhu D_800B9A02,
 *      address cached / value reloaded" shape and the general addPrim(ot,p)
 *      == setaddr(p,getaddr(ot)); setaddr(ot,p) reading.
 *
 *   3. src/ov_SC03_119/ov_SC03_119_jr_8017FB84.c func_801860E8 (same TU,
 *      just above func_80185944) — its own header documents **Lever B**,
 *      byte-measured: "THE OT TABLE MUST BE AN ARRAY_REF (`D_800A651C[i].a`),
 *      NOT `*(s32*)((u8*)&D_800A651C + i*20)`. With the pointer-arith
 *      spelling gcc allocates a phantom 8-byte stack temp that is never
 *      referenced... The temp only appears when the SAME lookup expression
 *      occurs in two statements; the ARRAY_REF form kills it." This was the
 *      load-bearing fix for this draft too — confirmed empirically here via
 *      the `cpp|cc1 … | grep '.frame'` pipeline (§162i's own diagnostic
 *      method): pointer-arith form gave `vars=16` (0x38 frame, +8 over
 *      target's 0x30); switching every `D_800A651C` reference to
 *      `D_800A651C[idx].a` ARRAY_REF form (using the `OtBlk` shape from
 *      engine_types.h:525, local-suffixed here since match_one compiles
 *      standalone) dropped it straight to `vars=8` (0x30, exact). This
 *      generalizes §162i1's "only a BLKmode local reserves frame space" law
 *      to a second, distinct anonymous-temp source (a raw-pointer-arith
 *      symbol expression repeated in 2 statements) — worth a cookbook
 *      addendum since §162i1 as written only covers dead-local pads.
 *
 * REGISTER-ALLOCATION LEVERS (found empirically, byte-verified against this
 * function's own .frame/.s, not inherited from the exemplars above):
 *   - `bidx` pinned to $8 ($t0): natural (unpinned) allocation put the
 *     shared D_800B9A02-address pointer in $a3 instead, cascading a
 *     one-register shift through the whole mask/index register set.
 *   - `mask1` (0xFFFFFF) pinned to $7 ($a3); `tag0` (the packet's old tag
 *     word, read once before the first addPrim half) pinned to $4 ($a0) —
 *     both needed to reproduce the target's exact a2/a3/t0/t1 register
 *     picks for the addPrim RMW pair.  `mask2` (0xFF000000) and `depth4`
 *     (temp_v0_2*4) are explicitly NOT pinned — pinning them re-introduced a
 *     2-instruction schedule swap between the depth<<2 and the 0xFF000000
 *     `lui`; left as plain (named, for depth4) / literal (for mask2)
 *     locals, natural allocation lands them correctly.
 *   - `rgb` (arg2, the color word) pinned to $16 ($s0): unpinned, arg2 and
 *     the &D_800AF648 matrix address land in $s1/$s0 (swapped from target).
 *     `rgb`'s single SET made it a sched1 "birthing insn"
 *     (`birthing_insn_p`: `reg_n_sets==1`) — boosted to max priority in
 *     sched1's BACKWARD scan, which schedules a boosted insn late (cookbook
 *     "birthing-boost prologue-order" lever). A zero-byte non-volatile
 *     re-tie `__asm__("" : "=r"(rgb) : "0"(rgb));` placed immediately after
 *     `rgb = arg2;` gives it a 2nd SET (boost dead) with zero emitted code,
 *     and the 3-instruction prologue cluster (save $s0 / set $s0=arg2 / set
 *     $a0=0x10 for the alloc call) reorders to the target's exact sequence.
 *
 * INTEGRATION SURFACE (checked against destination TU
 * src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c):
 *   func_80010A08, func_8004914C, func_800491AC, RotTransPers, D_800AF648,
 *   D_800B9A02, D_800A6518 all match the TU's own existing extern spellings
 *   verbatim (grepped at TU lines 2448/2632-2633/4674 and the
 *   func_8018F694/func_8018F060 block). D_800A651C and func_80016638 have NO
 *   file-scope declaration anywhere in the TU (only ever appear inside other
 *   INCLUDE_ASM'd/unbanked functions) — declared here exactly as the
 *   func_801860E8/func_80185944 MATCHed precedent declares them: `OtBlk
 *   D_800A651C[]` (locally as `OtBlk_8018A974` — match_one compiles
 *   standalone without ../shared/engine_core.h; at bank time this collapses
 *   onto the TU's own already-visible `OtBlk` from engine_types.h:525,
 *   identical layout, a copy-edit not a fresh investigation) and
 *   `void func_80016638(void *a0, s32 a1, s32 a2)`.
 */

typedef struct { s32 a; s32 b[4]; } OtBlk_8018A974;   /* == engine_types.h OtBlk (0x14) */

void func_8018A974(s32 arg0, s32 arg1, s32 arg2)
{
    extern void *func_80010A08(s32);
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern s32 RotTransPers(s32, s32, s32 *, s32 *);
    extern u8 D_800AF648;
    extern OtBlk_8018A974 D_800A651C[];
    extern u8 D_800A6518[];
    extern short D_800B9A02;
    extern void func_80016638(void *a0, s32 a1, s32 a2);

    s32 sp10;
    s32 sp14;
    s32 temp_v0_2;
    void *temp_v0;
    s32 ot;
    s32 depth4;
    register u16 *bidx __asm__("$8");
    register u32 mask1 __asm__("$7");
    register s32 rgb __asm__("$16");
    register u32 tag0 __asm__("$4");

    rgb = arg2;
    __asm__("" : "=r"(rgb) : "0"(rgb));   /* zero-byte 2nd SET: kills the sched1 birthing boost */
    temp_v0 = func_80010A08(0x10);
    *(u8 *)((u8 *)temp_v0 + 3) = 3;
    *(s32 *)((u8 *)temp_v0 + 4) = rgb;
    *(u8 *)((u8 *)temp_v0 + 7) = 0x42;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    temp_v0_2 = RotTransPers(arg0, temp_v0 + 8, &sp10, &sp14);
    if ((temp_v0_2 > 0) && (sp14 >= 0) &&
        (RotTransPers(arg1, temp_v0 + 0xC, &sp10, &sp14) > 0) && (sp14 >= 0)) {
        /* addPrim(otp, p) == setaddr(p, getaddr(otp)), setaddr(otp, p) */
        mask1 = 0xFFFFFF;
        bidx = (u16 *)&D_800B9A02;
        depth4 = temp_v0_2 * 4;
        tag0 = *(u32 *)temp_v0;
        *(u32 *)temp_v0 = (tag0 & 0xFF000000) |
            (*(u32 *)(depth4 + D_800A651C[*bidx].a) & mask1);
        ot = D_800A651C[*bidx].a;
        *(u32 *)(depth4 + ot) =
            (*(u32 *)(depth4 + ot) & 0xFF000000) | ((u32)temp_v0 & mask1);
        func_80016638(&D_800A6518[*bidx * 20], temp_v0_2, 1);
    }
}


void func_8018AB00(void)
{
    typedef struct { u8 b0, b1, b2, b3; } Blk4;
    extern void func_800233CC(void *, unsigned short);
    extern Blk4 D_801D57B0;
    extern Blk4 D_801D57B4;
    extern Blk4 D_801D3B08;
    extern Blk4 D_801D3B0C;

    func_800233CC(&D_801D57B0, 0x80);

    D_801D57B0 = D_801D3B08;
    D_801D57B4 = D_801D3B0C;
}


typedef struct { u8 b0, b1, b2, b3; } Blk4;
extern Blk4 D_801D57B0;
extern Blk4 D_801D3B10;
extern Blk4 D_801D3B08;

void func_8018AB74(void) {
    if (D_801D57B0.b0 == 0xFF) {
        D_801D57B0 = D_801D3B10;
    } else {
        D_801D57B0 = D_801D3B08;
    }
}



void func_8018ABD4(s32 target, u16 *cur, s32 step)
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


extern void func_801437D8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u8 D_801CD460[];

void func_8018AC58(s32 arg0)
{
    s32 s0 = arg0;
    u16 sp10[4];

    sp10[0] = *(u16 *)(s0 + 6);
    sp10[1] = *(u16 *)(s0 + 0xA) - 0x60;
    sp10[2] = *(u16 *)(s0 + 0xE);
    sp10[3] = 0x3800;
    func_801437D8(s0 + 0x100, (s32)sp10, (s32)D_801CD460, 0);
    if ((*(u16 *)(s0 + 0x100) & 3) == 0) {
        func_8002D4C8(0xA9F, 0);
    }
}


extern s32 func_8012B8A4(s16 *a0);
extern s32 rand(void);
extern void func_8018AD74(s32 a0, s32 a1, s32 a2, s32 a3);

void func_8018ACD4(s32 param_1)
{
    s32 v;
    s32 t;
    s32 w;

    v = func_8012B8A4((s16 *)param_1);
    func_8018AD74(param_1, 0x32, 2, (s16)v);
    t = v - 0x200;
    func_8018AD74(param_1, 0x33, 3, (s16)(t - (rand() & 0x3F0)));
    w = v + 0x200;
    func_8018AD74(param_1, 0x33, 2, (s16)(w + (rand() & 0x3F0)));
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC", func_8018AD74);

void func_8018AE64(s32 param_1) {
    /* decls block-scoped ([T51] house idiom, cf. func_8018AF88); spellings are the
       TU-canonical ones from the atlas tu rows -- '?' lists stay unspecified. */
    extern s32 rand(void);
    extern void func_8012C1B8(void);
    extern void func_8012CAE4();
    extern void func_8001C214();
    extern void func_8012B23C(void *a0);
    extern void func_8018AF88(s32 a0);
    extern void func_8018B1D8(s32 a0);
    extern void func_8018B4D8(s32 a0);
    extern s32 D_801CD478[];
    extern s32 D_801CD47C[];
    s32 iVar2;
    s32 o2;
    u16 v;

    iVar2 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar2;
    if (iVar2 == 0) {
        func_8012CAE4(param_1);
    } else if (*(s16 *)(param_1 + 0x70) < 0x10) {
        func_8001C214(iVar2, D_801CD478[*(s16 *)(param_1 + 0x70)]);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) | 0x10;
        func_8012B23C(param_1);
        if (*(s16 *)(param_1 + 0x70) == 0) {
            func_8018AF88(param_1);
        } else {
            func_8018B1D8(param_1);
        }
    } else {
        func_8001C214(*(s32 *)(param_1 + 0x20), D_801CD47C[rand() & 3]);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) | 0x10;
        v = (rand() & 0x1F0) | 0x400;
        o2 = *(s32 *)(param_1 + 0x20);
        *(u16 *)(o2 + 0x1C) = v;
        *(u16 *)(o2 + 0x1A) = v;
        *(u16 *)(o2 + 0x18) = v;
        func_8012B23C(param_1);
        func_8018B4D8(param_1);
    }
}


// @class: struct
// @stuck: none — §136c SIBLING-FIRST. Near-twin (byte-identical template) = func_80186160 in
//   src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c (same jr_8017C24C base overlay TU, still
//   nonmatching); the two differ only in the per-overlay D_ table symbol (D_801CD498 here vs
//   D_801BEF4C there). RotMatrixY/func_8012AD44 canonical decl forms lifted from
//   src/ov_SC06_008/ov_SC06_008_jr_8016AB6C.c ("extern void RotMatrixY(s32 a0, void *a1);") and
//   src/shared/engine_core.h; the func_800484EC cast-through-fnptr call form is lifted from the
//   banked func_80188B00 in this same TU. The D_800AE620 8-word struct copy (3+3+2 lw/sw
//   grouping) is the established whole-struct `local = D_800AE620;` idiom already used for this
//   exact symbol elsewhere (Blk20, renamed here to avoid clashing with the real typedef pulled
//   in via engine_core.h when this splices into the TU). The address of the local matrix is
//   cached in a POINTER LOCAL (T6) because it's used again across the intervening RotMatrixY
//   call -- that's what forces it into a callee-saved reg ($s1) instead of being recomputed as
//   `addiu $a0,$sp,0x10` at each use site.


extern s32 D_801CD498;

extern s32 func_8012B8A4(s16 *a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32, s32, s32);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 rand(void);

void func_8018AF88(s32 param_1)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Blk20_8018AF88 D_800AE620;
    Blk20_8018AF88 local_30;
    Blk20_8018AF88 *m;
    s32 iVar1;
    s32 iVar2;

    local_30 = D_800AE620;
    iVar1 = func_8012B8A4((s16 *)param_1);
    m = &local_30;
    RotMatrixY(iVar1, m);
    ((void (*)(void *, void *, s32))func_800484EC)(m, &D_801CD498, param_1 + 0x10);
    *(s32 *)(param_1 + 0x14) = 0xFFDC0000;
    *(s32 *)(param_1 + 0xE0) = 0xFFDC0000;
    *(s32 *)(param_1 + 0x1C) = 0x10;
    iVar2 = rand();
    *(u16 *)(param_1 + 0x106) = iVar2 & 0x70;
    iVar2 = rand();
    *(u16 *)(param_1 + 0x108) = iVar2 & 0x70;
    func_8012AD44((s32 *)param_1, 1);
}


#include "common.h"

/* func_8018B060 -- ov_SC06_018; banked twin ov_SC06_032:func_80186238.
 * Keys:
 * (1) func_8012CC40 is fleet-canonical `void`; its $v0 is used, so both call
 *     sites go through the §17a-1 cast instead of redeclaring it.
 * (2) Case 0's if-body reads *(u16*)(p+0x34)+1 into a temp FIRST (that is what
 *     puts `lhu 0x34` ahead of `lw 0xE0` in the schedule).
 * (3) s32 pad[1] forces the 0x20 frame (same trick as func_80187AEC key (2)).
 */

extern void func_8012CC40(s32 arg0, s32 arg1);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8018B698(s32 a0);
extern s32  D_801CD490;

void func_8018B060(s32 param_1)
{
    s32 iVar;
    s32 pad[1];

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        iVar = ((s32 (*)(s32, s32))func_8012CC40)(param_1, (s32)&D_801CD490);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + *(u16 *)(param_1 + 0x106);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + *(u16 *)(param_1 + 0x108);
        if (iVar != 0) {
            u16 ns = *(u16 *)(param_1 + 0x34) + 1;
            *(s32 *)(param_1 + 0x14) = *(s32 *)(param_1 + 0xE0) >> 1;
            *(s32 *)(param_1 + 0x18) = 0;
            *(s32 *)(param_1 + 0x10) = 0;
            *(u16 *)(param_1 + 0x34) = ns;
        }
        break;
    case 1:
        iVar = ((s32 (*)(s32, s32))func_8012CC40)(param_1, (s32)&D_801CD490);
        func_8018B698(param_1);
        if (iVar != 0) {
            *(s32 *)(param_1 + 0x1C) = 0x10;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        }
        break;
    case 2:
        func_8018B698(param_1);
        if (func_8012BEE8(param_1) != 0) {
            func_8012C218((void *)param_1);
        } else if (*(s32 *)(param_1 + 0x1C) & 1) {
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x80000000;
        } else {
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
        }
        break;
    }
}


typedef struct { s32 a; s32 b[4]; } OtBlk_8018A974_8018EB08_8018B1D8;   /* == engine_types.h OtBlk (0x14) */

/* Local standins for the shared types (src/shared/engine_types.h) that the real TU pulls in via
 * "../shared/engine_core.h" -- match_one's -Iinclude can't reach src/shared/, so these are typed
 * identically for the standalone compile only; the real TU already has both. */



/* STEP 0 magic-literal grep: aD800AE620_8018B1D8 / D_801CD40C / ApplyMatrixSV / func_8012AD44 turned up the
 * banked sibling func_80186160 (same TU) which establishes: the whole-struct
 * `local = aD800AE620_8018B1D8;` idiom (typed Blk20_8018AF88_80186160, from src/shared/engine_types.h), the
 * address of that local cached into a POINTER LOCAL (forced into $s1 because it's live across the
 * RotMatrixY call and reused as ApplyMatrixSV's a0), and the `func_8012AD44((s32 *)param_1, N)`
 * call-through form. D_801CD40C here is a per-overlay array of SVECTOR (indexed *8 = sizeof(SVECTOR)),
 * unrelated to the scalar u8 D_801CD40C seen in ov_SC03_104 (different overlay, same address).
 */

extern void RotMatrixY(s32 a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 rand(void);

void func_8018B1D8(s32 param_1)
{

    extern Blk20_8018AF88_80186160 aD800AE620_8018B1D8 __asm__("D_800AE620");
    extern SVECTOR D_801CD40C[];
    Blk20_8018AF88_80186160 local_38;
    Blk20_8018AF88_80186160 *m;
    SVECTOR out;
    s32 rotY;
    s32 t;
    s16 v1;

    local_38 = aD800AE620_8018B1D8;
    rotY = rand() & 0x1F0;
    m = &local_38;
    RotMatrixY(rotY, m);
    ApplyMatrixSV(m, &D_801CD40C[*(s16 *)(param_1 + 0x70)], &out);

    *(u16 *)(param_1 + 6) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 6) + (u16)out.vx;
    *(u16 *)(param_1 + 0xA) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xA) + (u16)out.vy;
    *(u16 *)(param_1 + 0xE) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xE) + (u16)out.vz;

    *(s32 *)(param_1 + 0x10) = (s32)out.vx << 12;
    t = -(((rand() & 0x3F) << 12) + 0x200000);
    *(s32 *)(param_1 + 0x14) = t;
    *(s32 *)(param_1 + 0xE0) = t;
    *(s32 *)(param_1 + 0x18) = (s32)out.vz << 12;

    *(u16 *)(param_1 + 0x106) = rand() & 0xF0;
    *(u16 *)(param_1 + 0x108) = rand() & 0xF0;
    v1 = *(s16 *)(param_1 + 0x70);
    *(u16 *)(param_1 + 0xFE) = v1;

    func_8012AD44((s32 *)param_1, 2);
}



extern void func_8012CC40(s32 arg0, s32 arg1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32  func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8018B714(s32 a0);

void func_8018B330(s32 param_1)
{

    extern s32 D_801CD4A8;
    s32 iVar;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        iVar = ((s32 (*)(s32, s32))func_8012CC40)(param_1, (s32)&D_801CD4A8);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + *(u16 *)(param_1 + 0x106);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + *(u16 *)(param_1 + 0x108);
        if (iVar != 0) {
            u16 ns = *(u16 *)(param_1 + 0x34) + 1;
            *(s32 *)(param_1 + 0x14) = *(s32 *)(param_1 + 0xE0) >> 1;
            *(s32 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x10) >> 1;
            *(s32 *)(param_1 + 0x18) = *(s32 *)(param_1 + 0x18) >> 1;
            *(u16 *)(param_1 + 0x34) = ns;
        }
        func_8018B714(param_1);
        break;
    case 1:
        iVar = ((s32 (*)(s32, s32))func_8012CC40)(param_1, (s32)&D_801CD4A8);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + *(u16 *)(param_1 + 0x106);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + *(u16 *)(param_1 + 0x108);
        if (iVar != 0) {
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            *(s32 *)(param_1 + 0x1C) = 0x10;
        }
        func_8018B714(param_1);
        break;
    case 2:
        if (func_8012BEE8(param_1) != 0) {
            func_8012C218((void *)param_1);
        } else if (*(s32 *)(param_1 + 0x1C) & 1) {
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x80000000;
        } else {
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
        }
        break;
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC", func_8018B4D8);


extern void (*D_801CD4B0[])(void);

void func_8018B65C(void *a0) {
    D_801CD4B0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC", func_8018B698);

void func_8018B714(s32 param_1)
{
    s32 result;
    u16 counter;

    counter = *(u16 *)(param_1 + 0xFE) + 1;
    *(u16 *)(param_1 + 0xFE) = counter;
    if ((counter & 7) == 0) {
        result = func_80132EF4(param_1, 0x22);
        if (result != 0) {
            *(u32 *)(result + 0x14) = 0xFFF80000;
            *(u16 *)(result + 0x34) = 0x4001;
            *(u16 *)(*(s32 *)(result + 0x20) + 0x2C) = 0xC010;
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC", func_8018B774);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC", func_8018B8B0);


extern Blk4 D_801D57B0;

void func_8018B8F8(s32 param_1)
{
    extern s32 func_8012C194(void);
    extern void func_8001CD9C(int a0, void *a1);
    extern void func_8012AD44(s32 *a0, s16 a1);
    s32 s0;
    s32 k;
    u16 t;

    s0 = func_8012C194();
    if (s0 != 0) {
        *(s32 *)(param_1 + 0xCC) = s0;
        func_8001CD9C(s0, &D_801D57B0);
        *(u16 *)((s32)s0 + 8) = *(u16 *)(param_1 + 6);
        k = 0x50000000;
        *(u16 *)((s32)s0 + 0xA) = *(u16 *)(param_1 + 0xA);
        t = *(u16 *)(param_1 + 0xE);
        *(s32 *)((s32)s0 + 4) |= k;
        *(u16 *)((s32)s0 + 0x1A) = 0x80;
        *(u16 *)((s32)s0 + 0x18) = 0x80;
        *(u16 *)((s32)s0 + 0x2C) = 0xC006;
        *(u16 *)((s32)s0 + 0xC) = t;
    }
    *(s32 *)(param_1 + 0x1C) = 8;
    func_8012AD44((s32 *)param_1, 2);
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018B998(void *a0) {
        func_8002D4C8(0xAE5, 0);
        ((void (*)(void *, int))func_8012AD44)(a0, 0x3);
    }


extern u16 D_80126B96;
extern s16 D_80126B98;

void func_8018B9D4(s32 param_1)
{
    struct { u16 a; u16 b; s16 c; u16 d; } t1;
    struct { u16 a; u16 b; s16 c; u16 d; } t2;
    s32 r1, r2, r3, r4;
    s32 pad[2];
    s32 var_ea;
    s32 var_fe;
    s32 var_a0;
    s32 var_v0;
    register s32 zr __asm__("$0");

    func_8018BCC4((void *)param_1, 0, (u16 *)(param_1 + 0xE8), 0x81818);
    func_8018BCC4((void *)param_1, 1, (u16 *)(param_1 + 0xE8), 0x204040);
    t1.b = 0;
    t1.a = 0;
    t1.c = -*(u16 *)(param_1 + 0xE8);
    t2.b = 0;
    t2.a = 0;
    t2.c = -*(u16 *)(param_1 + 0xEA);
    (void)r1; (void)r2; (void)r3; (void)r4; (void)pad;
    if (func_8012DEB8(param_1, &t1, &t2) != 0) {
        D_80126B96 = 0x4018;
        D_80126B98 = 0x96;
    }
    var_ea = *(s16 *)(param_1 + 0xEA);
    var_fe = *(s16 *)(param_1 + 0xFE);
    var_a0 = var_ea + zr;
    if (var_ea < var_fe) {
        var_v0 = var_a0 + 0x40;
        *(s16 *)(param_1 + 0xEA) = var_v0;
        if ((var_v0 << 16) >> 16 >= *(s16 *)(param_1 + 0xFE)) {
            *(s16 *)(param_1 + 0xEA) = *(s16 *)(param_1 + 0xFE);
            func_8018BC40(param_1);
        }
    } else {
        var_v0 = *(u16 *)(param_1 + 0xE8) + 0x40;
        *(u16 *)(param_1 + 0xE8) = var_v0;
        if ((var_v0 << 16) >> 16 < *(s16 *)(param_1 + 0xFE)) {
            return;
        }
        if (*(s32 *)(param_1 + 0xCC) != 0) {
            func_80016714((void *)*(s32 *)(param_1 + 0xCC), 0x38);
        }
        *(s32 *)(*(s32 *)(param_1 + 0x64) + 0xD0) = 0;
        func_8012C218((void *)param_1);
    }
}


extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);
extern void (*D_801CD4D0[])(void);

void func_8018BB18(void *a0) {
    D_801CD4D0[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        if ((*(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36) != *(s16 *)((s32)a0 + 0x100)) ||
            (*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) == 4)) {
            if (*(s32 *)((s32)a0 + 0xCC) != 0) {
                func_80016714((void *)(*(s32 *)((s32)a0 + 0xCC)), 0x38);
            }
            func_8012C218(a0);
        }
    }
}


void func_8018BBB8(s32 a0)
{
    short buf[4];
    s32 p;

    buf[0] = *(u16 *)(a0 + 0x6);
    buf[1] = *(u16 *)(a0 + 0xA);
    buf[2] = *(u16 *)(a0 + 0xE);
    buf[3] = 0xC;

    p = func_8018D364(buf, 0, 0x40C0C0);
    if (p != 0) {
        *(u16 *)(*(s32 *)(p + 0x20) + 0x2C) = 0xC006;
        *(s32 *)(*(s32 *)(p + 0x20) + 0x4) |= 0x50000000;
        *(s16 *)(*(s32 *)(p + 0x20) + 0x18) = 0xA00;
    }
}


void func_8018BC40(s32 param_1)
{
    s32 result;
    u16 val_e4;

    result = func_80132EF4(param_1, 0x23);
    if (result != 0) {
        *(u16 *)(result + 0x6) = *(u16 *)(param_1 + 0xE0);
        *(u16 *)(result + 0xA) = *(u16 *)(param_1 + 0xE2);
        val_e4 = *(u16 *)(param_1 + 0xE4);
        *(u16 *)(result + 0x34) = 0x3001;
        *(u16 *)(result + 0xE) = val_e4;
        *(u16 *)(*(s32 *)(result + 0x20) + 0x2C) = 0xC008;
        *(u32 *)(*(s32 *)(result + 0x20) + 0x4) |= 0x50000000;
    }
}


typedef struct { s32 a; s32 b[4]; } OtBlk_8018A974_8018EB08_8018BCC4;   /* == engine_types.h OtBlk (0x14) */

/* func_8018BCC4 -- MATCH (185 ins, relocation-masked).
 *
 * Three load-bearing spellings, all verified by byte-diff:
 *
 *  (a) `pad_lo[4]` -- the target's var area starts 0x20 BELOW `sv`. Without a
 *      32-byte leading local the frame is 0x98 instead of 0xB8 and every
 *      sp-relative offset is short by 0x20 (134/185 mismatched). gcc-2.7.2
 *      still reserves the slot for an unreferenced aggregate, so any 32-byte
 *      aggregate declared first reproduces the layout.
 *
 *  (b) 4th param declared `u32 col` (a SCALAR whose address is taken), NOT a
 *      4-byte struct by value, together with the `arg0->mtx` COMPONENT_REF.
 *      Both spellings emit identical instructions, but they change gcc-2.7.2's
 *      alias heuristic in alias.c:true_dependence -- "a varying struct ref does
 *      not conflict with a fixed scalar ref". With a struct param the 0xC4 home
 *      slot MEM is MEM_IN_STRUCT_P, so `sw $a3,0xC4($sp)` stays dependent on
 *      `lw 0x20($s1)` and sched1 cannot sink it (3 mismatched at idx 11-13).
 *      Scalar-param home slot (not in-struct, non-varying) + struct-member load
 *      (in-struct, varying) => independent => the store sinks to idx 13. MATCH.
 *
 *  (c) SVec/CVec have alignment 2 / 1, which is what makes the plain struct
 *      assignments lower to lwl/lwr + swl/swr block moves (cookbook 48-C2).
 */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern void func_8018C090(void *a0);

typedef struct { s16 vx, vy, vz, pad; } SVec_80186E9C_8018BCC4;   /* 8 bytes, align 2 -> lwl/lwr block move */
typedef struct { u8 r, g, b, cd; } CVec_80186E9C_8018BCC4;        /* 4 bytes, align 1 */
typedef struct {
    /* 0x00 */ SVec_80186E9C_8018BCC4 v[4];
    /* 0x20 */ CVec_80186E9C_8018BCC4 col;
    /* 0x24 */ u32 code;
} Quad_80186E9C_8018BCC4;

typedef struct { u8 pad00[0x20]; /* 0x20 */ u8 *mtx; } Ent_80186E9C_8018BCC4;


void func_8018BCC4(Ent_80186E9C_8018BCC4 *arg0, s32 arg1, u16 *arg2, u32 col)
{

    extern SVec_80186E9C_8018BCC4 D_801CD4E0[];
    SVec_80186E9C_8018BCC4 pad_lo[4];   /* unused 32-byte leading local (frame filler) */
    SVec_80186E9C_8018BCC4 sv;
    SVec_80186E9C_8018BCC4 out[6];
    Quad_80186E9C_8018BCC4 q;
    long flag;
    SVec_80186E9C_8018BCC4 *p;
    s32 i;

    func_8004914C(arg0->mtx + 0x34);
    func_800491AC(arg0->mtx + 0x34);

    p = &D_801CD4E0[(arg1 & 1) * 3];

    for (i = 0; i < 3; i++) {
        sv.vx = p[i].vx;
        sv.vy = p[i].vy;
        sv.vz = -arg2[0];
        RotTransSV(&sv, &out[i], &flag);
    }
    for (i = 0; i < 3; i++) {
        sv.vx = p[i].vx;
        sv.vy = p[i].vy;
        sv.vz = -arg2[1];
        RotTransSV(&sv, &out[i + 3], &flag);
    }

    q.col = *(CVec_80186E9C_8018BCC4 *)&col;
    q.code = 0x50000000;

    q.v[0] = out[0]; q.v[1] = out[1]; q.v[2] = out[3]; q.v[3] = out[4];
    func_8018C090(&q);
    q.v[0] = out[1]; q.v[1] = out[2]; q.v[2] = out[4]; q.v[3] = out[5];
    func_8018C090(&q);
    q.v[0] = out[2]; q.v[1] = out[0]; q.v[2] = out[5]; q.v[3] = out[3];
    func_8018C090(&q);
}



extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80047948(s32 a0); /* rsin-like: angle (0..0xFFF) -> 1.12 fixed */
extern s32 func_8004787C(s32 a0); /* rcos-like: angle (0..0xFFF) -> 1.12 fixed */

/* The 4-byte destination is a PACKED PAIR of angles held entirely in ONE saved register
 * ($s4) across all three calls — that is what produces the target's
 *   andi $s4,$s4,0xFFFF   (read of the still-uninitialized local, hoisted into the prologue)
 *   ... or  $s4,$s4,ang<<16      -> t.hi = yaw
 *   ... and $s4,$s4,0xFFFF0000 / or $s4,$s4,ang&0xFFFF  -> t.lo = pitch
 * A `struct { s16 lo, hi; }` has align 2 -> BLKmode-ish handling: gcc spills it to the stack
 * and stores it with lwl/lwr + swl/swr (54 ins, 53 mismatched). Two 16-bit BITFIELDS in a
 * u32 container give the SImode, align-4 struct gcc keeps in a register. */

/* a0 = destination packed-angle word, a1 = "from" entity, a2 = "to" entity.
 * Both entities carry 16.16 fixed-point x/y/z at +0/+4/+8; the s16 reads at +2/+6/+0x4 are
 * the integer halves. Returns the destination pointer — the return value is REAL: without it
 * gcc stores with `sw $s4,0($s3)` (57 ins) instead of the target's
 *   addu $v0,$s3,$zero ; sw $s4,0($v0)   (the return-value copy that the store's base coalesces onto).
 * The flattened `dz` reuse at the end is also load-bearing: making the (dz*sin + dx*cos)>>12
 * temp its OWN variable gives it $a1 for the whole chain; reusing `dz` extends that allocno so
 * it lands in $s5 exactly as the target does (`sra $s5,$v0,12` / `negu $a1,$s5`), and it also
 * demotes dz's priority so the saved-reg order comes out $s3=out, $s4=t, $s5=dz. */
s32 func_8018BFA8(s32 out, s32 from, s32 to) {
    Ang2_8012B77C_8018BFA8 t;
    s32 dx, dy, dz;
    s32 ang;
    s32 r1, r2;

    dz = *(s16 *)(to + 0x4) - *(s16 *)(from + 0x4);
    dx = *(s16 *)(to + 0x0) - *(s16 *)(from + 0x0);
    dy = *(s16 *)(to + 0x2) - *(s16 *)(from + 0x2);

    ang = (ratan2(-dz, dx) - 0x400) & 0xFFF;
    t.hi = ang;

    r1 = func_80047948(ang);
    r2 = func_8004787C(ang);
    dz = (dz * r1 + dx * r2) >> 12;
    t.lo = ratan2(dy, -dz);

    *(Ang2_8012B77C_8018BFA8 *)out = t;
    return out;
}


#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")

#define gte_stotz(r0) __asm__ volatile (         \
    "swc2 $7, 0( %0 )"                           \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

void func_8018C090(void *a0)
{
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern void func_80017254(void *);
    extern u8 D_800AF648;

    s32 flag1, flag2, otz;

    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);

    gte_ldv3(a0, (char *)a0 + 8, (char *)a0 + 0x10);
    gte_rtpt();
    gte_stflg(&flag1);
    gte_stsxy3(a0, (char *)a0 + 8, (char *)a0 + 0x10);

    gte_ldv0((char *)a0 + 0x18);
    gte_rtps();
    gte_stflg(&flag2);
    flag1 = flag1 | flag2;
    gte_stsxy((char *)a0 + 0x18);

    gte_avsz4();
    gte_stotz(&otz);

    *(s16 *)((char *)a0 + 4) = otz;
    if ((u32)otz < 0x1000) {
        func_80017254(a0);
    }
}


extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F038(int param_1, short *param_2, short *param_3);
extern u8 D_801CD4C8[];

struct Fr_8018C190 {
    s16 mtx[10];   /* sp+0x10, only its address is used (func_80049CAC out) */
    s32 pos[3];    /* sp+0x24 */
    s16 sv[4];     /* sp+0x30 (RotTransSV out) */
    s16 sv2[4];    /* sp+0x38 (unused, layout filler) */
    s16 buf40[4];  /* sp+0x40 (func_8012F038 out) */
    s16 rot[4];    /* sp+0x48 */
    s32 flg[4];    /* sp+0x50 (RotTransSV flag out) */
};

void func_8018C190(s32 param_1) {
    struct Fr_8018C190 fr;
    s32 dx, dy, dz;
    s32 ang;
    s32 r1, r2, r3;
    s32 t;

    func_8004914C((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
    RotTransSV(D_801CD4C8, fr.sv, fr.flg);

    dz = *(s16 *)(param_1 + 0xE4) - (s16)fr.sv[2];
    dx = *(s16 *)(param_1 + 0xE0) - (s16)fr.sv[0];
    dy = *(s16 *)(param_1 + 0xE2) - (s16)fr.sv[1];

    ang = (ratan2(-dz, dx) - 0x400) & 0xFFF;
    t &= 0xFFFF;
    t |= ang << 16;

    r1 = func_80047948(ang);
    r2 = func_8004787C(ang);
    dz = (dz * r1 + dx * r2) >> 12;
    r3 = ratan2(dy, -dz);
    t &= 0xFFFF0000;
    t |= r3 & 0xFFFF;
    fr.flg[2] = t;

    fr.rot[0] = t;
    fr.rot[1] = t >> 16;
    fr.rot[2] = 0;
    ((void (*)(void *, void *))func_80049CAC)(fr.rot, fr.mtx);

    fr.pos[0] = fr.sv[0];
    fr.pos[1] = fr.sv[1];
    fr.pos[2] = fr.sv[2];

    func_8004914C((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(param_1 + 0x20) + 0x34));
    func_8012F038(*(s32 *)(param_1 + 0x20) + 0x34, (short *)(param_1 + 0xE0), fr.buf40);

    *(s16 *)(param_1 + 0xFE) = -fr.buf40[2];
}




void func_8018C310(void)
{
    extern Blip_8018F694 D_801D55B0[];
    Blip_8018F694 *bp = D_801D55B0;
    s32 i = 0x1F;

    do {
        bp->tm = 0;
        bp++;
        i--;
    } while (i >= 0);
}


typedef struct { u8 d[4]; } __attribute__((packed, aligned(1))) B4_8018C334;
typedef struct { u8 d[8]; } __attribute__((packed, aligned(1))) B8_8018C334;

void func_8018C334(s32 param_1, s32 param_2)
{
    extern u8 D_801D55B0[];

    u8 *p;
    s32 i;
    s32 c;

    p = D_801D55B0;
    i = 0;
    do {
        i++;
        if (*(s16 *)(p + 0xE) == 0) {
            *(B8_8018C334 *)(p + 8) = *(B8_8018C334 *)(((u8 *)param_1) + 0);
            *(B4_8018C334 *)p = *(B4_8018C334 *)(((u8 *)&param_2) + 0);
            c = p[0] >> 3;
            p[4] = c;
            if (c == 0) {
                p[4] = 1;
            }
            c = p[1] >> 3;
            p[5] = c;
            if (c == 0) {
                p[5] = 1;
            }
            c = p[2] >> 3;
            p[6] = c;
            if (c == 0) {
                p[6] = 1;
            }
            break;
        }
        p += 0x10;
    } while (i < 0x20);
}


#include "common.h"

/* ---- types (TU-canonical: Blip_8018F694 / UVEC_8018F694 / PTag_8018F694 /
 * TPage_8018F694 ALL already live in src/shared/engine_types.h:724/1094/941/1073,
 * reached from the destination TU via "../shared/engine_core.h" — DROP this whole
 * typedef block when banking.) */





#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stszotz(r0) __asm__ volatile (       \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )


void func_8018C3F8(void)
{
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern void *func_80010A08(s32);
    extern void func_8018C7A8(UVEC_8018F694 *, UVEC_8018F694 *,
                              Blip_8018F694 *, PTag_8018F694 *);
    extern u8 D_800AF648;
    extern u8 D_800A6610[];
    extern short D_800B9A02;
    extern Blip_8018F694 D_801D55B0[];

    UVEC_8018F694 sxy;
    UVEC_8018F694 p0;
    UVEC_8018F694 p1;
    long flag;
    long otz;
    s32 i;
    PTag_8018F694 *ot;
    PTag_8018F694 *otp;
    Blip_8018F694 *bp;
    s32 t, c, d, z, x, n;

    ot = (PTag_8018F694 *)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    bp = D_801D55B0;

    for (i = 0; i < 32; i++, bp++) {
        t = bp->tm;
        __asm__ __volatile__ ("" : "=r" (t) : "0" (t));
        if (t != 0) {
            gte_ldv0(&bp->vx);
            gte_rtps();
            gte_stsxy((long *) &sxy);
            gte_stflg(&flag);
            gte_stszotz(&otz);
            if ((u16) (sxy.vx + 0x200) < 0x401 &&
                (u16) (sxy.vy + 0x180) < 0x301 &&
                (u32) (otz - 0x10) < 0x1000) {
                z = otz - 0x10;
                c = t >> 6;
                d = (t * 3) >> 8;
                otp = (PTag_8018F694 *) ((s32) ot + (z << 2));

                p0.vx = sxy.vx - c;
                p0.vy = sxy.vy - c;
                p1.vx = p0.vx + d;
                p1.vy = p0.vy;
                func_8018C7A8(&p0, &p1, bp, otp);

                p1.vx = p0.vx;
                p1.vy = p0.vy + d;
                func_8018C7A8(&p0, &p1, bp, otp);

                p0.vx = sxy.vx + c;
                p1.vx = p0.vx - d;
                p1.vy = p0.vy;
                func_8018C7A8(&p0, &p1, bp, otp);

                p1.vx = p0.vx;
                p1.vy = p0.vy + d;
                func_8018C7A8(&p0, &p1, bp, otp);

                p0.vy = sxy.vy + c;
                p1.vx = p0.vx - d;
                p1.vy = p0.vy;
                func_8018C7A8(&p0, &p1, bp, otp);

                p1.vx = p0.vx;
                p1.vy = p0.vy - d;
                func_8018C7A8(&p0, &p1, bp, otp);

                p0.vx = sxy.vx - c;
                p1.vx = p0.vx + d;
                p1.vy = p0.vy;
                func_8018C7A8(&p0, &p1, bp, otp);

                p1.vx = p0.vx;
                p1.vy = p0.vy - d;
                func_8018C7A8(&p0, &p1, bp, otp);

                {
                    TPage_8018F694 *tp = (TPage_8018F694 *) func_80010A08(8);
                    tp->len = 1;
                    tp->code0 = 0xE1000020;
                    tp->addr = otp->addr;
                    otp->addr = (u32) tp;
                }

                n = bp->r;
                x = n - bp->dr;
                n = x;
                if (x < 0) { n = 0; }
                bp->r = n;
                n = bp->g;
                x = n - bp->dg;
                n = x;
                if (x < 0) { n = 0; }
                bp->g = n;
                n = bp->b;
                x = n - bp->db;
                n = x;
                if (x < 0) { n = 0; }
                bp->b = n;
                x = n | (bp->r | bp->g);
                if ((u8) x == 0) {
                    bp->tm = 0;
                }
            }
        }
    }
}


void func_8018C7A8(u16 *param_1, u16 *param_2, u8 *param_3, u32 *param_4)
{
    u8 *p;
    register u32 tag __asm__("$5");
    register u32 mask1 __asm__("$4");
    register u32 mask2 __asm__("$6");
    p = func_80010A08(0x10);
    p[3] = 0x3;
    p[7] = 0x42;
    p[4] = param_3[0];
    p[5] = param_3[1];
    p[6] = param_3[2];
    *(u16 *)(p + 8) = param_1[0];
    *(u16 *)(p + 10) = param_1[1];
    *(u16 *)(p + 12) = param_2[0];
    *(u16 *)(p + 14) = param_2[1];
    tag = *(u32 *)p;
    mask1 = 0xFFFFFF;
    mask2 = 0xFF000000;
    *(u32 *)p = (tag & mask2) | (*param_4 & mask1);
    *param_4 = (*param_4 & mask2) | ((u32)p & mask1);
}


void func_8018C884(void) {
}

extern s32  func_8012B8A4(s16 *a0);
extern void func_8018ABD4(s32 target, u16 *cur, s32 step);
extern void func_8012B2CC(s32 a0);
extern s32  func_8018A86C(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern s32  func_8012C588(s32 a0, s32 a1);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

void func_8018C88C(s32 param_1)
{
    s32 ent;
    s32 state;
    s16 t;

    ent = param_1;
    state = *(u16 *)(ent + 0x34);
    switch (state) {
    case 0:
        t = func_8012B8A4((s16 *)ent);
        *(s16 *)(ent + 0x106) = t;
        func_8018ABD4(t, (u16 *)(*(s32 *)(ent + 0x20) + 0x12), 0x20);
        func_8012B2CC(ent);
        *(u16 *)(ent + 0xE0) = D_80126B5E;
        *(u16 *)(ent + 0xE2) = D_80126B62 - 0x38;
        *(u16 *)(ent + 0xE4) = D_80126B66;
        if (func_8018A86C(ent) != 0) {
            *(s32 *)(ent + 0xD0) = func_8012C588(0x30E, ent);
            (*(u16 *)(ent + 0x34))++;
        }
        break;
    case 1:
        if (*(s32 *)(ent + 0xD0) == 0) {
            *(s32 *)(ent + 0x1C) = 0x10;
            (*(u16 *)(ent + 0x34))++;
        }
        break;
    case 2:
        if (func_8012BEE8(ent) != 0) {
            *(u16 *)(ent + 0x108) = 0;
            *(u16 *)(ent + 0x34) = 0;
        }
        break;
    }
}


extern void func_8012AD80(s32 a0);
extern void func_801437D8(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern u8 D_801CD43C[];

void func_8018C9B0(s32 arg0)
{
    s32 s0 = arg0;
    u16 sp10[4];

    func_8012AD80(s0);
    sp10[0] = *(u16 *)(s0 + 6);
    sp10[1] = *(u16 *)(s0 + 0xA);
    sp10[2] = *(u16 *)(s0 + 0xE);
    sp10[3] = 0x3000;
    func_801437D8(s0 + 0x100, (s32)sp10, (s32)D_801CD43C, 0);
    if ((*(u16 *)(s0 + 0x100) & 3) == 0) {
        func_8002D4C8(0xA9F, 0);
    }
    if (func_8012BEE8(s0) != 0) {
        func_8012C218((void *)s0);
    }
}


void func_8018CA44(s32 param_1)
{
    if (func_8012BEE8(param_1) != 0) {
        func_8012C218((void *)param_1);
    } else {
        func_8012AD80(param_1);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + *(u16 *)(param_1 + 0x106);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) = *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + *(u16 *)(param_1 + 0x108);
    }
}


extern void func_8018C334(s32 a0, s32 a1);
extern void func_8018B8F8(s32 a0);

void func_8018CABC(s32 param_1)
{
    s16 t;

    func_8018C334(param_1 + 0xE0, 0x4040FF);
    t = *(s16 *)(param_1 + 0xE6);
    t = t - 0x100;
    *(s16 *)(param_1 + 0xE6) = t;
    if (t == 0) {
        func_8018B8F8(param_1);
    }
}


void func_8018CB14(s32 param_1)
{
    s32 var_a0;
    s16 var_v0;

    var_a0 = *(s32 *)(param_1 + 0xCC);
    if (var_a0 != 0) {
        var_v0 = *(s16 *)(var_a0 + 0x18);
        if (var_v0 < 0x500) {
            *(s16 *)(var_a0 + 0x18) = var_v0 + 0xC0;
            *(u16 *)(var_a0 + 0x1A) = *(u16 *)(var_a0 + 0x1A) + 0xC0;
        }
    }
    if (func_8012BEE8(param_1) != 0) {
        func_8018B998(param_1);
    }
}


extern void func_8012931C(s32 a0);
extern void func_801292C8(s32 a0);
extern void func_8018CC88(void *a0);
extern void func_8018CD04(void *a0);

void func_8018CB88(void *a0) {
    if (*(u16 *)((s32)a0 + 0x2) == 0) {
        func_8018CC88(a0);
        return;
    }

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(s32 *)((s32)a0 + 0x1C) -= 1;
        func_8012931C((s32)a0);

        if (*(s16 *)((s32)a0 + 0x32) == 0) {
            u16 t = *(u16 *)((s32)a0 + 0xA) + 0x1000;
            if (t >= 0x1001) {
                func_801292C8((s32)a0);
                return;
            }
        }
    } else {
        func_801292C8((s32)a0);
        return;
    }

    *(s32 *)((s32)a0 + 0x14) += *(s32 *)((s32)a0 + 0x34);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += *(u16 *)((s32)a0 + 0x30);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x8) = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0xA) = *(u16 *)((s32)a0 + 0xA);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0xC) = *(u16 *)((s32)a0 + 0xE);
    func_8018CD04((void *)*(s32 *)((s32)a0 + 0x20));
}




void func_8018CC88(void *a0) {
    s32 *s1;
    s32 *s0;
    u16 v0_const;
    s32 rand_val;
    u16 *val_ptr;

    s1 = (s32 *)a0;
    v0_const = 0x0B;
    __asm__("");
    s0 = *(s32 **)((u8 *)s1 + 0x20);

    
    *(u16 *)((u8 *)s0 + 0x2) = v0_const;

    
    *(s32 *)((u8 *)s0 + 0x4) |= 0x50000000;

    
    if (*(s16 *)((u8 *)s0 + 0x18) == 0) {
        *(s16 *)((u8 *)s0 + 0x18) = 0x600;
    }

    
    rand_val = rand();
    *(u16 *)((u8 *)s0 + 0x14) = (u16)(rand_val & 0xFF0);

    
    val_ptr = (u16 *)((u8 *)s1 + 0x2);
    *val_ptr = *val_ptr + 1;

    
    *(s16 *)((u8 *)s1 + 0x30) = 0x100;
}


#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stszotz(r0) __asm__ volatile (       \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )
#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )
#define gte_SetRotMatrix(r0) __asm__ volatile (  \
    "lw $12, 0( %0 );"                           \
    "lw $13, 4( %0 );"                           \
    "ctc2 $12, $0;"                              \
    "ctc2 $13, $1;"                              \
    "lw $12, 8( %0 );"                           \
    "lw $13, 12( %0 );"                          \
    "lw $14, 16( %0 );"                          \
    "ctc2 $12, $2;"                              \
    "ctc2 $13, $3;"                              \
    "ctc2 $14, $4"                               \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "$13", "$14" )
#define gte_SetTransMatrix(r0) __asm__ volatile ( \
    "lw $12, 20( %0 );"                          \
    "lw $13, 24( %0 );"                          \
    "ctc2 $12, $5;"                              \
    "lw $14, 28( %0 );"                          \
    "ctc2 $13, $6;"                              \
    "ctc2 $14, $7"                               \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "$13", "$14" )
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsz(r0) __asm__ volatile (          \
    "swc2 $19, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stszotz(r0) __asm__ volatile (       \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )
#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )
#define RD16(p) (((struct { u16 v; } *)(p))->v)
#define RW32(p) (((struct { u32 v; } *)(p))->v)

void func_8018CD04(void *a0)
{
    extern u8 D_800AF648;
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern void RotMatrixZ(s32 a0, void *a1);

    u8 stk[0x60];                        /* sp+0x10 .. sp+0x6F */
    u32 flags;
    u32 idx;
    u32 ot;
    u32 t2;
    u8 *pkt;
    u8 *p1;
    u8 *p2;
    u8 *pkb;
    s32 d;
    u32 *otp;
    register u32 tv __asm__("$3");       /* §137 pin — see header */
    register u32 tv2 __asm__("$4");      /* §137 pin — see header */

    u8 *rotm;

    flags = *(u32 *)((s32)a0 + 4);
    rotm = &D_800AF648;

    gte_SetRotMatrix(rotm);
    gte_SetTransMatrix(rotm);
    gte_ldv0((s32)a0 + 8);
    gte_rtps();
    gte_stsxy(stk);
    gte_stflg(stk + 0x48);
    gte_stsz(stk + 0x4c);
    gte_stszotz(stk + 0x50);

    if ((*(u32 *)(stk + 0x48) & 0xFFFFEFFF) == 0) {
        idx = *(s32 *)(stk + 0x50) + 1;
        ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
        {
            u16 flags2 = *(u16 *)((s32)a0 + 0x2c);
            if ((flags2 & 0xC000) != 0) {
                if ((flags2 & 0xC000) == 0xC000) {
                    idx = idx - (flags2 & 0xFFF);
                    if ((s32)idx < 0) idx = 0;
                } else {
                    idx = idx + (flags2 & 0xFFF);
                }
            }
        }

        if (idx < 0x1000) {
            d = (s32)&stk[0x08];

            *(u16 *)(stk + 0x08) = *(u16 *)((s32)a0 + 0x18);
            *(u16 *)(stk + 0x0a) = 0;
            *(u16 *)(stk + 0x0c) = 0;
            *(u16 *)(stk + 0x0e) = 0;
            *(u16 *)(stk + 0x10) = *(u16 *)((s32)a0 + 0x18);
            *(u16 *)(stk + 0x12) = 0;
            *(u16 *)(stk + 0x14) = 0;
            *(u16 *)(stk + 0x16) = 0;
            *(u16 *)(stk + 0x18) = 0x1000;
            *(u32 *)(stk + 0x24) = 0;
            *(u32 *)(stk + 0x20) = 0;
            *(u32 *)(stk + 0x1c) = 0;

            RotMatrixZ(*(s16 *)((s32)a0 + 0x14), (void *)d);
            gte_SetRotMatrix((void *)d);
            gte_SetTransMatrix((void *)d);

            *(u16 *)(stk + 0x28) = 0x20;
            *(u16 *)(stk + 0x2a) = 0;
            *(s16 *)(stk + 0x2c) = (s16)*(u32 *)(stk + 0x4c);
            gte_ldv0(stk + 0x28);
            gte_rtps();
            gte_stsxy(stk + 0x54);

            d = (u16)((s16)(RD16(stk + 0x54)) >> 3);
            d |= (s32)((s16)(RD16(stk + 0x56)) >> 3) << 16;

            pkt = D_800A5E60;
            p1 = pkt + 0x18;
            *(u8 *)(pkt + 0x3) = 5;
            *(u8 *)(pkt + 0x7) = 0x28;
            *(u8 *)(p1 + 0x3) = 5;
            t2 = flags & 0x40000000;
            *(u8 *)(p1 + 0x7) = 0x28;
            if (t2 != 0) {
                *(u8 *)(pkt + 0x7) = *(u8 *)(pkt + 0x7) | 2;
                *(u8 *)(p1 + 0x7) = *(u8 *)(p1 + 0x7) | 2;
            }
            *(u8 *)(pkt + 0x4) = *(u8 *)((s32)a0 + 0x24);
            *(u8 *)(pkt + 0x5) = *(u8 *)((s32)a0 + 0x25);
            *(u8 *)(pkt + 0x6) = *(u8 *)((s32)a0 + 0x26);
            *(u8 *)(p1 + 0x4) = *(u8 *)((s32)a0 + 0x24);
            *(u8 *)(p1 + 0x5) = *(u8 *)((s32)a0 + 0x25);
            *(u8 *)(p1 + 0x6) = *(u8 *)((s32)a0 + 0x26);

            *(s16 *)(pkt + 0x8) = RD16(stk) + RD16(stk + 0x54);
            *(s16 *)(pkt + 0xa) = RD16(stk + 0x02) + RD16(stk + 0x56);
            *(s16 *)(pkt + 0xc) = RD16(stk) - (d >> 16);
            *(s16 *)(pkt + 0xe) = RD16(stk + 0x02) + d;
            *(s16 *)(pkt + 0x10) = RD16(stk) + (d >> 16);
            *(s16 *)(pkt + 0x12) = RD16(stk + 0x02) - d;
            *(s16 *)(pkt + 0x14) = RD16(stk) - RD16(stk + 0x54);
            *(s16 *)(pkt + 0x16) = RD16(stk + 0x02) - RD16(stk + 0x56);
            *(s16 *)(p1 + 0x8) = RD16(stk) - RD16(stk + 0x56);
            *(s16 *)(p1 + 0xa) = RD16(stk + 0x02) + RD16(stk + 0x54);
            *(s16 *)(p1 + 0xc) = RD16(stk) - d;
            *(s16 *)(p1 + 0xe) = RD16(stk + 0x02) - (d >> 16);
            *(s16 *)(p1 + 0x10) = RD16(stk) + d;
            *(s16 *)(p1 + 0x12) = RD16(stk + 0x02) + (d >> 16);
            *(s16 *)(p1 + 0x14) = RD16(stk) + RD16(stk + 0x56);
            *(s16 *)(p1 + 0x16) = RD16(stk + 0x02) - RD16(stk + 0x54);

            /* addPrim(otp, pkt); addPrim(otp, p1); */
            otp = (u32 *)((idx << 2) + ot);
            tv = RW32(pkt);
            RW32(pkt) = (tv & 0xFF000000) | (RW32(otp) & 0xFFFFFF);
            RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
            tv = RW32(p1);
            RW32(p1) = (tv & 0xFF000000) | (RW32(otp) & 0xFFFFFF);

            pkb = D_800A5E60;
            p2 = pkb + 0x30;
            D_800A5E60 = p2;
            RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)p1 & 0xFFFFFF);

            if (t2 != 0) {
                D_800A5E60 = pkb + 0x38;
                *(u8 *)(p2 + 3) = 1;
                RW32(p2 + 4) = ((flags >> 23) & 0x60) | 0xE1000000;
                tv2 = RW32(p2);
                RW32(p2) = (tv2 & 0xFF000000) | (RW32(otp) & 0xFFFFFF);
                RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)p2 & 0xFFFFFF);
            }
        }
    }
}


// @class: loose-typing
// @stuck: none — MATCH (99 ins). short* for param_2/param_3: gcc emits lh where sign is live (<<1 for signed div), lhu where truncated to short (arith result / direct copy)

extern int rand(void);
extern int func_8018D364(short *pos, int a1, int a2);

void func_8018D1A4(unsigned short *param_1, short *param_2, short *param_3,
                   unsigned int param_4, int param_5)
{
    int r;
    int d;
    short buf[4];
    int p;

    if ((*param_1 & (short)((1 << param_4) - 1)) == 0) {
        r = rand();
        d = param_3[0] << 1;
        buf[0] = (param_2[0] + (r % d)) - param_3[0];
        r = rand();
        d = param_3[1] << 1;
        buf[1] = (param_2[1] + (r % d)) - param_3[1];
        r = rand();
        d = param_3[2] << 1;
        buf[2] = (param_2[2] + (r % d)) - param_3[2];
        buf[3] = param_3[3];
        p = func_8018D364(buf, 0, param_5);
        if (p != 0) {
            *(short *)(*(int *)(p + 0x20) + 0x18) = param_2[3];
        }
    }
    *param_1 = *param_1 + 1;
}


extern int func_8018D364(short *pos, int a1, int a2);

int func_8018D330(short *pos, int a1, int a2)
{
    int p;

    p = func_8018D364(pos, a1, a2);
    if (p != 0) {
        *(s16 *)(p + 0x32) = 1;
    }
    return p;
}


extern u8 *func_801290DC(s32 a0, u8 *a1);

int func_8018D364(short *pos, int a1, int a2)
{
    u8 *v1;

    v1 = func_801290DC(0x55, (u8 *)pos);

    if (v1 != 0) {
        *(s32 *)(v1 + 0x1C) = pos[3];

        if (a1 != 0) {
            *(s32 *)(v1 + 0x10) = *(s32 *)(a1 + 0x0);
            *(s32 *)(v1 + 0x14) = *(s32 *)(a1 + 0x4);
            *(s32 *)(v1 + 0x18) = *(s32 *)(a1 + 0x8);
            *(s32 *)(v1 + 0x34) = *(s32 *)(a1 + 0xC);
        }

        if (a2 != 0) {
            u8 *ptr = *(u8 **)(v1 + 0x20);
            *(s32 *)(ptr + 0x24) = a2;
        }
    }

    return (int)v1;
}


extern s32 func_8012B864(s32 a0);

void func_8018D40C(s32 arg0) {
    s32 v;
    s32 d;

    v = func_8012B864(arg0);

    d = (v + *(s16 *)(arg0 + 0x100)) - *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
    if (d > 0x800) {
        s32 t = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) + 0x1000;
        d = v - t;
    }
    if (d < -0x800) {
        s32 t = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) - 0x1000;
        d = v - t;
    }
    if (d > 0) {
        if (d > 0x20) {
            d = 0x20;
        }
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) =
            *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) + d;
    } else if (d < 0) {
        if (d < -0x20) {
            d = -0x20;
        }
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) =
            *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) + d;
    } else {
        *(s16 *)(arg0 + 0x100) = (rand() & 0x7FF) - 0x400;
    }

    d = *(s16 *)(*(s32 *)(arg0 + 0x64) + 0xFC) - *(s16 *)(arg0 + 0xFC);
    if (d > 0) {
        if (d > 8) {
            d = 8;
        }
        *(s16 *)(arg0 + 0xFC) = *(s16 *)(arg0 + 0xFC) + d;
    } else if (d < 0) {
        if (d < -8) {
            d = -8;
        }
        *(s16 *)(arg0 + 0xFC) = *(s16 *)(arg0 + 0xFC) + d;
    }

    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x10) = *(u16 *)(arg0 + 0xFC) & 0xFFF;
}


void func_8018D514(s32 arg0) {
    s32 v;
    s32 d;

    v = func_8012B864(arg0);

    d = (v + *(s16 *)(arg0 + 0x100)) - *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
    if (d > 0x800) {
        s32 t = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) + 0x1000;
        d = v - t;
    }
    if (d < -0x800) {
        s32 t = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12) - 0x1000;
        d = v - t;
    }
    if (d > 0) {
        if (d > 0x20) {
            d = 0x20;
        }
        *(s16 *)(arg0 + 0xFE) = *(u16 *)(arg0 + 0xFE) + d;
        if (*(s16 *)(arg0 + 0xFE) > 0x200) {
            *(s16 *)(arg0 + 0xFE) = 0x200;
        }
    } else if (d < 0) {
        if (d < -0x20) {
            d = -0x20;
        }
        *(s16 *)(arg0 + 0xFE) = *(u16 *)(arg0 + 0xFE) + d;
        if (*(s16 *)(arg0 + 0xFE) < -0x200) {
            *(s16 *)(arg0 + 0xFE) = -0x200;
        }
    } else {
        *(s16 *)(arg0 + 0x100) = (rand() & 0x7FF) - 0x400;
    }

    d = *(s16 *)(*(s32 *)(arg0 + 0x64) + 0xFC) - *(s16 *)(arg0 + 0xFC);
    if (d > 0) {
        if (d > 8) {
            d = 8;
        }
        *(s16 *)(arg0 + 0xFC) = *(s16 *)(arg0 + 0xFC) + d;
    } else if (d < 0) {
        if (d < -8) {
            d = -8;
        }
        *(s16 *)(arg0 + 0xFC) = *(s16 *)(arg0 + 0xFC) + d;
    }
}


#include "common.h"

/* func_8018D654 @ ov_SC06_018 (subseg ov_SC06_018_jr_80187AEC) — 135 ins. MATCH.
 *
 * GATE: python3 tools/match_one.py func_8018D654 \
 *         --c .run/wave6/func_8018D654/func_8018D654.c \
 *         --asm-subdir asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80187AEC
 *
 * ------------------------------------------------------------------ what it is
 * A per-frame "screen-edge cleanup" tick for one entity.
 *   1. Bail if the entity is dead (f0 == 0) or its f20 sub-object's 0x12 word
 *      still has any of the low 12 bits set (busy/animating).
 *   2. If the global scroll limit D_80126B58[0xC] has not yet passed
 *      self->fC - 0x800000, and the global gate func_8014CB8C() is open, and
 *      self is not kind 0x25, and self->f76 > 0: build a 4-halfword spawn
 *      descriptor {D_80126B5E, D_80126B62 - 0x40, self->fE - 0x30, 0} at
 *      0x10(sp) and, depending on self->f70 (4 = left band, 5 = right band) and
 *      whether the horizontal distance dx = self->f6 - D_80126B5E falls in the
 *      band, hand it to func_8014C3A4(&D_80126B58, self, 0x25, desc).
 *   3. Clamp D_80126B58[0xC] down to self->fC - 0x500000.
 *   4. Walk the 0x60-entry / 0x10C-stride entity table D_801202A0 and, for every
 *      live non-0x318 entity with f3C != 0 whose CURRENT y (f0E) and HOME y
 *      (f42) sit on OPPOSITE sides of self->fE, reset it home: zero f10/f18 and
 *      copy f3A/f42 into f06/f0E.
 *
 * ---------------------------------------------------------------- the levers
 * L1  D_80126B64 IS NOT A SYMBOL HERE — IT IS `D_80126B58 + 0xC`, REACHED
 *     THROUGH A POINTER LOCAL.  This is cookbook §164-08 (`use_related_value`,
 *     cse.c:1781) in its two-offset form.  The target's block-1 shape is
 *
 *         lui   $s2, %hi(D_80126B64) ; addiu $s2, $s2, %lo(D_80126B64)
 *         lw    $a0, 0x0($s2)                       <- the limit read
 *         ...
 *         addiu $a0, $s2, -0xC                      <- &D_80126B58, ONE insn
 *
 *     cse hashes `SYM+0xC` (already live in $s2 because a POINTER LOCAL forced
 *     the full address into a pseudo — §136-5) and rewrites the later plain
 *     `SYM` as `$s2 - 0xC`.  Spelling the limit as its own `extern s32
 *     D_80126B64;` relates nothing: the read collapses to `lui/lw` (−1 insn)
 *     and `&D_80126B58` rebuilds `lui/addiu` (+1) — 135 ins either way, so the
 *     LENGTH never drifts and there is no diff line that names the mistake.
 *     The second call site is in a different extended basic block (the `f70==5`
 *     test is a join point), so cse's table is flushed there and `&D_80126B58`
 *     legitimately rebuilds `lui/addiu` — that asymmetry is the target's, not a
 *     bug.  Block 3 needs its OWN pointer local: one shared variable would stay
 *     live in $s2 instead of rematerialising into $a1.
 *
 * L2  fC/fE AND f38/f3A AND f40/f42 OVERLAP.  `lw 0xC` and `lh 0xE` are the
 *     same 32-bit fixed-point y (0x0E is its integer half).  Declaring `s32 fC`
 *     next to `s16 fE` silently pushes every later field +4 and the stride to
 *     0x110 — the first draft's 116-mismatch OPCODE-MIXED.  Fields are declared
 *     as s16 pairs and the word is read `*(s32 *)&self->fC`.
 *
 * L3  ONE VARIABLE SERVES BOTH `dx` AND THE LOOP COUNTER.  The target puts the
 *     horizontal distance in $s0 (callee-saved, it crosses two calls) and then
 *     the 0..0x60 counter in $s0 as well.  Two separate locals give the counter
 *     a call-clobbered register ($a2) because REG_ALLOC_ORDER prefers those for
 *     an allocno that crosses no call, and the 0x318 constant then slides to
 *     $a3 — 4 extra mismatches through the whole loop.
 *
 * L4  THE `lh $a0, 0x6($s1)` MUST LEAD THE RTL, WHICH MEANS D_80126B5E IS
 *     INLINED IN THE SUBTRACTION AND READ AGAIN FOR v[0].  The pre-reload
 *     scheduler (sched pass 1, on by default at -O2) emits the three load
 *     groups in the order it receives them:
 *         `i = self->f6 - *(s16 *)&D_80126B5E;` first  -> lh f6, lh B5E, lhu B62
 *             -> post-sched: f6, B62, B5E   == TARGET
 *         `bx = *(s16 *)&D_80126B5E; i = self->f6 - bx;` -> lh B5E, lh f6, lhu B62
 *             -> post-sched: B5E, B62, f6   == 5 mismatched, every ordering of
 *                the four stores tried (240 permutations, best 3).
 *     So the `bx` temp cannot exist; both reads are spelled out and cse merges
 *     them into the single `lh`.
 *
 * L5  THE LOCAL IS `s16 v[4]`, NOT `v[8]` — AND THE FRAME IS THE ORACLE.
 *     Merging the two D_80126B5E reads leaves gcc holding a `(subreg:HI)` of the
 *     sign-extended pseudo, for which it reserves an 8-byte frame temp it never
 *     references (`vars= 24` in the `.frame` comment vs the target's 16).  The
 *     descriptor is 4 halfwords = 8 bytes, the phantom temp is the other 8, and
 *     the sum is the target's 0x10 var area with the stores landing on
 *     0x10/0x12/0x14/0x16.  `v[8]` gives frame 0x38 (10 mismatched, all
 *     prologue/epilogue); `v[5]` and `v[6]` likewise.  Byte-probed, all four.
 *
 * L6  THE STORE ORDER IS v[0], v[1], v[2], v[3] AND THE RESET BLOCK IS
 *     f6, fE, f10, f18.  The latter is the giv base: gcc prepends address givs
 *     as it discovers them, so the LAST address in the loop body becomes the
 *     combined base register — `e->f18` gives the target's `addiu $a0,$a1,0x18`.
 *     Writing the two `sw`s first makes 0x0E the base (`addiu $a0,$a1,0xE`) and
 *     every offset in the loop shifts.  The two reset blocks are textually
 *     identical so jump.c cross-jumps them into the single `.L8018D828`.
 *
 * L7  `if (e->fE >= self->fE)` — the `>=` spelling, not `<`.  gcc emits
 *     `slt tmp,x,y; bnez tmp,<else>`, so the ELSE arm is the one at the branch
 *     target (.L8018D814) and the THEN arm falls through, which is the target's
 *     block order.  Same for both D_80126B58[0xC] tests (`>=`, not `<=`).
 *
 * ---------------------------------------------------------------- integration
 * INTEGRATION SURFACE (§52b/§161c) — every extern below is already declared in
 * the destination TU src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c with the
 * IDENTICAL spelling, so nothing conflicts and nothing needs to move to block
 * scope:
 *     extern s32 D_80126B58;                                          (L48)
 *     extern u8  D_801202A0[];                                        (L377)
 *     extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);     (L516)
 *     extern s32 func_8014CB8C(void);                                 (L556)
 *     extern u16 D_80126B5E;                                          (L1781)
 *     extern u16 D_80126B62;                                          (L1782)
 * D_80126B5E is `u16` fleet-wide but this body needs a SIGNED read (`lh`), so it
 * is read as `*(s16 *)&D_80126B5E` — that keeps the canonical decl and avoids
 * the §163a conflict entirely.  D_80126B64 is deliberately NOT declared (see L1).
 * Only the typedef `Ent_8018D654` is new; the TU carries `Ent_80188E10`,
 * `V4_80188E10` and `OtBlk_8018A974`, so the name is free (§120).
 *
 * SIBLINGS (family reach x3 — the two zero-crack twins are func_8018D3A4 in
 * ov_SC06_032/ov_SC06_032_jr_80182890 and func_80189390 in
 * ov_SC06_033/ov_SC06_033_jr_80186574).  Every symbol this body touches is
 * RESIDENT — D_80126B58, D_80126B5E, D_80126B62, D_801202A0, func_8014CB8C,
 * func_8014C3A4 — so the §40 remap is expected to be pure IDENTITY: no
 * per-overlay symbol to re-point.  Check each sibling TU's canonical spellings
 * before sweeping (§56b — carry the TU's types, not this draft's).
 */

typedef struct {
    u16 f0;                     /* 0x00  kind; 0 = dead, 0x318 = skipped     */
    u8  p02[0x04 - 0x02];
    s16 f4;                     /* 0x04  x, fractional half                  */
    s16 f6;                     /* 0x06  x                                   */
    u8  p08[0x0C - 0x08];
    s16 fC;                     /* 0x0C  y, fractional half                  */
    s16 fE;                     /* 0x0E  y   (*(s32 *)&fC is the whole fixed) */
    s32 f10;                    /* 0x10  velocity, zeroed on reset           */
    u8  p14[0x18 - 0x14];
    s32 f18;                    /* 0x18  velocity, zeroed on reset           */
    u8  p1C[0x20 - 0x1C];
    s32 f20;                    /* 0x20  -> sub object (0x12 = busy bits)    */
    u8  p24[0x38 - 0x24];
    s16 f38;                    /* 0x38  home x, fractional half             */
    s16 f3A;                    /* 0x3A  home x                              */
    s32 f3C;                    /* 0x3C  "has a home" flag                   */
    s16 f40;                    /* 0x40  home y, fractional half             */
    s16 f42;                    /* 0x42  home y                              */
    u8  p44[0x5E - 0x44];
    u8  f5E;                    /* 0x5E  kind tag; 0x25 is excluded          */
    u8  p5F[0x70 - 0x5F];
    s16 f70;                    /* 0x70  band: 4 = left, 5 = right           */
    u8  p72[0x76 - 0x72];
    s16 f76;                    /* 0x76  budget                              */
    u8  p78[0x10C - 0x78];      /* stride 0x10C, 0x60 entries                */
} Ent_8018D654;

extern s32 D_80126B58;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u8  D_801202A0[];

extern s32 func_8014CB8C(void);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);

void func_8018D654(Ent_8018D654 *self) {
    s16 v[4];                   /* 0x10(sp); L5: gcc adds the other 8 bytes */
    Ent_8018D654 *e;
    s32 i;

    if (self->f0 == 0) {
        return;
    }
    if ((*(u16 *)(self->f20 + 0x12) & 0xFFF) != 0) {
        return;
    }

    {
        s32 *lim = (s32 *)((u8 *)&D_80126B58 + 0xC);            /* L1 */

        if (*lim >= *(s32 *)&self->fC - 0x800000) {
            if (func_8014CB8C() != 0 && self->f5E != 0x25 && self->f76 > 0) {
                i = self->f6 - *(s16 *)&D_80126B5E;             /* L3, L4 */
                v[0] = *(s16 *)&D_80126B5E;                     /* L4 */
                v[1] = D_80126B62 - 0x40;
                v[2] = self->fE - 0x30;
                v[3] = 0;
                if (self->f70 == 4 && i >= -8 && i <= 0xB0) {
                    func_8014C3A4(&D_80126B58, (s32)self, 0x25, (s32)v);
                }
                if (self->f70 == 5 && i >= -0xB0 && i <= 8) {
                    func_8014C3A4(&D_80126B58, (s32)self, 0x25, (s32)v);
                }
            }
        }
    }

    {
        s32 *lim = (s32 *)((u8 *)&D_80126B58 + 0xC);            /* L1: its own */

        if (*lim >= *(s32 *)&self->fC - 0x500000) {
            *lim = *(s32 *)&self->fC - 0x500000;
        }
    }

    e = (Ent_8018D654 *)D_801202A0;
    for (i = 0; i < 0x60; i++, e++) {
        if (e->f0 == 0) {
            continue;
        }
        if (e->f0 == 0x318) {
            continue;
        }
        if (e->f3C == 0) {
            continue;
        }
        if (e->fE >= self->fE) {                                /* L7 */
            if (e->f42 < self->fE) {
                e->f6 = e->f3A;                                 /* L6 */
                e->fE = e->f42;
                e->f10 = 0;
                e->f18 = 0;
            }
        } else {
            if (e->f42 >= self->fE) {
                e->f6 = e->f3A;                                 /* L6 */
                e->fE = e->f42;
                e->f10 = 0;
                e->f18 = 0;
            }
        }
    }
}


// func_8018D870 — ov_SC06_018 / ov_SC06_018_jr_8017C24C
// Sibling of func_8018E188 (same TU, banked MATCH) — shares the entry decrement block,
// the 0x82&1 finisher, the C8/C9 pokes, the two 8-iteration spawn loops (0x281 / 0x23),
// and the three-field (0xCC/0xD0/0xD4) particle-reseed block VERBATIM. This function adds
// a THIRD leading func_8012C658 triple-spawn (not present in E188) and a FOURTH field
// (0xD8) that repeats the two 8-iteration spawn loops against a second base pointer before
// the two unconditional func_8012C218 tail calls.

extern s32 rand(void);
extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_8002D4C8(s32, s32);
extern s32 func_8012C658(s32, s32, s32);
extern s32 func_8012C588(s32, s32);
extern u8 *func_8012913C(s32);
extern void func_8012B23C(void *);
extern void func_8012B1B4(void *, void *);
extern void func_8012A828(s32, void *);
extern void func_8012C218(void *);
extern u8 D_801D1210;
extern u8 D_801D1200;
extern u8 D_801D11DC;

void func_8018D870(void *arg) {
    register u8 *p __asm__("$18");   /* $s2 */
    s32 e;
    s32 i;
    s32 iv;
    s32 d8;

    p = (u8 *)arg;
    e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(u16 *)(p + 0x82) = 0;
            *(u16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(u16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(u16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0 && *(s16 *)(p + 0x60) != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec < 1) dec = 1;
            } else {
                dec = *(s16 *)(p + 0x60);
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
            ((void (*)(void *, s32))func_8016AA50)(p, dec);
        }
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            func_80019064(&D_801D1210);
        }
    }

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520((s32)p);
        if (*(u8 *)(p + 0xC9)) func_8002A790((s32)p);
    }

    if (*(s16 *)(p + 0x76) < 0) {
        func_8002D4C8(0xAE0, 0);

        {
            s32 t = func_8012C658(0x33, 3, (s32)p);
            if (t != 0) {
                *(s16 *)(t + 0x16) = -0x10;
                *(u16 *)(t + 0x12) = 0;
                *(s16 *)(t + 0x1A) = -4;
            }
        }
        {
            s32 t = func_8012C658(0x33, 2, (s32)p);
            if (t != 0) {
                *(u16 *)(t + 0x12) = 5;
                *(s16 *)(t + 0x16) = -0x10;
                *(u16 *)(t + 0x1A) = 4;
            }
        }
        {
            s32 t = func_8012C658(0x32, 2, (s32)p);
            if (t != 0) {
                *(s16 *)(t + 0x12) = -5;
                *(s16 *)(t + 0x16) = -0x10;
                *(u16 *)(t + 0x1A) = 4;
            }
        }

        i = 0;
        do {
            iv = ((s32 (*)(s32, void *))func_8012C588)(0x281, p);
            if (iv != 0) {
                *(s32 *)(iv + 0x1C) = 2;
                *(u16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                *(u16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                *(u16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            i++;
        } while (i < 8);
        i = 0;
        do {
            iv = (s32)func_8012913C(0x23);
            if (iv != 0) {
                s32 r;
                s32 sv;
                r = rand();
                *(u16 *)(iv + 0x06) = *(u16 *)(p + 0x06) + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x0A) = *(u16 *)(p + 0x0A) - (r & 0x3F) - 0x20;
                r = rand();
                sv = *(u16 *)(p + 0x0E);
                *(s32 *)(iv + 0x18) = 0;
                *(s32 *)(iv + 0x14) = 0;
                *(s32 *)(iv + 0x10) = 0;
                *(u16 *)(iv + 0x0E) = sv + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x34) = (r & 0x17FF) + 0x1800;
            }
            i++;
        } while (i < 8);

        iv = *(s32 *)(p + 0xCC);
        if (iv != 0) {
            *(u16 *)(iv + 0x02) = 5;
            *(u16 *)(iv + 0x34) = 0;
            func_8012B23C((void *)iv);
            func_8012B1B4((void *)iv, &D_801D1200);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801D11DC);
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x38;
            *(u16 *)(iv + 0xFC) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0xFE) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0x100) = (rand() & 0xFF) - 0x80;
            *(s32 *)(iv + 0x1C) = 0x3C;
        }
        iv = *(s32 *)(p + 0xD0);
        if (iv != 0) {
            *(u16 *)(iv + 0x02) = 5;
            *(u16 *)(iv + 0x34) = 0;
            func_8012B23C((void *)iv);
            func_8012B1B4((void *)iv, &D_801D1200);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801D11DC);
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x38;
            *(u16 *)(iv + 0xFC) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0xFE) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0x100) = (rand() & 0xFF) - 0x80;
            *(s32 *)(iv + 0x1C) = 0x3C;
        }
        iv = *(s32 *)(p + 0xD4);
        if (iv != 0) {
            *(u16 *)(iv + 0x02) = 5;
            *(u16 *)(iv + 0x34) = 0;
            func_8012B23C((void *)iv);
            func_8012B1B4((void *)iv, &D_801D1200);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801D11DC);
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x38;
            *(u16 *)(iv + 0xFC) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0xFE) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0x100) = (rand() & 0xFF) - 0x80;
            *(s32 *)(iv + 0x1C) = 0x3C;
        }

        {
        register s32 t __asm__("$4");
        t = *(s32 *)(p + 0xD8);
        d8 = t;
        if (t != 0) {
            i = 0;
            do {
                iv = func_8012C588(0x281, d8);
                if (iv != 0) {
                    *(s32 *)(iv + 0x1C) = 2;
                    *(u16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                    *(u16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                    *(u16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
                }
                i++;
            } while (i < 8);
            i = 0;
            do {
                iv = (s32)func_8012913C(0x23);
                if (iv != 0) {
                    s32 r;
                    s32 sv;
                    r = rand();
                    *(u16 *)(iv + 0x06) = *(u16 *)(d8 + 0x06) + (r & 0x3F) - 0x20;
                    r = rand();
                    *(u16 *)(iv + 0x0A) = *(u16 *)(d8 + 0x0A) - (r & 0x3F) - 0x20;
                    r = rand();
                    sv = *(u16 *)(d8 + 0x0E);
                    *(s32 *)(iv + 0x18) = 0;
                    *(s32 *)(iv + 0x14) = 0;
                    *(s32 *)(iv + 0x10) = 0;
                    *(u16 *)(iv + 0x0E) = sv + (r & 0x3F) - 0x20;
                    r = rand();
                    *(u16 *)(iv + 0x34) = (r & 0x17FF) + 0x1800;
                }
                i++;
            } while (i < 8);
            func_8012C218((void *)d8);
        }
        }
        func_8012C218((void *)p);
    } else {
        func_8002D4C8(0x9B7, 0);
        *(u16 *)(p + 0x5C) = 0x8800;
        *(u16 *)(p + 0x60) = 0;
        *(u8 *)(p + 0xC1) = 0;
        *(u8 *)(p + 0xC2) = 0x10;
    }
}


// func_8018DE60 -- ov_SC06_018 / ov_SC06_018_jr_80187AEC
//
// Structural sibling of func_8018E188 (SAME TU, banked MATCH, this file: func_8018E188).
// Shares VERBATIM: the 0x60 gate + 0x1D snapshot block, the 0x78/0x60 decrement block
// (AND form -- see E188's @stuck note), the 0x82&1 finisher, and the C8/C9 pokes.
// Diverges after that: instead of E188's 0x76<0 spawn-loop / CC-D0-D4 reseed, this
// function's 0x76<0 arm sets a distinct "state 2" field group (offsets 2/0x5C/0x34/
// 0xC1/0xF4 + clears bit 0x80 of *(p+0x20)->0x2C), and its else arm plays a different
// sound (func_8002D4C8(0xAD8,0) vs E188's 0xAE0) then tail-calls func_8018D654 (still
// INCLUDE_ASM in this TU -- no other TU references it, so this call site sets its own
// convention: void func_8018D654(void *)).
//
// @class: regalloc-order
// @stuck: none -- see match_one output.

extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_8002D4C8(s32, s32);
extern void func_8018D654();
extern u8 D_801D1210;

void func_8018DE60(void *arg) {
    u8 *p = (u8 *)arg;
    s32 e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(u16 *)(p + 0x82) = 0;
            *(u16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(u16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(u16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0 && *(s16 *)(p + 0x60) != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec < 1) dec = 1;
            } else {
                dec = *(s16 *)(p + 0x60);
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
            ((void (*)(void *, s32))func_8016AA50)(p, dec);
        }
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            func_80019064(&D_801D1210);
        }
    }

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520(p);
        if (*(u8 *)(p + 0xC9)) func_8002A790(p);
    }

    if (*(s16 *)(p + 0x76) < 0) {
        s32 q = *(s32 *)(p + 0x20);
        *(s16 *)(p + 0x02) = 0xA;
        *(u16 *)(p + 0x5C) = 0x800;
        *(u16 *)(p + 0x34) = 0;
        *(u8  *)(p + 0xC1) = 0;
        *(s32 *)(p + 0xF4) = 1;
        *(u16 *)(q + 0x2C) &= 0xFF7F;
    } else {
        func_8002D4C8(0xAD8, 0);
        *(u16 *)(p + 0x5C) = 0x8800;
        *(u16 *)(p + 0x60) = 0;
        *(u8  *)(p + 0xC1) = 0;
        *(u8  *)(p + 0xC2) = 0x10;
        func_8018D654(p);
    }
}




// func_8018DFF4 -- ov_SC06_018 / ov_SC06_018_jr_80187AEC
//
// Structural sibling of func_8018E188 (SAME TU, banked MATCH, this file: func_8018E188).
// Shares VERBATIM: the 0x60 gate + 0x1D snapshot block, the 0x78/0x60 decrement block
// (AND form -- see E188's @stuck note), the 0x82&1 finisher, and the C8/C9 pokes.
// Diverges after that: instead of E188's 0x76<0 spawn-loop / CC-D0-D4 reseed, this
// function's 0x76<0 arm sets a distinct "state 2" field group (offsets 2/0x5C/0x34/
// 0xC1/0xF4 + clears bit 0x80 of *(p+0x20)->0x2C), and its else arm plays a different
// sound (func_8002D4C8(0xAD8,0) vs E188's 0xAE0) then tail-calls func_8018D654 (still
// INCLUDE_ASM in this TU -- no other TU references it, so this call site sets its own
// convention: void func_8018D654(void *)).
//
// @class: regalloc-order
// @stuck: none -- see match_one output.

extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_8002D4C8(s32, s32);
extern void func_8018D654();

void func_8018DFF4(void *arg) {
    u8 *p = (u8 *)arg;
    s32 e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(u16 *)(p + 0x82) = 0;
            *(u16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(u16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(u16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0 && *(s16 *)(p + 0x60) != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec < 1) dec = 1;
            } else {
                dec = *(s16 *)(p + 0x60);
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
            ((void (*)(void *, s32))func_8016AA50)(p, dec);
        }
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            func_80019064(&D_801D1210);
        }
    }

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520(p);
        if (*(u8 *)(p + 0xC9)) func_8002A790(p);
    }

    if (*(s16 *)(p + 0x76) < 0) {
        s32 q = *(s32 *)(p + 0x20);
        *(s16 *)(p + 0x02) = 0xB;
        *(u16 *)(p + 0x5C) = 0x800;
        *(u16 *)(p + 0x34) = 0;
        *(u8  *)(p + 0xC1) = 0;
        *(s32 *)(p + 0xF4) = 1;
        *(u16 *)(q + 0x2C) &= 0xFF7F;
    } else {
        func_8002D4C8(0xAD8, 0);
        *(u16 *)(p + 0x5C) = 0x8800;
        *(u16 *)(p + 0x60) = 0;
        *(u8  *)(p + 0xC1) = 0;
        *(u8  *)(p + 0xC2) = 0x10;
        func_8018D654(p);
    }
}


// @class: regalloc-order
// @stuck: none — MATCH (277 ins). p pinned $s1; e/spawn-ptr coalesce $s0; counter $s2; const2 hoisted $s3.
//   Key lever: dec-block written as AND form `if (q!=0 && p60!=0){compute}else{dec=p60}` (compute as
//   fall-through) — the OR/De-Morgan form inverted the 2nd branch (bnez v1) and drifted +1 ins.

extern s32 rand(void);
extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_8002D4C8(s32, s32);
extern s32 func_8012C588(s32, s32);
extern u8 *func_8012913C(s32);
extern void func_8012B23C(void *);
extern void func_8012B1B4(void *, void *);
extern void func_8012A828(s32, void*);
extern void func_8012C218(void *);
extern u8 D_801D1210;
extern u8 D_801D1200;
extern u8 D_801D11DC;

void func_8018E188(void *arg) {
    register u8 *p __asm__("$17");   /* $s1 */
    s32 e;
    s32 i;
    s32 iv;

    p = (u8 *)arg;
    e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(u16 *)(p + 0x82) = 0;
            *(u16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(u16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(u16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0 && *(s16 *)(p + 0x60) != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec < 1) dec = 1;
            } else {
                dec = *(s16 *)(p + 0x60);
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
            ((void (*)(void *, s32))func_8016AA50)(p, dec);
        }
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            func_80019064(&D_801D1210);
        }
    }

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520(p);
        if (*(u8 *)(p + 0xC9)) func_8002A790(p);
    }

    if (*(s16 *)(p + 0x76) < 0) {
        if (-1000 < *(s16 *)(p + 0x76)) {
            func_8002D4C8(0xAE0, 0);
        }
        i = 0;
        do {
            iv = ((s32 (*)(s32, void *))func_8012C588)(0x281, p);
            if (iv != 0) {
                *(s32 *)(iv + 0x1C) = 2;
                *(u16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                *(u16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                *(u16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            i++;
        } while (i < 8);
        i = 0;
        do {
            iv = (s32)func_8012913C(0x23);
            if (iv != 0) {
                s32 r;
                s32 sv;
                r = rand();
                *(u16 *)(iv + 0x06) = *(u16 *)(p + 0x06) + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x0A) = *(u16 *)(p + 0x0A) - (r & 0x3F) - 0x20;
                r = rand();
                sv = *(u16 *)(p + 0x0E);
                *(s32 *)(iv + 0x18) = 0;
                *(s32 *)(iv + 0x14) = 0;
                *(s32 *)(iv + 0x10) = 0;
                *(u16 *)(iv + 0x0E) = sv + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x34) = (r & 0x17FF) + 0x1800;
            }
            i++;
        } while (i < 8);

        iv = *(s32 *)(p + 0xCC);
        if (iv != 0) {
            *(u16 *)(iv + 0x02) = 5;
            *(u16 *)(iv + 0x34) = 0;
            func_8012B23C((void *)iv);
            func_8012B1B4((void *)iv, &D_801D1200);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801D11DC);
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x38;
            *(u16 *)(iv + 0xFC) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0xFE) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0x100) = (rand() & 0xFF) - 0x80;
            *(s32 *)(iv + 0x1C) = 0x3C;
        }
        iv = *(s32 *)(p + 0xD0);
        if (iv != 0) {
            *(u16 *)(iv + 0x02) = 5;
            *(u16 *)(iv + 0x34) = 0;
            func_8012B23C((void *)iv);
            func_8012B1B4((void *)iv, &D_801D1200);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801D11DC);
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x38;
            *(u16 *)(iv + 0xFC) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0xFE) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0x100) = (rand() & 0xFF) - 0x80;
            *(s32 *)(iv + 0x1C) = 0x3C;
        }
        iv = *(s32 *)(p + 0xD4);
        if (iv != 0) {
            *(u16 *)(iv + 0x02) = 5;
            *(u16 *)(iv + 0x34) = 0;
            func_8012B23C((void *)iv);
            func_8012B1B4((void *)iv, &D_801D1200);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801D11DC);
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x38;
            *(u16 *)(iv + 0xFC) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0xFE) = (rand() & 0xFF) - 0x80;
            *(u16 *)(iv + 0x100) = (rand() & 0xFF) - 0x80;
            *(s32 *)(iv + 0x1C) = 0x3C;
        }
        *(s32 *)(*(s32 *)(p + 0x64) + 0xCC) = 0;
        func_8012C218(p);
    } else {
        *(u16 *)(p + 0x5C) = 0x8800;
        *(u16 *)(p + 0x60) = 0;
        *(u8 *)(p + 0xC1) = 0;
        *(u8 *)(p + 0xC2) = 0x10;
    }
}


#include "common.h"

/* func_8018E5DC — ov_SC06_018 / ov_SC06_018_jr_8017C24C
 *
 * Direct structural sibling of func_8018E188 (SAME TU, banked MATCH,
 * src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c:9077) and of func_8018D5C0
 * (src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c:8530).  Shares VERBATIM:
 *   - the 0x60 gate + 0x1D snapshot block,
 *   - the 0x78/0x60 decrement block (AND form — see E188's @stuck note),
 *   - the 0x82&1 finisher, the C8/C9 pokes,
 *   - the two 8-iteration spawn loops (0x281 / 0x23),
 *   - the 0x76<0 else arm (0x8800 / 0x60 / 0xC1 / 0xC2).
 * It ADDS three leading func_8012C658 triple-spawns and replaces E188's
 * CC/D0/D4 particle-reseed with the byte-proven RTP_SND block already
 * matched in this TU at :4292 (func_8017F5xx) — same &D_800AF648 $a0-pin
 * idiom, different constants (0x9F/0x13F, 0x77/0xEF, /0xA0, no panning).
 *
 * Regalloc target (identical to E188): p pinned $s1, e/spawn-ptr coalesce
 * on $s0, loop counter $s2, the hoisted constant 2 on $s3.
 *
 * @class: regalloc-order
 * @stuck: none — MATCH (248 ins), iteration 2.
 *   ONLY residual on iteration 1 was REGALLOC-PERM/$v1>$a0: the 2nd and 3rd
 *   func_8012C658 results landed in $v1 where the target has $a0 (block 1 was
 *   already right).  LEVER: the three spawn pointers are ONE function-scope
 *   variable `t`, not three block-scope `s32 t`.  Block 1 CSEs the shared -4
 *   constant into $v1, which forces its pointer to $a0; making `t` a single
 *   multi-block (global) allocno propagates that $a0 to blocks 2 and 3.  With
 *   three separate block-local pseudos each block re-runs local-alloc
 *   independently and takes $v1 (lower in REG_ALLOC_ORDER).  This is the §76
 *   "variable reuse selects the allocno CLASS" law applied to a pointer whose
 *   live ranges are disjoint — reuse is what makes it global, and global is
 *   what makes the first block's forced choice bind the later ones.
 */

extern s32 rand(void);
extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_8002D4C8(s32, s32);
extern s32 func_8012C658(s32, s32, s32);
extern s32 func_8012C588(s32, s32);
extern u8 *func_8012913C(s32);
extern void func_8012C218(void *);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8 D_801D1210;

void func_8018E5DC(void *arg) {

    extern u8 D_800AF648;

    /* L5: slot offsets are exact only through ONE struct (see the TU's other
       RTP_SND site) — rv at sp+0x10, sxy at sp+0x18, z sp+0x1C, flag sp+0x20. */
    struct {
        s16 rv[4];   /* sp+0x10 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    register u8 *p __asm__("$17");   /* $s1 */
    s32 e;
    s32 i;
    s32 iv;
    s32 t;

    p = (u8 *)arg;
    e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(u16 *)(p + 0x82) = 0;
            *(u16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(u16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(u16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0 && *(s16 *)(p + 0x60) != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec < 1) dec = 1;
            } else {
                dec = *(s16 *)(p + 0x60);
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
            ((void (*)(void *, s32))func_8016AA50)(p, dec);
        }
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            func_80019064(&D_801D1210);
        }
    }

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520(p);
        if (*(u8 *)(p + 0xC9)) func_8002A790(p);
    }

    if (*(s16 *)(p + 0x76) < 0) {
        t = func_8012C658(0x33, 3, (s32)p);
        if (t != 0) {
            *(s16 *)(t + 0x12) = -4;
            *(s16 *)(t + 0x16) = -0x10;
            *(s16 *)(t + 0x1A) = -4;
        }
        t = func_8012C658(0x33, 2, (s32)p);
        if (t != 0) {
            *(s16 *)(t + 0x12) = -4;
            *(s16 *)(t + 0x16) = -0x10;
            *(u16 *)(t + 0x1A) = 0;
        }
        t = func_8012C658(0x32, 2, (s32)p);
        if (t != 0) {
            *(s16 *)(t + 0x12) = -4;
            *(s16 *)(t + 0x16) = -0x10;
            *(u16 *)(t + 0x1A) = 4;
        }

        i = 0;
        do {
            iv = ((s32 (*)(s32, void *))func_8012C588)(0x281, p);
            if (iv != 0) {
                *(s32 *)(iv + 0x1C) = 2;
                *(u16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                *(u16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                *(u16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            i++;
        } while (i < 8);
        i = 0;
        do {
            iv = (s32)func_8012913C(0x23);
            if (iv != 0) {
                s32 r;
                s32 sv;
                r = rand();
                *(u16 *)(iv + 0x06) = *(u16 *)(p + 0x06) + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x0A) = *(u16 *)(p + 0x0A) - (r & 0x3F) - 0x20;
                r = rand();
                sv = *(u16 *)(p + 0x0E);
                *(s32 *)(iv + 0x18) = 0;
                *(s32 *)(iv + 0x14) = 0;
                *(s32 *)(iv + 0x10) = 0;
                *(u16 *)(iv + 0x0E) = sv + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x34) = (r & 0x17FF) + 0x1800;
            }
            i++;
        } while (i < 8);

        L.rv[0] = *(s32 *)(*(s32 *)(p + 0x20) + 0x48);
        L.rv[1] = *(s32 *)(*(s32 *)(p + 0x20) + 0x4C);
        L.rv[2] = *(s32 *)(*(s32 *)(p + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.rv, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F
                      && (u32)((L.sxy[1] + 0x77) & 0xFFFF) < 0xEF) {
            s32 x = (s16)L.sxy[0];
            s32 ax;

            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xA0 - ax) * 0x7F) / 0xA0;
            func_8002D4C8(0xB32, (ax | 0x1000) & 0xFFFF);
        }
        func_8012C218((void *)p);
    } else {
        *(u16 *)(p + 0x5C) = 0x8800;
        *(u16 *)(p + 0x60) = 0;
        *(u8 *)(p + 0xC1) = 0;
        *(u8 *)(p + 0xC2) = 0x10;
    }
}


#include "common.h"

/* func_8018E9BC — ov_SC06_018 / ov_SC06_018_jr_80187AEC
 *
 * §160g STEP 0 HIT, in the DESTINATION TU ITSELF: func_8018E5DC
 * (src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c:5416, banked MATCH, 248 ins) is a
 * near-verbatim template.  Shared VERBATIM: the 0x60 gate + 0x1D snapshot, the
 * 0x78/0x60 decrement (AND form), the 0x82&1 finisher, the C8/C9 pokes, the
 * three func_8012C658 triple-spawns, both 8-iteration spawn loops (0x281/0x23),
 * the RTP_SND block (&D_800AF648 $a0-pin idiom, 0x9F/0x13F, 0x77/0xEF, /0xA0),
 * and the 0x76<0 else arm (0x8800/0x60/0xC1/0xC2).
 *
 * TWO DELTAS vs E5DC:
 *   (1) the triple-spawn constants: 0x12 is +4 here (E5DC has -4), and 0x1A
 *       runs -4 / 0 / +4.  This changes WHICH constant CSEs: E5DC shared -4
 *       across 0x12+0x1A of block 1; here block 1's three constants are all
 *       distinct (4, -0x10, -4 -> $v0 reused serially) while block 3 shares
 *       +4 across 0x12+0x1A (-> $v1, with -0x10 in $v0).  Byte-confirmed
 *       against the target at 8018EAFC / 8018EB2C / 8018EB58.
 *   (2) an EXTRA guard block between the second spawn loop and the RTP stores:
 *       h = *(s32*)(p+0x64); if (*(s16*)(h+0x36) == *(s16*)(p+0xFC))
 *       *(s32*)(h+0xCC) = 0;   The target loads 0x64 ONCE into $a0 and reuses
 *       that base for the 0xCC store, so it must be a variable, not two loads.
 *
 * §76 LEVER (inherited from E5DC's @stuck, and reinforced here): the three
 * spawn pointers AND this new 0x64 base are ONE function-scope variable `t`,
 * not four block-scope pseudos.  Reuse is what makes the allocno GLOBAL, and
 * global is what makes block 1's forced $a0 (its constants monopolise $v0)
 * bind blocks 2, 3 and the 0x64 block — all four are $a0 in the target.  Four
 * separate block-local pseudos each re-run local-alloc and take $v1 (lower in
 * REG_ALLOC_ORDER).
 *
 * Regalloc target (identical to E5DC): p pinned $s1, spawn-ptr `iv` on $s0,
 * loop counter $s2, the hoisted constant 2 on $s3.
 *
 * @class: regalloc-order
 */

extern s32 rand(void);
extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_8002D4C8(s32, s32);
extern s32 func_8012C658(s32, s32, s32);
extern s32 func_8012C588(s32, s32);
extern u8 *func_8012913C(s32);
extern void func_8012C218(void *);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8 D_801D1210;

void func_8018E9BC(void *arg) {

    extern u8 D_800AF648;

    /* L5: slot offsets are exact only through ONE struct (see the TU's other
       RTP_SND sites) — rv at sp+0x10, sxy at sp+0x18, z sp+0x1C, flag sp+0x20. */
    struct {
        s16 rv[4];   /* sp+0x10 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    register u8 *p __asm__("$17");   /* $s1 */
    s32 e;
    s32 i;
    s32 iv;
    s32 t;

    p = (u8 *)arg;
    e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(u16 *)(p + 0x82) = 0;
            *(u16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(u16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(u16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0 && *(s16 *)(p + 0x60) != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec < 1) dec = 1;
            } else {
                dec = *(s16 *)(p + 0x60);
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
            ((void (*)(void *, s32))func_8016AA50)(p, dec);
        }
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            func_80019064(&D_801D1210);
        }
    }

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520(p);
        if (*(u8 *)(p + 0xC9)) func_8002A790(p);
    }

    if (*(s16 *)(p + 0x76) < 0) {
        t = func_8012C658(0x33, 3, (s32)p);
        if (t != 0) {
            *(s16 *)(t + 0x12) = 4;
            *(s16 *)(t + 0x16) = -0x10;
            *(s16 *)(t + 0x1A) = -4;
        }
        t = func_8012C658(0x33, 2, (s32)p);
        if (t != 0) {
            *(s16 *)(t + 0x12) = 4;
            *(s16 *)(t + 0x16) = -0x10;
            *(u16 *)(t + 0x1A) = 0;
        }
        t = func_8012C658(0x32, 2, (s32)p);
        if (t != 0) {
            *(s16 *)(t + 0x12) = 4;
            *(s16 *)(t + 0x16) = -0x10;
            *(s16 *)(t + 0x1A) = 4;
        }

        i = 0;
        do {
            iv = ((s32 (*)(s32, void *))func_8012C588)(0x281, p);
            if (iv != 0) {
                *(s32 *)(iv + 0x1C) = 2;
                *(u16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                *(u16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                *(u16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            i++;
        } while (i < 8);
        i = 0;
        do {
            iv = (s32)func_8012913C(0x23);
            if (iv != 0) {
                s32 r;
                s32 sv;
                r = rand();
                *(u16 *)(iv + 0x06) = *(u16 *)(p + 0x06) + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x0A) = *(u16 *)(p + 0x0A) - (r & 0x3F) - 0x20;
                r = rand();
                sv = *(u16 *)(p + 0x0E);
                *(s32 *)(iv + 0x18) = 0;
                *(s32 *)(iv + 0x14) = 0;
                *(s32 *)(iv + 0x10) = 0;
                *(u16 *)(iv + 0x0E) = sv + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x34) = (r & 0x17FF) + 0x1800;
            }
            i++;
        } while (i < 8);

        t = *(s32 *)(p + 0x64);
        if (*(s16 *)(t + 0x36) == *(s16 *)(p + 0xFC)) {
            *(s32 *)(t + 0xCC) = 0;
        }

        L.rv[0] = *(s32 *)(*(s32 *)(p + 0x20) + 0x48);
        L.rv[1] = *(s32 *)(*(s32 *)(p + 0x20) + 0x4C);
        L.rv[2] = *(s32 *)(*(s32 *)(p + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.rv, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0x9F) & 0xFFFF) < 0x13F
                      && (u32)((L.sxy[1] + 0x77) & 0xFFFF) < 0xEF) {
            s32 x = (s16)L.sxy[0];
            s32 ax;

            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xA0 - ax) * 0x7F) / 0xA0;
            func_8002D4C8(0xB32, (ax | 0x1000) & 0xFFFF);
        }
        func_8012C218((void *)p);
    } else {
        *(u16 *)(p + 0x5C) = 0x8800;
        *(u16 *)(p + 0x60) = 0;
        *(u8 *)(p + 0xC1) = 0;
        *(u8 *)(p + 0xC2) = 0x10;
    }
}


#include "common.h"

/* func_8018EDB8 — ov_SC06_018 / ov_SC06_018_jr_80187AEC
 *
 * Direct structural sibling of func_8018E188 (SAME TU, banked MATCH,
 * src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c:5255).  Shares VERBATIM:
 *   - the 0x60 gate + 0x1D snapshot block,
 *   - the 0x78/0x60 decrement block (AND form — see E188's @stuck note),
 *   - the 0x82&1 finisher, the C8/C9 pokes,
 *   - the two 8-iteration spawn loops (0x281 / 0x23).
 * Diverges: no leading func_8002D4C8 in the 0x76<0 arm, E188's CC/D0/D4
 * particle reseed is replaced by a "hand off to the 0x64 owner" block
 * (5C/60/5E/D8/76/62 pokes + func_8018D870), and the else arm gains a
 * leading func_8002D4C8(0x9B7, 0).
 *
 * Regalloc target (identical to E188): p pinned $s1, e/spawn-ptr coalesce
 * on $s0, loop counter $s2, the hoisted constant 2 on $s3.
 *
 * @class: regalloc-order
 * @stuck: none — MATCH (170 ins), iteration 3.  Body was E188 verbatim on
 *   iteration 1; both residuals were in the 12-insn 0x64 hand-off tail:
 *   (1) `-0xA` stored through a `u16 *` folds to the unsigned 0xFFF6 and emits
 *       `ori $v0,$zero,0xfff6`; the target's `addiu $v0,$zero,-0xA` needs the
 *       store spelled `*(s16 *)(q + 0x76)` (§162k-adjacent width law, applied
 *       to a CONSTANT rather than a load).
 *   (2) the tail pointer lives in TWO registers — $s0 (the `lw 0x20` base) and
 *       $a0 (every store base + the func_8018D870 arg).  Spelling that as
 *       `register s32 q __asm__("$4"); q = iv;` alone is NOT enough: with the
 *       0x20 load left BELOW the copy, local-alloc's `optimize_reg_copy_1`
 *       (§162j1) rewrites that surviving use $s0 -> $a0, and the now-$a0-based
 *       load can no longer be scheduled above the $a0-based stores (they may
 *       alias), costing two load-delay nops = the +2 LENGTH-DRIFT.
 *   LEVER: `optimize_reg_copy_1`'s substitution scan runs FORWARD from the copy
 *   only, so hoisting the surviving use ABOVE `q = iv` in SOURCE order puts it
 *   out of reach — `sv = *(s32 *)(iv + 0x20);` before the copy.  It keeps $s0,
 *   and being source-first it also legally precedes the store block, which is
 *   what recovers the target's schedule (lw / sh / sh / lhu interleave).  This
 *   is a second, zero-side-effect defeat for §162j1 that works where its
 *   in-place-SET lever cannot: the surviving use here is a LOAD, which has no
 *   way to also SET its own base register.
 */

extern s32 rand(void);
extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_8002D4C8(s32, s32);
extern s32 func_8012C588(s32, s32);
extern u8 *func_8012913C(s32);
extern void func_8012C218(void *);
extern void func_8018D870(void *);
extern u8 D_801D1210;

void func_8018EDB8(void *arg) {
    register u8 *p __asm__("$17");   /* $s1 */
    s32 e;
    s32 i;
    s32 iv;

    p = (u8 *)arg;
    e = *(u8 *)(p + 0x5E);

    if (*(s16 *)(p + 0x60) != 0) {
        if (e == 0x1D) {
            *(u16 *)(p + 0x82) = 0;
            *(u16 *)(p + 0x7C) = *(u16 *)(p + 0x06);
            *(u16 *)(p + 0x7E) = *(u16 *)(p + 0x0A);
            *(u16 *)(p + 0x80) = *(u16 *)(p + 0x0E);
        }
        {
            s32 dec;
            s32 q = *(s32 *)(p + 0x78);
            if (q != 0 && *(s16 *)(p + 0x60) != 0) {
                dec = ((s32)*(s16 *)(p + 0x60) * (s32)*(s16 *)(q + 0x30)) >> 12;
                if (dec < 1) dec = 1;
            } else {
                dec = *(s16 *)(p + 0x60);
            }
            *(u16 *)(p + 0x76) = *(u16 *)(p + 0x76) - dec;
            ((void (*)(void *, s32))func_8016AA50)(p, dec);
        }
        if (*(u16 *)(p + 0x82) & 1) {
            ((void (*)(void *))func_8016B428)(p);
            func_80019064(&D_801D1210);
        }
    }

    if (e != 0x1D) {
        if (*(u8 *)(p + 0xC8)) func_8002A520(p);
        if (*(u8 *)(p + 0xC9)) func_8002A790(p);
    }

    if (*(s16 *)(p + 0x76) < 0) {
        i = 0;
        do {
            iv = ((s32 (*)(s32, void *))func_8012C588)(0x281, p);
            if (iv != 0) {
                *(s32 *)(iv + 0x1C) = 2;
                *(u16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                *(u16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                *(u16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            i++;
        } while (i < 8);
        i = 0;
        do {
            iv = (s32)func_8012913C(0x23);
            if (iv != 0) {
                s32 r;
                s32 sv;
                r = rand();
                *(u16 *)(iv + 0x06) = *(u16 *)(p + 0x06) + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x0A) = *(u16 *)(p + 0x0A) - (r & 0x3F) - 0x20;
                r = rand();
                sv = *(u16 *)(p + 0x0E);
                *(s32 *)(iv + 0x18) = 0;
                *(s32 *)(iv + 0x14) = 0;
                *(s32 *)(iv + 0x10) = 0;
                *(u16 *)(iv + 0x0E) = sv + (r & 0x3F) - 0x20;
                r = rand();
                *(u16 *)(iv + 0x34) = (r & 0x17FF) + 0x1800;
            }
            i++;
        } while (i < 8);

        {
        register s32 q __asm__("$4");
        s32 sv;
        iv = *(s32 *)(p + 0x64);
        sv = *(s32 *)(iv + 0x20);
        q = iv;
        *(u16 *)(q + 0x5C) = 1;
        *(u16 *)(q + 0x60) = 0;
        sv = *(u16 *)(sv + 0x12);
        *(u16 *)(q + 0x5E) = 0x1D;
        *(s32 *)(q + 0xD8) = 0;
        *(s16 *)(q + 0x76) = -0xA;
        *(u16 *)(q + 0x62) = sv - 0x800;
        func_8018D870((void *)q);
        }
        func_8012C218(p);
    } else {
        func_8002D4C8(0x9B7, 0);
        *(u16 *)(p + 0x5C) = 0x8800;
        *(u16 *)(p + 0x60) = 0;
        *(u8 *)(p + 0xC1) = 0;
        *(u8 *)(p + 0xC2) = 0x10;
    }
}


// @class: none
// @stuck: none — MATCH (397/397 ins, match_one + rtu_match).
//
// Three residuals closed this session (the prior draft sat at 15/397 and was ledgered
// "coupled ties / permuter territory"; all three turned out to be deterministic C levers):
//
// (a) `addiu $a0,$s0,0x18` x2 vs `move $a0,$s0` x2 — the matrix arg.  The target keeps the BASE
//     `&D_800AF630` in $s0 and re-adds 0x18 at BOTH call sites.  Two things block that:
//       1. cse folds `(plus (reg-holding-symbol) 24)` back into `la sym+24` (one lui/addiu).
//          Killed by making the base OPAQUE with a §21 re-tie `asm("":"=r"(mb):"0"(mb))`.
//       2. with ONE re-tie, cse then unifies the two identical `mb+0x18` into one pseudo
//          (+1 insn).  Killed by a SECOND re-tie between the calls: it mints a fresh pseudo
//          (tied to the same hard reg by the "0" constraint) so the two adds are distinct
//          expressions.  Cost: zero bytes.
//     THE RE-TIES MUST BE NON-VOLATILE.  `__volatile__` gives the asm a sched dependence on
//     every insn already emitted, which drags the `&pkt[0]` pseudo (created earlier, by the
//     struct copies) ABOVE the two jals; it then conflicts with the base, loses $s0, and needs
//     a `move` to reach the pinned $16.  Non-volatile => the pseudo sinks back after the calls
//     and both values share $s0, exactly as the target does.  (400 ins -> 397.)
//
// (b) `addiu $v0,$sp,0xA0` vs `$v1` for the &otz store — a §137 REGALLOC-PERM, solved as
//     ARITHMETIC, not by search.  Splitting otz off `pfl` is structurally required (target has
//     &flag1 in $v1 and &otz in a $v0 temp), but it drops pfl's priority and permutes
//     p1/p2/pfl through a 3-cycle (a0,v1,a1) instead of (a1,a0,v1).  From `cc1 -dl -dg`:
//         pri = floor_log2(R)*R/L*1e4   (global.c:allocno_compare)
//         p0  R=9 L=15 -> 18000     p2  R=9 L=24 -> 11250     pfl R=6 L=15 -> 8000
//     pfl must land in the WINDOW (11250, 18000) to be allocated right after p0 and take $v1.
//     Source reordering only moves L (measured: L=12 -> 10000, still short; L=9 -> 13333 works
//     but emits the addiu in the wrong place).  The lever that moves R: one zero-byte
//     `asm volatile("" :: "r"(pfl))` after the stflg — R 6->9, L 15->18 => pri 15000, inside
//     the window, and it ties p0 (15000) which breaks by allocno number in p0's favour.
//     Result: p0=$v0, pfl=$v1, p2=$a0, p1=$a1, p3=$a2 — the target's assignment exactly.
//
// (c) prologue `sw $a3,0xD4($sp)` scheduled BEFORE `lw $a0,0x20($s1)` instead of after.  This
//     is a real memory dependence, not a priority: gcc-2.7.2 true_dependence() only drops the
//     store->load edge when the LOAD is MEM_IN_STRUCT_P *and* varying while the STORE is not
//     in-struct and non-varying (the arg-home slot already qualifies).  `*(s32*)(p + 0x20)` is
//     an INDIRECT_REF of a CAST => MEM_IN_STRUCT_P is 0; `((s32*)p)[8]` is an INDIRECT_REF of a
//     PLUS_EXPR => expand_expr sets MEM_IN_STRUCT_P (idiom 2).  Second half: the old draft's
//     `asm volatile("":"=m"(dead))` frame-padding barrier re-created the same ordering through
//     itself (191 -> 16 -> 19 in the dep chain).  It is NOT needed — gcc-2.7.2 allocates a
//     stack slot for an unreferenced local anyway, so `dead[0x20]` alone holds the frame at
//     0xC8.  Both halves together, and only together, sink the store.
//
// DECLARATION SURFACE (checked with a whole-TU one-pass grep, D2):
//   * SVEC / SVECTOR / B4 / B8 are ALL already typedef'd in src/shared/engine_types.h, which
//     this TU pulls in through ../shared/engine_core.h — a local copy of any of those names is
//     a C89 redefinition error.  The four types here therefore carry the per-function suffix
//     (the same convention engine_types.h itself uses for SVECTOR_8016E7C8 / B8_8018F060), so
//     the file compiles BOTH standalone (match_one) and spliced (rtu_match).
//   * D_800AF630 is `extern u8 D_800AF630[]` at TU file scope (line 53) — same spelling here.
//   * D_800B9A02 is `short` at TU file scope (2457/2459).  Do NOT redeclare it u16; the `lhu`
//     is forced at the USE with the TU's own canonical `*(u16 *)&D_800B9A02` spelling
//     (§8d sub-class (b), the form already used at TU lines 2848 and 7416).
//   * func_8004914C / func_800491AC / RotTransSV keep the TU's file-scope prototypes verbatim.
//   * D_801D1228 / D_800A651C / D_800AE610 / func_80017254 appear nowhere else in the TU.
//   * func_8018F060 has NO caller anywhere in src/, so its signature is unconstrained.

#include "common.h"

       /* u16 source vec -> lhu */
    /* 8 bytes, align 2 */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern void func_80017254(void *a0);
extern SVEC_8018F060 D_801D1228[];
extern short D_800B9A02;
extern u8 D_800A651C[];
extern u8 D_800AE610[];
extern u8 D_800AF630[];

#define gte_ldv0(r0) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" "lwc2 $1, 4( %0 )" : : "r"( r0 ) )
#define gte_ldv3(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );" "lwc2 $1, 4( %0 );" "lwc2 $2, 0( %1 );" \
    "lwc2 $3, 4( %1 );" "lwc2 $4, 0( %2 );" "lwc2 $5, 4( %2 )" \
    : : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_stsxy(r0) __asm__ volatile ( \
    "swc2 $14, 0( %0 )" : : "r"( r0 ) : "memory" )
#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );" "swc2 $13, 0( %1 );" "swc2 $14, 0( %2 )" \
    : : "r"( r0 ), "r"( r1 ), "r"( r2 ) : "memory" )
#define gte_avsz4() __asm__ volatile ("nop;nop;avsz4")
#define gte_stotz(r0) __asm__ volatile ( \
    "swc2 $7, 0( %0 )" : : "r"( r0 ) : "memory" )
#define gte_stflg(r0) __asm__ volatile ( \
    "cfc2 $12, $31;" "nop;" "sw $12, 0( %0 )" : : "r"( r0 ) : "$12", "memory" )

#define DRAW() \
    mb = (u8 *)&D_800AF630; \
    __asm__("" : "=r"(mb) : "0"(mb)); \
    func_8004914C(mb + 0x18); \
    __asm__("" : "=r"(mb) : "0"(mb)); \
    func_800491AC(mb + 0x18); \
    pc = (long *)&pkt[0]; \
    p1 = (long *)&pkt[2]; \
    p2 = (long *)&pkt[4]; \
    p3 = (long *)&pkt[6]; \
    pfl = &flag1; \
    p0 = pc; \
    gte_ldv3(p0, p1, p2); \
    gte_rtpt(); \
    gte_stflg(pfl); \
    __asm__ __volatile__("" :: "r"(pfl)); \
    gte_stsxy3(p0, p1, p2); \
    gte_ldv0(p3); \
    gte_rtps(); \
    gte_stflg(&flag2); \
    flag1 |= flag2; \
    gte_stsxy(p3); \
    gte_avsz4(); \
    gte_stotz(&otz); \
    oz = otz; \
    *(s16 *)((u8 *)pkt + 4) = (s16)oz; \
    if (oz > 0 && flag1 >= 0 && \
        !((u32)&D_800AE610 < (u32)(*(s32 *)((u8 *)&D_800A651C \
            + (*(u16 *)&D_800B9A02) * 0x14) + oz * 4))) { \
        func_80017254(pc); \
    }

void func_8018F060(s32 param_1, u32 param_2, u16 *param_3, u32 param_4) {
    u8      dead[0x20];   /* 0x10 : reserved, never referenced (holds the frame at 0xC8) */
    SVECTOR_8018F060 scratch;      /* 0x30 */
    B8_8018F060 out[6];   /* 0x38 */
    u32     pkt[10];      /* 0x68 : v0..v3 + color(0x88) + code(0x8C) */
    SVECTOR_8018F060 rtflag;       /* 0x90 (8 bytes -> 0x94 gap) */
    s32     flag1;        /* 0x98 */
    s32     flag2;        /* 0x9C */
    s32     otz;          /* 0xA0 */
    SVEC_8018F060 *src;
    s32 i, oz;
    long *p0, *p1, *p2, *p3, *pfl;
    u8 *mb;
    register long *pc __asm__("$16");

    func_8004914C((void *)(((s32 *)param_1)[8] + 0x34));
    func_800491AC((void *)(((s32 *)param_1)[8] + 0x34));

    src = &D_801D1228[(param_2 & 1) * 3];
    for (i = 0; i < 3; i++) {
        scratch.vx = src[i].vx;
        scratch.vy = src[i].vy;
        scratch.vz = -param_3[0];
        RotTransSV(&scratch, &out[i], &rtflag);
    }
    for (i = 0; i < 3; i++) {
        scratch.vx = src[i].vx;
        scratch.vy = src[i].vy;
        scratch.vz = -param_3[1];
        RotTransSV(&scratch, &out[3 + i], &rtflag);
    }

    *(B4_8018F060 *)&pkt[8] = *(B4_8018F060 *)&param_4;
    pkt[9] = 0x50000000;

    /* face 0: verts 0,1,3,4 */
    *(B8_8018F060 *)&pkt[0] = out[0];
    *(B8_8018F060 *)&pkt[2] = out[1];
    *(B8_8018F060 *)&pkt[4] = out[3];
    *(B8_8018F060 *)&pkt[6] = out[4];
    DRAW();

    /* face 1: verts 1,2,4,5 */
    *(B8_8018F060 *)&pkt[0] = out[1];
    *(B8_8018F060 *)&pkt[2] = out[2];
    *(B8_8018F060 *)&pkt[4] = out[4];
    *(B8_8018F060 *)&pkt[6] = out[5];
    DRAW();

    /* face 2: verts 2,0,5,3 */
    *(B8_8018F060 *)&pkt[0] = out[2];
    *(B8_8018F060 *)&pkt[2] = out[0];
    *(B8_8018F060 *)&pkt[4] = out[5];
    *(B8_8018F060 *)&pkt[6] = out[3];
    DRAW();
}


// @class: other
// @stuck: none — MATCH (478 ins, relocation-masked byte-identical)

#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

#define gte_stszotz(r0) __asm__ volatile (       \
    "mfc2 $12, $19;"                             \
    "nop;"                                       \
    "sra $12, $12, 2;"                           \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stflg(r0) __asm__ volatile (         \
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )


void func_8018F694(void)
{
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern void *func_80010A08(s32);
    extern u8 D_800AF648;
    extern u8 D_800A6610[];
    extern short D_800B9A02;
    extern Blip_8018F694 D_801D57F0[];

    UVEC_8018F694 sxy;
    UVEC_8018F694 p0;
    UVEC_8018F694 p1;
    long flag;
    long otz;
    s32 i;
    PTag_8018F694 *ot;
    PTag_8018F694 *otp;
    Blip_8018F694 *bp;
    s32 t, c, d, z, x, n;

    ot = (PTag_8018F694 *)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    bp = D_801D57F0;

#define EMIT_8018F694() { \
    LineF2_8018F694 *pk = (LineF2_8018F694 *)func_80010A08(0x10); \
    pk->len = 3; \
    pk->code = 0x42; \
    pk->r0 = bp->r; \
    pk->g0 = bp->g; \
    pk->b0 = bp->b; \
    pk->x0 = p0.vx; \
    pk->y0 = p0.vy; \
    pk->x1 = p1.vx; \
    pk->y1 = p1.vy; \
    pk->addr = otp->addr; \
    otp->addr = (u32) pk; }

    for (i = 0; i < 32; i++, bp++) {
        t = bp->tm;
        __asm__ __volatile__ ("" : "=r" (t) : "0" (t));
        if (t != 0) {
            gte_ldv0(&bp->vx);
            gte_rtps();
            gte_stsxy((long *) &sxy);
            gte_stflg(&flag);
            gte_stszotz(&otz);
            if ((u16) (sxy.vx + 0x200) < 0x401 &&
                (u16) (sxy.vy + 0x180) < 0x301 &&
                (u32) (otz - 0x10) < 0x1000) {
                z = otz - 0x10;
                c = t >> 6;
                d = (t * 3) >> 8;
                otp = (PTag_8018F694 *) ((z << 2) + (s32) ot);

                p0.vx = sxy.vx - c;
                p0.vy = sxy.vy - c;
                p1.vx = p0.vx + d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy + d;
                EMIT_8018F694();

                p0.vx = sxy.vx + c;
                p1.vx = p0.vx - d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy + d;
                EMIT_8018F694();

                p0.vy = sxy.vy + c;
                p1.vx = p0.vx - d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy - d;
                EMIT_8018F694();

                p0.vx = sxy.vx - c;
                p1.vx = p0.vx + d;
                p1.vy = p0.vy;
                EMIT_8018F694();

                p1.vx = p0.vx;
                p1.vy = p0.vy - d;
                EMIT_8018F694();

                {
                    TPage_8018F694 *tp = (TPage_8018F694 *) func_80010A08(8);
                    tp->len = 1;
                    tp->code0 = 0xE100002A;
                    tp->addr = otp->addr;
                    otp->addr = (u32) tp;
                }

                n = bp->r;
                x = n - bp->dr;
                n = x;
                if (x < 0) { n = 0; }
                bp->r = n;
                n = bp->g;
                x = n - bp->dg;
                n = x;
                if (x < 0) { n = 0; }
                bp->g = n;
                n = bp->b;
                x = n - bp->db;
                n = x;
                if (x < 0) { n = 0; }
                bp->b = n;
                x = n | (bp->r | bp->g);
                if ((u8) x == 0) {
                    bp->tm = 0;
                }
            }
        }
    }
}


typedef struct { s32 a; s32 b[4]; } OtBlk_8018FE0C;

/* ==== simulated TU file-scope surface (verbatim from ov_SC06_018_jr_80187AEC.c) ==== */
extern short D_800B9A02;
extern s16 D_800B9A02;
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern void func_8004914C();
extern void func_800491AC();
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8 D_800A651C[];

void func_8018FE0C(s32 arg0, s32 arg1, s32 arg2)
{
    extern void *func_80010A08(s32);
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern s32 RotTransPers(s32, s32, s32 *, s32 *);
    extern u8 D_800AF648;
    extern OtBlk_8018FE0C aD800A651C[] __asm__("D_800A651C");
    extern u8 D_800A6518[];
    extern short D_800B9A02;
    extern void func_80016638(void *a0, s32 a1, s32 a2);

    s32 sp10;
    s32 sp14;
    s32 temp_v0_2;
    void *temp_v0;
    s32 ot;
    s32 depth4;
    register u16 *bidx __asm__("$8");
    register u32 mask1 __asm__("$7");
    register s32 rgb __asm__("$16");
    register u32 tag0 __asm__("$4");

    rgb = arg2;
    __asm__("" : "=r"(rgb) : "0"(rgb));
    temp_v0 = func_80010A08(0x10);
    *(u8 *)((u8 *)temp_v0 + 3) = 3;
    *(s32 *)((u8 *)temp_v0 + 4) = rgb;
    *(u8 *)((u8 *)temp_v0 + 7) = 0x42;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    temp_v0_2 = RotTransPers(arg0, temp_v0 + 8, &sp10, &sp14);
    if ((temp_v0_2 > 0) && (sp14 >= 0) &&
        (RotTransPers(arg1, temp_v0 + 0xC, &sp10, &sp14) > 0) && (sp14 >= 0)) {
        mask1 = 0xFFFFFF;
        bidx = (u16 *)&D_800B9A02;
        depth4 = temp_v0_2 * 4;
        tag0 = *(u32 *)temp_v0;
        *(u32 *)temp_v0 = (tag0 & 0xFF000000) |
            (*(u32 *)(depth4 + aD800A651C[*bidx].a) & mask1);
        ot = aD800A651C[*bidx].a;
        *(u32 *)(depth4 + ot) =
            (*(u32 *)(depth4 + ot) & 0xFF000000) | ((u32)temp_v0 & mask1);
        func_80016638(&D_800A6518[*bidx * 20], temp_v0_2, 1);
    }
}

