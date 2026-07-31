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
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80192E18;
extern u8 D_80192D88;
extern u8 D_80192D64;
extern u8 D_80192D40;
extern u8 D_80192DF4;
extern u8 D_80192DD0;
extern u8 D_80192DAC;
extern u8 D_80192D1C;
extern void func_80145934(void);
extern u8 D_80192EA8;
extern u8 D_80192E84;
extern u8 D_80192E60;
extern u8 D_80192E3C;
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
extern unsigned char D_801922A0[];
extern unsigned char D_801922D0[];
extern unsigned char D_80192320[];
extern unsigned char D_80192350[];
extern unsigned char D_80192380[];
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
extern void (*D_801923D0[])(void *);
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
extern u8 D_801202A0[];
extern s32 func_80149F2C(s32 a0, s32 a1);
extern s32 func_80149E94(s32 arg0);
extern void func_80149FA8(void);
extern s32 D_80192498[];
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
extern u8 D_80192520[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80192528;
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
extern int D_801E3128;
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
extern s32 D_801E312C;
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
extern s32 D_80192558;
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
extern void (*D_80192600[])(void);
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
extern void (*D_80192624[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80192614;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80192638[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80192644[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80192654[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8019266C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8019265C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80192680[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8019269C[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8019268C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801926B0[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801926C4[])(void);
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
extern s32 D_801926D8;
extern void (*D_80192700[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801926E0;
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
extern int (*D_8019274C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80192750[])(void);
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
extern s32 func_8014C568(void *a0);
extern void func_801567BC(s32 a0);
extern u8 D_80126730[];
extern void func_80156848(s32 param_1, s32 param_2);
extern unsigned char D_8011520C[];
extern unsigned short D_80192BB4[];
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
extern void (*D_80192BC4[])(void);
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
extern int D_801E3160;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80192BEC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80192BCC;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80192BDC;
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
extern void (*D_80192C2C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80192C34[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80192C00;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80192C40[])(void);
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
extern u8 D_80192C10;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801E3168;
extern s32 D_801E3174;
extern s32 D_801E3178;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80192C7C[])(s32 *);
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
extern s32 D_80192C50[];
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
extern s32 D_801E3170;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80192ECC[])(void);
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
extern char D_80192CEC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80192F70[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_801930C4[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80192EE0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_801930CC[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80192EF0;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80192F10;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_801930D4[])(void);
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
extern void (*D_801930FC[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80193108[])(void);
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
extern void (*D_80192F7C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801931AC;
extern void func_8015D380(s32 a0);
extern unsigned char D_80192290[];
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
extern unsigned char D_801931C0[];
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
extern s8 D_801931FC[];
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
extern u16 D_80193244;
extern u16 D_80193246;
extern u16 D_80193248;
extern s32 D_8019324C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80193254;
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
extern int D_80192F60;
extern void func_8015EE7C(s32 param_1);
extern void func_80159B70(void*);
extern void (*D_80192F7C[])(void*);
extern void func_8015EEE0(void* arg0);
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
extern unsigned int D_801932D8[];
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
extern void (*D_80193388[])(void);
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
extern u16 D_801933B8[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8019341C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801E3180[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80193440[])(void);
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
extern int D_801E31D8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80193488[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80193478;
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
extern char D_801E26F8[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80193490[])(void);
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
extern void (*D_801934E4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801934AC;
extern s16 D_801934E0;
extern s16 D_801934DE;
extern s16 D_801934DC;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_801934F0[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E3238;
extern u8 D_801E3239;
extern u8 D_801E323A;
extern u8 D_801E323B;
extern u8 D_801E323C;
extern u8 D_801E323D;
extern u8 D_801E323E;
extern u8 D_801E323F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80193500[])(void);
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
extern s32 D_801E3278;
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
extern void (*D_80193544[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801935C0[];
extern s32 D_801935E0[];
extern u8 D_8019365C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8019367C[];
extern u8 D_8019369C[];
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
extern void (*D_80193738[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801937B4[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801E2708;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801937C0[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801937C8[])(void);
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
extern void (*D_80193890[])(void);
extern void func_80166618(void *a0);
extern void (*D_801938A0[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801938B0[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801938BC[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8019381C[];
extern u8   D_80193830[];
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
extern void (*D_801938D4[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801938DC[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801938E4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801938EC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_801938F4[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_801938FC[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80193904[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801939B8[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801939C0[])(void);
extern void func_80169F00(void *a0);
extern char D_80193970[];
extern char D_80193930[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_801939F8[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80193A04[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80193A4C[])(void);
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
extern void (*D_80193AC8[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E3598;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80193ABC[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80193B00[];
extern unsigned short D_80193B08[];
extern unsigned short D_80193B10[];
extern unsigned char D_801E35A0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E3598;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80193B18[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E36D4;
extern M2C_UNK D_801E36D8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E3660;
extern void (*D_80193B48[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E36DC[];
extern u8 D_801E36E4[];
extern u8 D_801E3694[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80193B50[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80193B6C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80193B74[])(void);
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
extern void (*D_80193BDC[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80193B80;
extern u8 D_80193B8C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80193C10[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80193C18[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80193C6C[])(void);
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
extern u16 D_80193CA0[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80193C90[];
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
extern s32 D_80193CBC;
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
extern void (*D_80193D34[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80193D3C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80193D44[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80193D4C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80193D54[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80193D5C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80193D68[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80193D74[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80193D80[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80193D90[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80193DA0[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80193DA8[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80193DB0[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80193DB8[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80193DC0[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80193DC8[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80193DD0[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80193DD8[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80193DE0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80193DE8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80193DF0[])(void);
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
extern void (*D_80193DF8[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80193E00[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80193E08[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80193E10[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80193E18[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80193E20[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80193E28[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80193E30[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80193E38[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80193E40[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80193E48[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80193E50[])(void);
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
extern void (*D_80193E94[])(void);
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
extern M2C_UNK D_80193E58;
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
extern void (*D_80193EC4[])(void);
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
extern void (*D_80193F00[])(void);
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
extern void (*D_80193F58[])();
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
extern void (*D_80193F68[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80193F70[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_801940D8[])();
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
extern void (*D_801940E4[])();
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
extern M2C_UNK D_801E2950;
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
extern s16 D_801E4BD8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801E3E18;
extern short D_801E4C4C;
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
extern s32 D_801E4244;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E426C;
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
extern s16 D_801E4228;
extern s32 func_8017A3B0(void);
extern short D_801E4264;
extern short D_801E4260;
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

extern s16 D_801E4BA8;
extern s16 D_801E4BAA;
extern s16 D_801E4BB4;

void func_8017AE2C(s32 param_1) {
    register s32 pv __asm__("$16") = param_1;
    register s16 *g __asm__("$17") = &D_801E4BA8;

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
                    func_8012B744(p, &D_801E4BB4);
                func_8012B178(pv, 0xFFFA0000);
                func_8012AD80(pv);
                *(u16 *)(pv + 0xA) -= 8;
                func_8012B030((u8 *)pv);
                /* &D_801E4BA8+0xC == &D_801E4BB4; distinct rtx defeats gcc's address-CSE
                   so BE98's arg rematerializes instead of sharing the store's reg (byte-gate). */
                if (func_8012BE98(pv, (u16 *)((s32)&D_801E4BA8 + 0xC)) < 0x101) {
                    D_801E4BA8 = 0;
                    D_801E4BAA = 0;
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
            func_8012B744((void *)(pv + 4), &D_801E4BB4);
        func_8012B178(pv, 0xFFFA0000);
        func_8012AD80(pv);
        *(u16 *)(pv + 0xA) -= 8;
        func_8012B030((u8 *)pv);
        /* see note above: distinct rtx for the same address defeats address-CSE. */
        if (func_8012BE98(pv, (u16 *)((s32)&D_801E4BA8 + 0xC)) < 0x101) {
            D_801E4BA8 = 0;
            D_801E4BAA = 0;
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
    extern s16 D_801E42A4;
    extern s16 D_801E42A6;
    extern s16 D_801E42A8;
    extern s16 D_801E429C;
    extern s16 D_801E429E;
    extern s16 D_801E42A0;

    *(s32 *)(((s32)param_1) + 0x48) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x48), (s32)D_801E42A4, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x4C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x4C), (s32)D_801E42A6, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x50) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x50), (s32)D_801E42A8, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x3C) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x3C), (s32)D_801E429C, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x40) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x40), (s32)D_801E429E, (s32)((s16)param_2));
    *(s32 *)(((s32)param_1) + 0x44) = (s16)func_80012C6C((s32)*(s16 *)(((s32)param_1) + 0x44), (s32)D_801E42A0, (s32)((s16)param_2));
}



extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s16 D_801E422C;
extern u16 D_801E42AC;
extern u16 D_801E42AE;
extern u16 D_801E42B0;
extern s16 D_801E4BD8;

void func_8017B1D8(void) {
    func_8012A418();
    D_801E4BD8 = 0;
    D_801E422C = 0;
    D_801E42AC = D_80126B5E;
    D_801E42AE = D_80126B62;
    D_801E42B0 = D_80126B66;
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
    extern u8 D_80194220[];
    extern s16 D_801E42A4;
    extern s16 D_801E429C;
    extern u8 D_8012694C;


    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B238_8017B238 *)&buf[0] = *(Blk8_8017B238_8017B238 *)src;
        *(Blk8_8017B238_8017B238 *)&buf[8] = *(Blk8_8017B238_8017B238 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80194220[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80194220[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801E42A4;
        s16 *p78C = &D_801E429C;
        *(Blk8_8017B238_8017B238 *)p794 = *(Blk8_8017B238_8017B238 *)&buf[0];
        *(Blk8_8017B238_8017B238 *)p78C = *(Blk8_8017B238_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801E4BD8 = 1;
        D_801E422C = 0;
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
    extern SV4_8017B368 D_801E424C;
    extern SV4_8017B368 D_801E4254;
    extern s16 D_801E42A4;
    extern s16 D_801E429C;
    extern u16 D_80194220;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801E424C;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801E4254;
    } else {
        s32 ax = (s32)&((Pair16_8017B368 *)&D_80194220)[n].x;
        s32 ay = (s32)&((Pair16_8017B368 *)&D_80194220)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801E42A4) = loc0;
    (*(SV4_8017B368 *)&D_801E429C) = loc1;
    D_801E4BD8 = 1;
    D_801E422C = 0;
}





s32 func_8017B490(s32 param)
{
    extern void func_8017BA3C(s32 param_1, s32 param_2);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern SV4_8017B368 D_801E424C;
    extern SV4_8017B368 D_801E4254;
    extern s16 D_801E42A4;
    extern s16 D_801E429C;
    extern u16 D_80194220;
    extern s16 D_801E422C;
    extern s16 D_801E4BD8;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;

    SV4_8017B368 loc0;
    SV4_8017B368 loc1;
    u32 n = (u32)&D_801E424C;

    ((void (*)(void))func_8017BA3C)();

    if (n >= 0xB) {
        loc0 = *(SV4_8017B368 *)n;
        loc1 = D_801E4254;
    } else {
        s32 ax = (s32)&((Pair16 *)&D_80194220)[n].x;
        s32 ay = (s32)&((Pair16 *)&D_80194220)[n].y;
        func_8012F214(param, ax, (s32)&loc0);
        func_8012F214(param, ay, (s32)&loc1);
    }

    (*(SV4_8017B368 *)&D_801E42A4) = loc0;
    (*(SV4_8017B368 *)&D_801E429C) = loc1;
    D_801E4BD8 = 1;
    D_801E422C = 0x1E;
    D_80126990 = (*(SV4_8017B368 *)&D_801E42A4).a;
    D_80126994 = (*(SV4_8017B368 *)&D_801E42A4).b;
    D_80126998 = (*(SV4_8017B368 *)&D_801E42A4).c;
    D_80126984 = (*(SV4_8017B368 *)&D_801E429C).a;
    D_80126988 = (*(SV4_8017B368 *)&D_801E429C).b;
    D_8012698C = (*(SV4_8017B368 *)&D_801E429C).c;
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
    extern u8 D_80194220[];
    extern s16 D_801E42A4;
    extern s16 D_801E42A6;
    extern s16 D_801E42A8;
    extern s16 D_801E429C;
    extern s16 D_801E429E;
    extern s16 D_801E42A0;
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
        s32 a1addr = (s32)&D_80194220[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80194220[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801E42A4;
        s16 *p78C = &D_801E429C;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_801E42A6;
            v798 = D_801E42A8;
            v78C = *p78C;
            v78E = D_801E429E;
            v790 = D_801E42A0;
            __asm__ __volatile__("");
            D_801E4BD8 = 1;
            D_801E422C = 0x1E;
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
extern s16 D_801E422C;
extern s16 D_801E42A4;
extern s16 D_801E42A6;
extern s16 D_801E42A8;
extern s16 D_801E429C;
extern s16 D_801E429E;
extern s16 D_801E42A0;

void func_8017B7A8(void)
{
    D_8012694C = 1;
    D_801E422C = 0;
    D_801E42A4 = (s16) D_80114F30;
    D_801E42A6 = (s16) D_80114F34;
    D_801E42A8 = (s16) D_80114F38;
    D_801E429C = (s16) D_80114F24;
    D_801E429E = (s16) D_80114F28;
    D_801E42A0 = (s16) D_80114F2C;
}




extern s32 D_801151D4;
extern s16 D_801E42BC;
extern s16 D_801E42BE;
extern s16 D_801E42C0;
extern s16 D_801E42C4;
extern s16 D_801E42C6;
extern s16 D_801E42C8;

void func_8017B824(void) {
    D_801E42BC = (s16) M2C_FIELD(D_801151D4, s32 *, 0x48);
    D_801E42BE = (s16) M2C_FIELD(D_801151D4, s32 *, 0x4C);
    D_801E42C0 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x50);
    D_801E42C4 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x3C);
    D_801E42C6 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x40);
    D_801E42C8 = (s16) M2C_FIELD(D_801151D4, s32 *, 0x44);
}



// @class: schedule
// @stuck: none — MATCH

extern s16 D_801E42BC;
extern s16 D_801E42BE;
extern s16 D_801E42C0;
extern s16 D_801E42C4;
extern s16 D_801E42C6;
extern s16 D_801E42C8;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

void func_8017B880(void)
{
    D_80114F30 = D_801E42BC;
    D_80114F34 = D_801E42BE;
    D_80114F38 = D_801E42C0;
    D_80114F24 = D_801E42C4;
    D_80114F28 = D_801E42C6;
    D_80114F2C = D_801E42C8;
}


// @class: struct
// @stuck: none — MATCH

/* 16-byte unaligned block copy from param to two adjacent align-1 globals.
   src[0..7] -> (*(S8_8017B8E8 *)&D_801E42A4), src[8..15] -> (*(S8_8017B8E8 *)&D_801E429C) (source order).
   An 8-byte struct of u8 has alignment 1, so gcc copies it via lwl/lwr+swl/swr. */



s32 func_8017B8E8(s32 src) {
    (*(S8_8017B8E8 *)&D_801E42A4) = ((S8_8017B8E8 *)src)[0];
    (*(S8_8017B8E8 *)&D_801E429C) = ((S8_8017B8E8 *)src)[1];
}




// @class: struct
// @stuck: none — MATCH (63 ins)

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u16 D_801E42AC;
extern u16 D_801E42AE;
extern u16 D_801E42B0;

extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;
extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;

extern u8  D_8012694C;
extern s16 D_801E422C;
extern short D_801E42B4;
extern short D_801E42B6;
extern short D_801E42B8;
extern s16 D_801E42A4;
extern s16 D_801E42A6;
extern s16 D_801E42A8;
extern s16 D_801E429C;
extern s16 D_801E429E;
extern s16 D_801E42A0;

void func_8017B940(void)
{
    s32 buf[3];

    D_8012694C = 2;
    buf[0] = (*(s16 *)&D_80126B5E) - (*(s16 *)&D_801E42AC);
    buf[1] = (*(s16 *)&D_80126B62) - (*(s16 *)&D_801E42AE);
    buf[2] = (*(s16 *)&D_80126B66) - (*(s16 *)&D_801E42B0);
    (*(s16 *)&D_801E42B4) = buf[0];
    (*(s16 *)&D_801E42B6) = buf[1];
    (*(s16 *)&D_801E42B8) = buf[2];
    D_801E42A4 = D_80114F30 + buf[0];
    D_801E422C = 0;
    D_801E42A6 = D_80114F34 + buf[1];
    D_801E42A8 = D_80114F38 + buf[2];
    D_801E429C = D_80114F24 + buf[0];
    D_801E429E = D_80114F28 + buf[1];
    D_801E42A0 = D_80114F2C + buf[2];
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

extern SV4 D_801E424C;
extern SV4 D_801E4254;

void func_8017BA3C(s32 param_1, s32 param_2)
{
    SV4 v0;            /* sp+0x10 : func_80049CAC arg0 */
    MTX mtx;           /* sp+0x18 : MATRIX_L48, t[] at sp+0x2c */
    SV4 v1;            /* sp+0x38 : RotTransSV arg0 */
    SV4 svec;          /* sp+0x40 : func_8012F214 out */
    SV4 buf1;          /* sp+0x48 : RotTransSV arg1 (-> D_801E4254) */
    SV4 buf2;          /* sp+0x50 : RotTransSV arg2 */

    func_8012F214(param_1, param_2, (s32)&svec);
    D_801E424C = svec;

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
    D_801E4254 = buf1;
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
    SV4_8017BB34 buf1;          /* sp+0x48 : RotTransSV arg1 (-> (*(SV4_8017BB34*)&D_801E4254)) */
    SV4_8017BB34 buf2;          /* sp+0x50 : RotTransSV arg2 */

    svec = *(SV4_8017BB34 *)param_2;
    (*(SV4_8017BB34*)&D_801E424C) = svec;

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
    (*(SV4_8017BB34*)&D_801E4254) = buf1;
}




// @class: regalloc-order
// @stuck: pending self-check — register order param=$s2 counter=$s1 ptr=$s0

extern void (*D_801E4274[10])(int);

void func_8017BC38(int param_1)
{
    register int i __asm__("$17");
    register void (**p)(int) __asm__("$16");

    i = 0;
    p = D_801E4274;
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
extern s16 D_801E422C;
extern s16 D_801E4BD8;

void func_8017BCA0(int param_1) {
    func_8017B0E4(param_1, 0xC);
    D_801E422C = D_801E422C + 1;
    if (D_801E422C >= 0x1F) {
        D_801E4BD8 = 2;
    }
}




// @class: plumbing
// @stuck: none — MATCH expected (simple short-increment + guarded call)

extern s16 D_801E422C;
extern s16 D_801E4BD8;

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

void func_8017BCF4(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801E422C = D_801E422C + 1;
    if (0x18 < D_801E422C) {
        func_8012A4BC();
        D_801E4BD8 = 0;
    }
    return;
}




// @class: regalloc-order
// @stuck: none — MATCH (branch-polarity invert: fn-ptr non-zero call is the fall-through arm)

extern void func_8017B0E4(int, int);
extern void func_8012A4BC(void);

extern s16 D_801E422C;
extern void (*D_801E4270)(void);
extern short D_801E42B4;
extern short D_801E42B6;
extern short D_801E42B8;
extern s16 D_801E4BD8;

extern s32 D_80114F24;
extern s32 D_80114F28;
extern s32 D_80114F2C;
extern s32 D_80114F30;
extern s32 D_80114F34;
extern s32 D_80114F38;

void func_8017BD50(int param_1)
{
    func_8017B0E4(param_1, 6);
    D_801E422C = D_801E422C + 1;
    if (D_801E422C >= 0x19) {
        if (D_801E4270 != 0) {
            (*D_801E4270)();
        } else {
            D_80114F30 = D_80114F30 + D_801E42B4;
            D_80114F34 = D_80114F34 + D_801E42B6;
            D_80114F38 = D_80114F38 + D_801E42B8;
            D_80114F24 = D_80114F24 + D_801E42B4;
            D_80114F28 = D_80114F28 + D_801E42B6;
            D_80114F2C = D_80114F2C + D_801E42B8;
            func_8012A4BC();
        }
        D_801E4BD8 = 0;
    }
}



extern void (*D_801942C0[])(void);

void func_8017BE60(void *a0) {
    D_801942C0[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017BE9C);

extern void func_8017BF14(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
    void func_8017BEC0(s32 arg0, s32 arg1, s16 arg2) {
        func_8017BF14(arg0, arg1, arg2, 0);
    }


extern void func_8017BF14(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
    void func_8017BEE8(void *a0, void *a1, s32 a2, s32 a3) {
        ((void (*)(void *, void *, s32, s32))func_8017BF14)(a0, a1, (s16)a2, (s16)a3);
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017BF14);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017BF9C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017BFF0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017C048);


extern void (*D_80194320[])(void);

void func_8017C0F4(void *a0) {
    D_80194320[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017C130);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017C41C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017C8B0);

extern void ReadRotMatrix(void *a0);
extern void PushMatrix(void);
extern void func_8004974C(void *a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void PopMatrix(void);
void func_8017CC88(u16 *a0, void *a1) {
    s32 mat[8];
    s32 buf[8];
    s16 sv[4];
    ReadRotMatrix((void *)mat);
    PushMatrix();
    sv[0] = (s16)(a0[0] - *(s32 *)((u8 *)mat + 0x14));
    sv[1] = (s16)(a0[1] - *(s32 *)((u8 *)mat + 0x18));
    sv[2] = (s16)(a0[2] - *(s32 *)((u8 *)mat + 0x1C));
    func_8004974C((void *)mat, (void *)buf);
    ApplyMatrixSV((void *)buf, (void *)sv, a1);
    PopMatrix();
}


int func_8017CD2C(short *param_1, short *param_2, short *param_3, int param_4) {
    register int i2o __asm__("$5");
    register int i4o __asm__("$9");
    short sVar1; int rx, rz, uVar5;
    i4o = param_2[1];
    __asm__ __volatile__("" : : "r"(i4o));
    i2o = param_1[1]; uVar5 = 0;
    if (i2o >= i4o) {
        rx = param_1[0] - i2o * (param_2[0] - param_1[0]);
        rz = param_1[2] - i2o * (param_2[2] - param_1[2]);
    } else {
        register int den __asm__("$3");
        int p2x = param_2[0], p2z = param_2[2];
        den = i2o - i4o;
        rx = p2x + i4o * (p2x - param_1[0]) / den;
        rz = p2z + i4o * (p2z - param_1[2]) / den;
    }
    if (rx >= -0x7fff) { i2o = 0x7fff; if (rx < 0x8000) i2o = rx; }
    else i2o = -0x7fff;
    *param_3 = (short)i2o;
    if (rz >= -0x7fff) { i2o = 0x7fff; if (rz < 0x8000) i2o = rz; }
    else i2o = -0x7fff;
    param_3[2] = (short)i2o; param_3[1] = 0; sVar1 = (short)param_4;
    if ((int)*param_3 < *param_1 - param_4) { uVar5 = 0xffffffff; *param_3 = *param_1 - sVar1; }
    if (*param_1 + param_4 < (int)*param_3) { uVar5 = 0xffffffff; *param_3 = *param_1 + sVar1; }
    if ((int)param_3[2] < param_1[2] - param_4) { uVar5 = 0xffffffff; param_3[2] = param_1[2] - sVar1; }
    if (param_1[2] + param_4 < (int)param_3[2]) { uVar5 = 0xffffffff; param_3[2] = param_1[2] + sVar1; }
    return uVar5;
}


extern void ReadGeomOffset(s32 *a0, s32 *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8004921C(s32 a0, s32 a1);
void func_8017CF24(s32 a0, s32 a1) {
    s32 ofx;
    s32 ofy;
    s32 sxy;
    s32 p;
    ReadGeomOffset(&ofx, &ofy);
    func_8004921C(0, 0);
    RotTransPers(a0, a1, &sxy, &p);
    func_8004921C(ofx, ofy);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017CF90);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017DE5C);

extern void func_8012A018(s32 a, s32 b);
    extern void func_8017E97C();
    void func_8017DF00(void) {
        ((void (*)(void *, s32))func_8012A018)((void *)func_8017E97C, 0x2);
    }


extern void func_8012A018(s32 a, s32 b);
    extern void func_8017E97C();
    void func_8017DF28(void) {
        ((void (*)(void *, s32))func_8012A018)((void *)func_8017E97C, 0x3);
    }


extern void func_8012A018(s32 a, s32 b);
    extern void func_8017E97C(void *a0);
    void func_8017DF50(void) {
        ((void (*)(void *, s32))func_8012A018)((void *)func_8017E97C, 0x8);
    }


#include "common.h"

/* func_8017DF78 — one of the "install actor-behaviour preset N" thunks in this
 * TU: pokes the shared preset block at 0x80126954..0x8012697A, registers the
 * dispatcher func_8017E97C with mode 8, then runs the two fixups over the
 * record at D_80126948.
 *
 * §71 sibling-first: func_8017DF50 (same TU, 0x28 bytes earlier) is the bare
 * `((void (*)(void *, s32))func_8012A018)((void *)func_8017E97C, 0x8);` form,
 * and func_8017E014 (immediately AFTER this one) is the byte-for-byte same
 * skeleton with different constants — copy its shape verbatim.
 * D_80126948 is `u8 []` fleet-canon (line 667 of the split TU); taking it once
 * and using it in both calls is what puts &D_80126948 in $s0 across the calls.
 */

extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017E97C(void *a0);

extern u8 D_80126948[];
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017DF78(void) {
    D_80126954 = 0x12C;
    D_8012695C = 0x28A;
    D_80126968 = 0x238;
    D_8012696A = 0x600;
    D_8012696C = 0;
    D_80126976 = -0x80;
    D_80126978 = 0;
    D_8012697A = -0x80;
    ((void (*)(void *, s32))func_8012A018)((void *)func_8017E97C, 0x8);
    func_8012A094((s32)D_80126948);
    func_8017E97C((void *)D_80126948);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E014);

#include "common.h"

typedef struct {
    s16 vx, vy, vz, pad;
} Vec8_8017E0B4;

extern Vec8_8017E0B4 D_801E2D70;
extern Vec8_8017E0B4 D_801E2D78;

extern s32 D_80126E60[];
extern s32 D_80126E6C;
extern s32 D_80126E9C;
extern s32 D_80126EA0;
extern s32 D_80126EA4;
extern s32 D_80126EA8;
extern s32 D_80126EAC;
extern s32 D_80126EB0;

extern void func_80129FF4(void);
extern void func_8012A094(s32 a0);
extern void func_8012A100(s8 a0);

void func_8017E0B4(void)
{
    Vec8_8017E0B4 a;
    Vec8_8017E0B4 b;

    a = D_801E2D70;
    b = D_801E2D78;

    D_80126E6C = 500;
    D_80126E9C = a.vx;
    D_80126EA0 = a.vy;
    D_80126EA4 = a.vz;
    D_80126EA8 = b.vx;
    D_80126EAC = b.vy;
    D_80126EB0 = b.vz;

    func_80129FF4();
    func_8012A094((s32)D_80126E60);
    func_8012A100(1);
}





extern void func_80129FF4(void);
extern void func_8012A094(s32 a0);
extern void func_8012A100(s8 a0);

void func_8017E190(void)
{

    extern Vec8_8017E0B4 D_801E2D80;
    extern Vec8_8017E0B4 D_801E2D88;
    extern s32 D_80126F04[];
    extern s32 D_80126F10;
    extern s32 D_80126F40;
    extern s32 D_80126F44;
    extern s32 D_80126F48;
    extern s32 D_80126F4C;
    extern s32 D_80126F50;
    extern s32 D_80126F54;
    Vec8_8017E0B4 a;
    Vec8_8017E0B4 b;

    a = D_801E2D80;
    b = D_801E2D88;

    D_80126F10 = 500;
    D_80126F40 = a.vx;
    D_80126F44 = a.vy;
    D_80126F48 = a.vz;
    D_80126F4C = b.vx;
    D_80126F50 = b.vy;
    D_80126F54 = b.vz;

    func_80129FF4();
    func_8012A094((s32)D_80126F04);
    func_8012A100(2);
}





extern void func_80129FF4(void);
extern void func_8012A094(s32 a0);
extern void func_8012A100(s8 a0);

void func_8017E26C(void)
{

    extern Vec8_8017E0B4 D_801E2D90;
    extern Vec8_8017E0B4 D_801E2D98;
    extern s32 D_80126FA8[];
    extern s32 D_80126FB4;
    extern s32 D_80126FE4;
    extern s32 D_80126FE8;
    extern s32 D_80126FEC;
    extern s32 D_80126FF0;
    extern s32 D_80126FF4;
    extern s32 D_80126FF8;
    Vec8_8017E0B4 a;
    Vec8_8017E0B4 b;

    a = D_801E2D90;
    b = D_801E2D98;

    D_80126FB4 = 500;
    D_80126FE4 = a.vx;
    D_80126FE8 = a.vy;
    D_80126FEC = a.vz;
    D_80126FF0 = b.vx;
    D_80126FF4 = b.vy;
    D_80126FF8 = b.vz;

    func_80129FF4();
    func_8012A094((s32)D_80126FA8);
    func_8012A100(3);
}





extern void func_80129FF4(void);
extern void func_8012A094(s32 a0);
extern void func_8012A100(s8 a0);

void func_8017E348(void)
{

    extern Vec8_8017E0B4 D_801E2DA0;
    extern Vec8_8017E0B4 D_801E2DA8;
    extern s32 D_80126F04[];
    extern s32 D_80126F10;
    extern s32 D_80126F40;
    extern s32 D_80126F44;
    extern s32 D_80126F48;
    extern s32 D_80126F4C;
    extern s32 D_80126F50;
    extern s32 D_80126F54;
    Vec8_8017E0B4 a;
    Vec8_8017E0B4 b;

    a = D_801E2DA0;
    b = D_801E2DA8;

    D_80126F10 = 460;
    D_80126F40 = a.vx;
    D_80126F44 = a.vy;
    D_80126F48 = a.vz;
    D_80126F4C = b.vx;
    D_80126F50 = b.vy;
    D_80126F54 = b.vz;

    func_80129FF4();
    func_8012A094((s32)D_80126F04);
    func_8012A100(2);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E424);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E454);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E4F8);

extern void func_8012A0E0(void);
    void func_8017E5AC(void) {
        ((s32 (*)(void))func_8012A0E0)();
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E5CC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E664);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E6FC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E798);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E898);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E8E4);



void func_8017E97C(void *a0) {

    extern void (*D_80194328[])(void);
    D_80194328[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017E9B8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017EA74);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017EA9C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017EAD4);

void func_8017EB30(void) {
}

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017EB38);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017EB8C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017ECAC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017ED28);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017EDF8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017EFB4);


extern void (*D_8019439C[])(void);

void func_8017F010(void *a0) {
    D_8019439C[*(u8 *)((s32)a0 + 0x15)]();
}



// @class: plumbing
// @stuck: none — MATCH (simple two-call wrapper, $s0 holds param across calls by default regalloc)

extern void func_8017F428(void *arg0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_800167B8(s32 a0);

s32 func_8017F04C(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_8017F428, 0x1000000);
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017F09C(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_801943A4[])(void);

void func_8017F0C0(void *a0) {
    D_801943A4[*(u8 *)((s32)a0 + 0x15)]();
}


s32 func_8017F0FC(u8 *a0) {
        *(s32 *)(a0 + 0x28) = 0x14;
        a0[0x15] += 1;
        return 0;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F118);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F194);


extern void (*D_80194454[])(void);

void func_8017F1DC(void *a0) {
    D_80194454[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_80171B44(s32 *a0);
    void func_8017F218(u8 *a0) {
        *(s8 *)(a0 + 0x214) += 1;
        ((void (*)(void))func_80171B44)();
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F244);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F2C4);


// @class: plumbing
// @stuck: none — MATCH (param_1 survives across func_8016F0E4 → lands in $s0; passed to func_80165770)

extern void func_8016F0E4(void);
extern void func_80165770(void);
extern void func_80175414(s32);

void func_8017F320(s32 param_1)
{
    func_8016F0E4();
    ((void (*)(s32))func_80165770)(param_1);
    ((void (*)(void))func_80175414)();
}



extern void (*D_80194464[])(void);

void func_8017F358(void *a0) {
    D_80194464[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F394);


// @class: plumbing
// @stuck: none — MATCH (expected); simple call + conditional u8 increment

extern s32 func_80171B4C(s32 a0, s32 a1);

void func_8017F3C4(int param_1)
{
    if (func_80171B4C(param_1, 0x2) != 0) {
        *(unsigned char *)(param_1 + 0x214) += 1;
    }
    return;
}


extern void func_8016F0E4(void);
    void func_8017F408(void) {
        func_8016F0E4();
    }



extern void (*D_80194470[])(void);

void func_8017F428(void *a0) {
    D_80194470[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F464);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F530);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F5B0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F63C);


extern s32 D_801270C8;
extern void func_8017F6A4(void);

void func_8017F674(void) {
    if (D_801270C8 == 6) {
        func_8017F6A4();
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F6A4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F6E8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F748);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F7CC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F898);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F924);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017F998);

extern s32 D_801270C8;
extern void func_8017FA3C(void);

void func_8017FA0C(void) {
    if (*(s32 *)&D_801270C8 == 0xC) {
        ((void (*)(void))func_8017FA3C)();
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FA3C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FA94);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FB14);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FB80);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FC64);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FCFC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FDB4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FE08);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FEA0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FF2C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FF8C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8017FFF0);


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180060);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801800CC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018016C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801801DC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180234);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801802CC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180328);


extern void (*D_801944E8[])(void);

void func_80180380(void *a0) {
    D_801944E8[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801803BC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180454);

extern void func_8016EE94();
    extern char func_801804D4[];
    void func_801804AC(void) {
        ((void (*)(char *, unsigned int))func_8016EE94)(func_801804D4, 0x1000000);
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801804D4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180510);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180574);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180610);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018074C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801808B0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180A3C);

extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
    extern void func_80180AA4(void *a0);
    void func_80180A7C(void) {
        ((void (*)(s32, s32))func_8016EDEC)((s32)&func_80180AA4, 0x1000000);
    }




void func_80180AA4(void *a0) {

    extern void (*D_80194544[])(void);
    D_80194544[*(u8 *)((s32)a0 + 0x214)]();
}


extern void func_8014C6C0(void);
void func_80180AE0(void *a0) {
    ((void (*)(void *))func_8014C6C0)(a0);
    *(u8 *)((s32)a0 + 0x214) += 1;
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180B18);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180B90);

extern void func_8014C6AC(void);
extern void func_8016F0E4(void);
extern void func_80165770(void);
void func_80180C04(void *a0) {
    ((void (*)(void *))func_8014C6AC)(a0);
    ((s32 (*)(struct S *))func_8016F0E4)((struct S *)a0);
    ((void (*)(void *))func_80165770)(a0);
}


extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_80180C64(void*);
void func_80180C3C(void) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_80180C64, 0x1000000);
}



extern void (*D_8019455C[])(void);

void func_80180C64(void *a0) {
    D_8019455C[*(u8 *)((s32)a0 + 0x214)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180CA0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180D18);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180DB8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180E08);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180F5C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80180FA8);

extern void func_8017E798(void *a0);
void func_80181028(void *a0) {
    func_8017E798(a0);
    *(u8 *)((s32)a0 + 0x214) += 1;
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181060);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801810F0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018112C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018118C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181238);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181270);

extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_801812DC(void*);
void func_801812B4(void) {
    ((void (*)(void *, s32))func_8016EDEC)((void *)func_801812DC, 0x1000000);
}



extern void (*D_8019458C[])(void);

void func_801812DC(void *a0) {
    D_8019458C[*(u8 *)((s32)a0 + 0x214)]();
}


void func_80181318(void *a0) {
        *(s32 *)((s32)a0 + 0x204) = 0x20;
        *(u8 *)((s32)a0 + 0x214) += 1;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181330);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181388);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801813F0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018141C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801814B4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181570);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801815FC);

extern void func_80147060(u8*);
extern void func_8016F0E4(void);
void func_8018166C(s32 a0) {
    ((void (*)(void))func_80147060)();
    ((void (*)(s32))func_8016F0E4)(a0);
}


s32 func_8018169C(s32 a0, s32 a1) {
    s32 a2 = *(s32 *)((s32)a0 + 0x20);
    u16 v1 = *(u16 *)((s32)a0 + 0x206);
    u16 v0 = *(u16 *)((s32)a2 + 0x12);
    *(u16 *)((s32)a2 + 0x12) = (v0 + v1) & 0xFFF;
    return (*(s32 *)((s32)a0 + 0x204) -= a1);
}


s32 func_801816CC(s32 a0, s32 a1) {
    s32 a2 = *(s32 *)((s32)a0 + 0x20);
    u16 v1 = *(u16 *)((s32)a0 + 0x20A);
    u16 v0 = *(u16 *)((s32)a2 + 0x10);
    *(u16 *)((s32)a2 + 0x10) = (v0 - v1) & 0xFFF;
    return (*(s32 *)((s32)a0 + 0x208) += a1);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801816FC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181900);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181984);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181BE8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181D30);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181F04);

void func_80181F68(void *a0) {
        *(s16 *)((s32)a0 + 0x34) = 0;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181F70);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181FA8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80181FE8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018203C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182098);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801820E4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801821C8);

extern void func_801862F0(void * arg0);
    void func_80182284(s32 arg0) {
        s32 temp_s0 = arg0;
        ((void (*)(void))func_801862F0)();
        *(s16 *)(temp_s0 + 0x34) = 0x8;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801822B4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801822EC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801824D0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182740);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801827A8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182810);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801828D8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182918);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182998);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182A8C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182D80);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182DCC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182E04);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182E78);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182EB0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182F78);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80182FAC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018300C);

void func_80183060(void *a0) {
        *(short *)((char *)a0 + 0x34) = 0x3;
        *(int *)((char *)a0 + 0x1c) = 0x20;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183074);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801830F4);

void func_80183160(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x8;
        *(s16 *)((char *)a0 + 0x34) = 0x6;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183174);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801831A4);

void func_80183200(void *a0) {
        *(s8 *)((s32)a0 + 0xc1) = 0;
        *(s16 *)((s32)a0 + 0x5e) = 0;
        *(u16 *)((s32)a0 + 0x5c) &= 0xfffe;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183218);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801834C8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183524);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183584);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183610);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801838A8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183B0C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183C7C);


extern void (*D_80196320[])(void);

void func_80183D18(void *a0) {
    D_80196320[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183D54);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183D90);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80183FCC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801840E8);

void func_8018415C(void *a0) {
        s32 v0;
        if (*(s16 *)((s32)a0 + 0xe) == 0) {
            *(s16 *)((s32)a0 + 0xae) = -1;
            v0 = *(u16 *)((s32)a0 + 0xfc);
            *(u16 *)((s32)a0 + 0xfc) = v0 | 2;
        }
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184184);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801841E0);


extern void (*D_801963E8[])(void);

void func_8018431C(void *a0) {
    D_801963E8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184358);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184404);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184480);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801844D4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018454C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801846CC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184828);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801849E4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184A34);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184A8C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184C20);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184CA4);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80184D24(void *arg0) {
        ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 0x7);
    }



extern void (*D_80196470[])(void);

void func_80184D44(void *a0) {
    D_80196470[*(u16 *)((s32)a0 + 0x2)]();
}



void func_80184D80(void *a0) {
        *(s8 *)((s32)a0 + 0xc1) = 0;
        *(s16 *)((s32)a0 + 0x5e) = 0;
        *(u16 *)((s32)a0 + 0x5c) &= 0xfffe;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184D98);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184E30);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80184EC0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185060);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801851E0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185214);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801853CC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801853EC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018548C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018550C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801856E4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185764);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185858);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801858C4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018592C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185A04);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185A88);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185B38);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185D6C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185D84);

#include "common.h"

void func_80185DD0(s32 target, u16 *cur, s32 step)
{
    s32 t;
    s32 diff;
    s32 mag;

    t = (target - *cur) & 0xFFF;
    if (t < 0x800) {
        diff = t;
    } else {
        diff = t | 0xF000;
    }
    mag = diff;
    if ((s16)diff < 0) {
        mag = -diff;
    }
    __asm__ __volatile__("" : "=r"(diff) : "0"(diff) : "memory");
    if ((s16)mag > (u16)step) {
        if ((s16)diff < 0) {
            *cur = *cur - step;
        } else {
            *cur = *cur + step;
        }
    } else {
        *cur = target;
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185E54);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80185E80);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801860F4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186144);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186178);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018622C);

void func_801862E0(s32 *a0) {
        s32 v0 = *(s32 *)((s32)a0 + 0xCC);
        *(s16 *)((s32)a0 + 0x98) = 0;
        *(s16 *)(v0 + 0x98) = 0;
    }


void func_801862F0(void * arg0) {
        *(short *)((char *)arg0 + 0x98) = 1;
        *(short *)(*(int *)((char *)arg0 + 0xcc) + 0x98) = 1;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186304);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186424);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018655C);

extern s32 func_8012D714(s32 param_1, u32 param_2);
    extern u16 D_80126B96;
    void func_801865D0(void *arg0) {
        if (func_8012D714((s32)arg0, 0x5)) {
            D_80126B96 = 0x4005;
        }
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186600);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018675C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018687C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018692C);

















extern s32 D_80196208;
void func_801869E0(s32 *param_1)
{
  s32 *new_var;
  new_var = (s32 *) (((char *) param_1) + 0x20);
  *((s32 *) ((*new_var) + 0x80)) = (s32) (&D_80196208);
  new_var = (s32 *) ((*((s32 *) ((*((s32 *) (((char *) param_1) + 0xcc))) + 0x20))) + 0x80);
  *new_var = *((s32 *) ((*((s32 *) (((char *) param_1) + 0xcc))) + 0x20));
  param_1++;
  param_1--;
  *((s32 *) ((*new_var) + 0x80)) = (s32) (&D_80196208);
}

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186A04);

extern s32 D_801961B8;
    extern s32 D_801961E0;
    void func_80186ADC(s32 arg0) {
        *(s32 *)(*(s32 *)(arg0 + 0x20) + 0x80) = &D_801961B8;
        *(s32 *)(*(s32 *)(*(s32 *)(arg0 + 0xcc) + 0x20) + 0x80) = &D_801961E0;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186B08);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186BB8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186C0C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186C70);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186CA8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186D00);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186D74);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186DE8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186F14);

void func_80186F58(void *a0) {
        *(s16 *)((s32)a0 + 0xFC) = 0;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186F60);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80186F9C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187070);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801870BC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801871E4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187280);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187348);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801873FC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187508);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187560);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187664);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801876B0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187768);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801877FC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801878C0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018791C);

extern void func_80181900(void *a0);
    void func_801879DC(void *a0) {
        *(s32 *)((s32)a0 + 0xE8) |= 1;
        *(s16 *)((s32)a0 + 0xE0) = -1;
        ((void (*)(void *))func_80181900)(a0);
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187A0C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187A38);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187A8C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187AD0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187B0C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187B48);

extern s32 func_80185D84(s32 a0);
extern s32 func_80181F70(void *a0);
void func_80187B7C(int param_1)
{
    if (((int (*)(void))func_80185D84)() != 0) {
        ((void (*)(int))func_80181F70)(param_1);
    }
}


extern void func_80181FA8(void);
    void func_80187BB4(s32 arg0) {
        if (*(s16 *)((char *)arg0 + 0x98) == 0) {
            ((void (*)(void))func_80181FA8)();
        }
    }


extern void func_80181FE8(void);
    void func_80187BE4(s32 *a0) {
        if (*(s32 *)((char *)a0 + 0x94) == 0xB) {
            ((void (*)(void))func_80181FE8)();
        }
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187C14);

extern s32 func_8012BEE8(s32 a0);
extern s32 func_80182098(void *a0);
void func_80187C9C(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_80182098)(param_1);
    }
}


extern s32 func_8012CBCC(s32 a0);
extern s32 func_801820E4(void *a0);
void func_80187CD4(int param_1)
{
    if (((int (*)(void))func_8012CBCC)() != 0) {
        ((void (*)(int))func_801820E4)(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187D0C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187D4C);



void func_80187D90(void *a0) {

    extern void (*D_80196250[])(void);
    D_80196250[*(u16 *)((s32)a0 + 0x34)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187DCC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187E18);


extern void func_8012CBF4(s32 a0);
    extern void func_80182E04(void *a0);
    void func_80187F1C(void *a0) {
        if ((((s32 (*)(s32))func_8012CBF4)((s32)a0) & 0x2000) != 0) {
            ((void (*)(s32))func_80182E04)((s32)a0);
        }
    }



extern s32 D_801270C8;
extern void func_80182EB0(void);

void func_80187F58(void) {
    if (D_801270C8 == 22) {
        func_80182EB0();
    }
}


void func_80187F88(void) {
}



extern void func_8012CBF4(s32 a0);
    extern void func_80182EB0(void);
    void func_80187F90(void *a0) {
        if ((((s32 (*)(s32))func_8012CBF4)((s32)a0) & 0x2000) != 0) {
            ((void (*)(s32))func_80182EB0)((s32)a0);
        }
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80187FCC);



void func_8018802C(void *a0) {

    extern void (*D_80196274[])(void);
    D_80196274[*(u16 *)((s32)a0 + 0x34)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188068);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801880AC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018810C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188150);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188194);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801881F4);

extern s32 func_8012BEE8(s32 a0);
extern s32 func_80183174(void *a0);
void func_801882A8(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_80183174)(param_1);
    }
}


void func_801882E0(void) {
}



void func_801882E8(void *a0) {

    extern void (*D_801962A0[])(void);
    D_801962A0[*(u16 *)((s32)a0 + 0x34)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188324);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801883C4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188404);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801884C8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018850C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801885BC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188690);

void func_801886BC(void) {
}

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801886C4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188720);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018874C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801887CC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188830);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801888EC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018893C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188968);


extern void (*D_801964BC[])(void);

void func_801889D4(void *a0) {
    D_801964BC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188A10);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80188A5C(void *arg0) {
        ((void (*)(s32, s32))func_8012AD44)((s32)arg0, 1);
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188A7C);


extern void (*D_801964FC[])(void);

void func_80188BB4(void *a0) {
    D_801964FC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188BF0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188D1C);

extern void func_80188F38(void);
    void func_80188F08(u8 *a0) {
        *(s8 *)(a0 + 0xC1) = 0;
        *(s8 *)(a0 + 0xC2) = 0;
        *(u16 *)(a0 + 0x5C) &= 0xFFFE;
        func_80188F38();
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188F38);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80188FF0);


extern void (*D_801965B0[])(void);

void func_80189204(void *a0) {
    D_801965B0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80189240);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80189268);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801892CC);


extern void (*D_801965C0[])(void);

void func_801894C8(void *a0) {
    D_801965C0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80189504);


extern void (*D_801965D4[])(void);

void func_801895A4(void *a0) {
    D_801965D4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801895E0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018968C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801898F4);


extern void (*D_8019660C[])(void);

void func_80189AF4(void *a0) {
    D_8019660C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80189B30);


extern void (*D_801966A0[])(void);

void func_80189C90(void *a0) {
    D_801966A0[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801966B8[])(void);

void func_80189CCC(void *a0) {
    D_801966B8[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80196760[])(void);

void func_80189D08(void *a0) {
    D_80196760[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801967C4[])(void);

void func_80189D44(void *a0) {
    D_801967C4[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801967CC[])(void);

void func_80189D80(void *a0) {
    D_801967CC[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80196814[])(void);

void func_80189DBC(void *a0) {
    D_80196814[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80196868[])(void);

void func_80189DF8(void *a0) {
    D_80196868[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80189E34);

extern s32 func_80132EF4(s32 a0, s32 a1);
    void func_80189F44(s32 arg0) {
        ((void (*)(s32, s32))func_80132EF4)(arg0, 0x16);
    }


extern u8 *func_8012913C(s32 a0);
    void func_80189F64(void) {
        ((void (*)(s32))func_8012913C)(0x15);
    }


extern s32 func_80132EF4(s32 a0, s32 a1);
    void func_80189F84(s32 arg0) {
        ((void (*)(s32, s32))func_80132EF4)(arg0, 0xC);
    }


extern s32 func_80132EF4(s32 a0, s32 a1);
    void func_80189FA4(void *a0) {
        ((void (*)(void *, int))func_80132EF4)(a0, 0x13);
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80189FC4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018A0E4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018A174);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018A1D8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018A30C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018A3B4);

#include "common.h"

/* 8-byte, alignment-1 blob: the target copies it with lwl/lwr + swl/swr,
 * which is gcc's emit_block_move for align < 4. */
typedef struct {
    char b[8];
} Blob8_8018A47C;

extern Blob8_8018A47C D_801E2F28;
extern void func_8018A6A0(s32 a0, Blob8_8018A47C *a1);

void func_8018A47C(s32 a0) {
    Blob8_8018A47C tmp;

    tmp = D_801E2F28;
    func_8018A6A0(a0, &tmp);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018A4C4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018A658);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018A6A0);

void func_8018A7D0(void) {
}

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018A7D8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018A968);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018AA88);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018AAAC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018AB84);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018ABE0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018AC10);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018AC48);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018ACB4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018AD20);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018AD8C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018ADF0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018AEB4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018AF58);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B058);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B16C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B2DC);

#include "common.h"

extern u8 D_801E44F0[];

s32 func_8018B300(void)
{
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801E44F0;
    do {
        if (*p == 0) {
            *p = v;
            ret = i;
            goto done;
        }
        i++;
        p++;
    } while (i < 8);
    ret = -1;
done:
    return ret;
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B344);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B368);

void func_8018B408(void) {
}

extern void func_80132784(s32 a0, s32 a1, u32 a2);
    void func_8018B410(u8 *a0) {
        ((void (*)(u8 *, u8 *, u16))func_80132784)(a0, *(u8 **)(a0 + 0x64), *(u16 *)(a0 + 0xfe));
    }


void func_8018B438(void) {
}

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B440);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B4D0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B554);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B5E0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B638);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B6A0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B6E8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B7A4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B7F8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B8CC);

extern s32 D_801270C8;
extern void func_801292C8(u8 *a0);

void func_8018B93C(void) {
    if (*(s32 *)&D_801270C8 == 0x13) {
        ((void (*)(void))func_801292C8)();
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018B96C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018BA38);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018BAE4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018BB58);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018BB9C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018BC48);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018BCA4);

extern s32 func_80128DB4(s32 a0, s32 *a1);
    s32 func_8018BCEC(void *a0) {
        ((void (*)(void *, void *))func_80128DB4)(*(void **)((char *)a0 + 0x20), (void *)((char *)a0 + 0x24));
    }


#include "common.h"

extern u8 D_8019681C[];
extern u8 D_80196828[];

extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018BD14(s32 param_1)
{
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_8019681C;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x65;

    func_80128EA8(*(u32 *)(param_1 + 0x20), param_1 + 0x24, (s32)&D_80196828);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern s32 func_80128ED8(void *a0, void *a1);
extern void func_801292C8(u8*);
void func_8018BD90(s32 a0) {
    if (func_80128ED8((void *)*(s32 *)(a0 + 0x20), (void *)(a0 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018BDD0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018BE88);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018BF88(u8 *a0) {
        *(s32 *)(a0 + 0x1c) = 0x20;
        *(s16 *)(a0 + 0x102) |= 2;
        ((void (*)(void *, s32))func_8012AD44)(a0, 0x3);
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018BFBC);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018BFDC(u8 *a0) {
        *(u16 *)(a0 + 0x102) |= 0x1;
        ((void (*)(void *, s32))func_8012AD44)(a0, 0x5);
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C008);


extern void (*D_801968F4[])(void);

void func_8018C08C(void *a0) {
    D_801968F4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C0C8);


extern void (*D_80196B80[])(void);

void func_8018C108(void *a0) {
    D_80196B80[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C144);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C1C0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C204);


extern void (*D_80196B8C[])(void);

void func_8018C274(void *a0) {
    D_80196B8C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

// @stuck: none — MATCH (42 ins), iteration 1, rtu_match clean.
// Saturating add of a 3-byte RGB triple by a signed delta.
// Idioms: (1) `s8` by-value param => entry `sll/sra 24` for the sign test only;
//   combine folds the extension back out of `~a1`/`-a1`/`a0[i]+a1` because every
//   consumer is 8-bit (andi 0xFF / sb), so $a1 is used RAW after the test.
// (2) branch sense read off the target `sltu` operand ORDER (§3-T4): positive arm
//   `sltu lim,p[i]` => store when `p[i] <= lim`; negative arm `sltu p[i],lim`
//   => store when `p[i] >= lim`.
// (3) the third `if` written out in BOTH arms; jump.c cross-jumps the identical
//   tails into the shared `j .L8018C344` (§5a) — do not hoist it after the if/else.
void func_8018C2B0(u8 *a0, s8 a1) {
    u8 lim;

    if (a1 == 0) {
        return;
    }
    if (a1 > 0) {
        lim = ~a1;
        if (a0[0] <= lim) {
            a0[0] = a0[0] + a1;
        }
        if (a0[1] <= lim) {
            a0[1] = a0[1] + a1;
        }
        if (a0[2] <= lim) {
            a0[2] = a0[2] + a1;
        }
    } else {
        lim = -a1;
        if (a0[0] >= lim) {
            a0[0] = a0[0] + a1;
        }
        if (a0[1] >= lim) {
            a0[1] = a0[1] + a1;
        }
        if (a0[2] >= lim) {
            a0[2] = a0[2] + a1;
        }
    }
}



extern void (*D_80196B98[])(void);

void func_8018C358(void *a0) {
    D_80196B98[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C394);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_8018C3C4(void * arg0) {
        *(s8 *)((char *)arg0 + 0xfc) = 0x8;
        ((void (*)(s32, s32))func_8012AD44)((int)arg0, 0x2);
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C3EC);


extern void (*D_80196BA0[])(void);

void func_8018C418(void *a0) {
    D_80196BA0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C454);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C598);


extern void (*D_80196BB0[])(void);

void func_8018C66C(void *a0) {
    D_80196BB0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C6A8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C758);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C84C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C928);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018C978);

extern void func_8012C218(void *a0);
    void func_8018CA1C(void) {
        ((s32 (*)(void))func_8012C218)();
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018CA3C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018CA74);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018CB70);

extern void func_8012C218(void *a0);
    void func_8018CBF8(s32 *a0) {
        if (*(s16 *)((char *)a0 + 0x98) == 0) {
            ((void (*)(void))func_8012C218)();
        }
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018CC28);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018CCF8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018CD80);

#include "common.h"

/* ---- externs ------------------------------------------------------------ */
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *a0, unsigned short a1);

extern u8 D_801E4918;
extern u8 D_801E491C;
extern u8 D_801E2F60;
extern u8 D_801E2F64;

/* align-1 4-byte block: lowers via emit_block_move (unaligned lwl/lwr + swl/swr)
 * with ZERO memcpy-symbol reference, so the TU's `extern memcpy` cannot turn
 * this into a CALL.  (house idiom, cf. func_8017B238 / func_8017B614) */
typedef struct { u8 b[4]; } Blk4_8018CE04;

void func_8018CE04(s32 param_1)
{
    func_8001CD50(*(s32 *)(param_1 + 0x20), (s32)&D_801E4918);

    *(u16 *)(param_1 + 0xA) -= 0x100;
    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0x400;
    *(s16 *)(param_1 + 0x2C) = 0x10;

    func_800233CC(&D_801E4918, 0x10);

    *(Blk4_8018CE04 *)&D_801E4918 = *(Blk4_8018CE04 *)&D_801E2F60;
    *(Blk4_8018CE04 *)&D_801E491C = *(Blk4_8018CE04 *)&D_801E2F64;

    *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1E) = 0xC00;
    *(u16 *)(param_1 + 2) += 1;
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018CEE0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018CF58);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D04C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D144);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D21C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D270);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D318);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D43C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D488);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D4D8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D574);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D608);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D6B0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D73C);

void func_8018D7DC(void *a0) {
        *(s16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D7F0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D8A8);

void func_8018D904(void *a0) {
        *(s16 *)((s32)a0 + 0x2) += 1;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D918);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D964);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018D9A4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018DA40);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018DA8C);

void func_8018DAD8(void) {
}


extern void (*D_80196C9C[])(void);

void func_8018DAE0(void *a0) {
    D_80196C9C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_80196C14;

void func_8018DB1C(s32 arg0) {
    *(s32 *)(arg0 + 0x58) = &D_80196C14;
    *(s32 *)(arg0 + 0x1C) = 0x18;
    *(s16 *)(arg0 + 0x2) += 1;
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018DB40);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018DCD8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018DDFC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018DE5C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018DEB8);


extern void (*D_80196CB0[])(void);

void func_8018DF88(void *a0) {
    D_80196CB0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018DFC4);

void func_8018E22C(void) {
}

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018E234);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018E288);


extern void (*D_80196CC0[])(void);

void func_8018E400(void *a0) {
    D_80196CC0[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018E43C(void *a0) {
        *(s16 *)((s32)a0 + 0x2) += 1;
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018E450);

void func_8018E6D4(void) {
}

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018E6DC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018E730);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018E7E4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018EA04);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018EB60);


extern void (*D_80196CD4[])(void);

void func_8018ECB8(void *a0) {
    D_80196CD4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_800D387C[];

void func_8018ECF4(s32 arg0) {
    s32 iVar1;

    iVar1 = *(s32 *)(arg0 + 0x20);
    ((void (*)(s32, s32, s32, s32))func_8001CC3C)(iVar1, (s32)&D_800D387C, 0x270, 0x120);
    *(u8 *)(iVar1 + 0x27) = 0x9C;
    *(u16 *)(iVar1 + 0x1A) = 0x7000;
    *(u16 *)(iVar1 + 0x18) = 0x7000;
    *(u8 *)(iVar1 + 0x26) = 0x90;
    *(u8 *)(iVar1 + 0x25) = 0x90;
    *(u8 *)(iVar1 + 0x24) = 0x90;
    *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
    *(s16 *)(arg0 + 0x2C) = 0x46;
    *(s16 *)(arg0 + 0x2) += 1;
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018ED84);


extern void (*D_80196CDC[])(void);

void func_8018EDF8(void *a0) {
    D_80196CDC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018EE34);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018EF20);

extern void func_8012C218(void *a0);
    void func_8018EF90(void) {
        ((void (*)(void))func_8012C218)();
    }



extern void (*D_80196CE8[])(void);

void func_8018EFB0(void *a0) {
    D_80196CE8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018EFEC);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018F164);

extern void func_8012C218(void *a0);
    void func_8018F1D4(void) {
        ((s32 (*)(void))func_8012C218)();
    }



extern void (*D_80196CF4[])(void);

void func_8018F1F4(void *a0) {
    D_80196CF4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018F230);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018F2C4);

extern void func_8013C414(void *a0, void *a1);
extern s32 D_8019AA5C;
extern s32 D_801D91D4;

void func_8018F414(void) {
    func_8013C414(&D_8019AA5C, &D_801D91D4);
}


extern void func_8013C414(void *a0, void *a1);
    extern s32 D_8019AA5C;
    extern s32 D_801DA5FC;
    void func_8018F444(void) {
        func_8013C414(&D_8019AA5C, &D_801DA5FC);
    }


extern void func_8013C414(void *a0, void *a1);
    extern s32 D_8019AA5C;
    extern s32 D_801DB658;
    void func_8018F474(void) {
        func_8013C414(&D_8019AA5C, &D_801DB658);
    }


extern void func_8013C414(void *a0, void *a1);
extern s32 D_8019AA5C;

void func_8018F4A4(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801DC180;
    func_8013C414(&D_8019AA5C, &D_801DC180);
}


extern void func_8013C414(void *a0, void *a1);
extern s32 D_8019AA5C;
extern s32 D_801DCD04;

void func_8018F4D4(void) {
    func_8013C414(&D_8019AA5C, &D_801DCD04);
}


extern void func_8013C414(void *a0, void *a1);
extern s32 D_8019AA5C;
extern s32 D_801DD2D4;

void func_8018F504(void) {
    func_8013C414(&D_8019AA5C, &D_801DD2D4);
}


extern void func_8013C414(void *a0, void *a1);
    extern s32 D_8019AA5C;
    extern s32 D_801DDD30;
    void func_8018F534(void) {
        func_8013C414(&D_8019AA5C, &D_801DDD30);
    }



extern void func_8013C414(void *a0, void *a1);
extern s32 D_8019AA5C;

void func_8018F564(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801DE674;
    func_8013C414(&D_8019AA5C, &D_801DE674);
}


extern void func_8013C414(void *a0, void *a1);
    extern s32 D_8019AA5C;
    extern s32 D_801DF3B4;
    void func_8018F594(void) {
        func_8013C414(&D_8019AA5C, &D_801DF3B4);
    }


extern void func_8013C360(void *a0);
    extern s32 D_801D91D4;
    void func_8018F5C4(void) {
        func_8013C360(&D_801D91D4);
    }


extern void func_8013C360(void *a0);
    extern s32 D_801DA5FC;
    void func_8018F5EC(void) {
        func_8013C360(&D_801DA5FC);
    }


extern void func_8013C360(void *a0);
    extern s32 D_801DB658;
    void func_8018F614(void) {
        func_8013C360(&D_801DB658);
    }


extern void func_8013C360(void*);
void func_8018F63C(void) {

    extern s32 D_801DC180;
    ((s32 (*)(s32 *))func_8013C360)(&D_801DC180);
}


extern void func_8013C360(void *a0);
    extern s32 D_801DCD04;
    void func_8018F664(void) {
        func_8013C360(&D_801DCD04);
    }


extern void func_8013C360(void *a0);
    extern s32 D_801DD2D4;
    void func_8018F68C(void) {
        func_8013C360(&D_801DD2D4);
    }


extern void func_8013C360(void *);
    extern s32 D_801DDD30;
    void func_8018F6B4(void) {
        func_8013C360(&D_801DDD30);
    }


extern void func_8013C360(void*);
void func_8018F6DC(void) {

    extern s32 D_801DE674;
    ((s32 (*)(s32 *))func_8013C360)(&D_801DE674);
}


extern void func_8013C360(void*);
void func_8018F704(void) {

    extern s32 D_801DF3B4;
    ((s32 (*)(s32 *))func_8013C360)(&D_801DF3B4);
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018F72C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018F894);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018F91C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018F944);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018FA34);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018FAE0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018FB8C);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018FC38);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018FCE4);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018FE18);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018FEA0);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8018FFC4);

void func_80190068(s32 *a0) {
        *(s16 *)((s32)a0 + 0x2) = 0xC;
    }



extern void (*D_80196CFC[])(void);

void func_80190074(void *a0) {
    D_80196CFC[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801900B0);


extern s32 D_801E4C40;

void func_801900E0(void) {
    D_801E4C40 = 1280;
}



extern s32 D_801E4C40;

void func_801900F4(void) {
    D_801E4C40 = 3796;
}



extern void (*D_80196EA4[])(void);

void func_80190108(void *a0) {
    D_80196EA4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80190144);

extern void func_80190384(void);
    void func_80190344(void) {
        func_80190384();
    }


extern void func_80146C3C(void);
    void func_80190364(void) {
        func_80146C3C();
    }


#include "common.h"

extern void func_80017254(void *a0);
extern void func_800176F0(void *a0);
extern u8 D_80196DAC[];
extern u8 D_80196DD4[];

void func_80190384(void) {
    u8 *p;
    s32 i;

    func_80017254(D_80196DAC);
    i = 0;
    p = D_80196DD4;
    do {
        func_800176F0(p);
        i++;
        p += 0x34;
    } while (i < 4);
}


extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
    void func_801903DC(void *arg0) {
        ((void (*)(s32, s32, s32, s32))func_80146994)(0x28, 0, arg0, 0);
    }


#include "common.h"

extern s32 D_80126B58;
extern s32 func_8014C050(s32 a0, s32 a1);

void func_80190408(void) {
    s32 t;

    t = func_8014C050((s32)&D_80126B58, 0x28);
    if (t != 0) {
        *(u16 *)(t + 2) += 1;
    }
}



extern void (*D_80196F00[])(void);

void func_8019044C(void *a0) {
    D_80196F00[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_801904B8(s32 arg);
    extern void func_80146CA0(void *a0);
    void func_80190488(s32 arg0) {
        func_801904B8(arg0);
        ((void (*)(s32))func_80146CA0)(arg0);
    }


INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_801904B8);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_80190538);

INCLUDE_ASM("asm/ov_SC02_005/nonmatchings/ov_SC02_005_jr_8017AE2C", func_8019084C);




