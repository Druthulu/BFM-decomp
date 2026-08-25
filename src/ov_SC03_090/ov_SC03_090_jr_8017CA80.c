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
extern u8 D_8018DFC0;
extern u8 D_8018DF30;
extern u8 D_8018DF0C;
extern u8 D_8018DEE8;
extern u8 D_8018DF9C;
extern u8 D_8018DF78;
extern u8 D_8018DF54;
extern u8 D_8018DEC4;
extern void func_80145934(void);
extern u8 D_8018E050;
extern u8 D_8018E02C;
extern u8 D_8018E008;
extern u8 D_8018DFE4;
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
extern unsigned char D_8018D448[];
extern unsigned char D_8018D478[];
extern unsigned char D_8018D4C8[];
extern unsigned char D_8018D4F8[];
extern unsigned char D_8018D528[];
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
extern void (*D_8018D578[])(void *);
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
extern s32 D_8018D640[];
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
extern u8 D_8018D6C8[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018D6D0;
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
extern int D_801CAA30;
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
extern u8 D_801152A8[];
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern s32 D_801CAA34;
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
extern s32 D_8018D700;
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
extern void (*D_8018D7A8[])(void);
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
extern void (*D_8018D7CC[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_8018D7BC;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018D7E0[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_8018D7EC[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_8018D7FC[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8018D814[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8018D804;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_8018D828[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_8018D844[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8018D834;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_8018D858[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_8018D86C[])(void);
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
extern s32 D_8018D880;
extern void (*D_8018D8A8[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8018D888;
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
extern int (*D_8018D8F4[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8018D8F8[])(void);
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
extern unsigned short D_8018DD5C[];
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
extern void (*D_8018DD6C[])(void);
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
extern int D_801CAA68;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_8018DD94[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_8018DD74;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_8018DD84;
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
extern void (*D_8018DDD4[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_8018DDDC[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8018DDA8;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8018DDE8[])(void);
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
extern u8 D_8018DDB8;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801CAA70;
extern s32 D_801CAA7C;
extern s32 D_801CAA80;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_8018DE24[])(s32 *);
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
extern s32 D_8018DDF8[];
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
extern s32 D_801CAA78;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_8018E074[])(void);
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
extern char D_8018DE94[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_8018E118[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_8018E26C[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_8018E088;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_8018E274[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_8018E098;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_8018E0B8;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_8018E27C[])(void);
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
extern void (*D_8018E2A4[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018E2B0[])(void);
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
extern void (*D_8018E124[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_8018E354;
extern void func_8015D380(s32 a0);
extern unsigned char D_8018D438[];
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
extern unsigned char D_8018E368[];
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
extern s8 D_8018E3A4[];
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
extern u16 D_8018E3EC;
extern u16 D_8018E3EE;
extern u16 D_8018E3F0;
extern s32 D_8018E3F4;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_8018E3FC;
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
extern int D_8018E108;
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
extern unsigned int D_8018E480[];
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
extern void (*D_8018E530[])(void);
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
extern u16 D_8018E560[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8018E5C4;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801CAA88[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_8018E5E8[])(void);
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
extern int D_801CAAE0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_8018E630[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_8018E620;
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
extern char D_801CA2F8[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_8018E638[])(void);
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
extern void (*D_8018E68C[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_8018E654;
extern s16 D_8018E688;
extern s16 D_8018E686;
extern s16 D_8018E684;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8018E698[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801CAB40;
extern u8 D_801CAB41;
extern u8 D_801CAB42;
extern u8 D_801CAB43;
extern u8 D_801CAB44;
extern u8 D_801CAB45;
extern u8 D_801CAB46;
extern u8 D_801CAB47;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8018E6A8[])(void);
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
extern s32 D_801CAB80;
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
extern void (*D_8018E6EC[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8018E768[];
extern s32 D_8018E788[];
extern u8 D_8018E804[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8018E824[];
extern u8 D_8018E844[];
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
extern void (*D_8018E8E0[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_8018E95C[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801CA308;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8018E968[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018E970[])(void);
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
extern void (*D_8018EA38[])(void);
extern void func_80166618(void *a0);
extern void (*D_8018EA48[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_8018EA58[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_8018EA64[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8018E9C4[];
extern u8   D_8018E9D8[];
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
extern void (*D_8018EA7C[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_8018EA84[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_8018EA8C[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_8018EA94[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_8018EA9C[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8018EAA4[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_8018EAAC[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_8018EB60[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8018EB68[])(void);
extern void func_80169F00(void *a0);
extern char D_8018EB18[];
extern char D_8018EAD8[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_8018EBA0[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_8018EBAC[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8018EBF4[])(void);
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
extern void (*D_8018EC70[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801CAEA0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_8018EC64[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8018ECA8[];
extern unsigned short D_8018ECB0[];
extern unsigned short D_8018ECB8[];
extern unsigned char D_801CAEA8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801CAEA0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_8018ECC0[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801CAFDC;
extern M2C_UNK D_801CAFE0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801CAF68;
extern void (*D_8018ECF0[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801CAFE4[];
extern u8 D_801CAFEC[];
extern u8 D_801CAF9C[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8018ECF8[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_8018ED14[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_8018ED1C[])(void);
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
extern void (*D_8018ED84[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018ED28;
extern u8 D_8018ED34;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8018EDB8[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_8018EDC0[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_8018EE14[])(void);
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
extern u16 D_8018EE48[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_8018EE38[];
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
extern s32 D_8018EE64;
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
extern void (*D_8018EEDC[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_8018EEE4[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_8018EEEC[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_8018EEF4[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_8018EEFC[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_8018EF04[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_8018EF10[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_8018EF1C[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_8018EF28[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_8018EF38[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_8018EF48[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_8018EF50[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_8018EF58[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_8018EF60[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8018EF68[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_8018EF70[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8018EF78[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_8018EF80[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8018EF88[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_8018EF90[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8018EF98[])(void);
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
extern void (*D_8018EFA0[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8018EFA8[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_8018EFB0[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8018EFB8[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_8018EFC0[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8018EFC8[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_8018EFD0[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8018EFD8[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_8018EFE0[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8018EFE8[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_8018EFF0[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8018EFF8[])(void);
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
extern void (*D_8018F03C[])(void);
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
extern M2C_UNK D_8018F000;
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
extern void (*D_8018F06C[])(void);
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
extern void (*D_8018F0A8[])(void);
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
extern s32 D_80126950;
extern void func_801748EC(void);
extern s32 func_801749C8();
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_8018F100[])();
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
extern void (*D_8018F110[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_8018F118[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018F280[])();
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
extern void (*D_8018F28C[])();
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
extern M2C_UNK D_801CA550;
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
extern s16 D_801CBD18;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801CB720;
extern short D_801CBD8C;
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
extern s32 D_801CBB4C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801CBB74;
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
extern s16 D_801CBB30;
extern s32 func_8017A3B0(void);
extern short D_801CBB6C;
extern short D_801CBB68;
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
extern s16 D_801CBB34;
extern u16 D_801CBBB4;
extern u16 D_801CBBB6;
extern u16 D_801CBBB8;
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
extern s16 D_801CBBAC;
extern s16 D_801CBBAE;
extern s16 D_801CBBB0;
extern s16 D_801CBBA4;
extern s16 D_801CBBA6;
extern s16 D_801CBBA8;
extern void func_8017B7A8(void);
extern s16 D_801CBBC4;
extern s16 D_801CBBC6;
extern s16 D_801CBBC8;
extern s16 D_801CBBCC;
extern s16 D_801CBBCE;
extern s16 D_801CBBD0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801CBBBC;
extern short D_801CBBBE;
extern short D_801CBBC0;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801CBB54;
extern SV4 D_801CBB5C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801CBB7C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801CBB78)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018F468[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8018F4A0[])(void);
extern void func_8017BEF8(void *a0);
extern void (*D_8018F4B4[])(void);
extern void func_8017C524(void *a0);
extern void (*D_8018F4C8[])(void);
extern void func_8017C7C4(void *a0);
/* ==== end §8b carried decl layer ==== */

/* func_8017CA80 — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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

void func_8017CA80(s32 arg0)
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


#include "common.h"
#include "../shared/engine_types.h"

/* ===========================================================================
 * func_8017D960 -- 3,338 ins, ov_SC03_090 (behemoth #2).   *** MATCHED ***
 *
 * STATUS (2026-07-25, session 20, gcc-2.7.2 pinned triple):
 *   python3 tools/match_one.py func_8017D960 --c <this file> \
 *     --asm-subdir asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80
 *   -> MATCH (3338 ins)          symcheck -> SYMS-OK, 21 symbols agree
 *   b3_align: register-MASKED 3338/3338 = 100.0%, register-KEPT 3338/3338 = 100.0%
 *   PIN-FREE (the five `register __asm__` pins of the b2 draft are GONE).
 *   match_one is the CANDIDATE gate; the whole-binary SHA1 rebuild (G3/P9) is the
 *   arbiter and has NOT been run here (the task forbade touching the build tree).
 *
 * WHAT IT IS (decoded in s18, unchanged):
 *   The *3-point volumetric-light* variant of func_8017CA80 (952 ins, MATCHED,
 *   same TU, immediately preceding it in the binary).  Identical skeleton:
 *   same 3-call prologue (func_800491EC / func_800547D8 / func_80052E38),
 *   same Part[] outer loop (stride 0x14) with the 8-corner AABB rtpt/rtpt+
 *   rtps/rtps + otz + screen-bbox reject, same Prim[] inner loop (stride 0xC)
 *   with rtpt/stflg/nclip/stopz, same OT insertion, same `D_800A5E60 = pkt`.
 *
 *   Differences vs func_8017CA80:
 *     - only prim codes 2,3 (quad) and 6,7 (tri) are drawn; 0,1,4,5 are dropped
 *       (the untextured F3/F4 cases of the sibling).
 *     - screen Y clip is -0x6E..0x6F (not -0x78..0x79).
 *     - no `code&1 ? +0x200` OT bias.
 *     - THE ADDED WORK: 3 axis-aligned "light boxes" read out of D_801CBC68 /
 *       D_801CBC84 / D_801CBCA0 ({s32 enable; u16 cx,cy,cz; s32 range}).  Per
 *       prim, each vertex is range-tested against all 3 boxes (OR-accumulated
 *       into 3 flags); then per vertex a 0..0x80 attenuation is computed per
 *       active box as a separable per-axis linear falloff over the outer 0x80
 *       of the range (axes visited x, z, y), the three summed and clamped to
 *       0x80, and the result becomes a grey gouraud vertex colour.
 *     - lit  -> POLY_GT3 (0x28, OT 0x9000000, GPU 0x34) / POLY_GT4 (0x34, OT
 *       0xC000000, GPU 0x3C)
 *       unlit -> POLY_FT3 (0x20, OT 0x7000000) / POLY_FT4 (0x28, OT 0x9000000)
 *       with rgbc = tp[0] & 0xFF000000 (i.e. black).
 *
 * Frame: 0x320 = 0x00 args | 0x10 tmpxy[4] | 0x20 box[8] | 0x60 sxy[8] |
 *   0xA0 mtx | 0xC0 g{otz,flag,opz,sz0..sz3} | 0xE0..0x2F7 spill slots |
 *   0x2F8..0x31F saved regs (s0-s7, fp, ra).
 *
 * ---------------------------------------------------------------------------
 * THE NINE LEVERS THAT TOOK b2 (3334 ins / 1806 mismatched) TO MATCH.
 * Every one is individually NECESSARY -- drop-one ablation measured, see
 * .run/giants/s19_d960_report.md.  Eight of the nine are ALLOCNO-CLASS or
 * VARIABLE-REUSE levers (cookbook Sec.76); none is reachable by the permuter.
 *
 * L1  `u32 *otp;` DECLARED PER EMIT ARM (all four), not at function scope.
 *     3334 -> 3338 ins: THIS ALONE FIXED THE ENTIRE -4 LENGTH DRIFT.
 *     WHY: at function scope otp has 4 deaths, so local-alloc.c:472
 *     (REG_BASIC_BLOCK >= 0 && REG_N_DEATHS == 1) refuses it -> global allocno
 *     -> combine_regs (local-alloc.c:1825) cannot tie the (g.opz>>2)<<2 chain
 *     into it, otp squats in $a2, and (global.c:668-671) that hard-reg mark
 *     pushes the per-tail 0xFFFFFF constant OFF $a1 and into $a0 -- where it is
 *     free early enough to be hoisted into the FIRST tp[] load-delay slot.
 *     The target instead materialises 0xFFFFFF in $a1 only AFTER tp ($a1) dies,
 *     so its first load-delay slot stays a real `nop`.  4 emit tails x 1 nop
 *     = the whole -4.  (The prior "one fold OR-chain error left" reading of the
 *     -4 was wrong: the drift was never in the colour chain.)
 * L2  NO REGISTER PINS.  The five b2 pins ($25/$17/$19/$20/$21 on r1/r2/r0lo/
 *     r1lo/r2lo) are removed; gcc reproduces the target light-box allocation on
 *     its own once L1..L9 are in place.  (A pin is a PREFERENCE, not a
 *     reservation -- cookbook Sec.72.)
 * L3  `u32 vw, vzw;` -- DEDICATED vertex-word temps instead of reusing w/wz.
 *     w/wz are also the prim-word and part->zz temps; reusing them inflates
 *     their allocno_compare ref count (global.c:594, refs counted x loop depth
 *     = x3 here) so they outrank the scratch pool and the vertex word lands in
 *     $a1/$a0 instead of the target's $v0/$a1.  106 vs 190 mismatched.
 * L4  RC-15 ZERO-BYTE REF DIAL on `mny`, first statement inside the TRI cull
 *     block.  Same lever as func_8017F510 L4: `mny` is defined FIRST but has the
 *     LONGER live range, so allocno_compare ranks `my` above it and `my` takes
 *     the lower $a2; the dial adds reg_n_refs += 3 (loop depth 3) to `mny` and
 *     flips the grant to the target's mny->$a2 / my->$a3.  Emits only
 *     #APP/#NO_APP.  Placement is load-bearing (Sec.RC-11): at a cull-block head
 *     it is byte-free; inside the box-build statement stream it costs +9.
 *     67 vs 106 mismatched; in BOTH cull blocks it is 70 (worse) -- tri only.
 * L5  `base = D_800AF630;` HOISTED TO THE FIRST STATEMENT of the function
 *     (before the three calls), as in the matched sibling func_8017F510.
 *     Makes the address a call-crossing allocno -> callee-saved $s0 (target)
 *     instead of $v1, and fixes the D_800A6610 / `sw $s7` emission order.
 * L6  `f2 = 0; f1 = 0; f0 = 0;` -- the three box flags cleared in REVERSE
 *     source order (2 x 2 ins: $s2/$t6 init order).
 * L7  `u32 cb;` -- ONE shared "colour base" holding BOTH the poly tag constant
 *     in the lit arms (`cb = 0x34000000` / `0x3C000000`) AND `tp[0]&0xFF000000`
 *     in the unlit arms; the lit chain is `rgbw = (c | cb) | (c<<8) | (c<<16)`.
 *     TWO separate effects:
 *       (a) STRUCTURE.  With a literal tag, gcc-2.7.2 `fold`'s associate: block
 *           (fold-const.c, split_tree) hoists the constant OUT of the first
 *           `|`: `(c|K)|(c<<8)|(c<<16)` is rewritten to `c | ((c<<8)|K) |
 *           (c<<16)` -- 5 ins in the wrong operand shape, at all 7 sites, in
 *           EVERY parenthesisation tried (7 measured, see report).  A VARIABLE
 *           tag is opaque to fold, so the target's `or acc,c,cb / sll t,c,8 /
 *           or / sll t,c,16 / or` falls out.
 *       (b) ALLOCATION.  cb also carrying the unlit rgbc raises its ref count
 *           enough to take $a0 there (`and $a0,$v0,$a2`), which the target has
 *           and a dedicated single-purpose temp never gets.
 * L8  `u32 rgbw;` -- ONE shared function-scope temp for the lit rgb word,
 *     written then stored.  Routing the result through a MULTI-death variable
 *     stops local-alloc tying the whole chain into one high-priority qty
 *     (qty_compare, local-alloc.c:1579: floor_log2(refs)*refs/(death-birth) =
 *     2*6/5 = 24000 for the tied chain vs 20000 for each `sll` temp), so the
 *     temp is granted first and takes $v0, leaving the accumulator $v1 -- the
 *     target's assignment.  33 vs 54 mismatched.  (Same lever as f510 L3.)
 * L9  `s32 za, zb;` DECLARED PER CASE (inside both innermost cull blocks), as
 *     in the matched sibling func_8017CA80.  Last 8 ins: it flips the quad
 *     z-max grant from za->$v1 / sz1-temp->$a0 to the target's za->$a0 /
 *     sz1-temp->$v1.  8 -> 0.
 *
 * TEMPLATES TO (all 3,338 ins, identical global-symbol shape; only the three
 * light-descriptor symbols change):
 *   func_8017D960 @ ov_SC03_089, ov_SC03_104
 *   func_8017E778 @ ov_SC03_091 (D_801D25B8 / D_801D25D4 / D_801D25F0)
 *   func_8017CD9C @ ov_SC03_102 (D_801B9B00 / D_801B9B1C / D_801B9B38)
 * =========================================================================== */

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

/* ---- the two gouraud-textured packet layouts this function emits ---------- */
                                      /* 0x28 */

                                      /* 0x34 */

/* ---- the three light-volume descriptors ---------------------------------- */
extern s32 D_801CBC68;
extern u16 D_801CBC6C, D_801CBC6E, D_801CBC70;
extern s32 D_801CBC74;
extern s32 D_801CBC84;
extern u16 D_801CBC88, D_801CBC8A, D_801CBC8C;
extern s32 D_801CBC90;
extern s32 D_801CBCA0;
extern u16 D_801CBCA4, D_801CBCA6, D_801CBCA8;
extern s32 D_801CBCAC;

/* ---- the box-containment test for one vertex against one light box ------- */
#define BOXTEST(F, X, Y, Z, LX, HX, LY, HY, LZ, HZ) \
    if ((LX) < (X) && (X) < (HX) && (LY) < (Y) && (Y) < (HY) && (LZ) < (Z) && (Z) < (HZ)) F = 1

/* ---- the separable per-axis falloff, visited in x, z, y order ------------ */
#define ATTEN(A, F, X, Y, Z, CX, CY, CZ, R, RLO)                \
    A = 0;                                                      \
    if (F) {                                                    \
        d = (X) - (CX);   if (d < 0) d = (CX) - (X);            \
        if (d < (R)) { A = 0x80; if (d >= (RLO)) A = (R) - d; } \
        d = (Z) - (CZ);   if (d < 0) d = (CZ) - (Z);            \
        if ((R) < d) A = 0;                                     \
        else if ((RLO) < d) A = (A * ((R) - d)) >> 7;           \
        d = (Y) - (CY);   if (d < 0) d = (CY) - (Y);            \
        if ((R) < d) A = 0;                                     \
        else if ((RLO) < d) A = (A * ((R) - d)) >> 7;           \
    }

#define CLAMP80(C, A0, A1, A2)  C = (A0) + (A1) + (A2); if ((C) > 0x80) C = 0x80

void func_8017D960(s32 arg0)
{
    typedef struct { u32 w0, w1, w2; } Prim;

    extern s32 func_800491EC(void);
    extern void func_800547D8(s32, MATRIX2 *);
    extern void func_80052E38(MATRIX2 *);
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern u8 D_800AF630[];

    DVECTOR2 tmpxy[4];
    SVECTOR2 box[8];
    SVECTOR2 sxy[8];
    MATRIX2 mtx;
    struct { long otz, flag, opz, sz0, sz1, sz2, sz3; } g;

    s32 lim;
    s32 j;
    u32 i;
    u8 *vd;
    u32 ot;
    u8 *pkt;
    s16 x3, z3, y3;
    Prim *prim;
    u32 nprim;
    u8 *vtx;
    s32 nparts;
    Part *part;
    s16 lo0x, hi0x, lo0y, hi0y, lo0z, hi0z;
    s16 lo1x, hi1x, lo1y, hi1y, lo1z, hi1z;
    s16 lo2x, hi2x, lo2y, hi2y, lo2z, hi2z;
    s16 cx0, cy0, cz0, cx1, cy1, cz1, cx2, cy2, cz2;
    s16 r0;
    s16 r1;
    s16 r2;
    s16 r0lo;
    s16 r1lo;
    s16 r2lo;
    u8 *va, *vb, *vc;
    u32 w; s32 code;
    u32 vw, vzw;
    u32 wx, wy, wz;
    s32 xa32, xb32, t32;
    s32 xmn1, xmx1, xmn2, xmx2;
    s32 mnc, mxc;
    s16 my, mny, mx, mn;
    u8 *base;
    s32 f0, f1, f2;
    s16 x0, y0, z0, x1, y1, z1, x2, y2, z2;
    s32 a0v, a1v, a2v;
    s32 d;
    s32 c0, c1, c2, c3;
    u32 *tp;
    u32 uvw;
    u32 cb;
    u32 rgbw;

    base = D_800AF630;
    lim = func_800491EC() + *(s32 *)(arg0 + 0x64);
    func_800547D8(arg0 + 0x10, &mtx);
    func_80052E38(&mtx);

    r2lo = 0;
    r1lo = 0;
    r0lo = 0;
    r2 = 0;
    r1 = 0;
    r0 = 0;

    if (D_801CBC68) {
        cx0 = D_801CBC6C;
        cy0 = D_801CBC6E;
        r0lo = D_801CBC74 - 0x80;
        r0 = D_801CBC74;
        cz0 = D_801CBC70;
    } else {
        cz0 = 0x6000;
        cy0 = 0x6000;
        cx0 = 0x6000;
    }
    if (D_801CBC84) {
        cx1 = D_801CBC88;
        cy1 = D_801CBC8A;
        r1 = D_801CBC90;
        r1lo = D_801CBC90 - 0x80;
        cz1 = D_801CBC8C;
    } else {
        cz1 = 0x6000;
        cy1 = 0x6000;
        cx1 = 0x6000;
    }
    if (D_801CBCA0) {
        cx2 = D_801CBCA4;
        cy2 = D_801CBCA6;
        r2 = D_801CBCAC;
        r2lo = D_801CBCAC - 0x80;
        cz2 = D_801CBCA8;
    } else {
        cz2 = 0x6000;
        cy2 = 0x6000;
        cx2 = 0x6000;
    }

    lo0x = cx0 - r0;  hi0x = cx0 + r0;
    lo0y = cy0 - r0;  hi0y = cy0 + r0;
    lo0z = cz0 - r0;  hi0z = cz0 + r0;
    lo1x = cx1 - r1;  hi1x = cx1 + r1;
    lo1y = cy1 - r1;  hi1y = cy1 + r1;
    lo1z = cz1 - r1;  hi1z = cz1 + r1;
    lo2x = cx2 - r2;  hi2x = cx2 + r2;
    lo2y = cy2 - r2;  hi2y = cy2 + r2;
    lo2z = cz2 - r2;  hi2z = cz2 + r2;

    pkt = D_800A5E60;
    part = *(Part **)(arg0 + 0xC);
    nparts = *(s32 *)(*(s32 *)(arg0 + 8) + 8);
    vtx = *(u8 **)(*(s32 *)(arg0 + 8) + 0x10);
    ot = (u32)&D_800A6610[(*(u16 *)(base + 0xA3D2)) << 14];

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
                if ((s16)mxc >= -0x6E && (s16)mnc < 0x6F) {
                    nprim = part->nprim;
                    prim = (Prim *)part->prim;
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
                                case 6:
                                case 7:
                                    /* ---------------- TRI (FT3 / GT3) ---------------- */
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_stsz3(&g.sz0, &g.sz1, &g.sz2);
                                    if (tmpxy[0].vx > tmpxy[1].vx) { mx = tmpxy[0].vx; mn = tmpxy[1].vx; }
                                    else { mn = tmpxy[0].vx; mx = tmpxy[1].vx; }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (mx >= -0xA0 && mn < 0xA1) {
                                        if (tmpxy[0].vy > tmpxy[1].vy) { my = tmpxy[0].vy; mny = tmpxy[1].vy; }
                                        else { mny = tmpxy[0].vy; my = tmpxy[1].vy; }
                                        if (tmpxy[2].vy > my) my = tmpxy[2].vy;
                                        else if (tmpxy[2].vy < mny) mny = tmpxy[2].vy;
                                        if (my >= -0x6E && mny < 0x6F) {
                                            s32 za, zb;
                                            __asm__ __volatile__ ("" :: "r" (mny));
                                            if (g.sz0 > g.sz1) { za = g.sz0; if (za < g.sz2) za = g.sz2; }
                                            else { za = g.sz1; if (za < g.sz2) za = g.sz2; }
                                            g.opz = za;

                                            f2 = 0; f1 = 0; f0 = 0;

                                            vw = *(u32 *)va;
                                            vzw = *(u32 *)(va + 4);
                                            x0 = vw; y0 = vw >> 16; z0 = vzw;
                                            BOXTEST(f0, x0, y0, z0, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                            BOXTEST(f1, x0, y0, z0, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                            BOXTEST(f2, x0, y0, z0, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                            vw = *(u32 *)vb;
                                            vzw = *(u32 *)(vb + 4);
                                            x1 = vw; y1 = vw >> 16; z1 = vzw;
                                            BOXTEST(f0, x1, y1, z1, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                            BOXTEST(f1, x1, y1, z1, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                            BOXTEST(f2, x1, y1, z1, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                            vw = *(u32 *)vc;
                                            vzw = *(u32 *)(vc + 4);
                                            x2 = vw; y2 = vw >> 16; z2 = vzw;
                                            BOXTEST(f0, x2, y2, z2, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                            BOXTEST(f1, x2, y2, z2, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                            BOXTEST(f2, x2, y2, z2, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);

                                            if (f0 | f1 | f2) {
                                            u32 *otp;
                                                ATTEN(a0v, f0, x0, y0, z0, cx0, cy0, cz0, r0, r0lo);
                                                ATTEN(a1v, f1, x0, y0, z0, cx1, cy1, cz1, r1, r1lo);
                                                ATTEN(a2v, f2, x0, y0, z0, cx2, cy2, cz2, r2, r2lo);
                                                CLAMP80(c0, a0v, a1v, a2v);
                                                ATTEN(a0v, f0, x1, y1, z1, cx0, cy0, cz0, r0, r0lo);
                                                ATTEN(a1v, f1, x1, y1, z1, cx1, cy1, cz1, r1, r1lo);
                                                ATTEN(a2v, f2, x1, y1, z1, cx2, cy2, cz2, r2, r2lo);
                                                CLAMP80(c1, a0v, a1v, a2v);
                                                ATTEN(a0v, f0, x2, y2, z2, cx0, cy0, cz0, r0, r0lo);
                                                ATTEN(a1v, f1, x2, y2, z2, cx1, cy1, cz1, r1, r1lo);
                                                ATTEN(a2v, f2, x2, y2, z2, cx2, cy2, cz2, r2, r2lo);
                                                CLAMP80(c2, a0v, a1v, a2v);

                                                *(u32 *)&((PolyGT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyGT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyGT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                cb = 0x34000000;
                                                rgbw = (c0 | cb) | (c0 << 8) | (c0 << 16);
                                                ((PolyGT3 *)pkt)->rgb0 = rgbw;
                                                rgbw = (c1 | cb) | (c1 << 8) | (c1 << 16);
                                                ((PolyGT3 *)pkt)->rgb1 = rgbw;
                                                rgbw = (c2 | cb) | (c2 << 8) | (c2 << 16);
                                                ((PolyGT3 *)pkt)->rgb2 = rgbw;
                                                ((PolyGT3 *)pkt)->uv0 = tp[1];
                                                ((PolyGT3 *)pkt)->uv1 = tp[2];
                                                ((PolyGT3 *)pkt)->uv2 = tp[3];
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x9000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x28;
                                            } else {
                                            u32 *otp;
                                                *(u32 *)&((PolyFT3 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                *(u32 *)&((PolyFT3 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                *(u32 *)&((PolyFT3 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                tp = (u32 *)prim->w0;
                                                cb = tp[0] & 0xFF000000;
                                                ((PolyFT3 *)pkt)->rgbc = cb;
                                                ((PolyFT3 *)pkt)->uvc0 = tp[1];
                                                ((PolyFT3 *)pkt)->uvp1 = tp[2];
                                                ((PolyFT3 *)pkt)->uv2 = tp[3];
                                                otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                *(u32 *)pkt = (*otp & 0xFFFFFF) | 0x7000000;
                                                *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                pkt += 0x20;
                                            }
                                        }
                                    }
                                    break;
                                case 2:
                                case 3:
                                    /* ---------------- QUAD (FT4 / GT4) ---------------- */
                                    gte_stsxy3c(&tmpxy[0]);
                                    gte_ldv0(vd);
                                    gte_rtps();
                                    if (tmpxy[0].vx > tmpxy[1].vx) { mx = tmpxy[0].vx; mn = tmpxy[1].vx; }
                                    else { mn = tmpxy[0].vx; mx = tmpxy[1].vx; }
                                    if (tmpxy[2].vx > mx) mx = tmpxy[2].vx;
                                    else if (tmpxy[2].vx < mn) mn = tmpxy[2].vx;
                                    if (tmpxy[0].vy > tmpxy[1].vy) { my = tmpxy[0].vy; mny = tmpxy[1].vy; }
                                    else { mny = tmpxy[0].vy; my = tmpxy[1].vy; }
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
                                            if (my >= -0x6E && mny < 0x6F) {
                                                s32 za, zb;
                                                zb = g.sz2;
                                                if (zb < g.sz3) zb = g.sz3;
                                                za = g.sz0;
                                                if (za < g.sz1) za = g.sz1;
                                                if (za < zb) za = zb;
                                                g.opz = za;

                                                f2 = 0; f1 = 0; f0 = 0;

                                                vw = *(u32 *)va;
                                                vzw = *(u32 *)(va + 4);
                                                x0 = vw; y0 = vw >> 16; z0 = vzw;
                                                BOXTEST(f0, x0, y0, z0, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x0, y0, z0, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x0, y0, z0, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                                vw = *(u32 *)vb;
                                                vzw = *(u32 *)(vb + 4);
                                                x1 = vw; y1 = vw >> 16; z1 = vzw;
                                                BOXTEST(f0, x1, y1, z1, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x1, y1, z1, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x1, y1, z1, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                                vw = *(u32 *)vc;
                                                vzw = *(u32 *)(vc + 4);
                                                x2 = vw; y2 = vw >> 16; z2 = vzw;
                                                BOXTEST(f0, x2, y2, z2, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x2, y2, z2, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x2, y2, z2, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);
                                                vw = *(u32 *)vd;
                                                vzw = *(u32 *)(vd + 4);
                                                x3 = vw; y3 = vw >> 16; z3 = vzw;
                                                BOXTEST(f0, x3, y3, z3, lo0x, hi0x, lo0y, hi0y, lo0z, hi0z);
                                                BOXTEST(f1, x3, y3, z3, lo1x, hi1x, lo1y, hi1y, lo1z, hi1z);
                                                BOXTEST(f2, x3, y3, z3, lo2x, hi2x, lo2y, hi2y, lo2z, hi2z);

                                                if (f0 | f1 | f2) {
                                                u32 *otp;
                                                    ATTEN(a0v, f0, x0, y0, z0, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x0, y0, z0, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x0, y0, z0, cx2, cy2, cz2, r2, r2lo);
                                                    CLAMP80(c0, a0v, a1v, a2v);
                                                    ATTEN(a0v, f0, x1, y1, z1, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x1, y1, z1, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x1, y1, z1, cx2, cy2, cz2, r2, r2lo);
                                                    CLAMP80(c1, a0v, a1v, a2v);
                                                    ATTEN(a0v, f0, x2, y2, z2, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x2, y2, z2, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x2, y2, z2, cx2, cy2, cz2, r2, r2lo);
                                                    CLAMP80(c2, a0v, a1v, a2v);
                                                    ATTEN(a0v, f0, x3, y3, z3, cx0, cy0, cz0, r0, r0lo);
                                                    ATTEN(a1v, f1, x3, y3, z3, cx1, cy1, cz1, r1, r1lo);
                                                    ATTEN(a2v, f2, x3, y3, z3, cx2, cy2, cz2, r2, r2lo);
                                                    CLAMP80(c3, a0v, a1v, a2v);

                                                    *(u32 *)&((PolyGT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                    *(u32 *)&((PolyGT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                    *(u32 *)&((PolyGT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                    gte_stsxy((long *)&((PolyGT4 *)pkt)->x3);
                                                    tp = (u32 *)prim->w0;
                                                    cb = 0x3C000000;
                                                    rgbw = (c0 | cb) | (c0 << 8) | (c0 << 16);
                                                    ((PolyGT4 *)pkt)->rgb0 = rgbw;
                                                    rgbw = (c1 | cb) | (c1 << 8) | (c1 << 16);
                                                    ((PolyGT4 *)pkt)->rgb1 = rgbw;
                                                    rgbw = (c2 | cb) | (c2 << 8) | (c2 << 16);
                                                    ((PolyGT4 *)pkt)->rgb2 = rgbw;
                                                    rgbw = (c3 | cb) | (c3 << 8) | (c3 << 16);
                                                    ((PolyGT4 *)pkt)->rgb3 = rgbw;
                                                    ((PolyGT4 *)pkt)->uv0 = tp[1];
                                                    ((PolyGT4 *)pkt)->uv1 = tp[2];
                                                    uvw = tp[3];
                                                    ((PolyGT4 *)pkt)->uv2 = uvw;
                                                    ((PolyGT4 *)pkt)->uv3 = uvw >> 16;
                                                    otp = (u32 *)(((g.opz >> 2) << 2) + ot);
                                                    *(u32 *)pkt = (*otp & 0xFFFFFF) | 0xC000000;
                                                    *otp = (*otp & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                                                    pkt += 0x34;
                                                } else {
                                                u32 *otp;
                                                    *(u32 *)&((PolyFT4 *)pkt)->x0 = *(u32 *)&tmpxy[0];
                                                    *(u32 *)&((PolyFT4 *)pkt)->x1 = *(u32 *)&tmpxy[1];
                                                    *(u32 *)&((PolyFT4 *)pkt)->x2 = *(u32 *)&tmpxy[2];
                                                    tp = (u32 *)prim->w0;
                                                    cb = tp[0] & 0xFF000000;
                                                    ((PolyFT4 *)pkt)->rgbc = cb;
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




extern int func_80181ED0(int param_1);

void func_80180D88(void) {

    extern const void D_8018F898;
    extern const void D_8018F9B0;
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_801274C8 = (u8 *)&D_8018F898;
    D_801274CC = (void *)&D_8018F9B0;
    func_80181ED0(0);
}



extern int func_80181ED0(int param_1);

void func_80180DC8(void)
{

    extern u8 D_8018F9C4[];
    extern u8 D_8018FA8C[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_801274C8 = D_8018F9C4;
    D_801274CC = D_8018FA8C;
    func_80181ED0(1);
}



extern int func_80181ED0(int param_1);

void func_80180E08(void)
{

    extern u8 D_8018FAA0[];
    extern u8 D_8018FB54[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_801274C8 = D_8018FAA0;
    D_801274CC = D_8018FB54;
    func_80181ED0(2);
}



extern int func_80181ED0(int param_1);

void func_80180E48(void)
{

    extern u8 D_8018FB68[];
    extern u8 D_8018FCBC[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_801274C8 = D_8018FB68;
    D_801274CC = D_8018FCBC;
    func_80181ED0(3);
}



extern int func_80181ED0(int param_1);

void func_80180E88(void)
{

    extern u8 D_8018FCD0[];
    extern u8 D_8018FDD4[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 *D_801274C8;
    extern void *D_801274CC;
    D_801274C8 = D_8018FCD0;
    D_801274CC = D_8018FDD4;
    func_80181ED0(4);
}



extern void (*D_8018F6F0[])(void);

void func_80180EC8(void *a0) {
    D_8018F6F0[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_801812F4(void);
extern void func_800167B8(s32 a0);

s32 func_80180F04(s32 a0) {
    func_801812F4();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_80180F48(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_8018F6F8[])(void);

void func_80180F6C(void *a0) {
    D_8018F6F8[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8018131C(void);

s32 func_80180FA8(s32 a0) {
    func_8018131C();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_80180FE8(u8 *a0) {
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
    void func_80181064(void) {
        ((s32 (*)(void))func_800D1EBC)();
    }



extern void (*D_8018F704[])(void);

void func_80181084(void *a0) {
    D_8018F704[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_801810C0(s32 a0) {
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



extern void (*D_8018F710[])(void);

void func_80181134(void *a0) {
    D_8018F710[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_80181450(void);
extern void func_800167B8(s32 a0);

s32 func_80181170(s32 a0) {
    func_80181450();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}


extern s32 D_80126B58;

s32 func_801811B4(void) {
    if ((func_800167F0(0) & 0xFFFF) == 0) {
        return 0;
    }
    func_80171990((u8 *)&D_80126B58);
    return 1;
}



extern void (*D_8018F718[])(void);

void func_801811F4(void *a0) {
    D_8018F718[*(u8 *)((s32)a0 + 0x15)]();
}




















extern void func_80181550(void);
s32 func_80181230(s32 arg0)
{
  s32 temp_v0;
 do { func_80181550(); temp_v0 = (*((u8 *) (arg0 + 0x15))) + 1; *((u8 *) (arg0 + 0x15)) = temp_v0; } while (temp_v0 = 0);
  return temp_v0;
}


s32 func_8018126C(void) {
        return 0;
    }


extern void func_8001BFD0(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800D1E28(void);

s32 func_80181274(s32 a0)
{
    u8 *s0 = (u8 *)a0;
    func_8002D4C8(0x1C, 0);
    func_8001BFD0();
    func_8002D4C8(0x1D, 0);
    func_800D1E28();
    s0[0x15] = s0[0x15] + 1;
    return 0;
}


extern void func_800D1EBC(void);
    void func_801812D4(void) {
        func_800D1EBC();
    }


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_801812F4(void) {

    extern s32 D_8018F728(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_8018F728, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018F72C;

void func_8018131C(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018F72C, 0x1000000);
}



extern void (*D_8018F740[])(void);

void func_80181344(void *a0) {
    D_8018F740[*(u8 *)((s32)a0 + 0x216)]();
}


extern s32 func_80171990(u8*);
extern void func_8014708C(void*);
extern s32 func_801472C8(struct S*);
extern void func_8014706C(void*);
extern void func_801813C8(void);
void func_80181380(s32 a0) {
    ((void (*)(s32))func_80171990)(a0);
    ((void (*)(s32))func_8014708C)(a0);
    ((s32 (*)(s32))func_801472C8)(a0);
    ((void (*)(s32))func_8014706C)(a0);
    ((void (*)(void *))func_801813C8)((void *)a0);
}


void func_801813C8(void) {
}

extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80171990(u8 *a0);

void func_801813D0(arg0)
s32 arg0;
{
    func_80146994(0x1A, arg0, 0x6E706E8, 0);
    func_80171990((u8 *)arg0);
}


extern s32 func_8014C050(s32 arg0, s32 arg1);
    extern void func_80171928(void *a0);
    void func_80181414(void *a0) {
        if (!func_8014C050((s32)a0, 0x1A)) {
            ((void (*)(void *))func_80171928)(a0);
        }
    }


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_8018F738;

void func_80181450(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018F738, 0x1000000);
}



extern void (*D_8018F758[])(void);

void func_80181478(void *a0) {
    D_8018F758[*(u8 *)((s32)a0 + 0x216)]();
}


INCLUDE_ASM("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80", func_801814B4);

extern s32 func_8014C050(s32 a0, s32 a1);
extern u8 D_800AE6BD;
extern void func_80171928(void *a0);

void func_801814FC(void *a0) {
    if (!func_8014C050((s32)a0, 0x19)) {
        D_800AE6BD = D_800AE6BD + 1;
        func_80171928(a0);
    }
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018F750;

void func_80181550(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018F750, 0x1000000);
}


#include "common.h"

/* A-prop sibling of the byte-matched seed func_8017D840 (ov_SC01_077,
 * src/ov_SC01_077/ov_SC01_077_jr_8017AE2C.c). Same skeleton; the words that
 * differ are the per-overlay callback symbol, the eight init constants, and the
 * call order of func_8012A094 vs the callback. Symbol surface taken from
 * asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/func_80181578.s. */
extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_80181874(void*);
extern u8 D_80126948[];
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_80181578(void) {
    D_80126954 = 0x1F4;
    D_8012695C = 0x4B0;
    D_80126968 = 0xE3;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x80;
    D_8012697A = 0;
    func_8012A018(func_80181874, 0);
    func_8012A094(&D_80126948);
    ((s32 (*)(void *))func_80181874)(&D_80126948);
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_80181874(void *a0);

void func_80181614(void) {

    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    D_80126954 = 0x1f4;
    D_8012695C = 0x4B0;
    D_80126968 = 0x2AA;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80181874, 1);
    func_8012A094((s32)D_80126948);
    func_80181874(D_80126948);
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_80181874(void *a0);

void func_801816AC(void) {

    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    D_80126954 = 0x190;
    D_8012695C = 0x3E8;
    D_80126968 = 0x117;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80181874, 2);
    func_8012A094((s32)D_80126948);
    func_80181874(D_80126948);
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_80181874(void *a0);

void func_80181744(void) {

    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    D_80126954 = 0x1f4;
    D_8012695C = 0x4B0;
    D_80126968 = 0xE3;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80181874, 3);
    func_8012A094((s32)D_80126948);
    func_80181874(D_80126948);
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_80181874(void *a0);

void func_801817DC(void) {

    extern u8 D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    D_80126954 = 0x190;
    D_8012695C = 0x3E8;
    D_80126968 = 0x117;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80181874, 4);
    func_8012A094((s32)D_80126948);
    func_80181874(D_80126948);
}



extern void (*D_8018F760[])(void);

void func_80181874(void *a0) {
    D_8018F760[*(u8 *)((s32)a0 + 0x4)]();
}




void func_801818B0(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_8018F774[];
    extern Blk8_80126940_8017D6D0_80181C80 D_80126940;
    Blk8_80126940_8017D6D0_80181C80 sp10;
    u8 t;
    s16 v0, v1;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_8018F774[t];
    }
    sp10 = D_80126940;

    /* Set sp10.v[0] */
    v1 = -0x340;
    sp10.v[0] = v1;

    /* Clamp sp10.v[2] */
    v0 = -0x740;
    if (sp10.v[2] < v0) {
        sp10.v[2] = v0;
    }

    func_80181D30(a0, sp10.v);
}


#include "common.h"

// @class: regalloc
// @stuck: none — MATCH (76 ins). Skeleton twin: ov_SC06_024:func_8017D474 (0.8244 sim);
//   direct siblings in THIS TU are func_80181AA0 / func_80181C80 (same D_80126B58/
//   func_80148800 toggle, same 8-byte D_80126940 lwl/lwr struct copy (§48-C2), same
//   func_80181D30 tail) — their declarations are adopted verbatim (law 2).
//   Residual that took two passes: the three post-call clamps store their bound from
//   $a0 in the target; plain literals land in $v1 and a plain shared s16 local lands in
//   $v0 (both measured). Fix = the documented $a0 pin (cf. ov_SC03_099.c:175 "register
//   __asm__(\"$4\") forces the a0 allocation, gcc otherwise picks v0") applied to ONE
//   shared store-value local across ALL THREE clamps — pinning only the two failing
//   clamps drifts the length, because the middle clamp's own literal then re-competes
//   for $a0. Compare-bound spelling is orthogonal and stays per §189-E: clamps 1/3 want
//   the constant verbatim + natural order (named local -> `slti x,CST`), clamp 2 wants
//   the bound materialised first (`li $v0,-0x540 ; slt $v0,$v0,$v1`).

extern u16 func_80148800(s32 *a0);
extern void func_80181D30(s32 param_1, s16 *param_2);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);

/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2)
   §183 COSMETIC-TYPEDEF reconcile: the destination TU already declares D_80126940 with the
   sibling's name (ov_SC03_090_jr_8017CA80.c:4408, `Blk8_80126940_8017D6D0_80181C80`, defined
   in src/shared/engine_types.h:1517-1519 as the IDENTICAL `{ s16 v[4]; }`).  Adopted that
   name verbatim -- same name, same body, so §183.1's name/shape trap is not tripped; the
   overlay gate's cdecl.strip_provided_typedefs drops this standalone copy at bank time.
   Re-verified MATCH (76 ins) after the rename. */


void func_80181970(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_8018F778[];
    extern Blk8_80126940_8017D6D0_80181C80 D_80126940;
    Blk8_80126940_8017D6D0_80181C80 sp10;
    u8 t;
    s16 v1;
    register s16 c __asm__("$4"); /* clamp store value — target stores every bound from $a0 */

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_8018F778[t];
    }
    sp10 = D_80126940;

    v1 = sp10.v[0];
    if (v1 < -0x6FF) {
        if (v1 < -0x7BF) {
            *(s16 *)(a0 + 0x2E) = 0;
        } else {
            *(s16 *)(a0 + 0x2E) = -0x7C0 - v1;
        }
    } else {
        *(s16 *)(a0 + 0x2E) = 0;
    }

    *(s16 *)(a0 + 0x28) = (s16)func_80012F74(*(s16 *)(a0 + 0x28), *(s16 *)(a0 + 0x2E), 4, 1);

    {
        s16 lo = -0x800;
        if (sp10.v[0] < lo) {
            c = -0x800;
            sp10.v[0] = c;
        }
    }
    {
        s16 lim = -0x540;
        if (lim < sp10.v[0]) {
            c = -0x540;
            sp10.v[0] = c;
        }
    }
    {
        s16 lo2 = -0x3C0;
        if (sp10.v[2] < lo2) {
            c = -0x3C0;
            sp10.v[2] = c;
        }
    }

    func_80181D30(a0, sp10.v);
}



/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2) */

extern u16 func_80148800(s32 *a0);
extern void func_80181D30(s32 param_1, s16 *param_2);

void func_80181AA0(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_8018F77C[];
    extern Blk8_80126940_8017D6D0_80181AA0 D_80126940;
    Blk8_80126940_8017D6D0_80181AA0 sp10;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_8018F77C[t];
    }
    sp10 = D_80126940;
    sp10.v[0] = -0x800;
    sp10.v[2] = 0x3F0;
    func_80181D30(a0, sp10.v);
}


INCLUDE_ASM("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80", func_80181B50);


/* 8 bytes, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2) */

extern u16 func_80148800(s32 *a0);
extern void func_80181D30(s32 param_1, s16 *param_2);

void func_80181C80(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_8018F784[];
    extern Blk8_80126940_8017D6D0_80181C80 D_80126940;
    Blk8_80126940_8017D6D0_80181C80 sp10;
    u8 t;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_8018F784[t];
    }
    sp10 = D_80126940;
    sp10.v[0] = -0x340;
    sp10.v[2] = 0x780;
    func_80181D30(a0, sp10.v);
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

void func_80181D30(s32 param_1, s16 *param_2) {
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


void func_80181EC8(void) {
}

extern void func_8013B7F4(void *a0, int a1);
extern unsigned char D_8018F7A8[];

int func_80181ED0(int param_1)
{
    register int iVar1 __asm__("$4");
    iVar1 = *(int *)(D_8018F7A8 + param_1 * 4);
    __asm__ __volatile__("" ::: "memory");
    func_8013B7F4((void *)iVar1, 0);
}


extern u8 D_8018F788[];
extern u8 D_8018F798[];
extern s32 D_801CBC90;

void func_80181F00(u8 *parent)
{
    switch (*(s16 *)(parent + 0x70)) {
    case 0:
        func_8013B598(1, (u16 *)D_8018F788);
        func_8013B598(2, (u16 *)(D_8018F788 + 8));
        break;
    case 1:
        func_8013B598(1, (u16 *)D_8018F798);
        D_801CBC90 = 0x140;
        func_8013B598(2, (u16 *)(D_8018F798 + 8));
        break;
    }
}




s32 func_80181F84(void) {

    extern s32 D_8012704C;
    if (D_8012704C == 0) {
        return 0x3e;
    }
    return 0x47;
}



/* Declarations copied VERBATIM from the TU (ov_SC02_026_jr_8017C180.c):
 *   D_80126B62     TU:1793/4533  `extern u16` -> cast to s16* at the use site (`lh`)
 *   D_80126B96     TU:3758/4695/5189/5269  `extern u16`
 *   func_8012DEB8  TU:5081/5147/5266/5315  `s32 (s32,s32,s32)`
 *   func_8012BD14  TU:3986                 `s32 (s32)`
 * D_801A0B2C / D_801A0B54 / D_801A0B7C are 20-entry `.short` tables in
 * asm/ov_SC02_026/data/tail.data.s:40884/40909/40934 (loads are `lhu` -> u16).
 * D_801A0BA4 is the 2-entry fn-ptr table right after them (func_80180A4C /
 * func_80180AF0); same `void (*[])(...)` form as D_801A9EB8 (TU:3653).
 * func_8002D59C is declared nowhere in this TU. */

extern s32 func_8012DEB8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012BD14(s32 a0);
extern void func_8002D59C(s32 a0, u16 a1, s32 a2);

void func_80181FA4(s32 a0) {

    extern u16 D_80126B62;
    extern u16 D_80126B96;
    extern u16 D_801A0B2C[];
    extern u16 D_801A0B54[];
    extern u16 D_801A0B7C[];
    extern void (*D_801A0BA4[])(s32);
 /* 8 bytes */

    V4_8017FAC0_80181FA4 p1;
    V4_8017FAC0_80181FA4 p2;
    s32 i;
    s32 t;
    s32 y;
    s32 ret;

    t = *(s16 *)(a0 + 0xA) + 0x20;
    y = *(s16 *)&D_80126B62 - t;
    if (y < -0x110) {
        y = -0x110;
    } else if (y > 0) {
        y = 0;
    }
    p1.y = y;
    p2.y = y;

    for (i = 0; i < 20; i += 4) {
        p1.x = D_801A0B2C[i];
        p1.z = D_801A0B2C[i + 1];
        p2.x = D_801A0B2C[i + 2];
        p2.z = D_801A0B2C[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }
    for (i = 0; i < 20; i += 4) {
        p1.x = D_801A0B54[i];
        p1.z = D_801A0B54[i + 1];
        p2.x = D_801A0B54[i + 2];
        p2.z = D_801A0B54[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }
    for (i = 0; i < 20; i += 4) {
        p1.x = D_801A0B7C[i];
        p1.z = D_801A0B7C[i + 1];
        p2.x = D_801A0B7C[i + 2];
        p2.z = D_801A0B7C[i + 3];
        if (func_8012DEB8(a0, (s32)&p1, (s32)&p2) == 1) {
            D_80126B96 = 0x4004;
        }
    }

    D_801A0BA4[*(u16 *)(a0 + 0x2)](a0);

    ret = func_8012BD14(a0);
    if (ret > 0x3FFFF) {
        *(s16 *)(a0 + 0xFE) = 1;
        func_8002D59C(4, 0x609, *(u16 *)(a0 + 0x70));
    } else {
        *(s16 *)(a0 + 0xFE) = *(u16 *)(a0 + 0xFE) - 1;
        if (*(s16 *)(a0 + 0xFE) == 0) {
            *(s16 *)(a0 + 0xFE) = 4;
            func_8002D59C(0x609, ((0x40000 - ret) * 127) / 0x40000 | 0x1000,
                          *(u16 *)(a0 + 0x70));
        }
    }
}



/* func_8018223C -- ov_SC02_026 / ov_SC02_026_jr_8017C180
 * TU-verbatim decls (src/ov_SC02_026/ov_SC02_026_jr_8017C180.c):
 *   extern u8 D_801202A0[];                                     (line 387, 586)
 *   extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);   (line 592)
 *   extern s32 func_80047948(s32 a0);                           (line 2206)
 *   extern s32 func_8004787C(s32 a0);                           (line 2207)
 * Not in this TU: func_8012B6D4 (fleet-standard sig), D_801A0BF0 (2-entry fn-ptr
 * table in ov_SC02_026 tail.data: func_80180B0C / func_80180B90).
 */

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);

void func_8018223C(void *arg0) {

    extern u8 D_801202A0[];
    extern void (*D_801A0BF0[])(void *);
                 /* 8 bytes, align 2 -> lwl/lwr/swl/swr copy */
                /* stride 0x10C, 0x60 entries (0x6480) */

    /* Two further V4 slots the original body declared ahead of `pos` but that
     * this function never reads: the target frame is 0x50 with locals at
     * 0x10..0x37 and the first live vector at 0x20, i.e. 0x10 bytes of stack
     * precede `pos`. Dropping them yields a 0x40 frame and shifts every sp
     * displacement by 0x10 (36 mismatches). */
    V4_8017FD58_8018223C unused[2];
    V4_8017FD58_8018223C pos;
    V4_8017FD58_8018223C tmp;
    V4_8017FD58_8018223C dst;
    Ent_8017FD58_8018223C *p;
    Ent_8017FD58_8018223C *e;
    s32 i;
    s32 ang;

    p = (Ent_8017FD58_8018223C *)arg0;
    D_801A0BF0[p->f2](p);
    e = (Ent_8017FD58_8018223C *)D_801202A0;
    for (i = 0; i < 0x60; i++, e++) {
        if (e->f0 == 0x12C) {
            pos.x = e->x;
            pos.y = e->y;
            pos.z = e->z;
            ang = func_8012B6D4((s16 *)&p->f4, (s16 *)&e->f4);
            if (*(s16 *)(p->f64 + 0xFC) < 0) {
                ang -= 0x400;
            } else {
                ang += 0x400;
            }
            ang &= 0xFFF;
            pos.x -= func_8004787C(ang) >> 8;
            pos.z -= func_80047948(ang) >> 8;
            tmp.x = e->x;
            tmp.y = e->y;
            tmp.z = e->z;
            dst = tmp;
            if (func_80135888(p->f20, p->f58, (s32)&pos, (s32)&dst) != 0) {
                e->x = pos.x;
                e->z = pos.z;
            }
        }
    }
}


#include "common.h"

void func_801823C4(s32 a0) {
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8012B23C(void *a0);
    extern u16 D_801A0E94[];
    extern u16 D_801A0E96[];
    extern u16 D_801A0E98[];
    extern void func_8001CA1C(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, s32 a1);
    extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
    extern s32 rand(void);

    extern u8 D_801A0BF8[];
    extern u8 D_801A0CB8[];
    extern u8 D_801A0D40[];
    extern u8 D_801A0E00[];
    extern u8 D_801A0EE4[];
    extern u8 D_801A0F08[];
    extern u8 D_801A0BBC[];
    extern u8 D_801A0EF4[];
    extern u8 D_801A0F00[];

    s32 v0;
    s16 sVar1;
    u32 uVar3;
    u32 uVar5;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }
    func_8012B23C((void *)a0);
    *(u16 *)(a0 + 0x12) = D_801A0E94[*(s16 *)(a0 + 0xFC) * 4];
    *(u16 *)(a0 + 0x16) = D_801A0E96[*(s16 *)(a0 + 0xFC) * 4];
    *(u16 *)(a0 + 0x1A) = D_801A0E98[*(s16 *)(a0 + 0xFC) * 4];
    switch (*(s16 *)(a0 + 0x70)) {
    case 0:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A0BF8);
        func_8012A828(a0, (s32)D_801A0CB8);
        *(s16 *)(a0 + 2) = 1;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2000;
        break;
    case 1:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A0D40);
        func_8012A828(a0, (s32)D_801A0E00);
        *(s16 *)(a0 + 2) = 4;
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
        *(s32 *)(a0 + 0x1C) = 8;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        *(u8 *)(a0 + 0xC0) = 1;
        *(u8 **)(a0 + 0x58) = D_801A0EE4;
        *(u16 *)(a0 + 0x5C) = 0x8000;
        *(s16 *)(a0 + 0xAE) = -9;
        *(u8 **)(a0 + 0xBC) = D_801A0F08;
        *(u32 *)(a0 + 0xB4) = 0;
        *(u8 **)(a0 + 0x78) = D_801A0BBC;
        *(u32 *)(a0 + 0xC4) |= 2;
        uVar3 = func_8012C658(0x12F, 4, a0);
        *(u32 *)(a0 + 0xCC) = uVar3;
        break;
    case 2:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A0BF8);
        func_8012A828(a0, (s32)D_801A0CB8);
        *(s16 *)(a0 + 2) = 6;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x2000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x2000;
        break;
    case 3:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A0D40);
        func_8012A828(a0, (s32)D_801A0E00);
        *(s16 *)(a0 + 2) = 7;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        *(s32 *)(a0 + 0x1C) = 6;
        break;
    case 4:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A0EF4);
        func_8012A828(a0, (s32)D_801A0F00);
        *(s16 *)(a0 + 2) = 8;
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x8000000;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x3C00;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x3C00;
        break;
    case 5:
        func_8001CA1C(*(s32 *)(a0 + 0x20), (s32)D_801A0BF8);
        func_8012A828(a0, (s32)D_801A0CB8);
        *(s16 *)(a0 + 2) = 9;
        *(u16 *)(a0 + 0xFE) = *(u16 *)(*(s32 *)(a0 + 0x64) + 0x36);
        *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x80000000;
        *(s16 *)(a0 + 0x100) = *(s16 *)(*(s32 *)(a0 + 0x64) + 0xFE) * 6;
        sVar1 = *(s16 *)(*(s32 *)(a0 + 0x64) + 0x70);
        if (sVar1 == 5) {
            *(s16 *)(a0 + 0x12) = (rand() % 0x60) - 0x30;
            *(s16 *)(a0 + 0x16) = (rand() % 0x60) - 0x60;
            sVar1 = (rand() % 0x60) - 0x40;
        } else {
            if (sVar1 != 6) {
                break;
            }
            *(s16 *)(a0 + 0x12) = (rand() % 0x60) - 0x30;
            *(s16 *)(a0 + 0x16) = (rand() % 0x20) - 0x20;
            sVar1 = (rand() % 0x60) - 0x50;
        }
        *(s16 *)(a0 + 0x1A) = sVar1;
    }
    uVar5 = rand();
    *(u32 *)(a0 + 0x94) = uVar5 & 0xF;
    *(u32 *)(*(s32 *)(a0 + 0x20) + 4) |= 0x50000000;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;
}




extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80182870(void *a0) {
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) =
        *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x4);
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) &= 0xEFFFFFFF;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x08000000;
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x60000000;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
    *(s32 *)((s32)a0 + 0x4) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4) -
        (func_8004787C(*(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) & 0xFFF) << 8);
    *(s32 *)((s32)a0 + 0x8) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x8);
    *(s32 *)((s32)a0 + 0xC) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC) -
        (func_80047948(*(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) & 0xFFF) << 8);
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x18) / 2;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x1A) / 2;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) =
        (s16) * (u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x1C) / 2;
}


extern void func_8012C218(void *a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
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

void func_80182A04(void *a0)
{
    u16 sv0[4];
    u16 sv1[4];
    s32 flag[4];
    s32 cnt;
    s32 tmp;
    s32 m;

    if (*(s16 *)((s32)a0 + 0xFE) == *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        if ((*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x100) & 0x4000) == 0) {
            goto low;
        }
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) - 0x200;
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) - 0x200;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) >= 0x200) {
            goto tail;
        }
        func_80143B6C((s32)a0, 0);
    }
    func_8012C218(a0);
    return;

low:
    cnt = *(u16 *)((s32)a0 + 0x100) - 1;
    *(s16 *)((s32)a0 + 0x100) = cnt;
    if ((s16)cnt < 9) {
        *(s16 *)((s32)a0 + 0x100) = 0x18;
        if (*(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x70) == 5) {
            *(s16 *)((s32)a0 + 0x12) = rand() % 56 - 0x1C;
            *(s16 *)((s32)a0 + 0x16) = rand() % 96 - 0x60;
            *(s16 *)((s32)a0 + 0x1A) = rand() % 56 - 0x2C;
        } else if (*(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x70) == 6) {
            *(s16 *)((s32)a0 + 0x12) = rand() % 56 - 0x1C;
            *(s16 *)((s32)a0 + 0x16) = rand() % 32 - 0x20;
            *(s16 *)((s32)a0 + 0x1A) = rand() % 128 - 0x60;
        }
    }
    tmp = *(s16 *)((s32)a0 + 0x100);
    if (tmp < 0x10) {
        s32 g1;                       /* per-arm local: §5a cross-jump barrier, see header */
        g1 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)(g1 + 0x1A) = tmp * 0x300;
        *(s16 *)(g1 + 0x18) = tmp * 0x300;
    } else {
        s32 g2;                       /* per-arm local: §5a cross-jump barrier, see header */
        g2 = *(s32 *)((s32)a0 + 0x20);
        *(s16 *)(g2 + 0x1A) = (0x20 - tmp) * 0x300;
        *(s16 *)(g2 + 0x18) = (0x20 - tmp) * 0x300;
    }

tail:
    {
        s32 msk;
        msk = 0x80000000;             /* HOISTED OUT OF THE ARM ON PURPOSE — see header (3) */
        if (*(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x4) < 0) {
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= msk;
        } else {
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        }
    }

    *(s32 *)((s32)a0 + 0x4) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4);
    *(s32 *)((s32)a0 + 0x8) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x8);
    *(s32 *)((s32)a0 + 0xC) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC);

    sv0[0] = *(u16 *)((s32)a0 + 0x12);
    sv0[1] = *(u16 *)((s32)a0 + 0x16);
    sv0[2] = *(u16 *)((s32)a0 + 0x1A);

    m = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x34;
    gte_SetRotMatrix(m);
    gte_SetTransMatrix(m);

    RotTransSV(sv0, sv1, flag);

    *(s16 *)((s32)a0 + 0x6) = sv1[0];
    *(s16 *)((s32)a0 + 0xA) = sv1[1];
    *(s16 *)((s32)a0 + 0xE) = sv1[2];
}



extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80182DB4(void *a0) {

    extern void (*D_801A0F18[])(void);
    extern u16 D_80126B96;
    s32 t;
    u16 *q;

    D_801A0F18[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        if (*(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) >= 0) {
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) - 0x40;
            if (func_8012D624(a0, 0x1c, 0xa) == 1) {
                q = &D_80126B96;
                *q |= 0x200;
            }
            *(s16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0xa) + 0x40;
            if (*(s16 *)((s32)a0 + 0x70) == 1) {
                t = *(s32 *)((s32)a0 + 0x1c) - 1;
                *(s32 *)((s32)a0 + 0x1c) = t;
                if (t == 0) {
                    *(s32 *)((s32)a0 + 0x1c) = 8;
                    func_8012C658(0x12f, 3, (s32)a0);
                }
            }
        }
    }
}



extern void (*D_801A0FC4[])(void);

void func_80182EA0(void *a0) {
    D_801A0FC4[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801A1078[])(void);

void func_80182EDC(void *a0) {
    D_801A1078[*(u16 *)((s32)a0 + 0x2)]();
}



void func_80182F18(void *a0) {
        *(s8 *)((s32)a0 + 0xc1) = 0;
        *(s16 *)((s32)a0 + 0x5e) = 0;
        *(u16 *)((s32)a0 + 0x5c) &= 0xc800;
    }




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80182F30(s32 a0) {

    extern u8 D_801A0AF8[];
    extern u8 D_801A0AD8[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_8018BDB4[];
    s32 t;

    if (func_8012C354(a0, (s32)D_801A0AF8) != 0) {
        *(u8 *)(a0 + 0xC0) = 1;

        t = *(s32 *)(a0 + 0xC4);
        *(s32 *)(a0 + 0xBC) = (s32)D_801A0AD8;
        *(s32 *)(a0 + 0xC4) = t | 0x2;

        func_8012A828(a0, (s32)D_8018BDB4);

        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(s16 *)(a0 + 0xFE) = 1;

        func_8012C658(0x164, 0x555, a0);
        func_8012C658(0x164, 0xAAA, a0);
        func_8012C658(0x164, 0x1000, a0);
    }
}


void func_80182FD4(void *a0) {
        void *a1 = *(void **)((char *)a0 + 0x20);
        *(u16 *)((char *)a1 + 0x12) += *(u16 *)((char *)a0 + 0xfc);
    }




extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);

void func_80182FF0(void *a0) {

    extern u8 D_8018BDB4[];
    extern u8 D_801A0BBC[];
    extern u8 D_801A0AD8[];
    if (func_8012C354((s32)a0, (s32)D_801A0BBC) != 0) {
        void *a2 = *(void **)((char *)a0 + 0x20);

        *(s32 *)((char *)a2 + 0x4) |= 0x80000000;
        *(u8 *)((char *)a0 + 0xC0) = 1;

        *(s32 *)((char *)a0 + 0xBC) = (s32)D_801A0AD8;
        *(s32 *)((char *)a0 + 0xC4) |= 0x2;

        func_8012A828((s32)a0, (s32)D_8018BDB4);

        *(u16 *)((char *)a0 + 0x2) = 1;
        *(u8 *)((char *)a0 + 0x75) = 0;
    }
}


extern void func_8012B2CC(s32 a0);


void func_80183074(s32 *a0) {
    s32 val_at_64;
    s32 deref;
    u16 val1, val2;
    s32 ptr_at_20;

    val_at_64 = *(s32 *)((char *)a0 + 0x64);
    deref = *(s32 *)((char *)val_at_64 + 0x20);
    val1 = *(u16 *)((char *)deref + 0x12);
    val2 = *(u16 *)((char *)a0 + 0x70);
    ptr_at_20 = *(s32 *)((char *)a0 + 0x20);

    *(u16 *)((char *)ptr_at_20 + 0x12) = val1 + val2;

    func_8012B2CC(a0);
}




void func_801830B0(void *a0)
{
    u16 v = *(u16 *)(a0 + 0x5E);
    if (v != 0x1D) {
        *(u16 *)(a0 + 0x5C) = 0;
        *(u16 *)(a0 + 0x2) = 0x7;
    } else {
        *(u16 *)(a0 + 0x5C) = 0x8000;
    }
    *(u8 *)(a0 + 0xC1) = 0;
    *(u16 *)(a0 + 0x5E) = 0;
}



extern void func_8012CBCC(s32 a0);
extern void func_8012E688(void*, s32, s32);

void func_801830E0(s32 a0) {
    if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x2000) {
        s16 v = *(s16 *)(a0 + 0x70);
        if (v != 0) {
            *(s16 *)(a0 + 0x2) = 2;
            ((void (*)(void*, s32, s32))func_8012E688)((void *)a0, 0xBA2, 0);
        } else {
            void *p = *(void **)(a0 + 0x20);
            *(s16 *)(a0 + 0x2) = 3;
            *(s32 *)(p + 0x4) |= 0x80000000;
            *(s32 *)(a0 + 0x1C) = 0x1E;
        }
    }
}



extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B864(s32 a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012E688(void*, s32, s32);

void func_80183164(s32 a0) {

    extern u8 D_801A0E88[];
    extern s16 D_80126CB6;
    s32 r;

    if (func_8012BCCC(a0) > 0x63FFF) {
        *(u16 *)(a0 + 0x2) = 5;
    } else {
        r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                          func_8012B864(a0), 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        func_8012B1B4(a0, (s32)D_801A0E88);
        *(s32 *)(a0 + 0x14) =
            *(s32 *)(a0 + 0x14) +
            ((D_80126CB6 - *(s16 *)(a0 + 0xA)) << 8);
        if (((s32 (*)(s32))func_8012CBCC)(a0)) {
            *(s16 *)(a0 + 0x16) = -0x18;
            ((void (*)(s32, s32, s32))func_8012E688)(a0, 0xBA2, 0);
        }
    }
}



extern void func_8012E688(void *a0, s32 a1, s32 a2);
extern void func_8012B23C(void *a0);

void func_80183228(void *a0) {

    extern u16 D_801A0E94[];
    extern u16 D_801A0E96[];
    extern u16 D_801A0E98[];
    void *a1;

    if (--*(s32 *)((s32)a0 + 0x1c) == 0) {
        *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)a0 + 0x88);
        *(u16 *)((s32)a0 + 0xa) = *(u16 *)((s32)a0 + 0x8a);
        *(u16 *)((s32)a0 + 0xe) = *(u16 *)((s32)a0 + 0x8c);
        a1 = *(void **)((s32)a0 + 0x20);
        *(u32 *)((s32)a1 + 0x4) &= 0x7fffffff;
        func_8012E688(a0, 0x679, 0);
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012B23C(a0);
        *(u16 *)((s32)a0 + 0x12) = D_801A0E94[*(s16 *)((s32)a0 + 0xfc) * 4];
        *(u16 *)((s32)a0 + 0x16) = D_801A0E96[*(s16 *)((s32)a0 + 0xfc) * 4];
        *(u16 *)((s32)a0 + 0x1a) = D_801A0E98[*(s16 *)((s32)a0 + 0xfc) * 4];
    }
}




extern s32 func_8012BD14(s32 a0);
extern void func_80143970(void *a0);
extern void func_8012E688(void *a0, s32 a1, s32 a2);

void func_80183308(s32 a0) {
    s32 ret = func_8012BD14(a0);
    if (ret <= 0x64000) {
        Struct_80183308 *ptr = *(Struct_80183308 **)(a0 + 0x20);
        *(s16 *)(a0 + 0x2) = 1;
        ptr->f1 = ptr->f1 & 0x7FFFFFFF;
        func_80143970((void *)a0);
        func_8012E688((void *)a0, 0xBA2, 0);
    }
}



extern s32 func_8012BCCC(s32 a0);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012E688(void*, s32, s32);

void func_80183378(s32 a0) {

    extern u8 D_801A0E88[];
    s16 sp10[3];
    s32 r;

    if (func_8012BCCC(a0) <= 0x38400) {
        *(u16 *)(a0 + 0x2) = 2;
    } else {
        sp10[0] = *(u16 *)(a0 + 0x6);
        sp10[2] = *(u16 *)(a0 + 0xE);
        r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                          func_8012B70C(sp10, (s16 *)(a0 + 0x88)), 4);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        func_8012B1B4(a0, (s32)D_801A0E88);
        *(s32 *)(a0 + 0x14) =
            *(s32 *)(a0 + 0x14) +
            ((*(s16 *)(a0 + 0x8A) - *(s16 *)(a0 + 0xA)) << 8);
        if (((s32 (*)(s32))func_8012CBCC)(a0) & 0x8000) {
            *(s16 *)(a0 + 0x16) = -4;
            ((void (*)(s32, s32, s32))func_8012E688)(a0, 0xBA2, 0);
        }
    }
}


void func_80183454(void) {
}


/* func_8018345C — per-frame entity tick:
 *  - decrement the timer at 0x1C if non-zero
 *  - fade the two u16 colour/alpha words at +0x18 / +0x1A of the display record
 *    hanging off 0x20 by 0x100 each
 *  - once the second one drops to <= 0x80, tear the entity down
 *
 * §71 sibling-first: DEFINE_func_801319E0() (engine_core.h L17451) is the same
 * `func_8002A04C(arg0); func_8012C218((void *)arg0);` teardown tail with arg0
 * living in $s0 across the calls — signature and casts copied from it.
 */

extern void func_8002A04C(s32 a0);
extern void func_8012C218(void *a0);

void func_8018345C(s32 arg0) {
    if (*(s32 *)(arg0 + 0x1C) != 0) {
        *(s32 *)(arg0 + 0x1C) -= 1;
    }
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) -= 0x100;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) -= 0x100;
    if (*(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) < 0x81) {
        if (*(s16 *)(arg0 + 0x70) == 1) {
            /* LOAD-BEARING: hoisting the argument load into its own local
             * emits `lw $a0,0xCC($s0)` ABOVE the guard branch and leaves the
             * beqz delay slot a nop. Inlining it at the call site instead
             * gives beqz/nop/lw -> 3 mismatches (class DELAY-SLOT). A/B-tested. */
            void *temp = *(void **)(arg0 + 0xCC);
            if (arg0 != 0) {
                func_8012C218(temp);
            }
        }
        func_8002A04C(arg0);
        func_8012C218((void *)arg0);
    }
}



extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);


void func_80183514(s32 a0) {

    extern u8 D_801A0F50[];
    extern u8 D_8018BDB4[];
    extern u16 D_801A0F84[];
    extern u16 D_801A0F86[];
    extern u16 D_801A0F88[];
    extern s16 D_801A0F8A[];
    if (func_8012C354(a0, (s32)D_801A0F50) != 0) {
        func_8012A828(a0, (s32)D_8018BDB4);
        *(s16 *)(a0 + 0x2) = 1;
        *(u8 *)(a0 + 0x75) = 0;
        *(u16 *)(a0 + 0x12) = D_801A0F84[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x16) = D_801A0F86[*(s16 *)(a0 + 0xFC) * 4];
        *(u16 *)(a0 + 0x1A) = D_801A0F88[*(s16 *)(a0 + 0xFC) * 4];
        *(s32 *)(a0 + 0x1C) = D_801A0F8A[*(s16 *)(a0 + 0xFC) * 4];
        func_8012C588(0x1C4, a0);
    }
}




extern void func_8012CBA4(s32 a0);
extern void func_8012DFD4(u8 *a0);

void func_801835D8(s32 a0) {
    s32 t;

    func_8012CBA4(a0);
    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;
    if (t == 0) {
        *(s32 *)(a0 + 0x1C) = 0x6;
        *(s16 *)(a0 + 0x2) = 0x2;
    }
    func_8012DFD4((u8 *)a0);
}



extern void func_8012DFD4(u8 *a0);

void func_8018362C(s32 a0) {

    extern s16 D_801A0F8A[];
    s32 a1 = a0;
    s32 t = *(s32 *)(a1 + 0x1C) - 1;
    *(s32 *)(a1 + 0x1C) = t;
    if (t == 0) {
        s16 idx = *(s16 *)(a1 + 0xFC);
        s32 val = D_801A0F8A[idx * 4];

        *(s16 *)(a1 + 0x12) = -*(u16 *)(a1 + 0x12);
        *(s16 *)(a1 + 0x16) = -*(u16 *)(a1 + 0x16);
        *(s16 *)(a1 + 0x1A) = -*(u16 *)(a1 + 0x1A);
        *(s16 *)(a1 + 0x2) = 1;
        *(s32 *)(a1 + 0x1C) = val;
    }
    func_8012DFD4((u8 *)a0);
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 rand(void);


void func_801836A8(s32 param_1)
{

    extern u8 D_801A0FD0[];
    extern u8 D_801A1030[];
    s32 v0;
    s16 sVar1;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
    } else {
        func_8001CA1C(v0, (s32)D_801A0FD0);
        func_8012A828(param_1, (s32)D_801A1030);
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x18) = 0x10;
        *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x1a) = 0x10;
        *(s32 *)(param_1 + 0x94) = rand() & 7;
        *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2c) |= 0x10;
        if ((u32)(*(u16 *)(param_1 + 0x70) - 1) >= 0x6fff) {
            *(u16 *)(param_1 + 0x70) = rand() & 0x77ff;
            sVar1 = 2;
        } else {
            sVar1 = 1;
        }
        *(s16 *)(param_1 + 2) = sVar1;
    }
}



extern s32 rand(void);
extern s32 func_8004787C(s32 a0);

void func_8018378C(s32 a0) {
    s32 t;

    if (*(s32 *)(a0 + 0x1C) == 0) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        *(s16 *)(a0 + 0xFE) += 0x40;
        if (*(s16 *)(a0 + 0xFE) >= 0x800) {
            *(s16 *)(a0 + 0xFE) = 0;
            *(s32 *)(a0 + 0x1C) = rand() & 0x1F;
            *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x80000000;
        }
        t = (*(s16 *)(a0 + 0x70) * func_8004787C(*(s16 *)(a0 + 0xFE))) >> 12;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = t + 0x800;
    } else {
        *(s32 *)(a0 + 0x1C) -= 1;
    }
}



extern s32 rand(void);
extern s32 func_8004787C(s32 a0);

void func_80183858(s32 a0) {
    s32 t;

    if (*(s32 *)(a0 + 0x1C) == 0) {
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) &= 0x7FFFFFFF;
        *(s16 *)(a0 + 0xFE) += 0x40;
        if (*(s16 *)(a0 + 0xFE) >= 0x800) {
            *(s16 *)(a0 + 0xFE) = 0;
            *(s32 *)(a0 + 0x1C) = rand() & 0x1F;
            *(s16 *)(a0 + 0x70) = rand() & 0x77FF;
            *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4) |= 0x80000000;
        }
        t = (*(s16 *)(a0 + 0x70) * func_8004787C(*(s16 *)(a0 + 0xFE))) >> 12;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = t + 0x800;
    } else {
        *(s32 *)(a0 + 0x1C) -= 1;
    }
}



extern void (*D_801A2EF8[])(void);

void func_80183930(void *a0) {
    D_801A2EF8[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8013B7AC(s32 a0);

void func_8018396C(s32 a0) {
    s32 i;
    s32 s1 = a0;

    for (i = 0; i < 3; i++) {
        func_8013B7AC(i);
    }

    *(u16 *)(s1 + 0x2) += 1;
    *(u32 *)(s1 + 0xCC) = 0;
}


typedef struct { short vx, vy, vz, pad; } SV_801851A8_801839C4;
typedef struct { short m[3][3]; long t[3]; } MTX_801851A8_801839C4;

extern void func_8013B7AC(s32 a0);
extern s32 func_8012BD14(s32 a0);
extern s32 func_80183B98(s32 a0);
extern void func_80183BF0(s32 a0, s32 a1);
extern void func_80183C3C(s32 a0, s32 a1);

void func_801839C4(s32 a0) {

    extern u8 D_801202A0[];
    s32 i;
    s32 v1;
    register s32 val1 __asm__("$21");
    register s32 val2 __asm__("$20");
    u8 *cur;
    register u8 *best1 __asm__("$18");
    register u8 *best2 __asm__("$22");
    register s32 flag __asm__("$19");
    s32 t;
    register s32 cmp __asm__("$23");
    s32 pad[2];

    best1 = 0;
    best2 = 0;
    flag = 0;
    t = *(s32 *)(a0 + 0xCC);
    if (t == 0) {
        goto L_D54;
    }
    func_80183C3C(t + 4, 0);
    goto L_D5C;

L_D3C:
    val1 = func_8012BD14((s32)cur);
    best1 = cur;
    flag = 1;
    goto L_D8C;

L_D54:
    func_8013B7AC(0);

L_D5C:
    cur = D_801202A0;
    i = 0;
    cmp = 1;

L_D6C:
    if (func_80183B98((s32)cur) == cmp) {
        goto L_D3C;
    }
    i++;
    cur += 0x10C;
    if (i < 0x60) {
        goto L_D6C;
    }

L_D8C:
    if (flag) {
        goto L_DBC;
    }
    func_8013B7AC(1);
    goto L_DFC;

L_DA4:
    val2 = func_8012BD14((s32)cur);
    best2 = cur;
    flag = 1;
    goto L_DE8;

L_DBC:
    flag = 0;
    if (i >= 0x60) {
        goto L_DE8;
    }
    cmp = 1;

L_DC8:
    if (func_80183B98((s32)cur) == cmp) {
        goto L_DA4;
    }
    i++;
    cur += 0x10C;
    if (i < 0x60) {
        goto L_DC8;
    }

L_DE8:
    if (flag) {
        goto L_E0C;
    }
    func_80183BF0((s32)best1, 1);

L_DFC:
    func_8013B7AC(2);
    return;

L_E0C:
    if (i >= 0x60) {
        goto L_E78;
    }
    flag = 1;

L_E18:
    if (func_80183B98((s32)cur) == flag) {
        v1 = func_8012BD14((s32)cur);
        if (v1 < val1) {
            best2 = best1;
            best1 = cur;
            val2 = val1;
            val1 = v1;
        } else if (v1 < val2) {
            best2 = cur;
            val2 = v1;
        }
    }
    i++;
    cur += 0x10C;
    if (i < 0x60) {
        goto L_E18;
    }

L_E78:
    func_80183BF0((s32)best1, 1);
    func_80183BF0((s32)best2, 2);
}


INCLUDE_ASM("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80", func_80183B98);

extern void func_80183C3C(s32 a0, s32 a1);
extern void func_80183C80(s32 a0, s32 a1, s32 a2);

void func_80183BF0(s32 a0, s32 a1) {
    u16 type;
    type = *(u16 *) a0;
    if (type != 0x178 && type != 0x1E8) {
        func_80183C3C(a0 + 4, a1);
    } else {
        func_80183C80(a0 + 4, a1, 0xC0);
    }
}


INCLUDE_ASM("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80", func_80183C3C);

extern void func_8013B6A0(s32 idx, u16 *src, s32 val);

void func_80183C80(s32 a0, s32 a1, s32 a2) {
    u16 sp[3];
    sp[0] = *(u16 *)(a0 + 0x2);
    sp[1] = *(u16 *)(a0 + 0x6);
    sp[2] = *(u16 *)(a0 + 0xA);
    func_8013B6A0(a1, sp, a2);
}


void func_80183CC4(void) {
}


extern void func_80184998(void *a0);

void func_80183CCC(void *a0) {

    extern void (*D_801A2F84[])(void);
    D_801A2F84[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        *(s32 *)((s32)a0 + 0xE4) = *(s32 *)((s32)a0 + 0xE4) + 1;
        if ((*(s32 *)((s32)a0 + 0xE4) & 0xF) == 0) {
            func_80184998(a0);
        }
    }
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);
extern u32 D_801A2F10[];
extern s32 D_801A2F54;
extern u8 D_801A5984[];

void func_80183D48(void *a0) {
    s32 r;

    if (func_8012C354((s32)a0, (s32)D_801A2F10) != 0) {
        *(u8 *)((char *)a0 + 0xC0) = 1;
        *(s32 *)((char *)a0 + 0xB4) = -1;
        *(s32 **)((char *)a0 + 0xBC) = &D_801A2F54;
        *(u32 *)((char *)a0 + 0xC4) |= 1;
        *(s32 *)((char *)a0 + 0xE0) = -(((rand() % 8) + 8) << 16);
        func_8012A828((s32)a0, (s32)D_801A5984);
        r = func_8012C658(0x178, *(s16 *)((char *)a0 + 0x70), (s32)a0);
        *(s32 *)((char *)a0 + 0xCC) = r;
        if (*(u16 *)((char *)a0 + 0x70) & 1) {
            *(s16 *)((char *)a0 + 0x2) = 1;
        } else {
            *(s16 *)((char *)a0 + 0x2) = 4;
        }
    }
}


void func_80183E14(void *a0) {
    s16 t;
    s32 r;

    t = rand();
    *(u16 *)((s32)a0 + 0x104) = *(u16 *)((s32)a0 + 0xFC);
    func_8012B200(a0);
    r = rand();
    *(s32 *)((s32)a0 + 0x1C) = r % 60 + 0x78;
    *(s16 *)((s32)a0 + 0xFE) = t % 32 + 0xA;
    *(s16 *)((s32)a0 + 0x2) = 2;
}


#include "common.h"

/* func_80183EC4 — ov_SC03_090, 82 ins.
 * Banked twin (seed_ref): ov_SC02_035:func_801834BC (0.7356 sim) — same opening block
 * (func_80184888 out-buffer copy, sh 0x10, func_8012B608 damage calc, sh/lhu accumulate
 * at 0x12, func_8012B178, func_8012CBF4). This target diverges from the twin after that:
 *   - func_8012B178's second arg reads *(s32*)(a0+0xE0), NOT a0+0xE4 (twin's field).
 *   - the guard chain is func_8012BEE8 -> func_80184A04 -> func_80184958 -> func_8012BE54,
 *     not the twin's func_8012BEE8 -> (a0+0xE0==0) -> func_80183F14.
 *   - the tail (on func_8012BE54(a0) > 0x8000) sets a0+0x1C = rand()%60+0x78 and
 *     a0+0xFE = rand()%32+0xA, matching the sibling func_80183394's else-branch pattern
 *     (rand()%60+0x78) and func_8018362C's *(a0+0xFE)=rand()%32+10 pattern verbatim, just
 *     spelled with the target's own magic-multiply (0x88888889) codegen for %60.
 *   - otherwise (<=0x8000) it sets a0+0x2 = 8 (state) and returns.
 *
 * Declarations: none of func_80184888/func_8012B608/func_8012B178/func_8012CBF4/
 * func_8012BEE8/func_80184A04/func_80184958/func_8012BE54 have a FILE-SCOPE declaration
 * before this function's INCLUDE_ASM position (line 5601) in the destination TU, so all
 * are declared block-scope here using the canonical forms found used LATER in the same TU:
 *   func_80184888  -> src/ov_SC03_090/..._8017CA80.c:5646 `void func_80184888(s32 out, s32 a1, s32 a2)`
 *   func_8012B608  -> :5123/5201/6380  `s32 func_8012B608(s32 a0, s32 a1, s32 a2)`
 *   func_8012B178  -> :5643/6087/6377  `void func_8012B178(s32 a0, s32 a1)`
 *   func_8012CBF4  -> :5638/6601       `void func_8012CBF4(s32 a0)` (canonical void; cast at use site when $v0 is read — not needed here)
 *   func_8012BEE8  -> :5640/6381/6603  `s32 func_8012BEE8(s32 a0)`
 *   func_8012BE54  -> project-canonical (ov_SC03_099 etc, and THIS TU at :6518) `void func_8012BE54(s32 a0)`,
 *                     with the return value recovered via a function-pointer cast AT THE CALL SITE —
 *                     the exact pattern already used in this same TU at :6539
 *                     `((s32 (*)(s32))func_8012BE54)(ent)`.
 *   func_80184A04  -> DEFINED further down THIS SAME TU (:5788) as `s32 func_80184A04(void)`
 *                     (it ignores its incoming register — the body only reads a global). The
 *                     target's call site still loads $a0=s0 before the jal, so the call-site
 *                     declaration must NOT be the real (void) prototype (that would drop the
 *                     arg-setup instruction and lose an instruction) — declared here K&R
 *                     no-prototype `extern s32 func_80184A04();` so `func_80184A04(a0)` still
 *                     compiles and still emits the $a0 move, byte-identical to the (void)
 *                     definition once linked (index_gap: this K&R-vs-void split for an
 *                     ignored-but-still-passed argument, inside the SAME TU as the real def).
 *   func_80184958  -> INCLUDE_ASM in this TU only (:5758), no prototype anywhere else in the
 *                     tree; typed by use: pointer arg, s32 return compared against 1.
 */

extern s32 rand(void);

void func_80183EC4(s32 a0)
{
    extern void func_80184888(s32 out, s32 a1, s32 a2);
    extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
    extern void func_8012B178(s32 a0, s32 a1);
    extern void func_8012CBF4(s32 a0);
    extern s32  func_8012BEE8(s32 a0);
    extern s32  func_80184A04();
    extern s32  func_80184958(s32 a0);
    extern void func_8012BE54(s32 a0);

    s32 sp10[2];
    s32 t;
    s32 r;

    func_80184888(sp10, a0, a0 + 0x102);
    t = sp10[0];
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
    r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), t >> 16,
                       *(s16 *)(a0 + 0xFE));
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
    func_8012B178(a0, *(s32 *)(a0 + 0xE0));
    func_8012CBF4(a0);
    if (func_8012BEE8(a0)) {
        if (func_80184A04(a0) != 1) {
            if (func_80184958(a0) == 1) {
                if (((s32 (*)(s32))func_8012BE54)(a0) <= 0x8000) {
                    *(s16 *)(a0 + 0x2) = 8;
                } else {
                    *(s32 *)(a0 + 0x1C) = rand() % 60 + 0x78;
                    *(s16 *)(a0 + 0xFE) = rand() % 32 + 0xA;
                }
            }
        }
    }
}


extern void func_8012CBF4(s32 a0);
extern s32 func_80013478(s32 a0, s32 a1);

void func_8018400C(s32 a0) {
    func_8012CBF4(a0);
    if (func_80013478(a0 + 4, a0 + 0x88) < 0x101) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        *(u16 *)(a0 + 2) = 4;
    }
}


void func_80184060(s32 a0)
{
    extern void func_8012BE54(s32 a0);
    extern s32  func_80184A04();
    extern s16  D_80126CBA;

    if (((s32 (*)(s32))func_8012BE54)(a0) <= 0x40000 && D_80126CBA == 0 && func_80184A04(a0) == 0) {
        *(s16 *)(a0 + 0x2) = 5;
    }
}


extern s32 *D_80126B78;
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_80184888(s32 out, s32 a1, s32 a2);
extern void func_8012B200(u8 *a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_801840C0(s32 a0) {
    register s32 rin __asm__("$2");
    s16 sp10[3];
    s32 sp18[2];
    s32 t;
    s32 u;

    func_8012B0B4((unsigned int *)sp18,
                  *(s16 *)((s32)D_80126B78 + 0x12) + 0x800,
                  ((s16)rin % 128) + 0x100);

    t = sp18[0];
    sp10[1] = -0x20;
    sp10[0] = t;
    sp10[2] = t >> 16;
    func_80184888((s32)sp18, a0, (s32)sp10);

    u = sp18[0];
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = u;
    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = u >> 16;
    func_8012B200((u8 *)a0);
    func_8012B2CC(a0);
    func_8012B178(a0, *(s32 *)(a0 + 0xE0) - 0x20000);
    *(s16 *)(a0 + 0x2) = 6;
    *(s16 *)(a0 + 0x34) = 0;
}


typedef struct { short m[3][3]; long t[3]; } MTX_801851A8;

/* func_801841A4 — ov_SC03_089 (ov_SC03_089_jr_8017CA80), 154 ins, jtbl_801C53E4 (5 entries,
 * minval 0 / maxval 4 — `lhu` + `sltiu 5`, so the switch expression is UNSIGNED and neither
 * §162a2's leading nor §162a1/§162a3's trailing empty-case tell applies).
 *
 * Decl provenance (§161c) — forms copied VERBATIM from the destination TU where it already
 * declares the callee ABOVE this function's INCLUDE_ASM (src/…/ov_SC03_089_jr_8017CA80.c:5332):
 *   func_8002D4C8   TU:59 / 3984 / 4018   `extern void func_8002D4C8(s32 a0, s32 a1);`   (visible)
 *   func_8012B2CC   TU:2523 / 4913        `extern void func_8012B2CC(s32 a0);`           (visible)
 *   func_8012B178   TU:5635 (BELOW)       same canonical form, so it agrees, not conflicts
 *   func_8018485C   TU:5351 (BELOW)       DEFINED `s32 func_8018485C(s32 arg0)` — agrees
 *   func_80184888   TU:5356 (BELOW)       INCLUDE_ASM only, no decl to conflict with
 * func_8012CBF4 / func_8012B8E4 / func_8012BEE8 / func_8012B200 / func_8012B77C / D_801A2F4C
 * are not declared anywhere in the host TU; the forms below are the project-canonical ones
 * (ov_SC03_099_jr_8012ACE0.c:1688, :353, ov_SC03_099_jr_801380E0.c:272, …).
 *
 * THE SHAPE THAT COSTS THE MATCH — the shared `.L801846F4` tail is a CROSS-JUMP, not a `break`.
 * Case 0 (both arms) and case 3 each end `lhu $v0,0x34; addiu $v0,$v0,1` and only the STORE
 * `sh $v0,0x34($s0)` is shared. Spelling that with a switch-scope `s16 nv; … break;` + a single
 * post-switch `*(s16*)(a0+0x34) = nv;` compiles to 152 ins / 113 mismatched: one shared pseudo
 * makes case 3's `lhu` land in $v1 (`addu $2,$3,1`), which breaks jump.c's minimum=1 path
 * (find_cross_jump(insn, JUMP_LABEL(insn), 1) — jump.c:1978) against case 3's trailing `addiu`,
 * so the minimum=2 jump_chain path fires instead and welds case-0 arm1 into arm2 (a 3-insn tail
 * at a new label) — a merge the target does not have. Written LONGHAND (each arm stores 0x34
 * itself and `return`s), every arm gets its own single-block temp, all of them land in $v0, and
 * the compiler makes exactly the target's merge. Cf. §162h's floor law read from the other side:
 * here the source-level factoring is what has to be REMOVED. */

extern void func_8012CBF4(s32 a0);   /* canonical `void`; $v0 is used in case 0 -> cast at the site */
extern s32  func_8012B8E4(s32 a0, s32 a1);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern void func_80184888(s32 out, s32 a1, s32 a2);
extern s32  func_8018485C(s32 arg0);

void func_801841A4(s32 a0) {

    extern u8 D_801A2F4C[];
    s32 sp10[4];   /* 0x10: the func_8012B77C "to" record — fields at +0x2/+0x6/+0xA */
    s32 sp20[2];   /* 0x20: the 8-byte out buffer shared by func_80184888 and func_8012B77C */
    s32 t;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (((s32 (*)(s32))func_8012CBF4)(a0) != 0) {
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            return;
        } else {
            if (*(s16 *)(a0 + 0x100) >= *(s16 *)(a0 + 0xA)) {
                return;
            }
            *(s16 *)(a0 + 0xA) = *(s16 *)(a0 + 0x100);
            *(s32 *)(a0 + 0x1C) = 0x1E;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
            return;
        }

    case 1:
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) += func_8012B8E4(a0, 6);
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        func_8012B200((u8 *)a0);
        *(s32 *)(a0 + 0x1C) = 0x20;
        func_8002D4C8(0x6FF, 0);
        return;

    case 2:
        func_80184888((s32)sp20, a0, (s32)D_801A2F4C);
        t = sp20[0];
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t >> 16;
        func_8012B178(a0, *(s32 *)(a0 + 0xE0) - 0x80000);
        func_8012CBF4(a0);
        if (func_8018485C(a0) != 1) {
            if (func_8012BEE8(a0) == 0) {
                return;
            }
        }
        *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        *(s16 *)((s32)sp10 + 0x2) = *(u16 *)(a0 + 0x88);
        *(s16 *)((s32)sp10 + 0x6) = *(u16 *)(a0 + 0x8A);
        *(s16 *)((s32)sp10 + 0xA) = *(u16 *)(a0 + 0x8C);
        func_8012B77C((s32)sp20, a0 + 4, (s32)sp10);
        t = sp20[0];
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t >> 16;
        func_8012B2CC(a0);
        func_8012B178(a0, *(s32 *)(a0 + 0xE0) - 0x80000);
        *(s32 *)(a0 + 0x1C) = 0x80;
        return;

    case 3:
        func_8012CBF4(a0);
        if (func_8012BEE8(a0) == 0) {
            if (*(s16 *)(a0 + 0xA) >= *(s16 *)(a0 + 0x8A)) {
                return;
            }
        }
        *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0x8A);
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
        *(s32 *)(a0 + 0x1C) = 0x3C;
        *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        return;

    case 4:
        if (func_8012BEE8(a0) == 0) {
            return;
        }
        /* fall through */
    default:
        *(s16 *)(a0 + 0x2) = 4;
        return;
    }
}

#include "common.h"

/* Declarations copied VERBATIM from the destination TU (src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c)
 * where they are already established for the near-identical sibling func_801841A4's case 2
 * (same sp10[4]/sp20[2] shared-buffer idiom, same func_8012B77C "to" record):
 *   func_8012BEE8   TU:5640   extern s32  func_8012BEE8(s32 a0);
 *   func_8012B2CC   TU:5644 / 2523 / 4913   extern void func_8012B2CC(s32 a0);
 *   func_8012B178   TU:5643 / 5635   extern void func_8012B178(s32 a0, s32 a1);
 *   func_8012B77C   TU:5645   extern s32  func_8012B77C(s32 out, s32 from, s32 to);
 *   func_8012B0B4   TU:6779   extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
 *   func_8012E88C   TU:6520   extern void func_8012E88C(u8 *a0);
 *   func_8012A828   TU:7157   extern void func_8012A828(s32 a0, s32 a1);
 * D_801A5984 is not declared in this TU; other overlays (ov_SC03_113) know it as a 10-entry
 * s32/fnptr array, but here only its ADDRESS is taken (passed through as an opaque s32/void*
 * to func_8012A828), so it is declared in the rawest form per law 4, matching this TU's own
 * D_801A0CB8 idiom at line 4670 (`extern u8 D_801A0CB8[];` ... `(s32)D_801A0CB8`).
 */
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_8012E88C(u8 *a0);
extern void func_8012A828(s32 a0, s32 a1);
extern s32  rand(void);
extern u8   D_801A5984[];

void func_8018440C(s32 a0) {
    s32 sp10[4];   /* 0x10: the func_8012B77C "to" record — fields at +0x2/+0x6/+0xA */
    s32 sp20[2];   /* 0x20: the 8-byte out buffer shared by func_8012B0B4 and func_8012B77C */
    s32 t;
    s32 r;

    if (func_8012BEE8(a0) == 0) {
        return;
    }

    if (*(u16 *)(a0 + 0x70) & 1) {
        *(s16 *)(a0 + 0x2) = 1;
    } else {
        *(s16 *)(a0 + 0x2) = 3;
        r = rand();
        func_8012B0B4((unsigned int *)sp20, r % 0x1000, 0x100);
        t = sp20[0];
        *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) + t;
        *(s16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) - 0x100;
        *(s16 *)(a0 + 0xE) = *(u16 *)(a0 + 0xE) + (t >> 16);
        *(s16 *)((s32)sp10 + 0x2) = *(u16 *)(a0 + 0x88);
        *(s16 *)((s32)sp10 + 0x6) = *(u16 *)(a0 + 0x8A);
        *(s16 *)((s32)sp10 + 0xA) = *(u16 *)(a0 + 0x8C);
        func_8012B77C((s32)sp20, a0 + 4, (s32)sp10);
        t = sp20[0];
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t >> 16;
        func_8012B2CC(a0);
        func_8012B178(a0, *(s32 *)(a0 + 0xE0));
    }

    *(s16 *)(a0 + 0x5C) = *(u16 *)(*(s32 *)(a0 + 0x78) + 0x2);
    *(s16 *)(a0 + 0x76) = *(u16 *)(*(s32 *)(a0 + 0x78) + 0x0);
    func_8012E88C((u8 *)a0);
    func_8012A828(a0, (s32)D_801A5984);

    {
        s32 u = *(s32 *)(a0 + 0xCC);
        if (u != 0) {
            *(s16 *)(u + 0xFC) = 0;
        }
    }
}


void func_8018455C(void *a0) {
    s32 v1 = *(s32 *)((char *)a0 + 0xCC);
    *(s16 *)((char *)a0 + 2) = 9;
    *(s32 *)((char *)a0 + 0x1C) = 0x20;
    *(s16 *)((char *)a0 + 0x34) = 0;
    if (v1 != 0) {
        *(s16 *)((char *)v1 + 0xFC) = 1;
    }
}


#include "common.h"

/* Declarations conformed to this TU's existing canonical forms (§193-B law 2):
 *   func_8012BEE8   ov_SC03_090_jr_8017CA80.c:5640  `extern s32  func_8012BEE8(s32 a0);`
 *   func_8012B200   ov_SC03_090_jr_8017CA80.c:5641  `extern void func_8012B200(u8 *a0);`
 *   func_8012B2CC   ov_SC03_090_jr_8017CA80.c:5644  `extern void func_8012B2CC(s32 a0);`
 *   func_8012B77C   ov_SC03_090_jr_8017CA80.c:5645  `extern s32  func_8012B77C(s32 out, s32 from, s32 to);`
 *   func_8012CBF4   ov_SC03_090_jr_8017CA80.c:5638  `extern void func_8012CBF4(s32 a0);` (return value unused here)
 *   func_8012B178   ov_SC03_090_jr_8017CA80.c:5643  `extern void func_8012B178(s32 a0, s32 a1);`
 *   func_8012B0B4   ov_SC03_090_jr_8017CA80.c:6779  `extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);`
 *   func_8012E8A8   ov_SC03_090_jr_8017CA80.c:6244/6677 `extern void func_8012E8A8(u8 *a0);`
 *   func_8012E778   not declared in this TU; project-canonical form used elsewhere
 *                   (e.g. ov_SC03_099_jr_80182F24.c:2769) `extern s32 func_8012E778(s32 a0, s32 a1);`
 *
 * Structural template: this TU's OWN func_801841A4 case 2 (same file, ~line 5685) walks the
 * identical func_8012B77C((s32)out, a0+4, (s32)to) / t=out[0] / store-split-into-(a0+0x20)
 * ->0x10/0x12 shape, and uses the same `s32 sp10[4]` "to"-record idiom with fields written at
 * byte offsets +0x2/+0x6/+0xA via `*(s16*)((s32)sp10 + N)`. Reused verbatim here. The banked
 * seed_ref ov_SC02_035:func_80183A14 supplied the `s16 r = rand(); func_8012B0B4(...)` /
 * `func_8012B200/func_8012B2CC/func_8012B178` tail shape.
 */
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012B2CC(s32 a0);
extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern void func_8012CBF4(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern void func_8012E8A8(u8 *a0);
extern s32  func_8012E778(s32 a0, s32 a1);
extern s32  rand(void);

void func_80184588(s32 a0)
{
    s32 sp10[6];   /* the func_8012B77C "to" record — fields at +0x2/+0x6/+0xA;
                    * sized 6 words (24B, not case2's 4) — the target's buf sits
                    * at sp+0x28, a full 24B above sp10's base at sp+0x10. */
    s32 sp28[2];   /* reused as both func_8012B0B4's dest and func_8012B77C's "out" */
    s32 t;
    s16 r;

    if (*(u16 *)(a0 + 0x34) == 0) {
        if (func_8012BEE8(a0) != 0) {
            r = rand();
            func_8012B0B4((unsigned int *)sp28, r % 0x1000, (r % 0x80) + 0xC0);

            t = sp28[0];
            *(s16 *)((s32)sp10 + 0x2) = t;
            *(s16 *)((s32)sp10 + 0x6) = *(s16 *)(a0 + 0xA) - 0x180;
            *(s16 *)((s32)sp10 + 0xA) = t >> 16;
            func_8012B77C((s32)sp28, a0 + 4, (s32)sp10);

            t = sp28[0];
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) = t;
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = t >> 16;
            func_8012B200((u8 *)a0);
            func_8012B2CC(a0);
            func_8012B178(a0, *(s32 *)(a0 + 0xE0) - 0x20000);
            *(s16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
    } else {
        func_8012CBF4(a0);
        if (func_8012E778(a0, 0xA000C8) == 0) {
            *(s16 *)(a0 + 0x2) = 0xA;
            *(s32 *)(a0 + 0x1C) = 0x80;
            func_8012E8A8((u8 *)a0);
        }
    }
}


#include "common.h"

extern s32  func_8012BEE8(s32 a0);
extern void func_8012E88C(u8 *a0);

void func_801846E4(s32 a0) {
    s32 u;

    if (func_8012BEE8(a0) != 0) {
        *(s16 *)(a0 + 0x2) = 1;
        func_8012E88C((u8 *)a0);
        u = *(s32 *)(a0 + 0xCC);
        if (u != 0) {
            *(s16 *)(u + 0xFC) = 0;
        }
    }
}


#include "common.h"

void func_80184734(s32 arg0) {
    s32 v = *(s32 *)(arg0 + 0xCC);

    if (v != 0) {
        *(s16 *)(v + 0xFC) = 1;
    }
}


extern void func_8002A04C(s32 a0);
extern void func_8012B200(u8 *a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8012C218(void *a0);

void func_80184750(void *arg0) {
    func_8002A04C((s32)arg0);

    if ((*(s16 *)((char *)arg0 + 0x70) & 0x8000) != 0) {
        s32 v1 = *(s32 *)((char *)arg0 + 0x20);
        *(s16 *)((char *)arg0 + 0x2) = 0x7;
        *(s8 *)((char *)arg0 + 0xC1) = 0;
        *(s32 *)((char *)arg0 + 0x1C) = 0x40;
        *(s16 *)((char *)arg0 + 0x5E) = 0;
        *(s16 *)((char *)arg0 + 0x5C) = 0;
        *(s16 *)((char *)v1 + 0x12) = 0;
        *(s16 *)((char *)v1 + 0x10) = 0;
        *(u16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x2C) &= 0xFFEF;
        *(s16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x18) =
            *(s16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x1A) =
            *(s16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x1C) = 0x1000;
        func_8012B200((u8 *)arg0);
        func_8012E8A8((u8 *)arg0);
        *(s16 *)((char *)arg0 + 0x6) = *(u16 *)((char *)arg0 + 0x88);
        *(s16 *)((char *)arg0 + 0xA) = *(u16 *)((char *)arg0 + 0x8A);
        *(s16 *)((char *)arg0 + 0xE) = *(u16 *)((char *)arg0 + 0x8C);
    } else {
        func_8012C218(arg0);
    }
}


void func_8018480C(void *a0) {
    extern u8 D_801A5984[];
    if (*(u16 *)((s32)a0 + 0x70) & 1) {
        *(s16 *)((s32)a0 + 0x2) = 1;
    } else {
        *(s16 *)((s32)a0 + 0x2) = 4;
    }
    *(s16 *)((s32)a0 + 0x5C) = *(u16 *)(*(s32 *)((s32)a0 + 0x78) + 0x2);
    func_8012A828((s32)a0, (s32)D_801A5984);
}



extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);
    extern u8 D_801A2FB0[];
    s32 func_8018485C(s32 arg0) {
        return ((s32 (*)(s32, void *, void *, s32))func_8012D5E4)(arg0, &D_801A2FB0[0], &D_801A2FB0[8], 5) != 0;
    }


extern s16 D_80126CBA;

void func_80184888(s32 out, s32 a1, s32 a2) {
    s32 sp10[4];
    s32 sp20;
    s16 *q;
    u16 *p;
    s16 t;
    extern s32 func_80184A04();
    register s32 dst __asm__("$2");

    q = &D_80126CBA;
    if (*q == 0) {
        if (func_80184A04(a1) == 0) {
            p = (u16 *)(q - 3);
            *(s32 *)(a1 + 0xDC) = 0;
        } else {
            p = (u16 *)(a1 + 0x88);
            *(s32 *)(a1 + 0xDC) = 1;
        }
    } else {
        p = (u16 *)(a1 + 0x88);
        *(s32 *)(a1 + 0xDC) = 1;
    }
    *(s16 *)((s32)sp10 + 0x2) = p[0] + *(u16 *)a2;
    t = p[1] + *(u16 *)(a2 + 2);
    *(s16 *)((s32)sp10 + 0x6) = t;
    *(s16 *)(a1 + 0x100) = t;
    *(s16 *)((s32)sp10 + 0xA) = p[2] + *(u16 *)(a2 + 4);
    func_8012B77C((s32)&sp20, a1 + 4, (s32)sp10);
    dst = (s32)out;
    *(s32 *)dst = sp20;
    __asm__ __volatile__("" : : "r" (dst));
}


INCLUDE_ASM("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80", func_80184958);


extern s32 func_8012BD14(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

/* The `register ... __asm__("$4")` pin on the FIRST call argument is load-bearing.
 * The target sets $a0 = 0x6FE in the ENTRY block (dbr steals it into the `bnez`
 * delay slot -- sched.md D1 backward fill), but a plain `s32 id = 0x6FE;` local is
 * rematerialised at the use site (single-set constant pseudo -> REG_EQUIV), so the
 * `li` sinks past the label into the join block and dbr fills the slot with the
 * if-body's `lui` instead (SHIFT-DRIFT/+1). Pinning the local to $a0 makes the `li`
 * a hard-reg set that stays where it is written, and the call's arg move degenerates
 * to a deleted `(set (reg 4) (reg 4))`. */
void func_80184998(void *a0) {
    register s32 id __asm__("$4");
    s32 vol;
    s32 t;

    vol = 0x7F;
    t = func_8012BD14((s32)a0);
    id = 0x6FE;
    if (t > 0x1000) {
        vol -= (t - 0x1000) / 0x2700;
    }
    func_8002D4C8(id, (vol | 0x1000) & 0xFFFF);
}


extern u8 D_80078EC1;
    s32 func_80184A04(void) {
        return *(u8 *)&D_80078EC1 == 0x15;
    }



extern void (*D_801A3030[])(void);

void func_80184A1C(void *a0) {
    D_801A3030[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012C194();
extern void func_8001CD9C(int, void *);
extern u8 D_801A34BC;
extern u8 D_801A2FC0;
extern u8 D_801A3000;

void func_80184A58(s32 param_1)
{
    s32 v0;
    s32 v1;
    s32 s0;
    u16 h;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }

    ((void (*)(s32, s32))func_8001C214)(v0, (s32)&D_801A34BC);

    s0 = ((s32 (*)(void))func_8012C194)();
    if (s0 != 0) {
        *(s32 *)(param_1 + 0xCC) = s0;
        ((void (*)(s32, void *))func_8001CD9C)(s0, &D_801A2FC0);
        *(u16 *)(s0 + 0x18) = 0x800;
        *(u16 *)(s0 + 0x1A) = 0x800;
        *(u32 *)(s0 + 4) |= 0x50000000;
    }

    v1 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x20;

    v1 = *(s32 *)(param_1 + 0x20);
    *(u32 *)(v1 + 0x80) = (s32)&D_801A3000;

    v0 = *(s32 *)(param_1 + 0x64);
    h = *(u16 *)(v0 + 0x36);
    *(u16 *)(param_1 + 2) = 1;
    *(u16 *)(param_1 + 0xFE) = h;
}


#include "common.h"

typedef struct { s16 a, b, c; } SV3x_80184B30;
typedef struct { s16 a, b, c, d; } SV4x_80184B30;

extern s32 D_801A3040;
extern void func_8012B23C(void *a0);
extern void func_80184E20(s32 param_1);
extern void func_80184E84(s32 param_1);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);

void func_80184B30(void *a0)
{
    s32 s0 = (s32)a0;
    s32 s1;
    SV3x_80184B30 out;

    s1 = *(s32 *)(s0 + 0x64);

    if (*(s16 *)(s0 + 0xFC) != 0) {
        *(s16 *)(s0 + 0x2) = 2;
        func_8012B23C((void *)s0);
        *(s32 *)(s0 + 0x1C) = 0x5A;
        return;
    }
    __asm__("" : "=r"(s0) : "0"(s0) : "memory");

    if (*(s16 *)(s0 + 0xFE) != *(s16 *)(s1 + 0x36)) {
        func_80184E20(s0);
        return;
    }

    func_8012F214(s1, (s32)&D_801A3040, (s32)&out);
    *(s16 *)(s0 + 0x6) = out.a;
    *(s16 *)(s0 + 0xA) = out.b;
    *(s16 *)(s0 + 0xE) = out.c;
    func_80184E84(s0);

    *(s32 *)(*(s32 *)(s0 + 0x20) + 0x20) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x20);
    *(SV4x_80184B30 *)(*(s32 *)(s0 + 0x20) + 0x10) = *(SV4x_80184B30 *)(*(s32 *)(s1 + 0x20) + 0x10);
    *(SV4x_80184B30 *)(*(s32 *)(s0 + 0x20) + 0x18) = *(SV4x_80184B30 *)(*(s32 *)(s1 + 0x20) + 0x18);
    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x2C) = *(s16 *)(*(s32 *)(s1 + 0x20) + 0x2C) | 0x20;
    *(s32 *)(*(s32 *)(s0 + 0x20) + 0x4) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x4);
}


#include "common.h"

/* Packed struct to trigger lwl/lwr unaligned block copy (same idiom as the
 * banked twin ov_SC02_011:func_8018754C's BlockData). */
typedef struct {
    u32 field0;
    u32 field1;
} __attribute__((packed, aligned(1))) Block8_80184C74;

extern Block8_80184C74 D_801CA864;
/* Canonical shared engine-core spelling (return read via call-site cast,
 * codebase idiom — see src/ov_SC03_099/ov_SC03_099_jr_8012ACE0.c:1694). */
extern void func_8012CC64(s32 a0, s32 a1);
extern void func_8012E8A8(u8 *a0);
extern void func_80185198(s32 arg0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_80184E58(s32 a0);
extern void func_80185138(s32 a0);

void func_80184C74(s32 a0)
{
    Block8_80184C74 buffer;
    s32 v0;
    s32 s1;

    buffer = D_801CA864;
    v0 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)&buffer);

    if (v0 & 0x2000) {
        *(s16 *)(a0 + 0x2) = 3;
        func_8012E8A8((u8 *)a0);
        func_80185198(*(s32 *)(a0 + 0xCC));
        s1 = 0;
        func_8012C588(0x1AA, a0);
        do {
            func_8012C588(0x1B0, a0);
        } while (++s1 < 8);
        func_8002D4C8(0x705, 0);
    } else {
        if (func_8012BEE8(a0) != 0) {
            *(s16 *)(a0 + 0x2) = 3;
            func_8012E8A8((u8 *)a0);
            func_80185198(*(s32 *)(a0 + 0xCC));
        } else {
            func_80184E58(a0);
            func_80185138(a0);
        }
    }
}


extern void func_8012E88C(u8 *a0);
extern void func_80184E20(s32 param_1);
extern void func_80185178(s32 arg0);
extern void func_8012B2CC(s32 a0);
extern void func_80185138(s32 a0);

void func_80184D74(void *a0) {
    if (*(s16 *)((s32)a0 + 0xFE) != *(s16 *)(*(s32 *)((s32)a0 + 0x64) + 0x36)) {
        func_80184E20((s32)a0);
        return;
    }

    if (*(s16 *)((s32)a0 + 0xFC) == 0) {
        *(s16 *)((s32)a0 + 0x2) = 1;
        func_8012E88C((u8 *)a0);
        func_80185178(*(s32 *)((s32)a0 + 0xCC));
        *(s32 *)((s32)a0 + 0x4) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x4);
        *(s32 *)((s32)a0 + 0x8) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x8);
        *(s32 *)((s32)a0 + 0xC) = *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0xC);
        func_8012B2CC((s32)a0);
        func_80185138((s32)a0);
    }
}



extern void func_80016714(void *a0, s32 a1);
    extern void func_8012C218(void *a0);
    void func_80184E20(s32 param_1) {
        s32 iVar1;
        iVar1 = *(s32 *)(param_1 + 0xcc);
        ((void (*)(s32 *, s32))func_80016714)((s32 *)iVar1, 0x38);
        ((void (*)(s32))func_8012C218)(param_1);
    }


extern s32 D_801A3048;
extern s32 func_8012D5E4(s32 a0, s32 a1, s32 a2, s32 a3);

    void func_80184E58(arg0)
s32 arg0;
{
        ((void (*)(void *, s32, s32, s32))func_8012D5E4)((void *)arg0, &D_801A3048, (s32)&D_801A3048 + 0x8, 0x5);
    }


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

/* func_80184E84 @ ov_SC03_089 (subseg ov_SC03_089_jr_8017CA80) — 173 ins.
 *
 * Template: engine_core.h DEFINE_func_8012EC04() — same RotMatrix-from-packed-word
 * decode + the same GTE column/translation tail, but composing into a SECOND matrix
 * and then feeding ((void (*)(s32, s32, s32))func_8012F14C)(SetRotMatrix/SetTransMatrix/RotTransSV).
 *
 * Two load-bearing details (do not "clean up" when templating to siblings):
 *  1) `LV_801851A8_80184E84 unused;` — the frame is 0x80, and out(8)+buf(8)+m1(32)+m2(32)
 *     only accounts for 0x50 of the 0x60 local area. gcc-2.7.2 keeps the slot of an
 *     unreferenced BLKmode local, so the dead 16-byte local is what makes sp == 0x80.
 *  2) `mk = 0x80000000;` BEFORE the if. gcc-2.7.2's cse is basic-block-local, so a
 *     constant parked in a named local one block earlier is NOT propagated into the
 *     arm: the pseudo stays live across the branch, which (a) flips the then-arm's
 *     local-alloc to ptr=$v1 / val=$v0 (matching the target) and (b) leaves the
 *     `lui $a0,0x8000` before the bgez where reorg's backward scan pulls it into the
 *     branch delay slot. Writing the literal inline gives ptr=$v0 / val=$v1 and a
 *     stolen `lui $v1,0x7fff` in the slot — 7 wrong instructions. Pin-free.
 */

typedef struct { short m[3][3]; long t[3]; } MTX_801851A8_80184E84;
typedef struct { short vx, vy, vz, pad; } SV_801851A8_80184E84;
typedef struct { long vx, vy, vz, pad; } LV_801851A8_80184E84;
typedef struct { u8 d[8]; } __attribute__((packed, aligned(1))) B8_801851A8_80184E84;

extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_80184E84(s32 param_1)
{

    extern SV_801851A8_80184E84 D_801A3058;
    SV_801851A8_80184E84 out;
    SV_801851A8_80184E84 buf;
    MTX_801851A8_80184E84 m1;
    MTX_801851A8_80184E84 m2;
    LV_801851A8_80184E84 unused;
    u32 w;
    s32 M;
    s32 c;
    s32 dst;
    s32 dp;
    u32 mk;
    s32 p;
    s32 mp;

    if (*(s32 *)(param_1 + 0xCC) != 0) {
        p = (s32)(*(u32 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x20) & 0xfeffffff);
        mp = (s32)&m1;
        buf.vx = *(s16 *)(p + 6);
        w = *(u32 *)p;
        buf.vy = (s16)(*(u8 *)(p + 1) | ((w & 0xf) << 8));
        buf.vz = (s16)(((w >> 0x10) & 0xff) | ((w & 0xf0) << 4));
        func_80049CAC((s32)&buf, mp);
        m1.t[0] = *(s8 *)(p + 3);
        m1.t[1] = *(s8 *)(p + 4);
        m1.t[2] = *(s8 *)(p + 5);

        /* gte_SetRotMatrix(M) */
        M = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
        __asm__ __volatile__(
            "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
            "ctc2 $12, $0\n" "ctc2 $13, $1\n"
            "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
            "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n"
            : : "r"(M) : "$12", "$13", "$14", "memory");

        /* column 0 */
        __asm__ __volatile__(
            "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
            "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
            "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
            : : "r"(mp) : "$12", "$13", "$14", "memory");
        dp = (s32)&m2;
        __asm__ __volatile__(
            "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
            "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
            : : "r"(dp) : "$12", "$13", "$14", "memory");

        /* column 1 */
        c = (s32)&m1 + 2;
        __asm__ __volatile__(
            "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
            "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
            "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
            : : "r"(c) : "$12", "$13", "$14", "memory");
        c = (s32)&m2 + 2;
        __asm__ __volatile__(
            "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
            "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
            : : "r"(c) : "$12", "$13", "$14", "memory");

        /* column 2 */
        c = (s32)&m1 + 4;
        __asm__ __volatile__(
            "lhu $12, 0(%0)\n" "lhu $13, 6(%0)\n" "lhu $14, 12(%0)\n"
            "mtc2 $12, $9\n" "mtc2 $13, $10\n" "mtc2 $14, $11\n"
            "nop\n" "nop\n" "mvmva 1, 0, 3, 3, 0\n"
            : : "r"(c) : "$12", "$13", "$14", "memory");
        c = (s32)&m2 + 4;
        __asm__ __volatile__(
            "mfc2 $12, $9\n" "mfc2 $13, $10\n" "mfc2 $14, $11\n"
            "sh $12, 0(%0)\n" "sh $13, 6(%0)\n" "sh $14, 12(%0)\n"
            : : "r"(c) : "$12", "$13", "$14", "memory");

        /* gte_SetTransMatrix(M) */
        M = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
        __asm__ __volatile__(
            "lw $12, 20(%0)\n" "lw $13, 24(%0)\n"
            "ctc2 $12, $5\n" "lw $14, 28(%0)\n"
            "ctc2 $13, $6\n" "ctc2 $14, $7\n"
            : : "r"(M) : "$12", "$13", "$14", "memory");

        /* gte_ldlv0(m1.t) ; gte_rt() ; gte_stlvnl(m2.t) */
        c = (s32)&m1 + 0x14;
        __asm__ __volatile__(
            "lhu $13, 4(%0)\n" "lhu $12, 0(%0)\n"
            "sll $13, $13, 16\n" "or $12, $12, $13\n"
            "mtc2 $12, $0\n" "lwc2 $1, 8(%0)\n"
            "nop\n" "nop\n" "mvmva 1, 0, 0, 0, 0\n"
            : : "r"(c) : "$12", "$13", "memory");
        c = (s32)&m2 + 0x14;
        __asm__ __volatile__(
            "swc2 $25, 0(%0)\n" "swc2 $26, 4(%0)\n" "swc2 $27, 8(%0)\n"
            : : "r"(c) : "memory");

        ((void (*)(s32, s32, s32))func_8012F14C)(dp, (s32)&D_801A3058, (s32)&out);

        dst = *(s32 *)(param_1 + 0xCC);
        *(B8_801851A8_80184E84 *)(dst + 8) = *(B8_801851A8_80184E84 *)&out;

        mk = 0x80000000;
        if (*(s32 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 4) < 0) {
            *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) | mk;
        } else {
            *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0xCC) + 4) & 0x7FFFFFFF;
        }
    }
}


void func_80185138(s32 a0) {
    s32 v1;

    v1 = *(s32 *)(a0 + 0xCC);
    if (v1 != 0) {
        *(u16 *)(v1 + 0x8) = *(u16 *)(a0 + 0x6);
        *(u16 *)(v1 + 0xA) = *(u16 *)(a0 + 0xA) - 0x19;
        *(u16 *)(v1 + 0xC) = *(u16 *)(a0 + 0xE);
    }
}


void func_80185178(s32 arg0) {
        if (arg0 != 0) {
            *(s32 *)(arg0 + 0x4) &= 0x7FFFFFFF;
        }
    }


void func_80185198(s32 arg0) {
        if (arg0 != 0) {
            M2C_FIELD(arg0, s32 *, 0x4) |= 0x80000000;
        }
    }


void func_801851B8(s32 arg0) {
    extern u8 D_801A300C[];
    extern u8 D_801A2FC0;
    extern u8 D_801A2FC1;
    extern u8 D_801A2FC2;
    extern s32 func_8004787C(s32 a0);
    register u8 *p __asm__("$4");
    register s32 i __asm__("$5");
    s32 t;

    t = ((func_8004787C((*(s32 *)(arg0 + 0x1C) << 6) & 0x7C0) * 100) >> 12) + 0x64;

    i = 0;
    p = D_801A300C;
    do {
        i++;
        p[2] = t;
        p[1] = t;
        p[0] = t;
        p += 0x10;
    } while (i < 3);

    D_801A2FC2 = t;
    D_801A2FC1 = t;
    D_801A2FC0 = t;

    *(s32 *)(arg0 + 0x1C) += 1;
}



extern void (*D_801A31A8[])(void);

void func_8018525C(void *a0) {
    D_801A31A8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80185298(s32 a0)
{
    /* [T51] scoped in from file scope (cookbook §103) */
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001CA1C(s32 a0, s32 a1);
    extern void func_8012A828(s32 a0, s32 a1);
    extern u8 D_801A3060[];
    extern u8 D_801A3120[];

    s32 unused[2];              /* dead 8-byte local — frame 0x28, not 0x20 */
    s32 s0;

    s0 = ((s32 (*)(void))func_8012C1B8)();
    if (s0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    /* store folded into the arg list: store RTL precedes the arg copy */
    func_8001CA1C(*(s32 *)(a0 + 0x20) = s0, (s32)D_801A3060);
    *(u16 *)(s0 + 0x18) = 0x2000;
    *(u16 *)(s0 + 0x1A) = 1;
    *(u16 *)(s0 + 0x2E) = 0xC004;
    *(s32 *)(s0 + 0x4) |= 0x50000000;
    *(u16 *)(s0 + 0x2C) |= 0x10;
    *(u16 *)(a0 + 0xA) -= 0x19;
    func_8012A828(a0, (s32)D_801A3120);
    *(u16 *)(a0 + 2) += 1;
}


#include "common.h"

extern s32  func_8004787C(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_80185484(s32 a0);

void func_80185354(s32 a0) {
    s32 ent = a0;
    s32 state = *(u16 *)(ent + 0x34);
    register s32 sub __asm__("$3");
    register s32 t __asm__("$2");
    s32 cnt;

    switch (state) {
    case 0:
        t = func_8004787C(*(s32 *)(ent + 0x1C) << 6);
        *(s16 *)(*(s32 *)(ent + 0x20) + 0x18) = t * 7;
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = t << 1;
        cnt = *(s32 *)(ent + 0x1C) + 1;
        *(s32 *)(ent + 0x1C) = cnt;
        if (cnt < 0x10) {
            break;
        }
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = 0x7000;
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = 0x2000;
        *(s32 *)(ent + 0x1C) = 0x40;
        *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        break;
    case 1:
        if (func_8012BEE8(ent) != 0) {
            *(s32 *)(ent + 0x1C) = 0x10;
            *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        }
        break;
    case 2:
        t = func_8004787C(*(s32 *)(ent + 0x1C) << 6);
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = t << 1;
        cnt = *(s32 *)(ent + 0x1C) - 1;
        *(s32 *)(ent + 0x1C) = cnt;
        if (cnt == 0) {
            func_8012C218((void *)ent);
            return;
        }
        break;
    }

    func_80185484(ent);
}


extern void func_80185484(s32 a0);

s32 func_80185484_body(s32 a0) __asm__("func_80185484");

s32 func_80185484_body(s32 a0) {
    extern void func_8012BE54(s32 a0);
    extern u16 D_80126B62;
    extern u8 D_801A31B0[];

    register s32 ent __asm__("$17");   /* $s1 */
    s32 p;
    s32 h;
    s32 h2;
    s32 ret;
    s32 s0;
    s32 r;
    s32 v;
    s32 g;
    s32 d;
    u16 arr[3];

    ent = a0;
    p = *(s32 *)(ent + 0x20);
    h = *(s16 *)(p + 0x18);
    __asm__("" : "=r"(h) : "0"(h));
    ret = ((s32 (*)(s32))func_8012BE54)(ent);
    s0 = h >> 8;
    if (ret > s0 * s0) {
        return 0;
    }
    v = *(s16 *)(ent + 0xA);
    h2 = *(s16 *)(*(s32 *)(ent + 0x20) + 0x1A);
    __asm__ __volatile__("" : "=r"(h2) : "0"(h2));
    g = *(s16 *)&D_80126B62;
    r = h2 >> 6;
    d = v - g;
    if (d >= 0 ? r < d : r < g - v) {
        return 0;
    }
    a0 = 1;
    arr[0] = *(u16 *)(ent + 0x6);
    arr[1] = *(u16 *)(ent + 0xA);
    arr[2] = *(u16 *)(ent + 0xE);
    func_8012F568(1, 0x4201, 0, 0x1C, (s32)arr, (s32)D_801A31B0);
}



extern void (*D_801A31B8[])(void);

void func_8018555C(void *a0) {
    D_801A31B8[*(u16 *)((s32)a0 + 0x2)]();
}




/* Sibling-first template: src/ov_SC06_032/ov_SC06_032_jr_8017C24C.c:4778 func_80184294
 * (banked/matched — same family, same struct-offset chain: func_8012C1B8 -> obj,
 * store obj to param_1+0x20, func_8001C214(obj,0), raw=rand() truncated to s16,
 * r=(s32)raw, flags|=0x10, v=r%384+0x400 written to obj+0x1c/0x1a/0x18, sgn=+-1
 * chosen from raw&1, obj+0x10 = sgn*(r%128)-0x300, obj+0x12 = r%4096, tail calls
 * func_8012B2CC/func_8012B178, then a repeated rand()%N +- C spread into a p[]
 * array at param_1+0xDC with p[1]/p[5]/p[9]/p[13] zeroed). This instance differs
 * only in: an extra obj+0x14=0 store, TWO tail helper calls (func_8012B2CC AND
 * func_8012B23C) instead of one, mod-8 (not mod-12) spread with +-0x10 (not
 * +-0x18), and a longer tail (0xFC/0xFD/0xFE bytes + 0x100 flag word).
 *
 * Declarations conformed to this TU's own canonical externs (grepped in one pass,
 * D2): func_8012C1B8/func_8012CAE4/func_8012B23C/func_8012B2CC at
 * src/ov_SC03_089/ov_SC03_089_jr_8017CA80.c:5114-5115,4924,2523 and
 * func_8001C214 at :5425. func_8012B178 is not yet declared in this TU; its
 * canonical extern form is copied verbatim from sibling TUs (e.g.
 * src/ov_SC03_099/ov_SC03_099_jr_80135A4C.c:273).
 *
 * Per-field +-0x10 sign derived directly from the target .s (bnez-taken/not-taken
 * addiu operands at each block, asm/ov_SC03_089/nonmatchings/.../func_80185598.s):
 *   0xDC:-0x10  0xE0:-0x10  0xE4:+0x10  0xE8:-0x10  0xEC:-0x10  0xF0:+0x10
 *   0xF4:+0x10  0xF8:+0x10
 * — the same alternating pattern (-,-,+,-,-,+,+,+) as the sibling's mod-12/0x18
 * block, just re-keyed to mod-8/0x10.
 */

extern s32 rand(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B23C(void *a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_80185598(s32 param_1) {

    s32 unused[2]; /* dead 8-byte local — frame padding (cookbook idiom 6) */
    s32 obj;
    s16 raw;
    s32 r;
    s32 sgn;
    s32 v;
    s32 q;
    s32 w;
    /* The `register ... __asm__("$4")` pin on the tail's +2-field counter is
     * load-bearing (matching-cookbook idiom 9 / L-lever family): unpinned, gcc
     * puts the 0x50000000 OR-mask constant in $a0 and the field value in $v1
     * (register-swapped vs. the target) and schedules the field's `lhu` right
     * before the `or` instead of hoisting it ahead of the 0xFC/FD/FE `sb`
     * stores. Pinning $4/$a0 to this value AND folding the `+1` into the same
     * statement as the load (`cnt = *(u16*)(param_1+2) + 1;`, store separate)
     * reproduces both the register choice and the exact schedule position. */
    register s32 cnt __asm__("$4");

    obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj == 0) {
        func_8012CAE4((void *)param_1);
        return;
    }
    *(s32 *)(param_1 + 0x20) = obj;
    func_8001C214(obj, 0);

    raw = rand();
    r = raw;
    *(u16 *)(obj + 0x2C) = *(u16 *)(obj + 0x2C) | 0x10;
    v = r % 384 + 0x400;
    *(s16 *)(obj + 0x1C) = v;
    *(s16 *)(obj + 0x1A) = v;
    *(s16 *)(obj + 0x18) = v;
    sgn = -1;
    if (raw & 1) {
        sgn = 1;
    }
    *(s16 *)(obj + 0x10) = sgn * (r % 128) - 0x300;
    *(s16 *)(obj + 0x12) = r % 4096;
    *(u16 *)(obj + 0x14) = 0;

    *(u16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x19;
    func_8012B2CC(param_1);
    func_8012B23C((void *)param_1);
    func_8012B178(param_1, -0xC0000 - ((r % 8) << 16));

    *(s32 *)(param_1 + 0x1C) = 0x5A;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xDC) = w;
    *(s16 *)(param_1 + 0xDE) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xE0) = w;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xE4) = w;
    *(s16 *)(param_1 + 0xE6) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xE8) = w;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q - 0x10;
    } else {
        w = q - 0x10;
    }
    *(s16 *)(param_1 + 0xEC) = w;
    *(s16 *)(param_1 + 0xEE) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xF0) = w;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xF4) = w;
    *(s16 *)(param_1 + 0xF6) = 0;

    q = rand() % 8;
    if ((rand() & 1) == 0) {
        w = -q + 0x10;
    } else {
        w = q + 0x10;
    }
    *(s16 *)(param_1 + 0xF8) = w;

    cnt = *(u16 *)(param_1 + 2) + 1;
    *(u8 *)(param_1 + 0xFC) = 0x80;
    *(u8 *)(param_1 + 0xFD) = 0x80;
    *(u8 *)(param_1 + 0xFE) = 0x80;
    *(u32 *)(param_1 + 0x100) = *(u32 *)(param_1 + 0x100) | 0x50000000;
    *(u16 *)(param_1 + 2) = cnt;
}


#include "common.h"

extern void func_8012CBCC(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012C218(void *a0);
extern void func_80017274(s32 a0, s32 a1);

void func_80185934(s32 param_1) {
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + 0x40;

    if (((s32 (*)(s32))func_8012CBCC)(param_1) != 0 || func_8012BEE8(param_1) != 0) {
        func_8012C218((void *)param_1);
    } else {
        func_80017274(param_1 + 0xDC, *(s32 *)(param_1 + 0x20) + 0x34);
    }
}


extern void (*D_801A5BC4[])(void);
extern void func_8012C0EC(void *a0);

void func_801859A8(void *a0) {
    D_801A5BC4[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        void *ptr = *(void **)((s32)a0 + 0x20);
        *(u16 *)((s32)ptr + 0x2C) |= 0x10;
        if (!(*(u16 *)((s32)a0 + 0x70) & 0x20)) {
            func_8012C0EC(a0);
        }
    }
}










extern s32 func_80186AAC(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012E8A8(u8 *a0);
extern void func_8012B2CC(s32 a0);
extern s32 rand(void);


void func_80185A34(s32 a0) {

    extern u8 D_801A5AE4[];
    extern u8 D_801A5B84[];
    s16 state;
    s16 flag;
    s32 p;
    s32 dst;

    if ((*(u16 *)(a0 + 0x70) & 0xF) == 0 && func_80186AAC() == 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    state = *(u16 *)(a0 + 0x70) & 0xF;
    if (func_8012C354(a0, (s32)(D_801A5AE4 + state * 0x34)) == 0) {
        return;
    }

    *(u8 *)(a0 + 0xC0) = 1;
    *(s32 *)(a0 + 0xBC) = (s32)D_801A5B84;
    *(s32 *)(a0 + 0xB4) = -2;
    *(s32 *)(a0 + 0xC4) |= 1;
    *(s16 *)(a0 + 0xFE) = (rand() % 16) + 8;

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) |= 0x10;

    flag = *(s16 *)(a0 + 0x70);
    if ((flag & 0x8000) == 0) {
        if ((flag & 0x800) != 0) {
            *(s16 *)(a0 + 0x2) = 5;
            func_8012E8A8((u8 *)a0);
        } else {
            *(s16 *)(a0 + 0x2) = 1;
        }
    } else {
        p = *(s32 *)(a0 + 0x64);
        *(s16 *)(a0 + 0x2) = 3;
        *(s16 *)(a0 + 0x5C) = 0;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = *(u16 *)(*(s32 *)(p + 0x20) + 0x12);
        dst = *(s32 *)(a0 + 0x20);
        *(s16 *)(dst + 0x18) = *(s16 *)(dst + 0x1A) = *(s16 *)(dst + 0x1C) = 1;
        func_8012B2CC(a0);
    }
}


extern void func_8012B23C(void *a0);

void func_80185BA0(s32 a0) {
    func_8012B23C((void *)a0);
    *(s32 *)(a0 + 0x1C) = 0x40;
    *(s16 *)(a0 + 0x2) = 2;
    *(s16 *)(a0 + 0x34) = 0;
    *(s32 *)(a0 + 0xE4) = 0;
    *(s32 *)(a0 + 0xE8) = 0x40;
}



/* func_80185BE4 — ov_SC02_026 / ov_SC02_026_jr_8017C180.c   MATCH (230 ins)
 * Family exemplar: 6 members / 1380 templatable instructions (all 6 were in
 * nonmatchings, §136e — no twin existed, so this was derived from the .s).
 *
 * DERIVATION NOTES (each item moved the count):
 *
 *  1. `u8 *m = D_800AF630;` AS THE FIRST LOCAL (form copied verbatim from the
 *     banked sibling func_8017D77C, src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c:4273,
 *     and from GameModeDispatch in src/boot.c).  The target builds the base in a
 *     register (`lui/addiu $s2` then `lui $at,1 / addu / lhu -0x5C56($at)`), NOT
 *     `%hi(D_800AF630+0xA3AA)` — that split only happens for a REGISTER base, i.e.
 *     a pointer local.  Declaring it first makes it live across the func_8004787C
 *     call, which is what puts it in a callee-saved reg; global-alloc's density
 *     sort then hands out $s0=a0, $s1=ang, $s2=m exactly as the target has them.
 *
 *  2. FRAME PADDING (idiom 6).  All 14 initial mismatches were sp-relative
 *     immediates off by a uniform 0x10: 16 bytes of DEAD locals sit at sp+0x10
 *     (frame 0x30, saves at 0x20..0x2C).  It must be an AGGREGATE — a scalar
 *     becomes a pseudo and vanishes.  `s32 pad[4]` closed 10 of 14.
 *
 *  3. THE $a1 PIN ON THE func_8012B178 ARGUMENT (§40; same lever, same register,
 *     as the banked sibling func_8018389C at TU:5062).  Target emits
 *         addiu $a1,$v0,-0x4000 / jal func_8012B178 / addu $a0,$s0,$zero
 *     i.e. the a1 setup FIRST and the a0 move stolen into the call's delay slot.
 *     Written as `func_8012B178(a0, t - 0x4000)` combine folds the subtract into
 *     the a1 arg-MOVE, which is emitted AFTER the a0 move, so the two swap
 *     (SCHEDULE-REORDER/4, both in case 0 and case 1).  Hoisting the subtract to
 *     its own statement does NOT help (combine still merges it into the move —
 *     A/B tested), and a §21 zero-byte re-tie on `t` does not either.  A local
 *     pinned to $5 makes the addiu a BODY insn at the join, so the a0 move is the
 *     last insn before the jal and dbr steals it.  This is not a parameter pin
 *     (S3), it is the arg-value pin.
 *
 *  4. `r` IS A LOCAL IN case 0 BUT INLINED IN case 1 (§136 L1/L3).  case 0 tests
 *     func_8012CBA4's result twice, so the pseudo outlives $v0 and lands in $v1
 *     (`addu $v1,$v0,$zero` + two `andi` off $v1); case 1 tests it once and the
 *     target has `andi $v0,$v0,0x2000` with no copy — so it must NOT be a local
 *     there.
 *
 *  5. BRANCH POLARITY on the ±offset pick (§3-T4 / T7).  The target is
 *         bnez $v0,L / addu $v0,$s2,$s1 (DELAY SLOT) / subu $v0,$s2,$s1 / L:
 *     The delay-slot insn is the ELSE arm, moved (not copied) by
 *     fill_slots_from_thread because the label is own_thread.  That requires the
 *     THEN arm to be the subtract, i.e. `if ((rand() & 1) == 0) v = base - off;
 *     else v = base + off;`.  The natural spelling `if (rand() & 1) v = base+off;`
 *     puts the subtract in the slot instead.  The single trailing `sw` also
 *     requires the store to be AFTER the if/else on a local `v`, not duplicated
 *     into both arms.
 *
 *  6. THE 3x DUPLICATED "go to state 2" TAIL IS REAL SOURCE DUPLICATION.  jump.c's
 *     cross-jumping (2nd jump_optimize, post-reload) merges the three identical
 *     copies into the one block at 0x801818F4 and redirects case 0's two arms into
 *     it — case 0's `&0x8000` arm to 0x801818F4 and its `!&0x2000` arm to the
 *     func_8012ADE4 head at 0x801818EC.
 *
 * DECLARATION SURFACE (whole-TU one-pass grep, D2 — above AND below the splice at
 * TU:4477; the spliced TU was compiled end-to-end and its codegen for this
 * function is identical to the standalone compile modulo $L numbering):
 *   copied VERBATIM from the TU's existing spelling —
 *     D_800AF630    (TU:53, file scope)      func_8004787C (TU:2206)
 *     func_8012B8E4 (TU:4901)                func_8012CBA4 (TU:4343/4768, `void`
 *                                              -> return taken through a cast, idiom 9)
 *     func_8012B608 (TU:4163/5051)           func_8012BEE8 (TU:6145)
 *     func_8012B030 (TU:4480, `u8 *`)        rand          (TU:957; TU:1092 has the
 *                                              equivalent `int` form — never redeclared)
 *   NOT declared anywhere in the TU or in common.h/engine_core.h, so the canonical
 *   fleet form is used —
 *     func_8012B178 / func_8012ADE4 : the engine_core.h DEFINE_func_* bodies
 *       (L4288 / L1724) and the 10 sibling TUs all use exactly these two forms.
 *     func_80186944 / func_80186874 : only INCLUDE_ASM lines (TU:4504/4506), which
 *       declare nothing.
 *     D_801A5BE0 : real dlabel in asm/ov_SC02_026/data/tail.data.s:43706; the
 *       0x70&0xF index runs past its 2 words into the following dlabels, so it must
 *       be an unsized `s32 []`.
 */

extern s32 func_8004787C(s32 a0);
extern s32 func_8012B8E4(s32 a0, s32 a1);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012CBA4(s32 a0);
extern void func_8012ADE4(u8 *a0);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 rand(void);
extern void func_80186944(s32 a0);
extern void func_80186874(s32 a0, s32 a1);

void func_80185BE4(s32 a0) {

    extern u8 D_800AF630[];
    extern s32 D_801A5BE0[];
    s32 pad[4];   /* idiom 6: 16 bytes of dead locals at sp+0x10 => frame 0x30 */
    u8 *m = D_800AF630;
    s32 ang;
    s32 off;
    s32 base;

    ang = func_8004787C(*(s32 *)(a0 + 0xE4));
    if (*(s16 *)(a0 + 0xAA) == 0) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = (ang >> 2) + 0x1000;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x1000 - (ang >> 1);
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = (ang >> 1) + 0x1000;
    } else {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = (ang >> 3) + 0x700;
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x700 - (ang >> 2);
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = (ang >> 2) + 0x700;
    }

    if (*(u16 *)(m + 0xA3AA) % *(s16 *)(a0 + 0xFE) == 0) {
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + func_8012B8E4(a0, 0x20);
    }

    switch (*(u16 *)(a0 + 0x34)) {
    case 0: {
        s32 t;
        s32 r;
        if (ang >= 0) {
            t = -(ang << 4);
        } else {
            t = ang << 4;
        }
        {
            register s32 av __asm__("$5");
            av = t - 0x4000;
            func_8012B178(a0, av);
        }
        r = ((s32 (*)(s32))func_8012CBA4)(a0);
        if (r & 0x8000) {
            *(u16 *)(a0 + 0x34) = 2;
            *(s32 *)(a0 + 0xE0) = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800;
            *(s32 *)(a0 + 0x1C) = rand() % 10 + 0x14;
        } else if ((r & 0x2000) == 0) {
            func_8012ADE4((u8 *)a0);
            *(u16 *)(a0 + 0x34) = 2;
            *(s32 *)(a0 + 0xE0) = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800;
            *(s32 *)(a0 + 0x1C) = rand() % 10 + 0x14;
        } else if (--*(s32 *)(a0 + 0xE8) == 0) {
            if (rand() & 1) {
                s32 v;
                *(u16 *)(a0 + 0x34) = 1;
                *(s32 *)(a0 + 0x1C) = 0x20;
                off = rand() % 1024;
                base = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12);
                if ((rand() & 1) == 0) {
                    v = base - off;
                } else {
                    v = base + off;
                }
                *(s32 *)(a0 + 0xE0) = v;
            } else {
                *(s32 *)(a0 + 0xE8) = 0x40;
            }
        }
        break;
    }
    case 1: {
        s32 t;
        s32 d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              *(s32 *)(a0 + 0xE0), 0x14);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        if (ang >= 0) {
            t = -(ang << 4);
        } else {
            t = ang << 4;
        }
        {
            register s32 av __asm__("$5");
            av = t - 0x4000;
            func_8012B178(a0, av);
        }
        if ((((s32 (*)(s32))func_8012CBA4)(a0) & 0x2000) == 0) {
            func_8012ADE4((u8 *)a0);
            *(u16 *)(a0 + 0x34) = 2;
            *(s32 *)(a0 + 0xE0) = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) + 0x800;
            *(s32 *)(a0 + 0x1C) = rand() % 10 + 0x14;
        } else if (func_8012BEE8(a0) != 0) {
            *(u16 *)(a0 + 0x34) = 0;
            *(s32 *)(a0 + 0xE8) = 0x40;
        }
        break;
    }
    case 2: {
        s32 d = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                              *(s32 *)(a0 + 0xE0), 0x14);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + d;
        if (func_8012BEE8(a0) != 0) {
            *(u16 *)(a0 + 0x34) = 0;
            func_8012B030((u8 *)a0);
        }
        break;
    }
    }

    func_80186944(a0);
    func_80186874(a0, D_801A5BE0[*(u16 *)(a0 + 0x70) & 0xF]);
    *(s32 *)(a0 + 0xE4) = (*(s32 *)(a0 + 0xE4) + 0x40) & 0x7FF;
    if (*(s32 *)(a0 + 0x14) > 0x100000) {
        *(s32 *)(a0 + 0x14) = 0x100000;
    }
}


extern s32 func_8012B030(u8 *a0);
    void func_80185F7C(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 1;
        *(s16 *)((s32)a0 + 0x2) = 4;
        ((void (*)(void))func_8012B030)();
    }


extern s32 func_8004787C(s32 a0);

void func_80185FA8(s32 a0) {
    s32 p;
    s16 t;

    p = *(s32 *)(a0 + 0x20);
    t = func_8004787C(*(s32 *)(a0 + 0x1C) << 6);
    *(s16 *)(p + 0x1C) = t;
    *(s16 *)(p + 0x1A) = t;
    *(s16 *)(p + 0x18) = t;
    if (++*(s32 *)(a0 + 0x1C) >= 0x11) {
        *(s16 *)(a0 + 2) = 1;
        *(u16 *)(a0 + 0x5C) = *(u16 *)(*(s32 *)(a0 + 0x78) + 2);
    }
}


extern s32 func_8012BEE8(s32 a0);

void func_80186020(s32 a0) {
    s32 v1;

    if (func_8012BEE8(a0) != 0) {
        v1 = *(s32 *)(a0 + 0x20);
        *(s16 *)(a0 + 0x2) = 6;
        *(s16 *)(a0 + 0x34) = 0;
        *(s16 *)(v1 + 0x1C) = 0x400;
        *(s16 *)(v1 + 0x18) = 0x400;
        v1 = *(s32 *)(a0 + 0x20);
        *(s16 *)(v1 + 0x1A) = 0x3000;
    }
}



extern void func_8012BE54(s32 a0);
extern void func_8012CBCC(s32 a0);
extern void func_8012E88C(u8 *a0);
extern void func_8012B21C(void *a0);
extern s32 func_8004787C(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186074(s32 a0) {
    register s32 state __asm__("$16");   /* $s0 */
    register s32 ent   __asm__("$17");   /* $s1 */
    s32 sub;
    s32 t;
    s32 v;
    s32 cnt;

    ent = a0;
    __asm__ volatile("" ::: "$4");
    state = *(u16 *)(ent + 0x34);

    switch (state) {
    case 0:
        if (0x10000 < ((s32 (*)(s32))func_8012BE54)(ent)) {
            return;
        }
        *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        func_8012E88C((u8 *)ent);
        func_8012B21C((void *)ent);
        return;
    case 1:
        if ((((s32 (*)(s32))func_8012CBCC)(ent) & 0x2000) == 0) {
            return;
        }
        *(s32 *)(ent + 0x1C) = state;
        *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        func_8002D4C8(0x703, 0);
        /* fallthrough */
    case 2:
        sub = *(s32 *)(ent + 0x20);
        t = func_8004787C(*(s32 *)(ent + 0x1C) << 7);
        v = (t * 0x1c00 >> 12) + 0x400;
        *(s16 *)(sub + 0x1C) = v;
        *(s16 *)(sub + 0x18) = v;
        {
            s32 w = 0x3000 - (t * 0x2800 >> 12);
            *(s16 *)(sub + 0x1A) = w;
        }
        cnt = *(s32 *)(ent + 0x1C) + 1;
        *(s32 *)(ent + 0x1C) = cnt;
        if (cnt < 9) {
            return;
        }
        *(s32 *)(ent + 0x1C) = 1;
        *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        return;
    case 3:
        sub = *(s32 *)(ent + 0x20);
        t = func_8004787C(*(s32 *)(ent + 0x1C) << 7);
        {
            register s32 lo __asm__("$3");
            lo = (t << 12) >> 12;
            v = 0x2000 - lo;
        }
        *(s16 *)(sub + 0x1C) = v;
        *(s16 *)(sub + 0x18) = v;
        {
            s32 w = ((t * 0x800) >> 12) + 0x800;
            *(s16 *)(sub + 0x1A) = w;
        }
        cnt = *(s32 *)(ent + 0x1C) + 1;
        *(s32 *)(ent + 0x1C) = cnt;
        if (8 < cnt) {
            *(u16 *)(ent + 2) = 1;
        }
        return;
    }
}


extern s32 rand(void);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012B23C(void *a0);
extern s32 func_80186B00(void *a0, s32 a1, s32 a2, s32 a3);

void func_80186224(s32 param_1) {
    s32 i;
    s32 neg;
    s32 base;
    s32 r;
    s32 q;
    s32 w;

    i = 0;
    neg = -0x40000;
    base = ((*(u16 *)(param_1 + 0x70) & 0xF) | -0x8000) << 16;
    do {
        r = rand();
        w = r;
        if (r < 0) {
            w = r + 3;
        }
        q = w >> 2;
        func_80186B00((void *)(param_1 + 0x7C),
                      *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12),
                      neg - ((r - q * 4) << 16), base >> 16);
        i++;
    } while (i < 4);

    *(s32 *)(param_1 + 0xEC) = 0x40000;
    func_8012B23C((void *)param_1);
    func_8012B178(param_1, *(s32 *)(param_1 + 0xEC));

    *(s32 *)(param_1 + 0x1C) = 0x10;
    *(u16 *)(param_1 + 0x34) = 0;
}



extern s32 func_80047948(s32 a0);
extern void func_8012CBA4(s32 a0);
extern void func_8012CBF4(s32 a0);
extern void func_8012B23C(void *a0);
extern s32 func_8012BEE8(s32 a0);
extern s32 func_80143B6C(s32 a0, s32 a1);
extern void func_80131C78(s32 a0);
extern void func_80131E00(void *a0, s32 a1);

void func_801862F0(s32 a0) {
    s32 delta;
    s32 ret;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        delta = func_80047948((*(s32 *)(a0 + 0x1C) - 1) << 6) -
                func_80047948(*(s32 *)(a0 + 0x1C) << 6);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) + delta;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) - (delta >> 3);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) + delta;
        ret = ((s32(*)(s32))func_8012CBA4)(a0);
        if (ret & 0x1000) {
            func_80131E00((void *)a0, 0x12);
            break;
        }
        if ((ret & 0x2000) == 0) {
            func_8012B23C((void *)a0);
            *(u16 *)(a0 + 0x34) = 2;
            *(s32 *)(a0 + 0x1C) = 0x3C;
            break;
        }
        if (*(s32 *)(a0 + 0x1C) % 3 == 0) {
            func_80143B6C(a0, 1);
        }
        if (func_8012BEE8(a0) != 0) {
            *(u16 *)(a0 + 0x34) = 1;
        }
        break;
    case 1:
        delta = func_80047948((*(s32 *)(a0 + 0x1C) + 1) << 6) -
                func_80047948(*(s32 *)(a0 + 0x1C) << 6);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) + delta;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) - (delta >> 3);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) + delta;
        *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) + 1;
        if (*(s32 *)(a0 + 0x1C) >= 0x10) {
            func_80131C78(a0);
        }
        break;
    case 2:
        ret = ((s32(*)(s32))func_8012CBF4)(a0);
        if (ret & 0xFF) {
            func_801867C8(a0);
        } else if (ret & 0x2000) {
            func_80131C78(a0);
        } else if (func_8012BEE8(a0) != 0) {
            func_80131E00((void *)a0, 0xD);
        }
        break;
    }

    if (*(s32 *)(a0 + 0x14) > 0x100000) {
        *(s32 *)(a0 + 0x14) = 0x100000;
    }
}


void func_80186554(void *a0) {
        *(unsigned short *)((char *)a0 + 0x2) = 1;
        *(unsigned short *)((char *)a0 + 0x5c) = 0xa810;
    }



extern s32 rand(void);
extern s32 func_80186B00(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_8012E8A8(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186568(s32 a0) {
    u16 buf[3];
    register s32 angle1 __asm__("$23");
    register s32 angle2 __asm__("$22");
    s32 maskraw;
    s32 flags;
    register s32 head1 __asm__("$18");
    register s32 head2 __asm__("$17");
    register s32 i __asm__("$19");
    s32 ret1;
    s32 ret2;

    buf[0] = *(u16 *)(a0 + 0x6);
    buf[1] = *(u16 *)(a0 + 0xA);
    buf[2] = *(u16 *)(a0 + 0xE);
    head1 = 0;
    head2 = 0;
    {
        register s32 fieldval __asm__("$3") = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12);
        angle1 = fieldval + 0x400;
        flags = *(u16 *)(a0 + 0x70);
        maskraw = flags & 0xF;
        angle2 = fieldval - 0x400;
    }

    if ((flags & 1) == 0) {
        register s32 mask __asm__("$16");
        register s32 negoffset __asm__("$17");
        i = 0;
        negoffset = -0x60000;
        mask = maskraw;
        while (i < 4) {
            __asm__ __volatile__("" : "=r"(angle1) : "0"(angle1));
            func_80186B00(buf, angle1 * 0x10000 >> 0x10, rand() % 4 * -0x10000 + negoffset, mask);
            __asm__ __volatile__("" : "=r"(angle2) : "0"(angle2));
            func_80186B00(buf, angle2 * 0x10000 >> 0x10, rand() % 4 * -0x10000 + negoffset, mask);
            i++;
        }
    } else {
        s32 mask;
        i = 0;
        mask = maskraw;
        for (; i < 4; i++) {
            __asm__ __volatile__("" : "=r"(angle1) : "0"(angle1));
            __asm__ __volatile__("" : "=r"(angle2) : "0"(angle2));
            ret1 = func_80186B00(buf, angle1 * 0x10000 >> 0x10, rand() % 4 * -0x10000 + -0x60000, mask);
            ret2 = func_80186B00(buf, angle2 * 0x10000 >> 0x10, rand() % 4 * -0x10000 + -0x60000, mask);
            if (ret1 != 0) {
                if (head1 != 0) {
                    *(s32 *)(ret1 + 0x2C) = head1;
                    *(s32 *)(head1 + 0x30) = *(s32 *)(head1 + 0x30) + 1;
                } else {
                    *(s32 *)(ret1 + 0x2C) = -1;
                    *(s32 *)(ret1 + 0x24) = a0;
                    head1 = ret1;
                }
            }
            if (ret2 != 0) {
                if (head2 != 0) {
                    *(s32 *)(ret2 + 0x2C) = head2;
                    *(s32 *)(head2 + 0x30) = *(s32 *)(head2 + 0x30) + 1;
                } else {
                    *(s32 *)(ret2 + 0x2C) = -1;
                    *(s32 *)(ret2 + 0x24) = a0;
                    head2 = ret2;
                }
            }
        }
    }

    func_8012E8A8((u8 *)a0);
    func_8002D4C8(0xA65, 0);
}


extern void func_8012B2CC(s32 a0);
extern void func_8012C098(void *param_1);

void func_801867C8(arg0)
s32 arg0;
{
    register s32 a3 __asm__("$7");
    register s32 v1 __asm__("$3");
    register s32 v0 __asm__("$2");
    register s32 a0r __asm__("$4");
    register s32 a1r __asm__("$5");
    register s32 a2r __asm__("$6");

    a3 = arg0;
    v1 = *(u16 *)(a3 + 0x70);
    if ((v1 & 0x800) != 0) {
        v0 = v1 & 0x10;
        if (v0 != 0) {
            v0 = 5;
            v1 = *(s32 *)(a3 + 0x78);
            a0r = *(u16 *)(a3 + 0x88);
            a1r = *(s32 *)(a3 + 0x20);
            *(s16 *)(a3 + 0x2) = v0;
            v0 = 0x5A;
            *(s8 *)(a3 + 0xC1) = 0;
            *(s16 *)(a3 + 0x5E) = 0;
            *(s32 *)(a3 + 0x1C) = v0;
            v0 = *(u16 *)(v1 + 0x2);
            *(s16 *)(a3 + 0x5C) = v0;
            v0 = *(s32 *)(a3 + 0x78);
            v1 = *(u16 *)(a3 + 0x8C);
            a2r = *(u16 *)(v0 + 0x0);
            v0 = *(u16 *)(a3 + 0x8A);
            *(s16 *)(a3 + 0x6) = a0r;
            *(s16 *)(a3 + 0xE) = v1;
            *(s16 *)(a3 + 0xA) = v0;
            *(s16 *)(a3 + 0x76) = a2r;
            *(s16 *)(a1r + 0x10) = 0;
            v0 = *(s32 *)(a3 + 0x20);
            *(s16 *)(v0 + 0x12) = 0;
            *(s16 *)(a3 + 0xAA) = 0;
            func_8012B2CC(a3);
        } else {
            goto c098;
        }
    } else {
    c098:
        func_8012C098((void *)a3);
    }
}


extern s32 *D_80126B78;
extern u8 D_801A5BE8[];
extern u8 D_801152A8[];

extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);

void func_80186874(s32 arg0, s32 arg1) {
    register s32 rv __asm__("$2");
    s32 buf1[2];
    s32 buf2[2];

    ((void (*)(s32, s32, s32))func_8012F14C)((s32)D_80126B78 + 0x34, (s32)D_801A5BE8, (s32)buf1);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)D_80126B78 + 0x34, (s32)(D_801A5BE8 + 8), (s32)buf2);
    if (func_80135888(*(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x58), (s32)buf1, (s32)buf2) != 0) {
        func_8012F568(1, (*(u16 *)(arg0 + 0x70) & 0xF) != 0 ? 0x2001 : 1,
                      *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12), arg1,
                      (s32)buf2, (s32)D_801152A8);
        rv = 1;
    } else {
        rv = 0;
    }
    __asm__ __volatile__("" : "=r"(rv) : "0"(rv));
}


extern s32 func_8012CC88(s32 a0, s32 a1, s32 a2);
typedef struct {
    s32 w[4];
} Rec16_8017DDC4_80186944;
typedef struct {
    u16 x, y, z;
    s16 w;
} Rec8_8017DDC4_80186944;

/* func_80186944 -- ov_SC02_026 / ov_SC02_026_jr_8017C180
 * Same TU declares this at line 4712 (extern void func_80186944(s32 a0);) and
 * calls it at line 4822. Callee set derived from already-matched siblings in
 * THIS TU (§160g): func_8017FD58 (line 3739, Ent_8017FD58 loop-array idiom),
 * func_8012CC88 (src/shared/engine_core.h DEFINE_func_8012CC88, the sp10/sp18
 * SV3_8012CC88-from-0x3A/0x3E/0x42 pattern), and the ground-truth DEFINE_ bodies
 * for func_8012BC60 / func_8012B6D4 / func_8012B0B4 / func_8012CEB0 / func_8012ADE4.
 */

extern s32 func_8012BC60(struct Vec *a0, struct Vec *a1);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8012ADE4(u8 *a0);

void func_80186944(s32 a0) {

    extern u8 D_801202A0[];
    Ent_8017FD58 *e;
    s32 i;
    s16 *mover;
    s32 off;
    unsigned int *offp;
    s32 ang;
    s32 v0;
    SV3_8012CC88 sp10;
    SV3_8012CC88 sp18;

    e = (Ent_8017FD58 *)D_801202A0;
    i = 0;
    mover = (s16 *)(a0 + 4);
    offp = (unsigned int *)&off;
    for (; i < 0x60; i++, e++) {
        if (e->f0 == 0x17F && a0 != (s32)e &&
            func_8012BC60((struct Vec *)mover, (struct Vec *)&e->f4) < 0x1000) {
            ang = func_8012B6D4(mover, (s16 *)&e->f4);
            func_8012B0B4(offp, ang, 0x41);
            sp18.vx = e->x;
            sp18.vy = e->y;
            sp18.vz = e->z;
            sp18.vx += off;
            sp18.vz += (off >> 16);
            sp10.vx = *(u16 *)(a0 + 0x3A);
            sp10.vy = *(u16 *)(a0 + 0x3E);
            sp10.vz = *(u16 *)(a0 + 0x42);
            v0 = func_8012CEB0((s32)&sp10, (s32)&sp18, 0);
            if ((v0 & 0x2000) == 0) {
                func_8012ADE4((u8 *)a0);
                return;
            }
            *(s16 *)(a0 + 0x6) = sp18.vx;
            *(s16 *)(a0 + 0xA) = sp18.vy;
            *(s16 *)(a0 + 0xE) = sp18.vz;
            return;
        }
    }
}


INCLUDE_ASM("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80", func_80186AAC);


extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);

s32 func_80186B00(void *a0, s32 a1, s32 a2, s32 a3) {

    extern u16 D_801A5C04[][4];
    extern s32 D_801A5BF8[];
    u8 *obj;
    s32 sub;
    s32 rvA;
    s16 rvB;
    s32 p1;

    p1 = a1;
    obj = func_801290DC(0x41, (u8 *)a0);
    if (obj == 0) {
        return 0;
    }
    {
        s32 idx;

        rvA = rand();
        rvB = rvA;
        sub = *(s32 *)(obj + 0x20);
        *(s32 *)(sub + 0x20) = (s32) D_801A5BF8;
        idx = a3 & 0xF;
        {
            u16 *tbl = D_801A5C04[idx];
            *(u8 *)(sub + 0x27) = (u8) tbl[2];
            *(u16 *)(sub + 0x28) = tbl[0];
            *(u16 *)(sub + 0x2A) = tbl[1];
        }

        if ((a3 & 0x8000) != 0) {
            s16 spd = (rvA * 0x10000 >> 0x10) % 0x200 + 0x400;
            *(u16 *)(sub + 0x1A) = spd;
            *(u16 *)(sub + 0x18) = spd;
            *(s32 *)(obj + 0x34) = spd;
        } else {
            s16 spd = (rvA * 0x10000 >> 0x10) % 0xC00 + 0x400;
            *(u16 *)(sub + 0x1A) = spd;
            *(u16 *)(sub + 0x18) = spd;
            *(s32 *)(obj + 0x34) = spd;
        }

        {
            s32 sign;
            s32 h;
            s32 mod128;
            s16 srcvec[4];
            s32 buf[8];
            s32 trailing[4];

            sign = -1;
            if ((rvB & 1) != 0) {
                sign = 1;
            }
            h = rvB;
            mod128 = h % 128;

            srcvec[2] = 0;
            trailing[1] = 0;
            trailing[0] = 0;
            trailing[2] = a2;

            srcvec[0] = (s16) (sign * mod128 - 0x300);
            srcvec[1] = (s16) (p1 + sign * (h % 0x300));

            func_80049CAC((s32) srcvec, (s32) buf);
            func_800484EC((s32) buf, (s32) trailing, (s32) (obj + 0x10));
            *(s32 *)(obj + 0x1C) = 0x2D;
        }
    }
    return (s32) obj;
}



extern void (*D_801A5C14[])(void);

void func_80186D04(void *a0) {
    D_801A5C14[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80186D40(s32 arg0) {
    extern u8 D_800D3918[];
    s32 v1;
    s32 v0;

    v1 = func_801870EC(arg0, (s32)D_800D3918, 0x11);
    if ((v1 & 0xFF) != 0) {
        goto L80186DE0;
    }
    if (v1 & 0x2000) {
        if (*(s32 *)(arg0 + 0x2C) == 0) {
            goto L80186E08;
        }
        *(s32 *)(arg0 + 0x1C) = 0x1E;
        *(s16 *)(arg0 + 2) = 4;
        return;
    }
    /* L80186D98 */
    if (*(s32 *)(arg0 + 0x1C) < 0x23) {
        *(s32 *)(arg0 + 0x14) += 0x10000;
        if (*(s32 *)(arg0 + 0x2C) != 0) {
            *(u8 *)(*(s32 *)(arg0 + 0x20) + 0x27) = 0x62;
        }
    }
    /* L80186DCC */
    v0 = *(s32 *)(arg0 + 0x1C) - 1;
    *(s32 *)(arg0 + 0x1C) = v0;
    if (v0 != 0) {
        return;
    }
L80186DE0:
    v1 = *(s32 *)(arg0 + 0x2C);
    if (v1 == 0) {
        goto L80186E08;
    }
    if (v1 == -1) {
        goto L80186E08;
    }
    *(s32 *)(v1 + 0x30) -= 1;
L80186E08:
    func_801292C8((u8 *)arg0);
}


extern void func_80187318(s32 a0);

void func_80186E24(s32 arg0) {
    s32 temp_v0;
    func_80187318(arg0);
    if (*(s32 *)(arg0 + 0x30) == 0) {
        *(s16 *)(arg0 + 2) = 6;
        *(s32 *)(arg0 + 0x1c) = 0;
    } else {
        temp_v0 = *(s32 *)(arg0 + 0x1c) + 1;
        *(s32 *)(arg0 + 0x1c) = temp_v0;
    }
}



extern s32 func_80187240(s32 a0, s32 a1);
extern void func_801292C8(u8 *a0);
extern void func_80187318(s32 a0);
extern s32 func_801870EC(s32 a0, s32 a1, s32 a2);
extern s32 func_800132BC(s32 a0, s32 a1);

void func_80186E78(s32 a0) {

    extern u8 D_800D3918[];
    s32 partner;
    s32 ret;

    if (func_80187240(a0, -0x18000) == 0) {
        func_801292C8((u8 *)a0);
    } else {
        partner = *(s32 *)(a0 + 0x2C);
        *(s32 *)(a0 + 0x14) = 0x18000;

        if (*(s32 *)(a0 + 0x1C) >= 0x150) {
            *(s32 *)(partner + 0x30) -= 1;
            func_801292C8((u8 *)a0);
        } else {
            SV3_8012CC88 sp10;
            SV3_8012CC88 sp18;
            s32 pad[4];

            func_80187318(a0);
            func_801870EC(a0, (s32)D_800D3918, 0);

            sp10.vx = *(u16 *)(a0 + 0x6);
            sp10.vy = 0;
            sp10.vz = *(u16 *)(a0 + 0xE);
            sp18.vx = *(u16 *)(partner + 0x6);
            sp18.vy = 0;
            sp18.vz = *(u16 *)(partner + 0xE);

            ret = func_800132BC((s32)&sp10, (s32)&sp18);
            if (ret < 0x41) {
                *(s32 *)(partner + 0x30) -= 1;
                *(s16 *)(a0 + 0x2) = 5;
            }
            *(s32 *)(a0 + 0x1C) += 1;
        }
    }
}


extern void func_801292C8(u8 *a0);
    s32 func_80186F84(s32 arg0) {
        *(s32 *)(arg0 + 0x1c) -= 1;
        if (*(s32 *)(arg0 + 0x1c) == 0) {
            ((void (*)(void))func_801292C8)();
        }
    }


INCLUDE_ASM("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80", func_80186FB8);

extern void func_801292C8(u8 *a0);
extern void func_80187318(s32 a0);

void func_80186FF8(s32 arg0) {
    func_80187318(arg0);
    if (*(u16 *)(*(s32 *)(arg0 + 0x2c)) == 0) {
        func_801292C8((u8 *)arg0);
    }
    *(s32 *)(arg0 + 0x1c) += 1;
}


typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 type;
    u16 sub;
    s16 pad1;
    s16 flag;
    s16 pad2;
    s32 extra;
} Msg_80187050;

extern void func_80187318(s32 a0);
extern void func_801292C8(u8 *a0);
extern s32 func_8012C51C(void *a0, s32 a1);

void func_80187050(s32 a0) {
    Msg_80187050 msg;
    s32 t;

    func_80187318(a0);
    t = *(s32 *)(a0 + 0x1C) + 1;
    *(s32 *)(a0 + 0x1C) = t;
    if (t >= 0x1F) {
        msg.x = *(u16 *)(a0 + 0x6);
        msg.y = *(u16 *)(a0 + 0xA);
        msg.z = *(u16 *)(a0 + 0xE);
        msg.type = 0x17F;
        msg.sub = 0x8000;
        msg.pad1 = 0;
        msg.extra = 0;
        msg.pad2 = 0;
        msg.flag = 0x7FFF;
        func_8012C51C(&msg, *(s32 *)(a0 + 0x24));
        func_801292C8((u8 *)a0);
    }
}



extern void func_8012931C(struct vec *a0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);

/* a0 = actor/entity base (struct vec-compatible; s16 fields at +6/+A/+E, s32 flag/vel at +0x14),
 * a1 = s16[3] offset vector, a2 = mode passed through to func_8012CEB0.
 * Same family as func_8012CC88 (src/ov_SC02_027/ov_SC02_027_jr_8012ACE0.c etc) but the
 * position-integration step is a real call to func_8012931C instead of being inlined. */
s32 func_801870EC(s32 a0, s32 a1, s32 a2) {
    SV3_8012CC88 sp10;
    SV3_8012CC88 sp18;
    s32 v0;

    sp10.vx = *(u16*)(a0 + 0x06);
    sp10.vy = *(u16*)(a0 + 0x0A);
    sp10.vz = *(u16*)(a0 + 0x0E);
    sp10.vx += *(u16*)(a1 + 0);
    sp10.vy += *(u16*)(a1 + 2);
    sp10.vz += *(u16*)(a1 + 4);

    func_8012931C((struct vec *)a0);

    sp18.vx = *(u16*)(a0 + 0x06);
    sp18.vy = *(u16*)(a0 + 0x0A);
    sp18.vz = *(u16*)(a0 + 0x0E);
    sp18.vx += *(u16*)(a1 + 0);
    sp18.vy += *(u16*)(a1 + 2);
    sp18.vz += *(u16*)(a1 + 4);

    v0 = func_8012CEB0((s32)&sp10, (s32)&sp18, a2);

    sp18.vx -= *(u16*)(a1 + 0);
    sp18.vy -= *(u16*)(a1 + 2);
    sp18.vz -= *(u16*)(a1 + 4);
    *(s16*)(a0 + 0x06) = sp18.vx;
    *(s16*)(a0 + 0x0A) = sp18.vy;
    *(s16*)(a0 + 0x0E) = sp18.vz;

    if (v0 & 0x6000) {
        *(s32*)(a0 + 0x14) = 0;
    }
    return v0;
}




extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern Blk20 D_800AE620;

s32 func_80187240(s32 param_1, s32 param_2)
{
    s32 pad[4];
    Blk20 mat;
    s32 vec[3];
    u16 *var_a2;

    var_a2 = *(u16 **)(param_1 + 0x2C);
    if (*var_a2 == 0) {
        return 0;
    }
    mat = D_800AE620;
    RotMatrixY(
        func_8012B6D4((s16 *)(param_1 + 4), (s16 *)(var_a2 + 2)),
        &mat);
    vec[1] = 0;
    vec[0] = 0;
    vec[2] = param_2;
    func_800484EC((s32)&mat, (s32)vec, (s32)(param_1 + 0x10));
    return 1;
}


void func_80187318(s32 a0)
{
    s32 t = func_8004787C((*(s32 *)(a0 + 0x1C) << 7) & 0x780);
    s32 a = *(s32 *)(a0 + 0x34);
    s32 *p = *(s32 **)(a0 + 0x20);
    s32 r = a - ((a >> 2) * t >> 12);

    *(s16 *)((u8 *)p + 0x1A) = r;
    *(s16 *)((u8 *)p + 0x18) = r;
}



extern void (*D_801A5CA8[])(void);

void func_80187378(void *a0) {
    D_801A5CA8[*(u16 *)((s32)a0 + 0x2)]();
}




void func_801873B4(void *a0) {

    extern s32 D_801A5C30;
    register s32 p __asm__("$3");
    register s32 q __asm__("$2");
    p = *(u16 *)((char *)a0 + 0x2);
    q = (s32)&D_801A5C30;
    *(s32 *)((char *)a0 + 0xd0) = q;
    *(s32 *)((char *)a0 + 0xcc) = q;
    *(s32 *)((char *)a0 + 0xe0) = *(s32 *)q;
    p += 1;
    *(s16 *)((char *)a0 + 0x2) = p;
}


extern void func_800183E0(s32 a0);

void func_801873DC(s32 a0)
{
    s32 v0;
    s32 v1;
    s32 a1;

    v0 = *(s32 *)(a0 + 0xE0);
    if (v0 == 0) {
        goto END;
    }
    v0 = v0 - 1;
    *(s32 *)(a0 + 0xE0) = v0;
    if (v0 > 0) {
        goto END;
    }

    v1 = *(s32 *)(a0 + 0xD0);
    v1 = v1 + 8;
    a1 = *(s32 *)v1;
    if ((a1 & 0x40000000) != 0) {
        v1 = *(s32 *)(a0 + 0xCC);
    } else if (a1 < 0) {
        *(s32 *)(a0 + 0xE0) = 0;
        goto END;
    }

    v0 = *(s32 *)v1;
    *(s32 *)(a0 + 0xD0) = v1;
    *(s32 *)(a0 + 0xE0) = v0;
    func_800183E0(*(s32 *)(v1 + 4));

END:
    ;
}


#include "common.h"

extern s32 D_801A9058[];
extern void func_80187F4C(s32);

void func_8018745C(s32 s0) {
    typedef void (*FuncPtr)(void);
    FuncPtr fn;
    s16 v0;

    fn = (FuncPtr)D_801A9058[*(u16*)(s0 + 2)];
    fn();

    v0 = *(s16*)(s0 + 0xFE);
    if (v0 != 0) {
        func_80187F4C(s0);
    }
}


extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CA1C(s32 a0, s32 a1);
extern s32 func_8012E504(s32 a0, s32 a1);
extern u8 D_801A8F9C[];
extern u8 D_801A8F80[];
extern u8 D_801A8FD0[];

void func_801874BC(s32 param_1)
{
    s32 obj;

    func_8012C354(param_1, (s32)D_801A8F9C);
    obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }
    *(s32 *)(param_1 + 0x20) = obj;
    func_8001CA1C(obj, (s32)D_801A8F80);
    *(u16 *)(obj + 0x1A) = 0x2000;
    *(u16 *)(obj + 0x18) = 0x2000;
    *(u32 *)(obj + 4) |= 0x58000000;
    *(u16 *)(obj + 0x2C) |= 0x10;
    if (((s32 (*)(s32, s32))func_8012E504)(param_1, 0x19E) == 0) {
        *(s16 *)(param_1 + 0xFE) = 1;
        *(s32 *)(param_1 + 0xD0) = (s32)D_801A8FD0;
        *(s32 *)(param_1 + 0xCC) = (s32)D_801A8FD0;
        *(s32 *)(param_1 + 0xE0) = *(s32 *)D_801A8FD0;
    }
    *(s16 *)(param_1 + 0xAE) = -1;
    *(s16 *)(param_1 + 2) = 1;
}


extern void func_80187B44(s32 a0, s32 a1);

void func_80187598(s32 a0)
{
    u16 v1;

    if (*(s16 *)(a0 + 0x70) & 0x8000) {
        v1 = *(u16 *)(a0 + 0xFC);
        *(s16 *)(a0 + 2) = 3;
        *(u16 *)(a0 + 0xE6) = v1;
    } else {
        *(s16 *)(a0 + 2) = 2;
        func_80187B44(a0, 0);
    }
}


#include "common.h"

/* func_801875E4 (ov_SC03_090, 117 ins). Fresh mass-lane crack (no banked twin, card
 * gid 91f906ba70c2, lever "head-crack").
 *
 * Derived from the target .s (asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80/
 * func_801875E4.s) plus two proven sibling idioms already banked in *other* TUs:
 *   - func_80182D80 (src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c:6499-6591) documents
 *     `func_80049CAC(SVECTOR*, MATRIX*)` builds a rotation matrix from an angle triple;
 *     `func_800484EC(MATRIX*, Vec32*, Vec32*)` applies it -- and the exact
 *     `t1 = func_8012B70C(D_800D3918, &v1); result = t1*2 - func_8012B70C(&v2, D_800D3918)`
 *     angle-delta idiom (this target's version omits that sibling's trailing `& 0xFFF`
 *     -- confirmed absent from the .s, no andi emitted before the sh at 0x102).
 *   - func_80181D30 (this same TU, TU:4436-4468) shows the local MATRIX/SVECTOR typedef
 *     convention used because match_one's standalone -Iinclude-only compile cannot see
 *     engine_core.h's real MATRIX/SVECTOR/VECTOR (comment at ov_SC02_041_jr_8017BEBC.c
 *     TU:6501-6503 states this explicitly) -- local per-function typedefs required.
 *
 * DECLARATION SURFACE (audited against the destination TU
 * src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c):
 *   func_8004787C  TU:2200/4601/4778 `extern s32 func_8004787C(s32 a0);`      <- adopted verbatim
 *   func_80049CAC  TU:2639/4435/5895 `extern void func_80049CAC(s32 a0, s32 a1);` <- adopted verbatim
 *   func_800484EC  TU:240/6832       `extern void func_800484EC(s32 a0, s32 a1, s32 a2);` <- adopted verbatim
 *   func_8012B70C  TU:5200           `extern s32 func_8012B70C(s16 *a0, s16 *a1);` <- adopted verbatim
 *   func_8012CC40  (declared void everywhere in the project, e.g. src/ov_SC02_041/..:6591
 *                   `extern void func_8012CC40(s32 arg0, s32 arg1);` -- cast to
 *                   `(s32(*)(s32,s32))` at the call site since $v0 is used) <- adopted verbatim
 *   D_800D3918     TU:6930 `extern u8 D_800D3918[];`                          <- adopted verbatim
 *   D_801152B0     TU:401  `extern s16 D_801152B0;`                           <- adopted verbatim
 *   func_80187B44 / func_80187C64 / func_80187D70 / func_80187CBC -- all still
 *     INCLUDE_ASM stubs later in this same TU (no existing extern decl to adopt);
 *     typed by the target .s's own arg registers (raw s32/void, PsyQ-style entity ptr).
 *
 * SECOND PASS (S54 repair, 20 -> 0). The first pass's residual was filed as
 * "regalloc-schedule (sched2 call-arg-copy hoist)". It was NOT a scheduler residual at
 * all -- both blocks were SOURCE-ORDER defects, and §190-B ("compile the plain natural
 * order FIRST; sched1 produces interleaving FROM natural order, so an interleaved target
 * is not evidence of an interleaved source") named both of them:
 *
 *   (1) The vecOut->buf[] extraction was hand-"pre-scheduled" as buf[0], buf[2], buf[1]
 *       with two s16 temps hoisting the loads. That made all three extracted halfwords
 *       simultaneously live, so local_alloc needed a THIRD register ($a2) and sched1 had
 *       to pack the loads together. The target reuses $v0 (load 0x52 -> store 0x18 ->
 *       reload 0x56), which only happens when each load's store follows it directly in
 *       the insn stream. Writing the three assignments in plain index order 0,1,2 with no
 *       temps gives exactly two live values ($v0/$v1), and sched1 then produces the
 *       target's own interleave (lhu 0x52 / lhu 0x5A / a0 / sh 0x18 / lhu 0x56 / a1 /
 *       sh 0x1C / addiu 0x28 / jal / sh 0x1A) for free. The call-arg copies "hoisted to
 *       the block top" were a SYMPTOM of the register pressure, not the defect.
 *   (2) The angle-delta block wrote `tmpv.vz = ...` BETWEEN the two func_8012B70C calls.
 *       The target stores BOTH halfwords (0x10($sp) and 0x14($sp)) before the FIRST jal --
 *       the tell is that the target's second `lw`/`sra`/`sh` triple uses $v0, while a
 *       store placed after the call must use $v1 because $v0 is holding the first call's
 *       return value (§186c: where a value is loaded decides which allocator owns it).
 *       Hoisting the vz store above the first call fixed 12 of the 20 mismatches alone.
 *
 * Ordering was swept exhaustively over all six permutations of the three buf[] writes:
 * 0,1,2 -> MATCH; 2,1,0 -> 4; 2,0,1 -> 7; 0,2,1 -> 8; 1,0,2 and 1,2,0 -> 9.
 *
 * Symbol audit (wave law 1c -- match_one MASKS jal/HI16/LO16, so a clean MATCH proves
 * shape, not identity): all 15 relocations in the compiled object were walked against the
 * target .s's own relocation lines and agree in symbol, register and instruction index --
 * func_80187B44 / func_80187C64 / func_8004787C / func_80049CAC / func_800484EC /
 * func_8012CC40 / .text (the internal `j`) / D_800D3918 (%hi+%lo -> $s0) / D_801152B0
 * (%hi+%lo -> $a1) / func_8012B70C x2 / func_80187D70 / func_80187CBC.
 */

typedef struct { short vx, vy, vz, pad; } SV_801875E4;
typedef struct { short m[3][3]; long t[3]; } MTX_801875E4;
typedef struct { s32 vx, vy, vz; } V32_801875E4;

extern void func_80187B44(s32 a0, s32 a1);
extern void func_80187C64(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern u8 D_800D3918[];
extern s16 D_801152B0;
extern void func_8012CC40(s32 arg0, s32 arg1);
extern void func_80187D70(s32 a0);
extern void func_80187CBC(s32 a0);

void func_801875E4(s32 a0)
{
    SV_801875E4 tmpv;
    s16 buf[3];
    MTX_801875E4 mtx;
    V32_801875E4 vecIn;
    V32_801875E4 vecOut;
    MTX_801875E4 *mp;
    s32 ang;
    s32 flags;
    s32 cnt;
    s32 t1, t2;

    if ((*(s32 *)(a0 + 0x1C) & 0x1FF) == 0) {
        func_80187B44(a0, 1);
    }

    func_80187C64(a0, (s32)0xFFF60000);

    ang = func_8004787C(*(s32 *)(a0 + 0x1C) << 6);

    mp = &mtx;
    *(s16 *)(a0 + 0x52) = (s16)((u32)ang >> 8);
    func_80049CAC(a0 + 0x100, (s32)mp);

    vecIn.vy = 0;
    vecIn.vx = 0;
    vecIn.vz = (s32)0xFFD00000;
    func_800484EC((s32)mp, (s32)&vecIn, (s32)&vecOut);

    buf[0] = *(s16 *)((u8 *)&vecOut.vx + 2);
    buf[1] = *(s16 *)((u8 *)&vecOut.vy + 2) + 0x28;
    buf[2] = *(s16 *)((u8 *)&vecOut.vz + 2);

    flags = ((s32 (*)(s32, s32))func_8012CC40)(a0, (s32)buf);
    if (flags != 0) {
        if (flags & 0x2000) {
            *(u16 *)(a0 + 0x100) = 0x1000 - *(u16 *)(a0 + 0x100);
        } else if (flags & 0x8000) {
            s16 *p = (s16 *)D_800D3918;
            tmpv.vx = (s16)(*(s32 *)(a0 + 0x10) >> 8);
            tmpv.vz = (s16)(*(s32 *)(a0 + 0x18) >> 8);
            t1 = func_8012B70C(p, &D_801152B0);
            t2 = func_8012B70C((s16 *)&tmpv, p);
            *(s16 *)(a0 + 0x102) = t1 * 2 - t2;
        }
    }

    if ((s16)*(s16 *)(a0 + 0xA) < (s16)*(s16 *)(a0 + 0xFC)) {
        *(s16 *)(a0 + 0xA) = *(s16 *)(a0 + 0xFC);
        *(u16 *)(a0 + 0x100) = 0x1000 - *(u16 *)(a0 + 0x100);
    }

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) += 0x40;

    cnt = *(s32 *)(a0 + 0x1C);
    if (cnt == (cnt / 20) * 20) {
        func_80187D70(a0);
    }
    func_80187CBC(a0);

    *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) + 1;
}


#include "common.h"

/* func_801877B8 — ov_SC03_090 (ov_SC03_090_jr_8017CA80), 124 ins.
 *
 * A 3-case state machine on the u16 at +0x34 (§193-G: three case nodes already
 * give balance_case_nodes a TREE — beq 1 / slti 2 / beq 0 / beq 2 — which is
 * exactly the dispatch the target shows), followed by a SHARED tail that every
 * arm (including the implicit default) falls into.
 *
 * Struct offsets used (types from load/store widths):
 *   +0x04  s16[]  transform record handed to func_8012B77C ("from")
 *   +0x0A  u16    speed/scale fed into the sp10 record at +0x6
 *   +0x0E  s16    height/altitude, the state-transition discriminant
 *   +0x1C  s32    frame counter (also the `% 20` phase)
 *   +0x20  s32    -> render/sprite record; +0x14 is a u16 bumped by 0x20/frame
 *   +0x34  u16    state
 *   +0x100 s16    low half of the func_8012B77C result word
 *   +0x102 u16    accumulated angle
 *
 * Locals: sp10[4] (the 16-byte func_8012B77C "to" record, fields at +0x2/+0x6/+0xA)
 * and sp20[2] (the 8-byte out buffer) — §193-I: 16 + 8 = 0x18 of frame, plus the
 * 0x10 arg area and the 0xC of saves ($s0/$s1/$ra) => 0x38.  $s1 exists because the
 * 0x800 constant in case 2 is live across two calls.
 */

extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012CC40(s32 arg0, s32 arg1);
extern void func_80187C64(s32 a0, s32 a1);
extern void func_80187CBC(s32 a0);
extern void func_80187D70(s32 a0);

void func_801877B8(s32 a0) {

    extern u8 D_801A9018[];
    s32 sp10[4];   /* 0x10: func_8012B77C "to" record */
    s32 sp20[2];   /* 0x20: the 8-byte out buffer */
    s32 t;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        /* Written with the `>=` arm FIRST: the target's `slti -0x40` + `bnez` sends
         * the LESS-THAN case to the second test, so the state=1 store must be the
         * fall-through then-arm, not the else-arm (BRANCH-POLARITY). */
        if (*(s16 *)(a0 + 0xE) >= -0x40) {
            *(s16 *)(a0 + 0x34) = 1;
        } else if (*(s16 *)(a0 + 0xE) <= -0x2C0) {
            *(s16 *)(a0 + 0x34) = 2;
        }
        break;

    case 1:
        *(s16 *)((s32)sp10 + 0x2) = 0x800;
        *(s16 *)((s32)sp10 + 0x6) = *(u16 *)(a0 + 0xA);
        *(s16 *)((s32)sp10 + 0xA) = -0x40;
        func_8012B77C((s32)sp20, a0 + 4, (s32)sp10);
        t = sp20[0];
        *(s16 *)(a0 + 0x100) = t;
        *(u16 *)(a0 + 0x102) =
            *(u16 *)(a0 + 0x102) + func_8012B608(*(s16 *)(a0 + 0x102), t >> 16, 0x20);
        if (*(s16 *)(a0 + 0xE) <= -0x40) {
            *(s16 *)(a0 + 0x34) = 0;
            *(s16 *)(a0 + 0x102) = 0;
        }
        break;

    case 2:
        *(s16 *)((s32)sp10 + 0x2) = 0x800;
        *(s16 *)((s32)sp10 + 0x6) = *(u16 *)(a0 + 0xA);
        *(s16 *)((s32)sp10 + 0xA) = -0x2C0;
        func_8012B77C((s32)sp20, a0 + 4, (s32)sp10);
        t = sp20[0];
        *(s16 *)(a0 + 0x100) = t;
        *(u16 *)(a0 + 0x102) =
            *(u16 *)(a0 + 0x102) + func_8012B608(*(s16 *)(a0 + 0x102), t >> 16, 0x20);
        func_80187C64(a0, -0x50000);
        if (*(s16 *)(a0 + 0xE) >= -0x2C0) {
            *(s16 *)(a0 + 0x34) = 0;
            *(s16 *)(a0 + 0x102) = 0x800;
        }
        break;
    }

    func_80187C64(a0, -0x50000);
    func_8012CC40(a0, (s32)D_801A9018);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) + 0x20;
    if (*(s32 *)(a0 + 0x1C) % 20 == 0) {
        func_80187D70(a0);
    }
    func_80187CBC(a0);
    *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) + 1;
}


void func_801879A8(void) {
}

INCLUDE_ASM("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80", func_801879B0);

void func_801879D8(s32 *a0) {
        *(s16 *)((s32)a0 + 0x5C) = 0;
        *(s32 *)((s32)a0 + 0x1C) = 0;
    }


#include "common.h"

/* func_801879E4 (ov_SC03_090_jr_8017CA80) — mass-lane fresh crack.
 *
 * Structural twin of func_80181BEC (src/ov_SC03_093/ov_SC03_093_jr_8017D898.c, MATCH 59/59 ins)
 * and func_801860B8 (src/ov_SC02_027/ov_SC02_027_jr_8017D898.c): same D_80126CE0-gated speed-ramp
 * toward a target, same signed-div-by-4-with-rounding diff adjustment, same "load ptr, read/write
 * flags, abs, sh" tail. Differs from func_80181BEC in that spd here is 0x1800 (not the power-of-two
 * 0x2000), so the "(0x90-a)*spd/0x90" step compiles to a real register multiply (mult $v0,$a2)
 * instead of the shift form; spd is loaded once (unconditionally, ahead of the a==0 test) and reused
 * for the multiply, the D_801CBBDC store, and the v = cur - prev + spd sum, matching func_801860B8's
 * shape. The reset block re-materializes the literal 0x1800 in a fresh register rather than reusing
 * the spd register. Tail only stores *(s16*)(e2+0x18) = abs(v) (no +0x1A / +0x1C stores, unlike
 * func_801860B8's boosted variant).
 */

extern s16 D_80126CE0;
extern s32 D_801CBBD8;
extern s32 D_801CBBDC;

void func_801879E4(s32 arg0_)
{
    register s32 arg0 __asm__("$5");
    s32 prev;
    u16 flags;
    s32 a;
    s32 diff;
    s32 v;
    s32 spd;
    s32 e1;
    s32 e2;
    s32 cur;

    arg0 = arg0_;
    *(s16 *)(arg0 + 0x5C) = 0;
    a = D_80126CE0;
    if (a == 0) {
        D_801CBBD8 = 0x1800;
        D_801CBBDC = 0x1800;
    }
    spd = 0x1800;
    a = (spd * (0x90 - a)) / 0x90;

    diff = D_801CBBD8 - a;
    if (diff > 0) {
        D_801CBBD8 -= diff >> 2;
    } else if (diff < 0) {
        D_801CBBD8 += (-diff) / 4;
    }

    prev = D_801CBBDC;
    cur = D_801CBBD8;
    e1 = *(s32 *)(arg0 + 0x20);
    v = cur - prev + spd;
    D_801CBBDC = spd;
    flags = *(u16 *)(e1 + 0x2C);
    D_801CBBD8 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;

    e2 = *(s32 *)(arg0 + 0x20);
    v = __builtin_abs(v);
    *(s16 *)(e2 + 0x18) = v;
}


void func_80187AD4(s32 a0) {
    s32 v1;
    s16 t;

    v1 = *(s32 *)(a0 + 0x78);
    *(s16 *)(a0 + 2) = 1;
    t = *(u16 *)(v1 + 2);
    v1 = *(s32 *)(a0 + 0x20);
    *(s16 *)(a0 + 0x5C) = t;
    *(s16 *)(v1 + 0x18) = 0x1800;
}


extern void func_8012C098(void *param_1);
extern void func_8012E8A8(u8 *a0);

void func_80187AF8(s32 a0) {
    if (*(s16 *)(a0 + 0xFE) == 0) {
        func_8012C098((void *)a0);
        return;
    }
    *(u16 *)(a0 + 0x2) = 4;
    *(u8 *)(a0 + 0xC1) = 0;
    *(u16 *)(a0 + 0x5E) = 0;
    *(u16 *)(a0 + 0x5C) = 0;
    func_8012E8A8((u8 *)a0);
}


extern s32  func_8012B77C(s32 out, s32 from, s32 to);
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern void func_8012B0B4(unsigned int *param_1, int param_2, int param_3);

void func_80187B44(a0, a1)
s32 a0;
s32 a1;
{
    s16 sp10[8];   
    s32 sp20[2];   
    s32 t;
    s16 r;

    r = rand();
    func_8012B0B4((unsigned int *)sp20, r % 0x1000, (r % 0x100) + 0x200);

    t = sp20[0];
    if (a1 != 0) {
        sp10[1] = D_80126B5E + t;
        sp10[3] = *(u16 *)(a0 + 0xA);
        sp10[5] = D_80126B66 + (t >> 16);
    } else {
        sp10[1] = *(u16 *)(a0 + 0x88) + t;
        sp10[3] = *(u16 *)(a0 + 0xA);
        sp10[5] = *(u16 *)(a0 + 0x8C) + (t >> 16);
    }
    func_8012B77C((s32)sp20, a0 + 4, (s32)sp10);

    t = sp20[0];
    *(s16 *)(a0 + 0x100) = *(s16 *)(a0 + 0xE4) = t;
    *(s16 *)(a0 + 0x102) = *(s16 *)(a0 + 0xE6) = t >> 16;
}


typedef struct { short m[3][3]; long t[3]; } MTX_80187C64;
typedef struct { s32 vx, vy, vz; } V32_80187C64;

extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);

void func_80187C64(s32 a0, s32 a1)
{
    MTX_80187C64 mtx;
    V32_80187C64 vec;

    func_80049CAC(a0 + 0x100, (s32)&mtx);
    vec.vy = 0;
    vec.vx = 0;
    vec.vz = a1;
    func_800484EC((s32)&mtx, (s32)&vec, a0 + 0x10);
}


INCLUDE_ASM("asm/ov_SC03_090/nonmatchings/ov_SC03_090_jr_8017CA80", func_80187CBC);

#include "common.h"

/* Declarations adopted VERBATIM from src/ov_SC03_090/ov_SC03_090_jr_8017CA80.c
   (func_80049CAC TU:2639/4435/5895/6831, func_800484EC TU:240/6832, rand TU:952/6833). */
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);

/* Not declared anywhere in the TU or in include/ (func_80187FD8 is INCLUDE_ASM'd
   later in the same file, TU:7115).  Raw-word/void* form per wave law 4. */
extern void *func_80187FD8();
extern s32 D_801A907C[];

/* Spawns three scatter particles around a0's position.  Two rotation transforms
   (func_80049CAC builds the matrix from an SVECTOR, func_800484EC applies it to a
   vector) with rand()%512 yaw jitter and a rand()%20 radial step.
   Frame: 0x10 pos[3], 0x20 mat, 0x40 buf1, 0x50 trailing, 0x60 buf2, 0x70 svec. */
/* §183 SIGNATURE reconcile: the two sibling drafts landing in this same TU
   (func_801875E4, func_801877B8) both call this as `extern void func_80187D70(s32 a0);`.
   Adopting the s32 spelling on the DEFINITION is byte-neutral here because every use of
   a0 in the body already goes through an explicit `(s32)a0` cast. */
void func_80187D70(s32 a0) {
    s16 pos[8];
    s32 mat[8];
    s32 buf1[4];
    s32 trailing[4];
    s32 buf2[4];
    s16 svec[4];
    s32 i;
    void *ent;

    trailing[1] = 0;
    trailing[0] = 0;

    svec[0] = *(u16 *)((s32)a0 + 0x100) + 0x800;
    svec[1] = *(u16 *)((s32)a0 + 0x102);
    svec[2] = *(u16 *)((s32)a0 + 0x104);

    func_80049CAC((s32)svec, (s32)&mat);
    func_800484EC((s32)&mat, (s32)D_801A907C, (s32)buf1);

    for (i = 0; i < 3; i++) {
        s32 r1;
        s32 r2;
        s32 rv;
        s32 s0;
        s32 s1;

        r1 = rand();
        s0 = r1 % 512;
        s1 = *(s16 *)((s32)a0 + 0x102);
        r2 = rand();

        {
            /* The jitter goes through a temp `t` and the &svec arg through the
               named local `pv` ON PURPOSE (this is the whole residual).  reorg.c
               fill_simple_delay_slots picks the NEAREST eligible insn above the
               `jal` for its delay slot, so the target's `sh $v0,0x72($sp)` in that
               slot proves the arg setup was emitted BEFORE the store.  RTL emission
               order is source order here (verified: -fno-schedule-insns2 changes
               nothing), so `pv`'s def site — which local_alloc coalesces straight
               into $a0 — has to sit after the branch join and before the store.
               Writing `svec[1] = cond ? .. : ..;` inline puts the store first and
               costs the 3-instruction SCHEDULE-REORDER residual. */
            s32 t = (r2 & 1) ? (s1 + s0) : (s1 - s0);
            s32 pv = (s32)svec;
            svec[1] = t;
            func_80049CAC(pv, (s32)&mat);
        }

        rv = rand();
        trailing[2] = 0xFFE80000 - ((rv % 20) << 16);

        func_800484EC((s32)&mat, (s32)trailing, (s32)buf2);

        pos[0] = (*(s32 *)((s32)a0 + 0x4) + buf2[0]) >> 16;
        pos[1] = (*(s32 *)((s32)a0 + 0x8) + buf2[1]) >> 16;
        pos[2] = (*(s32 *)((s32)a0 + 0xC) + buf2[2]) >> 16;

        ent = func_80187FD8(pos);
        if (ent != 0) {
            *(s32 *)((s32)ent + 0x10) = buf1[0];
            *(s32 *)((s32)ent + 0x14) = buf1[1];
            *(s32 *)((s32)ent + 0x18) = buf1[2];
            *(u16 *)(*(s32 *)((s32)ent + 0x20) + 0x14) =
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14);
            *(s32 *)((s32)ent + 0x1C) = i << 3;
        }
    }
}


void func_80187F4C(s32 a0)
{
    register s32 v0 __asm__("$2");
    s32 v1;
    s32 a1;

    v0 = *(s32 *)(a0 + 0xE0);
    if (v0 == 0) {
        v0 = 1;
        goto END;
    }
    v0 = v0 - 1;
    *(s32 *)(a0 + 0xE0) = v0;
    if (v0 > 0) {
        goto SET0;
    }

    v1 = *(s32 *)(a0 + 0xD0);
    v1 = v1 + 8;
    a1 = *(s32 *)v1;
    if ((a1 & 0x40000000) != 0) {
        v1 = *(s32 *)(a0 + 0xCC);
    } else if (a1 < 0) {
        v0 = 1;
        *(s32 *)(a0 + 0xE0) = 0;
        goto END;
    }

    v0 = *(s32 *)v1;
    *(s32 *)(a0 + 0xD0) = v1;
    *(s32 *)(a0 + 0xE0) = v0;
    func_800183E0(*(s32 *)(v1 + 4));

SET0:
    v0 = 0;
END:
    __asm__ volatile("" : : "r"(v0));
}


extern u8 *func_801290DC(s32 a0, u8 *a1);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void * func_80187FD8(s32 a0)
{

    extern u8 D_801A908C[];
    extern s32 D_801A9098[];
    u8 *obj;
    s32 sub;
    s32 arg;

    obj = func_801290DC(0x43, (u8 *)a0);
    if (obj == 0) {
        return 0;
    }
    arg = (s32)obj + 0x24;
    sub = *(s32 *)(obj + 0x20);
    *(s32 *)(sub + 0x20) = (s32)D_801A908C;
    *(u8 *)(sub + 0x27) = 0x66;
    *(u16 *)(sub + 0x1A) = 0x2000;
    *(u16 *)(sub + 0x18) = 0x2000;
    *(s32 *)(sub + 4) |= 0xD8000000;
    func_80128EA8(sub, arg, (s32)D_801A9098);
    return (s32)obj;
}


void func_8018805C(s32 a0) {
    register u16 state __asm__("$3");
    register u16 nv __asm__("$2");

    state = *(u16 *)(a0 + 2);
    if (state == 0) {
        s32 val = *(s32 *)(a0 + 0x1C);
        if (val == 0) {
            nv = state + 1;
            *(u16 *)(a0 + 2) = nv;
            *(s32 *)(*(s32 *)(a0 + 0x20) + 4) &= 0x7FFFFFFF;
        } else {
            *(s32 *)(a0 + 0x1C) = val - 1;
        }
    } else {
        func_8012931C((struct vec *)a0);
        if (func_80128ED8(*(s32 *)(a0 + 0x20), (s32 *)(a0 + 0x24)) != 0) {
            func_801292C8((u8 *)a0);
        }
    }
}



/* func_801880F0 — "spawn a paired effect entity above/below the actor" template
 * (family exemplar, 15 members / 1455 templatable instructions).
 *
 * Declaration provenance (all verified against the whole TU in one pass, cookbook §135-8):
 *   func_8012A828(s32,s32)          — TU col-0 decl (lines 3488/3771/…/4781), identical form
 *   func_8012C658(s32,s32,s32)      — TU col-0 decl (lines 2524/3721/3772/4935)
 *   func_8012C218(void *)           — TU col-0 decl (lines 3545/4016/…/5226)
 *   func_8012B030(u8 *)             — TU col-0 decl (line 4208)
 *   func_8012CEB0(s32,s32,s32)      — TU fn-scope decl (line 4404), same signature
 *   func_8002AC00(s32)              — TU fn-scope decl (line 5085), same signature
 *   func_8001C214(s32,s32)          — NOT declared in this TU; form copied from
 *                                     src/shared/engine_core.h:8751 so it can never clash
 *   D_801B1E78 / D_801B95BC         — real dlabels in asm/ov_SC02_026/data/tail.data.s
 *                                     (0x801B5A4C / 0x801BD190), declared nowhere else
 *
 * Codegen notes (each closed a residual):
 *  - The buf[8] halfword-pair setup is the byte-verified twin of func_801843AC in THIS TU
 *    (line 4403): the three $2/$3/$7 register pins reproduce the original's temp allocation,
 *    and the doubled buf[1]/buf[5] stores are real — the ±8 adjust is a second store, so the
 *    scheduler emits sh/sh then sh/sh with a single lhu of a0+0xA (cookbook §135-4: the list
 *    scheduler preserves the relative order of disambiguable stores).
 *    Third temp lands in $a3 (not $a2 as in func_801843AC) because $a2 is already pinned to
 *    the literal-0 third argument here.
 *  - `>= 0x10` (not `< 0x10` with swapped arms) is what puts the func_8012C218 arm in the
 *    fall-through position and the func_8012B030 arm behind the `j`.
 *  - The `s16 t` temp on line ~72 is load-BEFORE-stores in SOURCE. Without it the lhu of
 *    a0+0x100 cannot hoist above the two ent-relative stores — §135-2's MEM_IN_STRUCT_P
 *    escape does NOT apply here because those stores have varying (register) addresses, so
 *    true_dependence() keeps the edge. Source order is the only lever; costs one nop otherwise.
 *  - The do/while's `sll/sra` pair is CSE store-forwarding: `*(u16*)` read for the += keeps
 *    the HImode load (result is truncated), then the signed compare must materialize the
 *    sign extension of the just-stored register.
 */

extern void func_8002AC00(s32 arg0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012C218(void *a0);
extern s32 func_8012B030(u8 *a0);

void func_801880F0(void *a0) {

    extern s32 D_801B1E78;
    extern s32 D_801B95BC;
    u16 buf[8];
    s32 ent;
    u16 saved;
    register u16 v0 __asm__("$2");
    register u16 v1 __asm__("$3");
    register u16 a3 __asm__("$7");

    func_8002AC00(0xD);
    if (*(u16 *)((s32)a0 + 0x0) != 0) {
        v0 = *(u16 *)((s32)a0 + 0x6);
        buf[0] = v0;
        buf[4] = v0;

        v1 = *(u16 *)((s32)a0 + 0xA);
        v0 = v1 - 8;
        buf[1] = v1;
        buf[5] = v1;

        a3 = *(u16 *)((s32)a0 + 0xE);
        v1 = v1 + 8;
        buf[1] = v0;
        buf[5] = v1;
        buf[2] = a3;
        buf[6] = a3;

        if ((func_8012CEB0((s32)&buf[0], (s32)&buf[4], 0) & 0x1F) == 0) {
            if ((*(s16 *)((s32)a0 + 0x100) & 0x8000) == 0) {
                saved = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12);
                func_8001C214(*(s32 *)((s32)a0 + 0x20), (s32)&D_801B1E78);
                func_8012A828((s32)a0, (s32)&D_801B95BC);
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = saved;
                ent = func_8012C658(0x12C, 1, (s32)a0);
                if (ent != 0) {
                    if (*(s16 *)((s32)a0 + 0xA) >= 0x10) {
                        func_8012C218((void *)ent);
                    } else {
                        *(u16 *)(*(s32 *)(ent + 0x20) + 0x12) = saved;
                        func_8012B030((u8 *)ent);
                        if (*(s16 *)((s32)a0 + 0x70) == 5) {
                            s16 t = *(s16 *)((s32)a0 + 0x100);
                            *(s16 *)(ent + 0x70) = 6;
                            *(s16 *)(ent + 0xFE) = 1;
                            *(s16 *)(ent + 0x100) = t;
                            do {
                                func_8012C658(0x12F, 5, ent);
                                *(s16 *)(ent + 0xFE) = *(u16 *)(ent + 0xFE) + 3;
                            } while (*(s16 *)(ent + 0xFE) < 0x10);
                            *(s16 *)(ent + 0xFE) = 0;
                        }
                    }
                }
            }
        }
    }
}
