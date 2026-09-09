#include "common.h"
#include "../shared/engine_prelude.h"


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
extern u8 D_8018AED8;
extern u8 D_8018AE48;
extern u8 D_8018AE24;
extern u8 D_8018AE00;
extern u8 D_8018AEB4;
extern u8 D_8018AE90;
extern u8 D_8018AE6C;
extern u8 D_8018ADDC;
extern void func_80145934(void);
extern u8 D_8018AF68;
extern u8 D_8018AF44;
extern u8 D_8018AF20;
extern u8 D_8018AEFC;
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
extern unsigned char D_8018A360[];
extern unsigned char D_8018A390[];
extern unsigned char D_8018A3E0[];
extern unsigned char D_8018A410[];
extern unsigned char D_8018A440[];
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
extern void (*D_8018A490[])(void *);
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
extern s32 D_8018A558[];
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
extern u8 D_8018A5E0[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018A5E8;
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
extern int D_801C5D38;
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
extern s32 D_801C5D3C;
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
extern s32 D_8018A618;
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
extern void (*D_8018A6C0[])(void);
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
extern void (*D_8018A6E4[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018A6D4;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018A6F8[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018A704[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018A714[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018A72C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018A71C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018A740[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018A75C[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018A74C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018A770[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018A784[])(void);
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
extern s32 D_8018A798;
extern void (*D_8018A7C0[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018A7A0;
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
extern int (*D_8018A80C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018A810[])(void);
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
extern unsigned short D_8018AC74[];
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
extern void (*D_8018AC84[])(void);
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
extern int D_801C5D70;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018ACAC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018AC8C;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018AC9C;
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
extern void (*D_8018ACEC[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018ACF4[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018ACC0;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018AD00[])(void);
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
extern u8 D_8018ACD0;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801C5D78;
extern s32 D_801C5D84;
extern s32 D_801C5D88;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018AD3C[])(s32 *);
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
extern s32 D_8018AD10[];
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
extern s32 D_801C5D80;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018AF8C[])(void);
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
extern char D_8018ADAC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018B030[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018B184[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018AFA0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018B18C[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018AFB0;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018AFD0;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018B194[])(void);
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
extern void (*D_8018B1BC[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018B1C8[])(void);
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
extern void (*D_8018B03C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018B26C;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018A350[];
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
extern unsigned char D_8018B280[];
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
extern s8 D_8018B2BC[];
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
extern u16 D_8018B304;
extern u16 D_8018B306;
extern u16 D_8018B308;
extern s32 D_8018B30C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018B314;
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
extern int D_8018B020;
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
extern unsigned int D_8018B398[];
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
extern void (*D_8018B448[])(void);
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
extern u16 D_8018B478[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018B4DC;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801C5D90[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018B500[])(void);
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
extern int D_801C5DE8[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018B548[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018B538;
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
extern char D_801C5444[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018B550[])(void);
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
extern void (*D_8018B5A4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern s32 D_8018B56C;
extern s16 D_8018B5A0;
extern s16 D_8018B59E;
extern s16 D_8018B59C;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018B5B0[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801C5E48;
extern u8 D_801C5E49;
extern u8 D_801C5E4A;
extern u8 D_801C5E4B;
extern u8 D_801C5E4C;
extern u8 D_801C5E4D;
extern u8 D_801C5E4E;
extern u8 D_801C5E4F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018B5C0[])(void);
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
extern s32 D_801C5E88;
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
extern void (*D_8018B604[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018B680[];
extern s32 D_8018B6A0[];
extern u8 D_8018B71C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018B73C[];
extern u8 D_8018B75C[];
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
extern void (*D_8018B7F8[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018B874[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801C5454;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018B880[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018B888[])(void);
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
extern void (*D_8018B950[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018B960[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018B970[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018B97C[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018B8DC[];
extern u8   D_8018B8F0[];
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
extern void (*D_8018B994[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018B99C[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018B9A4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018B9AC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018B9B4[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018B9BC[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018B9C4[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018BA78[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018BA80[])(void);
extern void func_80169F00(void *a0);
extern char D_8018BA30[];
extern char D_8018B9F0[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018BAB8[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018BAC4[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018BB0C[])(void);
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
extern void (*D_8018BB88[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801C61A8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018BB7C[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018BBC0[];
extern unsigned short D_8018BBC8[];
extern unsigned short D_8018BBD0[];
extern unsigned char D_801C61B0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801C61A8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018BBD8[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801C62E4;
extern M2C_UNK D_801C62E8;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801C6270;
extern void (*D_8018BC08[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801C62EC[];
extern u8 D_801C62F4[];
extern u8 D_801C62A4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018BC10[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018BC2C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018BC34[])(void);
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
extern void (*D_8018BC9C[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018BC40;
extern u8 D_8018BC4C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018BCD0[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018BCD8[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018BD2C[])(void);
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
extern u16 D_8018BD60[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018BD50[];
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
extern s32 D_8018BD7C;
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
extern void (*D_8018BDF4[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018BDFC[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018BE04[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018BE0C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018BE14[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018BE1C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018BE28[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018BE34[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018BE40[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018BE50[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018BE60[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018BE68[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018BE70[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018BE78[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018BE80[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018BE88[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018BE90[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018BE98[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018BEA0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018BEA8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018BEB0[])(void);
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
extern void (*D_8018BEB8[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018BEC0[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018BEC8[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018BED0[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018BED8[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018BEE0[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018BEE8[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018BEF0[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018BEF8[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018BF00[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018BF08[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018BF10[])(void);
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
extern void (*D_8018BF54[])(void);
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
extern M2C_UNK D_8018BF18;
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
extern void (*D_8018BF84[])(void);
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
extern void (*D_8018BFC0[])(void);
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
extern void (*D_8018C018[])();
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
extern void (*D_8018C028[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018C030[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018C198[])();
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
extern void (*D_8018C1A4[])();
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
extern M2C_UNK D_801C569C;
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
extern s16 D_801C7FB8;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801C6A28;
extern short D_801C802C;
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
extern s32 D_801C6E54;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801C6E7C;
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
extern s16 D_801C6E38;
extern s32 func_8017A3B0(void);
extern short D_801C6E74;
extern short D_801C6E70;
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
extern s16 D_801C6E3C;
extern u16 D_801C6EBC;
extern u16 D_801C6EBE;
extern u16 D_801C6EC0;
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
extern s16 D_801C6EB4;
extern s16 D_801C6EB6;
extern s16 D_801C6EB8;
extern s16 D_801C6EAC;
extern s16 D_801C6EAE;
extern s16 D_801C6EB0;
extern void func_8017B7A8(void);
extern s16 D_801C6ECC;
extern s16 D_801C6ECE;
extern s16 D_801C6ED0;
extern s16 D_801C6ED4;
extern s16 D_801C6ED6;
extern s16 D_801C6ED8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801C6EC4;
extern short D_801C6EC6;
extern short D_801C6EC8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801C6E5C;
extern SV4 D_801C6E64;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801C6E84[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801C6E80)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018C380[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void func_8017BF34(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8017BF08(void *a0, void *a1, s32 a2, s32 a3);
extern void (*D_8018C3E0[])(void);
extern void func_8017C114(void *a0);
/* ==== end §8b carried decl layer ==== */

/* func_8017C8D0 — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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

#include "../shared/ov/func_8017C8D0__t67f11bf2.h"



extern void (*D_8018C498[])(void);

void func_8017D7B0(void *a0) {
    D_8018C498[*(u8 *)((s32)a0 + 0x216)]();
}


extern void func_8014706C(void *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_80171990(u8 *a0);
void func_8017D7EC(s32 a0) {

    extern u8 D_8018C3E8;
    func_8014706C((void *)a0);
    func_80154274((s32 *)a0, (s32)&D_8018C3E8);
    func_80171990((u8 *)a0);
}


extern void func_801466F0(s32 a0, s32 a1, s32 a2, s32 a3, s32 sp5, s32 sp6, s32 sp7, s32 sp8);
extern void func_80147324(s32 a0);
extern s32 func_80171990(u8 *a0);

void func_8017D82C(s32 a0) {
    if (*(u16 *)(a0 + 0xB8) & 0x4000) {
        *(s32 *)(a0 + 0x44) |= 0x20000;
        func_801466F0(0x16, a0, 0, -0x80, -0x10, 0, 0, 0);
        func_80147324(0x7BC);
        func_80171990((u8 *)a0);
    }
}


extern s32 func_8014C088(s32 a0, s32 a1);
extern s32 func_8014CB58(void);
extern s32 func_80171990(u8 *a0);
extern void func_8014B5C4(s32 *a0, s32 a1, s32 a2);

void func_8017D8A8(s32 a0)
{
    if (func_8014C088(a0, 0x16) == 0)
    {
        *(s32 *)(a0 + 0x44) &= ~0x20000;
        func_8014B5C4((s32 *)a0, func_8014CB58() & 0xFF, 0x80);
        func_80171990((u8 *)a0);
    }
}


void func_8017D908(void) {
}

extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D910(void) {

    extern s32 D_8018C490(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018C490, 0x1000000);
}


















extern s32 D_80126D54;
extern s32 D_8018C490;
s32 func_8017D938(void)
{
  int new_var;
  new_var = 0xFFFFFFFF;
  new_var = (float) 0xFFFFFFFF;
  return ((u32) (D_80126D54 ^ ((s32) (&D_8018C490)))) == (1 & new_var);
}

    s32 func_8017D954(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s16 D_80126B0C;
        return D_80126B0C;
    }


    extern void (*D_8018C4E0[])(void);
    extern void func_80162D28(s32*);
    void func_8017D964(void *a0) {
        D_8018C4E0[*(u16 *)((s32)a0 + 0x2)]();
        if (*(s32 *)((s32)a0 + 0x20) != 0) {
            ((void (*)(void *))func_80162D28)(a0);
        }
    }



extern void func_8014659C(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_80149374(s32 a0, s32 a1);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80146CA0(void *a0);

void func_8017D9C4(s32 a0) {

    extern s32 D_80191BA8;
    extern s16 D_8018C4DC;
    extern s16 D_8018C4DA;
    extern s16 D_8018C4D8;
    s32 iVar1;
    s32 iVar2;

    iVar1 = *(s32 *)(a0 + 0x4C);
    iVar2 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(a0 + 0x20) = iVar2;
    if (iVar2 != 0) {
        func_8001C214(iVar2, (s32)&D_80191BA8);
        *(u16 *)(iVar2 + 0x10) = 0x800;
        *(u16 *)(a0 + 0x60) = 0;
        func_80149374(iVar1, a0 + 4);
        func_80146DE8((s32 *)a0, 0, 0xFFC00000, 0);
        D_8018C4DC = 0x80;
        D_8018C4DA = 0x80;
        D_8018C4D8 = 0x80;
        func_80146CA0((void *)a0);
        if (*(s32 *)(a0 + 0x50) == 0) {
            *(u16 *)(iVar2 + 0x2c) = *(u16 *)(iVar2 + 0x2c) | 0x10;
        }
    }
}


extern void func_8001C810(s32 a0, s32 a1);
extern void func_8013C9C4(void * arg0);
extern void func_801466B4(u16 a0, s32 a1, s32 a2, s32 a3, s32 arg5);
extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern void func_80162FC0(s32 *a0);
extern void func_8016325C(s32 a0, s32 a1, s32 a2, s32 a3);

void func_8017DA90(s32 a0) {
    extern u8 D_8018C4F0[];
    extern s32 D_80192200;
    extern s32 D_8018C4A8;

    s32 iVar1;
    s32 iVar2;
    s16 sVar1;

    iVar1 = *(s32 *)(a0 + 0x4c);
    iVar2 = *(s32 *)(a0 + 0x20);
    func_8016325C(a0, 0, 0x20000, 0);
    func_80162FC0((s32 *)a0);
    if ((*(s16 *)(a0 + 0x60) == 0) && (0 < *(s32 *)(a0 + 0x28))) {
        u16 uVar1;
        *(u16 *)(iVar2 + 0x10) = 0;
        uVar1 = *(u16 *)(a0 + 0x60);
        *(u16 *)(a0 + 0x60) = uVar1 + 1;
    }
    sVar1 = *(s16 *)(iVar1 + 0xA);
    if (sVar1 < *(s16 *)(a0 + 0xA)) {
        u16 uVar1;
        s32 uVar2;
        *(s16 *)(a0 + 0xA) = sVar1;
        func_8013C9C4(D_8018C4F0);
        *(u16 *)(a0 + 0x60) = *(u16 *)(iVar2 + 0x18);
        func_8001C810(iVar2, (s32)&D_80192200);
        *(s32 **)(iVar2 + 0x80) = &D_8018C4A8;
        *(u16 *)(iVar2 + 0x2c) = *(u16 *)(iVar2 + 0x2c) | 0xA0;
        *(u32 *)(iVar2 + 4) = *(u32 *)(iVar2 + 4) | 0x50000000;
        uVar1 = *(u16 *)(a0 + 0x60);
        *(u16 *)(iVar2 + 0x1c) = uVar1;
        *(u16 *)(iVar2 + 0x1a) = uVar1;
        *(u16 *)(iVar2 + 0x18) = uVar1;
        if (*(s32 *)(a0 + 0x50) == 0) {
            *(u16 *)(iVar2 + 0x2c) = *(u16 *)(iVar2 + 0x2c) | 0x10;
            func_801466B4(0x1B, a0, 0, 0, 1);
            func_801466B4(0x1B, a0, 1, 0, 1);
            func_801466B4(0x1B, a0, 2, 0, 1);
            func_801466B4(0x1B, a0, 3, 0, 1);
            uVar2 = 0x81D;
        } else {
            uVar2 = 0xC5E;
        }
        func_80147324(uVar2);
        func_80146CA0((void *)a0);
    } else if (*(s16 *)(a0 + 0x60) != 0) {
        s16 sVar2;
        sVar2 = *(u16 *)(iVar2 + 0x1c) + 0x100;
        *(s16 *)(iVar2 + 0x1c) = sVar2;
        *(s16 *)(iVar2 + 0x1a) = sVar2;
        *(s16 *)(iVar2 + 0x18) = sVar2;
    }
}


void func_8017DC5C(void) {
    extern s16 D_8018C4DC;
    extern s16 D_8018C4DA;
    extern s16 D_8018C4D8;
    extern void func_80146CA0(void *a0);
    s16 sVar1;

    sVar1 = D_8018C4DC + 8;
    D_8018C4DC = sVar1;
    D_8018C4DA = sVar1;
    D_8018C4D8 = sVar1;
    if (sVar1 >= 0x101) {
        ((void (*)(void))func_80146CA0)();
    }
}


extern s16 D_8018C4D8;
extern s16 D_8018C4DA;
extern s16 D_8018C4DC;
extern void func_80162CCC(void);

void func_8017DCB8(void) {
    extern s16 D_8018C4DC;
    extern s16 D_8018C4DA;
    extern s16 D_8018C4D8;
    s16 sVar1;

    sVar1 = D_8018C4DC - 8;
    D_8018C4DC = sVar1;
    D_8018C4DA = sVar1;
    D_8018C4D8 = sVar1;
    if (sVar1 < -0x80) {
        func_80162CCC();
    }
}


    extern void func_8017DFAC();
    extern void (*D_8018C524[])(int);
    extern void func_80162D28(s32*);
    void func_8017DD14(int param_1)
    {
        func_8017DFAC();
        D_8018C524[*(unsigned short *)(param_1 + 2)](param_1);
        if (*(s32 *)(param_1 + 0x20) != 0) {
            ((void (*)(int))func_80162D28)(param_1);
        }
    }


extern void func_8014659C(void);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern void func_80162CCC(void);
void func_8017DD78(int param_1) {

    extern u16 D_800DF2E0;
    extern s32 D_8018C4A8;
    extern s32 D_8018C504[];
    s32 iVar1;
    iVar1 = ((s32 (*)(void))func_8014659C)();
    *(s32 *)(param_1 + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32, void *))func_8001C810)(iVar1, &D_800DF2E0);
        *(s32 **)(iVar1 + 0x80) = &D_8018C4A8;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        *(u16 *)(iVar1 + 0x2c) = *(u16 *)(iVar1 + 0x2c) | 0xb0;
        *(s32 *)(param_1 + 0x58) = (s32)&D_8018C504[*(s32 *)(param_1 + 0x50) * 2];
        *(u16 *)(iVar1 + 0x1c) = 0;
        *(u16 *)(iVar1 + 0x1a) = 0;
        *(u16 *)(iVar1 + 0x18) = 0;
        ((void (*)(s32))func_80146CA0)(param_1);
    } else {
        ((void (*)(s32))func_80162CCC)(param_1);
    }
}



/* func_8017DE28 — per-frame spin + clamp handler (ov_SC03_014, reach x8).
 *
 * Byte-proven shape notes:
 *  - obj->0x1C/0x1A are read u16 / written s16 (this file's house idiom), so
 *    "+= 0x800" is lhu+addiu+sh and the compare re-derives the s16 (sll/sra).
 *  - each clamp needs TWO pseudos: `limN` (s32, the compare operand — it must be
 *    SINGLE-BLOCK so local-alloc TIES the `slt` dest into it, giving the target's
 *    `slt $v1,$v1,$v0`) and `lvN` (s16, the store value — it crosses the branch,
 *    so it is a GLOBAL allocno, global.c never coalesces, and the target's
 *    `addu $aN,$v1,$zero` copy survives).  Sharing one variable per role across
 *    the two blocks makes both global, kills the tie and loses both copies
 *    (regalloc map K8).  `lvN` must be s16: an s32 copy folds away (-2 ins).
 *  - `o` (9 refs / 28 insns, density 9642) out-prioritises lv1 (3 refs / 7,
 *    4285) in global.c's allocno_compare and grabs $a0 first; the target has
 *    $a0 = lv, $a1 = o.  The zero-byte read-modify-write asm below gives lv1 two
 *    extra refs (5 refs / 8 insns -> 12500) so it allocates first and takes $a0,
 *    pushing `o` to $a1.  It emits nothing.  (Byte-identical alternatives:
 *    `register s32 o __asm__("$5");`, or pinning lv1/lv2 to "$4".)
 *    NB gcc-2.7.2 rejects "+r" constraints — use "=r"(x) : "0"(x).
 *  - the 0x10 phantom frame slot is an address-taken pad (cookbook S17/S36#3).
 */

extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146CA0(void *a0);

void func_8017DE28(s32 p) {

    extern s16 D_80126B0C;
    s32 o;
    s32 lim1, lim2;
    s16 t1, t2, lv1, lv2;
    s32 pad[3];

    (void)&pad;
    o = *(s32 *)(p + 0x20);
    t1 = *(u16 *)(o + 0x1C) + 0x800;
    *(s16 *)(o + 0x1C) = t1;
    *(s16 *)(o + 0x18) = t1;
    lim1 = **(s16 **)(p + 0x58);
    lv1 = lim1;
    __asm__("" : "=r"(lv1) : "0"(lv1));
    if (lim1 < t1) {
        *(s16 *)(o + 0x1C) = lv1;
        *(s16 *)(o + 0x18) = lv1;
        D_80126B0C = 1;
    }
    t2 = *(u16 *)(o + 0x1A) + 0x800;
    *(s16 *)(o + 0x1A) = t2;
    lim2 = *(s16 *)(*(s32 *)(p + 0x58) + 2);
    lv2 = lim2;
    if (lim2 < t2) {
        *(s16 *)(o + 0x1A) = lv2;
        func_80146E90((s32 *)p, *(s16 *)(*(s32 *)(p + 0x58) + 4));
        func_80146CA0((void *)p);
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_80162CCC(void);

void func_8017DEEC(s32 a0) {
    u8 *s0;
    u8 *s2;
    u16 w;

    s2 = *(u8 **)(a0 + 0x4C);
    s0 = *(u8 **)(a0 + 0x20);

    if (func_80146E98(a0) != 0) {
        w = *(u16 *)(s0 + 0x1C) + 0x400;
        *(u16 *)(s0 + 0x1C) = w;
        *(u16 *)(s0 + 0x18) = w;
        if ((s16)w >= 0x7001) {
            *(u16 *)(s0 + 0x1C) = 0x7000;
            *(u16 *)(s0 + 0x18) = 0x7000;
        }

        w = *(u16 *)(s0 + 0x1A) + 0x100;
        *(u16 *)(s0 + 0x1A) = w;
        if ((s16)w >= 0x7001) {
            *(u16 *)(s0 + 0x1A) = 0x7000;
        }
    }

    if (*(u16 *)s2 != 0x16) {
        ((void (*)(s32))func_80162CCC)(a0);
    }
}




void func_8017DFAC(s32 param_1) {
    s32 tbl;
    s32 obj;

    tbl = *(s32 *)(param_1 + 0x4C);
    obj = *(s32 *)(param_1 + 0x20);
    *(s32 *)(param_1 + 0x04) = *(s32 *)(tbl + 0x04);
    *(s32 *)(param_1 + 0x08) = *(s32 *)(tbl + 0x08);
    *(s32 *)(param_1 + 0x0C) = *(s32 *)(tbl + 0x0C);
    *(u16 *)(obj + 0x12) += *(u16 *)(*(s32 *)(param_1 + 0x58) + 0x06);
}



extern void (*D_8018C530[])(void);

void func_8017DFF0(void *a0) {
    D_8018C530[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 rand(void);

typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
} SubRec_801EB5C8_8017E02C; /* 0x1C */

typedef struct {
    u16 g0;
    u16 g2;
    s32 g4;
    s32 g8;
    s32 gC;
    SubRec_801EB5C8_8017E02C subs[16];
} GroupRec_801EB5C8_8017E02C; /* 0x1D0 */


void func_8017E02C(s32 param_1)
{

    extern GroupRec_801EB5C8_8017E02C D_801C6FA8[8];
    s32 i, j;
    GroupRec_801EB5C8_8017E02C *grp;
    SubRec_801EB5C8_8017E02C *sub;

    for (i = 0; i < 8; i++) {
        grp = &D_801C6FA8[i];
        grp->g0 = 0;
        grp->g2 = i << 9;
        grp->gC = (rand() & 0xF) << 16;
        grp->g4 = ((rand() & 0xF) << 15) + 0x10000;
        grp->g8 = ((rand() & 0xF) << 12) + 0x8000;

        for (j = 0; j < 16; j++) {
            sub = &grp->subs[j];
            sub->f0 = 0;
            sub->f2 = (rand() & 3) + 4;
            sub->f8 = (j << 8) + (rand() & 0xF) * 56;
            sub->fA = (rand() & 0xF) << 8;
            sub->f14 = (rand() & 0xF) << 13;
            sub->fC = ((rand() & 0xF) << 14) + 0x10000;
            sub->f10 = ((rand() & 0xF) << 12) + 0x8000;
            sub->f4 = 0x200;
            sub->f6 = (rand() & 0xF) << 4;
            sub->f18 = ((rand() & 3) << 5) + 0x40;
        }
    }

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}






void func_8017E1D4(void *arg0) {
    extern GroupRec_801EB5C8_8017E02C D_801C6FA8[8];
    extern void func_8017E368();
    extern void func_80146C3C();
    s32 cnt2;
    s32 i;
    s32 j;
    register s32 base __asm__("$5");
    s32 p;
    s32 vel;
    s32 pos;
    u16 life;
    s32 f18;

    cnt2 = 0;
    for (i = 0; i < 8; i++) {
        {
            register s32 sym __asm__("$2") = (s32)((u8 *)D_801C6FA8);
            base = sym + i * 0x1D0;
        }
        if (*(s16 *)(base) == 0) {
            *(s32 *)(base + 0xC) = *(s32 *)(base + 0xC) + 0x10000;
        }
        for (j = 0; j < 16; j++) {
            p = base + 0x10 + j * 0x1C;
            switch (*(s16 *)(p)) {
            case 0:
                vel = *(s32 *)(p + 0xC) + *(s32 *)(p + 0x10);
                pos = *(s32 *)(p + 0x14);
                life = *(u16 *)(p + 2) - 1;
                pos = pos + vel;
                *(s32 *)(p + 0x14) = pos;
                *(s32 *)(p + 0xC) = vel;
                *(u16 *)(p + 2) = life;
                if ((s16)life == -1) {
                    *(u16 *)(p) = *(u16 *)(p) + 1;
                }
                *(u16 *)(p + 4) = *(u16 *)(p + 4) + *(u16 *)(p + 6);
                *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) + 0x10;
                break;
            case 1:
                *(u16 *)(p + 4) = *(u16 *)(p + 4) + 0x80;
                f18 = *(s32 *)(p + 0x18) - 8;
                *(s32 *)(p + 0x18) = f18;
                if (f18 < 0) {
                    *(s32 *)(p + 0x18) = 0;
                    *(u16 *)(p) = *(u16 *)(p) + 1;
                }
                break;
            case 2:
                cnt2 = cnt2 + 1;
                break;
            }
        }
        func_8017E368(arg0);
    }
    if (cnt2 == 0x80) {
        ((void (*)(u8 *))func_80146C3C)(arg0);
    }
}



extern void func_80015978(s32 a0, s32 *a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern void func_8012EFB8(s32 a0);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_80017DC4(void *a0, void *a1);
extern s32 func_80017E30(void *a0, void *a1);
extern void func_80016ED4(void *a0);




void func_8017E368(s32 a0, s32 a1) {

    extern SVECTOR_8017F40C_8017E368 D_8018C538[4];
    Prim_8017F40C_8017E368 prim;
    u8 matBuf[0x20];
    SVECTOR_8017F40C_8017E368 vecB;
    SVECTOR_8017F40C_8017E368 angBuf;
    SVECTOR_8017F40C_8017E368 sinOut;
    SVECTOR_8017F40C_8017E368 sv1, sv2, sv3, sv4;
    u32 mask;
    s32 rowPtr;
    SVECTOR_8017F40C_8017E368 *ap;
    void *mp;
    SVECTOR_8017F40C_8017E368 *dv;

    func_80015978(a0 + 4, (s32 *)&vecB);
    angBuf.vx = 0;
    angBuf.vy = 0;
    angBuf.vz = *(u16 *)(a1 + 0xe);
    func_800139C8((s32) *(s16 *)(a1 + 2), &angBuf, &angBuf);
    mask = ((u32(*)(void *, void *))func_8012EFB8)(&vecB, &vecB);
    if ((mask & 0xffffefff) == 0) {
        Prim_8017F40C_8017E368 *pp = &prim;
        s32 off;
        s32 cnt;
        cnt = 0;
        ap = &angBuf;
        mp = matBuf;
        dv = D_8018C538;
        off = 0x10;
        pp->v[0].vz = 3;
        pp->code = 0x12;
        pp->tag = 0x50000000;
        pp->k30 = 0x870;
        pp->k32 = 0x1a8;
        pp->k34 = 0x88f;
        pp->k36 = 0x1a8;
        pp->k38 = 0x870;
        pp->k3a = 0x1c7;
        pp->k3c = 0x88f;
        pp->k3e = 0x1c7;
        vecB.vx = vecB.vx + angBuf.vx;
        vecB.vy = vecB.vy + angBuf.vy;
        vecB.vz = vecB.vz + angBuf.vz;
        do {
            rowPtr = a1 + off;
            {
                u32 c = *(u32 *)(rowPtr + 0x18);
                pp->bcast = c | ((c << 0x10) | (c << 8));
            }
            angBuf.vx = angBuf.vy = angBuf.vz = *(u16 *)(rowPtr + 4);
            func_80017DC4(ap, mp);
            angBuf.vx = 0;
            angBuf.vy = 0;
            angBuf.vz = *(u16 *)(rowPtr + 0xa);
            func_80017E30(ap, mp);
            ApplyMatrixSV(mp, &dv[0], &sv1);
            ApplyMatrixSV(mp, &dv[1], &sv2);
            ApplyMatrixSV(mp, &dv[2], &sv3);
            ApplyMatrixSV(mp, &dv[3], &sv4);
            angBuf.vx = 0;
            angBuf.vy = 0;
            angBuf.vz = *(u16 *)(rowPtr + 0x16);
            func_800139C8((s32) *(s16 *)(rowPtr + 8), ap, &sinOut);
            sinOut.vx = sinOut.vx + vecB.vx;
            sinOut.vz = sinOut.vz + vecB.vy;
            pp->v[0].vx = sinOut.vx + sv1.vx;
            pp->v[0].vy = sinOut.vz + sv1.vy;
            pp->v[1].vx = sinOut.vx + sv2.vx;
            pp->v[1].vy = sinOut.vz + sv2.vy;
            pp->v[2].vx = sinOut.vx + sv3.vx;
            off = off + 0x1c;
            pp->v[2].vy = sinOut.vz + sv3.vy;
            cnt = cnt + 1;
            pp->v[3].vx = sinOut.vx + sv4.vx;
            pp->v[3].vy = sinOut.vz + sv4.vy;
            func_80016ED4(pp);
        } while (cnt < 0x10);
    }
}



extern void (*D_80192258[])(void);

void func_8017E620(void *a0) {
    D_80192258[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017E7F4(void);
extern void func_800167B8(s32 a0);

s32 func_8017E65C(s32 a0) {
    func_8017E7F4();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017E6A0(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}


extern void (*D_80192260[])(void);

void func_8017E6C4(void *a0) {
    D_80192260[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017E81C(void);

s32 func_8017E700(s32 a0) {
    func_8017E81C();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800167B8(s32 a0);

s32 func_8017E740(void *a0) {
    s32 v0;
    s32 v1 = -1;
    v0 = *(s32 *)(a0 + 0x28);
    v0 += -1;
    *(s32 *)(a0 + 0x28) = v0;
    if (v0 == v1) {
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        func_8002D4C8(0x1D, 0);
        func_800D0C48(1);
        func_800167B8(4);
        *(u8 *)(a0 + 0x15) = *(u8 *)(a0 + 0x15) + 1;
    }
    return 0;
}


extern s32 func_800167F0(s32 arg);
extern void func_800CFBCC(s32 arg);

s32 func_8017E7BC(void) {
    if ((func_800167F0(0x4) & 0xFFFF) == 0) {
        return 0;
    } else {
        func_800CFBCC(0x5);
        return 1;
    }
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_8019226C;

void func_8017E7F4(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8019226C, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017E81C(void) {

    extern s32 D_80192274(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_80192274, 0x1000000);
}


extern s32 func_80147054(void *a0);
    extern void func_80171928(void *a0);
    void func_8017E844(s32 a0) {
        ((void (*)(s32 *))func_80147054)((s32 *)a0);
        ((s32 (*)(s32))func_80171928)(a0);
    }


void func_8017E874(void) {
    extern void func_8012A094(s32 a0);
    extern void func_8017E9D4(void *a0);

    D_80126954 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x155;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0xC0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017E9D4, 0);
    func_8012A094((s32)D_80126948);
    func_8017E9D4(D_80126948);
}


#include "common.h"

extern s32 D_80126E60[];
extern s32 D_80126E6C;
extern s32 D_80126E74;
extern s16 D_80126E80;
extern s16 D_80126E82;
extern s16 D_80126E84;
extern s16 D_80126E8E;
extern s16 D_80126E90;
extern s16 D_80126E92;

extern void func_8012A048(void *a0, s32 a1, u8 a2);
extern void func_8012A094(s32 a0);
extern void func_8017E9D4(void *a0);
extern void func_8012A100(s8 a0);

void func_8017E910(void) {
    s32 *s0 = (s32 *)D_80126E60;

    D_80126E6C = 0xC8;
    D_80126E74 = 0x2BC;
    D_80126E80 = -0xE3;
    D_80126E82 = 0x400;
    D_80126E84 = 0;
    D_80126E8E = 0;
    D_80126E90 = 0;
    D_80126E92 = 0;

    func_8012A048(s0, (s32)func_8017E9D4, 1);
    func_8012A094((s32)s0);
    func_8017E9D4(s0);
    func_8012A100(1);
}


extern void func_8012A100(s8 a0);
    void func_8017E9B4(void) {
        ((s32 (*)(s32))func_8012A100)(0);
    }



extern void (*D_8019227C[])(void);

void func_8017E9D4(void *a0) {
    D_8019227C[*(u8 *)((s32)a0 + 0x4)]();
}



/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2) */

extern u16 func_80148800(s32 *a0);
extern void func_8017EAE4(s32 param_1, s16 *param_2);

void func_8017EA10(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_80192284[];
    extern Blk8_80126940_8017EA10 D_80126940;
    Blk8_80126940_8017EA10 sp10;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_80192284[t];
    }
    sp10 = D_80126940;
    func_8017EAE4(a0, sp10.v);
}


extern void func_8017EAE4(s32 param_1, s16 *param_2);

void func_8017EAB0(s32 a0) {
    extern s16 D_80192288;
    s16 v0;

    v0 = *(u16 *)(a0 + 0x22) + 0xB;
    *(s16 *)(a0 + 0x22) = v0;
    *(s16 *)(a0 + 0x1A) = v0;
    func_8017EAE4(a0, &D_80192288);
}



// @class: schedule
// @stuck: none — MATCH (102 ins). MATRIX(0x20:m@0,t@0x14)+SVECTOR in/out stack layout; the only
//   lever past struct-layout was source order: emit m1.t[2] BEFORE svec_in.vx/vy so the two `sh
//   zero` stores schedule into the t[2] load-delay slot (after the a1 setup), not after t[1].

   /* 0x20: m@0, pad@0x12, t@0x14 */
      /* 8 bytes */

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_8017EAE4(s32 param_1, s16 *param_2) {
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C((s32)*(s16 *)(param_1 + 0x28), (s32)*(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2A), (s32)*(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C((s32)*(s16 *)(param_1 + 0x2C), (s32)*(s16 *)(param_1 + 0x32), 0x10);

    *(s32 *)(param_1 + 0x48) = (s32)*(s16 *)(param_1 + 0x28) + (s32)param_2[0];
    *(s32 *)(param_1 + 0x4C) = (s32)*(s16 *)(param_1 + 0x2A) + (s32)param_2[1];
    *(s32 *)(param_1 + 0x50) = (s32)*(s16 *)(param_1 + 0x2C) + (s32)param_2[2];
    func_80049CAC(param_1 + 0x18, (s32)&m1);

    m1.t[0] = *(s16 *)(param_1 + 0x28) + param_2[0];
    m1.t[1] = *(s16 *)(param_1 + 0x2A) + param_2[1];
    m1.t[2] = *(s16 *)(param_1 + 0x2C) + param_2[2];
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(param_1 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(param_1 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(param_1 + 0x44) = (s32)svec_out.vz;
}


s32 func_8017EC7C(void)
{
    extern u8 D_80192478[];
    extern volatile s32 D_801C7E30;
    s32 i;
    s32 ptr;

    for (i = 0; i < 6; i++) {
        ptr = (&D_801C7E30)[D_80192478[i]];
        if (*(s16 *)(*(s32 *)(ptr + 0x6C) + 0x76) > 0) {
            return *(s32 *)(ptr + 4);
        }
    }
    return 0;
}


s32 func_8017ECE4(s32 arg0) {
    s32 x;
    s32 y;

    if ((u16) (*(u16 *) (arg0 + 6) + 0x100) >= 0x301U) {
        return -1;
    }
    if ((u16) (*(u16 *) (arg0 + 0xE) + 0xA0) >= 0x141U) {
        return -1;
    }
    x = -(func_80047948((((s32) *(u16 *) (arg0 + 6) << 16) >> 15) - 0xC0) * 0x30) >> 12;
    x -= 0x90;
    y = *(s16 *) (arg0 + 0xE);
    if (y >= 0) {
        x += (y << 6) / 0xA0;
    } else {
        x -= (y * 0x30) / 0xA0;
    }
    if (x >= *(s16 *) (arg0 + 10)) {
        return 0;
    }
    *(s16 *) (arg0 + 10) = x;
    return 1;
}


extern void func_800599B8(void *a0, void *a1);
extern u8 D_80192480[];
extern void *D_801C39FC[];
extern void *D_801C3A00[];

void func_8017EDEC(s32 param_1) {
    volatile s32 pad1;
    volatile s32 pad2;
    u8 t;

    t = (*(u8 *)(param_1 + 0xC2) + 2) & 0xF;
    *(u8 *)(param_1 + 0xC2) = t;
    func_800599B8(D_80192480, D_801C39FC[t]);
    func_800599B8(D_80192480 + 8, D_801C3A00[*(u8 *)(param_1 + 0xC2)]);
}


extern volatile s32 D_801C7E30;
extern s32 D_801C7E34;
extern s32 D_801C7E38;
extern volatile s32 D_801C7E4C;
extern s32 D_801C7E50;
extern s32 D_801C7E58;
extern s32 D_801C7E64;
extern s32 D_801C7E74;
extern s32 D_801C7E78;
extern s16 D_801C7E28;
extern s16 D_801C7E2C;
extern s32 D_801924A0;
extern s32 D_801A33AC;

void func_8017EE68(int param_1)
{
    int iVar1;
    s32 uVar2;
    s32 *puVar3;
    s32 *puVarX;

    iVar1 = func_8012C354(param_1, &D_801924A0);
    if (iVar1 != 0) {
        *(u16 *)(param_1 + 2) = 10;
        func_8012A828(param_1, &D_801A33AC);
        *(u8 *)(param_1 + 0xc0) = 1;
        *(s32 *)(param_1 + 0xb4) = -1;
        func_8012B23C(param_1);
        func_8001D0E8(*(s32 *)(param_1 + 0x20), 0x400, 0x400);
        iVar1 = 2;
        puVarX = &D_801C7E30;
        *puVarX = param_1;
        puVar3 = puVarX + 2;
        D_801C7E34 = 0;
        D_801C7E64 = 0;
        do {
            uVar2 = func_8012C658(0x25e, iVar1 + -2, param_1);
            *puVar3 = uVar2;
            iVar1 = iVar1 + 1;
            puVar3 = puVar3 + 1;
        } while (iVar1 < 7);
        D_801C7E4C = func_8012C588(0x2b1, param_1);
        *(s32 *)(D_801C7E4C + 0xe0) = 0x10000000;
        *(u8 *)(param_1 + 0x75) = 3;
        *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) = *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) & 0x7fffffff;
        D_801C7E50 = func_8012C588(0x28c, param_1);
        D_801C7E58 = func_8012C588(0x28e, param_1);
        *(u16 *)(param_1 + 0x76) = 0x180;
        D_801C7E74 = 0;
        D_801C7E78 = 0;
        D_801C7E28 = 0;
        D_801C7E2C = 0;
    }
    return;
}


/*
 * func_8017EFC8 (101 ins, ov_SC05_010) — cracked pin-light.
 *
 * Two levers, both from local-alloc.c:
 *
 *  1. SPLIT THE SHARED TAIL VARIABLE.  The prior draft used one cross-block
 *     `s16 t` + `goto L` for the shared `sh $vX, 0xFE($s0)` tail.  That makes
 *     `t` a GLOBAL allocno, so local-alloc hands $v0 to the per-block constant
 *     first and `t` is pushed onto $v1 in BOTH arms (the measured
 *     REGALLOC-PERM/$v0>$v1>$v0, closeness 11).  Giving case 2 and case 7 their
 *     own block-local temps and their own store makes both block-local; the
 *     shared tail comes back for free because jump2/cross_jump runs AFTER
 *     regalloc and re-merges the two identical `sh $v0, 0xFE($s0)` tails
 *     (101 ins, and case 7 then allocates exactly like the target).
 *
 *  2. THE $v0 PIN IN CASE 2.  local-alloc.c:1579 `qty_compare` ranks by
 *        pri = floor_log2(refs) * refs * size / (death - birth) * 10000
 *     with birth/death on a 2*insn_number scale, evaluated on the PRE-sched2
 *     (i.e. source) order.  Case 7 ties (temp 2*4/8, const 2/2 -> 10000 each)
 *     and the tie breaks on qty number, so the temp wins $v0.  Case 2 carries
 *     one extra insn (`sw $zero, 0x1C($s0)`) inside the temp's range, so the
 *     temp scores 8000 against the constant's 10000 and LOSES $v0.  The window
 *     is empty in integer insn counts — every legal statement permutation
 *     keeps exactly four insns between the load and the last use (measured: 6
 *     orderings, closeness 46/47 or a wrecked schedule) — so the tie is closed
 *     with a zero-byte block-scope pin instead.  No call is crossed, so the
 *     §74 caller-saved hazard does not apply.
 */
void func_8017EFC8(s32 param_1)
{
    extern s32 D_801C7E74;
    extern s32 D_801C7E78;
    extern s32 D_801C7E70;
    extern u8 *D_801C7E60[];
    extern u8 D_801924D4[];
    extern u8 D_801A34B4[];
    extern u8 D_801A3844[];
    extern u8 D_801A3A2C[];
    extern void func_8012A828(s32 a0, void *a1);

    u32 idx;
    u8 c;

    if (*(s32 *)(param_1 + 0x1C) != 0) {
        (*(s32 *)(param_1 + 0x1C))--;
        return;
    }
    if ((*(u16 *)(param_1 + 0x72) & 0x4000) == 0) {
        return;
    }
    idx = D_801C7E74;
    c = D_801924D4[idx];
    *(u16 *)(param_1 + 0x34) = 0;
    D_801C7E74 = (idx + 1) % 6;
    switch (c) {
    case 0:
        *(u16 *)(D_801C7E60[0] + 0xAE) = 0;
        func_8012A828(param_1, &D_801A34B4);
        *(u16 *)(param_1 + 2) = 3;
        *(u16 *)(param_1 + 0x84) = 0x1E;
        break;
    case 1:
        *(s32 *)(param_1 + 0x1C) = 0x3C;
        *(u16 *)(param_1 + 2) = 4;
        break;
    case 2: {
        register s16 t2 __asm__("$2");
        t2 = D_801C7E78 + 7;
        *(s32 *)(param_1 + 0x1C) = 0;
        *(u16 *)(param_1 + 2) = 5;
        *(s16 *)(param_1 + 0xFE) = t2;
        break;
    }
    case 3:
    case 4:
    case 5:
        *(s32 *)(param_1 + 0x1C) = D_801C7E78 * 18 + 0x25;
        func_8012A828(param_1, &D_801A3844);
        *(u16 *)(param_1 + 2) = 6;
        break;
    case 6:
        *(u16 *)(param_1 + 2) = 7;
        break;
    case 7: {
        s16 t3;
        D_801C7E70 = 0;
        func_8012A828(param_1, &D_801A3A2C);
        t3 = D_801C7E78 + 2;
        *(u16 *)(param_1 + 2) = 2;
        *(s16 *)(param_1 + 0xFE) = t3;
        break;
    }
    case 8:
        break;
    }
}


/*
 * func_8017F15C (279 ins, ov_SC05_010) — MATCH.
 *  - §195-H: D_801C7E50 is re-loaded before EVERY store through it, so it is
 *    declared as a one-element array alias (`[0]` grants /s -> cse kills it at
 *    each varying-address store). The TU's file-scope decl is scalar s32, hence
 *    the __asm__ alias (house style, see func_8017FDE0's D_801C7E34_tbl).
 *  - Block-local temps per case (a shared function-scope temp goes global
 *    allocno and lands in $a0 — same lever as func_8017EFC8's comment).
 *  - D_80126B5E/62 are u16 in the TU; the -0x100/-0xB0 stores need `addiu`,
 *    not `ori`, so they are read/written through the TU's s16 aliases.
 *  - case 5 is `if (!A && !B) { tail } else { X }` (both tests bnez -> X, tail
 *    falls through); case 4 duplicates the tail and cross-jump merges it.
 */
void func_8017F15C(s32 param_1)
{
    extern s32 D_801C7E70;
    extern s32 D_801C7E50_p[] __asm__("D_801C7E50");
    extern s32 D_801C7E54;
    extern s32 D_801C7E5C;
    extern s16 D_801C7E68;
    extern s16 D_801C7E6A;
    extern s16 D_80126B5E_s __asm__("D_80126B5E");
    extern s16 D_80126B62_s __asm__("D_80126B62");
    extern s32 D_80126B6C;
    extern s32 D_801A33AC;
    extern u8 D_801A3AC4[];
    extern u8 D_801A3B2C[];
    extern u8 D_801A3B74[];
    extern u8 D_801A3BB4[];
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32 func_80153BD8(s32 a0);
    extern s32 func_80153BF0(s32 a0);
    extern s32 func_8012C588(s32 a0, s32 a1);

    if (D_801C7E70 != 0) {
        D_801C7E70--;
    }
    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        if (*(s16 *)(param_1 + 0x98) == 0) {
            *(s16 *)(D_801C7E50_p[0] + 0x10A) = 1;
            *(s16 *)(D_801C7E50_p[0] + 0x102) = 0x1E;
            *(s16 *)(D_801C7E54 + 0x10A) = 1;
            *(s16 *)(D_801C7E5C + 0x10A) = 1;
            func_8012A828(param_1, &D_801A3AC4);
            *(s16 *)(param_1 + 0x34) = 1;
        }
        break;
    case 1:
        if (*(s16 *)(D_801C7E50_p[0] + 0x10A) >= 2) {
            *(s16 *)(param_1 + 0x34) = 2;
            *(s16 *)(param_1 + 0x100) = 0x3C;
        }
        break;
    case 2:
        if (*(s16 *)(param_1 + 0x100) == 0) {
            s16 t;
            t = *(s16 *)(param_1 + 0xFE) - 1;
            *(s16 *)(param_1 + 0xFE) = t;
            if (t != 0) {
                func_8002D4C8(0x89A, 0);
                *(s16 *)(param_1 + 0x100) = 0x96;
                *(s16 *)(D_801C7E50_p[0] + 0x102) = 0x5A;
                *(s16 *)(D_801C7E50_p[0] + 0x10A) = 1;
            } else {
                *(s16 *)(param_1 + 0x34) = 3;
                *(s32 *)(param_1 + 0x1C) = 0x3C;
                *(s16 *)(D_801C7E50_p[0] + 0x10A) = 4;
                func_8012A828(param_1, &D_801A3B2C);
            }
        } else {
            *(s16 *)(param_1 + 0x100) -= 1;
        }
        if (func_80153BD8(D_801C7E54) != 0 || func_80153BD8(D_801C7E5C) != 0) {
            func_8012A828(param_1, &D_801A3B74);
            *(s16 *)(D_801C7E50_p[0] + 0x10A) = 5;
            *(s16 *)(D_801C7E54 + 0x10A) = 0;
            *(s16 *)(D_801C7E5C + 0x10A) = 0;
            *(s16 *)(param_1 + 0x34) = 4;
            D_801C7E68 = D_80126B5E_s;
            D_801C7E6A = D_80126B62_s;
            *(s32 *)(param_1 + 0x1C) = 0x100;
            *(s16 *)(param_1 + 0xFC) = 0;
            func_8002D4C8(0x89A, 0);
        }
        break;
    case 3: {
        s32 v;
        if (*(s16 *)(param_1 + 0x98) == 0) {
            func_8012A828(param_1, &D_801A33AC);
        }
        v = *(s32 *)(param_1 + 0x1C) - 1;
        *(s32 *)(param_1 + 0x1C) = v;
        if (v == 0) {
            *(s16 *)(param_1 + 2) = 1;
            *(s16 *)(D_801C7E50_p[0] + 0x10A) = 0;
            *(s16 *)(D_801C7E54 + 0x10A) = 0;
            *(s16 *)(D_801C7E5C + 0x10A) = 0;
            *(s32 *)(param_1 + 0x1C) = 0x3C;
        }
        break;
    }
    case 4:
        if (func_80153BD8(D_801C7E54) != 0 || func_80153BD8(D_801C7E5C) != 0) {
            s16 t;
            s32 v;
            t = *(s16 *)(param_1 + 0xFC) + 1;
            *(s16 *)(param_1 + 0xFC) = t;
            v = *(s32 *)(param_1 + 0x1C) - (t >> 3);
            *(s32 *)(param_1 + 0x1C) = v;
            if (v <= 0) {
                D_80126B5E_s = -0x100;
                D_80126B62_s = -0xB0;
                *(s16 *)(param_1 + 0x34) = 5;
                func_8002D4C8(0xAD4, 0);
            }
            D_80126B5E_s = (((D_801C7E68 + 0x100) * *(s32 *)(param_1 + 0x1C)) >> 8) - 0x100;
            D_80126B62_s = (((D_801C7E6A + 0xC0) * *(s32 *)(param_1 + 0x1C)) >> 8) - 0xC0;
        } else {
            *(s16 *)(param_1 + 0x34) = 3;
            *(s32 *)(param_1 + 0x1C) = 0x3C;
            *(s16 *)(D_801C7E50_p[0] + 0x10A) = 4;
            func_8012A828(param_1, &D_801A3B2C);
            func_80153BF0(param_1);
        }
        break;
    case 5:
        D_80126B6C = 0;
        if (*(s16 *)(param_1 + 0x98) == 0) {
            func_8012A828(param_1, &D_801A3BB4);
        }
        if (func_80153BD8(D_801C7E54) == 0 && func_80153BD8(D_801C7E5C) == 0) {
            *(s16 *)(param_1 + 0x34) = 3;
            *(s32 *)(param_1 + 0x1C) = 0x3C;
            *(s16 *)(D_801C7E50_p[0] + 0x10A) = 4;
            func_8012A828(param_1, &D_801A3B2C);
            func_80153BF0(param_1);
        } else {
            s32 v = func_8012C588(0x2D7, param_1);
            if (v != 0) {
                *(s16 *)(v + 6) = -0x100;
                *(s16 *)(v + 0xA) = -0x180;
            }
        }
        break;
    }
}


void func_8017F5B8(s32 param_1)
{
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 func_8012C588(s32 a0, s32 a1);
    extern void func_8012C218(void *a0);
    extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
    extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
    extern void func_800599B8(void *a0, void *a1);
    extern u8 D_801152A8[];
    extern u16 D_80126B66;
    extern s32 *D_80126B78;
    extern s32 *D_80126B90;
    extern u8 D_80192480[];
    extern u8 D_80192488[];
    extern u8 D_80192480_b[] __asm__("D_80192480");
    extern u8 D_80192488_b[] __asm__("D_80192488");
    extern s32 D_801A33AC;
    extern u8 D_801A35FC[];
    extern u16 D_801A3C44;
    extern s32 D_801A3D94;
    extern u8 D_801A3E2C[];
    extern void *D_801C39FC[];
    extern u8 *D_801C7E60[];
    extern s32 D_801C7E64;
    extern s32 D_801C7E64_b __asm__("D_801C7E64");
    extern s32 D_801C7E78;

    u16 sv0[4];
    u16 sv1[4];
    s32 q;
    s32 r;
    s32 bx;
    s32 z;
    s32 t2;
    s32 by;
    s16 c;
    u8 t;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        c = *(u16 *)(param_1 + 0x84) - 1;
        *(s16 *)(param_1 + 0x84) = c;
        if (c == 0) {
            func_8002D4C8(0x89B, 0);
        }
        if (*(s16 *)(param_1 + 0x98) == 0) {
            func_8012A828(param_1, &D_801A35FC);
            *(s16 *)(param_1 + 0x34) = 1;
            D_801C7E64 = func_8012C588(0x2EC, param_1);
            if (D_801C7E64 != 0) {
                *(s16 *)(D_801C7E64_b + 6) = sv0[0] + 0x10;
            }
            func_8002D4C8(0x89C, 0);
        }
        break;
    case 1:
        if (*(u16 *)(param_1 + 0x72) & 0x4000) {
            func_8012A828(param_1, &D_801A3C44);
            t2 = D_801C7E78;
            *(s16 *)(param_1 + 0x34) = 2;
            *(u8 *)(param_1 + 0xC2) = 0;
            *(s32 *)(param_1 + 0x1C) = 3 - t2;
            if (D_801C7E64 != 0) {
                func_8012C218((void *)D_801C7E64);
            }
        } else {
            q = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x20);
            q += 0x24;
            bx = *(u16 *)(param_1 + 0x6) + *(u16 *)(q + 0x0);
            z = D_80126B66;
            sv0[0] = bx + 0x20;
            by = *(u16 *)(param_1 + 0xA) + *(u16 *)(q + 0x2);
            sv1[0] = bx + 0x10;
            sv1[2] = z;
            sv0[2] = z;
            sv0[1] = by;
            sv1[1] = by;
            if (D_801C7E64 != 0) {
                *(s16 *)(D_801C7E64_b + 6) = bx + 0x30;
            }
            *(s32 *)(param_1 + 0x1C) = *(s32 *)(param_1 + 0x1C) + 1;
            if ((*(s32 *)(param_1 + 0x1C) & 1) == 0) {
                r = func_8012C588(0x2EB, param_1);
                if (r != 0) {
                    *(s16 *)(r + 0x6) = *(u16 *)(param_1 + 0x6) + *(u16 *)(q + 0x0);
                    *(s16 *)(r + 0xA) = *(u16 *)(param_1 + 0xA) + *(u16 *)(q + 0x2);
                    *(s16 *)(r + 0xE) = *(u16 *)(param_1 + 0xE) + *(u16 *)(q + 0x4);
                    *(s16 *)(*(s32 *)(r + 0x20) + 0x10) = *(u16 *)(q + 0x6);
                    *(s16 *)(*(s32 *)(r + 0x20) + 0x12) = *(u16 *)(q + 0x8);
                    *(s16 *)(*(s32 *)(r + 0x20) + 0x14) = *(u16 *)(q + 0xA);
                }
            }
            if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)sv0, (s32)sv1) != 0) {
                func_8012F568(1, 0x4004, 0x400, 0x30, (s32)sv1, (s32)D_801152A8);
            }
        }
        break;
    case 2:
        if (*(s16 *)(param_1 + 0x98) == 0) {
            func_8012A828(param_1, &D_801A3E2C);
            *(s16 *)(param_1 + 0x34) = 3;
        }
        break;
    case 3:
        t = (*(u8 *)(param_1 + 0xC2) + 2) & 0xF;
        *(u8 *)(param_1 + 0xC2) = t;
        func_800599B8(D_80192480, D_801C39FC[t]);
        func_800599B8(D_80192488, D_801C39FC[*(u8 *)(param_1 + 0xC2) + 1]);
        if (*(u16 *)(param_1 + 0x72) & 0x4000) {
            if (--*(s32 *)(param_1 + 0x1C) == 0) {
                *(s16 *)(param_1 + 0x34) = 4;
                func_8012A828(param_1, &D_801A3D94);
                *(u8 *)(param_1 + 0xC2) = 0;
                func_800599B8(D_80192480_b, D_801C39FC[*(u8 *)(param_1 + 0xC2)]);
                func_800599B8(D_80192488_b, D_801C39FC[*(u8 *)(param_1 + 0xC2) + 1]);
            }
        }
        break;
    case 4:
        if (*(s16 *)(param_1 + 0x98) == 0) {
            func_8012A828(param_1, &D_801A33AC);
            *(s16 *)(param_1 + 0x2) = 1;
            *(s32 *)(param_1 + 0x1C) = 0x3C;
            *(s16 *)(D_801C7E60[0] + 0xAE) = -1;
        }
        break;
    }
}


#include "common.h"

extern s32 D_801A33AC;
extern volatile s32 D_801C7E4C;
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);

void func_8017F9B4(s32 param_1)
{
    s32 cnt;
    s32 i;
    s32 ent;
    s32 tblptr;
    s32 r;

    cnt = *(s32 *)(param_1 + 0x1C);
    if (cnt == 0) {
        *(s16 *)(param_1 + 2) = 1;
        func_8012A828(param_1, &D_801A33AC);
        *(s32 *)(param_1 + 0x1C) = 0x5A;
    } else {
        /* sched.md S2: `next` must be a FRESH SINGLE-SET local. Reusing `cnt`
         * (2 SETs) kills birthing_insn_p's boost, the addiu stays at bb-top and
         * dbr steals IT into the bnez slot instead of the magic-constant lui. */
        s32 next = cnt - 1;
        *(s32 *)(param_1 + 0x1C) = next;
        if (next % 19 == 0) {
            func_8012C588(0x29E, param_1);
            tblptr = *(s32 *)(D_801C7E4C + 0x20);
            *(s16 *)(tblptr + 0x1A) = 0xC00;
            for (i = 0; i < 8; i++) {
                ent = func_8012C658(0x29E, 2, param_1);
                if (ent != 0) {
                    s32 fld;
                    *(u16 *)(ent + 6) = *(u16 *)(ent + 6) + 0x25B;
                    r = rand();
                    fld = *(u16 *)(ent + 0xA);
                    *(s16 *)(ent + 0x16) = -0x10;
                    *(u16 *)(ent + 0xA) = fld + -0x70 + (r & 0x1F);
                    r = rand();
                    *(s16 *)(ent + 0x12) = (r & 7) - 4;
                    r = rand();
                    *(s16 *)(ent + 0x1A) = -4 - (r & 7);
                }
            }
        }
    }
}


void func_8017FAF4(s32 param_1)
{
    extern s32 D_801A3D5C;
    extern u8 D_801202A0[];
    extern volatile s32 D_801C7E4C;
    extern s32 D_80126B60;
    extern u16 D_80126B5E;
    extern s32 func_8014CB8C(void);
    extern s32 func_80172658(s32 *a0);
    extern s32 func_801726A0(s32 *a0);
    extern u8 D_801A3E2C[];
    extern s32 D_801C7E78;
    extern s32 D_801A3D94;
    extern s32 D_801A33AC;
    extern u8 *D_801C7E60[];
    extern u8 D_80192480[];
    extern u8 D_80192488[];
    /* Second-copy aliases of the same two symbols.  cse.c hashes a SYMBOL_REF by the
     * interned-string POINTER, so a second decl with the same __asm__ name is a distinct
     * rtx: the two halves of case 2 no longer unify, each address stays used exactly once,
     * local-alloc's update_equiv_regs substitutes the constant back, and gcc emits `la $a0,…`
     * at all four call sites (nop delay slot) instead of hoisting them into $s3/$s4. */
    extern u8 D_80192480_b[] __asm__("D_80192480");
    extern u8 D_80192488_b[] __asm__("D_80192488");
    extern void *D_801C39FC[];
    extern void func_800599B8(void *a0, void *a1);
    extern void func_8012A828(s32 a0, void *a1);
    extern void func_8002D4C8(s32 a0, s32 a1);

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        if (*(s16 *)(param_1 + 0x98) == 0) {
            u16 *ptr;
            s32 i;

            *(s16 *)(param_1 + 0x34) = 1;
            func_8012A828(param_1, &D_801A3D5C);
            *(s32 *)(param_1 + 0x1C) = 0x5A;
            ptr = (u16 *)D_801202A0;
            for (i = 0; i < 0x60; i++) {
                if (ptr[0] == 0x2B5) {
                    ptr[0x1A] = 1;
                }
                ptr += 0x86;
            }
            *(s32 *)(D_801C7E4C + 0xE0) = 0x78;
        }
        break;
    case 1:
        if (func_8014CB8C() == 0) {
            s32 *p = &D_80126B60;

            if (*p < 0) {
                if (func_80172658(p - 2) != 0 || func_801726A0(p - 2) != 0) {
                    D_80126B5E = D_80126B5E + 4;
                } else {
                    D_80126B5E = D_80126B5E + 0x18;
                }
            }
        }
        if (--*(s32 *)(param_1 + 0x1C) == 0) {
            *(s16 *)(param_1 + 0x34) = 2;
            func_8012A828(param_1, &D_801A3E2C);
            *(u8 *)(param_1 + 0xC2) = 0;
            func_8002D4C8(4, 0x89F);
            *(s32 *)(param_1 + 0x1C) = 7 - D_801C7E78 * 2;
        }
        break;
    case 2: {
        u8 t;

        t = (*(u8 *)(param_1 + 0xC2) + 2) & 0xF;
        *(u8 *)(param_1 + 0xC2) = t;
        func_800599B8(D_80192480, D_801C39FC[t]);
        func_800599B8(D_80192488, D_801C39FC[*(u8 *)(param_1 + 0xC2) + 1]);
        if (*(u16 *)(param_1 + 0x72) & 0x4000) {
            if (--*(s32 *)(param_1 + 0x1C) == 0) {
                *(s16 *)(param_1 + 0x34) = 3;
                func_8012A828(param_1, &D_801A3D94);
                *(u8 *)(param_1 + 0xC2) = 0;
                func_800599B8(D_80192480_b, D_801C39FC[*(u8 *)(param_1 + 0xC2)]);
                func_800599B8(D_80192488_b, D_801C39FC[*(u8 *)(param_1 + 0xC2) + 1]);
            }
        }
        break;
    }
    case 3:
        if (*(s16 *)(param_1 + 0x98) == 0) {
            func_8012A828(param_1, &D_801A33AC);
            *(s16 *)(param_1 + 2) = 1;
            *(s32 *)(param_1 + 0x1C) = 0x5A;
            *(s16 *)(D_801C7E60[0] + 0xAE) = -1;
            *(u16 *)(param_1 + 0x70) &= 0xFFFE;
        }
        break;
    }
}


void func_8017FDE0(s32 param_1)
{
    extern u8 *D_801C7E60[];
    extern s32 D_801C7E78;
    extern s32 D_801C7E34_tbl[] __asm__("D_801C7E34");
    extern s16 D_80192470[];
    extern u8 D_801A36FC[];
    extern void func_8012A828(s32 a0, void *a1);
    extern s32 func_8012C588(s32 a0, s32 a1);
    extern u16 D_801A3C44;
    extern void func_8002D4C8(s32 a0, s32 a1);

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        if (10000 - D_80192470[D_801C7E78] < *(s16 *)(D_801C7E60[0] + 0x76))
            goto L_state4;
        *(s16 *)(D_801C7E60[0] + 0x76) = 10000;
        *(s16 *)(D_801C7E60[0] + 0xAE) = -1;
        func_8012A828(param_1, &D_801A36FC);
        *(s16 *)(param_1 + 0x34) = 1;
        break;
    L_state4:
        func_8012A828(param_1, &D_801A36FC);
        *(s32 *)(param_1 + 0x1C) = D_801C7E78 * 16 + 0x19;
        *(s16 *)(param_1 + 2) = 4;
        *(s16 *)(D_801C7E60[0] + 0xAE) = -1;
        break;

    case 1: {
        s32 *pp = D_801C7E34_tbl;
        if (*pp == 0) {
            *pp = func_8012C588(0x2DB, param_1);
            *(u16 *)(D_801C7E34_tbl[0] + 6) += 0x270;
            *(u16 *)(D_801C7E34_tbl[0] + 10) -= 0xA0;
        }
        *(s32 *)(param_1 + 0x1C) = 0;
        *(u16 *)(param_1 + 0x34) += 1;
        break;
    }

    case 2:
        break;

    case 3:
        func_8012A828(param_1, &D_801A3C44);
        *(s16 *)(param_1 + 2) = 8;
        func_8002D4C8(0x89F, 0);
        *(u16 *)(param_1 + 0x70) |= 1;
        *(s16 *)(param_1 + 0x34) = 0;
        *(s16 *)(D_801C7E60[0] + 0xAE) = 0;
        break;
    }
}


void func_8017FFA8(s32 param_1)
{
    extern volatile s32 D_801C7E30;
    extern volatile s32 D_801C7E4C;
    extern s32 D_801C7E60;
    extern u8 D_80192478[];
    extern u16 D_801922B8;
    extern u16 D_80126B62;
    extern s32 D_8019231C;
    extern s32 func_8012C588(s32 a0, s32 a1);
    extern s32 func_80178B18(s32 param_1, s32 param_2);
    extern void func_801746DC(void);
    extern int func_80178970(void);
    extern void func_80178D18(void);

    s32 found;
    s32 i;
    s32 *tbl;
    s16 *b62;
    s32 q;
    s32 sub;
    s32 a;
    u16 b;
    u16 lookup;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        found = 0;
        i = 0;
        tbl = (s32 *)&D_801C7E30;
        b62 = (s16 *)&D_80126B62;
        for (; i < 6; i++) {
            q = tbl[D_80192478[i]];
            sub = *(s32 *)(q + 0x6C);
            if (*(u8 *)(sub + 0x74) != 0) {
                a = *(s16 *)(sub + 0x70);
                b = *(u16 *)(sub + 0xA);
                lookup = *(u16 *)((u8 *)&D_801922B8 + (a << 4));
                found = 1;
                *(s32 *)((u8 *)b62 + 0xA) = 0;
                *b62 = b + lookup;
            }
        }
        if (!found) {
            break;
        }
        func_80178B18(param_1, (s32)&D_8019231C);
        func_801746DC();
        goto tail_inc;
    case 4:
        D_801C7E60 = func_8012C588(0x27C, param_1);
        /* fallthrough */
    case 2:
    tail_inc:
        *(u16 *)(param_1 + 0x34) += 1;
        break;
    case 1:
    case 3:
    case 5:
        break;
    }
    if (((s32 (*)(s32))func_80178970)(param_1)) {
        ((void (*)(s32))func_80178D18)(param_1);
        *(u16 *)(param_1 + 2) = 1;
        *(u16 *)(param_1 + 0x34) = 0;
        *(s32 *)(param_1 + 0x1C) = 0x1E;
        *(s32 *)(D_801C7E4C + 0xE0) = 0;
    }
}



extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8 D_801152A8[];
extern s16 D_801C7E28;
extern void (*D_801924E4[])(struct Entry_8016E95C *);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);

void func_80180108(s32 arg0)
{
    s16 *b5e = (s16 *)&D_80126B5E;
    s16 vecA[3];
    s16 vecB[3];

    if (*b5e < -0x120) {
        *b5e = -0x120;
        vecA[0] = -0x130;
        vecB[0] = -0x110;
        vecA[1] = vecB[1] = D_80126B62 - 0x40;
        vecA[2] = vecB[2] = D_80126B66;
        if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)vecA, (s32)vecB) != 0) {
            func_8012F568(1, 0x8004, 0xC00, 10, (s32)vecB, (s32)D_801152A8);
        }
    }
    if (D_801C7E28 != 0) {
        D_801C7E28 = D_801C7E28 - 1;
    }
    D_801924E4[*(u16 *)(arg0 + 2)]((struct Entry_8016E95C *)arg0);
}


extern s32 func_8004787C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8 D_801152A8[];
extern volatile s32 D_801C7E30;

void func_80180214(s32 arg0) {
    register s32 t __asm__("$3"); /* pinned to $v1 */
    u16 state = M2C_FIELD(arg0, u16 *, 0x34);
    s16 cnt;
    s16 vec[3];

    switch (state) {
    case 0:
        M2C_FIELD(arg0, s32 *, 0x1C) += 0x80;
        t = func_8004787C(M2C_FIELD(arg0, s32 *, 0x1C)) >> 4;
        t += 0x1000;
        M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1A) = (s16)t;
        M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1C) = (s16)t;
        if (M2C_FIELD(arg0, s32 *, 0x1C) >= 0x800) {
            M2C_FIELD(arg0, s32 *, 0x1C) &= 0x7FF;
            cnt = M2C_FIELD(arg0, u16 *, 0xFC) - 1;
            M2C_FIELD(arg0, u16 *, 0xFC) = cnt;
            if (cnt == 0) {
                M2C_FIELD(arg0, u16 *, 0x34) += 1;
                func_8002D4C8(0x905, 0);
                if (*(u8 *)(*(s32 *)(arg0 + 0x6C) + 0x74) != 0) {
                    func_8002D4C8(0x904, 0);
                    vec[0] = D_80126B5E;
                    vec[1] = D_80126B62;
                    vec[2] = D_80126B66;
                    func_8012F568(1, 0x1E, 0x400, 0x20, (s32)vec, (s32)D_801152A8);
                    M2C_FIELD(arg0, u16 *, 0xFC) = D_80126B62;
                }
            } else {
                func_8002D4C8(0x903, 0);
            }
        }
        break;

    case 1:
        M2C_FIELD(arg0, s32 *, 0x1C) += 0x80;
        t = func_8004787C(M2C_FIELD(arg0, s32 *, 0x1C)) >> 1;
        t += 0x1000;
        M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1A) = (s16)t;
        M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1C) = (s16)t;
        if (M2C_FIELD(arg0, s32 *, 0x1C) >= 0x800) {
            M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1A) = 0x1000;
            M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1C) = 0x1000;
            if (M2C_FIELD(arg0, s16 *, 0xFC) != 0) {
                M2C_FIELD(arg0, u16 *, 0x34) += 1;
                M2C_FIELD(D_801C7E30, s32 *, 0x1C) += 0x28;
            } else {
                M2C_FIELD(arg0, u16 *, 2) = 1;
            }
        }
        break;

    case 2:
        M2C_FIELD(arg0, s32 *, 0x1C) += 0x80;
        if (M2C_FIELD(arg0, s32 *, 0x1C) >= 0x1C00) {
            func_8012C658(0x274, (s16)(M2C_FIELD(arg0, u16 *, 0x70) | 0x10), arg0);
            M2C_FIELD(arg0, u16 *, 2) = 1;
        }
        break;
    }
}


extern s32 func_8004787C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u16 D_80126B62;

void func_80180450(s32 arg0) {
    register s32 t __asm__("$3"); /* pinned to $v1 */
    u16 state = M2C_FIELD(arg0, u16 *, 0x34);
    s16 cnt;
    struct { s32 d0, d1; } dead; /* reserved-at-expand slot -> frame 0x20 */

    switch (state) {
    case 0:
        M2C_FIELD(arg0, s32 *, 0x1C) += 0x80;
        t = func_8004787C(M2C_FIELD(arg0, s32 *, 0x1C)) >> 5;
        t += 0x1000;
        M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1A) = (s16)t;
        M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1C) = (s16)t;
        if (M2C_FIELD(arg0, s32 *, 0x1C) >= 0x800) {
            M2C_FIELD(arg0, s32 *, 0x1C) &= 0x7FF;
            cnt = M2C_FIELD(arg0, u16 *, 0xFC) - 1;
            M2C_FIELD(arg0, u16 *, 0xFC) = cnt;
            if (cnt == 0) {
                M2C_FIELD(arg0, u16 *, 0x34) += 1;
                if (*(u8 *)(*(s32 *)(arg0 + 0x6C) + 0x74) != 0) {
                    func_8002D4C8(0x904, 0);
                    M2C_FIELD(arg0, u16 *, 0xFC) = D_80126B62;
                }
            }
        }
        break;

    case 1:
        M2C_FIELD(arg0, s32 *, 0x1C) += 0x80;
        t = func_8004787C(M2C_FIELD(arg0, s32 *, 0x1C)) >> 2;
        t += 0x1000;
        M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1A) = (s16)t;
        M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1C) = (s16)t;
        if (M2C_FIELD(arg0, s32 *, 0x1C) >= 0x800) {
            M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1A) = 0x1000;
            M2C_FIELD(*(void **)(arg0 + 0x20), s16 *, 0x1C) = 0x1000;
            M2C_FIELD(arg0, u16 *, 2) = 1;
        }
        if (M2C_FIELD(arg0, s16 *, 0xFC) != 0 && M2C_FIELD(arg0, s32 *, 0x1C) < 0x401) {
            D_80126B62 = M2C_FIELD(arg0, u16 *, 0xFC) - (func_8004787C(M2C_FIELD(arg0, s32 *, 0x1C)) >> 5);
        }
        break;
    }
}



extern void (*D_80192568[])(void);

void func_801805D0(void *a0) {
    D_80192568[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012C588(s32 a0, s32 a1);
extern void (*D_801925B0[])(s32);

void func_8018060C(s32 param_1)
{
    if (*(s32 *)(param_1 + 0xE0) != 0) {
        *(s32 *)(param_1 + 0xE0) -= 1;
    } else {
        if ((*(s32 *)(param_1 + 0xDC) < 0x20) && (func_8012C588(0x2B5, param_1) != 0)) {
            *(s32 *)(param_1 + 0xDC) += 1;
        }
    }
    D_801925B0[*(u16 *)(param_1 + 2)](param_1);
}


typedef struct {
    u8 unk00[0x70];
    s16 unk70;
    s16 unk72;
    s16 unk74;
    s16 unk76;
    u8 pad78[0x84];
    s16 unkFC;
} Work;

extern void MoveImage(void *a0, s32 a1, s32 a2);
extern u8 D_801925C4[];
extern s16 D_80192614[];
extern s16 D_801926D4[];

void func_801806A0(Work *work, s32 arg1)
{
    s32 i;

    if (work->unk76 > 0) {
        for (i = 0; i < 5; i++) {
            if (work->unk76 >= D_801926D4[i]) {
                if (work->unkFC == i) {
                    return;
                }
                MoveImage(D_801925C4 + i * 0x10, work->unk70 * 0x10 + 0x2B0, 0x100);
                MoveImage(D_801925C4 + i * 0x10 + 8, 0x160, work->unk70 + 0x147);
                work->unkFC = i;
                return;
            }
        }
        return;
    }
    if (arg1 != 0) {
        if (work->unk76 == 0) {
            work->unk76 = 300;
            MoveImage(D_801925C4, work->unk70 * 0x10 + 0x2B0, 0x100);
            MoveImage(D_801925C4 + 8, 0x160, work->unk70 + 0x147);
            work->unkFC = 0;
            return;
        }
        if (work->unk76 >= -4) {
            MoveImage(&D_801926D4[work->unk76 * 8], work->unk70 * 0x10 + 0x2B0, 0x100);
            MoveImage(&D_801926D4[work->unk76 * 8 + 4], 0x160, work->unk70 + 0x147);
            return;
        }
    }
    MoveImage(&D_80192614[(work->unk76 & 7) * 8], work->unk70 * 0x10 + 0x2B0, 0x100);
    MoveImage(&D_80192614[(work->unk76 & 7) * 8 + 4], 0x160, work->unk70 + 0x147);
}


extern void (*D_80192724[])(void);
extern s16 D_801922B0[];
extern void *D_80126CC8;
extern s32 D_80126B6C;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8 D_801152A8[];
extern volatile s32 D_801C7E30;
extern void func_8012DFD4(u8 *a0);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_801806A0();

void func_80180854(s32 arg0)
{
    s16 *b5e = (s16 *)&D_80126B5E;
    s16 *b62 = (s16 *)&D_80126B62;
    s16 *p;
    s32 val;
    s16 x;
    s16 y;
    s16 t;
    s16 vecA[3];
    s16 vecB[3];

    D_80192724[*(u16 *)(arg0 + 2)]();
    if (*(u16 *)arg0 != 0) {
        if (D_80126CC8 == (void *)arg0) {
            *(s16 *)(arg0 + 6) = *(u16 *)(arg0 + 0x88);
            *(s16 *)(arg0 + 0xE) = *(u16 *)(arg0 + 0x8C);
            D_80126B62 = D_80126B62 - 0x40;
        }
        p = &D_801922B0[*(s16 *)(arg0 + 0x70) * 8];
        val = (s32)*(s16 *)(*(s32 *)(*(s32 *)(arg0 + 0x64) + 0x20) + 0x1A) * (s32)p[4];
        if (val < 0) {
            val += 0xFFF;
        }
        *(s16 *)(arg0 + 0xA) = (s16)(*(u16 *)(arg0 + 0x8A) + (val >> 12) - p[4]);
        func_8012DFD4((u8 *)arg0);
        if (*(u16 *)(D_801C7E30 + 2) < 0xA) {
            x = *(s16 *)(arg0 + 6);
            if (x + p[2] <= *b5e && *b5e <= x + p[3]) {
                y = *(s16 *)(arg0 + 0xA);
                if (y + p[4] < *b62) {
                    D_80126B62 = y + p[4];
                    D_80126B6C = 0;
                }
            }
        }
        t = *(s16 *)(arg0 + 0x76);
        if (t < 0x12C) {
            *(s16 *)(arg0 + 0x76) = t + 1;
        }
        if (*(u8 *)(arg0 + 0x74) != 0 && *(s16 *)(arg0 + 0x76) < 0) {
            vecA[0] = vecB[0] = D_80126B5E;
            vecA[1] = D_80126B62 + 0x10;
            vecB[1] = D_80126B62 - 0x10;
            vecA[2] = vecB[2] = D_80126B66;
            if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)vecA, (s32)vecB) != 0) {
                func_8012F568(1, 0x4004, 0x400, 0x14, (s32)vecB, (s32)D_801152A8);
            }
        }
        func_801806A0((void *)arg0, 1);
    }
}


extern void (*D_80192770[])(void);
extern s16 D_80192734;
extern void func_8012DFD4(u8 *a0);

void func_80180AA0(short *param_1) {
    s32 pad[4];
    s32 val;
    D_80192770[*(u16 *)((s32)param_1 + 2)]();
    if (*(u16 *)param_1 != 0) {
        u8 *arg = (u8 *)param_1;
        __asm__("" ::: "$4");
        val = (s32)*(s16 *)(*(s32 *)(*(s32 *)((s32)arg + 0x64) + 0x20) + 0x1A) * (s32)D_80192734;
        if (val < 0) {
            val += 0xFFF;
        }
        *(s16 *)(arg + 0xA) = (s16)(*(u16 *)(arg + 0x8A) + (val >> 12) - D_80192734);
        func_8012DFD4(arg);
    }
}


#include "common.h"

extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern s16 D_80126B5E_s __asm__("D_80126B5E");
extern s16 D_80126B62_s __asm__("D_80126B62");
extern u16 D_80126B66;
extern u8 D_801152A8[];
extern s32 rand(void);
extern s32 func_80047948(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);

void func_80180B44(s32 arg0)
{
    s16 vecA[3];
    s16 vecB[3];
    s32 i;
    s32 p;
    s32 r;

    if (*(s16 *)(arg0 + 0xFC) != 0x800) {
        *(s16 *)(arg0 + 0xFC) += 0x100;
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) = 0x900 - (func_80047948(*(s16 *)(arg0 + 0xFC)) >> 1);
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x900 - (func_80047948(*(s16 *)(arg0 + 0xFC)) >> 1);
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1C) = 0x900 - (func_80047948(*(s16 *)(arg0 + 0xFC)) >> 1);
        if (*(s16 *)(arg0 + 0xFC) == 0x400) {
            func_8002D4C8(0x80B, 0);
            for (i = 0; i < 0x10; i++) {
                p = func_8012C588(0x2ED, arg0);
                if (p != 0) {
                    r = (rand() & 0x7F) - 0x40;
                    *(s32 *)(p + 0x10) = r << 12;
                    *(u16 *)(p + 0x6) += r;
                    r = (rand() & 0x7F) - 0x40;
                    *(s32 *)(p + 0x18) = r << 12;
                    *(u16 *)(p + 0xE) += r;
                    *(u16 *)(p + 0xA) -= 0x80;
                    *(s16 *)(p + 0x16) = -0x18 - (rand() & 7);
                }
            }
        }
    } else if (*(s16 *)(arg0 + 0xFE) != 0) {
        *(s16 *)(arg0 + 0xFE) -= 1;
    } else {
        *(s16 *)(arg0 + 0xFC) += 0x100;
        func_8002D4C8(0x80C, 0);
    }

    if (*(s16 *)(arg0 + 0xFC) >= 0x1000) {
        func_8012C218((void *)arg0);
        return;
    }
    if ((*(u16 *)(arg0 + 0x70) & 0xF0) != 0) {
        if (*(s16 *)(arg0 + 0xFC) == 0x7F0) {
            func_8002D4C8(0xC8E, 0);
        }
        return;
    }
    r = D_80126B5E_s - *(s16 *)(arg0 + 6);
    if (r > -0x60 && r < 0x60) {
        r = *(s16 *)(arg0 + 0xA) - ((*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) * 11) >> 8);
        if (r < D_80126B62_s) {
            vecA[0] = vecB[0] = D_80126B5E_s;
            vecA[1] = D_80126B62_s + 0x10;
            vecB[1] = D_80126B62_s - 0x10;
            vecA[2] = vecB[2] = D_80126B66;
            if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)vecA, (s32)vecB) != 0) {
                func_8012F568(1, 0x4004, 0x400, 0x20, (s32)vecB, (s32)D_801152A8);
            }
        }
    }
}



extern void (*D_801927B8[])(void);

void func_80180DEC(void *a0) {
    D_801927B8[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8004787C(s32 a0);
extern s32 func_8017ECE4(s32 arg0);
extern void func_8012D624(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012B370(int a0);
extern s16 D_801C7E28;
extern s16 D_801C7E2C;
extern u16 D_8019244C[][2];

void func_80180E28(s32 param_1)
{
    s32 iVar1;

    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) -= 0x80;
    *(u16 *)(param_1 + 0x100) += 0x40;
    *(s32 *)(param_1 + 4) -= *(s32 *)(param_1 + 0x10);
    iVar1 = func_8004787C(*(s16 *)(param_1 + 0x100));
    *(s32 *)(param_1 + 8) = iVar1 * *(s16 *)(param_1 + 0xFE) * -0x10 - 0x700000;
    iVar1 = func_8017ECE4(param_1);
    if (iVar1 >= 1) {
        s32 child = *(s32 *)(param_1 + 0x20);
        s32 e28 = D_801C7E28;
        s16 val1E = 0x1E;

        *(u16 *)(child + 0x14) = 0;
        *(s16 *)(param_1 + 2) = 2;
        *(s16 *)(param_1 + 0xFE) = val1E;
        *(s16 *)(param_1 + 0xFC) = 0x400;
        if (e28 != 0) {
            D_801C7E2C = D_801C7E2C + 1;
            if (D_801C7E2C >= 9) {
                D_801C7E2C = 8;
            }
            D_801C7E28 = val1E;
            func_8002D4C8(D_8019244C[D_801C7E2C][0], 0);
        } else {
            D_801C7E28 = val1E;
            D_801C7E2C = 0;
            func_8002D4C8(0x896, 0);
        }
    } else {
        func_8012D624(param_1, 0x20, 0xC);
    }
    func_8012B370(param_1);
}
