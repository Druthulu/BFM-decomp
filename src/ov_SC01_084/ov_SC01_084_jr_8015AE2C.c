#include "common.h"
#include "../shared/engine_core.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80188D84;
extern u8 D_80188CF4;
extern u8 D_80188CD0;
extern u8 D_80188CAC;
extern u8 D_80188D60;
extern u8 D_80188D3C;
extern u8 D_80188D18;
extern u8 D_80188C88;
extern void func_80145934(void);
extern u8 D_80188E14;
extern u8 D_80188DF0;
extern u8 D_80188DCC;
extern u8 D_80188DA8;
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
extern unsigned char D_8018820C[];
extern unsigned char D_8018823C[];
extern unsigned char D_8018828C[];
extern unsigned char D_801882BC[];
extern unsigned char D_801882EC[];
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
extern void (*D_8018833C[])(void *);
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
extern void func_8012F14C(s32);
extern void func_80149374(s32 arg0, s32 arg1);
extern void func_801493D0(s32 param_1, s32 param_2, s32 param_3);
extern void func_8012F038(s32);
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
extern s32 func_8012E5CC(s32 a0, s32 a1, s32 a2);
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
extern s32 D_80188404[];
extern u8 D_80078E78[];
extern s32 func_80149FB0(s32 a0);
extern s32 func_80135260(s32, s32, s32, s32);
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
extern u8 D_8018848C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80188494;
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
extern struct Packed8 D_80126C98;
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
extern void func_8014CF04();
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
extern int D_801C6330;
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
extern s32 D_801C6334;
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
extern s32 D_801884C4;
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
extern void (*D_8018856C[])(void);
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
extern void (*D_80188590[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80188580;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_801885A4[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_801885B0[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801885C0[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801885D8[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801885C8;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801885EC[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80188608[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801885F8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018861C[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80188630[])(void);
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
extern s32 D_80188644;
extern void (*D_8018866C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018864C;
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
extern int (*D_801886B8[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801886BC[])(void);
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
extern S801563EC *func_801563EC(u16 idx);
extern s32 func_80029B4C(s32 a0, s32 a1);
extern s32 func_80029BC8(s32 a0, s32 a1);
extern s32 func_80029C44(s32 a0, s32 a1);
extern s32 func_8015640C(s32 a0, s32 a1);
extern s32 rand(void);
extern u32 func_8015616C(s32 param_1, u16 param_2);
extern u16 func_80156370(u16 param_1);
extern S801563EC * func_801563EC(u16 idx);
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
extern s32 func_8014C568(void *a0);
extern void func_801567BC(s32 a0);
extern B8 D_80128120[];
extern B8 D_80128138[];
extern S8 D_80126AF0[];
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern unsigned char D_8011520C[];
extern unsigned short D_80188B20[];
extern void func_80156A1C(s32 param_1, s32 param_2);
extern s32 D_801150E0[];
extern void func_80156A88(s32 a0, s32 a1);
extern void func_80156B74(s32 param_1, u32 param_2, u8 *param_3);
extern void func_80156ECC(int param_1, int param_2, int param_3, int param_4, int param_5);
extern void func_80156FA8(s16 *param_1, s16 *param_2, s16 *param_3);
extern void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern s32 func_80135260(s32 a0, s32 a1, s32 a2, s32 a3);
extern u32 func_801571C4(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801575E4(void *a0);
extern void func_801574DC(s32 *a0);
extern void func_80157544(void *a0);
extern void (*D_80188B30[])(void);
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
extern int D_801C6368;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80188B58[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80188B38;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80188B48;
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
extern void (*D_80188B98[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80188BA0[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80188B6C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80188BAC[])(void);
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
extern u8 D_80188B7C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801C6370;
extern s32 D_801C637C;
extern s32 D_801C6380;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80188BE8[])(s32 *);
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
extern s32 D_80188BBC[];
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
extern s32 D_801C6378;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80188E38[])(void);
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
extern char D_80188C58[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80188EDC[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80189030[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80188E4C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80189038[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80188E5C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80188E7C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80189040[])(void);
extern void func_8015ADB0(s32);
extern void func_8015AD78(s32 a0);
extern void func_8015ADB0(s32 arg0);
/* ==== end §8b carried decl layer ==== */


/* func_8015AE2C (ov_SC01_077_after, 562 ins, jtbl_801D8B54) — Phase 26 crack
 * Entity main-update dispatcher: 7-case switch (0/1/2/6 shared, 3/4/5 own, no default
 * block — out-of-range falls to the after-switch join), then movement/clamp/decay tail.
 * PIN-FREE. Offset-pure (s32 arg0 + raw offsets) — ×134 template-safe.
 *
 * match_one: MATCH (562 ins). rtu_match (whole-TU): MATCH (562 ins) — see func_8015AE2C.md
 * for the two TU-side prerequisites (engine_core.h DEFINE_func_8015BEC4 extern must drop its
 * `(void)` prototype, and the def must stay K&R) plus the jtbl_carve trailing-pad-word note.
 *
 * Signature: `s32` return + K&R def are REQUIRED by the TU, byte-neutral vs void/ANSI here
 * (both verified MATCH 562): engine_core.h's thunk DEFINE_func_8015BEC4 does
 * `return func_8015AE2C();` (s32, zero-arg call) — only an unprototyped K&R def coexists
 * with that call. §41d does not bite on this body (it has early `return;`s).
 *
 * jtbl_801D8B54 = 7 entries [0,1,2,6]->0x8015AEE4  [3]->0x8015AFE0  [4]->0x8015AFF0
 * [5]->0x8015B000, bound `sltiu 7`, default(out-of-range) -> 0x8015B044 (after-switch).
 * The raw dlabel's 8th word 0x00000000 is NOT a table entry: it is the original TU's
 * intra-TU `.align 3` pad between consecutive jtbls (B34/B54/B74 chain) — the compiled
 * object emits exactly 28 B; the pad must stay in the raw post-carve data piece.
 */
extern s32 func_80161A60(s32 a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_80149FB0(s32 a0);
extern s32 func_801619A4(s32 *a0);
extern s32 func_80149C08(s32 a0);
extern void func_801577C8();
extern s32 func_8015B6F4(s32 a0);
extern s32 func_8015B7B4(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8015B8F8(s32 *a0);
extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_801498E0(s32 *a0);
extern s32 func_80149954(s32 s0);
extern s32 func_80149A64(s32 *a0);
extern void func_800CCCC0(s32 a0);
extern int func_80155FF8(int arg, int a1);
extern s32 func_8015B858(u8 *a0);
extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147814(s32 a0, s32 a1);
extern s32 func_800CF8B4(void);
extern s32 func_801491C4(s32 a0);
extern int func_80148AFC(void *a0);
extern s32 func_80149184(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80147A30(s32 a0, s32 a1, s32 a2);
extern s32 func_80146E98(s32 a0);
extern void func_80146D90(s32 a0);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32 *a0);
extern s32 func_80172644(u8 *a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801541D8(u8 *a0, s32 a1, s32 a2);
extern s32 func_8014C050(s32 a0, s32 a1);
extern void func_800CCB78(s32 a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_80161488(void *a0);
extern void func_80146CA0(void *a0);
extern s32 func_8014A674(s32 *a0);
extern void func_8014E434(void);
extern void func_8015CC40(s32 *a0);
extern s32 func_8014A69C(s32 *a0);
extern void func_8014E6A0(void);
extern void func_8015CF8C(s32 *a0);
extern s32 func_801725A4(u8 *a0);

s32 func_8015AE2C(arg0)
s32 arg0;
{
    extern void (*D_80188EE8[])(void *);
    extern s16 D_801152A0;
    extern u8 D_800D4BE0[];
    extern s32 D_800D4E94;
    extern s32 D_800D4ED4;
    extern u8 D_800D4F8C[];
    extern s32 D_800D4A9C;
    extern s32 D_800D4B48;

    s32 flag;
    s32 r;
    s32 lim;
    s32 doit;
    s32 t;

    flag = 0;
    if ((func_80161A60(arg0) != 0) && (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) && (*(s32 *)(arg0 + 0x34) >= 0)) {
        flag = 1;
        if (*(s32 *)(arg0 + 0x5C) == 0) {
            *(s32 *)(arg0 + 0x58) = 0;
            *(s32 *)(arg0 + 0x54) = 0;
            *(s32 *)(arg0 + 0x50) = 0;
        }
        *(s32 *)(arg0 + 0x5C) = 1;
    } else {
        *(s32 *)(arg0 + 0x5C) = 0;
    }
    ((void (*)(s32))func_80149FB0)(arg0);
    if (*(s32 *)(arg0 + 0x1B0) == 0) {
        switch (((s32 (*)(s32))func_801619A4)(arg0)) {
        case 0:
        case 1:
        case 2:
        case 6:
            if (*(s32 *)(arg0 + 0xB4) == (s32)&(*(s32 *)&D_800D4BE0)) {
                if (func_80149C08(arg0) != 0) {
                    D_80188EE8[*(u16 *)arg0]((void *)arg0);
                    ((void (*)(s32))func_801577C8)(arg0);
                    return;
                }
            }
            if ((*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4E94) &&
                (*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4ED4) &&
                (*(s32 *)(arg0 + 0xB4) != (s32)&(*(s32 *)&D_800D4F8C))) {
                if (func_8015B6F4(arg0) == 0) {
                    ((void (*)(s32))func_8015B7B4)(arg0);
                }
            } else {
                if (*(u16 *)(arg0 + 0xB8) == 0x8000) {
                    func_80154A74(arg0, 0x22);
                    ((void (*)(s32))func_8015B8F8)(arg0);
                    *(u32 *)(arg0 + 0x44) &= ~2;
                    if (flag != 0) {
                        ((void (*)(s32, s32, s32, s32))func_80146994)(0x3B, arg0, 0, 0);
                    }
                }
            }
            break;
        case 3:
            ((void (*)(s32))func_801498E0)(arg0);
            break;
        case 4:
            ((void (*)(s32))func_80149954)(arg0);
            break;
        case 5:
            if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
                D_80188EE8[*(u16 *)arg0]((void *)arg0);
                func_800CCCC0(arg0);
                return;
            }
            break;
        }
    }
    if (*(u32 *)(arg0 + 0x44) & 2) {
        ((void (*)(s32, s32))func_80155FF8)(arg0, *(u8 *)(arg0 + 0x1AA));
    } else {
        if ((*(s32 *)(arg0 + 0x240) == 0) && (((s32 (*)(s32))func_8015B858)(arg0) != 0)) {
            *(s32 *)(arg0 + 0x240) += 1;
        }
        if ((*(s32 *)(arg0 + 0xB4) == (s32)&(*(s32 *)&D_800D4BE0)) && (*(u16 *)(arg0 + 0xB8) & 0x8000)) {
            ((void (*)(s32))func_8015B8F8)(arg0);
        } else if ((*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4A9C) ||
                   (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4B48)) {
            if (*(u16 *)(arg0 + 0xB8) & 0x8000) {
                if (*(s32 *)(arg0 + 0x34) >= 0) {
                    *(u16 *)(arg0 + 0xB8) += 1;
                }
            }
        }
    }
    if (*(u8 *)(arg0 + 0x1C6) != 0) {
        if (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) {
            func_80148038(arg0, 0xFFFE6000);
        } else {
            func_80148038(arg0, 0x1A000);
        }
        lim = 0x40000;
        if ((*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4E94) &&
            (*(s32 *)(arg0 + 0xB4) != (s32)&D_800D4ED4) &&
            (*(s32 *)(arg0 + 0xB4) != (s32)&(*(s32 *)&D_800D4F8C))) {
            lim = 0xC0000;
        }
        if (*(s32 *)(arg0 + 0x34) < -lim) {
            *(s32 *)(arg0 + 0x34) = -lim;
        } else if (lim < *(s32 *)(arg0 + 0x34)) {
            *(s32 *)(arg0 + 0x34) = lim;
        }
        func_80147460(arg0);
    } else {
        if (*(s32 *)(arg0 + 0x34) < 0) {
            if (((s32 (*)(s32))func_801487F4)(arg0) & 0x40) {
                func_80147814(arg0, 0xFFFF0000);
            }
            func_80147814(arg0, 0x10000);
        }
    }
    if (func_800CF8B4() != 0) {
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = ((*(u16 *)&D_801152A0) + func_801491C4(arg0)) & 0xFFF;
    }
    if (flag == 0) {
        if ((u8)((s32 (*)(s32))func_80148AFC)(arg0)) {
            (*(u16 *)&D_801152A0) = func_80149184(arg0);
            ((void (*)(s32, s32))func_80146E90)(arg0, 4);
            if (*(s32 *)(arg0 + 0x2C) > -0x80000) {
                *(s32 *)(arg0 + 0x2C) = -0x80000;
                func_80147A30(arg0, -0x10000, 0xBA000);
            } else {
                func_80147A30(arg0, -0x1000, 0xBA000);
            }
        } else {
            if (func_80146E98(arg0) != 0) {
                func_80146D90(arg0);
            }
        }
        func_80147A84(arg0);
        ((void (*)(s32))func_801473EC)(arg0);
        if (*(u8 *)(arg0 + 0x1C6) == 0) {
            func_80148038(arg0, 0x1A000);
            func_80147460(arg0);
        }
    } else {
        ((void (*)(s32))func_80172644)(arg0);
        if ((u8)((s32 (*)(s32))func_80148AFC)(arg0)) {
            (*(u16 *)&D_801152A0) = func_80149184(arg0);
            func_80146D90(arg0);
            func_80147AD4(arg0, 0, 0, 0xFFFF4000);
            *(s32 *)(arg0 + 0x50) += *(s32 *)(arg0 + 0x10);
            *(s32 *)(arg0 + 0x54) += *(s32 *)(arg0 + 0x14);
            *(s32 *)(arg0 + 0x58) += *(s32 *)(arg0 + 0x18);
            if (*(s32 *)(arg0 + 0x50) > 0xBA000) {
                *(s32 *)(arg0 + 0x50) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x50) < -0xBA000) {
                *(s32 *)(arg0 + 0x50) = -0xBA000;
            }
            if (*(s32 *)(arg0 + 0x54) > 0xBA000) {
                *(s32 *)(arg0 + 0x54) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x54) < -0xBA000) {
                *(s32 *)(arg0 + 0x54) = -0xBA000;
            }
            if (*(s32 *)(arg0 + 0x58) > 0xBA000) {
                *(s32 *)(arg0 + 0x58) = 0xBA000;
            } else if (*(s32 *)(arg0 + 0x58) < -0xBA000) {
                *(s32 *)(arg0 + 0x58) = -0xBA000;
            }
            *(s32 *)(arg0 + 0x10) = *(s32 *)(arg0 + 0x50);
            *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x54);
            *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0x58);
            ((void (*)(s32))func_801473EC)(arg0);
        } else {
            doit = 0;
            if (*(s32 *)(arg0 + 0x50) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x50) >= 0) {
                    *(s32 *)(arg0 + 0x50) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x50) < 0) {
                        *(s32 *)(arg0 + 0x50) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x50) += 0x8000;
                    if (*(s32 *)(arg0 + 0x50) >= 0) {
                        *(s32 *)(arg0 + 0x50) = 0;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x54) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x54) >= 0) {
                    *(s32 *)(arg0 + 0x54) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x54) < 0) {
                        *(s32 *)(arg0 + 0x54) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x54) += 0x8000;
                    if (*(s32 *)(arg0 + 0x54) >= 0) {
                        *(s32 *)(arg0 + 0x54) = 0;
                    }
                }
            }
            if (*(s32 *)(arg0 + 0x58) != 0) {
                doit = 1;
                if (*(s32 *)(arg0 + 0x58) >= 0) {
                    *(s32 *)(arg0 + 0x58) -= 0x8000;
                    if (*(s32 *)(arg0 + 0x58) < 0) {
                        *(s32 *)(arg0 + 0x58) = 0;
                    }
                } else {
                    *(s32 *)(arg0 + 0x58) += 0x8000;
                    if (*(s32 *)(arg0 + 0x58) >= 0) {
                        *(s32 *)(arg0 + 0x58) = 0;
                    }
                }
            }
            if (doit != 0) {
                *(s32 *)(arg0 + 0x10) = *(s32 *)(arg0 + 0x50);
                *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x54);
                *(s32 *)(arg0 + 0x18) = *(s32 *)(arg0 + 0x58);
                ((void (*)(s32))func_801473EC)(arg0);
            }
            if (!(*(u32 *)(arg0 + 0x44) & 2)) {
                ((void (*)(s32, s32, s32))func_801541D8)(arg0, 0xF, 0x12);
            }
        }
        t = func_8014C050(arg0, 0x3B);
        if (t != 0) {
            func_800CCB78(t);
        }
        if ((*(u16 *)(arg0 + 0x1C8) & 0x1F) == 0) {
            ((void (*)(s32, s32, s32, s32))func_80146994)(0x3C, arg0, 0, 0);
        }
    }
    if (*(s32 *)(arg0 + 0x1B0) != 0) {
        if (*(s32 *)(arg0 + 0x1B0) == 1) {
            func_80154A74(arg0, 0x22);
            func_80154150(arg0, 0xF);
        } else {
            ((void (*)(s32, s32))func_80154274)(arg0, *(s32 *)(arg0 + 0x1B4));
        }
    }
    r = ((s32 (*)(s32))func_80161488)(arg0);
    if (r & 5) {
        *(u32 *)(arg0 + 0x44) &= ~2;
        if (*(s32 *)(arg0 + 0xB4) == (s32)&D_800D4A9C) {
            func_80154150(arg0, 0xE);
        } else {
            func_80154150(arg0, 0x10);
        }
        ((void (*)(s32))func_80146CA0)(arg0);
    }
    if (r == 0) {
        if ((((s32 (*)(s32))func_8014A674)(arg0) != 0) && (((s32 (*)(s32))func_8014E434)(arg0) != 0)) {
            D_80188EE8[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8015CC40)(arg0);
        } else if ((((s32 (*)(s32))func_8014A69C)(arg0) != 0) && (((s32 (*)(s32))func_8014E6A0)(arg0) != 0)) {
            D_80188EE8[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_8015CF8C)(arg0);
        } else {
            ((void (*)(s32))func_801725A4)(arg0);
        }
    }
}

DEFINE_func_8015B6F4()  /* dedup: shared engine-core @0x8015B6F4 (src/shared) */

DEFINE_func_8015B7B4()  /* dedup: shared engine-core @0x8015B7B4 (src/shared) */

DEFINE_func_8015B858()  /* dedup: shared engine-core @0x8015B858 (src/shared) */

DEFINE_func_8015B8F8()  /* dedup: shared engine-core @0x8015B8F8 (src/shared) */

extern s32 func_8015AE2C();

// @class: plumbing
// @stuck: none — MATCH (271/271, pin-free, zero asm). The ONLY residual is DEF-SIDE plumbing, and it is now named exactly: the in-TU instantiation `DEFINE_func_8015BEE4()` (engine_core.h:1851-1855) expands to `extern s32 func_8015B950(void);` INSIDE ov_SC01_077_jr_8015AE2C.c, ~14 lines BELOW this definition, so the 1-param def collides with a `(void)` prototype -> `conflicting types for func_8015B950` (.run/bank_func_8015B950.log). §73 PARAMS axis / T0. Surgical fix = §65b de-macroize that ONE instantiation (blast radius: this TU); the fleet-wide `(void)`->`()` header edit is §63 and must be R22-validated.
/* func_8015B950 (ov_SC01_077_jr_8015AE2C, 271 ins, jtbl_801D8B74) — SESSION-21 re-verified
 *
 * ── ROUND-2 INDEPENDENT RE-VERIFICATION (2026-07-27, fresh agent, §88e discipline) ─────────────
 *   match_one : MATCH (271 ins) against the CURRENT tree — §87 staleness re-checked today.
 *   .text size: compiled .text = 0x43C = 1084 B = 271 ins, EXACTLY the target's declared 0x43C
 *               ("nonmatching func_8015B950, 0x43C"). So this is NOT a §83a length drift hiding
 *               behind a zero count — the count is over equal-length streams.
 *   jtbl      : RE-DECODED MECHANICALLY, not inherited. Compiled .rodata = 0x1C = 28 B = 7 words,
 *               7x R_MIPS_32 -> .text with implicit addends [58,58,58,E0,F0,100,58]; +0x8015B950
 *               = [8015B9A8, 8015B9A8, 8015B9A8, 8015BA30, 8015BA40, 8015BA50, 8015B9A8].
 *               Diffed word-for-word against asm/ov_SC01_077/data/tail14.data.s:15-23 — 7/7 identical.
 *   symcheck  : SYMS-DIFF target=35 draft=34, sole MISSING = jtbl_801D8B74. This is the §81 jr
 *               FALSE POSITIVE, re-confirmed here by reading the relocs: gcc emits its OWN table and
 *               references it with R_MIPS_HI16/LO16 against the SECTION `.rodata` (t.o +0x40/+0x48),
 *               so the splat's dlabel NAME can never appear in the draft object's relocation set.
 *               Nothing is dropped and nothing is invented: the draft's other 34 symbols are exactly
 *               the target's other 34.
 *   FAMILY    : the x138 remap is clean and §84-safe. Every sibling is 271 ins with an IDENTICAL
 *               callee set; only THREE names vary per overlay — the two data labels and the jtbl:
 *                 ov_SC01_077  D_80188E7C / D_80188EE8 / jtbl_801D8B74
 *                 ov_SC03_099  D_80185A50 / D_80185ABC / jtbl_801BD898
 *                 ov_SC06_008  D_80187E44 / D_80187EB0 / jtbl_801A8734
 *               The pair is always +0x6C apart, and NO literal in this draft encodes that distance
 *               (both labels are referenced by name), so there is no §84 derived-offset hazard.
 *               D_8011F9C4 is fleet-constant (main-EXE data) and must NOT be remapped.
 *
 * match_one: MATCH (271 ins) against the CURRENT tree (§87 staleness re-checked, 2026-07-27).
 * PIN-FREE, zero asm, offset-pure (s32 arg0 + raw offsets) — x138 template-safe.
 * Provenance: this is the Phase-26 crack (.run/phase26-cracks/func_8015B950.c) re-gated verbatim,
 * with ONE deliberate change: the definition's return type void -> s32.
 *   - `void func_8015B950(s32 arg0)` : MATCH (271 ins)   [the Phase-26 form]
 *   - `s32  func_8015B950(s32 arg0)` : MATCH (271 ins)   [shipped — §3a-1 void->s32 is byte-neutral]
 * The fleet/engine_core.h canonical decl is `extern s32 func_8015B950(void);` (engine_core.h:1852),
 * and the last bank attempt (.run/bank_func_8015B950.log) died on `conflicting types for
 * func_8015B950`. Shipping the s32 return kills the §73 RETURN axis for free and leaves only the
 * cheap T0 PARAMS axis for the ladder (fix_header_decl.py / --fix-def-sig / cast_call_sites).
 * Both forms are byte-identical, so the orchestrator may swap the return type back at zero cost.
 *
 * SYMBOLS (§58 rules 1/2 — all splat spellings, all verified present):
 *   D_80188EE8    asm/ov_SC01_077/data/tail.data.s:4355 (the state-handler vtable)
 *   D_80188E7C    asm/ov_SC01_077/data/tail.data.s:4293
 *   D_8011F9C4    main-EXE data; spelled `extern s32 D_8011F9C4;` in 5+ already-banked TUs
 *   jtbl_801D8B74 asm/ov_SC01_077/data/tail14.data.s:15 (compiler jump table — not named in C)
 *
 * JTBL VERIFIED (§8a gate): compiled .rodata = exactly 0x1C B / 7 words, 7x R_MIPS_32 .text with
 * addends [0x58,0x58,0x58,0xE0,0xF0,0x100,0x58] -> +0x8015B950 = [B9A8,B9A8,B9A8,BA30,BA40,BA50,
 * B9A8] == the original words at 0x801D8B74..0x801D8B8C. Bound `sltiu $v0,$v1,0x7` matches.
 * The raw dlabel's 8th word 0x00000000 is NOT an entry — it is the intra-TU `.align 3` pad of the
 * B34/B54/B74 jtbl chain; the object can never emit it (maspsx drops .align), so it must stay in
 * the post-carve RAW data piece (the §53/§62/§81 carve chain applies at bank time).
 *
 * Same family as the TU's own already-matched func_8015AE2C: 7-case switch on ((s32 (*)(s32))func_801619A4)()
 * (0/1/2/6 shared, 3/4/5 own, no default block — out-of-range and every `break` fall to the
 * after-switch join), then a chain of "state handler" tests, each dispatching
 * D_80188EE8[*(u16*)arg0](arg0) and returning.
 *
 * THREE LEVERS (draft -> MATCH in 3 compiles):
 *
 * 1. PROLOGUE CONSTANT = an INITIALIZED LOCAL, not a literal in the compare.
 *    Target opens with `lui $s2, 0xFFF5` in the *prologue*, used once ~200 ins later in
 *    `slt $v0,$s2,$s1`. No gcc-2.7.2 pass hoists a (set reg const_int) across basic blocks
 *    (loop.c needs a loop; cse/combine/sched never move insns between BBs) — so the insn must
 *    have been EMITTED in the first BB, i.e. the constant is a local initialized at the top of
 *    the function. cse then cannot fold it back into the compare: the `slt` operand predicate is
 *    `arith_operand`, which rejects a CONST_INT wider than 16 bits, so validate_change fails and
 *    the pseudo survives. Its live range spans every call -> global.c gives it a callee-saved reg.
 *    Writing `z > -0xB0000` inline instead emits the `lui` into the branch delay slot next to the
 *    compare (caller-saved $v0) and the function is 1 insn short. => `s32 lim = -0xB0000;` at top.
 *
 * 2. `lh` vs `lhu`: a short->short copy is a pure HImode move and gcc emits `lhu`. The target's
 *    `lh $v0,0x26($s0)` means the value passed through an SImode (int) temp: expand makes
 *    (set (reg:SI) (sign_extend (mem:HI))) + (set (mem:HI) (subreg:HI ...)), and combine cannot
 *    merge them (the merged form is mem<-mem, which no movhi accepts) so the sign-extending load
 *    survives. => route both halfword copies through the `s32 t` temp.
 *
 * 3. THE `goto` LAYOUT — dodging jump.c's store-flag conversion (jump.c:1005-1065).
 *    An if/else chain writing 0/1 into `doit` makes gcc collapse the last pair into
 *    `sltiu $v0,$v0,1`. jump.c fires that conversion when the insn immediately after a
 *    conditional jump is a lone `SET pseudo, CONST_INT` whose following simplejump targets the
 *    SAME label as the branch (jump.c:1038 `reallabelprev == temp || ... JUMP_LABEL(temp4) ==
 *    JUMP_LABEL(insn)`) — exactly the shape of `if (c) x=0; else x=1;`.
 *    The target instead cross-jumps ALL the `doit=0` exits into ONE shared block placed after the
 *    `doit=1` fall-through; reorg's fill_slots_from_thread then COPIES that single set into all
 *    three branch delay slots and redirects each branch past it (which is why `addu $v0,$zero,
 *    $zero` appears 3x in delay slots and the shared block vanishes). A `goto zero;` / `goto one;`
 *    chain expresses that layout directly, and each conditional jump is then followed by a
 *    compare/call rather than a lone const set, so the store-flag conversion never triggers.
 *    GENERAL RULE: multiple predicates that all assign the SAME constant to one flag => write
 *    them as `goto` to a shared assignment, never as an if/else ladder.
 */
extern s32 D_8011F9C4;
extern s32 D_80188E7C;

extern s32 func_80161B18(void);
extern s32 func_801619A4(s32*);
extern s32 func_80149AA8(s32*);
extern void func_80149AD4(s32*);
extern s32 func_80149B54(s32*);
extern void func_80149BAC(s32*);
extern s32 func_801498E0(s32*);
extern s32 func_80149954(s32);
extern s32 func_80149A64(s32*);
extern void func_800CCCC0(s32 a0);
extern s32 func_80149CD4(s32 a0);
extern void func_8015E880(s32*);
extern s32 func_80149744(struct S_80149744*);
extern void func_80149788(void);
extern s32 func_801496D4(void*);
extern void func_80149704(void);
extern int func_80148AFC(void*);
extern void func_80146D90(s32 a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_801541D8(u8*, s32, s32);
extern s32 func_801488A8(u8*);
extern void func_80147078(s32*, s16);
extern void func_8015A264(void*);
extern s32 func_80013294(void*, void*);
extern void func_80159B70(void*);
extern s32 func_8016F1AC(void);
extern s32 func_80029178(s32 a0);
extern void func_80146DB8(s32*, s32*);
extern s32 func_80161CD0(s32, s32);
extern s32 func_80161208(s32 a0);
extern s32 func_801725A4(u8*);

s32 func_8015B950(s32 arg0)
{

    extern void (*D_80188EE8[])(void *);
    s16 sp10[4];
    s16 sp18[4];
    s32 t;
    s32 z;
    s32 doit;
    s32 lim = -0xB0000;

    if (func_80161B18() != 0) {
        return;
    }
    switch (((s32 (*)(s32))func_801619A4)(arg0)) {
    case 0:
    case 1:
    case 2:
    case 6:
        if (((s32 (*)(s32))func_80149AA8)(arg0) != 0) {
            D_80188EE8[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149AD4)(arg0);
            return;
        }
        if (((s32 (*)(s32))func_80149B54)(arg0) != 0) {
            D_80188EE8[*(u16 *)arg0]((void *)arg0);
            ((void (*)(s32))func_80149BAC)(arg0);
            return;
        }
        break;
    case 3:
        ((void (*)(s32))func_801498E0)(arg0);
        break;
    case 4:
        ((void (*)(s32))func_80149954)(arg0);
        break;
    case 5:
        if (((s32 (*)(s32))func_80149A64)(arg0) != 0) {
            D_80188EE8[*(u16 *)arg0]((void *)arg0);
            func_800CCCC0(arg0);
            return;
        }
        break;
    }
    if (func_80149CD4(arg0) != 0) {
        D_80188EE8[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_8015E880)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_80149744)(arg0) != 0) {
        D_80188EE8[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149788)(arg0);
        return;
    }
    if (((s32 (*)(s32))func_801496D4)(arg0) != 0) {
        D_80188EE8[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32))func_80149704)(arg0);
        if (((u8)((s32 (*)(s32))func_80148AFC)(arg0)) == 0) {
            func_80146D90(arg0);
        }
        if ((*(s32 *)(arg0 + 0x24) | *(s32 *)(arg0 + 0x2C)) != 0) {
            func_80154150(arg0, 0xF);
        } else {
            ((void (*)(s32, s32, s32))func_801541D8)(arg0, 0xD, 6);
        }
        *(s32 *)(arg0 + 0x238) = 1;
        return;
    }
    if (((s32 (*)(s32))func_801488A8)(arg0) != 0) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = 0;
        t = *(s16 *)(arg0 + 0x26);
        sp18[0] = t;
        sp18[1] = 0;
        t = *(s16 *)(arg0 + 0x2E);
        sp18[2] = t;
        D_80188EE8[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32, s32))func_80147078)(arg0, 1);
        ((void (*)(s32))func_8015A264)(arg0);
        t = -(((s32 (*)(s16 *, s16 *))func_80013294)(sp10, sp18) << 0x10);
        if (t < *(s32 *)(arg0 + 0x2C)) {
            *(s32 *)(arg0 + 0x2C) = t;
        }
        return;
    }
    if (*(u16 *)(arg0 + 0xB8) == 0x8000) {
        D_80188EE8[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32, s32))func_80147078)(arg0, 0);
        ((void (*)(s32))func_80159B70)(arg0);
        return;
    }
    z = *(s32 *)(arg0 + 0x2C);
    if (func_8016F1AC() != 0) {
        goto zero;
    }
    if (z <= lim) {
        goto one;
    }
    if (D_8011F9C4 == 0) {
        goto zero;
    }
    if (((u8)func_80029178(0x21)) != 0) {
        goto zero;
    }
one:
    doit = 1;
    goto join;
zero:
    doit = 0;
join:
    if (doit != 0) {
        D_80188EE8[*(u16 *)arg0]((void *)arg0);
        ((void (*)(s32, s32))func_80147078)(arg0, 0);
        ((void (*)(s32))func_80159B70)(arg0);
        func_80154150(arg0, 9);
        ((void (*)(s32, s32 *))func_80146DB8)(arg0, &D_80188E7C);
        ((void (*)(s32, s32))func_80161CD0)(arg0, *(u16 *)(arg0 + 0x16E));
        return;
    }
    if (func_80161208(arg0) == 0) {
        ((void (*)(s32))func_801725A4)(arg0);
    }
}

DEFINE_func_8015BD8C()  /* dedup: shared engine-core @0x8015BD8C (src/shared) */

DEFINE_func_8015BDD0()  /* dedup: shared engine-core @0x8015BDD0 (src/shared) */

DEFINE_func_8015BE04()  /* dedup: shared engine-core @0x8015BE04 (src/shared) */



void func_8015BE38(struct Obj *a0) {

    extern void (*D_8018905C[])(void);
    D_8018905C[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8015BE74()  /* dedup: shared engine-core @0x8015BE74 (src/shared) */

DEFINE_func_8015BE94()  /* dedup: shared engine-core @0x8015BE94 (src/shared) */

DEFINE_func_8015BEC4()  /* dedup: shared engine-core @0x8015BEC4 (src/shared) */

DEFINE_func_8015BEE4()  /* dedup: shared engine-core @0x8015BEE4 (src/shared) */

DEFINE_func_8015BF04()  /* dedup: shared engine-core @0x8015BF04 (src/shared) */

DEFINE_func_8015BF48()  /* dedup: shared engine-core @0x8015BF48 (src/shared) */

DEFINE_func_8015BF7C()  /* dedup: shared engine-core @0x8015BF7C (src/shared) */

DEFINE_func_8015BFB0()  /* dedup: shared engine-core @0x8015BFB0 (src/shared) */


extern void (*D_80189068[])(void);

void func_8015BFF4(void *a0) {
    D_80189068[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC01_084/nonmatchings/ov_SC01_084_jr_8015AE2C", func_8015C030);

DEFINE_func_8015C08C()  /* dedup: shared engine-core @0x8015C08C (src/shared) */

DEFINE_func_8015C0C4()  /* dedup: shared engine-core @0x8015C0C4 (src/shared) */

#include "common.h"



s32 func_8015C128(s32 param_1) {
    extern void func_8015C6E0(int);
    extern void (*D_80188EE8[])(int);

    int sp10[3];
    int sp20[3];
    int temp_s0;
    int temp_v0;

    ((void(*)())func_80149FB0)();
    if (((int(*)(int))func_80148AFC)(((int)param_1)) & 0xFF) {
        sp10[0] = 0;
        sp10[1] = 0;
        sp10[2] = -0x4000;
        ((void(*)(int, int *, int *))func_8001382C)(*(short *)(*(int *)(((int)param_1) + 0x20) + 0x12), sp10, sp20);
        *(int *)(((int)param_1) + 0x234) += sp20[0];
        *(int *)(((int)param_1) + 0x238) += sp20[1];
        *(int *)(((int)param_1) + 0x23C) += sp20[2];
    }
    ((void(*)(int, int *, int *))func_8001382C)((short)(-*(unsigned short *)(*(int *)(((int)param_1) + 0x20) + 0x12)),
                  (int *)(((int)param_1) + 0x234), sp20);
    ((void(*)(int, int *))func_80146DB8)(((int)param_1), sp20);
    func_80147A84(((int)param_1));
    ((void(*)(int))func_801473EC)(((int)param_1));
    if (!(D_800B99DA & 3)) {
        ((void(*)(int, int))func_8014C010)(((int)param_1), 1);
        ((void(*)(int))func_80147324)(0x65F);
    }
    if (((int(*)(int))func_8014D738)(((int)param_1)) != 0) {
        D_80188EE8[*(u16 *)((int)param_1)](((int)param_1));
        func_8015C6E0(((int)param_1));
        return;
    }
    temp_s0 = ((int(*)(int))func_8014CC28)(((int)param_1));
    temp_v0 = ((int(*)(int))func_8014F3E8)(((int)param_1));
    if (temp_v0 != 0) {
        if ((temp_v0 & 0xFF00) != 0x4000) {
            ((void(*)(int, int))func_80146E90)(((int)param_1), 6);
            ((void(*)(int))func_80146CA0)(((int)param_1));
            return;
        }
        if ((temp_v0 & 0x4000) && ((int(*)(int))func_80146E98)(((int)param_1)) != 0) {
            ((void(*)(int, int))func_80147078)(((int)param_1), 4);
            ((void(*)(int))func_8015C0C4)(((int)param_1));
        }
    } else if (temp_s0 == 0) {
        D_80188EE8[*(u16 *)((int)param_1)](((int)param_1));
        ((void(*)(int, int))func_80147078)(((int)param_1), 3);
        ((void(*)(int))func_8015BE94)(((int)param_1));
    }
}
