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
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_8018F74C;
extern u8 D_8018F6BC;
extern u8 D_8018F698;
extern u8 D_8018F674;
extern u8 D_8018F728;
extern u8 D_8018F704;
extern u8 D_8018F6E0;
extern u8 D_8018F650;
extern void func_80145934(void);
extern u8 D_8018F7DC;
extern u8 D_8018F7B8;
extern u8 D_8018F794;
extern u8 D_8018F770;
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
extern unsigned char D_8018EBD4[];
extern unsigned char D_8018EC04[];
extern unsigned char D_8018EC54[];
extern unsigned char D_8018EC84[];
extern unsigned char D_8018ECB4[];
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
extern void (*D_8018ED04[])(void *);
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
extern s32 D_8018EDCC[];
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
extern u8 D_8018EE54[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018EE5C;
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
extern int D_801E5BA8;
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
extern s32 D_801E5BAC;
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
extern s32 D_8018EE8C;
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
extern void (*D_8018EF34[])(void);
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
extern void (*D_8018EF58[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018EF48;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018EF6C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018EF78[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018EF88[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018EFA0[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018EF90;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018EFB4[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018EFD0[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018EFC0;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018EFE4[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018EFF8[])(void);
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
extern s32 D_8018F00C;
extern void (*D_8018F034[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018F014;
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
extern int (*D_8018F080[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018F084[])(void);
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
extern unsigned short D_8018F4E8[];
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
extern void (*D_8018F4F8[])(void);
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
extern int D_801E5BE0;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018F520[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018F500;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018F510;
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
extern void (*D_8018F560[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018F568[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018F534;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018F574[])(void);
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
extern u8 D_8018F544;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801E5BE8;
extern s32 D_801E5BF4;
extern s32 D_801E5BF8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018F5B0[])(s32 *);
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
extern s32 D_8018F584[];
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
extern s32 D_801E5BF0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018F800[])(void);
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
extern char D_8018F620[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018F8A4[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018F9F8[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018F814;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018FA00[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018F824;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018F844;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018FA08[])(void);
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
extern void (*D_8018FA30[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018FA3C[])(void);
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
extern void (*D_8018F8B0[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018FAE0;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018EBC4[];
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
extern unsigned char D_8018FAF4[];
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
extern s8 D_8018FB30[];
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
extern u16 D_8018FB78;
extern u16 D_8018FB7A;
extern u16 D_8018FB7C;
extern s32 D_8018FB80;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018FB88;
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
extern int D_8018F894;
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
extern unsigned int D_8018FC0C[];
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
extern void (*D_8018FCBC[])(void);
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
extern u16 D_8018FCEC[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018FD50;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801E5C00[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018FD74[])(void);
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
extern int D_801E5C58[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018FDBC[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018FDAC;
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
extern char D_801E5054[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018FDC4[])(void);
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
extern void (*D_8018FE18[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018FDE0;
extern s16 D_8018FE14;
extern s16 D_8018FE12;
extern s16 D_8018FE10;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018FE24[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E5CB8;
extern u8 D_801E5CB9;
extern u8 D_801E5CBA;
extern u8 D_801E5CBB;
extern u8 D_801E5CBC;
extern u8 D_801E5CBD;
extern u8 D_801E5CBE;
extern u8 D_801E5CBF;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018FE34[])(void);
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
extern s32 D_801E5CF8;
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
extern void (*D_8018FE78[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018FEF4[];
extern s32 D_8018FF14[];
extern u8 D_8018FF90[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018FFB0[];
extern u8 D_8018FFD0[];
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
extern void (*D_8019006C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801900E8[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801E5064;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801900F4[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801900FC[])(void);
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
extern void (*D_801901C4[])(void);
extern void func_80166618(void *a0);
extern void (*D_801901D4[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801901E4[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801901F0[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80190150[];
extern u8   D_80190164[];
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
extern void (*D_80190208[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80190210[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80190218[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80190220[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80190228[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80190230[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80190238[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801902EC[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801902F4[])(void);
extern void func_80169F00(void *a0);
extern char D_801902A4[];
extern char D_80190264[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8019032C[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80190338[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80190380[])(void);
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
extern void (*D_801903FC[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E6018;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801903F0[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80190434[];
extern unsigned short D_8019043C[];
extern unsigned short D_80190444[];
extern unsigned char D_801E6020[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E6018;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8019044C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E6154;
extern M2C_UNK D_801E6158;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E60E0;
extern void (*D_8019047C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E615C[];
extern u8 D_801E6164[];
extern u8 D_801E6114[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80190484[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801904A0[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801904A8[])(void);
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
extern void (*D_80190510[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801904B4;
extern u8 D_801904C0;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80190544[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8019054C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801905A0[])(void);
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
extern u16 D_801905D4[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801905C4[];
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
extern s32 D_801905F0;
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
extern void (*D_80190668[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80190670[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80190678[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80190680[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80190688[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80190690[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8019069C[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801906A8[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801906B4[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801906C4[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_801906D4[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_801906DC[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_801906E4[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_801906EC[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_801906F4[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_801906FC[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80190704[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8019070C[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80190714[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8019071C[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80190724[])(void);
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
extern void (*D_8019072C[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80190734[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8019073C[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80190744[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8019074C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80190754[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8019075C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80190764[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8019076C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80190774[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8019077C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80190784[])(void);
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
extern void (*D_801907C8[])(void);
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
extern M2C_UNK D_8019078C;
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
extern void (*D_801907F8[])(void);
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
extern void (*D_80190834[])(void);
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
extern void (*D_8019088C[])();
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
extern void (*D_8019089C[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_801908A4[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_80190A0C[])();
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
extern void (*D_80190A18[])();
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
extern M2C_UNK D_801E52AC;
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
extern s16 D_801E7AB0;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern short D_801E7B24;
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
extern s32 D_801E6CC4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E6CEC;
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
extern s16 D_801E6CA8;
extern s32 func_8017A3B0(void);
extern short D_801E6CE4;
extern short D_801E6CE0;
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
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012BE98(s32 a0, u16 *a1);
extern s16 D_801E7A68;
extern s16 D_801E7A6A;
extern s16 D_801E7A74;
extern void func_8017AE2C(s32 param_1);
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801E6CAC;
extern u16 D_801E6D2C;
extern u16 D_801E6D2E;
extern u16 D_801E6D30;
extern void func_8017B1D8(void);
extern s32 func_8017B238(s32 param_1, s32 param_2);
extern s32 func_8017B368(s32 param);
extern s32 func_8017B490(s32 param);
extern s32 func_8017B614(s32 param_1, s32 param_2);
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern u8 D_8012694C;
extern s16 D_801E6D24;
extern s16 D_801E6D26;
extern s16 D_801E6D28;
extern s16 D_801E6D1C;
extern s16 D_801E6D1E;
extern s16 D_801E6D20;
extern void func_8017B7A8(void);
extern s16 D_801E6D3C;
extern s16 D_801E6D3E;
extern s16 D_801E6D40;
extern s16 D_801E6D44;
extern s16 D_801E6D46;
extern s16 D_801E6D48;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801E6D34;
extern short D_801E6D36;
extern short D_801E6D38;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801E6CCC;
extern SV4 D_801E6CD4;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801E6CF4[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801E6CF0)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80190BF4[])(void);
extern void func_8017BE60(void *a0);
extern void (*D_80190C94[])(void);
extern void func_8017BE9C(void *a0);
extern void (*D_80190C9C[])(void);
extern void func_8017BED8(void *a0);
extern void (*D_80190CA4[])(void);
extern void func_8017BF14(void *a0);
extern u8 *func_8012913C(s32 a0);
extern s32 func_8012C750(s32 a0);
extern void func_8017BF50(s32 a0);
extern void func_8017C094(void);
extern void func_8017C100(s32 param_1);
extern void func_8017C1AC(s32 param_1);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32*, s32);
extern void func_8012B260(u8 *a0);
extern void func_8017C1EC(s32 a0);
extern void func_8017C2B0(s32 a0);
extern void (*D_80190CC4[])(void);
extern void func_8017C338(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_8017C374(s32 param_1);
extern void func_8017C538(u8 *p);
extern void (*D_80190CCC[])(void);
extern void func_8017C5CC(void *a0);
extern u8 D_80190CB8;
extern void func_8017C608(s32 a0);
extern void func_8017C6AC(int a0);
extern void func_8017C710(s32 arg0);
extern void (*D_80190CE4[])(void);
extern void func_8017D5F0(void *a0);
extern void func_8001C214(s32, s32);
extern u32 D_80190CD4;
extern void func_8017D62C(s32 arg0);
extern void func_8017D6A8(void);
extern void (*D_80190D1C[])(void);
extern void func_8017D6B0(s32 *param_1);
extern void func_8017DA08(void *arg0);
extern s32 func_8012AD50(void *arg0);
extern Ent_8017D6EC D_801E6F58[];
extern void func_8017D6EC(void *arg0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8017D9B8(void);
extern void func_8017DAC4(void *arg0);
extern void func_8017D77C(s32 *arg0);
extern void (*D_80190CEC[])(void);
extern void func_80017714(void *);
extern u32 D_801E6FE8;
extern u16 D_80190D24[];
extern u16 D_801E6FEC[];
extern s32 D_80190D44;
extern void func_8017DC0C(void);
extern void func_8017E038(void *arg0);
extern s32 func_8017DC98(s32 param_1);
extern s32 func_8017DCE8(void);
extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8001BFD0(void);
extern s32 func_8017DD7C(s32 a0);
extern void func_800D1EBC(void);
extern void func_8017DE2C(void);
extern s32 func_8017DE4C(void *a0);
extern void (*D_80190D64[])(void);
extern void func_8017DF34(void *a0);
extern void (*D_80190D6C[])(void);
extern void func_8017DF70(void *a0);
extern void (*D_80190D78[])(void);
extern void func_8017DFAC(void *a0);
extern void (*D_80190D84[])(void);
extern void func_8017DFE8(void *a0);
extern s32 D_80127050;
extern void func_8017E024(void);
extern void (*D_80191060[])(void);
extern void func_8017E038(void *a0);
extern void func_8017E074(void *a0);
extern void func_8017E088(void *a0);
extern void (*D_80191068[])(void);
extern void func_8017E0C0(void *a0);
extern void func_8017E0FC(u8 *a0);
extern void func_8017E110(void);
extern void func_8012A094(s32 a0);
extern void func_8017E1F4(void *a0);
extern u8  D_801269E8;
extern void func_8017E130(void);
extern void (*D_80191070[])(void);
extern void func_8017E264(void *a0);
extern s16 D_8018D530[];
extern void func_8017E26C(void *a0, u8 *a1);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017E3AC(s32 param_1);
extern void func_80184CB8(s32*, s32);
extern void func_8017E5A0(void * arg0);
extern void (*D_801912A8[])(void);
extern void func_8017E760(void *a0);
extern void func_8012A828(s32 *a0, s32 a1);
extern void func_8017E79C(short *a0);
extern void (*D_801912C8[])(void);
extern void func_8017E810(void *a0);
extern void func_80178CBC(s32*, s32);
extern void func_8017E84C(void * arg0);
extern void func_8017E878(void * arg0);
extern void func_8012C588(s32, s32);
extern void func_8017E99C(void);
extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern void func_8017E5A0(void *arg0);
extern void func_8017E9C0(void *arg0);
extern short D_80191074;
extern void func_8017EAAC(void * arg0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8017E79C(short*);
extern void func_8017EBA0(s32 a0);
extern void func_8017E7CC(void);
extern void func_8017EBE0(u8 *a0);
extern void func_8017F02C(void * arg0);
extern void (*D_8019155C[])(void);
extern void func_8017F058(void *a0);
extern void func_8017F094(void * arg0);
extern s32 func_8017F0C0(void);
extern void func_80029124(s32 arg0, s32 arg1);
extern void func_8017F108(void);
extern void func_80029514(int);
extern void func_8017F1A8(void);
extern void func_8017F28C(void * arg0);
extern void (*D_801916E4[])(void);
extern void func_8017F5BC(void *a0);
extern void func_80178CBC(s32 *a0, s32 a1);
extern short D_80191694;
extern short D_801915EC;
extern void func_8017F5F8(void *a0);
extern void func_8017F6D8(void *a0);
extern void func_8017F7B8(void *a0);
extern void func_8017F898(void *a0);
extern void func_8017FA34(void);
extern void func_8017FCD8(void * arg0);
extern void (*D_80191814[])(void);
extern void func_8017FF34(void *a0);
extern void (*D_801918E4[])(void);
extern void func_801800E0(void *a0);
extern s32 func_8018011C(void);
extern void func_8018015C(void);
extern void func_80180164(void * arg0);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32 *a0, s32 a1);  /* fleet-canonical sig (TU L3775) */
extern void func_80184C90(s32);
extern void func_80184ED4(s32, s32, s32, s32);
extern short D_801918F4;
extern short D_801B65B8;
extern void func_8018034C(void *arg0);
extern void (*D_801919C4[])(void);
extern void func_8018048C(void *a0);
extern s32 func_80184DD0(s32 a0);
extern s32 D_80191918[];
extern void func_80180504(s32 a0);
extern s32 func_80180544(void);
extern void func_80180580(void *arg0);
extern s32 func_8012BD14(s32 a0);
extern s32 func_80180814(void *a0);
extern short D_801919E0;
extern short D_801B6614;
extern void func_80180888(void *arg0);
extern void func_8012E88C(s32 a0);
extern void func_80184C90(s32 a0);
extern short D_801919E8;
extern short D_801B9B50;
extern void func_801808FC(void *a0);
extern void func_801809DC(void * arg0);
extern void (*D_80191A80[])(void);
extern void func_80180B6C(void *a0);
extern void func_80180C0C(short *a0);
extern s32 func_801848DC(void);
extern s32 func_8018625C(void *);
extern s32 func_80178BF8(void);
extern s32 func_80180CC0(void *a0);
extern s32 func_80178BF8();   /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2541) */
extern s16 D_801E7010;
extern s16 D_801E7012;
extern s32 func_80180D38(void *a0);
extern s32 func_80185BE0(s32 a0);
extern s32 func_80184FA4(s32 a0);
extern u8 D_801B6620[];
extern void func_80180EE8(void *a0);
extern void func_80181020(void *a0);
extern void func_80181244(void * arg0);
extern void func_801812D0(void * arg0);
extern void (*D_80191B20[])(void);
extern void func_801812FC(void *a0);
extern void func_80181338(void * arg0);
extern void func_80181364(s32 a0);
extern void func_80181474(void * arg0);
extern s32 func_80181564(void *a0);
extern void func_8018170C(void * arg0);
extern void func_8018178C(void * arg0);
extern void (*D_80191BDC[])(void);
extern void func_80181924(void *a0);
extern s32 D_801D7598;
extern s32 D_801D2200;
extern void func_80181998(void);
extern s32 D_801E7018;
extern void func_801819B0(void);
extern void func_8012A828(s32 *, s32);
extern void func_80178CBC(s32 *, s32);
extern s32 D_80191B3C;
extern s32 D_80191B74;
extern void func_801819C8(void *arg0);
extern void func_80181A28(s32 a0);
extern void func_801815DC(void *arg0);
extern void func_80181A68(void *arg0);
extern void func_801816A8(void *arg0);
extern void func_80181B34(void *arg0);
extern void func_80184ED4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8018170C(void *a0);
extern u8 D_801B662C[];
extern void func_80181BEC(void *arg0);
extern void func_80181738(void *arg0);
extern void func_80181C78(void *arg0);
extern void func_801817B8(void *arg0);
extern void func_80181DC4(void *arg0);
extern s32 func_80181EFC(void *a0);
extern void func_80181F70(void *arg0);
extern void func_80181FE4(void *a0);
extern void func_80184CB8(s32 *a0, s32 a1);
extern void func_801821A8(short *a0);
extern void (*D_80191EE4[])(void);
extern void func_8018233C(s32 *param_1);
extern void func_80182490(short *a0);
extern s32 func_80182544(void *a0);
extern s32 func_801825BC(void *a0);
extern void func_8018276C(void *a0);
extern void func_801828B0(void *a0);
extern void func_801821A8(short*);
extern void func_80182920(void *arg0);
extern void func_80182ACC(void *a0);
extern void func_80182B58(void *arg0);
extern void func_80182BCC(void *a0);
extern void (*D_80192014[])(void);
extern void func_80182C98(void *a0);
extern s32 D_801D7E84;
extern s32 D_801D6C98;
extern void func_80182D0C(void);
extern void func_80182D24(void *arg0);
extern void func_80182D84(s32 a0);
extern s32 func_80182DC4(void);
extern void func_80182E00(void *arg0);
extern void func_80182C24();
extern void func_80182ED8(void *arg0);
extern void func_80182F18(void *a0);
extern void func_801831AC(void * arg0);
extern void func_8018330C(short *a0);
extern void (*D_8019211C[])(void);
extern void func_80183438(void *a0);
extern void func_80183474(void * arg0);
extern void func_801834A0(void * arg0);
extern void func_801834CC(void * arg0);
extern void func_801834F8(s32 a0);
extern void func_80183538(s32 a0);
extern void func_801831AC(void *arg0);
extern void func_80183674(void *arg0);
extern void func_801831D8(s32 *a0);
extern void func_801836C0(s32 *a0);
extern void func_8018370C(void * arg0);
extern void func_80183938(void *arg0);
extern void (*D_80192230[])(void);
extern void func_80183A68(void *a0);
extern void func_80183AA4(short *a0);
extern void func_80183AD0(s32 a0);
extern s32 func_80183B10(void);
extern void func_80183B4C(void *arg0);
extern s32 func_801839A8();
extern void func_80183B8C(int param_1);
extern s32 func_80183D80(void *a0);
extern void func_80183DF4(void * arg0);
extern void (*D_80192414[])(void);
extern void func_80184130(void *a0);
extern void func_8018416C(s32 a0);
extern void func_801841AC(s32 a0);
extern void func_801841EC(s32 a0);
extern s32 func_8018422C(void);
extern void func_80184268(short *a0);
extern void func_80184298(short *a0);
extern void func_801842C8(short *a0);
extern void func_801842F8(short *a0);
extern void func_80183FA8(s32 *a0);
extern void func_80184328(s32 *a0);
extern void func_80183DF4(void*);
extern void func_801843C4(s32 *a0);
extern void func_80183E20(void *arg0);
extern void func_80184460(void *arg0);
extern void func_8018479C(void *a0);
extern void func_801847AC(void *a0);
extern s32 func_8012E57C(s32 a0, s32 a1);
extern u8 D_801B85A8;
extern s32 func_801847BC(void *a0, void *a1);
extern void func_80184858(void *a0);
extern void func_80184884(void *a0);
extern void func_801848B0(void *a0);
extern u16 D_80126B62;
extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CB64(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern s32 aF801848DC();
extern s32 D_801E7998;
extern s16 D_801B86BC[];
extern s16 D_801B86F0[];
extern s32 D_801B85BC[][8];
extern s32 func_80184B04(s32 arg0);
extern s32 func_80184960(s32 a0);
extern s32 func_80184960(s32 arg);
extern void func_80184AC4(void *a0);
extern void func_80184A90(void *a0);
extern short D_800BA2BA;
extern void (*D_801B8720[])(void);
extern void func_80184B2C(void *a0);
extern void func_80184B68(void);
extern void func_80184B70(void *a0, s32 a1, s32 a2);
extern s32 func_80184BD0(u8 a0, u8 a1, u8 a2, u8 a3);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_80184C28(void *a0, s32 a1);
extern s32 D_801B8728;
extern void func_80184CB0(void *a0);
extern void func_8012E8A8(u8 *a0);
extern s32 func_80184D00(void);
extern s32 func_80184D5C(void);
extern s32 aF80184DD0();
extern s32 func_80184E44(void);
extern void func_80184EA0(void);
extern void func_8012B200(u8 *a0);
extern s32 func_8018516C(s32 a0);
extern void (*D_801B8740[])(void);
extern void func_801851B4(void *a0);
extern void func_801851F0(void);
extern void func_801851F8(void);
extern void func_80185200(void);
extern void func_80185208(void);
extern void func_80185210(void);
extern s32 D_801E7A88;
extern s32 D_801E799C;
extern void func_80185218(void *a0);
extern void func_8018525C(void);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_801C03D8[];
extern s32 D_801B8738[];
extern void func_80185264(s32 a0);
extern void func_80185978(s32 a0);
extern void func_80185904(s32 a0);
extern void func_801859D8(s32 a0);
extern void func_8018589C(s32 a0);
extern void (*D_801B8A18[])(s32);
extern void func_801852EC(s32 a0);
extern void func_8001C97C(s32 a0);
extern void *func_80185C6C(void *a0);
extern s32 D_801B8748[][2];
extern u32 D_801B8760;
extern u32 D_801B877C;
extern s16 D_801B8788[];
extern Blk12_801854C4 D_801B8770;
extern void func_801854C4(s32 a0);
extern void func_80185D70(void *a0);
extern void func_80185664(void *a0);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern s32 func_80185EEC(void);
extern void func_801856E0(s32 a0);
extern void func_801857AC(void);
extern void func_801857CC(s32 a0);
extern void func_80185A58(s32 a0, s32 a1);
extern void func_8018602C(s32 a0, s32 a1);
extern void func_80185AB0(s32 a0);
extern void func_80185B10(s32 a0);
extern void func_80185B58(s32 a0);
extern void func_80185BA8(s32 a0);
extern s32 func_80185D10(void *a0);
extern s32 func_801862A8(void *a0);
extern void * func_80185C6C(void *a0);
extern void func_80185F20(void *a0);
extern void aF80185EEC();
extern void func_80185F54(void *a0, s32 a1, s32 a2);
extern void func_80185FB8(s32 a0, s32 a1, s32 a2);
extern void (*D_801B8A3C[])(void);
extern void func_80186084(void *a0);
extern s32 D_801B8A2C;
extern void func_801860C0(void *a0);
extern void func_8018613C(void *a0);
extern s32 func_8018625C(void *a0);
extern s32 func_801863B4(s32 a0);
extern s16 D_801B8A44[];
extern void func_8012F214(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_801B87D8;
extern s32 D_801E7AAC;
extern void func_80186410(void);
extern s16 D_801E7030;
extern s32 func_80186450(void);
extern void func_80029444(void);
extern void func_801754A8(void);
extern void func_80141C04(void);
extern void func_801864AC(void);
extern u8 D_801151C8[];
extern u16 D_80115112;
extern u8 D_80115138[];
extern u8 D_80115148[];
extern s32 D_80115130;
extern u8 D_800B9A15;
extern s16 D_801E7708;
extern s32 D_801E7700;
extern s32 D_801E7704;
extern s16 D_801E7790;
extern s16 D_801E7798;
extern s16 D_801E779C;
extern s16 D_801E77A0;
extern s16 D_801E77A4;
extern s16 D_801E77A8;
extern s16 D_801E77AC;
extern s32 D_801E7778;
extern s32 D_801EC928;
extern s32 D_801E930C;
extern s32 D_801E9968;
extern s32 D_801B9410;
extern u8 D_801B94A4[];
extern s32 D_801B946C[];
extern s32 resLoad_lastId;
extern s32 func_800149E0(s32 a0);
extern void func_80137B80(void);
extern s32 func_801376E8(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_80139A68(s32 a0, u16 a1);
extern s16 func_8014168C(s16 a0);
extern void func_80188778(void);
extern s32 func_80189540(s16 a0, s16 a1);
extern s16 func_80189E54();
extern void func_801878E8(void);
extern s16 D_801B9414[];
extern void func_801EA0E4(s32 a0);
extern void func_80189EA0(void);
extern s32 D_801EC970;
extern void func_801880EC(void);
extern s32 func_80188428(void);
extern void  func_80024054(void *a0, void *a1);
extern s32  *func_800D2650(s32 *, void *, s32, s32, s32, s32);
extern s32   func_800D27DC(s32, s32 *, void *, s32, s32);
extern s32  *func_800D29F8(s32, s32, void *, s32, s32);
extern s32  *func_80189214(s32 *, void *, s32, void *, s32);
extern s32   func_80188B84(void *, s32, s32, s32, s32 *);
extern s32 * func_801889B8(s32 *ot, Panel_8017E978_801889B8 *w0, s16 idx);
/* ==== end §8b carried decl layer ==== */

#include "common.h"

/* func_80188E1C — ov_SC04_018 / ov_SC04_018_jr_801878E8, 254 ins, jtbl_801E599C (8 entries,
 * minval 7 -> `addiu $a0,$a0,-7` + HImode re-extension, so the switch index type is short).
 *
 * Modelled on the ALREADY-MATCHED structural twin in the same overlay,
 * src/ov_SC04_018/ov_SC04_018_jr_8013FFD8.c:1065 `func_8014032C` — same family:
 *   `result = D_801117EC;` default, `switch ((short)param_1)`, `((short)param_2)` at every use,
 *   `func_800291B4(D_8018E2C8[...]) & 0xFF` -> `result = D_8018E388[uVar3];`.
 * Case bodies are emitted in SOURCE order, so the source order here is 10,7,8,13,14,11,default
 * (read off the block order after the jr: 80188E70, 80188EB8, 80188F28, 80189004, 80189044,
 * 80189108, 801891E0).
 *
 * Cases 9 and 12 are ABSENT from the source: their jtbl slots (indices 2 and 5) point at the
 * default label 0x801891E0, which is also the out-of-range target of `beqz $v0,.L801891E0`.
 *
 * Three register/shape constraints read off the target:
 *  (a) each `& 0xFF` temp is BLOCK-SCOPED. A single function-scope temp gives one pseudo whose
 *      live range crosses the calls in cases 13/14, so gcc pins it to $s0; the target keeps it in
 *      $v1 / $v0 (dead before the call) and uses $s0 only for the value that IS live across a call.
 *  (b) case 14 uses u8 (QImode) locals. `lbu` into an s32 local is provably <=0xFF, so gcc folds
 *      `(v & 0xFF)` away; the target emits `andi $v1,$a0,0xFF` for the compare and
 *      `andi $s3,$a0,0xFF` for `n + 0x62`, which is the QImode-pseudo widening pattern.
 *      Case 13 has NO such andi, so there the local is s32 — the two cases are deliberately
 *      asymmetric (cookbook §160d). Case 14 also REUSES that one variable for `v + 1`
 *      (`v = v + 1`, not `u8 n = v + 1`): two pseudos gave `addiu $v0,$a0,1; andi $s3,$v0`,
 *      one pseudo gives the target's in-place `addiu $a0,$a0,1; andi $s3,$a0`. That was the
 *      last 2-instruction residual.
 *  (c) in case 11 the arms whose `lui/addiu $s1,%hi/%lo(sym)` sits BEFORE the branch (filling the
 *      `lw` load-delay slot) are assign-then-conditionally-override, not if/else: the address
 *      materialisation has to be in the SAME basic block as the load for the post-reload scheduler
 *      to hoist it. The arm at .L801891B4 keeps its `nop`, so that one is a plain `if`.
 */

extern s32 func_800291B4(s32 arg);
extern void func_80139A68(s32 a0, u16 a1);
extern u8 D_80115148[];

s32 func_80188E1C(s32 param_1, s32 param_2) {
    /* [T51] scoped in: these must not constrain the rest of the TU (cookbook §103). */
    extern void *func_80189DDC(s32 a0);
    extern s16 D_80115126;
    extern u8 D_801117EC[];
    extern u8 *D_801E76F4;
    extern u8 *D_801E76FC;
    extern u8 D_801E77B8[];
    extern u8 D_8018E2C8[];
    extern void *D_8018E388[];
    extern void *D_801E3D58[];
    extern void *D_801B93D4[];
    extern void *D_801B93F0[];
    extern s32 *D_801E7774[];
    extern s16 D_8010EDEE;  /* +2 field of the 0xC-byte record table (resident.c:1395) */
    extern u8 D_8010EDF2;   /* +6 field of the same 0xC-byte record */
    extern s16 D_800A6586[];
    extern u8 D_801E8CEC[];
    extern u8 D_801E9174[];
    extern u8 D_801ECAA8[];
    extern u8 D_801ECAD4[];
    extern u8 D_801ECAEC[];
    extern u8 D_801ECB18[];

    void *result;

    result = D_801117EC;
    switch ((short)param_1) {
    case 10:
        if (D_80115126 != 5) {
            result = D_8018E388[D_801E76F4[(short)param_2]];
        } else {
            result = D_801B93D4[(short)param_2];
        }
        break;

    case 7: {
        s32 t = func_800291B4(D_8018E2C8[(short)param_2]) & 0xFF;
        if (t != 0) {
            s32 idx = t * 0xC;
            if (*(s16 *)((u8 *)&D_8010EDEE + idx) != 0 &&
                D_80115126 == *((u8 *)&D_8010EDF2 + idx)) {
                result = func_80189DDC(((short)param_2 & 3) + 6);
                func_80139A68(*(s16 *)((u8 *)&D_8010EDEE + idx), 0);
            } else {
                result = func_80189DDC(5);
            }
        }
        break;
    }

    case 8:
        if (D_80115148[0] != 0) {
            s32 t = func_800291B4(D_8018E2C8[(short)param_2]) & 0xFF;
            if (t != 0) {
                s32 idx = t * 0xC;
                if (*(s16 *)((u8 *)&D_8010EDEE + idx) != 0 &&
                    D_80115126 == *((u8 *)&D_8010EDF2 + idx)) {
                    result = func_80189DDC(((short)param_2 & 3) + 6);
                    func_80139A68(*(s16 *)((u8 *)&D_8010EDEE + idx), 0);
                } else {
                    result = func_80189DDC(5);
                }
            }
        } else {
            s32 t = func_800291B4(D_8018E2C8[(short)param_2]) & 0xFF;
            if (t != 0) {
                result = D_8018E388[t];
            }
        }
        break;

    case 13: {
        s32 e = D_801E76FC[(short)param_2];
        if ((func_800291B4(e + 0x62) & 0x80) != 0) {
            result = D_801E3D58[e];
        }
        break;
    }

    case 14: {
        u8 v = D_801E77B8[(short)param_2];
        if (v != 0xFF) {
            s32 code;
            v = v + 1;
            code = v + 0x62;
            if ((func_800291B4(code) & 0xF0) == 0xC0) {
                result = func_80189DDC(((short)param_2 & 1) | 6);
                func_80139A68((s16)(D_800A6586[v] * 9 / 10), 0);
            } else if ((func_800291B4(code) & 0xF0) == 0xE0) {
                result = D_801E8CEC;
            }
        }
        break;
    }

    case 11:
        if (D_80115126 == 4) {
            if (D_80115148[0] == 0) {
                result = D_801ECAA8;
                if (D_801E7774[(short)param_2] == 0) {
                    result = D_801B93F0[(short)param_2];
                }
            } else {
                s32 *p = D_801E7774[(short)param_2];
                if (p != 0) {
                    result = D_801ECB18;
                    if (p[1] != 0) {
                        result = D_801ECAEC;
                    }
                } else {
                    result = D_801ECAD4;
                }
            }
        } else {
            if (D_801E7774[(short)param_2] != 0) {
                result = D_801E9174;
            }
        }
        break;

    default:
        result = func_80189DDC(0);
        break;
    }
    return (s32)result;
}


extern s16 func_8014168C(s16 a0);

s32 *func_80189214(s32 *ot, void *a1p, s32 idx, void *a3p, s32 tag) {

    typedef struct { u32 *ot; u32 pad[4]; } Env_8018C960_80189EA0;   /* 0x14 stride */

    extern u8  D_80115138[];
    extern u8  D_80115140[];
    extern u8  D_80115148[];
    extern u8  D_80115158[];
    extern u16 D_80115116;
    extern u16 D_8011511A;
    extern u16 D_801B8DDA;
    extern u16 D_801B8DEE;
    extern s16 D_800B9A02;
    extern Env_8018C960_80189EA0 D_800AE7BC[];

    register s32 zr __asm__("$0");
    u16 *pb;
    u16 *p;
    s32  c;
    register s32 tv __asm__("$3");
    s32  idx2;
    s16  t;
    register u32 c0 __asm__("$3");

    c = D_80115138[(s16)idx];
    *(u32 *)ot = 0x4000000;
    tv = tag;
    *((u8 *)ot + 0xC) = 0x30;
    *((u8 *)ot + 0xD) = 0x48;
    ot[1] = tv | 0x64000000;
    *(s16 *)((u8 *)ot + 0xE) = 0x4056;
    idx2 = idx + zr;

    if (c < 10) {
        t = ((s32 (*)(s32))func_8014168C)((s16)idx) * 2;
    } else {
        t = (D_80115148[(s16)idx * 2] - D_80115140[(s16)idx]) * 2;
    }

    p = (u16 *)(t * 2 + (s32)a1p);
    *(s16 *)((u8 *)ot + 0x8) = p[0] - 8;
    *(s16 *)((u8 *)ot + 0xA) = p[1];
    *(s16 *)((u8 *)ot + 0x12) = 8;
    *(s16 *)((u8 *)ot + 0x10) = 8;

    pb = (u16 *)&D_800B9A02;
    c0 = ot[0];
    ot[0] = (c0 & 0xFF000000) | (D_800AE7BC[*pb].ot[2] & 0xFFFFFF);
    D_800AE7BC[*pb].ot[2] =
        (D_800AE7BC[*pb].ot[2] & 0xFF000000) | (((u32)ot) & 0xFFFFFF);

    ot += 5;

    if (c >= 10) {
        s32 m = D_8011511A;
        if ((m == (s16)idx2) && ((D_80115116 & 8) != 0)) {
            s16 j;
            s32 k;
            u8 *q;
            s16 y;
            u16 *pb2;
            u32 m24;
            u32 mhi;
            s32 eight;

            j = 0;
            k = m;
            eight = 8;
            __asm__ volatile("" :: "r"(pb), "r"(pb), "r"(pb), "r"(pb), "r"(pb));
            pb2 = (u16 *)&D_800B9A02;
            m24 = 0xFFFFFF;
            mhi = 0xFF000000;
            q = (u8 *)ot + 0x14;
            for (; j < 2; j++) {
                if (j == 0) {
                    if (D_80115140[k] == 0) {
                        continue;
                    }
                    q[-7] = 0x30;
                    y = D_801B8DDA - 2;
                } else {
                    s32 k2 = k * 2;
                    if ((((s8 *)D_80115158)[k2] - ((s8 *)D_80115140)[k]) < 7) {
                        continue;
                    }
                    q[-7] = 0x38;
                    y = D_801B8DEE + 1;
                }
                *(s16 *)(q - 10) = y;
                __asm__("" ::: "memory");
                *((u32 *)ot) = 0x4000000;
                q[-8] = 0x78;
                *((u32 *)(q - 0x10)) = 0x64808080;
                *(s16 *)(q - 6) = 0x4056;
                *(s16 *)(q - 0xC) = ((s32 *)a3p)[2] + ((s32 *)a3p)[3] - 0xC;
                *(s16 *)(q - 4) = eight;
                *(s16 *)(q - 2) = eight;
                *((u32 *)ot) = ((*(u32 *)ot) & mhi) | (D_800AE7BC[*pb2].ot[2] & m24);
                {
                    register u32 *op __asm__("$4");
                    op = D_800AE7BC[*pb2].ot;
                    op[2] = (op[2] & mhi) | (((u32)ot) & m24);
                }
                q += 0x14;
                ot += 5;
            }
        }
    }
    return ot;
}


/* func_80189540 — tier 3 (compiler-internals).  STATE: MATCH (551/551).
 *
 * ==== WAVE-3 RE-VERIFICATION (2026-08-11) ====
 * Re-gated against the CURRENT carve
 *   asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_80188E1C/func_80189540.s
 * -> MATCH (551 ins).  Two edits were needed vs the archived backlog copy:
 *  (1) SIGNATURE.  The archived copy had been "fixed" to `s32 arg0` (to agree
 *      with the host TU's file-scope prototype); that costs exactly -2 ins:
 *      the target's `addiu a0,a0,-1; sll 16; sra 16; sltiu 0xF` switch-index
 *      range check is the HImode re-extension of a `short` parameter after the
 *      minval subtract.  With `s32` gcc emits `addiu; sltiu` only (549 ins).
 *      The first parameter IS `s16`.  -> integration: the host TU's
 *      src/ov_SC04_018/ov_SC04_018_jr_80188E1C.c:3093
 *      `extern s32 func_80189540(s32 a0, s16 a1);` must become `(s16, s16)`
 *      or the TU dies with a HARD "conflicting types" (byte-probed).
 *  (2) SCOPE of Rec / D_801E7774.  The host TU already carries a BLOCK-scope
 *      `extern s32 *D_801E7774[];` (:3162) inside another function.  A
 *      FILE-scope `extern Rec *D_801E7774[];` here is a HARD "conflicting
 *      types" error; the same decl at BLOCK scope is only a
 *      "type mismatch with previous external decl" WARNING (both byte-probed).
 *      So the Rec typedef + the D_801E7774 decl now live inside `case 11`.
 *      Codegen is unchanged — still MATCH at 551.
 * Every other extern in this file was diffed against the host TU: all agree
 * (func_8002D4C8/800291B4/800291A0/80189E54/800D0F8C/800D0EC4/800D0F0C/
 *  800D0FE0/800D128C/80029124/80029514/8017ADE8/80139A68, D_801E7030,
 *  D_801E76FC, D_801E76F4, D_801E77B8, D_800A6586, D_8010EDEE, D_8010EDF2,
 *  D_80115126, D_80115148, D_801E7700, D_801E3CEC, D_80115112, D_801EC928)
 * or are absent from the host TU entirely (D_8011511A, D_8011514C/4E,
 *  D_8010EDEC, D_8010EDF1, D_801E778C, D_801E96C8, D_801B9420, D_801E3E1C,
 *  D_801E9664, D_801E92E0, D_801E7794, D_801E96A4, func_80186E24,
 *  func_80189E14, func_80139A44).
 * ==== end wave-3 note ====
 *
 * Overlay ov_SC04_018 (byte-identical twin ov_SC04_019), carve region
 * ov_SC04_018_jr_801878E8 (551 ins).  NB the prompt's asm path said
 * `jr_8017AE2C`; the real carve is `jr_801878E8`:
 *   asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_801878E8/func_80189540.s
 *
 * ---- TIER-3 CRACKS (the 4 residual ins -> 0), both from reading vanilla
 *      tools/reference/gcc-2.7.2/ sources.  GENERALIZABLE — cookbook fodder. ----
 *
 * T3-A (was idx 255/256, case 10 `move s0,s1` vs `sra` order — S2-boost class):
 *   ROOT CAUSE chain: (1) the RTL dump showed the order is GENERATION order, not
 *   a sched tie: cse folds the (s16) arg extension's `sra` INTO the a0-load
 *   position (the original sra insn dies), splitting the sll/sra pair around the
 *   statement-positioned copy.  (2) The target needs the copy SUNK between
 *   `sra` and the a1-copy — only sched1's birthing boost (sched.c:2469
 *   birthing_insn_p: pattern SET(REG,..), REG_N_SETS(dest)==1) does that, and a
 *   `register __asm__("$16")` pin kills it (hard $16 is multi-set function-wide).
 *   (3) Plain-unpinning instead DELETES the copy: local-alloc combine_regs
 *   (local-alloc.c:1722) ties a SET(reg,reg) copy whose source dies there
 *   (byte-seen: 550 ins, copy gone).
 *   LEVER: unpin w10 AND write the copy as an asm-move
 *       __asm__("addu %0,%1,$zero" : "=r"(w10) : "r"(b10));
 *   — an asm SET is NOT a SET(reg,reg), so combine_regs cannot tie it, yet its
 *   PATTERN is still SET(REG, asm_operands), so birthing_insn_p BOOSTS it →
 *   it sinks to just before its first consumer (the a1-copy) = target position;
 *   global-alloc hands the call-crossing pseudo $16 (first callee-saved in
 *   order; $16 free — slot dead at the sll once the copy sinks).  Net-zero
 *   ref-count on b10 (the asm read replaces the copy read) → no K2 ripple.
 *
 * T3-B (was idx 133/135, case 14 lbu dest $s1-vs-$v0 — cse from_plus class):
 *   ROOT CAUSE: cse.c:5577 fold_rtx `from_plus` association: for
 *   (PLUS reg const) it does lookup_as_function(reg, PLUS) in reg's class and
 *   combines the constants (c14 = n14+0x62 → lbu_temp+0x63), so the +1 chain
 *   must be hidden — but the in-place `n14=tbl[i]; n14=n14+1` hides it by
 *   making the load dest BE $s1 (wrong lbu dest).  lookup_as_function validates
 *   entries with exp_equiv_p(...,validate=1) — reg_tick staleness of ANY reg
 *   inside the expr kills the entry.
 *   LEVER: name the load temp, keep the one-statement +1 (right lbu dest), and
 *   stale THE TEMP (not n14) with a dead-output non-volatile re-tie:
 *       t14 = D_801E77B8[i14];  n14 = t14 + 1;
 *       __asm__("" : "=r"(t14) : "0"(t14));   c14 = n14 + 0x62;
 *   cse (both passes) re-SETs t14 → reg_tick[t14]++ → (plus t14 1) fails
 *   validation → NO fold; then FLOW deletes the dead-output asm BEFORE
 *   combine/sched/regalloc ever see it (cse_expr.md §2 boundary #2) → zero
 *   downstream ripple.  (Re-tie on n14 itself instead: 4 mism — it ripples the
 *   later sll temp's allocation.  A "0"-tied t14→n14 asm-copy: +1 ins — reload
 *   materializes the $17 copy because t14 first-fits into the lbu scratch.)
 *
 * ---- tier-2 provenance below (levers L1-L8 still load-bearing) ----
 * Case-body SOURCE ORDER is the asm's block layout order:
 *   {1,2,4,6}, 3, 5, 12, 13, 14, 10, 7, 8, 15, 11   (9 + out-of-range = default)
 *
 * ---- the levers that closed this, in the order they mattered ----
 * L1 CROSS-JUMP TAIL PLACEMENT (-8 ins).  The shared `func_8002D4C8(0x472,0);
 *    return 0;` error tail is an EXPLICIT label (`bad472`) at the very END of
 *    the function, reached by `goto`.  gcc-2.7.2's jump.c keeps the
 *    PHYSICALLY-LAST copy of a merged tail; only a last copy that is a bare
 *    `li a0,0x472` block lets the "jump around jump" inversion turn the four
 *    `beq/bne …; li a0; j tail` triples into single conditional branches to
 *    .L80189DA8.  Writing the call literally at each site instead cross-jumped
 *    into case 3's body and cost 4x2 instructions.
 * L2 `u8`-RETURN BLOCKS THE AND-FOLD.  `extern u8 ((u8 (*)(s32))func_800291B4)(s32)` (NOT
 *    `s32` + an explicit `& 0xFF`).  With `s32`+mask, combine folds
 *    `(and (and x 0xff) 0xf0)` -> `(and x 0xf0)` and the second `andi` reads
 *    the raw call result; the zero_extend from a QImode return does not fold,
 *    so the target's `andi $s0,$v0,0xFF; andi $v1,$s0,0xF0` survives.
 *    (Byte-proven in .run/s46/casc/micro2.c variant a2.)
 * L3 FRAME KNOB.  Target frame is 0x38 (vars=16); ours computes vars=8, so an
 *    8-byte unreferenced local array is carried.  It emits NO code but fixes
 *    all 11 prologue/epilogue offsets.  This is the one honest GUESS in the
 *    file — the real cause of the target's extra 8 bytes of `vars` is unknown.
 * L4 ADDRESS-IN-A-REGISTER for the D_8011514C/D_80115142 pair: a plain
 *    `u8 *q = &D_8011514C` is constant-folded into 4 separate `lui/%lo`; the
 *    asm launder `__asm__("" : "=r"(q) : "0"(&D_8011514C))` forces `la` =
 *    lui+addiu and the target's `0($a1)` / `-0xA($a1)` displacements.
 * L5 DIVISOR from the magic constant: 0x66666667 + `sra 2` is /10, not /5
 *    (0x66666667 + `sra 1` would be /5).  So case 14 is `x * 9 / 10`.
 * L6 REGISTER PINS (cookbook §17/§72).  gcc's global.c allocno priority is
 *    refs/live-length, which consistently gave OUR earlier-born value $s0
 *    where the target gives it to the later-born one.  Pinning splits the tie.
 *    Pins are per-switch-arm so their live ranges are disjoint by control flow;
 *    within an arm every pinned pair was checked for range overlap (the one
 *    real hazard, `slot`/`w10` both on $16, is separated by the `sl16` temp so
 *    `slot` is dead before `w10` is born — verified in the emitted asm).
 * L7 SCHEDULING BARRIER: `__asm__ __volatile__("")` between the volatile
 *    reload and the `->unk4` read in case 11's .L80189CFC path stops gcc's
 *    sched from hoisting `lw ...,4(...)` into the load-delay slot (that single
 *    barrier took the diff 58 -> 5).
 * L8 The `.L80189D80` tail (`func_8002D4C8(0x45D,0); D_80115112++;`) is also
 *    an explicit label (`tail45D`) for the same reason as L1.
 *
 * ---- former tier-2 residual (SOLVED by T3-A/T3-B above) ----
 *  idx 133/135  case 14 lbu dest        -> T3-B (stale-the-temp re-tie)
 *  idx 255/256  case 10 move/sra order  -> T3-A (asm-move + boost sink)
 */








/* ---- functions ---- */
extern void func_8002D4C8(s32, s32);
extern s32 func_800291B4(s32);
extern void func_800291A0(s32, s32);
extern void func_80186E24(void);
extern s16  func_80189E54();
extern void func_80189E14();
extern s32  func_800D0F8C(s32);
extern s32 func_800D0EC4(void);
extern void func_800D0F0C(s32, s32);
extern int func_800D0FE0(int);
extern void func_800D128C(s32, s32);
extern void func_80029124(s32, s32);
extern void func_80029514(s32);
extern s32 func_8017ADE8(s32);
extern void func_80139A44(s32, s32);
extern void func_80139A68(s32, u16);

/* ---- data ---- */
extern u16  D_8011511A;
extern s16  D_801E7030;
extern s16  D_8011514E;
extern u8  *D_801E76FC;
extern s16  D_800A6586[];
extern u8   D_8011514C;
extern u8   D_801E77B8[];
extern u8  *D_801E76F4;
extern s16  D_8010EDEC;   /* record +0x0, s16 (12-byte stride) */
extern s16  D_8010EDEE;   /* record +0x2, s16 */
extern u8   D_8010EDF1;   /* record +0x5, u8  */
extern u8   D_8010EDF2;   /* record +0x6, u8  */
extern s16  D_80115126;
extern u8 D_80115148[];
extern s16  D_801E778C;
extern s32  D_801E96C8;
extern s32  D_801E7700;
extern void (*D_801E3CEC[])(void);
extern s8   D_801B9420[];
extern s32  D_801E3E1C[];
extern s32  D_801E9664;
extern u16  D_80115112;
extern s32  D_801EC928;
extern s32  D_801E92E0;
extern s16  D_801E7794;
extern s32  D_801E96A4;

#define REC_S16(base, idx) (*(s16 *)((u8 *)&(base) + (s32)(idx) * 0xC))
#define REC_U16(base, idx) (*(u16 *)((u8 *)&(base) + (s32)(idx) * 0xC))
#define REC_U8(base, idx)  (*(u8  *)((u8 *)&(base) + (s32)(idx) * 0xC))

s32 func_80189540(s16 arg0, s16 arg1)
{
    /* frame knob: the target's frame is 0x38 (vars=16); ours is vars=8 without
     * this 8-byte unreferenced local. Emits no code. */
    s32 unused_[2];

    switch (arg0) {
    case 1:
    case 2:
    case 4:
    case 6:
        if (arg1 == 2) {
            return -1;
        }
        func_8002D4C8(0x46F, 0);
        D_8011511A = arg1 + 1;
        return 0;

    case 3:
        if (arg1 == 2) {
            return -1;
        }
        D_8011511A = 2;
        func_8002D4C8(0x46F, 0);
        return 0;

    case 5:
        if (arg1 == 1) {
            D_801E7030 = 1;
            func_8002D4C8(0x474, 0);
            return -1;
        }
        if (arg1 == 3) {
            return -1;
        }
        func_8002D4C8(0x46F, 0);
        if (arg1 != 0) {
            D_8011511A = arg1;
        } else {
            D_8011511A = 2;
        }
        return 0;

    case 12:
        D_8011511A = 3;
        D_8011514E = 0;
        func_8002D4C8(0x46F, 0);
        return 0;

    case 13:
    {
        register s32 f13 __asm__("$16");
        register s32 i13 __asm__("$17");
        register s32 c13 __asm__("$18");
        register u8 *q __asm__("$5");
        s16 d;
        i13 = D_801E76FC[arg1];
        c13 = i13 + 0x62;
        f13 = ((u8 (*)(s32))func_800291B4)(c13);
        if ((f13 & 0xF0) != 0x80) {
            goto bad472;
        }
        if (func_80189E54(-D_800A6586[i13]) != 0) {
        L801896C8:
            func_80189E14(3);
            goto bad472;
        }
        func_800291A0(c13, f13 | 0x40);
        func_80186E24();
        __asm__ __volatile__("" : "=r"(q) : "0"(&D_8011514C));
        d = (s8)q[0] - (s8)q[-0xA];
        if (d >= 6) {
            q[-0xA] = q[0] - 5;
        } else if (d < 0) {
            q[-0xA] = q[0];
        }
        func_80189E14(1);
        func_8002D4C8(0x5EE, 0);
        return 0;
    }

    case 14:
    {
        register s32 f14 __asm__("$16");
        s32 i14;
        register s32 n14 __asm__("$17");
        s32 t14;
        s32 c14;
        i14 = arg1;
        t14 = D_801E77B8[i14];
        n14 = t14 + 1;
        __asm__("" : "=r"(t14) : "0"(t14)); /* stales (plus t14 1) in cse; dead output -> deleted by flow */
        c14 = n14 + 0x62;
        f14 = ((u8 (*)(s32))func_800291B4)(c14);
        if ((f14 & 0xF0) != 0xC0) {
            goto bad472;
        }
        func_80189E54(D_800A6586[n14] * 9 / 10);
        func_800291A0(c14, f14 & 0xBF);
        func_80186E24();
        D_801E77B8[i14] = 0xFF;
        func_80189E14(4);
        func_8002D4C8(0x5EE, 0);
        return 0;
    }

    case 10:
    {
        s32 b10 = D_801E76F4[arg1];
        s32 m10;
        s32 w10;
        __asm__ __volatile__("" : "=r"(m10) : "0"(b10));
        if (m10 < 0x6F) {
            register s16 slot __asm__("$16");
            register s16 sraw __asm__("$2");
            s16 val;
            s16 x;
            if (m10 == 0xA) {
                if (func_800D0F8C(0xA) != 0) {
                    goto bad472;
                }
            }
            sraw = ((s16 (*)(void))func_800D0EC4)();
            slot = sraw;
            if (sraw == 0) {
                func_80189E14(2);
                func_8002D4C8(0x45F, 0);
                return 0;
            }
            x = D_801E778C;
            if (x != 0) {
                if (D_80115126 == 0) {
                    val = REC_S16(D_8010EDEC, b10) * (100 - x) / 100;
                } else {
                    val = REC_U16(D_8010EDEC, b10) - x;
                }
            } else {
                val = REC_U16(D_8010EDEC, b10);
            }
            if (func_80189E54(-val) != 0) {
                func_80189E14(3);
                func_8002D4C8(0x472, 3);
                return 0;
            }
            func_8002D4C8(0x5EE, 0);
            __asm__("addu %0,%1,$zero" : "=r"(w10) : "r"(b10));
            func_800D0F0C(slot, w10);
            if (w10 == 0xA) {
                func_80186E24();
            }
        } else {
            if (func_80189E54(-REC_S16(D_8010EDEC, m10)) != 0) {
                goto L801896C8;
            }
            func_800D128C(b10, 0);
        }
        func_80189E14(1);
        return 0;
    }

    case 7:
    {
        s32 c7;
        s32 k7;
        s32 a7;
    L801899B0:
        c7 = (s32)arg1 + 0x2F;
        k7 = ((u8 (*)(s32))func_800291B4)(c7);
        if (k7 == 0) {
            goto bad472;
        }
        a7 = REC_S16(D_8010EDEE, k7);
        if (a7 == 0 || D_80115126 != REC_U8(D_8010EDF2, k7)) {
            func_80189E14(5);
            goto bad472;
        }
        func_80189E54(a7);
        ((void (*)(s32))func_800D0FE0)(c7);
        if (k7 == 0xA) {
            func_80186E24();
        }
        func_80189E14(4);
        func_8002D4C8(0x5EE, 0);
        return 0;
    }

    case 8:
    {
        s32 k8;
        register s32 f8 __asm__("$2");
        register s32 g8 __asm__("$16");
        register s32 t8 __asm__("$2");
        register s32 cv __asm__("$2");
        s32 p8;
        register u16 *c __asm__("$3");
        if ((*(u8 *)D_80115148) != 0) {
            goto L801899B0;
        }
        k8 = ((u8 (*)(s32))func_800291B4)((s32)arg1 + 0x2F);
        if (k8 == 0) {
            goto bad472;
        }
        f8 = REC_S16(D_8010EDEC, k8);
        if (f8 >= 0) {
            D_801E7700 = (s32)&D_801E96C8;
            goto bad472;
        }
        __asm__ __volatile__("" : "=r"(g8) : "0"(f8));
        t8 = g8 & 0x4000;
        if (t8 != 0) {
            p8 = ((s32 *)D_801E3CEC)[k8];
        } else {
            p8 = D_801E3E1C[(REC_U8(D_8010EDF1, k8) - 0x14) >> 1];
        }
        D_801E7700 = (s32)&D_801E9664;
        func_80139A44(p8, 0);
        c = &D_80115112;
        cv = *c;
        cv = cv + 1;
        *c = cv;
        return 0;
    }

    case 15:
    {
        register u16 f15 __asm__("$16");
        register s32 t15 __asm__("$2");
        s32 c15;
        s32 k15;
        s32 n15;
        c15 = (s32)arg1 + 0x2F;
        k15 = ((u8 (*)(s32))func_800291B4)(c15);
        f15 = REC_U16(D_8010EDEC, k15);
        n15 = REC_U8(D_8010EDF1, k15);
        t15 = f15 & 0x4000;
        if (t15 != 0) {
            s32 m15;
            __asm__ __volatile__("" : "=r"(m15) : "0"(n15));
            func_80029124(m15, 1);
            ((void (*)(s32))func_800D0FE0)(c15);
            D_801E7030 = n15 - 0x1C;
            if (m15 != 0x1F) {
                return 0;
            }
            func_80029514(0x64);
            func_80029124(0xEB, 1);
            func_80029124(0x91, 1);
            func_800291A0(0xCE, 1);
            return 0;
        }
        func_800D0F0C(c15, n15);
        return 0;
    }

    case 11:
    {
        typedef struct Rec {
            s32 unk0;
            s32 unk4;
            s32 unk8;
            void (*unkC)(void);
        } Rec;
        extern Rec *D_801E7774[];
        Rec **pp;
        Rec *r;
        Rec **pp2;
        register s32 dv __asm__("$2");
        Rec **base;
        Rec *r2;
        s32 t;
        s32 u;
        if (D_80115126 == 4) {
            if ((*(u8 *)D_80115148) == 0) {
                s32 i11 = arg1;
                if (D_801E7774[i11] != 0) {
                    goto bad472;
                }
                if (func_80189E54(D_801B9420[i11]) != 0) {
                    goto L801896C8;
                }
                D_801E7700 = (s32)&D_801EC928;
                D_80115112 = D_80115112 + 1;
                ((void (*)(s32, s32))func_80139A68)((s16)(arg1 + 1), 0);
                func_8002D4C8(0x5EE, 0);
                return 0;
            }
            base = D_801E7774;
            pp = &base[arg1];
            r = *pp;
            if (r == 0) {
                goto bad472;
            }
            if (r->unk4 == 0) {
                goto bad472;
            }
            D_801E7700 = r->unk4;
            if (r->unkC != 0) {
                r->unkC();
            }
            ((void (*)(s32))func_8017ADE8)((*pp)->unk8);
            goto tail45D;
        }
        base = D_801E7774;
        pp2 = &base[arg1];
        r2 = *pp2;
        if (r2 == 0) {
            goto bad472;
        }
        t = (*(Rec * volatile *)pp2)->unk8;
        __asm__ __volatile__("");
        D_801E7700 = r2->unk4;
        ((void (*)(s32))func_8017ADE8)(t);
        u = D_801E7700;
        D_801E7794 = 0;
        if (u == (s32)&D_801E92E0) {
            D_801E7794 = 1;
        }
        if (u == (s32)&D_801E96A4) {
            D_801E7794 = 2;
        }
    tail45D:
        func_8002D4C8(0x45D, 0);
        dv = D_80115112;
        dv = dv + 1;
        D_80115112 = dv;
        return 0;
    }
    }
    goto done;

bad472:
    func_8002D4C8(0x472, 0);
done:
    return 0;
}


DEFINE_func_80189DDC()  /* dedup: shared engine-core @0x80189DDC (src/shared) */

extern s16 D_80115126;
extern s32 D_801B92E4[];
extern s32 D_801E7700;

void func_80189E14(s32 a0)
{
    void *ret = (void *)D_801B92E4[D_80115126 * 10 + (s16)a0];

    D_801E7700 = (s32)ret;
    return ret;
}


extern s32 D_80078E8C;
s16 func_80189E54(s32 a0)
{
    s32 v1 = D_80078E8C + a0;
    if (v1 > 99999) v1 = 99999;
    if (v1 < 0) return 1;
    D_80078E8C = v1;
    return 0;
}



/* func_80189EA0 — ov_SC03_001 (133 ins), exemplar of a 5-member open-only
 * h_norm cluster.  Builds the full-screen fade overlay: a DR_MODE-style 8-byte
 * GP0 packet (0xE1000015), a 320x240 semi-transparent gouraud quad (POLY_G4,
 * code 0x3A), and a second 8-byte GP0 packet (0xE1000240), each linked into the
 * current OT with the psyq `addPrim` idiom.  The type shapes and the
 * `((PTag *)x)->addr = ((PTag *)ot)->addr; ((PTag *)ot)->addr = (u32)x;` pair
 * are copied VERBATIM from the already-matched neighbour func_8018BCD4 in this
 * same TU (§71) — Env_* / PTag_* there are the fleet-canonical shapes.
 *
 * Levers that were load-bearing (all byte-tested; the draft is PIN-FREE):
 *   §20  &D_801151D0 / &D_800B9A02 taken into pointer LOCALS -> each address is
 *        force_reg'd once (lui+addiu -> $t2 / $a3) instead of a %lo per use.
 *   §36  the 24-bit BITFIELD store, not a hand-written mask, is what emits
 *        0x00FFFFFF (lui+ori) ahead of 0xFF000000 (lui) while the body ANDs the
 *        destination first — expmed's store_fixed_bit_field signature.
 *   §37  asm-label aliases for D_801E770C/D_801E7710: the TU canon is u16/s16
 *        but the target does a bare `lbu %lo(sym)`, and a plain block-scope
 *        `extern u8` would be a conflicting redeclaration.
 *   ---  `volatile` on the OT index read keeps all SIX *pbh loads alive; a plain
 *        read cse-folds them and the function loses ~25 instructions.
 *   S1   the whole body is ONE branch-free basic block and every store ties at
 *        the same priority, so forward asm order == source statement order —
 *        the POLY_G4 block below is a literal transcription of the target.
 *   S2   `p` is destructively updated (multi-set -> no birthing boost) so its
 *        `addiu +8` floats up into the preceding load-delay gap, while `r` is a
 *        FRESH single-set local (boosted) so its `addiu +0x24` sinks to sit
 *        immediately before `sb 3($a0)`.  Both placements are the target's.
 *   ---  the bare `p = r;` before r's uses is a COMBINE BARRIER: without a SET
 *        of `p` between `r = p + 9` and r's first use, `can_combine_p` lets
 *        combine substitute `r` -> `p + 0x24` into every MEM offset and the
 *        `addiu` disappears entirely (and, at the tail, `p += 2` folds to
 *        `addiu $t3,$t3,0x2C` off the stale base instead of `addiu $t3,$a0,8`).
 *        It also fixes the register rotation for free — verified that adding or
 *        removing `register __asm__` pins on p/r/pbh is a byte no-op.
 */

/* ---- TU-visible spellings (file scope of ov_SC03_001_jr_8018A3A8.c) ---- */

void func_80189EA0(void) {

    extern s32 D_801151D0;
    extern u16 D_801E770C;
    extern s16 D_801E7710;
    /* §100/§120: draft-local, uniquely-named types — they live in the BODY so
     * they cannot collide with the TU's own Env_8018BCD4 / PTag_8018BCD4. */
    typedef struct { u32 addr : 24; u32 len : 8; } PTag_8018C960_80189EA0;
    typedef struct { u32 *ot; u32 pad[4]; } Env_8018C960_80189EA0;   /* 0x14 stride */
    typedef struct {
        u32 tag;                        /* 0x00 */
        u8  r0, g0, b0, code;           /* 0x04..0x07 */
        s16 x0, y0;                     /* 0x08, 0x0A */
        u8  r1, g1, b1, p1;             /* 0x0C..0x0F */
        s16 x1, y1;                     /* 0x10, 0x12 */
        u8  r2, g2, b2, p2;             /* 0x14..0x17 */
        s16 x2, y2;                     /* 0x18, 0x1A */
        u8  r3, g3, b3, p3;             /* 0x1C..0x1F */
        s16 x3, y3;                     /* 0x20, 0x22 */
    } PG4_8018C960_80189EA0;                     /* -> 0x24 */

    extern Env_8018C960_80189EA0 D_800AE7BC[];
    extern u8 aD801EF1EC __asm__("D_801E770C");
    extern u8 aD801EF1F0 __asm__("D_801E7710");

    u32 **pp;
    volatile u16 *pbh;
    u32 *p;
    u32 *r;
    u8 c1, c2;

    pp  = (u32 **)&D_801151D0;
    pbh = (volatile u16 *)&D_800B9A02;

    p = *pp;
    ((PTag_8018C960_80189EA0 *)p)->len = 1;
    p[1] = 0xE1000015;
    ((PTag_8018C960_80189EA0 *)p)->addr = ((PTag_8018C960_80189EA0 *)D_800AE7BC[*pbh].ot)->addr;
    ((PTag_8018C960_80189EA0 *)D_800AE7BC[*pbh].ot)->addr = (u32)p;

    p += 2;
    ((PG4_8018C960_80189EA0 *)p)->tag  = 0x08000000;
    ((PG4_8018C960_80189EA0 *)p)->code = 0x3A;
    ((PG4_8018C960_80189EA0 *)p)->x2 = -160;
    ((PG4_8018C960_80189EA0 *)p)->x0 = -160;
    ((PG4_8018C960_80189EA0 *)p)->x3 = 160;
    ((PG4_8018C960_80189EA0 *)p)->x1 = 160;
    c1 = aD801EF1EC;
    ((PG4_8018C960_80189EA0 *)p)->b1 = c1;
    ((PG4_8018C960_80189EA0 *)p)->b0 = c1;
    ((PG4_8018C960_80189EA0 *)p)->g1 = c1;
    ((PG4_8018C960_80189EA0 *)p)->g0 = c1;
    ((PG4_8018C960_80189EA0 *)p)->r1 = c1;
    ((PG4_8018C960_80189EA0 *)p)->r0 = c1;
    c2 = aD801EF1F0;
    ((PG4_8018C960_80189EA0 *)p)->y1 = -120;
    ((PG4_8018C960_80189EA0 *)p)->b3 = c2;
    ((PG4_8018C960_80189EA0 *)p)->b2 = c2;
    ((PG4_8018C960_80189EA0 *)p)->g3 = c2;
    ((PG4_8018C960_80189EA0 *)p)->g2 = c2;
    ((PG4_8018C960_80189EA0 *)p)->r3 = c2;
    ((PG4_8018C960_80189EA0 *)p)->r2 = c2;
    ((PG4_8018C960_80189EA0 *)p)->y0 = -120;
    ((PG4_8018C960_80189EA0 *)p)->y3 = 120;
    ((PG4_8018C960_80189EA0 *)p)->y2 = 120;

    ((PTag_8018C960_80189EA0 *)p)->addr = ((PTag_8018C960_80189EA0 *)D_800AE7BC[*pbh].ot)->addr;
    ((PTag_8018C960_80189EA0 *)D_800AE7BC[*pbh].ot)->addr = (u32)p;

    r = p + 9;                          /* 0x24 */
    p = r;                              /* COMBINE BARRIER — see header */
    ((PTag_8018C960_80189EA0 *)r)->len = 1;
    r[1] = 0xE1000240;
    ((PTag_8018C960_80189EA0 *)r)->addr = ((PTag_8018C960_80189EA0 *)D_800AE7BC[*pbh].ot)->addr;
    ((PTag_8018C960_80189EA0 *)D_800AE7BC[*pbh].ot)->addr = (u32)r;

    p += 2;
    *pp = p;
}


extern void func_8001D074(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_8001CD50(s32 a0, s32 a1);

extern s32 D_801E77E8[];
extern s32 D_801E7804;

void func_8018A0B4(void) {
    s32 i;

    i = 0;
    do {
        D_801E77E8[i] = ((s32 (*)(s32, s32))func_8001D074)(0x3E, 0x7D);
        (&D_801E7804)[i * 0x10] = 0;
        func_800233CC(&(&D_801E7804)[i * 0x10] - 1, 0x30);
        func_8001CD50(D_801E77E8[i], (s32)(&(&D_801E7804)[i * 0x10] - 1));
        ((s32 *)D_801E77E8[i])[1] |= 0xD0000040;
        i++;
    } while (i < 6);
}




extern s32 D_801E7984;

void func_8018A168(a0, a1)
s32 a0;
s32 a1;
{
    extern s32 D_801E7984;
    register s32 rv __asm__("$2");
    s32 x = ((s32 *)&D_801E7984)[0];
    s32 y = a1;
    s32 d;

    if (y < a0) {
        if (x < y) {
            x = x + 0x5A0;
        }
        y = y + 0x5A0;
    }
    if (a0 >= x) {
        rv = -1;
        goto done;
    }
    if (x >= y) {
        rv = -1;
        goto done;
    }
    d = x - a0;
    if (d < 16) {
        rv = d * 2;
        goto done;
    }
    d = y - x;
    if (d < 16) {
        rv = d * 2;
        goto done;
    }
    rv = 31;
done:
    __asm__("" :: "r"(rv));
}


extern s32 (*D_801E0498[])();
extern s32 D_801E7980;
extern s32 func_8018A224();

void func_8018A1D0(s32 a0)
{
    s32 res;
    res = D_801E0498[a0]();
    if (res == -1) {
        return -1;
    }
    return func_8018A224(D_801E7980, res);
}


extern u16 D_800B99DA;
extern u8 D_801E04E0[];
extern void func_8018A2E0(u16 *a0, s32 a1);

typedef struct {
    u16 f0;
    u16 f1;
    u16 f2;
    s16 f3;
} Ent_8018A224;

s32 func_8018A224(Ent_8018A224 *arg0, s32 arg1)
{
    u8 rect[4];
    s32 step;
    register s32 q __asm__("$3");
    register s32 half __asm__("$2");

    step = 0x50;
    if (D_801E04E0[D_800B99DA & 0xF] == 0) {
        step = 0x60;
    }
    arg1 += 1;
    q = (step * arg1) / 32;
    half = q / 2;
    rect[0] = q;
    rect[1] = q;
    rect[2] = half;
    rect[3] = 0;
    if (arg0->f3 != -1) {
        do {
            func_8018A2E0(&arg0->f0, *(s32 *)rect);
            arg0++;
        } while (arg0->f3 != -1);
    }
}


/* func_8018A2E0 (ov_SC04_018, ov_SC04_018_jr_8017AE2C) — MATCH (250 ins)
 *
 * Shadow/marker quad renderer: builds an outer quad (D_801E00B0 offset table)
 * through RotNclip4, rejects it on OTZ, builds the inner quad (D_801E0130)
 * through RotTransPers4, then emits 4 semi-transparent POLY_G4 (0x24 each) +
 * one semi-transparent POLY_F4 (0x18) out of one 0xA8 packet allocation.
 *
 * Levers that closed the residual (all byte-verified against the .s):
 *  - frame 0xE0 with locals starting at 0x30: STARTING_FRAME_OFFSET ==
 *    outgoing-args size (RotNclip4 takes 11 args -> 0x2C -> 0x30).  `pad0[16]`
 *    is the DEAD 0x20-byte first local (§136 idiom 6) that puts va at sp+0x50.
 *  - `sxy[8]` is ONE array: RotNclip4 fills [0..3], RotTransPers4 fills [4..7],
 *    and the loop indexes the whole thing (idx values run 0..7).
 *  - `register u16 *dst __asm__("$4")`: a HARD-reg dst is not a biv, so loop.c
 *    cannot strength-reduce its +2/+4 accesses into a second IV.  That is what
 *    gives ONE register with offsets 0/2/4 (unpinned -> 254 ins, extra IV).
 *  - `p2 = p1 + 2` (two walked source pointers): `p1[0]` is a bare deref
 *    (excluded from givs, loop-map L1 rule 4) so p1 stays the biv used at
 *    offset 0, and p2 is the second IV carrying the -2/0 offset cluster.
 *  - `while` loops with `i++` written BEFORE the pointer bumps: the increment
 *    LUID order decides which bump fills the first load-delay slot.
 *  - `s16 idx[4]` as a real ARRAY (ARRAY_REF => MEM_IN_STRUCT_P): that makes
 *    the varying-address packet store conflict with the stack slots, so CSE
 *    cannot forward idx[1..3] and gcc re-loads them with `lh` (an
 *    INDIRECT_REF `*(s16*)(buf+0x82)` forwards them and loses the reloads).
 *  - `D_800A651C[][5]` / `D_801E01Dx[][4]` two-dimensional externs: the 1-D
 *    `sym + byte_offset` spelling makes gcc materialise `&D_800A651C` into a
 *    hoisted callee-saved register ($s5, +4 ins); the 2-D array-ref keeps the
 *    symbol folded in the MEM address (gas `lw $2,sym($1)` macro) and makes the
 *    table index a REDUCED GIV, whose preheader init lands AFTER the hoisted
 *    `addiu $s3,$sp,0x30` movable (target order s3 -> s2 -> s0).
 *  - `type2 = type + zr` ($zero pin): the target keeps TWO pseudos for
 *    (attr & 0xFF) — $a0 for the pre-call use and $s1 for the post-call one —
 *    so a plain second variable would be propagated away by CSE.
 *  - `pk[7] = 0x3A` written AFTER the 0x1C colour store: it only conflicts with
 *    the 0x04 store, so the scheduler sinks it into the `lh 0xB6($sp)` delay
 *    slot exactly as in the target (§135 idiom 4, source order sets the sink).
 */

extern void func_8012E32C(void);
extern void func_8018A6C8(void *, s32);
extern s32 RotNclip4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern s32 RotTransPers4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern void *func_80010A08(s32);
extern s32 AddPrim(s32, void *);
extern void func_8012E28C(s32, s32);
extern s32 D_800A651C[][5];
extern short D_800B9A02;
extern u16 D_801E00B0[];
extern u16 D_801E0130[];
extern u16 D_801E01D0[][4];
extern u16 D_801E01D2[][4];
extern u16 D_801E01D4[][4];
extern u16 D_801E01D6[][4];

void func_8018A2E0(u16 *a0, s32 a1)
{
    register s32 zr __asm__("$0");

    u16 pad0[16];   /* dead: locals begin at sp+0x30, va must land at sp+0x50 */
    u16 va[16];     /* sp+0x50 — outer quad, 4 x SVECTOR */
    u16 vb[16];     /* sp+0x70 — inner quad, 4 x SVECTOR */
    s32 sxy[8];     /* sp+0x90 — [0..3] RotNclip4, [4..7] RotTransPers4 */
    s16 idx[4];     /* sp+0xB0 */
    s32 p;          /* sp+0xB8 */
    s32 otz;        /* sp+0xBC */
    s32 flag;       /* sp+0xC0 */

    u16 attr;
    s32 type;
    s32 type2;
    u16 *p1;
    u16 *p2;
    register u16 *dst __asm__("$4");
    s32 i;
    u8 *pk;
    s32 j;

    func_8012E32C();

    attr = a0[3];
    type = attr & 0xFF;
    type2 = type + zr;
    if ((attr & 0xF00) == 0x200) {
        func_8018A6C8(a0, a1);
        return;
    }

    p1 = (u16 *)((u8 *)D_801E00B0 + type * 0x20);
    i = 0;
    p2 = p1 + 2;
    dst = va;
    while (i < 4) {
        dst[0] = a0[0] + p1[0];
        dst[1] = a0[1] + p2[-1];
        dst[2] = a0[2] + p2[0];
        i++;
        p1 += 4;
        p2 += 4;
        dst += 4;
    }

    if (RotNclip4((s32)&va[0], (s32)&va[4], (s32)&va[8], (s32)&va[12],
                  &sxy[0], &sxy[1], &sxy[2], &sxy[3], &p, &otz, &flag) <= 0) {
        return;
    }

    otz -= 0x10;
    if (otz < 0) {
        return;
    }
    if (otz >= 0x1000) {
        return;
    }

    p1 = (u16 *)((u8 *)D_801E0130 + type2 * 0x20);
    i = 0;
    p2 = p1 + 2;
    dst = vb;
    while (i < 4) {
        dst[0] = a0[0] + p1[0];
        dst[1] = a0[1] + p2[-1];
        dst[2] = a0[2] + p2[0];
        i++;
        p1 += 4;
        p2 += 4;
        dst += 4;
    }

    RotTransPers4((s32)&vb[0], (s32)&vb[4], (s32)&vb[8], (s32)&vb[12],
                  &sxy[4], &sxy[5], &sxy[6], &sxy[7], &p, &flag);

    pk = func_80010A08(0xA8);

    for (j = 0; j < 4; j++) {
        idx[0] = D_801E01D0[j][0];
        idx[1] = D_801E01D2[j][0];
        idx[2] = D_801E01D4[j][0];
        idx[3] = D_801E01D6[j][0];
        *(s32 *)(pk + 0x4) = a1 & -(idx[0] < 4);
        *(s32 *)(pk + 0xC) = a1 & -(idx[1] < 4);
        *(s32 *)(pk + 0x14) = a1 & -(idx[2] < 4);
        *(s32 *)(pk + 0x1C) = a1 & -(idx[3] < 4);
        pk[7] = 0x3A;
        *(u32 *)(pk + 0x0) = 0x08000000;
        *(s32 *)(pk + 0x8) = sxy[idx[0]];
        *(s32 *)(pk + 0x10) = sxy[idx[1]];
        *(s32 *)(pk + 0x18) = sxy[idx[2]];
        *(s32 *)(pk + 0x20) = sxy[idx[3]];
        AddPrim(D_800A651C[(u16)D_800B9A02][0] + (otz * 4), pk);
        pk += 0x24;
    }

    *(s32 *)(pk + 0x4) = a1;
    pk[7] = 0x2A;
    *(u32 *)(pk + 0x0) = 0x05000000;
    *(s32 *)(pk + 0x8) = sxy[0];
    *(s32 *)(pk + 0xC) = sxy[1];
    *(s32 *)(pk + 0x10) = sxy[2];
    *(s32 *)(pk + 0x14) = sxy[3];
    AddPrim(D_800A651C[(u16)D_800B9A02][0] + (otz * 4), pk);
    func_8012E28C(otz, 1);
}


extern s32 D_801E77E8[];
extern s32 D_801E7800[];

void func_8018A6C8(void *a0, s32 a1) {
    s32 v1;
    s32 *a2;

    v1 = ((u16 *)a0)[3] >> 12;
    a2 = (s32 *)D_801E77E8[v1];
    a2[1] &= 0x7FFFFFFF;
    D_801E7800[v1 * 16] = a1;
    ((u16 *)a2)[4] = ((u16 *)a0)[0];
    ((u16 *)a2)[5] = ((u16 *)a0)[1];
    ((u16 *)a2)[6] = ((u16 *)a0)[2];
    ((u16 *)a2)[9] = (((u16 *)a0)[3] & 0xF) << 10;
}


DEFINE_func_8018A740()  /* dedup: shared engine-core @0x8018A740 (src/shared) */


extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012BEE8(s32 a0);
extern s32 rand(void);
extern u8 D_801E0500[][4];

void func_8018A77C(s32 param_1) {
    s32 i;
    s32 v1;
    s32 uVar1;

    if (func_80184BAC(7, 0x13) == 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (D_801E0500[*(s16 *)(param_1 + 0x100)][i] == *(s32 *)(param_1 + 0x1c)) {
            func_8012C658(0x140,
                          *(u8 *)(param_1 + 0xfc) | ((*(s16 *)(param_1 + 0xfe) << 8) & 0xff00),
                          param_1);
            break;
        }
    }
    if (func_8012BEE8(param_1) == 0) {
        return;
    }
    *(s32 *)(param_1 + 0x1c) = 0x50;
    uVar1 = rand();
    v1 = *(u16 *)(param_1 + 0xfe) + (uVar1 & 0xf) - 7;
    v1 &= 0xff;
    *(u16 *)(param_1 + 0xfe) = v1;
    uVar1 = rand();
    v1 = *(u16 *)(param_1 + 0xfc) + (uVar1 & 0xf) - 7;
    v1 &= 0xff;
    *(u16 *)(param_1 + 0xfc) = v1;
    uVar1 = rand();
    *(s16 *)(param_1 + 0x100) = uVar1 % 7;
}


DEFINE_func_8018A898()  /* dedup: shared engine-core @0x8018A898 (src/shared) */



extern void (*D_801E0524[])(void);

void func_8018A8D4(void *a0) {
    D_801E0524[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801E0534[])(void);

void func_8018A910(void *a0) {
    D_801E0534[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801E0544[])(void);

void func_8018A94C(void *a0) {
    D_801E0544[*(u16 *)((s32)a0 + 0x2)]();
}


DEFINE_func_8018A988()  /* dedup: shared engine-core @0x8018A988 (src/shared) */


extern s32 func_8012BEE8(s32 a0);
extern s32 rand(void);

void func_8018A990(s32 param_1) {
    s32 uVar1;
    s32 iVar2;
    register s32 iVar3 __asm__("$3");
    register s32 iVar4 __asm__("$16");
    u32 uVar3;

    uVar1 = *(u16 *)(param_1 + 0x34);
    if (uVar1 == 1) {
        goto case1;
    }
    if (uVar1 < 2) {
        if (uVar1 == 0) {
            goto case0;
        }
        return;
    }
    if (uVar1 == 2) {
        goto case2;
    }
    if (uVar1 != 3) {
        return;
    }
    goto case3;

case0:
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(s32 *)(param_1 + 0x1c) = 0x40;
    *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
    uVar3 = rand();
    iVar4 = uVar3 & 0x3fff;
    iVar4 = iVar4 + 0x7800;
    uVar3 = rand();
    if ((uVar3 & 1) == 0) {
        iVar4 = -iVar4;
    }
    *(s32 *)(param_1 + 0xe0) = iVar4;
    *(s32 *)(param_1 + 0xe4) = 0;
    return;

case1:
    iVar3 = *(s32 *)(param_1 + 0xe4);
    iVar3 = iVar3 + *(s32 *)(param_1 + 0xe0);
    *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + iVar3;
    *(s32 *)(param_1 + 0xe4) = iVar3;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
    uVar3 = rand();
    uVar3 = uVar3 & 0x3f;
    goto tail;

case2:
    *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + *(s32 *)(param_1 + 0xe4);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(s32 *)(param_1 + 0x1c) = 0x40;
    *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
    *(s32 *)(param_1 + 0xe0) = -*(s32 *)(param_1 + 0xe0);
    return;

case3:
    __asm__ __volatile__("" ::: "memory");
    iVar3 = *(s32 *)(param_1 + 0xe4);
    iVar3 = iVar3 + *(s32 *)(param_1 + 0xe0);
    *(s32 *)(param_1 + 0xdc) = *(s32 *)(param_1 + 0xdc) + iVar3;
    *(s32 *)(param_1 + 0xe4) = iVar3;
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) = *(u16 *)(param_1 + 0xde);
    iVar2 = func_8012BEE8(param_1);
    if (iVar2 == 0) {
        return;
    }
    *(u16 *)(param_1 + 0x34) = 0;
    uVar3 = rand();
    uVar3 = uVar3 & 0xff;

tail:
    *(u32 *)(param_1 + 0x1c) = uVar3 + 0x40;
}


DEFINE_func_8018AB3C()  /* dedup: shared engine-core @0x8018AB3C (src/shared) */


extern u16 D_800B99DA;
extern s32 D_80126B58;
extern u8 D_800AF648;
extern s32 D_801E055C;
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018AB78(void)
{
    extern s32 func_80013450(s32);
    s32 *p = &D_80126B58;
    s32 sxy, pv, flag;
    s16 x;
    s32 pan;
    s32 dist;
    s32 vol;

    if (!(D_800B99DA & 1)) {
        func_8004914C(&D_800AF648);
        func_800491AC(&D_800AF648);
        if (RotTransPers((s32)&D_801E055C, (s32)&sxy, &pv, &flag) <= 0 || flag < 0) {
            func_8002D4C8(4, 0x7E6);
        } else {
            x = *(u16 *)&sxy + 0xA0;
            *(s16 *)&sxy = x;
            if (x < 0) {
                x = 0;
                *(s16 *)&sxy = x;
            } else if (x >= 0x141) {
                x = 0x140;
                *(s16 *)&sxy = x;
            }
            x = *(s16 *)&sxy;
            pan = (x * 15) / 320;
            dist = ((s32 (*)(s32, s32))func_80013450)((s32)(p + 1), (s32)&D_801E055C);
            if (dist >= 0x240) {
                dist = 0x23F;
            }
            {
                s32 panpart;
                vol = ((0x23F - dist) * 127) / 576;
                panpart = ((pan << 8) & 0xF00) | 0x3000;
                func_8002D4C8(0x7E6, panpart | (vol & 0x7F));
            }
        }
    }
}



extern s32 D_801E01F0;
extern s32 D_801E7980;
extern void func_8018A168();

void func_8018ACD4(void) {
    D_801E7980 = &D_801E01F0;
    func_8018A168(0x474, 0x4B0);
}


extern void func_8018A168();
    extern s32 D_801E0228;
    extern s32 D_801E7980;
    void func_8018AD08(void) {
        D_801E7980 = &D_801E0228;
        func_8018A168(0x474, 0x4EC);
    }



DEFINE_func_8018AD3C()  /* dedup: shared engine-core @0x8018AD3C (src/shared) */



extern s32 D_801E0288;
extern s32 D_801E7980;
extern void func_8018A168();

void func_8018AD70(void) {
    D_801E7980 = &D_801E0288;
    func_8018A168(0x474, 0x4B0);
}



extern s32 D_801E02C0;
extern s32 D_801E7980;
extern void func_8018A168();

void func_8018ADA4(void) {
    D_801E7980 = &D_801E02C0;
    func_8018A168(0x474, 0x528);
}


s32 func_8018ADD8(void) {
    extern s32 D_801E02F8;
    extern s32 D_801E7980;
    extern void func_8018A168();
    s32 s0;

    D_801E7980 = (s32)&D_801E02F8;
    s0 = ((s32 (*)(s32, s32))func_8018A168)(0x168, 0x1A4);
    if (s0 == -1) {
        s0 = ((s32 (*)(s32, s32))func_8018A168)(0x474, 0x4EC);
    }
    if ((u32)(func_80029504() - 0xC8) < 0xDC) {
        return -1;
    }
    return s0;
}



extern s32 D_801E0338;
extern s32 D_801E7980;
extern void func_8018A168();

void func_8018AE4C(void) {
    D_801E7980 = &D_801E0338;
    func_8018A168(0x474, 0x1A4);
}


extern s32 func_80029504(void);
extern void func_8018A168();
extern s32 D_801E0370;
extern s32 D_801E7980;

s32 func_8018AE80(void) {
    s32 v;
    D_801E7980 = (s32)&D_801E0370;
    v = func_80029504();
    if ((u32)(v - 0x64) < 0x1F4) {
        return -1;
    }
    func_8018A168(0x96, 0xF0);
}



extern s32 D_801E0390;
extern s32 D_801E7980;
extern void func_8018A168();

void func_8018AECC(void) {
    D_801E7980 = &D_801E0390;
    func_8018A168(0x12c, 0x1A4);
}


DEFINE_func_8018AF00()  /* dedup: shared engine-core @0x8018AF00 (src/shared) */



extern s32 D_801E0440;
extern s32 D_801E7980;
extern void func_8018A168();

void func_8018AF34(void) {
    D_801E7980 = &D_801E0440;
    func_8018A168(0x474, 0x4B0);
}




extern s32 func_80029504(void);
extern void func_8018A168();

s32 func_8018AF68(void) {

    extern s32 D_801E0470;
    s32 v;
    D_801E7980 = (s32)&D_801E0470;
    v = func_80029504();
    if ((u32)(v - 0x64) < 0x1F4) {
        return -1;
    }
    func_8018A168(0x474, 0x78);
}



extern s32 D_801E0488;
extern s32 D_801E7980;
extern void func_8018A168();

void func_8018AFB4(void) {
    D_801E7980 = &D_801E0488;
    func_8018A168(0x564, 0x1A4);
}


DEFINE_func_8018AFE8()  /* dedup: shared engine-core @0x8018AFE8 (src/shared) */


extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 D_801E77E8[];
extern s32 D_801E7984;
extern s32 D_801E799C;
extern void func_8018A1D0(s32 a0);
extern void func_8018AB78(void);

void func_8018AFF0(void) {
    s32 i;

    D_801E7984 = (((D_80078EB1 << 4) - D_80078EB1) << 2) + D_80078EB0;
    for (i = 0; i < 6; i++) {
        *(s32 *)(D_801E77E8[i] + 4) |= 0x80000000;
    }
    for (i = 2; i < 18; i++) {
        func_8018A1D0(i);
    }
    func_8018AB78();
    if (D_801E799C != 0) {
        D_801E799C--;
    }
}


#include "common.h"

DEFINE_func_8018B0AC()  /* dedup: shared engine-core @0x8018B0AC (src/shared) */


DEFINE_func_8018B158()  /* dedup: shared engine-core @0x8018B158 (src/shared) */


/*
 * func_8018B19C -- ov_SC04_018 / ov_SC04_018_jr_80188E1C, 71 ins, family reach x6.
 *
 * STEP 0 sibling: this is a direct extension of the shared-engine-core macro
 * DEFINE_func_80144558() (src/shared/engine_core.h) -- identical prologue
 * through the func_80128EA8 call and the three field copies (+8/+0xA/+0xC
 * from param_1+6/+0xA/+0xE), but instead of calling func_8012B200(param_1) at
 * the end, this variant sets a handful of extra fields directly and calls
 * func_8012B0B4 (angle -> velocity split), matching the idiom seen at
 * src/ov_SC03_099/ov_SC03_099_jr_8017BEBC.c:func_8017F9C4/func_8017FB58 and
 * the DEFINE_func_8012B0B4() macro itself (single u32 result word written
 * through the output pointer).
 */
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern u8 D_800D387C[];
extern u8 D_800D3888[];

void func_8018B19C(u8 *arg0)
{
    register u8 *param_1 __asm__("$16");   /* $s0 */
    s32 raw;
    u32 buf[6];

    param_1 = arg0;
    {
        register s32 s0 __asm__("$17");   /* $s1 -- scoped: dead after func_80128EA8 */
        s0 = ((s32 (*)(void))func_8012C194)();
        if (s0 == 0) {
            func_8012CAE4(param_1);
            return;
        }
        *(s32 *)(param_1 + 0xCC) = s0;
        func_8001CC3C(s0, 0, 0, 0);
        *(s32 *)(s0 + 0x20) = (s32)D_800D387C;
        *(u8 *)(s0 + 0x27) = 0x9C;
        *(u16 *)(s0 + 0x1A) = 0x3000;
        *(u16 *)(s0 + 0x18) = 0x3000;
        *(u32 *)(s0 + 4) = *(u32 *)(s0 + 4) | 0x50000000;
        func_80128EA8(s0, (s32)(param_1 + 0xD0), (s32)D_800D3888);
    }
    {
        s32 obj = *(s32 *)(param_1 + 0xCC);
        *(u16 *)(obj + 8) = *(u16 *)(param_1 + 6);
        *(u16 *)(obj + 0xA) = *(u16 *)(param_1 + 0xA);
        *(u16 *)(obj + 0xC) = *(u16 *)(param_1 + 0xE);
    }
    raw = *(s16 *)(param_1 + 0x70);
    *(s32 *)(param_1 + 0x1C) = 0x5A;
    *(u16 *)(param_1 + 2) = 1;
    *(s32 *)(param_1 + 0x10) = 0;
    *(s32 *)(param_1 + 0x14) = 0xFFF80000;
    *(s32 *)(param_1 + 0x18) = 0;
    func_8012B0B4((unsigned int *)buf, (raw & 0xFF00) >> 4, (raw & 0xFF) << 6);
    {
        register s32 full __asm__("$2");
        register s32 low  __asm__("$3");
        full = *(s32 *)buf;
        low = *(s16 *)buf;
        *(s32 *)(param_1 + 0x48) = 0;
        *(s32 *)(param_1 + 0x44) = low;
        *(s32 *)(param_1 + 0x4C) = full >> 16;
    }
}


extern void func_8012AD80(s32 a0);
extern s32 func_80128ED8(s32 a0, s32 *a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);

void func_8018B2B8(void *arg0) {
    s32 temp_s1;
    s32 temp_v1;

    temp_s1 = *(s32 *)((s32)arg0 + 0xCC);
    func_8012AD80((s32)arg0);
    temp_v1 = *(s32 *)((s32)arg0 + 0xCC);
    *(u16 *)(temp_v1 + 8) = *(u16 *)((s32)arg0 + 6);
    *(u16 *)(temp_v1 + 0xA) = *(u16 *)((s32)arg0 + 0xA);
    *(u16 *)(temp_v1 + 0xC) = *(u16 *)((s32)arg0 + 0xE);
    if ((*(s32 *)((s32)arg0 + 0x1C) & 7) == 0) {
        func_80128ED8(temp_s1, (s32 *)((s32)arg0 + 0xD0));
    }
    if (func_8012BEE8((s32)arg0) != 0) {
        func_80016714((void *)temp_s1, 0x38);
        func_8012C218(arg0);
    }
}


extern void func_8012B414(int a0);
    void func_8018B354(s32 arg0) {
        s32 temp_v1 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(temp_v1 + 0x14) += 0x8;
        ((void (*)(void))func_8012B414)();
    }


#include "common.h"

DEFINE_func_8018B388()  /* dedup: shared engine-core @0x8018B388 (src/shared) */


extern u16 D_800B99DA;
extern s32 func_8004787C(s32);

void func_8018B400(void *arg0) {
    u32 ret;
    u8 *v1;

    ret = func_8004787C(D_800B99DA * 48);
    v1 = *(u8 **)((char *)arg0 + 0x20);
    *(u16 *)(v1 + 0x10) = ret >> 5;
}


extern s32 func_80029504(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 D_801B60B0[];
extern s32 D_801E053C[];

void func_8018B448(s32 a0) {
    s32 v0;
    if ((u32)(func_80029504() - 0x181) < 0x55) {
        func_8012CAE4((void *)a0);
        return;
    }
    *(s32 *)(a0 + 0x20) = v0 = ((s32 (*)(void))func_8012C1B8)();
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C810(v0, (s32)D_801B60B0);
    *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x8000;
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);
    func_8012E8E0(a0, (s32)D_801E053C);
    *(s16 *)(a0 + 0x2) = 1;
    return;
}


void func_8018B4EC(void *a0) {
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32, s32);
    extern void func_8012E8E0(s32, s32);
    extern u8 D_801B65B0[];
    extern s16 D_801E054C;

    *(s32 *)((char *)a0 + 0x20) = ((s32 (*)(void))func_8012C1B8)();
    if (*(s32 *)((char *)a0 + 0x20) == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(*(s32 *)((char *)a0 + 0x20), (s32)&D_801B65B0[0]);
        func_8012E8E0((s32)a0, (s32)&D_801E054C);
        *(s16 *)((char *)a0 + 0x2) = 1;
        *(s16 *)((char *)a0 + 0x34) = 0;
        *(s32 *)((char *)a0 + 0xDC) = 0;
        *(s32 *)((char *)a0 + 0xE0) = 0;
        *(s32 *)((char *)a0 + 0xE4) = 0;
    }
}


DEFINE_func_8018B564()  /* dedup: shared engine-core @0x8018B564 (src/shared) */



extern void (*D_801E056C[])(void);

void func_8018B570(void *a0) {
    D_801E056C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern s32 func_80184D00(void);
extern s32 func_80184E44(void);
extern u8 D_80078EBA;

s32 func_8018B5AC(void) {
    if (func_80184D00() == 3) {
        return 1;
    }
    if (func_80184E44() == 1) {
        return 1;
    }
    if (D_80078EBA != 2) {
        return func_80184BAC(0xC, 0x14) == 0;
    }
    return 1;
}


#include "common.h"

DEFINE_func_8018B614()  /* dedup: shared engine-core @0x8018B614 (src/shared) */


#include "common.h"

DEFINE_func_8018B660()  /* dedup: shared engine-core @0x8018B660 (src/shared) */


void func_8018B6A0(void *a0) {
    s32 v0;

    v0 = func_8012E57C(0x61, 0xD);
    *(s32 *)((char *)a0 + 0xCC) = v0;
    v0 = func_8018B5AC();

    if (v0 != 0) {
        v0 = 2;
    } else {
        v0 = 1;
    }

    *(s16 *)((char *)a0 + 0x2) = v0;
}


DEFINE_func_8018B6E8()  /* dedup: shared engine-core @0x8018B6E8 (src/shared) */


extern void (*D_801E0580[])(void);

void func_8018B6F4(void *a0) {
    D_801E0580[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern u8 D_80078EBA;
extern void func_8018B6E8(s32*);

void func_8018B730(void *a0) {
    s32 v0;
    *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    if (D_80078EBA == 3) {
        v0 = 0;
    } else {
        v0 = func_80184BAC(7, 0x13) != 0;
    }
    if (!v0) {
        ((void (*)(void *))func_8018B6E8)(a0);
    }
}


extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern u8 D_80078EBA;

void func_8018B798(void *a0) {
    s32 v0;
    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    if (D_80078EBA == 3) {
        v0 = 0;
    } else {
        v0 = func_80184BAC(7, 0x13) != 0;
    }
    if (v0 != 0) {
        *(u16 *)((char *)a0 + 2) = 1;
    }
}


#include "common.h"

DEFINE_func_8018B7FC()  /* dedup: shared engine-core @0x8018B7FC (src/shared) */


DEFINE_func_8018B868()  /* dedup: shared engine-core @0x8018B868 (src/shared) */


extern void (*D_801E0594[])(void);

void func_8018B874(void *a0) {
    D_801E0594[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern s32 func_80184BAC(s32 arg0, s32 arg1);

s32 func_8018B8B0(void) {
    if ((u32)(func_80029504() - 0x12C) < 0x12C) {
        if ((func_80029178(0xFA) & 0xFF) != 0) {
            return 0;
        }
    }
    return func_80184BAC(0xA, 0x14) != 0;
}




extern s32 func_8018B8B0();

void func_8018B904(void *a0) {
    *(s32 *)(*(s32 *)((char *)a0 + 0xCC) + 0xB0) = 1;
    if (func_8018B8B0() == 0) {
        func_8018B868(a0);
    }
}


extern s32 func_8018B8B0(void);

void func_8018B948(a0)
s32 a0;
{
    s32 *v1;
    v1 = *(s32 **)((s32)a0 + 0xCC);
    *(s32 *)((s32)v1 + 0xB0) = 2;
    if (func_8018B8B0() != 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
    }
}


extern s32 func_8012E57C(s32 a0, s32 a1);
extern s32 func_8018B8B0(void);

void func_8018B988(void *a0) {
    s32 v0;

    v0 = func_8012E57C(0x61, 0xC);
    *(s32 *)((char *)a0 + 0xCC) = v0;
    v0 = func_8018B8B0();

    if (v0 != 0) {
        v0 = 1;
    } else {
        v0 = 2;
    }

    *(s16 *)((char *)a0 + 0x2) = v0;
}


DEFINE_func_8018B9D0()  /* dedup: shared engine-core @0x8018B9D0 (src/shared) */



extern void (*D_801E05A8[])(void);

void func_8018B9DC(void *a0) {
    D_801E05A8[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

DEFINE_func_8018BA18()  /* dedup: shared engine-core @0x8018BA18 (src/shared) */


extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern u8 D_80078EBA;

void func_8018BA80(a0)
void *a0;
{
    s32 v0;
    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    if (D_80078EBA == 0) {
        v0 = 0;
    } else {
        v0 = func_80184BAC(0xB, 0x10) != 0;
    }
    if (v0 != 0) {
        *(u16 *)((char *)a0 + 2) = 1;
    }
}


extern s32 func_8012E57C(s32 a0, s32 a1);
extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern u8 D_80078EBA;

void func_8018BAE4(a0)
void *a0;
{
    s32 v0;
    v0 = func_8012E57C(0x61, 0x9);
    *(s32 *)((char *)a0 + 0xCC) = v0;
    if (D_80078EBA == 0) {
        v0 = 0;
    } else {
        v0 = func_80184BAC(0xB, 0x10);
        v0 = (0U < (u32)v0) ? 1 : 0;
    }
    if (v0 != 0) {
        v0 = 1;
    } else {
        v0 = 2;
    }
    *(s16 *)((char *)a0 + 0x2) = v0;
}




extern u8 D_80078EBA;
extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern s32 func_80029504(void);
extern s32 func_80184D00(void);
extern s32 func_80184E44(void);

s32 func_8018BB50(void) {
    u8 d = D_80078EBA;
    s32 v1;
    s32 v0;

    if (d == 6) {
        if (func_80184BAC(0, 0xC) == 0) {
            return 0;
        }
    } else if (d == 0) {
        if (func_80184BAC(0, 0xC) != 0) {
            return 0;
        }
    }

    v1 = func_80029504();
    if (v1 < 0xC8) {
        v1 = func_80184D00();
        if (v1 < 0) {
            return v1;
        }
        if (v1 < 3) {
            goto common;
        }
        v0 = v1 < 5;
        if (!v0) {
            goto ret0;
        }
        v0 = 0;
ret0:
        return v0;
    } else {
        if (v1 < 0x258) {
            return 0;
        }
    }
    if (v1 < 0x384) {
common:
        return func_80184BAC(2, 0x12) == 0;
    }
    if (func_80184BAC(2, 0x12) == 0) {
        return func_80184E44() != 1;
    }
    return 0;
}



extern void (*D_801E05B4[])(void);

void func_8018BC3C(void *a0) {
    D_801E05B4[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8018BB50(void);
extern u8 D_801E7A96;

void func_8018BC78(s32 a0) {
    if (func_8018BB50() != 0) {
        *(s32 *)(*(s32 *)(a0 + 0xCC) + 0xB0) = 1;
        D_801E7A96 = 1;
    } else {
        *(s32 *)(*(s32 *)(a0 + 0xCC) + 0xB0) = 2;
        D_801E7A96 = 0;
    }
}


extern s32 func_8012E57C(s32 a0, s32 a1);
extern s32 func_8018BB50(void);
extern u8 D_801E7A96;

void func_8018BCDC(s32 a0) {
    *(s16 *)(a0 + 0x2) = 1;
    *(s32 *)(a0 + 0xCC) = func_8012E57C(0x61, 0xE);
    if (func_8018BB50() != 0) {
        *(s32 *)(*(s32 *)(a0 + 0xCC) + 0xB0) = 1;
        D_801E7A96 = 1;
    } else {
        *(s32 *)(*(s32 *)(a0 + 0xCC) + 0xB0) = 2;
        D_801E7A96 = 0;
    }
}



extern void (*D_801E05BC[])(void);

void func_8018BD58(void *a0) {
    D_801E05BC[*(u16 *)((s32)a0 + 0x2)]();
}



void func_8018BD94(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    }


#include "common.h"

DEFINE_func_8018BDA4()  /* dedup: shared engine-core @0x8018BDA4 (src/shared) */



extern void func_80184CB8(s32*, s32);
    extern short D_801E05C4;
    void func_8018BDE0(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_801E05C4);
    }



extern void func_80184CB8(s32*, s32);
    extern short D_801E05C4;
    void func_8018BE0C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 3;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_801E05C4);
    }



extern void (*D_801E0690[])(void);

void func_8018BE38(void *a0) {
    D_801E0690[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80029504(void);
extern s32 func_80184D00(void);
extern s32 func_80184DD0(s32 a0);

void func_8018BE74(s32 a0) {

    extern s32 D_801E05E0[];
    extern s32 D_801E05F4[];

    s32 v1 = func_80029504();

    if (v1 < 0xC8) {
        s32 v0 = func_80184D00();
        *(s32 *)(a0 + 0xE4) = D_801E05E0[v0];
    } else {
        s32 v0 = ((s32 (*)(void))func_80184DD0)();
        *(s32 *)(a0 + 0xE4) = D_801E05F4[v0];
    }
}




extern s32 func_8014CB1C(void);

s32 func_8018BEE8(void) {
    return (u32)func_8014CB1C() != 0;
}


DEFINE_func_8018BF08()  /* dedup: shared engine-core @0x8018BF08 (src/shared) */


extern void func_80178CBC(s32 *a0, s32 a1);
    extern short D_801E0648;
    void func_8018BF34(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        *(short *)((char *)a0 + 0x34) = 0;
        func_80178CBC((s32 *)a0, (s32)&D_801E0648);
    }


extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern void func_8018BDE0(void*);

void func_8018BF64(void *arg0) {
    s32 s0 = (s32)arg0;
    s32 v0, v1;
    *(s32 *)((u8 *)(*(s32 **)((u8 *)s0 + 0xCC)) + 0xB0) = 2;
    v0 = func_80184BAC(6, 0x12);
    if (v0 != 0) {
        v1 = 1;
    } else {
        v0 = func_80184BAC(0x12, 0x15);
        v1 = (v0 != 0) << 1;
    }
    if (v1 != 0) {
        ((void (*)(s32))func_8018BDE0)(s0);
    }
}




extern s32 func_80184BAC(s32 arg0, s32 arg1);

void func_8018BFCC(void *arg0) {
    register s32 *s0 asm("$16") = arg0;
    s32 v0, v1;
    *(s32 *)((u8 *)(*(s32 **)((u8 *)s0 + 0xCC)) + 0xB0) = 1;
    v0 = func_80184BAC(6, 0x12);
    if (v0 != 0) {
        v1 = 1;
    } else {
        v0 = func_80184BAC(0x12, 0x15);
        v1 = (v0 != 0) ? 2 : 0;
    }
    if (v1 != 1) {
        func_8018BE0C(s0);
    }
}


#include "common.h"

DEFINE_func_8018C038()  /* dedup: shared engine-core @0x8018C038 (src/shared) */


void func_8018C0B0(void * arg0) {

    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern void func_80184CB8(s32*, s32);
    extern short D_801E05C4;
    if (*(u16 *)((char *)arg0 + 0x34) == 0) {
        if (func_80178970() != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            *(short *)((char *)arg0 + 0x2) = 3;
            ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_801E05C4);
        }
    }
}


extern s32 D_801E05CC;
extern s16 D_801E05C4;
extern s32 func_801847BC(void *, void *);
extern s32 func_80184BAC(s32, s32);
extern void func_80184CB8(s32 *, s32);
extern s32 func_801788B8(s32, s32);
extern s32 func_8018C1E0(void*);

void func_8018C114(void *arg0) {
    s32 s0 = (s32)arg0;
    s32 m;
    s32 r = 1;

    if (func_801847BC(arg0, &D_801E05CC) == 0) {
        return;
    }
    if (func_80184BAC(6, 0x12) != 0) {
        m = 1;
    } else {
        m = (func_80184BAC(0x12, 0x15) != 0) << 1;
    }
    switch (m) {
    case 0:
        r = 1;
        break;
    case 1:
        r = 2;
        break;
    case 2:
        r = 3;
        break;
    default:
        goto tail;
    }
    *(s16 *)((char *)s0 + 0x2) = r;
    func_80184CB8((s32 *)s0, (s32)&D_801E05C4);
tail:;
    {
        s32 v1 = *(s32 *)((char *)s0 + 0x68);
        *(s16 *)((char *)v1 + 0xC) = 0x7FFF;
    }
    *(s32 *)((char *)s0 + 0xD4) = func_801788B8((s32)s0, (s32)&func_8018C1E0);
}


#include "common.h"

DEFINE_func_8018C1E0()  /* dedup: shared engine-core @0x8018C1E0 (src/shared) */



extern void func_80184CB8(s32*, s32);
    extern short D_801E06A8;
    void func_8018C24C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_801E06A8);
    }




extern s32 func_80029504(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern s32 func_80184D00(void);
extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern void func_80184CB8(s32*, s32);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_8018C3F0(void*);

void func_8018C278(void *a0) {

    extern short D_801E06A8;
    void *s0 = a0;
    s32 v0;
    s32 v1;
    void *v1p;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)s0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(s0);
    }
    func_8001C214(*(s32 *)((u8 *)s0 + 0x20), 0);

    v1 = func_80029504();
    if (v1 < 0xC8) {
        v0 = func_80184D00();
        if (v0 == 3) {
            v0 = 2;
        } else {
            v0 = func_80184BAC(0xA, 0x10);
            if (v0 != 0) {
                v0 = 1;
            } else {
                v0 = 2;
            }
        }
    } else if (v1 < 0x258) {
        func_8012CAE4(s0);
        return;
    } else if (v1 < 0x384) {
        if (v1 < 0x276) {
            func_8012CAE4(s0);
            return;
        }
        v0 = 1;
    } else {
        v0 = 1;
    }

    *(s16 *)((u8 *)s0 + 0x2) = (s16)v0;
    __asm__ __volatile__("");
    func_80184CB8((s32 *)s0, (s32)&D_801E06A8);

    v1p = *(void **)((u8 *)s0 + 0x68);
    *(s16 *)((u8 *)v1p + 0xC) = 0x7FFF;
    *(s32 *)((u8 *)s0 + 0xD4) = func_801788B8((s32)s0, (s32)&func_8018C3F0);
}



extern void (*D_801E077C[])(void);

void func_8018C368(void *a0) {
    D_801E077C[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80178CBC(s32*, s32);
    extern short D_801E070C;
    void func_8018C3A4(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        ((void (*)(s32, s32))func_80178CBC)((int)arg0, (int)&D_801E070C);
    }


extern s32 func_800D0EC4();
s32 func_8018C3D0(void) {
    return func_800D0EC4() == 0;
}


#include "common.h"

DEFINE_func_8018C3F0()  /* dedup: shared engine-core @0x8018C3F0 (src/shared) */



void func_8018C494(void *a0) {
    s32 v1 = func_80029504();
    s32 v0;

    if (v1 < 0xC8) {
        v0 = func_80184D00();
        v1 = 3;
        if (v0 == v1) goto call_func_8018C24C;
        goto call_func_80184BAC;
    } else if (v1 >= 0x258) {
        if (v1 < 0x384) {
            goto call_func_80184BAC;
        } else {
            v0 = func_80184E44();
            v1 = 1;
            if (v0 == v1) goto call_func_8018C24C;
        }

call_func_80184BAC:
        v0 = func_80184BAC(0xA, 0x10);
        if (v0 != 0) return;
    } else {
        return;
    }

call_func_8018C24C:
    func_8018C24C(a0);
}


extern s32 func_80029504(void);
extern s32 func_80184D00(void);
extern s32 func_80184E44(void);
extern s32 func_80184BAC(s32 arg0, s32 arg1);
extern void func_80184CB8(s32*, s32);
extern short D_801E06A8;

void func_8018C518(void *a0) {
    void *s0 = a0;
    s32 v1 = func_80029504();
    s32 v0;

    if (v1 < 0xC8) {
        v0 = func_80184D00();
        v1 = 3;
        if (v0 == v1) {
            return;
        }
        v0 = func_80184BAC(0xA, 0x10);
        if (v0 == 0) {
            return;
        }
        v0 = 1;
    } else if (v1 < 0x258) {
        v0 = 1;
    } else if (v1 < 0x384) {
        v0 = func_80184BAC(0xA, 0x10);
        if (v0 == 0) {
            return;
        }
        v0 = 1;
    } else {
        v0 = func_80184E44();
        v1 = 1;
        if (v0 == v1) {
            return;
        }
        v0 = func_80184BAC(0xA, 0x10);
        if (v0 == 0) {
            return;
        }
        v0 = 1;
    }

    *(s16 *)((char *)s0 + 0x2) = 0x1;
    ((void (*)(s32, s32))func_80184CB8)((s32)s0, (s32)&D_801E06A8);
}



extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80184CB8(s32*, s32);

void func_8018C5AC(void * arg0) {

    extern short D_801E06A8;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80184CB8)((int)arg0, (int)&D_801E06A8);
    }
}



extern void (*D_801E3AF4[])(void);

void func_8018C5FC(void *a0) {
    D_801E3AF4[*(u16 *)((s32)a0 + 0x2)]();
}


/* Declarations conformed to the TU (ov_SC04_018_jr_8017AE2C.c) — lever (A):
 *   func_8012A828 : TU declares `extern void func_8012A828(s32*, s32);`
 *                   at L3460 / L4615 / L5083 / L5372 / L5859 / L6004 / L6155 /
 *                   L6479 / L6504 / L6529.  The draft's `(s32, s32)` form caused
 *                   the 7697-vs-6529 conflict.  Conformed here; the type
 *                   disagreement is pushed to a cast at the call site.
 *   D_8018D540    : TU declares `extern u8 D_8018D540[];` (block scope, L3467).
 *                   Conformed; `(s32)D_8018D540` == `(s32)&D_8018D540`.
 *   func_801788B8 : verbatim from TU L2532 / L7756 (below the splice point).
 *   func_8012C354, D_801E39E0, func_8018C730, func_8018C638 : no other
 *                   declaration anywhere in the TU (func_8018C730 / func_8018C638
 *                   appear only as INCLUDE_ASM, which emits no C declaration).
 *
 * Body: the original draft was NOT byte-correct.  `*(u16 *)(x + 2) = 1;` must be
 * sequenced BEFORE the func_8012A828 call, not after it — with it after, gcc
 * coalesces the store base onto $a0 (`sh v0,2(a0)`) and re-emits the arg copy,
 * giving a 6-instruction ADDRESSING/cse diff.  Moved above the call; both stores
 * now retire off $s0 and the sh lands in the jal delay slot, as in the target. */

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern s32 func_801788B8(s32 arg0, s32 arg1);

extern M2C_UNK D_801E39E0;
extern u8 D_8018D540[];
extern void func_8018C730(void);

void func_8018C638(s32 a0) {
    s32 s0 = a0;
    if (func_8012C354(a0, (s32)&D_801E39E0)) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(u16 *)(s0 + 0x2) = 1;
        func_8012A828((s32 *)s0, (s32)D_8018D540);
        func_801788B8(s0, (s32)func_8018C730);
    }
}


DEFINE_func_8018C69C()  /* dedup: shared engine-core @0x8018C69C (src/shared) */

extern signed char D_801E3AD0[];
extern void func_80178CBC(s32 *a0, s32 a1);

void func_8018C6A4(s32 *a0)
{
    s32 v0;

    v0 = *(s16 *)((s32)a0 + 0x70);
    v0 = v0 * 4;
    func_80178CBC(a0, *(s32 *)((s32)D_801E3AD0 + v0));
    *(s16 *)((s32)a0 + 0x2) = 0x3;
}



extern int func_80178970(void);
extern void func_80178D18(void);

void func_8018C6F0(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

void func_8018C730(void)
{
    register s32 a0r __asm__("$4");
    register s32 base __asm__("$16");
    register s32 ret __asm__("$2");

    base = (s32)a0r;
    if (func_8012BD14(*(s32 *)(base + 0x64)) <= 0x1000) {
        *(s16 *)(*(s32 *)(base + 0x64) + 0x2) = 2;
        func_80178BF8();
        __asm__ __volatile__("" : "=r"(ret) : "0"((s32)func_80172710));
        return;
    }
    __asm__ __volatile__("" : "=r"(ret) : "0"(0));
}



extern void (*D_801E3BA4[])(void);

void func_8018C78C(void *a0) {
    D_801E3BA4[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018C7C8(s32 a0) {
    extern u8 D_801E3B9C[];
    extern void func_8012E8E0(s32 a0, s32 a1);
    func_8012E8E0(a0, (s32)D_801E3B9C);
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);

void func_8018C7F0(s32 a0) {
    extern u8 D_801DE748[];
    extern u8 D_801E3B9C[];
    s32 v0;
    s32 v1;

    v1 = func_80029504();
    if (v1 < 200) goto L850;
    if (v1 < 600) {
        if ((func_80029178(0x106) & 0xFF) == 0) goto L850;
        goto L840;
    } else {
        if (v1 >= 630) goto L850;
    }
L840:
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 != 0) goto L860;
L850:
    func_8012CAE4((void *)a0);
    return;
L860:
    func_8001C214(v0, (s32)D_801DE748);
    func_8012E8E0(a0, (s32)D_801E3B9C);
    *(s16 *)(*(s32 *)(a0 + 0x68) + 0xC) = 0x7FFF;
    *(s16 *)(a0 + 0x2) = 1;
}


extern u16 D_80126B5E;
extern u16 D_80126B66;
extern u16 D_80126B62;

s32 func_8018C8A8(void)
{
    s16 v1;
    s32 result;

    v1 = *(s16 *)&D_80126B5E;
    if (v1 < 0x400) {
        result = 0;
    } else if (v1 >= 0x501) {
        result = 0;
    } else {
        v1 = *(s16 *)&D_80126B66;
        if (v1 < 0x580) {
            result = 0;
        } else if (v1 >= 0x601) {
            result = 0;
        } else {
            v1 = *(s16 *)&D_80126B62;
            result = (v1 >= -0x200);
        }
    }
    return result;
}



extern void func_8012B2CC(s32 arg);
    void func_8018C90C(void *arg0) {
        s32 *p = *(s32 **)((char *)arg0 + 0x20);
        *(s16 *)((char *)arg0 + 0x2) = 2;
        *(s16 *)((char *)p + 0x12) = -0x600;
        func_8012B2CC((s32)arg0);
    }


extern void func_8012B2CC(s32 arg);
    void func_8018C93C(void *a0) {
        s32 v1 = *(s32 *)((char *)a0 + 0x20);
        *(s16 *)((char *)a0 + 0x2) = 0x4;
        *(s16 *)(v1 + 0x12) = 0x600;
        func_8012B2CC((s32)a0);
    }


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern void func_8018CB18(void);
extern u8 D_801DE040[];
extern u8 D_801DE130[];
extern u8 D_801E3BAC[];
extern u8 D_801E3BBC[];

void func_8018C96C(void *arg0) {
    s32 v0;
    s32 t;
    s32 *p;

    v0 = ((s32 (*)(void *))func_8012C1B8)(arg0);
    *(s32 *)((char *)arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(arg0);
    } else {
        func_8001C214(v0, *(s16 *)((char *)arg0 + 0x70) == 0 ? (s32)&D_801DE040[0] : (s32)&D_801DE130[0]);
        *(s16 *)((char *)arg0 + 0x5C) = 0x800;
        *(s32 *)((char *)arg0 + 0x58) =
            (s32)&D_801E3BBC[*(s16 *)((char *)arg0 + 0x70) * 0x10] | 0x40000000;
        func_8012E8E0((s32)arg0, (s32)&D_801E3BAC[*(s16 *)((char *)arg0 + 0x70) * 8]);
        *(s16 *)(*(s32 *)((char *)arg0 + 0x68) + 0xC) = 0x7FFF;
        t = func_80029504();
        if ((func_80029178(0xF6) & 0xFF) == 0 && t < 0xE6) {
            if (*(s16 *)((char *)arg0 + 0x70) == 0) {
                *(s16 *)((char *)arg0 + 0x2) = 1;
                *(s16 *)((char *)arg0 + 0x34) = 0;
                func_801788B8((s32)arg0, (s32)func_8018CB18);
            } else {
                s32 *q = *(s32 **)((char *)arg0 + 0x20);
                *(s16 *)((char *)arg0 + 0x2) = 3;
                *(s16 *)((char *)arg0 + 0x34) = 0;
                *(s16 *)((char *)q + 0x12) = 0;
                *(s32 *)((char *)arg0 + 0x1C) = 0x30;
            }
        } else {
            if (*(s16 *)((char *)arg0 + 0x70) == 0) {
                p = *(s32 **)((char *)arg0 + 0x20);
                *(s16 *)((char *)arg0 + 0x2) = 2;
                *(s16 *)((char *)p + 0x12) = -0x600;
                func_8012B2CC((s32)arg0);
            } else {
                p = *(s32 **)((char *)arg0 + 0x20);
                *(s16 *)((char *)arg0 + 0x2) = 4;
                *(s16 *)((char *)p + 0x12) = 0x600;
                func_8012B2CC((s32)arg0);
            }
        }
    }
}



extern void (*D_801E3CEC[])(void);

void func_8018CADC(void *a0) {
    D_801E3CEC[*(u16 *)((s32)a0 + 0x2)]();
}


/* func_8018CB18 — state-2 gate for the SC04_018 actor state machine.
 *
 * Reads the actor's linked object (a0->0x64), requires its state word (+0x2) == 1
 * and the actor's own +0x34 flag clear, then asks func_8018C8A8() for permission;
 * on success it stamps 1 into the linked object's +0x34, pokes func_80178BF8() and
 * returns the address of the next callback (func_80172710).
 *
 * DECL SURFACE (§73 / §37): the TU already carries a fleet-canonical forward decl
 *   `extern void func_8018CB18(void);`   (ov_SC04_018_jr_8017AE2C.c L7759)
 * used only to take the function's ADDRESS at L7786.  The byte-true signature
 * disagrees on BOTH §73 axes (return void->s32 AND params void->void*), so neither
 * the fleet widen nor a cast-at-use fixes it.  Instead the definition is emitted
 * under the C identifier `aF8018CB18` with an __asm__("func_8018CB18") label
 * (§37 asm-label alias, the proven function-definition form — cf.
 * src/ov_SC03_099/ov_SC03_099_after.c L533).  The C-level name never collides with
 * the canonical decl, the emitted symbol is unchanged, and codegen is byte-identical
 * (verified: match_one MATCH 31/31 with and without the alias).
 *
 * ORACLE: .venv/bin/python tools/match_one.py func_8018CB18 \
 *           --c .run/s7/ov_SC04_018/func_8018CB18.c \
 *           --asm-subdir asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_8017AE2C  -> MATCH (31 ins)
 */

extern s32 func_8018C8A8(void);
extern s32 func_80178BF8();      /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2539) */
extern void func_80172710(void); /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2231) */

s32 aF8018CB18(void *a0) __asm__("func_8018CB18");

s32 aF8018CB18(void *a0)
{
    if (*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) != 1) {
        return 0;
    }
    if (*(u16 *)((s32)a0 + 0x34) != 0) {
        return 0;
    }
    if (func_8018C8A8() == 0) {
        return 0;
    }
    *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x34) = 1;
    func_80178BF8();
    return (s32)func_80172710;
}


void func_8018CB94(void *a0)
{
    s32 result;

    *(u16 *)((s32)a0 + 0x34) = *(u16 *)((s32)a0 + 0x34) + 1;

    func_8002D4C8(0x7A0, 0);
    func_80029124(0xF6, 1);
    func_800D0F4C(0x59);

    result = func_8012E57C(0x1F2, 1);

    if (result) {
        *(u16 *)(result + 0x34) = *(u16 *)(result + 0x34) + 1;
    }
}





s32 func_8018CC04(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801E79A0;
    return !(D_801E79A0 ^ 2);
}


extern void func_8002D4C8(s32, s32);
void func_8018CC1C(void) {
    func_8002D4C8(0x7E0, 0);
}

