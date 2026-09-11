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
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_8018D0E8;
extern u8 D_8018D058;
extern u8 D_8018D034;
extern u8 D_8018D010;
extern u8 D_8018D0C4;
extern u8 D_8018D0A0;
extern u8 D_8018D07C;
extern u8 D_8018CFEC;
extern void func_80145934(void);
extern u8 D_8018D178;
extern u8 D_8018D154;
extern u8 D_8018D130;
extern u8 D_8018D10C;
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
extern unsigned char D_8018C570[];
extern unsigned char D_8018C5A0[];
extern unsigned char D_8018C5F0[];
extern unsigned char D_8018C620[];
extern unsigned char D_8018C650[];
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
extern void (*D_8018C6A0[])(void *);
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
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_8018C768[];
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
extern u8 D_8018C7F0[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018C7F8;
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
extern int D_801E0650;
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
extern s32 D_801E0654;
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
extern s32 D_8018C828;
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
extern void (*D_8018C8D0[])(void);
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
extern void (*D_8018C8F4[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018C8E4;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018C908[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018C914[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018C924[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018C93C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018C92C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018C950[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018C96C[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018C95C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018C980[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018C994[])(void);
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
extern s32 D_8018C9A8;
extern void (*D_8018C9D0[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018C9B0;
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
extern int (*D_8018CA1C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018CA20[])(void);
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
extern unsigned short D_8018CE84[];
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
extern void (*D_8018CE94[])(void);
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
extern int D_801E0688;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018CEBC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018CE9C;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018CEAC;
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
extern void (*D_8018CEFC[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018CF04[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018CED0;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018CF10[])(void);
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
extern u8 D_8018CEE0;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801E0690;
extern s32 D_801E069C;
extern s32 D_801E06A0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018CF4C[])(s32 *);
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
extern s32 D_8018CF20[];
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
extern s32 D_801E0698;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018D19C[])(void);
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
extern char D_8018CFBC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018D240[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018D394[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018D1B0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018D39C[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018D1C0;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018D1E0;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018D3A4[])(void);
extern void func_8015ADB0(s32);
extern void func_8015AD78(s32 a0);
extern void func_8015ADB0(s32 arg0);
extern s32 D_800D4A9C;
extern int func_8015B6F4(int param_1);
extern u8 D_800D4F8C[];
extern s32 func_8015B7B4(s32 a0);
extern u8 D_800D4BE0[];
extern s32 func_8014A51C(int param_1);
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
extern void (*D_8018D3CC[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018D3D8[])(void);
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
extern void (*D_8018D24C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018D47C;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018C560[];
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
extern unsigned char D_8018D490[];
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
extern s8 D_8018D4CC[];
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
extern u16 D_8018D514;
extern u16 D_8018D516;
extern u16 D_8018D518;
extern s32 D_8018D51C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018D524;
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
extern int D_8018D230;
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
extern unsigned int D_8018D5A8[];
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
extern void (*D_8018D658[])(void);
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
extern int func_801497A8(s32 *a0);
extern int func_80161BE0(void *param_1);
extern u16 D_8018D688[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018D6EC;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801E06A8[];
extern void func_8016216C(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018D710[])(void);
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
extern int D_801E0700[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018D758[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018D748;
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
extern char D_801DFB40[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018D760[])(void);
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
extern void (*D_8018D7B4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018D77C;
extern s16 D_8018D7B0;
extern s16 D_8018D7AE;
extern s16 D_8018D7AC;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018D7C0[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E0760;
extern u8 D_801E0761;
extern u8 D_801E0762;
extern u8 D_801E0763;
extern u8 D_801E0764;
extern u8 D_801E0765;
extern u8 D_801E0766;
extern u8 D_801E0767;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018D7D0[])(void);
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
extern s32 D_801E07A0;
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
extern void (*D_8018D814[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018D890[];
extern s32 D_8018D8B0[];
extern u8 D_8018D92C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018D94C[];
extern u8 D_8018D96C[];
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
extern void (*D_8018DA08[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018DA84[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801DFB50;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018DA90[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018DA98[])(void);
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
extern void (*D_8018DB60[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018DB70[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018DB80[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018DB8C[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018DAEC[];
extern u8   D_8018DB00[];
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
extern void (*D_8018DBA4[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018DBAC[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018DBB4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(s32 *p);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018DBBC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018DBC4[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018DBCC[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018DBD4[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018DC88[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018DC90[])(void);
extern void func_80169F00(void *a0);
extern char D_8018DC40[];
extern char D_8018DC00[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018DCC8[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018DCD4[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018DD1C[])(void);
extern void func_8016AB30(void *a0);
extern void func_8016B234(s32 param_1);
extern void func_8016AFB0(s32 a0);
extern void func_8016B114(void *arg0);
extern s32 func_8016B448(s32, s32);
extern s32 func_8016BA48(s32 a0);
extern void func_8016B3F4(s32 a0);
extern s32 func_8016B428(s32 a0);
extern void func_8016B984(void *a0);
extern s32 func_8016B448(s32 arg0, s32 arg1);
extern void (*D_8018DD98[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E0AC0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018DD8C[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018DDD0[];
extern unsigned short D_8018DDD8[];
extern unsigned short D_8018DDE0[];
extern unsigned char D_801E0AC8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E0AC0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018DDE8[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E0BFC;
extern M2C_UNK D_801E0C00;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E0B88;
extern void (*D_8018DE18[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E0C04[];
extern u8 D_801E0C0C[];
extern u8 D_801E0BBC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018DE20[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018DE3C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018DE44[])(void);
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
extern void (*D_8018DEAC[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018DE50;
extern u8 D_8018DE5C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018DEE0[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018DEE8[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018DF3C[])(void);
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
extern u16 D_8018DF70[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018DF60[];
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
extern s32 D_8018DF8C;
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
extern void (*D_8018E004[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018E00C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018E014[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018E01C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018E024[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018E02C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018E038[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018E044[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018E050[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018E060[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018E070[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018E078[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018E080[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018E088[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018E090[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018E098[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018E0A0[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018E0A8[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018E0B0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018E0B8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018E0C0[])(void);
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
extern void (*D_8018E0C8[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018E0D0[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018E0D8[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018E0E0[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018E0E8[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018E0F0[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018E0F8[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018E100[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018E108[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018E110[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018E118[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018E120[])(void);
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
extern void (*D_8018E164[])(void);
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
extern M2C_UNK D_8018E128;
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
extern void (*D_8018E194[])(void);
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
extern void (*D_8018E1D0[])(void);
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
extern void func_801748EC(void);
extern s32 func_801749C8();
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_8018E228[])();
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
extern void (*D_8018E238[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018E240[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_8018E3A8[])();
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
extern void (*D_8018E3B4[])();
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
extern M2C_UNK D_801DFD98;
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
extern s16 D_801E2570;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern short D_801E25E4;
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
extern s32 D_801E176C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E1794;
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
extern s16 D_801E1750;
extern s32 func_8017A3B0(void);
extern short D_801E178C;
extern short D_801E1788;
extern int func_800D0CA0(int);
extern int func_8001AAA0(s32 arg0);
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
extern s16 D_801E2528;
extern s16 D_801E252A;
extern s16 D_801E2534;
extern void func_8017AE2C(s32 param_1);
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801E1754;
extern u16 D_801E17D4;
extern u16 D_801E17D6;
extern u16 D_801E17D8;
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
extern s16 D_801E17CC;
extern s16 D_801E17CE;
extern s16 D_801E17D0;
extern s16 D_801E17C4;
extern s16 D_801E17C6;
extern s16 D_801E17C8;
extern void func_8017B7A8(void);
extern s16 D_801E17E4;
extern s16 D_801E17E6;
extern s16 D_801E17E8;
extern s16 D_801E17EC;
extern s16 D_801E17EE;
extern s16 D_801E17F0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801E17DC;
extern short D_801E17DE;
extern short D_801E17E0;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801E1774;
extern SV4 D_801E177C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801E179C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801E1798)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018E590[])(void);
extern void func_8017BE60(void *a0);
extern void (*D_8018E630[])(void);
extern void func_8017BE9C(void *a0);
extern void (*D_8018E638[])(void);
extern void func_8017BED8(void *a0);
extern void (*D_8018E640[])(void);
extern void func_8017BF14(void *a0);
extern u8 *func_8012913C(s32 a0);
extern s32 func_8012C750(s32 a0);
extern void func_8017BF50(s32 a0);
extern void func_8017C094(void);
extern void func_8017C100(s32 param_1);
extern void func_8017C1AC(s32 param_1);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32, s32);
extern void func_8012B260(u8 *a0);
extern void func_8017C1EC(s32 a0);
extern void func_8017C2B0(s32 a0);
extern void (*D_8018E660[])(void);
extern void func_8017C338(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_8017C374(s32 param_1);
extern void func_8017C538(u8 *p);
extern void (*D_8018E668[])(void);
extern void func_8017C5CC(void *a0);
extern u8 D_8018E654;
extern void func_8017C608(s32 a0);
extern void func_8017C6AC(int a0);
extern void func_8017C710(s32 arg0);
extern void func_8017D990(void *arg0);
extern s32 func_8017D5F0(s32 param_1);
extern s32 func_8017D640(void);
extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8001BFD0(void);
extern s32 func_8017D6D4(s32 a0);
extern void func_800D1EBC(void);
extern void func_8017D784(void *a0);
extern s32 func_8017D7A4(void *a0);
extern void (*D_8018E670[])(void);
extern void func_8017D88C(void *a0);
extern void (*D_8018E678[])(void);
extern void func_8017D8C8(void *a0);
extern void (*D_8018E684[])(void);
extern void func_8017D904(void *a0);
extern void (*D_8018E690[])(void);
extern void func_8017D940(void *a0);
extern s32 D_80127050;
extern void func_8017D97C(void *a0);
extern void (*D_8018E944[])(void);
extern void func_8017D990(void *a0);
extern void func_8017D9CC(u8 *a0);
extern void func_8017D9E0(s32 arg0);
extern void (*D_8018E94C[])(void);
extern void func_8017DA18(void *a0);
extern void func_8017DA54(void *a0);
extern void func_8017DA68(void *a0);
extern void func_8012A094(s32 a0);
extern void func_8017DB4C(void *a0);
extern void func_8017DA88(void);
extern void (*D_8018E954[])(void);
extern void func_8017DBBC(s32 *a0);
extern void func_8017DBC4(void *a0, u8 *a1);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017DD04(s32 param_1);
extern void (*D_8018F01C[])(void);
extern void func_8017E380(void *a0);
extern s32 func_8012E544(s32 arg);
extern void func_8017E510(void *a0);
extern void func_8017E534(void *a0);
extern void func_8017E558(s32 param_1);
extern void func_8017E57C(s32 param_1);
extern void func_8017E5A0(u8 *a0);
extern void func_801843E0(void*, s32);
extern void func_8017E880(void * arg0);
extern void (*D_8018F1C8[])(void);
extern void func_8017E8AC(void *a0);
extern void func_80178CBC(s32*, s32);
extern void func_8017E8E8(void * arg0);
extern void func_80029514(int);
extern void func_8017E914(void);
extern s32 func_801842D4(s32 arg0, s32 arg1);
extern void func_8017E880(void*);
extern void func_8017EA10(s32 *a0);
extern void func_8017EAB4(void * arg0);
extern void func_801843E0(void *a0, s32 a1);
extern void func_8017ECFC(s16 *a0);
extern void (*D_8018F330[])(void);
extern void func_8017ED28(void *a0);
extern void func_8017ED64(void * arg0);
extern void func_8017F09C(void);
extern void (*D_8018F46C[])(void);
extern void func_8017F20C(void *a0);
extern void func_8017F248(void);
extern void func_8017F40C(void * arg0);
extern void func_8017F840(void *a0);
extern void (*D_8018FBE4[])(void);
extern void func_8017F848(void *a0);
extern void func_8017FA34(void);
extern s32 D_801E1A18;
extern void func_8017FA84(void *a0);
extern void func_8017F768(void *a0);
extern void func_8017FB54(void);
extern void func_801851D8(s32 arg);
extern void func_8017FCE4(s32 a0);
extern void func_80185238(s32 arg);
extern void func_8017FD04(s32 arg0);
extern s32 func_8012E57C(s32 arg0, s32 arg1);
extern void func_8017FD24(void);
extern void func_8017FE10(s32 param_1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8017FE18(u8 *a0);
extern void func_8017FE3C(void *a0);
extern void func_8017FE78(s32 a0);
extern void func_8012E88C(s32 a0);
extern void func_801843B8(s32 a0);
extern void func_8017FFC8(void *a0);
extern void func_80180020(void * arg0);
extern void (*D_8018FC14[])(void);
extern void func_801801F4(void *a0);
extern void func_80180230(void *a0);
extern void func_801804B8(void);
extern void func_80180684(void);
extern void (*D_8018FDFC[])(void);
extern void func_8018068C(void *a0);
extern s32 func_801806C8(void *a0);
extern s32 func_8012C588(s32, s32);
extern void func_801806E0(void *arg0);
extern void func_80180704(s32 arg0);
extern void func_8018072C(void);
extern void (*D_8018FE1C[])(void);
extern void func_80180A24(void *a0);
extern s32 D_8018FE14;
extern void func_80180A60(void * arg0);
extern void (*D_8018FEA4[])(void);
extern void func_80180B40(void *a0);
extern void func_80180B7C(void);
extern void func_80178CBC(s32 *a0, s32 a1);
extern void func_80180B84(short *param_1);
extern void (*D_8018FF38[])(void);
extern void func_80181040(void *a0);
extern void (*D_8019003C[])(void);
extern void func_801812D0(void *a0);
extern void (*D_80190088[])(void);
extern void func_801814A4(void *a0);
extern s32 func_8018107C(s32 arg0);
extern void func_8018156C(void *a0);
extern s32 func_801817AC(void);
extern void func_80181810(void * arg0);
extern void func_8001C214(s32, s32);
extern void func_80181A1C(void *arg0);
extern void func_80181870(void *arg0);
extern void (*D_801901D0[])(void);
extern void func_801819E0(void *a0);
extern s32 func_80178BF8();      /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2539) */
extern void func_80172710(void); /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2231) */
extern s32 aF8018CB18();
extern s32 func_8012E57C(s32 a0, s32 a1);
extern void func_80181A98(void *a0);
extern s32 func_80181B08(void *a0);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_80181B20(s32 a0);
/* ==== end §8b carried decl layer ==== */


extern int func_80178970(void);
extern void func_80178D18(void);

/* ov_SC04_018 :: func_80181B44  — actor state machine, jump-table switch on the
 * u16 state word at +0x34.  Jump table = jtbl_801E59F8 (6 entries, index 0..5).
 *
 * KEY IDIOM (the whole crack): the table is indexed from ZERO — the target does
 *     lhu $v1,0x34($s0) ; sltiu $v0,$v1,6 ; sll $v0,$v1,2
 * with NO `addiu $v1,$v1,-1`.  gcc-2.7.2 sets minval = the LOWEST case label, so
 * a switch whose cases are 1..5 emits the subtract and `sltiu ...,5` (78 ins,
 * every later index shifted by one).  Writing an explicit empty `case 0: break;`
 * pulls minval down to 0, kills the subtract, and gcc's jump optimizer threads
 * case 0's empty body straight onto the epilogue — which is exactly what the real
 * jtbl shows (entry[0] = 0x8018CD60 = the function end, entries[1..5] = the five
 * real case bodies).  77 ins, byte-exact.
 *
 * The callees are the loose/unprototyped engine helpers: func_80178970 and
 * func_80178D18 are defined `(void)` in this overlay, but every caller in this TU
 * passes the actor pointer in $a0 anyway (K&R decls in the original source), so
 * they are declared here with empty parameter lists and CALLED with a0.
 */

extern s32  func_800D0F8C(s32);
extern void func_80178CBC();
extern void func_80181810();
extern u8   D_80190110[];
extern u8   D_80190128[];

void func_80181B44(void *a0)
{
    s32 *p;
    s32 t;

    switch (*(u16 *)((char *)a0 + 0x34)) {
    case 0:
        break;
    case 1:
        if (func_800D0F8C(0x59) == 0) {
            func_80178CBC(a0, D_80190110);
            *(u16 *)((char *)a0 + 0x34) = 2;
        } else {
            func_80178CBC(a0, D_80190128);
            *(u16 *)((char *)a0 + 0x34) = 3;
        }
        break;
    case 2:
        if (((s32 (*)(s32))func_80178970)(a0) != 0) {
            ((void (*)(s32))func_80178D18)(a0);
            *(u16 *)((char *)a0 + 0x2) = 1;
            *(u16 *)((char *)a0 + 0x34) = 0;
        }
        break;
    case 3:
        ((s32 (*)(s32))func_80178970)(a0);
        *(s32 *)((char *)a0 + 0x1C) = 0;
        break;
    case 4:
        ((s32 (*)(s32))func_80178970)(a0);
        p = *(s32 **)((char *)a0 + 0x20);
        *(u16 *)((char *)p + 0x12) = *(u16 *)((char *)p + 0x12) - 0x20;
        t = *(s32 *)((char *)a0 + 0x1C) + 1;
        *(s32 *)((char *)a0 + 0x1C) = t;
        if (t >= 0x30) {
            *(u16 *)((char *)a0 + 0x34) = 5;
        }
        break;
    case 5:
        if (((s32 (*)(s32))func_80178970)(a0) != 0) {
            ((void (*)(s32))func_80178D18)(a0);
            func_80181810(a0);
        }
        break;
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_80181840(void *a0);

void func_80181C78(void *a0) {
    u16 v1;

    v1 = *(u16 *)((char *)a0 + 0x34);
    if (v1 == 0) {
        return;
    }
    if (v1 != 1) {
        return;
    }
    {
        u16 *p = (u16 *)*(s32 *)((char *)a0 + 0x20);

        *(u16 *)((char *)p + 0x12) = *(u16 *)((char *)p + 0x12) + 0x20;
        if (((s32 (*)(void))func_8012BEE8)()) {
            func_80181840(a0);
        }
    }
}


void func_80181CE0(void) {
}

void func_80181CE8(void) {
}

s32 func_80181CF0(void) {
        return 0x27;
    }


void func_80181CF8(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
    }



extern void (*D_801901EC[])(void);

void func_80181D04(void *a0) {
    D_801901EC[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80184428(void);
extern s32 func_8018456C(void);
extern s32 func_801842D4(s32 arg0, s32 arg1);
extern u8 D_80078EBA;

s32 func_80181D40(void) {
    s32 v0;

    v0 = ((s32 (*)(void))func_80184428)();
    if (v0 == 3) {
        return 1;
    }
    v0 = func_8018456C();
    if (v0 == 1) {
        return 1;
    }
    if (D_80078EBA != 2) {
        return func_801842D4(0xC, 0x14) == 0;
    }
    return 1;
}


extern s32 func_80181D40();
extern void func_80181CF8(void *a0);

    void func_80181DA8(void *a0) {
        s32 s0;
        s0 = 1;
        *(s32 *)(*(s32 *)((char *)a0 + 0xCC) + 0xB0) = s0;
        if (func_80181D40() != s0) {
            return;
        }
        func_80181CF8(a0);
    }




    void func_80181DF4(s32 a0) {
        s32 *v1;
        v1 = *(s32 **)((s32)a0 + 0xCC);
        *(s32 *)((s32)v1 + 0xB0) = 2;
        if (func_80181D40() == 0) {
            *(s16 *)((s32)a0 + 0x2) = 1;
        }
    }


extern s32 func_8012E57C(s32 a0, s32 a1);

void func_80181E34(void *a0) {
    s32 v0;

    v0 = func_8012E57C(0x61, 0xD);
    *(s32 *)((char *)a0 + 0xCC) = v0;
    v0 = func_80181D40();

    if (v0 != 0) {
        v0 = 2;
    } else {
        v0 = 1;
    }

    *(s16 *)((char *)a0 + 0x2) = v0;
}


void func_80181E7C(void *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
    }



extern void (*D_80190200[])(void);

void func_80181E88(void *a0) {
    D_80190200[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_801842D4(s32 arg0, s32 arg1);
extern u8 D_80078EBA;
extern void func_80181E7C(void *a0);

void func_80181EC4(void *a0) {
    s32 v0;
    *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    if (D_80078EBA == 3) {
        v0 = 0;
    } else {
        v0 = func_801842D4(7, 0x13) != 0;
    }
    if (v0 == 0) {
        func_80181E7C(a0);
    }
}


extern s32 func_801842D4(s32 arg0, s32 arg1);
extern u8 D_80078EBA;

void func_80181F2C(void *a0) {
    s32 v0;
    *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 2;
    if (D_80078EBA == 3) {
        v0 = 0;
    } else {
        v0 = func_801842D4(7, 0x13) != 0;
    }
    if (v0 != 0) {
        *(s16 *)((s32)a0 + 2) = 1;
    }
}


extern s32 func_8012E57C(s32 a0, s32 a1);
extern s32 func_801842D4(s32 arg0, s32 arg1);
extern u8 D_80078EBA;

    void func_80181F90(void *a0) {
        s32 v0;
        v0 = func_8012E57C(0x61, 0x8);
        *(s32 *)((char *)a0 + 0xCC) = v0;
        if (D_80078EBA == 3) {
            v0 = 0;
        } else {
            v0 = func_801842D4(0x7, 0x13);
            v0 = (0U < (u32)v0) ? 1 : 0;
        }
        if (v0 != 0) {
            v0 = 1;
        } else {
            v0 = 2;
        }
        *(s16 *)((char *)a0 + 0x2) = v0;
    }


void func_80181FFC(s32 *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0x2;
    }



extern void (*D_80190214[])(void);

void func_80182008(void *a0) {
    D_80190214[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_80029178(s32 arg);
extern s32 func_80029504(void);
extern s32 func_801842D4(s32 arg0, s32 arg1);

s32 func_80182044() {
    if ((u32)(func_80029504() - 0x12C) < 0x12C) {
        if ((func_80029178(0xFA) & 0xFF) != 0) {
            return 0;
        }
    }
    return (0U < (u32)func_801842D4(0xA, 0x14)) ? 1 : 0;
}


extern s32 func_80182044(void);
extern void func_80181FFC(s32 *a0);

void func_80182098(void *a0) {
    *(s32 *)(*(s32 *)((char *)a0 + 0xCC) + 0xB0) = 1;
    if (func_80182044() == 0) {
        func_80181FFC(a0);
    }
}


extern s32 func_80182044(void);

void func_801820DC(a0)
s32 a0;
{
    s32 *v1;
    v1 = *(s32 **)((s32)a0 + 0xCC);
    *(s32 *)((s32)v1 + 0xB0) = 2;
    if (func_80182044() != 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
    }
}


extern s32 func_8012E57C(s32 arg0, s32 arg1);
extern s32 func_80182044(void);

void func_8018211C(void *a0) {
    s32 v0;

    v0 = func_8012E57C(0x61, 0xC);
    *(s32 *)((char *)a0 + 0xCC) = v0;
    v0 = func_80182044();

    if (v0 != 0) {
        v0 = 1;
    } else {
        v0 = 2;
    }

    *(s16 *)((char *)a0 + 0x2) = v0;
}


void func_80182164(void *a0) {
        M2C_FIELD(a0, s16 *, 0x2) = 2;
    }



extern void (*D_80190228[])(void);

void func_80182170(void *a0) {
    D_80190228[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_801842D4(s32 arg0, s32 arg1);
extern u8 D_80078EBA;
extern void func_80182164(void *a0);

    void func_801821AC(void *a0) {
        s32 v0;
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
        if (D_80078EBA == 0) {
            v0 = 0;
        } else {
            v0 = func_801842D4(0xB, 0x10) != 0;
        }
        if (!v0) {
            func_80182164(a0);
        }
    }


extern s32 func_801842D4(s32 arg0, s32 arg1);
extern u8 D_80078EBA;

void func_80182214(void *a0) {
    s32 v0;
    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    if (D_80078EBA == 0) {
        v0 = 0;
    } else {
        v0 = func_801842D4(0xB, 0x10) != 0;
    }
    if (v0 != 0) {
        *(s16 *)((char *)a0 + 2) = 1;
    }
}


extern s32 func_8012E57C(s32 a0, s32 a1);
extern s32 func_801842D4(s32 arg0, s32 arg1);
extern u8 D_80078EBA;

void func_80182278(void *a0) {
    s32 v0;

    *(s32 *)((char *)a0 + 0xCC) = func_8012E57C(0x61, 9);
    if (D_80078EBA == 0) {
        v0 = 0;
    } else {
        v0 = func_801842D4(0xB, 0x10) != 0;
    }
    if (v0 != 0) {
        v0 = 1;
    } else {
        v0 = 2;
    }
    *(s16 *)((char *)a0 + 2) = v0;
}



extern void (*D_80190234[])(void);

void func_801822E4(void *a0) {
    D_80190234[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80182320(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    }


extern s32 func_8012E57C(s32 a0, s32 a1);

    void func_80182330(s32 a0) {
        *(s16 *)(a0 + 0x2) = 1;
        *(s32 *)(a0 + 0xCC) = func_8012E57C(0x61, 0xA);
    }


extern s32 D_801E1A30[];
extern s32 D_801E1A4C;
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_8001D074(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);

void func_8018236C() {
    extern s32 D_801E1A30[];
    extern s32 D_801E1A4C;
    s32 i;

    i = 0;
    do {
        D_801E1A30[i] = ((s32 (*)(s32, s32))func_8001D074)(0x3E, 0x7D);
        (&D_801E1A4C)[i * 0x10] = 0;
        func_800233CC(&(&D_801E1A4C)[i * 0x10] - 1, 0x30);
        func_8001CD50(D_801E1A30[i], (s32)(&(&D_801E1A4C)[i * 0x10] - 1));
        ((s32 *)D_801E1A30[i])[1] |= 0xD0000040;
        i++;
    } while (i < 6);
}


extern s32 D_801E1BCC[];

void func_80182420(a0, a1)
s32 a0;
s32 a1;
{
    extern s32 D_801E1BCC[];
    register s32 rv __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 x = D_801E1BCC[0];
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
    __asm__("" :: "r"(rv));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B tus9)
}


extern s32 (*D_80190624[])(void);
extern void *D_801E1BC8;
extern void func_801824DC(s32 a0, s32 a1);

void func_80182488(s32 arg0)
{
    s32 v0;

    v0 = D_80190624[arg0]();
    if (v0 != -1) {
        func_801824DC((s32)D_801E1BC8, v0);
    }
}


void func_801824DC(s32 a0, s32 a1)
{
    extern u8 D_8019066C[];
    extern u16 D_800B99DA;
    extern void func_80182598(u16 *a0, s32 a1);
    s32 var_v1;
    s32 var_v0;
    s32 val;

    var_v1 = (D_8019066C[D_800B99DA & 0xF] == 0) ? 0x60 : 0x50;
    a1 += 1;
    var_v1 = var_v1 * a1 / 32;
    var_v0 = var_v1 / 2;
    *(s8 *)&val = var_v1;
    *((s8 *)&val + 1) = var_v1;
    *((s8 *)&val + 2) = var_v0;
    *((s8 *)&val + 3) = 0;

    if (*(s16 *)(a0 + 6) != -1) {
        do {
            func_80182598(a0, val);
            a0 += 8;
        } while (*(s16 *)(a0 + 6) != -1);
    }
}



/* func_80182598 (ov_SC04_018, ov_SC04_018_jr_8017AE2C) — MATCH (250 ins)
 *
 * Shadow/marker quad renderer: builds an outer quad (D_8019023C offset table)
 * through RotNclip4, rejects it on OTZ, builds the inner quad (D_801902BC)
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
extern void func_80182980(void *, s32);
extern s32 RotNclip4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern s32 RotTransPers4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern void *func_80010A08(s32);
extern s32 AddPrim(s32, void *);
extern void func_8012E28C(s32, s32);

void func_80182598(u16 *a0, s32 a1)
{

    extern s32 D_800A651C[][5];
    extern u16 D_8019023C[];
    extern u16 D_801902BC[];
    extern u16 D_8019035C[][4];
    extern u16 D_8019035E[][4];
    extern u16 D_80190360[][4];
    extern u16 D_80190362[][4];
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus9)

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
    register u16 *dst __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    s32 i;
    u8 *pk;
    s32 j;

    func_8012E32C();

    attr = a0[3];
    type = attr & 0xFF;
    type2 = type + zr;
    if ((attr & 0xF00) == 0x200) {
        func_80182980(a0, a1);
        return;
    }

    p1 = (u16 *)((u8 *)D_8019023C + type * 0x20);
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

    p1 = (u16 *)((u8 *)D_801902BC + type2 * 0x20);
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
        idx[0] = D_8019035C[j][0];
        idx[1] = D_8019035E[j][0];
        idx[2] = D_80190360[j][0];
        idx[3] = D_80190362[j][0];
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


extern s32 D_801E1A30[];
extern s32 D_801E1A48[];

void func_80182980(void *a0, s32 a1) {
    s32 v1;
    s32 *a2;

    v1 = ((u16 *)a0)[3] >> 12;
    a2 = (s32 *)D_801E1A30[v1];
    a2[1] &= 0x7FFFFFFF;
    D_801E1A48[v1 * 16] = a1;
    ((u16 *)a2)[4] = ((u16 *)a0)[0];
    ((u16 *)a2)[5] = ((u16 *)a0)[1];
    ((u16 *)a2)[6] = ((u16 *)a0)[2];
    ((u16 *)a2)[9] = (((u16 *)a0)[3] & 0xF) << 10;
}


extern void (*D_8019067C[])(void);

void func_801829F8(void *a0) {
    D_8019067C[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_801842D4(s32 arg0, s32 arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012BEE8(s32 a0);
extern s32 rand(void);

void func_80182A34(s32 param_1) {

    extern u8 D_8019068C[][4];
    s32 i;
    s32 v1;
    s32 uVar1;

    if (func_801842D4(7, 0x13) == 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (D_8019068C[*(s16 *)(param_1 + 0x100)][i] == *(s32 *)(param_1 + 0x1c)) {
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



extern void (*D_801906A8[])(void);

void func_80182B50(void *a0) {
    D_801906A8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801906B0[])(void);

void func_80182B8C(void *a0) {
    D_801906B0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801906C0[])(void);

void func_80182BC8(void *a0) {
    D_801906C0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801906D0[])(void);

void func_80182C04(void *a0) {
    D_801906D0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80182C40(void) {
}


extern s32 func_8012BEE8(s32 a0);
extern s32 rand(void);

void func_80182C48(s32 param_1) {
    s32 uVar1;
    s32 iVar2;
    register s32 iVar3 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 iVar4 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
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



extern void (*D_801906E0[])(void);

void func_80182DF4(void *a0) {
    D_801906E0[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80182E30(void)
{

    extern u16 D_800B99DA;
    extern s32 D_80126B58;
    extern u8 D_800AF648;
    extern s32 D_801906E8;
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
        if (RotTransPers((s32)&D_801906E8, (s32)&sxy, &pv, &flag) <= 0 || flag < 0) {
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
            dist = ((s32 (*)(s32, s32))func_80013450)((s32)(p + 1), (s32)&D_801906E8);
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


extern s32 D_8019037C;
extern void *D_801E1BC8;
extern void func_80182420(s32 arg0, s32 arg1);

void func_80182F8C(void) {
    *(void **)&D_801E1BC8 = &D_8019037C;
    func_80182420(0x474, 0x4B0);
}


extern void func_80182420(s32 arg0, s32 arg1);
    extern s32 D_801903B4;
    extern void *D_801E1BC8;
    void func_80182FC0(void) {
        D_801E1BC8 = &D_801903B4;
        func_80182420(0x474, 0x4EC);
    }


extern s32 D_801903EC;
extern void *D_801E1BC8;
extern void func_80182420(s32 arg0, s32 arg1);

void func_80182FF4(void) {
    *(void **)&D_801E1BC8 = &D_801903EC;
    func_80182420(0x474, 0x4B0);
}



extern void func_80182420(s32 arg0, s32 arg1);

void func_80183028(void) {

    extern s32 D_80190414;
    D_801E1BC8 = &D_80190414;
    func_80182420(0x474, 0x4B0);
}



extern void func_80182420(s32 arg0, s32 arg1);

void func_8018305C(void) {

    extern s32 D_8019044C;
    D_801E1BC8 = &D_8019044C;
    func_80182420(0x474, 0x528);
}


extern s32 D_80190484;
extern s32 func_80029504(void);
extern void *D_801E1BC8;
extern void func_80182420(s32 arg0, s32 arg1);

s32 func_80183090() {
    s32 var_s0;

    D_801E1BC8 = (s32)&D_80190484;
    var_s0 = ((s32 (*)(s32, s32))func_80182420)(0x168, 0x1A4);
    if (var_s0 == -1) {
        var_s0 = ((s32 (*)(s32, s32))func_80182420)(0x474, 0x4EC);
    }
    if ((u32)(func_80029504() - 200) < 220) {
        return -1;
    }
    return var_s0;
}



extern void func_80182420(s32 arg0, s32 arg1);

void func_80183104(void) {

    extern s32 D_801904C4;
    D_801E1BC8 = &D_801904C4;
    func_80182420(0x474, 0x1A4);
}




extern s32 func_80029504(void);
extern void func_80182420(s32 arg0, s32 arg1);

s32 func_80183138(void) {

    extern s32 D_801904FC;
    s32 v;
    D_801E1BC8 = (s32)&D_801904FC;
    v = func_80029504();
    if ((u32)(v - 0x64) < 0x1F4) {
        return -1;
    }
    func_80182420(0x96, 0xF0);
}



extern void func_80182420(s32 arg0, s32 arg1);

void func_80183184(void) {

    extern s32 D_8019051C;
    D_801E1BC8 = &D_8019051C;
    func_80182420(0x12c, 0x1A4);
}


extern void func_80182420(s32 arg0, s32 arg1);
    extern s32 D_8019056C;
    extern void *D_801E1BC8;
    void func_801831B8(void) {
        D_801E1BC8 = &D_8019056C;
        func_80182420(0x474, 0x4B0);
    }



extern void func_80182420(s32 arg0, s32 arg1);

void func_801831EC(void) {

    extern s32 D_801905CC;
    D_801E1BC8 = &D_801905CC;
    func_80182420(0x474, 0x4B0);
}




extern s32 func_80029504(void);
extern void func_80182420(s32 arg0, s32 arg1);

s32 func_80183220(void) {

    extern s32 D_801905FC;
    s32 v;
    D_801E1BC8 = (s32)&D_801905FC;
    v = func_80029504();
    if ((u32)(v - 0x64) < 0x1F4) {
        return -1;
    }
    func_80182420(0x474, 0x78);
}



extern void func_80182420(s32 arg0, s32 arg1);

void func_8018326C(void) {

    extern s32 D_80190614;
    D_801E1BC8 = &D_80190614;
    func_80182420(0x564, 0x1A4);
}


extern s32 func_801832A0(void);

s32 func_801832A0(void) {
    return -1;
}




void func_801832A8(void)
{
    extern u8 D_80078EB0;
    extern u8 D_80078EB1;
    extern s32 D_801E1BCC[];
    extern s32 D_801E245C;
    extern s32 D_801E1A30[];
    extern void func_80182488(s32 arg0);
    extern void func_80182E30(void);
    s32 i;
    s32 mask;
    s32 *ptr;

    i = 0;
    mask = 0x80000000;
    D_801E1BCC[0] = D_80078EB1 * 60 + D_80078EB0;
    ptr = D_801E1A30;

    while (i < 6) {
        *(s32 *)(*ptr + 4) |= mask;
        ptr++;
        i++;
    }

    for (i = 2; i < 18; i++) {
        func_80182488(i);
    }

    func_80182E30();

    if (D_801E245C != 0) {
        D_801E245C = D_801E245C - 1;
    }
}


extern void func_8001C214(s32, s32);
extern void func_8012C1B8(void);
extern s32 func_8012C588(s32, s32);
extern void func_8012CAE4(void *a0);
extern void func_8018236C(void);

    void func_80183364(void *a0) {
        s32 v0;
        u16 val;
        v0 = ((s32 (*)(void *))func_8012C1B8)(a0);
        *(s32 *)((char *)a0 + 0x20) = v0;
        if (v0 == 0) {
            func_8012CAE4(a0);
            return;
        }
        func_8001C214(v0, 0);
        ((void (*)(s32, s32))func_8012C588)(0x13F, 0);
        ((void (*)(s32, s32))func_8012C588)(0x66, 0);
        ((void (*)(s32, s32))func_8012C588)(0x65, 0);
        ((void (*)(s32, s32))func_8012C588)(0x14C, 0);
        ((void (*)(s32, s32))func_8012C588)(0x335, 0);
        ((void (*)(s32, s32))func_8012C588)(0x3D9, 0);
        val = *(u16 *)((char *)a0 + 0x72);
        *(u16 *)((char *)a0 + 0x2) = 1;
        val |= 0x1000;
        *(u16 *)((char *)a0 + 0x72) = val;
        func_8018236C();
    }


extern u8 D_80190684[];
extern void func_8012E8E0(s32 a0, s32 a1);

    void func_80183410(s32 a0) {
        *(s16 *)(a0 + 0x2) = 1;
        func_8012E8E0(a0, (s32)&D_80190684);
        *(s16 *)(a0 + 0xFE) = 0;
        *(s16 *)(a0 + 0xFC) = 0x80;
    }


extern void func_8012B200(u8 *a0);

/*
 * func_80183454 -- ov_SC04_018 / ov_SC04_018_jr_80188E1C, 71 ins, family reach x6.
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

void func_80183454(u8 *arg0)
{

    extern u8 D_800D387C[];
    extern u8 D_800D3888[];
    u8 *param_1;
    s32 raw;
    u32 buf[6];

    do { param_1 = arg0; } while (0);
    {
        s32 s0;   /* $s1 -- scoped: dead after func_80128EA8 */
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
        s32 full;
        s32 low;
        full = *(s32 *)buf;
        low = *(s16 *)buf;
        *(s32 *)(param_1 + 0x48) = 0;
        *(s32 *)(param_1 + 0x44) = low;
        *(s32 *)(param_1 + 0x4C) = full >> 16;
    }
}


extern void func_8012AD80(s32 a0);
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);
extern s32 func_8012BEE8(s32 a0);

void func_80183570(s32 a0) {
    s32 owner = *(s32 *)(a0 + 0xCC);
    s32 obj;

    func_8012AD80(a0);
    obj = *(s32 *)(a0 + 0xCC);
    *(u16 *)(obj + 8) = *(u16 *)(a0 + 6);
    *(u16 *)(obj + 0xA) = *(u16 *)(a0 + 0xA);
    *(u16 *)(obj + 0xC) = *(u16 *)(a0 + 0xE);
    if ((*(u32 *)(a0 + 0x1C) & 7) == 0) {
        func_80128ED8(owner, (s32 *)(a0 + 0xD0));
    }
    if (func_8012BEE8(a0) != 0) {
        func_80016714((void *)owner, 0x38);
        func_8012C218((void *)a0);
    }
}



extern void func_8012B414(int a0);
    void func_8018360C(s32 arg0) {
        s32 temp_v1 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(temp_v1 + 0x14) += 0x8;
        ((void (*)(void))func_8012B414)();
    }


    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern s32 D_80194714[];
    extern s32 D_801906B8[];
    void func_80183640(s32 a0) {
        s32 v0;
        v0 = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(a0 + 0x20) = v0;
        if (v0 == 0) {
            func_8012CAE4((void *)a0);
            return;
        }
        func_8001C214(v0, (s32)D_80194714);
        func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);
        func_8012E8E0(a0, (s32)D_801906B8);
        *(s16 *)(a0 + 0x2) = 1;
    }




void func_801836B8(s32 arg0)
{
    extern u16 D_800B99DA;
    extern s32 func_8004787C(s32 a0);
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x10) = (u32)func_8004787C(D_800B99DA * 48) >> 5;
}


extern s32 func_80029504(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 D_801943AC[];
extern s32 D_801906C8[];

void func_80183700(s32 a0) {
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
    func_8001C810(v0, (s32)D_801943AC);
    *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x8000;
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);
    func_8012E8E0(a0, (s32)D_801906C8);
    *(s16 *)(a0 + 0x2) = 1;
    return;
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8012E8E0(s32 a0, s32 a1);

void func_801837A4(s32 a0) {
    extern s32 D_801948AC[];
    extern s32 D_801906D8[];
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
    } else {
        func_8001C214(v0, (s32)D_801948AC);
        func_8012E8E0(a0, (s32)D_801906D8);
        *(s16 *)(a0 + 0x2) = 1;
        *(s16 *)(a0 + 0x34) = 0;
        *(s32 *)(a0 + 0xDC) = 0;
        *(s32 *)(a0 + 0xE0) = 0;
        *(s32 *)(a0 + 0xE4) = 0;
    }
}



extern void (*D_80190700[])(void);

void func_8018381C(void *a0) {
    D_80190700[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern u32 D_801906F0;

void func_80183858(s32 arg0) {
    s32 v0 = ((s32 (*)(s32))func_8012C1B8)(arg0);
    *(s32*)((u8*)arg0 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(arg0);
    } else {
        func_8001C214(v0, 0);
        *(s16*)((u8*)arg0 + 0x2) = 1;
        *(s16*)((u8*)arg0 + 0x5C) = 0x20;
        *(s32*)((u8*)arg0 + 0x58) = (u32)&D_801906F0 | 0x40000000;
        *(s16*)((u8*)(*(s32*)((u8*)arg0 + 0x20)) + 0x12) = *(u16*)((u8*)arg0 + 0xFC);
    }
}


void func_801838D4(void) {
}


extern void (*D_80190738[])(void);

void func_801838DC(void *a0) {
    D_80190738[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_80183C34(void *arg0);
extern s32 func_8012AD50(void *arg0);

/* 0x24-stride record at D_801E1BD0 (4 entries; asm/ov_SC04_018/data/tail18.data.s) */


void func_80183918(void *arg0) {

    extern u8 D_80078EB1;
    extern Ent_8017D6EC_80183918 D_801E1BD0[];
    s32 i;

    if (D_80078EB1 == 7) {
        for (i = 0; i < 4; i++) {
            Ent_8017D6EC_80183918 *p = &D_801E1BD0[i];

            p->unk16 = i;
            func_80183C34(p);
            if (i & 1) {
                p->unk1C = 1;
            }
        }
        func_8012AD50(arg0);
    }
}






extern s32 func_8004787C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80183BE4(void);
extern void func_80183CF0(void *arg0);

void aF801839A8(void *arg0) __asm__("func_801839A8");
void aF801839A8(void *arg0)
{

    extern u8 D_80078EB1;
    extern u8 D_80078E78[];
    extern u8 D_800AF630[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Ent_8017D6EC_8017DEE8 D_801E1BD0[];
    u8 *m;
    u8 *e78;
    s32 k;

    m = D_800AF630;
    e78 = D_80078E78;

    if (D_80078EB1 >= 9) {
        s32 count;
        s32 i;
        u8 *base;

        base = (u8 *)D_801E1BD0;
        count = 0;
        for (i = 0; i < 4; i++) {
            if (*(s32 *)(base + i * 0x24 + 0x1C) == 0) {
                count++;
            }
        }
        if (count == 0) {
            func_8012AD44((s32 *)arg0, 0);
            return;
        }
    }

    for (k = 0; k < 4; k++) {
        u8 *p = (u8 *)D_801E1BD0 + k * 0x24;
        s32 c;

        if (*(s32 *)(p + 0x1C) != 0) {
            continue;
        }

        {
            s16 val = *(s16 *)(p + 0xC);
            if (val < 0x401) {
                *(s16 *)(p + 0xC) = val + 0xB;
            } else if (*(s32 *)(p + 0x18) != 0) {
                *(s32 *)(p + 0x18) -= 1;
            } else {
                *(s16 *)(p + 0xC) = val + 0xB;
            }
        }

        if (*(s16 *)(p + 0xC) >= 0x801) {
            *(s16 *)(p + 0xC) = 0;
        }

        c = (func_8004787C(*(s16 *)(p + 0xC)) / 64) & 0xFF;
        c = c | (c << 16 | c << 8);
        *(s32 *)(p + 0x4) = c;

        c = (func_8004787C(*(s16 *)(p + 0xC)) / 256) & 0xFF;
        c = c | (c << 16 | c << 8);
        *(s32 *)(p + 0x8) = c;

        if ((*(u16 *)(m + 0xA3AA) & 1) == 0) {
            s16 cnt = *(u16 *)(p + 0xE) + 1;
            *(u16 *)(p + 0xE) = cnt;
            if (cnt >= 0x40) {
                *(u16 *)(p + 0xE) = 0;
            }
        }

        {
            s32 val2 = *(s16 *)(p + 0xC);
            if (val2 == 0) {
                *(s32 *)(p + 0x1C) = 1;
            } else if (val2 >= 0x556) {
                if (*(s32 *)(p + 0x20) == 0) {
                    *(s32 *)(p + 0x20) = 1;
                    if (e78[0x39] < 9) {
                        ((void (*)(void *))func_80183BE4)(p);
                    }
                }
            }
        }

        func_80183CF0(p);
    }
}




/* func_80183BE4 - iterate through 4-entry array, call func_80183C34 if any unk1C is non-zero */

extern void func_80183C34(void *arg0);




void func_80183BE4(void) {

    extern Ent_8017D6EC D_801E1BD0[];
    s32 i = 0;
    Ent_8017D6EC *p = &D_801E1BD0[0];

    while (i < 4) {
        if (p->unk1C != 0) {
            func_80183C34(p);
            break;
        }
        i++;
        p = (Ent_8017D6EC *)((char *)p + 0x24);
    }
}



extern s32 rand(void);

void func_80183C34(void *arg0) {

    extern void (*D_80190708[])(void);
    s32 base = (s32)arg0;
    s32 r1;
    s32 r2;
    s32 h;
    s32 t;

    *(s32 *)(base + 0x0) = (s32)D_80190708;
    *(s32 *)(base + 0x4) = 0;
    *(s32 *)(base + 0x8) = 0;
    *(s16 *)(base + 0xC) = 0;
    *(s16 *)(base + 0xE) = 0;
    *(s16 *)(base + 0x10) = 0;

    r1 = rand();
    r2 = rand();
    h = *(s16 *)(base + 0x16) * 80;
    t = (r1 & 7) * 5 - 0xA0;
    *(s16 *)(base + 0x12) = h + t + (r2 & 0xF);

    *(s16 *)(base + 0x14) = -((rand() & 0xF) * 2);
    *(s32 *)(base + 0x1C) = 0;
    *(s32 *)(base + 0x20) = 0;
    *(s32 *)(base + 0x18) = (*(u16 *)(base + 0x16) & 2) * 30;
}




/* func_80183CF0 — build a 4-vertex SVECTOR quad from an 8-u16 source record,
 * translate it by the actor's (0x12,0x14) offset, and hand it to the
 * 0x80017714 draw helper — three records per call.
 *
 * Frame math: 0x10 arg-save + 0x38 local + 7 saved regs (s0..s5,ra) = 0x68.
 * The local is the same block shape as the D_801AA000 global in
 * ov_SC06_008_jr_8017C294 (SVECTOR v[4]; then six words), with the last
 * word DEAD (idiom 6: the frame delta is a dead field, not codegen).
 *
 * Two levers, both required:
 *  (1) THE PRIM BASE IS A SOURCE-LEVEL POINTER, not `&prim` at the use sites.
 *      Writing the loop body as `prim.v[k].vx = ...` addresses every store
 *      sp-relative, costs no callee-saved register and comes out -3 ins
 *      ($s5 never allocated, no `addiu $s1,$sp,0x10`). Introducing `q = &prim`
 *      BEFORE the loop and using `q->` only inside it reproduces the target
 *      exactly: the pre-loop initialisers stay sp-relative (same block as q's
 *      set, so cse folds them back) while the loop body keeps $s1.
 *  (2) A chained assignment stores the INNERMOST target first. The target's
 *      order is `sw 0x34` then `sw 0x30`, so it must be written
 *      `prim.f20 = prim.f24 = x;` — `f24 = f20 = x` emits 0x30 then 0x34.
 *
 * The two induction pointers ($s4 walking the record and $s0 = $s4 + 0xE)
 * fall out of a SINGLE `u16 *p` walked with `p += 8` — loop.c splits the
 * eight DEST_ADDR givs onto two bases on its own; do not hand-write a
 * second pointer.
 *
 * Byte-identical target asm in ov_SC04_019 and ov_SC05_017 (same TU name),
 * so this body remaps to those overlays unchanged.
 */



extern void func_80017714(void *);

void func_80183CF0(void *arg0)
{
    s32 a0 = (s32)arg0;
    Prim_8017DAC4_80183CF0 prim;
    Prim_8017DAC4_80183CF0 *q;
    u16 *p;
    u16 dx, dy;
    s32 i;

    q = &prim;
    p = *(u16 **)(a0 + 0x0);
    dx = *(u16 *)(a0 + 0x12);
    dy = *(u16 *)(a0 + 0x14);
    i = 0;

    prim.v[0].vz = 3;
    prim.f20 = prim.f24 = *(s32 *)(a0 + 0x4);
    prim.f28 = *(s32 *)(a0 + 0x8);
    prim.f2C = 0;
    prim.f30 = 0x50000000;

    do {
        q->v[0].vx = p[0] + dx;
        q->v[0].vy = p[1] + dy;
        q->v[1].vx = p[2] + dx;
        q->v[1].vy = p[3] + dy;
        q->v[2].vx = p[4] + dx;
        q->v[2].vy = p[5] + dy;
        q->v[3].vx = p[6] + dx;
        q->v[3].vy = p[7] + dy;
        func_80017714(q);
        p += 8;
        i++;
    } while (i < 3);
}


extern void func_8013CB84(void);
extern void func_80183E38(void);
extern void func_800D06E8(void);

void func_80183E08(void)
{
    func_8013CB84();
    func_80183E38();
    func_800D06E8();
}



// @class: regalloc-order
// @stuck: none — MATCH

extern u32 D_801E1C60;
extern u16 D_80190740[];
extern u16 D_801E1C64[];
extern s32 D_80190760;

extern void func_800183E0(s32 a0);

void func_80183E38(void)
{
    u32 i;
    u16 *p;
    u32 base;
    u16 *tbl;

    i = 0;
    tbl = D_80190740;
    base = D_801E1C60 >> 8;
    p = D_801E1C64;
    do {
        *p = tbl[(base + i) & 0xF] | 0x8000;
        i = i + 1;
        p = p + 1;
    } while (i < 0x10);
    func_800183E0((s32)&D_80190760);
    D_801E1C60 = D_801E1C60 + 0x100;
}


void func_80183EC4(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    }



void func_80183ED4(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 2;
    }



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern s32 func_8012E57C(s32 a0, s32 a1);

s32 func_80183EE4(void *a0, void *a1) {

    extern u8 D_801BBCF0;
    s32 v0;
    s16 val;

    if (a1 == 0) {
        a1 = (void *)&D_801BBCF0;
    }
    *(void **)((char *)a0 + 0xD0) = a1;
    if (*(s32 *)a1 != 0) {
        v0 = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)((char *)a0 + 0x20) = v0;
        if (v0 == 0) {
            func_8012CAE4(a0);
            return 0;
        }
        func_8001C214(v0, *(s32 *)a1);
    }
    val = *(s16 *)((char *)a1 + 0x12);
    if (val == -1) {
        return 1;
    }
    *(s32 *)((char *)a0 + 0xCC) = func_8012E57C(0x61, val);
    return 1;
}



















extern void func_8012A828(s32 arg0, s32 arg1);
void func_80183F80(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  func_8012A828(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0x4)));
}



















extern void func_8012A828(s32 arg0, s32 arg1);
void func_80183FAC(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  func_8012A828(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0x8)));
}



















extern void func_8012A828(s32 arg0, s32 arg1);
void func_80183FD8(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  func_8012A828(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0xc)));
}




/* func_80184004 — ov_SC04_018 (TU: src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c)
 *
 * DECL SURFACE (§37 / §124 asm-label alias):
 *   The TU already carries three fleet-canonical forward decls
 *     `extern s32 func_80184004(void);`   (L5361, L5592, L5904 — all ABOVE the
 *   splice point at L6839), each used by a banked caller that invokes it with
 *   NO arguments (`if (func_80184004() == 0)`).  The byte-true signature takes
 *   a pointer in $a0 (`lw $a2, 0x64($a0)` at 0x801848E4), so the definition
 *   disagrees with the canonical decl on arity -> cc1 emits
 *     "conflicting types for `func_80184004'".
 *   Neither a fleet widen nor a cast-at-use fixes an arity clash on the symbol
 *   being DEFINED, so the definition is emitted under the C identifier
 *   `aF801848DC` with an __asm__("func_80184004") label.  The C-level name
 *   never collides with the canonical decls, the emitted symbol is unchanged,
 *   and codegen is byte-identical (verified: match_one MATCH 33/33 with and
 *   without the alias).  Precedent in this very TU: aF8018CB18 @ L8872.
 *
 *   func_8012F2E8 / func_8012CB64 / D_80126B5E / D_80126B62 / D_80126B66 are
 *   reproduced VERBATIM from the TU's own decls (L7717-L7722, L7964-L7965,
 *   L8727-L8729) — identical types, so no second conflict hides behind the
 *   first.  No shared header is touched.
 *
 * BODY: the original draft discarded the func_8012CB64 result and returned a
 *   literal 0, which forced `move $v0,$zero` into the epilogue and displaced
 *   `addiu $sp,$sp,0x30` into the jr delay slot (DIFF 3/33 @ idx 9/30/32).
 *   The target sets $v0=0 in the *branch* delay slot and falls through to a
 *   bare epilogue after `jal func_8012CB64`, i.e. it RETURNS the callee's
 *   value on the taken path — the exact shape of the banked sibling
 *   func_80185D10 (TU L7724-L7733).  Early-return + tail-return reproduces it.
 *
 * ORACLE: .venv/bin/python tools/match_one.py func_80184004 \
 *           --c .run/s7/ov_SC04_018/func_80184004.c \
 *           --asm-subdir asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_8017AE2C
 */


extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CB64(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

s32 aF801848DC(void *a0) __asm__("func_80184004");

s32 aF801848DC(void *a0) {

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    s16 out[3];
    s16 in[3];
    void *p;

    p = *(void **)((char *)a0 + 0x64);
    if (*(u16 *)(*(s32 *)((char *)p + 0xCC) + 0x2) != 0x2) {
        return 0;
    }

    in[0] = D_80126B5E;
    in[1] = D_80126B62;
    in[2] = D_80126B66;
    func_8012F2E8(*(s32 *)((char *)p + 0xCC), (s32)in, (s32)out);
    return func_8012CB64((s32)out, -0xC0, 0x40, -0x60, 0);
}



/* func_80184088 — 76 instructions */

extern s32 func_8018422C(s32 arg0);

s32 func_80184088(s32 a0) {

    extern u8 D_80078E78[];
    extern u8 D_80078EB1;
    extern u16 D_80078EAC;
    extern s32 D_801E2458;
    extern s16 D_801BBE04[];
    extern s16 D_801BBE38[];
    extern s32 D_801BBD04[][8];
    u8 *p;
    s32 s0;
    s32 t;
    s32 q;
    s32 r;
    s32 b;
    s32 c;
    s32 idx;

    p = D_80078E78;
    s0 = D_801BBE04[*(s16 *)(*(s32 *)(a0 + 0xD0) + 0x10)];
    if (s0 == -1) {
        D_801E2458 = 0;
        return 0;
    }

    t = func_8018422C(a0);
    q = t / 24;
    r = t % 24;
    b = D_80078EB1;
    c = D_80078EAC;

    if (t == 0) {
        idx = D_801BBE38[b] - 1;
    } else if (c - q >= 5) {
        idx = 7;
    } else if (c == q && b - r >= 2) {
        idx = 6;
    } else {
        idx = p[0x39];
        idx = D_801BBE38[idx] - 1;
    }

    ((struct { s32 w; } *)&D_801E2458)->w = 1;
    return D_801BBD04[idx][s0];
}



extern s32 func_80184088(s32 arg);
extern void func_801841EC(void *a0);

void func_801841B8(void *a0) {
    *(s32 *)((char *)a0 + 0xe0) = func_80184088((s32)a0);
    func_801841EC(a0);
}





void func_801841EC(void *a0) {

    extern u16 D_80078EAC;
    extern u8 D_80078EB1;
    extern short D_800BA2BA;
    u16 idx1 = D_80078EAC;
    u8 idx2 = D_80078EB1;
    s32 ptr = *(s32 *)((char *)a0 + 0xD0);
    s16 offset = *(s16 *)((char *)ptr + 0x10);

    *(short *)((char *)&D_800BA2BA + (offset << 2)) = idx2 + (idx1 * 24);
}



extern short D_800BA2BA;
    s32 func_8018422C(s32 arg0) {
        return *(short *)((char *)&D_800BA2BA + (*(short *)(*(s32 *)(arg0 + 0xd0) + 0x10) << 2));
    }



extern void (*D_801BBE68[])(void);

void func_80184254(void *a0) {
    D_801BBE68[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80184290(void) {
}



void func_80184298(void *a0, s32 a1, s32 a2)
{

    extern u8 D_80078EB1;

    if (D_80078EB1 >= a1 && D_80078EB1 < a2) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 1;
    } else {
        *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    }
}





s32 func_801842D4(s32 arg0, s32 arg1) {

    extern u8 D_80078EB1;
    return (D_80078EB1 >= arg0) && (D_80078EB1 < arg1);
}





s32 func_801842F8(u8 a0, u8 a1, u8 a2, u8 a3) {

    extern u8 D_80078EB0;
    s32 pad[8];
    s32 v0, h0, l0, h1, l1, x, y;

    v0 = 0;
    h0 = a0;
    l0 = a1;
    x = (h0 << 8) | l0;
    h1 = a2;
    l1 = a3;
    y = (h1 << 8) | l1;

    if ((s16)x <= *(s16 *)&D_80078EB0) {
        v0 = (s16)y;
        v0 = *(s16 *)&D_80078EB0 < v0;
    }
    return v0;
}



extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);


void func_80184350(void *a0, s32 a1)
{
    Vec4s_80184350 loc_10;
    Vec4s_80184350 loc_18;
    Vec4s_80184350 loc_20;

    loc_10.f0 = *(s16 *)((u8 *)a0 + 0x6);
    loc_10.f1 = *(s16 *)((u8 *)a0 + 0xA);
    loc_10.f2 = *(s16 *)((u8 *)a0 + 0xE);

    loc_18.f0 = 0;
    loc_18.f1 = 0;
    loc_18.f2 = (s16)(-a1);

    ((void(*)(s32, s32, s32))func_8012F214)((s32)a0, (s32)&loc_18, (s32)&loc_20);
    func_8012CEB0((s32)&loc_10, (s32)&loc_20, 0);
}





void func_801843B8(s32 a0)
{

    extern s32 D_801BBE70;
    *(s32 *)(a0 + 0x58) = (u32)&D_801BBE70 | 0x40000000;
    *(s16 *)(a0 + 0x5C) = 0x800;
}


void func_801843D8(void *a0) {
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }





extern void func_8012E8A8(u8 *a0);
extern void func_8012E8E0(s32 a0, s32 a1);

void aF801843E0(s32 *a0, s32 a1) __asm__("func_801843E0");
void aF801843E0(s32 *a0, s32 a1)
{
    func_8012E8A8((u8 *)a0);
    *(s16 *)((s32)a0 + 0x98) = 0;
    *(s16 *)((s32)a0 + 0x5C) = 0;
    func_8012E8E0((s32)a0, a1);
}


extern s32 func_80029504(void);

s32 func_80184428(void) {
    s32 v1 = func_80029504();

    if (v1 < 0x14) {
        return 0;
    }
    if (v1 < 0x46) {
        return 1;
    }
    if (v1 < 0x64) {
        return 2;
    }
    if (v1 < 0x82) {
        return 3;
    }
    return 4;
}



extern s32 func_80029504(void);

s32 func_80184484(void) {
    s32 v0 = func_80029504();

    if (v0 < 0xC8) return 5;
    if (v0 < 0x12C) return 0;
    if (v0 < 0x258) return 1;
    if (v0 < 0x2BC) return 2;
    if (v0 < 0x2E4) return 3;
    if (v0 < 0x384) return 4;
    return 6;
}



extern s32 func_80029504(void);

s32 func_801844F8(void) {
    s32 v0 = func_80029504();

    if (v0 < 0xC8) return 5;
    if (v0 < 0x12C) return 0;
    if (v0 < 0x258) return 1;
    if (v0 < 0x2B2) return 2;
    if (v0 < 0x2E4) return 3;
    if (v0 < 0x384) return 4;
    return 6;
}


extern s32 func_80029504(void);

s32 func_8018456C(void) {
    s32 v1 = func_80029504();

    if (v1 < 0x3b6) {
        return 0;
    }
    if (v1 < 0x3e8) {
        return 1;
    }
    if (v1 < 0x44c) {
        return 2;
    }
    if (v1 < 0x4b0) {
        return 3;
    }
    return 4;
}



extern s32 func_80029504(void);
    extern void func_80029514(s32 arg0);
    void func_801845C8(void) {
        if (((s32 (*)(void))func_80029504)() == 0x3A2) {
            ((void (*)(s32))func_80029514)(0x3AC);
        }
    }




extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012B200(u8 *a0);

void func_801845FC(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 idx;
    s32 base;
    u16 vals[3];
    s32 result;
    s32 *v1;

    *(u8*)(a0 + 0x108) = a2;
    a2 = a2 & 0xFF;
    *(s32*)(a0 + 0xE8) = a1;
    *(u8*)(a0 + 0x109) = a3;

    idx = *(s16*)a1;

    if (a2 == 0) {
        *(u16*)(a0 + 0x106) = 2;
        *(u16*)(a0 + 0x6) = *(u16*)(a1 + 4);
        *(u16*)(a0 + 0xE) = *(u16*)(a1 + 6);
        vals[0] = *(u16*)(a1 + 8);
        vals[2] = *(u16*)(a1 + 10);
    } else {
        base = idx;
        base = base * 4 + a1;
        *(u16*)(a0 + 0x106) = (u16)(idx - 1);
        *(u16*)(a0 + 0x6) = *(u16*)(base);
        *(u16*)(a0 + 0xE) = *(u16*)(base + 2);
        vals[0] = *(u16*)(base - 4);
        vals[2] = *(u16*)(base - 2);
    }

    result = func_8012B744((void*)(a0 + 4), vals);

    v1 = (s32*)(a0 + 0x20);
    *(u16*)(*v1 + 0x12) = (u16)result;
    func_8012B200((u8*)a0);
}




/* func_801846CC @ 0x80184FA4 — ov_SC04_018_jr_8017AE2C
 * Decls copied verbatim from the TU (src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c):
 *   line 350   extern s32  func_8016F1AC(void);
 *   line 448   extern void func_8014B12C(void);      <- void! call through a cast (idiom 9)
 *   line 2616  extern s32  func_8012B608(s32, s32, s32);
 *   line 2617  extern void func_8012B178(s32, s32);
 *   line 2618  extern void func_8012AD80(s32);
 *   line 2619  extern s32  func_8012B030(u8 *);
 *   line 2620  extern s32  func_8012B744(void *, void *);
 *   line 2621  extern s32  func_8012BE98(s32, u16 *);
 *   line 4926  extern s32  func_801846CC(s32 a0);
 */

extern s32 func_8016F1AC(void);
extern void func_8014B12C(void);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012BE98(s32 a0, u16 *a1);

s32 func_801846CC(s32 a0) {
    u16 vals[3];
    s32 sh;

    if (func_8016F1AC() != 0) {
        return 0;
    }

    if (*(u8 *)(a0 + 0x108) == 0) {
        if (*(s16 *)(*(s32 *)(a0 + 0xE8)) < *(s16 *)(a0 + 0x106)) {
            return 1;
        }
    } else if (*(s16 *)(a0 + 0x106) <= 0) {
        return 1;
    }

    vals[0] = *(u16 *)(*(s16 *)(a0 + 0x106) * 4 + *(s32 *)(a0 + 0xE8));
    vals[2] = *(u16 *)(*(s16 *)(a0 + 0x106) * 4 + *(s32 *)(a0 + 0xE8) + 2);

    sh = *(u8 *)(a0 + 0x109);
    sh = sh << 12;

    if (((s32 (*)(void))func_8014B12C)() != 0) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            func_8012B744((void *)(a0 + 4), vals);
        sh = sh << 3;
    } else {
        s32 r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              func_8012B744((void *)(a0 + 4), vals), 4);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
    }

    func_8012B178(a0, -sh);
    func_8012AD80(a0);
    *(u16 *)(a0 + 0xA) -= 0x10;
    func_8012B030((u8 *)a0);

    if (((s32 (*)(void))func_8014B12C)() != 0) {
        if (func_8012BE98(a0, vals) < 0x1001) {
            if (*(u8 *)(a0 + 0x108) == 0) {
                *(u16 *)(a0 + 0x106) = *(u16 *)(a0 + 0x106) + 1;
            } else {
                *(u16 *)(a0 + 0x106) = *(u16 *)(a0 + 0x106) - 1;
            }
        }
    } else {
        if (func_8012BE98(a0, vals) < 0x101) {
            if (*(u8 *)(a0 + 0x108) == 0) {
                *(u16 *)(a0 + 0x106) = *(u16 *)(a0 + 0x106) + 1;
            } else {
                *(u16 *)(a0 + 0x106) = *(u16 *)(a0 + 0x106) - 1;
            }
        }
    }
    return 0;
}




extern void func_8014B12C(void);
extern s32 func_8016F1C4(void);

s32 func_80184894(s32 a0) {
    if (func_8016F1C4() != 0) {
        return 0;
    }
    if (((s32 (*)(void))func_8014B12C)() != 0) {
        return 2;
    }
    return 1;
}



extern void (*D_801BBE88[])(void);

void func_801848DC(void *a0) {
    D_801BBE88[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80184918(void) {
}

void func_80184920(void) {
}

void func_80184928(void) {
}

void func_80184930(void) {
}

void func_80184938(void) {
}


extern void func_80016714(void *a0, s32 a1);
extern void func_8012CAE4(void *a0);


void func_80184940(void *a0) {

    extern s32 D_801E2548;
    extern s32 D_801E245C;
    func_80016714(&D_801E2548, 0x14);
    D_801E245C = 0;
    func_8012CAE4(a0);
}


void func_80184984(void) {
}


/* §37 lever (A): conform to the TU's existing decl verbatim (TU lines 6430 /
 * 6862 both say `void`); the s32 return is recovered by a cast at the call
 * site below. Decl-only change => zero bytes move. */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012E8E0(s32 a0, s32 a1);


void func_8018498C(s32 a0) {

    extern s32 D_801C5480[];
    extern s32 D_801BBE80[];
    s32 v0;
    s32 result;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    func_8001C214(v0, (s32)D_801C5480);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);

    result = *(s32 *)(a0 + 0x20);
    *(s32 *)(result + 0x4) |= 0x40;
    func_8012E8E0(a0, (s32)D_801BBE80);

    *(s16 *)(a0 + 0x2) = 1;
}



extern void func_801850A0(s32 a0);
extern void func_8018502C(s32 a0);
extern void func_80185100(s32 a0);
extern void func_80184FC4(s32 a0);

void func_80184A14(s32 a0) {

    extern void (*D_801BC160[])(s32);
    u32 st;

    if (*(s16 *)(a0 + 0x10A) > 0) {
        *(s16 *)(a0 + 0x10A) = *(s16 *)(a0 + 0x10A) - 1;
    }
    if (*(s16 *)(a0 + 0x108) != 0) {
        *(s32 *)(a0 + 0xB0) = *(s16 *)(a0 + 0x108);
        *(s16 *)(a0 + 0x108) = 0;
    }

    st = *(u32 *)(a0 + 0xB0);
    switch (st) {
    case 1:
        if (*(u16 *)(a0 + 0x2) != 2 || *(u16 *)(a0 + 0x34) == 0) {
            if (*(s16 *)(a0 + 0xEA) != st) {
                *(s16 *)(a0 + 0xEA) = st;
                if (*(s16 *)(a0 + 0xE8) != 0) {
                    func_801850A0(a0);
                } else {
                    func_8018502C(a0);
                }
                *(s16 *)(a0 + 0xE8) = 1;
            }
        }
        break;
    case 2:
        if (*(u16 *)(a0 + 0x2) != 2 || *(u16 *)(a0 + 0x34) == 0) {
            if (*(s16 *)(a0 + 0xEA) != st) {
                *(s16 *)(a0 + 0xEA) = st;
                if (*(s16 *)(a0 + 0xE8) != 0) {
                    func_80185100(a0);
                } else {
                    func_80184FC4(a0);
                }
                *(s16 *)(a0 + 0xE8) = 1;
            }
        }
        break;
    case 3:
        if (*(u16 *)(a0 + 0x2) != 2 || *(u16 *)(a0 + 0x34) == 0) {
            func_8018502C(a0);
        }
        break;
    case 4:
        if (*(u16 *)(a0 + 0x2) != 2 || *(u16 *)(a0 + 0x34) == 0) {
            func_80184FC4(a0);
        }
        break;
    }

    D_801BC160[*(u16 *)(a0 + 0x2)](a0);
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001C214(s32, s32);
extern void func_8001C97C(s32 a0);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_80184FC4(s32 a0);
extern void *func_80185394(void *a0);



void func_80184BEC(s32 a0) {

    extern s32 D_801BBE90[][2];
    extern u32 D_801BBEA8;
    extern u32 D_801BBEC4;
    extern s16 D_801BBED0[];
    extern Blk12_801854C4_80184BEC D_801BBEB8;
    s32 v0;
    s16 idx;
    s16 *p;

    v0 = ((s32 (*)(s32))func_8012C1B8)(a0);
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(a0);
        return;
    }

    idx = *(s16 *)(a0 + 0x70);
    p = &D_801BBED0[idx];
    switch (idx) {
    case 7:
    case 9:
    case 10:
    case 12:
        func_8001C810(v0, D_801BBE90[*p][0]);
        *(s32 *)(v0 + 4) |= 0x8040;
        break;
    default:
        func_8001C214(v0, D_801BBE90[*p][0]);
        break;
    }

    func_8001C97C(D_801BBE90[*p][1]);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0xC8, 0xB4);
    *(s32 *)(a0 + 0x58) = (u32)&D_801BBEA8 | 0x40000000;
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = (s32)&D_801BBEC4;
    *(s16 *)(a0 + 0xE8) = 0;
    *(Blk12_801854C4_80184BEC *)(a0 + 0xEC) = D_801BBEB8;
    *(s16 *)(a0 + 0x10A) = 6;
    func_80184FC4(a0);
    *(s32 *)(a0 + 0xDC) = (s32)func_80185394;
}




extern void func_80185498(void *a0);
extern int func_80178970(void);
extern void func_80178D18(void);

void func_80184D8C(void *a0) {
    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        break;
    case 1:
        func_80185498(a0);
        *(s16 *)((s32)a0 + 0x34) = 2;
        break;
    case 2:
        if (((s32 (*)(s32))func_80178970)((s32)a0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)a0);
            *(s16 *)((s32)a0 + 0x34) = 0;
        }
        break;
    }
}



extern s32 func_80184894(s32 a0);
extern void func_8018502C(s32 a0);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern void func_80185614(void);

void func_80184E08(s32 a0) {
    s32 s0;
    u16 v0;
    u16 v1;

    if (func_80184894(a0) == 2) {
        func_8018502C(a0);
    }
    s0 = a0;

    v0 = *(u16 *)(s0 + 0x84);
    v0 = v0 + 1;
    *(u16 *)(s0 + 0x84) = v0;

    if ((s16)v0 == 8) {
        func_8012E688(s0, 0x514, 0);
    }

    v0 = *(u16 *)(s0 + 0x100);
    v1 = *(u16 *)(s0 + 0x102);
    v0 = v0 + v1;
    *(u16 *)(s0 + 0x100) = v0;

    if ((s16)v0 >= 0x50) {
        *(u16 *)(s0 + 0x100) = 0x50;
    }

    v0 = *(u16 *)(s0 + 0xFE);
    v1 = *(u16 *)(s0 + 0x100);
    v0 = v0 + v1;
    *(u16 *)(s0 + 0xFE) = v0;

    if ((s16)v0 >= 0x600) {
        func_8018502C(s0);
    }

    ((void (*)(s32))func_80185614)(s0);
}


extern void func_80185614(void);
    void func_80184ED4(void) {
        func_80185614();
    }



extern s32 func_80184894(s32 a0);
extern void func_80184FC4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern void func_80185614(void);

void func_80184EF4(s32 a0) {
    if (func_80184894(a0) == 2) {
        func_80184FC4(a0);
    }
    if (*(u16 *)(a0 + 0x34) == 0) {
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        *(u16 *)(a0 + 0x34) = 1;
    }
    *(u16 *)(a0 + 0x100) = *(u16 *)(a0 + 0x100) + *(u16 *)(a0 + 0x102);
    if (*(s16 *)(a0 + 0x100) >= 0x50) {
        *(u16 *)(a0 + 0x100) = 0x50;
    }
    *(u16 *)(a0 + 0xFE) = *(u16 *)(a0 + 0xFE) - *(u16 *)(a0 + 0x100);
    if (*(s16 *)(a0 + 0xFE) <= 0) {
        func_8012E688(a0, 0x515, 0);
        func_80184FC4(a0);
    } else {
        ((void (*)(s32))func_80185614)(a0);
    }
}


extern s16 D_801BBED0[];
extern s32 D_801BBE94[][2];
extern void func_80185614(void);

void func_80184FC4(a0)
s32 a0;
{

    extern s16 D_801BBED0[];
    extern s32 D_801BBE94[][2];

    *(s16 *)(a0 + 0x2) = 2;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0xFE) = 0;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x24) =
        D_801BBE94[D_801BBED0[*(s16 *)(a0 + 0x70)]][0];
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0xB0) = 0;
    func_80185614();
}




extern void func_80185614(void);

void func_8018502C(s32 a0) {

    extern s32 D_801BBE90[][2];
    extern s16 D_801BBED0[];
    s32 idx_val, ptr_val, data_val;

    *(s16 *)(a0 + 0x2) = 0x4;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0xFE) = 0x600;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x102) = 0;
    idx_val = D_801BBED0[*(s16 *)(a0 + 0x70)];
    ptr_val = *(s32 *)(a0 + 0x20);
    data_val = D_801BBE90[idx_val][0];
    *(s32 *)(ptr_val + 0x24) = data_val;
    *(s16 *)(a0 + 0x84) = 0;
    *(s16 *)(a0 + 0x5C) = 0;
    *(s32 *)(a0 + 0xB0) = 0;
    ((s32 (*)(void))func_80185614)();
}


void func_801850A0(s32 a0) {

    extern s16 D_801BBED0[];
    extern s32 D_801BBE90[][2];
    *(s16 *)(a0 + 0x2) = 3;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0xFE) = 0;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x102) = 2;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x24) = D_801BBE90[D_801BBED0[*(s16 *)(a0 + 0x70)]][0];
    *(s16 *)(a0 + 0x84) = 0;
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0xB0) = 0;
}



extern void func_80185614(void);

void func_80185100(s32 a0) {

    extern s16 D_801BBED0[];
    extern s32 D_801BBE90[][2];
    *(s16 *)(a0 + 0x2) = 1;
    *(s32 *)(a0 + 0x1C) = 8;
    *(s16 *)(a0 + 0xFE) = 0x600;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x102) = 2;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x24) = D_801BBE90[D_801BBED0[*(s16 *)(a0 + 0x70)]][0];
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0xB0) = 0;
    ((s32 (*)(void))func_80185614)();
}





void func_80185180(s32 a0, s32 a1)
{

    extern u8 D_801202A0[];
    u8 *p = D_801202A0;
    u8 *end = p + 0x6480;

    if (p != end) {
        do {
            if (*(u16 *)p == 0x61 && *(s16 *)(p + 0x70) == a0) {
                *(s32 *)(p + 0xB0) = a1;
                return;
            }
            p += 0x10C;
        } while (p != end);
    }
}



extern s32 func_8012E57C(s32 a0, s32 a1);
extern void func_80185754(s32 a0, s32 a1);

void func_801851D8(s32 a0) {
    s32 v0 = func_8012E57C(0x61, (s16)a0);
    if (v0 != 0) {
        if (*(u16 *)((char *)v0 + 0x2) == 2) {
            *(s32 *)((char *)v0 + 0xB0) = 1;
        }
        func_80185754(a0, 0x3C);
    }
}




extern s32 func_8012E57C(s32 a0, s32 a1);

void func_80185238(s32 a0) {
    void *p;

    p = (void *)func_8012E57C(0x61, (s16)a0);
    if (p == 0) {
        return;
    }
    if (*(u16 *)((char *)p + 0x2) == 0x4) {
        *(s32 *)((char *)p + 0xB0) = 0x2;
    }
}




extern s32 func_8012E57C(s32 a0, s32 a1);
extern void func_80185754(s32 a0, s32 a1);

void func_80185280(s32 a0) {
    s32 v1;

    v1 = func_8012E57C(0x61, (s32)(s16)a0);
    if (v1 != 0) {
        *(s16 *)((char *)v1 + 0x108) = 1;
        func_80185754(a0, 0x3C);
    }
}




extern s32 func_8012E57C(s32 a0, s32 a1);

void func_801852D0(s32 a0) {
    s32 shift_temp;
    s32 v1;

    shift_temp = ((a0 << 16) >> 16);
    v1 = func_8012E57C(0x61, shift_temp);
    if (v1 != 0) {
        *(s16 *)((char *)v1 + 0x108) = 2;
    }
}


extern s32 func_8012E57C(s32 a0, s32 a1);
s32 func_80185308(s32 a0) {
    void *p;

    p = (void *)func_8012E57C(0x61, (s16)a0);
    if (p == 0) {
        return 1;
    }
    switch (*(u16 *)((char *)p + 2)) {
    case 1:
    case 2:
        *(s16 *)((char *)p + 0x108) = 1;
        return 0;
    case 3:
        *(s16 *)((char *)p + 0x108) = 1;
        return 0;
    case 4:
        *(s16 *)((char *)p + 0x108) = 1;
        return 1;
    }
}



extern s16 currentLocationId;
extern s32 func_80185438(void *a0);
extern s32 func_801859D0(void *a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

void *func_80185394(void *a0) {
    if (currentLocationId == 0x3069) {
        return 0;
    }
    if (*(u16 *)((s32)a0 + 0x2) != 2) {
        return 0;
    }
    if (*(u16 *)((s32)a0 + 0x34) != 0) {
        return 0;
    }
    if (*(s16 *)((s32)a0 + 0x10A) != 0) {
        return 0;
    }
    if (func_80185438(a0) == 0) {
        return 0;
    }
    if (func_801859D0(a0) != 0) {
        return 0;
    }
    *(s16 *)((s32)a0 + 0x34) = 1;
    func_80178BF8();
    return (void *)func_80172710;
}





extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CB64(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

s32 func_80185438(void *a0) {

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    s16 out[3];
    s16 in[3];

    in[0] = D_80126B5E;
    in[1] = D_80126B62;
    in[2] = D_80126B66;
    func_8012F2E8((s32)a0, (s32)in, (s32)out);
    return func_8012CB64((s32)out, -0x80, 0x80, -0x60, 0);
}

