#include "common.h"
#include "../shared/engine_prelude.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
   /* 12-byte sub-table record (stride 0xC) */
 /* 0x20 bytes */
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80189444;
extern u8 D_801893B4;
extern u8 D_80189390;
extern u8 D_8018936C;
extern u8 D_80189420;
extern u8 D_801893FC;
extern u8 D_801893D8;
extern u8 D_80189348;
extern void func_80145934(void);
extern u8 D_801894D4;
extern u8 D_801894B0;
extern u8 D_8018948C;
extern u8 D_80189468;
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
extern unsigned char D_801888CC[];
extern unsigned char D_801888FC[];
extern unsigned char D_8018894C[];
extern unsigned char D_8018897C[];
extern unsigned char D_801889AC[];
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
extern void (*D_801889FC[])(void *);
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
extern u8 D_801202A0[];
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_80188AC4[];
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
extern u8 D_80188B4C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80188B54;
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
extern int D_801C0008;
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
extern s32 D_801C000C;
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
extern s32 D_80188B84;
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
extern void (*D_80188C2C[])(void);
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
extern void (*D_80188C50[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80188C40;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80188C64[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80188C70[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80188C80[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_80188C98[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_80188C88;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80188CAC[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80188CC8[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80188CB8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80188CDC[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80188CF0[])(void);
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
extern s32 D_80188D04;
extern void (*D_80188D2C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80188D0C;
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
extern int (*D_80188D78[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80188D7C[])(void);
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
extern unsigned short D_801891E0[];
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
extern void (*D_801891F0[])(void);
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
extern int D_801C0040;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80189218[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_801891F8;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80189208;
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
extern void (*D_80189258[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80189260[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018922C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018926C[])(void);
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
extern u8 D_8018923C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801C0048;
extern s32 D_801C0054;
extern s32 D_801C0058;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801892A8[])(s32 *);
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
extern s32 D_8018927C[];
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
extern s32 D_801C0050;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_801894F8[])(void);
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
extern char D_80189318[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018959C[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_801896F0[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018950C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_801896F8[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018951C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018953C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80189700[])(void);
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
extern s32 func_8015AE2C(s32 arg0);
extern s32 D_800D4A9C;
extern int func_8015B6F4(int param_1);
extern u8 D_800D4F8C[];
extern u8 D_800D4BE0[];
extern s32 func_8014A51C(int param_1);
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
extern void (*D_80189728[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80189734[])(void);
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
extern s32 func_8015CCD0();
extern s32 func_8015CCB0(void);
extern s32 func_801725E0(u8 *a0);
extern s32 func_8015CCD0(s32 param_1);
extern s32 func_8015CD20(s32 arg0);
extern void func_8015CF24(s32 a0);
extern void func_8015D01C(int param_1);
extern void func_8015CF58(s32 *param_1);
extern void func_8015CFC0(s32 *a0);
extern void func_8015CFFC(void);
extern void func_8015D01C(int param_1);
extern void (*D_801895A8[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801897D8;
extern void func_8015D380(s32 a0);
extern unsigned char D_801888BC[];
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
extern unsigned char D_801897EC[];
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
extern s8 D_80189828[];
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
extern u16 D_80189870;
extern u16 D_80189872;
extern u16 D_80189874;
extern s32 D_80189878;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80189880;
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
extern int D_8018958C;
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
extern unsigned int D_80189904[];
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
extern void (*D_801899B4[])(void);
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
extern void func_8016130C(void *a0, s32 a1);
extern void func_80161240(void *a0);
extern void func_80161374(void *a0, s32 a1);
extern void func_80161278(void *a0);
extern s32 func_801612B8(void * a0, s32 a1);
extern void func_8016163C(void *a0, s32 a1);
extern void func_80161774(void *a0, s32 a1);
extern s32 func_8016197C(s32 a0, s32 a1);
extern void func_80161888(void *a0, s32 a1);
extern void func_801614E4(void *a0);
extern void func_8016191C(void *a0, s32 a1);
extern void func_8016151C(void *a0);
extern void func_80161554(void *a0);
extern s32 func_801615C4(void * arg0, s32 arg1);
extern s32 func_80161A00(s32 a0);
extern s32 func_80161A30(s32 a0);
extern int func_801497A8(s32 *a0);
extern int func_80161BE0(void *param_1);
extern u16 D_801899E4[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80189A48;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801C0060[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80189A6C[])(void);
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
extern int D_801C00B8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80189AB4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80189AA4;
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
extern char D_801BF81C[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80189ABC[])(void);
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
extern void (*D_80189B10[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80189AD8;
extern s16 D_80189B0C;
extern s16 D_80189B0A;
extern s16 D_80189B08;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80189B1C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801C0118;
extern u8 D_801C0119;
extern u8 D_801C011A;
extern u8 D_801C011B;
extern u8 D_801C011C;
extern u8 D_801C011D;
extern u8 D_801C011E;
extern u8 D_801C011F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80189B2C[])(void);
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
extern s32 D_801C0158;
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
extern void (*D_80189B70[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80189BEC[];
extern s32 D_80189C0C[];
extern u8 D_80189C88[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_80189CA8[];
extern u8 D_80189CC8[];
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
extern void (*D_80189D64[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80189DE0[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801BF82C;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80189DEC[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80189DF4[])(void);
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
extern void (*D_80189EBC[])(void);
extern void func_80166618(void *a0);
extern void (*D_80189ECC[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994(s32 param_1, int param_2, int param_3, int param_4);
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80189EDC[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80189EE8[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80189E48[];
extern u8   D_80189E5C[];
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
extern Blk20 D_800AE620;
extern s32  RotMatrixX(s32 a0, void *a1);
extern void func_80168664(void *arg0);
extern void (*D_80189F00[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80189F08[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80189F10[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80189F18[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80189F20[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80189F28[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80189F30[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80189FE4[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80189FEC[])(void);
extern void func_80169F00(void *a0);
extern char D_80189F9C[];
extern char D_80189F5C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018A024[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018A030[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern s32 func_80016A5C();
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018A078[])(void);
extern void func_8016AB30(void *a0);
/* ==== end §8b carried decl layer ==== */


/* func_8016AB6C (ov_SC01_077 jr family, 188 ins, jtbl_801D8BC8) — Phase 26 crack
 * PIN-FREE.  Status: **MATCH (188 ins)**, jtbl VERIFIED exact.
 *
 * jtbl_801D8BC8 = 8 entries, bound `sltiu $v0,$v1,8`, default -> after-switch join.
 *   case 0->+0x88  1->+0xA8  2->+0x110  3->+0x130  4->+0x110  5->+0xA8  6->+0x178  7->+0x178
 * My .rodata relocs (8x R_MIPS_32 vs .text) are byte-identical to that:
 *   88 a8 110 130 110 a8 178 178   (objdump -r/-s -j .rodata .run/match/func_8016AB6C/t.o)
 *
 * ============================================================================
 * LEVER 9 — THE CALL-SINK (the last 2 ins; NEW, generalizable).  See cookbook §48-B.
 * ============================================================================
 * FINAL RESIDUAL was 2 ins (idx 141/143): both present and byte-correct, only transposed
 * around `jal func_8001CE28`:
 *     mine  : addu $a1,$s0,$zero ; jal ; [delay] addu $a0,$s2,$zero
 *     target: addu $a0,$s2,$zero ; jal ; [delay] addu $a1,$s0,$zero
 *
 * It was NOT a scheduling residual (sched1 already emitted a0-then-a1, per calls.c:1878
 * which loads arg regs in ASCENDING arg order).  It was a REGALLOC residual:
 *
 *   The old shape `f(A,LIT); p = LIT;` created TWO pseudos: a block-local arg pseudo
 *   (reg145/150, holding the symbol) and a GLOBAL allocno `p` (reg79) fed by a copy at the
 *   end of each arm.  greg dump said:  `;; 79 preferences: 5 16`.
 *     - $5  copy-pref  <- the join's arg move  (set (reg:SI 5 a1) (reg 79))
 *     - $16 copy-pref  <- the arms' copies     (set (reg 79) (reg145))  ... because
 *       set_preference (global.c:1535) applies reg_renumber[], so a LOCALLY-allocated
 *       pseudo counts as its hard reg.
 *   find_reg's copy-preference override (global.c:~1000) scans hard regs `for (i = 0; i <
 *   FIRST_PSEUDO_REGISTER; i++)` — plain ASCENDING regno, NOT reg_alloc_order.  So $5 beats
 *   $16, deterministically.  The ONLY way $16 wins is if $5 is already in `used` when that
 *   scan runs, and the only reachable way to do that is
 *       allocno_calls_crossed[p] > 0  ->  find_reg sets used1 = call_used_reg_set (global.c:906)
 *       -> AND_COMPL(hard_reg_copy_preferences, used) strips $5 -> $16 is all that's left.
 *   reg79 crossed NO call (def after func_80024054, last use before func_8001CE28), so $5 won.
 *   p in $a1 => the arms' copies became `move $5,$16`, cross_jump merged them to the top of
 *   the join (ahead of the a0 move), and reorg then slotted the a0 move.
 *
 * THE FIX — SINK THE CALL INTO THE ARMS (byte-proven, close=2 -> MATCH):
 *     BEFORE                                     AFTER
 *     if (c) { s3 = f(A1,P1)+3; p = P1; }        if (c) { s3 = f(A1,P1)+3; g(obj,P1); }

 *     else   { s3 = f(A2,P2)+9; p = P2; }        else   { s3 = f(A2,P2)+9; g(obj,P2); }
 *     g(obj, p);                                 // no join copy, no `p` at all
 *   Duplicating the call kills the cross-block pseudo `p` entirely.  The pointer is now a
 *   BLOCK-LOCAL pseudo per arm (lreg: "Register 144 used 3 times across 12 insns in block 13;
 *   crosses 1 call; pointer") -> LOCAL-alloc, crosses a call -> $s0, exactly as before, so the
 *   load-bearing "$16 occupant" that pushes arg0 off $s0 onto $s1 (lever 3) is PRESERVED.
 *   greg goes from "9 regs to allocate: ... 79 ..." to "8 regs to allocate:" (79 gone), and
 *   dispositions are unchanged: arg0=$s1, obj=$s2, var_s3=$s3, var_s0=$s0.
 *   The duplicated `[addu $a0,$s2][addu $a1,$s0][jal g]` tail is IDENTICAL in both arms after
 *   reload (same hard regs!), so jump2's cross_jump re-merges it into a single join block —
 *   ZERO extra bytes — and dbr then fills the jal slot with the nearest insn above it, which
 *   is now the a1 move.  Target shape, exactly.
 *
 * GENERAL RULE: when a value is defined in both arms of an if/else and consumed only by a
 * call in the join, gcc's join-copy makes it a global allocno whose ascending-scan copy-pref
 * hands it the ARG register.  If the target instead keeps it in a callee-saved reg, DUPLICATE
 * THE CALL INTO BOTH ARMS — cross_jump gives the bytes back for free, and the value demotes to
 * a call-crossing block-local, which local-alloc parks in $s0.  (Inverse of §48-A1: A1 sinks an
 * INIT to shorten a live range; this sinks the CONSUMER to delete the allocno outright.)
 *
 * LEVERS PROVEN HERE (see the report / cookbook):
 *  1. LOOP ROTATION (§46 L1, exact trigger): stmt.c:2255 expand_end_loop scans forward from the
 *     loop start label and stops at the FIRST CODE_LABEL, but sets last_test_insn on any
 *     unconditional `jump end_label` — which is exactly what `break` emits.  So `break` out of
 *     the first test rotates the loop (peels the test into a preheader).  `goto lout;` jumps to a
 *     USER label, not end_label, so last_test_insn stays 0 and the loop is NOT rotated.
 *     (`do{}while()` alone does NOT help: expand_exit_loop_if_false ends with a CODE_LABEL, so
 *     expand_end_loop's "already ends in a bare condjump" guard never fires.)
 *     Bonus: the unrotated loop is what keeps the s16 re-sign-extension INSIDE the loop
 *     (sll16/sra16 for the AND, and `sra 20` reusing that same `sll 16` for the >>4).
 *  2. `var_v1 = -0x1000;` AFTER the call, not before -> it no longer crosses the call -> $v1
 *     instead of a callee-saved reg.
 *  3. THE $s0/$s1 DIAL (new): `f(A,B); p = B;`  (literal args, then assign p from the SAME
 *     literal AFTER the call) makes cse rewrite `p = B` as a COPY of the call's arg pseudo.
 *     That arg pseudo is then live across the call yet stays BLOCK-LOCAL -> local_alloc gives it
 *     $s0 -> every global allocno live there now conflicts with hard reg $16 -> the big pointer
 *     (arg0) is pushed off $s0 onto $s1 and the whole allocation flips.  Writing `p = B; f(A,p);`
 *     instead merges them into ONE global allocno, no local, and arg0 takes $s0.  (99 -> 54.)
 *  4. §46 L2 refinement: a SAME-mode copy always dies (cse canon_reg/qty_first_reg).  A
 *     DIFFERENT-mode copy `(set (reg:QI x) (subreg:QI (reg:SI y)))` is not a plain reg-reg copy,
 *     so cse cannot merge the qtys and the copy insn SURVIVES.  That is how `var_c2 = var_s0;`
 *     materialises the target's `addu $v0,$s0,$zero`.  (187 -> 188 ins.)
 *  5. ANTI-DEP PINS A COPY EARLY: sched deterministically SINKS a copy to just before its
 *     consumers.  Reusing the SAME local (var_s0) as the if/else scratch, copying it out, then
 *     redefining var_s0 creates a WAR dep that pins the copy ahead of the redefinition — which
 *     also removes the live-range overlap so both share $s0.  (54 -> 22.)
 *  6. `t = x+1; x = t+1;` is folded by cse to `x = x+2`.  `t = x+1; x = t; x++;` keeps
 *     `addiu t,x,1 ; addiu x,t,1`.  (22 -> 21.)
 *  7. STORE-SINK: to get "compute chain A first, store A last", put A's store FIRST in the
 *     source — the backward list scheduler sinks a store (no dependents) but keeps the compute
 *     order.  (21 -> 8.)
 *  8. DELAY SLOT = source order: reorg takes the closest eligible insn before the jal, and the
 *     backward scheduler puts the HIGHEST-LUID (latest in source) of the tied independents
 *     nearest the call.  `var_s0 = 3;` written AFTER the call statement (sched still hoists it
 *     above the call — pseudos may cross calls at sched1) puts `addiu $s0,$zero,3` in the delay
 *     slot instead of the a1=0 arg move.  (8 -> 2.)
 */





s32 func_8016AB6C(s32 arg0) {
    extern s32 func_801783D0(s32 a0, s32 a1);
    extern s32 func_80024054(u8 *a0, u8 *a1);
    extern void func_8001CE28(Obj_8016AB6C *a0, u8 *a1);
    extern u8 D_8018A038[];
    extern u8 D_8018A048[];
    extern u8 D_801C0428[];
    extern u8 D_801C0450[];

    SVec_8016AB6C sp10;
    SVec_8016AB6C sp18;
    s16 var_s0;
    s16 var_v1;
    s16 var_s3;
    s16 tmp;
    s32 temp_v0;
    u32 r;
    u8 var_c2;
    Obj_8016AB6C *obj;

    temp_v0 = func_801783D0(((Ent_8016AB6C *)arg0)->unk30, 0);
    var_s0 = 3;
    var_v1 = -0x1000;
    ((Ent_8016AB6C *)arg0)->unk30 = temp_v0;
    do {
        if (temp_v0 & var_v1) {
            goto lout;
        }
        var_s0--;
        var_v1 >>= 4;
    } while (var_s0 >= 0);
lout:
    switch (((Ent_8016AB6C *)arg0)->unk2C) {
    case 0:
        ((Ent_8016AB6C *)arg0)->unk26 = 1;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x60;
        ((Ent_8016AB6C *)arg0)->unkA -= 0x20;
        break;
    case 1:
    case 5:
        ((Ent_8016AB6C *)arg0)->unk14 = 0xFFF60000;
        r = ((u32(*)())rand)();
        tmp = var_s0 + 1;
        var_s0 = tmp;
        ((Ent_8016AB6C *)arg0)->unk10 = (r & 0xF) - 8 << 0xF;
        ((Ent_8016AB6C *)arg0)->unk18 = ((r >> 4) & 0xF) - 8 << 0xF;
        ((Ent_8016AB6C *)arg0)->unk26 = 4;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x80;
        ((Ent_8016AB6C *)arg0)->unk30 |= 0xA << (tmp * 4);
        break;
    case 2:
    case 4:
        ((Ent_8016AB6C *)arg0)->unk26 = 4;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x80;
        ((Ent_8016AB6C *)arg0)->unkA -= 0x18;
        break;
    case 3:
        tmp = var_s0 + 1;
        var_s0 = tmp;
        var_s0++;
        ((Ent_8016AB6C *)arg0)->unk26 = 4;
        ((Ent_8016AB6C *)arg0)->unk24 = 0x80;
        ((Ent_8016AB6C *)arg0)->unkA -= 0x18;
        ((Ent_8016AB6C *)arg0)->unk30 = (((Ent_8016AB6C *)arg0)->unk30 | (0xF << (tmp * 4))) * 0x10;
        break;
    case 6:
    case 7:
        obj = ((Obj_8016AB6C *(*)(s32))func_801465C0)(temp_v0);
        if (obj == 0) {
            ((void(*)(Ent_8016AB6C *))func_80146C3C)(((Ent_8016AB6C *)arg0));
            return;
        }
        sp10.vx = ((Ent_8016AB6C *)arg0)->unk6;
        sp10.vy = ((Ent_8016AB6C *)arg0)->unkA - 0x18;
        sp10.vz = ((Ent_8016AB6C *)arg0)->unkE;
        ((void(*)(SVec_8016AB6C *, SVec_8016AB6C *, s32))func_800D20C0)(&sp10, &sp18, 6);
        ((Ent_8016AB6C *)arg0)->unk6 = sp10.vx;
        ((Ent_8016AB6C *)arg0)->unkA = sp10.vy;
        ((Ent_8016AB6C *)arg0)->unkE = sp10.vz;
        if (((Ent_8016AB6C *)arg0)->unk2C == 6) {
            var_s3 = func_80024054(D_8018A038, D_801C0428) + 3;
            func_8001CE28(obj, D_801C0428);
        } else {
            var_s3 = func_80024054(D_8018A048, D_801C0450) + 9;
            func_8001CE28(obj, D_801C0450);
        }
        obj->unkE = var_s3;
        obj->unk4 |= 0x04000000;
        if (((Ent_8016AB6C *)arg0)->unk2C == 6) {
            obj->unk27 = 0xB5;
            var_s0 = 0x70;
        } else {
            obj->unk27 = 0xAE;
            var_s0 = 0xB0;
        }
        var_c2 = var_s0;
        var_s0 = var_s3 >> 2;
        obj->unk2E = -8;
        obj->unk30 = 0;
        obj->unk26 = var_c2;
        obj->unk25 = var_c2;
        obj->unk24 = var_c2;
        ((Ent_8016AB6C *)arg0)->unk20 = obj;
        break;
    }
    ((Ent_8016AB6C *)arg0)->unk2A = 4 - (var_s0 * 4);
    ((Ent_8016AB6C *)arg0)->unk28 = var_s0;
    ((Ent_8016AB6C *)arg0)->unk1C = 0xB;
    ((Ent_8016AB6C *)arg0)->unk2++;
}



extern void func_8016B234();  // K&R: ? of 1 args (P37 rung D t4_D7)
extern void func_800D22E4(s32 a0);

#include "../shared/ov/func_8016AE5C__te4eb1475.h"

#include "../shared/ov/func_8016AFB0.h"

#include "../shared/ov/func_8016B114.h"



extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_80016ED4(void *a0);


void func_8016B234(s32 param_1) {

    extern u8 D_800AF648;
    extern u8 D_8018A070;
    short input[3];
    Prim_B234 prim;
    struct { s16 xy[2]; s32 sp1c; s32 flag; } out;
    void *dp;
    u32 uVar1; /* the projected screen Y, then the UV column index */
    s16 iVar2;
    s32 X, Y0, Y1, base, ni;
    s16 xtmp;
    s32 sxy;
    s32 hh;

    dp = &D_800AF648;
    func_8004914C(dp);
    func_800491AC(dp);
    input[0] = *(u16 *)(param_1 + 6);
    input[1] = *(u16 *)(param_1 + 0xA);
    input[2] = *(u16 *)(param_1 + 0xE);
    RotTransPers((s32)input, (s32)out.xy, &out.sp1c, &out.flag);
    if ((out.flag & 0xffffefff) == 0) {
        sxy = *(s32 *)out.xy;
        prim.a04 = 0x10;
        X = *(u16 *)(param_1 + 0x2a) + sxy;
        uVar1 = (u16)out.xy[1];
        prim.ax = prim.cx = X;
        prim.bx = prim.dx = X + 8;
        Y0 = uVar1 - *(u16 *)(param_1 + 0x26);
        prim.ay = prim.by = Y0;
        hh = *(u16 *)(param_1 + 0x26);
        prim.v0 = prim.v1 = 0x1d0;
        prim.v2 = prim.v3 = 0x1d8;
        prim.cy = prim.dy = uVar1 + hh;
        prim.r = prim.g = prim.b = *(u8 *)(param_1 + 0x24);
        prim.code = (&D_8018A070)[*(s32 *)(param_1 + 0x2c)];
        if (*(s16 *)(param_1 + 0x26) < 5) {
            prim.tag = 0;
        } else {
            prim.tag = 0x50000000;
        }
        uVar1 = *(u16 *)(param_1 + 0x30);
        iVar2 = 0;
        if (0 < *(s16 *)(param_1 + 0x28) + 1) {
            do {
                base = ((uVar1 + 1) & 0xf) << 3;
                prim.u0 = prim.u2 = base + 0x620;
                prim.u1 = prim.u3 = base + 0x628;
                func_80016ED4(&prim);
                uVar1 = (s32)(uVar1 << 0x10) >> 0x14;
                iVar2 = iVar2 + 1;
                xtmp = prim.ax;
                prim.cx = prim.ax = xtmp - 8;
                prim.bx = prim.dx = xtmp;
            } while ((s16)iVar2 < *(s16 *)(param_1 + 0x28) + 1);
        }
    }
}


#include "../shared/ov/func_8016B3F4.h"

#include "../shared/ov/func_8016B428.h"

#include "../shared/ov/func_8016B448.h"


extern void (*D_8018A0F4[])(void);

void func_8016B4BC(void *a0) {
    D_8018A0F4[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: struct
// @unstuck(P36): none — MATCH

extern void func_80015978(s32 a0, s32 *a1);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B984(void *a0);
extern void func_8016B91C(int);
extern int D_801C0478;

void func_8016B4F8(int param_1)
{
    int iVar1;
    int uVar2;
    int buf[2];

    ((void (*)(int, void *))func_80015978)(param_1 + 4, &D_801C0478);
    if (func_8016B9F8(param_1) == 0) {
        *(int *)(param_1 + 0x18) = 0;
        *(int *)(param_1 + 0x14) = 0;
        *(int *)(param_1 + 0x10) = 0;
        iVar1 = func_8016B834(param_1, 0);
        *(int *)(param_1 + 0x10) = iVar1;
        if (iVar1 != 0) {
            iVar1 = func_8016B834(param_1, 1);
            *(int *)(param_1 + 0x14) = iVar1;
            if (iVar1 != 0) {
                iVar1 = func_8016B834(param_1, 2);
                *(int *)(param_1 + 0x18) = iVar1;
                if (iVar1 != 0) goto success;
            }
        }
    }
    ((void (*)(int))func_8016B984)(param_1);
    return;
success:
    func_8016B91C(param_1);
    uVar2 = *(int *)(param_1 + 0x2c);
    if (uVar2 == 0) {
        uVar2 = 0xf0;
    } else {
        uVar2 = 0x2d0;
    }
    *(int *)(param_1 + 0x1c) = uVar2;
    uVar2 = *(unsigned short *)(param_1 + 2);
    uVar2 = uVar2 + 1;
    *(unsigned short *)(param_1 + 2) = uVar2;
}



// @class: schedule
// @unstuck(P36): none — MATCH


extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B984(void *a0);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);

extern s16 D_8018A0E8[];

void func_8016B5C0(s32 param_1) {
    s32 iVar4;
    s32 iVar2;
    s32 iVar5;
    s16 sVar1;
    s16 *psVar5;
    s32 i;

    iVar4 = *(s32 *)(param_1 + 0x18);
    if (((s32 (*)(void))func_8016B9F8)() != 0) {
        goto L984;
    }
    sVar1 = *(s16 *)(iVar4 + 0x1a) + 0x200;
    *(s16 *)(iVar4 + 0x1a) = sVar1;
    *(s16 *)(iVar4 + 0x18) = sVar1;
    if (*(s32 *)(param_1 + 0x2c) == 0) {
        iVar2 = *(s32 *)(param_1 + 0x1c);
    } else {
        iVar2 = *(s32 *)(param_1 + 0x1c) / 3;
    }
    iVar5 = *(s32 *)(param_1 + 0x1c) + -0x20;
    *(s32 *)(param_1 + 0x1c) = iVar5;
    if (iVar5 >= 0) {
        goto LOOP;
    }
L984:
    ((void (*)(s32))func_8016B984)(param_1);
    return;
LOOP:
    i = 0;
    psVar5 = D_8018A0E8;
    do {
        func_8016B6BC(param_1, iVar2, (s32)*psVar5, (s32)(s16)i);
        psVar5 = psVar5 + 1;
        i = i + 1;
    } while (i < 6);
    func_8016B91C(param_1);
    return;
}



// @class: schedule
// @unstuck(P36): none — MATCH (94/94 ins, match_one relocation-masked)
//
// Exemplar of the 138-member h_seq family. The whole crack was ONE statement-order
// lever in the tail: the target's post-func_80015978 fix-up runs
//   v[2].x += off.x;  v[2].y += off.y;  v[0].c = 3;
// (the `c = 3` store LAST). Writing `c = 3` between the two v[2] RMWs — the order the
// Ghidra-C literally prints, and what every prior draft copied — costs 12 mismatches:
// gcc hoists the `li 3` into the load-delay window, which pushes v[2].x into $v1 and
// the off.x temp into $a0, and then the `addu $a0,$s1,$zero` arg copy can no longer be
// scheduled early enough to become the base register of the v[2]/v[0].c stores.
// With `c = 3` last, the arg copy births at the v[2].x/v[2].y boundary (idx 76) exactly
// as the target does, and the mixed $s1-load / $a0-store addressing falls out for free.
// (§67-adjacent: the copy PLACEMENT was the root cause — but here plain statement order
// reaches it, no `__asm__` launder and no register pin needed. Prior notes calling this a
// regalloc tie-break and pinning $a0 were chasing the consequence, not the cause.)
//
// Everything else follows the Ghidra-C: `Prim *p = &prim` (one alias only — a second
// pointer name splits the pseudo and breaks the $s1 base), the `q++` post-increment
// running pointer over the 8-byte table rows, and the ((param_4 << 16) >> 14) byte-offset
// index into D_8018A0D0 (sll 16 / sra 14).


             /* 0x28 */


               /* the 8-byte D_8018A0D0[] row */

extern void func_80013CFC(s32 a0, s32 a1, void *a2);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8001739C(void *a0);

/* Def sig is deliberately (s32,s32,s32,s32) — byte-identical to the (int,unsigned,short,int)
 * spelling, and IDENTICAL to this TU's own caller decl `extern void func_8016B6BC(s32,s32,s32,s32);`
 * (ov_SC01_077_jr_8016AB6C.c), so there is no §73/§57 def-side self-decl conflict to reconcile. */
void func_8016B6BC(s32 param_1, s32 param_2, s32 param_3, s32 param_4) {

    extern int D_8018A0D0;
    int iVar1;
    M8_8016B6BC *q;
    Prim_8016B6BC prim;
    Prim_8016B6BC *p = &prim;
    DVec_8016B6BC off;
    unsigned int v;
    unsigned int c;

    q = (M8_8016B6BC *)*(int *)((int)&D_8018A0D0 + ((param_4 << 0x10) >> 0xe));
    p->color = 0x50000000;
    c = (unsigned int)param_2;
    v = 0x20;
    if (c < 0x20) {
        v = c;
    }
    if (*(int *)(param_1 + 0x2c) == 0) {
        c = c | (v << 0x10 | v << 8);
    } else {
        c = c << 8 | v << 0x10 | v;
    }
    p->combined = c;
    iVar1 = (int)(short)param_3;
    p->z1c = 0;
    p->z20 = 0;
    func_80013CFC(iVar1, (int)q++, &p->v[0]);
    func_80013CFC(iVar1, (int)q++, &p->v[1]);
    func_80013CFC(iVar1, (int)q, &p->v[2]);
    func_80015978(param_1 + 4, (s32 *)&off);
    p->v[0].x += off.x;
    p->v[0].y += off.y;
    p->v[1].x += off.x;
    p->v[1].y += off.y;
    p->v[2].x += off.x;
    p->v[2].y += off.y;
    p->v[0].c = 3;
    func_8001739C(p);
}



// @class: schedule
// @unstuck(P36): none — MATCH (statement order: compute puVar2 base before puVar3 table lookup so param*0x40+base schedule into prologue, leaving the 0x2c load-delay nop)
extern void func_801465C0(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);

extern int *D_8018A12C[];
extern unsigned short D_8018A134[];
extern unsigned short D_8018A13C[];
extern unsigned char D_801C0480[];

int func_8016B834(int param_1, int param_2) {
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_801C0480 + param_2 * 0x40);
    puVar3 = D_8018A12C[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_8018A134[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_8018A13C[param_2];
    }
    return iVar1;
}


#include "../shared/ov/func_8016B91C.h"

#include "../shared/ov/func_8016B964.h"

#include "../shared/ov/func_8016B984.h"


// @class: regalloc-order
// @unstuck(P36): none — MATCH (result is func_8012EFB8's return saved in $s0 across the func_80015954 call; the save-move fills the 2nd call's delay slot. func_80015954's return is discarded.)


extern s32 D_801C0478;
extern void func_8012EFB8(s32 a0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016B9F8(s32 param_1)
{
    s32 buf[2];
    u32 v;

    v = ((u32 (*)(s32 *, s32 *))func_8012EFB8)(&D_801C0478, buf);
    ((void (*)(s32 *, s32 *))func_80015954)(buf, (s32 *)(param_1 + 4));
    return (v & 0xffffefff) != 0;
}


#include "../shared/ov/func_8016BA48.h"

#include "../shared/ov/func_8016BA68.h"


#include "../shared/ov/func_8016BADC.h"


extern void (*D_8018A144[])(void);

void func_8016BBA4(void *a0) {
    D_8018A144[*(u16 *)((s32)a0 + 0x2)]();
}


// @class: plumbing
// @unstuck(P36): none — MATCH (56 ins, match_one relocation-masked)




s32 func_8016BBE0(s32 param_1) {
    extern void func_8016BF34(void *a0);
    extern s32 func_8016BF50();  // K&R: 0/1 of 1 args (P37 rung D t4_D7)
    extern void func_8001CF00(s32);
    extern M2C_UNK D_801C05B4;
    extern u8 D_801C05B5;
    extern u8 D_801C05B6;
    extern M2C_UNK D_801C05B8;
    extern u8 D_801C05B9;
    extern u8 D_801C05BA;

    int iVar1;
    int temp;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    *(int *)(((int)param_1) + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32))func_8016BF34)(((int)param_1));
        func_8016BF50(((int)param_1));
        func_8001CF00(iVar1);
        *(s16 *)(iVar1 + 0x10) = 0;
        temp = *(int *)(((int)param_1) + 0x2c);
        *(s16 *)(iVar1 + 0x14) = 0;
        *(s16 *)(iVar1 + 0x1a) = 0;
        *(s16 *)(iVar1 + 0x18) = 0;
        *(s16 *)(iVar1 + 0x12) = temp * 0x555;
        *(s16 *)(((int)param_1) + 0x10) = 0;
        *(s16 *)(((int)param_1) + 0x14) = 0;
        (*(u8 *)&D_801C05B4) = 0x20;
        D_801C05B5 = 0x20;
        D_801C05B6 = 0;
        (*(u8 *)&D_801C05B8) = 0xc0;
        D_801C05B9 = 0xc0;
        D_801C05BA = 0;
        *(u16 *)(((int)param_1) + 2) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)(((int)param_1));
    }
}



extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801C05B4;
extern M2C_UNK D_801C05B8;

void func_8016BCC0(void *arg0) {
    u16 temp_a2;
    u16 temp_v0;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x20);
    func_8016BF50();
    temp_a2 = M2C_FIELD(arg0, u16 *, 0x10) + 0x60;
    M2C_FIELD(arg0, u16 *, 0x10) = temp_a2;
    temp_v0 = M2C_FIELD(temp_s0, u16 *, 0x1A) + temp_a2;
    M2C_FIELD(temp_s0, u16 *, 0x1A) = temp_v0;
    M2C_FIELD(temp_s0, u16 *, 0x18) = temp_v0;
    M2C_FIELD(temp_s0, u16 *, 0x12) = (u16) ((M2C_FIELD(temp_s0, u16 *, 0x12) + 0x71) & 0xFFF);
    func_8016BFA8(arg0, &D_801C05B4, &D_801C05B8, temp_s0 + 0x18);
    if ((s16) M2C_FIELD(temp_s0, u16 *, 0x1A) >= 0x1001) {
        M2C_FIELD(temp_s0, u16 *, 0x18) = 0x1000U;
        M2C_FIELD(temp_s0, u16 *, 0x1A) = 0x1000U;
        func_80146E90(arg0, M2C_FIELD(arg0, s32 *, 0x30));
        M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) + 1);
    }
}


// @class: struct
// @unstuck(P36): none — MATCH (74 ins, relocation-masked)




s32 func_8016BD78(s32 param_1)
{
    extern s32 func_8016BF50();  // K&R: 0/1 of 1 args (P37 rung D t4_D7)
    extern u8 D_801C05B5;
    extern u8 D_801C05B6;
    extern u8 D_801C05B9;
    extern u8 D_801C05BA;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    func_8016BF50();

    p1 = &(*(u8 *)&D_801C05B4);
    if (*p1 != 0) *p1 -= 4;
    if (D_801C05B5 != 0) D_801C05B5 -= 4;
    if (D_801C05B6 != 0) D_801C05B6 -= 4;
    p2 = &(*(u8 *)&D_801C05B8);
    if (*p2 != 0) *p2 -= 4;
    if (D_801C05B9 != 0) D_801C05B9 -= 4;
    if (D_801C05BA != 0) D_801C05BA -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}



// @class: plumbing
// @unstuck(P36): none — MATCH

s32 func_8016BEA0(s32 param_1)
{
    extern s32 func_8016BF50();  // K&R: 0/1 of 1 args (P37 rung D t4_D7)

    int iVar2;
    unsigned short uVar1;

    iVar2 = *(int *)(((int)param_1) + 0x20);
    func_8016BF50();
    uVar1 = *(unsigned short *)(((int)param_1) + 0x10) - 0x18;
    *(unsigned short *)(((int)param_1) + 0x10) = uVar1;
    *(unsigned short *)(iVar2 + 0x1a) = *(unsigned short *)(iVar2 + 0x1a) + uVar1;
    *(unsigned short *)(iVar2 + 0x12) = (*(unsigned short *)(iVar2 + 0x12) + 0x22) & 0xfff;
    ((void (*)(int, void *, void *, int))func_8016BFA8)(((int)param_1), &(*(int *)&D_801C05B4), &(*(int *)&D_801C05B8), iVar2 + 0x18);
    if (*(short *)(iVar2 + 0x1a) < 0) {
        ((void (*)(int))func_80146C3C)(((int)param_1));
    }
}



#include "../shared/ov/func_8016BF34.h"


/* §71 sibling-first: this is the head of the already-matched func_8016C2C4
 * (src/ov_SC03_099/ov_SC03_099_jr_8016AB6C.c L2707) lifted into its own leaf. */

#include "../shared/ov/func_8016BF50.h"



extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801C0540;

void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3) {
    func_8016BFD0(a0, a1, a2, a3, &D_801C0540);
}


// @class: struct
// @unstuck(P36): none — MATCH (95 ins). Keys: (1) 4-byte unaligned copies via `struct{char b[4];}`
//   assignment -> lwl/lwr/swl/swr with reload; (2) 0x40-byte stack buffer `buf` (Mtx_8016BFD0 padded to
//   0x40, not 0x20) sets the frame to 0x70 and lands v1/v2 at sp+0x50/0x58; (3) func_80017714(a4)
//   takes param_5 as an arg -> gcc materializes `addu $a0,$s0,$zero` and stores the 4 zeros via $a0.




void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4) {
    extern void func_80017714(void *arg0);
    extern s32 D_8018A154;
    extern s32 D_8018A15C;
    extern s32 D_8018A164;
    extern s32 D_8018A16C;

    Mtx_8016BFD0 buf;
    Vec3_8016BFD0 v1;
    Vec3_8016BFD0 v2;
    s32 iVar5 = *(s32 *)(a0 + 0x20);

    *(u32 *)((s32)a4 + 0x30) = 0x50000000;
    *(W_8016BFD0 *)((s32)a4 + 0x20) = *(W_8016BFD0 *)a1;
    *(W_8016BFD0 *)((s32)a4 + 0x24) = *(W_8016BFD0 *)a1;
    *(W_8016BFD0 *)((s32)a4 + 0x28) = *(W_8016BFD0 *)a2;
    *(W_8016BFD0 *)((s32)a4 + 0x2c) = *(W_8016BFD0 *)a2;

    v1.x = *(u16 *)(a0 + 6);
    v1.y = *(u16 *)(a0 + 0xa);
    v1.z = *(u16 *)(a0 + 0xe);
    ((void(*)())func_8012EFB8)(&v1, &v1);
    ((void(*)())func_80013F3C)(&buf);
    ((void(*)())func_800123F0)(&buf, (s32)*(s16 *)(iVar5 + 0x12));

    v2.x = *(u16 *)(a3 + 0);
    v2.y = *(u16 *)(a3 + 2);
    v2.z = *(u16 *)(a3 + 4);
    ((void(*)())func_80020F34)(&buf, &v2);

    buf.t[0] = v1.x;
    buf.t[1] = v1.y;
    buf.t[2] = v1.z;
    ((void(*)())func_8012F14C)(&buf, &D_8018A154, (s32)a4);
    ((void(*)())func_8012F14C)(&buf, &D_8018A15C, (s32)a4 + 8);
    ((void(*)())func_8012F14C)(&buf, &D_8018A164, (s32)a4 + 0x10);
    ((void(*)())func_8012F14C)(&buf, &D_8018A16C, (s32)a4 + 0x18);

    *(s16 *)((s32)a4 + 4) = 0;
    *(s16 *)((s32)a4 + 0xc) = 0;
    *(s16 *)((s32)a4 + 0x14) = 0;
    *(s16 *)((s32)a4 + 0x1c) = 0;
    func_80017714(a4);
}




extern void (*D_8018A174[])(void);

void func_8016C14C(void *a0) {
    D_8018A174[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_801465C0(void);
extern void func_80149350(s32 arg0);

void func_8016C188(s32 param)
{
    s32 s1;
    s32 s2;
    u8 *s0;
    u16 buf[3];
    s16 *pBCC;
    s16 *pBD4;
    s32 t34;

    extern void func_80015954(s32, s32);
    extern s32 func_8016C374(s32, s32, s32, s32);
    extern void func_80146C3C(void);
    extern void func_8001CD9C(s32, void *);
    extern void func_800233CC(void *, unsigned short);
    extern u8 D_801C0574[];
    extern s16 D_801C05BC;
    extern s16 D_801C05BE;
    extern s16 D_801C05C0;
    extern s16 D_801C05C4;
    extern s16 D_801C05C6;
    extern s16 D_801C05C8;
    s32 param2;
    param2 = param;

    s1 = param2;
    s2 = ((s32 (*)(void))func_801465C0)();
    *(s32 *)(s1 + 0x20) = s2;
    if (s2 != 0) {
        *(u16 *)(s1 + 0x12) = *(u16 *)(s1 + 0x6);
        *(u16 *)(s1 + 0x16) = *(u16 *)(s1 + 0xA);
        *(u16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0xE);
        t34 = *(s32 *)(s1 + 0x34);
        buf[0] = *(u16 *)(s1 + 0x12);
        buf[1] = *(u16 *)(s1 + 0x16);
        buf[2] = *(u16 *)(s1 + 0x1A);
        ((void (*)(s32, void *, void *))func_80149350)(t34, buf, buf);
        ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
        s0 = D_801C0574;
        ((void (*)(s32, void *))func_8001CD9C)(s2, s0);
        *(s16 *)(s2 + 0x1E) = 0xCCC;
        *(s32 *)(s2 + 4) = *(s32 *)(s2 + 4) | 0x50000000;
        ((void (*)(void *, s32))func_800233CC)(s0, 0x80);
        *(s16 *)(s2 + 0x1A) = 0;
        *(s16 *)(s2 + 0x18) = 0;
        *(s16 *)(s1 + 0x10) = 0;
        pBCC = &D_801C05BC;
        pBD4 = &D_801C05C4;
        *pBCC = 0x20;
        D_801C05BE = 0x20;
        D_801C05C0 = 0;
        *pBD4 = 0xC0;
        D_801C05C6 = 0xC0;
        D_801C05C8 = 0;
        ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, pBCC, pBD4, s0);
        *(u16 *)(s1 + 2) = *(u16 *)(s1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}



// @class: schedule
// @unstuck(P36): none — MATCH (44 ins; pins $s0/$s1 + hoist call-arg into a temp so its load fills the buf-store delay slot)


extern void func_80149350(s32 arg0);
extern void func_80015954(s32 a0, s32 a1);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);

extern u8 D_801C05BC[];
extern u8 D_801C05C4[];
extern u8 D_801C0574[];

void func_8016C2C4(s32 param)
{
    s32 s1;
    s32 s0;
    u16 buf[3];
    s16 v;
    s32 r;
    s32 arg;

    s1 = param;
    s0 = *(s32 *)(s1 + 0x20);
    arg = *(s32 *)(s1 + 0x34);
    buf[0] = *(u16 *)(s1 + 0x12);
    buf[1] = *(u16 *)(s1 + 0x16);
    buf[2] = *(u16 *)(s1 + 0x1a);
    ((void (*)(s32, void *, void *))func_80149350)(arg, buf, buf);
    ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
    v = *(s16 *)(s1 + 0x10) + 0x10;
    *(s16 *)(s1 + 0x10) = v;
    v = *(s16 *)(s0 + 0x1a) + v;
    *(s16 *)(s0 + 0x1a) = v;
    *(s16 *)(s0 + 0x18) = v;
    r = ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, D_801C05BC, D_801C05C4, D_801C0574);
    if (r == 0) {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}


#include "../shared/ov/func_8016C374.h"

// @class: regalloc-order
// @unstuck(P36): none — MATCH (172/172, relocation-masked)



s32 func_8016C49C(s32 param_1_arg) {
    extern s32 VectorNormalSS(void *, void *);
    extern void func_8001CD9C(s32, void *);
    extern void func_8016CF04(s32, s32);
    extern u8 D_801C05D0[];
    extern u8 D_801C0690;

    u16 *param_1 = ((u16 *)param_1_arg);
    int iVar5;
    int iVar6;
    u16 sv[4];
    s32 mat[8];
    short sVar1;

    iVar5 = *(int *)(param_1 + 0x18);
    iVar6 = *(int *)(param_1 + 0x1a);
    param_1[0x14] = *(u16 *)(iVar5 + 0x36);
    if ((*(u32 *)(param_1 + 0x16) & 0x8000) == 0) {
        short iVar4 = 0;
        u16 *psVar3 = (u16 *)&D_8011D030;
        do {
            if (psVar3 != param_1 && *psVar3 == 0x30) {
                ((void(*)(void *))func_80146C3C)(psVar3);
            }
            iVar4 = iVar4 + 1;
            psVar3 = psVar3 + 0x2c;
        } while (iVar4 < 0x1e);
        D_801C05D0[1] = 0xff;
        D_801C05D0[2] = 0x10;
        D_801C05D0[0] = 0x10;
        D_801C05D0[6] = 0;
        D_801C05D0[5] = 0;
        D_801C05D0[4] = 0;
        ((void(*)(void *, s32))func_800233CC)(D_801C05D0, 10);
        sv[0] = *(u16 *)(iVar5 + 6) - *(u16 *)(iVar6 + 6);
        {
            int t = *(u16 *)(iVar6 + 0xa) + 0x28;
            sv[1] = *(u16 *)(iVar5 + 0xa) - t;
        }
        sv[2] = *(u16 *)(iVar5 + 0xe) - *(u16 *)(iVar6 + 0xe);
        VectorNormalSS(sv, sv);
        param_1[3] = *(u16 *)(iVar5 + 6) + ((s16)sv[0] >> 9);
        param_1[5] = *(u16 *)(iVar5 + 0xa) + (((s16)sv[1] >> 9) - 0x28);
        param_1[7] = *(u16 *)(iVar5 + 0xe) + ((s16)sv[2] >> 9);
        ((void(*)(void *))func_800D23D0)(sv);
        sv[0] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, param_1 + 0x1c);
        ((void(*)(void *, s32))func_80016714)(&D_801C0690, 0x620);
        ((s32(*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x32, param_1, 0, 0, 0, 0, *(int *)(param_1 + 0x18));
        sVar1 = 5;
    } else {
        int iVar5b = ((s32(*)())func_801465C0)();
        u32 uVar2;
        if (iVar5b == 0) {
            return;
        }
        func_8001CD9C(iVar5b, D_801C05D0);
        *(u32 *)(iVar5b + 4) |= 0x50000000;
        uVar2 = ((int(*)())rand)();
        sv[0] = (uVar2 & 0x7f) * 8 - 0x80;
        sv[1] = ((uVar2 & 0x7f00) >> 4) - 0x400;
        sv[2] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, mat);
        ((void(*)(void *, void *))func_80048EAC)(param_1 + 0x1c, mat);
        sv[1] = 0;
        sv[0] = 0;
        sv[2] = 0xb;
        ((void(*)(void *, void *, void *))ApplyMatrixSV)(mat, sv, sv);
        param_1[9] = sv[0];
        param_1[0xb] = sv[1];
        param_1[0xd] = sv[2];
        *(int *)(param_1 + 0x10) = iVar5b;
        *(int *)(param_1 + 0xe) = 8;
        func_8016CF04((s32)param_1, 0);
        *(int *)(param_1 + 0x16) = 0;
        sVar1 = param_1[1] + 1;
    }
    do { param_1[1] = sVar1; } while (0);
}



#include "../shared/ov/func_8016C74C.h"

#include "../shared/ov/func_8016C83C.h"


extern short func_8016CBC0(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 D_80126B9C;


void func_8016C998(s32 param_1)
{

    extern s16 D_80126CE0;
    u16 *psVar7;
    s32 r;
    short i;
    extern Slot_998 D_801C0690[];

    psVar7 = *(u16 **)(param_1 + 0x34);
    if (*psVar7 != 1) {
        *(s16 *)(param_1 + 2) = 6;
    }
    func_8016CBC0();
    if (*(s16 *)(param_1 + 0x28) != *(s16 *)(*(s32 *)(param_1 + 0x30) + 0x36)) {
        return;
    }
    if ((D_80126B9C & 0x20) == 0) {
        return;
    }
    if ((*(s32 *)(param_1 + 0x1c) == 0) ||
        (*(s16 *)(param_1 + 0x12) < D_80126CE0)) {
        *(s16 *)(param_1 + 0x12) = D_80126CE0;
        i = 0;
        do {
            if (D_801C0690[i].f0 == 0) {
                goto found;
            }
            i++;
        } while (i < 8);
    found:
        if (i >= 8) {
            return;
        }
        r = func_80146A6C(0x30, psVar7, 0, 0, 0, 0x8000, *(s32 *)(param_1 + 0x30));
        if (r == 0) {
            return;
        }
        D_801C0690[i].f0 = 1;
        *(Blk32_998 *)(r + 0x38) = *(Blk32_998 *)(param_1 + 0x38);
        *(s16 *)(r + 0x2a) = i;
        *(s16 *)(r + 6) = *(s16 *)(param_1 + 6);
        *(s16 *)(r + 0xa) = *(s16 *)(param_1 + 0xa);
        *(s16 *)(r + 0xe) = *(s16 *)(param_1 + 0xe);
        *(s32 *)(param_1 + 0x1c) = 0x10;
    } else {
        *(s32 *)(param_1 + 0x1c) = *(s32 *)(param_1 + 0x1c) - 1;
    }
}



extern void (*D_8018A17C[])(void);

void func_8016CB84(void *a0) {
    D_8018A17C[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_80017758(void *a0, void *a1);
extern Blk20 D_800AE620;
short func_8016CBC0(void)
{

    extern Blk_8016CBC0 D_801C0690[];
  Poly_8016CBC0 p0;
  Poly_8016CBC0 p1;
  Mtx8_8016CBC0 mtx;
  Blk_8016CBC0 *blk;
  Rec_8016CBC0 *sub;
  Rec_8016CBC0 *pv;
  short uVar9;
  short w9;
  unsigned short uc;
  unsigned int a2;
  int col;
  short iVar3;
  short w3;
  short w3b;
  short count;
  short i;
  mtx = (*(Mtx8_8016CBC0 *)&D_800AE620);
  count = 0;
  p1.tag = 0x50000000;
  p0.tag = 0x50000000;
  p1.col[3].b = 0;
  p1.col[3].g = 0;
  p1.col[3].r = 0;
  p1.col[1].b = 0;
  p1.col[1].g = 0;
  p1.col[1].r = 0;
  p0.col[2].b = 0;
  p0.col[2].g = 0;
  p0.col[2].r = 0;
  p0.col[0].b = 0;
  p0.col[0].g = 0;
  p0.col[0].r = 0;
  for (i = 0; i < 8; i++)
  {
    blk = &D_801C0690[i];
    if (blk->f0 != 0)
    {
      sub = blk->ent;
      uVar9 = blk->f1;
      iVar3 = blk->f2;
      col = blk->f3;
      count = count + 1;
      w3 = iVar3 - 1;
      iVar3 = w3;
      if (w3 != (-1))
      {
        do
        {
          pv = &sub[uVar9];
          {
            unsigned int a = pv->h[0];
            unsigned int b;
            p0.v[0].x = a;
            b = pv->h[3];
            p1.v[1].x = b;
            p0.v[1].x = (p1.v[0].x = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[1];
            unsigned int b;
            p0.v[0].y = a;
            b = pv->h[4];
            uc = ((unsigned) (col & 0xFF)) >> 3;
            p1.v[1].y = b;
            p0.v[1].y = (p1.v[0].y = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
            w9 = uVar9 - 1;
            uVar9 = w9;
          }
          {
            unsigned int a = pv->h[2];
            unsigned int b;
            p0.v[0].z = a;
            b = pv->h[5];
            p1.col[0].g = col;
            p0.col[1].g = col;
            p1.col[0].b = uc;
            p0.col[1].b = uc;
            p1.col[0].r = uc;
            p0.col[1].r = uc;
            p1.v[1].z = b;
            p0.v[1].z = (p1.v[0].z = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          if (w9 < 0)
          {
            uVar9 = 0xF;
          }
          pv = &sub[uVar9];
          col = col - 0xF;
          a2 = (unsigned) (col & 0xFF);
          a2 = a2 >> 3;
          {
            unsigned int a = pv->h[0];
            unsigned int b;
            p0.v[2].x = a;
            b = pv->h[3];
            p1.v[3].x = b;
            p0.v[3].x = (p1.v[2].x = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[1];
            unsigned int b;
            p0.v[2].y = a;
            b = pv->h[4];
            p1.v[3].y = b;
            p0.v[3].y = (p1.v[2].y = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          {
            unsigned int a = pv->h[2];
            unsigned int b;
            p0.v[2].z = a;
            b = pv->h[5];
            p1.col[2].g = col;
            p0.col[3].g = col;
            p1.col[2].b = a2;
            p0.col[3].b = a2;
            p1.col[2].r = a2;
            p0.col[3].r = a2;
            p1.v[3].z = b;
            p0.v[3].z = (p1.v[2].z = ((unsigned) (((s16) a) + ((s16) b))) >> 1);
          }
          func_80017758(&p0, &mtx);
          func_80017758(&p1, &mtx);
          w3b = iVar3 - 1;
          iVar3 = w3b;
        }
        while (w3b != (-1));
      }
    }
  }

  return count;
}


/* func_8016CF04 returns short (case 2: 1 if the decremented f2 hit 0, else 0; all other
 * paths return 0 via the addu $v0,$zero,$zero at 0x8016D154). The TU/engine_core.h declare
 * it `void` in 4 DEFINE_ macros + one block-scope decl in func_8016C49C; the real apply is the
 * byte-neutral engine_core.h void->short flip (every caller discards or ptr-casts the return,
 * cf. func_8016D5EC's `(s16)(...)` cast). The //@EDIT lines above are the rtu_match proxy for
 * that flip. Body verified 166/166 in isolation AND in a whole-TU compile w/ the reconciled hdr. */
                /* 4 + 16*12 = 0xC4 stride */

short func_8016CF04(s32 param_1, s32 param_2) {
    extern Blk_8016CF04_8016CF04 D_801C0690[];


    Blk_8016CF04_8016CF04 *p = &D_801C0690[*(short *)(((int)param_1) + 0x2a)];
    u16 rot[4];
    u16 out[4];
    s32 mtx[8];

    switch (((short)param_2)) {
    case 0:
        p->f2 = 0;
        p->f1 = 0;
        p->f3 = 0xf0;
        break;
    case 1:
        p->f1 = p->f1 + 1;
        if ((u8)p->f1 >= 0x10)
            p->f1 = 0;
        if ((u8)p->f2 < 0xf)
            p->f2 = p->f2 + 1;
        break;
    case 2: {
        u8 c = p->f2 - 1;
        p->f2 = c;
        if (c == 0) {
            p->f0 = 0;
            return 1;
        }
        p->f3 = p->f3 - 0xf;
        return 0;
    }
    }

    rot[0] = *(s32 *)(((int)param_1) + 0x10) >> 12;
    rot[1] = *(s32 *)(((int)param_1) + 0x14) >> 12;
    rot[2] = *(s32 *)(((int)param_1) + 0x18) >> 12;
    func_800D23D0(rot);
    RotMatrixYXZ(rot, mtx);
    rot[0] = 9;
    rot[1] = 0;
    rot[2] = 0;
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].a = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].b = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].c = *(u16 *)(((int)param_1) + 0xe) + out[2];
    rot[0] = -rot[0];
    rot[1] = -rot[1];
    ApplyMatrixSV(mtx, rot, out);
    p->ent[(u8)p->f1].d = *(u16 *)(((int)param_1) + 6)   + out[0];
    p->ent[(u8)p->f1].e = *(u16 *)(((int)param_1) + 0xa) + out[1];
    p->ent[(u8)p->f1].g = *(u16 *)(((int)param_1) + 0xe) + out[2];
    return 0;
}




extern void (*D_8018A198[])(void);

void func_8016D19C(void *a0) {
    D_8018A198[*(u16 *)((s32)a0 + 0x2)]();
}







   /* 8 bytes */
                 /* 32 bytes */


extern void func_801465C0(void);
extern void func_800233CC(void*, unsigned short);
extern void func_8001CD9C(int, void*);
extern void func_80147324(int a);
extern int  rand(void);
extern void RotMatrixYXZ(void *a, void *b);
extern void ApplyMatrixSV(void *a, void *b, void *c);

void func_8016D1D8(int param_1) {

    extern u8 D_801C0610[];
    extern u8 D_801C0650[];
    int iVar5;
    int iVar2;
    u16 uVar1;
    unsigned int uVar3;
    short sVar4;
    SVEC_L1 sv;
    MTX_L1 mtx;

    iVar5 = *(int *)(param_1 + 0x34);
    if (*(int *)(param_1 + 0x2c) == 0) {
        D_801C0610[1] = 0xE0;
        D_801C0610[2] = 0xE0;
        D_801C0610[0] = 0xE0;
        D_801C0610[6] = 0;
        D_801C0610[5] = 0;
        D_801C0610[4] = 0;
        iVar5 = ((int (*)(void))func_801465C0)();
        if (iVar5 != 0) {
            int pp;
            *(int *)(param_1 + 0x20) = iVar5;
            ((void (*)(void *, int))func_800233CC)(D_801C0610, 0x28);
            ((void (*)(void *, void *))func_8001CD9C)((void *)iVar5, D_801C0610);
            *(short *)(iVar5 + 0x1a) = 0x1400;
            *(u32 *)(iVar5 + 4) |= 0x50000000;
            pp = *(int *)(param_1 + 0x30);
            *(u16 *)(param_1 + 0x28) = *(u16 *)(pp + 0x36);
            *(u16 *)(param_1 + 0x12) = *(u16 *)(pp + 6);
            *(short *)(param_1 + 0x16) = *(u16 *)(pp + 0xa) - 0x28;
            uVar1 = *(u16 *)(pp + 0xe);
            *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
            *(u16 *)(param_1 + 0x1a) = uVar1;
        }
        *(int *)(param_1 + 0x1c) = 8;
        func_80147324(0x647);
    } else {
        D_801C0650[1] = 0xE0;
        D_801C0650[2] = 0x20;
        D_801C0650[0] = 0x20;
        D_801C0650[5] = 0;
        D_801C0650[6] = 0;
        D_801C0650[4] = 0;
        iVar2 = ((int (*)(void))func_801465C0)();
        if (iVar2 != 0) {
            *(int *)(param_1 + 0x20) = iVar2;
            ((void (*)(void *, int))func_800233CC)(D_801C0650, 0x18);
            ((void (*)(void *, void *))func_8001CD9C)((void *)iVar2, D_801C0650);
            *(u32 *)(iVar2 + 4) |= 0x50000000;
            *(u16 *)(param_1 + 6) = *(u16 *)(iVar5 + 6);
            *(u16 *)(param_1 + 0xa) = *(u16 *)(iVar5 + 0xa);
            *(u16 *)(param_1 + 0xe) = *(u16 *)(iVar5 + 0xe);
            uVar3 = rand();
            sv.vx = ((uVar3 & 0x7F) * 8) - 0x80;
            sv.vy = (uVar3 & 0x7F00) >> 3;
            sv.vz = 0;
            RotMatrixYXZ(&sv, &mtx);
            sv.vy = 0;
            sv.vx = 0;
            sv.vz = 0x240;
            ApplyMatrixSV(&mtx, &sv, &sv);
            *(int *)(param_1 + 0x10) = (int)sv.vx << 0xc;
            *(int *)(param_1 + 0x14) = (int)sv.vy << 0xc;
            sVar4 = (uVar3 & 0x3F0) + 0x200;
            *(int *)(param_1 + 0x18) = (int)sv.vz << 0xc;
            *(short *)(iVar2 + 0x1a) = sVar4;
            *(short *)(iVar2 + 0x18) = sVar4;
            *(int *)(param_1 + 0x1c) = 0x10;
            *(short *)(param_1 + 2) = 2;
        }
    }
}



extern void (*D_8018A1A0[])(void);

void func_8016D428(void *a0) {
    D_8018A1A0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8016D464.h"

#include "../shared/ov/func_8016D4DC.h"

#include "../shared/ov/func_8016D5EC.h"

#include "../shared/ov/func_8016D64C.h"


extern void func_801465C0(void);
extern void func_800233CC(void*, unsigned short);
extern void func_8001CD9C(int, void *);

void func_8016D688(int param_1)
{

    extern unsigned char D_801C0610[];
    int iVar2;
    int iVar3;

    D_801C0610[1] = 0xe0;
    D_801C0610[2] = 0xe0;
    D_801C0610[0] = 0xe0;
    D_801C0610[6] = 0;
    D_801C0610[5] = 0;
    D_801C0610[4] = 0;
    iVar2 = ((int (*)(void))func_801465C0)();
    if (iVar2 != 0) {
        *(int *)(param_1 + 0x20) = iVar2;
        ((void (*)(void *, int))func_800233CC)(D_801C0610, 0x28);
        func_8001CD9C(iVar2, D_801C0610);
        *(unsigned short *)(iVar2 + 0x1a) = 0x1400;
        *(unsigned int *)(iVar2 + 4) = *(unsigned int *)(iVar2 + 4) | 0x50000000;
        iVar3 = *(int *)(param_1 + 0x30);
        *(unsigned short *)(param_1 + 0x28) = *(unsigned short *)(iVar3 + 0x36);
        *(unsigned short *)(param_1 + 0x12) = *(unsigned short *)(iVar3 + 6);
        *(short *)(param_1 + 0x16) = *(unsigned short *)(iVar3 + 0xa) - 0x28;
        *(unsigned short *)(param_1 + 0x1a) = *(unsigned short *)(iVar3 + 0xe);
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    }
    return;
}


#include "../shared/ov/func_8016D778.h"

#include "../shared/ov/func_8016D848.h"

#include "../shared/ov/func_8016D984.h"

#include "../shared/ov/func_8016DA04.h"


// @class: struct
// @unstuck(P36): none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8016DBD8(u8 *a0);
extern void (*D_8018A208[])(int);

void func_8016DA30(int param_1)
{
    ((void (*)(void))func_8016DBD8)();
    D_8018A208[*(unsigned short *)(param_1 + 2)](param_1);
}




// @class: plumbing
// @unstuck(P36): none — MATCH (clean if/else, one call-crossing local; bnez polarity = if(iVar1==0) fall-through)

extern void func_801465C0(void);
extern void func_80146C3C(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

extern u8 D_8018A1AC;
extern u8 D_8018A1B8;

void func_8016DA7C(s32 param_1)
{
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    if (iVar1 == 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    } else {
        *(s32 *)(param_1 + 0x20) = iVar1;
        ((void (*)(s32, s32, s32, s32))func_8001CC3C)(iVar1, (s32)&D_8018A1AC, 0x250, 0x100);
        *(u8 *)(iVar1 + 0x27) = 0x90;
        *(u16 *)(iVar1 + 0x18) = 0x3000;
        *(u16 *)(iVar1 + 0x1a) = 0x4000;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        func_80128EA8(iVar1, param_1 + 0x24, (s32)&D_8018A1B8);
        *(s32 *)(param_1 + 0x10) = 0;
        *(s32 *)(param_1 + 0x14) = 0xfff40000;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
}


#include "../shared/ov/func_8016DB34.h"

#include "../shared/ov/func_8016DBD8.h"


extern s32 D_8011D030;

extern void func_80149374(s32 a0, s32 a1);
extern s32 func_801619D0(void *a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C(void);

void func_8016DC20(s16 *param_1) {

    extern s16 D_801C0CB0;
    extern s16 D_801C0CB4;
    extern u8 D_8018A210[];
    extern u8 D_8018A21C[];
    u16 *psVar1;
    s32 iVar2;
    s32 iVar3;
    s32 iVar4;
    s16 i;
    s16 sp[6];

    i = 0;
    psVar1 = (u16 *)&D_8011D030;
    iVar4 = *(s32 *)((u8 *)param_1 + 0x34);
    do {
        if ((psVar1 != (u16 *)param_1) && (*psVar1 == 0x34)) goto end;
        i = i + 1;
        psVar1 = psVar1 + 0x2c;
    } while (i < 0x1e);
    func_80149374(iVar4, (s32)param_1 + 4);
    iVar2 = func_801619D0((void *)iVar4);
    i = 0;
    if (iVar2 == 0) goto ddb0;
    psVar1 = (u16 *)&D_8011D030;
    do {
        if (*psVar1 == 0x11) goto ddb0;
        i = i + 1;
        psVar1 = psVar1 + 0x2c;
    } while (i < 0x1e);
    func_80146A6C(0x11, param_1, *(s16 *)((u8 *)param_1 + 6),
                  (s16)(*(u16 *)((u8 *)param_1 + 0xa) - 8),
                  *(s16 *)((u8 *)param_1 + 0xe), 0, 0);
    sp[0] = *(u16 *)((u8 *)param_1 + 6);
    sp[1] = *(u16 *)((u8 *)param_1 + 0xa);
    sp[2] = *(u16 *)((u8 *)param_1 + 0xe);
    func_800D20C0(&sp[0], &sp[4], 0);
    sp[5] = 0;
    func_800D23D0(&sp[4]);
    i = 0;
    do {
        iVar3 = func_80146A6C(0x12, param_1, *(s16 *)(iVar4 + 6),
                              *(s16 *)(iVar4 + 0xa), *(s16 *)(iVar4 + 0xe),
                              i, 0);
        if (iVar3 != 0) {
            *(u16 *)(iVar3 + 0x12) = sp[4];
            *(u16 *)(iVar3 + 0x16) = sp[5];
            *(u16 *)(iVar3 + 0x1a) = 0;
        }
        i = i + 2;
    } while (i < 3);
    goto end;
ddb0:
    if (((D_801C0CB0 != *(s16 *)(iVar4 + 6)) || (D_801C0CB4 != *(s16 *)(iVar4 + 0xe))) &&
        (iVar2 = func_800D21C4((s32)param_1, D_8018A210, 0x18), iVar2 != 0)) {
        D_801C0CB0 = *(u16 *)(iVar4 + 6);
        D_801C0CB4 = *(u16 *)(iVar4 + 0xe);
        func_800D1FC8((s32)param_1, 7);
        *(s32 *)((u8 *)param_1 + 0x20) = iVar2;
        *(u16 *)(iVar2 + 0x1a) = 0x3000;
        *(u16 *)(iVar2 + 0x18) = 0x3000;
        *(u8 *)(iVar2 + 0x26) = 0xff;
        *(u32 *)(iVar2 + 4) = *(u32 *)(iVar2 + 4) | 0x50000000;
        func_80128EA8(iVar2, (s32)param_1 + 0x24, (s32)D_8018A21C);
        func_80128ED8((void *)iVar2, (void *)((s32)param_1 + 0x24));
        *(u16 *)((u8 *)param_1 + 2) = *(u16 *)((u8 *)param_1 + 2) + 1;
        return;
    }
end:
    ((void (*)(s16 *))func_80146C3C)(param_1);
}



extern void (*D_8018A23C[])(void);

void func_8016DEA4(void *a0) {
    D_8018A23C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8016DEE0.h"


extern void (*D_8018A244[])(void);

void func_8016DF20(void *a0) {
    D_8018A244[*(u16 *)((s32)a0 + 0x2)]();
}


extern Blk20 D_800AE620;
extern s32 D_8011D030;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_801465C0(void);
extern void func_80146C3C(void);




void func_8016DF5C(s32 param_1)
{
    extern void func_8016E3CC(void *a0);
    extern void RotMatrixY(s32 a0, void *a1);
    extern u8 D_801C0CB8;
    extern u8 D_801C0CB9;
    extern u8 D_801C0CBA;
    extern u8 D_801C0CBC;
    extern u8 D_801C0CBD;
    extern u8 D_801C0CBE;

    s32 iVar8;

    iVar8 = *(s32 *)((u8 *)((void *)param_1) + 0x34);
    if ((*(u32 *)((u8 *)((void *)param_1) + 0x2c) & 0x8000) == 0) {
        unsigned short uVar7 = 0;
        u16 *psVar6 = (u16 *)&D_8011D030;
        s32 iNew;
        s32 base;
        do {
            if (psVar6 != (u16 *)((void *)param_1) && (*psVar6 == 0x41 || *psVar6 == 0x48)) {
                ((void (*)(void *))func_80146C3C)(psVar6);
            }
            uVar7++;
            psVar6 += 0x2c;
        } while (uVar7 < 0x1e);
        iNew = ((s32(*)())func_801465C0)();
        if (iNew == 0) {
            return;
        }
        base = (s32)&D_801C0CB8;
        D_801C0CBA = 0xc0;
        *(u8 *)base = 0xc0;
        D_801C0CB9 = 0;
        D_801C0CBE = 0;
        D_801C0CBD = 0;
        D_801C0CBC = 0;
        ((void(*)(void *, unsigned short))func_800233CC)((void *)base, 0x40);
        func_8001CD50(iNew, base);
        *(s32 *)(iNew + 0x34) = (s32)((u8 *)((void *)param_1) + 0x38);
        *(s16 *)(iNew + 0x1a) = 0;
        *(s16 *)(iNew + 0x18) = 0;
        *(u32 *)(iNew + 4) = *(u32 *)(iNew + 4) | 0x50000000;
        func_8016E3CC(((void *)param_1));
        {
            s32 t10;
            t10 = 0x10;
            *(s32 *)((u8 *)((void *)param_1) + 0x20) = iNew;
            *(s32 *)((u8 *)((void *)param_1) + 0x1c) = t10;
        }
        *(s16 *)((u8 *)((void *)param_1) + 2) = (*(u16 *)((u8 *)((void *)param_1) + 2) + 1);
    } else {
        short asStack_60[20];
        Blk20_8016DF5C localMatrix;
        s32 uVar2;

        asStack_60[0] = 0;
        asStack_60[1] = 0;
        asStack_60[2] = 0x20;
        localMatrix = (*(Blk20_8016DF5C*)&D_800AE620);
        uVar2 = ((s32(*)())rand)();
        RotMatrixY((uVar2 & 0x7f00) >> 3, &localMatrix);
        ApplyMatrixSV(&localMatrix, asStack_60, asStack_60);
        *(s16 *)((u8 *)((void *)param_1) + 6) = D_80126B5E + asStack_60[0];
        *(s16 *)((u8 *)((void *)param_1) + 0xa) = D_80126B62 - ((u16)uVar2 & 0x3f);
        *(s16 *)((u8 *)((void *)param_1) + 0xe) = D_80126B66 + asStack_60[2];
        *(Blk20_8016DF5C *)((u8 *)((void *)param_1) + 0x38) = *(Blk20_8016DF5C *)((u8 *)iVar8 + 0x38);
        *(s32 *)((u8 *)((void *)param_1) + 0x2c) = 0x1000;
        *(s32 *)((u8 *)((void *)param_1) + 0x30) = 0xff;
        *(s32 *)((u8 *)((void *)param_1) + 0x1c) = 0x10;
        *(s16 *)((u8 *)((void *)param_1) + 2) = (4);
    }
}


#include "../shared/ov/func_8016E1CC.h"

#include "../shared/ov/func_8016E26C.h"

#include "../shared/ov/func_8016E2E8.h"

#include "../shared/ov/func_8016E358.h"

#include "../shared/ov/func_8016E3CC.h"

#include "../shared/ov/func_8016E460.h"


extern void (*D_8018A298[])(void);

void func_8016E5B8(void *a0) {
    D_8018A298[*(u16 *)((s32)a0 + 0x2)]();
}


#include "../shared/ov/func_8016E5F4.h"

#include "../shared/ov/func_8016E688.h"

#include "../shared/ov/func_8016E6E4.h"

#include "../shared/ov/func_8016E728.h"

#include "../shared/ov/func_8016E778.h"

// @class: regalloc-order
// @unstuck(P36): none — MATCH (74 ins); register pin $s2 forces &prim into a saved reg (§17)

                 /* 0x08 */
     /* 0x20 */

typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;


void func_8016E7C8(int param_1, short *param_2, unsigned int *param_3)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern void func_80016ED4(void *a0);
    extern SVECTOR_8016E7C8 D_8018A258[4];
    extern s32 D_8018A278;
    extern s32 D_8018A280;
    extern s32 D_8018A288;
    extern s32 D_8018A290;

    Prim_8016E7C8 prim;
    MATRIX_8016E7C8 m;
    SVECTOR_8016E7C8 tmp;
    Prim_8016E7C8 *pp;   /* $s2 — force &prim into a saved reg */

    ((void (*)(void *, void *))func_80017DC4)(param_2, &m);
    m.t[0] = *(short *)(param_1 + 6);
    m.t[1] = *(short *)(param_1 + 10);
    m.t[2] = *(short *)(param_1 + 14);
    func_8004914C(&m);
    func_800491AC(&m);
    pp = &prim;
    RotTransSV(&D_8018A258[0], pp, &tmp);
    RotTransSV(&D_8018A258[1], &prim.v[1], &tmp);
    RotTransSV(&D_8018A258[2], &prim.v[2], &tmp);
    RotTransSV(&D_8018A258[3], &prim.v[3], &tmp);
    prim.v[0].vz = 3;
    prim.f5 = 0x50000000;
    prim.f0 = D_8018A278;
    prim.f1 = D_8018A280;
    prim.f2 = D_8018A288;
    prim.f3 = D_8018A290;
    prim.f4 = *param_3;
    prim.f6 = 0x27;
    func_80016ED4(pp);
}



#include "../shared/ov/func_8016E8F0.h"

#include "../shared/ov/func_8016E918.h"

// @class: struct
// @unstuck(P36): none — MATCH (36/36 ins, match_one relocation-masked)



typedef void (*Handler)(struct Entry_8016E95C *);


s32 func_8016E95C() {
    extern Handler D_8018A2D8[];

    struct Entry_8016E95C *p;
    for (p = ((struct Entry_8016E95C *)&D_80115218); p < &((struct Entry_8016E95C *)&D_80115218)[4]; p++) {
        if (p->f0 != 0) {
            D_8018A2D8[p->f1](p);
        }
    }
}




/* @class: regalloc (non-coalescing delay-slot copy) + sched (load-temp hoist)
 * @unstuck(P36): none — MATCH (53/53 ins, match_one AND rtu_match in the real TU).
 *
 * Two levers, both from the cookbook:
 *
 * 1. §52a "non-coalescing delay-slot copy" + §17 zero-reg-copy (the load-bearing one).
 *    The target holds `p[0]-1` in TWO callee-saved regs: $s0 (the array index, later
 *    destroyed in place by `sll $s0,$s0,1`) and $s4 (the value stored to p[3]), created
 *    by `addu $s4,$s0,$zero` sitting in the DELAY SLOT of `jal func_800D2CA8`. A plain
 *    C `c = i;` is destroyed by cse.c canon_reg head-promotion (measured: 50 ins, -3),
 *    and every #APP-asm spelling of the copy is INELIGIBLE for a delay slot (measured:
 *    51 ins, -2 — tried `__asm__("":"=r"(c):"0"(i))`, a real-opcode
 *    `__asm__("addu %0,%1,$0")`, and the §52b RC-7 post-copy second-set barrier
 *    `c=i; __asm__("":"=r"(c):"0"(c))`; all three collapse or lose the slot).
 *    Only the `$0`-add — `register u32 zr __asm__("$0"); c = i + zr;` — emits a bare
 *    `addu` with no asm insn, so reorg can sink it into the call's delay slot.
 *    NOTE for ×138 propagation: this is a ZERO-REGISTER pin, not an allocation pin —
 *    it constrains no real value. family_sweep's §42e "skip pinned exemplar" guard is
 *    documented over-conservative (§86; the SIGABRT was our own extract_unit macro-drop,
 *    fixed in Phase 27), so this exemplar should still sweep.
 *
 * 2. Free-floating load temp for a scheduler hoist (§52a-adjacent, idiom 7).
 *    With the p+6 store written as one statement the sched2 list scheduler hoists
 *    `lbu $v0,1($a0)` ahead of `sb $s4,3($a0)` and sinks the D_8018A2C4 lui/addu/lhu
 *    chain (8 mismatched, same 53-ins multiset). Splitting the load into its own
 *    statement `h = D_8018A2C4[i];` placed BEFORE `p[2] = 0` (exactly what the Ghidra
 *    seed showed) puts the lhu chain right after `sh $v0,4($a0)` → 0.
 *
 * Data typing: D_8018A2A8 is a WORD array (`sll $v0,$s0,2`; its element is dereferenced
 * as a buffer by func_80024054) => u8 *[]. D_8018A2C0 is byte-indexed (`lbu`, no shift)
 * => u8[]. D_8018A2C4 is halfword-indexed (`sll $s0,$s0,1` + `lhu`) => u16[].
 * `*(s16 *)(p + 4) = -0xD7` emits `addiu $v0,$zero,-0xD7`; 0xFF29 as a u16 would not.
 */


extern s32 func_800D2CA8(s32 a0, s32 a1);
extern void func_800D2D10(s32 a0, s32 a1, void *a2, s32 a3);
extern s32 func_80024054(void *a0, void *a1);
extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016E9EC(u8 *p)
{

    extern u8 *D_8018A2A8[];
    extern u8 D_8018A2C0[];
    extern u16 D_8018A2C4[];
    s16 i;
    u8 *buf;
    u8 off;
    s32 h;

    i = p[0] - 1;
    off = D_8018A2C0[i];
    buf = D_8018A2A8[i];
    func_800D2D10((func_800D2CA8(p[3], 0x1C)), 1, buf + off, 0);
    func_80024054(buf, p + 8);
    p[3] = (i + 0);
    *(s16 *)(p + 4) = -0xD7;
    h = D_8018A2C4[i];
    p[2] = 0;
    *(u16 *)(p + 6) = h;
    p[1] = p[1] + 1;
    ((void (*)(u8 *, s32))func_8016EC0C)(p, 0x80);
}



// @class: struct
// @unstuck(P36): none — MATCH (31/31 ins, match_one verified)

extern u16 D_8018A2CC[];
extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EAC0(Wave *param_1)
{
    unsigned char bVar1;

    param_1->f4 = param_1->f4 + D_8018A2CC[param_1->f2];
    ((void (*)(void *, int))func_8016EC0C)(param_1, 0x80);
    bVar1 = param_1->f2 + 1;
    param_1->f2 = bVar1;
    if (5 < bVar1) {
        param_1->f2 = 0x20;
        param_1->f1 = param_1->f1 + 1;
    }
}



// @class: loose-typing
// @unstuck(P36): none — MATCH (u8 v + 0xFF emits addiu 0xFF; v-1 would emit -1/0xffff)

extern u8 D_8018A2BC[];
extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EB3C(s32 p) {
    u8 v;

    ((void (*)(s32, s32))func_8016EC0C)(p, D_8018A2BC[*(u8 *)(p + 2) & 3]);

    v = *(u8 *)(p + 2);
    *(u8 *)(p + 2) = v + 0xFF;
    if (v == 0) {
        *(u8 *)(p + 2) = 5;
        *(u8 *)(p + 1) = *(u8 *)(p + 1) + 1;
    }
}



// @class: struct
// @unstuck(P36): none — MATCH (25 ins). %lo-fold via extern u16 D_8018A2CC[]; predecrement emitted as +0xFF (u8 promote→sb low byte), not -1.

extern u16 D_8018A2CC[];

extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EBA8(u8 *param_1)
{
    u8 c;

    *(u16 *)(param_1 + 4) =
        *(u16 *)(param_1 + 4) - D_8018A2CC[param_1[2]];
    ((void (*)(u8 *, int))func_8016EC0C)(param_1, 0x80);
    c = param_1[2];
    param_1[2] = c + 0xFF;
    if (c == 0) {
        param_1[0] = 0;
    }
}



extern void func_80017B98(void *a0);
extern u8 D_8018A2B8[];

void func_8016EC0C(s32 a0, s32 a1)
{
    /* §100 draft-LOCAL type: a file-scope typedef is an EXEMPLAR-ONLY bank — extract_unit/
       remap_hseq carry only the BODY, so every sibling fails `T8016EC0C undeclared`
       (measured on ov_SC01_000). Block scope travels with the body; byte-neutral. */
 /* 0x1C */
    T8016EC0C s;
    u16 *p;
    s32 x;
    s32 y;
    s32 v;

    s.r = s.g = s.b = a1;
    s.u18 = D_8018A2B8[*(u8 *)(a0 + 3)];
    s.u0C = 0x640;
    s.u0E = 0x1C8;
    s.u14 = 0;
    s.u08 = 0x28;
    s.u0A = 8;
    x = *(u16 *)(a0 + 4);
    s.x = x + 0x10;
    y = *(u16 *)(a0 + 6);
    s.u04 = 0x10;
    s.y = y;
    func_80017B98(&s);
    s.u08 = 8;
    y += 0xA;
    p = (u16 *)(a0 + 8);
    while (*p != 0xFFFF) {
        v = *p;
        switch (v) {
        case 0x1850:
        case 0x1858:
            s.x = x + 4;
            s.y = y - 7;
            break;
        case 0x3872:
            x += 2;
            p++;
            continue;
        default:
            s.x = x;
            s.y = y;
            x += 8;
            break;
        }
        s.u0C = *(u8 *)p + 0x500;
        s.u0E = (*p >> 8) + 0x100;
        p++;
        func_80017B98(&s);
    }
}


#include "../shared/ov/func_8016ED6C.h"

#include "../shared/ov/func_8016ED8C.h"

#include "../shared/ov/func_8016EDBC.h"

#include "../shared/ov/func_8016EDEC.h"

#include "../shared/ov/func_8016EE40.h"

#include "../shared/ov/func_8016EE94.h"

#include "../shared/ov/func_8016EF78.h"

#include "../shared/ov/func_8016EFA8.h"

#include "../shared/ov/func_8016EFC8.h"

#include "../shared/ov/func_8016F094.h"

// @class: plumbing
// @unstuck(P36): none — MATCH

#include "../shared/ov/func_8016F0AC.h"




/* RECONCILE NOTE (uc3) — the body is byte-unchanged from uc2; only the declaration
 * environment moved.  The gate error was
 *     jr_8016AB6C.c:4183 conflicting types for func_8016F0E4 || :4089 previous declaration
 * :4089 was THIS definition; :4183 is the `extern void func_8016F0E4(void);` carried inside
 * DEFINE_func_8016F4C4() (src/shared/engine_core.h:22579), which the host TU instantiates at
 * ov_SC01_077_jr_8016AB6C.c:4136 — i.e. AFTER the definition, so it is a hard error, not the
 * mere warning produced by the earlier block-scope decl in func_8016F0AC (TU:4047).
 * Byte-true signature is `void (u8 *)`; the fleet canon is `void (void)` — a PARAM/ARITY
 * disagreement on func_8016F0E4 ITSELF.
 *
 * ESCAPE TAKEN: §37/§124 ASM-LABEL ALIAS (escape 2, T0 draft-only, zero tracked-file edits).
 * The C identifier is aF8016F0E4 so this TU declares func_8016F0E4 exactly once (the macro's
 * own `extern void`), while the emitted SYMBOL is func_8016F0E4.  Both existing callers already
 * launder through a cast or take no args, so neither is perturbed:
 *   - func_8016F0AC (TU:4047-4049) casts:  ((void (*)(void *))func_8016F0E4)(&D_80126B58);
 *   - DEFINE_func_8016F4C4 calls func_8016F0E4() with 0 args against its own (void) prototype.
 * cc1-proven: preprocess+compile of the real TU with this body spliced in is free of any
 * func_8016F0E4 diagnostic (the pre-existing unrelated warnings in the TU are unchanged).
 *
 * This SUPERSEDES uc2's //@EDIT de-macroize plan (§65b) and its T2 engine_core.h alternative
 * (§75c) — neither is needed; nothing outside this unit changes, so the bank travels to the
 * 137 siblings as a plain unit (carry the alias DECLARATION line with it — §124 trap 2).
 */

#include "../shared/ov/func_8016F0E4.h"


#include "../shared/ov/func_8016F14C.h"

#include "../shared/ov/func_8016F1AC.h"


// @class: schedule
// @unstuck(P36): none — MATCH

extern s32 D_8018A2E8;
extern s32 D_80126B58;
extern s16 currentLocationId;

s32 func_8016F1C4(void) {
    s32 *p;
    s32 cur;
    s32 loc;
    s32 v;
    s32 *base = &D_80126B58;

    p = &D_8018A2E8;
    cur = *p;
    if (cur != 0) {
        loc = currentLocationId;
        p = p + 1;
        for (;;) {
            if (loc == cur) {
                return 1;
            }
            cur = *p;
            p = p + 1;
            if (cur == 0) {
                break;
            }
        }
    }
    v = base[0x7E];
    if (((v & 0x80FFFFFF) != 0) && ((v & 0x10000000) != 0)) {
        return 0;
    }
    return base[0x7E] & 0x80FFFFFF;
}


#include "../shared/ov/func_8016F250.h"

#include "../shared/ov/func_8016F264.h"

#include "../shared/ov/func_8016F288.h"

#include "../shared/ov/func_8016F2A8.h"

#include "../shared/ov/func_8016F2C8.h"

#include "../shared/ov/func_8016F2EC.h"

#include "../shared/ov/func_8016F30C.h"

#include "../shared/ov/func_8016F330.h"

#include "../shared/ov/func_8016F350.h"

#include "../shared/ov/func_8016F374.h"

#include "../shared/ov/func_8016F388.h"

#include "../shared/ov/func_8016F398.h"

#include "../shared/ov/func_8016F410.h"

#include "../shared/ov/func_8016F44C.h"

#include "../shared/ov/func_8016F470.h"

#include "../shared/ov/func_8016F494.h"

#include "../shared/ov/func_8016F4C4.h"

#include "../shared/ov/func_8016F4F4.h"

#include "../shared/ov/func_8016F4FC.h"

#include "../shared/ov/func_8016F540.h"

#include "../shared/ov/func_8016F578.h"

#include "../shared/ov/func_8016F5B0.h"

#include "../shared/ov/func_8016F5E0.h"

#include "../shared/ov/func_8016F610.h"

#include "../shared/ov/func_8016F648.h"

#include "../shared/ov/func_8016F680.h"

#include "../shared/ov/func_8016F6B0.h"


extern void (*D_8018A360[])(void);

void func_8016F6E0(void *a0) {
    D_8018A360[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8016F71C.h"

#include "../shared/ov/func_8016F764.h"


extern void (*D_8018A368[])(void);

void func_8016F798(void *a0) {
    D_8018A368[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8016F7D4.h"

#include "../shared/ov/func_8016F804.h"


extern void (*D_8018A370[])(void);

void func_8016F834(void *a0) {
    D_8018A370[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8016F870.h"

#include "../shared/ov/func_8016F8AC.h"


extern void (*D_8018A378[])(void);

void func_8016F8E4(void *a0) {
    D_8018A378[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8016F920.h"

#include "../shared/ov/func_8016F95C.h"


extern void (*D_8018A380[])(void);

void func_8016F9C4(void *a0) {
    D_8018A380[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8016FA00.h"

#include "../shared/ov/func_8016FA44.h"


extern void (*D_8018A388[])(void);

void func_8016FA84(void *a0) {
    D_8018A388[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8016FAC0.h"

#include "../shared/ov/func_8016FB10.h"

#include "../shared/ov/func_8016FB50.h"


extern void (*D_8018A394[])(void);

void func_8016FB7C(void *a0) {
    D_8018A394[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8016FBB8.h"

#include "../shared/ov/func_8016FC24.h"

#include "../shared/ov/func_8016FC64.h"


extern void (*D_8018A3A0[])(void);

void func_8016FC90(void *a0) {
    D_8018A3A0[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8016FCCC.h"

#include "../shared/ov/func_8016FD08.h"

#include "../shared/ov/func_8016FD7C.h"


extern void (*D_8018A3AC[])(void);

void func_8016FDB4(void *a0) {
    D_8018A3AC[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8016FDF0.h"

#include "../shared/ov/func_8016FE2C.h"

#include "../shared/ov/func_8016FE78.h"

#include "../shared/ov/func_8016FED0.h"


extern void (*D_8018A3BC[])(void);

void func_8016FF30(void *a0) {
    D_8018A3BC[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8016FF6C.h"

#include "../shared/ov/func_8016FFA8.h"


extern void (*D_8018A3CC[])(void);

void func_8016FFDC(void *a0) {
    D_8018A3CC[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170018.h"

#include "../shared/ov/func_80170068.h"

#include "../shared/ov/func_801700B8.h"

#include "../shared/ov/func_80170100.h"


extern void (*D_8018A3D4[])(void);

void func_80170150(void *a0) {
    D_8018A3D4[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8017018C.h"

#include "../shared/ov/func_801701C8.h"


extern void (*D_8018A3DC[])(void);

void func_80170240(void *a0) {
    D_8018A3DC[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8017027C.h"

#include "../shared/ov/func_801702B8.h"


extern void (*D_8018A3E4[])(void);

void func_801702FC(void *a0) {
    D_8018A3E4[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170338.h"

#include "../shared/ov/func_80170374.h"


extern void (*D_8018A3EC[])(void);

void func_801703E0(void *a0) {
    D_8018A3EC[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8017041C.h"

#include "../shared/ov/func_8017044C.h"


extern void (*D_8018A3F4[])(void);

void func_801704B0(void *a0) {
    D_8018A3F4[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_801704EC.h"

#include "../shared/ov/func_8017051C.h"


extern void (*D_8018A3FC[])(void);

void func_80170548(void *a0) {
    D_8018A3FC[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170584.h"

#include "../shared/ov/func_801705C0.h"


extern void (*D_8018A404[])(void);

void func_801705F8(void *a0) {
    D_8018A404[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170634.h"

#include "../shared/ov/func_80170670.h"


extern void (*D_8018A40C[])(void);

void func_801706AC(void *a0) {
    D_8018A40C[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_801706E8.h"

#include "../shared/ov/func_80170718.h"


extern void (*D_8018A414[])(void);

void func_80170748(void *a0) {
    D_8018A414[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170784.h"

#include "../shared/ov/func_801707D4.h"


extern void (*D_8018A41C[])(void);

void func_80170810(void *a0) {
    D_8018A41C[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8017084C.h"


#include "../shared/ov/func_801708B0.h"


#include "../shared/ov/func_80170928.h"

#include "../shared/ov/func_80170970.h"

#include "../shared/ov/func_801709B8.h"

#include "../shared/ov/func_80170A00.h"

#include "../shared/ov/func_80170A48.h"

#include "../shared/ov/func_80170A90.h"


extern void (*D_8018A424[])(void);

void func_80170AD8(void *a0) {
    D_8018A424[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170B14.h"

#include "../shared/ov/func_80170B48.h"

#include "../shared/ov/func_80170B90.h"


extern void (*D_8018A42C[])(void);

void func_80170BD8(void *a0) {
    D_8018A42C[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170C14.h"

#include "../shared/ov/func_80170C44.h"


extern void (*D_8018A434[])(void);

void func_80170C74(void *a0) {
    D_8018A434[*(u8 *)((s32)a0 + 0x215)]();
}


#include "../shared/ov/func_80170CB0.h"


#include "../shared/ov/func_80170CF0.h"



extern void (*D_8018A43C[])(void);

void func_80170D68(void *a0) {
    D_8018A43C[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170DA4.h"

#include "../shared/ov/func_80170DE0.h"


extern void (*D_8018A444[])(void);

void func_80170E34(void *a0) {
    D_8018A444[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170E70.h"

#include "../shared/ov/func_80170EAC.h"


extern void (*D_8018A44C[])(void);

void func_80170EFC(void *a0) {
    D_8018A44C[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170F38.h"

#include "../shared/ov/func_80170F74.h"


extern void (*D_8018A454[])(void);

void func_80170FB0(void *a0) {
    D_8018A454[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80170FEC.h"

#include "../shared/ov/func_80171028.h"


extern void (*D_8018A45C[])(void);

void func_80171064(void *a0) {
    D_8018A45C[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_801710A0.h"

#include "../shared/ov/func_801710DC.h"


extern void (*D_8018A464[])(void);

void func_80171120(void *a0) {
    D_8018A464[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8017115C.h"

#include "../shared/ov/func_8017118C.h"


extern void (*D_8018A46C[])(void);

void func_801711C0(void *a0) {
    D_8018A46C[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_801711FC.h"

#include "../shared/ov/func_80171238.h"


extern void (*D_8018A474[])(void);

void func_80171260(void *a0) {
    D_8018A474[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_8017129C.h"

#include "../shared/ov/func_80171384.h"


extern void (*D_8018A47C[])(void);

void func_801714E4(void *a0) {
    D_8018A47C[*(u8 *)((s32)a0 + 0x216)]();
}


#include "../shared/ov/func_80171520.h"

#include "../shared/ov/func_8017162C.h"

#include "../shared/ov/func_801716AC.h"

#include "../shared/ov/func_801717A0.h"

#include "../shared/ov/func_801717F4.h"

#include "../shared/ov/func_80171824.h"

#include "../shared/ov/func_80171854.h"

#include "../shared/ov/func_80171884.h"

#include "../shared/ov/func_801718AC.h"

#include "../shared/ov/func_80171904.h"

#include "../shared/ov/func_80171928.h"

#include "../shared/ov/func_8017196C.h"

#include "../shared/ov/func_8017197C.h"

#include "../shared/ov/func_80171990.h"

#include "../shared/ov/func_801719A4.h"

#include "../shared/ov/func_80171A04.h"

#include "../shared/ov/func_80171A10.h"

#include "../shared/ov/func_80171A1C.h"

#include "../shared/ov/func_80171A34.h"

#include "../shared/ov/func_80171A44.h"

#include "../shared/ov/func_80171A58.h"

#include "../shared/ov/func_80171A6C.h"

#include "../shared/ov/func_80171A80.h"

#include "../shared/ov/func_80171A88.h"

#include "../shared/ov/func_80171AB0.h"

#include "../shared/ov/func_80171B10.h"

#include "../shared/ov/func_80171B44.h"
