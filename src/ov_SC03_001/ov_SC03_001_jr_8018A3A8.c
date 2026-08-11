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
extern u8 D_8018FA44;
extern u8 D_8018F9B4;
extern u8 D_8018F990;
extern u8 D_8018F96C;
extern u8 D_8018FA20;
extern u8 D_8018F9FC;
extern u8 D_8018F9D8;
extern u8 D_8018F948;
extern void func_80145934(void);
extern u8 D_8018FAD4;
extern u8 D_8018FAB0;
extern u8 D_8018FA8C;
extern u8 D_8018FA68;
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
extern unsigned char D_8018EECC[];
extern unsigned char D_8018EEFC[];
extern unsigned char D_8018EF4C[];
extern unsigned char D_8018EF7C[];
extern unsigned char D_8018EFAC[];
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
extern void (*D_8018EFFC[])(void *);
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
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_8018F0C4[];
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
extern u8 D_8018F14C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018F154;
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
extern int D_801ED4D8;
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
extern s32 D_801ED4DC;
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
extern s32 D_8018F184;
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
extern void (*D_8018F22C[])(void);
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
extern void (*D_8018F250[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018F240;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018F264[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018F270[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018F280[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018F298[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018F288;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018F2AC[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018F2C8[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018F2B8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018F2DC[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018F2F0[])(void);
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
extern s32 D_8018F304;
extern void (*D_8018F32C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018F30C;
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
extern int (*D_8018F378[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018F37C[])(void);
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
extern unsigned short D_8018F7E0[];
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
extern void (*D_8018F7F0[])(void);
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
extern int D_801ED510;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018F818[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018F7F8;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018F808;
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
extern void (*D_8018F858[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018F860[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018F82C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018F86C[])(void);
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
extern u8 D_8018F83C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801ED518;
extern s32 D_801ED524;
extern s32 D_801ED528;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018F8A8[])(s32 *);
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
extern s32 D_8018F87C[];
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
extern s32 D_801ED520;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018FAF8[])(void);
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
extern char D_8018F918[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018FB9C[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018FCF0[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018FB0C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018FCF8[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018FB1C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018FB3C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018FD00[])(void);
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
extern void (*D_8018FD28[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018FD34[])(void);
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
extern void (*D_8018FBA8[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018FDD8;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018EEBC[];
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
extern unsigned char D_8018FDEC[];
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
extern s8 D_8018FE28[];
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
extern u16 D_8018FE70;
extern u16 D_8018FE72;
extern u16 D_8018FE74;
extern s32 D_8018FE78;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018FE80;
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
extern int D_8018FB8C;
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
extern unsigned int D_8018FF04[];
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
extern void (*D_8018FFB4[])(void);
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
extern u16 D_8018FFE4[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80190048;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801ED530[];
extern void func_8016216C(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8019006C[])(void);
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
extern int D_801ED588[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_801900B4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801900A4;
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
extern char D_801EC888[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801900BC[])(void);
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
extern void (*D_80190110[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801900D8;
extern s16 D_8019010C;
extern s16 D_8019010A;
extern s16 D_80190108;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8019011C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801ED5E8;
extern u8 D_801ED5E9;
extern u8 D_801ED5EA;
extern u8 D_801ED5EB;
extern u8 D_801ED5EC;
extern u8 D_801ED5ED;
extern u8 D_801ED5EE;
extern u8 D_801ED5EF;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8019012C[])(void);
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
extern s32 D_801ED628;
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
extern void (*D_80190170[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801901EC[];
extern s32 D_8019020C[];
extern u8 D_80190288[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801902A8[];
extern u8 D_801902C8[];
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
extern void (*D_80190364[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801903E0[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801EC898;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801903EC[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801903F4[])(void);
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
extern void (*D_801904BC[])(void);
extern void func_80166618(void *a0);
extern void (*D_801904CC[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801904DC[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801904E8[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80190448[];
extern u8   D_8019045C[];
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
extern void (*D_80190500[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80190508[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80190510[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80190518[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80190520[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80190528[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80190530[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801905E4[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801905EC[])(void);
extern void func_80169F00(void *a0);
extern char D_8019059C[];
extern char D_8019055C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80190624[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80190630[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80190678[])(void);
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
extern void (*D_801906F4[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801ED948;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801906E8[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8019072C[];
extern unsigned short D_80190734[];
extern unsigned short D_8019073C[];
extern unsigned char D_801ED950[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801ED948;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80190744[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801EDA84;
extern M2C_UNK D_801EDA88;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801EDA10;
extern void (*D_80190774[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801EDA8C[];
extern u8 D_801EDA94[];
extern u8 D_801EDA44[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8019077C[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80190798[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801907A0[])(void);
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
extern void (*D_80190808[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801907AC;
extern u8 D_801907B8;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8019083C[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80190844[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80190898[])(void);
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
extern u16 D_801908CC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801908BC[];
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
extern s32 D_801908E8;
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
extern void func_80175414(s32);
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
extern void (*D_80190960[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80190968[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80190970[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80190978[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80190980[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80190988[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80190994[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801909A0[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801909AC[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801909BC[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_801909CC[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_801909D4[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_801909DC[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_801909E4[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_801909EC[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_801909F4[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_801909FC[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80190A04[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80190A0C[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80190A14[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80190A1C[])(void);
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
extern void (*D_80190A24[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80190A2C[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80190A34[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80190A3C[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80190A44[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80190A4C[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80190A54[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80190A5C[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80190A64[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80190A6C[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80190A74[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80190A7C[])(void);
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
extern void (*D_80190AC0[])(void);
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
extern M2C_UNK D_80190A84;
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
extern void (*D_80190AF0[])(void);
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
extern void (*D_80190B2C[])(void);
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
extern void (*D_80190B84[])();
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
extern void (*D_80190B94[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80190B9C[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80190D04[])();
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
extern void (*D_80190D10[])();
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
extern M2C_UNK D_801ECAE0;
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
extern s16 D_801EF3F0;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern short D_801EF464;
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
extern s32 D_801EE5F4;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801EE61C;
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
extern s16 D_801EE5D8;
extern s32 func_8017A3B0(void);
extern short D_801EE614;
extern short D_801EE610;
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
extern s16 D_801EF3A8;
extern s16 D_801EF3AA;
extern s16 D_801EF3B4;
extern void func_8017AE2C(s32 param_1);
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801EE5DC;
extern u16 D_801EE65C;
extern u16 D_801EE65E;
extern u16 D_801EE660;
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
extern s16 D_801EE654;
extern s16 D_801EE656;
extern s16 D_801EE658;
extern s16 D_801EE64C;
extern s16 D_801EE64E;
extern s16 D_801EE650;
extern void func_8017B7A8(void);
extern s16 D_801EE66C;
extern s16 D_801EE66E;
extern s16 D_801EE670;
extern s16 D_801EE674;
extern s16 D_801EE676;
extern s16 D_801EE678;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801EE664;
extern short D_801EE666;
extern short D_801EE668;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801EE5FC;
extern SV4 D_801EE604;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801EE624[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801EE620)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80190EEC[])(void);
extern void func_8017BE60(void *a0);
extern void (*D_80190F8C[])(void);
extern void func_8017BE9C(void *a0);
extern void (*D_80190F94[])(void);
extern void func_8017BED8(void *a0);
extern void (*D_80190F9C[])(void);
extern void func_8017BF14(void *a0);
extern u8 D_801EE680[];
extern u8 *func_8012913C(s32 a0);
extern s32 func_8012C750(s32 a0);
extern void func_8017BF50(s32 a0);
extern s16 D_801EE880;
extern void func_8017C094(void);
extern u8 D_80190EF8[];
extern void func_8017C100(s32 param_1);
extern void func_8017C1AC(s32 param_1);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32, s32);
extern void func_8012B260(u8 *a0);
extern u8 D_80190F74[];
extern u8 D_80190F7C[];
extern void func_8017C1EC(s32 a0);
extern void func_8017C2B0(s32 a0);
extern void (*D_80190FBC[])(void);
extern void func_8017C338(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_8017C374(s32 param_1);
extern void func_8017C538(u8 *p);
extern void (*D_80190FC4[])(void);
extern void func_8017C5CC(void *a0);
extern u8 D_80190FB0;
extern void func_8017C608(s32 a0);
extern void func_8017C6AC(int a0);
extern void func_8017C710(s32 arg0);
extern void func_8017DC48(void);
extern void (*D_8019106C[])(void);
extern void func_8017DDEC(void *a0);
extern void func_8001C214(s32, s32);
extern u32 D_8019105C;
extern void func_8017DE28(s32 arg0);
extern void func_8017DEA4(void);
extern void (*D_801910A4[])(void);
extern void func_8017DEAC(void *a0);
extern void func_8017E204(void *arg0);
extern s32 func_8012AD50(void *arg0);
extern void func_8017DEE8(void *arg0);
extern u8 D_80078EB1;
extern u8 D_80078E78[];
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8017E1B4(void *a0);
extern void func_8017E2C0(void *arg0);
extern void func_8017DF78(void *arg0);
extern void aF8017E1B4();
extern void func_80017714(void *);
extern u32 D_801EE918;
extern u16 D_801910AC[];
extern u16 D_801EE91C[];
extern s32 D_801910CC;
extern void func_8017E408(void);
extern void func_8017E824(void *arg0);
extern s32 func_8017E494(s32 param_1);
extern s32 func_8017E4E4(void);
extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8001BFD0(void);
extern s32 func_8017E578(s32 a0);
extern void func_800D1EBC(void);
extern void func_8017E628(void);
extern s32 func_8017E648(void *a0);
extern void (*D_801910EC[])(void);
extern void func_8017E720(void *a0);
extern void (*D_801910F4[])(void);
extern void func_8017E75C(void *a0);
extern void (*D_80191100[])(void);
extern void func_8017E798(void *a0);
extern void (*D_8019110C[])(void);
extern void func_8017E7D4(void *a0);
extern s32 D_80127050;
extern void func_8017E810(void);
extern void (*D_801913C0[])(void);
extern void func_8017E824(void *a0);
extern void func_8017E860(s32 *a0);
extern void func_8017E874(void *a0);
extern void (*D_801913C8[])(void);
extern void func_8017E8AC(void *a0);
extern void func_8017E8E8(u8 *a0);
extern void func_8017E8FC(void);
extern void func_8012A094(s32 a0);
extern void func_8017E9E0(void *a0);
extern void func_8017E91C(void);
extern void (*D_801913D0[])(void);
extern void func_8017EA50(u8 *a0);
extern void func_8017EA58(void *a0, u8 *a1);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_8017EB98(s32 param_1);
extern void func_80187778(s32 *a0, s32 a1);
extern void func_8017ED8C(void *a0);
extern void (*D_801914A8[])(void);
extern void func_8017EEA8(void *a0);
extern void func_80178CBC(s32*, s32);
extern void func_8017EEE4(void * arg0);
extern s32 func_8017EF10(void);
extern s32 func_801877C0(s32);
extern s32 func_80187904(void);
extern s32 func_8018766C(s32 arg0, s32 arg1);
extern void func_80187778(s32*, s32);
extern void func_8017F058(void *a0);
extern void func_8017F0EC(void * arg0);
extern void func_8012E32C(void);
extern void func_8017F750(void *, s32);
extern s32 RotNclip4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern s32 RotTransPers4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern void *func_80010A08(s32);
extern s32 AddPrim(s32, void *);
extern void func_8012E28C(s32, s32);
extern void func_8017F368(u16 *a0, s32 a1);
extern void (*D_801918FC[])(void);
extern void func_8017F7C8(void *a0);
extern void (*D_80191928[])(void);
extern void func_8017F920(void *a0);
extern void (*D_80191930[])(void);
extern void func_8017F95C(void *a0);
extern void (*D_80191940[])(void);
extern void func_8017F998(void *a0);
extern void (*D_80191950[])(void);
extern void func_8017F9D4(void *a0);
extern void func_8017FA10(void);
extern void (*D_80191960[])(void);
extern void func_8017FBC4(void *a0);
extern s32 D_801915FC;
extern s32 D_801EEAE8;
extern void func_8017F1F0(s32 arg0, s32 arg1);
extern void func_8017FD5C(void);
extern s32 D_80191634;
extern void func_8017FD90(void);
extern s32 D_8019166C;
extern void func_8017FDC4(void);
extern s32 D_80191694;
extern void func_8017FDF8(void);
extern s32 D_801916CC;
extern void func_8017FE2C(void);
extern s32 D_80191744;
extern void func_8017FED4(void);
extern s32 func_8017FF08(void);
extern s32 D_8019179C;
extern void func_8017FF54(void);
extern s32 D_801917EC;
extern void func_8017FF88(void);
extern s32 D_8019184C;
extern void func_8017FFBC(void);
extern s32 func_8017FFF0(void);
extern s32 D_80191894;
extern void func_8018003C(void);
extern s32 func_80180070(void);
extern void func_8012B414(int a0);
extern void func_801803DC(s32 arg0);
extern void func_801805EC(void *a0);
extern void (*D_80191978[])(void);
extern void func_801805F8(void *a0);
extern s32 func_8012E57C(s32 a0, s32 a1);
extern void func_80180728(void *a0);
extern void func_80180770(void *a0);
extern void (*D_8019198C[])(void);
extern void func_8018077C(void *a0);
extern void func_801808F0(void *a0);
extern void (*D_801919A0[])(void);
extern void func_801808FC(void *a0);
extern void func_80180A58(short *a0);
extern void (*D_80191B0C[])(void);
extern void func_80180A88(void *a0);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_80187750(s32);
extern void func_80187994(s32, s32, s32, s32);
extern void aF80180B5C();
extern void func_8012A828(s32 a0, s32 a1);
extern void func_80180C3C(void * arg0);
extern s32 func_801877C0(s32 a0);
extern void func_80180D5C(s32 a0);
extern s32 func_80180D9C(void);
extern s32 func_80180AC4(s32 a0);
extern s32 func_80180B5C(void *a0);
extern void func_80180DD8(int param_1);
extern s32 func_8012BD14(s32 a0);
extern s32 func_80181078(void *a0);
extern void func_801810EC(void *a0);
extern void (*D_80191B30[])(void);
extern void func_801810F8(void *a0);
extern void func_8018126C(void * arg0);
extern void func_80181298(short *param_1);
extern void (*D_80191C08[])(void);
extern void func_801812C4(void *a0);
extern int func_80181374(void);
extern void func_80181394(void);
extern void func_80178CBC(s32 *a0, s32 a1);
extern void func_801813C0(short *a0);
extern void (*D_80191C20[])(void);
extern void func_801817C4(void *a0);
extern void func_801818E0(short *a0);
extern void (*D_80191C90[])(void);
extern void func_8018190C(void *a0);
extern void func_80181988(void *a0);
extern void func_801819A0(s32 a0);
extern s32 func_80181948(s32 a0);
extern void func_801818E0(short*);
extern void func_801819E0(int param_1);
extern s32 func_8018739C(void);
extern s32 func_80188D1C(void *);
extern s32 func_80178BF8(void);
extern s32 func_80181BC0(void *a0);
extern void func_8012E88C(s32 a0);
extern void func_80187750(s32 a0);
extern void func_80181CAC(void *a0);
extern void func_80181D8C(short *a0);
extern void (*D_80191D3C[])(void);
extern void func_80181ED4(void *a0);
extern void func_80181F74(short *a0);
extern void func_80181FA0(s32 a0);
extern s32 func_80181FE0(void *a0);
extern s32 func_80178BF8();   /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2541) */
extern s32 func_80182058(void *a0);
extern s32 func_801886A0(s32 a0);
extern s32 func_80187A64(s32 a0);
extern void func_801821C0(void *a0);
extern void func_80181D04(void *arg0);
extern void func_80182254(void *arg0);
extern void func_80182294(void *a0);
extern void func_80182450(short *param);
extern void func_8018260C(short *a0);
extern void func_8018268C(void * arg0);
extern void (*D_80191E0C[])(void);
extern void func_80182824(void *a0);
extern s32 D_801DD064;
extern s32 D_801D6014;
extern void func_80182898(void);
extern s32 D_801EEAF8;
extern void func_801828B0(void);
extern void func_80178CBC(s32 *, s32);
extern void func_801828C8(void *arg0);
extern void func_80182928(s32 a0);
extern void func_801824DC(void *arg0);
extern void func_80182968(void *arg0);
extern void func_801825A8(void *arg0);
extern void func_80182A34(void *arg0);
extern void func_80187994(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8018260C(short*);
extern void func_80182AEC(void *arg0);
extern void func_80182638(void *arg0);
extern void func_80182B78(void *arg0);
extern void func_801826B8(void *arg0);
extern void func_80182CC4(void *arg0);
extern s32 func_80182DFC(void *a0);
extern void func_80182E70(void *arg0);
extern void func_80182EE4(void *a0);
extern void func_801831F0(short *a0);
extern void (*D_801922F0[])(void);
extern void func_8018333C(void *a0);
extern void func_801833DC(short *a0);
extern void func_80183408(s32 a0);
extern s32 func_80183448(void *a0);
extern s32 func_801834C0(void *a0);
extern void func_80183628(void *a0);
extern void func_80183168(s32 *a0);
extern void func_801836BC(s32 *a0);
extern void func_80183708(void *a0);
extern void func_801831F0(short*);
extern void func_80183778(void *arg0);
extern void func_801838BC(short *a0);
extern void func_80183948(void *arg0);
extern void func_801839BC(void *a0);
extern void (*D_80192418[])(void);
extern void func_80183A88(void *a0);
extern s32 D_801DD950;
extern s32 D_801DAAAC;
extern void func_80183AFC(void);
extern void func_80183B14(void *arg0);
extern void func_80183B74(s32 a0);
extern s32 func_80183BB4(void);
extern void func_80183BF0(void *arg0);
extern void func_80183A14(void *arg0);
extern void func_80183CC8(void *arg0);
extern void func_80183D08(void *a0);
extern s32 func_80183EE4(void *a0);
extern void func_80183F58(void *arg0);
extern void func_801840B8(void * arg0);
extern void (*D_80192510[])(void);
extern void func_80184210(void *a0);
extern void func_8018424C(short *a0);
extern void func_80184278(void * arg0);
extern void func_801842A4(short *param);
extern void func_801842D0(s32 a0);
extern void func_80184310(s32 a0);
extern void func_8018444C(void *arg0);
extern void func_8018451C(void * arg0);
extern void (*D_80192544[])(void);
extern void func_80184748(void *a0);
extern void func_80184784(void *a0);
extern void func_801847D0(void *arg0);
extern void (*D_80192624[])(void);
extern void func_80184900(void *a0);
extern void func_8018493C(short *param);
extern s32 func_801849E0(void);
extern s32 func_80187A64(s32);
extern void func_80184A8C(s32 arg0);
extern s32 func_80184CF0(void *a0);
extern void func_80184D64(short *param_1);
extern void (*D_80192828[])(void);
extern void func_801850A0(void *a0);
extern void func_801850DC(s32 a0);
extern void func_8018511C(s32 a0);
extern void func_8018515C(s32 a0);
extern s32 func_8018519C(void);
extern void func_801851D8(short *a0);
extern short D_80192740;
extern void func_80185208(void *a0);
extern void func_80185238(short *a0);
extern short D_801927B8;
extern void func_80185268(short *a0);
extern void func_80184F18(s32 *a0);
extern void func_80185298(s32 *a0);
extern void func_80184D64(short*);
extern void func_80185334(s32 *a0);
extern void func_80184D90(void *arg0);
extern void func_801853D0(void *arg0);
extern void func_80185874(short *param_1);
extern void func_801858A0(short *param_1);
extern void func_801858CC(short *param_1);
extern void func_801858F8(short *param_1);
extern void func_80185924(short *a0);
extern void (*D_801928D8[])(void);
extern void func_80185C60(void *a0);
extern void (*D_80192968[])(void);
extern void func_80185CD8(void *a0);
extern s32 func_80128C98(s32 arg);
extern void func_80185D14(void *a0);
extern void func_80185D50(void *a0);
extern void func_80185D8C(void *a0);
extern void func_80185F9C(void);
extern void func_80185FA4(void *a0);
extern void func_80185FB4(void *a0);
extern void func_801EF624(void *a0);
extern void func_80186064(void *a0);
extern void func_801860A0(short *param_1);
extern void func_80186288(short *param_1);
extern void (*D_801929D4[])(void);
extern void func_801862B4(void *a0);
extern void func_801862F0(void * arg0);
extern void func_80186288(short*);
extern void func_8018640C(void *arg0);
extern void func_80186498(void * arg0);
extern s32 func_80186568(void *a0);
extern void func_801865E0(short *a0);
extern void (*D_80192A50[])(void);
extern void func_8018660C(void *a0);
extern void func_80186648(short *param);
extern void func_80186674(s32 a0);
extern void func_801865E0(short*);
extern void func_801866B4(s32 *a0);
extern void func_80186758(void * arg0);
extern void (*D_80192AE8[])(void);
extern void func_801868E0(void *a0);
extern void (*D_80192B10[])(void);
extern void func_8018691C(void *a0);
extern short D_80192AC8;
extern void func_80186958(short *param);
extern void func_801869C8(s32 arg0);
extern void func_80186A6C(void);
extern void func_80186A74(void);
extern void func_80186A7C(void);
extern void func_80186A84(void);
extern s32 func_80186D18(void);
extern void func_8012B2CC(s32 arg);
extern void func_80186D7C(void *arg0);
extern void func_80186F88(void);
extern void func_80186DDC(void *arg0);
extern void (*D_801C063C[])(void);
extern void func_80186F4C(void *a0);
extern s32 func_80178BF8();      /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2539) */
extern void func_80172710(void); /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2231) */
extern s32 aF8018CB18();
extern void func_80187004(void *a0);
extern s32 func_80187074(void);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8018708C(void);
extern s32 func_8012BEE8(s32 a0);
extern void func_80186DAC(void *a0);
extern void func_801871E4(void *a0);
extern void func_8018724C(void);
extern void func_80187254(void);
extern void func_8018725C(void *a0);
extern void func_8018726C(void *a0);
extern s32 func_8018727C(void *a0, void *a1);
extern void func_8012A828(s32 arg0, s32 arg1);
extern void func_80187318(void *a0);
extern void func_80187344(void *a0);
extern void func_80187370(void *a0);
extern s32 func_801875C4(s32 arg0);
extern s32 func_80187420(s32 a0);
extern s32 func_80187420(s32 arg);
extern void func_80187584(void *a0);
extern void func_80187550(void *a0);
extern short D_800BA2BA;
extern void (*D_801C0B00[])(void);
extern void func_801875EC(void *a0);
extern void func_80187628(void);
extern void func_80187630(void *a0, s32 a1, s32 a2);
extern s32 func_80187690(u8 a0, u8 a1, u8 a2, u8 a3);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_801876E8(void *a0, s32 a1);
extern void func_80187770(void *a0);
extern void func_8012E8A8(u8 *a0);
extern s32 aF801877C0();
extern s32 func_8018781C(void);
extern s32 func_80187890(void);
extern void func_80187960(void);
extern void func_8012B200(u8 *a0);
extern s32 func_80187C2C(s32 a0);
extern void (*D_801C0B20[])(void);
extern void func_80187C74(void *a0);
extern void func_80187CB0(void);
extern void func_80187CB8(void);
extern void func_80187CC0(void);
extern void func_80187CC8(void);
extern void func_80187CD0(void);
extern void func_80187CD8(void *a0);
extern void func_80187D1C(void);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_80187D24(s32 a0);
extern void func_80188438(s32 a0);
extern void func_801883C4(s32 a0);
extern void func_80188498(s32 a0);
extern void func_8018835C(s32 a0);
extern void func_80187DAC(s32 a0);
extern void func_8001C97C(s32 a0);
extern void *func_8018872C(void *a0);
extern void func_80187F84(s32 a0);
extern void func_80188830(void *a0);
extern void func_80188124(void *a0);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern s32 func_801889AC(void);
extern void func_801881A0(s32 a0);
extern void func_8018826C(void);
extern void func_8018828C(s32 a0);
extern void func_80188518(s32 a0, s32 a1);
extern void func_80188AEC(s32 a0, s32 a1);
extern void func_80188570(s32 a0);
extern void func_801885D0(s32 a0);
extern void func_80188618(s32 a0);
extern void func_80188668(s32 a0);
extern s32 func_801887D0(void *a0);
extern s32 func_80188D68(void *a0);
extern void * func_8018872C(void *a0);
extern void func_801889E0(void *a0);
extern void aF80185EEC();
extern void func_80188A14(void *a0, s32 a1, s32 a2);
extern void func_80188A78(s32 a0, s32 a1, s32 a2);
extern void (*D_801C0E1C[])(void);
extern void func_80188B44(void *a0);
extern void func_80188B80(void *a0);
extern void func_80188BFC(void *a0);
extern s32 func_80188E74(s32 a0);
extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CB64(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_8012F214(s32 arg0, s32 arg1, s32 arg2);
extern void func_80188ED0(void);
extern s16 D_801EEB10;
extern s32 func_80188F10(void);
extern void func_80029444(void);
extern void func_801754A8(void);
extern void func_80141C04(void);
extern void func_80188F6C(void);
extern void func_80189030(void);
/* ==== end §8b carried decl layer ==== */


extern s16 D_800B9A02;
extern s32 D_801151D0;
extern s16 D_80115126;
extern u8 D_80115138[];
extern u8 D_80115148[];

extern u16 D_801EF1EC;
extern s16 D_801EF1F0;
extern s16 D_801EF274;
extern s16 D_801EF278;
extern s16 D_801EF27C;
extern s16 D_801EF280;
extern s16 D_801EF284;
extern s16 D_801EF288;
extern s16 D_801EF28C;
extern s32 D_801EF258;
extern s16 D_801EEB10;

extern s32 D_801F4334;
extern s32 D_801F0D18;
extern s32 D_801F1374;
extern u8 D_801C1884[];
extern s32 D_801C184C[];
extern s32 resLoad_lastId;

extern s32 rand(void);
extern int func_8001AAA0(void);
extern s32 func_800149E0(s32 a0);
extern void func_80029124(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80137B80(void);
extern s32 func_801376E8(s32 a0, s32 a1);
extern void func_80139954(void);
extern void func_80139A68(s32 a0, u16 a1);
extern s32 func_801399F0(s32 a0);
extern s16 func_8014168C(s16 a0);
extern s32 func_8017ADE8(s32 a0);
extern void func_8018B238(void);
extern s32 func_8018C000(s32 a0, s16 a1);
extern s16 func_8018C914(s32 a0);

void func_8018A3A8(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_801151C8[];
    extern s16 D_801EF1E8;
    extern u8 D_800B9A15;
    extern u16 D_80115112;
    extern s32 D_801EF1E0;
    extern s32 D_80115130;
    extern s32 D_801C17F0;
    extern s16 D_801EF270;
    extern s32 D_801EF1E4;
    extern u16 D_8011511A;
    s32 s0;
    s32 pad[2];
    (void)&pad;

    D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];

    if (D_80115126 == 4) {
        if (func_801399F0(D_801EF1E4) != 0) {
            if (D_80115148[0] == 0) {
                if (D_801EF1E0 == (s32)&D_801F4334) {
                    D_801EF1E8 = 0x60;
                    D_801EF1F0 = 0;
                    D_801EF1EC = 0;
                    D_801EF1E0 = 0;
                    if (resLoad_lastId == 0x16) {
                        D_801EF270 = 1;
                        ((s32 (*)(s32))func_8001AAA0)(0x35);
                    } else {
                        D_801EF270 = 0;
                    }
                    D_80115112 = 6;
                } else {
                    D_80115112 = D_80115112 - 1;
                }
            } else {
                D_801EF1E0 = 0;
                func_8017ADE8(0x12);
                func_8002D4C8(0x46F, 0);
                D_8011511A = 0;
                D_80115112 = D_80115112 - 1;
            }

            if (D_801EF1E0 != 0) {
                D_80115130 = D_801EF1E0;
                func_80139954();
                D_801EF1E4 = func_801376E8(D_801EF1E0, (s32)&D_801C17F0);
            }
        }
    } else if (D_80115126 == 5) {
        if (D_801EF1E0 != 0) {
            if ((D_801EF28C = func_801399F0(D_801EF1E4)) != 0) {
                D_801EF1E0 = 0;
            }
        } else if ((func_800149E0(0) & 0x50) != 0 || D_801EF28C > 0) {
            switch (D_801EF274) {
            case 0:
                D_801EF274 = -1;
                break;

            case 1:
                if (D_801EF28C < 0) {
                    D_801EF1E0 = (s32)&D_801F0D18;
                } else if (D_801EF28C == 1) {
                    u16 *p = &D_80115112;
                    D_801EEB10 = 1;
                    func_80139954();
                    D_800B9A15 = 0;
                    *p = *p + 1;
                } else {
                    D_801EF274 = -2;
                }
                break;

            case 2:
                D_801EF288 = 0;
                D_801EF278 = 0;
                /* fallthrough */
            case 5:
            case 6:
                D_801EF274 = ((u16)D_801EF274 + 1) | 0x100;
                break;

            case 3:
                if (D_801EF28C == 1) {
                    D_801EF274 = (u16)D_801EF274 + 1;
                    if (D_801EF288 == 0) {
                        if (func_8018C914(-0xA) != 0) {
                            func_8002D4C8(0x472, 0);
                            D_801EF274 = 0x10C;
                            break;
                        }
                        func_8002D4C8(0x5EE, 0);
                        D_801EF278 = 0;
                        D_801EF288 = 0;
                        D_801EF27C = rand() % 9 + 3;
                        func_80139A68(D_801EF27C, 0);
                    } else {
                        func_80139A68(D_801EF27C, 0);
                        D_801EF274 = 0x106;
                        break;
                    }
                }
                D_801EF274 = ((u16)D_801EF274 + 1) | 0x100;
                break;

            case 4:
            case 12:
            case 13:
                if (D_801EF278 != 0) {
                    func_8018C914(D_801EF278);
                    func_8002D4C8(0x5EE, 0);
                }
                D_801EF274 = -1;
                break;

            case 7:
                D_801EF284 = (u16)D_801EF28C - 1;
                D_801EF280 = rand() % 13 + 1;
                func_80139A68(D_801EF280, 0);
                D_801EF274 = ((u16)D_801EF274 + 1) | 0x100;
                break;

            case 8:
            case 9:
                if (D_801EF27C == D_801EF280) {
                    D_801EF280 = rand() % 13 + 1;
                    func_80139A68(D_801EF280, 0);
                    D_801EF274 = 0x109;
                    break;
                }
                if (D_801EF284 == 0 ? D_801EF27C < D_801EF280 : D_801EF280 < D_801EF27C) {
                    if (D_801EF278 == 0) {
                        D_801EF278 = 0xA;
                    }
                    D_801EF278 = (u16)D_801EF278 * 2;
                    func_80139A68(D_801EF278, 0);
                    func_8002D4C8(0x5EE, 0);
                    if (D_801EF278 >= 0x2800) {
                        func_80029124(0x11A, 1);
                        D_801EF274 = 0x10D;
                        *(s32 *)(D_801EF258 + 4) = (s32)&D_801F1374;
                    } else {
                        s32 r;
                        D_801EF288 = (u16)D_801EF288 + 1;
                        s0 = D_801C1884[D_801EF288];
                        r = rand() % (9 - s0 * 2);
                        s0 = s0 + 3;
                        D_801EF27C = r + s0;
                        func_80139A68(D_801EF278, 0);
                        D_801EF274 = 0x10A;
                    }
                } else {
                    D_801EF278 = 0;
                    D_801EF288 = 0;
                    D_801EF274 = 0x10B;
                    func_8002D4C8(0xC62, 0);
                }
                break;

            case 10:
            case 11:
                D_801EF274 = 0x103;
                break;
            }

            if (D_801EF274 < 0) {
                func_8017ADE8(0xA);
                if (D_801EF274 == -1) {
                    func_8002D4C8(0x46F, 0);
                }
                {
                    u16 *p = &D_80115112;
                    D_801EF274 = 0;
                    *p = *p - 1;
                }
            }
            if (D_801EF274 >= 0x100) {
                s32 t = D_801EF274 & 0xFF;
                D_801EF274 = t;
                D_801EF1E0 = D_801C184C[t];
            }

            if (D_801EF1E0 != 0) {
                D_80115130 = D_801EF1E0;
                func_80139954();
                D_801EF1E4 = func_801376E8(D_801EF1E0, (s32)&D_801C17F0);
            }
        }
    } else {
        if (D_801EF1E0 != 0) {
            if (func_801399F0(D_801EF1E4) != 0) {
                D_801EF1E0 = 0;
            }
        } else if ((func_800149E0(0) & 0x50) != 0) {
            u16 idx = D_8011511A;
            if (D_80115138[idx] == 8) {
                func_8018C000(0xF, func_8014168C((s16)idx));
            }
            if (D_801EEB10 != 0) {
                func_80139954();
                D_800B9A15 = 0;
                func_8002D4C8(0x474, 0);
                D_80115112 = D_80115112 + 1;
            } else {
                func_8002D4C8(0x46F, 0);
                D_80115112 = D_80115112 - 1;
            }
        }
    }

    func_8018B238();
    func_80137B80();
}



extern s16 func_8014168C(s16 a0);
extern void func_8014BB24(s32 a0, s32 a1, s32 a2);
extern void func_8014B944(s32 a0, s32 a1, s32 a2);
extern void func_8014B2A8(void);
extern void func_801F1A24(s32 a0);
extern void func_8014BD24(s32 a0, s32 a1);
extern void func_8018C960(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void func_80139954(void);
extern void func_8018B238(void);
extern void func_80137B80(void);
extern s32 func_801376E8(s32 a0, s32 a1);
extern int func_8001AAA0(void);
extern s32 func_801399F0(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018ABAC(void)
{

    extern s32 D_80126B58;
    extern u8 D_801151C8[];
    extern s16 D_801EF1E8;
    extern s16 D_801C17F4[];
    extern u8 D_800B9A15;
    extern u16 D_80115112;
    extern s32 D_801EF1E0;
    extern s32 D_801F437C;
    extern s32 D_80115130;
    extern s32 D_801C17F0;
    extern s16 D_801EF270;
    extern s32 D_801EF1E4;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_8011511A;
    register s16 s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    register s32 s2 __asm__("$18");
    register s32 base __asm__("$19");
    s32 pad[2];
    (void)&pad;

    D_801151D0 = *(s32 *)&D_801151C8[(u16)D_800B9A02 * 4];
    base = (s32)&D_80126B58;

    if (D_801EF1E8 != 0) {
        D_801EF1E8 = D_801EF1E8 - 1;
        s0 = func_8014168C((s16)D_8011511A);

        if ((s16)s0 != 3) {
            s2 = 8;
            s1 = 0x3E7;
        } else {
            s2 = 3;
            s1 = 0x18;
        }

        if (D_801EF1E8 >= 0x3F) {
            if ((s16)D_801EF1EC != 0xFF) {
                D_801EF1EC += 0x10;
                if ((s16)D_801EF1EC >= 0x100) {
                    D_801EF1EC = 0xFF;
                }
            } else {
                D_801EF1F0 = *(u16 *)&D_801EF1F0 + 0x10;
                if (D_801EF1F0 >= 0x100) {
                    D_801EF1F0 = 0xFF;
                }
            }
        } else {
            if (D_801EF1E8 < 0x20) {
                if (D_801EF1F0 != 0) {
                    D_801EF1F0 -= 0x10;
                    if ((s16)D_801EF1F0 < 0) {
                        D_801EF1F0 = 0;
                    }
                } else {
                    D_801EF1EC -= 0x10;
                    if ((s16)D_801EF1EC < 0) {
                        D_801EF1EC = 0;
                    }
                }
            } else if (D_801EF1E8 == 0x30) {
                s0 = (s16)s0;
                func_8014BB24(base, D_801C17F4[s0], 1);
                func_8014B944(base, 0x1000000, 1);
                if (s0 == 2) {
                    func_8014B2A8();
                }
                func_801F1A24(s2);
                func_8014BD24(base, s1);
            }
        }

        func_8018C960();
        if (D_801EF1E8 == 0) {
            if (func_801621CC(s2) != 0) {
                func_801622C4();
                func_80139954();
                D_800B9A15 = 0;
                D_80115112 = 4;
                return;
            }
        }
    } else {
        if (D_801EF1E0 == 0) {
            D_801EF1E0 = (s32)&D_801F437C;
            D_80115130 = (s32)&D_801F437C;
            func_80139954();
            D_801EF1E4 = func_801376E8(D_801EF1E0, (s32)&D_801C17F0);
            if (D_801EF270 != 0) {
                ((s32 (*)(s32))func_8001AAA0)(0x16);
            }
        } else {
            if (func_801399F0(D_801EF1E4) != 0) {
                D_801EF1E0 = 0;
                func_8002D4C8(0x46F, 0);
                D_8011511A = 0;
                D_80115112 = 2;
            }
        }
    }

    func_8018B238();
    func_80137B80();
}




s32 func_8018AEE8(void) {

    extern s32  func_80014ED4(s32 a0);
    extern s32  func_80015018(s32 a0);
    extern s16  func_8014168C(s16 a0);
    extern s32  func_8018C000(s32 a0, s16 a1);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_801898E4(void);

    extern s32 D_801EF1E0;
    extern u16 D_8011511A;
    extern u16 D_80115120;
    extern u16 D_80115122;
    extern u8  D_80115138[];
    extern u8  D_80115140[];
    extern u8  D_8011514E;
    extern u8  D_80115143;

    s32 flags;
    s32 pad;
    s16 effectVal;
    s32 byteVal;
    s16 changed;
    u16 *p;
    u8 *pcur;
    u8 *pmax;
    s16 ret;
    s32 v;
    u8 b;
    u8 bb;
    u8 m;
    s16 d;
    register s32 zr __asm__("$0");

    changed = 0;
    flags = func_80014ED4(0);
    if ((u16)flags != 0) {
        D_801EF1E0 = 0;
    }
    pad = func_80015018(0);
    p = &D_8011511A;
    effectVal = func_8014168C(*(s16 *)p);
    byteVal = D_80115138[*p];

    if (flags & 0x40) {
        ret = func_8018C000(byteVal, effectVal);
        {
            s16 ret2 = ret;
            return ret & -(ret2 != 0);
        }
    } else if (flags & 0x10) {
        pad = byteVal + zr;
        if (pad < 7) {
            return -1;
        }
        func_8002D4C8(0x473, 0);
        if (pad != 0xD) {
            *p = 0;
        } else {
            *p = 1;
        }
        return 0;
    } else {
        pcur = (u8 *)&D_8011511A + (*p * 2 + 0x2E);
        pmax = (u8 *)&D_8011511A + (*p * 2 + 0x3E);

        if ((u16)pad != 0) {
            if ((u16)pad == D_80115120) {
                if (--D_80115122 == 0) {
                    flags = pad & 0xF000;
                    D_80115122 = 3;
                }
            } else {
                D_80115120 = pad;
                D_80115122 = 8;
            }
        } else {
            D_80115120 = 0;
            D_80115122 = 0xC;
        }

        if (flags & 0x1000) {
            v = pcur[0] - 1;
            pcur[0] = v;
            changed = 1;
            if ((u8)v >= 0x80) {
                if (byteVal < 10) {
                    pcur[0] = pmax[0] - 1;
                } else {
                    pcur[0] = 0;
                    changed = 0;
                }
            }
        }
        if (flags & 0x4000) {
            b = pcur[0];
            v = b + 1;
            pcur[0] = v;
            changed = 1;
            if ((u8)v >= pmax[0]) {
                if (byteVal < 10) {
                    pcur[0] = 0;
                } else {
                    pcur[0] = b;
                    changed = 0;
                }
            }
        }

        if (byteVal == 7 || byteVal == 8) {
            if (flags & 0x8000) {
                v = pcur[1] - 1;
                pcur[1] = v;
                changed = 1;
                if ((u8)v > 0x7F) {
                    pcur[1] = pmax[1] - 1;
                }
            }
            if (flags & 0x2000) {
                v = pcur[1] + 1;
                pcur[1] = v;
                changed = 1;
                if (pmax[1] <= (u8)v) {
                    pcur[1] = 0;
                }
            }
        } else {
            u16 idx2;
            bb = pcur[0];
            idx2 = D_8011511A;
            m = D_80115140[idx2];
            d = (s8)bb - (s8)m;
            if (d >= 6) {
                D_80115140[idx2] = bb - 5;
            } else if (d < 0) {
                D_80115140[idx2] = bb;
            }
        }

        if (changed != 0) {
            func_8002D4C8(0x45A, 0);
            if (byteVal + zr == 0xC) {
                D_8011514E = 0;
                D_80115143 = 0;
                func_801898E4();
            }
        }
        return 0;
    }
}


#include "common.h"

/* func_8018B238 — build the SC03 HUD display list for this frame.
 * 144 ins, frame 0x30, no stack locals.  match_one: MATCH (closeness 0).
 *
 * TU: src/ov_SC03_001/ov_SC03_001_jr_8018A3A8.c  (INCLUDE_ASM at line 3540)
 *
 * ---------------------------------------------------------------------------
 * WHERE THE SHAPE CAME FROM (§71 — the already-matched neighbours in this TU)
 *   func_8018B478  (line 3586) : the panel walker. Its Panel_8017E978_8018B478
 *                                is 0x20 bytes -> the `w++` (+0x20) stride here,
 *                                and its 3rd param is `s16 idx` -> the sll/sra
 *                                pair at the top of the loop feeding BOTH the
 *                                D_80115158 index and $a2.
 *                                It also supplies the RC-12 `+ zr` lever below.
 *   func_8018BCD4  (line 3651) : the §36 bitfield-store OT-link idiom and the
 *                                `volatile u16 *pbh` double read of D_800B9A02.
 *
 * ---------------------------------------------------------------------------
 * THE SIX LEVERS THAT WERE ACTUALLY LOAD-BEARING (each byte-verified by
 * removing it and re-running tools/match_one.py):
 *
 * 1. D_80115158 must be a STRUCT array, not `extern s16 D_80115158[]`.
 *    Symptom: an extra `la` hoisted into a callee-saved reg (+3 ins, $s4 saved).
 *    Mechanism: gcc-2.7.2 expand_expr rewrites `arr[i]` with a NON-CONSTANT
 *    index as `*(&arr + i*size)`, so the address reaches memory_address() as
 *    (plus SYMBOL_REF (mult reg 2)) -> not a legitimate MIPS address ->
 *    force_operand materialises the whole symbol into a register, which loop.c
 *    then hoists.  A COMPONENT_REF goes through get_inner_reference instead,
 *    whose offset is force_reg'd, giving (plus SYMBOL_REF reg) — the legitimate
 *    assembler-macro form `lh $v0, D_80115158($v0)` that maspsx expands to
 *    lui/addu/lh %lo.  (Same reason `D_800AE7BC[i].ot` already worked.)
 *    Cookbook index entry: "an extra `la` / the address hoisted into a
 *    callee-saved register across calls" -> §20 + gcc-2.7.2-map/cse_expr.md §H.
 *
 * 2. `register s32 n __asm__("$2")` (§17 register pin).  Without it reorg fills
 *    the INNER `bne`'s delay slot by stealing `addu $a0,$s0,$zero` from the
 *    fall-through instead of taking `addiu $v0,4` from the else thread, which
 *    leaves an extra `j` in the stream.  The pin does not change which register
 *    n gets (it was $v0 either way) — it changes what reorg's resource analysis
 *    can see, and that flips the choice.
 *
 * 3/4. BOTH `n = 3` sites must be `n = 3 + zr` (RC-12, the $0-ADD OPAQUE COPY
 *    documented on func_8018B478 in this same TU).  `(plus (reg 0) 3)` is not a
 *    plain constant load, so
 *      - it survives the noop-move deletion that otherwise eats the outer else
 *        arm entirely (its value is already in $v0 from the compare constant),
 *      - and being the SAME rtx in both arms it stays cross-jumpable, so the
 *        outer `bne` targets the shared insn and reorg COPIES it into the delay
 *        slot.  That copy is the target's "redundant" `addiu $v0,$zero,3`.
 *    Making only one of the two opaque gives 145 ins; making neither gives a
 *    `nop` in that delay slot.
 *
 * 5. `__asm__("")` at the head of the loop's if-body (§5a/§34 zero-byte fence).
 *    reorg.c stop_search_p halts fill_simple_delay_slots' forward scan on an asm
 *    insn, so the `beqz` slot is filled from the branch TARGET instead — the
 *    duplicated `addiu $v0,$s1,1` the target has in both the delay slot and
 *    after the call.  Without it the function is one instruction short.
 *
 * 6. `__asm__ __volatile__("" ::: "memory")` before the D_801151D0 store.
 *    The OT-link store is MEM_IN_STRUCT_P + varying while D_801151D0 is a plain
 *    SYMBOL_REF, which is exactly the pair gcc-2.7.2's true_dependence drop
 *    clause discards (§37 /s-DEP LATTICE), so the scheduler hoists the global
 *    store above the read-modify-write.  The fence restores the order.
 *    (Re-declaring D_801151D0 as a one-field struct via a §37 asm-label alias
 *    works identically; the fence is the smaller edit.)
 *
 * Also note: the loop guard is `if (n != 0)` + do-while, NOT `for (i=0;i<n;i++)`
 * — a plain `for` makes gcc emit the guard on the same pseudo as the loop bound
 * and drops the `addu $s3,$v0,$zero` copy the target has.
 *
 * ---------------------------------------------------------------------------
 * BANKING NOTES for the sibling overlays (this h_norm cluster has 5 members):
 *  - D_80115158 is declared `extern u8 D_80115158[]` at BLOCK scope inside
 *    func_8018BCD4 in this TU. The Flag_S40 spelling below is deliberately a
 *    draft-local type (§100/§120) so it cannot collide; keep it draft-local
 *    when propagating.
 *  - aD800B9A02 is the fleet's standard unsigned-access alias for the
 *    `extern short D_800B9A02` canon (§37); 864 sites already use that spelling.
 */

typedef struct { u32 addr : 24; u32 len : 8; } PTag_S40_8018B238;
typedef struct { u32 w; }                      W_S40_8018B238;
typedef struct { u32 *ot; u32 pad[4]; }        Env_S40_8018B238;   /* 0x14 stride */
typedef struct { s16 v; }                      Flag_S40_8018B238;  /* 0x02 stride */

typedef struct Panel_S40_8018B238 {
    s16   f0;    /* 0x00 */
    s16   f2;    /* 0x02 */
    void *f4;    /* 0x04 */
    void *f8;    /* 0x08 */
    s16   fC;    /* 0x0C */
    s16   fE;    /* 0x0E */
    s16   f10;   /* 0x10 */
    s16   f12;   /* 0x12 */
    void *f14;   /* 0x14 */
    void *f18;   /* 0x18 */
    void *f1C;   /* 0x1C */
} Panel_S40_8018B238;                                              /* 0x20 stride */






void func_8018B238(void) {
    extern short D_800B9A02;                        /* fleet-canonical spelling */
    extern u16   aD800B9A02 __asm__("D_800B9A02");  /* §37: the unsigned-access alias */
    extern Env_S40_8018B238    D_800AE7B8[];
    extern Env_S40_8018B238    D_800AE7BC[];
    extern s32                 D_801151D0;
    extern Panel_S40_8018B238 *D_80115134;
    extern s16                 D_801EF274;
    extern s16                 D_80115126;
    extern u16                 D_8011511A;
    extern Flag_S40_8018B238   D_80115158[];
    extern u8                  D_801C0E80[];
    extern u8                  D_801C0E94[];
    extern u8                  D_801C17E8[];
    extern Panel_S40_8018B238  D_801C1568;
    extern int   func_80137D08(int arg0, int arg1, short arg2);
    extern s32   func_800D27DC(s32, s32 *, void *, s32, s32);
    extern s32 func_8013AB54(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32  *func_8018B478(s32 *ot, Panel_S40_8018B238 *w0, s16 idx);
    extern s32   func_8005A600(s32, s32, s32, s32, s32);
    Panel_S40_8018B238 *w;
    s32 *ot;
    register s32 n __asm__("$2");      /* lever 2 */
    s32 cnt;
    register s32 zr __asm__("$0");     /* RC-12 opaque-copy source */
    s16 i;
    volatile u16 *pbh;

    w  = D_80115134;
    ot = (s32 *)func_80137D08(D_801151D0, (int)&D_800AE7B8[aD800B9A02], 2);

    /* Two full calls, not a ternary: gcc cross-jumps only the trailing
       `addiu $a3,1` + `jal`, which is why a0/a1/sp+0x10 are duplicated. */
    if (D_801EF274 == 3 || D_801EF274 == 7) {
        ot = (s32 *)func_800D27DC(2, ot, D_801C0E94, 1, 0);
    } else {
        ot = (s32 *)func_800D27DC(2, ot, D_801C0E80, 1, 0);
    }

    ot = (s32 *)func_8013AB54((s32)ot, (s32)(D_800AE7BC[aD800B9A02].ot + 2),
                              (s32)D_801C17E8, 0);

    if (D_80115126 == 3) {
        if (D_8011511A == 3) {
            ot = func_8018B478(ot, &D_801C1568, 3);
            n = 3 + zr;                /* lever 3 */
        } else {
            n = 4;
        }
    } else {
        n = 3 + zr;                    /* lever 4 */
    }

    i = 0;
    if (n != 0) {
        cnt = n;
        do {
            if (D_80115158[i].v != 0) {
                __asm__("");           /* lever 5 */
                ot = func_8018B478(ot, w, i);
            }
            i++;
            w++;
        } while (i < cnt);
    }

    func_8005A600((s32)ot, 0, 0, 0x15, 0);

    /* §36 bitfield-store OT link, exactly as in func_8018BCD4 next door. */
    pbh = (volatile u16 *)&D_800B9A02;
    ((W_S40_8018B238 *)ot)->w = 0x02000000;
    ((PTag_S40_8018B238 *)ot)->addr =
        ((PTag_S40_8018B238 *)(D_800AE7BC[*pbh].ot + 2))->addr;
    ((PTag_S40_8018B238 *)(D_800AE7BC[*pbh].ot + 2))->addr = (u32)ot;
    ot += 10;
    __asm__ __volatile__("" ::: "memory");   /* lever 6 */
    D_801151D0 = (s32)ot;
}



/* func_8018B478 — "draw one HUD panel" (family exemplar), 115 ins, frame 0x88.
 *
 * Re-derived from the .s (the earlier DIFF verdict was on a different draft shape).
 * Banked structural sibling (same author, expanded form):
 *   src/ov_SC06_008/ov_SC06_008_jr_8013F350.c  func_8013FAF8
 *     u8 sp18[72]; s32 sp60[2];  ->  sp18 @0x18, sp60 @0x60, frame 0x88
 *     flag != 0 ? 0x585858 : 0x808080   /   sp60[0] += -0x282828
 *     func_800D29F8(flagN, func_800D27DC(flagN != 0, ...), ...)
 *
 * Three levers were needed; all three are byte-verified by tools/match_one.py:
 *
 *  1. The flag is BRANCHLESS here (xor/sltu/negu/andi), unlike the sibling's
 *     if/else — that is `-(a != b) & 0xFF`, i.e. store_flag normalized to -1
 *     then truncated to u8.
 *
 *  2. RC-12 ($0-ADD OPAQUE COPY, docs/gcc-2.7.2-map/regalloc.md).  The target
 *     keeps the flag in TWO live regs — `beqz $s0` (ternary 1) reads the andi's
 *     own dest while `$s4` (the copy) feeds everything after it.  A plain
 *     `flag2 = flag;` is destroyed by cse.c make_regs_eqv head-promotion: the
 *     longer-lived copy becomes canonical and canon_reg rewrites ternary 1 to
 *     read $s4 (the single residual instruction in every plain-C spelling).
 *     `flag2 = flag + zr;` with `register s32 zr __asm__("$0")` is a (plus rA
 *     (reg 0)) — not a reg-reg set, so no qty merge and no canon — and
 *     assembles to the byte-identical `addu $s4, $s0, $zero`.  The same lever
 *     materializes the tail copy `addu $s0, $s4, $zero`.
 *
 *  3. `w` must be pinned to $18: unpinned, global.c's density order hands $s1
 *     to `w` and $s2 to `ot` (the target's grant is the other way round).  The
 *     pin lands on a LOCAL fed from the parameter, never on the parameter
 *     itself (S3).  Pin-free spellings (plain local, $0-add copy, routing `ot`
 *     through a local instead) were all tried and all leave the 22-diff swap.
 */




extern void  func_80024054(void *a0, void *a1);
extern s32  *func_800D2650(s32 *, void *, s32, s32, s32, s32);
extern s32   func_800D27DC(s32, s32 *, void *, s32, s32);
extern s32  *func_800D29F8(s32, s32, void *, s32, s32);
extern s32  *func_8018BCD4(s32 *, void *, s32, void *, s32);
extern s32   func_8018B644(void *, s32, s32, s32, s32 *);

s32 *func_8018B478(s32 *ot, Panel_8017E978_8018B478 *w0, s16 idx) {

    extern u16 D_8011511A;
    register Panel_8017E978_8018B478 *w __asm__("$18");
    u8 sp18[72];
    s32 sp60[2];
    register s32 zr __asm__("$0");
    s32 flag;
    s32 flag2;
    s32 flag3;
    s32 flag4;
    s16 i;
    Prim4_8017E978_8018B478 *p;
    s32 r;

    w = w0;
    flag = -(D_8011511A != idx) & 0xFF;
    func_80024054(w->f14, sp18);
    flag2 = flag + zr;
    ot = func_800D2650(ot, sp18, w->f10, w->f12, 1,
                       flag != 0 ? 0x585858 : 0x808080);
    ot = func_8018BCD4(ot, w->f18, idx, w->f8,
                       flag2 != 0 ? 0x585858 : 0x808080);
    i = 0;
    flag3 = flag2;
    p = w->f18;
    for (;;) {
        r = func_8018B644(w->f1C, w->f0, idx, i++, sp60);
        if (r == 0) {
            break;
        }
        if (r < 0) {
            func_80024054((void *)r, sp18);
            if (flag3 != 0) {
                sp60[0] += -0x282828;
            }
            ot = func_800D2650(ot, sp18, p->f0, p->f2, 1, sp60[0]);
        }
        p++;
    }
    flag4 = flag2 + zr;
    return func_800D29F8(flag4,
                         func_800D27DC(flag4 != 0, ot, w->f4, w->fC, 0),
                         w->f8, w->fE, 0);
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8018A3A8", func_8018B644);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8018A3A8", func_8018B8DC);








/* Duplicate of the TU's own forward decl at ov_SC03_001_jr_8017AE2C.c:9324 (ABOVE the splice
 * point, §138) — kept verbatim so the K&R definition below is checked against it. The 3rd
 * parameter is `s32` in that prototype and `s16` here: a K&R identifier-list definition is
 * compatible with a prototype carrying the DEFAULT-PROMOTED type, and the s16 spelling is what
 * produces the target's per-use `sll/sra 16` off the raw $a2 kept in $s4. */
extern s32 *func_8018BCD4(s32 *, void *, s32, void *, s32);

s32 *func_8018BCD4(out, src, idx, w, col)
    s32 *out;
    void *src;
    s16 idx;
    void *w;
    s32 col;
{
    extern short D_800B9A02;                /* TU-visible spelling (file scope, line 2448) */
    extern s16 func_8014168C(s16 a0);
    extern u16 D_8011511A;
    extern u16 D_80115116;
    extern u8  D_80115138[];
    extern u8  D_80115140[];
    extern u8  D_80115148[];
    extern u8  D_80115158[];
    extern u16 D_801C11BA;
    extern u16 D_801C11CE;

    extern Env_8018BCD4 D_800AE7BC[];


    /* §37 /s-DEP LATTICE: this store MUST be MEM_IN_STRUCT_P. `out[0] = k` folds `out + 0`
     * away and expands as a NON-/s mem, which keeps the true_dependence edge to the incoming
     * 5th-arg slot and pins `lw $v1,0x38($sp)` after it. The target has the arg load AFTER
     * the out[0] store, i.e. the edge must be DROPPED — sched.c's drop clause needs the store
     * /s + varying and the load non-/s + fixed-address. A COMPONENT_REF at offset 0 supplies
     * the /s.  (This single bit was the last 10 of 203 instructions.) */

    s32 c;
    s16 t;
    u16 *q;
    s32 m;
    volatile u16 *pbh;

    c = D_80115138[idx];

    ((W_8018BCD4 *)out)->w = 0x04000000;
    *((u8 *)out + 0xC) = 0x30;
    *((u8 *)out + 0xD) = 0x48;
    *(s16 *)((u8 *)out + 0xE) = 0x4056;
    out[1] = col | 0x64000000;

    if (c < 10) {
        /* §135 idiom 9/T3: the fleet decl returns s16; cast at the CALL so the return feeds
         * `sll $v0,$v0,1` with no `andi`/re-extend. */
        t = ((s32 (*)(s16)) func_8014168C)(idx) * 2;
    } else {
        t = (D_80115148[idx * 2] - D_80115140[idx]) * 2;
    }

    q = (u16 *)(t * 2 + (s32)src);
    pbh = (volatile u16 *)&D_800B9A02;
    *(s16 *)((u8 *)out + 0x8) = q[0] - 8;
    *(s16 *)((u8 *)out + 0xA) = q[1];
    *(s16 *)((u8 *)out + 0x12) = 8;
    *(s16 *)((u8 *)out + 0x10) = 8;

    /* §36 BITFIELD STORE = THE MASK-ORDER DECOUPLER. The head materializes 0x00FFFFFF
     * (lui+ori) BEFORE 0xFF000000 (lui) while the body ANDs the dest first — the signature of
     * expmed.c's store_fixed_bit_field, not of user-mask C. `volatile` on the index read is
     * what keeps the SECOND *pbh load alive (a plain read cse-folds and the fn loses 5 ins). */
    ((PTag_8018BCD4 *)out)->addr =
        ((PTag_8018BCD4 *)(D_800AE7BC[*pbh].ot + 2))->addr;
    ((PTag_8018BCD4 *)(D_800AE7BC[*pbh].ot + 2))->addr = (u32)out;

    out += 5;
    if (c < 10) {
        return out;
    }

    m = D_8011511A;
    if (m == idx) {
        if ((D_80115116 & 8) != 0) {
            s16 j;
            s32 k;
            s16 y;
            s16 eight;
            u16 *pb;
            /* §137/§36: m24 is a 2-insn constant, but the natural allocno order puts j/k ahead
             * of it and rotates $a2/$a3/$t0. Pinning m24 alone restores the whole rotation. */
            register u32 m24 __asm__("$6");
            u32 mhi;
            s32 vsum;

            j = 0;
            k = m;
            eight = 8;
            pb = (u16 *)&D_800B9A02;
            m24 = 0xFFFFFF;
            mhi = 0xFF000000;
            /* NOTE: the loop deliberately has NO source pointer of its own. gcc's combine_givs
             * folds every `out + K` reference into ONE address giv based at out+0x12; adding a
             * `u8 *p = (u8*)out + 0x12` biv makes `*(s16*)p` use the biv directly, which
             * survives as a SECOND register (the +1-instruction LENGTH-DRIFT). The giv's base
             * is the LAST such reference in source order — hence the +8 (`vsum`) store sits
             * before the 0x10/0x12 stores here even though the scheduler sinks it back. */
            for (; j < 2; j++) {
                if (j == 0) {
                    if (D_80115140[k] == 0) {
                        continue;
                    }
                    *((u8 *)out + 0xD) = 0x30;
                    y = D_801C11BA - 2;
                } else {
                    s32 k2 = k * 2;
                    if ((((s8 *)D_80115158)[k2] - ((s8 *)D_80115140)[k]) < 7) {
                        continue;
                    }
                    *((u8 *)out + 0xD) = 0x38;
                    y = D_801C11CE + 1;
                }
                *(s16 *)((u8 *)out + 0xA) = y;
                __asm__("" ::: "memory");   /* keeps the y store ahead of the 0x64808080 pair */
                *(u32 *)out = 0x04000000;
                *((u8 *)out + 0xC) = 0x78;
                *(u32 *)((u8 *)out + 0x4) = 0x64808080;
                *(s16 *)((u8 *)out + 0xE) = 0x4056;
                vsum = *(s32 *)((u8 *)w + 8) + *(s32 *)((u8 *)w + 0xC) - 0xC;
                *(s16 *)((u8 *)out + 0x8) = vsum;
                *(s16 *)((u8 *)out + 0x10) = eight;
                *(s16 *)((u8 *)out + 0x12) = eight;
                *(u32 *)out = ((*(u32 *)out) & mhi) | (D_800AE7BC[*pb].ot[2] & m24);
                {
                    register u32 *op __asm__("$4");
                    op = D_800AE7BC[*pb].ot;
                    op[2] = (op[2] & mhi) | (((u32)out) & m24);
                }
                out += 5;
            }
        }
    }
    return out;
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8018A3A8", func_8018C000);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8018A3A8", func_8018C89C);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8018A3A8", func_8018C8D4);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8018A3A8", func_8018C914);

#include "common.h"

/* func_8018C960 — ov_SC03_001 (133 ins), exemplar of a 5-member open-only
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
 *   §37  asm-label aliases for D_801EF1EC/D_801EF1F0: the TU canon is u16/s16
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
extern s16 D_800B9A02;
extern s32 D_801151D0;
extern u16 D_801EF1EC;
extern s16 D_801EF1F0;

void func_8018C960(void) {
    /* §100/§120: draft-local, uniquely-named types — they live in the BODY so
     * they cannot collide with the TU's own Env_8018BCD4 / PTag_8018BCD4. */
    typedef struct { u32 addr : 24; u32 len : 8; } PTag_8018C960;
    typedef struct { u32 *ot; u32 pad[4]; } Env_8018C960;   /* 0x14 stride */
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
    } PG4_8018C960;                     /* -> 0x24 */

    extern Env_8018C960 D_800AE7BC[];
    extern u8 aD801EF1EC __asm__("D_801EF1EC");
    extern u8 aD801EF1F0 __asm__("D_801EF1F0");

    u32 **pp;
    volatile u16 *pbh;
    u32 *p;
    u32 *r;
    u8 c1, c2;

    pp  = (u32 **)&D_801151D0;
    pbh = (volatile u16 *)&D_800B9A02;

    p = *pp;
    ((PTag_8018C960 *)p)->len = 1;
    p[1] = 0xE1000015;
    ((PTag_8018C960 *)p)->addr = ((PTag_8018C960 *)D_800AE7BC[*pbh].ot)->addr;
    ((PTag_8018C960 *)D_800AE7BC[*pbh].ot)->addr = (u32)p;

    p += 2;
    ((PG4_8018C960 *)p)->tag  = 0x08000000;
    ((PG4_8018C960 *)p)->code = 0x3A;
    ((PG4_8018C960 *)p)->x2 = -160;
    ((PG4_8018C960 *)p)->x0 = -160;
    ((PG4_8018C960 *)p)->x3 = 160;
    ((PG4_8018C960 *)p)->x1 = 160;
    c1 = aD801EF1EC;
    ((PG4_8018C960 *)p)->b1 = c1;
    ((PG4_8018C960 *)p)->b0 = c1;
    ((PG4_8018C960 *)p)->g1 = c1;
    ((PG4_8018C960 *)p)->g0 = c1;
    ((PG4_8018C960 *)p)->r1 = c1;
    ((PG4_8018C960 *)p)->r0 = c1;
    c2 = aD801EF1F0;
    ((PG4_8018C960 *)p)->y1 = -120;
    ((PG4_8018C960 *)p)->b3 = c2;
    ((PG4_8018C960 *)p)->b2 = c2;
    ((PG4_8018C960 *)p)->g3 = c2;
    ((PG4_8018C960 *)p)->g2 = c2;
    ((PG4_8018C960 *)p)->r3 = c2;
    ((PG4_8018C960 *)p)->r2 = c2;
    ((PG4_8018C960 *)p)->y0 = -120;
    ((PG4_8018C960 *)p)->y3 = 120;
    ((PG4_8018C960 *)p)->y2 = 120;

    ((PTag_8018C960 *)p)->addr = ((PTag_8018C960 *)D_800AE7BC[*pbh].ot)->addr;
    ((PTag_8018C960 *)D_800AE7BC[*pbh].ot)->addr = (u32)p;

    r = p + 9;                          /* 0x24 */
    p = r;                              /* COMBINE BARRIER — see header */
    ((PTag_8018C960 *)r)->len = 1;
    r[1] = 0xE1000240;
    ((PTag_8018C960 *)r)->addr = ((PTag_8018C960 *)D_800AE7BC[*pbh].ot)->addr;
    ((PTag_8018C960 *)D_800AE7BC[*pbh].ot)->addr = (u32)r;

    p += 2;
    *pp = p;
}



extern void (*D_801EB364[])(void);

void func_8018CB74(void *a0) {
    D_801EB364[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: iv-combine
// @stuck: none — MATCH (49 ins). gcc folds (v0+0x1800)-0x1000 -> v0+0x800; re-tie barrier on the WORKING reg v0 (NOT a saved local) forces the target chain v0=base+0x1800; s2=copy; v0-=0x1000; s1=v0<<5. NO register pins (pins re-trigger the lhu/lh dual-load CSE collapse and shrink the frame; natural alloc gives s0-s3 + frame 0x38).
extern int rand(void);
extern u8 *func_8012913C(s32 a0);

extern unsigned short D_801EB344[];

void func_8018CBB0(s32 param_1, s32 param_2)
{
    int s3;
    unsigned short s0;
    int s2;
    int s1;
    int v0;
    int iVar3;

    s0 = D_801EB344[*(short *)(param_1 + 0xfc)];
    s3 = param_2;
    if (((short *)D_801EB344)[*(short *)(param_1 + 0xfc)] == 0) {
        *(short *)(param_1 + 0xfc) = 0;
        s0 = D_801EB344[0];
    }
    *(short *)(param_1 + 0xfc) = *(short *)(param_1 + 0xfc) + 1;
    v0 = (rand() & 3) * 0x400 + 0x1800;
    s2 = v0;
    __asm__ __volatile__("" : "=r"(v0) : "0"(v0));
    s1 = (v0 - 0x1000) * 0x20;
    iVar3 = ((int (*)(int))func_8012913C)(4);
    if (iVar3 != 0) {
        *(short *)(iVar3 + 6) = s3;
        *(short *)(iVar3 + 0xa) = s0;
        *(short *)(iVar3 + 0xe) = 0;
        *(int *)(iVar3 + 0x10) = s1;
        *(short *)(iVar3 + 0x2c) = s2;
    }
}



extern void (*D_801EB378[])(void);

void func_8018CC74(void *a0) {
    D_801EB378[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: regalloc-order
// @stuck: none — MATCH

extern void func_8018CBB0(s32, s32);
extern s32 func_8012AD50(void *a0);

void func_8018CCB0(int param_1) {
    short uVar1;

    *(short *)(param_1 + 0xfc) = 0;
    *(int *)(param_1 + 0x1c) = 1;
    uVar1 = *(unsigned short *)(param_1 + 0x70) & 7;
    *(short *)(param_1 + 0xfe) = (uVar1 < 2) ? 0x1e : 0xf;
    if (uVar1 != 0) {
        func_8018CBB0(param_1, -0x80);
        func_8018CBB0(param_1, -0x30);
        func_8018CBB0(param_1, 0x20);
        func_8018CBB0(param_1, 0x70);
        func_8018CBB0(param_1, 0xc0);
    }
    if (1 < uVar1) {
        func_8018CBB0(param_1, -0x58);
        func_8018CBB0(param_1, -0x8);
        func_8018CBB0(param_1, 0x48);
        func_8018CBB0(param_1, 0x98);
        func_8018CBB0(param_1, 0xe8);
    }
    ((void (*)(int))func_8012AD50)(param_1);
}



// @class: regalloc-order
// @stuck: none — MATCH (param_1 naturally lands in $s0 across the call, mirrors sibling func_80184AEC)

extern s32 func_8012BEE8(s32 a0);
extern void func_8018CBB0(s32, s32);

void func_8018CD98(s32 arg0) {
    if (func_8012BEE8(arg0)) {
        *(s32 *)(arg0 + 0x1c) = (s32)*(s16 *)(arg0 + 0xfe);
        func_8018CBB0(arg0, 0x110);
    }
}



// @class: plumbing
// @stuck: none — MATCH (expected)
extern void func_8001CB00(int param_1, void *src, int len, int n);

extern unsigned char D_801EB36C;

void func_8018CDD8(int param_1)
{
    unsigned short uVar1;
    int iVar2;

    iVar2 = *(int *)(param_1 + 0x20);
    func_8001CB00(iVar2, &D_801EB36C, 0x280, 0x100);
    *(unsigned int *)(iVar2 + 4) = *(unsigned int *)(iVar2 + 4) | 0x70000000;
    uVar1 = *(unsigned short *)(param_1 + 0x2c);
    *(unsigned char *)(iVar2 + 0x27) = 0x9e;
    *(unsigned short *)(iVar2 + 0x2c) = 4;
    *(unsigned short *)(iVar2 + 0x1c) = uVar1;
    *(unsigned short *)(iVar2 + 0x1a) = uVar1;
    *(unsigned short *)(iVar2 + 0x18) = uVar1;
    *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    return;
}



extern void func_801292C8(u8 *a0);

void func_8018CE60(u8 *a0) {
    *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x4) - *(s32 *)(a0 + 0x10);
    if (*(s16 *)(a0 + 0x6) < -0x110) {
        func_801292C8(a0);
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8018A3A8", func_8018CEA8);


extern void (*D_801EB48C[])(void);

void func_8018CF54(void *a0) {
    D_801EB48C[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conformed to the TU (ov_SC04_018_jr_8017AE2C.c) — lever (A):
 *   func_8012A828 : TU declares `extern void ((void (*)(s32*, s32))func_8012A828)(s32*, s32);`
 *                   at L3460 / L4615 / L5083 / L5372 / L5859 / L6004 / L6155 /
 *                   L6479 / L6504 / L6529.  The draft's `(s32, s32)` form caused
 *                   the 7697-vs-6529 conflict.  Conformed here; the type
 *                   disagreement is pushed to a cast at the call site.
 *   D_8018D838    : TU declares `extern u8 D_8018D838[];` (block scope, L3467).
 *                   Conformed; `(s32)D_8018D838` == `(s32)&D_8018D838`.
 *   func_801788B8 : verbatim from TU L2532 / L7756 (below the splice point).
 *   func_8012C354, D_801EB390, func_8018D088, func_8018CF90 : no other
 *                   declaration anywhere in the TU (func_8018D088 / func_8018CF90
 *                   appear only as INCLUDE_ASM, which emits no C declaration).
 *
 * Body: the original draft was NOT byte-correct.  `*(u16 *)(x + 2) = 1;` must be
 * sequenced BEFORE the func_8012A828 call, not after it — with it after, gcc
 * coalesces the store base onto $a0 (`sh v0,2(a0)`) and re-emits the arg copy,
 * giving a 6-instruction ADDRESSING/cse diff.  Moved above the call; both stores
 * now retire off $s0 and the sh lands in the jal delay slot, as in the target. */

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32, s32);
extern s32 func_801788B8(s32 arg0, s32 arg1);

extern void func_8018D088(void);

void func_8018CF90(s32 a0) {

    extern M2C_UNK D_801EB390;
    extern u8 D_8018D838[];
    s32 s0 = a0;
    if (func_8012C354(a0, (s32)&D_801EB390)) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(u16 *)(s0 + 0x2) = 1;
        ((void (*)(s32*, s32))func_8012A828)((s32 *)s0, (s32)D_8018D838);
        func_801788B8(s0, (s32)func_8018D088);
    }
}


void func_8018CFF4(void) {
}


extern void func_80178CBC(s32 *a0, s32 a1);

void func_8018CFFC(s32 *a0)
{

    extern signed char D_801EB468[];
    s32 v0;

    v0 = *(s16 *)((s32)a0 + 0x70);
    v0 = v0 * 4;
    func_80178CBC(a0, *(s32 *)((s32)D_801EB468 + v0));
    *(s16 *)((s32)a0 + 0x2) = 0x3;
}



extern int func_80178970(void);
extern void func_80178D18(void);

void func_8018D048(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8018A3A8", func_8018D088);

INCLUDE_ASM("asm/ov_SC03_001/nonmatchings/ov_SC03_001_jr_8018A3A8", func_8018D0E4);






