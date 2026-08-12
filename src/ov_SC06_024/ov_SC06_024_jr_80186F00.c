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
extern u8 D_80191D28;
extern u8 D_80191C98;
extern u8 D_80191C74;
extern u8 D_80191C50;
extern u8 D_80191D04;
extern u8 D_80191CE0;
extern u8 D_80191CBC;
extern u8 D_80191C2C;
extern void func_80145934(void);
extern u8 D_80191DB8;
extern u8 D_80191D94;
extern u8 D_80191D70;
extern u8 D_80191D4C;
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
extern unsigned char D_801911B0[];
extern unsigned char D_801911E0[];
extern unsigned char D_80191230[];
extern unsigned char D_80191260[];
extern unsigned char D_80191290[];
extern void func_80145EE8(s32 param_1);
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_80146074(void);
extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0();
extern void func_8014607C(void);
extern u8 D_80078EC1;
extern s32 D_80078EC8;
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
extern void (*D_801912E0[])(void *);
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
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_801913A8[];
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
extern u8 D_80191430[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80191438;
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
extern int D_801DFF70;
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
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern s32 D_801DFF74;
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
extern s32 D_80191468;
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
extern void (*D_80191510[])(void);
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
extern void (*D_80191534[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80191524;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80191548[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80191554[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80191564[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8019157C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8019156C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80191590[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801915AC[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8019159C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801915C0[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801915D4[])(void);
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
extern s32 D_801915E8;
extern void (*D_80191610[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801915F0;
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
extern int (*D_8019165C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80191660[])(void);
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
extern unsigned short D_80191AC4[];
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
extern void (*D_80191AD4[])(void);
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
extern int D_801DFFA8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80191AFC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80191ADC;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80191AEC;
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
extern void (*D_80191B3C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80191B44[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80191B10;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80191B50[])(void);
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
extern u8 D_80191B20;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801DFFB0;
extern s32 D_801DFFBC;
extern s32 D_801DFFC0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80191B8C[])(s32 *);
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
extern s32 D_80191B60[];
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
extern s32 D_801DFFB8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80191DDC[])(void);
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
extern char D_80191BFC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80191E80[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80191FD4[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80191DF0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80191FDC[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80191E00;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80191E20;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80191FE4[])(void);
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
extern void (*D_8019200C[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80192018[])(void);
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
extern void (*D_80191E8C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801920BC;
extern void func_8015D380(s32 a0);
extern unsigned char D_801911A0[];
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
extern unsigned char D_801920D0[];
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
extern s8 D_8019210C[];
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
extern u16 D_80192154;
extern u16 D_80192156;
extern u16 D_80192158;
extern s32 D_8019215C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80192164;
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
extern int D_80191E70;
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
extern unsigned int D_801921E8[];
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
extern void (*D_80192298[])(void);
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
extern u16 D_801922C8[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8019232C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801DFFC8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80192350[])(void);
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
extern int D_801E0020[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80192398[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80192388;
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
extern char D_801DF6DC[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801923A0[])(void);
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
extern void (*D_801923F4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801923BC;
extern s16 D_801923F0;
extern s16 D_801923EE;
extern s16 D_801923EC;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80192400[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E0080;
extern u8 D_801E0081;
extern u8 D_801E0082;
extern u8 D_801E0083;
extern u8 D_801E0084;
extern u8 D_801E0085;
extern u8 D_801E0086;
extern u8 D_801E0087;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80192410[])(void);
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
extern s32 D_801E00C0;
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
extern void (*D_80192454[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801924D0[];
extern s32 D_801924F0[];
extern u8 D_8019256C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8019258C[];
extern u8 D_801925AC[];
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
extern void (*D_80192648[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801926C4[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801DF6EC;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801926D0[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801926D8[])(void);
extern void func_801663FC(void *a0);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_801665B4();
extern void func_80146C3C();
extern void func_80166438(u8 *a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_800D22E4(s32 a0);
extern void func_801665B4(s32 *a0);
extern void (*D_801927A0[])(void);
extern void func_80166618(void *a0);
extern void (*D_801927B0[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801927C0[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801927CC[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8019272C[];
extern u8   D_80192740[];
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
extern void (*D_801927E4[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801927EC[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801927F4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801927FC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80192804[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8019280C[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80192814[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801928C8[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801928D0[])(void);
extern void func_80169F00(void *a0);
extern char D_80192880[];
extern char D_80192840[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80192908[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80192914[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8019295C[])(void);
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
extern void (*D_801929D8[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E03E0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801929CC[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80192A10[];
extern unsigned short D_80192A18[];
extern unsigned short D_80192A20[];
extern unsigned char D_801E03E8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E03E0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80192A28[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E051C;
extern M2C_UNK D_801E0520;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E04A8;
extern void (*D_80192A58[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E0524[];
extern u8 D_801E052C[];
extern u8 D_801E04DC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80192A60[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80192A7C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80192A84[])(void);
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
extern void (*D_80192AEC[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80192A90;
extern u8 D_80192A9C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80192B20[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80192B28[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80192B7C[])(void);
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
extern u16 D_80192BB0[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80192BA0[];
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
extern s32 D_80192BCC;
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
extern void (*D_80192C44[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80192C4C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80192C54[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80192C5C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80192C64[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80192C6C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80192C78[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80192C84[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80192C90[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80192CA0[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80192CB0[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80192CB8[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80192CC0[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80192CC8[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80192CD0[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80192CD8[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80192CE0[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80192CE8[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80192CF0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80192CF8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80192D00[])(void);
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
extern void (*D_80192D08[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80192D10[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80192D18[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80192D20[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80192D28[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80192D30[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80192D38[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80192D40[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80192D48[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80192D50[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80192D58[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80192D60[])(void);
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
extern void (*D_80192DA4[])(void);
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
extern M2C_UNK D_80192D68;
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
extern void (*D_80192DD4[])(void);
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
extern void (*D_80192E10[])(void);
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
extern void (*D_80192E68[])();
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
extern void (*D_80192E78[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80192E80[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80192FE8[])();
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
extern void (*D_80192FF4[])();
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
extern M2C_UNK D_801DF934;
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
extern s16 D_801E18F0;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801E0C60;
extern short D_801E1964;
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
extern s32 D_801E108C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E10B4;
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
extern s16 D_801E1070;
extern s32 func_8017A3B0(void);
extern short D_801E10AC;
extern short D_801E10A8;
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
extern s16 D_801E1074;
extern u16 D_801E10F4;
extern u16 D_801E10F6;
extern u16 D_801E10F8;
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
extern s16 D_801E10EC;
extern s16 D_801E10EE;
extern s16 D_801E10F0;
extern s16 D_801E10E4;
extern s16 D_801E10E6;
extern s16 D_801E10E8;
extern void func_8017B7A8(void);
extern s16 D_801E1104;
extern s16 D_801E1106;
extern s16 D_801E1108;
extern s16 D_801E110C;
extern s16 D_801E110E;
extern s16 D_801E1110;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801E10FC;
extern short D_801E10FE;
extern short D_801E1100;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801E1094;
extern SV4 D_801E109C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801E10BC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801E10B8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_801931D0[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BEBC(s32 arg0);
extern void (*D_8019327C[])(void);
extern void func_8017CE2C(void *a0);
extern void func_8017D0D8(void);
extern s32 func_8017CE68(s32 a0);
extern s32 func_8017CEAC(void);
extern void func_8017D100(void);
extern s32 func_8017CED0(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017CF10(u8 *a0);
extern void func_800D1EBC(void);
extern void func_8017CF8C(void);
extern void (*D_80193290[])(void);
extern void func_8017CFAC(void *a0);
extern s32 func_8017CFE8(s32 a0);
extern void (*D_8019329C[])(void);
extern void func_8017D05C(void *a0);
extern void func_8017D128(void);
extern s32 func_8017D098(s32 a0);
extern s32 D_801932B4;
extern s32 D_801932C8;
extern void (*D_801932D4[])(void);
extern void func_8017D34C(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017D63C(s32 param_1, s16 *param_2);
extern void func_8013B7F4(void *a0, int a1);
extern int func_8017D7D4(int param_1);
extern void (*D_801935C8[])(void);
extern void func_8017F7B8(void *a0);
extern void (*D_801935E0[])(void);
extern void func_8017FBF8(void *a0);
extern void func_801292C8(u8 *a0);
extern s32 func_8017FC8C(s32 arg0);
extern void (*D_80193608[])(void);
extern void func_8017FCC0(void *a0);
extern void (*D_8019366C[])(void);
extern void func_80180104(void *a0);
extern void func_801801D0(void);
extern void func_8012E8C4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(s32 a0);
extern void func_801801D8(s32 a0);
extern s32 func_80180218(void);
extern void func_8012DFD4(void *a0);
extern void func_8018090C(void *a0);
extern void (*D_801937B4[])(void);
extern void func_8018096C(void *a0);
extern void func_80180CE8(s32 a0);
extern void func_80180F2C(void *a0);
extern void (*D_801937D8[])(void);
extern void func_80180FB8(void *a0);
extern void func_801811AC(void *a0);
extern void func_80181204(s32 a0);
extern s32 func_8018148C(void);
extern void func_80181414(s32 a0);
extern void func_801812C0(s32 param_1);
extern void func_80181468(void);
extern void (*D_80193814[])(void);
extern void func_801814D0(void *a0);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_80181700(void*);
extern void func_801816D0(s32*);
extern void func_8018150C(int param_1);
extern s32 func_80181714(s32 *a0, s32 a1);
extern void func_801816D0(s32 *a0);
extern void func_80181658(s32 *a0);
extern void func_801816D0(s32 *param_1);
extern void func_80181700(void *a0);
extern void (*D_8019384C[])(void);
extern void func_8018177C(void *a0);
extern void func_801817B8(s32 param_1);
extern void func_80181854(s32 param_1);
extern void func_80181804(s32 param);
extern void func_8018184C(void);
extern void func_801819B8();
extern void func_80013F3C(s32);
extern void RotMatrixZ(s32, void *);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern void func_80017714(void *);
extern SVECTOR_8017E6D8 D_801E1674[4];
extern struct PW8017E6D8 D_801E1694;
extern struct PW8017E6D8 D_801E1698;
extern u8 D_801E169C, D_801E169D, D_801E169E, D_801E16A0, D_801E16A1, D_801E16A2;
extern int D_801E16A4;
extern void func_801819B8(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d, SVECTOR_8017E6D8 *e, SVECTOR_8017E6D8 *f, s16 *g, struct PW8017E6D8 *h);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80181ED4(s32 arg0);
extern void func_801823A8(void *a0);
extern void func_80182584(void *arg0);
extern void (*D_801AC4F8[])(void);
extern void func_801827E8(void *a0);
extern void func_80182EAC(s32 arg0);
extern void func_80183188(s32 arg0);
extern void (*D_801AC564[])(void);
extern void func_8018337C(void *a0);
extern void func_80183408(s32 target, u16 *cur, s32 step);
extern void (*D_801AC590[])(void);
extern void func_80183640(void *a0);
extern void func_8012B23C();
extern void func_801837D0(s32 a0);
extern code_fn D_801AC64C[];
extern s32 func_8012B414(s32 a0);
extern void func_801838A0(int param_1);
extern void func_801838F0(s32 arg0);
extern void func_80183B34(void);
extern void func_80183CA8(void);
extern s32 func_8012C354(s32 a0, void *a1);
extern s32 func_80143994(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012CAE4(s32 a0);
extern void func_8012B030(s32 a0);
extern void func_80183FDC(s32 param_1);
extern void func_80184248(s32 param_1);
extern void func_8018447C(s32 param_1);
extern void func_8012C218(s32);
extern void func_8001C924(s32 a0, void *a1);
extern s32  func_8012BEE8();
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_80187BC8(s32 a0);
extern void func_80013350(s32 a0, void *a1);
extern void func_80184AE8(s32 p);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern void func_80142414(s32 a0, s16 a1);
extern void func_80184DB0(s32 p);
extern void func_80184E70(s32 param_1);
extern void func_801857D4(s32 param_1);
extern void func_80187D50(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_801897F0(void *a0, s32 a1, s32 a2);
extern s32  func_8012BEE8();   /* TU-canonical: an earlier call site passes zero args */
extern void func_8018588C(s32 p);
extern void func_8012A828(s32, void*);
extern void func_80185A2C(short *a0);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern s32  func_8012B744(void *a0, void *a1);
extern void func_801898EC(s32, void*, void*, s32);
extern void func_80189888(s32, void*, s32, s32, s32, s32);
extern s32  func_80013478(s32 a0, s32 a1);
extern void func_80185EF8(s32 param_1);
extern void func_801875A4(void);
extern void func_80186314(void *a0);
/* ==== end §8b carried decl layer ==== */


extern void func_80187460(s32 a0);
extern s32  func_8012DBD0(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801872EC(s32 a0, s32 a1);
extern void func_8012CC64(s32 a0, s32 a1);
extern s32  func_80143B6C(s32 a0, s32 a1);
extern s32  func_8012CBA4(s32 a0);
extern s32  func_8012CBF4(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_80131C78(s32 a0);
extern void func_80131E00();
extern void func_8018A3CC(s32 a0, s32 a1);


void func_80186F00(s32 a0) {

    extern u8 D_801BC428;
    u16 sp10[4];
    s32 s1;

    if (*(s16 *)(a0 + 0xA) >= 0x10) {
        func_80187460(a0);
        return;
    }

    if (*(s32 *)(a0 + 0x10) != 0 || *(s32 *)(a0 + 0x18) != 0) {
        func_8012DBD0(a0, 0x50,
                      *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800, 0x1D);
    }

    switch (*(u8 *)(a0 + 0xC2)) {
    case 0:
        func_801872EC(a0, (s32)&D_801BC428);
        *(u8 *)(a0 + 0xC2) += 1;
    case 1:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x29) {
            func_80131E00(a0, 0xD);
            return;
        }
        s1 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&D_801BC428);
        if (s1 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (s1 & 0x4000) {
            func_8012B23C(a0);
            *(u8 *)(a0 + 0xC2) = 4;
        } else if (s1 & 0x2000) {
            *(u8 *)(a0 + 0xC2) = 2;
            func_80143B6C(a0, 1);
            *(s32 *)(a0 + 0x14) = 0xFFF30000;
            *(s32 *)(a0 + 0x1C) = 0;
            func_8018A3CC(a0, 0x9B8);
        }
        break;

    case 2:
        {
            s32 s2;

            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
            *(s32 *)(a0 + 0x1C) += 1;
            if (*(s32 *)(a0 + 0x1C) >= 0x29) {
                func_80131E00(a0, 0xD);
                return;
            }
            s2 = *(s32 *)(a0 + 0x14);
            s1 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&D_801BC428);
            if (s1 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (s1 & 0x4000) {
                func_8012B23C(a0);
                *(u8 *)(a0 + 0xC2) = 4;
            } else if (s1 & 0x2000) {
                func_80143B6C(a0, 1);
                *(s32 *)(a0 + 0x14) = (-s2) / 3;
                *(s32 *)(a0 + 0x1C) = 0;
                *(u8 *)(a0 + 0xC2) = 3;
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            }
        }
        break;

    case 3:
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) * 15 / 16;
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) * 15 / 16;
        if (*(u8 *)(a0 + 0xC3) & 1) {
            s1 = func_8012CBA4(a0);
            if (s1 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (!(s1 & 0x6000)) {
                func_80131E00(a0, 0xD);
                return;
            }
        } else {
            s1 = func_8012CBF4(a0);
            if (s1 & 0x8000) {
                *(s32 *)(a0 + 0x18) = 0;
                *(s32 *)(a0 + 0x10) = 0;
            }
            if (s1 & 0x4000) {
                func_8012B23C(a0);
                *(u8 *)(a0 + 0xC2) = 4;
                break;
            } else if (s1 & 0x2000) {
                *(u8 *)(a0 + 0xC3) |= 1;
                func_8018A3CC(a0, 0x9B8);
            }
        }
        if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
            func_80143B6C(a0, 1);
        }
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) < 0x11) {
            break;
        }
        if (!(s1 & 0x6000)) {
            func_80131E00(a0, 0xD);
            return;
        }
        if (*(s16 *)(a0 + 0x76) <= 0) {
            func_80131E00(a0, 6);
        } else {
            func_80131C78(a0);
        }
        break;

    case 4:
        s1 = func_8012CBA4(a0);
        if (s1 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        if (s1 & 0x2000) {
            if (*(s16 *)(a0 + 0x76) <= 0) {
                func_80131E00(a0, 6);
            } else {
                func_80131C78(a0);
            }
        } else {
            if ((*(s32 *)(a0 + 0x1C) & 3) == 3) {
                func_80143B6C(a0, 1);
            }
            *(s32 *)(a0 + 0x1C) += 1;
            if (*(s32 *)(a0 + 0x1C) >= 0x3D) {
                func_80131E00(a0, 0xD);
                return;
            }
        }
        break;
    }
}


/* §160g STEP 0 sibling hit: identical shape already matched inline inside
 * func_80131340 (src/ov_SC03_099/ov_SC03_099_jr_8012ACE0.c and its dedup
 * siblings), where the "delta" struct is a LOCAL computed earlier in that
 * function. Here the delta is passed in directly via a1 — same struct-copy /
 * add / dead-copy / call / subtract / store shape, adapted to a pointer
 * parameter instead of a local. */

void func_801872EC(s32 a0, s32 a1)
{
    struct V8_801872EC {
        u16 vx, vy, vz, pad;
    };
    extern s32 func_8012CEB0(void*, void*, s32);

    struct V8_801872EC sp10;
    struct V8_801872EC sp18;
    struct V8_801872EC sp20;

    sp10.vx = *(u16 *)(a0 + 0x3A);
    sp10.vy = *(u16 *)(a0 + 0x3E);
    sp10.vz = *(u16 *)(a0 + 0x42);
    sp18 = sp10;
    sp18.vx += *(u16 *)(a1 + 0x0);
    sp18.vy += *(u16 *)(a1 + 0x2);
    sp18.vz += *(u16 *)(a1 + 0x4);
    sp20 = sp18; /* load-bearing dead aggregate copy — gcc-2.7.2 has no aggregate DSE (§160e-family) */
    ((s32 (*)(s32, s32, s32))func_8012CEB0)((s32)&sp10, (s32)&sp18, 1);
    sp18.vx -= *(u16 *)(a1 + 0x0);
    sp18.vy -= *(u16 *)(a1 + 0x2);
    sp18.vz -= *(u16 *)(a1 + 0x4);
    *(u16 *)(a0 + 0x3A) = sp18.vx;
    *(u16 *)(a0 + 0x3E) = sp18.vy;
    *(u16 *)(a0 + 0x42) = sp18.vz;
    *(u16 *)(a0 + 0x6) = sp18.vx;
    *(u16 *)(a0 + 0xA) = sp18.vy;
    *(u16 *)(a0 + 0xE) = sp18.vz;
}


extern void func_8018A3CC(s32 arg0, s32 arg1);
    void func_80187440(s32 arg0) {
        func_8018A3CC(arg0, 0x9B7);
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_80187460);


extern void func_801875A4(void);
extern void func_80187A50(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_801874E4(s32 param_1) {

    extern s32 D_801D420C;
    u16 uVar1;
    s32 iVar2;

    *(s16 *)(param_1 + 0x34) = 0;
    if ((*(u32 *)(param_1 + 0xe0) & 8) == 0) {
        func_801875A4();
    } else {
        if ((*(u32 *)(param_1 + 0xe0) & 0x20) != 0) {
            func_80187A50(param_1, -0x8000);
        }
        *(s16 *)(param_1 + 2) = 0x22;
        func_8012A828(param_1, &D_801D420C);
    }
    iVar2 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(iVar2 + 0x14) = 0;
    *(s16 *)(iVar2 + 0x10) = 0;
    uVar1 = *(u16 *)(*(s32 *)(param_1 + 0x78) + 2);
    *(u32 *)(param_1 + 0xe0) = (*(u32 *)(param_1 + 0xe0) & 0xffffffd5) | 0x400;
    *(s16 *)(param_1 + 0x5e) = 0;
    *(u16 *)(param_1 + 0xae) = *(u16 *)(param_1 + 0xae) & 0xfffe;
    *(u32 *)(param_1 + 0xc4) = *(u32 *)(param_1 + 0xc4) & 0xfffffffb;
    *(s16 *)(param_1 + 0x5c) = uVar1;
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_801875A4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018769C);



extern s32 func_8012BCCC(s32 a0);
extern s32 func_80189938(s32 a0, s32 a1);
extern void func_8012F214(s32, s32, s32);
extern s32 func_801897F0(void *a0, s32 a1, s32 a2);

/* Two load-bearing constructs (do NOT "clean up"):
 *  1. `goto ret0` / `goto store` with `ret0:` placed BEFORE the store block — cookbook L1344
 *     shared-ret0 goto. A trailing `return 0` makes gcc sink the merged ret0 tail past the
 *     store block (7 mismatches: BRANCH-POLARITY + swapped tail).
 *  2. `register s32 r __asm__("$2")` on the func_80189938 result + `return r`. Plain
 *     `return 0;` there emits `set v0,0; j epi`, which cross_jump (§5a) merges into the
 *     ret0 block, so the branch lands on ret0 instead of the epilogue. Pinning r to $v0
 *     makes `return r` a self-copy that dies before jump2, leaving a bare `j epi` that
 *     jump.c collapses into `beqz $v0, .L8018730C`. (A plain `s32 r` does NOT work — cse2
 *     const-folds `r` to 0 on the fall-through edge and the merge comes back.) */
s32 func_801877BC(s32 p) {

    extern s32 D_80126B9C;
    extern u8 D_801BC200[];
    s32 buf10[2];
    register s32 r __asm__("$2");   /* $v0 — see note 2 above */

    if ((*(u32 *)(p + 0xE0) & 1) == 0) {
        goto ret0;
    }
    if (*(u16 *)(p + 2) == 1) {
        goto ret0;
    }
    if (*(u16 *)(p + 2) == 0xD) {
        return 0;
    }
    if ((D_80126B9C & 2) == 0) {
        return 0;
    }
    if (0x10000 < func_8012BCCC(p)) {
        return 0;
    }
    r = func_80189938(p, 0x380);
    if (r == 0) {
        return r;
    }
    ((void (*)(s32, void *, void *))func_8012F214)(p, D_801BC200, buf10);
    if (func_801897F0(buf10, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x380) != 0) {
        goto store;
    }
ret0:
    return 0;
store:
    *(u16 *)(p + 2) = 0xC;
    return 1;
}



/* func_8018788C — walk the 0x60-entry / 0x10C-stride entity table D_801202A0 and
 * react to the first neighbour of class 0x27A (get pushed away from it) or 0x2F4
 * (get clamped down onto it).
 *
 * §71 sibling-first: the callee signatures below are copied VERBATIM from this TU's
 * own already-matched neighbours — func_8012B0B4 (TU L6971/7855/8177), func_8012B6D4
 * (TU L6419), func_8012CEB0 (TU L7226, the func_80187844 block), func_8012C098
 * (TU L5379) — and D_801202A0 is the TU's file-scope `extern u8 D_801202A0[];` (L384).
 * func_8012BC60 / func_8012ADE4 are not declared in this TU; the forms below are the
 * fleet-majority shapes (func_8012ADE4 verbatim; func_8012BC60 with `void *` instead of
 * `struct Vec *` so the draft does not depend on engine_types.h being in scope).
 *
 * FIVE load-bearing constructs (do NOT "clean up"):
 *
 *  1. NO SECOND WALKED POINTER. All of +0x6/+0xA/+0xE are written as `*(T *)(p + k)`
 *     off the single biv `p`. combine_givs then merges the three DEST_ADDR givs onto
 *     ONE anchor = the LAST-emitted one (+0xE, from the case-0x2F4 `lh`), giving the
 *     target's `$s3 = $s2 + 0xE` with -0x8/-0x4/0x0 displacements.
 *     An explicit `q = p + 0xE` with `*(u16 *)q` looks equivalent and is NOT:
 *     gcc-2.7.2 excludes a bare `*q` (mult 1, add 0) from givs (find_mem_givs:4198),
 *     so q stays a live biv AND the remaining two accesses combine onto their own
 *     anchor +0xA => THREE IVs, the wrong anchor, and the $s6 hoist lost to pressure
 *     (measured: 111 ins, 87 mismatched).  gcc-2.7.2-map/loop.md §L1 rules 4 & 6.
 *
 *  2. `switch`, not `if/else if`. The two-case switch is what emits the target's
 *     compare CHAIN with BOTH arms out of line (`beq`/`beq`/`j default`, 6 slots).
 *     An `if (id == 0x27A) ... else if (id == 0x2F4)` inverts the first test and lets
 *     the 0x27A arm fall through — 2 instructions short.
 *
 *  3. do-while with `i++` BEFORE `p += 0x10C`. strength_reduce inserts the reduced
 *     giv's `addiu` immediately before ITS biv's increment, so the source order
 *     i-then-p is what produces `addiu $s4,$s4,1` / `addiu $s3,$s3,0x10C` /
 *     (delay) `addiu $s2,$s2,0x10C`. A `for (i = 0; i < 0x60; i++)` with `p += 0x10C`
 *     last puts the giv add first and swaps the pair.
 *
 *  4. `self4` and `sc` are REAL pre-loop locals, in that order. Both are loop
 *     invariants; written inline as `(s16 *)(a0 + 4)` / `(unsigned int *)sp20` at the
 *     call, combine folds the address straight into the argument move
 *     (`addiu $a0,$sp,0x20`) and the target's `$s6 = $sp + 0x20` hoist never happens.
 *     Assigning them in a *different basic block* from their uses is what keeps the
 *     pseudos alive; the declaration ORDER (p, i, self4, sc) is what gives
 *     $s2/$s4/$s5/$s6 in the target's prologue emission order.
 *
 *  5. `s16 y` (a SHORT local), and `s32 sp20[2]` (an EIGHT-byte scratch).
 *     - The short local is why `y` gets a second pseudo: gcc-2.7.2 emits
 *       `(set (reg:HI B) (subreg:HI (reg:SI A)))` for the HImode assignment, i.e. the
 *       target's `addu $a1,$a0,$zero` in the branch delay slot, with the two `- 0x60`
 *       recomputed from A ($a0, the compare) and B ($a1, the stored value).
 *       An `s32 y` coalesces the pair away and loses that instruction.
 *     - The short local also costs a DEAD 4-byte reload home at the top of the frame
 *       (`(use (mem:SI (plus $sp 48)))` in the greg dump, no insn references it).
 *       That is exactly why the func_8012B0B4 buffer is 8 bytes, not 16: 0x10 + 8
 *       (v10) + 8 (v18) + 8 (sp20) + 4 (dead) rounds to 0x30 = the target's first
 *       saved-register slot. 8 bytes also matches the fleet's canonical shape for a
 *       func_8012B0B4 output buffer (`unsigned int buf[2]`).
 */


extern s32  func_8012BC60(void *a0, void *a1);
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern s32  func_8012CEB0(void *a0, void *a1, s32 a2);
extern void func_8012ADE4(u8 *a0);
extern void func_8012C098(void *param_1);

void func_8018788C(s32 a0) {

    extern u8   D_801202A0[];
    u8 *p;
    s16 *self4;
    unsigned int *sc;
    s32 i;
    s16 y;
    s32 z;
    s32 ang;
    s16 v10[4];  /* sp+0x10 */
    s16 v18[4];  /* sp+0x18 */
    s32 sp20[2]; /* sp+0x20 — func_8012B0B4 output */

    p = D_801202A0;
    i = 0;
    self4 = (s16 *)(a0 + 4);
    sc = (unsigned int *)sp20;
    do {
        if ((u8 *)a0 != p) {
            switch (*(u16 *)p) {
            case 0x27A:
                if (func_8012BC60((void *)self4, (void *)(p + 4)) < 0x6400) {
                    ang = func_8012B6D4(self4, (s16 *)(p + 4));
                    func_8012B0B4(sc, ang, 0xA1);
                    v18[0] = *(u16 *)(p + 6);
                    v18[1] = *(u16 *)(p + 0xA);
                    v18[2] = *(u16 *)(p + 0xE);
                    v18[0] += sp20[0];
                    v18[2] += sp20[0] >> 16;
                    v18[1] = *(u16 *)(a0 + 0xA);
                    v10[0] = *(u16 *)(a0 + 0x3A);
                    v10[1] = *(u16 *)(a0 + 0x3E);
                    v10[2] = *(u16 *)(a0 + 0x42);
                    if ((func_8012CEB0(v10, v18, 0) & 0x2000) == 0) {
                        func_8012ADE4((u8 *)a0);
                        return;
                    }
                    *(u16 *)(a0 + 6) = v18[0];
                    *(u16 *)(a0 + 0xA) = v18[1];
                    *(u16 *)(a0 + 0xE) = v18[2];
                    return;
                }
                break;
            case 0x2F4:
                y = *(s16 *)(p + 0xE);
                z = *(s16 *)(a0 + 0xE);
                if (y + 0x10 < z) {
                    func_8012C098((void *)a0);
                    return;
                }
                if (y - 0x60 < z) {
                    *(s16 *)(a0 + 0xE) = y - 0x60;
                }
                break;
            }
        }
        i++;
        p += 0x10C;
    } while (i < 0x60);
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_80187A50);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_80187BC8);


/* Family exemplar (S48 wave-4). Two compiler-shape levers used, both already
 * documented in the cookbook:
 *  - §164z (func_8018A974 refutation): a non-volatile `__asm__("" ::: "memory")`
 *    barrier forces a genuine second `lw` reload of *(a0+0x90) at the C/D-group
 *    check, matching the target's register-clash reload, at zero extra stack cost.
 *  - §45 Lever 4: the call is written literally duplicated in each of the three
 *    arms rather than shared through one fall-through tail; gcc-2.7.2's jump.c
 *    cross-jumps the duplicates back together, which is what lets `addiu $a0,$zero,0x53`
 *    (not the unrelated stack-arg constant 0x14) win both branch-delay slots.
 */

extern s32 func_801469C8(int, void*, int, int, u16, int, int, int);

void func_80187C28(s32 a0, s32 a1) {

    extern u8 D_801D3284[];
    extern u8 D_801D3C44[];
    extern u8 D_801D3D3C[];
    extern u8 D_801D3904[];
    extern u16 D_800B99DA;
    if ((*(s16 *)(a0 + 0x70) & 0x8000) == 0) {
        return;
    }
    if ((a1 & 0xFF) != 0x24) {
        return;
    }

    if (*(u8 **)(a0 + 0x90) == D_801D3284) {
        if (D_800B99DA % 3 == 0) {
            ((s32 (*)(int, void *, int, int, s32, int, int, int))func_801469C8)(0x53, (void *)a0, *(s16 *)(a0 + 6), (s16)(*(u16 *)(a0 + 0xA) - 0xA0),
                          *(s16 *)(a0 + 0xE), 0, 0, 0x14);
        }
    } else if (*(u8 **)(a0 + 0x90) == D_801D3C44 && *(u16 *)(a0 + 2) == 0xB) {
        ((s32 (*)(int, void *, int, int, s32, int, int, int))func_801469C8)(0x53, (void *)a0, *(s16 *)(a0 + 6), (s16)(*(u16 *)(a0 + 0xA) - 0xA0),
                      *(s16 *)(a0 + 0xE), 0, 0, 0x14);
    } else {
        __asm__("" ::: "memory");
        if ((*(u8 **)(a0 + 0x90) == D_801D3D3C || *(u8 **)(a0 + 0x90) == D_801D3904) &&
            D_800B99DA % 6 == 0) {
            ((s32 (*)(int, void *, int, int, s32, int, int, int))func_801469C8)(0x53, (void *)a0, *(s16 *)(a0 + 6), (s16)(*(u16 *)(a0 + 0xA) - 0xA0),
                          *(s16 *)(a0 + 0xE), 0, 0, 0x14);
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_80187D50);


/* func_80187DB0 — line-of-sight / collision probe.
 *
 * Rotate the direction SVECTOR D_801BC450[dir] through the entity's matrix
 * (*(0x20) + 0x34) into a scratch SVECTOR at sp+0x10, build the segment
 * start (sp+0x18) = entity pos and end (sp+0x20) = entity pos + rotated
 * vector, then hand the pair to func_8012CEB0 / func_800132BC.
 *
 * §71 sibling-first: DEFINE_func_80169408 / DEFINE_func_8016986C in
 * src/shared/engine_core.h are the house shape for this ApplyMatrixSV +
 * SVECTOR-local family — `s16 vNN[4]` locals declared in ASCENDING stack
 * offset order (sp+0x10, sp+0x18, sp+0x20) and the entity position read as
 * `*(u16 *)(s1 + 0x6 / 0xA / 0xE)` (which is what makes the loads `lhu`).
 *
 * The target stores each of sp+0x20/0x22/0x24 TWICE — a plain copy first,
 * then the copy plus the rotated component — so the source assigns the
 * position, then `+=` the delta as separate statements (the local's address
 * is taken, so gcc-2.7.2 cannot kill the first store).
 */

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_8012CEB0(void *a0, void *a1, s32 a2);
extern s32 func_800132BC(void *a0, void *a1);

s32 func_80187DB0(s32 a0, s32 a1) {

    extern s16 D_801BC450[][4];
    extern s32 D_801E16A8;
    s32 s0 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR — ApplyMatrixSV out */
    s16 v18[4];   /* sp+0x18 SVECTOR — segment start */
    s16 v20[4];   /* sp+0x20 SVECTOR — segment end */
    s32 r;

    ApplyMatrixSV((void *)(*(s32 *)(s0 + 0x20) + 0x34), D_801BC450[a1], v10);
    v18[0] = *(u16 *)(s0 + 0x6);
    v18[1] = *(u16 *)(s0 + 0xA);
    v18[2] = *(u16 *)(s0 + 0xE);
    v20[0] = *(u16 *)(s0 + 0x6);
    v20[1] = *(u16 *)(s0 + 0xA);
    v20[2] = *(u16 *)(s0 + 0xE);
    v20[0] = v20[0] + v10[0];
    v20[1] = v20[1] + v10[1];
    v20[2] = v20[2] + v10[2];
    r = func_8012CEB0(v18, v20, 0);
    D_801E16A8 = func_800132BC(v18, v20);
    return r != 0x2000;
}



extern void (*D_801BC490[])(void);

void func_80187E90(void *a0) {
    D_801BC490[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_80187ECC);


/* ov_SC06_018 :: func_80188058  — actor state machine, jump-table switch on the
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
extern void func_8012E8C4(s32);
extern void func_8012E8A8(u8 *a0);
extern void func_8018956C(s32 a0, s32 a1);
extern s32  func_801899B8(s32 a0, s32 a1, s32 a2);
extern void func_8012C218(s32);


void func_80188058(s32 param_1)
{

    extern u8 D_801BC49C;
    s32 iVar;
    s32 t;
    u16 st;
    u16 uVar1;
    s32 pad[1];   /* see key (2): forces the 0x20 frame — never referenced */

    if (0xf < *(s16 *)(param_1 + 0xA)) {
        ((void (*)(void *))func_8012C218)((void *)param_1);
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
                 ((*(u16 *)(param_1 + 0x70) & 0xF) * 8) + (s32)&D_801BC49C) &
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
        ((void (*)(u8 *))func_8012E8C4)((u8 *)param_1);
        if (func_8012BEE8(param_1) == 1) {
            ((void (*)(void *))func_8012C218)((void *)param_1);
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
            func_8018956C(param_1, 1);
        }
        return;
    case 5:
        if (func_801899B8(param_1, 0x60, 0xA0) == 1) {
            ((void (*)(void *))func_8012C218)((void *)param_1);
        }
        return;
    }
}


extern void func_8012C218(s32);
extern void func_8012E8A8(u8 *a0);

/* §48-C2: lwl/lwr/swl/swr block copy == a plain struct assign of a 2-byte-aligned struct */

void func_8018833C(s32 param_1)
{
    s32 t1 = *(s32 *)(param_1 + 0x64);
    s32 pad[2];

    if (*(s16 *)(t1 + 0x36) != *(s16 *)(param_1 + 0x10A)) {
        ((void (*)(void *))func_8012C218)((void *)param_1);
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
                    *(UAlign12_8018833C *)(param_1 + 0xFC) = *(UAlign12_8018833C *)(a2 + 0x90);
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

            *(UAlign8_8018833C *)(param_1 + 0x50) = *(UAlign8_8018833C *)(t1 + 0x50);

            {
                s32 dst = *(s32 *)(param_1 + 0x20);
                s32 src = *(s32 *)(t1 + 0x20);
                *(UAlign8_8018833C *)(dst + 0x10) = *(UAlign8_8018833C *)(src + 0x10);
            }
            {
                s32 dst = *(s32 *)(param_1 + 0x20);
                s32 src = *(s32 *)(t1 + 0x20);
                *(UAlign8_8018833C *)(dst + 0x18) = *(UAlign8_8018833C *)(src + 0x18);
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



extern void (*D_801BC5E8[])(void);

void func_801885F4(void *a0) {
    D_801BC5E8[*(u16 *)((s32)a0 + 0x2)]();
}



/* Sibling-search (cookbook §160g): every declaration below is TU-canonical, lifted verbatim
 * from src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c (the destination TU):
 *   func_8012C354  -- decl at TU:2846 "extern s32 func_8012C354(s32 a0, void *a1);"
 *   func_8012CAE4  -- decl at TU:2849 "extern void func_8012CAE4(s32 a0);"
 *   func_80143994  -- decl at TU:2847 "extern s32 func_80143994(s32 a0, s32 a1);"
 *   func_8018906C  -- ALREADY DEFINED in this TU at :3492 "void func_8018906C(s32 p)" (banked)
 *   func_8012C1B8  -- TU-canonical `void (void)` at :4123/:3929, called via the established
 *                     cast-through-function-pointer idiom (§161c) seen in this TU's own
 *                     func_80189A34 (:4138) and func_801894F0 (:3948) -- byte-identical spawn
 *                     idiom, same handle-alloc-then-null-check shape as our case 2.
 *   func_8001CA1C  -- not yet declared in THIS TU; canonical form taken from the sibling TU
 *                     ov_SC06_018_jr_80140608.c:1704 "extern void func_8001CA1C(s32 a0, s32 a1);"
 *   func_801887A0  -- INCLUDE_ASM in this TU at :3206 (still unmatched); called here with the
 *                     object pointer and its own return discarded, so declared void(s32).
 * D_801BC4F8 / D_801BC52C / D_801BC4CC are new (undeclared anywhere in src/); declared as
 * plain byte arrays per this TU's own convention for opaque data blobs (e.g. D_801AD470[]
 * at TU:2791) -- only their address is used (func_8012C354's a1 is void*, func_8001CA1C's a1
 * is a raw s32 cast of the address), so element type is codegen-irrelevant.
 */
extern s32 func_8012C354(s32 a0, void *a1);
extern void func_8012CAE4(s32 a0);
extern s32 func_80143994(s32 a0, s32 a1);
extern void func_801887A0(s32 a0);
extern void func_8012C1B8(void);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8018906C(s32 p);


void func_80188630(s32 a0) {

    extern u8 D_801BC4F8[];
    extern u8 D_801BC52C[];
    extern u8 D_801BC4CC[];
    s32 v1;
    s32 obj;

    v1 = *(u16 *)(a0 + 0x70) & 0xF;
    switch (v1) {
    case 0:
        if (func_8012C354(a0, D_801BC4F8) == 0) {
            return;
        }
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = a0 + 0xE8;
        *(u16 *)(a0 + 0x104) = 0x78;
        func_801887A0(a0);
        func_80143994(a0, 0x1800);
        return;
    case 1:
        if (func_8012C354(a0, D_801BC52C) == 0) {
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
        func_8001CA1C(obj, (s32)D_801BC4CC);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x14CC;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x1199;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x58000000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
        func_8018906C(a0);
        return;
    default:
        return;
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_801887A0);


extern void func_8012C218(s32);
extern s32  func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8018956C(s32 a0, s32 a1);
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BEE8(s32 a0);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_8012CBF4(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern u8  *func_8012913C(s32 a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);


void func_80188808(s32 param_1) {

    extern u8 D_801BC560;
    extern u8 D_801BC614[];
    extern u16 D_80126CB4;
    extern u16 D_80126CB6;
    extern u16 D_80126CB8;
    u16 uVar1;

    if (0xf < *(s16 *)(param_1 + 0xA)) {
        ((void (*)(void *))func_8012C218)((void *)param_1);
        return;
    }

    {
        s32 base = (s32)&D_801BC560;
        s32 r = func_8012D5E4(param_1, base, base + 8, 0x78);
        if (r == 1 || (*(u16 *)(param_1 + 0x5C) & 1) != 0) {
            func_8018956C(param_1, 1);
            ((void (*)(void *))func_8012C218)((void *)param_1);
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
    func_8018956C(param_1, 1);
    return;
LAB_80188494:
    {
        s32 iv = (s32)func_8012913C(0x80);
        if (iv == 0) return;
        {
            u16 out[4];
            ((void (*)(s32, void *, void *))func_8012F214)(param_1, D_801BC614, out);
            *(u16 *)(iv + 6) = out[0];
            *(u16 *)(iv + 0xA) = out[1];
            *(u16 *)(iv + 0xE) = out[2];
        }
        return;
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_80188A60);


extern void func_8012C218(s32);
extern s32  func_8012BD14(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012CC64(s32 a0, s32 a1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32  func_80143B6C(s32 a0, s32 a1);   /* fleet-canonical */
extern void func_8018956C(s32 a0, s32 a1);


void func_80188AC0(s32 param_1) {

    extern u8 D_801BC580;
    s32 v0;
    s32 iVar;

    if (0xf < *(s16 *)(param_1 + 0xA)) {
        ((void (*)(void *))func_8012C218)((void *)param_1);
        return;
    }
    v0 = func_8012BD14(param_1);
    if (v0 < 0x1001) {
        goto LAB_tail;
    }
    if (*(u16 *)(param_1 + 0x34) == 0) {
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) - 0x40;
        v0 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801BC580);
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
    func_8018956C(param_1, 0);
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_80188BF8);


// @class: struct
// @stuck: none — MATCH (276 ins, relocation-masked). Verified BOTH standalone (match_one) and
//          spliced into src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c (whole-TU cc1 -O2 clean,
//          masked structured_diff 0/276).
// Keys: (1) the first func_8012C218 call gets a NOP delay slot because reload_cse_regs deletes the
//           redundant `move a0,s1` -- $a0 still holds the incoming param on the fall-through path
//           (no CODE_LABEL between the prologue and the jal). The second call site is behind a
//           label, so the move survives. Source is the natural `((void (*)(void *))func_8012C218)((void *)param_1)` at
//           BOTH sites -- do NOT write a zero-arg call (it also breaks in-TU: the composite type
//           from the earlier file-scope `extern void ((void (*)(void *))func_8012C218)(void *a0);` rejects 0 args).
//       (2) case 0's guard is an `||` with an early return -- that is what puts `beqz -> fail` then
//           `beq -> ok` (an `&&` would emit `bne -> fail`).
//       (3) `register s32 sVar2 __asm__("$2")` holds the p+0x34 reload in cases 1/2 so the two arms
//           cross-jump into the shared .L80188928 tail.
//       (4) `__asm__ __volatile__("")` after the func_8012C658 arm forces the `lw v1,0x1C(s1)`
//           reload before the cross-jumped `li v0,9` (§21 zero-byte re-tie).
//       (5) `-((iVar3 << 0x10) / 0x22)` reproduces the 0x78787879/sra-4 magic-divide by 34 + negu.
//       (6) `*p * 0xc` then `>>4` with the manual `if (x<0) x+=0xf` is the /16 rounding form.

extern void func_8012C218(s32);
extern void func_801898EC(s32, void*, void*, s32);
extern s32  func_80013328(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CC64(s32 a0, s32 a1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32 func_8012C658(s32, s32, s32);
extern s32  func_80143B6C(s32 a0, s32 a1);   /* fleet-canonical */
extern s32  func_8012BEE8(s32 a0);
extern void func_80016714(void*, s32);
extern void func_8018956C(s32 a0, s32 a1);


void func_80188C1C(s32 param_1) {

    extern u8 D_801D4314;
    extern u8 D_801BC588;
    extern u8 D_801BC590;
    extern u8 D_801BC580;
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
        ((void (*)(void *))func_8012C218)((void *)param_1);
        return;
    }
    uVar1 = *(u16 *)(param_1 + 0x34);
    switch (uVar1) {
    case 0:
        psVar5 = *(s32 *)(param_1 + 0x64);
        if ((*(u16 *)psVar5 == 0) ||
            (*(s32 *)(psVar5 + 0x90) != (s32)&D_801D4314)) {
            ((void (*)(void *))func_8012C218)((void *)param_1);
            return;
        }
        if (*(s32 *)(psVar5 + 0x94) < 0x11) {
            ((void (*)(void *, void *, void *, s32))func_801898EC)((void *)psVar5, (void *)&D_801BC588, buf, 5);
            *(s16 *)(param_1 + 6) = buf[0];
            *(s16 *)(param_1 + 0xA) = buf[1];
            *(s16 *)(param_1 + 0xE) = buf[2];
            return;
        }
        ((void (*)(void *, void *, void *, s32))func_801898EC)((void *)psVar5, (void *)&D_801BC590, buf, 4);
        ((void (*)(void *, void *, void *, s32))func_801898EC)((void *)psVar5, (void *)&D_801BC590, &buf[4], 5);
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
        iVar3 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801BC580);
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
        uVar4 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801BC580);
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
        func_8018956C(param_1, 0);
        return;
    }
    return;
}



extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern void func_8012B260(u8 *a0);

void func_8018906C(s32 p) {
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


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_80189108);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_801892C0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_801892FC);


/* func_8018937C @ ov_SC06_018 (subseg ov_SC06_018_jr_8017C24C) — 124 ins. MATCH.
 *
 * GATE: .venv/bin/python tools/match_one.py func_8018937C \
 *         --c .run/wave-s40/ov_SC06_018/func_8018937C.c \
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
 *      state 9 and func_8018956C(e, 0); return 1.  No hit -> 0.
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
 *     `sh 9; jal func_8018956C; return 1` block.  Keep them identical.
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
 * `extern void func_8018956C(s32 a0, s32 a1);` (L7388, and DEFINES it at L7711)
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
 * is func_8018956C, and in this overlay it is defined in the SAME TU
 * (ov_SC06_018_jr_8017C24C.c:7711).  So the §40 remap for the siblings is
 * expected to be near-identity: re-point func_8018956C at each sibling's own
 * address and check that sibling TU's canonical spellings for the four externs
 * before sweeping (§56b — carry the TU's types, not this draft's).
 */

typedef struct { u16 x, y, z, w; } V4_80188E10_8018937C;

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
} Ent_80188E10_8018937C;

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8018956C(s32 a0, s32 a1);


s32 func_8018937C(Ent_80188E10_8018937C *self, s32 arg1, s32 arg2, s32 arg3, u16 kind) {

    extern s32 *D_80126B78;
    extern s32 *D_80126B90;
    extern u8   D_801152A8[];
    extern u8   D_801202A0[];
    V4_80188E10_8018937C a;              /* 0x18(sp) */
    V4_80188E10_8018937C b;              /* 0x20(sp) */
    V4_80188E10_8018937C c;              /* 0x28(sp) */
    Ent_80188E10_8018937C *e;
    s32 i;

    func_8012F214((s32)self, arg1, (s32)&a);
    func_8012F214((s32)self, arg2, (s32)&b);
    c = b;                                              /* L2: lwl/lwr block move */
    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&a, (s32)&b) != 0) {
        func_8012F568(1, 1, *(s16 *)(self->f20 + 0x12), arg3, (s32)&b, (s32)D_801152A8);
        return 1;
    }
    e = (Ent_80188E10_8018937C *)D_801202A0;
    if (kind != 0xFFFF) {                               /* L3 */
        for (i = 0; i < 0x60; i++, e++) {               /* L2: i=0 HERE, not above */
            if (e->f0 == 0x282 && (e->f70 == kind || e->f70 == self->f70) && e != self &&
                func_80135888(e->f20, e->f58, (s32)&a, (s32)&c) != 0) {
                e->f2 = 9;                              /* L4: keep identical */
                func_8018956C((s32)e, 0);
                return 1;
            }
        }
        return 0;
    } else {
        for (i = 0; i < 0x60; i++, e++) {               /* L2 */
            if (e->f0 == 0x282 && e->f70 == self->f70 && e != self &&
                func_80135888(e->f20, e->f58, (s32)&a, (s32)&c) != 0) {
                e->f2 = 9;                              /* L4: keep identical */
                func_8018956C((s32)e, 0);
                return 1;
            }
        }
        return 0;
    }
}



extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern s32 func_8012C658(s32, s32, s32);
extern void func_8018A3CC(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018956C(s32 a0, s32 a1) {
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

    func_8018A3CC(a0, 0x95e);
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_801897F0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_80189888);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_801898EC);


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
s32 aF80189938(s32 a0, s16 a1) __asm__("func_80189938");
s32 aF80189938(s32 a0, s16 a1)
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


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_801899B8);


extern void (*D_801BC61C[])(void);

void func_80189A20(void *a0) {
    D_801BC61C[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 rand(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_80189A5C(s32 param_1) {

    extern u8 D_801BC624[];
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
    tbl = &D_801BC624[(*(u16 *)(param_1 + 0x70) & 0xF) * 4];

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



extern s32  func_8012CBF4(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012C218(s32);
extern void func_80017274(s32 a0, s32 a1);

void func_80189EC0(s32 param_1) {
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + *(u16 *)(param_1 + 0xFE);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + *(u16 *)(param_1 + 0x100);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + *(u16 *)(param_1 + 0x102);

    if (func_8012CBF4(param_1) != 0 || func_8012BEE8(param_1) != 0) {
        ((void (*)(void *))func_8012C218)((void *)param_1);
    } else {
        func_80017274(param_1 + 0xDC, *(s32 *)(param_1 + 0x20) + 0x34);
    }
}



extern void (*D_801BC63C[])(void);

void func_80189F64(void *a0) {
    D_801BC63C[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32  rand(void);
extern void func_8012C1B8(void);   /* TU-canonical (ov_SC06_018_jr_8017C24C) */
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);  /* TU-canonical */
extern void func_8012B2CC(s32 a0);

void func_80189FA0(s32 param_1) {
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
extern void func_8012C218(s32);
extern s32 func_80017758(void *a0, void *a1);

void func_8018A194(void *a0)
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
            ((void (*)(void *))func_8012C218)(a0);
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


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018A2D0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018A3CC);


extern void (*D_801BC648[])(void);

void func_8018A538(void *a0) {
    D_801BC648[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018A574(s32 param_1) {

    extern u8 D_800D387C[];
    extern u8 D_800D3888[];
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



extern void func_8012931C(s32 a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(u8*);

void func_8018A624(s32 param_1) {
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
        ((void (*)(s32))func_801292C8)(param_1);
    }
}



extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_8018A6DC(s32 a0, s32 a1) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801E17F0;
    D_801E17F0 = a1;
    return func_8012C588(0x85, a0);
}


extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(s32);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80134510(s32 arg);

// @class: regalloc-order
// @stuck: none — MATCH (145/145 ins, match_one confirmed)




s32 func_8018A70C(s32 param_1) {

    extern u8 D_801152A8[];
    extern M2C_UNK D_8018FB1C;
    extern s32 D_801E17F0;
    extern s32 func_8012C354(s32, void*);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801D4450;
    extern char * D_801D4484;
    extern char D_801E17D0[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801D4450) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_8018FB1C));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801E17F0, &s60);
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
        register char *tmp __asm__("$2");
        tmp = D_801D4484;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801D4484 = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801E17D0 < puVar4) {
        D_801D4484 = D_801E17D0 - 0x120;
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
            register char *tmp __asm__("$3");
            tmp = D_801D4484;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801D4484 = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801E17D0 < puVar4) {
            D_801D4484 = D_801E17D0 - 0x120;
        }
        func_800D23D0(&(*(s32 *)&D_801152A8));
        ((void(*)(void *, void *))RotMatrixYXZ)(&(*(s32 *)&D_801152A8), puVar2);
        ((void (*)(void *, s32))func_80017E68)(&s50, (s32)puVar2);
    }
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


extern s32 func_80017758(void *a0, void *a1);
extern void func_8012C218(s32);
//   (3) counter is `short i` do-while (keeps the `addu $s2,$v0,$0` raw-copy + sll16/sra16 compare);
//   (4) gcc-2.7.2 loads s8/s16 via lbu/lhu+shift-extend (not lb/lh) so `signed char *p; *(s16*)buf=*p++`
//   emits lbu;sll24;sra24;sh; (5) else-branch zero-byte asm barrier forces `addu $a0,$s1,$0` (else gcc
//   reuses the still-live incoming $a0 with a nop delay slot).

s32 func_8018A950(s32 param_1) {

    extern signed char D_801D443C[];
    register int self __asm__("$17") = ((int)param_1);
    int iVar6;
    int iVar1;
    unsigned char buf[0x34];
    signed char *p;
    short i;
    int dest;
    int td;
    unsigned short t;

    iVar1 = *(int *)(self + 0x1c);
    iVar6 = *(int *)(self + 0x20);
    *(int *)(self + 0x1c) = iVar1 + 1;
    if (iVar1 < 2) {
        p = D_801D443C;
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
            p = D_801D443C;
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
        *(short *)(self + 0x70) = *(short *)(self + 0x70) >> 1;
        *(unsigned short *)(iVar6 + 0x2c) |= 1;
    } else {
        __asm__ __volatile__("" : "=r"(self) : "0"(self));
        ((void (*)(void *))func_8012C218)((void *)self);
    }
}



extern void (*D_801D4488[])(void);

void func_8018ABF0(void *a0) {
    D_801D4488[*(u16 *)((s32)a0 + 0x2)]();
}




// @class: schedule
// @stuck: none — MATCH (132 ins, match_one). Levers: (1) block2 statement order — compute sv1.vz (with the *(p+0xe) load) right after the 2nd call so gcc hoists that load into $v1, forcing the sv2.vx=sv1.vx copy through $a3, which globally pushes every `func*param>>12` product from $a3 to $t0; (2) sv2 store order vx-before-vy; (3) SHARED return-0 join via gotos placed BEFORE the copy block (ret0: before docopy:) — this blocks gcc's conditional-jump-over-jump inversion + return-threading, so the copy block falls through to the epilogue with v0=1 preset in the beqz delay slot (drops the extra `li v0,1`).


extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);

int func_8018AC2C(int param_1, short param_2)
{
    int iVar1;
    unsigned int uVar2;
    int iVar3;
    SVECTOR sv1;
    SVECTOR sv2;

    if (*(int *)(param_1 + 0xdc) != 0) goto ret0;
    sv1.vx = *(short *)(param_1 + 6);
    sv1.vy = *(short *)(param_1 + 0xa) + -0x20;
    sv1.vz = *(short *)(param_1 + 0xe);
    iVar1 = func_8004787C(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
    iVar3 = (int)param_2;
    sv2.vy = sv1.vy;
    sv2.vx = sv1.vx - (short)(iVar1 * iVar3 >> 0xc);
    iVar1 = func_80047948(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
    sv2.vz = sv1.vz - (short)(iVar1 * iVar3 >> 0xc);
    uVar2 = ((int (*)(int, SVECTOR *, SVECTOR *))func_80133784)(1, &sv1, &sv2);
    if ((uVar2 & 0x8000) != 0) {
        iVar1 = func_8004787C(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
        *(short *)(param_1 + 6) = sv2.vx + (short)(iVar1 * iVar3 >> 0xc);
        iVar1 = func_80047948(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
        *(short *)(param_1 + 0xe) = sv2.vz + (short)(iVar1 * iVar3 >> 0xc);
        return 1;
    }
    iVar1 = func_8004787C(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
    sv1.vx = *(short *)(param_1 + 6) - (short)(iVar1 * iVar3 >> 0xc);
    sv1.vy = *(short *)(param_1 + 0xa) + -0x10;
    iVar1 = func_80047948(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
    sv1.vz = *(short *)(param_1 + 0xe) - (short)(iVar1 * iVar3 >> 0xc);
    sv2.vx = sv1.vx;
    sv2.vy = sv1.vy + 0x20;
    sv2.vz = sv1.vz;
    uVar2 = ((int (*)(int, SVECTOR *, SVECTOR *))func_80133784)(1, &sv1, &sv2);
    if ((uVar2 & 0x6000) == 0) goto docopy;
ret0:
    return 0;
docopy:
    *(int *)(param_1 + 4) = *(int *)(param_1 + 0x38);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 0x3c);
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0x40);
    return 1;
}




/* func_8018AE3C — ov_SC06_008 / ov_SC06_008_jr_8017C294
 *
 * Two-arm actor tick keyed on the s16 countdown at actor+0xFC:
 *   arm A (counter == 0, the FALL-THROUGH / longer block): three func_8012C658
 *     spawns with offset pokes, a sound cue, two child-actor state pokes, an
 *     8-iteration 0x281 particle burst, then the RTP positional-sound block
 *     (the byte-proven RTP_SND shape from ov_SC03_099_jr_8017BEBC.c:5406).
 *   arm B (counter != 0): a func_8012913C(0x23) spawn scattered around the
 *     actor, VectorNormalSS toward D_801151D4->{0x5C,0x60,0x64}, sound 0xAF8.
 *
 * Declarations copied VERBATIM from the TU (one-pass grep, D2):
 *   D_801151D4      src/ov_SC06_008/ov_SC06_008_jr_8017C294.c:323
 *   rand            :956
 *   VectorNormalSS  :1849
 *   func_8012C658   :2523
 *   func_8012C588   :3767
 *   func_8012C218   :3782
 *   func_8002D4C8   :59
 *   func_8004914C   :2645
 *   func_800491AC   :2646
 *   func_8012913C   :4356  (non-prototype form, BELOW the splice point)
 *   func_8002AC00   :5447  (block-scope extern only)
 * RotTransPers / D_800AF648 / func_8002A04C are not in this TU -> fleet-dominant forms.
 */

extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8  *func_8012913C();

void func_8018AE3C(s32 a0)
{

    extern s32  D_801151D4;
    extern u8 D_800AF648;

    /* L5: slot offsets are exact only through ONE struct — plain array locals
       get 8-byte-rounded slots and pushed z/flag to 0x28/0x2C (measured). */
    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 rv[4];   /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;

    s32 g;
    s32 s0;
    s32 i;

    g = D_801151D4;

    if (*(s16 *)(a0 + 0xFC) == 0) {
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) - 5;
        }
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) + 5;
        }
        s0 = func_8012C658(0x32, 2, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) + 8;
        }
        func_8002AC00(0x22);

        s0 = *(s32 *)(a0 + 0xCC);
        *(s16 *)(s0 + 0x2)  = 2;
        *(s16 *)(s0 + 0xFC) = 1;
        s0 = *(s32 *)(a0 + 0xD0);
        *(s16 *)(s0 + 0x2)  = 2;
        *(s16 *)(s0 + 0xFC) = 1;

        for (i = 0; i < 8; i++) {
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x30;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }

        L.rv[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.rv[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.rv[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.rv, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                      && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
            s32 x = (s16)L.sxy[0];
            s32 ax;

            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xF0 - ax) * 0x7F) / 0xF0;
            __asm__("" : "=r"(ax) : "0"(ax));
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            {
                s32 flg = 0x3000;
                func_8002D4C8(0x961, ((ax | flg) | x) & 0xFFFF);
            }
        }
        func_8002A04C(a0);
        ((void (*)(void *))func_8012C218)((void *)a0);
    } else {
        s0 = (s32)func_8012913C(0x23);
        if (s0 != 0) {
            *(s16 *)(s0 + 0x6) = *(u16 *)(a0 + 0x6) + (rand() & 0x7F) - 0x40;
            *(s16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA) + (rand() & 0x7F) - 0xE0;
            {
                s32 r = rand();
                s32 t = *(u16 *)(a0 + 0xE);
                *(s16 *)(s0 + 0x34) = 0x1800;
                *(s32 *)(s0 + 0x18) = 0;
                *(s32 *)(s0 + 0x14) = 0;
                *(s32 *)(s0 + 0x10) = 0;
                *(s16 *)(s0 + 0xE) = t + (r & 0x7F) - 0x40;
            }
            L.nv[0] = *(s32 *)(g + 0x5C) - *(u16 *)(s0 + 0x6);
            L.nv[1] = *(s32 *)(g + 0x60) - *(u16 *)(s0 + 0xA);
            L.nv[2] = *(s32 *)(g + 0x64) - *(u16 *)(s0 + 0xE);
            VectorNormalSS(L.nv, L.nv);
            *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)L.nv[0] >> 6);
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)L.nv[1] >> 6);
            *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)L.nv[2] >> 6);
            *(s16 *)(s0 + 0x34) = 0x3000;
            func_8002D4C8(0xAF8, 0);
        }
        *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) - 1;
    }
}




// TARGET: func_8018B240  (ov_SC06_008, TU ov_SC06_008_jr_8017C294.c, 93 ins)
//
// Template: func_801821F8 in this SAME TU (src/ov_SC06_008/ov_SC06_008_jr_8017C294.c,
// around line 5283) is an already-MATCHED sibling (126 ins) with a documented byte-exact
// idiom set (its comment, verbatim):
//   @class: plumbing
//   @stuck: none — MATCH (126 ins). Keys: (1) cVar1 as `int` (not unsigned char) so the
//     lbu-loaded byte stays full-width and gcc omits the per-compare `andi 0xff`; (2) uninitialized
//     `int unaff_s1` -> $s1 (live-from-entry across func_8002D4C8); (3) func_8016AA50 takes TWO args
//     (param_1, unaff_s1) — a1=unaff_s1 arg-setup is reused by the preceding subtraction and a0=s0
//     hoists into the branch delay slot; (4) 0x76 read UNSIGNED (lhu) in the subtract, SIGNED (lh) in
//     the `< 1` test.
//
// func_8018B240 is the SAME body with the leading "if (*(short*)(param_1+0xfc)==0) {...}" block
// (the 0x64-indirected 3x int-copy + 3x u16-copy prologue) removed, and the "already fired" gate
// field is 0xe2 instead of 0x102. Confirmed against the target .s: no reference anywhere to 0xfc,
// 0x64, or 0x102/0x20 offsets; the gate compare is `lh $v1, 0xE2($s0)` / `sh $v1(=0xA), 0xE2($s0)`.

extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);

void func_8018B240(int param_1)
{
    extern unsigned char D_801D4B7C[];
    int cVar1;
    int unaff_s1;

    cVar1 = *(unsigned char *)(param_1 + 0x5e);
    *(char *)(param_1 + 0xc1) = 0;
    *(short *)(param_1 + 0x5e) = 0;
    *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) & 0xfffe;
    if (*(short *)(param_1 + 0xe2) == 0) {
        *(short *)(param_1 + 0xe2) = 10;
        *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) | 0x4000;
        func_8002D4C8(0x9b7, 0);
        if (*(short *)(param_1 + 0x60) != 0) {
            if (cVar1 == 0x1d) {
                *(short *)(param_1 + 0x82) = 0;
                *(short *)(param_1 + 0x7c) = *(unsigned short *)(param_1 + 6);
                *(short *)(param_1 + 0x7e) = *(unsigned short *)(param_1 + 0xa);
                *(short *)(param_1 + 0x80) = *(unsigned short *)(param_1 + 0xe);
            }
            if (*(int *)(param_1 + 0x78) != 0) {
                unaff_s1 = (int)*(short *)(param_1 + 0x60) *
                           (int)*(short *)(*(int *)(param_1 + 0x78) + 0x30) >> 0xc;
                if (unaff_s1 < 1) {
                    unaff_s1 = 1;
                }
            }
            *(unsigned short *)(param_1 + 0x76) =
                *(unsigned short *)(param_1 + 0x76) - unaff_s1;
            func_8016AA50(param_1, unaff_s1);
            if ((*(unsigned short *)(param_1 + 0x82) & 1) != 0) {
                ((void (*)(int))func_8016B428)(param_1);
                func_80019064(D_801D4B7C);
            }
        }
        if (cVar1 != 0x1d) {
            if (*(unsigned char *)(param_1 + 0xc8) != 0) {
                func_8002A520(param_1);
            }
            if (*(unsigned char *)(param_1 + 0xc9) != 0) {
                func_8002A790(param_1);
            }
        }
        if (*(short *)(param_1 + 0x76) < 1) {
            *(short *)(param_1 + 0x5c) = 0;
            func_80131E00(param_1, 6);
        }
    }
    return;
}



// @class: schedule
// @stuck: none — MATCH; success-block placed last via `goto big` (bnez forward into epilogue), single cae4 merge kept

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


void func_8018B3B4(int param_1) {

    extern u8 D_801D4B9C[];
    extern u8 D_801D4AE0[];
    extern u8 D_801D4AA0[];
    extern u8 D_801D4AE8[];
    extern u8 D_801D4AC0[];
    extern u8 D_801D8E08[];
    extern u8 D_801DC0B8[];
    extern u8 D_801D4BDC[];
    extern u8 D_801DBF20[];
    extern u8 D_801DBFA8[];
    extern u8 D_801DC030[];
    int iVar1;

    iVar1 = func_8012C354(param_1, D_801D4B9C);
    if (iVar1 != 0) {
        if (*(short *)(param_1 + 0x70) != 0) {
            func_800599B8(D_801D4AE0, D_801D4AA0);
            func_800599B8(D_801D4AE8, D_801D4AC0);
            func_8001C214(*(int *)(param_1 + 0x20), D_801D8E08);
        }
        *(u8 *)(param_1 + 0xc0) = 1;
        *(int *)(param_1 + 0xb4) = 0xffffdfde;
        func_80143970(param_1);
        func_8012B030(param_1);
        *(short *)(param_1 + 0xae) = 0x2100;
        func_8012A828(param_1, D_801DC0B8);
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
        func_8012B23C(param_1);
        *(u32 *)(param_1 + 0xc4) = *(u32 *)(param_1 + 0xc4) | 2;
        iVar1 = func_8012C658(0x26f, (int)*(short *)(param_1 + 0x70), param_1);
        if (iVar1 != 0) {
            *(int *)(param_1 + 0xcc) = iVar1;
            iVar1 = func_8012C658(0x270, (int)*(short *)(param_1 + 0x70), param_1);
            if (iVar1 != 0) goto big;
            func_8012C218(*(int *)(param_1 + 0xcc));
        }
        func_8012CAE4(param_1);
    }
    return;
big:
    *(int *)(param_1 + 0xd0) = iVar1;
    *(u32 *)(param_1 + 0xbc) = (u32)D_801D4BDC;
    *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) =
        *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) | 0x10;
    *(short *)(*(int *)(param_1 + 0x20) + 0x18) = 0x2400;
    *(short *)(*(int *)(param_1 + 0x20) + 0x1a) = 0x2400;
    *(short *)(*(int *)(param_1 + 0x20) + 0x1c) = 0x2400;
    *(u16 *)(param_1 + 2) = 8;
    func_8012A828(param_1, D_801DBF20);
    func_8012A828(*(int *)(param_1 + 0xcc), D_801DBFA8);
    func_8012A828(*(int *)(param_1 + 0xd0), D_801DC030);
    return;
}



/* func_8018B564 — ov_SC06_008 / ov_SC06_008_jr_8017C294.  MATCH 163/163.
 * Family of 7 (ov_SC06_008/010/018/022/024/032/033, all 163 ins, all still in
 * nonmatchings) — §136e applies: no twin existed, so this is derived from the .s.
 * The byte-proven accumulate head (b744 nested inside b608, then two RE-LOADS of
 * *(s32*)(a0+0x20)) is copied verbatim from src/ov_SC03_099/..._jr_8017BEBC.c:5424.
 *
 * Four levers, each measured against match_one:
 *
 * 1. NO frame padding.  args_size already fills sp+0x00..0x1F, so the four saved
 *    regs land at 0x20..0x2F and the frame is 0x30 with ZERO locals.  A 16-byte
 *    dead aggregate (idiom 6, added on the first draft from a mis-derived
 *    args_size=0x10) made it 0x40 — idiom 6 only applies when the reg-save area
 *    does NOT start at args_size.
 *
 * 2. BRANCH POLARITY / BLOCK LAYOUT (§3-T4, T7).  `if (C) goto X;` followed by a
 *    `break` is REWRITTEN by jump.c's jump-around-jump inversion into
 *    `if (!C) goto break_target;` — which is the wrong polarity here.  The target
 *    wants the true arm to FALL THROUGH.  Two rewrites, both worth +0 instructions
 *    but different bytes:
 *      case 1: `if (A||B) goto st2; break;`  ->  `if (!A && !B) break; goto st2;`
 *              (TRUTH_ANDIF gives reversed branches to `next`, and the trailing
 *               `j st2` is the fall-through — exactly `beqz L600 / j L5E0`.)
 *      case 3: same shape, plus the range test written as the POSITIVE
 *              `if (r >= -0xFF && r <= 0xFF) break;` so fold_range_test's
 *              `sltiu (r+0xFF),0x1FF` branches on TRUE to the switch end and case 3
 *              falls through into st2 (saves the `j`+`nop`, 165 -> 163 ins).
 *    Case 0 keeps the plain `if (A||B) {..} else {..}` — there jump.c's inversion
 *    IS what the target has.
 *
 * 3. THE SHARED STORE BLOCK.  L801815F8/L801815FC (`li v0,1` / `sh v0,0x34`) sit
 *    AFTER st2 in the target, so they are NOT inline `else` arms (cross-jumping
 *    keeps the LAST copy, which would put them BEFORE st2).  They are explicit
 *    trailing labels inside the switch with an `ns` join variable; case 2 enters at
 *    `setstate` with ns=3, cases 0 and 3 enter at `set1`.
 *
 * 4. REGALLOC-PERM -> the $16 pin (see below).
 */

extern s32 rand(void);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012BE54(s32 a0);
extern int func_8018AC2C(int param_1, short param_2);

void func_8018B564(s32 a0) {

    extern u8 D_801D4BFC[];

    /* §137/K3+K5: unpinned, the a0-copy allocno (R=37/L=137, pri 13503) is
     * ranked first and first-fits $s0, pushing `tbl` to $s1 — a clean 2-reg
     * perm no source reordering can flip (pri(tbl) = 394). Pinning `tbl` to
     * $16 makes $s0 "already dirty" in find_reg pass 0: the a0 copy conflicts
     * with it and opens $s1, and case 3's `d` (which does NOT conflict with
     * `tbl`) grabs $s0 in pass 0 — exactly the target's assignment. */
    register s32 tbl __asm__("$16");
    s32 ns;

    tbl = (s32)D_801D4BFC;
    func_8012B1B4(a0, tbl);
    func_8012CBCC(a0);

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (func_8018AC2C(a0, 0x48) != 0 ||
            ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88)) >
                0x3FFFF) {
            s32 r = func_8012B608(
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88)), 8);
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
            func_8012B1B4(a0, tbl);
        } else {
            goto set1;
        }
        break;

    case 1:
        if (func_8018AC2C(a0, 0x48) == 0 &&
            ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88)) <=
                0x3FFFF) {
            break;
        }
        goto st2;

    case 2: {
        s32 r = func_8012B608(
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
            func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88)), 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }
        func_8018AC2C(a0, 0x48);
        {
            s16 c = *(s16 *)(a0 + 0x102);
            if (c == 0) {
                ns = 3;
                goto setstate;
            }
            *(s16 *)(a0 + 0x102) = c - 1;
        }
        break;

    case 3: {
        void *p88 = (void *)(a0 + 0x88);
        s32 d = ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)p88);
        if (func_8018AC2C(a0, 0x48) == 0) {
            if (d > 0x40000) {
                s32 r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                                      func_8012B744((void *)(a0 + 4), p88), 1);
                if (r >= -0xFF && r <= 0xFF) {
                    break;
                }
            } else {
                goto set1;
            }
        }
    }
        /* fall through into st2 */
    st2:
        *(u16 *)(a0 + 0x34) = 2;
        *(u16 *)(a0 + 0x102) = (rand() & 7) + 8;
        break;

    set1:
        ns = 1;
    setstate:
        *(u16 *)(a0 + 0x34) = ns;
        break;
    }

    {
        s16 t = *(s16 *)(a0 + 0x100);
        if (t != 0) {
            *(s16 *)(a0 + 0x100) = t - 1;
        } else if (((s32(*)(s32))func_8012BE54)(a0) <= 0x24000) {
            *(s16 *)(a0 + 0x2) = 5;
            *(s16 *)(a0 + 0x100) = 0x3C;
        }
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_8004914C();
extern void func_800491AC();
extern u8 *func_8012913C(s32 a0);
extern void func_8012A828(s32 a0, void * a1);
#define RTP_SND(sndid)                                                        \
    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);                            \
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);                            \
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);                            \
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); } \
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); } \
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);                        \
    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF              \
                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {           \
        s32 x = (s16)L.sxy[0];                                                \
        s32 ax;                                                               \
        ax = x;                                                               \
        if (x < 0) {                                                          \
            ax = -x;                                                          \
        }                                                                     \
        ax = ((0xF0 - ax) * 0x7F) / 0xF0;                                     \
        __asm__("" : "=r"(ax) : "0"(ax));                                     \
        x = (x + 0xF0) / 0x1E;                                                \
        if (x == 0x10) {                                                      \
            x = 0xF;                                                          \
        }                                                                     \
        x = x << 8;                                                           \
        {                                                                     \
            s32 flg = 0x3000;                                                 \
            func_8002D4C8(sndid, ((ax | flg) | x) & 0xFFFF);                  \
        }                                                                     \
    }

void func_8018B7F0(s32 a0) {

    extern u8  D_800AF648;
    extern s32 D_801D4A60[];
    extern u8  D_801DBF20[];
    extern u8  D_801DBFA8[];
    extern u8  D_801DC030[];
    struct {
        s16 pad0[4];  /* sp+0x10 — dead, but sizes the frame (idiom 6) */
        s16 v[3];     /* sp+0x18 */
        s16 pad1;     /* sp+0x1E */
        u16 sxy[2];   /* sp+0x20 */
        s32 z;        /* sp+0x24 */
        s32 flag;     /* sp+0x28 */
    } L;
    s32 t;
    s32 ang;
    s32 idx;
    s32 m;
    s32 c;
    s32 p;

    if (*(s16 *)(a0 + 0x98) == 0) {
        s32 spr = (s32)func_8012913C(0x7F);
        if (spr != 0) {
            m = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)
              + (func_8004787C(*(s16 *)(a0 + 0x104)) >> 3);
            *(s16 *)(spr + 0x6) = *(u16 *)(a0 + 0x6) - (func_8004787C(m) * 0x6C) / 0x1000;
            *(s16 *)(spr + 0xA) = *(u16 *)(a0 + 0xA) - 0x34;
            *(s16 *)(spr + 0xE) = *(u16 *)(a0 + 0xE) - (func_80047948(m) * 0x6C) / 0x1000;
            *(s32 *)(spr + 0x14) = 0x40000;
            *(s32 *)(spr + 0x10) = -(func_8004787C(m) * 0xC0);
            *(s32 *)(spr + 0x18) = -(func_80047948(m) * 0xC0);
        }
        t = *(u16 *)(a0 + 0x104) + 0x100;
        *(s16 *)(a0 + 0x104) = t;
        ang = (s16)t;
        idx = ang / 0x100;
        m = (s16)(idx % 0x10);
        if (ang == 0x100) {
            RTP_SND(0x95F)
        } else if (m == 0) {
            RTP_SND(0x960)
        }
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = D_801D4A60[m];
        c = *(u16 *)(a0 + 0x100) - 1;
        *(s16 *)(a0 + 0x100) = c;
        if ((s16)c == 0) {
            p = *(s32 *)(a0 + 0xCC);
            *(s16 *)(a0 + 0x98) = 1;
            if (p != 0) {
                *(s16 *)(p + 0x98) = 1;
            }
            p = *(s32 *)(a0 + 0xD0);
            if (p != 0) {
                *(s16 *)(p + 0x98) = 1;
            }
        }
    } else if ((*(u16 *)(a0 + 0x72) & 0x4000) != 0) {
        *(s16 *)(a0 + 0x2) = 7;
        *(s16 *)(a0 + 0x100) = 0x3C;
        func_8012A828(a0, D_801DBF20);
        p = *(s32 *)(a0 + 0xCC);
        if (p != 0) {
            func_8012A828(p, D_801DBFA8);
        }
        p = *(s32 *)(a0 + 0xD0);
        if (p != 0) {
            func_8012A828(p, D_801DC030);
        }
    }
}



extern void func_8012B370(int a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018BCB4(s32 a0) {

    extern u8   D_800AF648;

    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    s16 hp;
    s32 p;

    hp = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14);
    if (hp < 0x301) {
        s32 count;
        s32 total;

        count = *(u16 *)(a0 + 0xFC);
        total = *(u16 *)(a0 + 0xFE);
        count = count + 1;
        total = total + count;
        *(u16 *)(a0 + 0xFC) = count;
        *(u16 *)(a0 + 0xFE) = total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) + total;
    } else {
        p = *(s32 *)(a0 + 0xD0);
        *(s16 *)(a0 + 2) = 3;
        *(s32 *)(a0 + 0x1C) = 0x1E;
        *(s16 *)(a0 + 0x98) = 0;
        *(s16 *)(p + 2) = 3;
        *(s32 *)(p + 0x1C) = 0x1E;
        *(s16 *)(p + 0x98) = 0;

        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                        && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
            s32 x = (s16)L.sxy[0];
            s32 ax;
            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xF0 - ax) * 0x7F) / 0xF0;
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            func_8002D4C8(0x961, (ax | (0x3000 | x)) & 0xFFFF);
        }
    }
    func_8012B370(a0);
}


extern s32 func_801823F0(void);

/* func_8018BE84 -- ov_SC06_008, TU ov_SC06_008_jr_8017C294.c (family of 7)
 *
 * Low-HP flinch/knockback reaction. hp = *(s16*)(a0->0x20 ptr + 0x14). If
 * 0 < hp < 0xD00, put self AND the partner at a0->0xCC into stagger state 3
 * (a 0x1E-frame timer, status flag cleared), compute a screen-space
 * position via RotTransPers and play a positional sound. Otherwise
 * (hp==0 or hp>=0xD00) apply the accumulated hit-combo counter (0xFC/0xFE)
 * to the target's HP and re-mask its low 12 bits.
 *
 * §136c sibling-first: the RTP + positional-sound tail is the byte-proven
 * RTP_SND form from func_8018165C in this same TU (line 4746) -- v[]/pad,
 * u16 sxy[2], s32 z, s32 flag, and the ax/x div-by-0xF0 / div-by-0x1E
 * magic-constant idiom (0x88888889); also confirmed against func_801823F0
 * (same TU) which reuses the identical sndid 0x961 and the identical
 * `sx = (sx + 0xF0) / 0x1E; if (sx == 0x10) sx = 0xF; sx <<= 8;` tail.
 *
 * Control flow: gcc-2.7.2 lays out basic blocks in literal SOURCE order, not
 * by fallthrough-preference. A nested-if spelling (`if (hp<0xD00) { state=3;
 * if (hp!=0) { B; goto end; } } A; end:`) places B (textually the inner
 * then-body) inline right after the tests and relocates A after it -- the
 * REVERSE of the target, which has the short block A inline and the long
 * RTP+sound block B out-of-line. Explicit goto/label with A written BEFORE B
 * in source (`if (hp>=0xD00) goto L_A; state=3; if (hp!=0) goto L_B; L_A: A;
 * goto L_end; L_B: B; L_end: ...`) reproduces the target's physical layout
 * directly -- no branch-polarity inversion needed, just source ORDER.
 *
 * Frame: RotTransPers args are sp+0x10 (v), sp+0x18 (&sxy), sp+0x1C (&z),
 * sp+0x20 (&flag); v[3]+pad1 fills 0x10-0x17, sxy 0x18-0x1B, z 0x1C-0x1F,
 * flag 0x20-0x23 -- leaves a dead 4 bytes (0x24-0x27) before the s0 save at
 * 0x28. A trailing `pad2` dead struct member (same aggregate, so it can't
 * be eliminated) reserves those 4 bytes, mirroring func_8018165C's own
 * "dead aggregate sizes the frame" idiom (comment there: idiom 6).
 */

extern void func_8012B370(int a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018BE84(s32 a0) {

    extern u8   D_800AF648;

    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
        s32 pad2;    /* sp+0x24 -- dead, sizes the frame */
    } L;

    s16 hp;
    s32 state;
    s32 p;

    hp = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14);
    if (hp >= 0xD00) {
        goto L_A;
    }
    state = 3;
    if (hp != 0) {
        goto L_B;
    }

L_A:
    {
        s32 count;
        s32 total;

        count = *(u16 *)(a0 + 0xFC);
        total = *(u16 *)(a0 + 0xFE);
        count = count + 1;
        total = total + count;
        *(u16 *)(a0 + 0xFC) = count;
        *(u16 *)(a0 + 0xFE) = total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) - total;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) & 0xFFF;
    }
    goto L_end;

L_B:
    p = *(s32 *)(a0 + 0xCC);
    *(s16 *)(a0 + 2) = state;
    *(s32 *)(a0 + 0x1C) = 0x1E;
    *(s16 *)(a0 + 0x98) = 0;
    *(s16 *)(p + 2) = state;
    *(s32 *)(p + 0x1C) = 0x1E;
    *(s16 *)(p + 0x98) = 0;

    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
        s32 sx = (s16)L.sxy[0];
        s32 av;
        av = sx;
        if (sx < 0) {
            av = -sx;
        }
        av = ((0xF0 - av) * 0x7F) / 0xF0;
        sx = (sx + 0xF0) / 0x1E;
        if (sx == 0x10) {
            sx = 0xF;
        }
        sx = sx << 8;
        func_8002D4C8(0x961, (av | (0x3000 | sx)) & 0xFFFF);
    }

L_end:
    func_8012B370(a0);
}


extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void *param_1);
extern void func_8012C218(s32);
extern int func_80143C74(short *, int);
extern s32 rand(void);

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018C074(s32 a0)
{

    extern void (*D_801D4C0C[])(void);
    extern u8 D_800AF648;
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
    } L;

    D_801D4C0C[*(u16 *)(a0 + 0x2)]();

    if (*(u16 *)(a0 + 0x0) != 0) {
        if (*(s16 *)(a0 + 0x70) == 0 && func_8012C044(a0) != 0) {
            if (*(s32 *)(a0 + 0xCC) != 0) {
                ((void (*)(void *))func_8012C218)(*(void **)(a0 + 0xCC));
            }
            if (*(s32 *)(a0 + 0xD0) != 0) {
                ((void (*)(void *))func_8012C218)(*(void **)(a0 + 0xD0));
            }
            func_8012C098((void *)a0);
        } else {
            s16 v;

            v = *(s16 *)(a0 + 0xE2);
            if (v != 0) {
                v = v - 1;
                *(s16 *)(a0 + 0xE2) = v;
                if (v == 0) {
                    *(u16 *)(a0 + 0x5C) &= 0xBFFF;
                }
            }

            if ((*(s16 *)(a0 + 0x76) < 5) && ((rand() & 3) == 0)) {
                s32 iVar2 = ((s32 (*)(s32, s32))func_80143C74)(a0, 0);
                s32 r;

                if (iVar2 != 0) {
                    r = rand();
                    *(s32 *)(iVar2 + 0x10) = ((r & 0x7FF) - 0x400) << 8;
                    *(s32 *)(iVar2 + 0x14) = 0xFFF00000;
                    r = rand();
                    *(s32 *)(iVar2 + 0x18) = ((r & 0x7FF) - 0x400) << 8;
                    r = rand();
                    *(u16 *)(iVar2 + 0x6) -= 0x20;
                    *(u16 *)(iVar2 + 0x6) += (r & 0x3F);
                    *(s16 *)(iVar2 + 0xA) -= 0xC0;
                    r = rand();
                    *(u16 *)(iVar2 + 0xE) -= 0x20;
                    *(u16 *)(iVar2 + 0xE) += (r & 0x3F);
                }
            }

            if (*(u16 *)(a0 + 0x2) != 1 && *(u16 *)(a0 + 0x2) != 5) {
                *(s16 *)(a0 + 0x84) = 0xE;
            } else {
                if (*(s16 *)(a0 + 0x84) != 0) {
                    *(s16 *)(a0 + 0x84) = *(s16 *)(a0 + 0x84) - 1;
                } else {
                    *(s16 *)(a0 + 0x84) = 0xE;

                    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
                    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
                    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
                    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
                    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
                    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
                    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
                        s32 x = (s16)L.sxy[0];
                        s32 ax;
                        ax = x;
                        if (x < 0) {
                            ax = -x;
                        }
                        ax = ((0xF0 - ax) * 0x7F) / 0xF0;
                        __asm__("" : "=r"(ax) : "0"(ax));
                        x = (x + 0xF0) / 0x1E;
                        if (x == 0x10) {
                            x = 0xF;
                        }
                        x = x << 8;
                        {
                            s32 flg = 0x3000;
                            func_8002D4C8(0x8BF, ((ax | flg) | x) & 0xFFFF);
                        }
                    }
                }
            }
        }
    }
}



// @class: plumbing
// @stuck: none — MATCH (126 ins). Keys: (1) cVar1 as `int` (not unsigned char) so the
//   lbu-loaded byte stays full-width and gcc omits the per-compare `andi 0xff`; (2) uninitialized
//   `int unaff_s1` -> $s1 (live-from-entry across func_8002D4C8); (3) func_8016AA50 takes TWO args
//   (param_1, unaff_s1) — a1=unaff_s1 arg-setup is reused by the preceding subtraction and a0=s0
//   hoists into the branch delay slot; (4) 0x76 read UNSIGNED (lhu) in the subtract, SIGNED (lh) in
//   the `< 1` test.

extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);

void func_8018C38C(int param_1)
{

    extern unsigned char D_801D4B7C[];
    int cVar1;
    int unaff_s1;

    cVar1 = *(unsigned char *)(param_1 + 0x5e);
    *(char *)(param_1 + 0xc1) = 0;
    *(short *)(param_1 + 0x5e) = 0;
    *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) & 0xfffe;
    if (*(short *)(param_1 + 0xfc) == 0) {
        *(int *)(param_1 + 4) = *(int *)(*(int *)(param_1 + 0x64) + 4);
        *(int *)(param_1 + 8) = *(int *)(*(int *)(param_1 + 0x64) + 8);
        *(int *)(param_1 + 0xc) = *(int *)(*(int *)(param_1 + 0x64) + 0xc);
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x10) =
            *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x10);
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) =
            *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x12);
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x14) =
            *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x14);
    }
    if (*(short *)(param_1 + 0x102) == 0) {
        *(short *)(param_1 + 0x102) = 10;
        *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) | 0x4000;
        func_8002D4C8(0x9b7, 0);
        if (*(short *)(param_1 + 0x60) != 0) {
            if (cVar1 == 0x1d) {
                *(short *)(param_1 + 0x82) = 0;
                *(short *)(param_1 + 0x7c) = *(unsigned short *)(param_1 + 6);
                *(short *)(param_1 + 0x7e) = *(unsigned short *)(param_1 + 0xa);
                *(short *)(param_1 + 0x80) = *(unsigned short *)(param_1 + 0xe);
            }
            if (*(int *)(param_1 + 0x78) != 0) {
                unaff_s1 = (int)*(short *)(param_1 + 0x60) *
                           (int)*(short *)(*(int *)(param_1 + 0x78) + 0x30) >> 0xc;
                if (unaff_s1 < 1) {
                    unaff_s1 = 1;
                }
            }
            *(unsigned short *)(param_1 + 0x76) =
                *(unsigned short *)(param_1 + 0x76) - unaff_s1;
            func_8016AA50(param_1, unaff_s1);
            if ((*(unsigned short *)(param_1 + 0x82) & 1) != 0) {
                ((void (*)(int))func_8016B428)(param_1);
                func_80019064(D_801D4B7C);
            }
        }
        if (cVar1 != 0x1d) {
            if (*(unsigned char *)(param_1 + 0xc8) != 0) {
                func_8002A520(param_1);
            }
            if (*(unsigned char *)(param_1 + 0xc9) != 0) {
                func_8002A790(param_1);
            }
        }
        if (*(short *)(param_1 + 0x76) < 1) {
            *(short *)(param_1 + 0x5c) = 0;
            func_80131E00(param_1, 6);
        }
    }
    return;
}





extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(s32);
extern u8 *func_8012913C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 VectorNormalSS(void *a0, void *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018C584(s32 a0) {

    extern s32 D_801151D4;

    extern void func_8002AC00(s32 arg0);
    extern void func_8002A04C(s32 arg0);
    extern u8 D_800AF648;

    u16 v10[4];   /* sp+0x10 */
    s16 v18[4];   /* sp+0x18 */
    s32 sxy;      /* sp+0x20 */
    s32 z;        /* sp+0x24 */
    s32 flag;     /* sp+0x28 */
    s32 base;
    s32 iv;
    s32 i;
    s32 t;
    s32 r;

    base = D_801151D4;

    if (*(s16 *)(a0 + 0xFC) >= 0x1F) {
        iv = func_8012C658(0x33, 3, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) - 8;
            *(u16 *)(iv + 0x1A) = *(u16 *)(iv + 0x1A) - 5;
        }
        iv = func_8012C658(0x33, 3, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) - 8;
            *(u16 *)(iv + 0x1A) = *(u16 *)(iv + 0x1A) + 5;
        }
        iv = func_8012C658(0x32, 2, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) + 8;
        }

        func_8002AC00(0x22);

        iv = *(s32 *)(a0 + 0x64);
        *(s16 *)(iv + 2) = 2;
        iv = *(s32 *)(*(s32 *)(a0 + 0x64) + 0xD0);
        *(s16 *)(iv + 2) = 4;
        *(s32 *)(*(s32 *)(a0 + 0x64) + 0xCC) = 0;

        i = 0;
        do {
            iv = func_8012C588(0x281, a0);
            if (iv != 0) {
                *(s32 *)(iv + 0x1C) = 2;
                *(s16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                *(s16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            i++;
        } while (i < 8);

        v18[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        v18[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        v18[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)v18, (s32)&sxy, &z, &flag);
        if (flag >= 0 && (u32)((*(u16 *)&sxy + 0xEF) & 0xFFFF) < 0x1DF
                      && (u32)((*((u16 *)&sxy + 1) + 0xB3) & 0xFFFF) < 0x167) {
            s32 sx;
            s32 av;

            sx = (s16)*(u16 *)&sxy;
            av = sx;
            if (sx < 0) {
                av = -sx;
            }
            /* one local for |x| AND the volume: gcc-2.7.2 keeps the single pseudo
               in $v1 in place (subu $v1,$v0,$v1); a separate `vol` local steals $a1
               and the whole OR chain drifts (cookbook §136 L1). */
            av = ((0xF0 - av) * 0x7F) / 0xF0;
            sx = (sx + 0xF0) / 0x1E;
            if (sx == 0x10) {
                sx = 0xF;
            }
            sx = sx << 8;
            func_8002D4C8(0x961, (av | (0x3000 | sx)) & 0xFFFF);
        }

        func_8002A04C(a0);
        ((void (*)(void *))func_8012C218)((void *)a0);
        return;
    }

    iv = (s32)func_8012913C(0x23);
    if (iv != 0) {
        r = rand();
        *(u16 *)(iv + 0x06) = *(u16 *)(a0 + 0x06) + (r & 0x7F) - 0x40;
        r = rand();
        *(u16 *)(iv + 0x0A) = *(u16 *)(a0 + 0x0A) + (r & 0x7F) - 0x80;
        r = rand();
        *(u16 *)(iv + 0x0E) = *(u16 *)(a0 + 0x0E) + (r & 0x7F) - 0x40;

        t = func_80047948((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(s32 *)(iv + 0x04) = *(s32 *)(iv + 0x04) + (t << 10);

        t = func_8004787C((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(u16 *)(iv + 0x34) = 0x1800;
        *(s32 *)(iv + 0x18) = 0;
        *(s32 *)(iv + 0x14) = 0;
        *(s32 *)(iv + 0x10) = 0;
        *(s32 *)(iv + 0x0C) = *(s32 *)(iv + 0x0C) - (t << 10);

        v10[0] = *(s32 *)(base + 0x5C) - *(u16 *)(iv + 0x06);
        v10[1] = *(s32 *)(base + 0x60) - *(u16 *)(iv + 0x0A);
        v10[2] = *(s32 *)(base + 0x64) - *(u16 *)(iv + 0x0E);
        VectorNormalSS(v10, v10);

        *(u16 *)(iv + 0x06) = *(u16 *)(iv + 0x06) + ((s16)v10[0] >> 6);
        *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) + ((s16)v10[1] >> 6);
        *(u16 *)(iv + 0x0E) = *(u16 *)(iv + 0x0E) + ((s16)v10[2] >> 6);
        *(u16 *)(iv + 0x34) = 0x3000;
        func_8002D4C8(0xAF8, 0);
    }

    *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
}



// @class: struct
// @stuck: none — MATCH

extern int rand(void);
extern int func_80143C74(short *, int);
extern int func_80047948(int);
extern int func_8004787C(int);

void func_8018C9CC(short *param_1)
{

    extern void (*D_801D4C94[])(short *);
    int iVar3;
    unsigned int uVar2;
    short v;

    v = param_1[0x81];
    if (v != 0) {
        v = v - 1;
        param_1[0x81] = v;
        if (v == 0) {
            *(unsigned short *)(param_1 + 0x2e) &= 0xbfff;
        }
    }
    D_801D4C94[*(unsigned short *)(param_1 + 1)](param_1);
    if (*(unsigned short *)param_1 != 0) {
        if (param_1[0x7e] == 0) {
            *(int *)(param_1 + 2) = *(int *)(*(int *)(param_1 + 0x32) + 4);
            *(int *)(param_1 + 4) = *(int *)(*(int *)(param_1 + 0x32) + 8);
            *(int *)(param_1 + 6) = *(int *)(*(int *)(param_1 + 0x32) + 0xc);
            *(unsigned short *)(*(int *)(param_1 + 0x10) + 0x10) =
                *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x32) + 0x20) + 0x10);
            *(unsigned short *)(*(int *)(param_1 + 0x10) + 0x12) =
                *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x32) + 0x20) + 0x12);
            *(unsigned short *)(*(int *)(param_1 + 0x10) + 0x14) =
                *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x32) + 0x20) + 0x14);
        }
        if ((param_1[0x3b] < 5) && ((rand() & 3) == 0) &&
            ((iVar3 = func_80143C74(param_1, 0)) != 0)) {
            uVar2 = rand();
            *(int *)(iVar3 + 0x10) = ((uVar2 & 0x7ff) - 0x400) * 0x100;
            *(unsigned int *)(iVar3 + 0x14) = 0xfff00000;
            uVar2 = rand();
            *(int *)(iVar3 + 0x18) = ((uVar2 & 0x7ff) - 0x400) * 0x100;
            *(int *)(iVar3 + 4) +=
                func_80047948((int)*(short *)(*(int *)(param_1 + 0x10) + 0x12)) * 0x400;
            *(int *)(iVar3 + 0xc) -=
                func_8004787C((int)*(short *)(*(int *)(param_1 + 0x10) + 0x12)) * 0x400;
            uVar2 = rand();
            *(short *)(iVar3 + 6) -= 0x20;
            *(short *)(iVar3 + 6) += (uVar2 & 0x3f);
            *(short *)(iVar3 + 0xa) -= 0x40;
            uVar2 = rand();
            *(short *)(iVar3 + 0xe) -= 0x20;
            *(short *)(iVar3 + 0xe) += (uVar2 & 0x3f);
        }
    }
    return;
}




extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(s32);
extern u8  *func_8012913C();
extern s32  rand(void);
extern s32  func_80047948(s32 a0);
extern s32  func_8004787C(s32 a0);
extern s32  VectorNormalSS(void *a0, void *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002A04C(s32 a0);


void func_8018CBDC(s32 a0) {

    extern s32 D_801151D4;

    extern u8 D_800AF648;
    extern void func_8002AC00(s32 arg0);

    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 v[4];    /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;
    s32 p;
    s32 s0;
    s32 i;

    p = D_801151D4;

    if (*(s16 *)(a0 + 0xFC) >= 0x1F) {
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(s16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) - 5;
        }
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(s16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) + 5;
        }
        s0 = func_8012C658(0x32, 2, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) + 8;
        }
        func_8002AC00(0x22);
        s0 = *(s32 *)(a0 + 0x64);
        *(s16 *)(s0 + 0x2) = 4;
        s0 = *(s32 *)(*(s32 *)(a0 + 0x64) + 0xCC);
        *(s16 *)(s0 + 0x2) = 4;

        for (i = 0; i < 8; i++) {
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }

        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                        && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
            s32 x = (s16)L.sxy[0];
            s32 ax;
            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xF0 - ax) * 0x7F) / 0xF0;
            __asm__("" : "=r"(ax) : "0"(ax));
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            {
                s32 flg = 0x3000;
                func_8002D4C8(0x961, ((ax | flg) | x) & 0xFFFF);
            }
        }

        *(s32 *)(*(s32 *)(a0 + 0x64) + 0xD0) = 0;
        func_8002A04C(a0);
        ((void (*)(void *))func_8012C218)((void *)a0);
        return;
    }

    s0 = (s32)func_8012913C(0x23);
    if (s0 != 0) {
        *(s16 *)(s0 + 0x6) = *(u16 *)(a0 + 0x6) + (rand() & 0x7F) - 0x40;
        *(s16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA) + (rand() & 0x7F) - 0x80;
        *(s16 *)(s0 + 0xE) = *(u16 *)(a0 + 0xE) + (rand() & 0x7F) - 0x40;

        *(s32 *)(s0 + 0x4) =
            *(s32 *)(s0 + 0x4) -
            func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x400;
        {
            s32 t = func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x400;
            *(s16 *)(s0 + 0x34) = 0x1800;
            *(s32 *)(s0 + 0x18) = 0;
            *(s32 *)(s0 + 0x14) = 0;
            *(s32 *)(s0 + 0x10) = 0;
            *(s32 *)(s0 + 0xC) = *(s32 *)(s0 + 0xC) + t;
        }

        L.nv[0] = *(s32 *)(p + 0x5C) - *(u16 *)(s0 + 0x6);
        L.nv[1] = *(s32 *)(p + 0x60) - *(u16 *)(s0 + 0xA);
        L.nv[2] = *(s32 *)(p + 0x64) - *(u16 *)(s0 + 0xE);
        VectorNormalSS(L.nv, L.nv);

        *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)L.nv[0] >> 6);
        *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)L.nv[1] >> 6);
        *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)L.nv[2] >> 6);
        *(s16 *)(s0 + 0x34) = 0x3000;
        func_8002D4C8(0xAF8, 0);
    }

    *(s16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
}



extern s32 rand(void);
extern s32 func_80143C74();
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8018D020(s32 a0) {

    extern void (*D_801D4D0C[])(s32);
    s32 iVar3;
    s32 iVar4;
    s32 r;

    {
        s16 t = *(s16 *)(a0 + 0x102);
        if (t != 0) {
            t--;
            *(s16 *)(a0 + 0x102) = t;
            if (t == 0) {
                *(u16 *)(a0 + 0x5C) &= 0xBFFF;
            }
        }
    }

    D_801D4D0C[*(u16 *)(a0 + 2)](a0);

    if (*(u16 *)(a0 + 0) != 0) {
        if (*(s16 *)(a0 + 0xFC) == 0) {
            *(s32 *)(a0 + 4) = *(s32 *)(*(s32 *)(a0 + 0x64) + 4);
            *(s32 *)(a0 + 8) = *(s32 *)(*(s32 *)(a0 + 0x64) + 8);
            *(s32 *)(a0 + 0xC) = *(s32 *)(*(s32 *)(a0 + 0x64) + 0xC);
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(s16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x10);
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(s16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12);
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
                *(s16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x14);
        }
        if (*(s16 *)(a0 + 0x76) < 5 && (rand() & 3) == 0 &&
            (iVar3 = func_80143C74(a0, 0)) != 0) {
            *(s32 *)(iVar3 + 0x10) = ((rand() & 0x7FF) - 0x400) << 8;
            *(s32 *)(iVar3 + 0x14) = 0xFFF00000;
            *(s32 *)(iVar3 + 0x18) = ((rand() & 0x7FF) - 0x400) << 8;
            iVar4 = func_80047948((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
            *(s32 *)(iVar3 + 4) = *(s32 *)(iVar3 + 4) - iVar4 * 0x400;
            iVar4 = func_8004787C((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
            *(s32 *)(iVar3 + 0xC) = *(s32 *)(iVar3 + 0xC) + iVar4 * 0x400;
            r = rand();
            {
                s32 m6 = *(u16 *)(iVar3 + 6) - 0x20;
                *(u16 *)(iVar3 + 6) = m6 + (r & 0x3F);
            }
            *(u16 *)(iVar3 + 0xA) = *(u16 *)(iVar3 + 0xA) - 0x40;
            r = rand();
            {
                s32 mE = *(u16 *)(iVar3 + 0xE) - 0x20;
                *(u16 *)(iVar3 + 0xE) = mE + (r & 0x3F);
            }
        }
    }
}




// @class: schedule
// @stuck: none — MATCH. Two levers: (1) split rand()-result into its own var (shared iVar1 forced an extra move a0,v0); (2) reorder decrement before sp[0] to group the two lhu loads as target's scheduler does; (3) materialize &D_80126B96 via a local u16* to CSE the address (lui+addiu once) instead of %hi/%lo split-per-access.








extern void func_80128EA8();
extern void func_8012931C();
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern u8  *func_8012913C();
extern void func_801292C8();
extern int  func_8012D664();

extern u16 D_801270C0;

void func_8018D230(s32 arg0) {

    extern u8  D_801D4AF0;
    extern u8  D_801D4AFC;
    extern u16 D_80126B96;
    s32 iVar1;
    s32 rv;
    u8 *p;
    u16 sp[3];

    if (*(u16 *)(arg0 + 2) == 0) {
        *(u8 **)(*(s32 *)(arg0 + 0x20) + 0x20) = &D_801D4AF0;
        *(u32 *)(*(s32 *)(arg0 + 0x20) + 4) |= 0x50000000;
        *(u8 *)(*(s32 *)(arg0 + 0x20) + 0x27) = 0x59;
        func_80128EA8(*(s32 *)(arg0 + 0x20), arg0 + 0x24, (s32)&D_801D4AFC);
        rv = rand();
        *(s32 *)(arg0 + 0x1c) = 0x10;
        *(s32 *)(arg0 + 0x2c) = 0x200;
        *(s16 *)(arg0 + 0x28) = rv % 15;
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) = 0x1200;
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1a) = 0x1200;
        *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
    } else if (*(s16 *)&D_801270C0 == 1) {
        func_8012931C(arg0);
        func_80128ED8(*(s32 *)(arg0 + 0x20), arg0 + 0x24);
        *(s32 *)(arg0 + 0x1c) -= 1;
        if ((rand() & 7) == 0 && (p = func_8012913C(0x22)) != 0) {
            *(u16 *)(p + 6) = *(u16 *)(arg0 + 6);
            *(u16 *)(p + 0xa) = *(u16 *)(arg0 + 0xa);
            *(u16 *)(p + 0xe) = *(u16 *)(arg0 + 0xe);
            *(s32 *)(p + 0x10) = *(s32 *)(arg0 + 0x10) >> 3;
            *(s32 *)(p + 0x14) = *(s32 *)(arg0 + 0x14) >> 3;
            *(s32 *)(p + 0x18) = *(s32 *)(arg0 + 0x18) >> 3;
            *(s16 *)(p + 0x34) = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) + 1;
            *(u16 *)(*(s32 *)(p + 0x20) + 0x2c) = 0xc008;
        }
        if (*(s32 *)(arg0 + 0x1c) == 0) {
            func_801292C8(arg0);
        } else {
            *(s32 *)(arg0 + 0x14) = 0xffff0000;
            iVar1 = *(s32 *)(arg0 + 0x2c) + 0x80;
            *(s32 *)(arg0 + 0x2c) = iVar1;
            *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) =
                *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) + (s16)iVar1;
            *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1a) =
                *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1a) + (s16)*(s32 *)(arg0 + 0x2c);
            *(s16 *)(arg0 + 0xa) = *(s16 *)(arg0 + 0xa) - 0x20;
            sp[0] = *(u16 *)(arg0 + 6);
            sp[1] = *(u16 *)(arg0 + 0xa);
            sp[2] = *(u16 *)(arg0 + 0xe);
            if (func_8012D664(sp, 0x10, 0xb4) == 1) {
                u16 *q = &D_80126B96;
                *q |= 0x4200;
            }
            *(s16 *)(arg0 + 0xa) = *(s16 *)(arg0 + 0xa) + 0x20;
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018D4B4);


extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern int func_8018AC2C(int param_1, short param_2);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern void func_8012A828(s32 a0, void *a1);

void func_8018D4D4(s32 a0) {
    extern u8 D_801D4BFC[];
    extern u8 D_801DC3B8[];
    extern u8 D_801DC4A8[];
    extern u8 D_801DC598[];
    s32 pad[4];

    func_8012B1B4(a0, (s32)D_801D4BFC);
    func_8012CBCC(a0);
    func_8018AC2C(a0, 0x48);
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    *(u16 *)(a0 + 0x100) -= 1;
    if (*(s16 *)(a0 + 0x100) == 0) {
        *(s16 *)(a0 + 2) = 6;
        *(u16 *)(a0 + 0x100) = 0x2D;
        *(s32 *)(a0 + 0x1C) = 0;
        *(s16 *)(a0 + 0x104) = 0;
        func_8012A828(a0, D_801DC3B8);

        if (*(s32 *)(a0 + 0xCC) != 0) {
            func_8012A828(*(s32 *)(a0 + 0xCC), D_801DC4A8);
        }
        if (*(s32 *)(a0 + 0xD0) != 0) {
            func_8012A828(*(s32 *)(a0 + 0xD0), D_801DC598);
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018D5D4);


extern void func_8012B370(int a0);
extern void func_8012C218(s32);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018D674(s32 a0)
{
    s32 t;
    register s32 *a1 asm("$5");
    u32 v0;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        a1 = *(s32 **)(a0 + 0x20);
        v0 = *(u32 *)(a1 + 0x1);
        v0 ^= 0x80000000;
        *(u32 *)(a1 + 0x1) = v0;
        ((void (*)(void))func_8012B370)();

        t = *(s32 *)(a0 + 0x1C);
        if ((t & 0x3) != 0) {
            s32 s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    ((void (*)(void *))func_8012C218)((void *)a0);
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018D734);



















void func_8018D7CC(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0x64));
  *((s16 *) (v0 + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xD0))) + 0x5C)) = 0;
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018D7EC);

void func_8018D8DC(void) {
}

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018D8E4);


extern void func_8012B370(int a0);
extern void func_8012C218(s32);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018D9B8(s32 a0)
{
    s32 t;
    register s32 *a1 asm("$5");
    u32 v0;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        a1 = *(s32 **)(a0 + 0x20);
        v0 = *(u32 *)(a1 + 0x1);
        v0 ^= 0x80000000;
        *(u32 *)(a1 + 0x1) = v0;
        ((void (*)(void))func_8012B370)();

        t = *(s32 *)(a0 + 0x1C);
        if ((t & 0x3) != 0) {
            s32 s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    ((void (*)(void *))func_8012C218)((void *)a0);
}


extern void func_8012B370(int a0);
    void func_8018DA78(void) {
        ((s32 (*)(void))func_8012B370)();
    }


















void func_8018DA98(void *a0)
{
  s32 v0;
  *((s16 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xCC))) + 0x5C)) = 0;
}


extern s32 func_8012C354(s32, void*);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B030();
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_8018DAB8(s32 a0) {

    extern u8 D_801D4CB8[];
    extern u8 D_801DA8E4[];
    extern u8 D_801D4CEC[];
    extern u8 D_801DC2B8[];

    s32 v0;

    v0 = ((s32 (*)(s32, s32))func_8012C354)(a0, (s32)D_801D4CB8);
    if (v0 != 0) {
        if (*(s16 *)(a0 + 0x70) != 0) {
            func_8001C214(*(s32 *)(a0 + 0x20), (s32)D_801DA8E4);
        }
        *(u8 *)(a0 + 0xC0) = 1;
        *(s32 *)(a0 + 0xB4) = 0xFFFFDFDF;
        func_8012B030(a0);
        *(void **)(a0 + 0xBC) = D_801D4CEC;
        *(s16 *)(a0 + 0xAE) = 0x2100;
        *(u32 *)(a0 + 0xC4) = *(u32 *)(a0 + 0xC4) | 2;
        func_8012A828(a0, D_801DC2B8);
        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
        func_8012B23C(a0);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) | 0x10;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2400;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2400;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x2400;
    }
}


void func_8018DBAC(void) {
}


extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8012B370(s32 a0);

void func_8018DBB4(s32 a0) {
    s16 ang;
    u16 cnt;
    u16 acc;

    ang = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14);
    if (ang < 0xC00) {
        if (ang != 0) {
            goto state3;
        }
    }

    cnt = *(u16 *)(a0 + 0xFC);
    acc = *(u16 *)(a0 + 0xFE);
    cnt = cnt + 1;
    acc = acc + cnt;
    *(u16 *)(a0 + 0xFC) = cnt;
    *(u16 *)(a0 + 0xFE) = acc;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) - acc;

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) & 0xFFF;

    *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 8;

    *(s32 *)(a0 + 4) = *(s32 *)(a0 + 4) -
        func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x80;

    *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0xC) +
        func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x80;
    goto tail;

state3:
    *(u16 *)(a0 + 2) = 3;
    *(s32 *)(a0 + 0x1C) = 0x1E;
    *(u16 *)(a0 + 0x98) = 0;

tail:
    func_8012B370(a0);
}



extern void func_8012B370(int a0);
extern void func_8012C218(s32);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018DCA8(s32 a0)
{
    s32 t;
    register s32 *a1 asm("$5");
    u32 v0;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        a1 = *(s32 **)(a0 + 0x20);
        v0 = *(u32 *)(a1 + 0x1);
        v0 ^= 0x80000000;
        *(u32 *)(a1 + 0x1) = v0;
        ((void (*)(void))func_8012B370)();

        t = *(s32 *)(a0 + 0x1C);
        if ((t & 0x3) != 0) {
            s32 s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    ((void (*)(void *))func_8012C218)((void *)a0);
}


extern void func_8012B370(int a0);
    void func_8018DD68(void) {
        ((void (*)(void))func_8012B370)();
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018DD88);


/* TU declares func_8018DEC0 as void(void) (S35 self-axis) but the asm takes
 * $a0 as a pointer parameter — bind through a private C name. */
extern void aF8017ED80(void *param_1) __asm__("func_8018DEC0");

void aF8017ED80(void *param_1) {
    u8 *a0 = (u8 *)param_1;
    s32 pad_[4];
    s32 iVar2;
    u32 uVar1;

    if (*(u16 *)(a0 + 0x0) != 0) {
        iVar2 = *(s32 *)(a0 + 0xCC);
        *(u16 *)(iVar2 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(iVar2 + 0xA) = *(u16 *)(a0 + 0xA);
        *(u16 *)(iVar2 + 0xC) = *(u16 *)(a0 + 0xE);
        *(u16 *)(iVar2 + 0x10) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10);
        *(u16 *)(iVar2 + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + *(u16 *)(a0 + 0xFC);
        *(u16 *)(iVar2 + 0x14) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14);
        *(u16 *)(iVar2 + 0x18) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        *(u16 *)(iVar2 + 0x1A) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A);
        *(u16 *)(iVar2 + 0x1C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C);
        if (*(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) < 0) {
            register u32 val __asm__("$2");
            val = *(u32 *)(iVar2 + 0x4);
            uVar1 = val | 0x80000000;
        } else {
            __asm__ __volatile__("");
            uVar1 = *(u32 *)(iVar2 + 0x4) & 0x7FFFFFFF;
        }
        *(u32 *)(iVar2 + 0x4) = uVar1;

        iVar2 = *(s32 *)(a0 + 0xD0);
        *(u16 *)(iVar2 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(iVar2 + 0xA) = *(u16 *)(a0 + 0xA);
        *(u16 *)(iVar2 + 0xC) = *(u16 *)(a0 + 0xE);
        *(u16 *)(iVar2 + 0x10) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10);
        *(u16 *)(iVar2 + 0x12) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + *(u16 *)(a0 + 0xFE);
        *(u16 *)(iVar2 + 0x14) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14);
        *(u16 *)(iVar2 + 0x18) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        *(u16 *)(iVar2 + 0x1A) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A);
        *(u16 *)(iVar2 + 0x1C) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C);
        if (*(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) < 0) {
            register u32 val __asm__("$2");
            val = *(u32 *)(iVar2 + 0x4);
            uVar1 = val | 0x80000000;
        } else {
            __asm__ __volatile__("");
            uVar1 = *(u32 *)(iVar2 + 0x4) & 0x7FFFFFFF;
        }
        *(u32 *)(iVar2 + 0x4) = uVar1;
    }
}



/* func_8018E094 -- ov_SC06_008, TU ov_SC06_008_jr_8017C294.c (open-only h_norm
 * cluster exemplar, 7 members).
 *
 * a0+0x0  : u16 active flag; 0 => early return.
 * a0+0x84 : s16 sound cooldown timer.
 *   cooldown != 0  -> just decrement it.
 *   cooldown == 0  -> try to play a positional sound (RotTransPers screen
 *                     projection of the parent's position, range-gated on
 *                     screen X/Y, volume from the classic div-by-0xF0 /
 *                     div-by-0x1E magic-constant idiom -- byte-proven sibling
 *                     form is func_80181CF0 in this same TU, sndid 0x849 here
 *                     vs 0x961 there), then unconditionally reset the timer
 *                     to 0xA regardless of whether the sound actually played.
 * a0+0xFC / 0xFE : running hit-combo accumulators, bumped by +/-0x280 every
 *                     call (unconditional tail).
 * Tail always calls ((void (*)(void *))func_8018DEC0)(a0) (the TU's canonical decl for this
 * symbol is void(void) -- S35 self-axis -- so this draft binds its own
 * private extern with the asm's real void(void*) shape).
 *
 * Control flow is EXPLICIT goto/label, mirroring source-order block
 * placement (gcc-2.7.2 lays out basic blocks in literal source order, not by
 * fallthrough preference -- see the func_80181CF0 comment, same TU): the
 * cooldown!=0 decrement is the SHORT block and sits out-of-line (jumped to),
 * the cooldown==0 RTP+sound block is the LONG block and sits inline
 * (fallthrough), matching the target's physical layout exactly.
 *
 * MATCH levers (byte-proven, 2026-08-05):
 *  1. Naive `if(old!=0){cool=old-1;}else{...}` folds trivially: reorg.c's
 *     delay-slot filler steals the single-insn decrement into the `bnez`'s
 *     own delay slot and retargets the branch straight to the join label
 *     (2 ins short of target). The target instead keeps a genuine copy
 *     (`addu $v1,$v0,zero`) in the delay slot and a SEPARATE `addiu $v0,$v1,-1`
 *     at the decrement site. Reproduced by pinning a second variable
 *     `register s32 v1 __asm__("$3")`, assigned UNCONDITIONALLY right after
 *     the load (`v1 = old;`) -- the scheduler places that copy in the
 *     branch's delay slot on its own, and the decrement (`cool = v1 - 1`)
 *     can no longer be folded away. `cool` is separately pinned to
 *     `__asm__("$2")` so its other def sites (the three `cool = 0xA` early
 *     exits) don't drift onto $3 by coalescing with v1.
 *  2. The tail's `sh $v0,0x84($s0)` / `addu $a0,$s0,zero` order (store off
 *     the callee-saved pointer BEFORE reloading it into the call-argument
 *     register) needed a `__asm__ __volatile__("":::"memory")` fence right
 *     after the store -- without it, sched1 hoists the independent a0-reload
 *     ahead of the store even when the reload is written later in source.
 *  3. Frame is -0x38, 8 bytes (2 words) larger than the natural -0x30 the
 *     locals alone produce; `pad2[2]` (dead, address never read) inside `L`
 *     reserves them, mirroring func_80181CF0's own "dead aggregate sizes the
 *     frame" idiom.
 */


/* §37/§124 def-side asm-label alias (P30 S1d class lever): the TU declares
 * `extern void func_8018E094(void);` (L4082, L4091) for callers that invoke it with NO args,
 * while the byte-true definition takes an s32 in $a0 -> `conflicting types`. Neither side can
 * move (a no-prototype escape is illegal once a param promotes), so the DEFINITION gets a
 * private C identifier and binds the emitted symbol with a GNU asm label. Zero blast radius:
 * the TU's declaration never meets the definition, and the emitted symbol is unchanged. */
void aF8017EF54(s32 a0) __asm__("func_8018E094");

void aF8017EF54(s32 a0)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
    extern u8   D_800AF648;
    extern void func_8018DEC0(void);
    struct {
        s16 v[3];    /* sp+0x10 */
        s16 pad1;    /* sp+0x16 */
        u16 sxy[2];  /* sp+0x18 */
        s32 z;       /* sp+0x1C */
        s32 flag;    /* sp+0x20 */
        s32 pad2[2]; /* sp+0x24 -- dead, sizes the frame */
    } L;

    register s32 v1 __asm__("$3");
    register s32 cool __asm__("$2");
    s32 old;

    if (*(u16 *)(a0 + 0x0) == 0) {
        return;
    }

    old = *(s16 *)(a0 + 0x84);
    v1 = old;
    if (old != 0) {
        goto L_dec;
    }

    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);

    if (L.flag < 0) {
        cool = 0xA;
        goto L_join;
    }
    if ((u32)((L.sxy[0] + 0xEF) & 0xFFFF) >= 0x1DF) {
        cool = 0xA;
        goto L_join;
    }
    if ((u32)((L.sxy[1] + 0xB3) & 0xFFFF) >= 0x167) {
        goto L_snd_skip;
    }

    {
        s32 sx = (s16)L.sxy[0];
        s32 av;

        av = sx;
        if (sx < 0) {
            av = -sx;
        }
        av = ((0xF0 - av) * 0x7F) / 0xF0;
        sx = (sx + 0xF0) / 0x1E;
        if (sx == 0x10) {
            sx = 0xF;
        }
        sx = sx << 8;
        func_8002D4C8(0x849, (av | (0x3000 | sx)) & 0xFFFF);
    }

L_snd_skip:
    cool = 0xA;
    goto L_join;

L_dec:
    cool = v1 - 1;

L_join:
    *(s16 *)(a0 + 0x84) = cool;
    __asm__ __volatile__("" ::: "memory");

    {
        s32 p = a0;
        *(u16 *)(p + 0xFC) = *(u16 *)(p + 0xFC) + 0x280;
        *(u16 *)(p + 0xFE) = *(u16 *)(p + 0xFE) - 0x280;
        ((void (*)(void *))func_8018DEC0)((void *)p);
    }
}



extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_8012C588(s32 a0, s32 a1);
extern u8  *func_8012913C();
extern void func_8018DEC0(void);

void func_8018E240(s32 a0)
{

    extern s32  D_801151D4;
    u16 nv[4];
    s32 g;
    s32 s0;
    s32 idx;

    g = D_801151D4;

    if (*(u16 *)a0 != 0) {
        idx = *(s32 *)(a0 + 0x1C) & 3;
        switch (idx) {
        case 0:
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            break;
        case 1:
            break;
        case 2:
        case 3:
            s0 = (s32)func_8012913C(0x23);
            if (s0 != 0) {
                *(s16 *)(s0 + 0x6) = *(u16 *)(a0 + 0x6) + (rand() & 0x3F) - 0x20;
                *(s16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA) + (rand() & 0x3F) - 0x30;
                {
                    s32 r = rand();
                    s32 t = *(u16 *)(a0 + 0xE);
                    *(s32 *)(s0 + 0x18) = 0;
                    *(s32 *)(s0 + 0x14) = 0;
                    *(s32 *)(s0 + 0x10) = 0;
                    *(s16 *)(s0 + 0xE) = t + (r & 0x3F) - 0x20;
                }
                *(s16 *)(s0 + 0x34) = (rand() & 0x17FF) + 0x800;
                nv[0] = *(s32 *)(g + 0x5C) - *(u16 *)(s0 + 0x6);
                nv[1] = *(s32 *)(g + 0x60) - *(u16 *)(s0 + 0xA);
                nv[2] = *(s32 *)(g + 0x64) - *(u16 *)(s0 + 0xE);
                VectorNormalSS(nv, nv);
                *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)nv[0] >> 6);
                *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)nv[1] >> 6);
                *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)nv[2] >> 6);
            }
            break;
        }
        ((void (*)(s32))func_8018DEC0)(a0);
    }
}



extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern void func_8012BE54(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8018DD88(s32 a0, s32 a1);

void func_8018E428(s32 a0)
{
    s16 hi;
    s16 pos;
    s32 sp10[3];
    u16 state;

    hi = *(s16 *)(a0 + 0x8A);
    pos = *(s16 *)(a0 + 0xA);

    if (pos >= hi - 8) {
        if (*(s32 *)(a0 + 0x48) >= 0) {
            *(s32 *)(a0 + 0x48) = -0x8000;
            *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
        }
    } else {
        if (hi + 8 >= pos) {
            if (*(s32 *)(a0 + 0x48) <= 0) {
                *(s32 *)(a0 + 0x48) = 0x8000;
                *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
            }
        }
    }

    if (*(s32 *)(a0 + 0xDC) < -0x40000) {
        *(s32 *)(a0 + 0xDC) = -0x40000;
    }

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = *(s32 *)(a0 + 0xDC);
    func_8012B1B4(a0, (s32)sp10);
    func_8012CBCC(a0);

    state = *(u16 *)(a0 + 0x34);
    switch (state) {
    case 0: {
        register s32 s0v __asm__("$16");
        s32 ret;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;
        register s32 p20 __asm__("$4");

        s0v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s0v);
        if (ret <= 0x3FFFF) {
            if (func_8018DD88(a0, 0x51) == 0) {
                goto set_state1;
            }
        }
        p744 = func_8012B744((void *)(a0 + 4), (void *)s0v);
        v1p = *(s32 *)(a0 + 0x20);
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 8);
        p20 = *(s32 *)(a0 + 0x20);
        *(u16 *)(p20 + 0x12) = *(u16 *)(p20 + 0x12) + b608;
        v1p = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1p + 0x12) = *(u16 *)(v1p + 0x12) & 0xFFF;
        func_8012B1B4(a0, (s32)sp10);
        break;
    }
    case 1: {
        s32 ret;

        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) << 1;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88));
        if (ret > 0x3FFFF) {
            goto rand_tail;
        }
        if (func_8018DD88(a0, 0x51) == 0) {
            goto end_switch;
        }
        goto rand_tail;
    }
    case 2: {
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;
        s32 p20;

        p744 = func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88));
        v1p = *(s32 *)(a0 + 0x20);
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 0x10);
        p20 = *(s32 *)(a0 + 0x20);
        *(u16 *)(p20 + 0x12) = *(u16 *)(p20 + 0x12) + b608;
        v1p = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1p + 0x12) = *(u16 *)(v1p + 0x12) & 0xFFF;
        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) >> 1;
        func_8018DD88(a0, 0x51);
        if (*(s16 *)(a0 + 0x102) == 0) {
            *(u16 *)(a0 + 0x34) = 3;
        } else {
            *(s16 *)(a0 + 0x102) = *(s16 *)(a0 + 0x102) - 1;
        }
        break;
    }
    case 3: {
        register s32 s2v __asm__("$18");
        s32 ret;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;

        s2v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s2v);
        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) << 1;
        if (func_8018DD88(a0, 0x51) != 0) {
            goto rand_tail;
        }
        if (ret <= 0x40000) {
            goto set_state1;
        }
        p744 = func_8012B744((void *)(a0 + 4), (void *)s2v);
        v1p = *(s32 *)(a0 + 0x20);
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 1);
        if ((u32)(b608 + 0xFF) < 0x1FF) {
            goto end_switch;
        }
        goto rand_tail;
    }
    }
    goto end_switch;

rand_tail:
    *(u16 *)(a0 + 0x34) = 2;
    {
        s32 r = rand();
        *(s16 *)(a0 + 0x102) = (r & 7) + 8;
    }
    goto end_switch;

set_state1:
    *(u16 *)(a0 + 0x34) = 1;

end_switch:
    if (*(s16 *)(a0 + 0x100) != 0) {
        *(s16 *)(a0 + 0x100) = *(s16 *)(a0 + 0x100) - 1;
    } else {
        s32 ret3;

        ret3 = ((s32 (*)(s32))func_8012BE54)(a0);
        if (ret3 <= 0x24000) {
            *(s16 *)(a0 + 0x2) = 2;
            *(s16 *)(a0 + 0x100) = 0x3C;
        }
    }
}




extern s32 func_8018A6DC(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012B370(int a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);


void func_8018E764(s32 param_1)
{

    extern u8 D_801DC794;
    extern u8 D_801DC79C;
    extern u8 D_801DC7A4;
    extern u8 D_800AF648;
    /* L5: slot offsets are exact only through ONE struct — copied verbatim
       from the banked RTP_SND sibling func_80180CA8 (same TU) so the
       sp+0x10.."0x2B layout reproduces byte-for-byte. */
    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 rv[4];   /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;

    s16 sVar1;
    s32 s0;

    if (*(s32 *)(param_1 + 0x1c) == 0) {
        sVar1 = *(s16 *)(param_1 + 0x100) - 1;
        *(s16 *)(param_1 + 0x100) = sVar1;
        if (sVar1 == 0) {
            *(s16 *)(param_1 + 2) = 1;
            *(s16 *)(param_1 + 0x100) = 0x3c;
            *(s16 *)(param_1 + 0x8a) = *(s16 *)(param_1 + 0xa) - 0x140;
        } else {
            *(s32 *)(param_1 + 0x1c) = (sVar1 == 1) ? 0x3c : 3;

            func_8018A6DC(param_1, (s32)&D_801DC794);

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&D_801DC79C, (s32)L.nv);
                *(s16 *)(s0 + 6)  = L.nv[0];
                *(s16 *)(s0 + 0xA) = L.nv[1];
                *(s16 *)(s0 + 0xE) = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 0, s0);
            }

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&D_801DC7A4, (s32)L.nv);
                *(s16 *)(s0 + 6)  = L.nv[0];
                *(s16 *)(s0 + 0xA) = L.nv[1];
                *(s16 *)(s0 + 0xE) = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 1, s0);
            }

            L.rv[0] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x48);
            L.rv[1] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4C);
            L.rv[2] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x50);
            { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
            { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
            RotTransPers((s32)L.rv, (s32)L.sxy, &L.z, &L.flag);
            if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                          && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
                s32 x = (s16)L.sxy[0];
                s32 ax;

                ax = x;
                if (x < 0) {
                    ax = -x;
                }
                ax = ((0xF0 - ax) * 0x7F) / 0xF0;
                __asm__("" : "=r"(ax) : "0"(ax));
                x = (x + 0xF0) / 0x1E;
                if (x == 0x10) {
                    x = 0xF;
                }
                x = x << 8;
                {
                    s32 flg = 0x3000;
                    func_8002D4C8(0x84A, ((ax | flg) | x) & 0xFFFF);
                }
            }
        }
    } else {
        *(s32 *)(param_1 + 0x1c) = *(s32 *)(param_1 + 0x1c) - 1;
    }
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8018EA0C;









void func_8018EA0C(s32 a0)
{

    extern s16 D_801DC7AC[];
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
    {
        s16 idx = *(s16 *)(a0 + 0x70);
        s16 *p = &D_801DC7AC[(idx - 1) * 4];
        s16 gx = *(s16 *)&D_80126B5E;
        s16 gz;
        s32 p20;

        if (!(*p < gx)) {
            break;
        }
        p++;
        if (!(gx < *p)) {
            break;
        }
        p++;
        gz = *(s16 *)&D_80126B66;
        if (!(*p < gz)) {
            break;
        }
        if (!(gz < p[1])) {
            break;
        }

        p20 = *(s32 *)(a0 + 0x20);
        *(u32 *)(p20 + 4) = *(u32 *)(p20 + 4) & 0x7FFFFFFF;

        {
            s32 t;

            *(s16 *)(a0 + 0x88) = D_80126B5E;
            *(s16 *)(a0 + 0x6)  = D_80126B5E;
            t = D_80126B62 - 0x80;
            *(s16 *)(a0 + 0x8A) = t;

            t = *(u16 *)(a0 + 0x34);
            {
                register s16 z __asm__("$3");
                t = t + 1;
                z = D_80126B66;
                *(u16 *)(a0 + 0x34) = t;
                *(s16 *)(a0 + 0x8C) = z;
                *(s16 *)(a0 + 0xE)  = z;
            }
        }
        break;
    }
    case 1:
    {
        s16 v;

        v = *(u16 *)(a0 + 0xA) + 8;
        *(u16 *)(a0 + 0xA) = v;
        if (v < *(s16 *)(a0 + 0x8A)) {
            break;
        }
        *(s16 *)(a0 + 0x2) = 1;
        *(u16 *)(a0 + 0x34) = 0;
        break;
    }
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018EB3C);


extern void (*D_801DC7F8[])(void);

void func_8018EC14(void *a0) {
    D_801DC7F8[*(u16 *)((s32)a0 + 0x2)]();
}



/* SV4 is the TU-canonical name (src/shared/engine_types.h) for func_8012F214's
 * in/out struct (see ov_SC06_008_jr_8017AE2C.c:3135, "SV4 svec" comment: func_8012F214 out).
 * Isolated match_one has no include path to that header, so it is typedef'd
 * locally here for the standalone compile only. */


/* func_8018EC50 - ov_SC06_008 / ov_SC06_008_jr_8017C294 (93 ins)
 *
 * One-time init (guarded by state flag at +0x34): mirror the +0x64 sub-object's
 * +0x20/+0x12 field into our own +0x20 sub-object, kick off two "core" calls,
 * pick an entry from the 2-element 12-byte table D_801DC800 (indexed by the
 * s16 at +0x70), then call func_8012F214 with a zeroed input SV4 and read the
 * first 3 fields of the output SV4 back into +6/+0xA/+0xE.  Sets the countdown
 * at +0x1c to 0x5a and marks the state flag +0x34 = 1.
 *
 * Always-executed tail: bump the +0x20 sub-object's +0x10/+0x12/+0x14 fields
 * (reloading the +0x20 pointer fresh for each field -- no CSE across the
 * intervening stores, straight literal translation), mirror +0x14 into +0xDC,
 * call func_8012CBCC(a0) and test its return (canonical fleet decl is
 * void func_8012CBCC(s32 a0); the return value is read via a function-
 * pointer cast at the use site, per the established TU idiom -- see
 * ov_SC03_099_jr_8017BEBC.c:5630 comment block). If (ret & 0x6000), decrement
 * the +0xac counter (signed s16 compare-to-zero on the POST-decrement value --
 * gcc-2.7.2's sll-by-16/bnez idiom for a s16 local) and negate +0xDC into
 * +0x14; on the counter hitting zero, call func_8012C218. Finally decrement
 * the +0x1c countdown and call func_8012C218 again when IT hits zero.
 */

extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012CBCC(s32 a0);
extern void func_8012C218(s32);


void func_8018EC50(s32 a0)
{

    extern s32 D_801DC800;
    SV4 in;
    SV4 out;
    s16 v1;
    u16 uStack_c;

    if (*(u16 *)(a0 + 0x34) == 0) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12);
        func_8012B2CC(a0);
        func_8012B23C(a0);
        func_8012B14C(a0, *(s16 *)(a0 + 0x70) * 12 + (s32)&D_801DC800);

        in.a = 0;
        in.b = 0;
        in.c = 0x10;
        func_8012F214(a0, (s32)&in, (s32)&out);
        *(u16 *)(a0 + 6) = out.a;
        *(u16 *)(a0 + 0xa) = out.b;
        uStack_c = out.c;
        *(s32 *)(a0 + 0x1c) = 0x5a;
        *(u16 *)(a0 + 0x34) = 1;
        *(u16 *)(a0 + 0xe) = uStack_c;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) += -0x80;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += 4;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) += *(u16 *)(a0 + 0xfc);

    *(s32 *)(a0 + 0xdc) = *(s32 *)(a0 + 0x14);
    if ((((s32 (*)(s32))func_8012CBCC)(a0)) & 0x6000) {
        register s32 negdc __asm__("$2");
        negdc = -*(s32 *)(a0 + 0xdc);
        v1 = *(u16 *)(a0 + 0xac);
        v1 -= 1;
        *(s16 *)(a0 + 0xac) = v1;
        *(s32 *)(a0 + 0x14) = negdc;
        if (v1 == 0) {
            ((void (*)(void *))func_8012C218)((void *)a0);
        }
    }

    {
        s32 iVar3 = *(s32 *)(a0 + 0x1c) - 1;
        *(s32 *)(a0 + 0x1c) = iVar3;
        if (iVar3 == 0) {
            ((void (*)(void *))func_8012C218)((void *)a0);
        }
    }
}



extern void (*D_801DC818[])(void);

void func_8018EDC4(void *a0) {
    D_801DC818[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018EE00);

extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8018DEC0(void);

void func_8018EE88(void *a0) {
    func_8002D4C8(0xB32, 0);
    ((void (*)(void *))func_8018DEC0)(a0);
}


extern void func_8018E094(void);
    void func_8018EEC0(s32 *param_1) {
        *(short *)(*(int *)((char *)param_1 + 0x20) + 0x10) = 0xe00;
        ((void (*)(void))func_8018E094)();
    }


extern void func_8018E094(void);
    void func_8018EEE8(s32 arg0) {
        s32 temp_v1 = *(s32 *)(arg0 + 0x20);
        *(u16 *)(temp_v1 + 0x10) += 0x20;
        func_8018E094();
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018EF1C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018EF68);

extern void func_8018DEC0(void);
    void func_8018F054(s32 *a0) {
        *(s32 *)((char *)a0 + 0x10) = *(s32 *)((char *)a0 + 0x10) >> 1;
        *(s32 *)((char *)a0 + 0x18) = *(s32 *)((char *)a0 + 0x18) >> 1;
        ((void (*)(void))func_8018DEC0)();
    }


extern void func_8018DEC0(void);
    void func_8018F088(u8 *param_1) {
        param_1[0xC1] = 0xC;
        *(int *)(param_1 + 0x1C) = 0x3C;
        ((void (*)(void))func_8018DEC0)();
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018F0B4);


extern s32 func_8012C354(s32, void*);
extern void func_80143970();
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);
extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012CAE4(s32);

void func_8018F140(s32 a0) {

    extern u8 D_801DC698[];
    extern u8 D_801DE3D8[];
    extern u8 D_801DC6CC[];
    extern u8 D_801DE0E8[];
    extern u8 D_801DE3C0[];
    extern u8 D_8018FB1C[];

    s32 s0;
    u16 t;

    if (((s32 (*)(s32, s32))func_8012C354)(a0, D_801DC698) == 0) {
        return;
    }
    *(u8 *)(a0 + 0xC0) = 1;
    *(s32 *)(a0 + 0xB4) = -0x1001;
    ((s32 (*)(s32))func_80143970)(a0);
    func_8012A828(a0, D_801DE3D8);
    *(u16 *)(a0 + 0x2) += 1;
    func_8012B200((u8 *)a0);
    *(s32 *)(a0 + 0xBC) = (s32)D_801DC6CC;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        goto fail;
    }
    *(s32 *)(a0 + 0xCC) = s0;
    func_8001C214(s0, (s32)D_801DE0E8);
    t = *(u16 *)(s0 + 0x2C) | 0x10;
    *(s32 *)(s0 + 0x20) = *(s32 *)D_8018FB1C;
    *(u16 *)(s0 + 0x2C) = t;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        func_80016714((void *)*(s32 *)(a0 + 0xCC), 0x84);
fail:
        ((void (*)(void *))func_8012CAE4)((void *)a0);
        return;
    }
    *(s32 *)(a0 + 0xD0) = s0;
    func_8001C214(s0, (s32)D_801DE3C0);
    t = *(u16 *)(s0 + 0x2C) | 0x10;
    *(s32 *)(s0 + 0x20) = *(s32 *)D_8018FB1C;
    *(u16 *)(s0 + 0x2C) = t;
    *(u16 *)(a0 + 0x100) = 0x3C;
    *(s32 *)(a0 + 0xDC) = 0xFFFC0000;
}




extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern s32 func_8018DD88(s32 a0, s32 a1);
extern s32 func_8012B8E4(s32 arg0, s32 arg1);

void func_8018F268(s32 a0)
{

    extern s32 D_80126B60;
    s32 sp10[3];

    if (*(s32 *)(a0 + 8) >= D_80126B60 - 0x200000) {
        if (*(s32 *)(a0 + 0x48) >= 0) {
            *(s32 *)(a0 + 0x48) = -0x8000;
            *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
        }
    } else {
        if (D_80126B60 - 0x180000 >= *(s32 *)(a0 + 8)) {
            if (*(s32 *)(a0 + 0x48) <= 0) {
                *(s32 *)(a0 + 0x48) = 0x8000;
                *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
            }
        }
    }

    *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) >> 1;

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = *(s32 *)(a0 + 0xDC);
    func_8012B1B4(a0, (s32)sp10);
    func_8012CBCC(a0);
    func_8018DD88(a0, 0x51);

    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;

    *(u16 *)(a0 + 0x100) -= 1;
    if (*(s16 *)(a0 + 0x100) == 0) {
        *(s16 *)(a0 + 2) = 3;
        *(u16 *)(a0 + 0x100) = 5;
        *(s32 *)(a0 + 0x1C) = 0;
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018F39C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018F3FC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_80186F00", func_8018F4BC);


extern void func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012CAE4(s32);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 rand(void);

void func_8018F590(s32 param_1)
{

    extern u8 D_801DE578[];
    *(s32 *)(param_1 + 0x20) = ((s32 (*)(void))func_8012C1B8)();
    if (*(s32 *)(param_1 + 0x20) == 0) {
        ((void (*)(void *))func_8012CAE4)((void *)param_1);
    } else {
        func_8001C214(*(s32 *)(param_1 + 0x20), (s32)D_801DE578);

        *(u16 *)(param_1 + 0x2) = 1;
        *(u16 *)(param_1 + 0x34) = 0;
        {
            s32 v1 = *(s32 *)(param_1 + 0x64);
            s32 t = *(s32 *)(v1 + 0x20);
            s32 r = func_80047948(*(s16 *)(t + 0x12));
            *(s32 *)(param_1 + 0xC) = *(s32 *)(param_1 + 0xC) + (r << 8);
        }
        {
            s32 v1 = *(s32 *)(param_1 + 0x64);
            s32 t = *(s32 *)(v1 + 0x20);
            s32 r = func_8004787C(*(s16 *)(t + 0x12));
            *(s32 *)(param_1 + 0x4) = *(s32 *)(param_1 + 0x4) + (r << 8);
        }
        {
            s32 t = *(s32 *)(param_1 + 0x20);
            *(u16 *)(t + 0x2C) = *(u16 *)(t + 0x2C) | 0x10;
        }
        {
            s32 t = *(s32 *)(param_1 + 0x20);
            *(s16 *)(t + 0x18) = 0x1800;
        }
        {
            s32 t = *(s32 *)(param_1 + 0x20);
            *(s16 *)(t + 0x1A) = 0x1800;
        }
        {
            s32 t = *(s32 *)(param_1 + 0x20);
            *(s16 *)(t + 0x1C) = 0x1800;
        }

        *(u16 *)(param_1 + 0xAC) = 2;
        {
            s32 r = rand();
            *(u16 *)(param_1 + 0xFC) = r & 0xFF;
        }
    }
}



extern void func_8012B23C(s32 a0);
extern void func_8012CBCC(s32 a0);
extern u8 *func_8012913C(s32 a0);
extern void func_8012C218(s32);

void func_8018F688(s32 a0)
{
    s32 s0 = a0;
    s32 ret;
    u16 val;

    if (*(u16 *)(s0 + 2) == 0) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        func_8012B23C(s0);
        *(s32 *)(s0 + 0x1C) = 1;
        return;
    }

    *(s32 *)(s0 + 0xDC) = *(s32 *)(s0 + 0x14);
    ret = ((s32 (*)(s32))func_8012CBCC)(s0);
    if (ret != 0 && (ret & 0x6000) != 0) {
        s32 cnt = *(s32 *)(s0 + 0x1C) - 1;
        *(s32 *)(s0 + 0x1C) = cnt;
        if (cnt == 0) {
            goto L80183CF4;
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

L80183CF4:
    ((void (*)(void *))func_8012C218)((void *)s0);
}






