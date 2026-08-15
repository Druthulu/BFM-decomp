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
extern u8 D_8018D134;
extern u8 D_8018D0A4;
extern u8 D_8018D080;
extern u8 D_8018D05C;
extern u8 D_8018D110;
extern u8 D_8018D0EC;
extern u8 D_8018D0C8;
extern u8 D_8018D038;
extern void func_80145934(void);
extern u8 D_8018D1C4;
extern u8 D_8018D1A0;
extern u8 D_8018D17C;
extern u8 D_8018D158;
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
extern unsigned char D_8018C5BC[];
extern unsigned char D_8018C5EC[];
extern unsigned char D_8018C63C[];
extern unsigned char D_8018C66C[];
extern unsigned char D_8018C69C[];
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
extern void (*D_8018C6EC[])(void *);
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
extern s32 D_8018C7B4[];
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
extern u8 D_8018C83C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018C844;
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
extern int D_801E6E60;
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
extern s32 D_801E6E64;
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
extern s32 D_8018C874;
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
extern void (*D_8018C91C[])(void);
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
extern void (*D_8018C940[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018C930;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018C954[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018C960[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018C970[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018C988[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018C978;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018C99C[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018C9B8[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018C9A8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018C9CC[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018C9E0[])(void);
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
extern s32 D_8018C9F4;
extern void (*D_8018CA1C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018C9FC;
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
extern int (*D_8018CA68[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018CA6C[])(void);
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
extern s32 func_8014C568(s16 *a0, s16 *a1);
extern void func_801567BC(s32 a0);
extern B8 D_80128120[];
extern B8 D_80128138[];
extern S8 D_80126AF0[];
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern unsigned char D_8011520C[];
extern unsigned short D_8018CED0[];
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
extern void (*D_8018CEE0[])(void);
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
extern int D_801E6E98;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018CF08[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018CEE8;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018CEF8;
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
extern void (*D_8018CF48[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018CF50[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018CF1C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018CF5C[])(void);
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
extern u8 D_8018CF2C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801E6EA0;
extern s32 D_801E6EAC;
extern s32 D_801E6EB0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018CF98[])(s32 *);
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
extern s32 D_8018CF6C[];
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
extern s32 D_801E6EA8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018D1E8[])(void);
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
extern char D_8018D008[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018D28C[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018D3E0[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018D1FC;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018D3E8[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018D20C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018D22C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018D3F0[])(void);
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
extern s32 func_8015AE2C(void);
extern s32 func_8015BEC4(void);
extern s32 func_8015B950(s32 arg0);
extern s32 func_8015BEE4(void);
extern void func_8015BF04(s32 *a0);
extern void func_8015C0C4(s32 a0);
extern void func_8015BFF4(void *a0);
extern void func_8015BF7C(s32 *a0);
extern void func_8015C030(s32 *a0, s32 a1);
extern void func_8015BFB0(s32 *a0, s32 a1);
extern void (*D_8018D418[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018D424[])(void);
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
extern void (*D_8018D298[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018D4C8;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018C5AC[];
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
extern unsigned char D_8018D4DC[];
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
extern s8 D_8018D518[];
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
extern u16 D_8018D560;
extern u16 D_8018D562;
extern u16 D_8018D564;
extern s32 D_8018D568;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
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
extern int D_8018D27C;
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
extern unsigned int D_8018D5F4[];
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
extern void (*D_8018D6A4[])(void);
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
extern u16 D_8018D6D4[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018D738;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801E6EB8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018D75C[])(void);
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
extern int D_801E6F10[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018D7A4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018D794;
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
extern char D_801E63B4[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018D7AC[])(void);
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
extern void (*D_8018D800[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018D7C8;
extern s16 D_8018D7FC;
extern s16 D_8018D7FA;
extern s16 D_8018D7F8;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018D80C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E6F70;
extern u8 D_801E6F71;
extern u8 D_801E6F72;
extern u8 D_801E6F73;
extern u8 D_801E6F74;
extern u8 D_801E6F75;
extern u8 D_801E6F76;
extern u8 D_801E6F77;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018D81C[])(void);
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
extern s32 D_801E6FB0;
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
extern void (*D_8018D860[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018D8DC[];
extern s32 D_8018D8FC[];
extern u8 D_8018D978[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018D998[];
extern u8 D_8018D9B8[];
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
extern void (*D_8018DA54[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018DAD0[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801E63C4;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018DADC[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018DAE4[])(void);
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
extern void (*D_8018DBAC[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018DBBC[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018DBCC[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018DBD8[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018DB38[];
extern u8   D_8018DB4C[];
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
extern Blk20 D_800AE620;
extern s32  RotMatrixX(s32 a0, void *a1);
extern void func_80168664(void *arg0);
extern void (*D_8018DBF0[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018DBF8[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018DC00[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018DC08[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018DC10[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018DC18[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018DC20[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018DCD4[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018DCDC[])(void);
extern void func_80169F00(void *a0);
extern char D_8018DC8C[];
extern char D_8018DC4C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018DD14[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018DD20[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018DD68[])(void);
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
extern void (*D_8018DDE4[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E72D0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018DDD8[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018DE1C[];
extern unsigned short D_8018DE24[];
extern unsigned short D_8018DE2C[];
extern unsigned char D_801E72D8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E72D0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018DE34[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E740C;
extern M2C_UNK D_801E7410;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E7398;
extern void (*D_8018DE64[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E7414[];
extern u8 D_801E741C[];
extern u8 D_801E73CC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018DE6C[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018DE88[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018DE90[])(void);
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
extern void (*D_8018DEF8[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018DE9C;
extern u8 D_8018DEA8;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018DF2C[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018DF34[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018DF88[])(void);
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
extern u16 D_8018DFBC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018DFAC[];
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
extern s32 D_8018DFD8;
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
extern void (*D_8018E050[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018E058[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018E060[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018E068[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018E070[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018E078[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018E084[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018E090[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018E09C[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018E0AC[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018E0BC[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018E0C4[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018E0CC[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018E0D4[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018E0DC[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018E0E4[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018E0EC[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018E0F4[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018E0FC[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018E104[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018E10C[])(void);
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
extern void (*D_8018E114[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018E11C[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018E124[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018E12C[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018E134[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018E13C[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018E144[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018E14C[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018E154[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018E15C[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018E164[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018E16C[])(void);
extern void func_801714E4(void *a0);
extern struct B16 D_800A5E88;
extern struct B16 D_800A5EA8;
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
extern void (*D_8018E1B0[])(void);
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
extern M2C_UNK D_8018E174;
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
extern struct S80126B38 D_80126B38;
extern s16 D_80126B3E;
extern void func_80173460(s32 a0, s32 a1);
extern void func_801734BC(s32 arg0, s32 _unused1);
extern void (*D_8018E1E0[])(void);
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
extern void (*D_8018E21C[])(void);
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
extern void (*D_8018E274[])();
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
extern void (*D_8018E284[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018E28C[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018E3F4[])();
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
extern void (*D_8018E400[])();
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
extern M2C_UNK D_801E660C;
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
extern s16 D_801E87BC;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801E7B50;
extern short D_801E8864;
extern void func_80178CBC(s32 arg0, s32 arg1);
extern void func_80178D18(void);
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
extern s32 D_801E7F7C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E7FA4;
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
extern s16 D_801E7F60;
extern s32 func_8017A3B0(void);
extern short D_801E7F9C;
extern short D_801E7F98;
extern int func_800D0CA0(int);
extern int func_8001AAA0(void);
extern int func_800D0CE0(void);
extern int func_8017A3D8(void);
extern s32 func_8017AD0C(s32 arg0);
extern s32 func_8017AD0C(s32);
extern s32 func_8017ADE8(s32 a0);
extern s32 func_8017AE08(void);
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801E7F64;
extern u16 D_801E7FE4;
extern u16 D_801E7FE6;
extern u16 D_801E7FE8;
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
extern s16 D_801E7FDC;
extern s16 D_801E7FDE;
extern s16 D_801E7FE0;
extern s16 D_801E7FD4;
extern s16 D_801E7FD6;
extern s16 D_801E7FD8;
extern void func_8017B7A8(void);
extern s16 D_801E7FF4;
extern s16 D_801E7FF6;
extern s16 D_801E7FF8;
extern s16 D_801E7FFC;
extern s16 D_801E7FFE;
extern s16 D_801E8000;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801E7FEC;
extern short D_801E7FEE;
extern short D_801E7FF0;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801E7FAC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801E7FA8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018E5DC[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8018E614[])(void);
extern void func_8017BEF8(void *a0);
extern void (*D_8018E628[])(void);
extern void func_8017C524(void *a0);
extern void (*D_8018E63C[])(void);
extern void func_8017C7C4(void *a0);
extern void (*D_8018E65C[])(void);
extern void func_8017CA80(void *a0);
extern void (*D_8018E664[])(void);
extern void func_8017CD14(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern u8 D_8018E650;
extern void func_8017CD50(s32 a0);
extern s32 func_8017E404(s32 a0, s32 a1);
extern s32 func_8012AE00(s32 a0);
extern void func_8017E51C(s32 a0);
extern s16 D_8018E6CC;
extern s16 D_8018E6D0;
extern s32 func_80013478(s32 a0, s32 a1);
extern s32 ratan2(s32, s32);
extern s32 func_8017E958(s32 param_1, s32 param_2);
extern void func_8012A828(s32 a0, void *a1);
extern char D_801A668C[];
extern void func_8017F5A0(int param_1);
extern s32 D_801A72C4;
extern void func_8017F5E4(s32 param_1);
extern void func_8017FC9C(void *a0);
extern s32 D_801270CC;
extern void func_8012C098(void);
extern void func_8012C218(void *a0);
extern void func_8017FCB0(void *a0);
extern void func_8017FD2C(u8 *a0);
extern void func_8017FD44(void *a0);
extern void func_8012A828(int, void *);
extern void func_8012B2CC(int);
extern void func_8012B23C(int);
extern void func_8012B14C(s32 a0, s32 a1);
extern unsigned char D_801A6F44;
extern unsigned char D_8018E6EC;
extern void func_8017FD80(int param_1);
extern void func_8012B23C(s32 a0);
extern unsigned char D_8018E6F8;
extern void func_8017FDE8(int param_1);
extern unsigned char D_8018E704;
extern void func_8017FE68(int param_1);
extern void func_8012DBD0(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012CC64(s32 a0, void *a1);
extern void func_8012CBF4(s32);
extern s32 func_8012CBA4(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_80180A18(s32 a0);
extern void func_80180878(short*);
extern void func_80180394(void*);
extern void func_8017FF18(int param_1);
extern unsigned char D_801A6E7C[];
extern void func_80143CD4(s32 a0);
extern int func_800CB0E8(int param);
extern void func_801801EC(int param_1);
extern void func_80180394(void *a0);
extern void func_801803D0(void);
extern void func_801803B0(void);
extern unsigned char D_801A73BC[];
extern void func_80180428(int param_1);
extern int D_801A6C5C;
extern void func_80180878(short *param_1);
extern s32 func_8012BEE8(s32);
extern void func_8012B2CC(s32);
extern void func_8012B23C(s32);
extern u8 D_801A629C;
extern unsigned char D_8018E68C[];
extern unsigned char D_801A648C[];
extern void func_801808C4(s32 param_1);
extern void func_80130740(void *a0, u16 *a1);
extern unsigned char D_8018E78C[];
extern void func_80180A18(int param);
extern void func_8012A828(s32, void *);
extern void func_8002D4C8(s32, s32);
extern void func_80180A64(s32 param_1);
extern void func_8012E364(void);
extern void func_80181498(void);
extern s32 func_8012E470(s32 a0);
extern s32 func_8012E4C8(void *a0);
extern void func_801814B8(int param_1);
extern s32 func_8012BEE8(s32 a0);
extern void func_801814F0(int param_1);
/* ==== end §8b carried decl layer ==== */


// @class: struct
// @stuck: none — MATCH (clean switch + jtbl; orchestrator owns jtbl/rodata migration)

extern void func_80130D48(s32 a0);
extern void func_8012C098(void);
extern void func_8012C218(void *a0);
extern s32 D_801270CC;

void func_8018173C(int param_1) {
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x1c) + 1;
    *(int *)(param_1 + 0x1c) = iVar1;
    if (iVar1 >= 0x3d) {
        ((void (*)(void))func_80130D48)();
        switch ((int)((unsigned int)*(unsigned short *)(param_1 + 0x70) << 0x10) >> 0x18) {
        case 0:
        case 1:
        case 2:
        case 5:
        case 6:
            ((void (*)(int))func_8012C098)(param_1);
            break;
        case 3:
        case 7:
            ((void (*)(int))func_8012C218)(param_1);
            break;
        case 4:
            D_801270CC = D_801270CC + -1;
            ((void (*)(int))func_8012C218)(param_1);
        }
    } else if (0x1e < iVar1) {
        *(unsigned int *)(*(int *)(param_1 + 0x20) + 4) =
            *(unsigned int *)(*(int *)(param_1 + 0x20) + 4) ^ 0x80000000;
    }
    return;
}

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80181820);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801818C0);

DEFINE_func_80181914()  /* dedup: shared engine-core @0x80181914 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80181934);

DEFINE_func_801819F4()  /* dedup: shared engine-core @0x801819F4 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80181A94);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80181AD4);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80181B4C);

DEFINE_func_80181C10()  /* dedup: shared engine-core @0x80181C10 (src/shared) */

DEFINE_func_80181CE0()  /* dedup: shared engine-core @0x80181CE0 (src/shared) */

extern s16 D_80126968;
    extern s16 D_80126978;
    void func_80181D0C(void) {
        D_80126968 = 0x200;
        D_80126978 = -0x1C0;
    }


DEFINE_func_80181D2C()  /* dedup: shared engine-core @0x80181D2C (src/shared) */


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80181D68);

DEFINE_func_80181DE0()  /* dedup: shared engine-core @0x80181DE0 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80181DE8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80181E70);


extern s32 func_80013200(s32 *a0, s32 *a1);
extern s32 ratan2(s32 a0, s32 a1);

void func_80182058(s32 param_1) {

    extern s16 D_800B9AB8[];
    extern s16 D_800B9ABA[];
    s32 v1[3];
    s32 v2[3];
    s32 dist;
    s32 angle;
    s32 v0;

    v1[0] = *(s32 *)(param_1 + 0x48);
    v1[1] = 0;
    v1[2] = *(s32 *)(param_1 + 0x50);
    v2[0] = *(s32 *)(param_1 + 0x3C);
    v2[1] = 0;
    v2[2] = *(s32 *)(param_1 + 0x44);
    dist = func_80013200(v1, v2);
    angle = ratan2(*(s32 *)(param_1 + 0x4C) - *(s32 *)(param_1 + 0x40), dist);
    if (angle >= 0x801) {
        angle = 0x1000 - angle;
    }
    v0 = angle * 360 / 1024 + 0xA0;
    D_800B9ABA[0] = (s16)v0;

    angle = ratan2(v1[0] - v2[0], v1[2] - v2[2]);
    v0 = angle * 640 / 4096 + 0x50;
    D_800B9AB8[0] = (s16)v0;
}



extern void (*D_8018EAC4[])(void);

void func_80182154(void *a0) {
    D_8018EAC4[*(u8 *)((s32)a0 + 0x15)]();
}


DEFINE_func_80182190()  /* dedup: shared engine-core @0x80182190 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801821E8);


extern void (*D_8018EACC[])(void);

void func_80182234(void *a0) {
    D_8018EACC[*(u8 *)((s32)a0 + 0x15)]();
}



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801826C4(void *arg0);

s32 func_80182270(s32 param_1) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801826C4, 0x1000000);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 10;
    return 0;
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801822BC);

DEFINE_func_80182338()  /* dedup: shared engine-core @0x80182338 (src/shared) */

DEFINE_func_8018235C()  /* dedup: shared engine-core @0x8018235C (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182398);

DEFINE_func_801823F0()  /* dedup: shared engine-core @0x801823F0 (src/shared) */


extern void (*D_8018EAE0[])(void);

void func_80182414(void *a0) {
    D_8018EAE0[*(u8 *)((s32)a0 + 0x15)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182450);

DEFINE_func_801824A8()  /* dedup: shared engine-core @0x801824A8 (src/shared) */


extern s32 D_801E8770;

void func_801824CC(void) {
    D_801E8770 = 1;
}



extern void (*D_8018ED20[])(void);

void func_801824E0(void *a0) {
    D_8018ED20[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018251C);

DEFINE_func_8018258C()  /* dedup: shared engine-core @0x8018258C (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182594);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801825E0);

DEFINE_func_80182630()  /* dedup: shared engine-core @0x80182630 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (param_1 survives across func_8016F0E4 → lands in $s0; passed to func_80165770)

extern void func_8016F0E4(void);
extern void func_80165770(void);
extern void func_80175414(s32 _arg0);

void func_8018268C(s32 param_1)
{
    func_8016F0E4();
    ((void (*)(s32))func_80165770)(param_1);
    ((void (*)(void))func_80175414)();
}



extern void (*D_8018ED38[])(void);

void func_801826C4(void *a0) {
    D_8018ED38[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182700);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182744);

extern void func_8016F0E4(void);
    void func_801827A0(void) {
        ((s32 (*)(void))func_8016F0E4)();
    }


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801827C0);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182854);

DEFINE_func_80182894()  /* dedup: shared engine-core @0x80182894 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182964);

DEFINE_func_801829F8()  /* dedup: shared engine-core @0x801829F8 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182AE4);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182B74);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182BD0);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182CB4);

DEFINE_func_80182D00()  /* dedup: shared engine-core @0x80182D00 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182D3C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182D84);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182E08);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182E84);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182EEC);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182F4C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80182F78);

DEFINE_func_80183010()  /* dedup: shared engine-core @0x80183010 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183018);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183098);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018316C);

DEFINE_func_801831A8()  /* dedup: shared engine-core @0x801831A8 (src/shared) */


extern u8 D_80126D6C;
    void func_801831E4(void) {
        D_80126D6C = 0x8;
    }


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801831F8);


extern void (*D_8018EDA0[])(void);

void func_80183238(void *a0) {
    D_8018EDA0[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183274);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183310);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801834EC);


void func_80183574(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x204) - 1;
    M2C_FIELD(arg0, s32 *, 0x204) = temp_v0;
    if (temp_v0 == -1) {
        func_80185F24();
        M2C_FIELD(arg0, s32 *, 0x204) = 0x30;
        M2C_FIELD(arg0, u8 *, 0x214) = (u8) (M2C_FIELD(arg0, u8 *, 0x214) + 1);
    }
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801835C8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801835F8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018366C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801836C8);


extern void (*D_8018EDC0[])(void);

void func_80183718(void *a0) {
    D_8018EDC0[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183754);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183814);


void func_801839C4(void *a0) {
    s32 bVar1;

    *(u32 *)((s32)a0 + 0x1F8) = *(u32 *)((s32)a0 + 0x1F8) & 0xFEFFFFFF;
    *(u16 *)((s32)a0 + 0xAA) = *(u16 *)((s32)a0 + 0xAA) & 0xFF40;
    bVar1 = *(u8 *)((s32)a0 + 0xA9);
    *(u16 *)((s32)a0 + 0xAC) = *(u16 *)((s32)a0 + 0xAC) & 0xFF40;

    __asm__ __volatile__("" ::: "memory");

    switch (bVar1) {
    case 0x41:
        *(u16 *)((s32)a0 + 0xAA) = *(u16 *)((s32)a0 + 0xAA) & 0xAFFF;
        *(u16 *)((s32)a0 + 0xAC) = *(u16 *)((s32)a0 + 0xAC) & 0xAFFF;
        *(u16 *)((s32)a0 + 0xAA) = *(u16 *)((s32)a0 + 0xAA) | 0x4000;
        *(u16 *)((s32)a0 + 0xAC) = *(u16 *)((s32)a0 + 0xAC) | 0x4000;
        break;
    case 0x53:
    case 0x73:
        *(u16 *)((s32)a0 + 0xAE) = *(u8 *)((s32)a0 + 0xAE) | 0xFF00;
        break;
    }
}


DEFINE_func_80183A78()  /* dedup: shared engine-core @0x80183A78 (src/shared) */

DEFINE_func_80183A80()  /* dedup: shared engine-core @0x80183A80 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183B64);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183BA4);

DEFINE_func_80183C94()  /* dedup: shared engine-core @0x80183C94 (src/shared) */

extern s32 func_8013767C(s32 a0);
extern void func_80147324(s32 a0);
void func_80183C9C(s32 a0) {

    extern s16 D_8018EDD8[];
    extern u8 D_801A7CB0;
    s16 v;
    s16 d;
    v = D_8018EDD8[*(u8 *)(a0 + 0x20C)];
    if (v != 0) {
        d = v - *(u16 *)(a0 + 0xE);
        v = d;
        if (d < 0) {
            v = -d;
        }
        if (v < 0x180) {
            *(s32 *)(a0 + 0x198) = func_8013767C((s32)&D_801A7CB0);
            switch (*(u8 *)(a0 + 0x20C)) {
            case 0:
                func_80147324(0x5A1);
                break;
            case 1:
                func_80147324(0x5F1);
                break;
            case 2:
                func_80147324(0x5F2);
                break;
            }
            *(u8 *)(a0 + 0x20C) += 1;
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183D80);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183DD8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183EB8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183F0C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183F64);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80183FC8);

DEFINE_func_80184164()  /* dedup: shared engine-core @0x80184164 (src/shared) */

DEFINE_func_80184174()  /* dedup: shared engine-core @0x80184174 (src/shared) */

DEFINE_func_8018419C()  /* dedup: shared engine-core @0x8018419C (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80184250);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80184358);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018453C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801847B8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018483C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80184A08);

DEFINE_func_80184B00()  /* dedup: shared engine-core @0x80184B00 (src/shared) */

DEFINE_func_80184B14()  /* dedup: shared engine-core @0x80184B14 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80184BD8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018512C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801852E4);

DEFINE_func_8018535C()  /* dedup: shared engine-core @0x8018535C (src/shared) */

DEFINE_func_80185364()  /* dedup: shared engine-core @0x80185364 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018537C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801853D4);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018545C);

DEFINE_func_801854C4()  /* dedup: shared engine-core @0x801854C4 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801854CC);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801855D4);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801857B0);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185840);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185910);


extern void (*D_8018F2E0[])(void);

void func_80185B40(void *a0) {
    D_8018F2E0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185B7C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185BF0);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185C48);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185D58);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185E00);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185E88);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185EC8);

DEFINE_func_80185F24()  /* dedup: shared engine-core @0x80185F24 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185F58);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80185F8C);


extern void (*D_8018F2E8[])(void);

void func_801860A8(void *a0) {
    D_8018F2E8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801860E4);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018618C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801861D8);

DEFINE_func_8018621C()  /* dedup: shared engine-core @0x8018621C (src/shared) */

DEFINE_func_8018623C()  /* dedup: shared engine-core @0x8018623C (src/shared) */


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018626C);


extern void (*D_8018F2F4[])(void);

void func_801863AC(void *a0) {
    D_8018F2F4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_801863E8()  /* dedup: shared engine-core @0x801863E8 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80186424);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80186530);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80186764);

DEFINE_func_801868D4()  /* dedup: shared engine-core @0x801868D4 (src/shared) */



extern void (*D_8018F394[])(void);

void func_80186910(void *a0) {
    D_8018F394[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018694C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801869CC);

extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80186A64(void *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 0x96;
        *(s16 *)((s32)a0 + 0x2) += 1;
        func_8002D4C8(0x402, 0);
    }


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80186A9C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80186AE4);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80186C44);


extern void (*D_8018F3AC[])(void);

void func_80186CAC(void *a0) {
    D_8018F3AC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80186CE8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80186D88);


extern void (*D_8018F3C4[])(void);

void func_80186E30(void *a0) {
    D_8018F3C4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80186E6C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80186F44);

DEFINE_func_80186FDC()  /* dedup: shared engine-core @0x80186FDC (src/shared) */

DEFINE_func_80187060()  /* dedup: shared engine-core @0x80187060 (src/shared) */


extern void (*D_8018F3D4[])(void);

void func_801870DC(void *a0) {
    D_8018F3D4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80187118);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801871B8);

extern void func_8012CBCC(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
s32 func_80187254(s32 param_1) {
    s32 p;
    p = *(s32 *)(param_1 + 0x20);
    *(s16 *)(p + 0x12) = *(u16 *)(p + 0x12) + 0x100;
    if (((s32 (*)(void))func_8012CBCC)() != 0) {
        *(s32 *)(param_1 + 0x18) = 0xFFE80000;
        *(s32 *)(param_1 + 0x14) = 0xFFC80000;
        *(s32 *)(param_1 + 0x44) = 0;
        *(s32 *)(param_1 + 0x48) = 0x80000;
        *(s32 *)(param_1 + 0x4C) = 0;
        func_80143B6C(param_1, 0);
        *(s16 *)(param_1 + 0xFC) = 0x40;
        *(s16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
    }
}


extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
void func_801872D8(int param_1) {
    short v;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 0x100;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 0x20;
    v = *(unsigned short *)(param_1 + 0xFC) - 1;
    *(short *)(param_1 + 0xFC) = v;
    if (v == 0) {
        ((void (*)(void))func_8012C218)();
    } else {
        ((void (*)(void))func_8012AD80)();
    }
}


DEFINE_func_80187354()  /* dedup: shared engine-core @0x80187354 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80187480);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80187558);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018762C);


extern void (*D_8018F460[])(void);

void func_801876FC(void *a0) {
    D_8018F460[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80187738);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80187834);

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
void func_801878D0(int param_1) {
    short v;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 0x100;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 0x20;
    v = *(unsigned short *)(param_1 + 0xFC) - 1;
    *(short *)(param_1 + 0xFC) = v;
    if (v == 0) {
        ((void (*)(void))func_8012C218)();
    } else {
        ((void (*)(void))func_8012AD80)();
    }
}



extern void (*D_8018F46C[])(void);

void func_8018794C(void *a0) {
    D_8018F46C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80187988);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80187B40);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80187DB8);

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
void func_80187EB4(int param_1) {
    short v;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 0x100;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 0x20;
    v = *(unsigned short *)(param_1 + 0xFC) - 1;
    *(short *)(param_1 + 0xFC) = v;
    if (v == 0) {
        ((void (*)(void))func_8012C218)();
    } else {
        ((void (*)(void))func_8012AD80)();
    }
}


DEFINE_func_80187F30()  /* dedup: shared engine-core @0x80187F30 (src/shared) */


extern void (*D_8018F540[])(void);

void func_80187FEC(void *a0) {
    D_8018F540[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80188028);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80188134);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018825C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80188414);


extern void func_8012C218(void*);
    s32 func_80188484(s32 arg0) {
        *(s32 *)(arg0 + 0xdc) -= 1;
        if (*(s32 *)(arg0 + 0xdc) == 0) {
            ((void (*)(void))func_8012C218)();
        }
    }


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801884B8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801884FC);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80188680);


extern void (*D_8018F558[])(void);

void func_801886DC(void *a0) {
    D_8018F558[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_8018F590[])(void);

void func_80188718(void *a0) {
    D_8018F590[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_8018F598[])(void);

void func_80188754(void *a0) {
    D_8018F598[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80188790);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_801888CC(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x10;
        ((void (*)(s32, s32))func_8012AD44)((s32)a0, 0x1);
    }


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801888F4);



s32 func_80188A18(s32 param_1)
{
    extern void func_8012931C(struct vec *a0);
    extern void func_801292C8(u8 *a0);

    register unsigned short c __asm__("$5");
    register int d __asm__("$4");
    register int g __asm__("$6");
    int a;
    int e;
    ((void (*)(int))func_8012931C)(((int)param_1));
    a = *(int *)(((int)param_1) + 0x10);
    c = *(unsigned short *)(((int)param_1) + 0x34);
    e = *(int *)(((int)param_1) + 0x2c);
    __asm__ __volatile__("" : : "r"(a));
    d = *(int *)(((int)param_1) + 0x30);
    {
        unsigned short cp1 = c + 1;
        *(int *)(((int)param_1) + 0x10) = a + e;
        *(unsigned short *)(((int)param_1) + 0x34) = cp1;
    }
    *(int *)(((int)param_1) + 8) = *(int *)(((int)param_1) + 8) + 0x10000;
    *(int *)(((int)param_1) + 0x18) = *(int *)(((int)param_1) + 0x18) + d;
    g = *(short *)(((int)param_1) + 0xa);
    if (g > *(short *)(((int)param_1) + 0x36)) {
        ((void (*)(int))func_801292C8)(((int)param_1));
    } else if (*(short *)(((int)param_1) + 0x34) == 8) {
        *(int *)(((int)param_1) + 0x2c) = -*(int *)(((int)param_1) + 0x2c);
        *(int *)(((int)param_1) + 0x30) = -*(int *)(((int)param_1) + 0x30);
        *(int *)(((int)param_1) + 0x14) = -*(int *)(((int)param_1) + 0x14);
    } else if (*(short *)(((int)param_1) + 0x34) == 0x10) {
        *(short *)(((int)param_1) + 0x34) = 0;
        *(int *)(((int)param_1) + 0x14) = -*(int *)(((int)param_1) + 0x14);
    }
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80188AEC);

extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);

void func_80188BAC(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + 0x200;
    func_8012931C((struct vec *)a0);
    if (*(s16 *)(a0 + 0xA) > *(s16 *)(a0 + 0x36)) {
        func_801292C8(a0);
    }
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80188C0C);


extern void (*D_8018F5A0[])(void);

void func_80188C9C(void *a0) {
    D_8018F5A0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(u8*);
void func_80188CD8(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(a0);
    }
}



extern void (*D_8018F5BC[])(void);

void func_80188D18(void *a0) {
    D_8018F5BC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80188D54);

DEFINE_func_80188DF0()  /* dedup: shared engine-core @0x80188DF0 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80188DF8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80188E80);


extern void (*D_8018F6C4[])(void);

void func_80188ECC(void *a0) {
    D_8018F6C4[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_80188F08()  /* dedup: shared engine-core @0x80188F08 (src/shared) */

















void func_80188F30(void *arg0)
{
  *((s16 *) (((char *) arg0) + 0x2)) = 1;
  *((s32 *) (((char *) arg0) + 0x1c)) = 1;
  *((s16 *) (((char *) arg0) + 0xa8)) = 0x7f;
  *((s16 *) (((char *) arg0) + 0x84)) = 1;
  *((s32 *) (((char *) arg0) + 0xa4)) = 0;
  *((unsigned short *) (((char *) arg0) + 0x72)) |= 0x1000;
}

extern void func_80028620(s32, void *);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_800CF8B4();
extern s32 func_8012B8A4(s16 *a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_80189340(s32 p);

void func_80188F60(s32 self)
{

    extern s16 D_800B9A0E;
    extern s32 D_80126B58;
    extern s32 D_801270C8;
    extern s32 D_801270D4;
    extern u8 D_8018F6CC[];
    extern struct B16 D_800A5E98;   /* AGREES with the TU's file-scope decl (line 2167) */
    extern s32 D_800A5E9C;
    extern u8 D_800A5EA4;
    extern u8 D_800A5EA5;
    extern u8 D_800A5EA6;
    u8 *dst = (u8 *)(self + 0x103);
    u8 *src = D_8018F6CC;
    s16 *tp = (s16 *)&D_80126B58;
    s32 *rec;
    s32 i;
    s32 t;

    if (func_8012BEE8(self) != 0) {
        i = 0;
        *(s32 *)(self + 0x1C) = (rand() & 1) + 1;
        do {
            if (*src != 0) {
                *dst = rand() % *src;
            } else {
                *dst = 0;
            }
            dst--;
            i++;
            src++;
        } while (i < 0x18);
    }
    if (*(s16 *)(self + 0x70) != 0) {
        rec = (s32 *)&D_800A5E98;
        *rec = -0x12;
        D_800A5E9C = rand() % 31 + 10;
        D_800A5EA4 = *(u16 *)(self + 0xA8);
        D_800A5EA5 = *(s16 *)(self + 0xA8) * 5 / 127;
        D_800A5EA6 = *(s16 *)(self + 0xA8) * 51 / 127;
        func_80028620(1, rec);
    }
    t = (s16)*(u16 *)(self + 0xA8) >> 1;
    *(s16 *)(self + 0xA8) = t;
    if (D_801270C8 != 1) {
        *(s16 *)(self + 0xA8) = t | 0x40;
        if (*(s16 *)(self + 0x70) == 0) {
            goto tail;
        }
        *(u16 *)(self + 0x84) -= 1;
        if (*(s16 *)(self + 0x84) == 0) {
            i = (func_8012B8A4(self) - 0x400) & 0xFFF;
            if (i >= 0x800) {
                i = 0xFFF - i;
            }
            i >>= 5;
            i += 0x10;
            if (tp[3] > 0x380) {
                i += (tp[3] - 0x380) * 80 / 120;
            }
            if (i >= 0x80) {
                i = 0x7F;
            }
            *(s16 *)(self + 0x84) = 0xF;
            if (func_800CF8B4() != 0) {
                func_8002D4C8(0x4CF, (u16)(i | 0x1000));
            } else {
                func_8002D4C8(4, 0x4CF);
            }
            *(s32 *)(self + 0xA4) = 1;
        }
    } else {
        if (*(s16 *)(self + 0x70) != 0 && *(s32 *)(self + 0xA4) != 0) {
            func_8002D4C8(4, 0x4CF);
            *(s16 *)(self + 0x84) = 1;
            *(s32 *)(self + 0xA4) = 0;
        }
        if (D_801270D4 == 1) {
            s32 *rec2 = &D_800A5E9C;
            func_8012C218((void *)self);
            *rec2 = 0x18;
            D_800A5EA4 = 0x7F;
            D_800A5EA5 = 0x66;
            D_800A5EA6 = 0x7F;
            func_80028620(1, rec2 - 1);
            return;
        }
    }
    if (*(s16 *)(self + 0x70) != 0 && *(s32 *)(self + 0xA4) != 0 && D_800B9A0E != 0) {
        func_8002D4C8(4, 0x4CF);
        *(s32 *)(self + 0xA4) = 0;
    }
tail:
    func_80189340(self);
}



extern void (*D_8018F714[])(void);

void func_80189304(void *a0) {
    D_8018F714[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_80189340 -- ov_SC02_000 (jr_8018173C).  Projects a 8-node "tail"/streamer chain
 * (D_8018F6E4 = a u16[3] offset table, one row per node; the per-node byte deltas live in
 * the object at +0x100 walking DOWNWARD) and, for every node whose bit is set in the
 * s16 mask at obj+0xA8, emits 4 semi-transparent gouraud quads (POLY_G4, len=8, code=0x3A)
 * that fan the previous->current screen segment out by +-radius in x (j=0,1) or y (j=2,3).
 *
 * Byte-verified levers (match_one MATCH, 260 ins):
 *  L1 FRAME (sp+0xE8, out-arg area 0x18 for func_8005A600's 5th arg).  Declared-local slots
 *     are handed out in DECLARATION order; everything at/above sp+0xA0 is a reload SPILL
 *     slot (8-aligned, size rounded to 8 -- assign_stack_local(align == -1)), which is why
 *     prim/ot/mask/ptrC land on 0xA0/0xA8/0xB0/0xB8 with holes between.  So the declared set
 *     must be exactly: tags[28] (0x18), sv[4] (0x88), xy[4] (0x90), rgb (0x98), flag (0x9C).
 *     `rgb` and `flag` MUST be plain address-taken scalars (4-aligned, no hole); folding them
 *     into the xy aggregate would 8-align them and shift the frame.
 *  L2 tags[1..27] are genuinely DEAD stores in the original -- keep them.  The loop body must
 *     read `tags[0]` (not the `prim` pseudo): tags[] is an ARRAY_REF, so the store tags[i]=
 *     invalidates it every iteration and re-emits `lw $v0,0x18($sp)`.
 *  L3 ONE variable for BOTH the tags counter and the outer node counter.  Two separate
 *     counters split the allocno; the merged one out-ranks the ptrC giv, takes $s4, and
 *     pushes ptrC into the 0xB8 spill -- which is also what forces the target's TWO separate
 *     `la D_8018F6E4` materialisations in the preheader (257 -> 260 ins).
 *  L4 `ret * 4` is written TWICE (ot, and the divisor).  Binding it to a local computes it
 *     once and loses a `sll`; CSE cannot merge the two because a loop back-edge separates
 *     their extended basic blocks.
 *  L5 The 14 prim stores go through STRUCT types (MEM_IN_STRUCT_P).  cse.c's true_dependence
 *     drops the dependence of a varying in-struct store on a fixed NON-struct scalar, so the
 *     plain scalar `rgb` survives across them (one `lw 0x98($sp)` feeding both colour stores)
 *     while the ARRAY_REF xy[] reads do NOT (each `sh` gets its own `lhu`).  Plain
 *     `*(s32 *)(pp + 0x04)` casts would re-load rgb twice and lose the match.
 *  L6 `s32 c = rgb;` -- a block-scoped temp read at the TOP of the j body.  It is what hoists
 *     `lw $v1,0x98($sp)` above `addiu $v0,$zero,8` and hands rgb $v1 (not $v0), which in turn
 *     lets the 0x3A constant float up.  Reading `rgb` directly at the two colour stores is an
 *     8-instruction schedule miss; it must NOT be hoisted out of the j loop (AddPrim clobbers
 *     memory, so loop.c cannot treat the load as invariant).
 *  L7 `xy[0]=xy[2]; xy[1]=xy[3];` sit AFTER the three sv[] stores (any earlier placement is
 *     12-50 off), and `q` is a single walking `*q--` cursor seeded at obj+0x103 -- gcc folds
 *     the three peeled decrements into the one `addiu $s3,$s6,0x100`.
 *
 * Integration surface (host TU src/ov_SC02_000/ov_SC02_000_jr_8018173C.c):
 *   AGREES at file scope -- D_800AF648 (u8[]), D_80126950 (s32), D_800B9A02 (s16, matched to
 *   the TU canon; the u16 spelling also byte-matches but would CONFLICT), func_8004914C /
 *   func_800491AC (void(void*)).  NOT declared anywhere in the TU or in include/ --
 *   D_8018F6E4, D_800A651C, RotTransPers, func_80010A08, GetTPage, func_8005A600, AddPrim.
 *   D_8018F6E4 is overlay-local data: the ~2 family sibling needs its own symbol remapped.
 */


extern void  func_8004914C(void *a0);
extern void  func_800491AC(void *a0);
extern s32   RotTransPers(void *a0, void *a1, s32 *a2, s32 *a3);
extern void *func_80010A08(s32 a0);
extern s32   GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32   func_8005A600(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern s32   AddPrim(s32 a0, void *a1);

void func_80189340(s32 p)
{

    extern u8  D_800AF648[];
    extern u16 D_8018F6E4[];
    extern s32 D_80126950;
    extern s32 D_800A651C;
    typedef struct { u8 pad0[3]; u8 len; u8 pad1[3]; u8 code; } PHdr_80189340_80189340;
    typedef struct {
        u32 tag;            /* 0x00 */
        u32 c0;             /* 0x04 */
        u16 x0, y0;         /* 0x08, 0x0A */
        u32 c1;             /* 0x0C */
        u16 x1, y1;         /* 0x10, 0x12 */
        u32 c2;             /* 0x14 */
        u16 x2, y2;         /* 0x18, 0x1A */
        u32 c3;             /* 0x1C */
        u16 x3, y3;         /* 0x20, 0x22 */
    } PG4_80189340_80189340;         /* 0x24 */

    s32 tags[28];           /* sp+0x18 */
    s16 sv[4];              /* sp+0x88 */
    u16 xy[4];              /* sp+0x90 */
    s32 rgb;                /* sp+0x98 */
    s32 flag;               /* sp+0x9C */

    u8 *q;
    u8 *pp;
    u8 *prim;
    s32 ret;
    s32 ot;
    s32 radius;
    s32 tp;
    s32 i, j;
    u8  mask;

    func_8004914C(D_800AF648);
    func_800491AC(D_800AF648);

    mask = 1;
    q = (u8 *)(p + 0x103);
    sv[0] = D_8018F6E4[0] + *q--;
    sv[1] = D_8018F6E4[1] + *q--;
    sv[2] = D_8018F6E4[2] + *q--;
    ret = RotTransPers(sv, &xy[2], &rgb, &flag);
    if (ret > 0 && flag >= 0) {
        ot = *(s32 *)((s8 *)&D_800A651C + ((u16)D_800B9A02 * 0x14)) + ret * 4;
        prim = (u8 *)func_80010A08(0x3FC);
        if (prim != 0) {
            tp = GetTPage(0, 1, 0, 0);
            func_8005A600((s32)prim, 0, 0, (u16)tp, 0);

            tags[0] = (s32)(prim + 0xC);
            for (i = 1; i < 28; i++) {
                tags[i] = tags[0] + i * 0x24;
            }

            radius = ((D_80126950 + 0x1F4) * 8) / (ret * 4);
            pp = (u8 *)tags[0];

            for (i = 1; i < 8; i++) {
                sv[0] = D_8018F6E4[i * 3] + *q--;
                sv[1] = D_8018F6E4[i * 3 + 1] + *q--;
                sv[2] = D_8018F6E4[i * 3 + 2] + *q--;
                xy[0] = xy[2];
                xy[1] = xy[3];
                RotTransPers(sv, &xy[2], &rgb, &flag);
                if ((*(s16 *)(p + 0xA8) & mask) != 0) {
                    rgb = *(s32 *)(p + 0x1C) << 6;
                    for (j = 0; j < 4; j++) {
                        s32 c = rgb;
                        ((PHdr_80189340_80189340 *)pp)->len = 8;
                        ((PG4_80189340_80189340 *)pp)->c1 = 0;
                        ((PG4_80189340_80189340 *)pp)->c3 = 0;
                        ((PG4_80189340_80189340 *)pp)->c0 = c;
                        ((PG4_80189340_80189340 *)pp)->c2 = c;
                        ((PHdr_80189340_80189340 *)pp)->code = 0x3A;
                        ((PG4_80189340_80189340 *)pp)->x0 = xy[0];
                        ((PG4_80189340_80189340 *)pp)->x1 = xy[0];
                        ((PG4_80189340_80189340 *)pp)->x2 = xy[2];
                        ((PG4_80189340_80189340 *)pp)->x3 = xy[2];
                        ((PG4_80189340_80189340 *)pp)->y0 = xy[1];
                        ((PG4_80189340_80189340 *)pp)->y1 = xy[1];
                        ((PG4_80189340_80189340 *)pp)->y2 = xy[3];
                        ((PG4_80189340_80189340 *)pp)->y3 = xy[3];
                        switch (j) {
                        case 0:
                            ((PG4_80189340_80189340 *)pp)->x1 = ((PG4_80189340_80189340 *)pp)->x1 + radius;
                            ((PG4_80189340_80189340 *)pp)->x3 = ((PG4_80189340_80189340 *)pp)->x3 + radius;
                            break;
                        case 1:
                            ((PG4_80189340_80189340 *)pp)->x1 = ((PG4_80189340_80189340 *)pp)->x1 - radius;
                            ((PG4_80189340_80189340 *)pp)->x3 = ((PG4_80189340_80189340 *)pp)->x3 - radius;
                            break;
                        case 2:
                            ((PG4_80189340_80189340 *)pp)->y1 = ((PG4_80189340_80189340 *)pp)->y1 + radius;
                            ((PG4_80189340_80189340 *)pp)->y3 = ((PG4_80189340_80189340 *)pp)->y3 + radius;
                            break;
                        case 3:
                            ((PG4_80189340_80189340 *)pp)->y1 = ((PG4_80189340_80189340 *)pp)->y1 - radius;
                            ((PG4_80189340_80189340 *)pp)->y3 = ((PG4_80189340_80189340 *)pp)->y3 - radius;
                            break;
                        }
                        AddPrim(ot, pp);
                        pp += 0x24;
                    }
                }
                mask = mask << 1;
            }
            AddPrim(ot, prim);
        }
    }
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80189750);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_801897E8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80189858);

extern s16 D_800B9A0E;
    s32 func_80189888(void) {
        return *(s16 *)&D_800B9A0E;
    }


DEFINE_func_80189898()  /* dedup: shared engine-core @0x80189898 (src/shared) */


DEFINE_func_801898C8()  /* dedup: shared engine-core @0x801898C8 (src/shared) */


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80189904);

DEFINE_func_80189950()  /* dedup: shared engine-core @0x80189950 (src/shared) */

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80189958);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80189A00);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80189A70);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80189B1C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80189C6C);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80189D10);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_80189DB8);


// @class: struct
// @stuck: none — MATCH (94 ins). Keys: (1) cache out[0] in a local `o` before the switch so gcc
//   holds it in $a0 across the case stores (else it reloads/`lh` per case, +3 ins); (2) declare the
//   `in` struct BEFORE `out[2]` so in@sp+0x10 / out@sp+0x20; (3) the 0x14 word is written via
//   `*(s32*)&in.lo = D_80126B60` then the high short RMW'd `in.hi -= 0x20` (memory lhu/sh, not reg);
//   (4) order the three global assigns B60,B5C,B64 (B60 first → v0/v1/a2 alloc); (5) explicit
//   `case 2: break;` after case 3 so gcc emits the `beq $v1,2` test with case1 falling into case3.

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8002D4C8(s32, s32);
extern void func_8012A828(s32, void *);
extern void func_8012B77C(void *, s32, void *);
extern void func_8012B2CC(s32);
extern s32 func_8012C588(s32 a0, s32 a1);


void func_80189E58(s32 param_1) {

    extern M2C_UNK D_801A79A4;
    extern u8   D_801A777C;
    extern u8 D_80126B5C;
    extern s32  D_80126B60;
    extern s32  D_80126B64;
    s32 iVar1;
    struct In in;
    s32 out[2];
    s32 t;
    s32 o;

    iVar1 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }
    ((void (*)(s32, void *))func_8001C214)(iVar1, &(*(u8 *)&D_801A79A4));
    if ((*(u16 *)(param_1 + 0x70) & 0x1000) == 0) {
        func_8002D4C8(0x43A, 0);
    } else {
        func_8002D4C8(0x6D6, 0);
    }
    func_8012A828(param_1, &D_801A777C);
    *(s16 *)(param_1 + 2) = 1;
    *(s32 *)(param_1 + 0x1C) = 100;

    *(s32 *)&in.lo = D_80126B60;
    in.hi -= 0x20;
    in.w0 = (*(s32 *)&D_80126B5C);
    in.w2 = D_80126B64;
    func_8012B77C(out, param_1 + 4, &in);

    o = out[0];
    t = *(u16 *)(param_1 + 0x70) & 0xF;
    switch (t) {
    case 0:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)o;
        break;
    case 1:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = (s16)o;
    case 3:
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = (s16)(o >> 16);
        break;
    case 2:
        break;
    }

    if (*(u16 *)(param_1 + 0x70) & 0x1000) {
        *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) << 1;
    }
    func_8012B2CC(param_1);
    ((void (*)(s32, s32))func_8012C588)(0xBC, param_1);
}



extern void (*D_801A7818[])(void);

void func_80189FD0(void *a0) {
    D_801A7818[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801A782C[])(void);

void func_8018A00C(void *a0) {
    D_801A782C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CBF4(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern s32 D_801A7804;
extern s32 D_801A7810;
extern u8 D_800D3918[];
extern s32 D_80126D50;

void func_8018A048(s32 param_1) {
    s32 s0 = param_1;
    s32 v;

    func_8012B14C(s0, (s32)&D_801A7804);
    if (((s32 (*)(s32))func_8012CBF4)(s0) != 0) {
        func_80146A6C(6, (void *)s0, *(s16 *)(s0 + 0x6), *(s16 *)(s0 + 0xA),
                      *(s16 *)(s0 + 0xE), 0, 0);
        v = func_80132EF4(s0, 0x22);
        if (v != 0) {
            *(s16 *)(v + 0x34) = 0x2000;
        }
    } else {
        if (func_8012D5E4(s0, (s32)&D_801A7810, (s32)&D_800D3918, 0x19) == 0 &&
            (*(s16 *)(s0 + 0x70) == 2 || D_80126D50 == 0) &&
            func_8012BEE8(s0) == 0) {
            return;
        }
    }
    func_8012C218((void *)s0);
}



// @class: schedule
// @stuck: none — MATCH (71 ins). Tail schedule: read out.c into an explicit temp BEFORE the 0x5a/1 const stores so gcc hoists its lhu early (load-delay filled by li 0x5a) and stores out.c last from a held reg; without the temp gcc instead deferred out.b's store. in/out are two separate SV3{s16 a,b,c} stack slots (sp+0x10, sp+0x18) for ((void (*)(int, void *, void *))func_8012F214)(a0,&in,&out). 0x34 compare reads u16 (lhu, not lh).

extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

extern int D_801A7820;

void func_8018A128(int param_1)
{
    SV3 in;
    SV3 out;
    short c;

    if (*(unsigned short *)(param_1 + 0x34) == 0) {
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
            *(short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x12);
        ((void (*)(void))func_8012B2CC)();
        func_8012B23C(param_1);
        ((void (*)(int, void *))func_8012B14C)(param_1, &D_801A7820);
        in.a = 0;
        in.b = 0;
        in.c = 0x10;
        ((void (*)(int, void *, void *))func_8012F214)(param_1, &in, &out);
        *(short *)(param_1 + 6) = out.a;
        *(short *)(param_1 + 0xa) = out.b;
        c = out.c;
        *(int *)(param_1 + 0x1c) = 0x5a;
        *(short *)(param_1 + 0x34) = 1;
        *(short *)(param_1 + 0xe) = c;
    }
    *(short *)(*(int *)(param_1 + 0x20) + 0x10) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x10) - 0x80;
    *(short *)(*(int *)(param_1 + 0x20) + 0x12) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x12) + 4;
    *(short *)(*(int *)(param_1 + 0x20) + 0x14) =
        *(short *)(*(int *)(param_1 + 0x20) + 0x14) + 5;
    func_8012AD80(param_1);
    if (func_8012BEE8(param_1) != 0) {
        ((void (*)(int))func_8012C218)(param_1);
    }
}



// @class: other
// @stuck: none — MATCH (expected); 16-bit sh stores via short* casts, s0=param_1 call-crossing

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);

extern int D_801A7AD4;

void func_8018A244(int param_1)
{
    int v0;

    v0 = ((int (*)(void))func_8012C1B8)();
    *(int *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(int))func_8012CAE4)(param_1);
    } else {
        ((int (*)(int, void *))func_8001C214)(v0, &D_801A7AD4);
        *(short *)(param_1 + 0x2) = 1;
        *(short *)(param_1 + 0x34) = 0;
    }
}


INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018A2A0);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018A3C8);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018A3FC);

INCLUDE_ASM("asm/ov_SC02_003/nonmatchings/ov_SC02_003_jr_8018173C", func_8018A440);


extern void func_8001D074(s32 a0, s32 a1);
extern void func_8001CD04(s32 a0, s32 a1);




void func_8018A550(Ctl_8018A550_8018A550 *ctl, Rec_8018A550_8018A550 *rec)
{
    s32 i;
    Obj_8018A550_8018A550 *m;
    s16 v;
    u16 t;

    do {
        for (i = 0; i < 8; i++) {
            if (ctl->slots[i] == 0) {
                break;
            }
        }
        m = (Obj_8018A550_8018A550 *)((s32 (*)(s32, s32))func_8001D074)(0x7E, 0x100);
        if (m != 0) {
            ((void (*)(Obj_8018A550_8018A550 *, s32))func_8001CD04)(m, rec->fC);
            m->f4 |= 0xF0000000;
            v = rec->f6;
            m->f1C = v;
            m->f1A = v;
            m->f18 = v;
            ctl->slots[i] = m;
            ctl->ids[i] = rec->f4;
        }
        t = rec->f0;
        rec++;
    } while (t != 0xFF);
}


















void func_8018A640(s32 *a0, s32 a1, s32 a2, s32 a3)
{
  s8 *new_var;
  new_var = (s8 *) (a0 + 0x0);
  *new_var = a1;
  new_var = a0;
  *((s8 *) (new_var + 0x1)) = a2;
  *((s8 *) (new_var + 0x2)) = a3;
}

DEFINE_func_8018A650()  /* dedup: shared engine-core @0x8018A650 (src/shared) */


extern s32 D_801E8668;
extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_8018A660(s32 a0, s32 a1) {
    D_801E8668 = a1;
    return func_8012C588(0x85, a0);
}


extern u8 D_801152A8[];
extern s32 D_801E8668;
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




s32 func_8018A690(s32 param_1) {

    extern M2C_UNK D_8018AF28;
    extern s32 func_8012C354(s32 a0, s32 a1);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801A7AF0;
    extern char * D_801A7B24;
    extern char D_801E8648[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801A7AF0) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_8018AF28));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801E8668, &s60);
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
        tmp = D_801A7B24;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801A7B24 = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801E8648 < puVar4) {
        D_801A7B24 = D_801E8648 - 0x120;
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
            tmp = D_801A7B24;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801A7B24 = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801E8648 < puVar4) {
            D_801A7B24 = D_801E8648 - 0x120;
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

s32 func_8018A8D4(s32 param_1) {

    extern signed char D_801A7ADC[];
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
        p = D_801A7ADC;
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
            p = D_801A7ADC;
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



extern void (*D_801A7B28[])(void);

void func_8018AB74(void *a0) {
    D_801A7B28[*(u16 *)((s32)a0 + 0x2)]();
}




