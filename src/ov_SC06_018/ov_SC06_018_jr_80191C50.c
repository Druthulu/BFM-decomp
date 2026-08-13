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
extern void func_80175414(s32 _arg0);
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
extern s32 func_8017D1CC(void);
extern void (*D_80197050[])(void);
extern void func_8017D1F0(void *a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017D26C(u8 *a0);
extern void func_800D1EBC(void);
extern void func_8017D2E8(void);
extern void (*D_8019705C[])(void);
extern void func_8017D308(void *a0);
extern M2C_UNK D_8019706C;
extern void func_8017D3E0(void);
extern void (*D_80197080[])(void);
extern void func_8017D4A0(void *a0);
extern void (*D_80197088[])(void);
extern void func_8017D8F8(void *a0);
extern s32 func_8017DC58(void);
extern void func_8017DEA4(void);
extern void (*D_8019714C[])(void);
extern void func_8017E1F0(void *a0);
extern void func_8017E420(void *a0);
extern void (*D_80197184[])(void);
extern void func_8017E49C(void *a0);
extern void func_8017E56C(void);
extern void (*D_801AAF88[])(void);
extern void func_8017F8E0(void *a0);
extern void (*D_801AAFA8[])(void);
extern void func_8017FA90(void *a0);
extern void func_8017ED60(void);
extern void func_8017FB8C(s32 *param);
extern void func_8017EB8C(s32 arg0);
extern void func_8017FD20(s32 *a0);
extern void func_8017FD54(u8 *param_1);
extern s32 D_801D55A0;
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_80180354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(void *a0);
extern s32 func_80180384(s32 param_1);
extern s32 func_801805C8(s32 param_1);
extern void (*D_801ACD5C[])(void);
extern void func_80180868(void *a0);
extern void func_80183554(void);
extern void func_80183824(void);
extern void func_8012B370(int a0);
extern void func_801839E0(void);
extern void func_80187038(void);
extern void func_80185DA8(s32 arg0);
extern void func_80189E60(s32 arg0, s32 arg1);
extern void func_80186ED4(s32 arg0);
extern void (*D_801B53F4[])(void);
extern void func_80187924(void *a0);
extern void (*D_801B554C[])(void);
extern void func_80188088(void *a0);
extern void (*D_801B5580[])(void);
extern void func_801894B4(void *a0);
extern void (*D_801B55A0[])(void);
extern void func_801899F8(void *a0);
extern void (*D_801B55AC[])(void);
extern void func_80189FCC(void *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8018A474(void *arg0);
extern void (*D_801CD4B0[])(void);
extern void func_8018B65C(void *a0);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8018B998(void *a0);
extern void func_8018C884(void);
extern void func_8018F694(void);
extern s32 func_8012BE54(s32);
extern void func_8001C214(s32, void *);
extern void func_8012A828(s32, void *);
extern s32 func_8012C658(s32, s32, s32);
extern void func_8018D40C(s32);
extern void func_8012B2CC(s32);
extern void func_8018D514(s32);
extern void func_8012B77C(void *, void *, void *);
extern void func_8002D4C8(s32, s32);
extern void func_8004914C(void*);
extern void func_800491AC(void*);
extern void RotTransSV(void *, void *, void *);
extern void func_8018FE0C(void *, void *, s32);
extern u8 D_801D16C0[];
extern u8 D_801D11B4[];
extern u8 D_801D109C[];
extern u8 D_801D11F8[];
extern u8 D_801D1220[];
extern u16 D_800B99D8;
extern void func_8019059C(s32 _arg0);
/* ==== end §8b carried decl layer ==== */

#include "common.h"

/* ============================================================================
 * func_80191C50  (ov_SC06_018 / split TU ov_SC06_018_jr_8019059C, 710 ins)
 *
 * A boss/effect state-machine tick for entity class 0x318, structurally the
 * SAME SHAPE as its already-MATCHED 673-ins sibling func_8019059C in
 * src/ov_SC06_018/ov_SC06_018_jr_8019059C.c (3-member PURE/jr family).
 * The sibling's XFER / XFERLAST / SCAN macros + register pins are reused
 * verbatim; only the per-case bodies differ.
 *
 * ---- CONTROL-FLOW MAP (from asm) ------------------------------------------
 * prologue  sp -= 0x40; save ra@0x38, s1@0x34, s0@0x30; s1 = arg0
 *           locals: sp10@0x10 sp18@0x18 sp20@0x20 sp28@0x28
 * dispatch  lhu v1,0x34(s1); sltiu v0,v1,0xC; beqz -> epilogue
 *           jtbl_801D3BA4 (12 entries, 0..0xB; entry 0 == default == return)
 *
 * case 1  @80191C90  spawn(0x318,2) -> 0xCC, copy rot.y, +0x120, st++, flag|=1<<31, FALLTHRU
 * case 2  @80191CF8  spawn(0x318,2) -> 0xD0, +0xC0,  st++, flag|=1<<31,             FALLTHRU
 * case 3  @80191D4C  spawn(0x318,2) -> 0xD4, +0x60,  st=0xA, tmr=2, RETURN
 * case 4  @80191D90  0xCC.y -= 0x30; if(--tmr<1){tmr=2; [0xAE]=0; st++}  -> TAIL
 * case 5  @80191DD8  0xCC.rot.x += 0x40; if(>=0x200) st=9;
 *                    0xD0[0xFC]-=0x40; 0xD4[0xFC]-=0x40;                 -> TAIL
 * case 6  @80191E4C  8018D40C(0xCC); XFER(CC->D0); 8018D514(D0);
 *                    XFER(D0->D4); 8018D514(D4); XFERLAST(D4);
 *                    8012B77C(sp10,&s1[4],D_80126B5C); write rot to 0x20 obj;
 *                    if((tmr&0xF)==0) [0xFC] = rand()%0x180 + 0x180;
 *                    if(--tmr) RETURN; tmr=0x10;
 *                    if(8012BE54()>0x8FFFF) RETURN;
 *                    SCAN(); tmr=0x3C; st++; 8002D4C8(0x9BB,0); RETURN
 * case 7  @80192104  if(8012BE54()>0x8FFFF){tmp=6; goto L801924AC;}
 *                    SCAN(); XFER(CC->D0); XFER(D0->D4); XFERLAST(D4);
 *                    8012B77C(...); write rot;
 *                    if(--tmr==0){ st++; [0xDC..0xE0]=D_80126B5E/62-0x38/66;
 *                                  tmr=0xF; 8002D4C8(0x9BC,0);
 *                                  8012C658(0x318,3,arg0); RETURN }
 *                    sp20 = {B5E, B62-0x38, B66};
 *                    8004914C/800491AC(obj+0x34); RotTransSV(D_801D1220,sp18,sp28);
 *                    col = (D_800B99D8&1) ? 0xE0 : 0x202080;
 *                    8018FE0C(sp18, sp20, col); RETURN
 * case 8  @80192408  if(--tmr==0) goto L801924A8; SCAN();                 -> TAIL
 * L801924A8 tmp=6
 * L801924AC  st = tmp; tmr = 0x96; RETURN     (cross-jump target of case 7)
 * case 9  @801924BC  0xCC.rot.x -= 0x40; &= 0xFFF;
 *                    if(==0){ if(--tmr==0){st=6;tmr=0x1E} else st=5; }
 *                    0xD0[0xFC]+=0x40; 0xD4[0xFC]+=0x40;                 -> TAIL
 * case 0xA @80192570 0xCC.y -= 0x30; if(--tmr<1){tmr=2; st++}
 *                    e5 = 0xD0; goto L801925F8
 * case 0xB @801925BC 0xCC.y -= 0x30; if(--tmr<1){st=4; tmr=2}; e5 = 0xCC
 * L801925F8  e5->obj.flags &= 0x7FFFFFFF;                                 -> TAIL
 *
 * TAIL @80192610  XFER(CC->D0); XFER(D0->D4); XFERLAST(D4); return
 * epilogue @80192750
 * ==========================================================================*/

extern s32 func_8012BE54(s32);
extern s32 func_8012C658(s32, s32, s32);
extern void func_8018D40C(s32);
extern void func_8012B2CC(s32);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8018D514(s32);
extern void func_8012B77C(void *, void *, void *);
extern s32 rand(void);
extern void func_8002D4C8(s32, s32);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern void RotTransSV(void *, void *, void *);
extern void func_8018FE0C(void *, void *, s32);

extern u8 D_801D11F8[];
extern u8 D_80126B5C;
extern u8 D_801202A0[];
extern u8 D_801D1220[];
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_800B99D8;

#define XFER(SRCOFF, DSTOFF)                                                                      \
    src = *(s32 *)(arg0 + SRCOFF);                                                                \
    func_8012B2CC(src);                                                                           \
    mp = D_801D11F8;                                                                              \
    __asm__ __volatile__("" : "=r"(mp) : "0"(mp));                                                \
    ((void (*)(s32, void *, void *))func_8012F14C)(*(s32 *)(src + 0x20) + 0x34, mp, sp10);        \
    dst = *(s32 *)(arg0 + DSTOFF);                                                                \
    *(u16 *)(dst + 6) = sp10[0];                                                                  \
    *(u16 *)(dst + 0xA) = sp10[1];                                                                \
    *(u16 *)(dst + 0xE) = sp10[2];                                                                \
    *(u16 *)(*(s32 *)(dst + 0x20) + 0x10) =                                                       \
        *(u16 *)(dst + 0xFC) + *(u16 *)(*(s32 *)(src + 0x20) + 0x10);                             \
    *(u16 *)(*(s32 *)(dst + 0x20) + 0x12) =                                                       \
        *(u16 *)(dst + 0xFE) + *(u16 *)(*(s32 *)(src + 0x20) + 0x12);

#define XFERLAST(SRCOFF)                                                                          \
    src = *(s32 *)(arg0 + SRCOFF);                                                                \
    func_8012B2CC(src);                                                                           \
    mp = D_801D11F8;                                                                              \
    __asm__ __volatile__("" : "=r"(mp) : "0"(mp));                                                \
    ((void (*)(s32, void *, void *))func_8012F14C)(*(s32 *)(src + 0x20) + 0x34, mp, sp10);        \
    *(u16 *)(arg0 + 6) = sp10[0];                                                                 \
    *(u16 *)(arg0 + 0xA) = sp10[1];                                                               \
    *(u16 *)(arg0 + 0xE) = sp10[2];

#define SCAN()                                                                                    \
    p = (u8 *)D_801202A0;                                                                         \
    i = 0;                                                                                        \
    do {                                                                                          \
        if (*(u16 *)p == 0x318 && p != (u8 *)arg0 &&                                              \
            (*(s16 *)(p + 0x70) == 0 || *(s16 *)(p + 0x70) == 6) &&                               \
            *(u16 *)(p + 0x34) == 6 && *(s32 *)(p + 0x1C) < 0x11) {                               \
            *(s32 *)(p + 0x1C) = *(s32 *)(p + 0x1C) + 0x10;                                       \
        }                                                                                         \
        p += 0x10C;                                                                               \
        i += 1;                                                                                   \
    } while (i < 0x60);

void func_80191C50(s32 _arg0) {
    register s32 arg0 __asm__("$17");
    register s32 src __asm__("$16");
    register s32 dst __asm__("$3");
    register s32 tmp __asm__("$2");
    register s32 e5 __asm__("$4");
    s32 r;
    s32 cnt;
    s32 col;
    s32 sv;
    s32 sw2;
    u8 *p;
    s32 i;
    u8 *mp;
    u8 *mm;
    u16 *m18;
    u16 *m18b;
    u16 sp10[4];
    u16 sp18[4];
    s16 sp20[4];
    u16 sp28[4];

    arg0 = _arg0;
    switch (*(u16 *)(arg0 + 0x34)) {
    case 1:
        r = func_8012C658(0x318, 2, arg0);
        if (r == 0) {
            return;
        }
        *(u16 *)(*(s32 *)(r + 0x20) + 0x12) = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
        *(u16 *)(r + 0xA) = *(u16 *)(r + 0xA) + 0x120;
        *(s32 *)(arg0 + 0xCC) = r;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        *(s32 *)(*(s32 *)(r + 0x20) + 4) = *(s32 *)(*(s32 *)(r + 0x20) + 4) | 0x80000000;
        /* fallthrough */
    case 2:
        r = func_8012C658(0x318, 2, arg0);
        if (r == 0) {
            return;
        }
        *(u16 *)(r + 0xA) = *(u16 *)(r + 0xA) + 0xC0;
        *(s32 *)(arg0 + 0xD0) = r;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        *(s32 *)(*(s32 *)(r + 0x20) + 4) = *(s32 *)(*(s32 *)(r + 0x20) + 4) | 0x80000000;
        /* fallthrough */
    case 3:
        r = func_8012C658(0x318, 2, arg0);
        if (r == 0) {
            return;
        }
        *(u16 *)(r + 0xA) = *(u16 *)(r + 0xA) + 0x60;
        *(u16 *)(arg0 + 0x34) = 0xA;
        *(s32 *)(arg0 + 0xD4) = r;
        *(s32 *)(arg0 + 0x1C) = 2;
        return;
    case 4:
        e5 = *(s32 *)(arg0 + 0xCC);
        *(u16 *)(e5 + 0xA) = *(u16 *)(e5 + 0xA) - 0x30;
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt < 1) {
            *(s32 *)(arg0 + 0x1C) = 2;
            *(u16 *)(arg0 + 0xAE) = 0;
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        }
        break;
    case 5:
        e5 = *(s32 *)(arg0 + 0xCC);
        *(u16 *)(*(s32 *)(e5 + 0x20) + 0x10) = *(u16 *)(*(s32 *)(e5 + 0x20) + 0x10) + 0x40;
        if (*(s16 *)(*(s32 *)(e5 + 0x20) + 0x10) >= 0x200) {
            *(u16 *)(arg0 + 0x34) = 9;
        }
        e5 = *(s32 *)(arg0 + 0xD0);
        *(u16 *)(e5 + 0xFC) = *(u16 *)(e5 + 0xFC) - 0x40;
        e5 = *(s32 *)(arg0 + 0xD4);
        *(u16 *)(e5 + 0xFC) = *(u16 *)(e5 + 0xFC) - 0x40;
        break;
    case 6:
        func_8018D40C(*(s32 *)(arg0 + 0xCC));
        XFER(0xCC, 0xD0)
        func_8018D514(*(s32 *)(arg0 + 0xD0));
        XFER(0xD0, 0xD4)
        func_8018D514(*(s32 *)(arg0 + 0xD4));
        XFERLAST(0xD4)
        func_8012B77C(sp10, (void *)(arg0 + 4), ((u8 *)&D_80126B5C));
        tmp = *(s32 *)sp10;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x10) = tmp;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = tmp >> 16;
        if ((*(s32 *)(arg0 + 0x1C) & 0xF) == 0) {
            *(u16 *)(arg0 + 0xFC) = rand() % 0x180 + 0x180;
        }
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt != 0) {
            return;
        }
        *(s32 *)(arg0 + 0x1C) = 0x10;
        if (func_8012BE54(arg0) > 0x8FFFF) {
            return;
        }
        SCAN()
        *(s32 *)(arg0 + 0x1C) = 0x3C;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        func_8002D4C8(0x9BB, 0);
        return;
    case 7:
        if (func_8012BE54(arg0) > 0x8FFFF) {
            tmp = 6;
            goto L801924AC;
        }
        SCAN()
        XFER(0xCC, 0xD0)
        XFER(0xD0, 0xD4)
        XFERLAST(0xD4)
        func_8012B77C(sp10, (void *)(arg0 + 4), ((u8 *)&D_80126B5C));
        tmp = *(s32 *)sp10;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x10) = tmp;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = tmp >> 16;
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt == 0) {
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            *(u16 *)(arg0 + 0xDC) = D_80126B5E;
            tmp = D_80126B62 - 0x38;
            *(u16 *)(arg0 + 0xDE) = tmp;
            dst = D_80126B66;
            tmp = 0xF;
            *(s32 *)(arg0 + 0x1C) = tmp;
            *(u16 *)(arg0 + 0xE0) = dst;
            func_8002D4C8(0x9BC, 0);
            func_8012C658(0x318, 3, arg0);
            return;
        }
        sv = D_80126B5E;
        sw2 = D_80126B66;
        sp20[0] = sv;
        sp20[2] = sw2;
        sv = D_80126B62 - 0x38;
        sp20[1] = sv;
        ((void (*)(s32))func_8004914C)(*(s32 *)(arg0 + 0x20) + 0x34);
        ((void (*)(s32))func_800491AC)(*(s32 *)(arg0 + 0x20) + 0x34);
        mm = D_801D1220;
        __asm__ __volatile__("" : "=r"(mm) : "0"(mm));
        m18 = sp18;
        __asm__ __volatile__("" : "=r"(m18) : "0"(m18));
        RotTransSV(mm, m18, sp28);
        col = 0x202080;
        if ((D_800B99D8 & 1) != 0) {
            col = 0xE0;
        }
        m18b = sp18;
        __asm__ __volatile__("" : "=r"(m18b) : "0"(m18b));
        func_8018FE0C(m18b, sp20, col);
        return;
    case 8:
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt == 0) {
            goto L801924A8;
        }
        SCAN()
        break;
    L801924A8:
        tmp = 6;
    L801924AC:
        *(u16 *)(arg0 + 0x34) = tmp;
        *(s32 *)(arg0 + 0x1C) = 0x96;
        return;
    case 9:
        e5 = *(s32 *)(arg0 + 0xCC);
        *(u16 *)(*(s32 *)(e5 + 0x20) + 0x10) = *(u16 *)(*(s32 *)(e5 + 0x20) + 0x10) - 0x40;
        *(u16 *)(*(s32 *)(e5 + 0x20) + 0x10) = *(u16 *)(*(s32 *)(e5 + 0x20) + 0x10) & 0xFFF;
        if (*(s16 *)(*(s32 *)(e5 + 0x20) + 0x10) == 0) {
            cnt = *(s32 *)(arg0 + 0x1C) - 1;
            *(s32 *)(arg0 + 0x1C) = cnt;
            if (cnt != 0) {
                *(u16 *)(arg0 + 0x34) = 5;
            } else {
                *(u16 *)(arg0 + 0x34) = 6;
                *(s32 *)(arg0 + 0x1C) = 0x1E;
            }
        }
        e5 = *(s32 *)(arg0 + 0xD0);
        *(u16 *)(e5 + 0xFC) = *(u16 *)(e5 + 0xFC) + 0x40;
        e5 = *(s32 *)(arg0 + 0xD4);
        *(u16 *)(e5 + 0xFC) = *(u16 *)(e5 + 0xFC) + 0x40;
        break;
    case 0xA:
        e5 = *(s32 *)(arg0 + 0xCC);
        *(u16 *)(e5 + 0xA) = *(u16 *)(e5 + 0xA) - 0x30;
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt < 1) {
            *(s32 *)(arg0 + 0x1C) = 2;
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        }
        e5 = *(s32 *)(arg0 + 0xD0);
        goto L801925F8;
    case 0xB:
        e5 = *(s32 *)(arg0 + 0xCC);
        *(u16 *)(e5 + 0xA) = *(u16 *)(e5 + 0xA) - 0x30;
        cnt = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = cnt;
        if (cnt < 1) {
            *(u16 *)(arg0 + 0x34) = 4;
            *(s32 *)(arg0 + 0x1C) = 2;
        }
    L801925F8:
        *(s32 *)(*(s32 *)(e5 + 0x20) + 4) = *(s32 *)(*(s32 *)(e5 + 0x20) + 4) & 0x7FFFFFFF;
        break;
    case 0:
    default:
        return;
    }

    XFER(0xCC, 0xD0)
    XFER(0xD0, 0xD4)
    XFERLAST(0xD4)
}

#include "common.h"

/* func_80192768 — ov_SC06_018 / ov_SC06_018_jr_80191C50   (254 ins)
 *
 * Boss "defeat / finale" tick for the 0x318-class entity driven by the
 * already-MATCHED TU neighbours func_80191C50 and func_80192F64.
 *
 *   state 0  : arm the 0x1E-frame timer, st++
 *   state 1  : every frame spawn a 0x23 spark (func_8012913C) at a random
 *              offset around the boss and play 0xAD7; when the timer runs
 *              out, st++ and release the +0xCC child (flag |= 1, y-vel,
 *              anim 2), then clear +0xCC.
 *   state 2  : if the owner (+0x6C)[0xF4] is set -> the big finale: sound
 *              0xAD6, three func_8012C658 props (0x33/3, 0x33/2, 0x32/2),
 *              eight func_8012C588(0x281) debris with rand()-driven pos/vel,
 *              func_8002A04C(self), stamp the owner's +0xCC child, then
 *              free the owner and self.
 *              otherwise: reload the 0x20 display record from D_801D233C
 *              preserving its +0x12 yaw, set +0xAE = -1, st++.
 *   always   : tail-call ((void (*)(s32))func_8018D654)(self).
 *
 * @class: none — MATCH (254 ins), iteration 6.
 *
 * @lever (NEW, generalizable — fold's split_tree REASSOCIATION and how to
 *   defeat it):  `(x - K) - r`  and  `x - (r + K)` are the SAME source-level
 *   value but NOT the same codegen, and gcc-2.7.2 canonicalises BOTH into
 *   `x - (r + K)` — `fold-const.c:3736` "EXPR is (VAR+CON) +- ARG1 ...
 *   otherwise return VAR +- (ARG1 +- CON)", reached through `split_tree`
 *   (`fold-const.c:882`).  The target here wants the UN-reassociated
 *   `(x - K) - r`  (`lhu; addiu -K; ...; subu rem`).  Neither operand order
 *   produces it — they are mutual inverses and both land on `x - (r + K)`.
 *   THE LEVER: `split_tree` only strips conversions that DO NOT CHANGE THE
 *   MACHINE MODE (`fold-const.c:891`), so wrapping the inner subtraction in a
 *   HImode cast — `(u16)(*(u16 *)(e + 6) - 0x30) - rand() % 320` — leaves a
 *   NOP_EXPR at the top, `split_tree` returns 0, and the reassociation is
 *   skipped.  The zero-extend costs nothing: the value is consumed by an `sh`,
 *   so combine's `force_to_mode` drops it.  A/B-verified against 6 spellings.
 *
 * @lever (store order is pinned by MAY-ALIAS, not by taste): the three
 *   `*(s32 *)(e + 0x10/0x14/0x18) = 0` stores must come AFTER the
 *   `*(u16 *)(e + 0xE) = *(u16 *)(arg0 + 0xE) - 0x28` load in source.  A load
 *   off `$s1` and a store off `$s0` cannot be disambiguated by
 *   `memrefs_conflict_p` (different base regs), so sched cannot lift the `lhu`
 *   over them — writing the zeros first pushed the `lhu 0xE` down, cost the
 *   3 fillers of its load-delay and emitted a `nop` (+1 ins).  Two stores off
 *   the SAME base with different constant offsets ARE disambiguated, which is
 *   why the `sh 0xE` still floats down into the `jal rand` delay slot.
 *
 * @lever (§76 allocno CLASS): the three `func_8012C658` results and the
 *   `func_8012C588` loop result are DIFFERENT variables (`p` vs `e`).  Merged
 *   into one, the live range spans the rand()-loop, `calls_crossed > 0` forces
 *   callee-saved and all four land in $s0; split, `p` is call-crossing-free
 *   and lands in $a0 (first free in REG_ALLOC_ORDER) as the target has it.
 *
 * @lever (the +0xCC child is loaded TWICE in source): the target spends an
 *   extra `addu $s0, $v0, $zero` in the `beqz` delay slot — i.e. it tests the
 *   raw load in $v0 and copies it into the loop's `e` ($s0).  `e = *(...);
 *   if (e != 0)` loads straight into $s0 (-1 ins).  Testing the EXPRESSION and
 *   re-reading it inside the guard gives CSE a copy insn, which is the target.
 *
 * @lever (negative constants through a u16 lvalue): `*(u16 *)(x) = -3` emits
 *   `ori $v0,$zero,0xFFFD` (the constant is converted to u16 FIRST); the
 *   target's `addiu $v0,$zero,-0x3` needs an `s16` lvalue.  Five stores here.
 *
 * @lever (§162 cross-jump, the `minimum=1` fall-through path): the +0x76
 *   select is an IF/ELSE WITH TWO `sh` STORES, not a ternary.  Both spellings
 *   give the same 6 instructions, but the ternary keeps one live value across
 *   the join, so the `2` for +0x5E overlaps it and takes $v1; written as two
 *   stores, cross_jump merges the 1-insn `sh` tail (`jump.c:1978`, one side
 *   falls through so a 1-insn suffix is enough) and the value serially reuses
 *   $v0 — which is the only thing that keeps `addiu $v0,$zero,0x2` BELOW
 *   `sh $v0,0x76($s0)`, by anti-dependency.  4 mismatches -> MATCH.
 *
 * @lever (the shared `st++` tail is COMPILER tail-merge, write it longhand):
 *   `.L80192B34` is a 2-insn `addiu/sh` block entered by a forward `j` from
 *   case 0 and by fall-through from case 2's else arm, with the `lhu 0x34`
 *   DUPLICATED in each predecessor.  sched2 runs BEFORE the cross-jump pass
 *   (`toplev.c:3104` vs `:3140`), so each arm's `lhu` is scheduled up into its
 *   own block first and only the 2-insn suffix survives the merge.  Writing
 *   the increment once at a shared label would have put the `lhu` in the
 *   merged block and cost a `nop`.
 */

extern u8 *func_8012913C(s32);
extern s32 rand(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8001C214(s32 a0, void *a1);
extern void func_8018D654();
extern u8 D_801D233C[];

void func_80192768(s32 arg0) {
    s32 e;
    s32 p;
    s32 i;
    s32 t;

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        *(s32 *)(arg0 + 0x1C) = 0x1E;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        goto end;
    case 1:
        *(u8 *)(arg0 + 0xC2) = 0xA;
        e = ((s32 (*)(s32))func_8012913C)(0x23);
        if (e != 0) {
            *(u16 *)(e + 6) = *(u16 *)(arg0 + 6) - rand() % 224 + 0x10;
            *(u16 *)(e + 0xA) = *(u16 *)(arg0 + 0xA) - rand() % 320;
            *(u16 *)(e + 0xE) = *(u16 *)(arg0 + 0xE) - 0x28;
            *(s32 *)(e + 0x18) = 0;
            *(s32 *)(e + 0x14) = 0;
            *(s32 *)(e + 0x10) = 0;
            *(u16 *)(e + 0x34) = (rand() & 0x17FF) + 0x1800;
            func_8002D4C8(0xAD7, 0);
        }
        t = *(s32 *)(arg0 + 0x1C) - 1;
        *(s32 *)(arg0 + 0x1C) = t;
        if (t == 0) {
            e = *(s32 *)(arg0 + 0xCC);
            *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
            if (e != 0) {
                *(u16 *)(e + 0x5C) = *(u16 *)(e + 0x5C) | 1;
                if (*(s32 *)(*(s32 *)(arg0 + 0x6C) + 0xF4) == 0) {
                    *(s16 *)(e + 0x76) = -0x1F4;
                } else {
                    *(s16 *)(e + 0x76) = -0x3E8;
                }
                *(u16 *)(e + 0x5E) = 2;
                *(s32 *)(arg0 + 0xCC) = 0;
            }
        }
        goto end;
    case 2:
        if (*(s32 *)(*(s32 *)(arg0 + 0x6C) + 0xF4) != 0) {
            func_8002D4C8(0xAD6, 0);
            p = func_8012C658(0x33, 3, arg0);
            if (p != 0) {
                *(s16 *)(p + 0x12) = -3;
                *(s16 *)(p + 0x16) = -0x10;
                *(s16 *)(p + 0x1A) = -4;
                *(u16 *)(p + 6) = *(u16 *)(p + 6) - 0x140;
            }
            p = func_8012C658(0x33, 2, arg0);
            if (p != 0) {
                *(u16 *)(p + 0x12) = 3;
                *(s16 *)(p + 0x16) = -0x10;
                *(s16 *)(p + 0x1A) = -4;
                *(u16 *)(p + 6) = *(u16 *)(p + 6) - 0x140;
            }
            p = func_8012C658(0x32, 2, arg0);
            if (p != 0) {
                *(u16 *)(p + 0x12) = 0;
                *(s16 *)(p + 0x16) = -0x10;
                *(s16 *)(p + 0x1A) = -4;
                *(u16 *)(p + 6) = *(u16 *)(p + 6) - 0x140;
            }
            i = 0;
            do {
                e = func_8012C588(0x281, arg0);
                if (e != 0) {
                    *(s32 *)(e + 0x1C) = 2;
                    *(u16 *)(e + 6) = (u16)(*(u16 *)(e + 6) - 0x30) - rand() % 320;
                    *(u16 *)(e + 0xA) = (u16)(*(u16 *)(e + 0xA) - 0x20) - rand() % 256;
                    *(u16 *)(e + 0x12) = (rand() & 0x1F) - 0x10;
                    *(u16 *)(e + 0x16) = -((rand() & 0xF) + 0x10);
                    *(u16 *)(e + 0x1A) = (rand() & 0x1F) - 0x10;
                }
                i += 1;
            } while (i < 8);
            func_8002A04C(arg0);
            if (*(s32 *)(*(s32 *)(arg0 + 0x6C) + 0xCC) != 0) {
                e = *(s32 *)(*(s32 *)(arg0 + 0x6C) + 0xCC);
                *(s16 *)(e + 0x76) = -0x3E8;
                *(u16 *)(e + 0x5E) = 2;
                *(u16 *)(e + 0x5C) = *(u16 *)(e + 0x5C) | 1;
            }
            func_8012C218(*(void **)(arg0 + 0x6C));
            func_8012C218((void *)arg0);
            goto end;
        }
        i = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
        func_8001C214(*(s32 *)(arg0 + 0x20), D_801D233C);
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = i;
        *(s16 *)(arg0 + 0xAE) = -1;
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        goto end;
    default:
        goto end;
    }
end:
    ((void (*)(s32))func_8018D654)(arg0);
}


#include "common.h"

/* func_80192B60 — ov_SC06_018 / TU ov_SC06_018_jr_80191C50   (257 ins)
 *
 * A 3-state boss-death / effect tick.  Same actor family as its already-MATCHED
 * TU neighbours func_80191C50 (:2880) and func_80192F64 (:3167); the spawn
 * idioms are lifted verbatim from the byte-proven siblings
 *   func_8018E188  (src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c:5255)  — the $s1
 *                  arg pin, the 0x281 particle burst, the 0x23 debris spawn;
 *   func_80180CA8  (src/ov_SC06_008/ov_SC06_008_jr_8017C294.c:4742)  — the
 *                  triple func_8012C658 spawn + func_8002A04C/func_8012C218 tail.
 *
 * state 0 : arm the 0x1E countdown, st++
 * state 1 : one 0x23 debris spawn scattered around self + sound 0xAD7; when the
 *           countdown hits 0, st++ and slam the +0xCC child (-1000 or -500 into
 *           +0x76 depending on the +0x64 owner's +0xF4 flag), then drop it.
 * state 2 : if the owner's +0xF4 flag is set -> the full death burst (sound
 *           0xAD6, three func_8012C658 attachments, an 8x 0x281 particle burst,
 *           func_8002A04C, slam the owner's +0xCC child, free owner + self);
 *           else swap in the D_801D233C/D_801D11F0 animation pair (preserving
 *           the object's rot.y), set +0xAE = -1 and st++.
 * always  : tail func_8018D654(self).
 *
 * @class: none — MATCH (257 ins), iteration 6.
 *
 * @lever (§162 cross-jump direction as a source-shape oracle):  the -1000/-500
 *   select is NOT a temp.  A temp (`t = -1000; if (!flag) t = -500;`) is live
 *   from before the +0xF4 load, so it CONFLICTS with the load's allocno, is
 *   pushed to $v1, and that in turn lets sched2 hoist `lhu 0x5C` above
 *   `sh 0x76` (+4 wrong ins).  Writing BOTH arms as full stores lets the final
 *   jump pass cross-jump the identical tails (sh 0x76 downwards), which is what
 *   puts the constant in the branch delay slot AND lets the value share $v0
 *   with the flag it was tested from.  (`t` reused as the flag variable itself
 *   also matches — same allocno, same reason.)
 *
 * @lever (fold's PLUS/MINUS re-association is source-form INVARIANT):  five
 *   spellings of `x + 0x30 + rand()%0x140` (parenthesised, operands swapped,
 *   constant folded into either side) all emit `x + (r%0x140 + 0x30)` — fold
 *   canonicalises before expand, so re-ordering the operands is USELESS here.
 *   The target's `(x + 0x30) + r%0x140` only appears once the constant add is
 *   its OWN statement on its OWN temp, which requires the rand() result to be
 *   hoisted into a temp first (otherwise the `lhu` lands before the `jal`, and
 *   a load can never be scheduled back across a call).  Same for the -0x20.
 *
 * @lever (§76 allocno CLASS):  the three func_8012C658 results and the
 *   0x281/0x23/+0xCC pointers must be DIFFERENT locals.  `e` never crosses a
 *   call -> $a0 (first free in REG_ALLOC_ORDER); `iv` spans the rand() calls in
 *   the burst loop -> calls_crossed > 0 -> the callee-saved $s0 that every other
 *   use of it then coalesces onto.  One shared variable puts all of them in $s0.
 *
 * @lever (the second +0xCC child is loaded TWICE):  `iv = load; if (iv)` emits
 *   `lw $s0` directly; the target tests the load and re-reads it inside the arm,
 *   so CSE leaves a live `addu $s0, $v0, $zero` that fills the beqz delay slot
 *   (+1 ins — this was the entire length drift).
 */

extern s32 rand(void);
extern u8 *func_8012913C(s32);
extern void func_8002D4C8(s32, s32);
extern s32 func_8012C658(s32, s32, s32);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8001C214(s32, void *);
extern void func_8012A828(s32, void *);
extern void func_8018D654();

extern u8 D_801D233C[];
extern u8 D_801D11F0[];

void func_80192B60(void *arg) {
    register u8 *p __asm__("$17");
    s32 e;
    s32 iv;
    s32 i;

    p = (u8 *)arg;

    switch (*(u16 *)(p + 0x34)) {
    case 0:
        *(s32 *)(p + 0x1C) = 0x1E;
        *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
        break;

    case 1:
        *(u8 *)(p + 0xC2) = 0xA;
        iv = (s32)func_8012913C(0x23);
        if (iv != 0) {
            *(u16 *)(iv + 0x06) = *(u16 *)(p + 0x06) + rand() % 0xE0 + 0x10;
            *(u16 *)(iv + 0x0A) = *(u16 *)(p + 0x0A) - rand() % 0x140;
            {
                s32 sv = *(u16 *)(p + 0x0E);
                *(s32 *)(iv + 0x18) = 0;
                *(s32 *)(iv + 0x14) = 0;
                *(s32 *)(iv + 0x10) = 0;
                *(u16 *)(iv + 0x0E) = sv - 0x28;
            }
            *(u16 *)(iv + 0x34) = (rand() & 0x17FF) + 0x1800;
            func_8002D4C8(0xAD7, 0);
        }
        *(s32 *)(p + 0x1C) = *(s32 *)(p + 0x1C) - 1;
        if (*(s32 *)(p + 0x1C) == 0) {
            iv = *(s32 *)(p + 0xCC);
            *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
            if (iv != 0) {
                if (*(s32 *)(*(s32 *)(p + 0x64) + 0xF4) != 0) {
                    *(s16 *)(iv + 0x76) = -1000;
                } else {
                    *(s16 *)(iv + 0x76) = -500;
                }
                *(u16 *)(iv + 0x5E) = 2;
                *(u16 *)(iv + 0x5C) = *(u16 *)(iv + 0x5C) | 1;
                *(s32 *)(p + 0xCC) = 0;
            }
        }
        break;

    case 2:
        if (*(s32 *)(*(s32 *)(p + 0x64) + 0xF4) != 0) {
            func_8002D4C8(0xAD6, 0);

            e = func_8012C658(0x33, 3, (s32)p);
            if (e != 0) {
                *(s16 *)(e + 0x12) = -3;
                *(s16 *)(e + 0x16) = -0x10;
                *(s16 *)(e + 0x1A) = -4;
                *(u16 *)(e + 0x06) = *(u16 *)(e + 0x06) + 0x140;
            }
            e = func_8012C658(0x33, 2, (s32)p);
            if (e != 0) {
                *(s16 *)(e + 0x12) = 3;
                *(s16 *)(e + 0x16) = -0x10;
                *(s16 *)(e + 0x1A) = -4;
                *(u16 *)(e + 0x06) = *(u16 *)(e + 0x06) + 0x140;
            }
            e = func_8012C658(0x32, 2, (s32)p);
            if (e != 0) {
                *(s16 *)(e + 0x12) = 0;
                *(s16 *)(e + 0x16) = -0x10;
                *(s16 *)(e + 0x1A) = -4;
                *(u16 *)(e + 0x06) = *(u16 *)(e + 0x06) + 0x140;
            }

            i = 0;
            do {
                iv = func_8012C588(0x281, (s32)p);
                if (iv != 0) {
                    *(s32 *)(iv + 0x1C) = 2;
                    {
                        s32 rr = rand();
                        s32 xx = *(u16 *)(iv + 0x06) + 0x30;
                        *(u16 *)(iv + 0x06) = xx + rr % 0x140;
                    }
                    {
                        s32 rr = rand();
                        s32 yy = *(u16 *)(iv + 0x0A) - 0x20;
                        *(u16 *)(iv + 0x0A) = yy - rr % 0x100;
                    }
                    *(u16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                    *(u16 *)(iv + 0x16) = -((rand() & 0xF) + 0x10);
                    *(u16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
                }
                i++;
            } while (i < 8);

            func_8002A04C((s32)p);
            if (*(s32 *)(*(s32 *)(p + 0x64) + 0xCC) != 0) {
                iv = *(s32 *)(*(s32 *)(p + 0x64) + 0xCC);
                *(s16 *)(iv + 0x76) = -1000;
                *(u16 *)(iv + 0x5E) = 2;
                *(u16 *)(iv + 0x5C) = *(u16 *)(iv + 0x5C) | 1;
            }
            func_8012C218(*(void **)(p + 0x64));
            func_8012C218(p);
            break;
        }
        i = *(s16 *)(*(s32 *)(p + 0x20) + 0x12);
        func_8001C214(*(s32 *)(p + 0x20), D_801D233C);
        func_8012A828((s32)p, D_801D11F0);
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) = i;
        *(s16 *)(p + 0xAE) = -1;
        *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
        break;
    }

    func_8018D654(p);
}


#include "common.h"

/* func_80192F64 — ov_SC06_018 / ov_SC06_018_jr_80191C50   (226 ins)
 *
 * A "sweeping beam" tick for the 0x318 boss-effect entity family — the same
 * entity class its already-MATCHED TU neighbour func_80191C50 drives
 * (src/ov_SC06_018/ov_SC06_018_jr_80191C50.c:2860).
 *
 *   - 3-way state machine on +0x34:
 *       0 = spawn the child (func_8012C658(0x318, 8, arg0)) -> +0xCC,
 *       1 = sweep -Z until 0x8C-z >= 0xFC, then state 2,
 *       2 = sweep +Z until z-0x8C >= 0xFC, then state 1.
 *   - then, if the child (+0xCC) exists: two func_8018F060 draws (colours
 *     0x81818 / 0x204040), and TWO substep-interpolated hit sweeps that walk
 *     the beam origin backwards by `d` once per substep:
 *       (a) over the 0x60-entry entity table D_801202A0 (stride 0x10C),
 *           hit-testing each live entity with func_80135260 and, on a hit,
 *           stamping state 0x1D / timer 0xA / flag 1 / +0x62 = yaw-0x800;
 *       (b) against the player with func_8012DF34, stamping D_80126B98.
 *
 * @class: none — MATCH (226 ins), iteration 3.
 *
 * @lever (NEW, generalizable — loop.c `combine_givs` ANCHOR RULE):
 *   Iterations 1-2 were LENGTH-DRIFT +5 / +2 with an EXTRA induction register.
 *   All of the entity-record accesses (+0x20 +0x58 +0x5C +0x5E +0x60 +0x62
 *   +0xAE) are DEST_ADDR givs on the table pointer, and gcc-2.7.2 allocates
 *   ONE new pseudo for the combined group.  Which offset the group is
 *   ANCHORED at is not free: `record_giv` PREPENDS to `bl->giv`, and
 *   `combine_givs` walks that list from the head taking the first absorber —
 *   so the anchor is the **LAST address giv discovered in source order**.
 *   The target anchors at +0x5E (base $s3, giv $s0, offsets -0x3E..+0x50);
 *   my draft anchored at +0x62 because `*(u16*)(e+0x62) = ...` was the last
 *   store in the hit block, which forced a THIRD induction register (+$s7,
 *   +2 prologue/epilogue insns, +1 giv-init, +1 latch increment, +1 nop).
 *   FIX: reorder the hit block so the **+0x5E store is last** — pure source
 *   ordering, zero semantic change, and the scheduler still emits +0x62 last
 *   in the asm because it depends on a lw->lhu chain.
 *
 * @lever (§76 allocno CLASS): the spawn result, the +0xCC child pointer and
 *   the D_801202A0 table walker are ONE variable `e`.  Split into separate
 *   variables the first two are local, call-crossing-free allocnos and land
 *   in $a0 (first free in REG_ALLOC_ORDER); merged, the live range spans the
 *   func_80135260 loop, so calls_crossed > 0 forces a callee-saved reg and
 *   the whole chain coalesces onto $s3 — which is also what frees the
 *   `bnez $s3` delay slot for `addu $a0, $s2, $zero`.
 *
 * @lever (store order): `sp10.vy = sp18.vy = v` (not `sp18.vy = sp10.vy = v`)
 *   — `a = b = v` stores b first, and the target emits sh 0x1A before 0x12.
 */

extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012B2CC(s32 a0);
extern void func_8018F060(s32 param_1, u32 param_2, u16 *param_3, u32 param_4);
extern s32 func_8004787C(s32 a0);
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
extern s32 func_8012DF34(s32 a0, s32 a1, s32 a2);
extern u8 D_801202A0[];
extern u16 D_80126B98[];

typedef struct {
    s16 vx, vy, vz, pad;
} SV_80192F64;

void func_80192F64(s32 arg0) {
    s32 e;
    s16 t;
    s32 i;
    s32 n;
    s32 d;
    SV_80192F64 sp10;
    SV_80192F64 sp18;
    SV_80192F64 sp20;
    u16 sp28[2];

    switch (*(u16 *)(arg0 + 0x34)) {
    case 0:
        e = func_8012C658(0x318, 8, arg0);
        if (e != 0) {
            *(u16 *)(arg0 + 0x34) = (*(u16 *)(arg0 + 0xFC) & 1) + 1;
            *(u16 *)(*(s32 *)(e + 0x20) + 0x12) = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) + 0x800;
            *(s32 *)(e + 4) = *(s32 *)(e + 4) - *(s32 *)(arg0 + 0xDC);
            *(s32 *)(arg0 + 0xCC) = e;
            *(u16 *)(e + 0xFC) = *(u16 *)(arg0 + 0x36);
        }
        break;
    case 1:
        t = *(u16 *)(arg0 + 0xE) - 4;
        *(u16 *)(arg0 + 0xE) = t;
        if (*(s16 *)(arg0 + 0x8C) - t >= *(s16 *)(arg0 + 0xFC)) {
            *(u16 *)(arg0 + 0x34) = 2;
        }
        break;
    case 2:
        t = *(u16 *)(arg0 + 0xE) + 4;
        *(u16 *)(arg0 + 0xE) = t;
        if (t - *(s16 *)(arg0 + 0x8C) >= *(s16 *)(arg0 + 0xFC)) {
            *(u16 *)(arg0 + 0x34) = 1;
        }
        break;
    }

    e = *(s32 *)(arg0 + 0xCC);
    if (e == 0) {
        *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
        return;
    }
    *(s32 *)(e + 0xC) = *(s32 *)(arg0 + 0xC);
    sp28[0] = 0;
    sp28[1] = *(u16 *)(arg0 + 0xDE);
    func_8012B2CC(arg0);
    func_8018F060(arg0, 0, sp28, 0x81818);
    func_8018F060(arg0, 1, sp28, 0x204040);

    sp10.vx = *(u16 *)(arg0 + 6);
    sp10.vy = sp18.vy = *(u16 *)(arg0 + 0xA);
    sp10.vz = sp18.vz = *(u16 *)(arg0 + 0xE);
    e = (s32)D_801202A0;
    i = 0;
    d = func_8004787C(*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12)) >> 4;
    do {
        if (*(u16 *)e != 0 && *(u16 *)e != 0x25D && *(u16 *)e != 0x318 &&
            (*(u16 *)(e + 0x5C) & 0x8000) != 0 && *(u16 *)(e + 0x5E) != 0x1D &&
            (*(u16 *)(e + 0xAE) & 1) == 0) {
            n = ((s16) * (u16 *)(arg0 + 0xDE) >> 8) + 1;
            sp18.vx = sp10.vx;
            sp20.vy = sp18.vy;
            sp20.vz = sp18.vz;
            do {
                sp20.vx = sp18.vx - d;
                if (func_80135260(*(s32 *)(e + 0x20), *(s32 *)(e + 0x58), &sp18.vx, &sp20.vx) == 1) {
                    *(u16 *)(e + 0x60) = 0xA;
                    *(u16 *)(e + 0x5C) = *(u16 *)(e + 0x5C) | 1;
                    *(u16 *)(e + 0x62) = *(u16 *)(*(s32 *)(e + 0x20) + 0x12) - 0x800;
                    *(u16 *)(e + 0x5E) = 0x1D;
                    n = 1;
                }
                n--;
                sp18.vx = sp18.vx - d;
            } while (n != 0);
        }
        e += 0x10C;
        i++;
    } while (i < 0x60);

    n = ((s16) * (u16 *)(arg0 + 0xDE) >> 8) + 1;
    sp18.vx = sp10.vx;
    sp20.vy = sp18.vy;
    sp20.vz = sp18.vz;
    do {
        sp20.vx = sp18.vx - d;
        if (func_8012DF34(arg0, (s32)&sp18.vx, (s32)&sp20.vx) == 1) {
            D_80126B98[0] = 0x96;
            D_80126B98[-1] = 0x4018;
            n = 1;
        }
        n--;
        sp18.vx = sp18.vx - d;
    } while (n != 0);
}


INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80191C50", func_801932EC);

void func_8019334C(void) {
}

void func_80193354(void) {
}

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80191C50", func_8019335C);

INCLUDE_ASM("asm/ov_SC06_018/nonmatchings/ov_SC06_018_jr_80191C50", func_80193458);

void func_80193580(void) {
}






