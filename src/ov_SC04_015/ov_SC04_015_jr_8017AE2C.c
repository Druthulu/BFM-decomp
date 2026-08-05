#include "common.h"
#include "../shared/engine_core.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
   /* 12-byte sub-table record (stride 0xC) */
 /* 0x20 bytes */
                /* 4 + 16*12 = 0xC4 stride */
                 /* 0x08 */
     /* 0x20 */
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
extern void func_8012F14C(s32);
extern void func_80149374(s32 arg0, s32 arg1);
extern void func_801493D0(s32 param_1, s32 param_2, s32 param_3);
extern void func_8012F038(s32);
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
extern s32 func_8012E5CC(s32 a0, s32 a1, s32 a2);
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
extern u16 D_800B99DA;
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
extern s32 func_8014C568(void *a0);
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
extern s32 func_80135260(s32 arg0, s32 arg1, s16 *arg2, s16 *arg3);
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
extern u8 D_800D387C[];
extern u8 D_800D3888[];
extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_800D1FC8(s32 a0, s32 a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern void func_801665B4();
extern void func_80146C3C();
extern void func_80166438(u8 *a0);
extern s32 func_80128ED8(void *a0, void *a1);
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
/* ==== end §8b carried decl layer ==== */


extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012BE98(s32 a0, u16 *a1);
extern s32 func_80012A60(s32 a0, s32 a1);

extern s16 D_801C9320;
extern s16 D_801C9322;
extern s16 D_801C932C;

void func_8017AE2C(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801C9320;

    switch (g[0]) {
    case 0:
    default:
        return;
    case 1:
        g[1] = (u16)g[1] - 1;
        if (g[1] <= 0) {
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) = (u16)g[2];
            goto reset_both;
        }
        {
            s32 r = func_8012B608(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12), g[2], 6);
            *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) + r;
        }
        return;
    case 2:
        func_8012B178(pv, (s32)g[4] << 8);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        break;
    case 3:
        if (g[1] != 0) {
            if (g[5] != 0) {
                void *p = (void *)(pv + 4);
                if ((s16)func_80012A60(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12),
                                       (s16)func_8012B744(p, &g[6])) < 0x100) {
                    g[1] = 0;
                }
                *(s16 *)(*(s32 *)(pv + 0x20) + 0x12) =
                    func_8012B744(p, &D_801C932C);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801C9320+0xC == &D_801C932C; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801C9320 + 0xC)) < 0x101) {
                    D_801C9320 = 0;
                    D_801C9322 = 0;
                }
            }
            {
                s32 t = func_8012B744((void *)(pv + 4), &g[6]);
                s32 r = func_8012B608(*(s16 *)(*(s32 *)(pv + 0x20) + 0x12), t, g[3]);
                *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) =
                    *(u16 *)(*(s32 *)(pv + 0x20) + 0x12) + r;
            }
            g[1] = (u16)g[1] - 1;
            if (g[1] > 0) {
                return;
            }
            g[1] = 0;
            return;
        }
        *(s16 *)(*(s32 *)(pv + 0x20) + 0x12) =
            func_8012B744((void *)(pv + 4), &D_801C932C);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801C9320 + 0xC)) < 0x101) {
            D_801C9320 = 0;
            D_801C9322 = 0;
        }
        return;
    case 4:
        func_8012AD80(pv);
    }
    g[1] = (u16)g[1] - 1;
    if (g[1] > 0) {
        return;
    }
reset_both:
    g[0] = 0;
    g[1] = 0;
    return;
}

// @class: plumbing
// @stuck: none — MATCH


void func_8017B0E4(int param_1, int param_2)
{
    extern s16 D_801C892C;
    extern s16 D_801C892E;
    extern s16 D_801C8930;
    extern s16 D_801C8924;
    extern s16 D_801C8926;
    extern s16 D_801C8928;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801C892C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801C892E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801C8930, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801C8924, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801C8926, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801C8928, (s32)((s16)param_2));
}



extern s16 D_801C88B4;
extern u16 D_801C8934;
extern u16 D_801C8936;
extern u16 D_801C8938;
extern s16 D_801C9368;

void func_8017B1D8(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
    func_8012A418();
    D_801C9368 = 0;
    D_801C88B4 = 0;
    D_801C8934 = D_80126B5E;
    D_801C8936 = D_80126B62;
    D_801C8938 = D_80126B66;
}


// @class: regalloc-order — simplified sibling of matched func_8017B614.
// @stuck: none. Block-moves are align-1 struct-assigns (u8[8]) -> emit_block_move
// (unaligned lwl/lwr/swl/swr), ZERO memcpy-symbol reference, so the TU's `extern memcpy`
// (which turned the old draft's memcpy into a CALL -> DIFF 64) can't drift this.
// $16 pin + in-place re-tie keeps param_2 in $a1 until the >=0xB branch, then $s0 for loads.


s32 func_8017B238(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_80187E78[];
    extern s16 D_801C892C;
    extern s16 D_801C8924;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80187E78[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80187E78[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801C892C;
        s16 *p78C = &D_801C8924;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801C9368 = 1;
        D_801C88B4 = 0;
    }
}



// @class: struct
// @stuck: none — MATCH (74 ins)

      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
         /* 16-byte stride array element */



s32 func_8017B368(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801C88D4;
    extern SV4_8017B368 D_801C88DC;
    extern s16 D_801C892C;
    extern s16 D_801C8924;
    extern u16 D_80187E78;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801C88D4;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801C88DC;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_80187E78)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_80187E78)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801C892C) = loc0;
    (*(SV4_8017B368 *)&D_801C8924) = loc1;
    D_801C9368 = 1;
    D_801C88B4 = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801C88D4;
    extern SV4_8017B368 D_801C88DC;
    extern s16 D_801C892C;
    extern s16 D_801C8924;
    extern u16 D_80187E78;
    extern s16 D_801C88B4;
    extern s16 D_801C9368;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801C88D4;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801C88DC;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80187E78)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80187E78)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801C892C) = loc0;
    (*(SV4_8017B368 *)&D_801C8924) = loc1;
    D_801C9368 = 1;
    D_801C88B4 = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801C892C).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801C892C).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801C892C).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801C8924).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801C8924).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801C8924).c;
}


// @class: regalloc-order + T1 memcpy-builtin→call re-crack
// @stuck: 0 (iso). Register lever = $16 pin + in-place re-tie on the memcpy-branch src (keeps
// param_2 in $a1 until the branch, then $s0 for the loads). Block-moves are align-1 struct-assigns
// (u8[8]) so they lower via emit_block_move (movstrsi/move_by_pieces) with ZERO memcpy-symbol
// reference — TU-independent, so the sibling TU's `extern memcpy` (which disables the builtin and
// turned the old inlined block-move into a CALL) can no longer drift this.




s32 func_8017B614(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_80187E78[];
    extern s16 D_801C892C;
    extern s16 D_801C892E;
    extern s16 D_801C8930;
    extern s16 D_801C8924;
    extern s16 D_801C8926;
    extern s16 D_801C8928;
    extern u8 D_8012694C;
    extern s32 D_80126998;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80187E78[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80187E78[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801C892C;
        s16 *p78C = &D_801C8924;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801C892E;
            v798 = D_801C8930;
            v78C = *p78C;
            v78E = D_801C8926;
            v790 = D_801C8928;
            __asm__ __volatile__("");
            D_801C9368 = 1;
            D_801C88B4 = 0x1E;
            D_80126990 = v794;
            D_80126994 = v796;
            D_80126998 = v798;
            D_80126984 = v78C;
            D_80126988 = v78E;
            D_8012698C = v790;
        }
        func_80129CF8();
    }
}




// @class: plumbing
// @stuck: none — MATCH

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8 D_8012694C;
extern s16 D_801C88B4;
extern s16 D_801C892C;
extern s16 D_801C892E;
extern s16 D_801C8930;
extern s16 D_801C8924;
extern s16 D_801C8926;
extern s16 D_801C8928;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801C88B4 = 0;
    D_801C892C = (s16) D_80114F30;
    D_801C892E = (s16) D_80114F34;
    D_801C8930 = (s16) D_80114F38;
    D_801C8924 = (s16) D_80114F24;
    D_801C8926 = (s16) D_80114F28;
    D_801C8928 = (s16) D_80114F2C;
}




extern s16 D_801C8944;
extern s16 D_801C8946;
extern s16 D_801C8948;
extern s16 D_801C894C;
extern s16 D_801C894E;
extern s16 D_801C8950;

void func_8017B824(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801151D4;
    D_801C8944 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801C8946 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801C8948 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801C894C = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801C894E = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801C8950 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801C8944;
extern s16 D_801C8946;
extern s16 D_801C8948;
extern s16 D_801C894C;
extern s16 D_801C894E;
extern s16 D_801C8950;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801C8944;
    D_80114F34 = D_801C8946;
    D_80114F38 = D_801C8948;
    D_80114F24 = D_801C894C;
    D_80114F28 = D_801C894E;
    D_80114F2C = D_801C8950;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801C892C), src[8..15] -> (*(S8_8017B8E8 *)&D_801C8924) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801C892C) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801C8924) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_801C8934;
extern u16 D_801C8936;
extern u16 D_801C8938;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801C88B4;
extern short D_801C893C;
extern short D_801C893E;
extern short D_801C8940;
extern s16 D_801C892C;
extern s16 D_801C892E;
extern s16 D_801C8930;
extern s16 D_801C8924;
extern s16 D_801C8926;
extern s16 D_801C8928;

void func_8017B940(void)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u16 D_80126B62;
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801C8934);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801C8936);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801C8938);
    (*(s16 *)&D_801C893C) = buf[0];
    (*(s16 *)&D_801C893E) = buf[1];
    (*(s16 *)&D_801C8940) = buf[2];
    D_801C892C = D_80114F30 + buf[0];
    D_801C88B4 = 0;
    D_801C892E = D_80114F34 + buf[1];
    D_801C8930 = D_80114F38 + buf[2];
    D_801C8924 = D_80114F24 + buf[0];
    D_801C8926 = D_80114F28 + buf[1];
    D_801C8928 = D_80114F2C + buf[2];
}



// @class: struct
// @stuck: none — MATCH (62 ins)

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);

/* short-only (align 2) struct -> the 8-byte struct copy emits lwl/lwr/swl/swr */

/* PSX MATRIX_L48: 3x3 short rotation + pad + 3 long translation (offset 0x14) */

extern SV4 D_801C88D4;
extern SV4 D_801C88DC;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801C88DC) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801C88D4 = svec;

    v0.a = -*(s16 *)(param_2 + 0xc);
    v0.b = *(u16 *)(param_2 + 8);
    v0.c = 0;
    v1.a = 0;
    v1.b = 0;
    v1.c = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))func_80049CAC)(&v0, &mtx);

    mtx.t[0] = (s32)svec.a;
    mtx.t[1] = (s32)svec.b;
    mtx.t[2] = (s32)svec.c;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    RotTransSV(&v1, &buf1, &buf2);
    D_801C88DC = buf1;
}


// @class: struct
// @stuck: none — MATCH (65 ins)
#include "common.h"




s32 func_8017BB34(s32 param_1, s32 param_2)
{
    SV4_8017BB34 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX_8017BB34 mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4_8017BB34 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4_8017BB34 svec;          /* sp+0x40 */
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801C88DC)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801C88D4) = svec;

    v0.a = -*(s16 *)(param_2 + 0xc);
    v0.b = *(u16 *)(param_2 + 8);
    v0.c = 0;
    v1.a = 0;
    v1.b = 0;
    v1.c = -*(s16 *)(param_2 + 0xa);
    ((void (*)(void *, void *))func_80049CAC)(&v0, &mtx);

    mtx.t[0] = (s32)svec.a;
    mtx.t[1] = (s32)svec.b;
    mtx.t[2] = (s32)svec.c;
    func_8004914C(&mtx);
    func_800491AC(&mtx);

    RotTransSV(&v1, &buf1, &buf2);
    (*(SV4_8017BB34*)&D_801C88DC) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801C88FC[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801C88FC;
    do {
        if (*p != (void (*)(int))0) {
            (*p)(param_1);
        }
        i = i + 1;
        p = p + 1;
    } while (i < 10);
    return;
}




// @class: plumbing
// @stuck: none — MATCH (expected); short-typed global increment + signed compare, store-2 on overflow

extern void func_8017B0E4(int, int);
extern s16 D_801C88B4;
extern s16 D_801C9368;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801C88B4 = D_801C88B4 + 1;
    if (D_801C88B4 >= 0x1F) {
        D_801C9368 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801C88B4;
extern s16 D_801C9368;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801C88B4 = D_801C88B4 + 1;
    if (0x18 < D_801C88B4) {
        func_8012A4BC();
        D_801C9368 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801C88B4;
extern void (*D_801C88F8)(void);
extern short D_801C893C;
extern short D_801C893E;
extern short D_801C8940;
extern s16 D_801C9368;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801C88B4 = D_801C88B4 + 1;
    if (D_801C88B4 >= 0x19) {
        if (D_801C88F8 != 0) {
            (*D_801C88F8)();
        } else {
            D_80114F30 = D_80114F30 + D_801C893C;
            D_80114F34 = D_80114F34 + D_801C893E;
            D_80114F38 = D_80114F38 + D_801C8940;
            D_80114F24 = D_80114F24 + D_801C893C;
            D_80114F28 = D_80114F28 + D_801C893E;
            D_80114F2C = D_80114F2C + D_801C8940;
            func_8012A4BC();
        }
        D_801C9368 = 0;
    }
}



extern void (*D_80187F18[])(void);

void func_8017BE60(void *a0) {
    D_80187F18[*(u8 *)((s32)a0 + 0x4)]();
}


DEFINE_func_8017BE9C()  /* dedup: shared engine-core @0x8017BE9C (src/shared) */

DEFINE_func_8017BEA4()  /* dedup: shared engine-core @0x8017BEA4 (src/shared) */

DEFINE_func_8017BEAC()  /* dedup: shared engine-core @0x8017BEAC (src/shared) */

DEFINE_func_8017BEB4()  /* dedup: shared engine-core @0x8017BEB4 (src/shared) */


extern void (*D_80187FB8[])(void);

void func_8017BEBC(void *a0) {
    D_80187FB8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80187FC0[])(void);

void func_8017BEF8(void *a0) {
    D_80187FC0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80187FC8[])(void);

void func_8017BF34(void *a0) {
    D_80187FC8[*(u16 *)((s32)a0 + 0x2)]();
}




/* Decl layer conformed to the TU (ov_SC03_001_jr_8017AE2C.c):
 *  - func_8012913C: the TU already declares `extern u8 *func_8012913C(s32 a0);`
 *    at line 7121 -- BELOW this splice point (3327), which is why cc1 reported the
 *    conflict at 7181. Copied verbatim; the s32 use is pushed to a cast at the call
 *    site, matching the idiom the TU itself uses at line 7145. Byte-neutral.
 *  - func_8012C750: not declared in this TU; conformed anyway to the canonical
 *    engine_core.h form (`s32 func_8012C750(s32 a0)`, DEFINE_func_8012C750) with the
 *    pointer arg cast at the call site, so a future macro expansion cannot collide.
 */
extern u8 *func_8012913C(s32 a0);
extern s32 func_8012C750(s32 a0);


/* $16-$19 are pinned: without them gcc's strength reduction splits the `s1` store
 * base into TWO induction variables (base+0x18 with offsets -4/0, plus base+0x1C),
 * burning an extra callee-saved reg and growing the frame to 0x48. s4 must stay
 * UNPINNED -- a pin collapses `$v0 = $s4 + 1; $s4 = $v0` into `addiu $s4,$s4,1` and
 * then sign-extends from $s4, losing the target's `addu $s4,$v0,$zero` + sll/sra on
 * $v0 at the loop join. It still lands in $20 naturally once $16-$19 are taken.
 */
void func_8017BF70(s32 a0)
{

    extern u8 D_801C8958[];
    register s32 s3 asm("$19");
    register s16 *s0 asm("$16");
    register s32 *s1 asm("$17");
    register u8 *s2 asm("$18");
    s16 s4;
    Buf8017BF50_8017BF70 buf;

    s3 = a0;
    s0 = *(s16 **)(s3 + 0xDC);
    if (s0 != 0) {
        s2 = D_801C8958;
        s4 = 0;
        s1 = (s32 *)(D_801C8958 + 0x1C);
        buf.unk06 = 0x158;
        buf.unk0A = 0;
        buf.unk08 = 0;
        buf.unk0E = 0;
        buf.unk10 = 0;
        do {
            u16 v1;

            v1 = (u16)*s0;
            if ((v1 & 0xFFFF) == 0x8000) break;

            if (*(s16 *)(s3 + 0x70) != 0) {
                buf.unk00 = *s0++;
                buf.unk02 = *s0++;
                buf.unk04 = *s0++;
                if (((s32 (*)(void *))func_8012C750)(&buf) == 0) break;
            } else {
                s32 v3;

                v3 = ((s32 (*)(s32))func_8012913C)(0x11);
                if (v3 == 0) break;
                s1[-2] = *s0++;
                s1[-1] = *s0++;
                s1[0] = *s0++;
                s1 += 8;
                *(u8 **)(v3 + 0x30) = s2;
                s2 += 0x20;
            }
            s4++;
        } while (s4 < 0x10);
    }
    *(u16 *)(s3 + 2) += 1;
}




extern void func_800D23D0(void *a0);

void func_8017C0B4(void) {

    extern s32 D_801151D4;
    extern s16 D_801C8B58;
    s16 diffs[3];
    s32 *ptr = (s32 *)D_801151D4;

    diffs[0] = (s16)(*(s32 *)((u8 *)ptr + 0x68) - *(s32 *)((u8 *)ptr + 0x5C));
    diffs[1] = (s16)(*(s32 *)((u8 *)ptr + 0x6C) - *(s32 *)((u8 *)ptr + 0x60));
    diffs[2] = (s16)(*(s32 *)((u8 *)ptr + 0x70) - *(s32 *)((u8 *)ptr + 0x64));

    func_800D23D0(diffs);

    D_801C8B58 = (u16)diffs[1];
}



extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);

void func_8017C120(s32 param_1)
{

    extern u8 D_80187F24[];
    s32 s0;

    s0 = *(s32 *)(param_1 + 0x20);
    if (*(s16 *)(param_1 + 0x2e) == 0) {
        func_8001CB6C((u8 *)s0, (s32)D_80187F24, 0x3c0, 0xa0);
    } else {
        func_8001CC3C(s0, (s32)D_80187F24, 0x3c0, 0xa0);
    }
    *(u8 *)(s0 + 0x27) = 0xfc;
    *(u16 *)(s0 + 0x1a) = 0x3c00;
    *(u16 *)(s0 + 0x18) = 0x3c00;
    *(u32 *)(s0 + 0x4) |= 0x01000000;
    *(u32 *)(s0 + 0x34) = *(u32 *)(param_1 + 0x30);
    (*(u16 *)(param_1 + 0x2))++;
}



extern void RotMatrixYXZ(void *a0, void *a1);


void func_8017C1CC(s32 param_1)
{

    extern s16 D_801C8B58;
    SV4 sv4;
    s32 s0;
    s32 a1;

    s0 = *(s32 *)(param_1 + 0x20);
    sv4.a = -0x20;
    sv4.c = 0;
    sv4.b = D_801C8B58;
    a1 = *(s32 *)(s0 + 0x34);
    RotMatrixYXZ(&sv4, a1);
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012A828(s32*, s32);
extern void func_8012B260(u8 *a0);


void func_8017C20C(s32 a0)
{

    extern u8 D_80184864[];
    extern u8 D_80187FA0[];
    extern u8 D_80187FA8[];
    s32 s0;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        ((void (*)(s32))func_8012CAE4)(a0);
        return;
    }

    func_8001C810(s0, (s32)D_80187FA0);
    ((void (*)(s32, s32))func_8012A828)(a0, (s32)D_80184864);

    *(s32 *)(a0 + 0x20) = s0;
    *(s16 *)(s0 + 0x1A) = 0x3C00;
    *(s16 *)(s0 + 0x18) = 0x3C00;
    *(s16 *)(s0 + 0x10) = -0x20;
    *(s16 *)(s0 + 0x12) = -1;
    *(s32 *)(s0 + 0x4) |= 0x8040;
    *(u16 *)(s0 + 0x2C) |= 0x10;

    ((void (*)(s32))func_8012B260)(a0);

    *(s32 *)(a0 + 0x58) = (s32)D_80187FA8;
    *(u16 *)(a0 + 0x2) += 1;
}



extern void func_80049CAC(s32 a0, s32 a1);

void func_8017C2D0(s32 a0)
{

    extern u16 D_80126B62;
    extern s16 D_801C8B58;
    s32 unused[2];              /* dead 8-byte local — frame 0x28, not 0x20 */
    s32 s0;

    s0 = *(s32 *)(a0 + 0x20);

    if ((s32)*(s16 *)(a0 + 0xA) - (s32)(*(s16 *)&D_80126B62) >= 0x40) {
        *(s16 *)(a0 + 0x5C) = 0x40;
    } else {
        *(s16 *)(a0 + 0x5C) = 0x800;
    }

    if (*(s16 *)(s0 + 0x12) != D_801C8B58) {
        *(s16 *)(s0 + 0x12) = D_801C8B58;
        func_80049CAC(*(s32 *)(a0 + 0x20) + 0x10, *(s32 *)(a0 + 0x20) + 0x34);
        *(u16 *)(s0 + 0x2C) |= 0x11;
    }
}



extern void (*D_80187FE8[])(void);

void func_8017C358(void *a0) {
    D_80187FE8[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);


void func_8017C394(s32 param_1) {

    extern u8 D_80187FD0;
    s32 obj = *(s32 *)(param_1 + 0x34);
    Work8017 w;
    short i;
    s32 e;
    s32 node;

    func_80146A6C(0x11, (void *)param_1, *(s16 *)(param_1 + 6),
                  (s16)(*(u16 *)(param_1 + 0xA) - 0x10),
                  *(s16 *)(param_1 + 0xE), 0, 0);

    w.x = *(u16 *)(param_1 + 6);
    w.y = *(u16 *)(param_1 + 0xA);
    w.z = *(u16 *)(param_1 + 0xE);
    func_800D20C0(&w.x, &w.vx, 10);
    *(s16 *)(param_1 + 6) = w.x;
    *(s16 *)(param_1 + 0xE) = w.z;
    w.vy = 0;
    func_800D23D0(&w.vx);

    i = 0;
    do {
        e = func_80146A6C(0x12, (void *)param_1, *(s16 *)(obj + 6),
                          *(s16 *)(obj + 0xA), *(s16 *)(obj + 0xE), i, 0);
        if (e != 0) {
            *(s16 *)(e + 0x12) = w.vx;
            *(s16 *)(e + 0x16) = w.vy;
            *(s16 *)(e + 0x1A) = 0;
        }
        i = i + 1;
    } while (i < 3);

    node = func_800D222C(param_1, &D_80187FD0, 0xFD);
    if (node != 0) {
        *(s32 *)(param_1 + 0x20) = node;
        *(u32 *)(node + 4) = *(u32 *)(node + 4) | 0x5D000100;
        ((void (*)(void *))func_8001CF30)((void *)node);
        *(s16 *)(node + 0x18) = 0x4000;
        *(s16 *)(node + 0x1A) = 0x200;
        *(s16 *)(param_1 + 0x16) = 0x200;
        *(s16 *)(param_1 + 0x14) = 0x1000;
        *(s16 *)(node + 0x28) = 0x240;
        *(s16 *)(node + 0x2A) = 0x180;
        *(s16 *)(node + 0x10) = w.vx;
        *(s16 *)(node + 0x12) = w.vy;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


extern void func_80146C3C(void);
void func_8017C558(u8 *p) {
    u8 *q;
    s32 t;
    s32 b;
    q = *(u8 **)(p + 0x20);
    *(u16 *)(p + 0x16) = *(u16 *)(p + 0x16) + *(u16 *)(p + 0x14);
    if (*(s32 *)(p + 0x1C) < 8) {
        *(s16 *)(p + 0x14) = *(u16 *)(p + 0x14) - 0x200;
    } else {
        *(s16 *)(p + 0x14) = *(u16 *)(p + 0x14) - 0x51;
    }
    b = *(u8 *)(q + 0x26) - 2;
    *(s16 *)(q + 0x1A) = *(u16 *)(p + 0x16);
    *(s8 *)(q + 0x26) = b;
    *(s8 *)(q + 0x25) = b;
    *(s8 *)(q + 0x24) = b;
    t = *(s32 *)(p + 0x1C);
    *(s32 *)(p + 0x1C) = t + 1;
    if (t >= 0x1E) {
        ((void (*)(u8 *))func_80146C3C)(p);
    }
}



extern void (*D_80187FF0[])(void);

void func_8017C5EC(void *a0) {
    D_80187FF0[*(u16 *)((s32)a0 + 0x2)]();
}



// @class: plumbing
// @stuck: none — MATCH (41 ins, relocation-masked); frame needed a 0x30 address-taken local

extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern void func_80146C3C(void);
extern u8 D_80187FDC;

void func_8017C628(s32 a0) {
    s32 r;
    s32 buf[12];

    (void)&buf;
    r = func_800D222C(a0, &D_80187FDC, 0x18);
    if (r != 0) {
        *(s32 *)(a0 + 0x20) = r;
        *(u32 *)(r + 4) = *(u32 *)(r + 4) | 0x5C000140;
        func_8001CF30((void *)r);
        *(s16 *)(r + 0x10) = 0x400;
        *(s16 *)(r + 0x18) = 0x3000;
        *(s16 *)(r + 0x1A) = 0x3000;
        *(s16 *)(r + 0x28) = 0x248;
        *(s16 *)(r + 0x2A) = 0x180;
        *(s16 *)(a0 + 2) = *(s16 *)(a0 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}


extern void func_80146C3C(void);
void func_8017C6CC(int a0) {
    int v0 = *(int *)(a0 + 0x1C);
    register unsigned char *p __asm__("$5") = *(unsigned char **)(a0 + 0x20);
    *(int *)(a0 + 0x1C) = v0 + 1;
    if (v0 >= 0x1F) {
        func_80146C3C();
    } else {
        unsigned short hv = *(unsigned short *)(p + 0x1A) + 0x1E0;
        signed char bv = *(unsigned char *)(p + 0x26) - 3;
        *(unsigned short *)(p + 0x1A) = hv;
        *(unsigned short *)(p + 0x18) = hv;
        *(signed char *)(p + 0x26) = bv;
        *(signed char *)(p + 0x25) = bv;
        *(signed char *)(p + 0x24) = bv;
    }
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
#define gte_ldv3c(r0) __asm__ volatile (         \
    "lwc2 $0, 0( %0 );"                          \
    "lwc2 $1, 4( %0 );"                          \
    "lwc2 $2, 8( %0 );"                          \
    "lwc2 $3, 12( %0 );"                         \
    "lwc2 $4, 16( %0 );"                         \
    "lwc2 $5, 20( %0 )"                          \
    :                                            \
    : "r"( r0 ) )
#define gte_rtps() __asm__ volatile ("nop;nop;rtps")
#define gte_rtpt() __asm__ volatile ("nop;nop;rtpt")
#define gte_nclip() __asm__ volatile ("nop;nop;nclip")
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
#define gte_stsxy3c(r0) __asm__ volatile (       \
    "swc2 $12, 0( %0 );"                         \
    "swc2 $13, 4( %0 );"                         \
    "swc2 $14, 8( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsxy3_f3(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsxy3_ft3(r0) __asm__ volatile (    \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 16( %0 );"                        \
    "swc2 $14, 24( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsxy3_f4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )
#define gte_stsz3(r0, r1, r2) __asm__ volatile ( \
    "swc2 $17, 0( %0 );"                         \
    "swc2 $18, 0( %1 );"                         \
    "swc2 $19, 0( %2 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 )            \
    : "memory" )
#define gte_stsz4(r0, r1, r2, r3) __asm__ volatile ( \
    "swc2 $16, 0( %0 );"                         \
    "swc2 $17, 0( %1 );"                         \
    "swc2 $18, 0( %2 );"                         \
    "swc2 $19, 0( %3 )"                          \
    :                                            \
    : "r"( r0 ), "r"( r1 ), "r"( r2 ), "r"( r3 ) \
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
#define gte_stopz(r0) __asm__ volatile (         \
    "swc2 $24, 0( %0 )"                          \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )

void func_8017C730(s32 arg0)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern short D_800B9A02;   /* TU-visible spelling (engine_core.h + ov_SC01_000.c col-0); unsigned access forced at use — §8d sub-class (b) */

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    MATRIX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 nparts;
    s32 j;
    u32 nprim;
    u32 i;
    Part *part;
    Prim *prim;
    u8 *pkt;
    u32 ot;
    u8 *vtx;
    u8 *va, *vb, *vc, *vd;
    u32 w, code;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;

    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    pkt = D_800A5E60;
    part = *(Part **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];

    for (j = 0; j < nparts; j++, part++) {
        wx = part->xx;
        mn = wx;
        mx = wx >> 16;
        wy = part->yy;
        mny = wy;
        my = wy >> 16;
        wz = part->zz;
        box[0].vx = mn; box[0].vy = mny;
        box[1].vx = mx; box[1].vy = mny;
        box[2].vx = mn; box[2].vy = mny;
        box[3].vx = mx; box[3].vy = mny;
        box[4].vx = mn; box[4].vy = my;
        box[5].vx = mx; box[5].vy = my;
        box[6].vx = mn; box[6].vy = my;
        box[7].vx = mx; box[7].vy = my;
        wy = wz >> 16;
        box[0].vz = wz;
        box[1].vz = wz;
        box[4].vz = wz;
        box[5].vz = wz;
        box[2].vz = wy;
        box[3].vz = wy;
        box[6].vz = wy;
        box[7].vz = wy;

        gte_ldv3c(&box[0]);
        gte_rtpt();
        gte_stsxy3(&sxy[0], &sxy[1], &sxy[2]);
        gte_ldv0(&box[3]);
        gte_rtps();
        gte_stsxy(&sxy[3]);
        gte_ldv3c(&box[4]);
        __asm__ volatile ("");   /* §45-B live-length slider: +1 static insn splits the 228/230 allocno-priority tie (498/498 -> 497/498) */
        gte_rtpt();
        gte_stsxy3(&sxy[4], &sxy[5], &sxy[6]);
        gte_ldv0(&box[7]);
        gte_rtps();
        gte_stsxy(&sxy[7]);
        gte_stszotz(&g.otz);

        if (lim >= g.otz) {
            xa32 = sxy[0].vx;
            xb32 = sxy[1].vx;
            if (xb32 < xa32) { xmx1 = xa32; xmn1 = xb32; } else { xmn1 = xa32; xmx1 = xb32; }
            t32 = sxy[2].vx;
            if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
            t32 = sxy[3].vx;
            if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
            xa32 = sxy[4].vx;
            xb32 = sxy[5].vx;
            if (xb32 < xa32) { xmx2 = xa32; xmn2 = xb32; } else { xmn2 = xa32; xmx2 = xb32; }
            t32 = sxy[6].vx;
            if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
            t32 = sxy[7].vx;
            if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
            mnc = xmn1;
            if (xmn2 < xmn1) mnc = xmn2;
            mxc = xmx1;
            if (mxc < xmx2) mxc = xmx2;
            if ((s16)mxc >= -0xA0 && (s16)mnc < 0xA1) {
                xa32 = sxy[0].vy;
                xb32 = sxy[1].vy;
                if (xb32 < xa32) { xmx1 = xa32; xmn1 = xb32; } else { xmn1 = xa32; xmx1 = xb32; }
                t32 = sxy[2].vy;
                if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
                t32 = sxy[3].vy;
                if (xmx1 < t32) xmx1 = t32; else if (t32 < xmn1) xmn1 = t32;
                xa32 = sxy[4].vy;
                xb32 = sxy[5].vy;
                if (xb32 < xa32) { xmx2 = xa32; xmn2 = xb32; } else { xmn2 = xa32; xmx2 = xb32; }
                t32 = sxy[6].vy;
                if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
                t32 = sxy[7].vy;
                if (xmx2 < t32) xmx2 = t32; else if (t32 < xmn2) xmn2 = t32;
                mnc = xmn1;
                if (xmn2 < xmn1) mnc = xmn2;
                mxc = xmx1;
                if (mxc < xmx2) mxc = xmx2;
                if ((s16)mxc >= -0x78 && (s16)mnc < 0x79) {
                    prim = (Prim *)part->prim;
                    nprim = part->nprim;
                    for (i = 0; i < nprim; i++, prim++) {
                        w = prim->w1;
                        va = vtx + (w & 0xFFFF);
                        vb = vtx + (w >> 16);
                        w = prim->w2;
                        vc = vtx + (w & 0xFFFF);
                        w = w >> 16;
                        gte_ldv3(va, vb, vc);
                        gte_rtpt();
                        gte_stflg(&g.flag);
                        if (!(g.flag & 0x7F85E000)) {
                            gte_nclip();
                            code = w & 7;
                            vd = vtx + (w & 0xFFF8);
                            gte_stopz(&g.opz);
                            if (g.opz > 0) {
                                switch (code) {
                                case 4:
                                case 5:
                                    gte_stsxy3_f3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((PolyF3 *)pkt)->x0 > ((PolyF3 *)pkt)->x1) {
                                        mx = ((PolyF3 *)pkt)->x0;
                                        mn = ((PolyF3 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyF3 *)pkt)->x0;
                                        mx = ((PolyF3 *)pkt)->x1;
                                    }
                                    if (((PolyF3 *)pkt)->x2 > mx) mx = ((PolyF3 *)pkt)->x2;
                                    else if (((PolyF3 *)pkt)->x2 < mn) mn = ((PolyF3 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyF3 *)pkt)->y0 > ((PolyF3 *)pkt)->y1) {
                                            my = ((PolyF3 *)pkt)->y0;
                                            mny = ((PolyF3 *)pkt)->y1;
                                        } else {
                                            mny = ((PolyF3 *)pkt)->y0;
                                            my = ((PolyF3 *)pkt)->y1;
                                        }
                                        if (((PolyF3 *)pkt)->y2 > my) my = ((PolyF3 *)pkt)->y2;
                                        else if (((PolyF3 *)pkt)->y2 < mny) mny = ((PolyF3 *)pkt)->y2;
                                        if (my >= -0x78 && mny < 0x79) {
                                            s32 za, zb;
                                            u32 *otp;
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code != 4) g.opz = za + 0x20;
                                            ((PolyF3 *)pkt)->rgbc = prim->w0;
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x4000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x14;
                                        }
                                    }
                                    break;
                                case 6:
                                case 7:
                                    gte_stsxy3_ft3(pkt);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (((PolyFT3 *)pkt)->x0 > ((PolyFT3 *)pkt)->x1) {
                                        mx = ((PolyFT3 *)pkt)->x0;
                                        mn = ((PolyFT3 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyFT3 *)pkt)->x0;
                                        mx = ((PolyFT3 *)pkt)->x1;
                                    }
                                    if (((PolyFT3 *)pkt)->x2 > mx) mx = ((PolyFT3 *)pkt)->x2;
                                    else if (((PolyFT3 *)pkt)->x2 < mn) mn = ((PolyFT3 *)pkt)->x2;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (((PolyFT3 *)pkt)->y0 > ((PolyFT3 *)pkt)->y1) {
                                            my = ((PolyFT3 *)pkt)->y0;
                                            mny = ((PolyFT3 *)pkt)->y1;
                                        } else {
                                            mny = ((PolyFT3 *)pkt)->y0;
                                            my = ((PolyFT3 *)pkt)->y1;
                                        }
                                        if (((PolyFT3 *)pkt)->y2 > my) my = ((PolyFT3 *)pkt)->y2;
                                        else if (((PolyFT3 *)pkt)->y2 < mny) mny = ((PolyFT3 *)pkt)->y2;
                                        if (my >= -0x78 && mny < 0x79) {
                                            s32 za, zb;
                                            u32 *otp;
                                            u32 *tp;
                                            if (g.sz0 > g.sz1) {
                                                za = g.sz0;
                                                if (za < g.sz2) za = g.sz2;
                                            } else {
                                                za = g.sz1;
                                                if (za < g.sz2) za = g.sz2;
                                            }
                                            g.opz = za;
                                            if (code == 7) g.opz = za + 0x20;
                                            tp = (u32 *)prim->w0;
                                            ((PolyFT3 *)pkt)->rgbc = tp[0];
                                            ((PolyFT3 *)pkt)->uvc0 = tp[1];
                                            ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                            ((PolyFT3 *)pkt)->uv2 = tp[3];
                                            otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                            *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                            *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                            pkt += 0x20;
                                        }
                                    }
                                    break;
                                case 0:
                                case 1:
                                    gte_stsxy3_f4(pkt);
                                    gte_ldv0(vd);
                                    gte_rtps();
                                    if (((PolyF4 *)pkt)->x0 > ((PolyF4 *)pkt)->x1) {
                                        mx = ((PolyF4 *)pkt)->x0;
                                        mn = ((PolyF4 *)pkt)->x1;
                                    } else {
                                        mn = ((PolyF4 *)pkt)->x0;
                                        mx = ((PolyF4 *)pkt)->x1;
                                    }
                                    if (((PolyF4 *)pkt)->x2 > mx) mx = ((PolyF4 *)pkt)->x2;
                                    else if (((PolyF4 *)pkt)->x2 < mn) mn = ((PolyF4 *)pkt)->x2;
                                    if (((PolyF4 *)pkt)->y0 > ((PolyF4 *)pkt)->y1) {
                                        my = ((PolyF4 *)pkt)->y0;
                                        mny = ((PolyF4 *)pkt)->y1;
                                    } else {
                                        mny = ((PolyF4 *)pkt)->y0;
                                        my = ((PolyF4 *)pkt)->y1;
                                    }
                                    if (((PolyF4 *)pkt)->y2 > my) my = ((PolyF4 *)pkt)->y2;
                                    else if (((PolyF4 *)pkt)->y2 < mny) mny = ((PolyF4 *)pkt)->y2;
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((PolyF4 *)pkt)->x3);
                                        if (((PolyF4 *)pkt)->x3 < mn) mn = ((PolyF4 *)pkt)->x3;
                                        else if (mx < ((PolyF4 *)pkt)->x3) mx = ((PolyF4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyF4 *)pkt)->y3 < mny) mny = ((PolyF4 *)pkt)->y3;
                                            else if (my < ((PolyF4 *)pkt)->y3) my = ((PolyF4 *)pkt)->y3;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb;
                                                u32 *otp;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                ((PolyF4 *)pkt)->rgbc = prim->w0;
                                                otp = (u32 *)(((za >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x5000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x18;
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_ldv0(vd);
                                    gte_rtps();
                                    if (tmpxy[0].vx > tmpxy[1].vx) {
                                        mx = tmpxy[0].vx;
                                        mn = tmpxy[1].vx;
                                    } else {
                                        mn = tmpxy[0].vx;
                                        mx = tmpxy[1].vx;
                                    }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (tmpxy[0].vy > tmpxy[1].vy) {
                                        my = tmpxy[0].vy;
                                        mny = tmpxy[1].vy;
                                    } else {
                                        mny = tmpxy[0].vy;
                                        my = tmpxy[1].vy;
                                    }
                                    if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                    else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                    gte_stflg(&g.flag);
                                    if (!(g.flag & 0x7F85E000)) {
                                        gte_stsz4(&g.sz0, &g.sz1, &g.sz2, &g.sz3);
                                        gte_stsxy((long *)&((PolyFT4 *)pkt)->x3);
                                        if (((PolyFT4 *)pkt)->x3 < mn) mn = ((PolyFT4 *)pkt)->x3;
                                        else if (mx < ((PolyFT4 *)pkt)->x3) mx = ((PolyFT4 *)pkt)->x3;
                                        if (mx >= -0xA0 && mn < 0xA1) {
                                            if (((PolyFT4 *)pkt)->y3 < mny) mny = ((PolyFT4 *)pkt)->y3;
                                            else if (my < ((PolyFT4 *)pkt)->y3) my = ((PolyFT4 *)pkt)->y3;
                                            if (my >= -0x78 && mny < 0x79) {
                                                s32 za, zb;
                                                u32 *otp;
                                                u32 *tp;
                                                u32 uvw;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;
                                                if (code == 3) g.opz = za + 0x20;
                                                *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                ((PolyFT4 *)pkt)->rgbc = tp[0];
                                                ((PolyFT4 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT4 *)pkt)->uvp1 = tp[2];
                                                uvw = tp[3];
                                                ((PolyFT4 *)pkt)->uv2 = uvw;
                                                ((PolyFT4 *)pkt)->uv3 = uvw >> 16;
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x28;
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    D_800A5E60 = pkt;
}

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017D610);


extern s32 func_800167F0(s32 a0);

s32 func_8017D674(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017D698);


extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);

s32 func_8017D6FC(s32 a0) {

    extern s16 D_800B9A0A;
    s16 s0;

    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_800D1E28();
        s0 = D_800B9A0A;
        if (s0 != 0x1000 || (s16)func_800D1D94() != s0) {
            func_8002D4C8(0x1C, 0);
            func_8001BFD0();
            func_8002D4C8(0x1D, 0);
            func_800D0C48(1);
        }
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017D7AC(void) {
        func_800D1EBC();
    }


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017D7CC);



















extern void func_8017DA90(void);
s32 func_8017D83C(s32 arg0)
{
  s32 temp_v0;
 do { func_8017DA90(); temp_v0 = (*((u8 *) (arg0 + 0x15))) + 1; *((u8 *) (arg0 + 0x15)) = temp_v0; } while (temp_v0 = 0);
  return temp_v0;
}


s32 func_8017D878(void) {
        return 0;
    }


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017D880);


extern void (*D_80187FF8[])(void);

void func_8017D8C8(void *a0) {
    D_80187FF8[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_80188000[])(void);

void func_8017D904(void *a0) {
    D_80188000[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_80188018[])(void);

void func_8017D940(void *a0) {
    D_80188018[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_801882F0[])(void);

void func_8017D97C(void *a0) {
    D_801882F0[*(u8 *)((s32)a0 + 0x214)]();
}


s32 func_8017D9B8(u8 *a0)
{
    s32 v = a0[532] + 1;
    a0[532] = v;
    return v;
}


extern void func_8016F0E4(void);
extern void func_80165770(void);
void func_8017D9CC(s32 a0) {
    func_8016F0E4();
    ((void (*)(s32))func_80165770)(a0);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D9FC(void) {

    extern s32 D_801882F8(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801882F8, 0x1000000);
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017DA24);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017DA5C);

extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017DA90(void) {

    extern s32 D_80188300(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80188300, 0x1000000);
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017DAB8);


extern void (*D_80188320[])(void);

void func_8017DB70(void *a0) {
    D_80188320[*(u8 *)((s32)a0 + 0x4)]();
}


















extern void func_8017DBEC(s32 a0, s32 a1);
extern void func_8017DD2C(void *a0);
void func_8017DBAC(s32 arg0)
{
  volatile unsigned char new_var;
  func_8017DBEC(arg0, arg0 + 0xA0);
  ;
  func_8017DD2C((void *) arg0);
}

void func_8017DBE0(u8 *a0) {
        *(s8 *)(a0 + 0xA0) = 0x6;
    }






extern u16 func_801487F4(s32 *a0);
extern u16 func_80148800(s32 *a0);
extern s32 func_80012A60(s32 a0, s32 a1);

void aF8017DBEC(void *a0, u8 *a1) __asm__("func_8017DBEC");
void aF8017DBEC(void *a0, u8 *a1)
{

    extern s32 D_80126B58;
    extern s16 D_80184854[];
    /* Dead aggregate local (idiom 6): args(0x10) + saves(7*4) alone give a 0x30
     * frame; the target is 0x38, i.e. vars != 0.  gcc-2.7.2 rounds the var area
     * to 8, so ONE dead word reproduces it (s32 pad[2] overshoots to 0x40). */
    s32 frame_pad[1];
    u8 dir;
    s32 lim;
    s32 flags;
    s32 held;
    s32 cur;

    dir = *a1;
    held = ((s32(*)(s32 *))func_801487F4)(&D_80126B58);
    cur = ((s32(*)(s32 *))func_80148800)(&D_80126B58);
    *(s16 *)((s32)a0 + 0x9C) = 0x5B;

    lim = 0;
    if (cur & 3) {
        lim = 0x555;
        flags = cur;
        *(s16 *)((s32)a0 + 0xA2) = 8;
    } else if (*(s16 *)((s32)a0 + 0xA2) == 0) {
        if (held & 3) {
            lim = 0x555;
            flags = held;
            *(s16 *)((s32)a0 + 0x9C) = 0x2D;
        }
    } else {
        *(s16 *)((s32)a0 + 0xA2) = *(s16 *)((s32)a0 + 0xA2) - 1;
    }

    if (lim != 0) {
        if (flags & 1) {
            dir = (dir - 1) & 7;
        } else if (flags & 2) {
            dir = (dir + 1) & 7;
        }
        if ((s16)func_80012A60(*(s16 *)((s32)a0 + 0x1A), D_80184854[dir]) < lim) {
            *a1 = dir;
        }
    }

    *(s16 *)((s32)a0 + 0x22) = D_80184854[*a1];
}






   /* 0x20: m@0, pad@0x12, t@0x14 */
      /* 8 bytes */

extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32);

void aF8017DD2C(s32 param_1) __asm__("func_8017DD2C");
void aF8017DD2C(s32 param_1)
{
    extern s16 D_80126940;
    extern s16 D_80126942;
    extern s16 D_80126944;

    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;
    register s32 lim __asm__("$16");

    lim = *(u16 *)(param_1 + 0x9C);

    {
        s32 delta = func_80012B04(*(s16 *)(param_1 + 0x1A), *(s16 *)(param_1 + 0x22), 0x14);
        if ((s16)delta > (s16)lim) {
            delta = lim;
        } else if ((s16)delta < -(s16)lim) {
            delta = -lim;
        }
        *(s16 *)(param_1 + 0x1A) = (*(u16 *)(param_1 + 0x1A) + delta) & 0xFFF;
        *(s16 *)(param_1 + 0x18) = func_80012ABC(*(s16 *)(param_1 + 0x18), *(s16 *)(param_1 + 0x20), 4);
    }

    *(s16 *)(param_1 + 0x1C) = func_80012ABC(*(s16 *)(param_1 + 0x1C), *(s16 *)(param_1 + 0x24), 4);
    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C(*(s16 *)(param_1 + 0x8),  *(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C(*(s16 *)(param_1 + 0x10), *(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C(*(s16 *)(param_1 + 0x28), *(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C(*(s16 *)(param_1 + 0x2A), *(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C(*(s16 *)(param_1 + 0x2C), *(s16 *)(param_1 + 0x32), 0x10);

    {
        s16 *p940 = &D_80126940;
        *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + *p940;
        *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + D_80126942;
        *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + D_80126944;
        func_80049CAC(param_1 + 0x18, (s32)&m1);

        m1.t[0] = *(s16 *)(param_1 + 0x28) + *p940;
        m1.t[1] = *(s16 *)(param_1 + 0x2A) + D_80126942;
        m1.t[2] = *(s16 *)(param_1 + 0x2C) + D_80126944;
    }
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017DF20);


extern void (*D_80188584[])(void);

void func_8017DF90(void *a0) {
    D_80188584[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017DFCC);

















extern s16 D_801C9320;
s32 func_8017E004(void)
{
  long new_var2;
  int new_var;
  new_var2 = 0x1;
  new_var2 = 0;
  new_var = D_801C9320 == new_var2;
  new_var += new_var2;
  ;
  return new_var;
}

extern void func_80029124(s32 a, s32 b);
void func_8017E014(void) {
    func_80029124(0x13C, 0x1);
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017E038);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017E0CC);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017E16C);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017E230);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017E2CC);


extern void (*D_801885C0[])(void);

void func_8017E4E4(void *a0) {
    D_801885C0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017E520);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017E830);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017E9B0);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017EA2C);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017EB14);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017EB78);

extern void func_80016714(void *a0, s32 a1);
extern s32 D_801C8C64;

void func_8017ED00(void) {
    func_80016714(&D_801C8C64, 0x380);
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017ED28);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017EE80);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017F018);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017F0EC);


extern void (*D_801888F4[])(void);

void func_8017F408(void *a0) {
    D_801888F4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017F444);

extern s16 D_801C8B70;

s32 func_8017F53C(void) {
    return D_801C8B70;
}



extern void (*D_80188948[])(void);

void func_8017F54C(void *a0) {
    D_80188948[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017F588);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017F600);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017F708);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017F748);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017F7E4);


extern void (*D_801889E0[])(void);

void func_8017F90C(void *a0) {
    D_801889E0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017F948);

extern void func_80029124(s32 arg0, s32 arg1);
    void func_8017F990(void) {
        func_80029124(0x13A, 1);
    }


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017F9B4);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017FA78);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017FB40);


extern void (*D_80188A78[])(void);

void func_8017FBD4(void *a0) {
    D_80188A78[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017FC10);

extern void func_80029124(s32 arg0, s32 arg1);
    void func_8017FC58(void) {
        func_80029124(0x139, 1);
    }


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017FC7C);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017FD40);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017FE08);


extern void (*D_80188B10[])(void);

void func_8017FE9C(void *a0) {
    D_80188B10[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017FED8);

extern void func_80029124(s32 arg0, s32 arg1);
    void func_8017FF20(void) {
        func_80029124(0x13B, 1);
        func_80029124(0x116, 1);
    }


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8017FF50);


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80180014);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_801800DC);


extern void (*D_80188B74[])(void);

void func_80180170(void *a0) {
    D_80188B74[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conformed to the TU (ov_SC04_018_jr_8017AE2C.c) — lever (A):
 *   func_8012A828 : TU declares `extern void func_8012A828(s32*, s32);`
 *                   at L3460 / L4615 / L5083 / L5372 / L5859 / L6004 / L6155 /
 *                   L6479 / L6504 / L6529.  The draft's `(s32, s32)` form caused
 *                   the 7697-vs-6529 conflict.  Conformed here; the type
 *                   disagreement is pushed to a cast at the call site.
 *   D_80184864    : TU declares `extern u8 D_80184864[];` (block scope, L3467).
 *                   Conformed; `(s32)D_80184864` == `(s32)&D_80184864`.
 *   func_801788B8 : verbatim from TU L2532 / L7756 (below the splice point).
 *   func_8012C354, D_80188B28, func_80180290, func_801801AC : no other
 *                   declaration anywhere in the TU (func_80180290 / func_801801AC
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

extern void func_80180290(void);

void func_801801AC(s32 a0) {

    extern M2C_UNK D_80188B28;
    extern u8 D_80184864[];
    s32 s0 = a0;
    if (func_8012C354(a0, (s32)&D_80188B28)) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(u16 *)(s0 + 0x2) = 1;
        func_8012A828((s32 *)s0, (s32)D_80184864);
        func_801788B8(s0, (s32)func_80180290);
    }
}


DEFINE_func_80180210()  /* dedup: shared engine-core @0x80180210 (src/shared) */


extern void func_80178CBC(s32 arg0, s32 arg1);
extern s32 D_80188B5C;

void func_80180218(void *arg0) {
    ((void (*)(void *, void *))func_80178CBC)(arg0, &D_80188B5C);
    *(s16 *)((u8 *)arg0 + 0x2) = 0x3;
}



extern int func_80178970(void);
extern void func_80178D18(void);

void func_80180250(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80180290);

extern void func_8018030C(void);
    void func_801802EC(void) {
        ((s32 (*)(void))func_8018030C)();
    }



// @class: regalloc-order
// @stuck: none — MATCH


extern void func_800183E0(s32 a0);

void func_8018030C(void)
{

    extern u32 D_801C8FE8;
    extern u16 D_80188B84[];
    extern u16 D_801C8FEC[];
    extern s32 D_80188BA4;
    u32 i;
    u16 *p;
    u32 base;
    u16 *tbl;

    i = 0;
    tbl = D_80188B84;
    base = D_801C8FE8 >> 8;
    p = D_801C8FEC;
    do {
        *p = tbl[(base + i) & 0xF] | 0x8000;
        i = i + 1;
        p = p + 1;
    } while (i < 0x10);
    func_800183E0((s32)&D_80188BA4);
    D_801C8FE8 = D_801C8FE8 + 0x100;
}



extern void (*D_80188C10[])(void);

void func_80180398(void *a0) {
    D_80188C10[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_801803D4);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80180440);

extern s32 func_80180514(void);

s32 func_80180514(void) {
    return 0x5B;
}



extern void (*D_80189330[])(void);

void func_8018051C(void *a0) {
    D_80189330[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern u32 D_80189320;

void func_80180558(s32 arg0) {
    s32 v0 = ((s32 (*)(s32))func_8012C1B8)(arg0);
    *(s32*)((u8*)arg0 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(arg0);
    } else {
        func_8001C214(v0, 0);
        *(s16*)((u8*)arg0 + 0x2) = 1;
        *(s16*)((u8*)arg0 + 0x5C) = 0x20;
        *(s32*)((u8*)arg0 + 0x58) = (u32)&D_80189320 | 0x40000000;
        *(s16*)((u8*)(*(s32*)((u8*)arg0 + 0x20)) + 0x12) = *(u16*)((u8*)arg0 + 0xFC);
    }
}


void func_801805D4(void) {
}


extern void (*D_80189368[])(void);

void func_801805DC(void *a0) {
    D_80189368[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_80180934(void *arg0);
extern s32 func_8012AD50(void *arg0);

/* 0x24-stride record at D_801C9010 (4 entries; asm/ov_SC04_018/data/tail18.data.s) */


void func_80180618(void *arg0) {

    extern u8 D_80078EB1;
    extern Ent_8017D6EC_80180618 D_801C9010[];
    s32 i;

    if (D_80078EB1 == 7) {
        for (i = 0; i < 4; i++) {
            Ent_8017D6EC_80180618 *p = &D_801C9010[i];

            p->unk16 = i;
            func_80180934(p);
            if (i & 1) {
                p->unk1C = 1;
            }
        }
        func_8012AD50(arg0);
    }
}






extern s32 func_8004787C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_801808E4(void);
extern void func_801809F0(void *arg0);

void aF801806A8(void *arg0) __asm__("func_801806A8");
void aF801806A8(void *arg0)
{

    extern u8 D_80078EB1;
    extern u8 D_80078E78[];
    extern u8 D_800AF630[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Ent_8017D6EC_8017DEE8 D_801C9010[];
    u8 *m;
    u8 *e78;
    s32 k;

    m = D_800AF630;
    e78 = D_80078E78;

    if (D_80078EB1 >= 9) {
        s32 count;
        s32 i;
        u8 *base;

        base = (u8 *)D_801C9010;
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
        u8 *p = (u8 *)D_801C9010 + k * 0x24;
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
                        ((void (*)(void *))func_801808E4)(p);
                    }
                }
            }
        }

        func_801809F0(p);
    }
}




/* func_801808E4 - iterate through 4-entry array, call func_80180934 if any unk1C is non-zero */

extern void func_80180934(void *arg0);




void func_801808E4(void) {

    extern Ent_8017D6EC D_801C9010[];
    s32 i = 0;
    Ent_8017D6EC *p = &D_801C9010[0];

    while (i < 4) {
        if (p->unk1C != 0) {
            func_80180934(p);
            break;
        }
        i++;
        p = (Ent_8017D6EC *)((char *)p + 0x24);
    }
}



extern s32 rand(void);

void func_80180934(void *arg0) {

    extern void (*D_80189338[])(void);
    s32 base = (s32)arg0;
    s32 r1;
    s32 r2;
    s32 h;
    s32 t;

    *(s32 *)(base + 0x0) = (s32)D_80189338;
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




/* func_801809F0 — build a 4-vertex SVECTOR quad from an 8-u16 source record,
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

void func_801809F0(void *arg0)
{
    s32 a0 = (s32)arg0;
    Prim_8017DAC4_801809F0 prim;
    Prim_8017DAC4_801809F0 *q;
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


void func_80180B08(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    }


void func_80180B18(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 2;
    }



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern s32 func_8012E57C(s32 a0, s32 a1);

s32 func_80180B28(void *a0, void *a1) {

    extern u8 D_801B27DC;
    s32 v0;
    s16 val;

    if (a1 == 0) {
        a1 = (void *)&D_801B27DC;
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



















extern void func_8012A828(s32*, s32);
void func_80180BC4(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  ((void (*)(s32, s32))func_8012A828)(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0x4)));
}


















extern void func_8012A828(s32 *a0, s32 a1);
void func_80180BF0(s32 *a0)
{
  s32 *p = *((s32 **) (((s32) a0) + 0xD0));
  func_8012A828(p, (*((s32 **) (((s32) (p = a0)) + 0xD0)))[2]);
}


















extern void func_8012A828(s32*, s32);
void func_80180C1C(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  ((void (*)(s32, s32))func_8012A828)(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0xc)));
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80180C48);


/* func_80180CCC — 76 instructions */

extern s32 func_80180E70(s32 arg0);

s32 func_80180CCC(s32 a0) {

    extern u8 D_80078E78[];
    extern u8 D_80078EB1;
    extern u16 D_80078EAC;
    extern s32 D_801C9250;
    extern s16 D_801B28F0[];
    extern s16 D_801B2924[];
    extern s32 D_801B27F0[][8];
    u8 *p;
    s32 s0;
    s32 t;
    s32 q;
    s32 r;
    s32 b;
    s32 c;
    s32 idx;

    p = D_80078E78;
    s0 = D_801B28F0[*(s16 *)(*(s32 *)(a0 + 0xD0) + 0x10)];
    if (s0 == -1) {
        D_801C9250 = 0;
        return 0;
    }

    t = func_80180E70(a0);
    q = t / 24;
    r = t % 24;
    b = D_80078EB1;
    c = D_80078EAC;

    if (t == 0) {
        idx = D_801B2924[b] - 1;
    } else if (c - q >= 5) {
        idx = 7;
    } else if (c == q && b - r >= 2) {
        idx = 6;
    } else {
        idx = p[0x39];
        idx = D_801B2924[idx] - 1;
    }

    ((struct { s32 w; } *)&D_801C9250)->w = 1;
    return D_801B27F0[idx][s0];
}



extern s32 func_80180CCC(s32 arg);
extern void func_80180E30(void *a0);

void func_80180DFC(void *a0) {
    *(s32 *)((char *)a0 + 0xe0) = func_80180CCC((s32)a0);
    func_80180E30(a0);
}





void func_80180E30(void *a0) {

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
    s32 func_80180E70(s32 arg0) {
        return *(short *)((char *)&D_800BA2BA + (*(short *)(*(s32 *)(arg0 + 0xd0) + 0x10) << 2));
    }



extern void (*D_801B2954[])(void);

void func_80180E98(void *a0) {
    D_801B2954[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80180ED4(void) {
}



void func_80180EDC(void *a0, s32 a1, s32 a2)
{

    extern u8 D_80078EB1;
    s32 v0;
    register s32 v1 __asm__("$3");

    v0 = D_80078EB1;
    if (!(v0 < a1)) {
        if (v0 < a2) {
            v0 = 1;
            v1 = *(s32 *)((s32)a0 + 0xCC);
        } else {
            v1 = *(s32 *)((s32)a0 + 0xCC);
            v0 = 2;
        }
    } else {
        v1 = *(s32 *)((s32)a0 + 0xCC);
        v0 = 2;
    }
    *(s32 *)(v1 + 0xB0) = v0;
}





s32 func_80180F18(s32 arg0, s32 arg1) {

    extern u8 D_80078EB1;
    return (D_80078EB1 >= arg0) && (D_80078EB1 < arg1);
}





s32 func_80180F3C(u8 a0, u8 a1, u8 a2, u8 a3) {

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


void func_80180F94(void *a0, s32 a1)
{
    Vec4s_80180F94 loc_10;
    Vec4s_80180F94 loc_18;
    Vec4s_80180F94 loc_20;

    loc_10.f0 = *(s16 *)((u8 *)a0 + 0x6);
    loc_10.f1 = *(s16 *)((u8 *)a0 + 0xA);
    loc_10.f2 = *(s16 *)((u8 *)a0 + 0xE);

    loc_18.f0 = 0;
    loc_18.f1 = 0;
    loc_18.f2 = (s16)(-a1);

    ((void(*)(s32, s32, s32))func_8012F214)((s32)a0, (s32)&loc_18, (s32)&loc_20);
    func_8012CEB0((s32)&loc_10, (s32)&loc_20, 0);
}





void func_80180FFC(s32 a0)
{

    extern s32 D_801B295C;
    *(s32 *)(a0 + 0x58) = (u32)&D_801B295C | 0x40000000;
    *(s16 *)(a0 + 0x5C) = 0x800;
}


void func_8018101C(void *a0) {
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }



extern void func_8012E8A8(u8 *a0);
extern void func_8012E8E0(s32 a0, s32 a1);

void func_80181024(s32 *a0, s32 a1) {
    func_8012E8A8((u8 *)a0);
    *(s16 *)((s32)a0 + 0x98) = 0;
    *(s16 *)((s32)a0 + 0x5C) = 0;
    func_8012E8E0((s32)a0, a1);
}


extern s32 func_80029504(void);

s32 func_8018106C(void) {
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

s32 func_801810C8(void) {
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

s32 func_8018113C(void) {
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

s32 func_801811B0(void) {
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

void func_8018120C(void) {
    if (((s32 (*)(void))func_80029504)() == 0x3A2) {
        ((void (*)(s32))func_80029514)(0x3AC);
    }
}




extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012B200(u8 *a0);

void func_80181240(s32 a0, s32 a1, s32 a2, s32 a3) {
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




/* func_80181310 @ 0x80184FA4 — ov_SC04_018_jr_8017AE2C
 * Decls copied verbatim from the TU (src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c):
 *   line 350   extern s32  func_8016F1AC(void);
 *   line 448   extern void func_8014B12C(void);      <- void! call through a cast (idiom 9)
 *   line 2616  extern s32  func_8012B608(s32, s32, s32);
 *   line 2617  extern void func_8012B178(s32, s32);
 *   line 2618  extern void func_8012AD80(s32);
 *   line 2619  extern s32  func_8012B030(u8 *);
 *   line 2620  extern s32  func_8012B744(void *, void *);
 *   line 2621  extern s32  func_8012BE98(s32, u16 *);
 *   line 4926  extern s32  func_80181310(s32 a0);
 */

extern s32 func_8016F1AC(void);
extern void func_8014B12C(void);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012BE98(s32 a0, u16 *a1);

s32 func_80181310(s32 a0) {
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

s32 func_801814D8(s32 a0) {
    if (func_8016F1C4() != 0) {
        return 0;
    }
    if (((s32 (*)(void))func_8014B12C)() != 0) {
        return 2;
    }
    return 1;
}



extern void (*D_801B2974[])(void);

void func_80181520(void *a0) {
    D_801B2974[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018155C(void) {
}

void func_80181564(void) {
}

void func_8018156C(void) {
}

void func_80181574(void) {
}

void func_8018157C(void) {
}


extern void func_80016714(void *a0, s32 a1);
extern void func_8012CAE4(void *a0);


void func_80181584(void *a0) {

    extern s32 D_801C9340;
    extern s32 D_801C9254;
    func_80016714(&D_801C9340, 0x14);
    D_801C9254 = 0;
    func_8012CAE4(a0);
}


void func_801815C8(void) {
}


/* §37 lever (A): conform to the TU's existing decl verbatim (TU lines 6430 /
 * 6862 both say `void`); the s32 return is recovered by a cast at the call
 * site below. Decl-only change => zero bytes move. */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012E8E0(s32 a0, s32 a1);


void func_801815D0(s32 a0) {

    extern s32 D_801B9BE0[];
    extern s32 D_801B296C[];
    s32 v0;
    s32 result;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    func_8001C214(v0, (s32)D_801B9BE0);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);

    result = *(s32 *)(a0 + 0x20);
    *(s32 *)(result + 0x4) |= 0x40;
    func_8012E8E0(a0, (s32)D_801B296C);

    *(s16 *)(a0 + 0x2) = 1;
}



extern void func_80181CE4(s32 a0);
extern void func_80181C70(s32 a0);
extern void func_80181D44(s32 a0);
extern void func_80181C08(s32 a0);

void func_80181658(s32 a0) {

    extern void (*D_801B2C4C[])(s32);
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
                    func_80181CE4(a0);
                } else {
                    func_80181C70(a0);
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
                    func_80181D44(a0);
                } else {
                    func_80181C08(a0);
                }
                *(s16 *)(a0 + 0xE8) = 1;
            }
        }
        break;
    case 3:
        if (*(u16 *)(a0 + 0x2) != 2 || *(u16 *)(a0 + 0x34) == 0) {
            func_80181C70(a0);
        }
        break;
    case 4:
        if (*(u16 *)(a0 + 0x2) != 2 || *(u16 *)(a0 + 0x34) == 0) {
            func_80181C08(a0);
        }
        break;
    }

    D_801B2C4C[*(u16 *)(a0 + 0x2)](a0);
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001C214(s32, s32);
extern void func_8001C97C(s32 a0);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_80181C08(s32 a0);
extern void *func_80181FD8(void *a0);



void func_80181830(s32 a0) {

    extern s32 D_801B297C[][2];
    extern u32 D_801B2994;
    extern u32 D_801B29B0;
    extern s16 D_801B29BC[];
    extern Blk12_801854C4_80181830 D_801B29A4;
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
    p = &D_801B29BC[idx];
    switch (idx) {
    case 7:
    case 9:
    case 10:
    case 12:
        func_8001C810(v0, D_801B297C[*p][0]);
        *(s32 *)(v0 + 4) |= 0x8040;
        break;
    default:
        func_8001C214(v0, D_801B297C[*p][0]);
        break;
    }

    func_8001C97C(D_801B297C[*p][1]);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0xC8, 0xB4);
    *(s32 *)(a0 + 0x58) = (u32)&D_801B2994 | 0x40000000;
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = (s32)&D_801B29B0;
    *(s16 *)(a0 + 0xE8) = 0;
    *(Blk12_801854C4_80181830 *)(a0 + 0xEC) = D_801B29A4;
    *(s16 *)(a0 + 0x10A) = 6;
    func_80181C08(a0);
    *(s32 *)(a0 + 0xDC) = (s32)func_80181FD8;
}




extern void func_801820DC(void *a0);
extern int func_80178970(void);
extern void func_80178D18(void);

void func_801819D0(void *a0) {
    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        break;
    case 1:
        func_801820DC(a0);
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



extern s32 func_801814D8(s32 a0);
extern void func_80181C70(s32 a0);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern s32 func_80182258(void);

void func_80181A4C(s32 a0) {
    s32 s0;
    u16 v0;
    u16 v1;

    if (func_801814D8(a0) == 2) {
        func_80181C70(a0);
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
        func_80181C70(s0);
    }

    ((void (*)(s32))func_80182258)(s0);
}


extern s32 func_80182258(void);
    void func_80181B18(void) {
        func_80182258();
    }



extern s32 func_801814D8(s32 a0);
extern void func_80181C08(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern s32 func_80182258(void);

void func_80181B38(s32 a0) {
    if (func_801814D8(a0) == 2) {
        func_80181C08(a0);
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
        func_80181C08(a0);
    } else {
        ((void (*)(s32))func_80182258)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80181C08);



extern s32 func_80182258(void);

void func_80181C70(s32 a0) {

    extern s32 D_801B297C[][2];
    extern s16 D_801B29BC[];
    s32 idx_val, ptr_val, data_val;

    *(s16 *)(a0 + 0x2) = 0x4;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0xFE) = 0x600;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x102) = 0;
    idx_val = D_801B29BC[*(s16 *)(a0 + 0x70)];
    ptr_val = *(s32 *)(a0 + 0x20);
    data_val = D_801B297C[idx_val][0];
    *(s32 *)(ptr_val + 0x24) = data_val;
    *(s16 *)(a0 + 0x84) = 0;
    *(s16 *)(a0 + 0x5C) = 0;
    *(s32 *)(a0 + 0xB0) = 0;
    func_80182258();
}


void func_80181CE4(s32 a0) {

    extern s16 D_801B29BC[];
    extern s32 D_801B297C[][2];
    *(s16 *)(a0 + 0x2) = 3;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0xFE) = 0;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x102) = 2;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x24) = D_801B297C[D_801B29BC[*(s16 *)(a0 + 0x70)]][0];
    *(s16 *)(a0 + 0x84) = 0;
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0xB0) = 0;
}



extern s32 func_80182258(void);

void func_80181D44(s32 a0) {

    extern s16 D_801B29BC[];
    extern s32 D_801B297C[][2];
    *(s16 *)(a0 + 0x2) = 1;
    *(s32 *)(a0 + 0x1C) = 8;
    *(s16 *)(a0 + 0xFE) = 0x600;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x102) = 2;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x24) = D_801B297C[D_801B29BC[*(s16 *)(a0 + 0x70)]][0];
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0xB0) = 0;
    func_80182258();
}





void func_80181DC4(s32 a0, s32 a1)
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
extern void func_80182398(s32 a0, s32 a1);

void func_80181E1C(s32 a0) {
    s32 v0 = func_8012E57C(0x61, (s16)a0);
    if (v0 != 0) {
        if (*(u16 *)((char *)v0 + 0x2) == 2) {
            *(s32 *)((char *)v0 + 0xB0) = 1;
        }
        func_80182398(a0, 0x3C);
    }
}




extern s32 func_8012E57C(s32 a0, s32 a1);

void func_80181E7C(s32 a0) {
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
extern void func_80182398(s32 a0, s32 a1);

void func_80181EC4(s32 a0) {
    s32 v1;

    v1 = func_8012E57C(0x61, (s32)(s16)a0);
    if (v1 != 0) {
        *(s16 *)((char *)v1 + 0x108) = 1;
        func_80182398(a0, 0x3C);
    }
}




extern s32 func_8012E57C(s32 a0, s32 a1);

void func_80181F14(s32 a0) {
    s32 shift_temp;
    s32 v1;

    shift_temp = ((a0 << 16) >> 16);
    v1 = func_8012E57C(0x61, shift_temp);
    if (v1 != 0) {
        *(s16 *)((char *)v1 + 0x108) = 2;
    }
}


extern s32 func_8012E57C(s32 a0, s32 a1);
s32 func_80181F4C(s32 a0) {
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
extern s32 func_8018207C(void *a0);
extern s32 func_80182614(void *a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

void *func_80181FD8(void *a0) {
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
    if (func_8018207C(a0) == 0) {
        return 0;
    }
    if (func_80182614(a0) != 0) {
        return 0;
    }
    *(s16 *)((s32)a0 + 0x34) = 1;
    func_80178BF8();
    return (void *)func_80172710;
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8018207C);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_801820DC);


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


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_801825C8);


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


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80182B54);


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

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80182D00);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80182DB4);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80182E1C);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80182E70);


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


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80183314);


extern void (*D_801C4480[])(void);

void func_8018338C(void *a0) {
    D_801C4480[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_801833C8);


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

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_801835DC);


extern void (*D_801C44E4[])(void);

void func_80183788(void *a0) {
    D_801C44E4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_801837C4);


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


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80183A24);

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


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80183C3C);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80183CF8);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80183DA4);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80183DE8);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80183F04);


extern void func_8012B414(int a0);
    void func_80183FA0(s32 arg0) {
        s32 temp_v1 = *(s32 *)(arg0 + 0x20);
        *(s16 *)(temp_v1 + 0x14) += 0x8;
        ((void (*)(void))func_8012B414)();
    }


INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80183FD4);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_8018404C);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80184094);

INCLUDE_ASM("asm/ov_SC04_015/nonmatchings/ov_SC04_015_jr_8017AE2C", func_80184138);


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





