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
extern u8 D_8018BEA0;
extern u8 D_8018BE10;
extern u8 D_8018BDEC;
extern u8 D_8018BDC8;
extern u8 D_8018BE7C;
extern u8 D_8018BE58;
extern u8 D_8018BE34;
extern u8 D_8018BDA4;
extern void func_80145934(void);
extern u8 D_8018BF30;
extern u8 D_8018BF0C;
extern u8 D_8018BEE8;
extern u8 D_8018BEC4;
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
extern unsigned char D_8018B328[];
extern unsigned char D_8018B358[];
extern unsigned char D_8018B3A8[];
extern unsigned char D_8018B3D8[];
extern unsigned char D_8018B408[];
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
extern void (*D_8018B458[])(void *);
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
extern s32 D_8018B520[];
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
extern u8 D_8018B5A8[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018B5B0;
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
extern int D_801D3080;
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
extern s32 D_801D3084;
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
extern s32 D_8018B5E0;
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
extern void (*D_8018B688[])(void);
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
extern void (*D_8018B6AC[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018B69C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018B6C0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018B6CC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018B6DC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018B6F4[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018B6E4;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018B708[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018B724[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018B714;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018B738[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018B74C[])(void);
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
extern s32 D_8018B760;
extern void (*D_8018B788[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018B768;
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
extern int (*D_8018B7D4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018B7D8[])(void);
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
extern unsigned short D_8018BC3C[];
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
extern void (*D_8018BC4C[])(void);
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
extern int D_801D30B8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018BC74[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018BC54;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018BC64;
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
extern void (*D_8018BCB4[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018BCBC[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018BC88;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018BCC8[])(void);
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
extern u8 D_8018BC98;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801D30C0;
extern s32 D_801D30CC;
extern s32 D_801D30D0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018BD04[])(s32 *);
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
extern s32 D_8018BCD8[];
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
extern s32 D_801D30C8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018BF54[])(void);
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
extern char D_8018BD74[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018BFF8[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018C14C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018BF68;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018C154[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018BF78;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018BF98;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018C15C[])(void);
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
extern void (*D_8018C184[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018C190[])(void);
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
extern void (*D_8018C004[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018C234;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018B318[];
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
extern unsigned char D_8018C248[];
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
extern s8 D_8018C284[];
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
extern u16 D_8018C2CC;
extern u16 D_8018C2CE;
extern u16 D_8018C2D0;
extern s32 D_8018C2D4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018C2DC;
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
extern int D_8018BFE8;
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
extern unsigned int D_8018C360[];
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
extern void (*D_8018C410[])(void);
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
extern u16 D_8018C440[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018C4A4;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801D30D8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018C4C8[])(void);
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
extern int D_801D3130[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018C510[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018C500;
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
extern char D_801D28E4[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018C518[])(void);
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
extern void (*D_8018C56C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018C534;
extern s16 D_8018C568;
extern s16 D_8018C566;
extern s16 D_8018C564;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018C578[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801D3190;
extern u8 D_801D3191;
extern u8 D_801D3192;
extern u8 D_801D3193;
extern u8 D_801D3194;
extern u8 D_801D3195;
extern u8 D_801D3196;
extern u8 D_801D3197;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018C588[])(void);
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
extern s32 D_801D31D0;
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
extern void (*D_8018C5CC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018C648[];
extern s32 D_8018C668[];
extern u8 D_8018C6E4[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018C704[];
extern u8 D_8018C724[];
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
extern void (*D_8018C7C0[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018C83C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801D28F4;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018C848[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018C850[])(void);
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
extern void (*D_8018C918[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018C928[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018C938[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018C944[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018C8A4[];
extern u8   D_8018C8B8[];
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
extern void (*D_8018C95C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018C964[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018C96C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018C974[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018C97C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018C984[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018C98C[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018CA40[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018CA48[])(void);
extern void func_80169F00(void *a0);
extern char D_8018C9F8[];
extern char D_8018C9B8[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018CA80[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018CA8C[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018CAD4[])(void);
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
extern void (*D_8018CB50[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801D34F0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018CB44[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018CB88[];
extern unsigned short D_8018CB90[];
extern unsigned short D_8018CB98[];
extern unsigned char D_801D34F8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801D34F0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018CBA0[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801D362C;
extern M2C_UNK D_801D3630;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D35B8;
extern void (*D_8018CBD0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801D3634[];
extern u8 D_801D363C[];
extern u8 D_801D35EC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018CBD8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018CBF4[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018CBFC[])(void);
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
extern void (*D_8018CC64[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018CC08;
extern u8 D_8018CC14;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018CC98[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018CCA0[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018CCF4[])(void);
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
extern u16 D_8018CD28[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018CD18[];
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
extern s32 D_8018CD44;
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
extern void (*D_8018CDBC[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018CDC4[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018CDCC[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018CDD4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018CDDC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018CDE4[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018CDF0[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018CDFC[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018CE08[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018CE18[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018CE28[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018CE30[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018CE38[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018CE40[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018CE48[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018CE50[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018CE58[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018CE60[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018CE68[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018CE70[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018CE78[])(void);
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
extern void (*D_8018CE80[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018CE88[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018CE90[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018CE98[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018CEA0[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018CEA8[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018CEB0[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018CEB8[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018CEC0[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018CEC8[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018CED0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018CED8[])(void);
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
extern void (*D_8018CF1C[])(void);
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
extern M2C_UNK D_8018CEE0;
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
extern void (*D_8018CF4C[])(void);
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
extern void (*D_8018CF88[])(void);
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
extern void (*D_8018CFE0[])();
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
extern void (*D_8018CFF0[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018CFF8[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018D160[])();
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
extern void (*D_8018D16C[])();
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
extern M2C_UNK D_801D2B3C;
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
extern s16 D_801D47D8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801D3D70;
extern short D_801D484C;
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
extern s32 D_801D419C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801D41C4;
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
extern s16 D_801D4180;
extern s32 func_8017A3B0(void);
extern short D_801D41BC;
extern short D_801D41B8;
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
extern s16 D_801D4184;
extern u16 D_801D4204;
extern u16 D_801D4206;
extern u16 D_801D4208;
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
extern s16 D_801D41FC;
extern s16 D_801D41FE;
extern s16 D_801D4200;
extern s16 D_801D41F4;
extern s16 D_801D41F6;
extern s16 D_801D41F8;
extern void func_8017B7A8(void);
extern s16 D_801D4214;
extern s16 D_801D4216;
extern s16 D_801D4218;
extern s16 D_801D421C;
extern s16 D_801D421E;
extern s16 D_801D4220;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801D420C;
extern short D_801D420E;
extern short D_801D4210;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801D41A4;
extern SV4 D_801D41AC;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801D41CC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801D41C8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018D348[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8018D354[])(void);
extern void func_8017BEE4(void *a0);
extern void func_8017BF98(void);
extern void (*D_8018D360[])(void);
extern void func_8017BFC8(void *a0);
extern void func_8017C07C(void);
extern void (*D_8018D420[])(void);
extern void func_8017C0C8(void *a0);
extern void func_8017C154(void);
extern void func_8017C12C(void);
extern void func_8017C14C(void);
extern void (*D_8018D460[])(void);
extern void func_8017C664(void *a0);
extern void (*D_8018D480[])(void);
extern void func_8017CE54(void *a0);
extern void (*D_8018D490[])(void);
extern void func_8017D0DC(void *a0);
extern void (*D_8018D49C[])(void);
extern void func_8017D63C(void *a0);
extern void (*D_8018D620[])(void);
extern void func_8017DB00(void *a0);
extern void func_8017DB74(u8 *a0);
extern void func_8017DD74(void);
extern void func_8017DF7C(void);
extern void (*D_8018D920[])(void);
extern void func_8017E898(void *a0);
extern void (*D_8018D95C[])(void);
extern void func_8017EF6C(void *a0);
extern void func_8017F16C(u8 *p);
extern void (*D_8018D964[])(void);
extern void func_8017F200(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern u8 D_8018D950;
extern void func_8017F23C(s32 a0);
extern void (*D_8018DA1C[])(void);
extern void func_8017F344(void *a0);
extern void func_8017F49C(void);
extern M2C_UNK D_8018DA14;
extern void func_8017F4A4(void);
extern s32 func_8017F4E8(void);
extern void func_8017FB84(s32 arg0);
extern void func_80180A64(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void (*D_8018DD98[])(void);
extern void func_8018165C(void *a0);
extern void func_801819C4(void);
extern s32 func_80181698(s32 a0);
extern s32 func_801816DC(void);
extern void (*D_8018DDA0[])(void);
extern void func_80181700(void *a0);
extern void func_801819EC(void);
extern s32 func_8018173C(s32 a0);
extern void (*D_8018DDA8[])(void);
extern void func_80181780(void *a0);
extern void func_80181A14(void);
extern s32 func_801817BC(s32 a0);
extern void func_800D1EBC(void);
extern void func_8018188C(void);
extern void (*D_8018DDB4[])(void);
extern void func_801818AC(void *a0);
extern void func_80181A3C(void);
extern s32 func_801818E8(s32 a0);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);
extern s32 func_80181928(u8 *a0);
extern void func_801819A4(void);
extern M2C_UNK D_8018DDC0;
extern M2C_UNK D_8018DDCC;
extern M2C_UNK D_8018DDE4;
extern void func_8012A094(s32 a0);
extern void func_80181B08(void *a0);
extern void func_80181A64(void);
extern void (*D_8018DDF0[])(void);
extern void (*D_8018DE08[])(void);
extern void func_80181E1C(void *a0);
extern s32 func_8018248C(s32 arg0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80182550(void *arg0);
extern void func_801831D0(void);
extern void func_80182570(void);
extern void func_8013CAE8(void);
extern void func_80182590(void);
extern void (*D_8018E0E4[])(void);
extern void func_801825B0(void *a0);
extern void func_80182704(void *a0);
extern void func_8017BEBC(void);
extern void func_801828A4(void);
extern void func_8017BFA0(void);
extern void func_801828C4(void);
extern void func_800D0C48(s32 arg);
extern void func_801828E4(void);
extern void func_80182904(void *a0);
extern void func_80182910(void *a0);
extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8018295C(void *a0);
extern void func_80182988(s32 *a0);
extern void func_801829E4(u8 *a0);
extern void (*D_8018E134[])(int);
extern void func_80182998(int param_1);
extern void func_80182ADC(void);
extern void func_80182AE4(void);
extern void func_80182AEC(void *arg0);
extern void func_8018291C(void);
extern void func_80182FAC(void);
extern void (*D_8018E208[])(void);
extern void func_801838A4(void *a0);
extern void (*D_8018E858[])(void);
extern void func_801838E0(void *a0);
extern void func_80183AF8(void);
extern void (*D_8018E8A0[])(void);
extern void func_80183B00(void *a0);
extern s32 func_80183B3C(void *a0, s32 *p);
extern void func_80183C50(void);
extern void (*D_8018EC08[])(void);
extern void func_80183C58(void *a0);
extern void func_80184164(void);
extern void func_8018416C(s32 param_1);
extern void func_801841C0(s32 param_1);
extern void (*D_8018EC14[])(void);
extern void func_80184430(void *a0);
extern void (*D_8018EF38[])(void);
extern void func_8018446C(void *a0);
extern s32 func_80184644(void);
extern s32 func_8012A828(void *a0, void *a1);
extern void func_8018474C(void *arg0);
extern void func_80184778(void *arg0);
extern void func_801847A4(void *arg0);
extern void func_801847D0(void *arg0);
extern void func_801847FC(void *arg0);
extern void func_80184828(void *arg0);
extern void func_80184854(void *arg0);
extern void func_80184880(void *arg0);
extern void func_801848AC(void *arg0);
extern void func_801848D8(void *a0);
extern void (*D_8018EF74[])(void);
extern void func_80184940(void *a0);
extern void (*D_8018EF90[])();
extern void func_80184DD8(int param_1);
extern void func_8018523C(void *a0);
extern void (*D_801C5928[])(void);
extern void func_8018545C(void *a0);
extern void func_8018552C(void);
extern void func_801855F0(s32 arg0, s32 arg1, s32 arg2);
extern void func_8018570C(s32 arg0, Rec_8018A6A4_80185550 *arg1, s32 arg2, s32 arg3);
extern void func_80185550(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_80185620(s32 a0);
extern s16 D_801D4472;
extern void func_80185698(s32 arg0);
extern s32 rand(void);      /* TU L951, verbatim */
extern void aF8018A860();
extern s32 func_801857E0(void);
extern void func_8018581C(s32 a0, s32 a1);
extern void func_80185944(s32 arg0);
extern void func_80185868(void);
extern void func_80185C08(void);
extern void func_80185C54(s32 a0);
extern void func_80185C2C(s32 a0);
extern void func_80185CDC(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern void func_80185D48(void *a0, void *a1, s16 a2);
extern void func_80185E7C(s32 a0, s16 a1, u16 a2);
extern void func_80185DB8(s32 a0);
extern s32 func_80185F98(void);
extern void func_80185E30(s32 a0, s32 a1);
extern void aF8018AFD0();
extern void func_80185FD4(void);
extern void RotMatrixZ(s32 a0, void *a1);
extern void func_8004901C(void *a0, void *a1);
extern void func_80016638(void *a0, s32 a1, s32 a2);
extern void func_801860E8(s32 a0);
/* ==== end §8b carried decl layer ==== */


extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern s32 func_8012A828(void*, void*);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8012C1B8(void);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 rand(void);


void func_801863CC(void *a0v)
{

    extern u8 D_801C6F08[];
    extern u8 D_801C8338[];
    extern u8 D_801C6FDC[];
    extern u8 D_801C6FA8[];
    extern u8 D_801D4558[];
    extern u8 D_801C6F3C[];
    extern u8 D_801C6F48[];
    extern u8 D_801C6F50[];
    extern u8 D_801C6F60[];
    extern u16 D_801C6F64;
    extern u8 D_801C6F68[];
    extern u8 D_801C6F74[];
    extern u8 D_801C6F7C[];
    extern u8 D_801C6FA0[];
    extern u16 D_801C6FA4;
    extern u8 D_801C6F8C[];
    extern u8 D_801C6F98[];
    extern u8 D_801D4599;
    extern u8 D_801D459A;
    extern u8 D_801D459C;
    s32 e;
    s32 r;
    s32 o;
    s32 cc;
    s32 sv;
    u8 *p;
    u8 *q;

    e = (s32)a0v;

    switch (*(s16 *)(e + 0x70)) {
    case 0:
        if (func_8012C354(e, (s32)D_801C6F08) == 0) {
            return;
        }
        *(u8 *)(e + 0xC0) = 1;
        *(s32 *)(e + 0xB4) = -1;
        *(s32 *)(e + 0xBC) = (s32)D_801C6FDC;
        ((void (*)(s32, void *))func_8012A828)(e, D_801C8338);
        *(s16 *)(e + 0x2) = 1;
        *(s16 *)(e + 0x34) = 1;
        func_8012B23C(e);
        func_8012B1B4(e, (s32)D_801C6FA8);
        *(s32 *)(e + 0xCC) = (s32)(D_801D4558 + *(s16 *)(e + 0xFC) * 8);
        o = func_8012C658(0x1EA, 1, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        return;

    case 1:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801C6F3C);
        ((void (*)(s32, void *))func_8012A828)(e, D_801C6F48);
        *(s16 *)(e + 0x2) = 2;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801C6F50 | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801C6F60;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801C6F64;
        cc = *(s32 *)(*(s32 *)(e + 0x64) + 0xCC);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) | 0x80;
        *(s32 *)(*(s32 *)(e + 0x20) + 0x80) = cc;
        *(s32 *)(e + 0xCC) = cc;
        o = func_8012C658(0x1EA, 2, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        return;

    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801C6F68);
        ((void (*)(s32, void *))func_8012A828)(e, D_801C6F74);
        *(s16 *)(e + 0x2) = 0xF;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801C6F7C | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801C6FA0;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801C6FA4;
        return;

    case 7:
        if (func_8012C354(e, (s32)D_801C6F08) == 0) {
            return;
        }
        p = &D_801D4599;
        q = p - 1;
        D_801D459A = 0xFF;
        *q = 0xFF;
        *p = 0;
        D_801D459A = 0;
        D_801D459C = 0;
        func_800233CC(q, 0x20);
        *(u8 *)(e + 0xC0) = 1;
        *(s32 *)(e + 0xB4) = -1;
        *(s32 *)(e + 0xBC) = (s32)D_801C6FDC;
        ((void (*)(s32, void *))func_8012A828)(e, D_801C8338);
        *(s16 *)(e + 0x2) = 8;
        *(s16 *)(e + 0x34) = 0xB;
        func_8012B23C(e);
        sv = *(s16 *)(e + 0xFC);
        *(s16 *)(e + 0xFC) = 0;
        *(s32 *)(e + 0xCC) = (s32)(D_801D4558 + sv * 8);
        o = func_8012C658(0x1EA, 8, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        return;

    case 8:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801C6F3C);
        ((void (*)(s32, void *))func_8012A828)(e, D_801C6F48);
        *(s16 *)(e + 0x2) = 2;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801C6F50 | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801C6F60;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801C6F64;
        cc = *(s32 *)(*(s32 *)(e + 0x64) + 0xCC);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) | 0x80;
        *(s32 *)(*(s32 *)(e + 0x20) + 0x80) = cc;
        *(s32 *)(e + 0xCC) = cc;
        o = func_8012C658(0x1EA, 9, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
        }
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801C6F68);
        ((void (*)(s32, void *))func_8012A828)(e, D_801C6F74);
        *(s16 *)(e + 0x2) = 0xF;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801C6F7C | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801C6FA0;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801C6FA4;
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 14:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801C6F8C);
        ((void (*)(s32, void *))func_8012A828)(e, D_801C6F98);
        *(s16 *)(e + 0x2) = 0xC;
        *(u16 *)(*(s32 *)(e + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(*(s32 *)(e + 0x64) + 0x20) + 0x10);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(e + 0x64) + 0x20) + 0x12);
        *(s32 *)(e + 0x14) = func_8004787C(*(s16 *)(*(s32 *)(e + 0x20) + 0x10)) << 9;
        {
            s32 t1 = func_8004787C(*(s16 *)(*(s32 *)(e + 0x20) + 0x12));
            *(s32 *)(e + 0x10) = -((t1 * func_80047948(*(s16 *)(*(s32 *)(e + 0x20) + 0x10))) >> 3);
        }
        {
            s32 t2 = func_80047948(*(s16 *)(*(s32 *)(e + 0x20) + 0x12));
            *(s32 *)(e + 0x18) = -((t2 * func_80047948(*(s16 *)(*(s32 *)(e + 0x20) + 0x10))) >> 3);
        }
        *(s32 *)(e + 0x10) = (*(s32 *)(e + 0x10) * 2) / 3;
        *(s32 *)(e + 0x1C) = 0x12C;
        *(s32 *)(e + 0x14) = (*(s32 *)(e + 0x14) * 2) / 3;
        *(s32 *)(e + 0x18) = (*(s32 *)(e + 0x18) * 2) / 3;
        return;

    case 15:
        if (func_8012C354(e, (s32)D_801C6F08) == 0) {
            return;
        }
        *(u8 *)(e + 0xC0) = 1;
        *(s32 *)(e + 0xB4) = -1;
        *(s32 *)(e + 0xBC) = (s32)D_801C6FDC;
        ((void (*)(s32, void *))func_8012A828)(e, D_801C8338);
        *(s16 *)(e + 0x2) = 0xD;
        *(s16 *)(e + 0x34) = 0xD;
        func_8012B23C(e);
        *(s32 *)(e + 0xCC) = (s32)(D_801D4558 + *(s16 *)(e + 0xFC) * 8);
        o = func_8012C658(0x1EA, 0x11, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
            *(s32 *)(e + 0x6C) = o;
        }
        *(s16 *)(e + 0xFC) = 0xA;
        return;

    case 16:
    case 24:
        *(s16 *)(e + 0x2) = 0xE;
        *(s32 *)(e + 0x1C) = 6;
        return;

    case 17:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801C6F3C);
        ((void (*)(s32, void *))func_8012A828)(e, D_801C6F48);
        *(s16 *)(e + 0x2) = 0x11;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801C6F50 | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801C6F60;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801C6F64;
        cc = *(s32 *)(*(s32 *)(e + 0x64) + 0xCC);
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) | 0x80;
        *(s32 *)(*(s32 *)(e + 0x20) + 0x80) = cc;
        *(s32 *)(e + 0xCC) = cc;
        o = func_8012C658(0x1EA, 0x12, e);
        if (o != 0) {
            *(u16 *)(o + 0xFE) = *(u16 *)(e + 0x36);
            *(s32 *)(e + 0x6C) = o;
        }
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
        r = func_8012C1B8();
        *(s32 *)(e + 0x20) = r;
        if (r == 0) {
            func_8012CAE4((void *)e);
            return;
        }
        func_8001CA1C(r, (s32)D_801C6F68);
        ((void (*)(s32, void *))func_8012A828)(e, D_801C6F74);
        *(s16 *)(e + 0x2) = 0x10;
        *(s16 *)(e + 0x5C) = 0x810;
        *(s32 *)(e + 0x58) = (s32)D_801C6F7C | 0x40000000 | 0x20000000;
        *(s32 *)(e + 0xD0) = (s32)D_801C6FA0;
        *(u16 *)(e + 0xE) = *(u16 *)(e + 0xE) + D_801C6FA4;
        *(u16 *)(e + 0x106) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x100) = (rand() & 0x1F) + 0x20;
        *(u16 *)(e + 0x102) = rand() & 0xFFF;
        *(u16 *)(e + 0x104) = rand() & 0xFFF;
        return;

    case 25:
        *(s16 *)(e + 0x2) = 0x13;
        return;
    }
}


// @class: MATCH (386 ins, match_one byte-exact)
// @notes: 386-ins camera follow/aim update.  Frame 0x50, $s0..$s3 + $ra saved.
//
// SIX LOAD-BEARING LEVERS (each MOVED the count; 183 -> 17 -> 7 -> 4 -> 0):
//
//  1. §136 L5 / idiom 6 — LOCAL SLOT ORDER + THE DEAD PAD.
//     out[4]@0x10 (RotTransSV out, read lhu)  sv[4]@0x18 (RotTransSV in)
//     pos[4]@0x20 (func_8012CEB0 arg1)        flag@0x28.
//     `flag` is ONE addressable s32 reused as the yaw-delta temp, the
//     RotTransSV out-param AND the func_8012CEB0 result — every stack ref in
//     the .s is 0x28, so it cannot be split.  vars must be 0x28 (s0@0x38), so
//     8 dead bytes are needed AFTER flag.
//     *** The pad MUST be an INNER-BLOCK decl at the END of the body. ***
//     An addressable SCALAR gets its stack slot lazily, when the C front end
//     parses the first `&flag` (gcc 2.x generates RTL as it parses); a
//     function-scope `s32 pad[2];` is expand_decl'd BEFORE any statement and
//     therefore steals 0x28, pushing flag to 0x30 (cost: 15 mismatches).
//
//  2. §136 L1 (reuse, not split) — ONE pointer local `p` carries BOTH
//     *(a0+0xCC) and the three *(a0+0xD0) reloads.  Refs in 4 basic blocks =>
//     a GLOBAL allocno => $s1, which is the 4th callee-saved register and the
//     whole reason the frame is 0x50.  A separate `m` for the 0xD0 sites is a
//     local allocno in $v1 and the function is 1 instruction short.
//
//  3. fold's `associate:` REASSOCIATES `(A - K) + B` into `A + (B - K)` and
//     `A - (B - K)` into `(A + K) - B`.  Both spellings appear here and both
//     had to be split into a two-statement form with an explicit temp:
//       `s32 t = *(u16*)(q+0x12) - 0x200;  *(u16*)(q+0x12) = t + flag;`
//       `s32 t = pos[1] - 0x10;            d = *(s16*)(a0+0xA) - t;`
//     Left folded, the first emits `li $a1,0xfe00` + `addu` where the target
//     has `addiu $v1,$v1,-0x200` (idiom T2), and breaks the .L80186D68
//     cross-jump merge of the two clamp arms.
//
//  4. §5a/§34 ZERO-BYTE FENCE — `__asm__ __volatile__("")` as the FIRST
//     statement of the `>= 0` (else / branch-target) arm.  reorg.c
//     `mostly_true_jump` predicts `bgez` TAKEN, so `fill_eager_delay_slots`
//     fills the delay slot from the branch-TARGET thread and steals that arm's
//     `lui $v1,0x7fff`, leaving a nop behind.  `stop_search_p` bails on any asm
//     insn, so the fence forces the fall-through thread instead — which yields
//     the target's `lui $a0,(0x80000000>>16)` in the slot.  Worth 3 mismatches.
//
//  5. REGALLOC-PERM $v0<->$v1 in the sign-set arm — the one place a source
//     lever could not reach (all 8 spellings swept: ptr local, value temp,
//     u32, `|=`, const-first, ~mask, swapped arms).  Pinned the pointer to $3.
//     It is a BLOCK-LOCAL pointer, not a parameter (S3), so it costs nothing.
//     Levers 4 and 5 are BOTH required: either alone leaves 3 mismatches.
//
//  6. The two GTE control-register blocks are this TU's own
//     gte_SetRotMatrix / gte_SetTransMatrix bodies verbatim.  That #define
//     lives BELOW the splice point (TU:5437/5451), so they are respelled here
//     under private names to avoid a redefinition.
//
// DECLARATION SURFACE (D2 whole-TU one-pass grep, all above/below the splice):
//   func_80047948 (TU:2204/4542/4642), func_8004787C (2205/4543/4643),
//   func_80049CAC (2652), RotTransSV (2655) — copied VERBATIM.
//   func_8012C218 (4926/5226/5265/5371, all BELOW the splice) — copied
//     VERBATIM; the .s passes no argument, so it is called through a cast
//     (idiom 9), exactly as the TU's banked func_801886xx sibling does.
//   func_8012CEB0 — declared NOWHERE in this TU and in none of the 17
//     DEFINE_func_*() macros this TU expands (all checked), so the fleet-
//     dominant `(s32,s32,s32)` spelling is free here.
//   func_80186B78 itself has no prototype anywhere (only the INCLUDE_ASM at
//     TU:4837), so no asm-label alias is needed.

extern void func_8012C218(void *a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);

#define SRM_80186B78(r0) __asm__ __volatile__( \
    "lw $12, 0(%0)\n"  \
    "lw $13, 4(%0)\n"  \
    "ctc2 $12, $0\n"   \
    "ctc2 $13, $1\n"   \
    "lw $12, 8(%0)\n"  \
    "lw $13, 12(%0)\n" \
    "lw $14, 16(%0)\n" \
    "ctc2 $12, $2\n"   \
    "ctc2 $13, $3\n"   \
    "ctc2 $14, $4\n"   \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

#define STM_80186B78(r0) __asm__ __volatile__( \
    "lw $12, 20(%0)\n" \
    "lw $13, 24(%0)\n" \
    "ctc2 $12, $5\n"   \
    "lw $14, 28(%0)\n" \
    "ctc2 $13, $6\n"   \
    "ctc2 $14, $7\n"   \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

void func_80186B78(s32 a0)
{
    u16 out[4];      /* sp+0x10 */
    s16 sv[4];       /* sp+0x18 */
    s16 pos[4];      /* sp+0x20 */
    s32 flag;        /* sp+0x28 */
    s16 *p;

    if (*(s16 *)(*(s32 *)(a0 + 0x64) + 0x36) != *(s16 *)(a0 + 0xFE)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    if (*(s16 *)(a0 + 0x70) == 1 || *(s16 *)(a0 + 0x70) == 8) {
        s32 ang;
        s32 t;
        ang = (*(u16 *)(a0 + 0xFC) + 0x40) & 0xFFF;
        p = *(s16 **)(a0 + 0xCC);
        *(s16 *)(a0 + 0xFC) = ang;
        t = (func_8004787C(ang) >> 6) + 0xBF;
        p[2] = t;
        p[1] = t;
        p[0] = t;
    }

    if (*(s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 4) < 0) {
        { register s32 *q __asm__("$3"); q = *(s32 **)(a0 + 0x20);
          q[1] = q[1] | 0x80000000; }
    } else {
        __asm__ __volatile__("");
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) =
            *(s32 *)(*(s32 *)(a0 + 0x20) + 4) & 0x7FFFFFFF;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x18);

    if (*(s16 *)(*(s32 *)(a0 + 0x64) + 0x70) < 8) {
        *(s16 *)(a0 + 0x108) = (*(u16 *)(a0 + 0x108) + 0x40) & 0xFFF;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12) & 0xFFF;

        flag = *(s16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12) -
               *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        if (flag > 0x800) {
            flag = flag - 0x1000;
        }
        if (flag < -0x800) {
            flag = flag + 0x1000;
        }
        if (flag > 0x200) {
            s32 t = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) - 0x200;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t + flag;
        } else if (flag < -0x200) {
            s32 t = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x200;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t + flag;
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + (flag / 16);
        }

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) +
            (func_8004787C(*(s16 *)(a0 + 0x108)) >> 6);

        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        SRM_80186B78((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
        STM_80186B78((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

        p = *(s16 **)(a0 + 0xD0);
        sv[0] = 0;
        sv[1] = 0;
        sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
        RotTransSV(sv, out, &flag);

        *(s16 *)(a0 + 6) = out[0];
        *(s16 *)(a0 + 0xA) = out[1];
        *(s16 *)(a0 + 0xE) = out[2];
        out[1] = out[1] - 0x40;

        pos[0] = *(u16 *)(a0 + 6);
        pos[1] = *(u16 *)(a0 + 0xA) + 0x10;
        pos[2] = *(u16 *)(a0 + 0xE);
        flag = func_8012CEB0((s32)out, (s32)pos, 1);
        if (flag & 0x1000) {
            return;
        }
        if (flag != 0) {
            s32 d;
            s32 t = pos[1] - 0x10;
            d = *(s16 *)(a0 + 0xA) - t;
            if (d < 5) {
                return;
            }
            if (d > 0x40) {
                d = 0x40;
            }
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) + (d << 4);

            func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
            SRM_80186B78((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
            STM_80186B78((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

            p = *(s16 **)(a0 + 0xD0);
            sv[0] = 0;
            sv[1] = 0;
            sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
            RotTransSV(sv, out, &flag);

            *(s16 *)(a0 + 6) = out[0];
            *(s16 *)(a0 + 0xA) = out[1];
            *(s16 *)(a0 + 0xE) = out[2];
        } else {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) - 0x80;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) & 0xFFF;
            if ((u32)(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) - 0x801) < 0x3FF) {
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0xC00;
            }
        }
    } else {
        s32 ang;
        s32 ang2;

        ang = (*(u16 *)(a0 + 0x102) + *(u16 *)(a0 + 0x106)) & 0xFFF;
        *(s16 *)(a0 + 0x102) = ang;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = func_80047948(ang) >> 6;

        ang2 = (*(u16 *)(a0 + 0x104) + *(u16 *)(a0 + 0x100)) & 0xFFF;
        *(s16 *)(a0 + 0x104) = ang2;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) = func_80047948(ang2) >> 6;

        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) + 0xC00;

        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        SRM_80186B78((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
        STM_80186B78((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

        p = *(s16 **)(a0 + 0xD0);
        sv[0] = 0;
        sv[1] = 0;
        sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
        RotTransSV(sv, out, &flag);

        *(s16 *)(a0 + 6) = out[0];
        *(s16 *)(a0 + 0xA) = out[1];
        *(s16 *)(a0 + 0xE) = out[2];
    }
    { s32 pad[2]; }   /* LEVER 1: frame pad. INNER-BLOCK + LAST is load-bearing --
                         a function-scope decl takes 0x28 and evicts flag to 0x30 */
}


#include "common.h"

extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern void func_8012CC40(s32 arg0, s32 arg1);   /* fleet-canonical: void; $v0 used -> cast at call site */

void func_80187180(s32 a0)
{
    extern u8 D_801C6FA8[];
    extern s32 D_801C6FC4;

    s16 pos1[4];
    s16 pos2[4];
    s32 s1;

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;
    func_8012B1B4(a0, (s32)D_801C6FA8);

    {
        s16 *p1 = pos1;
        s16 *p2 = pos2;
        s32 x, y, z;

        x = *(u16 *)(a0 + 0x6);
        p2[0] = x;
        p1[0] = x;
        y = *(u16 *)(a0 + 0xA);
        p2[1] = y;
        p1[1] = y;
        z = *(u16 *)(a0 + 0xE);
        p2[1] = y + 0x40;
        p2[2] = z;
        p1[2] = z;
        s1 = func_8012CEB0((s32)p1, (s32)p2, 1);
    }

    if (s1 & 0x6000) {
        if (!(s1 & 0x1000)) {
            s1 = func_8012BCCC(a0);
            if (s1 < 0x4001) {
                if (func_8012BDBC(a0, 0x200) == 1) {
                    *(s16 *)(a0 + 0x2) = 4;
                    *(s16 *)(a0 + 0xFC) = 0;
                    *(s16 *)(a0 + 0x100) = *(u16 *)(a0 + 0xA);
                }
            }
        }
    }
    if (s1 > 0x40000) {
        *(s16 *)(a0 + 0x2) = 1;
    }

    if ((((s32 (*)(s32, s32))func_8012CC40)(a0, (s32)&D_801C6FC4) & 0x1000) != 0) {
        *(s16 *)(a0 + 0x2) = 0x12;
    }
}


#include "common.h"

void func_801872B4(s32 arg0) {
    extern void func_8012C218(void *a0);
    extern s32 func_8012CC64(s32 a0, void *a1);
    extern s32 func_80133784(s32 a0, void *a1, s32 a2);
    extern void func_8012E688(s32 arg0, s32 arg1, s32 arg2);
    extern void func_8012B23C(s32 a0);
    extern void func_8012B1B4(s32 a0, s32 a1);
    extern s32 rand(void);
    extern s32 D_801C6FC4;
    extern s32 D_801C6FA8;

    s32 e;
    s32 n;
    s32 dir;

    e = arg0;
    if (--*(s16 *)(e + 0xFC) == 0) {
        n = 0;
        do {
            arg0 = *(s32 *)(arg0 + 0x6C);
            n++;
        } while (arg0 != 0);
        if (n < 7) {
            if (e != 0) {
                arg0 = e;
                for (;;) {
                    e = *(s32 *)(arg0 + 0x6C);
                    func_8012C218((void *)arg0);
                    arg0 = e;
                    __asm__ __volatile__("" : "=r"(arg0) : "0"(arg0));
                    if (arg0 == 0) {
                        return;
                    }
                }
            }
            return;
        }
    }

    {
        s32 f;

        *(s16 *)(*(s32 *)(e + 0x20) + 0x14) += 0x40;
        *(s16 *)(*(s32 *)(e + 0x20) + 0x14) &= 0xFFF;
        f = func_8012CC64(e, &D_801C6FC4);

        if (f & 0x1000) {
            *(s16 *)(e + 0x2) = 0x12;
            return;
        }

        n = 0;
        if (f & 0xC000) {
            s16 p1[3];
            s16 p2[3];

            {
                s16 *q = p2;
                s32 x;
                s32 y;
                s32 z;

                *(s16 *)(e + 0x16) = -(rand() & 3) - 8;
                x = *(u16 *)(e + 6);
                p1[0] = x - 0x20;
                y = *(u16 *)(e + 0xA) + 0x10;
                p1[1] = y;
                z = *(u16 *)(e + 0xE) + 0x20;
                p1[2] = z;
                q[0] = x + 0x20;
                q[1] = y;
                q[2] = z;

                if (func_80133784(1, p1, (s32)q) != 0) {
                    n = 1;
                    *(s16 *)(e + 0x12) = -(rand() & 3) - 4;
                } else {
                    q[0] = p1[0] + 0x40;
                    q[1] = p1[1];
                    q[2] = p1[2];
                    if (func_80133784(1, q, (s32)p1) != 0) {
                        n = 2;
                        *(s16 *)(e + 0x12) = (rand() & 3) + 4;
                        __asm__ __volatile__(""); /* cookbook 5a cross-jump barrier vs the n==1 arm */
                    }
                }
            }
            {
                s16 *q = p2;
                s32 x;
                s32 y;
                s32 z;

                x = *(u16 *)(e + 6);
                p1[0] = x;
                y = *(u16 *)(e + 0xA) + 0x10;
                p1[1] = y;
                z = *(u16 *)(e + 0xE);
                p1[2] = z;
                q[0] = x;
                q[1] = y;
                q[2] = z + 0x40;

                if (func_80133784(1, p1, (s32)q) != 0) {
                    n += 4;
                    *(s16 *)(e + 0x1A) = -(rand() & 3) - 4;
                } else {
                    q[0] = p1[0];
                    q[1] = p1[1];
                    q[2] = p1[2] + 0x40;
                    if (func_80133784(1, q, (s32)p1) != 0) {
                        n += 8;
                        *(s16 *)(e + 0x1A) = (rand() & 3) + 4;
                        __asm__ __volatile__(""); /* cookbook 5a cross-jump barrier vs the n+=4 arm */
                    }
                }
            }

            switch (n - 1) {
            case 0:
                dir = 0x800;
                break;
            case 1:
                dir = 0;
                break;
            case 3:
                dir = 0x400;
                break;
            case 4:
                dir = 0x600;
                break;
            case 5:
                dir = 0x200;
                break;
            case 7:
                dir = 0xC00;
                break;
            case 8:
                dir = 0xA00;
                break;
            case 9:
                dir = 0xE00;
                break;
            }
            *(s16 *)(*(s32 *)(e + 0x20) + 0x12) = dir;
        } else if (f & 0x2000) {
            func_8012E688(e, 0x833, 0);
            if ((rand() & 0xF) == 0) {
                s32 t1;
                s32 t2;
                s32 t3;
                s32 p;

                *(s16 *)(*(s32 *)(e + 0x20) + 0x14) = 0;
                t1 = *(u16 *)(e + 6);
                t2 = *(u16 *)(e + 0xA);
                t3 = *(u16 *)(e + 0xE);
                *(s16 *)(e + 0x2) = 1;
                *(s16 *)(e + 0x34) = 1;
                *(s16 *)(e + 0x70) = 0;
                *(s16 *)(e + 0x88) = t1;
                *(s16 *)(e + 0x8A) = t2;
                *(s16 *)(e + 0x8C) = t3;
                func_8012B23C(e);
                func_8012B1B4(e, (s32)&D_801C6FA8);
                p = *(s32 *)(e + 0x6C);
                if (p != 0) {
                    do {
                        *(s16 *)(p + 0x2) = 2;
                        *(s16 *)(p + 0x70) -= 0x10;
                        *(s16 *)(*(s32 *)(p + 0x20) + 0x14) = 0;
                        p = *(s32 *)(p + 0x6C);
                    } while (p != 0);
                }
                *(s16 *)(e + 0xFC) = 0;
            } else {
                *(s16 *)(e + 0x16) = -(rand() & 3) - 8;
            }
        }
    }

    if (*(s16 *)(e + 0xA) >= 0x65) {
        func_8012C218((void *)e);
    }
}


#include "common.h"

extern void func_8012C218(void *a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void RotTransSV(void *a0, void *a1, void *a2);

#define SRM_80186B78(r0) __asm__ __volatile__( \
    "lw $12, 0(%0)\n"  \
    "lw $13, 4(%0)\n"  \
    "ctc2 $12, $0\n"   \
    "ctc2 $13, $1\n"   \
    "lw $12, 8(%0)\n"  \
    "lw $13, 12(%0)\n" \
    "lw $14, 16(%0)\n" \
    "ctc2 $12, $2\n"   \
    "ctc2 $13, $3\n"   \
    "ctc2 $14, $4\n"   \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

#define STM_80186B78(r0) __asm__ __volatile__( \
    "lw $12, 20(%0)\n" \
    "lw $13, 24(%0)\n" \
    "ctc2 $12, $5\n"   \
    "lw $14, 28(%0)\n" \
    "ctc2 $13, $6\n"   \
    "ctc2 $14, $7\n"   \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

void func_80187674(s32 a0)
{
    u16 out[4];      /* sp+0x10 */
    s16 sv[4];       /* sp+0x18 */
    s16 pos[4];      /* sp+0x20 */
    s32 flag;        /* sp+0x28 */
    s16 *p;

    if (*(s16 *)(*(s32 *)(a0 + 0x64) + 0x36) != *(s16 *)(a0 + 0xFE)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    if (*(s16 *)(a0 + 0x70) == 0x11) {
        s32 ang;
        s32 t;
        ang = (*(u16 *)(a0 + 0xFC) + 0x40) & 0xFFF;
        p = *(s16 **)(a0 + 0xCC);
        *(s16 *)(a0 + 0xFC) = ang;
        t = (func_8004787C(ang) >> 6) + 0xBF;
        p[2] = t;
        p[1] = t;
        p[0] = t;
    }

    if (*(s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 4) < 0) {
        { register s32 *q __asm__("$3"); q = *(s32 **)(a0 + 0x20);
          q[1] = q[1] | 0x80000000; }
    } else {
        __asm__ __volatile__("");
        *(s32 *)(*(s32 *)(a0 + 0x20) + 4) =
            *(s32 *)(*(s32 *)(a0 + 0x20) + 4) & 0x7FFFFFFF;
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x18);

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x14);

    {
        s32 ang;
        s32 ang2;

        ang = (*(u16 *)(a0 + 0x102) + *(u16 *)(a0 + 0x106)) & 0xFFF;
        *(s16 *)(a0 + 0x102) = ang;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = func_80047948(ang) >> 3;

        ang2 = (*(u16 *)(a0 + 0x104) + *(u16 *)(a0 + 0x100)) & 0xFFF;
        *(s16 *)(a0 + 0x104) = ang2;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_80047948(ang2) >> 3;

        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        SRM_80186B78((s32 *)(*(s32 *)(a0 + 0x20) + 0x34));
        STM_80186B78((s32 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x34));

        p = *(s16 **)(a0 + 0xD0);
        sv[0] = 0;
        sv[1] = 0;
        sv[2] = (p[2] * *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18)) >> 12;
        RotTransSV(sv, out, &flag);

        *(s16 *)(a0 + 6) = out[0];
        *(s16 *)(a0 + 0xA) = out[1];
        *(s16 *)(a0 + 0xE) = out[2];
    }
    { s32 pad[2]; }   /* LEVER 1: frame pad -- matches func_80186B78's byte-verified 8-byte
                         trailing dead local (docs/matching-cookbook.md §136 L6). */
}


INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_801878B8);

#include "common.h"

extern u8 *func_8012913C(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);
extern void func_801292C8(u8 *a0);

typedef struct {
    u16 x, y, z;
    u8 flag;
} V8_80187968;

void func_80187968(s32 a0) {
    u32 v0;
    u8 *s1;

    v0 = *(u16 *)(a0 + 0x10A) + 1;
    *(u16 *)(a0 + 0x10A) = v0;

    if ((v0 & 7) == 0) {
        s1 = func_8012913C(0x7B);
        if (s1 != 0) {
            V8_80187968 p1;
            V8_80187968 q;

            v0 = *(u16 *)(a0 + 0x10A);
            *(s32 *)(s1 + 0x2C) = (v0 & 0x18) >> 3;

            p1.x = *(u16 *)(a0 + 0x6);
            p1.y = *(u16 *)(a0 + 0xA);
            p1.z = *(u16 *)(a0 + 0xE);
            q.x = p1.x;
            q.y = p1.y + 0x80;
            q.z = p1.z;

            func_80133784(1, &p1, (s32)&q);

            if (q.flag) {
                *(u16 *)(s1 + 0x6) = *(u16 *)(a0 + 0x6);
                *(u16 *)(s1 + 0xA) = q.y;
                *(u16 *)(s1 + 0xE) = *(u16 *)(a0 + 0xE);
            } else {
                func_801292C8(s1);
            }
        }
    }
}



extern void (*D_801C705C[])(void);

void func_80187A4C(void *a0) {
    D_801C705C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80187A88);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80187AEC);

extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012B23C(s32 a0);
extern void func_8012B1B4(s32 a0, s32 a1);

void func_80187B80(s32 a0)
{
    extern u8 D_801C6FA8[];
    u16 out[4];
    u16 pos[4];
    u16 t0, t1, t2;

    *(u16 *)(a0 + 0x5C) = 0xA810;
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x34);

    t0 = *(u16 *)(a0 + 0x6);
    pos[0] = t0;
    out[0] = t0;
    t1 = *(u16 *)(a0 + 0xA);
    pos[1] = t1;
    out[1] = t1 - 0x18;
    t2 = *(u16 *)(a0 + 0xE);
    pos[2] = t2;
    out[2] = t2;
    func_8012CEB0((s32)out, (s32)pos, 1);

    *(u16 *)(a0 + 0xA) = pos[1] - 0x10;

    if (*(s16 *)(a0 + 0x70) == 0xF) {
        s32 c;

        c = *(s32 *)(a0 + 0x20);
        *(u16 *)(c + 0x14) = 0;

        *(u16 *)(a0 + 0x2) = 1;
        *(u16 *)(a0 + 0x34) = 1;
        *(u16 *)(a0 + 0x70) = 0;
        *(u16 *)(a0 + 0x88) = *(u16 *)(a0 + 0x6);
        *(u16 *)(a0 + 0x8A) = *(u16 *)(a0 + 0xA);
        *(u16 *)(a0 + 0x8C) = *(u16 *)(a0 + 0xE);
        func_8012B23C(a0);
        func_8012B1B4(a0, (s32)D_801C6FA8);

        {
            s32 n = *(s32 *)(a0 + 0x6C);
            while (n != 0) {
                *(u16 *)(n + 0x2) = 2;
                *(u16 *)(n + 0x70) = *(u16 *)(n + 0x70) - 0x10;
                *(u16 *)(*(s32 *)(n + 0x20) + 0x14) = 0;
                n = *(s32 *)(n + 0x6C);
            }
        }
        *(u16 *)(a0 + 0xFC) = 0;
    } else {
        func_8012B23C(a0);
        func_8012B1B4(a0, (s32)D_801C6FA8);
    }
}


extern void func_8012E688(s32 *a0, s32 a1, s32 a2);
    void func_80187CA8(void *a0) {
        if (*(s16 *)((s32)a0 + 0x76) > 0) {
            func_8012E688(a0, 0x8C6, 0);
        }
    }




extern void func_8012E688(s32*, s32, s32);
    extern void func_8002AC00(s32 arg0);
    void func_80187CD8(void *arg0) {
        ((void (*)(s32, s32, s32))func_8012E688)((s32)arg0, 0x8C7, 0);
        func_8002AC00(0x10);
    }


DEFINE_func_80187D04()  /* dedup: shared engine-core @0x80187D04 (src/shared) */

#include "common.h"

void func_80187D0C(s32 a0)
{
    extern void func_8012BE98(s32 a0, u16 *a1);
    extern s32  func_8012B744(void *a0, void *a1);
    extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
    extern void func_8012B1B4(s32 a0, s32 a1);
    extern s32  func_8012BD3C(s32 a0, s32 a1, s32 a2);
    extern void func_8012CC40(s32 arg0, s32 arg1);
    extern s32  func_8012C0EC(s32 a0);
    extern u8   D_801C6FA8[];
    extern s32  D_801C6FC4;

    s32 anim = a0 + 0x88;

    if (((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)anim) >= 0x4000) {
        s32 d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              func_8012B744((void *)(a0 + 4), (void *)anim), 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
        func_8012B1B4(a0, (s32)D_801C6FA8);
    } else {
        if (func_8012BD3C(a0, 0x200, 0x40000) == 1) {
            *(s16 *)(a0 + 0x2) = 3;
        }
    }

    if ((((s32 (*)(s32, s32))func_8012CC40)(a0, (s32)&D_801C6FC4) & 0x1000) != 0) {
        *(s16 *)(a0 + 0x2) = 0x12;
    } else {
        func_8012C0EC(a0);
    }
}


INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80187DF8);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80187E78);

#include "common.h"

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern void func_8012E688(s32*, s32, s32);

void func_80187F2C(s32 a0)
{
    *(s32 *)(a0 + 0x8) -= 0x80000;
    *(s32 *)(a0 + 0x4) += func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) << 7;
    *(s32 *)(a0 + 0xC) += func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) << 7;

    if (--*(s16 *)(a0 + 0xFE) == 0) {
        if (func_8012BCCC(a0) < 0x4001) {
            if (func_8012BDBC(a0, 0x200) == 1) {
                *(s16 *)(a0 + 0x2) = 5;
                *(s16 *)(a0 + 0xFE) = 4;
                ((void (*)(s32, s32, s32))func_8012E688)(a0, 0x98F, 0);
            } else {
                *(s16 *)(a0 + 0x2) = 7;
            }
        } else {
            *(s16 *)(a0 + 0x2) = 7;
        }
    }
}


INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_8018800C);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188074);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_801880D4);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188164);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_801881D8);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188228);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_801882A8);

extern int func_8012C658(int arg0, int arg1, int arg2);
extern void func_80186B78(int a0);

void func_80188348(int a0)
{
    short cnt;
    int v1;

    *(short *)(a0 + 0x2) = 2;
    cnt = *(unsigned short *)(a0 + 0x70) + 1;
    *(unsigned short *)(a0 + 0x70) = cnt;

    if (cnt < 7) {
        v1 = func_8012C658(0x1EA, cnt, a0);
        if (v1 != 0) {
            *(unsigned short *)(v1 + 0xFE) = *(unsigned short *)(a0 + 0x36);
            *(unsigned short *)(v1 + 0x108) = (*(unsigned short *)(a0 + 0x70) - 1) << 9;
        }
    }

    cnt = *(short *)(a0 + 0x70);
    if (cnt >= 8) {
        if (cnt < 14) {
            v1 = func_8012C658(0x1EA, cnt, a0);
            if (v1 != 0) {
                *(unsigned short *)(v1 + 0xFE) = *(unsigned short *)(a0 + 0x36);
            }
        }
    }

    *(unsigned short *)(a0 + 0x70) = *(unsigned short *)(a0 + 0x70) - 1;
    func_80186B78(a0);
}


INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188418);


















extern void func_8012C218(void *a0);
void func_801884AC(void *a0)
{
register s32 v0 __asm__("$2");
register s32 v1 __asm__("$3");
  v0 = (*((s32 *) (((s32) a0) + 0x8)) = (*((s32 *) (((s32) a0) + 0x8))) + 0x40000);
  v1 = 0x400000;
  if (v1 < v0)
  {
    v1 = v1 / 65536;
    ((s32 (*)(s32)) func_8012C218)((s32) a0);
  }
}


extern u8 D_801202A0[];
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);

void func_801884E8(void *a0)
{
    u8 *p;
    s32 cnt;
    s32 i;
    s16 st;
    s32 q;
    s16 t;

    p = D_801202A0;
    cnt = 0;
    for (i = 0; i < 0x60; i++) {
        if (*(u16 *)p == 0x1EA) {
            st = *(s16 *)(p + 0x70);
            if (st == 0 || st == 7 || st == 0xF) {
                cnt++;
            }
        }
        p += 0x10C;
    }

    if (cnt < 2) {
        p = (u8 *)func_8012C658(0x1EA, 0, (s32)a0);
        if (p != 0) {
            t = rand() & 0xFFF;
            q = *(s32 *)(p + 0x20);
            *(u16 *)(q + 0x12) = t;
            {
                s32 rr = rand() & 0x7F;
                s32 xx = *(u16 *)(p + 0x6) - 0x40;
                *(u16 *)(p + 0x6) = xx + rr;
            }
            {
                s32 rr = rand() & 0x7F;
                s32 xx = *(u16 *)(p + 0xE) - 0x40;
                *(u16 *)(p + 0xE) = xx + rr;
            }
        }
    }
}


extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern u8 D_801D45D8[];

void func_801885D0(void *a0)
{
    s32 s1;
    u8 *p;

    s1 = *(s32 *)((s32)a0 + 0x20);
    p = D_801D45D8 + *(s32 *)((s32)a0 + 0x2C) * 0x40;
    func_8001CD50(s1, (s32)p);
    *(s16 *)(s1 + 0x1E) = 0xCCC;
    *(s16 *)(s1 + 0x10) = 0x400;
    *(s16 *)(s1 + 0x1A) = 0;
    *(s16 *)(s1 + 0x18) = 0;
    *(s32 *)(s1 + 4) = *(s32 *)(s1 + 4) | 0x50000000;
    func_800233CC(p, 0x80);
    p[2] = 0xFF;
    p[1] = 0xFF;
    p[0] = 0xFF;
    p[5] = 0x40;
    p[4] = 0x40;
    p[6] = 0x80;
    *(s32 *)((s32)a0 + 0x1C) = 0x10;
    *(u16 *)((s32)a0 + 2) = *(u16 *)((s32)a0 + 2) + 1;
}


/* Declaration reconciliation with src/ov_SC03_118/ov_SC03_118_jr_8017FB84.c:
 *  - D_801D45D8: the TU already declares it at line 4526 as `extern u8 D_801D45D8[];`
 *    (used by the banked func_801885D0 just above the splice point). The draft had
 *    `extern s32 D_801D45D8[]` -> "conflicting types". Lever (A): conform the decl
 *    VERBATIM and keep the disagreement at the use site, which already casts the
 *    decayed pointer to s32. Zero bytes change.
 *  - func_801292C8: not declared anywhere in this TU, but src/shared/engine_core.h
 *    declares it as `extern void func_801292C8(u8 *a0);` inside four DEFINE_ macros
 *    (6304/8491/13623/13794). None of those macros is expanded in this TU today, but
 *    conforming to that shape now makes the splice conflict-proof if one ever is.
 *    $a0 already holds the incoming pointer, so passing it costs no instruction
 *    (jal + nop delay slot, exactly as in the target).
 */
extern u8 D_801D45D8[];

extern void func_801292C8(u8 *a0);

void func_80188694(void *a0) {
    s32 v0;
    s32 v1;
    s32 a1;
    s32 a2;
    u8 *v1ptr;

    v0 = *(s32 *)((s32)a0 + 0x1C);
    v1 = *(s32 *)((s32)a0 + 0x2C);
    a1 = v0 - 1;
    /* §21 zero-byte re-tie barrier: without it gcc's scheduler hoists the 0x2C load
     * (and its sll) ahead of the 0x1C load + addiu pair -- the 4-slot SCHEDULE-REORDER
     * residual. Folding the shift into the address expression fixes the order but then
     * swaps $v0/$v1 across the sll/lui pair (REGALLOC-PERM). The re-tie keeps the
     * in-place `v1 <<= 6` form (so the shift stays in $v1) AND anchors it after the
     * two loads. Emits no code. */
    __asm__ __volatile__("" : "=r"(v1) : "0"(v1));
    v1 = v1 << 6;
    a2 = (s32)D_801D45D8 + v1;
    v1ptr = *(u8 **)((s32)a0 + 0x20);

    *(s32 *)((s32)a0 + 0x1C) = a1;

    if (!(a1 == -1)) {
        v0 = 0x10 - a1;
        *(u16 *)((s32)v1ptr + 0x1A) = v0 << 8;
        *(u16 *)((s32)v1ptr + 0x18) = v0 << 8;

        v1 = *(s32 *)((s32)a0 + 0x1C);
        v0 = (v1 << 8) - v1;
        if (v0 < 0) {
            v0 = v0 + 0xF;
        }
        v0 = (u32)v0 >> 4;

        *(u8 *)(a2 + 0x2) = v0;
        *(u8 *)(a2 + 0x1) = v0;
        *(u8 *)(a2 + 0x0) = v0;

        v0 = *(s32 *)((s32)a0 + 0x1C) << 2;
        *(u8 *)(a2 + 0x5) = v0;
        *(u8 *)(a2 + 0x4) = v0;

        *(u8 *)(a2 + 0x6) = *(s32 *)((s32)a0 + 0x1C) << 3;
    } else {
        func_801292C8((u8 *)a0);
    }
}


INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188748);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188788);

extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

s32 func_801887DC(s32 a0, s16 a1, s16 a2) {
    s16 p1[3];
    s16 p2[3];
    s32 t;
    s32 result;

    p1[0] = *(u16 *)(a0 + 6);
    p1[1] = *(u16 *)(a0 + 0xA);
    p1[2] = *(u16 *)(a0 + 0xE);

    t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF) * a1;
    p2[1] = p1[1];
    p2[0] = p1[0] - (t >> 12);

    t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF) * a1;
    p2[2] = p1[2] - (t >> 12);

    result = func_80133784(1, p1, (s32)p2);

    if ((result & 0x8000) && a2) {
        t = func_8004787C(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF) * a1;
        p1[1] = p2[1];
        p1[0] = p2[0] + (t >> 12);

        t = func_80047948(*(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF) * a1;
        p1[2] = p2[2] + (t >> 12);

        result = func_80133784(1, p2, (s32)p1);

        *(s16 *)(a0 + 6) = p1[0];
        *(s16 *)(a0 + 0xA) = p1[1];
        *(s16 *)(a0 + 0xE) = p1[2];

        if (!(*(u16 *)(a0 + 0x84) & 2)) {
            *(u16 *)(a0 + 0x84) |= 2;
        }
    } else {
        *(u16 *)(a0 + 0x84) &= ~2;
    }

    return result;
}


INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188990);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188C8C);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188DE4);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188E8C);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188EB0);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188F14);

DEFINE_func_80188F90()  /* dedup: shared engine-core @0x80188F90 (src/shared) */


INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80188FB0);

INCLUDE_ASM("asm/ov_SC03_118/nonmatchings/ov_SC03_118_jr_801863CC", func_80189074);


extern void (*D_801D1070[])(void);

void func_8018913C(void *a0) {
    D_801D1070[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conform VERBATIM to the ones already present in
 * src/ov_SC03_014/ov_SC03_014_jr_801848E4.c (lines 58, 2524, 2527, 3139,
 * 3222, 3244, 3245).  Type mismatches are resolved by casting AT THE USE. */
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80029178(s32 arg);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern s32 func_8012A828(void*, void*);
/* not declared anywhere in the TU */
extern void func_80189824(void);

void func_80189178(void *a0) {

    extern s32 D_801D0DC8[];
    extern u8 D_801D0D60[];
    extern u8 D_80189C94[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801D0D60);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801D0DC8[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_80189824);
        *(s32 *)((s32)a0 + 0xCC) = res2;
    } else {
        val = *(s16 *)((s32)a0 + 0x70);
        val |= 0x4000;
        *(s16 *)((s32)a0 + 0x70) = val;
    }

    res2 = func_8012C658(0x8F, *(s16 *)((s32)a0 + 0x70), (s32)a0);
    *(s32 *)((s32)a0 + 0x6C) = res2;

    if (res2 == 0) {
        func_8012CAE4(a0);
    } else {
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_80189C94);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_8018924C(void *a0) {
    void *p1, *p2;
    u16 val;
    long x;

    p1 = *(void **)(a0 + 0x20);
    p2 = *(void **)(a0 + 0x6C);
    val = *(u16 *)(p1 + 0x12);
    p2 = *(void **)(p2 + 0x20);
    val += 0x800;
    val &= 0xFFF;
    *(u16 *)(p2 + 0x12) = val;
    x = 2;
    *(u16 *)(a0 + 0x2) = x;
    return x;
}


DEFINE_func_80189274()  /* dedup: shared engine-core @0x80189274 (src/shared) */


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_8018927C(void *a0) {

    extern s32 D_801D0FAC;
    extern s32 D_801D0F98;
    extern s32 D_801D0F94;
    extern s32 D_801D102C;
    extern s32 D_801D0FC0;
    extern s32 D_801D0E8C[];
    extern s32 D_801D0F10[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801D0FAC = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801D0F94 = 0;
                D_801D0F98 = D_801D0F10[v0];
            } else {
                D_801D0F98 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801D0F10[v0], 1);
                D_801D0F94 = 2;
            }
        } else {
            D_801D0FAC = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801D0F94 = 0;
            D_801D0F98 = D_801D0E8C[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801D0FC0);
    } else {
        p = &D_801D102C;
        *p = *(s32 *)((char *)s0 + 0x0);
        func_80178CBC((s32)a0, (s32)(p - 7));
    }

    *(u16 *)(a0 + 0x2) = 4;
    *(u16 *)(a0 + 0x70) |= 0x8000;
}




/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (lines 43, 45, 58, 65, 2528, 2538, 2712, 3177, 3282).
 * Type mismatches resolved by casting AT THE USE (func_80178D18). */
extern s32 func_801789AC(s32 arg0);
extern void func_80178D18(void);
extern s32 func_80029178(s32 arg);
extern void func_80029514(s32);
extern void func_80029124(s32, s32);
extern void func_80145EE8(s32 param_1);
extern void func_8012C218(void *a0);
extern s32 func_801895CC(void);

void func_801893C8(void *arg0) {

    extern s32 D_801D0DC8[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801D0DC8[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801D0DC8[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_801895CC() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}


extern void func_8012C218(void *a0);
    s32 func_801894E8(void * arg0) {
        *(s16 *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32 *))func_8012C218)(*(s32 **)((char *)arg0 + 0xcc));
    }


void func_80189514(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_80189524(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_80189534(void *a0) {

    extern s32 D_801D0DC8[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801D0DC8[idx], 1);
}


extern void func_8014ADA8(s32 a0, s32 a1);
    extern s32 D_80126B58;
    void func_80189574(s32 arg0) {
        register s32 temp_v0 __asm__("$2");
        temp_v0 = *(s32 *)(arg0 + 0xdc);
        ((void (*)(s32 *, s32))func_8014ADA8)((s32 *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
    }


extern s16 func_80174764(void);
s32 func_801895A8(void) {
    return ((s32 (*)(void))func_80174764)() == 1;
}




extern s32 func_80029178(s32 arg);

s32 func_801895CC(void) {

    extern s32 D_801D0DC8[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801D0DC8[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



extern void (*D_801D1098[])(void);

void func_80189630(void *a0) {
    D_801D1098[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_8012A828(void*, void*);

void func_8018966C(void *a0) {

    extern u8 D_801D0D94[];
    extern u8 D_801D1758[];
    extern u8 D_801D1538[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801D0D94) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801D1758);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801D1538);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern s32 func_8012A828(void*, void*);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801896F4(void *a0) {

    extern u8 D_801D1548[];
    extern u8 D_801D1650[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801D1548);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801D1650);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_801897B4 — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801D1758, else
 * D_801D1538), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `((void (*)(s32, void *))func_8012A828)(entity, D_801D1758 / D_801D1538)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern s32 func_8012A828(void*, void*);

void func_801897B4(void *a0) {

    extern u8 D_801D1758[];
    extern u8 D_801D1538[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801D1758);
        } else {
            ((void (*)(s32, void *))func_8012A828)((s32)a0, D_801D1538);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801D1088[];
extern s32 func_8012BDBC(s32 a0, s32 a1);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80172710(void);
extern s32 func_80178BF8();
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

s32 aF8018A224() __asm__("func_80189824");

s32 aF8018A224(param_1)
    void *param_1;
{
    s32 *m;
    s32 obj;
    s32 sv0[2];
    s32 sv1[2];
    s32 flag;

    m = (s32 *)((u8 *)D_80126B78 + 0x34);
    obj = *(s32 *)((s32)param_1 + 0x64);

    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

    RotTransSV(D_801D1088, sv0, &flag);
    RotTransSV(D_801D1088 + 8, sv1, &flag);

    if (func_80135888(*(s32 *)(obj + 0x20), *(s32 *)(obj + 0x58), (s32)sv0, (s32)sv1) == 0) {
        return 0;
    }
    if (func_8012BDBC(obj, 0x300) == 0) {
        return 0;
    }
    *(s16 *)(obj + 0x2) = 3;
    func_80178BF8();
    return (s32)func_80172710;
}






