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
extern s32 func_8014C568(void *a0);
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
extern s32 func_80128ED8(void *a0, void *a1);
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

void func_8017BEBC(s32 arg0)
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


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017CD9C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017CDE4);


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


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017D150);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017D1EC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017D288);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017D2C8);


extern void (*D_801932D4[])(void);

void func_8017D34C(void *a0) {
    D_801932D4[*(u8 *)((s32)a0 + 0x4)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017D388);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017D474);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017D550);


// @class: schedule
// @stuck: none — MATCH (102 ins). MATRIX(0x20:m@0,t@0x14)+SVECTOR in/out stack layout; the only
//   lever past struct-layout was source order: emit m1.t[2] BEFORE svec_in.vx/vy so the two `sh
//   zero` stores schedule into the t[2] load-delay slot (after the a1 setup), not after t[1].

   /* 0x20: m@0, pad@0x12, t@0x14 */
      /* 8 bytes */

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32);

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
    register int iVar1 __asm__("$4");
    iVar1 = *(int *)(D_801932EC + param_1 * 4);
    __asm__ __volatile__("" ::: "memory");
    func_8013B7F4((void *)iVar1, 0);
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017D804);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017D89C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017DA9C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017DAE0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017DBFC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017E1F0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017E548);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017E61C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017E8F8);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017EADC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017EC4C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017F4FC);


extern void (*D_801935C8[])(void);

void func_8017F7B8(void *a0) {
    D_801935C8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017F7F4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017FA1C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017FB28);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017FB84);


extern void (*D_801935E0[])(void);

void func_8017FBF8(void *a0) {
    D_801935E0[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017FC34);


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


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017FCFC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8017FFCC);



extern void (*D_8019366C[])(void);

void func_80180104(void *a0) {
    D_8019366C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180140);

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


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180220);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018036C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180594);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180724);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180894);


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


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801809A8);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180AA8);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180B5C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180C34);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180C9C);


extern int func_80178970(void);
extern void func_80178D18(void);

void func_80180CE8(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180D28);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180D98);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180ECC);

















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

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180F58);

extern void (*D_801937D8[])(void);

void func_80180FB8(void *a0) {
    D_801937D8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80180FF4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80181068);


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


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80181254);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801812C0);

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
    register int iVar3 __asm__("$16");
    register int iVar3b __asm__("$19");
    int iVar5;
    short sVar2;

    iVar5 = (int)D_801E1174 + *(int *)(param_1 + 0x2c) * 0x40;
    iVar3 = ((int (*)(void))func_801465C0)();
    *(int *)(param_1 + 0x20) = iVar3;
    iVar3b = iVar3;
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
register s32 p __asm__("$4");
register s32 r __asm__("$3");
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

#define gte_ldv0(r0)  __asm__ __volatile__( \
    "lwc2 $0, 0(%0)\n" \
    "lwc2 $1, 4(%0)\n" \
    : : "r"(r0) : "memory")

#define gte_rt()  __asm__ __volatile__( \
    "nop\n" \
    "nop\n" \
    "mvmva 1, 0, 0, 0, 0\n" \
    : : : "memory")

#define gte_stsv(r0)  __asm__ __volatile__( \
    "mfc2 $12, $9\n" \
    "mfc2 $13, $10\n" \
    "mfc2 $14, $11\n" \
    "sh $12, 0(%0)\n" \
    "sh $13, 2(%0)\n" \
    "sh $14, 4(%0)\n" \
    : : "r"(r0) : "$12", "$13", "$14", "memory")

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
    gte_rt();
    gte_stsv(r0_00);

    gte_ldv0(f);
    gte_rt();
    gte_stsv(r0_00 + 1);

    gte_ldv0(d);
    gte_rt();
    r0 = r0_00 + 2;
    gte_stsv(r0);

    *d = *f;
    r = rand();
    d->vx = d->vx - (f->pad & r);

    gte_ldv0(d);
    gte_rt();
    pSVar6 = r0_00 + 3;
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    gte_ldv0(e);
    gte_rt();
    gte_stsv(r0);

    *e = *f;
    r = rand();
    e->vx = e->vx + (f->pad & r);

    gte_ldv0(e);
    gte_rt();
    gte_stsv(pSVar6);

    r0_00->vz = ((u16 *)b)[2];
    func_80017714(r0_00);

    *c = *f;
}



INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80181D34);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80181ED4(s32 arg0) {
        ((void (*)(s32, s32))func_8012AD44)(arg0, 0x1);
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80181EF4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80181FD4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80182074);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_801823A8(void *a0) {
        *(s32 *)((char *)a0 + 0x1c) = 0x20;
        ((void (*)(s32 *, s32))func_8012AD44)(a0, 0x4);
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801823D0);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80182584(void *arg0) {
        ((void (*)(void *, int))func_8012AD44)(arg0, 0x5);
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801825A4);


extern void (*D_801AC4F8[])(void);

void func_801827E8(void *a0) {
    D_801AC4F8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80182824);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801828FC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80182994);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80182B58);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80182BD8);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80182D10);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80182EAC(s32 arg0) {
        ((void (*)(s32, s32))func_8012AD44)(arg0, 0x3);
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80182ECC);

extern void func_8012AD44(s32 *a0, s16 a1);
    void func_80183188(s32 arg0) {
        ((void (*)(s32, s32))func_8012AD44)(arg0, 0x5);
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801831A8);


extern void (*D_801AC564[])(void);

void func_8018337C(void *a0) {
    D_801AC564[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801833B8);


void func_80183408(s32 target, u16 *cur, s32 step)
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


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018348C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183598);


extern void (*D_801AC590[])(void);

void func_80183640(void *a0) {
    D_801AC590[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018367C);


extern void func_8012B23C();
extern s32 rand(void);
extern void func_8012AD44(s32 *a0, s16 a1);

void func_801837D0(s32 a0) {
    func_8012B23C(a0);
    *(s32 *)(a0 + 0x10) = ((rand() & 0x7F) - 0x40) << 11;
    *(s32 *)(a0 + 0x14) = -((rand() & 0x7F) << 13);
    *(s32 *)(a0 + 0x18) = (rand() & 0x7F) << 13;
    *(u16 *)(a0 + 0x106) = rand() & 0x1F0;
    *(u16 *)(a0 + 0x108) = rand() & 0x1F0;
    *(s16 *)(a0 + 0xE6) = 8;
    {
        s32 v = *(s16 *)(a0 + 0x70);
        *(s16 *)(a0 + 0xE4) = v << 1;
    }
    ((void (*)(s32, s32))func_8012AD44)(a0, 1);
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018386C);


// @class: struct
// @stuck: none — MATCH (fn-ptr table %lo-fold via extern array of code ptrs)

extern code_fn D_801AC64C[];

extern s32 func_8012B414(s32 a0);

void func_801838A0(int param_1)
{
    D_801AC64C[*(unsigned short *)(param_1 + 2)]();
    ((void (*)(int))func_8012B414)(param_1);
    return;
}



extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_801838F0(s32 arg0) {
    s32 i;

    for (i = 0; i < 20; i++) {
        func_8012C658(0x311, i, arg0);
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183940);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183A28);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183AA4);

void func_80183B34(void) {
}

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183B3C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183C1C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183C58);

void func_80183CA8(void) {
}

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183CB0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183DBC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183E74);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183F24);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80183F6C);


// @class: struct
// @stuck: none — MATCH (135/135 ins, match_one confirmed)


extern s32 func_8012C354(s32 a0, void *a1);
extern s32 func_80143994(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32 func_8012C658(s32 a0, s32 a1, s32 a2);
extern void func_8012CAE4(s32 a0);
extern void func_8012B030(s32 a0);
extern void func_8012B2CC(s32 a0);

void func_80183FDC(s32 param_1) {

    extern Elem52_801B5094 D_801BC130[];
    extern u8 D_801BC2C8[];
    extern u8 D_801BC250[];
    extern u8 D_801D321C[];
    extern u16 D_801D3710;
    extern u16 D_801D3568;
    s32 iVar1;
    u16 uVar2;

    iVar1 = func_8012C354(param_1, &D_801BC130[*(u16 *)(param_1 + 0x70) & 0xf]);
    if (iVar1 != 0) {
        *(u8 *)(param_1 + 0xc0) = 1;
        *(u8 **)(param_1 + 0xbc) = D_801BC2C8;
        *(s32 *)(param_1 + 0xb4) = -0x8ad;
        *(u32 *)(param_1 + 0xc4) |= 2;
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2c) |= 0x80;
        *(u8 **)(*(s32 *)(param_1 + 0x20) + 0x80) = D_801BC250;
        func_80143994(param_1, 0x4000);
        *(s32 *)(param_1 + 0x48) = 0x18000;
        uVar2 = *(u16 *)(param_1 + 0x70) & 0xf;
        switch (uVar2) {
        case 0: {
            s32 t;
            *(u32 *)(param_1 + 0xe0) |= 1;
            t = (s32)*(u16 *)(*(s32 *)(param_1 + 0x78)) << 0x10;
            *(s16 *)(param_1 + 0xfe) = (s16)((t >> 0x10) / 2);
            if (((s32)*(s16 *)(param_1 + 0x70) & 0x8000) == 0) {
                *(s16 *)(param_1 + 2) = 2;
            } else {
                *(s16 *)(param_1 + 2) = 1;
                *(s32 *)(param_1 + 0x1c) = 0x1e;
                func_8012A828(param_1, &D_801D321C);
            }
            break;
        }
        case 1:
            *(s16 *)(param_1 + 2) = 0x13;
            D_801D3710 = 0x28;
            if (((s32)*(s16 *)(param_1 + 0x70) & 0x8000) != 0) {
                *(u32 *)(param_1 + 0xe0) |= 0x400;
            }
            break;
        case 2:
            *(s16 *)(param_1 + 2) = 0x18;
            D_801D3568 = 0x28;
            break;
        case 3:
            *(s16 *)(param_1 + 2) = 0x1f;
            if (func_8012C658(0x27f, 5, param_1) == 0) {
                func_8012CAE4(param_1);
                return;
            }
            break;
        }
        func_8012B030(param_1);
        *(s32 *)(param_1 + 0x38) = *(s32 *)(param_1 + 4);
        *(s32 *)(param_1 + 0x3c) = *(s32 *)(param_1 + 8);
        *(s32 *)(param_1 + 0x40) = *(s32 *)(param_1 + 0xc);
        func_8012B2CC(param_1);
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801841F8);


/* func_80184248 — a randomised state entry: seed the timer at 0x1C with
 * rand()%64 + 0x80, park 18000 at 0x48, then nudge the value at 0xE8 by a
 * random 0..1023 in a random direction, push the command list D_801D3D3C,
 * set the state word at 0x02 to 3 and clear bit 6 of the flags at 0xE0.
 *
 * §71 sibling-first: func_8018598C (same TU, MATCHed) is the same
 * `if ((rand() & 1) == 0) v = base - off; else v = base + off;` idiom.
 */

extern s32 rand(void);
extern void func_8012A828(s32 a0, void *a1);

void func_80184248(s32 param_1) {

    extern u8 D_801D3D3C[];
    s32 r;
    s32 off;
    s32 base;
    s32 nv;

    r = rand();
    *(s32 *)(param_1 + 0x1C) = r % 0x40 + 0x80;
    *(s32 *)(param_1 + 0x48) = 18000;

    r = rand();
    off = r % 0x400;
    base = *(s32 *)(param_1 + 0xE8);
    if ((rand() & 1) != 0) {
        nv = base + off;
    } else {
        nv = base - off;
    }
    *(s32 *)(param_1 + 0xE8) = nv;

    func_8012A828(param_1, D_801D3D3C);
    *(s16 *)(param_1 + 2) = 3;
    *(u32 *)(param_1 + 0xE0) &= 0xFFFFFFBF;
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80184310);



extern void func_8012A828(s32 a0, void *a1);

void func_8018447C(s32 param_1)
{

    extern u8 D_801D3284[];
    func_8012A828(param_1, D_801D3284);
    *(s32 *)(param_1 + 0x48) = 0x4650;
    *(s16 *)(param_1 + 0x2) = 0x5;
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801844BC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80184644);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80184678);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80184700);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018474C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80184888);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801848DC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80184A2C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80184A6C);


extern void func_8012C218(s32);
extern void func_8001C924(s32 a0, void *a1);
extern void func_8012A828(s32 a0, void *a1);
extern s32  func_8012BEE8();
extern s32  func_8012B6D4(s16 *a0, s16 *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_80187BC8(s32 a0);
extern void func_80013350(s32 a0, void *a1);


void func_80184AE8(s32 p)
{

    extern u8 D_801C2718;
    extern u8 D_801BEF54;
    extern u8 D_801D3284[];
    extern u8 D_801D4184[];
    u16 uVar1;
    s32 s1;
    s32 r;

    uVar1 = *(u16 *)(p + 0x34);
    switch (uVar1) {
    case 0:
        s1 = *(s32 *)(p + 0xCC);
        if (s1 == 0 || *(s16 *)(s1 + 0x36) != *(s16 *)(p + 0xEC) ||
            func_8012BEE8(p) != 0) {
            *(u16 *)(p + 2) = 0x23;
            *(u32 *)(p + 0xE0) |= 0x800;
            return;
        }
        goto call_b6d4;
    case 1:
        if (*(s16 *)(p + 0x98) != 0) {
            return;
        }
        ((void (*)(void *))func_8012C218)((void *)*(s32 *)(p + 0xCC));
        *(s32 *)(p + 0xCC) = 0;
        func_8001C924(*(s32 *)(p + 0x20), &D_801C2718);
        func_8012A828(p, D_801D3284);
        {
            register u16 ns __asm__("$4");
            ns = *(u16 *)(p + 0x34);
            *(s32 *)(p + 0x1C) = 0x200;
            ns = ns + 1;
            *(u32 *)(p + 0xE0) &= 0xFFFFFFFB;
            *(u16 *)(p + 0x34) = ns;
        }
        return;
    case 2:
        s1 = *(s32 *)(p + 0xD0);
        if (s1 == 0 || *(s16 *)(s1 + 0x36) != *(s16 *)(p + 0xEE) ||
            func_8012BEE8(p) != 0) {
            *(u16 *)(p + 2) = 4;
            *(u32 *)(p + 0xE0) &= 0xFFFFFFFE;
            return;
        }
    call_b6d4:
        r = func_8012B6D4((s16 *)(p + 4), (s16 *)(s1 + 4));
        *(s32 *)(p + 0xE8) = r;
        goto LAB_80184738;
    case 3:
        ((void (*)(void *))func_8012C218)((void *)*(s32 *)(p + 0xD0));
        *(s32 *)(p + 0xD0) = 0;
        func_8001C924(*(s32 *)(p + 0x20), &D_801BEF54);
        func_8012A828(p, D_801D3284);
        *(s32 *)(p + 0x48) = 0x4650;
        *(u16 *)(p + 2) = 5;
        *(u32 *)(p + 0xE0) |= 1;
        return;
    default:
        goto LAB_80184738;
    }

LAB_80184738:
    r = func_8012B608(*(s16 *)(*(s32 *)(p + 0x20) + 0x12), *(s32 *)(p + 0xE8), 8);
    *(u16 *)(*(s32 *)(p + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) + r;

    if (*(u16 *)(p + 0x34) == 0) {
        func_8012B178(p, 0xFFF8D000);
    } else {
        func_8012B178(p, 0xFFF90000);
    }

    func_80187BC8(p);

    r = ((s32(*)(s32, s32))func_80013350)(p + 4, s1 + 4);
    if (r < 0x900) {
        if (*(u16 *)(p + 0x34) == 0) {
            func_8012A828(p, D_801D4184);
        }
        *(u16 *)(p + 0x34) = *(u16 *)(p + 0x34) + 1;
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80184D68);


extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32  func_8012BDBC(s32 a0, s32 a1);
extern s32  func_8012BEE8();
extern void func_80142414(s32 a0, s16 a1);

void func_80184DB0(s32 p) {
    s32 r;

    if (*(u16 *)(p + 0x34) == 0) {
        r = func_8012B608(*(s16 *)(*(s32 *)(p + 0x20) + 0x12), *(s32 *)(p + 0xE8), 4);
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) += r;
        if (func_8012BDBC(p, 0x200) != 0) {
            *(s32 *)(p + 0x1C) = 0xF;
            *(u16 *)(p + 0x34) += 1;
            func_80142414(p, -0x90);
        } else if (r == 0) {
            *(u16 *)(p + 2) = 2;
        }
    } else if (func_8012BEE8(p) != 0) {
        *(u16 *)(p + 2) = 4;
    }
}




extern void func_8012A828(s32 a0, void *a1);

void func_80184E70(s32 param_1)
{

    extern u8 D_801D3904[];
    func_8012A828(param_1, D_801D3904);
    *(s32 *)(param_1 + 0x48) = 0x4650;
    *(s16 *)(param_1 + 0x2) = 0x12;
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80184EB0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80185014);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80185068);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80185178);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801851E0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80185660);


/* func_801857D4 — randomised state entry (state word 0x19):
 * set the state at 0x02, push command list D_801D383C, seed the timer at
 * 0x1C with rand()%64 + 0x80, nudge the value at 0xE8 by a random 0..1023
 * in a random direction, then park 18000 at 0x48.
 *
 * §71 sibling-first: func_80183CDC / func_8018598C (same TU, MATCHed) are the
 * same `if ((rand() & 1) != 0) v = base + off; else v = base - off;` idiom.
 */

extern s32 rand(void);
extern void func_8012A828(s32 a0, void *a1);

void func_801857D4(s32 param_1) {

    extern u8 D_801D383C[];
    s32 r;
    s32 off;
    s32 base;
    s32 nv;

    *(s16 *)(param_1 + 2) = 0x19;
    func_8012A828(param_1, D_801D383C);

    r = rand();
    *(s32 *)(param_1 + 0x1C) = r % 0x40 + 0x80;

    r = rand();
    off = r % 0x400;
    base = *(s32 *)(param_1 + 0xE8);
    if ((rand() & 1) != 0) {
        nv = base + off;
    } else {
        nv = base - off;
    }
    *(s32 *)(param_1 + 0xE8) = nv;

    *(s32 *)(param_1 + 0x48) = 18000;
}




extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_80187BC8(s32 a0);
extern void func_80187D50(s32 a0);
extern void func_8012F214(s32, s32, s32);
extern s32  func_8012BCCC(s32 a0);
extern s32  func_801897F0(void *a0, s32 a1, s32 a2);
extern s32  func_8012BEE8();   /* TU-canonical: an earlier call site passes zero args */

void func_8018588C(s32 p) {

    extern u8 D_801BC200[];
    s32 buf10[2];
    s32 r_b608;

    r_b608 = func_8012B608((s32)*(s16 *)(*(s32 *)(p + 0x20) + 0x12),
                           *(s32 *)(p + 0xE8), 0x10);
    *(u16 *)(*(s32 *)(p + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(p + 0x20) + 0x12) + r_b608;
    func_8012B178(p, 0xFFFBD000);

    *(u32 *)(p + 0xE0) &= 0xFFFFFFBF;
    if (func_80187BC8(p) == 0) {
        func_80187D50(p);
    }

    ((void (*)(s32, void *, void *))func_8012F214)(p, D_801BC200, buf10);
    if (func_801897F0(buf10, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x380) != 0 &&
        func_8012BCCC(p) < 0x64000) {
        *(u16 *)(p + 2) = 0x1C;
    } else if (func_8012BEE8(p) != 0) {
        *(u16 *)(p + 2) = 0x1A;
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018596C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801859AC);

extern void func_8012A828(s32, void*);
    extern short D_801D33F4;
    void func_80185A2C(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x1D;
        *(short *)((char *)a0 + 0x34) = 0;
        *(int *)((char *)a0 + 0x1c) = 0xf;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (int)&D_801D33F4);
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80185A64);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80185D38);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80185EB0);


typedef struct {
    u8  pad0[6];
    u16 f6;         /* 0x06 -> D_80126B5E */
    u8  pad8[2];
    u16 fa;         /* 0x0A -> D_80126B62 */
    u8  padc[2];
    u16 fe;         /* 0x0E -> D_80126B66 */
} StructB58_80185EF8;

/* holds a pointer value */

extern int  rand(void);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern s32  func_8012B744(void *a0, void *a1);
extern s32  func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern s32  func_80187BC8(s32 a0);
extern void func_80187D50(s32 a0);
extern void func_8012F14C(s32 a0);
extern void func_801898EC(s32, void*, void*, s32);
extern void func_80189888(s32, void*, s32, s32, s32, s32);
extern s32  func_80013478(s32 a0, s32 a1);

void func_80185EF8(s32 param_1) {

    extern s32 D_80126B58;
    extern u16       D_800B99DA;
    extern u8        D_801BC220;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 *D_80126B78;
    u8  auStack_38[8];
    s16 sp20[3];
    u8  auStack_28[8];
    register StructB58_80185EF8 *b58 __asm__("$20") = &(*(StructB58_80185EF8 *)&D_80126B58);   /* $s4 */
    short *psVar7 = (short *)(param_1 + 0xec);
    s32 sVar1;
    s32 r_b608;

    if (func_8012BEE8(param_1) != 0) {
        register unsigned int *p28 __asm__("$21") = (unsigned int *)auStack_28; /* $s5 */
        s32 r0 = rand();
        s32 coord;
        s32 s2v;
        s32 r3;
        s32 tmp;

        coord = r0 % 0x400;
        sVar1 = *(s16 *)((*(s32 *)&(*(s32 *)&D_80126B78)) + 0x12);
        s2v   = sVar1 + 0x800;
        if ((rand() & 1) == 0) {
            coord = s2v - coord;
        } else {
            s32 c = coord;   /* fresh pseudo so gcc keeps s2v first in the addu (§10 A1) */
            coord = s2v + c;
        }

        func_8012B0B4(p28, coord, rand() % 0x200 + 0x200);

        tmp = *(s32 *)auStack_28;
        psVar7[0] = b58->f6 + tmp;
        psVar7[1] = b58->fa;
        psVar7[2] = b58->fe + (tmp >> 16);

        r3 = rand();
        *(s32 *)(param_1 + 0x1c) = 0x80;
        *(s16 *)(param_1 + 0x100) = r3 % 9 + 8;
    }

    if ((*(u32 *)(param_1 + 0xe0) & 0x40) == 0) {
        *(u32 *)(param_1 + 0xe8) = func_8012B744((void *)(param_1 + 4), psVar7);
    }

    r_b608 = func_8012B608((s32)*(s16 *)(*(s32 *)(param_1 + 0x20) + 0x12),
                           *(s32 *)(param_1 + 0xe8),
                           (s32)*(s16 *)(param_1 + 0x100));
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + r_b608;
    func_8012B178(param_1, 0xfffa0000);

    *(u32 *)(param_1 + 0xe0) &= 0xffffffbf;
    if (func_80187BC8(param_1) == 0) {
        func_80187D50(param_1);
        sp20[1] = 0;
        sp20[0] = 0;
        sp20[2] = -0x100;
        ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34,
                                                 (s32)sp20, (s32)psVar7);
    }

    if (((u32)D_800B99DA % 0x28 == 0) && ((*(u32 *)(param_1 + 0xe0) & 0x80) == 0)) {
        ((void (*)(s32, s32, s32, s32))func_801898EC)(param_1, (s32)&D_801BC220, (s32)auStack_38, 0xb);
        ((void (*)(s32, s32, s32, s32, s32, s32))func_80189888)(param_1, (s32)auStack_38, 0x282, 1, 0, 0);
        *(u32 *)(param_1 + 0xe0) |= 0x80;
    }

    if (func_80013478(param_1 + 4, (s32)psVar7) < 0x400) {
        *(s32 *)(param_1 + 0x1c) = 0;
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186198);

extern void func_801875A4(void);
    void func_80186314(void *a0) {
        if (*(s16 *)((s32)a0 + 0x98) == 0) {
            ((void (*)(void))func_801875A4)();
        }
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186344);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801864C4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801867DC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186C40);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186CA4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186CF0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186D6C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186DBC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186E00);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186E48);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186E94);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80186F00);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801872EC);

extern void func_8018A3CC(s32 arg0, s32 arg1);
    void func_80187440(s32 arg0) {
        func_8018A3CC(arg0, 0x9B7);
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80187460);


extern void func_801875A4(void);
extern void func_80187A50(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);

void func_801874E4(s32 param_1) {

    extern s32 D_801D420C;
    u16 uVar1;
    s32 iVar2;

    *(s16 *)(param_1 + 0x34) = 0;
    if ((*(u32 *)(param_1 + 0xe0) & 8) == 0) {
        func_801875A4();
    } else {
        if ((*(u32 *)(param_1 + 0xe0) & 0x20) != 0) {
            func_80187A50(param_1, -0x8000);
        }
        *(s16 *)(param_1 + 2) = 0x22;
        func_8012A828(param_1, &D_801D420C);
    }
    iVar2 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(iVar2 + 0x14) = 0;
    *(s16 *)(iVar2 + 0x10) = 0;
    uVar1 = *(u16 *)(*(s32 *)(param_1 + 0x78) + 2);
    *(u32 *)(param_1 + 0xe0) = (*(u32 *)(param_1 + 0xe0) & 0xffffffd5) | 0x400;
    *(s16 *)(param_1 + 0x5e) = 0;
    *(u16 *)(param_1 + 0xae) = *(u16 *)(param_1 + 0xae) & 0xfffe;
    *(u32 *)(param_1 + 0xc4) = *(u32 *)(param_1 + 0xc4) & 0xfffffffb;
    *(s16 *)(param_1 + 0x5c) = uVar1;
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801875A4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018769C);



extern s32 func_8012BCCC(s32 a0);
extern s32 func_80189938(s32 a0, s32 a1);
extern void func_8012F214(s32, s32, s32);
extern s32 func_801897F0(void *a0, s32 a1, s32 a2);

/* Two load-bearing constructs (do NOT "clean up"):
 *  1. `goto ret0` / `goto store` with `ret0:` placed BEFORE the store block — cookbook L1344
 *     shared-ret0 goto. A trailing `return 0` makes gcc sink the merged ret0 tail past the
 *     store block (7 mismatches: BRANCH-POLARITY + swapped tail).
 *  2. `register s32 r __asm__("$2")` on the func_80189938 result + `return r`. Plain
 *     `return 0;` there emits `set v0,0; j epi`, which cross_jump (§5a) merges into the
 *     ret0 block, so the branch lands on ret0 instead of the epilogue. Pinning r to $v0
 *     makes `return r` a self-copy that dies before jump2, leaving a bare `j epi` that
 *     jump.c collapses into `beqz $v0, .L8018730C`. (A plain `s32 r` does NOT work — cse2
 *     const-folds `r` to 0 on the fall-through edge and the merge comes back.) */
s32 func_801877BC(s32 p) {

    extern s32 D_80126B9C;
    extern u8 D_801BC200[];
    s32 buf10[2];
    register s32 r __asm__("$2");   /* $v0 — see note 2 above */

    if ((*(u32 *)(p + 0xE0) & 1) == 0) {
        goto ret0;
    }
    if (*(u16 *)(p + 2) == 1) {
        goto ret0;
    }
    if (*(u16 *)(p + 2) == 0xD) {
        return 0;
    }
    if ((D_80126B9C & 2) == 0) {
        return 0;
    }
    if (0x10000 < func_8012BCCC(p)) {
        return 0;
    }
    r = func_80189938(p, 0x380);
    if (r == 0) {
        return r;
    }
    ((void (*)(s32, void *, void *))func_8012F214)(p, D_801BC200, buf10);
    if (func_801897F0(buf10, *(s16 *)(*(s32 *)(p + 0x20) + 0x12), 0x380) != 0) {
        goto store;
    }
ret0:
    return 0;
store:
    *(u16 *)(p + 2) = 0xC;
    return 1;
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018788C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80187A50);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80187BC8);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80187C28);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80187D50);


/* func_80187DB0 — line-of-sight / collision probe.
 *
 * Rotate the direction SVECTOR D_801BC450[dir] through the entity's matrix
 * (*(0x20) + 0x34) into a scratch SVECTOR at sp+0x10, build the segment
 * start (sp+0x18) = entity pos and end (sp+0x20) = entity pos + rotated
 * vector, then hand the pair to func_8012CEB0 / func_800132BC.
 *
 * §71 sibling-first: DEFINE_func_80169408 / DEFINE_func_8016986C in
 * src/shared/engine_core.h are the house shape for this ApplyMatrixSV +
 * SVECTOR-local family — `s16 vNN[4]` locals declared in ASCENDING stack
 * offset order (sp+0x10, sp+0x18, sp+0x20) and the entity position read as
 * `*(u16 *)(s1 + 0x6 / 0xA / 0xE)` (which is what makes the loads `lhu`).
 *
 * The target stores each of sp+0x20/0x22/0x24 TWICE — a plain copy first,
 * then the copy plus the rotated component — so the source assigns the
 * position, then `+=` the delta as separate statements (the local's address
 * is taken, so gcc-2.7.2 cannot kill the first store).
 */

extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern s32 func_8012CEB0(void *a0, void *a1, s32 a2);
extern s32 func_800132BC(void *a0, void *a1);

s32 func_80187DB0(s32 a0, s32 a1) {

    extern s16 D_801BC450[][4];
    extern s32 D_801E16A8;
    s32 s0 = a0;
    s16 v10[4];   /* sp+0x10 SVECTOR — ApplyMatrixSV out */
    s16 v18[4];   /* sp+0x18 SVECTOR — segment start */
    s16 v20[4];   /* sp+0x20 SVECTOR — segment end */
    s32 r;

    ApplyMatrixSV((void *)(*(s32 *)(s0 + 0x20) + 0x34), D_801BC450[a1], v10);
    v18[0] = *(u16 *)(s0 + 0x6);
    v18[1] = *(u16 *)(s0 + 0xA);
    v18[2] = *(u16 *)(s0 + 0xE);
    v20[0] = *(u16 *)(s0 + 0x6);
    v20[1] = *(u16 *)(s0 + 0xA);
    v20[2] = *(u16 *)(s0 + 0xE);
    v20[0] = v20[0] + v10[0];
    v20[1] = v20[1] + v10[1];
    v20[2] = v20[2] + v10[2];
    r = func_8012CEB0(v18, v20, 0);
    D_801E16A8 = func_800132BC(v18, v20);
    return r != 0x2000;
}



extern void (*D_801BC490[])(void);

void func_80187E90(void *a0) {
    D_801BC490[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80187ECC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80188058);


extern void func_8012C218(s32);
extern void func_8012E8A8(u8 *a0);

/* §48-C2: lwl/lwr/swl/swr block copy == a plain struct assign of a 2-byte-aligned struct */
typedef struct { u16 a, b, c, d, e, f; } UAlign12_8018833C;
typedef struct { u16 a, b, c, d; } UAlign8_8018833C;

void func_8018833C(s32 param_1)
{
    s32 t1 = *(s32 *)(param_1 + 0x64);
    s32 pad[2];

    if (*(s16 *)(t1 + 0x36) != *(s16 *)(param_1 + 0x10A)) {
        ((void (*)(void *))func_8012C218)((void *)param_1);
        return;
    }
    {
        if ((*(u32 *)(t1 + 0xE0) & 4) != 0) {
            func_8012E8A8((u8 *)param_1);
            return;
        }
        {
            s32 a2 = *(s32 *)(*(s32 *)(t1 + 0x20) + 0x20);
            s32 a3 = param_1 + 0xFC;

            if (a2 != 0) {
                if ((a2 & 0x1000000) != 0) {
                    s32 a1 = a2 & 0xFEFFFFFF;
                    register u32 v0 __asm__("$2");
                    u32 a0;
                    u32 v1a;
                    u32 v1b;
                    u32 v0b;
                    u32 v1;

                    *(u16 *)(param_1 + 0x102) = *(u16 *)(a1 + 0x66);

                    v0 = *(u32 *)(a1 + 0x60);
                    a0 = *(u8 *)(a1 + 0x61);
                    v1a = (v0 & 0xF) << 8;
                    a0 = a0 | v1a;
                    v1b = ((s32)v0 >> 16) & 0xFF;
                    v0b = (v0 & 0xF0) << 4;
                    v1 = v1b | v0b;
                    *(u16 *)(param_1 + 0x104) = (u16)a0;
                    *(u16 *)(param_1 + 0x106) = (u16)v1;

                    *(s16 *)(param_1 + 0xFC) = (s8)*(u8 *)(a1 + 0x63);
                    *(s16 *)(param_1 + 0xFE) = (s8)*(u8 *)(a1 + 0x64);
                    *(s16 *)(param_1 + 0x100) = (s8)*(u8 *)(a1 + 0x65);
                } else {
                    *(UAlign12_8018833C *)(param_1 + 0xFC) = *(UAlign12_8018833C *)(a2 + 0x90);
                }
                *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = a3;
            }

            if ((*(u32 *)(t1 + 0xE0) & 0x80) != 0) {
                if (*(u16 *)(param_1 + 0x34) == 0) {
                    s16 sVar2 = *(u16 *)(param_1 + 0x108) + 0x40;
                    *(s16 *)(param_1 + 0x108) = sVar2;
                    if (sVar2 > 0x200) {
                        *(u16 *)(param_1 + 0x108) = 0x200;
                        *(s16 *)(param_1 + 0x34) = *(s16 *)(param_1 + 0x34) + 1;
                    }
                } else {
                    u16 uVar3 = *(u16 *)(param_1 + 0x108) - 0x80;
                    *(u16 *)(param_1 + 0x108) = uVar3;
                    if ((s16)uVar3 < 0) {
                        *(u16 *)(param_1 + 0x108) = 0;
                        *(u16 *)(param_1 + 0x34) = 0;
                        *(u32 *)(t1 + 0xE0) = *(u32 *)(t1 + 0xE0) & ~0x80;
                    }
                }
            }

            *(u16 *)(a3 + 6) = *(u16 *)(a3 + 6) + *(u16 *)(param_1 + 0x108);

            *(u32 *)(param_1 + 4) = *(u32 *)(t1 + 4);
            *(u32 *)(param_1 + 8) = *(u32 *)(t1 + 8);
            *(u32 *)(param_1 + 0xC) = *(u32 *)(t1 + 0xC);

            *(UAlign8_8018833C *)(param_1 + 0x50) = *(UAlign8_8018833C *)(t1 + 0x50);

            {
                s32 dst = *(s32 *)(param_1 + 0x20);
                s32 src = *(s32 *)(t1 + 0x20);
                *(UAlign8_8018833C *)(dst + 0x10) = *(UAlign8_8018833C *)(src + 0x10);
            }
            {
                s32 dst = *(s32 *)(param_1 + 0x20);
                s32 src = *(s32 *)(t1 + 0x20);
                *(UAlign8_8018833C *)(dst + 0x18) = *(UAlign8_8018833C *)(src + 0x18);
            }
            {
                s32 src = *(s32 *)(t1 + 0x20);
                s32 dst = *(s32 *)(param_1 + 0x20);
                *(u32 *)(dst + 4) = *(u32 *)(src + 4);
            }
            {
                s32 src = *(s32 *)(t1 + 0x20);
                s32 dst = *(s32 *)(param_1 + 0x20);
                *(u16 *)(dst + 0x2C) = *(u16 *)(src + 0x2C);
            }
        }
    }
}



extern void (*D_801BC5E8[])(void);

void func_801885F4(void *a0) {
    D_801BC5E8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80188630);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801887A0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80188808);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80188A60);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80188AC0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80188BF8);


// @class: struct
// @stuck: none — MATCH (276 ins, relocation-masked). Verified BOTH standalone (match_one) and
//          spliced into src/ov_SC06_018/ov_SC06_018_jr_8017C24C.c (whole-TU cc1 -O2 clean,
//          masked structured_diff 0/276).
// Keys: (1) the first func_8012C218 call gets a NOP delay slot because reload_cse_regs deletes the
//           redundant `move a0,s1` -- $a0 still holds the incoming param on the fall-through path
//           (no CODE_LABEL between the prologue and the jal). The second call site is behind a
//           label, so the move survives. Source is the natural `((void (*)(void *))func_8012C218)((void *)param_1)` at
//           BOTH sites -- do NOT write a zero-arg call (it also breaks in-TU: the composite type
//           from the earlier file-scope `extern void ((void (*)(void *))func_8012C218)(void *a0);` rejects 0 args).
//       (2) case 0's guard is an `||` with an early return -- that is what puts `beqz -> fail` then
//           `beq -> ok` (an `&&` would emit `bne -> fail`).
//       (3) `register s32 sVar2 __asm__("$2")` holds the p+0x34 reload in cases 1/2 so the two arms
//           cross-jump into the shared .L80188928 tail.
//       (4) `__asm__ __volatile__("")` after the func_8012C658 arm forces the `lw v1,0x1C(s1)`
//           reload before the cross-jumped `li v0,9` (§21 zero-byte re-tie).
//       (5) `-((iVar3 << 0x10) / 0x22)` reproduces the 0x78787879/sra-4 magic-divide by 34 + negu.
//       (6) `*p * 0xc` then `>>4` with the manual `if (x<0) x+=0xf` is the /16 rounding form.

extern void func_8012C218(s32);
extern void func_801898EC(s32, void*, void*, s32);
extern s32  func_80013328(s32 a0, s32 a1);
extern void func_8012B14C(s32 a0, s32 a1);
extern void func_8012CC64(s32 a0, s32 a1);   /* fleet-canonical: void; $v0 used -> cast at use */
extern s32 func_8012C658(s32, s32, s32);
extern s32  func_80143B6C(s32 a0, s32 a1);   /* fleet-canonical */
extern s32  func_8012BEE8(s32 a0);
extern void func_80016714(void*, s32);
extern void func_8018956C(s32 a0, s32 a1);


void func_80188C1C(s32 param_1) {

    extern u8 D_801D4314;
    extern u8 D_801BC588;
    extern u8 D_801BC590;
    extern u8 D_801BC580;
    extern u8 D_80126B5C;
    u16 uVar1;
    register s32 sVar2 __asm__("$2");
    s32 iVar3;
    s32 iVar4;
    s32 iVar5;
    u32 uVar4;
    s32 psVar5;
    u16 buf[8];
    s32 vec[3];

    if (0xf < *(s16 *)(param_1 + 0xA)) {
        ((void (*)(void *))func_8012C218)((void *)param_1);
        return;
    }
    uVar1 = *(u16 *)(param_1 + 0x34);
    switch (uVar1) {
    case 0:
        psVar5 = *(s32 *)(param_1 + 0x64);
        if ((*(u16 *)psVar5 == 0) ||
            (*(s32 *)(psVar5 + 0x90) != (s32)&D_801D4314)) {
            ((void (*)(void *))func_8012C218)((void *)param_1);
            return;
        }
        if (*(s32 *)(psVar5 + 0x94) < 0x11) {
            ((void (*)(void *, void *, void *, s32))func_801898EC)((void *)psVar5, (void *)&D_801BC588, buf, 5);
            *(s16 *)(param_1 + 6) = buf[0];
            *(s16 *)(param_1 + 0xA) = buf[1];
            *(s16 *)(param_1 + 0xE) = buf[2];
            return;
        }
        ((void (*)(void *, void *, void *, s32))func_801898EC)((void *)psVar5, (void *)&D_801BC590, buf, 4);
        ((void (*)(void *, void *, void *, s32))func_801898EC)((void *)psVar5, (void *)&D_801BC590, &buf[4], 5);
        *(s16 *)(param_1 + 6) =
            (s16)((*(s16 *)&buf[0] + *(s16 *)&buf[4]) >> 1);
        *(s16 *)(param_1 + 0xA) =
            (s16)((*(s16 *)&buf[1] + *(s16 *)&buf[5]) >> 1);
        *(s16 *)(param_1 + 0xE) =
            (s16)((*(s16 *)&buf[2] + *(s16 *)&buf[6]) >> 1);
        if (*(s32 *)(psVar5 + 0x94) != 0x19) {
            return;
        }
        *(u16 *)(param_1 + 0x34) = *(u16 *)(param_1 + 0x34) + 1;
        vec[0] = 0;
        vec[1] = 0xfff40000;
        iVar3 = func_80013328((s32)&D_80126B5C, param_1 + 4);
        vec[2] = -((iVar3 << 0x10) / 0x22);
        func_8012B14C(param_1, (s32)vec);
        *(s32 *)(param_1 + 0x48) = 0xc000;
        return;
    case 1:
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + 0x80;
        iVar3 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801BC580);
        if (iVar3 == 0) {
            return;
        }
        sVar2 = *(u16 *)(param_1 + 0x34);
        *(s32 *)(param_1 + 0x1c) = 0;
        *(u16 *)(param_1 + 0x34) = sVar2 + 1;
        return;
    case 2:
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
            *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + 0x40;
        uVar4 = ((s32 (*)(s32, s32))func_8012CC64)(param_1, (s32)&D_801BC580);
        if ((uVar4 & 0x2000) == 0) {
            return;
        }
        iVar4 = *(s32 *)(param_1 + 0x1c) + 1;
        *(s32 *)(param_1 + 0x1c) = iVar4;
        if (iVar4 >= 4) {
            sVar2 = *(u16 *)(param_1 + 0x34);
            *(s32 *)(param_1 + 0x1c) = 0x1e;
            *(u16 *)(param_1 + 0x34) = sVar2 + 1;
            return;
        }
        iVar3 = *(s32 *)(param_1 + 0x10) * 0xc;
        if (iVar3 < 0) {
            iVar3 = iVar3 + 0xf;
        }
        *(s32 *)(param_1 + 0x10) = iVar3 >> 4;
        iVar5 = *(s32 *)(param_1 + 0x18) * 0xc;
        if (iVar5 < 0) {
            iVar5 = iVar5 + 0xf;
        }
        *(s32 *)(param_1 + 0x18) = iVar5 >> 4;
        *(s32 *)(param_1 + 0x14) = -(0x80000 / *(s32 *)(param_1 + 0x1c));
        func_80143B6C(param_1, 1);
        return;
    case 3:
        uVar4 = *(u32 *)(param_1 + 0x1c);
        if ((uVar4 - 0xe < 0xb) && ((uVar4 & 1) == 0)) {
            ((void (*)(s32, s32, s32))func_8012C658)(0x2a8, (s32)*(s16 *)(param_1 + 0x104), param_1);
            *(u16 *)(param_1 + 0x104) = *(u16 *)(param_1 + 0x104) + 1;
            __asm__ __volatile__("");
            uVar4 = *(u32 *)(param_1 + 0x1c);
        }
        if (uVar4 == 9) {
            *(u32 *)(*(s32 *)(param_1 + 0xcc) + 4) =
                *(u32 *)(*(s32 *)(param_1 + 0xcc) + 4) & 0x7fffffff;
            *(s16 *)(*(s32 *)(param_1 + 0xcc) + 8) = *(u16 *)(param_1 + 6);
            *(s16 *)(*(s32 *)(param_1 + 0xcc) + 0xa) =
                *(u16 *)(param_1 + 0xa) - 0x24;
            *(s16 *)(*(s32 *)(param_1 + 0xcc) + 0xc) = *(u16 *)(param_1 + 0xe);
        }
        if (*(s32 *)(param_1 + 0x1c) - 4U < 6) {
            *(s16 *)(*(s32 *)(param_1 + 0xcc) + 0x18) =
                *(u16 *)(*(s32 *)(param_1 + 0xcc) + 0x18) + 0x200;
            *(s16 *)(*(s32 *)(param_1 + 0xcc) + 0x1a) =
                *(u16 *)(*(s32 *)(param_1 + 0xcc) + 0x1a) + 0x200;
        }
        iVar3 = func_8012BEE8(param_1);
        if (iVar3 != 1) {
            return;
        }
        ((void (*)(s32, s32))func_80016714)(*(s32 *)(param_1 + 0xcc), 0x38);
        *(s16 *)(param_1 + 2) = 9;
        func_8018956C(param_1, 0);
        return;
    }
    return;
}



extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern void func_8012B260(u8 *a0);

void func_8018906C(s32 p) {
    s32 g10[4];   /* sp+0x10 */
    u16 g20[4];   /* sp+0x20 */
    s32 buf28[8]; /* sp+0x28 */
    u16 v;

    g10[2] = 0xFFF00000;
    g10[1] = 0;
    g10[0] = 0;
    g20[0] = 0x10;
    v = *(u16 *)(*(s32 *)(*(s32 *)(p + 0x64) + 0x20) + 0x12) +
        *(u16 *)(p + 0xFC);
    g20[1] = v;
    *(u16 *)(p + 0xFE) = v;
    g20[2] = 0;
    ((void (*)(void *, void *))func_80049CAC)(g20, buf28);
    ((void (*)(void *, void *, s32))func_800484EC)(buf28, g10, p + 0x10);
    *(u16 *)(p + 2) = 8;
    *(s32 *)(p + 0x1C) = 0x40;
    ((void (*)(s32))func_8012B260)(p);
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80189108);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801892C0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801892FC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018937C);


extern s32 func_80132EF4(s32 a0, s32 a1);
extern void func_8012B0B4(unsigned int *p, int a1, int a2);
extern void func_80049CAC(s32, s32);
extern void func_800484EC(s32, s32, s32);
extern s32 func_8012C658(s32, s32, s32);
extern void func_8018A3CC(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018956C(s32 a0, s32 a1) {
    s32 buf10[8];    /* sp+0x10 (0x20) - func_80049CAC out / func_800484EC in */
    s32 g40[4];      /* sp+0x30, only [0..2] used - func_800484EC vec3 arg */
    u16 g30[4];      /* sp+0x40, only [0..2] used - func_80049CAC vec3 arg */
    unsigned int buf48[2]; /* sp+0x48 (8) - func_8012B0B4 output */
    unsigned int *p48;
    s32 i;
    s32 baseY;
    s32 e;
    u32 uVar;
    s32 scratch;
    s32 tmp;

    i = 0;
    p48 = buf48;
    baseY = 0x100;
    do {
        e = func_80132EF4(a0, 0x23);
        if (e != 0) {
            *(s16 *)(e + 0x34) = rand() % 0x4000 + 0x1000;
            *(u16 *)(*(s32 *)(e + 0x20) + 0x2c) = 0xc008;

            func_8012B0B4(p48, rand() % 0x1000, rand() % 0x58);

            tmp = *(s32 *)buf48;
            *(s16 *)(e + 6) = *(s16 *)(e + 6) + (s16)tmp;
            *(s16 *)(e + 0xe) = *(s16 *)(e + 0xe) + (s16)(tmp >> 16);

            tmp = rand();
            scratch = tmp % 0x80;
            uVar = rand();
            g30[0] = (uVar & 1) == 0 ? -scratch + 0x400 : scratch + 0x400;

            scratch = rand() % 0xc0;
            uVar = rand();
            g30[1] = (uVar & 1) != 0 ? baseY + scratch : baseY - scratch;

            g30[2] = 0;
            g40[1] = 0;
            g40[0] = 0;
            g40[2] = (rand() % 4 + 3) << 16;

            ((void (*)(void *, void *))func_80049CAC)(g30, buf10);
            ((void (*)(void *, void *, s32))func_800484EC)(buf10, g40, e + 0x10);
        }
        i++;
        baseY += 0x200;
    } while (i < 8);

    e = func_80132EF4(a0, 0x23);
    if (e != 0) {
        *(u16 *)(e + 0x34) = 0x7ff1;
        *(u16 *)(*(s32 *)(e + 0x20) + 0x2c) = 0xc004;
        *(s32 *)(e + 0x14) = 0xfffb0000;
    }

    i = 0;
    do {
        func_8012C658(0x29d, (u16)a1, a0);
        i++;
    } while (i < 4);

    func_8018A3CC(a0, 0x95e);
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801897F0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80189888);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801898EC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80189938);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_801899B8);


extern void (*D_801BC61C[])(void);

void func_80189A20(void *a0) {
    D_801BC61C[*(u16 *)((s32)a0 + 0x2)]();
}




extern s32 rand(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(s32 a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012B2CC(s32 a0);
extern void func_8012B178(s32 a0, s32 a1);

void func_80189A5C(s32 param_1) {

    extern u8 D_801BC624[];
    s32 unused[2]; /* dead 8-byte local — frame padding (cookbook idiom 6) */
    s32 obj;
    s16 raw;
    s32 r;
    s32 sgn;
    s32 v;
    u8 *tbl;
    s16 *p;
    s32 q;
    s32 w;

    obj = ((s32 (*)(void))func_8012C1B8)();
    if (obj == 0) {
        func_8012CAE4(param_1);
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
    *(s32 *)(param_1 + 0x48) = 0xC000;
    *(u16 *)(param_1 + 0xA) = *(u16 *)(param_1 + 0xA) - 0x19;
    func_8012B2CC(param_1);
    func_8012B178(param_1, -0xC0000 - ((r % 8) << 16));
    *(s32 *)(param_1 + 0x1C) = 0x3C;
    *(s16 *)(param_1 + 0xFE) = rand() & 0xF0;
    *(s16 *)(param_1 + 0x100) = rand() & 0x1F0;
    *(s16 *)(param_1 + 0x102) = rand() & 0x30;
    tbl = &D_801BC624[(*(u16 *)(param_1 + 0x70) & 0xF) * 4];

    p = (s16 *)(param_1 + 0xDC);

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q - 0x18;
    } else {
        w = q - 0x18;
    }
    p[0] = w;
    p[1] = 0;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q - 0x18;
    } else {
        w = q - 0x18;
    }
    p[2] = w;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[4] = w;
    p[5] = 0;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q - 0x18;
    } else {
        w = q - 0x18;
    }
    p[6] = w;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q - 0x18;
    } else {
        w = q - 0x18;
    }
    p[8] = w;
    p[9] = 0;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[10] = w;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[12] = w;
    p[13] = 0;

    q = rand() % 12;
    if ((rand() & 1) == 0) {
        w = -q + 0x18;
    } else {
        w = q + 0x18;
    }
    p[14] = w;

    *((u8 *)p + 0x20) = tbl[0];
    *((u8 *)p + 0x21) = tbl[1];
    *((u8 *)p + 0x22) = tbl[2];
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}



extern s32  func_8012CBF4(s32 a0);
extern s32  func_8012BEE8(s32 a0);
extern void func_8012C218(s32);
extern void func_80017274(s32 a0, s32 a1);

void func_80189EC0(s32 param_1) {
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x10) + *(u16 *)(param_1 + 0xFE);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x12) + *(u16 *)(param_1 + 0x100);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) =
        *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x14) + *(u16 *)(param_1 + 0x102);

    if (func_8012CBF4(param_1) != 0 || func_8012BEE8(param_1) != 0) {
        ((void (*)(void *))func_8012C218)((void *)param_1);
    } else {
        func_80017274(param_1 + 0xDC, *(s32 *)(param_1 + 0x20) + 0x34);
    }
}



extern void (*D_801BC63C[])(void);

void func_80189F64(void *a0) {
    D_801BC63C[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_80189FA0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018A194);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018A2D0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018A3CC);


extern void (*D_801BC648[])(void);

void func_8018A538(void *a0) {
    D_801BC648[*(u16 *)((s32)a0 + 0x2)]();
}



extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

void func_8018A574(s32 param_1) {

    extern u8 D_800D387C[];
    extern u8 D_800D3888[];
    s32 t;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 0x20) = (u32)&D_800D387C;

    *(u32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x50000000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x27) = 0x9c;

    t = *(s32 *)(param_1 + 0x20);
    *(u16 *)(t + 0x1a) = 0x2000;
    *(u16 *)(t + 0x18) = 0x2000;

    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x24) = 0xff;
    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x25) = 0;
    *(u8 *)(*(s32 *)(param_1 + 0x20) + 0x26) = 0;

    func_80128EA8(*(s32 *)(param_1 + 0x20), param_1 + 0x24, (s32)&D_800D3888);

    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}



extern void func_8012931C(s32 a0);
extern s32 func_80128ED8(void *a0, void *a1);
extern void func_801292C8(u8*);

void func_8018A624(s32 param_1) {
    s32 q;
    u8 a;
    u8 b;
    u16 h;

    q = *(s32 *)(param_1 + 0x20);

    a = *(u8 *)(q + 0x24) - 0x20;
    *(u8 *)(q + 0x24) = a;
    if (a < 0x80) {
        *(u8 *)(q + 0x24) = 0x80;
    }

    b = *(u8 *)(q + 0x25) + 0x20;
    *(u8 *)(q + 0x25) = b;
    if (b > 0x80) {
        *(u8 *)(q + 0x25) = 0x80;
    }

    h = *(u16 *)(q + 0x1A) + 0x400;
    *(u8 *)(q + 0x26) = *(u8 *)(q + 0x25);
    *(u16 *)(q + 0x1A) = h;
    *(u16 *)(q + 0x18) = h;

    func_8012931C(param_1);

    if (func_80128ED8((void *)q, (void *)(param_1 + 0x24)) != 0) {
        ((void (*)(s32))func_801292C8)(param_1);
    }
}



extern s32 func_8012C588(s32 a0, s32 a1);

s32 func_8018A6DC(s32 a0, s32 a1) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801E17F0;
    D_801E17F0 = a1;
    return func_8012C588(0x85, a0);
}


extern s32 func_80017DC4(void *a0, void *a1);
extern void func_80017E68(void *a0, void *a1);
extern void func_800D20C0(void *a0, void *a1, s32 a2);
extern void func_800D23D0(void *a0);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012C218(s32);
extern void func_8012F14C(s32);
extern s32 func_80134510(s32 arg);

// @class: regalloc-order
// @stuck: none — MATCH (145/145 ins, match_one confirmed)




s32 func_8018A70C(s32 param_1) {

    extern u8 D_801152A8[];
    extern M2C_UNK D_8018FB1C;
    extern s32 D_801E17F0;
    extern s32 func_8012C354(s32, void*);
    extern void RotMatrixZ(s32, void *);
    extern void MulMatrix0(s32, void *, s32);
    extern s32 D_801D4450;
    extern char * D_801D4484;
    extern char D_801E17D0[];

    S8_80184F08 s60;
    SVECTOR_80184F08 sStack_58;
    S8_80184F08 s50;
    int auStack_48[8];
    s32 iVar5, iVar8;
    char *puVar2, *puVar4;
    u16 uVar3;

    if (((s32 (*)(s32, void *))func_8012C354)(param_1, &D_801D4450) == 0) {
        ((void (*)(s32))func_8012C218)(param_1);
    }
    ((void(*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_8018FB1C));
    iVar5 = *(s32 *)(param_1 + 0x20);
    *(s16 *)(param_1 + 0x70) = 0x80;
    *(s32 *)(iVar5 + 4) |= 0x50000040;
    *(u16 *)(iVar5 + 0x2c) |= 1;
    iVar8 = *(s32 *)(*(s32 *)(param_1 + 0x64) + 0x20) + 0x34;
    ((void (*)(s32, s32, void *))func_8012F14C)(iVar8, D_801E17F0, &s60);
    s50 = s60;
    sStack_58.vz = 0x1800;
    sStack_58.vy = 0x1800;
    sStack_58.vx = 0x1800;
    ((void (*)(void *, void *))func_80017DC4)(&sStack_58, auStack_48);
    RotMatrixZ(rand() & 0xfff, auStack_48);
    MulMatrix0(iVar8, auStack_48, iVar5 + 0x34);
    ((void (*)(void *, s32))func_80017E68)(&s50, iVar5 + 0x34);

    /* pool-alloc: gcc routes the loaded pointer through a caller-saved reg ($v0)
       before the callee-saved home ($s1) — pin it to reproduce the extra move. */
    {
        register char *tmp __asm__("$2");
        tmp = D_801D4484;
        puVar2 = tmp;
    }
    puVar4 = puVar2 + 0x20;
    D_801D4484 = puVar4;
    *(char **)(param_1 + 0xcc) = puVar2;
    if (D_801E17D0 < puVar4) {
        D_801D4484 = D_801E17D0 - 0x120;
    }
    func_800D20C0(&s60, &sStack_58, 7);
    func_800D23D0(&sStack_58);
    ((void(*)(void *, void *))RotMatrixYXZ)(&sStack_58, puVar2);
    ((void (*)(void *, s32))func_80017E68)(&s60, (s32)puVar2);

    uVar3 = *(u16 *)((char *)&s50 + 2);
    if (((s32 (*)(void *))func_80134510)(&s50) != 0 &&
        (s32)(s16)uVar3 - (s32)*(s16 *)((char *)&s50 + 2) < 0x80) {
        *(s16 *)((char *)&s50 + 2) = *(s16 *)((char *)&s50 + 2) - 4;
        {
            register char *tmp __asm__("$3");
            tmp = D_801D4484;
            puVar2 = tmp;
        }
        puVar4 = puVar2 + 0x20;
        D_801D4484 = puVar4;
        *(char **)(param_1 + 0xd0) = puVar2;
        if (D_801E17D0 < puVar4) {
            D_801D4484 = D_801E17D0 - 0x120;
        }
        func_800D23D0(&(*(s32 *)&D_801152A8));
        ((void(*)(void *, void *))RotMatrixYXZ)(&(*(s32 *)&D_801152A8), puVar2);
        ((void (*)(void *, s32))func_80017E68)(&s50, (s32)puVar2);
    }
    *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
}


extern s32 func_80017758(void *a0, void *a1);
extern void func_8012C218(s32);
//   (3) counter is `short i` do-while (keeps the `addu $s2,$v0,$0` raw-copy + sll16/sra16 compare);
//   (4) gcc-2.7.2 loads s8/s16 via lbu/lhu+shift-extend (not lb/lh) so `signed char *p; *(s16*)buf=*p++`
//   emits lbu;sll24;sra24;sh; (5) else-branch zero-byte asm barrier forces `addu $a0,$s1,$0` (else gcc
//   reuses the still-live incoming $a0 with a nop delay slot).

s32 func_8018A950(s32 param_1) {

    extern signed char D_801D443C[];
    register int self __asm__("$17") = ((int)param_1);
    int iVar6;
    int iVar1;
    unsigned char buf[0x34];
    signed char *p;
    short i;
    int dest;
    int td;
    unsigned short t;

    iVar1 = *(int *)(self + 0x1c);
    iVar6 = *(int *)(self + 0x20);
    *(int *)(self + 0x1c) = iVar1 + 1;
    if (iVar1 < 2) {
        p = D_801D443C;
        i = 0;
        dest = *(int *)(self + 0xcc);
        t = *(unsigned short *)(self + 0x70);
        *(short *)(buf + 0x0c) = 0;
        *(short *)(buf + 0x0a) = 0;
        *(short *)(buf + 0x08) = 0;
        *(short *)(buf + 0x1c) = 0;
        *(short *)(buf + 0x14) = 0;
        *(short *)(buf + 0x04) = 0;
        buf[0x22] = 0;
        buf[0x21] = 0;
        buf[0x20] = 0;
        buf[0x2a] = 0;
        buf[0x29] = 0;
        buf[0x28] = 0;
        buf[0x2e] = 0;
        buf[0x2d] = 0;
        buf[0x2c] = 0;
        *(int *)(buf + 0x30) = 0x50000000;
        buf[0x25] = t;
        buf[0x26] = t;
        buf[0x24] = t;
        do {
            *(short *)(buf + 0x00) = *p++;
            *(short *)(buf + 0x02) = *p++;
            *(short *)(buf + 0x10) = *p++;
            *(short *)(buf + 0x12) = *p++;
            *(short *)(buf + 0x18) = *p++;
            *(short *)(buf + 0x1a) = *p--;
            func_80017758(buf, (void *)dest);
            i++;
        } while (i < 4);

        td = *(int *)(self + 0xd0);
        if (td != 0) {
            dest = td;
            p = D_801D443C;
            i = 0;
            t = *(unsigned short *)(self + 0x70);
            *(short *)(buf + 0x0c) = 0;
            *(short *)(buf + 0x0a) = 0;
            *(short *)(buf + 0x08) = 0;
            *(short *)(buf + 0x1c) = 0;
            *(short *)(buf + 0x14) = 0;
            *(short *)(buf + 0x04) = 0;
            buf[0x22] = 0;
            buf[0x21] = 0;
            buf[0x20] = 0;
            buf[0x2a] = 0;
            buf[0x29] = 0;
            buf[0x28] = 0;
            buf[0x2e] = 0;
            buf[0x2d] = 0;
            buf[0x2c] = 0;
            *(int *)(buf + 0x30) = 0x50000000;
            buf[0x25] = t;
            buf[0x26] = t;
            buf[0x24] = t;
            do {
                *(short *)(buf + 0x00) = *p++;
                *(short *)(buf + 0x02) = *p++;
                *(short *)(buf + 0x10) = *p++;
                *(short *)(buf + 0x12) = *p++;
                *(short *)(buf + 0x18) = *p++;
                *(short *)(buf + 0x1a) = *p--;
                func_80017758(buf, (void *)dest);
                i++;
            } while (i < 4);
        }
        *(short *)(self + 0x70) = *(short *)(self + 0x70) >> 1;
        *(unsigned short *)(iVar6 + 0x2c) |= 1;
    } else {
        __asm__ __volatile__("" : "=r"(self) : "0"(self));
        ((void (*)(void *))func_8012C218)((void *)self);
    }
}



extern void (*D_801D4488[])(void);

void func_8018ABF0(void *a0) {
    D_801D4488[*(u16 *)((s32)a0 + 0x2)]();
}




// @class: schedule
// @stuck: none — MATCH (132 ins, match_one). Levers: (1) block2 statement order — compute sv1.vz (with the *(p+0xe) load) right after the 2nd call so gcc hoists that load into $v1, forcing the sv2.vx=sv1.vx copy through $a3, which globally pushes every `func*param>>12` product from $a3 to $t0; (2) sv2 store order vx-before-vy; (3) SHARED return-0 join via gotos placed BEFORE the copy block (ret0: before docopy:) — this blocks gcc's conditional-jump-over-jump inversion + return-threading, so the copy block falls through to the epilogue with v0=1 preset in the beqz delay slot (drops the extra `li v0,1`).


extern int func_8004787C(int);
extern int func_80047948(int);
extern s32 func_80133784(s32, void*, s32);

int func_8018AC2C(int param_1, short param_2)
{
    int iVar1;
    unsigned int uVar2;
    int iVar3;
    SVECTOR sv1;
    SVECTOR sv2;

    if (*(int *)(param_1 + 0xdc) != 0) goto ret0;
    sv1.vx = *(short *)(param_1 + 6);
    sv1.vy = *(short *)(param_1 + 0xa) + -0x20;
    sv1.vz = *(short *)(param_1 + 0xe);
    iVar1 = func_8004787C(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
    iVar3 = (int)param_2;
    sv2.vy = sv1.vy;
    sv2.vx = sv1.vx - (short)(iVar1 * iVar3 >> 0xc);
    iVar1 = func_80047948(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
    sv2.vz = sv1.vz - (short)(iVar1 * iVar3 >> 0xc);
    uVar2 = ((int (*)(int, SVECTOR *, SVECTOR *))func_80133784)(1, &sv1, &sv2);
    if ((uVar2 & 0x8000) != 0) {
        iVar1 = func_8004787C(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
        *(short *)(param_1 + 6) = sv2.vx + (short)(iVar1 * iVar3 >> 0xc);
        iVar1 = func_80047948(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
        *(short *)(param_1 + 0xe) = sv2.vz + (short)(iVar1 * iVar3 >> 0xc);
        return 1;
    }
    iVar1 = func_8004787C(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
    sv1.vx = *(short *)(param_1 + 6) - (short)(iVar1 * iVar3 >> 0xc);
    sv1.vy = *(short *)(param_1 + 0xa) + -0x10;
    iVar1 = func_80047948(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) & 0xfff);
    sv1.vz = *(short *)(param_1 + 0xe) - (short)(iVar1 * iVar3 >> 0xc);
    sv2.vx = sv1.vx;
    sv2.vy = sv1.vy + 0x20;
    sv2.vz = sv1.vz;
    uVar2 = ((int (*)(int, SVECTOR *, SVECTOR *))func_80133784)(1, &sv1, &sv2);
    if ((uVar2 & 0x6000) == 0) goto docopy;
ret0:
    return 0;
docopy:
    *(int *)(param_1 + 4) = *(int *)(param_1 + 0x38);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 0x3c);
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0x40);
    return 1;
}




/* func_8018AE3C — ov_SC06_008 / ov_SC06_008_jr_8017C294
 *
 * Two-arm actor tick keyed on the s16 countdown at actor+0xFC:
 *   arm A (counter == 0, the FALL-THROUGH / longer block): three func_8012C658
 *     spawns with offset pokes, a sound cue, two child-actor state pokes, an
 *     8-iteration 0x281 particle burst, then the RTP positional-sound block
 *     (the byte-proven RTP_SND shape from ov_SC03_099_jr_8017BEBC.c:5406).
 *   arm B (counter != 0): a func_8012913C(0x23) spawn scattered around the
 *     actor, VectorNormalSS toward D_801151D4->{0x5C,0x60,0x64}, sound 0xAF8.
 *
 * Declarations copied VERBATIM from the TU (one-pass grep, D2):
 *   D_801151D4      src/ov_SC06_008/ov_SC06_008_jr_8017C294.c:323
 *   rand            :956
 *   VectorNormalSS  :1849
 *   func_8012C658   :2523
 *   func_8012C588   :3767
 *   func_8012C218   :3782
 *   func_8002D4C8   :59
 *   func_8004914C   :2645
 *   func_800491AC   :2646
 *   func_8012913C   :4356  (non-prototype form, BELOW the splice point)
 *   func_8002AC00   :5447  (block-scope extern only)
 * RotTransPers / D_800AF648 / func_8002A04C are not in this TU -> fleet-dominant forms.
 */

extern s32  rand(void);
extern s32  VectorNormalSS(void *a0, void *a1);
extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002A04C(s32 a0);
extern void func_8002AC00(s32 a0);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern u8  *func_8012913C();

void func_8018AE3C(s32 a0)
{

    extern s32  D_801151D4;
    extern u8 D_800AF648;

    /* L5: slot offsets are exact only through ONE struct — plain array locals
       get 8-byte-rounded slots and pushed z/flag to 0x28/0x2C (measured). */
    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 rv[4];   /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;

    s32 g;
    s32 s0;
    s32 i;

    g = D_801151D4;

    if (*(s16 *)(a0 + 0xFC) == 0) {
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) - 5;
        }
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(u16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) + 5;
        }
        s0 = func_8012C658(0x32, 2, a0);
        if (s0 != 0) {
            *(u16 *)(s0 + 0xA)  = *(u16 *)(s0 + 0xA)  - 0x20;
            *(u16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) + 8;
        }
        func_8002AC00(0x22);

        s0 = *(s32 *)(a0 + 0xCC);
        *(s16 *)(s0 + 0x2)  = 2;
        *(s16 *)(s0 + 0xFC) = 1;
        s0 = *(s32 *)(a0 + 0xD0);
        *(s16 *)(s0 + 0x2)  = 2;
        *(s16 *)(s0 + 0xFC) = 1;

        for (i = 0; i < 8; i++) {
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(u16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x30;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }

        L.rv[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.rv[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.rv[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.rv, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                      && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
            s32 x = (s16)L.sxy[0];
            s32 ax;

            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xF0 - ax) * 0x7F) / 0xF0;
            __asm__("" : "=r"(ax) : "0"(ax));
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            {
                s32 flg = 0x3000;
                func_8002D4C8(0x961, ((ax | flg) | x) & 0xFFFF);
            }
        }
        func_8002A04C(a0);
        ((void (*)(void *))func_8012C218)((void *)a0);
    } else {
        s0 = (s32)func_8012913C(0x23);
        if (s0 != 0) {
            *(s16 *)(s0 + 0x6) = *(u16 *)(a0 + 0x6) + (rand() & 0x7F) - 0x40;
            *(s16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA) + (rand() & 0x7F) - 0xE0;
            {
                s32 r = rand();
                s32 t = *(u16 *)(a0 + 0xE);
                *(s16 *)(s0 + 0x34) = 0x1800;
                *(s32 *)(s0 + 0x18) = 0;
                *(s32 *)(s0 + 0x14) = 0;
                *(s32 *)(s0 + 0x10) = 0;
                *(s16 *)(s0 + 0xE) = t + (r & 0x7F) - 0x40;
            }
            L.nv[0] = *(s32 *)(g + 0x5C) - *(u16 *)(s0 + 0x6);
            L.nv[1] = *(s32 *)(g + 0x60) - *(u16 *)(s0 + 0xA);
            L.nv[2] = *(s32 *)(g + 0x64) - *(u16 *)(s0 + 0xE);
            VectorNormalSS(L.nv, L.nv);
            *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)L.nv[0] >> 6);
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)L.nv[1] >> 6);
            *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)L.nv[2] >> 6);
            *(s16 *)(s0 + 0x34) = 0x3000;
            func_8002D4C8(0xAF8, 0);
        }
        *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) - 1;
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018B240);


// @class: schedule
// @stuck: none — MATCH; success-block placed last via `goto big` (bnez forward into epilogue), single cae4 merge kept

extern int  func_8012C354();
extern void func_800599B8();
extern void func_8001C214();
extern void func_80143970();
extern void func_8012B030();
extern void func_8012A828();
extern void func_8012B23C();
extern int  func_8012C658();
extern void func_8012C218();
extern void func_8012CAE4();


void func_8018B3B4(int param_1) {

    extern u8 D_801D4B9C[];
    extern u8 D_801D4AE0[];
    extern u8 D_801D4AA0[];
    extern u8 D_801D4AE8[];
    extern u8 D_801D4AC0[];
    extern u8 D_801D8E08[];
    extern u8 D_801DC0B8[];
    extern u8 D_801D4BDC[];
    extern u8 D_801DBF20[];
    extern u8 D_801DBFA8[];
    extern u8 D_801DC030[];
    int iVar1;

    iVar1 = func_8012C354(param_1, D_801D4B9C);
    if (iVar1 != 0) {
        if (*(short *)(param_1 + 0x70) != 0) {
            func_800599B8(D_801D4AE0, D_801D4AA0);
            func_800599B8(D_801D4AE8, D_801D4AC0);
            func_8001C214(*(int *)(param_1 + 0x20), D_801D8E08);
        }
        *(u8 *)(param_1 + 0xc0) = 1;
        *(int *)(param_1 + 0xb4) = 0xffffdfde;
        func_80143970(param_1);
        func_8012B030(param_1);
        *(short *)(param_1 + 0xae) = 0x2100;
        func_8012A828(param_1, D_801DC0B8);
        *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
        func_8012B23C(param_1);
        *(u32 *)(param_1 + 0xc4) = *(u32 *)(param_1 + 0xc4) | 2;
        iVar1 = func_8012C658(0x26f, (int)*(short *)(param_1 + 0x70), param_1);
        if (iVar1 != 0) {
            *(int *)(param_1 + 0xcc) = iVar1;
            iVar1 = func_8012C658(0x270, (int)*(short *)(param_1 + 0x70), param_1);
            if (iVar1 != 0) goto big;
            func_8012C218(*(int *)(param_1 + 0xcc));
        }
        func_8012CAE4(param_1);
    }
    return;
big:
    *(int *)(param_1 + 0xd0) = iVar1;
    *(u32 *)(param_1 + 0xbc) = (u32)D_801D4BDC;
    *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) =
        *(u16 *)(*(int *)(param_1 + 0x20) + 0x2c) | 0x10;
    *(short *)(*(int *)(param_1 + 0x20) + 0x18) = 0x2400;
    *(short *)(*(int *)(param_1 + 0x20) + 0x1a) = 0x2400;
    *(short *)(*(int *)(param_1 + 0x20) + 0x1c) = 0x2400;
    *(u16 *)(param_1 + 2) = 8;
    func_8012A828(param_1, D_801DBF20);
    func_8012A828(*(int *)(param_1 + 0xcc), D_801DBFA8);
    func_8012A828(*(int *)(param_1 + 0xd0), D_801DC030);
    return;
}



/* func_8018B564 — ov_SC06_008 / ov_SC06_008_jr_8017C294.  MATCH 163/163.
 * Family of 7 (ov_SC06_008/010/018/022/024/032/033, all 163 ins, all still in
 * nonmatchings) — §136e applies: no twin existed, so this is derived from the .s.
 * The byte-proven accumulate head (b744 nested inside b608, then two RE-LOADS of
 * *(s32*)(a0+0x20)) is copied verbatim from src/ov_SC03_099/..._jr_8017BEBC.c:5424.
 *
 * Four levers, each measured against match_one:
 *
 * 1. NO frame padding.  args_size already fills sp+0x00..0x1F, so the four saved
 *    regs land at 0x20..0x2F and the frame is 0x30 with ZERO locals.  A 16-byte
 *    dead aggregate (idiom 6, added on the first draft from a mis-derived
 *    args_size=0x10) made it 0x40 — idiom 6 only applies when the reg-save area
 *    does NOT start at args_size.
 *
 * 2. BRANCH POLARITY / BLOCK LAYOUT (§3-T4, T7).  `if (C) goto X;` followed by a
 *    `break` is REWRITTEN by jump.c's jump-around-jump inversion into
 *    `if (!C) goto break_target;` — which is the wrong polarity here.  The target
 *    wants the true arm to FALL THROUGH.  Two rewrites, both worth +0 instructions
 *    but different bytes:
 *      case 1: `if (A||B) goto st2; break;`  ->  `if (!A && !B) break; goto st2;`
 *              (TRUTH_ANDIF gives reversed branches to `next`, and the trailing
 *               `j st2` is the fall-through — exactly `beqz L600 / j L5E0`.)
 *      case 3: same shape, plus the range test written as the POSITIVE
 *              `if (r >= -0xFF && r <= 0xFF) break;` so fold_range_test's
 *              `sltiu (r+0xFF),0x1FF` branches on TRUE to the switch end and case 3
 *              falls through into st2 (saves the `j`+`nop`, 165 -> 163 ins).
 *    Case 0 keeps the plain `if (A||B) {..} else {..}` — there jump.c's inversion
 *    IS what the target has.
 *
 * 3. THE SHARED STORE BLOCK.  L801815F8/L801815FC (`li v0,1` / `sh v0,0x34`) sit
 *    AFTER st2 in the target, so they are NOT inline `else` arms (cross-jumping
 *    keeps the LAST copy, which would put them BEFORE st2).  They are explicit
 *    trailing labels inside the switch with an `ns` join variable; case 2 enters at
 *    `setstate` with ns=3, cases 0 and 3 enter at `set1`.
 *
 * 4. REGALLOC-PERM -> the $16 pin (see below).
 */

extern s32 rand(void);
extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012BE54(s32 a0);
extern int func_8018AC2C(int param_1, short param_2);

void func_8018B564(s32 a0) {

    extern u8 D_801D4BFC[];

    /* §137/K3+K5: unpinned, the a0-copy allocno (R=37/L=137, pri 13503) is
     * ranked first and first-fits $s0, pushing `tbl` to $s1 — a clean 2-reg
     * perm no source reordering can flip (pri(tbl) = 394). Pinning `tbl` to
     * $16 makes $s0 "already dirty" in find_reg pass 0: the a0 copy conflicts
     * with it and opens $s1, and case 3's `d` (which does NOT conflict with
     * `tbl`) grabs $s0 in pass 0 — exactly the target's assignment. */
    register s32 tbl __asm__("$16");
    s32 ns;

    tbl = (s32)D_801D4BFC;
    func_8012B1B4(a0, tbl);
    func_8012CBCC(a0);

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (func_8018AC2C(a0, 0x48) != 0 ||
            ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88)) >
                0x3FFFF) {
            s32 r = func_8012B608(
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88)), 8);
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
            func_8012B1B4(a0, tbl);
        } else {
            goto set1;
        }
        break;

    case 1:
        if (func_8018AC2C(a0, 0x48) == 0 &&
            ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88)) <=
                0x3FFFF) {
            break;
        }
        goto st2;

    case 2: {
        s32 r = func_8012B608(
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
            func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88)), 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }
        func_8018AC2C(a0, 0x48);
        {
            s16 c = *(s16 *)(a0 + 0x102);
            if (c == 0) {
                ns = 3;
                goto setstate;
            }
            *(s16 *)(a0 + 0x102) = c - 1;
        }
        break;

    case 3: {
        void *p88 = (void *)(a0 + 0x88);
        s32 d = ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)p88);
        if (func_8018AC2C(a0, 0x48) == 0) {
            if (d > 0x40000) {
                s32 r = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                                      func_8012B744((void *)(a0 + 4), p88), 1);
                if (r >= -0xFF && r <= 0xFF) {
                    break;
                }
            } else {
                goto set1;
            }
        }
    }
        /* fall through into st2 */
    st2:
        *(u16 *)(a0 + 0x34) = 2;
        *(u16 *)(a0 + 0x102) = (rand() & 7) + 8;
        break;

    set1:
        ns = 1;
    setstate:
        *(u16 *)(a0 + 0x34) = ns;
        break;
    }

    {
        s16 t = *(s16 *)(a0 + 0x100);
        if (t != 0) {
            *(s16 *)(a0 + 0x100) = t - 1;
        } else if (((s32(*)(s32))func_8012BE54)(a0) <= 0x24000) {
            *(s16 *)(a0 + 0x2) = 5;
            *(s16 *)(a0 + 0x100) = 0x3C;
        }
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_8004787C(s32 a0);
extern s32 func_80047948(s32 a0);
extern void func_8004914C();
extern void func_800491AC();
extern u8 *func_8012913C(s32 a0);
extern void func_8012A828(s32 a0, void * a1);
#define RTP_SND(sndid)                                                        \
    L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);                            \
    L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);                            \
    L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);                            \
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); } \
    { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); } \
    RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);                        \
    if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF              \
                    && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {           \
        s32 x = (s16)L.sxy[0];                                                \
        s32 ax;                                                               \
        ax = x;                                                               \
        if (x < 0) {                                                          \
            ax = -x;                                                          \
        }                                                                     \
        ax = ((0xF0 - ax) * 0x7F) / 0xF0;                                     \
        __asm__("" : "=r"(ax) : "0"(ax));                                     \
        x = (x + 0xF0) / 0x1E;                                                \
        if (x == 0x10) {                                                      \
            x = 0xF;                                                          \
        }                                                                     \
        x = x << 8;                                                           \
        {                                                                     \
            s32 flg = 0x3000;                                                 \
            func_8002D4C8(sndid, ((ax | flg) | x) & 0xFFFF);                  \
        }                                                                     \
    }

void func_8018B7F0(s32 a0) {

    extern u8  D_800AF648;
    extern s32 D_801D4A60[];
    extern u8  D_801DBF20[];
    extern u8  D_801DBFA8[];
    extern u8  D_801DC030[];
    struct {
        s16 pad0[4];  /* sp+0x10 — dead, but sizes the frame (idiom 6) */
        s16 v[3];     /* sp+0x18 */
        s16 pad1;     /* sp+0x1E */
        u16 sxy[2];   /* sp+0x20 */
        s32 z;        /* sp+0x24 */
        s32 flag;     /* sp+0x28 */
    } L;
    s32 t;
    s32 ang;
    s32 idx;
    s32 m;
    s32 c;
    s32 p;

    if (*(s16 *)(a0 + 0x98) == 0) {
        s32 spr = (s32)func_8012913C(0x7F);
        if (spr != 0) {
            m = *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)
              + (func_8004787C(*(s16 *)(a0 + 0x104)) >> 3);
            *(s16 *)(spr + 0x6) = *(u16 *)(a0 + 0x6) - (func_8004787C(m) * 0x6C) / 0x1000;
            *(s16 *)(spr + 0xA) = *(u16 *)(a0 + 0xA) - 0x34;
            *(s16 *)(spr + 0xE) = *(u16 *)(a0 + 0xE) - (func_80047948(m) * 0x6C) / 0x1000;
            *(s32 *)(spr + 0x14) = 0x40000;
            *(s32 *)(spr + 0x10) = -(func_8004787C(m) * 0xC0);
            *(s32 *)(spr + 0x18) = -(func_80047948(m) * 0xC0);
        }
        t = *(u16 *)(a0 + 0x104) + 0x100;
        *(s16 *)(a0 + 0x104) = t;
        ang = (s16)t;
        idx = ang / 0x100;
        m = (s16)(idx % 0x10);
        if (ang == 0x100) {
            RTP_SND(0x95F)
        } else if (m == 0) {
            RTP_SND(0x960)
        }
        *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = D_801D4A60[m];
        c = *(u16 *)(a0 + 0x100) - 1;
        *(s16 *)(a0 + 0x100) = c;
        if ((s16)c == 0) {
            p = *(s32 *)(a0 + 0xCC);
            *(s16 *)(a0 + 0x98) = 1;
            if (p != 0) {
                *(s16 *)(p + 0x98) = 1;
            }
            p = *(s32 *)(a0 + 0xD0);
            if (p != 0) {
                *(s16 *)(p + 0x98) = 1;
            }
        }
    } else if ((*(u16 *)(a0 + 0x72) & 0x4000) != 0) {
        *(s16 *)(a0 + 0x2) = 7;
        *(s16 *)(a0 + 0x100) = 0x3C;
        func_8012A828(a0, D_801DBF20);
        p = *(s32 *)(a0 + 0xCC);
        if (p != 0) {
            func_8012A828(p, D_801DBFA8);
        }
        p = *(s32 *)(a0 + 0xD0);
        if (p != 0) {
            func_8012A828(p, D_801DC030);
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018BCB4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018BE84);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018C074);


// @class: plumbing
// @stuck: none — MATCH (126 ins). Keys: (1) cVar1 as `int` (not unsigned char) so the
//   lbu-loaded byte stays full-width and gcc omits the per-compare `andi 0xff`; (2) uninitialized
//   `int unaff_s1` -> $s1 (live-from-entry across func_8002D4C8); (3) func_8016AA50 takes TWO args
//   (param_1, unaff_s1) — a1=unaff_s1 arg-setup is reused by the preceding subtraction and a0=s0
//   hoists into the branch delay slot; (4) 0x76 read UNSIGNED (lhu) in the subtract, SIGNED (lh) in
//   the `< 1` test.

extern void func_8002D4C8(int, int);
extern void func_8016AA50(int, int);
extern s32 func_8016B428(s32);
extern void func_80019064(void *);
extern void func_8002A520(int);
extern void func_8002A790(int);
extern void func_80131E00(int, int);

void func_8018C38C(int param_1)
{

    extern unsigned char D_801D4B7C[];
    int cVar1;
    int unaff_s1;

    cVar1 = *(unsigned char *)(param_1 + 0x5e);
    *(char *)(param_1 + 0xc1) = 0;
    *(short *)(param_1 + 0x5e) = 0;
    *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) & 0xfffe;
    if (*(short *)(param_1 + 0xfc) == 0) {
        *(int *)(param_1 + 4) = *(int *)(*(int *)(param_1 + 0x64) + 4);
        *(int *)(param_1 + 8) = *(int *)(*(int *)(param_1 + 0x64) + 8);
        *(int *)(param_1 + 0xc) = *(int *)(*(int *)(param_1 + 0x64) + 0xc);
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x10) =
            *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x10);
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x12) =
            *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x12);
        *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x14) =
            *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x64) + 0x20) + 0x14);
    }
    if (*(short *)(param_1 + 0x102) == 0) {
        *(short *)(param_1 + 0x102) = 10;
        *(unsigned short *)(param_1 + 0x5c) = *(unsigned short *)(param_1 + 0x5c) | 0x4000;
        func_8002D4C8(0x9b7, 0);
        if (*(short *)(param_1 + 0x60) != 0) {
            if (cVar1 == 0x1d) {
                *(short *)(param_1 + 0x82) = 0;
                *(short *)(param_1 + 0x7c) = *(unsigned short *)(param_1 + 6);
                *(short *)(param_1 + 0x7e) = *(unsigned short *)(param_1 + 0xa);
                *(short *)(param_1 + 0x80) = *(unsigned short *)(param_1 + 0xe);
            }
            if (*(int *)(param_1 + 0x78) != 0) {
                unaff_s1 = (int)*(short *)(param_1 + 0x60) *
                           (int)*(short *)(*(int *)(param_1 + 0x78) + 0x30) >> 0xc;
                if (unaff_s1 < 1) {
                    unaff_s1 = 1;
                }
            }
            *(unsigned short *)(param_1 + 0x76) =
                *(unsigned short *)(param_1 + 0x76) - unaff_s1;
            func_8016AA50(param_1, unaff_s1);
            if ((*(unsigned short *)(param_1 + 0x82) & 1) != 0) {
                ((void (*)(int))func_8016B428)(param_1);
                func_80019064(D_801D4B7C);
            }
        }
        if (cVar1 != 0x1d) {
            if (*(unsigned char *)(param_1 + 0xc8) != 0) {
                func_8002A520(param_1);
            }
            if (*(unsigned char *)(param_1 + 0xc9) != 0) {
                func_8002A790(param_1);
            }
        }
        if (*(short *)(param_1 + 0x76) < 1) {
            *(short *)(param_1 + 0x5c) = 0;
            func_80131E00(param_1, 6);
        }
    }
    return;
}





extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(s32);
extern u8 *func_8012913C(s32 a0);
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 VectorNormalSS(void *a0, void *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018C584(s32 a0) {

    extern s32 D_801151D4;

    extern void func_8002AC00(s32 arg0);
    extern void func_8002A04C(s32 arg0);
    extern u8 D_800AF648;

    u16 v10[4];   /* sp+0x10 */
    s16 v18[4];   /* sp+0x18 */
    s32 sxy;      /* sp+0x20 */
    s32 z;        /* sp+0x24 */
    s32 flag;     /* sp+0x28 */
    s32 base;
    s32 iv;
    s32 i;
    s32 t;
    s32 r;

    base = D_801151D4;

    if (*(s16 *)(a0 + 0xFC) >= 0x1F) {
        iv = func_8012C658(0x33, 3, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) - 8;
            *(u16 *)(iv + 0x1A) = *(u16 *)(iv + 0x1A) - 5;
        }
        iv = func_8012C658(0x33, 3, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) - 8;
            *(u16 *)(iv + 0x1A) = *(u16 *)(iv + 0x1A) + 5;
        }
        iv = func_8012C658(0x32, 2, a0);
        if (iv != 0) {
            *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) - 0x20;
            *(u16 *)(iv + 0x12) = *(u16 *)(iv + 0x12) + 8;
        }

        func_8002AC00(0x22);

        iv = *(s32 *)(a0 + 0x64);
        *(s16 *)(iv + 2) = 2;
        iv = *(s32 *)(*(s32 *)(a0 + 0x64) + 0xD0);
        *(s16 *)(iv + 2) = 4;
        *(s32 *)(*(s32 *)(a0 + 0x64) + 0xCC) = 0;

        i = 0;
        do {
            iv = func_8012C588(0x281, a0);
            if (iv != 0) {
                *(s32 *)(iv + 0x1C) = 2;
                *(s16 *)(iv + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(iv + 0x16) = -((rand() & 0x0F) + 0x10);
                *(s16 *)(iv + 0x1A) = (rand() & 0x1F) - 0x10;
            }
            i++;
        } while (i < 8);

        v18[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        v18[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        v18[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)v18, (s32)&sxy, &z, &flag);
        if (flag >= 0 && (u32)((*(u16 *)&sxy + 0xEF) & 0xFFFF) < 0x1DF
                      && (u32)((*((u16 *)&sxy + 1) + 0xB3) & 0xFFFF) < 0x167) {
            s32 sx;
            s32 av;

            sx = (s16)*(u16 *)&sxy;
            av = sx;
            if (sx < 0) {
                av = -sx;
            }
            /* one local for |x| AND the volume: gcc-2.7.2 keeps the single pseudo
               in $v1 in place (subu $v1,$v0,$v1); a separate `vol` local steals $a1
               and the whole OR chain drifts (cookbook §136 L1). */
            av = ((0xF0 - av) * 0x7F) / 0xF0;
            sx = (sx + 0xF0) / 0x1E;
            if (sx == 0x10) {
                sx = 0xF;
            }
            sx = sx << 8;
            func_8002D4C8(0x961, (av | (0x3000 | sx)) & 0xFFFF);
        }

        func_8002A04C(a0);
        ((void (*)(void *))func_8012C218)((void *)a0);
        return;
    }

    iv = (s32)func_8012913C(0x23);
    if (iv != 0) {
        r = rand();
        *(u16 *)(iv + 0x06) = *(u16 *)(a0 + 0x06) + (r & 0x7F) - 0x40;
        r = rand();
        *(u16 *)(iv + 0x0A) = *(u16 *)(a0 + 0x0A) + (r & 0x7F) - 0x80;
        r = rand();
        *(u16 *)(iv + 0x0E) = *(u16 *)(a0 + 0x0E) + (r & 0x7F) - 0x40;

        t = func_80047948((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(s32 *)(iv + 0x04) = *(s32 *)(iv + 0x04) + (t << 10);

        t = func_8004787C((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
        *(u16 *)(iv + 0x34) = 0x1800;
        *(s32 *)(iv + 0x18) = 0;
        *(s32 *)(iv + 0x14) = 0;
        *(s32 *)(iv + 0x10) = 0;
        *(s32 *)(iv + 0x0C) = *(s32 *)(iv + 0x0C) - (t << 10);

        v10[0] = *(s32 *)(base + 0x5C) - *(u16 *)(iv + 0x06);
        v10[1] = *(s32 *)(base + 0x60) - *(u16 *)(iv + 0x0A);
        v10[2] = *(s32 *)(base + 0x64) - *(u16 *)(iv + 0x0E);
        VectorNormalSS(v10, v10);

        *(u16 *)(iv + 0x06) = *(u16 *)(iv + 0x06) + ((s16)v10[0] >> 6);
        *(u16 *)(iv + 0x0A) = *(u16 *)(iv + 0x0A) + ((s16)v10[1] >> 6);
        *(u16 *)(iv + 0x0E) = *(u16 *)(iv + 0x0E) + ((s16)v10[2] >> 6);
        *(u16 *)(iv + 0x34) = 0x3000;
        func_8002D4C8(0xAF8, 0);
    }

    *(u16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
}



// @class: struct
// @stuck: none — MATCH

extern int rand(void);
extern int func_80143C74(short *, int);
extern int func_80047948(int);
extern int func_8004787C(int);

void func_8018C9CC(short *param_1)
{

    extern void (*D_801D4C94[])(short *);
    int iVar3;
    unsigned int uVar2;
    short v;

    v = param_1[0x81];
    if (v != 0) {
        v = v - 1;
        param_1[0x81] = v;
        if (v == 0) {
            *(unsigned short *)(param_1 + 0x2e) &= 0xbfff;
        }
    }
    D_801D4C94[*(unsigned short *)(param_1 + 1)](param_1);
    if (*(unsigned short *)param_1 != 0) {
        if (param_1[0x7e] == 0) {
            *(int *)(param_1 + 2) = *(int *)(*(int *)(param_1 + 0x32) + 4);
            *(int *)(param_1 + 4) = *(int *)(*(int *)(param_1 + 0x32) + 8);
            *(int *)(param_1 + 6) = *(int *)(*(int *)(param_1 + 0x32) + 0xc);
            *(unsigned short *)(*(int *)(param_1 + 0x10) + 0x10) =
                *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x32) + 0x20) + 0x10);
            *(unsigned short *)(*(int *)(param_1 + 0x10) + 0x12) =
                *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x32) + 0x20) + 0x12);
            *(unsigned short *)(*(int *)(param_1 + 0x10) + 0x14) =
                *(unsigned short *)(*(int *)(*(int *)(param_1 + 0x32) + 0x20) + 0x14);
        }
        if ((param_1[0x3b] < 5) && ((rand() & 3) == 0) &&
            ((iVar3 = func_80143C74(param_1, 0)) != 0)) {
            uVar2 = rand();
            *(int *)(iVar3 + 0x10) = ((uVar2 & 0x7ff) - 0x400) * 0x100;
            *(unsigned int *)(iVar3 + 0x14) = 0xfff00000;
            uVar2 = rand();
            *(int *)(iVar3 + 0x18) = ((uVar2 & 0x7ff) - 0x400) * 0x100;
            *(int *)(iVar3 + 4) +=
                func_80047948((int)*(short *)(*(int *)(param_1 + 0x10) + 0x12)) * 0x400;
            *(int *)(iVar3 + 0xc) -=
                func_8004787C((int)*(short *)(*(int *)(param_1 + 0x10) + 0x12)) * 0x400;
            uVar2 = rand();
            *(short *)(iVar3 + 6) -= 0x20;
            *(short *)(iVar3 + 6) += (uVar2 & 0x3f);
            *(short *)(iVar3 + 0xa) -= 0x40;
            uVar2 = rand();
            *(short *)(iVar3 + 0xe) -= 0x20;
            *(short *)(iVar3 + 0xe) += (uVar2 & 0x3f);
        }
    }
    return;
}




extern s32  func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_8012C588(s32 a0, s32 a1);
extern void func_8012C218(s32);
extern u8  *func_8012913C();
extern s32  rand(void);
extern s32  func_80047948(s32 a0);
extern s32  func_8004787C(s32 a0);
extern s32  VectorNormalSS(void *a0, void *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32  RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002A04C(s32 a0);


void func_8018CBDC(s32 a0) {

    extern s32 D_801151D4;

    extern u8 D_800AF648;
    extern void func_8002AC00(s32 arg0);

    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 v[4];    /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;
    s32 p;
    s32 s0;
    s32 i;

    p = D_801151D4;

    if (*(s16 *)(a0 + 0xFC) >= 0x1F) {
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(s16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) - 5;
        }
        s0 = func_8012C658(0x33, 3, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) - 8;
            *(s16 *)(s0 + 0x1A) = *(u16 *)(s0 + 0x1A) + 5;
        }
        s0 = func_8012C658(0x32, 2, a0);
        if (s0 != 0) {
            *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) - 0x20;
            *(s16 *)(s0 + 0x12) = *(u16 *)(s0 + 0x12) + 8;
        }
        func_8002AC00(0x22);
        s0 = *(s32 *)(a0 + 0x64);
        *(s16 *)(s0 + 0x2) = 4;
        s0 = *(s32 *)(*(s32 *)(a0 + 0x64) + 0xCC);
        *(s16 *)(s0 + 0x2) = 4;

        for (i = 0; i < 8; i++) {
            s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }

        L.v[0] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x48);
        L.v[1] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x4C);
        L.v[2] = *(s32 *)(*(s32 *)(a0 + 0x20) + 0x50);
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
        { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
        RotTransPers((s32)L.v, (s32)L.sxy, &L.z, &L.flag);
        if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                        && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
            s32 x = (s16)L.sxy[0];
            s32 ax;
            ax = x;
            if (x < 0) {
                ax = -x;
            }
            ax = ((0xF0 - ax) * 0x7F) / 0xF0;
            __asm__("" : "=r"(ax) : "0"(ax));
            x = (x + 0xF0) / 0x1E;
            if (x == 0x10) {
                x = 0xF;
            }
            x = x << 8;
            {
                s32 flg = 0x3000;
                func_8002D4C8(0x961, ((ax | flg) | x) & 0xFFFF);
            }
        }

        *(s32 *)(*(s32 *)(a0 + 0x64) + 0xD0) = 0;
        func_8002A04C(a0);
        ((void (*)(void *))func_8012C218)((void *)a0);
        return;
    }

    s0 = (s32)func_8012913C(0x23);
    if (s0 != 0) {
        *(s16 *)(s0 + 0x6) = *(u16 *)(a0 + 0x6) + (rand() & 0x7F) - 0x40;
        *(s16 *)(s0 + 0xA) = *(u16 *)(a0 + 0xA) + (rand() & 0x7F) - 0x80;
        *(s16 *)(s0 + 0xE) = *(u16 *)(a0 + 0xE) + (rand() & 0x7F) - 0x40;

        *(s32 *)(s0 + 0x4) =
            *(s32 *)(s0 + 0x4) -
            func_80047948(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x400;
        {
            s32 t = func_8004787C(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12)) * 0x400;
            *(s16 *)(s0 + 0x34) = 0x1800;
            *(s32 *)(s0 + 0x18) = 0;
            *(s32 *)(s0 + 0x14) = 0;
            *(s32 *)(s0 + 0x10) = 0;
            *(s32 *)(s0 + 0xC) = *(s32 *)(s0 + 0xC) + t;
        }

        L.nv[0] = *(s32 *)(p + 0x5C) - *(u16 *)(s0 + 0x6);
        L.nv[1] = *(s32 *)(p + 0x60) - *(u16 *)(s0 + 0xA);
        L.nv[2] = *(s32 *)(p + 0x64) - *(u16 *)(s0 + 0xE);
        VectorNormalSS(L.nv, L.nv);

        *(s16 *)(s0 + 0x6) = *(u16 *)(s0 + 0x6) + ((s16)L.nv[0] >> 6);
        *(s16 *)(s0 + 0xA) = *(u16 *)(s0 + 0xA) + ((s16)L.nv[1] >> 6);
        *(s16 *)(s0 + 0xE) = *(u16 *)(s0 + 0xE) + ((s16)L.nv[2] >> 6);
        *(s16 *)(s0 + 0x34) = 0x3000;
        func_8002D4C8(0xAF8, 0);
    }

    *(s16 *)(a0 + 0xFC) = *(u16 *)(a0 + 0xFC) + 1;
}



extern s32 rand(void);
extern s32 func_80143C74();
extern s32 func_80047948(s32 a0);
extern s32 func_8004787C(s32 a0);

void func_8018D020(s32 a0) {

    extern void (*D_801D4D0C[])(s32);
    s32 iVar3;
    s32 iVar4;
    s32 r;

    {
        s16 t = *(s16 *)(a0 + 0x102);
        if (t != 0) {
            t--;
            *(s16 *)(a0 + 0x102) = t;
            if (t == 0) {
                *(u16 *)(a0 + 0x5C) &= 0xBFFF;
            }
        }
    }

    D_801D4D0C[*(u16 *)(a0 + 2)](a0);

    if (*(u16 *)(a0 + 0) != 0) {
        if (*(s16 *)(a0 + 0xFC) == 0) {
            *(s32 *)(a0 + 4) = *(s32 *)(*(s32 *)(a0 + 0x64) + 4);
            *(s32 *)(a0 + 8) = *(s32 *)(*(s32 *)(a0 + 0x64) + 8);
            *(s32 *)(a0 + 0xC) = *(s32 *)(*(s32 *)(a0 + 0x64) + 0xC);
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x10) =
                *(s16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x10);
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(s16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x12);
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x14) =
                *(s16 *)(*(s32 *)(*(s32 *)(a0 + 0x64) + 0x20) + 0x14);
        }
        if (*(s16 *)(a0 + 0x76) < 5 && (rand() & 3) == 0 &&
            (iVar3 = func_80143C74(a0, 0)) != 0) {
            *(s32 *)(iVar3 + 0x10) = ((rand() & 0x7FF) - 0x400) << 8;
            *(s32 *)(iVar3 + 0x14) = 0xFFF00000;
            *(s32 *)(iVar3 + 0x18) = ((rand() & 0x7FF) - 0x400) << 8;
            iVar4 = func_80047948((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
            *(s32 *)(iVar3 + 4) = *(s32 *)(iVar3 + 4) - iVar4 * 0x400;
            iVar4 = func_8004787C((s32) * (s16 *)(*(s32 *)(a0 + 0x20) + 0x12));
            *(s32 *)(iVar3 + 0xC) = *(s32 *)(iVar3 + 0xC) + iVar4 * 0x400;
            r = rand();
            {
                s32 m6 = *(u16 *)(iVar3 + 6) - 0x20;
                *(u16 *)(iVar3 + 6) = m6 + (r & 0x3F);
            }
            *(u16 *)(iVar3 + 0xA) = *(u16 *)(iVar3 + 0xA) - 0x40;
            r = rand();
            {
                s32 mE = *(u16 *)(iVar3 + 0xE) - 0x20;
                *(u16 *)(iVar3 + 0xE) = mE + (r & 0x3F);
            }
        }
    }
}




// @class: schedule
// @stuck: none — MATCH. Two levers: (1) split rand()-result into its own var (shared iVar1 forced an extra move a0,v0); (2) reorder decrement before sp[0] to group the two lhu loads as target's scheduler does; (3) materialize &D_80126B96 via a local u16* to CSE the address (lui+addiu once) instead of %hi/%lo split-per-access.








extern void func_80128EA8();
extern void func_8012931C();
extern int  func_80128ED8();
extern u8  *func_8012913C();
extern void func_801292C8();
extern int  func_8012D664();

extern u16 D_801270C0;

void func_8018D230(s32 arg0) {

    extern u8  D_801D4AF0;
    extern u8  D_801D4AFC;
    extern u16 D_80126B96;
    s32 iVar1;
    s32 rv;
    u8 *p;
    u16 sp[3];

    if (*(u16 *)(arg0 + 2) == 0) {
        *(u8 **)(*(s32 *)(arg0 + 0x20) + 0x20) = &D_801D4AF0;
        *(u32 *)(*(s32 *)(arg0 + 0x20) + 4) |= 0x50000000;
        *(u8 *)(*(s32 *)(arg0 + 0x20) + 0x27) = 0x59;
        func_80128EA8(*(s32 *)(arg0 + 0x20), arg0 + 0x24, (s32)&D_801D4AFC);
        rv = rand();
        *(s32 *)(arg0 + 0x1c) = 0x10;
        *(s32 *)(arg0 + 0x2c) = 0x200;
        *(s16 *)(arg0 + 0x28) = rv % 15;
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) = 0x1200;
        *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1a) = 0x1200;
        *(u16 *)(arg0 + 2) = *(u16 *)(arg0 + 2) + 1;
    } else if (*(s16 *)&D_801270C0 == 1) {
        func_8012931C(arg0);
        func_80128ED8(*(s32 *)(arg0 + 0x20), arg0 + 0x24);
        *(s32 *)(arg0 + 0x1c) -= 1;
        if ((rand() & 7) == 0 && (p = func_8012913C(0x22)) != 0) {
            *(u16 *)(p + 6) = *(u16 *)(arg0 + 6);
            *(u16 *)(p + 0xa) = *(u16 *)(arg0 + 0xa);
            *(u16 *)(p + 0xe) = *(u16 *)(arg0 + 0xe);
            *(s32 *)(p + 0x10) = *(s32 *)(arg0 + 0x10) >> 3;
            *(s32 *)(p + 0x14) = *(s32 *)(arg0 + 0x14) >> 3;
            *(s32 *)(p + 0x18) = *(s32 *)(arg0 + 0x18) >> 3;
            *(s16 *)(p + 0x34) = *(u16 *)(*(s32 *)(arg0 + 0x20) + 0x18) + 1;
            *(u16 *)(*(s32 *)(p + 0x20) + 0x2c) = 0xc008;
        }
        if (*(s32 *)(arg0 + 0x1c) == 0) {
            func_801292C8(arg0);
        } else {
            *(s32 *)(arg0 + 0x14) = 0xffff0000;
            iVar1 = *(s32 *)(arg0 + 0x2c) + 0x80;
            *(s32 *)(arg0 + 0x2c) = iVar1;
            *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) =
                *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) + (s16)iVar1;
            *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1a) =
                *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1a) + (s16)*(s32 *)(arg0 + 0x2c);
            *(s16 *)(arg0 + 0xa) = *(s16 *)(arg0 + 0xa) - 0x20;
            sp[0] = *(u16 *)(arg0 + 6);
            sp[1] = *(u16 *)(arg0 + 0xa);
            sp[2] = *(u16 *)(arg0 + 0xe);
            if (func_8012D664(sp, 0x10, 0xb4) == 1) {
                u16 *q = &D_80126B96;
                *q |= 0x4200;
            }
            *(s16 *)(arg0 + 0xa) = *(s16 *)(arg0 + 0xa) + 0x20;
        }
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018D4B4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018D4D4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018D5D4);


extern void func_8012B370(int a0);
extern void func_8012C218(s32);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018D674(s32 a0)
{
    s32 t;
    register s32 *a1 asm("$5");
    u32 v0;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        a1 = *(s32 **)(a0 + 0x20);
        v0 = *(u32 *)(a1 + 0x1);
        v0 ^= 0x80000000;
        *(u32 *)(a1 + 0x1) = v0;
        ((void (*)(void))func_8012B370)();

        t = *(s32 *)(a0 + 0x1C);
        if ((t & 0x3) != 0) {
            s32 s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    ((void (*)(void *))func_8012C218)((void *)a0);
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018D734);



















void func_8018D7CC(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0x64));
  *((s16 *) (v0 + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xD0))) + 0x5C)) = 0;
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018D7EC);

void func_8018D8DC(void) {
}

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018D8E4);


extern void func_8012B370(int a0);
extern void func_8012C218(s32);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018D9B8(s32 a0)
{
    s32 t;
    register s32 *a1 asm("$5");
    u32 v0;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        a1 = *(s32 **)(a0 + 0x20);
        v0 = *(u32 *)(a1 + 0x1);
        v0 ^= 0x80000000;
        *(u32 *)(a1 + 0x1) = v0;
        ((void (*)(void))func_8012B370)();

        t = *(s32 *)(a0 + 0x1C);
        if ((t & 0x3) != 0) {
            s32 s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    ((void (*)(void *))func_8012C218)((void *)a0);
}


extern void func_8012B370(int a0);
    void func_8018DA78(void) {
        ((s32 (*)(void))func_8012B370)();
    }


















void func_8018DA98(void *a0)
{
  s32 v0;
  *((s16 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0x5C)) = 0;
  ;
  *((s16 *) ((*((s32 *) ((*((s32 *) (((s32) a0) + 0x64))) + 0xCC))) + 0x5C)) = 0;
}

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018DAB8);

void func_8018DBAC(void) {
}

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018DBB4);


extern void func_8012B370(int a0);
extern void func_8012C218(s32);
extern s32 func_8012C588(s32 a0, s32 a1);
extern s32 rand(void);

void func_8018DCA8(s32 a0)
{
    s32 t;
    register s32 *a1 asm("$5");
    u32 v0;

    t = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = t;

    if (t != 0) {
        a1 = *(s32 **)(a0 + 0x20);
        v0 = *(u32 *)(a1 + 0x1);
        v0 ^= 0x80000000;
        *(u32 *)(a1 + 0x1) = v0;
        ((void (*)(void))func_8012B370)();

        t = *(s32 *)(a0 + 0x1C);
        if ((t & 0x3) != 0) {
            s32 s0 = func_8012C588(0x281, a0);
            if (s0 != 0) {
                *(s32 *)(s0 + 0x1C) = 2;
                *(s16 *)(s0 + 0x12) = (rand() & 0x1F) - 0x10;
                *(s16 *)(s0 + 0x16) = -((rand() & 0xF) + 0x10);
                *(s16 *)(s0 + 0x1A) = (rand() & 0x1F) - 0x10;
            }
        }
        return;
    }

    ((void (*)(void *))func_8012C218)((void *)a0);
}


extern void func_8012B370(int a0);
    void func_8018DD68(void) {
        ((void (*)(void))func_8012B370)();
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018DD88);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018DEC0);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018E094);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018E240);


extern void func_8012B1B4(s32 a0, s32 a1);
extern void func_8012CBCC(s32 a0);
extern void func_8012BE98(s32 a0, u16 *a1);
extern void func_8012BE54(s32 a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern s32 func_8018DD88(s32 a0, s32 a1);

void func_8018E428(s32 a0)
{
    s16 hi;
    s16 pos;
    s32 sp10[3];
    u16 state;

    hi = *(s16 *)(a0 + 0x8A);
    pos = *(s16 *)(a0 + 0xA);

    if (pos >= hi - 8) {
        if (*(s32 *)(a0 + 0x48) >= 0) {
            *(s32 *)(a0 + 0x48) = -0x8000;
            *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
        }
    } else {
        if (hi + 8 >= pos) {
            if (*(s32 *)(a0 + 0x48) <= 0) {
                *(s32 *)(a0 + 0x48) = 0x8000;
                *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
            }
        }
    }

    if (*(s32 *)(a0 + 0xDC) < -0x40000) {
        *(s32 *)(a0 + 0xDC) = -0x40000;
    }

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = *(s32 *)(a0 + 0xDC);
    func_8012B1B4(a0, (s32)sp10);
    func_8012CBCC(a0);

    state = *(u16 *)(a0 + 0x34);
    switch (state) {
    case 0: {
        register s32 s0v __asm__("$16");
        s32 ret;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;
        register s32 p20 __asm__("$4");

        s0v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s0v);
        if (ret <= 0x3FFFF) {
            if (func_8018DD88(a0, 0x51) == 0) {
                goto set_state1;
            }
        }
        p744 = func_8012B744((void *)(a0 + 4), (void *)s0v);
        v1p = *(s32 *)(a0 + 0x20);
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 8);
        p20 = *(s32 *)(a0 + 0x20);
        *(u16 *)(p20 + 0x12) = *(u16 *)(p20 + 0x12) + b608;
        v1p = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1p + 0x12) = *(u16 *)(v1p + 0x12) & 0xFFF;
        func_8012B1B4(a0, (s32)sp10);
        break;
    }
    case 1: {
        s32 ret;

        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) << 1;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88));
        if (ret > 0x3FFFF) {
            goto rand_tail;
        }
        if (func_8018DD88(a0, 0x51) == 0) {
            goto end_switch;
        }
        goto rand_tail;
    }
    case 2: {
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;
        s32 p20;

        p744 = func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88));
        v1p = *(s32 *)(a0 + 0x20);
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 0x10);
        p20 = *(s32 *)(a0 + 0x20);
        *(u16 *)(p20 + 0x12) = *(u16 *)(p20 + 0x12) + b608;
        v1p = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1p + 0x12) = *(u16 *)(v1p + 0x12) & 0xFFF;
        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) >> 1;
        func_8018DD88(a0, 0x51);
        if (*(s16 *)(a0 + 0x102) == 0) {
            *(u16 *)(a0 + 0x34) = 3;
        } else {
            *(s16 *)(a0 + 0x102) = *(s16 *)(a0 + 0x102) - 1;
        }
        break;
    }
    case 3: {
        register s32 s2v __asm__("$18");
        s32 ret;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;

        s2v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s2v);
        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) << 1;
        if (func_8018DD88(a0, 0x51) != 0) {
            goto rand_tail;
        }
        if (ret <= 0x40000) {
            goto set_state1;
        }
        p744 = func_8012B744((void *)(a0 + 4), (void *)s2v);
        v1p = *(s32 *)(a0 + 0x20);
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 1);
        if ((u32)(b608 + 0xFF) < 0x1FF) {
            goto end_switch;
        }
        goto rand_tail;
    }
    }
    goto end_switch;

rand_tail:
    *(u16 *)(a0 + 0x34) = 2;
    {
        s32 r = rand();
        *(s16 *)(a0 + 0x102) = (r & 7) + 8;
    }
    goto end_switch;

set_state1:
    *(u16 *)(a0 + 0x34) = 1;

end_switch:
    if (*(s16 *)(a0 + 0x100) != 0) {
        *(s16 *)(a0 + 0x100) = *(s16 *)(a0 + 0x100) - 1;
    } else {
        s32 ret3;

        ret3 = ((s32 (*)(s32))func_8012BE54)(a0);
        if (ret3 <= 0x24000) {
            *(s16 *)(a0 + 0x2) = 2;
            *(s16 *)(a0 + 0x100) = 0x3C;
        }
    }
}




extern s32 func_8018A6DC(s32 a0, s32 a1);
extern s32 func_8012C588(s32 a0, s32 a1);
extern void func_8012F14C(s32);
extern void func_8012B370(int a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);


void func_8018E764(s32 param_1)
{

    extern u8 D_801DC794;
    extern u8 D_801DC79C;
    extern u8 D_801DC7A4;
    extern u8 D_800AF648;
    /* L5: slot offsets are exact only through ONE struct — copied verbatim
       from the banked RTP_SND sibling func_80180CA8 (same TU) so the
       sp+0x10.."0x2B layout reproduces byte-for-byte. */
    struct {
        u16 nv[4];   /* sp+0x10 */
        s16 rv[4];   /* sp+0x18 */
        u16 sxy[2];  /* sp+0x20 */
        s32 z;       /* sp+0x24 */
        s32 flag;    /* sp+0x28 */
    } L;

    s16 sVar1;
    s32 s0;

    if (*(s32 *)(param_1 + 0x1c) == 0) {
        sVar1 = *(s16 *)(param_1 + 0x100) - 1;
        *(s16 *)(param_1 + 0x100) = sVar1;
        if (sVar1 == 0) {
            *(s16 *)(param_1 + 2) = 1;
            *(s16 *)(param_1 + 0x100) = 0x3c;
            *(s16 *)(param_1 + 0x8a) = *(s16 *)(param_1 + 0xa) - 0x140;
        } else {
            *(s32 *)(param_1 + 0x1c) = (sVar1 == 1) ? 0x3c : 3;

            func_8018A6DC(param_1, (s32)&D_801DC794);

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&D_801DC79C, (s32)L.nv);
                *(s16 *)(s0 + 6)  = L.nv[0];
                *(s16 *)(s0 + 0xA) = L.nv[1];
                *(s16 *)(s0 + 0xE) = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 0, s0);
            }

            s0 = func_8012C588(0x260, param_1);
            if (s0 != 0) {
                ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)(param_1 + 0x20) + 0x34, (s32)&D_801DC7A4, (s32)L.nv);
                *(s16 *)(s0 + 6)  = L.nv[0];
                *(s16 *)(s0 + 0xA) = L.nv[1];
                *(s16 *)(s0 + 0xE) = L.nv[2];
                func_8012B370(s0);
                func_8012C658(0x261, 1, s0);
            }

            L.rv[0] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x48);
            L.rv[1] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x4C);
            L.rv[2] = *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x50);
            { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_8004914C(r4); }
            { register void *r4 __asm__("$4"); r4 = &D_800AF648; func_800491AC(r4); }
            RotTransPers((s32)L.rv, (s32)L.sxy, &L.z, &L.flag);
            if (L.flag >= 0 && (u32)((L.sxy[0] + 0xEF) & 0xFFFF) < 0x1DF
                          && (u32)((L.sxy[1] + 0xB3) & 0xFFFF) < 0x167) {
                s32 x = (s16)L.sxy[0];
                s32 ax;

                ax = x;
                if (x < 0) {
                    ax = -x;
                }
                ax = ((0xF0 - ax) * 0x7F) / 0xF0;
                __asm__("" : "=r"(ax) : "0"(ax));
                x = (x + 0xF0) / 0x1E;
                if (x == 0x10) {
                    x = 0xF;
                }
                x = x << 8;
                {
                    s32 flg = 0x3000;
                    func_8002D4C8(0x84A, ((ax | flg) | x) & 0xFFFF);
                }
            }
        }
    } else {
        *(s32 *)(param_1 + 0x1c) = *(s32 *)(param_1 + 0x1c) - 1;
    }
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018EA0C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018EB3C);


extern void (*D_801DC7F8[])(void);

void func_8018EC14(void *a0) {
    D_801DC7F8[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018EC50);


extern void (*D_801DC818[])(void);

void func_8018EDC4(void *a0) {
    D_801DC818[*(u16 *)((s32)a0 + 0x2)]();
}


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018EE00);

extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8018DEC0(void);

void func_8018EE88(void *a0) {
    func_8002D4C8(0xB32, 0);
    ((void (*)(void *))func_8018DEC0)(a0);
}


extern void func_8018E094(void);
    void func_8018EEC0(s32 *param_1) {
        *(short *)(*(int *)((char *)param_1 + 0x20) + 0x10) = 0xe00;
        ((void (*)(void))func_8018E094)();
    }


extern void func_8018E094(void);
    void func_8018EEE8(s32 arg0) {
        s32 temp_v1 = *(s32 *)(arg0 + 0x20);
        *(u16 *)(temp_v1 + 0x10) += 0x20;
        func_8018E094();
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018EF1C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018EF68);

extern void func_8018DEC0(void);
    void func_8018F054(s32 *a0) {
        *(s32 *)((char *)a0 + 0x10) = *(s32 *)((char *)a0 + 0x10) >> 1;
        *(s32 *)((char *)a0 + 0x18) = *(s32 *)((char *)a0 + 0x18) >> 1;
        ((void (*)(void))func_8018DEC0)();
    }


extern void func_8018DEC0(void);
    void func_8018F088(u8 *param_1) {
        param_1[0xC1] = 0xC;
        *(int *)(param_1 + 0x1C) = 0x3C;
        ((void (*)(void))func_8018DEC0)();
    }


INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018F0B4);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018F140);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018F268);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018F39C);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018F3FC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018F4BC);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018F590);

INCLUDE_ASM("asm/ov_SC06_024/nonmatchings/ov_SC06_024_jr_8017BEBC", func_8018F688);




