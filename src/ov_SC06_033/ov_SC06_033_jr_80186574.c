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
extern u8 D_80193D6C;
extern u8 D_80193CDC;
extern u8 D_80193CB8;
extern u8 D_80193C94;
extern u8 D_80193D48;
extern u8 D_80193D24;
extern u8 D_80193D00;
extern u8 D_80193C70;
extern void func_80145934(void);
extern u8 D_80193DFC;
extern u8 D_80193DD8;
extern u8 D_80193DB4;
extern u8 D_80193D90;
extern void func_80145A2C(void);
extern s32 func_800291DC(s32);
extern void func_800291C8(s32, s32);
extern void func_80162120(void);
extern void func_80029124(s32, s32);
extern s32 func_80165A50(s32);
extern void func_80029514(s32);
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
extern unsigned char D_801931F4[];
extern unsigned char D_80193224[];
extern unsigned char D_80193274[];
extern unsigned char D_801932A4[];
extern unsigned char D_801932D4[];
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
extern void (*D_80193324[])(void *);
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
extern s32 D_801933EC[];
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
extern u8 D_80193474[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8019347C;
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
extern int D_801CF400;
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
extern s32 D_801CF404;
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
extern s32 D_801934AC;
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
extern void (*D_80193554[])(void);
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
extern void (*D_80193578[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80193568;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8019358C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80193598[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801935A8[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801935C0[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801935B0;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801935D4[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801935F0[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801935E0;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80193604[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80193618[])(void);
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
extern s32 D_8019362C;
extern void (*D_80193654[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80193634;
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
extern int (*D_801936A0[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801936A4[])(void);
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
extern unsigned short D_80193B08[];
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
extern void (*D_80193B18[])(void);
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
extern int D_801CF438;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80193B40[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80193B20;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80193B30;
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
extern void (*D_80193B80[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80193B88[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80193B54;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80193B94[])(void);
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
extern u8 D_80193B64;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801CF440;
extern s32 D_801CF44C;
extern s32 D_801CF450;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80193BD0[])(s32 *);
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
extern s32 D_80193BA4[];
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
extern s32 D_801CF448;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80193E20[])(void);
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
extern char D_80193C40[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80193EC4[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80194018[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80193E34;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80194020[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80193E44;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80193E64;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80194028[])(void);
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
extern void (*D_80194050[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8019405C[])(void);
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
extern void (*D_80193ED0[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80194100;
extern void func_8015D380(s32 a0);
extern unsigned char D_801931E4[];
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
extern unsigned char D_80194114[];
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
extern s8 D_80194150[];
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
extern u16 D_80194198;
extern u16 D_8019419A;
extern u16 D_8019419C;
extern s32 D_801941A0;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_801941A8;
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
extern int D_80193EB4;
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
extern unsigned int D_8019422C[];
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
extern void (*D_801942DC[])(void);
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
extern u16 D_8019430C[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80194370;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801CF458[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80194394[])(void);
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
extern int D_801CF4B0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_801943DC[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801943CC;
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
extern char D_801CEB28[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801943E4[])(void);
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
extern void (*D_80194438[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80194400;
extern s16 D_80194434;
extern s16 D_80194432;
extern s16 D_80194430;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80194444[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801CF510;
extern u8 D_801CF511;
extern u8 D_801CF512;
extern u8 D_801CF513;
extern u8 D_801CF514;
extern u8 D_801CF515;
extern u8 D_801CF516;
extern u8 D_801CF517;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80194454[])(void);
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
extern s32 D_801CF550;
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
extern void (*D_80194498[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80194514[];
extern s32 D_80194534[];
extern u8 D_801945B0[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801945D0[];
extern u8 D_801945F0[];
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
extern void (*D_8019468C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80194708[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801CEB38;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80194714[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8019471C[])(void);
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
extern void (*D_801947E4[])(void);
extern void func_80166618(void *a0);
extern void (*D_801947F4[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80194804[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80194810[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80194770[];
extern u8   D_80194784[];
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
extern void (*D_80194828[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80194830[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80194838[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80194840[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80194848[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80194850[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80194858[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8019490C[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80194914[])(void);
extern void func_80169F00(void *a0);
extern char D_801948C4[];
extern char D_80194884[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8019494C[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80194958[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801949A0[])(void);
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
extern void (*D_80194A1C[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801CF870;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80194A10[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80194A54[];
extern unsigned short D_80194A5C[];
extern unsigned short D_80194A64[];
extern unsigned char D_801CF878[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801CF870;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80194A6C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801CF9AC;
extern M2C_UNK D_801CF9B0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801CF938;
extern void (*D_80194A9C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801CF9B4[];
extern u8 D_801CF9BC[];
extern u8 D_801CF96C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80194AA4[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80194AC0[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80194AC8[])(void);
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
extern void (*D_80194B30[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80194AD4;
extern u8 D_80194AE0;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80194B64[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80194B6C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80194BC0[])(void);
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
extern u16 D_80194BF4[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80194BE4[];
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
extern s32 D_80194C10;
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
extern void (*D_80194C88[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80194C90[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80194C98[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80194CA0[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80194CA8[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80194CB0[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80194CBC[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80194CC8[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80194CD4[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80194CE4[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80194CF4[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80194CFC[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80194D04[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80194D0C[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80194D14[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80194D1C[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80194D24[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80194D2C[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80194D34[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80194D3C[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80194D44[])(void);
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
extern void (*D_80194D4C[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80194D54[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80194D5C[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80194D64[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80194D6C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80194D74[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80194D7C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80194D84[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80194D8C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80194D94[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80194D9C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80194DA4[])(void);
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
extern void (*D_80194DE8[])(void);
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
extern M2C_UNK D_80194DAC;
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
extern void (*D_80194E18[])(void);
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
extern void (*D_80194E54[])(void);
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
extern void (*D_80194EAC[])();
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
extern void (*D_80194EBC[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80194EC4[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_8019502C[])();
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
extern void (*D_80195038[])();
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
extern M2C_UNK D_801CED80;
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
extern s16 D_801D0F78;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801D00F0;
extern short D_801D0FEC;
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
extern s32 D_801D051C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801D0544;
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
extern s16 D_801D0500;
extern s32 func_8017A3B0(void);
extern short D_801D053C;
extern short D_801D0538;
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
extern s16 D_801D0504;
extern u16 D_801D0584;
extern u16 D_801D0586;
extern u16 D_801D0588;
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
extern s16 D_801D057C;
extern s16 D_801D057E;
extern s16 D_801D0580;
extern s16 D_801D0574;
extern s16 D_801D0576;
extern s16 D_801D0578;
extern void func_8017B7A8(void);
extern s16 D_801D0594;
extern s16 D_801D0596;
extern s16 D_801D0598;
extern s16 D_801D059C;
extern s16 D_801D059E;
extern s16 D_801D05A0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801D058C;
extern short D_801D058E;
extern short D_801D0590;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801D0524;
extern SV4 D_801D052C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801D054C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801D0548)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80195214[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8019522C[])(void);
extern void func_8017BEBC(void *a0);
extern void func_8017C090(void *a0);
extern void func_8017C24C(s32 arg0);
extern void func_8017D12C(s32 a0, s16 *a1, s16 a2);
extern void func_8017D1F8(s32 a0);
extern void (*D_80195264[])(void);
extern void func_8017D354(void *a0);
extern void func_8017D390(void *a0);
extern void func_8002931C(void);
extern void func_8017D3F0(void);
extern void (*D_801952BC[])(void);
extern void func_8017D410(void *a0);
extern void func_8017D67C(void);
extern s32 func_8017D44C(s32 a0);
extern s32 func_8017D490(void);
extern void (*D_801952C4[])(void);
extern void func_8017D4B4(void *a0);
extern void func_8017D6A4(void);
extern s32 func_8017D4F0(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_8017D530(u8 *a0);
extern void func_800D1EBC(void);
extern void func_8017D5AC(void);
extern void (*D_801952D0[])(void);
extern void func_8017D5CC(void *a0);
extern s32 func_8017D608(s32 a0);
extern void (*D_801952F4[])(void);
extern void func_8017D7A4(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017DA78(s32 param_1, s16 *param_2);
extern void func_8017DC10(void *a0);
extern void (*D_801952FC[])(void);
extern void func_8017DDC4(void *a0);
extern s32 func_8017E21C(void);
extern void func_8012DFD4(void *a0);
extern void func_8017E594(void *a0);
extern s32 func_8017E5F4(s32 *a0);
extern void func_8017E694(void);
extern void func_8017E784(void *a0);
extern void func_8017E7DC(s32 a0);
extern void func_8017EA0C(s32 a0);
extern void func_8017EA60(void);
extern s32 func_8017EA84(void);
extern void (*D_801953D0[])(void);
extern void func_8017EAC8(void *a0);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_8017ECF8(void*);
extern void func_8017ECC8(s32*);
extern void func_8017EB04(int param_1);
extern s32 func_8017ED0C(s32 *a0, s32 a1);
extern void func_8017ECC8(s32 *a0);
extern void func_8017EC50(s32 *a0);
extern void func_8017ECC8(s32 *param_1);
extern void func_8017ECF8(void *a0);
extern void (*D_80195408[])(void);
extern void func_8017ED74(void *a0);
extern void func_8017EDB0(s32 param_1);
extern void func_8017EE4C(s32 param_1);
extern void func_8017EDFC(s32 param);
extern void func_8017EE44(void);
extern void func_8017EFB0();
extern void func_80013F3C(s32);
extern void RotMatrixZ(s32, void *);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern void func_80017714(void *);
extern SVECTOR_8017E6D8 D_801D0ABC[4];
extern struct PW8017E6D8 D_801D0ADC;
extern struct PW8017E6D8 D_801D0AE0;
extern u8 D_801D0AE4, D_801D0AE5, D_801D0AE6, D_801D0AE8, D_801D0AE9, D_801D0AEA;
extern int D_801D0AEC;
extern void func_8017EFB0(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d, SVECTOR_8017E6D8 *e, SVECTOR_8017E6D8 *f, s16 *g, struct PW8017E6D8 *h);
extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);
extern int func_8017F32C(int param_1, short param_2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8  *func_8012913C();
extern void func_8017F53C(s32 a0);
extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);
extern void func_8017F940(int param_1);
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
extern void func_8017FAB4(int param_1);
extern void func_8012B1B4(void*, void*);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012BE54(s32 a0);
extern void func_8017FC64(s32 a0);
extern void func_8004914C();
extern void func_800491AC();
extern u8 *func_8012913C(s32 a0);
extern void func_8012A828(s32 a0, void * a1);
extern void func_8017FEF0(s32 a0);
extern void func_8012B370(int a0);
extern void func_801803B4(s32 a0);
extern s32 func_801823F0(void);
extern void func_80180584(s32 a0);
extern s32 func_8012C044(s32 a0);
extern void func_8012C098(void *param_1);
extern int func_80143C74(short *, int);
extern void func_80180774(s32 a0);
extern void func_80180A8C(int param_1);
extern void func_80180C84(s32 a0);
extern void func_801810CC(short *param_1);
extern void func_801812DC(s32 a0);
extern s32 func_80143C74();
extern void func_80181720(s32 a0);
extern void func_80128EA8();
extern void func_8012931C();
extern void func_801292C8();
extern int  func_8012D664();
extern void func_80181930(s32 arg0);
extern void func_80181D74(s32 a0);
extern void func_80181ECC(void *a0);
extern void func_80181FDC(void);
extern void func_801820B8(s32 a0);
extern void func_80182178(void);
extern void func_80182198(void *a0);
extern void func_801822AC(void);
extern void func_801823A8(s32 a0);
extern void func_80182468(void);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80182764(s32 param_1);
extern void func_80182998(s32 param_1);
extern void func_8001C924(s32 a0, void *a1);
extern s32  func_8012BEE8();
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_801860E4(s32 a0);
extern void func_80013350(s32 a0, void *a1);
extern void func_80183004(s32 p);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern void func_80142414(s32 a0, s16 a1);
extern void func_801832CC(s32 p);
extern void func_8018338C(s32 param_1);
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012E778(int param_1, int param_2);
extern s32  func_8012BCCC(s32 a0);
extern void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3);
extern s32 func_80188BF8(s32, s32);
extern void func_80187DA4(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_801888E8(s32 a0, s32 a1);
extern void func_801836FC(s32 p);
extern void func_80183CF0(s32 param_1);
extern void func_8018626C(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_80187D0C(void *a0, s32 a1, s32 a2);
extern s32  func_8012BEE8();   /* TU-canonical: an earlier call site passes zero args */
extern void func_80183DA8(s32 p);
extern void func_8012A828(s32, void*);
extern void func_80183F48(short *a0);
extern void func_80187E08(s32 a0, void *a1, void *a2, s32 a3);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern void func_80183F80(s32 p);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern void func_80187E08(s32, void*, void*, s32);
extern void func_80187DA4(s32, void*, s32, s32, s32, s32);
extern s32  func_80013478(s32 a0, s32 a1);
extern void func_80184414(s32 param_1);
extern void func_80185AC0(void);
extern void func_80184830(s32 *param);
extern void func_8018597C(s32 a0);
extern s32  func_8012DBD0(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32  func_8012CBF4(s32 a0);
extern s32  func_8012CBA4(s32 a0);
extern s32  func_80143B6C(s32 a0, s32 a1);
extern void func_80131E00();
extern void func_80131C78(s32 a0);
extern u8 D_801C758C[];
extern void func_80184CF8(s32 a0);
extern void func_80185F6C(s32 a0, s32 a1);
extern void func_80185A00(s32 param_1);
extern s32 func_80187E54(s32 a0, s32 a1);
extern s32 func_80185CD8(s32 p);
extern s32  func_8012BC60(void *a0, void *a1);
extern s32  func_8012CEB0(void *a0, void *a1, s32 a2);
extern void func_8012ADE4(u8 *a0);
extern void func_80185DA8(s32 a0);
extern s32 func_800132BC(void *a0, void *a1);
extern s32 func_801862CC(s32 a0, s32 a1);
extern void (*D_801AFC18[])(void);
extern void func_801863AC(void *a0);
/* ==== end §8b carried decl layer ==== */


/* ov_SC06_018 :: func_80186574  — actor state machine, jump-table switch on the
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
extern void func_80187A88(s32 a0, s32 a1);
extern s32  func_80187ED4(s32 a0, s32 a1, s32 a2);
extern void func_8012C218(void *a0);

extern u8 D_801AFC24;

void func_80186574(s32 param_1)
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
                 ((*(u16 *)(param_1 + 0x70) & 0xF) * 8) + (s32)&D_801AFC24) &
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
            func_80187A88(param_1, 1);
        }
        return;
    case 5:
        if (func_80187ED4(param_1, 0x60, 0xA0) == 1) {
            func_8012C218((void *)param_1);
        }
        return;
    }
}


extern void func_8012C218(void *a0);
extern void func_8012E8A8(u8 *a0);

/* §48-C2: lwl/lwr/swl/swr block copy == a plain struct assign of a 2-byte-aligned struct */

void func_80186858(s32 param_1)
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
                    *(UAlign12_80186858 *)(param_1 + 0xFC) = *(UAlign12_80186858 *)(a2 + 0x90);
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

            *(UAlign8_80186858 *)(param_1 + 0x50) = *(UAlign8_80186858 *)(t1 + 0x50);

            {
                s32 dst = *(s32 *)(param_1 + 0x20);
                s32 src = *(s32 *)(t1 + 0x20);
                *(UAlign8_80186858 *)(dst + 0x10) = *(UAlign8_80186858 *)(src + 0x10);
            }
            {
                s32 dst = *(s32 *)(param_1 + 0x20);
                s32 src = *(s32 *)(t1 + 0x20);
                *(UAlign8_80186858 *)(dst + 0x18) = *(UAlign8_80186858 *)(src + 0x18);
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


extern void (*D_801AFD70[])(void);

void func_80186B10(void *a0) {
    D_801AFD70[*(u16 *)((s32)a0 + 0x2)]();
}


extern int  func_8012C354();
extern s32 func_80143994(s32 a0, s32 a1);
extern u8 D_801AFC54[];
extern u8 D_801AFC80[];
extern u8 D_801AFCB4[];
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012C1B8(void);
extern void func_8012CAE4();
extern void func_80186CBC(s32 a0);
extern void func_80187588(s32 p);

void func_80186B4C(s32 a0) {
    s32 v1;
    s32 obj;

    v1 = *(u16 *)(a0 + 0x70) & 0xF;
    switch (v1) {
    case 0:
        if (func_8012C354(a0, D_801AFC80) == 0) {
            return;
        }
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = a0 + 0xE8;
        *(u16 *)(a0 + 0x104) = 0x78;
        func_80186CBC(a0);
        func_80143994(a0, 0x1800);
        return;
    case 1:
        if (func_8012C354(a0, D_801AFCB4) == 0) {
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
        func_8001CA1C(obj, (s32)D_801AFC54);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x14CC;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x1199;
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x58000000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
        func_80187588(a0);
        return;
    default:
        return;
    }
}


extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_80186CBC(s32 param_1) {
    *(s32 *)(param_1 + 0x1C) = 0x18;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0x80;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12);
    func_8012B2CC(param_1);
    func_8012B178(param_1, -0x100000);
    *(s16 *)(param_1 + 2) = 2;
}



extern void func_8012C218(void *a0);
extern s32  func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80187A88(s32 a0, s32 a1);
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BEE8(s32 a0);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_8012CBF4(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern u8  *func_8012913C(s32 a0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);


void func_80186D24(s32 param_1) {

    extern u8 D_801AFCE8;
    extern u8 D_801AFD9C[];
    extern u16 D_80126CB4;
    extern u16 D_80126CB6;
    extern u16 D_80126CB8;
    u16 uVar1;

    if (0xf < *(s16 *)(param_1 + 0xA)) {
        func_8012C218((void *)param_1);
        return;
    }

    {
        s32 base = (s32)&D_801AFCE8;
        s32 r = func_8012D5E4(param_1, base, base + 8, 0x78);
        if (r == 1 || (*(u16 *)(param_1 + 0x5C) & 1) != 0) {
            func_80187A88(param_1, 1);
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
    func_80187A88(param_1, 1);
    return;
LAB_80188494:
    {
        s32 iv = (s32)func_8012913C(0x80);
        if (iv == 0) return;
        {
            u16 out[4];
            ((void (*)(s32, void *, void *))func_8012F214)(param_1, D_801AFD9C, out);
            *(u16 *)(iv + 6) = out[0];
            *(u16 *)(iv + 0xA) = out[1];
            *(u16 *)(iv + 0xE) = out[2];
        }
        return;
    }
}


extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);

void func_80186F7C(param_1)
s32 param_1;
{
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



extern void func_8012C218(void *a0);
extern s32  func_8012BD14(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012CC64(s32 a0, s32 a1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32  func_80143B6C(s32 a0, s32 a1);   /* fleet-canonical */
extern void func_80187A88(s32 a0, s32 a1);


void func_80186FDC(s32 param_1) {

    extern u8 D_801AFD08;
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
        v0 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801AFD08);
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
    func_80187A88(param_1, 0);
}


void func_80187114(s32 a0) {
    s32 v1 = *(s32 *)(a0 + 0x64);
    *(u16 *)(a0 + 2) = 6;
    *(u16 *)(a0 + 0x34) = 0;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(v1 + 0x20) + 0x12);
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
extern void func_80187E08(s32, void*, void*, s32);
extern s32  func_80013328(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CC64(s32 a0, s32 a1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32 func_8012C658(s32, s32, s32);
extern s32  func_80143B6C(s32 a0, s32 a1);   /* fleet-canonical */
extern s32  func_8012BEE8(s32 a0);
extern void func_80016714(void*, s32);
extern void func_80187A88(s32 a0, s32 a1);


void func_80187138(s32 param_1) {

    extern u8 D_801C7A9C;
    extern u8 D_801AFD10;
    extern u8 D_801AFD18;
    extern u8 D_801AFD08;
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
            (*(s32 *)(psVar5 + 0x90) != (s32)&D_801C7A9C)) {
            func_8012C218((void *)param_1);
            return;
        }
        if (*(s32 *)(psVar5 + 0x94) < 0x11) {
            ((void (*)(void *, void *, void *, s32))func_80187E08)((void *)psVar5, (void *)&D_801AFD10, buf, 5);
            *(s16 *)(param_1 + 6) = buf[0];
            *(s16 *)(param_1 + 0xA) = buf[1];
            *(s16 *)(param_1 + 0xE) = buf[2];
            return;
        }
        ((void (*)(void *, void *, void *, s32))func_80187E08)((void *)psVar5, (void *)&D_801AFD18, buf, 4);
        ((void (*)(void *, void *, void *, s32))func_80187E08)((void *)psVar5, (void *)&D_801AFD18, &buf[4], 5);
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
        iVar3 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801AFD08);
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
        uVar4 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801AFD08);
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
        func_80187A88(param_1, 0);
        return;
    }
    return;
}



extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern void func_8012B260(u8 *a0);

void func_80187588(s32 p) {
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

void func_80187624(s32 param_1)
{
    extern s32 *D_80126B78;
    extern s32 *D_80126B90;
    extern u8   D_801152A8[];
    extern u8   D_801AFCF8[];
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
    extern s32  func_8012CBF4(s32 a0);
    extern s32  func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
    extern s32  func_80132EF4(s32 a0, s32 a1);
    extern s32  func_8012BEE8(s32 a0);
    extern void func_8012C218(void *a0);
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

    RotTransSV(&D_801AFCF8[0], &b, &flag);
    RotTransSV(&D_801AFCF8[8], &c, &flag);

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

void func_801877DC(void *a0)
{
    ((void (*)(void *))func_8012E8A8)(a0);
    *(u32 *)(a0 + 0x1C) = 0xA;
    *(u16 *)(a0 + 0x5C) = 0;
    *(u16 *)(a0 + 0x2) = 0xA;
}


extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
extern s32 func_80187ED4(s32 a0, s32 a1, s32 a2);
extern void func_8012C218(void *a0);

void func_80187818(s32 param_1) {
    extern u16 D_80126B96;
    if (*(u16 *)(param_1 + 0x70) & 1) {
        if (func_8012D624((void *)param_1, 0x60, *(s16 *)(param_1 + 0x104)) == 1) {
            D_80126B96 = 0x4001;
        }
    }
    if (func_80187ED4(param_1, 0x60, *(s16 *)(param_1 + 0x104)) == 1) {
        func_8012C218((void *)param_1);
    }
}



/* func_80187898 @ ov_SC06_018 (subseg ov_SC06_018_jr_8017C24C) — 124 ins. MATCH.
 *
 * GATE: .venv/bin/python tools/match_one.py func_80187898 \
 *         --c .run/wave-s40/ov_SC06_018/func_80187898.c \
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
 *      state 9 and func_80187A88(e, 0); return 1.  No hit -> 0.
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
 *     `sh 9; jal func_80187A88; return 1` block.  Keep them identical.
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
 * `extern void func_80187A88(s32 a0, s32 a1);` (L7388, and DEFINES it at L7711)
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
 * is func_80187A88, and in this overlay it is defined in the SAME TU
 * (ov_SC06_018_jr_8017C24C.c:7711).  So the §40 remap for the siblings is
 * expected to be near-identity: re-point func_80187A88 at each sibling's own
 * address and check that sibling TU's canonical spellings for the four externs
 * before sweeping (§56b — carry the TU's types, not this draft's).
 */

typedef struct { u16 x, y, z, w; } V4_80188E10_80187898;

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
} Ent_80188E10_80187898;

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_80187A88(s32 a0, s32 a1);


s32 func_80187898(Ent_80188E10_80187898 *self, s32 arg1, s32 arg2, s32 arg3, u16 kind) {

    extern s32 *D_80126B78;
    extern s32 *D_80126B90;
    extern u8   D_801202A0[];
    V4_80188E10_80187898 a;              /* 0x18(sp) */
    V4_80188E10_80187898 b;              /* 0x20(sp) */
    V4_80188E10_80187898 c;              /* 0x28(sp) */
    Ent_80188E10_80187898 *e;
    s32 i;

    func_8012F214((s32)self, arg1, (s32)&a);
    func_8012F214((s32)self, arg2, (s32)&b);
    c = b;                                              /* L2: lwl/lwr block move */
    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&a, (s32)&b) != 0) {
        func_8012F568(1, 1, *(s16 *)(self->f20 + 0x12), arg3, (s32)&b, (s32)D_801152A8);
        return 1;
    }
    e = (Ent_80188E10_80187898 *)D_801202A0;
    if (kind != 0xFFFF) {                               /* L3 */
        for (i = 0; i < 0x60; i++, e++) {               /* L2: i=0 HERE, not above */
            if (e->f0 == 0x282 && (e->f70 == kind || e->f70 == self->f70) && e != self &&
                func_80135888(e->f20, e->f58, (s32)&a, (s32)&c) != 0) {
                e->f2 = 9;                              /* L4: keep identical */
                func_80187A88((s32)e, 0);
                return 1;
            }
        }
        return 0;
    } else {
        for (i = 0; i < 0x60; i++, e++) {               /* L2 */
            if (e->f0 == 0x282 && e->f70 == self->f70 && e != self &&
                func_80135888(e->f20, e->f58, (s32)&a, (s32)&c) != 0) {
                e->f2 = 9;                              /* L4: keep identical */
                func_80187A88((s32)e, 0);
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
extern void func_801888E8(s32 a0, s32 a1);
extern s32 rand(void);

void func_80187A88(s32 a0, s32 a1) {
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

    func_801888E8(a0, 0x95e);
}


INCLUDE_ASM("asm/ov_SC06_033/nonmatchings/ov_SC06_033_jr_80186574", func_80187D0C);

extern s32 func_8012C51C(void *a0, s32 a1);

typedef struct {
    u16 f10; /* 0x10 */
    u16 f12; /* 0x12 */
    u16 f14; /* 0x14 */
    s16 f16; /* 0x16 */
    s16 f18; /* 0x18 */
    s16 f1a; /* 0x1A */
    s16 f1c; /* 0x1C */
    u16 f1e; /* 0x1E */
    s32 f20; /* 0x20 */
} buf_80187DA4;

void func_80187DA4(a0, a1, a2, a3, a4, a5)
s32 a0;
void *a1;
s32 a2;
s32 a3;
u16 a4;
s32 a5;
{
    buf_80187DA4 sp;
    u16 t;

    sp.f10 = *(u16 *)a1;
    sp.f12 = *(u16 *)(2 + (char *)a1);
    t = *(u16 *)(4 + (char *)a1);
    sp.f16 = a2;
    sp.f18 = a3;
    sp.f1a = 0;
    sp.f1e = a4;
    sp.f20 = a5;
    sp.f1c = 0x7FFF;
    sp.f14 = t;
    func_8012C51C(&sp, a0);
}


INCLUDE_ASM("asm/ov_SC06_033/nonmatchings/ov_SC06_033_jr_80186574", func_80187E08);


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
s32 aF80187E54(s32 a0, s16 a1) __asm__("func_80187E54");
s32 aF80187E54(s32 a0, s16 a1)
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

s32 func_80187ED4(s32 a0, s32 a1, s32 a2)
{
    s32 e;

    if (func_8012BEE8(a0) != 0) {
        e = func_80132EF4(a0, 0x22);
        if (e != 0) {
            *(u16 *)(e + 0x34) = 0x7FFF;
            *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = 0xC006;
            *(s32 *)(e + 0x14) = 0xFFFE0000;
        }
        return 1;
    }
    return 0;
}


extern void (*D_801AFDA4[])(void);

void func_80187F3C(void *a0) {
    D_801AFDA4[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 rand(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_80187F78(s32 param_1) {

    extern u8 D_801AFDAC[];
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
    tbl = &D_801AFDAC[(*(u16 *)(param_1 + 0x70) & 0xF) * 4];

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
extern void func_8012C218(void *a0);   /* TU-canonical (ov_SC06_018_jr_8017C24C L5455) */
extern void func_80017274(s32 a0, s32 a1);

void func_801883DC(s32 param_1) {
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


extern void (*D_801AFDC4[])(void);

void func_80188480(void *a0) {
    D_801AFDC4[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32  rand(void);
extern void func_8012C1B8(void);   /* TU-canonical (ov_SC06_018_jr_8017C24C) */
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);  /* TU-canonical */
extern void func_8012B2CC(s32 a0);

void func_801884BC(s32 param_1) {
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

void func_801886B0(void *a0)
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


typedef struct { s16 vx, vy, vz, pad; } SVec_80186E9C_8018BCC4_801887EC;   /* 8 bytes, align 2 -> lwl/lwr block move */
typedef struct { s32 a; s32 b[4]; } OtBlk_8018A974_8018EB08_8018A28C_801887EC;   /* == engine_types.h OtBlk (0x14) */
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
} Ent_80188E10_801887EC;
typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_801887EC;

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
void func_801887EC(void *a0)
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


INCLUDE_ASM("asm/ov_SC06_033/nonmatchings/ov_SC06_033_jr_80186574", func_801888E8);

extern void (*D_801AFDD0[])(void);

void func_80188A54(void *a0) {
    D_801AFDD0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_80188A90(s32 param_1) {

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
extern void func_801292C8(s32 a0);

void func_80188B40(s32 param_1) {
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



extern s32 D_801D0C38;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_80188BF8(s32 a0, s32 a1) {
    D_801D0C38 = a1;
    return func_8012C588(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801D0C38;
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




s32 func_80188C28(s32 param_1) {

    extern M2C_UNK D_80191B60;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801C7BD8;
    extern char * D_801C7C0C;
    extern char D_801D0C18[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801C7BD8) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_80191B60));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801D0C38, &s60);
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
        tmp = D_801C7C0C;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801C7C0C = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801D0C18 < puVar4) {
        D_801C7C0C = D_801D0C18 - 0x120;
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
            tmp = D_801C7C0C;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801C7C0C = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801D0C18 < puVar4) {
            D_801C7C0C = D_801D0C18 - 0x120;
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

s32 func_80188E6C(s32 param_1) {

    extern signed char D_801C7BC4[];
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
        p = D_801C7BC4;
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
            p = D_801C7BC4;
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
        func_8012C218((void *)self);
    }
}



extern void (*D_801C7C10[])(void);

void func_8018910C(void *a0) {
    D_801C7C10[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012B864(s32 a0);

void func_80189148(s32 arg0) {
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


extern s32 func_8012B864(s32 a0);
extern s32 rand(void);

void func_80189250(s32 arg0) {
    s32 v;
    s32 d;
    u16 w;

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
        *(u16 *)(arg0 + 0xFE) = w = *(u16 *)(arg0 + 0xFE) + d;
        if ((s16)w >= 0x201) {
            *(u16 *)(arg0 + 0xFE) = 0x200;
        }
    } else if (d < 0) {
        if (d < -0x20) {
            d = -0x20;
        }
        *(u16 *)(arg0 + 0xFE) = w = *(u16 *)(arg0 + 0xFE) + d;
        if ((s16)w < -0x200) {
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

void func_80189390(void *arg) {
    Ent_8018D654 *self = (Ent_8018D654 *)arg;
    s16 v[4];                   /* 0x10(sp); gcc adds the other 8 bytes */
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



// func_801895AC — ov_SC06_018 / ov_SC06_018_jr_8017C24C
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

void func_801895AC(void *arg) {

    extern u8 D_801C835C;
    extern u8 D_801C834C;
    extern u8 D_801C8328;
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
            func_80019064(&D_801C835C);
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
            func_8012B1B4((void *)iv, &D_801C834C);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801C8328);
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
            func_8012B1B4((void *)iv, &D_801C834C);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801C8328);
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
            func_8012B1B4((void *)iv, &D_801C834C);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801C8328);
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




// func_80189B9C -- ov_SC06_018 / ov_SC06_018_jr_80187AEC
//
// Structural sibling of func_8018E188 (SAME TU, banked MATCH, this file: func_8018E188).
// Shares VERBATIM: the 0x60 gate + 0x1D snapshot block, the 0x78/0x60 decrement block
// (AND form -- see E188's @stuck note), the 0x82&1 finisher, and the C8/C9 pokes.
// Diverges after that: instead of E188's 0x76<0 spawn-loop / CC-D0-D4 reseed, this
// function's 0x76<0 arm sets a distinct "state 2" field group (offsets 2/0x5C/0x34/
// 0xC1/0xF4 + clears bit 0x80 of *(p+0x20)->0x2C), and its else arm plays a different
// sound (func_8002D4C8(0xAD8,0) vs E188's 0xAE0) then tail-calls func_80189390 (still
// INCLUDE_ASM in this TU -- no other TU references it, so this call site sets its own
// convention: void func_80189390(void *)).
//
// @class: regalloc-order
// @stuck: none -- see match_one output.

extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_8002D4C8(s32, s32);
extern void func_80189390(void *);

void func_80189B9C(void *arg) {

    extern u8 D_801C835C;
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
            func_80019064(&D_801C835C);
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
        func_80189390(p);
    }
}




// func_80189D30 -- ov_SC06_018 / ov_SC06_018_jr_80187AEC
//
// Structural sibling of func_8018E188 (SAME TU, banked MATCH, this file: func_8018E188).
// Shares VERBATIM: the 0x60 gate + 0x1D snapshot block, the 0x78/0x60 decrement block
// (AND form -- see E188's @stuck note), the 0x82&1 finisher, and the C8/C9 pokes.
// Diverges after that: instead of E188's 0x76<0 spawn-loop / CC-D0-D4 reseed, this
// function's 0x76<0 arm sets a distinct "state 2" field group (offsets 2/0x5C/0x34/
// 0xC1/0xF4 + clears bit 0x80 of *(p+0x20)->0x2C), and its else arm plays a different
// sound (func_8002D4C8(0xAD8,0) vs E188's 0xAE0) then tail-calls func_80189390 (still
// INCLUDE_ASM in this TU -- no other TU references it, so this call site sets its own
// convention: void func_80189390(void *)).
//
// @class: regalloc-order
// @stuck: none -- see match_one output.

extern void func_8016AA50(s32, s32);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_8002D4C8(s32, s32);
extern void func_80189390(void *);

void func_80189D30(void *arg) {

    extern u8 D_801C835C;
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
            func_80019064(&D_801C835C);
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
        func_80189390(p);
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

void func_80189EC4(void *arg) {

    extern u8 D_801C835C;
    extern u8 D_801C834C;
    extern u8 D_801C8328;
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
            func_80019064(&D_801C835C);
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
            func_8012B1B4((void *)iv, &D_801C834C);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801C8328);
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
            func_8012B1B4((void *)iv, &D_801C834C);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801C8328);
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
            func_8012B1B4((void *)iv, &D_801C834C);
            *(u16 *)(iv + 0x16) = (rand() & 3) - 0x1B;
            ((void (*)(void *, void *))func_8012A828)((void *)iv, &D_801C8328);
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



/* func_8018A318 — ov_SC06_018 / ov_SC06_018_jr_8017C24C
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

void func_8018A318(void *arg) {

    extern u8 D_801C835C;

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
            func_80019064(&D_801C835C);
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



/* func_8018A6F8 — ov_SC06_018 / ov_SC06_018_jr_80187AEC
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

void func_8018A6F8(void *arg) {

    extern u8 D_801C835C;

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
            func_80019064(&D_801C835C);
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


typedef struct { s32 a; s32 b[4]; } OtBlk_8018A974_8018AAF4;   /* == engine_types.h OtBlk (0x14) */

/* func_8018AAF4 — ov_SC06_018 / ov_SC06_018_jr_80187AEC
 *
 * Direct structural sibling of func_8018E188 (SAME TU, banked MATCH,
 * src/ov_SC06_018/ov_SC06_018_jr_80187AEC.c:5255).  Shares VERBATIM:
 *   - the 0x60 gate + 0x1D snapshot block,
 *   - the 0x78/0x60 decrement block (AND form — see E188's @stuck note),
 *   - the 0x82&1 finisher, the C8/C9 pokes,
 *   - the two 8-iteration spawn loops (0x281 / 0x23).
 * Diverges: no leading func_8002D4C8 in the 0x76<0 arm, E188's CC/D0/D4
 * particle reseed is replaced by a "hand off to the 0x64 owner" block
 * (5C/60/5E/D8/76/62 pokes + func_801895AC), and the else arm gains a
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
 *       $a0 (every store base + the func_801895AC arg).  Spelling that as
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
extern void func_801895AC(void *);

void func_8018AAF4(void *arg) {

    extern u8 D_801C835C;
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
            func_80019064(&D_801C835C);
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
        func_801895AC((void *)q);
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


INCLUDE_ASM("asm/ov_SC06_033/nonmatchings/ov_SC06_033_jr_80186574", func_8018AD9C);

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
#define gte_ldv0(r0)  __asm__ __volatile__( \
    "lwc2 $0, 0(%0)\n" \
    "lwc2 $1, 4(%0)\n" \
    : : "r"(r0) : "memory")
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


void func_8018B3D0(void)
{
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern void *func_80010A08(s32);
    extern u8 D_800AF648;
    extern u8 D_800A6610[];
    extern short D_800B9A02;
    extern Blip_8018F694 D_801D0C40[];

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
    bp = D_801D0C40;

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



/* func_8018BB48 — allocates a semi-trans LineF2 GPU packet, projects two
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
 *   D_800A651C[]` (locally as `OtBlk_8018A974_8018BB48` — match_one compiles
 *   standalone without ../shared/engine_core.h; at bank time this collapses
 *   onto the TU's own already-visible `OtBlk` from engine_types.h:525,
 *   identical layout, a copy-edit not a fresh investigation) and
 *   `void func_80016638(void *a0, s32 a1, s32 a2)`.
 */

typedef struct { s32 a; s32 b[4]; } OtBlk_8018A974_8018BB48;   /* == engine_types.h OtBlk (0x14) */

void func_8018BB48(s32 arg0, s32 arg1, s32 arg2)
{
    extern void *func_80010A08(s32);
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern s32 RotTransPers(s32, s32, s32 *, s32 *);
    extern u8 D_800AF648;
    extern OtBlk_8018A974_8018BB48 D_800A651C[];
    extern u8 D_800A6518[];
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

