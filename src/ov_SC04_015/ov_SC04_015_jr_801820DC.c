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
extern u8 D_80186A70;
extern u8 D_801869E0;
extern u8 D_801869BC;
extern u8 D_80186998;
extern u8 D_80186A4C;
extern u8 D_80186A28;
extern u8 D_80186A04;
extern u8 D_80186974;
extern void func_80145934(void);
extern u8 D_80186B00;
extern u8 D_80186ADC;
extern u8 D_80186AB8;
extern u8 D_80186A94;
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
extern unsigned char D_80185EF8[];
extern unsigned char D_80185F28[];
extern unsigned char D_80185F78[];
extern unsigned char D_80185FA8[];
extern unsigned char D_80185FD8[];
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
extern void (*D_80186028[])(void *);
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
extern s32 D_801860F0[];
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
extern u8 D_80186178[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80186180;
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
extern int D_801C77B0;
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
extern s32 D_801C77B4;
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
extern s32 D_801861B0;
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
extern void (*D_80186258[])(void);
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
extern void (*D_8018627C[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018626C;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80186290[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018629C[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801862AC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801862C4[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801862B4;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801862D8[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801862F4[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801862E4;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80186308[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018631C[])(void);
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
extern s32 D_80186330;
extern void (*D_80186358[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80186338;
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
extern int (*D_801863A4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801863A8[])(void);
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
extern unsigned short D_8018680C[];
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
extern void (*D_8018681C[])(void);
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
extern int D_801C77E8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80186844[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80186824;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80186834;
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
extern void (*D_80186884[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018688C[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80186858;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80186898[])(void);
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
extern u8 D_80186868;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801C77F0;
extern s32 D_801C77FC;
extern s32 D_801C7800;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801868D4[])(s32 *);
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
extern s32 D_801868A8[];
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
extern s32 D_801C77F8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80186B24[])(void);
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
extern char D_80186944[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80186BC8[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80186D1C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80186B38;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80186D24[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80186B48;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80186B68;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80186D2C[])(void);
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
extern void (*D_80186D54[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80186D60[])(void);
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
extern void (*D_80186BD4[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80186E04;
extern void func_8015D380(s32 a0);
extern unsigned char D_80185EE8[];
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
extern unsigned char D_80186E18[];
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
extern s8 D_80186E54[];
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
extern u16 D_80186E9C;
extern u16 D_80186E9E;
extern u16 D_80186EA0;
extern s32 D_80186EA4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80186EAC;
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
extern int D_80186BB8;
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
extern unsigned int D_80186F30[];
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
extern void (*D_80186FE0[])(void);
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
extern u16 D_80187010[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80187074;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801C7808[];
extern void func_8016216C(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80187098[])(void);
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
extern int D_801C7860[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_801870E0[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801870D0;
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
extern char D_801C7084[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801870E8[])(void);
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
extern void (*D_8018713C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80187104;
extern s16 D_80187138;
extern s16 D_80187136;
extern s16 D_80187134;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80187148[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801C78C0;
extern u8 D_801C78C1;
extern u8 D_801C78C2;
extern u8 D_801C78C3;
extern u8 D_801C78C4;
extern u8 D_801C78C5;
extern u8 D_801C78C6;
extern u8 D_801C78C7;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80187158[])(void);
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
extern s32 D_801C7900;
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
extern void (*D_8018719C[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80187218[];
extern s32 D_80187238[];
extern u8 D_801872B4[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801872D4[];
extern u8 D_801872F4[];
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
extern void (*D_80187390[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018740C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801C7094;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80187418[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80187420[])(void);
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
extern void (*D_801874E8[])(void);
extern void func_80166618(void *a0);
extern void (*D_801874F8[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80187508[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80187514[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80187474[];
extern u8   D_80187488[];
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
extern void (*D_8018752C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80187534[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018753C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80187544[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018754C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80187554[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018755C[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80187610[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80187618[])(void);
extern void func_80169F00(void *a0);
extern char D_801875C8[];
extern char D_80187588[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80187650[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018765C[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_801876A4[])(void);
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
extern void (*D_80187720[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801C7C20;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80187714[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80187758[];
extern unsigned short D_80187760[];
extern unsigned short D_80187768[];
extern unsigned char D_801C7C28[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801C7C20;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80187770[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801C7D5C;
extern M2C_UNK D_801C7D60;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801C7CE8;
extern void (*D_801877A0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801C7D64[];
extern u8 D_801C7D6C[];
extern u8 D_801C7D1C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_801877A8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801877C4[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801877CC[])(void);
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
extern void (*D_80187834[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801877D8;
extern u8 D_801877E4;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80187868[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80187870[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801878C4[])(void);
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
extern u16 D_801878F8[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801878E8[];
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
extern s32 D_80187914;
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
extern void (*D_8018798C[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80187994[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018799C[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_801879A4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_801879AC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_801879B4[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_801879C0[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801879CC[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801879D8[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801879E8[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_801879F8[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80187A00[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80187A08[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80187A10[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80187A18[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80187A20[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80187A28[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80187A30[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80187A38[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80187A40[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80187A48[])(void);
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
extern void (*D_80187A50[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80187A58[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80187A60[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80187A68[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80187A70[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80187A78[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80187A80[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80187A88[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80187A90[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80187A98[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80187AA0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80187AA8[])(void);
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
extern void (*D_80187AEC[])(void);
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
extern M2C_UNK D_80187AB0;
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
extern void (*D_80187B1C[])(void);
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
extern void (*D_80187B58[])(void);
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
extern void (*D_80187BB0[])();
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
extern void (*D_80187BC0[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80187BC8[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80187D30[])();
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
extern void (*D_80187D3C[])();
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
extern M2C_UNK D_801C72DC;
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
extern s16 D_801C9368;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801C84A0;
extern short D_801C93DC;
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
extern s32 D_801C88CC;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801C88F4;
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
extern s16 D_801C88B0;
extern s32 func_8017A3B0(void);
extern short D_801C88EC;
extern short D_801C88E8;
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
extern s16 D_801C9320;
extern s16 D_801C9322;
extern s16 D_801C932C;
extern void func_8017AE2C(s32 param_1);
extern void func_8017B0E4(int param_1, int param_2);
extern s16 D_801C88B4;
extern u16 D_801C8934;
extern u16 D_801C8936;
extern u16 D_801C8938;
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
extern s16 D_801C892C;
extern s16 D_801C892E;
extern s16 D_801C8930;
extern s16 D_801C8924;
extern s16 D_801C8926;
extern s16 D_801C8928;
extern void func_8017B7A8(void);
extern s16 D_801C8944;
extern s16 D_801C8946;
extern s16 D_801C8948;
extern s16 D_801C894C;
extern s16 D_801C894E;
extern s16 D_801C8950;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801C893C;
extern short D_801C893E;
extern short D_801C8940;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801C88D4;
extern SV4 D_801C88DC;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801C88FC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801C88F8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80187F18[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80187FB8[])(void);
extern void func_8017BEBC(void *a0);
extern void (*D_80187FC0[])(void);
extern void func_8017BEF8(void *a0);
extern void (*D_80187FC8[])(void);
extern void func_8017BF34(void *a0);
extern u8 *func_8012913C(s32 a0);
extern s32 func_8012C750(s32 a0);
extern void func_8017BF70(s32 a0);
extern void func_8017C0B4(void);
extern void func_8017C120(s32 param_1);
extern void func_8017C1CC(s32 param_1);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32*, s32);
extern void func_8012B260(u8 *a0);
extern void func_8017C20C(s32 a0);
extern void func_8017C2D0(s32 a0);
extern void (*D_80187FE8[])(void);
extern void func_8017C358(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_8017C394(s32 param_1);
extern void func_8017C558(u8 *p);
extern void (*D_80187FF0[])(void);
extern void func_8017C5EC(void *a0);
extern u8 D_80187FDC;
extern void func_8017C628(s32 a0);
extern void func_8017C6CC(int a0);
extern void func_8017C730(s32 arg0);
extern s32 func_8017D674(void);
extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8001BFD0(void);
extern s32 func_8017D6FC(s32 a0);
extern void func_800D1EBC(void);
extern void func_8017D7AC(void);
extern void func_8017DA90(void);
extern s32 func_8017D83C(s32 arg0);
extern s32 func_8017D878(void);
extern void (*D_80187FF8[])(void);
extern void func_8017D8C8(void *a0);
extern void (*D_80188000[])(void);
extern void func_8017D904(void *a0);
extern void (*D_80188018[])(void);
extern void func_8017D940(void *a0);
extern void (*D_801882F0[])(void);
extern void func_8017D97C(void *a0);
extern s32 func_8017D9B8(u8 *a0);
extern void func_8017D9CC(s32 a0);
extern void func_8017D9FC(void);
extern void (*D_80188320[])(void);
extern void func_8017DB70(void *a0);
extern void func_8017DBEC(s32 a0, s32 a1);
extern void func_8017DD2C(void *a0);
extern void func_8017DBAC(s32 arg0);
extern void func_8017DBE0(u8 *a0);
extern void aF8017DBEC();
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void aF8017DD2C();
extern void (*D_80188584[])(void);
extern void func_8017DF90(void *a0);
extern s32 func_8017E004(void);
extern void func_80029124(s32 a, s32 b);
extern void func_8017E014(void);
extern void (*D_801885C0[])(void);
extern void func_8017E4E4(void *a0);
extern s32 D_801C8C64;
extern void func_8017ED00(void);
extern void (*D_801888F4[])(void);
extern void func_8017F408(void *a0);
extern s16 D_801C8B70;
extern s32 func_8017F53C(void);
extern void (*D_80188948[])(void);
extern void func_8017F54C(void *a0);
extern void (*D_801889E0[])(void);
extern void func_8017F90C(void *a0);
extern void func_80029124(s32 arg0, s32 arg1);
extern void func_8017F990(void);
extern void (*D_80188A78[])(void);
extern void func_8017FBD4(void *a0);
extern void func_8017FC58(void);
extern void (*D_80188B10[])(void);
extern void func_8017FE9C(void *a0);
extern void func_8017FF20(void);
extern void (*D_80188B74[])(void);
extern void func_80180170(void *a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80180290();
extern void func_801801AC(s32 a0);
extern void func_80180210(void);
extern s32 D_80188B5C;
extern void func_80180218(void *arg0);
extern void func_80180250(s32 a0);
extern void func_8018030C(void);
extern void func_801802EC(void);
extern void (*D_80188C10[])(void);
extern void func_80180398(void *a0);
extern s32 func_80180514(void);
extern void (*D_80189330[])(void);
extern void func_8018051C(void *a0);
extern void func_8001C214(s32, s32);
extern u32 D_80189320;
extern void func_80180558(s32 arg0);
extern void func_801805D4(void);
extern void (*D_80189368[])(void);
extern void func_801805DC(void *a0);
extern void func_80180934(void *arg0);
extern s32 func_8012AD50(void *arg0);
extern void func_80180618(void *arg0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801808E4(void);
extern void func_801809F0(void *arg0);
extern void aF801806A8();
extern void func_80017714(void *);
extern void func_80180B08(void *a0);
extern void func_80180B18(void *a0);
extern s32 func_8012E57C(s32 a0, s32 a1);
extern s32 func_80180B28(void *a0, void *a1);
extern void func_80180BC4(void *a0);
extern void func_8012A828(s32 *a0, s32 a1);
extern void func_80180BF0(s32 *a0);
extern void func_80180C1C(void *a0);
extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CB64(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern s32 aF801848DC();
extern s32 func_80180E70(s32 arg0);
extern s32 func_80180CCC(s32 a0);
extern s32 func_80180CCC(s32 arg);
extern void func_80180E30(void *a0);
extern void func_80180DFC(void *a0);
extern short D_800BA2BA;
extern void (*D_801B2954[])(void);
extern void func_80180E98(void *a0);
extern void func_80180ED4(void);
extern void func_80180EDC(void *a0, s32 a1, s32 a2);
extern s32 func_80180F18(s32 arg0, s32 arg1);
extern s32 func_80180F3C(u8 a0, u8 a1, u8 a2, u8 a3);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_80180F94(void *a0, s32 a1);
extern void func_80180FFC(s32 a0);
extern void func_8018101C(void *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_80181024(s32 *a0, s32 a1);
extern s32 func_8018106C(void);
extern s32 func_801810C8(void);
extern s32 func_8018113C(void);
extern s32 func_801811B0(void);
extern void func_80029514(s32 arg0);
extern void func_8018120C(void);
extern void func_8012B200(u8 *a0);
extern void func_80181240(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80181310(s32 a0);
extern s32 func_801814D8(s32 a0);
extern void (*D_801B2974[])(void);
extern void func_80181520(void *a0);
extern void func_8018155C(void);
extern void func_80181564(void);
extern void func_8018156C(void);
extern void func_80181574(void);
extern void func_8018157C(void);
extern void func_80181584(void *a0);
extern void func_801815C8(void);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_801815D0(s32 a0);
extern void func_80181CE4(s32 a0);
extern void func_80181C70(s32 a0);
extern void func_80181D44(s32 a0);
extern void func_80181C08(s32 a0);
extern void func_80181658(s32 a0);
extern void func_8001C97C(s32 a0);
extern void *func_80181FD8(void *a0);
extern void func_80181830(s32 a0);
extern void func_801820DC(void *a0);
extern void func_801819D0(void *a0);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern s32 func_80182258(void);
extern void func_80181A4C(s32 a0);
extern void func_80181B18(void);
extern s32 func_8012BEE8(s32 a0);
extern void func_80181B38(s32 a0);
extern void func_80181DC4(s32 a0, s32 a1);
extern void func_80182398(s32 a0, s32 a1);
extern void func_80181E1C(s32 a0);
extern void func_80181E7C(s32 a0);
extern void func_80181EC4(s32 a0);
extern void func_80181F14(s32 a0);
extern s32 func_80181F4C(s32 a0);
extern s32 func_8018207C(void *a0);
extern s32 func_80182614(void *a0);
extern void * func_80181FD8(void *a0);
/* ==== end §8b carried decl layer ==== */




extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg0);
extern s32 func_8018106C(void);
extern s32 func_801811B0(void);
extern void func_80178CBC(s32, s32);

void func_801820DC(void *a0) {

    extern u8 D_80078E78[];
    extern void *D_801B2C04[];
    extern s32 D_801B2BD4;
    extern s32 D_801B2BEC;
    register void *s2 __asm__("$18") = a0;
    register u8 *p __asm__("$17");
    register void *s0 __asm__("$16");
    s32 v0;
    s16 v1;

    v0 = func_80029504();
    v1 = *(s16 *)((s32)s2 + 0x70);
    p = D_80078E78;
    s0 = D_801B2C04[v1];
    v1 -= 8;
    switch (v1) {
    case 1:
        if (p[0x42] == 0) {
            s0 = &D_801B2BD4;
        }
        break;
    case 0:
        if (p[0x42] == 3) {
            s0 = &D_801B2BD4;
        }
        break;
    case 4:
        if ((u32)(v0 - 0x12C) < 0x12C) {
            if ((func_80029178(0xFA) & 0xFF) != 0) {
                s0 = &D_801B2BEC;
            }
        }
        break;
    case 6:
        if (p[0x42] == 6) {
            s0 = &D_801B2BD4;
        }
        if ((u32)(v0 - 0x64) < 0x1F4) {
            s0 = &D_801B2BEC;
        }
        if (func_801811B0() == 1) {
            s0 = &D_801B2BEC;
        }
        break;
    case 5:
        if (p[0x42] == 2) {
            s0 = &D_801B2BD4;
        }
        if (func_8018106C() == 3) {
            s0 = &D_801B2BEC;
        }
        if (func_801811B0() == 1) {
            s0 = &D_801B2BEC;
        }
        break;
    }
    ((void (*)(s32, s32))func_80178CBC)((s32)s2, (s32)s0);
}


/*
 * Declaration reconciliation (byte-neutral) — these notes MUST travel with the body.
 *
 * 1. func_80182258 (the function being defined).  This TU already carries the
 *    canonical declaration
 *        extern s32 func_80182258(void);
 *    FIVE times above the splice point (L7450, L7492, L7504, L7534, L7559), and
 *    its banked callers reach it through `((void (*)(s32))func_80182258)(x)`
 *    casts.  The real function takes one argument and returns void, so defining
 *    it under its own C name collides:
 *        7740: conflicting types for `func_80182258'
 *        7559: previous declaration of `func_80182258'
 *    Fix = the §37/§124 asm-label alias: define under the C name aF80185EEC
 *    carrying __asm__("func_80182258").  The emitted symbol is unchanged, the
 *    C-level name never meets the canonical declaration, blast radius is zero.
 *
 * 2. func_8018228C (a callee).  The TU DEFINES it BELOW the splice point
 *    (pre-splice L7740) as
 *        void func_8018228C(void *a0)
 *    so the invented prototype `extern void func_8018228C(s32 a0);` conflicted
 *    with that later definition:
 *        7753: conflicting types for `func_8018228C'
 *        7738: previous declaration of `func_8018228C'
 *    Fix = conform the prototype to the TU's own signature and push the type
 *    disagreement to a cast at the call site.  Casting an s32 to void * emits
 *    no instruction, so this is byte-neutral.
 *
 * match_one.py still reports MATCH (13/13) after both changes.
 */

extern void func_8018228C(void *a0);

void aF80185EEC(s32 a0) __asm__("func_80182258");

void aF80185EEC(s32 a0) {
    u16 v0;
    s32 v1;

    v0 = *(u16 *)(a0 + 0xFE);
    v1 = *(s32 *)(a0 + 0x20);
    v0 = -v0;
    *(s16 *)(a0 + 0xF4) = v0;
    *(s32 *)(v1 + 0x20) = a0 + 0xEC;
    func_8018228C((void *)a0);
}



void func_8018228C(void *a0) {
    if (*(u16 *)(a0 + 0x2) != 4) {
        *(s16 *)(a0 + 0x5C) = 0x800;
    } else if (*(s32 *)(a0 + 0xCC) != 1) {
        *(s16 *)(a0 + 0x5C) = 0;
    } else {
        *(s16 *)(a0 + 0x5C) = 0x800;
    }
}



extern s32 func_8012E57C(s32 a0, s32 a1);

void func_801822C0(void *a0, s32 a1, s32 a2) {
    s32 v1 = func_8012E57C(0x61, (s32)(s16)a1);
    if (v1 != 0) {
        s32 v0 = *(s32 *)((char *)v1 + 0xCC);
        if (v0 == 0) {
            *(s32 *)((char *)v1 + 0xCC) = a2;
            *(s32 *)((char *)v1 + 0xD0) = (s32)a0;
        }
    }
}




extern s32 func_8012E57C(s32 a0, s32 a1);

void func_80182324(s32 a0, s32 a1, s32 a2) {
    s32 s1;
    s32 s0;
    s32 v1;
    s32 shift_temp;

    s1 = a0;
    s0 = a2;
    shift_temp = ((a1 << 16) >> 16);
    v1 = func_8012E57C(0x61, shift_temp);
    if (v1 == 0) {
        return;
    }
    if (*(s32 *)((char *)v1 + 0xCC) != s0) {
        return;
    }
    if (*(s32 *)((char *)v1 + 0xD0) != s1) {
        return;
    }
    *(s32 *)((char *)v1 + 0xCC) = 0;
    *(s32 *)((char *)v1 + 0xD0) = 0;
}




extern s32 func_8012E57C(s32 a0, s32 a1);

void func_80182398(s32 a0, s32 a1) {
    s32 v1 = func_8012E57C(0x61, (s32)(s16)a0);
    if (v1 != 0) {
        if (*(s16 *)(v1 + 0x10A) < a1) {
            *(s16 *)(v1 + 0x10A) = a1;
        }
    }
}



extern void (*D_801B2C70[])(void);

void func_801823F0(void *a0) {
    D_801B2C70[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);

void func_8018242C(void *a0)
{

    extern s32 D_801B2C60;
    s32 v0;
    u16 v0_2;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)a0 + 0x20) = v0;

    if (v0 == 0) {
        ((void (*)(void *))func_8012CAE4)(a0);
    } else {
        ((void (*)(s32, s32))func_8001C214)(v0, 0);

        *(s32 *)((u8 *)a0 + 0x58) = (s32)&D_801B2C60 | 0x40000000;
        v0_2 = *(u16 *)((u8 *)a0 + 0x2);
        *(u16 *)((u8 *)a0 + 0x34) = 0;
        *(s32 *)((u8 *)a0 + 0x1C) = 0;
        *(u16 *)((u8 *)a0 + 0x5C) = 0x800;
        *(u16 *)((u8 *)a0 + 0x2) = v0_2 + 1;
    }
}




/* func_801824A8 — scan the 96-entry / 0x10C-stride D_801202A0 actor table for
 * the lowest-scoring slot whose u16 tag at +0 is 0x61, then splat 3 words plus
 * an align-1 8-byte block into the caller's struct.
 *
 * Byte-verified idioms (all four were needed; each was a real residual):
 *
 *  1. The 0x61 compare constant is NOT a source variable. gcc keeps it in a
 *     callee-saved reg and LICM sinks the `li` into the loop PREHEADER, so
 *     `addiu $s5,$zero,0x61` lands AFTER the guard branch's delay slot. Pinning
 *     an `s5` local puts the `li` in the entry block instead (+1 wrong slot).
 *
 *  2. The 8-byte copy at +0x10 is ONE align-1 struct assign, not two 4-byte
 *     ones. gcc's MIPS block move loads BOTH words first (lwl/lwr $a0,
 *     lwl/lwr $a1) then stores both; splitting it emits load/nop/store twice
 *     and costs an instruction (cookbook-index: "align-1 4xu8 struct assign
 *     emits the inline form").
 *
 *  3. The parameter must NOT be register-pinned. With `register u8 *s2
 *     __asm__("$18")` the entry-block `move` is a schedulable body insn and
 *     the list scheduler ranks the higher-priority `lui $s0` chain ahead of
 *     it, so the anti-dependent prologue `sw`s come out in regno order
 *     (s0,s1,s2,s3) instead of the target's def order (s2,s0,s1,s3). Letting
 *     gcc allocate the incoming parameter itself keeps the copy first and the
 *     whole prologue falls into place. (The other five pins are still needed.)
 *
 *  4. After the block store, gcc-2.7.2 CSE has invalidated memory, so
 *     a0->0x20 is RELOADED into a second pseudo — two separate C variables,
 *     not one reused variable (one variable => one pseudo => $a3 for both).
 *     The destination pointer must also be loaded BEFORE the source pointer:
 *     that source order is what lets the scheduler hoist `lw $v1,0x20($s2)`
 *     up into the first word-copy's load-delay slot.
 */

extern s32 func_8012BD14(s32 a0);

/* align-1 8-byte payload — drives the lwl/lwr + swl/swr inline block move */

void func_801824A8(void *a0)
{

    extern u8 D_801202A0[];
    register u8 *s0 __asm__("$16");
    register s32 s1 __asm__("$17");
    register u8 *s3 __asm__("$19");
    register u8 *s4 __asm__("$20");
    u8 *s2;
    u8 *v0;
    u8 *v1;
    u8 *a0p;

    s2 = (u8 *)a0;
    s0 = D_801202A0;
    s1 = 0x7FFF;
    s3 = s0 + 0x6480;

    while (s0 != s3) {
        if (*(u16 *)s0 == 0x61) {
            s32 v1_val = func_8012BD14((s32)s0);
            if (v1_val < s1) {
                s1 = v1_val;
                s4 = s0;
            }
        }
        s0 += 0x10C;
    }

    s0 = s4;
    if (s1 == 0x7FFF) {
        *(s16 *)((s32)s2 + 0x5C) = 0;
    } else {
        *(s32 *)(s2 + 0x4) = *(s32 *)(s0 + 0x4);
        *(s32 *)(s2 + 0x8) = *(s32 *)(s0 + 0x8);
        *(s32 *)(s2 + 0xC) = *(s32 *)(s0 + 0xC);

        v1 = *(u8 **)(s2 + 0x20);
        v0 = *(u8 **)(s0 + 0x20);
        *(struct Un8_8018613C *)(v1 + 0x10) = *(struct Un8_8018613C *)(v0 + 0x10);

        a0p = *(u8 **)(s2 + 0x20);
        *(u16 *)(a0p + 0x12) = *(u16 *)(a0p + 0x12) - *(u16 *)(s0 + 0xFE);

        *(s16 *)((s32)s2 + 0x5C) = 0x800;
    }
}


extern s32 func_80182614(void *a0);
s32 func_801825C8(void *a0) {
    a0 = *(void **)((char *)a0 + 0xCC);
    if (a0 == 0) {
        return 0;
    }
    if (*(u16 *)a0 != 0x61) {
        return 0;
    }
    return func_80182614(a0);
}



/* func_80182614 — scan the 96-entry / 0x10C-stride D_801202A0 actor table for
 * an entry whose world position, transformed into a0's local frame, falls
 * inside the box (x in [-0xA0,0x80), y in [-0xC0,0x80)).  Returns 1 on the
 * first hit, 0 if none.
 *
 * Two idioms carry this one:
 *
 *  1. ONE source pointer, TWO induction registers.  The target walks $s1 (the
 *     record base, used for the +0 tag load and as the func_80182720 argument)
 *     and $s0 = $s1 + 0xE, which serves the +6 / +0xA / +0xE / +0x20 fields as
 *     -8 / -4 / 0 / +0x12.  That second register is loop.c's own giv: write
 *     ONE pointer `p` and address every field as `p + const`, and combine_givs
 *     rebases them all onto a single p+0xE representative.  Writing the second
 *     pointer explicitly in source is what breaks it — gcc then treats it as a
 *     second biv AND still manufactures a giv at p+0xA, giving three IV
 *     registers and +2 instructions ($s4 spill, 69 ins).
 *
 *  2. The zero-byte `__asm__("")` fence before `return 1` (cookbook §34
 *     toolkit).  Without it, reorg.c cannot fill the `beqz` delay slot from
 *     the fall-through thread (`li v0,1` clobbers the branch's own operand),
 *     leaves the slot empty, and then relax_delay_slots' "conditional jump
 *     around an unconditional jump" rule INVERTS the branch into
 *     `bnez $v0, <epilogue>` + `li $v0,1` — a strictly shorter tail (65 ins)
 *     that the original does not have.  The asm insn stops both the eager
 *     filler and the inversion test (`next_active_insn` is no longer the `j`),
 *     so reorg falls back to copying `addiu $s1,$s1,0x10C` out of the branch
 *     target and advancing the label — the target's duplicated increment.
 */

extern s32 func_80182720(s32 a0);
extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CB64(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

s32 func_80182614(void *a0) {

    extern u8 D_801202A0[];
    u8 *p;
    u8 *end;
    s32 t;
    u16 tag;
    s16 out[3];
    s16 in[3];

    p = D_801202A0;
    end = p + 0x6480;
    if (p != end) {
        do {
            tag = *(u16 *)p;
            if (tag != 0 && tag != 0x61 && func_80182720((s32)p) != 0) {
                t = *(s32 *)(p + 0x20);
                if (t != 0 && *(s32 *)(t + 0x24) != 0 && *(s32 *)(t + 0x4) >= 0) {
                    in[0] = *(u16 *)(p + 0x6);
                    in[1] = *(u16 *)(p + 0xA);
                    in[2] = *(u16 *)(p + 0xE);
                    func_8012F2E8((s32)a0, (s32)in, (s32)out);
                    if (func_8012CB64((s32)out, -0xA0, 0x80, -0xC0, 0x80) != 0) {
                        __asm__("");
                        return 1;
                    }
                }
            }
            p += 0x10C;
        } while (p != end);
    }
    return 0;
}





s32 func_80182720(s32 a0) {

    extern s16 D_801B2C78[];
    s16 *p;
    s16 v;
    s32 x;

    p = D_801B2C78;
    v = *p;
    if (*p != -1) {
        x = *(u16 *)a0;
        do {
            if (x == v) {
                return 1;
            }
            p++;
            v = *p;
        } while (*p != -1);
    }
    return 0;
}



extern void func_8012F214(s32 arg0, s32 arg1, s32 arg2);

void func_8018277C(void) {

    extern s32 D_801B2A0C;
    extern s32 D_801C9364;
    register s32 a0 __asm__("$4");
    u16 buffer[4];
    s32 val;
    s32 *p;

    func_8012F214(a0, (s32)&D_801B2A0C, (s32)buffer);

    val = buffer[0] | (((s16)buffer[2]) << 16);

    p = *(s32**)&D_801C9364;
    p[1] = val;
}




s32 func_801827BC(void)
{

    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    extern u16 D_80126B62;
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
    void func_80182820(void *arg0) {
        s32 *p = *(s32 **)((char *)arg0 + 0x20);
        *(s16 *)((char *)arg0 + 0x2) = 2;
        *(s16 *)((char *)p + 0x12) = -0x600;
        func_8012B2CC((s32)arg0);
    }


extern void func_8012B2CC(s32 a0);
    void func_80182850(void * arg0) {
        s32 temp_v1;
        temp_v1 = *(s32 *)((char *)arg0 + 0x20);
        *(s16 *)((char *)arg0 + 0x2) = 0x4;
        *(s16 *)(temp_v1 + 0x12) = 0x600;
        func_8012B2CC((s32)arg0);
    }



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_80029504(void);
extern s32 func_80029178(s32 arg);
extern void func_80182A2C(void);

void func_80182880(void *arg0) {

    extern u8 D_801C3DF4[];
    extern u8 D_801C3EE4[];
    extern u8 D_801C3EEC[];
    extern u8 D_801C3EFC[];
    s32 v0;
    s32 t;
    s32 *p;

    v0 = ((s32 (*)(void *))func_8012C1B8)(arg0);
    *(s32 *)((char *)arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(arg0);
    } else {
        func_8001C214(v0, *(s16 *)((char *)arg0 + 0x70) == 0 ? (s32)&D_801C3DF4[0] : (s32)&D_801C3EE4[0]);
        *(s16 *)((char *)arg0 + 0x5C) = 0x800;
        *(s32 *)((char *)arg0 + 0x58) =
            (s32)&D_801C3EFC[*(s16 *)((char *)arg0 + 0x70) * 0x10] | 0x40000000;
        func_8012E8E0((s32)arg0, (s32)&D_801C3EEC[*(s16 *)((char *)arg0 + 0x70) * 8]);
        *(s16 *)(*(s32 *)((char *)arg0 + 0x68) + 0xC) = 0x7FFF;
        t = func_80029504();
        if ((func_80029178(0xF6) & 0xFF) == 0 && t < 0xE6) {
            if (*(s16 *)((char *)arg0 + 0x70) == 0) {
                *(s16 *)((char *)arg0 + 0x2) = 1;
                *(s16 *)((char *)arg0 + 0x34) = 0;
                func_801788B8((s32)arg0, (s32)func_80182A2C);
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



extern void (*D_801C402C[])(void);

void func_801829F0(void *a0) {
    D_801C402C[*(u16 *)((s32)a0 + 0x2)]();
}




/* func_80182A2C — state-2 gate for the SC04_018 actor state machine.
 *
 * Reads the actor's linked object (a0->0x64), requires its state word (+0x2) == 1
 * and the actor's own +0x34 flag clear, then asks func_801827BC() for permission;
 * on success it stamps 1 into the linked object's +0x34, pokes func_80178BF8() and
 * returns the address of the next callback (func_80172710).
 *
 * DECL SURFACE (§73 / §37): the TU already carries a fleet-canonical forward decl
 *   `extern void func_80182A2C(void);`   (ov_SC04_018_jr_8017AE2C.c L7759)
 * used only to take the function's ADDRESS at L7786.  The byte-true signature
 * disagrees on BOTH §73 axes (return void->s32 AND params void->void*), so neither
 * the fleet widen nor a cast-at-use fixes it.  Instead the definition is emitted
 * under the C identifier `aF8018CB18` with an __asm__("func_80182A2C") label
 * (§37 asm-label alias, the proven function-definition form — cf.
 * src/ov_SC03_099/ov_SC03_099_after.c L533).  The C-level name never collides with
 * the canonical decl, the emitted symbol is unchanged, and codegen is byte-identical
 * (verified: match_one MATCH 31/31 with and without the alias).
 *
 * ORACLE: .venv/bin/python tools/match_one.py func_80182A2C \
 *           --c .run/s7/ov_SC04_018/func_80182A2C.c \
 *           --asm-subdir asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_8017AE2C  -> MATCH (31 ins)
 */

extern s32 func_801827BC(void);
extern s32 func_80178BF8();      /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2539) */
extern void func_80172710(void); /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2231) */

s32 aF8018CB18(void *a0) __asm__("func_80182A2C");

s32 aF8018CB18(void *a0)
{
    if (*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) != 1) {
        return 0;
    }
    if (*(u16 *)((s32)a0 + 0x34) != 0) {
        return 0;
    }
    if (func_801827BC() == 0) {
        return 0;
    }
    *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x34) = 1;
    func_80178BF8();
    return (s32)func_80172710;
}


extern void func_80029124(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800D0F4C(s32 a0);
extern s32 func_8012E57C(s32 a0, s32 a1);


void func_80182AA8(void *a0)
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





s32 func_80182B18(void) {

    extern s32 D_801C9258;
    return !(D_801C9258 ^ 2);
}


extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80182B30(void) {
        func_8002D4C8(0x7E0, 0);
    }


extern int func_80178970(void);
extern void func_80178D18(void);

/* ov_SC04_018 :: func_80182B54  — actor state machine, jump-table switch on the
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
extern void func_80182820();
extern u8   D_801C3F6C[];
extern u8   D_801C3F84[];

void func_80182B54(void *a0)
{
    s32 *p;
    s32 t;

    switch (*(u16 *)((char *)a0 + 0x34)) {
    case 0:
        break;
    case 1:
        if (func_800D0F8C(0x59) == 0) {
            func_80178CBC(a0, D_801C3F6C);
            *(u16 *)((char *)a0 + 0x34) = 2;
        } else {
            func_80178CBC(a0, D_801C3F84);
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
            func_80182820(a0);
        }
        break;
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_80182850(void *a0);

void func_80182C88(void *a0) {
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
            func_80182850(a0);
        }
    }
}


void func_80182CF0(void) {
}

void func_80182CF8(void) {
}

extern s32 D_801C90A0[];
extern s32 D_801C90BC;
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_8001D074(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);

void func_80182D00() {
    extern s32 D_801C90A0[];
    extern s32 D_801C90BC;
    s32 i;

    i = 0;
    do {
        D_801C90A0[i] = ((s32 (*)(s32, s32))func_8001D074)(0x3E, 0x7D);
        (&D_801C90BC)[i * 0x10] = 0;
        func_800233CC(&(&D_801C90BC)[i * 0x10] - 1, 0x30);
        func_8001CD50(D_801C90A0[i], (s32)(&(&D_801C90BC)[i * 0x10] - 1));
        ((s32 *)D_801C90A0[i])[1] |= 0xD0000040;
        i++;
    } while (i < 6);
}


extern s32 D_801C923C;

s32 func_80182DB4_body(s32 arg0, s32 arg1) __asm__("func_80182DB4");
s32 func_80182DB4_body(s32 arg0, s32 arg1) {
    s32 clock;

    clock = D_801C923C;
    if (arg0 > arg1) {
        if (clock < arg1) {
            clock += 0x5A0;
        }
        arg1 += 0x5A0;
    }
    if (!(arg0 < clock && clock < arg1)) {
        return -1;
    } else {
        arg0 = clock - arg0;
        if (arg0 < 0x10) {
            return arg0 * 2;
        }
        arg0 = arg1 - clock;
        if (arg0 < 0x10) {
            return arg0 * 2;
        }
        return 0x1F;
    }
}


extern s32 (*D_801C4428[])(void);
extern s32 D_801C9238;
extern void func_80182E70(u16 *a0, s32 a1);

void func_80182E1C(s32 a0)
{
    s32 v0;

    v0 = D_801C4428[a0]();
    if (v0 != -1) {
        func_80182E70((u16 *)D_801C9238, v0);
    }
}


extern void func_80182F2C(u16 *a0, s32 a1);

void func_80182E70(u16 *a0, s32 a1)
{
    extern u16 D_800B99DA;
    extern u8 D_801C4470[];

    u8 col[4];
    s32 n;
    s32 x;
    s32 h;

    if (D_801C4470[D_800B99DA & 0xF] == 0) {
        n = 0x60;
    } else {
        n = 0x50;
    }
    x = n * ++a1;
    n = x / 32;
    h = n / 2;
    col[0] = n;
    col[1] = n;
    col[2] = h;
    col[3] = 0;

    if ((s16)a0[3] != -1) {
        do {
            func_80182F2C(a0, *(s32 *)col);
            a0 += 4;
        } while ((s16)a0[3] != -1);
    }
}



/* func_80182F2C (ov_SC04_018, ov_SC04_018_jr_8017AE2C) — MATCH (250 ins)
 *
 * Shadow/marker quad renderer: builds an outer quad (D_801C4040 offset table)
 * through RotNclip4, rejects it on OTZ, builds the inner quad (D_801C40C0)
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
extern void func_80183314(void *, s32);
extern s32 RotNclip4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern s32 RotTransPers4(s32, s32, s32, s32, s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);
extern void *func_80010A08(s32);
extern s32 AddPrim(s32, void *);
extern void func_8012E28C(s32, s32);

void func_80182F2C(u16 *a0, s32 a1)
{

    extern s32 D_800A651C[][5];
    extern u16 D_801C4040[];
    extern u16 D_801C40C0[];
    extern u16 D_801C4160[][4];
    extern u16 D_801C4162[][4];
    extern u16 D_801C4164[][4];
    extern u16 D_801C4166[][4];
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
        func_80183314(a0, a1);
        return;
    }

    p1 = (u16 *)((u8 *)D_801C4040 + type * 0x20);
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

    p1 = (u16 *)((u8 *)D_801C40C0 + type2 * 0x20);
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
        idx[0] = D_801C4160[j][0];
        idx[1] = D_801C4162[j][0];
        idx[2] = D_801C4164[j][0];
        idx[3] = D_801C4166[j][0];
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


extern s32 D_801C90A0[];
extern s32 D_801C90B8[];

void func_80183314(void *a0, s32 a1) {
    s32 v1;
    s32 *a2;

    v1 = ((u16 *)a0)[3] >> 12;
    a2 = (s32 *)D_801C90A0[v1];
    a2[1] &= 0x7FFFFFFF;
    D_801C90B8[v1 * 16] = a1;
    ((u16 *)a2)[4] = ((u16 *)a0)[0];
    ((u16 *)a2)[5] = ((u16 *)a0)[1];
    ((u16 *)a2)[6] = ((u16 *)a0)[2];
    ((u16 *)a2)[9] = (((u16 *)a0)[3] & 0xF) << 10;
}



extern void (*D_801C4480[])(void);

void func_8018338C(void *a0) {
    D_801C4480[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80180F18(s32 arg0, s32 arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012BEE8(s32 a0);
extern s32 rand(void);

void func_801833C8(s32 param_1) {

    extern u8 D_801C4490[][4];
    s32 i;
    s32 v1;
    s32 uVar1;

    if (func_80180F18(7, 0x13) == 0) {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (D_801C4490[*(s16 *)(param_1 + 0x100)][i] == *(s32 *)(param_1 + 0x1c)) {
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



extern void (*D_801C44AC[])(void);

void func_801834E4(void *a0) {
    D_801C44AC[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801C44B4[])(void);

void func_80183520(void *a0) {
    D_801C44B4[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801C44C4[])(void);

void func_8018355C(void *a0) {
    D_801C44C4[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801C44D4[])(void);

void func_80183598(void *a0) {
    D_801C44D4[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801835D4(void) {
}


extern s32 func_8012BEE8(s32 a0);
extern s32 rand(void);

void func_801835DC(s32 param_1) {
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



extern void (*D_801C44E4[])(void);

void func_80183788(void *a0) {
    D_801C44E4[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32, s32, s32 *, s32 *);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801837C4(void)
{

    extern u16 D_800B99DA;
    extern s32 D_80126B58;
    extern u8 D_800AF648;
    extern s32 D_801C44EC;
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
        if (RotTransPers((s32)&D_801C44EC, (s32)&sxy, &pv, &flag) <= 0 || flag < 0) {
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
            dist = ((s32 (*)(s32, s32))func_80013450)((s32)(p + 1), (s32)&D_801C44EC);
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



extern s32 D_801C4180;
extern s32 D_801C9238;
extern void func_80182DB4(s32 arg0, s32 arg1);

void func_80183920(void) {
    D_801C9238 = &D_801C4180;
    func_80182DB4(0x474, 0x4B0);
}



extern s32 D_801C41B8;
extern s32 D_801C9238;
extern void func_80182DB4(s32 arg0, s32 arg1);

void func_80183954(void) {
    D_801C9238 = &D_801C41B8;
    func_80182DB4(0x474, 0x4EC);
}



extern s32 D_801C41F0;
extern s32 D_801C9238;
extern void func_80182DB4(s32 arg0, s32 arg1);

void func_80183988(void) {
    D_801C9238 = &D_801C41F0;
    func_80182DB4(0x474, 0x4B0);
}



extern s32 D_801C4218;
extern s32 D_801C9238;
extern void func_80182DB4(s32 arg0, s32 arg1);

void func_801839BC(void) {
    D_801C9238 = &D_801C4218;
    func_80182DB4(0x474, 0x4B0);
}


extern s32 D_801C4250;
extern s32 D_801C9238;
extern void func_80182DB4(s32 arg0, s32 arg1);

void func_801839F0(void) {
    D_801C9238 = &D_801C4250;
    func_80182DB4(0x474, 0x528);
}


extern s32 D_801C4288;
extern s32 D_801C9238;
extern s32 func_80029504(void);

extern s32 func_80182DB4_call(s32 arg0, s32 arg1) __asm__("func_80182DB4");

s32 func_80183A24(void) {
    s32 r;

    D_801C9238 = &D_801C4288;
    r = func_80182DB4_call(0x168, 0x1A4);
    if (r == -1) {
        r = func_80182DB4_call(0x474, 0x4EC);
    }
    if ((u32)(func_80029504() - 0xC8) < 0xDC) {
        return -1;
    }
    return r;
}


extern s32 D_801C42C8;
extern s32 D_801C9238;
extern void func_80182DB4(s32 arg0, s32 arg1);

void func_80183A98(void) {
    D_801C9238 = &D_801C42C8;
    func_80182DB4(0x474, 0x1A4);
}




extern s32 func_80029504(void);
extern void func_80182DB4(s32 arg0, s32 arg1);

s32 func_80183ACC(void) {

    extern s32 D_801C4300;
    s32 v;
    D_801C9238 = (s32)&D_801C4300;
    v = func_80029504();
    if ((u32)(v - 0x64) < 0x1F4) {
        return -1;
    }
    func_80182DB4(0x96, 0xF0);
}


extern void func_80182DB4(s32 arg0, s32 arg1);
extern s32 D_801C4320;
extern s32 D_801C9238;

void func_80183B18(void) {
    D_801C9238 = &D_801C4320;
    func_80182DB4(0x12C, 0x1A4);
}



extern s32 D_801C4370;
extern s32 D_801C9238;
extern void func_80182DB4(s32 arg0, s32 arg1);

void func_80183B4C(void) {
    D_801C9238 = &D_801C4370;
    func_80182DB4(0x474, 0x4B0);
}



extern s32 D_801C43D0;
extern s32 D_801C9238;
extern void func_80182DB4(s32 arg0, s32 arg1);

void func_80183B80(void) {
    D_801C9238 = &D_801C43D0;
    func_80182DB4(0x474, 0x4B0);
}




extern s32 func_80029504(void);
extern void func_80182DB4(s32 arg0, s32 arg1);

s32 func_80183BB4(void) {

    extern s32 D_801C4400;
    s32 v;
    D_801C9238 = (s32)&D_801C4400;
    v = func_80029504();
    if ((u32)(v - 0x64) < 0x1F4) {
        return -1;
    }
    func_80182DB4(0x474, 0x78);
}


extern s32 D_801C4418;
extern s32 D_801C9238;
extern void func_80182DB4(s32 arg0, s32 arg1);

void func_80183C00(void) {
    D_801C9238 = &D_801C4418;
    func_80182DB4(0x564, 0x1A4);
}


extern s32 func_80183C34(void);

s32 func_80183C34(void) {
    return -1;
}


extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 D_801C923C;
extern s32 D_801C9254;
extern s32 D_801C90A0[];
extern void func_80182E1C();

void func_80183C3C(void)
{
    s32 i;

    D_801C923C = (((D_80078EB1 << 4) - D_80078EB1) << 2) + D_80078EB0;
    for (i = 0; i < 6; i++) {
        *(s32 *)(D_801C90A0[i] + 4) |= 0x80000000;
    }
    for (i = 2; i < 18; i++) {
        func_80182E1C((void *)i);
    }
    func_801837C4();
    if (D_801C9254 != 0) {
        D_801C9254 -= 1;
    }
}


extern void func_8001C214(s32, s32);
extern void func_8012C1B8(void);
extern void func_8012C588(s32, s32);
extern void func_8012CAE4(void *a0);
extern void func_80182D00(void);

    void func_80183CF8(void *a0) {
        s32 v0;
        u16 val;
        v0 = ((s32 (*)(void *))func_8012C1B8)(a0);
        *(s32 *)((char *)a0 + 0x20) = v0;
        if (v0 == 0) {
            func_8012CAE4(a0);
            return;
        }
        func_8001C214(v0, 0);
        func_8012C588(0x13F, 0);
        func_8012C588(0x66, 0);
        func_8012C588(0x65, 0);
        func_8012C588(0x14C, 0);
        func_8012C588(0x335, 0);
        func_8012C588(0x3D9, 0);
        val = *(u16 *)((char *)a0 + 0x72);
        *(u16 *)((char *)a0 + 0x2) = 1;
        val |= 0x1000;
        *(u16 *)((char *)a0 + 0x72) = val;
        func_80182D00();
    }


extern u8 D_801C4488[];
extern void func_8012E8E0(s32 a0, s32 a1);

    void func_80183DA4(s32 a0) {
        *(s16 *)(a0 + 0x2) = 1;
        func_8012E8E0(a0, (s32)&D_801C4488);
        *(s16 *)(a0 + 0xFE) = 0;
        *(s16 *)(a0 + 0xFC) = 0x80;
    }


extern void func_8012B200(u8 *a0);

/*
 * func_80183DE8 -- ov_SC04_018 / ov_SC04_018_jr_80188E1C, 71 ins, family reach x6.
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

void func_80183DE8(u8 *arg0)
{

    extern u8 D_800D387C[];
    extern u8 D_800D3888[];
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
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);
extern s32 func_8012BEE8(s32 a0);

void func_80183F04(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0xCC);
    u8 *v1;
    func_8012AD80((s32)a0);
    v1 = *(u8 **)(a0 + 0xCC);
    *(u16 *)(v1 + 8) = *(u16 *)(a0 + 6);
    *(u16 *)(v1 + 0xA) = *(u16 *)(a0 + 0xA);
    *(u16 *)(v1 + 0xC) = *(u16 *)(a0 + 0xE);
    if ((*(u32 *)(a0 + 0x1C) & 7) == 0) {
        func_80128ED8(s1, a0 + 0xD0);
    }
    if (func_8012BEE8((s32)a0)) {
        func_80016714(s1, 0x38);
        func_8012C218(a0);
    }
}



extern void func_8012B414(int a0);
    void func_80183FA0(s32 arg0) {
        s32 temp_v1 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(temp_v1 + 0x14) += 0x8;
        ((void (*)(void))func_8012B414)();
    }


    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern s32 D_801AD2F8[];
    extern s32 D_801C44BC[];
    void func_80183FD4(s32 a0) {
        s32 v0;
        v0 = ((s32 (*)(void))func_8012C1B8)();
        *(s32 *)(a0 + 0x20) = v0;
        if (v0 == 0) {
            func_8012CAE4((void *)a0);
            return;
        }
        func_8001C214(v0, (s32)D_801AD2F8);
        func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);
        func_8012E8E0(a0, (s32)D_801C44BC);
        *(s16 *)(a0 + 0x2) = 1;
    }


void func_8018404C(void *a0)
{
    extern u16 D_800B99DA;
    u16 var;
    s32 ret;

    var = D_800B99DA;
    ret = func_8004787C(((s32)var * 3) << 4);
    *(u16 *)(*(s32 *)((char *)a0 + 0x20) + 0x10) = (u16)((u32)ret >> 5);
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_80029504(void);
extern s32 D_801ACF90[];
extern s32 D_801C44CC[];

void func_80184094(s32 a0) {
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
    func_8001C810(v0, (s32)D_801ACF90);
    *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x8000;
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);
    func_8012E8E0(a0, (s32)D_801C44CC);
    *(s16 *)(a0 + 0x2) = 1;
    return;
}


void func_80184138(s32 arg0) {
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern s32 D_801AD490[];
    extern s32 D_801C44DC[];

    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(arg0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)arg0);
        return;
    }
    func_8001C214(v0, (s32)D_801AD490);
    func_8012E8E0(arg0, (s32)D_801C44DC);
    *(u16 *)(arg0 + 2) = 1;
    *(u16 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0xDC) = 0;
    *(s32 *)(arg0 + 0xE0) = 0;
    *(s32 *)(arg0 + 0xE4) = 0;
}



extern void (*D_801C5F0C[])(void);

void func_801841B0(void *a0) {
    D_801C5F0C[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: iv-combine
// @stuck: none — MATCH (49 ins). gcc folds (v0+0x1800)-0x1000 -> v0+0x800; re-tie barrier on the WORKING reg v0 (NOT a saved local) forces the target chain v0=base+0x1800; s2=copy; v0-=0x1000; s1=v0<<5. NO register pins (pins re-trigger the lhu/lh dual-load CSE collapse and shrink the frame; natural alloc gives s0-s3 + frame 0x38).
extern int rand(void);
extern u8 *func_8012913C(s32 a0);

extern unsigned short D_801C5EEC[];

void func_801841EC(s32 param_1, s32 param_2)
{
    int s3;
    unsigned short s0;
    int s2;
    int s1;
    int v0;
    int iVar3;

    s0 = D_801C5EEC[*(short *)(param_1 + 0xfc)];
    s3 = param_2;
    if (((short *)D_801C5EEC)[*(short *)(param_1 + 0xfc)] == 0) {
        *(short *)(param_1 + 0xfc) = 0;
        s0 = D_801C5EEC[0];
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



extern void (*D_801C5F20[])(void);

void func_801842B0(void *a0) {
    D_801C5F20[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: regalloc-order
// @stuck: none — MATCH

extern void func_801841EC(s32, s32);
extern s32 func_8012AD50(void *a0);

void func_801842EC(int param_1) {
    short uVar1;

    *(short *)(param_1 + 0xfc) = 0;
    *(int *)(param_1 + 0x1c) = 1;
    uVar1 = *(unsigned short *)(param_1 + 0x70) & 7;
    *(short *)(param_1 + 0xfe) = (uVar1 < 2) ? 0x1e : 0xf;
    if (uVar1 != 0) {
        func_801841EC(param_1, -0x80);
        func_801841EC(param_1, -0x30);
        func_801841EC(param_1, 0x20);
        func_801841EC(param_1, 0x70);
        func_801841EC(param_1, 0xc0);
    }
    if (1 < uVar1) {
        func_801841EC(param_1, -0x58);
        func_801841EC(param_1, -0x8);
        func_801841EC(param_1, 0x48);
        func_801841EC(param_1, 0x98);
        func_801841EC(param_1, 0xe8);
    }
    ((void (*)(int))func_8012AD50)(param_1);
}



// @class: regalloc-order
// @stuck: none — MATCH (param_1 naturally lands in $s0 across the call, mirrors sibling func_80184AEC)

extern s32 func_8012BEE8(s32 a0);
extern void func_801841EC(s32, s32);

void func_801843D4(s32 arg0) {
    if (func_8012BEE8(arg0)) {
        *(s32 *)(arg0 + 0x1c) = (s32)*(s16 *)(arg0 + 0xfe);
        func_801841EC(arg0, 0x110);
    }
}



// @class: plumbing
// @stuck: none — MATCH (expected)
extern void func_8001CB00(int param_1, void *src, int len, int n);

extern unsigned char D_801C5F14;

void func_80184414(int param_1)
{
    unsigned short uVar1;
    int iVar2;

    iVar2 = *(int *)(param_1 + 0x20);
    func_8001CB00(iVar2, &D_801C5F14, 0x280, 0x100);
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

void func_8018449C(u8 *a0) {
    *(s32 *)(a0 + 0x4) = *(s32 *)(a0 + 0x4) - *(s32 *)(a0 + 0x10);
    if (*(s16 *)(a0 + 0x6) < -0x110) {
        func_801292C8(a0);
    }
}






