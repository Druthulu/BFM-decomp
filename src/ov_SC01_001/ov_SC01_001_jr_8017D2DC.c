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
extern u8 D_80185D90;
extern u8 D_80185D00;
extern u8 D_80185CDC;
extern u8 D_80185CB8;
extern u8 D_80185D6C;
extern u8 D_80185D48;
extern u8 D_80185D24;
extern u8 D_80185C94;
extern void func_80145934(void);
extern u8 D_80185E20;
extern u8 D_80185DFC;
extern u8 D_80185DD8;
extern u8 D_80185DB4;
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
extern unsigned char D_80185218[];
extern unsigned char D_80185248[];
extern unsigned char D_80185298[];
extern unsigned char D_801852C8[];
extern unsigned char D_801852F8[];
extern void func_80145EE8(s32 param_1);
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_80146074(void);
extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0(void);
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
extern void (*D_80185348[])(void *);
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
extern s32 D_80185410[];
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
extern u8 D_80185498[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_801854A0;
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
extern int D_801EC800;
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
extern s32 D_801EC804;
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
extern s32 D_801854D0;
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
extern void (*D_80185578[])(void);
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
extern void (*D_8018559C[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018558C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_801855B0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_801855BC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801855CC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801855E4[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801855D4;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801855F8[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_80185614[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_80185604;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80185628[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018563C[])(void);
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
extern s32 D_80185650;
extern void (*D_80185678[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80185658;
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
extern int (*D_801856C4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801856C8[])(void);
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
extern unsigned short D_80185B2C[];
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
extern void (*D_80185B3C[])(void);
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
extern int D_801EC838;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80185B64[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80185B44;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80185B54;
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
extern void (*D_80185BA4[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80185BAC[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80185B78;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80185BB8[])(void);
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
extern u8 D_80185B88;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801EC840;
extern s32 D_801EC84C;
extern s32 D_801EC850;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80185BF4[])(s32 *);
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
extern s32 D_80185BC8[];
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
extern s32 D_801EC848;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80185E44[])(void);
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
extern char D_80185C64[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80185EE8[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018603C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80185E58;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80186044[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80185E68;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80185E88;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018604C[])(void);
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
extern void (*D_80186074[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80186080[])(void);
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
extern void (*D_80185EF4[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80186124;
extern void func_8015D380(s32 a0);
extern unsigned char D_80185208[];
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
extern unsigned char D_80186138[];
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
extern s8 D_80186174[];
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
extern u16 D_801861BC;
extern u16 D_801861BE;
extern u16 D_801861C0;
extern s32 D_801861C4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_801861CC;
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
extern int D_80185ED8;
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
extern unsigned int D_80186250[];
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
extern void (*D_80186300[])(void);
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
extern u16 D_80186330[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80186394;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801EC858[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_801863B8[])(void);
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
extern int D_801EC8B0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80186400[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801863F0;
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
extern char D_801EBF2C[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80186408[])(void);
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
extern void (*D_8018645C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80186424;
extern s16 D_80186458;
extern s16 D_80186456;
extern s16 D_80186454;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80186468[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801EC910;
extern u8 D_801EC911;
extern u8 D_801EC912;
extern u8 D_801EC913;
extern u8 D_801EC914;
extern u8 D_801EC915;
extern u8 D_801EC916;
extern u8 D_801EC917;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80186478[])(void);
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
extern s32 D_801EC950;
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
extern void (*D_801864BC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80186538[];
extern s32 D_80186558[];
extern u8 D_801865D4[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801865F4[];
extern u8 D_80186614[];
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
extern void (*D_801866B0[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018672C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801EBF3C;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80186738[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80186740[])(void);
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
extern void (*D_80186808[])(void);
extern void func_80166618(void *a0);
extern void (*D_80186818[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80186828[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80186834[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80186794[];
extern u8   D_801867A8[];
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
extern void (*D_8018684C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80186854[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018685C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80186864[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018686C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80186874[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018687C[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80186930[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80186938[])(void);
extern void func_80169F00(void *a0);
extern char D_801868E8[];
extern char D_801868A8[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80186970[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018697C[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801869C4[])(void);
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
extern void (*D_80186A40[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801ECC70;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80186A34[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80186A78[];
extern unsigned short D_80186A80[];
extern unsigned short D_80186A88[];
extern unsigned char D_801ECC78[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801ECC70;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80186A90[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801ECDAC;
extern M2C_UNK D_801ECDB0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801ECD38;
extern void (*D_80186AC0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801ECDB4[];
extern u8 D_801ECDBC[];
extern u8 D_801ECD6C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80186AC8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80186AE4[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80186AEC[])(void);
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
extern void (*D_80186B54[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80186AF8;
extern u8 D_80186B04;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80186B88[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80186B90[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80186BE4[])(void);
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
extern u16 D_80186C18[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80186C08[];
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
extern s32 D_80186C34;
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
extern void (*D_80186CAC[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80186CB4[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80186CBC[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80186CC4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80186CCC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80186CD4[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80186CE0[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80186CEC[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80186CF8[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80186D08[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80186D18[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80186D20[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80186D28[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80186D30[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80186D38[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80186D40[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80186D48[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80186D50[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80186D58[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80186D60[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80186D68[])(void);
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
extern void (*D_80186D70[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80186D78[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80186D80[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80186D88[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80186D90[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80186D98[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80186DA0[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80186DA8[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80186DB0[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80186DB8[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80186DC0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80186DC8[])(void);
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
extern void (*D_80186E0C[])(void);
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
extern M2C_UNK D_80186DD0;
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
extern void (*D_80186E3C[])(void);
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
extern void (*D_80186E78[])(void);
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
extern void (*D_80186ED0[])();
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
extern void (*D_80186EE0[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80186EE8[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80187050[])();
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
extern void (*D_8018705C[])();
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
extern M2C_UNK D_801EC184;
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
extern s16 D_801F3150;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801ED4F0;
extern short D_801F31C4;
extern void func_80178CBC(s32 arg0, s32 arg1);
extern void func_80178D18(void);
extern s32 func_80178D40(s32 arg0, s32 arg1);
extern void func_80179B28(s32 a0);
extern void func_80179B74(u16 *p);
extern void func_80179D30(u16 *a0);
extern void func_80179D78(u16 *a0);
extern void func_80179B74(u16 *p);
extern void func_80179DCC(short a0);
extern void func_80179DF8(void);
extern void func_80179E1C(short a0);
extern void func_80179E48(s16 a0);
extern void func_80179E74(s16 a0);
extern void func_80179EA0(u16 *a0);
extern void func_80179B74(u16 *p);
extern void func_80179EE8(short a0);
extern void func_80179F14(s16 a0, s16 a1);
extern void func_80179F44(void);
extern void func_80179F6C(short a0);
extern void func_80179F98(u16 *a0);
extern void func_80179FEC(u16 *a0);
extern void func_8017A040(u16 *a0);
extern s32 D_801ED91C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801ED944;
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
extern s16 D_801ED900;
extern s32 func_8017A3B0(void);
extern short D_801ED93C;
extern short D_801ED938;
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
extern s16 D_801ED904;
extern u16 D_801ED984;
extern u16 D_801ED986;
extern u16 D_801ED988;
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
extern s16 D_801ED97C;
extern s16 D_801ED97E;
extern s16 D_801ED980;
extern s16 D_801ED974;
extern s16 D_801ED976;
extern s16 D_801ED978;
extern void func_8017B7A8(void);
extern s16 D_801ED994;
extern s16 D_801ED996;
extern s16 D_801ED998;
extern s16 D_801ED99C;
extern s16 D_801ED99E;
extern s16 D_801ED9A0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801ED98C;
extern short D_801ED98E;
extern short D_801ED990;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801ED924;
extern SV4 D_801ED92C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801ED94C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801ED948)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80187238[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BEBC(s32 arg0);
extern void (*D_80187294[])(void);
extern void func_8017CD9C(void *a0);
extern s32 func_800167F0(s32 arg0);
extern s32 func_8017CE24(void);
extern void (*D_8018729C[])(void);
extern void func_8017CE48(void *a0);
extern void (*D_801872B8[])(void);
extern void func_8017D060(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017D13C(s32 param_1, s16 *param_2);
extern s32 func_8017D2D4(void);
/* ==== end §8b carried decl layer ==== */


/* func_8017D2DC @ ov_SC01_001 (ov_SC01_001_jr_8017BEBC) -- 1,586 ins, 125-case jr switch
 * over the scene-script state D_801F313C (jtbl_801EC46C).  Behemoth #7.
 *
 * STATUS: **match_one MATCH (1586 ins)** -- candidate gate only (masks jal/HI16/LO16, never links).
 *   .venv/bin/python tools/match_one.py func_8017D2DC \
 *       --c .run/giants/s21_func_8017D2DC_b1.c \
 *       --asm-subdir asm/ov_SC01_001/nonmatchings/ov_SC01_001_jr_8017BEBC
 *   => MATCH (1586 ins)
 * NOT YET BANKED.  This is a `jr` function => §81 carve chain REQUIRED before the real gate can
 * agree.  See .run/giants/s21_8017D2DC_report.md for the (favourable) carve picture and the
 * §17a-1 decl notes.
 *
 * PIN-FREE.  No stack locals (frame 0x18 = 0x10 arg-save + $s0 + $ra).
 *
 * THE TWO LEVERS THAT CLOSED IT (drop-one ablated, base = this file):
 *   L1  the 8 `D_801ED9F4 > K` timeouts must compare against a BLOCK-LOCAL VARIABLE holding K
 *       (`s32 lim = K; ... if (lim < D_801ED9F4)`), not a literal.  A literal in ANY spelling
 *       (`> K`, `>= K+1`, `K < x`, `!(x <= K)`, `++x > K`, early-return) folds to
 *       `slti x,K+1` + `bnez`; only a pseudo on the LEFT of `slt` gives the target's
 *       `li K; slt K,x; beqz`.  This is §78's literal-position law on a COMPARISON.
 *       ablation: one site back to the literal -> 8 mismatched.
 *   L2  in case 95 that `lim` must live in an INNER block AFTER the call-bearing `if`, or its
 *       live range spans the calls, it becomes callee-saved ($s0) and the `li` hoists.  §76.
 *       ablation: `lim` at case-95 top -> 8 mismatched.
 *   plus `pv` (function-scope) -> ablation 1587 ins / 1204 mismatched, and `case 124:` -> 1.
 *
 * THE RELATIVE (§71, and it is in this very overlay):
 *   src/ov_SC01_001/ov_SC01_001_jr_80178D40.c :: func_80178D40 -- 890 ins, 94-case jr switch,
 *   MATCHED, with a 13-point recipe comment above it.  Levers taken from it verbatim:
 *     #1  NO status variable.  Every case stores `D_801ED9F4 = 0; D_801F313C++;` DIRECTLY;
 *         .L8017EB5C/.L8017EB64/.L8017EB70 are a jump2 CROSS-JUMP merge of those stores
 *         (the merge lives at the tail of case 123, the last case that has one).
 *     #2  after-switch = `func_8017EBCC(); func_80182D04(D_801ED9F0);` -- the out-of-range
 *         default lands there with NO explicit `default:` label.
 *     #7  per-case temporaries are block-local (there are none here).
 *     #8  stack locals in slot order -- there are none; only `pv` (a pointer, $s0).
 *
 * DECODE FACTS (byte-derived):
 *   - the switch bound is `sltiu 0x7D` and the table has 125 entries => max case value is 124,
 *     so `case 124:` EXISTS with an empty body (its entry == the default/after-switch label).
 *     Cases 10/11/12 are ABSENT (their entries are the default label -- indistinguishable
 *     from an empty case, so they are simply omitted).
 *   - cases 19,21,27,31,51,53,57,59,87,89 have the bare tail as their WHOLE body; cross_jump
 *     reduced each block to `j .L8017EB5C` and jump.c's ADDR_VEC follow_jumps pass then
 *     retargeted the table entry straight at .L8017EB5C.
 *   - `pv` (= &D_80126948) is a FUNCTION-SCOPE pointer: the target materialises the address in
 *     the prologue ($s0, callee-saved, live across `jal func_80174E9C` in case 1) and case 1
 *     stores through it with `sw $v0,0x8($s0)`.  An inline `*(s32*)&D_80126948[8]` would emit
 *     lui+sw at the use site instead.
 *   - the head is `pad = func_800149E0(0);` FIRST (unconditional call), then
 *     `if (D_801F313C < 0x7B && (pad & 0x840)) D_801F313C = 0x7B;`  -- the `&&` gives exactly
 *     slti/beqz then andi/beqz; the call cannot be inside the `&&` or it would sit after the
 *     first branch.
 *   - the `pv=` insn is scheduled AFTER the jal in the target: a pseudo set from a SYMBOL_REF
 *     carries no dependence on a CALL_INSN in sched.c, so it is free to fill the load-delay of
 *     `lw $v1,D_801F313C`.  Nothing in the source expresses that; leave the decl first.
 *
 * NEW OBSERVATION worth a cookbook entry (§88 candidate) -- CROSS_JUMP WILL NOT MERGE A COMMON
 * SUFFIX THAT CONTAINS A CALL.  This function contains ~34 BYTE-IDENTICAL 6-insn blocks
 * (`jal func_8017EC18; beqz $v0,.L8017EB5C; j .L8017EB78`) and case 66's sub-0/sub-2 are two
 * byte-identical 12-insn blocks -- NONE of them are merged, while every call-free common tail
 * (.L8017EB5C/EB64/EB70, .L8017E9A0/E9AC/E9B4, .L8017E06C, .L8017DAF0, .L8017E804) IS merged.
 * => write the repeated `if (func_8017EC18() == 0) {...}` cases out longhand; they stay separate.
 */

#include "common.h"

/* ---- shared (resident) callees ------------------------------------------------ */
extern s32  func_800149E0(s32 a0);            /* no fleet canon -- free choice */
extern void func_80016450(s32 a0, s32 a1);    /* no fleet canon -- free choice */
extern int  func_8001AAA0(void);              /* TU canon: (void); called with 1 arg -> §17a-1 cast */
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800D0C48(s32 a0);
extern void func_800D1724(s32 a0);
extern void func_8013C9C4(void *a0);
extern s32  func_8013D13C(void);              /* fleet canon: (void); called with 1 arg -> §17a-1 cast */

/* ---- overlay-local callees ---------------------------------------------------- */
extern void func_80174E9C(s32 a0);
extern void func_8017EBA4();      /* §17a-1 PAIR: the TU DEFINES `void func_8017EBA4(void)` (a
                                   * pass-through: its body calls func_8013767C with no args, so
                                   * $a0 flows straight through).  A `(void *)` prototype here is a
                                   * hard conflict with that definition; the K&R `()` form is
                                   * compatible in either order and the CALLS carry the cast. */
extern void func_8017EBCC(void);
extern s32  func_8017EC18(void);
extern void func_8017EC28(s32 a0);
extern void func_8017F1C8();
extern void func_8017F1F8(void);
extern void func_80181834(void);
extern void func_80181A28(void);
extern void func_80181A4C(void);
extern void func_80181E04(void);
extern void func_80182238(void);
extern s32  func_80182284(void);
extern void func_801824EC(s32 a0);
extern s32  func_8018275C(void);
extern void func_80182A48();
extern void func_80182B68(s32 a0);
extern void func_80182B9C(s32 a0);
extern void func_80182BD0(s32 a0);
extern void func_80182C10(void);
extern void func_80182D04(s32 a0);
extern void func_80182EB0();
extern void func_801831EC(void);
extern void func_80183748();

/* ---- scalars ------------------------------------------------------------------ */
extern u16 D_800B99D8;
extern u8  D_80126948[];
extern s32 D_80188A90;
extern s32 D_801ED9CC;
extern s32 D_801ED9D4;
extern s32 D_801ED9D8;
extern s32 D_801ED9E0;
extern s32 D_801ED9E4;
extern s32 D_801ED9E8;
extern s32 D_801ED9F0;
extern s32 D_801ED9F4;
extern s32 D_801EDA20;
extern s32 D_801EDA38;
extern s32 D_801EDA3C;
extern s32 D_801EDA40;
extern s32 D_801F3034;
extern s32 D_801F313C;

/* ---- address-taken blobs ------------------------------------------------------ */
extern u8 D_80183FB4[];
extern u8 D_80187268[];
extern u8 D_80188B14[];
extern u8 D_80188B34[];
extern u8 D_80188B54[];
extern u8 D_80188C5C[];
extern u8 D_80188CF8[];
extern u8 D_80188D10[];
extern u8 D_80188F54[];
extern u8 D_80188FC0[];
extern u8 D_80189018[];
extern u8 D_80189064[];
extern u8 D_80189088[];
extern u8 D_801890EC[];
extern u8 D_80189168[];
extern u8 D_801891A4[];
extern u8 D_80189208[];
extern u8 D_8018922C[];
extern u8 D_80189264[];
extern u8 D_8018928C[];
extern u8 D_801892D4[];
extern u8 D_80189318[];
extern u8 D_801893A0[];
extern u8 D_801893C8[];
extern u8 D_80189420[];
extern u8 D_80189458[];
extern u8 D_801894C0[];
extern u8 D_80189524[];
extern u8 D_8018957C[];
extern u8 D_801895B8[];
extern u8 D_80189618[];
extern u8 D_80189678[];
extern u8 D_801896D8[];
extern u8 D_80189758[];
extern u8 D_80189874[];
extern u8 D_801898F8[];
extern u8 D_8018996C[];
extern u8 D_80189A18[];
extern u8 D_80189A58[];
extern u8 D_80189B34[];
extern u8 D_80189B64[];
extern u8 D_80189BD4[];
extern u8 D_80189C28[];
extern u8 D_80189C54[];
extern u8 D_80189D2C[];
extern u8 D_80189D6C[];
extern u8 D_80189DDC[];
extern u8 D_80189E4C[];
extern u8 D_80189E8C[];
extern u8 D_801C357C[];
extern u8 D_801C565C[];
extern u8 D_801C5BC8[];
extern u8 D_801C5E94[];
extern u8 D_801C5EC0[];
extern u8 D_801C62A4[];
extern u8 D_801C9584[];
extern u8 D_801CC838[];
extern u8 D_801CC864[];
extern u8 D_801CC890[];
extern u8 D_801CC8BC[];
extern u8 D_801CC8E8[];
extern u8 D_801CC914[];
extern u8 D_801CC940[];
extern u8 D_801CD7F8[];
extern u8 D_801CD824[];
extern u8 D_801CD850[];
extern u8 D_801CDBA8[];
extern u8 D_801CDBD4[];
extern u8 D_801CE38C[];
extern u8 D_801CE3B8[];
extern u8 D_801CE3E4[];
extern u8 D_801CE410[];
extern u8 D_801CE43C[];
extern u8 D_801CE468[];
extern u8 D_801CE494[];
extern u8 D_801CE4C0[];
extern u8 D_801CE4EC[];
extern u8 D_801CE518[];
extern u8 D_801CE544[];
extern u8 D_801CF6D4[];
extern u8 D_801CF700[];
extern u8 D_801CF72C[];
extern u8 D_801CF758[];
extern u8 D_801CF784[];
extern u8 D_801CF7B0[];
extern u8 D_801CFCAC[];
extern u8 D_801D113C[];
extern u8 D_801D1938[];
extern u8 D_801D2470[];
extern u8 D_801D2534[];


void func_8017D2DC(void)
{
    s32 *pv = (s32 *)D_80126948;
    s32 pad = func_800149E0(0);

    if (D_801F313C < 0x7B && (pad & 0x840)) {
        D_801F313C = 0x7B;
    }
    func_8017F1F8();

    switch (D_801F313C) {
    case 0:
        D_801ED9CC = 0;
        D_801EDA20 = 0;
        D_801ED9D4 = 0;
        D_801ED9D8 = 1;
        D_801ED9F0 = 0;
        func_80181A28();
        func_80182C10();
        func_80183748(D_80188B14);
        D_80188A90 = 0;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 1:
        D_801ED9E4 = 0x2D;
        D_801ED9E8 = 0x1E;
        func_80174E9C((s32)D_80188C5C);
        pv[2] = 0x100;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 2:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        D_801ED9E8--;
        if (D_801ED9E8 == 0) {
            func_8002D4C8(0xB0A, 0);
            func_8013C9C4(D_80183FB4);
            func_80182EB0(D_80188CF8, 3);
        }
        break;
    case 3:
        func_8017F1C8(D_801C357C);
        func_8017EC28(1);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 4: {
        s32 lim = 0x8A;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            ((void (*)(void *))func_8017EBA4)(D_80188F54);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 5:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 6: {
        s32 lim = 0x1E;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            ((void (*)(void *))func_8017EBA4)(D_80188FC0);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 7:
        if (func_8017EC18() == 0) {
            func_8017EC28(2);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 8:
        ((void (*)(void *))func_8017EBA4)(D_80189018);
        func_8017F1C8(D_801C565C);
        D_801ED9E4 = 0x30;
        D_801ED9F4 = 0;
        D_801F313C++;
        /* fallthrough */
    case 9:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_80182BD0(3);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C = 0xD;
            func_8017EC28(3);
        }
        break;
    case 13:
        func_8017F1C8(D_801C5BC8);
        ((void (*)(void *))func_8017EBA4)(D_80189064);
        func_80182C10();
        func_80183748(D_80188B34);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 14:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 15:
        func_8017F1C8(D_801C5E94);
        ((void (*)(void *))func_8017EBA4)(D_80189088);
        func_8017EC28(0xF);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 16:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 17:
        func_8017F1C8(D_801C5EC0);
        func_8017EC28(0x12);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 18: {
        s32 lim = 0x46;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            D_801ED9F4 = 0;
            D_801F313C = 0x21;
        }
        break;
    }
    case 19:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 20:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 21:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 22:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 23:
        ((void (*)(void *))func_8017EBA4)(D_801891A4);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 24:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 25:
        func_8017F1C8(D_801C62A4);
        func_8017EC28(4);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 26:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 27:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 28:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 29:
        func_8017F1C8(D_801C9584);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 30:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 31:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 32:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 33:
        ((void (*)(void *))func_8017EBA4)(D_801890EC);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 34:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 35:
        ((void (*)(void *))func_8017EBA4)(D_80189168);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 36:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 37:
        func_8017F1C8(D_801CC838);
        func_8017EC28(9);
        func_80182BD0(3);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 38:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 39:
        func_8017F1C8(D_801C62A4);
        func_8017EC28(4);
        ((void (*)(void *))func_8017EBA4)(D_80189208);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 40:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 41:
        func_80182BD0(1);
        func_8017F1C8(D_801CC864);
        func_8017EC28(0xB);
        func_800D0C48(1);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 42: {
        s32 lim = 0x1E;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 43:
        func_8017F1C8(D_801CC890);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 44: {
        s32 lim = 0x1E;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 45:
        func_8017F1C8(D_801CC8BC);
        D_801ED9E0 = 0;
        D_801F3034 = 0;
        func_80181834();
        func_80182238();
        func_8002D4C8(0xB0C, 0);
        D_801ED9E4 = 0x1E;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 46:
        switch (D_801F3034) {
        case 0:
            if (D_801ED9E0 == 0 && (D_800B99D8 & 1) &&
                ((s32 (*)(s32))func_8013D13C)(9) == 0) {
                D_801ED9E0 = 1;
            }
            if (func_80182284() == 0) {
                func_80181A4C();
            } else {
                D_801ED9E4--;
                if (D_801ED9E4 == 0) {
                    func_80016450(0xFF, 0);
                    func_8002D4C8(0xB0D, 0);
                    D_801ED9E4 = 2;
                    D_801F3034++;
                }
            }
            break;
        case 1:
            func_80016450(0xFF, 0);
            D_801ED9E4--;
            if (D_801ED9E4 == 0) {
                func_8013C9C4(D_80183FB4);
                func_801824EC(0);
                func_801824EC(1);
                func_801824EC(2);
                D_801ED9E4 = 8;
                D_801F3034++;
            }
            break;
        case 2:
            D_801ED9E4--;
            if (D_801ED9E4 == 0) {
                func_801824EC(0);
                func_801824EC(1);
            }
            if (func_8018275C() != 0) {
                func_80182A48();
                func_80016450(0xFF, 0);
                D_801EDA38 = 1;
                D_801ED9F4 = 0;
                D_801F313C++;
            }
            break;
        }
        func_80181E04();
        break;
    case 47:
        func_8017F1C8(D_801CC8E8);
        func_80183748(D_80188B54);
        D_801ED9F0 = 0;
        func_80182B9C(2);
        func_8017EC28(0x2424);
        D_801EDA38 = 1;
        ((int (*)(s32))func_8001AAA0)(0x90);
        D_801ED9E4 = 0xFF;
        D_801F3034 = 0;
        D_801ED9F4 = 0;
        D_801F313C++;
        /* fallthrough */
    case 48:
        switch (D_801F3034) {
        case 0:
            ((s32 (*)(s32))func_8013D13C)(1);
            func_80016450(*(u8 *)&D_801ED9E4, 0);
            D_801ED9E4 -= 4;
            if (D_801ED9E4 < 0) {
                ((void (*)(void *))func_8017EBA4)(D_8018922C);
                D_801EDA3C = 0;
                D_801EDA40 = 0;
                D_801F3034++;
            }
            break;
        case 1:
            if (func_8017EC18() == 0) {
                func_8017F1C8(D_801CC914);
                ((void (*)(void *))func_8017EBA4)(D_80189264);
                func_801831EC();
                D_801F3034++;
            }
            break;
        case 2:
            func_801831EC();
            if (func_8017EC18() == 0) {
                D_801ED9F4 = 0;
                D_801F313C++;
            }
            break;
        }
        break;
    case 49:
        func_8017F1C8(D_801CC940);
        ((void (*)(void *))func_8017EBA4)(D_8018928C);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 50:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C = 0x37;
        }
        break;
    case 51:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 52:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 53:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 54:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 55:
        ((void (*)(void *))func_8017EBA4)(D_801892D4);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 56:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C = 0x3D;
        }
        break;
    case 57:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 58:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 59:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 60:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 61:
        func_8017F1C8(D_801CD7F8);
        func_8017EC28(0x3031);
        ((void (*)(void *))func_8017EBA4)(D_80189318);
        func_80182B68(2);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 62:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 63:
        ((void (*)(void *))func_8017EBA4)(D_801893A0);
        func_8017EC28(0x30B);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 64:
        if (func_8017EC18() == 0) {
            func_8017EC28(0x100);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 65:
        func_80182B68(3);
        ((void (*)(void *))func_8017EBA4)(D_801893C8);
        func_8017EC28(0x3131);
        D_801F3034 = 0;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 66:
        switch (D_801F3034) {
        case 0:
            if (func_8017EC18() == 0) {
                D_801ED9F4 = 0;
                D_801F3034 = 0;
                D_801F313C++;
            }
            break;
        case 1:
            func_8017EC28(0xD);
            func_8017F1C8(D_801C62A4);
            D_801F3034++;
            break;
        case 2:
            if (func_8017EC18() == 0) {
                D_801ED9F4 = 0;
                D_801F3034 = 0;
                D_801F313C++;
            }
            break;
        }
        break;
    case 67:
        switch (D_801F3034) {
        case 0:
            func_8017F1C8(D_801CD824);
            ((void (*)(void *))func_8017EBA4)(D_80189420);
            func_8017EC28(0x10);
            func_80182C10();
            D_801F3034++;
            break;
        case 1:
            if (func_8017EC18() == 0) {
                D_801F3034++;
            }
            break;
        case 2:
            func_8017F1C8(D_801CD850);
            func_80182B9C(1);
            func_8017EC28(0x11);
            D_801ED9E4 = 0;
            D_801F3034++;
            break;
        case 3:
            if (D_801ED9E4 != 0) {
                D_801ED9F4 = 0;
                D_801F313C++;
            }
            break;
        }
        break;
    case 68: {
        s32 lim = 0x1E;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 69:
        func_8017F1C8(D_801CDBA8);
        ((void (*)(void *))func_8017EBA4)(D_80189458);
        func_8017EC28(0x3636);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 70:
        if (func_8017EC18() == 0) {
            func_8017EC28(0x3737);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 71:
        func_8017F1C8(D_801CDBD4);
        func_80182BD0(0);
        ((void (*)(void *))func_8017EBA4)(D_801894C0);
        D_801ED9E4 = 0x64;
        D_801ED9E8 = 0x28;
        D_801ED9F4 = 0;
        D_801F313C++;
        /* fallthrough */
    case 72:
        D_801ED9E8--;
        if (D_801ED9E8 == 0) {
            func_80182BD0(7);
        }
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_80182BD0(2);
            func_8017EC28(0x37B);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 73:
        func_8017F1C8(D_801CE38C);
        func_8017EC28(0x38A);
        ((void (*)(void *))func_8017EBA4)(D_80189524);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 74:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 75:
        func_8017F1C8(D_801CE3B8);
        func_8017EC28(0x38B);
        ((void (*)(void *))func_8017EBA4)(D_8018957C);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 76:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 77:
        func_8017F1C8(D_801CE3E4);
        func_8017EC28(0x3939);
        ((void (*)(void *))func_8017EBA4)(D_801895B8);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 78:
        if (func_8017EC18() == 0) {
            func_8017EC28(0x4040);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 79:
        func_8017F1C8(D_801CE410);
        ((void (*)(void *))func_8017EBA4)(D_80189618);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 80:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 81:
        func_8017F1C8(D_801CE43C);
        func_8017EC28(0x4141);
        ((void (*)(void *))func_8017EBA4)(D_80189678);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 82:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 83:
        func_8017F1C8(D_801CE468);
        func_80182B9C(1);
        func_8017EC28(0x4242);
        ((void (*)(void *))func_8017EBA4)(D_801896D8);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 84:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C = 0x5B;
        }
        break;
    case 85:
        func_8017EC28(0x4747);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 86:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 87:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 88:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 89:
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 90:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 91:
        func_8017F1C8(D_801CE494);
        ((void (*)(void *))func_8017EBA4)(D_80189758);
        func_8017EC28(0x4747);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 92:
        if (func_8017EC18() == 0) {
            func_8017EC28(0x4848);
            func_8017F1C8(D_801CE4C0);
            ((void (*)(void *))func_8017EBA4)(D_80189874);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 93:
        if (func_8017EC18() == 0) {
            func_8017EC28(0x4949);
            D_801ED9E4 = 0x14;
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 94:
        func_8017F1C8(D_801CE4EC);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 95:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_8013C9C4(D_80183FB4);
            func_8002D4C8(0xB0B, 0);
            func_80182EB0(D_80188D10, 7);
        }
        {
            s32 lim = 0x3C;
            D_801ED9F4++;
            if (lim < D_801ED9F4) {
                ((void (*)(void *))func_8017EBA4)(D_801898F8);
                D_801ED9F4 = 0;
                D_801F313C++;
            }
        }
        break;
    case 96:
        func_8017EC28(0x5050);
        func_8017F1C8(D_801CE518);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 97:
        if (func_8017EC18() == 0) {
            func_8017F1C8(D_801CE544);
            ((void (*)(void *))func_8017EBA4)(D_8018996C);
            func_8017EC28(0x5151);
            D_801ED9E4 = 0xAA;
            D_801ED9E8 = 0x12C;
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 98:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_8017EC28(0x5151B);
        }
        D_801ED9E8--;
        if (D_801ED9E8 == 0) {
            func_8017EC28(0x5151C);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 99:
        D_801ED9F0 = 1;
        func_80182B9C(0);
        ((void (*)(void *))func_8017EBA4)(D_80189A18);
        func_8017EC28(0x5252);
        D_801ED9E4 = 0x13;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 100:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_8017F1C8(D_801CF6D4);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 101:
        func_8017F1C8(D_801CF700);
        func_8017EC28(0x53A);
        ((void (*)(void *))func_8017EBA4)(D_80189A58);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 102:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 103:
        func_8017F1C8(D_801CF72C);
        func_8017EC28(0x53B);
        ((void (*)(void *))func_8017EBA4)(D_80189B34);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 104:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 105:
        func_8017F1C8(D_801CF758);
        ((void (*)(void *))func_8017EBA4)(D_80189B64);
        func_8017EC28(0x53C);
        D_801ED9E4 = 0;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 106:
        switch (D_801ED9E4) {
        case 0:
            if (func_8017EC18() == 0) {
                func_8017EC28(0x5454);
                D_801ED9E8 = 0x10;
                D_801ED9E4++;
            }
            break;
        case 1:
            D_801ED9E8--;
            if (D_801ED9E8 == 0) {
                D_801ED9F0 = 2;
                func_8002D4C8(0xC8D, 0);
                D_801ED9E8 = 0x10;
                D_801ED9E4++;
            }
            break;
        case 2:
            D_801ED9E8--;
            if (D_801ED9E8 == 0) {
                func_8017EC28(0x54B);
                D_801ED9F4 = 0;
                D_801F313C++;
            }
            break;
        }
        break;
    case 107:
        func_8017F1C8(D_801CF784);
        func_8017EC28(0x5555);
        ((void (*)(void *))func_8017EBA4)(D_80189BD4);
        D_801ED9F4 = 0;
        D_801ED9E4 = 0x59;
        D_801F313C++;
        break;
    case 108:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_8017EC28(0x55B);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 109:
        func_8017F1C8(D_801CF7B0);
        func_8017EC28(0x5656);
        ((void (*)(void *))func_8017EBA4)(D_80189C28);
        func_80182C10();
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 110:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 111:
        func_8017F1C8(D_801CFCAC);
        func_8017EC28(0x57A);
        ((void (*)(void *))func_8017EBA4)(D_80189C54);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 112:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 113:
        func_8017F1C8(D_801D113C);
        ((void (*)(void *))func_8017EBA4)(D_80189D2C);
        D_801ED9E4 = 0x1E;
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 114:
        D_801ED9E4--;
        if (D_801ED9E4 == 0) {
            func_8017EC28(0x57B);
        }
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 115: {
        s32 lim = 0x1E;
        D_801ED9F4++;
        if (lim < D_801ED9F4) {
            func_8017F1C8(D_801D1938);
            func_8017EC28(0x5858);
            ((void (*)(void *))func_8017EBA4)(D_80189D6C);
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    }
    case 116:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 117:
        func_8017F1C8(D_801D2470);
        func_8017EC28(0x5959);
        func_80182BD0(3);
        ((void (*)(void *))func_8017EBA4)(D_80189DDC);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 118:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 119:
        ((void (*)(void *))func_8017EBA4)(D_80189E4C);
        func_8017F1C8(D_801D2534);
        func_80182C10();
        func_8017EC28(0x6060);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 120:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 121:
        ((void (*)(void *))func_8017EBA4)(D_80189E8C);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 122:
        if (func_8017EC18() == 0) {
            D_801ED9F4 = 0;
            D_801F313C++;
        }
        break;
    case 123:
        func_800D1724((s32)D_80187268);
        D_801ED9F4 = 0;
        D_801F313C++;
        break;
    case 124:
        break;
    }

    func_8017EBCC();
    func_80182D04(D_801ED9F0);
}


extern s32 func_8013767C(s32 a0);
extern s32 D_801EDA20;

void func_8017EBA4(void) {
    D_801EDA20 = (void *)((s32 (*)(void))func_8013767C)();
}


extern s32 D_801EDA20;
extern s32 func_801399F0(s32);
extern void func_80139914(s32);

void func_8017EBCC(void)
{
    if (D_801EDA20 != 0) {
        if (func_801399F0(D_801EDA20) != 0) {
            func_80139914(D_801EDA20);
            D_801EDA20 = 0;
        }
    }
}


extern s32 D_801EDA20;
    s32 func_8017EC18(void) {
        return D_801EDA20 != 0;
    }


extern s32 D_801EDA08;
extern s32 D_801EDA0C;
extern s32 D_801EDA10;
extern s32 D_801EDA14;
extern s32 D_801EDA18;
extern s32 D_801EDA1C;

void func_8017EC28(s32 param_1) {
    switch (param_1) {
    case 0:
        break;
    case 0x5151B:
        D_801EDA14 = param_1;
        break;
    case 1:
        D_801EDA10 = param_1;
        D_801EDA0C = param_1;
        D_801EDA14 = param_1;
        break;
    case 0x2424:
        D_801EDA14 = param_1;
        break;
    case 3:
        D_801EDA10 = param_1;
        D_801EDA14 = 4;
        D_801EDA18 = 2;
        D_801EDA1C = 2;
        D_801EDA0C = param_1;
        break;
    case 4:
        D_801EDA10 = param_1;
        D_801EDA14 = 5;
        D_801EDA1C = 3;
        D_801EDA18 = 3;
        D_801EDA0C = param_1;
        break;
    case 0xB:
        D_801EDA10 = 0xA;
        break;
    case 0x3031:
        D_801EDA10 = 8;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        break;
    case 0x30B:
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA10 = param_1;
        break;
    case 2:
        D_801EDA10 = param_1;
        break;
    case 5:
        D_801EDA10 = param_1;
        break;
    case 6:
        D_801EDA10 = param_1;
        break;
    case 7:
        D_801EDA10 = param_1;
        break;
    case 9:
        D_801EDA10 = param_1;
        break;
    case 0x37B:
        D_801EDA10 = param_1;
        break;
    case 0x3131:
        D_801EDA10 = param_1;
        break;
    case 0x35C:
        D_801EDA08 = 0x35C;
        break;
    case 0x38A:
        D_801EDA10 = param_1;
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        break;
    case 0x3737:
        D_801EDA10 = param_1;
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        break;
    case 0x5858:
        D_801EDA10 = param_1;
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        break;
    case 0x5151:
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        break;
    case 0x4141:
        D_801EDA08 = param_1;
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        break;
    case 0x4242:
        D_801EDA08 = param_1;
        D_801EDA10 = param_1;
        D_801EDA0C = param_1;
        break;
    case 0xD:
        D_801EDA10 = 0xC;
        break;
    case 0x4747:
        D_801EDA18 = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x54B:
        D_801EDA08 = param_1;
        break;
    case 0x35B:
        D_801EDA08 = param_1;
        break;
    case 0x35D:
        D_801EDA08 = param_1;
        break;
    case 0x3636:
        D_801EDA08 = param_1;
        break;
    case 0x4848:
        D_801EDA08 = param_1;
        break;
    case 0x4949:
        D_801EDA08 = param_1;
        break;
    case 0x5151C:
        D_801EDA08 = 0x51C;
        break;
    case 0x53C:
        D_801EDA08 = 0x5252;
        break;
    case 0x55B:
        D_801EDA10 = 0x5555;
        break;
    case 0x38B:
        D_801EDA10 = param_1;
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x57A:
        D_801EDA10 = param_1;
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x57B:
        D_801EDA10 = param_1;
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x3939:
        D_801EDA10 = param_1;
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x5656:
        D_801EDA10 = param_1;
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x53A:
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x53B:
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x4040:
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x5050:
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x5252:
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x5454:
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x5555:
        D_801EDA14 = param_1;
        D_801EDA1C = param_1;
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x5959:
        D_801EDA10 = param_1;
        D_801EDA08 = param_1;
        break;
    case 0x6060:
        D_801EDA10 = param_1;
        D_801EDA0C = param_1;
        break;
    case 0xF:
        D_801EDA18 = 6;
        D_801EDA1C = 6;
        break;
    case 0x10:
        D_801EDA08 = 1;
        break;
    case 0x11:
        D_801EDA08 = 2;
        D_801EDA10 = 0x3333;
        break;
    case 0x12:
        D_801EDA10 = 0xE;
        D_801EDA14 = 8;
        D_801EDA18 = 7;
        D_801EDA1C = 7;
        D_801EDA0C = 7;
        break;
    case 0x100:
        D_801EDA18 = param_1;
        D_801EDA0C = param_1;
        break;
    }
}


extern void func_80174E9C(s32 a0);
extern s32 D_801ED9DC;
extern s32 D_801ED9D4;

void func_8017F1C8(s32 arg0) {
    D_801ED9DC = 0;
    D_801ED9D4 = arg0;
    func_80174E9C(arg0);
}


extern s32 D_801ED9D4;
extern s32 func_80174ED4(void);

void func_8017F1F8(void)
{
    s16 sVar1;

    if ((D_801ED9D4 != 0) && (sVar1 = func_80174ED4(), sVar1 != 0)) {
        D_801ED9D4 = 0;
    }
}


extern void func_8017D2DC(void);
extern void (*D_80188DD0[])(void *);
extern void func_80182C58(void);

void func_8017F238(void *a0)
{
    func_8017D2DC();
    D_80188DD0[*(u16 *)((u8 *)a0 + 2)](a0);
    func_80182C58();
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_80143994(s32 a0, s32 a1);

extern s32 D_8019BD38;
extern s32 D_80187898;
extern s32 D_801EDA10;

void func_8017F28C(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    s0 = a0;
    v0 = func_8012C1B8();
    *(s32 *)(s0 + 0x20) = v0;
    s1 = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        func_8001C214(s1, (s32)&D_8019BD38);
        func_8001D0E8(s1, 0x7FFF, 0x7FFF);
        func_8012A828(s0, (s32)&D_80187898);
        func_80143994(s0, 0x3000);
        {
            u16 tmp = *(u16 *)(s0 + 0x2);
            D_801EDA10 = 0;
            *(u16 *)(s0 + 0x2) = tmp + 1;
        }
    }
}


extern void func_8012A828(s32 a0, s32 a1);
extern void func_80182B60(s32 *a0, s32 a1);
extern s32 D_801EDA10;
extern s32 D_80187898;
extern s32 D_80187940;
extern s32 D_801879B8;
extern s32 D_80187A60;
extern s32 D_80187AD0;
extern s32 D_80187B18;
extern s32 D_80187BC0;
extern s32 D_80187C48;
extern s32 D_80187D90;
extern s32 D_80187E60;
extern s32 D_801D78C4;
extern s32 D_801D8B88;
extern s32 D_801D8EAC;
extern s32 D_801D9CD8;
extern s32 D_801D9DD4;
extern s32 D_801D9360;
extern s32 D_801DAB54;
extern s32 D_801DB140;
extern s32 D_801DB504;
extern s32 D_801DB518;
extern s32 D_801DB554;
extern s32 D_801DB5E0;
extern s32 D_801DB68C;
extern s32 D_801DB960;
extern s32 D_801DBAAC;
extern s32 D_801DBAC0;
extern s32 D_801DBAD4;
extern s32 D_801DBB40;

void func_8017F328(s32 arg0)
{
    s32 s0 = arg0;

    switch (D_801EDA10) {
    case 0:
        break;
    case 1:
        func_8012A828(s0, (s32)&D_80187898);
        func_80182B60((s32 *)s0, (s32)&D_801D78C4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 2:
        func_8012A828(s0, (s32)&D_80187940);
        func_80182B60((s32 *)s0, (s32)&D_801D8B88);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 3:
        func_8012A828(s0, (s32)&D_80187898);
        func_80182B60((s32 *)s0, (s32)&D_801D8EAC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 4:
        func_8012A828(s0, (s32)&D_801879B8);
        func_80182B60((s32 *)s0, (s32)&D_801D9CD8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 5:
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 6:
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 7:
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 8:
        func_8012A828(s0, (s32)&D_80187B18);
        func_80182B60((s32 *)s0, (s32)&D_801D9DD4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 9:
        func_8012A828(s0, (s32)&D_80187A60);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 10:
        func_8012A828(s0, (s32)&D_80187AD0);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x3333:
        func_8012A828(s0, (s32)&D_80187898);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x30B:
        func_8012A828(s0, (s32)&D_80187898);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x3131:
        func_8012A828(s0, (s32)&D_80187E60);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x3737:
        func_8012A828(s0, (s32)&D_80187898);
        func_80182B60((s32 *)s0, (s32)&D_801DAB54);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x37B:
        func_8012A828(s0, (s32)&D_80187B18);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x38A:
        func_8012A828(s0, (s32)&D_80187D90);
        func_80182B60((s32 *)s0, (s32)&D_801DB140);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x38B:
        func_80182B60((s32 *)s0, (s32)&D_801DB504);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x3939:
        func_80182B60((s32 *)s0, (s32)&D_801DB518);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4242:
        func_80182B60((s32 *)s0, (s32)&D_801DB554);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 12:
        func_8012A828(s0, (s32)&D_80187898);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x5555:
        func_80182B60((s32 *)s0, (s32)&D_801DB5E0);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5656:
        func_8012A828(s0, (s32)&D_80187898);
        func_80182B60((s32 *)s0, (s32)&D_801DB68C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x57A:
        func_80182B60((s32 *)s0, (s32)&D_801DB960);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x57B:
        func_80182B60((s32 *)s0, (s32)&D_801DBAAC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5858:
        func_80182B60((s32 *)s0, (s32)&D_801DBAC0);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5959:
        func_8012A828(s0, (s32)&D_80187BC0);
        func_80182B60((s32 *)s0, (s32)&D_801DBAD4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x6060:
        func_8012A828(s0, (s32)&D_80187C48);
        func_80182B60((s32 *)s0, (s32)&D_801DBB40);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 14:
        func_8012A828(s0, (s32)&D_80187898);
        func_80182B60((s32 *)s0, (s32)&D_801D9360);
        *(u16 *)(s0 + 2) = 3;
        break;
    }

    if (D_801EDA10 != 0) {
        D_801EDA10 = 0;
    }
}


void func_8017F7F4(s32 param_1) {
    extern s32 D_801EDA10;
    if (*(s16 *)(param_1 + 0x98) == 0 || D_801EDA10 != 0) {
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) - 1;
    }
}




extern s32 D_801EDA10;
extern s32 func_80182B00();

void func_8017F830(s32 arg0) {
    if (func_80182B00(arg0) != 0 || D_801EDA10 != 0) {
        *(s16 *)(arg0 + 2) = 1;
    }
}



extern void (*D_80188DE0[])(void);

void func_8017F878(void *a0) {
    D_80188DE0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_80188050;
extern s32 D_8019E4A4;
extern s32 D_801EDA14;
extern s32 func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012CAE4(s32 a0);
extern void func_80143994(s32 a0, s32 a1);

void func_8017F8B4(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    s0 = a0;
    v0 = func_8012C1B8();
    *(s32 *)(s0 + 0x20) = v0;
    s1 = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        func_8001C214(s1, (s32)&D_8019E4A4);
        func_8001D0E8(s1, 0x7FFF, 0x7FFF);
        func_8012A828(s0, (s32)&D_80188050);
        func_80143994(s0, 0x3000);
        {
            u16 tmp = *(u16 *)(s0 + 0x2);
            D_801EDA14 = 0;
            *(u16 *)(s0 + 0x2) = tmp + 1;
        }
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, s32 a1);
extern void func_80182B60(s32 *a0, s32 a1);
extern s32 D_801EDA14;
extern s32 D_80187F90;
extern s32 D_80187FE8;
extern s32 D_80188148;
extern s32 D_801881D0;
extern s32 D_80188298;
extern s32 D_801DBEAC;
extern s32 D_801DD170;
extern s32 D_801DD624;
extern s32 D_801DD64C;
extern s32 D_801DD6C8;
extern s32 D_801DDCB4;
extern s32 D_801DDCC8;
extern s32 D_801DDCDC;
extern s32 D_801DDCF0;
extern s32 D_801DE224;
extern s32 D_801DEA28;
extern s32 D_801DF1F4;
extern s32 D_801DFBF8;
extern s32 D_801DFF1C;
extern s32 D_801E00B8;
extern s32 D_801E00CC;
extern s32 D_801E00E0;
extern s32 D_801E00F4;
extern s32 D_801E03C8;
extern s32 D_801E03DC;
extern s32 D_801E0868;

void func_8017F950(s32 arg0)
{
    s32 s0 = arg0;

    switch (D_801EDA14) {
    case 0:
        break;
    case 1:
        func_8012A828(s0, (s32)&D_80187FE8);
        func_80182B60((s32 *)s0, (s32)&D_801DBEAC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 2:
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 3:
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 4:
        func_8012A828(s0, (s32)&D_80187FE8);
        func_80182B60((s32 *)s0, (s32)&D_801DD170);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 5:
        func_8012A828(s0, (s32)&D_80187F90);
        func_80182B60((s32 *)s0, (s32)&D_801DD64C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x2424:
        func_8012A828(s0, (s32)&D_80188298);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x3737:
        func_80182B60((s32 *)s0, (s32)&D_801DD6C8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x38A:
        func_80182B60((s32 *)s0, (s32)&D_801DDCB4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x38B:
        func_80182B60((s32 *)s0, (s32)&D_801DDCC8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x3939:
        func_80182B60((s32 *)s0, (s32)&D_801DDCDC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4040:
        func_80182B60((s32 *)s0, (s32)&D_801DDCF0);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4141:
        func_80182B60((s32 *)s0, (s32)&D_801DE224);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5050:
        func_80182B60((s32 *)s0, (s32)&D_801DEA28);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5151:
        func_80182B60((s32 *)s0, (s32)&D_801DF1F4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5151B:
        func_8012A828(s0, (s32)&D_80188148);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x5151C:
        func_8012A828(s0, (s32)&D_801881D0);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x5252:
        func_8012A828(s0, (s32)&D_801881D0);
        func_80182B60((s32 *)s0, (s32)&D_801DFBF8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x53A:
        func_80182B60((s32 *)s0, (s32)&D_801DFF1C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x53B:
        func_80182B60((s32 *)s0, (s32)&D_801E00B8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5454:
        func_80182B60((s32 *)s0, (s32)&D_801E00CC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5555:
        func_80182B60((s32 *)s0, (s32)&D_801E00E0);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5656:
        func_80182B60((s32 *)s0, (s32)&D_801E00F4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x57A:
        func_80182B60((s32 *)s0, (s32)&D_801E03C8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x57B:
        func_80182B60((s32 *)s0, (s32)&D_801E03DC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5858:
        func_80182B60((s32 *)s0, (s32)&D_801E0868);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 8:
        func_8012A828(s0, (s32)&D_80187FE8);
        func_80182B60((s32 *)s0, (s32)&D_801DD624);
        *(u16 *)(s0 + 2) = 3;
        break;
    }

    if (D_801EDA14 != 0) {
        D_801EDA14 = 0;
    }
}


extern s32 D_801EDA14;

void func_8017FD70(s32 arg0) {
    if (*(s16 *)(arg0 + 0x98) == 0 || D_801EDA14 != 0) {
        *(u16 *)(arg0 + 2) -= 1;
    }
}


extern s32 D_80188050;
extern s32 D_801EDA14;
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_80182B00();

void func_8017FDAC(s32 a0)
{
    register s32 s0 __asm__("$16");
    s32 v0;

    s0 = a0;
    v0 = func_80182B00();
    if ((v0 != 0) || (D_801EDA14 != 0)) {
        func_8012A828(s0, (s32)&D_80188050);
        *(s16 *)(s0 + 0x2) = 1;
    }
}



extern void (*D_80188DF0[])(void);

void func_8017FE08(void *a0) {
    D_80188DF0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_801884A8;
extern s32 D_801A05E4;
extern s32 D_801EDA0C;
extern s32 func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012CAE4(s32 a0);
extern void func_80143994(s32 a0, s32 a1);

void func_8017FE44(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    s0 = a0;
    v0 = func_8012C1B8();
    *(s32 *)(s0 + 0x20) = v0;
    s1 = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        func_8001C214(s1, (s32)&D_801A05E4);
        func_8001D0E8(s1, 0x7FFF, 0x7FFF);
        func_8012A828(s0, (s32)&D_801884A8);
        func_80143994(s0, 0x3000);
        {
            u16 tmp = *(u16 *)(s0 + 0x2);
            D_801EDA0C = 0;
            *(u16 *)(s0 + 0x2) = tmp + 1;
        }
    }
}


/* func_8017FEE0 — 305 ins, ov_SC01_001. Same idiom as the in-TU neighbour
 * func_8017F328: a 28-node balanced switch on D_801EDA0C whose arms call
 * func_8012A828 / func_80182B60 and then either set *(u16*)(s0+2) = 3 or
 * bump it by 1; post-switch `if (D != 0) D = 0;`.
 *
 * Case set was derived from the balance_case_nodes split arithmetic
 * (root 0x57B needs 13 low / 14 high nodes): `case 0: break;` and `case 3`
 * are REAL nodes (the earlier backlog draft lacked both). Arm order below is
 * the target's emission order (§222: source arm order IS emission order);
 * the trailing 0x100 / 2 arms let cross_jump fold the `+= 1` tail exactly
 * as the .s shows (.L8018035C shared jal, .L80180364 shared lhu/addiu/sh).
 *
 * Declarations: D_801EDA0C, D_801884A8, func_8012A828, func_80182B60 are
 * copied verbatim from this TU; every other D_ symbol is undeclared in the
 * TU and only ever has its address taken, so it follows the neighbour's
 * `extern s32` house style.
 */

extern void func_8012A828(s32 a0, s32 a1);
extern void func_80182B60(s32 *a0, s32 a1);
extern s32 D_801EDA0C;
extern s32 D_801884A8;
extern s32 D_80188500;
extern s32 D_80188568;
extern s32 D_801E6A44;
extern s32 D_801E7D08;
extern s32 D_801E81BC;
extern s32 D_801E81E4;
extern s32 D_801E8260;
extern s32 D_801E8BC4;
extern s32 D_801E8BD8;
extern s32 D_801E8F9C;
extern s32 D_801E8FB0;
extern s32 D_801E8FC4;
extern s32 D_801E94F8;
extern s32 D_801E9CFC;
extern s32 D_801E9D10;
extern s32 D_801EA42C;
extern s32 D_801EA440;
extern s32 D_801EA454;
extern s32 D_801EA468;
extern s32 D_801EA47C;
extern s32 D_801EA490;
extern s32 D_801EA4A4;
extern s32 D_801EA4B8;
extern s32 D_801EA4CC;
extern s32 D_801EA7F8;
extern s32 D_801EA80C;

void func_8017FEE0(s32 arg0)
{
    s32 s0 = arg0;

    switch (D_801EDA0C) {
    case 0:
        break;
    case 1:
        func_8012A828(s0, (s32)&D_80188500);
        func_80182B60((s32 *)s0, (s32)&D_801E6A44);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 3:
        func_8012A828(s0, (s32)&D_80188500);
        func_80182B60((s32 *)s0, (s32)&D_801E7D08);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 4:
        func_8012A828(s0, (s32)&D_801884A8);
        func_80182B60((s32 *)s0, (s32)&D_801E81E4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x3031:
        func_80182B60((s32 *)s0, (s32)&D_801E8260);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x30B:
        func_8012A828(s0, (s32)&D_80188568);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x3737:
        func_80182B60((s32 *)s0, (s32)&D_801E8BC4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x38A:
        func_80182B60((s32 *)s0, (s32)&D_801E8BD8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x38B:
        func_80182B60((s32 *)s0, (s32)&D_801E8F9C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x3939:
        func_80182B60((s32 *)s0, (s32)&D_801E8FB0);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4040:
        func_80182B60((s32 *)s0, (s32)&D_801E8FC4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4141:
        func_80182B60((s32 *)s0, (s32)&D_801E94F8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4242:
        func_80182B60((s32 *)s0, (s32)&D_801E9CFC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5050:
        func_80182B60((s32 *)s0, (s32)&D_801E9D10);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5151:
        func_80182B60((s32 *)s0, (s32)&D_801EA42C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5252:
        func_80182B60((s32 *)s0, (s32)&D_801EA440);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x53A:
        func_80182B60((s32 *)s0, (s32)&D_801EA454);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x53B:
        func_80182B60((s32 *)s0, (s32)&D_801EA468);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5454:
        func_80182B60((s32 *)s0, (s32)&D_801EA47C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5555:
        func_80182B60((s32 *)s0, (s32)&D_801EA490);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5656:
        func_80182B60((s32 *)s0, (s32)&D_801EA4A4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x57A:
        func_80182B60((s32 *)s0, (s32)&D_801EA4B8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x57B:
        func_80182B60((s32 *)s0, (s32)&D_801EA4CC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5858:
        func_80182B60((s32 *)s0, (s32)&D_801EA7F8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x6060:
        func_80182B60((s32 *)s0, (s32)&D_801EA80C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 7:
        func_8012A828(s0, (s32)&D_80188500);
        func_80182B60((s32 *)s0, (s32)&D_801E81BC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x100:
        func_8012A828(s0, (s32)&D_801884A8);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 2:
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    }

    if (D_801EDA0C != 0) {
        D_801EDA0C = 0;
    }
}



extern s32 D_801EDA0C;

void func_801803A4(void *a0) {
    if (*(s16 *)((s32)a0 + 0x98) == 0 || D_801EDA0C != 0) {
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) - 1;
    }
}


extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_80182B00();
extern s32 D_801884A8;
extern s32 D_801EDA0C;

void func_801803E0(s32 a0)
{
    if ((func_80182B00() != 0) || (D_801EDA0C != 0)) {
        func_8012A828(a0, (s32)&D_801884A8);
        *(s16 *)(a0 + 0x2) = 1;
    }
}



extern void (*D_80188E00[])(void);

void func_8018043C(void *a0) {
    D_80188E00[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_80188720;
extern s32 D_801A23FC;
extern s32 D_801EDA1C;
extern s32 func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012CAE4(s32 a0);
extern void func_80143994(s32 a0, s32 a1);

void func_80180478(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    s0 = a0;
    v0 = func_8012C1B8();
    *(s32 *)(s0 + 0x20) = v0;
    s1 = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        func_8001C214(s1, (s32)&D_801A23FC);
        func_8001D0E8(s1, 0x7FFF, 0x7FFF);
        func_8012A828(s0, (s32)&D_80188720);
        func_80143994(s0, 0x3000);
        {
            u16 tmp = *(u16 *)(s0 + 0x2);
            D_801EDA1C = 0;
            *(u16 *)(s0 + 0x2) = tmp + 1;
        }
    }
}


extern s32 D_801EDA1C;
extern s32 D_80188630;
extern s32 D_80188720;
extern void func_8012A828(s32 a0, s32 a1);
extern void func_80182B60(s32 *a0, s32 a1);
extern s32 D_801E65A4;
extern s32 D_801E4F1C;
extern s32 D_801E4A54;
extern s32 D_801E4F44;
extern s32 D_801E4A68;
extern s32 D_801E652C;
extern s32 D_801E4FD4;
extern s32 D_801E4FE8;
extern s32 D_801E6540;
extern s32 D_801E6590;
extern s32 D_801E5804;
extern s32 D_801E5010;
extern s32 D_801E4FC0;
extern s32 D_801E4FFC;
extern s32 D_801E5024;
extern s32 D_801E5038;
extern s32 D_801E6568;
extern s32 D_801E6208;
extern s32 D_801E6554;
extern s32 D_801E657C;
extern s32 D_801E6A30;

void func_80180514(s32 arg0) {
    s32 s0 = arg0;

    switch (D_801EDA1C) {
    case 0:
        break;
    case 1:
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 2:
        func_8012A828(s0, (s32)&D_80188720);
        func_80182B60((s32 *)s0, (s32)&D_801E4A54);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 3:
        func_8012A828(s0, (s32)&D_80188630);
        func_80182B60((s32 *)s0, (s32)&D_801E4F44);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x3737:
        func_80182B60((s32 *)s0, (s32)&D_801E4FC0);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x38A:
        func_80182B60((s32 *)s0, (s32)&D_801E4FD4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x38B:
        func_80182B60((s32 *)s0, (s32)&D_801E4FE8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x3939:
        func_80182B60((s32 *)s0, (s32)&D_801E4FFC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4040:
        func_80182B60((s32 *)s0, (s32)&D_801E5010);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4141:
        func_80182B60((s32 *)s0, (s32)&D_801E5024);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5050:
        func_80182B60((s32 *)s0, (s32)&D_801E5038);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5151:
        func_80182B60((s32 *)s0, (s32)&D_801E5804);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5252:
        func_80182B60((s32 *)s0, (s32)&D_801E6208);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x53A:
        func_80182B60((s32 *)s0, (s32)&D_801E652C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x53B:
        func_80182B60((s32 *)s0, (s32)&D_801E6540);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5454:
        func_80182B60((s32 *)s0, (s32)&D_801E6554);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5555:
        func_80182B60((s32 *)s0, (s32)&D_801E6568);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5656:
        func_80182B60((s32 *)s0, (s32)&D_801E657C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x57A:
        func_80182B60((s32 *)s0, (s32)&D_801E6590);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x57B:
        func_80182B60((s32 *)s0, (s32)&D_801E65A4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5858:
        func_80182B60((s32 *)s0, (s32)&D_801E6A30);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 6:
        func_8012A828(s0, (s32)&D_80188630);
        func_80182B60((s32 *)s0, (s32)&D_801E4A68);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 7:
        func_8012A828(s0, (s32)&D_80188630);
        func_80182B60((s32 *)s0, (s32)&D_801E4F1C);
        *(u16 *)(s0 + 2) = 3;
        break;
    }

    if (D_801EDA1C != 0) {
        D_801EDA1C = 0;
    }
}


extern s32 D_801EDA1C;

void func_80180854(param_1)
s32 param_1;
{
    extern s32 D_801EDA1C;
    if (*(s16 *)(param_1 + 0x98) == 0 || D_801EDA1C != 0) {
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) - 1;
    }
}


extern s32 D_801EDA1C;
extern s32 func_80182B00();

void func_80180890(s32 arg0) {
    if (func_80182B00(arg0) != 0 || D_801EDA1C != 0) {
        *(s16 *)(arg0 + 2) = 1;
    }
}



extern void (*D_80188E10[])(void);

void func_801808D8(void *a0) {
    D_80188E10[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_801888F8;
extern s32 D_801A512C;
extern s32 D_801EDA18;
extern s32 func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012CAE4(s32 a0);
extern void func_80143994(s32 a0, s32 a1);

void func_80180914(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    s0 = a0;
    v0 = func_8012C1B8();
    *(s32 *)(s0 + 0x20) = v0;
    s1 = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        func_8001C214(s1, (s32)&D_801A512C);
        func_8001D0E8(s1, 0x7FFF, 0x7FFF);
        func_8012A828(s0, (s32)&D_801888F8);
        func_80143994(s0, 0x3000);
        {
            u16 tmp = *(u16 *)(s0 + 0x2);
            D_801EDA18 = 0;
            *(u16 *)(s0 + 0x2) = tmp + 1;
        }
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, s32 a1);
extern void func_80182B60(s32 *a0, s32 a1);
extern s32 D_801EDA18;
extern s32 D_801887E8;
extern s32 D_801888F8;
extern s32 D_801889C8;
extern s32 D_801E087C;
extern s32 D_801E0890;
extern s32 D_801E08A4;
extern s32 D_801E08CC;
extern s32 D_801E0948;
extern s32 D_801E12AC;
extern s32 D_801E1898;
extern s32 D_801E18AC;
extern s32 D_801E18C0;
extern s32 D_801E18D4;
extern s32 D_801E18E8;
extern s32 D_801E18FC;
extern s32 D_801E3048;
extern s32 D_801E3814;
extern s32 D_801E4218;
extern s32 D_801E453C;
extern s32 D_801E4550;
extern s32 D_801E4564;
extern s32 D_801E4578;
extern s32 D_801E458C;
extern s32 D_801E45A0;
extern s32 D_801E45B4;
extern s32 D_801E4A40;

void func_801809B0(s32 arg0) {
    s32 s0 = arg0;

    switch (D_801EDA18) {
    case 0:
        break;
    case 1:
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 2:
        func_8012A828(s0, (s32)&D_801888F8);
        func_80182B60((s32 *)s0, (s32)&D_801E087C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 3:
        func_8012A828(s0, (s32)&D_801887E8);
        func_80182B60((s32 *)s0, (s32)&D_801E08CC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x3031:
        func_80182B60((s32 *)s0, (s32)&D_801E0948);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x30B:
        func_8012A828(s0, (s32)&D_801889C8);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x3737:
        func_80182B60((s32 *)s0, (s32)&D_801E12AC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x38A:
        func_80182B60((s32 *)s0, (s32)&D_801E1898);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x38B:
        func_80182B60((s32 *)s0, (s32)&D_801E18AC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x3939:
        func_80182B60((s32 *)s0, (s32)&D_801E18C0);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4040:
        func_80182B60((s32 *)s0, (s32)&D_801E18D4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4141:
        func_80182B60((s32 *)s0, (s32)&D_801E18E8);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x4747:
        func_80182B60((s32 *)s0, (s32)&D_801E18FC);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5050:
        func_80182B60((s32 *)s0, (s32)&D_801E3048);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5151:
        func_80182B60((s32 *)s0, (s32)&D_801E3814);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5252:
        func_80182B60((s32 *)s0, (s32)&D_801E4218);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x53A:
        func_80182B60((s32 *)s0, (s32)&D_801E453C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x53B:
        func_80182B60((s32 *)s0, (s32)&D_801E4550);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5454:
        func_80182B60((s32 *)s0, (s32)&D_801E4564);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5555:
        func_80182B60((s32 *)s0, (s32)&D_801E4578);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5656:
        func_80182B60((s32 *)s0, (s32)&D_801E458C);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x57A:
        func_80182B60((s32 *)s0, (s32)&D_801E45A0);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x57B:
        func_80182B60((s32 *)s0, (s32)&D_801E45B4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x5858:
        func_80182B60((s32 *)s0, (s32)&D_801E4A40);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 6:
        func_8012A828(s0, (s32)&D_801887E8);
        func_80182B60((s32 *)s0, (s32)&D_801E0890);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 7:
        func_8012A828(s0, (s32)&D_801887E8);
        func_80182B60((s32 *)s0, (s32)&D_801E08A4);
        *(u16 *)(s0 + 2) = 3;
        break;
    case 0x100:
        func_8012A828(s0, (s32)&D_801888F8);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    }

    if (D_801EDA18 != 0) {
        D_801EDA18 = 0;
    }
}


extern s32 D_801EDA18;

void func_80180E54(param_1)
s32 param_1;
{
    extern s32 D_801EDA18;
    if (*(s16 *)(param_1 + 0x98) == 0 || D_801EDA18 != 0) {
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) - 1;
    }
}


extern s32 D_801888F8;
extern s32 D_801EDA18;
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_80182B00();

void func_80180E90(s32 a0)
{
    register s32 s0 __asm__("$16");
    s32 v0;

    s0 = a0;
    v0 = func_80182B00();
    if ((v0 != 0) || (D_801EDA18 != 0)) {
        func_8012A828(s0, (s32)&D_801888F8);
        *(s16 *)(s0 + 0x2) = 1;
    }
}


extern s32 D_801ED9F0;
extern void (*D_80188E20[])(void);
extern void func_801832BC(s32 param_1);

void func_80180EEC(s32 param_1) {
    D_80188E20[*(u16 *)(param_1 + 0x2)]();
    if ((1 < *(u16 *)(param_1 + 0x2)) && (D_801ED9F0 == 1)) {
        func_801832BC(param_1);
    }
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 D_80199754;
extern s32 D_80183B84;
extern s32 D_801EDA34[];
extern s32 D_801EDA38;

void func_80180F64(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    s0 = a0;
    v0 = func_8012C1B8();
    *(s32 *)(s0 + 0x20) = v0;
    s1 = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        func_8001C214(s1, (s32)&D_80199754);
        func_8001D0E8(s1, 0x7FFF, 0x7FFF);
        func_8012A828(s0, (s32)&D_80183B84);
        {
            u16 tmp = *(u16 *)(s0 + 0x2);
            D_801EDA34[0] = 8;
            D_801EDA38 = 0;
            *(u16 *)(s0 + 0x2) = tmp + 1;
        }
    }
}


extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_80143970(s32 a0);
extern s32 D_800DE2A4[];
extern s32 D_801EDA34[];
extern s32 D_801EDA38;
extern s32 D_801EDA08;
extern void (*D_801872C0)(void *);

void func_80181000(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 p __asm__("$5");
    register s32 g __asm__("$3");
    u16 tmp;
    s32 flag;

    s0 = a0;
    p = *(s32 *)(s0 + 0x20);
    g = D_801EDA34[0];
    tmp = *(u16 *)(p + 0x12) + g;
    flag = D_801EDA38;
    *(u16 *)(p + 0x12) = tmp;
    if (flag == 0)
        return;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = 0;
    *(s16 *)(s0 + 6) = 5;
    *(s16 *)(s0 + 0xA) = -0x292;
    *(s16 *)(s0 + 0xE) = -0x15;
    func_8001C214(*(s32 *)(s0 + 0x20), (s32)&D_800DE2A4);
    func_8012A828(s0, (s32)&D_801872C0);
    func_80143970(s0);
    tmp = *(u16 *)(s0 + 2);
    D_801EDA08 = 0;
    *(u16 *)(s0 + 2) = tmp + 1;
}


#include "common.h"

extern void func_8012A828(s32 a0, s32 a1);
extern void func_80182B60(s32 *a0, s32 a1);
extern s32 func_80182B00(s32 a0);
extern void func_8012C218(void *a0);
extern s32 D_801ED9F8;
extern s32 D_801ED9FC;
extern s32 D_801EDA08;
extern s32 D_801872D8;
extern s32 D_80187360;
extern s32 D_80187478;
extern s32 D_80187488;
extern s32 D_80187590;
extern s32 D_801875F8;
extern s32 D_80187680;
extern s32 D_801877F0;
extern s32 D_801D3174;
extern s32 D_801D319C;
extern s32 D_801D3924;
extern s32 D_801D443C;
extern s32 D_801D4450;
extern s32 D_801D4464;
extern s32 D_801D4AD0;
extern s32 D_801D621C;
extern s32 D_801D6230;
extern s32 D_801D7400;
extern s32 D_801D743C;
extern s32 D_801D74E0;
extern s32 D_801D7584;
extern s32 D_801D7598;

void func_801810A4(s32 arg0)
{
    s32 s0 = arg0;

    switch (D_801EDA08) {
    case 0:
        break;
    case 1:
        func_8012A828(s0, (s32)&D_80187590);
        *(u16 *)(s0 + 2) = 5;
        break;
    case 2:
        func_8012A828(s0, (s32)&D_80187360);
        func_80182B60((s32 *)s0, (s32)&D_801D319C);
        D_801ED9F8 = 0xA;
        D_801ED9FC = 0x28;
        *(u16 *)(s0 + 2) = 9;
        break;
    case 4:
        func_8012A828(s0, (s32)&D_80187478);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x3636:
        func_8012A828(s0, (s32)&D_801872D8);
        func_80182B60((s32 *)s0, (s32)&D_801D3924);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x38B:
        func_8012A828(s0, (s32)&D_80187680);
        *(u16 *)(s0 + 2) = 7;
        break;
    case 0x4040:
        func_80182B60((s32 *)s0, (s32)&D_801D443C);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x4141:
        func_80182B60((s32 *)s0, (s32)&D_801D4450);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x4242:
        func_8012A828(s0, (s32)&D_80187680);
        func_80182B60((s32 *)s0, (s32)&D_801D4464);
        *(u16 *)(s0 + 2) = 0xC;
        break;
    case 0x4747:
        func_8012A828(s0, (s32)&D_801872D8);
        func_80182B60((s32 *)s0, (s32)&D_801D4AD0);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x4848:
        func_8012A828(s0, (s32)&D_80187680);
        func_80182B60((s32 *)s0, (s32)&D_801D621C);
        func_80182B00(s0);
        *(u16 *)(s0 + 2) = 7;
        break;
    case 0x5050:
        func_80182B60((s32 *)s0, (s32)&D_801D6230);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x51C:
        func_8012A828(s0, (s32)&D_801877F0);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x5252:
        func_8012A828(s0, (s32)&D_80187478);
        func_80182B60((s32 *)s0, (s32)&D_801D7400);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x53A:
        func_80182B60((s32 *)s0, (s32)&D_801D3174);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x53B:
        func_80182B60((s32 *)s0, (s32)&D_801D3174);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x53C:
        func_80182B60((s32 *)s0, (s32)&D_801D7400);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x5454:
        func_8012A828(s0, (s32)&D_80187488);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x3939:
    case 0x4949:
    case 0x54B:
        func_8012A828(s0, (s32)&D_801872D8);
        *(u16 *)(s0 + 2) = *(u16 *)(s0 + 2) + 1;
        break;
    case 0x5555:
        func_8012A828(s0, (s32)&D_801872D8);
        func_80182B60((s32 *)s0, (s32)&D_801D743C);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x5656:
        func_80182B60((s32 *)s0, (s32)&D_801D74E0);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x57A:
        func_80182B60((s32 *)s0, (s32)&D_801D7584);
        *(u16 *)(s0 + 2) = 4;
        break;
    case 0x57B:
        func_8012A828(s0, (s32)&D_801875F8);
        func_80182B60((s32 *)s0, (s32)&D_801D7598);
        *(s16 *)(s0 + 0xDE) = 4;
        *(u16 *)(s0 + 2) = 0xB;
        break;
    case 0x5959:
        func_8012C218((void *)s0);
        break;
    }

    if (D_801EDA08 != 0) {
        D_801EDA08 = 0;
    }
}


extern s32 D_801EDA08;
void func_8018150C(s32 a0)
{
    if (*(s16 *)(a0 + 0x98) == 0 || D_801EDA08 != 0) {
        *(s16 *)(a0 + 2) = 2;
    }
}


extern s32 func_80182B00(s32 arg0);
extern s32 D_801EDA08;

void func_8018153C(s32 arg0) {
    if (func_80182B00(arg0) != 0 || D_801EDA08 != 0) {
        *(s16 *)(arg0 + 2) = 2;
    }
}


extern u8 D_80187338[];
extern void func_8012A828(s32, s32);

    void func_80181584(void *a0)
    {
        if (*(s16 *)((s32)a0 + 0x98) != 0) {
            return;
        }
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_80187338);
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }


extern s32 D_801EDA08;

void func_801815D8(s32 a0)
{
    if (D_801EDA08 != 0) {
        *(u16 *)(a0 + 2) = 2;
    }
}


extern u8 D_80187758[];
extern void func_8012A828(s32, s32);

    void func_801815F8(void *a0)
    {
        if (*(s16 *)((s32)a0 + 0x98) != 0) {
            return;
        }
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_80187758);
        *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }


extern u8 D_80187758[];
extern void func_8012A828(s32, s32);
extern s32 func_80182B00(s32 a0);

void func_8018164C(void *a0)
{
    func_80182B00((s32)a0);
    if (*(s16 *)((s32)a0 + 0x98) != 0) {
        return;
    }
    ((void (*)(s32, void *))func_8012A828)((s32)a0, D_80187758);
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}


extern s32 D_801ED9F8;
extern u8 D_80187430[];
extern void func_8012A828(s32 a0, s32 a1);
extern s32 D_801ED9FC;
extern u16 D_801877D0[];
extern s32 func_80182B00(s32 a0);
extern s32 D_801EDA08;
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u16 D_801873D8[];
extern s32 D_801EDA00;

void func_801816A4(s32 a0)
{
    register s32 s0 __asm__("$16");

    s0 = a0;
    if (--D_801ED9F8 == 0) {
        func_8012A828(s0, (s32)&D_80187430);
    }
    if (--D_801ED9FC == 0) {
        func_8012A828(s0, (s32)&D_801877D0);
    }
    if (func_80182B00(s0) != 0 || D_801EDA08 != 0) {
        func_80143B6C(s0, 1);
        func_8002D4C8(0x42E, 0);
        func_8012A828(s0, (s32)&D_801873D8);
        {
            u16 tmp = *(u16 *)(s0 + 0x2);
            D_801EDA00 = 10;
            *(u16 *)(s0 + 0x2) = tmp + 1;
        }
    }
}


extern s32 D_801EDA00;
extern s32 D_801ED9E4;

void func_80181784(s32 a0) {
    D_801EDA00--;
    if (D_801EDA00 == 0) {
        D_801ED9E4 = 1;
        *(s16 *)((s32)a0 + 2) = 2;
    }
}


extern s32 D_801EDA08;
extern s32 func_80143B6C(s32 a0, s32 a1);
extern s32 func_80182B00(s32 a0);

void func_801817BC(int param_1)
{
    int uVar1;

    uVar1 = (*(u16 *)(param_1 + 0xde) - 1);
    *(u16 *)(param_1 + 0xde) = uVar1;
    if ((uVar1 << 0x10) == 0) {
        func_80143B6C(param_1, 1);
        *(u16 *)(param_1 + 0xde) = 10;
    }
    if (func_80182B00(param_1) != 0 || D_801EDA08 != 0) {
        *(u16 *)(param_1 + 2) = 2;
    }
}


void func_80181834(void) {
}

#include "common.h"

/* §200 alias: this TU spells func_8001D074 `void (s32,s32)` (lines 119/124), but the target
   stores its $v0 into D_801EDA24 — the fleet's 5 rivals declare it s32.  Bind our own
   identifier to the same link name so the TU's spelling stays untouched. */
extern s32 aF8001D074(s32, s32) __asm__("func_8001D074");
extern void func_800233CC(void *, unsigned short);
extern void func_8001CD9C(int, void *);

extern s32 D_801ED9B8;
extern s32 D_801ED9BC;
extern s32 D_801ED9C0;
extern s32 D_801ED9C4;
extern s32 D_801EDA24;
extern u8  D_80188A94;
extern u8  D_80188A95;
extern u8  D_80188A96;

s32 func_8018183C(void) {
    switch (D_801ED9B8) {
    case 0:
        D_801EDA24 = aF8001D074(0x3E, 0x7D);
        D_801ED9C4 = 0x10;
        if (D_801EDA24 != 0) {
            func_800233CC(&D_80188A94, 0x10);
            func_8001CD9C(D_801EDA24, &D_80188A94);
            *(s32 *)(D_801EDA24 + 4) |= 0x50000040;
        }
        D_801ED9C0 = 0xFF;
        D_801ED9BC = 0x10;
        *(s16 *)(D_801EDA24 + 0xA) = -0x2E9;
        *(s16 *)(D_801EDA24 + 0xC) = -0x2C;
        *(s16 *)(D_801EDA24 + 0x8) = 0;
        D_80188A94 = 0x10;
        D_80188A95 = 0xFF;
        D_80188A96 = 0xFF;
        D_801ED9B8++;
        break;
    case 1:
        func_800233CC(&D_80188A94, (u16)D_801ED9C4);
        if (D_801ED9BC == 0) {
            D_801ED9C0 -= 0x10;
            if (D_801ED9C0 <= 0) {
                D_801ED9C0 = 0;
            }
            D_80188A95 = D_801ED9C0;
            D_80188A96 = D_801ED9C0;
            D_801ED9C4 -= 4;
            if (D_801ED9C4 < 0) {
                D_801ED9C4 = 0;
            }
            if (D_801ED9C0 == 0) {
                *(s16 *)(D_801EDA24 + 0x0) = 0;
                return 1;
            }
        } else {
            D_801ED9BC--;
        }
        *(u16 *)(D_801EDA24 + 0xA) = *(u16 *)(D_801EDA24 + 0xA) - 6;
        break;
    }
    return 0;
}


extern s32 D_801EDA44;
    void func_80181A28(void) {
        s32 i = 0x4FB0;
        do {
            *(s32 *)((s32)&D_801EDA44 + i) = 0;
            i -= 0x50;
        } while (i >= 0);
    }


extern s32 D_801F3050;
extern s32 D_801F304C;
extern s32 D_80188C78[];
extern s32 D_801EDA70[];
extern s32 D_801EDA6C[];
extern s32 D_801F2A6C[];
extern u16 D_800B99DC;
extern s32 D_801EDA44;
extern s32 D_801EDA48[];
extern s32 D_801EDA4C[];
extern s32 D_801EDA50[];
extern s32 D_801EDA54[];
extern s32 D_801EDA58[];
extern s32 D_801EDA5C[];
extern s32 D_801EDA60[];
extern s32 D_801EDA88[];
extern s32 D_801EDA8C[];
extern s32 D_801EDA90[];

void func_80181A4C(void)
{
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    register s32 a0 __asm__("$4");
    register s32 a1 __asm__("$5");
    register s32 a2 __asm__("$6");
    register s32 a3 __asm__("$7");
    register s32 t0 __asm__("$8");
    register s32 t1 __asm__("$9");
    register s32 t2 __asm__("$10");
    register s32 *t3 __asm__("$11");
    register s32 *t4 __asm__("$12");
    register s32 *t5 __asm__("$13");
    register s32 *t6 __asm__("$14");
    register s32 *t7 __asm__("$15");
    register s32 i __asm__("$16");
    register s32 back __asm__("$17");
    register s32 *src __asm__("$18");
    register s32 color __asm__("$19");
    register s32 *tbl __asm__("$20");
    register s32 *srcm12 __asm__("$21");
    register s32 *tbl4 __asm__("$22");
    register s32 *t8 __asm__("$24");
    register s32 *t9 __asm__("$25");

    if (((D_801F3050 = D_801F3050 + 1) & 7) != 0) {
        return;
    }

    back = D_801F304C;
    for (i = back & 1; i < 0x10;) {
        color = 0xFCF50000;
        tbl = D_80188C78;
        tbl4 = tbl + 1;
        src = D_801EDA70;
        srcm12 = src - 3;

        do {
            v0 = back + 7;
            back = v0 & 0xF;
            v1 = back * 8;
            a0 = v1 + (s32)tbl4;
            t4 = D_801EDA6C;
            t9 = t4 - 1;
            t8 = t4 - 2;
            t7 = t4 + 6;
            t6 = t4 + 5;
            t5 = t4 + 4;
            a3 = 0;
            t1 = (s32)srcm12;
            t0 = (s32)src;
            do {
                if (*(s32 *)((char *)&D_801EDA44 + a3) == 0) {
                    v0 = 1;
                    *(s32 *)((char *)&D_801EDA44 + a3) = v0;
                    __asm__ __volatile__("addu %0,%1,%2" : "=r"(v0) : "r"(v1), "r"(tbl));
                    __asm__ __volatile__("move %0,%1" : "=r"(t3) : "r"(t1));
                    *(s32 *)((char *)&D_801EDA58 + a3) = 0;
                    *(s32 *)((char *)&D_801EDA5C + a3) = color;
                    *(s32 *)((char *)&D_801EDA60 + a3) = 0;
                    v0 = *(s32 *)v0;
                    v1 = D_801F304C;
                    v0 <<= 16;
                    v1 &= 0x1F;
                    v1 <<= 19;
                    *(s32 *)((char *)&D_801EDA4C + a3) = v0;
                    v0 = *(s32 *)a0;
                    a0 = (s32)(src - 9);
                    a0 = a3 + a0;
                    *(s32 *)((char *)&D_801EDA54 + a3) = v1;
                    v0 <<= 16;
                    v0 += color;
                    *(s32 *)((char *)&D_801EDA50 + a3) = v0;
                    __asm__ __volatile__("lw %0,0(%3)\n\tlw %1,4(%3)\n\tlw %2,8(%3)\n\tsw %0,0(%4)\n\tsw %1,4(%4)\n\tsw %2,8(%4)"
                                         : "=r"(v0), "=r"(v1), "=r"(a1)
                                         : "r"(a0), "r"(t0));
                    v1 = (s32)(src - 6);
                    v1 = a3 + v1;
                    a1 = *(s16 *)(v1 + 2);
                    v0 = *(s16 *)(a0 + 2);
                    a2 = *(s16 *)(v1 + 6);
                    v1 = *(s16 *)(v1 + 10);
                    t2 = a1 - v0;
                    t0 = t2;
                    a1 = *(s16 *)(a0 + 6);
                    v0 = *(s16 *)(a0 + 10);
                    a2 -= a1;
                    t1 = v1 - v0;
                    if (t2 < 0) {
                        t0 = -t2;
                    }
                    a0 = a2;
                    if (a2 < 0) {
                        a0 = -a2;
                    }
                    v1 = t1;
                    if (t1 < 0) {
                        v1 = -t1;
                    }
                    v0 = (a0 < t0);
                    a1 = t0;
                    if (!v0) {
                        a1 = a0;
                    }
                    v0 = (a1 < v1);
                    if (v0) {
                        a1 = v1;
                    }
                    a0 = t2 << 16;
                    a0 /= a1;
                    v1 = a2 << 16;
                    v1 /= a1;
                    v0 = t1 << 16;
                    v0 /= a1;
                    *(s32 *)((char *)t3 + 0) = a0;
                    *(s32 *)((char *)t3 + 4) = v1;
                    *(s32 *)((char *)t3 + 8) = v0;
                    v0 = *t8;
                    v0 <<= 1;
                    *t5 = v0;
                    v0 = *t9;
                    v0 <<= 1;
                    *t6 = v0;
                    v0 = *t4;
                    v0 <<= 1;
                    *t7 = v0;
                    *t5 = 0;
                    *t6 = 0;
                    *t7 = 0;
                    v0 = *t8;
                    v1 = (u32)v0 >> 31;
                    v0 += v1;
                    v0 >>= 1;
                    *(s32 *)((char *)&D_801EDA88 + a3) = v0;
                    v0 = *t9;
                    v1 = (u32)v0 >> 31;
                    v0 += v1;
                    v0 >>= 1;
                    *(s32 *)((char *)&D_801EDA8C + a3) = v0;
                    v0 = *t4;
                    v1 = (u32)v0 >> 31;
                    v0 += v1;
                    v0 >>= 1;
                    *(s32 *)((char *)&D_801EDA90 + a3) = v0;
                    v0 = D_800B99DC;
                    v0 &= 7;
                    v0 += 10;
                    *(s32 *)((char *)&D_801EDA48 + a3) = v0;
                    break;
                }
                t4 += 20;
                t9 += 20;
                t8 += 20;
                t7 += 20;
                t6 += 20;
                t5 += 20;
                a3 += 0x50;
                t1 += 0x50;
                t0 += 0x50;
            } while ((s32)t4 < (s32)D_801F2A6C);
            D_801F304C = D_801F304C + 7;
        } while (++i < 0x10);
    }
}


#include "common.h"

/* func_80181E04 (ov_SC01_001, 269 ins) - MATCH.
 *
 * splat labels this "handwritten" only because of the `cfc2` in gte_stflg; the
 * prologue/epilogue and the whole body are ordinary gcc-2.7.2 -O2 output (no $s
 * register is touched because both `jal`s precede the loop, so every loop value
 * lives happily in a call-clobbered temp).
 *
 * Four levers, in the order they were needed:
 *
 * 1. §246-2 PARALLEL GLOBALS SHARE ONE giv. The target reaches sixteen distinct
 *    D_801EDA?? symbols as `lui $at,%hi(sym); addu $at,$at,$a2; lw/sw %lo(sym)($at)`
 *    off ONE 0x50-stride byte-offset giv ($a2). Declaring every one of them as an
 *    array of a common 0x50-byte record type (field at +0) makes giv-combine fuse all
 *    of them onto that single IV -- and unlike the plain `s32 sym[]` + `sym[i*20]`
 *    spelling it folds for the STORES too. §200 aliases (`__asm__("D_801EDA4C")`)
 *    keep the TU's own `extern s32 D_801EDA4C[]` decls untouched.
 *    The six `lhu` reads are the SAME record type with a u16 at +0, aliased onto the
 *    +2 half-word symbols the linker script already exports (D_801EDA4E/52/56/72/76/7A).
 *
 * 2. THE COUNTED LOOP, NOT THE POINTER WALK. `i < 0x100` lets loop.c eliminate the
 *    biv in favour of the &D_801EDA44[i] address giv, and it emits the derived bound
 *    INSIDE the loop (`lui/addiu` are re-materialised every iteration at .L80182208
 *    because biv elimination runs after invariant motion). The reloc becomes
 *    D_801EDA44+0x5000, which links to the identical 0x801F2A44 bytes as the target's
 *    %hi/%lo(D_801F2A44). Spelling the bound as `&D_801F2A44` instead costs +12.
 *
 * 3. THE ROUNDING IS SOURCE-LEVEL, THE SHIFT IS NOT. The target's `bgez/addiu 7` sits
 *    BEFORE the packet stores and its `sra` AFTER them. A single `z / 8` cannot split
 *    like that (the whole div sequence is emitted at one point); `if (z < 0) z += 7;`
 *    then `(z >> 3) * 4 + (s32)ot` at the use site reproduces both halves, and the
 *    `lui 0xE100` falls into the bgez delay slot for free. Writing `(u32 *)ot + z/8`
 *    instead reverses the final `addu` operands.
 *
 * 4. THE OT INSERT IS A 24-BIT BITFIELD STORE, NOT A HAND-MASKED WORD. This is what
 *    the last 18 instructions turned on. Hand-written as
 *      `*(u32 *)pkt = (*(u32 *)pkt & 0xFF000000) | (*otp & 0xFFFFFF);`
 *    gcc evaluates the destination mask first, so 0xFF000000 hoists BEFORE 0xFFFFFF
 *    and the $a0/$v1/$a1 roles come out permuted (18 mismatched, all regalloc).
 *    Spelled as PsyQ's P_TAG `addr:24` bitfield, store_bit_field masks the VALUE first
 *    and then `expand_binop(ior, temp, value)` -- which fixes, in one edit, (a) the
 *    0xFFFFFF-before-0xFF000000 movable hoist order, (b) both `or` operand orders, and
 *    (c) the whole $a1/$v1/$a0 allocation. A local `register ... __asm__("$3")` pin on
 *    the OT pointer is INERT here (gcc-2.7.2 only honours a local reg var at an asm
 *    that references it) -- the bitfield spelling is the real lever.
 *
 * The packet is a 0x18-byte custom prim: tag, an inline GP0(E1) draw-mode word, then a
 * semi-transparent gouraud LINE_G2 body (code 0x52) whose two vertices come straight
 * from gte_stsxy01 into +0xC / +0x14.
 */

/* ---- GTE inline-asm macros (same spelling as the matched ov_SC03_099 TU) ---- */
#define gte_ldv3_80181E04(r0, r1, r2) __asm__ volatile ( \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )

#define gte_rtpt_80181E04() __asm__ volatile ("nop;nop;rtpt")

#define gte_stflg_80181E04(r0) __asm__ volatile (\
    "cfc2 $12, $31;"                             \
    "nop;"                                       \
    "sw $12, 0( %0 )"                            \
    :                                            \
    : "r"( r0 )                                  \
    : "$12", "memory" )

#define gte_stsxy01_80181E04(r0, r1) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 )                       \
    : "memory" )

#define gte_stsz3_80181E04(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )

/* §246-2: every parallel global spelled as an array of one 0x50-byte record type so
 * gcc fuses all their address computations onto ONE scaled-offset giv. §200 aliases
 * keep the TU's own `extern s32 D_801EDA4C[]` spellings untouched. */
typedef struct { u32 addr:24; u32 len:8; } PTag_80181E04;
typedef struct { s32 v; u8 pad[0x4C]; } W50_80181E04;
typedef struct { u16 h; u8 pad[0x4E]; } H50_80181E04;

extern W50_80181E04 wD801EDA44[] __asm__("D_801EDA44");
extern W50_80181E04 wD801EDA48[] __asm__("D_801EDA48");
extern W50_80181E04 wD801EDA4C[] __asm__("D_801EDA4C");
extern W50_80181E04 wD801EDA50[] __asm__("D_801EDA50");
extern W50_80181E04 wD801EDA54[] __asm__("D_801EDA54");
extern W50_80181E04 wD801EDA58[] __asm__("D_801EDA58");
extern W50_80181E04 wD801EDA70[] __asm__("D_801EDA70");
extern W50_80181E04 wD801EDA74[] __asm__("D_801EDA74");
extern W50_80181E04 wD801EDA78[] __asm__("D_801EDA78");
extern W50_80181E04 wD801EDA7C[] __asm__("D_801EDA7C");
extern W50_80181E04 wD801EDA80[] __asm__("D_801EDA80");
extern W50_80181E04 wD801EDA84[] __asm__("D_801EDA84");
extern W50_80181E04 wD801EDA88[] __asm__("D_801EDA88");
extern W50_80181E04 wD801EDA8C[] __asm__("D_801EDA8C");
extern W50_80181E04 wD801EDA90[] __asm__("D_801EDA90");
extern H50_80181E04 hD801EDA4E[] __asm__("D_801EDA4E");
extern H50_80181E04 hD801EDA52[] __asm__("D_801EDA52");
extern H50_80181E04 hD801EDA56[] __asm__("D_801EDA56");
extern H50_80181E04 hD801EDA72[] __asm__("D_801EDA72");
extern H50_80181E04 hD801EDA76[] __asm__("D_801EDA76");
extern H50_80181E04 hD801EDA7A[] __asm__("D_801EDA7A");

extern void func_800547D8(s32, MATRIX2 *);
extern void func_80052E38(MATRIX2 *);
extern u8 *D_800A5E60;
extern u8 D_800A6610[];
extern s16 D_801F3168;

void func_80181E04(void)
{
    MATRIX2 mtx;                                /* sp+0x10 */
    SVECTOR2 va;                                /* sp+0x30 */
    SVECTOR2 vb;                                /* sp+0x38 */
    struct { s32 flag, sz0, sz1, sz2; } g;      /* sp+0x40 */
    u8 *pkt;
    u8 *ot;
    u32 *otp;
    s32 i;
    s32 z;

    func_800547D8((s32)&D_801F3168, &mtx);
    func_80052E38(&mtx);

    ot = &D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    pkt = D_800A5E60;

    for (i = 0; i < 0x100; i++) {
        if (wD801EDA44[i].v != 0) {
            va.vx = hD801EDA4E[i].h;
            va.vy = hD801EDA52[i].h;
            va.vz = hD801EDA56[i].h;
            vb.vx = hD801EDA72[i].h;
            vb.vy = hD801EDA76[i].h;
            vb.vz = hD801EDA7A[i].h;

            wD801EDA4C[i].v += wD801EDA7C[i].v;
            wD801EDA50[i].v += wD801EDA80[i].v;
            wD801EDA54[i].v += wD801EDA84[i].v;
            if (wD801EDA48[i].v == 0) {
                wD801EDA70[i].v += wD801EDA7C[i].v;
                wD801EDA74[i].v += wD801EDA80[i].v;
                wD801EDA78[i].v += wD801EDA84[i].v;
            } else {
                wD801EDA48[i].v = wD801EDA48[i].v - 1;
            }
            wD801EDA7C[i].v += wD801EDA88[i].v;
            wD801EDA80[i].v += wD801EDA8C[i].v;
            wD801EDA84[i].v += wD801EDA90[i].v;

            if (wD801EDA7C[i].v > 0) {
                if (wD801EDA4C[i].v > wD801EDA58[i].v) {
                    wD801EDA44[i].v = 0;
                }
            } else {
                if (wD801EDA4C[i].v < wD801EDA58[i].v) {
                    wD801EDA44[i].v = 0;
                }
            }

            if (wD801EDA44[i].v != 0) {
                gte_ldv3_80181E04(&va, &vb, &vb);
                gte_rtpt_80181E04();
                gte_stflg_80181E04(&g.flag);
                if ((g.flag & 0x7F85E000) == 0) {
                    gte_stsxy01_80181E04(pkt + 0xC, pkt + 0x14);
                    gte_stsz3_80181E04(&g.sz0, &g.sz1, &g.sz2);
                    z = g.sz0 + g.sz1;
                    if (z < 0) {
                        z += 7;
                    }
                    pkt[3] = 5;
                    pkt[0xB] = 0x52;
                    pkt[9] = 0xE0;
                    pkt[0xA] = 0x88;
                    pkt[0x10] = 0x40;
                    pkt[0x11] = 0x60;
                    *(u32 *)(pkt + 4) = 0xE1000020;
                    pkt[8] = 0;
                    pkt[0x12] = 0x10;
                    otp = (u32 *)((z >> 3) * 4 + (s32)ot);
                    ((PTag_80181E04 *)pkt)->addr = ((PTag_80181E04 *)otp)->addr;
                    ((PTag_80181E04 *)otp)->addr = (u32)pkt;
                    pkt += 0x18;
                }
            }
        }
    }
    D_800A5E60 = pkt;
}



extern u8 D_801F2A44[];
extern u8 D_801F2A48[];
extern s32 D_801F3044;
extern s32 D_801F3048;

void func_80182238(void) {
    s32 i;
    s32 off;

    i = 0;
    off = 0;
    do {
        *(u32 *)(D_801F2A44 + off) = 0;
        *(u32 *)(D_801F2A48 + off) = 0;
        off += 0x4C;
        i++;
    } while (i < 0x14);
    D_801F3044 = 0;
    D_801F3048 = 0x40;
}


#include "common.h"

/* §200 alias: this TU spells func_8001D074 `void (s32,s32)` (lines 119/124), but the target
   stores its $v0 into the slot pointer.  Bind our own identifier to the same link name so the
   TU's spelling stays untouched (same trick already used for func_8018183C at line 5156). */
extern s32 aF8001D074(s32, s32) __asm__("func_8001D074");
extern void func_800233CC(void *, unsigned short);
extern void func_8001CD9C(int, void *);

extern u8 D_801F2A44[];
extern u8 D_801F2A48[];
extern u8 D_801F2A50[];
extern u8 D_801F2A51[];
extern u8 D_801F2A52[];
extern u8 D_801F2A54[];
extern u8 D_801F2A55[];
extern u8 D_801F2A56[];
extern u8 D_80188B74[];
extern u8 D_80188B76[];
extern u8 D_80188B78[];
extern s32 D_801F3044;
extern s32 D_801F3048;
/* Scalar alias for D_801EDA34: the TU spells it `s32 []`, and `D_801EDA34[0] += 4` makes gcc
   CSE the array base into a register (`la $v1,sym; lw 0($v1); sw 0($v1)`).  The target uses the
   plain global form (`lui/lw %lo`, then a fresh `lui/sw %lo`), which only a SCALAR ref emits. */
extern s32 aD_801EDA34 __asm__("D_801EDA34");

/* The object func_8001D074 hands back.  It is spelled as a struct (not `*(u16 *)(p + 8)`) on
   purpose: gcc-2.7.2's alias oracle (alias.c true_/output_dependence) disambiguates a
   MEM_IN_STRUCT_P + varying-address reference against a fixed-address non-struct global, which
   is what lets the `D_801F3044` store schedule up into the `lhu` shadow, ahead of the `sh 0xC`. */
typedef struct {
    s32 unk0;   /* 0x0 */
    u32 unk4;   /* 0x4 */
    u16 unk8;   /* 0x8 */
    u16 unkA;   /* 0xA */
    u16 unkC;   /* 0xC */
} Obj_80182284;

s32 func_80182284(void) {
    s32 i;
    u8 *bytes;
    s32 *ct;
    s32 off;
    s32 *en;
    s32 *ct2;
    s32 *st;
    s32 off2;
    s32 n;
    u8 *p;

    i = 0;
    bytes = D_801F2A50;
    ct = (s32 *)(bytes - 4);
    off = 0;
    do {
        if (*(s32 *)(D_801F2A44 + off) != 0 && *ct >= 0x11) {
            func_800233CC(bytes, (*ct -= 4));
        }
        bytes += 0x4C;
        ct += 0x13;
        i++;
        off += 0x4C;
    } while (i < 0x14);

    if (D_801F3044 >= 0xC) {
        return 1;
    }
    if (--D_801F3048 == -1) {
        /* if/else, NOT `?:` — the two stores cross_jump into one merged tail block, which is why
           the `sw %lo(D_801F3048)` lands first at .L80182358 instead of being scheduled down. */
        if (D_801F3044 >= 4) {
            D_801F3048 = 1;
        } else {
            D_801F3048 = 8;
        }
        i = 0;
        en = (s32 *)D_801F2A48;
        ct2 = en + 1;
        st = en - 1;
        off2 = 0;
        aD_801EDA34 += 4;
        for (; i < 0x14; i++) {
            if (*st == 0) {
                *en = aF8001D074(0x3E, 0x7D);
                if (*en == 0) break;
                *st = 1;
                *ct2 = 0x80;
                p = D_801F2A50 + off2;
                func_8001CD9C(*en, p);
                D_801F2A51[off2] = 0xE0;
                D_801F2A50[off2] = 0;
                D_801F2A52[off2] = 0x88;
                D_801F2A54[off2] = 0;
                D_801F2A55[off2] = 0;
                D_801F2A56[off2] = 0;
                func_800233CC(p, *(u16 *)ct2);
                n = D_801F3044;
                ((Obj_80182284 *)*en)->unk8 = *(u16 *)(D_80188B74 + n * 8);
                ((Obj_80182284 *)*en)->unkA = *(u16 *)(D_80188B76 + n * 8);
                ((Obj_80182284 *)*en)->unkC = *(u16 *)(D_80188B78 + n * 8);
                D_801F3044 = n + 1;
                {
                    /* $3 pin: without it local-alloc hands $v1 to the 0x50000040 constant and
                       $a0 to this pointer — the exact inverse of the target (closeness 6). */
                    register Obj_80182284 *o __asm__("$3");
                    o = (Obj_80182284 *)*en;
                    o->unk4 |= 0x50000040;
                }
                break;
            }
            en += 0x13;
            ct2 += 0x13;
            st += 0x13;
            off2 += 0x4C;
        }
    }
    return 0;
}


#include "common.h"

/* func_801824EC (ov_SC01_001, 156 ins) — MATCH.
 *
 * Three levers, in the order they were needed:
 *
 * 1. §246-1 ADDRESS-FROM-INDEX / array-index form. The target addresses
 *    D_801F2A44/48/4C as `lui $at,%hi(sym); addu $at,$at,$s0; lw %lo(sym)($at)`
 *    with ONE 0x4C-stride scaled-offset giv ($s0) shared by all three symbols
 *    (§246-2). Spelling them `u8 sym[]` + `*(s32 *)(sym + off)` makes combine_givs
 *    fuse each into its own stepped POINTER instead (-21 ins). The `[][19]`
 *    array-index spelling is what births the scaled-index giv anchored on %hi/%lo.
 *
 * 2. §193-F / §148-A2 preheader ORDER, and the reason it is a giv question.
 *    The target's preheader is [arg copy][li 2][li 0x400][lui/addiu &D_801F2A50]
 *    [+4][copy][base][index=0]. loop.c emits hoisted MOVABLES before strength
 *    reduction's GIV INITS, so the address chain landing AFTER the two constants
 *    proves &D_801F2A50 + i*0x4C and +4 are GIVS, not source-initialised pointers.
 *    Walking them as source locals (`p2 += 0x4C`) puts the chain first and costs
 *    11 mismatched prologue insns; writing them inline as `aD801F2A50[i]` /
 *    `aD801F2A50[i] + 4` moves them behind the movables and fixes all 11.
 *
 * 3. The same restructure kills the 0xC00 hoist for free. With source-walked
 *    pointers, `-dL` reads `Loop from 25 to 357: 82 real insns` and the two
 *    textually equal `li 0xC00` movables merge to savings 2 / life 2, so
 *    26*2*2 = 104 >= 82 admits a third hoist the target does not have. The
 *    index-only loop shifts insn_count over the cutoff. `2` and `0x400` stay
 *    literals on purpose: combine_movables merges the dispatch's `case 2:`
 *    constant with the two `D_801F2A44[i] = 2` stores (savings 3 / life 3), which
 *    is what makes the case-2 test `beq $s1,$s5` instead of `li $v0,2; beq`.
 *
 * Also: the -0x2E9 / -0x292 stores must go through `s16 *`; a `u16 *` lvalue
 * converts them to 0xFD17 / 0xFD6E and emits `ori`, not `addiu`.
 * The 4-byte align-1 struct is the lwl/lwr + swl/swr block move.
 * §200 aliases everywhere so the TU's own `extern u8 D_801F2A44[]` spelling and
 * its `void func_8001D074(s32,s32)` prototype stay untouched.
 */

typedef struct { u8 d[4]; } Blk4_801EC660;

extern u32 aD801F2A44[][19] __asm__("D_801F2A44");
extern u32 aD801F2A48[][19] __asm__("D_801F2A48");
extern u32 aD801F2A4C[][19] __asm__("D_801F2A4C");
extern u8  aD801F2A50[][76] __asm__("D_801F2A50");
extern Blk4_801EC660 aD801EC660 __asm__("D_801EC660");
extern Blk4_801EC660 aD801EC664 __asm__("D_801EC664");
extern s32 aF8001D074(s32, s32) __asm__("func_8001D074");
extern void func_8001CD50(s32, s32);
extern void func_800233CC(void *, unsigned short);

void func_801824EC(s32 arg0) {
    s32 i;
    s32 h;

    i = 0;
    do {
        if (aD801F2A44[i][0] == 0) {
            h = aF8001D074(0x3E, 0x7D);
            aD801F2A48[i][0] = h;
            if (h == 0) {
                return;
            }
            func_8001CD50(h, (s32)aD801F2A50[i]);
            *(u32 *)(aD801F2A48[i][0] + 4) |= 0x50000000;
            *(u16 *)(aD801F2A48[i][0] + 8) = 0;
            *(s16 *)(aD801F2A48[i][0] + 0xA) = -0x2E9;
            *(u16 *)(aD801F2A48[i][0] + 0xC) = 0;
            switch (arg0) {
            case 0:
                *(u16 *)(aD801F2A48[i][0] + 0x1E) = 0xC00;
                *(u16 *)(aD801F2A48[i][0] + 0x10) = 0x400;
                *(u16 *)(aD801F2A48[i][0] + 0x12) = 0x180;
                aD801F2A44[i][0] = 2;
                break;
            case 1:
                *(u16 *)(aD801F2A48[i][0] + 0x1E) = 0xC00;
                *(u16 *)(aD801F2A48[i][0] + 0x10) = 0x400;
                *(u16 *)(aD801F2A48[i][0] + 0x12) = 0xE80;
                aD801F2A44[i][0] = 2;
                break;
            case 2:
                *(s16 *)(aD801F2A48[i][0] + 0xA) = -0x292;
                *(u16 *)(aD801F2A48[i][0] + 0x10) = 0x400;
                aD801F2A44[i][0] = 3;
                break;
            }
            aD801F2A4C[i][0] = 0x10;
            func_800233CC(aD801F2A50[i], 0x10);
            *(Blk4_801EC660 *)aD801F2A50[i] = aD801EC660;
            *(Blk4_801EC660 *)(aD801F2A50[i] + 4) = aD801EC664;
            return;
        }
        i++;
    } while (i < 20);
}


extern u8 D_801F2A50[];
extern u8 D_801F2A51[];
extern u8 D_801F2A52[];
extern void func_800233CC(void *, unsigned short);
extern void func_80182974(u8 *, s8);
extern void func_80182A14(s32);

s32 func_8018275C(void) {
    s32 ret = 0;
    s32 i = 0;
    register u8 *base __asm__("$2") = D_801F2A50;
    s32 *st = (s32 *)(base - 0xC);
    s32 *en = (s32 *)(base - 8);
    s32 *ct = (s32 *)(base - 4);
    register u8 *bytes __asm__("$17") = base;
    s32 pos = 0;

    for (; i < 0x14; i++) {
        switch (*st) {
        case 1:
            if (i > 0) break;
            if (*ct < 0x180) {
                *ct += 0x20;
                if (*(s16 *)(*en + 0xC) >= -0x17F) {
                    *(s16 *)(*en + 0xC) -= 0x20;
                }
            }
            func_80182974(bytes, 8);
            func_80182974(bytes + 4, 8);
            func_800233CC(bytes, *(u16 *)ct);
            if (D_801F2A50[pos] == 0xFF &&
                D_801F2A51[pos] == D_801F2A50[pos] &&
                D_801F2A52[pos] == D_801F2A51[pos]) {
                ret = 1;
            }
            break;
        case 3:
            *ct += 0x10;
            func_80182974(bytes, -8);
            func_80182974(bytes + 4, -8);
            func_800233CC(bytes, *(u16 *)ct);
            if (*ct >= 0x381) {
                func_80182A14(*en);
                *st = 0;
            }
            break;
        case 2:
            func_800233CC(bytes, (*ct += 0x28));
            *(u16 *)(*en + 0x14) += 0x10;
            if (*ct >= 0x201) {
                func_80182A14(*en);
                *st = 0;
            }
            break;
        }
        st += 19;
        en += 19;
        ct += 19;
        bytes += 0x4C;
        pos += 0x4C;
    }
    return ret;
}


void func_80182974(u8 *param_1, s8 param_2) {
    s32 iVar1;
    s32 iVar2;
    s32 iVar3;
    s32 iVar4;
    u8 bVar5;
    u8 bVar6;
    u8 bVar7;

    iVar2 = (s32)param_2;
    if (iVar2 != 0) {
        iVar1 = (u32)*param_1 + iVar2;
        bVar6 = (u8)iVar1;
        iVar3 = (u32)param_1[1] + iVar2;
        bVar5 = (u8)iVar3;
        iVar4 = (u32)param_1[2] + iVar2;
        bVar7 = (u8)iVar4;
        if (0 < iVar2) {
            if (0xff < iVar1) {
                bVar6 = 0xff;
            }
            if (0xff < iVar3) {
                bVar5 = 0xff;
            }
            if (0xff < iVar4) {
                bVar7 = 0xff;
            }
        } else {
            if (iVar1 < 0) {
                bVar6 = 0;
            }
            if (iVar3 < 0) {
                bVar5 = 0;
            }
            if (iVar4 < 0) {
                bVar7 = 0;
            }
        }
        *param_1 = bVar6;
        param_1[1] = bVar5;
        param_1[2] = bVar7;
    }
}


















extern void func_80016714(void *a0, s32 a1);
void func_80182A14(s32 arg0)
{
  if ((*((u16 *) arg0)) == 0x1)
  {
    func_80016714((void *) arg0, 0x84);
  }
  else
  {
    func_80016714((void *) arg0, 0x38);
  }
}

extern u8 D_801F2A44[];
extern u8 D_801F2A48[];
extern s32 D_801EDA44;
extern void func_80016714(void *a0, s32 a1);

void func_80182A48(void) {
    s32 flag;
    s32 i;
    s32 p;
    s32 ent;
    s32 j;

    flag = 1;
    p = (s32)&(*(s32 *)D_801F2A44);
    i = 0;
    do {
        if (*(s32 *)p != 0) {
            ent = *(s32 *)((s32)&(*(s32 *)D_801F2A48) + i);
            if (*(u16 *)ent == flag) {
                func_80016714((void *)ent, 0x84);
            } else {
                func_80016714((void *)ent, 0x38);
            }
            *(s32 *)p = 0;
        }
        p += 0x4C;
        i += 0x4C;
    } while (p < (s32)&(*(s32 *)D_801F2A44) + 0x5F0);

    j = 0x4FB0;
    do {
        *(s32 *)((s32)&D_801EDA44 + j) = 0;
        j -= 0x50;
    } while (j >= 0);
}


s32 func_80182B00(s32 a0) {
    u16 *ptr = *(u16 **)(a0 + 0xCC);
    if (*ptr != 0x8000) {
        *(u16 *)(a0 + 6) = ptr[0];
        *(u16 *)(a0 + 10) = ptr[1];
        *(u16 *)(a0 + 14) = ptr[2];
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = ptr[3];
        ptr += 4;
        *(u16 **)(a0 + 0xCC) = ptr;
        return *ptr == 0x8000;
    }
    return 1;
}


void func_80182B60(s32 *a0, s32 a1) {
        *(s32*)((s32)a0 + 0xCC) = a1;
    }


void func_80182B68(s32 arg0) {
    extern u8 D_80188C0C[][8];
    MoveImage(&D_80188C0C[arg0], 0x280, 0x188);
}


extern u8 D_80188BF4[][8];

void func_80182B9C(arg0)
s32 arg0;
{
    extern u8 D_80188BF4[][8];
    MoveImage(&D_80188BF4[arg0], 0x200, 0x100);
}


void func_80182BD0(s32 arg0) {
    extern s32 D_801F3040;
    extern u8 D_80188C0C[][8];

    D_801F3040 = 1;
    MoveImage(&D_80188C0C[arg0], 0x280, 0x188);
}


void func_80182C10(void) {
    extern u16 D_80188C0C[];
    extern s32 D_801F3038;
    extern s32 D_801F303C;
    extern s32 D_801F3040;

    MoveImage(D_80188C0C, 0x280, 0x188);
    D_801F3040 = 0;
    D_801F3038 = 0x3C;
    D_801F303C = 0;
}


extern s32 D_801F3038;
extern s32 D_801F303C;
extern s32 D_801F3040;
extern u8 D_80188C14[];
extern u16 D_80188C0C[];

void func_80182C58(void) {
    if (D_801F3040 == 0) {
        if (D_801F303C != 0) {
            D_801F303C--;
            if (D_801F303C == 0) {
                MoveImage(D_80188C0C, 0x280, 0x188);
                D_801F3038 = 0x3C;
            }
        } else if (D_801F3038 != 0) {
            D_801F3038--;
            if (D_801F3038 == 0) {
                MoveImage(D_80188C14, 0x280, 0x188);
                D_801F303C = 2;
            }
        }
    }
}


#include "common.h"

/* NOTE (load-bearing): D_800DE2F8 MUST be declared as an ARRAY and read as
 * D_800DE2F8[0].  §229 declaration corollary + §20 global-RMW: the target
 * materialises this one address ONCE (`lui/addiu %lo` -> `lw 0($r)` / `sw 0($r)`)
 * while every other global keeps the direct `%lo` fold.  A plain `extern s32`
 * spelling emits `lui;lw %lo` + `lui $at;sw %lo` instead and de-rails the whole
 * block schedule (112 ins vs 107).  A pointer VARIABLE (`s32 *p = &D_800DE2F8`)
 * is NOT equivalent -- it becomes an alias barrier and blocks the 1-statement
 * load lookahead (114 ins).
 * Statement order is plain ascending 2F8..30C in all three arms; sched1 does the
 * (300,304) / (308,30C) pair swaps that the target shows. */
extern s32 D_800DE2F8[];
extern s32 D_800DE2FC;
extern s32 D_800DE300;
extern s32 D_800DE304;
extern s32 D_800DE308;
extern s32 D_800DE30C;

void func_80182D04(s32 arg0) {
    switch (arg0) {
    case 0:
        D_800DE2F8[0] |= 0x1000000;
        D_800DE2FC |= 0x1000000;
        D_800DE300 |= 0x1000000;
        D_800DE304 |= 0x1000000;
        D_800DE308 |= 0x1000000;
        D_800DE30C |= 0x1000000;
        break;
    case 1:
        D_800DE2F8[0] &= ~0x1000000;
        D_800DE2FC &= ~0x1000000;
        D_800DE300 &= ~0x1000000;
        D_800DE304 |= 0x1000000;
        D_800DE308 |= 0x1000000;
        D_800DE30C &= ~0x1000000;
        break;
    case 2:
        D_800DE2F8[0] &= ~0x1000000;
        D_800DE2FC |= 0x1000000;
        D_800DE300 &= ~0x1000000;
        D_800DE304 |= 0x1000000;
        D_800DE308 |= 0x1000000;
        D_800DE30C &= ~0x1000000;
        break;
    }
}


#include "common.h"

extern s32 func_8012C51C(void *a0, s32 a1);
extern s32 D_801EDA30;

void func_80182EB0(s32 a0, s32 a1) {
    s16 buf[12];
    s32 i;

    D_801EDA30 = 0;
    for (i = 0; i < a1; i++) {
        buf[0] = *(u16 *)a0;
        buf[1] = *(u16 *)(a0 + 2);
        buf[2] = *(u16 *)(a0 + 4);
        buf[3] = 0x3B8;
        buf[5] = 0;
        buf[4] = 0;
        a0 += 8;
        func_8012C51C(buf, 0);
    }
}



extern void (*D_80188E58[])(void);

void func_80182F58(void *a0) {
    D_80188E58[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B200(u8 *a0);
extern s32 D_80199934;
extern s32 D_80183B84;

void func_80182F94(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    s32 v0;

    s0 = a0;
    v0 = func_8012C1B8();
    *(s32 *)(s0 + 0x20) = v0;
    s1 = v0;

    if (v0 == 0) {
        func_8012CAE4(s0);
    } else {
        func_8001C214(s1, (s32)&D_80199934);
        func_8001D0E8(s1, 0x7FFF, 0x7FFF);
        func_8012A828(s0, (s32)&D_80183B84);
        func_8012B200((u8 *)s0);
        *(s32 *)(s0 + 0x4C) = 0;
        *(s32 *)(s0 + 0x44) = 0;
        *(s32 *)(s0 + 0x48) = 0x20000;
        *(u16 *)(s0 + 0x2) = *(u16 *)(s0 + 0x2) + 1;
    }
}


extern s32 D_801EDA30;

void func_80183034(void *param_1)
{
    if (func_80183128(param_1, 1, 0x10) != 0) {
        register u32 v __asm__("$2");
        int d;
        v = 0xFFF40000;
        d = D_801EDA30;
        *(u32 *)((s32)param_1 + 0x18) = 0;
        *(u32 *)((s32)param_1 + 0x14) = v;
        if (d == 0) {
            D_801EDA30 = 1;
            func_8002D4C8(0xB98, 0);
        }
        *(u16 *)((s32)param_1 + 2) += 1;
    }
}


void func_801830A8(void *a0) {
    if (func_80183128(a0, 1, 0) != 0) {
        *(u16 *)((s32)a0 + 2) += 1;
    }
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) += 0x100;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += 0x100;
}


void func_80183120(void) {
}

extern void func_8012AD80(s32 a0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
s32 func_80183128(void *a0, s32 a1, s32 a2) {
    s16 arr1[3];
    s16 arr2[3];
    s32 res_val;
    arr1[0] = *(u16 *)((s32)a0 + 0x3A);
    arr1[1] = *(u16 *)((s32)a0 + 0x3E) + a2;
    arr1[2] = *(u16 *)((s32)a0 + 0x42);
    func_8012AD80((s32)a0);
    arr2[0] = *(u16 *)((s32)a0 + 0x6);
    arr2[1] = *(u16 *)((s32)a0 + 0xA) + a2;
    arr2[2] = *(u16 *)((s32)a0 + 0xE);
    res_val = func_8012CEB0((s32)arr1, (s32)arr2, a1);
    *(u16 *)((s32)a0 + 0x6) = arr2[0];
    *(u16 *)((s32)a0 + 0xA) = arr2[1] - a2;
    *(u16 *)((s32)a0 + 0xE) = arr2[2];
    if ((res_val & 0x6000) != 0) {
        *(s32 *)((s32)a0 + 0x14) = 0;
    }
    return res_val;
}


void func_801831EC(void) {
    extern s32 D_801EDA3C;
    extern s32 D_801EDA40;
    extern u8 D_80188D48[];
    extern u8 D_80188D4A[];
    extern u8 D_80188D4C[];
    extern s32 func_80143C74(s32 a0, s32 a1);
    s32 s0;
    s32 iVar3;
    s32 iVar4;
    u16 uVar1;

    s0 = D_801EDA3C;
    if (D_801EDA40 < 0xD) {
        D_801EDA40 = D_801EDA40 + 1;
        iVar3 = func_80143C74(0, 0);
        iVar4 = s0 * 8;
        if (iVar3 != 0) {
            *(u16 *)(iVar3 + 6) = *(u16 *)(D_80188D48 + iVar4);
            *(u16 *)(iVar3 + 10) = *(u16 *)(D_80188D4A + iVar4);
            uVar1 = *(u16 *)(D_80188D4C + iVar4);
            *(s32 *)(iVar3 + 0x14) = 0xFFFC0000;
            *(s32 *)(iVar3 + 0x10) = 0;
            *(s32 *)(iVar3 + 0x18) = 0;
            *(s32 *)(iVar3 + 0x44) = 0;
            *(s32 *)(iVar3 + 0x48) = 0x200;
            *(s32 *)(iVar3 + 0x4C) = 0;
            *(u16 *)(iVar3 + 0xE) = uVar1;
        }
        s0 += 7;
        if (s0 >= 0xC) {
            s0 -= 0xB;
        }
        D_801EDA3C = s0;
    }
}


extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_801833A0(s32, s16*, s16*, void*);
extern u8 D_80188E68;
extern u8 D_801ED9A8;

void func_801832BC(s32 param_1) {
    struct {
        s16 mat[10];
        s32 pos[3];
        s32 dead[8];
        u16 vec[6];
    } l;

    if (*(s32 *) (param_1 + 0x90) != 0) {
        s32 temp = *(s32 *) (*(s32 *) (param_1 + 0x20) + 0x20);
        l.vec[0] = *(u16 *) (temp + 0x10E);
        l.vec[1] = *(u16 *) (temp + 0x110);
        l.vec[2] = *(u16 *) (temp + 0x112);
        func_80049CAC(l.vec, l.mat);
        l.pos[0] = *(s16 *) (temp + 0x108);
        l.pos[1] = *(s16 *) (temp + 0x10A);
        l.pos[2] = *(s16 *) (temp + 0x10C);
        func_8012F14C(l.mat, &D_80188E68, &D_801ED9A8);
        func_8012F14C(l.mat, &D_80188E68 + 8, &D_801ED9A8 + 8);
        ((void (*)(s32, s32, s32))func_801833A0)(*(s32 *) (param_1 + 0x20) + 0x34, &D_801ED9A8, &D_801ED9A8 + 8);
    }
}


extern void func_801835C8(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u16 D_800B99DA;
extern s8 D_80188DA8[];
extern s8 D_80188DBC[];
extern s32 func_80017758(void *a0, void *a1);

void func_801833A0(s32 param_1, s16 *param_2, s16 *param_3, void *param_4) {
    u8 buf[0x54];
    s8 *p;
    s32 t;
    s16 i;

    func_801835C8(param_1, ((s16 *)param_2), ((s16 *)param_3), buf);

    *(s16 *)(buf + 0x3C) = 0;
    *(s16 *)(buf + 0x34) = 0;
    *(s16 *)(buf + 0x24) = 0;
    *(s16 *)(buf + 0x2C) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    if (D_800B99DA & 1) {
        buf[0x46] = 0x58;
    } else {
        buf[0x46] = 0x48;
    }
    buf[0x45] = buf[0x46] >> 2;
    buf[0x44] = buf[0x45];

    p = D_80188DA8;
    buf[0x42] = 0;
    buf[0x41] = 0;
    buf[0x40] = 0;
    buf[0x4A] = 0;
    buf[0x49] = 0;
    buf[0x48] = 0;
    buf[0x4E] = 0;
    buf[0x4D] = 0;
    buf[0x4C] = 0;
    *(s32 *)(buf + 0x50) = 0x50000000;

    for (i = 0; i < 4; i++) {
        t = *p++;
        *(s16 *)(buf + 0x20) = t;
        t = *p++;
        *(s16 *)(buf + 0x22) = t;
        t = *p++;
        *(s16 *)(buf + 0x30) = t;
        t = *p++;
        *(s16 *)(buf + 0x32) = t;
        t = *p++;
        *(s16 *)(buf + 0x38) = t;
        t = *p--;
        *(s16 *)(buf + 0x3A) = t;
        func_80017758(buf + 0x20, buf);
    }

    p = D_80188DBC;
    *(s16 *)(buf + 0x2C) = -0x12;
    *(s16 *)(buf + 0x3A) = 0;
    *(s16 *)(buf + 0x32) = 0;
    *(s16 *)(buf + 0x22) = 0;
    *(s16 *)(buf + 0x2A) = 0;
    *(s16 *)(buf + 0x28) = 0;
    buf[0x46] = buf[0x46] << 1;
    buf[0x44] = buf[0x45] = buf[0x45] << 1;

    for (i = 0; i < 4; i++) {
        t = *p++;
        *(s16 *)(buf + 0x20) = t;
        t = *p++;
        *(s16 *)(buf + 0x24) = t;
        t = *p++;
        *(s16 *)(buf + 0x30) = t;
        t = *p++;
        *(s16 *)(buf + 0x34) = t;
        t = *p++;
        *(s16 *)(buf + 0x38) = t;
        t = *p--;
        *(s16 *)(buf + 0x3C) = t;
        if (i == 2) {
            buf[0x4E] = buf[0x46];
            buf[0x4D] = buf[0x44];
            buf[0x4C] = buf[0x4D];
        } else if (i == 3) {
            buf[0x4E] = 0;
            buf[0x4D] = 0;
            buf[0x4C] = buf[0x4D];
            buf[0x42] = buf[0x46];
            buf[0x41] = buf[0x44];
            buf[0x40] = buf[0x44];
        }
        func_80017758(buf + 0x20, buf);
    }
}


extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D23D0(void *a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32 ratan2(s32 a0, s32 a1);
extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;

void func_801835C8(s32 param_1, s16 *param_2, s16 *param_3, void *param_4) {
    s16 mid[3];
    s16 dir[3];
    s32 pos[3];
    mid[0] = (param_2[0] + param_3[0]) >> 1;
    mid[1] = (param_2[1] + param_3[1]) >> 1;
    mid[2] = (param_2[2] + param_3[2]) >> 1;
    ((void (*)(s32, void *, void *))func_8012F14C)(param_1, mid, mid);
    func_800D20C0(mid, dir, 8);
    func_80017E68(mid, param_4);
    dir[0] = (u16)param_3[0] - (u16)param_2[0];
    dir[1] = (u16)param_3[1] - (u16)param_2[1];
    dir[2] = (u16)param_3[2] - (u16)param_2[2];
    ApplyMatrixSV((void *)param_1, dir, dir);
    func_800D23D0(dir);
    RotMatrixYXZ(dir, param_4);
    pos[0] = D_801269A4 - mid[0];
    pos[1] = D_801269A8 - mid[1];
    pos[2] = D_801269AC - mid[2];
    ApplyTransposeMatrixLV(param_4, pos, pos);
    dir[2] = -ratan2(pos[0], pos[1]);
    RotMatrixYXZ(dir, param_4);
}


/* func_80183748 — copies 3 packed 10-byte source records into the 3 consecutive
 * 16-byte records at D_800A5E88[0..2] ({s32 a,b,c; u8 d,e,f,g}) and registers
 * each one with func_80028620(i, &rec[i]).  Sibling of func_8013CF68
 * (ov_SC03_099/jr_8013C98C), which writes the same three records unrolled.
 *
 * TWO load-bearing shape facts (cookbook §164-06 + §148-A, both read off `cc1 -dL`):
 *
 * 1. The preheader order is  j=0 ; $s1=param_1 ; $s0=0 .  A loop.c giv-init is
 *    ALWAYS emitted immediately before loop_start, i.e. AFTER every source-level
 *    preheader insn, so no source ordering can put the source pointer BETWEEN the
 *    two counters.  Both $s1 and $s0 therefore have to be giv inits, and
 *    `strength_reduce` walks `loop_iv_list` = the REVERSE of the increment order
 *    (loop.c:4295 prepends, :3717 walks).  Hence `j++` is written BEFORE `m += 10`
 *    so j's class is processed LAST and its giv (k) is emitted after m's giv (the
 *    pointer).  `k = j * 16;` must be an explicit statement: without the pseudo the
 *    six symbol addresses are recomputed from the biv as an inline `sll` (-1 ins).
 *
 * 2. loop.c:1631 hoists an invariant iff `threshold * savings * lifetime >= insn_count`,
 *    and threshold = (loop_has_call ? 1 : 2) * (1 + n_non_fixed_regs) = 29 here.
 *    This loop is 29 RTL insns, so `&D_800A5E88` (savings 1, lifetime 1) hoists into
 *    a callee-saved register that the target rematerializes inline — +3 instructions.
 *    The zero-byte `__asm__("" : :)` below is ONE extra RTL insn: 29 -> 30, so
 *    29 >= 30 is false and the address stays in the loop.  Solo-proven: deleting
 *    that one line takes this body from MATCH to closeness 48 / 52 ins.
 */

extern void func_80028620(s32, void *);

void func_80183748(u8 *param_1)
{

    extern u8 D_800A5E88;
    extern u8 D_800A5E8C;
    extern u8 D_800A5E90;
    s32 j;
    s32 m;
    s32 k;

    j = 0;
    m = 0;
    do {
        k = j * 16;
        __asm__("" : :);
        (&D_800A5E94)[k] = param_1[m];
        (&D_800A5E95)[k] = param_1[m + 1];
        (&D_800A5E96)[k] = param_1[m + 2];
        *(s32 *)(&D_800A5E88 + k) = *(s16 *)(param_1 + m + 4);
        *(s32 *)(&D_800A5E8C + k) = *(s16 *)(param_1 + m + 6);
        *(s32 *)(&D_800A5E90 + k) = *(s16 *)(param_1 + m + 8);
        func_80028620(j, (void *)(&D_800A5E88 + k));
        j++;
        m += 10;
    } while (j < 3);
}






