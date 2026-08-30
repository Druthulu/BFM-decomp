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
extern u8 D_8018D1F8;
extern u8 D_8018D168;
extern u8 D_8018D144;
extern u8 D_8018D120;
extern u8 D_8018D1D4;
extern u8 D_8018D1B0;
extern u8 D_8018D18C;
extern u8 D_8018D0FC;
extern void func_80145934(void);
extern u8 D_8018D288;
extern u8 D_8018D264;
extern u8 D_8018D240;
extern u8 D_8018D21C;
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
extern unsigned char D_8018C680[];
extern unsigned char D_8018C6B0[];
extern unsigned char D_8018C700[];
extern unsigned char D_8018C730[];
extern unsigned char D_8018C760[];
extern void func_80145EE8(s32 param_1);
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_80146074(void);
extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0();
extern void func_8014607C(void);
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
extern void (*D_8018C7B0[])(void *);
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
extern s32 D_8018C878[];
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
extern u8 D_8018C900[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018C908;
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
extern int D_801BEF08;
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
extern s32 D_801BEF0C;
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
extern s32 D_8018C938;
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
extern void (*D_8018C9E0[])(void);
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
extern void (*D_8018CA04[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018C9F4;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018CA18[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018CA24[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018CA34[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018CA4C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018CA3C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018CA60[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018CA7C[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018CA6C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018CA90[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018CAA4[])(void);
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
extern s32 D_8018CAB8;
extern void (*D_8018CAE0[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018CAC0;
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
extern int (*D_8018CB2C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018CB30[])(void);
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
extern unsigned short D_8018CF94[];
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
extern void (*D_8018CFA4[])(void);
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
extern int D_801BEF40;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018CFCC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018CFAC;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018CFBC;
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
extern void (*D_8018D00C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018D014[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018CFE0;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018D020[])(void);
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
extern u8 D_8018CFF0;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801BEF48;
extern s32 D_801BEF54;
extern s32 D_801BEF58;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018D05C[])(s32 *);
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
extern s32 D_8018D030[];
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
extern s32 D_801BEF50;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018D2AC[])(void);
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
extern char D_8018D0CC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018D350[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018D4A4[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018D2C0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018D4AC[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018D2D0;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018D2F0;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018D4B4[])(void);
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
extern void (*D_8018D4DC[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018D4E8[])(void);
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
extern void (*D_8018D35C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018D58C;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018C670[];
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
extern unsigned char D_8018D5A0[];
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
extern s8 D_8018D5DC[];
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
extern u16 D_8018D624;
extern u16 D_8018D626;
extern u16 D_8018D628;
extern s32 D_8018D62C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018D634;
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
extern int D_8018D340;
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
extern unsigned int D_8018D6B8[];
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
extern void (*D_8018D768[])(void);
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
extern u16 D_8018D798[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018D7FC;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801BEF60[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018D820[])(void);
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
extern int D_801BEFB8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018D868[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018D858;
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
extern char D_801BE7B0[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018D870[])(void);
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
extern void (*D_8018D8C4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018D88C;
extern s16 D_8018D8C0;
extern s16 D_8018D8BE;
extern s16 D_8018D8BC;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018D8D0[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801BF018;
extern u8 D_801BF019;
extern u8 D_801BF01A;
extern u8 D_801BF01B;
extern u8 D_801BF01C;
extern u8 D_801BF01D;
extern u8 D_801BF01E;
extern u8 D_801BF01F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018D8E0[])(void);
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
extern s32 D_801BF058;
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
extern void (*D_8018D924[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018D9A0[];
extern s32 D_8018D9C0[];
extern u8 D_8018DA3C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018DA5C[];
extern u8 D_8018DA7C[];
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
extern void (*D_8018DB18[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018DB94[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801BE7C0;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018DBA0[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018DBA8[])(void);
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
extern void (*D_8018DC70[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018DC80[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018DC90[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018DC9C[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018DBFC[];
extern u8   D_8018DC10[];
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
extern void (*D_8018DCB4[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018DCBC[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018DCC4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018DCCC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018DCD4[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018DCDC[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018DCE4[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018DD98[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018DDA0[])(void);
extern void func_80169F00(void *a0);
extern char D_8018DD50[];
extern char D_8018DD10[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018DDD8[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018DDE4[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018DE2C[])(void);
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
extern void (*D_8018DEA8[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801BF378;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018DE9C[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018DEE0[];
extern unsigned short D_8018DEE8[];
extern unsigned short D_8018DEF0[];
extern unsigned char D_801BF380[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801BF378;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018DEF8[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801BF4B4;
extern M2C_UNK D_801BF4B8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801BF440;
extern void (*D_8018DF28[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801BF4BC[];
extern u8 D_801BF4C4[];
extern u8 D_801BF474[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018DF30[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018DF4C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018DF54[])(void);
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
extern void (*D_8018DFBC[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018DF60;
extern u8 D_8018DF6C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018DFF0[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018DFF8[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018E04C[])(void);
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
extern u16 D_8018E080[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018E070[];
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
extern s32 D_8018E09C;
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
extern void (*D_8018E114[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018E11C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018E124[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018E12C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018E134[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018E13C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018E148[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018E154[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018E160[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018E170[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018E180[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018E188[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018E190[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018E198[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018E1A0[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018E1A8[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018E1B0[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018E1B8[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018E1C0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018E1C8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018E1D0[])(void);
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
extern void (*D_8018E1D8[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018E1E0[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018E1E8[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018E1F0[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018E1F8[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018E200[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018E208[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018E210[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018E218[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018E220[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018E228[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018E230[])(void);
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
extern void (*D_8018E274[])(void);
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
extern M2C_UNK D_8018E238;
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
extern void (*D_8018E2A4[])(void);
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
extern void (*D_8018E2E0[])(void);
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
extern void (*D_8018E338[])();
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
extern void (*D_8018E348[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018E350[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_8018E4B8[])();
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
extern void (*D_8018E4C4[])();
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
extern M2C_UNK D_801BEA08;
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
extern s16 D_801C0420;
extern int func_80178970(void);
extern void func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801BFBF8;
extern short D_801C0494;
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
extern s32 D_801C0024;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801C004C;
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
extern s16 D_801C0008;
extern s32 func_8017A3B0(void);
extern short D_801C0044;
extern short D_801C0040;
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
extern s16 D_801C000C;
extern u16 D_801C008C;
extern u16 D_801C008E;
extern u16 D_801C0090;
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
extern s16 D_801C0084;
extern s16 D_801C0086;
extern s16 D_801C0088;
extern s16 D_801C007C;
extern s16 D_801C007E;
extern s16 D_801C0080;
extern void func_8017B7A8(void);
extern s16 D_801C009C;
extern s16 D_801C009E;
extern s16 D_801C00A0;
extern s16 D_801C00A4;
extern s16 D_801C00A6;
extern s16 D_801C00A8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801C0094;
extern short D_801C0096;
extern short D_801C0098;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801C002C;
extern SV4 D_801C0034;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801C0054[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801C0050)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018E6A0[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8018E6D8[])(void);
extern void func_8017BEF8(void *a0);
extern void (*D_8018E6EC[])(void);
extern void func_8017C524(void *a0);
extern void (*D_8018E700[])(void);
extern void func_8017C7C4(void *a0);
extern void func_8017CA80(s32 arg0);
extern s32 D_801C0370;
extern u16 D_801C0374, D_801C0376, D_801C0378;
extern s32 D_801C037C;
extern s32 D_801C038C;
extern u16 D_801C0390, D_801C0392, D_801C0394;
extern s32 D_801C0398;
extern s32 D_801C03A8;
extern u16 D_801C03AC, D_801C03AE, D_801C03B0;
extern s32 D_801C03B4;
extern void func_8017D960(s32 arg0);
extern int func_80181774(int param_1);
extern void func_80180D88(void);
extern void (*D_8018E7A4[])(void);
extern void func_80180E14(void *a0);
extern void func_80181188(void);
extern s32 func_80180E50(s32 a0);
extern s32 func_80180E94(void);
extern void (*D_8018E7AC[])(void);
extern void func_80180EB8(void *a0);
extern void func_801811B0(void);
extern s32 func_80180EF4(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_80180F34(u8 *a0);
extern s32 func_800D1EBC(void);
extern void func_80180FB0(void);
extern void (*D_8018E7B8[])(void);
extern void func_80180FD0(void *a0);
extern s32 func_8018100C(s32 a0);
extern void (*D_8018E7C4[])(void);
extern void func_80181080(void *a0);
extern void func_801812B0(void);
extern s32 func_801810BC(s32 arg0);
extern s32 func_801810F8(void);
extern void func_80181168(void);
extern s32 D_8018E7D8;
extern void (*D_8018E7E4[])(void);
extern void func_801811D8(void *a0);
extern void (*D_8018E7EC[])(void);
extern void func_80181404(void *a0);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_801815DC(s32 param_1, s16 *param_2);
extern void func_8013B7F4(void *a0, int a1);
extern s32 func_801817A4(void);
extern void (*D_80199DC0[])(void);
extern void func_801817C4(void *a0);
extern void func_80181B58(void);
extern void func_8018282C(void *a0);
extern void func_80181B60(void *a0);
/* ==== end §8b carried decl layer ==== */

typedef struct { short m[3][3]; long t[3]; } MTX_801851A8;

/* func_80182038 — ov_SC03_089 (ov_SC03_089_jr_8017CA80), 154 ins, jtbl_801C53E4 (5 entries,
 * minval 0 / maxval 4 — `lhu` + `sltiu 5`, so the switch expression is UNSIGNED and neither
 * §162a2's leading nor §162a1/§162a3's trailing empty-case tell applies).
 *
 * Decl provenance (§161c) — forms copied VERBATIM from the destination TU where it already
 * declares the callee ABOVE this function's INCLUDE_ASM (src/…/ov_SC03_089_jr_8017CA80.c:5332):
 *   func_8002D4C8   TU:59 / 3984 / 4018   `extern void func_8002D4C8(s32 a0, s32 a1);`   (visible)
 *   func_8012B2CC   TU:2523 / 4913        `extern void func_8012B2CC(s32 a0);`           (visible)
 *   func_8012B178   TU:5635 (BELOW)       same canonical form, so it agrees, not conflicts
 *   func_801826F0   TU:5351 (BELOW)       DEFINED `s32 func_801826F0(s32 arg0)` — agrees
 *   func_8018271C   TU:5356 (BELOW)       INCLUDE_ASM only, no decl to conflict with
 * func_8012CBF4 / func_8012B8E4 / func_8012BEE8 / func_8012B200 / func_8012B77C / D_80199E14
 * are not declared anywhere in the host TU; the forms below are the project-canonical ones
 * (ov_SC03_099_jr_8012ACE0.c:1688, :353, ov_SC03_099_jr_801380E0.c:272, …).
 *
 * THE SHAPE THAT COSTS THE MATCH — the shared `.L801846F4` tail is a CROSS-JUMP, not a `break`.
 * Case 0 (both arms) and case 3 each end `lhu $v0,0x34; addiu $v0,$v0,1` and only the STORE
 * `sh $v0,0x34($s0)` is shared. Spelling that with a switch-scope `s16 nv; … break;` + a single
 * post-switch `*(s16*)(a0+0x34) = nv;` compiles to 152 ins / 113 mismatched: one shared pseudo
 * makes case 3's `lhu` land in $v1 (`addu $2,$3,1`), which breaks jump.c's minimum=1 path
 * (find_cross_jump(insn, JUMP_LABEL(insn), 1) — jump.c:1978) against case 3's trailing `addiu`,
 * so the minimum=2 jump_chain path fires instead and welds case-0 arm1 into arm2 (a 3-insn tail
 * at a new label) — a merge the target does not have. Written LONGHAND (each arm stores 0x34
 * itself and `return`s), every arm gets its own single-block temp, all of them land in $v0, and
 * the compiler makes exactly the target's merge. Cf. §162h's floor law read from the other side:
 * here the source-level factoring is what has to be REMOVED. */

extern void func_8012CBF4(s32 a0);   /* canonical `void`; $v0 is used in case 0 -> cast at the site */
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern void func_8018271C(s32 out, s32 a1, s32 a2);
extern s32  func_801826F0(s32 arg0);

void func_80182038(s32 a0) {

    extern u8 D_80199E14[];
    s32 sp10[4];   /* 0x10: the func_8012B77C "to" record — fields at +0x2/+0x6/+0xA */
    s32 sp20[2];   /* 0x20: the 8-byte out buffer shared by func_8018271C and func_8012B77C */
    s32 t;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (((s32 (*)(s32))func_8012CBF4)(a0) != 0) {
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            return;
        } else {
            if (*(s16 *)(a0 + 0x100) >= *(s16 *)(a0 + 0xA)) {
                return;
            }
            *(s16 *)(a0 + 0xA) = *(s16 *)(a0 + 0x100);
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            return;
        }

    case 1:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 6);
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        func_8012B200((u8 *)a0);
        *(s32 *)(a0 + 0x1C) = 0x20;
        func_8002D4C8(0x6FF, 0);
        return;

    case 2:
        func_8018271C((s32)sp20, a0, (s32)D_80199E14);
        t = sp20[0];
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t >> 16;
        func_8012B178(a0, *(s32 *)(a0 + 0xE0) - 0x80000);
        func_8012CBF4(a0);
        if (func_801826F0(a0) != 1) {
            if (func_8012BEE8(a0) == 0) {
                return;
            }
        }
        *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        *(s16 *)((s32)sp10 + 0x2) = *(u16 *)(a0 + 0x88);
        *(s16 *)((s32)sp10 + 0x6) = *(u16 *)(a0 + 0x8A);
        *(s16 *)((s32)sp10 + 0xA) = *(u16 *)(a0 + 0x8C);
        func_8012B77C((s32)sp20, a0 + 4, (s32)sp10);
        t = sp20[0];
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t >> 16;
        func_8012B2CC(a0);
        func_8012B178(a0, *(s32 *)(a0 + 0xE0) - 0x80000);
        *(s32 *)(a0 + 0x1C) = 0x80;
        return;

    case 3:
        func_8012CBF4(a0);
        if (func_8012BEE8(a0) == 0) {
            if (*(s16 *)(a0 + 0xA) >= *(s16 *)(a0 + 0x8A)) {
                return;
            }
        }
        *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0x8A);
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        *(s32 *)(a0 + 0x1C) = 0x3C;
        *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        return;

    case 4:
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        /* fall through */
    default:
        *(s16 *)(a0 + 0x2) = 4;
        return;
    }
}

typedef struct { s16 a, b, c; } SV3x_80184B30_801822A0;
typedef struct { short m[3][3]; long t[3]; } MTX_801851A8_801839C4_801822A0;

/* Declarations copied VERBATIM from the destination TU (src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c)
 * where they are already established for the near-identical sibling func_801841A4's case 2
 * (same sp10[4]/sp20[2] shared-buffer idiom, same func_8012B77C "to" record):
 *   func_8012BEE8   TU:5640   extern s32  func_8012BEE8(s32 a0);
 *   func_8012B2CC   TU:5644 / 2523 / 4913   extern void func_8012B2CC(s32 a0);
 *   func_8012B178   TU:5643 / 5635   extern void func_8012B178(s32 a0, s32 a1);
 *   func_8012B77C   TU:5645   extern s32  func_8012B77C(s32 out, s32 from, s32 to);
 *   func_8012B0B4   TU:6779   extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
 *   func_8012E88C   TU:6520   extern void func_8012E88C(u8 *a0);
 *   func_8012A828   TU:7157   extern void func_8012A828(s32 a0, s32 a1);
 * D_8019C84C is not declared in this TU; other overlays (ov_SC03_113) know it as a 10-entry
 * s32/fnptr array, but here only its ADDRESS is taken (passed through as an opaque s32/void*
 * to func_8012A828), so it is declared in the rawest form per law 4, matching this TU's own
 * D_801A0CB8 idiom at line 4670 (`extern u8 D_801A0CB8[];` ... `(s32)D_801A0CB8`).
 */
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_8012E88C(u8 *a0);
extern void func_8012A828(s32 a0, s32 a1);
extern s32  rand(void);

void func_801822A0(s32 a0) {

    extern u8   D_8019C84C[];
    s32 sp10[4];   /* 0x10: the func_8012B77C "to" record — fields at +0x2/+0x6/+0xA */
    s32 sp20[2];   /* 0x20: the 8-byte out buffer shared by func_8012B0B4 and func_8012B77C */
    s32 t;
    s32 r;

    if (func_8012BEE8(a0) == 0) {
        return;
    }

    if (*(u16 *)(a0 + 0x70) & 1) {
        *(s16 *)(a0 + 0x2) = 1;
    } else {
        *(s16 *)(a0 + 0x2) = 3;
        r = rand();
        func_8012B0B4((unsigned int *)sp20, r % 0x1000, 0x100);
        t = sp20[0];
        *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) + t;
        *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 0x100;
        *(s16 *)(a0 + 0xE) = *(u16 *)(a0 + 0xE) + (t >> 16);
        *(s16 *)((s32)sp10 + 0x2) = *(u16 *)(a0 + 0x88);
        *(s16 *)((s32)sp10 + 0x6) = *(u16 *)(a0 + 0x8A);
        *(s16 *)((s32)sp10 + 0xA) = *(u16 *)(a0 + 0x8C);
        func_8012B77C((s32)sp20, a0 + 4, (s32)sp10);
        t = sp20[0];
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t >> 16;
        func_8012B2CC(a0);
        func_8012B178(a0, *(s32 *)(a0 + 0xE0));
    }

    *(s16 *)(a0 + 0x5C) = *(u16 *)(*(s32 *)(a0 + 0x78) + 0x2);
    *(s16 *)(a0 + 0x76) = *(u16 *)(*(s32 *)(a0 + 0x78) + 0x0);
    func_8012E88C((u8 *)a0);
    func_8012A828(a0, (s32)D_8019C84C);

    {
        s32 u = *(s32 *)(a0 + 0xCC);
        if (u != 0) {
            *(s16 *)(u + 0xFC) = 0;
        }
    }
}


void func_801823F0(s32 a0) {
    s32 v1 = *(s32 *)(a0 + 0xCC);
    *(s16 *)(a0 + 2) = 9;
    *(s32 *)(a0 + 0x1C) = 0x20;
    *(s16 *)(a0 + 0x34) = 0;
    if (v1 != 0) {
        *(s16 *)(v1 + 0xFC) = 1;
    }
}


typedef struct { s16 a, b, c; } SV3x_80184B30_8018241C;
typedef struct { short m[3][3]; long t[3]; } MTX_801851A8_801839C4_8018241C;

/* Declarations conformed to this TU's existing canonical forms (§193-B law 2):
 *   func_8012BEE8   ov_SC03_090_jr_8017CA80.c:5640  `extern s32  func_8012BEE8(s32 a0);`
 *   func_8012B200   ov_SC03_090_jr_8017CA80.c:5641  `extern void func_8012B200(u8 *a0);`
 *   func_8012B2CC   ov_SC03_090_jr_8017CA80.c:5644  `extern void func_8012B2CC(s32 a0);`
 *   func_8012B77C   ov_SC03_090_jr_8017CA80.c:5645  `extern s32  func_8012B77C(s32 out, s32 from, s32 to);`
 *   func_8012CBF4   ov_SC03_090_jr_8017CA80.c:5638  `extern void func_8012CBF4(s32 a0);` (return value unused here)
 *   func_8012B178   ov_SC03_090_jr_8017CA80.c:5643  `extern void func_8012B178(s32 a0, s32 a1);`
 *   func_8012B0B4   ov_SC03_090_jr_8017CA80.c:6779  `extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);`
 *   func_8012E8A8   ov_SC03_090_jr_8017CA80.c:6244/6677 `extern void func_8012E8A8(u8 *a0);`
 *   func_8012E778   not declared in this TU; project-canonical form used elsewhere
 *                   (e.g. ov_SC03_099_jr_80182F24.c:2769) `extern s32 func_8012E778(s32 a0, s32 a1);`
 *
 * Structural template: this TU's OWN func_801841A4 case 2 (same file, ~line 5685) walks the
 * identical func_8012B77C((s32)out, a0+4, (s32)to) / t=out[0] / store-split-into-(a0+0x20)
 * ->0x10/0x12 shape, and uses the same `s32 sp10[4]` "to"-record idiom with fields written at
 * byte offsets +0x2/+0x6/+0xA via `*(s16*)((s32)sp10 + N)`. Reused verbatim here. The banked
 * seed_ref ov_SC02_035:func_80183A14 supplied the `s16 r = rand(); func_8012B0B4(...)` /
 * `func_8012B200/func_8012B2CC/func_8012B178` tail shape.
 */
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012B2CC(s32 a0);
extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern void func_8012CBF4(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_8012E8A8(u8 *a0);
extern s32  func_8012E778(s32 a0, s32 a1);
extern s32  rand(void);

void func_8018241C(s32 a0)
{
    s32 sp10[6];   /* the func_8012B77C "to" record — fields at +0x2/+0x6/+0xA;
                    * sized 6 words (24B, not case2's 4) — the target's buf sits
                    * at sp+0x28, a full 24B above sp10's base at sp+0x10. */
    s32 sp28[2];   /* reused as both func_8012B0B4's dest and func_8012B77C's "out" */
    s32 t;
    s16 r;

    if (*(u16 *)(a0 + 0x34) == 0) {
        if (func_8012BEE8(a0) != 0) {
            r = rand();
            func_8012B0B4((unsigned int *)sp28, r % 0x1000, (r % 0x80) + 0xC0);

            t = sp28[0];
            *(s16 *)((s32)sp10 + 0x2) = t;
            *(s16 *)((s32)sp10 + 0x6) = *(s16 *)(a0 + 0xA) - 0x180;
            *(s16 *)((s32)sp10 + 0xA) = t >> 16;
            func_8012B77C((s32)sp28, a0 + 4, (s32)sp10);

            t = sp28[0];
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t >> 16;
            func_8012B200((u8 *)a0);
            func_8012B2CC(a0);
            func_8012B178(a0, *(s32 *)(a0 + 0xE0) - 0x20000);
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
    } else {
        func_8012CBF4(a0);
        if (func_8012E778(a0, 0xA000C8) == 0) {
            *(s16 *)(a0 + 0x2) = 0xA;
            *(s32 *)(a0 + 0x1C) = 0x80;
            func_8012E8A8((u8 *)a0);
        }
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8012E88C(u8 *a0);

void func_80182578(s32 a0)
{
    if (func_8012BEE8(a0) != 0) {
        *(s16 *)(a0 + 0x2) = 1;
        func_8012E88C((u8 *)a0);
        {
            s32 t = *(s32 *)(a0 + 0xCC);
            if (t != 0) {
                *(s16 *)(t + 0xFC) = 0;
            }
        }
    }
}




void func_801825C8(arg0)
s32 arg0;
{
    if (*(s32*)(arg0 + 0xCC) != 0) {
        *(u16*)(*(s32*)(arg0 + 0xCC) + 0xFC) = 1;
    }
}


extern void func_8002A04C(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8012C218(void *a0);

void func_801825E4(s32 arg0) {
    s32 temp;

    func_8002A04C(arg0);

    if ((*(s16 *)(arg0 + 0x70) & 0x8000) != 0) {
        temp = *(s32 *)(arg0 + 0x20);
        *(s16 *)(arg0 + 0x2) = 7;
        *(s8 *)(arg0 + 0xC1) = 0;
        *(s32 *)(arg0 + 0x1C) = 0x40;
        *(s16 *)(arg0 + 0x5E) = 0;
        *(s16 *)(arg0 + 0x5C) = 0;
        *(s16 *)(temp + 0x12) = 0;
        *(s16 *)(temp + 0x10) = 0;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x2C) &= 0xFFEF;
        temp = *(s32 *)(arg0 + 0x20);
        *(s16 *)(temp + 0x1C) = 0x1000;
        *(s16 *)(temp + 0x1A) = 0x1000;
        *(s16 *)(temp + 0x18) = 0x1000;
        func_8012B200((u8 *)arg0);
        func_8012E8A8((u8 *)arg0);
        *(s16 *)(arg0 + 0x6) = *(u16 *)(arg0 + 0x88);
        *(s16 *)(arg0 + 0xA) = *(u16 *)(arg0 + 0x8A);
        *(s16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0x8C);
    } else {
        func_8012C218(arg0);
    }
}


extern void func_8012A828(s32 a0, s32 a1);

void func_801826A0(s32 a0) {
    extern u8 D_8019C84C[];
    register s32 t __asm__("$2");

    t = *(u16 *)(a0 + 0x70) & 1;
    if (t == 0) {
        t = 4;
    } else {
        t = 1;
    }
    *(s16 *)(a0 + 0x2) = t;
    t = *(s32 *)(a0 + 0x78);
    t = *(u16 *)(t + 0x2);
    *(s16 *)(a0 + 0x5C) = t;
    func_8012A828(a0, (s32)D_8019C84C);
}



extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern u8 D_80199E78[];
    s32 func_801826F0(s32 arg0) {
        return ((s32 (*)(s32, void *, void *, s32))func_8012D5E4)(arg0, &D_80199E78[0], &D_80199E78[8], 5) != 0;
    }


extern s16 D_80126CBA;

void func_8018271C(s32 out, s32 a1, s32 a2) {
    s32 sp10[4];
    s32 sp20;
    s16 *q;
    u16 *p;
    s16 t;
    register s32 rv __asm__("$2");

    q = &D_80126CBA;
    if (*q == 0) {
        if (func_80182898(a1) == 0) {
            p = (u16 *)(q - 3);
            *(s32 *)(a1 + 0xDC) = 0;
        } else {
            p = (u16 *)(a1 + 0x88);
            *(s32 *)(a1 + 0xDC) = 1;
        }
    } else {
        p = (u16 *)(a1 + 0x88);
        *(s32 *)(a1 + 0xDC) = 1;
    }
    *(s16 *)((s32)sp10 + 0x2) = p[0] + *(u16 *)a2;
    t = p[1] + *(u16 *)(a2 + 2);
    *(s16 *)((s32)sp10 + 0x6) = t;
    *(s16 *)(a1 + 0x100) = t;
    *(s16 *)((s32)sp10 + 0xA) = p[2] + *(u16 *)(a2 + 4);
    func_8012B77C((s32)&sp20, a1 + 4, (s32)sp10);
    rv = (s32)out;
    *(s32 *)rv = sp20;
    __asm__ __volatile__("" : : "r" (rv));
}




extern s32 func_80134510(s32 arg);

s32 func_801827EC(s32 a0)
{
    u16 sp[3];
    s32 result;
    sp[0] = *(u16 *)(a0 + 0x6);
    sp[1] = *(u16 *)(a0 + 0xA);
    sp[2] = *(u16 *)(a0 + 0xE);
    result = func_80134510((s32)sp);
    return ((u32)result > 0) ? 1 : 0;
}



extern s32 func_8012BD14(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

/* The `register ... __asm__("$4")` pin on the FIRST call argument is load-bearing.
 * The target sets $a0 = 0x6FE in the ENTRY block (dbr steals it into the `bnez`
 * delay slot -- sched.md D1 backward fill), but a plain `s32 id = 0x6FE;` local is
 * rematerialised at the use site (single-set constant pseudo -> REG_EQUIV), so the
 * `li` sinks past the label into the join block and dbr fills the slot with the
 * if-body's `lui` instead (SHIFT-DRIFT/+1). Pinning the local to $a0 makes the `li`
 * a hard-reg set that stays where it is written, and the call's arg move degenerates
 * to a deleted `(set (reg 4) (reg 4))`. */
void func_8018282C(void *a0) {
    register s32 id __asm__("$4");
    s32 vol;
    s32 t;

    vol = 0x7F;
    t = func_8012BD14((s32)a0);
    id = 0x6FE;
    if (t > 0x1000) {
        vol -= (t - 0x1000) / 0x2700;
    }
    func_8002D4C8(id, (vol | 0x1000) & 0xFFFF);
}



extern u8 D_80078EC1;
    s32 func_80182898(void) {
        return (D_80078EC1 ^ 0x15) == 0;
    }



extern void (*D_80199EF8[])(void);

void func_801828B0(void *a0) {
    D_80199EF8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012C194(void);
extern void func_8001CD9C(int, void *);
extern u8 D_80199E88;
extern u8 D_80199EC8;
extern u8 D_8019A384;

void func_801828EC(s32 param_1)
{
    s32 v0;
    s32 s0;
    s32 v1;
    u16 t36;
    register s32 a0 __asm__("$4");

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }

    func_8001C214(v0, (s32)&D_8019A384);

    s0 = func_8012C194();
    if (s0 != 0) {
        *(s32 *)(param_1 + 0xCC) = s0;
        a0 = s0;
        func_8001CD9C(a0, (void *)&D_80199E88);
        *(s16 *)(s0 + 0x18) = 0x800;
        *(s16 *)(s0 + 0x1A) = 0x800;
        *(u32 *)(s0 + 4) |= 0x50000000;
    }

    v1 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x20;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x80) = (s32)&D_80199EC8;
    t36 = *(u16 *)(*(s32 *)(param_1 + 0x64) + 0x36);
    *(s16 *)(param_1 + 2) = 1;
    *(s16 *)(param_1 + 0xFE) = t36;
}



typedef struct { s16 a, b, c; } SV3x_80184B30_801829C4;
typedef struct { s16 a, b, c, d; } SV4x_80184B30_801829C4;

extern void func_8012B23C(void *a0);
extern void func_80182CB4(s32 param_1);
extern void func_80182D18(s32 param_1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

void func_801829C4(void *a0)
{

    extern s32 D_80199F08;
    s32 s0 = (s32)a0;
    s32 s1;
    SV3x_80184B30_801829C4 out;

    s1 = *(s32 *)(s0 + 0x64);

    if (*(s16 *)(s0 + 0xFC) != 0) {
        *(s16 *)(s0 + 0x2) = 2;
        func_8012B23C((void *)s0);
        *(s32 *)(s0 + 0x1C) = 0x5A;
        return;
    }
    __asm__("" : "=r"(s0) : "0"(s0) : "memory");

    if (*(s16 *)(s0 + 0xFE) != *(s16 *)(s1 + 0x36)) {
        func_80182CB4(s0);
        return;
    }

    func_8012F214(s1, (s32)&D_80199F08, (s32)&out);
    *(s16 *)(s0 + 0x6) = out.a;
    *(s16 *)(s0 + 0xA) = out.b;
    *(s16 *)(s0 + 0xE) = out.c;
    func_80182D18(s0);

    *(s32 *)(*(s32 *)(s0 + 0x20) + 0x20) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x20);
    *(SV4x_80184B30_801829C4 *)(*(s32 *)(s0 + 0x20) + 0x10) = *(SV4x_80184B30_801829C4 *)(*(s32 *)(s1 + 0x20) + 0x10);
    *(SV4x_80184B30_801829C4 *)(*(s32 *)(s0 + 0x20) + 0x18) = *(SV4x_80184B30_801829C4 *)(*(s32 *)(s1 + 0x20) + 0x18);
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x2C) = *(s16 *)(*(s32 *)(s1 + 0x20) + 0x2C) | 0x20;
    *(s32 *)(*(s32 *)(s0 + 0x20) + 0x4) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x4);
}


/* banked twin ov_SC03_090:func_80184C74 formulation, file-scope decls */
typedef struct {
    u8 b[8];
} Blk8_80182B08;

extern Blk8_80182B08 D_801BED04;
extern void func_8012CC64(s32 a0, s32 a1);
extern void func_8012E8A8(u8 *a0);
extern void func_8018302C(s32 arg0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);

void func_80182B08(s32 a0)
{
    extern void func_80182CEC();
    extern void func_80182FCC(s32 param_1);
    Blk8_80182B08 buffer;
    s32 v0;
    s32 s1;

    buffer = D_801BED04;
    v0 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&buffer);

    if (v0 & 0x2000) {
        *(s16 *)(a0 + 2) = 3;
        func_8012E8A8((u8 *)a0);
        func_8018302C(*(s32 *)(a0 + 0xCC));
        s1 = 0;
        func_8012C588(0x1AA, a0);
        do {
            func_8012C588(0x1B0, a0);
        } while (++s1 < 8);
        func_8002D4C8(0x705, 0);
    } else {
        if (func_8012BEE8(a0) != 0) {
            *(s16 *)(a0 + 2) = 3;
            func_8012E8A8((u8 *)a0);
            func_8018302C(*(s32 *)(a0 + 0xCC));
        } else {
            func_80182CEC(a0);
            func_80182FCC(a0);
        }
    }
}


extern void func_80182CB4(s32 param_1);
extern void func_8012E88C(u8 *a0);
extern void func_8018300C(s32 arg0);
extern void func_8012B2CC(s32 a0);
extern void func_80182FCC(s32 param_1);

void func_80182C08(void *a0) {
    if (*(s16 *)((s32)a0 + 0xFE) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        func_80182CB4((s32)a0);
    } else if (*(s16 *)((s32)a0 + 0xFC) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012E88C((u8 *)a0);
        func_8018300C(*(s32 *)((s32)a0 + 0xCC));
        *(s32 *)((s32)a0 + 0x4) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4);
        *(s32 *)((s32)a0 + 0x8) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x8);
        *(s32 *)((s32)a0 + 0xC) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC);
        func_8012B2CC((s32)a0);
        func_80182FCC((s32)a0);
    }
}



extern void func_80016714(void *a0, s32 a1);
    extern void func_8012C218(void *a0);
    void func_80182CB4(s32 param_1) {
        s32 iVar1;
        iVar1 = *(s32 *)(param_1 + 0xcc);
        ((void (*)(s32 *, s32))func_80016714)((s32 *)iVar1, 0x38);
        ((void (*)(s32))func_8012C218)(param_1);
    }


extern s32 D_80199F10;
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);

    void func_80182CEC(arg0)
s32 arg0;
{
        ((void (*)(void *, s32, s32, s32))func_8012D5E4)((void *)arg0, &D_80199F10, (s32)&D_80199F10 + 0x8, 0x5);
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

/* func_80182D18 @ ov_SC03_089 (subseg ov_SC03_089_jr_8017CA80) — 173 ins.
 *
 * Template: engine_core.h DEFINE_func_8012EC04() — same RotMatrix-from-packed-word
 * decode + the same GTE column/translation tail, but composing into a SECOND matrix
 * and then feeding ((void (*)(s32, s32, s32))func_8012F14C)(SetRotMatrix/SetTransMatrix/RotTransSV).
 *
 * Two load-bearing details (do not "clean up" when templating to siblings):
 *  1) `LV_801851A8_80182D18 unused;` — the frame is 0x80, and out(8)+buf(8)+m1(32)+m2(32)
 *     only accounts for 0x50 of the 0x60 local area. gcc-2.7.2 keeps the slot of an
 *     unreferenced BLKmode local, so the dead 16-byte local is what makes sp == 0x80.
 *  2) `mk = 0x80000000;` BEFORE the if. gcc-2.7.2's cse is basic-block-local, so a
 *     constant parked in a named local one block earlier is NOT propagated into the
 *     arm: the pseudo stays live across the branch, which (a) flips the then-arm's
 *     local-alloc to ptr=$v1 / val=$v0 (matching the target) and (b) leaves the
 *     `lui $a0,0x8000` before the bgez where reorg's backward scan pulls it into the
 *     branch delay slot. Writing the literal inline gives ptr=$v0 / val=$v1 and a
 *     stolen `lui $v1,0x7fff` in the slot — 7 wrong instructions. Pin-free.
 */

typedef struct { short m[3][3]; long t[3]; } MTX_801851A8_80182D18;
typedef struct { short vx, vy, vz, pad; } SV_801851A8_80182D18;
typedef struct { long vx, vy, vz, pad; } LV_801851A8_80182D18;
typedef struct { u8 d[8]; } __attribute__((packed, aligned(1))) B8_801851A8_80182D18;

extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_80182D18(s32 param_1)
{

    extern SV_801851A8_80182D18 D_80199F20;
    SV_801851A8_80182D18 out;
    SV_801851A8_80182D18 buf;
    MTX_801851A8_80182D18 m1;
    MTX_801851A8_80182D18 m2;
    LV_801851A8_80182D18 unused;
    u32 w;
    s32 M;
    s32 c;
    s32 dst;
    s32 dp;
    u32 mk;
    s32 p;
    s32 mp;

    if (*(s32 *)(param_1 + 0xCC) != 0) {
        p = (s32)(*(u32 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x20) & 0xfeffffff);
        mp = (s32)&m1;
        buf.vx = *(s16 *)(p + 6);
        w = *(u32 *)p;
        buf.vy = (s16)(*(u8 *)(p + 1) | ((w & 0xf) << 8));
        buf.vz = (s16)(((w >> 0x10) & 0xff) | ((w & 0xf0) << 4));
        func_80049CAC((s32)&buf, mp);
        m1.t[0] = *(s8 *)(p + 3);
        m1.t[1] = *(s8 *)(p + 4);
        m1.t[2] = *(s8 *)(p + 5);

        /* gte_SetRotMatrix(M) */
        M = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
        __asm__ __volatile__(
            "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
            "ctc2 $12, $0\n" "ctc2 $13, $1\n"
            "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
            "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
            : : "r"(M) : "$12", "$13", "$14", "memory");

        /* column 0 */
        __asm__ __volatile__(
            "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
            "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
            "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
            : : "r"(mp) : "$12", "$13", "$14", "memory");
        dp = (s32)&m2;
        __asm__ __volatile__(
            "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
            "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
            : : "r"(dp) : "$12", "$13", "$14", "memory");

        /* column 1 */
        c = (s32)&m1 + 2;
        __asm__ __volatile__(
            "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
            "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
            "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
            : : "r"(c) : "$12", "$13", "$14", "memory");
        c = (s32)&m2 + 2;
        __asm__ __volatile__(
            "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
            "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
            : : "r"(c) : "$12", "$13", "$14", "memory");

        /* column 2 */
        c = (s32)&m1 + 4;
        __asm__ __volatile__(
            "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
            "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
            "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
            : : "r"(c) : "$12", "$13", "$14", "memory");
        c = (s32)&m2 + 4;
        __asm__ __volatile__(
            "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
            "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
            : : "r"(c) : "$12", "$13", "$14", "memory");

        /* gte_SetTransMatrix(M) */
        M = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
        __asm__ __volatile__(
            "lw $12, 20(%0)\n" "lw $13, 24(%0)\n"
            "ctc2 $12, $5\n" "lw $14, 28(%0)\n"
            "ctc2 $13, $6\n" "ctc2 $14, $7\n"
            : : "r"(M) : "$12", "$13", "$14", "memory");

        /* gte_ldlv0(m1.t) ; gte_rt() ; gte_stlvnl(m2.t) */
        c = (s32)&m1 + 0x14;
        __asm__ __volatile__(
            "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n"
            "sll $13, $13, 16\n" "or $12, $12, $13\n"
            "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n"
            "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n"
            : : "r"(c) : "$12", "$13", "memory");
        c = (s32)&m2 + 0x14;
        __asm__ __volatile__(
            "swc2 $25, 0(%0)\n" "swc2 $26, 4(%0)\n" "swc2 $27, 8(%0)\n"
            : : "r"(c) : "memory");

        ((void (*)(s32, s32, s32))func_8012F14C)(dp, (s32)&D_80199F20, (s32)&out);

        dst = *(s32 *)(param_1 + 0xCC);
        *(B8_801851A8_80182D18 *)(dst + 8) = *(B8_801851A8_80182D18 *)&out;

        mk = 0x80000000;
        if (*(s32 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 4) < 0) {
            *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) | mk;
        } else {
            *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) & 0x7FFFFFFF;
        }
    }
}


void func_80182FCC(s32 arg0) {
    s32 v1;
    v1 = *(s32 *)(arg0 + 0xCC);
    if (v1 != 0) {
        *(u16 *)(v1 + 8) = *(u16 *)(arg0 + 6);
        *(u16 *)(v1 + 0xA) = *(u16 *)(arg0 + 0xA) - 0x19;
        *(u16 *)(v1 + 0xC) = *(u16 *)(arg0 + 0xE);
    }
}


void func_8018300C(s32 arg0) {
        if (arg0 != 0) {
            *(s32 *)(arg0 + 0x4) &= 0x7FFFFFFF;
        }
    }


void func_8018302C(s32 arg0) {
        if (arg0 != 0) {
            M2C_FIELD(arg0, s32 *, 0x4) |= 0x80000000;
        }
    }


extern s32 func_8004787C(s32 a0);
extern s16 D_80199ED4[];
extern u8 D_80199E88;
extern u8 D_80199E89;
extern u8 D_80199E8A;

void func_8018304C(void *a0) {
    s32 ent = (s32)a0;
    s32 t;
    register u8 *p __asm__("$4");
    register s32 i __asm__("$5");

    t = (func_8004787C((*(s32 *)(ent + 0x1C) << 6) & 0x7C0) * 100 >> 12) + 100;
    i = 0;
    p = (u8 *)D_80199ED4;
    do {
        i++;
        p[2] = t;
        p[1] = t;
        p[0] = t;
        p += 0x10;
    } while (i < 3);
    D_80199E8A = t;
    D_80199E89 = t;
    D_80199E88 = t;
    *(s32 *)(ent + 0x1C) += 1;
}



extern void (*D_8019A070[])(void);

void func_801830F0(void *a0) {
    D_8019A070[*(u16 *)((s32)a0 + 0x2)]();
}




void func_8018312C(s32 a0)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001CA1C(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, s32 a1);
    extern u8 D_80199F28[];
    extern u8 D_80199FE8[];

    s32 unused[2];              /* dead 8-byte local — frame 0x28 */
    s32 s0;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        ((void (*)(s32))func_8012CAE4)((void *)a0);
        return;
    }

    *(s32 *)(a0 + 0x20) = s0;
    func_8001CA1C(s0, (s32)D_80199F28);

    *(u16 *)(s0 + 0x18) = 0x2000;
    *(u16 *)(s0 + 0x1A) = 1;
    *(u16 *)(s0 + 0x2E) = 0xC004;
    *(u32 *)(s0 + 4) |= 0x50000000;
    *(u16 *)(s0 + 0x2C) |= 0x10;

    *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 0x19;
    func_8012A828(a0, (s32)D_80199FE8);

    *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
}


extern s32  func_8012BEE8(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8012C218(void *a0);
extern void func_80183318(s32 a0);

void func_801831E8(s32 a0) {
    s32 ent = a0;
    s32 state = *(u16 *)(ent + 0x34);
    register s32 sub __asm__("$3");
    register s32 t __asm__("$2");
    s32 cnt;

    switch (state) {
    case 0:
        t = func_8004787C(*(s32 *)(ent + 0x1C) << 6);
        *(s16 *)(*(s32 *)(ent + 0x20) + 0x18) = t * 7;
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = t << 1;
        cnt = *(s32 *)(ent + 0x1C) + 1;
        *(s32 *)(ent + 0x1C) = cnt;
        if (cnt < 0x10) {
            break;
        }
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = 0x7000;
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = 0x2000;
        *(s32 *)(ent + 0x1C) = 0x40;
        *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        break;
    case 1:
        if (func_8012BEE8(ent) != 0) {
            *(s32 *)(ent + 0x1C) = 0x10;
            *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        }
        break;
    case 2:
        t = func_8004787C(*(s32 *)(ent + 0x1C) << 6);
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = t << 1;
        cnt = *(s32 *)(ent + 0x1C) - 1;
        *(s32 *)(ent + 0x1C) = cnt;
        if (cnt == 0) {
            func_8012C218((void *)ent);
            return;
        }
        break;
    }

    func_80183318(ent);
}


typedef struct { s16 a, b, c; } SV3x_80184B30;
typedef struct { s32 vx, vy, vz; } V32_801875E4;
typedef struct { s16 a, b, c, d; } SV4x_80184B30;
typedef struct { short vx, vy, vz, pad; } SV_801851A8_801839C4;



extern void func_80183318(s32 a0);

s32 func_80185484_body(s32 a0) __asm__("func_80183318");

s32 func_80185484_body(s32 a0) {
    extern void func_8012BE54(s32 a0);
    extern u16 D_80126B62;
    extern u8 D_8019A078[];

    register s32 ent __asm__("$17");   /* $s1 */
    s32 p;
    s32 h;
    s32 h2;
    s32 ret;
    s32 s0;
    s32 r;
    s32 v;
    s32 g;
    s32 d;
    u16 arr[3];

    ent = a0;
    p = *(s32 *)(ent + 0x20);
    h = *(s16 *)(p + 0x18);
    __asm__("" : "=r"(h) : "0"(h));
    ret = ((s32 (*)(s32))func_8012BE54)(ent);
    s0 = h >> 8;
    if (ret > s0 * s0) {
        return 0;
    }
    v = *(s16 *)(ent + 0xA);
    h2 = *(s16 *)(*(s32 *)(ent + 0x20) + 0x1A);
    __asm__ __volatile__("" : "=r"(h2) : "0"(h2));
    g = *(s16 *)&D_80126B62;
    r = h2 >> 6;
    d = v - g;
    if (d >= 0 ? r < d : r < g - v) {
        return 0;
    }
    a0 = 1;
    arr[0] = *(u16 *)(ent + 0x6);
    arr[1] = *(u16 *)(ent + 0xA);
    arr[2] = *(u16 *)(ent + 0xE);
    func_8012F568(1, 0x4201, 0, 0x1C, (s32)arr, (s32)D_8019A078);
}



extern void (*D_8019A080[])(void);

void func_801833F0(void *a0) {
    D_8019A080[*(u16 *)((s32)a0 + 0x2)]();
}




/* Sibling-first template: src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c:4778 func_80184294
 * (banked/matched — same family, same struct-offset chain: func_8012C1B8 -> obj,
 * store obj to param_1+0x20, func_8001C214(obj,0), raw=rand() truncated to s16,
 * r=(s32)raw, flags|=0x10, v=r%384+0x400 written to obj+0x1c/0x1a/0x18, sgn=+-1
 * chosen from raw&1, obj+0x10 = sgn*(r%128)-0x300, obj+0x12 = r%4096, tail calls
 * func_8012B2CC/func_8012B178, then a repeated rand()%N +- C spread into a p[]
 * array at param_1+0xDC with p[1]/p[5]/p[9]/p[13] zeroed). This instance differs
 * only in: an extra obj+0x14=0 store, TWO tail helper calls (func_8012B2CC AND
 * func_8012B23C) instead of one, mod-8 (not mod-12) spread with +-0x10 (not
 * +-0x18), and a longer tail (0xFC/0xFD/0xFE bytes + 0x100 flag word).
 *
 * Declarations conformed to this TU's own canonical externs (grepped in one pass,
 * D2): func_8012C1B8/func_8012CAE4/func_8012B23C/func_8012B2CC at
 * src/ov_SC03_089/ov_SC03_089_jr_8017CA80.c:5114-5115,4924,2523 and
 * func_8001C214 at :5425. func_8012B178 is not yet declared in this TU; its
 * canonical extern form is copied verbatim from sibling TUs (e.g.
 * src/ov_SC03_099/ov_SC03_099_jr_80135A4C.c:273).
 *
 * Per-field +-0x10 sign derived directly from the target .s (bnez-taken/not-taken
 * addiu operands at each block, asm/ov_SC03_089/nonmatchings/.../func_8018342C.s):
 *   0xDC:-0x10  0xE0:-0x10  0xE4:+0x10  0xE8:-0x10  0xEC:-0x10  0xF0:+0x10
 *   0xF4:+0x10  0xF8:+0x10
 * — the same alternating pattern (-,-,+,-,-,+,+,+) as the sibling's mod-12/0x18
 * block, just re-keyed to mod-8/0x10.
 */

extern s32 rand(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(void *a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_8018342C(s32 param_1) {

    s32 unused[2]; /* dead 8-byte local — frame padding (cookbook idiom 6) */
    s32 obj;
    s16 raw;
    s32 r;
    s32 sgn;
    s32 v;
    s32 q;
    s32 w;
    /* The `register ... __asm__("$4")` pin on the tail's +2-field counter is
     * load-bearing (matching-cookbook idiom 9 / L-lever family): unpinned, gcc
     * puts the 0x50000000 OR-mask constant in $a0 and the field value in $v1
     * (register-swapped vs. the target) and schedules the field's `lhu` right
     * before the `or` instead of hoisting it ahead of the 0xFC/FD/FE `sb`
     * stores. Pinning $4/$a0 to this value AND folding the `+1` into the same
     * statement as the load (`cnt = *(u16*)(param_1+2) + 1;`, store separate)
     * reproduces both the register choice and the exact schedule position. */
    register s32 cnt __asm__("$4");

    obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj == 0) {
        func_8012CAE4((void *)param_1);
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
    *(u16 *)(obj + 0x14) = 0;

    *(u16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x19;
    func_8012B2CC(param_1);
    func_8012B23C((void *)param_1);
    func_8012B178(param_1, -0xC0000 - ((r % 8) << 16));

    *(s32 *)(param_1 + 0x1C) = 0x5A;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xDC) = w;
    *(s16 *)(param_1 + 0xDE) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xE0) = w;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xE4) = w;
    *(s16 *)(param_1 + 0xE6) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xE8) = w;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xEC) = w;
    *(s16 *)(param_1 + 0xEE) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xF0) = w;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xF4) = w;
    *(s16 *)(param_1 + 0xF6) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xF8) = w;

    cnt = *(u16 *)(param_1 + 2) + 1;
    *(u8 *)(param_1 + 0xFC) = 0x80;
    *(u8 *)(param_1 + 0xFD) = 0x80;
    *(u8 *)(param_1 + 0xFE) = 0x80;
    *(u32 *)(param_1 + 0x100) = *(u32 *)(param_1 + 0x100) | 0x50000000;
    *(u16 *)(param_1 + 2) = cnt;
}


#include "common.h"

extern void func_8012CBCC(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_80017274(s32 a0, s32 a1);

void func_801837C8(s32 param_1) {
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + 0x40;

    if (((s32 (*)(s32))func_8012CBCC)(param_1) != 0 || func_8012BEE8(param_1) != 0) {
        func_8012C218((void *)param_1);
    } else {
        func_80017274(param_1 + 0xDC, *(s32 *)(param_1 + 0x20) + 0x34);
    }
}


typedef struct {
    s32 a;      /* 0x00 -> D_801DA750 */
    s32 b;      /* 0x04 -> D_801DA754 */
} Pair8_8017DDC4_80182244_80180040_8018383C;

extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80029178(s32 arg);
extern void func_80183C30(void *arg0);
extern s32 func_8012C194(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_80185278(void);
extern s32 func_8012AD50(void *a0);

/* 4-byte, align-4 unaligned block: forces lwl/lwr + swl/swr (cookbook §48-C2 /
 * matches the sibling idiom at ov_SC02_005:func_8018CE04). */
/* 4-byte, align-4 unaligned block: forces lwl/lwr + swl/swr (cookbook §48-C2 /
 * matches the sibling idiom at ov_SC02_005:func_8018CE04). */
typedef struct { u8 b[4]; } Blk4_80181EDC_8018383C;

/* §183 TYPE-adopted-sibling: func_80182060 / func_80182688 land in this same TU
 * and spell D_801C00B0 as a plain `u8` (byte lbu/sb arithmetic).  This function
 * wants the 4-byte block view, so it adopts the raw `u8` spelling on the
 * DECLARATION and takes the block view at the USE SITE — which it was already
 * doing via `(s32)&D_801C00B0` + `*(Blk4_80181EDC_8018383C *)s0`, so this is byte-free. */

void func_8018383C(s32 s1)
{

    extern u8 D_8019C9AC;
    extern u8 D_8019C9E0;
    extern s32 D_8019CA20[];
    extern u8 D_801C00B0;
    extern Blk4_80181EDC_8018383C D_801C00B4;
    extern Blk4_80181EDC_8018383C D_801BED0C;
    extern Blk4_80181EDC_8018383C D_801BED10;
    s32 v1;
    s32 a1ptr;
    s32 s2;

    if (func_8012C354(s1, (s32)&D_8019C9AC) != 0) {
        register s32 t0 __asm__("$2");
        register s32 t1 __asm__("$3");

        t0 = 1;
        *(u8 *)(s1 + 0xC0) = t0;
        t0 = (s32)&D_8019C9E0;
        *(s32 *)(s1 + 0xBC) = t0;
        t0 = *(s32 *)(s1 + 0xC4);
        t1 = 0x14;
        *(u8 *)(s1 + 0x75) = t1;
        v1 = *(s16 *)(s1 + 0x70);
        *(s32 *)(s1 + 0xB4) = 0;
        *(u8 *)(s1 + 0xC1) = 0;
        t0 = t0 | 2;
        *(s32 *)(s1 + 0xC4) = t0;
        t0 = *(u16 *)(s1 + 0x72);
        t0 = t0 | 0x1000;
        *(u16 *)(s1 + 0x72) = t0;

        if ((func_80029178(D_8019CA20[v1]) & 0xFF) != 0) {
            a1ptr = *(s32 *)(s1 + 0x20);
            *(u32 *)(a1ptr + 4) |= 0x80000000;
            *(s16 *)(s1 + 0xAE) = -1;
            func_80183C30((void *)s1);
            *(u16 *)(s1 + 0x34) += 1;
        } else {
            *(s16 *)(s1 + 0xAE) = -4;
            s2 = func_8012C194();
            *(s32 *)(s1 + 0xCC) = s2;
            if (s2 != 0) {
                s32 s0 = (s32)&D_801C00B0;
                func_8001CD9C(s2, (void *)s0);
                func_800233CC((void *)s0, 0x80);
                *(Blk4_80181EDC_8018383C *)s0 = *(Blk4_80181EDC_8018383C *)&D_801BED0C;
                *(Blk4_80181EDC_8018383C *)&D_801C00B4 = *(Blk4_80181EDC_8018383C *)&D_801BED10;
                *(s16 *)(s2 + 0x18) = 0x800;
                *(s16 *)(s2 + 0x1A) = 0x800;
                *(u32 *)(s2 + 4) |= 0x50000000;
            }
            func_80185278();
            func_8012AD50((void *)s1);
        }
    }
}


extern s16 D_8019CA30[];
extern s32 func_8012BEE8(s32 a0);
extern u8 D_801C00B0;
extern u8 D_801C00B1;
extern u8 D_801C00B2;
extern void func_80183AF4(void *a0);
extern void func_80183B90(void *a0);
extern void func_80183D54(s32 a0);

void func_801839C0(void *a0)
{
    void *s0 = a0;
    void *v0;
    s16 t18;
    u16 t1a;
    s16 tfc;
    s16 val;
    u16 nfc;
    u8 c1, c2, c0, nc0;
    u8 *p;

    v0 = *(void **)((u8 *)s0 + 0xCC);
    if (v0 != NULL) {
        s16 e18, p18;
        
        e18 = *(s16 *)((u8 *)v0 + 0x18);
        if (e18 < 0x1C00) {
            t18 = e18 + 0x200;
            *(s16 *)((u8 *)v0 + 0x18) = t18;
            t1a = *(u16 *)((u8 *)v0 + 0x1A);
            t1a = t1a + 0x200;
            *(u16 *)((u8 *)v0 + 0x1A) = t1a;
        }
        p18 = *(s16 *)((u8 *)v0 + 0x18);
        if (p18 >= 0x1001) {
            tfc = *(s16 *)((u8 *)s0 + 0xFC);
            val = D_8019CA30[tfc];
            if (val >= 0) {
                func_80183AF4((void *)(s32)val);
                nfc = *(u16 *)((u8 *)s0 + 0xFC);
                nfc = nfc + 1;
                *(u16 *)((u8 *)s0 + 0xFC) = nfc;
            }
        }
    }

    p = &D_801C00B0;
    
    __asm__("" : "=r"(p) : "0"(p));
    c0 = *p;
    if (c0 < 0xFF) {
        nc0 = c0 + 0x10;
        *p = nc0;
        c1 = D_801C00B1;
        c2 = D_801C00B2;
        c1 = c1 + 0x10;
        c2 = c2 + 0x10;
        D_801C00B1 = c1;
        D_801C00B2 = c2;
        if (nc0 == 0) {
            *p = 0xFF;
            D_801C00B1 = 0xFF;
            D_801C00B2 = 0xFF;
        }
    }

    func_80183D54((s32)s0);
    if (func_8012BEE8((s32)s0) != 0) {
        func_80183B90(s0);
    }
}


typedef struct { u8 b[4]; } Blk4_80183AF4;

extern s32 rand(void);
extern void func_80185400(void *a0, void *a1, void *a2);

void func_80183AF4(void *a0) {
    extern Blk4_80183AF4 D_801BED14;
    extern Blk4_80183AF4 D_801BED18;
    Blk4_80183AF4 pos;   /* sp+0x10 */
    Blk4_80183AF4 vel;   /* sp+0x18 */
    struct { u16 x; u16 y; u16 z; u16 w; } prm; /* sp+0x20 */

    pos = D_801BED14;
    vel = D_801BED18;

    *(s8 *)((u8 *)&pos + 2) = (rand() & 0x3f) - 0x80;

    prm.x = 0x100;
    prm.z = 0x80;
    prm.y = (u16)(s32)a0;
    prm.w = 1;

    func_80185400(&prm, &pos, &vel);
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_80183B90(void *a0) {
    (*(s32 *)(*(s32 **)((char *)a0 + 0x20) + 1)) |= 0x80000000;
    *(s16 *)((char *)a0 + 0xFC) = 0;
    ((void (*)(s32, s32))func_8012AD44)(a0, 3);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80183BCC(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x20;
        ((void (*)(s32, s32))func_8012AD44)((s32)a0, 4);
    }


extern void func_80178B18(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_8019C9F8;

void func_80183BF4(void * arg0) {
    func_80178B18((s32)arg0, (s32)&D_8019C9F8);
    ((void (*)(s32, s32))func_8012AD44)(arg0, 5);
}


extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80183C30(void *arg0) {
        ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 0x6);
    }



// @class: struct
// @stuck: none — MATCH (fn-ptr table %lo-fold via extern array of code ptrs)

extern code_fn D_8019CA44[];

extern s32 func_80183D98();

void func_80183C50(int param_1)
{
    D_8019CA44[*(unsigned short *)(param_1 + 2)]();
    ((void (*)(int))func_80183D98)(param_1);
    return;
}



extern void func_80185278(void);
extern void func_8018533C(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012B2CC(s32 a0);
extern void func_8018536C(s32 a0);
extern void func_80178B18(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80183CA0(s32 a0) {
    extern u8 D_801C00B0;
    extern Blk4_80181EDC_8018383C D_801BED0C;
    extern s32 D_8019C9F0;
    s32 sp0;
    s32 s0 = a0;

    *(u8 *)(s0 + 0xC1) = 0;
    *(u16 *)(s0 + 0x5E) = 0;
    *(u16 *)(s0 + 0x5C) = 0x800;
    *(Blk4_80181EDC_8018383C *)&D_801C00B0 = *(Blk4_80181EDC_8018383C *)&D_801BED0C;
    func_80185278();
    func_8018533C((s32)&sp0, 0x1000, 0);
    func_8012B2CC(s0);
    func_8018536C(s0 + 4);
    *(u16 *)(s0 + 0xFC) = 0;
    *(s32 *)(s0 + 0x1C) = 0x40;
    func_80178B18(s0, (s32)&D_8019C9F0);
    ((void (*)(s32, s32))func_8012AD44)(s0, 2);
    func_8002D4C8(0x700, 0);
}


extern void func_8012B2CC(s32 a0);
extern void func_8018536C(s32 a0);
extern void func_801853E4(s32 arg0);
extern void func_801855B4(void);

void func_80183D54(s32 a0) {
    func_801853E4(0x8);
    func_8012B2CC(a0);
    func_8018536C(a0 + 0x4);
    func_801855B4();
}


s32 func_80183D98(s32 a0)
{
    s32 v1 = *(s32*)(a0 + 0xCC);
    if (v1) {
        *(u16*)(v1 + 8) = *(u16*)(a0 + 6);
        *(u16*)(v1 + 0xA) = *(u16*)(a0 + 0xA);
        *(u16*)(v1 + 0xC) = *(u16*)(a0 + 0xE);
        func_801330E0((void*)(v1 + 8), (s16*)(v1 + 8), -256);
    }
}


typedef struct {
    u16 x, y, z;
    s16 w;
} Rec8_8017DDC4_8018034C_80183DEC;
typedef struct {
    s32 a;      /* 0x00 -> D_801DA750 */
    s32 b;      /* 0x04 -> D_801DA754 */
} Pair8_8017DDC4_80182244_80180040_80183DEC;

/* local mirrors of the TU's shared engine_types.h structs (Blk8_80183DEC @497, Blk32_8018AA98_80183D30_80183DEC
 * @1413) — match_one compiles this draft standalone without the shared header chain, so the
 * types are re-declared here verbatim rather than pulled through engine_core.h. */
/* 20-byte spawn-message record built at sp+0x10: x,y,z / type / sub-id / pad / flag / pad,
 * then a trailing s32 "extra" field copied out of *(a0+0xDC). §193-I: this aggregate's frame
 * slot rounds up to 24 (ceil(20,8)), which is exactly the 4-byte gap between it and `vec`
 * below in the target's stack layout (sp+0x24-0x27 unused). */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 type;
    s16 sub;
    s16 pad1;
    s16 flag;
    s16 pad2;
    s32 extra;
} Msg_8018248C_80183DEC;

extern void RotMatrixY(s32 a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_8012C51C(void *a0, s32 a1);

void func_80183DEC(s32 a0, s32 a1) {
    /* §183 TYPE-shadowed-block-scope.  Blk8_80183DEC / Blk32_8018AA98_80183D30_80183DEC come from
     * the TU's own engine_types.h (lines 497 / 1413) — the draft's file-scope
     * mirrors were dropped to avoid DUPLICATE-TYPEDEF.  D_800AE620 has NO
     * file-scope decl in this TU: it is already declared twice, block-scoped and
     * with two different types (Blk32_8018AA98_80183D30_80183DEC @5594, s32 @6053).  This
     * body follows that existing TU precedent verbatim. */
    typedef struct { u8 b[8]; } Blk8_80183DEC;
    typedef struct { s32 w[8]; } Blk32_8018AA98_80183D30_80183DEC;
    extern Blk8_80183DEC D_801BED1C;
    extern s32 D_800AE620;
    Msg_8018248C_80183DEC msg;          /* sp+0x10 (24-byte stride, §193-I) */
    Blk8_80183DEC vec;                 /* sp+0x28 */
    Blk32_8018AA98_80183D30_80183DEC m; /* sp+0x30 */

    vec = D_801BED1C;
    m = *(Blk32_8018AA98_80183D30_80183DEC *)&D_800AE620;

    RotMatrixY(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), &m);
    ApplyMatrixSV(&m, &vec, &vec);

    if (a0 != 0 && *(u16 *)a0 != 0) {
        msg.x = *(u16 *)(a0 + 0x6) + *(u16 *)((u8 *)&vec + 0);
        msg.y = *(u16 *)(a0 + 0xA) + *(u16 *)((u8 *)&vec + 2);
        msg.z = *(u16 *)(a0 + 0xE) + *(u16 *)((u8 *)&vec + 4);
    } else {
        msg.z = 0;
        msg.y = 0;
        msg.x = 0;
    }

    msg.type = 0x1E1;
    msg.sub = (s16)a1;
    msg.pad1 = 0;
    msg.pad2 = 0;
    msg.extra = *(s32 *)(a0 + 0xDC);
    msg.flag = 0x7FFF;

    func_8012C51C(&msg, a0);
}



extern void (*D_8019CA70[])(void);

void func_80183F4C(void *a0) {
    D_8019CA70[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 D_801C00B0;
extern u8 D_801C00B1;
extern u8 D_801C00B2;

void func_80183F88(s32 *a0)
{
    s32 t;
    u8 v;

    t = a0[7] + 1;
    a0[7] = t;
    if (t & 0x10) {
        v = ((t & 0xF) >> 1) + 9;
    } else {
        v = 0x10 - ((t & 0xF) >> 1);
    }
    D_801C00B2 = v * 8;
    D_801C00B1 = v * 8;
    D_801C00B0 = v * 8;
}


extern u8 D_801C00B0;
extern u8 D_801C00B1;
extern u8 D_801C00B2;
extern void func_80185568(s32 a0, s32 a1);
extern void func_80183DEC(s32 a0, s32 a1);
extern void func_80183BCC(void *a0);
extern void func_80183D54(s32 a0);

void func_80183FE8(void *arg0) {
    s16 v;
    void *s1;
    u8 *p;

    v = *(s16 *)((u8 *)arg0 + 0xFC);
    s1 = *(void **)((u8 *)arg0 + 0xCC);

    if (v < 0x10) {
        func_80185568(v, 1);
        *(u16 *)((u8 *)arg0 + 0xFC) = *(u16 *)((u8 *)arg0 + 0xFC) + 1;
    }

    if (*(s16 *)((u8 *)arg0 + 0xFC) >= 9) {
        if (s1 != NULL) {
            s16 h = *(s16 *)((u8 *)s1 + 0x18);
            if (h > 0) {
                *(s16 *)((u8 *)s1 + 0x18) = h - 0x100;
                *(u16 *)((u8 *)s1 + 0x1A) = *(u16 *)((u8 *)s1 + 0x1A) - 0x100;
            }
        }

        p = &D_801C00B0;
        if (*p >= 17) {
            *p -= 0x10;
            D_801C00B1 -= 0x10;
            D_801C00B2 -= 0x10;
        } else {
            *(s16 *)((u8 *)s1 + 0x0) = 0;
            *(s32 *)((u8 *)arg0 + 0xCC) = 0;
            func_80183DEC((s32)arg0, 0x4000);
            func_80183BCC(arg0);
        }
    }

    func_80183D54((s32)arg0);
}


extern s32 D_8019CA20[];
extern s32 func_80029178(s32 arg);
extern s32 func_8012BEE8(s32 a0);
extern void func_80029124(s32, s32);
extern void func_80029514(s32);
extern void func_80178D18(void);
extern void func_80183BF4(void *arg0);
extern void func_80183C30(void *arg0);

void func_801840F4(void *a0) {
    s32 i;
    s32 flag;
    s16 idx;

    if (func_8012BEE8((s32)a0) == 0) {
        return;
    }

    ((void (*)(s32))func_80178D18)((s32)a0);

    flag = 0;
    for (i = 0; i < 4; i++) {
        flag |= func_80029178(D_8019CA20[i]) & 0xFF;
    }

    if (flag == 0) {
        func_80183BF4(a0);
    } else {
        func_80183C30(a0);
    }
    flag = 1;

    idx = *(s16 *)((s32)a0 + 0x70);
    func_80029124(D_8019CA20[idx], 1);

    for (i = 0; i < 4; i++) {
        if ((func_80029178(D_8019CA20[i]) & 0xFF) == 0) {
            flag = 0;
        }
    }

    if (flag != 0) {
        func_80029514(0x172);
    }
}


extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80183C30(void*);
void func_80184200(u8 * a0)
{
    if (((s32 (*)(s32 *))func_80178970)(a0)) {
        ((void (*)(u8 *))func_80178D18)((u8 *)a0);
        ((s32 (*)(s32))func_80183C30)((s32)a0);
    }
}


void func_80184240(void *a0) {
    if (*(u16 *)((s32)a0 + 0x34) != 0) {
        func_80183DEC(a0, 0);
        *(u16 *)((s32)a0 + 0x34) = *(u16 *)((s32)a0 + 0x34) - 1;
    }
}


void func_8018428C(void *a0)
{
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C2C4(s32 a0);
    extern s16 D_8019CA60;
    extern s32 D_8019CA14;
    extern s32 func_8012AD50(void *a0);

    register void *s0 __asm__("$16") = a0;
    s32 v0 = ((s32 (*)(void))func_8012C1B8)();

    *(s32 *)((u8 *)s0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4((void *)s0);
        return;
    }

    func_8001C2C4(v0);
    *(s32 *)((u8 *)s0 + 0x58) = (s32)&D_8019CA60 | 0x40000000;
    *(s16 *)((u8 *)s0 + 0x5C) = 0x800;
    *(u16 *)((u8 *)s0 + 0x72) |= 0x1000;
    *(s32 *)&D_8019CA14 = *(s32 *)((u8 *)s0 + 0xDC);
    func_8012AD50((void *)s0);
}


void func_80184314(void) {
}


extern s32 func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_8001CF00(s32 a0);
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_800291B4(s32 arg);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012AD50(void *a0);

void func_8018431C(void *a0)
{
    extern s32 D_8019CAF4[];
    extern u8 D_8019CAE4[];
    extern u8 D_8019CA7C[];
    extern u8 D_8019CA7E[];
    extern u8 D_801C00F0[];

    s32 s2;
    s32 s1;
    u16 v0;
    s16 v1;
    s16 s0raw;

    s2 = (s32)a0;
    s1 = func_8012C194();
    if (s1 == 0) {
        func_8012CAE4((void *)s2);
        return;
    }

    v0 = *(u16 *)(s2 + 0x72);
    *(s32 *)(s2 + 0x20) = s1;
    v0 |= 0x1000;
    *(u16 *)(s2 + 0x72) = v0;
    v1 = *(s16 *)(s2 + 0x70);
    s0raw = v1;

    if ((v1 & 0x8000) != 0) {
        s32 idx;
        u8 *p;
        u16 b;

        idx = s0raw & 1;
        p = D_8019CAE4 + idx * 8;
        func_8001CB6C((u8 *)s1, D_8019CAF4[idx], *(s16 *)(p + 0), *(s16 *)(p + 2));
        b = *(u16 *)(p + 4);
        *(u16 *)(s1 + 0x10) = 0x400;
        *(u16 *)(s1 + 0x1A) = 0x2000;
        *(u16 *)(s1 + 0x18) = 0x2000;
        *(u8 *)(s1 + 0x27) = b;
    } else {
        register u8 *dptr __asm__("$4");

        func_8001CF00(s1);
        dptr = D_801C00F0;
        *(u16 *)(s1 + 0x28) = 0x300;
        *(u16 *)(s1 + 0x2A) = 0x110;
        *(u8 *)(s1 + 0x27) = 0x78;
        *(u32 *)(s1 + 0x20) = (s32)dptr;
        *(u16 *)(s1 + 0x10) = 0x400;
        *(u16 *)(s1 + 0x1A) = 0x800;
        *(u16 *)(s1 + 0x18) = 0x800;

        if ((*(u16 *)(s2 + 0x70) & 3) == 0) {
            func_800233CC(dptr, 0x80);
        }

        {
            u16 flags = *(u16 *)(s2 + 0x70);
            if ((flags & 1) != 0) {
                *(u16 *)(D_8019CA7C + (flags & 3) * 12) = 0x10;
                *(u16 *)(s1 + 0x14) = 0x400;
                goto shared_tail;
            }
            *(u16 *)(D_8019CA7C + (flags & 3) * 12) = 0x20;
        }

        *(u32 *)(s1 + 4) |= 0x40000000;

        if ((*(u16 *)(s2 + 0x70) & 0x4000) != 0) {
            func_8002D4C8(0x701, 0);
        }
        if ((*(u16 *)(s2 + 0x70) & 0x2000) != 0) {
            s32 ret = func_800291B4(*(s16 *)(s2 + 0xFC));
            if ((ret & 0xFF) == 0) {
                *(u16 *)(s2 + 0x70) |= 0x4000;
            } else {
                *(u16 *)(s2 + 0x70) &= 0xDFFF;
            }
        }
        func_8012C658(0x1E1, (s16)(*(u16 *)(s2 + 0x70) | 1), s2);

    shared_tail:
        *(u16 *)(D_8019CA7E + ((*(u16 *)(s2 + 0x70)) & 3) * 12) = 0x20;
        if ((*(u16 *)(s2 + 0x70) & 0x4000) != 0) {
            *(u16 *)(s1 + 0x1A) = 0;
            *(u16 *)(s1 + 0x18) = 0;
        }
    }

    func_8012AD50((void *)s2);
}


extern void func_80178B18(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_8019CB00;

void func_80184574(s32 *arg0) {
    s32 *ptr = &D_8019CB00;
    *ptr = (*(u16 *)((char *)arg0 + 6)) | ((*(s16 *)((char *)arg0 + 0xE)) << 16);
    func_80178B18((s32)arg0, ((s32)ptr) - 4);
    func_8012AD44(arg0, 2);
}



extern void (*D_8019CB14[])(void);

void func_801845C8(void *a0) {
    D_8019CB14[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80184934(void *a0, void *a1);

void func_80184604(void *a0)
{

    extern u8 D_8019CA78[];
    s32 s0;
    s32 s1;
    u8 *s2;
    u16 v0;
    u32 idx;

    s0 = (s32)a0;
    idx = *(u16 *)(s0 + 0x70);
    s1 = *(s32 *)(s0 + 0x20);
    idx &= 3;
    s2 = D_8019CA78 + idx * 12;

    func_80184934((void *)s1, (void *)s2);

    v0 = *(u16 *)(s0 + 0x70);
    if (v0 & 1) {
        *(u16 *)(s1 + 0x14) -= 4;
        v0 = *(u16 *)(s2 + 4) + 1;
        *(u16 *)(s2 + 4) = v0;
        if ((s16)v0 >= 0x30) {
            *(u16 *)(s2 + 4) = 0x10;
        }
    } else {
        *(u16 *)(s1 + 0x14) += 4;
        v0 = *(u16 *)(s2 + 4) - 1;
        *(u16 *)(s2 + 4) = v0;
        if ((s16)v0 < 0x11) {
            *(u16 *)(s2 + 4) = 0x30;
        }
    }
}


extern void Square0(s32 *a0, s32 *a1);

s32 func_801846F0(void *a0, s32 a1) {
    extern u16 D_80126B62;
    extern u16 D_80126B5E;
    extern u16 D_80126B66;

    s32 in[3];
    s32 out[3];
    s32 d;
    s16 e;
    register s32 ret __asm__("$2");

    in[0] = *(s16 *)((s32)a0 + 6) - *(s16 *)&D_80126B5E;
    in[1] = 0;
    in[2] = *(s16 *)((s32)a0 + 0xE) - *(s16 *)&D_80126B66;
    Square0(in, out);

    d = D_80126B62 - *(u16 *)((s32)a0 + 0xA);
    e = d;
    if ((s16)d < 0) {
        e = -d;
    }

    ret = 0;
    if (out[0] + out[2] < (u16)a1 * (u16)a1) {
        ret = (s16)e < 4;
    }
    return ret;
}


void func_801847B0(void) {

    extern u8 D_801202A0[];
    u8 *p;
    s32 i;

    p = D_801202A0;
    for (i = 0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p == 0x1E1) {
            *(u16 *)(p + 0x70) |= 0x1000;
        }
    }
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80029124(s32, s32);
extern void func_80184574();
extern void func_80184604(void *a0);
extern s32 func_801846F0(void *a0, s32 a1);

void func_80184800(void *a0)
{
    s32 s1;
    s16 flags;
    s16 v0;

    flags = *(s16 *)((s32)a0 + 0x70);
    s1 = *(s32 *)((s32)a0 + 0x20);

    if ((flags & 0x8000) != 0) {
        return;
    }

    if ((flags & 0x2000) != 0) {
        if ((flags & 0x1000) == 0) {
            return;
        }
        *(u16 *)((s32)a0 + 0x70) = flags & 0xDFFF;
        func_8002D4C8(0x701, 0);
    }

    v0 = *(s16 *)(s1 + 0x18);
    if (v0 < 0x800) {
        *(s16 *)(s1 + 0x18) = v0 + 0x40;
        *(u16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0x1A) + 0x40;
    } else if ((*(u16 *)((s32)a0 + 0x70) & 1) == 0) {
        if (func_801846F0(a0, 0x30) != 0) {
            func_80184574(a0);
            func_80029124(0xAE, 0);
            func_80029124(0xAF, 0);
            func_80029124(0xB0, 0);
        }
    }

    func_80184604(a0);
}


extern int func_80178970(void);
extern void func_800D1724(s32 a0);
extern void func_80178D18(void);
extern void func_80184604(void *a0);

void func_801848E8(s32 param) {
    s32 local;

    if (((s32 (*)(s32))func_80178970)(param) != 0) {
        ((void (*)(s32))func_80178D18)(param);
        local = *(s32*)(param + 0xDC);
        func_800D1724(local);
    }
    ((void (*)(s32))func_80184604)(param);
}




#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )
#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
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
#define gte_ldv0(r0) __asm__ volatile (          \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 )"                           \
    :                                            \
    : "r"( r0 ) )
#define gte_ldv3(r0, r1, r2) __asm__ volatile (  \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 0( %1 );"                          \
    "lwc2 $3, 4( %1 );"                          \
    "lwc2 $4, 0( %2 );"                          \
    "lwc2 $5, 4( %2 )"                           \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ) )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_stsxy(r0) __asm__ volatile (         \
    "swc2 $14, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsxy3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 0( %1 );"                         \
    "swc2 $14, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
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

void func_80184934(void *a0, void *a1)
{

    extern void func_8001E094(void);
    extern void func_8001E378(void *a0);
    extern void func_80184D50(void *a0, void *a1, u32 *a2, u32 *a3);
    extern u8 D_800A6610[];
    extern short D_800B9A02;   /* TU-visible spelling (engine_core.h + ov_SC01_000.c col-0);
                                * unsigned access forced at the use — §8d sub-class (b) */

    Vec8_80182FD4 base;
    Vec8_80182FD4 v[3];
    u32  buf[19];
    long flag;
    long otz;
    long flag2;

    Src_80182FD4 *s;
    u32 *ot;
    s32 z;
    s32 i;
    u16 w;

    ot = (u32 *)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    s = *(Src_80182FD4 **)((s32)a0 + 0x20);
    if (s == 0) {
        return;
    }

    if (*(s32 *)((s32)a0 + 0x34) != 0) {
        func_8001E094();
    } else {
        func_8001E378(a0);
    }

    base.vx = *(u16 *)((s32)a0 + 0x2E);
    base.vy = *(u16 *)((s32)a0 + 0x30);
    base.vz = *(u16 *)((s32)a0 + 0x32);

    gte_ldv0(&base);
    gte_rtps();
    gte_stsxy(&buf[0]);
    gte_stflg(&flag);
    gte_stszotz(&otz);

    if (flag & ~0x1000) {
        return;
    }

    w = *(u16 *)((s32)a0 + 0x2C);
    z = otz + 1;
    if ((w & 0xC000) != 0) {
        if ((w & 0xC000) == 0xC000) {
            z -= (w & 0xFFF);
            if (z < 0) {
                z = 0;
            }
        } else {
            z += (w & 0xFFF);
        }
    }
    if (z >= 0x1000) {
        return;
    }

    if (*(s16 *)((s32)a0 + 0x1E) & 0x8000) {
        for (i = 0; i < 12; i += 6) {
            v[0].vx = base.vx + s->pt[i].vx;
            v[0].vy = base.vy + s->pt[i].vy;
            v[0].vz = base.vz;
            v[1].vx = base.vx + s->pt[i + 2].vx;
            v[1].vy = base.vy + s->pt[i + 2].vy;
            v[1].vz = base.vz;
            v[2].vx = base.vx + s->pt[i + 4].vx;
            v[2].vy = base.vy + s->pt[i + 4].vy;
            v[2].vz = base.vz;
            gte_ldv3(&v[0], &v[1], &v[2]);
            gte_rtpt();
            gte_stsxy3(&buf[i + 1], &buf[i + 3], &buf[i + 5]);
        }
        for (i = 1; i < 12; i += 2) {
            v[0].vx = base.vx + s->pt[i].vx;
            v[0].vy = base.vy + s->pt[i].vy;
            v[0].vz = base.vz;
            gte_ldv0(&v[0]);
            gte_rtps();
            gte_stsxy(&buf[i + 1]);
            gte_stflg(&flag2);
            gte_stszotz(&otz);
            buf[13 + (i >> 1)] = otz + 1;
        }
        func_80184D50(a0, a1, &buf[0], ot);
    } else {
        for (i = 0; i < 12; i += 3) {
            v[0].vx = base.vx + s->pt[i].vx;
            v[0].vy = base.vy + s->pt[i].vy;
            v[0].vz = base.vz;
            v[1].vx = base.vx + s->pt[i + 1].vx;
            v[1].vy = base.vy + s->pt[i + 1].vy;
            v[1].vz = base.vz;
            v[2].vx = base.vx + s->pt[i + 2].vx;
            v[2].vy = base.vy + s->pt[i + 2].vy;
            v[2].vz = base.vz;
            gte_ldv3(&v[0], &v[1], &v[2]);
            gte_rtpt();
            gte_stsxy3(&buf[i + 1], &buf[i + 2], &buf[i + 3]);
        }
        func_80184D50(a0, a1, &buf[0], ot + z);
    }
}


#define ADDPRIM_801833F0(o, p)                                                 \
    (((PTag_801833F0 *)(p))->addr = ((PTag_801833F0 *)(o))->addr,              \
     ((PTag_801833F0 *)(o))->addr = (u32)(p))
#define SR3_801833F0(a) (((s32)(*(u16 *)(a) << 16)) >> 19)

void func_80184D50(void *ent, void *spr, u32 *q, u32 *ot)
{
    extern u8 *D_800A5E60;
    register s32 zr __asm__("$0");

    Ft4_801833F0 *poly;
    Drm_801833F0 *dm;
    s32 vtx;
    u32 flags;
    s32 tp, abr, code, shift;
    u16 x;
    u32 y;
    s32 tpage, clut, cy;
    s32 su, sv, uu, vv;
    u16 fl;
    s32 i, m;
    u32 b;

    poly = (Ft4_801833F0 *)D_800A5E60;
    fl = *(u16 *)((s32)ent + 0x1E) & 0x8000;
    flags = *(u32 *)((s32)ent + 4);
    tp = (flags >> 24) & 3;
    shift = 2 - tp;
    x = *(u16 *)((s32)ent + 0x28) + (*(s16 *)((s32)spr + 4) >> shift);
    y = *(u16 *)((s32)ent + 0x2A) + *(u16 *)((s32)spr + 6);
    vtx = *(s32 *)((s32)ent + 0x20);
    D_800A5E60 += 0xF0;
    if (flags & 0x40000000) {
        code = 0x2E;
        abr = (flags >> 28) & 3;
    } else {
        code = 0x2C;
        abr = 1;
    }
    tpage = (tp << 7) | (abr << 5) | ((y & 0x100) >> 4) | ((x & 0x3C0) >> 6) |
            ((y & 0x200) << 2);
    b = *(u8 *)((s32)ent + 0x27);
    cy = (b + 0x100) << 6;
    if (b < 0xE0) {
        clut = cy | 0x16;
    } else {
        clut = cy | 0x10;
    }
    {
        s32 t = ((x - ((tpage & 0xF) << 6)) << shift) +
                (*(u16 *)((s32)spr + 4) & ((1 << shift) - 1));
        su = t + zr;
        __asm__ __volatile__("" ::"r"(t + *(u8 *)((s32)spr + 2) - 1));
        __asm__ __volatile__("" ::"r"(t));
    }
    y = y & 0xFFFF;
    if (tpage & 0x10) {
        sv = y - 0x100;
    } else {
        sv = y + zr;
    }
    __asm__ __volatile__("" ::"r"(sv + *(u8 *)((s32)spr + 3) - 1));

    i = 1;
    uu = su;
    vv = sv;
    for (; i < 13; i += 2, poly++) {
        s32 k = (i - 1) * 4;
        __asm__ __volatile__("" ::"r"(i));
        poly->tag.len = 9;
        poly->code = code;
        poly->tpage = tpage;
        poly->u2 = su;
        poly->v2 = sv;
        poly->u0 = SR3_801833F0(vtx + k + 0x10) + uu;
        poly->v0 = SR3_801833F0(vtx + k + 0x12) + vv;
        poly->u1 = SR3_801833F0(vtx + i * 4 + 0x10) + uu;
        poly->v1 = SR3_801833F0(vtx + i * 4 + 0x12) + vv;
        /* k2 is recorded as a giv HERE, AFTER the u1/v1 mem giv - see (1). */
        {
            s32 k2 = (i + 1) * 4;
            poly->u3 = SR3_801833F0(vtx + k2 + 0x10) + uu;
            poly->v3 = SR3_801833F0(vtx + k2 + 0x12) + vv;
        }
        poly->clut = clut;
        __asm__ __volatile__("" ::"r"(i), "r"(i));
        poly->r0 = *(u8 *)((s32)ent + 0x24);
        poly->g0 = *(u8 *)((s32)ent + 0x25);
        poly->b0 = *(u8 *)((s32)ent + 0x26);
        poly->x0 = ((u16 *)q)[i * 2];
        poly->y0 = ((u16 *)q)[i * 2 + 1];
        poly->x1 = ((u16 *)q)[i * 2 + 2];
        poly->y1 = ((u16 *)q)[i * 2 + 3];
        poly->x2 = ((u16 *)q)[0];
        poly->y2 = ((u16 *)q)[1];
        poly->x3 = ((u16 *)q)[i * 2 + 4];
        poly->y3 = ((u16 *)q)[i * 2 + 5];
        if (fl != 0) {
            ADDPRIM_801833F0(&ot[*(s32 *)((s32)q + 0x34 + (i >> 1) * 4)], poly);
        } else {
            ADDPRIM_801833F0(ot, poly);
        }
    }
    poly[-1].x3 = ((u16 *)q)[2];
    poly[-1].y3 = ((u16 *)q)[3];
    poly[-1].u3 = su + SR3_801833F0(vtx + 0x10);
    poly[-1].v3 = sv + SR3_801833F0(vtx + 0x12);

    if (flags & 0x40000000) {
        dm = (Drm_801833F0 *)poly;
        if (fl != 0) {
            m = 0;
            D_800A5E60 += 0x30;
            do {
                m++;
                dm->tag.len = 1;
                dm->code0 = (abr << 5) | 0xE100000A;
                ADDPRIM_801833F0(&ot[*(volatile s32 *)((s32)q + 0x34)], dm);
                q = (u32 *)((s32)q + 4);
                dm++;
            } while (m < 6);
        } else {
            dm->code0 = (abr << 5) | 0xE100000A;
            D_800A5E60 += 8;
            dm->tag.len = 1;
            ADDPRIM_801833F0(ot, dm);
            /* Zero-byte live-range stretch: puts vtx's allocno priority at
             * 1232, inside the (1228, 1296) window - see (2).  Placement is
             * load-bearing; do not move this statement. */
            __asm__ __volatile__("" ::"r"(vtx));
        }
    }
}


void func_80185270(void) {
}

void func_80185278(void) {

    extern s16 D_801C0244;
    s16 *p = &D_801C0244;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0xe);
        i--;
    } while (i >= 0);
}



/* func_8018529C — cookbook §71 (sibling-first).
 * func_8018533C is ALREADY MATCHED in the same TU
 * (src/ov_SC03_014/ov_SC03_014_jr_8017EB7C.c L4221) as a 3-arg
 * `void func_8018533C(s32, s32, s32)`, so the untouched $a3 at the first
 * jal is just the incoming arg3 living on, not a 4th argument.
 * func_80185458 (asm, same TU) reads its 2nd arg as lhu+0 / lhu+2 / lh+4 /
 * lh+6 => the sp+0x10 local is a 4 x s16 record.
 *
 * Two levers took it 32 -> 2 -> 0 (match_one MATCH, rtu_match MATCH):
 *  1. LENGTH-DRIFT (-2, cookbook §78): writing `sp10.unk2 = i * 0x100`
 *     leaves gcc-2.7.2 recomputing `sll v0,s1,8` instead of building the
 *     strength-reduced giv, so only s0..s3 get saved and the frame is two
 *     instructions short.  An EXPLICIT accumulator (`ang += 0x100`) forces
 *     the second callee-saved register ($s2) and restores sw/lw $s4.
 *  2. REGALLOC-PERM $s1>$s2 (cookbook §3-T2, source order drives emission):
 *     `ang = 0;` on its own line before the loop emits the $s2 zero-init
 *     FIRST.  Folding it into the for-init (`for (i = 0, ang = 0; ...)`)
 *     puts $s1's zero-init first, which is the target order.
 */


extern void func_8018533C(s32 arg0, s32 arg1, s32 arg2);
extern void func_80185458(s32 arg0, Rec_8018A6A4_8018529C *arg1, s32 arg2, s32 arg3);

void func_8018529C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Rec_8018A6A4_8018529C sp10;
    s32 i;
    s32 ang;

    func_8018533C(arg0, 0x1000, 0);
    sp10.unk0 = *(u16 *)(arg3 + 0x0);
    sp10.unk4 = *(u16 *)(arg3 + 0x2);
    sp10.unk6 = 1;
    for (i = 0, ang = 0; i < 16; i++) {
        sp10.unk2 = ang;
        func_80185458(i, &sp10, arg1, arg2);
        ang += 0x100;
    }
}


extern s16 D_801C023C;
extern s16 D_801C023E;
extern s16 D_801C0240;

    void func_8018533C(s32 arg0, s32 arg1, s32 arg2) {

    extern s16 D_801C0242;
        D_801C023C = *(u16 *)((s32)arg0 + 0x0);
        D_801C023E = *(u16 *)((s32)arg0 + 0x2);
        D_801C0240 = arg1;
        D_801C0242 = arg2;
    }




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018536C(s32 a0) {

    extern s16 D_801C023C;
    extern s16 D_801C023E;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_800AF648;
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801C023C = sxy[0];
    D_801C023E = sxy[1];
}


    void func_801853E4(s32 arg0) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801C0242;
        *(s16 *)((s32)&D_801C0242 + 0x0) += arg0;
    }




extern void func_80185458(s32 arg0, Rec_8018A6A4_8018529C *arg1, s32 arg2, s32 arg3);

void func_80185400(void *a0, void *a1, void *a2) {
    s32 v0 = func_8018552C();
    if (v0 >= 0) {
        func_80185458(v0, (Rec_8018A6A4_8018529C *)a0, (s32)a1, (s32)a2);
    }
}



/* func_80185458 — SPLICE RECONCILE (bytes unchanged from the s6h draft).
 *
 * THREE in-TU collisions, all fixed without touching an emitted instruction
 * (src/ov_SC03_014/ov_SC03_014_jr_801848E4.c):
 *
 * (1) memcpy — cookbook §2959 / the sibling note at TU L3742.  The TU declares
 *     memcpy THREE times: L81 + L1518 with the builtin-compatible signature
 *     (void*, const void*, unsigned) and then L1524 as
 *     `extern void *memcpy(void *dst, void *src, s32 n);`.  L1524 disagrees with
 *     gcc's built-in, so duplicate_decls "throws away the built-in" (warning only,
 *     because the old decl was still DECL_BUILT_IN) and installs a PLAIN function
 *     decl.  Two consequences at the splice point (L3635):
 *       a. my own builtin-shaped redeclaration now conflicts with a plain decl —
 *          hard error ("conflicting types for `memcpy'", :3637 vs :1524);
 *       b. even if it compiled, the identifier `memcpy` is no longer a builtin
 *          here, so both copies would lower to `jal memcpy` — but the TARGET
 *          bytes are the INLINE block move (lwl 3 / lwr 0 / swl / swr, no jal).
 *     Fix = do not name memcpy at all: a 4-byte STRUCT ASSIGN through an
 *     ALIGN-1 struct (u8 x4).  That is exactly the sibling func_8018ADA8 lever
 *     in this same TU (TU L3736-3744, cookbook §48-C2): align 1 routes
 *     mips.c expand_block_move, which copy_addr_to_reg's the source into one
 *     held register -> the identical lwl/lwr + swl/swr pair, zero memcpy ref.
 *     The typedef is BLOCK-scoped so it cannot collide with the TU's own
 *     block-scoped `V4` at L3758.
 *
 * (2) func_80185458 itself — the TU prototypes it at L3570 as
 *     `extern void func_80185458(s32, Rec_8018A6A4 *, s32, s32);` (used by the
 *     matched caller func_8018A6A4 at L3583).  Rec_8018A6A4 is a TU-local
 *     typedef I cannot restate (C89 forbids the redefinition), and the last two
 *     args are really pointers, so defining the name directly is "conflicting
 *     types".  Fix = §37/§124 ASM-LABEL ALIAS: define aF8018A860 with an
 *     __asm__("func_80185458") label.  Emits the identical symbol, leaves the
 *     TU's declaration untouched, zero blast radius, zero byte change.
 *
 * (3) D_801C0244 / rand — declared VERBATIM as the TU already has them
 *     (D_801C0244: TU L3637 + L3671; rand: TU L951), so both are exact
 *     re-declarations and merge silently.
 */
extern s32 rand(void);      /* TU L951, verbatim */

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3) __asm__("func_80185458");

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3)
{

    extern s16 D_801C0244;      /* TU L3637 / L3671, verbatim */
   /* align 1 — §48-C2 */
    s16 *s1;
    u16 temp_u16;
    s16 temp_s16;
    s32 temp_s32, v0;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801C0244);

    *(u16 *)s1 = *(u16 *)a1;

    *(B4_80185458 *)((u8 *)s1 + 6) = *(B4_80185458 *)a2;
    *(u8 *)((u8 *)s1 + 9) = 0;

    *(B4_80185458 *)((u8 *)s1 + 10) = *(B4_80185458 *)a3;
    *(u8 *)((u8 *)s1 + 13) = 0;

    v0 = rand() & 0x3f;
    temp_u16 = *(u16 *)((u8 *)a1 + 2);
    *(u16 *)((u8 *)s1 + 2) = temp_u16 + v0 - 0x20;

    v0 = rand() & 0x7f0;
    temp_s16 = *(s16 *)((u8 *)a1 + 4);
    temp_s32 = temp_s16 * (v0 + 0xc00);
    v0 = (s32)(temp_s32 >> 12);
    *(s16 *)((u8 *)s1 + 4) = (s16)v0;

    v0 = *(s16 *)((u8 *)a1 + 6);
    if (v0 != 0) {
        u16 v1 = *(u16 *)((u8 *)s1 + 4);
        *(u8 *)((u8 *)s1 + 9) = 1;
        *(u16 *)((u8 *)s1 + 4) = 0;
        *(u8 *)((u8 *)s1 + 13) = (u8)v1;
    }
}




s32 func_8018552C(void) {

    extern s16 D_801C0244;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801C0244 + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0xE;
    }
    return -1;
}





void func_80185568(s32 a0, s32 a1) {

    extern s16 D_801C0244;
    s16 *s1;
    u16 val;

    if (a0 >= 0x10) return;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801C0244);
    val = *(u16 *)s1;

    if (val == 0) return;

    if (a1 == 0) {
        *(u16 *)s1 = 0;
    } else {
        *(u8 *)((u8 *)s1 + 9) = 2;
    }
}



/* func_801855B4 — 16-entry table walk, stride 0xE, over D_801C0244.
 * §71 sibling: func_8018A680 (same TU, L4199) already matched the
 * `extern s16 D_801C0244; s16 *p = &D_801C0244; p = (s16*)((s32)p+0xe)`
 * shape over the very same array — copy that walker verbatim.
 *
 * Two induction registers in the target ($s1 = base+0, $s0 = base+4) are NOT
 * two source pointers: $s1 is the user pointer (the biv, used for the +0
 * accesses) and $s0 is loop.c's single COMBINED address giv for the
 * {+4, +9, +13} group (offsets 0/5/9 off $s0). Declaring a second pointer
 * splits that group and costs a third register (iter 1: 53 mismatches).
 */

extern void func_80185690(s32 arg0);

void func_801855B4(void) {

    extern s16 D_801C0244;
    s16 *p = &D_801C0244;
    s32 i = 0;
    s16 t;

    do {
        if (*(u16 *)p != 0) {
            func_80185690(i);
            switch (*(u8 *)((s32)p + 9)) {
            case 1:
                if (*(s16 *)((s32)p + 4) < *(u8 *)((s32)p + 13)) {
                    *(s16 *)((s32)p + 4) = *(s16 *)((s32)p + 4) + 8;
                } else {
                    *(u8 *)((s32)p + 9) = 0;
                }
                break;
            case 2:
                t = *(s16 *)((s32)p + 4);
                if (t != 0) {
                    t -= 0x10;
                    *(s16 *)((s32)p + 4) = t;
                    if (t > 0) {
                        break;
                    }
                }
                *p = 0;
                break;
            }
        }
        i++;
        p = (s16 *)((s32)p + 0xe);
    } while (i < 0x10);
}



/* func_80185690 — draws one entry of the 16-slot D_801C0244 particle table:
 * bump-allocates a 0x1C-byte GPU packet out of D_800A5E60, fills it from the
 * table entry, runs two RotMatrixZ/ApplyMatrixSV passes to place the two
 * endpoints, then link-ins the packet into the current double-buffer's OT
 * (the PSY-Q `addPrim` macro pair) and calls func_80016638.
 *
 * STATUS: byte-MATCH, 177/177 instructions (match_one standalone AND spliced
 * into the real TU — the in-TU compile adds ZERO new cc1 diagnostics over the
 * unmodified TU baseline).
 *
 * ---------------------------------------------------------------------------
 * LEVERS (each byte-checked against asm/.../func_80185690.s)
 *
 *  §48  STRUCT ASSIGN, not a hand-rolled temp copy.  `m = D_800AE620;` on a
 *       32-byte aggregate routes expr.c move_by_pieces, which emits the exact
 *       lw/lw/lw + sw/sw/sw (x2) + lw/lw + sw/sw grouping AND picks the
 *       target's registers ($a2 = source address, $v0/$v1/$a1 = carriers), and
 *       keeps the arg0*14 allocator chain OUT of the copy.  The manual
 *       three-temp form (DEFINE_func_8012B4B8, engine_core.h L29487) emits the
 *       same instruction MIX but a different allocation (+60 mismatches).
 *
 *  §21/T6  The double-buffer index D_800B9A02 is read at ALL THREE use sites
 *       (three `lhu`s off ONE materialised `la`).  A PLAIN read is CSEd down to
 *       two AND keeps -G0 symbol addressing (lui+lhu per read, +1 insn); a
 *       POINTER local gives the `la` but lets cse fold the third read.  The
 *       `volatile u16 *` pointer local reproduces BOTH properties and leaves
 *       the TU's own `extern s16 D_800B9A02;` untouched.
 *
 *  T6   The OT base is bound to an s32 local (`ot`) so the tag read/write keep
 *       the `0x40($v1)` displacement form instead of folding into the pointer.
 *
 *  L4   `mp`, a pointer local bound to &m, is what puts the matrix address in a
 *       callee-saved register ($s2) and turns each argument setup into a move;
 *       passing the array directly re-materialises `addiu $aN,$sp,0x10` at
 *       every call site and drops $s6 from the frame entirely.
 *
 *  S1   `t = *(u16 *)ent;` is hoisted ABOVE the two `sh $zero` stores — the
 *       sp-relative stores are not disambiguated from the $s0-based load, so
 *       only SOURCE ORDER moves it (4 mismatches).
 *
 *  T-form  `u16 bx/by` (not s32) is what makes `addu $v0,$s3,$v0` come out with
 *       the accumulator first; through s32 locals combine canonicalises the
 *       zero_extend into operand 0 and both adds emit reversed.
 *
 *  §83c-inverse  FRAME: 0x70 = 16 args + 56 declared vars + 32 saved regs + an
 *       8-byte COMPILER TEMP that gcc allocates for the two `symbol+register`
 *       memory references (both D_800A651C).  So the DECLARED locals must total
 *       56, not 60: m(32)@0x10, sv(8)@0x30, out(8)@0x38, v(8)@0x40 — the third
 *       word of the vector handed to func_8004901C (sp+0x48) lands INSIDE that
 *       compiler temp.  `s32 v[3]` gives a 0x78 frame and 19 extra mismatches.
 *       Do NOT invent a dead local to reach the frame size.
 *
 * ---------------------------------------------------------------------------
 * THE TWO RESIDUAL CLUSTERS AND WHAT ACTUALLY CLOSED THEM
 * (both are gcc-2.7.2-map/sched.md §1 rule 7 "BIRTHING BOOST" + rule 5(b)
 *  "potential hazard"; diagnosed from the cc1 `-dS` ready-list trace, which
 *  names the decision verbatim: `;; insn 245 has a greater potential hazard`.)
 *
 *  (a) The three symbol loads before the first RotMatrixZ came out E4,EA,E6
 *      instead of EA,E4,E6.  `lh $a0,D_801C0242` is a single-set SET(REG,…) —
 *      the sched1 birthing boost sinks it to just before its consumer (the
 *      jal), i.e. one slot too late.  Statement order CANNOT fix this: written
 *      as a plain local the load is combined into the call's arg setup, so its
 *      LUID is the call's either way (verified: two source orders, identical
 *      bytes).  `register s32 ang __asm__("$4")` keeps the load a separate insn
 *      AT its source position — zero extra instructions, +0 bytes.
 *
 *  (b) The tail's `lw $v1,0($s1)` (`*(u32 *)p`) belongs in the load-delay slot
 *      of `lhu $a0,0($a2)`; ours landed 7 insns later with `lui $a0,0xff00`
 *      taking the slot.  sched1 trace: at T-27 the ready list is
 *      `247 (7f000001) 245 (7f000001)` — BOTH boosted — and the tie goes to the
 *      LOAD via `potential_hazard` (memory-unit users beat ALU insns), so the
 *      load is picked first = placed LAST.  TWO edits are needed and neither
 *      works alone:
 *        1. KILL the boost on the load's destination — `pv` gets a second SET
 *           from a zero-byte dead `__asm__ __volatile__("" : "=r"(pv));` at the
 *           end of the function (sched.md S2: a plain C reassignment does not
 *           work, cse/flow removes it; reusing one local across BOTH addPrim
 *           halves does kill the boost but makes `pv` a 2-death GLOBAL allocno
 *           that loses $v1, §136).  With the boost dead, sched1 emits the
 *           target order exactly (proved with -fno-schedule-insns2).
 *        2. PIN `pv` to $v1 (`register u32 pv __asm__("$3")`).  Without it,
 *           local-alloc gives $v1 to the shorter, denser index quantity and
 *           `pv` lands in $a1/$t0; sched2 then re-applies rule 5(b) and undoes
 *           sched1's order.  With `pv` in $v1 the index is pushed to $a0, the
 *           0xFF000000 constant reuses $a0, and its output-dependence on the
 *           index's `sll/addu` FREEZES it after them — which is precisely the
 *           target's shape, and what makes sched2 leave sched1's order alone.
 *
 *      Pin-trim log (all re-scored): dropping the $a2 `bidx` pin — MATCH;
 *      dropping the $a3 0xFFFFFF pin — MATCH; dropping `ang` — 4 mismatches
 *      (a dead-volatile boost-kill on `ang` does NOT substitute); dropping
 *      `pv` — 11; dropping the dead `pv` asm — 11.  Two pins are the minimum
 *      found.
 *
 * ---------------------------------------------------------------------------
 * DECLARATIONS: ApplyMatrixSV, D_800B9A02 and D_801C023C/E6/EA/EC are declared
 * VERBATIM as the TU already has them at file scope (L163, L2460/2462,
 * L3689/3705/3706, L3726, L3879), so they merge silently.  D_800AE620,
 * D_800A5E60, D_800A651C, D_800A6518, D_801C0240, RotMatrixZ, func_8004901C and
 * func_80016638 have NO file-scope declaration anywhere in the TU and none in
 * include/ (checked in one pass, D2), so each is block-scoped here to keep the
 * blast radius on the rest of the TU at zero (§103/T51).  Verified by splicing
 * this body over the INCLUDE_ASM at TU L3917 and compiling the whole TU: same
 * 7 stderr lines as the untouched TU, and func_80185690 is byte-identical.
 */

void func_80185690(s32 arg0)
{
   /* 32 bytes, align 4 */

    extern Blk32_8018AA98_80185690 D_800AE620;
    extern s32 D_800A5E60;
    extern s32 D_800A651C;
    extern u8 D_800A6518[];
    extern s16 D_801C023C;
    extern s16 D_801C023E;
    extern s16 D_801C0240;
    extern s16 D_801C0242;
    extern s16 D_801C0244;
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8004901C(void *a0, void *a1);
    extern void func_80016638(void *a0, s32 a1, s32 a2);

    Blk32_8018AA98_80185690 m;                    /* sp+0x10 */
    s16 sv[4];                           /* sp+0x30 */
    s16 out[4];                          /* sp+0x38 */
    s32 v[2];                            /* sp+0x40 — 3rd word lives in the temp area */
    void *mp;
    u8 *p;
    u8 *ent;
    s32 ot;
    u16 bx;
    u16 by;
    register s32 ang __asm__("$4");      /* §17 pin — see residual (a) */
    volatile u16 *bidx;
    s32 t;
    register u32 pv __asm__("$3");       /* §17 pin — see residual (b) */

    m = D_800AE620;
    mp = &m;

    ent = (u8 *)((arg0 * 14) + (s32)&D_801C0244);
    p = (u8 *)D_800A5E60;
    D_800A5E60 = (s32)p + 0x1C;

    p[3] = 6;
    p[7] = 0x32;
    p[4] = ent[6];
    p[5] = ent[7];
    p[6] = ent[8];
    p[0xC] = ent[0xA];
    p[0xD] = ent[0xB];
    p[0xE] = ent[0xC];
    p[0x14] = ent[0xA];
    p[0x15] = ent[0xB];
    p[0x16] = ent[0xC];

    ang = D_801C0242;
    bx = (u16)D_801C023C;
    by = (u16)D_801C023E;
    RotMatrixZ(ang, mp);

    *(s32 *)((u8 *)v + 8) = D_801C0240;
    v[1] = *(s32 *)((u8 *)v + 8);
    v[0] = v[1];
    func_8004901C(mp, v);

    t = *(u16 *)ent;
    sv[2] = 0;
    sv[1] = 0;
    sv[0] = t;
    *(s16 *)(p + 8) = bx;
    *(s16 *)(p + 0xA) = by;

    RotMatrixZ(*(s16 *)(ent + 2) - (((s32)*(u16 *)(ent + 4) << 16) >> 17), mp);
    ApplyMatrixSV(mp, sv, out);
    *(s16 *)(p + 0x10) = bx + (u16)out[0];
    *(s16 *)(p + 0x12) = by + (u16)out[1];

    RotMatrixZ(*(s16 *)(ent + 4), mp);
    ApplyMatrixSV(mp, sv, out);
    bx += (u16)out[0];
    *(s16 *)(p + 0x18) = bx;
    by += (u16)out[1];
    *(s16 *)(p + 0x1A) = by;

    /* addPrim(otp, p) == setaddr(p, getaddr(otp)), setaddr(otp, p) */
    bidx = (volatile u16 *)&D_800B9A02;
    pv = *(u32 *)p;
    *(u32 *)p = (pv & 0xFF000000) |
                (*(u32 *)(*(s32 *)((u8 *)&D_800A651C +
                                   (*bidx * 20)) + 0x40) & 0xFFFFFF);
    ot = *(s32 *)((u8 *)&D_800A651C + (*bidx * 20));
    *(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
    func_80016638(&D_800A6518[*bidx * 20], 0x10, 1);
    __asm__ __volatile__("" : "=r"(pv));   /* zero-byte 2nd SET: kills the sched1 birthing boost */
}


void func_80185954(void) {

    extern s16 D_801C013C;
    s16 *p = &D_801C013C;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0x10);
        i--;
    } while (i >= 0);
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_801859A0(s32 a0);

void func_80185978(s32 a0) {
    s32 pv[2];
    func_80015978(a0, pv);
    func_801859A0((s32)pv);
}



/* func_801859A0 — §71 sibling of func_8018A774 / func_8018AF0C (same TU): the
 * RotTransPers wrapper family.  Here the SVECTOR comes in as the parameter
 * instead of being produced by func_80015978, so pv[0..1] is free and carries
 * the 4-byte word copied out of D_801BED24 instead.
 *
 * Frame proof (0x38 = 0x10 outgoing + 0x18 var + 0x10 saved s0/s1/ra):
 *   sp+0x10  u16 sxy[4]  (8 bytes)  -> RotTransPers a1, func_80185A28 arg0
 *   sp+0x18  s32 pv[4]   (16 bytes) -> pv[0] = copy dest, &pv[2]/&pv[3] = 0x20/0x24
 *
 * The lwl 0x3 / lwr 0x0 / swl 0x1B / swr 0x18 block move: a 4-byte struct assign
 * whose type has ALIGNMENT 1 (cookbook §48-C2).  Align 1 (not 2) is load-bearing —
 * it is what pushes the copy off the move_by_pieces path (which keeps the SYMBOL
 * in the address and emits a fresh `lui $at,%hi` per reference) onto mips.c
 * expand_block_move, which copy_addr_to_reg's the source address into ONE held
 * register first -> `lui $a1,%hi; addiu $a1,$a1,%lo; lwl 3($a1); lwr 0($a1)`.
 * A {u16,u16} (align 2) struct compiles to the same opcode sequence but with the
 * folded-symbol addressing: 4 mismatches.  Struct assign, NOT memcpy (memcpy
 * byte-matches in isolation but lowers to `jal memcpy` in any TU that declares
 * it — §2959).
 *
 * All four callee prototypes are copied VERBATIM from this TU (func_8004914C /
 * func_800491AC / RotTransPers at file scope L3484-3486; func_80185A28 from its
 * own definition at L3612).  D_800AF648 is block-scoped `extern u8` exactly as
 * the two matched siblings do it.  D_801BED24 appears nowhere else in the TU.
 */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_80185A28(void *arg0, void *arg1, s32 arg2, s32 arg3);

void func_801859A0(s32 a0) {
    extern u8 D_800AF648;
    extern V4_801859A0 D_801BED24;
    u16 sxy[4];
    s32 pv[4];

    *(V4_801859A0 *)pv = D_801BED24;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers(a0, (s32)sxy, &pv[2], &pv[3]);
    func_80185A28(sxy, pv, 0x10, 0x18);
}



extern void func_80185A94(void *a0, void *a1, s16 a2);
extern void func_80185BC8(s32 a0, s16 a1, u16 a2);

void func_80185A28(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    /* The target frame is 0x30: 0x10 outgoing-arg area + 0x10 var_size +
     * 0x10 saved regs (s0/s1/s2/ra at 0x20..0x2C).  gcc-2.7.2 allocates a
     * declared aggregate even when it is never referenced, so this 16-byte
     * local reproduces the original's var_size exactly. */
    s32 unused[4];
    s32 i;
    s32 j;

    func_80185A94(arg0, arg1, arg2);
    for (i = 0, j = 0; i < 0x10; i++, j += 0x100) {
        func_80185BC8(i, j, arg3);
    }
}





void func_80185A94(void *a0, void *a1, s16 a2) {

    extern s16 D_801C0130;
    extern s16 D_801C0132;
    extern u8 D_801C0138;
    extern u8 D_801C0139;
    extern u8 D_801C013A;
    extern u32 D_801C0134;
    if (a0 != NULL) {
        D_801C0130 = *(u16 *)a0;
        D_801C0132 = *(u16 *)((s32)a0 + 2);
    } else {
        D_801C0130 = 0;
        D_801C0132 = 0;
    }

    D_801C0138 = *(u8 *)a1;
    D_801C0139 = *(u8 *)((s32)a1 + 1);
    D_801C013A = *(u8 *)((s32)a1 + 2);
    D_801C0134 = (u32)a2 << 16;
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_80185B04(s32 a0) {

    extern s16 D_801C0130;
    extern s16 D_801C0132;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_800AF648;
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801C0130 = sxy[0];
    D_801C0132 = sxy[1];
}




extern s32 func_80185CE4(void);
extern void func_80185BC8(s32 a0, s16 a1, u16 a2);

void func_80185B7C(s32 a0, s32 a1) {
    s32 result = func_80185CE4();
    if (result >= 0) {
        s16 ext_a0 = (s16)a0;
        func_80185BC8(result, ext_a0, (u16)a1);
    }
}



/* func_80185BC8 — particle/ripple spawner for slot `a0` of the 16-entry,
 * 0x10-byte-stride table at D_801C013C.
 *
 * Declaration notes (the TU already carries all of these — nothing is invented):
 *   - rand / func_80047948 / func_8004787C : verbatim re-declarations of the
 *     TU's own file-scope prototypes (L951, L2197, L2198) -> merge silently.
 *   - D_801C013C : block-scope `extern s16` exactly as func_8018AD5C (L3869)
 *     and func_8018B0EC (L3982) declare it.
 *   - D_801C0136 : its own dlabel in asm/ov_SC03_014/data/tail19.data.s:5868;
 *     undeclared anywhere in the TU, so a block-scope extern is conflict-free.
 *     It is declared as an ARRAY on purpose: the ARRAY_REF sets MEM_IN_STRUCT_P,
 *     which restores the true_dependence() edge against the in-struct `p->f2`
 *     store and stops sched2 from hoisting the load above it (cookbook §135/2).
 *   - The TU's own prototype for this function is
 *       extern void func_80185BC8(s32 a0, s16 a1, u16 a2);   (L3929)
 *     but the body byte-proves the params are plain s32 (no `sll/sra` on $a1 and
 *     a single `andi` at the use, not the promoted-var `move`+`andi` pair). So the
 *     definition uses the §37/§124 ASM-LABEL ALIAS — exactly what this same TU
 *     already does for `aF8018A860` — leaving the TU's declaration untouched.
 */

extern s32 rand(void);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void aF8018AFD0(s32 a0, s32 a1, s32 a2) __asm__("func_80185BC8");

void aF8018AFD0(s32 a0, s32 a1, s32 a2)
{

    extern s16 D_801C013C;
    extern s16 D_801C0136[];

    s32 unused[4];      /* dead locals — reproduces var_size 0x10 (frame 0x38) */
    P_80185BC8 *p;
    u16 rad;
    s32 m;
    s32 ang;
    s32 t8;
    s16 tC;

    p = (P_80185BC8 *)((s32)&D_801C013C + (a0 << 4));

    rad = a2;
    rad = a2 + (rand() % (rad >> 2) - (rad >> 3));

    ang = a1 + (rand() & 0x3f) - 0x20;
    p->f6 = ang;

    m = rad;
    t8 = (func_80047948(p->f6) * m) >> 12;
    tC = (func_8004787C(p->f6) * m) >> 12;
    p->f8 = t8 << 16;
    p->fC = tC << 16;

    p->f0 = (rand() & 0xf) + 0x10;
    p->f2 = m << 6;
    p->f4 = (s32)D_801C0136[0] * 64;
}




s32 func_80185CE4(void) {

    extern s16 D_801C013C;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801C013C + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0x10;
    }
    return -1;
}




/* func_80185D20 — the 16-slot particle/effect stepper over D_801C013C[16]
 * (0x10-byte records; slot 0 = the `active` u16 that func_8018AD5C clears and
 * func_8018B0EC scans).  Layout used here, all as byte-offsets off ONE walked
 * base pointer:
 *   +0x0 u16 active   +0x2 s16 angle   +0x4 u16 dangle
 *   +0x6 s16 dir      +0x8 s32 x       +0xC s32 z
 *
 * IV shape (cookbook §3-Giv / gcc-map L1): the target has ONE biv (the walked
 * base, kept alive by the bare +0x0 accesses, which find_mem_givs excludes from
 * giv formation) plus ONE combined DEST_ADDR giv anchored at base+2
 * (`addiu $s1, $s2, 0x2`).  combine_givs takes g1 from the list HEAD and
 * record_giv PREPENDS, so *the last-emitted offset reference anchors*: the
 * `+= dangle` statement (which ends on a +0x2 store) must therefore come LAST
 * in the body.  Written before the two s32 updates it anchors at base+0xC
 * instead -> 14 mismatched immediates.
 *
 * Both rsin/rcos products are computed BEFORE any store because gcc-2.7.2's
 * sched.c makes every mem ref depend on last_function_call — a store emitted
 * between the two `jal`s could not have floated below the second one.
 *
 * `i++` precedes the pointer bump in the for-increment: that emission order is
 * what puts `addiu $s4,$s4,1` ahead of the giv's `addiu $s1,$s1,0x10` (the
 * biv's own bump then fills the branch delay slot).
 *
 * func_80047948 / func_8004787C keep this TU's file-scope prototypes verbatim
 * (L2197-2198, `s32` param) — the s16 field is sign-extended at the call site
 * by the `lh`, so the narrower m2c-style `s16` prototype is not needed (§17a-1).
 * D_801C013C uses the TU's existing block-scope `extern s16` spelling
 * (func_8018AD5C L3869, func_8018B0EC L3982).
 */

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80185D20(void) {

    extern s16 D_801C0136;
    extern s16 D_801C013C;
    extern void func_80185E34(s32);

    s16 *p;
    s32 i;
    s16 ang;
    s32 vx;
    s32 vz;

    ang = D_801C0136;
    p = &D_801C013C;

    for (i = 0; i < 0x10; i++, p = (s16 *)((s32)p + 0x10)) {
        if (*(u16 *)p != 0) {
            if ((ang > 0 && *(s16 *)((s32)p + 2) > 0x4000) ||
                (ang < 0 && *(s16 *)((s32)p + 2) <= 0)) {
                *p = 0;
            } else {
                func_80185E34(i);
                vx = func_80047948(*(s16 *)((s32)p + 6)) * ang * 0x10;
                vz = func_8004787C(*(s16 *)((s32)p + 6)) * ang * 0x10;
                *(s32 *)((s32)p + 8) += vx;
                *(s32 *)((s32)p + 12) += vz;
                *(u16 *)((s32)p + 2) += *(u16 *)((s32)p + 4);
            }
        }
    }
}



/* func_80185E34 — spawns one 0x14-byte GPU packet from D_800A5E60, rotates /
 * scales a matrix copy of D_800AE620 by the D_801C013C[a0] record, projects the
 * four corner offsets into the packet, then links the packet into the OT.
 *
 * Byte-verified levers (all three were needed; each is worth 8-31 insns):
 *
 *  A. THE OT LINK IS THE libgpu P_TAG BITFIELD, NOT HAND-MASKING.  Writing
 *     `*(u32*)q = (*(u32*)q & 0xFF000000) | (ot & 0xFFFFFF)` is byte-correct
 *     arithmetic but gives the WRONG register assignment (16 mismatches: the
 *     0xFFFFFF / 0xFF000000 / &D_800B9A02 pseudos land in a0/a2/a3 permuted,
 *     and the `lw $v1,0($s3)` gets serialised behind the index load).  The
 *     `unsigned addr:24; unsigned len:8` bitfield insert reproduces both the
 *     allocation and the schedule exactly.  This is just `addPrim(ot, q)`.
 *
 *  B. THE OT TABLE MUST BE AN ARRAY_REF (`D_800A651C[i].a`), NOT
 *     `*(s32*)((u8*)&D_800A651C + i*20)`.  With the pointer-arith spelling gcc
 *     allocates a phantom 8-byte stack temp that is never referenced, pushing
 *     the frame from 0x68 to 0x70 (cookbook D6 in reverse: the frame is too
 *     BIG).  The temp only appears when the SAME lookup expression occurs in
 *     two statements; the ARRAY_REF form (engine_core.h `OtBlk`) kills it.
 *
 *  C. THE LAST ApplyMatrixSV RECOMPUTES THE MATRIX ADDRESS.  The first four
 *     matrix arguments come out of $s4 (`addu $aX,$s4,$zero`), but the fifth is
 *     `addiu $a0,$sp,0x10`.  cse.c cannot be talked out of folding a fifth
 *     `&m` into the existing pseudo: the conditional above it is a
 *     "branch around a block", so cse_end_of_basic_block EXTENDS the basic
 *     block through the join label (status AROUND) and the equivalence class
 *     for (plus fp 16) is still live.  Every source-level attempt to break it
 *     (pointer local, `mp = m` in the skipped arm, a §21 zero-byte re-tie,
 *     do{}while(0) loop notes) either changed nothing or cost 3 insns by
 *     turning the pointer into a two-def global allocno.  Pinning a reader to
 *     $sp makes the expression `(plus (reg 29) 16)` — a different rtx from
 *     `(plus (reg fp) 16)`, so cse never looks it up, and the single-use pseudo
 *     is folded by combine into the one `addiu` the target has.
 *
 *  The svp/outp block around the FIRST ApplyMatrixSV is load-bearing too:
 *  removing it costs 6 insns and two extra callee-saved registers.
 */

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixZ(s32 a0, void *a1);
extern void func_8004901C(void *a0, void *a1);
extern void func_80016638(void *a0, s32 a1, s32 a2);


/* 0x10-byte-stride record table at D_801C013C (same table as func_8018AD5C) */

      /* the 0x20-byte matrix */
  /* == engine_types.h OtBlk */
          /* the D_800B9A02 buffer index */
 /* libgpu P_TAG */

void func_80185E34(s32 a0) {

    extern s16 D_801C0130;
    extern s16 D_801C0132;
    extern u8 D_801C0138;
    extern u8 D_801C0139;
    extern u8 D_801C013A;

    extern s16 D_801C013C;
    extern u8 *D_800A5E60;
    extern s32 D_800AE620;
    extern u8 D_800A6518[];
    extern Ot_8018B23C_80185E34 D_800A651C[];

    s32 m[8];       /* sp+0x10 */
    u8 sv[8];       /* sp+0x30 */
    u16 out[4];     /* sp+0x38 */
    s32 scale[4];   /* sp+0x40 */

    u8 *q;
    Rec_8018B23C_80185E34 *p;
    s32 x;
    s32 y;
    s32 ang;

    q = D_800A5E60;

    *(Mat32_8018B23C_80185E34 *)m = *(Mat32_8018B23C_80185E34 *)&D_800AE620;

    D_800A5E60 = q + 0x14;
    *(u8 *)(q + 3) = 4;
    *(u8 *)(q + 7) = 0x22;
    *(u8 *)(q + 4) = D_801C0138;
    *(u8 *)(q + 5) = D_801C0139;
    *(u8 *)(q + 6) = D_801C013A;

    p = (Rec_8018B23C_80185E34 *)((s32)&D_801C013C + (a0 << 4));
    x = p->fA + (u16)D_801C0130;
    y = p->fE + (u16)D_801C0132;
    RotMatrixZ(p->f6, m);

    scale[0] = *(s16 *)((s32)p + 2);
    scale[1] = *(s16 *)((s32)p + 2);
    scale[2] = *(s16 *)((s32)p + 2);
    func_8004901C(m, scale);

    *(s16 *)(sv + 4) = 0;
    *(s16 *)(sv + 2) = 0;
    *(s16 *)(sv + 0) = p->f0;
    {
        void *svp = sv;
        void *outp = out;
        ApplyMatrixSV(m, svp, outp);
        __asm__ __volatile__("" : "=r"(svp));
        __asm__ __volatile__("" : "=r"(outp));
    }

    *(s16 *)(q + 0x8) = x + ((s16)out[0] >> 1) * 3;
    *(s16 *)(q + 0xA) = y + ((s16)out[1] >> 1) * 3;
    *(s16 *)(q + 0xC) = x - ((s16)out[0] >> 1);
    *(s16 *)(q + 0xE) = y - ((s16)out[1] >> 1);
    x = x + out[0];
    *(s16 *)(q + 0x10) = x;
    y = y + out[1];
    *(s16 *)(q + 0x12) = y;

    ang = -0x400;
    if (p->f0 & 1) {
        ang = 0x400;
    }
    RotMatrixZ(ang, m);

    *(s16 *)(sv + 0) = 2;
    {
        /* lever C: sp+0x10 IS &m, but spelled so cse cannot fold it to $s4 */
        register u8 *spr __asm__("$29");
        ApplyMatrixSV(spr + 0x10, sv, out);
    }

    *(s16 *)(q + 0x10) = *(u16 *)(q + 0x10) + out[0];
    *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + out[1];

    {
        Bidx_8018B23C_80185E34 *bp = (Bidx_8018B23C_80185E34 *)&D_800B9A02;

        /* addPrim(&D_800A651C[bp->f].a[0x10], q) */
        ((PTag_8018B23C_80185E34 *)q)->addr =
            ((PTag_8018B23C_80185E34 *)(D_800A651C[bp->f].a + 0x40))->addr;
        ((PTag_8018B23C_80185E34 *)(D_800A651C[bp->f].a + 0x40))->addr = (u32)q;
        func_80016638(&D_800A6518[bp->f * 20], 0x10, 1);
    }
}



/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c):
 *   D_80126B62     TU:1793/4533  `extern u16` -> cast to s16* at the use site (`lh`)
 *   D_80126B96     TU:3758/4695/5189/5269  `extern u16`
 *   func_8012DEB8  TU:5081/5147/5266/5315  `s32 (s32,s32,s32)`
 *   func_8012BD14  TU:3986                 `s32 (s32)`
 * D_8019D1F4 / D_8019D21C / D_8019D244 are 20-entry `.short` tables in
 * asm/ov_SC02_026/data/tail.data.s:40884/40909/40934 (loads are `lhu` -> u16).
 * D_8019D26C is the 2-entry fn-ptr table right after them (func_80180A4C /
 * func_80180AF0); same `void (*[])(...)` form as D_801A9EB8 (TU:3653).
 * func_8002D59C is declared nowhere in this TU. */

extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012BD14(s32 a0);
extern void func_8002D59C(s32 a0, u16 a1, s32 a2);

void func_80186118(s32 a0) {

    extern u16 D_80126B62;
    extern u16 D_80126B96;
    extern u16 D_8019D1F4[];
    extern u16 D_8019D21C[];
    extern u16 D_8019D244[];
    extern void (*D_8019D26C[])(s32);
 /* 8 bytes */

    V4_8017FAC0_80186118 p1;
    V4_8017FAC0_80186118 p2;
    s32 i;
    s32 t;
    s32 y;
    s32 ret;

    t = *(s16 *)(a0 + 0xA) + 0x20;
    y = *(s16 *)&D_80126B62 - t;
    if (y < -0x110) {
        y = -0x110;
    } else if (y > 0) {
        y = 0;
    }
    p1.y = y;
    p2.y = y;

    for (i = 0; i < 20; i += 4) {
        p1.x = D_8019D1F4[i];
        p1.z = D_8019D1F4[i + 1];
        p2.x = D_8019D1F4[i + 2];
        p2.z = D_8019D1F4[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }
    for (i = 0; i < 20; i += 4) {
        p1.x = D_8019D21C[i];
        p1.z = D_8019D21C[i + 1];
        p2.x = D_8019D21C[i + 2];
        p2.z = D_8019D21C[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }
    for (i = 0; i < 20; i += 4) {
        p1.x = D_8019D244[i];
        p1.z = D_8019D244[i + 1];
        p2.x = D_8019D244[i + 2];
        p2.z = D_8019D244[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }

    D_8019D26C[*(u16 *)(a0 + 0x2)](a0);

    ret = func_8012BD14(a0);
    if (ret > 0x3FFFF) {
        *(s16 *)(a0 + 0xFE) = 1;
        func_8002D59C(4, 0x609, *(u16 *)(a0 + 0x70));
    } else {
        *(s16 *)(a0 + 0xFE) = *(u16 *)(a0 + 0xFE) - 1;
        if (*(s16 *)(a0 + 0xFE) == 0) {
            *(s16 *)(a0 + 0xFE) = 4;
            func_8002D59C(0x609, ((0x40000 - ret) * 127) / 0x40000 | 0x1000,
                          *(u16 *)(a0 + 0x70));
        }
    }
}



/* func_801863B0 -- ov_SC02_026 / ov_SC02_026_jr_8017C180
 * TU-verbatim decls (src/ov_SC02_026/ov_SC02_026_jr_8017C180.c):
 *   extern u8 D_801202A0[];                                     (line 387, 586)
 *   extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);   (line 592)
 *   extern s32 func_80047948(s32 a0);                           (line 2206)
 *   extern s32 func_8004787C(s32 a0);                           (line 2207)
 * Not in this TU: func_8012B6D4 (fleet-standard sig), D_8019D2B8 (2-entry fn-ptr
 * table in ov_SC02_026 tail.data: func_80180B0C / func_80180B90).
 */

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);

void func_801863B0(void *arg0) {

    extern u8 D_801202A0[];
    extern void (*D_8019D2B8[])(void *);
                 /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
                /* stride 0x10C, 0x60 entries (0x6480) */

    /* Two further V4 slots the original body declared ahead of `pos` but that
     * this function never reads: the target frame is 0x50 with locals at
     * 0x10..0x37 and the first live vector at 0x20, i.e. 0x10 bytes of stack
     * precede `pos`. Dropping them yields a 0x40 frame and shifts every sp
     * displacement by 0x10 (36 mismatches). */
    V4_8017FD58_801863B0 unused[2];
    V4_8017FD58_801863B0 pos;
    V4_8017FD58_801863B0 tmp;
    V4_8017FD58_801863B0 dst;
    Ent_8017FD58_801863B0 *p;
    Ent_8017FD58_801863B0 *e;
    s32 i;
    s32 ang;

    p = (Ent_8017FD58_801863B0 *)arg0;
    D_8019D2B8[p->f2](p);
    e = (Ent_8017FD58_801863B0 *)D_801202A0;
    for (i = 0; i < 0x60; i++, e++) {
        if (e->f0 == 0x12C) {
            pos.x = e->x;
            pos.y = e->y;
            pos.z = e->z;
            ang = func_8012B6D4((s16 *)&p->f4, (s16 *)&e->f4);
            if (*(s16 *)(p->f64 + 0xFC) < 0) {
                ang -= 0x400;
            } else {
                ang += 0x400;
            }
            ang &= 0xFFF;
            pos.x -= func_8004787C(ang) >> 8;
            pos.z -= func_80047948(ang) >> 8;
            tmp.x = e->x;
            tmp.y = e->y;
            tmp.z = e->z;
            dst = tmp;
            if (func_80135888(p->f20, p->f58, (s32)&pos, (s32)&dst) != 0) {
                e->x = pos.x;
                e->z = pos.z;
            }
        }
    }
}

