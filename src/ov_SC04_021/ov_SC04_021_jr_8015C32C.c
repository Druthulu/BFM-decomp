#include "common.h"
#include "../shared/engine_prelude.h"


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
extern u8 D_801817B0;
extern u8 D_80181720;
extern u8 D_801816FC;
extern u8 D_801816D8;
extern u8 D_8018178C;
extern u8 D_80181768;
extern u8 D_80181744;
extern u8 D_801816B4;
extern void func_80145934(void);
extern u8 D_80181840;
extern u8 D_8018181C;
extern u8 D_801817F8;
extern u8 D_801817D4;
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
extern unsigned char D_80180C38[];
extern unsigned char D_80180C68[];
extern unsigned char D_80180CB8[];
extern unsigned char D_80180CE8[];
extern unsigned char D_80180D18[];
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
extern void (*D_80180D68[])(void *);
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
extern s32 D_8011F754;
extern u8 * func_801468C8(s32 arg0, u8 arg1);
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
extern void func_80147364(u16 param_1, u16 param_2);
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
extern void func_80147364(u16 param_1, u16 param_2);
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
extern s32 D_80180E30[];
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
extern u8 D_80180EB8[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80180EC0;
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
extern int D_8018E810;
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
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern s32 D_8018E814;
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
extern s32 D_80180EF0;
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
extern void (*D_80180F98[])(void);
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
extern void (*D_80180FBC[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80180FAC;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80180FD0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80180FDC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80180FEC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80181004[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80180FF4;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80181018[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80181034[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80181024;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80181048[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018105C[])(void);
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
extern s32 D_80181070;
extern void (*D_80181098[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80181078;
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
extern int (*D_801810E4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801810E8[])(void);
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
extern s32 func_8014C568(s16 *a0, s16 *a1);
extern void func_801567BC(s32 a0);
extern B8 D_80128120[];
extern B8 D_80128138[];
extern S8 D_80126AF0[];
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern unsigned char D_8011520C[];
extern unsigned short D_8018154C[];
extern void func_80156A1C(s32 param_1, s32 param_2);
extern s32 D_801150E0[];
extern void func_80156A88(s32 a0, s32 a1);
extern void func_80156B74(s32 param_1, u32 param_2, u8 *param_3);
extern void func_80156ECC(int param_1, int param_2, int param_3, int param_4, int param_5);
extern void func_80156FA8(s16 *param_1, s16 *param_2, s16 *param_3);
extern void func_80157158(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
extern u32 func_801571C4(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801575E4(void *a0);
extern void func_801574DC(s32 *a0);
extern void func_80157544(void *a0);
extern void (*D_8018155C[])(void);
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
extern int D_8018E848;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80181584[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80181564;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80181574;
extern void func_8015795C(int param_1);
extern void func_80161D20(int param_1, u32 param_2);
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
extern void (*D_801815C4[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_801815CC[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80181598;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_801815D8[])(void);
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
extern u8 D_801815A8;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_8018E850;
extern s32 D_8018E85C;
extern s32 D_8018E860;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80181614[])(s32 *);
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
extern s32 D_801815E8[];
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
extern s32 D_8018E858;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80181864[])(void);
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
extern char D_80181684[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80181908[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80181A5C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80181878;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80181A64[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80181888;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern void func_80161CD0(int param_1, unsigned int param_2);
extern M2C_UNK D_801818A8;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80181A6C[])(void);
extern void func_8015ADB0(s32);
extern void func_8015AD78(s32 a0);
extern void func_8015ADB0(s32 arg0);
extern s32 func_80161A60(s32 a0);
extern s32 func_801619A4(s32 *a0);
extern s32 func_80149C08(s32 a0);
extern s32 func_8015B6F4(s32 a0);
extern s32 func_8015B7B4(s32 a0);
extern void func_8015B8F8(s32 *a0);
extern void func_800CCCC0(s32 a0);
extern s32 func_8015B858(u8 *a0);
extern s32 func_800CF8B4(void);
extern void func_80147A84(s32 a0);
extern s32 func_80172644(u8 *a0);
extern void func_800CCB78(s32 a0);
extern s32 func_80161488(void *a0);
extern void func_8015CC40(s32 *a0);
extern void func_8015CF8C(s32 *a0);
extern s32 func_8015AE2C();
extern s32 D_800D4A9C;
extern int func_8015B6F4(int param_1);
extern u8 D_800D4F8C[];
extern u8 D_800D4BE0[];
extern s32 func_8014A51C(void);
extern s32 D_800D4B48;
extern void func_8015BD8C(s32 *a0);
extern s32 func_8015BE94();
extern void func_8015BE38(struct Obj *a0);
extern s32 func_8015BE74(void);
extern void func_80161124(void *a0);
extern s32 func_8015BE94(s32 *a0);
extern s32 func_8015BEC4(void);
extern s32 func_8015B950(s32 arg0);
extern s32 func_8015BEE4(void);
extern void func_8015BF04(s32 *a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015BFF4(void *a0);
extern void func_8015BF7C(s32 *a0);
extern void func_8015C030(s32 *a0, s32 a1);
extern void func_8015BFB0(s32 *a0, s32 a1);
extern void (*D_80181A94[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
/* ==== end §8b carried decl layer ==== */




extern u16 D_800B99DA;

extern s32 func_80149FB0(s32 a0);
extern s32 func_801496D4(void*);
extern void func_80149704(void);
extern s32 func_801619A4(s32*);
extern s32 func_80149AA8(s32*);
extern void func_80149AD4(s32*);
extern s32 func_80149B54(s32*);
extern void func_80149BAC(s32*);
extern s32 func_801498E0(s32*);
extern s32 func_80149954(s32);
extern s32 func_80149A64(s32*);
extern void func_800CCCC0(s32 a0);
extern int func_80148AFC(void *a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32*);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_80147324(s32 a0);
extern void func_8014D738(void);
extern void func_8014CC28(s32);
extern s32 func_8014F3E8(s32);
extern s32 func_80146E98(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_80159BE4(s32 a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015C6E0(s32*);

#include "../shared/ov/func_8015C32C__11445a3f.h"


#include "../shared/ov/func_8015C6A4.h"

#include "../shared/ov/func_8015C6AC.h"

#include "../shared/ov/func_8015C6E0.h"


extern void (*D_80181AA0[])(void);

void func_8015C714(void *a0) {
    D_80181AA0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015C750.h"

#include "../shared/ov/func_8015C788.h"


// @class: struct
// @unstuck(P36): none — MATCH (match_one 88/88); fn-ptr-array dispatch, top-level if/else needed branch-polarity invert (small block falls through, big block at L854)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_801496D4(void *a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80149704(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80148AAC(u8 *a0);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);
extern void func_8014C010(s32 a0, s32 a1);


#include "../shared/ov/func_8015C7E4__61b9597c.h"




// @class: struct
// @unstuck(P36): none — dispatch + control flow on a single callee-saved param; expect MATCH

extern s32 func_80149FB0(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161240(void *a0);
extern s32 func_80146E98(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80161C24(s32, s32);


#include "../shared/ov/func_8015C944__afbe8a9a.h"



// @class: schedule
// @unstuck(P36): none — MATCH (goto forces the func_80161240 block to the function tail; bnez-to-end layout vs early-return fall-through)


extern s32 func_80149FB0(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_801496D4(void *a0);
extern u16 func_801487F4(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern void func_80148AAC(u8 *a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C98(s32 *a0, s16 a1);
extern void func_80161240(void *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80149704(void);


#include "../shared/ov/func_8015CA28__28f5a61f.h"


#include "../shared/ov/func_8015CB94.h"

#include "../shared/ov/func_8015CBCC.h"

#include "../shared/ov/func_8015CBD4.h"

#include "../shared/ov/func_8015CBDC.h"

#include "../shared/ov/func_8015CBE4.h"

#include "../shared/ov/func_8015CBEC.h"

#include "../shared/ov/func_8015CBF4.h"

#include "../shared/ov/func_8015CBFC.h"

#include "../shared/ov/func_8015CC04.h"

#include "../shared/ov/func_8015CC0C.h"

#include "../shared/ov/func_8015CC40.h"



void func_8015CC74(s32 *a0) {

    extern void (*D_80181AB0[])(void);
    D_80181AB0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015CCB0.h"

#include "../shared/ov/func_8015CCD0.h"

#define NULL 0





#include "../shared/ov/func_8015CD20__d8c58cdb.h"



#include "../shared/ov/func_8015CF24.h"

#include "../shared/ov/func_8015CF58.h"

#include "../shared/ov/func_8015CF8C.h"



void func_8015CFC0(s32 *a0) {

    extern void (*D_80181AE8[])(void);
    D_80181AE8[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015CFFC.h"

// @class: regalloc-order
// @unstuck(P36): none — MATCH (uVar1 pinned $s3, uVar5 pinned $s1; param_1->s2, iVar4->s0 fall out)


#include "../shared/ov/func_8015D01C__e5d73af4.h"





// @class: struct
// @unstuck(P36): none — MATCH (pending gate)

extern s32 func_80149FB0(s32 a0);
extern void func_8014FA04(s32 a0);
extern void func_8014E6A0(void);
extern void (*D_80181914[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_801725F4(u8 *a0);
extern void func_80146CA0(void *a0);

#include "../shared/ov/func_8015D104__ae9e650f.h"



extern s32 func_80149FB0(s32);
extern void func_80147324(s32 a0);
extern u16  func_80148800(s32 *a0);
extern void func_80149724(void);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146DB8(s32*, s32*);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_8014FA04(s32);
extern void func_8014E6A0(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void*);
extern void func_8015D380(s32);
extern s32  func_801725F4(u8 *a0);

extern void (*D_80181914[])(void*);

#include "../shared/ov/func_8015D1B8__43d53584.h"



// @class: regalloc-order
// @unstuck(P36): pinning a0->$s1 and buffer-ptr->$s0; body copy already matches
extern void func_80013F3C(s32 a0);
extern void func_80012558(s32 a0, s32 a1);
extern void func_800126C4(s32 a0, s32 a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void *memcpy(void *dst, const void *src, u32 n);

extern s32 D_80181B44;

#include "../shared/ov/func_8015D380__95fbfaa8.h"




// @class: plumbing
// @unstuck(P36): none — MATCH

extern unsigned char D_80180C28[];

extern void func_801553C0(s32 a0);
extern void func_80154A74(s32 a0, s32 a1);

#include "../shared/ov/func_8015D414__15eb5ba2.h"


#include "../shared/ov/func_8015D480.h"

#include "../shared/ov/func_8015D4B4.h"



s32 func_8015D4E8(s16 *a0) {

    extern void (*D_80181B4C[])(void);
    D_80181B4C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015D524.h"

#include "../shared/ov/func_8015D544.h"

#include "../shared/ov/func_8015D57C.h"


// @class: loose-typing
// @unstuck(P36): none — MATCH (field 0xb8 compared as u16 == 0x8000, not s16 == -0x8000)

extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern void func_80154A74(int, int);
extern s32 func_80161208();
extern void func_80154150(int, int);
extern void func_80146CA0(void *a0);
extern void func_80149374(int, int);

extern unsigned char D_80181B58[];

#include "../shared/ov/func_8015D5E8__5fff3768.h"



extern int func_80148AFC(void*);
extern s32 func_80161B18(void *);
extern s32 func_80161B84(void *);
extern u16 func_80148800(s32*);
extern u8 func_8014BEF8(void);
extern s32 func_80165624(s32);
extern s32 func_801488A8(u8*);
extern void func_8014D738(void);
extern s32 func_80161208();
extern void func_80154A74(s32, s32);
extern void func_8015DAC4(s32*);
extern void func_8015DE24(s32*);
extern void func_8015DA5C(s32);
extern void func_8015F948(s32*);
extern void func_800CAF14(void *);
extern void func_80154150(s32, s32);
extern void func_80146DB8(s32*, s32*);
extern void func_80147A84(s32);
extern void func_801473EC(s32*);
extern void func_80149374(s32, s32);
extern void func_80147078(s32*, s16);
extern void func_80159B70(void *);
extern void func_8015C714(void *);
extern void func_801483E8(void);

extern void (*D_80181914[])(void *);
extern u8 D_80078E78[];
extern u8 D_80181B58[];

#include "../shared/ov/func_8015D738__6e729a10.h"


#include "../shared/ov/func_8015DA5C.h"

#include "../shared/ov/func_8015DA90.h"

#include "../shared/ov/func_8015DAC4.h"



void func_8015DAF8(s32 *a0) {

    extern void (*D_80181B8C[])(void);
    D_80181B8C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015DB34.h"

#include "../shared/ov/func_8015DB6C.h"


// @class: struct
// @unstuck(P36): none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern void (*D_80181914[])(void *);
extern int func_8015DD74(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015DCB8(s32 a0);

#include "../shared/ov/func_8015DBD4__83daff82.h"


#include "../shared/ov/func_8015DC84.h"


// @class: other
// @unstuck(P36): none — MATCH (proxy gate)

extern s8 D_80181B94[];
extern void func_80149374(s32 a0, s32 a1);

void func_8015DCB8(s32 param_1) {
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_80181B94[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_80181B94[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_80181B94[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


#include "../shared/ov/func_8015DD74.h"

#include "../shared/ov/func_8015DDF0.h"

#include "../shared/ov/func_8015DE24.h"



void func_8015DE58(s32 *a0) {

    extern void (*D_80181BAC[])(void);
    D_80181BAC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015DE94.h"

#include "../shared/ov/func_8015DECC.h"


// @class: struct
// @unstuck(P36): none — MATCH (mirrors byte-matched func_8015F89C/func_8015F9A4 in same overlay)

extern void (*D_80181914[])(void *);
extern int func_8015E0D4(int);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();
extern void func_8015E018(s32 a0);

#include "../shared/ov/func_8015DF34__ad0c1369.h"


#include "../shared/ov/func_8015DFE4.h"


// @class: other
// @unstuck(P36): none — MATCH (proxy gate)

extern s8 D_80181B94[];
extern void func_80149374(s32 a0, s32 a1);

void func_8015E018(s32 param_1) {
    s32 iVar1;
    s32 iVar2;

    iVar2 = *(s32 *)(param_1 + 0x178);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 6) = (s16)D_80181B94[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xc);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 10) = (s16)D_80181B94[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0xe);

    iVar1 = *(s32 *)(param_1 + 0x234);
    *(s32 *)(param_1 + 0x234) = iVar1 + 1;
    *(s16 *)(iVar2 + 0xe) = (s16)D_80181B94[iVar1] + *(s16 *)(*(s32 *)(iVar2 + 0x78) + 0x10);

    func_80149374(param_1, iVar2 + 4);
}


#include "../shared/ov/func_8015E0D4.h"

#include "../shared/ov/func_8015E150.h"

#include "../shared/ov/func_8015E184.h"



s32 func_8015E1B8(s32 a0) {

    extern void (*D_80181BCC[])(void);
    D_80181BCC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015E1F4.h"

#include "../shared/ov/func_8015E22C.h"

#include "../shared/ov/func_8015E288.h"


// @class: struct
// @unstuck(P36): none — MATCH (pending whole-binary gate); fn-ptr table folds %lo via extern array, 0x234 single word store


extern void func_8015E40C(s32 a0);
extern s32 func_80161B18(void *a0);
extern s32 func_80161B84(void *a0);
extern s32 func_80161208();
extern void func_8015E5B0(u8*);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);

extern void (*D_80181914[])(void*);

#include "../shared/ov/func_8015E344__6a040027.h"


#include "../shared/ov/func_8015E40C.h"


// @class: struct
// @unstuck(P36): none — MATCH (pending whole-binary gate); s16 v[3] array forces all 3 locals addressable (reload-from-stack), u16* psVar1 → lhu null/flag check


extern u16 D_80181BDC;
extern u16 D_80181BDE;
extern u16 D_80181BE0;
extern s32 D_80181BE4;

extern void func_80149350(s32 arg0);
extern void func_80013E94(void *a0, void *a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

#include "../shared/ov/func_8015E4B0__dee0300d.h"




extern void func_8013C9C4(void *a0);
extern s32 D_80181BEC;

#include "../shared/ov/func_8015E588__b0b4e285.h"


#include "../shared/ov/func_8015E5B0.h"


// @class: struct
// @unstuck(P36): none — MATCH (clean -O2 reconstruction; table-of-fnptr indexed by param_1[0])


extern s32 func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159BE4(s32 arg0);

/* function-pointer dispatch table */
extern void (*D_80181914[])(void*);

#include "../shared/ov/func_8015E698__33c63185.h"


#include "../shared/ov/func_8015E714.h"

#include "../shared/ov/func_8015E84C.h"

#include "../shared/ov/func_8015E880.h"

#include "../shared/ov/func_8015E8B4.h"



void func_8015E8E8(s32 *a0) {

    extern void (*D_80181C00[])(void);
    D_80181C00[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015E924.h"

#include "../shared/ov/func_8015E95C.h"

#include "../shared/ov/func_8015E9B8.h"


extern u16 func_801487F4(s32*);
extern void func_80147078(s32*, s16);
extern void func_80159B70(void *a0);
extern s32 func_80149D10(s32);
extern void func_80175150(void *a0);
extern void func_8016EE40(s32 a0, s32 a1);
extern s32 func_80149744(struct S_80149744*);
extern void func_80149788(void);
extern s32 func_80161B84(void *a0);
extern s32 func_8014A4B4(void *a0);
extern void func_8014A4FC(void);
extern s32 func_80149AA8(s32*);
extern void func_80149AD4(s32*);
extern s32 func_80149B54(s32*);
extern void func_80149BAC(s32*);
extern s32 func_800CF8B4(void);
extern s32 func_801491C4(s32);
extern s32 func_80148E54(void *a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32*, s32*);
extern void func_80147A84(s32);
extern void func_801473EC(s32*);
extern void func_80154150(s32, s32);
extern void func_8014D738(void);
extern void func_8015C714(void *a0);
extern s32 func_80161208();  /* canonical no-proto (§17a-1) */
extern void func_801483E8(void);

extern void (*D_80181914[])(void *);

#include "../shared/ov/func_8015EA3C__cadf3ee3.h"


#include "../shared/ov/func_8015ED6C.h"

#include "../shared/ov/func_8015EDA0.h"

#include "../shared/ov/func_8015EDD4.h"



s32 func_8015EE08(s32 a0) {

    extern void (*D_80181C08[])(void);
    D_80181C08[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015EE44.h"


// @class: plumbing
// @unstuck(P36): none — MATCH (straight STUB call sequence; param saved to $s0 across calls)

extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);

extern int D_800D4C48;
extern int D_801818F8;

#include "../shared/ov/func_8015EE7C__b34f471c.h"



extern void (*D_80181914[])(void *);

extern void func_80148038(s32 a0, s32 a1);
extern void func_80147460(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80161418(void *a0);
extern s32 func_801725A4(u8 *a0);

#include "../shared/ov/func_8015EEE0__05ff1db5.h"


#include "../shared/ov/func_8015EF9C.h"

#include "../shared/ov/func_8015EFA4.h"

#include "../shared/ov/func_8015EFD8.h"



#include "../shared/ov/func_8015F00C__bb93e93c.h"


#include "../shared/ov/func_8015F048.h"

#include "../shared/ov/func_8015F080.h"

extern s32 D_80062BE8;
extern void (*D_80181914[])(void *);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8014AB5C(void);
extern void func_80159B70(void *a0);
extern void func_80019064(void *a0);
extern void func_80147324(s32 a0);
extern s32 func_80161208(void);
extern int func_80155FF8(int arg, int a1);

#include "../shared/ov/func_8015F118__a1950d70.h"


#include "../shared/ov/func_8015F260.h"

#include "../shared/ov/func_8015F2BC.h"

#include "../shared/ov/func_8015F2F0.h"



void func_8015F324(s32 *a0) {

    extern void (*D_80181C18[])(void);
    D_80181C18[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015F360.h"

#include "../shared/ov/func_8015F380.h"


extern void (*D_80181914[])(void *);

extern s32 func_80149884(void);
extern s32 func_801496D4(void*);
extern void func_80149724(void);
extern void func_801477E8(s32*, s32);
extern u16 func_80148800(s32*);
extern s32 func_80148980(u8*);
extern void func_8014F1F4(void);
extern void func_8014FCFC(void);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80147A84(s32 a0);
extern void func_801473EC(s32*);
extern void func_80146DB8(s32*, s32*);
extern void func_80146E90(s32*, s32);
extern void func_8014ED28(s32 a0);
extern void func_8014FA04(s32 a0);
extern s32 func_801725B8(u8*);
extern void func_80147324(s32 a0);
extern void func_80019064(void*);
extern void func_801484B0(s32, s32);
extern void func_80148534(s32, s32);

#include "../shared/ov/func_8015F448__add714ee.h"


#include "../shared/ov/func_8015F738.h"

#include "../shared/ov/func_8015F76C.h"

#include "../shared/ov/func_8015F7A0.h"



s32 func_8015F7D4(s32 a0) {

    extern void (*D_80181C50[])(void);
    D_80181C50[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8015F810.h"

#include "../shared/ov/func_8015F848.h"


extern void (*D_80181914[])(void *);
extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80147078(s32 *, s16);
extern void func_80159B70(void *);
extern s32 func_80161208(void);

#include "../shared/ov/func_8015F89C__610b5f14.h"


#include "../shared/ov/func_8015F948.h"


extern void (*D_80181914[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208(void);

#include "../shared/ov/func_8015F9A4__76dde591.h"


#include "../shared/ov/func_8015FA24.h"

#include "../shared/ov/func_8015FA44.h"

#include "../shared/ov/func_8015FA78.h"



void func_8015FAAC(s32 *a0) {

    extern void (*D_80181C5C[])(void);
    D_80181C5C[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_801612B8(void *a0, s32 a1);
extern void func_8016007C(s32 a0);
extern void (*D_80181914[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern s32 func_8015BE94();
extern void func_8015C0C4(s32 a0);
extern void func_8015FBE0(s32 *a0);

#include "../shared/ov/func_8015FAE8__9b46348c.h"



extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80147324(s32 a0);
extern void func_801553A8(s32 *a0);
extern void func_801553C0(s32 a0);
extern void func_80146CA0(void *a0);


#include "../shared/ov/func_8015FBE0__dd2ea6e8.h"


extern void func_801599A4(void *a0);

// @class: struct
// @unstuck(P36): none — MATCH (indexed fn-ptr table call + byte-offset struct stores; mirrors sibling func_801599A4 idiom)

extern s32 D_800AE6B0;
extern void (*D_80181914[])(void *);

extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

#include "../shared/ov/func_8015FCC8__87a5e0ba.h"



// @class: plumbing
// @unstuck(P36): none — MATCH expected; simple 3-call sequence with global table index

extern unsigned int D_80181C70[];

extern void func_80147324(s32 arg0);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);

#include "../shared/ov/func_8015FD74__012cd6bc.h"


#include "../shared/ov/func_8015FDCC.h"


// @class: struct
// @unstuck(P36): none — MATCH expected (fn-ptr-table dispatch + ushort struct fields)


extern void (*D_80181914[])(void*);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_80154A74(s32 a0, s32 a1);
extern s32 func_80161208();

#include "../shared/ov/func_8015FE70__bbab5a5a.h"



extern s32 D_800AE6B0;
extern void (*D_80181914[])(void *);
extern u8 D_80078EC1;
extern u8 D_80078EC2;
extern u16 D_801270C0;

extern void func_8016007C(s32 a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern u8 func_801656E8(s32 a0, s32 a1);
extern void func_80150820(s32 a0, s32 a1);
extern void func_8014BFF4(s32 a0, s32 a1);
extern void func_80165670(s32 a0, s32 a1);
extern void func_80165840(void);
extern void func_801658DC(void);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_8016004C(s32 a0);

#include "../shared/ov/func_8015FF20__7a9d7733.h"


#include "../shared/ov/func_8016004C.h"

#include "../shared/ov/func_8016007C.h"

#include "../shared/ov/func_801600D0.h"

#include "../shared/ov/func_80160104.h"



void func_80160138(s32 *a0) {

    extern void (*D_80181CEC[])(void);
    D_80181CEC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80160174.h"

#include "../shared/ov/func_801601AC.h"

#include "../shared/ov/func_801601E4.h"

#include "../shared/ov/func_80160244.h"


extern void (*D_80181914[])(void*);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

#include "../shared/ov/func_801602A4__b32c8455.h"


#include "../shared/ov/func_8016032C.h"

#include "../shared/ov/func_80160334.h"

#include "../shared/ov/func_80160368.h"



void func_8016039C(s32 *a0) {

    extern void (*D_80181CFC[])(void);
    D_80181CFC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_801603D8.h"

#include "../shared/ov/func_80160410.h"







/* data */
extern u8  D_80078EC0;
extern u8  D_80078EBF;
extern void (*D_80181914[])(void *);

/* callees (engine_core.h canonical sigs) */
extern void func_80149020(s32 *a0);
extern void func_80149034(s32 *a0);
extern u16  func_80148800(s32 *a0);
extern s32  func_80149B54(s32 *a0);
extern void func_80149BAC(s32 *a0);
extern s32  func_80149AA8(s32 *a0);
extern void func_80149AD4(s32 *a0);
extern s32  func_80146E98(s32 a0);
extern u16  func_801487F4(s32 *a0);
extern void func_8015E9B8(s32 *a0);
extern void func_80159B70(void *a0);
extern s32  func_800CF8B4();
extern s32  func_801491C4(s32 a0);
extern void func_80147AD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801473EC(s32 *a0);
extern void func_8014D738(void);
extern void func_8015C714(void *a0);
extern s32  func_80161208();
extern void func_80147078(s32 *a0, s16 a1);
extern void func_8015F00C(s32 *a0);

#include "../shared/ov/func_80160534__c72b33ac.h"


#include "../shared/ov/func_801607B8.h"

#include "../shared/ov/func_801607E4.h"

#include "../shared/ov/func_80160818.h"



#include "../shared/ov/func_8016084C__4dd15e96.h"


#include "../shared/ov/func_80160888.h"

#include "../shared/ov/func_801608C0.h"


// @class: struct
// @unstuck(P36): none — MATCH (function-pointer table folds %lo via extern array indexed by halfword)


extern void (*D_80181914[])(void*);

extern u16 func_801487F4(s32 *a0);
extern s32 func_80161208();
extern void func_80160A74(s32 *a0);
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);

#include "../shared/ov/func_80160920__f19f7444.h"




// @class: struct
// @unstuck(P36): none — MATCH (pending byte-gate); function-pointer table %lo-fold via extern array


extern u16 func_801487F4(s32 *a0);
extern void func_80160A74(s32 *a0);
extern s32 func_80161208();

/* function-pointer dispatch table; indexed by *param_1 (×4 = ptr size) */
extern void (*D_80181914[])(void*);

#include "../shared/ov/func_801609B8__7e8f4287.h"


#include "../shared/ov/func_80160A28.h"

#include "../shared/ov/func_80160A74.h"

#include "../shared/ov/func_80160ACC.h"

#include "../shared/ov/func_80160B00.h"



#include "../shared/ov/func_80160B34__e8ed7a9b.h"


#include "../shared/ov/func_80160B70.h"

#include "../shared/ov/func_80160BB4.h"

#include "../shared/ov/func_80160C28.h"

#include "../shared/ov/func_80160CB4.h"


// @class: struct
// @unstuck(P36): none — MATCH (mirrors byte-matched func_8015DBD4 in same overlay; dispatch via D_80181914 + func_80147078/func_80159B70 tail, func_80161208 else)

extern void (*D_80181914[])(void *);
extern u16 func_80148800(s32 *a0);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern s32 func_80161208();

#include "../shared/ov/func_80160D10__20d94e53.h"


#include "../shared/ov/func_80160DEC.h"

#include "../shared/ov/func_80160E3C.h"

#include "../shared/ov/func_80160E70.h"


extern void (*D_80181D20[])(void);

void func_80160EA4(void *a0) {
    D_80181D20[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80160EE0.h"

#include "../shared/ov/func_80160F00.h"

#include "../shared/ov/func_80160F70.h"

#include "../shared/ov/func_80160FE0.h"


// @class: struct
// @unstuck(P36): none — MATCH

extern void func_80149020(s32 *a0);
extern void (*D_80181914[])(void *);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);

#include "../shared/ov/func_80161034__317ceab4.h"


#include "../shared/ov/func_80161094.h"

#include "../shared/ov/func_801610FC.h"

#include "../shared/ov/func_80161104.h"

#include "../shared/ov/func_80161124.h"

extern s32 func_801612B8(void *a0, s32 a1);
extern s32 func_8016130C(void *a0, s32 a1);
void aF80161208(void *a0) __asm__("func_80161208");
#include "../shared/ov/func_80161208.h"


#include "../shared/ov/func_80161240.h"

#include "../shared/ov/func_80161278.h"

#include "../shared/ov/func_801612B8.h"

extern void func_80161240(void *a0);
extern s32 func_801612B8(void * a0, s32 a1);
#define SHB(x) __asm__ __volatile__("" : "=r"(x) : "0"(x))
#define SHB(x) __asm__("" : "=r"(x) : "0"(x))

extern void func_801599A4(void*);
extern void func_8015BDD0(s32*);
extern void func_8015BF48(s32*);

/* REDRAFT (decay axis: RETURN TYPE). The stored draft had been flipped to
 * `void` to fit the fleet header decl in src/shared/engine_core.h, while the
 * body still `return 1; / return 0;`. gcc-2.7.2 silently drops the $v0 sets in
 * that situation, costing the three `addiu $v0, $zero, 1` / `addu $v0,$zero,$zero`
 * instructions the ASM plainly has. Restored to s32 (§109/§85 — the single call
 * site `func_8016130C(a0, func_801612B8(a0, 1));` discards the result, so the
 * void->s32 widen is caller-neutral and must be fixed on the HEADER side). */

/* RECONCILE (§37/§124 asm-label alias — zero header touch).
 * Gate error: jr_8015C32C.c:3501 conflicting types for `func_8016130C'
 *             :3479 previous declaration.
 * TU line 3479 is `DEFINE_func_80161240()`, whose expansion (engine_core.h:3781)
 * declares `extern void func_8016130C(void *a0, s32 a1);` — a RETURN-TYPE
 * disagreement with this draft's required `s32`.  The third line the gate quoted
 * (:5228 "location of previous definition") is unrelated noise: it is the
 * pre-existing `#define SHB(x)` redefinition *warning* between TU lines 5227 and
 * 5538, present with or without this draft.
 * Fix: the C identifier becomes aF8016130C, so it never collides with the
 * canonical `void func_8016130C` declaration, while the GNU asm label makes the
 * EMITTED symbol `func_8016130C`.  The macro's caller func_80161240 keeps calling
 * the `extern void` spelling and is byte-unaffected (it discards the return).
 * Codegen for this function is untouched — match_one still MATCH.
 * (Alternative, house style, NOT taken here per the no-header-edit rule: widen
 * src/shared/engine_core.h:3781 to `extern s32 func_8016130C(void *a0, s32 a1);`
 * and rename back to the plain name — byte-identical either way.) */


#include "../shared/ov/func_8016130C.h"



// @class: schedule
// @unstuck(P36): none — MATCH


#include "../shared/ov/func_80161374.h"


#include "../shared/ov/func_80161418.h"

#include "../shared/ov/func_80161450.h"

#include "../shared/ov/func_80161488.h"

#include "../shared/ov/func_801614E4.h"

#include "../shared/ov/func_8016151C.h"

#include "../shared/ov/func_80161554.h"

#include "../shared/ov/func_8016158C.h"

#include "../shared/ov/func_801615C4.h"



// @class: other
// @unstuck(P36): first draft — plain if-chain over the flag bits
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
extern void func_8015BF48(s32 *a0);
extern void func_8015F2F0(s32 *a0);
extern void func_8014C010(s32 a0, s32 a1);
extern void func_80161D20(int param_1, u32 param_2);
extern s32 func_8014A6C4(s32 a0);
extern s32 ratan2(s32 a0, s32 a1);

#include "../shared/ov/func_8016163C.h"



extern void func_8014C010(s32 a0, s32 a1);
extern void func_80161D20(int param_1, u32 param_2);
extern void func_801599A4(void *a0);
extern void func_8015BF48(s32 *a0);
extern s32 func_8014A6C4(s32 a0);
extern void func_8015F2F0(s32*);
extern s32 ratan2(s32 x, s32 y);

#include "../shared/ov/func_80161774.h"



// @class: schedule
// @unstuck(P36): none — MATCH

#include "../shared/ov/func_80161888.h"


#include "../shared/ov/func_8016191C.h"


#include "../shared/ov/func_8016197C.h"

#include "../shared/ov/func_801619A4.h"

#include "../shared/ov/func_801619D0.h"

#include "../shared/ov/func_80161A00.h"

#include "../shared/ov/func_80161A30.h"

#include "../shared/ov/func_80161A60.h"


#include "../shared/ov/func_80161A90.h"


#include "../shared/ov/func_80161B18.h"

#include "../shared/ov/func_80161B84.h"

#include "../shared/ov/func_80161BE0.h"


extern void func_80147324();

/* RECONCILE (§17a-1/§20): the TU already declares
 *   extern void func_80161C24(s32, s32);   (jr_8015C32C.c:1474 / :1417)
 * so the definition must use (int, int); the unsigned semantics of param_2
 * are restored by a cast at each use (codegen-neutral: sltiu + index math). */
#include "../shared/ov/func_80161C24__38230eb9.h"



// @class: struct
// @unstuck(P36): none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

extern u16 D_80181D50[];
extern void func_80147324(s32 arg0);

#include "../shared/ov/func_80161C98__6735a841.h"



// @class: plumbing
// @unstuck(P36): none — MATCH (20 ins)
// DECAY AXIS: return type. The stored draft declared `s32 func_80161CD0(...)` with no
// return statement. That kept $v0 live-out at the epilogue, so gcc-2.7.2's delayed-branch
// pass refused to speculatively fill the second `beqz $v0` delay slot from the fall-through
// with `sll $v0, $s0, 1` — costing one extra nop (21 vs 20 ins) and shifting both branch
// displacements. Declaring the function `void` makes $v0 dead at the return and the fill
// happens. Same return-type axis as the wave, opposite direction (s32 -> void).
// param_2 must be UNSIGNED: the guard assembles as `sltiu $v0, $s0, 0x8`.
//
// RECONCILE (§37/§124 asm-label alias) — the ONLY change vs the uc2 draft; the body is
// byte-identical and untouched.
//   The real TU src/ov_SC01_077/ov_SC01_077_jr_8015C32C.c already carries the m2c canonical
//   declaration
//       :23   extern s32 func_80161CD0(s32 a0, s32 a1);   /* match-first, arity 2 */
//       :1207 extern s32 func_80161CD0(s32 a0, s32 a1);
//   so a plain `void func_80161CD0(int, unsigned int)` definition dies with
//       conflicting types for `func_80161CD0' / previous declaration ... (rtu_match CC1 FAIL).
//   This is the RETURN axis (s32 vs void) plus the param-2 signedness axis, and BOTH spellings
//   are load-bearing for the 20-instruction codegen — conforming the definition to the
//   declaration (escape #1) would perturb bytes, so it is not available here.
//   The alias fixes it at T0: the C identifier is aF80161CD0 (no declaration to collide with)
//   while the EMITTED SYMBOL is func_80161CD0. In-TU callers keep using the `extern s32`
//   spelling and are byte-unaffected (they discard the return). Zero tracked files touched;
//   no header edit is even possible/needed — grep shows func_80161CD0 has NO declaration in
//   include/ or src/shared/, the conflict is purely TU-local m2c boilerplate.
//   Exactly the pattern already banked at src/ov_SC03_099/ov_SC03_099_jr_8015C32C.c:3503
//   for the sibling func_8016191C.
//
//   NOTE on the third gate diagnostic (`:5223 note: location of previous definition`): that is
//   a RED HERRING, unrelated to this function. It is the pre-existing CPP note paired with
//   `:5533 warning: "SHB" redefined` — the TU defines the SHB scheduling-barrier macro twice
//   (post-splice :5222 with __volatile__, :5533 without). It is a warning, present with or
//   without this draft, and it does not fail cc1.

extern int func_800CF8B4();
extern void func_80147324(int arg0);


#include "../shared/ov/func_80161CD0__591d568e.h"



// @class: struct
// @unstuck(P36): none — MATCH (indexed-global %lo-fold via extern u16 array, §18)

extern void func_80147324(s32 arg0);

#include "../shared/ov/func_80161D20__c54665f2.h"


#include "../shared/ov/func_80161D58.h"


// @class: other
// @unstuck(P36): none — MATCH (short-circuit && chain; reused 0x80FFFFFF mask const, andi-0xFF on callee ret)

extern s32 D_800AE6B0;
extern s32 D_800AE6A8;
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32, s32);
extern void func_800D1734(void *);
extern s32 D_80181DB4;

#include "../shared/ov/func_80161D88__41d070a3.h"


// @class: regalloc-order
// @unstuck(P36): none — MATCH (175 ins, relocation-masked). Giant, 3 similar guarded blocks. base=&D_800AF630
//   hoisted to $s2 (referenced only to build the 3 stored pointers base+0x65A8/0x65E0/0x6618 -> $s1);
//   guard reads (D_800B5BD8/C10/C48) + the "=1" + coord stores use direct symbols. Coord idiom:
//   -(s32)(u16)D_800AF7BC/2 + K (negu;srl31;addu;sra1). a2=func_800291DC(8) survives in $s3 for the
//   final (a2&0x7FFF)==(s16)D_80078EB0 test. KEY RESIDUAL (cracked): target computes each pointer into
//   scratch $v0 then `addu $s1,$v0` (dead-intermediate copy) and stores $s1 — natural C ALWAYS coalesces
//   that copy into a direct `addiu $s1,$s2,off` (172 ins, 3 short). Forcing the un-coalesced copy needs
//   an explicit `move` inline-asm (an empty "=r"/"0" re-tie is only a barrier, won't emit the copy).
#include "common.h"







#include "../shared/ov/func_80161E08__c58c620a.h"



#include "../shared/ov/func_801620C4.h"

#include "../shared/ov/func_80162120.h"


// @class: schedule
// @unstuck(P36): none — MATCH (do-while scan over 3-entry global; increments placed AFTER the call so p++ schedules between load and jal, i++ into the delay slot)

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);

extern int D_8018E868[];

#include "../shared/ov/func_8016216C__8fca1d46.h"



extern s32 func_800291DC(s32);
extern u8 D_80078E78[];
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 D_80181DB4;

#include "../shared/ov/func_801621CC__abdb90f8.h"




// @class: schedule
// @unstuck(P36): none — MATCH
extern void func_80029124(s32, s32);
extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);
extern int D_8018E868[];

#include "../shared/ov/func_801622C4__994a7377.h"



extern void (*D_80181DD8[])(void);

#include "../shared/ov/func_80162330__9950e1fa.h"


#include "../shared/ov/func_8016236C.h"

#include "../shared/ov/func_801623B8.h"

#include "../shared/ov/func_80162414.h"

// @class: regalloc-order
// @unstuck(P36): none — MATCH (160 ins, relocation-masked). Keys: (1) base=&D_800AF630 hoisted, pinned $s2;
//   uVar2 UNPINNED (a $s3 pin forced the final `uVar2 & 0x7FFF` in-place+early, breaking the lh delay
//   slot). (2) item pinned $s1, dest INLINED (D_801D96Dx in both call args) so it lands $s0 AFTER a0.
//   (3) base assigned BEFORE the func_800291DC call so the return-copy `addu $s3,$v0` schedules after
//   the base lui/addiu. (4) THE MOVE: each block's `addu $s1,$v0,$zero` = compute `base+off` into a
//   $v0-PINNED temp `t`, then `item = t`. Two distinct hard regs ($v0 vs $s1) can't coalesce, forcing
//   the exact `addiu $v0,$s2,off ; addu $s1,$v0` pair the target emits (plain `item=base+off` coalesces
//   into one `addiu $s1` — 3 ins short). (5) store D_8018E8C0[i] via `extern int D_8018E8C0[]` (folds
//   %lo, consistent with func_80162760). Coord = (s16)(-D_800AF7Bx / 2 + K) (negu; srl 31; addu; sra 1).

#include "common.h"








#include "../shared/ov/func_80162438__e113e304.h"



#include "../shared/ov/func_801626B8.h"

#include "../shared/ov/func_80162714.h"


// @class: schedule
// @unstuck(P36): none — MATCH (24 ins). do-while; load+call first, then p++ and i++ AFTER the call so gcc schedules p++/arg ahead of jal and i++ into the delay slot.

extern void func_800291C8(s32, s32);
extern void func_80016714(void *a0, s32 a1);

extern int D_8018E8C0[];

#include "../shared/ov/func_80162760__e8f6604d.h"


#include "../shared/ov/func_801627C0.h"


// @class: struct
// @unstuck(P36): none — MATCH (19 ins, relocation-masked)
//
// Tiny dispatcher: byte count at D_8011F750 (offset 0 of a 0x58-byte ctl struct;
// cf. func_801627C0 which calls func_80016714(&D_8011F750, 0x58)). If nonzero,
// call D_80181E1C[count - 1]() through a word-stride fn-pointer table.
//
// Two idioms combined to match gcc-2.7.2 -O2:
//  1. The target MATERIALIZES &D_8011F750 (lui;addiu %lo) into $a0 before the lbu
//     instead of folding %lo into the load. A direct global byte read always
//     %lo-folds (lui;lbu %lo), so force the full-address materialization with the
//     §21 re-tie barrier __asm__ __volatile__("":"=r"(p):"0"(p)) and pin the
//     pointer to $a0 with register __asm__("$4") to get the exact register.
//  2. Writing `idx = idx - 1;` as its OWN statement (not inline D_80181E1C[count-1])
//     keeps the array index/decrement separate so %lo(D_80181E1C) folds into the
//     dispatch load (lw %lo(...)($at)) — the inline form instead constant-folds the
//     -1*4 into a -4 load offset and drops the %lo fold (1 ins short, schedule off).


#include "../shared/ov/func_801627E8__a1273625.h"



extern void (*D_80181E20[])(void);

#include "../shared/ov/func_80162834__aeffcd8e.h"



// @class: plumbing
// @unstuck(P36): none — MATCH (stub: alloc + global init + two calls; $s0 holds param_1 across calls)

extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);

extern u8 D_800B5CB8;
extern s32 D_80181E10;
extern s32 D_800B5CBC;
extern u8 D_800B5CDF;
extern s32 D_800B5CEC;

#include "../shared/ov/func_80162870__de1c9bc5.h"


#include "../shared/ov/func_801628F4.h"

#include "../shared/ov/func_80162968.h"

#include "../shared/ov/func_80162AC0.h"

#include "../shared/ov/func_80162ACC.h"

#include "../shared/ov/func_80162AE0.h"

#include "../shared/ov/func_80162AF4.h"

#include "../shared/ov/func_80162B1C.h"

#include "../shared/ov/func_80162CC4.h"

extern void func_80016714(void *a0, s32 a1);
void aF80162CCC(u8 *a0) __asm__("func_80162CCC");
#include "../shared/ov/func_80162CCC.h"


#include "../shared/ov/func_80162D28.h"

#include "../shared/ov/func_80162D88.h"

#include "../shared/ov/func_80162DE8.h"

#include "../shared/ov/func_80162E48.h"

#include "../shared/ov/func_80162EA8.h"

#include "../shared/ov/func_80162F08.h"

#include "../shared/ov/func_80162F60.h"

#include "../shared/ov/func_80162F80.h"

#include "../shared/ov/func_80162FA0.h"

#include "../shared/ov/func_80162FC0.h"

#include "../shared/ov/func_80162FF4.h"

#include "../shared/ov/func_801630C4.h"

#include "../shared/ov/func_80163194.h"

#include "../shared/ov/func_80163234.h"

#include "../shared/ov/func_8016325C.h"

#include "../shared/ov/func_801632E0.h"

#include "../shared/ov/func_801632F0.h"

#include "../shared/ov/func_80163328.h"

#include "../shared/ov/func_801633A8.h"

// @class: struct
// @unstuck(P36): none — MATCH (21 ins, relocation-masked)


#include "../shared/ov/func_80163408__aae3aabe.h"



#include "../shared/ov/func_8016345C.h"


// @class: struct
// @unstuck(P36): none — MATCH (unaligned 8-byte memcpy from global into stack buffer, then forward to callee)

extern char D_8018E118[8];

extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_80163534(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, u16 * a5);

#include "../shared/ov/func_801634D8__644087e9.h"


#include "../shared/ov/func_80163534.h"


#include "../shared/ov/func_80163664.h"

#include "../shared/ov/func_801636D0.h"


#include "../shared/ov/func_80163764.h"


#include "../shared/ov/func_8016380C.h"

#include "../shared/ov/func_801638A0.h"

#include "../shared/ov/func_80163950.h"


extern void (*D_80181E28[])(void);

void func_80163A58(void *a0) {
    D_80181E28[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80163A94.h"

#include "../shared/ov/func_80163C2C.h"


#include "../shared/ov/func_80163EC8__070a59a1.h"


#include "../shared/ov/func_80164270.h"

#include "../shared/ov/func_801642AC.h"

#include "../shared/ov/func_8016432C.h"

#include "../shared/ov/func_80164410.h"

#include "../shared/ov/func_80164418.h"

#include "../shared/ov/func_80164530.h"


// @class: struct
// @unstuck(P36): none — MATCH expected (fn-ptr table dispatch via u16 idx, $s0 holds *(s32*)(p+0x20) across the call)

extern void (*D_80181E7C[])(void);
extern void func_80162D28(s32 *a0);

#include "../shared/ov/func_80164744__75842b8a.h"




// @class: other
// @unstuck(P36): none — MATCH (relocation-masked); key was `if (iVar1 != 0) { big } else { func_80164930 }` (non-zero case first → beqz, not bnez)


extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80146CA0(void *a0);
extern void func_80164930(s32 a);

extern u16 D_800DF2E0;
extern s32 D_80181E44;
extern s16 D_80181E78;
extern s16 D_80181E76;
extern s16 D_80181E74;

#include "../shared/ov/func_801647A4__1eeea95d.h"


#include "../shared/ov/func_80164864.h"

// @class: regalloc-order — wave-3 real-TU crack (§42a); cracked at Max.
// Fix: D_80181E78 read needs direct-addressed `lhu` (u16). Cannot use `*(u16*)&D_80181E78`
// (forces &sym into a held reg -> drift) NOR a block-scoped `extern u16` (conflicting-types
// ERROR vs the ambient s16, cc1 exit 33). Solution: flip the file-scope decl (5802) to u16 —
// byte-neutral to the only other user (func_801647A4 store-only) — and reference directly.


#include "../shared/ov/func_80164930__98817909.h"



#include "../shared/ov/func_80164A74.h"

#include "../shared/ov/func_80164ACC.h"


extern void (*D_80181E88[])(void);

#include "../shared/ov/func_80164BA0__b49a1e16.h"



extern void func_80146578(void);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80146CA0(void *a0);
extern void func_80164DB0(void);

extern u8 D_8018E920;
extern u8 D_8018E921;
extern u8 D_8018E922;
extern u8 D_8018E923;
extern u8 D_8018E924;
extern u8 D_8018E925;
extern u8 D_8018E926;
extern u8 D_8018E927;

#include "../shared/ov/func_80164BDC__b9aaf8bd.h"


#include "../shared/ov/func_80164CD4.h"

#include "../shared/ov/func_80164D4C.h"

#include "../shared/ov/func_80164DB0.h"

#include "../shared/ov/func_80164DD0.h"





extern u8 D_8018E920;
extern u8 D_8018E921;
extern u8 D_8018E922;

#include "../shared/ov/func_80164E40__b458f4a1.h"



extern void (*D_80181E98[])(void);

void func_80164EA4(void *a0) {
    D_80181E98[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @unstuck(P36): none — MATCH

  /* stride 0x10 */
extern DStruct D_8018E96C[];

extern void func_80165124(void *a0);
extern void func_80146CA0(void *a0);

#include "../shared/ov/func_80164EE0__b6346974.h"


#include "../shared/ov/func_80164F44.h"

#include "../shared/ov/func_80165024.h"

#include "../shared/ov/func_80165064.h"

#include "../shared/ov/func_801650C4.h"

#include "../shared/ov/func_80165124.h"

// @class: struct
// @unstuck(P36): none — MATCH (30 ins)
//
// Unaligned slot-fill: loop over 8 slots (0x10 stride) of a global table,
// fill the first free one (field @0xC == 0). Two unaligned block copies from
// param_1 (packed struct assigns -> lwl/lwr/swl/swr). Key: recompute
// p = &D_8018E960[i] each iteration (NOT p++) so gcc reduces base+i*0x10 into
// a SINGLE pointer IV with immediate offsets 0/8/0xC. Hand-incrementing p makes
// combine_givs split the field offsets into a second pointer IV (+2 ins).




#include "../shared/ov/func_80165140__2718b2e5.h"




// @class: schedule
// @unstuck(P36): none — MATCH (pins $s2/$s1/$s0 + zero-code barrier hoists $a0 copy into beqz delay slot)

extern void func_80165240(void *param_1, void *param_2, void *param_3);
extern s32 D_8018E960;

#include "../shared/ov/func_801651B8__b905c751.h"


extern void func_80016ED4(void *a0);
extern s32 func_80017DC4(void *a0, void *a1);

#include "../shared/ov/func_80165240__2568f863.h"


#include "../shared/ov/func_8016533C.h"

#include "../shared/ov/func_80165374.h"

#include "../shared/ov/func_801653B8.h"

#include "../shared/ov/func_801653F4.h"


// @class: struct
// @unstuck(P36): none — MATCH (54 ins)

extern u8 D_80078E78[];
extern u8 D_80078EC1;
extern void (*D_80181EDC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);

#include "../shared/ov/func_801654A8__a242daaf.h"



// @class: struct
// @unstuck(P36): none — MATCH (function-pointer-array dispatch; & 0x80 branch + & 0x7f index fold)

extern u8 D_80078EC5;
extern u8 D_80078EC1;
extern void (*D_80181EDC[])(void);
extern void func_80165B28(void *a0);

#include "../shared/ov/func_80165580__7088316d.h"


#include "../shared/ov/func_801655E4.h"

#include "../shared/ov/func_80165624.h"


extern u8 D_80181F58[];

#include "../shared/ov/func_80165658__7d41d9cf.h"



extern s32 D_80181F78[];
extern s32 D_80078EC8;

#include "../shared/ov/func_80165670__9b6d7eb9.h"


#include "../shared/ov/func_80165694.h"


extern u8 D_80181FF4[];

#include "../shared/ov/func_801656D0__2cb3c351.h"



extern u8 D_80182014[];

#include "../shared/ov/func_801656E8__2d94a135.h"



extern u8 D_80182034[];

#include "../shared/ov/func_80165700__1fb1778a.h"


#include "../shared/ov/func_80165718.h"

#include "../shared/ov/func_80165770.h"

#include "../shared/ov/func_801657A0.h"

#include "../shared/ov/func_801657D8.h"

#include "../shared/ov/func_80165840.h"

#include "../shared/ov/func_80165874.h"

#include "../shared/ov/func_801658DC.h"

#include "../shared/ov/func_801658EC.h"

#include "../shared/ov/func_80165900.h"

#include "../shared/ov/func_80165910.h"

#include "../shared/ov/func_80165938.h"

#include "../shared/ov/func_80165958.h"

#include "../shared/ov/func_80165978.h"

#include "../shared/ov/func_80165988.h"

#include "../shared/ov/func_801659A8.h"

#include "../shared/ov/func_801659B8.h"

#include "../shared/ov/func_801659CC.h"



#include "../shared/ov/func_801659DC__0d9631e7.h"


#include "../shared/ov/func_80165A18.h"

#include "../shared/ov/func_80165A20.h"

#include "../shared/ov/func_80165A50.h"

#include "../shared/ov/func_80165A78.h"


extern u8 D_80078EC1;
extern void (*D_801820D0[])(void);

#include "../shared/ov/func_80165AC8__f1ffda7f.h"


#include "../shared/ov/func_80165B08.h"

#include "../shared/ov/func_80165B10.h"

#include "../shared/ov/func_80165B18.h"

#include "../shared/ov/func_80165B20.h"


extern void (*D_8018214C[])(void);

#include "../shared/ov/func_80165B28__c7b72cf4.h"


#include "../shared/ov/func_80165B6C.h"

#include "../shared/ov/func_80165BB4.h"

#include "../shared/ov/func_80165BFC.h"

#include "../shared/ov/func_80165C58.h"

#include "../shared/ov/func_80165C78.h"

#include "../shared/ov/func_80165CA0.h"


extern M2C_UNK D_8018E128;

#include "../shared/ov/func_80165E2C__1f54f802.h"


#include "../shared/ov/func_80165E90.h"

#include "../shared/ov/func_80165FA4.h"


extern void (*D_80182158[])(void);

void func_80166018(void *a0) {
    D_80182158[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80166054.h"

#include "../shared/ov/func_801661CC.h"

#include "../shared/ov/func_80166244.h"

#include "../shared/ov/func_8016629C.h"

#include "../shared/ov/func_801662F4.h"

#include "../shared/ov/func_8016634C.h"

#include "../shared/ov/func_801663A4.h"


extern void (*D_80182160[])(void);

void func_801663FC(void *a0) {
    D_80182160[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80166438.h"

#include "../shared/ov/func_801665B4.h"


extern void (*D_80182228[])(void);

void func_80166618(void *a0) {
    D_80182228[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80182238[])(void);

void func_80166654(void *a0) {
    D_80182238[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

   /* 12-byte sub-table record (stride 0xC) */



#include "../shared/ov/func_80166690__8e3d7914.h"




/* func_80166994 — trail/afterimage ring recorder (0xC4-stride Trail records at D_8018E9E0).
 * param_2: 0=init, 1=advance(record), 2=fadeout; param_3: trail index (s16); param_4: divisor (s16).
 *
 * K&R definition: true s16 params => callee-side lazy per-use narrow/extend with raw pseudos
 * (s3/t0/s4 hold raw a1/a2/a3; first-use extension allocates IN PLACE into the arg reg), while
 * the promoted K&R type (int x4) stays compatible with the canon-sig s32 prototype in the TU.
 * Returns s32 (v0=1 when the fadeout completes, else 0) => the //@EDIT above flips the split's
 * canon-sig prototype return type, AND engine_core.h needs the once-global ec_edit (all 5 sites,
 * byte-neutral: every caller discards the result):
 *   ec_edit old: "extern void func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 *   ec_edit new: "extern s32 func_80166994(s32 a0, s32 a1, s32 a2, s32 a3); \"
 * Without the ec_edit, cc1 hard-errors (conflicting types vs the void decls in DEFINE_ macros).
 *
 * Fully block-scoped (typedefs + externs inside the body) so the crack propagates ×134 via
 * family_remap with zero file-scope footprint. No register pins.
 */
#include "../shared/ov/func_80166994__f9f79a43.h"


// @class: regalloc-order
// @unstuck(P36): none — MATCH (69 ins). Pins $s4/$s1 for param_2/param_3 + a1/a2-pinned temps
//   with non-volatile SHB barriers force the sign-ext move-form; short iVar2 (unpinned)
//   gives the temp-form counter increment that fills the skip-branch delay slots;
//   loop-invariant eq=(p2==p3) hoisted; SHB(p2) after the move serializes param_2 before
//   param_3's sign-ext (last ordering swap); param_1/param_4 left natural (arg-order saves).


#define SHB(x) __asm__("" : "=r"(x) : "0"(x))

#include "../shared/ov/func_80166F58__3728db8a.h"





#include "../shared/ov/func_8016706C.h"



// @class: schedule
// @crack (P36 S103, agent c14 — the @stuck note that stood here was refuted on bytes): CLOSED lever-free. The `la $s2`/`i=0`
// placement is sched1's source-order tie-break (rank_for_schedule, sched.c:2385, INSN_LUID last) — the ~40 permutations
// never moved the loop init to just before its `do`; `&f.cx` passed at each call (no pointer local, so cse cannot make
// it a callee-saved pseudo, cse.c:6776-6803 / invalidate_for_call :1725); block 2 as plain single-use temps (a reused
// temp dies twice and is refused by local-alloc.c:472). Full reading: .run/P36/agents/ov_SC04_011__func_801670E4/mechanism.md




extern void func_80149350(s32);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32  func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);


#include "../shared/ov/func_801670E4__07fc245b.h"



 /* 0x20 bytes */






#include "../shared/ov/func_80167540.h"



#include "../shared/ov/func_80167714.h"


extern void (*D_80182248[])(void);

#include "../shared/ov/func_801678B4__5889ab74.h"



#include "../shared/ov/func_801678F0.h"



extern void (*D_80182254[])(void);

void func_80167A9C(void *a0) {
    D_80182254[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80167AD8.h"

// @class: regalloc-order
// @unstuck(P36): none — MATCH expected; mirrors already-matched sibling func_8016A290 (same 3-loop tail), swapping the inline matrix-setup for a func_80168070 call + constant color block.

#include "common.h"





#include "../shared/ov/func_80167AE0__7a5ad569.h"




// @class: schedule
// @unstuck(P36): none — MATCH. The between-loops f1/f2 store-swap (0x55/0x56) is fixed by writing f2's assign first, then the chained `buf[0x44] = buf[0x45] = buf[0x45] << 1;` — the chain keeps f1's read first (read order fixed by -0x12 in $v0) while emitting f2's store (0x56) ahead of the f1/f0 pair (0x55,0x54). 173/173.

extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u16  D_800B99DA;
extern u8   D_801821B4[];
extern u8   D_801821C8[];

#include "../shared/ov/func_80167DBC__a1f70bee.h"


#include "../shared/ov/func_80168070.h"


extern s32 func_80029178(s32 arg);
extern s32 func_80166F58(s32, s32, s32, s32);

#include "../shared/ov/func_801681FC__9cf18f49.h"


#include "../shared/ov/func_8016829C.h"

#include "../shared/ov/func_80168328.h"

#include "../shared/ov/func_801683D8.h"


extern s32 func_80166F58(s32, s32, s32, s32);

#include "../shared/ov/func_80168430__64c1a81e.h"


#include "../shared/ov/func_801684B4.h"

#include "../shared/ov/func_80168540.h"

#include "../shared/ov/func_801685EC.h"

#include "../shared/ov/func_80168640.h"

#include "../shared/ov/func_80168664.h"


extern void (*D_8018226C[])(void);

#include "../shared/ov/func_80168744__54ea2f8d.h"


#include "../shared/ov/func_80168780.h"

#include "../shared/ov/func_801687CC.h"

// @class: decl-conflict (reconcile) — MATCH (108 ins), real-TU verified via rtu_match
// @crack: The wave-2 "8-residual SCHEDULE" note was a STALE-OBJECT / isolation phantom (§42b):
//   in the real TU the draft NOCOMPILEs — DEFINE_func_801687CC() (split line ~6757) expands
//   `extern void func_80168828(void);` right before the def, so `void func_80168828(s32 param_1)`
//   is a HARD `conflicting types` error (cc1 exit 33). RECONCILE-FIRST fix (sweep-safe, lives
//   entirely in the def — no //@EDIT, no macro edit): declare the fn `(void)` and capture a0 via
//     register s32 a0v __asm__("$4");  s32 param_1 = a0v;
//   The register-var binds incoming $a0; copying it into a NORMAL pseudo (live across the calls)
//   makes gcc allocate param_1 to a callee-saved reg, emitting the target's `addu $s1,$a0,$zero`
//   at idx2. NOTE: a DIRECT `register s32 param_1 __asm__("$4")` FAILS (param_1 stays in the
//   call-clobbered $a0 → 100-off). With this reconcile, gcc's natural schedule places the CSE'd
//   `li $v1,0x40` at idx15 with ZERO extra levers — the §42a lever-4 consumer-block reorder was
//   never needed. The $v1 pin (register c40 __asm__("$3")) is still load-bearing (else 0x40 folds
//   to a $v0 immediate). 134-overlay family exemplar: only D_8018225C differs -> banks x134.
#include "common.h"



#include "../shared/ov/func_80168828__46111998.h"




extern void (*D_80182274[])(void);

void func_801689D8(void *a0) {
    D_80182274[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80168A14.h"

#include "../shared/ov/func_80168A88.h"


extern void (*D_8018227C[])(void);

void func_80168AA8(void *a0) {
    D_8018227C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80168AE4.h"


extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
/* Conform to the TU's canonical decl (jr_8015C32C.c:5546 `extern void func_80146C3C(void);`)
 * and cast at the use site — same escape the TU already uses at :6388. Codegen-neutral. */
extern void func_80146C3C(void);

#include "../shared/ov/func_80168B70.h"


#include "../shared/ov/func_80168BDC.h"


extern void (*D_80182284[])(void);

void func_80168D58(void *a0) {
    D_80182284[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80168D94.h"

#include "../shared/ov/func_80168EC4.h"

#include "../shared/ov/func_80168F40.h"


extern void (*D_8018228C[])(void);

#include "../shared/ov/func_8016901C__b3dcb7cf.h"


#include "../shared/ov/func_80169058.h"

#include "../shared/ov/func_801691B8.h"

#include "../shared/ov/func_80169228.h"


extern void (*D_80182294[])(void);

void func_801693CC(void *a0) {
    D_80182294[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_80169408.h"

#include "../shared/ov/func_8016951C.h"

#include "../shared/ov/func_80169584.h"

#include "../shared/ov/func_801696D8.h"


extern void (*D_8018229C[])(void);

#include "../shared/ov/func_80169830__0644614e.h"


#include "../shared/ov/func_8016986C.h"

#include "../shared/ov/func_801699D0.h"

#include "../shared/ov/func_80169A4C.h"


extern void (*D_80182350[])(void);

void func_80169B80(void *a0) {
    D_80182350[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_800D2318(void);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_800D222C(void *a0, void *a1, s32 a2);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern s32 ratan2(s32 a0, s32 a1);
extern void func_80048D9C(void *a0, void *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(void);

#include "../shared/ov/func_80169BBC__974035e4.h"


#include "../shared/ov/func_80169E44.h"


extern void (*D_80182358[])(void);

#include "../shared/ov/func_80169F00__f286ec5d.h"



// @class: plumbing
// @unstuck(P36): none — MATCH (expected; simple straight-line + single branch, one call-crossing local in $s0)

extern void func_800D1FC8(s32 a0, s32 a1);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_80146C3C(void);

extern char D_80182308[];
extern char D_801822C8[];

#include "../shared/ov/func_80169F3C__a4abc210.h"


#include "../shared/ov/func_80169FE0.h"


extern void (*D_80182390[])(void);

void func_8016A020(void *a0) {
    D_80182390[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8016A05C.h"

#include "../shared/ov/func_8016A08C.h"

#include "../shared/ov/func_8016A1CC.h"

// @class: regalloc-order
// @unstuck(P36): none — MATCH (284 ins). Loop-counter biv update: pinned $v0 temp + $0-add opaque copy (i = t + zr) forces the target's 2-insn `addiu v0,s1,1; addu s1,v0,zero` and keeps CSE from rewriting the (s16)t test to read s1.

#include "common.h"





#include "../shared/ov/func_8016A290__8947ff46.h"




extern void (*D_8018239C[])(void);

void func_8016A700(void *a0) {
    D_8018239C[*(u16 *)((s32)a0 + 0x2)]();
}


// Seed for func_8016A73C (ov_SC01_077 exemplar). Overlay-local struct guessed.





#include "../shared/ov/func_8016A73C.h"



#include "../shared/ov/func_8016A890.h"


// @class: struct
// @unstuck(P36): none — expect MATCH (single-call leaf, stack-struct prim build + averaging writeback)

#include "../shared/ov/func_8016A8FC.h"


#include "../shared/ov/func_8016AA50.h"


extern void (*D_801823E4[])(void);

void func_8016AB30(void *a0) {
    D_801823E4[*(u16 *)((s32)a0 + 0x2)]();
}

