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
extern u8 D_8018AED8;
extern u8 D_8018AE48;
extern u8 D_8018AE24;
extern u8 D_8018AE00;
extern u8 D_8018AEB4;
extern u8 D_8018AE90;
extern u8 D_8018AE6C;
extern u8 D_8018ADDC;
extern void func_80145934(void);
extern u8 D_8018AF68;
extern u8 D_8018AF44;
extern u8 D_8018AF20;
extern u8 D_8018AEFC;
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
extern unsigned char D_8018A360[];
extern unsigned char D_8018A390[];
extern unsigned char D_8018A3E0[];
extern unsigned char D_8018A410[];
extern unsigned char D_8018A440[];
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
extern void (*D_8018A490[])(void *);
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
extern s32 D_8018A558[];
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
extern u8 D_8018A5E0[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018A5E8;
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
extern int D_801C5D38;
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
extern s32 D_801C5D3C;
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
extern s32 D_8018A618;
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
extern void (*D_8018A6C0[])(void);
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
extern void (*D_8018A6E4[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018A6D4;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018A6F8[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018A704[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018A714[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018A72C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018A71C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018A740[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018A75C[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018A74C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018A770[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018A784[])(void);
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
extern s32 D_8018A798;
extern void (*D_8018A7C0[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018A7A0;
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
extern int (*D_8018A80C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018A810[])(void);
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
extern unsigned short D_8018AC74[];
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
extern void (*D_8018AC84[])(void);
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
extern int D_801C5D70;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018ACAC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018AC8C;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018AC9C;
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
extern void (*D_8018ACEC[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018ACF4[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018ACC0;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018AD00[])(void);
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
extern u8 D_8018ACD0;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801C5D78;
extern s32 D_801C5D84;
extern s32 D_801C5D88;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018AD3C[])(s32 *);
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
extern s32 D_8018AD10[];
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
extern s32 D_801C5D80;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018AF8C[])(void);
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
extern char D_8018ADAC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018B030[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018B184[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018AFA0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018B18C[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018AFB0;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018AFD0;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018B194[])(void);
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
extern void (*D_8018B1BC[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018B1C8[])(void);
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
extern void (*D_8018B03C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018B26C;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018A350[];
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
extern unsigned char D_8018B280[];
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
extern s8 D_8018B2BC[];
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
extern u16 D_8018B304;
extern u16 D_8018B306;
extern u16 D_8018B308;
extern s32 D_8018B30C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018B314;
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
extern int D_8018B020;
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
extern unsigned int D_8018B398[];
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
extern void (*D_8018B448[])(void);
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
extern u16 D_8018B478[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018B4DC;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801C5D90[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018B500[])(void);
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
extern int D_801C5DE8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018B548[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018B538;
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
extern char D_801C5444[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018B550[])(void);
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
extern void (*D_8018B5A4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018B56C;
extern s16 D_8018B5A0;
extern s16 D_8018B59E;
extern s16 D_8018B59C;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018B5B0[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801C5E48;
extern u8 D_801C5E49;
extern u8 D_801C5E4A;
extern u8 D_801C5E4B;
extern u8 D_801C5E4C;
extern u8 D_801C5E4D;
extern u8 D_801C5E4E;
extern u8 D_801C5E4F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018B5C0[])(void);
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
extern s32 D_801C5E88;
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
extern void (*D_8018B604[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018B680[];
extern s32 D_8018B6A0[];
extern u8 D_8018B71C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018B73C[];
extern u8 D_8018B75C[];
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
extern void (*D_8018B7F8[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018B874[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801C5454;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018B880[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018B888[])(void);
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
extern void (*D_8018B950[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018B960[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018B970[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018B97C[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018B8DC[];
extern u8   D_8018B8F0[];
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
extern void (*D_8018B994[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018B99C[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018B9A4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018B9AC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018B9B4[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018B9BC[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018B9C4[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018BA78[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018BA80[])(void);
extern void func_80169F00(void *a0);
extern char D_8018BA30[];
extern char D_8018B9F0[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018BAB8[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018BAC4[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018BB0C[])(void);
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
extern void (*D_8018BB88[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801C61A8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018BB7C[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018BBC0[];
extern unsigned short D_8018BBC8[];
extern unsigned short D_8018BBD0[];
extern unsigned char D_801C61B0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801C61A8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018BBD8[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801C62E4;
extern M2C_UNK D_801C62E8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801C6270;
extern void (*D_8018BC08[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801C62EC[];
extern u8 D_801C62F4[];
extern u8 D_801C62A4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018BC10[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018BC2C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018BC34[])(void);
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
extern void (*D_8018BC9C[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018BC40;
extern u8 D_8018BC4C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018BCD0[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018BCD8[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018BD2C[])(void);
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
extern u16 D_8018BD60[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018BD50[];
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
extern s32 D_8018BD7C;
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
extern void (*D_8018BDF4[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018BDFC[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018BE04[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018BE0C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018BE14[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018BE1C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018BE28[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018BE34[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018BE40[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018BE50[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018BE60[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018BE68[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018BE70[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018BE78[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018BE80[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018BE88[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018BE90[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018BE98[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018BEA0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018BEA8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018BEB0[])(void);
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
extern void (*D_8018BEB8[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018BEC0[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018BEC8[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018BED0[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018BED8[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018BEE0[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018BEE8[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018BEF0[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018BEF8[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018BF00[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018BF08[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018BF10[])(void);
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
extern void (*D_8018BF54[])(void);
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
extern M2C_UNK D_8018BF18;
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
extern void (*D_8018BF84[])(void);
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
extern void (*D_8018BFC0[])(void);
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
extern void (*D_8018C018[])();
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
extern void (*D_8018C028[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018C030[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018C198[])();
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
extern void (*D_8018C1A4[])();
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
extern M2C_UNK D_801C569C;
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
extern s16 D_801C7FB8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801C6A28;
extern short D_801C802C;
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
extern s32 D_801C6E54;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801C6E7C;
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
extern s16 D_801C6E38;
extern s32 func_8017A3B0(void);
extern short D_801C6E74;
extern short D_801C6E70;
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
extern s16 D_801C6E3C;
extern u16 D_801C6EBC;
extern u16 D_801C6EBE;
extern u16 D_801C6EC0;
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
extern s16 D_801C6EB4;
extern s16 D_801C6EB6;
extern s16 D_801C6EB8;
extern s16 D_801C6EAC;
extern s16 D_801C6EAE;
extern s16 D_801C6EB0;
extern void func_8017B7A8(void);
extern s16 D_801C6ECC;
extern s16 D_801C6ECE;
extern s16 D_801C6ED0;
extern s16 D_801C6ED4;
extern s16 D_801C6ED6;
extern s16 D_801C6ED8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801C6EC4;
extern short D_801C6EC6;
extern short D_801C6EC8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801C6E5C;
extern SV4 D_801C6E64;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801C6E84[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801C6E80)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018C380[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BF34(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8017BF08(void *a0, void *a1, s32 a2, s32 a3);
extern void (*D_8018C3E0[])(void);
extern void func_8017C114(void *a0);
extern void func_8017C8D0(s32 arg0);
extern void (*D_8018C498[])(void);
extern void func_8017D7B0(void *a0);
extern void func_8017D908(void);
extern void func_8017D910(void);
extern s32 D_8018C490;
extern s32 func_8017D938(void);
extern s32 func_8017D954(void);
extern void func_8017DE28(s32 p);
extern void (*D_8018C530[])(void);
extern void func_8017DFF0(void *a0);
extern void (*D_80192258[])(void);
extern void func_8017E620(void *a0);
extern s32 func_8017E6A0(void);
extern void (*D_80192260[])(void);
extern void func_8017E6C4(void *a0);
extern s32 func_800167F0(s32 arg);
extern void func_800CFBCC(s32 arg);
extern s32 func_8017E7BC(void);
extern s32 D_8019226C;
extern void func_8017E7F4(void);
extern void func_8017E81C(void);
extern void func_8017E844(s32 a0);
extern void func_8012A100(s8 a0);
extern void func_8017E9B4(void);
extern void (*D_8019227C[])(void);
extern void func_8017E9D4(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017EAE4(s32 param_1, s16 *param_2);
extern void (*D_80192568[])(void);
extern void func_801805D0(void *a0);
extern void (*D_801927B8[])(void);
extern void func_80180DEC(void *a0);
/* ==== end §8b carried decl layer ==== */

#include "common.h"

/* =============================================================================
 * func_80181CDC  —  ov_SC05_010 / ov_SC05_010_jr_8017C8D0  (769 ins)
 *
 * CONTROL-FLOW MAP (from asm/ov_SC05_010/nonmatchings/ov_SC05_010_jr_8017C8D0/
 * func_80181CDC.s + jtbl_801C5B4C @ asm/ov_SC05_010/data/tail21.data.s:70):
 *
 *   switch ((s16)obj->unk10A)          lh 0x10A / sltiu 6 / jtbl_801C5B4C
 *     case 0 -> 0x801828AC  == epilogue (plain return; the jtbl's slot 0)
 *     case 1 -> 0x80181D38  "seek/steer + timer"      (lines   27..263)
 *     case 2 -> 0x801820C8  "countdown, then SFX"     (lines  264..282)
 *     case 3 -> 0x80182110  "seek, >>9 steer"         (lines  283..515)
 *     case 4 -> 0x80182490  "damped return to rest"   (lines  516..548)
 *     case 5 -> 0x80182514  "seek, >>8 steer"         (lines  549..788)
 *     default (>=6)         -> epilogue
 *
 *   Cases 3 and 5 have IDENTICAL tails; gcc cross-jumped them at .L80182890
 *   (case 3 reaches it with a2=8, case 5 falls in with a2=4).
 *
 * FRAME (0x70):
 *   0x00..0x0F  outgoing-arg area
 *   0x10        SVec1CDC pos  (out-param of func_8012F14C)
 *   0x18        SVec1CDC tgt  (write-only in memory; its values are CSE'd into regs)
 *   0x20        LVec1CDC d    (Square0 scratch: three s32 in a 16-byte VECTOR)
 *   0x30        Rot1CDC  w    (assigned 6x, never read)
 *   0x38,0x40   reload spill slots for the 2 Rot1CDC pseudos that lost the
 *               callee-saved race (reload uses align -1 => BIGGEST_ALIGNMENT 8,
 *               which is what forces the 8-byte stride and pins d/w's sizes)
 *   0x48..0x6C  s0-s7, fp, ra
 *
 * THE FIVE LEVERS THAT MADE IT MATCH (each verified by reverting it):
 *  1. Rot = a 2x16 BITFIELD struct, not `struct {s16 a,b;}`.  Only the bitfield
 *     form is SImode (align 32 from the int base type) and so can live in ONE
 *     register with `insv` field writes: andi 0xFFFF / or (v<<16), and
 *     lui 0xFFFF0000 / and / or (v & 0xFFFF).  The two-s16 struct is BLKmode
 *     (align 16) and lowers to sh/sh + lwl/lwr/swl/swr.
 *  2. `Rot1CDC *wp = &w;` — gcc-2.7.2 DELETES dead stores to non-addressable
 *     locals, so `w` (written 6x, never read) evaporates and the frame shrinks
 *     by 8.  Escaping its address once (and nowhere else) costs no code and
 *     keeps all six `sw ..,0x30($sp)`.   [without this: 758 ins / 379 off]
 *  3. AIM as a MACRO, so each of the 6 copies gets its OWN dx/dy/dz/ang pseudos.
 *     gcc-2.7.2 has no live-range splitting: one shared function-scope set has a
 *     6x longer live_length, loses the global-alloc priority race, and drags the
 *     whole assignment off by one register.       [shared temps: 576 -> 559]
 *  4. `ta`/`tb`: the tail reads COPIES of the pair, not the pair itself.  That is
 *     the single biggest lever — it is where the target's two extra `addu`
 *     copies come from and it re-seats $s0/$s1 for the whole tail.  [514 -> 48]
 *  5. `dz` is REUSED for the >>12 result instead of a fresh `h`.  One pseudo for
 *     both is why the target's $s5 holds dz and then the shifted value, and why
 *     the dz operand chain is NOT coalesced into $s5.            [30 -> MATCH]
 *  NOTE: register pins ($s4 for obj, $s5 for h, $v0 for the mult-sum) were used
 *  as scaffolding while converging and are ALL removable once 4+5 are in place.
 *  The final source needs zero pins.
 *
 * OTHER IDIOMS
 *   - "bgez / addiu 0x1FF / sra 9" is signed DIVISION by 0x200 (not >>9).
 *     Case 5 uses /0x100 (addiu 0xFF / sra 8).
 *   - The object's 16-bit fields are s16: `+=` still emits lhu (gcc truncates on
 *     the store either way), but `f = -0x400` needs the SIGNED type to get
 *     `addiu $v0,$zero,-0x400`; a u16 field emits `ori $v0,$zero,0xfc00`.
 *     unk34 stays u16 (its compare is lhu + sltiu 4).
 *   - `case 0:` must exist and be empty: it is what makes the jump table start
 *     at 0 (sltiu 6, 6 entries, slot 0 = the epilogue) instead of gcc emitting
 *     a 5-entry table with an `addiu -1` bias.
 * ========================================================================== */

   /* 8 bytes */
   /* 16 bytes */
/* 4 bytes, SImode (align 32 from the `int` base type) so it lives in ONE
 * register; field writes lower to `insv` = andi 0xFFFF / or  and
 * lui 0xFFFF0000 / and / or.  A plain `struct {s16 a,b;}` is BLKmode here
 * (align 16) and compiles to sh/sh + lwl/lwr/swl/swr — NOT what the target does. */




extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void Square0(s32 *a0, s32 *a1);
extern s32  ratan2(s32 a0, s32 a1);
extern s32  func_80047948(s32 a0);
extern s32  func_8004787C(s32 a0);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u16  D_80126B5E;
extern u16  D_80126B62;
extern u16  D_80126B66;
extern u8   D_8019292C[];
extern u8  *D_801C7E54;


/* The 6 identical ~50-instruction "aim at (tx,ty,tz)" blocks.  Written as a macro
 * so each copy gets its OWN dx/dy/dz/ang pseudos: gcc-2.7.2 has no live-range
 * splitting, so one shared set of function-scope temps would have a 6x longer
 * live_length and lose the global-alloc priority race the target's temps win. */
#define AIM(dst, tx, ty, tz)                                                  \
    {                                                                         \
        s32 dx = (tx) - obj->x;                                               \
        s32 dy = (ty) - obj->y;                                               \
        s32 dz = (tz) - obj->z;                                               \
        s32 ang = (ratan2(-dz, dx) - 0x400) & 0xFFF;                          \
        dst.b = ang;                                                          \
        dz = (dz * func_80047948(ang) + dx * func_8004787C(ang)) >> 12;       \
        dst.a = ratan2(dy, -dz);                                               \
        w = dst;                                                              \
    }

void func_80181CDC(Obj1CDC *obj) {
    SVec1CDC pos;
    SVec1CDC tgt;
    LVec1CDC d;
    Rot1CDC  w;
    /* gcc-2.7.2 deletes dead stores to NON-addressable locals; the target keeps
     * all 6 `sw ..,0x30($sp)`, so 0x30 must be an addressable object.  Escaping
     * the address here (and nowhere else) reproduces that at zero code cost. */
    Rot1CDC *wp = &w;
    Rot1CDC  ta, tb;
    s32  sum;

    switch (obj->unk10A) {
    case 0:
        break;

    case 1:
        {
            Rot1CDC ra, rb;

            ((void (*)(s32, void *, void *))func_8012F14C)(
                M2C_FIELD(D_801C7E54, s32 *, 0x20) + 0x34, D_8019292C, &pos);

            d.vx = obj->x - pos.vx;
            d.vy = obj->y - pos.vy;
            d.vz = obj->z - pos.vz;
            Square0(&d.vx, &d.vx);
            sum = d.vx + d.vy + d.vz;

            d.vx = obj->x - (s16)D_80126B5E;
            d.vy = obj->y - (s16)D_80126B62;
            d.vz = obj->z - (s16)D_80126B66;
            Square0(&d.vx, &d.vx);
            sum -= d.vx + d.vy + d.vz;

            if (sum > 0) {
                if (sum > 0x4000) {
                    obj->unkFC += 0x20;
                } else {
                    obj->unkFC += sum / 0x200;
                    obj->unk102 -= 1;
                }
                if ((s16)obj->unkFC > 0x400) {
                    obj->unkFC = 0x400;
                }
            } else {
                if (sum < 0) {
                    if (sum < -0x4000) {
                        obj->unkFC -= 0x20;
                    } else {
                        obj->unkFC += sum / 0x200;
                        obj->unk102 -= 1;
                    }
                    if ((s16)obj->unkFC < -0x400) {
                        obj->unkFC = -0x400;
                    }
                }
                obj->unk102 -= 4;
            }

            tgt.vx = D_80126B5E;
            tgt.vy = -0xC0;
            tgt.vz = -0x100;

            AIM(ra, tgt.vx, tgt.vy, tgt.vz)

            AIM(rb, pos.vx, pos.vy, pos.vz)

            ta = ra;
            tb = rb;
            obj->unk20->unk14 += func_8012B608(tb.a, ta.a, 4);
            obj->unk100 += func_8012B608((s16)obj->unk100,
                                         (s16)obj->unk20->unk14, 4);
            obj->unkFE += func_8012B608(tb.b, ta.b, 8);

            if ((s16)obj->unk102 <= 0) {
                obj->unk10A = 2;
                obj->unk102 = 0xF;
            }
        }
        break;

    case 2:
        obj->unk102 -= 1;
        if (obj->unk102 != 0) {
            obj->unkFE += 0x18;
        } else {
            obj->unk10A = 3;
            func_8002D4C8(0x89A, 0);
        }
        break;

    case 3:
        {
            Rot1CDC ra, rb;

            ((void (*)(s32, void *, void *))func_8012F14C)(
                M2C_FIELD(D_801C7E54, s32 *, 0x20) + 0x34, D_8019292C, &pos);

            if (pos.vz > 0) {
                if (obj->unk64->unk34 < 4) {
                    obj->unk10A = 1;
                    obj->unk64->unk100 = 0;
                }
            }

            d.vx = obj->x - pos.vx;
            d.vy = obj->y - pos.vy;
            d.vz = obj->z - pos.vz;
            Square0(&d.vx, &d.vx);
            sum = d.vx + d.vy + d.vz;

            d.vx = obj->x - (s16)D_80126B5E;
            d.vy = obj->y + 0xC0;
            d.vz = obj->z - (s16)D_80126B66;
            Square0(&d.vx, &d.vx);
            sum -= d.vx + d.vy + d.vz;

            if (sum > 0) {
                if (sum > 0x4000) {
                    obj->unkFC += 0x20;
                } else {
                    obj->unkFC += sum / 0x200;
                }
                if ((s16)obj->unkFC > 0x400) {
                    obj->unkFC = 0x400;
                }
            } else if (sum < 0) {
                if (sum < -0x4000) {
                    obj->unkFC -= 0x20;
                } else {
                    obj->unkFC += sum / 0x200;
                }
                if ((s16)obj->unkFC < -0x400) {
                    obj->unkFC = -0x400;
                }
            }

            tgt.vx = D_80126B5E;
            tgt.vy = -0xC0;
            tgt.vz = D_80126B66;

            AIM(ra, tgt.vx, tgt.vy, tgt.vz)

            AIM(rb, pos.vx, pos.vy, pos.vz)

            ta = ra;
            tb = rb;
            obj->unk20->unk14 += func_8012B608(tb.a, ta.a, 4);
            obj->unk100 += func_8012B608((s16)obj->unk100,
                                         (s16)obj->unk20->unk14, 4);
            obj->unkFE += func_8012B608(tb.b, ta.b, 8);
        }
        break;

    case 4:
        obj->unk20->unk14 += func_8012B608((s16)obj->unk20->unk14, 0x180, 0x10);
        obj->unkFC += func_8012B608((s16)obj->unkFC, 0, 0x10);
        obj->unkFE += func_8012B608((s16)obj->unkFE, 0x400, 0x10);
        obj->unk100 += func_8012B608((s16)obj->unk100, 0, 0x10);
        break;

    case 5:
        {
            Rot1CDC ra, rb;

            ((void (*)(s32, void *, void *))func_8012F14C)(
                M2C_FIELD(D_801C7E54, s32 *, 0x20) + 0x34, D_8019292C, &pos);

            if (pos.vz > 0) {
                if (obj->unk64->unk34 < 4) {
                    obj->unk10A = 1;
                    obj->unk64->unk100 = 0;
                }
            }

            d.vx = obj->x - pos.vx;
            d.vy = obj->y - pos.vy;
            d.vz = obj->z - pos.vz;
            Square0(&d.vx, &d.vx);
            sum = d.vx + d.vy + d.vz;

            d.vx = obj->x - (s16)D_80126B5E;
            d.vy = obj->y + 0xC0;
            d.vz = obj->z - (s16)D_80126B66;
            Square0(&d.vx, &d.vx);
            sum -= d.vx + d.vy + d.vz;

            if (sum > 0) {
                if (sum > 0x4000) {
                    obj->unkFC += 0x40;
                } else {
                    obj->unkFC += sum / 0x100;
                }
                if ((s16)obj->unkFC > 0x400) {
                    obj->unkFC = 0x400;
                }
            } else if (sum < 0) {
                if (sum < -0x4000) {
                    obj->unkFC -= 0x40;
                } else {
                    obj->unkFC += sum / 0x100;
                }
                if ((s16)obj->unkFC < -0x400) {
                    obj->unkFC = -0x400;
                }
            }

            tgt.vx = D_80126B5E;
            tgt.vy = -0xC0;
            tgt.vz = D_80126B66;

            AIM(ra, tgt.vx, tgt.vy, tgt.vz)

            AIM(rb, pos.vx, pos.vy, pos.vz)

            ta = ra;
            tb = rb;
            obj->unk20->unk14 += func_8012B608(tb.a, ta.a, 4);
            obj->unk100 += func_8012B608((s16)obj->unk100,
                                         (s16)obj->unk20->unk14, 4);
            obj->unkFE += func_8012B608(tb.b, ta.b, 4);
        }
        break;
    }
}


extern void (*D_80192934[])(void);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_8012B370(int a0);

void func_801828E0(s32 param_1) {
    volatile s32 pad;
    s32 s0;

    D_80192934[*(u16 *)(param_1 + 2)]();

    if (*(u16 *)(*(s32 *)(param_1 + 0x64)) != 0) {
        s0 = *(s32 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x20);
        s0 = s0 + 0x60;

        *(u16 *)(param_1 + 6) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 6) + *(u16 *)(s0 + 0);
        *(u16 *)(param_1 + 0xA) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xA) + *(u16 *)(s0 + 2);
        *(u16 *)(param_1 + 0xE) = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xE) + *(u16 *)(s0 + 4);

        *(u16 *)(param_1 + 6) -= (func_8004787C(*(s16 *)(s0 + 8)) << 6) >> 12;
        *(u16 *)(param_1 + 0xE) -= (func_80047948(*(s16 *)(s0 + 6)) << 6) >> 12;

        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(param_1 + 0xFC) + *(u16 *)(param_1 + 0xFE);

        func_8012B370(param_1);
    }
}


#include "common.h"

extern void (*D_80192990[])(void);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern u8 D_80192924[];
extern void func_8012B370(int a0);

void func_801829F0(s32 param_1) {
    struct { s16 vx, vy, vz, pad; } pos;

    D_80192990[*(u16 *)(param_1 + 2)]();

    if (*(u16 *)(*(s32 *)(param_1 + 0x64)) != 0) {
        u16 t = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0xFC) + 0x400;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12) - t;

        ((void (*)(s32, void *, void *))func_8012F14C)(
            *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34,
            D_80192924,
            &pos);

        *(s16 *)(param_1 + 6)  = pos.vx;
        *(s16 *)(param_1 + 0xA) = pos.vy;
        *(s16 *)(param_1 + 0xE) = pos.vz;

        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(param_1 + 0x64) + 0x100);
        func_8012B370(param_1);
    }
}


#include "common.h"

extern void (*D_801929DC[])(void);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_8012B370(int a0);

void func_80182AC0(void *a0) {
    void *q;
    register void *s0 __asm__("$16");

    D_801929DC[*(u16 *)((s32)a0 + 0x2)]();

    if (*(u16 *)((s32)*(void **)((s32)a0 + 0x64) + 0x0) != 0) {
        q = *(void **)((s32)*(void **)((s32)a0 + 0x64) + 0x20);
        s0 = *(void **)((s32)q + 0x20);
        s0 = (void *)((s32)s0 + 0x60);

        *(u16 *)((s32)*(void **)((s32)a0 + 0x20) + 0x12) =
            *(u16 *)((s32)a0 + 0xFC) + *(u16 *)((s32)a0 + 0xFE);

        *(u16 *)((s32)a0 + 0x6) =
            *(u16 *)((s32)*(void **)((s32)a0 + 0x64) + 0x6) + *(u16 *)((s32)s0 + 0x0);
        *(u16 *)((s32)a0 + 0xA) =
            *(u16 *)((s32)*(void **)((s32)a0 + 0x64) + 0xA) + *(u16 *)((s32)s0 + 0x2);
        *(u16 *)((s32)a0 + 0xE) =
            *(u16 *)((s32)*(void **)((s32)a0 + 0x64) + 0xE) + *(u16 *)((s32)s0 + 0x4);

        *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)a0 + 0x6) +
            ((func_8004787C(*(s16 *)((s32)s0 + 0x8)) << 6) >> 12);

        *(u16 *)((s32)a0 + 0xE) = *(u16 *)((s32)a0 + 0xE) +
            ((func_80047948(*(s16 *)((s32)s0 + 0x6)) << 6) >> 12);

        func_8012B370((int)a0);
    }
}


#include "common.h"
#include "../shared/engine_types.h"

extern void (*D_80192A28[])(void);
extern u8 D_80192924[];
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012B370(int a0);

void func_80182BD0(Obj1CDC *obj) {
    u16 out[3];

    D_80192A28[M2C_FIELD(obj, u16 *, 0x2)]();

    if (M2C_FIELD(obj->unk64, u16 *, 0x0) != 0) {
        u16 fc = M2C_FIELD(obj->unk64, u16 *, 0xFC);
        fc -= 0x400;

        M2C_FIELD(obj->unk20, u16 *, 0x12) =
            *(u16 *)(M2C_FIELD(obj->unk64, s32 *, 0x20) + 0x12) - fc;

        func_8012F14C(M2C_FIELD(obj->unk64, s32 *, 0x20) + 0x34,
                      (s32)D_80192924, (s32)out);

        obj->x = out[0];
        obj->y = out[1];
        obj->z = out[2];

        obj->unk20->unk14 = obj->unk64->unk100;
        func_8012B370((int)obj);
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80182CA0(s32 p)
{
    extern u8 D_80192A30[];
    extern u8 D_80192A9C[];

    *(s32 *)(p + 0x20) = func_8012C1B8(p);
    if (*(s32 *)(p + 0x20) == 0) {
        func_8012CAE4(p);
        return;
    }
    func_8012B23C(p);

    switch (*(s16 *)(p + 0x70)) {
    case 0:
        func_8001CA1C(*(s32 *)(p + 0x20), D_80192A30);
        func_8012A828(p, D_80192A9C);
        *(s16 *)(p + 0x6) = 0x25B;
        *(s16 *)(p + 0x12) = 0x5B;
        *(s16 *)(p + 0x16) = -0x70;
        *(s16 *)(p + 0xA) = -0x70;
        *(s16 *)(p + 0x2) = 1;
        *(s16 *)(*(s32 *)(p + 0x20) + 0x18) = 0x6000;
        *(s16 *)(*(s32 *)(p + 0x20) + 0x1A) = 0x6000;
        *(u32 *)(*(s32 *)(p + 0x20) + 4) |= 0x8000000;
        *(s16 *)(*(s32 *)(p + 0x20) + 0x14) = 0x600;
        break;
    case 1:
        func_8001CA1C(*(s32 *)(p + 0x20), D_80192A30);
        func_8012A828(p, D_80192A9C);
        *(s32 *)(p + 0x94) = rand() & 7;
        *(s16 *)(*(s32 *)(p + 0x20) + 0x18) = 0x4000;
        *(s16 *)(*(s32 *)(p + 0x20) + 0x1A) = 0x4000;
        *(s32 *)(p + 0x48) = *(s32 *)(p + 0x48) * 2 / 3;
        *(s16 *)(p + 0x2) = 2;
        break;
    default:
        func_8001CA1C(*(s32 *)(p + 0x20), D_80192A30);
        func_8012A828(p, D_80192A9C);
        *(s32 *)(p + 0x94) = rand() & 7;
        *(s16 *)(p + 0x2) = 3;
        break;
    }

    *(u32 *)(*(s32 *)(p + 0x20) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(p + 0x20) + 0x2C) |= 0x10;
    func_8002D4C8(0x898, 0);
}


#include "common.h"

/* TU already declares these exact symbols (src/ov_SC05_010/ov_SC05_010_jr_80181CDC.c) —
 * spellings + call idiom copied verbatim from that TU's own neighbours
 * func_801865E8 (L3388-3394, the func_8012CBCC/func_8012C218 pair) and
 * func_80185F08 (L3356-3361, the func_8017ECE4 pair). */
extern void func_8012CBCC(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8017ECE4(void);
extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8004787C(s32 a0);
extern s32  func_80047948(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  rand(void);

/* not declared elsewhere in the TU; matches its usual house form
 * (see DEFINE_func_80186C4C in engine_core.h: `s32 func_80143C74(s32 a0, s32 a1)`). */
extern s32 func_80143C74(s32 a0, s32 a1);

void func_80182E78(s32 a0) {
    s32 r;
    s32 i;
    s32 ang;

    if ((((s32 (*)(s32))func_8012CBCC)(a0) & 0x2000) != 0) {
        ((void (*)(s32))func_8012C218)(a0);
    } else if (((s32 (*)(s32))func_8017ECE4)(a0) > 0) {
        r = func_80143C74(a0, 0);
        if (r != 0) {
            *(s16 *)(*(s32 *)(r + 0x20) + 0x18) = 0x5000;
            *(s16 *)(*(s32 *)(r + 0x20) + 0x1A) = 0x5000;
            *(s16 *)(r + 0x16) = -8;
        }

        for (i = 0; i < 8; i++) {
            r = func_8012C658(0x29E, 2, a0);
            if (r != 0) {
                ang = (rand() & 0x1FF) + (i << 9);
                *(s32 *)(r + 0x10) = func_8004787C(ang) << 6;
                *(s32 *)(r + 0x18) = func_80047948(ang) << 6;
                *(s32 *)(r + 0x14) = 0xFFF80000 - ((rand() & 0x3FF) << 8);
            }
        }

        ((void (*)(s32))func_8012C218)(a0);
        func_8002D4C8(0x899, 0);
    } else {
        s32 v = *(s32 *)(a0 + 0x10) * 7;
        if (v < 0) {
            v += 7;
        }
        *(s32 *)(a0 + 0x10) = v >> 3;
    }
}


void func_80182FD4(void *a0) {
    extern void (*D_80192AEC[])(void);
    extern u16 D_80126B96;
    extern s16 D_80126B98;
    extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
    extern void func_8012C218(void *a0);

    D_80192AEC[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0 && *(s16 *)((s32)a0 + 0x70) < 2) {
        *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0x40;
        if (func_8012D624(a0, 0x30, 0x18) == 1) {
            D_80126B96 = 0x4014;
            D_80126B98 = 0x18;
            func_8012C218(a0);
        } else {
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) + 0x40;
        }
    }
}


extern u16  D_80126B5E;
extern u16  D_80126B66;
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8   D_801152A8[];
extern s32  D_801C7E4C;
extern void func_8012C218(void *a0);
extern s32  func_8014CB8C(void);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

/* The camera x/y pair at D_80126B5E / D_80126B5E+4 (== D_80126B62).  The target
 * reads BOTH through the one `la $s1, D_80126B5E` (`lh 0x0($s1)` / `lh 0x4($s1)`),
 * so they must be reached through a pointer — see the launder below. */
typedef struct {
    u16 x;      /* 0x00  D_80126B5E */
    u16 unk2;   /* 0x02 */
    u16 y;      /* 0x04  D_80126B62 */
} Cam183098;

void func_80183098(s32 param_1) {
    u16 sp18[3];
    u16 sp20[3];
    Cam183098 *cam;
    s32 d;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        if (*(u16 *)(param_1 + 0x72) & 0x4000) {
            goto free_it;
        }
        break;
    case 1:
        if (*(u16 *)(param_1 + 0x72) & 0x4000) {
            goto free_it;
        }
        *(s32 *)(param_1 + 0x10) += 0xC000;
        break;
    default:
        goto free_it;
    }

    /* §153 address-rematerialisation launder: without it cse's find_best_addr
     * folds `cam->y` back to %hi/%lo(D_80126B5E+4) and emits a SECOND `la`
     * instead of the target's `lh 0x4($s1)`.  Zero bytes. */
    cam = (Cam183098 *)&D_80126B5E;
    __asm__("" : "=r"(cam) : "0"(cam));

    *(s32 *)(param_1 + 0x4) += *(s32 *)(param_1 + 0x10);
    *(s32 *)(param_1 + 0x8) += *(s32 *)(param_1 + 0x14);

    /* ONE local for both tail-guard differences (§176-B addendum): it is what
     * puts the load pair on $v1/$v0 and lets sched2's WAR edge emit
     * addu;addu;sw;sw;lh above. */
    d = *(s16 *)(param_1 + 0x6) - (s16)cam->x;
    if ((u32)(d + 0x1F) >= 0x3F) {
        return;
    }
    d = (s16)cam->y - *(s16 *)(param_1 + 0xA);
    if ((u32)(d + 0xF) >= 0x7F) {
        return;
    }

    if (func_8014CB8C() != 0) {
    free_it:
        {
            s32 p = D_801C7E4C;
            *(s32 *)(p + 0xDC) -= 1;
            func_8012C218((void *)param_1);
        }
    } else {
        /* x and y must both be READ before the first store (the stores to the
         * addressable sp arrays kill cse's equivalences for the `cam` loads);
         * z is read late and dies immediately, so all three land in $v0/$v1.
         * The two chained assignments (§205) give the store order
         * 0x20,0x18 … 0x24,0x1C the target schedules. */
        u16 x = cam->x;
        u16 y = cam->y;

        sp18[0] = sp20[0] = x;
        sp18[1] = y - 0x10;
        sp20[1] = y + 0x10;
        sp18[2] = sp20[2] = D_80126B66;
        if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)sp18, (s32)sp20) == 0) {
            return;
        }
        func_8012F568(1, 0x2020, 0x400, 0x10, (s32)sp20, (s32)D_801152A8);
    }
}



extern void (*D_80192B68[])(void);

void func_80183238(void *a0) {
    D_80192B68[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C218(void *a0);
extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8004787C(s32 a0);
extern s32  func_80047948(s32 a0);
extern s32  func_80143C74(s32 a0, s32 a1);
extern s32  func_80153BD8(s32 a0);
extern void func_80153C74(s16 a0, s16 a1);
extern s32  rand(void);
extern u8  *D_801C7E54;

void func_80183274(s32 a0) {
    extern void (*D_80192CB8[])(void);
    extern s32 D_801C7E5C;
    extern s32 D_801C7E70;
    extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
    s32 pad[4];
    s32 r;
    s32 i;
    s32 ang;
    (void)pad;

    D_80192CB8[*(u16 *)(a0 + 0x2)]();
    if (*(u16 *)(a0) != 0) {
        if (func_80153BD8((s32) D_801C7E54) != 0 || func_80153BD8(D_801C7E5C) != 0) {
            if (D_801C7E70 == 0) {
                func_80153C74(2, 0x28);
                D_801C7E70 = 0x1E;
                r = func_80143C74(a0, 0);
                if (r != 0) {
                    *(s16 *)(*(s32 *)(r + 0x20) + 0x18) = 0x5000;
                    *(s16 *)(*(s32 *)(r + 0x20) + 0x1A) = 0x5000;
                    *(s16 *)(r + 0x16) = -8;
                }
                for (i = 0; i < 8; i++) {
                    r = func_8012C658(0x29E, 2, a0);
                    if (r != 0) {
                        ang = (rand() & 0x1FF) + (i << 9);
                        *(s32 *)(r + 0x10) = func_8004787C(ang) << 6;
                        *(s32 *)(r + 0x18) = func_80047948(ang) << 6;
                        *(s32 *)(r + 0x14) = 0xFFF80000 - ((rand() & 0x3FF) << 8);
                    }
                }
                func_8012C218(a0);
            }
        } else {
            func_8012D624((void *)a0, 0x10, 0x28);
        }
    }
}









extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern s32 func_8004787C(s32 a0);
extern s32 D_80126950;
extern void *func_80010A08(s32 size);
extern s32 GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8005A600(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern s32 AddPrim(s32 ot, void *prim);

extern u8 D_800AF648;
extern s32 D_800A651C[];
extern s16 D_800B9A02;
extern s16 D_80192CC0;
extern s16 D_80192CC4[];
extern u8 D_80192CD0[];
extern u8 D_80192CD1[];
extern u8 D_80192CD2[];
extern u8 D_80192CD3[];
extern u8 D_80192CE0[];
extern u8 D_80192CE1[];
extern u8 D_80192CE2[];
extern u8 D_80192CE3[];
extern u8 D_80192CF0[];
extern u8 D_80192CF1[];
extern u8 D_80192CF2[];
extern u8 D_80192CF3[];

void func_8018340C(void *a0)
{
    s32 tags[4];      /* sp+0x18 */
    s16 in[4];        /* sp+0x28 */
    s16 xs[8];        /* sp+0x30 */
    s16 ys[8];        /* sp+0x40 */
    struct {
        u16 sxy[2];   /* sp+0x50 */
        s32 p;        /* sp+0x54 */
        s32 flag;     /* sp+0x58 */
    } o;

    s32 ot;
    s32 m;
    s32 d;
    s32 e;
    s32 x;
    s32 y;
    s32 t;
    s32 u;
    s32 ret;
    u8 *prim;
    u8 *pp;
    u8 *base;
    s16 *pal;
    s32 i;
    s32 k;
    /* cookbook SS194-A: the zero-byte volatile-asm fence below keeps the
       D_80126950 load from being hoisted into the imul latency gap (sched1
       priority, map sched.md S3). The three pins split the one collapsed
       chain pseudo into the target's $t0/$v0/$a2 triple (local-alloc). */
    register s32 aa __asm__("$8");
    register s32 bb __asm__("$2");
    register s32 cc __asm__("$6");

    in[0] = *(s16 *)((s8 *)a0 + 0x06);
    in[1] = *(s16 *)((s8 *)a0 + 0x0A);
    in[2] = *(s16 *)((s8 *)a0 + 0x0E);

    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);

    ret = RotTransPers((s32)in, (s32)o.sxy, &o.p, &o.flag);
    if ((ret > 0) && (o.flag >= 0)) {
        ot = *(s32 *)((s8 *)&D_800A651C + (u16)D_800B9A02 * 0x14) + ret * 4;
        m = D_80192CC0;
        t = func_8004787C(*(s16 *)((s8 *)a0 + 0xDE)) * 3;
        if (t < 0) {
            t += 7;
        }
        t = (t >> 3) - 0x800;
        if (t < 0) {
            u = func_8004787C(*(s16 *)((s8 *)a0 + 0xDE)) * 3;
            if (u < 0) {
                u += 7;
            }
            t = 0x800 - (u >> 3);
        } else {
            t = func_8004787C(*(s16 *)((s8 *)a0 + 0xDE)) * 3;
            if (t < 0) {
                t += 7;
            }
            t = (t >> 3) - 0x800;
        }
        aa = t * m;
        bb = aa >> 12;
        cc = bb + 8;
        __asm__ __volatile__("");
        d = cc * (D_80126950 + 500);
        d = d / (ret * 4);

        x = o.sxy[0];
        y = o.sxy[1];
        e = (d * 179) >> 8;

        xs[2] = x;
        ys[2] = y;
        xs[0] = x - d;
        xs[1] = x - e;
        xs[3] = x + e;
        xs[4] = x + d;
        ys[0] = y - d;
        ys[1] = y - e;
        ys[3] = y + e;
        ys[4] = y + d;

        prim = (u8 *)func_80010A08(0x9C);
        if (prim != 0) {
            s32 tp;
            tp = GetTPage(0, 1, 0, 0);
            func_8005A600((s32)prim, 0, 1, (u16)tp, 0);

            tags[0] = (s32)(prim + 0xC);
            pp = prim + 0xC;
            pal = D_80192CC4;
            base = (u8 *)tags;
            k = 0;
            tags[1] = (s32)(prim + 0x30);
            tags[2] = (s32)(prim + 0x54);
            tags[3] = (s32)(prim + 0x78);
            do {
                i = k * 4;
                *(u32 *)(pp + 0x04) = ((u32 *)pal)[D_80192CF0[i]];
                *(u32 *)(pp + 0x0C) = ((u32 *)pal)[D_80192CF1[i]];
                *(u32 *)(pp + 0x14) = ((u32 *)pal)[D_80192CF2[i]];
                *(u32 *)(pp + 0x1C) = ((u32 *)pal)[D_80192CF3[i]];
                *(u8 *)(pp + 0x03) = 8;
                *(u8 *)(pp + 0x07) = 0x3A;
                *(u16 *)(pp + 0x08) = *(u16 *)(base + 0x18 + D_80192CD0[i] * 2);
                *(u16 *)(pp + 0x10) = *(u16 *)(base + 0x18 + D_80192CD1[i] * 2);
                *(u16 *)(pp + 0x18) = *(u16 *)(base + 0x18 + D_80192CD2[i] * 2);
                *(u16 *)(pp + 0x20) = *(u16 *)(base + 0x18 + D_80192CD3[i] * 2);
                *(u16 *)(pp + 0x0A) = *(u16 *)(base + 0x28 + D_80192CE0[i] * 2);
                *(u16 *)(pp + 0x12) = *(u16 *)(base + 0x28 + D_80192CE1[i] * 2);
                *(u16 *)(pp + 0x1A) = *(u16 *)(base + 0x28 + D_80192CE2[i] * 2);
                *(u16 *)(pp + 0x22) = *(u16 *)(base + 0x28 + D_80192CE3[i] * 2);
                AddPrim(ot, pp);
                k += 1;
                pp += 0x24;
            } while (k < 4);
            AddPrim(ot, prim);
        }
    }
}


#include "common.h"

/* Spellings copied from the destination TU src/ov_SC05_010/ov_SC05_010_jr_80181CDC.c
 * (L379 D_801202A0, L1245 func_801746DC, L1461 func_800D0C48, L2529 func_80178B18,
 *  L2581 func_8001AAA0, L2528 func_80178970, L2536 func_80178D18, L2392 func_80174774,
 *  L165 func_8014704C, L1785 D_80126B66, L3231 func_8012C218, L51 func_8002D4C8,
 *  L949 rand) — the `(void)`-declared callees are reached through the TU's own
 *  ((void (*)(s32))f)(x) cast idiom (func_801844AC L3710). */
extern u8   D_801202A0[];
extern u8   D_801923C4[];
extern void func_801746DC(void);
extern s32  func_80178B18(s32 param_1, s32 param_2);
extern void func_800D0C48(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  rand(void);
extern int  func_8001AAA0(void);
extern int  func_80178970(void);
extern void func_80178D18(void);
extern s16  func_80174774(void);  /* TU decl says s16, but the target has NO
                                  * sll/sra extension before the beqz -> the call site
                                  * is reached through an s32-returning cast (below). */
extern void func_8014704C(s32 *a0);
extern u16  D_80126B66;

/* not declared in the TU */
extern s32  func_8012C588(s32 a0, s32 a1);
extern s32  func_80132EF4(s32 a0, s32 a1);
extern void func_8013373C(s16 a0);
extern void func_8017C068(void);
extern void func_80187874(void);
extern void func_8002AC00(s32 a0);
extern s32  D_801C7E30[];
extern s32  D_801C7E50[];  /* == &D_801C7E30[8]; the target .s relocates against THIS symbol */
extern s32  D_801C7E4C;
extern s32  D_80192D64[];
extern s32  D_80126B58;
extern s32  D_80126B60;

void func_8018388C(s32 param_1) {
    s32 i;
    s32 obj;
    u8 *q;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        func_80178B18(param_1, (s32)D_801923C4);
        func_801746DC();
        *(s32 *)(param_1 + 0x1C) = 0x80;
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        func_800D0C48(4);
        q = D_801202A0;
        for (i = 0; i < 0x60; i++) {
            if (*(u16 *)q == 0x2B5) {
                func_8012C218(q);
            }
            q += 0x10C;
        }
        *(s32 *)(D_801C7E4C + 0xE0) = 0x10000000;
        break;

    case 1:
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
        if ((*(s32 *)(param_1 + 0x1C) & 0xF) == 0) {
            obj = func_8012C588(0x2DE, param_1);
            if (obj != 0) {
                func_8002D4C8(0x8B8, 0);
                *(u16 *)(obj + 0xA) = *(u16 *)(obj + 0xA) + 0x20;
                if (*(s32 *)(param_1 + 0x1C) & 0x40) {
                    *(u16 *)(obj + 0xFC) = (*(s32 *)(param_1 + 0x1C) & 0x30) << 6;
                } else {
                    *(u16 *)(obj + 0xFC) = ((*(s32 *)(param_1 + 0x1C) & 0x30) << 6) + 0x200;
                }
                *(u16 *)(obj + 0xFC) = *(u16 *)(obj + 0xFC) + (rand() & 0x1FF);
                *(u16 *)(obj + 0xFE) = *(s32 *)(param_1 + 0x1C) + 0x60;
            }
        }
        if (*(s32 *)(param_1 + 0x1C) == 0) {
            *(s32 *)(param_1 + 0x1C) = 0x10;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        }
        break;

    case 2:
        if (*(s32 *)(param_1 + 0x1C) == 0) {
            *(s32 *)(param_1 + 0x1C) = 0x3C;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            func_8012C588(0x2DC, D_801C7E30[0]);
            func_80132EF4(D_801C7E30[0], 0x5F);
            func_8002D4C8(0x8B9, 0);
        } else {
            *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
        }
        break;

    case 3:
        if (*(s16 *)(param_1 + 0x84) == 0) {
            *(s16 *)(param_1 + 0x84) = ((s32 (*)(s32))func_8001AAA0)(0x6D);
        }
        if (*(s32 *)(param_1 + 0x1C) != 0) {
            *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) - 1;
        } else {
            func_8012C218((void *)D_801C7E30[0]);
            D_801C7E30[0] = 0;
            for (i = 2; i < 8; i++) {
                func_8012C218((void *)*(s32 *)(D_801C7E30[i] + 0x6C));
                func_8012C218((void *)D_801C7E30[i]);
                D_801C7E30[i] = 0;
            }
            for (i = 8; i < 12; i++) {
                func_8012C218((void *)D_801C7E50[i - 8]);
                D_801C7E50[i - 8] = 0;
            }
            q = D_801202A0;
            for (i = 0; i < 0x60; i++) {
                if (*(u16 *)q == 0x275) {
                    func_8012C218(q);
                }
                q += 0x10C;
            }
            func_8014704C(&D_80126B58);
            func_8013373C(0);
            *(s16 *)(param_1 + 0xA) = 0x77;
            *(s16 *)(param_1 + 0x6) = 0;
            *(s16 *)(param_1 + 0xE) = 0;
            D_80126B60 = 0x970000;
            D_80126B66 = 0x90;
            func_8012C588(0x2F7, param_1);
            for (i = 0; i < 0x18; i++) {
                obj = func_8012C588(0x2E3, param_1);
                if (obj != 0) {
                    *(s32 *)(*(s32 *)(obj + 0x20) + 0x24) = D_80192D64[i];
                }
            }
            func_8017C068();
            func_80187874();
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        }
        break;

    case 4:
        if (*(s16 *)(param_1 + 0x84) == 0) {
            *(s16 *)(param_1 + 0x84) = ((s32 (*)(s32))func_8001AAA0)(0x6D);
        }
        break;

    case 5:
        if (((s32 (*)(void))func_80174774)() != 0) {
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x80000000;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            func_8002AC00(0x1E);
        }
        break;

    case 6:
        break;
    }

    if (((s32 (*)(s32))func_80178970)(param_1) != 0) {
        ((void (*)(s32))func_80178D18)(param_1);
        *(u16 *)(param_1 + 0x2) = 6;
    }
}


extern s32 func_8004787C(s32 a0);
extern void func_8018340C(void *a0);
extern u8 D_80192D4C[];
extern u8 D_80192D4E[];
extern u8 D_80192D50[];
extern void (*D_80192DC4[])(void *);

void func_80183C84(void *a0) {
    if (*(s32 *)(*(s32 *)((s32)a0 + 0x20) + 4) >= 0) {
        *(u16 *)((s32)a0 + 0xDC) = (*(u16 *)((s32)a0 + 0xDC) + 0x88) & 0xFFF;
        *(s16 *)&D_80192D4C = (func_8004787C(*(s16 *)((s32)a0 + 0xDC)) >> 6) + 0xC0;
        *(s16 *)&D_80192D4E = (func_8004787C(*(s16 *)((s32)a0 + 0xDC)) >> 6) + 0xC0;
        *(s16 *)&D_80192D50 = (func_8004787C(*(s16 *)((s32)a0 + 0xDC)) >> 6) + 0xC0;
        *(u16 *)((s32)a0 + 0xDE) = (*(u16 *)((s32)a0 + 0xDE) - 0x88) & 0xFFF;
        func_8018340C(a0);
    }
    D_80192DC4[*(u16 *)((s32)a0 + 2)](a0);
}


typedef struct { s16 vx, vy, vz, pad; } SV83;

void func_80183D5C(s32 arg0)
{
    extern void func_8004914C(void *);
    extern void func_800491AC(void *);
    extern s32 func_8004787C(s32);
    extern s32 func_80047948(s32);
    extern s32 RotTransPers3(void *, void *, void *, s32 *, s32 *, s32 *, s32 *, s32 *);
    extern void *func_80010A08(s32);
    extern s32 GetTPage(s32, s32, s32, s32);
    extern s32 func_8005A600(s32, s32, s32, s32, s32);
    extern s32 AddPrim(s32, void *);
    extern u8 D_800AF648;
    extern s32 D_800A651C[];
    extern s16 D_800B9A02;

    register u8 *db __asm__("$16");
    register s32 obj __asm__("$17");
    void *q;
    SV83 v[3];
    s32 scr[6];
    s32 ret;
    s32 tp;
    s32 i;
    u16 *e;
    u8 *r;
    s32 ot;

    obj = arg0;
    db = &D_800AF648;
    func_8004914C(db);
    func_800491AC(db);

    v[0].vx = *(u16 *)((char *)obj + 6);
    v[0].vy = *(u16 *)((char *)obj + 0xA);
    v[0].vz = *(u16 *)((char *)obj + 0xE);

    ret = func_8004787C(*(s16 *)((char *)obj + 0xFC) + 0x40);
    v[1].vx = *(u16 *)((char *)obj + 6) - (ret * *(s16 *)((char *)obj + 0x100) >> 7);
    v[1].vy = *(u16 *)((char *)obj + 0xA) - (*(u16 *)((char *)obj + 0x100) << 5);
    ret = func_80047948(*(s16 *)((char *)obj + 0xFC) + 0x40);
    v[1].vz = *(u16 *)((char *)obj + 0xE) - (ret * *(s16 *)((char *)obj + 0x100) >> 7);
    ret = func_8004787C(*(s16 *)((char *)obj + 0xFC) - 0x40);
    v[2].vx = *(u16 *)((char *)obj + 6) - (ret * *(s16 *)((char *)obj + 0x100) >> 7);
    v[2].vy = *(u16 *)((char *)obj + 0xA) - (*(u16 *)((char *)obj + 0x100) << 5);
    ret = func_80047948(*(s16 *)((char *)obj + 0xFC) - 0x40);
    v[2].vz = *(u16 *)((char *)obj + 0xE) - (ret * *(s16 *)((char *)obj + 0x100) >> 7);

    ret = RotTransPers3(&v[0], &v[1], &v[2], &scr[0], &scr[1], &scr[2], &scr[4], &scr[5]);
    if (ret <= 0 || scr[5] < 0) {
        *(u16 *)((char *)obj + 0x102) = 0;
        *(u16 *)((char *)obj + 0x100) = *(u16 *)((char *)obj + 0x100) - 1;
        return;
    }
    ret -= 0x10;

    ot = D_800A651C[*(u16 *)&D_800B9A02 * 5] + (ret << 2);

    q = func_80010A08(0x30);
    if (q == 0) {
        return;
    }

    tp = GetTPage(0, 1, 0, 0);
    func_8005A600((s32)q, 0, 0, (u16)tp, 0);

    r = (u8 *)q + 0xC;
    for (i = 0, e = (u16 *)scr; i < 3; i++) {
        if (!((u16)(e[0] + 0xA0) < 0x141 && (u16)(e[1] + 0x78) < 0xF1)) {
            *(u16 *)((char *)obj + 0x102) = 0;
        }
        e += 2;
    }

    r[0x1C] = r[0x14] = r[0xC] = r[4] = 0xFF;
    r[0x1D] = r[0x15] = r[0xD] = r[5] = 0xFF;
    r[0x1E] = r[0x16] = r[0xE] = r[6] = 0xFF;
    r[3] = 8;
    r[7] = 0x3A;
    *(u16 *)(r + 8) = *(volatile u16 *)&scr[0];
    *(u16 *)(r + 0x10) = *(volatile u16 *)&scr[0];
    *(u16 *)(r + 0x18) = *(volatile u16 *)&scr[1];
    *(u16 *)(r + 0x20) = *(volatile u16 *)&scr[2];
    *(u16 *)(r + 0xA) = *(volatile u16 *)((u16 *)&scr[0] + 1);
    *(u16 *)(r + 0x12) = *(volatile u16 *)((u16 *)&scr[0] + 1);
    *(u16 *)(r + 0x1A) = *(volatile u16 *)((u16 *)&scr[1] + 1);
    *(u16 *)(r + 0x22) = *(volatile u16 *)((u16 *)&scr[2] + 1);
    AddPrim(ot, r);
    AddPrim(ot, q);
}


void func_80184084(s32 a0)
{
    u16 v0;
    s32 t;

    v0 = *(u16 *)(a0 + 2);
    if (v0 == 0) {
        *(u16 *)(a0 + 2) = v0 + 1;
        *(u16 *)(a0 + 0x102) = 1;
    } else {
        t = *(s32 *)(a0 + 0x1C) + 1;
        *(s32 *)(a0 + 0x1C) = t;
        if (t >= *(s16 *)(a0 + 0xFE)) {
            func_8012C218((void *)a0);
        } else {
            *(u16 *)(a0 + 0x100) = *(u16 *)(a0 + 0x100) + *(u16 *)(a0 + 0x102);
            func_80183D5C(a0);
        }
    }
}



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
void func_80184100(u8 *a0, s8 a1) {
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



extern void (*D_80192DE0[])(void);

void func_801841A8(void *a0) {
    D_80192DE0[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_801841E4(s32 *a0) {
    s32 *v0;

    v0 = *(s32 **)(((u8 *)a0) + 0x20);
    *(s16 *)(((u8 *)v0) + 0x1C) = 0;
    *(s16 *)(((u8 *)v0) + 0x1A) = 0;
    *(s16 *)(((u8 *)v0) + 0x18) = 0;
    func_8012AD44(a0, 1);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80184214(void *a0) {
        *(s8 *)((s32)a0 + 0xFC) = 0x8;
        ((void (*)(s32, s32))func_8012AD44)((s32)a0, 0x2);
    }


















extern void func_8012AD44(s32 *a0, s16 a1);
void func_8018423C(void)
{
  int new_var;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 3);
  new_var = (unsigned int) 0x51AB;
 do { } while (0);
}


extern void (*D_80192DE8[])(void);

void func_8018425C(void *a0) {
    D_80192DE8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80192DF8[])(void);

void func_80184298(void *a0) {
    D_80192DF8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80192E34[])(void);

void func_801842D4(void *a0) {
    D_80192E34[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80192E50[])(void);

void func_80184310(void *a0) {
    D_80192E50[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80192E6C[])(void);

void func_8018434C(void *a0) {
    D_80192E6C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_8019426C[])(void);

void func_80184388(void *a0) {
    D_8019426C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801843C4(s32 param_1)
{
    extern u8 D_80193EB4[];
    extern u8 D_80193674[];
    extern u8 D_80193E74[];
    extern u8 D_80193ECC[];
    extern u8 D_80192E74[];
    s32 v0;

    func_800599B8((u16 *)D_80193EB4, (u16 *)D_80192E74);
    func_800599B8((u16 *)(D_80193EB4 + 8), (u16 *)D_80193674);
    func_800599B8((u16 *)(D_80193EB4 + 0x10), (u16 *)D_80193E74);
    *(u16 *)(param_1 + 0xA) = 0x97;
    *(u16 *)(param_1 + 6) = 0;
    *(u16 *)(param_1 + 0xE) = 0;
    v0 = func_801849DC(param_1, (s32)D_80193ECC, 0x300, 0x100, 0xA1);
    *(s32 *)(param_1 + 0xCC) = v0;
    if (v0 == 0) {
        goto fail;
    }
    v0 = func_801849DC(param_1, (s32)D_80193ECC, 0x310, 0x100, 0xA2);
    *(s32 *)(param_1 + 0xD0) = v0;
    if (v0 == 0) {
        func_80016714((void *)*(s32 *)(param_1 + 0xCC), 0x38);
    fail:
        func_8012CAE4((void *)param_1);
        return;
    }
    *(u16 *)(param_1 + 2) = 1;
}


#include "common.h"

extern s32 func_8012BD14(s32 a0);
extern void func_801746DC(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_801789AC(s32 arg0);
extern void func_80178D18(void);
extern s32 func_8014CB58(void);
extern void func_8014B598(s32 a0, s32 a1);
extern s32 func_8016F1AC(void);
extern void func_80175454(void);
extern void func_800D0C48(s32 a0);
extern s32 func_8014CB2C(void);
extern void func_80184934(s32 param_1);
extern void func_80184988(s32 param_1);
extern s32 func_8016F0AC();
extern void func_8002959C(void);
extern s32 D_8018C490;
extern u8 D_80194234[];
extern u8 D_80194244[];

void func_801844AC(s32 param_1) {
    u16 n;
    if (func_8012BD14(param_1) < 0x401
        || (u32)(*(u16 *)(param_1 + 0x34) - 1) < 2) {
        switch (*(u16 *)(param_1 + 0x34)) {
        case 0:
            func_801746DC();
            func_80178B18(param_1, (s32)D_80194234);
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            break;
        case 1:
            if (func_801789AC(param_1) == 1) {
                ((void (*)(s32))func_80178D18)(param_1);
                *(u16 *)(param_1 + 0x34) = 3;
            }
            break;
        case 2:
            if (func_801789AC(param_1) == 1) {
                ((void (*)(s32))func_80178D18)(param_1);
                *(u16 *)(param_1 + 0x34) = 4;
            }
            break;
        case 3:
            if (func_8014CB58() == 5) {
                func_8014B598(5, (s32)&D_8018C490);
                if (func_8016F1AC() != 0) {
                    if ((*(u16 *)(param_1 + 0x100) & 4) == 0) {
                        *(u16 *)(param_1 + 0x100) |= 4;
                        *(s32 *)(param_1 + 0x1C) = 0;
                        func_80175454();
                    }
                }
                if (*(u16 *)(param_1 + 0x100) & 4) {
                    *(s32 *)(param_1 + 0x1C) += 1;
                }
                if (!(*(u16 *)(param_1 + 0x100) & 2)
                    && *(s32 *)(param_1 + 0x1C) == 0x5A) {
                    *(u16 *)(param_1 + 0x100) |= 2;
                    func_800D0C48(0);
                }
                if (!(*(u16 *)(param_1 + 0x100) & 1)) {
                    if ((func_8014CB2C() & 0x8000007F) == 0x80000005) {
                        n = *(u16 *)(param_1 + 0x34) + 1;
                        *(u16 *)(param_1 + 0x100) |= 1;
                        *(u16 *)(param_1 + 0x34) = n;
                    }
                }
            }
            break;
        }
        func_80184934(param_1);
        func_80184988(param_1);
    } else {
        *(u8 *)(*(s32 *)(param_1 + 0xCC) + 0x27) = 0xA1;
        func_80184988(param_1);
    }
    if (*(u16 *)(param_1 + 0x100) & 1) {
        *(u16 *)(param_1 + 0x100) &= ~1;
        func_8016F0AC();
        *(u16 *)(param_1 + 2) = 2;
        *(u16 *)(param_1 + 0x34) = 0;
        *(u8 *)(*(s32 *)(param_1 + 0xCC) + 0x27) = 0xA1;
        *(u8 *)(*(s32 *)(param_1 + 0xD0) + 0x27) = 0xA2;
        func_80178B18(param_1, (s32)D_80194244);
        *(u16 *)(param_1 + 0x102) = 0xA;
        *(s32 *)(param_1 + 0x1C) = 0;
        *(u16 *)(param_1 + 0x104) = 0xAF;
        func_8002959C();
    }
}
