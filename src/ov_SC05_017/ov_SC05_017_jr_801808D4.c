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
extern u8 D_8018F710;
extern u8 D_8018F680;
extern u8 D_8018F65C;
extern u8 D_8018F638;
extern u8 D_8018F6EC;
extern u8 D_8018F6C8;
extern u8 D_8018F6A4;
extern u8 D_8018F614;
extern void func_80145934(void);
extern u8 D_8018F7A0;
extern u8 D_8018F77C;
extern u8 D_8018F758;
extern u8 D_8018F734;
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
extern unsigned char D_8018EB98[];
extern unsigned char D_8018EBC8[];
extern unsigned char D_8018EC18[];
extern unsigned char D_8018EC48[];
extern unsigned char D_8018EC78[];
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
extern void (*D_8018ECC8[])(void *);
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
extern s32 D_8018ED90[];
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
extern u8 D_8018EE18[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018EE20;
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
extern int D_801EBA00;
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
extern s32 D_801EBA04;
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
extern s32 D_8018EE50;
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
extern void (*D_8018EEF8[])(void);
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
extern void (*D_8018EF1C[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018EF0C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018EF30[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018EF3C[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018EF4C[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018EF64[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018EF54;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018EF78[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018EF94[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018EF84;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018EFA8[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018EFBC[])(void);
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
extern s32 D_8018EFD0;
extern void (*D_8018EFF8[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018EFD8;
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
extern int (*D_8018F044[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018F048[])(void);
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
extern unsigned short D_8018F4AC[];
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
extern void (*D_8018F4BC[])(void);
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
extern int D_801EBA38;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018F4E4[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018F4C4;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018F4D4;
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
extern void (*D_8018F524[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018F52C[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018F4F8;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018F538[])(void);
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
extern u8 D_8018F508;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801EBA40;
extern s32 D_801EBA4C;
extern s32 D_801EBA50;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018F574[])(s32 *);
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
extern s32 D_8018F548[];
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
extern s32 D_801EBA48;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018F7C4[])(void);
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
extern char D_8018F5E4[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018F868[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018F9BC[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018F7D8;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018F9C4[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018F7E8;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018F808;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018F9CC[])(void);
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
extern void (*D_8018F9F4[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018FA00[])(void);
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
extern void (*D_8018F874[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018FAA4;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018EB88[];
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
extern unsigned char D_8018FAB8[];
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
extern s8 D_8018FAF4[];
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
extern u16 D_8018FB3C;
extern u16 D_8018FB3E;
extern u16 D_8018FB40;
extern s32 D_8018FB44;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018FB4C;
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
extern int D_8018F858;
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
extern unsigned int D_8018FBD0[];
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
extern void (*D_8018FC80[])(void);
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
extern u16 D_8018FCB0[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018FD14;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801EBA58[];
extern void func_8016216C(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018FD38[])(void);
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
extern int D_801EBAB0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018FD80[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018FD70;
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
extern char D_801EAE90[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018FD88[])(void);
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
extern void (*D_8018FDDC[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018FDA4;
extern s16 D_8018FDD8;
extern s16 D_8018FDD6;
extern s16 D_8018FDD4;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018FDE8[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801EBB10;
extern u8 D_801EBB11;
extern u8 D_801EBB12;
extern u8 D_801EBB13;
extern u8 D_801EBB14;
extern u8 D_801EBB15;
extern u8 D_801EBB16;
extern u8 D_801EBB17;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018FDF8[])(void);
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
extern s32 D_801EBB50;
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
extern void (*D_8018FE3C[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018FEB8[];
extern s32 D_8018FED8[];
extern u8 D_8018FF54[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018FF74[];
extern u8 D_8018FF94[];
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
extern void (*D_80190030[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801900AC[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801EAEA0;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801900B8[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801900C0[])(void);
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
extern void (*D_80190188[])(void);
extern void func_80166618(void *a0);
extern void (*D_80190198[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801901A8[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801901B4[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80190114[];
extern u8   D_80190128[];
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
extern void (*D_801901CC[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801901D4[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801901DC[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801901E4[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_801901EC[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_801901F4[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_801901FC[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801902B0[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801902B8[])(void);
extern void func_80169F00(void *a0);
extern char D_80190268[];
extern char D_80190228[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_801902F0[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_801902FC[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80190344[])(void);
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
extern void (*D_801903C0[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801EBE70;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801903B4[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_801903F8[];
extern unsigned short D_80190400[];
extern unsigned short D_80190408[];
extern unsigned char D_801EBE78[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801EBE70;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80190410[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801EBFAC;
extern M2C_UNK D_801EBFB0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801EBF38;
extern void (*D_80190440[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801EBFB4[];
extern u8 D_801EBFBC[];
extern u8 D_801EBF6C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80190448[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80190464[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8019046C[])(void);
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
extern void (*D_801904D4[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80190478;
extern u8 D_80190484;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80190508[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80190510[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80190564[])(void);
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
extern u16 D_80190598[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80190588[];
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
extern s32 D_801905B4;
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
extern void (*D_8019062C[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80190634[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8019063C[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80190644[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8019064C[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80190654[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80190660[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8019066C[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80190678[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80190688[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80190698[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_801906A0[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_801906A8[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_801906B0[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_801906B8[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_801906C0[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_801906C8[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_801906D0[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_801906D8[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_801906E0[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_801906E8[])(void);
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
extern void (*D_801906F0[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_801906F8[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80190700[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80190708[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80190710[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80190718[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80190720[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80190728[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80190730[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80190738[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80190740[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80190748[])(void);
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
extern void (*D_8019078C[])(void);
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
extern M2C_UNK D_80190750;
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
extern void (*D_801907BC[])(void);
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
extern void (*D_801907F8[])(void);
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
extern void (*D_80190850[])();
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
extern void (*D_80190860[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80190868[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175494(void);
extern void (*D_801909D0[])();
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
extern void (*D_801909DC[])();
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
extern M2C_UNK D_801EB0E8;
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
extern s16 D_801ED910;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801EC6F0;
extern short D_801ED984;
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
extern s32 D_801ECB1C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801ECB44;
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
extern s16 D_801ECB00;
extern s32 func_8017A3B0(void);
extern short D_801ECB3C;
extern short D_801ECB38;
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
extern s16 D_801ED8C8;
extern s16 D_801ED8CA;
extern s16 D_801ED8D4;
extern void func_8017AE2C(s32 param_1);
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801ECB04;
extern u16 D_801ECB84;
extern u16 D_801ECB86;
extern u16 D_801ECB88;
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
extern s16 D_801ECB7C;
extern s16 D_801ECB7E;
extern s16 D_801ECB80;
extern s16 D_801ECB74;
extern s16 D_801ECB76;
extern s16 D_801ECB78;
extern void func_8017B7A8(void);
extern s16 D_801ECB94;
extern s16 D_801ECB96;
extern s16 D_801ECB98;
extern s16 D_801ECB9C;
extern s16 D_801ECB9E;
extern s16 D_801ECBA0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801ECB8C;
extern short D_801ECB8E;
extern short D_801ECB90;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801ECB24;
extern SV4 D_801ECB2C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801ECB4C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801ECB48)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80190BB8[])(void);
extern void func_8017BE60(void *a0);
extern void (*D_80190C58[])(void);
extern void func_8017BE9C(void *a0);
extern void (*D_80190C60[])(void);
extern void func_8017BED8(void *a0);
extern void (*D_80190C68[])(void);
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
extern void (*D_80190C88[])(void);
extern void func_8017C338(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_8017C374(s32 param_1);
extern void func_8017C538(u8 *p);
extern void (*D_80190C90[])(void);
extern void func_8017C5CC(void *a0);
extern u8 D_80190C7C;
extern void func_8017C608(s32 a0);
extern void func_8017C6AC(int a0);
extern void func_8017C710(s32 arg0);
extern void (*D_80190CA8[])(void);
extern void func_8017D5F0(void *a0);
extern void func_8001C214(s32, s32);
extern u32 D_80190C98;
extern void func_8017D62C(s32 arg0);
extern void func_8017D6A8(void);
extern void (*D_80190CE0[])(void);
extern void func_8017D6B0(void *a0);
extern void func_8017DA08(void *arg0);
extern s32 func_8012AD50(void *arg0);
extern void func_8017D6EC(void *arg0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8017D9B8(void);
extern void func_8017DAC4(void *arg0);
extern void aF8017D77C();
extern void func_80017714(void *);
extern void func_8013CB84(void);
extern void func_8017DC0C(void);
extern void func_800D06E8(void);
extern void func_8017DBDC(void);
extern u32 D_801ECE40;
extern u16 D_80190CE8[];
extern u16 D_801ECE44[];
extern s32 D_80190D08;
extern void func_8017E050(void *arg0);
extern s32 func_8017DC98(s32 param_1);
extern s32 func_8017DCE8(void);
extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8001BFD0(void);
extern s32 func_8017DD7C(s32 a0);
extern void func_800D1EBC(void);
extern void func_8017DE2C(void);
extern s32 func_8017DE4C(void *a0);
extern void (*D_80190D28[])(void);
extern void func_8017DF4C(void *a0);
extern void (*D_80190D30[])(void);
extern void func_8017DF88(void *a0);
extern void (*D_80190D3C[])(void);
extern void func_8017DFC4(void *a0);
extern void (*D_80190D48[])(void);
extern void func_8017E000(void *a0);
extern s32 D_80127050;
extern void func_8017E03C(void);
extern void (*D_80190FFC[])(void);
extern void func_8017E050(void *a0);
extern void func_8017E08C(u8 *a0);
extern void func_8017E0A0(void *a0);
extern void (*D_80191004[])(void);
extern void func_8017E0D8(void *a0);
extern void func_8017E114(void *a0);
extern void func_8017E128(void);
extern void func_8012A094(s32 a0);
extern void func_8017E20C(void *a0);
extern void func_8017E148(void);
extern void (*D_8019100C[])(void);
extern void func_8017E27C(u8 *a0);
extern void func_8017E284(void *a0, u8 *a1);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017E3C4(s32 param_1);
extern void (*D_80191158[])(void);
extern void func_8017E5B8(void *a0);
extern void func_80029514(int);
extern void func_8017E5F4(void);
extern s32 func_80178B18(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern s16 D_80191028[6];
extern void func_8017E614(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8017E6D8(void *a0);
extern u8 D_80078EAE;
extern s32 func_8017E778(void);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_80184990(s32);
extern void func_80184BD4(s32, s32, s32, s32);
extern void func_8017E7EC(void *arg0);
extern s32 D_801B9DB4;
extern short D_801B6364;
extern void func_80185CB8(s32, s32, s32);
extern void func_8017E85C(void *arg0);
extern void func_8017E8CC(s32 a0);
extern s32 func_801848D0(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_8017EA6C(s32 a0);
extern s16 D_80191248;
extern s16 D_80191228;
extern s16 D_801E4130;
extern void func_8017E92C(s32 a0);
extern void func_8012E8A8(u8 *a0);
extern void func_801849B0(void *a0);
extern void func_8017EAE0(void *a0);
extern s16  func_80184B44(void);
extern s32  func_801844BC(void *a0, void *a1);
extern s32  func_801848AC(s32 arg0, s32 arg1);
extern void func_8012E88C(s32 a0);
extern void func_801849B8(s32 *a0, s32 a1);
extern void func_80185CB8(s32 a0, s32 a1, s32 a2);
extern void func_8017EE10(void);
extern void func_8017EB30(void *a0);
extern void (*D_801912B8[])(void);
extern void func_8017ED1C(void *a0);
extern void func_8017ED94(s32 a0);
extern s32 func_8017EDD4(void);
extern void func_8017EEC8(void *a0);
extern s32 func_80184CA4(s32);
extern void func_8017E8CC(s32);
extern void func_8017EF78(s32 a0);
extern void func_8017EFFC();
extern void func_8017F04C(void *a0);
extern s32 func_801858E0(s32 a0);
extern s32 func_80184CA4(s32 a0);
extern void func_801849B8(s32*, s32);
extern void func_8017F0C0(s32 a0);
extern void func_80029124(s32 arg0, s32 arg1);
extern void func_8017F174(void);
extern void func_8017F198(s32 a0);
extern void func_8017F398(short *a0);
extern void (*D_80191350[])(void);
extern void func_8017F3C4(void *a0);
extern short D_80191318;
extern void func_8017F400(short *param);
extern void func_8017F42C(s32 a0);
extern s32 func_8012E544(s32 a0);
extern void func_8017F398(s16 *a0);
extern void func_8017F46C(s16 *arg0);
extern void func_8017F53C(void * arg0);
extern s32 func_8012E544(s32 arg0);
extern s32 func_8017F650(void *a0);
extern void func_8017F58C(void *a0);
extern s32 func_801845DC(void);
extern s32 func_80185F5C(void *);
extern s32 func_80178BF8(void);
extern void func_8017F6C8(void *arg0);
extern void func_80184990(s32 a0);
extern void func_8017F73C(void *a0);
extern void func_8017F794(void *arg0);
extern void func_8017F81C(void * arg0);
extern s32 func_8017FA98(void *a0);
extern s32 func_8017FB10(void *a0);
extern void func_8017F848(void *arg0);
extern void (*D_801913FC[])(void);
extern void func_8017F98C(void *a0);
extern s32 func_80180AEC(s32 a0);
extern short D_8019136C;
extern short D_801B9B0C;
extern void func_80178CBC(s32, s32);
extern void func_8017F9C8(void *a0);
extern short D_8019139C;
extern void func_8017FA2C(void *arg0);
extern void func_8017FA58(s32 a0);
extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();   /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2541) */
extern void func_8017F6C8(void *a0);
extern void func_8017F81C(void *a0);
extern void func_8017FC00(void *arg0);
extern void func_8017FCA0(void *a0);
extern void func_8017FDB8(void *a0);
extern s32 func_801858E0(s32);
extern void func_8017F81C(void *);
extern void func_8017FE28(void *arg0);
extern short D_80191364;
extern void func_8017FF6C();
extern void func_80178CBC(s32 a0, s32 a1);
extern void func_8017FFBC(void * arg0);
extern void func_80180048(void *arg0);
extern void func_80180124(void *arg0);
extern void func_80180188(void * arg0);
extern void func_80180240(void * arg0);
extern void func_8001C97C(s32 a0);
extern s32 func_801805F0(void *a0);
extern void func_801803D8(void *a0);
extern void (*D_80191504[])(void);
extern void func_801804F0(void *a0);
extern void func_8018052C(void *arg0);
extern void func_8018058C(s32 a0);
extern s32 func_801805CC(void);
extern void func_80180048(void *a0);
extern void func_80180664(void *a0);
extern s32 func_801858E0(s32 arg0);
extern u8 D_801B63D4[];
extern void func_801800BC(void *a0);
extern void func_801806BC(void *a0);
extern void func_80180748(void *arg0);
extern void func_80184BD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80180188(void *a0);
extern void func_80180808(void *arg0);
extern void func_801801B4(void *arg0);
extern void func_80180894(void *arg0);
/* ==== end §8b carried decl layer ==== */


extern s32 func_801858E0(s32 a0);
extern s32 func_80184CA4(s32 a0);
extern void func_80184BD4(s32 a0, s32 a1, s32 a2, s32 a3);

void func_801808D4(void *arg0)
{
    extern u8 D_801B63C8[];
    extern u8 D_801B640C[];
    extern u8 D_801B645C[];

    switch (*(u16 *)((s32)arg0 + 0x34)) {
    case 0:
        if (func_801858E0(3) == 0) {
            return;
        }
        *(u16 *)((s32)arg0 + 0x34) = 1;
        func_80184BD4((s32)arg0, (s32)&D_801B63C8, 0, 0x80);
        return;
    case 1:
        func_801858E0(3);
        if (func_80184CA4((s32)arg0) == 0) {
            return;
        }
        *(u16 *)((s32)arg0 + 0x34) = 2;
        func_80184BD4((s32)arg0, (s32)&D_801B640C, 0, 0x80);
        return;
    case 2:
        if (func_80184CA4((s32)arg0) != 0) {
            *(u16 *)((s32)arg0 + 0x34) = 3;
        }
        return;
    case 3:
        if (func_801858E0(13) == 0) {
            return;
        }
        *(u16 *)((s32)arg0 + 0x34) = 4;
        func_80184BD4((s32)arg0, (s32)&D_801B645C, 0, 0x80);
        return;
    case 4:
        func_801858E0(13);
        if (func_80184CA4((s32)arg0) != 0) {
            func_80180240(arg0);
        }
        return;
    }
}



/* func_801809E0 — guarded dispatch: ask func_801848AC(17, 0x12); if it answers
 * zero, run func_8018026C on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_801848AC(s32 arg0, s32 arg1);
extern void func_8018026C(void *arg0);

void func_801809E0(void *arg0) {
    if (func_801848AC(17, 0x12) == 0) {
        func_8018026C(arg0);
    }
}




extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32);
extern void func_80184BD4(s32, s32, s32, s32);


void func_80180A20(void *arg0) {

    extern short D_80191530;
    extern short D_801B6468;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern short D_801B9A64;
    *(short *)((char *)arg0 + 0x2) = 2;
    func_8012E8E0((s32)arg0, (s32)&D_80191530);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801B9A64);
    func_80184990((s32)arg0);
    *(short *)((char *)arg0 + 0x34) = 0;
    func_80184BD4((s32)arg0, (s32)&D_801B6468, 0, 0x40);
}




extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32 a0);


void func_80180A94(void *a0) {

    extern short D_80191538;
    extern short D_801B9B0C;
    *(short *)((char *)a0 + 0x2) = 3;
    func_8012E8E0((s32)a0, (s32)&D_80191538);
    func_8012E88C((s32)a0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801B9B0C);
    func_80184990((s32)a0);
}


s32 func_80180AEC(s32 a0) {
    extern short D_80191818;
    extern short D_801917F0;
    extern s32 D_80191868[];
    extern s32 func_8012E544(s32 a0);
    extern s16 func_80184B44(void);

    s32 v;

    if (*(u16 *)a0 == 0x363) {
        v = func_8012E544(0x365);
        if (v == 0) {
            goto zero;
        }
        goto chk;
    } else {
        v = func_8012E544(0x363);
        if (v != 0) {
            goto chk;
        }
    }
zero:
    v = 0;
    goto join;
chk:
    v = (*(u16 *)(v + 2) == 3);
join:
    if (v == 0) {
        if (*(u16 *)a0 == 0x363) {
            return (s32)&D_801917F0;
        }
        return (s32)&D_80191818;
    }
    return D_80191868[((s32 (*)(void))func_80184B44)()];
}


    extern void func_8012E8E0(s32 a0, s32 a1);
    extern void func_8012E88C(s32 a0);
    extern void func_8012A828(s32, s32);
    extern void func_80184990(s32);
    extern void func_80184BD4(s32, s32, s32, s32);
    void func_80180BA8(void *arg0) {
        extern short D_80191538;
        extern s32 D_801B9A64;
        extern u8 D_801B6474[];
        void *v1;
        *(short *)((char *)arg0 + 0x2) = 0x4;
        func_8012E8E0((s32)arg0, (s32)&D_80191538);
        v1 = *(void **)((char *)arg0 + 0x20);
        *(short *)((char *)v1 + 0x12) = *(short *)((char *)v1 + 0x12) + 0x800;
        func_8012E88C((s32)arg0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&(*(short *)&D_801B9A64));
        func_80184990((s32)arg0);
        *(short *)((char *)arg0 + 0x34) = 0;
        func_80184BD4((s32)arg0, (s32)&(*(short *)D_801B6474), 0x1, 0x40);
    }


extern void func_801849B8(s32 *a0, s32 a1);
    extern short D_80191530;
    void func_80180C30(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x5;
        func_801849B8((s32 *)a0, (s32)&D_80191530);
    }


#include "common.h"

/* func_80180C5C — entity spawn/init state machine.
 *
 * Shape read off the target .s (asm/ov_SC05_017/nonmatchings/ov_SC05_017_jr_8017AE2C/func_80180C5C.s):
 *   - func_801844BC(a0, &D_80191540): bail (return) if it reports 0.
 *   - probe func_80184B44()/func_801848AC(...) twice to compute a small
 *     "mode" value v1 in {0,1,2}.
 *   - dispatch on v1: case 1/2 share a func_801849B8 tail (mirrors the
 *     TU's func_80180C30, which hardcodes state=5 + the same call); the
 *     default (v1==0) shares its 4-call tail with the TU's func_80180A94
 *     (state=3 + func_8012E8E0/func_8012E88C/func_8012A828/func_80184990).
 *   - shared tail: re-arm the template entity at s0->0x68 (state field
 *     0x7FFF), spawn two child entities via func_801788B8 (handlers
 *     func_80180F3C / func_80180FB4) and stash their pointers at
 *     s0->0xD4 / s0->0xD8, per the ov_SC03_006 / ov_SC03_014 sibling idiom
 *     `func_801788B8(s0, (s32)handler)`.
 */

extern s32 func_801844BC(void *a0, void *a1);
extern s32 func_801848AC(s32 arg0, s32 arg1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32 a0);
extern void func_801849B8(s32 *a0, s32 a1);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_80180F3C(void *a0);
extern s32 func_80180FB4(void *a0);

void func_80180C5C(void *a0) {

    extern short D_80191540;
    extern short D_80191538;
    extern short D_801B9B0C;
    extern short D_80191530;
    extern s16 func_80184B44(void);   /* TU-canonical decl (e.g. L4848) */

    void *s0 = a0;
    s32 v0, v1, arg0;
    void *newEnt;

    if (func_801844BC(a0, &D_80191540) == 0) {
        return;
    }

    if (((s32 (*)(void))func_80184B44)() == 1) {
        arg0 = 0xA;
    } else if (func_801848AC(0xA, 0x10) == 0) {
        arg0 = 0x10;
    } else {
        v1 = 0;
        goto dispatch;
    }
    v1 = (func_801848AC(arg0, 0x15) != 0) ? 1 : 2;
dispatch:

    switch (v1) {
    case 0:
        v0 = 3;
        *(u16 *)((u8 *)s0 + 2) = v0;
        func_8012E8E0((s32)s0, (s32)&D_80191538);
        func_8012E88C((s32)s0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)s0, (s32)&D_801B9B0C);
        func_80184990((s32)s0);
        break;
    case 1:
        v0 = 5;
        goto set_and_call;
    case 2:
        v0 = 1;
    set_and_call:
        *(u16 *)((u8 *)s0 + 2) = v0;
        func_801849B8((s32 *)s0, (s32)&D_80191530);
        break;
    default:
        v0 = 1;
        break;
    }

    {
        register void *pv0 __asm__("$2");
        register s32 pv1 __asm__("$3");
        pv0 = *(void **)((u8 *)s0 + 0x68);
        pv1 = 0x7FFF;
        *(s16 *)((u8 *)pv0 + 0xC) = (s16)pv1;
    }
    newEnt = (void *)func_801788B8((s32)s0, (s32)func_80180F3C);
    *(s32 *)((u8 *)s0 + 0xD4) = (s32)newEnt;
    func_8012E8E0((s32)newEnt, (s32)&D_80191530);
    newEnt = (void *)func_801788B8((s32)s0, (s32)func_80180FB4);
    *(s32 *)((u8 *)s0 + 0xD8) = (s32)newEnt;
}



extern void (*D_8019187C[])(void);

void func_80180DA4(void *a0) {
    D_8019187C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern s32 func_8012E544(s32 a0);
extern s16 func_80184B44(void);
extern void func_80178CBC(s32, s32);

void func_80180DE0(void *a0) {

    extern short D_80191538;
    extern short D_801B9B0C;
    extern short D_80191818;
    extern short D_801917F0;
    extern s32 D_80191868[];

    s32 v;
    s32 arg;

    *(short *)((char *)a0 + 0x2) = 9;
    func_8012E8E0((s32)a0, (s32)&D_80191538);
    func_8012E88C((s32)a0);
    ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801B9B0C);

    /* The two arms end in DIFFERENT branch senses/targets, so cross_jump finds
       no common scheduled suffix and the two jal sites stay distinct (§193-C). */
    if (*(u16 *)a0 == 0x363) {
        v = func_8012E544(0x365);
        if (v == 0) {
            goto zero;
        }
        goto chk;
    } else {
        v = func_8012E544(0x363);
        if (v != 0) {
            goto chk;
        }
    }
zero:
    v = 0;
    goto join;
chk:
    v = (*(u16 *)(v + 2) == 3);
join:
    if (v == 0) {
        arg = (s32)&D_80191818;
        if (*(u16 *)a0 == 0x363) {
            arg = (s32)&D_801917F0;
        }
    } else {
        arg = D_80191868[((s32 (*)(void))func_80184B44)()];
    }

    ((void (*)(s32, s32))func_80178CBC)((s32)a0, arg);
}


extern void func_80178CBC(s32 arg0, s32 arg1);
    extern short D_80191568;
    void func_80180ED0(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x7;
        func_80178CBC((s32 *)a0, (s32)&D_80191568);
    }



extern s16 func_80184B44(void);

void func_80180EFC(s32 a0) {

    extern s32 D_80191554[];
    s32 idx = ((s32 (*)(s32))func_80184B44)(a0);
    *(s32 *)(a0 + 0xE4) = D_80191554[idx];
}



extern void func_80172710(void);
extern s32 func_801845DC(void);
extern s32 func_80185F5C(void *);
extern s32 func_80178BF8(void);

s32 func_80180F3C(void *a0)
{
    void *s0 = a0;
    void **v0p;
    u16 v1;

    v0p = (void **)(s0 + 0x64);
    v1 = *(u16 *)(*v0p + 0x2);
    if (v1 != 0x5) {
        return 0;
    }

    if (func_801845DC() == 0) {
        return 0;
    }

    if (func_80185F5C(*v0p) != 0) {
        return 0;
    }

    *(u16 *)(*v0p + 0x2) = 0x6;
    func_80178BF8();

    return (s32)func_80172710;
}



/* func_80180FB4 — state-machine callback registered by func_80180A08.
 *
 * Shape (read off the target, not off Ghidra — the Ghidra seed is for a
 * different address entirely):
 *   - guard call func_8012BD14(a0->0x64), bail if result > 0x4000
 *   - switch on the u16 at +2 of a0->0x64, cases 3 / 2 / 4 (gcc balances the
 *     tree on the middle case 3, hence `slti $v0,$v1,4` for "index > node->high")
 *   - the comparison constants for the case-2/case-4 sub-tests ride in the
 *     dispatch branch delay slots (§3-T4: read the constant off the delay slot,
 *     not off the branch line) — case 2 tests +0x34 == 1, case 4 tests +0x34 == 0
 *   - the two adjacent globals get their own `lui $at` each => two separate
 *     symbols, NOT one array (§20 pointer-var rule does not apply here)
 *   - +0x34 is reloaded after the D_801ECE78 store, and 0x64 is reloaded too:
 *     gcc-2.7.2 CSE invalidates memory on the global store, so re-express both
 */

extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();   /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2541) */
extern void func_80172710(void);

s32 func_80180FB4(void *a0)
{

    extern s16 D_801ECE78;
    extern s16 D_801ECE7A;
    void *p;
    u16 st;

    if (func_8012BD14(*(s32 *)((s32)a0 + 0x64)) > 0x4000) {
        /* LOAD-BEARING zero-byte cross-jump barrier (cookbook §5a).
         * Without it gcc's find_cross_jump merges this `move v0,0; j epi`
         * tail with the identical case-2 failure tail -> 58 ins instead of
         * 60, and the case-2 `beq` then loses its delay-slot fill. */
        __asm__ __volatile__("");
        return 0;
    }

    p = *(void **)((s32)a0 + 0x64);
    st = *(u16 *)((s32)p + 0x2);
    switch (st) {
    case 3:
        *(s16 *)((s32)p + 0x2) = 8;
        break;
    case 2:
        if (*(u16 *)((s32)p + 0x34) != 1) {
            return 0;
        }
        goto hit;
    case 4:
        if (*(u16 *)((s32)p + 0x34) != 0) {
            return 0;
        }
    hit:
        D_801ECE78 = st;
        D_801ECE7A = *(u16 *)((s32)p + 0x34);
        *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 10;
        break;
    default:
        return 0;
    }

    func_80178BF8();
    return (s32)func_80172710;
}


INCLUDE_ASM("asm/ov_SC05_017/nonmatchings/ov_SC05_017_jr_801808D4", func_801810A4);


extern s32 func_801858E0(s32 a0);
extern s32 func_80184CA4(s32 a0);
extern void func_80184BD4(s32, s32, s32, s32);
extern void func_80180A94(void *a0);

void func_80181144(void *a0)
{

    extern u8 D_801B6474[];
    if (*(u16 *)((s32)a0 + 0x34) == 0) {
        if (func_801858E0(3) == 0) {
            return;
        }
        if (func_80184CA4((s32)a0) == 0) {
            return;
        }
        ((void (*)(void *, void *, s32, s32))func_80184BD4)(a0, D_801B6474, 0, 0x40);
        *(s16 *)((s32)a0 + 0x34) = 1;
        return;
    }

    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    if (func_80184CA4((s32)a0) != 0) {
        func_80180A94(a0);
    }
}


extern s16 func_80184B44(void);
extern s32 func_801848AC(s32 arg0, s32 arg1);
extern void func_80180BA8(void *arg0);

void func_801811D8(void *a0)
{
    s32 v1;

    *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    if (((s32 (*)(void))func_80184B44)() == 1) {
        v1 = func_801848AC(10, 0x15) != 0 ? 1 : 2;
    } else if (func_801848AC(10, 0x10) != 0) {
        v1 = 0;
    } else {
        v1 = func_801848AC(16, 0x15) != 0 ? 1 : 2;
    }

    switch (v1) {
    case 0:
        break;
    case 1:
        func_80180BA8(a0);
        break;
    case 2:
        func_80180BA8(a0);
        break;
    }
}



extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32);


void func_80181268(void *a0) {

    extern short D_80191538;
    extern short D_801B9B0C;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)a0);
        *(short *)((char *)a0 + 0x2) = 3;
        func_8012E8E0((s32)a0, (s32)&D_80191538);
        func_8012E88C((s32)a0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801B9B0C);
        func_80184990((s32)a0);
    }
}



extern s32 func_80184CA4(s32 a0);
extern void func_80184BD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_801858E0(s32 a0);
extern void func_80180C30(short*);

void func_801812D8(void *arg0) {

    extern u8 D_801B6468[];
    if (*(u16 *)((char *)arg0 + 0x34) == 0) {
        if (((s32 (*)(void))func_80184CA4)() != 0) {
            func_80184BD4((s32)arg0, (s32)&D_801B6468[0], 1, 0x40);
            *(s16 *)((char *)arg0 + 0x34) = 1;
        }
    } else if (func_801858E0(3) != 0) {
        if (func_80184CA4((s32)arg0) != 0) {
            ((void (*)(void *))func_80180C30)(arg0);
        }
    }
}


void func_80181364(void *arg0) {
    extern s16 func_80184B44(void);
    extern s32 func_801848AC(s32 arg0, s32 arg1);
    extern void func_801849B8(s32 *a0, s32 a1);
    extern short D_80191530;

    void *s0 = arg0;
    s32 v0;
    s32 code;
    s32 a0val;

    *(s32 *)(*(s32 *)((u8 *)s0 + 0xCC) + 0xB0) = 2;

    v0 = ((s32 (*)(void))func_80184B44)();
    if (v0 == 1) {
        a0val = 0xA;
    } else {
        if (func_801848AC(0xA, 0x10) != 0) {
            code = 0;
            goto ladder_done;
        }
        a0val = 0x10;
    }
    if (func_801848AC(a0val, 0x15) != 0) {
        code = 1;
    } else {
        code = 2;
    }
ladder_done:
    switch (code) {
    case 0:
    case 2:
        *(s16 *)((u8 *)s0 + 0x2) = 1;
        func_801849B8((s32 *)s0, (s32)&D_80191530);
        break;
    case 1:
        break;
    }
}


extern int func_80178970(void);
extern short D_80191530;
extern void func_80178D18(void);
extern void func_801849B8(s32 *a0, s32 a1);

void func_80181414(arg0)
void * arg0;
{

    extern short D_80191530;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 5;
        ((void (*)(s32, s32))func_801849B8)((int)arg0, (int)&D_80191530);
    }
}



extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80191840;
    void func_80181464(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 11;
        func_80178CBC((int)arg0, (int)&D_80191840);
    }


extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012A828(s32, s32);

void func_80181490(void *arg0)
{
    extern short D_801ECE78;
    extern short D_801ECE7A;
    extern short D_801B9A64;

    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = D_801ECE78;
        *(short *)((char *)arg0 + 0x34) = D_801ECE7A;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801B9A64);
    }
}




extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32);
extern void func_80184BD4(s32, s32, s32, s32);


void func_801814F0(void *arg0) {

    extern short D_801918AC;
    extern short D_801B649C;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern short D_801B9964;
    *(short *)((char *)arg0 + 0x2) = 2;
    func_8012E8E0((s32)arg0, (s32)&D_801918AC);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801B9964);
    func_80184990((s32)arg0);
    *(short *)((char *)arg0 + 0x34) = 0;
    func_80184BD4((s32)arg0, (s32)&D_801B649C, 0, 0x60);
}




extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32 a0);


void func_80181564(void *a0) {

    extern short D_801918B4;
    extern short D_801C0CFC;
    *(short *)((char *)a0 + 0x2) = 3;
    func_8012E8E0((s32)a0, (s32)&D_801918B4);
    func_8012E88C((s32)a0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801C0CFC);
    func_80184990((s32)a0);
}


    extern void func_8012E8E0(s32, s32);
    extern void func_8012E88C(s32);
    extern void func_8012A828(s32, s32);
    extern void func_80184990(s32);
    extern void func_80184BD4(s32, s32, s32, s32);
    void func_801815BC(void *arg0) {
        extern short D_801918B4;
        extern short D_801B9964;
        extern short D_801B64A8;
        *(short *)((char *)arg0 + 0x2) = 6;
        func_8012E8E0((s32)arg0, (s32)&D_801918B4);
        func_8012E88C((s32)arg0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801B9964);
        func_80184990((s32)arg0);
        *(short *)((char *)arg0 + 0x34) = 0;
        func_80184BD4((s32)arg0, (s32)&D_801B64A8, 1, 0x60);
    }



extern void (*D_80191990[])(void);

void func_80181630(void *a0) {
    D_80191990[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80178CBC(s32, s32);

void func_8018166C(void *arg0) {

    extern s32 D_801918B4;
    extern s32 D_80191910;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801B9A0C;
    *(short *)((char *)arg0 + 0x2) = 5;
    func_8012E8E0((s32)arg0, (s32)&D_801918B4);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801B9A0C);
    ((void (*)(s32 *, s32))func_80178CBC)((s32 *)arg0, (s32)&D_80191910);
}


INCLUDE_ASM("asm/ov_SC05_017/nonmatchings/ov_SC05_017_jr_801808D4", func_801816CC);


extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801816DC(void) {
        if ((func_80029178(0x113) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x113, 1);
            return 1;
        }
        return 0;
    }



/* func_80181718 — guarded dispatch: ask func_801848AC(7, 0xe); if it answers
 * NON-zero, run func_801814F0 on the incoming entity.  The entity pointer is
 * live across the jal, so it lands in $s0 and comes back out as $a0.
 * §71 sibling: func_80181B34 in this same TU is the identical shape.
 * §3-T4: target branch is `beqz $v0, ret` => the C condition is `!= 0`
 * (the sibling's is `bnez` => `== 0`; polarity is read off the opcode). */

extern s32 func_801848AC(s32 arg0, s32 arg1);
extern void func_801814F0(void *arg0);

void func_80181718(void *arg0) {
    if (func_801848AC(7, 0xe) != 0) {
        func_801814F0(arg0);
    }
}


extern s32 func_80184CA4(s32 a0);
extern s32 func_801858E0(s32 arg0);
extern void *D_801B64A8;
extern void func_80181564(void *a0);
extern void func_80184BD4(s32, s32, s32, s32);

void func_80181758(s32 a0) {
    s32 v0, v1;

    if (*(u16 *)(a0 + 0x34) == 0) {
        if ((v0 = func_801858E0(2)) != 0 && (v0 = func_80184CA4(a0)) != 0) {
            *(u16 *)(a0 + 0x34) = 1;
            func_80184BD4(a0, (s32)&D_801B64A8, 0, 0x60);
            v1 = *(s32 *)(a0 + 0xCC);
            *(s32 *)(v1 + 0xB0) = 2;
        }
    } else {
        if ((v0 = func_80184CA4(a0)) != 0) {
            func_80181564(a0);
        }
    }
}



/* func_801817F0 — guarded dispatch: ask func_801848AC(7, 0xE); if it answers
 * zero, run func_801815BC on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern s32 func_801848AC(s32 arg0, s32 arg1);
extern void func_801815BC();

void func_801817F0(void *arg0) {
    if (func_801848AC(7, 0xE) == 0) {
        func_801815BC(arg0);
    }
}



extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32);


void func_80181830(void *a0) {

    extern short D_801918B4;
    extern short D_801C0CFC;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)a0);
        *(short *)((char *)a0 + 0x2) = 3;
        func_8012E8E0((s32)a0, (s32)&D_801918B4);
        func_8012E88C((s32)a0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801C0CFC);
        func_80184990((s32)a0);
    }
}


extern s32 func_80184CA4(s32 a0);
extern s32 func_801858E0(s32 arg0);
extern short D_801918AC;
extern short D_801B649C;
extern void func_801849B8(s32*, s32);
extern void func_80184BD4(s32, s32, s32, s32);

void func_801818A0(s32 a0) {
    if (*(u16*)(a0 + 0x34) == 0) {
        if (func_80184CA4(a0) != 0) {
            *(s16*)(a0 + 0x34) = 1;
            func_80184BD4(a0, (s32)&D_801B649C, 1, 0x60);
        }
    } else {
        if (func_801858E0(0x2) != 0) {
            if (func_80184CA4(a0) != 0) {
                *(s16*)(a0 + 0x2) = 1;
                func_801849B8((s32*)a0, (s32)&D_801918AC);
            }
        }
    }
}


extern void func_8012A828(s32, s32);
extern void func_801849B8(s32*, s32);

void func_8018193C(void *a0) {

    /* [T51] shadow: file-scope `extern s16 ((s32 (*)(void))func_80184B44)(void)` (this TU, near
       func_8017FA58) is in scope at this point and would sign-extend $v0 with
       an sll after the jal; the target has none. Block-scope int-return decl
       restores the implicit-int call shape (cf. func_80181364's cast). */
    extern s16 func_80184B44(void);

    extern s16 D_801918BC;
    extern s16 D_801918B4;
    extern short D_801C0CFC;
    extern short D_801918AC;
    extern s32 D_801D5AFC;
    extern s32 D_801D2C58;
    extern s32 D_801ECE80;
    extern s32 func_80181A4C(void*);
    void *v1;

    if (((s32 (*)(void))func_80184B44)() != 0) {
        func_8012CAE4(a0);
        return;
    }
    if (func_801844BC(a0, &D_801918BC) == 0) {
        return;
    }
    func_8001C97C((s32)&D_801D5AFC);
    D_801ECE80 = D_801D2C58;
    D_801D2C58 = D_801D5AFC;
    if (func_801848AC(7, 0xE) != 0) {
        *(s16 *)((char *)a0 + 0x2) = 3;
        func_8012E8E0((s32)a0, (s32)&D_801918B4);
        func_8012E88C((s32)a0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801C0CFC);
        func_80184990((s32)a0);
    } else {
        *(s16 *)((char *)a0 + 0x2) = 1;
        ((void (*)(s32, s32))func_801849B8)((int)a0, (int)&D_801918AC);
    }
    v1 = *(void **)((char *)a0 + 0x68);
    *(s16 *)((char *)v1 + 0xC) = 0x7FFF;
    *(s32 *)((char *)a0 + 0xD4) = func_801788B8((s32)a0, (s32)&func_80181A4C);
}


extern s32 func_8012BD14(s32 a0);
extern s32 func_8012E544(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710();

s32 func_80181A4C(void *a0)
{
    s32 ptr;
    s32 t;
    u16 st;

    ptr = *(s32 *)((s32)a0 + 0x64);
    st = *(u16 *)((s32)ptr + 0x2);
    if (st != 3) {
        return 0;
    }

    t = func_8012BD14(ptr);
    if (t >= 0x4001) {
        return 0;
    }

    {
        s32 e;
        e = func_8012E544(0x372);
        if (e != 0 && *(u16 *)((s32)e + 0x2) == 8 && func_8012BD14(e) < t) {
            return 0;
        }
    }

    {
        s32 p;
        u16 st2;
        p = *(s32 *)((s32)a0 + 0x64);
        st2 = *(u16 *)((s32)p + 0x2);
        st2++;
        *(u16 *)((s32)p + 0x2) = st2;
    }
    func_80178BF8();
    return (s32)func_80172710;
}


extern void func_801849B8(s32 *a0, s32 a1);
    extern short D_801919AC;
    void func_80181B04(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x2;
        func_801849B8((s32 *)a0, (s32)&D_801919AC);
    }



extern void (*D_80191AA4[])(void);

void func_80181B30(void *a0) {
    D_80191AA4[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80191A54;
    void func_80181B6C(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 4;
        func_80178CBC((int)arg0, (int)&D_80191A54);
    }



extern s16 func_80184B44(void);

void func_80181B98(s32 a0) {

    extern s32 D_801919E4[];
    s32 idx = ((s32 (*)(s32))func_80184B44)(a0);
    *(s32 *)(a0 + 0xE4) = D_801919E4[idx];
}


INCLUDE_ASM("asm/ov_SC05_017/nonmatchings/ov_SC05_017_jr_801808D4", func_80181BD8);

INCLUDE_ASM("asm/ov_SC05_017/nonmatchings/ov_SC05_017_jr_801808D4", func_80181C1C);

extern s16 func_80184B44(void);
extern s32 D_801ED90C;

void func_80181C60(void) {
    if (((s32 (*)(void))func_80184B44)() > 0) {
        *(s32 *)(D_801ED90C + 4) = 0x10;
    } else {
        *(s32 *)(D_801ED90C + 4) = 0x11;
    }
}




extern s32 func_801848AC(s32 arg0, s32 arg1);
extern void func_80181B04(short*);

void func_80181CA4(void *arg0) {
    s32 v1;

    v1 = *(s32 *)((char *)arg0 + 0xCC);
    *(s32 *)((char *)v1 + 0xB0) = 2;
    if (func_801848AC(7, 0x14) != 0) {
        ((void (*)(void *))func_80181B04)(arg0);
    }
}



void func_80181CF0(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 2;
    }



extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_801849B8(s32*, s32);

void func_80181D00(void * arg0) {

    extern short D_801919AC;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_801849B8)((int)arg0, (int)&D_801919AC);
    }
}


extern void func_80181E0C();

void func_80181D50(void *a0) {

    extern s16 func_80184B44(void);
    extern void func_8012CAE4(void *a0);
    extern s32 func_801844BC(void *a0, void *a1);
    extern s32 func_801848AC(s32 arg0, s32 arg1);
    extern void func_801849B8(s32*, s32);
    extern s32 func_801788B8(s32 arg0, s32 arg1);
    extern s32 D_801919BC;
    extern void *D_801919D0[];
    extern short D_801919AC;

    void *v1;
    s32 sel;

    sel = ((s32 (*)(void))func_80184B44)();
    if (sel == 0) {
        if (func_801844BC(a0, &D_801919BC) == 0) {
            return;
        }
    } else if (sel == 1) {
        func_8012CAE4(a0);
        return;
    } else {
        if (func_801844BC(a0, D_801919D0) == 0) {
            return;
        }
    }
    if (func_801848AC(7, 0x14) != 0) {
        *(s16 *)((char *)a0 + 0x2) = 2;
    } else {
        *(s16 *)((char *)a0 + 0x2) = 1;
    }
    ((void (*)(s32, s32))func_801849B8)((int)a0, (int)&D_801919AC);
    v1 = *(void **)((char *)a0 + 0x68);
    *(s16 *)((char *)v1 + 0xC) = 0x7FFF;
    *(s32 *)((char *)a0 + 0xD4) = func_801788B8((s32)a0, (s32)&func_80181E0C);
}


extern void func_80172710(void);
extern s32 func_801845DC(void);
extern s32 func_80185F5C(void *);
extern s32 func_80178BF8(void);

#define func_80181E0C func_80181E0C_definition
s32 func_80181E0C(void *a0) __asm__("func_80181E0C");
s32 func_80181E0C(void *a0)
{
    void *s0 = a0;

    if (*(u16 *)(*(void **)(s0 + 0x64) + 2) == 2) {
        if (func_801845DC() != 0) {
            if (func_80185F5C(*(void **)(s0 + 0x64)) == 0) {
                *(u16 *)(*(void **)(s0 + 0x64) + 2) += 1;
                func_80178BF8();
                return (s32)func_80172710;
            }
        }
    }
    return 0;
}
#undef func_80181E0C



/* func_80181E90 — state-entry init (family exemplar, reach x11).
 * Sets the actor's state id (halfword @ +0x2) then runs the fixed
 * five-call entry chain. Sibling style copied from func_80180164
 * in the same TU (cookbook §71). */

extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32);
extern void func_80184BD4(s32, s32, s32, s32);


void func_80181E90(void *arg0) {

    extern short D_80191AB8;
    extern short D_801B9C0C;
    extern short D_801B6564;
    *(short *)((char *)arg0 + 0x2) = 2;
    func_8012E8E0((s32)arg0, (s32)&D_80191AB8);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801B9C0C);
    func_80184990((s32)arg0);
    func_80184BD4((s32)arg0, (s32)&D_801B6564, 0, 0x60);
}


extern s32 D_801B6578;
extern s32 D_801B9C0C;
extern void func_8012A828(s32, s32);
extern void func_8012E88C(s32);
extern void func_80184990(s32);
extern void func_80184BD4(s32, s32, s32, s32);

s32 func_80181F00(s32 a0)
{
    *(u16 *)(a0 + 2) = 3;
    func_8012E88C(a0);
    ((void (*)(s32, s32))func_8012A828)(a0, (s32)&(*(short *)&D_801B9C0C));
    func_80184990(a0);
    func_80184BD4(a0, (s32)&D_801B6578, 0, 0x40);
}


    extern void func_8012E88C(s32 a0);
    extern void func_8012A828(s32, s32);
    extern void func_80184990(s32 a0);
    extern void func_80184BD4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 D_801B9C0C;
    extern short D_801B6564;
    void func_80181F60(s32 a0) {
        *(u16 *)(a0 + 2) = 6;
        func_8012E88C(a0);
        ((void (*)(s32, s32))func_8012A828)(a0, (s32)&D_801B9C0C);
        func_80184990(a0);
        func_80184BD4(a0, (s32)&(*(s32 *)&D_801B6564), 1, 0x60);
    }


extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32);
extern void func_80184BD4(s32, s32, s32, s32);

void func_80181FC0(s32 a0)
{
    extern s32 D_80191B90[];
    extern s32 D_801B9C0C;
    extern s32 D_801B6790;

    *(u16 *)(a0 + 2) = 9;
    *(u16 *)(a0 + 0x34) = 0;
    func_8012E8E0(a0, (s32)&D_80191B90);
    func_8012E88C(a0);
    func_8012A828(a0, (s32)&D_801B9C0C);
    func_80184990(a0);
    func_80184BD4(a0, (s32)&D_801B6790, 1, 0x60);
}


extern s32 D_80191B90[];
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E8A8(u8 *a0);
extern void func_801849B0(void *a0);

void func_80182034(void *a0)
{
    *(s16 *)((char *)a0 + 2) = 10;
    *(s16 *)((char *)a0 + 0x34) = 0;
    func_8012E8E0((s32)a0, (s32)&D_80191B90);
    func_8012E8A8(a0);
    *(s16 *)((char *)a0 + 0x98) = 0;
    func_801849B0(a0);
}


extern s16 func_80184B44(void);
extern s32 func_80029504(void);
extern void func_8012CAE4(void *a0);
extern s32 func_801844BC(void *a0, void *a1);
extern s32 func_801848D0(u8 a0, u8 a1, u8 a2, u8 a3);
extern s32 func_801848AC(s32 arg0, s32 arg1);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E88C(s32 a0);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_80184990(s32 a0);
extern void func_8012E8A8(u8 *a0);
extern void func_801849B0(void *a0);
extern void func_80184BD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801849B8(s32 *a0, s32 a1);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern void func_80182318();

void func_80182084(void *a0) {

    extern s32   D_80191AC8[];
    extern s32 D_80191B90[];
    extern s16 D_801E4758;
    extern s32 D_801B9C0C;
    extern s32   D_801B6578;
    extern short D_80191AB8;

    s32 sel;

    ((void (*)(void))func_80184B44)();
    sel = func_80029504();

    if (((s32 (*)(void))func_80184B44)() == 1) {
        func_8012CAE4(a0);
        return;
    }

    if (func_801844BC(a0, D_80191AC8) == 0) {
        return;
    }

    if (((s32 (*)(void))func_80184B44)() == 3 && sel < 0x492) {
        if (func_801848D0(0xA, 0xF, 0x12, 0) != 0) {
            *(s16 *)((char *)a0 + 0x2) = 8;
            *(s16 *)((char *)a0 + 0x34) = 0;
            func_8012E8E0((s32)a0, (s32)&(*(s32 *)D_80191B90));
            func_8012E88C((s32)a0);
            func_8012A828((s32)a0, (s32)&(*(s32 *)&D_801E4758));
            func_80184990((s32)a0);
        } else {
            *(s16 *)((char *)a0 + 0x2) = 0xA;
            *(s16 *)((char *)a0 + 0x34) = 0;
            func_8012E8E0((s32)a0, (s32)&(*(s32 *)D_80191B90));
            func_8012E8A8((u8 *)a0);
            *(s16 *)((char *)a0 + 0x98) = 0;
            func_801849B0(a0);
        }
    } else if (func_801848AC(9, 0x11) != 0) {
        *(s16 *)((char *)a0 + 0x2) = 3;
        func_8012E88C((s32)a0);
        func_8012A828((s32)a0, (s32)&(*(short *)&D_801B9C0C));
        func_80184990((s32)a0);
        func_80184BD4((s32)a0, (s32)&D_801B6578, 0, 0x40);
    } else {
        *(s16 *)((char *)a0 + 0x2) = 1;
        ((void (*)(s32 *, s32))func_801849B8)((s32 *)a0, (s32)&D_80191AB8);
    }

    *(s16 *)(*(s32 *)((char *)a0 + 0x68) + 0xC) = 0x7FFF;
    *(s32 *)((char *)a0 + 0xD4) = func_801788B8((s32)a0, (s32)func_80182318);
}



extern void (*D_80191C18[])(void);

void func_80182234(void *a0) {
    D_80191C18[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80178CBC(s32 a0, s32 a1);
    extern short D_80191B18;
    void func_80182270(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 5;
        func_80178CBC((int)arg0, (int)&D_80191B18);
    }



extern s16 func_80184B44(void);

void func_8018229C(s32 a0) {

    extern s32 D_80191ADC[];
    s32 idx = ((s32 (*)(s32))func_80184B44)(a0);
    *(s32 *)(a0 + 0xE4) = D_80191ADC[idx];
}



extern s32 func_80029178(s32 arg);
    extern void func_80029124(s32, s32);
    s32 func_801822DC(void) {
        if ((func_80029178(0x115) & 0xFF) == 0) {
            ((void (*)(void *, s32))func_80029124)((void *)0x115, 1);
            return 1;
        }
        return 0;
    }


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

extern s32 func_80182318_def(void *a0) __asm__("func_80182318");

s32 func_80182318_def(void *a0)
{
    void *p;
    u16 st;

    p = *(void **)((s32)a0 + 0x64);
    st = *(u16 *)((s32)p + 0x2);
    switch (st) {
    case 3:
        if (func_8012BD14((s32)p) >= 0x4001) {
            return 0;
        }
        {
            void *p2 = *(void **)((s32)a0 + 0x64);
            u16 v = *(u16 *)((s32)p2 + 0x2);
            v = v + 1;
            *(u16 *)((s32)p2 + 0x2) = v;
        }
        break;
    case 8:
        if (func_8012BD14((s32)p) >= 0x4001) {
            return 0;
        }
        {
            void *p3 = *(void **)((s32)a0 + 0x64);
            u16 w = *(u16 *)((s32)p3 + 0x34);
            w = w + 1;
            *(u16 *)((s32)p3 + 0x34) = w;
        }
        break;
    default:
        return 0;
    }

    func_80178BF8();
    return (s32)func_80172710;
}



/* func_801823D0 — guarded dispatch: ask func_801848AC(9, 0x11); if it answers
 * NON-zero, run func_80181E90 on the incoming entity.  The entity pointer is
 * live across the jal, so it lands in $s0 and comes back out as $a0.
 * §71 sibling: func_80181B34 in this same TU is the identical shape.
 * §3-T4: target branch is `beqz $v0, ret` => the C condition is `!= 0`
 * (the sibling's is `bnez` => `== 0`; polarity is read off the opcode). */

extern s32 func_801848AC(s32 arg0, s32 arg1);
extern void func_80181E90(void *arg0);

void func_801823D0(void *arg0) {
    if (func_801848AC(9, 0x11) != 0) {
        func_80181E90(arg0);
    }
}


extern s32 func_80184CA4(s32 a0);
extern s32 func_80181F00();
void func_80182410(int param_1)
{
    if (((int (*)(void))func_80184CA4)() != 0) {
        ((void (*)(int))func_80181F00)(param_1);
    }
}


extern void func_80184BD4(s32, s32, s32, s32);
extern s32 func_801848AC(s32 arg0, s32 arg1);
extern s32 func_80184CA4(s32);

void func_80182448(s32 a0) {
    extern s32 D_801B6578;
    extern void func_80181F60(s32);

    if (func_80184CA4(a0) == 0) {
        return;
    }

    if (func_801848AC(9, 0x11) == 0) {
        ((void (*)(void *))func_80181F60)((void *)a0);
    } else {
        func_80184BD4(a0, (s32)&D_801B6578, 0, 0x40);
    }
}


extern int func_80178970(void);
extern s32 D_801B9C0C;
extern void func_8012A828(s32, s32);
extern void func_80178D18(void);

void func_801824AC(arg0)
void * arg0;
{

    extern s32 D_801B9C0C;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(short *)((char *)arg0 + 0x2) = 3;
        ((void (*)(s32, s32))func_8012A828)((int)arg0, (int)&(*(short *)&D_801B9C0C));
    }
}


extern s32 func_80184CA4(s32 a0);
extern short D_80191AB8;
extern void func_801849B8(s32*, s32);

void func_801824FC(s32 a0)
{
    if (func_80184CA4(a0) != 0) {
        *(s16 *)(a0 + 0x2) = 1;
        ((void (*)(s32 *, s32 *))func_801849B8)((s32*)a0, &D_80191AB8);
    }
}


extern void func_80029124(s32 arg0, s32 arg1);
    void func_80182540(void) {
        func_80029124(0x115, 1);
    }


#include "common.h"

extern s32 D_80191BA8;
extern s32 D_80191B90[];
extern s16 D_801E4758;
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_801848D0(u8 a0, u8 a1, u8 a2, u8 a3);
extern void func_80178CBC(s32 arg0, s32 arg1);
extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32);
extern void func_80181FC0(s32 a0);

void func_80182564(s32 a0) {
    u16 state = *(u16 *)(a0 + 0x34);
    switch (state) {
    case 0: {
        s32 r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), 0xC00, 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        if (func_801848D0(0xA, 0xF, 0x12, 0) == 0) {
            func_80181FC0(a0);
        }
        break;
    }
    case 1:
        func_80178CBC(a0, (s32)&D_80191BA8);
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        break;
    case 2: {
        if (((s32 (*)(s32))func_80178970)(a0) == 0) {
            break;
        }
        ((void (*)(s32))func_80178D18)(a0);
        *(u16 *)(a0 + 0x2) = 8;
        *(u16 *)(a0 + 0x34) = 0;
        func_8012E8E0(a0, (s32)&D_80191B90);
        func_8012E88C(a0);
        func_8012A828(a0, (s32)&D_801E4758);
        func_80184990(a0);
        break;
    }
    }
}


extern s32 func_80184CA4(s32);
extern void func_80184BD4(s32, s32, s32, s32);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(s32, s32);
extern void func_80184990(s32);
extern s32 D_801B6790;
extern s32 D_80191B90[];
extern s16 D_801E4758;

void func_8018268C(void *arg0) {
    s32 v0;
    u16 v1;

    v1 = *(u16 *)((u8 *)arg0 + 0x34);
    switch (v1) {
    case 0:
        v0 = func_80184CA4((s32)arg0);
        if (v0 != 0) {
            *(u16 *)((u8 *)arg0 + 0x34) = *(u16 *)((u8 *)arg0 + 0x34) + 1;
            func_80184BD4((s32)arg0, (s32)&D_801B6790, 0, 0x60);
        }
        break;
    case 1:
        v0 = func_80184CA4((s32)arg0);
        if (v0 != 0) {
            *(u16 *)((u8 *)arg0 + 0x2) = 8;
            *(u16 *)((u8 *)arg0 + 0x34) = 0;
            func_8012E8E0((s32)arg0, (s32)&D_80191B90);
            func_8012E88C((s32)arg0);
            func_8012A828((s32)arg0, (s32)&D_801E4758);
            func_80184990((s32)arg0);
        }
        break;
    }
}


extern s32 func_80184CA4(s32 a0);
extern void func_80184BD4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80182034(void *a0);
extern short D_801B6778;

void func_80182750(s32 arg0) {
    u16 state;

    state = *(u16 *)(arg0 + 0x34);
    switch (state) {
    case 0:
        if (((s32 (*)(s32))func_80184CA4)(arg0) != 0) {
            *(u16 *)(arg0 + 0x34) += 1;
            ((void (*)(s32, s32, s32, s32))func_80184BD4)(arg0, (s32)&D_801B6778, 1, 0x60);
        }
        break;
    case 1:
        if (((s32 (*)(s32))func_80184CA4)(arg0) != 0) {
            ((void (*)(s32))func_80182034)(arg0);
        }
        break;
    }
}


INCLUDE_ASM("asm/ov_SC05_017/nonmatchings/ov_SC05_017_jr_801808D4", func_801827E4);

extern void func_801849B8(s32 *a0, s32 a1);
    extern short D_80191C44;
    void func_80182874(short *param_1) {
        *(short *)((char *)param_1 + 2) = 1;
        ((void (*)(int, int))func_801849B8)((int)param_1, &D_80191C44);
    }


extern short D_801B9964;
    extern void func_8012A828(s32, s32);
extern void func_8012E88C(s32);
extern void func_80184990(s32);

void func_801828A0(arg0)
void *arg0;
{
    extern short D_801B9964;
    extern void func_8012E88C(s32);
    extern void func_8012A828(s32, s32);
    extern void func_80184990(s32);

    *(short *)((char *)arg0 + 0x2) = 0x2;
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801B9964);
    func_80184990((s32)arg0);
    *(short *)((char *)arg0 + 0x34) = 0;
}


