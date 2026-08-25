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
extern u8 D_8018D97C;
extern u8 D_8018D8EC;
extern u8 D_8018D8C8;
extern u8 D_8018D8A4;
extern u8 D_8018D958;
extern u8 D_8018D934;
extern u8 D_8018D910;
extern u8 D_8018D880;
extern void func_80145934(void);
extern u8 D_8018DA0C;
extern u8 D_8018D9E8;
extern u8 D_8018D9C4;
extern u8 D_8018D9A0;
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
extern unsigned char D_8018CE04[];
extern unsigned char D_8018CE34[];
extern unsigned char D_8018CE84[];
extern unsigned char D_8018CEB4[];
extern unsigned char D_8018CEE4[];
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
extern void (*D_8018CF34[])(void *);
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
extern s32 D_8018CFFC[];
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
extern u8 D_8018D084[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018D08C;
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
extern int D_801D1C88;
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
extern s32 D_801D1C8C;
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
extern s32 D_8018D0BC;
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
extern void (*D_8018D164[])(void);
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
extern void (*D_8018D188[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018D178;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018D19C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018D1A8[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018D1B8[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018D1D0[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018D1C0;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018D1E4[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018D200[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018D1F0;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018D214[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018D228[])(void);
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
extern s32 D_8018D23C;
extern void (*D_8018D264[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018D244;
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
extern int (*D_8018D2B0[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018D2B4[])(void);
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
extern unsigned short D_8018D718[];
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
extern void (*D_8018D728[])(void);
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
extern int D_801D1CC0;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018D750[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018D730;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018D740;
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
extern void (*D_8018D790[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018D798[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018D764;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018D7A4[])(void);
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
extern u8 D_8018D774;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801D1CC8;
extern s32 D_801D1CD4;
extern s32 D_801D1CD8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018D7E0[])(s32 *);
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
extern s32 D_8018D7B4[];
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
extern s32 D_801D1CD0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018DA30[])(void);
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
extern char D_8018D850[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018DAD4[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018DC28[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018DA44;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018DC30[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018DA54;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018DA74;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018DC38[])(void);
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
extern void (*D_8018DC60[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018DC6C[])(void);
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
extern void (*D_8018DAE0[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018DD10;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018CDF4[];
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
extern unsigned char D_8018DD24[];
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
extern s8 D_8018DD60[];
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
extern u16 D_8018DDA8;
extern u16 D_8018DDAA;
extern u16 D_8018DDAC;
extern s32 D_8018DDB0;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018DDB8;
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
extern int D_8018DAC4;
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
extern unsigned int D_8018DE3C[];
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
extern void (*D_8018DEEC[])(void);
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
extern u16 D_8018DF1C[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018DF80;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801D1CE0[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018DFA4[])(void);
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
extern int D_801D1D38[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018DFEC[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018DFDC;
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
extern char D_801D154C[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018DFF4[])(void);
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
extern void (*D_8018E048[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018E010;
extern s16 D_8018E044;
extern s16 D_8018E042;
extern s16 D_8018E040;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018E054[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801D1D98;
extern u8 D_801D1D99;
extern u8 D_801D1D9A;
extern u8 D_801D1D9B;
extern u8 D_801D1D9C;
extern u8 D_801D1D9D;
extern u8 D_801D1D9E;
extern u8 D_801D1D9F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018E064[])(void);
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
extern s32 D_801D1DD8;
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
extern void (*D_8018E0A8[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018E124[];
extern s32 D_8018E144[];
extern u8 D_8018E1C0[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018E1E0[];
extern u8 D_8018E200[];
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
extern void (*D_8018E29C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018E318[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801D155C;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018E324[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018E32C[])(void);
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
extern void (*D_8018E3F4[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018E404[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018E414[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018E420[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018E380[];
extern u8   D_8018E394[];
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
extern void (*D_8018E438[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018E440[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018E448[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018E450[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018E458[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018E460[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018E468[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018E51C[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018E524[])(void);
extern void func_80169F00(void *a0);
extern char D_8018E4D4[];
extern char D_8018E494[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018E55C[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018E568[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018E5B0[])(void);
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
extern void (*D_8018E62C[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801D20F8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018E620[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018E664[];
extern unsigned short D_8018E66C[];
extern unsigned short D_8018E674[];
extern unsigned char D_801D2100[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801D20F8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018E67C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801D2234;
extern M2C_UNK D_801D2238;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D21C0;
extern void (*D_8018E6AC[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801D223C[];
extern u8 D_801D2244[];
extern u8 D_801D21F4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018E6B4[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018E6D0[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018E6D8[])(void);
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
extern void (*D_8018E740[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018E6E4;
extern u8 D_8018E6F0;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018E774[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018E77C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018E7D0[])(void);
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
extern u16 D_8018E804[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018E7F4[];
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
extern s32 D_8018E820;
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
extern void (*D_8018E898[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018E8A0[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018E8A8[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018E8B0[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018E8B8[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018E8C0[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018E8CC[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018E8D8[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018E8E4[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018E8F4[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018E904[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018E90C[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018E914[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018E91C[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018E924[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018E92C[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018E934[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018E93C[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018E944[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018E94C[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018E954[])(void);
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
extern void (*D_8018E95C[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018E964[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018E96C[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018E974[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018E97C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018E984[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018E98C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018E994[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018E99C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018E9A4[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018E9AC[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018E9B4[])(void);
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
extern void (*D_8018E9F8[])(void);
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
extern M2C_UNK D_8018E9BC;
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
extern void (*D_8018EA28[])(void);
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
extern void (*D_8018EA64[])(void);
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
extern void (*D_8018EABC[])();
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
extern void (*D_8018EACC[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018EAD4[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018EC3C[])();
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
extern void (*D_8018EC48[])();
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
extern M2C_UNK D_801D17A4;
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
extern s16 D_801D35C8;
extern int func_80178970(void);
extern void func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801D2978;
extern short D_801D363C;
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
extern s32 D_801D2DA4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801D2DCC;
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
extern s16 D_801D2D88;
extern s32 func_8017A3B0(void);
extern short D_801D2DC4;
extern short D_801D2DC0;
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
extern s16 D_801D2D8C;
extern u16 D_801D2E0C;
extern u16 D_801D2E0E;
extern u16 D_801D2E10;
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
extern s16 D_801D2E04;
extern s16 D_801D2E06;
extern s16 D_801D2E08;
extern s16 D_801D2DFC;
extern s16 D_801D2DFE;
extern s16 D_801D2E00;
extern void func_8017B7A8(void);
extern s16 D_801D2E1C;
extern s16 D_801D2E1E;
extern s16 D_801D2E20;
extern s16 D_801D2E24;
extern s16 D_801D2E26;
extern s16 D_801D2E28;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801D2E14;
extern short D_801D2E16;
extern short D_801D2E18;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801D2DAC;
extern SV4 D_801D2DB4;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801D2DD4[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801D2DD0)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018EE24[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8018EF40[])(void);
extern void func_8017C8B8(void *a0);
extern void func_8012C218(void *a0);
extern void func_8017CC60(void);
extern void (*D_8018EF98[])(void);
extern void func_8017CD10(void *a0);
extern void (*D_8018EFAC[])(void);
extern void func_8017D33C(void *a0);
extern void (*D_8018EFC0[])(void);
extern void func_8017D5DC(void *a0);
extern void func_8017D898(s32 arg0);
extern int func_8017FB44(int param_1);
extern void func_8017E810(void);
extern void func_8017E89C(void);
extern void func_8017E8DC(void);
extern void (*D_8018F1A4[])(void);
extern void func_8017E968(void *a0);
extern void func_8017EEDC(void);
extern s32 func_8017E9A4(s32 a0);
extern s32 func_8017E9E8(void);
extern void (*D_8018F1AC[])(void);
extern void func_8017EA0C(void *a0);
extern void func_8017EF04(void);
extern s32 func_8017EA48(s32 a0);
extern void func_800D1EBC(void);
extern void func_8017EB14(void);
extern void (*D_8018F1B8[])(void);
extern void func_8017EB34(void *a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017EB70(u8 *a0);
extern void (*D_8018F1C4[])(void);
extern void func_8017EBEC(void *a0);
extern void func_8017EF2C(void);
extern s32 func_8017EC28(s32 a0);
extern void (*D_8018F1D0[])(void);
extern void func_8017ED00(void *a0);
extern void func_8017F02C(void);
extern s32 func_8017ED3C(s32 arg0);
extern s32 func_8017ED78(void);
extern void func_8017EDE8(void);
extern void (*D_8018F1E0[])(void);
extern void func_8017EE08(void *a0);
extern M2C_UNK D_8018F1EC;
extern M2C_UNK D_8018F1F0;
extern void (*D_8018F204[])(void);
extern void func_8017EF54(void *a0);
extern void func_8012A094(s32 a0);
extern void func_8017F3E4(void *a0);
extern void func_8017F0F0(void);
extern void (*D_8018F20C[])(void);
extern void func_8017F9AC(s32 param_1, s16 *param_2);
extern void func_8017F558(s32 a0);
extern void func_8017F794(s32 a0);
extern void func_8017F844(s32 a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8013B7F4(void *a0, int a1);
extern s32 resLoad_lastId;
extern s32 func_8017FB74(void);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8017FB8C(void);
extern void func_8017FD30(void);
extern void func_8017FBBC(void);
extern s32 D_801D30C8;
extern void func_8017FD0C(void);
extern void func_8017FF68(void *a0, s32 a1);
extern code_fn D_801A4C2C[];
extern s32 func_8018030C();
extern void func_801801C4(int param_1);
extern void (*D_801A4C88[])(void);
extern void func_80180568(void *a0);
extern void func_801805A4(void);
extern void func_801805AC(void);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801806B8(s32 *a0);
extern void func_80180804(void * arg0);
extern void (*D_801A4DA4[])(void);
extern void func_80180E18(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_801806E0();
extern void func_80181044(int param_1);
extern void func_801810C8(void);
extern void func_801813E0(s32 *a0);
extern void func_80181760(void * arg0);
extern void func_80181788(s32 *a0);
extern void func_801819F0(void *a0);
extern void func_80181A20(void *arg0);
extern void func_80181D84(void);
extern void func_80181ED4(void);
extern void func_8018226C(void *a0);
extern void func_80178B18(s32 a0, s32 a1);
extern M2C_UNK D_801A4E88;
extern void func_80182294(void *arg0);
extern void func_801822D0(void *arg0);
extern code_fn D_801A4ED4[];
extern s32 func_80182438(s32 a0);
extern void func_801822F0(int param_1);
extern void (*D_801A4F00[])(void);
extern void func_801825EC(void *a0);
extern void func_801829B4(void);
extern s32 func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CF00(s32 a0);
extern void func_800233CC(void *a0, unsigned short a1);
extern s32 func_8012AD50(void *a0);
extern void func_801829BC(void *a0);
extern void (*D_801A4FA4[])(void);
extern void func_80182C68(void *a0);
extern void func_80182FD4(void *a0, void *a1);
extern void func_801833F0(void *ent, void *spr, u32 *q, u32 *ot);
extern void func_80183910(void);
extern void func_80183918(void);
extern void func_801839DC(s32 arg0, s32 arg1, s32 arg2);
extern void func_80183AF8(s32 arg0, Rec_8018A6A4_8018393C *arg1, s32 arg2, s32 arg3);
extern void func_8018393C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_80183A0C(s32 a0);
extern s16 D_801D3292;
extern void func_80183A84(s32 arg0);
extern s32 rand(void);      /* TU L951, verbatim */
extern void aF8018A860();
extern s32 func_80183BCC(void);
extern void func_80183C08(s32 a0, s32 a1);
extern void func_80183D30(s32 arg0);
extern void func_80183C54(void);
extern void func_80183FF4(void);
extern void func_80184040(s32 a0);
extern void func_80184018(s32 a0);
extern void func_801840C8(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_80184134(void *a0, void *a1, s16 a2);
extern void func_80184268(s32 a0, s16 a1, u16 a2);
extern void func_801841A4(s32 a0);
extern s32 func_80184384(void);
extern void func_8018421C(s32 a0, s32 a1);
extern void aF8018AFD0();
extern void func_801843C0(void);
extern void RotMatrixZ(s32 a0, void *a1);
extern void func_8004901C(void *a0, void *a1);
extern void func_80016638(void *a0, s32 a1, s32 a2);
extern void func_801844D4(s32 a0);
extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012BD14(s32 a0);
extern void func_8002D59C(s32 a0, u16 a1, s32 a2);
extern void func_801847B8(s32 a0);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern void func_80184A50(void *arg0);
/* ==== end §8b carried decl layer ==== */


#include "common.h"

void func_80184BD8(s32 a0) {
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8012B23C(void *a0);
    extern u16 D_801A751C[];
    extern u16 D_801A751E[];
    extern u16 D_801A7520[];
    extern void func_8001CA1C(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, s32 a1);
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
    extern s32 rand(void);

    extern u8 D_801A7280[];
    extern u8 D_801A7340[];
    extern u8 D_801A73C8[];
    extern u8 D_801A7488[];
    extern u8 D_801A756C[];
    extern u8 D_801A7590[];
    extern u8 D_801A7244[];
    extern u8 D_801A757C[];
    extern u8 D_801A7588[];

    s32 v0;
    s16 sVar1;
    u32 uVar3;
    u32 uVar5;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8012B23C((void *)a0);
    *(u16 *)(a0 + 0x12) = D_801A751C[*(s16 *)(a0 + 0xFC) * 4];
    *(u16 *)(a0 + 0x16) = D_801A751E[*(s16 *)(a0 + 0xFC) * 4];
    *(u16 *)(a0 + 0x1A) = D_801A7520[*(s16 *)(a0 + 0xFC) * 4];
    switch (*(s16 *)(a0 + 0x70)) {
    case 0:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A7280);
        func_8012A828(a0, (s32)D_801A7340);
        *(s16 *)(a0 + 2) = 1;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2000;
        break;
    case 1:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A73C8);
        func_8012A828(a0, (s32)D_801A7488);
        *(s16 *)(a0 + 2) = 4;
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
        *(s32 *)(a0 + 0x1C) = 8;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        *(u8 *)(a0 + 0xC0) = 1;
        *(u8 **)(a0 + 0x58) = D_801A756C;
        *(u16 *)(a0 + 0x5C) = 0x8000;
        *(s16 *)(a0 + 0xAE) = -9;
        *(u8 **)(a0 + 0xBC) = D_801A7590;
        *(u32 *)(a0 + 0xB4) = 0;
        *(u8 **)(a0 + 0x78) = D_801A7244;
        *(u32 *)(a0 + 0xC4) |= 2;
        uVar3 = func_8012C658(0x12F, 4, a0);
        *(u32 *)(a0 + 0xCC) = uVar3;
        break;
    case 2:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A7280);
        func_8012A828(a0, (s32)D_801A7340);
        *(s16 *)(a0 + 2) = 6;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2000;
        break;
    case 3:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A73C8);
        func_8012A828(a0, (s32)D_801A7488);
        *(s16 *)(a0 + 2) = 7;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        *(s32 *)(a0 + 0x1C) = 6;
        break;
    case 4:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A757C);
        func_8012A828(a0, (s32)D_801A7588);
        *(s16 *)(a0 + 2) = 8;
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x8000000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        break;
    case 5:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A7280);
        func_8012A828(a0, (s32)D_801A7340);
        *(s16 *)(a0 + 2) = 9;
        *(u16 *)(a0 + 0xFE) = *(u16 *)(*(s32 *)(a0 + 0x64) + 0x36);
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
        *(s16 *)(a0 + 0x100) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0xFE) * 6;
        sVar1 = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x70);
        if (sVar1 == 5) {
            *(s16 *)(a0 + 0x12) = (rand() % 0x60) - 0x30;
            *(s16 *)(a0 + 0x16) = (rand() % 0x60) - 0x60;
            sVar1 = (rand() % 0x60) - 0x40;
        } else {
            if (sVar1 != 6) {
                break;
            }
            *(s16 *)(a0 + 0x12) = (rand() % 0x60) - 0x30;
            *(s16 *)(a0 + 0x16) = (rand() % 0x20) - 0x20;
            sVar1 = (rand() % 0x60) - 0x50;
        }
        *(s16 *)(a0 + 0x1A) = sVar1;
    }
    uVar5 = rand();
    *(u32 *)(a0 + 0x94) = uVar5 & 0xF;
    *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
}




extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80185084(void *a0) {
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) =
        *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x4);
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) &= 0xEFFFFFFF;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x08000000;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x60000000;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
    *(s32 *)((s32)a0 + 0x4) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4) -
        (func_8004787C(*(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) & 0xFFF) << 8);
    *(s32 *)((s32)a0 + 0x8) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x8);
    *(s32 *)((s32)a0 + 0xC) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC) -
        (func_80047948(*(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) & 0xFFF) << 8);
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x18) / 2;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x1A) / 2;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x1C) / 2;
}


extern void func_8012C218(void *a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
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
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )
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
#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

void func_80185218(void *a0)
{
    u16 sv0[4];
    u16 sv1[4];
    s32 flag[4];
    s32 cnt;
    s32 tmp;
    s32 m;

    if (*(s16 *)((s32)a0 + 0xFE) == *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        if ((*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x100) & 0x4000) == 0) {
            goto low;
        }
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) - 0x200;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) - 0x200;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) >= 0x200) {
            goto tail;
        }
        func_80143B6C((s32)a0, 0);
    }
    func_8012C218(a0);
    return;

low:
    cnt = *(u16 *)((s32)a0 + 0x100) - 1;
    *(s16 *)((s32)a0 + 0x100) = cnt;
    if ((s16)cnt < 9) {
        *(s16 *)((s32)a0 + 0x100) = 0x18;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x70) == 5) {
            *(s16 *)((s32)a0 + 0x12) = rand() % 56 - 0x1C;
            *(s16 *)((s32)a0 + 0x16) = rand() % 96 - 0x60;
            *(s16 *)((s32)a0 + 0x1A) = rand() % 56 - 0x2C;
        } else if (*(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x70) == 6) {
            *(s16 *)((s32)a0 + 0x12) = rand() % 56 - 0x1C;
            *(s16 *)((s32)a0 + 0x16) = rand() % 32 - 0x20;
            *(s16 *)((s32)a0 + 0x1A) = rand() % 128 - 0x60;
        }
    }
    tmp = *(s16 *)((s32)a0 + 0x100);
    if (tmp < 0x10) {
        s32 g1;                       /* per-arm local: §5a cross-jump barrier, see header */
        g1 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)(g1 + 0x1A) = tmp * 0x300;
        *(s16 *)(g1 + 0x18) = tmp * 0x300;
    } else {
        s32 g2;                       /* per-arm local: §5a cross-jump barrier, see header */
        g2 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)(g2 + 0x1A) = (0x20 - tmp) * 0x300;
        *(s16 *)(g2 + 0x18) = (0x20 - tmp) * 0x300;
    }

tail:
    {
        s32 msk;
        msk = 0x80000000;             /* HOISTED OUT OF THE ARM ON PURPOSE — see header (3) */
        if (*(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x4) < 0) {
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= msk;
        } else {
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        }
    }

    *(s32 *)((s32)a0 + 0x4) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4);
    *(s32 *)((s32)a0 + 0x8) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x8);
    *(s32 *)((s32)a0 + 0xC) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC);

    sv0[0] = *(u16 *)((s32)a0 + 0x12);
    sv0[1] = *(u16 *)((s32)a0 + 0x16);
    sv0[2] = *(u16 *)((s32)a0 + 0x1A);

    m = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x34;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

    RotTransSV(sv0, sv1, flag);

    *(s16 *)((s32)a0 + 0x6) = sv1[0];
    *(s16 *)((s32)a0 + 0xA) = sv1[1];
    *(s16 *)((s32)a0 + 0xE) = sv1[2];
}



extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_801855C8(void *a0) {

    extern void (*D_801A75A0[])(void);
    extern u16 D_80126B96;
    s32 t;
    u16 *q;

    D_801A75A0[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        if (*(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) >= 0) {
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0x40;
            if (func_8012D624(a0, 0x1c, 0xa) == 1) {
                q = &D_80126B96;
                *q |= 0x200;
            }
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) + 0x40;
            if (*(s16 *)((s32)a0 + 0x70) == 1) {
                t = *(s32 *)((s32)a0 + 0x1c) - 1;
                *(s32 *)((s32)a0 + 0x1c) = t;
                if (t == 0) {
                    *(s32 *)((s32)a0 + 0x1c) = 8;
                    func_8012C658(0x12f, 3, (s32)a0);
                }
            }
        }
    }
}



extern void (*D_801A764C[])(void);

void func_801856B4(void *a0) {
    D_801A764C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801A7700[])(void);

void func_801856F0(void *a0) {
    D_801A7700[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018572C(void *a0) {
        *(s8 *)((s32)a0 + 0xc1) = 0;
        *(s16 *)((s32)a0 + 0x5e) = 0;
        *(s16 *)((s32)a0 + 0x5c) &= 0xc800;
    }




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80185744(s32 a0) {

    extern u8 D_801A7180[];
    extern u8 D_801A7160[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_8018B770[];
    s32 t;

    if (func_8012C354(a0, (s32)D_801A7180) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;

        t = *(s32 *)(a0 + 0xC4);
        *(s32 *)(a0 + 0xBC) = (s32)D_801A7160;
        *(s32 *)(a0 + 0xC4) = t | 0x2;

        func_8012A828(a0, (s32)D_8018B770);

        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(s16 *)(a0 + 0xFE) = 1;

        func_8012C658(0x164, 0x555, a0);
        func_8012C658(0x164, 0xAAA, a0);
        func_8012C658(0x164, 0x1000, a0);
    }
}


void func_801857E8(void *a0) {
        void *a1 = *(void **)((char *)a0 + 0x20);
        *(u16 *)((char *)a1 + 0x12) += *(u16 *)((char *)a0 + 0xfc);
    }




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);

void func_80185804(void *a0) {

    extern u8 D_8018B770[];
    extern u8 D_801A7244[];
    extern u8 D_801A7160[];
    if (func_8012C354((s32)a0, (s32)D_801A7244) != 0) {
        void *a2 = *(void **)((char *)a0 + 0x20);

        *(s32 *)((char *)a2 + 0x4) |= 0x80000000;
        *(u8 *)((char *)a0 + 0xC0) = 1;

        *(s32 *)((char *)a0 + 0xBC) = (s32)D_801A7160;
        *(s32 *)((char *)a0 + 0xC4) |= 0x2;

        func_8012A828((s32)a0, (s32)D_8018B770);

        *(u16 *)((char *)a0 + 0x2) = 1;
        *(u8 *)((char *)a0 + 0x75) = 0;
    }
}


extern void func_8012B2CC(s32 a0);


void func_80185888(s32 *a0) {
    s32 val_at_64;
    s32 deref;
    u16 val1, val2;
    s32 ptr_at_20;

    val_at_64 = *(s32 *)((char *)a0 + 0x64);
    deref = *(s32 *)((char *)val_at_64 + 0x20);
    val1 = *(u16 *)((char *)deref + 0x12);
    val2 = *(u16 *)((char *)a0 + 0x70);
    ptr_at_20 = *(s32 *)((char *)a0 + 0x20);

    *(u16 *)((char *)ptr_at_20 + 0x12) = val1 + val2;

    func_8012B2CC(a0);
}




void func_801858C4(void *a0)
{
    u16 v = *(u16 *)(a0 + 0x5E);
    if (v != 0x1D) {
        *(u16 *)(a0 + 0x5C) = 0;
        *(u16 *)(a0 + 0x2) = 0x7;
    } else {
        *(u16 *)(a0 + 0x5C) = 0x8000;
    }
    *(u8 *)(a0 + 0xC1) = 0;
    *(u16 *)(a0 + 0x5E) = 0;
}



extern void func_8012CBCC(s32 a0);
extern void func_8012E688(void*, s32, s32);

void func_801858F4(s32 a0) {
    if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x2000) {
        s16 v = *(s16 *)(a0 + 0x70);
        if (v != 0) {
            *(s16 *)(a0 + 0x2) = 2;
            ((void (*)(void*, s32, s32))func_8012E688)((void *)a0, 0xBA2, 0);
        } else {
            void *p = *(void **)(a0 + 0x20);
            *(s16 *)(a0 + 0x2) = 3;
            *(s32 *)(p + 0x4) |= 0x80000000;
            *(s32 *)(a0 + 0x1C) = 0x1E;
        }
    }
}



extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B864(s32 a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012E688(void*, s32, s32);

void func_80185978(s32 a0) {

    extern u8 D_801A7510[];
    extern s16 D_80126CB6;
    s32 r;

    if (func_8012BCCC(a0) > 0x63FFF) {
        *(u16 *)(a0 + 0x2) = 5;
    } else {
        r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                          func_8012B864(a0), 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        func_8012B1B4(a0, (s32)D_801A7510);
        *(s32 *)(a0 + 0x14) =
            *(s32 *)(a0 + 0x14) +
            ((D_80126CB6 - *(s16 *)(a0 + 0xA)) << 8);
        if (((s32 (*)(s32))func_8012CBCC)(a0)) {
            *(s16 *)(a0 + 0x16) = -0x18;
            ((void (*)(s32, s32, s32))func_8012E688)(a0, 0xBA2, 0);
        }
    }
}



extern void func_8012E688(void *a0, s32 a1, s32 a2);
extern void func_8012B23C(void *a0);

void func_80185A3C(void *a0) {

    extern u16 D_801A751C[];
    extern u16 D_801A751E[];
    extern u16 D_801A7520[];
    void *a1;

    if (--*(s32 *)((s32)a0 + 0x1c) == 0) {
        *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)a0 + 0x88);
        *(u16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0x8a);
        *(u16 *)((s32)a0 + 0xe) = *(u16 *)((s32)a0 + 0x8c);
        a1 = *(void **)((s32)a0 + 0x20);
        *(u32 *)((s32)a1 + 0x4) &= 0x7fffffff;
        func_8012E688(a0, 0x679, 0);
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012B23C(a0);
        *(u16 *)((s32)a0 + 0x12) = D_801A751C[*(s16 *)((s32)a0 + 0xfc) * 4];
        *(u16 *)((s32)a0 + 0x16) = D_801A751E[*(s16 *)((s32)a0 + 0xfc) * 4];
        *(u16 *)((s32)a0 + 0x1a) = D_801A7520[*(s16 *)((s32)a0 + 0xfc) * 4];
    }
}




extern s32 func_8012BD14(s32 a0);
extern void func_80143970(void *a0);
extern void func_8012E688(void *a0, s32 a1, s32 a2);

void func_80185B1C(s32 a0) {
    s32 ret = func_8012BD14(a0);
    if (ret <= 0x64000) {
        Struct_80185B1C *ptr = *(Struct_80185B1C **)(a0 + 0x20);
        *(s16 *)(a0 + 0x2) = 1;
        ptr->f1 = ptr->f1 & 0x7FFFFFFF;
        func_80143970((void *)a0);
        func_8012E688((void *)a0, 0xBA2, 0);
    }
}



extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012E688(void*, s32, s32);

void func_80185B8C(s32 a0) {

    extern u8 D_801A7510[];
    s16 sp10[3];
    s32 r;

    if (func_8012BCCC(a0) <= 0x38400) {
        *(u16 *)(a0 + 0x2) = 2;
    } else {
        sp10[0] = *(u16 *)(a0 + 0x6);
        sp10[2] = *(u16 *)(a0 + 0xE);
        r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                          func_8012B70C(sp10, (s16 *)(a0 + 0x88)), 4);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        func_8012B1B4(a0, (s32)D_801A7510);
        *(s32 *)(a0 + 0x14) =
            *(s32 *)(a0 + 0x14) +
            ((*(s16 *)(a0 + 0x8A) - *(s16 *)(a0 + 0xA)) << 8);
        if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x8000) {
            *(s16 *)(a0 + 0x16) = -4;
            ((void (*)(s32, s32, s32))func_8012E688)(a0, 0xBA2, 0);
        }
    }
}


void func_80185C68(void) {
}


/* func_80185C70 — per-frame entity tick:
 *  - decrement the timer at 0x1C if non-zero
 *  - fade the two u16 colour/alpha words at +0x18 / +0x1A of the display record
 *    hanging off 0x20 by 0x100 each
 *  - once the second one drops to <= 0x80, tear the entity down
 *
 * §71 sibling-first: DEFINE_func_801319E0() (engine_core.h L17451) is the same
 * `func_8002A04C(arg0); func_8012C218((void *)arg0);` teardown tail with arg0
 * living in $s0 across the calls — signature and casts copied from it.
 */

extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);

void func_80185C70(s32 arg0) {
    if (*(s32 *)(arg0 + 0x1C) != 0) {
        *(s32 *)(arg0 + 0x1C) -= 1;
    }
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) -= 0x100;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) -= 0x100;
    if (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) < 0x81) {
        if (*(s16 *)(arg0 + 0x70) == 1) {
            /* LOAD-BEARING: hoisting the argument load into its own local
             * emits `lw $a0,0xCC($s0)` ABOVE the guard branch and leaves the
             * beqz delay slot a nop. Inlining it at the call site instead
             * gives beqz/nop/lw -> 3 mismatches (class DELAY-SLOT). A/B-tested. */
            void *temp = *(void **)(arg0 + 0xCC);
            if (arg0 != 0) {
                func_8012C218(temp);
            }
        }
        func_8002A04C(arg0);
        func_8012C218((void *)arg0);
    }
}



extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);


void func_80185D28(s32 a0) {

    extern u8 D_801A75D8[];
    extern u8 D_8018B770[];
    extern u16 D_801A760C[];
    extern u16 D_801A760E[];
    extern u16 D_801A7610[];
    extern s16 D_801A7612[];
    if (func_8012C354(a0, (s32)D_801A75D8) != 0) {
        func_8012A828(a0, (s32)D_8018B770);
        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(u16 *)(a0 + 0x12) = D_801A760C[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x16) = D_801A760E[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x1A) = D_801A7610[*(s16 *)(a0 + 0xFC) * 4];
        *(s32 *)(a0 + 0x1C) = D_801A7612[*(s16 *)(a0 + 0xFC) * 4];
        func_8012C588(0x1C4, a0);
    }
}




extern void func_8012CBA4(s32 a0);
extern void func_8012DFD4(u8 *a0);

void func_80185DEC(s32 a0) {
    s32 t;

    func_8012CBA4(a0);
    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;
    if (t == 0) {
        *(s32 *)(a0 + 0x1C) = 0x6;
        *(s16 *)(a0 + 0x2) = 0x2;
    }
    func_8012DFD4((u8 *)a0);
}



extern void func_8012DFD4(u8 *a0);

void func_80185E40(s32 a0) {

    extern s16 D_801A7612[];
    s32 a1 = a0;
    s32 t = *(s32 *)(a1 + 0x1C) - 1;
    *(s32 *)(a1 + 0x1C) = t;
    if (t == 0) {
        s16 idx = *(s16 *)(a1 + 0xFC);
        s32 val = D_801A7612[idx * 4];

        *(s16 *)(a1 + 0x12) = -*(u16 *)(a1 + 0x12);
        *(s16 *)(a1 + 0x16) = -*(u16 *)(a1 + 0x16);
        *(s16 *)(a1 + 0x1A) = -*(u16 *)(a1 + 0x1A);
        *(s16 *)(a1 + 0x2) = 1;
        *(s32 *)(a1 + 0x1C) = val;
    }
    func_8012DFD4((u8 *)a0);
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 rand(void);


void func_80185EBC(s32 param_1)
{

    extern u8 D_801A7658[];
    extern u8 D_801A76B8[];
    s32 v0;
    s16 sVar1;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        func_8001CA1C(v0, (s32)D_801A7658);
        func_8012A828(param_1, (s32)D_801A76B8);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = 0x10;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1a) = 0x10;
        *(s32 *)(param_1 + 0x94) = rand() & 7;
        *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2c) |= 0x10;
        if ((u32)(*(u16 *)(param_1 + 0x70) - 1) >= 0x6fff) {
            *(u16 *)(param_1 + 0x70) = rand() & 0x77ff;
            sVar1 = 2;
        } else {
            sVar1 = 1;
        }
        *(s16 *)(param_1 + 2) = sVar1;
    }
}



extern s32 rand(void);
extern s32 func_8004787C(s32 a0);

void func_80185FA0(s32 a0) {
    s32 t;

    if (*(s32 *)(a0 + 0x1C) == 0) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        *(s16 *)(a0 + 0xFE) += 0x40;
        if (*(s16 *)(a0 + 0xFE) >= 0x800) {
            *(s16 *)(a0 + 0xFE) = 0;
            *(s32 *)(a0 + 0x1C) = rand() & 0x1F;
            *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x80000000;
        }
        t = (*(s16 *)(a0 + 0x70) * func_8004787C(*(s16 *)(a0 + 0xFE))) >> 12;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = t + 0x800;
    } else {
        *(s32 *)(a0 + 0x1C) -= 1;
    }
}



extern s32 rand(void);
extern s32 func_8004787C(s32 a0);

void func_8018606C(s32 a0) {
    s32 t;

    if (*(s32 *)(a0 + 0x1C) == 0) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        *(s16 *)(a0 + 0xFE) += 0x40;
        if (*(s16 *)(a0 + 0xFE) >= 0x800) {
            *(s16 *)(a0 + 0xFE) = 0;
            *(s32 *)(a0 + 0x1C) = rand() & 0x1F;
            *(s16 *)(a0 + 0x70) = rand() & 0x77FF;
            *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x80000000;
        }
        t = (*(s16 *)(a0 + 0x70) * func_8004787C(*(s16 *)(a0 + 0xFE))) >> 12;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = t + 0x800;
    } else {
        *(s32 *)(a0 + 0x1C) -= 1;
    }
}


INCLUDE_ASM("asm/ov_SC02_028/nonmatchings/ov_SC02_028_jr_80184BD8", func_80186144);

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern u8 D_801A9590[];
extern u8 D_801A9680[];
extern void func_801876C4(void *a0, s32 a1);

void func_80186210(void *a0) {

    extern u8 D_801A9590[];
    extern u8 D_801A9680[];

    if (func_8012C354((s32)a0, (s32)(D_801A9590 + ((*(u16 *)((s32)a0 + 0x70)) & 1) * 0x34)) != 0) {
        s32 sub;
        s32 v;

        *(u8 *)((s32)a0 + 0xC0) = 1;
        *(s32 *)((s32)a0 + 0xBC) = (s32)D_801A9680;
        *(s32 *)((s32)a0 + 0xB4) = -0x20EF;

        *(s32 *)((s32)a0 + 0xC4) |= 3;
        if (*(s32 *)((s32)a0 + 0xDC) == 0) {
            *(s32 *)((s32)a0 + 0xDC) = 0x40000;
        }

        if (*(s16 *)((s32)a0 + 0xFE) == 0) {
            *(s16 *)((s32)a0 + 0xFE) = 0x3C;
        }

        if ((*(u16 *)((s32)a0 + 0x70)) & 1) {
            sub = *(s32 *)((s32)a0 + 0x20);
            *(u16 *)(sub + 0x2C) |= 0x10;

            sub = *(s32 *)((s32)a0 + 0x20);
            v = 0x1666;
            *(s16 *)(sub + 0x1C) = v;
            *(s16 *)(sub + 0x1A) = v;
            *(s16 *)(sub + 0x18) = v;
        } else {
            v = 0x1000;
        }
        *(s16 *)((s32)a0 + 0x100) = v;
        __asm__ __volatile__("" ::: "memory");

        func_8012C588(0x153, (s32)a0);
        func_801876C4(a0, 1);
        *(s16 *)((s32)a0 + 0x2) = 1;
    }
}



extern void func_8012A828(s32 a0, s32 a1);
    extern short D_801AE158;
    void func_80186318(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        func_8012A828((int)arg0, (int)&D_801AE158);
    }


extern s32 func_8012BD3C(s32 a0, s32 a1, s32 a2);
extern s32 func_8012E778(s32 param_1, s32 param_2);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186344(s32 a0) {
    if (func_8012BD3C(a0, 0x400, *(s32 *)(a0 + 0xDC)) != 0) {
        *(s16 *)(a0 + 0x2) = 3;
    }

    if ((*(u16 *)(a0 + 0x72) & 0x4000) != 0) {
        if (func_8012E778(a0, 0x8C00B4) == 1) {
            func_8002D4C8(0x64A, 0);
        }
    }
}


void func_801863B4(void *a0) {
        M2C_FIELD(a0, s16 *, 0x2) = 4;
    }


extern u8 D_801AE220[];
extern s32 D_801A970C;
extern u8 D_801A971C[];
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012E778(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_80187780(s16 *a0, s32 a1, s32 a2, s32 a3);
extern s32 rand(void);

void func_801863C0(s32 a0) {
    s16 sp10[4];
    s16 sp18[4];
    register s32 ang1 __asm__("$20");
    register s32 ang2 __asm__("$19");
    register s32 negbase __asm__("$17");

    if ((*(s32 *)(a0 + 0xE0) & 1) == 0) {
        if (func_8012BD3C(a0, 0x400, *(s32 *)(a0 + 0xDC)) == 0) {
            *(s16 *)(a0 + 2) = 1;
        } else {
            func_8012A828(a0, (s32)D_801AE220);
            if (func_8012E778(a0, 0x8C00B4) == 1) {
                func_8002D4C8(0x64A, 0);
            }
        }
    }

    if (*(s32 *)(a0 + 0x94) == 0x19) {
        register s32 i __asm__("$16");
        func_8012F214(a0, (s32)&D_801A970C, (s32)sp10);
        func_8012F214(a0, (s32)&D_801A970C + 8, (s32)sp18);
        i = 0;
        {
            register s32 fieldval __asm__("$2");
            fieldval = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
            ang1 = fieldval + 0x400;
            negbase = -0x80000;
            ang2 = fieldval - 0x400;
        }
        for (; i < 6; i++) {
            __asm__ __volatile__("" : "=r"(ang1) : "0"(ang1));
            func_80187780(sp10, (s16)ang1, negbase - (rand() % 4) * 0x10000, 0);
            __asm__ __volatile__("" : "=r"(ang2) : "0"(ang2));
            func_80187780(sp18, (s16)ang2, negbase - (rand() % 4) * 0x10000, 0);
        }
        {
            register s32 halfbase __asm__("$19");
            register s32 ptr __asm__("$17");
            i = 0;
            halfbase = 0x80000;
            ptr = (s32)D_801A971C;
            while (i < 4) {
                func_8012F214(a0, ptr, (s32)sp10);
                func_80187780(sp10, 0, (rand() % 4) * 0x10000 + halfbase, 1);
                i++;
                ptr += 8;
            }
        }
    }
}


extern s32 func_8012BD14(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B2CC(s32 a0);

void func_801865A4(s32 a0)
{
    s32 v0;
    register s32 v1 __asm__("$3");

    if (func_8012BEE8(a0)) {
        if (func_8012BD14(a0) > 0x18FFF) {
            v1 = *(s32 *)(a0 + 0x20);
            *(u16 *)(a0 + 0x2) = 6;
            *(s32 *)(a0 + 0x1C) = 0x20;
            *(s32 *)(v1 + 4) &= 0x7FFFFFFF;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
            v1 = *(s32 *)(a0 + 0x20);
            *(u16 *)(v1 + 0x1C) = 1;
            *(u16 *)(v1 + 0x1A) = 1;
            *(u16 *)(v1 + 0x18) = 1;
            v0 = *(s32 *)(a0 + 0x20);
            *(u16 *)(v0 + 0x14) = 0;
            *(u16 *)(v0 + 0x10) = 0;
            v0 = *(s32 *)(a0 + 0x68);
            v1 = *(s32 *)(a0 + 0x20);
            *(u16 *)(v1 + 0x12) = *(u16 *)(v0 + 0xC);
            func_8012B2CC(a0);
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_028/nonmatchings/ov_SC02_028_jr_80184BD8", func_80186668);

    typedef struct { u8 b[8]; } Blk8_80186740;
    typedef struct {
        u8 c[8];
    } Blk8_80186594_80186740;
typedef struct {
    s32 a;      /* 0x00 -> D_801DA750 */
    s32 b;      /* 0x04 -> D_801DA754 */
} Pair8_8017DDC4_80182244_80186740;

/* func_80186740 -- ov_SC02_027, subseg ov_SC02_027_jr_8017D898 (106 ins).
 * Mass-lane fresh crack. Nearest exemplar ov_SC02_026:func_8017E72C is still
 * unmatched (INCLUDE_ASM), so no cousin body to adapt -- built straight from
 * the target .s.
 *
 * Symbol provenance:
 *   func_8012E9C0     NOT declared anywhere in this TU (only inside the
 *                     engine_core.h DEFINE_func_8012E9C0 macro, unexpanded
 *                     here) -> declared fresh, `void (int)`, no conflict.
 *   func_8002A520     NOT declared in this TU; matches the sibling-TU form
 *                     seen in ov_SC03_006/099 etc's jr_8012ACE0.c: `void (void*)`.
 *   func_8002A790     same as above, `void (void*)`.
 *   D_80126B5E        TU col-0 decl (this file:1789), adopted verbatim      `extern u16`
 *   D_80126B62        TU local-scope decl (this file:4233/6455/6538),
 *                     adopted verbatim                                     `extern u16`
 *   D_80126B66        TU col-0 decl (this file:1790), adopted verbatim     `extern u16`
 *   VectorNormalSS    TU col-0 decl (this file:1846), adopted verbatim     `s32 (void*,void*)`
 *   func_80131E00     TU local-scope decl (this file:6734/6813/6981),
 *                     adopted verbatim                                     `void (void*, s32)`
 *   func_8012A828     TU col-0/local decl (this file:4380 et al), adopted
 *                     verbatim                                             `void (s32, s32)`
 *   D_801AE3A8        not declared anywhere in-tree yet; passed as a bare
 *                     lui/addiu address (no load) -> declared as u8[] here.
 *
 * Residual-class note: field 0x76 is read (u16, for the decrement), stored,
 * then read AGAIN (s16, for the <=0 test). A plain second dereference of the
 * same `(u8*)a0+0x76` expression lets gcc-2.7.2's cse.c reuse the just-stored
 * HImode value and synthesize the sign test via `sll $r,16` instead of a
 * genuine `lh` -- confirmed by isolated probes (adds 1 spurious instruction,
 * every time another independent load/store shares the block, regardless of
 * source statement order or an intervening asm memory-clobber). Fix: (1) an
 * `__asm__ __volatile__("" ::: "memory")` between the store and the reload
 * to pin ordering, AND (2) drop the named `cnt`/`flags` locals in favor of
 * inlining both the 0x5C read-modify-write and the 0x76 compare directly at
 * their use sites -- naming the intermediate values reintroduces the same
 * cse fold even behind the barrier. Both edits were required together.
 */

extern void func_8012E9C0(int param_1);
extern void func_8002A520(void *a0);
extern void func_8002A790(void *a0);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_80131E00(void *a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);

void func_80186740(void *a0) {

    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    extern u8 D_801AE3A8[];
    extern u16 D_80126B62;
    u16 sv[4];
    s32 speed;

    func_8012E9C0((s32)a0);

    if (*(u16 *)((u8 *)a0 + 0x5E) != 0x1D) {
        if (*(u8 *)((u8 *)a0 + 0xC8)) {
            func_8002A520(a0);
        }
        if (*(u8 *)((u8 *)a0 + 0xC9)) {
            func_8002A790(a0);
        }
    }

    {
        s32 base = *(s32 *)((u8 *)a0 + 0x78);
        speed = (*(s16 *)((u8 *)a0 + 0x60) * *(s16 *)(base + 0x30)) >> 12;
    }
    if (speed <= 0) {
        speed = 1;
    }

    *(u16 *)((u8 *)a0 + 0x76) = *(u16 *)((u8 *)a0 + 0x76) - speed;
    __asm__ __volatile__("" ::: "memory");

    {
        *(u16 *)((u8 *)a0 + 0x5C) = *(u16 *)((u8 *)a0 + 0x5C) & 0xFFFE;
        if (*(s16 *)((u8 *)a0 + 0x76) <= 0) {
            *(u16 *)((u8 *)a0 + 0x5C) = 0;
            func_80131E00(a0, 0xE);
        } else {
            if (speed > 0x10) {
                speed = 0x10;
            }

            sv[0] = *(u16 *)((u8 *)a0 + 6) - D_80126B5E;
            sv[1] = *(u16 *)((u8 *)a0 + 0xA) - D_80126B62;
            sv[2] = *(u16 *)((u8 *)a0 + 0xE) - D_80126B66;
            VectorNormalSS(sv, (u8 *)a0 + 0x102);

            speed += 8;
            {
                s32 p0 = speed * *(s16 *)((u8 *)a0 + 0x102);
                s32 p1 = speed * *(s16 *)((u8 *)a0 + 0x104);
                s32 p2 = speed * *(s16 *)((u8 *)a0 + 0x106);
                *(s32 *)((u8 *)a0 + 0x1C) = 0x10;
                *(s16 *)((u8 *)a0 + 0x102) = p0 >> 12;
                *(s16 *)((u8 *)a0 + 0x104) = p1 >> 12;
                *(s16 *)((u8 *)a0 + 0x106) = p2 >> 12;
            }
        }
    }

    *(s16 *)((u8 *)a0 + 6) = *(u16 *)((u8 *)a0 + 0x88);
    *(s16 *)((u8 *)a0 + 0xA) = *(u16 *)((u8 *)a0 + 0x8A);
    *(s16 *)((u8 *)a0 + 0xE) = *(u16 *)((u8 *)a0 + 0x8C);
    func_8012A828((s32)a0, (s32)D_801AE3A8);
}


extern s32 func_8004787C(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_80186D20();

void func_801868E8(s32 self) {
    s32 var;

    var = -(func_8004787C((*(s32 *)(self + 0x1C) << 10) & 0xC00) >> 12);
    *(u16 *)(self + 0x6) += *(u16 *)(self + 0x102) * var;
    *(u16 *)(self + 0xA) += *(u16 *)(self + 0x104) * var;
    *(u16 *)(self + 0xE) += *(u16 *)(self + 0x106) * var;
    if (func_8012BEE8(self) != 0) {
        *(u8 *)(self + 0xC1) = 0;
        *(u16 *)(self + 0x5E) = 0;
        func_80186D20(self);
    }
}


extern u8 D_801A95F8;
extern void func_80143CD4(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800CB0E8(s32 a0);

void func_80186994(s32 param_1)
{
    s32 v0;

    v0 = *(u16 *)(param_1 + 0x5C);
    *(s32 *)(param_1 + 0x1C) = 0x78;
    *(u16 *)(param_1 + 0x5C) = v0 & 0xFFFE;
    func_80143CD4(param_1);
    func_8002D4C8(0x47B, 0);
    func_8002D4C8(0x478, 0);
    func_800CB0E8(param_1);
    *(s32 *)(param_1 + 0xCC) = (s32)&D_801A95F8;
}


extern s32 func_8012BEE8(s32 a0);
extern u8 D_801A95F8;
extern void func_80186D20();

void func_801869FC(s32 self) {
    s32 p;
    s32 q;
    s32 e;

    p = *(s32 *)(self + 0xCC);
    q = *(s32 *)(self + 0x20);
    *(u16 *)(q + 0x10) = *(u16 *)(p + 0);
    *(u16 *)(q + 0x14) = *(u16 *)(p + 4);
    p += 8;
    if (*(s16 *)(p + 6) == 0x7FFF) {
        *(s32 *)(self + 0xCC) = (s32)&D_801A95F8;
    } else {
        *(s32 *)(self + 0xCC) = p;
    }
    if (func_8012BEE8(self) != 0) {
        *(u8 *)(self + 0xC1) = 0;
        *(u16 *)(self + 0x5E) = 0;
        e = *(s32 *)(self + 0x20);
        *(u16 *)(e + 0x14) = 0;
        *(u16 *)(e + 0x10) = 0;
        func_80186D20(self);
    }
}


void func_80186A8C(void *a0) {
        *(s16 *)((char *)a0 + 0x5c) = 0;
        *(s16 *)((char *)a0 + 0x98) = 0;
        *(s32 *)((char *)a0 + 0x1c) = 0;
    }


extern s16 D_80126CE0;
extern s32 D_801D3378;
extern s32 D_801D337C;

void func_80186A9C(s32 arg0_)
{
    register s32 arg0 __asm__("$7");
    register s32 prev __asm__("$5");
    register u16 flags __asm__("$2");
    s32 a;
    s32 diff;
    s32 v;
    register s32 d __asm__("$2");
    s32 spd;
    s32 e1;
    s32 e2;
    s32 boost;
    s32 tail;

    arg0 = arg0_;
    *(s16 *)(arg0 + 0x5C) = 0;
    boost = (*(u16 *)(arg0 + 0x70) & 1) * 819;
    tail = boost * 2;
    a = D_80126CE0;
    if (a == 0) {
        D_801D3378 = (s16)(boost * 2) + 0x1000;
        D_801D337C = (s16)(boost * 2) + 0x1000;
    }
    spd = (s16)(boost * 2) + 0x1000;
    a = (spd * (0x90 - a)) / 0x90;

    diff = D_801D3378 - a;
    if (diff > 0) {
        D_801D3378 -= diff >> 2;
    } else if (diff < 0) {
        D_801D3378 += (-diff) / 4;
    }

    prev = D_801D337C;
    e1 = *(s32 *)(arg0 + 0x20);
    v = D_801D3378 - prev + spd;
    D_801D337C = spd;
    flags = *(u16 *)(e1 + 0x2C);
    D_801D3378 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;

    e2 = *(s32 *)(arg0 + 0x20);
    d = __builtin_abs(v);
    *(s16 *)(e2 + 0x1C) = d;
    *(s16 *)(e2 + 0x18) = d;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = tail + 0x1000;
}


extern s32 func_8012BD14(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186BCC(s32 a0) {
    s32 var_s0;

    var_s0 = 0x10000;
    *(s16 *)(a0 + 0x5C) = 0;
    *(s32 *)(a0 + 0x1C) = 0x1E;
    if ((*(u16 *)(a0 + 0x70) & 1) == 0) {
        var_s0 = 0x6400;
    }
    if (func_8012BD14(a0) < var_s0) {
        func_8002D4C8(0x64B, 0);
    } else {
        func_8002D4C8(0x652, 0);
    }
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_80186C8C();
extern void func_8002AC00(s32 arg0);
extern void func_80130D48(s32 a0);

void func_80186C2C(void *a0) {
    s32 *ent = *(s32 **)((s32)a0 + 0x20);
    ent[1] ^= 0x80000000;
    if (func_8012BEE8((s32)a0)) {
        func_8002AC00(0xF);
        func_80130D48((s32)a0);
        func_80186C8C(a0);
    }
}


extern void func_8002A04C(s32 a0);
extern void func_8012C098(void *param_1);

s32 func_80186C8C(s32 arg0)
{
    s32 temp;

    func_8002A04C(arg0);
    if ((*(s16 *)(arg0 + 0x70) & 0xC000) != 0) {
        func_8012C098((void *)arg0);
    } else {
        temp = *(s32 *)(arg0 + 0x20);
        *(s16 *)(arg0 + 0x2) = 5;
        *(s8 *)(arg0 + 0xC1) = 0;
        *(s32 *)(arg0 + 0x1C) = 0x78;
        *(s16 *)(arg0 + 0x5E) = 0;
        *(s16 *)(arg0 + 0x5C) = 0;
        *(s32 *)(temp + 0x4) |= 0x80000000;
        *(u16 *)(arg0 + 0xAA) = 0;
        *(s16 *)(arg0 + 0x6) = *(u16 *)(arg0 + 0x88);
        *(s16 *)(arg0 + 0xA) = *(u16 *)(arg0 + 0x8A);
        *(s16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0x8C);
    }
}


void func_80186D20(s32 arg0) {
    register s32 a3 __asm__("$7");
    u16 a1;
    u16 b;
    u16 c;
    u16 d;
    u16 flags;
    s32 e;

    a3 = arg0;
    *(u16 *)(a3 + 2) = 1;
    d = *(u16 *)(*(s32 *)(a3 + 0x78) + 2);
    a1 = *(u16 *)(a3 + 0x88);
    b = *(u16 *)(a3 + 0x8A);
    c = *(u16 *)(a3 + 0x8C);
    flags = *(u16 *)(a3 + 0x70);
    *(u16 *)(a3 + 6) = a1;
    *(u16 *)(a3 + 0xA) = b;
    *(u16 *)(a3 + 0xE) = c;
    *(u16 *)(a3 + 0x5C) = d;
    if (flags & 1) {
        e = *(s32 *)(a3 + 0x20);
        *(u16 *)(e + 0x2C) |= 0x10;
        e = *(s32 *)(a3 + 0x20);
        *(u16 *)(e + 0x1C) = 0x1666;
        *(u16 *)(e + 0x1A) = 0x1666;
        *(u16 *)(e + 0x18) = 0x1666;
        *(u16 *)(a3 + 0x100) = 0x1666;
    }
}


extern void (*D_801A973C[])(void);

void func_80186D94(void *a0) {
    D_801A973C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80186DD0(s32 param_1)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern u8 D_801ACF50[];
    typedef struct { u8 b[8]; } Blk8;
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    func_8001C214(v0, (s32)D_801ACF50);
    *(u16 *)(param_1 + 0xFC) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0x36);
    *(Blk8 *)(*(s32 *)(param_1 + 0x20) + 0x18) =
        *(Blk8 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x18);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
        *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x2C);
    *(u16 *)(param_1 + 2) = 1;
}


extern void func_8012C218(void *a0);
    void func_80186E88(s32 arg0) {
        s32 *p = *(s32 **)((s32)arg0 + 0x64);
        if (*(s16 *)((s32)p + 0x36) != *(s16 *)((s32)arg0 + 0xfc)) {
            ((void (*)(void))func_8012C218)();
        }
    }



extern void (*D_801A9A58[])(void);

void func_80186EC4(void *a0) {
    D_801A9A58[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern u8 D_801A9754[];
extern void func_8012E8A8(u8 *a0);

void func_80186F00(void *a0) {

    extern u8 D_801A9754[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801A9754) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (!(v0 & 1)) {
        func_8012E8A8((u8 *)a0);
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0xFC);
    *(unsigned short *)((s32)a0 + 0x2) = 1;
    *(unsigned short *)((s32)a0 + 0x104) = v1;
}


INCLUDE_ASM("asm/ov_SC02_028/nonmatchings/ov_SC02_028_jr_80184BD8", func_80186F78);

extern s32 D_801A9788;
    void func_80187094(s32 *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x3;
        *(s32 *)((s32)a0 + 0xcc) = &D_801A9788;
    }


INCLUDE_ASM("asm/ov_SC02_028/nonmatchings/ov_SC02_028_jr_80184BD8", func_801870AC);

extern s32 D_801A9910;

void func_80187140(s32 a0) {
    s32 a1 = *(s32 *)(a0 + 0x64);
    s32 v1 = *(s16 *)(a0 + 0xFC);
    *(s16 *)(a0 + 2) = 5;
    *(s32 *)(a0 + 0xCC) = &D_801A9910;
    *(s32 *)(a0 + 0x1C) = 0;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0x100) = 0;
    if (v1 == *(s16 *)(a1 + 0x36)) {
        *(s32 *)(a1 + 0xE0) |= 1;
    }
}


typedef struct {
    s32 w[4];
} Rec16_8017DDC4_80187190;

/* func_80187190 -- ov_SC02_026, subseg ov_SC02_026_jr_8017C180 (133 ins). */

extern void func_8012F14C(s32 a0, s32 a1, s32 a2);  /* TU:329 file scope, verbatim */
extern s32  func_8012BEE8(s32 a0);                  /* TU:4993/5216/7272, verbatim */
extern void func_8012CC1C(s32 arg0, s32 arg1);      /* fleet-canonical void; $v0 used -> cast */
extern s32  func_80187414();
extern void func_8018754C(s32 a0, s32 a1);
extern void func_80187490(s32 a0);
extern void func_801873A4(s32 a0);
extern void func_801875F0(s32 a0);

void func_80187190(s32 a0) {
    typedef struct {
        u8 c[8];
    } Blk8_80187190;  /* alignment 1 -> lwl/lwr + swl/swr block move (S160a) */
    extern Blk8_80187190 D_801A9A70;
    Blk8_80187190 sv;
    s32 obj;
    s32 p;

    if (func_80187414(a0) == 1) {
        return;
    }
    obj = *(s32 *)(a0 + 0x64);
    if (*(u16 *)(a0 + 0x34) == 0) {
        s32 t = *(s32 *)(a0 + 0x1C) + 1;
        *(s32 *)(a0 + 0x1C) = t;
        if (t == 0x1D) {
            *(s16 *)(a0 + 0x100) = 1;
        }
        p = *(s32 *)(a0 + 0xCC);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = *(u16 *)(p + 6);
        func_8012F14C(*(s32 *)(obj + 0x20) + 0x34, p, (s32)&sv);
        *(u16 *)(a0 + 6) = *(u16 *)&sv.c[0];
        *(u16 *)(a0 + 0xA) = *(u16 *)&sv.c[2];
        *(u16 *)(a0 + 0xE) = *(u16 *)&sv.c[4];
        p += 8;
        if (*(s16 *)(p + 6) == 0x7FFF) {
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s32 *)(a0 + 0x48) = 0x18000;
            *(s16 *)(a0 + 0x102) = 0;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) | 0x10;
            func_8018754C(a0, 0xFFF00000);
        } else {
            *(s32 *)(a0 + 0xCC) = p;
        }
    } else {
        s32 r;
        s32 c;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) + 0x80;
        if (*(s16 *)(a0 + 0x102) < 0x20) {
            s32 q = *(s32 *)(a0 + 0x20);
            u16 w;
            *(s16 *)(a0 + 0x102) = *(s16 *)(a0 + 0x102) + 1;
            w = *(u16 *)(q + 0x1C) + 0x100;
            *(u16 *)(q + 0x1C) = w;
            *(u16 *)(q + 0x1A) = w;
            *(u16 *)(q + 0x18) = w;
        }
        sv = D_801A9A70;
        *(s16 *)&sv.c[2] =
            (*(s16 *)&sv.c[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A)) >> 12;
        r = ((s32 (*)(s32, s32))func_8012CC1C)(a0, (s32)&sv);
        if ((r & 0x2000) == 0) {
            c = func_8012BEE8(a0);
        } else {
            c = r & 0x8000;
        }
        if (c != 0) {
            *(s32 *)(obj + 0xE0) = *(s32 *)(obj + 0xE0) & ~1;
            func_80187490(a0);
            return;
        }
    }
    func_801873A4(a0);
    if (*(s16 *)(a0 + 0x100) != 0) {
        func_801875F0(a0);
    }
}


INCLUDE_ASM("asm/ov_SC02_028/nonmatchings/ov_SC02_028_jr_80184BD8", func_801873A4);

extern void func_80187454(void);

s32 func_80187414(void *a0) {
    u8 *a0_byte = (u8 *)a0;
    s32 *v0 = *(s32 **)(a0_byte + 0x64);
    s16 v1 = *(s16 *)((u8 *)v0 + 0x36);
    s16 v2 = *(s16 *)(a0_byte + 0xFC);

    if (v1 == v2) {
        return 0;
    }
    func_80187454();
    return 1;
}


extern void func_8002D59C(s32 a0, u16 a1, s32 a2);
extern void func_8012C218(void *a0);

/* §37/§124 def-side asm-label alias: the TU declares `extern void func_80187454(void);`
 * (L4194) for the no-argument caller at L4205, while the byte-true definition takes a
 * pointer in $a0 (sw $s0 / addu $s0,$a0,$zero prologue). Neither side can move, so the
 * definition gets a private C identifier and binds the emitted symbol with a GNU asm
 * label. Same class as banked func_8017EF54 (ov_SC06_008_jr_8017C294.c:4152). */
void aF80187454(void *arg0) __asm__("func_80187454");

void aF80187454(void *arg0) {
    func_8002D59C(4, 0x64E, *(u16 *)((char *)arg0 + 0x104));
    func_8012C218(arg0);
}


extern void func_8002D59C(s32 a0, u16 a1, s32 a2);

void func_80187490(s32 a0) {
    s32 *s1;
    s32 *s0;
    s16 *v1;

    s1 = (s32 *)a0;
    s0 = *(s32 **)((u8 *)s1 + 0x64);
    func_8002D59C(4, 0x64E, *(u16 *)((u8 *)s1 + 0x104));
    *(s32 *)((u8 *)s1 + 0x4) = *(s32 *)((u8 *)s0 + 0x4);
    *(s32 *)((u8 *)s1 + 0x8) = *(s32 *)((u8 *)s0 + 0x8) - 0x260000;
    *(s32 *)((u8 *)s1 + 0xC) = *(s32 *)((u8 *)s0 + 0xC);
    *(u16 *)((u8 *)s1 + 0x70) = 1;
    v1 = *(s16 **)((u8 *)s1 + 0x20);
    if (*(u16 *)((u8 *)s0 + 0x70) & 1) {
        *(u16 *)((u8 *)v1 + 0x14) = 0;
        *(u16 *)((u8 *)v1 + 0x12) = 0;
        *(u16 *)((u8 *)v1 + 0x10) = 0;
        *(u16 *)((u8 *)v1 + 0x1C) = 1;
        *(u16 *)((u8 *)v1 + 0x1A) = 1;
        *(u16 *)((u8 *)v1 + 0x18) = 1;
    } else {
        *(u16 *)((u8 *)v1 + 0x14) = 0;
        *(u16 *)((u8 *)v1 + 0x12) = 0;
        *(u16 *)((u8 *)v1 + 0x10) = 0;
        *(u16 *)((u8 *)v1 + 0x2C) = *(u16 *)((u8 *)v1 + 0x2C) & 0xFFEF;
    }
    *(u16 *)((u8 *)s1 + 0x2) = 1;
}


INCLUDE_ASM("asm/ov_SC02_028/nonmatchings/ov_SC02_028_jr_80184BD8", func_8018754C);

INCLUDE_ASM("asm/ov_SC02_028/nonmatchings/ov_SC02_028_jr_80184BD8", func_801875F0);

INCLUDE_ASM("asm/ov_SC02_028/nonmatchings/ov_SC02_028_jr_80184BD8", func_801876C4);

typedef struct {
    s32 a;      /* 0x00 -> D_801D0120 */
    s32 b;      /* 0x04 -> D_801D0124 */
} Pair8_8017DDC4_80187780;

/* func_80187780 (ov_SC02_026, 154 ins) — spawns a type-0x3B object at *a0,
 * seeds its sub-record (0x20 handler table / 0x27 / 0x28 / 0x2A), picks a
 * random +-(rand%200) speed around 0x400, then either (a3 == 0) builds a
 * random launch vector and runs it through func_80049CAC/func_800484EC, or
 * (a3 != 0) copies the caller's position into the object and arms it.
 * MATCH (154/154 ins), match_one standalone.
 *
 * STEP-0 SIBLING (§160g): func_80181F88 in src/ov_SC03_098/..._jr_8017D898.c
 * (L5153) is the same routine for object type 0x41 — identical callee set
 * {func_801290DC, rand, func_80049CAC, func_800484EC}, identical sub-record
 * offsets, identical `sign * (h % 128) - 0x300` / `p1 + sign * (h % 0x300)`
 * launch vector and identical srcvec[2]/trailing[1]/trailing[0]/trailing[2]
 * statement order. That draft's local/frame shape was reused verbatim:
 * s16 srcvec[4] @sp+0x10, the 32-byte block @sp+0x18, s32 trailing[4]
 * @sp+0x38 -> frame 0x68 with 8 saved registers at 0x48..0x64.
 *
 * DELTA vs the sibling, and the two levers this function needed:
 *
 *  1. §48 STRUCT ASSIGN. This variant seeds the func_80049CAC output block
 *     from D_800AE620 first (`m = D_800AE620;`). The 32-byte, 4-aligned
 *     struct routes move_by_pieces to the plain lw/lw/lw + sw/sw/sw grouping
 *     (3,3,2) the target emits — not lwl/lwr, and not a memcpy call. It is
 *     written immediately before the func_80049CAC call, which is where the
 *     block lands in the target's schedule.
 *
 *  2. BRANCH POLARITY on the +-speed pick (§3-T4/T7, and the same law the TU
 *     records at L4765 for func_801818xx). The target is
 *         bnez $v0,L / negu $v0,$s0 (DELAY SLOT) / addiu $v0,$v0,0x400
 *         / j / L: addiu $v0,$s0,0x400
 *     i.e. the delay-slot insn is the head of the FALL-THROUGH arm, moved
 *     (not copied) by fill_slots_from_thread. That requires the THEN arm to
 *     be the NEGATED one: `if ((rand() & 1) == 0) spd = -base + 0x400; else
 *     spd = base + 0x400;`. The natural spelling `if (rand() & 1) spd = base
 *     + 0x400;` inverts the branch. `-base + 0x400` (not `0x400 - base`) is
 *     what gives negu + addiu rather than a li/subu pair.
 *
 *  3. THE ONE-LINE LEVER THAT CLOSED THE LAST 8: a leading `s32 p1 = a1;`.
 *     Without it the residual is a pure SCHEDULE-REORDER/8 confined to the
 *     prologue — same 154 instructions, same registers, only
 *     `addiu $a0,$zero,0x3B` and `addu $a1,$s3,$zero` sitting BELOW the four
 *     `sw $sN`/`move $sN,$aN` pairs instead of woven into them:
 *         target: sw s3 / move s3,a0 / li a0,0x3B / sw s6 / move s6,a1 /
 *                 move a1,s3 / sw s5 / move s5,a2 / sw s4 / move s4,a3
 *         mine:   sw s3 / move s3,a0 / sw s6 / move s6,a1 / sw s5 /
 *                 move s5,a2 / sw s4 / move s4,a3 / li a0,0x3B / move a1,s3
 *     Prologue saves are sched2-scheduled (toplev.c:3103 threads the prologue
 *     between global_alloc and sched2). sched2 runs BACKWARD and every insn
 *     here ties at priority 1 and at class 3 against the last-scheduled
 *     `sw $ra`, so rank_for_schedule (sched.c:2385) falls all the way through
 *     to its final tie-break `INSN_LUID (tmp) - INSN_LUID (tmp2)` = stream
 *     order, and higher LUID wins. So the ONLY way to weave the arg setup
 *     into the saves is to make the a2/a3 parameter copies come LATER in the
 *     stream than it — and the whole chain was read off `cc1 -dS`:
 *
 *       (a) sched.c:3189-3215 ("at the start of a function, before reload,
 *           don't delay getting parameters from hard registers") sets
 *           INSN_REF_COUNT = 1 — never schedulable — on the LEADING RUN of
 *           `(set pseudo hardreg)` insns at the head of bb0, and STOPS at the
 *           first insn that is not one (a NOTE stops it too). Unlevered, all
 *           four parameter copies are in that run, so all four stay above the
 *           call's arg setup forever and out-LUID it at sched2.
 *       (b) A leading `p1 = a1;` makes cse DELETE the original a1 parameter
 *           copy (insn 6 becomes a NOTE) and rewrite the later `p1 = a1` copy
 *           to read `(reg:SI 5 a1)` directly — so it survives as a
 *           HIGHER-UID insn further down the stream. That NOTE terminates the
 *           pin run after the a0 copy alone: the a1, a2 and a3 copies are now
 *           schedulable by sched1.
 *       (c) sched1's `adjust_priority` birthing boost (pre-reload only;
 *           `birthing_insn_p` = dest set exactly once) then boosts those three
 *           single-set copies to 0x7f000001 while the arg setups stay at 1.
 *           sched1 is BACKWARD, so boosted = picked first = emitted LAST, and
 *           the post-sched1 stream becomes exactly
 *               4 (s3=a0) / 19 ($a0=0x3B) / 16 (s6=a1) / 21 ($a1=s3) /
 *               8 (s5=a2) / 10 (s4=a3) / call
 *           which is the target's bb0 order verbatim. sched2 then has nothing
 *           left to undo.
 *
 *     The A/B fingerprint of the same mechanism: a leading copy of a LATER
 *     parameter frees strictly fewer copies — `p2 = a2` alone reads 7
 *     mismatched, `p3 = a3` alone reads 8 (frees nothing), copying all three
 *     also MATCHes. So the lever is "break the pin run as EARLY as the target
 *     needs", not "copy the parameter you happen to use".
 *
 *     This is the same lever the ov_SC03_098 sibling carries as its own
 *     leading `p1 = a1;`, and the precise mechanism behind
 *     docs/matching-cookbook.md L2465's one-line note that "a leading
 *     `pb = param_3;` rides sched.c:3191-3215's 'don't delay getting
 *     parameters' pin". A/B, same file, one line: 8 mismatched -> MATCH.
 *     No register pins, no permuter — the draft compiles standalone, so it
 *     is free to propagate to this family's other two binaries (§37).
 *
 * DECLARATION SURFACE (§52b/§161c; whole-TU one-pass grep, D2):
 *   AGREE VERBATIM with the destination TU (ov_SC02_026_jr_8017C180.c), so
 *   they merge silently —
 *     func_801290DC  TU:5246  `extern u8 *func_801290DC(s32 a0, u8 *a1);`
 *     func_80049CAC  TU:2645/3421  `extern void func_80049CAC(s32, s32);`
 *     func_800484EC  TU:241/3529   `extern void func_800484EC(s32,s32,s32);`
 *     rand           TU:957 `extern s32 rand(void);` (TU:1092 has the
 *                    equivalent `int` form; never redeclared)
 *   NOT declared anywhere in this TU, nor at file scope in common.h /
 *   src/shared/engine_core.h (engine_core.h's D_800AE620 spellings all live
 *   INSIDE DEFINE_ macro bodies, i.e. block scope, and this TU invokes none
 *   of them), so they are fresh here —
 *     D_801A9AA0     real dlabel, asm/ov_SC02_026/data/tail.data.s:35987;
 *                    used only as an address -> unsized `s32 []`
 *     D_800AE620     the shared 32-byte, 4-aligned engine block; typed with
 *                    a function-unique struct name so it cannot collide with
 *                    the `Blk20` / `Mat32` spellings other TUs use.
 */

extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);

typedef struct { s32 w[8]; } Blk32_8017F76C_80187780;   /* 32 bytes, align 4 */

s32 func_80187780(s16 *a0, s32 a1, s32 a2, s32 a3) {

    extern s32 D_801A9AA0[];
    extern Blk32_8017F76C_80187780 D_800AE620;
    s32 p1 = a1;
    u8 *obj;
    s32 sub;
    s32 base;
    s32 spd;

    obj = func_801290DC(0x3B, (u8 *)a0);
    if (obj == 0) {
        return 0;
    }
    sub = *(s32 *)(obj + 0x20);
    *(s32 *)(sub + 0x20) = (s32) D_801A9AA0;
    *(u8 *)(sub + 0x27) = 0x56;
    *(u16 *)(sub + 0x28) = 0x2A0;
    *(u16 *)(sub + 0x2A) = 0x1A0;

    base = rand() % 200;
    if ((rand() & 1) == 0) {
        spd = -base + 0x400;
    } else {
        spd = base + 0x400;
    }
    *(u16 *)(sub + 0x1A) = spd;
    *(u16 *)(sub + 0x18) = spd;

    if (a3 == 0) {
        s32 sign;
        s32 h;
        s32 mod128;
        s32 r;
        s16 srcvec[4];
        Blk32_8017F76C_80187780 buf;
        s32 trailing[4];

        r = rand();
        sign = -1;
        if ((r & 1) != 0) {
            sign = 1;
        }
        h = (s16) r;
        mod128 = h % 128;

        srcvec[2] = 0;
        trailing[1] = 0;
        trailing[0] = 0;
        trailing[2] = a2;

        srcvec[0] = (s16) (sign * mod128 - 0x300);
        srcvec[1] = (s16) (p1 + sign * (h % 0x300));

        buf = D_800AE620;

        func_80049CAC((s32) srcvec, (s32) &buf);
        func_800484EC((s32) &buf, (s32) trailing, (s32) (obj + 0x10));
        *(s32 *)(obj + 0x1C) = 0x2D;
    } else {
        *(s32 *)(obj + 0x2C) = a0[0];
        *(s32 *)(obj + 0x30) = a0[1];
        *(s32 *)(obj + 0x34) = a0[2];
        *(u16 *)(obj + 0x28) = rand() % 2 + 6;
        *(s32 *)(obj + 0x14) = a2;
        *(s32 *)(obj + 0x1C) = 0xA;
        *(u16 *)(obj + 0x2) = *(u16 *)(obj + 0x2) + 1;
    }
    return (s32) obj;
}


extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);

void func_801879E8(struct vec *arg0) {
    if (*(u16 *)((s32)arg0 + 2) == 0) {
        func_8012931C(arg0);
        if (*(s32 *)((s32)arg0 + 0x1C) < 0x23) {
            *(s32 *)((s32)arg0 + 0x14) += 0x10000;
        }
        if (--*(s32 *)((s32)arg0 + 0x1C) == 0) {
            func_801292C8((u8 *)arg0);
        }
    } else {
        func_8012931C(arg0);
        if (--*(s32 *)((s32)arg0 + 0x1C) == 0) {
            s16 t = *(u16 *)((s32)arg0 + 0x28);
            t--;
            *(u16 *)((s32)arg0 + 0x28) = t;
            if (t != 0) {
                *(s32 *)((s32)arg0 + 0x1C) = 10;
                *(s32 *)((s32)arg0 + 0x14) += (s32)0xFFFF0000;
                *(u16 *)((s32)arg0 + 6) = *(s32 *)((s32)arg0 + 0x2C);
                *(u16 *)((s32)arg0 + 0xA) = *(s32 *)((s32)arg0 + 0x30);
                *(u16 *)((s32)arg0 + 0xE) = *(s32 *)((s32)arg0 + 0x34);
            } else {
                func_801292C8((u8 *)arg0);
            }
        }
    }
}



extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_80143970(void *a0);
extern void func_8012B23C(void *a0);



void func_80187AD4(s32 a0) {

    extern u8 D_801AE418[];
    extern u8 D_801AF438[];
    extern u8 D_801AE44C[];
    extern u16 D_801AE3B8[];
    extern u16 D_801AE3BA[];
    extern u16 D_801AE3BC[];
    s32 v1;
    s16 idx;

    if (func_8012C354(a0, (s32)D_801AE418) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;
        *(s32 *)(a0 + 0xB4) = -0x201;
        *(s32 *)(a0 + 0xBC) = (s32)D_801AE44C;
        func_8012A828(a0, (s32)D_801AF438);

        *(s16 *)(a0 + 0x2) = 1;
        func_80143970((void *)a0);

        func_8012B23C((void *)a0);

        *(s16 *)(a0 + 0xFE) = (rand() & 0x1F) + 0x20;
        *(s16 *)(a0 + 0x100) = (rand() & 0x1F) + 0x20;

        v1 = *(s32 *)(a0 + 0x64);
        if (*(s16 *)(*(s32 *)(v1 + 0x20) + 0x12) != 0) {
            idx = *(s16 *)(a0 + 0x70);
            *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) -
                *(u16 *)((u8 *)D_801AE3B8 + idx * 8);
            idx = *(s16 *)(a0 + 0x70);
            *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) +
                *(u16 *)((u8 *)D_801AE3BA + idx * 8);
            idx = *(s16 *)(a0 + 0x70);
            *(s16 *)(a0 + 0xE) = *(u16 *)(a0 + 0xE) -
                *(u16 *)((u8 *)D_801AE3BC + idx * 8);
        } else {
            idx = *(s16 *)(a0 + 0x70);
            *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) +
                *(u16 *)((u8 *)D_801AE3B8 + idx * 8);
            idx = *(s16 *)(a0 + 0x70);
            *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) +
                *(u16 *)((u8 *)D_801AE3BA + idx * 8);
            idx = *(s16 *)(a0 + 0x70);
            *(s16 *)(a0 + 0xE) = *(u16 *)(a0 + 0xE) +
                *(u16 *)((u8 *)D_801AE3BC + idx * 8);
        }

        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12);
    }
}



extern s32 func_80047948(s32 a0);


void func_80187C6C(void *arg0) {

    extern u16 D_801AE3B8[];
    extern u16 D_801AE3BA[];
    extern u16 D_801AE3BC[];
    s32 s0 = (s32)arg0;
    s32 v1 = *(s32 *)(s0 + 0x64);
    s16 a0v;

    if (*(s16 *)(*(s32 *)(v1 + 0x20) + 0x12) != 0) {
        *(s16 *)(s0 + 0x6) = *(u16 *)(v1 + 0x6) -
            *(u16 *)((u8 *)D_801AE3B8 + *(s16 *)(s0 + 0x70) * 8);

        *(s16 *)(s0 + 0xA) = *(u16 *)(*(s32 *)(s0 + 0x64) + 0xA) +
            *(u16 *)((u8 *)D_801AE3BA + *(s16 *)(s0 + 0x70) * 8);

        *(s16 *)(s0 + 0xE) = *(u16 *)(*(s32 *)(s0 + 0x64) + 0xE) -
            *(u16 *)((u8 *)D_801AE3BC + *(s16 *)(s0 + 0x70) * 8);
    } else {
        *(s16 *)(s0 + 0x6) = *(u16 *)(v1 + 0x6) +
            *(u16 *)((u8 *)D_801AE3B8 + *(s16 *)(s0 + 0x70) * 8);

        *(s16 *)(s0 + 0xA) = *(u16 *)(*(s32 *)(s0 + 0x64) + 0xA) +
            *(u16 *)((u8 *)D_801AE3BA + *(s16 *)(s0 + 0x70) * 8);

        *(s16 *)(s0 + 0xE) = *(u16 *)(*(s32 *)(s0 + 0x64) + 0xE) +
            *(u16 *)((u8 *)D_801AE3BC + *(s16 *)(s0 + 0x70) * 8);
    }

    a0v = (*(u16 *)(s0 + 0x102) + *(u16 *)(s0 + 0xFE)) & 0xFFF;
    *(u16 *)(s0 + 0x102) = a0v;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x10) = func_80047948(a0v) >> 5;

    a0v = (*(u16 *)(s0 + 0x104) + *(u16 *)(s0 + 0x100)) & 0xFFF;
    *(u16 *)(s0 + 0x104) = a0v;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x14) = func_80047948(a0v) >> 5;
}


    typedef struct { u8 b[8]; } Blk8_80187DE4;
typedef struct {
    s32 a;      /* 0x00 -> D_801DA750 */
    s32 b;      /* 0x04 -> D_801DA754 */
} Pair8_8017DDC4_80182244_80187DE4;

/* func_80187DE4 — ov_SC02_027 / ov_SC02_027_jr_8017D898.c   MATCH (249 ins)
 *
 * Per-frame tick for a 4-state actor: first a proximity sweep over the live entity
 * list (retarget every type-0x16F entity within 0x1900 to state 0x1D), then a
 * switch on the state byte at +0xC2.  case 0 FALLS THROUGH into case 1 (that is
 * why the `*(u8*)(a0+0xC2) = 1` store is unconditional and why case 0's block sits
 * physically above the shared tail); the `func_8012C218` bail of case 0/1 and of
 * case 2 are textually identical, so jump.c cross-jumps them into one copy at
 * .L801876C4 (the LOWER site is the one redirected — §162 cross-jump direction).
 *
 * Declaration provenance (§161c — every decl checked against the whole host TU):
 *   func_8012CEB0(s32,s32,s32)  — TU col-0 decl at L5276 (and fn-scope L4404): identical
 *   func_80143B6C(s32,s32)      — TU col-0 decl at L4482: identical
 *   func_8012C218(void *)       — TU col-0 decls at L2665/L3877/L4481: identical
 *   func_8012DE2C / func_8012DDA4 / func_80013350 — NOT in the TU; forms are byte-copies
 *                                 of the canonical set in src/shared/engine_core.h
 *                                 (L24522/24523/24524, DEFINE_func_8012DBD0)
 *   func_8012CC64 / func_8012CBF4 — NOT in the TU; canonical returns are `void`
 *                                 (engine_core.h L5361 / L8375) and the asm USES $v0, so
 *                                 the read is a call-site cast (codegen-neutral, the
 *                                 codebase's own idiom — cf. func_80131340).
 *   D_801D3380                  — real dlabel, asm/ov_SC02_027/data/tail18.data.s:5345
 *                                 (0x801DA780, 8 bytes); declared nowhere else in src/.
 *   The TU instantiates NO DEFINE_ macro, so none of the above can be redefined behind us.
 *
 * Codegen notes (each closed a residual — do not "clean up"):
 *  - sp10/18/20/28 are four 8-byte, align-2 vectors.  align(2) < 4 is what makes the
 *    aggregate copies unaligned lwl/lwr + swl/swr block moves, and `sp28 = sp20` is a
 *    DEAD copy that gcc-2.7.2 KEEPS (no aggregate DSE) — load-bearing, not dead code.
 *    Byte-proven twin: func_80131340 in ov_SC02_027_jr_8012ACE0.c.
 *  - The 0x1D constant is hoisted to $s2 in the loop preheader by loop.c because it is
 *    used TWICE in the loop (the 0x5E compare and the 0x5E store); 0x16F/0xA are used
 *    once each and stay inside.  Writing the literal twice is what produces that.
 *  - Two scheduling levers, both alias-analysis (sched.c true_dependence), see inline.
 */

extern s32 func_8012DE2C(s32 a0);
extern s32 func_8012DDA4(void);
extern void func_80013350(s32 a0, void *a1);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012CC64(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8012C218(void *a0);


void func_80187DE4(s32 a0)
{

    extern s32 D_801D3380;
    /* 8-byte, align-2 vector — align < 4 is what makes the aggregate copies
     * unaligned lwl/lwr + swl/swr block moves (§ sibling func_80131340). */
    struct V8_80187DE4 {
        u16 vx, vy, vz, pad;
    };
    struct Cnt_80187DE4 {
        s32 c;
    };

    struct V8_80187DE4 sp10;
    struct V8_80187DE4 sp18;
    struct V8_80187DE4 sp20;
    struct V8_80187DE4 sp28;
    s32 p;

    sp10.vz = 0;
    sp10.vx = 0;
    sp10.vy = 0x30;

    p = func_8012DE2C(a0);
    while (p != 0) {
        if (*(u16 *)p == 0x16F && (*(u16 *)(p + 0x5C) & 0x8000) != 0 &&
            *(u16 *)(p + 0x5E) != 0x1D &&
            ((s32 (*)(s32, s32))func_80013350)(a0 + 4, p + 4) < 0x1900) {
            *(u16 *)(p + 0x60) = 0xA;
            *(u16 *)(p + 0x5C) |= 1;
            /* The 0x5E store must be SOURCE-ORDERED after the a0+0x20 loads: the
             * anti-dependence (different base regs -> memrefs_conflict_p cannot
             * disambiguate) pins it below them, so the scheduler can only place it
             * in the lhu's load-delay stall. Written before them it floats up into
             * the lhu 0x5C shadow instead and costs a nop. */
            *(u16 *)(p + 0x62) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800;
            *(u16 *)(p + 0x5E) = 0x1D;
        }
        p = func_8012DDA4();
    }

    switch (*(u8 *)(a0 + 0xC2)) {
    case 0:
        *(u8 *)(a0 + 0xC2) = 1;
        sp18.vx = *(u16 *)(a0 + 0x3A);
        sp18.vy = *(u16 *)(a0 + 0x3E);
        sp18.vz = *(u16 *)(a0 + 0x42);
        sp20 = sp18;
        sp20.vx += sp10.vx;
        sp20.vy += sp10.vy;
        sp20.vz += sp10.vz;
        sp28 = sp20; /* load-bearing dead aggregate copy — no aggregate DSE in 2.7.2 */
        func_8012CEB0((s32)&sp18, (s32)&sp20, 1);
        sp20.vx -= sp10.vx;
        sp20.vy -= sp10.vy;
        sp20.vz -= sp10.vz;
        *(u16 *)(a0 + 0x3A) = sp20.vx;
        *(u16 *)(a0 + 0x3E) = sp20.vy;
        *(u16 *)(a0 + 0x42) = sp20.vz;
        /* fallthrough */
    case 1:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) += *(u16 *)(a0 + 0xFE);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) += *(u16 *)(a0 + 0x100);
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x29) {
            func_8012C218((void *)a0);
            return;
        }
        D_801D3380 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&sp10);
        if (D_801D3380 & 0x2000) {
            *(u8 *)(a0 + 0xC2) = 2;
            func_80143B6C(a0, 1);
            *(s32 *)(a0 + 0x14) = 0xFFF30000;
            *(s32 *)(a0 + 0x1C) = 0;
        }
        break;

    case 2:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) += *(u16 *)(a0 + 0xFE);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) += *(u16 *)(a0 + 0x100);
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x29) {
            func_8012C218((void *)a0);
            return;
        }
        D_801D3380 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&sp10);
        if (D_801D3380 & 0x2000) {
            func_80143B6C(a0, 1);
            *(u8 *)(a0 + 0xC2) = 3;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) &= 0xFFF;
            if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) < 0x800) {
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0x400;
            } else {
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0xC00;
            }
        }
        break;

    case 3:
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) * 15 / 16;
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) * 15 / 16;
        D_801D3380 = ((s32 (*)(s32))func_8012CBF4)(a0);
        /* MEM_IN_STRUCT_P lever (sched.c:837 true_dependence escape): a struct-member
         * ref at a VARYING address never conflicts with a non-struct ref at a FIXED
         * address, so this load may hoist above the D_801D3380 store and fill the jal
         * shadow.  Written as `*(s32 *)(a0 + 0x1C)` the ref is a plain INDIRECT_REF,
         * the escape does not fire, and the load stalls one nop below the store. */
        ((struct Cnt_80187DE4 *)(a0 + 0x1C))->c += 1;
        if (((struct Cnt_80187DE4 *)(a0 + 0x1C))->c >= 0x11) {
            *(u16 *)(a0 + 0x2) = 3;
            *(s32 *)(a0 + 0x1C) = 0x1E;
        }
        break;
    }
}



extern void (*D_801AE45C[])(void);

void func_801881C8(void *a0) {
    D_801AE45C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern u8 D_8018B770[];
extern void func_8012A828(s32 a0, s32 a1);

void func_80188204(s32 a0)
{
    s16 ang;

    *(u16 *)(a0 + 0x5C) &= 0xFFFE;
    *(u8 *)(a0 + 0xC1) = 0;
    *(u16 *)(a0 + 0x2) = 2;

    *(u16 *)(a0 + 0xFE) = (rand() & 0x7F) + 0x80;
    *(u16 *)(a0 + 0x100) = (rand() & 0x7F) + 0x80;

    ang = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + (rand() & 0x3FF) + 0x600;

    *(s32 *)(a0 + 0x10) = func_8004787C(ang) << 8;
    *(s32 *)(a0 + 0x18) = -(func_80047948(ang) << 8);

    *(s16 *)(a0 + 0x16) = (rand() & 0xF) - 0x20;
    *(u8 *)(a0 + 0xC2) = 0;
    *(s32 *)(a0 + 0x1C) = 0;

    func_8012A828(a0, (s32)D_8018B770);

    if (*(u8 *)(a0 + 0xC3) == 0) {
        *(u8 *)(a0 + 0xC3) = 1;
        (*(u16 *)(*(s32 *)(a0 + 0x64) + 0xFC))--;
    }
}


INCLUDE_ASM("asm/ov_SC02_028/nonmatchings/ov_SC02_028_jr_80184BD8", func_80188300);


/* func_80188354 — "spawn a paired effect entity above/below the actor" template
 * (family exemplar, 15 members / 1455 templatable instructions).
 *
 * Declaration provenance (all verified against the whole TU in one pass, cookbook §135-8):
 *   func_8012A828(s32,s32)          — TU col-0 decl (lines 3488/3771/…/4781), identical form
 *   func_8012C658(s32,s32,s32)      — TU col-0 decl (lines 2524/3721/3772/4935)
 *   func_8012C218(void *)           — TU col-0 decl (lines 3545/4016/…/5226)
 *   func_8012B030(u8 *)             — TU col-0 decl (line 4208)
 *   func_8012CEB0(s32,s32,s32)      — TU fn-scope decl (line 4404), same signature
 *   func_8002AC00(s32)              — TU fn-scope decl (line 5085), same signature
 *   func_8001C214(s32,s32)          — NOT declared in this TU; form copied from
 *                                     src/shared/engine_core.h:8751 so it can never clash
 *   D_801B5828 / D_801BCF6C         — real dlabels in asm/ov_SC02_026/data/tail.data.s
 *                                     (0x801B5A4C / 0x801BD190), declared nowhere else
 *
 * Codegen notes (each closed a residual):
 *  - The buf[8] halfword-pair setup is the byte-verified twin of func_801843AC in THIS TU
 *    (line 4403): the three $2/$3/$7 register pins reproduce the original's temp allocation,
 *    and the doubled buf[1]/buf[5] stores are real — the ±8 adjust is a second store, so the
 *    scheduler emits sh/sh then sh/sh with a single lhu of a0+0xA (cookbook §135-4: the list
 *    scheduler preserves the relative order of disambiguable stores).
 *    Third temp lands in $a3 (not $a2 as in func_801843AC) because $a2 is already pinned to
 *    the literal-0 third argument here.
 *  - `>= 0x10` (not `< 0x10` with swapped arms) is what puts the func_8012C218 arm in the
 *    fall-through position and the func_8012B030 arm behind the `j`.
 *  - The `s16 t` temp on line ~72 is load-BEFORE-stores in SOURCE. Without it the lhu of
 *    a0+0x100 cannot hoist above the two ent-relative stores — §135-2's MEM_IN_STRUCT_P
 *    escape does NOT apply here because those stores have varying (register) addresses, so
 *    true_dependence() keeps the edge. Source order is the only lever; costs one nop otherwise.
 *  - The do/while's `sll/sra` pair is CSE store-forwarding: `*(u16*)` read for the += keeps
 *    the HImode load (result is truncated), then the signed compare must materialize the
 *    sign extension of the just-stored register.
 */

extern void func_8002AC00(s32 arg0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012C218(void *a0);
extern s32 func_8012B030(u8 *a0);

void func_80188354(void *a0) {

    extern s32 D_801B5828;
    extern s32 D_801BCF6C;
    u16 buf[8];
    s32 ent;
    u16 saved;
    register u16 v0 __asm__("$2");
    register u16 v1 __asm__("$3");
    register u16 a3 __asm__("$7");

    func_8002AC00(0xD);
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        v0 = *(u16 *)((s32)a0 + 0x6);
        buf[0] = v0;
        buf[4] = v0;

        v1 = *(u16 *)((s32)a0 + 0xA);
        v0 = v1 - 8;
        buf[1] = v1;
        buf[5] = v1;

        a3 = *(u16 *)((s32)a0 + 0xE);
        v1 = v1 + 8;
        buf[1] = v0;
        buf[5] = v1;
        buf[2] = a3;
        buf[6] = a3;

        if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x1F) == 0) {
            if ((*(s16 *)((s32)a0 + 0x100) & 0x8000) == 0) {
                saved = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12);
                func_8001C214(*(s32 *)((s32)a0 + 0x20), (s32)&D_801B5828);
                func_8012A828((s32)a0, (s32)&D_801BCF6C);
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = saved;
                ent = func_8012C658(0x12C, 1, (s32)a0);
                if (ent != 0) {
                    if (*(s16 *)((s32)a0 + 0xA) >= 0x10) {
                        func_8012C218((void *)ent);
                    } else {
                        *(u16 *)(*(s32 *)(ent + 0x20) + 0x12) = saved;
                        func_8012B030((u8 *)ent);
                        if (*(s16 *)((s32)a0 + 0x70) == 5) {
                            s16 t = *(s16 *)((s32)a0 + 0x100);
                            *(s16 *)(ent + 0x70) = 6;
                            *(s16 *)(ent + 0xFE) = 1;
                            *(s16 *)(ent + 0x100) = t;
                            do {
                                func_8012C658(0x12F, 5, ent);
                                *(s16 *)(ent + 0xFE) = *(u16 *)(ent + 0xFE) + 3;
                            } while (*(s16 *)(ent + 0xFE) < 0x10);
                            *(s16 *)(ent + 0xFE) = 0;
                        }
                    }
                }
            }
        }
    }
}

