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
extern u8 D_80192964;
extern u8 D_801928D4;
extern u8 D_801928B0;
extern u8 D_8019288C;
extern u8 D_80192940;
extern u8 D_8019291C;
extern u8 D_801928F8;
extern u8 D_80192868;
extern void func_80145934(void);
extern u8 D_801929F4;
extern u8 D_801929D0;
extern u8 D_801929AC;
extern u8 D_80192988;
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
extern unsigned char D_80191DEC[];
extern unsigned char D_80191E1C[];
extern unsigned char D_80191E6C[];
extern unsigned char D_80191E9C[];
extern unsigned char D_80191ECC[];
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
extern void (*D_80191F1C[])(void *);
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
extern s32 D_80191FE4[];
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
extern u8 D_8019206C[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80192074;
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
extern int D_801EDB58;
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
extern s32 D_801EDB5C;
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
extern s32 D_801920A4;
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
extern void (*D_8019214C[])(void);
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
extern void (*D_80192170[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80192160;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80192184[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80192190[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801921A0[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801921B8[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801921A8;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801921CC[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801921E8[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801921D8;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801921FC[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80192210[])(void);
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
extern s32 D_80192224;
extern void (*D_8019224C[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_8019222C;
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
extern int (*D_80192298[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_8019229C[])(void);
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
extern unsigned short D_80192700[];
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
extern void (*D_80192710[])(void);
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
extern int D_801EDB90;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80192738[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80192718;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80192728;
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
extern void (*D_80192778[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80192780[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_8019274C;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_8019278C[])(void);
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
extern u8 D_8019275C;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801EDB98;
extern s32 D_801EDBA4;
extern s32 D_801EDBA8;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_801927C8[])(s32 *);
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
extern s32 D_8019279C[];
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
extern s32 D_801EDBA0;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80192A18[])(void);
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
extern char D_80192838[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80192ABC[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80192C10[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80192A2C;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80192C18[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80192A3C;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80192A5C;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80192C20[])(void);
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
extern void (*D_80192C48[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80192C54[])(void);
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
extern void (*D_80192AC8[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80192CF8;
extern void func_8015D380(s32 a0);
extern unsigned char D_80191DDC[];
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
extern unsigned char D_80192D0C[];
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
extern s8 D_80192D48[];
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
extern u16 D_80192D90;
extern u16 D_80192D92;
extern u16 D_80192D94;
extern s32 D_80192D98;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80192DA0;
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
extern int D_80192AAC;
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
extern unsigned int D_80192E24[];
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
extern void (*D_80192ED4[])(void);
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
extern u16 D_80192F04[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80192F68;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801EDBB0[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80192F8C[])(void);
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
extern int D_801EDC08[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80192FD4[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80192FC4;
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
extern char D_801ED2A8[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_80192FDC[])(void);
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
extern void (*D_80193030[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80192FF8;
extern s16 D_8019302C;
extern s16 D_8019302A;
extern s16 D_80193028;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_8019303C[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801EDC68;
extern u8 D_801EDC69;
extern u8 D_801EDC6A;
extern u8 D_801EDC6B;
extern u8 D_801EDC6C;
extern u8 D_801EDC6D;
extern u8 D_801EDC6E;
extern u8 D_801EDC6F;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_8019304C[])(void);
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
extern s32 D_801EDCA8;
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
extern void (*D_80193090[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_8019310C[];
extern s32 D_8019312C[];
extern u8 D_801931A8[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801931C8[];
extern u8 D_801931E8[];
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
extern void (*D_80193284[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80193300[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801ED2B8;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_8019330C[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_80193314[])(void);
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
extern void (*D_801933DC[])(void);
extern void func_80166618(void *a0);
extern void (*D_801933EC[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801933FC[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80193408[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80193368[];
extern u8   D_8019337C[];
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
extern void (*D_80193420[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80193428[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80193430[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80193438[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80193440[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80193448[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80193450[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80193504[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_8019350C[])(void);
extern void func_80169F00(void *a0);
extern char D_801934BC[];
extern char D_8019347C[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80193544[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80193550[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80193598[])(void);
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
extern void (*D_80193614[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801EDFC8;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80193608[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_8019364C[];
extern unsigned short D_80193654[];
extern unsigned short D_8019365C[];
extern unsigned char D_801EDFD0[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801EDFC8;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80193664[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801EE104;
extern M2C_UNK D_801EE108;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801EE090;
extern void (*D_80193694[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801EE10C[];
extern u8 D_801EE114[];
extern u8 D_801EE0C4[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_8019369C[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_801936B8[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_801936C0[])(void);
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
extern void (*D_80193728[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801936CC;
extern u8 D_801936D8;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_8019375C[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80193764[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_801937B8[])(void);
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
extern u16 D_801937EC[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_801937DC[];
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
extern s32 D_80193808;
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
extern void (*D_80193880[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80193888[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80193890[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80193898[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_801938A0[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_801938A8[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_801938B4[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_801938C0[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_801938CC[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_801938DC[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_801938EC[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_801938F4[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_801938FC[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80193904[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_8019390C[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80193914[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_8019391C[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80193924[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_8019392C[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80193934[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_8019393C[])(void);
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
extern void (*D_80193944[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_8019394C[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80193954[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_8019395C[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80193964[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_8019396C[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80193974[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_8019397C[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80193984[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_8019398C[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80193994[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_8019399C[])(void);
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
extern void (*D_801939E0[])(void);
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
extern M2C_UNK D_801939A4;
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
extern void (*D_80193A10[])(void);
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
extern void (*D_80193A4C[])(void);
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
extern void (*D_80193AA4[])();
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
extern void (*D_80193AB4[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80193ABC[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80193C24[])();
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
extern void (*D_80193C30[])();
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
extern M2C_UNK D_801ED500;
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
extern s16 D_801F1638;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801EE848;
extern short D_801F16AC;
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
extern s32 D_801EEC74;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801EEC9C;
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
extern s16 D_801EEC58;
extern s32 func_8017A3B0(void);
extern short D_801EEC94;
extern short D_801EEC90;
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
extern s16 D_801EEC5C;
extern u16 D_801EECDC;
extern u16 D_801EECDE;
extern u16 D_801EECE0;
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
extern s16 D_801EECD4;
extern s16 D_801EECD6;
extern s16 D_801EECD8;
extern s16 D_801EECCC;
extern s16 D_801EECCE;
extern s16 D_801EECD0;
extern void func_8017B7A8(void);
extern s16 D_801EECEC;
extern s16 D_801EECEE;
extern s16 D_801EECF0;
extern s16 D_801EECF4;
extern s16 D_801EECF6;
extern s16 D_801EECF8;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801EECE4;
extern short D_801EECE6;
extern short D_801EECE8;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801EEC7C;
extern SV4 D_801EEC84;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801EECA4[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801EECA0)(void);
extern void func_8017BD50(int param_1);
extern void (*D_80193E0C[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_80193E44[])(void);
extern void func_8017BEF8(void *a0);
extern void (*D_80193E58[])(void);
extern void func_8017C524(void *a0);
extern void (*D_80193E6C[])(void);
extern void func_8017C7C4(void *a0);
extern void func_8017CAF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_8017CAA4(s32 arg0, s32 arg1, s16 arg2);
extern void func_8017CACC(void *a0, void *a1, s32 a2, s32 a3);
extern void (*D_80193EC8[])(void);
extern void func_8017CCD8(void *a0);
/* ==== end §8b carried decl layer ==== */

/* func_8017D494 — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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
















void func_8017D494(s32 arg0)
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
        __asm__ volatile ("");   /* §45-B live-length slider: +1 static insn splits the 228/230 allocno-priority tie (498/498 -> 497/498) */  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t3_tus1)
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
                                    gte_stsxy3_f3(pkt);
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



extern void (*D_80193ED0[])(void);

void func_8017E374(void *a0) {
    D_80193ED0[*(u16 *)((s32)a0 + 0x2)]();
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
} SubRec_801EB5C8_8017E3B0; /* 0x1C */

typedef struct {
    u16 g0;
    u16 g2;
    s32 g4;
    s32 g8;
    s32 gC;
    SubRec_801EB5C8_8017E3B0 subs[16];
} GroupRec_801EB5C8_8017E3B0; /* 0x1D0 */


void func_8017E3B0(s32 param_1)
{

    extern GroupRec_801EB5C8_8017E3B0 D_801EEDC8[8];
    s32 i, j;
    GroupRec_801EB5C8_8017E3B0 *grp;
    SubRec_801EB5C8_8017E3B0 *sub;

    for (i = 0; i < 8; i++) {
        grp = &D_801EEDC8[i];
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


/* func_8017E558 — particle-group tick for the D_801EEDC8 (0x1D0 stride) table.
 * Shape lifted from the banked twin ov_SC03_028:func_8017F278 (§193-A); every symbol and
 * literal re-read from THIS target's own .s (law 1/2): D_801EEDC8 (not D_801EB5C8) and
 * func_8017E6EC (not func_8017F40C).
 *
 * Levers:
 *  - the %hi/%lo of D_801EEDC8 is RE-MATERIALISED inside the outer loop and lands in $v0, with
 *    the group base in $a1: the `register ... __asm__("$2")` / `__asm__("$5")` pin pair (§17a-1,
 *    the twin's own note) is what forces that allocation instead of a hoisted loop-invariant.
 *  - byte-typed base so the block-scope `extern u8 D_801EEDC8[]` costs no typedef here: the TU's
 *    own decl (GroupRec_801EB5C8_8017E3B0, block-scope in func_8017E3B0) stays untouched and this
 *    file still compiles standalone under match_one, which the previous attempt did not.
 *  - func_8017E6EC is defined LATER in this TU with (s32,s32); the no-prototype forward decl is
 *    required so the 1-argument call site here does not become a 2-argument call (§263).
 */
extern void func_8017E6EC();
extern void func_80146C3C();

void func_8017E558(void *arg0) {
    extern u8 D_801EEDC8[];
    s32 cnt2;
    s32 i;
    s32 j;
    register s32 base __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 p;
    s32 vel;
    s32 pos;
    u16 life;
    s32 f18;

    cnt2 = 0;
    for (i = 0; i < 8; i++) {
        {
            register s32 sym __asm__("$2") = (s32)((u8 *)D_801EEDC8);  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
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
        func_8017E6EC(arg0);
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




void func_8017E6EC(s32 a0, s32 a1) {

    extern SVECTOR_8017F40C_8017E6EC D_80193ED8[4];
    Prim_8017F40C_8017E6EC prim;
    u8 matBuf[0x20];
    SVECTOR_8017F40C_8017E6EC vecB;
    SVECTOR_8017F40C_8017E6EC angBuf;
    SVECTOR_8017F40C_8017E6EC sinOut;
    SVECTOR_8017F40C_8017E6EC sv1, sv2, sv3, sv4;
    u32 mask;
    s32 rowPtr;
    SVECTOR_8017F40C_8017E6EC *ap;
    void *mp;
    SVECTOR_8017F40C_8017E6EC *dv;

    func_80015978(a0 + 4, (s32 *)&vecB);
    angBuf.vx = 0;
    angBuf.vy = 0;
    angBuf.vz = *(u16 *)(a1 + 0xe);
    func_800139C8((s32) *(s16 *)(a1 + 2), &angBuf, &angBuf);
    mask = ((u32(*)(void *, void *))func_8012EFB8)(&vecB, &vecB);
    if ((mask & 0xffffefff) == 0) {
        Prim_8017F40C_8017E6EC *pp = &prim;
        s32 off;
        s32 cnt;
        cnt = 0;
        ap = &angBuf;
        mp = matBuf;
        dv = D_80193ED8;
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



extern void func_80019064(void *a0);

void func_8017E9A4(void *a0) {

    extern u8 D_80193EF8;
    extern void (*D_80193F1C[])(void *);
    func_80019064(&D_80193EF8);
    D_80193F1C[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_8014E934(s32 a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_8017EA44(s32 a0);
extern void func_80146CA0(void *a0);
void func_8017E9FC(s32 a0) {
    func_8014E934(a0);
    func_8014CC28(a0);
    func_8014F3E8(a0);
    func_8017EA44(a0);
    func_80146CA0((void *)a0);
}


extern void func_80149020(s32 *a0);
extern void func_80147324(s32 a0);
extern int func_801511E0(int a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_8014CBF8(void *a0);
extern void func_801474EC(s32 *a0);
extern void func_80146DE8(s32 *a0, s32 a1, s32 a2, s32 a3);
extern void func_801477E8(s32 *a0, s32 a1);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern void func_80146CA0(void *a0);
extern s32 D_80193F00;

void func_8017EA44(s32 a0)
{
    s32 s0 = a0;
    s32 a2, a3;
    s32 temp;

    func_80149020((s32 *)s0);
    func_80147324(0x451);
    func_801511E0(s0);
    func_80154274((s32 *)s0, (s32)&D_80193F00);
    func_8014CBF8((void *)s0);
    func_801474EC((s32 *)s0);

    a2 = 0;
    a3 = 0;
    temp = (*(u16 *)(s0 + 0xF4) + 0x800) & 0xFFF;
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) = temp;
    *(u16 *)(s0 + 0x244) = temp;
    func_80146DE8((s32 *)s0, a2, a3, 0x100000);

    func_801477E8((s32 *)s0, 0xFFF40000);

    *(u8 *)(s0 + 0xDF) = 0;
    *(u8 *)(s0 + 0xDE) = 0x5A;
    func_80147324(0x7EB);

    ((void (*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x3F, (void *)s0, a2, a3, 0, 0, 0);
    func_80146CA0((void *)s0);
}


void func_8017EB10(s32 *a0)
{
    s32 ret;
    u8 temp;
    func_80149020(a0);
    if (*(u8 *)((char *)a0 + 0xDF) == 0) {
        func_80147A84((s32)a0);
        func_801473EC(a0);
        func_80148038((s32)a0, 0x18000);
        func_80147460((s32)a0);
    }
    ret = func_801535F4(a0);
    if (ret != 0)
        if (ret >= 0)
            if (ret < 3) {
                if (*(s32 *)((char *)a0 + 0x34) > 0) {
                    if (*(u8 *)((char *)a0 + 0xDF) == 0) {
                        *(u8 *)((char *)a0 + 0xDF) = 1;
                        func_80146D90((s32)a0);
                    }
                }
            }
    temp = *(u8 *)((char *)a0 + 0xDE);
    *(u8 *)((char *)a0 + 0xDE) = temp + 0xFF;
    if (temp == 0) {
        func_8017EBE8((s32)a0);
        func_80159B3C(a0);
        func_80165718((s32)a0);
    }
}


extern u8 D_80062C04[];
extern void func_80019064(void *a0);
extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80151664(void);

void func_8017EBE8(s32 a0)
{
    s32 s0 = a0;
    ((void (*)(s32))func_80019064)((s32)&(*(s32 *)D_80062C04));
    func_8014BC44(s0, *(s16 *)(s0 + 0xF2));
    *(u8 *)(s0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(s0);
}



extern void func_80019064(void *a0);

void func_8017EC38(void *a0) {

    extern u8 D_80193F28;
    extern void (*D_80193F4C[])(void *);
    func_80019064(&D_80193F28);
    D_80193F4C[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_8014E934(s32 a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_8017ECD8();
extern void func_80146CA0(void *a0);
void func_8017EC90(s32 a0) {
    func_8014E934(a0);
    func_8014CC28(a0);
    func_8014F3E8(a0);
    func_8017ECD8(a0);
    func_80146CA0((void *)a0);
}


#include "common.h"

extern void func_80149020(s32 *a0);
extern void func_80147324(s32 a0);
extern int func_801511E0(int a0);
extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_80146A6C(s32, void*, s32, s32, s32, s32, s32);
extern s32 func_80172630(u8 *a0);
extern void func_80146CA0(void *a0);
extern s32 D_80193F30;

void func_8017ECD8(s32 a0)
{
    s32 s0 = a0;
    s32 a2, a3;

    func_80149020((s32 *)s0);
    func_80147324(0x451);
    func_801511E0(s0);
    func_80154274((s32 *)s0, (s32)&D_80193F30);
    *(u8 *)(s0 + 0xDE) = 0x5A;
    func_80147324(0x7EB);

    a2 = 0;
    a3 = 0;
    ((void (*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x3F, (void *)s0, a2, a3, 0, 0, 0);
    func_80172630((u8 *)s0);
    func_80146CA0((void *)s0);
}


extern void func_80149020(s32 *a0);
extern void func_8017EDC4(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern s32 func_80172630(u8 *a0);

void func_8017ED60(s32 *a0)
{
    u8 temp;
    func_80149020(a0);
    temp = *(u8 *)((char *)a0 + 0xDE);
    *(u8 *)((char *)a0 + 0xDE) = temp + 0xFF;
    if (temp == 0) {
        func_8017EDC4((s32)a0);
        func_80159B3C(a0);
        func_80165718((s32)a0);
    } else {
        func_80172630((u8 *)a0);
    }
}


extern u8 D_80062C04[];
extern void func_80019064(void *a0);
extern void func_8014BC44(s32 a0, s32 a1);
extern void func_80151664(void);

void func_8017EDC4(s32 a0)
{
    s32 s0 = a0;
    ((void (*)(s32))func_80019064)((s32)&(*(s32 *)D_80062C04));
    func_8014BC44(s0, *(s16 *)(s0 + 0xF2));
    *(u8 *)(s0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(s0);
}



extern void (*D_80193F84[])(void);

void func_8017EE14(void *a0) {
    D_80193F84[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_800D21C4(s32 a0, void *a1, s32 a2);
extern void func_8017F2A8(s32 *a0);
extern void func_8017F2C4(s32 *a0);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146C3C();
extern s32 D_80193F58;

void func_8017EE50(s32 a0) {
    s32 a1;
    s32 pad[12];

    a1 = func_800D21C4(a0, (s32)&D_80193F58, 0x2B);
    *(s32 *)(a0 + 0x20) = a1;

    if (a1 != 0) {
        *(s16 *)(a1 + 0x28) = 0x224;
        *(s16 *)(a1 + 0x2A) = 0x1A8;
        *(s16 *)(a1 + 0x1A) = 0x3000;
        *(s16 *)(a1 + 0x18) = 0x3000;
        *(s16 *)(a1 + 0x14) = -0x400;

        *(s32 *)(a1 + 0x04) |= 0x48000000;
        *(u16 *)(a1 + 0x2C) = 0xC080;

        func_8017F2A8((s32 *)a0);
        func_8017F2C4((s32 *)a0);

        *(s32 *)(a0 + 0x2C) = 0;
        *(s32 *)(a0 + 0x30) = 0;

        func_80146E90((s32 *)a0, 0x5A);

        *(u16 *)(a0 + 0x02) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)(a0);
    }
}



extern void func_8017F2C4(s32 *a0);
extern void func_800183E0(s32 a0);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_8017F8D0(s32 *a0);
extern void func_80147324(s32 arg0);
extern s32 func_80146E98(s32 a0);
extern s32 func_8017F8E0(void *a0);
extern void func_8014ABF0(void);
extern void func_80146C3C();


void func_8017EF0C(s32 param_1) {

    extern void *D_80193F94[];
    extern s32 D_80193F7C[2];
    s32 iVar1;
    s32 iVar3;
    void *puVar2;

    iVar3 = *(s32 *)(param_1 + 0x20);
    func_8017F2C4((s32 *)param_1);
    if (*(s32 *)(param_1 + 0x30) == 0) {
        puVar2 = D_80193F94[*(s32 *)(param_1 + 0x2c)];
        if (D_80193F94[*(s32 *)(param_1 + 0x2c)] == 0) {
            *(s32 *)(param_1 + 0x30) = 0x20;
            *(s32 *)(param_1 + 0x2c) = 0;
            puVar2 = D_80193F94[0];
        }
        func_800183E0((s32)puVar2);
        *(s32 *)(param_1 + 0x2c) = *(s32 *)(param_1 + 0x2c) + 1;
    } else {
        s32 iVar0 = *(s32 *)(param_1 + 0x30) - 1;
        *(s32 *)(param_1 + 0x30) = iVar0;
        if ((iVar0 == 0) && (*(s32 *)(param_1 + 0x1c) != 0)) {
            func_80147324(0x7EC);
        }
    }
    if (*(s32 *)(param_1 + 0x1c) == 1) {
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 0, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 1, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 2, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 3, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 4, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 5, 0);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 0, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 1, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 2, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 3, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 4, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 5, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 0, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 1, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 2, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 3, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 4, 1);
        func_80146A6C(0x40, (void *)param_1, 0, 0, 0, 5, 1);
        func_8017F8D0(D_80193F7C);
        func_80147324(0x7F4);
        *(u32 *)(iVar3 + 4) = *(u32 *)(iVar3 + 4) | 0x80000000;
    }
    iVar1 = func_80146E98(param_1);
    if ((iVar1 != 0) && (iVar1 = func_8017F8E0((void *)D_80193F7C), iVar1 != 0)) {
        ((void (*)(s32))func_8014ABF0)(0x40);
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


void func_8017F2A8(s32 *a0) {
        *(s32 *)((s32)a0 + 0x10) = *(s32 *)((s32)a0 + 0x4);
        *(s32 *)((s32)a0 + 0x14) = *(s32 *)((s32)a0 + 0x8);
        *(s32 *)((s32)a0 + 0x18) = *(s32 *)((s32)a0 + 0xC);
    }


#include "common.h"

extern void func_80149374(s32 a0, s32 a1);

void func_8017F2C4(s32 *a0)
{
    s32 arg;

    a0[1] = a0[4];
    arg = a0[13];
    a0[2] = a0[5];
    a0[3] = a0[6];

    func_80149374(arg, (s32)(a0 + 1));
}


extern void (*D_80193FBC[])(void);

void func_8017F304(void *a0) {
    D_80193FBC[*(u16 *)((s32)a0 + 0x2)]();
}



/* Host TU (src/ov_SC02_041/ov_SC02_041_jr_8017BEBC.c) already has these three via
 * ../shared/engine_core.h -> engine_types.h as SVECTOR (:997), MATRIX (:1168) and
 * Vec32 (:1098) -- byte-identical layouts. Renamed here only because match_one
 * compiles standalone with -Iinclude (engine_core.h is not on that path); on bank,
 * drop these three typedefs and use the TU's own names. */
typedef struct { s16 vx, vy, vz, pad; } SV_8017D7C0_8017F340;   /*  8 bytes, align 2 */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8017D7C0_8017F340; /* 0x20 bytes, align 4 */
typedef struct { s32 vx, vy, vz, pad; } V32_8017D7C0_8017F340;  /* 16 bytes, align 4 */

/* ov_SC02_041 func_8017F340 -- 181 ins, zero-crack family exemplar (reach x4:
 * ov_SC04_002:8017f19c, ov_SC04_004:8017f65c, ov_SC04_011:8017f340).
 *
 * Spawn-a-particle-burst routine:
 *   obj = actor->0x34; p = alloc(); actor->0x20 = p;
 *   if (p) { init p, force its "hidden" bit, copy the actor position into it,
 *            scale it from a table, jitter a rotation SVECTOR + a velocity
 *            Vec32 with rand(), RotMatrix + ApplyMatrix into the actor's
 *            velocity, then 9 more rand() shorts at actor+0x38 }
 *   else   { func_80146C3C(actor) }
 *
 * Frame (0x60): sp+0x10 s16 buf[4]   (func_80015978/func_80015954 position temp)
 *               sp+0x18 SVECTOR rot  (8 bytes, align 2)
 *               sp+0x20 MATRIX  m    (0x20 bytes)
 *               sp+0x40 Vec32   vel  (16 bytes, align 4)
 *               sp+0x50..0x5F saved s0/s1/s2/ra
 * -> declaration order IS frame order (gcc-2.7.2 MIPS frame grows upward).
 */

extern void func_8001CF00(s32 a0);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_80015954(s32 a0, s32 a1);
extern void func_801465C0(void);
extern void func_80146C3C();
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern int rand(void);


void func_8017F340(s32 param_1) {

    extern SV_8017D7C0_8017F340 D_80193FC8[]; /* stride 8, align 2 -> lwl/lwr + swl/swr copy */
    extern V32_8017D7C0_8017F340 D_80193FF8;   /* 16 bytes, align 4 -> plain lw/sw copy      */
    extern u16     D_80194008[]; /* stride 2 scale table                       */
    s16 buf[4];
    SV_8017D7C0_8017F340 rot;
    MTX_8017D7C0_8017F340 m;
    V32_8017D7C0_8017F340 vel;
    s32 obj;
    s32 p;
    s16 *q;
    s32 i;
    u16 sc;

    obj = *(s32 *)(param_1 + 0x34);
    p = ((s32 (*)(void))func_801465C0)();
    *(s32 *)(param_1 + 0x20) = p;

    if (p != 0) {
        func_8001CF00(p);
        *(s32 *)(p + 0x4) |= 0x80000000;
        func_80015978(obj + 4, (s32 *)buf);
        func_80015954((s32)buf, param_1 + 4);

        sc = D_80194008[*(s32 *)(param_1 + 0x30)];
        *(u16 *)(p + 0x18) = *(u16 *)(p + 0x1a) = *(u16 *)(p + 0x1c) = sc;

        vel = D_80193FF8;
        rot = D_80193FC8[*(s32 *)(param_1 + 0x2c)];

        if (*(s32 *)(param_1 + 0x30) != 0) {
            /* LEVER: the compound `+=` is load-bearing. Spelled out as
             * `rot.vx = rot.vx - 0x200 + ((rand() & 0x3f) << 4);` gcc-2.7.2 folds
             * the -0x200 onto the JITTER term (addiu $v0 after the sll) instead of
             * onto the loaded field (addiu $v1 after the lhu) -- 9 mismatched ins.
             * `a += jitter - 0x200` keeps `a` the accumulator and emits the target's
             * lhu / sll / addiu $v1,-0x200 / addu $v1,$v0. See notes at the bottom. */
            rot.vx += ((rand() & 0x3f) << 4) - 0x200;
            rot.vy += ((rand() & 0x3f) << 4) - 0x200;
            rot.vz += ((rand() & 0x3f) << 4) - 0x200;
            vel.vx = ((rand() & 0x1f) - 0x10) << 16;
            vel.vy = ((rand() & 0x1f) - 0x10) << 16;
            vel.vz = ((rand() & 0x1f) - 0x10) << 16;
        }

        func_80049CAC((s32)&rot, (s32)&m);
        func_800484EC((s32)&m, (s32)&vel, (s32)&vel);

        *(s32 *)(param_1 + 0x10) = vel.vx;
        *(s32 *)(param_1 + 0x14) = vel.vy;
        *(s32 *)(param_1 + 0x18) = vel.vz;

        q = (s16 *)(param_1 + 0x38);
        i = 0;
        *(s32 *)(param_1 + 0x4c) = ((rand() & 0x1f) - 0x10) * 11;
        *(s32 *)(param_1 + 0x50) = ((rand() & 0x1f) - 0x10) * 11;
        *(s32 *)(param_1 + 0x54) = ((rand() & 0x1f) - 0x10) * 11;

        do {
            i++;
            *q++ = (rand() & 0x7f) - 0x40;
            *q++ = (rand() & 0x7f) - 0x40;
            *q++ = (rand() & 0x7f) - 0x40;
        } while (i < 3);

        func_80146E90((s32 *)param_1, 2);
        *(s16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


#include "common.h"

extern void func_8017F6D8(s32 arg0);
extern void func_8017F85C(s32*);
extern s32 func_80146E98(s32 a0);
extern void func_80146E90(s32 *a0, s32 a1);

void func_8017F614(s32 param_1) {
    func_8017F6D8(param_1);
    ((void (*)(s32))func_8017F85C)(param_1);
    if (func_80146E98(param_1) != 0) {
        *(s32 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x10) >> 2;
        *(s32 *)(param_1 + 0x14) = *(s32 *)(param_1 + 0x14) >> 2;
        *(s32 *)(param_1 + 0x18) = *(s32 *)(param_1 + 0x18) >> 2;
        func_80146E90((s32 *)param_1, 0x40);
        *(u16 *)(param_1 + 2) += 1;
    }
}


extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();
extern void func_8017F6D8(s32 arg0);
extern void func_8017F85C(s32*);

void func_8017F690(param_1)
s32 param_1;
{
    func_8017F6D8(param_1);
    func_8017F85C(param_1);
    if (func_80146E98(param_1) != 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    }
}


extern void func_8017F700(s32 arg0, s32 arg1);
extern s32 D_80193F64;

void func_8017F6D8(s32 arg0) {
    func_8017F700(arg0, &D_80193F64);
}


typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8017F700;

extern void func_80015978(s32 a0, s32 *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_80017DF8(s16 *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_80017168(void *a0, void *a1);

void func_8017F700(s32 a0, s32 a1)
{
    s32 p;
    MTX_8017F700 mtx;
    s16 buf[4];

    p = *(s32 *)(a0 + 0x20);
    *(s32 *)(a1 + 0x1c) = 0x50000000;

    func_80017DC4((void *)(p + 0x18), &mtx);
    func_80017DF8((s16 *)(p + 0x10), &mtx);
    func_80015978(a0 + 4, (s32 *)buf);
    func_80017E68((void *)buf, &mtx);
    func_80017168((void *)a1, &mtx);

    mtx.t[0] += *(s16 *)(a0 + 0x38);
    mtx.t[1] += *(s16 *)(a0 + 0x3a);
    mtx.t[2] += *(s16 *)(a0 + 0x3c);
    func_80017168((void *)a1, &mtx);
    func_80017E68((void *)buf, &mtx);

    mtx.t[0] += *(s16 *)(a0 + 0x3e);
    mtx.t[1] += *(s16 *)(a0 + 0x40);
    mtx.t[2] += *(s16 *)(a0 + 0x42);
    func_80017168((void *)a1, &mtx);
    func_80017E68((void *)buf, &mtx);

    mtx.t[0] += *(s16 *)(a0 + 0x44);
    mtx.t[1] += *(s16 *)(a0 + 0x46);
    mtx.t[2] += *(s16 *)(a0 + 0x48);
    func_80017168((void *)a1, &mtx);
}


void func_8017F85C(s32 *a0) {
    s32 *p;

    a0[1] += a0[4];
    a0[2] += a0[5];
    a0[3] += a0[6];
    p = (s32 *)a0[8];
    *(u16 *)((s32)p + 0x10) += (u16)a0[0x13];
    *(u16 *)((s32)p + 0x12) += (u16)a0[0x14];
    *(u16 *)((s32)p + 0x14) += (u16)a0[0x15];
}


void func_8017F8D0(s32 *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0x80404080;
    }


#include "common.h"

extern u16 D_800B99DA;

s32 func_8017F8E0(void *a0) {
    u8 val;
    u16 global;
    s16 result;
    s32 cmp;

    val = *(u8 *)((s32)a0 + 3) - 2;
    *(u8 *)((s32)a0 + 3) = val;

    if ((val & 0xFF) == 0) {
        goto ret1;
    }


    global = D_800B99DA;

    if ((global & 1) == 0) {
        goto add40;
    }
    result = val & 0xFF;
    goto joinpt;
add40:
    result = (val & 0xFF) + 0x40;
joinpt:

    if (result >= 0x101) {
        result = 0xFF;
    }

    cmp = result + 0;

    *(u8 *)((s32)a0 + 2) = result;
    if (cmp < (s32)*(u8 *)a0) {
        *(u8 *)a0 = result;
    }

    if (cmp < (s32)*(u8 *)((s32)a0 + 1)) {
        *(u8 *)((s32)a0 + 1) = result;
    }

    return 0;

ret1:
    return 1;
}



extern void (*D_8019429C[])(void);

void func_8017F96C(void *a0) {
    D_8019429C[*(u8 *)((s32)a0 + 0x15)]();
}


extern s32 D_8011F9C4;
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8017FCDC(void);
extern void func_800167B8(s32 a0);

s32 func_8017F9A8(void *a0)
{
    D_8011F9C4 = 1;
    func_8002D4C8(6, 0);
    func_8017FCDC();
    func_800167B8(0);
    *(u8 *)((s32)a0 + 0x15) = *(u8 *)((s32)a0 + 0x15) + 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017FA08(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}



extern void (*D_801942A4[])(void);

void func_8017FA2C(void *a0) {
    D_801942A4[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017FD04(void);

s32 func_8017FA68(s32 a0) {
    func_8017FD04();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017FAA8(u8 *a0) {
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
    void func_8017FB24(void) {
        func_800D1EBC();
    }



extern void (*D_801942B0[])(void);

void func_8017FB44(void *a0) {
    D_801942B0[*(u8 *)((s32)a0 + 0x15)]();
}




















extern void func_8017FE44(void);
s32 func_8017FB80(s32 arg0)
{
  s32 temp_v0;
 do { func_8017FE44(); temp_v0 = (*((u8 *) (arg0 + 0x15))) + 1; *((u8 *) (arg0 + 0x15)) = temp_v0; } while (temp_v0 = 0);
  return temp_v0;
}


s32 func_8017FBBC(void) {
    return 0;
}


extern void func_8001BFD0(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017FBC4(s32 a0)
{
    u8 *s0 = (u8 *)a0;
    func_8002D4C8(0x1C, 0);
    func_8001BFD0();
    func_8002D4C8(0x1D, 0);
    func_800D0C48(1);
    func_800D1E28();
    s0[0x15] = s0[0x15] + 1;
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017FC2C(void) {
        func_800D1EBC();
    }



extern void (*D_801942C8[])(void);

void func_8017FC4C(void *a0) {
    D_801942C8[*(u8 *)((s32)a0 + 0x216)]();
}


extern s32 func_80171990(u8*);
void func_8017FC88(void) {
    ((void (*)(void))func_80171990)();
}


extern void func_80171928(void *a0);
    s32 func_8017FCA8(s32 arg0) {
        if (*(s16 *)(arg0 + 0xa) >= -0x7a2) {
            ((void (*)(void))func_80171928)();
        }
    }


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern char D_801942C0[];

void func_8017FCDC(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_801942C0, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017FD04(void) {

    extern s32 D_801942D0(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801942D0, 0x1000000);
}



extern void (*D_801942E4[])(void);

void func_8017FD2C(void *a0) {
    D_801942E4[*(u8 *)((s32)a0 + 0x216)]();
}


#include "common.h"

extern void func_80175454(void);
extern s32 func_80171990(u8 *a0);
extern s32 func_8012AD50(void *a0);
extern void func_8017FDF0(void *a0);
extern u8 D_801202A0[];

void func_8017FD68(void *a0) {
    s32 i;
    u8 *ptr;

    func_80175454();
    func_80171990((u8 *)a0);

    for (i = 0; i < 0x60; i++) {
        ptr = D_801202A0 + (i * 0x10C);
        if (*(u16 *)ptr == 0x3AF) {
            func_8012AD50(ptr);
        }
    }

    func_8017FDF0(a0);
}


extern s32 func_8012E544(s32 a0);
extern void func_80171928(void *a0);
extern u8 D_800AE6BD;

void func_8017FDF0(void *a0) {
    if (func_8012E544(0x3AF) == 0) {
        D_800AE6BD = D_800AE6BD + 1;
        func_80171928(a0);
    }
}


extern s32 D_801942DC;
extern void func_8016EE40(s32 a0, s32 a1, s32 a2);

void func_8017FE44(void) {
    ((void (*)(s32, s32))func_8016EE40)((s32)&D_801942DC, 0x1000000);
}




extern void func_8012A018(s32 a0, s32 a1);
extern void func_8012A094(s32 a0);
extern void func_80180050(void *a0);

void func_8017FE6C(void) {

    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8 D_80126948[];
    D_80126954 = 0x190;
    D_8012695C = 0x384;
    D_80126968 = 0x2aa;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_80180050, 0);
    func_8012A094((s32)D_80126948);
    func_80180050(D_80126948);
}


#include "common.h"

extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern void func_80180050(void *a0);
extern void func_8012A018(s32 a, s32 b);

void func_8017FF04(void) {
    D_80126954 = 0x12C;
    D_8012695C = 0x2EE;
    D_80126968 = 0x155;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x96;
    D_8012697A = 0;
    func_8012A018((s32)func_80180050, 1);
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
extern s16 D_80126F00;

extern void func_8012A048(void *a0, s32 a1, u8 a2);
extern void func_8012A094(s32 a0);
extern void func_80180050(void *a0);
extern void func_8012A100(s8 a0);

void func_8017FF80(void) {
    extern s32 D_80126E6C;
    extern s32 D_80126E74;
    extern s16 D_80126E80;
    extern s16 D_80126E82;
    extern s16 D_80126E84;
    extern s16 D_80126E8E;
    extern s16 D_80126E90;
    extern s16 D_80126E92;
    extern s16 D_80126F00;

    s32 *s0 = (s32 *)D_80126E60;

    D_80126E6C = 0x190;
    D_80126E74 = 0x258;
    D_80126E80 = -0xE3;
    D_80126E82 = 0x400;
    {
        s32 temp_func = (s32)func_80180050;
        s32 temp_v0 = 0x20;
        D_80126E84 = 0;
        D_80126E8E = 0;
        D_80126E90 = temp_v0;
        D_80126E92 = 0;

        func_8012A048(s0, temp_func, 0x2);
        func_8012A094((s32)s0);
        func_80180050(s0);
        func_8012A100(0x1);
    }

    D_80126F00 = 0;
}



extern void func_8012A100(s8 a0);
void func_80180030(void) {
    func_8012A100(0);
}



extern void (*D_8019433C[])(void);

void func_80180050(void *a0) {
    D_8019433C[*(u8 *)((s32)a0 + 0x4)]();
}


#include "common.h"

/* 8-byte block, align 2 -> lwl/lwr/swl/swr copy (cookbook §48-C2, matches
 * the Blk8_80126940_* family in shared/engine_types.h) */
typedef struct {
    s16 v[4];
} Blk8_80126940_8018008C;

extern Blk8_80126940_8018008C D_80126940;
extern Blk8_80126940_8018008C D_801274E8;

extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

extern void func_8012A018(s32 a0, s32 a1);
extern void func_80180050(void *a0);
extern void func_80180570(s32 a0);
extern void func_801803D8(s32 param_1, s16 *param_2);

extern u8 D_80194328[];
extern u8 D_80194314[];
extern u8 D_801942EC[];
extern u8 D_80194300[];

void func_8018008C(s32 a0) {
    s32 s0 = a0;
    Blk8_80126940_8018008C local = D_80126940;

    if (local.v[2] >= 0x1501) {
        D_801274E8 = local;
        D_80126954 = 0x12C;
        D_8012695C = 0x2EE;
        D_80126968 = 0x155;
        D_8012696A = 0x800;
        D_8012696C = 0;
        D_80126976 = 0;
        D_80126978 = -0x96;
        D_8012697A = 0;
        func_8012A018((s32)func_80180050, 1);
    } else {
        s32 msg;
        if (local.v[2] >= 0x901) {
            msg = (s32)&D_80194328;
        } else {
            if (local.v[0] >= 0x441) {
                msg = (s32)&D_80194314;
            } else {
                if (local.v[2] >= 0x341) {
                    msg = (s32)&D_80194300;
                } else {
                    msg = (s32)&D_801942EC;
                }
            }
        }
        func_80180570(msg);
    }

    if (local.v[1] >= -0x67F) {
        local.v[1] = -0x680;
    }
    func_801803D8(s0, local.v);
}


extern s32 D_801151D4;
    void func_80180200(void) {
        *(s32 *)(D_801151D4 + 0x14) = 0x2EE;
    }



extern s32 D_801151D4;
    void func_80180214(void) {
        *(s32 *)(D_801151D4 + 0x14) = 0x4B0;
    }


#include "common.h"



extern Blk8_80126940_8018008C D_80126940;
extern Blk8_80126940_8018008C D_801274E8;
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_801803D8(s32 param_1, s16 *param_2);

void func_80180228(s32 a0) {
    Blk8_80126940_8018008C local = D_80126940;

    if (local.v[0] < 0x340) {
        local.v[0] = 0x340;
    }
    if (local.v[0] >= 0x6C1) {
        local.v[0] = 0x6C0;
    }
    if (local.v[2] < 0x1580) {
        local.v[2] = 0x1580;
    }
    if (local.v[2] >= 0x1801) {
        local.v[2] = 0x1800;
    }

    if (D_801274E8.v[1] != -0x782) {
        D_801274E8.v[1] = func_80012C6C(D_801274E8.v[1], -0x782, 0x10);
    }

    local.v[1] = D_801274E8.v[1];
    func_801803D8(a0, local.v);
}


void func_80180320(s32 param_1) {
    s16 sVar1;
    s16 local[4];

    switch (*(s16 *)(param_1 + 0xA0)) {
    case 0:
        sVar1 = *(s16 *)(param_1 + 0x22) + 2;
        *(s16 *)(param_1 + 0x22) = sVar1;
        *(s16 *)(param_1 + 0x1A) = sVar1;
        if (0x800 < sVar1) {
            *(s16 *)(param_1 + 0xA0) = 1;
        }
        break;
    case 1:
        sVar1 = *(s16 *)(param_1 + 0x22) - 2;
        *(s16 *)(param_1 + 0x22) = sVar1;
        *(s16 *)(param_1 + 0x1A) = sVar1;
        if (sVar1 < 0x400) {
            *(s16 *)(param_1 + 0xA0) = 0;
        }
        break;
    }
    func_80186EFC((s32)local);
    func_801803D8(param_1, local);
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

void func_801803D8(s32 param_1, s16 *param_2) {
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;

    *(s32 *)(param_1 + 0x8)  = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x8),  (s32)*(s16 *)(param_1 + 0xC),  10);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C((s32)*(s16 *)(param_1 + 0x10), (s32)*(s16 *)(param_1 + 0x14), 10);
    *(s16 *)(param_1 + 0x18) = func_80012ABC((s32)*(s16 *)(param_1 + 0x18), (s32)*(s16 *)(param_1 + 0x20), 10);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1A), (s32)*(s16 *)(param_1 + 0x22), 10);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC((s32)*(s16 *)(param_1 + 0x1C), (s32)*(s16 *)(param_1 + 0x24), 10);
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


void func_80180570(s32 arg0) {

    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;

    D_80126954 = *(s16 *)((s32)arg0 + 0x0);
    D_8012695C = *(s16 *)((s32)arg0 + 0x2);
    D_80126968 = *(u16 *)((s32)arg0 + 0x4);
    D_8012696A = *(u16 *)((s32)arg0 + 0x6);
    D_8012696C = *(u16 *)((s32)arg0 + 0x8);
    D_80126976 = *(u16 *)((s32)arg0 + 0xC);
    D_80126978 = *(u16 *)((s32)arg0 + 0xE);
    D_8012697A = *(u16 *)((s32)arg0 + 0x10);
}


















extern void func_8012AD44(s32 *a0, s16 a1);
void func_801805D8(void)
{
  int new_var;
  ((void (*)(s32, s32)) func_8012AD44)(new_var, 1);
  new_var = 0x100000;
}

extern void func_8018637C(s32 arg0, s32 arg1);
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern s32 D_801DEC6C;
    void func_801805F8(s32 param_1) {
        func_8018637C(param_1, &D_801DEC6C);
        ((void (*)(s32, s32))func_8012AD44)(param_1, 2);
    }



extern void func_8002D4C8(s32 arg0, s32 arg1);
    void func_80180634(void *arg0) {
        *(s32 *)((char *)arg0 + 0x1c) = 0x40;
        func_8002D4C8(0x7F2, 0);
    }


extern void func_8012BEE8(u8 *a0);
extern void func_8013C9C4(void *a0);

s32 func_80180660(void *param)
{
    extern u8 D_80190B88[];
    void *s0 = param;

    if (((s32 (*)(s32))func_8012BEE8)((s32)s0) != 0) {
        return 1;
    }
    if ((*(s32 *)((char *)s0 + 0x1C) & 0xF) != 0) {
        return 0;
    }
    func_8013C9C4(D_80190B88);
    return 0;
}


void func_801806B8(void *arg0)
{
    extern u16 D_801EFD40;
    extern u8 D_80194460[];
    extern void func_8018332C(s32 a0, s32 a1);
    extern s32 D_801EFCA0;
    extern void func_8018A47C(void *a0);
    s32 v;

    D_801EFD40 = (D_801EFD40 | 0x20) & 0xFFF7;
    func_8018332C((s32)arg0, (s32)&D_80194460);
    v = D_801EFCA0;
    *(s32 *)((s32)arg0 + 0x1C) = 0x20;
    func_8018A47C((void *)v);
}


extern void func_801833D4(int a0, int a1);
extern s32 func_80183A28(u8 *a0);
extern void func_8012BEE8(u8 *a0);
void func_80180714(u8 *a0) {
    func_801833D4((int)a0, -64);
    func_80183A28(a0);
    func_8012BEE8(a0);
}


extern s32 func_80183A28(u8 *a0);
extern void func_801833D4(int a0, int a1);

s32 func_80180750(u8 *a0) {
    if (((s32 (*)(int, int))func_801833D4)((int)a0, -0x40) != 0) {
        return 1;
    }
    func_80183A28(a0);
    return 0;
}


#include "common.h"

extern void func_801837C4(s32, s32);
extern void func_80183BAC(u8*);

void func_80180790(s32 self) {
    ((void (*)(s32))func_801837C4)(self);
    ((void (*)(s32))func_80183BAC)(self);
    *(u16 *)(self + 0x100) = 0;
    *(s32 *)(self + 0x1C) = 0x70;
}


extern u16 D_801EFD20;
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern void func_80183880(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80185960(s32 target, u16 *cur, s32 step);
extern void func_8012BEE8(u8*);

s32 func_801807CC(void *param)
{
    s32 obj;
    s16 x;
    s16 y;
    void *self;

    self = param;
    obj = aFC4C[D_801EFD20];
    x = *(u16 *)(*(s32 *)(obj + 0x20) + 0x12) & 0xFFF;
    if (x >= 0x800) {
        x |= 0xF000;
    }
    func_80183880((s32)self);
    y = *(u16 *)(*(s32 *)(obj + 0x20) + 0x12) & 0xFFF;
    if (y >= 0x800) {
        y |= 0xF000;
    }
    if ((x < -0x200 && -0x201 < y) || (-0x200 < x && y < -0x1FF)) {
        func_8002D4C8(0x9C3, 0);
    }
    func_80185960(0, (u16 *)(*(s32 *)(obj + 0x20) + 0x14), 0xFFC0);
    if (((s32 (*)(s32))func_8012BEE8)((s32)self) != 0) {
        return !*(s16 *)(*(s32 *)(obj + 0x20) + 0x14);
    }
    return 0;
}


void func_801808EC(void *arg0)
{
    extern u8 D_80194468[];
    extern void func_8018332C(s32 a0, s32 a1);
    extern void func_8002D4C8(s32 a0, s32 a1);

    func_8018332C((s32)arg0, (s32)&D_80194468);
    *(s32 *)((s32)arg0 + 0x1C) = 0x10;
    func_8002D4C8(0x9C3, 0);
}


extern void func_801833D4(int a0, int a1);
extern s32 func_80183A28(u8 *a0);

s32 func_80180930(u8 *a0) {
    if (((s32 (*)(int, int))func_801833D4)((int)a0, 0x20) != 0) {
        return 1;
    }
    func_80183A28(a0);
    return 0;
}


extern u16 D_801EFD40;
extern void func_801863D4();
extern void func_8018637C(s32 a0, s32 a1);
extern s32 D_801DECA4;

void func_80180970(void *a0)
{
    void *s0 = a0;

    D_801EFD40 &= 0xFFFB;
    func_801863D4(s0);
    {
        void *t;
        t = s0;
        *(s16 *)((u8 *)t + 0x6) = -0x40;
        *(s16 *)((u8 *)t + 0xE) = 0x40;
        *(s16 *)((u8 *)t + 0xA) = -0x200;
        func_8018637C((s32)t, (s32)&D_801DECA4);
    }
}


s32 func_801809D4(s32 *a0) {
    return *(s16 *)((s32)a0 + 0x98) == 0;
}


extern void func_8018FC58(void *a0);

void func_801809E0(s32 arg0) {
    s32 s0;

    s0 = arg0;
    func_8017FF80();
    func_8018FC58((void *)3);
    *(s32 *)(s0 + 0x1C) = 0xC0;
    *(s16 *)(s0 + 0x84) = 0x28;
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012BEE8(u8*);
extern void func_80180030(void);
extern void func_8018FC84(void);

s32 func_80180A20(s32 *param_1) {
    s16 v;
    s32 r;

    v = *(u16 *)((s32)param_1 + 0x84) - 1;
    *(u16 *)((s32)param_1 + 0x84) = v;
    if (v == 0x14) {
        func_8002D4C8(0x9C2, 0);
    }
    if (*(s16 *)((s32)param_1 + 0x84) == 0) {
        func_8002D4C8(0x9C4, 0);
        *(u16 *)((s32)param_1 + 0x84) = 0x28;
    }
    r = ((s32 (*)(s32))func_8012BEE8)((s32)param_1);
    if (r != 0) {
        func_80180030();
        func_8018FC84();
    }
    return r;
}


struct Ent_80180AB4 {
    /* 0x00 */ u8  pad00[0x34];
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u8  pad36[0xAA];
    /* 0xE0 */ u16 unkE0;
    /* 0xE2 */ u8  padE2[0x10];
    /* 0xF2 */ s16 unkF2;
    /* 0xF4 */ s16 unkF4;
};

void func_80180AB4(struct Ent_80180AB4 *arg0) {
    extern u8 D_80194470[];
    extern void func_8018332C(s32 a0, s32 a1);
    extern void func_80183BAC(u8 *a0);
    extern u16 D_801EFD40;
    extern void func_8012AD44(s32 *a0, s16 a1);

    arg0->unkF4 = 0;
    func_8018332C((s32)arg0, (s32)&D_80194470);
    func_80183BAC((u8 *)arg0);
    arg0->unkE0 = 0x10;
    arg0->unkF2 = 0;
    D_801EFD40 |= 0x200;
    func_8012AD44((s32 *)arg0, 3);
    arg0->unk34 = 3;
}


/* func_80180B24 — S71a_1 fable. Body = .run/pool_1/opus (standalone MATCH 215/215);
 * integration fix: D_80126B58 spelled through the TU's house __asm__ alias (the TU also
 * declares it `u8 []` at block scope in func_80184978, so a file-scope `s32` decl conflicts). */
struct Ent_80180B24 {
    /* 0x00 */ u8  pad00[0x34];
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u8  pad36[0xBC];
    /* 0xF2 */ u16 unkF2;
    /* 0xF4 */ u16 unkF4;
};
extern u16 D_801EFD20;
extern u16 D_801EFD40;
extern s32 aB58_80180B24[1] __asm__("D_80126B58");
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern u8 D_80194470[];
extern void func_80183880(s32 a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012BEE8(u8 *a0);
extern void func_80183564(s32 a0, s16 *a1);
extern void func_801833D4(int a0, int a1);
extern s32 func_80183A28(u8 *a0);
extern void func_80180E80(u8 *self);
extern void func_80183BAC(u8 *a0);
extern void func_801837C4(s32, s32);

void func_80180B24(s32 s0)
{
    /* BLOCK scope on purpose (house style, TU l.5019/5156): the TU defines
     * `void func_80183BD0(s32 a0)` at ~l.7238 and its earlier block-scope `(u8 *a0)` externs
     * sit in limbo; a FILE-scope decl here would let gcc-2.7.2's pushdecl merge that
     * prototype into the global (different_binding_level) and the definition then errors
     * `conflicting types for func_80183BD0` -- measured on a spliced-TU cc1 run. */
    extern void func_80183BD0(u8 *a0);
    struct Ent_80180B24 *p;
    s32 a;
    s32 ta;
    s32 tb;
    s32 tc;
    s32 s1;
    s32 s3;
    s16 x;
    s16 y;
    s16 buf[3];

    p = (struct Ent_80180B24 *)s0;
    s3 = (s32)&aB58_80180B24[0];
    if (*(u16 *)(s0 + 0x34) == 4) {
        s1 = aFC4C[D_801EFD20];
        x = *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF;
        if (x >= 0x800) {
            x |= 0xF000;
        }
        func_80183880((s32)s0);
        y = *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF;
        if (y >= 0x800) {
            y |= 0xF000;
        }
        if ((x < -0x200 && -0x201 < y) || (-0x200 < x && y < -0x1FF)) {
            func_8002D4C8(0x9C3, 0);
        }
        if (((s32 (*)(u8 *))func_8012BEE8)((u8 *)s0) != 0) {
            buf[0] = *(u16 *)(s3 + 6);
            buf[1] = *(u16 *)(s3 + 0xA) - 0x50;
            buf[2] = *(u16 *)(s3 + 0xE);
            func_80183BD0((u8 *)s0);
            func_80183564((s32)s0, buf);
            *(u16 *)(s0 + 0xE0) = 0x10;
            *(u16 *)(s0 + 0x34) = 0;
        }
        return;
    }
    if (((s32 (*)(int, int))func_801833D4)((int)s0, 0) != 0) {
        switch (*(u16 *)(s0 + 0x34)) {
        case 0:
            /* §49-variant/§30#3: zero-byte re-ties set reg_n_sets=2, killing sched1's
             * birthing_insn_p LAUNCH_PRIORITY boost that glued each add to its store;
             * yields the target's load*3 / add*3 / store*3 order. */
            ta = *(u16 *)(s0 + 0xF4) + 1;
            tb = *(u16 *)(s0 + 0xF2) + 1;
            __asm__("" : "=r"(ta) : "0"(ta));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
            __asm__("" : "=r"(tb) : "0"(tb));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
            *(u16 *)(s0 + 0xF4) = ta;
            *(u16 *)(s0 + 0xF2) = tb;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8002D4C8(0x992, 0);
            break;
        case 1:
            /* struct-member spelling (MEM_IN_STRUCT_P) on the s0 fields defeats the false
             * alias against the D_801EFD40 store. */
            D_801EFD40 = D_801EFD40 & 0xFFFE;
            a = p->unkF4 + 1;
            p->unkF4 = a + (p->unkF2 & 1);
            tc = p->unk34 + 1;
            __asm__("" : "=r"(tc) : "0"(tc));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
            p->unk34 = tc;
            break;
        case 2:
            if (*(s16 *)(s0 + 0x76) == 0) {
                func_80180E80((u8 *)s0);
                return;
            }
            *(u16 *)(s0 + 0xF4) = 0;
            func_80183BAC((u8 *)s0);
            *(u16 *)(s0 + 0x34) = 3;
            break;
        case 3:
            ((void (*)(s32))func_801837C4)(s0);
            func_80183BAC((u8 *)s0);
            *(s32 *)(s0 + 0x1C) = 0x80;
            *(u16 *)(s0 + 0x100) = 0;
            *(u16 *)(s0 + 0x34) = 4;
            return;
        }
        func_80183564((s32)s0, (s16 *)(D_80194470 + (*(s16 *)(s0 + 0xF4) * 8)));
        *(u16 *)(s0 + 0xE0) = 0x10;
    } else {
        /* store 0xE0 in BOTH arms: cross_jump merges the sh at the join, and the s16 local
         * yields the un-coalesced addu $v1,$v0,$zero that stops reorg stealing the decrement. */
        s16 v0 = *(s16 *)(s0 + 0xE0);
        if (v0 != 0) {
            *(s16 *)(s0 + 0xE0) = v0 - 1;
        } else {
            func_80183A28((u8 *)s0);
            *(s16 *)(s0 + 0xE0) = 0x10;
        }
        if (*(u16 *)(s0 + 0x34) == 0) {
            u16 flag = D_801EFD40;
            if (!(flag & 1)) {
                s1 = aFC4C[D_801EFD20];
                if ((u16)(((*(u16 *)(s0 + 0x106) & 0xFFF) -
                           (*(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) & 0xFFF)) - 0x180) >= 0xD01) {
                    D_801EFD40 = flag | 1;
                    func_8002D4C8(0x7E3, 0);
                }
            }
        }
    }
}


extern void func_80183564(s32 a0, s16 *a1);
extern s32 func_80186710(void);
extern void func_8012AD44(s32 *a0, s16 a1);
extern u16 D_801EFD20;
extern u16 D_801EFD40;
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern u8 D_80194490[];

void func_80180E80(u8 *self) {
    s32 obj;
    s32 vp1;
    s32 vp2;

    obj = aFC4C[D_801EFD20];
    vp1 = *(s32 *)(obj + 0x20);
    *(s16 *)(obj + 6) = 0x640;
    *(s16 *)(obj + 0xA) = -0x980;
    *(s16 *)(obj + 0xE) = 0x240;
    *(s16 *)(vp1 + 0x12) = 0x600;
    vp2 = *(s32 *)(obj + 0x20);
    *(s16 *)(vp2 + 0x10) = 0;
    *(s16 *)(self + 0xFE) = 0;
    func_80186710();
    *(s16 *)(self + 0xF4) = 0;
    *(s16 *)(self + 0xF2) = 0;
    func_80183564((s32)self, (s16 *)D_80194490);
    D_801EFD40 = D_801EFD40 & 0xFDFF;
    func_8012AD44((s32 *)self, 4);
}


extern void func_801833D4(int a0, int a1);
extern s32 func_80183A28(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80183564(s32 a0, s16 *a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_801837C4(s32, s32);
extern void func_80183BAC(u8*);
extern void func_801861D4(s32 a0);
extern void func_8018A018(s32 a0);
extern void func_80183880(s32 a0);
extern void func_80185960(s32 target, u16 *cur, s32 step);
extern void func_8012BEE8(u8*);
extern void func_80189D38(void*);
extern void func_801811D0(s32 *a0);
extern void func_8013C9C4(void *a0);
extern u16 D_801EFD20;
extern s32 D_801EFCA4;
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern s32 D_801EFCE8[];
extern u8 D_80194490[];
extern u8 D_80194470[];
extern u8 D_80190B88[];

void func_80180F30(s32 s2)
{
    s32 v0;
    s32 v1;
    s32 s1;
    s32 *s0;

    if ((*(u16 *)(s2 + 0x34) < 4)) {
        if (((s32 (*)(int, int))func_801833D4)(s2, 0x30) != 0) {
            switch (*(u16 *)(s2 + 0x34)) {
            case 0:
                *(s16 *)(s2 + 0x84) = 0;
                /* fallthrough */
            case 1:
                v1 = *(u16 *)(s2 + 0xF4) + 1;
                *(u16 *)(s2 + 0xF4) = v1;
                func_80183564(s2, (s16 *)(D_80194490 + (((v1 << 16) >> 13))));
                *(u16 *)(s2 + 0x34) = *(u16 *)(s2 + 0x34) + 1;
                break;
            case 2:
                func_8018A018(D_801EFCA4);
                *(s16 *)(s2 + 0xF2) = 0x20;
                func_80183564(s2, (s16 *)D_80194470);
                *(u16 *)(s2 + 0x34) = *(u16 *)(s2 + 0x34) + 1;
                func_8012C588(0x3D8, s2);
                break;
            case 3:
                ((void (*)(s32))func_801837C4)(s2);
                ((void (*)(s32))func_80183BAC)(s2);
                *(u16 *)(s2 + 0x100) = 0;
                *(s32 *)(s2 + 0x1C) = 8;
                *(u16 *)(s2 + 0x34) = *(u16 *)(s2 + 0x34) + 1;
                func_801861D4(s2);
                break;
            }
        } else {
            func_80183A28((u8 *)s2);
            if (*(u16 *)(s2 + 0x34) == 1) {
                v0 = *(u16 *)(s2 + 0x84) + 1;
                *(s16 *)(s2 + 0x84) = v0;
                if (((v0 << 16) >> 16) == 0x50) {
                    func_8002D4C8(0x992, 0);
                }
            }
        }
    } else {
        func_80183880(s2);
        func_80185960(0, (u16 *)(*(s32 *)(aFC4C[D_801EFD20] + 0x20) + 0x14), 0x40);
        switch (*(u16 *)(s2 + 0x34)) {
        case 4:
            if (((s32 (*)(u8 *))func_8012BEE8)((u8 *)s2) != 0) {
                *(s16 *)(s2 + 0xF2) = 0xC0;
                s1 = 0x10;
                s0 = D_801EFCE8;
                do {
                    ((void (*)(s32))func_80189D38)(*s0++);
                    s1++;
                } while (s1 < 0x14);
                *(u16 *)(s2 + 0x34) = 5;
            }
            break;
        case 5:
            if (*(s16 *)(s2 + 0xF2) == 0) {
                func_801811D0((s32 *)s2);
            }
            break;
        }
    }
    if (*(s16 *)(s2 + 0xF2) != 0) {
        if ((*(u16 *)(s2 + 0xF2) & 0xF) == 0) {
            func_8013C9C4(D_80190B88);
        }
        *(u16 *)(s2 + 0xF2) = *(u16 *)(s2 + 0xF2) - 1;
    }
}


void func_801811D0(s32 *arg0) {
    extern s16 D_801944A8[];
    extern void func_8018332C(s32 a0, s32 a1);
    extern void func_80183BD0(u8 *a0);
    extern void func_80186BD8(void);
    extern void func_8012AD44(s32 *a0, s16 a1);

    *(s16 *)((s32)arg0 + 0xF4) = 0;
    func_8018332C((s32)arg0, (s32)&D_801944A8);
    func_80183BD0((u8 *)arg0);
    *(u16 *)((s32)arg0 + 0xF2) = 0;
    func_80186BD8();
    func_8012AD44(arg0, 5);
}


#include "common.h"

/* §183: this TU declares D_80126B58 at BLOCK scope with other shapes (u8[] in func_80184978,
   u16 in func_80187068). A FILE-scope decl here turns those into hard errors, so reach the
   symbol through an __asm__ label alias (the TU's own idiom, func_80188094 L6390). */
extern s32 aB58_80181220[1] __asm__("D_80126B58");
extern s16 D_801944A8[][4];

/* §183 SIGNATURE-cast-at-call: the TU declares `extern void func_801833D4(int, int);`
   (L4269/L4328) and recovers the s32 result with a call-site function-pointer cast
   (its own idiom at L4362). Same here. */
extern void func_801833D4(int a0, int a1);
extern s32 func_80183A28(u8 *a0);
extern void func_80181390(s32 a0);
extern void func_80183564(s32 a0, s16 *a1);
extern void func_8002D4C8(s32 arg0, s32 arg1);

void func_80181220(s32 a0) {
    s32 s0;
    u8 *s1;
    s32 v0;
    u16 state;
    s16 t;
    s16 buf[3];

    s0 = a0;
    s1 = (u8 *)&aB58_80181220[0];

    v0 = ((s32 (*)(int, int))func_801833D4)((int)s0, 0);
    if (v0 != 0) {
        state = *(u16 *)(s0 + 0x34);
        switch (state) {
        case 0:
        case 2:
            if (*(s16 *)(s0 + 0xF2) != 0) {
                func_80181390(s0);
            } else {
                buf[0] = *(u16 *)(s1 + 0x6);
                buf[1] = *(u16 *)(s1 + 0xA) - 0x50;
                buf[2] = *(u16 *)(s1 + 0xE);
                func_80183564(s0, buf);
                *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            }
            break;
        case 1:
        case 3: {
            u16 idx = (u16)((*(u16 *)(s0 + 0xF4) + 1) & 1);
            *(u16 *)(s0 + 0xF4) = idx;
            func_80183564(s0, D_801944A8[idx]);
            *(u16 *)(s0 + 0x34) = (u16)((*(u16 *)(s0 + 0x34) + 1) & 3);
            func_8002D4C8(0x992, 0);
            break;
        }
        default:
            break;
        }
    } else {
        func_80183A28((u8 *)s0);
    }

    t = *(s16 *)(s0 + 0xF2);
    if (t == 0) {
        if (*(s16 *)(s1 + 0xE) >= 0xA01) {
            if (*(s16 *)(s1 + 0xA) >= -0x73F) {
                *(s16 *)(s0 + 0xF2) = t + 1;
            }
        }
    }
}


void func_80181390(s32 a0) {
    extern u8 D_801944B8[];
    extern void func_8018332C(s32 a0, s32 a1);
    extern void func_80186BD8(void);
    extern void func_8012AD44(s32 *a0, s16 a1);

    s16 buf[3];

    *(s16 *)(a0 + 0xF4) = 0;
    buf[0] = 0x500;
    buf[1] = -0xE00;
    buf[2] = *(u16 *)D_801944B8 + 0x200;
    func_8018332C(a0, (s32)buf);
    func_80186BD8();
    func_8012AD44((s32 *)a0, 6);
    *(s16 *)(a0 + 0x34) = 3;
}


void func_801813FC(s32 s0)
{
    u16 t;
    s16 tc;
    s32 a0;
    s32 v7;
    s32 vcmp;
    s32 vs1e;
    s16 buf[7];
    u8 *s1;

    extern u16 D_801EFD20;
    extern u16 D_801EFD40;
    extern s32 D_801EFD18;
    extern s32 aFC4C[] __asm__("D_801EFC4C");
    extern s32 aB58_801813FC[1] __asm__("D_80126B58");
    extern s16 aB62_801813FC __asm__("D_80126B62");
    extern u8 D_801944B8[];
    extern u8 D_801944C8[];
    extern u8 D_80190B88[];
    extern void func_801833D4(int a0, int a1);
    extern s32 func_80183A28(u8*);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_8012BE54(s32 a0);
    extern void func_80186B08(s32 a0);
    extern void func_8013C9C4(void *a0);
    extern void func_80183564(s32 a0, s16 *a1);
    extern void func_80185FAC(void);
    extern s32 func_80188E00(s32 a0, void *a1);
    extern void func_801439C0();
    extern void func_801837C4(s32, s32);
    extern void func_80183BAC(u8*);
    extern void func_80183880(s32 a0);
    extern void func_8012BEE8(u8 *a0);
    extern void func_80183BD0(u8 *a0);

    s1 = (u8 *)aB58_801813FC;

    if (*(u16 *)(s0 + 0x34) != 7) {
        if (((s32 (*)(int, int))func_801833D4)(s0, 0) != 0) {
            switch (*(u16 *)(s0 + 0x34)) {
            case 0:
                func_80186B08(s0);
                func_8013C9C4(D_80190B88);
                buf[0] = 0x500;
                buf[1] = -0xB00;
                buf[2] = *(u16 *)(D_801944B8 + ((*(s16 *)(s0 + 0xF4) << 16) >> 15)) - 0x100;
                func_80183564(s0, buf);
                v7 = 1;
                t = D_801EFD20;
                *(u16 *)(s0 + 0x34) = v7;
                if (((s32 (*)(s32))func_8012BE54)(aFC4C[t]) <= 0x23FFF) {
                    func_8002D4C8(0x992, 0);
                }
                break;
            case 1:
                *(u16 *)(s0 + 0xF4) = *(u16 *)(s0 + 0xF4) + 1;
                if ((s16)*(u16 *)(s0 + 0xF4) >= 8) {
                    func_80185FAC();
                    v7 = 6;
                    t = D_801EFD40;
                    *(u16 *)(s0 + 0x34) = v7;
                    D_801EFD40 = t | 8;
                } else {
                    buf[0] = 0x500;
                    buf[1] = -0xB00;
                    a0 = *(u16 *)(D_801944B8 + ((*(s16 *)(s0 + 0xF4) << 16) >> 15));
                    buf[2] = a0 + 0x580;
                    vs1e = *(s16 *)(s1 + 0xE);
                    vcmp = *(s16 *)(D_801944B8 + ((*(s16 *)(s0 + 0xF4) << 16) >> 15)) + 0xE0;
                    if (vs1e > vcmp) {
                        buf[2] = a0 + 0x280;
                    }
                    func_80183564(s0, buf);
                    *(u16 *)(s0 + 0x34) = 2;
                }
                break;
            case 2:
                buf[0] = 0x600;
                buf[1] = -0xB00;
                buf[2] = *(u16 *)(D_801944B8 + ((*(s16 *)(s0 + 0xF4) << 16) >> 15)) + 0x180;
                func_80183564(s0, buf);
                *(u16 *)(s0 + 0x34) = 3;
                break;
            case 3:
                buf[0] = 0x500;
                buf[1] = -0x700;
                buf[2] = *(u16 *)(D_801944B8 + ((*(s16 *)(s0 + 0xF4) << 16) >> 15));
                D_801EFD18 = func_80188E00(aFC4C[D_801EFD20], buf);
                func_80183564(s0, buf);
                *(s16 *)(s0 + 0x84) = 0;
                *(u16 *)(s0 + 0x34) = 4;
                break;
            case 4:
                func_80186B08(s0);
                func_8013C9C4(D_80190B88);
                if (D_801EFD18 != 0) {
                    func_801439C0(D_801EFD18);
                    D_801EFD18 = 0;
                }
                func_80183564(s0, (s16 *)D_801944C8);
                *(u16 *)(s0 + 0x34) = 5;
                break;
            case 5:
                ((void (*)(s32))func_801837C4)(s0);
                func_80183BAC((u8 *)s0);
                *(u16 *)(s0 + 0x100) = 0;
                tc = *(u16 *)(s0 + 0xF4) + 1;
                *(u16 *)(s0 + 0xF4) = tc;
                vs1e = *(s16 *)(s1 + 0xE);
                vcmp = *(s16 *)(D_801944B8 + ((tc << 16) >> 15)) + 0xC0;
                if (vs1e > vcmp) {
                    *(s32 *)(s0 + 0x1C) = 0x18;
                } else {
                    *(s32 *)(s0 + 0x1C) = (tc == 7) ? 0x18 : 0x90;
                }
                *(u16 *)(s0 + 0x34) = 7;
                break;
            case 6:
                break;
            }
        } else {
            ((void (*)(u8 *))func_80183A28)((u8 *)s0);
            if (*(u16 *)(s0 + 0x34) == 4 && *(s16 *)(s0 + 0x84) == 0) {
                if (((s32 (*)(s32))func_8012BE54)(aFC4C[D_801EFD20]) <= 0x23FFF &&
                    aB62_801813FC - *(s16 *)(aFC4C[D_801EFD20] + 0xA) < 0x180) {
                    func_8002D4C8(0x992, 0);
                    *(s16 *)(s0 + 0x84) = 1;
                }
            }
        }
    } else {
        func_80183880(s0);
        if (((s32 (*)(u8 *))func_8012BEE8)((u8 *)s0) != 0) {
            buf[0] = 0x500;
            buf[1] = -0x700;
            buf[2] = *(u16 *)(D_801944B8 + ((*(s16 *)(s0 + 0xF4) << 16) >> 15));
            func_80183BD0((u8 *)s0);
            func_80183564(s0, buf);
            *(u16 *)(s0 + 0x34) = 0;
        }
    }
}


#include "common.h"

extern void func_80183564(s32 a0, s16 *a1);
extern void func_80183BD0();
extern s32 func_80186710(void);
extern void func_80186BD8(void);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_80188E00(s32 a0, void *a1);

extern u16 D_801EFD20;
extern u16 D_801EFD40;
extern s32 D_801EFD18;
/* §183: the TU spells D_801EFC4C as a scalar elsewhere; reach the array view
   through an __asm__ label alias -- the TU's own established idiom. */
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern u8 D_801944D0[];

void func_80181868(u8 *self) {
    s32 obj;
    s32 vp;

    obj = aFC4C[D_801EFD20];
    if (!(D_801EFD40 & 0x400)) {
        D_801EFD18 = func_80188E00(obj, D_801944D0);
    }
    vp = *(s32 *)(obj + 0x20);
    *(s16 *)(obj + 6) = 0x500;
    *(s16 *)(obj + 0xA) = -0xD88;
    *(s16 *)(obj + 0xE) = 0x1980;
    *(s16 *)(vp + 0x12) = 0;
    vp = *(s32 *)(obj + 0x20);
    *(s16 *)(vp + 0x10) = 0x380;
    *(s16 *)(self + 0xFE) = 0x380;
    func_80186710();
    func_80183BD0(self);
    D_801EFD40 = D_801EFD40 & 0xFFF7;
    func_80183564((s32)self, (s16 *)D_801944D0);
    func_80186BD8();
    func_8012AD44((s32 *)self, 7);
}


#include "common.h"

/* Declarations copied VERBATIM from the destination TU
 * (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c) — see wave law 2.
 *   line 4269: extern void func_801833D4(int a0, int a1);
 *   line 4270: extern s32  func_80183A28(u8 *a0);
 *   line 1304: extern void func_8013C9C4(void *a0);
 *   line 4505: extern u16  D_801EFD40;
 * func_801833D4's s32 result is recovered with a call-site cast (§37 lever)
 * so the TU's `void` spelling is preserved byte-neutrally. */
extern void func_801833D4(int a0, int a1);
extern s32 func_80183A28(u8 *a0);
extern void func_8013C9C4(void *a0);
extern u16 D_801EFD40;

/* Not declared anywhere in the destination TU — typed by access width. */
extern u16 D_801EFD20;
extern s32 D_801EFD14;
extern s32 D_801EFD18;
extern u8 D_801944D8[];
extern u8 D_80190B88[];
extern u8 D_801DF06C[];
extern u8 D_80194C14[];

/* Unprototyped arg lists: composite-type compatible with any prototyped
 * spelling another draft in this TU may add (law 4, function flavour). */
extern void func_80189188();
extern void func_80189270();
extern void func_801439C0();
extern void func_80183564(s32 a0, s16 *a1);
extern void func_80186300(s32, void *, s32);
extern void func_80184CCC();
extern void func_80184DB8(s32 a0);
extern s32 func_80184F4C();
extern void func_80181B30();
extern void func_80184840();

void func_80181948(s32 a0) {
    s32 pad[2];
    u16 g = D_801EFD20;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
    case 1:
        if (((s32 (*)(int, int))func_801833D4)((int)a0, 0) != 0) {
            switch (*(u16 *)(a0 + 0x34)) {
            case 0:
                if ((D_801EFD40 & 0x400) == 0) {
                    func_80189188(D_801EFD14);
                    func_80189270(D_801EFD14);
                    D_801EFD40 |= 0x400;
                    if (D_801EFD18 != 0) {
                        func_801439C0(D_801EFD18);
                        D_801EFD18 = 0;
                    }
                } else {
                    func_80189270(D_801EFD14);
                }
                *(u16 *)(a0 + 0xF4) = 0;
                func_80183564(a0, D_801944D8);
                func_8013C9C4(D_80190B88);
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
                return;
            case 1:
                *(u16 *)(a0 + 6) = 0;
                *(u16 *)(a0 + 0xE) = 0;
                *(u16 *)(a0 + 0xA) = 0;
                func_80186300(a0, D_801DF06C, 0);
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
                return;
            }
        } else {
            func_80183A28((u8 *)a0);
        }
        return;
    case 2:
        if (*(s16 *)(a0 + 0x98) != 0) {
            return;
        }
        D_801EFD20 = 0xD;
        D_801EFD40 &= 0xFFDF;
        func_80184CCC(a0, D_80194C14);
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        return;
    case 3:
        func_80184DB8(g);
        if (func_80184F4C() != 0) {
            func_80181B30(a0);
            func_80184840();
        }
        return;
    }
}


#include "common.h"

/* func_80181B30 — cutscene teardown for this SC04 entity: close the two HUD
 * gauges (func_80185B04 / func_80185C04), tear down the dialogue box, clear the
 * hit-flash timer at 0xF2, recompute the 0x1C field as 6 * the s16 at 0xF6 plus
 * 0x10, and hand the entity to the state dispatcher with mode 8.
 *
 * §103 / wave law 2 — EVERY callee declaration below is deliberately BLOCK-SCOPE,
 * and that is the whole fix for the previous attempt on this function.
 * The previous draft's BODY was already byte-correct (match_one MATCH, 28/28);
 * it declared its callees at FILE scope and the whole-binary gate rejected it,
 * cause undetermined.  Reproduced here against the pinned cc1 by splicing the
 * draft over this TU's INCLUDE_ASM stub — cc1 exits 33 with four HARD errors:
 *     :5353: conflicting types for `func_80185B04'
 *     :5354: conflicting types for `func_80185C04'
 *     :8038: conflicting types for `func_80185B04'
 *     :8083: conflicting types for `func_80185C04'
 * This TU declares both gauge calls as (s32, s32) inside OTHER function bodies
 * (L5327/L5328 and L5643/L5644) and DEFINES both as (u16, u16) later in the same
 * file (L8011 / L8056).  A file-scope extern of either spelling at this insertion
 * point collides with the other; only a block-scope one is invisible to both.
 * func_8012AD44 (file scope, L4510/L5131) and func_80186BD8 (file scope, L5130)
 * ARE already visible here — the declarations below repeat those two spellings
 * verbatim, and (s32, s32) for the gauges is the spelling the TU's own neighbour
 * func_80181BA0 uses at L5643/L5644.
 *
 * Verified before submitting: with this text spliced over the stub the whole TU
 * compiles with ZERO new cc1 diagnostics vs. the unspliced baseline, and every
 * other function in the file emits byte-identical assembly (the only delta is
 * assembler-local $L renumbering, which is byte-neutral).
 *
 * Struct members, not raw casts, on purpose: the target loads 0xF6 BEFORE storing
 * to 0xF2.  Only COMPONENT_REFs of distinct members let sched.c prove the two
 * MEMs do not alias and hoist the `lh` above the `sh`; the `*(s16 *)(a0 + off)`
 * spelling keeps them dependent and emits the store first. */
struct Ent_80181B30 {
    /* 0x00 */ u8  pad00[0x1C];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8  pad20[0xD2];
    /* 0xF2 */ s16 unkF2;
    /* 0xF4 */ u8  padF4[0x2];
    /* 0xF6 */ s16 unkF6;
};

void func_80181B30(struct Ent_80181B30 *a0) {
    extern void func_80183CF4(void *);
    extern void func_80185B04(s32, s32);
    extern void func_80185C04(s32, s32);
    extern void func_80186BD8(void);
    extern void func_8012AD44(s32 *a0, s16 a1);

    func_80183CF4((void *)a0);
    func_80185B04(1, 0x20);
    func_80185C04(3, 0x30);
    func_80186BD8();
    a0->unkF2 = 0;
    a0->unk1C = a0->unkF6 * 6 + 0x10;
    func_8012AD44((s32 *)a0, 8);
}


#include "common.h"

/* [T51] every symbol below is scoped INTO the function body: this TU already carries
   file-scope decls of some of these names with other shapes (cookbook §103 / wave law 2).
   The three names that ARE already visible at file scope before this function
   (func_8012BEE8, func_8013C9C4, func_8002D4C8) are spelled exactly as the TU spells them. */

extern void func_8012BEE8(u8 *a0);
extern void func_8013C9C4(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

/* Real struct types: the entity's members MUST be COMPONENT_REFs so MEM_IN_STRUCT_P is set.
   sched.c true_dependence drops the edge between a (IN_STRUCT && varying) member MEM and the
   (!IN_STRUCT && !varying) SYMBOL_REF global D_801EFD40 -- that is what lets the target hoist
   every `lhu D_801EFD40` above the entity stores (cookbook line 14831). */
struct Sub_80181BA0 {
    /* 0x00 */ u8  pad00[0x12];
    /* 0x12 */ s16 unk12;
};

struct Ent_80181BA0 {
    /* 0x00 */ u8  pad00[0x6];
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u8  pad08[0x2];
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ u8  pad0C[0x2];
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ u8  pad10[0xC];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ struct Sub_80181BA0 *unk20;
    /* 0x24 */ u8  pad24[0x10];
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u8  pad36[0x5E];
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ u8  pad9A[0x58];
    /* 0xF2 */ s16 unkF2;
    /* 0xF4 */ u8  padF4[0x2];
    /* 0xF6 */ s16 unkF6;
};

void func_80181BA0(struct Ent_80181BA0 *a0) {
    extern u16 D_801EFD20;
    extern u16 D_801EFD40;
    /* §183: the TU spells D_801EFC4C as a file-scope SCALAR; reach the array view through an
       __asm__ label ALIAS (the TU's own idiom, func_80188094 L6390). */
    extern s32 aFC4C[] __asm__("D_801EFC4C");
    extern u8 D_801DF1D4[];
    extern u8 D_80194C14[];
    extern u8 D_80190B88[];

    extern void func_80183C74(s32, s32);
    extern void func_80183D00(s32);
    extern void func_80185B5C(u16);
    extern void func_80185C5C(u16);
    extern void func_80184DB8(s32);
    extern void func_80185A30(s32);
    extern void func_80186300(s32 a0, void *a1, s32 a2);
    extern void func_80186BF8(void);
    extern void func_8018AA70(s32);
    /* §183 SIGNATURE-cast-at-call: TU declares (s32, s32); adopt it and cast at the call. */
    extern void func_80184CCC();
    extern void func_80183CF4(void *);
    extern void func_80185B04(s32, s32);
    extern void func_80185C04(s32, s32);
    extern void func_80185214(s32);
    extern s32 func_80184F4C(void);
    extern void func_80186BD8(void);
    extern void func_80181EA0(s32);
    extern s32 func_80184884(void);
    extern void func_801826E4(s32);

    struct Sub_80181BA0 *p;
    s32 pad[2];

    switch (a0->unk34) {
    case 0:
        func_80183C74(aFC4C[D_801EFD20], (0x18 - a0->unkF6 * 4) & 0xFFFC);
        func_80183D00((s32)a0);
        func_80185B5C(1);
        func_80185C5C(3);
        func_80184DB8(D_801EFD20);
        func_80185A30(0);
        if (((s32 (*)(s32))func_8012BEE8)((s32)a0) != 0) {
            p = a0->unk20;
            a0->unk06 = 0x508;
            a0->unk0A = -0x76C;
            a0->unk0E = 0x18CD;
            func_80186300((s32)a0, D_801DF1D4, p->unk12);
            func_80186BF8();
            a0->unk34 = a0->unk34 + 1;
            D_801EFD40 |= 0x800;
        }
        break;
    case 1:
        if (a0->unk98 == 0) {
            u16 f;
            u16 t;
            a0->unk1C = a0->unkF6 * 8;
            f = D_801EFD40;
            t = a0->unk34 + 1;
            a0->unk34 = t;
            D_801EFD40 = f & 0xF7FF;
        } else {
            if (a0->unk94 == 0x28) {
                a0->unkF2 = 0x20;
            }
            if (a0->unk94 == 0x24) {
                func_8002D4C8(0x889, 0);
            }
            if (a0->unk94 >= 0x24 && a0->unk94 <= 0x29) {
                func_8018AA70(aFC4C[0]);
            }
        }
        break;
    case 2:
        if (((s32 (*)(s32))func_8012BEE8)((s32)a0) != 0) {
            u16 t;
            D_801EFD40 |= 0x20;
            func_80184CCC((s32)a0, (s32)D_80194C14);
            func_80183CF4((void *)a0);
            func_80185B04(1, 0x20);
            func_80185C04(3, 0x30);
            func_80185214(a0->unk20->unk12);
            t = a0->unk34 + 1;
            D_801EFD40 |= 2;
            a0->unk34 = t;
        }
        break;
    case 3:
        func_80184DB8(D_801EFD20);
        if (func_80184F4C() != 0) {
            D_801EFD40 &= 0xFFDD;
            func_80186BD8();
            func_80181EA0((s32)a0);
        }
        break;
    }

    if (a0->unkF2 > 0) {
        if ((a0->unkF2 & 0xF) == 0) {
            func_8013C9C4(D_80190B88);
        }
        *(u16 *)&a0->unkF2 = *(u16 *)&a0->unkF2 - 1;
    }
    if ((s16)func_80184884() == 0) {
        func_801826E4((s32)a0);
    }
}


#include "common.h"

/* Entity view for this target only.  The TU already DEFINES `struct Ent_80181BA0`
   at file scope (L5279/L5284) — redefining that tag in a spliced draft is a
   gcc-2.7.2/C89 "redefinition of `struct ...'" plumbing error, which is what sank
   the previous attempt (match_one MATCH, whole-binary gate reject).  A private tag
   carries the same MEM_IN_STRUCT_P property with no collision.

   The members MUST be COMPONENT_REFs: sched.c true_dependence drops the edge
   between an (IN_STRUCT && varying) member MEM and the (!IN_STRUCT && !varying)
   SYMBOL_REF global D_801EFD40, and that is what hoists `lhu D_801EFD40` above
   `sh $v1, 0xF2($a0)` (this TU's own note @L5275, cookbook line 14831). */
struct Ent_80181EA0 {
    /* 0x00 */ u8  pad00[0x1C];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8  pad20[0xD2];
    /* 0xF2 */ s16 unkF2;
};

/* Parameter is s32: the TU declares `extern void func_80181EA0(s32);` inside
   func_80181BA0 (L5332) and calls it as `func_80181EA0((s32)a0)` (L5398). */
void func_80181EA0(s32 a0) {
    /* §T6-3/§2329 self-contained lift unit — every extern spelled exactly as the
       destination TU spells it: func_8012AD44 L4510/L4745, D_801EFD40 L5300,
       func_80184CCC L5203 (unprototyped, §183 cast-at-call), D_80194C3C L5652.
       D_801F161E is undeclared in the TU — typed by access width (sh -> u16). */
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern void func_80184CCC();
    extern u16 D_801EFD40;
    extern u16 D_801F161E;
    extern u8 D_80194C3C[];

    struct Ent_80181EA0 *e = (struct Ent_80181EA0 *)a0;

    func_80184CCC((s32)a0, (s32)D_80194C3C);

    e->unk1C = 0x18;
    e->unkF2 = 5;
    D_801F161E = 0;
    D_801EFD40 = (D_801EFD40 & 0xFFFE) | 2;

    func_8012AD44((s32 *)a0, 9);
}


#include "common.h"

/* Private, single-member view used ONLY for the 0xF2 access in case 3: the member must be
   a COMPONENT_REF so sched.c true_dependence drops the edge against the (!IN_STRUCT,
   !varying) SYMBOL_REF global D_801EFD40 -- that is what hoists `lh 0xF2($s0)` ABOVE
   `sh %lo(D_801EFD40)` (this TU's own note @L5275, cookbook line 14831).  Every OTHER
   entity access stays a raw cast, because cases 0/1 need the OPPOSITE: the D_801EFD40
   load must stay BELOW `sw 0x1C($s0)`. */
struct EntF2_80181F0C {
    /* 0x00 */ u8  pad00[0xF2];
    /* 0xF2 */ s16 unkF2;
};

void func_80181F0C(s32 a0) {
    extern void func_8012BEE8(u8 *a0);
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern void func_80184CCC();
    extern void func_80183DF8(void);
    extern void func_80183C74(s32, u16);
    extern void func_80183D00(s32);
    extern void func_80184DB8(s32);
    extern s16 func_80185A30(s32);
    extern void func_80185B04(u16, u16);
    extern void func_80185C04(u16, u16);
    extern void func_8018214C(s32, s32);
    extern u16 D_801EFD20;
    extern u16 D_801EFD40;
    extern u16 D_801F161E;
    extern u8 D_80194C14[];
    extern u8 D_80194C64[];
    extern u8 D_80194C8C[];
    extern s32 aFC4C[] __asm__("D_801EFC4C");
    extern s32 aB58[] __asm__("D_80126B58");

    /* Hoisted base pointer -- this is what puts the lui/addiu %hi/%lo(D_80126B58) pair in a
       callee-saved reg at function ENTRY, above the switch (the TU's own idiom: func_80185A30
       L8144 `p58 = (s16 *)aB58;`, func_80184978 L7428 `outp = D_80126B58;`). */
    s16 *p58 = (s16 *)aB58;
    u16 t;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (((s32 (*)(s32))func_8012BEE8)(a0) != 0) {
            func_80184CCC(a0, (s32)D_80194C64);
            t = *(u16 *)(a0 + 0x34) + 1;
            *(s32 *)(a0 + 0x1C) = 8;
            D_801EFD40 = D_801EFD40 & 0xFFFD;
            *(u16 *)(a0 + 0x34) = t;
        }
        break;
    case 1:
        if (((s32 (*)(s32))func_8012BEE8)(a0) != 0) {
            func_80184CCC(a0, (s32)D_80194C8C);
            t = *(u16 *)(a0 + 0x34) + 1;
            *(s32 *)(a0 + 0x1C) = 3;
            D_801EFD40 = D_801EFD40 | 1;
            *(u16 *)(a0 + 0x34) = t;
        }
        break;
    case 2:
        if (((s32 (*)(s32))func_8012BEE8)(a0) != 0) {
            func_80183DF8();
            t = *(u16 *)(a0 + 0x34) + 1;
            *(s32 *)(a0 + 0x1C) = (*(s16 *)(a0 + 0xF6) - 1) * 2 + 1;
            *(u16 *)(a0 + 0x34) = t;
        }
        break;
    case 3:
        if (((s32 (*)(s32))func_8012BEE8)(a0) != 0) {
            struct EntF2_80181F0C *e = (struct EntF2_80181F0C *)a0;
            D_801EFD40 = D_801EFD40 & 0xFFFE;
            if (e->unkF2 != 0) {
                e->unkF2 = e->unkF2 - 1;
                *(s32 *)(a0 + 0x1C) = 3;
                *(u16 *)(a0 + 0x34) = 0;
            } else {
                u16 n = *(u16 *)(a0 + 0x34);
                *(s32 *)(a0 + 0x1C) = 0x10;
                *(u16 *)(a0 + 0x34) = n + 1;
            }
        }
        break;
    case 4:
        if (((s32 (*)(s32))func_8012BEE8)(a0) != 0) {
            if (D_801F161E < 2) {
                func_8018214C(a0, p58[3] >= 0x509);
                return;
            }
            func_80184CCC(a0, (s32)D_80194C14);
            ((void (*)(s32, s32))func_80185B04)(1, 0x20);
            ((void (*)(s32, s32))func_80185C04)(3, 0x30);
            func_8012AD44((s32 *)a0, 8);
        }
        break;
    }

    ((void (*)(s32, s32))func_80183C74)(aFC4C[D_801EFD20], 8);
    func_80183D00(a0);
    func_80184DB8(D_801EFD20);
    ((void (*)(s32))func_80185A30)(0);
}


#include "common.h"

void func_8018214C(s32 a0, s32 a1) {
    /* §T6-3/§2329: ALL externs block-scope, types verbatim - self-contained lift unit.
       Legal vs TU decls above (L4593/L4595/L4779/L4788, identical types) and below
       (func_80132EC4 L5378, Rec801944E8/D_801944E8 L5118, compatible layouts). */
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern u16 D_801EFD40;
    extern u8 D_80194C14[];
    extern void func_80184CCC();
    extern void func_80132EC4(s32 a0, s32 a1);
    extern struct { s32 f0; s32 f1; s32 f2; } D_801944E8[];

    s32 s0 = a0;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 v1;

    if (a1 < 0) {
        v0 = rand() & 1;
    } else {
        v0 = a1 & 1;
    }
    *(s16 *)(s0 + 0xE2) = v0;
    __asm__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B t3_tus1)

    v0 = (s32)(*(s16 *)(s0 + 0xE2));
    func_80132EC4(D_801944E8[v0].f0, 0x2);

    D_801EFD40 |= 0x20;
    func_80184CCC((s32)s0, (s32)D_80194C14);
    func_8012AD44((s32 *)s0, 0xA);
}


#include "common.h"

extern s32 D_801EFC48;
/* §183: the TU declares D_801EFC4C at BLOCK scope as `s32[]` further down; a FILE-scope
   scalar decl here turns those into hard errors. Reach it through the batch-wide
   __asm__ label alias instead (the TU's own idiom, func_80188094 L6390). */
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern u16 D_801EFD20;

typedef struct {
    s32 f0;
    s32 f1;
    s32 f2;
} Rec801944E8;
extern Rec801944E8 D_801944E8[];

extern void func_80185960(s32 target, u16 *cur, s32 step);
extern s32 func_80184F4C(void);
/* §183 SIGNATURE-cast-at-call: batch-wide spelling is (s32, void *, s32). */
extern void func_80186300(s32, void *, s32);
extern void func_80188560(s32 a0, s32 a1);
extern void func_80185F1C(void);
extern void func_80185214(s32 a0);
extern void func_80184DB8(s32 a0);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_801873D8(s32 a0);
extern void func_80185D04(s32 a0);
extern void func_801823C0(void *a0);
/* §183 SIGNATURE-cast-at-call: the TU DEFINES `s32 func_80184978(s32, s32, s32)` (L5102);
   adopt that prototype and cast the buffers at the call. */
extern s32 func_80184978(s32 a0, s32 a1, s32 a2);

void func_801821E4(void *a0)
{
    u16 state;
    s16 v0;
    s32 v1;
    u16 buf1[3];
    u16 buf2[3];

    state = *(u16 *)((char *)a0 + 0x34);
    if (state == 0) {
        goto L80182214;
    }
    if (state == 1) {
        goto L801822F0;
    }
    goto L8018237C;

L80182214:
    func_80185960(0, (u16 *)((char *)(*(void **)((char *)a0 + 0x20)) + 0x12), 0x40);
    if (*(s16 *)((char *)(*(void **)((char *)a0 + 0x20)) + 0x12) != 0) {
        goto L801822C4;
    }
    if (func_80184F4C() == 0) {
        goto L801822C4;
    }
    {
        *(s16 *)((char *)a0 + 0x6) = 0x508;
        *(s16 *)((char *)a0 + 0xA) = -0x76C;
        *(s16 *)((char *)a0 + 0xE) = 0x18CD;
        func_80186300((s32)a0, (void *)D_801944E8[*(s16 *)((char *)a0 + 0xE2)].f0,
                       *(s16 *)((char *)(*(void **)((char *)a0 + 0x20)) + 0x12));
        func_80188560(aFC4C[0], D_801EFC48);
        func_80185F1C();
        *(u16 *)((char *)a0 + 0x34) = *(u16 *)((char *)a0 + 0x34) + 1;
        goto L80182378;
    }

L801822C4:
    func_80185214(*(s16 *)((char *)(*(void **)((char *)a0 + 0x20)) + 0x12));
    func_80184DB8(D_801EFD20);
    goto L8018237C;

L801822F0:
    v0 = *(s16 *)((char *)a0 + 0x98);
    if (v0 == 0) {
        goto L80182370;
    }
    if (v0 != state) {
        goto L8018237C;
    }
    v1 = *(s32 *)((char *)a0 + 0x94);
    if (v1 == 0x29) {
        *(s32 *)((char *)a0 + 0xD0) = func_8012C588(0x2B6, aFC4C[0]);
        func_8002D4C8(0x88B, 0);
        goto L8018237C;
    }
    goto L80182340;

L80182340:
    if (v1 != 0x75) {
        goto L8018237C;
    }
    {
        s32 d0 = *(s32 *)((char *)a0 + 0xD0);

        if (d0 == 0) {
            goto L80182380;
        }
        func_801873D8(d0);
        func_80185D04(1);
        goto L8018237C;
    }

L80182370:
    func_801823C0(a0);
    goto L80182378;

L80182378:
L8018237C:
L80182380:
    buf2[1] = 0x20;
    buf1[1] = 0x20;
    buf2[0] = 0;
    buf1[0] = 0;
    buf1[2] = 0;
    buf2[2] = 0x100;
    func_80184978(aFC4C[0], (s32)buf1, (s32)buf2);
}


#include "common.h"

void func_801823C0(void *a0)
{
    extern void func_8018637C(s32 arg0, s32 arg1);
    extern void func_80186BF8(void);
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern struct { s32 f0; s32 f1; s32 f2; } D_801944EC[];

    s32 s0 = (s32)a0;

    func_8018637C((s32)a0, D_801944EC[*(s16 *)(s0 + 0xE2)].f0);
    func_80186BF8();
    func_8012AD44((s32 *)s0, 0xB);
}


#include "common.h"

/* func_80182420 — 3-state entity state machine (switch on the u16 at 0x34).
 *
 * Field layout: offsets 0x1C/0x34/0x94/0x98/0xF2/0xF6 agree with this TU's own
 * `struct Ent_80181BA0` (L5265); 0x72 and 0xE2 come from this target's own loads.
 * A fresh tag name is used because Ent_80181BA0 lacks those two members. */
struct Ent_80182420 {
    /* 0x00 */ u8  pad00[0x1C];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8  pad20[0x14];
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u8  pad36[0x3C];
    /* 0x72 */ u16 unk72;
    /* 0x74 */ u8  pad74[0x20];
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s16 unk98;
    /* 0x9A */ u8  pad9A[0x48];
    /* 0xE2 */ s16 unkE2;
    /* 0xE4 */ u8  padE4[0xE];
    /* 0xF2 */ u16 unkF2;
    /* 0xF4 */ u8  padF4[0x2];
    /* 0xF6 */ s16 unkF6;
};

void func_80182420(struct Ent_80182420 *a0)
{
    /* Every decl below is the destination TU's own spelling (wave law 2):
     *   L4510 extern void func_8012AD44(s32 *a0, s16 a1);
     *   L4518 extern void func_8018637C(s32 arg0, s32 arg1);
     *   L5181 extern void func_80184CCC();          (def (s32,s32) @L7184)
     *   L5182 extern void func_80184DB8(s32 a0);
     *   L5183 extern s32  func_80184F4C();          (block (void) @L5313)
     *   L5113 extern void func_80186BD8(void);
     *   L5309 extern void func_80183CF4(void *);    (def @L6455)
     *   L5310 extern void func_80185B04(s32, s32);  (§183 call-site cast form)
     *   L5311 extern void func_80185C04(s32, s32);
     *   L5316 extern s32  func_80184884(void);      (def @L6967)
     *   L6951 extern s32  D_801EFC4C;               (scalar spelling)
     *   L4606 extern u16  D_801EFD20;
     *   L5172 extern u8   D_80194C14[];
     * func_80182630 (INCLUDE_ASM @L5578) and D_80194C3C are undeclared in the
     * TU — typed by this target's access width / argument use. */
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern void func_8018637C(s32 arg0, s32 arg1);
    extern void func_80184CCC();
    extern void func_80184DB8(s32 a0);
    extern s32 func_80184F4C(void);
    extern void func_80186BD8(void);
    extern void func_80183CF4(void *a0);
    extern void func_80185B04(s32, s32);
    extern void func_80185C04(s32, s32);
    extern s32 func_80184884(void);
    extern void func_80182630(s32 a0);
    extern void func_8018BD18(s32 a0);

    extern s32 D_801EFC4C;
    extern u16 D_801EFD20;
    extern u8 D_80194C14[];
    extern u8 D_80194C3C[];
    /* Stride-0xC record table — the TU spells the sibling table the same way
     * at L5566 (`struct { s32 f0; s32 f1; s32 f2; } D_801944EC[]`).  The
     * target's own relocation names D_801944F0, so that is what is spelled
     * here; it carries its own dlabel in asm/ov_SC04_011/data/tail.data.s. */
    extern struct { s32 f0; s32 f1; s32 f2; } D_801944F0[];

    s16 lim;
    s16 cnt;

    switch (a0->unk34) {
    case 0:
        /* §162: this arm's `func_80182630` tail is 2 insns over the cross-jump
         * floor, so gcc merges it with case 1's copy — write both longhand. */
        if ((s16)func_80184884() == 0) {
            func_80182630((s32)a0);
            break;
        }
        if (a0->unk98 != 0) {
            break;
        }
        func_8018637C((s32)a0, D_801944F0[a0->unkE2].f0);
        a0->unkF2 = 0;
        a0->unk34 = a0->unk34 + 1;
        break;
    case 1:
        if ((s16)func_80184884() == 0) {
            func_80182630((s32)a0);
            break;
        }
        if ((a0->unk72 & 0x400) && a0->unk94 == 0) {
            /* The counter store must be SEQUENCED BEFORE the clamp `if`: it is
             * what fills the `bgtz` delay slot.  With the clamp first the slot
             * goes empty and the delay-slot pass duplicates the join block's
             * `sll $v0,$a0,16` instead — +2 instructions. */
            lim = a0->unkF6 - 1;
            cnt = a0->unkF2 + 1;
            a0->unkF2 = cnt;
            if (lim <= 0) {
                lim = 1;
            }
            if (cnt == lim) {
                func_80186BD8();
                func_80184CCC((s32)a0, (s32)D_80194C3C);
                a0->unk34 = a0->unk34 + 1;
                break;
            }
        }
        if (a0->unk94 == 0xC) {
            func_8018BD18(D_801EFC4C);
        }
        break;
    case 2:
        func_80184DB8(D_801EFD20);
        if (func_80184F4C() != 0) {
            func_80184CCC((s32)a0, (s32)D_80194C14);
            func_80183CF4((void *)a0);
            func_80185B04(1, 0x20);
            func_80185C04(3, 0x30);
            func_80186BD8();
            a0->unkF2 = 0;
            a0->unk1C = a0->unkF6 * 6 + 0x10;
            func_8012AD44((s32 *)a0, 8);
        }
        break;
    }
}


void func_80182630(s32 param_1)
{
    extern s32 rand(void);
    extern void func_8018637C(s32 arg0, s32 arg1);
    extern s32 func_8018B948();
    extern void func_8018B9D4();
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern s32 D_801EFC54;
    extern void *D_80194500[];

    s32 v1;
    s32 *pp;
    s32 obj;

    v1 = *(u16 *)(param_1 + 0xE2) | (rand() & 2);
    *(u16 *)(param_1 + 0xE2) = v1;
    func_8018637C(param_1, (s32)D_80194500[(short)v1 * 3]);
    pp = &D_801EFC54;
    obj = func_8018B948(*pp);
    *(s32 *)(param_1 + 0xD0) = obj;
    if (obj != 0) {
        func_8018B9D4(*pp, obj);
        *(u16 *)(obj + 0x1A) = 0x1400;
        *(u16 *)(obj + 0x18) = 0x1400;
    }
    func_8012AD44((s32 *)param_1, 0xC);
}


extern s32 rand(void);
extern void func_80186300();
extern s32 func_8018B948();
extern void func_8018B9D4();
extern void func_8012AD44(s32 *, s16);
extern s32 D_801EFC54;
extern void *D_80194500[];

void func_801826E4(s32 param_1)
{
    s32 v1;
    s32 v0;
    s32 *pp;
    s32 obj;

    v1 = *(s32 *)(param_1 + 0x20);
    *(u16 *)(param_1 + 6) = 0x508;
    *(s16 *)(param_1 + 0xA) = -0x76C;
    *(u16 *)(param_1 + 0xE) = 0x18CD;
    *(u16 *)(param_1 + 0xE2) = 0;
    v0 = *(u16 *)(v1 + 0x12);
    if ((v0 & 0xFFF) < 0x800) {
        *(u16 *)(param_1 + 0xE2) = 1;
    }
    *(u16 *)(param_1 + 0xE2) = *(u16 *)(param_1 + 0xE2) | (rand() & 2);
    func_80186300(param_1, D_80194500[(short)*(u16 *)(param_1 + 0xE2) * 3], 0);
    pp = &D_801EFC54;
    obj = func_8018B948(*pp);
    *(s32 *)(param_1 + 0xD0) = obj;
    if (obj != 0) {
        func_8018B9D4(*pp, obj);
        *(u16 *)(obj + 0x1A) = 0x1400;
        *(u16 *)(obj + 0x18) = 0x1400;
    }
    func_8012AD44((s32 *)param_1, 0xC);
}


void func_801827DC(s32 param_1)
{
    extern void func_80186C1C(void);
    extern void func_80183F10(void);
    extern void func_8018BA9C(void);
    extern void func_80183EA8(void);
    extern void func_8018BAC4(void);
    extern void func_80182D34(s32 a0);
    extern void func_8018AC00(void *a0);
    extern void func_8012BEE8(u8 *a0);
    extern void func_8013C9C4(void *a0);
    extern void func_8018637C(s32 arg0, s32 arg1);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_8018B9D4();
    extern void func_80182AF8();
    /* §183: the TU spells D_80194500 as a flat void*[] elsewhere; reach the
       row-of-3 view through an __asm__ label alias -- the TU's own idiom. */
    extern void *a4500[][3] __asm__("D_80194500");
    extern s32 aFC4C[] __asm__("D_801EFC4C");
    extern s32 D_801EFC54;
    extern s32 D_801EFC5C;
    extern s32 D_801EFC60;
    extern s32 D_801EFC64[];
    extern s32 D_801EFC68;
    extern s32 D_801EFD28;
    extern u16 D_801EFD40;
    extern u8 D_80190B88[];
    s32 r;
    s32 obj;
    u16 t;
    u16 f;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
    case 1:
        if (*(s16 *)(param_1 + 0x98) == 0) {
            func_8018637C(param_1, (s32)a4500[*(s16 *)(param_1 + 0xE2)][*(u16 *)(param_1 + 0x34) + 1]);
            goto incr;
        }
        goto draw;
    case 2:
        if (*(s32 *)(param_1 + 0x94) != 0xB) {
            goto draw;
        }
        func_80186C1C();
        *(s16 *)(param_1 + 0x76) = 0x64;
        *(s32 *)(param_1 + 0x1C) = 0x80;
        *(s16 *)(param_1 + 0xF2) = 1;
        *(s16 *)(param_1 + 0xE2) = (s16)*(u16 *)(param_1 + 0xE2) >> 1;
        func_8013C9C4(D_80190B88);
        func_8018AC00((void *)aFC4C[0]);
        func_8018AC00((void *)D_801EFC54);
        func_8018AC00((void *)D_801EFC5C);
        func_8018AC00((void *)D_801EFC60);
        func_8018AC00((void *)D_801EFC64[0]);
        func_8018AC00((void *)D_801EFC68);
        func_8002D4C8(0x907, 0);
incr:
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
draw:
        func_8018B9D4(D_801EFC54, *(s32 *)(param_1 + 0xD0));
        return;
    case 3:
        if (*(s16 *)(param_1 + 0x76) == 0) {
            t = *(u16 *)(param_1 + 0xF6) - 1;
            *(u16 *)(param_1 + 0xF6) = t;
            *(s16 *)&D_801EFD28 = (s16)t * 100;
            func_80183F10();
            obj = *(s32 *)(param_1 + 0xD0);
            if (obj != 0) {
                *(u16 *)(obj + 0x1A) = 0x800;
                *(u16 *)(obj + 0x18) = 0x800;
            }
            func_8018BA9C();
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
            if (*(s16 *)(param_1 + 0xF6) == 0) {
                f = D_801EFD40;
                *(s32 *)(param_1 + 0x1C) = 8;
                D_801EFD40 = f | 0x100;
                return;
            }
            *(s32 *)(param_1 + 0x1C) = 0x10;
            return;
        }
        r = ((s32 (*)(s32))func_8012BEE8)((s32)param_1);
        if (r == 0) {
            if (((*(s32 *)(param_1 + 0x1C) & 0xF) == 0) && (*(s16 *)(param_1 + 0xF2) != 0)) {
                *(s16 *)(param_1 + 0xF2) = *(s16 *)(param_1 + 0xF2) - 1;
                func_8013C9C4(D_80190B88);
            }
            func_8018B9D4(D_801EFC54, *(s32 *)(param_1 + 0xD0));
            if ((*(s32 *)(param_1 + 0x1C) & 1) != 0) {
                return;
            }
            func_80183EA8();
            return;
        }
        goto L_af8;
    case 4:
        r = ((s32 (*)(s32))func_8012BEE8)((s32)param_1);
        if (r != 0) {
            if (*(s16 *)(param_1 + 0xF6) == 0) {
                func_80182D34(param_1);
                return;
            }
L_af8:
            func_80182AF8(param_1);
            return;
        }
        obj = *(s32 *)(param_1 + 0xD0);
        if (obj != 0) {
            t = *(u16 *)(obj + 0x18) + 0x600;
            *(u16 *)(obj + 0x18) = t;
            *(u16 *)(obj + 0x1A) = t;
        }
        func_8018BAC4();
        return;
    default:
        return;
    }
}


void func_80182AF8(s32 a0) {
    extern void func_80186EBC();
    extern void func_80184840();
    extern void func_80186BD8(void);
    extern void func_8018637C(s32 a0, s32 a1);
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern s32 D_80194530[];

    s32 s0 = a0;
    s32 idx;

    func_80186EBC(a0);
    func_80184840();
    func_80186BD8();
    idx = *(s16 *)(s0 + 0xE2);
    func_8018637C(s0, D_80194530[idx]);
    func_8012AD44((s32 *)s0, 0xD);
}


void func_80182B5C(void *arg0) {
    extern u8 D_80194538[];
    extern void func_8018332C(s32 a0, s32 a1);
    extern void func_80186908();
    extern u16 D_801EFD40;
    extern void func_8012AD44(s32 *a0, s16 a1);

    *(s16 *)((s32)arg0 + 0xF4) = 0;
    func_8018332C((s32)arg0, (s32)&D_80194538);
    func_80186908();
    D_801EFD40 |= 0x20;
    func_8012AD44((s32 *)arg0, 0xE);
}


#include "common.h"

/* TU (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c) already declares func_801833D4 as
   `extern void func_801833D4(int a0, int a1);` at file scope -- but this call site needs the
   return value. Match the existing decl exactly, then use the file's own established cast-call
   idiom (see func_801805D8 / func_801805F8 in the same TU) to call it as if it returned s32. */
extern void func_801833D4(int a0, int a1);
extern s32 func_80183A28(u8 *a0);
/* §183 SIGNATURE-cast-at-call: batch-wide spelling is (s32, s16 *). */
extern void func_80183564(s32 a0, s16 *a1);
extern void func_80183BD0();
extern s32 func_80186710(void);
extern void func_80186BD8(void);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 func_80188E00(s32 a0, void *a1);

extern u16 D_801EFD20;
extern u16 D_801EFD40;
extern s32 D_801EFD18;
/* §183: the TU spells these symbols differently at file scope, so reach them through
   __asm__ label ALIASES -- the TU's own established idiom (func_80188094, L6390):
   same assembler symbol, private type, zero declaration surface. */
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern u8 D_801944D0[];
extern u8 D_80194538[];

void func_80182BBC(u8 *self) {
    int state = *(u16 *)(self + 0x34);
    s32 pad[2];
    (void)pad;

    if (state < 0) {
        goto L_end;
    }
    if (state < 2) {
        goto L_BF8;
    }
    if (state == 2) {
        goto L_C44;
    }
    goto L_end;

L_BF8:
    if (((s32 (*)(int, int))func_801833D4)((int)self, 0) == 0) {
        goto L_D14;
    } else {
        register u16 f __asm__("$3") = *(u16 *)(self + 0xF4);  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t3_tus1)
        register s32 off __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)
        u8 *addr;
        f = f + 1;
        off = (s16)f * 8;
        addr = D_80194538 + off;
        *(u16 *)(self + 0xF4) = f;
        func_80183564((s32)self, (s16 *)addr);
        *(u16 *)(self + 0x34) = *(u16 *)(self + 0x34) + 1;
        goto L_end;
    }

L_C44:
    if (((s32 (*)(int, int))func_801833D4)((int)self, 0) == 0) {
        goto L_D14;
    } else {
        s32 obj;
        s32 vp;

        obj = aFC4C[D_801EFD20];
        if (!(D_801EFD40 & 0x400)) {
            D_801EFD18 = func_80188E00(obj, D_801944D0);
        }
        vp = *(s32 *)(obj + 0x20);
        *(s16 *)(obj + 6) = 0x500;
        *(s16 *)(obj + 0xA) = -0xD88;
        *(s16 *)(obj + 0xE) = 0x1980;
        *(s16 *)(vp + 0x12) = 0;
        vp = *(s32 *)(obj + 0x20);
        *(s16 *)(vp + 0x10) = 0x380;
        *(s16 *)(self + 0xFE) = 0x380;
        func_80186710();
        func_80183BD0(self);
        D_801EFD40 = D_801EFD40 & 0xFFF7;
        func_80183564((s32)self, (s16 *)D_801944D0);
        func_80186BD8();
        func_8012AD44((s32 *)self, 7);
        goto L_end;
    }

L_D14:
    func_80183A28(self);

L_end:
    return;
}


#include "common.h"

extern void func_80132EC4(s32 a0, s32 a1);
extern void func_8018637C(s32 arg0, s32 arg1);
extern void func_80186EBC();
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_800D0C48(s32 a0);
extern void func_8002AC00(s32 arg0);

extern s32 D_80194554;
extern s32 D_80194550;

void func_80182D34(s32 a0) {
    s32 s0 = a0;
    s32 v0;
    s32 v1;

    /* Load index from structure at offset 0xE2 */
    v1 = (s32)(*(s16 *)(s0 + 0xE2));

    /* Compute offset: v1 * 12 */
    v0 = v1 << 1;
    v0 = v0 + v1;
    v0 = v0 << 2;

    /* Load from D_80194554 + offset and call func_80132EC4 */
    func_80132EC4(*(s32 *)((s32)&D_80194554 + v0), 0x2);

    /* Reload index */
    v1 = (s32)(*(s16 *)(s0 + 0xE2));

    /* Compute offset again */
    v0 = v1 << 1;
    v0 = v0 + v1;
    v0 = v0 << 2;

    /* Load from D_80194550 + offset and call func_8018637C */
    func_8018637C(s0, *(s32 *)((s32)&D_80194550 + v0));

    /* Call remaining functions */
    func_80186EBC(s0);
    func_8012AD44((s32 *)s0, 0xF);
    func_800D0C48(1);
    func_8002AC00(0x18);
}


#include "common.h"

extern void func_8018637C(s32 arg0, s32 arg1);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern int func_80178970(void);
extern s32 func_8004787C(s32 a0);
extern void func_8012BEE8(u8 *a0);
extern void func_801439C0();
extern void func_8018B5E4(s32 a0);
extern void func_8018B1B4(s32 arg0);
extern void func_8018B744(s32 *a0);
extern void func_8018B2F8(s32 *a0, s32 a1);
extern void func_80185D04(s32 a0);
extern void func_80186D58(s32 a0);
extern s32 func_80186DCC(s32 a0);
extern s32 D_80194554;
extern s32 D_80194558;
extern s8 D_801945A4;
extern s32 D_801EFD18;

void func_80182DCC(s32 a0) {
    /* §183: the TU spells D_801EFC4C as a file-scope `s32[]` rename (aFC4C) and as a
     * block-scope scalar elsewhere; keep the scalar spelling LOCAL so it cannot collide
     * with the later block-scope `extern s32 D_801EFC4C[];` in this same TU. */
    extern s32 D_801EFC4C;
    s32 v0;

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (*(s16 *)(a0 + 0x98) != 0) {
            break;
        }
        v0 = (s32)(*(s16 *)(a0 + 0xE2)) * 12;
        func_8018637C(a0, *(s32 *)((s32)&D_80194554 + v0));
        *(s16 *)(a0 + 0xF2) = 0;
        *(s16 *)(a0 + 0x10A) = 0;
        func_80178B18(a0, (s32)&D_801945A4);
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        break;
    case 1:
        *(s16 *)(a0 + 0x6) = *(u16 *)(a0 + 0x6) + (func_8004787C(*(s16 *)(a0 + 0xF2)) >> 9);
        *(u16 *)(a0 + 0xF2) = *(u16 *)(a0 + 0xF2) + 0x400;
        if (*(s16 *)(a0 + 0x98) != 0) {
            break;
        }
        v0 = (s32)(*(s16 *)(a0 + 0xE2)) * 12;
        func_8018637C(a0, *(s32 *)((s32)&D_80194558 + v0));
        *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        func_8018B5E4((s32)&D_801EFC4C);
        break;
    case 2:
        if (*(s16 *)(a0 + 0x98) == 0) {
            func_80185D04(0);
            *(s32 *)(a0 + 0x1C) = 0x10;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        func_8018B744(&D_801EFC4C);
        break;
    case 3:
        if (((s32 (*)(s32))func_8012BEE8)(a0) != 0) {
            func_8018B1B4((s32)&D_801EFC4C);
            *(s32 *)(a0 + 0x1C) = 0x38;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        func_8018B744(&D_801EFC4C);
        break;
    case 4:
        func_8018B2F8(&D_801EFC4C, 0);
        func_8018B744(&D_801EFC4C);
        if (((s32 (*)(s32))func_8012BEE8)(a0) != 0) {
            *(s16 *)(a0 + 0x10A) = 1;
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    case 5:
        if (*(s16 *)(a0 + 0x10A) == 0) {
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    case 6:
        func_80186D58(a0);
        if (func_80186DCC(a0) != 0) {
            if (D_801EFD18 != 0) {
                func_801439C0(D_801EFD18);
                D_801EFD18 = 0;
            }
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
        break;
    case 7:
        break;
    }
    ((void (*)(s32))func_80178970)(a0);
}


s32 func_80183008(void) {
        return 0;
    }


s32 func_80183010(s32 *a0) {
        return *(s16 *)((s32)a0 + 0x10A);
    }





extern void func_80186C40();
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8018301C(s32 *a0)
{
    func_80186C40(a0);
    *(u16 *)((s32)a0 + 0xF2) = 0x20;
    func_8002D4C8(0x8C2, 0);
}


#include "common.h"

/* §183: the TU declares D_801EFC4C at BLOCK scope as `s32[]` further down; a FILE-scope
   scalar decl here turns those into hard errors. Reach it through the batch-wide
   __asm__ label alias instead (the TU's own idiom, func_80188094 L6390). */
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern s32 D_801EFD14;
extern s32 D_801EFD18;

/* §183 SIGNATURE-cast-at-call: the TU DEFINES `void func_8018B2F8(s32 *, s32)` (L7882). */
extern void func_8018B2F8(s32 *a0, s32 a1);
extern void func_8018B830();
extern void func_80016450(s32 a0, s32 a1);
extern void func_80189410();
extern void func_8018B8C0(void *a0);
extern s32  func_80143970(s32 a0);
extern void func_8017CC2C(void);

s32 func_80183058(s32 *a0) {
    s32 s1 = (s32)a0;
    void *s0;
    s32 frame_pad[2];
    s32 v0;
    register s32 v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t3_tus1)
    register s32 t4 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
    (void)&frame_pad;

    s0 = (void *)aFC4C;
    func_8018B2F8((s32 *)s0, 1);
    func_8018B830(s0);

    v0 = *(s16 *)(s1 + 0xF2);
    v1 = v0;
    __asm__("" : "=r"(v0) : "0"(v0));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
    if (v0 < 0x60) {
        v0 = v1 + 1;
    } else {
        v0 = v1 + 8;
    }
    *(s16 *)(s1 + 0xF2) = v0;
    __asm__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B t3_tus1)

    v0 = *(s16 *)(s1 + 0xF2);
    if (v0 >= 0x100) {
        v0 = 0xFF;
        *(s16 *)(s1 + 0xF2) = v0;
    }

    func_80016450(*(u8 *)(s1 + 0xF2), 1);

    v1 = *(s16 *)(s1 + 0xF2);
    if (v1 != 0xFF) {
        goto ret0;
    }
    t4 = D_801EFD14;
    if (t4 != 0) {
        func_80189410();
        D_801EFD14 = 0;
    }
    func_8018B8C0((void *)aFC4C);
    D_801EFD18 = func_80143970(s1);
    func_8017CC2C();
    return 1;

ret0:
    return 0;
}



void func_8018314C(s32 *a0) {
        *(s32 *)((s32)a0 + 0x1C) = 16;
        *(s16 *)((s32)a0 + 0x84) = 0;
    }


#include "common.h"

/* Declarations copied from the destination TU
 * (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c):
 *   func_80016450   : src/800.c:2073 canonical form `void func_80016450(s32 a0, s32 a1);`
 *   func_8012C218   : this TU, line 5179 `extern void func_8012C218(void *a0);`
 *   func_8001AAA0   : this TU, line 2582 declares `extern int ((int (*)(int))func_8001AAA0)(void);`
 *                      (no-arg) at file scope; our call passes an arg, so we
 *                      shadow it with a block-scope extern matching the call
 *                      shape used elsewhere in the codebase
 *                      (ov_SC03_099_jr_801588CC.c:1086 `extern int ((int (*)(int))func_8001AAA0)(int);`).
 *   func_8018BC08   : defined later in this same TU (still an INCLUDE_ASM stub
 *                      there); not declared anywhere earlier in the TU, and the
 *                      call site here passes/uses nothing, so a fresh
 *                      void(void) extern is added.
 *   func_80186CD8   : this TU, line 4963 `void func_80186CD8(s32 a0)`.
 *   D_801EFD1C      : not declared anywhere in this TU; used purely as a
 *                      pointer handed straight to func_8012C218(void *a0) and
 *                      cleared afterward, so declared as the raw pointer type.
 *
 * Struct field types on the a0 entity, cross-checked against sibling
 * functions already decompiled in this TU:
 *   +0x1C  s32  (func_8018314C: `*(s32 *)((s32)a0 + 0x1C) = 16;`)
 *   +0x84  s16  (func_8018314C: `*(s16 *)((s32)a0 + 0x84) = 0;`;
 *                func_80183010: `return *(s16 *)((s32)a0 + 0x10A);` confirms
 *                the s16 convention for this struct's short fields)
 *   +0xF2  s16  (line 4752 of this TU: `*(u16 *)(obj + 0xF2)` used in an
 *                addition — 16-bit field; the leading `lbu` here comes from
 *                an explicit narrow-cast read of its low byte, matching the
 *                existing in-TU idiom `func_80016450(*(u8 *)&D_801ED9E4, 0);`)
 *   +0x10A u16  (cleared to 0, matches func_80183010's s16 read of the same
 *                offset)
 */

extern void func_80016450(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_8018BC08(void);
extern void func_80186CD8(s32 a0);
extern void *D_801EFD1C;

s32 func_8018315C(s32 *a0) {
    s32 s0;
    s32 v0;
    register s32 v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 frame_pad[2];
    extern int func_8001AAA0(void);
    (void)&frame_pad;

    s0 = (s32)a0;

    func_80016450(*(u8 *)(s0 + 0xF2), 1);

    v0 = *(s32 *)(s0 + 0x1C);
    if (v0 != 0) {
        v0 -= 1;
        *(s32 *)(s0 + 0x1C) = v0;
        if (v0 != 0) {
            goto ret0;
        }

        func_8018BC08();

        if (D_801EFD1C != 0) {
            func_8012C218(D_801EFD1C);
            D_801EFD1C = 0;
        }

        func_80186CD8(s0);

        v0 = *(s32 *)(s0 + 0x1C);
        /* unconditional — this store shares the delay slot of the branch
         * that tests the reloaded 0x1C counter below */
        *(u16 *)(s0 + 0x10A) = 0;
        if (v0 != 0) {
            goto ret0;
        }
    }

    v0 = *(s16 *)(s0 + 0x84);
    if (v0 == 0) {
        if (((int (*)(int))func_8001AAA0)(0x68) != 0) {
            v0 = 1;
            *(s16 *)(s0 + 0x84) = v0;
        }
    }

    v0 = *(s16 *)(s0 + 0xF2);
    if (v0 != 0) {
        register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B t3_tus1)
        v1 = v0 + zr;
        v0 = v1 - 2;
        *(s16 *)(s0 + 0xF2) = v0;
        if ((s16)v0 < 0) {
            *(s16 *)(s0 + 0xF2) = 0;
        }
        v0 = *(s16 *)(s0 + 0xF2);
        if (v0 != 0) {
            goto ret0;
        }
    }

    v0 = *(s16 *)(s0 + 0x84);
    if (v0 != 0) {
        v0 = 1;
        goto ret;
    }
ret0:
    v0 = 0;
ret:
    return v0;
}


extern s16 func_80174774(void);
extern void func_80186EBC();

s32 func_80183258(s32 a0) {
    s32 v0;

    if (((s32 (*)(void))func_80174774)() != 0) {
        v0 = *(s32 *)((s32)a0 + 0x20);
        *(s32 *)(v0 + 4) |= 0x80000000;
        func_80186EBC(a0);
        return 1;
    }

    return 0;
}


extern void func_800D1724(s32 a0);
extern s32 D_80194270;

void func_801832B4(void) {
    ((void (*)(void *))func_800D1724)(&D_80194270);
}



// @class: struct
// @stuck: none — MATCH (fn-ptr table %lo-fold via extern array of code ptrs)

extern code_fn D_8019466C[];

extern s32 func_80183E20(s32 a0);

void func_801832DC(int param_1)
{
    D_8019466C[*(unsigned short *)(param_1 + 2)]();
    ((void (*)(int))func_80183E20)(param_1);
    return;
}


#include "common.h"

extern u16 D_801EFD40;
/* §183: the TU declares D_801EFC4C at BLOCK scope as `s32[]` further down; a FILE-scope
   scalar decl here turns those into hard errors. Reach it through the batch-wide
   __asm__ label alias instead (the TU's own idiom, func_80188094 L6390). */
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern u16 D_801EFD20;

extern void func_801863D4();
extern void func_801863B4(s32 a0);
extern void func_80184ABC();
/* §183 SIGNATURE-cast-at-call: batch-wide spelling is (s32, s16 *). */
extern void func_80183564();

void func_8018332C(s32 a0, s32 a1) {
    s32 v0;
    s32 s1;
    s32 s2;

    v0 = D_801EFD40;
    s1 = aFC4C[0];
    s2 = a1;

    D_801EFD20 = 0;
    v0 = v0 | 0x4;
    D_801EFD40 = (u16)v0;

    if (v0 & 0x10) {
        func_801863D4();
        func_801863B4(a0);
    }

    func_80184ABC(D_801EFD20);
    func_80183564(a0, (s16 *)s2);

    v0 = *(s32 *)(s1 + 0x20);
    v0 = *(u16 *)(v0 + 0x10);

    *(u16 *)(a0 + 0x102) = 0;
    *(u16 *)(a0 + 0x104) = 0;
    *(u16 *)(a0 + 0xFE) = (u16)v0;
}


#include "common.h"

extern u16 D_801EFD20;
extern u16 D_801EFD40;
/* §183: the TU spells these symbols differently at file scope, so reach them through
   __asm__ label ALIASES -- the TU's own established idiom (func_80188094, L6390):
   same assembler symbol, private type, zero declaration surface. */
extern s32 aFC4C[] __asm__("D_801EFC4C");

extern void func_801852BC(s32 a0);
extern void func_801853D0(s32 a0);
extern void func_80185648();
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern s32 func_80183BF0(s32 a0);
/* §183 SIGNATURE-cast-at-call: the TU DEFINES `s32 func_801836D4(void *, void *)` (L4677). */
extern s32 func_801836D4(void *a0, void *a1);
extern void func_80185960(s32 target, u16 *cur, s32 step);

/* NOTE (band verify): the destination TU (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c:4201)
   already has "extern void func_801833D4(int a0, int a1);" for this address, used only from
   func_80180714() where the return value is discarded. That decl's "void" return conflicts
   with this function's real behavior -- every path (including both early-exits) funnels into
   a shared epilogue that copies $s4 (0 or 1) into $v0 right before the jr $ra, so the true
   return type is s32. Flagging for the TU-side fix; this draft uses the byte-correct s32. */
s32 impl_801833D4(s32 a0, s32 a1) __asm__("func_801833D4");

s32 impl_801833D4(s32 a0, s32 a1)
{
    /* $a1 is call-saved across func_801852BC/func_801853D0/func_80185648 until its one use
       far below; gcc puts its param->hardreg move in the branch's delay slot rather than up
       front. A plain local didn't reproduce that ordering vs. the s4=0 init -- pin it to $19
       ($s3, its natural hardreg) so the mid-fn scheduling matches (cookbook lever B/pin). */
    register s32 r1 __asm__("$19") = a1;  // !FAKE: pin $19 — NEEDED DIFFERS (P36 rung B t3_tus1)
    u16 s0;
    s32 obj;
    s32 s4;
    /* v[2..4] is a 3-word (vel-like x/y/z) struct passed by address to func_800484EC; the
       real local apparently has 2 leading words of other data ahead of it in the frame (its
       address-taken struct forces gcc to reserve stack starting 2 words earlier than our x
       field) -- v[0]/v[1] are unused padding needed only to reproduce the frame layout. */
    s32 v[5];

    s0 = D_801EFD20;
    s4 = 0;
    obj = aFC4C[s0];

    if (D_801EFD40 & 0x4) {
        func_801852BC(s0);
        func_801853D0(s0);
        func_80185648(s0);

        v[3] = 0;
        v[2] = 0;
        if (D_801EFD40 & 0x20) {
            v[4] = 0xFFD80000;
        } else {
            v[4] = 0xFFEC0000;
        }

        func_800484EC(*(s32 *)(obj + 0x20) + 0x34, (s32)&v[2], (s32)&v[2]);

        *(s32 *)(obj + 0x4) += v[2];
        *(s32 *)(obj + 0x8) += v[3];
        *(s32 *)(obj + 0xC) += v[4];

        *(u16 *)(*(s32 *)(obj + 0x20) + 0x14) =
            *(u16 *)(*(s32 *)(obj + 0x20) + 0x14) + r1;
        func_80183BF0(a0);

        *(u16 *)(*(s32 *)(obj + 0x20) + 0x10) =
            *(u16 *)(a0 + 0xFE) + *(u16 *)(a0 + 0x102);

        if (func_801836D4((void *)a0, (void *)obj) != 0) {
            s4 = 1;
        } else {
            if (D_801EFD40 & 0x20) {
                s0 = 0x40;
            } else {
                s0 = 0x20;
            }
            func_80185960(*(s16 *)(a0 + 0x106), (u16 *)(*(s32 *)(obj + 0x20) + 0x12), s0);
            func_80185960(*(s16 *)(a0 + 0x100), (u16 *)(a0 + 0xFE), s0);
        }
    }

    return s4;
}


void func_80183564(s32 a0, s16 *a1)
{
    extern s32 func_80183A28(u8 *a0);
    extern void func_801835B0(s32 a0);

    *(u16 *)(a0 + 0xE4) = *(u16 *)(a1 + 0);
    *(u16 *)(a0 + 0xE6) = *(u16 *)(a1 + 1);
    *(u16 *)(a0 + 0xE8) = *(u16 *)(a1 + 2);
    func_80183A28((u8 *)a0);
    func_801835B0(a0);
}


/* func_801835B0 — pick the dominant axis of (self - target) into self->0xE2.
 *
 * §333: the target's frame is 0x18 with NO saved register and NO stack traffic —
 *       that is 24 bytes of DECLARED-but-unreferenced aggregate (gcc-2.7.2 slots
 *       every aggregate local in declaration order whether it is used or not).
 * §194-K: the zero-byte re-tie inside each negative arm gives `u` a second SET so
 *       cse cannot fold `(neg (subreg:SI (reg:HI u)))` back onto the pre-copy
 *       SImode load (cse.c's paradoxical-SUBREG case). Without it the three
 *       `negu $aN,$v1` read `$v0` instead — the whole 3-instruction residual.
 * §183: the TU spells D_801EFC4C as a scalar; reach the array view through an
 *       __asm__-labelled alias so no declaration conflicts.
 */
extern u16 D_801EFD20;
extern s32 aFC4C[] __asm__("D_801EFC4C");

void func_801835B0(s32 a0)
{
    s32 obj;
    s16 *p;
    s32 t;
    s16 u;
    s16 m;
    s16 c;
    s32 pad[6];                         /* §333: sets the 0x18 frame */

    obj = aFC4C[D_801EFD20];
    p = (s16 *)(a0 + 0xEC);
    if ((a0 + 0xE4) != 0) {
        *(u16 *)(a0 + 0xEC) = *(u16 *)(a0 + 0xE4) - *(u16 *)(obj + 6);
        *(u16 *)(a0 + 0xEE) = *(u16 *)(a0 + 0xE6) - *(u16 *)(obj + 0xA);
        *(u16 *)(a0 + 0xF0) = *(u16 *)(a0 + 0xE8) - *(u16 *)(obj + 0xE);
    } else {
        *(u16 *)(a0 + 0xF0) = 0;
        *(u16 *)(a0 + 0xEE) = 0;
        *(u16 *)(a0 + 0xEC) = 0;
    }
    *(u16 *)(a0 + 0xEA) = 0x1E0;

    t = p[0];
    u = t;
    if (t < 0) {
        __asm__("" : "=r"(u) : "0"(u));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
        m = -u;
    } else {
        m = u;
    }
    *(u16 *)(a0 + 0xE2) = 0;

    t = p[1];
    u = t;
    if (t < 0) {
        __asm__("" : "=r"(u) : "0"(u));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
        c = -u;
    } else {
        c = u;
    }
    if (m < c) {
        m = c;
        *(u16 *)(a0 + 0xE2) = 1;
    }

    t = p[2];
    u = t;
    if (t < 0) {
        __asm__("" : "=r"(u) : "0"(u));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
        c = -u;
    } else {
        c = u;
    }
    if (m < c) {
        *(u16 *)(a0 + 0xE2) = 2;
    }
}


#include "common.h"

/* func_801836D4 — ov_SC04_011 (second-pass repair, MATCH 60/60)
 *
 * Residual cracked (was WIDTH/hardreg-pin-defeats-sign-extend, 10/60):
 *   1) lhu-vs-lh: the "target" field must be read into an *SImode* local
 *      (s32 tw = *(s16*)...) so RTL gets (sign_extend:SI (mem:HI)) -> `lh`.
 *      Declaring it s16 makes it an HImode pseudo, whose movhi load is `lhu`.
 *      The HImode-ness the xor needs is then re-introduced by an explicit
 *      (s16) copy, NOT by the load's type.
 *   2) the missing `addu $a1,$v0,$zero`: it is the SI->HI truncating copy
 *      tw -> t16.  Unpinned, local-alloc coalesces the two pseudos and the
 *      copy vanishes; pinning tw to $2 and t16 to $5 forces it to survive.
 *   3) `xor` destination: with t16 dead after the xor, gcc reuses $a1 for the
 *      result.  A third pin (xr on $2) puts it back in $v0.
 * `xr` must stay s16 so fold narrows (diff ^ t16) to an HImode xor — that is
 * what keeps the raw `xor` + `sll 16` pair instead of an sll/sra sign-extend
 * of diff.
 */
s32 func_801836D4(void *a0, void *a1) {
    s16 buf[16];                        /* dead-store scratch: forces frame 0x28 */
    register u16 b __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t3_tus1)
    u16 a;
    s16 diff;
    s16 v1;
    register s32 tw __asm__("$2");      /* SImode -> lh */  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s16 t16;     /* HImode copy of tw -> addu $a1,$v0,$0 */
    s16 xr;      /* xor result back in $v0 */

    if (*(s16 *)((s32)a0 + 0xEA) != 0) {
        *(s16 *)((s32)a0 + 0xEA) = *(s16 *)((s32)a0 + 0xEA) - 1;
    }

    v1 = *(s16 *)((s32)a0 + 0xE2);
    switch (v1) {
    case 0:
        a = *(u16 *)((s32)a0 + 0xE4);
        b = *(u16 *)((s32)a1 + 0x6);
        diff = a - b;
        buf[0] = diff;
        tw = *(s16 *)((s32)a0 + 0xEC);
        break;
    case 1:
        a = *(u16 *)((s32)a0 + 0xE6);
        b = *(u16 *)((s32)a1 + 0xA);
        diff = a - b;
        buf[1] = diff;
        tw = *(s16 *)((s32)a0 + 0xEE);
        break;
    case 2:
        a = *(u16 *)((s32)a0 + 0xE8);
        b = *(u16 *)((s32)a1 + 0xE);
        diff = a - b;
        buf[2] = diff;
        tw = *(s16 *)((s32)a0 + 0xF0);
        break;
    default:
        goto default_case;
    }

    if (tw == 0) goto ret1;
    t16 = tw;
    if (diff == 0) goto ret1;
    xr = diff ^ t16;
    if (xr >= 0) goto default_case;
ret1:
    return 1;

default_case:
    return *(s16 *)((s32)a0 + 0xEA) == 0;
}


void func_801837C4(s32 a0, s32 a1) {
    extern u16 D_801EFD40;
    extern s32 aFC4C[] __asm__("D_801EFC4C");
    extern u16 D_801EFD20;
    extern void func_801863D4();
    extern void func_801863B4(s32 a0);
    extern void func_80184ABC();
    s32 v0;
    s32 s1;

    v0 = D_801EFD40;
    s1 = aFC4C[0];
    D_801EFD20 = 0;
    v0 |= 0x4;
    D_801EFD40 = (u16)v0;

    if (v0 & 0x10) {
        func_801863D4();
        func_801863B4(a0);
    }

    func_80184ABC(D_801EFD20);

    v0 = *(u16 *)(*(s32 *)(s1 + 0x20) + 0x10);
    *(u16 *)(a0 + 0x102) = 0;
    *(u16 *)(a0 + 0x104) = 0;
    *(u16 *)(a0 + 0xFE) = (u16)v0;

    v0 = *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12);
    *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) = v0 & 0xFFF;
    *(u16 *)(a0 + 0x106) = *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12);
}


void func_80183880(s32 a0)
{
    extern u16 D_801EFD20;
    extern u16 D_801EFD40;
    extern s32 D_801EFC4C[];
    extern void func_801852BC(s32);
    extern void func_801853D0(s32);
    extern void func_80185648();
    extern void func_800484EC(s32, s32, s32);
    extern s32 func_80183BF0(s32);
    extern void func_80185960(s32, u16 *, s32);

    u16 idx;
    s32 obj;
    s32 v[3];
    s32 step;
    s32 sub;

    idx = D_801EFD20;
    obj = D_801EFC4C[idx];

    if (D_801EFD40 & 4) {
        func_801852BC(idx);
        func_801853D0(idx);
        func_80185648(idx);

        v[1] = 0;
        v[0] = 0;
        if (D_801EFD40 & 0x20) {
            v[2] = 0xFFD80000;
        } else {
            v[2] = 0xFFEC0000;
        }

        func_800484EC(*(s32 *)(obj + 0x20) + 0x34, (s32)&v[0], (s32)&v[0]);

        *(s32 *)(obj + 0x4) += v[0];
        *(s32 *)(obj + 0x8) += v[1];
        *(s32 *)(obj + 0xC) += v[2];

        func_80183BF0(a0);

        *(u16 *)(*(s32 *)(obj + 0x20) + 0x10) =
            *(u16 *)(a0 + 0xFE) + *(u16 *)(a0 + 0x102);

        func_80185960(*(s16 *)(a0 + 0x100), (u16 *)(a0 + 0xFE), 0x20);

        if (D_801EFD40 & 0x20) {
            step = 0x40;
        } else {
            step = 0x20;
        }

        sub = *(s32 *)(obj + 0x20);

        if (*(s16 *)(sub + 0x12) < *(s16 *)(a0 + 0x106) + 0x1000) {
            *(s16 *)(sub + 0x12) += step;
            if (!(*(s16 *)(*(s32 *)(obj + 0x20) + 0x12) < *(s16 *)(a0 + 0x106) + 0x1000)) {
                *(s16 *)(*(s32 *)(obj + 0x20) + 0x12) = *(s16 *)(a0 + 0x106) + 0x2000;
            }
        } else {
            *(s16 *)(sub + 0x12) -= step;
            if (!(*(s16 *)(a0 + 0x106) + 0x1000 < *(s16 *)(*(s32 *)(obj + 0x20) + 0x12))) {
                *(s16 *)(*(s32 *)(obj + 0x20) + 0x12) = *(s16 *)(a0 + 0x106);
            }
        }
    }
}


#include "common.h"

/* Host TU (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c) already has this layout
 * via ../shared/engine_core.h -> engine_types.h as MATRIX (:1168) -- byte
 * identical. Renamed here only because match_one compiles standalone with
 * -Iinclude (engine_core.h is not on that path); on bank, drop this typedef
 * and use the TU's own MATRIX name. */
typedef struct { s16 m[3][3]; s32 t[3]; } Mtx32_80183A28; /* 0x20 bytes, align 4 */

extern u16 D_801EFD20;
/* §183: the TU spells these symbols differently at file scope, so reach them through
   __asm__ label ALIASES -- the TU's own established idiom (func_80188094, L6390):
   same assembler symbol, private type, zero declaration surface. */
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern Mtx32_80183A28 aAE620_80183A28[1] __asm__("D_800AE620");
extern void RotMatrixZ(s32 a0, void *a1);
extern void RotMatrixY(s32 a0, void *a1);
extern void func_8012F038(int param_1, short *param_2, short *param_3);
extern s32 ratan2(s32 a0, s32 a1);

s32 func_80183A28(u8 *a0) {
    Mtx32_80183A28 m;
    s16 out[4];
    void *mp;
    s32 obj;
    s32 sub;
    s32 v0;

    m = aAE620_80183A28[0];
    obj = aFC4C[D_801EFD20];
    m.t[0] = *(s16 *)(obj + 6);
    m.t[1] = *(s16 *)(obj + 0xA);
    m.t[2] = *(s16 *)(obj + 0xE);
    sub = *(s32 *)(obj + 0x20);
    mp = &m;

    RotMatrixZ(*(s16 *)(sub + 0x14), mp);
    func_8012F038((int)mp, (short *)(a0 + 0xE4), out);
    v0 = ratan2(out[2], out[0]);
    v0 = (-v0 - 0x400) & 0xFFF;
    *(s16 *)(a0 + 0x106) = v0;

    m = aAE620_80183A28[0];
    RotMatrixY(*(s16 *)(a0 + 0x106), mp);
    func_8012F038((int)mp, out, out);
    v0 = ratan2(out[2], out[1]);
    v0 = (v0 + 0x400) & 0xFFF;
    *(s16 *)(a0 + 0x100) = v0;
}


extern u16 D_801EFD40;

void func_80183BAC(u8 *a0) {
    u16 v = D_801EFD40;
    *(s16 *)(a0 + 0x104) = -0x20;
    D_801EFD40 = v | 0x40;
}


extern u16 D_801EFD40;

void func_80183BD0(s32 a0) {
    u16 f;

    f = D_801EFD40;
    *(s16 *)(a0 + 0x104) = 0;
    D_801EFD40 = f & 0xFFBF;
}


extern u16 D_801EFD40;
extern void func_80185960(s32 target, u16 *cur, s32 step);

/* NOTE (band verify): the destination TU (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c) has two
   pre-existing "extern s32 func_80183BF0(s32 a0);" decls for this address (file-scope L6237,
   and function-scope L6444 inside func_80183880), both used only as a discarded-value statement
   "func_80183BF0(a0);". That decl's `s32` return conflicts with the real behavior: no path here
   ever sets $v0 before the shared jr $ra, and -- per cookbook §162f1 -- a non-void return type
   marks $v0 live-out and BLOCKS reorg from filling the second clamp-if's branch delay slot with
   the `-0x20` constant (costs +1 insn, verified: s32 draft compiles to 34 ins vs the target's 33).
   The TU's own extern-s32 decl of THIS function is what conflicts (self_decl_tu), so per
   blast-radius law the fix stays in this draft: following the file's own established idiom for
   the mirror case (see impl_801833D4 above in this same TU, same trick, opposite direction), this
   draft defines the body under a distinct C identifier `impl_80183BF0` and binds it to the real
   assembler symbol via __asm__(). The TU's `func_80183BF0` identifier is therefore never given a
   body under that exact name in this file, so its pre-existing (wrong) s32 prototype never
   collides with our void definition -- and the emitted code is still the byte-identical 33-insn
   function (gcc: "conflicting types for 'func_80183BF0'" is what a literal `void func_80183BF0`
   definition would hit here). */
void impl_80183BF0(s32 a0) __asm__("func_80183BF0");

void impl_80183BF0(s32 a0)
{
    s16 sVar1;

    if (D_801EFD40 & 0x40) {
        sVar1 = *(s16 *)(a0 + 0x102) + *(s16 *)(a0 + 0x104);
        *(s16 *)(a0 + 0x102) = sVar1;
        if (sVar1 < -0x17F) {
            *(u16 *)(a0 + 0x104) = 0x20;
        }
        if (*(s16 *)(a0 + 0x102) >= 0x180) {
            *(s16 *)(a0 + 0x104) = -0x20;
        }
    } else {
        func_80185960(0, (u16 *)(a0 + 0x102), 0x20);
    }
}


extern void func_80185960(s32 target, u16 *cur, s32 step);
extern s32 func_8012B6D4(s16 *a0, s16 *a1);
extern u8 D_80126B5C;
extern s32 D_801EFC48;

void func_80183C74(s32 a0, u16 a1)
{
    s32 id;
    s32 v;

    v = func_8012B6D4((s16 *)(a0 + 4), (s16 *)&D_80126B5C);
    id = v & 0xFFF;
    if (id < 0x800) {
        id = (id < 0x221) ? id : 0x220;
    } else {
        if (id < 0xDE0) id = 0xDE0;
    }
    func_80185960(id, (u16 *)(*(s32 *)(D_801EFC48 + 0x20) + 0x12), a1);
}


void func_80183CF4(void *a0) {
        *(s16 *)((s32)a0 + 0x108) = 0;
        *(s16 *)((s32)a0 + 0xE2) = 0;
    }


void func_80183D00(s32 param_1)
{
    s32 obj;
    s16 v;
    u16 arr[5];
    u16 *p;
    s32 i;

    obj = *(s32 *)(param_1 + 0xCC);
    v = *(u16 *)(param_1 + 0xE2) + 0x20;
    *(s16 *)(param_1 + 0xE2) = v;
    *(s16 *)(param_1 + 0x108) = func_8004787C(v) >> 3;
    arr[4] = 0;
    i = 1;
    arr[3] = (*(s16 *)(param_1 + 0x108) / 4) * 3;
    p = &arr[1];
    arr[2] = -(((s16)*(u16 *)(param_1 + 0x108)) >> 1);
    arr[1] = *(u16 *)(param_1 + 0x108);
    do {
        func_80185A18(*(u8 *)(obj + i * 8 + 6),
                      (s16)(*(u16 *)(obj + i * 8 + 2) + *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + *p));
        p++;
        if (*(s16 *)(obj + i * 8 + 6) & 0x8000) {
            return;
        }
        i++;
    } while (i < 5);
}


extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 aFC4C[] __asm__("D_801EFC4C");

void func_80183DF8(void) {
    func_8012C588(0x2A9, aFC4C[0]);
}


/* §183/§200 DEF+DATA asm-label aliases: the TU prototypes this fn `extern s32
   func_80183E20(s32);` (L5706) and declares D_801EFD24 `extern s32` (L7727);
   both spellings conflict with the byte-true body (void(void*), u16 counter),
   so bind private identifiers to the same symbols -- zero declaration surface. */
void aF80183E20(void *a0) __asm__("func_80183E20");
void aF80183E20(void *a0) {
    extern u16 D_801EFD40;
    extern u16 aEFD24 __asm__("D_801EFD24");
    u16 flags;
    u16 cnt;
    s32 v0;
    s32 v1;
    s32 v1b;
    flags = D_801EFD40;
    if (flags & 0x80) {
        v0 = *(u16 *)((u8 *)a0 + 0x76);
        v1 = *(u16 *)((u8 *)a0 + 0x60);
        *(u16 *)((u8 *)a0 + 0x60) = 0;
        v0 = v0 - v1;
        *(u16 *)((u8 *)a0 + 0x76) = v0;
        __asm__("":::"memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B t3_tus1)
        v1b = *(s16 *)((u8 *)a0 + 0x76);
        D_801EFD40 = flags & 0xFF7F;
        if (v1b < 0) {
            *(u16 *)((u8 *)a0 + 0x76) = 0;
        }
    }
    cnt = aEFD24;
    if (cnt != 0) {
        cnt = cnt - 1;
        aEFD24 = cnt;
        if (cnt == 0) {
            func_80186AB8();
        }
    }
}


extern s32 rand(void);
extern s32 D_801EFC54;
extern void func_8018B0B0(void *a0, void *a1, void *a2, u32 a3);

void func_80183EA8(void) {
    s16 svec[4];
    s32 obj;

    obj = D_801EFC54;
    svec[0] = (rand() & 0x3F) - 0x20;
    svec[1] = 0x80;
    svec[2] = (rand() & 0x3F) - 0x20;
    func_8018B0B0((void *)obj, svec, (void *)0, 8);
}


#include "common.h"

typedef struct { s32 w[8]; } Blk32_80183F10;

extern s32 D_801EFC54;
/* §183: the TU spells these symbols differently at file scope, so reach them through
   __asm__ label ALIASES -- the TU's own established idiom (func_80188094, L6390):
   same assembler symbol, private type, zero declaration surface. */
extern Blk32_80183F10 aAE620_80183F10[1] __asm__("D_800AE620");
extern void RotMatrixY(s32 a0, void *a1);
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
/* §183 SIGNATURE-cast-at-call: the TU DEFINES
   `void func_8018B0B0(void *, void *, void *, u32)` (L7630); adopt it and cast. */
extern void func_8018B0B0(void *a0, void *a1, void *a2, u32 a3);

void func_80183F10(void)
{
    s16 svec[4];
    Blk32_80183F10 m;
    s32 vecB[4];
    s32 out[4];
    register void *mp __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B t3_tus1)
    void *op;
    void *mp2;
    void *op2;
    s32 obj;
    s32 i;
    s32 ang;

    i = 0;
    mp = &m;
    op = out;
    obj = D_801EFC54;

    svec[1] = 0x80;
    vecB[1] = 0xE0000;
    svec[0] = 0;
    svec[2] = 0;
    vecB[0] = 0;
    vecB[2] = 0xFFF20000;

    for (; i < 8; i++) {
        m = aAE620_80183F10[0];
        RotMatrixY(i << 9, mp);
        func_800484EC((s32)mp, (s32)vecB, (s32)op);
        func_8018B0B0((void *)obj, svec, op, 0x10);
    }

    mp2 = mp;
    i = 0;
    op2 = op;
    ang = 0x100;
    vecB[1] = 0x80000;
    vecB[0] = 0;
    vecB[2] = 0xFFEE0000;
    for (; i < 8; i++) {
        m = aAE620_80183F10[0];
        RotMatrixY(ang, mp2);
        func_800484EC((s32)mp2, (s32)vecB, (s32)op2);
        func_8018B0B0((void *)obj, svec, op2, 0x10);
        ang += 0x200;
    }
}


extern void func_80175454(void);
void func_801840B8(void) {
    func_80175454();
}


extern void func_80175414(s32 _arg0);
    void func_801840D8(void) {
        ((void (*)(void))func_80175414)();
    }


#include "common.h"

extern void *D_801DEC8C;

extern s32 D_80194754[];
extern u8 D_8019470C[];
extern u8 D_80194724[];
extern u8 D_801946AC[];
extern u8 D_80194348[];
extern u8 D_801947A8[];
extern u8 D_801947C0[];

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001C1E4(void *a0, s32 a1);
extern void func_80184414(void *a0);
extern void func_80185D9C(void *a0);

void func_801840F8(void *a0) {
    void *ent = a0;
    u16 n;
    s32 tbl;
    s16 *dst;
    s32 obj;

    n = *(u16 *)((s32)ent + 0x70);
    tbl = (s32)D_801DEC8C;
    dst = (s16 *)((s32)ent + 0x104);

    obj = func_8012C1B8();
    *(s32 *)((s32)ent + 0x20) = obj;
    if (obj == 0) {
        func_8012CAE4(ent);
        return;
    }

    func_8001C214(obj, D_80194754[n]);
    *(s16 *)((s32)ent + 0x102) = D_8019470C[n];

    if (D_80194724[n] != 0 && *(s32 *)((s32)ent + 0x64) != 0) {
        s32 row;

        func_8001C1E4(*(void **)((s32)ent + 0x20),
                      *(s32 *)(*(s32 *)((s32)ent + 0x64) + 0x20));
        *(u16 *)((s32)ent + 0x86) |= 8;

        row = n * 12 + tbl;
        *(s16 *)((s32)ent + 0x6) = *(u16 *)(row + 0) - *(u16 *)(row - 0xC);
        *(s16 *)((s32)ent + 0xA) = *(u16 *)(row + 2) - *(u16 *)(row - 0xA);
        *(s16 *)((s32)ent + 0xE) = *(u16 *)(row + 4) - *(u16 *)(row - 8);
        *(u16 *)(*(s32 *)((s32)ent + 0x20) + 0x10) =
            *(u16 *)(row + 6) - *(u16 *)(row - 6);
        *(u16 *)(*(s32 *)((s32)ent + 0x20) + 0x12) =
            *(u16 *)(row + 8) - *(u16 *)(row - 4);
        *(u16 *)(*(s32 *)((s32)ent + 0x20) + 0x14) =
            *(u16 *)(row + 0xA) - *(u16 *)(row - 2);
    } else {
        u16 m = n + 1;

        if (D_80194724[m] != 0) {
            m = n + 2;
        }
        if (m < 0x15) {
            s32 ra = m * 12 + tbl;
            s32 rb = n * 12 + tbl;

            dst[0] = *(u16 *)(ra + 0) - *(u16 *)(rb + 0);
            dst[1] = *(u16 *)(ra + 2) - *(u16 *)(rb + 2);
            dst[2] = *(u16 *)(ra + 4) - *(u16 *)(rb + 4);
        }

        *(s16 *)((s32)ent + 0x6) = 0;
        *(s16 *)((s32)ent + 0xA) = 0;
        *(s16 *)((s32)ent + 0xE) = 0;
        *(s32 *)((s32)ent + 0x58) =
            (s32)&D_801946AC[*(s16 *)((s32)ent + 0x102) * 16] | 0x40000000;
    }

    func_80184414(ent);
    *(u16 *)(*(s32 *)((s32)ent + 0x20) + 0x2C) |= 0x80;
    *(s32 *)(*(s32 *)((s32)ent + 0x20) + 0x80) = (s32)D_80194348;
    *(u8 *)((s32)ent + 0x75) = 0x15;

    switch (n) {
    case 0:
        *(u8 *)((s32)ent + 0xC0) = 1;
        *(s32 *)((s32)ent + 0xBC) = (s32)D_801947A8;
        *(u16 *)((s32)ent + 0x5C) = 0x8000;
        *(s32 *)((s32)ent + 0xB4) = 0;
        *(u8 *)((s32)ent + 0xC1) = 0;
        *(s16 *)((s32)ent + 0xAE) = -5;
        *(s32 *)((s32)ent + 0xC4) |= 2;
        break;
    case 2:
        *(u8 *)((s32)ent + 0xC0) = 1;
        *(s32 *)((s32)ent + 0xBC) = (s32)D_801947C0;
        *(u16 *)((s32)ent + 0x5C) = 0x8000;
        *(s32 *)((s32)ent + 0xB4) = 0;
        *(u8 *)((s32)ent + 0xC1) = 0;
        *(s32 *)((s32)ent + 0xC4) |= 2;
        *(u16 *)(*(s32 *)((s32)ent + 0x20) + 0x2C) |= 0x10;
        *(s16 *)((s32)ent + 0xAE) = -1;
        break;
    default:
        *(s16 *)((s32)ent + 0xAE) = -1;
        *(u16 *)((s32)ent + 0x5C) = 0xC000;
        break;
    }

    func_80185D9C(ent);
}


#include "common.h"

extern void func_80185FF4(void *a0);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_80184414(void *a0)
{
    if (*(s16 *)((s32)a0 + 0x70) == 1) {
        func_80185FF4(a0);
    }
    func_8012AD44((s32 *)a0, 1);
}


#include "common.h"

extern void *D_801947D8[];
extern u16 D_801EFD40;

void func_8018445C(s32 a0) {
    s32 *s0 = (s32 *)a0;
    s32 v0_idx;

    // Load u16 from offset 0x2, multiply by 4 for array index
    v0_idx = *(u16 *)((u8 *)s0 + 0x2);
    ((void (*)(void))D_801947D8[v0_idx])();

    // Check if D_801EFD40 bit 0x8 is set - if yes, jump to set_bit
    if ((D_801EFD40 & 0x8) != 0) {
        goto set_bit;
    }

    // Check if *(u16*)(s0+0x86) bit 0x10 is set
    if ((*(u16 *)((u8 *)s0 + 0x86) & 0x10) == 0) {
        goto clear_bit;
    }

set_bit:
    {
        s32 *v0 = *(s32 **)((u8 *)s0 + 0x20);
        s32 v1 = *(s32 *)((u8 *)v0 + 0x4);
        v1 |= 0x80000000;
        *(s32 *)((u8 *)v0 + 0x4) = v1;
    }
    return;

clear_bit:
    {
        s32 *a0 = *(s32 **)((u8 *)s0 + 0x20);
        s32 v0 = *(s32 *)((u8 *)a0 + 0x4);
        s32 v1 = 0x7FFFFFFF;
        v0 &= v1;
        *(s32 *)((u8 *)a0 + 0x4) = v0;
    }
}


extern s32 D_801EFC54;
extern void func_80186940(void *a0, s32 a1, s32 a2);

void func_80184504(void *arg0)
{
    s32 tbl;
    s16 diff;

    tbl = D_801EFC54;
    *(u8 *)((s32)arg0 + 0xC1) = 1;
    *(s32 *)((s32)arg0 + 0x1C) = 4;
    *(u16 *)((s32)arg0 + 0x5C) &= ~1;
    diff = *(s16 *)((s32)arg0 + 0x76);
    if (diff != 0) {
        diff = diff - *(u16 *)((s32)arg0 + 0x60);
        *(s16 *)((s32)arg0 + 0x76) = diff;
        if (diff < 0) {
            *(s16 *)((s32)arg0 + 0x76) = 0;
        }
        *(s16 *)(*(s32 *)(tbl + 0x20) + 0x18) =
        *(s16 *)(*(s32 *)(tbl + 0x20) + 0x1A) =
        *(s16 *)(*(s32 *)(tbl + 0x20) + 0x1C) =
            0x1000 - (0x240 - *(s16 *)((s32)arg0 + 0x76)) * 3;
    }
    func_80186940(arg0, *(s16 *)((s32)arg0 + 0x60), 1);
}


#include "common.h"

extern void func_8012BEE8(u8*);
extern void func_80185DDC(void *a0);
extern void func_80186020(void *a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8018489C();

extern s32 D_801EFC48;
extern u16 D_801EFD40;

void func_801845A8(void *a0)
{
    s32 v0;
    s32 p;

    if (((s32 (*)(s32))func_8012BEE8)((s32)a0) != 0) {
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(s16 *)((s32)a0 + 0x5E) = 0;
    }

    func_80185DDC(a0);

    if (*(s16 *)((s32)a0 + 0x70) == 1) {
        func_80186020(a0);
    }

    if (!(*(u16 *)((s32)a0 + 0x86) & 0x10)) {
        if (!(D_801EFD40 & 0x4)) {
            v0 = D_801EFC48;
            p = *(s32 *)((s32)a0 + 0x20);
            *(s16 *)((s32)a0 + 0xE) = 0;
            *(s16 *)((s32)a0 + 0xA) = 0;
            *(s16 *)((s32)a0 + 0x6) = 0;
            *(s16 *)(p + 0x14) = 0;
            *(s16 *)(p + 0x12) = 0;
            *(s16 *)(p + 0x10) = 0;
            func_80132784((s32)a0, v0, *(u16 *)((s32)a0 + 0x70));
        }

        if (*(s16 *)((s32)a0 + 0x70) == 0 || *(s16 *)((s32)a0 + 0x70) == 2) {
            if (D_801EFD40 & 0x1000) {
                func_8018489C(a0, 0x30, -0x20);
                func_8018489C(a0, 0x30, 0x20);
            } else {
                func_8018489C(a0, 0x30, 0);
            }
        } else {
            func_8018489C(a0, 0x24, 0);
        }
    }
}


extern void func_80186940(void *a0, s32 a1, s32 a2);
extern void func_8016B3F4(s32 a0);
extern void func_80186BD8(void);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801846C0(void *arg0)
{
    *(u8 *)((s32)arg0 + 0xC1) = 1;
    *(u16 *)((s32)arg0 + 0x5C) &= ~1;
    *(s32 *)((s32)arg0 + 0x1C) = 8;
    func_80186940(arg0, 100, 1);
    func_8016B3F4((s32)arg0);
    func_80186BD8();
    func_8002D4C8(0xB36, 0);
}


#include "common.h"

extern void func_8012BEE8(u8*);
extern void func_80185DDC(void*);
extern void func_80186020(void*);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8018489C();

void func_80184728(void *a0) {

    extern u16 D_801EFD40;
    extern s32 D_801EFC48;
    void *s0;
    void *ptr;
    s32 ret;
    s16 v1;
    u16 v0;

    ret = ((s32 (*)(s32))func_8012BEE8)((s32)a0);
    s0 = a0;
    if (ret != 0) {
        *(u8 *)((s32)s0 + 0xC1) = 0;
        *(s16 *)((s32)s0 + 0x5E) = 0;
    }

    ((void (*)(s32))func_80185DDC)((s32)s0);

    v1 = *(s16 *)((s32)s0 + 0x70);
    if (v1 == 1) {
        ((void (*)(s32))func_80186020)((s32)s0);
    }

    v0 = *(u16 *)((s32)s0 + 0x86);
    if (!(v0 & 0x10)) {
        if (!(D_801EFD40 & 0x4)) {
            s32 tmp = D_801EFC48;
            ptr = *(void **)((s32)s0 + 0x20);
            *(s16 *)((s32)s0 + 0xE) = 0;
            *(s16 *)((s32)s0 + 0xA) = 0;
            *(s16 *)((s32)s0 + 0x6) = 0;
            *(s16 *)((s32)ptr + 0x14) = 0;
            *(s16 *)((s32)ptr + 0x12) = 0;
            *(s16 *)((s32)ptr + 0x10) = 0;
            func_80132784((s32)s0, tmp, *(u16 *)((s32)s0 + 0x70));
        }

        v1 = *(s16 *)((s32)s0 + 0x70);
        if (v1 == 0 || v1 == 2) {
            if (D_801EFD40 & 0x1000) {
                ((void (*)(s32, s32, s32))func_8018489C)((s32)s0, 0x30, -0x20);
                ((void (*)(s32, s32, s32))func_8018489C)((s32)s0, 0x30, 0x20);
            } else {
                ((void (*)(s32, s32, s32))func_8018489C)((s32)s0, 0x30, 0);
            }
        } else {
            ((void (*)(s32, s32, s32))func_8018489C)((s32)s0, 0x24, 0);
        }
    }
}


void func_80184840(void) {
    extern s32 D_801EFC48;
    extern s32 D_801EFC4C;
    extern s32 D_801EFC54;
    s32 p;
    s32 obj;

    p = D_801EFC4C;
    *(s16 *)(p + 0x76) = 0x240;
    *(s16 *)(D_801EFC48 + 0x76) = 0x1000;
    p = D_801EFC54;
    obj = *(s32 *)(p + 0x20);
    *(s16 *)(obj + 0x1C) = 0x1000;
    *(s16 *)(obj + 0x1A) = 0x1000;
    *(s16 *)(obj + 0x18) = 0x1000;
}


s32 func_80184884(void) {
    extern s32 D_801EFC4C;
    return *(s16 *)(D_801EFC4C + 0x76);
}


/* func_8018489C — ov_SC04_011 (split ov_SC04_011_jr_8017D494), 55 ins, match_one MATCH.
 *
 * Guarded "nudge the entity three ways" helper: under the D_801EFD24 / D_801EFD40&0x100
 * gate it fills two 3-halfword stack vectors from the 16-byte D_801946AC record selected by
 * *(s16 *)(arg0+0x102), then calls func_80184978 with dx = -arg1, then 0, then +arg1,
 * stopping at the first call that returns non-zero.
 *
 * THE TWO LEVERS (both zero-byte; the naive body is `near 4`, OPCODE-MIXED):
 *
 *  1. `-arg1` READS THE INCOMING $a1, NOT THE $s2 PARAMETER COPY (`negu $a3,$a1`).  Spelling
 *     it `-arg1` negates the parameter pseudo, which lives across the three calls and is
 *     therefore in $s2 -> `negu $a3,$s2`, and with no register WAR edge the negu is free to
 *     float: gcc's birthing boost (sched.c adjust_priority/birthing_insn_p) sinks it to just
 *     above its two `sh` consumers, 11 slots too late.  Reading the raw argument register
 *     through an uninitialised `register s32 a1v __asm__("$5")` gives BOTH halves at once —
 *     the right source register AND a REG_DEP_ANTI against `addiu $a1,$sp,0x10`, which is
 *     what pins the negu to the head of the block (where dbr then steals it into the
 *     `bnez ...,0x100` delay slot).
 *
 *  2. THE SYMBOL BASE MUST BE A MULTI-SET REGISTER, ELSE ITS BIRTHING BOOST OUTRANKS THE
 *     CALL'S ARGUMENT SETUP.  `p = D_801946AC + idx*16;` puts the `la` in a single-set pseudo,
 *     so at sched1 it carries priority 0x7f000001 and is picked before the (priority-1)
 *     `addiu $a1,$sp,0x10`; sched1's output order IS sched2's LUID, so at sched2 the `la`
 *     keeps winning the tie and lands BELOW the arg setup — target has it above.  Binding the
 *     base to $v0 with `register u8 *base __asm__("$2")` kills the boost for free, because
 *     reg_n_sets[$v0] already counts the three `jal` return values (>1 => birthing_insn_p
 *     returns 0) — and $v0 is exactly the register the target materialises the symbol in.
 *     (A plain multi-set `p = D_801946AC; p += idx*16;` also kills the boost and fixes the
 *     schedule, but then `p` owns the symbol's register too: REGALLOC-PERM $v0<->$v1, near 5.)
 *
 * §183 DATA asm-label alias: this TU declares D_801EFD24 `extern s32` at file scope (L9135)
 * while the byte-true body reads it with `lhu`; bind a private identifier to the symbol, the
 * TU's own idiom for this exact global (aF80183E20, L7272).
 */

extern s32 func_80184978(s32 a0, s32 a1, s32 a2);

void func_8018489C(s32 arg0, s32 arg1, s32 arg2)
{
    extern u16 aEFD24 __asm__("D_801EFD24");

    s32 z;        /* arg2, kept in the caller-saved $t0 */
    register s32 a1v __asm__("$5");      /* the INCOMING $a1, i.e. arg1 pre-copy — lever 1 */  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)
    register u8 *base __asm__("$2");     /* multi-set home for the symbol — lever 2 */  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s16 sp10[3];
    s16 sp18[3];
    u8 *p;

    if (aEFD24 == 0 && !(D_801EFD40 & 0x100)) {
        z = arg2;
        base = D_801946AC;
        p = base + *(s16 *)(arg0 + 0x102) * 16;
        sp10[2] = *(u16 *)(p + 12);
        sp18[2] = *(u16 *)(p + 14);
        sp18[1] = z;
        sp10[1] = z;
        sp18[0] = -a1v;
        sp10[0] = -a1v;
        if (func_80184978(arg0, (s32)sp10, (s32)sp18) == 0) {
            sp18[0] = 0;
            sp10[0] = 0;
            if (func_80184978(arg0, (s32)sp10, (s32)sp18) == 0) {
                sp18[0] = arg1;
                sp10[0] = arg1;
                func_80184978(arg0, (s32)sp10, (s32)sp18);
            }
        }
    }
}


#include "common.h"

/* func_80184978 — ov_SC04_011 (split ov_SC04_011_jr_8017D494), 81 ins, MATCH.
 *
 * Second-pass repair of a NEAR(3) draft.  The first pass had the whole structure right
 * (two func_8012F214 out-param fills into stack Pt-structs, a func_80135888 gate, a
 * D_801EFD40 bit tree picking 0x28/0x50/0x40 for $a3, then a D_801EFD40&0x200 split with
 * two func_8012F568 calls) and had already found the `u8 *outp = D_80126B58;` lever that
 * frees $s0 for the &D_80126B58 base.  Residual was exactly THREE target `nop`s our
 * compile filled with useful work.  Both remaining levers are sched-pass attributions, not
 * "unsteerable scheduler priority":
 *
 *   1. DEFAULT-THEN-OVERRIDE for the $a3 constant (sched.md S1 / cookbook §31 statement
 *      order = schedule).  The target's first `beqz` delay slot holds `addiu $a3,$zero,0x28`
 *      and the SECOND branch's slot is a bare `nop`.  That is the shape of
 *          code = 0x28;  if (f & 0x800) code = 0x50;  else if (f & 0x1000) code = 0x40;
 *      — the unconditional `code = 0x28` DOMINATES the branch, so dbr backward-fills the
 *      first slot with it and the `andi 0x1000` stays put (nothing left for slot 2).
 *      Writing 0x28 as the trailing `else` (the first pass's form) makes the andi the only
 *      backward candidate: it steals slot 1 and the `li 0x28` steals slot 2.  -1 nop.
 *
 *   2. THE TWO func_8012F568 CALL SETUPS = a **sched2** hoist, byte-attributed with
 *      `-fno-schedule-insns2` (sched.md S10: that one flag alone took the diff from 35 to
 *      the 4 prologue-weave insns sched2 legitimately owns, i.e. sched1 ALREADY emits the
 *      target's `li $a1 / lw / nop / lh` order).  Post-reload sched2 then hoists
 *      `lw $v0,0x20($s1)` above `li $a1,<msg>` so the constant wedges into the load-delay
 *      gap (S4: the gap exists iff an independent insn is READY at that tick).  The fix is
 *      to make the two arg constants NOT be ready there — materialise $a0/$a1 BEFORE the
 *      load with `register __asm__` pins and fence the load behind a zero-byte
 *      `__asm__ __volatile__("" ::: "memory")`.  The `li $a0,1` stays the head of the
 *      thread so dbr still steals it into the `beqz` delay slot (and still elides the copy
 *      in the other arm); `li $a1` is now above the fence, so the `lw` cannot climb past
 *      it and its delay slot stays the target's bare `nop`.  -2 nops.
 *      (Pins are safe here — the §42e "pin SIGABRTs sibling TUs" verdict was corrected to a
 *      staging/extract_unit bug; these are plain arg-register pins confined to one arm.)
 *      Byte-measured ladder: barrier alone 5 off; pin $a1 only 37 off; pins + plain
 *      volatile asm (no "memory") 5 off; pins + "memory" clobber = MATCH.
 */

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_8012F568();
extern u16  D_801EFD40;
extern u8   D_801152A8[];

s32 func_80184978(s32 arg0, s32 arg1, s32 arg2)
{
    /* [T51/§103] scoped in: func_8012B8A4 has no decl in this TU yet, and a file-scope one
       would constrain every later function here.  Type copied from the canonical form used
       by every other overlay TU (`extern s32 func_8012B8A4(s16 *a0);`). */
    extern s32  func_8012B8A4(s16 *a0);
    extern s32 *D_80126B78;
    extern s32 *D_80126B90;
    extern u8   D_80126B58[];

    struct { u16 x, y, z, w; } a;
    struct { u16 x, y, z, w; } b;
    u8 *outp;
    u16 flags;
    s32 code;
    s32 v0;

    func_8012F214(arg0, arg1, &a);
    func_8012F214(arg0, arg2, &b);
    /* hoisted base pointer (NOT a pre-added +0x42 one — that folds the offset into the
       LUI/ADDIU and drops the `sh 0x42($s0)` immediate); lets $s0 be reused after its last
       &b use exactly like the target. */
    outp = D_80126B58;

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&a, (s32)&b) != 0) {
        flags = D_801EFD40;
        code = 0x28;                       /* lever 1: default-then-override, see header */
        if (flags & 0x800) {
            code = 0x50;
        } else if (flags & 0x1000) {
            code = 0x40;
        }

        if (D_801EFD40 & 0x200) {
            register s32 m0 __asm__("$4");  /* lever 2: materialise the arg constants */  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
            register s32 m1 __asm__("$5");  /* above the fence, see header */  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)
            s16 fld;
            m0 = 1;
            m1 = 0x4017;
            __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B t3_tus1)
            fld = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
            func_8012F568(m0, m1, fld, code, &b, D_801152A8);
            v0 = func_8012B8A4((s16 *)arg0);
            v0 = (v0 + 0x200) & 0xFFF;
            if (v0 < 0x800) {
                *(s16 *)(outp + 0x42) = 0x200;
            } else {
                *(s16 *)(outp + 0x42) = 0xA00;
            }
        } else {
            register s32 m0 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
            register s32 m1 __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)
            s16 fld;
            m0 = 1;
            m1 = 0x4013;
            __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B t3_tus1)
            fld = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
            func_8012F568(m0, m1, fld, code, &b, D_801152A8);
        }
        return 1;
    }
    return 0;
}


void func_80184ABC(s32 a0)
{
    extern s32 D_801EFC4C;
    extern u8 D_80194724[];
    extern void func_80184B3C();

    s32 i;
    s32 *p;

    if ((u32)a0 < 0x14) {
        i = a0 + 1;
        if (i < 0x15) {
            s32 base;

            base = (s32)((s32 *)&D_801EFC4C);
            p = (s32 *)(base + i * 4);
            do {
                if (D_80194724[i] == 0) {
                    func_80184B3C(*p);
                }
                i++;
                p++;
            } while (i < 0x15);
        }
    }
}


void func_80184B3C(void *a0)
{
    s16 *wp = (s16 *)((s32)a0 + 0xE4);
    s32 i;

    if (*(u8 *)((s32)a0 + 0x10A) != 1) {
        for (i = 0; i < 4; i++) {
            *wp++ = *(u16 *)((s32)(*(void **)((s32)a0 + 0x20)) + 0x10);
            *wp++ = *(u16 *)((s32)(*(void **)((s32)a0 + 0x20)) + 0x12);
            *wp++ = *(u16 *)((s32)(*(void **)((s32)a0 + 0x20)) + 0x14);
        }
        *(u8 *)((s32)a0 + 0x10B) = 0;
        *(u8 *)((s32)a0 + 0x10A) = 1;
    }
}


#include "common.h"

extern u16 D_801EFD40;
extern void func_80185960(s32 target, u16 *cur, s32 step);

void func_80184BAC(void *a0, void *a1)
{
    u8 idx;
    s16 *wp;
    u16 step;
    s32 mask;
    register s32 off __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    u16 flag;

    idx = *(u8 *)((s32)a0 + 0x10B);
    flag = D_801EFD40;
    off = idx * 6 + 0xE4;
    wp = (s16 *)((s32)a0 + off);

    if (flag & 0x20) {
        step = 0x80;
        mask = 1;
    } else {
        step = 0x40;
        mask = 3;
    }

    func_80185960(wp[0], (u16 *)((s32)(*(void **)((s32)a0 + 0x20)) + 0x10), step);
    func_80185960(wp[1], (u16 *)((s32)(*(void **)((s32)a0 + 0x20)) + 0x12), step);
    func_80185960(wp[2], (u16 *)((s32)(*(void **)((s32)a0 + 0x20)) + 0x14), step);

    *(u8 *)((s32)a0 + 0x10B) = mask & (idx + 1);

    off = idx * 6 + 0xE4;
    wp = (s16 *)((s32)a0 + off);

    wp[0] = *(u16 *)((s32)(*(void **)((s32)a1 + 0x20)) + 0x10);
    wp[1] = *(u16 *)((s32)(*(void **)((s32)a1 + 0x20)) + 0x12);
    wp[2] = *(u16 *)((s32)(*(void **)((s32)a1 + 0x20)) + 0x14);
}


#include "common.h"

extern u16 D_801EFD40;
extern s16 D_801EFD30[];
extern u8 D_80194724[];
extern u16 D_801EFD3C;

extern void func_80186470(void *);
extern void func_801863B4(s32 a0);
extern void func_80185FAC(void);
extern void func_801859E4(s32, u16*);

void func_80184CCC(s32 a0, s32 a1) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;

    s2 = a1;

    D_801EFD40 = D_801EFD40 | 4;

    if (D_801EFD40 & 0x10) {
        func_80186470((void *)a0);
        func_801863B4(a0);
    }

    func_80185FAC();
    s1 = 0;
    s0 = a0;
    *(s32 *)(s0 + 0xCC) = s2;
    s0 = s2 + 6;
    s3 = (s32)&D_801EFD30[0];

    while (s1 < 5) {
        s32 c = *(u8 *)s0;
        if (c < 0x15 && D_80194724[c] == 0) {
            *(u16 *)s3 = (u16)c;
            ((void (*)(s32, s32))func_801859E4)(c, s2);
            s3 += 2;
            s1++;
        }
        if (*(s16 *)s0 & 0x8000) {
            break;
        }
        s0 += 8;
        s2 += 8;
    }

    D_801EFD3C = (u16)s1;
}


#include "common.h"

extern u16 D_801EFD3C;
extern s16 D_801EFD30[];
/* §183: the TU spells these symbols differently at file scope, so reach them through
   __asm__ label ALIASES -- the TU's own established idiom (func_80188094, L6390):
   same assembler symbol, private type, zero declaration surface. */
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern u16 D_801EFD40;

extern void func_801858DC(void *a0);
extern void func_80185020(s32 a0, s32 a1);
extern void func_8018681C(s32 a0, void *a1);
/* §183 SIGNATURE-cast-at-call: these three take s32 elsewhere in the batch/TU; adopt that
   prototype and cast at the call (byte-identical). */
extern void func_801852BC(s32 a0);
extern void func_801853D0(s32 a0);
extern void func_80185648();

/* §183 DEF-side: the TU declares `extern void func_80184DB8(s32 a0);` at file scope (L4350),
   so the definition adopts s32. */
void func_80184DB8(s32 a0) {
    s32 i;
    register s32 obj __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
    u16 buf[3];

    for (i = 0; i < D_801EFD3C; i++) {
        func_801858DC((void *)aFC4C[D_801EFD30[i]]);
    }

    for (i = 0; i < D_801EFD3C - 1; i++) {
        func_80185020(D_801EFD30[i], D_801EFD30[i + 1]);
    }

    if (D_801EFD30[i] < 0x13) {
        obj = aFC4C[D_801EFD30[i]];
        buf[0] = *(u16 *)(*(s32 *)(obj + 0x20) + 0x10);
        buf[1] = *(u16 *)(*(s32 *)(obj + 0x20) + 0x12);
        buf[2] = *(u16 *)(*(s32 *)(obj + 0x20) + 0x14);
        func_8018681C(D_801EFD30[i], buf);
    }

    if (D_801EFD40 & 4) {
        func_801852BC(a0);
        func_801853D0(a0);
        func_80185648(a0);
    }
}


extern s16 D_801EFD30[];
extern u16 D_801EFD3C;
extern s32 func_80184FC4(s32 arg0);

s32 func_80184F4C(void) {
    s32 i;
    s32 ok;

    ok = 1;
    for (i = 0; i < D_801EFD3C; i++) {
        ok = ok & func_80184FC4(D_801EFD30[i]);
    }
    return ok;
}


extern s32 aFC4C[] __asm__("D_801EFC4C");

s32 func_80184FC4(s32 idx) {
    s32 obj;
    s32 sub;

    obj = aFC4C[idx];
    sub = *(s32 *)(obj + 0x20);
    if (*(s16 *)(sub + 0x10) != *(s16 *)(obj + 0xE4) ||
        *(s16 *)(sub + 0x12) != *(s16 *)(obj + 0xE6)) {
        return 0;
    }
    return *(s16 *)(sub + 0x14) == *(s16 *)(obj + 0xE8);
}


#include "common.h"

void func_80185020(s32 start, s32 end)
{
    /* Block-scope decls (cookbook §103 / the TU's own [T51] convention): this TU already
       carries a file-scope `extern s32 D_801EFC4C;` further down, so a file-scope array
       decl here would conflict. func_80185B5C/func_80185C5C use exactly this spelling. */
    extern u8 D_80194724[];
    extern s32 D_801EFC4C[];
    u32 i;
    s32 n;
    s32 ep;
    s32 sp;
    s32 d;
    s32 x, y, z;
    s32 dx, dy, dz;
    s32 o;

    n = 0;
    for (i = start + 1; i < end; i++) {
        if (D_80194724[i] == 0) {
            n++;
        }
    }
    if (n == 0) {
        return;
    }

    sp = *(s32 *)(D_801EFC4C[start] + 0x20);
    ep = *(s32 *)(D_801EFC4C[end] + 0x20);

    d = (*(s16 *)(ep + 0x10) - *(s16 *)(sp + 0x10)) & 0xFFF;
    if (d >= 0x800) {
        d -= 0x1000;
    }
    dx = (d << 16) / (n + 1);

    d = (*(s16 *)(ep + 0x12) - *(s16 *)(sp + 0x12)) & 0xFFF;
    if (d >= 0x800) {
        d -= 0x1000;
    }
    dy = (d << 16) / (n + 1);

    d = (*(s16 *)(ep + 0x14) - *(s16 *)(sp + 0x14)) & 0xFFF;
    if (d >= 0x800) {
        d -= 0x1000;
    }
    dz = (d << 16) / (n + 1);

    x = *(s16 *)(sp + 0x10) << 16;
    y = *(s16 *)(sp + 0x12) << 16;
    z = *(s16 *)(sp + 0x14) << 16;

    for (i = start + 1; i < end; i++) {
        if (D_80194724[i] == 0) {
            x += dx;
            y += dy;
            z += dz;
            o = D_801EFC4C[i];
            *(s16 *)(*(s32 *)(o + 0x20) + 0x10) = x >> 16;
            *(s16 *)(*(s32 *)(o + 0x20) + 0x12) = y >> 16;
            *(s16 *)(*(s32 *)(o + 0x20) + 0x14) = z >> 16;
        }
    }
}


#include "common.h"

void func_80185214(s32 a0)
{
    extern s32 D_801EFC48;
    extern u8 D_80194724[];
    extern void func_80185A18(s32 idx, s32 val);
    register s32 s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 s1;
    s32 s2;
    s32 c;

    s2 = a0;
    s0 = *(s32 *)(D_801EFC48 + 0xCC);
    s1 = s0 + 0x28;
    do {
        c = *(u8 *)(s0 + 6);
        if (c < 0x15 && D_80194724[c] == 0) {
            func_80185A18(c, (s16)(*(u16 *)(s0 + 2) + s2));
        }
        if (*(s16 *)(s0 + 6) & 0x8000) {
            break;
        }
        s0 += 8;
    } while (s0 < s1);
}


#include "common.h"

/* §183: the TU declares D_801EFC4C at file scope as a SCALAR (`extern s32 D_801EFC4C;`).
   Reach it through an __asm__ label ALIAS -- the TU's own established idiom (func_80188094,
   L6390) -- so this array view can never collide with the file's spelling. Same assembler
   symbol, zero declaration surface. */
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern void func_80049CAC(s32 a0, s32 a1);

typedef struct {
    s32 a, b, c, d, e, f, g, h;
} Oct_801852BC;

void func_801852BC(s32 id)
{
    s32 obj;
    Oct_801852BC mtx;

    obj = aFC4C[id];
    func_80049CAC(*(s32 *)(obj + 0x20) + 0x10, (s32)&mtx);

    mtx.f = *(s16 *)(obj + 0x6);
    mtx.g = *(s16 *)(obj + 0xA);
    mtx.h = *(s16 *)(obj + 0xE);

    *(Oct_801852BC *)(*(s32 *)(obj + 0x20) + 0x34) = mtx;
    *(Oct_801852BC *)(*(s32 *)(obj + 0x20) + 0x54) = mtx;

    *(s32 *)(*(s32 *)(obj + 0x20) + 0x30) = 1;

    *(u16 *)(*(s32 *)(obj + 0x20) + 0x2C) |= 1;
}


#include "common.h"

extern s32 aFC4C[] __asm__("D_801EFC4C");
extern u8 D_80194724[];
extern u8 D_80194725[];

extern void func_80049CAC(s32 a0, s32 a1);







typedef struct {
    s32 w[8];
} Oct_801853D0;

void func_801853D0(s32 id)
{
    s32 l[16];
    s32 obj;
    s32 obj2;
    s16 t;
    s32 i;

    if ((id != 0) && ((u32)id < 0x15)) {
        for (i = id - 1; i >= 0; i--) {
            if (D_80194724[i] == 0) {
                obj = aFC4C[i];
                obj2 = D_80194725[i] ? aFC4C[i + 2] : aFC4C[i + 1];

                func_80049CAC(*(s32 *)(obj + 0x20) + 0x10, (s32)l);
                gte_SetTransMatrix((void *)(*(s32 *)(obj2 + 0x20) + 0x34));
                gte_SetRotMatrix((void *)l);

                *(s16 *)((s32)l + 0x20) = -*(u16 *)(obj + 0x104);
                *(s16 *)((s32)l + 0x22) = -*(u16 *)(obj + 0x106);
                *(s16 *)((s32)l + 0x24) = -*(u16 *)(obj + 0x108);

                gte_ldv0((s32)l + 0x20);
                gte_rtv0tr();
                gte_stlvnl((s32)l + 0x28);
                gte_stflg((s32)l + 0x38);

                t = l[10];
                *(s16 *)(obj + 6) = t;
                l[5] = t;
                t = l[11];
                *(s16 *)(obj + 0xA) = t;
                l[6] = t;
                t = l[12];
                *(s16 *)(obj + 0xE) = t;
                l[7] = t;

                *(Oct_801853D0 *)(*(s32 *)(obj + 0x20) + 0x34) = *(Oct_801853D0 *)l;
                *(Oct_801853D0 *)(*(s32 *)(obj + 0x20) + 0x54) = *(Oct_801853D0 *)l;

                *(s32 *)(*(s32 *)(obj + 0x20) + 0x30) = 1;
                *(u16 *)(*(s32 *)(obj + 0x20) + 0x2C) |= 1;
            }
        }
    }
}



typedef struct { s32 a, b, c, d, e, f, g, h; } MTX8_80185648;

void func_80185648(u32 a0)
{
    extern s32 aFC4C[] __asm__("D_801EFC4C");
    extern u8 D_80194724[];
    extern u8 D_80194723[];
    extern void func_80049CAC(s32, s32);
    extern void func_80184BAC(void *, void *);
    extern void func_801858DC(void *);

    s32 pad[8];   /* dead 0x20 slot — reproduces the target's frame gap */
    MTX8_80185648 m;
    s32 r[3];
    s32 flag;
    s32 w0, w1, w2, sh, c;
    register s32 t __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    register s32 s5 __asm__("$21");  // !FAKE: pin $21 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 s6;

    if (a0 >= 0x14) return;
    s2 = a0 + 1;
    if (s2 >= 0x15) return;
    s4 = 1;
    s5 = (s32)&aFC4C[0];
    s6 = s5 - 4;
    t = s2 << 2;
    s3 = t + s5;

    do {
        if (D_80194724[s2] == 0) {
            s0 = *(s32 *)s3;
            sh = s2 << 2;
            if (D_80194723[s2] != 0)
                s1 = *(s32 *)(s5 + sh - 8);
            else
                s1 = *(s32 *)(sh + s6);

            {
                s32 rp = *(s32 *)(s1 + 0x20) + 0x34;
                gte_SetRotMatrix((void *)rp);
                gte_SetTransMatrix((void *)rp);
            }
            gte_ldv0((void *)(s1 + 0x104));
            gte_rtv0tr();
            gte_stlvnl(r);
            gte_stflg(&flag);

            func_80049CAC(*(s32 *)(s0 + 0x20) + 0x10, (s32)&m);

            w0 = r[0];
            *(s16 *)(s0 + 6) = w0;
            m.f = (s16)w0;
            w1 = r[1];
            *(s16 *)(s0 + 0xA) = w1;
            m.g = (s16)w1;
            w2 = r[2];
            *(s16 *)(s0 + 0xE) = w2;
            m.h = (s16)w2;

            {
                s32 d = *(s32 *)(s0 + 0x20);
                *(MTX8_80185648 *)(d + 0x34) = *(MTX8_80185648 *)&m;
            }
            {
                s32 d = *(s32 *)(s0 + 0x20);
                *(MTX8_80185648 *)(d + 0x54) = *(MTX8_80185648 *)&m;
            }

            *(s32 *)(*(s32 *)(s0 + 0x20) + 0x30) = s4;
            *(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) |= 1;

            c = *(u8 *)(s0 + 0x10A);
            if (c == s4)
                goto lbac;
            if (c == 2)
                goto ldc;
            goto linc;
        lbac:
            func_80184BAC((void *)s0, (void *)s1);
            goto linc;
        ldc:
            func_801858DC((void *)s0);
        }
    linc:
        s2++;
        s3 += 4;
    } while (s2 < 0x15);
}


#include "common.h"

extern u16 D_801EFD40;
extern void func_80185960(s32 target, u16 *cur, s32 step);

void func_801858DC(void *a0)
{
    u16 step;
    u16 flag;

    flag = D_801EFD40;
    step = 0x20;
    if (flag & 0x20) {
        step = 0x40;
    }

    func_80185960(*(s16 *)((s32)a0 + 0xE4),
                  (u16 *)((s32)(*(void **)((s32)a0 + 0x20)) + 0x10), step);
    func_80185960(*(s16 *)((s32)a0 + 0xE6),
                  (u16 *)((s32)(*(void **)((s32)a0 + 0x20)) + 0x12), step);
    func_80185960(*(s16 *)((s32)a0 + 0xE8),
                  (u16 *)((s32)(*(void **)((s32)a0 + 0x20)) + 0x14), step);
}



void func_80185960(s32 target, u16 *cur, s32 step)
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
    __asm__ __volatile__("" : "=r"(diff) : "0"(diff) : "memory");  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
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


void func_801859E4(s32 idx, u16 *src) {
    extern s32 D_801EFC4C[];
    s32 obj;

    obj = D_801EFC4C[idx];
    *(u16 *)(obj + 0xE4) = src[0];
    *(u16 *)(obj + 0xE6) = src[1];
    *(u16 *)(obj + 0xE8) = src[2];
}


void func_80185A18(s32 idx, s32 val)
{
    extern s32 D_801EFC4C[];

    *(s16 *)(D_801EFC4C[idx] + 0xE6) = val;
}


s16 func_80185A30(s32 param_1) {
    extern s32 aFC4C[] __asm__("D_801EFC4C");
    extern s32 aB58[] __asm__("D_80126B58");
    extern s32 func_8012BE54(s32);
    extern s32 func_8012B6D4(s16 *a0, s16 *a1);
    s32 iVar5;
    s32 iVar2;
    s32 uVar3;
    s16 *p58;
    s16 *pE4;

    iVar5 = aFC4C[param_1];
    p58 = (s16 *)aB58;
    iVar2 = func_8012BE54(iVar5);
    pE4 = (s16 *)(iVar5 + 0xE4);
    if (iVar2 < 0x4000) {
        return *(s16 *)(iVar5 + 0xE6);
    }
    uVar3 = func_8012B6D4(iVar5 + 4, p58 + 2);
    uVar3 &= 0xFFF;
    if (uVar3 < 0x800) {
        if (uVar3 > 0x400) {
            uVar3 = 0x800 - uVar3;
        }
        if (uVar3 >= 0x301) {
            uVar3 = 0x300;
        }
    } else {
        if (uVar3 < 0xC00) {
            uVar3 = 0x17FF - uVar3;
        }
        if (uVar3 < 0xD00) {
            uVar3 = 0xD00;
        }
    }
    pE4[1] = (s16)uVar3;
    return (s16)uVar3;
}


extern s32 D_801EFC48;
extern s32 aFC4C[] __asm__("D_801EFC4C");

void func_80185B04(u16 a0, u16 a1)
{
    
    extern s32 D_801EFC48;
    extern s32 D_801EFC4C[];
    s32 obj;
    u16 t;

    obj = D_801EFC4C[*(u8 *)(a0 * 8 + *(s32 *)(D_801EFC48 + 0xCC) + 6)];
    if (obj != 0) {
        t = *(u16 *)(obj + 0xE4);
        *(u16 *)(obj + 0xEC) = 0;
        *(u16 *)(obj + 0xEE) = 0;
        *(u16 *)(obj + 0xF2) = a1;
        *(u16 *)(obj + 0xF0) = t;
    }
}


#include "common.h"

extern s32 func_8004787C(s32 a0);

void func_80185B5C(u16 id)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801EFC48;
    extern s32 D_801EFC4C[];
    s32 obj;
    s32 q;

    obj = D_801EFC4C[*(u8 *)(id * 8 + *(s32 *)(D_801EFC48 + 0xCC) + 6)];
    if (obj != 0) {
        *(u16 *)(obj + 0xEE) = *(u16 *)(obj + 0xEE) + *(u16 *)(obj + 0xF2);
        q = func_8004787C(*(s16 *)(obj + 0xEE)) / 22;
        *(s16 *)(obj + 0xEC) = q;
        *(s16 *)(obj + 0xE4) = *(u16 *)(obj + 0xF0) + q;
    }
}


#include "common.h"

void func_80185C04(u16 a0, u16 a1)
{
    /* [T51] scoped in from file scope, mirroring func_80185B5C/func_80185C5C
       directly above/below in this TU. */
    extern s32 D_801EFC48;
    extern s32 D_801EFC4C[];
    s32 obj;
    u16 t;

    obj = D_801EFC4C[*(u8 *)(a0 * 8 + *(s32 *)(D_801EFC48 + 0xCC) + 6)];
    if (obj != 0) {
        t = *(u16 *)(obj + 0xE8);
        *(u16 *)(obj + 0xF4) = 0;
        *(u16 *)(obj + 0xF6) = 0;
        *(u16 *)(obj + 0xFA) = a1;
        *(u16 *)(obj + 0xF8) = t;
    }
}



extern s32 func_8004787C(s32 a0);

void func_80185C5C(u16 id)
{

    extern s32 D_801EFC48;
    extern s32 D_801EFC4C[];
    s32 obj;
    s32 q;

    obj = D_801EFC4C[*(u8 *)(id * 8 + *(s32 *)(D_801EFC48 + 0xCC) + 6)];
    if (obj != 0) {
        *(u16 *)(obj + 0xF6) = *(u16 *)(obj + 0xF6) + *(u16 *)(obj + 0xFA);
        q = func_8004787C(*(s16 *)(obj + 0xF6)) / 22;
        *(s16 *)(obj + 0xF4) = q;
        *(s16 *)(obj + 0xE8) = *(u16 *)(obj + 0xF8) + q;
    }
}


extern s32 D_801EFC64[];
void func_80185D9C(void *a0);

void func_80185D04(s32 a0)
{
    s32 i = 6;
    s32 h = 0x1000;
    s32 *p = D_801EFC64;

    for (; i < 0x15; i++, p++) {
        s32 rec = *p;
        *(u16 *)(*(s32 *)(rec + 0x20) + 0x18) = h;
        *(u16 *)(*(s32 *)(rec + 0x20) + 0x1A) = h;
        *(u16 *)(rec + 0x86) &= ~1;
        if (a0 != 0) {
            func_80185D9C((void *)rec);
        }
    }
}


void func_80185D9C(void *a0)
{
    u16 n;

    n = *(u16 *)((s32)a0 + 0x70);
    if ((u32)(n - 6) < 13) {
        *(u16 *)((s32)a0 + 0x84) = n * 8;
        *(u16 *)((s32)a0 + 0xFE) = 0x30;
        *(u16 *)((s32)a0 + 0x100) = 0x40;
        *(u16 *)((s32)a0 + 0x86) |= 3;
    }
}


#include "common.h"

void func_80185DDC(void *a0)
{
    if (*(u16 *)((s32)a0 + 0x86) & 1) {
        if (*(s16 *)((s32)a0 + 0x84) != 0) {
            *(s16 *)((s32)a0 + 0x84) -= 1;
        } else {
            *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
            if (*(u16 *)((s32)a0 + 0x86) & 2) {
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) += *(u16 *)((s32)a0 + 0x100);
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) += *(u16 *)((s32)a0 + 0x100);
                if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) >= 0x1380) {
                    *(u16 *)((s32)a0 + 0x86) &= 0xFFFD;
                }
            } else {
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) -= *(u16 *)((s32)a0 + 0x100);
                *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) -= *(u16 *)((s32)a0 + 0x100);
                if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) < 0x1001) {
                    *(u16 *)((s32)a0 + 0x86) |= 0x2;
                    *(s16 *)((s32)a0 + 0x84) = *(u16 *)((s32)a0 + 0xFE);
                    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) &= 0xFFEF;
                }
            }
        }
    }
}


extern s32 D_801EFC64[];

void func_80185F1C(void) {
    s32 i = 6;
    s32 h = 0x1000;
    s32 c = 0xC;
    s32 w = 0x10;
    s32 x = 0x80;
    s32 *p = D_801EFC64;

    for (; i < 21; i++, p++) {
        s32 *rec = (s32 *)*p;
        *(s16 *)((s8 *)*(s32 *)((s8 *)rec + 0x20) + 0x18) = h;
        *(s16 *)((s8 *)*(s32 *)((s8 *)rec + 0x20) + 0x1A) = h;
        if (i < 13) {
            u16 f = *(u16 *)((s8 *)rec + 0x86);
            *(s16 *)((s8 *)rec + 0x84) = (c - i) * 4;
            *(s16 *)((s8 *)rec + 0xFE) = w;
            *(s16 *)((s8 *)rec + 0x100) = x;
            *(u16 *)((s8 *)rec + 0x86) = f | 3;
        } else {
            *(u16 *)((s8 *)rec + 0x86) &= ~1;
        }
    }
}


extern u8 D_80194724[];
extern s32 D_801EFC4C;

void func_80185FAC(void) {
    s32 i;
    for (i = 0; i < 0x15; i++) {
        if (D_80194724[i] == 0) {
            *(u8 *)(((s32 *)&D_801EFC4C)[i] + 0x10A) = 0;
        }
    }
}


#include "common.h"

void func_80185FF4(void *a0)
{
    extern u16 D_801EFD44;
    extern u16 D_801EFD48;
    extern u16 D_801EFD4C;
    s32 obj;

    obj = *(s32 *)((s32)a0 + 0x20);
    D_801EFD48 = 0;
    D_801EFD44 = *(u16 *)(obj + 0x10);
    D_801EFD4C = 0x60;
}


extern u16 D_801EFD40;
extern u16 D_801EFD44;
extern u16 D_801EFD48;
extern u16 D_801EFD4C;

void func_80186020(void *a0) {
    s32 p;
    u16 x;
    /* $v0 pin (cookbook "register pin" lever): without it sched1's birthing boost
       hands $v0 to the wrong temp and the two lhu's swap registers (residual 12). */
    register u16 y __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)

    if ((D_801EFD40 & 2) != 0) {
        if ((s16)D_801EFD48 >= 0x120) {
            *(s16 *)&D_801EFD4C = -0x60;
        } else if ((s16)D_801EFD48 < -0x5F) {
            *(s16 *)&D_801EFD4C = 0x60;
        }
        x = D_801EFD48;
        y = D_801EFD4C;
        p = *(s32 *)((s32)a0 + 0x20);
        x = x + y;
        y = D_801EFD44;
        D_801EFD48 = x;
        y = y + x;
        *(u16 *)(p + 0x10) = y;
    } else {
        if ((D_801EFD40 & 1) != 0) {
            if ((s16)D_801EFD48 >= 0x120) {
                return;
            }
            y = (s16)D_801EFD48 + 0x60;
        } else {
            if ((s16)D_801EFD48 < -0x5F) {
                return;
            }
            y = (s16)D_801EFD48 - 0x60;
        }
        x = D_801EFD44;
        p = *(s32 *)((s32)a0 + 0x20);
        D_801EFD48 = y;
        x = x + y;
        *(u16 *)(p + 0x10) = x;
    }
}


void func_80186110(s32 arg0)
{
    extern s32 D_801EFCA0;
    s32 var;

    var = func_8012C588(0x214, arg0);
    if (var != 0) {
        *(s16 *)(var + 6) = 0x60;
        *(s16 *)(var + 0xA) = -0x540;
        *(s16 *)(var + 0xE) = 0x900;
    }
    D_801EFCA0 = var;
}


#include "common.h"

extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_801EFCA4;
extern s32 D_801EFCE8[];

void func_8018615C(s32 arg0)
{
    s32 i;

    D_801EFCA4 = func_8012C588(0x255, arg0);
    for (i = 0x10; i < 0x14; i++) {
        D_801EFCE8[i - 0x10] = func_8012C658(0x257, i, arg0);
    }
}


#include "common.h"

extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_801861D4(s32 arg0)
{
    s32 i;
    s32 *ptr;
    extern s32 D_801EFCA8[];
    extern s32 D_801EFCF8[];
    extern s32 D_801EFD14;
    extern void *D_801EFD1C;

    i = 0;
    ptr = D_801EFCA8;
    for (; i < 0x10; i++) {
        *ptr++ = func_8012C658(0x257, i, arg0);
    }
    for (i = 0; i < 7; i++) {
        D_801EFCF8[i] = func_8012C658(0x258, i + 1, arg0);
    }
    D_801EFD14 = func_8012C588(0x272, arg0);
    D_801EFD1C = (void *)func_8012C588(0x291, arg0);
}


extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_801862A4(s32 _arg0)
{
    extern s32 D_801EFC4C;
    s32 i;
    s32 v0;

    v0 = 0;
    for (i = 0; i < 0x15; i++) {
        v0 = func_8012C658(0x200, i, v0);
        aFC4C[i] = v0;
    }
}


#include "common.h"

extern u16 D_801EFD40;
extern void func_80186470(void *a0);
extern void func_8018637C(s32 arg0, s32 arg1);

void func_80186300(s32 a0, void *a1, s32 a2) {
    register s32 s1 __asm__("$17") = a2;  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B t3_tus1)

    D_801EFD40 = D_801EFD40 & 0xFFFB;
    func_80186470((void *)a0);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) = 0;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (u16)s1;
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x14) = 0;
    func_8018637C(a0, (s32)a1);
}


extern void func_8012A828();
extern u16 D_801EFD40;

void func_8018637C(s32 arg0, s32 arg1)
{
    func_8012A828();
    D_801EFD40 |= 0x10;
}


#include "common.h"

extern u16 D_801EFD40;

void func_801863B4(s32 a0) {
    u16 f;

    f = D_801EFD40;
    *(s16 *)(a0 + 0x98) = 0;
    D_801EFD40 = f & 0xFFEF;
}


extern u16 D_801EFD40;
extern s32 D_801EFC4C;
extern void func_80186518(void *a0, void *a1, s32 a2);
extern void func_801866C4(void *a0);

void func_801863D4(void *a0) {
    s32 i;
    s32 *p;

    i = 0;
    p = &((s32 *)&D_801EFC4C)[0];
    do {
        u16 flag;
        void *ent;

        flag = D_801EFD40;
        ent = (void *)p[0];
        flag &= 0x4;
        if (flag != 0) {
            func_80186518(a0, ent, i);
        } else {
            func_801866C4(ent);
        }
        *(u16 *)((u8 *)ent + 0x86) &= ~0x10;
        __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B t3_tus1)
        i++;
        p++;
    } while (i < 0x15);
}


#include "common.h"

extern s32 D_801EFC4C;
extern u16 D_801EFD40;

extern void func_80186518(void *a0, void *a1, s32 a2);
extern void func_801866C4(void *a0);

void func_80186470(void *a0) {
    s32 s0;
    s32 *s1;

    s0 = 0;
    s1 = ((s32 *)&D_801EFC4C);
    do {
        u16 flag;
        void *a1;

        flag = D_801EFD40;
        a1 = (void *)s1[0];
        flag &= 0x4;
        if (flag != 0) {
            if (s0 < 0xE) {
                func_80186518(a0, a1, s0);
            }
        } else {
            if (s0 >= 0xE) {
                *(u16 *)((u8 *)a1 + 0x86) |= 0x10;
            } else {
                func_801866C4(a1);
            }
        }

        s0++;
        s1++;
    } while (s0 < 0x15);
}


#include "common.h"

extern void *D_801DEC8C;
extern void func_8001C1E4(void *a0, s32 a1);

void func_80186518(void *a0, void *a1, s32 a2) {
    void *self0;
    s32 flag;
    void *tbl;
    s32 base;
    s32 base2;

    self0 = a0;
    flag = *(u16 *)((s32)a1 + 0x86);
    tbl = D_801DEC8C;
    if (flag & 8) {
        base = a2 * 12 + (s32)tbl;
        *(s16 *)((s32)a1 + 0x6) = *(u16 *)(base + 0) - *(u16 *)(base - 0xC);
        *(s16 *)((s32)a1 + 0xA) = *(u16 *)(base + 2) - *(u16 *)(base - 0xA);
        *(s16 *)((s32)a1 + 0xE) = *(u16 *)(base + 4) - *(u16 *)(base - 8);
        *(u16 *)(*(s32 *)((s32)a1 + 0x20) + 0x10) =
            *(u16 *)(base + 6) - *(u16 *)(base - 6);
        *(u16 *)(*(s32 *)((s32)a1 + 0x20) + 0x12) =
            *(u16 *)(base + 8) - *(u16 *)(base - 4);
        *(u16 *)(*(s32 *)((s32)a1 + 0x20) + 0x14) =
            *(u16 *)(base + 0xA) - *(u16 *)(base - 2);

        func_8001C1E4(*(void **)((s32)a1 + 0x20),
                      *(s32 *)(*(s32 *)((s32)a1 + 0x64) + 0x20));
    } else {
        u16 *dst;
        s32 i;

        base2 = *(s32 *)(*(s32 *)((s32)self0 + 0x20) + 0x20);
        if (base2 != 0) {
            s32 row2 = a2 * 12 + base2;
            *(u16 *)(*(s32 *)((s32)a1 + 0x20) + 0x10) = *(u16 *)(row2 + 6);
            *(u16 *)(*(s32 *)((s32)a1 + 0x20) + 0x12) =
                *(u16 *)(row2 + 8) + *(u16 *)(*(s32 *)((s32)self0 + 0x20) + 0x12);
            *(u16 *)(*(s32 *)((s32)a1 + 0x20) + 0x14) = *(u16 *)(row2 + 0xA);
        }

        *(s16 *)((s32)a1 + 0x6) = *(s32 *)(*(s32 *)((s32)a1 + 0x20) + 0x48);
        *(s16 *)((s32)a1 + 0xA) = *(s32 *)(*(s32 *)((s32)a1 + 0x20) + 0x4C);
        *(s16 *)((s32)a1 + 0xE) = *(s32 *)(*(s32 *)((s32)a1 + 0x20) + 0x50);

        dst = (u16 *)((s32)a1 + 0xE4);
        for (i = 0; i < 4; i++) {
            *dst = *(u16 *)(*(s32 *)((s32)a1 + 0x20) + 0x10);
            dst++;
            *dst = *(u16 *)(*(s32 *)((s32)a1 + 0x20) + 0x12);
            dst++;
            *dst = *(u16 *)(*(s32 *)((s32)a1 + 0x20) + 0x14);
            dst++;
        }
    }
}


void func_801866C4(void *a0)
{
    if (*(u16 *)((s32)a0 + 0x86) & 8) {
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x78) = 0;
    }
    *(s16 *)((s32)a0 + 0x6) = 0;
    *(s16 *)((s32)a0 + 0xA) = 0;
    *(s16 *)((s32)a0 + 0xE) = 0;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = 0;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) = 0;
}


#include "common.h"

extern u16 D_801EFD20;
/* §183: the TU spells D_801EFC4C as a scalar elsewhere; reach the array view
   through an __asm__ label alias -- the TU's own established idiom. */
extern s32 aFC4C[] __asm__("D_801EFC4C");
extern void func_80186798(s32 a0, void *a1);
extern void func_8018681C(s32 a0, void *a1);

s32 func_80186710(void) {
    u16 buf[3];
    s32 s0;
    s32 obj;

    s0 = D_801EFD20;
    obj = aFC4C[s0];
    buf[0] = *(u16 *)(*(s32 *)(obj + 0x20) + 0x10);
    buf[1] = *(u16 *)(*(s32 *)(obj + 0x20) + 0x12);
    buf[2] = *(u16 *)(*(s32 *)(obj + 0x20) + 0x14);
    func_80186798(s0, buf);
    func_8018681C(s0, buf);
}


#include "common.h"

void func_80186798(s32 a0, void *a1) {
    extern u8 D_80194724[];
    extern s32 aFC4C[] __asm__("D_801EFC4C");
    extern void func_801868A0();
    u32 i;

    for (i = 0; i < (u32)a0; i++) {
        if (D_80194724[i] == 0) {
            func_801868A0((void *)aFC4C[i], a1);
        }
    }
}


extern s32 aFC4C[] __asm__("D_801EFC4C");
extern u8 D_80194724[];
extern void func_801868A0();

void func_8018681C(s32 a0, void *a1) {
    s32 i;

    for (i = a0 + 1; i < 0x15; i++) {
        if (D_80194724[i] == 0) {
            func_801868A0((void *)aFC4C[i], a1);
        }
    }
}


void func_801868A0(void *a0, u16 *a1) {
    u16 *dst;
    s32 i;

    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = a1[0];
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = a1[1];
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) = a1[2];

    dst = (u16 *)((s32)a0 + 0xE4);
    for (i = 0; i < 4; i++) {
        *dst = a1[0];
        dst++;
        *dst = a1[1];
        dst++;
        *dst = a1[2];
        dst++;
    }
}


extern s32 D_801EFC4C;

void func_80186908(void) {
    s32 i;

    for (i = 0; i < 0x15; i++) {
        *(u16 *)(((s32 *)&D_801EFC4C)[i] + 0x86) &= ~0x10;
    }
}


#include "common.h"

extern u16 D_801EFD40;
extern s32 D_801EFC48;
extern s32 D_801EFD24;
extern s32 D_801EFD28;
extern s16 func_80186A20(s32 a0, s32 a1);
extern void func_80186A68(void);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80186940(void *a0, s32 a1, s32 a2) {
    s16 ret;
    s16 a2s;
    s32 msg;

    a2s = a2;
    D_801EFD40 |= 0x80;
    ret = func_80186A20(D_801EFC48, (s16)a1);
    *(u16 *)(D_801EFC48 + 0x60) = *(u16 *)(D_801EFC48 + 0x60) + ret;
    if (a2s != 0) {
        func_8016AA50((s32)a0, ret);
    }
    *(u16 *)&D_801EFD24 = 8;
    if (ret != 0) {
        func_80186A68();
        msg = 0xBA9;
        if (*(u16 *)&D_801EFD28 - *(s16 *)(D_801EFC48 + 0x60) > 0) {
            msg = 0x906;
        }
        func_8002D4C8(msg, 0);
    }
}


s16 func_80186A20(s32 a0, s32 a1)
{
    s32 d;
    s32 t;

    d = *(u16 *)(a0 + 0x76) - *(u16 *)(a0 + 0x60);
    t = d - a1;
    if ((s16)d <= 0) {
        return 0;
    }
    if ((s16)t <= 0) {
        return (s16)d;
    }
    return (s16)a1;
}


extern s32 aFC4C[] __asm__("D_801EFC4C");
extern u8 D_80194350[];

void func_80186A68(void) {
    extern s32 D_801EFC4C;
    extern u8 D_80194350[];
    s32 i;
    s32 obj;
    s32 sub;

    for (i = 0; i < 0x15; i++) {
        obj = ((s32 *)&D_801EFC4C)[i];
        if (obj != 0) {
            sub = *(s32 *)(obj + 0x20);
            if (sub != 0) {
                *(s32 *)(sub + 0x80) = (s32)D_80194350;
            }
        }
    }
}


void func_80186AB8(void) {
    extern s32 D_801EFC4C;
    extern u8 D_80194348[];
    s32 i;
    s32 obj;
    s32 sub;

    for (i = 0; i < 0x15; i++) {
        obj = ((s32 *)&D_801EFC4C)[i];
        if (obj != 0) {
            sub = *(s32 *)(obj + 0x20);
            if (sub != 0) {
                *(s32 *)(sub + 0x80) = (s32)D_80194348;
            }
        }
    }
}


#include "common.h"

extern s32 D_801EFCF4[];
extern s32 D_801EFCA8[];
extern void func_8012C218(void *a0);
extern void func_80189D38(void *a0);

void func_80186B08(void *a0)
{
    s16 idx;

    idx = *(s16 *)((s32)a0 + 0xF4);
    if (idx != 0 && D_801EFCF4[idx] != 0) {
        func_8012C218((void *)D_801EFCF4[idx]);
        D_801EFCF4[idx] = 0;
    }

    if (D_801EFCA8[(s16)(idx * 2)] != 0) {
        func_80189D38((void *)D_801EFCA8[(s16)(idx * 2)]);
        D_801EFCA8[(s16)(idx * 2)] = 0;
    }

    if (D_801EFCA8[(s16)(idx * 2 + 1)] != 0) {
        func_80189D38((void *)D_801EFCA8[(s16)(idx * 2 + 1)]);
        D_801EFCA8[(s16)(idx * 2 + 1)] = 0;
    }
}


extern s32 D_801EFC4C;
extern s32 D_801EFC54;

void func_80186BD8(void) {
    *(s16 *)(D_801EFC4C + 0xAE) = -1;
    *(s16 *)(D_801EFC54 + 0xAE) = -1;
}


extern s32 D_801EFC4C;
extern s32 D_801EFC54;

void func_80186BF8(void) {
    *(s16 *)(D_801EFC4C + 0xAE) = -5;
    *(s16 *)(D_801EFC54 + 0xAE) = -1;
}


extern s32 D_801EFC4C;
extern s32 D_801EFC54;

void func_80186C1C(void) {
    *(s16 *)(D_801EFC4C + 0xAE) = -1;
    *(s16 *)(D_801EFC54 + 0xAE) = -3;
}


#include "common.h"

void func_80186C40(void) {
    extern s32 aFC4C[] __asm__("D_801EFC4C");
    extern u8 D_8019473C[];
    extern void func_8018B060(s32 a0);
    extern void func_8012AD44(s32 *a0, s16 a1);

    s32 ent;
    s32 i;

    for (i = 0; i < 0x15; i++) {
        ent = aFC4C[i];
        if (ent == 0) {
            continue;
        }
        *(u16 *)(ent + 0x86) |= 0x10;
        if (D_8019473C[*(s16 *)(ent + 0x70)] != 0) {
            func_8018B060(ent);
        }
        func_8012AD44((s32 *)ent, 2);
    }
}


#include "common.h"

extern void func_8001C924(void*, void*);
extern s32 func_8018B948(void);
extern void func_8018BA44(s32 a0, s32 a1);
extern u8 D_801AA158[];
extern u8 D_80063548[];

void func_80186CD8(s32 a0)
{
    s32 s0;
    s32 v0;
    s32 v1;

    s0 = a0;

    /* Load pointer from s0 + 0x20 */
    v0 = *(s32 *)(s0 + 0x20);

    /* Call func_8001C924 with that pointer and address of D_801AA158 */
    ((void (*)(s32, void *))func_8001C924)(v0, (void *)D_801AA158);

    /* Force addu $a0, $s0, $zero to preserve s0 in a0 for func_8018BA44 */
    asm volatile("addu $a0, $s0, $zero");  // !FAKE: instruction addu — REFUSED instruction `addu` has no C spelling in the table (P36 rung B t3_tus2)

    /* Load pointer from s0 + 0x20 again */
    v1 = *(s32 *)(s0 + 0x20);

    /* Load D_80063548 and store to the structure's field at offset 0x20 */
    *(s32 *)(v1 + 0x20) = (s32)D_80063548;

    /* Set short fields in s0 */
    *(s16 *)(s0 + 0x6) = 0x500;
    *(s16 *)(s0 + 0xA) = -0x9C0;
    *(s16 *)(s0 + 0xE) = 0x18A0;

    /* Clear short field at s0 + 0xF4 before calling func_8018B948 */
    *(s16 *)(s0 + 0xF4) = 0;

    /* Call func_8018B948 */
    v0 = func_8018B948();

    /* Store result to s0 + 0xD0 */
    *(s32 *)(s0 + 0xD0) = v0;

    /* If result is zero, return */
    if (v0 == 0) {
        return;
    }

    /* Otherwise, call func_8018BA44 with s0 and v0 */
    func_8018BA44(a0, v0);
}


extern void func_8018BA44(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);

void func_80186D58(s32 a0) {
    s16 v;

    func_8018BA44(a0, *(s32 *)(a0 + 0xD0));
    if (*(s16 *)(a0 + 0xA) < -0x7C0) {
        *(s16 *)(a0 + 0xA) = *(s16 *)(a0 + 0xA) + 3;
    } else {
        v = *(u16 *)(a0 + 0xF4) + 0x40;
        *(u16 *)(a0 + 0xF4) = v;
        *(s16 *)(a0 + 0x52) = func_8004787C(v) >> 8;
    }
}


#include "common.h"

extern s32 func_80186E54();

s32 func_80186DCC(s32 a0) {
    s16 local_10[3];  /* sp+0x10 */
    s16 local_18[3];  /* sp+0x18 */
    s32 v0;

    /* Initialize arrays in target instruction order */
    local_10[0] = -0x18;
    local_18[0] = 0x18;
    local_18[1] = 0x18;
    local_10[1] = 0x18;
    local_18[2] = -0x18;
    local_10[2] = -0x18;

    v0 = func_80186E54(a0, local_10, local_18);

    if (v0 == 0) {
        local_18[2] = 0x18;
        local_10[2] = 0x18;
        v0 = func_80186E54(a0, local_10, local_18);
        return (v0 != 0) ? 1 : 0;
    }

    return 1;
}


#include "common.h"

extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);

s32 func_80186E54(s32 arg0, s32 arg1, s32 arg2)
{
    extern s32 *D_80126B78;
    extern s32 *D_80126B90;
    struct { u16 x, y, z, w; } a;
    struct { u16 x, y, z, w; } b;

    func_8012F214(arg0, arg1, &a);
    func_8012F214(arg0, arg2, &b);
    func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&a, (s32)&b);
}


void func_80186EBC(void *a0)
{
    extern void func_80016714(void *a0, s32 a1);

    if (*(void **)((s32)a0 + 0xD0) != NULL) {
        func_80016714(*(void **)((s32)a0 + 0xD0), 0x38);
        *(void **)((s32)a0 + 0xD0) = NULL;
    }
}


extern s32 D_801EFC4C;

void func_80186EFC(s32 arg0) {
    s32 base;

    base = D_801EFC4C;
    *(s16 *)((s32)arg0 + 0) = *(s32 *)(*(s32 *)(base + 0x20) + 0x48);
    *(s16 *)((s32)arg0 + 2) = *(s32 *)(*(s32 *)(base + 0x20) + 0x4C);
    *(s16 *)((s32)arg0 + 4) = *(s32 *)(*(s32 *)(base + 0x20) + 0x50);
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern u16 D_801EFD40;
extern u16 D_801EFD20;
extern s32 D_801EFC48;
extern s32 D_801EFD2C;
extern s32 D_801EFD28;
extern s32 D_801DEC6C;
extern void func_80186110();
extern void func_8018615C(s32 a0);
extern void func_80189A98();
extern void func_8018637C(s32 a0, s32 a1);
extern void func_801862A4(s32 a0);
extern void func_801805D8(void);

void func_80186F44(void *a0)
{
    register void *s0 __asm__("$16") = a0;  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((u8 *)s0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(s0);
        return;
    }
    func_8001C2C4(v0);
    *(s32 *)&D_801EFC48 = (s32)s0;
    D_801EFD40 = 8;
    func_80186110(s0);
    func_8018615C(s0);
    func_80189A98();
    D_801EFD20 = 0;
    func_8018637C(s0, &D_801DEC6C);
    func_801862A4(s0);
    {
        register void *t __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
        t = s0;
        *(s16 *)((u8 *)t + 0x76) = 0x40;
        *(s16 *)((u8 *)t + 0xF6) = 3;
    }
    (*(u16 *)&D_801EFD2C) = 0x12C;
    (*(u16 *)&D_801EFD28) = 0x12C;
    func_801805D8();
}


extern u16 D_801EFD20;
extern u16 D_801EFD40;
extern void func_801805F8(s32 arg0);
extern void func_801852BC(s32 a0);
extern void func_801853D0(s32 a0);
extern void func_80185648();

void func_80187008(s32 arg0) {
    s32 g = D_801EFD20;
    func_801805F8(arg0);
    if (D_801EFD40 & 4) {
        func_801852BC(g);
        func_801853D0(g);
        func_80185648(g);
    }
}


#include "common.h"

/* TU (ov_SC04_011_jr_8017D494.c) already declares these at file scope: */
extern u16 D_80126B5E;
extern u16 D_80126B66;
extern int func_80178970(void);
extern void func_80178D18(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern void func_8017CACC(void *a0, void *a1, s32 a2, s32 a3);
extern void func_8002D4C8(s32 a0, s32 a1);

extern void func_80139A68(s32 a0, u16 a1);

/* not declared anywhere in this TU yet */
extern u8 D_80194378[];
extern s32 D_801EFD28;
extern s32 D_801EFD2C;
extern void func_80180AB4();

void func_80187068(s32 a0) {
    extern u16 D_80126B58;
    u16 state;

    state = *(u16 *)(a0 + 0x34);
    switch (state) {
    case 0:
        if (*(s16 *)&D_80126B5E < 0x201) {
            return;
        }
        if (*(s16 *)&D_80126B66 < 0x5F9) {
            return;
        }
        if (((u32)D_80126B58 - 2) < 2) {
            return;
        }
        func_80139A68(4, 0);
        func_80139A68(0xC, 1);
        func_80178B18(a0, (s32)D_80194378);
        state = *(u16 *)(a0 + 0x34);
        *(u16 *)(a0 + 0x10A) = 0;
        *(u16 *)(a0 + 0x34) = state + 1;
        break;
    case 1:
        if (((s32 (*)(s32))func_80178970)(a0) == 0) {
            return;
        }
        ((void (*)(s32))func_80178D18)(a0);
        func_8017CACC((void *)&D_801EFD28, (void *)&D_801EFD2C, 4, 0xB4);
        func_80180AB4(a0);
        func_8002D4C8(0xB37, 0);
        break;
    }
}


#include "common.h"

extern u16 D_801EFD40;
extern u16 D_801EFD20;
extern u8 D_80194C14[];
extern u8 D_80194CB4[];
extern void func_80184CCC();
extern void func_80184DB8();
extern s32 func_80184F4C(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80182B5C(void *a0);

void func_80187178(void *a0)
{
    void *s0 = a0;
    u16 state;
    u16 st;
    s16 v0;

    state = *(u16 *)((s32)s0 + 0x34);
    switch (state) {
    case 0:
        v0 = *(s16 *)((s32)s0 + 0x98);
        if (v0 == 0) {
            func_80184CCC((s32)s0, (s32)D_80194C14);
            {
                u16 pinst;
                u16 flags = D_801EFD40 | 0x20;
                pinst = *(u16 *)((s32)s0 + 0x34);
                D_801EFD40 = flags;
                pinst = pinst + 1;
                *(u16 *)((s32)s0 + 0x34) = pinst;
                D_801EFD40 = flags & 0xEFFF;
            }
        } else if (*(s32 *)((s32)s0 + 0x94) == 0x42) {
            D_801EFD40 |= 0x1000;
            func_8002D4C8(0x994, 0);
        }
        break;
    case 1:
        func_80184DB8(D_801EFD20);
        if (func_80184F4C() != 0) {
            func_80184CCC((s32)s0, (s32)D_80194CB4);
            *(u16 *)((s32)s0 + 0x34) += 1;
        }
        break;
    case 2:
        func_80184DB8(D_801EFD20);
        if (func_80184F4C() != 0) {
            func_80182B5C(s0);
        }
        break;
    }
}


#include "common.h"

extern void func_80185DDC(void *a0);
extern void func_80186020(void *a0);
extern void func_80132784(s32 a0, s32 a1, u32 a2);
extern void func_8018489C();

extern u16 D_801EFD40;
extern s32 D_801EFC48;

void func_801872D0(void *a0)
{
    void *s0;
    s16 v1;
    s32 v0;
    s32 a1;
    s32 a2;

    func_80185DDC(a0);
    s0 = a0;

    v1 = *(s16 *)((s32)s0 + 0x70);
    if (v1 == 1) {
        func_80186020(s0);
    }

    if ((*(u16 *)((s32)s0 + 0x86) & 0x10) != 0) {
        return;
    }

    if ((D_801EFD40 & 4) == 0) {
        a1 = D_801EFC48;
        v0 = *(s32 *)((s32)s0 + 0x20);
        *(s16 *)((s32)s0 + 0xE) = 0;
        *(s16 *)((s32)s0 + 0xA) = 0;
        *(s16 *)((s32)s0 + 0x6) = 0;
        *(s16 *)(v0 + 0x14) = 0;
        *(s16 *)(v0 + 0x12) = 0;
        *(s16 *)(v0 + 0x10) = 0;
        func_80132784((s32)s0, a1, *(u16 *)((s32)s0 + 0x70));
    }

    v1 = *(s16 *)((s32)s0 + 0x70);
    if (v1 == 0) {
        goto shared;
    }
    if (v1 != 2) {
        goto default_case;
    }
shared:
    if (D_801EFD40 & 0x1000) {
        func_8018489C(s0, 0x30, -0x20);
        func_8018489C(s0, 0x30, 0x20);
    } else {
        func_8018489C(s0, 0x30, 0);
    }
    return;
default_case:
    func_8018489C(s0, 0x24, 0);
}


void func_801873D0(void) {
}

extern void func_8012AD44(s32 *a0, s16 a1);

void func_801873D8(s32 arg0) {
    func_8012AD44((s32 *)arg0, 3);
}


#include "common.h"

extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012B414(int a0);
extern void func_80187D68(void *a0);

extern void *D_801EFD70[4];

void func_801873F8(void *a0)
{
    void *s2 = a0;
    void *s3;
    u16 val;
    s32 i;

    s3 = *(void **)((s32)s2 + 0xCC);

    if (*(s16 *)(*(s32 *)((s32)s2 + 0x20) + 0x18) != 0) {
        *(s16 *)(*(s32 *)((s32)s2 + 0x20) + 0x18) -= 0x400;
        val = *(u16 *)(*(s32 *)((s32)s2 + 0x20) + 0x18);
        *(s16 *)(*(s32 *)((s32)s2 + 0x20) + 0x1A) = val;
        if (s3 != NULL) {
            *(s16 *)((s32)s3 + 0x18) = val;
            *(s16 *)((s32)s3 + 0x1A) = val;
        }
        for (i = 0; i < 4; i++) {
            register void *entry __asm__("$4") = D_801EFD70[i];  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
            if (entry != NULL) {
                *(s16 *)((s32)entry + 0x18) = val;
                *(s16 *)((s32)entry + 0x1A) = val;
            }
        }

        if (*(s16 *)(*(s32 *)((s32)s2 + 0x20) + 0x18) != 0) {
            goto special;
        }
    }

    for (i = 0; i < 4; i++) {
        if (D_801EFD70[i] != NULL) {
            func_80016714(D_801EFD70[i], 0x38);
        }
    }
    if (*(void **)((s32)s2 + 0xD0) != NULL) {
        func_80016714(*(void **)((s32)s2 + 0xD0), 0x38);
    }
    if (*(void **)((s32)s2 + 0xD4) != NULL) {
        func_80016714(*(void **)((s32)s2 + 0xD4), 0x38);
    }
    if (s3 != NULL) {
        func_80016714(s3, 0x84);
    }
    func_8012C218(s2);
    func_8002D4C8(4, 0x88A);
    func_8002D4C8(4, 0x88B);
    return;

special:
    *(s16 *)(*(s32 *)((s32)s2 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)((s32)s2 + 0x20) + 0x14) + 0x100;
    func_8012B414((s32)s2);
    func_80187D68(s2);
}


#include "common.h"

extern void (*D_801947E4[])(void);
extern void func_80187618(s32 *a0, u16 a1, u16 a2);
extern void func_801876A0(s32 a0);
extern u8 D_801EFD50;

void func_80187574(void *param_1)
{
    D_801947E4[*(unsigned short *)((char *)param_1 + 2)]();
    func_80187618((s32 *)&D_801EFD50, 0x160, 0x18F);
    func_801876A0((s32)param_1);
}




void func_801875D8(void* a0, s32 a1, s32 a2)
{
    u16 buf[4];

    buf[2] = 0x10;
    buf[0] = a1;
    buf[1] = a2;
    buf[3] = 1;
    StoreImage((s32)&buf, (void *)a0);
}


#include "common.h"

extern void func_800599B8(u16 *, s32 *);

void func_80187618(s32 *a0, u16 a1, u16 a2) {
    s32 t1;
    s32 t2;
    s32 i;
    u16 buf[4];

    t1 = a0[7];
    t2 = a0[6];

    i = 7;
    do {
        a0[i] = a0[i - 2];
        a0[i - 1] = a0[i - 3];
        i -= 2;
    } while (i >= 3);

    a0[i] = t1;
    a0[i - 1] = t2;

    buf[2] = 0x10;
    buf[0] = a1;
    buf[1] = a2;
    buf[3] = 1;

    func_800599B8(buf, a0);
}


void func_80187698(void *a0) {
        *(s16 *)((s32)a0 + 0xFE) = 0;
    }


void func_801876A0(s32 a0) {
    struct { s16 x, y, w, h; } rect;
    s16 v;

    v = *(s16 *)(a0 + 0xFE) + 8;
    *(s16 *)(a0 + 0xFE) = v;
    if (v >= 0x80) {
        *(s16 *)(a0 + 0xFE) = 0;
    }
    if (*(s16 *)(a0 + 0xFE) != 0) {
        rect.x = 0x2B0;
        rect.y = 0x200 - *(s16 *)(a0 + 0xFE);
        rect.w = 0x10;
        rect.h = *(s16 *)(a0 + 0xFE);
        MoveImage(&rect, 0x2B0, 0x100);
        rect.y = 0x180;
        rect.h = 0x80 - *(s16 *)(a0 + 0xFE);
        MoveImage(&rect, 0x2B0, *(s16 *)(a0 + 0xFE) + 0x100);
    } else {
        rect.x = 0x2B0;
        rect.y = 0x180;
        rect.w = 0x10;
        rect.h = 0x80;
        MoveImage(&rect, 0x2B0, 0x100);
    }
}


#include "common.h"

typedef struct { s16 x, y, z, w; } Vec4S16_8018778C;

extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern s32 func_80187940(s32 arg0, s32 arg1, s32 arg2, s16 arg3);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

/* func_8018778C — ov_SC04_011, 109 ins, MATCH.
 *
 * Residual class cracked on the 2nd pass: "header-load-chain-schedule-intrinsic" was NOT
 * intrinsic — it was two sched1 LUID/birthing-boost artifacts introduced by the draft's own
 * scaffolding (gcc-2.7.2-map/sched.md §S1 + §S2):
 *
 *  1. NO explicit `c140`/`c40` locals and NO hoisted `i = 0;` before the loop.  Writing the
 *     -0x140 / -0x40 constants INLINE in the loop body and using a plain `for (i = 0; ...)`
 *     lets loop.c hoist the constant loads into the preheader, which puts their LUIDs AFTER
 *     the call's arg setup.  Only then do `addiu $a0,$sp,0x10` / `addiu $a1,$sp,0x18` win the
 *     LUID tie-break and land early (target idx 12/14) as the fillers of the FIRST P-chain's
 *     load-delay slots — instead of sinking next to the jal.  Explicit early locals for those
 *     constants (the 1st-pass draft) forced the opposite order and cost 22 instructions.
 *     This is also what fixes the global temps' register choice ($v1/$a2/$v0, not $v1/$a1/$v0).
 *
 *  2. HEADER STATEMENT ORDER is the schedule (§S1): the three self-position reads come FIRST,
 *     in field order, and only then the three target-position globals in x,y,z order.  A 120-way
 *     sweep over every A-vs-B interleaving x every v18 field order has exactly ONE zero-diff
 *     point — this one; the next best (v18 written x,z,y) is 2 off, and ANY interleaving that
 *     puts a v18 store before v10.z is >= 20 off.
 *
 * Note the two 1st-pass levers that are NOT needed once the above is right: the loop body writes
 * v18 before v10 per call (kept), but the struct stays s16-typed (u16 would emit `ori` for
 * -0x280), and no register pins / pointer locals are involved at all — an early `s16 *p1 = &v18`
 * gets the birthing boost (REG_N_SETS==1) and sinks right back to the call.
 */
void func_8018778C(void *a0)
{
    Vec4S16_8018778C v10;
    Vec4S16_8018778C v18;
    s32 i;
    s16 ang;

    v10.x = *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x48);
    v10.y = *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x4C);
    v10.z = *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x50);
    v18.x = D_80126B5E;
    v18.y = D_80126B62;
    v18.z = D_80126B66;

    ang = func_8012B70C((s16 *)&v10, (s16 *)&v18) & 0xFFF;

    for (i = 0; i < 3; i++) {
        s16 x = (i << 6) - 0x40;
        v18.x = x;
        v10.x = x;
        v10.z = -0x140;
        v18.z = 0;
        v18.y = -0x40;
        v10.y = -0x40;
        if (func_80187940((s32)a0, (s32)&v10, (s32)&v18, ang)) {
            return;
        }

        v18.y = 0;
        v10.y = 0;
        if (func_80187940((s32)a0, (s32)&v10, (s32)&v18, ang)) {
            return;
        }

        v18.y = 0x40;
        v10.y = 0x40;
        if (func_80187940((s32)a0, (s32)&v10, (s32)&v18, ang)) {
            return;
        }

        v10.z = -0x280;
        v18.z = -0x140;
        if (func_80187940((s32)a0, (s32)&v10, (s32)&v18, ang)) {
            return;
        }

        v18.y = 0;
        v10.y = 0;
        if (func_80187940((s32)a0, (s32)&v10, (s32)&v18, ang)) {
            return;
        }

        v18.y = -0x40;
        v10.y = -0x40;
        if (func_80187940((s32)a0, (s32)&v10, (s32)&v18, ang)) {
            return;
        }
    }
}


#include "common.h"

/* func_80187940 — ov_SC04_011 (split ov_SC04_011_jr_8017D494), 49 ins, MATCH.
 *
 * Two byte-load-bearing levers (both cookbook-indexed):
 *   1. PARAM WIDTH (§43/§3-T3): arg3 must be a PROTOTYPED `s16`.  An `s32` param with an
 *      explicit `(s16)` cast at the use site gives the same sll/sra but LOSES the
 *      `addu $s1,$s2,$zero` copy that the target fills the func_80135888 delay slot with
 *      (48 ins vs 49).  The declared-narrow param makes gcc keep the incoming SImode arg
 *      ($s2, sign-extended at the int use) AND a separate HImode variable pseudo ($s1,
 *      stored with `sh`) — two live pseudos, hence the copy.
 *   2. RET-0 PLACEMENT (§3-T4 / the shared-ret0 note): `if (c != 0) { body; return 1; }
 *      return 0;` puts the return-0 block FIRST (bnez-to-body + `j` epilogue with
 *      `move v0,zero` in the delay slot).  The early-return form `if (c == 0) return 0;
 *      body; return 1;` is NOT equivalent here — gcc sinks the ret-0 block to the tail and
 *      emits `beqz` instead.  Byte-measured: `== 0` early-return = 13 mismatches, `!= 0`
 *      with a trailing `return 0` = MATCH.  (`goto ret0;` + trailing `ret0: return 0;`
 *      also matches.)
 */

   /* 8-byte out-param scratch */

extern void func_8012F14C(s32 a0, s32 a1, s32 a2);   /* TU-canonical decl; called through a cast (fleet house style) */
extern void func_8012F568();
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 *D_80126B90;
extern s16  D_80126B9A;
extern u8   D_801152A8[];

s32 func_80187940(s32 arg0, s32 arg1, s32 arg2, s16 arg3)
{
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 *D_80126B78;
    Pt_80187940 a;
    Pt_80187940 b;

    ((void (*)(s32, s32, void *))func_8012F14C)(*(s32 *)(arg0 + 0x20) + 0x54, arg1, &a);
    ((void (*)(s32, s32, void *))func_8012F14C)(*(s32 *)(arg0 + 0x20) + 0x54, arg2, &b);

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&a, (s32)&b) != 0) {
        func_8012F568(1, 0x4017, arg3, 0x78, &b, D_801152A8);
        D_80126B9A = arg3;
        return 1;
    }
    return 0;
}


#include "common.h"

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32 func_8012B70C(s16 *a0, s16 *a1);
extern void func_80188B78(u8 *a0);
extern u8 D_801202A0[];

typedef struct { s16 vx, vy, vz, pad; } SV_80187A04;

void func_80187A04(void *a0)
{
    SV_80187A04 self;
    SV_80187A04 probe;
    s32 unused;
    u16 *p;
    s32 i;
    s32 dist0;
    s32 dist;
    s16 diff;

    func_8004914C((void *)(*(s32 *)((s32)a0 + 0x20) + 0x54));
    func_800491AC((void *)(*(s32 *)((s32)a0 + 0x20) + 0x54));

    self.vx = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x68);
    self.vy = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x6C);
    self.vz = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x70);

    probe.vx = 0;
    probe.vy = 0;
    probe.vz = -0x280;
    RotTransSV(&probe, &probe, &unused);

    dist0 = func_8012B70C((s16 *)&self, (s16 *)&probe);

    p = (u16 *)D_801202A0;
    i = 0;
    do {
        if (*p == 0x2A9) {
            probe.vx = p[3];
            probe.vy = p[5];
            probe.vz = p[7];
            dist = func_8012B70C((s16 *)&self, (s16 *)&probe);
            diff = dist - dist0;
            if (diff < 0) {
                diff = -diff;
            }
            if (diff < 0x80) {
                func_80188B78((u8 *)p);
            }
        }
        i = i + 1;
        p = (u16 *)((u8 *)p + 0x10C);
    } while (i < 0x60);
}


#include "common.h"

/* §176/§181 declaration audit against the destination TU
 * (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c), where func_80187B40's INCLUDE_ASM
 * sits at L5435 -- i.e. BEFORE every declaration listed below:
 *   L5182  extern void func_80187D68(void *a0);            <- copied verbatim
 *   L5184  extern void *D_801EFD70[4];                     <- copied verbatim
 *   L5978  extern s32 func_8012C194(void);                 <- copied verbatim
 *   L5979  extern void func_8001CD9C(s32 a0, void *a1);    <- copied verbatim
 *   L5980  extern void func_800233CC(void *a0, unsigned short a1);  <- copied verbatim
 *   L6200  typedef struct { u8 d[4]; } Blk4;
 *   L6205  extern Blk4 D_801ED994;                         <- SEE NOTE BELOW
 * D_801ED990 / D_801ED998 / D_801EFD80 / D_801EFD84 / D_801EFDC0 / D_801EFDC4 /
 * D_801EFE04 have no declaration anywhere in the TU, so they take the simplest
 * raw form (§181 law 4).
 *
 * THE D_801ED994 / Blk4 COLLISION (the reason the align-1 block-move types below
 * are BLOCK-scoped rather than file-scoped):
 *   The TU already owns the file-scope typedef name `Blk4` for exactly this
 *   symbol at L6200/L6205. Two anonymous struct types are never compatible in C,
 *   and re-spelling `typedef struct { u8 d[4]; } Blk4;` here is a hard error
 *   ("conflicting types for `Blk4'" -- verified against cc1 2.7.2), because this
 *   function lands at L5435, ahead of L6200.
 *   Measured with the pinned cc1: a BLOCK-scope `extern <local-type> D_801ED994;`
 *   that PRECEDES the file-scope `extern Blk4 D_801ED994;` downgrades the clash
 *   from an error to "warning: type mismatch with previous external decl", and
 *   the emitted code is unchanged (still lwl/lwr + swl/swr). File scope, or the
 *   reverse order, is a hard error. So the whole align-1 copy machinery lives
 *   inside the function body and touches nothing at file scope.
 */

extern s32 func_8012C194(void);
extern void func_8001CD9C(s32 a0, void *a1);
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_80187D68(void *a0);

extern void *D_801EFD70[4];
extern u8 D_801EFD80[];
extern u8 D_801EFD84[];
extern u8 D_801EFDC0[];
extern u8 D_801EFDC4[];
extern u8 D_801EFE04[];

void func_80187B40(void *a0)
{
    /* align-1 4-byte RGB+code block, block-scoped -- see the header note */
    typedef struct { u8 c[4]; } Blk4_80187B40;
    extern Blk4_80187B40 D_801ED990;
    extern Blk4_80187B40 D_801ED994;
    extern Blk4_80187B40 D_801ED998;

    register void *s4 __asm__("$20") = a0;  // !FAKE: pin $20 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 obj;
    s32 i;
    s32 sz;
    void **pp;
    u8 *p;

    func_800233CC(D_801EFD80, 0xC0);
    *(Blk4_80187B40 *)D_801EFD80 = D_801ED990;
    *(Blk4_80187B40 *)D_801EFD84 = D_801ED994;

    /* §179-F5 inverted: this must NOT be a for/while loop. loop.c hoists the
     * one-use HImode constant 0xC060 out of any real loop (movhi_internal2's
     * insn condition rejects `(set (mem:HI) (const_int != 0))`, so loop.c's
     * single-use substitution path fails and it falls through to the movable
     * threshold, which a ~20-insn loop always clears). The target keeps
     * `ori $v0,$zero,0xC060` INSIDE the loop while 0x1000 sits hoisted in $s3 --
     * that combination is only reachable with NO loop notes at all, i.e. a goto
     * loop (loop.c never runs, so nothing is hoisted and nothing is strength-
     * reduced) plus 0x1000 held in a variable initialised in the preheader. */
    i = 0;
    sz = 0x1000;
    pp = D_801EFD70;
loop:
    obj = func_8012C194();
    *pp = (void *)obj;
    if (obj != 0) {
        func_8001CD9C(obj, D_801EFD80);
        *(u16 *)(obj + 0x18) = sz;
        *(u16 *)(obj + 0x1A) = sz;
        *(u16 *)(obj + 0x2C) = 0xC060;
        *(u32 *)(obj + 0x4) |= 0x50000000;
    }
    i++;
    pp++;
    if (i < 4) {
        goto loop;
    }

    func_800233CC(D_801EFDC0, 0x120);
    *(Blk4_80187B40 *)D_801EFDC0 = D_801ED998;
    *(Blk4_80187B40 *)D_801EFDC4 = D_801ED994;
    obj = func_8012C194();
    *(void **)((s32)s4 + 0xD0) = (void *)obj;
    if (obj != 0) {
        func_8001CD9C(obj, D_801EFDC0);
        *(u16 *)(obj + 0x18) = 0x1000;
        *(u16 *)(obj + 0x1A) = 0x1000;
        *(u16 *)(obj + 0x2C) = 0xC060;
        *(u32 *)(obj + 0x4) |= 0x50000000;
    }

    p = &D_801EFDC0[0x40];
    func_800233CC(p, 0x100);
    *(Blk4_80187B40 *)&D_801EFDC0[0x40] = D_801ED998;
    *(Blk4_80187B40 *)D_801EFE04 = D_801ED994;
    obj = func_8012C194();
    *(void **)((s32)s4 + 0xD4) = (void *)obj;
    if (obj != 0) {
        func_8001CD9C(obj, p);
        *(u16 *)(obj + 0x18) = 0x1000;
        *(u16 *)(obj + 0x1A) = 0x1000;
        *(u16 *)(obj + 0x2C) = 0xC060;
        *(u32 *)(obj + 0x4) |= 0x50000000;
    }

    func_80187D68(s4);
}


#include "common.h"

/* func_80187D68 — ov_SC04_011 (split ov_SC04_011_jr_8017D494), 187 ins.
 *
 * Declarations copied VERBATIM from the destination TU:
 *   func_8004914C / func_800491AC / RotTransSV  (file scope, L2643-2645)
 *   func_80135004                               (file scope, L980)
 *   D_801EFD70                                  (L5184, `extern void *D_801EFD70[4];`)
 *   the DEF-side signature `void func_80187D68(void *a0)` (declared at L5410).
 *
 * Two byte-load-bearing levers:
 *  1. Loop 1 uses `(i + 1)` in the body with `i++` in the for-increment.  CSE
 *     merges them into `s0 = s1 + 1` / `s1 = s0` — the biv increment now has a
 *     dest register different from its source, so loop.c's basic_induction_var
 *     never recognises i as a biv and does NOT strength-reduce -(i<<7).  Writing
 *     `i = i + 1;` at the top of a do/while instead yields a giv
 *     (`addiu s0,s0,-128`) and a 1-instruction length drift.  Loop 2 keeps the
 *     ordinary biv shape, so its D_801EFD70 walk IS reduced (s2) — which is what
 *     the target has; `ang` must stay an explicit variable there (the closed form
 *     `-0x40 - i*0xC0` makes loop.c build a +0xC0 giv and then negate, +2 ins).
 *  2. The `p->0xC` store must precede the `p->0x4` read-modify-write.  With the
 *     0x4 RMW first, nothing separates the `sh` from the guarded reload and cse
 *     folds the reload into the stored register (sll/sra sign-extend instead of
 *     `lh 0xC($s0)`); the intervening `sw 0x4($s0)` is what keeps the reload.
 */

typedef struct { s16 vx, vy, vz, pad; } SV_80187D68;   /* 8 bytes, align 2 -> lwl/lwr copy */
typedef struct { u8 c[4]; } Blk4_80187D68;             /* 4 bytes, align 1 -> lwl/lwr copy */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32 func_80135004(s32 a0, void *a1, s32 a2);
extern void func_80188054();
extern void *D_801EFD70[4];
extern u8 D_801EFDC0[];
extern u8 D_801ED998[];
extern u8 D_801ED99C[];

void func_80187D68(void *a0)
{
    SV_80187D68 sv0;
    SV_80187D68 sv1;
    SV_80187D68 out;
    s32 flag;
    s32 i;
    s32 hit;
    s32 ang;
    void *p;
    s32 t;
    s32 b;

    func_8004914C((void *)(*(s32 *)((s32)a0 + 0x20) + 0x54));
    func_800491AC((void *)(*(s32 *)((s32)a0 + 0x20) + 0x54));

    sv1.vx = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x68);
    sv1.vy = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x6C);
    sv1.vz = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x70);

    /* The `i + 1` at the top plus the `i++` at the bottom CSE into
       `s0 = s1 + 1` / `s1 = s0` — a two-pseudo copy chain, which stops
       loop.c's basic_induction_var from recognising i as a biv at all, so
       -(i<<7) stays an explicit sll/negu instead of a strength-reduced giv. */
    for (i = 0; i < 7; i++) {
        sv0.vy = 0;
        sv0.vx = 0;
        sv0.vz = -((i + 1) << 7);
        RotTransSV(&sv0, &out, &flag);
        hit = func_80135004(1, &sv1, (s32)&out);
        if (hit != 0) {
            break;
        }
        sv1 = out;
    }

    for (i = 0, ang = -0x40; i < 4; i++) {
        p = D_801EFD70[i];
        if (p != NULL) {
            sv0.vx = 0;
            sv0.vy = 0;
            sv0.vz = ang;
            RotTransSV(&sv0, &sv0, &flag);
            *(s16 *)((s32)p + 0x8) = sv0.vx;
            *(s16 *)((s32)p + 0xA) = sv0.vy;
            *(s16 *)((s32)p + 0xC) = sv0.vz;
            t = *(s32 *)((s32)p + 0x4) & 0x7FFFFFFF;
            *(s32 *)((s32)p + 0x4) = t;
            if (hit != 0) {
                if (*(s16 *)((s32)p + 0xC) < out.vz) {
                    *(s32 *)((s32)p + 0x4) = t | 0x80000000;
                }
            }
        }
        ang -= 0xC0;
    }

    if (hit == 0) {
        p = *(void **)((s32)a0 + 0xD0);
        if (p != NULL) {
            *(s32 *)((s32)p + 0x4) = *(s32 *)((s32)p + 0x4) | 0x80000000;
        }
        p = *(void **)((s32)a0 + 0xD4);
        if (p != NULL) {
            *(s32 *)((s32)p + 0x4) = *(s32 *)((s32)p + 0x4) | 0x80000000;
        }
    } else {
        b = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x68);
        out.vx = ((((s32)out.vx - b) * 20) >> 4) + b;
        b = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x6C);
        out.vy = ((((s32)out.vy - b) * 20) >> 4) + b;
        b = *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x70);
        out.vz = ((((s32)out.vz - b) * 20) >> 4) + b;

        func_80188054(*(void **)((s32)a0 + 0xD0), &out);
        func_80188054(*(void **)((s32)a0 + 0xD4), &out);

        if (D_801EFDC0[0] == 0xFF) {
            *(Blk4_80187D68 *)D_801EFDC0 = *(Blk4_80187D68 *)D_801ED99C;
        } else {
            *(Blk4_80187D68 *)D_801EFDC0 = *(Blk4_80187D68 *)D_801ED998;
        }
    }
}


void func_80188054(short *a0, short *a1) {
    short *dst = a0;

    if (dst != NULL) {
        dst[4] = a1[0];
        dst[5] = a1[1];
        dst[6] = a1[2];
        *(s32 *)((s32)dst + 4) = *(s32 *)((s32)dst + 4) & 0x7FFFFFFF;
    }
}


#include "common.h"

/* Callee decls copied verbatim from the destination TU
 * (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c):
 *   func_8001CD9C  L5979 / L1816      func_800233CC  L5980 / L1563
 *   func_8018E6EC  definition L7507   func_8018E82C  L7579 / definition L7601
 *   RotMatrixZ     L5535/L8130        ApplyMatrixSV  L168/L3248/L7857
 *   rand           L954/L3182/...
 * Every data symbol is reached through an __asm__ label ALIAS so that this
 * function's private types can never collide with the TU's own file-scope
 * spellings (`extern u8 D_801EFE60;` L6086, `extern Blk4 D_801ED994;` L6205,
 * and the three mutually-incompatible block-scope D_800AE620 decls at
 * L5534/L7418/L7880).  Same assembler symbol, zero declaration surface. */
extern void func_8001CD9C(s32 a0, void *a1);
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8018E6EC(void);
extern void func_8018E82C(void *a0, void *a1, s16 a2);
extern void RotMatrixZ(s32 a0, void *a1);
extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 rand(void);

void func_80188094(s32 arg0) {
    typedef struct { u8 b[4]; } B4_80188094;                    /* align 1 -> ulw/usw */
    typedef struct { s16 m[3][3]; s32 t[3]; } M32_80188094;     /* 0x20, align 4 */
    typedef struct { u16 vx, vy, vz, pad; } SV_80188094;        /* 8, align 2 */

    extern M32_80188094 aAE620 __asm__("D_800AE620");
    extern B4_80188094 aED994 __asm__("D_801ED994");
    extern B4_80188094 aED9A0 __asm__("D_801ED9A0");
    extern B4_80188094 aED9A4 __asm__("D_801ED9A4");
    extern u8 aEFE60[] __asm__("D_801EFE60");
    extern B4_80188094 aEFE64 __asm__("D_801EFE64");
    extern B4_80188094 aEFEA4 __asm__("D_801EFEA4");

    M32_80188094 m;     /* sp+0x10 */
    SV_80188094 sv;     /* sp+0x30 */
    B4_80188094 blk;    /* sp+0x38 */
    s32 f;

    m = aAE620;
    blk = aED9A0;
    f = *(u16 *)(arg0 + 0x2C) & 1;
    func_8001CD9C(*(s32 *)(arg0 + 0x20), &aEFE60[f << 6]);
    *(u32 *)(*(s32 *)(arg0 + 0x20) + 0x4) |= 0x50000000;
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x2C) = 0xC040;
    if (f == 0) {
        func_800233CC(&aEFE60[0], 0x80);
        *(B4_80188094 *)&aEFE60[0] = aED994;
        aEFE64 = aED994;
        func_8018E6EC();
        func_8018E82C((void *)0, &blk, -8);
    } else {
        func_800233CC(&aEFE60[0x40], 0x10);
        *(B4_80188094 *)&aEFE60[0x40] = aED9A4;
        aEFEA4 = aED994;
        RotMatrixZ(rand() & 0xFFF, &m);
        sv.vx = 0xC0;
        sv.vz = 0;
        sv.vy = 0;
        ApplyMatrixSV(&m, &sv, &sv);
        *(u16 *)(arg0 + 0x6) += sv.vx;
        *(u16 *)(arg0 + 0xA) += sv.vy;
        *(u16 *)(arg0 + 0xE) += sv.vz;
        *(s32 *)(arg0 + 0x10) = -((s32)(s16)sv.vx << 12);
        *(s32 *)(arg0 + 0x14) = -((s32)(s16)sv.vy << 12);
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) = 0;
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0;
        *(s32 *)(arg0 + 0x1C) = 0xC;
    }
    *(u16 *)(arg0 + 0x2) += 1;
}


#include "common.h"

struct vec;

/* All decls copied verbatim from the destination TU
 * (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c):
 *   L6082 extern void func_8012931C(struct vec *a0);
 *   L6084 extern void func_801885C0(s32 a0);
 *   L6086-88 extern u8 D_801EFE60/61/62;
 *   L6521 extern u8 *func_801290DC(s32 a0, u8 *a1);
 *   L7631 void func_8018E89C(s32 a0)
 *   L7657 void func_8018E914(s32 a0, s32 a1)
 *   L7784 void func_8018EAB8(void)
 *   L954  extern s32 rand(void);
 */
extern void func_8012931C(struct vec *a0);
extern void func_801885C0(s32 a0);
extern void func_8018E89C(s32 a0);
extern void func_8018E914(s32 a0, s32 a1);
extern void func_8018EAB8(void);
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern s32 rand(void);

extern u8 D_801EFE60;
extern u8 D_801EFE61;
extern u8 D_801EFE62;

void func_801882F8(s32 a0)
{
    s16 out[4];
    s32 sub;

    sub = *(s32 *)(a0 + 0x30);
    if ((*(u16 *)(a0 + 0x2C) & 1) == 0) {
        if (*(s32 *)(sub + 0x94) < 3) {
            return;
        }
        func_801885C0(a0);
        func_8018E89C(a0 + 4);
        if (*(s32 *)(sub + 0x94) != 0x75) {
            u8 *p = &D_801EFE62;
            s32 c = *p;
            u8 w;

            if (c < 0xFF) {
                s32 n = c + 5;
                w = n;
                if (n >= 0x100) {
                    w = 0xFF;
                }
                D_801EFE61 = w;
                *p = w;
                D_801EFE60 = D_801EFE60 + 3;
            }
            if (*(s32 *)(sub + 0x94) == 0x19) {
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0;
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0;
            }
            if (*(s32 *)(sub + 0x94) == 0x29) {
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = 0x800;
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x1A) = 0x800;
                D_801EFE60 = 0xFF;
                D_801EFE61 = 0xFF;
                D_801EFE62 = 0xFF;
            }
            if (*(s32 *)(sub + 0x94) < 0x14) {
                *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) + 1;
                if ((*(s32 *)(a0 + 0x1C) & 1) == 0) {
                    u8 *r;
                    out[0] = *(u16 *)(a0 + 0x6);
                    out[1] = *(u16 *)(a0 + 0xA);
                    out[2] = *(u16 *)(a0 + 0xE);
                    r = func_801290DC(0x5C, (u8 *)out);
                    if (r != 0) {
                        *(s16 *)(r + 0x2C) = 1;
                    }
                } else {
                    func_8018E914(rand() & 0xFF0, 0x40);
                }
            }
            func_8018EAB8();
            return;
        }
    } else {
        s16 h = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18);
        s32 t;

        if (h < 0x1000) {
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x18) = h + 0x400;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) + 0x400;
        }
        func_8012931C((struct vec *)a0);
        t = *(s32 *)(a0 + 0x1C);
        if (t != 0) {
            *(s32 *)(a0 + 0x1C) = t - 1;
            return;
        }
    }
    *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
}



extern void (*D_801947F4[])(void);

void func_80188524(void *a0) {
    D_801947F4[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8002D4C8(s32 a0, s32 a1);

/* TU decl at L5304 says `void func_80188560(s32,s32)`; the asm copies $s0 -> $v0
 * before the epilogue, so the true return is s32 (same situation as impl_801833D4,
 * L5924). Define under the private C name with the __asm__ label -- the TU's own
 * idiom -- so nothing else in the file needs to change. */
s32 impl_80188560(s32 a0, s32 a1) __asm__("func_80188560");

s32 impl_80188560(s32 a0, s32 a1)
{
    s32 rec;

    rec = func_80132EF4(a0, 0x5C);
    if (rec != 0) {
        *(s32 *)((s32)rec + 0x34) = a0;
        *(s32 *)((s32)rec + 0x30) = a1;
    }
    func_8002D4C8(0x88A, 0);
    return rec;
}


#include "common.h"

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);

void func_801885C0(s32 param_1)
{
    s16 v[4];
    u16 out[4];
    s32 p = *(s32 *)(param_1 + 0x34);

    v[0] = 0;
    v[1] = 0x40;
    v[2] = -0x28;
    func_8004914C((void *)(*(s32 *)(p + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(p + 0x20) + 0x34));
    RotTransSV(v, v, out);
    *(s16 *)(param_1 + 6) = v[0];
    *(s16 *)(param_1 + 0xA) = v[1];
    *(s16 *)(param_1 + 0xE) = v[2];
}


void func_80188650(void *arg0) {
    extern void func_801888B8(u8 *a0);
    extern void func_8012B2CC(s32 a0);
    extern void func_8012B178(s32 a0, s32 a1);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern void func_8012AD44(s32 *a0, s16 a1);
    extern u16 D_80126B5E;
    extern u16 D_80126B66;
    u16 t = D_80126B5E;

    *(s16 *)((u8 *)arg0 + 0x100) = -0x788;
    *(u16 *)((u8 *)arg0 + 0xFE) = t;
    *(u16 *)((u8 *)arg0 + 0x102) = D_80126B66;
    func_801888B8((u8 *)arg0);
    func_8012B2CC((s32)arg0);
    func_8012B178((s32)arg0, (s32)0xFFD00000);
    func_8002D4C8(0x88C, 0);
    func_8012AD44((s32 *)arg0, 1);
}


#include "common.h"

extern void func_8001C924(void *a0, void *a1);
extern void func_80188AC4(s32 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012AD44(s32 *a0, s16 a1);
extern s32 D_801E8A1C;
extern s32 D_80194818;

void func_801886C4(s32 *a0) {
    s32 *s0 = a0;
    s32 value;

    func_8001C924((void *)s0[0x08], (void *)&D_801E8A1C);

    *(u16 *)((u8 *)s0[0x08] + 0x10) = 0;
    *(u16 *)((u8 *)s0[0x08] + 0x12) = 0;
    *(u16 *)((u8 *)s0[0x08] + 0x14) = 0;
    *(u16 *)((u8 *)s0[0x08] + 0x1A) = 0x800;

    value = (s32)&D_80194818 | 0x20000000;
    s0[0x16] = value;

    *(u16 *)((u8 *)s0 + 0x5C) = 0x8C00;

    func_80188AC4(s0);

    func_8002D4C8(0x8F8, 0);

    func_8012AD44(s0, 2);
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_80188764(s32 param_1) {
    *(s16 *)(param_1 + 0xAE) = -5;
    *(s32 *)(param_1 + 0x1C) = 0x100;
    func_8012AD44((s32 *)param_1, 3);
}



extern void (*D_80194840[])(void);

void func_80188794(void *a0) {
    D_80194840[*(u16 *)((s32)a0 + 0x2)]();
}


void func_801887D0(void *a0) {
    s32 v1;
    s16 val;

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u8 *)((s32)a0 + 0xC1) = 1;
    val = *(u16 *)(v1 + 0x1A) - 0x200;
    *(u16 *)((s32)a0 + 0x104) = val;
    if (val < 0x801) {
        *(u16 *)((s32)a0 + 0x104) = 0;
    }
    *(u16 *)((s32)a0 + 0x5C) &= 0xFFFE;
}


extern void func_8012C218(void *a0);

void func_80188818(void *a0) {
    if (*(s16 *)((s32)a0 + 0x104) < *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A)) {
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) -= 0x10;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) -= 0x80;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) -= 0x10;
    } else {
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(s16 *)((s32)a0 + 0x5E) = 0;
    }

    if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) <= 0) {
        func_8012C218(a0);
    }
}


#include "common.h"



void func_801888B8(u8 *a0)
{
    extern Mat32 D_800AE620;
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void RotMatrixY(s32 a0, void *a1);
    extern void func_8012F038(int param_1, short *param_2, short *param_3);
    extern s32 ratan2(s32 a0, s32 a1);

    Mat32 m;
    s16 out[4];
    void *mp;
    u8 *ang;
    u8 *sub;
    s32 v0;

    m = D_800AE620;
    m.t0 = *(s16 *)(a0 + 6);
    m.t1 = *(s16 *)(a0 + 0xA);
    m.t2 = *(s16 *)(a0 + 0xE);
    mp = &m;

    ang = *(u8 **)(a0 + 0x20);
    RotMatrixZ(*(s16 *)(ang + 0x14), mp);
    func_8012F038((int)mp, (s16 *)(a0 + 0xFE), out);
    v0 = -ratan2(out[2], out[0]);
    v0 -= 0x400;
    sub = *(u8 **)(a0 + 0x20);
    *(s16 *)(sub + 0x12) = v0 & 0xFFF;

    m = D_800AE620;

    ang = *(u8 **)(a0 + 0x20);
    RotMatrixY(*(s16 *)(ang + 0x12), mp);
    func_8012F038((int)mp, out, out);
    v0 = ratan2(out[2], out[1]);
    v0 += 0x400;
    sub = *(u8 **)(a0 + 0x20);
    *(s16 *)(sub + 0x10) = v0 & 0xFFF;
}


void func_80188A30(s32 a0) {
    extern u16 D_80194814;
    extern u16 D_80194816;
    extern u16 D_801F161E;
    extern s16 D_80126B98;
    s16 in[3];
    s16 out[3];

    in[1] = 0;
    in[0] = 0;
    out[1] = 0;
    out[0] = 0;
    in[2] = D_80194814;
    out[2] = D_80194816;
    if (func_8012DEB8((s32)a0, (s32)in, (s32)out) != 0) {
        __asm__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B t3_tus1)
        D_80126B98 = 0x18;
        if (*(s16 *)((s32)a0 + 0x106) == 0) {
            u16 cnt = D_801F161E;
            *(s16 *)((s32)a0 + 0x106) = 1;
            D_801F161E = cnt + 1;
        }
    }
}


extern s32 func_80132EF4(s32 a0, s32 a1);
extern int func_8018AD3C(s16 *param_1, s32 *param_2, s32 param_3);

void func_80188AC4(s32 *param_1) {
    s16 sp10[4];
    s32 *a0;

    a0 = (s32 *)func_80132EF4((s32)param_1, 0x22);
    if (a0 != NULL) {
        *(u16 *)((s32)(*(s32 *)((s8 *)a0 + 0x20)) + 0x2C) = 0xC020;
        *(u16 *)((s8 *)a0 + 0x34) = 0x7001;
        *(u16 *)((s8 *)a0 + 0xA) -= 0x10;
    }
    sp10[0] = *(u16 *)((s8 *)param_1 + 0x6);
    sp10[1] = *(u16 *)((s8 *)param_1 + 0xA) - 0x10;
    sp10[2] = *(u16 *)((s8 *)param_1 + 0xE);
    func_8018AD3C(sp10, 0, 8);
    func_8018AD3C(sp10, 0, 8);
    func_8018AD3C(sp10, 0, 8);
    func_8018AD3C(sp10, 0, 8);
}


#include "common.h"

/* Host TU (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c) already has these layouts
 * via ../shared/engine_core.h -> engine_types.h as Mat32, SV_8017D7C0_8017F340,
 * V32_8017D7C0_8017F340 -- byte identical. Renamed/redeclared here only because
 * match_one compiles standalone with -Iinclude (engine_core.h is not on that
 * path); on bank, drop these typedefs and use the TU's own names. */
typedef struct { s32 w0, w4, w8, wC; s16 h10, hpad; s32 t0, t1, t2; } Mat32_80188B78; /* 0x20 bytes */
   /* 8 bytes, align 2 */
  /* 16 bytes, align 4 */

/* §183: the TU spells these symbols differently at file scope, so reach them through
   __asm__ label ALIASES -- the TU's own established idiom (func_80188094, L6390):
   same assembler symbol, private type, zero declaration surface. */
extern Mat32_80188B78 aAE620_80188B78[1] __asm__("D_800AE620");
extern void RotMatrixY(s32 a0, void *a1);
extern void ApplyRotMatrix(void *v0, void *v1);
extern void func_8004914C(void *a0);
extern int rand(void);
extern int func_8018F68C(short *pos, int a1, int a2);
extern void func_8012C218(void *a0);
extern SV_8017D7C0_8017F340 D_80194850[];

void func_80188B78(u8 *a0)
{
    Mat32_80188B78 m;
    s32 i;
    s32 count;
    s16 v1;
    short buf[4];
    V32_8017D7C0_8017F340 rv;
    s32 vec[4];
    int p;

    m = aAE620_80188B78[0];

    v1 = *(s16 *)(*(u8 **)(a0 + 0x20) + 0x1A);
    count = 9;
    if (v1 < 0x801) {
        count = 4;
    } else if (v1 < 0xC01) {
        count = 8;
    }

    RotMatrixY(rand() & 0xFF0, &m);
    func_8004914C(&m);

    for (i = 0; i < count; i++) {
        u16 fE;

        ApplyRotMatrix(&D_80194850[i], &rv);

        buf[0] = *(u16 *)(a0 + 0x6) + rv.vx;
        buf[1] = *(u16 *)(a0 + 0xA) + rv.vy;
        fE = *(u16 *)(a0 + 0xE);
        buf[3] = 0x10;

        vec[0] = rv.vx << 15;
        vec[1] = (rv.vy * 3) << 13;
        vec[3] = 0;
        vec[2] = rv.vz << 15;

        buf[2] = fE + rv.vz;

        p = func_8018F68C(buf, (int)vec, 0xE08060);

        if (p != 0) {
            *(u16 *)(*(s32 *)(p + 0x20) + 0x2C) = 0xC010;
            *(s16 *)(*(s32 *)(p + 0x20) + 0x18) = (short)((rand() & 0x1F0) + 0x600);
        }
    }

    func_8012C218(a0);
}



extern void (*D_801948D0[])(void);

void func_80188D18(void *a0) {
    D_801948D0[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80181868();
    s32 func_80188D54(s32 arg0) {
        return ((s32 (*)(s32))func_80181868)(*(s32 *)(arg0 + 0x64));
    }


void func_80188D78(s32 a0)
{
    s32 delta;
    s32 scaled;
    s32 quotient;
    s8 *ptr;

    delta = *(s16 *)(a0 + 0xA) - *(s16 *)(*(s32 *)(a0 + 0x64) + 0xA);
    ptr = *(s8 **)(a0 + 0xCC);
    if ((u32)delta >= 0x601) {
        *(s32 *)(ptr + 4) |= 0x80000000;
    } else {
        scaled = (0x600 - delta) * 0x5000;
        quotient = scaled / 0x600;
        *(s32 *)(ptr + 4) &= 0x7FFFFFFF;
        *(s16 *)(ptr + 0x1C) = quotient;
        *(s16 *)(ptr + 0x1A) = quotient;
        *(s16 *)(ptr + 0x18) = quotient;
    }
}


#include "common.h"

extern s32 func_80143970(s32 a0);

s32 func_80188E00(s32 a0, void *a1)
{
    s16 *src = (s16 *)a1;
    s32 obj;
    s8 *v1;
    s16 t0, t1, t2;

    obj = func_80143970(a0);
    if (obj != 0) {
        v1 = *(s8 **)(obj + 0xCC);
        *(s16 *)(obj + 0) = 0x278;
        t0 = *src;
        *(s16 *)(v1 + 8) = t0;
        *(s16 *)(obj + 6) = t0;
        t1 = src[1] - 0x10;
        *(s16 *)(v1 + 0xA) = t1;
        *(s16 *)(obj + 0xA) = t1;
        t2 = src[2];
        *(s16 *)(v1 + 0xC) = t2;
        *(s16 *)(obj + 0xE) = t2;
        *(s16 *)(v1 + 0x10) = 0x400;
        *(s16 *)(v1 + 0x12) = 0;
        *(s16 *)(v1 + 0x14) = 0x200;
    }
    return obj;
}


#include "common.h"

/*
 * func_80188E88 (ov_SC04_011, 160 ins) — spawn/init dispatcher keyed on ent->0x70.
 *
 * Declarations (wave law 2) — every callee/global below is copied VERBATIM from the
 * destination TU src/ov_SC04_011/ov_SC04_011_jr_8017D494.c where it already exists:
 *   func_8012C1B8 / func_8012CAE4 / func_8001C214 / func_8012B23C /
 *   func_8012AD50 / rand            : L5780-L5785
 *   func_8001C810                   : L1546
 *   func_8018A42C                   : L6241
 *   D_801948F0                      : L5778 / L5889
 * The rest (D_801E6094, D_801E73D4, D_801E7944/68/8C, D_801EFEE8/EC/F0/F4) have no
 * existing declaration anywhere in the TU; typed by access width / data layout.
 *
 * Two non-obvious spellings, both byte-required (cookbook §20 / §165-10):
 *  - case 1 writes D_801EFEE8 through a POINTER (`s32 *q = &D_801EFEE8; *q = ...`)
 *    while D_801EFEEC is written as a bare global. That asymmetry is what gives
 *    `sw $v0, 0x0($a1)` next to `sw $zero, %lo(D_801EFEEC)($at)`.
 *  - cases 2..7 need the two indexed stores to stay in the assembler-macro form
 *    (`sw $x, %lo(sym)($at)`) while the func_8001C214 argument is a SEPARATE
 *    `la`+`addu`. Spelling the argument off D_801EFEF0 lets cse common the two and
 *    costs one instruction; spelling it as `&D_801EFEF4[i*2] - 4` (same address,
 *    different RTL base) keeps the streams distinct. It is also what supplies the
 *    target's `vars= 8` frame — there is no dead local here (§83c / §162i1).
 */

extern u8 D_801E6094[];
extern s32 D_801E689C;
extern void *D_801E73D4[];
extern u8 D_801E7944[];
extern u8 D_801E7968[];
extern u8 D_801E798C[];
extern s32 D_801948F0[];
extern s32 D_801EFEE8;
extern s32 D_801EFEEC;
extern void *D_801EFEF0[];
extern s32 D_801EFEF4[];

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8018A42C(void *a0, void *a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8012AD50(void *a0);
extern s32 rand(void);

void func_80188E88(void *a0)
{
    s32 ent = (s32)a0;
    s32 v0;
    s32 p;
    s32 i;
    s32 t;
    s32 *q;

    v0 = func_8012C1B8();
    *(s32 *)(ent + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)ent);
        return;
    }

    switch (*(s16 *)(ent + 0x70)) {
    case 0:
        func_8001C810(v0, (s32)D_801E6094);
        p = *(s32 *)(ent + 0x20);
        *(s32 *)(p + 0x4) |= 0x8040;
        p = *(s32 *)(ent + 0x20);
        *(u16 *)(p + 0x2C) |= 0x10;
        p = *(s32 *)(ent + 0x20);
        *(u16 *)(p + 0x1C) = 0x1100;
        *(u16 *)(p + 0x1A) = 0x1100;
        *(u16 *)(p + 0x18) = 0x1100;
        func_8018A42C((void *)ent, D_801E7944);
        *(u16 *)(ent + 0xA) += 1;
        goto done;
    case 1:
        q = &D_801EFEE8;
        D_801EFEEC = 0;
        *q = D_801E689C;
        func_8001C214(*(s32 *)(ent + 0x20), (s32)q);
        func_8018A42C((void *)ent, D_801E7968);
        *(u16 *)(ent + 0xA) += 1;
        goto done;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
        i = *(s16 *)(ent + 0x70) - 2;
        D_801EFEF4[i * 2] = 0;
        D_801EFEF0[i * 2] = D_801E73D4[i];
        func_8001C214(*(s32 *)(ent + 0x20), (s32)&D_801EFEF4[i * 2] - 4);
        func_8018A42C((void *)ent, &D_801E798C[i * 12]);
        func_8012B23C(ent);
        *(s32 *)(ent + 0x10) =
            (*(s16 *)(ent + 0x6) - *(s16 *)(*(s32 *)(ent + 0x64) + 0x6)) << 13;
        t = (*(s16 *)(ent + 0xA) - *(s16 *)(*(s32 *)(ent + 0x64) + 0xA)) << 15;
        *(s32 *)(ent + 0x14) = t;
        *(s32 *)(ent + 0xE0) = t;
        *(s32 *)(ent + 0x18) =
            (*(s16 *)(ent + 0xE) - *(s16 *)(*(s32 *)(ent + 0x64) + 0xE)) << 13;
        break;
    default:
        func_8001C214(*(s32 *)(ent + 0x20), D_801948F0[*(u16 *)(ent + 0x70) & 3]);
        p = *(s32 *)(ent + 0x20);
        *(u16 *)(p + 0x1C) = 0x500;
        *(u16 *)(p + 0x1A) = 0x500;
        *(u16 *)(p + 0x18) = 0x500;
        p = *(s32 *)(ent + 0x20);
        *(u16 *)(p + 0x2C) |= 0x10;
        func_8012B23C(ent);
        break;
    }

    *(u16 *)(ent + 0x106) = rand() & 0xF0;
    *(u16 *)(ent + 0x108) = rand() & 0xF0;
    *(s32 *)(ent + 0x1C) = *(s16 *)(ent + 0x70);
done:
    func_8012AD50((void *)ent);
}


extern void func_8012AD44(s32 *a0, s16 a1);

void func_80189108(s32 *a0) {
    a0[4] >>= 1;
    a0[5] = a0[0x38] >> 1;
    a0[6] >>= 1;
    func_8012AD44(a0, 2);
}



extern void (*D_80194904[])(void);

void func_8018914C(void *a0) {
    D_80194904[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_801E6898;
extern s32 D_801EFEE0[];
extern s32 D_801EFEE4;
extern u8 D_801E795C[];
extern void func_8001C924(void *a0, void *a1);
extern void func_8018A42C(void *a0, void *a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80189188(void *a0)
{
    s32 ent = (s32)a0;
    s32 *q;

    if (*(s16 *)(ent + 0x70) != 0) {
        return;
    }

    q = &D_801EFEE0[0];
    D_801EFEE4 = 0;
    *q = D_801E6898;
    func_8001C924(*(void **)(ent + 0x20), (void *)q);
    func_8018A42C((void *)ent, D_801E795C);
    *(u16 *)(ent + 0xA) += 1;
    *(s32 *)(ent + 0xCC) = func_8012C658(0x272, 1, ent);
    func_8012C658(0x272, 2, ent);
    func_8012C658(0x272, 3, ent);
    func_8012C658(0x272, 4, ent);
    func_8012C658(0x272, 5, ent);
    func_8012C658(0x272, 6, ent);
    func_8002D4C8(0x84C, 0);
}


#include "common.h"

extern s32 rand(void);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8002D4C8(s32 a0, s32 a1);
extern u16 D_80194910[];
extern u16 D_80194912[];
extern u16 D_80194914[];

void func_80189270(s32 arg0) {
    s32 off;
    s32 i;
    s32 s0;
    s32 bound;
    s16 rnd[3];
    s32 v1;

    bound = 6;
    i = 0;
    off = 0;
    while (i < bound) {
        s0 = func_8012C658(0x272, (rand() & 3) | 8, arg0);
        if (s0 != 0) {
            rnd[0] = *(u16 *)((u8 *)D_80194910 + off) + (rand() & 0x1F) - 0x10;
            rnd[1] = *(u16 *)((u8 *)D_80194912 + off);
            rnd[2] = *(u16 *)((u8 *)D_80194914 + off) + (rand() & 0x1F) - 0x10;
            *(u16 *)(s0 + 0x6) += (u16)rnd[0];
            *(u16 *)(s0 + 0xA) += (u16)rnd[1];
            *(u16 *)(s0 + 0xE) += (u16)rnd[2];
            *(s32 *)(s0 + 0x10) = rnd[0] << 13;
            v1 = 0xFFE78000 - ((rand() & 0x3F0) << 8);
            *(s32 *)(s0 + 0x14) = v1;
            *(s32 *)(s0 + 0xE0) = v1;
            *(s32 *)(s0 + 0x18) = rnd[2] << 13;
        }
        off += 8;
        i++;
    }
    func_8002D4C8(0x946, 0);
}


/* func_801893D4 - guard on obj+0x14 sign bit, then halfword compare:
   obj+0xA >= (*(s32*)(obj+0x64))->halfword_at_0xA - 0x40 */
s32 func_801893D4(s32 obj)
{
    if (*(s32 *)(obj + 0x14) < 0)
    {
        return 0;
    }
   return *(s16 *)(obj + 0xA) >= *(s16 *)(*(s32 *)(obj + 0x64) + 0xA) - 0x40;
}


#include "common.h"

extern void func_8001C924(void *a0, void *a1);
extern void func_8012C218(void *a0);
extern u8 D_801E793C[];

void func_80189410(void *a0)
{
    if (*(s16 *)((s32)a0 + 0x70) != 0) {
        return;
    }

    func_8001C924(*(void **)((s32)a0 + 0x20), (void *)&D_801E793C);

    *(u16 *)((s32)a0 + 0xA) += 2;

    if (*(s32 *)((s32)a0 + 0xCC) != 0) {
        func_8012C218(*(void **)((s32)a0 + 0xCC));
        *(s32 *)((s32)a0 + 0xCC) = 0;
    }
}


#include "common.h"

/* Sibling of func_80187940 (same TU, MATCHED) — same func_8012F14C / func_80135888 /
   func_8012F568 call skeleton, but here BOTH func_8012F14C inputs are locally-built
   Pt_80187940 structs (idx = arg0->0x70 into D_801948D8[]) rather than raw scalar args.
   match_one isolation has no -I to src/shared/engine_types.h (engine_core.h is not on
   that path); on bank, drop this local typedef — the destination TU already defines
   Pt_80187940 via its own `#include "../shared/engine_core.h"`. */


extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern s32  func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8   D_801152A8[];

s32 func_80189478(s32 arg0)
{
    extern u16 D_801948D8[];
    Pt_80187940 p1;
    Pt_80187940 p2;
    Pt_80187940 b;
    Pt_80187940 c;

    u16 v2;

    p1.x = -D_801948D8[*(s16 *)(arg0 + 0x70)];
    v2 = D_801948D8[*(s16 *)(arg0 + 0x70)];
    p2.y = 0;
    p1.y = 0;
    p2.z = 0;
    p1.z = 0;
    p2.x = v2;

    ((void (*)(s32, s32, void *))func_8012F14C)(*(s32 *)(arg0 + 0x20) + 0x54, (s32)&p1, &b);
    ((void (*)(s32, s32, void *))func_8012F14C)(*(s32 *)(arg0 + 0x20) + 0x54, (s32)&p2, &c);

    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&b, (s32)&c) != 0) {
        func_8012F568(1, 1, 0, 0x10, (s32)&c, (s32)D_801152A8);
        return 1;
    }
    return 0;
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern s32 rand(void);

extern u16 D_801E33A0[];
extern s16 D_80194978[][4];
extern s16 D_8019497A[][4];
extern s16 D_8019497C[][4];
extern u8 D_80194960[];
extern u8 D_80194940[];

void func_80189578(void *a0)
{
    s32 v0;
    s32 v1;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, (s32)D_801E33A0);

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x10;

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x1A) = 0x1400;

    if (*(s16 *)((s32)a0 + 0x70) != 0) {
        *(u16 *)((s32)a0 + 0x6) = D_80194978[*(s16 *)((s32)a0 + 0x70) - 1][0];
        *(u16 *)((s32)a0 + 0xA) = D_8019497A[*(s16 *)((s32)a0 + 0x70) - 1][0];
        *(u16 *)((s32)a0 + 0xE) = D_8019497C[*(s16 *)((s32)a0 + 0x70) - 1][0];
    }

    *(u8 *)((s32)a0 + 0xC0) = 1;
    *(s32 *)((s32)a0 + 0xBC) = (s32)D_80194960;
    *(s16 *)((s32)a0 + 0xAE) = -5;
    *(s32 *)((s32)a0 + 0x58) = (s32)D_80194940 | 0x20000000;
    *(u16 *)((s32)a0 + 0x5C) = 0x8C00;
    *(s32 *)((s32)a0 + 0xB4) = 0;
    *(u8 *)((s32)a0 + 0xC1) = 0;
    *(u8 *)((s32)a0 + 0x75) = 0xC;
    *(s32 *)((s32)a0 + 0xC4) |= 2;
    *(s32 *)((s32)a0 + 0x1C) = rand() & 0xF;
    func_8012AD50(a0);
}



extern void (*D_801949B0[])(void);

void func_801896BC(void *a0) {
    D_801949B0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_80132EF4(s32 a0, s32 a1);

void func_801896F8(s32 a0)
{
    s16 t;

    *(u8 *)(a0 + 0xC1) = 1;
    t = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) - 0x180;
    *(s16 *)(a0 + 0xFE) = t;
    if (t < 0x601) {
        *(s16 *)(a0 + 0xFE) = 0;
        *(s16 *)(a0 + 0x100) = 0x10;
    }
    *(s16 *)(a0 + 0xAE) = -1;
    *(u16 *)(a0 + 0x5C) &= 0xFFFE;
    func_80132EF4(a0, 0x79);
}


#include "common.h"

extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8018985C(void *a0, void *a1);
extern void func_8012C218(void *a0);
extern unsigned char D_80194950;

void func_80189764(void *a0) {
    if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) < 0x601) {
        *(s16 *)((s32)a0 + 0x100) -= 1;
        if (*(s16 *)((s32)a0 + 0x100) == 0) {
            func_80132EF4((s32)a0, 0x79);
        }
    }

    if (*(s16 *)((s32)a0 + 0xFE) < *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A)) {
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) -= 0x30;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) -= 0xC;
    } else {
        *(u8 *)((s32)a0 + 0xC1) = 0;
        *(s16 *)((s32)a0 + 0x5E) = 0;
        *(s16 *)((s32)a0 + 0xAE) = -5;
    }

    if (*(s16 *)((s32)a0 + 0xFE) != 0) {
        ((s32 (*)())func_8018985C)(a0, &D_80194950);
    }

    if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) <= 0) {
        func_8012C218(a0);
    }
}



typedef struct { s16 m[3][3]; s32 t[3]; } MATRIX_8018985C;
typedef struct { s16 vx, vy, vz, pad; } SVECTOR_8018985C;

extern u16 D_80126B5E;
extern u16 D_80126B66;
extern s32 func_80017DC4(void *a0, void *a1);
extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern u8  D_801152A8[];

s32 func_8018985C(void *a0, void *a1)
{
    MATRIX_8018985C mtx;
    SVECTOR_8018985C sv[4];

    sv[0].vx = D_80126B5E - *(u16 *)((s32)a0 + 6);
    sv[0].vz = D_80126B66 - *(u16 *)((s32)a0 + 0xE);

    func_80017DC4((void *)(*(s32 *)((s32)a0 + 0x20) + 0x18), &mtx);

    sv[1].vx = *(u16 *)((s32)a1 + 4);
    sv[2].vx = *(u16 *)((s32)a1 + 6);
    sv[1].vz = *(u16 *)((s32)a1 + 0xC);
    sv[2].vz = *(u16 *)((s32)a1 + 0xE);

    gte_SetRotMatrix(&mtx);
    gte_ldv0(&sv[1]);
    gte_rtv0();
    gte_stsv(&sv[1]);
    gte_SetRotMatrix(&mtx);
    gte_ldv0(&sv[2]);
    gte_rtv0();
    gte_stsv(&sv[2]);

    if (sv[0].vx > sv[1].vx && sv[0].vx < sv[2].vx &&
        sv[0].vz > sv[1].vz && sv[0].vz < sv[2].vz) {
        func_8012F568(1, 0x4001, 0, 0x14, (s32)&sv[3], (s32)D_801152A8);
        return 1;
    }
    return 0;
}



extern void (*D_801949B8[])(void);

void func_80189A24(void *a0) {
    D_801949B8[*(u16 *)((s32)a0 + 0x2)]();
}


extern u8 D_801EFF20[];

void * func_80189A60(void)
{
    extern u8 D_801EFF20[];
    s32 a0;
    s32 v1;
    v1 = (s32)D_801EFF20;
    for (a0 = 0; a0 < 0x4; a0++, v1 += 0x40) {
        if (*(u8 *)(v1 + 11) == 0) {
            return (u8 *)v1;
        }
    }
    return 0;
}


#include "common.h"

extern void func_800233CC(void *a0, unsigned short a1);
extern u8 D_801EFF20[];

void func_80189A98(void) {
    u8 *p;
    s32 i;

    p = D_801EFF20;
    for (i = 0; i < 4; i++) {
        func_800233CC(p, 0x40);
        p[0xB] = 0;
        p += 0x40;
    }
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8018A42C(void *a0, void *a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8012AD50(void *a0);

typedef struct {
    s32 unk0;
    s32 unk4;
} Rec_80189AEC;

extern s32 D_801E4928[];
extern s32 D_801E57E4[];
extern Rec_80189AEC D_801F0020[];
extern Rec_80189AEC D_801F00A0[];
extern u8 D_801E5888[];
extern u8 D_801E5948[];
extern u16 D_801949DC;
extern u16 D_801949E0[];
extern u16 D_801949F0;

void func_80189AEC(void *a0) {
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    if (*(s16 *)((s32)a0 + 0x70) < 0x10) {
        D_801F0020[*(s16 *)((s32)a0 + 0x70)].unk0 =
            D_801E4928[*(s16 *)((s32)a0 + 0x70)];
        D_801F0020[*(s16 *)((s32)a0 + 0x70)].unk4 = 0;
        func_8001C214(*(s32 *)((s32)a0 + 0x20),
                      (s32)&D_801F0020[*(s16 *)((s32)a0 + 0x70)]);

        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x50000000;

        func_8018A42C(a0, &D_801E5888[*(s16 *)((s32)a0 + 0x70) * 12]);

        if (*(s16 *)((s32)a0 + 0x70) == 0xF) {
            s32 t0;
            s32 t1;

            t1 = D_801949F0;
            t0 = (s32)&D_801949DC;
            *(u16 *)t0 = t1;
            t0 = t0 - 0xC;
            t1 = 0x10000000;
            t0 = t0 | t1;
            t1 = 0x40000000;
            t0 = t0 | t1;
            *(s32 *)((s32)a0 + 0x58) = t0;
            *(u16 *)((s32)a0 + 0x5C) = 0xCC00;
            *(u8 *)((s32)a0 + 0x75) = 2;
        }
        *(s16 *)((s32)a0 + 0xFE) = 1;
    } else {
        s32 j = *(s16 *)((s32)a0 + 0x70) - 0x10;

        s32 val = D_801E57E4[j];

        D_801F00A0[j].unk4 = 0;
        D_801F00A0[j].unk0 = val;
        func_8001C810(*(s32 *)((s32)a0 + 0x20), (s32)&D_801F00A0[j]);

        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x4) |= 0x8040;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) = 0x1008;

        func_8018A42C(a0, &D_801E5948[*(s16 *)((s32)a0 + 0x70) * 12]);

        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x28) = 0x1000180;
        *(s16 *)((s32)a0 + 0xFE) = 0;
        *(s32 *)((s32)a0 + 0x48) = *(s32 *)((s32)a0 + 0x48) >> 1;

        if (*(s16 *)((s32)a0 + 0x70) == 0x10) {
            s32 t0;
            s32 t1;

            t1 = 0x10000000;
            t0 = (s32)&D_801949E0[0];
            t0 = t0 | t1;
            t1 = 0x40000000;
            t0 = t0 | t1;
            *(s32 *)((s32)a0 + 0x58) = t0;
            *(u16 *)((s32)a0 + 0x5C) = 0xCC00;
            *(u8 *)((s32)a0 + 0x75) = 2;
        } else {
            *(u16 *)((s32)a0 + 0x5C) = 0;
        }
    }

    func_8012B23C((s32)a0);
    func_8012AD50(a0);
}


#include "common.h"

extern void func_80189EAC();
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012C218(void *a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern u16 D_801949DC;
extern u16 D_801949F2[];
extern u8 D_801949C0[];

void func_80189D38(void *a0)
{
    register s32 mode __asm__("$5") = 2;  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)

    if (*(s16 *)((s32)a0 + 0xFE) != 0) {
        ((void (*)())func_80189EAC)(a0, mode);
        {
            u16 t = *(u16 *)((s32)a0 + 0x70);
            if (t & 1) {
                D_801949DC = D_801949F2[(s16)t >> 1];
            }
        }
        func_8012C218(a0);
        func_8002D4C8(0x84C, 0);
    } else {
        *(s32 *)((s32)a0 + 0x58) = (s32)&D_801949C0 | 0x40000000;
        *(u16 *)((s32)a0 + 0x5C) = 0xCC00;
        *(u16 *)((s32)a0 + 0x84) = 0;
        *(s32 *)((s32)a0 + 0x1C) = ((*(s16 *)((s32)a0 + 0x70) - 0x10) << 5) + 0x10;
        func_8012AD44((s32 *)a0, mode);
    }
}


#include "common.h"

typedef struct {
    u16 value;
    u8 pad[14];
} Entry_D_801949C8;

extern void (*D_80194A04[])(void *);
extern Entry_D_801949C8 D_801949C8[];
extern u16 D_80126B62;
extern void func_8012C218(void *);

void func_80189DFC(void *a0) {
    u16 index;
    void (*handler)(void *);
    s16 idx;
    u16 value, field_0A_val;
    s16 field_0A;

    // Call handler function from array indexed by value at +0x2
    index = *(u16 *)(a0 + 0x2);
    handler = D_80194A04[index];
    handler(a0);

    // Check if value at +0x0 is zero
    if (*(u16 *)a0 == 0) {
        return;
    }

    // Check if byte at +0x74 is non-zero
    if (*(u8 *)(a0 + 0x74) != 0) {
        // Load s16 from +0xFE as index into D_801949C8
        idx = *(s16 *)(a0 + 0xFE);
        value = D_801949C8[idx].value;
        field_0A_val = *(u16 *)(a0 + 0xA);
        value--;
        D_80126B62 = field_0A_val + value;
    }

    // Check if value at +0xA is >= -0x3FF
    field_0A = *(s16 *)(a0 + 0xA);
    if (field_0A >= -0x3FF) {
        func_8012C218(a0);
    }
}


#include "common.h"

extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80189EAC(s32 arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        func_8012C658(0x276, i, arg0);
    }
}


extern void func_80189F6C();

void func_80189EFC(s32 arg0) {
    u16 arr[3];

    arr[0] = *(u16 *)(arg0 + 6) + (rand() & 0x3F) - 0x20;
    arr[1] = *(u16 *)(arg0 + 0xA) - 0x40;
    arr[2] = *(u16 *)(arg0 + 0xE) + (rand() & 0xFF) - 0x80;
    func_80189F6C(arg0, arr);
}


#include "common.h"

/* Callee decls copied verbatim from the destination TU
 * (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c):
 *   func_801290DC : L6521/L7315   rand : L954/L3182/L7316
 */
extern u8 *func_801290DC(s32 a0, u8 *a1);
extern s32 rand(void);

void func_80189F6C(void) {
    s32 s0;

    /* TU prototype is (s32, u8*) but this site sets up only $a0=0x22 —
     * §165-15/§17a-1 call-site cast keeps the bare jal. */
    s0 = (s32)((u8 *(*)(s32))func_801290DC)(0x22);
    if (s0 == 0) {
        return;
    }
    *(u16 *)(*(s32 *)(s0 + 0x20) + 0x2C) = 0xC020;
    *(s32 *)(s0 + 0x34) = 0x4001;
    *(s32 *)(s0 + 0x10) = ((rand() & 0x7FF0) - 0x4000) << 4;
    *(s32 *)(s0 + 0x18) = ((rand() & 0x7FF0) - 0x4000) << 4;
}



extern void (*D_80194A60[])(void);

void func_80189FDC(void *a0) {
    D_80194A60[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8018A074(s32 arg0);
extern void func_8001C924(void *a0, void *a1);
extern void func_8018A42C(void *a0, void *a1);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 D_801E30C4;
extern u8 D_801E5870[];

void func_8018A018(s32 arg0)
{
    func_8018A074((s32)arg0);
    func_8001C924(*(void **)((s32)arg0 + 0x20), (void *)&D_801E30C4);
    func_8018A42C((void *)arg0, (void *)D_801E5870);
    *(s32 *)((s32)arg0 + 0x58) = 0;
    func_8002D4C8(0x84C, 0);
}


extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8018A0E0(s32 arg0);

void func_8018A074(s32 arg0) {
    s32 i;
    s32 var;

    for (i = 0; i < 4; i++) {
        var = func_8012C658(0x256, i, arg0);
        if (var != 0) {
            func_8012C658(0x256, i + 4, var);
        }
    }
    func_8018A0E0(arg0);
}


#include "common.h"

void func_8018A0E0(s32 arg0)
{
    /* All declaration surface kept block-scope (house style, cf.
     * func_80188094): private types + __asm__ label aliases reach the
     * assembler symbols without touching the TU's own decls. */
    typedef struct { s32 w[8]; } Mtx_8018A0E0;  /* 0x20, align 4 */

    extern Mtx_8018A0E0 aAE620_8018A0E0 __asm__("D_800AE620");
    extern u8 a194A68_8018A0E0[] __asm__("D_80194A68");
    extern void RotMatrixZ(s32 a0, void *a1);
    extern s32 func_80132EF4(s32 a0, s32 a1);
    extern void func_800484EC(s32 a0, s32 a1, s32 a2);

    Mtx_8018A0E0 m;     /* sp+0x10 */
    s32 i;              /* s0 */
    s32 p;

    m = aAE620_8018A0E0;
    RotMatrixZ(-0x200, &m);
    for (i = 0; i < 6; i++) {
        p = func_80132EF4(arg0, 0x22);
        if (p != 0) {
            *(s32 *)(p + 0x34) = 0x6002;
            func_800484EC((s32)&m, (s32)a194A68_8018A0E0, p + 0x10);
        }
        RotMatrixZ(0x100, &m);
    }
}


#include "common.h"

/* Declarations copied VERBATIM from the destination TU
 * (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c):
 *   func_8012C1B8 / func_8012CAE4 / func_8001C214 / func_8012AD50 / rand : L5780-L5785
 *   func_8012B23C                                                        : L5783
 *   func_8018A42C                                                        : L6241
 *   D_801948F0                                                           : L5778
 * New (not present anywhere in the tree): D_80194A78, D_801E5810 —
 *   typed by access width (lw -> s32 table; 12-byte stride record block -> u8[],
 *   spelled like the TU's neighbouring `extern u8 D_801E57F8[];` at L6244).
 */
extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern void func_8018A42C(void *a0, void *a1);
extern s32 func_8012AD50(void *a0);
extern s32 rand(void);

extern s32 D_801948F0[];
extern s32 D_80194A78[];
extern u8 D_801E5810[];

void func_8018A1B4(void *a0) {
    s32 v0;
    s16 r[3];
    s32 p;

    v0 = func_8012C1B8();
    *(s32 *)(a0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    if (*(s16 *)(a0 + 0x70) < 4) {
        func_8001C214(v0, D_80194A78[*(s16 *)(a0 + 0x70)]);
        func_8018A42C(a0, (void *)&D_801E5810[*(s16 *)(a0 + 0x70) * 12]);
        func_8012B23C((s32)a0);

        *(s32 *)(a0 + 0x10) =
            -0x60000 - ((*(s16 *)(a0 + 0x6) - *(s16 *)(*(s32 *)(a0 + 0x64) + 0x6)) << 13);
        *(s32 *)(a0 + 0x14) =
            ((*(s16 *)(a0 + 0xA) - *(s16 *)(*(s32 *)(a0 + 0x64) + 0xA)) << 13) - 0x180000;
        *(s32 *)(a0 + 0x18) =
            ((*(s16 *)(a0 + 0xE) - *(s16 *)(*(s32 *)(a0 + 0x64) + 0xE)) << 13) - 0x80000;
    } else {
        func_8001C214(v0, D_801948F0[*(s16 *)(a0 + 0x70) & 3]);

        p = *(s32 *)(a0 + 0x20);
        *(u16 *)(p + 0x1C) = 0x300;
        *(u16 *)(p + 0x1A) = 0x300;
        *(u16 *)(p + 0x18) = 0x300;

        p = *(s32 *)(a0 + 0x20);
        *(u16 *)(p + 0x2C) = *(u16 *)(p + 0x2C) | 0x10;

        r[0] = (rand() & 0x3F) - 0x20;
        r[1] = (rand() & 0x3F) - 0x20;
        r[2] = (rand() & 0x3F) - 0x20;

        *(u16 *)(a0 + 0x6) = *(u16 *)(*(s32 *)(a0 + 0x64) + 0x6) + (u16)r[0];
        *(u16 *)(a0 + 0xA) = *(u16 *)(*(s32 *)(a0 + 0x64) + 0xA) + (u16)r[1];
        *(u16 *)(a0 + 0xE) = *(u16 *)(*(s32 *)(a0 + 0x64) + 0xE) + (u16)r[2];
        func_8012B23C((s32)a0);

        *(s32 *)(a0 + 0x10) = *(s32 *)(*(s32 *)(a0 + 0x64) + 0x10) + (r[0] << 14);
        *(s32 *)(a0 + 0x14) = *(s32 *)(*(s32 *)(a0 + 0x64) + 0x14) + (r[1] << 14);
        *(s32 *)(a0 + 0x18) = *(s32 *)(*(s32 *)(a0 + 0x64) + 0x18) + (r[2] << 14);
    }

    *(s16 *)(a0 + 0x106) = rand() & 0xF0;
    *(s16 *)(a0 + 0x108) = rand() & 0xF0;
    *(s32 *)(a0 + 0x1C) = *(s16 *)(a0 + 0x70);
    func_8012AD50(a0);
}



extern void (*D_80194A88[])(void);

void func_8018A3F0(void *a0) {
    D_80194A88[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018A42C(void *a0, void *a1) {
    *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)a1 + 0x0);
    *(u16 *)((s32)a0 + 0xA) = *(u16 *)((s32)a1 + 0x2);
    *(u16 *)((s32)a0 + 0xE) = *(u16 *)((s32)a1 + 0x4);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = *(u16 *)((s32)a1 + 0x6);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = *(u16 *)((s32)a1 + 0x8);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) = *(u16 *)((s32)a1 + 0xA);
}


void func_8018A47C(void *a0) {
        *(short *)((char *)a0 + 0xfc) = 1;
    }



extern void (*D_80194A90[])(void);

void func_8018A488(void *a0) {
    D_80194A90[*(u16 *)((s32)a0 + 0x2)]();
}


/* func_8018A4C4 — ov_SC04_011, TU src/ov_SC04_011/ov_SC04_011_jr_8017D494.c
 *
 * Spawn/init dispatcher keyed on ent->0x70: below 0x10 it reads an 8-byte record
 * out of D_80194A98 (f0/f2/f4 = s16 offsets, f6 = u16 flag word); at 0x10 and
 * above everything is randomised. Sibling shape: func_8018A8EC (same TU, L11255)
 * and func_8018A1B4 (L11083) — declarations copied VERBATIM from those blocks
 * (func_8012C1B8 / func_8012CAE4 / func_8001C214 / func_8012B23C / func_8012AD50
 * / rand / D_801948F0). D_80194A98 is new: typed u8[] and indexed by byte offset,
 * the TU's own spelling for a strided record block (cf. `extern u8 D_801E5810[];`).
 *
 * TWO byte-required levers, both regalloc/schedule, neither reachable by pins:
 *
 * 1. §48-A2, THE LOCAL-ALLOC $s0 OCCUPANT — `tbl` is declared INSIDE the if-arm.
 *    That makes it a single-block, call-crossing quantity, so LOCAL-alloc parks it
 *    in $s0 before global-alloc runs. Every global allocno that is live in that
 *    block (the ent copy, the object pointer) then conflicts with $s0 and rotates
 *    onto $s1/$s2, while `s0` — dead in the if-arm — is free to share $s0 with it.
 *    That is what produces `addu $s2,$v0,$zero / addu $s0,$s2,$zero` at entry and
 *    `sll $s0,$v1,3 / addu $s0,$s0,$v0` at the table. Hoisting `tbl` to function
 *    scope (one variable for both roles) swaps $s0<->$s2 everywhere and additionally
 *    lets dbr steal the beqz delay slot. With `tbl` block-scoped the match is
 *    PIN-FREE; six pin combinations over $16/$17/$18 were tried first and every one
 *    cost 2-4 instructions (a hard-reg local cannot be the destination of a
 *    two-operand add, so `s0 += base` always buys a temp plus a `move`).
 *
 * 2. §31 STATEMENT ORDER — `ent->0x1C = (s16)ent->0x70` is written LAST, after the
 *    0x18 store, even though the target emits its `sw` BEFORE the 0x18 chain. Put it
 *    third (its emission position) and sched2 hoists the whole statement above the
 *    0x14 store and then has nothing left to fill the `lh 0x4($s0)` load delay: +1 nop.
 *    Written last, its `lh`/`sw` pair is exactly the filler for the two load delays,
 *    and the trailing 0x18 store is what cross_jump merges into the join block's
 *    `jal rand` delay slot. Do not pre-schedule for gcc.
 */


extern s32 D_801948F0[];
extern u8  D_80194A98[];

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8012AD50(void *a0);
extern s32 rand(void);

void func_8018A4C4(void *a0)
{
    s32 ent = (s32)a0;
    s32 v0;
    s32 s0;

    v0 = func_8012C1B8();
    s0 = v0;
    *(s32 *)(ent + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)ent);
        return;
    }

    if (*(s16 *)(ent + 0x70) < 0x10) {
        s32 tbl = (s32)&D_80194A98[*(s16 *)(ent + 0x70) * 8];
        u16 idx;
        u16 flags;
        u16 merged;

        idx = *(u16 *)(tbl + 0x6) & 7;
        *(u16 *)(ent + 0xFE) = idx;
        func_8001C214(v0, D_801948F0[idx]);

        flags = *(u16 *)(tbl + 0x6) & 0xFFF0;
        merged = *(u16 *)(v0 + 0x2C) | 0x10;
        *(u16 *)(v0 + 0x1C) = flags;
        *(u16 *)(v0 + 0x1A) = flags;
        *(u16 *)(v0 + 0x18) = flags;
        *(u16 *)(v0 + 0x2C) = merged;

        *(u16 *)(ent + 0x6) = *(u16 *)(*(s32 *)(ent + 0x64) + 0x6) + *(u16 *)(tbl + 0x0);
        *(u16 *)(ent + 0xA) = *(u16 *)(*(s32 *)(ent + 0x64) + 0xA) + *(u16 *)(tbl + 0x2);
        *(u16 *)(ent + 0xE) = *(u16 *)(*(s32 *)(ent + 0x64) + 0xE) + *(u16 *)(tbl + 0x4);
        func_8012B23C(ent);

        *(s32 *)(ent + 0x10) = *(s16 *)(tbl + 0x0) * 3 << 10;
        *(s32 *)(ent + 0x14) = (*(s16 *)(tbl + 0x2) << 12) - 0x80000;
        *(s32 *)(ent + 0x18) = *(s16 *)(tbl + 0x4) * 3 << 10;
        *(s32 *)(ent + 0x1C) = *(s16 *)(ent + 0x70);
    } else {
        u16 merged;

        func_8001C214(s0, D_801948F0[rand() & 3]);

        merged = *(u16 *)(s0 + 0x2C) | 0x10;
        *(u16 *)(s0 + 0x1C) = 0x600;
        *(u16 *)(s0 + 0x1A) = 0x600;
        *(u16 *)(s0 + 0x18) = 0x600;
        *(u16 *)(s0 + 0x2C) = merged;

        *(u16 *)(ent + 0x6) = *(u16 *)(*(s32 *)(ent + 0x64) + 0x6) + (rand() & 0x7F) - 0x40;
        *(u16 *)(ent + 0xA) = *(u16 *)(*(s32 *)(ent + 0x64) + 0xA) + (rand() & 0x7F) - 0x40;
        *(u16 *)(ent + 0xE) = *(u16 *)(*(s32 *)(ent + 0x64) + 0xE) + (rand() & 0x7F) - 0x40;
        func_8012B23C(ent);

        *(s32 *)(ent + 0x10) = *(s32 *)(*(s32 *)(ent + 0x64) + 0x10) * 4 / 3;
        *(s32 *)(ent + 0x14) = *(s32 *)(*(s32 *)(ent + 0x64) + 0x14) * 4 / 3;
        *(s32 *)(ent + 0x18) = *(s32 *)(*(s32 *)(ent + 0x64) + 0x18) * 4 / 3;
    }

    *(u16 *)(ent + 0x106) = rand() & 0xF0;
    *(u16 *)(ent + 0x108) = rand() & 0xF0;
    func_8012AD50((void *)ent);
}



extern void (*D_80194B18[])(void);

void func_8018A748(void *a0) {
    D_80194B18[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018A784(s32 arg0) {
    s32 i;
    s32 r;

    for (i = 0; i < 0x10; i++) {
        r = func_8012C658(0x215, i, arg0);
        if (r != 0) {
            func_8012C658(0x215, 0x10, r);
        }
    }
}


#include "common.h"

/* @class: instruction-scheduling (SOLVED — natural statement order)
 * @lever: §31 statement-order. The first-pass draft hand-permuted the vel[]
 *   assignments (2,3,0,1) and hoisted buf[3] to try to force the schedule;
 *   that FIGHT with sched1 cost 23/65. The real source is the plain natural
 *   order vel[0..3] then buf[0..3] — gcc-2.7.2's list scheduler produces the
 *   target interleave (vel[2] chain hoisted, `addiu $a1,$sp,0x18` used as the
 *   lhu load-delay filler) all by itself. Do not pre-schedule for gcc.
 * @note: vel[2] = buf[2] << 13 emits sll16/sra3 (CSE substitutes the just-
 *   stored register value + combine folds the sign-extend into the shift),
 *   while vel[0] = buf[0] << 13 emits a real `lh` (its value died across the
 *   two intervening rand() calls). buf[1] reloads with `lhu` because its only
 *   use is truncated back to a short; buf[0] reloads with `lh` because the
 *   same load feeds the sign-sensitive << 13.
 */

extern int rand(void);
extern int func_8018F68C(short *pos, int a1, int a2);

void func_8018A7E8(s32 a0)
{
    short buf[4];
    s32 vel[4];
    s32 s0;
    s32 p;

    s0 = a0;

    buf[0] = (rand() & 0x7F) - 0x40;
    buf[1] = (rand() & 0x7F) - 0x40;
    buf[2] = (rand() & 0x7F) - 0x40;

    vel[0] = buf[0] << 13;
    vel[1] = 0;
    vel[2] = buf[2] << 13;
    vel[3] = 0xC000;

    buf[0] = buf[0] + *(u16 *)(s0 + 0x6);
    buf[1] = buf[1] + *(u16 *)(s0 + 0xA);
    buf[2] = buf[2] + *(u16 *)(s0 + 0xE);
    buf[3] = 0x10;

    p = func_8018F68C(buf, (s32)vel, 0xC0C040);
    if (p != 0) {
        *(s16 *)(*(s32 *)(p + 0x20) + 0x18) = (rand() & 0x1F0) + 0x600;
        *(s32 *)(*(s32 *)(p + 0x20) + 0x4) |= 0x50000000;
        *(u16 *)(*(s32 *)(p + 0x20) + 0x2C) = 0xC030;
    }
}


#include "common.h"

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    u16 f6;
} TableRec_80194A10;

extern TableRec_80194A10 D_80194A10[];
extern s32 D_801948F0[];

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B23C(s32 a0);
extern s32 func_8012AD50(void *a0);
extern s32 rand(void);

void func_8018A8EC(void *a0)
{
    register void *ent __asm__("$17") = a0;  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 v0;
    s32 s2;
    TableRec_80194A10 *tbl;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    s2 = v0;
    *(s32 *)((s32)ent + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(ent);
        return;
    }

    tbl = &D_80194A10[*(s16 *)((s32)ent + 0x70)];

    func_8001C214(s2, D_801948F0[tbl->f6 & 3]);

    {
        u16 flags = tbl->f6 & 0xFFF0;
        u16 merged = *(u16 *)((s32)s2 + 0x2C) | 0x10;
        *(u16 *)((s32)s2 + 0x1C) = flags;
        *(u16 *)((s32)s2 + 0x1A) = flags;
        *(u16 *)((s32)s2 + 0x18) = flags;
        *(u16 *)((s32)s2 + 0x2C) = merged;
    }

    *(u16 *)((s32)ent + 0x6) = *(u16 *)(*(s32 *)((s32)ent + 0x64) + 0x6) + (u16)tbl->f0;
    *(u16 *)((s32)ent + 0xA) = *(u16 *)(*(s32 *)((s32)ent + 0x64) + 0xA) + (u16)tbl->f2;
    *(u16 *)((s32)ent + 0xE) = *(u16 *)(*(s32 *)((s32)ent + 0x64) + 0xE) + (u16)tbl->f4;
    func_8012B23C((s32)ent);

    *(s32 *)((s32)ent + 0x10) = (s32)tbl->f0 << 14;
    *(s32 *)((s32)ent + 0x18) = (s32)tbl->f4 << 13;
    *(s32 *)((s32)ent + 0x14) = -(((rand() & 0xF) + 0x10) << 16);
    *(s16 *)((s32)ent + 0x106) = rand() & 0xF0;
    *(s16 *)((s32)ent + 0x108) = rand() & 0xF0;
    ((void (*)(void *))func_8012AD50)(ent);
}



extern void (*D_80194B24[])(void);

void func_8018AA34(void *a0) {
    D_80194B24[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);

void func_8018AA70(void *param_1)
{
    s16 sp10[3];

    func_8004914C((void *)(*(s32 *)((s32)param_1 + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)((s32)param_1 + 0x20) + 0x34));

    sp10[0] = -0x28;
    sp10[1] = 0x20;
    sp10[2] = -0x50;
    func_8018AAE4(param_1, sp10);

    sp10[0] = 0x28;
    func_8018AAE4(param_1, sp10);
}


#include "common.h"

extern void RotTransSV(void *a0, void *a1, void *a2);
extern u8 *func_8012913C(s32 a0);
extern int func_8018AD3C(s16 *param_1, s32 *param_2, s32 param_3);

void *func_8018AAE4(void *a0, void *a1)
{
    s16 pos[3];
    s32 vec[3];
    s16 unused[4];
    void *ent;
    void *p1;

    RotTransSV(a1, pos, unused);
    pos[1] = -0x778;

    p1 = *(void **)((s32)a0 + 0x20);
    vec[0] = (pos[0] - *(s32 *)((s32)p1 + 0x48)) << 11;
    vec[1] = -0x30000;

    p1 = *(void **)((s32)a0 + 0x20);
    vec[2] = (pos[2] - *(s32 *)((s32)p1 + 0x50)) << 11;

    ent = func_8012913C(0x22);

    if (ent != NULL) {
        *(u16 *)((s32)ent + 0x6) = (u16)pos[0];
        *(u16 *)((s32)ent + 0xA) = (u16)pos[1];
        *(u16 *)((s32)ent + 0xE) = (u16)pos[2];
        *(s32 *)((s32)ent + 0x10) = vec[0];
        *(s32 *)((s32)ent + 0x14) = vec[1];
        *(s32 *)((s32)ent + 0x18) = vec[2];
        *(u16 *)((s32)ent + 0x34) = 0x6002;
        *(u16 *)((s32)(*(s32 *)((s32)ent + 0x20)) + 0x2C) = 0xC010;
    }

    func_8018AD3C(pos, vec, 0x20);
    func_8018AD3C(pos, vec, 0x20);
    func_8018AD3C(pos, vec, 0x20);

    return ent;
}


#include "common.h"

extern void *func_8018AC50(void *a0, void *a1);

void func_8018AC00(void *param_1)
{
    s16 sp10[3];

    sp10[0] = -0x40;
    sp10[2] = -0x50;
    func_8018AC50(param_1, sp10);

    sp10[0] = 0x40;
    func_8018AC50(param_1, sp10);
}


#include "common.h"

void *func_8018AC50(void *a0, void *a1)
{
    s32 vec[3];
    s16 pos[3];
    void *ent;
    void *p;

    p = *(void **)((s32)a0 + 0x20);
    pos[0] = *(u16 *)a1 + *(s32 *)((s32)p + 0x48);
    pos[1] = -0x778;
    p = *(void **)((s32)a0 + 0x20);
    pos[2] = *(u16 *)((s16 *)a1 + 2) + *(s32 *)((s32)p + 0x50);
    vec[0] = *(s16 *)a1 << 11;
    vec[1] = -0x30000;
    vec[2] = 0;

    ent = func_8012913C(0x22);

    if (ent != NULL) {
        *(u16 *)((s32)ent + 0x6) = (u16)pos[0];
        *(u16 *)((s32)ent + 0xA) = (u16)pos[1];
        *(u16 *)((s32)ent + 0xE) = (u16)pos[2];
        *(s32 *)((s32)ent + 0x10) = vec[0];
        *(s32 *)((s32)ent + 0x14) = vec[1];
        *(s32 *)((s32)ent + 0x18) = vec[2];
        *(u16 *)((s32)ent + 0x34) = 0x6002;
        *(u16 *)((s32)(*(s32 *)((s32)ent + 0x20)) + 0x2C) = 0xC010;
    }

    func_8018AD3C(pos, vec, 0x20);
    return ent;
}


#include "common.h"

extern int rand(void);
extern int func_8018F68C(short *pos, int a1, int a2);

int func_8018AD3C(s16 *param_1, s32 *param_2, s32 param_3)
{
    short buf[4];
    s32 vec[4];
    int r;
    int p;

    r = rand();
    buf[0] = (param_1[0] + (r & 0x3F)) - 0x1F;
    r = rand();
    buf[1] = (param_1[1] + (r & 0x3F)) - 0x1F;
    r = rand();
    buf[2] = (param_1[2] + (r & 0x3F)) - 0x1F;
    buf[3] = (short)param_3;

    if (param_2 != NULL) {
        vec[0] = param_2[0] * 22 / 16;
        vec[1] = param_2[1];
        vec[2] = param_2[2] * 22 / 16;
        vec[3] = 0;
        p = func_8018F68C(buf, (int)vec, 0xE08060);
    } else {
        p = func_8018F68C(buf, 0, 0xE08060);
    }

    if (p != 0) {
        *(u16 *)(*(s32 *)(p + 0x20) + 0x2C) = 0xC080;
        *(s32 *)(*(s32 *)(p + 0x20) + 4) |= 0x50000000;
        r = rand();
        *(s16 *)(*(s32 *)(p + 0x20) + 0x18) = (short)((r & 0x1F0) + 0x600);
    }

    return p;
}


#include "common.h"

extern u8 D_80194B2C[];
extern s32 D_801948F0[];

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B21C(void *a0);
extern s32 func_8012AD50(void *a0);
extern s32 rand(void);

void func_8018AEA8(void *a0)
{
    s32 v0;
    s32 rec;

    if ((*(s32 *)((s32)a0 + 0x20) = v0 = ((s32 (*)(void))func_8012C1B8)()) == 0) {
        func_8012CAE4(a0);
        return;
    }

    rec = (s32)&D_80194B2C[*(s16 *)((s32)a0 + 0x70) * 8];

    func_8001C214(v0, D_801948F0[*(u16 *)(rec + 0x6) & 7]);

    {
        u16 flags = *(u16 *)(rec + 0x6) & 0xFFF0;
        *(u16 *)(v0 + 0x1C) = flags;
        *(u16 *)(v0 + 0x1A) = flags;
        *(u16 *)(v0 + 0x18) = flags;
        *(u16 *)(v0 + 0x2C) |= 0x10;
    }

    *(u16 *)((s32)a0 + 0x6) = *(u16 *)(rec + 0x0)
        + *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x68);
    *(u16 *)((s32)a0 + 0xA) = *(u16 *)(rec + 0x2)
        + *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x6C);
    *(u16 *)((s32)a0 + 0xE) = *(u16 *)(rec + 0x4)
        + *(s32 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x70);

    func_8012B21C(a0);

    *(s32 *)((s32)a0 + 0x10) = ((*(s16 *)(rec + 0x0) + (rand() & 0x1F)) - 0x10) << 14;
    *(s32 *)((s32)a0 + 0x14) = (*(s16 *)(rec + 0x2) - 0x48) << 14;
    *(s32 *)((s32)a0 + 0x18) = ((rand() & 0xF) - 8) << 14;
    *(u16 *)((s32)a0 + 0x106) = rand() & 0xF0;
    *(u16 *)((s32)a0 + 0x108) = rand() & 0xF0;
    *(s32 *)((s32)a0 + 0x1C) = *(s16 *)((s32)a0 + 0x70);
    func_8012AD50(a0);
}



extern void (*D_80194B5C[])(void);

void func_8018B024(void *a0) {
    D_80194B5C[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_8018B060(s32 arg0) {
    s32 i;

    for (i = 0; i < 6; i++) {
        func_8012C658(0x2dd, i, arg0);
    }
}


#include "common.h"

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern void ApplyRotMatrixLV(void *in, void *out);
extern int func_8018F68C(short *pos, int a1, int a2);
extern int rand(void);

void func_8018B0B0(void *param_1, void *param_2, void *param_3, u32 param_4)
{
    s16 buf[4];
    s32 tmp[4];
    s32 out[2];
    int p;

    func_8004914C((void *)(*(s32 *)((s32)param_1 + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)((s32)param_1 + 0x20) + 0x34));
    RotTransSV(param_2, buf, out);

    if ((u16)param_4 > 0x40) {
        param_4 = 0x40;
    }
    buf[3] = (s16)param_4;

    if (param_3 != NULL) {
        ApplyRotMatrixLV(param_3, tmp);
        p = func_8018F68C(buf, (int)tmp, 0xC0C040);
    } else {
        p = func_8018F68C(buf, 0, 0xC0C040);
    }

    if (p != 0) {
        *(s16 *)(*(s32 *)(p + 0x20) + 0x18) = (rand() & 0x1F0) + 0x600;
        *(s32 *)(*(s32 *)(p + 0x20) + 0x4) |= 0x50000000;
        *(u16 *)(*(s32 *)(p + 0x20) + 0x2C) = 0xC040;
    }
}


#include "common.h"

/* func_8018B1B4 (ov_SC04_011, ov_SC04_011_jr_8017D494) — MATCH, 81/81 ins
 *
 * Rebuilds the 8-slot 0x20-byte primitive table at D_801F00C0 from the caller's
 * handle table (arg0).  For each slot k: idx = D_80194B6A[k] selects a handle
 * word out of arg0; on a non-null handle the three u16 offsets D_80194B64/66/68
 * are added to the three s32 fields at *(handle+0x20)+0x68/0x6C/0x70 and stored
 * as halfwords at +0x00/+0x02/+0x04; then an 8-byte unaligned copy from
 * D_80194BA4[k] lands at +0x08, two 4-byte unaligned copies of D_801ED994 at
 * +0x10 and +0x14, three zero halfwords at +0x06/+0x18/+0x1A, and the 0x50000000
 * GPU tag word at +0x1C.  Tail: D_801F01C0 = D_801F01C4 = 0.
 *
 * ── THE LEVER THAT CLOSED IT (second-pass repair; pass 1 parked at 7/81) ──
 * Pass 1 had every instruction right and only the PREHEADER ORDER wrong: it
 * emitted the counter's `move $a3,zero` immediately after $t0's `la`, while the
 * target defers it to LAST, after every hoisted invariant and every giv init:
 *
 *     target:  la $t0,D_801F00C0 | la $t2,D_801ED994 | lui $t4,0x5000 |
 *              addiu $a2,$t0,0x1C | la $t1,D_80194BA4 | addu $a3,$zero,$zero
 *     pass 1:  la $t0,...        | addu $a3,$zero,$zero | la $t2,... | ...
 *
 * That is NOT schedulable and NOT permutable, and it is not §2-T2's "reorder the
 * C statements" case.  It is a STRUCTURAL fact about where loop.c emits things:
 *   - original preheader insns (a source biv's own init) come FIRST;
 *   - `move_movables` hoists invariants with emit_insn_before(loop_start)  → next;
 *   - `strength_reduce` emits each reduced giv's init with
 *     emit_iv_add_mult(bl->initial_value, …, loop_start) (loop.c:3879) → LAST.
 * So a register whose init sits AFTER the hoisted invariants can only be a
 * REDUCED GIV, never a source-level biv.  $a3 is therefore not `i` — it is
 * `n * 8` derived from a step-1 counter biv `n` that gcc then eliminates
 * (the exit test becomes the target's `slti $v0,$a3,0x40`).
 *
 *   ⇒ the whole fix is the two lines `n = 0;` / `i = n * 8;` replacing pass 1's
 *     `i = 0;` + `i += 8;`.  7 → 0.
 *
 * ── WHY `i = n * 8;` MUST BE ITS OWN STATEMENT ──
 * Writing `n * 8` inline at the four table subscripts (the obvious spelling)
 * costs 40+ instructions: with mult_val = 8 each `&SYM + n*8` becomes a
 * worth-while address giv in its own right and gets its OWN preheader
 * `la`/`addiu` register — six hoisted table pointers instead of the target's
 * assembler-macro `lui $at,%hi(SYM); addu $at,$at,$a3; lh %lo(SYM)($at)` form.
 * Naming the product creates a DEST_REG giv (mult 8, add 0) that combine_givs
 * can express every symbol-based address off — `plus(reg $a3, SYM)` IS a legal
 * MIPS address, i.e. exactly the macro form — so the four table reads consume no
 * register at all.  (D_80194BA4 still gets its own $t1 because the lwl/lwr pair
 * needs a plain base register; that giv is recorded after $a3, and bl->giv is a
 * PREPEND list, which is why the preheader shows $t1 before $a3.)
 * Increment order at the loop tail (`t1 += 8; a3 += 8; a2 += 0x20; t0 += 0x20`)
 * falls out of §164-34 for free: `n++` is written BEFORE `out += 0x20`, so n's
 * class precedes out's in loop_iv_list.
 *
 * ── KEPT FROM PASS 1 (byte-checked, do not "simplify") ──
 *  - `out` stays a raw s32 walked with `out += 0x20` and every field addressed as
 *    `*(T *)(out + K)`.  No named "entry" pointer: the $t0/$a2 split (base for
 *    +0x00, base+0x1C with negative displacements for the rest) is combine_givs'
 *    own anchor choice, and naming the second pointer folds or triples it.
 *  - The Blk8/Blk4 byte-array structs are what emit the unaligned lwl/lwr /
 *    swl/swr copies; Blk4 is this TU's existing idiom.
 *  - `sub` is re-loaded from `*(s32 *)(handle + 0x20)` before EACH of the three
 *    field reads (the target reloads it three times).
 *
 * ── DECLARATIONS (law 2 / §181) ──
 * The destination TU declares NONE of these nine symbols before line 5961, but it
 * DOES declare, at file scope further down (L6200/L6205), `typedef struct { u8
 * d[4]; } Blk4;` and `extern Blk4 D_801ED994;`.  A file-scope duplicate of either
 * is a hard C89 ERROR ("conflicting types for `Blk4'" — verified with the pinned
 * cc1).  So every declaration here is BLOCK-scoped and the two local struct
 * typedefs carry a per-function suffix (the TU's own house style, cf.
 * Blk4_8018B948 at L5990).  Verified by splicing this body into a scratch copy of
 * the TU and compiling the whole file with the pinned cc1: exit 0, and the
 * emitted body is instruction-for-instruction identical to the standalone
 * compile (only $L label numbers differ).  Warning delta vs the untouched TU is
 * exactly +2 — the `D_801ED994` type-mismatch pair, the same benign shape the TU
 * already carries for D_801EFC4C and D_80126B58.
 * The other in-flight card in this TU (func_8018B2F8) also block-scopes its
 * externs, so there is no file-scope collision between the two drafts.
 */

void func_8018B1B4(s32 arg0) {
    typedef struct { u8 d[4]; } Blk4_8018B1B4;
    typedef struct { u8 d[8]; } Blk8_8018B1B4;

    extern s16 D_80194B6A[];
    extern u16 D_80194B64[];
    extern u16 D_80194B66[];
    extern u16 D_80194B68[];
    extern u8  D_80194BA4[];
    extern Blk4_8018B1B4 D_801ED994;
    extern u8  D_801F00C0[];
    extern s16 D_801F01C0;
    extern s16 D_801F01C4;

    s32 n;
    s32 i;
    s16 idx;
    s32 handle;
    s32 sub;
    s32 out;

    out = (s32) D_801F00C0;
    n = 0;
    do {
        i = n * 8;
        idx = *(s16 *)((s32) D_80194B6A + i);
        handle = *(s32 *)((idx << 2) + arg0);
        if (handle != 0) {
            sub = *(s32 *)(handle + 0x20);
            *(s16 *)(out + 0x00) = *(u16 *)((s32) D_80194B64 + i) + *(s32 *)(sub + 0x68);
            sub = *(s32 *)(handle + 0x20);
            *(s16 *)(out + 0x02) = *(u16 *)((s32) D_80194B66 + i) + *(s32 *)(sub + 0x6C);
            sub = *(s32 *)(handle + 0x20);
            *(s16 *)(out + 0x04) = *(u16 *)((s32) D_80194B68 + i) + *(s32 *)(sub + 0x70);
            *(Blk8_8018B1B4 *)(out + 0x08) = *(Blk8_8018B1B4 *)((s32) D_80194BA4 + i);
            *(Blk4_8018B1B4 *)(out + 0x10) = D_801ED994;
            *(Blk4_8018B1B4 *)(out + 0x14) = D_801ED994;
            *(s16 *)(out + 0x18) = 0;
            *(s16 *)(out + 0x1A) = 0;
            *(s16 *)(out + 0x06) = 0;
            *(u32 *)(out + 0x1C) = 0x50000000;
        }
        n++;
        out += 0x20;
    } while (n < 8);
    D_801F01C0 = 0;
    D_801F01C4 = 0;
}


#include "common.h"

/* func_8018B2F8 (ov_SC04_011, ov_SC04_011_jr_8017D494) — MATCH, 122 ins
 *
 * Per-entry HUD/damage-flash ticker over the 8-slot 0x20-byte table at
 * D_801F00C0.  Head: if the D_801F01C0 slot counter is < 8 it either ticks the
 * D_801F01C4 delay down, or (delay expired) arms slot[n] (halfword at +6 = 0x240),
 * bumps the counter, reloads the delay from D_80194BAA[n] and fires SFX 0x8C1.
 * Loop: for each of the 8 slots whose arg0[D_80194B6A[k]] word is non-zero and
 * whose +6 field is armed, arg1==0 grows the two u16 sizes (+0x18/+0x1A) and the
 * three colour bytes (+0x10/+0x11/+0x12), arg1!=0 shrinks them with a clamp-at-0;
 * then func_8018F734 renders the slot.
 *
 * LEVERS (byte-checked against asm/.../func_8018B2F8.s):
 *
 *  1. THE PREHEADER-ORDER LEVER — A HIDDEN STRIDE-1 COUNTER BIV `j`, WITH THE
 *     BYTE INDEX `i = j * 8` AS A REDUCED GIV.  This is what makes the preheader
 *     emit `addiu $s0,$s2,0x10` (p) BEFORE `addu $s1,$zero,$zero` (i), which in
 *     turn decides which insn the `j` at 0x8018B358 duplicates into its delay
 *     slot.  Mechanism (loop.c, pinned 2.7.2):
 *       - `record_biv` PREPENDS its class (loop.c:4295-4297), so with source
 *         increments `j++, q += 0x20` the class list is [q, j].
 *       - `strength_reduce` walks that list (loop.c:3717) and emits each class's
 *         giv inits with `emit_iv_add_mult (..., loop_start)` (loop.c:3879) —
 *         each landing immediately BEFORE loop_start, i.e. stream order ==
 *         emission order.  Class q first ⇒ p's init; class j second ⇒ i's init.
 *       - `j` itself is then ELIMINATED (its only use is the exit test), so
 *         `j = 0` / `j++` vanish and the test becomes `slti $v0,$s1,0x40` on the
 *         reduced index giv — exactly the target's test.
 *       - Giv increments go before their own biv's increment insn, so the tail
 *         comes out `addiu $s1,$s1,8` / `addiu $s0,$s0,0x20` /
 *         `addiu $s2,$s2,0x20` — the target's order — for free.
 *     A plain `for (i = 0; i < 0x40; i += 8, q += 0x20)` makes `i` a SOURCE biv
 *     whose `i = 0` is emitted at its source position, i.e. BEFORE the giv init:
 *     the two preheader insns come out swapped (3 mismatches).  Making `p` a
 *     source biv instead (init before the loop, `p += 0x20` in the increment)
 *     costs a 6th saved register and 6 insns — all four increment-order
 *     permutations measured, all 128 ins / 116 mismatched.
 *
 *  2. D_801F00C6 is spelled as its OWN symbol (the .s's reloc name), not as
 *     D_801F00C0 + 6.  Writing it off the D_801F00C0 base lets cse fold it into
 *     the q register (addiu $v1,$s3,6) instead of the target's
 *     lui $at/addu $at,$v1/sh %lo(D_801F00C6) assembler-macro address.
 *
 *  3. `D_801F01C0++` — NOT `D_801F01C0 = n + 1`.  The self-referencing memory
 *     increment is what produces the target's two-insn `addu $a2,$v1,$zero` /
 *     `addiu $a2,$a2,1` pair (a pseudo set twice, so combine cannot fold it), and
 *     that pair is ALSO what pushes n out of $a1 into $v1 — which in turn lets
 *     sched2 hoist the D_801F01C0 load above the parameter saves (the whole
 *     prologue order) and gives the 0x38 frame.  Every other spelling collapses
 *     to one addiu, n lands in $a1, and 27 instructions drift.
 *
 *  4. `p` (the +0x10 sub-pointer) must be a GIV, i.e. assigned INSIDE the loop
 *     from the biv q — `p = q + 0x10;` as a body statement.  See lever 1.
 *
 *  5. The clamp needs TWO pseudos: `t = x - k; u = t; if (t < 0) u = 0;`.
 *     Without the $2/$3 pins gcc coalesces u into t and the target's
 *     `addu $v1,$v0,$zero` delay-slot copy degenerates to a nop (§178 — a
 *     copy-elision residual, not regalloc-perm).  `u = p[0];` reuses the RESULT
 *     variable as the load destination for the second clamp; that anti-dependence
 *     is what stops sched2 hoisting `lbu $v1,0($s0)` above the two `sb $v1`
 *     stores.
 *
 *  6. The unsigned bounds tests are cast `(u32)`: a plain `u16`/`u8` compare
 *     promotes to int and emits slti, the target has sltiu.
 *
 * DECLARATIONS (§181 / law 2): func_8002D4C8 is copied verbatim from the
 * destination TU's file scope (L58) and func_8018F734 from its definition at
 * L8430.  The four data symbols shared with this binary's other wave card
 * (func_8018B1B4 — D_80194B6A / D_801F00C0 / D_801F01C0 / D_801F01C4) are
 * declared in EXACTLY that card's scalar `extern s16 X;` form so the two drafts
 * cannot collide in one TU; the address arithmetic is done at the use site with
 * `(s32)&X + off`.  D_80194BAA and D_801F00C6 are touched by no other draft, and
 * their scalar form measurably breaks the match (123 ins / 115 mismatched), so
 * they keep the array spelling.  All eight symbols and their reloc OFFSETS were
 * re-checked against the target .s after MATCH (law 1c).
 */

/* declared at file scope in the destination TU (L58) — copied verbatim */
extern void func_8002D4C8(s32 a0, s32 a1);
/* defined later in the destination TU (L8430) — signature copied verbatim */
extern void func_8018F734(s16 *arg0);

/* spelled exactly as in func_8018B1B4's draft (same TU, same symbols) */
extern s16 D_80194B6A;
extern s16 D_801F00C0;
extern s16 D_801F01C0;
extern s16 D_801F01C4;
/* touched by no other draft in this TU */
extern u16 D_80194BAA[];
extern s16 D_801F00C6[];

void func_8018B2F8(s32 *arg0, s32 arg1)
{
    u8 *p;
    u8 *q;
    s32 i;
    s32 j;
    s32 n;
    s32 r;
    register s32 t __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 u;

    n = D_801F01C0;
    q = (u8 *)&D_801F00C0;

    if (n < 8) {
        if (D_801F01C4 != 0) {
            D_801F01C4 = D_801F01C4 - 1;
        } else {
            r = D_80194BAA[n * 4];
            D_801F00C6[n * 0x10] = 0x240;
            D_801F01C0++;
            D_801F01C4 = r;
            func_8002D4C8(0x8C1, 0);
        }
    }

    for (j = 0; j < 8; j++, q += 0x20) {
        i = j * 8;
        p = q + 0x10;
        if (arg0[*(s16 *)((s32)&D_80194B6A + i)] != 0) {
            if (*(s16 *)(p - 0xA) != 0) {
                if (arg1 == 0) {
                    if ((u32)*(u16 *)(p + 8) < 0x18) {
                        *(u16 *)(p + 8) = *(u16 *)(p + 8) + 3;
                        *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) + 0xC;
                    }
                    if ((u32)p[2] < 0xF0) {
                        p[2] = p[2] + 0x10;
                        p[1] = p[1] + 0x10;
                        p[0] = p[0] + 0xA;
                    }
                } else {
                    if (*(u16 *)(p + 8) != 0) {
                        *(u16 *)(p + 8) = *(u16 *)(p + 8) - 6;
                        *(u16 *)(p + 0xA) = *(u16 *)(p + 0xA) - 0x18;
                    }
                    if (p[2] != 0) {
                        t = p[2] - 0x20;
                        u = t;
                        if (t < 0) {
                            u = 0;
                        }
                        p[2] = u;
                        p[1] = u;
                        u = p[0];
                        t = u - 0x14;
                        u = t;
                        if (t < 0) {
                            u = 0;
                        }
                        p[0] = u;
                    }
                }
            }
            func_8018F734((s16 *)q);
        }
    }
}


#include "common.h"

typedef struct { u8 c[4]; } Blk4_8018B4E0;

extern void func_800233CC(void *a0, unsigned short a1);
extern s32 func_8012C194(void);
extern void func_8001CD9C(s32 a0, void *a1);
/* §183: the TU spells these symbols differently at file scope, so reach them through
   __asm__ label ALIASES -- the TU's own established idiom (func_80188094, L6390):
   same assembler symbol, private type, zero declaration surface. */
extern Blk4_8018B4E0 aED994_8018B4E0[1] __asm__("D_801ED994");
extern Blk4_8018B4E0 aEFD80_8018B4E0[1] __asm__("D_801EFD80");
extern Blk4_8018B4E0 aEFD84_8018B4E0[1] __asm__("D_801EFD84");

s32 func_8018B4E0(s32 a0) {
    s32 s2 = a0;
    s32 s0;

    func_800233CC((void *)aEFD80_8018B4E0, 0x100);

    aEFD80_8018B4E0[0] = aED994_8018B4E0[0];
    aEFD84_8018B4E0[0] = aED994_8018B4E0[0];

    s0 = func_8012C194();
    if (s0) {
        func_8001CD9C(s0, (void *)aEFD80_8018B4E0);

        *(u16 *)(s0 + 0x18) = 0xC00;
        *(u16 *)(s0 + 0x1A) = 0x1C00;
        *(u16 *)(s0 + 0x2C) = 0xC040;
        *(s32 *)(s0 + 0x4) |= 0x50000000;

        *(s16 *)(s0 + 0x8) = *(s32 *)(*(s32 *)(s2 + 0x20) + 0x68);
        *(s16 *)(s0 + 0xA) = *(s32 *)(*(s32 *)(s2 + 0x20) + 0x6C);
        *(s16 *)(s0 + 0xC) = *(s32 *)(*(s32 *)(s2 + 0x20) + 0x70);
    }

    return s0;
}


#include "common.h"

/* Externs copied verbatim from the destination TU
 * (src/ov_SC04_011/ov_SC04_011_jr_8017D494.c), sibling block for
 * func_8018B948 immediately following this function's INCLUDE_ASM slot
 * (L5978-5981), which shares the exact same three callees. */
extern s32 func_8012C194(void);
extern void func_8001CD9C(s32 a0, void *a1);
extern void func_800233CC(void *a0, unsigned short a1);

/* Same align-1 4-byte block-move idiom used elsewhere in this TU for
 * D_801ED994 (func_8018C764, L6200-6217): lwl/lwr + swl/swr, not memcpy. */
typedef struct { u8 d[4]; } Blk4_8018B5E4;
/* §183: the TU spells these symbols differently at file scope, so reach them through
   __asm__ label ALIASES -- the TU's own established idiom (func_80188094, L6390):
   same assembler symbol, private type, zero declaration surface. */
extern Blk4_8018B5E4 aED994_8018B5E4[1] __asm__("D_801ED994");
extern Blk4_8018B5E4 aEFD80_8018B5E4[1] __asm__("D_801EFD80");
extern Blk4_8018B5E4 aEFD84_8018B5E4[1] __asm__("D_801EFD84");

/* Not present in this TU yet; typed by access width (lb -> signed byte,
 * used in bltz/bgez sign tests as the loop's negative-sentinel scan). */
extern s8 D_80194BE4[];

void func_8018B5E4(s32 a0) {
    s32 i;
    s32 s1;
    s32 obj;
    s32 tag;

    func_800233CC((void *)aEFD80_8018B5E4, 0xC0);
    aEFD80_8018B5E4[0] = aED994_8018B5E4[0];
    aEFD84_8018B5E4[0] = aED994_8018B5E4[0];

    i = 0;
    tag = D_80194BE4[0];
    while (tag >= 0) {
        s1 = *(s32 *)(a0 + tag * 4);
        if (s1 != 0) {
            obj = func_8012C194();
            if (obj != 0) {
                func_8001CD9C(obj, (void *)aEFD80_8018B5E4);
                *(u16 *)(obj + 0x2C) = 0xC040;
                *(u32 *)(obj + 0x4) |= 0x50000000;
                *(u16 *)(obj + 0x18) = 0x1000;
                *(u16 *)(obj + 0x1A) = 0x1000;
                *(u16 *)(obj + 0x8) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x68);
                *(u16 *)(obj + 0xA) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x6C);
                *(u16 *)(obj + 0xC) = *(s32 *)(*(s32 *)(s1 + 0x20) + 0x70);
            }
            *(s32 *)(s1 + 0xCC) = obj;
        }
        i++;
        tag = D_80194BE4[i];
    }
}


extern u8 D_801EFD80[];
extern u8 D_801EFD81[];
extern s8 D_80194BE4[];

void func_8018B744(s32 *a0) {
    s32 i;
    s32 tag;
    s32 obj;
    s32 a1;
    s32 v1;

    v1 = D_801EFD80[2];
    if (v1 < 0x50) {
        tag = v1 + 3;
        v1 = tag;
        __asm__ __volatile__("" : "=r"(v1) : "0"(v1));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t3_tus1)
        if (tag >= 0x51) {
            v1 = 0x50;
        }
        D_801EFD81[0] = v1;
        D_801EFD80[2] = v1;
        D_801EFD80[0] = D_801EFD80[0] + 2;
    }
    i = 0;
    tag = D_80194BE4[0];
    while (tag >= 0) {
        obj = a0[tag];
        if (obj != 0) {
            a1 = *(s32 *)(obj + 0xCC);
            if (a1 != 0) {
                *(u16 *)(a1 + 0x8) = *(s32 *)(*(s32 *)(obj + 0x20) + 0x68);
                *(u16 *)(a1 + 0xA) = *(s32 *)(*(s32 *)(obj + 0x20) + 0x6C);
                *(u16 *)(a1 + 0xC) = *(s32 *)(*(s32 *)(obj + 0x20) + 0x70);
            }
        }
        i++;
        tag = D_80194BE4[i];
    }
}


extern s8 D_80194BE4[];

void func_8018B830(s32 *a0) {
    s32 i;
    s32 tag;
    s32 obj;
    s32 a1;
    s16 a2;
    u16 temp;

    i = 0;
    tag = D_80194BE4[0];
    while (tag >= 0) {
        obj = a0[tag];
        if (obj != 0) {
            a1 = *(s32 *)(obj + 0xCC);
            if (a1 != 0) {
                a2 = *(s16 *)(a1 + 0x18);
                if (a2 < 0x5000) {
                    temp = *(u16 *)(a1 + 0x1A);
                    *(s16 *)(a1 + 0x18) = a2 + 0x100;
                    *(u16 *)(a1 + 0x1A) = temp + 0x100;
                }
            }
        }
        i++;
        tag = D_80194BE4[i];
    }
}


extern void func_80016714(void *a0, s32 a1);
extern s8 D_80194BE4[];

void func_8018B8C0(void *a0) {
    s32 s1;
    s32 i;
    s32 tag;
    s32 ptr;
    void *p;

    s1 = (s32)a0;
    i = 0;
    tag = D_80194BE4[0];
    while (tag >= 0) {
        ptr = *(s32 *)(s1 + tag * 4);
        if (ptr != 0) {
            p = *(void **)(ptr + 0xCC);
            if (p != 0) {
                func_80016714(p, 0x38);
            }
        }
        i++;
        tag = D_80194BE4[i];
    }
}


#include "common.h"

/* Externs needed by func_8018B948 */
extern s32 func_8012C194(void);
extern void func_8001CD9C(s32 a0, void *a1);
extern void func_800233CC(void *a0, unsigned short a1);
extern u8 D_801EFEA0[];

/* §160a: the target's tail copy is lwl/lwr + swl/swr (align-1 block move),
 * NOT a memcpy call -- and this TU declares memcpy three times with
 * conflicting signatures (L81/L1518/L1524), so naming memcpy here would
 * either hard-error or (if it slipped through) lower to `jal memcpy`,
 * which does not match the target's inline copy at all (TU note at
 * func_8018E1F0, L5311-5327). Route it through an align-1 struct assign
 * instead -- block-scoped so it cannot collide with anything file-scope. */
typedef struct { u8 c[4]; } Blk4_8018B948;
extern Blk4_8018B948 D_801ED9B4;

s32 func_8018B948(void) {
    s32 obj;
    u8 *ptr;

    obj = func_8012C194();
    if (obj) {
        ptr = D_801EFEA0;
        func_8001CD9C(obj, ptr);

        *(u16 *)(obj + 0x2C) = 0xC010;
        *(u32 *)(obj + 0x4) |= 0x50000000;

        func_800233CC((void *)ptr, 0x40);

        *(Blk4_8018B948 *)ptr = D_801ED9B4;
    }

    return obj;
}


extern u16 D_80194BEC[];

void func_8018B9D4(void *a0, void *a1)
{
    s32 sp10;
    s32 sp14;
    void *s0;
    void *s1;

    s0 = a0;
    s1 = a1;
    if (s0 != 0 && s1 != 0) {
        func_8004914C((void *)(*(s32 *)((s32)s0 + 0x20) + 0x34));
        func_800491AC((void *)(*(s32 *)((s32)s0 + 0x20) + 0x34));
        RotTransSV((void *)D_80194BEC, (void *)((s32)s1 + 8), &sp10);
    }
    func_8018BB44();
}


void func_8018BA44(s32 param_1, s32 param_2) {
    *(u16 *)(param_2 + 8) = *(u16 *)(param_1 + 6) + *(u16 *)(param_1 + 0x50);
    *(u16 *)(param_2 + 10) = *(u16 *)(param_1 + 10) + *(u16 *)(param_1 + 0x52);
    *(u16 *)(param_2 + 12) = *(u16 *)(param_1 + 14) + *(u16 *)(param_1 + 0x54);
    func_8018BB44();
}


extern u8 D_801EFEA0[];
extern u8 D_801EFEA1;
extern u8 D_801EFEA2;

void func_8018BA9C(void) {
    D_801EFEA0[0] = 0xF0;
    D_801EFEA1 = 0xF0;
    D_801EFEA2 = 0x80;
}


extern u8 D_801EFEA0[];
extern u8 D_801EFEA1;
extern u8 D_801EFEA2;

void func_8018BAC4(void) {
    u8 *pa;
    s32 t;
    register s32 r __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t3_tus1)
    register s32 x __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t3_tus1)

    pa = &D_801EFEA0[0];
    x = *(u8 *)pa;
    if (x != 0) {
        t = x - 0x18;
        r = t;
        if (t < 0) {
            r = 0;
        }
        *pa = r;
    }

    pa = &D_801EFEA1;
    x = *(u8 *)pa;
    if (x != 0) {
        t = x - 0x18;
        r = t;
        if (t < 0) {
            r = 0;
        }
        *pa = r;
    }

    pa = &D_801EFEA2;
    x = *(u8 *)pa;
    if (x != 0) {
        t = x - 0xD;
        r = t;
        if (t < 0) {
            r = 0;
        }
        *pa = r;
    }
}


void func_8018BB44(void) {
    extern u8 sBB44_A0 __asm__("D_801EFEA0");
    extern u8 sBB44_A1 __asm__("D_801EFEA1");
    extern u8 sBB44_A2 __asm__("D_801EFEA2");
    extern u8 sBB44_A3 __asm__("D_801EFEA3");
    u8 *flag;

    flag = &sBB44_A3;
    if (*flag == 0) {
        sBB44_A0 -= 3;
        sBB44_A1 -= 5;
        sBB44_A2 -= 7;
        if (sBB44_A2 < 0x61) {
            *flag = 1;
        }
    } else {
        sBB44_A0 += 3;
        sBB44_A1 += 5;
        sBB44_A2 += 7;
        if (sBB44_A2 >= 0xE0) {
            *flag = 0;
        }
    }
}


#include "common.h"

extern int rand(void);
extern int func_8018F68C(short *pos, int a1, int a2);

void func_8018BC08(void)
{
    short buf[4];
    s32 vec[4];
    int r;
    int p;
    int i;

    for (i = 0; i < 0x20; i++) {
        r = rand();
        buf[0] = (r & 0x3F0) + 0x300;
        r = rand();
        buf[1] = (r & 0x1F0) - 0xA80;
        r = rand();
        buf[2] = (r & 0x1F0) + 0x1800;
        r = rand();
        buf[3] = (r & 0x1F) + 0x50;
        r = rand();
        vec[0] = ((r & 0xF) - 8) << 15;
        r = rand();
        vec[2] = ((r & 0xF) - 8) << 15;
        vec[1] = 0x40000;
        vec[3] = 0;

        p = func_8018F68C(buf, (int)vec, 0xC0C040);
        if (p != 0) {
            r = rand();
            *(s16 *)(*(s32 *)(p + 0x20) + 0x18) = (r & 0x1F0) + 0x500;
            *(s32 *)(*(s32 *)(p + 0x20) + 4) |= 0x50000000;
            *(u16 *)(*(s32 *)(p + 0x20) + 0x2C) = 0xC040;
        }
    }
}


#include "common.h"

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern void ApplyRotMatrixLV(void *in, void *out);
extern s32 func_80132EF4(s32 a0, s32 a1);

extern u16 D_80194BF4[];
extern u16 D_80194BFC[];

void func_8018BD18(s32 a0)
{
    s32 v0;
    s32 v1;
    u16 v[4];
    u16 out[4];

    if (a0 == 0) {
        return;
    }

    v0 = func_80132EF4(a0, 0x22);

    func_8004914C((void *)(*(s32 *)(a0 + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(a0 + 0x20) + 0x34));

    RotTransSV(&D_80194BF4, v, out);

    *(u16 *)(v0 + 0x6) = v[0];
    *(u16 *)(v0 + 0xA) = v[1];
    *(u16 *)(v0 + 0xE) = v[2];
    v1 = *(s32 *)(v0 + 0x20);
    *(u16 *)(v1 + 0x2C) = 0xC008;
    *(u16 *)(v0 + 0x34) = 0x6001;

    ApplyRotMatrixLV(&D_80194BFC, (void *)(v0 + 0x10));

    *(s32 *)(v0 + 0x14) += -0x40000;
}



extern void (*D_80194C0C[])(void);

void func_8018BDCC(void *a0) {
    D_80194C0C[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001C1E4(void *a0, s32 a1);
extern void func_801875D8(void *a0, s32 a1, s32 a2);
extern void func_80187698(void *a0);
extern s32 func_8012AD50(void *a0);

extern u8 D_801EA9FC;
extern u8 D_801EFD50;

void func_8018BE08(void *a0) {
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(v0, (s32)&D_801EA9FC);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) |= 0x10;
    *(s16 *)((s32)a0 + 0xA) = 0x30;
    *(s16 *)((s32)a0 + 0xE) = -0x28;
    *(s16 *)((s32)a0 + 0x6) = 0;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = 0xC0;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) = 0x400;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) = 0x400;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) = 0x400;
    func_8001C1E4(*(void **)((s32)a0 + 0x20),
                  *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20));
    func_801875D8(&D_801EFD50, 0x160, 0x18F);
    func_80187698(a0);
    func_8012AD50(a0);
}


#include "common.h"

extern void func_8012B2CC(s32 a0);
extern s32 func_8012C1B8(void);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001C1E4(void *a0, s32 a1);
extern void func_8001C924(void *a0, void *a1);
extern s32 func_8012AD50(void *a0);
extern void func_80187B40(void *a0);

extern u8 D_801E9634;
extern u8 D_801EA2A4;

void func_8018BEEC(void *a0)
{
    s32 s0;

    func_8012B2CC((s32)a0);

    if (*(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) < 0x1000) {
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x18) += 0x400;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1A) += 0x400;
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x1C) += 0x400;
        return;
    }

    func_8001C924(*(void **)((s32)a0 + 0x20), (void *)&D_801E9634);

    s0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0xCC) = s0;
    if (s0 != 0) {
        func_8001C214(s0, (s32)&D_801EA2A4);
        *(u16 *)(s0 + 0x2C) |= 0x10;
        *(s32 *)(s0 + 0x4) |= 0x50000000;
        *(u16 *)(s0 + 0x8) = *(u16 *)((s32)a0 + 0x6);
        *(u16 *)(s0 + 0xA) = *(u16 *)((s32)a0 + 0xA);
        *(u16 *)(s0 + 0xC) = *(u16 *)((s32)a0 + 0xE);
        *(u16 *)(s0 + 0x10) = *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10);
        func_8001C1E4((void *)s0, *(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20));
    }

    func_80187B40(a0);
    func_8012AD50(a0);
}


extern void func_8012B414(int a0);
extern void func_80187D68(void *a0);
extern void func_8018778C(void *a0);
extern void func_80187A04(void *a0);

void func_8018C024(void *a0)
{
    s32 v1;

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(s16 *)(v1 + 0x14) = *(u16 *)(v1 + 0x14) + 0x100;
    func_8012B414((int)a0);
    func_80187D68(a0);
    func_8018778C(a0);
    func_80187A04(a0);
}


#include "common.h"
struct vec;

extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);
extern void func_801885C0(s32 a0);

extern u8 D_801EFE60;
extern u8 D_801EFE61;
extern u8 D_801EFE62;

void func_8018C07C(s32 arg0) {
    s16 v;
    u8 *p;

    func_8012931C((struct vec *)arg0);
    v = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18);
    if (v >= 0x400) {
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) = v - 0x400;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) - 0x400;
        if ((*(u16 *)(arg0 + 0x2C) & 1) == 0) {
            p = &D_801EFE60;
            *p -= 8;
            D_801EFE61 -= 0x20;
            D_801EFE62 -= 0x30;
            func_801885C0(arg0);
        }
    } else {
        func_801292C8((u8 *)arg0);
    }
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 D_801E81A4;
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern s32 D_80194800;
extern s32 D_80194828;
extern s32 D_80194808;
extern void func_80188650(void *a0);

/* Second-pass repair notes (SCHEDULE-REORDER, sched2 LUID tie-break).
 *   - `ent` must be a SECOND pseudo tied to $a0 (the call argument), not the $s0
 *     parameter copy: the tail's stores address off $a0 while the 0x6 store uses
 *     $s0.  `(s32)a0 + zr` with zr pinned to $0 defeats copy-propagation and emits
 *     the target's `addu $a0,$s0,$zero` for free (dropping it costs 1 ins).
 *   - The two zero-byte `__asm__ volatile("")` fences are the actual lever.  The
 *     residual was NOT reachable by statement order: gcc-2.7.2 sched2 ranks by
 *     priority, then potential-hazard, then LUID (= sched1's OUTPUT order), so no
 *     source permutation (~4000 byte-tested) could flip `lw 0xC4` vs `lhu 0x12(sp)`
 *     or sink the `ori` past the `li 1`.  Fencing the block splits it into three
 *     scheduling regions, which pins those three groups in source order.
 *   - `one` is split out of the 0xC0 store so the `li 1` and the `sb` can land 3
 *     slots apart (the fence would otherwise hold them adjacent).
 * Byte-verified MATCH (69 ins) with tools/match_one.py.
 */
void func_8018C14C(void *a0)
{
    s32 v0;
    s32 v1;
    u16 v[4];
    u16 out[4];

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, (s32)&D_801E81A4);

    v1 = *(s32 *)((s32)a0 + 0x20);
    *(u16 *)(v1 + 0x2C) |= 0x10;

    func_8004914C((void *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x34));
    func_800491AC((void *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x34));

    RotTransSV(&D_80194800, v, out);

    *(s16 *)((s32)a0 + 0x6) = v[0];
    {
        register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B t3_tus2)
        s32 ent = (s32)a0 + zr;
        s32 v2;
        s32 t1;
        s32 one;

        *(s16 *)(ent + 0xA) = v[1];
        t1 = *(u32 *)(ent + 0xC4);
        one = 1;
        __asm__ volatile("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B t3_tus2)
        t1 |= 2;
        v2 = v[2];
        *(u8 *)(ent + 0xC0) = one;
        *(s32 *)(ent + 0xBC) = (s32)&D_80194828;
        *(s16 *)(ent + 0xAE) = -1;
        *(u32 *)(ent + 0xC4) = t1;
        *(s32 *)(ent + 0x58) = (s32)&D_80194808 | 0x40000000;
        *(s32 *)(ent + 0xB4) = 0;
        *(u8 *)(ent + 0xC1) = 0;
        *(s16 *)(ent + 0x5C) = 0;
        *(u8 *)(ent + 0x75) = 2;
        *(s16 *)(ent + 0xE) = v2;

        func_80188650((void *)ent);
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_801888B8(u8 *a0);
extern s32 func_8018AD3C(s16 *a0, s32 *a1, s32 a2);
extern void func_801886C4(s32 *a0);
extern void func_80188A30(s32 a0);

void func_8018C260(s32 a0) {
    s16 sp10[4];
    s32 obj;
    u16 v0;

    obj = *(s32 *)(a0 + 0x20);
    v0 = *(u16 *)(obj + 0x14);
    *(u16 *)(obj + 0x14) = v0 + 0x100;

    func_8012AD80(a0);
    func_801888B8((u8 *)a0);

    sp10[0] = *(u16 *)(a0 + 0x6);
    sp10[1] = *(u16 *)(a0 + 0xA);
    sp10[2] = *(s16 *)(a0 + 0xE) + 0x20;

    func_8018AD3C(sp10, NULL, 8);
    func_8018AD3C(sp10, NULL, 8);

    if (*(s16 *)(a0 + 0xA) >= -0x780) {
        func_801886C4((s32 *)a0);
    } else {
        func_80188A30(a0);
    }
}


#include "common.h"

extern s32 func_8018985C(void *a0, void *a1);
extern void func_80188764(s32 param_1);
extern s32 D_80194818;

void func_8018C310(void *a0)
{
    void *s0 = a0;
    s32 obj = *(s32 *)((s32)s0 + 0x20);

    *(u16 *)(obj + 0x1A) += 0x800;

    ((s32 (*)())func_8018985C)(a0, &D_80194818);

    if (*(s16 *)(*(s32 *)((s32)s0 + 0x20) + 0x1A) >= 0x1800) {
        func_80188764((s32)s0);
    }
}


extern void func_8012BEE8(u8 *a0);
extern void func_8012C218(void *a0);
extern void func_80133298(s32 *a0);
extern s32 func_8018985C(void *a0, void *a1);
extern s32 D_80194818;

void func_8018C378(void *arg0)
{
    if (((s32 (*)(s32))func_8012BEE8)((s32)arg0) != 0) {
        func_8012C218(arg0);
        return;
    }
    if (*(s32 *)((s32)arg0 + 0x1C) < 0x18) {
        *(s16 *)((s32)arg0 + 0x5C) = 0;
        if (*(s32 *)((s32)arg0 + 0x1C) & 1) {
            *(s32 *)(*(s32 *)((s32)arg0 + 0x20) + 4) |= 0x80000000;
        } else {
            *(s32 *)(*(s32 *)((s32)arg0 + 0x20) + 4) &= 0x7FFFFFFF;
        }
    } else {
        if (*(u8 *)((s32)arg0 + 0x74)) {
            func_80133298((s32 *)arg0);
            ((s32 (*)())func_8018985C)(arg0, &D_80194818);
        }
    }
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C2C4(s32 a0);
extern s16 D_80194898;
extern s32 func_8012AD50(void*);

void func_8018C440(void *a0)
{
    register void *s0 __asm__("$16") = a0;  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 v0 = func_8012C1B8();

    *(s32 *)((u8 *)s0 + 0x20) = v0;

    if (!v0) {
        func_8012CAE4(s0);
    } else {
        func_8001C2C4(v0);
        *(s32 *)((u8 *)s0 + 0x58) = (s32)&D_80194898;
        *(s16 *)((u8 *)s0 + 0x5C) = 0x800;
        *(s16 *)((u8 *)s0 + 0x6) = 0x500;
        *(s16 *)((u8 *)s0 + 0xA) = -0x780;
        *(s16 *)((u8 *)s0 + 0xE) = 0x1820;
        ((void (*)(void *))func_8012AD50)(s0);
    }
}


#include "common.h"

void func_8018C4BC(s32 arg0)
{
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u16 D_80126B58;
    extern s32 func_80178B18(s32 param_1, s32 param_2);
    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern s32 D_801948A8;

    u16 v1 = *(u16 *)(arg0 + 0x34);

    switch (v1) {
    case 0:
        if ((*(s16 *)&D_80126B66) < 0x14FF)
            return;
        if ((*(s16 *)&D_80126B62) >= -0x780)
            return;
        if ((u16)(D_80126B58 - 2) < 2)
            return;
        func_80178B18(arg0, (s32)&D_801948A8);
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        break;
    case 1:
        if (((int (*)(s32))func_80178970)(arg0) == 0)
            return;
        ((void (*)(s32))func_80178D18)(arg0);
        *(u16 *)(arg0 + 0x34) = *(u16 *)(arg0 + 0x34) + 1;
        break;
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8018A7E8(s32 a0);
extern void func_80189108();
extern s32 func_801893D4(s32 a0);
extern s32 func_80189478(s32 a0);

void func_8018C58C(s32 a0) {
    s32 s0;
    s32 ptr;
    s32 v0;
    s32 v1;

    s0 = a0;

    v1 = *(s16 *)(s0 + 0x70);
    if (v1 < 2) {
        if (v1 >= 0) {
            return;
        }
    }

    func_8012AD80(a0);

    ptr = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(s0 + 0x106);
    v0 = *(u16 *)(ptr + 0x10);
    v0 = v0 + v1;
    *(u16 *)(ptr + 0x10) = (u16)v0;

    ptr = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(s0 + 0x108);
    v0 = *(u16 *)(ptr + 0x14);
    v0 = v0 + v1;
    *(u16 *)(ptr + 0x14) = (u16)v0;

    if ((*(s32 *)(s0 + 0x1C) & 3) == 0) {
        func_8018A7E8(a0);
    }

    v0 = *(s32 *)(s0 + 0x1C);
    v0 = v0 + 1;
    *(s32 *)(s0 + 0x1C) = v0;

    if (func_801893D4(a0) != 0) {
        func_80189108(a0);
    }

    func_80189478(a0);
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern s32 func_80189478(s32 a0);
extern s32 func_801893D4(s32 a0);
extern void func_8012BEE8(u8 *a0);
extern void func_8012C218(void *a0);

void func_8018C64C(s32 param_1)
{
    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        func_8012AD80(param_1);
        func_80189478(param_1);
        if (func_801893D4(param_1) != 0) {
            *(s32 *)(param_1 + 0x1C) = 0x10;
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        }
        break;
    case 1:
        if (((s32 (*)(s32))func_8012BEE8)((s32)param_1) != 0) {
            func_8012C218((void *)param_1);
        } else if (*(s32 *)(param_1 + 0x1C) & 1) {
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x80000000;
        } else {
            *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) &= 0x7FFFFFFF;
        }
        break;
    }
}


extern s32 func_8018985C(void *a0, void *a1);
    extern unsigned char D_80194950;
    void func_8018C72C(void *a0) {
        if (*(unsigned char *)((char *)a0 + 0x74)) {
            ((s32 (*)())func_8018985C)(a0, &D_80194950);
        }
    }


#include "common.h"

typedef struct { u8 d[4]; } Blk4;

extern void *func_80189A60(void);
extern void func_801292C8(u8 *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern Blk4 D_801ED994;
extern Blk4 D_801ED9A8;

void func_8018C764(s32 arg0) {
    s32 s0;

    s0 = (s32) func_80189A60();
    if (s0 == 0) {
        func_801292C8((u8 *)arg0);
    }
    *(u8 *)(s0 + 0xB) = 1;
    *(Blk4 *)(s0 + 0x0) = D_801ED994;
    *(Blk4 *)(s0 + 0x4) = D_801ED9A8;
    func_8001CD50(*(s32 *)(arg0 + 0x20), s0);
    *(s32 *)(arg0 + 0x34) = s0;
    *(u32 *)(*(s32 *)(arg0 + 0x20) + 0x4) =
        *(u32 *)(*(s32 *)(arg0 + 0x20) + 0x4) | 0x50000000;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x10) = 0xC00;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) =
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = 0x400;
    *(u16 *)(arg0 + 0x2) = *(u16 *)(arg0 + 0x2) + 1;
}


void func_8018C838(s32 arg0) {
    s16 v;
    u8 *p;

    p = (u8 *)*(s32 *)(arg0 + 0x34);
    *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) += 0xA0;
    v = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18);
    if (v >= 0x1200) {
        p[0xB] = 0;
        func_801292C8((u8 *)arg0);
    } else {
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = v;
        *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x1E) += 0x20;
        p[5] -= 5;
        p[6] -= 8;
    }
}


void func_8018C8CC(void) {
}

extern void func_8012BEE8(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern void func_80189EFC(s32 a0);

void func_8018C8D4(void *a0)
{
    if (((s32 (*)(s32))func_8012BEE8)((s32)a0) != 0) {
        if (*(s16 *)((s32)a0 + 0x84) == 0) {
            func_8002D4C8(0x84C, 0);
            *(s16 *)((s32)a0 + 0x84) = *(u16 *)((s32)a0 + 0x84) + 1;
        }
        func_8012AD80((s32)a0);
        if (*(s16 *)((s32)a0 + 0xFE) == 0) {
            func_80189EFC((s32)a0);
        }
    }
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8018A42C(void *a0, void *a1);
extern s32 func_8012AD50(void *a0);
extern u8 D_801E29B4[];
extern u8 D_801E57F8[];
extern u8 D_80194A50[];

void func_8018C94C(void *a0) {
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 t0;
    s32 t1;

    *(s32 *)(a0 + 0x20) = v0 = func_8012C1B8();

    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)D_801E29B4);
        func_8018A42C(a0, (void *)D_801E57F8);

        t0 = (s32)D_80194A50;
        t1 = 0x40000000;
        t0 = t0 | t1;
        *(s32 *)(a0 + 0x58) = t0;
        *(u16 *)(a0 + 0x5C) = 0xCC00;
        *(u8 *)(a0 + 0x75) = 0x2;

        t1 = *(s32 *)(a0 + 0x20);
        t0 = *(u16 *)(t1 + 0x2C);
        t0 = t0 | 0x10;
        *(u16 *)(t1 + 0x2C) = t0;

        t1 = *(s32 *)(a0 + 0x20);
        *(u16 *)(t1 + 0x1C) = 0x1100;
        *(u16 *)(t1 + 0x1A) = 0x1100;
        *(u16 *)(t1 + 0x18) = 0x1100;

        func_8012AD50(a0);
    }
}


void func_8018C9FC(void) {
}

#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8018A7E8(s32 a0);

void func_8018CA04(s32 arg0) {
    register s32 a0 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
    register s32 a1 __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)
    u16 val;

    // First update
    a0 = *(s32 *)(arg0 + 0x20);
    val = *(u16 *)(arg0 + 0x106);
    *(u16 *)(a0 + 0x10) = *(u16 *)(a0 + 0x10) + val;

    // Second update
    a1 = *(s32 *)(arg0 + 0x20);
    val = *(u16 *)(arg0 + 0x108);
    *(u16 *)(a1 + 0x14) = *(u16 *)(a1 + 0x14) + val;

    func_8012AD80(arg0);

    if ((*(s32 *)(arg0 + 0x1C) & 0x3) == 0) {
        func_8018A7E8(arg0);
    }

    *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;

    if (*(s16 *)(arg0 + 0xA) >= -0x3FF) {
        func_8012C218((void *)arg0);
    }
}


extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

extern u16 D_801E1AF4[];

void func_8018CA98(void *a0)
{
    s32 v0;

    v0 = func_8012C1B8();
    *(s32 *)((s32)a0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, (s32)D_801E1AF4);
    func_8012AD50(a0);
}


#include "common.h"

extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8018A784();

void func_8018CAF0(void *a0) {
    s32 s0 = (s32)a0;
    s32 mask;
    u16 v0;
    s16 h;
    s32 p;


    if ((*(u16 *)(s0 + 0x34)) == 0) {
        h = *(s16 *)(s0 + 0xFC);
        if (h != 0) {
            mask = (s32)0x80000000;
            p = *(s32 *)(s0 + 0x20);
            *(s32 *)(p + 4) = *(s32 *)(p + 4) | mask;

            func_8018A784((void *)s0);

            v0 = *(u16 *)(s0 + 0x34);
            v0 = v0 + 1;
            *(u16 *)(s0 + 0x34) = v0;

            func_8002D4C8(0x7E2, 0);
        }
    }
}


extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8018A7E8(s32 a0);

void func_8018CB68(s32 arg0) {
    register s32 a0 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
    register s32 a1 __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)
    u16 val;

    a0 = *(s32 *)(arg0 + 0x20);
    val = *(u16 *)(arg0 + 0x106);
    *(u16 *)(a0 + 0x10) = *(u16 *)(a0 + 0x10) + val;

    a1 = *(s32 *)(arg0 + 0x20);
    val = *(u16 *)(arg0 + 0x108);
    *(u16 *)(a1 + 0x14) = *(u16 *)(a1 + 0x14) + val;

    func_8012AD80(arg0);

    if (*(s16 *)(arg0 + 0x70) < 0x10) {
        if (*(s32 *)(arg0 + 0x1C) & 1) {
            func_8018A7E8(arg0);
        }

        *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg0 + 0x1C) + 1;
    }

    if (*(s16 *)(arg0 + 0xA) >= -0x3FF) {
        func_8012C218((void *)arg0);
    }
}


void func_8018CC1C(void) {
}

#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8018A7E8(s32);

void func_8018CC24(s32 a0) {
    s32 s0;
    s32 a0_ptr;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 v1;
    s32 v1_sign;

    s0 = a0;

    func_8012AD80(a0);

    a0_ptr = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(s0 + 0x106);
    v0 = *(u16 *)(a0_ptr + 0x10);
    v0 = v0 + v1;
    *(u16 *)(a0_ptr + 0x10) = (u16)v0;

    a0_ptr = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(s0 + 0x108);
    v0 = *(u16 *)(a0_ptr + 0x14);
    v0 = v0 + v1;
    *(u16 *)(a0_ptr + 0x14) = (u16)v0;

    v0 = *(s32 *)(s0 + 0x1C);
    if ((v0 & 0x3) == 0) {
        func_8018A7E8(a0);
    }

    v0 = *(s32 *)(s0 + 0x1C);
    v1_sign = *(s16 *)(s0 + 0xA);
    v0++;

    *(s32 *)(s0 + 0x1C) = v0;

    if (v1_sign >= -0x3FF) {
        func_8012C218((void *)a0);
    }
}


#include "common.h"

extern void func_8012AD80(s32 a0);
extern void func_8012C218(void *a0);
extern void func_8018B0B0(void *a0, void *a1, void *a2, u32 a3);


extern Blk8 D_801ED9AC[];

void func_8018CCB8(s32 arg0) {
    s32 s0;
    s32 ptr;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 v1;
    s32 v1_sign;
    Blk8 sp10;

    s0 = arg0;

    sp10 = D_801ED9AC[0];

    func_8012AD80(arg0);

    ptr = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(s0 + 0x106);
    v0 = *(u16 *)(ptr + 0x10);
    v0 = v0 + v1;
    *(u16 *)(ptr + 0x10) = (u16)v0;

    ptr = *(s32 *)(s0 + 0x20);
    v1 = *(u16 *)(s0 + 0x108);
    v0 = *(u16 *)(ptr + 0x14);
    v0 = v0 + v1;
    *(u16 *)(ptr + 0x14) = (u16)v0;

    v0 = *(s32 *)(s0 + 0x1C);
    if ((v0 & 0x3) == 0) {
        func_8018B0B0((void *)arg0, &sp10, (void *)0, 8);
    }

    v0 = *(s32 *)(s0 + 0x1C);
    v1_sign = *(s16 *)(s0 + 0xA);
    v0++;
    *(s32 *)(s0 + 0x1C) = v0;

    if (v1_sign >= -0x77F) {
        func_8012C218((void *)arg0);
    }
}


#include "common.h"

extern s32 func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);
extern s32 D_801EC144;

void func_8018CD8C(void *a0) {
    s32 v0;
    s32 *v1, *a1;

    v0 = func_8012C1B8();
    *(s32 *)((char *)a0 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4(a0);
    } else {
        func_8001C214(v0, (s32)&D_801EC144);
        v1 = *(s32 **)((char *)a0 + 0x20);
        *(s16 *)((char *)v1 + 0x12) = 0x600;
        a1 = *(s32 **)((char *)a0 + 0x20);
        *(s32 *)((char *)a0 + 0x1C) = 0x20;
        *(s32 *)((char *)a1 + 0x4) |= 0x80000000;
        func_8012AD50(a0);
    }
}


#include "common.h"

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8012C218(void *a0);
extern void func_8012BEE8(u8*);

void func_8018CE0C(void *a0)
{
    s16 t0 = *(s16 *)&D_80126B5E;
    s32 pad[2];

    if (!(t0 < 0x429 && *(s16 *)&D_80126B62 < -0x6BF)) {
        func_8012C218(a0);
        return;
    }

    *(s16 *)((u8 *)a0 + 0x6) = t0;
    *(s16 *)((u8 *)a0 + 0xA) = D_80126B62 - 0xE0;
    *(s16 *)((u8 *)a0 + 0xE) = D_80126B66;

    {
        s32 *obj0 = *(s32 **)((u8 *)a0 + 0x20);
        *(u16 *)((u8 *)obj0 + 0x10) = *(u16 *)((u8 *)obj0 + 0x10) - 0x40;
    }

    if (((s32 (*)(s32))func_8012BEE8)((s32)a0) != 0) {
        if (*(u16 *)((u8 *)a0 + 0x34) == 0) {
            s32 *obj1 = *(s32 **)((u8 *)a0 + 0x20);
            *(s32 *)((u8 *)obj1 + 0x4) &= 0x7FFFFFFF;
            *(s32 *)((u8 *)a0 + 0x1C) = 0xC;
            *(u16 *)((u8 *)a0 + 0x34) = 1;
        } else {
            s32 *obj2 = *(s32 **)((u8 *)a0 + 0x20);
            *(s32 *)((u8 *)obj2 + 0x4) |= 0x80000000;
            *(s32 *)((u8 *)a0 + 0x1C) = 4;
            *(u16 *)((u8 *)a0 + 0x34) = 0;
        }
    }
}


extern s32 func_8018CF10(void);
    s32 func_8018CF10(void) {
        return 0x5D;
    }


void func_8018CF18(void *a0) {
        *(s16 *)((s32)a0 + 0x2) += 1;
    }


#include "common.h"

void func_8018CF2C(void)
{
    extern s32 D_801151D4;
    extern s32 func_80047D3C(s32 a0);
    extern s32 ratan2(s32 a0, s32 a1);
    extern s16 D_800B9AB0[];
    extern s16 D_800B9AB2[];
    s32 *base;
    s32 dz;
    s32 dx;
    s32 r;
    s16 ang;

    base = (s32 *)D_801151D4;
    dz = (s16)(*(s32 *)((s8 *)base + 0x48) - *(s32 *)((s8 *)base + 0x5C));
    dx = (s16)(*(s32 *)((s8 *)base + 0x50) - *(s32 *)((s8 *)base + 0x64));
    r = func_80047D3C(dz * dz + dx * dx);
    ang = (((s16)ratan2(*(s32 *)((s8 *)base + 0x4C) - *(s32 *)((s8 *)base + 0x60), (s16)r)) >> 2) + 0x58;
    D_800B9AB2[0] = ang;
    D_800B9AB0[0] = ((s16)ratan2(dz, dx)) >> 1;
}



extern void (*D_80194CDC[])(void);

void func_8018CFF4(void *a0) {
    D_80194CDC[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_80194CE4[])(void);

void func_8018D030(void *a0) {
    D_80194CE4[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012BF4C(s32 *a0, s32 a1);
    extern s32 func_8012AD50(void *a0);
    void func_8018D06C(s32 *a0) {
        func_8012BF4C(a0, 0);
        ((void (*)(void *))func_8012AD50)((void *)a0);
    }


extern void func_8012BEE8(u8*);
extern s32 func_8017267C(s32 *a0);
extern void func_8012BF4C(s32*, s32);
extern s32 rand(void);

void func_8018D0A0(void *a0)
{

    extern s32 *D_80126B78;
    extern s32 D_80126B58;
    s16 v1;
    s32 v0;
    s32 s0;

    v0 = ((s32 (*)(void))func_8012BEE8)();
    if (v0 == 0)
        return;

    v1 = *(s16 *)((s32)a0 + 0x70);

    if (v1 != 0) {
        if (v1 != 1) {
            goto default_case;
        }
    } else {
        v0 = D_80126B78[1];
        if (v0 < 0)
            goto end_func;
        if (func_8017267C(&D_80126B58) != 0)
            goto end_func;
    }

    func_8018D1F0(a0);
    s0 = 0;
    do {
        v0 = rand() & 0x1;
        if (v0 == 0) {
            func_8018D1F0(a0);
        }

        v0 = rand() & 0x3;
        if (v0 == 0) {
            func_8018D1F0(a0);
        }

        s0 = s0 + 1;
    } while (s0 < 3);
    goto end_func;

default_case:
    func_8018D1F0(a0);
    s0 = 0;
    do {
        v0 = rand() & 0x1;
        if (v0 == 0) {
            func_8018D1F0(a0);
        }

        v0 = rand() & 0x3;
        if (v0 == 0) {
            func_8018D1F0(a0);
        }

        s0 = s0 + 1;
    } while (s0 <= 0);

end_func:
    v0 = rand();
    ((void (*)(s32, s32))func_8012BF4C)((s32)a0, (v0 & 0x1F) | 0x20);
}



extern void func_80149350(s32 arg0);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern s32 func_8012E544(s32 a0);
extern u8 *func_801290DC(s32 a0, u8 *a1);

void func_8018D1F0(void *a0) {

    extern s32 D_80126B58;
    extern u8 D_801202A0[];
    extern u8 D_80194CEC[];
    s32 t;
    u8 *r;
    u8 *p;
    s32 i;
    s32 o;
    s16 out[4];

    t = *(s16 *)((s32)a0 + 0x70);
    r = &D_80194CEC[t * 8];
    switch (t) {
    case 0:
        ((void (*)(void *, void *, void *))func_80149350)(&D_80126B58, r, out);
        func_801290DC(0x56, (u8 *)out);
        break;
    case 1:
        o = func_8012E544(0x245);
        if (o == 0) {
            return;
        }
        ((void (*)(void *, void *, void *))func_8012F214)((void *)o, r, out);
        func_801290DC(0x56, (u8 *)out);
        break;
    default:
        p = D_801202A0;
        for (i = 0; i < 0x60; i++) {
            if (*(u16 *)p == *(s16 *)(r + 6)) {
                ((void (*)(void *, void *, void *))func_8012F214)(p, r, out);
                func_801290DC(0x56, (u8 *)out);
            }
            p += 0x10C;
        }
        break;
    }
}



extern void (*D_80194D20[])(void);

void func_8018D2DC(void *a0) {
    D_80194D20[*(u16 *)((s32)a0 + 0x2)]();
}



/* func_8018D318 — state entry: init the sub-object at +4/+0x10, bind the
 * primitive at +0x20 to the command list D_80194D14 (0x270 / 0x100), paint
 * its RGB (0x40,0x40,0x40) + code 0x9C, OR 0xD0000000 into its tag word,
 * clear the counter at +0x2C, then seed three random fields and bump the
 * state word at +2.
 */

extern void func_800159E4(s32 a0, s32 a1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146E90(s32 *a0, s32 a1);
extern int rand(void);

void func_8018D318(int param_1)
{
    extern unsigned char D_80194D14[];
    int p;
    int r1;
    int r2;

    p = *(int *)(param_1 + 0x20);
    ((void (*)(int, int))func_800159E4)(param_1 + 4, param_1 + 0x10);
    ((void (*)(int, int, int, int))func_8001CC3C)(p, (int)D_80194D14, 0x270, 0x100);
    *(unsigned char *)(p + 0x27) = 0x9c;
    *(unsigned char *)(p + 0x26) = 0x40;
    *(unsigned char *)(p + 0x25) = 0x40;
    *(unsigned char *)(p + 0x24) = 0x40;
    *(unsigned int *)(p + 4) = *(unsigned int *)(p + 4) | 0xd0000000;
    *(int *)(param_1 + 0x2c) = 0;
    *(unsigned short *)(param_1 + 0x30) = (rand() & 3) + 1;
    r1 = rand();
    r2 = rand();
    *(unsigned short *)(p + 0x12) = (r1 & 3) * 0x400 + (r2 & 0xf) * 0x44;
    ((void (*)(int, int))func_80146E90)(param_1, rand() & 0xf);
    *(unsigned short *)(param_1 + 2) = *(unsigned short *)(param_1 + 2) + 1;
}


extern void func_80146E90(s32 *a0, s32 a1);
extern s32 func_80146E98(s32 a0);


void func_8018D3FC(s32 *a0) {
    s32 *s1 = *(s32 **)((s32)a0 + 0x20);
    s32 v0;
    s32 v1;
    s32 tmp0;

    if (func_80146E98((s32)a0) != 0) {
        v1 = 0x7FFFFFFF;
        tmp0 = *(s32 *)((s32)s1 + 0x4);
        v0 = tmp0;
        v0 = v0 & v1;
        *(s32 *)((s32)s1 + 0x4) = v0;
        func_80146E90(a0, 0x10);

        v0 = *(u16 *)((s32)a0 + 0x2);
        v0 = v0 + 1;
        *(u16 *)((s32)a0 + 0x2) = v0;
    }
}



/* func_8018D468 — per-frame update for the effect entity that func_8017E8CC
 * initialises (its GPU primitive lives at +0x20).  Advance the spin angle at
 * +0x2C by 0x40, take rsin(angle)/256 as the Z component of a stack vector,
 * rotate that vector by the primitive's own angle at p+0x12, then re-derive
 * the draw position words at +6/+0xA/+0xE, grow the size counter at +0x2E
 * (mirrored into the primitive's w/h at p+0x18/p+0x1A), fade the RGB triple
 * at p+0x24..0x26 by 4 per frame, and retire the entity via func_801292C8
 * once the shared lifetime check func_80146E98 reports done.
 *
 * Matching notes (cookbook §S1/§S4 in gcc-2.7.2-map/sched.md): the three
 * position statements and the +0x2E statement all tie at sched priority 1,
 * so their SOURCE ORDER is the schedule.  The target's order is
 * 0x6, 0xE, 0xA, 0x2E — writing them in field order (0x6, 0xA, 0xE, 0x2E)
 * costs 12 mismatches because the 0x30 load, not the 0x2E load, wins the
 * load-delay filler slot after the first group.  `siz` must be an explicit
 * temporary (a re-read of +0x2E in the p+0x1A statement re-groups the whole
 * block, 26+ mismatches).
 */


extern s32 func_8004787C(s32 a0);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80146E98(s32 a0);
extern void func_801292C8(u8*);

void func_8018D468(int param_1)
{
    UVec_8017EA1C_8018D468 v;
    int p;
    short ang;
    int siz;
    int wid;
    int col;

    p = *(int *)(param_1 + 0x20);
    ang = *(unsigned short *)(param_1 + 0x2c) + 0x40;
    *(unsigned short *)(param_1 + 0x2c) = ang;
    v.vz = func_8004787C(ang) / 256;
    v.vy = 0;
    v.vx = 0;
    func_800139C8(*(short *)(p + 0x12), &v, &v);

    *(unsigned short *)(param_1 + 6) = *(unsigned short *)(param_1 + 0x12) + v.vx;
    *(unsigned short *)(param_1 + 0xe) = *(unsigned short *)(param_1 + 0x1a) + v.vz;
    *(unsigned short *)(param_1 + 0xa) = *(unsigned short *)(param_1 + 0xa) - *(unsigned short *)(param_1 + 0x30);
    siz = *(unsigned short *)(param_1 + 0x2e) + 0x10;
    *(unsigned short *)(param_1 + 0x2e) = siz;

    wid = *(unsigned short *)(p + 0x1a) + siz;
    *(unsigned short *)(p + 0x1a) = wid;
    *(unsigned short *)(p + 0x18) = wid;

    col = *(unsigned char *)(p + 0x26) - 4;
    *(unsigned char *)(p + 0x26) = col;
    *(unsigned char *)(p + 0x25) = col;
    *(unsigned char *)(p + 0x24) = col;

    if (func_80146E98(param_1) != 0) {
        ((void (*)(int))func_801292C8)(param_1);
    }
}


#include "common.h"

extern void (*D_80194D5C[])(void);
extern void (*D_80194D6C[])(void);

void func_8018D554(s32 a0) {
    s16 tag = *(s16 *)((s32)a0 + 0x70);

    switch (tag) {
        case 0: {
            u16 idx = *(u16 *)((s32)a0 + 0x2);
            D_80194D5C[idx]();
            break;
        }
        case 1: {
            u16 idx = *(u16 *)((s32)a0 + 0x2);
            D_80194D6C[idx]();
            break;
        }
    }
}


void func_8018D5D0(void) {
}

#include "common.h"

extern void func_80016714(void *a0, s32 a1);
extern void func_8018D7C8();
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);

extern void *D_801F01C8;
extern void *D_80194D90;

void func_8018D5D8(s32 a0)
{
    void *s0;
    s32 s1;
    void *s2;
    s16 *v0_ptr;
    s32 v0;
    s32 *temp;

    s2 = (void *)a0;
    s0 = &D_801F01C8;
    func_80016714(s0, 0x1100);

    s1 = 0;
    v0_ptr = (s16 *)((u8 *)s2 + 0xFC);
    v0 = (*v0_ptr) << 5;
    temp = (s32 *)((u8 *)s2 + 0xDC);
    *temp = v0 + (s32)&D_80194D90;

    for (s1 = 0; s1 < 0x40; s1++) {
        s32 *offset_ptr = (s32 *)((u8 *)s2 + 0xDC);
        func_8018D7C8(s0, (void *)(*offset_ptr));
        s0 = (void *)((u8 *)s0 + 0x44);
    }

    func_8012BF4C((s32 *)s2, 0xA);
    func_8012AD50(s2);
}


#include "common.h"

extern u8 D_80194D4C[];
extern void func_8012BEE8(u8*);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_8018D66C(s32 a0) {
    s32 s0 = a0;

    if (((s32 (*)(s32))func_8012BEE8)((s32)s0) != 0) {
        func_8002D4C8(*(u16 *)(D_80194D4C + *(s16 *)(s0 + 0xFC) * 8), 0);
        func_8012AD50((void *)s0);
    }
}


extern void *D_801F01C8;

void func_8018D6C4(void *a0) {
    s32 s1, s2;
    s16 *p;
    u16 cnt;
    s16 kind;
    s32 neg1;

    s2 = 0;
    neg1 = -1;
    s1 = 0;
    do {
        p = (s16 *)(((u8 *)&D_801F01C8) + s1);
        kind = p[0];
        switch (kind) {
        case 0:
            cnt = *(u16 *)(p + 1) - 1;
            *(u16 *)(p + 1) = cnt;
            if ((s16)cnt == neg1) {
                *(u16 *)(p + 1) = 0xA;
                *(u16 *)(p + 0) = *(u16 *)(p + 0) + 1;
            }
            break;
        case 1:
            cnt = *(u16 *)(p + 1) - 1;
            *(u16 *)(p + 1) = cnt;
            if ((s16)cnt == neg1) {
                func_8018D7C8((int)p, *(s32 *)((u8 *)a0 + 0xDC));
            } else {
                func_8018DA18((s32)a0, (void *)p);
                func_8018D988((u8 *)p);
            }
            break;
        }
        s2++;
        s1 += 0x44;
    } while (s2 < 0x40);
}


#include "common.h"

extern s32 rand(void);
extern void func_800134FC(s32 a0, void *a1, void *a2);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern s32 D_80194D2C[];

void func_8018D7C8(int param_1, int param_2)
{
    s16 dx;
    s16 dz;

    *(u16 *)(param_1 + 0x4) = 0x100;
    *(u16 *)(param_1 + 0x6) = 0x100;
    *(u16 *)(param_1 + 0x0) = 0;
    *(u16 *)(param_1 + 0x2) = (rand() & 7) + 1;

    dx = rand() % *(s16 *)(param_1 + 0x4);
    if (rand() & 1) {
        dx = -dx;
    }
    *(s16 *)(param_1 + 0x3C) = dx;

    dz = rand() % *(s16 *)(param_1 + 0x6);
    if (rand() & 1) {
        dz = -dz;
    }
    *(s16 *)(param_1 + 0x3E) = dz;

    *(u16 *)(param_1 + 0x40) = 0;
    *(s16 *)(param_1 + 0xC) = -*(u16 *)(param_1 + 0x3E);
    *(u16 *)(param_1 + 0xE) = (0x800 - *(u16 *)(param_1 + 0x3C)) & 0xFFF;

    *(s32 *)(param_1 + 0x8) = D_80194D2C[rand() & 7];
    func_800134FC(*(s16 *)(param_1 + 0xC), (void *)param_2, (void *)(param_1 + 0x1C));
    func_8001382C(*(s16 *)(param_1 + 0xE), (void *)(param_1 + 0x1C), (void *)(param_1 + 0x1C));

    func_800134FC(*(s16 *)(param_1 + 0xC), (void *)(param_2 + 0x10), (void *)(param_1 + 0x2C));
    func_8001382C(*(s16 *)(param_1 + 0xE), (void *)(param_1 + 0x2C), (void *)(param_1 + 0x2C));

    *(u16 *)(param_1 + 0x16) = 0x1000;
    if (rand() & 1) {
        *(u16 *)(param_1 + 0x14) = 0x1000;
        *(u16 *)(param_1 + 0x18) = 0x7000;
    } else {
        *(u16 *)(param_1 + 0x18) = 0x2000;
        *(u16 *)(param_1 + 0x14) = 0x2000;
    }
}


#include "common.h"

void func_8018D988(u8 *a0) {
    s32 v0, v1;
    s32 stack_vals[3];

    v0 = *(s32 *)(a0 + 0x1C);
    v1 = *(s32 *)(a0 + 0x2C);
    v0 = v0 + v1;
    *(s32 *)(a0 + 0x1C) = v0;
    stack_vals[0] = v0;

    v0 = *(s32 *)(a0 + 0x20);
    v1 = *(s32 *)(a0 + 0x30);
    v0 = v0 + v1;
    *(s32 *)(a0 + 0x20) = v0;
    stack_vals[1] = v0;

    v0 = *(s32 *)(a0 + 0x24);
    v1 = *(s32 *)(a0 + 0x34);
    v0 = v0 + v1;
    *(s32 *)(a0 + 0x24) = v0;
    stack_vals[2] = v0;

    *(u16 *)(a0 + 0x3C) += *(u16 *)((u8 *)stack_vals + 2);
    *(u16 *)(a0 + 0x3E) += *(u16 *)((u8 *)stack_vals + 6);
    *(u16 *)(a0 + 0x40) += *(u16 *)((u8 *)stack_vals + 10);
}


#include "common.h"

extern void func_80015978(s32 a0, s32 *a1);

void func_8018DA18(s32 a0, void *a1) {
    s32 sp18[2];

    func_80015978(a0 + 4, sp18);
    func_8018DA64((s8 *)a1 + 0x14, (s8 *)a1 + 0xC, (void *)sp18, (s8 *)a1 + 8, (s8 *)a1 + 0x3C);
}


#include "common.h"

/* Local layout typedefs for standalone match_one compilation.
 * SVECTOR: {s16 vx,vy,vz,pad;} 8 bytes, align 2.
 * MATRIX_L: {s16 m[3][3]; s32 t[3];} 0x20 bytes, align 4.
 * Prim_L:  {SVECTOR v[4]; s16 k30..k3e (8 shorts); u32 bcast; s32 tag; u8 code; u8 pad[7];} 0x40 bytes.
 * This function is a byte-identical sibling of func_80182800 (ov_SC04_000) --
 * confirmed via normalized asm diff (only the D_* data-symbol addresses and
 * instruction addresses differ).
 */
typedef struct { s16 vx, vy, vz, pad; } SVECTOR_8018DA64;
typedef struct { s16 m[3][3]; s32 t[3]; } MATRIX_8018DA64;
typedef struct {
    SVECTOR_8018DA64 v[4];             /* 0x00 */
    s32 k30, k34, k38, k3c;            /* 0x20: each a packed pair of s16 UV/coord fields */
    u32 bcast;                         /* 0x30 */
    s32 tag;                           /* 0x34 */
    u8  code;                          /* 0x38 */
    u8  pad39[7];                      /* -> 0x40 */
} Prim_8018DA64;

extern SVECTOR_8018DA64 D_80194DD0;
extern SVECTOR_8018DA64 D_80194DD8;
extern SVECTOR_8018DA64 D_80194DE0;
extern SVECTOR_8018DA64 D_80194DE8;

extern s32 func_80017DC4(void *a0, void *a1);
extern s32 func_80017E30(void *a0, void *a1);
extern void func_80016EF8(void *a0, void *a1);

void func_8018DA64(void *a0, void *a1, SVECTOR_8018DA64 *a2, s32 *a3, SVECTOR_8018DA64 *a4) {
    Prim_8018DA64 prim;
    MATRIX_8018DA64 mtx;

    prim.tag = 0x50000000;
    prim.code = 0x9B;

    prim.v[0] = D_80194DD0;
    prim.v[1] = D_80194DD8;
    prim.v[2] = D_80194DE0;
    prim.v[3] = D_80194DE8;

    {
        s32 rK30 = 0x010009C0;   /* $t1 */
        s32 rK34 = 0x010009DF;   /* $t0 */
        s32 rK38 = 0x011F09C0;   /* $a2 */
        s32 rK3c = 0x011F09DF;   /* $v1 */

        prim.bcast = *(u32 *)a3;

        prim.k30 = rK30;
        prim.k34 = rK34;
        prim.k38 = rK38;
        prim.k3c = rK3c;
    }

    func_80017DC4(a0, &mtx);
    func_80017E30(a1, &mtx);

    mtx.t[0] = a2->vx + a4->vx;
    mtx.t[1] = a2->vy + a4->vy;
    mtx.t[2] = a2->vz + a4->vz;

    func_80016EF8(&prim, &mtx);
}


void func_8018DBE8(void) {
}

#include "common.h"

extern s32 func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern void func_8001CD9C(s32 a0, void *a1);
extern void func_800233CC(void *a0, unsigned short a1);
extern void func_8018DFDC(void);
extern s32 func_8012AD50(void *a0);
extern s32 D_801F12C8;
extern s32 D_801F12CC;

void func_8018DBF0(s32 a0) {
    register s32 s1 __asm__("$17") = a0;  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B t3_tus1)
    s32 s0;
    s32 s2;
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B t3_tus1)
    register s32 a0r __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
    register s32 a1r __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B t3_tus1)

    v0 = func_8012C194();
    s2 = (s32)&D_801F12C8;
    __asm__ volatile("addu %0,%1,$0" : "=r"(s0) : "r"(v0));  // !FAKE: instruction addu — NEEDED DIFFERS (P36 rung B t3_tus1)
    *(s32 *)(s1 + 0x20) = v0;

    if (v0 == 0) {
        func_8012CAE4((void *)s1);
    } else {
        func_8001CD9C(s0, (void *)s2);

        a0r = s2;
        a1r = 0x80;
        __asm__ volatile("addiu %0,$0,3" : "=r"(v0));  // !FAKE: instruction addiu — NEEDED DIFFERS (P36 rung B t3_tus1)
        *(s16 *)(s0 + 0x2C) = v0;
        v0 = *(s32 *)(s0 + 4);
        *(s16 *)(s0 + 0x1A) = 0;
        *(s16 *)(s0 + 0x18) = 0;
        v0 |= 0x50000000;
        *(s32 *)(s0 + 4) = v0;
        func_800233CC((void *)a0r, (unsigned short)a1r);

        D_801F12CC = 0;

        ((void (*)(void *))func_8018DFDC)((void *)s1);
        func_8012AD50((void *)s1);
    }
}


extern void func_8018DFDC(void);
extern void func_8012BF4C(s32 *a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_8018DC9C(s32 a0) {
    u8 *s0;
    u16 val16;

    s0 = *(u8 **)(a0 + 0x20);
    func_8018DFDC();

    val16 = *(u16 *)(s0 + 0x18);
    val16 += 0x200;
    *(u16 *)(s0 + 0x18) = val16;

    if ((s16)val16 >= 0x1001) {
        *(u16 *)(s0 + 0x18) = 0x1000;
    }

    *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x18);

    if (*(s16 *)(s0 + 0x18) == 0x1000) {
        func_8012BF4C((s32 *)a0, 0x78);
        func_8012AD50((void *)a0);
    }
}


#include "common.h"

extern u8 D_80194D50[];
extern void func_8018DFDC(void);
extern void func_8012BEE8(u8*);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012AD50(void *a0);

void func_8018DD24(s32 a0) {
    s32 s0 = a0;

    func_8018DFDC();
    if (((s32 (*)(s32))func_8012BEE8)((s32)s0) != 0) {
        func_8002D4C8(*(u16 *)(D_80194D50 + *(s16 *)(s0 + 0xFC) * 8), 0);
        func_8012AD50((void *)s0);
    }
}


#include "common.h"

extern void func_8018DFDC(void);
extern void func_80016940(s32 a0);
extern s32 func_8012AD50(void *a0);

void func_8018DD84(s32 a0) {
    u8 *s0;
    u16 val16;

    s0 = *(u8 **)(a0 + 0x20);
    func_8018DFDC();

    val16 = *(u16 *)(s0 + 0x18);
    val16 += 0x200;
    *(u16 *)(s0 + 0x18) = val16;

    {
        s16 temp = (s16)val16;
        if (temp >= 0x7001) {
            *(u16 *)(s0 + 0x18) = 0x7000;
        }
    }

    *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x18);

    if (*(s16 *)(s0 + 0x18) == 0x7000) {
        func_80016940(0x4);
        func_8012AD50((void *)a0);
    }
}


#include "common.h"

extern s32 func_80016978(s32 arg);
extern void func_8018DFDC(void);

void func_8018DE0C(s32 a0) {
    extern s32 D_80126B58;
    s32 s0 = a0;
    s32 s1;
    s32 v0;

    func_8018DFDC();

    do { v0 = func_80016978(4); } while (0);
    s1 = (s32)&D_80126B58;
    v0 &= 0xFFFF;

    if (v0 != 0) {
        v0 = func_8012E57C(0x3AF, 0);
        if (v0 != 0) {
            func_8012C098((void *)v0);
        }

        if (*(s16 *)(s0 + 0xFC) == 0) {
            func_8014708C((void *)s1);
            func_801472C8((struct S *)s1);
        } else {
            func_80147084((s32 *)s1);
            func_801472B4((void *)s1);
        }

        do { func_8012AD50((void *)s0); } while (0);
    }
}


#include "common.h"

extern s32 func_80016978(s32 arg);
extern void func_8018DFDC(void);
extern s32 func_8012AD50(void *a0);

void func_8018DEB0(s32 a0) {
    s32 s0 = a0;
    s32 v0;

    func_8018DFDC();

    v0 = func_80016978(0);
    v0 &= 0xFFFF;

    if (v0 != 0) {
        func_8012AD50((void *)s0);
    }
}


#include "common.h"

extern void func_8018DFDC(void);
extern s32 func_8012AD50(void *a0);

void func_8018DEF4(s32 a0) {
    u8 *s0;
    u16 val16;

    s0 = *(u8 **)(a0 + 0x20);
    func_8018DFDC();

    val16 = *(u16 *)(s0 + 0x1A);
    val16 -= 0x800;
    *(u16 *)(s0 + 0x1A) = val16;

    if ((s16)val16 < 0x100) {
        *(u16 *)(s0 + 0x1A) = 0x100;
    }

    if (*(s16 *)(s0 + 0x1A) == 0x100) {
        func_8012AD50((void *)a0);
    }
}


#include "common.h"

extern void func_8018DFDC(void);

void func_8018DF6C(s32 a0) {
    u8 *s0;
    u16 val16;

    s0 = *(u8 **)(a0 + 0x20);
    func_8018DFDC();

    val16 = *(u16 *)(s0 + 0x18);
    val16 -= 0x800;
    *(u16 *)(s0 + 0x18) = val16;

    if ((s16)val16 < 0) {
        *(u16 *)(s0 + 0x18) = 0;
    }

    if (*(s16 *)(s0 + 0x18) == 0) {
        func_8012C098((void *)a0);
    }
}


extern u16 D_800B99DA;
extern s32 D_801F12C8;

void func_8018DFDC(void) {
    s32 *ptr;

    ptr = &D_801F12C8;

    if (D_800B99DA & 1) {
        *ptr = 0xE0E0E0;
    } else {
        *ptr = 0xFFFFFF;
    }
}


void func_8018E010(void) {

    extern s16 D_801F141C;
    s16 *p = &D_801F141C;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0xe);
        i--;
    } while (i >= 0);
}



/* func_8018E034 — cookbook §71 (sibling-first).
 * func_8018E0D4 is ALREADY MATCHED in the same TU
 * (src/ov_SC03_014/ov_SC03_014_jr_8017EB7C.c L4221) as a 3-arg
 * `void func_8018E0D4(s32, s32, s32)`, so the untouched $a3 at the first
 * jal is just the incoming arg3 living on, not a 4th argument.
 * func_8018E1F0 (asm, same TU) reads its 2nd arg as lhu+0 / lhu+2 / lh+4 /
 * lh+6 => the sp+0x10 local is a 4 x s16 record.
 *
 * Two levers took it 32 -> 2 -> 0 (match_one MATCH, rtu_match MATCH):
 *  1. LENGTH-DRIFT (-2, cookbook §78): writing `sp10.unk2 = i * 0x100`
 *     leaves gcc-2.7.2 recomputing `sll v0,s1,8` instead of building the
 *     strength-reduced giv, so only s0..s3 get saved and the frame is two
 *     instructions short.  An EXPLICIT accumulator (`ang += 0x100`) forces
 *     the second callee-saved register ($s2) and restores sw/lw $s4.
 *  2. REGALLOC-PERM $s1>$s2 (cookbook §3-T2, source order drives emission):
 *     `ang = 0;` on its own line before the loop emits the $s2 zero-init
 *     FIRST.  Folding it into the for-init (`for (i = 0, ang = 0; ...)`)
 *     puts $s1's zero-init first, which is the target order.
 */


extern void func_8018E0D4(s32 arg0, s32 arg1, s32 arg2);
extern void func_8018E1F0(s32 arg0, Rec_8018A6A4_8018E034 *arg1, s32 arg2, s32 arg3);

void func_8018E034(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Rec_8018A6A4_8018E034 sp10;
    s32 i;
    s32 ang;

    func_8018E0D4(arg0, 0x1000, 0);
    sp10.unk0 = *(u16 *)(arg3 + 0x0);
    sp10.unk4 = *(u16 *)(arg3 + 0x2);
    sp10.unk6 = 1;
    for (i = 0, ang = 0; i < 16; i++) {
        sp10.unk2 = ang;
        func_8018E1F0(i, &sp10, arg1, arg2);
        ang += 0x100;
    }
}



    extern s16 D_801F1416;
    extern s16 D_801F1418;
    extern s16 D_801F141A;
    void func_8018E0D4(s32 arg0, s32 arg1, s32 arg2) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s16 D_801F1414;
        D_801F1414 = *(u16 *)((s32)arg0 + 0x0);
        D_801F1416 = *(u16 *)((s32)arg0 + 0x2);
        D_801F1418 = arg1;
        D_801F141A = arg2;
    }




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018E104(s32 a0) {

    extern s16 D_801F1414;
    extern s16 D_801F1416;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_800AF648;
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801F1414 = sxy[0];
    D_801F1416 = sxy[1];
}



extern s16 D_801F141A;
    void func_8018E17C(s32 arg0) {
        *(s16 *)((s32)&D_801F141A + 0x0) += arg0;
    }


extern s32 func_8018E2C4(void);

void func_8018E198(s32 a0, s32 a1, s32 a2) {
    s32 v0 = func_8018E2C4();
    if (v0 >= 0) {
        func_8018E1F0(v0, a0, a1, a2);
    }
}



/* func_8018E1F0 — SPLICE RECONCILE (bytes unchanged from the s6h draft).
 *
 * THREE in-TU collisions, all fixed without touching an emitted instruction
 * (src/ov_SC03_014/ov_SC03_014_jr_801848E4.c):
 *
 * (1) memcpy — cookbook §2959 / the sibling note at TU L3742.  The TU declares
 *     memcpy THREE times: L81 + L1518 with the builtin-compatible signature
 *     (void*, const void*, unsigned) and then L1524 as
 *     `extern void *memcpy(void *dst, void *src, s32 n);`.  L1524 disagrees with
 *     gcc's built-in, so duplicate_decls "throws away the built-in" (warning only,
 *     because the old decl was still DECL_BUILT_IN) and installs a PLAIN function
 *     decl.  Two consequences at the splice point (L3635):
 *       a. my own builtin-shaped redeclaration now conflicts with a plain decl —
 *          hard error ("conflicting types for `memcpy'", :3637 vs :1524);
 *       b. even if it compiled, the identifier `memcpy` is no longer a builtin
 *          here, so both copies would lower to `jal memcpy` — but the TARGET
 *          bytes are the INLINE block move (lwl 3 / lwr 0 / swl / swr, no jal).
 *     Fix = do not name memcpy at all: a 4-byte STRUCT ASSIGN through an
 *     ALIGN-1 struct (u8 x4).  That is exactly the sibling func_8018ADA8 lever
 *     in this same TU (TU L3736-3744, cookbook §48-C2): align 1 routes
 *     mips.c expand_block_move, which copy_addr_to_reg's the source into one
 *     held register -> the identical lwl/lwr + swl/swr pair, zero memcpy ref.
 *     The typedef is BLOCK-scoped so it cannot collide with the TU's own
 *     block-scoped `V4` at L3758.
 *
 * (2) func_8018E1F0 itself — the TU prototypes it at L3570 as
 *     `extern void func_8018E1F0(s32, Rec_8018A6A4 *, s32, s32);` (used by the
 *     matched caller func_8018A6A4 at L3583).  Rec_8018A6A4 is a TU-local
 *     typedef I cannot restate (C89 forbids the redefinition), and the last two
 *     args are really pointers, so defining the name directly is "conflicting
 *     types".  Fix = §37/§124 ASM-LABEL ALIAS: define aF8018A860 with an
 *     __asm__("func_8018E1F0") label.  Emits the identical symbol, leaves the
 *     TU's declaration untouched, zero blast radius, zero byte change.
 *
 * (3) D_801F141C / rand — declared VERBATIM as the TU already has them
 *     (D_801F141C: TU L3637 + L3671; rand: TU L951), so both are exact
 *     re-declarations and merge silently.
 */
extern s32 rand(void);      /* TU L951, verbatim */

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3) __asm__("func_8018E1F0");

void aF8018A860(s32 a0, s16 *a1, u8 *a2, u8 *a3)
{

    extern s16 D_801F141C;      /* TU L3637 / L3671, verbatim */
   /* align 1 — §48-C2 */
    s16 *s1;
    u16 temp_u16;
    s16 temp_s16;
    s32 temp_s32, v0;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801F141C);

    *(u16 *)s1 = *(u16 *)a1;

    *(B4_8018E1F0 *)((u8 *)s1 + 6) = *(B4_8018E1F0 *)a2;
    *(u8 *)((u8 *)s1 + 9) = 0;

    *(B4_8018E1F0 *)((u8 *)s1 + 10) = *(B4_8018E1F0 *)a3;
    *(u8 *)((u8 *)s1 + 13) = 0;

    v0 = rand() & 0x3f;
    temp_u16 = *(u16 *)((u8 *)a1 + 2);
    *(u16 *)((u8 *)s1 + 2) = temp_u16 + v0 - 0x20;

    v0 = rand() & 0x7f0;
    temp_s16 = *(s16 *)((u8 *)a1 + 4);
    temp_s32 = temp_s16 * (v0 + 0xc00);
    v0 = (s32)(temp_s32 >> 12);
    *(s16 *)((u8 *)s1 + 4) = (s16)v0;

    v0 = *(s16 *)((u8 *)a1 + 6);
    if (v0 != 0) {
        u16 v1 = *(u16 *)((u8 *)s1 + 4);
        *(u8 *)((u8 *)s1 + 9) = 1;
        *(u16 *)((u8 *)s1 + 4) = 0;
        *(u8 *)((u8 *)s1 + 13) = (u8)v1;
    }
}




s32 func_8018E2C4(void) {

    extern s16 D_801F141C;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801F141C + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0xE;
    }
    return -1;
}





void func_8018E300(s32 a0, s32 a1) {

    extern s16 D_801F141C;
    s16 *s1;
    u16 val;

    if (a0 >= 0x10) return;

    s1 = (s16 *)((a0 * 14) + (s32)&D_801F141C);
    val = *(u16 *)s1;

    if (val == 0) return;

    if (a1 == 0) {
        *(u16 *)s1 = 0;
    } else {
        *(u8 *)((u8 *)s1 + 9) = 2;
    }
}



/* func_8018E34C — 16-entry table walk, stride 0xE, over D_801F141C.
 * §71 sibling: func_8018A680 (same TU, L4199) already matched the
 * `extern s16 D_801F141C; s16 *p = &D_801F141C; p = (s16*)((s32)p+0xe)`
 * shape over the very same array — copy that walker verbatim.
 *
 * Two induction registers in the target ($s1 = base+0, $s0 = base+4) are NOT
 * two source pointers: $s1 is the user pointer (the biv, used for the +0
 * accesses) and $s0 is loop.c's single COMBINED address giv for the
 * {+4, +9, +13} group (offsets 0/5/9 off $s0). Declaring a second pointer
 * splits that group and costs a third register (iter 1: 53 mismatches).
 */

extern void func_8018E428(s32 arg0);

void func_8018E34C(void) {

    extern s16 D_801F141C;
    s16 *p = &D_801F141C;
    s32 i = 0;
    s16 t;

    do {
        if (*(u16 *)p != 0) {
            func_8018E428(i);
            switch (*(u8 *)((s32)p + 9)) {
            case 1:
                if (*(s16 *)((s32)p + 4) < *(u8 *)((s32)p + 13)) {
                    *(s16 *)((s32)p + 4) = *(s16 *)((s32)p + 4) + 8;
                } else {
                    *(u8 *)((s32)p + 9) = 0;
                }
                break;
            case 2:
                t = *(s16 *)((s32)p + 4);
                if (t != 0) {
                    t -= 0x10;
                    *(s16 *)((s32)p + 4) = t;
                    if (t > 0) {
                        break;
                    }
                }
                *p = 0;
                break;
            }
        }
        i++;
        p = (s16 *)((s32)p + 0xe);
    } while (i < 0x10);
}



/* func_8018E428 — draws one entry of the 16-slot D_801F141C particle table:
 * bump-allocates a 0x1C-byte GPU packet out of D_800A5E60, fills it from the
 * table entry, runs two RotMatrixZ/ApplyMatrixSV passes to place the two
 * endpoints, then link-ins the packet into the current double-buffer's OT
 * (the PSY-Q `addPrim` macro pair) and calls func_80016638.
 *
 * STATUS: byte-MATCH, 177/177 instructions (match_one standalone AND spliced
 * into the real TU — the in-TU compile adds ZERO new cc1 diagnostics over the
 * unmodified TU baseline).
 *
 * ---------------------------------------------------------------------------
 * LEVERS (each byte-checked against asm/.../func_8018E428.s)
 *
 *  §48  STRUCT ASSIGN, not a hand-rolled temp copy.  `m = D_800AE620;` on a
 *       32-byte aggregate routes expr.c move_by_pieces, which emits the exact
 *       lw/lw/lw + sw/sw/sw (x2) + lw/lw + sw/sw grouping AND picks the
 *       target's registers ($a2 = source address, $v0/$v1/$a1 = carriers), and
 *       keeps the arg0*14 allocator chain OUT of the copy.  The manual
 *       three-temp form (DEFINE_func_8012B4B8, engine_core.h L29487) emits the
 *       same instruction MIX but a different allocation (+60 mismatches).
 *
 *  §21/T6  The double-buffer index D_800B9A02 is read at ALL THREE use sites
 *       (three `lhu`s off ONE materialised `la`).  A PLAIN read is CSEd down to
 *       two AND keeps -G0 symbol addressing (lui+lhu per read, +1 insn); a
 *       POINTER local gives the `la` but lets cse fold the third read.  The
 *       `volatile u16 *` pointer local reproduces BOTH properties and leaves
 *       the TU's own `extern s16 D_800B9A02;` untouched.
 *
 *  T6   The OT base is bound to an s32 local (`ot`) so the tag read/write keep
 *       the `0x40($v1)` displacement form instead of folding into the pointer.
 *
 *  L4   `mp`, a pointer local bound to &m, is what puts the matrix address in a
 *       callee-saved register ($s2) and turns each argument setup into a move;
 *       passing the array directly re-materialises `addiu $aN,$sp,0x10` at
 *       every call site and drops $s6 from the frame entirely.
 *
 *  S1   `t = *(u16 *)ent;` is hoisted ABOVE the two `sh $zero` stores — the
 *       sp-relative stores are not disambiguated from the $s0-based load, so
 *       only SOURCE ORDER moves it (4 mismatches).
 *
 *  T-form  `u16 bx/by` (not s32) is what makes `addu $v0,$s3,$v0` come out with
 *       the accumulator first; through s32 locals combine canonicalises the
 *       zero_extend into operand 0 and both adds emit reversed.
 *
 *  §83c-inverse  FRAME: 0x70 = 16 args + 56 declared vars + 32 saved regs + an
 *       8-byte COMPILER TEMP that gcc allocates for the two `symbol+register`
 *       memory references (both D_800A651C).  So the DECLARED locals must total
 *       56, not 60: m(32)@0x10, sv(8)@0x30, out(8)@0x38, v(8)@0x40 — the third
 *       word of the vector handed to func_8004901C (sp+0x48) lands INSIDE that
 *       compiler temp.  `s32 v[3]` gives a 0x78 frame and 19 extra mismatches.
 *       Do NOT invent a dead local to reach the frame size.
 *
 * ---------------------------------------------------------------------------
 * THE TWO RESIDUAL CLUSTERS AND WHAT ACTUALLY CLOSED THEM
 * (both are gcc-2.7.2-map/sched.md §1 rule 7 "BIRTHING BOOST" + rule 5(b)
 *  "potential hazard"; diagnosed from the cc1 `-dS` ready-list trace, which
 *  names the decision verbatim: `;; insn 245 has a greater potential hazard`.)
 *
 *  (a) The three symbol loads before the first RotMatrixZ came out E4,EA,E6
 *      instead of EA,E4,E6.  `lh $a0,D_801F141A` is a single-set SET(REG,…) —
 *      the sched1 birthing boost sinks it to just before its consumer (the
 *      jal), i.e. one slot too late.  Statement order CANNOT fix this: written
 *      as a plain local the load is combined into the call's arg setup, so its
 *      LUID is the call's either way (verified: two source orders, identical
 *      bytes).  `register s32 ang __asm__("$4")` keeps the load a separate insn
 *      AT its source position — zero extra instructions, +0 bytes.
 *
 *  (b) The tail's `lw $v1,0($s1)` (`*(u32 *)p`) belongs in the load-delay slot
 *      of `lhu $a0,0($a2)`; ours landed 7 insns later with `lui $a0,0xff00`
 *      taking the slot.  sched1 trace: at T-27 the ready list is
 *      `247 (7f000001) 245 (7f000001)` — BOTH boosted — and the tie goes to the
 *      LOAD via `potential_hazard` (memory-unit users beat ALU insns), so the
 *      load is picked first = placed LAST.  TWO edits are needed and neither
 *      works alone:
 *        1. KILL the boost on the load's destination — `pv` gets a second SET
 *           from a zero-byte dead `__asm__ __volatile__("" : "=r"(pv));` at the
 *           end of the function (sched.md S2: a plain C reassignment does not
 *           work, cse/flow removes it; reusing one local across BOTH addPrim
 *           halves does kill the boost but makes `pv` a 2-death GLOBAL allocno
 *           that loses $v1, §136).  With the boost dead, sched1 emits the
 *           target order exactly (proved with -fno-schedule-insns2).
 *        2. PIN `pv` to $v1 (`register u32 pv __asm__("$3")`).  Without it,
 *           local-alloc gives $v1 to the shorter, denser index quantity and
 *           `pv` lands in $a1/$t0; sched2 then re-applies rule 5(b) and undoes
 *           sched1's order.  With `pv` in $v1 the index is pushed to $a0, the
 *           0xFF000000 constant reuses $a0, and its output-dependence on the
 *           index's `sll/addu` FREEZES it after them — which is precisely the
 *           target's shape, and what makes sched2 leave sched1's order alone.
 *
 *      Pin-trim log (all re-scored): dropping the $a2 `bidx` pin — MATCH;
 *      dropping the $a3 0xFFFFFF pin — MATCH; dropping `ang` — 4 mismatches
 *      (a dead-volatile boost-kill on `ang` does NOT substitute); dropping
 *      `pv` — 11; dropping the dead `pv` asm — 11.  Two pins are the minimum
 *      found.
 *
 * ---------------------------------------------------------------------------
 * DECLARATIONS: ApplyMatrixSV, D_800B9A02 and D_801F1414/E6/EA/EC are declared
 * VERBATIM as the TU already has them at file scope (L163, L2460/2462,
 * L3689/3705/3706, L3726, L3879), so they merge silently.  D_800AE620,
 * D_800A5E60, D_800A651C, D_800A6518, D_801F1418, RotMatrixZ, func_8004901C and
 * func_80016638 have NO file-scope declaration anywhere in the TU and none in
 * include/ (checked in one pass, D2), so each is block-scoped here to keep the
 * blast radius on the rest of the TU at zero (§103/T51).  Verified by splicing
 * this body over the INCLUDE_ASM at TU L3917 and compiling the whole TU: same
 * 7 stderr lines as the untouched TU, and func_8018E428 is byte-identical.
 */

void func_8018E428(s32 arg0)
{
   /* 32 bytes, align 4 */

    extern Blk32_8018AA98_8018E428 D_800AE620;
    extern s32 D_800A5E60;
    extern s32 D_800A651C;
    extern u8 D_800A6518[];
    extern s16 D_801F1414;
    extern s16 D_801F1416;
    extern s16 D_801F1418;
    extern s16 D_801F141C;
    extern void RotMatrixZ(s32 a0, void *a1);
    extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
    extern void func_8004901C(void *a0, void *a1);
    extern void func_80016638(void *a0, s32 a1, s32 a2);

    Blk32_8018AA98_8018E428 m;                    /* sp+0x10 */
    s16 sv[4];                           /* sp+0x30 */
    s16 out[4];                          /* sp+0x38 */
    s32 v[2];                            /* sp+0x40 — 3rd word lives in the temp area */
    void *mp;
    u8 *p;
    u8 *ent;
    s32 ot;
    u16 bx;
    u16 by;
    register s32 ang __asm__("$4");      /* §17 pin — see residual (a) */  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
    volatile u16 *bidx;
    s32 t;
    register u32 pv __asm__("$3");       /* §17 pin — see residual (b) */  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t3_tus1)

    m = D_800AE620;
    mp = &m;

    ent = (u8 *)((arg0 * 14) + (s32)&D_801F141C);
    p = (u8 *)D_800A5E60;
    D_800A5E60 = (s32)p + 0x1C;

    p[3] = 6;
    p[7] = 0x32;
    p[4] = ent[6];
    p[5] = ent[7];
    p[6] = ent[8];
    p[0xC] = ent[0xA];
    p[0xD] = ent[0xB];
    p[0xE] = ent[0xC];
    p[0x14] = ent[0xA];
    p[0x15] = ent[0xB];
    p[0x16] = ent[0xC];

    ang = D_801F141A;
    bx = (u16)D_801F1414;
    by = (u16)D_801F1416;
    RotMatrixZ(ang, mp);

    *(s32 *)((u8 *)v + 8) = D_801F1418;
    v[1] = *(s32 *)((u8 *)v + 8);
    v[0] = v[1];
    func_8004901C(mp, v);

    t = *(u16 *)ent;
    sv[2] = 0;
    sv[1] = 0;
    sv[0] = t;
    *(s16 *)(p + 8) = bx;
    *(s16 *)(p + 0xA) = by;

    RotMatrixZ(*(s16 *)(ent + 2) - (((s32)*(u16 *)(ent + 4) << 16) >> 17), mp);
    ApplyMatrixSV(mp, sv, out);
    *(s16 *)(p + 0x10) = bx + (u16)out[0];
    *(s16 *)(p + 0x12) = by + (u16)out[1];

    RotMatrixZ(*(s16 *)(ent + 4), mp);
    ApplyMatrixSV(mp, sv, out);
    bx += (u16)out[0];
    *(s16 *)(p + 0x18) = bx;
    by += (u16)out[1];
    *(s16 *)(p + 0x1A) = by;

    /* addPrim(otp, p) == setaddr(p, getaddr(otp)), setaddr(otp, p) */
    bidx = (u16 *)&D_800B9A02;
    pv = *(u32 *)p;
    *(u32 *)p = (pv & 0xFF000000) |
                (*(u32 *)(*(s32 *)((u8 *)&D_800A651C +
                                   (*bidx * 20)) + 0x40) & 0xFFFFFF);
    ot = *(s32 *)((u8 *)&D_800A651C + (*bidx * 20));
    *(u32 *)(ot + 0x40) = (*(u32 *)(ot + 0x40) & 0xFF000000) | ((u32)p & 0xFFFFFF);
    func_80016638(&D_800A6518[*bidx * 20], 0x10, 1);
    __asm__ __volatile__("" : "=r"(pv));   /* zero-byte 2nd SET: kills the sched1 birthing boost */  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B t3_tus1)
}


void func_8018E6EC(void) {

    extern s16 D_801F1314;
    s16 *p = &D_801F1314;
    s32 i = 0xF;
    do {
        *p = 0;
        p = (s16 *)((s32)p + 0x10);
        i--;
    } while (i >= 0);
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8018E738(s32 a0);

void func_8018E710(s32 a0) {
    s32 pv[2];
    func_80015978(a0, pv);
    func_8018E738((s32)pv);
}



/* func_8018E738 — §71 sibling of func_8018A774 / func_8018AF0C (same TU): the
 * RotTransPers wrapper family.  Here the SVECTOR comes in as the parameter
 * instead of being produced by func_80015978, so pv[0..1] is free and carries
 * the 4-byte word copied out of D_801ED9B8 instead.
 *
 * Frame proof (0x38 = 0x10 outgoing + 0x18 var + 0x10 saved s0/s1/ra):
 *   sp+0x10  u16 sxy[4]  (8 bytes)  -> RotTransPers a1, func_8018E7C0 arg0
 *   sp+0x18  s32 pv[4]   (16 bytes) -> pv[0] = copy dest, &pv[2]/&pv[3] = 0x20/0x24
 *
 * The lwl 0x3 / lwr 0x0 / swl 0x1B / swr 0x18 block move: a 4-byte struct assign
 * whose type has ALIGNMENT 1 (cookbook §48-C2).  Align 1 (not 2) is load-bearing —
 * it is what pushes the copy off the move_by_pieces path (which keeps the SYMBOL
 * in the address and emits a fresh `lui $at,%hi` per reference) onto mips.c
 * expand_block_move, which copy_addr_to_reg's the source address into ONE held
 * register first -> `lui $a1,%hi; addiu $a1,$a1,%lo; lwl 3($a1); lwr 0($a1)`.
 * A {u16,u16} (align 2) struct compiles to the same opcode sequence but with the
 * folded-symbol addressing: 4 mismatches.  Struct assign, NOT memcpy (memcpy
 * byte-matches in isolation but lowers to `jal memcpy` in any TU that declares
 * it — §2959).
 *
 * All four callee prototypes are copied VERBATIM from this TU (func_8004914C /
 * func_800491AC / RotTransPers at file scope L3484-3486; func_8018E7C0 from its
 * own definition at L3612).  D_800AF648 is block-scoped `extern u8` exactly as
 * the two matched siblings do it.  D_801ED9B8 appears nowhere else in the TU.
 */

extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8018E7C0(void *arg0, void *arg1, s32 arg2, s32 arg3);

void func_8018E738(s32 a0) {
    extern u8 D_800AF648;
    extern V4_8018E738 D_801ED9B8;
    u16 sxy[4];
    s32 pv[4];

    *(V4_8018E738 *)pv = D_801ED9B8;
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers(a0, (s32)sxy, &pv[2], &pv[3]);
    func_8018E7C0(sxy, pv, 0x10, 0x18);
}



extern void func_8018E82C(void *a0, void *a1, s16 a2);
extern void func_8018E960(s32 a0, s16 a1, u16 a2);

void func_8018E7C0(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    /* The target frame is 0x30: 0x10 outgoing-arg area + 0x10 var_size +
     * 0x10 saved regs (s0/s1/s2/ra at 0x20..0x2C).  gcc-2.7.2 allocates a
     * declared aggregate even when it is never referenced, so this 16-byte
     * local reproduces the original's var_size exactly. */
    s32 unused[4];
    s32 i;
    s32 j;

    func_8018E82C(arg0, arg1, arg2);
    for (i = 0, j = 0; i < 0x10; i++, j += 0x100) {
        func_8018E960(i, j, arg3);
    }
}





void func_8018E82C(void *a0, void *a1, s16 a2) {

    extern s16 D_801F1308;
    extern s16 D_801F130A;
    extern u8 D_801F1310;
    extern u8 D_801F1311;
    extern u8 D_801F1312;
    extern u32 D_801F130C;
    if (a0 != NULL) {
        D_801F1308 = *(u16 *)a0;
        D_801F130A = *(u16 *)((s32)a0 + 2);
    } else {
        D_801F1308 = 0;
        D_801F130A = 0;
    }

    D_801F1310 = *(u8 *)a1;
    D_801F1311 = *(u8 *)((s32)a1 + 1);
    D_801F1312 = *(u8 *)((s32)a1 + 2);
    D_801F130C = (u32)a2 << 16;
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);

void func_8018E89C(s32 a0) {

    extern s16 D_801F1308;
    extern s16 D_801F130A;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern u8 D_800AF648;
    u16 sxy[2];
    s32 pv[4];

    func_80015978(a0, pv);
    func_8004914C(&D_800AF648);
    func_800491AC(&D_800AF648);
    RotTransPers((s32)pv, (s32)sxy, &pv[2], &pv[3]);

    D_801F1308 = sxy[0];
    D_801F130A = sxy[1];
}




extern s32 func_8018EA7C(void);
extern void func_8018E960(s32 a0, s16 a1, u16 a2);

void func_8018E914(s32 a0, s32 a1) {
    s32 result = func_8018EA7C();
    if (result >= 0) {
        s16 ext_a0 = (s16)a0;
        func_8018E960(result, ext_a0, (u16)a1);
    }
}



/* func_8018E960 — particle/ripple spawner for slot `a0` of the 16-entry,
 * 0x10-byte-stride table at D_801F1314.
 *
 * Declaration notes (the TU already carries all of these — nothing is invented):
 *   - rand / func_80047948 / func_8004787C : verbatim re-declarations of the
 *     TU's own file-scope prototypes (L951, L2197, L2198) -> merge silently.
 *   - D_801F1314 : block-scope `extern s16` exactly as func_8018AD5C (L3869)
 *     and func_8018B0EC (L3982) declare it.
 *   - D_801F130E : its own dlabel in asm/ov_SC03_014/data/tail19.data.s:5868;
 *     undeclared anywhere in the TU, so a block-scope extern is conflict-free.
 *     It is declared as an ARRAY on purpose: the ARRAY_REF sets MEM_IN_STRUCT_P,
 *     which restores the true_dependence() edge against the in-struct `p->f2`
 *     store and stops sched2 from hoisting the load above it (cookbook §135/2).
 *   - The TU's own prototype for this function is
 *       extern void func_8018E960(s32 a0, s16 a1, u16 a2);   (L3929)
 *     but the body byte-proves the params are plain s32 (no `sll/sra` on $a1 and
 *     a single `andi` at the use, not the promoted-var `move`+`andi` pair). So the
 *     definition uses the §37/§124 ASM-LABEL ALIAS — exactly what this same TU
 *     already does for `aF8018A860` — leaving the TU's declaration untouched.
 */

extern s32 rand(void);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void aF8018AFD0(s32 a0, s32 a1, s32 a2) __asm__("func_8018E960");

void aF8018AFD0(s32 a0, s32 a1, s32 a2)
{

    extern s16 D_801F1314;
    extern s16 D_801F130E[];

    s32 unused[4];      /* dead locals — reproduces var_size 0x10 (frame 0x38) */
    P_8018E960 *p;
    u16 rad;
    s32 m;
    s32 ang;
    s32 t8;
    s16 tC;

    p = (P_8018E960 *)((s32)&D_801F1314 + (a0 << 4));

    rad = a2;
    rad = a2 + (rand() % (rad >> 2) - (rad >> 3));

    ang = a1 + (rand() & 0x3f) - 0x20;
    p->f6 = ang;

    m = rad;
    t8 = (func_80047948(p->f6) * m) >> 12;
    tC = (func_8004787C(p->f6) * m) >> 12;
    p->f8 = t8 << 16;
    p->fC = tC << 16;

    p->f0 = (rand() & 0xf) + 0x10;
    p->f2 = m << 6;
    p->f4 = (s32)D_801F130E[0] * 64;
}




s32 func_8018EA7C(void) {

    extern s16 D_801F1314;
    s32 i = 0;
    s32 offset = 0;

    while (i < 0x10) {
        u16 val = *(u16*)((u8*)&D_801F1314 + offset);
        if (val == 0) {
            return i;
        }
        i++;
        offset += 0x10;
    }
    return -1;
}




/* func_8018EAB8 — the 16-slot particle/effect stepper over D_801F1314[16]
 * (0x10-byte records; slot 0 = the `active` u16 that func_8018AD5C clears and
 * func_8018B0EC scans).  Layout used here, all as byte-offsets off ONE walked
 * base pointer:
 *   +0x0 u16 active   +0x2 s16 angle   +0x4 u16 dangle
 *   +0x6 s16 dir      +0x8 s32 x       +0xC s32 z
 *
 * IV shape (cookbook §3-Giv / gcc-map L1): the target has ONE biv (the walked
 * base, kept alive by the bare +0x0 accesses, which find_mem_givs excludes from
 * giv formation) plus ONE combined DEST_ADDR giv anchored at base+2
 * (`addiu $s1, $s2, 0x2`).  combine_givs takes g1 from the list HEAD and
 * record_giv PREPENDS, so *the last-emitted offset reference anchors*: the
 * `+= dangle` statement (which ends on a +0x2 store) must therefore come LAST
 * in the body.  Written before the two s32 updates it anchors at base+0xC
 * instead -> 14 mismatched immediates.
 *
 * Both rsin/rcos products are computed BEFORE any store because gcc-2.7.2's
 * sched.c makes every mem ref depend on last_function_call — a store emitted
 * between the two `jal`s could not have floated below the second one.
 *
 * `i++` precedes the pointer bump in the for-increment: that emission order is
 * what puts `addiu $s4,$s4,1` ahead of the giv's `addiu $s1,$s1,0x10` (the
 * biv's own bump then fills the branch delay slot).
 *
 * func_80047948 / func_8004787C keep this TU's file-scope prototypes verbatim
 * (L2197-2198, `s32` param) — the s16 field is sign-extended at the call site
 * by the `lh`, so the narrower m2c-style `s16` prototype is not needed (§17a-1).
 * D_801F1314 uses the TU's existing block-scope `extern s16` spelling
 * (func_8018AD5C L3869, func_8018B0EC L3982).
 */

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8018EAB8(void) {

    extern s16 D_801F130E;
    extern s16 D_801F1314;
    extern void func_8018EBCC(s32);

    s16 *p;
    s32 i;
    s16 ang;
    s32 vx;
    s32 vz;

    ang = D_801F130E;
    p = &D_801F1314;

    for (i = 0; i < 0x10; i++, p = (s16 *)((s32)p + 0x10)) {
        if (*(u16 *)p != 0) {
            if ((ang > 0 && *(s16 *)((s32)p + 2) > 0x4000) ||
                (ang < 0 && *(s16 *)((s32)p + 2) <= 0)) {
                *p = 0;
            } else {
                func_8018EBCC(i);
                vx = func_80047948(*(s16 *)((s32)p + 6)) * ang * 0x10;
                vz = func_8004787C(*(s16 *)((s32)p + 6)) * ang * 0x10;
                *(s32 *)((s32)p + 8) += vx;
                *(s32 *)((s32)p + 12) += vz;
                *(u16 *)((s32)p + 2) += *(u16 *)((s32)p + 4);
            }
        }
    }
}



/* func_8018EBCC — spawns one 0x14-byte GPU packet from D_800A5E60, rotates /
 * scales a matrix copy of D_800AE620 by the D_801F1314[a0] record, projects the
 * four corner offsets into the packet, then links the packet into the OT.
 *
 * Byte-verified levers (all three were needed; each is worth 8-31 insns):
 *
 *  A. THE OT LINK IS THE libgpu P_TAG BITFIELD, NOT HAND-MASKING.  Writing
 *     `*(u32*)q = (*(u32*)q & 0xFF000000) | (ot & 0xFFFFFF)` is byte-correct
 *     arithmetic but gives the WRONG register assignment (16 mismatches: the
 *     0xFFFFFF / 0xFF000000 / &D_800B9A02 pseudos land in a0/a2/a3 permuted,
 *     and the `lw $v1,0($s3)` gets serialised behind the index load).  The
 *     `unsigned addr:24; unsigned len:8` bitfield insert reproduces both the
 *     allocation and the schedule exactly.  This is just `addPrim(ot, q)`.
 *
 *  B. THE OT TABLE MUST BE AN ARRAY_REF (`D_800A651C[i].a`), NOT
 *     `*(s32*)((u8*)&D_800A651C + i*20)`.  With the pointer-arith spelling gcc
 *     allocates a phantom 8-byte stack temp that is never referenced, pushing
 *     the frame from 0x68 to 0x70 (cookbook D6 in reverse: the frame is too
 *     BIG).  The temp only appears when the SAME lookup expression occurs in
 *     two statements; the ARRAY_REF form (engine_core.h `OtBlk`) kills it.
 *
 *  C. THE LAST ApplyMatrixSV RECOMPUTES THE MATRIX ADDRESS.  The first four
 *     matrix arguments come out of $s4 (`addu $aX,$s4,$zero`), but the fifth is
 *     `addiu $a0,$sp,0x10`.  cse.c cannot be talked out of folding a fifth
 *     `&m` into the existing pseudo: the conditional above it is a
 *     "branch around a block", so cse_end_of_basic_block EXTENDS the basic
 *     block through the join label (status AROUND) and the equivalence class
 *     for (plus fp 16) is still live.  Every source-level attempt to break it
 *     (pointer local, `mp = m` in the skipped arm, a §21 zero-byte re-tie,
 *     do{}while(0) loop notes) either changed nothing or cost 3 insns by
 *     turning the pointer into a two-def global allocno.  Pinning a reader to
 *     $sp makes the expression `(plus (reg 29) 16)` — a different rtx from
 *     `(plus (reg fp) 16)`, so cse never looks it up, and the single-use pseudo
 *     is folded by combine into the one `addiu` the target has.
 *
 *  The svp/outp block around the FIRST ApplyMatrixSV is load-bearing too:
 *  removing it costs 6 insns and two extra callee-saved registers.
 */

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixZ(s32 a0, void *a1);
extern void func_8004901C(void *a0, void *a1);
extern void func_80016638(void *a0, s32 a1, s32 a2);


/* 0x10-byte-stride record table at D_801F1314 (same table as func_8018AD5C) */

      /* the 0x20-byte matrix */
  /* == engine_types.h OtBlk */
          /* the D_800B9A02 buffer index */
 /* libgpu P_TAG */

void func_8018EBCC(s32 a0) {

    extern s16 D_801F1308;
    extern s16 D_801F130A;
    extern u8 D_801F1310;
    extern u8 D_801F1311;
    extern u8 D_801F1312;

    extern s16 D_801F1314;
    extern u8 *D_800A5E60;
    extern s32 D_800AE620;
    extern u8 D_800A6518[];
    extern Ot_8018B23C_8018EBCC D_800A651C[];

    s32 m[8];       /* sp+0x10 */
    u8 sv[8];       /* sp+0x30 */
    u16 out[4];     /* sp+0x38 */
    s32 scale[4];   /* sp+0x40 */

    u8 *q;
    Rec_8018B23C_8018EBCC *p;
    s32 x;
    s32 y;
    s32 ang;

    q = D_800A5E60;

    *(Mat32_8018B23C_8018EBCC *)m = *(Mat32_8018B23C_8018EBCC *)&D_800AE620;

    D_800A5E60 = q + 0x14;
    *(u8 *)(q + 3) = 4;
    *(u8 *)(q + 7) = 0x22;
    *(u8 *)(q + 4) = D_801F1310;
    *(u8 *)(q + 5) = D_801F1311;
    *(u8 *)(q + 6) = D_801F1312;

    p = (Rec_8018B23C_8018EBCC *)((s32)&D_801F1314 + (a0 << 4));
    x = p->fA + (u16)D_801F1308;
    y = p->fE + (u16)D_801F130A;
    RotMatrixZ(p->f6, m);

    scale[0] = *(s16 *)((s32)p + 2);
    scale[1] = *(s16 *)((s32)p + 2);
    scale[2] = *(s16 *)((s32)p + 2);
    func_8004901C(m, scale);

    *(s16 *)(sv + 4) = 0;
    *(s16 *)(sv + 2) = 0;
    *(s16 *)(sv + 0) = p->f0;
    {
        void *svp = sv;
        void *outp = out;
        ApplyMatrixSV(m, svp, outp);
        __asm__ __volatile__("" : "=r"(svp));  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B t3_tus1)
        __asm__ __volatile__("" : "=r"(outp));  // !FAKE: launder out-only — NEEDED DIFFERS (P36 rung B t3_tus1)
    }

    *(s16 *)(q + 0x8) = x + ((s16)out[0] >> 1) * 3;
    *(s16 *)(q + 0xA) = y + ((s16)out[1] >> 1) * 3;
    *(s16 *)(q + 0xC) = x - ((s16)out[0] >> 1);
    *(s16 *)(q + 0xE) = y - ((s16)out[1] >> 1);
    x = x + out[0];
    *(s16 *)(q + 0x10) = x;
    y = y + out[1];
    *(s16 *)(q + 0x12) = y;

    ang = -0x400;
    if (p->f0 & 1) {
        ang = 0x400;
    }
    RotMatrixZ(ang, m);

    *(s16 *)(sv + 0) = 2;
    {
        /* lever C: sp+0x10 IS &m, but spelled so cse cannot fold it to $s4 */
        register u8 *spr __asm__("$29");  // !FAKE: pin $29 — NEEDED DIFFERS (P36 rung B t3_tus1)
        ApplyMatrixSV(spr + 0x10, sv, out);
    }

    *(s16 *)(q + 0x10) = *(u16 *)(q + 0x10) + out[0];
    *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + out[1];

    {
        Bidx_8018B23C_8018EBCC *bp = (Bidx_8018B23C_8018EBCC *)&D_800B9A02;

        /* addPrim(&D_800A651C[bp->f].a[0x10], q) */
        ((PTag_8018B23C_8018EBCC *)q)->addr =
            ((PTag_8018B23C_8018EBCC *)(D_800A651C[bp->f].a + 0x40))->addr;
        ((PTag_8018B23C_8018EBCC *)(D_800A651C[bp->f].a + 0x40))->addr = (u32)q;
        func_80016638(&D_800A6518[bp->f * 20], 0x10, 1);
    }
}



extern void func_8018EFB0(void *a0);
extern void func_8018F02C(void *a0);
extern void func_8012931C(struct vec *a0);
extern void func_801292C8(u8 *a0);

void func_8018EEB0(void *a0) {
    if (*(u16 *)((s32)a0 + 0x2) == 0) {
        func_8018EFB0(a0);
        return;
    }

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(s32 *)((s32)a0 + 0x1C) -= 1;
        func_8012931C((struct vec *)a0);

        if (*(s16 *)((s32)a0 + 0x32) == 0) {
            u16 t = *(u16 *)((s32)a0 + 0xA) + 0x1000;
            if (t >= 0x1001) {
                func_801292C8((u8 *)a0);
                return;
            }
        }
    } else {
        func_801292C8((u8 *)a0);
        return;
    }

    *(s32 *)((s32)a0 + 0x14) += *(s32 *)((s32)a0 + 0x34);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) += *(u16 *)((s32)a0 + 0x30);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x8) = *(u16 *)((s32)a0 + 0x6);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0xA) = *(u16 *)((s32)a0 + 0xA);
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0xC) = *(u16 *)((s32)a0 + 0xE);
    func_8018F02C((void *)*(s32 *)((s32)a0 + 0x20));
}


#include "common.h"

extern s32 rand(void);

void func_8018EFB0(void *a0) {
    s32 *s1;
    s32 *s0;
    u16 v0_const;
    s32 rand_val;
    u16 *val_ptr;
    void *a02;
    a02 = a0;

    s1 = (s32 *)a02;
    v0_const = 0x0B;
    s0 = *(s32 **)((u8 *)s1 + 0x20);

    // Store 0x0B as halfword at offset 0x2
    *(u16 *)((u8 *)s0 + 0x2) = v0_const;

    // Load word from offset 0x4, OR with 0x50000000, store back
    *(s32 *)((u8 *)s0 + 0x4) |= 0x50000000;

    // If the halfword at offset 0x18 is 0, store 0x600
    if (*(s16 *)((u8 *)s0 + 0x18) == 0) {
        *(s16 *)((u8 *)s0 + 0x18) = 0x600;
    }

    // Call rand, mask to 0xFF0, store at offset 0x14
    rand_val = rand();
    *(u16 *)((u8 *)s0 + 0x14) = (u16)(rand_val & 0xFF0);

    // Load halfword at offset 0x2 of s1, increment, store back
    val_ptr = (u16 *)((u8 *)s1 + 0x2);
    *val_ptr = *val_ptr + 1;

    // Store 0x100 as halfword at offset 0x30 of s1
    *(s16 *)((u8 *)s1 + 0x30) = 0x100;
}


#define RD16(p) (((struct { u16 v; } *)(p))->v)
#define RW32(p) (((struct { u32 v; } *)(p))->v)

void func_8018F02C(void *a0)
{
    extern u8 D_800AF648;
    extern u8 *D_800A5E60;
    extern u8 D_800A6610[];
    extern void RotMatrixZ(s32 a0, void *a1);

    u8 stk[0x60];                        /* sp+0x10 .. sp+0x6F */
    u32 flags;
    u32 idx;
    u32 ot;
    u32 t2;
    u8 *pkt;
    u8 *p1;
    u8 *p2;
    u8 *pkb;
    s32 d;
    u32 *otp;
    register u32 tv __asm__("$3");       /* §137 pin — see header */  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B t3_tus1)
    register u32 tv2 __asm__("$4");      /* §137 pin — see header */  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)

    u8 *rotm;

    flags = *(u32 *)((s32)a0 + 4);
    rotm = &D_800AF648;

    gte_SetRotMatrix(rotm);
    gte_SetTransMatrix(rotm);
    gte_ldv0((s32)a0 + 8);
    gte_rtps();
    gte_stsxy(stk);
    gte_stflg(stk + 0x48);
    gte_stsz(stk + 0x4c);
    gte_stszotz(stk + 0x50);

    if ((*(u32 *)(stk + 0x48) & 0xFFFFEFFF) == 0) {
        idx = *(s32 *)(stk + 0x50) + 1;
        ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
        {
            u16 flags2 = *(u16 *)((s32)a0 + 0x2c);
            if ((flags2 & 0xC000) != 0) {
                if ((flags2 & 0xC000) == 0xC000) {
                    idx = idx - (flags2 & 0xFFF);
                    if ((s32)idx < 0) idx = 0;
                } else {
                    idx = idx + (flags2 & 0xFFF);
                }
            }
        }

        if (idx < 0x1000) {
            d = (s32)&stk[0x08];

            *(u16 *)(stk + 0x08) = *(u16 *)((s32)a0 + 0x18);
            *(u16 *)(stk + 0x0a) = 0;
            *(u16 *)(stk + 0x0c) = 0;
            *(u16 *)(stk + 0x0e) = 0;
            *(u16 *)(stk + 0x10) = *(u16 *)((s32)a0 + 0x18);
            *(u16 *)(stk + 0x12) = 0;
            *(u16 *)(stk + 0x14) = 0;
            *(u16 *)(stk + 0x16) = 0;
            *(u16 *)(stk + 0x18) = 0x1000;
            *(u32 *)(stk + 0x24) = 0;
            *(u32 *)(stk + 0x20) = 0;
            *(u32 *)(stk + 0x1c) = 0;

            RotMatrixZ(*(s16 *)((s32)a0 + 0x14), (void *)d);
            gte_SetRotMatrix((void *)d);
            gte_SetTransMatrix((void *)d);

            *(u16 *)(stk + 0x28) = 0x20;
            *(u16 *)(stk + 0x2a) = 0;
            *(s16 *)(stk + 0x2c) = (s16)*(u32 *)(stk + 0x4c);
            gte_ldv0(stk + 0x28);
            gte_rtps();
            gte_stsxy(stk + 0x54);

            d = (u16)((s16)(RD16(stk + 0x54)) >> 3);
            d |= (s32)((s16)(RD16(stk + 0x56)) >> 3) << 16;

            pkt = D_800A5E60;
            p1 = pkt + 0x18;
            *(u8 *)(pkt + 0x3) = 5;
            *(u8 *)(pkt + 0x7) = 0x28;
            *(u8 *)(p1 + 0x3) = 5;
            t2 = flags & 0x40000000;
            *(u8 *)(p1 + 0x7) = 0x28;
            if (t2 != 0) {
                *(u8 *)(pkt + 0x7) = *(u8 *)(pkt + 0x7) | 2;
                *(u8 *)(p1 + 0x7) = *(u8 *)(p1 + 0x7) | 2;
            }
            *(u8 *)(pkt + 0x4) = *(u8 *)((s32)a0 + 0x24);
            *(u8 *)(pkt + 0x5) = *(u8 *)((s32)a0 + 0x25);
            *(u8 *)(pkt + 0x6) = *(u8 *)((s32)a0 + 0x26);
            *(u8 *)(p1 + 0x4) = *(u8 *)((s32)a0 + 0x24);
            *(u8 *)(p1 + 0x5) = *(u8 *)((s32)a0 + 0x25);
            *(u8 *)(p1 + 0x6) = *(u8 *)((s32)a0 + 0x26);

            *(s16 *)(pkt + 0x8) = RD16(stk) + RD16(stk + 0x54);
            *(s16 *)(pkt + 0xa) = RD16(stk + 0x02) + RD16(stk + 0x56);
            *(s16 *)(pkt + 0xc) = RD16(stk) - (d >> 16);
            *(s16 *)(pkt + 0xe) = RD16(stk + 0x02) + d;
            *(s16 *)(pkt + 0x10) = RD16(stk) + (d >> 16);
            *(s16 *)(pkt + 0x12) = RD16(stk + 0x02) - d;
            *(s16 *)(pkt + 0x14) = RD16(stk) - RD16(stk + 0x54);
            *(s16 *)(pkt + 0x16) = RD16(stk + 0x02) - RD16(stk + 0x56);
            *(s16 *)(p1 + 0x8) = RD16(stk) - RD16(stk + 0x56);
            *(s16 *)(p1 + 0xa) = RD16(stk + 0x02) + RD16(stk + 0x54);
            *(s16 *)(p1 + 0xc) = RD16(stk) - d;
            *(s16 *)(p1 + 0xe) = RD16(stk + 0x02) - (d >> 16);
            *(s16 *)(p1 + 0x10) = RD16(stk) + d;
            *(s16 *)(p1 + 0x12) = RD16(stk + 0x02) + (d >> 16);
            *(s16 *)(p1 + 0x14) = RD16(stk) + RD16(stk + 0x56);
            *(s16 *)(p1 + 0x16) = RD16(stk + 0x02) - RD16(stk + 0x54);

            /* addPrim(otp, pkt); addPrim(otp, p1); */
            otp = (u32 *)((idx << 2) + ot);
            tv = RW32(pkt);
            RW32(pkt) = (tv & 0xFF000000) | (RW32(otp) & 0xFFFFFF);
            RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
            tv = RW32(p1);
            RW32(p1) = (tv & 0xFF000000) | (RW32(otp) & 0xFFFFFF);

            pkb = D_800A5E60;
            p2 = pkb + 0x30;
            D_800A5E60 = p2;
            RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)p1 & 0xFFFFFF);

            if (t2 != 0) {
                D_800A5E60 = pkb + 0x38;
                *(u8 *)(p2 + 3) = 1;
                RW32(p2 + 4) = ((flags >> 23) & 0x60) | 0xE1000000;
                tv2 = RW32(p2);
                RW32(p2) = (tv2 & 0xFF000000) | (RW32(otp) & 0xFFFFFF);
                RW32(otp) = (RW32(otp) & 0xFF000000) | ((u32)p2 & 0xFFFFFF);
            }
        }
    }
}



// @class: loose-typing
// @stuck: none — MATCH (99 ins). short* for param_2/param_3: gcc emits lh where sign is live (<<1 for signed div), lhu where truncated to short (arith result / direct copy)

extern int rand(void);
extern int func_8018F68C(short *pos, int a1, int a2);

void func_8018F4CC(unsigned short *param_1, short *param_2, short *param_3,
                   unsigned int param_4, int param_5)
{
    int r;
    int d;
    short buf[4];
    int p;

    if ((*param_1 & (short)((1 << param_4) - 1)) == 0) {
        r = rand();
        d = param_3[0] << 1;
        buf[0] = (param_2[0] + (r % d)) - param_3[0];
        r = rand();
        d = param_3[1] << 1;
        buf[1] = (param_2[1] + (r % d)) - param_3[1];
        r = rand();
        d = param_3[2] << 1;
        buf[2] = (param_2[2] + (r % d)) - param_3[2];
        buf[3] = param_3[3];
        p = func_8018F68C(buf, 0, param_5);
        if (p != 0) {
            *(short *)(*(int *)(p + 0x20) + 0x18) = param_2[3];
        }
    }
    *param_1 = *param_1 + 1;
}


#include "common.h"

extern int func_8018F68C(short *pos, int a1, int a2);

int func_8018F658(short *pos, int a1, int a2) {
    int ret;
    ret = func_8018F68C(pos, a1, a2);
    if (ret != 0) {
        *(s16 *)(ret + 0x32) = 1;
    }
    return ret;
}


#include "common.h"

extern u8 *func_801290DC(s32 a0, u8 *a1);

int func_8018F68C(short *pos, int a1, int a2)
{
    u8 *v1;

    v1 = func_801290DC(0x55, (u8 *)pos);

    if (v1 != 0) {
        *(s32 *)(v1 + 0x1C) = pos[3];

        if (a1 != 0) {
            *(s32 *)(v1 + 0x10) = *(s32 *)(a1 + 0x0);
            *(s32 *)(v1 + 0x14) = *(s32 *)(a1 + 0x4);
            *(s32 *)(v1 + 0x18) = *(s32 *)(a1 + 0x8);
            *(s32 *)(v1 + 0x34) = *(s32 *)(a1 + 0xC);
        }

        if (a2 != 0) {
            u8 *ptr = *(u8 **)(v1 + 0x20);
            *(s32 *)(ptr + 0x24) = a2;
        }
    }

    return (int)v1;
}


typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8_8018F734;

/* func_8018F734 (ov_SC03_117, ov_SC03_117_jr_8017BEBC) — MATCH (148 ins)
 *
 * Tapered-beam / laser quad renderer.  Builds a 4-vertex SVECTOR quad in local
 * space (x = 0 .. arg0->len, y = -/+ half-width, the near half-width at 0x18 and
 * the far one at 0x1A), rotates it with the caller's angle triple (0x08) through
 * func_80049CAC + func_80017E8C, allocates ONE 0x24-byte POLY_G4 out of
 * func_80010A08, projects the quad straight into the packet's four xy slots with
 * RotTransPers4, and links the packet into the current double-buffer OT with the
 * inline PSY-Q addPrim pair.  If arg0->flags (0x1C) has bit 30, it also emits a
 * 1-word 0xE1000200 DR_TPAGE prim carrying the semi-transparency mode
 * ((flags >> 23) & 0x60) and chains that in front of the poly.
 *
 * FRAME 0x88 = 0x28 outgoing args (RotTransPers4 takes 10) + v[4] (0x20) +
 * mtx (0x20) + opz/flag (8) + 6 saved regs (0x18).  Locals are declared in
 * increasing-address order, so v/mtx/opz/flag land at 0x28/0x48/0x68/0x6C.
 *
 * LEVERS (each byte-checked against asm/.../func_8018F734.s)
 *
 *  - `ot` is computed BEFORE the `len == 0` early return: sched1 never moves an
 *    insn across a bb boundary, and the target has the whole
 *    lui/lhu/lui/addiu/sll run plus `addu $s4,$v0,$v1` (the beqz delay slot)
 *    ahead of the branch.  Computing it after the guard costs 5 insns of drift.
 *
 *  - `(otz << 2) + (u32)ot`, NOT `ot + otz`: gcc keeps the written operand order
 *    for the `addu`, and the target is `addu $s0, $v0, $s4` (offset first).
 *    Same reason `&D_800A6610[idx << 14]` gives `addu $s4, $v0, $v1`.
 *
 *  - `mp` (a pointer local bound to &mtx) is what puts the matrix address in a
 *    callee-saved register ($s0) and turns both call-site setups into `addu
 *    $aN,$s0,$zero` moves.  Passing &mtx directly re-materialises
 *    `addiu $aN,$sp,0x48` at each site.  The mtx.t[] stores stay sp-relative
 *    because they are written through the array, not through mp.
 *
 *  - Every `*(u16 *)(arg0 + N)` / `*(u32 *)(arg0 + N)` is spelled out at each
 *    use instead of being cached in a local: the quad stores take the address of
 *    v[], and poly is a heap pointer, so gcc cannot disambiguate them from the
 *    arg0 loads and re-loads each one — which is exactly the target's two
 *    `lhu 0x18($s2)`, two `lhu 0x1A($s2)`, two `lw 0x10($s2)`, two
 *    `lw 0x14($s2)`.  `len` IS a local (one `lhu 0x6($s2)`, three uses).
 *
 *  - `u16` reads + `>> 1`: `lhu` then `srl` (combine rewrites the ashiftrt to
 *    lshiftrt because the zero_extend proves the sign bit clear), then `negu`.
 *
 *  - `otz` is u32 so the 0x1000 bound test emits `sltiu`, and the `+ 1` is a
 *    separate statement AFTER the flag test so dbr can steal it for the `bnez`
 *    delay slot (the target keeps `addu $a0,$v0,$zero` and `addiu $a0,$a0,1` as
 *    two insns; `ret + 1` in one expression folds them into one `addiu`).
 *
 *  - THE TAIL CLUSTER (the last 9 mismatches).  Two facts decide it:
 *      (a) `q[3] = 1` (byte 3) OVERLAPS the word at q[0], so sched sees a real
 *          memory dependence and the `lw 0($v0)` MUST be written after the sb —
 *          reading `*(u32 *)q` before it inverts the dep into an anti-edge and
 *          drags the load above `sb`/`lw 0x1C($s2)` (2 mismatches, var_e).
 *      (b) With the load after the sb, its dest is a single-set pseudo, so
 *          `adjust_priority`'s BIRTHING BOOST (sched.md §1.7) raises it to
 *          0x7f000001, it wins every tie the moment it is ready, and it sinks
 *          past `or`/`sw 4($v0)` (9 mismatches).  The target has it competing
 *          normally at priority 2 and winning the T-16 tie against the `ori`
 *          only on `potential_hazard` (memory beats ALU).
 *    `register u32 qt __asm__("$4")` fixes BOTH the boost and the allocation in
 *    one zero-byte edit: it is the whole residual.  (A dead
 *    `__asm__ volatile("":"=r"(qt))` boost-kill also reorders correctly but
 *    leaves the $a0/$a1 pair swapped — 5 mismatches; sharing ONE temp across
 *    both addPrim halves kills the boost too but makes it a global allocno that
 *    loses $v1 in the FIRST addPrim — 7 mismatches.  The pin alone is minimal.)
 *
 * DECLARATIONS / integration surface: `func_80049CAC` and `D_800B9A02` are
 * spelled VERBATIM as the destination TU already has them at file scope
 * (ov_SC03_117_jr_8017BEBC.c L2643 and L2464/L2466), so they merge silently.
 * `D_800A6610`, `func_80010A08`, `func_80017E8C` and `RotTransPers4` have NO
 * file-scope declaration anywhere in that TU, so they are block-scoped here to
 * keep the blast radius on the rest of the TU at zero.  The two local typedefs
 * do not collide with any name in the TU.
 */

typedef struct { s16 vx, vy, vz, pad; } SV_1A30_8018F734;
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_1A30_8018F734;   /* 0x20 bytes */

void func_8018F734(s16 *arg0)
{
    extern u8 D_800A6610[];
    extern void func_80049CAC(s32 a0, s32 a1);
    extern void *func_80010A08(s32);
    extern void func_80017E8C(void *);
    extern s32 RotTransPers4(void *, void *, void *, void *,
                             s32 *, s32 *, s32 *, s32 *, s32 *, s32 *);

    SV_1A30_8018F734 v[4];        /* sp+0x28 */
    MTX_1A30_8018F734 mtx;        /* sp+0x48 */
    s32 opz;             /* sp+0x68 */
    s32 flag;            /* sp+0x6C */

    u32 *ot;
    u32 *otp;
    u8 *poly;
    u8 *q;
    void *mp;
    u16 len;
    u32 otz;
    register u32 qt __asm__("$4");   /* §17 pin — kills the birthing boost AND  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B t3_tus1)
                                        keeps the $a0/$a1 pair in target order */

    ot = (u32 *)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    len = *(u16 *)(arg0 + 3);
    if (len == 0) {
        return;
    }

    v[0].vx = 0;
    v[0].vy = -(*(u16 *)(arg0 + 0xC) >> 1);
    v[0].vz = 0;
    v[1].vx = 0;
    v[1].vy = *(u16 *)(arg0 + 0xC) >> 1;
    v[1].vz = 0;
    v[2].vx = len;
    v[2].vy = -(*(u16 *)(arg0 + 0xD) >> 1);
    v[2].vz = 0;
    v[3].vx = len;
    v[3].vy = *(u16 *)(arg0 + 0xD) >> 1;
    v[3].vz = 0;

    mp = &mtx;
    func_80049CAC((s32)(arg0 + 4), (s32)mp);

    mtx.t[0] = arg0[0];
    mtx.t[1] = arg0[1];
    mtx.t[2] = arg0[2];

    poly = (u8 *)func_80010A08(0x24);
    *(u32 *)(poly + 0x04) = *(u32 *)(arg0 + 8);
    *(u32 *)(poly + 0x0C) = *(u32 *)(arg0 + 8);
    *(u32 *)(poly + 0x14) = *(u32 *)(arg0 + 0xA);
    *(u32 *)(poly + 0x1C) = *(u32 *)(arg0 + 0xA);
    poly[3] = 8;        /* setlen(poly, 8)  */
    poly[7] = 0x38;     /* setcode POLY_G4  */

    func_80017E8C(mp);

    otz = RotTransPers4(&v[0], &v[1], &v[2], &v[3],
                        (s32 *)(poly + 0x08), (s32 *)(poly + 0x10),
                        (s32 *)(poly + 0x18), (s32 *)(poly + 0x20),
                        &opz, &flag);

    if ((flag & 0xFFFFEFFF) != 0) {
        return;
    }
    otz = otz + 1;
    if (otz >= 0x1000) {
        return;
    }

    otp = (u32 *)((otz << 2) + (u32)ot);

    /* addPrim(otp, poly) */
    *(u32 *)poly = (*(u32 *)poly & 0xFF000000) | (*otp & 0xFFFFFF);
    *otp = (*otp & 0xFF000000) | ((u32)poly & 0xFFFFFF);

    if (*(u32 *)(arg0 + 0xE) & 0x40000000) {
        poly[7] |= 2;                       /* semi-transparent */
        q = (u8 *)func_80010A08(8);
        q[3] = 1;                           /* setlen(q, 1) */
        qt = *(u32 *)q;
        *(u32 *)(q + 4) = ((*(u32 *)(arg0 + 0xE) >> 23) & 0x60) | 0xE1000200;
        /* addPrim(otp, q) */
        *(u32 *)q = (qt & 0xFF000000) | (*otp & 0xFFFFFF);
        *otp = (*otp & 0xFF000000) | ((u32)q & 0xFFFFFF);
    }
}


extern void (*D_801EBE38[])(void);

void func_8018F984(void *a0) {
    D_801EBE38[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_801465C0(void);
extern void func_80146C3C(void);

extern void func_8001CBDC(s32 a0, s32 a1, s32 a2, s32 a3);



void func_8018F9C0(void *a0) {

    extern s16 D_801EBCC4[][2];
    extern u8 D_801EBCF0[];
    extern EffectSlot4_8018F9C0 D_801EBCFC[];
    extern u8 D_801EBD28[];
    extern EffectSlot4_8018F9C0 D_801EBD60;
    extern EffectSlot4_8018F9C0 D_801EBD88;
    extern EffectSlot4_8018F9C0 D_801EBD8C;
    extern EffectSlot4_8018F9C0 D_801EBDBC;
    extern EffectSlot4_8018F9C0 D_801EBDC0;
    extern EffectSlot4_8018F9C0 D_801EBDF0;
    extern EffectSlot4_8018F9C0 D_801EBDF4;
    extern EffectSlot4_8018F9C0 D_801EBE24;
    extern EffectSlot4_8018F9C0 D_801EBE28;
    register void *s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B t3_tus1)
    void *s1;

    s0 = a0;
    s1 = ((void *(*)(void))func_801465C0)();
    if (s1 != 0) {
        s32 idx;
        u8 uVar1;

        *(s32 *)((s32)s0 + 0x20) = (s32)s1;
        idx = *(s32 *)((s32)s0 + 0x2C);
        func_8001CBDC((s32)s1, (s32)D_801EBD28, D_801EBCC4[idx][0], D_801EBCC4[idx][1]);
        uVar1 = D_801EBCF0[*(s32 *)((s32)s0 + 0x2C)];
        *(s16 *)((s32)s1 + 0x2C) = 3;
        *(u8 *)((s32)s1 + 0x27) = uVar1;
        *(s16 *)((s32)s0 + 0x6) = 0;
        *(s16 *)((s32)s0 + 0xA) = 0x50;

        /* The shift chain below needs a BASIC-BLOCK BOUNDARY before every copy
           except the first: gcc-2.7.2 CSE is per-extended-BB, and inside one BB
           it reuses the previous copy's DESTINATION address register as the next
           copy's SOURCE address (costing the lui/addiu pair the target emits).
           `if (c) X else X` supplies the boundary and is cross-jumped away by
           jump2 AFTER regalloc, so it costs 0 instructions (128/128).

           The FIRST copy must stay in block 1 with the `lw 0x2C` / `li 0x50`
           pair, or the index pseudo crosses a block and becomes a GLOBAL allocno
           (regalloc map K8) -- local-alloc then hands $v0 to the 0x50 constant
           and global-alloc is left with $v1 (the REGALLOC-PERM $v0<->$v1 swap).
           Both must be LOCAL qtys in the same block for the target's assignment.
           Its destination is therefore spelled as an INTERIOR ADDRESS of the
           neighbouring symbol (idiom 7): `&D_801EBE24 + 4 == &D_801EBE28`, a
           CSE-distinct rtx, so the next copy still recomputes its source
           address. Both spellings relocate to 0x80196E94. */
#define COND (*(s32 *)((s32)s0 + 0x2C) > 0)
        *(EffectSlot4_8018F9C0 *)((s32)&D_801EBE24 + 4) = D_801EBCFC[*(s32 *)((s32)s0 + 0x2C)];
        if (COND) { D_801EBE24 = D_801EBE28; } else { D_801EBE24 = D_801EBE28; }
        if (COND) { D_801EBDF4 = D_801EBE24; } else { D_801EBDF4 = D_801EBE24; }
        if (COND) { D_801EBDF0 = D_801EBDF4; } else { D_801EBDF0 = D_801EBDF4; }
        if (COND) { D_801EBDC0 = D_801EBDF0; } else { D_801EBDC0 = D_801EBDF0; }
        if (COND) { D_801EBDBC = D_801EBDC0; } else { D_801EBDBC = D_801EBDC0; }
        if (COND) { D_801EBD8C = D_801EBDBC; } else { D_801EBD8C = D_801EBDBC; }
#undef COND
        D_801EBD88 = D_801EBD8C;
        D_801EBD60 = D_801EBD88;

        *(s16 *)((s32)s0 + 0x2) = *(s16 *)((s32)s0 + 0x2) + 1;
    } else {
        ((void (*)(void *))func_80146C3C)(s0);
    }
}


extern void func_8018FC00();
    void func_8018FBC0(void) {
        func_8018FC00();
    }


extern void func_80146C3C(void);
    void func_8018FBE0(void) {
        func_80146C3C();
    }



extern void func_80017254(void *a0);
extern void func_800176F0(void *a0);

void func_8018FC00(void) {

    extern u8 D_801EBD40[];
    extern u8 D_801EBD68[];
    u8 *p;
    s32 i;

    func_80017254(D_801EBD40);
    i = 0;
    p = D_801EBD68;
    do {
        func_800176F0(p);
        i++;
        p += 0x34;
    } while (i < 4);
}


extern s32 func_80146994(s32 a0, s32 a1, s32 a2, s32 a3);
    void func_8018FC58(void *a0) {
        ((void (*)(s32, s32, s32, s32))func_80146994)(0x28, 0, a0, 0);
    }



extern s32 func_8014C050(s32 a0, s32 a1);

void func_8018FC84(void) {

    extern s32 D_80126B58;
    s32 t;

    t = func_8014C050((s32)&D_80126B58, 0x28);
    if (t != 0) {
        *(u16 *)(t + 2) += 1;
    }
}



extern void (*D_801EBE74[])(void);

void func_8018FCC8(void *a0) {
    D_801EBE74[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
    void func_8018FD04(s32 arg0) {
        *(s16 *)(arg0 + 0x100) = 0x7D;
        *(s16 *)(arg0 + 0xFC) = 0;
        *(s16 *)(arg0 + 0xFE) = 0;
        *(s16 *)(arg0 + 0x102) = 0x533;
        ((void (*)(void))func_8012AD50)();
    }


extern u8 D_801EBE44[];
extern u16 D_80126B66;
extern void func_80190264(s32 a0, s32 a1);
extern void func_8018FE20(s32 a0, void *a1, void *a2, s32 a3);
extern void func_8012C098(void *a0);

void func_8018FD38(s32 arg0) {
    register s32 s2 __asm__("$18") = arg0;  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B t3_tus1)
    u8 *s0;
    u8 *s1;

    s0 = &D_801EBE44[0];
    func_80190264(s2, *(s16 *)(s2 + 0xFE));
    s1 = s0 + 8;
    func_8018FE20(s2, s0, s1, *(s16 *)(s2 + 0xFC));
    s0 += 0x10;
    *(u16 *)(s2 + 0xFE) += 0xC;
    func_80190264(s2, *(s16 *)(s2 + 0x100));
    func_8018FE20(s2, s0, s0 + 8, *(s16 *)(s2 + 0xFC));
    *(u16 *)(s2 + 0x100) += 0xC;
    func_80190264(s2, *(s16 *)(s2 + 0x102));
    func_8018FE20(s2, s1 + 0x18, s1 + 0x20, *(s16 *)(s2 + 0xFC));
    *(u16 *)(s2 + 0x102) += 0xC;

    if (*(s16 *)&D_80126B66 >= 0x901) {
        func_8012C098((void *)s2);
    }
}


#include "common.h"

/* func_8018FE20 (ov_SC04_011, ov_SC04_011_jr_8017D494) — 213 ins.
 *
 * Lightning/beam ribbon emitter.  Builds a local MATRIX (rotation filled by
 * func_80017D98, translation = the s16 xyz triple at arg1), takes the delta
 * arg2-arg1 as a u16 vector, then walks 15 segments: for segment i the far
 * endpoint `b` is (d*i)/16 with a sine wobble added to y
 * (func_8004787C(i*0x1800/15 + ang) << 4) / 4096, and `a` is the previous
 * segment's endpoint.  Each segment emits ONE 0x38-byte quad prim (v[0]=v[2]=a,
 * v[1]=v[3]=b) THREE times through func_80190174 — an outer glow pair
 * (f0/f1 = 0x78D878, or 0x80E080 when D_800B99DA is odd), a middle pass whose
 * f2/f3 come from the walking table D_801F1500, and a core pass with f0/f1
 * cleared — each pass nudging a different vertex pair.  f4 = 0x50000000.
 *
 * LEVERS (each byte-checked against asm/.../func_8018FE20.s)
 *
 *  - THE FRAME IS THE PROOF OF THE TYPES.  Locals are laid out in declaration
 *    order from 0x10 (= the 16-byte outgoing-arg area), which pins every size:
 *    prim 0x10 (0x38 = SVECTOR v[4] + s32 f0..f5), mtx 0x48 (0x20), d 0x68,
 *    a 0x70, b 0x78, e[2] 0x80.  `prim.f4` at 0x30 IS the sp+0x40 store, and
 *    the DEAD `sh $a2,0x8A($sp)` is e[1].vy — gcc-2.7.2 has no DSE, so a dead
 *    store to an aggregate member survives while cse forwards the value to the
 *    register the next statement uses (hence `h`, not `e[1].vy`, feeds b.vy).
 *
 *  - `<< 4`, NOT `* 16`.  fold-const rewrites `(x * 16) / 4096` to `x / 256`.
 *    LSHIFT_EXPR is not MULT_EXPR, so the shift form survives to give the
 *    target's `sll 4` + `addiu 0xFFF` + `sra 12`.
 *
 *  - PASS `&mtx` DIRECTLY at all three sites, do NOT bind it to an `mp` local
 *    (§148-A staircase: the hoisted COPY of &mtx is the 213th instruction and
 *    the extra movable that keeps the `(s16)arg3` sign-extend inside the loop;
 *    with `mp` the extend hoists and the draft is 212 ins / closeness 163).
 *
 *  - `pp` (a pointer local bound to &prim) IS required — every prim access in
 *    the loop is `$s0`-relative in the target; `prim.f4` stays sp-relative
 *    precisely because it is written before `pp` exists.
 *
 *  - BLOCK 2's VERTEX PAIRS ARE WRITTEN LOW-INDEX-FIRST even though they ISSUE
 *    high-first (the `sw $a3,0x2C($s0)` in the middle flips the pairing).
 *
 *  - arg3 IS A `short` PARAMETER, and the definition must be K&R: the TU's
 *    file-scope `extern void func_8018FE20(s32, void*, void*, s32);` would
 *    reject a prototyped `s16`, but a K&R `short` promotes to int and is
 *    compatible.  `s32 arg3` + an explicit `(s16)` cast schedules the entry
 *    block differently (6 residual prologue mismatches).
 *
 *  - DECLARATIONS FOLLOW THE TU (the earlier draft failed to COMPILE here):
 *    func_80190174 is DEFINED later in this TU with a `Prim34_80190174 *`
 *    first param whose typedef is not visible at this slot, so it is declared
 *    with an EMPTY C89 parameter list (compatible with the later prototyped
 *    definition: pointer/int args are self-promoting).  D_801F1500 keeps the
 *    TU's `s8 []` spelling (the table-filler neighbour's block-scope extern) and is cast
 *    ONCE into an s32 walker — the address is all the codegen needs.
 *
 * SYMBOLS (law 1c — every one re-checked against this .s's own relocations):
 * func_80017D98, func_8004787C, func_80190174, D_800B99DA, D_801F1500.
 */

typedef struct { s16 vx, vy, vz, pad; } SV_8018FE20;        /* 8 bytes, align 2 */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_8018FE20;     /* 0x20 */
typedef struct {
    SV_8018FE20 v[4];           /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
} PRIM_8018FE20;                /* 0x38 */

extern u16  D_800B99DA;
extern s8   D_801F1500[];
extern void func_80017D98(void *a0);
extern s32  func_8004787C(s32 a0);
extern void func_80190174();

extern void func_8018FE20(s32 a0, void *a1, void *a2, s32 a3);

void func_8018FE20(arg0, arg1, arg2, arg3)
    s32 arg0;
    void *arg1;
    void *arg2;
    short arg3;
{
    PRIM_8018FE20 prim;
    MTX_8018FE20 mtx;
    SV_8018FE20 d;
    SV_8018FE20 a;
    SV_8018FE20 b;
    SV_8018FE20 e[2];
    PRIM_8018FE20 *pp;
    s32 *tbl;
    s32 col;
    s32 i;
    s32 h;

    prim.f4 = 0x50000000;
    func_80017D98(&mtx);
    mtx.t[0] = *(s16 *)((s32)arg1 + 0);
    mtx.t[1] = *(s16 *)((s32)arg1 + 2);
    mtx.t[2] = *(s16 *)((s32)arg1 + 4);
    tbl = (s32 *)D_801F1500;
    d.vx = *(u16 *)((s32)arg2 + 0) - *(u16 *)((s32)arg1 + 0);
    d.vy = *(u16 *)((s32)arg2 + 2) - *(u16 *)((s32)arg1 + 2);
    col = 0x78D878;
    d.vz = *(u16 *)((s32)arg2 + 4) - *(u16 *)((s32)arg1 + 4);
    pp = &prim;
    b.vx = b.vy = b.vz = 0;
    if (D_800B99DA & 1) {
        col = 0x80E080;
    }
    i = 1;
    do {
        a = b;
        h = (func_8004787C(i * 0x1800 / 15 + arg3) << 4) / 4096;
        e[1].vy = h;
        b.vx = d.vx * i / 16;
        b.vy = h + d.vy * i / 16;
        b.vz = d.vz * i / 16;
        pp->v[0] = a;
        pp->v[1] = b;
        pp->v[2] = a;
        pp->v[3] = b;
        pp->f0 = pp->f1 = col;
        pp->f2 = pp->f3 = 0;
        pp->v[2].vy += 0x33;
        pp->v[3].vy += 0x33;
        pp->v[2].vx -= 0x19;
        pp->v[3].vx -= 0x19;
        func_80190174(pp, &mtx, i);
        pp->f2 = tbl[0];
        pp->f3 = tbl[1];
        tbl++;
        pp->v[2].vy -= 0x99;
        pp->v[3].vy -= 0x99;
        pp->v[2].vx += 0x4C;
        pp->v[3].vx += 0x4C;
        func_80190174(pp, &mtx, i);
        pp->f0 = pp->f1 = 0;
        pp->v[0].vy -= 0x1CC;
        pp->v[1].vy -= 0x1CC;
        pp->v[0].vx += 0xE6;
        pp->v[1].vx += 0xE6;
        func_80190174(pp, &mtx, i);
        i++;
    } while (i < 0x10);
}


#include "common.h"

/* func_80190174 (ov_SC04_011, ov_SC04_011_jr_8017D494) — mass lane draft.
 *
 * Copies a 0x34-byte (v[4] SVECTOR quad + 5 leading s32 fields f0..f4) struct
 * from arg0 onto the stack, zeroes one field pair depending on arg2 (1 -> f0/f2,
 * 15 -> f1/f3), calls func_80017E8C(arg1), then perspective-transforms the quad
 * in place with RotTransPers4 (input AND output pointers are the same four
 * &local.v[N] addresses — the projected screen xy overwrites vx/vy in place).
 * If the returned clip flag has no bits set outside 0x1000, sets v[0].vz to
 * 0xFFD and calls func_80017714(&local).
 *
 * Modeled on func_8018F734 in this same TU (L8430) which uses the identical
 * RotTransPers4(10-arg) / func_80017E8C / mp-in-$s0 shape, and on the
 * file-scope `Prim_8016E7C8` struct (SVECTOR v[4] + s32 f0..f5) carried at the
 * top of this TU — this function's local is the first 0x34 bytes of that
 * layout (v[4] + f0..f4).
 */



typedef struct {
    SVECTOR_8016E7C8 v[4];  /* 0x00, 0x20 bytes */
    s32 f0, f1, f2, f3, f4; /* 0x20 - 0x33 */
} Prim34_80190174;          /* sizeof == 0x34 */

void func_80190174(Prim34_80190174 *arg0, void *arg1, s32 arg2)
{
    extern void func_80017E8C(void *);
    extern s32 RotTransPers4(void *, void *, void *, void *,
                              void *, void *, void *, void *,
                              s32 *, s32 *);
    extern void func_80017714(void *);

    Prim34_80190174 local;
    void *mp;
    s32 otz;
    s32 flag;

    local = *arg0;

    if (arg2 == 1) {
        local.f2 = 0;
        local.f0 = 0;
    } else if (arg2 == 15) {
        local.f3 = 0;
        local.f1 = 0;
    }

    func_80017E8C(arg1);

    mp = &local;
    RotTransPers4(mp, &local.v[1], &local.v[2], &local.v[3],
                  mp, &local.v[1], &local.v[2], &local.v[3],
                  &otz, &flag);

    if ((flag & 0xFFFFEFFF) == 0) {
        local.v[0].vz = 0xFFD;
        func_80017714(mp);
    }
}


/* func_80190264 (ov_SC04_011, ov_SC04_011_jr_8017D494)
 *
 * Fills a 16-entry, 4-byte-stride table at D_801F1500 from an angle:
 * per entry i the base angle is d = (i << 8) - arg1 (a s16 that is
 * re-sign-extended at every use -> the sll/sra 16 pairs), and the three
 * bytes written are
 *     +0  abs(sin(d + 0x155) / 64)      (D_801F1500)
 *     +2  abs(sin(d + 0x155) / 128)     (D_801F1502)
 *     +1  cos(d) * 63 / 4096 - 128      (D_801F1501)
 * arg0 is unused (signature fixed by the caller func_8018FD38 above).
 *
 * The abs() is written open-coded because the operand is re-evaluated in
 * every arm: gcc-2.7.2 emits three separate `jal func_8004787C` per block
 * (test arm + both result arms) and folds the `(x >> 6) < 0` test back onto
 * the rounding-adjusted value, which is why the second `bgez` sits directly
 * after the `addiu $v0, $v0, 0x3F` with no shift in between.
 *
 * `k` is a deliberate second index pseudo: without it the D_801F1502 store
 * shares $s1 with the other two, the frame loses one saved register and the
 * function comes out 2 instructions short (the sw/lw pair) with the
 * `addu $s2, $s1, $zero` delay slot at 0x80190320 degrading to a nop.
 */

extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_80190264(s32 arg0, s32 arg1) {

    extern s8 D_801F1500[];
    extern s8 D_801F1501[];
    extern s8 D_801F1502[];

    s32 i;
    s32 j;
    s32 k;
    s16 d;

    i = 0;
    j = 0;
    do {
        d = (i << 8) - arg1;

        D_801F1500[j] = (func_8004787C(d + 0x155) / 64) < 0
                            ? -(func_8004787C(d + 0x155) / 64)
                            : (func_8004787C(d + 0x155) / 64);

        k = j;
        D_801F1502[k] = (func_8004787C(d + 0x155) / 128) < 0
                            ? -(func_8004787C(d + 0x155) / 128)
                            : (func_8004787C(d + 0x155) / 128);

        D_801F1501[j] = (func_80047948(d) * 63) / 4096 - 128;

        i++;
        j += 4;
    } while (i < 16);
}





