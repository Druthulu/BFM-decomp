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
      /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
         /* 16-byte stride array element */
extern void func_801458E0(void);
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80189D48;
extern u8 D_80189CB8;
extern u8 D_80189C94;
extern u8 D_80189C70;
extern u8 D_80189D24;
extern u8 D_80189D00;
extern u8 D_80189CDC;
extern u8 D_80189C4C;
extern void func_80145934(void);
extern u8 D_80189DD8;
extern u8 D_80189DB4;
extern u8 D_80189D90;
extern u8 D_80189D6C;
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
extern unsigned char D_801891D0[];
extern unsigned char D_80189200[];
extern unsigned char D_80189250[];
extern unsigned char D_80189280[];
extern unsigned char D_801892B0[];
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
extern void (*D_80189300[])(void *);
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
extern s32 D_801893C8[];
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
extern u8 D_80189450[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80189458;
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
extern int D_801D8318;
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
extern s32 D_801D831C;
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
extern s32 D_80189488;
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
extern void (*D_80189530[])(void);
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
extern void (*D_80189554[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80189544;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80189568[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80189574[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80189584[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018959C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018958C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801895B0[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801895CC[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801895BC;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801895E0[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801895F4[])(void);
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
extern s32 D_80189608;
extern void (*D_80189630[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80189610;
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
extern int (*D_8018967C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80189680[])(void);
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
extern unsigned short D_80189AE4[];
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
extern void (*D_80189AF4[])(void);
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
extern int D_801D8350;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80189B1C[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80189AFC;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80189B0C;
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
extern void (*D_80189B5C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80189B64[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80189B30;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80189B70[])(void);
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
extern u8 D_80189B40;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801D8358;
extern s32 D_801D8364;
extern s32 D_801D8368;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80189BAC[])(s32 *);
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
extern s32 D_80189B80[];
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
extern s32 D_801D8360;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80189DFC[])(void);
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
extern char D_80189C1C[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80189EA0[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80189FF4[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80189E10;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80189FFC[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80189E20;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80189E40;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018A004[])(void);
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
extern void (*D_8018A02C[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018A038[])(void);
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
extern void (*D_80189EAC[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018A0DC;
extern void func_8015D380(s32 a0);
extern unsigned char D_801891C0[];
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
extern unsigned char D_8018A0F0[];
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
extern s8 D_8018A12C[];
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
extern u16 D_8018A174;
extern u16 D_8018A176;
extern u16 D_8018A178;
extern s32 D_8018A17C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018A184;
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
extern int D_80189E90;
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
extern unsigned int D_8018A208[];
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
extern void (*D_8018A2B8[])(void);
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
extern u16 D_8018A2E8[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018A34C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801D8370[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018A370[])(void);
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
extern int D_801D83C8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018A3B8[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018A3A8;
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
extern char D_801D7AD8[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018A3C0[])(void);
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
extern void (*D_8018A414[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018A3DC;
extern s16 D_8018A410;
extern s16 D_8018A40E;
extern s16 D_8018A40C;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018A420[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801D8428;
extern u8 D_801D8429;
extern u8 D_801D842A;
extern u8 D_801D842B;
extern u8 D_801D842C;
extern u8 D_801D842D;
extern u8 D_801D842E;
extern u8 D_801D842F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018A430[])(void);
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
extern s32 D_801D8468;
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
extern void (*D_8018A474[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018A4F0[];
extern s32 D_8018A510[];
extern u8 D_8018A58C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018A5AC[];
extern u8 D_8018A5CC[];
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
extern void (*D_8018A668[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018A6E4[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801D7AE8;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018A6F0[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018A6F8[])(void);
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
extern void (*D_8018A7C0[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018A7D0[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018A7E0[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018A7EC[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018A74C[];
extern u8   D_8018A760[];
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
extern void (*D_8018A804[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018A80C[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018A814[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018A81C[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018A824[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018A82C[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018A834[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018A8E8[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018A8F0[])(void);
extern void func_80169F00(void *a0);
extern char D_8018A8A0[];
extern char D_8018A860[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018A928[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018A934[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018A97C[])(void);
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
extern void (*D_8018A9F8[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801D8788;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018A9EC[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018AA30[];
extern unsigned short D_8018AA38[];
extern unsigned short D_8018AA40[];
extern unsigned char D_801D8790[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801D8788;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018AA48[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801D88C4;
extern M2C_UNK D_801D88C8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801D8850;
extern void (*D_8018AA78[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801D88CC[];
extern u8 D_801D88D4[];
extern u8 D_801D8884[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018AA80[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018AA9C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018AAA4[])(void);
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
extern void (*D_8018AB0C[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018AAB0;
extern u8 D_8018AABC;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018AB40[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018AB48[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018AB9C[])(void);
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
extern u16 D_8018ABD0[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018ABC0[];
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
extern s32 D_8018ABEC;
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
extern void (*D_8018AC64[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018AC6C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018AC74[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018AC7C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018AC84[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018AC8C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018AC98[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018ACA4[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018ACB0[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018ACC0[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018ACD0[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018ACD8[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018ACE0[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018ACE8[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018ACF0[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018ACF8[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018AD00[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018AD08[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018AD10[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018AD18[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018AD20[])(void);
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
extern void (*D_8018AD28[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018AD30[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018AD38[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018AD40[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018AD48[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018AD50[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018AD58[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018AD60[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018AD68[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018AD70[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018AD78[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018AD80[])(void);
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
extern void (*D_8018ADC4[])(void);
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
extern M2C_UNK D_8018AD88;
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
extern void (*D_8018ADF4[])(void);
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
extern void (*D_8018AE30[])(void);
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
extern void (*D_8018AE88[])();
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
extern void (*D_8018AE98[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018AEA0[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018B008[])();
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
extern void (*D_8018B014[])();
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
extern M2C_UNK D_801D7D30;
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
extern s16 D_801D99D0;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801D9008;
extern short D_801D9A44;
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
extern s32 D_801D9434;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801D945C;
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
extern s16 D_801D9418;
extern s32 func_8017A3B0(void);
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
extern s16 D_801D941C;
extern u16 D_801D949C;
extern u16 D_801D949E;
extern u16 D_801D94A0;
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
extern s16 D_801D9494;
extern s16 D_801D9496;
extern s16 D_801D9498;
extern s16 D_801D948C;
extern s16 D_801D948E;
extern s16 D_801D9490;
extern void func_8017B7A8(void);
extern s16 D_801D94AC;
extern s16 D_801D94AE;
extern s16 D_801D94B0;
extern s16 D_801D94B4;
extern s16 D_801D94B6;
extern s16 D_801D94B8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801D94A4;
extern short D_801D94A6;
extern short D_801D94A8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801D943C;
extern SV4 D_801D9444;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801D9464[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801D9460)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018B1F0[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8018B214[])(void);
extern void func_8017BEBC(void *a0);
extern void func_8017C0BC(u8 *p);
extern void (*D_8018B21C[])(void);
extern void func_8017C150(void *a0);
extern s32 func_800D222C(s32 a0, void *a1, s32 a2);
extern s32 func_8001CF30(void *a0);
extern u8 D_8018B208;
extern void func_8017C18C(s32 a0);
extern void func_8017C230(int a0);
extern void (*D_8018B334[])(void);
extern void func_8017CC90(void *a0);
extern void (*D_8018B38C[])(void);
extern void func_8017D0E8(void *a0);
extern void (*D_8018B3A0[])(void);
extern void func_8017D714(void *a0);
extern void (*D_8018B3B4[])(void);
extern void func_8017D9B4(void *a0);
/* ==== end §8b carried decl layer ==== */

/* func_8017DC70 — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
 * Outer loop: per-part bbox -> RTPT/RTPS projection -> g.otz + screen cull.
 * Inner loop: per-prim RTPT -> g.flag/nclip/g.opz cull -> switch(code&7):
 *   4,5=POLY_F3 / 6,7=POLY_FT3 / 0,1=POLY_F4 / 2,3=POLY_FT4 -> OT insert.
 * GTE ops are verbatim PsyQ inline_c.h macro bodies (rtps/rtpt/nclip spelled via
 * the project gas macros from include/gte_macros.inc, pulled in by common.h).*
 * CLOSED 2026-07-13 (Phase 26 session 8, Fable5 Max): match_one MATCH 952/952, PIN-FREE.
 * The close=2 residual (two transposed preheader addius) was a global.c allocno-priority TIE:
 *   pseudo 228 = &g.sz1 (sp+0xD0): refs 13, live_length 783 -> pri int(3*13*10000/783) = 498
 *   pseudo 230 = &g.sz2 (sp+0xD4): refs 13, live_length 782 -> pri int(3*13*10000/782) = 498
 * Tie -> creation-order tie-break -> sz1 allocated first (t8) = swapped. The shipped workaround
 * permuted the stsz3 operand list (creation sz0,sz2,sz1) which fixed allocation but transposed
 * the preheader emission (close=2). TRUE FIX: natural operand order restored (emission correct)
 * + ONE zero-byte `__asm__ volatile ("")` inside the common live range (between two existing GTE
 * volatile asms, so no new cse/sched barrier) -> L 784/783 -> pri 497 vs 498 -> the tie SPLITS
 * toward the shorter-lived allocno (sz2) -> sz2 first -> t8. All 10 grants cascade. The slider
 * emits nothing (#APP/#NO_APP only); the tie can ONLY split toward the target's allocation
 * because the later-defined pseudo always has the shorter range. Cookbook §47.
 */

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

void func_8017DC70(s32 arg0)
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
                                            if (code != 4) g.opz = za + 0x200;
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
                                            if (code == 7) g.opz = za + 0x200;
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
                                                if (code == 3) g.opz = za + 0x200;
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



extern void (*D_8018B568[])(void);

void func_8017EB50(void *a0) {
    D_8018B568[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017F0C8(void);
extern void func_800167B8(s32 a0);

s32 func_8017EB8C(s32 a0) {
    func_8017F0C8();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017EBD0(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_8018B570[])(void);

void func_8017EBF4(void *a0) {
    D_8018B570[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017F0F0(void);
extern void func_800167B8(s32 a0);

s32 func_8017EC30(s32 a0) {
    func_8017F0F0();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void (*D_8018B578[])(void);

void func_8017EC74(void *a0) {
    D_8018B578[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017F118(void);

s32 func_8017ECB0(s32 a0) {
    func_8017F118();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017ECF0(u8 *a0) {
    if (--(*(s32 *)(a0 + 0x28)) == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017ED6C(void) {
        func_800D1EBC();
    }



extern void (*D_8018B584[])(void);

void func_8017ED8C(void *a0) {
    D_8018B584[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017F140(void);

s32 func_8017EDC8(s32 a0) {
    func_8017F140();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017EE08(s32 a0) {
    s32 t = *(s32 *)(a0 + 0x28) - 1;

    *(s32 *)(a0 + 0x28) = t;
    if (t == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
void func_8017EE7C(void) {
    func_800D1EBC();
}



extern void (*D_8018B590[])(void);

void func_8017EE9C(void *a0) {
    D_8018B590[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017EED8(s32 a0) {
    s32 t = *(s32 *)(a0 + 0x28) - 1;

    *(s32 *)(a0 + 0x28) = t;
    if (t == -1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}



extern void (*D_8018B59C[])(void);

void func_8017EF4C(void *a0) {
    D_8018B59C[*(u8 *)((s32)a0 + 0x15)]();
}


s32 func_8017EF88(s32 a0) {
    s32 v = func_80029504();
    s32 t = *(s32 *)(a0 + 0x28) - 1;

    *(s32 *)(a0 + 0x28) = t;
    if (t == -1) {
        if (v < 200 && (u32)(v - 150) < 50) {
            func_800D0C48(1);
        }
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D1E28();
        *(u8 *)(a0 + 0x15) += 1;
    }
    return 0;
}



extern void (*D_8018B5A8[])(void);

void func_8017F024(void *a0) {
    D_8018B5A8[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017F49C(void);
extern void func_800167B8(s32 a0);

s32 func_8017F060(s32 a0) {
    func_8017F49C();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017F0A4(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017F0C8(void) {

    extern s32 D_8018B5B8(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018B5B8, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017F0F0(void) {

    extern s32 D_8018B5C4(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018B5C4, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017F118(void) {

    extern s32 D_8018B5C8(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018B5C8, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017F140(void) {

    extern s32 D_8018B5DC(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018B5DC, 0x1000000);
}



extern void (*D_8018B614[])(void);

void func_8017F168(void *a0) {
    D_8018B614[*(u8 *)((s32)a0 + 0x216)]();
}


extern u8 D_801C8570[];
extern u8 D_801C8610[];
extern s32 func_80171990(u8 *a0);

void func_8017F1A4(u8 *a0) {
    *(u32 *)(a0 + 0xB0) = (u32)D_801C8570;
    *(u32 *)(a0 + 0xCC) = (u32)D_801C8610;
    *(u16 *)(a0 + 0x20C) = 0;
    *(u16 *)(a0 + 0x20E) = 0;
    *(u16 *)(a0 + 0x210) = 0;
    func_80171990(a0);
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8017F1E4);



extern const Blk8 D_801D8018;
extern s32 func_80171CC4(void*, void*);
extern s32 func_80171990(u8 *a0);
extern void func_80172304(s32 *a0);

void func_8017F298(void *arg0) {
    Blk8 buffer;

    buffer = D_801D8018;

    if (((s32 (*)(u32, void *))func_80171CC4)(arg0, &buffer)) {
        func_801818EC();
        ((void (*)(u32))func_80171990)(arg0);
    }
    ((void (*)(void *))func_80172304)(arg0);
}


extern const Blk8 D_801D8020;
extern s32 func_80171CC4(void*, void*);
extern void func_80171928(void*);

void func_8017F310(u32 arg0) {
    Blk8 buffer;

    buffer = D_801D8020;

    if (((s32 (*)(u32, void *))func_80171CC4)(arg0, &buffer)) {
        ((void (*)(u32))func_80171928)(arg0);
    }
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8017F378);


// func_8017F3AC — MATCH (60 ins), match_one + rtu_match. Two levers:
//  1) §20 pointer-var-to-the-global: `u16 *p = &D_800B99DA;` and read `*p`
//     twice. The bare global would fold %lo into each access independently
//     (two lui/lhu pairs, no $s1); the pointer var force_regs the address so
//     CSE hoists it into the callee-saved $s1 across both calls.
//  2) SEPARATE temps `t` and `u` for the two call results (NOT one reused
//     `t`). gcc-2.7.2 expand_divmod emits `move temp,op0; bgez temp; temp+=d-1`
//     for a signed /2^k; cse.c make_regs_eqv only makes `temp` the canonical
//     reg of the quantity when temp's REGNO_LAST_UID outlives op0's. Reusing
//     one `t` across both calls stretches op0's last-use past temp's, so op0
//     stays canonical and cse rewrites the pair to `bgez $v0` + `addiu
//     $v1,$v0,3` — the copy then fills the delay slot and the function comes
//     out 1 instruction short. Split temps ⇒ op0 dies immediately ⇒ target's
//     `addu $v1,$v0,$zero; bgez $v1; nop; addiu $v1,$v1,3`.
// (The 2nd division still coalesces temp/u into $v0, matching `bgez $v0`.)

extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8017F3AC(s32 param_1) {

    extern u16 D_800B99DA;
    u16 *p = &D_800B99DA;
    s32 t;
    s32 u;

    *(s16 *)(param_1 + 0x20E) = func_80012F74(*(s16 *)(param_1 + 0x20E), 0, 10, 1);
    *(s16 *)(param_1 + 0x12E) = 1;
    t = func_8004787C((*p & 0x3F) << 6);
    *(s16 *)(param_1 + 0x128) = *(s16 *)(param_1 + 0x20E) + t / 4;
    u = func_80047948((*p & 0x3F) << 6);
    *(s16 *)(param_1 + 0x12C) = u / 8;
    if (*(s16 *)(param_1 + 0x13A) != 0) {
        *(s16 *)(param_1 + 0x13A) += *(s8 *)(param_1 + 0x20D);
        *(s16 *)(param_1 + 0x20C) -= 0xE0;
        if (*(s16 *)(param_1 + 0x13A) < 0) {
            *(s16 *)(param_1 + 0x13A) = 0;
            *(s16 *)(param_1 + 0x20C) = 0;
        }
    }
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017F49C(void) {

    extern s32 D_8018B5EC(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018B5EC, 0x1000000);
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8017F4C4);

extern u8 D_80126948[];
extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017F724(void *a0);
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern s16 D_80126940;
extern s16 D_801274E8;

typedef struct {
    s16 x0, x1, x2, x3;
} UnalignedShortBlock;

void func_8017F590(void) {
    D_80126954 = 0x190;
    D_8012695C = 0x384;
    D_80126968 = 0x38E;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x80;
    D_8012697A = 0;
    func_8012A018((s32)func_8017F724, 1);
    func_8012A094((s32)D_80126948);
    *(UnalignedShortBlock *)&D_801274E8 = *(UnalignedShortBlock *)&D_80126940;
    func_8017F724((void *)D_80126948);
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8017F658);


extern void (*D_8018B624[])(void);

void func_8017F724(void *a0) {
    D_8018B624[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8017F760);

extern void func_8017FA84(s32 a0, s16 *a1, u32 a2);

void func_8017FA2C(s32 a0)
{
    extern s16 D_80126940;
    extern s16 D_80126944;
    s16 *p = &D_80126940;

    func_8017FA84(a0, p, ratan2(*p, D_80126944) & 0xFFF);
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8017FA84);

extern void (*D_8018B754[])(void *);
extern void (*D_8018B768[])(void *);

void func_8017FC50(void *param_1) {
    extern void func_8017FF7C(void);
    extern void func_801800D0();

    if (*(u16 *)((s32)param_1 + 0x5C) & 1) {
        func_8017FF7C();
    }
    func_801800D0(param_1);
    if (*(u16 *)((s32)param_1 + 0x34) == 0) {
        D_8018B754[*(u16 *)((s32)param_1 + 2)](param_1);
    } else {
        D_8018B768[*(u16 *)((s32)param_1 + 0x34)](param_1);
    }
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8017FCE0);

INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8017FD74);

extern s32 func_8012BCCC(s32 a0);
extern void func_8013240C(s32 a0);
extern s32 D_801D9740;

void func_8017FDB4(s32 a0) {
    s32 v0 = func_8012BCCC(a0);
    if (v0 <= 0x11000) {
        *(s16 *)(a0 + 0x2) = 3;
    } else {
        func_8013240C((s32)&D_801D9740);
    }
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8017FE08);

extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern void func_8013240C(s32 a0);

extern s32 D_8018B774;
extern s32 D_801D9740;

void func_8017FE60(s32 a0) {
    s32 v0;
    s32 v1;
    s32 base;
    s32 tbl;
    s32 tbl2;
    s32 i;

    if (*(s16 *)(a0 + 0xAA) == 0) {
        if (*(s32 *)(a0 + 0x1C) < 0xB) {
            if (*(s32 *)(a0 + 0xDC) == 0) {
                i = 0;
                base = (s32)&D_8018B774;
                tbl2 = base + 8;
                tbl = base;
                for (; i < 0xC; i += 2) {
                    func_8012D5E4(a0, tbl, tbl2, 0x21);
                    tbl2 += 0x10;
                    tbl += 0x10;
                }
                *(s32 *)(a0 + 0xDC) ^= 1;
            }
        }
    }
    if (*(s32 *)(a0 + 0x1C) == 0xC) {
        func_8002D4C8(0xAD3, 0);
    }
    if (func_8012BEE8(a0) != 0) {
        v1 = func_8012BCCC(a0);
        if (v1 < 0x7001) {
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s32 *)(a0 + 0xDC) = 0;
        } else {
            *(s16 *)(a0 + 2) = 1;
            return;
        }
    }
    func_8013240C((s32)&D_801D9740);
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8017FF7C);


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80180088);

void func_801800D0(s32 a0)
{
    extern u16 D_801D9750[];
    extern u16 D_801D9754;

    if ((*(s16 *)(a0 + 0xAA) != 0) && ((u32)(*(s16 *)(a0 + 0xAA) - 0x10) < 0xE1))
    {
        if (*(s16 *)(a0 + 0xFC) == 0)
        {
            D_801D9750[0] = (s16)*(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) >> 1;
            D_801D9750[1] = (s16)*(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) >> 1;
            D_801D9754 = (s16)*(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) >> 1;
            *(s16 *)(a0 + 0xFC) = 1;
        }
        else
        {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = D_801D9750[0];
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = D_801D9750[1];
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = D_801D9754;
        }
    }
}


extern s32 func_8012BEE8(s32 a0);
extern void func_8002AC00(s32 a0);
extern void func_8002A04C();
extern void func_80180250(void *a0);

void func_801801AC(s32 a0) {
    if (*(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) < 0x1000) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) += 0x400;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) += 0x400;
    }
    if (func_8012BEE8(a0)) {
        func_8002AC00(9);
        func_8002A04C(a0);
        func_80180250((void *)a0);
    }
}


void func_80180234(void *a0) {
        s32 v1 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)((s32)a0 + 0x2) = 1;
        *(s16 *)((s32)a0 + 0x34) = 0;
        *(s16 *)(v1 + 0x10) = 0;
        *(s16 *)((s32)a0 + 0x5E) = 0;
    }


void func_80180250(void *arg0) {
    s32 *ptr;

    if ((*(s16 *)((s32)arg0 + 0x70) & 0x8000) == 0) {
        ptr = *(s32 **)((s32)arg0 + 0x68);
        if (ptr != NULL) {
            if ((*(s16 *)((s32)arg0 + 0x72) & 0x8000) != 0) {
                *(u16 *)((s32)ptr + 0xA) &= 0x7FFF;
            }
        }
    }

    func_8012C218(arg0);
    func_80029124(0x9D, 1);
}


void func_801802C4(s32 arg0) {
    extern u8 D_8018B8EC;
    s32 e;

    func_8002D4C8(0x526, 0);
    e = *(u8 *)((s32)arg0 + 0x5E);
    if (*(s16 *)((s32)arg0 + 0x60) != 0) {
        if (e == 0x1D) {
            *(s16 *)((s32)arg0 + 0x82) = 0;
            *(s16 *)((s32)arg0 + 0x7C) = *(u16 *)((s32)arg0 + 0x06);
            *(s16 *)((s32)arg0 + 0x7E) = *(u16 *)((s32)arg0 + 0x0A);
            *(s16 *)((s32)arg0 + 0x80) = *(u16 *)((s32)arg0 + 0x0E);
        }
        func_8016AA50(arg0, *(s16 *)((s32)arg0 + 0x60));
        if (*(u16 *)((s32)arg0 + 0x82) & 1) {
            func_8016B428(arg0);
            func_80019064((void *)&D_8018B8EC);
        }
    }
    *(u16 *)((s32)arg0 + 0x5C) = *(u16 *)((s32)arg0 + 0x5C) & 0xFFFE;
    {
        s32 r = *(s32 *)((s32)arg0 + 0x20);
        *(s16 *)(r + 0x12) = (*(u16 *)((s32)arg0 + 0x62) + 0x800) & 0xFFF;
    }
    {
        s32 r2 = *(s32 *)((s32)arg0 + 0x20);
        *(s16 *)(r2 + 0x14) = 0;
        *(s16 *)(r2 + 0x10) = 0;
    }
    func_8012B2CC(arg0);
    func_8012B23C(arg0);
    *(u8 *)((s32)arg0 + 0xC2) = 1;
    *(s16 *)((s32)arg0 + 0x98) = 0;
    *(s32 *)((s32)arg0 + 0x1C) = 0x10;
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_801803B0);

INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80180410);

INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80180444);

INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_801804A0);

void func_80180904(s32 arg0) {
    register s32 base __asm__("$2");
    register s32 cst __asm__("$3");
    register s32 b2 __asm__("$3");
    register s32 c2 __asm__("$2");
    register s32 r6 __asm__("$2");
    register s32 rA __asm__("$3");
    register s32 rE __asm__("$6");

    base = *(s32 *)(arg0 + 0x20);
    cst = 0x1800;
    *(s16 *)(arg0 + 0xAA) = 0;
    *(s16 *)(arg0 + 0x5C) = 0;
    *(s16 *)(base + 0x18) = cst;
    base = *(s32 *)(arg0 + 0x20);
    *(s16 *)(base + 0x1C) = cst;
    b2 = *(s32 *)(arg0 + 0x20);
    c2 = 0x100;
    *(s16 *)(b2 + 0x1A) = c2;
    b2 = *(s32 *)(arg0 + 0x20);
    *(u16 *)(b2 + 0x2C) |= 0x10;
    *(s16 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x1C) = 0x1E;
    *(s16 *)(arg0 + 0x98) = 0;
    func_8002D4C8(0x526, 0);
    r6 = *(u16 *)(arg0 + 0x6);
    rA = *(u16 *)(arg0 + 0xA);
    rE = *(u16 *)(arg0 + 0xE);
    *(s16 *)(arg0 + 0x7C) = r6;
    *(s16 *)(arg0 + 0x7E) = rA;
    *(s16 *)(arg0 + 0x80) = rE;
    func_8016AA50(arg0, 0xA);
}


#include "common.h"

extern void func_8012B23C(s32 a0);
extern s32 func_8012CBCC(s32 a0);

void func_801809A4(s32 a0)
{
    switch (*(u16 *)(a0 + 0x34)) {
    case 0: {
        s32 v0 = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = v0;
        if (v0 == 0) {
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    }
    case 1: {
        s32 v0 = *(s32 *)(a0 + 0x1C) - 1;
        *(s32 *)(a0 + 0x1C) = v0;
        if ((v0 & 2) != 0) {
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x1600;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x1600;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x400;
        } else {
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x1800;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x1800;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x100;
        }
        if (*(s32 *)(a0 + 0x1C) == 0) {
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) &= 0xFFEF;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x1000;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x1000;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x1000;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 0x40;
            func_8012B23C(a0);
        }
        break;
    }
    case 2:
        if (func_8012CBCC(a0) != 0) {
            *(s16 *)(a0 + 0x98) = 1;
            *(u8 *)(a0 + 0xC1) = 0;
            *(s32 *)(a0 + 0x1C) = 1;
            *(u16 *)(a0 + 0x5C) = 0x8A10;
            if (*(s16 *)(a0 + 0x76) < 0x320) {
                *(s16 *)(a0 + 0x76) = 0x384;
            }
        }
        break;
    }
}


void func_80180B44(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x20);

    *(s32 *)(v1 + 0x4) = *(s32 *)(v1 + 0x4) & 0x7FFFFFFF;
    *(u16 *)((s32)a0 + 0xFC) = 0;
    func_800291C8(0xA, 0x3065);
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80180B84);

void func_80180D3C(s32 arg0) {
    extern void func_8012A828(s32, void*);
    extern s32 func_8012B6D4(s16 *a0, s16 *a1);
    extern void func_8012BD14(s32 a0);
    extern s32 func_80178B18(s32 param_1, s32 param_2);
    extern void func_801746DC(void);
    extern s32 func_8012B8A4(s16 *a0);
    extern s32 func_801789AC(s32 arg0);
    extern void func_80178D18(void);
    extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
    extern u8 D_801C02A8[];
    extern u8 D_801C0178[];
    extern s32 D_8018B878;

    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) =
        func_8012B6D4((s16 *)(arg0 + 4), (s16 *)(*(s32 *)(arg0 + 0xCC) + 4));
    func_8012A828((s32)arg0, (void *)D_801C02A8);
    *(u16 *)(arg0 + 0x98) = 0;
    if (--*(s32 *)(arg0 + 0x1C) == 0) {
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x10) ^= 0xFE0;
        *(s32 *)(arg0 + 0x1C) = 2;
    }

    switch (*(s16 *)(arg0 + 0x10A)) {
    case 0:
        break;
    case 1:
        if (((s32 (*)(s32))func_8012BD14)((s32)arg0) < 0x1001) {
            func_80178B18((s32)arg0, (s32)&D_8018B878);
            func_801746DC();
            *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x12) = func_8012B8A4((s16 *)arg0);
            *(s16 *)(arg0 + 0x10A) = 2;
        }
        break;
    case 2:
        if (func_801789AC((s32)arg0) == 1) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            *(s16 *)(arg0 + 0x10A) = 0;
            *(u16 *)(arg0 + 0x5C) |= 0x200;
        }
        if ((*(u16 *)(arg0 + 0x72) & 0x4000) != 0) {
            func_8012A828((s32)arg0, (void *)D_801C0178);
            func_8012E688((s32)arg0, 0x525, 0);
        }
        break;
    default:
        break;
    }
}


extern void (*D_8018B8FC[])(void *);

void func_80180E94(void *a0) {
    s16 count = *(s16 *)((s32)a0 + 0xFC);
    if (count != 0) {
        s32 ptr = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)((s32)a0 + 0xFC) = count - 1;
        *(s32 *)(ptr + 4) = *(s32 *)(ptr + 4) ^ 0x80000000;
    }
    D_8018B8FC[*(u16 *)((s32)a0 + 0x2)](a0);
}



extern void (*D_8018B92C[])(void);

void func_80180F00(void *a0) {
    D_8018B92C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80180F3C);


extern void (*D_8018B934[])(void);

void func_80180FB0(void *a0) {
    D_8018B934[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 rand(void);

void func_80180FEC(s32 a0) {
    extern u8 D_801C0178[];
    extern u8 D_801C01A8[];

    if (*(u16 *)(a0 + 0x72) & 0x4000) {
        switch (rand() & 3) {
        case 0:
            func_8012A828(a0, D_801C0178);
            func_8012E688(a0, 0x525, 0);
            break;
        case 1:
            func_8012A828(a0, D_801C01A8);
            break;
        case 2:
            func_8012A828(a0, D_801C0178);
            break;
        case 3:
            func_8012A828(a0, D_801C01A8);
            break;
        }
    }
}

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012E688(s32 a0, u16 a1, u16 a2);


extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32 func_8012B030(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_8018B8C0;
extern s32 D_801C02A8;

void func_801810BC(void *a0) {
    register void *s0 __asm__("$16");
    register void *s2 __asm__("$18");
    s32 s1;
    s32 v0;

    s0 = a0;
    s2 = (u8 *)s0 + 4;
    s1 = *(s32 *)((u8 *)s0 + 0xCC) + 4;
    v0 = func_8012B6D4((s16 *)s2, (s16 *)s1);
    *(u16 *)(*(s32 *)((u8 *)s0 + 0x20) + 0x12) = v0;
    func_8012B2CC((s32)s0);
    func_8012B1B4((s32)s0, (s32)&D_8018B8C0);
    if (func_8012CBCC((s32)s0) & 0xA000) {
        *(u16 *)((u8 *)s0 + 0x16) -= 2;
    }
    if (func_8012BC60((struct Vec *)s2, (struct Vec *)s1) < 0x900) {
        func_8012B030(s0);
        *(u16 *)((u8 *)s0 + 2) = 3;
        func_8012A828((s32)s0, (void *)&D_801C02A8);
        *(u16 *)((u8 *)s0 + 0x98) = 0;
        *(s32 *)((u8 *)s0 + 0x1C) = 2;
    }
}


#include "common.h"

extern void func_80180F3C(void);
extern s32 func_8012B030(void *a0);
extern void func_800291C8(s32, s32);

extern u16 D_8018B8E4;
extern u16 D_8018B8E6;
extern u16 D_8018B8E8;

void func_8018118C(void *a0) {
    s32 v1 = *(s32 *)((s32)a0 + 0x20);
    u16 v0;

    *(u16 *)(v1 + 0x10) = *(u16 *)(v1 + 0x10) - 0x30;

    v0 = *(u16 *)((s32)a0 + 0xA) + 2;
    v1 = *(s32 *)((s32)a0 + 0x1C) - 1;
    *(s32 *)((s32)a0 + 0x1C) = v1;
    *(u16 *)((s32)a0 + 0xA) = v0;
    v1 &= 7;
    if (v1 == 0) {
        func_80180F3C();
    }

    if (*(s32 *)((s32)a0 + 0x1C) == 0) {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0;
        *(s16 *)((s32)a0 + 0x2) = 3;
        *(s32 *)((s32)a0 + 0x1C) = 2;
        *(u16 *)((s32)a0 + 0xFC) = 0x3C;
        *(u16 *)((s32)a0 + 0x6) = D_8018B8E4;
        *(u16 *)((s32)a0 + 0xA) = D_8018B8E6;
        *(u16 *)((s32)a0 + 0xE) = D_8018B8E8;
        func_8012B030(a0);
        *(u16 *)((s32)a0 + 0x5C) = 0x8A10;
        if (*(s16 *)((s32)a0 + 0x76) < 0x320) {
            *(u16 *)((s32)a0 + 0x76) = 0x384;
        }
        func_800291C8(0xA, 0x3025);
    }
}


void func_8018127C(void) {
}

INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80181284);


extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);

void func_80181338(void *a0)
{

    extern u8 D_801D9760[];
    s32 s1;
    u8 *p;

    s1 = *(s32 *)((s32)a0 + 0x20);
    p = D_801D9760 + *(s32 *)((s32)a0 + 0x2C) * 0x40;
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
 *  - D_801D9760: the TU already declares it at line 4526 as `extern u8 D_801D9760[];`
 *    (used by the banked func_801885D0 just above the splice point). The draft had
 *    `extern s32 D_801D9760[]` -> "conflicting types". Lever (A): conform the decl
 *    VERBATIM and keep the disagreement at the use site, which already casts the
 *    decayed pointer to s32. Zero bytes change.
 *  - func_801292C8: not declared anywhere in this TU, but src/shared/engine_core.h
 *    declares it as `extern void func_801292C8(u8 *a0);` inside four DEFINE_ macros
 *    (6304/8491/13623/13794). None of those macros is expanded in this TU today, but
 *    conforming to that shape now makes the splice conflict-proof if one ever is.
 *    $a0 already holds the incoming pointer, so passing it costs no instruction
 *    (jal + nop delay slot, exactly as in the target).
 */

extern void func_801292C8(u8 *a0);

void func_801813FC(void *a0) {

    extern u8 D_801D9760[];
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
    a2 = (s32)D_801D9760 + v1;
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



extern void (*D_8018B944[])(void);

void func_801814B0(void *a0) {
    D_8018B944[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 func_8014BF6C(void);
extern s32 func_8012AD50(void *a0);

void func_801814EC(void *a0) {
    s32 s0;

    s0 = ((s32 (*)(void))func_8014BF6C)();
    while ((s0 & 0xFF) != 0) {
        func_8012C658(0x103, (s0 & 0xFF) - 1, (s32)a0);
        s0 = s0 - 1;
    }
    func_8012AD50(a0);
}


void func_80181554(void) {
}


extern void (*D_8018B94C[])(void);

void func_8018155C(void *a0) {
    D_8018B94C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80181708(void *a0);
extern s32 func_8012AD50(void *a0);

extern s32 D_801D2038[];
extern s32 D_8118B93C[];

void func_80181598(void *a0)
{
    s32 s0;

    s0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = s0;
    if (s0 != 0) {
        func_8001C214(s0, (s32)D_801D2038);
        *(s32 *)((s32)s0 + 0x20) = (s32)D_8118B93C;
        func_80181708(a0);
        func_8012AD50(a0);
    }
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80181600);

extern void func_8012AD80(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C098(void);
void func_801816C8(s32 a0) {
    func_8012AD80(a0);
    if (func_8012BEE8(a0)) {
        ((void (*)(s32))func_8012C098)(a0);
    }
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80181708);

void func_801817D8(u8 *a0, u8 *a1) {
    u16 sp0[3];

    sp0[0] = *(u16 *)(a0 + 6);
    sp0[1] = *(u16 *)(a0 + 0xA);
    sp0[2] = *(u16 *)(a0 + 0xE);

    sp0[0] += *(u16 *)(a1 + 0);
    sp0[1] += *(u16 *)(a1 + 2);
    sp0[2] += *(u16 *)(a1 + 4);
}



extern void (*D_8018B9B8[])(void);

void func_80181838(void *a0) {
    D_8018B9B8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80181874(void) {
}

extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012AD50(void *a0);
void func_8018187C(int param_1)
{
    if (((int (*)(void))func_8012BEE8)() != 0) {
        ((void (*)(int))func_8012AD50)(param_1);
    }
}


extern s32 func_800D0CE0(s32 arg);
    extern void func_8012C098(void);
    void func_801818B4(void *a0) {
        if (func_800D0CE0((s32)a0)) {
            ((void (*)(s32))func_8012C098)((s32)a0);
        }
    }


extern s32 func_8012E544(s32);
extern void func_800D0C48(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_8012BF4C(s32 *a0, s32 a1);

void func_801818EC(void) {
    s32 *s0;
    s0 = (s32 *)func_8012E544(0x116);
    if (s0 != 0) {
        func_800D0C48(1);
        func_8012AD44(s0, 1);
        func_8012BF4C(s0, 0x30);
    }
}



extern void (*D_8018BB08[])(void);

void func_80181940(void *a0) {
    D_8018BB08[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_8018BAF0[];

void func_8018197C(s32 a0) {
    s32 idx;
    s32 *entry;

    idx = *(s32 *)(a0 + 0x2C);
    entry = &D_8018BAF0[idx * 3];

    if (*(u16 *)((s32)entry + 0x6) != 0) {
        *(s32 *)(a0 + 0x1C) = rand() % *(u16 *)((s32)entry + 0x6);
    } else {
        *(s32 *)(a0 + 0x1C) = 0;
    }

    *(u16 *)(a0 + 0x2) += 1;
}



extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);



void func_80181A30(s32 a0) {

    extern u8 D_8018B9C4[];
    extern s32 D_8018BAF0[];
    s32 effect;
    s32 count;
    s32 idx;
    s32 *entry;
    Quad_8018797C_80181A30 tmp;
    s32 off[3];
    u16 reload;

    effect = *(s32 *)(a0 + 0x20);
    count = *(s32 *)(a0 + 0x1c) - 1;
    *(s32 *)(a0 + 0x1c) = count;
    if (count == -1) {
        func_8001CC3C(effect, (s32)D_8018B9C4, 0, 0);
        *(u8 *)(effect + 0x27) = 0x9c;
        *(u16 *)(effect + 0x1a) = 0x4000;
        *(u16 *)(effect + 0x18) = 0x4000;
        *(u32 *)(effect + 4) = *(u32 *)(effect + 4) | 0x50000040;

        idx = *(s32 *)(a0 + 0x2c);
        entry = &D_8018BAF0[idx * 3];
        func_80128EA8(effect, a0 + 0x24, entry[0]);

        {
            s32 rnd;
            u32 sign;
            tmp = *(Quad_8018797C_80181A30 *)(entry[2] + 0x10);
            rnd = rand();
            off[0] = rnd % (tmp.f0 + 1);
            sign = rnd & 1;
            if (sign != 0) {
                off[0] = -off[0];
            }
            off[1] = rnd % (tmp.f1 + 1);
            if (sign != 0) {
                off[1] = -off[1];
            }
            off[2] = rnd % (tmp.f2 + 1);
            if (sign != 0) {
                off[2] = -off[2];
            }
        }

        *(s32 *)(a0 + 0x10) = *(s32 *)(entry[2] + 0) + off[0];
        *(s32 *)(a0 + 0x14) = *(s32 *)(entry[2] + 4) + off[1];
        *(s32 *)(a0 + 0x18) = *(s32 *)(entry[2] + 8) + off[2];

        {
            s32 rnd;
            u32 sign;
            tmp = *(Quad_8018797C_80181A30 *)(entry[2] + 0x30);
            rnd = rand();
            off[0] = rnd % (tmp.f0 + 1);
            sign = rnd & 1;
            if (sign != 0) {
                off[0] = -off[0];
            }
            off[1] = rnd % (tmp.f1 + 1);
            if (sign != 0) {
                off[1] = -off[1];
            }
            off[2] = rnd % (tmp.f2 + 1);
            if (sign != 0) {
                off[2] = -off[2];
            }
        }

        *(s32 *)(a0 + 0x2c) = *(s32 *)(entry[2] + 0x20) + off[0];
        *(s32 *)(a0 + 0x30) = *(s32 *)(entry[2] + 0x24) + off[1];
        *(s32 *)(a0 + 0x34) = *(s32 *)(entry[2] + 0x28) + off[2];

        reload = *(u16 *)((s32)entry + 4);
        *(u16 *)(a0 + 2) = *(u16 *)(a0 + 2) + 1;
        *(u32 *)(a0 + 0x1c) = reload;
    }
}


extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_801292C8(u8 *a0);
extern void func_8012931C(struct vec*);

void func_80181D9C(s32 arg0)
{
    register s32 s1 __asm__("$17") = arg0;
    register s32 s0 __asm__("$16");
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");
    register s32 a0 __asm__("$4");
    register s32 a1 __asm__("$5");
    register s32 a2 __asm__("$6");
    register s32 zr __asm__("$0");

    
    v0 = *(s32 *)(s1 + 0x10);
    v1 = *(s32 *)(s1 + 0x2C);
    a1 = *(s32 *)(s1 + 0x30);
    a2 = *(s32 *)(s1 + 0x34);

    
    s0 = *(s32 *)(s1 + 0x20);

    
    v0 = v0 + v1;
    *(s32 *)(s1 + 0x10) = v0;

    
    v0 = *(s32 *)(s1 + 0x14);
    v1 = *(s32 *)(s1 + 0x18);
    v0 = v0 + a1;
    v1 = v1 + a2;
    *(s32 *)(s1 + 0x14) = v0;
    *(s32 *)(s1 + 0x18) = v1;

    
    ((void (*)(void))func_8012931C)();

    
    a0 = s0 + zr;

    
    v0 = *(u16 *)(s0 + 0x1A);
    v0 = v0 - 0x100;
    *(u16 *)(a0 + 0x1A) = (u16)v0;
    *(u16 *)(a0 + 0x18) = (u16)v0;

    
    if (func_80128ED8(a0, (s32 *)(s1 + 0x24)) != 0) {
        func_801292C8((u8 *)s1);
    } else {
        v0 = *(s32 *)(s1 + 0x1C);
        if (v0 != 0) {
            v0--;
            *(s32 *)(s1 + 0x1C) = v0;
            if (v0 == 0) {
                func_801292C8((u8 *)s1);
            }
        }
    }
}



extern void (*D_8018BBBC[])(void);

void func_80181E44(void *a0) {
    D_8018BBBC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
    void func_80181E80(void) {
        ((s32 (*)(void))func_8012AD50)();
    }


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80181EA0);

extern u8 *func_801290DC(s32 a0, u8 *a1);

void func_80182050(u8 *a0, u8 *a1) {
    u16 temp[3];
    u16 v1_load;
    u8 *result;

    v1_load = *(u16 *)(a0 + 0x6);
    temp[0] = v1_load;

    temp[1] = *(u16 *)(a0 + 0xA);
    temp[2] = *(u16 *)(a0 + 0xE);

    temp[0] += *(u16 *)(a1 + 0x0);
    temp[1] += *(u16 *)(a1 + 0x2);
    temp[2] += *(u16 *)(a1 + 0x4);

    result = func_801290DC(0x3D, (u8 *)temp);

    if (result) {
        *(s32 *)(result + 0x2C) = *(s16 *)(a1 + 0x6);
    }
}


#include "common.h"

extern u8 D_8018BBAC[];
extern s32 D_80126B58;
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_80013294(void *a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801820E4(u8 *arg0)
{
    s32 sp10[2];
    u8 *p;
    s32 base;
    s16 snd;

    p = D_8018BBAC + *(s16 *)(arg0 + 0xFC) * 8;
    base = (s32)&D_80126B58;
    if (*(s16 *)(p + 6) != 0) {
        func_80015978(base + 4, sp10);
        snd = func_80013294(sp10, p);
        if (snd < 0xC00) {
            snd = (0xC00 - snd) * 127 / 0xC00;
            if (snd < 0) {
                snd = 0;
            }
            if (snd >= 0x80) {
                snd = 0x7F;
            }
            func_8002D4C8(*(u16 *)(p + 6), (u16)snd | 0x1000);
        }
    }
}



extern void (*D_8018BC04[])(void);

void func_801821B8(void *a0) {
    D_8018BC04[*(u16 *)((s32)a0 + 0x2)]();
}




s32 func_801821F4(void *a0, s32 *p) {
    s32 cur = *(s32 *)((s32)a0 + 0xDC);

    if (p[0] != cur) {
        p += 2;
        for (;;) {
            s32 t = p[0];
            if (t == 0) {
                return cur;
            }
            p += 2;
            if (t == cur) {
                break;
            }
        }
        p -= 2;
    }
    return p[1];
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_801821F4(void *a0, s32 *p);
extern s32 D_8018BBF4[];
extern s32 D_8018BBE4[];
extern s32 D_8018BBD4[];
extern s32 D_8018BBC4[];

void func_8018223C(void *a0) {
    s32 s1;
    s32 v0;

    s1 = func_80029504();
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, 0);
    *(s32 *)((s32)a0 + 0x58) = (s32)D_8018BBF4;
    *(u16 *)((s32)a0 + 0x2) += 1;
    *(s16 *)((s32)a0 + 0x5C) = 0x80;

    if (s1 >= 0x384) {
        *(s32 *)((s32)a0 + 0xDC) = func_801821F4(a0, D_8018BBE4);
    } else if (s1 >= 0x258) {
        *(s32 *)((s32)a0 + 0xDC) = func_801821F4(a0, D_8018BBD4);
    } else if (s1 >= 0xC8) {
        *(s32 *)((s32)a0 + 0xDC) = func_801821F4(a0, D_8018BBC4);
    }
}


void func_80182308(void) {
}

    void func_80182310(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_8012704C;
        D_8012704C = 1;
    }



extern void (*D_8018BC1C[])(void);

void func_80182324(void *a0) {
    D_8018BC1C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern u8 D_8018BC0C[];

void func_80182360(void *a0) {
    s32 ret;

    ret = func_8012C1B8();
    *(s32 *)((u8 *)a0 + 0x20) = ret;
    if (ret == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(ret, 0);
    *(u16 *)((u8 *)a0 + 0x2) = 1;
    *(u16 *)((u8 *)a0 + 0x5C) = 0x40;
    *(s32 *)((u8 *)a0 + 0x58) = (u32)D_8018BC0C;
}


void func_801823C8(void) {
}

INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_801823D0);

extern s32 D_801D9860;
extern u16 D_8018BC24[];
extern u16 D_8018BC64[];
extern u16 D_801D9864[];
extern u16 D_801D98A4[];
extern u8  D_8018BC84[];
extern void func_800183E0(s32 a0);

void func_8018246C(void) {
    u32 i;
    u32 t;

    t = (u32)D_801D9860 >> 8;
    for (i = 0; i < 0x20; i++) {
        D_801D9864[i] = D_8018BC24[(t + i) & 0x1F] | 0x8000;
    }

    t = (u32)D_801D9860 >> 8;
    for (i = 0; i < 0x10; i++) {
        D_801D98A4[i] = D_8018BC64[(t + i) & 0xF] | 0x8000;
    }

    func_800183E0((s32)D_8018BC84);

    D_801D9860 += 0x100;
}



extern void (*D_8018BCBC[])(void);

void func_80182544(void *a0) {
    D_8018BCBC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_800291B4(s32 arg);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32, void*);
extern u8 D_801C0B48[];
extern s32 D_8018BCB4[];
extern u8 D_80187B3C[];

void func_80182580(void *a0) {
    register void *s0 __asm__("$16");
    register s32 v0 __asm__("$2");
    s32 r;

    s0 = a0;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)s0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(s0);
        return;
    }

    func_8001C214(v0, (s32)D_801C0B48);

    r = func_800291B4(D_8018BCB4[*(u16 *)((s32)s0 + 0x70) & 0xF]) & 0xFF;
    if (r != 3) {
        func_8012C658(0x15A, *(s16 *)((s32)s0 + 0x70), (s32)s0);
    }

    *(u16 *)((s32)s0 + 2) = 1;
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)s0, (s32)D_80187B3C);
}


void func_80182628(void) {
}

extern void (*D_8018BCC4[])(void);

void func_80182630(void *a0) {
    D_8018BCC4[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_8018266C);

void func_80182700(void) {
}


extern void (*D_8018BCFC[])(void);

void func_80182708(void *a0) {
    D_8018BCFC[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_8018BCCC[];

/* 12-byte record, three s32 fields, declared align-1/packed so gcc-2.7.2's
 * emit_block_move takes the unaligned lwl/lwr + swl/swr path on BOTH the
 * table read and the write into a0+0xFC (matching the target even though
 * a0+0xFC is actually 4-aligned at runtime -- codegen goes off the type's
 * declared alignment, not the runtime address; cookbook §48-C2). */
struct Rec80182744_s {
    s32 f0;
    s32 f1;
    s32 f2;
} __attribute__((packed, aligned(1)));
typedef struct Rec80182744_s Rec80182744;

extern Rec80182744 D_8018BCD8[];

void func_80182744(void *a0) {
    s32 ret;
    u16 t;
    u16 t2;
    void *q;

    ret = func_8012C1B8();
    *(s32 *)((u8 *)a0 + 0x20) = ret;
    if (ret == 0) {
        func_8012CAE4(a0);
        return;
    }

    t = *(u16 *)((u8 *)a0 + 0x70);
    t &= 0xF;
    func_8001C214(ret, D_8018BCCC[t]);

    t2 = *(u16 *)((u8 *)a0 + 0x70);
    *(u16 *)((u8 *)a0 + 0x2) = 1;
    t2 &= 0xF;
    *(Rec80182744 *)((u8 *)a0 + 0xFC) = D_8018BCD8[t2];

    q = *(void **)((u8 *)a0 + 0x64);
    *(s32 *)((u8 *)a0 + 0xCC) = (s32)((u8 *)a0 + 0xFC);
    *(u16 *)((u8 *)a0 + 0xD0) = 1;
    *(s32 *)((u8 *)a0 + 0xD4) = 0;
    *(s16 *)((u8 *)a0 + 0xD8) = -2;
    *(u16 *)((u8 *)a0 + 0x108) = *(u16 *)((u8 *)q + 0x36);
    func_8012A828((s32)a0, (void *)((u8 *)a0 + 0xCC));
}


void func_80182858(void) {
}


extern s32 func_80178B18(s32, s32);
    extern short D_8018BD1C;
    void func_80182860(void * arg0) {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32, s32))func_80178B18)((int)arg0, (int)&D_8018BD1C);
    }



extern void (*D_8018BD9C[])(void);

void func_8018288C(void *a0) {
    D_8018BD9C[*(u16 *)((s32)a0 + 0x2)]();
}


extern u16 D_80126B5E;
extern void func_80182860(void*);
void func_801828C8(void) {
    if ((*(s16 *)&D_80126B5E) < 0xB60) {
        ((void (*)(void))func_80182860)();
    }
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_801828F8);

void func_80182958(void *a0) {
    extern s32 D_801D5BC8;
    extern s32 D_8018BD04;
    extern s32 D_801D3318;
    s32 v0;

    v0 = func_80029504();
    if ((u32)(v0 - 0xD2) >= 0x14 ||
        (v0 = func_8012C1B8(), (*(s32 *)((s32)a0 + 0x20) = v0), v0 == 0)) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801D5BC8);
        *(u16 *)((s32)a0 + 0x2) = 1;
        func_8012E8E0((s32)a0, (s32)&D_8018BD04);
        func_8012A828((s32)a0, (s32)&D_801D3318);
        *(s16 *)(*(s32 *)((s32)a0 + 0x68) + 0xC) = 0x7FFF;
    }
}




s32 func_801829F4(void) {

    extern s32 D_8012704C;
    if (D_8012704C == 0) {
        return 0x18;
    }
    return 0x2B;
}



extern void (*D_8018BE04[])(void);

void func_80182A14(void *a0) {
    D_8018BE04[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conformed to the TU (ov_SC04_018_jr_8017AE2C.c) — lever (A):
 *   func_8012A828 : TU declares `extern void ((void (*)(s32*, s32))func_8012A828)(s32*, s32);`
 *                   at L3460 / L4615 / L5083 / L5372 / L5859 / L6004 / L6155 /
 *                   L6479 / L6504 / L6529.  The draft's `(s32, s32)` form caused
 *                   the 7697-vs-6529 conflict.  Conformed here; the type
 *                   disagreement is pushed to a cast at the call site.
 *   D_80187B3C    : TU declares `extern u8 D_80187B3C[];` (block scope, L3467).
 *                   Conformed; `(s32)D_80187B3C` == `(s32)&D_80187B3C`.
 *   func_801788B8 : verbatim from TU L2532 / L7756 (below the splice point).
 *   func_8012C354, D_8018BDB8, func_80182B34, func_80182A50 : no other
 *                   declaration anywhere in the TU (func_80182B34 / func_80182A50
 *                   appear only as INCLUDE_ASM, which emits no C declaration).
 *
 * Body: the original draft was NOT byte-correct.  `*(u16 *)(x + 2) = 1;` must be
 * sequenced BEFORE the func_8012A828 call, not after it — with it after, gcc
 * coalesces the store base onto $a0 (`sh v0,2(a0)`) and re-emits the arg copy,
 * giving a 6-instruction ADDRESSING/cse diff.  Moved above the call; both stores
 * now retire off $s0 and the sh lands in the jal delay slot, as in the target. */

extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32, void*);
extern s32 func_801788B8(s32 arg0, s32 arg1);

extern void func_80182B34(void);

void func_80182A50(s32 a0) {

    extern M2C_UNK D_8018BDB8;
    extern u8 D_80187B3C[];
    s32 s0 = a0;
    if (func_8012C354(a0, (s32)&D_8018BDB8)) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(u16 *)(s0 + 0x2) = 1;
        ((void (*)(s32*, s32))func_8012A828)((s32 *)s0, (s32)D_80187B3C);
        func_801788B8(s0, (s32)func_80182B34);
    }
}


void func_80182AB4(void) {
}

extern void func_80178CBC(s32 a0, s32 a1);
extern short D_8018BDEC;

void func_80182ABC(void *a0) {
    func_80178CBC((s32)a0, (s32)&D_8018BDEC);
    *(short *)((char *)a0 + 2) = 0x3;
}



extern int func_80178970(void);
extern void func_80178D18(void);

void func_80182AF4(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


extern void func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 aF80182B34(void *a0) __asm__("func_80182B34");

s32 aF80182B34(void *a0)
{
    if (((s32 (*)(s32))func_8012BD14)(*(s32 *)((s32)a0 + 0x64)) > 0x1000) {
        return 0;
    }
    *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) = 2;
    func_80178BF8();
    return (s32)func_80172710;
}



extern void (*D_801C4250[])(void);

void func_80182B90(void *a0) {
    D_801C4250[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80182BCC(void *a0) {

    extern s32 D_801C4200;
    extern s32 D_801C4240;

    if (((*(u16 *)((s32)a0 + 0x70) & 0x1) != 0) &&
        ((func_80029178(0xE7) & 0xFF) == 0) &&
        ((u32)func_80029504() < 0x46)) {
        func_8012CAE4(a0);
        return;
    }

    if (func_8012C354((s32)a0, (s32)&D_801C4200) != 0) {
        func_8012A828((s32)a0, (void *)&D_801C4240);
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x40000000;
        *(s32 *)((s32)a0 + 0x1C) = 0;
        *(s16 *)((s32)a0 + 0xE0) = 1;
        *(s16 *)((s32)a0 + 0xFC) = 0;
        *(u8 *)((s32)a0 + 0x75) = 0xE;
        *(s16 *)((s32)a0 + 0x2) = 1;
        *(s32 *)((s32)a0 + 0xDC) |= 0x1;
    }
}


#include "common.h"

extern s32 func_8012B8A4(s16 *arg);
extern void func_8012DFD4(u8 *arg);
extern void func_80182D70(s32 arg);

void func_80182CA4(s32 param_1) {
    s32 dc;
    s32 cnt;
    s16 t;

    dc = *(s32 *)(param_1 + 0xDC);
    if ((dc & 1) != 0) {
        if (*(u8 *)(param_1 + 0x74) != 0) {
            *(s16 *)(param_1 + 0xFC) = func_8012B8A4((s16 *)param_1) + 0x400;
            *(s16 *)(param_1 + 0xE0) = 0x10;
            *(s32 *)(param_1 + 0xDC) = *(s32 *)(param_1 + 0xDC) & ~1;
        }
    } else {
        if (*(u8 *)(param_1 + 0x74) == 0) {
            *(s32 *)(param_1 + 0xDC) = dc | 1;
        }
    }
    func_80182D70(param_1);
    func_8012DFD4((u8 *)param_1);
    cnt = (*(s32 *)(param_1 + 0x1C) + 1) & 0x1F;
    *(s32 *)(param_1 + 0x1C) = cnt;
    if (cnt == 0) {
        t = *(u16 *)(param_1 + 0xE0) - 1;
        *(u16 *)(param_1 + 0xE0) = t;
        if (t == 0) {
            *(u16 *)(param_1 + 0xE0) = 1;
        }
    }
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80182D70);

INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80182E84);

extern s32 D_801C473C;
extern s32 D_801C4850;
extern u8 D_801C7AA4[];
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_80143994(s32 a0, s32 a1);

void func_80182F08(s32 a0) {
    s32 v0;
    s32 v1;
    void *a0_val;

    if (func_8012C354(a0, (s32)&D_801C473C) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;

        v1 = *(s32 *)(a0 + 0xC4);
        *(s32 *)(a0 + 0xBC) = (s32)&D_801C4850;
        *(s32 *)(a0 + 0xB4) = -0x20AD;
        *(s32 *)(a0 + 0xE0) = 0;
        v1 = v1 | 0x1;
        *(s32 *)(a0 + 0xC4) = v1;

        func_8012A828(a0, (void *)&(*(s32 *)D_801C7AA4));

        if ((*(u16 *)(a0 + 0x70) & 0x1) != 0) {
            a0_val = (void *)*(s32 *)(a0 + 0x20);
            *(s16 *)(a0 + 0x2) = 1;
            *(s16 *)(a0 + 0x5C) = 0;
            *(s32 *)(a0_val + 0x4) = *(s32 *)(a0_val + 0x4) | 0x80000000;
        } else {
            *(s16 *)(a0 + 0x2) = 3;
            *(s32 *)(a0 + 0xCC) = ((s32 (*)(s32, s32))func_80143994)(a0, 0x3000);
        }
    }
}


#include "common.h"

extern s32 func_8012E778(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012BD14(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_80143994(s32 a0, s32 a1);

void func_80182FC4(s32 a0)
{
    s32 t;
    s32 u;
    register s32 p __asm__("$3");

    if (*(s16 *)(a0 + 0x102) == 0) {
        if (func_8012E778(a0, 0x64008C) == 0) {
            return;
        }
        *(s16 *)(a0 + 0x102) = 1;
    } else {
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        if (((s32 (*)(s32))func_8012BD14)(a0) <= 0x18FFF) {
            return;
        }
    }

    *(s16 *)(a0 + 0x2) = 2;
    *(s32 *)(a0 + 0x1C) = 8;
    *(u16 *)(a0 + 0x5C) = 0xAA10;

    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x2C) |= 0x10;

    p = *(s32 *)(a0 + 0x20);
    *(s32 *)(p + 0x4) &= 0x7FFFFFFF;
    t = func_80047948(0x380);

    p = *(s32 *)(a0 + 0x20);
    *(s16 *)(p + 0x1C) = t;
    *(s16 *)(p + 0x18) = t;

    u = func_8004787C(0x380);
    p = *(s32 *)(a0 + 0x20);
    *(s16 *)(p + 0x1A) = (u << 1) + 0x1000;

    *(s32 *)(a0 + 0xCC) = ((s32 (*)(s32, s32))func_80143994)(a0, 0x3000);
}


extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8012BEE8(s32 a0);

void func_801830B8(s32 s0) {
  s32 v0;
  s32 v1;

  if (func_8012BEE8(s0) != 0) {
    v0 = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(v0 + 0x2C);
    v1 &= 0xFFEF;
    *(s16 *)(v0 + 0x2C) = v1;
    *(s16 *)(s0 + 0x2) = 3;
  } else {
    s32 a0 = *(s32 *)(s0 + 0x1C);
    a0 = (a0 << 10) >> 3;
    v0 = func_80047948(a0);
    v1 = *(s32 *)(s0 + 0x20);
    *(s16 *)(v1 + 0x1C) = v0;
    *(s16 *)(v1 + 0x18) = v0;
    a0 = *(s32 *)(s0 + 0x1C);
    a0 = (a0 << 10) >> 3;
    v0 = func_8004787C(a0);
    v0 = v0 << 1;
    v1 = *(s32 *)(s0 + 0x20);
    v0 += 0x1000;
    *(s16 *)(v1 + 0x1A) = v0;
  }
}


extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801C7AA4[];

void func_80183154(s32 param_1) {
    *(s16 *)(param_1 + 2) = 4;
    *(u16 *)(param_1 + 0x5C) = 0xAA10;
    func_8012A828(param_1, D_801C7AA4);
    *(s32 *)(param_1 + 0x1C) = 0x20;
    if (*(s32 *)(param_1 + 0xE0) != 0) {
        *(s32 *)(param_1 + 0xE0) = 0;
        *(s16 *)(param_1 + 0xA) = *(s16 *)(param_1 + 0xA) + 0x30;
    }
}


extern s32 func_8012BEE8(s32 a0);
extern s32 func_801844B0(s32 a0);

void func_801831B4(s32 a0) {
    u8 *p = *(u8 **)(a0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + 0x40;
    if (func_801844B0(a0) == 1) {
        return;
    }
    if (func_8012BEE8(a0) != 0) {
        *(s16 *)(a0 + 2) = 5;
    }
}


#include "common.h"

extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern u8 D_801C7AA4[];

void func_80183214(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 6;
    func_8012B23C(s0);
    func_8012B178(s0, 0xFFFE8000);
    func_8012A828(s0, (void *)&D_801C7AA4);
    *(s32 *)((s32)a0 + 0x1C) = 0x96;
    *(u16 *)((s32)a0 + 0xE6) = 0;
}


extern s32 func_801841F8(s32 a0, s32 a1);
extern s32 func_801844B0(s32 a0);
extern u8 D_800D3918[];

void func_80183270(s32 arg0) {
    if (func_801844B0(arg0) != 1) {
        if (func_801841F8(arg0, D_800D3918) == 0) {
            *(s16 *)(arg0 + 2) = 3;
        }
    }
}


extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);
extern s32 D_801C7B9C;

void func_801832C0(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 8;
    func_8012B23C(s0);
    func_8012A828(s0, (void *)&D_801C7B9C);
    *(s32 *)((s32)a0 + 0x1C) = 0x24;
    *(u16 *)((s32)a0 + 0xE6) = 0;
}


extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_801841F8(s32 a0, s32 a1);
extern u8 D_800D3918[];
extern void func_8012B178(s32 a0, s32 a1);

void func_8018330C(s32 a0)
{
    register s32 s0 __asm__("$16");
    register s32 v1 __asm__("$3");
    s32 v0;
    u16 *p;

    s0 = a0;
    __asm__ __volatile__("");
    v0 = func_8012B8E4(s0, 8);
    p = *(u16 **)(s0 + 0x20);
    p[9] = p[9] + (u16)v0;

    if (*(s32 *)(s0 + 0x1C) < 0x19) {
        func_8012B178(s0, 0xFFFC0000);
        v1 = func_801841F8(s0, (void *)D_800D3918);

        if (v1 == 0) {
            v0 = 9;
            goto L_store;
        }
        v0 = -1;
        if (v1 == -1) {
            
            return;
        }
        
    }

    v0 = func_8012BEE8(s0);
    if (v0 != 0) {
        v0 = 9;
    } else {
        v0 = func_8012BCCC(s0);
        if (v0 < 0x2001) {
            v0 = 9;
        } else {
            return;
        }
    }

L_store:
    *(s16 *)(s0 + 0x2) = v0;
}



















void func_801833BC(void *a0)
{
  s32 v1 = *((s32 *) (((s32) a0) + 0x20));
  int new_var;
  *((s16 *) (((s32) a0) + 0x2)) = 0xA;
  *((s16 *) (((s32) a0) + 0x5C)) = 0;
  *((s16 *) (((s32) a0) + (new_var = 0x34))) = 0;
  *((s32 *) (((s32) a0) + 0x1C)) = 0x8;
  *((s16 *) (((s32) v1) + 0x2C)) |= 0x10;
}



extern s32 func_8012BEE8(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_80143BDC(u16 *a0);
extern void func_80184008(s32 a0);

void func_801833EC(s32 param_1)
{
    s32 iVar3;
    s32 uVar1;
    s32 sVar2;
    u16 sp10[3];

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        if (func_8012BEE8(param_1) != 0) {
            *(s16 *)(param_1 + 0x34) = 1;
            *(s32 *)(param_1 + 0x1C) = 0x1E;
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) | 0x80000000;
            *(s16 *)(param_1 + 0xE4) = 3;
        } else {
            uVar1 = func_8004787C((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            iVar3 = *(s32 *)(param_1 + 0x20);
            *(s16 *)(iVar3 + 0x1C) = uVar1;
            *(s16 *)(iVar3 + 0x18) = uVar1;
            sVar2 = func_80047948((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = sVar2 * 2 + 0x1000;
        }
        break;
    case 1:
        uVar1 = *(u16 *)(param_1 + 0xE4) - 1;
        *(u16 *)(param_1 + 0xE4) = uVar1;
        if ((s16)uVar1 == 0) {
            sp10[0] = *(u16 *)(param_1 + 0x6);
            sp10[1] = *(u16 *)(param_1 + 0xA) - 0x38;
            sp10[2] = *(u16 *)(param_1 + 0xE);
            {
                s32 e;
                s32 q;

                e = func_80143BDC(sp10);
                if (e != 0) {
                    q = *(s32 *)(e + 0xCC);
                    if (q != 0) {
                        *(s16 *)(q + 0x1A) = 0x5000;
                        *(s16 *)(q + 0x18) = 0x5000;
                    }
                }
            }
            *(s16 *)(param_1 + 0x34) = 2;
        }
        /* fallthrough */
    case 2:
        if (func_8012BEE8(param_1) != 0) {
            *(s16 *)(param_1 + 0x34) = 3;
            *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) & 0x7FFFFFFF;
            func_80184008(param_1);
            *(s32 *)(param_1 + 0x1C) = 8;
            *(u16 *)(param_1 + 0x5C) = 0xAA10;
        }
        break;
    case 3:
        if (func_8012BEE8(param_1) != 0) {
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
                *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) & 0xFFEF;
            *(s16 *)(param_1 + 0x2) = 0xB;
        } else {
            sVar2 = func_80047948((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            iVar3 = *(s32 *)(param_1 + 0x20);
            *(s16 *)(iVar3 + 0x1C) = sVar2;
            *(s16 *)(iVar3 + 0x18) = sVar2;
            uVar1 = func_8004787C((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = uVar1 * 2 + 0x1000;
        }
        break;
    }
}


extern s32 D_801C7C74;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B23C(s32 a0);

void func_80183600(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0xC;
    func_8012B23C(s0);
    func_8012A828(s0, (void *)&D_801C7C74);
    *(s32 *)((s32)a0 + 0x1C) = 0x1A;
    *(u16 *)((s32)a0 + 0xE6) = 0;
    func_8012B23C(s0);
}


extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_801841F8(s32 a0, s32 a1);
extern u8 D_800D3918[];
extern void func_8012B178(s32 a0, s32 a1);

void func_80183654(s32 s0) {
    register s32 v0 __asm__("$2");
    s32 v1;

    v0 = func_8012B8E4(s0, 8);
    v1 = *(s32*)(s0 + 0x20);
    *(s16*)(v1 + 0x12) = (s16)(*(u16*)(v1 + 0x12) + v0);
    func_8012B178(s0, 0xFFFC0000);
    v0 = func_801841F8(s0, D_800D3918);
    if (v0 == -1)
        return;
    v0 = func_8012BEE8(s0);
    if (v0 != 0) {
        v0 = func_8012BCCC(s0);
        v0 = (v0 < 0x7001);
        if (v0)
            v0 = 0xD;
        else
            v0 = 0x3;
    } else {
        v0 = func_8012BCCC(s0);
        if (v0 < 0x3001)
            v0 = 0xD;
        else
            return;
    }
    *(s16*)(s0 + 0x2) = v0;
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_801836FC);

extern s32 func_8012B8E4(s32 arg0, s32 arg1);
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80183E70(s32 a0);

void func_80183744(void *a0)
{
    s32 s0 = (s32)a0;
    s32 v0;
    s32 s1;

    v0 = func_8012BCCC(s0);
    if (v0 <= 0x14400) {
        if (*(s32 *)(s0 + 0x1C) >= 0x16) {
            v0 = func_8012B8E4(s0, 8);
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) + v0;
        }
        s1 = *(s32 *)(s0 + 0x1C);
        if (s1 == 0x15) {
            func_8002D4C8(0x522, 0);
        }
        if (s1 != 0x15 || *(s32 *)(s0 + 0x1C) != s1) {
            s32 v1 = *(s32 *)(s0 + 0x1C);
            if (v1 == 0xB || v1 == 1) {
                func_80183E70(s0);
            }
        } else {
            func_80183E70(s0);
        }
        v0 = func_8012BEE8(s0);
        if (v0 == 0) {
            return;
        }
        v0 = 3;
    } else {
        v0 = 7;
    }
    *(s16 *)(s0 + 2) = (s16)v0;
}


extern s32 D_801C7B9C;
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012B2CC(s32 a0);

void func_80183818(void *a0) {
    s32 s0 = (s32)a0;
    *(u16 *)((s32)a0 + 2) = 0x10;
    func_8012B2CC(s0);
    func_8012B23C(s0);
    func_8012B178(s0, 0xFFFD0000);
    func_8012A828(s0, (void *)&D_801C7B9C);
    *(s32 *)((s32)a0 + 0x1C) = 0x1A;
    *(u16 *)((s32)a0 + 0xE6) = 0;
}


#include "common.h"

extern u8 D_800D3918[];
extern s32 func_8012BEE8(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801C7B9C;
extern s32 func_801841F8(s32 a0, s32 a1);

void func_80183878(void *a0) {
    if (*(s16 *)((s32)a0 + 0xAA) <= 0) {
        *(s16 *)((s32)a0 + 2) = 3;
    } else {
        if (func_8012BEE8((s32)a0) != 0) {
            func_8012A828((s32)a0, (void *)&D_801C7B9C);
            *(s32 *)((s32)a0 + 0x1C) = 0x1A;
        }
        func_801841F8((s32)a0, (s32)D_800D3918);
    }
}




void func_801838EC(void *a0)
{
    s32 a1;
    s32 b;
    u16 v1;

    a1 = *(s32 *)((s32)a0 + 0x20);
    v1 = *(u16 *)(a1 + 0x2C);
    __asm__ __volatile__("" : : "r"(v1));
    if (v1 & 0x10) {
        *(u16 *)(a1 + 0x2C) = v1 & 0xFFEF;
        b = *(s32 *)((s32)a0 + 0x20);
        *(u16 *)(b + 0x1C) = 0x1000;
        *(u16 *)(b + 0x1A) = 0x1000;
        *(u16 *)(b + 0x18) = 0x1000;
    }
}


void func_80183928(s32 a0) {
    s32 s0 = a0;
    *(s16 *)(s0 + 0x2) = 0xF;
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = (func_8012B864(s0) + 0x800) & 0xFFF;
}


extern void func_80131B14();
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801C81BC[];

void func_80183968(void *a0) {
    s32 s0;
    s32 v1;
    __asm__ __volatile__("" : "=r"(s0) : "0"(a0));

    if (*(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) & 0x10) {
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) &= ~0x10;
        v1 = *(s32 *)(s0 + 0x20);
        *(u16 *)(v1 + 0x1C) = 0x1000;
        *(u16 *)(v1 + 0x1A) = 0x1000;
        *(u16 *)(v1 + 0x18) = 0x1000;
    }

    func_80131B14(s0);
    func_8012A828(s0, D_801C81BC);
}


extern u8 D_801C4934[];
extern u8 D_801C4940[];
extern u8 D_801C823C[];
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);

void func_801839D8(s32 param_1) {
    s32 s0 = param_1;
    s32 v0;
    s32 t1;
    s32 t2;
    s32 t3;

    *(u16 *)(s0 + 0x5C) = *(u16 *)(s0 + 0x5C) & 0xFFFE;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) = (*(u16 *)(s0 + 0x62) + 0x800) & 0xFFF;

    t1 = *(s32 *)(s0 + 0x20);
    *(u16 *)(t1 + 0x14) = 0;
    *(u16 *)(t1 + 0x10) = 0;
    func_8012B23C(s0);

    *(u8 *)(s0 + 0xC2) = 0;
    *(u8 *)(s0 + 0xC3) = 0;
    *(u16 *)(s0 + 0x98) = 0;
    *(s32 *)(s0 + 0x1C) = 0;

    t2 = *(s32 *)(s0 + 0x20);
    *(u16 *)(t2 + 0x2C) = *(u16 *)(t2 + 0x2C) & 0xFFEF;

    t3 = *(s32 *)(s0 + 0x20);
    *(u16 *)(t3 + 0x1C) = 0x1000;
    *(u16 *)(t3 + 0x1A) = 0x1000;
    *(u16 *)(t3 + 0x18) = 0x1000;

    if (*(u16 *)(s0 + 0x5E) == 9 || *(u16 *)(s0 + 0x5E) == 0x1C) {
        func_8012B14C(s0, (s32)D_801C4934);
        v0 = 0xCC;
    } else {
        func_8012B14C(s0, (s32)D_801C4940);
        v0 = 0x100;
    }
    *(u16 *)(s0 + 0xDE) = v0;

    func_8012A828(s0, (void *)D_801C823C);
}


#include "common.h"

extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8012CC64(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_80131E00();
extern void func_8012B23C(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);

extern s32 D_801C494C;

void func_80183AC0(void *a0) {
    void *s0 = a0;
    s32 v0;
    s32 v1;
    s32 cnt;

    if (*(u8 *)(s0 + 0xC2) != 0) {
        goto L80183BC0;
    }

    func_8012DBD0((s32)a0, 0x50,
                  *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) + 0x800, 0x1D);

    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) - *(u16 *)(s0 + 0xDE);

    cnt = *(s32 *)(s0 + 0x1C) + 1;
    *(s32 *)(s0 + 0x1C) = cnt;
    if (cnt >= 0x29) {
        goto L80183C5C;
    }

    v1 = ((s32 (*)(s32, s32))func_8012CC64)((s32)s0, (s32)&D_801C494C);
    if ((v1 & 0x2000) == 0) {
        goto L80183B94;
    }
    if ((v1 & 0xFF) != 2) {
        goto L80183B60;
    }
    func_80131E00(s0, 0x12);
    return;

L80183B60:
    if (*(s16 *)(s0 + 0x76) <= 0) {
        func_80131E00(s0, 6);
        return;
    }
    *(u8 *)(s0 + 0xC1) = 0;
    *(u16 *)(s0 + 0x5E) = 0;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    *(s16 *)(s0 + 2) = 3;
    *(s32 *)(s0 + 0xE0) = 1;
    return;

L80183B94:
    if ((v1 & 0x4000) == 0) {
        return;
    }
    v0 = *(u8 *)(s0 + 0xC2) + 1;
    *(u8 *)(s0 + 0xC2) = v0;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
    func_8012B23C((s32)s0);
    *(s32 *)(s0 + 0x1C) = 0;
    return;

L80183BC0:
    v1 = ((s32 (*)(s32))func_8012CBA4)((s32)s0);
    if ((v1 & 0x2000) == 0) {
        goto L80183C24;
    }
    if ((v1 & 0xFF) != 2) {
        goto L80183BEC;
    }
    func_80131E00(s0, 0x12);
    return;

L80183BEC:
    if (*(s16 *)(s0 + 0x76) > 0) {
        goto L80183C10;
    }
    func_80131E00(s0, 6);
    goto L80183C24;

L80183C10:
    *(s16 *)(s0 + 2) = 3;
    *(u8 *)(s0 + 0xC1) = 0;
    *(u16 *)(s0 + 0x5E) = 0;
    *(s32 *)(s0 + 0xE0) = 1;

L80183C24:
    if ((*(s32 *)(s0 + 0x1C) & 3) == 3) {
        func_80143B6C((s32)s0, 1);
    }
    cnt = *(s32 *)(s0 + 0x1C) + 1;
    *(s32 *)(s0 + 0x1C) = cnt;
    if (cnt < 0x3D) {
        return;
    }

L80183C5C:
    func_80131E00(s0, 0xD);
    return;
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80183C7C);

INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80183CC4);

INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80183E70);

extern u32 D_801C4770[];
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void func_8001CD50(s32 a0, s32 a1);

u8 * func_80183F70(s32 a0, s32 a1, s32 a2) {
    register s32 s0 __asm__("$16") = a2;
    register s32 s2 __asm__("$18") = a0;
    u8 *s1;
    u8 *ret;
    register s32 v1 __asm__("$3");

    s1 = func_801290DC(0x17, (u8 *)a1);

    if (!s1) {
        return NULL;
    }

    s0 = *(s32 *)((char *)s1 + 0x20);
    func_8001CD50(s0, (s32)(&((u8 *)D_801C4770)[a2 << 6]));

    
    __asm__ volatile("move %0, %1" : "=r"(ret) : "r"(s1));

    v1 = 0xC00;
    *(u16 *)((char *)s0 + 0x1E) = v1;
    v1 = 0x1000;
    *(u16 *)((char *)s0 + 0x1A) = v1;
    *(u16 *)((char *)s0 + 0x18) = v1;
    v1 = *(s32 *)((char *)s0 + 0x4);
    *(u16 *)((char *)s0 + 0x12) = s2;
    v1 |= 0x40000000;
    *(s32 *)((char *)s0 + 0x4) = v1;

    return ret;
}


#include "common.h"

/* Local standalone-compile clone of engine_types.h's Blk20 (32-byte word block).
 * match_one's isolated compile only has -Iinclude and cannot resolve
 * ../shared/engine_types.h; the host TU already has Blk20 via engine_core.h.
 * When banking, prefer `extern Blk20 D_800AE620;` + `Blk20 m;`. */
struct Mtx32_80184008 { s32 w[8]; };

extern void func_8012B23C(s32 a0);
extern s32  func_80184520(s32 a0);
extern s32  func_80184580(void *a0, void *a1);
extern void func_8012ADE4(s32 a0);
extern s32  func_8012B864(s32 a0);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

extern u16  D_80126CB4;
extern u16  D_80126CB6;
extern u16  D_80126CB8;
extern s32 *D_80126B78;
extern struct Mtx32_80184008 D_800AE620;

void func_80184008(s32 a0) {
    s32 vec[3];                     /* sp+0x10 */
    s32 out[3];                     /* sp+0x20 */
    u16 sp30[3];                    /* sp+0x30 */
    u16 sv[3];                      /* sp+0x38 */
    s32 unused40[2];                /* sp+0x40 -- dead 8-byte slot the frame requires (§193-I) */
    struct Mtx32_80184008 m;        /* sp+0x48 */
    s32 pos[3];                     /* sp+0x68 (16.16 fixed point) */

    func_8012B23C(a0);

    sp30[0] = *(u16 *)(a0 + 0x3A);
    sp30[1] = *(u16 *)(a0 + 0x3E);
    sp30[2] = *(u16 *)(a0 + 0x42);

    if (func_80184520(a0) != 0) {
        goto body;
    }

    *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x88);
    *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0x8A);
    *(s16 *)(a0 + 0xE) = *(u16 *)(a0 + 0x8C);
    return;

found:
    *(s16 *)(a0 + 0x6) = sv[0];
    *(s16 *)(a0 + 0xA) = sv[1];
    *(s16 *)(a0 + 0xE) = sv[2];
    *(s32 *)(a0 + 0x14) = 0;
    goto tail;

body:
    *(s16 *)(a0 + 0x6) = D_80126CB4;
    *(s16 *)(a0 + 0xA) = D_80126CB6;
    *(s16 *)(a0 + 0xE) = D_80126CB8;

    vec[2] = (s32)0xFF600000;
    vec[1] = 0;
    vec[0] = 0;

    m = D_800AE620;
    RotMatrixY(*(s16 *)((u8 *)D_80126B78 + 0x12), &m);

    pos[1] = *(s32 *)(a0 + 0x8);
    do {
        pos[0] = *(s32 *)(a0 + 0x4);
        pos[2] = *(s32 *)(a0 + 0xC);
        func_800484EC((s32)&m, (s32)vec, (s32)out);
        pos[0] += out[0];
        pos[2] += out[2];
        sv[0] = *(u16 *)((u8 *)pos + 0x2);
        sv[1] = *(u16 *)((u8 *)pos + 0x6);
        sv[2] = *(u16 *)((u8 *)pos + 0xA);
        if (func_80184580(sp30, sv) == 1) {
            goto found;
        }
        vec[2] >>= 1;
    } while (-vec[2] > 0xFFFF);

    func_8012ADE4(a0);

tail:
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_8012B864(a0);
}


#include "common.h"

/* func_801841F8 -- mass-lane fresh crack (Phase 31 wave p31u)
 *
 * Byte-identical skeleton (seed_sim=1.0) to ov_SC02_011:func_8018DAA8
 * (already matched, src/ov_SC02_011/ov_SC02_011_jr_8017AE2C.c). Same
 * state-gate then "avoid overlapping same-kind entity" scan of the 0x60-entry
 * table at D_801202A0 (stride 0x10C), same offsets (a0+4/8/0xC from
 * a0+0x38/0x3C/0x40, angle fields at a0+6/a0+0xE), same callees. Ported
 * verbatim with the target's own function name; all callee/data symbols
 * verified against this target's own .s relocations.
 */

extern u8 D_801202A0[];

extern void func_8012ADE4(s32 a0);
extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);

extern void func_8012CC1C(s32 arg0, s32 arg1);
extern void func_80131E00(struct S80131E00 *a0, s32 a1);

s32 func_801841F8(s32 a0, s32 a1) {
    s32 state;
    u8 *p;
    s32 i;
    s32 ang;
    s32 buf[2];

    state = ((s32 (*)(s32, s32))func_8012CC1C)(a0, a1);

    if ((state & 0xFF) == 2) {
        func_80131E00((struct S80131E00 *)a0, 0x12);
        return -1;
    }

    if (state != 0x2000) {
        func_8012ADE4((s32)a0);
        return 0;
    }

    for (i = 0, p = D_801202A0; i < 0x60; i++, p += 0x10C) {
        if (*(u16 *)p != 0 && *(u16 *)a0 == *(u16 *)p && a0 != (s32)p) {
            if (func_8012BC60((struct Vec *)(a0 + 4), (struct Vec *)(p + 4)) < 0x1000) {
                *(s32 *)(a0 + 4) = *(s32 *)(a0 + 0x38);
                *(s32 *)(a0 + 8) = *(s32 *)(a0 + 0x3C);
                *(s32 *)(a0 + 0xC) = *(s32 *)(a0 + 0x40);

                ang = func_8012B6D4((s16 *)(a0 + 4), (s16 *)(p + 4));
                func_8012B0B4((unsigned int *)buf, ang, 0x41);

                {
                    register s32 t1 __asm__("$2") = *(s32 *)(p + 4);
                    register s32 v1 __asm__("$3") = buf[0];
                    register s32 t2 __asm__("$2");
                    register s32 t3 __asm__("$4");
                    register s32 t4 __asm__("$2");

                    *(s32 *)(a0 + 4) = t1;

                    t2 = *(u16 *)(a0 + 6);
                    t3 = *(s32 *)(p + 0xC);
                    t2 = t2 + v1;
                    *(s32 *)(a0 + 0xC) = t3;
                    *(u16 *)(a0 + 6) = t2;

                    t4 = *(u16 *)(a0 + 0xE);
                    v1 = v1 >> 16;
                    t4 = t4 + v1;
                    *(u16 *)(a0 + 0xE) = t4;
                }
                goto found;
            }
        }
    }

found:
    return 1;
}


#include "common.h"

/* Mass lane: adopted from banked twin ov_SC02_011:func_8018DBF4 (91 ins,
 * seed_sim 1.0) — same guards / block-copy shape / tail. Symbols spelled
 * from THIS target's .s and conformed to THIS TU's existing declaration
 * shapes (func_8012B2CC @ TU L2534; func_8012A828(s32,void*) @ L4583/4842/
 * 4876/4917 with extern u8 D_x[] second-arg pattern @ L4847-4848/4881-4882/
 * 4921-4922; func_8012C218(void *a0) @ L4365/4411/4725/4765/4875;
 * func_8002AC00(s32 a0) @ L4731). func_8002A04C / func_801439C0 / D_801C7AA4
 * are not declared anywhere in this TU, so declared fresh matching the
 * twin's proven-banked spelling. */

extern void func_8002A04C(void);
extern void func_8002AC00(s32 a0);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_801439C0(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012C218(void *a0);
extern u8 D_801C7AA4[];

void func_80184344(s32 a0) {
    u16 v1;

    if (*(s16 *)(a0 + 0x100) == 0) {
        func_8002A04C();
    }

    if (*(u8 *)(a0 + 0xC1) == 0xE) {
        func_8002AC00(0xA);
    }

    v1 = *(u16 *)(a0 + 0x70);
    if ((v1 & 1) == 0) {
        goto LCFC;
    }
    if ((v1 & 0x8000) != 0) {
        goto LD44;
    }
    if (*(u8 *)(a0 + 0xC1) == 0) {
        goto LCFC;
    }

    *(u8 *)(a0 + 0xC1) = 0;
    *(s16 *)(a0 + 0x2) = 1;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;

    {
        s32 ent;

        *(s16 *)(a0 + 0x5E) = 0;
        *(s16 *)(a0 + 0x5C) = 0;
        *(s16 *)(a0 + 0x76) = *(u16 *)(*(s32 *)(a0 + 0x78));
        ent = *(s32 *)(a0 + 0x20);
        *(s16 *)(ent + 0x14) = 0;
        *(s16 *)(ent + 0x12) = 0;
        *(s16 *)(ent + 0x10) = 0;
    }

    {
        u16 f88 = *(u16 *)(a0 + 0x88);
        u16 f8A = *(u16 *)(a0 + 0x8A);
        u16 f8C = *(u16 *)(a0 + 0x8C);

        *(s32 *)(a0 + 0x1C) = 0x40;
        *(s16 *)(a0 + 0xAA) = 0;
        *(s16 *)(a0 + 0x6) = f88;
        *(s16 *)(a0 + 0xA) = f8A;
        *(s16 *)(a0 + 0xE) = f8C;
        func_8012A828(a0, (void *)D_801C7AA4);
    }

    if (*(s32 *)(a0 + 0xCC) != 0) {
        func_801439C0(*(s32 *)(a0 + 0xCC));
    }

    func_8012B2CC(a0);
    return;

LCFC:
    if ((*(s16 *)(a0 + 0x70) & 0x8000) == 0) {
        s32 v1c = *(s32 *)(a0 + 0x68);
        if (v1c != 0) {
            if ((*(s16 *)(a0 + 0x72) & 0x8000) != 0) {
                u16 v0c = *(u16 *)(v1c + 0xA);
                v0c &= 0x7FFF;
                *(u16 *)(v1c + 0xA) = v0c;
            }
        }
    }
LD44:
    func_8012C218((void *)a0);
}


extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BDBC(s32 a0, s32 a1);

s32 func_801844B0(s32 obj) {
    s32 dist;

    dist = func_8012BCCC(obj);
    if (dist < 0x2001 || (dist <= 0x24000 && func_8012BDBC(obj, 0x400))) {
        *(s16 *)(obj + 0x2) = 7;
        return 1;
    }
    return 0;
}




s32 func_80184520(s32 a0) {
    s32 v[4];

    v[0] = *(s16 *)(a0 + 6) - *(s16 *)(a0 + 0x88);
    v[1] = 0;
    v[2] = *(s16 *)(a0 + 0xE) - *(s16 *)(a0 + 0x8C);
    Square0(&v[0], &v[0]);
    return (0x18FFFF < v[0] + v[2]) ^ 1;
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80184580);


extern void (*D_801C4954[])(void);

void func_80184658(void *a0) {
    D_801C4954[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80184694);

extern u16 D_801270C0;
extern void func_801292C8(u8 *a0);
extern void func_8012931C(struct vec*);
extern void func_801847FC(void);

void func_80184764(void *a0) {
    register s32 s0 __asm__("$16") = (s32)a0;
    s16 v1;
    u16 v0;
    s16 decremented;
    void *ptr_0x20;

    v1 = *(s16 *)&D_801270C0;

    if (v1 == 2) {
        return;
    }

    func_801847FC();

    v0 = *(u16 *)(s0 + 0x2C);
    decremented = v0 - 1;
    *(u16 *)(s0 + 0x2C) = decremented;

    if ((s16)v0 < 0) {
        func_801292C8((u8 *)s0);
        return;
    }

    ptr_0x20 = *(void **)(s0 + 0x20);
    *(u16 *)((s32)ptr_0x20 + 0x18) += 0x100;

    ptr_0x20 = *(void **)(s0 + 0x20);
    *(u16 *)((s32)ptr_0x20 + 0x1A) += 0x100;

    func_8012931C((struct vec *)s0);
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_801847FC);

#include "common.h"

/* func_80184958 — MASS lane fresh crack.
 *
 * Direct sibling of the MATCHED ov_SC02_011:func_8018E208 (skeleton sim
 * 0.9412, 84/84 ins). Same shape: computed matrix (func_80020DA4 +
 * func_80020F34, translation overwritten from the entity's s16 position)
 * fed through a 4-iteration loop over two advancing per-overlay vertex-pair
 * pointers (D_801C495C and D_801C495C+0x20), each iteration re-loading the
 * matrix into GTE via inline ctc2 and calling RotTransSV x2 + func_80135888.
 * Returns 1 on the first func_80135888 hit, else 0.
 *
 * Ported verbatim from the twin's three levers (loop-invariant hoisting in
 * loop-use order via inline preheader writes, `base` as its own local to
 * keep the vertex-array address in a dead pseudo, and a do{}while(0)
 * scheduling barrier after the func_80135888 call) — only the per-overlay
 * data symbol changed (D_801DF7B8 -> D_801C495C, per this target's own
 * relocation).
 */

extern s32 D_80126B58;                                     /* TU:55   verbatim */
extern void func_80020F34(s32 a0, s32 a1);                 /* TU:1664 verbatim */
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);  /* TU:591  verbatim */
extern void RotTransSV(void *a0, void *a1, void *a2);       /* TU:2650 verbatim */

/* not declared anywhere in src/; func_80020DA4 takes the (s32, s32) form of
 * its TU-declared sibling func_80020F34. D_801C495C is per-overlay data. */
extern void func_80020DA4(s32 a0, s32 a1);
extern u8 D_801C495C[];

/* named distinctly from this TU's own gte_SetRotMatrix/gte_SetTransMatrix
 * (defined later in the file for func_80185AE0) to avoid a redefinition. */
#define SRM_80184958(r0) __asm__ volatile (               \
    "lw $12, 0( %0 );"                                    \
    "lw $13, 4( %0 );"                                    \
    "ctc2 $12, $0;"                                       \
    "ctc2 $13, $1;"                                       \
    "lw $12, 8( %0 );"                                     \
    "lw $13, 12( %0 );"                                    \
    "lw $14, 16( %0 );"                                    \
    "ctc2 $12, $2;"                                        \
    "ctc2 $13, $3;"                                        \
    "ctc2 $14, $4"                                         \
    :                                                      \
    : "r"( r0 )                                            \
    : "$12", "$13", "$14" )
#define STM_80184958(r0) __asm__ volatile (               \
    "lw $12, 20( %0 );"                                    \
    "lw $13, 24( %0 );"                                    \
    "ctc2 $12, $5;"                                        \
    "lw $14, 28( %0 );"                                    \
    "ctc2 $13, $6;"                                        \
    "ctc2 $14, $7"                                         \
    :                                                      \
    : "r"( r0 )                                            \
    : "$12", "$13", "$14" )

s32 func_80184958(void *a0)
{
    s32 *cfg;
    s32  i;
    u8  *p0;
    u8  *p1;
    u8  *base;
    s32  matrix[8];   /* sp+0x10, MATRIX-shaped: t[] at matrix[5..7] */
    s32  sv0[2];      /* sp+0x30 */
    s32  sv1[2];      /* sp+0x38 */
    s32  flag;        /* sp+0x40 */
    s32  hit;

    cfg = (s32 *)&D_80126B58;
    p0 = (u8 *)*(s32 *)((s32)a0 + 0x20);

    func_80020DA4((s32)p0 + 0x10, (s32)matrix);
    func_80020F34((s32)matrix, (s32)p0 + 0x18);

    matrix[5] = *(s16 *)(p0 + 0x8);
    matrix[6] = *(s16 *)(p0 + 0xA);
    matrix[7] = *(s16 *)(p0 + 0xC);

    base = D_801C495C;
    p1 = base + 0x20;
    p0 = base;

    for (i = 0; i < 4; i++) {
        SRM_80184958(matrix);
        STM_80184958(matrix);

        RotTransSV(p0, sv0, &flag);
        RotTransSV(p1, sv1, &flag);

        hit = func_80135888(*(s32 *)((u8 *)cfg + 0x20), *(s32 *)((u8 *)cfg + 0x38),
                            (s32)sv0, (s32)sv1);
        do { } while (0);   /* scheduling barrier — see twin note 3, do not delete */
        p1 += 8;
        if (hit != 0) {
            return 1;
        }
        p0 += 8;
    }
    return 0;
}



extern void (*D_801C49BC[])(void);

void func_80184AA8(void *a0) {
    D_801C49BC[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80184AE4(void *a0) {
        *(short *)((char *)a0 + 0x2) = 1;
        *(int *)((char *)a0 + 0x1c) = 2;
        *(unsigned char *)((char *)a0 + 0xfc) = 1;
        *(unsigned char *)((char *)a0 + 0xfe) = 2;
        *(unsigned char *)((char *)a0 + 0xfd) = 0;
        *(unsigned char *)((char *)a0 + 0xff) = 4;
        *(short *)((char *)a0 + 0xdc) = 0;
    }


extern s32 func_8012BEE8(s32 a0);
extern void func_80184B70(s32 a0, u8 *a1);

void func_80184B18(void *a0) {
    s32 s0 = (s32)a0;

    if (func_8012BEE8(s0) != 0) {
        func_80184B70(0, (u8 *)(s0 + 0xFD));
        func_80184B70(1, (u8 *)(s0 + 0xFE));
        func_80184B70(2, (u8 *)(s0 + 0xFF));
        *(s32 *)(s0 + 0x1C) = 2;
    }
}


extern u32 D_801C4770[];
extern u32 D_801C499C[];
extern u32 D_801C49B4;

void func_80184B70(s32 a0, u8 *a1) {
    u8 idx;
    u32 *dst;

    idx = *a1;
    if (idx >= 7) {
        *a1 = 0;
    }

    a0 <<= 6;
    idx = *a1;
    dst = (u32 *)((u8 *)D_801C4770 + a0);
    *dst = D_801C499C[idx];

    idx = *a1;
    dst++;
    if (idx - 1 < 0) {
        *dst = D_801C49B4;
    } else {
        *dst = D_801C499C[idx - 1];
    }

    (*a1)++;
}



extern void (*D_801C49F0[])(void);

void func_80184C0C(void *a0) {
    D_801C49F0[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_801C49C4[];
extern s32 D_801C49D0[];
extern s32 D_801C49E8[];
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8012EC04(s32 param_1, s32 param_2, s32 *param_3);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_80184C48(void *a0)
{
    s32 buf[8];
    u16 out[4];
    register s32 zr __asm__("$0");
    register s32 v0 __asm__("$4");

    v0 = ((s32 (*)(void))func_8012C1B8)() + zr;
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, D_801C49C4[*(u16 *)((s32)a0 + 0x70) & 0xF]);

    *(s32 *)((s32)a0 + 0x1C) = 8;
    *(u16 *)((s32)a0 + 0x2) += 1;

    func_8012EC04(*(s32 *)((s32)a0 + 0x64), D_801C49D0[*(u16 *)((s32)a0 + 0x70) & 0xF], buf);
    ((void (*)(s32 *, s32, u16 *))func_8012F14C)(buf, (s32)D_801C49E8, out);

    *(u16 *)((s32)a0 + 0x6) = out[0];
    *(u16 *)((s32)a0 + 0xA) = out[1];
    *(u16 *)((s32)a0 + 0xE) = out[2];

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
}


extern s32 rand(void);
extern s32 func_8012BEE8(s32 a0);

extern s32 D_801C49DC[];

void func_80184D34(s32 a0) {
    s32 *p;
    s32 s0;
    s32 r;
    u16 h;

    if (func_8012BEE8(a0) == 0) {
        return;
    }
    s0 = a0;
    *(u16 *)(s0 + 0x2) += 1;
    r = rand();
    h = *(u16 *)(s0 + 0x70);
    p = D_801C49DC;
    *(s32 *)(s0 + 0x48) = p[h & 0xF] + r % 1024;
    *(s32 *)(s0 + 0x1C) = 0x100;
    *(s32 *)(s0 + 0xE0) = rand();
}


#include "common.h"

extern s32 func_80047948(s32 a0);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012CBF4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);

void func_80184DC8(void *a0)
{
    s32 vec[3];
    s16 out[6];
    s16 t5;

    if ((*(u16 *)((s32)a0 + 0x70) & 0xF) == 2) {
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) -= 0x10;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) < -0x400) {
            *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = -0x400;
        }
    } else {
        vec[0] = func_80047948((*(s32 *)((s32)a0 + 0xE0) << 6) & 0xFC0) << 8;
        vec[1] = 0;
        vec[2] = 0;
        func_800484EC(*(s32 *)((s32)a0 + 0x20) + 0x34, (s32)vec, (s32)out);
        *(s16 *)((s32)a0 + 0x50) = out[1];
        t5 = out[5];
        *(s32 *)((s32)a0 + 0xE0) = *(s32 *)((s32)a0 + 0xE0) + 1;
        *(s16 *)((s32)a0 + 0x54) = t5;
    }

    if (((s32 (*)(s32))func_8012CBF4)((s32)a0) != 0) {
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        *(s16 *)((s32)a0 + 0x2) += 1;
    } else if (func_8012BEE8((s32)a0) != 0) {
        func_8012C218(a0);
    }
}



extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);

void func_80184ED0(s32 param_1)
{
    s32 iVar3;
    s32 uVar1;
    s32 sVar2;

    if (*(u16 *)(param_1 + 0x34) == 0) {
        if ((*(u16 *)(param_1 + 0x70) & 0xF) == 2) {
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
                *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + -0x80;
            if (*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) < -0x400) {
                *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = -0x400;
            }
        }
        iVar3 = func_8012BEE8(param_1);
        if (iVar3 != 0) {
            *(s32 *)(param_1 + 0x1C) = 8;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) =
                *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) | 0x10;
        }
    } else {
        iVar3 = func_8012BEE8(param_1);
        if (iVar3 != 0) {
            ((void (*)(s32))func_8012C218)(param_1);
        } else {
            uVar1 = func_8004787C((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            iVar3 = *(s32 *)(param_1 + 0x20);
            *(s16 *)(iVar3 + 0x1C) = uVar1;
            *(s16 *)(iVar3 + 0x18) = uVar1;
            sVar2 = func_80047948((*(s32 *)(param_1 + 0x1C) << 10) >> 3);
            *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1A) = sVar2 * 8 + 0x1000;
        }
    }
}


extern s32 func_80017758(void *a0, void *a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012B414(int a0);
extern void func_8012C218(void *a0);
    typedef struct { s16 vx; u16 vy; s16 vz, pad; } SVec_8017F67C_80184FF0;
typedef struct { u8 d[4]; } Blk4_8017CE90_8017F32C_80184FF0;
#define SRM_8018E8A0(r0) __asm__ volatile (          \
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
#define STM_8018E8A0(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

typedef struct { s16 vx, vy, vz, pad; } SVec8_8018E8A0_80184FF0;          /* 0x08 */
typedef struct { s32 vx, vy, vz, pad; } Vec16_8018E8A0_80184FF0;          /* 0x10 */
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } Mtx_8018E8A0_80184FF0; /* 0x20 */
typedef struct { s16 f[0x86]; } Cnt_8018E8A0_80184FF0;
typedef struct {
    SVec8_8018E8A0_80184FF0 v[4];   /* 0x00 */
    u32            c[4];   /* 0x20 */
    s32            code;   /* 0x30 */
    s32            pad;    /* 0x34 */
} Prim_8018E8A0_80184FF0;           /* 0x38 */

void func_80184FF0(void *a0)
{

    extern u32 D_801C499C[];
    extern u8 D_801C4A00[];
    Vec16_8018E8A0_80184FF0  mv;      /* sp+0x10 */
    Prim_8018E8A0_80184FF0   prim;    /* sp+0x20 */
    Mtx_8018E8A0_80184FF0    mtx;     /* sp+0x58 */
    SVec8_8018E8A0_80184FF0  rot;     /* sp+0x78 */
    s32             flag;    /* sp+0x80 */
    s32            *p;
    s32            *q;
    s32            *zb;
    SVec8_8018E8A0_80184FF0 *src;
    SVec8_8018E8A0_80184FF0 *dst;
    register s32 d __asm__("$4");
    s32 i, j, k, base, ang, t;
    u32 col;

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += 0x40;
    func_8012B414((s32)a0);

    mv.vz  = -0x40000;
    rot.vz = 0;
    col = D_801C499C[(*(u16 *)((s32)a0 + 0x10A))++ & 7];
    prim.code = 0x50000000;
    *(u32 *)((s32)&prim + 0x20) = col;
    *(u32 *)((s32)&prim + 0x24) = col;
    *(u32 *)((s32)&prim + 0x28) = col;
    *(u32 *)((s32)&prim + 0x2C) = col;

    p = (s32 *)((s32)a0 + 0xCC);
    for (i = 0, k = 0; i < ((Cnt_8018E8A0_80184FF0 *)a0)->f[0x84]; i++, k++, p += 3) {
        zb = (s32 *)((s32)a0 + 0xD4);
        { register s32 c1 __asm__("$2"); register s32 c2 __asm__("$3");
          c1 = *(s32 *)((s32)a0 + 0x1C); c2 = i * 4; d = c1 - c2; }
        if (d > 0x40) {
            if (i == 4) {
                func_8012C218(a0);
                return;
            }
            continue;
        }
        base = d << 6;
        ang = base & 0xFFF;
        flag = (func_8004787C(ang) << 4) >> 12;

        switch (*(s16 *)((s32)a0 + 0x70)) {
        case 0:
            t = ang;
            goto horiz;
        case 1:
            t = base + 0x800;
            t &= 0xFC0;
        horiz:
            mv.vy = (func_80047948(t) << 4) * flag;
            mv.vx = 0;
            rot.vx = -ratan2(mv.vy, mv.vz);
            rot.vy = 0;
            break;
        case 2:
            t = ang;
            goto vert;
        case 3:
            t = base + 0x800;
            t &= 0xFC0;
        vert:
            mv.vx = (func_80047948(t) << 4) * flag;
            mv.vy = 0;
            rot.vx = 0;
            rot.vy = ratan2(-mv.vz, mv.vx) - 0x400;
            break;
        }
        ((void (*)(void *, void *))func_80049CAC)(&rot, &mtx);

        q = zb + k * 3;
        p[0] += mv.vx;
        q[-1] += mv.vy;
        q[0] += mv.vz;
        mtx.t[0] = ((s16 *)p)[1];
        mtx.t[1] = ((s16 *)q)[-1];
        mtx.t[2] = ((s16 *)q)[1];

        src = (SVec8_8018E8A0_80184FF0 *)(D_801C4A00 +
              ((s32)(s16)*(u16 *)((s32)a0 + 0x70) / 2) * 0x20);
        dst = prim.v;

        SRM_8018E8A0(&mtx);
        STM_8018E8A0(&mtx);

        for (j = 0; j < 4; j++, src++, dst++) {
            RotTransSV(src, dst, &flag);
        }
        func_80017758(&prim, (void *)(*(s32 *)((s32)a0 + 0x20) + 0x34));
    }

    *(s32 *)((s32)a0 + 0x1C) += 1;
    if ((*(s32 *)((s32)a0 + 0x1C) & 3) == 0) {
        if (((Cnt_8018E8A0_80184FF0 *)a0)->f[0x84] < 5) {
            ((Cnt_8018E8A0_80184FF0 *)a0)->f[0x84] = ((Cnt_8018E8A0_80184FF0 *)a0)->f[0x84] + 1;
        }
    }
}



extern void (*D_801C4A40[])(void);

void func_8018533C(void *a0) {
    D_801C4A40[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);

void func_80185378(void *a0)
{
    s32 ret;

    ret = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = ret;
    if (ret == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(ret, 0);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
    func_8012B2CC((s32)a0);
    *(u16 *)((s32)a0 + 0x108) = 1;
    *(u16 *)((s32)a0 + 0x2) += 1;
}



extern void (*D_801C89CC[])(void);

void func_801853F8(void *a0) {
    D_801C89CC[*(u16 *)((s32)a0 + 0x2)]();
}




/* Declarations conform VERBATIM to the ones already present in
 * src/ov_SC03_014/ov_SC03_014_jr_801848E4.c (lines 58, 2524, 2527, 3139,
 * 3222, 3244, 3245).  Type mismatches are resolved by casting AT THE USE. */
extern s32 func_8012C354(s32 a0, s32 a1);
extern s32 func_80029178(s32 arg);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012CAE4(void *a0);
extern void func_8012A828(s32 a0, void *a1);
/* not declared anywhere in the TU */
extern void func_80185AE0(void);

void func_80185434(void *a0) {

    extern s32 D_801C8724[];
    extern u8 D_801C86BC[];
    extern u8 D_80187B3C[];
    s32 res1, res2, arr_elem;
    void *ptr;
    u16 idx;
    s16 val;

    res1 = func_8012C354((s32)a0, (s32)D_801C86BC);
    if (res1 == 0) {
        return;
    }

    ptr = *(void **)((s32)a0 + 0xDC);
    idx = *(u16 *)((s32)ptr + 0xA);
    arr_elem = D_801C8724[idx];

    res1 = func_80029178(arr_elem);

    if ((res1 & 0xFF) == 0) {
        res2 = func_801788B8((s32)a0, (s32)func_80185AE0);
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
        func_8012A828((s32)a0, D_80187B3C);
        *(u16 *)((s32)a0 + 0x2) = 1;
    }
}




s32 func_80185508(void *a0) {
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


void func_80185530(void) {
}


/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_80185538(void *a0) {

    extern s32 D_801C8908;
    extern s32 D_801C88F4;
    extern s32 D_801C88F0;
    extern s32 D_801C8988;
    extern s32 D_801C891C;
    extern s32 D_801C87E8[];
    extern s32 D_801C886C[];
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801C8908 = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801C88F0 = 0;
                D_801C88F4 = D_801C886C[v0];
            } else {
                D_801C88F4 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801C886C[v0], 1);
                D_801C88F0 = 2;
            }
        } else {
            D_801C8908 = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801C88F0 = 0;
            D_801C88F4 = D_801C87E8[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801C891C);
    } else {
        p = &D_801C8988;
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
extern s32 func_80185888(void);

void func_80185684(void *arg0) {

    extern s32 D_801C8724[];
    extern void func_8002AC00(s32 arg0); /* not declared anywhere in the TU */
    s32 ptr;

    ptr = *(s32 *)((s32)arg0 + 0xDC);

    if (func_801789AC((s32)arg0) != 0) {
        ((void (*)(void *))func_80178D18)(arg0);

        if ((u8)func_80029178(D_801C8724[*(u16 *)(ptr + 0xA)]) != 0) {
            if (D_801C8724[*(u16 *)(ptr + 0xA)] == 0x54) {
                func_80029514(0x5A);
                func_80029124(0xEA, 1);
            }

            if ((*(u16 *)(ptr + 0x8) & 0x4000) != 0) {
                if ((u8)func_80029178(0x1D) != 0) {
                    func_80145EE8(0);
                }
            }

            if (func_80185888() == 1) {
                func_8002AC00(0x26);
            }

            *(u16 *)((s32)arg0 + 0x70) &= 0x8000;
            func_8012C218(*(void **)((s32)arg0 + 0xCC));
        }

        *(u16 *)((s32)arg0 + 0x2) = 2;
    }
}



extern void func_8012C218(void *a0);
    s32 func_801857A4(void * arg0)
    {
        *(short *)((char *)arg0 + 0x2) = 2;
        ((void (*)(s32 *))func_8012C218)(*(s32 **)((char *)arg0 + 0xcc));
    }


void func_801857D0(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 1;
    }


void func_801857E0(void *a0) {
        *(short *)(*(int *)((char *)a0 + 0x6c) + 0xfe) = 2;
    }




extern void func_80029124(s32, s32);

void func_801857F0(void *a0) {

    extern s32 D_801C8724[];
    u16 idx = *(u16 *)(*(s32 *)(a0 + 0xDC) + 0xA);
    func_80029124(D_801C8724[idx], 1);
}



extern s32 D_80126B58;
extern void func_8014ADA8(s32 a0, s32 a1);

void func_80185830(void * arg0) {
    s32 temp_v0;

    temp_v0 = *(s32 *)((s32)arg0 + 0xdc);
    ((void (*)(s32 *, s32))func_8014ADA8)((s32 *)&D_80126B58, *(u16 *)(temp_v0 + 0xc));
}


extern s16 func_80174764(void);
s32 func_80185864(void) {
    return ((s32 (*)(void))func_80174764)() == 1;
}




extern s32 func_80029178(s32 arg);

s32 func_80185888(void) {

    extern s32 D_801C8724[];
    s32 i;

    for (i = 0; i < 0x26; i++) {
        if ((u8)func_80029178(D_801C8724[i]) == 0) {
            return 0;
        }
    }
    return 1;
}



extern void (*D_801C89F4[])(void);

void func_801858EC(void *a0) {
    D_801C89F4[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_80185928(void *a0) {

    extern u8 D_801C86F0[];
    extern u8 D_801C90B4[];
    extern u8 D_801C8E94[];
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801C86F0) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        func_8012A828((s32)a0, D_801C90B4);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        func_8012A828((s32)a0, D_801C8E94);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}




extern void func_8012C218(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801859B0(void *a0) {

    extern u8 D_801C8EA4[];
    extern u8 D_801C8FAC[];
    s16 mode;

    if (*(s16 *)((s32)a0 + 0xFC) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        ((void (*)(void))func_8012C218)();
        return;
    }

    mode = *(s16 *)((s32)a0 + 0xFE);
    if (mode == 1) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801C8EA4);
        *(s16 *)((s32)a0 + 0x5C) = 0;
        func_8002D4C8(0x5BF, 0);
    } else if (mode == 2) {
        *(s16 *)((s32)a0 + 0x2) = 2;
        *(s32 *)((s32)a0 + 0x1C) = 0x20;
        func_8012A828((s32)a0, D_801C8FAC);
        *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    }
}



/* func_80185A70 — guarded state-kick: if the s16 at 0x98 is clear, set the
 * state word at 0x02 to 1, hand the entity to func_8012A828 with one of two
 * script tables selected by the s16 flag at 0xFE (== 1 -> D_801C90B4, else
 * D_801C8E94), then clear that flag.
 *
 * §71 sibling-first: func_8018A06C (same TU, 0x148 bytes earlier) is the same
 * two-arm `func_8012A828(entity, D_801C90B4 / D_801C8E94)` selector and pins
 * the widths: `lh` at 0x98/0xFE, `sh` at 0x02.
 */

extern void func_8012A828(s32 a0, void *a1);

void func_80185A70(void *a0) {

    extern u8 D_801C90B4[];
    extern u8 D_801C8E94[];
    if (*(s16 *)((s32)a0 + 0x98) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        if (*(s16 *)((s32)a0 + 0xFE) == 1) {
            func_8012A828((s32)a0, D_801C90B4);
        } else {
            func_8012A828((s32)a0, D_801C8E94);
        }
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }
}


extern s32 *D_80126B78;
extern u8 D_801C89E4[];
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

s32 aF8018A224() __asm__("func_80185AE0");

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

    RotTransSV(D_801C89E4, sv0, &flag);
    RotTransSV(D_801C89E4 + 8, sv1, &flag);

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


extern s32 D_801C93A8[];
extern s32 func_8012C044(s32 a0);
extern void func_80187050(void*);

void func_80185BD8(s32 a0) {
    s32 *s0 = (s32 *)a0;
    u32 v0;
    u32 (*func_ptr)(void);

    v0 = *(u16 *)((u8 *)s0 + 2);
    v0 = v0 * 4;
    func_ptr = (u32 (*)(void))D_801C93A8[v0 / 4];
    func_ptr();

    v0 = *(u16 *)s0;
    if (v0 == 0) {
        return;
    }

    v0 = func_8012C044((s32)s0);
    if (v0 != 1) {
        return;
    }
    ((void (*)(s32))func_80187050)((s32)s0);
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80185C4C);

#include "common.h"

extern s32 rand(void);
extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern void func_80186ECC(s32 a0, s32 a1);

extern s32 D_801D98C8;
extern s32 D_801C9124[];
extern s32 D_801CA0A0;

void func_80185D08(s32 a0) {
    *(s16 *)(a0 + 2) = 2;
    func_80132288(&D_801D98C8, D_801C9124, D_801CA0A0);
    *(s32 *)(a0 + 0x1C) = (rand() % 31) + 30;
    func_80186ECC(a0, 1);
}


extern s32 D_801D98C8;
extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8013240C(s32 a0);

void func_80185D9C(s32 a0) {
    if (func_8012BCCC(a0) < 0x4001) {
        *(s16 *)(a0 + 2) = 7;
        return;
    }
    if (func_8012BEE8(a0) != 0) {
        *(s16 *)(a0 + 2) = 5;
    }
    func_8013240C((s32)&D_801D98C8);
}


#include "common.h"

extern s32 rand(void);
extern void func_80186ECC(s32 a0, s32 a1);
extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern s32 func_8018723C(void *a0);

extern s32 D_801D98C8;
extern s32 D_801C9124[];
extern s32 D_801C913C;
extern s32 D_801CA0A0;

void func_80185DFC(void *a0) {
    register u8 *s0 __asm__("$16") = (u8 *)a0;
    s32 v1;

    *(s16 *)(s0 + 0x2) = 4;
    func_80186ECC((s32)s0, 1);

    v1 = (rand() & 1) ? 1 : -1;

    *(s16 *)(s0 + 0xE0) = v1;
    if (*(s16 *)(s0 + 0xEA) != 0) {
        *(s32 *)(s0 + 0x1C) = (rand() % 31) + 30;
        func_80132288(&D_801D98C8, D_801C9124, D_801CA0A0);
    } else {
        *(s32 *)(s0 + 0x1C) = (rand() % 31) + 15;
        func_80132288(&D_801D98C8, &D_801C913C, D_801CA0A0);
        if (func_8018723C(s0) == 1) {
            *(s16 *)(s0 + 0xE8) = 0;
        } else {
            *(s16 *)(s0 + 0xE8) = 1;
        }
    }
}


extern s32 D_801D98C8;

extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8013240C(s32 a0);
extern s32  func_80186DD4(s32 a0);

void func_80185F38(s32 arg0) {
    s32 v0;
    s32 v1;

    v0 = *(s16 *)(arg0 + 0xE0);
    v1 = *(s32 *)(arg0 + 0x20);
    *(u16 *)(v1 + 0x12) += v0 * 34;

    if (*(s16 *)(arg0 + 0xEA) == 0) {
        func_8012B178(arg0, 0xFFFE0000);
        if (func_80186DD4(arg0) == -1) {
            return;
        }
    }
    if (func_8012BCCC(arg0) < 0x4001) {
        *(s16 *)(arg0 + 2) = 7;
        return;
    }
    if (func_8012BEE8(arg0) != 0) {
        *(s16 *)(arg0 + 2) = 5;
    }
    func_8013240C((s32)&D_801D98C8);
}


extern s32 rand(void);
extern void func_8012B23C(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_80186ECC(s32 a0, s32 a1);
extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern s32 func_8018723C(void *a0);

extern s32 D_801D98C8;
extern s32 D_801C913C;
extern s32 D_801CA0A0;

void func_80185FE8(void *a0) {
    register u8 *s0 __asm__("$16") = (u8 *)a0;
    s32 v0;
    s32 *ptr;

    *(s16 *)(s0 + 0x2) = 6;
    func_8012B23C(s0);
    func_8012B178(s0, (s32)0xFFFE0000);
    v0 = rand();
    *(s32 *)(s0 + 0x1C) = v0 % 61 + 90;
    func_80186ECC((s32)s0, 1);
    ptr = &D_801D98C8;
    *(s16 *)(s0 + 0xE4) = 0;
    if (*ptr != (s32)&D_801C913C) {
        func_80132288(ptr, &D_801C913C, D_801CA0A0);
    }
    if (func_8018723C(s0) == 1) {
        *(s16 *)(s0 + 0xE8) = 0;
    } else {
        *(s16 *)(s0 + 0xE8) = 1;
    }
}


#include "common.h"

extern u8 D_80078EAE;
extern s32 D_801C913C;
extern s32 D_801C915C;
extern s32 D_801C931C;   /* VECTOR.z at 0x801C9314 + 8 */
extern s32 D_801CA0A0;
extern s32 D_801D98C8;

extern s32  func_80047D3C(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32  func_8012BEE8(s32 a0);
extern void func_80132288(int *param_1, int *param_2, int param_3);
extern void func_8013240C(s32 a0);
extern s32  func_80186DD4(s32 a0);
extern void func_80186ECC(s32 a0, s32 a1);
extern void func_80186F60(s32 a0);
extern s32  func_801870B8(s32 a0);
extern s32  func_80187118(s32 a0, s32 a1);

void func_801860C0(s32 obj) {
    s32 d;
    s32 p;
    s32 r;

    d = func_8012BCCC(obj);
    if (d <= 0x4000) {
        *(s16 *)(obj + 0x2) = 7;
        return;
    }
    if (D_80078EAE == 0 && d <= 0x8000 && *(s16 *)(obj + 0xE4) != 0) {
        s32 *vz = &D_801C931C;

        *vz = -(func_80047D3C(func_8012BCCC(obj)) << 16);
        if (func_80187118(obj, (s32)((u8 *)vz - 8)) & 0x2000) {
            *(s16 *)(obj + 0x2) = 9;
            return;
        }
    }
    if (!func_801870B8(obj) || !func_8012BDBC(obj, 0x400)) {
        if (*(s16 *)(obj + 0xE4) != 0) {
            func_8012B178(obj, 0xFFFE0000);
            func_80186ECC(obj, 1);
            func_80132288((int *)&D_801D98C8, (int *)&D_801C913C, D_801CA0A0);
            *(s16 *)(obj + 0xE4) = 0;
        }
        if (func_8012BEE8(obj)) {
            func_80186F60(obj);
            return;
        }
    } else {
        r = func_8012B8E4(obj, 4);
        p = *(s32 *)(obj + 0x20);
        *(u16 *)(p + 0x12) += r;
        func_8012B178(obj, 0xFFF80000);
        if (*(s16 *)(obj + 0xE4) == 0) {
            func_80186ECC(obj, 2);
            func_80132288((int *)&D_801D98C8, (int *)&D_801C915C, D_801CA0A0);
            *(s16 *)(obj + 0xE4) = 1;
        }
    }
    r = func_80186DD4(obj);
    if (r == 0) {
        if (*(s16 *)(obj + 0xE4) == 0 || *(s16 *)(obj + 0xEA) == 2) {
            *(s16 *)(obj + 0x2) = 3;
        }
    } else if (r == -1) {
        return;
    }
    func_8013240C((s32)&D_801D98C8);
}


extern s32 D_801C917C[];
extern s32 D_801CA0A0;
extern s32 D_801D98C8;
extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern void func_80186ECC(s32, s32);

void func_801862B8(s32 a0) {
    extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
    extern void func_80186ECC(s32 a0, s32 a1);
    extern s32 D_801D98C8;
    extern s32 D_801CA0A0;
    extern s32 D_801C917C[];
    s32 s0 = a0;

    *(s16 *)(s0 + 0x2) = 8;
    func_80132288(&D_801D98C8, D_801C917C, D_801CA0A0);
    *(s32 *)(s0 + 0x1C) = 0x28;
    func_80186ECC(s0, 2);
    *(s16 *)(s0 + 0xDE) = 0;
    *(s16 *)(s0 + 0xE6) = 0;
}


#include "common.h"

extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012BCCC(s32 a0);
extern void func_80186F60(s32 arg0);
extern void func_8013240C(s32 a0);

extern s32 D_801C9320[];
extern s32 D_801D98C8;

void func_80186320(s32 a0) {
    s32 v0;
    s32 v1;

    v0 = func_8012B8E4(a0, 3);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += v0;

    if (*(s32 *)(a0 + 0x1C) == 0x28) {
        func_8002D4C8(0x7F, 0);
    }
    if (*(s32 *)(a0 + 0x1C) == 5) {
        func_8002D4C8(0x524, 0);
    }
    if (*(s32 *)(a0 + 0x1C) < 0xB) {
        if (*(s16 *)(a0 + 0xDE) == 0) {
            func_8012D5E4(a0, (s32)D_801C9320, (s32)D_801C9320 + 8, 0x15);
            *(u16 *)(a0 + 0xDE) ^= 1;
        }
    }
    if (func_8012BEE8(a0) != 0) {
        v1 = func_8012BCCC(a0);
        if (v1 > 0x30000) {
            func_80186F60(a0);
            return;
        }
        if (v1 >= 0x4001) {
            *(s16 *)(a0 + 0x2) = 5;
            return;
        }
        *(s32 *)(a0 + 0x1C) = 0x28;
        *(u16 *)(a0 + 0xDE) = 0;
    }
    func_8013240C((s32)&D_801D98C8);
}


extern s32 D_801C91A4;
extern s32 D_801C931C;
extern s32 D_801C93DC;
extern s32 D_801CA0A0;
extern s32 D_801D98C8;
extern s32 func_8012B864(s32 a0);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern void func_80186ECC(s32, s32);

void func_80186448(s32 a0) {
    s32 s0 = a0;
    s16 ret864;
    s32 *tbl;

    *(s16 *)(s0 + 0x2) = 0xA;
    func_80132288((int *)&D_801D98C8, (int *)&D_801C91A4, D_801CA0A0);
    func_80186ECC(s0, 2);
    *(s16 *)(s0 + 0xDE) = 0;
    ret864 = func_8012B864(s0);
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = ret864;
    func_8012B2CC(s0);
    tbl = &D_801C93DC;
    *tbl = D_801C931C / 30;
    func_8012B23C(s0);
    func_8012B14C(s0, (s32)tbl - 8);
    *(s32 *)(s0 + 0x1C) = 0;
    *(s16 *)(s0 + 0x34) = 0;
}


#include "common.h"

extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_80131E00();
extern void func_8013240C(s32 a0);

extern s32 D_801C9320[];
extern s32 D_801D98C8;

void func_80186514(s32 param_1) {
    s32 ret;

    if (*(u16 *)(param_1 + 0x34) == 0) {
        if (*(s32 *)(param_1 + 0x1C) < 0xF) {
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) += 0x44;
        }

        if ((u32)(*(s32 *)(param_1 + 0x1C) - 0x15) < 0xA) {
            if (*(s16 *)(param_1 + 0xDE) == 0) {
                func_8012D5E4(param_1, (s32)((u8 *)D_801C9320), (s32)&((u8 *)D_801C9320)[8], 0x1F);
                *(u16 *)(param_1 + 0xDE) ^= 1;
            }
        }

        ret = func_8012CBCC(param_1);
        if ((ret & 0xFF) == 2) {
            ((void (*)(s32, s32))func_80131E00)(param_1, 0x12);
            return;
        } else {
            if (ret & 0x2000) {
                *(s32 *)(param_1 + 0x1C) = 0xF;
                *(u16 *)(param_1 + 0x34) += 1;
            }

            *(s32 *)(param_1 + 0x1C) += 1;
            if (*(s32 *)(param_1 + 0x1C) >= 0x28) {
                ((void (*)(s32, s32))func_80131E00)(param_1, 0xD);
            }
        }
    } else {
        if (func_8012BEE8(param_1) != 0) {
            *(s16 *)(param_1 + 0x2) = 1;
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) = 0;
        }
    }

    ((void (*)(s32))func_8013240C)((s32)&D_801D98C8);
}


extern void func_80186F9C(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801C9234;
extern u8 D_801C9268[];

void func_80186660(s32 arg0)
{
    func_80186F9C(arg0, &D_801C9234, 0);
    func_8012A828(arg0, D_801C9268);
}


extern void func_8013240C(s32 a0);
extern s32 D_801D98C8;

void func_801866A4(void) {
    ((void (*)(s32))func_8013240C)((s32)&D_801D98C8);
}


extern void func_80186F9C(s32 a0, s32 a1, s32 a2);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 D_801C9234;
extern u8 D_801C93E0[];
extern u8 D_801C93EC[];
extern u8 D_801C9268[];

void func_801866CC(s32 param_1) {
    s32 s0 = param_1;
    s32 v1;

    *(u8 *)(s0 + 0xC2) = 0;
    *(u8 *)(s0 + 0xC3) = 0;
    *(u16 *)(s0 + 0x98) = 0;
    func_80186F9C(s0, (s32)&D_801C9234, 0);
    v1 = *(u16 *)(s0 + 0x5E);
    if (v1 == 9 || v1 == 0x1C) {
        func_8012B14C(s0, (s32)D_801C93E0);
    } else {
        func_8012B14C(s0, (s32)D_801C93EC);
    }
    func_8012A828(s0, (void *)D_801C9268);
}


#include "common.h"

/* ov_SC03_029 :: func_80186758 (0x80186758, 183 ins)
 *
 * Actor state-machine tick. Shape is the wave-U twin ov_SC01_077:func_801824D0
 * (matched, 181 ins) crossed with the same-binary sibling
 * src/ov_SC03_029/ov_SC03_029_jr_8012ACE0.c::func_80131340 (matched) for the
 * *15/16 signed-div fixup and the func_8012CC64/func_80143B6C call-site casts.
 *
 * Object field map (offsets off the s32 actor pointer):
 *   0x10 s32 velocity X-ish     0x14 s32 (saved/restored around state 1)
 *   0x18 s32 velocity Z-ish     0x1C s32 frame counter
 *   0x20 s32 -> gfx block { ... 0x10 u16 alpha/flag, 0x12 s16 ... }
 *   0xC1 u8 (cleared on hand-off)   0xC2 u8 state   0xC3 u8 bitflags
 */

extern s32 func_8012DBD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8012CC64(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_8012CBF4(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_80131E00();
extern void func_8013240C(s32 a0);
extern void func_80186D90(s32 a0);

extern s32 D_801C92DC;
extern s32 D_801D98C8;

void func_80186758(s32 a0)
{
    /* 8 bytes of frame that the body never references: a declared aggregate local
     * gets assign_stack_local'd (var_size 8) and emits zero instructions (§193-I). */
    struct V8 {
        u16 vx, vy, vz, pad;
    };
    struct V8 sp10;
    s32 var_s1;
    s32 var_s2;

    var_s1 = 0;
    if (*(s32 *)(a0 + 0x10) != 0 || *(s32 *)(a0 + 0x18) != 0) {
        func_8012DBD0(a0, 0x50, *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800, 0x1D);
    }

    switch (*(u8 *)(a0 + 0xC2)) {
    case 0:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x29) {
            goto L9E8;
        }
        var_s1 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&D_801C92DC);
        if (var_s1 & 0x2000) {
            *(u8 *)(a0 + 0xC2) = 1;
            func_80143B6C(a0, 1);
            *(s32 *)(a0 + 0x14) = 0xFFF30000;
            *(s32 *)(a0 + 0x1C) = 0;
        }
        break;

    case 1:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) -= 0x100;
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x29) {
            goto L9E8;
        }
        var_s2 = *(s32 *)(a0 + 0x14);
        var_s1 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&D_801C92DC);
        if (var_s1 & 0x2000) {
            func_80143B6C(a0, 1);
            *(s32 *)(a0 + 0x14) = var_s2;
            *(u8 *)(a0 + 0xC2) = 2;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        } else if (var_s1 & 0x8000) {
            *(u8 *)(a0 + 0xC2) = 2;
            *(s32 *)(a0 + 0x1C) = 0;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
        break;

    case 2:
        /* *15/16 with the signed-division +0xF fixup (never >>4) */
        *(s32 *)(a0 + 0x10) = *(s32 *)(a0 + 0x10) * 15 / 16;
        *(s32 *)(a0 + 0x18) = *(s32 *)(a0 + 0x18) * 15 / 16;
        if (*(u8 *)(a0 + 0xC3) & 1) {
            var_s1 = ((s32 (*)(s32))func_8012CBA4)(a0);
            /* explicit goto pair: the target emits `bnez -> join ; j L9E8` */
            if (var_s1 & 0x2000) {
                goto L9AC;
            }
            goto L9E8;
        }
        var_s1 = ((s32 (*)(s32))func_8012CBF4)(a0);
        if (var_s1 & 0x2000) {
            *(u8 *)(a0 + 0xC3) |= 1;
        } else if (var_s1 & 0x8000) {
            *(s32 *)(a0 + 0x18) = 0;
            *(s32 *)(a0 + 0x10) = 0;
        }
    L9AC:
        *(s32 *)(a0 + 0x1C) += 1;
        if (*(s32 *)(a0 + 0x1C) < 0x11) {
            break;
        }
        if (!(var_s1 & 0x2000)) {
            goto L9E8;
        }
        *(u8 *)(a0 + 0xC1) = 0;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        func_80186D90(a0);
        return;
    }
    goto L9F0;

L9E8:
    func_80131E00(a0, 0xD);
L9F0:
    ((void (*)(s32))func_8013240C)((s32)&D_801D98C8);
    if ((var_s1 & 0xFF) == 2) {
        func_80131E00(a0, 0x12);
    }
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80186A34);

#include "common.h"

extern void func_8012CBA4(s32 a0);
extern void func_8012CC64(s32 a0, s32 a1);
extern s32 func_8012CBCC(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012B23C(s32 a0);
extern void func_80131E00();
extern void func_8013240C(s32 a0);
extern void func_80186D90(s32 a0);

extern s32 D_801C92DC;
extern s32 D_801D98C8;

void func_80186B4C(s32 a0) {
    s32 s0;
    s32 s1;
    s32 v0;
    s32 v1;
    s32 t;
    s32 p;
    s32 q;

    s0 = a0;
    v1 = *(u16 *)(s0 + 0x34);
    s1 = 0;

    switch (v1) {
    case 0:
        t = *(s32 *)(s0 + 0x1C) + 1;
        *(s32 *)(s0 + 0x1C) = t;
        if (t >= 0x29) {
            goto timeout;
        }
        q = *(s32 *)(s0 + 0x20);
        *(u16 *)(q + 0x10) -= 0x100;
        s1 = ((s32 (*)(s32, s32))func_8012CC64)(s0, (s32)&D_801C92DC);
        if (s1 & 0x2000) {
            *(s32 *)(s0 + 0x1C) = 0xF;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x10) = 0;
        }
        break;

    case 1:
        s1 = ((s32 (*)(s32))func_8012CBA4)(s0);
        if (!(s1 & 0x2000)) {
            *(u16 *)(s0 + 0x34) = 2;
            *(s32 *)(s0 + 0x1C) = 0;
            func_8012B23C(s0);
            break;
        }
        v0 = func_8012BEE8(s0);
        goto merge2;

    case 2:
        t = *(s32 *)(s0 + 0x1C) + 1;
        *(s32 *)(s0 + 0x1C) = t;
        if (t >= 0x29) {
timeout:
            func_80131E00(s0, 0xD);
            break;
        }
        s1 = ((s32 (*)(s32))func_8012CBCC)(s0);
        v0 = s1 & 0x2000;
merge2:
        if (v0) {
            p = *(s32 *)(s0 + 0x20);
            *(u8 *)(s0 + 0xC1) = 0;
            *(u16 *)(p + 0x10) = 0;
            *(s16 *)(s0 + 0x5E) = 0;
            func_80186D90(s0);
        }
        break;
    }

    ((void (*)(s32))func_8013240C)((s32)&D_801D98C8);
    if ((s1 & 0xFF) == 2) {
        func_80131E00(s0, 0x12);
    }
}


extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern void func_80186ECC(s32 a0, s32 a1);
extern s32 D_801D98C8;
extern s32 D_801C920C[];
extern s32 D_801CA0A0;

void func_80186CE4(s32 a0) {
    func_80132288(&D_801D98C8, &D_801C920C, D_801CA0A0);
    func_80186ECC(a0, 1);
}


extern void func_8013240C(s32 a0);
extern s32 D_801D98C8;

void func_80186D34(void) {
    ((void (*)(s32))func_8013240C)((s32)&D_801D98C8);
}




















extern void func_80186F9C(s32 arg0, s32 arg1, s32 arg2);
extern void func_8002D4C8(s32 a0, s32 a1);
void func_80186D5C(void)
{

    extern M2C_UNK D_801C9234;
  int new_var;
  func_80186F9C(new_var, (s32) (&D_801C9234), 0);
  new_var = 0xA74;
  func_8002D4C8(0xA74, 0);
 dummy_label_648936: ;
}


void func_80186D90(s32 a0) {
    extern u8 D_80187B3C[];
    *(s16 *)(a0 + 0x2) = 1;
    func_8012A828(a0, D_80187B3C);
    *(u16 *)(a0 + 0x5C) = 0xAA10;
    *(s16 *)(a0 + 0xEA) = 0;
}


#include "common.h"

extern void func_8012CBA4(s32 a0);
extern void func_80131E00();
extern s32 func_8012CBCC(s32 a0);
extern void func_8012ADE4(s32 a0);

s32 func_80186DD4(s32 a0) {
    s32 s0;
    s32 t;

    s0 = a0;
    if (*(s16 *)(s0 + 0xE8) == 0) {
        a0 = ((s32 (*)(s32))func_8012CBA4)(a0);
        if ((a0 & 0xFF) == 2) {
            func_80131E00(s0, 0x12);
            return -1;
        }
        if (!(a0 & 0x2000)) {
            func_8012ADE4(s0);
            *(s16 *)(s0 + 0xEA) = 2;
            return 0;
        }
        if (a0 & 0x4000) {
            func_8012ADE4(s0);
            *(s16 *)(s0 + 0xEA) = 1;
            return 0;
        }
        if (a0 & 0x8000) {
            *(s16 *)(s0 + 0xEA) = 1;
            return 0;
        }
        *(s16 *)(s0 + 0xEA) = 0;
        return 1;
    }

    a0 = func_8012CBCC(s0);
    if (!(a0 & 0x2000)) {
        t = *(u16 *)(s0 + 0xE8) + 1;
        *(u16 *)(s0 + 0xE8) = t;
        if ((s16)t >= 0x5A) {
            return -1;
        }
    }
    *(u16 *)(s0 + 0xE8) = 0;
    return 1;
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80186ECC);


extern s32 rand(void);
    void func_80186F60(s32 arg0) {
        if ((rand() & 1) != 0) {
            *(s16*)(arg0 + 0x2) = 0x1;
        } else {
            *(s16*)(arg0 + 0x2) = 0x3;
        }
    }


#include "common.h"

extern void func_8012B23C(s32 a0);
extern void func_80132288(s32 *param_1, s32 *param_2, s32 param_3);
extern void func_800183E0(s32 a0);

extern s32 D_801D98C8;
extern s32 D_801CA0A0;
extern s32 D_801CA248;

void func_80186F9C(s32 a0, s32 a1, s32 a2) {
    register s32 s1 __asm__("$17") = a0;
    register s32 s0 __asm__("$16");
    register s32 s2 __asm__("$18") = a2;
    s32 p;

    __asm__("" :: "r"(s1));
    s0 = a1;

    func_8012B23C(s1);
    func_80132288(&D_801D98C8, (s32 *)s0, D_801CA0A0);
    s0 = 1;
    if (*(u16 *)(s1 + 0xDC) & 2) {
        func_800183E0((s32)&D_801CA248);
        *(u16 *)(s1 + 0xDC) = s0;
    }
    *(u16 *)(s1 + 0x5C) &= 0xFFFE;
    *(s32 *)(s1 + 0x1C) = s2;
    *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) = (*(u16 *)(s1 + 0x62) + 0x800) & 0xFFF;
    p = *(s32 *)(s1 + 0x20);
    *(s16 *)(p + 0x14) = 0;
    *(s16 *)(p + 0x10) = 0;
}


extern void func_8012C218(void*);

void func_80187050(void *arg0) {
    int iVar1;
    if ((*(s16 *)((char *)arg0 + 0x70) & 0x8000) == 0) {
        iVar1 = *(int *)((char *)arg0 + 0x68);
        if ((iVar1 != 0) && ((*(s16 *)((char *)arg0 + 0x72) & 0x8000) != 0)) {
            *(unsigned short *)(iVar1 + 10) = *(unsigned short *)(iVar1 + 10) & 0x7FFF;
        }
    }
    func_8012C218(arg0);
}


extern void Square0(s32 *a0, s32 *a1);

s32 func_801870B8(s32 a0) {
    s32 sp10[4];

    sp10[0] = *(s16 *)((s32)a0 + 6) - *(s16 *)((s32)a0 + 0x88);
    sp10[1] = 0;
    sp10[2] = *(s16 *)((s32)a0 + 0xE) - *(s16 *)((s32)a0 + 0x8C);
    Square0(&sp10[0], &sp10[0]);
    return 0x18FFFF >= (sp10[0] + sp10[2]);
}


INCLUDE_ASM("asm/ov_SC03_029/nonmatchings/ov_SC03_029_jr_8017DC70", func_80187118);

s32 func_8018723C(void *a0) {
    short a[4];
    short b[4];
    s32 pa, pb;
    s32 r;
    a[0] = *(u16 *)((s32)a0 + 0x6);
    a[1] = *(u16 *)((s32)a0 + 0xA);
    a[2] = *(u16 *)((s32)a0 + 0xE);
    pa = (s32)a;
    pb = (s32)b;
    __builtin_memcpy((void *)pb, (void *)pa, 8);
    b[1] += 8;
    r = func_80133784(1, pa, pb) & 0x2000;
    return r != 0;
}



/* func_801872B4 — tiny matrix wrapper.
 * 0x20-byte local scratch matrix at sp+0x10 (frame 0x40 = 0x10 outgoing args
 * + 0x20 matrix + 0x10 for $s0/$s1/$s2/$ra).
 *   func_80013F3C(&m);            identity/init
 *   func_80187318((s16)a0, &m);   rotate by a *sign-extended halfword* angle
 *   ApplyMatrixSV(&m, a1, a2);
 * The `sll/sra 16` pair lands AFTER the first call (a0 lives in $s0 across it),
 * which is the cast-at-use-site form: an s32 parameter narrowed at the call.
 */

extern void func_80013F3C(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void func_80187318();

void func_801872B4(s32 a0, void *a1, void *a2) {
    s32 m[8];

    ((void (*)(void *))func_80013F3C)((void *)m);
    ((void (*)(s32, void *))func_80187318)((s16)a0, (void *)m);
    ApplyMatrixSV((void *)m, a1, a2);
}



void func_80187318(s32 param_1, s32 *param_2)
{
    s32 s0;
    s32 s1;
    s32 cos_val;
    s16 sin_val;
    s32 v1;
    s16 matrix_stack[16];

    s1 = (s32)param_2;
    s0 = param_1 & 0xFFF;

    cos_val = func_80187718(s0);
    sin_val = func_8018765C(s0);

    /* Build rotation matrix on stack */
    v1 = 0x7FF8;
    *(short *)((s32)matrix_stack + 0x04) = sin_val;
    *(short *)((s32)matrix_stack + 0x00) = cos_val;
    *(short *)((s32)matrix_stack + 0x02) = 0;
    *(short *)((s32)matrix_stack + 0x06) = 0;
    *(short *)((s32)matrix_stack + 0x08) = v1;
    *(short *)((s32)matrix_stack + 0x0A) = 0;
    *(short *)((s32)matrix_stack + 0x0C) = -sin_val;
    *(short *)((s32)matrix_stack + 0x0E) = 0;
    *(short *)((s32)matrix_stack + 0x10) = cos_val;

    __asm__ volatile (
        "lw $12, 0(%0);"
        "lw $13, 4(%0);"
        "ctc2 $12, $0;"
        "ctc2 $13, $1;"
        "lw $12, 8(%0);"
        "lw $13, 12(%0);"
        "lw $14, 16(%0);"
        "ctc2 $12, $2;"
        "ctc2 $13, $3;"
        "ctc2 $14, $4;"
        "addiu $2, $sp, 0x10;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0);"
        "addiu $2, $sp, 0x12;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu $2, %0, 0x2;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0($2);"
        "sh $13, 6($2);"
        "sh $14, 12($2);"
        "addiu $2, $sp, 0x14;"
        "lhu $12, 0($2);"
        "lhu $13, 6($2);"
        "lhu $14, 12($2);"
        "mtc2 $12, $9;"
        "mtc2 $13, $10;"
        "mtc2 $14, $11;"
        "nop;"
        "nop;"
        "mvmva 1, 0, 3, 3, 0;"
        "addiu %0, %0, 4;"
        "mfc2 $12, $9;"
        "mfc2 $13, $10;"
        "mfc2 $14, $11;"
        "sh $12, 0(%0);"
        "sh $13, 6(%0);"
        "sh $14, 12(%0)"
        : "=r"(s1)
        : "0"(s1)
        : "$12", "$13", "$14", "$2"
    );
}



void func_80187478(u16 *r, s16 *m) {
    s16 cx;
    s16 sx;
    s16 cy;
    s16 sy;
    s16 cz;
    s16 sz;
    s32 sxsy;
    s32 cxcz;
    s32 cxsz;

    cx = func_80187718(r[0] & 0xFFF);
    sx = func_8018765C(r[0] & 0xFFF);
    cy = func_80187718(r[1] & 0xFFF);
    sy = func_8018765C(r[1] & 0xFFF);
    cz = func_80187718(r[2] & 0xFFF);
    sz = func_8018765C(r[2] & 0xFFF);

    cxsz = (cx * sz) >> 15;
    cxcz = (cx * cz) >> 15;
    sxsy = (sx * sy) >> 15;

    m[0] = (cz * cy) >> 15;
    m[1] = ((sxsy * cz) >> 15) - cxsz;
    m[2] = ((cxcz * sy) >> 15) + ((sx * sz) >> 15);
    m[3] = (sz * cy) >> 15;
    m[4] = ((sxsy * sz) >> 15) + cxcz;
    m[5] = ((cxsz * sy) >> 15) - ((sx * cz) >> 15);
    m[6] = -sy;
    m[7] = (cy * sx) >> 15;
    m[8] = (cy * cx) >> 15;
}



/* func_8018765C — quadrant-folded sine lookup over a 0x400-entry u16 table.
 *
 * asm evidence:
 *   Q0 (a<0x400)          : lh   tbl[a]
 *   Q1 (a-0x400 < 0x400)  : lh   tbl[0x7FF - a]
 *   Q2 (a-0x800 < 0x400)  : lhu  tbl[a - 0x800], negu, sll/sra 16
 *   Q3 (a-0xC00 < 0x400)  : lhu  tbl[0xFFF - a],  negu, sll/sra 16
 *   else                  : NO value is produced at all (see below)
 *
 * The `lhu` + `negu` + 16-bit sign-extend in Q2/Q3 pins BOTH types:
 *   - the table element is UNSIGNED (zero-extending load feeding the negate), and
 *   - the result is truncated back to 16 bits => the function returns s16.
 * (An s16 table would give `lh`; an s32 return would drop the sll/sra pair.)
 *
 * Q2's base is D_801D517C == D_801D617C - 0x1000: gcc folded the `- 0x800`
 * element offset into the symbol addend and indexes with the raw parameter
 * (`sll $v0, $a0, 1`). Writing `tbl[a0 - 0x800]` reproduces that exactly.
 *
 * LOAD-BEARING: there is deliberately NO trailing `return 0;`.  The original
 * falls off the end of a non-void function, so the out-of-range path returns
 * whatever `$v0` happens to hold — which is the failing `sltiu` result, i.e. 0.
 * That is why the target's last test is `beqz $v0, .L8018BA04` + a bare `nop`
 * delay slot (gcc may not clobber $v0 on the taken edge) with no `move $v0,
 * $zero` anywhere.  Adding `return 0;` costs 2 instructions AND lets
 * find_cross_jump tail-merge the Q2/Q3 `negu; sll; sra` tails (cookbook §5a):
 * 45 ins / 19 mismatched instead of MATCH.
 */


s16 func_8018765C(u32 a0)
{

    extern u16 D_801D617C[];
    if (a0 < 0x400) {
        return D_801D617C[a0];
    }
    if (a0 - 0x400 < 0x400) {
        return D_801D617C[0x7FF - a0];
    }
    if (a0 - 0x800 < 0x400) {
        return -D_801D617C[a0 - 0x800];
    }
    if (a0 - 0xC00 < 0x400) {
        return -D_801D617C[0xFFF - a0];
    }
}



/* func_80187718 — quarter-table cosine lookup (sibling of func_8018B950, the sine).
 *
 * The four `lui/addu/l[h|hu] %lo(...)` bases in the target are all the SAME 0x400-entry
 * signed s16 quarter table at ((s16 *)D_801D617C); gcc folds the per-quadrant constant index
 * offset into the symbol:
 *   ((s16 *)D_801D617C)[a - 0x400]  ->  base ((s16 *)D_801D617C)-0x800 = D_801D597C, index a*2
 *   ((s16 *)D_801D617C)[a - 0xC00]  ->  base ((s16 *)D_801D617C)-0x1800 = D_801D497C, index a*2
 * so no extra externs are needed for D_801D597C / D_801D497C.
 *
 * Types: the positive quadrants return the `lh` value straight through (already
 * sign-extended, no sll/sra); the negative quadrants take an explicit (s16) cast on
 * the negation, which forces the truncate -> the return's sign-extend becomes the
 * `sll 16 / sra 16` pair, and combine downgrades those loads to `lhu`.  Writing the
 * arms as four flat `return`s (not one shared s16 local) keeps the extension OFF the
 * positive quadrants; cross-jump then merges the two `sll/sra` tails.
 *
 * The tail has NO `return 0`.  A trailing `return 0` costs an extra `move $v0,$zero`
 * block AND lets dbr steal `sll $v0,$a0,1` into the final beqz delay slot (target has
 * a `nop` there).  Falling off the end keeps `expand_function_end`'s `(use $v0)` live
 * over the epilogue, so the delay slot stays empty and the branch lands straight on
 * the shared `jr $ra` with the `sltiu` zero already in $v0 — which IS the 0 the
 * caller observes.  Same shape as the sibling func_8018B950.
 */


s32 func_80187718(u32 a0v)
{

    extern u16 D_801D617C[];
    if (a0v < 0x400) {
        return ((s16 *)D_801D617C)[0x3FF - a0v];
    }
    if (a0v - 0x400 < 0x400) {
        return (s16)-((s16 *)D_801D617C)[a0v - 0x400];
    }
    if (a0v - 0x800 < 0x400) {
        return (s16)-((s16 *)D_801D617C)[0xBFF - a0v];
    }
    if (a0v - 0xC00 < 0x400) {
        return ((s16 *)D_801D617C)[a0v - 0xC00];
    }
    /* no trailing `return 0`: gcc's end-of-function (use $v0) keeps the return
     * register live over the epilogue, so dbr cannot steal `sll $v0,$a0,1` into
     * the beqz delay slot, and the 0 the caller sees is the sltiu result. */
}





