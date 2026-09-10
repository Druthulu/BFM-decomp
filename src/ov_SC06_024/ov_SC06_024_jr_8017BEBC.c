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
extern u8 D_80191D28;
extern u8 D_80191C98;
extern u8 D_80191C74;
extern u8 D_80191C50;
extern u8 D_80191D04;
extern u8 D_80191CE0;
extern u8 D_80191CBC;
extern u8 D_80191C2C;
extern void func_80145934(void);
extern u8 D_80191DB8;
extern u8 D_80191D94;
extern u8 D_80191D70;
extern u8 D_80191D4C;
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
extern unsigned char D_801911B0[];
extern unsigned char D_801911E0[];
extern unsigned char D_80191230[];
extern unsigned char D_80191260[];
extern unsigned char D_80191290[];
extern void func_80145EE8(s32 param_1);
extern void MoveImage(void *a0, s32 a1, s32 a2);
extern void func_80146074(void);
extern s32 func_80146128(void);
extern void func_80146360(void);
extern void func_801463A0();
extern void func_8014607C(void);
extern u8 D_80078EC1;
extern s32 D_80078EC8;
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
extern void (*D_801912E0[])(void *);
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
extern s32 D_801913A8[];
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
extern u8 D_80191430[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_80191438;
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
/* canonical TU type (engine_core) — read via *(u16*) cast */
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
extern int D_801DFF70;
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
extern s32 D_801152BC;
extern int func_8014F74C(s32 arg0);
extern s32 func_8014FA70(s32 a0);
extern s32 D_801DFF74;
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
extern s32 D_80191468;
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
extern void (*D_80191510[])(void);
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
extern void (*D_80191534[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80191524;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_80191548[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80191554[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_80191564[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_8019157C[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_8019156C;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_80191590[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801915AC[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_8019159C;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_801915C0[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_801915D4[])(void);
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
extern s32 D_801915E8;
extern void (*D_80191610[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_801915F0;
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
extern int (*D_8019165C[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_80191660[])(void);
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
extern unsigned short D_80191AC4[];
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
extern void (*D_80191AD4[])(void);
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
extern int D_801DFFA8;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80191AFC[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80191ADC;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80191AEC;
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
extern void (*D_80191B3C[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80191B44[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80191B10;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80191B50[])(void);
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
extern u8 D_80191B20;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801DFFB0;
extern s32 D_801DFFBC;
extern s32 D_801DFFC0;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80191B8C[])(s32 *);
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
extern s32 D_80191B60[];
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
extern s32 D_801DFFB8;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80191DDC[])(void);
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
extern char D_80191BFC[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80191E80[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80191FD4[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80191DF0;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80191FDC[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80191E00;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80191E20;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80191FE4[])(void);
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
extern void (*D_8019200C[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_80192018[])(void);
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
extern void (*D_80191E8C[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_801920BC;
extern void func_8015D380(s32 a0);
extern unsigned char D_801911A0[];
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
extern unsigned char D_801920D0[];
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
extern s8 D_8019210C[];
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
extern u16 D_80192154;
extern u16 D_80192156;
extern u16 D_80192158;
extern s32 D_8019215C;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_80192164;
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
extern int D_80191E70;
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
extern unsigned int D_801921E8[];
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
extern void (*D_80192298[])(void);
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
extern u16 D_801922C8[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_8019232C;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801DFFC8[];
extern void func_8016216C(void);
extern u8 D_80078EB0;
extern u8 D_80078EB1;
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80192350[])(void);
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
extern int D_801E0020[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_80192398[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_80192388;
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
extern char D_801DF6DC[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801923A0[])(void);
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
extern void (*D_801923F4[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_801923BC;
extern s16 D_801923F0;
extern s16 D_801923EE;
extern s16 D_801923EC;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80192400[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E0080;
extern u8 D_801E0081;
extern u8 D_801E0082;
extern u8 D_801E0083;
extern u8 D_801E0084;
extern u8 D_801E0085;
extern u8 D_801E0086;
extern u8 D_801E0087;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80192410[])(void);
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
extern s32 D_801E00C0;
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
extern void (*D_80192454[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_801924D0[];
extern s32 D_801924F0[];
extern u8 D_8019256C[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_8019258C[];
extern u8 D_801925AC[];
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
extern void (*D_80192648[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_801926C4[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801DF6EC;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_801926D0[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_801926D8[])(void);
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
extern void (*D_801927A0[])(void);
extern void func_80166618(void *a0);
extern void (*D_801927B0[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_801927C0[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_801927CC[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_8019272C[];
extern u8   D_80192740[];
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
extern void (*D_801927E4[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_801927EC[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_801927F4[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_801927FC[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80192804[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_8019280C[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80192814[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_801928C8[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_801928D0[])(void);
extern void func_80169F00(void *a0);
extern char D_80192880[];
extern char D_80192840[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80192908[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80192914[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_8019295C[])(void);
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
extern void (*D_801929D8[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E03E0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_801929CC[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80192A10[];
extern unsigned short D_80192A18[];
extern unsigned short D_80192A20[];
extern unsigned char D_801E03E8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E03E0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80192A28[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E051C;
extern M2C_UNK D_801E0520;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E04A8;
extern void (*D_80192A58[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E0524[];
extern u8 D_801E052C[];
extern u8 D_801E04DC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80192A60[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80192A7C[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80192A84[])(void);
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
extern void (*D_80192AEC[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80192A90;
extern u8 D_80192A9C;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80192B20[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80192B28[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80192B7C[])(void);
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
extern u16 D_80192BB0[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80192BA0[];
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
extern s32 D_80192BCC;
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
extern void (*D_80192C44[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80192C4C[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80192C54[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80192C5C[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80192C64[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80192C6C[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80192C78[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80192C84[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80192C90[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80192CA0[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80192CB0[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80192CB8[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80192CC0[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80192CC8[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80192CD0[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80192CD8[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80192CE0[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80192CE8[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80192CF0[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80192CF8[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80192D00[])(void);
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
extern void (*D_80192D08[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80192D10[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80192D18[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80192D20[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80192D28[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80192D30[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80192D38[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80192D40[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80192D48[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80192D50[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80192D58[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80192D60[])(void);
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
extern void (*D_80192DA4[])(void);
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
extern M2C_UNK D_80192D68;
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
extern void (*D_80192DD4[])(void);
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
extern void (*D_80192E10[])(void);
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
extern void (*D_80192E68[])();
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
extern void (*D_80192E78[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80192E80[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_80192FE8[])();
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
extern void (*D_80192FF4[])();
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
extern M2C_UNK D_801DF934;
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
extern s16 D_801E18F0;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801E0C60;
extern short D_801E1964;
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
extern s32 D_801E108C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E10B4;
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
extern s16 D_801E1070;
extern s32 func_8017A3B0(void);
extern short D_801E10AC;
extern short D_801E10A8;
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
extern s16 D_801E1074;
extern u16 D_801E10F4;
extern u16 D_801E10F6;
extern u16 D_801E10F8;
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
extern s16 D_801E10EC;
extern s16 D_801E10EE;
extern s16 D_801E10F0;
extern s16 D_801E10E4;
extern s16 D_801E10E6;
extern s16 D_801E10E8;
extern void func_8017B7A8(void);
extern s16 D_801E1104;
extern s16 D_801E1106;
extern s16 D_801E1108;
extern s16 D_801E110C;
extern s16 D_801E110E;
extern s16 D_801E1110;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801E10FC;
extern short D_801E10FE;
extern short D_801E1100;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801E1094;
extern SV4 D_801E109C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801E10BC[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801E10B8)(void);
extern void func_8017BD50(int param_1);
extern void (*D_801931D0[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
/* ==== end §8b carried decl layer ==== */

/* func_8017BEBC — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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










#define gte_stsxy3_f4(r0) __asm__ volatile (     \
    "swc2 $12, 8( %0 );"                         \
    "swc2 $13, 12( %0 );"                        \
    "swc2 $14, 16( %0 )"                         \
    :                                            \
    : "r"( r0 )                                  \
    : "memory" )






#include "../shared/ov/func_8017BEBC__t67f11bf2.h"


#include "common.h"

extern void func_8002931C(s32 a0);
extern s32 func_8017D7D4(s32 param_1);

extern u8 D_801939DC[];
extern u8 D_80193B1C[];

extern u8 *D_801274C8;
extern void *D_801274CC;

void func_8017CD9C(void)
{
    func_8002931C(0x3C00000);

    D_801274C8 = D_801939DC;
    D_801274CC = D_80193B1C;

    func_8017D7D4(0);
}


extern void func_8002931C(s32 a0);
extern u8 D_80193B80[];
extern u8 D_80193BE4[];
extern u8 *D_801274C8;
extern void *D_801274CC;
extern int func_8017D7D4(int);

void func_8017CDE4(void)
{
    func_8002931C(0x3C00000);
    D_801274C8 = D_80193B80;
    D_801274CC = D_80193BE4;
    func_8017D7D4(1);
}



extern void (*D_8019327C[])(void);

void func_8017CE2C(void *a0) {
    D_8019327C[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017D0D8(void);
extern void func_800167B8(s32 a0);

s32 func_8017CE68(s32 a0) {
    func_8017D0D8();
    func_800167B8(0);
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern s32 func_800167F0(s32 a0);

s32 func_8017CEAC(void) {
    return (func_800167F0(0) & 0xffff) != 0;
}




extern void func_8017D100(void);

s32 func_8017CED0(s32 a0) {
    func_8017D100();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}



extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017CF10(u8 *a0) {
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
    void func_8017CF8C(void) {
        func_800D1EBC();
    }



extern void (*D_80193290[])(void);

void func_8017CFAC(void *a0) {
    D_80193290[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);
extern void func_800D1E28(void);

s32 func_8017CFE8(s32 a0) {
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



extern void (*D_8019329C[])(void);

void func_8017D05C(void *a0) {
    D_8019329C[*(u8 *)((s32)a0 + 0x15)]();
}




extern void func_8017D128(void);

s32 func_8017D098(s32 a0) {
    func_8017D128();
    *(s32 *)(a0 + 0x28) = 10;
    *(u8 *)(a0 + 0x15) += 1;
    return 0;
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
void func_8017D0D8(void) {

    extern s32 D_801932A8(void *a0);
    ((void (*)(void *, s32))func_8016EE40)((void *)D_801932A8, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_801932B4;

void func_8017D100(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_801932B4, 0x1000000);
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_801932C8;

void func_8017D128(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_801932C8, 0x1000000);
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;
extern void func_8017D34C(void *a0);
extern u8 D_80126948[];

void func_8017D150(void) {
    D_80126954 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x1C7;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x20;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D34C, 0);
    func_8012A094((s32)D_80126948);
    func_8017D34C(D_80126948);
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017D34C(void *a0);
extern u8 D_80126948[];
extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017D1EC(void) {
    D_80126954 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x155;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x20;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D34C, 0x1);
    func_8012A094((s32)D_80126948);
    func_8017D34C(D_80126948);
}


extern void func_8014C6AC(void);
extern void func_8012A018(s32 a, s32 b);
extern void func_8017D34C(void *a0);
extern u8 D_80126948[];

void func_8017D288(void) {
    func_8014C6AC();
    func_8012A018((s32)func_8017D34C, 0x2);
    func_8017D34C(D_80126948);
}


extern void func_8014C6C0(void);
extern void func_8012A018(s32 a, s32 b);

extern s32 D_80126954;
extern s32 D_8012695C;
extern s16 D_80126968;
extern s16 D_8012696A;
extern s16 D_8012696C;
extern s16 D_80126976;
extern s16 D_80126978;
extern s16 D_8012697A;

void func_8017D34C(void *a0);

void func_8017D2C8(void)
{
    func_8014C6C0();
    D_80126954 = 0x190;
    D_8012695C = 0x4B0;
    D_80126968 = 0x1C7;
    D_8012696A = 0x800;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = -0x20;
    D_8012697A = 0;
    func_8012A018((s32)func_8017D34C, 0);
}



extern void (*D_801932D4[])(void);

void func_8017D34C(void *a0) {
    D_801932D4[*(u8 *)((s32)a0 + 0x4)]();
}


void func_8017D388(s32 a0) {

    typedef struct {
        s16 v[4];
    } Blk8_80126940_8017D388;

    extern s32 D_80126B58;
    extern s16 D_801932E0[];
    extern Blk8_80126940_8017D388 D_80126940;
    Blk8_80126940_8017D388 sp10;
    u8 t;
    s16 v0, v1;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_801932E0[t];
    }
    sp10 = D_80126940;

    /* Clamp sp10.v[0] */
    v1 = sp10.v[0];
    if (v1 < -0xF80) {
        sp10.v[0] = -0xF80;
    } else if (v1 < 0x941) {
        /* v1 stays unchanged */
    } else {
        sp10.v[0] = 0x940;
    }

    /* Clamp sp10.v[2] */
    v0 = sp10.v[2];
    if (v0 < -0x100) {
        sp10.v[2] = -0x100;
    } else if (v0 < 0x481) {
        /* v0 stays unchanged */
    } else {
        sp10.v[2] = 0x480;
    }

    func_8017D63C(a0, sp10.v);
}


typedef struct {
    s16 v[4];
} Blk8_80126940_8017D474;

void func_8017D474(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_801932E4[];
    extern Blk8_80126940_8017D474 D_80126940;
    Blk8_80126940_8017D474 sp10;
    u8 t;
    s16 v0, v1;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_801932E4[t];
    }
    sp10 = D_80126940;

    /* Clamp sp10.v[0] */
    v1 = sp10.v[0];
    if (v1 < -0xF50) {
        sp10.v[0] = -0xF50;
    } else if (v1 < -0xEAF) {
        /* v1 stays unchanged */
    } else {
        sp10.v[0] = -0xEB0;
    }

    /* Clamp sp10.v[2] */
    v0 = sp10.v[2];
    if (v0 < 0x900) {
        sp10.v[2] = 0x900;
    }

    func_8017D63C(a0, sp10.v);
}




void func_8017D550(s32 a0) {

    extern s32 D_80126B58;
    extern s16 D_801932E8[];
    extern Blk8_80126940_8017D474 D_80126940;
    Blk8_80126940_8017D474 sp10;
    u8 t;
    s16 v0, v1;

    if (func_80148800(&D_80126B58) & 3) {
        t = (*(u8 *)(a0 + 5) + 1) & 1;
        *(u8 *)(a0 + 5) = t;
        *(s32 *)(a0 + 0x14) = D_801932E8[t];
    }
    sp10 = D_80126940;

    /* Clamp sp10.v[0] */
    v1 = sp10.v[0];
    if (v1 < -0xF80) {
        sp10.v[0] = -0xF80;
    } else if (v1 < 0x941) {
        /* v1 stays unchanged */
    } else {
        sp10.v[0] = 0x940;
    }

    /* Clamp sp10.v[2] */
    v0 = sp10.v[2];
    if (v0 < 0x43E) {
        sp10.v[2] = 0x43E;
    } else if (v0 < 0x481) {
        /* v0 stays unchanged */
    } else {
        sp10.v[2] = 0x480;
    }

    func_8017D63C(a0, sp10.v);
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

void func_8017D63C(s32 param_1, s16 *param_2) {
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



extern void func_8013B7F4(void *a0, int a1);

int func_8017D7D4(int param_1)
{

    extern unsigned char D_801932EC[];
    int iVar1;
    iVar1 = *(int *)(D_801932EC + param_1 * 4);
    func_8013B7F4((void *)iVar1, 0);
}


extern void (*D_80193514[])(void);
extern s32 func_8017E8F8(s32 a0);
extern void func_8017F4FC(void *a0);
extern s32 func_8012BDBC(s32, s32);

void func_8017D804(s32 a0) {
    D_80193514[*(u16 *)(a0 + 0x2)]();
    if (*(u16 *)(a0 + 0x0) != 0) {
        func_8017E8F8(a0);
        func_8017F4FC((void *)a0);
        if (func_8012BDBC(a0, 0x200) == 0) {
            *(u16 *)(a0 + 0x5C) |= 0x4000;
        } else {
            *(u16 *)(a0 + 0x5C) &= 0xBFFF;
        }
    }
}


extern s32 func_8012C354(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8001CD9C(int, void *);
extern s32 func_8012C194(void);
extern void func_80128D60(s32, s32 *, s32 *);

extern u8 D_80193304[];
extern u8 D_801AA430[];
extern u8 D_80193470;
extern u8 D_80193471;
extern u8 D_80193472;
extern u8 D_801934B0[];
extern void (*D_80193438)(void);
extern s32 D_801E1120[];
extern u8 D_801E1128[];
extern s32 D_801E112C;
extern s32 D_801E1158;
extern s32 D_801AA37C[];
extern s32 D_801AA394;
extern u16 D_801E1130[];
extern u16 D_801E1134[];

void func_8017D89C(s32 param_1) {
    s32 s1;
    s32 p;
    s32 i;
    s32 j;
    s32 v;
    s32 o;
    u8 *s0;

    if (func_8012C354(param_1, &D_80193304) != 0) {
        func_8001D0E8(*(s32 *)(param_1 + 0x20), 0x7FFF, 0x7FFF);
        func_8012A828(param_1, &D_801AA430);
        s1 = func_8012C194();
        if (s1 != 0) {
            s0 = &D_80193470;
            *(s32 *)(param_1 + 0xD4) = s1;
            func_8001CD9C(s1, s0);
            *(s16 *)(s1 + 0x18) = 0x400;
            *(s16 *)(s1 + 0x1A) = 0x400;
            *(u16 *)(s1 + 0x2C) = 0xC010;
            *(s32 *)(s1 + 4) |= 0xD0000000;
            *s0 = 0x20;
            D_80193471 = 0x20;
            D_80193472 = 0x20;
        }
        s1 = func_8012C194();
        if (s1 != 0) {
            *(s32 *)(param_1 + 0xD8) = s1;
            func_8001CD9C(s1, &D_801934B0);
            *(s16 *)(s1 + 0x18) = 0x555;
            *(s16 *)(s1 + 0x1A) = 0x555;
            *(s32 *)(s1 + 4) |= 0xD0000000;
        }
        *(s16 *)(param_1 + 0xAE) = -1;
        *(s16 *)(param_1 + 0xD0) = 0xC0;
        *(s16 *)(param_1 + 0xCE) = 0xC0;
        *(s16 *)(param_1 + 0xCC) = 0xC0;
        *(s16 *)(param_1 + 0xD2) = -2;
        *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x80) = param_1 + 0xCC;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x80;
        p = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x20) + 0xC;
        i = 3;
        do {
            *(s16 *)(p + 6) = 0;
            p += 0xC;
        } while (--i >= 0);
        func_80128D60(0, D_801E1120, &D_80193438);
        *(s32 *)D_801E1128 = D_801AA37C[0];
        D_801E112C = D_801AA394;
        i = 0;
        do {
            o = i << 3;
            j = i + 1;
            v = *(s32 *)((s32)D_801AA37C + (j << 2));
            *(s32 *)((s32)D_801E1134 + o) = 0;
            *(s32 *)((s32)D_801E1130 + o) = v;
            i = j;
        } while (i < 5);
        D_801E1158 = 5;
        *(s16 *)(param_1 + 2) = 1;
    }
}


extern s32 func_8012BE54(s32 a0);

void func_8017DA9C(s32 a0) {
    s32 v0 = func_8012BE54(a0);
    if (v0 <= 0x23FFF) {
        *(s16 *)(a0 + 0x34) = 0;
        *(s16 *)(a0 + 0x2) = 2;
    }
}


extern s32 func_80128DB4(s32, s32 *);
extern void func_80128D60(s32, s32 *, s32 *);
extern s32 func_8012BEE8(s32 a0);
extern s32 D_801E1120[];
extern s32 D_80193418;
extern s32 D_801933F8;
extern s32 D_80193338;

void func_8017DAE0(s32 param_1)
{
    s32 *p;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        func_80128D60(0, D_801E1120, &D_80193418);
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        *(s32 *)(param_1 + 0x1C) = 0x3C;
        /* fall through */
    case 1:
        p = D_801E1120;
        func_80128DB4(0, p);
        if (func_8012BEE8(param_1) != 0) {
            func_80128D60(0, p, &D_801933F8);
            *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        }
        return;
    case 2:
        if (func_80128DB4(0, D_801E1120) == 1) {
            func_80128D60(0, D_801E1120, &D_80193338);
            *(u16 *)(param_1 + 0x2) = 5;
            *(u16 *)(param_1 + 0x34) = 0;
            *(u16 *)(param_1 + 0xAE) = 0;
        }
        return;
    }
}


extern void func_8012EC04(s32, s32, s32 *);
extern void func_8012F14C(s32, s32, s32);
extern s32 func_80132EF4(s32, s32);
extern s32 func_80128DB4(s32, s32*);
extern s32 func_8012BE54(s32);
extern void func_8017EC4C(s32);
extern void func_8017EADC(s32);
extern s32 func_8012BEE8(s32);
extern s32 func_8012BA10(s32, s32);
extern s32 func_8012BDBC(s32, s32);
extern void func_8002D4C8(s32, s32);
extern void func_80128D60(s32, s32 *, s32 *);

extern u8 D_80193470;
extern u8 D_80193471;
extern u8 D_80193472;
extern u16 D_80193378[];
extern u16 D_801933B8[];
extern void (*D_80193438)(void);
extern u16 D_80193440[];
extern u16 D_80193442;
extern u16 D_80193444;
extern s32 D_80126B58;
extern s32 D_801E1118;
extern s32 D_801E1120[];
extern s32 D_801E1158;

void func_8017DBFC(s32 arg0)
{
    s32 s0;
    s32 s1;
    u16 buf[16];
    u16 vec[8];

    s0 = arg0;
    switch (*(u16 *)(s0 + 0x34)) {
    case 0:
        *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        *(s32 *)(s0 + 0xE4) = *(s32 *)(s0 + 0xE4) & ~4;
        *(u16 *)(s0 + 0x100) = 0;
        *(u16 *)(s0 + 0x102) = 0;
        *(s32 *)(s0 + 0x1C) = 0;
        break;
    case 1:
        if (func_8012BEE8(s0) != 0) {
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        break;
    case 2:
    {
        s32 v0;
        s32 v1;
        v0 = func_8012BA10(s0, 8);
        v1 = *(s32 *)(s0 + 0x20);
        *(s16 *)(v1 + 0x12) = *(s16 *)(v1 + 0x12) + v0;
        if (func_8012BDBC(s0, 0x100) != 0) {
            *(s32 *)(s0 + 0x1C) = 0x1E;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8002D4C8(0x95A, 0);
        }
        break;
    }
    case 3:
    {
        s32 v0;
        s32 v1;
        v0 = func_8012BA10(s0, 8);
        v1 = *(s32 *)(s0 + 0x20);
        *(s16 *)(v1 + 0x12) = *(s16 *)(v1 + 0x12) + v0;
        if (func_8012BEE8(s0) != 0) {
            *(s32 *)(s0 + 0x1C) = 7;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8002D4C8(4, 0x95A);
        }
        *(u16 *)(s0 + 0x102) = *(u16 *)(s0 + 0x102) + 0x10;
        func_8017EADC(s0);
        break;
    }
    case 4:
    {
        s32 v0;
        s32 v1;
        s1 = func_80132EF4(&D_80126B58, 0x5B);
        if (s1 != 0) {
            v0 = *(s32 *)(s0 + 0x1C);
            v1 = *(s32 *)(s1 + 0x20);
            *(s16 *)(v1 + 0x1A) = v0 << 12;
            *(s16 *)(v1 + 0x18) = v0 << 12;
            *(u16 *)(s1 + 0xA) = *(u16 *)(s1 + 0xA) - 0x30;
            if (*(s32 *)(s0 + 0x1C) == 7) {
                func_8002D4C8(0x95B, 0);
            }
        }
        if (func_8012BEE8(s0) != 0) {
            *(u16 *)(s0 + 0x102) = 0;
            *(s32 *)(s0 + 0x1C) = 0x1E;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_80128D60(0, D_801E1120, D_80193378);
            *(s32 *)(*(s32 *)(s0 + 0xD4) + 4) &= 0x7FFFFFFF;
            D_80193470 = 0x20;
            D_80193471 = 0x20;
            D_80193472 = 0x20;
        }
        break;
    }
    case 5:
    {
        u8 *p = &D_80193470;
        *p = *p + 7;
        D_80193471 = D_80193471 + 7;
        D_80193472 = D_80193472 + 7;
        if (func_8012BEE8(s0) != 0) {
            func_80128D60(0, D_801E1120, D_801933B8);
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            func_8002D4C8(0x95C, 0);
        }
        break;
    }
    case 6:
        *(u16 *)(s0 + 0x102) = *(u16 *)(s0 + 0x102) + 0x18;
        if ((*(s32 *)(s0 + 0xE4) & 4) != 0) {
            *(s32 *)(s0 + 0x1C) = 0x20;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        func_8017EC4C(s0);
        break;
    case 7:
    {
        s32 v1;
        *(u16 *)(s0 + 0x102) = *(u16 *)(s0 + 0x102) + 0x18;
        if (func_8012BEE8(s0) != 0) {
            *(s32 *)(s0 + 0x1C) = 0x60;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
            v1 = *(s32 *)(s0 + 0x20);
            if ((u32)((*(u16 *)(v1 + 0x12) & 0xFFF) - 0x501) < 0x800) {
                func_8002D4C8(0x963, 0);
                D_801E1118 = 0;
            } else {
                func_8002D4C8(0x962, 0);
                D_801E1118 = 1;
            }
        }
        func_8017EC4C(s0);
        break;
    }
    case 8:
    {
        s32 v0;
        s32 v1;
        *(u16 *)(s0 + 0x102) = *(u16 *)(s0 + 0x102) + 0x18;
        v1 = *(s32 *)(s0 + 0x20);
        *(s16 *)(v1 + 0x12) = *(s16 *)(v1 + 0x12) + 0x80;
        v0 = *(u16 *)(*(s32 *)(s0 + 0x20) + 0x12) & 0xFFF;
        if (D_801E1118 != 0) {
            if ((u32)(v0 - 0x501) < 0x800) {
                func_8002D4C8(0x963, 0);
                D_801E1118 = 0;
            }
        } else {
            if ((u32)(v0 - 0x501) >= 0x800) {
                func_8002D4C8(0x962, 0);
                D_801E1118 = 1;
            }
        }
        if (func_8012BEE8(s0) != 0) {
            *(s32 *)(s0 + 0x1C) = 0xA;
            *(u16 *)(s0 + 0x34) = *(u16 *)(s0 + 0x34) + 1;
        }
        if ((*(s32 *)(s0 + 0xE4) & 4) != 0) {
            s1 = func_80132EF4(s0, 0x22);
            if (s1 != 0) {
                func_8012EC04(s0, D_801E1158, buf);
                vec[0] = D_80193440[0];
                vec[1] = D_80193442;
                vec[2] = D_80193444 - 0xD0;
                func_8012F14C(buf, vec, &vec[4]);
                *(u16 *)(s1 + 0x34) = 0x3000;
                *(u16 *)(s1 + 6) = vec[4];
                *(u16 *)(s1 + 0xA) = vec[5];
                *(u16 *)(s1 + 0xE) = vec[6];
            }
        }
        func_8017EC4C(s0);
        break;
    }
    case 9:
    {
        s32 v0;
        s32 v1;
        u8 *p;
        *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x100) + 0x18;
        if ((*(s32 *)(s0 + 0xE4) & 4) == 0) {
            *(u16 *)(s0 + 0x102) = *(u16 *)(s0 + 0x102) + 0x18;
        }
        if (func_8012BEE8(s0) == 0) {
            p = &D_80193470;
            *p = *p - 0x18;
            D_80193471 = D_80193471 - 0x18;
            D_80193472 = D_80193472 - 0x18;
        }
        v0 = *(s16 *)(s0 + 0x100) - *(s16 *)(s0 + 0x102);
        if (v0 >= 0) {
            if (v0 < 0x20) {
                goto Ljoin9;
            }
            goto Lexit9;
        }
        if (*(s16 *)(s0 + 0x102) - *(s16 *)(s0 + 0x100) >= 0x20) {
            goto Lexit9;
        }
    Ljoin9:
        *(u16 *)(s0 + 0x100) = *(u16 *)(s0 + 0x102);
        v1 = func_8012BE54(s0);
        if (0x2FFFF < v1) {
            func_80128D60(0, D_801E1120, ((u16 *)&D_80193438));
            *(u16 *)(s0 + 2) = 1;
        } else {
            *(u16 *)(s0 + 2) = 3;
        }
        *(u16 *)(s0 + 0x34) = 0;
        *(s32 *)(*(s32 *)(s0 + 0xD4) + 4) |= 0x80000000;
        *(s32 *)(*(s32 *)(s0 + 0xD8) + 4) |= 0x80000000;
        func_8002D4C8(4, 0x95C);
        break;
    Lexit9:
        func_8017EC4C(s0);
        break;
    }
    default:
        break;
    }
    ((void (*)(s32, s32 *))func_80128DB4)(0, D_801E1120);
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_80128D60(s32 a0, s32 *a1, s32 *a2);
extern s32 func_80128DB4(s32 a0, s32 *a1);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_8012C51C(void *a0, s32 a1);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 rand(void);

extern s32 D_801E1120[];
extern s32 D_80193338;
extern s16 D_80193448[];
extern u8 D_80193530[];
extern s32 D_801E111C;
extern s32 D_801E1158;

void func_8017E1F0(s32 param_)
{
    s32 s1;
    register s32 ent __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 i __asm__("$18");  // !FAKE: pin $18 — NEEDED DIFFERS (P36 rung B tus9)
    s32 k;
    struct {
        s16 m[16];
        s16 out[4];
        s16 ax, ay, az;
        s16 w03;
        s16 idx;
        s16 f06;
        s16 f07;
        s16 f08;
        s32 f09;
    } frm;
    s32 *pp;
    s16 *cp;
    s32 cnt;
    s32 rnd;
    s32 cur;
    s32 ret;
    s32 idx;
    s32 tbl;
    s32 tmp;

    s1 = param_;
    switch (*(u16 *)(s1 + 0x34)) {
    case 0:
        *(s32 *)(s1 + 0x1C) = 0;
        *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
        func_80128D60(0, D_801E1120, &D_80193338);
        break;
    case 1:
        if (func_8012BEE8(s1) != 0) {
            func_8002D4C8(0x956, 0);
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
        }
        break;
    case 2:
        pp = *(s32 **)(s1 + 0x20);
        pp = (s32 *)*(s32 *)((s32)pp + 0x20);
        i = 3;
        cp = (s16 *)pp + 6;
        do {
            cp[3] = *(u16 *)(s1 + 0xFE);
            cp += 6;
        } while (--i >= 0);
        *(u16 *)(s1 + 0xFE) = *(u16 *)(s1 + 0xFE) + 0x1E;
        if (*(s16 *)(s1 + 0xFE) < 0x385) {
            break;
        }
        *(u16 *)(s1 + 0xFE) = 900;
        *(s32 *)(s1 + 0x1C) = 0;
        *(s32 *)(s1 + 0xE0) = 0;
        *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
        func_8002D4C8(4, 0x956);
        func_8002D4C8(0x957, 0);
        break;
    case 3:
        if (func_8012BEE8(s1) == 0) {
            break;
        }
        tmp = D_801E1158;
        frm.w03 = 0x2D5;
        frm.f06 = 0;
        frm.f09 = 0;
        frm.f08 = 0;
        frm.f07 = 0x7FFF;
        *(u16 *)(s1 + 0x108) = 0;
        func_8012EC04(s1, tmp, (s32 *)frm.m);
        k = 0;
        while (k < 4) {
            func_8012F14C((s32)frm.m, (s32)&D_80193448[k * 4], (s32)frm.out);
            frm.idx = k;
            frm.ax = frm.out[0];
            frm.ay = frm.out[1];
            frm.az = frm.out[2];
            func_8012C51C(&frm.ax, s1);
            ent = func_80132EF4(s1, 0x22);
            if (ent != 0) {
                *(u16 *)(ent + 0x34) = rand() & 1 | 0x2000;
                *(u16 *)(*(s32 *)(ent + 0x20) + 0x2C) = 0xC006U;
                frm.out[1] = frm.out[1] - 0x20;
                *(s16 *)(ent + 6) = frm.out[0];
                *(s16 *)(ent + 0xA) = frm.out[1];
                *(s16 *)(ent + 0xE) = frm.out[2];
            }
            k++;
        }
        func_8002D4C8(0x953, 0);
        cnt = *(s32 *)(s1 + 0xE0) + 1;
        *(s32 *)(s1 + 0xE0) = cnt;
        if (cnt < 2) {
            rnd = rand();
            cur = *(s16 *)(*(s32 *)(s1 + 0x20) + 0x12);
            idx = rnd % 4;
            tbl = cur + *(s16 *)&D_80193530[idx * 2];
            *(u16 *)(s1 + 0x34) = 5;
            *(s32 *)(s1 + 0x1C) = 0x1E;
            D_801E111C = tbl;
        } else {
            *(s32 *)(s1 + 0x1C) = 0;
            *(u16 *)(s1 + 0x34) = *(u16 *)(s1 + 0x34) + 1;
        }
        break;
    case 4:
        if (func_8012BEE8(s1) != 0) {
            *(u16 *)(s1 + 2) = 4;
            *(u16 *)(s1 + 0x34) = 0;
            func_8002D4C8(0x958, 0);
        }
        break;
    case 5:
        if (func_8012BEE8(s1) != 0) {
            ret = func_8012B608(*(s16 *)(*(s32 *)(s1 + 0x20) + 0x12), D_801E111C, 8);
            *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(s1 + 0x20) + 0x12) + ret;
            if (ret == 0) {
                *(u16 *)(s1 + 0x34) = 3;
            }
        }
        break;
    }
    func_80128DB4(0, D_801E1120);
}


extern s32 func_80128DB4(s32, s32 *);
extern void func_80128D60(s32, s32 *, s32 *);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8012BE54(s32 a0);
extern s32 D_801E1120[];
extern void (*D_80193438)(void);

void func_8017E548(s32 param_1) {
    s32 i;
    char *p;
    u16 uVar1;

    p = (char *)(*(s32 *)(*(s32 *)(param_1 + 0x20) + 0x20) + 0xC);
    for (i = 3; i >= 0; i--) {
        *(u16 *)(p + 6) = *(u16 *)(param_1 + 0xFE);
        p += 12;
    }
    uVar1 = *(u16 *)(param_1 + 0xFE) - 0x1E;
    *(u16 *)(param_1 + 0xFE) = uVar1;
    if ((s16)uVar1 < 0) {
        if (func_8012BE54(param_1) > 0x2FFFF) {
            func_80128D60(0, D_801E1120, &D_80193438);
            *(s16 *)(param_1 + 2) = 1;
        } else {
            *(s16 *)(param_1 + 2) = 5;
        }
        *(u16 *)(param_1 + 0xFE) = 0;
        *(s16 *)(param_1 + 0x34) = 0;
        func_8002D4C8(4, 0x958);
        func_8002D4C8(0x959, 0);
    }
    func_80128DB4(0, D_801E1120);
}


extern void func_80128D60(s32, s32*, s32*);
extern void func_8001C924(s32, void*);
extern void func_8012A828(s32, void*);
extern s32 func_8012C658(s32, s32, s32);
extern s32 func_80128DB4(s32, s32*);
extern s32 func_8012BEE8(s32);
extern s32 func_8002A04C(s32);
extern s32 func_8012E57C(s32, s32);
extern void func_8012C218(s32);
extern s32 func_80132EF4(s32, s32);
extern void func_8012B0B4(u32*, s32, s32);
extern void func_8002D4C8(s32, s32);
extern s32 rand(void);
extern s32 D_801E1120[];
extern u8 D_801E1128[];
extern s32 D_80193418;
extern s32 D_80193504[];
extern s32 D_801E1158;

void func_8017E61C(s32 p) {
    s32 e;
    s32 m;
    s32 i;
    s32 n;
    s32 r;
    s32 v;
    s32 w;
    s32 t;
    u32 buf[4];

    switch (*(u16 *)(p + 0x34)) {
    case 0:
        func_80128D60(0, D_801E1120, &D_80193418);
        *(s32 *)(p + 0x1C) = 0x3D;
        *(u16 *)(p + 0x34) += 1;
        *(u32 *)(*(s32 *)(p + 0xD4) + 4) |= 0x80000000;
        *(u32 *)(*(s32 *)(p + 0xD8) + 4) |= 0x80000000;
        func_8001C924(*(s32 *)(p + 0x20), &D_801E1128);
        func_8012A828(p, &D_80193504);
        D_801E1158 = 1;
        for (i = 0; i < 5; i++) {
            func_8012C658(0x3B4, i, p);
        }
        *(u32 *)(p + 0xE4) &= ~1;
        *(u32 *)(p + 0xE4) &= ~2;
        func_8002D4C8(4, 0x95A);
        func_8002D4C8(4, 0x95C);
        func_8002D4C8(0xB92, 0);
        break;
    case 1:
        n = rand() % 5;
        i = 0;
        if (n > 0) {
            do {
                e = func_80132EF4(p, 0x23);
                if (e != 0) {
                    func_8012B0B4(buf, rand() % 0x1000, 0x60);
                    w = buf[0];
                    *(u16 *)(e + 6) += w;
                    *(u16 *)(e + 0xA) = (t = *(u16 *)(e + 0xA) - 0x180) - rand() % 0xC0;
                    *(u16 *)(e + 0xE) += w >> 16;
                    r = rand();
                    v = rand();
                    *(u16 *)(e + 0x34) = ((r % 0x6000) + 0x1000) & 0x7FF0 | v & 1;
                    *(u16 *)(*(s32 *)(e + 0x20) + 0x2C) = 0xC010;
                }
                i++;
            } while (i < n);
        }
        func_80128DB4(0, D_801E1120);
        if (func_8012BEE8(p) != 0) {
            *(u16 *)(p + 0x34) += 1;
            func_8002A04C(p);
            m = func_8012E57C(0x390, 0);
            if (m != 0) {
                func_8012C218(m);
            }
        }
        break;
    case 2:
        break;
    }
}


#include "common.h"

/* declarations copied verbatim from src/ov_SC06_024/ov_SC06_024_jr_8017BEBC.c */
extern void func_8016AA50(s32 param_1, s32 param_2);
extern s32 func_8004787C(s32 a0);

s32 func_8017E8F8(s32 a0) {
    s16 t;
    u16 st;
    s16 *q;
    t = *(s16 *)(a0 + 0x106);
    if (t != 0) {
        q = *(s16 **)(*(s32 *)(a0 + 0x20) + 0x80);
        t = t - 1;
        *(s16 *)(a0 + 0x106) = t;
        if (t == 0) {
            q[2] = 0xC0;
            q[1] = 0xC0;
            q[0] = 0xC0;
        } else {
            q[0] = ((func_8004787C(t << 6) << 6) >> 12) + 0xC0;
            q[2] = 0;
            q[1] = 0;
        }
        *(s16 *)(a0 + 0x5E) = 0;
        *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFFFE;
        return 0;
    }

    if (*(s16 *)(a0 + 0x76) <= 0) {
        return 0;
    }
    if ((*(u16 *)(a0 + 0x5C) & 1) == 0) {
        return 0;
    }

    st = *(u16 *)(a0 + 0x5E);
    /* the store is written in EACH arm: cse then never sees store-then-reload,
       and cross_jump (jump2, after sched2) merges the identical `sh` suffix
       into the single one the target shows at .L8017EA20.  (§193-C) */
    if (st == 0x23 || st == 0x24) {
        *(s16 *)(a0 + 0x60) = 8;
    } else if (st == 0x2A) {
        *(s16 *)(a0 + 0x60) = (s16) * (u16 *)(a0 + 0x60) / 10;
    } else {
        *(s16 *)(a0 + 0x60) = (s16) * (u16 *)(a0 + 0x60) / 5;
    }
    func_8016AA50(a0, *(s16 *)(a0 + 0x60));

    *(s16 *)(a0 + 0x106) = 8;
    *(s16 *)(a0 + 0x5E) = 0;
    *(u16 *)(a0 + 0x76) = *(u16 *)(a0 + 0x76) - *(u16 *)(a0 + 0x60);
    *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFFFE;

    if (*(u16 *)(a0 + 0x76) >= 0x1F && *(u16 *)(a0 + 0x76) <= 0x32) {
        *(s32 *)(a0 + 0xE4) |= 1;
    }
    if (*(u16 *)(a0 + 0x76) >= 0xB && *(u16 *)(a0 + 0x76) <= 0x1E) {
        *(s32 *)(a0 + 0xE4) = (*(s32 *)(a0 + 0xE4) & ~1) | 2;
    }
    if (*(s16 *)(a0 + 0x76) <= 0) {
        *(s16 *)(a0 + 0x2) = 6;
        *(s16 *)(a0 + 0x34) = 0;
    }
    return 1;
}


extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern void func_8012B77C(void *a0, s32 a1, void *a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern s32 func_800133BC();
extern void func_800484EC(s32 a0, s32 a1, s32 a2);
extern void func_8012D3B4(s32 a0, s32 a1, s32 a2);
extern s32 D_801E1158;
extern u16 D_80193440[];
extern u16 D_80193468[];
extern u8 D_80126B5C;
extern s32 D_80126B64;
extern s32 D_80126B60;

void func_8017EADC(s32 a0) {
    s16 m[16];
    s16 s1[4];
    s16 tmp2[3];
    s16 tmp[3];
    s32 s2[3];
    s16 s3[6];
    s16 outb[6];
    s32 val;

    func_8012EC04(a0, D_801E1158, (s32 *)m);
    func_8012F14C((s32)m, (s32)&D_80193468, (s32)s1);
    func_8012F14C((s32)m, (s32)&D_80193440, *(s32 *)(a0 + 0xD4) + 8);

    s2[0] = *(s32 *)&D_80126B5C;
    s2[1] = D_80126B60 + 0xFFD00000;
    s2[2] = D_80126B64;
    s3[1] = s1[0];
    s3[3] = s1[1];
    s3[5] = s1[2];
    func_8012B77C(&val, (s32)s3, (s32)s2);

    tmp[0] = val;
    tmp[1] = val >> 16;
    tmp[2] = 0;
    func_80049CAC((s32)tmp, (s32)m);

    *(s16 *)(a0 + 0x102) = func_800133BC((s32)s1, (s32)s2);

    *(s32 *)&s3[2] = 0;
    *(s32 *)&s3[0] = 0;
    s3[5] = -*(u16 *)(a0 + 0x102);
    s3[4] = 0;
    func_800484EC((s32)m, (s32)s3, (s32)outb);

    tmp2[0] = s1[0] + outb[1];
    tmp2[1] = s1[1] + outb[3];
    tmp2[2] = s1[2] + outb[5];
    func_8012D3B4((s32)s1, (s32)tmp2, 0xFF);
}


/* func_8017EC4C  (ov_SC06_024, TU ov_SC06_024_jr_8017BEBC.c) — S68 fable escalation, MATCH 556/556.
 *
 * Warm-started from the opus draft (closeness 16); every opus lever preserved:
 * func_8012EC04(param_1,..), D_80193440[1]/[2] spelling, dbase in $fp with the
 * raw *(u16*)(dbase+0xA3AA) parity read, 16-byte stride on D_80193550/54/58/5C,
 * the g{} frame sizing, the in-place abs #1 + zero-byte asm on n (verified
 * load-bearing: removing it costs -2 length; its addu $a0,$s1,$zero copy is IN
 * the target), the blez guard shape, the two-armed 0x102 write, i reuse, otp/otq.
 *
 * What closed the final 16 (the two addPrim merge clusters):
 * the wrong-register rows were LOCAL-ALLOC QTY DENSITY ORDER, not a scheduling
 * tie. gcc-2.7.2 local-alloc allocates qtys by qty_compare density
 * (floor_log2(refs)*refs*size/life) and the FIRST qty through the scan grabs the
 * scan-order register the next one wanted. Each addPrim RMW merge is spelled:
 *
 *     w = *(u32 *)prim;            // raw tag word named EARLY (its own stmt)
 *     ...interleaving stmts...     // nextpri update / otq addr / E1 store
 *     w &= 0xFF000000;             // in-place mask, SPLIT from the ior
 *     *(u32 *)prim = w | (*otp & 0xFFFFFF);   // ior op1 = prim side
 *
 * The early def + split &= lengthens w's qty life, DROPPING its density below
 * the competing address-chain qty, so the chain allocates first (taking $v1)
 * and w's tied {lw,and,ior,sw} chain lands on the target's register; the ior
 * operand order (op1 = prim word) then emits or $rP,$rP,$rV with dest tied to
 * op1. Statement order around pk2[3]=1 is FORCED by a real dependence: the sb
 * writes byte 3 of the same word the lw reads, so their source order IS their
 * final order — the target's source read *pk2 AFTER pk2[3]=1 (merge-3) and
 * *otp BEFORE D_800A5E60=pk2+8 (merge-2). Mask-hoist order (t2 before t3) pins
 * the *value*-side and to first LUID use, which is why merge-1 splits BOTH
 * sides (wv first, then w1 &= mask).
 *
 * Verified against tools/reference/gcc-2.7.2 sched.c (no birthing boost for
 * block-dying pseudos, so sched1 load order is priority-fixed; final order is
 * sched2 under the colors) and local-alloc.c qty_compare. Reloc audit: 1:1 with
 * the target .s; D_80193440+2/+4 addends == D_80193442/D_80193444 (contiguous).
 */
#include "common.h"

typedef struct { s16 vx, vy, vz, pad; } SV_8017EC4C;
typedef struct { s16 m[3][3]; s32 t[3]; } MT_8017EC4C;

extern void func_8012EC04(s32, s32, s32 *);
extern void func_8012F14C(s32, s32, s32);
extern s32  func_80135888(s32, s32, s32, s32);
extern void func_8012F568(s32, s32, s32, s32, s32, s32);
extern s32  func_80133784(s32, void *, s32);
extern void func_8012F038(int, short *, short *);
extern void func_800D20C0(void *, void *, s32);
extern void func_80017E68(void *, void *);
extern void ApplyMatrixSV(void *, void *, void *);
extern void func_800D23D0(void *);
extern void RotMatrixYXZ(void *, void *);
extern void ApplyTransposeMatrixLV(void *, void *, void *);
extern s32  ratan2(s32, s32);

extern s16 D_800B9A02;
extern u16 D_800B99DA;
extern u8  D_800A6610[];
extern u8  D_800AF630[];
extern u8 *D_800A5E60;
extern s32 D_801E1158;
extern s32 *D_80126B78;
extern s32 *D_80126B90;
extern u8  D_801152A8[];
extern s32 D_801269A4;
extern s32 D_801269A8;
extern s32 D_801269AC;
extern u16 D_80193440[];


extern u8  D_801934B0[];
extern s32 D_801934F0[];
extern u16 D_80193538[];
extern s32 D_80193550[];
extern s32 D_80193554[];
extern s32 D_80193558[];
extern s32 D_8019355C[];












void func_8017EC4C(s32 param_1)
{
    SV_8017EC4C v[4];
    SV_8017EC4C tmp;
    struct { s32 vx, vy, vz, pad; } vec;
    MT_8017EC4C cmat;
    MT_8017EC4C M;
    struct { s32 flag, flag2, otz, x0, x1, x2, x3, x4; } g;

    u8 *dbase;
    u8 *pkt;
    u8 *pk2;
    u16 *tp;
    u32 *otp;
    u32 *otq;
    u32 ot;
    s32 hit;
    s32 d, n, t, rem, i, j, k;
    s32 aa, bb, cc, rr;
    u32 w2;
    u32 w1, wv;
    u32 w3;

    hit = 0;
    ot = (u32)&D_800A6610[(*(u16 *)&D_800B9A02) << 14];
    dbase = D_800AF630;
    func_8012EC04(param_1, D_801E1158, (s32 *)&cmat);
    func_8012F14C((s32)&cmat, (s32)&D_80193440[0], *(s32 *)(param_1 + 0xD4) + 8);

    v[0].vx = D_80193440[0];
    v[0].vy = D_80193440[1];
    v[0].vz = D_80193440[2] - *(u16 *)(param_1 + 0x100);
    v[1].vx = D_80193440[0];
    v[1].vy = D_80193440[1];
    v[1].vz = D_80193440[2] - *(u16 *)(param_1 + 0x102);
    func_8012F14C((s32)&cmat, (s32)&v[0], (s32)&v[0]);
    func_8012F14C((s32)&cmat, (s32)&v[1], (s32)&v[1]);
    tmp = v[1];
    if (func_80135888((s32)D_80126B78, (s32)D_80126B90, (s32)&v[0], (s32)&v[1]) != 0) {
        func_8012F568(1, 0x4018, *(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12), 0x96,
                      (s32)&v[1], (s32)D_801152A8);
    }

    d = *(s16 *)(param_1 + 0x102) - *(s16 *)(param_1 + 0x100);
    t = d / 128;
    n = t;
    if (t < 0) {
        t = -t;
    }
    rem = d - n * 128;
    __asm__ ("" : "=r" (n) : "0" (n));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    if ((d - n * 128) < 0) {
        rem = -rem;
    }

    i = 0;
    if (t > 0) {
        do {
            v[1].vx = D_80193440[0];
            v[1].vy = D_80193440[1];
            v[1].vz = D_80193440[2] - *(u16 *)(param_1 + 0x100) - ((i + 1) << 7);
            func_8012F14C((s32)&cmat, (s32)&v[1], (s32)&v[1]);
            hit = func_80133784(1, (void *)&v[0], (s32)&v[1]);
            if (hit != 0) {
                break;
            }
            v[0].vx = v[1].vx;
            v[0].vy = v[1].vy;
            v[0].vz = v[1].vz;
            i = i + 1;
        } while (i < t);
    }

    if (hit == 0) {
        v[1].vx = D_80193440[0];
        v[1].vy = D_80193440[1];
        v[1].vz = D_80193440[2] - *(u16 *)(param_1 + 0x100) - (t << 7) - rem;
        func_8012F14C((s32)&cmat, (s32)&v[1], (s32)&v[1]);
        hit = func_80133784(1, (void *)&v[0], (s32)&v[1]);
    }

    if (hit != 0) {
        *(SV_8017EC4C *)(*(s32 *)(param_1 + 0xD8) + 8) = v[1];
        *(s32 *)(*(s32 *)(param_1 + 0xD8) + 4) &= 0x7FFFFFFF;
        *(s32 *)D_801934B0 = D_801934F0[D_800B99DA & 1];
        func_8012F038((s32)&cmat, (short *)&v[1], (short *)&v[1]);
        cc = *(s16 *)(param_1 + 0x100);
        aa = (s32)*(s16 *)&D_80193440[2] - cc;
        bb = aa - v[1].vz;
        if (bb < 0) {
            rr = cc + (v[1].vz - aa);
        } else {
            rr = cc + bb;
        }
        *(s16 *)(param_1 + 0x102) = rr;
        *(s32 *)(param_1 + 0xE4) |= 4;
    } else {
        *(s32 *)(*(s32 *)(param_1 + 0xD8) + 4) |= 0x80000000;
        *(s32 *)(param_1 + 0xE4) &= ~4;
    }

    v[0].vx = 0;
    v[0].vy = D_80193440[1];
    v[0].vz = D_80193440[2];
    func_8012F14C((s32)&cmat, (s32)&v[0], (s32)&v[0]);
    func_800D20C0((void *)&v[0], (void *)&v[1], 8);
    func_80017E68((void *)&v[0], (void *)&M);
    v[1].vx = 0;
    v[1].vy = 0;
    k = *(u16 *)(param_1 + 0x100);
    v[1].vz = *(u16 *)(param_1 + 0x102) - k;
    ApplyMatrixSV((void *)&cmat, (void *)&v[1], (void *)&v[1]);
    func_800D23D0((void *)&v[1]);
    RotMatrixYXZ((void *)&v[1], (void *)&M);
    vec.vx = D_801269A4 - v[0].vx;
    vec.vy = D_801269A8 - v[0].vy;
    vec.vz = D_801269AC - v[0].vz;
    ApplyTransposeMatrixLV((void *)&M, (void *)&vec, (void *)&vec);
    v[1].vz = -ratan2(vec.vx, vec.vy);
    RotMatrixYXZ((void *)&v[1], (void *)&M);

    gte_SetRotMatrix(dbase + 0x18);
    gte_mulcol(&M.m[0][0]);
    gte_mulcol(&M.m[0][1]);
    gte_mulcol(&M.m[0][2]);
    gte_SetTransMatrix(dbase + 0x18);
    gte_multrans(&M.t[0]);

    gte_SetRotMatrix(&M);
    gte_SetTransMatrix(&M);

    tp = D_80193538;
    for (i = 0; i < 3; i++) {
        pkt = D_800A5E60;
        k = (i * 2 + (*(u16 *)(dbase + 0xA3AA) & 1)) * 4;
        D_800A5E60 = pkt + 0x24;
        *(u32 *)(pkt + 4) = D_80193550[k];
        *(u32 *)(pkt + 0xC) = D_80193554[k];
        *(u32 *)(pkt + 0x14) = D_80193558[k];
        *(u32 *)(pkt + 0x1C) = D_8019355C[k];
        pkt[3] = 8;
        pkt[7] = 0x38;

        v[0].vx = D_80193440[0] + *tp++;
        v[0].vy = 0;
        v[0].vz = -*(u16 *)(param_1 + 0x100);
        v[1].vx = D_80193440[0] + *tp++;
        v[1].vy = 0;
        v[1].vz = -*(u16 *)(param_1 + 0x102);
        v[2].vx = D_80193440[0] - *tp++;
        v[2].vy = 0;
        v[2].vz = -*(u16 *)(param_1 + 0x100);
        v[3].vx = D_80193440[0] - *tp++;
        v[3].vy = 0;
        v[3].vz = -*(u16 *)(param_1 + 0x102);

        gte_ldv3(&v[0], &v[1], &v[2]);
        gte_rtpt();
        gte_stflg(&g.flag);
        gte_stsxy3(pkt + 8, pkt + 0x10, pkt + 0x18);
        gte_ldv0(&v[3]);
        gte_rtps();
        gte_stflg(&g.flag2);
        g.flag |= g.flag2;
        gte_stsxy(pkt + 0x20);
        gte_avsz4();
        gte_stotz(&g.otz);

        if ((g.flag & ~0x1000) == 0) {
            g.otz = g.otz + 1;
            if (g.otz < 0x1000) {
                pkt[7] |= 2;
                w1 = *(u32 *)pkt;
                otp = (u32 *)((g.otz << 2) + ot);
                pk2 = D_800A5E60;
                wv = *otp & 0xFFFFFF;
                w1 &= 0xFF000000;
                *(u32 *)pkt = w1 | wv;
                w3 = *otp;
                D_800A5E60 = pk2 + 8;
                *otp = (w3 & 0xFF000000) | ((u32)pkt & 0xFFFFFF);
                pk2[3] = 1;
                w2 = *(u32 *)pk2;
                otq = (u32 *)((g.otz << 2) + ot);
                *(u32 *)(pk2 + 4) = 0xE100002A;
                w2 &= 0xFF000000;
                *(u32 *)pk2 = w2 | (*otq & 0xFFFFFF);
                *otq = (*otq & 0xFF000000) | ((u32)pk2 & 0xFFFFFF);
            }
        }
    }
}


extern u16 D_800B99DA;
extern s32 D_801E1158;
extern s32 D_801935B0;
extern s32 D_801935B8;
extern void func_8012EC04(s32 a0, s32 a1, s32 *a2);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);

void func_8017F4FC(void* a0)
{
    s16 m[16];
    s16 vec[4];
    s32 obj;

    if (*(s32 *)(a0 + 0xE4) & 1) {
        if (D_800B99DA % 5 == 0) {
            obj = func_80132EF4(a0, 0x22);
            if (obj != 0) {
                func_8012EC04(a0, D_801E1158, (s32 *)m);
                func_8012F14C((s32)m, (s32)&D_801935B0, (s32)vec);
                *(u16 *)(obj + 0x34) = 0x2001;
                *(u16 *)(obj + 0x6) = vec[0];
                *(u16 *)(obj + 0xA) = vec[1];
                *(u16 *)(obj + 0xE) = vec[2];
                *(s32 *)(obj + 0x14) = -0x60000 - ((rand() % 3) << 16);
            }
        }
    }
    if (*(s32 *)(a0 + 0xE4) & 2) {
        if (D_800B99DA % 5 == 0) {
            obj = func_80132EF4(a0, 0x22);
            if (obj != 0) {
                func_8012EC04(a0, D_801E1158, (s32 *)m);
                func_8012F14C((s32)m, (s32)&D_801935B0, (s32)vec);
                *(u16 *)(obj + 0x34) = 0x2001;
                *(u16 *)(obj + 0x6) = vec[0];
                *(u16 *)(obj + 0xA) = vec[1];
                *(u16 *)(obj + 0xE) = vec[2];
                *(s32 *)(obj + 0x14) = -0x60000 - ((rand() % 3) << 16);
            }
        }
        if (D_800B99DA % 6 == 0) {
            obj = func_80132EF4(a0, 0x22);
            if (obj != 0) {
                func_8012EC04(a0, D_801E1158, (s32 *)m);
                func_8012F14C((s32)m, (s32)&D_801935B8, (s32)vec);
                *(u16 *)(obj + 0x34) = 0x2001;
                *(u16 *)(obj + 0x6) = vec[0];
                *(u16 *)(obj + 0xA) = vec[1];
                *(u16 *)(obj + 0xE) = vec[2];
                *(s32 *)(obj + 0x14) = -0x60000 - ((rand() % 3) << 16);
            }
        }
    }
}



extern void (*D_801935C8[])(void);

void func_8017F7B8(void *a0) {
    D_801935C8[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8017F7F4(s32 param_1) {
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(s32 a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8012B2CC(s32 a0);
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_8012F14C(s32 a0, s32 a1, s32 a2);
    extern s32 func_8012B744(void *a0, void *a1);
    extern void func_8012B178(s32 a0, s32 a1);
    extern void func_80049CAC(s32 a0, s32 a1);
    extern s32 func_80132EF4(s32 a0, s32 a1);
    extern s32 func_80143994(s32 a0, s32 a1);
    extern u8 D_801AA398[];
    extern void (*D_801935C0)(void *);
    s32 buf[8];
    u16 vec[4];
    s16 t;
    u16 q;
    s32 rr;
    s32 sh;
    s32 adj;
    s32 obj;
    s32 e;

    *(s32 *)(param_1 + 0x20) = ((s32 (*)(void))func_8012C1B8)();
    if (*(s32 *)(param_1 + 0x20) == 0) {
        func_8012CAE4(param_1);
        return;
    }
    func_8001C214(*(s32 *)(param_1 + 0x20), (s32)D_801AA398);
    t = *(s16 *)(param_1 + 0x70);
    if ((t & 0x8000) == 0) {
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x12) +
            ((t & 0xF) << 10);
        func_8012B2CC(param_1);
        func_8012F214(param_1, (s32)&D_801935C0, param_1 + 0xF4);
    } else {
        vec[0] = *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x10);
        q = *(u16 *)(param_1 + 0x70);
        rr = *(s32 *)(param_1 + 0x64);
        sh = (q & 0xF) << 10;
        adj = *(s16 *)(*(s32 *)(rr + 0x20) + 0x12) +
              ((q & 0x800) ? 0x200 : -0x200);
        vec[1] = adj + sh;
        vec[2] = *(u16 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x14);
        buf[5] = *(s32 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x48);
        buf[6] = *(s32 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x4C);
        buf[7] = *(s32 *)(*(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x50);
        func_80049CAC((s32)vec, (s32)buf);
        func_8012F14C((s32)buf, (s32)&D_801935C0, param_1 + 0xF4);
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
            func_8012B744(param_1 + 4, param_1 + 0xF4);
        func_8012B2CC(param_1);
    }
    func_8012B178(param_1, -0x3D800);
    *(s32 *)(param_1 + 0x14) = -0x200000;
    *(s32 *)(param_1 + 0x48) = 0x12000;
    obj = func_80132EF4(param_1, 0x22);
    if (obj != 0) {
        e = *(s32 *)(obj + 0x20);
        *(u16 *)(obj + 0x34) = 0x2001;
        *(u16 *)(e + 0x2C) = 0xC006;
        *(s32 *)(obj + 0x10) = *(s32 *)(param_1 + 0x10);
        *(s32 *)(obj + 0x18) = *(s32 *)(param_1 + 0x18);
    }
    *(s32 *)(param_1 + 0xCC) = func_80143994(param_1, 0x800);
    *(u16 *)(param_1 + 0x34) = 0;
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}


extern void func_8012C218(s32 a0);
extern s32 func_8012CBF4(s32 a0);
extern void func_8017FB84(s32 a0);
extern void func_8012E8A8(u8 *a0);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8017FA1C(s32 arg0) {
    register s32 s0 __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    s0 = arg0;

    if (*(s16 *)((u8 *)s0 + 0xA) >= 0x10) {
        func_8012C218(s0);
        return;
    }
    __asm__ __volatile__("" ::: "a0");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
    if (func_8012CBF4(s0) != 0) {
        func_8017FB84(s0);
        {
            s32 t = *(u16 *)((u8 *)s0 + 0x2);
            *(s32 *)((u8 *)s0 + 0x1C) = 0xA;
            t += 1;
            *(u16 *)((u8 *)s0 + 0x2) = t;
            func_8012E8A8((u8 *)s0);
        }
        return;
    }
    if (*(u16 *)((u8 *)s0 + 0x34) == 0 && *(s32 *)((u8 *)s0 + 0x14) >= 0) {
        s32 t;
        register s32 u __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
        t = 0x800;
        u = *(s32 *)((u8 *)s0 + 0x20);
        *(s16 *)((u8 *)u + 0x10) = t;
        t = *(u16 *)((u8 *)s0 + 0x34) + 1;
        *(u16 *)((u8 *)s0 + 0x34) = t;
        func_8002D4C8(0x954, 0);
    }
    {
        s32 a1 = *(s16 *)((u8 *)s0 + 0xA);
        if (a1 < -0x602) {
            s32 v0 = -0x900;
            s32 v1 = *(s32 *)((u8 *)s0 + 0xCC);
            s32 a0 = v0 - a1;
            s32 a2 = *(s32 *)((u8 *)v1 + 0xCC);
            if (a0 >= 0) {
                v0 = a0 << 2;
                v0 += a0;
            } else {
                v1 = a1 + 0x900;
                v0 = v1 << 2;
                v0 += v1;
            }
            v0 <<= 1;
            *(s16 *)((u8 *)a2 + 0x1A) = v0;
            *(s16 *)((u8 *)a2 + 0x18) = v0;
        }
    }
}


extern s32 func_8012D624(void *a0, s32 a1, s32 a2);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(s32 a0);
extern u16 D_80126B96;

void func_8017FB28(s32 param_1) {
    if (func_8012D624((void *)param_1, 0x40, 0x78) == 1) {
        D_80126B96 = 0x4001;
    }
    if (func_8012BEE8(param_1) != 0) {
        func_8012C218(param_1);
    }
}


void func_8017FB84(s32 self) {
    s32 obj;
    char *p;

    obj = func_80132EF4(self, 0x23);
    if (obj != 0) {
        u16 v = *(u16 *)(obj + 0xA);
        *(u16 *)(obj + 0x34) = 0x6001;
        *(u16 *)(obj + 0xA) = v - 0x10;
        p = *(char **)(self + 0x64);
        if (*(s16 *)(p + 0x108) == 0) {
            func_8002D4C8(0x95D, 0);
            *(s16 *)(*(char **)(self + 0x64) + 0x108) = 1;
        }
    }
}



extern void (*D_801935E0[])(void);

void func_8017FBF8(void *a0) {
    D_801935E0[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void (*D_801935D4[])(void);

void func_8017FC34(void *a0) {
    *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x20) = (s32) D_801935D4;
    *(u8 *)(*(s32 *)((s32)a0 + 0x20) + 0x27) = 0x3D;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x28) = 0x2D1;
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2A) = 0x160;
    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x2C) = 0xC020U;
    *(s16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
    *(s32 *)((s32)a0 + 0x1C) = 7;
}



extern void func_801292C8(u8 *a0);
    s32 func_8017FC8C(s32 arg0) {
        *(s32 *)(arg0 + 0x1c) -= 1;
        if (*(s32 *)(arg0 + 0x1c) == 0) {
            ((void (*)(void))func_801292C8)();
        }
    }



extern void (*D_80193608[])(void);

void func_8017FCC0(void *a0) {
    D_80193608[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern s32 rand(void);
extern void func_8012B14C(s32 a0, s32 a1);
extern u16 D_801E1130[];
extern u16 D_80193610[];
extern u16 D_8019364C[];
extern u16 D_80193658[];
extern u16 D_8019364E;
extern u16 D_80193650;
extern u16 D_8019365A;
extern u16 D_8019365C;

void func_8017FCFC(void *a0) {
    register s32 v0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 v1;
    s32 key;
    register s32 tbl __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)
    s32 st[11];
    s32 *row;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((s32)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((s32)a0);
        return;
    }
    func_8001C214(v0, (s32)D_801E1130 + (*(s16 *)((s32)a0 + 0x70) << 3));
    key = *(s16 *)((s32)a0 + 0x70);
    row = (s32 *)(D_80193610 + key * 6);
    if (key != 4) {
        tbl = (s32)D_8019364C;
        *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)row + 0) + *(u16 *)((s32)tbl + 0) + *(u16 *)((s32)a0 + 0x6);
        *(u16 *)((s32)a0 + 0xA) = *(u16 *)((s32)row + 2) + D_8019364E + *(u16 *)((s32)a0 + 0xA);
        *(u16 *)((s32)a0 + 0xE) = *(u16 *)((s32)row + 4) + D_80193650 + *(u16 *)((s32)a0 + 0xE);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x10) = *(u16 *)((s32)row + 6);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
            *(u16 *)((s32)row + 8) + *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x14) = *(u16 *)((s32)row + 0xA);
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x20) = tbl;
        func_8012B2CC((s32)a0);
        st[8] = 0;
        v0 = rand();
        st[10] = 0xFFF80000;
        st[9] = 0xFFF00000 - (v0 % 9 << 16);
        func_8012B14C((s32)a0, (s32)&st[8]);
        v0 = rand();
        v1 = v0;
        if (v1 < 0) {
            v0 = v1 + 255;
        }
        v0 = v1 - ((v0 >> 8) << 8) + 0x100;
    } else {
        tbl = (s32)D_80193658;
        *(u16 *)((s32)a0 + 0x6) = *(u16 *)((s32)row + 0) + *(u16 *)((s32)tbl + 0) + *(u16 *)((s32)a0 + 0x6);
        *(u16 *)((s32)a0 + 0xA) = *(u16 *)((s32)row + 2) + D_8019365A + *(u16 *)((s32)a0 + 0xA);
        *(u16 *)((s32)a0 + 0xE) = *(u16 *)((s32)row + 4) + D_8019365C + *(u16 *)((s32)a0 + 0xE);
        *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(*(s32 *)((s32)a0 + 0x64) + 0x20) + 0x12);
        *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 0x20) = tbl;
        func_8012B2CC((s32)a0);
        st[8] = 0;
        v0 = rand();
        st[10] = 0x80000;
        st[9] = 0xFFF00000 - (v0 % 9 << 16);
        func_8012B14C((s32)a0, (s32)&st[8]);
        v0 = rand();
        v1 = v0;
        if (v1 < 0) {
            v0 = v1 + 255;
        }
        v0 = -(v1 - ((v0 >> 8) << 8) + 0x100);
    }
    *(s16 *)((s32)a0 + 0xFE) = v0;
    *(s32 *)((s32)a0 + 0x48) = 0xC000;
    *(s32 *)((s32)a0 + 0x1C) = 0x60;
    *(u16 *)((s32)a0 + 0x2) = *(u16 *)((s32)a0 + 0x2) + 1;
}


#include "common.h"

/* TU-canon forms (matches src/ov_SC06_024/ov_SC06_024_jr_8017BEBC.c file-scope decls,
 * lines 643 / 2523 / 3514-3515). */
extern s32 func_80134510(s32 arg);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(s32 a0);

/* func_8012CC64 is NOT declared anywhere in this TU. Cross-TU canon (many overlays,
 * e.g. src/ov_SC06_008/ov_SC06_008_jr_8012ACE0.c:1603 + call site :1694) is `void`
 * return with the actual s32 result recovered via a function-pointer cast at the
 * call site. */
extern void func_8012CC64(s32 a0, s32 a1);

/* Only address-of used ($a1 for func_8012CC64) -- raw byte array is enough. */
extern u8 D_80193664[];

void func_8017FFCC(s32 a0) {
    s32 v0;
    struct {
        u16 f0, f1, f2;
    } sp10;

    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x10) += *(u16 *)(a0 + 0xFE);

    if (*(u16 *)(a0 + 0x34) == 0 && *(s16 *)(a0 + 0x70) != 4 &&
        *(s32 *)(a0 + 0x1C) < 0x4C) {
        sp10.f0 = *(u16 *)(a0 + 0x6);
        sp10.f1 = *(u16 *)(a0 + 0xA);
        sp10.f2 = *(u16 *)(a0 + 0xE);
        if (func_80134510((s32)&sp10) != 0) {
            if (*(u16 *)(a0 + 0x70) & 1) {
                func_8012C658(0x33, 3, a0);
            } else {
                func_8012C658(0x32, 2, a0);
            }
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
        }
    }

    if (*(s16 *)(a0 + 0xA) >= 0x10 || func_8012BEE8(a0) != 0) {
        func_8012C218(a0);
        return;
    }

    v0 = ((s32 (*)(s32, s32))func_8012CC64)(a0, (s32)D_80193664);
    if (v0 & 0x2000) {
        *(s32 *)(a0 + 0x1C) = 0x20;
        *(u16 *)(a0 + 0x2) = *(u16 *)(a0 + 0x2) + 1;
    }
}




extern void (*D_8019366C[])(void);

void func_80180104(void *a0) {
    D_8019366C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80180140(s32 param_1) {
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(s32 a0);
    extern void func_8001C214(s32 a0, s32 a1);
    extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
    extern u8 D_801935E8[];

    s32 v0;
    u16 a0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(param_1);
        return;
    }

    func_8001C214(v0, 0);
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0x7FFF, 0x7FFF);

    v0 = 0x800;
    a0 = *(u16 *)(param_1 + 0x2) + 1;
    *(u16 *)(param_1 + 0x5C) = v0;
    v0 = *(s16 *)(param_1 + 0x70);
    *(s32 *)(param_1 + 0x58) = ((v0 << 4) + (s32)&D_801935E8) | 0x50000000;
    *(u16 *)(param_1 + 0x2) = a0;
}


void func_801801D0(void) {
}

extern void func_8012E8C4(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012C218(s32 a0);
void func_801801D8(s32 a0) {
    func_8012E8C4(a0);
    if (func_8012BEE8(a0)) {
        func_8012C218(a0);
    }
}



s32 func_80180218(void) {
    return 127;
}


extern u8 D_801202A0[];

void func_80180220(int param_1)
{
    u8 *pos;
    s16 *rec;
    s32 i;
    s32 dx;
    s32 dy;

    pos = D_801202A0;
    for (i = 0; i < 0x60; i++) {
        rec = (s16 *)(pos + 0xE);
        if (*(u16 *)pos == 0x263) {
            dx = rec[-4] - *(s16 *)(param_1 + 6);
            dy = rec[0] - *(s16 *)(param_1 + 0xE);
            if ((u32)(dx + 0x7F) < 0xFF && (u32)(dy + 0x7F) < 0xFF) {
                if (rec[0x77] == 0) {
                    rec[-2] = *(u16 *)(param_1 + 0xA) - 0x20;
                    *(s32 *)&rec[3] = 0;
                    *(s32 *)&rec[-5] += *(s32 *)(param_1 + 4) - *(s32 *)(param_1 + 0x38);
                    *(s32 *)&rec[-1] += *(s32 *)(param_1 + 0xC) - *(s32 *)(param_1 + 0x40);
                    dx = rec[-4] - *(s16 *)(param_1 + 6);
                    dy = rec[0] - *(s16 *)(param_1 + 0xE);
                }
                if (dx > 0x40) {
                    rec[-4] = *(u16 *)(param_1 + 6) + 0x40;
                }
                if (dx < -0x40) {
                    rec[-4] = *(u16 *)(param_1 + 6) - 0x40;
                }
                if (dy > 0x40) {
                    rec[0] = *(u16 *)(param_1 + 0xE) + 0x40;
                }
                if (dy < -0x40) {
                    rec[0] = *(u16 *)(param_1 + 0xE) - 0x40;
                }
            }
        }
        pos += 0x10C;
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 D_80126B58;
extern u16 D_80126B5E;
extern u16 D_80126B66;
/* §37 aliases: the TU canon for these two is `u16`, but this function reads and
 * writes them SIGNED (lh / addiu $v0,$zero,-K), which a u16 lvalue cannot spell
 * (a u16 store constant materialises as `ori`, not `addiu`). */
extern s16 aD80126B5E __asm__("D_80126B5E");
extern s16 aD80126B66 __asm__("D_80126B66");

void func_8018036C(s32 param_1)
{
    s16 var;
    s16 *p;

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        *(u16 *)(param_1 + 6) -= 4;
        var = *(u16 *)(param_1 + 0xA) - 2;
        *(u16 *)(param_1 + 0xA) = var;
        if (var < -0x4E1) {
            *(u16 *)(param_1 + 0x34) = 1;
        }
        return;
    case 1:
        if (aD80126B5E < -0x29E) {
            if ((u16)(D_80126B66 + 0x114) >= 0xE9) {
                aD80126B5E = -0x29E;
            } else {
                *(u16 *)(param_1 + 0x34) = 2;
            }
        }
        return;
    case 2:
        p = (s16 *)&D_80126B58;
        if (aD80126B5E < -0x29E) {
            if (aD80126B66 < -0x114) {
                aD80126B66 = -0x114;
            }
            if (aD80126B66 > -0x2C) {
                aD80126B66 = -0x2C;
            }
            if (aD80126B5E < -0x38B) {
                aD80126B5E = -0x38B;
            }
        } else {
            *(u16 *)(param_1 + 0x34) = 1;
        }
        if (p[3] < -0x2DE) {
            *(u16 *)(param_1 + 0x34) = 3;
        }
        if (*(u8 *)(param_1 + 0x74) != 0) {
            *(u16 *)(param_1 + 2) = 3;
            *(u16 *)(param_1 + 0x34) = 0;
            func_8002D4C8(0xB26, 0);
        }
        return;
    case 3:
        if (aD80126B5E > -0x2DE) {
            aD80126B5E = -0x2DE;
        }
        if (aD80126B66 < -0x114) {
            aD80126B66 = -0x114;
        }
        if (aD80126B66 > -0x2C) {
            aD80126B66 = -0x2C;
        }
        if (aD80126B5E < -0x38B) {
            aD80126B5E = -0x38B;
        }
        if (*(u8 *)(param_1 + 0x74) != 0) {
            *(u16 *)(param_1 + 2) = 3;
            *(u16 *)(param_1 + 0x34) = 0;
            func_8002D4C8(0xB26, 0);
        }
        return;
    }
}


extern u16 D_80126B5E;
extern u16 D_80126B66;
/* §37 aliases: the TU canon for these two is `u16` (see the identical pair at
 * ov_SC06_024_jr_8017BEBC.c:4926-4932, declared for the sibling func_8018036C),
 * but this function reads them SIGNED (`lh`) and stores negative results, which a
 * u16 lvalue cannot spell. */
extern s16 aD80126B5E __asm__("D_80126B5E");
extern s16 aD80126B66 __asm__("D_80126B66");

void func_80180594(s32 param_1)
{
    s16 var;
    s32 d;
    s16 *px;   /* &D_80126B5E held in a reg (lui+addiu %lo) — reassigned per case */

    switch (*(u16 *)(param_1 + 0x34)) {
    case 0:
        *(u16 *)(param_1 + 6) -= 4;
        var = *(u16 *)(param_1 + 0xA) - 2;
        *(u16 *)(param_1 + 0xA) = var;
        if (var < -0x96E) {
            *(u16 *)(param_1 + 0x34) = 1;
        }
        px = &aD80126B5E;
        d = *px - *(s16 *)(param_1 + 6);
        if (d < -0x78) {
            *px = *(s16 *)(param_1 + 6) - 0x78;
        }
        if (d > 0x78) {
            *px = *(u16 *)(param_1 + 6) + 0x78;
        }
        d = aD80126B66 - *(s16 *)(param_1 + 0xE);
        if (d < -0x78) {
            aD80126B66 = *(s16 *)(param_1 + 0xE) - 0x78;
        }
        if (d > 0x78) {
            aD80126B66 = *(u16 *)(param_1 + 0xE) + 0x78;
        }
        return;
    case 1:
        px = &aD80126B5E;
        d = *px - *(s16 *)(param_1 + 6);
        if (d < -0x90) {
            *(u16 *)(param_1 + 0x34) = 2;
        }
        if (d > 0x78) {
            *px = *(u16 *)(param_1 + 6) + 0x78;
        }
        d = aD80126B66 - *(s16 *)(param_1 + 0xE);
        if (d < -0x78) {
            aD80126B66 = *(s16 *)(param_1 + 0xE) - 0x78;
        }
        if (d > 0x78) {
            aD80126B66 = *(u16 *)(param_1 + 0xE) + 0x78;
        }
        return;
    case 2:
        px = &aD80126B5E;
        d = *px - *(s16 *)(param_1 + 6);
        if (d > -0x90) {
            *px = *(s16 *)(param_1 + 6) - 0x90;
        }
        return;
    }
}


extern s32 func_8012C588(s32 a0, s32 a1);

void func_80180724(s32 arg0) {
    s32 s1 = arg0;
    s32 s2;
    s32 s0;
    s32 v0;
    s32 v1;

    s2 = *(u16 *)(s1 + 0x34);
    switch (s2) {
    case 0:
        v0 = func_8012BE54(s1 + 0);
        if (v0 <= 0x64000) {
            *(u16 *)(s1 + 0x34) = 1;
        }
        break;
    case 1:
        s0 = func_8012C588(0x263, s1);
        if (s0 != 0) {
            *(s32 *)(s1 + 0xCC) = s0;
            *(u16 *)(s1 + 0xFC) = *(u16 *)(s0 + 0x36);
            *(u16 *)(s0 + 0xFC) = 0x60;
            *(u16 *)(s1 + 0x34) = 2;
            *(s32 *)(s0 + 0xDC) = s2;
        }
        break;
    case 2:
        s0 = *(s32 *)(s1 + 0xCC);
        if (*(s16 *)(s1 + 0xFC) == *(s16 *)(s0 + 0x36)) {
            v0 = *(u16 *)(s1 + 0xA);
            v1 = 0x19;
            *(u16 *)(s0 + 0xFC) = v1;
            *(u16 *)(s0 + 0xA) = v0 - 0x20;
        }
        v1 = *(s16 *)(s1 + 6);
        v0 = *(s16 *)(*(s32 *)(s1 + 0x64) + 6);
        if ((u32)(v0 - v1 - 1) < 0x7F) {
            v0 = -0x14;
            *(u16 *)(s0 + 0x16) = v0;
            v0 = -7;
            *(u16 *)(s0 + 0x1A) = v0;
            *(u16 *)(s1 + 0x34) = 3;
        }
        break;
    case 3:
        s0 = *(s32 *)(s1 + 0xCC);
        if (*(s16 *)(s1 + 0xFC) == *(s16 *)(s0 + 0x36)) {
            func_8012CBCC(s0);
            if (*(s16 *)(s0 + 0xFC) == 0) {
                *(u16 *)(s1 + 0x34) = 4;
            }
        }
        break;
    }
}


extern void (*D_801936D0[])(void);
extern void func_8012DFD4(void *a0);
extern void func_80180220(int param_1);

void func_80180894(void *a0)
{
    D_801936D0[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        func_8012DFD4(a0);
        if (*(s16 *)((s32)a0 + 0x70) == 0) {
            func_80180220((s32)a0);
        }
    }
}



extern void func_8012DFD4(void *a0);

void func_8018090C(void *a0) {

    extern void (*D_80193764[])(void);
    D_80193764[*(u16 *)((s32)a0 + 0x2)]();
    if (*(u16 *)a0 != 0) {
        func_8012DFD4(a0);
    }
}



extern void (*D_801937B4[])(void);

void func_8018096C(void *a0) {
    D_801937B4[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012C354(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B2CC(s32 a0);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern u8 D_80193688[];
extern u8 D_801936C8[];

void func_801809A8(s32 a0)
{
    s32 s0 = a0;
    s32 v1;

    if (func_8012C354(a0, &D_80193688) != 0) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(s32 *)(s0 + 0xB4) = -1;
        *(s16 *)(s0 + 0xAE) = -1;
        *(u8 *)(s0 + 0x75) = 8;
        func_8012A828(s0, &D_801936C8);
        __asm__("" : "=r"(s0) : "0"(s0));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
        if (*(s16 *)(s0 + 0x70) != 0) {
            *(s16 *)(s0 + 2) = 4;
        } else {
            *(s16 *)(s0 + 2) = 1;
            *(u32 *)(*(s32 *)(s0 + 0x20) + 4) |= 0x80000000;
            func_8012B2CC(s0);
            v1 = func_8012C658(0x346, 1, s0);
            if (v1 != 0) {
                *(s16 *)(v1 + 6) = -0x660;
                *(s16 *)(v1 + 0xA) = -0x682;
                *(s16 *)(v1 + 0xE) = 0x80;
            }
            v1 = func_8012C658(0x346, 1, s0);
            if (v1 != 0) {
                *(s16 *)(v1 + 6) = -0xA60;
                *(s16 *)(v1 + 0xA) = -0x882;
                *(s16 *)(v1 + 0xE) = 0x80;
            }
        }
    }
}


extern u8 D_801202A0[];

void func_80180AA8(void *a0) {
    s32 i;
    u8 *p;
    u16 t;

    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        p = D_801202A0;
        for (i = 0; i < 0x60; i++) {
            if (*(u16 *)p == 0x390) {
                *(void **)((s32)a0 + 0x6C) = p;
                t = *(u16 *)(p + 0x36);
                *(u16 *)((s32)a0 + 0x34) = 1;
                *(u16 *)((s32)a0 + 0xFE) = t;
            }
            p += 0x10C;
        }
        break;
    case 1: {
        u8 *p2 = *(u8 **)((s32)a0 + 0x6C);
        if (*(s16 *)((s32)a0 + 0xFE) != *(s16 *)(p2 + 0x36)) {
            *(s32 *)(*(s32 *)((s32)a0 + 0x20) + 4) &= 0x7FFFFFFF;
            *(u16 *)((s32)a0 + 2) = 2;
            *(u16 *)((s32)a0 + 0x34) = 0;
        }
        break;
    }
    }
}


#include "common.h"

extern s32 func_80047948(s32 a0);
extern s32 D_80126B60;

s32 func_80180B5C(s32 arg0)
{
    u16 v1 = *(u16 *)((s32)arg0 + 0x34);

    switch (v1) {
    case 0: {
        u16 t = *(u16 *)((s32)arg0 + 0xFC);
        t = t + 0x40;
        *(u16 *)((s32)arg0 + 0xFC) = t;
        if ((s16)t >= 0x400) {
            *(u16 *)((s32)arg0 + 0x34) = *(u16 *)((s32)arg0 + 0x34) + 1;
        }
        *(s32 *)((s32)arg0 + 0x8) =
            *(s32 *)((s32)arg0 + 0x8) -
            ((0x1000 - func_80047948(*(s16 *)((s32)arg0 + 0xFC))) << 7);
        break;
    }
    case 1:
        if (D_80126B60 != *(s32 *)((s32)arg0 + 0xDC)) {
            *(u16 *)((s32)arg0 + 0xA) = *(u16 *)((s32)arg0 + 0xA) - 8;
        }
        break;
    }

    *(s32 *)((s32)arg0 + 0xDC) = D_80126B60;
    return 0;
}


extern s32 func_8012C354(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);

void func_80180C34(s32 a0) {
    extern u8 D_8019371C[];
    extern M2C_UNK D_8019375C;
    s32 s0 = a0;
    if (func_8012C354(a0, (s32)&D_8019371C)) {
        *(u8 *)(s0 + 0xC0) = 1;
        *(s32 *)(s0 + 0xB4) = -1;
        *(s16 *)(s0 + 0xAE) = -1;
        *(u16 *)(s0 + 0x2) = 1;
        *(u8 *)(s0 + 0x75) = 0;
        func_8012A828(s0, (s32)&D_8019375C);
    }
}


extern s32 D_801936E4;

void func_80180C9C(s32 a0)
{
    if (func_8012BE54(a0) < 0x6401) {
        func_80178B18(a0, (s32)&D_801936E4);
        *(s16 *)(a0 + 2) = 2;
    }
}



extern int func_80178970(void);
extern void func_80178D18(void);

void func_80180CE8(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


extern s32 func_8012C354(s32 a0, void *a1);
extern u8 D_80193780;

void func_80180D28(s32 param_1)
{
    if (func_8012C354(param_1, &D_80193780) != 0) {
        *(u8 *)(param_1 + 0xc0) = 1;
        *(s32 *)(param_1 + 0xb4) = -1;
        *(s16 *)(param_1 + 0xae) = -1;
        *(u8 *)(param_1 + 0x75) = 8;
        *(s16 *)(param_1 + 2) = 1;
        *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x80000000;
    }
}


extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern u8 D_801202A0[];
extern void func_8012B2CC(s32 a0);
extern void func_8012F038(int param_1, short *param_2, short *param_3);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_80180D98(void *arg) {
    u16 sp10[3];
    s32 sp18;
    s32 sp1C;
    u8 *ptr;
    s32 i;
    s32 temp;
    s32 *p20;

    if (*(u16 *) ((s32) arg + 0x34) == 0) {
        *(u16 *) ((s32) arg + 0x34) = 1;
        func_8012B2CC((s32) arg);
    }
    sp10[0] = D_80126B5E;
    sp10[1] = D_80126B62;
    sp10[2] = D_80126B66;
    func_8012F038(*(s32 *) ((s32) arg + 0x20) + 0x34, (s16 *) sp10, (s16 *) &sp18);
    if ((((s16) D_80126B62) < -1535)
            && ((u16) (*(u16 *) &sp1C + 0x14) < 0xB)
            && ((u16) (*(u16 *) &sp18 + 0x60) < 0xC1)) {
        *(u16 *) ((s32) arg + 2) = 2;
        func_8002D4C8(0xC2A, 0);
        ptr = D_801202A0;
        for (i = 0; i < 0x60; i++) {
            if (*(u16 *) ptr == 0x390) {
                *(s32 *) ((s32) arg + 0x6C) = (s32) ptr;
                temp = *(u16 *) ((s32) ptr + 0x36);
                p20 = *(s32 **) ((s32) arg + 0x20);
                *(u16 *) ((s32) arg + 0x5C) = 0x800;
                *(u16 *) ((s32) arg + 0xFE) = temp;
                *(s32 *) ((s32) p20 + 4) &= 0x7FFFFFFF;
            }
            ptr += 0x10C;
        }
    }
}


extern s32 func_80047948(s32 arg0);

void func_80180ECC(void *a0) {
    s16 t;

    t = *(u16 *)((char *)a0 + 0xFC) + 0x40;
    *(u16 *)((char *)a0 + 0xFC) = t;
    *(s16 *)((char *)a0 + 0xA) = (func_80047948(t) >> 6) - 0x600;
    if (*(s16 *)((char *)a0 + 0xFC) < 0x400) {
        return;
    }
    *(u16 *)((char *)a0 + 2) = 3;
}


















void func_80180F2C(void *a0)
{
  s32 v0;
  void *p = *((void **) (((char *) a0) + 0x6c));
  v0 = *((short *) (((char *) p) + 0x36));
  if (v0 != (*((short *) (((char *) a0) + 0xfe))))
  {
    *((short *) (((char *) a0) + 0x2)) = 4;
    *((short *) (((char *) a0) + 0xfc)) = 0;
  }
}

extern s32 func_8004787C(s32 a0);
extern void func_8012C218(s32 a0);

void func_80180F58(s32 param_1)
{
    s16 var;

    var = *(u16 *)(param_1 + 0xFC) + 0x40;
    *(u16 *)(param_1 + 0xFC) = var;
    *(u16 *)(param_1 + 0xA) = (func_8004787C(var) >> 6) - 0x600;
    if (*(s16 *)(param_1 + 0xFC) >= 0x400)
    {
        func_8012C218(param_1);
    }
}


extern void (*D_801937D8[])(void);

void func_80180FB8(void *a0) {
    D_801937D8[*(u16 *)((s32)a0 + 0x2)]();
}


#include "common.h"

extern void func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void (*D_801937C8[])(void);

void func_80180FF4(s32 arg0) {
    s32 v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((u8 *)arg0 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(arg0);
    } else {
        func_8001C214(v0, 0);
        *(s32 *)((u8 *)arg0 + 0x58) = (u32)&D_801937C8 | 0x10000000 | 0x40000000;
        *(u16 *)((u8 *)arg0 + 0x2) = *(u16 *)((u8 *)arg0 + 0x2) + 1;
    }
}


#include "common.h"

extern u8 D_801202A0[];
extern void func_8012ADE4(u8 *a0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);

void func_80181068(s32 arg0) {
    s32 i;
    u8 *p;
    u16 kind;
    s16 buf1[3];
    s16 buf2[3];

    i = 0;
    p = D_801202A0;
    for (; i < 0x60; i++, p += 0x10C) {
        kind = *(u16 *)p;
        switch (kind) {
        case 0x263:
        case 0x25D:
        case 0x27A:
            buf1[0] = *(u16 *)(p + 0x3A);
            buf1[1] = *(u16 *)(p + 0x3E);
            buf1[2] = *(u16 *)(p + 0x42);
            buf2[0] = *(u16 *)(p + 0x6);
            buf2[1] = *(u16 *)(p + 0xA);
            buf2[2] = *(u16 *)(p + 0xE);
            if (func_80135A4C(*(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x58),
                               (s32 *)buf1, (s32)buf2) != 0) {
                if ((func_8012CEB0((s32)buf1, (s32)buf2, 0) & 0x2000) != 0) {
                    *(u16 *)(p + 0x6) = buf2[0];
                    *(u16 *)(p + 0xA) = buf2[1];
                    *(u16 *)(p + 0xE) = buf2[2];
                } else {
                    func_8012ADE4(p);
                }
            }
            break;
        }
    }
}



extern void func_80019064(void *a0);

void func_801811AC(void *a0) {

    extern u8 D_801937E0;
    extern void (*D_80193808[])(void *);
    func_80019064(&D_801937E0);
    D_80193808[*(u16 *)((s32)a0 + 0x2)](a0);
}


extern void func_80146CA0(void *a0);
extern void func_80147324(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014E934(s32 _arg0);
extern s32 func_8014F3E8(s32 a0);


void func_80181204(s32 a0)
{
    s32 s0 = a0;
    func_8014E934(a0);
    func_8014CC28(s0);
    func_8014F3E8(s0);
    func_80181254(s0);
    func_80147324(0x92F);
    func_80146CA0((void *)s0);
}


extern int func_801511E0(int arg);
extern s32 func_80172630(u8 *a0);
extern u8 D_801937E8[];
extern void func_80146CA0(void *a0);
extern void func_80147324(s32 arg0);
extern void func_80149020(s32 *a0);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80181468(void);

void func_80181254(s32 p)
{
    func_80147324(0x451);
    ((void (*)(s32))func_801511E0)(p);
    ((void (*)(s32, s32))func_80154274)(p, (s32)D_801937E8);
    ((void (*)(s32))func_80149020)(p);
    *(u8 *)(p + 0xDE) = 0x1E;
    *(u8 *)(p + 0xDF) = 0;
    func_80181468();
    ((void (*)(s32))func_80172630)(p);
    ((void (*)(s32))func_80146CA0)(p);
}



/* func_801812C0 @ ov_SC02_016 (subseg ov_SC02_016_jr_8017DC70) — 85 ins.
 *
 * GATE: .venv/bin/python tools/match_one.py func_801812C0 --binary ov_SC02_016 \
 *         --src .run/wave-s40/ov_SC02_016/func_801812C0.c
 *
 * Exemplar of an OPEN-ONLY h_norm cluster (9 members). Real TU is
 * src/ov_SC02_016/ov_SC02_016_jr_8017DC70.c — the immediate NEXT function in that
 * file, func_80181414 (already MATCHed, see its comment there), confirms:
 *   - actor pointer arg is plain `s32 a0`
 *   - func_80172630 canon extern: `extern s32 func_80172630(u8 *a0);` (cast at call)
 *   - func_80159B3C canon extern: `extern void func_80159B3C(void *a0);` (cast at call)
 *   - func_80165718 canon extern: `extern void func_80165718(s32 a0);` (no cast)
 *   - func_80146A6C canon extern (used 30+ times fleet-wide):
 *       extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
 *
 * `func_8018148C` is DEFINED in this same TU (a few lines below the INCLUDE_ASM
 * stub for this function) — a simple "find a free slot, mark it used" scan
 * returning the slot index or -1.
 *
 * Body shape (byte-confirmed against the .s, no residual after first draft):
 *   func_80015978(a0+4, buf)     -- fills a 3-short (SVECTOR-shaped) local from
 *                                    the actor's position substruct at a0+4; this
 *                                    exact `s16 buf[4]; func_80015978(a0+4,(s32*)buf);`
 *                                    idiom is the established fleet form (see
 *                                    engine_core.h DEFINE_func_8014A380/8016D778/
 *                                    8017C908 dedup macros).
 *   buf[1] -= 0x40                -- immediately after the call. The readback here
 *                                    is `lhu` (not `lh`) even though buf is a SIGNED
 *                                    s16 array: gcc-2.7.2 always emits `lhu` for a
 *                                    plain HImode load that feeds straight into an
 *                                    `sh` store (cookbook: "It does NOT cost you the
 *                                    lhu on readback" bullet, P30 wave 4). No cast
 *                                    needed, no separate unsigned local needed.
 *   do { ... } while (++i < 3)    -- the asm has NO initial top-of-loop test before
 *                                    label .L80182318 (s3=0 set, then falls straight
 *                                    into the body) -- a genuine do-while in the
 *                                    source, not a for-loop gcc happened to rotate.
 *   if (func_8018148C() >= 0) { func_80146A6C(0x51,...); 3x rand(); func_80146A6C(0x52,...); }
 *      - the three back-to-back `rand()` calls assign straight to 3 locals in
 *        source order; gcc's own delay-slot filler moves each captured value into
 *        a callee-saved reg ($s0/$s1) via the NEXT call's branch-delay slot
 *        (standard call-crossing-value idiom, cookbook "ORDER" register-allocation
 *        entry) -- no manual reordering needed, plain sequential C reproduces it.
 *      - the final random offset is computed into a **s16 local** (not s32): the
 *        assignment truncates+sign-extends via `sll/sra` in-register (matches the
 *        target's `sll $s0,$s0,16 / sra $s0,$s0,16` with NO memory round-trip,
 *        because the s16 value is used immediately as a call argument rather than
 *        stored to a separate memory slot).
 *   cnt = *(u8*)(a0+0xDE); *(u8*)(a0+0xDE) = cnt + 0xff; if (cnt == 0) { ... } else { ... }
 *      - `lbu` (not `lb`) for the read: the "feeds only a truncated store + an
 *        equality-to-zero test" idiom, so either signedness of the C type reads
 *        identically; u8 chosen to match the common counter-byte convention used
 *        elsewhere in this TU.
 *      - THE ONE non-obvious lever: write the decrement as `cnt + 0xff`, not
 *        `cnt - 1`. Both are mathematically identical mod 256 (only the low byte
 *        survives the `sb`), and both compile to a single `addiu`, but gcc-2.7.2
 *        picks a DIFFERENT immediate encoding for each source spelling: `cnt - 1`
 *        emits `addiu $v0,$v1,-1` (imm 0xFFFF, sign-extended -1); `cnt + 0xff`
 *        emits `addiu $v0,$v1,0xFF` (imm 0x00FF, the literal as typed) — which is
 *        what the target has. Confirmed the signedness of `cnt` (s8 vs u8) makes
 *        no difference here; the literal's own spelling is the lever. New
 *        cookbook idiom candidate (not in §31 as of this match).
 */

extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8018148C(void);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern int rand(void);
extern void func_80181414(s32 a0);
extern void func_80159B3C(void *a0);
extern void func_80165718(s32 a0);
extern s32 func_80172630(u8 *a0);

void func_801812C0(s32 param_1)
{
    s16 buf[4];
    s32 i;
    s32 iVar1;
    s32 uVar3;
    s32 uVar4;
    s32 uVar5;
    s16 rnd;
    u8 cnt;

    func_80015978(param_1 + 4, (s32 *)buf);
    buf[1] -= 0x40;

    i = 0;
    do {
        iVar1 = func_8018148C();
        if (iVar1 >= 0) {
            func_80146A6C(0x51, (void *)param_1, buf[0], buf[1], buf[2], iVar1, 0);

            uVar3 = rand();
            uVar4 = rand();
            uVar5 = rand();
            rnd = (uVar3 & 3) * 0x400 + (uVar4 & 3) * 0xfa + (uVar5 & 3) * 0x44;
            func_80146A6C(0x52, (void *)param_1, 0, -0x20, 0x10, rnd, 0);
        }
        i++;
    } while (i < 3);

    cnt = *(u8 *)(param_1 + 0xde);
    *(u8 *)(param_1 + 0xde) = cnt + 0xff;
    if (cnt == 0) {
        func_80181414(param_1);
        func_80159B3C((void *)param_1);
        func_80165718(param_1);
    } else {
        func_80172630((u8 *)param_1);
    }
}


extern void func_80147324(s32 a0);
extern void func_80147364(u16, s32);
extern void func_8014BC44(s32 a0, s32 a1);

/* func_80181414 — actor "enter state 0x92F/0x930" stub: two sound/state pokes,
 * the standard `func_8014BC44(actor, actor->0xF2)` animation kick, set 0xA8 = 0x20,
 * then hand the actor to func_80151664.
 *
 * Two load-bearing derivations (both byte-verified against the .s):
 *
 *  1. The final call TAKES THE ACTOR. The .s sets `addu $a0,$s0,$zero` immediately
 *     before `jal func_80151664`, but the whole fleet declares
 *         extern void func_80151664(void);
 *     (16 TUs + engine_core.h:2924; ov_SC02_016_after.c:3151 records that a
 *     `void func_80151664(s32)` definition is `conflicting types` everywhere).
 *     So: cookbook idiom 9 — cast at the CALL SITE, never touch the decl:
 *         ((void (*)(s32))func_80151664)(a0)
 *     The .run/ghidra_c seed shows `FUN_80151664()` with no argument and is WRONG
 *     here; the .s wins. This is the single instruction the previous draft missed.
 *
 *  2. `sb $v0, 0xA8($a0)` uses $a0 — NOT $s0 — as its base, and lands in the jal's
 *     delay slot. That needs no local-variable lever (no `s32 s0 = a0;` as the
 *     sibling DEFINE_func_80152790 template uses): the arg copy into $a0 is emitted
 *     ahead of the store, so the store simply addresses off the live copy, and
 *     reorg.c then lifts the last pre-jal insn into the delay slot. Writing a
 *     separate pointer local here would only add a pseudo.
 *
 * Declaration surface (D2 pass over the whole TU, one grep):
 *   func_80147364  -> ov_SC02_016_jr_8017DC70.c:194,360  extern void (u16, s32)
 *   func_80147324  -> :196,777                           extern void (s32)
 *   func_8014BC44  -> :486                                extern void (s32, s32)
 *   func_80151664  -> :880                                extern void (void)  [re-declared
 *                     identically below, which is a legal duplicate declaration]
 *   func_80181414  -> only the INCLUDE_ASM at :3587; no prior prototype anywhere in
 *                     ov_SC02_016 or include/. (The ov_SC03_09x definitions of this
 *                     name are other overlays sharing the VA — different binaries.)
 * Recompiled with those four prototypes prepended: still MATCH (21 ins).
 */

extern void func_80151664(void);

void func_80181414(s32 a0)
{
    func_80147364(4, 0x92F);
    func_80147324(0x930);
    func_8014BC44(a0, *(s16 *)(a0 + 0xF2));
    *(u8 *)(a0 + 0xA8) = 0x20;
    ((void (*)(s32))func_80151664)(a0);
}



void func_80181468(void)
{
    extern u8 D_801E1173;
    s32 i = 19;
    u8 *p = &D_801E1173;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
}




s32 func_8018148C(void)
{

    extern u8 D_801E1160[];
    s32 i;
    u8 v;
    u8 *p;
    s32 ret;

    i = 0;
    v = 1;
    p = D_801E1160;
    do {
        if (*p == 0) {
            *p = v;
            ret = i;
            goto done;
        }
        i++;
        p++;
    } while (i < 20);
    ret = -1;
done:
    return ret;
}



extern void (*D_80193814[])(void);

void func_801814D0(void *a0) {
    D_80193814[*(u16 *)((s32)a0 + 0x2)]();
}






// @class: regalloc-order
// @stuck: none — MATCH (83 ins). $s3 is a dual-copy of iVar3 used only in the ==0 tail block; natural C coalesces to one $s0, so pin iVar3=$s0 and iVar3b=$s3 (different hard regs prevent gcc coalescing the copy). Also: outer+inner branch polarity inverted (if!=0 / if!=0 puts both short blocks at the tail as beqz targets); base = (int)D_801E1174 + idx*0x40 (materialize form, arg to callees).

extern void func_801465C0(void);
extern void func_8001CD9C(int, void*);
extern void func_800233CC(void*, unsigned short);
extern void func_80181700(void*);
extern void func_801816D0(s32*);
extern int rand(void);

void func_8018150C(int param_1)
{

    extern unsigned char D_801E1174[];
    int iVar3;
    int iVar3b;
    int iVar5;
    short sVar2;

    iVar5 = (int)D_801E1174 + *(int *)(param_1 + 0x2c) * 0x40;
    iVar3 = ((int (*)(void))func_801465C0)();
    iVar3b = iVar3;
    *(int *)(param_1 + 0x20) = iVar3;
    if (iVar3 != 0) {
        ((void (*)(int, int))func_8001CD9C)(iVar3, iVar5);
        ((void (*)(int, int))func_800233CC)(iVar5, 0x10);
        ((void (*)(int))func_80181700)(iVar5);
        *(unsigned int *)(iVar3 + 4) = *(unsigned int *)(iVar3 + 4) | 0x50000000;
        if (*(int *)(param_1 + 0x2c) != 0) {
            sVar2 = (rand() & 3) * 0x800 + 0x1000;
            *(short *)(iVar3 + 0x1a) = sVar2;
            *(short *)(iVar3 + 0x18) = sVar2;
            *(unsigned short *)(param_1 + 0x12) = (rand() & 0xf) + 3;
            if ((rand() & 1) != 0) {
                *(short *)(param_1 + 0x12) = -*(short *)(param_1 + 0x12);
            }
            *(unsigned short *)(param_1 + 0x1a) = (rand() & 0xf) + 3;
            if ((rand() & 1) != 0) {
                *(short *)(param_1 + 0x1a) = -*(short *)(param_1 + 0x1a);
            }
        } else {
            *(short *)(iVar3b + 0x1a) = 0x4000;
            *(short *)(iVar3b + 0x18) = 0x4000;
        }
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    } else {
        ((void (*)(int))func_801816D0)(param_1);
    }
}




extern s32 func_80181714(s32 *a0, s32 a1);
extern void func_801816D0(s32 *a0);

void func_80181658(s32 *a0)
{

    extern unsigned char D_801E1174[];
    s32 param;
    s32 table_base;

    param = *(s32 *)((s32)a0 + 0x2c);
    table_base = (s32)D_801E1174 + param * 0x40;

    if (param != 0) {
        *(s16 *)((s32)a0 + 0x6) += *(s16 *)((s32)a0 + 0x12);
        *(s16 *)((s32)a0 + 0xE) += *(s16 *)((s32)a0 + 0x1A);

        if (func_80181714(a0, table_base) == 0) {
            return;
        }
    }

    func_801816D0(a0);
}



















extern void func_80146C3C(void);
void func_801816D0(s32 *param_1)
{

    extern s8 D_801E1160;
  int new_var;
register s32 p __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
s32 r;
  p = (s32) (&D_801E1160);
  r = param_1[0x2c / 4];
  new_var = r;
  p += new_var;
  *((s8 *) p) = 0;
  ((void (*)(void)) func_80146C3C)();
}



void func_80181700(void *a0) {
        *(s32 *)((s32)a0 + 0x0) = 0xF0F0F0;
        *(s32 *)((s32)a0 + 0x4) = 0;
    }




/* func_80181714 — scroll/advance one "text-ish" byte pair and pack it into a
 * 24-bit-ish word. Returns 1 when the decoded value is <= 0 (nothing written),
 * else stores the packed word through a1 and returns 0.
 *
 * Signature matches the in-TU forward declaration emitted by the func_80182678
 * draft: extern s32 func_80181714(s32 *a0, s32 a1);
 *
 * Two derivations that mattered (both byte-verified against the .s):
 *  - Both `-0x20` subtractions and the `sll $v0,$a2,16` in the bnez delay slot
 *    are reorg.c fill-from-target duplicates, NOT source duplication: one
 *    `t -= 0x20` after the if reproduces them exactly.
 *  - `(t << 8) | (t | 0xFF0000)` written as ONE expression is reassociated by
 *    fold()'s associate/split_tree step into `t | ((t<<8) | 0xFF0000)`, which
 *    swaps $v0/$v1 on the two temps. Splitting it into three statements gives
 *    fold nothing to reassociate and reproduces the target's temp lifetimes
 *    (local-alloc's qty_compare gives the SHORT-lived temps the lower reg, so
 *    the long-lived `x` correctly lands in $v1 and the pair in $v0).
 */
s32 func_80181714(s32 *a0, s32 a1) {
    s32 t;
    s32 ret;

    if (*(s32 *)((s32)a0 + 0x30) == 0) {
        t = *(u8 *)(a1 + 1);
    } else {
        t = *(u8 *)(a1 + 2);
    }
    t -= 0x20;
    ret = 1;
    if (t > 0) {
        if (*(s32 *)((s32)a0 + 0x30) == 0) {
            s32 x = t << 8;
            s32 y = t | 0xFF0000;
            t = x | y;
        } else {
            t = (t << 16) | 0xFFFF;
        }
        *(s32 *)a1 = t;
        ret = 0;
    }
    return ret;
}


extern void (*D_8019384C[])(void);

void func_8018177C(void *a0) {
    D_8019384C[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80146E90(s32 *a0, s32 a1);

void func_801817B8(s32 param_1)
{
    u8 pad[0x28];
    func_801495C4(*(s32 *)(param_1 + 0x34), param_1 + 0x4);
    func_80146E90((s32 *)param_1, 3);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}




extern s32 func_80146E98(s32 a0);
extern void func_80146C3C();
extern void func_80181854(s32 param_1);

void func_80181804(s32 param) {
    if (func_80146E98(param) != 0) {
        ((void (*)(s32))func_80146C3C)(param);
    } else {
        func_80181854(param);
    }
}


void func_8018184C(void) {
}




extern void func_80015978(s32 a0, s32 *a1);
extern void func_801819B8();

void func_80181854(s32 param_1) {

    extern u32 *D_80193844[];
    extern Blk8 D_80193860[];
    s32 buf[2];
    Blk8 A;
    Blk8 B;
    Blk8 C;
    Blk8 D;
    u32 *basep;
    s32 i;
    s32 j;

    basep = D_80193844[*(s32 *)(param_1 + 0x30)];
    *(s16 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x2c);
    func_80015978(param_1 + 4, buf);
    for (j = 0; j < 4; j++) {
        *(s16 *)&A = 0;
        *((s16 *)&A + 1) = 0;
        *((s16 *)&A + 2) = 0;
        B = A;
        C = A;
        for (i = 0; i < 4; i++) {
            D = D_80193860[i];
            *(s16 *)(param_1 + 0x12) = i + j;
            func_801819B8(param_1, buf, &A, &B, &C, &D, param_1 + 0x10, basep + i);
        }
    }
}


#include "common.h"
#include "../shared/engine_types.h"



// @class: regalloc-order
// @stuck: none — MATCH (223 ins). Giant GTE coord transform. Two levers: (1) vy = {int t=vy-0x10; t+(r&0x1f);}
//   blocks the (r&0x1f)-16 reassoc that materialized -0x10 via `li 0xfff0` (+1 ins); (2) inline the one-shot
//   r0_00+1 stsv arg so it stays a $v0 temp instead of stealing a saved reg from the reused pSVar6.

   /* 8, align 2 -> lwl/lwr copy */
  /* 0x20 */
    /* 4, align 1 -> lwl/lwr */

extern void func_80013F3C(s32);
extern void RotMatrixZ(s32, void *);
extern void func_8004914C(void *);
extern void func_800491AC(void *);
extern int rand(void);
extern void func_80017714(void *);

extern SVECTOR_8017E6D8 D_801E1674[4];
extern struct PW8017E6D8 D_801E1694;
extern struct PW8017E6D8 D_801E1698;
extern u8 D_801E169C, D_801E169D, D_801E169E, D_801E16A0, D_801E16A1, D_801E16A2;
extern int D_801E16A4;




void func_801819B8(int a, s16 *b, SVECTOR_8017E6D8 *c, SVECTOR_8017E6D8 *d,
                   SVECTOR_8017E6D8 *e, SVECTOR_8017E6D8 *f, s16 *g, struct PW8017E6D8 *h)
{
    MATRIX_8017E6D8 m;
    SVECTOR_8017E6D8 *r0_00;
    SVECTOR_8017E6D8 *pSVar6;
    SVECTOR_8017E6D8 *r0;
    int r;
    int mask;

    func_80013F3C((s32)&m);
    RotMatrixZ(g[0], &m);
    m.t[0] = b[0];
    m.t[1] = b[1];
    m.t[2] = 0;
    func_8004914C(&m);
    func_800491AC(&m);

    r0_00 = &D_801E1674[0];
    if (*(s16 *)(a + 0x12) == 0) {
        D_801E16A4 = 0x50000000;
        D_801E169C = 0;
        D_801E169D = 0;
        D_801E169E = 0;
        D_801E16A0 = 0;
        D_801E16A1 = 0;
        D_801E16A2 = 0;
    }
    D_801E1694 = h[0];
    D_801E1698 = h[1];

    f->vx = f->vx + c->vx;
    f->vy = f->vy + c->vy;
    r = rand();
    mask = f->pad & r;
    if (*(u16 *)(a + 0x12) & 1)
        f->vx = f->vx + mask;
    else
        f->vx = f->vx - mask;
    r = rand();
    { int t = f->vy - 0x10; f->vy = t + (r & 0x1f); }

    gte_ldv0(c);
    gte_rtv0tr();
    gte_stsv(r0_00);

    gte_ldv0(f);
    gte_rtv0tr();
    gte_stsv(r0_00 + 1);

    gte_ldv0(d);
    gte_rtv0tr();
    r0 = r0_00 + 2;
    gte_stsv(r0);

    *d = *f;
    r = rand();
    d->vx = d->vx - (f->pad & r);

    gte_ldv0(d);
    gte_rtv0tr();
    pSVar6 = r0_00 + 3;
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    gte_ldv0(e);
    gte_rtv0tr();
    gte_stsv(r0);

    *e = *f;
    r = rand();
    e->vx = e->vx + (f->pad & r);

    gte_ldv0(e);
    gte_rtv0tr();
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    *c = *f;
}
