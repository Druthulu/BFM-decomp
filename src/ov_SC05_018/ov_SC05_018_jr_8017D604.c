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
extern u8 D_80078E50;
extern void func_800D185C(u8 *a0);
extern void func_801458E8(void);
extern s32 func_80029504(void);
extern void func_80145B24(void);
extern u8 D_80188E6C;
extern u8 D_80188DDC;
extern u8 D_80188DB8;
extern u8 D_80188D94;
extern u8 D_80188E48;
extern u8 D_80188E24;
extern u8 D_80188E00;
extern u8 D_80188D70;
extern void func_80145934(void);
extern u8 D_80188EFC;
extern u8 D_80188ED8;
extern u8 D_80188EB4;
extern u8 D_80188E90;
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
extern unsigned char D_801882F4[];
extern unsigned char D_80188324[];
extern unsigned char D_80188374[];
extern unsigned char D_801883A4[];
extern unsigned char D_801883D4[];
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
extern void (*D_80188424[])(void *);
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
extern s32 D_801884EC[];
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
extern u8 D_80188574[];
extern void func_8014C1A0(s32 arg0, s32 arg1);
extern s32 func_80013328(s32 a0, s32 a1);
extern s32 func_8014C59C(void *a0, void *a1);
extern s32 func_8014C308(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_8014C43C(void *a0, s32 a1, s32 a2, s32 a3, s16 a5);
extern s32 func_8014C3A4(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C3D0(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014C43C(void * a0, s32 a1, s32 a2, s32 a3, s16 a4);
extern s32 ratan2(s32 dx, s32 dy);
extern u8 D_8018857C;
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
extern int D_801E5140;
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
extern s32 D_801E5144;
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
extern s32 D_801885AC;
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
extern void (*D_80188654[])(void);
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
extern void (*D_80188678[])(void);
extern void func_80152058(void *a0);
extern void func_801520DC(s32 a0);
extern void func_80152094(s32 a0);
extern void func_80147324(s32 a0);
extern u8 D_80062C04[];
extern M2C_UNK D_80188668;
extern void func_801520DC(s32 arg0);
extern void func_801470B4(s32 a0);
extern void func_8015369C(s32 a0);
extern void func_80152194(s32 *a0);
extern s32 func_801536DC(s32 a0);
extern void func_8015220C(s32 a0);
extern s32 func_80153800(s32 a0);
extern void func_801522CC(s32 a0);
extern void func_80152254(s32 *a0);
extern void (*D_8018868C[])(void);
extern void func_80152370(void *a0);
extern void func_801523F4(s32 a0);
extern void func_801523AC(s32 a0);
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern u8 D_80188698[];
extern void func_801523F4(s32 arg0);
extern void func_801525F4(int);
extern s32 func_801535F4(void *arg0);
extern void func_8015BF48(s32 *a0);
extern void func_80152500(int param_1);
extern void func_801525F4(s32 a0);
extern void (*D_801886A8[])(void);
extern void func_80152698(void *a0);
extern void func_80152714(s32 a0);
extern void func_801526D4(s32 a0);
extern void func_80152790(s32 a0);
extern void (*D_801886C0[])(void);
extern void func_8015282C(void *a0);
extern void func_801528B0(s32 a0);
extern void func_80152868(s32 a0);
extern M2C_UNK D_801886B0;
extern void func_801528B0(s32 arg0);
extern void func_8015294C(s32 a0);
extern void func_80152A08(s32 a0);
extern void func_80152AC8(s32 a0);
extern void func_80152A50(s32 *a0);
extern void (*D_801886D4[])(void);
extern void func_80152B6C(void *a0);
extern void func_80152BF0(s32 a0);
extern void func_80152BA8(s32 a0);
extern void func_80152C80(s32 *a0);
extern void func_80152C40(s32 *a0);
extern void (*D_801886F0[])(void);
extern void func_80152D24(void *a0);
extern void func_80152DA8(s32 a0);
extern void func_80152D60(s32 a0);
extern M2C_UNK D_801886E0;
extern void func_80152DA8(s32 arg0);
extern void func_80152E4C(s32 a0);
extern void func_80152EFC(s32 a0);
extern void func_80152FBC(s32 a0);
extern void func_80152F44(s32 *a0);
extern void (*D_80188704[])(void);
extern void func_80153060(void *a0);
extern void func_801530E4(s32 a0);
extern void func_8015309C(s32 a0);
extern void func_80155440(s32 *a0);
extern void func_801530E4(s32 arg0);
extern void func_80153150(struct S80153150 *a0);
extern void func_801531BC(s32 a0);
extern void func_8015327C(s32 a0);
extern void func_80153204(s32 *a0);
extern void (*D_80188718[])(void);
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
extern s32 D_8018872C;
extern void (*D_80188754[])(void *a0);
extern void func_80153CCC(S80153CCC *a0);
extern void func_80153D7C(s32 a0);
extern void func_80153D34(s32 a0);
extern u8 D_80188734;
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
extern int (*D_801887A0[])(void);
extern s32 func_80155458(s32 param_1);
extern s32 func_801659DC(u8 *a0);
extern s32 func_801554B8(void *arg0);
extern void func_801555F4(void *a0);
extern void func_80155518(s32 *a0);
extern void func_80155580(void *a0);
extern void (*D_801887A4[])(void);
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
extern unsigned short D_80188C08[];
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
extern void (*D_80188C18[])(void);
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
extern int D_801E5178;
extern void func_801578C0(s32 a0);
extern void func_80157788(int param_1);
extern void func_801577C8(s32 arg0);
extern void (*D_80188C40[])(void);
extern void func_80157808(void *param_1);
extern void func_80157880(s32 a0);
extern s32 func_801725A4(u8 *a0);
extern u8 D_800D5128;
extern u8 D_80188C20;
extern void func_801578C0(s32 param_1);
extern void func_80147A84(int);
extern void func_80148038(int, int);
extern void func_80147460(int);
extern void func_80146D90(int);
extern void func_80161450(void *a0);
extern void func_80157A8C(int);
extern void func_80154A74(int, int);
extern unsigned char D_800D5178;
extern unsigned char D_80188C30;
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
extern void (*D_80188C80[])(void);
extern void func_80157E38(void *);
extern void func_80157E00(void *a0);
extern void func_80157E38(void * a0);
extern s32 func_80157F64(s32 *a0);
extern s32 func_80156600(void *a0);
extern void func_80157EA4(void *a0);
extern void (*D_80188C88[])(void);
extern void func_80158038(void *);
extern void func_80158000(void *a0);
extern s32 D_800D51E0;
extern s32 D_80188C54;
extern void func_80158038(void * param);
extern u8 D_800D524C[];
extern void func_80161418(void *a0);
extern void func_801580B4(s32 a0);
extern void func_801581AC(s32 a0);
extern void (*D_80188C94[])(void);
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
extern u8 D_80188C64;
extern u8 D_800D533C;
extern void func_80158434(s32 param_1);
extern void func_80158548(s32 param_1);
extern void func_801585EC(u8 *a0);
extern void func_80158794(void);
extern s32 D_801E5180;
extern s32 D_801E518C;
extern s32 D_801E5190;
extern void func_80158880(s32 *param);
extern void func_8015879C(s32 param_1);
extern void func_80158814(void *arg0);
extern void (*D_80188CD0[])(s32 *);
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
extern s32 D_80188CA4[];
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
extern s32 D_801E5188;
extern void func_8015934C(void *arg0);
extern void func_801593E4(A801593E4 *a0);
extern void (*D_80188F20[])(void);
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
extern char D_80188D40[];
extern s32 func_801596F0(s32 param_1);
extern s32 func_80159874(void);
extern void func_800167B8(s32 a0);
extern s32 func_8015987C(s32 a0);
extern int func_800167F0(int arg);
extern int func_801598BC(void);
extern void func_80159968(void *a0);
extern void func_801598E0(u8 *a0);
extern void (*D_80188FC4[])(void);
extern void func_80159A20(void *a0);
extern void func_801599E0(void *a0);
extern void func_80159A18(void);
extern void func_80159BE4(s32);
extern void func_80159B08(s32 *a0);
extern void func_80159B70(void *a0);
extern void func_80159B3C(void * a0);
extern void (*D_80189118[])(void);
extern void func_80159BAC(s32 a0);
extern s32 func_80172590(u8 *a0);
extern unsigned char D_80188F34;
extern void func_80159BE4(s32 arg0);
extern void func_8015A1C8(s32 a0);
extern void func_8015A2D8(s32);
extern void func_8015A1FC(s32 *a0);
extern void func_8015A264(void *a0);
extern void func_8015A230(s32 *a0);
extern void (*D_80189120[])(void);
extern void func_8015A2A0(s32 a0);
extern int D_80188F44;
extern s32 func_80172608(u8 *a0);
extern void func_8015A2D8(s32 param_1);
extern u8 D_800D48DC;
extern s32 func_8015AB7C(s32 a0);
extern s32 D_8011F9C4;
extern s32 func_8015ABD4(s32 a0, s32 a1, s32 a2);
extern s32 func_80161CD0(s32 a0, s32 a1);
extern M2C_UNK D_80188F64;
extern void func_8015AC48(s32 arg0);
extern void func_8015AC90(s32 a0);
extern void func_8015ADB0(s32 a0);
extern void func_8015ACC4(s32 *arg0);
extern void func_8015AD3C(void *a0);
extern void func_8015AD08(void *arg0);
extern void (*D_80189128[])(void);
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
extern void (*D_80189150[])(void);
extern void func_8015C0C4(s32);
extern void func_8015C08C(s32 a0);
extern s32 func_8015C128(s32 param_1);
extern void func_8015C6A4(void);
extern void func_8015C788(s32 a0);
extern void func_8015C6AC(s32 *a0);
extern void func_8015C714(void *a0);
extern void func_8015C6E0(s32 *a0);
extern void (*D_8018915C[])(void);
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
extern void (*D_80188FD0[])(void *);
extern s32 func_801725F4(u8 *a0);
extern void func_8015D104(void *arg0);
extern s32 D_80189200;
extern void func_8015D380(s32 a0);
extern unsigned char D_801882E4[];
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
extern unsigned char D_80189214[];
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
extern s8 D_80189250[];
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
extern u16 D_80189298;
extern u16 D_8018929A;
extern u16 D_8018929C;
extern s32 D_801892A0;
extern void func_80013E94(void *a0, void *a1);
extern void func_8015E4B0(s32 param_1);
extern void func_8013C9C4(void *a0);
extern s32 D_801892A8;
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
extern int D_80188FB4;
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
extern unsigned int D_8018932C[];
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
extern void (*D_801893DC[])(void);
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
extern u16 D_8018940C[];
extern void func_80161C98(int param_1, u32 param_2);
extern void func_80161E08(s32);
extern s32 func_80162438(s32);
extern s32 D_800AE6A8;
extern void func_800D1734(void *);
extern s32 D_80189470;
extern void func_80161D88(void);
extern void func_80161E08(s32 param_1);
extern int func_800291DC(int);
extern int func_800D0E30(void *a0);
extern int func_801620C4(void);
extern s32 func_800D0D7C(s32, s32);
extern int D_801E5198[];
extern void func_8016216C(void);
extern s32 func_801621CC(s32 arg0);
extern void func_801622C4(void);
extern void (*D_80189494[])(void);
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
extern int D_801E51F0[];
extern void func_80162760(void);
extern void func_801627C0(void);
extern void (*D_801894DC[])(void);
extern void func_80162834(void *a0);
extern void func_8001CB6C(u8 *a0, s32 a1, s32 a2, s32 a3);
extern void func_80162968(s32 a0);
extern s32 func_80162ACC(u8 *a0);
extern u8 D_800B5CB8;
extern s32 D_801894CC;
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
extern char D_801E4A04[8];
extern void *memcpy(void *dst, const void *src, unsigned int n);
extern void func_801634D8(s32 param_1, u16 param_2, u16 param_3, s32 param_4, u16 param_5);
extern void func_80157158();
extern void func_80163664(s32 a0, u16 a1, u16 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, u16 a10, s32 a11, s32 a12);
extern void func_801636D0(s32 a0, s32 a1);
extern s32 func_8016380C(struct S8016380C *a0, s32 a1);
extern void *memcpy(void *dst, void *src, s32 n);
extern s32 func_801638A0(u8 *a0, s32 a1);
extern s32 func_80163950(s32 a0);
extern void (*D_801894E4[])(void);
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
extern void (*D_80189538[])(void);
extern void func_80164744(s32 param_1);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_80164A74(s32 *a0);
extern void func_80164930(s32 a);
extern u16 D_800DF2E0;
extern s32 D_80189500;
extern s16 D_80189534;
extern s16 D_80189532;
extern s16 D_80189530;
extern void func_801647A4(int param_1);
extern void func_80164ACC();
extern void func_80164864(void *a0);
extern void func_80164930(s32 param_1);
extern s32 func_8014C308(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80164ACC(s32 a0);
extern void (*D_80189544[])(void);
extern void func_80164BA0(void *a0);
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_80164DD0(s32 a0);
extern void func_80164DB0(void);
extern u8 D_801E5250;
extern u8 D_801E5251;
extern u8 D_801E5252;
extern u8 D_801E5253;
extern u8 D_801E5254;
extern u8 D_801E5255;
extern u8 D_801E5256;
extern u8 D_801E5257;
extern void func_80164BDC(s32 param_1);
extern void func_80164E40(void);
extern void func_80164CD4(u8 *a0);
extern void func_80164D4C(void *arg0);
extern void (*D_80189554[])(void);
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
extern s32 D_801E5290;
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
extern void (*D_80189598[])(void);
extern u8 func_80165658(s32 a0, s32 a1);
extern void func_800CAE0C(s32 a0);
extern void func_801654A8(s32 arg0);
extern void func_80165B28(void *a0);
extern void func_801655E4(s32 a0);
extern u8 D_80189614[];
extern s32 D_80189634[];
extern u8 D_801896B0[];
extern u8 func_801656D0(s32 a0, s32 a1);
extern u8 D_801896D0[];
extern u8 D_801896F0[];
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
extern void (*D_8018978C[])(void);
extern void func_80165B08(void);
extern void func_80165B10(void);
extern void func_80165B18(void);
extern void func_80165B20(void);
extern void (*D_80189808[])(void);
extern void func_80165BB4(u8 *a0);
extern void func_80165B6C(u8 *a0);
extern void func_80165C58(s32 arg0);
extern void func_80165BFC(void *a0);
extern void func_80165C78(void);
extern M2C_UNK D_801E4A14;
extern void func_80165E2C(u16 *arg0);
extern s32 func_80165FA4(s32 a0, s32 a1, s32 a2);
extern s32 func_80167DBC(s32 a0, s32 a1, s32 a2);
extern s32 func_80167AE0(s32 a0, s32 a1, s32 a2);
extern void func_80165E90(void);
extern void func_80020F34(s32 a0, s32 a1);
extern s32 func_80165FA4(s32 arg0, s32 arg1, s32 arg2);
extern void (*D_80189814[])(void);
extern void func_80166018(void *a0);
extern void func_80166054(s32 arg0);
extern void func_801661CC(s32 param_1);
extern void func_80166244(void* arg0);
extern void func_8016629C(void *a0);
extern void func_801662F4(void *a0);
extern void func_8016634C(void *a0);
extern void func_801663A4(void *a0);
extern void (*D_8018981C[])(void);
extern void func_801663FC(void *a0);
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
extern void (*D_801898E4[])(void);
extern void func_80166618(void *a0);
extern void (*D_801898F4[])(void);
extern void func_80166654(void *a0);
extern s32 func_80166690(s32 param_1, s32 param_2);
extern s32 func_80166994();
extern s32 func_80166F58(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern s32 func_80167540(s32 arg0);
extern void (*D_80189904[])(void);
extern void func_801678B4(void *a0);
extern void RotMatrixYXZ(void *a0, void *a1);
extern void func_80048EAC(void *a0, void *a1);
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);
extern void func_801678F0(s32 a0);
extern void (*D_80189910[])(void);
extern void func_80167A9C(void *a0);
extern void func_80167AD8(void);
extern s32 func_80167AE0(s32 param_1, s32 param_2, s32 param_3);
extern void func_80168070(s32 a0, s16 *a1, s16 *a2, void *a3);
extern u8   D_80189870[];
extern u8   D_80189884[];
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
extern void (*D_80189928[])(void);
extern void func_80168744(void *a0);
extern void func_80168BDC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_801687CC(s32 a0);
extern void func_80168780(s32 a0);
extern void func_80168828(void);
extern void func_801687CC(s32 param_1);
extern void func_80168828();
extern void (*D_80189930[])(void);
extern void func_801689D8(void *a0);
extern void func_80168A14(s32 *a0);
extern void func_80168A88(void);
extern void (*D_80189938[])(void);
extern void func_80168AA8(void *a0);
extern void func_80168AE4(s32 a0);
extern void func_800D2318(void);
extern void func_80168BDC(s32 param_1, s32 param_2, s32 param_3, s32 param_4);
extern void (*D_80189940[])(void);
extern void func_80168D58(void *a0);
extern void func_80168D94(int a0);
extern void func_80168F40();
extern void func_80168EC4(s32 a0);
extern void func_80168F40(void *arg0);
extern void (*D_80189948[])(void);
extern void func_8016901C(void *a0);
extern void func_80169058(s32 a0);
extern s32 func_80169228(void);
extern void func_801691B8(void *a0);
extern void (*D_80189950[])(void);
extern void func_801693CC(void *a0);
extern void func_80169584(s32 param_1);
extern void func_80169408(s32 a0);
extern void func_8016951C(int param_1);
extern s32 func_80017758(void *a0, void *a1);
extern s32  func_80017DC4(void *a0, void *a1);
extern void func_801696D8(s32 a0, s32 a1);
extern void (*D_80189958[])(void);
extern void func_80169830(void *a0);
extern void func_8016986C(s32 a0);
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_801699D0(void *arg0);
extern void (*D_80189A0C[])(void);
extern void func_80169B80(void *a0);
extern void func_80169E44(s32 a0);
extern void (*D_80189A14[])(void);
extern void func_80169F00(void *a0);
extern char D_801899C4[];
extern char D_80189984[];
extern void func_80169F3C(int param_1);
extern void func_80169FE0(s32 a0);
extern void (*D_80189A4C[])(void);
extern void func_8016A020(void *a0);
extern void func_8016A05C(void *a0);
extern void func_8016A290(s32 a, void *b, void *c);
extern void func_8016A08C(s32 param_1);
extern void func_8016A1CC(int param_1);
extern void func_8016A290(s32 param_1, void *param_2, void *param_3);
extern void (*D_80189A58[])(void);
extern void func_8016A700(void *a0);
extern s32 func_8016A73C(s32 arg0);
extern s32 func_8016A8FC(s32 a0);
extern void func_8016A890(s32 arg0);
extern void func_8016AA50(s32 param_1, s32 param_2);
extern void (*D_80189AA0[])(void);
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
extern void (*D_80189B1C[])(void);
extern void func_8016B4BC(void *a0);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B91C(int);
extern int D_801E55B0;
extern void func_8016B4F8(int param_1);
extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);
extern s16 D_80189B10[];
extern void func_8016B5C0(s32 param_1);
extern void func_8001CD9C(int, void *);
extern int *D_80189B54[];
extern unsigned short D_80189B5C[];
extern unsigned short D_80189B64[];
extern unsigned char D_801E55B8[];
extern int func_8016B834(int param_1, int param_2);
extern void func_8016B964(SrcB964 *a0, DstB964 *a1);
extern void func_8016B91C(s32 arg0);
extern s32 D_801E55B0;
extern s32 func_8016BA68(s32, s32);
extern void func_8016BADC(void *a0, s32 a1, s32 a2);
extern void (*D_80189B6C[])(void);
extern void func_8016BBA4(void *a0);
extern s32 func_8016BBE0(s32 param_1);
extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E56EC;
extern M2C_UNK D_801E56F0;
extern void func_8016BCC0(void *arg0);
extern s32 func_8016BD78(s32 param_1);
extern s32 func_8016BEA0(s32 param_1);
extern void func_8016BF34(void *a0);
extern void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern s32 D_801E5678;
extern void (*D_80189B9C[])(void);
extern void func_8016C14C(void *a0);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_801E56F4[];
extern u8 D_801E56FC[];
extern u8 D_801E56AC[];
extern void func_8016C2C4(s32 param);
extern s32 func_8016C49C(s32 param_1_arg);
extern s32 VectorNormalSS(void *a0, void *a1);
extern void func_8016C74C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern short func_8016CF04(s32 a0, s32 a1);
extern void func_8016C83C(s32 a0);
extern void (*D_80189BA4[])(void);
extern void func_8016CB84(void *a0);
extern short func_8016CF04(s32 param_1, s32 param_2);
extern void (*D_80189BC0[])(void);
extern void func_8016D19C(void *a0);
extern void (*D_80189BC8[])(void);
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
extern void (*D_80189C30[])(int);
extern void func_8016DA30(int param_1);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 D_80189BD4;
extern u8 D_80189BE0;
extern void func_8016DA7C(s32 param_1);
extern void func_8016DB34(s32 param_1);
extern void (*D_80189C64[])(void);
extern void func_8016DEA4(void *a0);
extern void func_8016DEE0(s32 a0);
extern void (*D_80189C6C[])(void);
extern void func_8016DF20(void *a0);
extern void func_8016E3CC(s32 a0);
extern void func_8016E1CC(s32 a0);
extern void func_8016E26C(s32 *a0);
extern void func_8016E2E8(void *a0);
extern void func_8016E460(void *a0, void *a1);
extern void func_8016E358(void *a0);
extern void func_8016E460(void *arg0, void *arg1);
extern void (*D_80189CC0[])(void);
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
extern u16 D_80189CF4[];
extern s32 func_8016EC0C(s32 a0, s32 a1);
extern void func_8016EAC0(Wave *param_1);
extern u8 D_80189CE4[];
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
extern s32 D_80189D10;
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
extern void (*D_80189D88[])(void);
extern void func_8016F6E0(void *a0);
extern s32 func_80171990(u8 *a0);
extern void func_8016F764(void *a0);
extern void func_8016F71C(u8 *a0);
extern void (*D_80189D90[])(void);
extern void func_8016F798(void *a0);
extern void func_8016F804(void *a0);
extern void func_8016F7D4(u8 *a0);
extern void func_80171928(void *);
extern void (*D_80189D98[])(void);
extern void func_8016F834(void *a0);
extern void func_8016F8AC(u8 *a0);
extern void func_8016F870(u8 *a0);
extern void func_80172358(u8 *a0, u8 *a1);
extern void (*D_80189DA0[])(void);
extern void func_8016F8E4(void *a0);
extern void func_8016F95C(void *a0);
extern void func_8016F920(u8 *a0);
extern s32 func_80171CC4(void *a0, void *a1);
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern u16 D_8011F73E;
extern void (*D_80189DA8[])(void);
extern void func_8016F9C4(void *a0);
extern void func_80171B44(s32 *a0);
extern void func_8016FA44(s32 a0);
extern void func_8016FA00(s32 a0);
extern s32 func_80171C64(s32 a0, s32 a1);
extern void (*D_80189DB0[])(void);
extern void func_8016FA84(void *a0);
extern void func_8016FB10(void *a0);
extern void func_8016FAC0(u8 *a0);
extern void func_8016FB50(void *a0);
extern void (*D_80189DBC[])(void);
extern void func_8016FB7C(void *a0);
extern void func_8016FC24();
extern void func_8016FBB8(s32 a0);
extern s32 func_80171B4C(s32 a0, s32 a1);
extern void func_8016FC24(s32 a0);
extern void func_8016FC64(void *a0);
extern void (*D_80189DC8[])(void);
extern void func_8016FC90(void *a0);
extern void func_8016FD08(u8 *a0);
extern void func_8016FCCC(u8 *a0);
extern s32 func_80172658(s32 *a0);
extern void func_8016FD08(u8 *s0);
extern void func_8016FD7C(s32 *a0);
extern void (*D_80189DD4[])(void);
extern void func_8016FDB4(void *a0);
extern void func_8016FE2C(u8 *a0);
extern void func_8016FDF0(u8 *a0);
extern void func_8016FE2C(u8 * a0);
extern s32 func_8016FE78(s32 *a0);
extern s32 func_80172664(s32 *a0);
extern void func_8016FED0(s32 *a0);
extern void (*D_80189DE4[])(void);
extern void func_8016FF30(void *a0);
extern void func_8016FFA8(u8 *a0);
extern void func_8016FF6C(u8 *a0);
extern void (*D_80189DF4[])(void);
extern void func_8016FFDC(void *a0);
extern void func_80170068(u8 *a0);
extern void func_80170018(u8 *a0);
extern void func_801700B8(u8 *a0);
extern void func_80170100(u8 *a0);
extern void (*D_80189DFC[])(void);
extern void func_80170150(void *a0);
extern void func_801701C8(u8 *a0);
extern void func_8017018C(u8 *a0);
extern void func_801701C8(u8 * a0);
extern void (*D_80189E04[])(void);
extern void func_80170240(void *a0);
extern void func_801702B8(s32 a0);
extern void func_8017027C(u8 *a0);
extern s16 func_80171AB0(s32 a0, void *a1);
extern void (*D_80189E0C[])(void);
extern void func_801702FC(void *a0);
extern void func_80170374(u8 *a0);
extern void func_80170338(u8 *a0);
extern s32 func_8014C168(s32 *a0, s32 a1);
extern void func_80170374(u8 * a0);
extern void (*D_80189E14[])(void);
extern void func_801703E0(void *a0);
extern void func_8017044C(u8 *a0);
extern void func_8017041C(u8 *a0);
extern void func_8017044C(u8 * a0);
extern void (*D_80189E1C[])(void);
extern void func_801704B0(void *a0);
extern void func_8017051C(void *a0);
extern void func_801704EC(u8 *a0);
extern void (*D_80189E24[])(void);
extern void func_80170548(void *a0);
extern void func_801705C0(u8 *a0);
extern void func_80170584(u8 *a0);
extern void func_801705C0(u8 * a0);
extern void (*D_80189E2C[])(void);
extern void func_801705F8(void *a0);
extern void func_80170670(void *a0);
extern void func_80170634(u8 *a0);
extern void func_8012A568(void (*a0)(void));
extern void (*D_80189E34[])(void);
extern void func_801706AC(void *a0);
extern void func_80170718(void *a0);
extern void func_801706E8(u8 *a0);
extern void func_80129FF4(void);
extern void (*D_80189E3C[])(void);
extern void func_80170748(void *a0);
extern void func_801707D4(void *a0);
extern void func_80170784(u8 *a0);
extern s32 func_80174ED4(void);
extern void (*D_80189E44[])(void);
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
extern void (*D_80189E4C[])(void);
extern void func_80170B14(int a0);
extern void func_80170B90(u8 *a0);
extern void (*D_80189E54[])(void);
extern void func_80170BD8(void *a0);
extern void func_80170C44(u8 *a0);
extern void func_80170C14(u8 *a0);
extern void (*D_80189E5C[])(void);
extern void func_80170C74(void *a0);
extern s32 func_8017197C(u8 *a0);
extern void func_80170CF0(void *a0);
extern void func_80170CB0(u8 *a0);
extern void (*D_80189E64[])(void);
extern void func_80170D68(void *a0);
extern void func_80170DE0(u8 *a0);
extern void func_80170DA4(u8 *a0);
extern s32 D_8011F73C;
extern s32 D_8011F740;
extern void func_801718AC(void *a0);
extern void func_80170DE0(u8 * _arg0);
extern void (*D_80189E6C[])(void);
extern void func_80170E34(void *a0);
extern void func_80170EAC(u8 *a0);
extern void func_80170E70(u8 *a0);
extern int func_800D0F8C(int a0);
extern void func_80170EAC(u8 * _arg0);
extern void (*D_80189E74[])(void);
extern void func_80170EFC(void *a0);
extern void func_80170F74(void *a0);
extern void func_80170F38(u8 *a0);
extern void (*D_80189E7C[])(void);
extern void func_80170FB0(void *a0);
extern void func_80171028(void *a0);
extern void func_80170FEC(u8 *a0);
extern void (*D_80189E84[])(void);
extern void func_80171064(void *a0);
extern void func_801710DC(u8 *a0);
extern void func_801710A0(u8 *a0);
extern u16 D_8011F73A;
extern void func_801710DC(u8 * arg0);
extern void (*D_80189E8C[])(void);
extern void func_80171120(void *a0);
extern void func_8017118C(u8 *a0);
extern void func_8017115C(u8 *a0);
extern void func_80142454(s32 a0);
extern void func_8017118C(u8 * a0);
extern void (*D_80189E94[])(void);
extern void func_801711C0(void *a0);
extern void func_80171238(void);
extern void func_801711FC(u8 *param_1);
extern void (*D_80189E9C[])(void);
extern void func_80171260(void *a0);
extern s32 func_80012F74(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80171384(void *a0);
extern void (*D_80189EA4[])(void);
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
extern void (*D_80189EE8[])(void);
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
extern M2C_UNK D_80189EAC;
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
extern void (*D_80189F18[])(void);
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
extern void (*D_80189F54[])(void);
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
extern void func_801748EC(void);
extern s32 func_801749C8();
extern s32 func_801749A8(s32 a0);
extern void func_80174BBC(void *a0);
extern void func_8012A0E0(void);
extern void func_80174BF4(void *a0);
extern void (*D_80189FAC[])();
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
extern void (*D_80189FBC[])(void*);
extern s32 func_80175268(s32);
extern void func_80175184(s32* arg0);
extern s32 func_80175218(void *a0);
extern void func_801751D8(void *a0);
extern void (*D_80189FC4[])(s32);
extern s32 func_80175218(void * param_1);
extern void func_801752BC(s32 *a0);
extern u8 D_8011F7A8;
extern u8 D_8011F7A9;
extern u8 D_8011F7AD;
extern u8 D_8011F7AE;
extern void func_80175414(s32 _arg0);
extern void func_80175494(void);
extern void (*D_8018A12C[])();
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
extern void (*D_8018A138[])();
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
extern M2C_UNK D_801E4C5C;
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
extern s16 D_801E6818;
extern int func_80178970(void);
extern s32 func_80178B18(s32 param_1, s32 param_2);
extern s32 func_80178B70(s32 param_1, s32 param_2);
extern void func_80178BB8(s32 a0, s32 a1);
extern s32 func_80178BF8();
extern s32 D_801E5E30;
extern short D_801E688C;
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
extern s32 D_801E625C;
extern void func_8017A094(s32 arg0);
extern void func_8017A0C4(s32 arg0);
extern void func_8017A0F4(void);
extern void func_8017A11C(void);
extern s32 D_801E6284;
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
extern s16 D_801E6240;
extern s32 func_8017A3B0(void);
extern short D_801E627C;
extern short D_801E6278;
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
extern s16 D_801E6244;
extern u16 D_801E62C4;
extern u16 D_801E62C6;
extern u16 D_801E62C8;
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
extern s16 D_801E62BC;
extern s16 D_801E62BE;
extern s16 D_801E62C0;
extern s16 D_801E62B4;
extern s16 D_801E62B6;
extern s16 D_801E62B8;
extern void func_8017B7A8(void);
extern s16 D_801E62D4;
extern s16 D_801E62D6;
extern s16 D_801E62D8;
extern s16 D_801E62DC;
extern s16 D_801E62DE;
extern s16 D_801E62E0;
extern void func_8017B824(void);
extern void func_8017B880(void);
extern s32 func_8017B8E8(s32 src);
extern short D_801E62CC;
extern short D_801E62CE;
extern short D_801E62D0;
extern void func_8017B940(void);
extern void func_8012F214(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(void *a0, void *a1, void *a2);
extern SV4 D_801E6264;
extern SV4 D_801E626C;
extern void func_8017BA3C(s32 param_1, s32 param_2);
extern s32 func_8017BB34(s32 param_1, s32 param_2);
extern void (*D_801E628C[10])(int);
extern void func_8017BC38(int param_1);
extern void func_8017B0E4(int, int);
extern void func_8017BCA0(int param_1);
extern void func_8012A4BC(void);
extern void func_8017BCF4(int param_1);
extern void (*D_801E6288)(void);
extern void func_8017BD50(int param_1);
extern void (*D_8018A314[])(void);
extern void func_8017BE60(void *a0);
extern void func_8017BE9C(void);
extern void func_8017BEA4(void);
extern void func_8017BEAC(void);
extern void func_8017BEB4(void);
extern void (*D_8018A32C[])(void);
extern void func_8017C0E4(void *a0);
extern void (*D_8018A3C8[])(void);
extern void func_8017C180(void *a0);
extern void (*D_8018A3D0[])(void);
extern void func_8017C1BC(void *a0);
extern void (*D_8018A3D8[])(void);
extern void func_8017C1F8(void *a0);
extern void (*D_8018A6B4[])(void);
extern void func_8017CF30(void *a0);
/* ==== end §8b carried decl layer ==== */

/* func_8017D604 — ov_SC01_000_after — TMD-style model renderer (952 ins, jr-function).
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

void func_8017D604(s32 arg0)
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



// @class: plumbing
// @stuck: none — MATCH (simple two-call wrapper, $s0 holds param across calls by default regalloc)

extern void func_8017EA50(void *arg0);
extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_800167B8(s32 a0);

s32 func_8017E4E4(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_8017EA50, 0x1000000);
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}



DEFINE_func_8017E534()  /* dedup: shared engine-core @0x8017E534 (src/shared) */



extern void func_8016EDEC(s32 a0, s32 a1, s32 a2);
extern void func_8017EAD8(void *a0);
extern s32 D_80126B9C;
extern u16 D_801270C0;

s32 func_8017E558(s32 param_1)
{
    ((void (*)(void *, s32))func_8016EDEC)(func_8017EAD8, 0x1000000);
    D_801270C0 = 2;
    D_80126B9C = D_80126B9C | 0x4000000;
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    *(s32 *)(param_1 + 0x28) = 0xA;
    return 0;
}



DEFINE_func_8017E5C8()  /* dedup: shared engine-core @0x8017E5C8 (src/shared) */


DEFINE_func_8017E678()  /* dedup: shared engine-core @0x8017E678 (src/shared) */



DEFINE_func_8017E698()  /* dedup: shared engine-core @0x8017E698 (src/shared) */


extern s32 func_800291B4(s32 arg);
extern void func_8001BFD0(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_800D0C48(s32 a0);
extern void func_800D1E28(void);

s32 func_8017E6EC(s32 param_1) {
    if ((*(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1) == -1) {
        func_800D1E28();
        func_8002D4C8(0x1C, 0);
        func_8001BFD0();
        if ((func_800291B4(0xCE) & 0xFF) == 0) {
            func_800D0C48(1);
        }
        *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    }
    return 0;
}


extern s32 func_80029504(void);
extern void func_8017F038(void);
extern void func_8017F528(void);
extern void func_800167B8(s32 a0);

s32 func_8017E770(s32 param_1)
{
    if (func_80029504() == 0x488) {
        func_8017F038();
    } else {
        func_8017F528();
    }
    func_800167B8(0);
    *(u8 *)(param_1 + 0x15) = *(u8 *)(param_1 + 0x15) + 1;
    return 0;
}




















extern void func_8017F7F0(void);
s32 func_8017E7D4(s32 arg0)
{
  s32 temp_v0;
 do { func_8017F7F0(); temp_v0 = (*((u8 *) (arg0 + 0x15))) + 1; *((u8 *) (arg0 + 0x15)) = temp_v0; } while (temp_v0 = 0);
  return temp_v0;
}


s32 func_8017E810(void) {
    return 0;
}


extern s32 D_80126B9C;

s32 func_8017E818(void *a0)
{
    D_80126B9C |= 0x4000000;
    *(s32 *)((s32)a0 + 0x28) = 0xA;
    *(u8 *)((s32)a0 + 0x15) += 1;
    return 0;
}


extern void func_800D1E28(void);
extern s32 func_800D1D94(void);
extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8001BFD0(void);

s32 func_8017E84C(s32 param_1) {

    extern s16 D_800B9A0A;
    s16 s0;

    if (--(*(s32 *)(param_1 + 0x28)) == -1) {
        func_800D1E28();
        s0 = D_800B9A0A;
        if (s0 != 0x1000 || (s16)func_800D1D94() != s0) {
            func_8002D4C8(0x1C, 0);
            func_8001BFD0();
            func_8002D4C8(0x1D, 0);
        }
        *(u8 *)(param_1 + 0x15) += 1;
    }
    return 0;
}


extern void func_800D1EBC(void);
    void func_8017E8F0(void) {
        func_800D1EBC();
    }



extern void (*D_8018A6D8[])(void);

void func_8017E910(void *a0) {
    D_8018A6D8[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_8018A6E0[])(void);

void func_8017E94C(void *a0) {
    D_8018A6E0[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_8018A6EC[])(void);

void func_8017E988(void *a0) {
    D_8018A6EC[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_8018A704[])(void);

void func_8017E9C4(void *a0) {
    D_8018A704[*(u8 *)((s32)a0 + 0x15)]();
}



extern void (*D_8018A70C[])(void);

void func_8017EA00(void *a0) {
    D_8018A70C[*(u8 *)((s32)a0 + 0x15)]();
}


extern s32 D_80127050;
    void func_8017EA3C(void) {
        D_80127050 = 1;
    }



extern void (*D_8018A838[])(void);

void func_8017EA50(void *a0) {
    D_8018A838[*(u8 *)((s32)a0 + 0x214)]();
}


void func_8017EA8C(u8 *a0) {
        *(u8 *)(a0 + 0x214) += 1;
    }


extern void func_80175414(s32 _arg0);
    extern void func_8016F0E4(void);
    extern void func_80165770(void);
    void func_8017EAA0(s32 param_1) {
        ((void (*)(void))func_80175414)();
        ((void (*)(s32))func_8016F0E4)(param_1);
        ((void (*)(s32))func_80165770)(param_1);
    }



extern void (*D_8018A840[])(void);

void func_8017EAD8(void *a0) {
    D_8018A840[*(u8 *)((s32)a0 + 0x214)]();
}


s32 func_8017EB14(u8 *a0)
{
    s32 v = a0[532] + 1;
    a0[532] = v;
    return v;
}


extern void func_8016F0E4(void);
void func_8017EB28(void) {
    func_8016F0E4();
}


extern void (*D_8018A860[])(void);

void func_8017EB48(void *a0) {
    D_8018A860[*(u8 *)((s32)a0 + 0x216)]();
}


extern void func_8017FED0(void);
extern void func_8014706C(void *arg0);
extern void func_8014708C(void *arg0);
extern s32 func_801472C8(struct S *a0);
extern void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80171990(u8 *a0);

void func_8017EB84(void *a0) {
    func_8017FED0();
    func_8014706C(a0);
    func_8014708C(a0);
    func_801472C8(a0);
    *(s32 *)((u8 *)a0 + 0x200) = 100;
    *(s16 *)((u8 *)a0 + 0x20C) = 1;
    *(s16 *)((u8 *)a0 + 0x20E) = 0;
    func_8017F818(a0, *(s16 *)((u8 *)a0 + 0x20C), *(s32 *)((u8 *)a0 + 0x200), 0);
    *(s32 *)((u8 *)a0 + 0x204) = 60;
    func_80171990((u8 *)a0);
}


extern s32 D_801151D4;
extern s32 func_80171990(u8 *);

void func_8017EBFC(void *a0) {
    s32 ptr;
    s16 val;
    s32 cnt;
    ptr = D_801151D4;
    val = *(u16 *)(ptr + 0x22) + 4;
    *(s16 *)(ptr + 0x22) = val;
    *(s16 *)(ptr + 0x1A) = val;
    cnt = *(s32 *)((u8 *)a0 + 0x204) - 1;
    *(s32 *)((u8 *)a0 + 0x204) = cnt;
    if (cnt == -1) {
        *(s32 *)((u8 *)a0 + 0x204) = 0x3C;
        *(s16 *)(ptr + 0x22) = 0x600;
        *(s16 *)(ptr + 0x1A) = 0x600;
        *(s32 *)(ptr + 0x14) = 0x384;
        *(s32 *)(ptr + 0x10) = 0x384;
        *(s16 *)(ptr + 0x2E) = 0x40;
        *(s16 *)(ptr + 0x28) = 0x40;
        *(s16 *)(ptr + 0x30) = -0x100;
        *(s16 *)(ptr + 0x2A) = -0x100;
        ((void (*)(void *))func_80171990)(a0);
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern void func_8017FE44(void);
extern s32 func_80171990(u8 *a0);
extern s32 D_801151D4;

void func_8017EC80(s32 a0) {
    register s32 v0 __asm__("$2");
    s32 v1;

    v1 = D_801151D4;
    v0 = *(u16 *)(v1 + 0x22) + 4;
    *(u16 *)(v1 + 0x22) = v0;
    *(s16 *)(v1 + 0x1A) = v0;

    v0 = *(s32 *)((u8 *)a0 + 0x204) - 1;
    *(s32 *)((u8 *)a0 + 0x204) = v0;
    if (v0 == -1) {
        func_8002D4C8(0xC4C, 0);
        func_8017FE44();
        func_80171990((u8 *)a0);
    }
}


extern void func_8017FD94(void);
extern s32 func_80171990(u8 *a0);
extern void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_8017F990();

void func_8017ECEC(void *a0)
{
    s32 v0;

    v0 = *(s32 *)((u8 *)a0 + 0x200) + 0xA;
    *(s32 *)((u8 *)a0 + 0x200) = v0;
    if (v0 >= 0x258) {
        *(s32 *)((u8 *)a0 + 0x200) = 0x64;
        func_8017FD94();
        func_80171990((u8 *)a0);
    }
    func_8017F818(a0, *(s16 *)((u8 *)a0 + 0x20C), *(s32 *)((u8 *)a0 + 0x200), 0);
    func_8017F990(a0, 0);
}


extern void func_8017F060(void);
extern void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_8017F990(s32 a0, s32 a1);
extern s32 func_80171990(u8 *a0);

void func_8017ED60(s32 arg0)
{
    func_8017F060();
    func_8017F818((void *)arg0, *(s16 *)(arg0 + 0x20C), *(s32 *)(arg0 + 0x200), 0);
    func_8017F990(arg0, 0);
    *(s32 *)(arg0 + 0x200) += 0xA;
    if (*(s32 *)(arg0 + 0x200) >= 0x258) {
        *(s32 *)(arg0 + 0x204) = 0xA0000;
        func_80171990((u8 *)arg0);
    }
}


extern void func_80129FF4(void);
extern void func_801805E0(void);
extern void func_8013C9C4(void *a0);
extern s16 func_8012A758(void);
extern void func_80015978(s32 a0, s32 *a1);
extern void func_80182CDC(void *a0, void *a1, s32 a2, s32 a3);
extern void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_8017F990();
extern s32 func_80171990(u8 *a0);
extern u8 D_8018A880[];
extern u16 D_8018A898[];

void func_8017EDD0(s32 arg0)
{
    struct { s16 x, y; } pos;
    s32 cnt;
    s16 r;
    s32 temp;

    if ((*(s32 *)(arg0 + 0x200) >= 0x2BC) && (*(s16 *)(arg0 + 0x20E) == 0)) {
        *(s16 *)(arg0 + 0x20E) = 1;
        func_80129FF4();
        func_801805E0();
        cnt = 0;
        func_8013C9C4(D_8018A880);
        r = func_8012A758() - 0x200;
        func_80015978(arg0 + 4, (s32 *)&pos);
        pos.x = pos.x - 0xC0;
        pos.y = pos.y + 0x80;
        do {
            func_80182CDC(&pos, D_8018A898, r, 2);
            if ((cnt & 1) != 0) {
                D_8018A898[1] = D_8018A898[1] + 0x30;
            } else {
                D_8018A898[1] = D_8018A898[1] - 0x30;
            }
            cnt++;
            r = r + 0x63;
        } while (cnt < 8);
    }
    func_8017F818((void *)arg0, *(s16 *)(arg0 + 0x20C), *(s32 *)(arg0 + 0x200), 0);
    func_8017F990(arg0, 0);
    temp = *(s32 *)(arg0 + 0x204) - 0x4000;
    *(s32 *)(arg0 + 0x204) = temp;
    if (temp <= 0xFFFF) {
        *(s32 *)(arg0 + 0x204) = 0x10000;
    }
    *(s32 *)(arg0 + 0x200) += *(s16 *)(arg0 + 0x206);
    if (*(s32 *)(arg0 + 0x200) >= 0x316) {
        *(s32 *)(arg0 + 0x200) = 0x1E;
        func_80171990((u8 *)arg0);
    }
}


extern s32 func_80171990(u8*);
void func_8017EF54(void *a0) {
    s32 v0 = *(s32 *)((u8 *)a0 + 0x200) - 1;
    *(s32 *)((u8 *)a0 + 0x200) = v0;
    if (v0 == -1) {
        ((void (*)(void *))func_80171990)(a0);
    }
}


extern s8 D_8018A8A0[];

void func_8017EF88(s32 a0) {
    extern void func_8017EFE0(void);
    s32 s0 = a0;
    func_8017EFE0();
    func_80147060((u8 *)s0);
    func_80147084((s32 *)s0);
    func_801472B4((void *)s0);
    func_80172310((u8 *)D_8018A8A0);
    func_80171928((void *)s0);
}


extern s32 func_8012E544(s32 arg);

void func_8017EFE0() {
    s32 v1;

    v1 = func_8012E544(0x19C);
    if (v1 != 0) {
        *(s16 *)(v1 + 0xFC) = 0;
    }

    v1 = func_8012E544(0x29A);
    if (v1 != 0) {
        *(s16 *)(v1 + 6) = -0x180;
        *(s16 *)(v1 + 10) = -0x380;
        *(s16 *)(v1 + 14) = 0x6A0;
    }
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern s32 D_8018A848;

void func_8017F038(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018A848, 0x1000000);
}


extern s32 D_801151D4;

void func_8017F060(void) {
    (*(s32 *)((s32)D_801151D4 + 0x14)) -= 8;
}



extern void (*D_8018A8C0[])(void);

void func_8017F080(void *a0) {
    D_8018A8C0[*(u8 *)((s32)a0 + 0x216)]();
}


extern void func_8014706C(void *arg0);
extern void func_8014708C(void *arg0);
extern s32 func_801472C8(struct S *a0);
extern void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80171990(u8 *a0);

void func_8017F0BC(void *a0) {
    func_8014706C(a0);
    func_8014708C(a0);
    func_801472C8(a0);
    *(s32 *)((u8 *)a0 + 0x200) = 100;
    *(s16 *)((u8 *)a0 + 0x20C) = 1;
    func_8017F818(a0, *(s16 *)((u8 *)a0 + 0x20C), *(s32 *)((u8 *)a0 + 0x200), 0);
    func_80171990((u8 *)a0);
}


extern void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_8017F990(s32 a0, s32 a1);
extern s32 func_80171990(u8 *a0);

void func_8017F120(s32 arg0)
{
    func_8017F818((void *)arg0, *(s16 *)(arg0 + 0x20C), *(s32 *)(arg0 + 0x200), 0);
    func_8017F990(arg0, 0);
    *(s32 *)(arg0 + 0x200) += 0xA;
    if (*(s32 *)(arg0 + 0x200) >= 0x258) {
        *(s32 *)(arg0 + 0x204) = 0xA0000;
        func_80171990((u8 *)arg0);
    }
}


extern void func_8017F818(void *, s32, s32, s32);
extern void func_8017F990(s32, s32);
extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80171990(u8*);

void func_8017F188(s32 a0)
{
    s32 temp;

    func_8017F818((void *)a0, *(s16 *)((u8 *)a0 + 0x20C), *(s32 *)((u8 *)a0 + 0x200), 0);
    func_8017F990(a0, 0);

    temp = *(s32 *)((u8 *)a0 + 0x204) - 0x4000;
    *(s32 *)((u8 *)a0 + 0x204) = temp;
    if (temp <= 0xFFFF) {
        *(s32 *)((u8 *)a0 + 0x204) = 0x10000;
    }

    *(s32 *)((u8 *)a0 + 0x200) += *(s16 *)((u8 *)a0 + 0x206);
    if (*(s32 *)((u8 *)a0 + 0x200) >= 0x316) {
        func_8002D4C8(0xBE5, 0);
        *(s32 *)((u8 *)a0 + 0x200) = 0x1E;
        func_80171990((u8 *)a0);
    }
}


extern s32 func_80171990(u8*);
void func_8017F220(void *a0) {
    s32 v0 = *(s32 *)((u8 *)a0 + 0x200) - 1;
    *(s32 *)((u8 *)a0 + 0x200) = v0;
    if (v0 == -1) {
        ((void (*)(void *))func_80171990)(a0);
    }
}


void func_8017F254(s32 a0) {
    extern void func_8017F2BC(void *a0);
    extern u8 D_8018A8D4[];
    extern void func_8017FB8C(void);
    s32 s0 = a0;
    func_8017F2BC(a0);
    func_80147060((u8 *)s0);
    func_80147084((s32 *)s0);
    func_801472B4((void *)s0);
    func_80172310(D_8018A8D4);
    func_8012A568(func_8017FB8C);
    func_80171928((void *)s0);
}


extern s32 func_8012E544(s32 arg);

void func_8017F2BC() {
    s32 v1;

    v1 = func_8012E544(0x19C);
    if (v1 != 0) {
        *(s16 *)(v1 + 0xFC) = 0;
    }

    v1 = func_8012E544(0x29A);
    if (v1 != 0) {
        *(s16 *)(v1 + 6) = -0x180;
        *(s16 *)(v1 + 10) = -0x380;
        *(s16 *)(v1 + 14) = 0x6A0;
    }
}



extern void (*D_8018A8DC[])(void);

void func_8017F314(void *a0) {
    D_8018A8DC[*(u8 *)((s32)a0 + 0x216)]();
}


void func_8017F350(s32 param) {
    if ((u32)(func_80029504() - 0x3B6) < 10) {
        func_80029514(0x3C0);
        func_80171990((u8 *)param);
    } else {
        func_80171928((void *)param);
    }
}


extern s32 D_801E31B4;
extern s32 func_8013767C(s32 a0);
extern s32 func_80171990(u8 *a0);

void func_8017F3A8(u8 *a0) {
    *(s32 *)(a0 + 0x198) = func_8013767C((s32)&D_801E31B4);
    func_80171990(a0);
}


extern s32 func_801399F0(s32);
extern void func_80139914(s32 a0);
extern void func_80142454(s32 a0);
extern void func_80171A80(s32 *a0, s32 a1);
extern s32 func_80171990(u8 *a0);

void func_8017F3E8(void *a0) {
    if (func_801399F0(*(s32 *)((u8 *)a0 + 0x198)) != 0) {
        func_80139914(*(s32 *)((u8 *)a0 + 0x198));
        ((void (*)(s32))func_80142454)(-0x80);
        ((void (*)(void *, s32))func_80171A80)(a0, 0x1E);
        ((void (*)(void *))func_80171990)(a0);
    }
    return;
}


extern void func_80154274(s32 *a0, s32 a1);
extern s32 func_8013767C(s32 a0);
extern s32 func_80171990(u8 *a0);
extern u8 D_800D599C[];
extern s32 func_80171A88(s32 a0);
extern void func_8014706C(void *arg0);
extern u8 D_801E3224;

void func_8017F448(s32 a0) {
    if (func_80171A88(a0) != 0) {
        func_8014706C((void *)a0);
        func_80154274((s32 *)a0, D_800D599C);
        *(s32 *)(a0 + 0x198) = func_8013767C(&D_801E3224);
        func_80171990((u8 *)a0);
    }
}


extern s32 func_801399F0(s32 a0);
extern void func_80139914(s32 a0);
extern void func_80171928(void *a0);

void func_8017F4AC(s32 a0) {
    s32 s0 = a0;
    if (func_801399F0(*(s32 *)(s0 + 0x198)) != 0) {
        func_80139914(*(s32 *)(s0 + 0x198));
        func_80171928((void *)s0);
    }
}


extern void func_80181A0C(void);
    extern void func_80171928(void *a0);
    void func_8017F4F8(s32 arg0) {
        func_80181A0C();
        ((s32 (*)(s32))func_80171928)(arg0);
    }


extern void func_8002D4C8(s32 arg0, s32 arg1);
extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018A8A8;

void func_8017F528(void) {
    func_8002D4C8(0xBE6, 0);
    ((void (*)(M2C_UNK *, s32))func_8016EE40)(&D_8018A8A8, 0x1000000);
}



extern void (*D_8018A900[])(void);

void func_8017F55C(void *a0) {
    D_8018A900[*(u8 *)((s32)a0 + 0x216)]();
}


extern void func_8014706C(void *arg0);
extern void func_8014708C(void *arg0);
extern s32 func_801472C8(struct S *a0);
extern void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_80171990(u8 *a0);

void func_8017F598(void *a0) {
    func_8014706C(a0);
    func_8014708C(a0);
    func_801472C8(a0);
    *(s32 *)((u8 *)a0 + 0x200) = 790;
    *(s32 *)((u8 *)a0 + 0x204) = 0;
    *(s16 *)((u8 *)a0 + 0x20C) = 1;
    func_8017F818(a0, 1, *(s32 *)((u8 *)a0 + 0x200), 0);
    *(s16 *)((u8 *)a0 + 0x20E) = 30;
    func_80171990((u8 *)a0);
}


extern s32 func_80171990(u8 *a0);

void func_8017F608(void *arg0) {
    s16 var;

    var = *(s16 *)((u8 *)arg0 + 0x20E) - 1;
    *(s16 *)((u8 *)arg0 + 0x20E) = var;
    if (var == -1) {
        *(s16 *)((u8 *)arg0 + 0x20E) = 0;
        func_80171990((u8 *)arg0);
    }
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern s32 func_80171990(u8 *a0);
extern void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3);
extern u8 D_8018A918[];

void func_8017F648(s32 a0) {
    register int p __asm__("$16");
    u16 v;
    int s1byte;

    p = a0;
    v = *(u16 *)((u8 *)p + 0x20E);
    (*(u16 *)((u8 *)p + 0x20E)) = v + 1;
    s1byte = D_8018A918[(s16)v];
    if (s1byte == 0) {
        func_8002D4C8(0xC27, 0);
        func_80171990((u8 *)p);
    }
    func_8017F818((void *)p, *(s16 *)((u8 *)p + 0x20C), *(s32 *)((u8 *)p + 0x200), s1byte);
}


extern s32 func_80171990(u8*);
extern void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_8017F990();

void func_8017F6C8(void *a0) {
    s32 v0;

    v0 = *(s32 *)((u8 *)a0 + 0x204) + 0x4000;
    *(s32 *)((u8 *)a0 + 0x204) = v0;
    if (v0 > 0xA0000) {
        *(s32 *)((u8 *)a0 + 0x204) = 0xA0000;
    }
    *(s32 *)((u8 *)a0 + 0x200) -= *(s16 *)((u8 *)a0 + 0x206);
    v0 = *(s32 *)((u8 *)a0 + 0x200);
    if (v0 < 0x259) {
        ((void (*)(void *))func_80171990)(a0);
    }
    func_8017F818(a0, *(s16 *)((u8 *)a0 + 0x20C), *(s32 *)((u8 *)a0 + 0x200), 0);
    func_8017F990(a0, 0x800);
}


extern s32 func_80171990(u8*);
extern void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_8017F990();

void func_8017F754(void *a0) {
    s32 v0;

    v0 = *(s32 *)((u8 *)a0 + 0x200) - 0xA;
    *(s32 *)((u8 *)a0 + 0x200) = v0;
    if (v0 < 0x6F) {
        ((void (*)(void *))func_80171990)(a0);
    }
    func_8017F818(a0, *(s16 *)((u8 *)a0 + 0x20C), *(s32 *)((u8 *)a0 + 0x200), 0);
    func_8017F990(a0, 0x800);
}


extern u8 D_800AE6BD;
extern void func_80171928(void *);

void func_8017F7BC(void) {
    D_800AE6BD++;
    ((void (*)(void))func_80171928)();
}


extern void func_8016EE40(s32 a0, s32 a1, s32 a2);
extern M2C_UNK D_8018A8F0;

void func_8017F7F0(void) {
    ((void (*)(void *, s32))func_8016EE40)(&D_8018A8F0, 0x1000000);
}


#include "common.h"

extern s16 D_8018A920;
extern s16 D_8018A922;
extern s16 D_8018A924;
extern s16 D_8018A928;
extern s16 D_8018A92A;
extern s16 D_8018A92C;

extern void func_80015954(s32 a0, s32 a1);
extern s32 func_8012E544(s32 arg);

void func_8017F818(void *a0, s32 a1, s32 a2, s32 a3) {
    struct {
        s16 x, y, z;
    } local;
    s32 v1;

    local.x = D_8018A928 + (D_8018A920 - D_8018A928) * a2 / 800;
    local.y = D_8018A92A + (D_8018A922 - D_8018A92A) * a2 / 800;
    local.z = D_8018A92C + (D_8018A924 - D_8018A92C) * a2 / 800;
    local.y = local.y + a3;

    func_80015954((s32)&local, (s32)a0 + 4);

    v1 = func_8012E544(0x19C);
    if (v1 != 0) {
        *(s32 *)(v1 + 4) = *(s32 *)((s32)a0 + 4);
        *(s32 *)(v1 + 8) = *(s32 *)((s32)a0 + 8);
        *(s32 *)(v1 + 0xC) = *(s32 *)((s32)a0 + 0xC);
        *(s16 *)(v1 + 0xFC) = (s16)a1;
    }

    v1 = func_8012E544(0x29A);
    if (v1 != 0) {
        *(s32 *)(v1 + 4) = *(s32 *)((s32)a0 + 4);
        *(s32 *)(v1 + 8) = *(s32 *)((s32)a0 + 8);
        *(s32 *)(v1 + 0xC) = *(s32 *)((s32)a0 + 0xC);
    }
}


extern void func_800139C8(s32 a0, void *a1, void *a2);
extern void func_80013E94(void *a0, void *a1);
extern u16 D_800B99DA;
extern void (*D_8018A930[])(void *);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);

void func_8017F990(s32 arg0, s32 arg1) {
    s32 buf[3];
    s32 t;

    func_800139C8(((arg1 + 0x555) << 16) >> 16, D_8018A930, buf);
    func_80013E94(buf, &buf[2]);
    t = buf[2] | 0x80000000;
    buf[2] = t;
    if ((D_800B99DA & 3) == 0) {
        func_80146A6C(6, arg0,
                      *(s16 *)((s32)arg0 + 6),
                      *(s16 *)((s32)arg0 + 0xA),
                      *(s16 *)((s32)arg0 + 0xE),
                      t, 0);
    }
}



extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017FF9C(u8*);


void func_8017FA20(void) {

    extern u8  D_80126948[];
    extern s32 D_80126950;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8  D_801269E8;
    u8 tmp = D_801269E8;

    D_80126954 = 0x1F4;
    D_80126950 = 0x1F4;
    D_8012695C = 0x4B0;
    D_80126968 = 0x238;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FF9C, 0);
    D_801269E8 = tmp;
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017FF9C(u8*);

void func_8017FAE4(void) {

    extern u8  D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;

    D_80126954 = 0x12C;
    D_8012695C = 0x384;
    D_80126968 = 0x38;
    D_8012696A = 0x900;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FF9C, 1);
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017FF9C(u8*);

void func_8017FB8C(void) {

    extern u8  D_80126948[];
    extern s32 D_80126950;
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern u8  D_801269E8;
    u8 tmp = D_801269E8;

    D_80126954 = 0x1F4;
    D_80126950 = 0x1F4;
    D_8012695C = 0x4B0;
    D_80126968 = 0x238;
    D_8012696A = 0;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FF9C, 0);
    D_801269E8 = tmp;
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
    D_801269E8 = 4;
    ((void (*)(void *))func_8017FF9C)(D_80126948);
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017FF9C(u8 *a0);

void func_8017FC74(void) {
    typedef struct { s8 c[8]; } Blk8;
    extern u8  D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern s16 D_80126940;
    extern s32 D_801274E8;
    extern s16 D_801269E4;
    extern s16 D_801269E6;
    s32 val;

    D_80126954 = 0x12C;
    D_8012695C = 0x384;
    D_80126968 = 0x38;
    D_8012696A = 0x900;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FF9C, 2);
    (*(Blk8 *)&D_801274E8) = (*(Blk8 *)&D_80126940);
    val = 0x5A;
    D_801269E6 = val;
    ((void (*)(void *))func_8017FF9C)(D_80126948);
    func_8012A094((s32)D_80126948);
    (*(Blk8 *)&D_801274E8) = (*(Blk8 *)&D_80126940);
    D_801269E4 = 0x40;
    D_801269E6 = val;
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017FF9C(u8*);


void func_8017FD94(void) {

    extern u8  D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;

    D_80126954 = 0x12C;
    D_8012695C = 0x384;
    D_80126968 = 0x71;
    D_8012696A = 0x800;
    D_80126976 = -0x30;
    D_8012696C = 0;
    D_80126978 = 0x80;
    D_8012697A = 0;
    func_8012A018((s32)func_8017FF9C, 1);
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
}


void func_8017FE44(void)
{
    extern void func_80129FF4(void);
    extern s32 D_80126950;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s32 D_80126998;
    extern s16 D_8018A938;
    extern s16 D_8018A93A;
    extern s16 D_8018A93C;
    extern s16 D_8018A940;
    extern s16 D_8018A942;
    extern s16 D_8018A944;

    D_80126950 = 0x12C;
    D_80126984 = D_8018A938;
    D_80126988 = D_8018A93A;
    D_8012698C = D_8018A93C;
    D_80126990 = D_8018A940;
    D_80126994 = D_8018A942;
    D_80126998 = D_8018A944;
    func_80129FF4();
}


extern void func_8012A018(s32 a, s32 b);
extern void func_8012A094(s32 a0);
extern void func_8017FF9C(u8 *a0);

void func_8017FED0(void) {
    extern u8  D_80126948[];
    extern s32 D_80126954;
    extern s32 D_8012695C;
    extern s16 D_80126968;
    extern s16 D_8012696A;
    extern s16 D_8012696C;
    extern s16 D_80126976;
    extern s16 D_80126978;
    extern s16 D_8012697A;
    extern s16 D_801274E8;
    extern s16 D_801274EA;
    extern s16 D_801274EC;

    D_80126954 = 0x190;
    D_8012695C = 0x76C;
    D_80126968 = 0x1C7;
    D_8012696A = 0x600;
    D_801274E8 = -0xC8;
    D_801274EA = -0x282;
    D_8012696C = 0;
    D_80126976 = 0;
    D_80126978 = 0;
    D_8012697A = 0;
    D_801274EC = 0x5F6;
    func_8012A018((s32)func_8017FF9C, 3);
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
    func_8012A094((s32)D_80126948);
    ((void (*)(void *))func_8017FF9C)(D_80126948);
}


extern void (*D_8018A948[])(void);

void func_8017FF9C(u8 *a0) {
    D_8018A948[a0[0x4]]();
}


extern void func_801800E0(void *a0, u8 *a1);
extern void func_80180220(s32 arg0, s32 arg1);
extern s16 D_80126940;

void func_8017FFD8(void *arg0) {
    func_801800E0(arg0, (u8 *) ((s32) arg0 + 0xA0));
    func_80180220((s32) arg0, (s32) &D_80126940);
}



extern void func_80180220(s32 arg0, s32 arg1);
extern s16 D_80126940;

void func_80180014(void *arg0) {
    func_80180220((s32) arg0, (s32) &D_80126940);
}




void func_8018003C(void *a0) {
    extern s16 D_80126940;
    extern s32 D_801274E8;
    if (*(s16 *)((s32)a0 + 0x9E) != 0) {
        (*(Blk8 *)&D_801274E8) = (*(Blk8 *)&D_80126940);
        *(s16 *)((s32)a0 + 0x9E) = *(u16 *)((s32)a0 + 0x9E) - 1;
    }
    func_80180220((s32)a0, (s32)&(*(Blk8 *)&D_801274E8));
}


extern void func_80180220(s32 arg0, s32 arg1);
extern s32 D_801274E8;

void func_801800B8(void *arg0) {
    func_80180220((s32)arg0, (s32)&D_801274E8);
}




extern u16 func_801487F4(s32 *a0);
extern u16 func_80148800(s32 *a0);
extern s32 func_80012A60(s32 a0, s32 a1);

void func_801800E0(void *a0, u8 *a1)
{

    extern s32 D_80126B58;
    extern s16 D_80186C50[];
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
        if ((s16)func_80012A60(*(s16 *)((s32)a0 + 0x1A), D_80186C50[dir]) < lim) {
            *a1 = dir;
        }
    }

    *(s16 *)((s32)a0 + 0x22) = D_80186C50[*a1];
}





extern s32 func_80012B04(s32 a0, s32 a1, s32 a2);
extern s32 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_80180220(s32 arg0, s32 arg1)
{
    MATRIX m1;
    SVECTOR svec_in;
    SVECTOR svec_out;
    s32 lim;

    lim = *(u16 *)(arg0 + 0x9C);

    {
        s32 delta = func_80012B04(*(s16 *)(arg0 + 0x1A), *(s16 *)(arg0 + 0x22), 0x14);
        if ((s16)delta > (s16)lim) {
            delta = lim;
        } else if ((s16)delta < -(s16)lim) {
            delta = -lim;
        }
        *(s16 *)(arg0 + 0x1A) = (*(u16 *)(arg0 + 0x1A) + delta) & 0xFFF;
        *(s16 *)(arg0 + 0x18) = func_80012ABC(*(s16 *)(arg0 + 0x18), *(s16 *)(arg0 + 0x20), 4);
    }

    *(s16 *)(arg0 + 0x1C) = func_80012ABC(*(s16 *)(arg0 + 0x1C), *(s16 *)(arg0 + 0x24), 4);
    *(s32 *)(arg0 + 0x8)  = (s16)func_80012C6C(*(s16 *)(arg0 + 0x8),  *(s16 *)(arg0 + 0xC),  4);
    *(s32 *)(arg0 + 0x10) = (s16)func_80012C6C(*(s16 *)(arg0 + 0x10), *(s16 *)(arg0 + 0x14), 4);
    *(s16 *)(arg0 + 0x28) = func_80012C6C(*(s16 *)(arg0 + 0x28), *(s16 *)(arg0 + 0x2E), 0x10);
    *(s16 *)(arg0 + 0x2A) = func_80012C6C(*(s16 *)(arg0 + 0x2A), *(s16 *)(arg0 + 0x30), 0x10);
    *(s16 *)(arg0 + 0x2C) = func_80012C6C(*(s16 *)(arg0 + 0x2C), *(s16 *)(arg0 + 0x32), 0x10);

    {
        *(s32 *)(arg0 + 0x48) = (s32)*(s16 *)(arg0 + 0x28) + *(s16 *)(arg1 + 0);
        *(s32 *)(arg0 + 0x4C) = (s32)*(s16 *)(arg0 + 0x2A) + *(s16 *)(arg1 + 2);
        *(s32 *)(arg0 + 0x50) = (s32)*(s16 *)(arg0 + 0x2C) + *(s16 *)(arg1 + 4);
        func_80049CAC(arg0 + 0x18, (s32)&m1);

        m1.t[0] = *(s16 *)(arg0 + 0x28) + *(s16 *)(arg1 + 0);
        m1.t[1] = *(s16 *)(arg0 + 0x2A) + *(s16 *)(arg1 + 2);
        m1.t[2] = *(s16 *)(arg0 + 0x2C) + *(s16 *)(arg1 + 4);
    }
    svec_in.vx = 0;
    svec_in.vy = 0;
    svec_in.vz = *(s32 *)(arg0 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&m1, (s32)&svec_in, (s32)&svec_out);

    *(s32 *)(arg0 + 0x3C) = (s32)svec_out.vx;
    *(s32 *)(arg0 + 0x40) = (s32)svec_out.vy;
    *(s32 *)(arg0 + 0x44) = (s32)svec_out.vz;
}


extern void func_801812FC(void);
extern void func_80180644(s32 a0);
extern void func_801813E8(s32 a0);
extern void func_80181324(void);
extern s32 D_801870B4[];
extern s32 D_80187090[];
extern s32 D_801B3DC4;
extern s32 D_801B44DC;
extern s32 D_801CB724;
extern s16 D_8018A978;
extern s16 D_8018A97A;

void func_80180408(void *arg0) {
    s32 timer;
    u16 state;

    timer = *(s32 *)((s32)arg0 + 0x1C);
    state = *(u16 *)((s32)arg0 + 0x34);
    *(s32 *)((s32)arg0 + 0x1C) = timer + 1;
    switch (state) {
    case 0:
        if (timer + 1 == D_8018A978) {
            ((void (*)(s32, s32))func_801812FC)((s32)arg0, (s32)&D_801B3DC4);
        }
        break;
    case 1:
        if (timer + 1 >= D_8018A97A) {
            *(u16 *)((s32)arg0 + 0x34) = state + 1;
            func_80174E9C((s32)&D_801B44DC);
            ((void (*)(s32, s32))func_801812FC)((s32)arg0, (s32)&D_801CB724);
            *(s32 *)((s32)arg0 + 0x1C) = 0;
        }
        break;
    case 2:
        func_801813E8((s32)arg0);
        switch (*(s32 *)((s32)arg0 + 0x1C)) {
        case 0xAE:
        case 0xA1:
        case 0xC0:
            func_8013C9C4(D_801870B4);
            break;
        case 0xDA:
            func_8013C9C4(D_80187090);
            func_80181324();
            func_80183ABC();
            func_8002D4C8(0xBE2, 0);
            break;
        }
        if ((s16)func_80174ED4() != 0) {
            *(s32 *)((s32)arg0 + 0x1C) = 0;
            *(u16 *)((s32)arg0 + 0x34) = *(u16 *)((s32)arg0 + 0x34) + 1;
        }
        break;
    case 3:
        if (timer + 1 >= 0x5A) {
            func_80180644((s32)arg0);
        }
        break;
    }
    func_801808AC((s32)arg0);
    func_8002D4C8(4, 0x42E);
    func_8002D4C8(4, 0x406);
    func_8002D4C8(4, 0x407);
}


extern s32 func_8012E544(s32 arg);
extern void func_80029514(s32);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern int func_800D0CA0(int);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801805E0(void)
{
    s32 v1;

    v1 = func_8012E544(0x2C6);
    if (v1 != 0) {
        *(u16 *)(v1 + 0x34) += 1;
        *(s32 *)(v1 + 0x1C) = 0;
        func_80029514(0x492);
        func_8012C658(0x3BE, 0, 0);
        func_800D0CA0(1);
        func_8002D4C8(0xBDF, 0);
    }
}


void func_80180644(s32 arg0)
{
    extern void func_8017FB8C(void);
    extern void func_80129CF8();
    extern void func_8012E8A8(u8 *arg0);
    extern s32 D_801E6748;

    func_8017FB8C();
    func_80129CF8();
    *(s16 *)(arg0 + 2) = 3;
    *(s16 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x1C) = 0;
    *(s16 *)(arg0 + 0x98) = 0;
    func_8012E8A8(arg0);
    D_801E6748 = 1;
}


typedef struct {
    u8 pad0[0x18];
    u16 f18;
    u16 f1A;
    u16 f1C;
    u8 pad1[0xE];
    u16 f2C;
} Act_8018069C;

void func_8018069C(s32 a0) {
    extern s32 D_801E6748;
    extern s32 D_801AA594;
    extern u16 D_8018A960[];
    extern s32 D_801B3DC4;
    extern s32 D_801BBAB8[];
    extern s32 D_801C29C4[];
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32, s32);
    extern void func_8001D0E8(s32, s32, s32);
    extern void func_801812FC(void);

    s32 s1;
    s32 t;
    u16 v;

    s1 = func_80029504();
    if ((u32)(s1 - 0x44C) >= 0x46) {
        goto FAIL;
    }
    t = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = t;
    if (t == 0) {
    FAIL:
        func_8012CAE4((void *)a0);
        return;
    }
    func_8001C214(*(s32 *)(a0 + 0x20), (s32)&D_801AA594);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C) =
        (v = *(u16 *)(*(s32 *)(a0 + 0x20) + 0x2C), D_801E6748 = 0, v | 0x10);
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x18) =
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1A) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x1C) = 0x3000;
    *(u16 *)(*(s32 *)(a0 + 0x68) + 0xC) = 0x7FFF;
    if (s1 == 0x488) {
        *(u16 *)(a0 + 2) = 2;
        func_8012E8E0(a0, (s32)D_8018A960);
        ((void (*)(s32, s32))func_801812FC)(a0, (s32)&D_801B3DC4);
        *(s32 *)(a0 + 0x1C) = 0;
        *(u16 *)(a0 + 0x34) = 0;
        return;
    }
    *(u16 *)(a0 + 2) = 1;
    func_8012E8E0(a0, (s32)D_8018A960);
    v = *(u16 *)(a0 + 0xFC) ^ 1;
    *(u16 *)(a0 + 0xFC) = v;
    if (v != 0) {
        ((void (*)(s32, s32))func_801812FC)(a0, (s32)D_801BBAB8);
    } else {
        ((void (*)(s32, s32))func_801812FC)(a0, (s32)D_801C29C4);
    }
    *(s32 *)(a0 + 0x1C) = 0;
}


void func_801807E8(void *arg0) {
    extern void (*D_8018A97C[])(void);
    extern unsigned short D_801E6508;
    D_8018A97C[*(u16 *)((s32)arg0 + 0x2)]();
    D_801E6508++;
}


extern void (*D_8018A98C)(void);
extern u8 D_8018A994;
extern void *D_8018A99C;
extern void func_80180ACC(s32, s32, s32, s32);
extern s32 func_800133E4(s16 *, s16 *);
extern u8 D_80126B5C;
extern void func_8012F568(s32, s32, s32, s32, void *, u8 *);

void func_8018083C(s32 a0) {
    s32 r;
    func_80180ACC(a0, 1, &D_8018A98C, &r);
    if (func_800133E4((s16 *)&r, (s16 *)&D_80126B5C) < 0x4000) {
        func_8012F568(1, 0x4001, 0, 0x1E, &D_8018A99C, &D_8018A994);
    }
}


void func_801808AC(s32 arg0)
{
    extern s32 D_801BBAB8[];
    extern s32 D_801C29C4[];
    extern s16 D_801E6508;
    extern s16 *D_8018A9EC[];
    extern s32 D_8018A9C4;
    extern void func_801809B8(s32 arg0, s32 arg1, s32 arg2);

    s32 *tbl;
    s16 *p;
    s32 i;
    s32 j;
    s16 pad[3];

    tbl = *(s32 **)(arg0 + 0x90);
    __asm__ __volatile__("" :: "r"(arg0));
    i = 0;
    if (tbl == &D_801B3DC4) {
        goto found;
    }
    i = 1;
    if (tbl == D_801BBAB8) {
        goto found;
    }
    i = 2;
    if (tbl == D_801C29C4) {
        goto found;
    }
    i = 3;
    if (tbl != &D_801CB724) {
        return;
    }
found:
    p = D_8018A9EC[i];
    while (*p != -1) {
        if (D_801E6508 == (s16)*(u16 *)p) {
            if (D_8018A9C4 > 0) {
                j = 0;
                do {
                    func_801809B8(arg0, i, j);
                    j++;
                } while (j < D_8018A9C4);
            }
            return;
        }
        p++;
    }
}


extern s32 func_80132EF4(s32 a0, s32 a1);
extern s32 rand(void);
extern void (*D_8018A9A4[])(void *);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_801809B8(s32 arg0, s32 arg1, s32 arg2)
{
    s32 res;
    s32 tbl;

    res = func_80132EF4(arg0, 0x22);
    if (res == 0) {
        return;
    }
    if (*(s32 *)(res + 0x20) != 0) {
        *(u16 *)(*(s32 *)(res + 0x20) + 0x2C) = 0xC010;
    }
    *(s32 *)(res + 0x10) = (rand() & 0x7FFF) * 8 - 0x20000;
    *(s32 *)(res + 0x14) = (rand() & 0x7FFF) * 4 - 0x60000;
    *(s32 *)(res + 0x18) = (rand() & 0x7FFF) * 8 - 0x20000;
    *(s16 *)(res + 0x34) = 0x3001;
    *(s32 *)(*(s32 *)(res + 0x20) + 4) |= 0x50000000;
    tbl = (s32)D_8018A9A4 + arg1 * 8;
    *(s16 *)(res + 0x06) = *(u16 *)(tbl + 0);
    *(s16 *)(res + 0x0A) = *(u16 *)(tbl + 2);
    *(s16 *)(res + 0x0E) = *(u16 *)(tbl + 4);
    if (arg2 == 0) {
        func_8002D4C8((arg1 == 3) ? 0xBE1 : 0xC2C, 0);
    }
}


extern void func_80180BE0();
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32 a0, s32 a1, s32 a2);

void func_80180ACC(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    struct St80180ACC { s16 a[3]; u16 b[3]; } st;
    u16 v[3];
    s16 out[6];
    s32 r[4];

    ((void (*)(s32, s32, s32))func_80180BE0)(arg0, arg1, (s32)&st);
    v[0] = st.b[0];
    v[1] = st.b[1];
    v[2] = st.b[2];
    ((void (*)(s32, s32))func_80049CAC)((s32)v, (s32)out);
    r[1] = st.a[0];
    r[2] = st.a[1];
    r[3] = st.a[2];
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)out, arg2, arg3);
    if (*(u16 *)(*(s32 *)(arg0 + 0x20) + 0x2C) & 0x10) {
        *(s16 *)((s32)arg3 + 0) = *(s16 *)((s32)arg3 + 0) * *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x18) >> 12;
        *(s16 *)((s32)arg3 + 2) = *(s16 *)((s32)arg3 + 2) * *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) >> 12;
        *(s16 *)((s32)arg3 + 4) = *(s16 *)((s32)arg3 + 4) * *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1C) >> 12;
    }
}


typedef struct { u8 b[12]; } Blk12_80180BE0;

void func_80180BE0(s32 arg0, s32 arg1, s16 *arg2)
{
    s32 pad;
    s32 idx = arg1;
    u32 v;
    register u32 w asm("$2");
    u32 t4;
    u32 t5;
    u8 *p;
    register s16 *out asm("$8");

    __asm__("" :: "r"(&pad));
    v = *(u32 *)(*(s32 *)(arg0 + 0x90) + (*(s32 *)(arg0 + 0x94) << 3));
    if ((v & 0x1000000) != 0) {
        out = arg2;
        __asm__ __volatile__("" : "=r"(out) : "0"(out));
        p = (u8 *)((v & 0xFEFFFFFF) + idx * 8);
        out[0] = *(s8 *)(p + 3);
        out[1] = *(s8 *)(p + 4);
        out[2] = *(s8 *)(p + 5);
        w = *(u32 *)p;
        t4 = *(u8 *)(p + 1) | ((w & 0xF) << 8);
        t5 = ((w >> 16) & 0xFF) | ((w & 0xF0) << 4);
        out[4] = t4;
        out[5] = t5;
        out[3] = *(u16 *)(p + 6);
    } else {
        out = arg2;
        __asm__ __volatile__("" : "=r"(out) : "0"(out));
        *(Blk12_80180BE0 *)out = *(Blk12_80180BE0 *)(v + idx * 12);
    }
}


extern void func_80180D04(void *a0);
    void func_80180CE4(void) {
        ((void (*)(void))func_80180D04)();
    }




void func_80180D04(void *a0) {

    extern void (*D_8018AA00[])(void);
    D_8018AA00[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_80016714(void *a0, s32 a1);
extern void func_80181204();

extern s16 D_801E650C;
extern s16 D_801E6514;
extern s16 D_801E664C;

void func_80180D40(void *a0)
{
    s32 i;

    *(u16 *)((u8 *)a0 + 2) = *(u16 *)((u8 *)a0 + 2) + 1;
    *(u32 *)((u8 *)a0 + 0x1C) = 0;
    __asm__ __volatile__("" ::: "memory");
    func_80016714(&D_801E650C, 0x100);
    for (i = 0; i < 0x10; i++) {
        *(s16 *)((s32)&D_801E650C + (i << 4)) = 1;
        *(s16 *)((s32)&D_801E6514 + (i << 4)) = i;
    }
    func_80181204(i);
    D_801E664C = 0;
}


/* func_80180DBC (ov_SC05_018) — 189 ins.
 * Dispatch spelling: §256 goto-ladder in the target's own block order.
 * Tell: all three arm bodies sit AFTER the whole dispatch, reached by forward
 * branches whose delay slots hold the NEXT compare's constant
 * (`beq $v1,$s3` / slti-in-slot, `bnez` / `li 2`-in-slot, `beq` / `li 3`-in-slot)
 * and a trailing `j default`. A plain 3-case `switch` balances to a median tree
 * rooted at 2 (li 2 / beq first, 192 ins) and an if/else-if chain inlines arm 1
 * (187 ins); only the goto ladder reproduces the root-at-1 linear chain. */

typedef struct {
    s16 state; /* 0x0 */
    s16 cnt;   /* 0x2 */
    s16 x;     /* 0x4 */
    s16 y;     /* 0x6 */
    s16 lim;   /* 0x8 */
    s16 velo;  /* 0xA */
    s16 spd;   /* 0xC */
    s16 flag;  /* 0xE */
} Ent_801E650C;

extern s16 D_8018A9FC;
extern s16 D_8018A9FE;
extern s16 D_801E650C;
extern s32 D_801E660C;
extern u16 D_801E662C;
extern s16 D_801E664C;
extern s32 rand(void);
extern void func_80016714(void *a0, s32 a1);
extern void func_8012C218(void *a0);
extern s32 func_80181294(u16 a0, s32 a1);
extern void func_8018124C(void);
extern void func_801810B0();

void func_80180DBC(void *a0) {
    Ent_801E650C *p;
    s32 i;
    s32 t;

    t = *(s32 *)((s32)a0 + 0x1C) + 1;
    *(s32 *)((s32)a0 + 0x1C) = t;
    if (t >= D_8018A9FC) {
        if (t == D_8018A9FC) {
            D_801E664C = 0;
        } else if (t < D_8018A9FC + D_8018A9FE) {
            D_801E664C = ((t - D_8018A9FC) << 12) / D_8018A9FE;
            for (i = 0; i < 0x10; i++) {
                *(s16 *)((s32)&D_801E660C + i * 2) =
                    ((s32 (*)())func_80181294)(*(u16 *)((s32)&D_801E662C + i * 2), D_801E664C);
            }
            func_8018124C();
        } else {
            func_80016714(&D_801E650C, 0x100);
            func_8012C218(a0);
            return;
        }
    }
    p = (Ent_801E650C *)&D_801E650C;
    for (i = 0; i < 0x10; i++, p++) {
        if (p->state == 1) goto st1;
        if (p->state < 2) goto done;
        if (p->state == 2) goto st2;
        if (p->state == 3) goto st3;
        goto done;
    st1:
        p->cnt++;
        if (p->cnt >= p->lim * 2) {
            p->cnt = 0;
            p->state++;
            p->x = rand() % 280 - 140;
            p->y = rand() % 200 - 100;
            p->spd = (rand() & 0x3F) + 0x30;
        }
        goto done;
    st2:
        p->flag = 1;
        p->cnt++;
        p->velo = p->spd * p->cnt / 6;
        if (p->cnt >= 6) {
            p->cnt = 0;
            p->state++;
        }
        goto done;
    st3:
        p->flag = 1;
        p->cnt++;
    done:
        if (p->flag != 0) {
            func_801810B0(p);
        }
    }
}


/* func_801810B0 — POLY_FT4 (0x28 bytes) centred sprite emit.
 *
 * Levers that closed this one (previous attempt sat at closeness=47):
 *
 *  1. D_800A651C IS NOT `s32[]`.  The tail computes the index with
 *     `sll 2; addu; sll 2` = *20, i.e. a 5-word record.  Declaring it
 *     `extern struct { s32 a; s32 b[4]; } D_800A651C[];` at BLOCK scope
 *     (the proven src/800.c:3377/:5326 form — the card's fleet type
 *     ('s32','') is the scalar spelling engine_core.h's DEFINE_ macros use)
 *     supplied the two missing instructions and fixed idx 67..78.
 *
 *  2. The tpage store lands in the `beqz` DELAY SLOT only if the flag load
 *     PRECEDES it in source.  With `*(u16*)(prim+0x16) = tpage;` written
 *     before the `if`, sched1 cannot prove the store does not alias the
 *     global, so a store->load dependence pins the store first and reorg
 *     steals `addiu 0x2E` from the arm instead.  Hoisting the read into a
 *     local (`flag = D_801E664C;`) turns that into a load->store anti-dep:
 *     lui/lh/nop/beqz emit first and the `sh` sinks into the slot.
 *
 *  3. The UV and XY blocks are plain libgpu MACRO ORDER — setUV4
 *     (u0,v0,u1,v1,u2,v2,u3,v3) and setXY4 (x0,y0,x1,y1,x2,y2,x3,y3).
 *     Writing the stores in the order the *target emits* them (all v's
 *     then all u's / all y's then all x's) is the trap: that is the
 *     SCHEDULER's output, not the source.  Source = macro order; sched1
 *     regroups by shared constant/register on its own.  The declaration
 *     order of x/y/half is byte-irrelevant (all 6 permutations MATCH).
 */
void func_801810B0(s32 arg0)
{
    extern void *func_80010A08(s32 arg0);
    extern s32 GetClut(s32 a0, s32 a1);
    extern s32 GetTPage(s32 a0, s32 a1, s32 a2, s32 a3);
    extern s32 AddPrim(s32 a0, void *a1);
    extern struct { s32 a; s32 b[4]; } D_800A651C[];   /* block scope: stride 0x14 (§ src/800.c:3377) */
    s32 prim;
    s32 clut;
    s32 tpage;
    s32 flag;
    s32 x;
    s32 y;
    s32 half;

    if (*(s16 *)(arg0 + 0xA) <= 0) {
        return;
    }

    prim = (s32)func_80010A08(0x28);
    clut = GetClut(0x160, 0x140);
    *(u16 *)(prim + 0xE) = clut;
    tpage = GetTPage(0, 1, 0x2C0, 0x100);
    *(s32 *)(prim + 4) = 0x808080;
    *(u8 *)(prim + 3) = 9;
    *(u8 *)(prim + 7) = 0x2C;
    flag = D_801E664C;
    *(u16 *)(prim + 0x16) = tpage;
    if (flag != 0) {
        *(u8 *)(prim + 7) = 0x2E;
    }

    *(u8 *)(prim + 0xC) = 0x90;
    *(u8 *)(prim + 0xD) = 0x50;
    *(u8 *)(prim + 0x14) = 0xCF;
    *(u8 *)(prim + 0x15) = 0x50;
    *(u8 *)(prim + 0x1C) = 0x90;
    *(u8 *)(prim + 0x1D) = 0x8F;
    *(u8 *)(prim + 0x24) = 0xCF;
    *(u8 *)(prim + 0x25) = 0x8F;

    half = (s16)*(u16 *)(arg0 + 0xA) / 2;
    x = *(s16 *)(arg0 + 4);
    y = *(s16 *)(arg0 + 6);

    *(s16 *)(prim + 8) = x - half;
    *(s16 *)(prim + 0xA) = y - half;
    *(s16 *)(prim + 0x10) = x + half;
    *(s16 *)(prim + 0x12) = y - half;
    *(s16 *)(prim + 0x18) = x - half;
    *(s16 *)(prim + 0x1A) = y + half;
    *(s16 *)(prim + 0x20) = x + half;
    *(s16 *)(prim + 0x22) = y + half;

    AddPrim(D_800A651C[*(u16 *)&D_800B9A02].a + 0x28, (void *)prim);
}



void func_80181204(void) {
    u16 buf[4];
    extern u16 D_801E662C;
    extern void StoreImage(u16 *);
    buf[0] = 0x160;
    buf[1] = 0x140;
    buf[2] = 0x10;
    buf[3] = 0x1;
    ((void (*)(u16 *, u16 *))StoreImage)(buf, (u16 *)&(*(s32 *)&D_801E662C));
}


void func_8018124C(void) {
    u16 buf[4];
    extern s32 D_801E660C;
    extern void func_800599B8(u16 *);
    buf[0] = 0x160;
    buf[1] = 0x140;
    buf[2] = 0x10;
    buf[3] = 0x1;
    ((void (*)(u16 *, u16 *))func_800599B8)(buf, (u16 *)&D_801E660C);
}


#include "common.h"

s32 func_80181294(u16 a0, s32 a1) {
    register s32 scale __asm__("$2");
    s32 r;
    s32 g;
    s32 b;
    s32 rp;
    s32 gp;
    s32 bp;
    s32 t;
    s32 out;

    r = a0 & 0x1F;
    scale = 0x1000 - a1;
    rp = r * scale;
    g = (a0 >> 5) & 0x1F;
    gp = g * scale;
    b = (a0 >> 10) & 0x1F;
    bp = b * scale;

    r = (rp >> 12) & 0x1F;
    g = gp >> 7;
    t = (g & 0x3E0) | -0x8000;
    out = r | t;
    b = bp >> 2;
    return (out | (b & 0x7C00)) & 0xFFFF;
}


extern void func_8012A828(void);
void func_801812FC(void) {

    extern s16 D_801E6508;
    func_8012A828();
    D_801E6508 = 0;
}


typedef struct { u8 b[8]; } Blk8_80181324;

extern Blk8_80181324 D_8018AA14;
extern u16 D_8018AA1C[];
extern void func_80182CDC(void*, void*, s32, s32);

void func_80181324(void) {
    Blk8_80181324 local;
    s32 s1 = 0, s0 = 0;
    do {
        local = D_8018AA14;
        func_80182CDC(&local, D_8018AA1C, (s16)s1, 2);
        if ((s0 & 1) != 0)
            D_8018AA1C[1] += 0x30;
        else
            D_8018AA1C[1] -= 0x30;
        s0++;
        s1 += 0x80;
    } while (s0 < 0x20);
}


extern void func_8002D4C8(s32 a0, s32 a1);
extern u16 D_800B99DA;

void func_801813E8(s32 arg0) {
    u16 v;

    if (*(s32 *)(arg0 + 0x1C) < 0x90) {
        v = D_800B99DA % 0x18;
        if (v == 0) {
            func_8002D4C8(0xBDD, 0);
        }
        if (v == 0xC) {
            func_8002D4C8(0xBDE, 0);
        }
    }
}


void func_80181474(s32 *a0) {
    extern void func_801808AC();
    extern void func_8018083C(s32);
    extern void func_801812FC(void);
    extern void func_8012E8E0(s32 a0, s32 a1);
    extern u16 D_8018A960[];
    extern s32 D_801BBAB8[];
    extern s32 D_801C29C4[];
    u16 v;

    *(s32 *)((s32)a0 + 0x1C) = *(s32 *)((s32)a0 + 0x1C) + 1;
    func_801808AC(a0);
    ((void (*)(void *))func_8018083C)(a0);
    if (*(u16 *)((s32)a0 + 0x72) & 0x4000) {
        *(u16 *)((s32)a0 + 0x2) = 1;
        func_8012E8E0((s32)a0, (s32)D_8018A960);
        v = *(u16 *)((s32)a0 + 0xFC) ^ 1;
        *(u16 *)((s32)a0 + 0xFC) = v;
        if (v != 0) {
            ((void (*)(s32, s32))func_801812FC)((s32)a0, (s32)D_801BBAB8);
        } else {
            ((void (*)(s32, s32))func_801812FC)((s32)a0, (s32)D_801C29C4);
        }
        *(s32 *)((s32)a0 + 0x1C) = 0;
    }
}


void func_80181518(void) {
}

extern void func_8012E88C(s32);
extern void func_8012A828(void);
extern void func_8012E8E0(s32, s32);
extern short D_801CC330;
extern s32 D_8018AA24;

s32 func_80181520(void *arg0) {
    s32 s0 = (s32)arg0;
    *(u16 *)(s0 + 2) = 2;
    func_8012E88C(s0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801CC330);
    func_8012E8E0((s32)arg0, (s32)&D_8018AA24);
}


extern void (*D_8018AB24[])(void);

void func_80181570(void *a0) {
    D_8018AB24[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_801815AC(void *arg)
{
    register s32 q __asm__("$3");
    s32 ptr;
    u16 st;
    u16 val;

    ptr = *(s32 *)((s32)arg + 0x64);
    st = *(u16 *)(ptr + 0x2);
    switch (st) {
    case 2:
        if (func_8012BD14(ptr) > 0x9000) {
            return 0;
        }
        q = *(s32 *)((s32)arg + 0x64);
        val = 3;
        break;
    case 1:
        if (func_8012BD14(ptr) > 0x9000) {
            return 0;
        }
        q = *(s32 *)((s32)arg + 0x64);
        val = 4;
        break;
    default:
        return 0;
    }
    *(u16 *)(q + 0x2) = val;
    *(u16 *)(q + 0x34) = 0;
    func_80178BF8();
    return (s32)func_80172710;
}


extern void func_80184590(s32 arg0, s32 arg1);
    void func_80181648(void) {
        func_80184590(0x7, 0x16);
    }


extern void func_80181648(void);
extern s32 func_80181520(void *a0);
void func_8018166C(int param_1)
{
    if (((int (*)(void))func_80181648)() != 0) {
        ((void (*)(int))func_80181520)(param_1);
    }
}


extern s32 D_801E6650;
extern s32 func_8012E544(s32 arg);
extern void func_8012E8A8(u8 *arg0);
extern void func_8012E88C(s32);
extern void func_80181648(void);
extern s32 D_8018AA24;
extern void func_8018469C(void *a0, s32 a1);

void func_801816A4(void *arg0) {
    s32 s0 = (s32)arg0;

    if (D_801E6650 != 0) {
        if (func_8012E544(0x37C) != 0) {
            func_8012E8A8((u8 *)s0);
            return;
        }
        func_8012E88C(s0);
    }

    if (((int (*)(void))func_80181648)() != 0) {
        return;
    }

    *(s16 *)(s0 + 2) = 1;
    func_8018469C((void *)s0, (s32)&D_8018AA24);
}





s32 func_80181720(void) {
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801E6700;
    return !(D_801E6700 ^ 1);
}


extern void func_800D1724(s32);
void func_80181738(void) {

    extern s32 D_8018A7D4;
    ((s32 (*)(s32 *))func_800D1724)(&D_8018A7D4);
}


extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_80178CBC(s32 arg0, s32 arg1);
extern void func_8012E88C(s32);
extern void func_8012A828(void);
extern void func_8012E8E0(s32, s32);
extern void func_800D1724(s32);
extern s16 *D_8018AA6C;
extern s32 D_8018AA24;
extern s32 D_8018A7D4;
extern short D_801CC330;

void func_80181760(void *arg0)
{
    s32 v1;

    v1 = *(u16 *)((s32)arg0 + 0x34);
    switch (v1) {
    case 0:
        func_80178CBC((s32)arg0, (s32)&D_8018AA6C);
        *(u16 *)((s32)arg0 + 0x34) = 1;
        return;

    case 1:
        if (((s32 (*)(s32))func_80178970)((s32)arg0) == 0) {
            return;
        }
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(u16 *)((s32)arg0 + 0x2) = 2;
        func_8012E88C((s32)arg0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801CC330);
        func_8012E8E0((s32)arg0, (s32)&D_8018AA24);
        return;

    case 2:
        ((s32 (*)(s32 *))func_800D1724)(&D_8018A7D4);
        *(u16 *)((s32)arg0 + 0x34) = 3;
        return;
    }
}


void func_80181840(void *arg0) {
    extern void func_80178CBC(s32 arg0, s32 arg1);
    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern void func_8018469C(void *a0, s32 a1);
    extern s16 D_8018AAE4;
    extern s32 D_8018AA24;

    switch (*(u16 *)((s32)arg0 + 0x34)) {
    case 0:
        func_80178CBC((s32)arg0, (s32)&D_8018AAE4);
        *(u16 *)((s32)arg0 + 0x34) = 1;
        break;
    case 1:
        if (((s32 (*)(s32))func_80178970)((s32)arg0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            *(s16 *)((s32)arg0 + 0x2) = 1;
            func_8018469C(arg0, &D_8018AA24);
        }
        break;
    }
}


void func_801818D0(void *a0) {
    extern s32 D_801E6650;
    extern s32 func_80029504(void);
    extern void func_8012C1B8(void);
    extern void func_8012CAE4(void *a0);
    extern void func_8001C214(s32, s32);
    extern void func_8012E88C(s32);
    extern void func_8012A828(void);
    extern void func_8012E8E0(s32, s32);
    extern s32 D_801D571C;
    extern short D_801CC330;
    extern s32 D_8018AA24;
    extern s32 func_801815AC(void*);
    extern s32 func_801788B8(s32, s32);

    s32 t1;
    s32 t2;

    t1 = ((s32 (*)(void))func_80029504)();
    if (t1 < 0x3B6) goto fail;
    if ((u32)(t1 - 0x44C) < 0x33) goto fail;
    if (t1 == 0x488) {
        D_801E6650 = 1;
    } else {
        D_801E6650 = 0;
    }
    t2 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((char *)a0 + 0x20) = t2;
    if (t2 == 0) {
fail:
        func_8012CAE4(a0);
        return;
    }
    func_8001C214(t2, (s32)&D_801D571C);
    *(s16 *)((char *)a0 + 0x2) = 2;
    func_8012E88C((s32)a0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801CC330);
    func_8012E8E0((s32)a0, (s32)&D_8018AA24);
    *(s16 *)(*(s32 *)((char *)a0 + 0x68) + 0xC) = 0x7FFF;
    func_801788B8((s32)a0, (s32)func_801815AC);
}


extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(void);
extern void func_80184674(s32);
void func_801819B0(void *arg0) {

    extern short D_8018AB38;
    extern short D_801CC330;
    *(short *)((char *)arg0 + 0x2) = 2;
    *(short *)((char *)arg0 + 0x34) = 0;
    func_8012E8E0((s32)arg0, (s32)&D_8018AB38);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801CC330);
    func_80184674((s32)arg0);
}


extern s32 func_8012E544(s32 arg);
    void func_80181A0C(void) {
        s32 p = func_8012E544(0x37C);
        if (p != 0) {
            *(u16*)(p + 0x34) += 1;
        }
    }


extern s32 func_80029504(void);
extern void func_8012CAE4(void *a0);
extern s32 func_801841A0(void *a0, void *a1);
extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(void);
extern void func_80184674(s32);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_80181B80(void *a0);

void func_80181A48(void *arg0) {
    extern short D_8018AB38;
    extern short D_801CC330;
    extern u8 D_8018ACB4[1];
    extern void (*D_8018AB40)(void);

    s32 stage;

    stage = func_80029504();
    if ((u32)(stage - 0x44C) >= 0x46) {
        func_8012CAE4(arg0);
        return;
    }
    if (func_801841A0(arg0, &D_8018AB40) == 0) {
        return;
    }
    if (stage == 0x47E) {
        *(u16 *)((char *)arg0 + 2) = 2;
        *(u16 *)((char *)arg0 + 0x34) = 0;
        func_8012E8E0((s32)arg0, (s32)&D_8018AB38);
    } else if (stage == 0x488) {
        *(u16 *)((char *)arg0 + 2) = 3;
        *(u16 *)((char *)arg0 + 0x34) = 0;
        func_8012E8E0((s32)arg0, (s32)&D_8018ACB4);
    } else {
        *(u16 *)((char *)arg0 + 2) = 1;
        *(u16 *)((char *)arg0 + 0x34) = 0;
        func_8012E8E0((s32)arg0, (s32)&D_8018AB38);
    }
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801CC330);
    func_80184674((s32)arg0);
    *(s16 *)(*(s32 *)((char *)arg0 + 0x68) + 0xC) = 0x7FFF;
    *(s32 *)((char *)arg0 + 0xD4) = func_801788B8((s32)arg0, (s32)func_80181B80);
}



extern void (*D_8018AD74[])(void);

void func_80181B44(void *a0) {
    D_8018AD74[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_80181B80(void *a0)
{
    s32 ptr;
    u16 st;

    ptr = *(s32 *)((s32)a0 + 0x64);
    st = *(u16 *)((s32)ptr + 0x2);
    if (st != 2) {
        return 0;
    }

    if (func_8012BD14(ptr) >= 0x4001) {
        return 0;
    }

    {
        s32 p;
        u16 st2;
        p = *(s32 *)((s32)a0 + 0x64);
        st2 = *(u16 *)((s32)p + 0x34);
        st2++;
        *(u16 *)((s32)p + 0x34) = st2;
    }
    func_80178BF8();
    return (s32)func_80172710;
}


void func_80181BF4(void *arg0)
{
    extern s32 func_8012CB64(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern void func_80029514(s32);
    extern s32 func_80178B18(s32 param_1, s32 param_2);
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u8 D_8018AB74;
    s32 state;
    struct {
        u16 f0;
        u16 f1;
        u16 f2;
    } pos;

    state = *(u16 *)((s32)arg0 + 0x34);
    if (state != 1) {
        if (state < 2 && state == 0) {
            pos.f0 = D_80126B5E;
            pos.f1 = D_80126B62;
            pos.f2 = D_80126B66;
            if (func_8012CB64((s32)&pos, -0x380, -0x180, 0x40D, 0x60D) != 0) {
                *(u16 *)((s32)arg0 + 0x34) += 1;
                func_80178B18((s32)arg0, (s32)&D_8018AB74);
            }
        }
    } else {
        if (((s32 (*)(s32))func_80178970)((s32)arg0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            func_80029514(0x47E);
            func_801819B0(arg0);
        }
    }
}


void func_80181CC4(void *arg0) {
    extern void func_80178CBC(s32, s32);
    extern s32 func_80178970();
    extern void func_80178D18();
    extern void func_8012E8E0(s32, s32);
    extern void func_8012E88C(s32);
    extern void func_8012A828();
    extern void func_80184674(s32);
    extern short D_8018AC14;
    extern short D_8018AB38;
    extern short D_801CC330;

    switch (*(u16 *)((s32)arg0 + 0x34)) {
    case 0:
        break;
    case 1:
        func_80178CBC((s32)arg0, (s32)&D_8018AC14);
        *(u16 *)((s32)arg0 + 0x34) = *(u16 *)((s32)arg0 + 0x34) + 1;
        break;
    case 2:
        if (((s32 (*)(s32))func_80178970)((s32)arg0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            *(short *)((char *)arg0 + 0x2) = 2;
            *(short *)((char *)arg0 + 0x34) = 0;
            ((void (*)(s32, s32))func_8012E8E0)((s32)arg0, (s32)&D_8018AB38);
            func_8012E88C((s32)arg0);
            ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801CC330);
            func_80184674((s32)arg0);
        }
        break;
    }
}


extern s32 D_801E6748;
extern s32 func_800D0CE0(void);

s32 func_80181D88(void)
{
    if (D_801E6748 != 0 && func_800D0CE0() == 1) {
        return 1;
    }
    return 0;
}


void func_80181DCC(void *arg0)
{
    extern s32 func_80178B18(s32 param_1, s32 param_2);
    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern void func_8017FB8C(void);
    extern void func_80129CF8();
    extern void func_8012C218(void *arg0);
    extern s32 D_8018ACBC;

    switch (*(u16 *)((s32)arg0 + 0x34)) {
    case 0:
        break;

    case 1:
        func_80178B18((s32)arg0, (s32)&D_8018ACBC);
        *(u16 *)((s32)arg0 + 0x34) = *(u16 *)((s32)arg0 + 0x34) + 1;
        break;

    case 2:
        if (((s32 (*)(s32))func_80178970)((s32)arg0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            func_8017FB8C();
            func_80129CF8();
            func_8012C218(*(void **)((s32)arg0 + 0xD4));
            func_8012C218(arg0);
        }
        break;
    }
}


extern s32 func_80029504(void);
extern u8 D_80078EAE;

s32 func_80181E78(void) {
    s32 v1 = func_80029504();

    if ((u32)(v1 - 0x460) < 0x32) {
        return 0x89;
    }
    if ((u32)(v1 - 0x384) < 0x6E) {
        return 0x65;
    }
    if ((u32)(v1 - 0x64) < 0x1E) {
        return 0x28;
    }
    if (D_80078EAE == 1) {
        return 0xF;
    }
    return 0x10;
}


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);
extern s32 func_801842C0(void);
extern s32 func_80184828(void);
extern void func_80182018(s16 *a0);

s32 func_80181EEC(void *a0)
{
    u16 st;

    st = *(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2);
    switch (st) {
    case 2:
        if (((s32 (*)(void *))func_801842C0)(a0) == 0) {
            return 0;
        }
        if (*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x34) != 0) {
            return 0;
        }
        *(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x34) += 1;
        break;
    case 3:
        if (func_8012BD14(*(s32 *)((s32)a0 + 0x64)) >= 0x4001) {
            return 0;
        }
        if (*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x34) != 2) {
            return 0;
        }
        *(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x34) = 5;
        break;
    case 1:
        if (((s32 (*)(void *))func_801842C0)(a0) == 0) {
            return 0;
        }
        if (((s32 (*)(void))func_80184828)() != st) {
            return 0;
        }
        ((void (*)(s16 *))func_80182018)(*(s32 *)((s32)a0 + 0x64));
        break;
    default:
        return 0;
    }
    func_80178BF8();
    return (s32)func_80172710;
}


extern void func_8018469C(void *a0, s32 a1);
    extern short D_8018AD84;
    void func_80182018(short *a0) {
        *(short *)((char *)a0 + 0x2) = 0x4;
        *(short *)((char *)a0 + 0x34) = 0;
        func_8018469C(a0, &D_8018AD84);
    }


extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_8012E8A8(u8 *a0);

void func_80182048(void *arg0) {
    extern short D_8018AD84;
    *(short *)((char *)arg0 + 0x2) = 2;
    *(short *)((char *)arg0 + 0x34) = 0;
    func_8012E8A8((u8 *)arg0);
    func_8012E8E0((s32)arg0, (s32)&D_8018AD84);
}


extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(void);
extern void func_80184674(s32);
void func_8018208C(void *arg0) {

    extern short D_8018AD84;
    extern short D_801CC388;
    *(short *)((char *)arg0 + 0x2) = 3;
    *(short *)((char *)arg0 + 0x34) = 0;
    func_8012E8E0((s32)arg0, (s32)&D_8018AD84);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801CC388);
    func_80184674((s32)arg0);
}


void func_801820E8(void *a0)
{
    extern s32 func_801855C4(s32);
    extern s32 func_80184988(s32);
    extern void func_801848B8(s32, s32, s32, s32);
    extern void func_8018469C(void *, s32);
    extern void func_80178CBC(s32, s32);
    extern s32 func_801789AC(s32);
    extern void func_80178D18();
    extern void func_8012A828();
    extern void func_80184674(s32);
    extern u8 D_8019F638[];
    extern u8 D_8019F644;
    extern s16 D_8018AD84;
    extern void (*D_8018ADF4)(void);
    extern short D_801CC388;

    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        if (func_801855C4(1) == 0) {
            return;
        }
        func_801848B8((s32)a0, (s32)D_8019F638, 0, 0x40);
        *(u16 *)((s32)a0 + 0x34) = 1;
        return;
    case 1:
        func_801855C4(1);
        if (func_80184988((s32)a0) == 0) {
            return;
        }
        func_801848B8((s32)a0, (s32)&D_8019F644, 1, 0x40);
        *(u16 *)((s32)a0 + 0x34) = 2;
        *(u16 *)(*(s32 *)((s32)a0 + 0xCC) + 0x108) = 0;
        *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
        return;
    case 2:
        if (func_80184988((s32)a0) != 0) {
            *(u16 *)((s32)a0 + 0x34) = 3;
        }
        break;
    case 3:
        if (func_801855C4(1) == 0) {
            return;
        }
        *(u16 *)((s32)a0 + 0x34) = 4;
        func_801848B8((s32)a0, (s32)D_8019F638, 1, 0x40);
        return;
    case 4:
        func_801855C4(1);
        if (func_80184988((s32)a0) == 0) {
            return;
        }
        *(u16 *)((s32)a0 + 0x2) = 1;
        *(u16 *)((s32)a0 + 0x34) = 0;
        func_8018469C(a0, &D_8018AD84);
        return;
    case 5:
        (*(u16 *)((s32)a0 + 0x34))++;
        func_80178CBC((s32)a0, (s32)&D_8018ADF4);
        break;
    case 6:
        if (func_801789AC((s32)a0) == 0) {
            return;
        }
        ((void (*)(s32))func_80178D18)((s32)a0);
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)a0, (s32)&D_801CC388);
        func_80184674((s32)a0);
        *(u16 *)((s32)a0 + 0x34) = 2;
        break;
    }
}



extern void (*D_8018AE9C[])(void);

void func_80182290(void *a0) {
    D_8018AE9C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_801E6814;
extern s32 func_80184828(void);
extern void (*D_8018ADA8[])(void);

void func_801822CC() {
    s32 iVar1;

    iVar1 = func_80184828();
    *(void **)(D_801E6814 + 4) = (void *)D_8018ADA8[iVar1];
}


extern void func_80184590(s32, s32);

void func_80182304(void *arg0) {
    *(s32 *)(*(s32 *)((s32)arg0 + 0xCC) + 0xB0) = 2;
    if (func_80184828() != 1) {
        if (func_801845B4(5, 0, 5, 0x1E) != 0) {
            func_8018208C(arg0);
        } else if (((s32 (*)(s32, s32))func_80184590)(7, 0x15) != 0) {
            func_80182048(arg0);
        }
    }
}


void func_80182384(void *arg0) {
    extern void func_80178CBC(s32 arg0, s32 arg1);
    extern int func_80178970(void);
    extern void func_80178D18(void);
    extern void func_8018469C(void *a0, s32 a1);
    extern short D_8018AD84;
    extern short D_8018AE34;

    switch (*(u16 *)((s32)arg0 + 0x34)) {
    case 0:
        func_80178CBC((s32)arg0, (s32)&D_8018AE34);
        *(u16 *)((s32)arg0 + 0x34) = *(u16 *)((s32)arg0 + 0x34) + 1;
        break;
    case 1:
        if (((s32 (*)(s32))func_80178970)((s32)arg0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            *(s16 *)((s32)arg0 + 0x2) = 1;
            *(s16 *)((s32)arg0 + 0x34) = 0;
            ((void (*)(s32, s32))func_8018469C)((s32)arg0, (s32)&D_8018AD84);
        }
        break;
    }
}


extern void func_80184590(s32, s32);
extern void func_8018469C(void *a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);
extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012E8A8(u8 *a0);
extern void func_8012E8E0(s32, s32);
extern s16 D_8018AD84;
extern short D_8018ADBC;

void func_80182420(void *arg0) {
    switch (*(u16 *)((s32)arg0 + 0x34)) {
    case 0:
        *(s32 *)(*(s32 *)((s32)arg0 + 0xCC) + 0xB0) = 2;
        if (((s32 (*)(s32, s32))func_80184590)(7, 0x15) == 0) {
            *(s16 *)((s32)arg0 + 0x2) = 1;
            *(s16 *)((s32)arg0 + 0x34) = 0;
            func_8018469C(arg0, &D_8018AD84);
        }
        break;
    case 1:
        *(u16 *)((s32)arg0 + 0x34) = *(u16 *)((s32)arg0 + 0x34) + 1;
        func_80178CBC((s32)arg0, (s32)&D_8018ADBC);
        break;
    case 2:
        if (((s32 (*)(s32))func_80178970)((s32)arg0) != 0) {
            ((void (*)(s32))func_80178D18)((s32)arg0);
            *(s16 *)((s32)arg0 + 0x2) = 2;
            *(s16 *)((s32)arg0 + 0x34) = 0;
            func_8012E8A8((u8 *)arg0);
            func_8012E8E0((s32)arg0, (s32)&D_8018AD84);
        }
        break;
    }
}


extern s32 func_801841A0(void *a0, void *a1);
extern void func_8018469C(void *a0, s32 a1);
extern s32 func_801788B8(s32 arg0, s32 arg1);
extern s32 func_80181EEC(void *a0);

void func_8018251C(void *param_1) {
    extern u8 D_8018AD94;
    extern short D_8018AD84;

    if (func_801841A0(param_1, &D_8018AD94) == 0) {
        return;
    }
    *(u16 *)((char *)param_1 + 2) = 1;
    *(u16 *)((char *)param_1 + 0x34) = 0;
    func_8018469C(param_1, &D_8018AD84);
    *(s16 *)(*(s32 *)((char *)param_1 + 0x68) + 0xC) = 0x7FFF;
    *(s32 *)((char *)param_1 + 0xD4) = func_801788B8((s32)param_1, (s32)func_80181EEC);
}



extern void (*D_8018B09C[])(void);

void func_8018258C(void *a0) {
    D_8018B09C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32  func_80029178(s32 a0);
extern void func_8012CAE4(void *a0);
extern void func_8012C1B8(void);
extern void func_8001C214(s32, s32);
extern void func_8012A828(void);
extern s32  func_801788B8(s32 arg0, s32 arg1);
extern void func_80182774(void);

void func_801825C8(void *arg0) {

    extern s32 D_801DCCD0;
    extern s32 D_8018AEB0;
    extern s32 D_8018AFB0;

    s32 v0;

    if ((func_80029178(0xF0) & 0xFF) == 0) {
        func_8012CAE4(arg0);
        return;
    }

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((char *)arg0 + 0x20) = v0;
    if (v0 == 0) {
        return;
    }

    func_8001C214(v0, (s32)&D_801DCCD0);
    *(s16 *)(*(s32 *)((char *)arg0 + 0x20) + 0x12) = 0xE00;
    ((void (*)(s32, s32))func_8012A828)((s32)arg0, (s32)&D_8018AEB0);
    *(s16 *)(*(s32 *)((char *)arg0 + 0x68) + 0xC) = 0x7FFF;
    *(s32 *)((char *)arg0 + 0x58) = (s32)&D_8018AFB0 | 0x40000000;
    *(s16 *)((char *)arg0 + 0x5C) = 0x800;
    *(s32 *)((char *)arg0 + 0xD4) = func_801788B8((s32)arg0, (s32)func_80182774);
    *(u16 *)((char *)arg0 + 0x2) += 1;
}


void func_80182694(void) {
}

extern s32 func_800291B4(s32 arg);
extern void func_800291A0(s32 a0, s32 a1);
extern void func_80178CBC(s32 a0, s32 a1);
extern s16 D_8018B00C[];
extern u8 D_8018AFC0[];
extern u8 D_8018B084[];

void func_8018269C(void *a0) {
    void *tbl;
    if ((func_800291B4(0x40) & 0xFF) == 1) {
        func_800291A0(0x40, 2);
    }
    if (*(s16 *)((char *)a0 + 0x10A) == 0) {
        *(s16 *)((char *)a0 + 0x10A) = 1;
        tbl = D_8018B00C;
        *(s32 *)((char *)a0 + 0x58) = (u32)D_8018AFC0 | 0x40000000;
    } else {
        tbl = D_8018B084;
    }
    func_80178CBC((s32)a0, (s32)tbl);
    *(u16 *)((char *)a0 + 2) += 1;
}



extern int func_80178970(void);
extern void func_80178D18(void);

void func_80182734(s32 a0) {
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)(a0);
        *(s16 *)(a0 + 2) = 1;
    }
}


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_80182774_body(void *a0) __asm__("func_80182774");

s32 func_80182774_body(void *a0)
{
    s32 ptr;
    u16 st;

    ptr = *(s32 *)((s32)a0 + 0x64);
    st = *(u16 *)((s32)ptr + 0x2);
    if (st != 1) {
        return 0;
    }

    if (func_8012BD14((s32)a0) >= 0x4000) {
        return 0;
    }

    {
        s32 p;
        u16 st2;
        p = *(s32 *)((s32)a0 + 0x64);
        st2 = *(u16 *)((s32)p + 0x2);
        st2++;
        *(u16 *)((s32)p + 0x2) = st2;
    }
    func_80178BF8();
    return (s32)func_80172710;
}



extern void (*D_8018B0AC[])(void);

void func_801827E8(void *a0) {
    D_8018B0AC[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 func_8012AD50(void *a0);
    void func_80182824(s32 *a0) {
        *(s16 *)((s32)a0 + 0xFC) = 0;
        ((void (*)(void))func_8012AD50)();
    }


typedef struct { u8 b[8]; } Blk8_80182844;

extern Blk8_80182844 D_801E4F60;
extern Blk8_80182844 D_801E4F68;
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8018290C();

void func_80182844(void *a0)
{
    Blk8_80182844 blk1;
    Blk8_80182844 blk2;
    Blk8_80182844 out;

    blk1 = D_801E4F60;
    blk2 = D_801E4F68;
    if (*(s16 *)((s32)a0 + 0xFC) == 0) {
        func_8018290C(&blk1, &blk2);
    } else {
        func_80015978((s32)a0 + 4, (s32 *)&out);
        func_8018290C(&blk1, &out);
        func_8018290C(&out, &blk2);
    }
}



/* identical layout to SVECTOR_8016E7C8 (src/shared/engine_types.h) */
typedef struct { short vx, vy, vz, pad; } SVEC_8017EC98_8018290C;

void func_8018290C(SVEC_8017EC98_8018290C *p0, SVEC_8017EC98_8018290C *p1) {
    /* conform to the TU's file-scope canon (`extern void func_8012EF70(s32, s32);`)
       and read the GTE flag through a cast at the call — the §138 "use is cast" lane. */
    extern void func_8012EF70(s32 a0, s32 a1);
    extern void func_80182BF4(void *a0, void *a1, void *a2, void *a3);

    SVEC_8017EC98_8018290C prev;
    SVEC_8017EC98_8018290C cur;
    SVEC_8017EC98_8018290C lo0;
    SVEC_8017EC98_8018290C lo1;
    SVEC_8017EC98_8018290C sv0;
    SVEC_8017EC98_8018290C sv1;
    SVEC_8017EC98_8018290C sv2;
    SVEC_8017EC98_8018290C sv3;
    s32 more;

    more = 1;
    cur = *p0;
    do {
        prev = cur;
        cur.vx += 0x40;
        cur.vy = p0->vy + (p1->vy - p0->vy) * (cur.vx - p0->vx) / (p1->vx - p0->vx);
        cur.vz = p0->vz + (p1->vz - p0->vz) * (cur.vx - p0->vx) / (p1->vx - p0->vx);
        if (cur.vx >= p1->vx) {
            cur.vx = p1->vx;
            more = 0;
        }
        lo0 = prev;
        lo0.vy -= 4;
        lo1 = cur;
        lo1.vy -= 4;
        if ((((s32 (*)(void *, void *))func_8012EF70)(&lo0, &sv0) & ~0x1000) == 0 &&
            (((s32 (*)(void *, void *))func_8012EF70)(&lo1, &sv1) & ~0x1000) == 0) {
            lo0 = prev;
            lo0.vy += 4;
            lo1 = cur;
            lo1.vy += 4;
            if ((((s32 (*)(void *, void *))func_8012EF70)(&lo0, &sv2) & ~0x1000) == 0 &&
                (((s32 (*)(void *, void *))func_8012EF70)(&lo1, &sv3) & ~0x1000) == 0) {
                func_80182BF4(&sv0, &sv1, &sv2, &sv3);
            }
        }
    } while (more);
}







void func_80182BF4(void *a0, void *a1, void *a2, void *a3)
{
    extern void func_80016ED4(void *a0);
    extern s32 D_8018B0B4;
    extern s32 D_8018B0B8;
    extern s32 D_8018B0BC;
    extern s32 D_8018B0C0;

    Prim_8016E7C8 prim;

    prim.v[0] = *(SVECTOR_8016E7C8 *)a0;
    prim.v[1] = *(SVECTOR_8016E7C8 *)a1;
    prim.v[2] = *(SVECTOR_8016E7C8 *)a2;
    prim.v[3] = *(SVECTOR_8016E7C8 *)a3;
    prim.f0 = D_8018B0B4;
    prim.f1 = D_8018B0B8;
    prim.f2 = D_8018B0BC;
    prim.f3 = D_8018B0C0;
    prim.f4 = 0x808080;
    prim.f5 = 0;
    prim.f6 = 0x50;
    func_80016ED4(&prim);
}


extern void ApplyMatrixSV(void *a0, void *a1, void *a2);
extern void RotMatrixYXZ(void *a0, void *a1);
extern s32 rand(void);

/* Old-style (K&R) definition on purpose: this TU already prototypes
 * `extern void func_80182CDC(void*, void*, s32, s32);` (twice, above), and the
 * asm truncates both a2 and a3 to 16 bits.  A prototyped `s16` definition is a
 * conflicting type (§376/§378); the K&R form's default argument promotions make
 * `s16` compatible with the declared `s32` while still emitting the entry
 * sll/sra sign-extension of a3.  Shape from the banked twin ov_SC03_002:
 * func_8017F068 (§193-A) — params used DIRECTLY, no local copies: any local
 * `base/src/ctr = argN;` copy reorders the four prologue sw/addu pairs. */
void func_80182CDC(a0, a1, a2, a3)
void *a0;
void *a1;
s16 a2;
s16 a3;
{
    extern u8 *func_8012913C(s32 a0);
    s16 i;
    s16 rot[4];
    s32 mtx[8];
    u8 *ent;

    i = 0;
    if (0 < a3) {
        do {
            ent = func_8012913C(0x46);
            if (ent != 0) {
                rot[0] = (rand() & 0x7F) * 8 + 0xF00;
                rot[1] = a2 + ((rand() & 0x7F00) >> 5);
                rot[2] = 0;
                RotMatrixYXZ(rot, mtx);
                ApplyMatrixSV(mtx, a1, rot);
                *(u16 *)(ent + 6) = *(u16 *)a0 + rot[0];
                *(u16 *)(ent + 10) = *(u16 *)((u8 *)a0 + 2) + rot[1];
                *(u16 *)(ent + 14) = *(u16 *)((u8 *)a0 + 4) + rot[2];
                *(s32 *)(ent + 0x10) = rot[0] << 12;
                *(s32 *)(ent + 0x14) = rot[1] << 12;
                *(s32 *)(ent + 0x18) = rot[2] << 12;
            }
            i = i + 1;
        } while (i < a3);
    }
}



extern void (*D_8018B0C4[])(void);

void func_80182E38(void *a0) {
    D_8018B0C4[*(u16 *)((s32)a0 + 0x2)]();
}



extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);

void func_80182E74(s32 arg0) {

    extern u8 D_800D387C[];
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
    *(s16 *)(arg0 + 0x2C) = 0x20;
    *(s16 *)(arg0 + 0x2) += 1;
}


struct vec;

void func_80182F04(s32 *a0)
{
    extern void func_801292C8(u8 *a0);
    extern void func_8012931C(struct vec *a0);
    s32 p;

    p = *(s32 *)((s32)a0 + 0x20);
    if (--*(s16 *)((s32)a0 + 0x2C) == -1) {
        func_801292C8((u8 *)a0);
        return;
    }
    func_8012931C((struct vec *)a0);
    *(u8 *)((s32)p + 0x24) = *(u8 *)((s32)p + 0x25) = *(u8 *)((s32)p + 0x26) =
        *(u8 *)((s32)p + 0x26) - 2;
}




void func_80182F78(s32 arg0)
{
    extern u8 * func_8012913C(s32 a0);
    typedef struct {
        u32 unk00; u32 unk04; u32 unk08; u32 unk0C; u32 unk10; u32 unk14;
        u16 unk18;
    } Rec_80189334;
    extern Rec_80189334 D_8018B0CC[];
    Rec_80189334 *src;
    u8 *temp;

    src = &D_8018B0CC[arg0];
    temp = func_8012913C(0x48);
    if (temp != 0) {
        *(u32 *)(temp + 0x04) = src->unk00;
        *(u32 *)(temp + 0x08) = src->unk04;
        *(u32 *)(temp + 0x0C) = src->unk08;
        *(u32 *)(temp + 0x10) = src->unk0C;
        *(u32 *)(temp + 0x14) = src->unk10;
        *(u32 *)(temp + 0x18) = src->unk14;
        *(u16 *)(temp + 0x2C) = src->unk18;
    }
}



extern void (*D_8018B180[])(void);

void func_80183018(void *a0) {
    D_8018B180[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_8018B174;
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);

void func_80183054(void *a0)
{
    s32 *s1 = (s32 *)a0;
    s32 *s0;
    s32 v0;
    s32 v1;

    s0 = M2C_FIELD(s1, s32 *, 0x20);
    ((void (*)(s32, s32, s32, s32))func_8001CC3C)((s32)s0, (s32)&D_8018B174, 0x240, 0x1D0);

    v0 = 0x54;
    *(u8 *)((s8 *)s0 + 0x27) = v0;
    v0 = *(s32 *)((s8 *)s0 + 0x4);
    v1 = 0x08000000;
    v0 |= v1;
    *(s32 *)((s8 *)s0 + 0x4) = v0;

    v0 = *(u16 *)((s8 *)s1 + 0x2C);
    *(u16 *)((s8 *)s0 + 0x1A) = v0;
    *(u16 *)((s8 *)s0 + 0x18) = v0;

    v0 = *(u16 *)((s8 *)s1 + 0x2);
    v1 = 0x20;
    *(u16 *)((s8 *)s1 + 0x2C) = v1;
    v0 += 1;
    *(u16 *)((s8 *)s1 + 0x2) = v0;
}


struct vec;

void func_801830D8(s32 *a0)
{
    extern void func_801292C8(u8 *a0);
    extern void func_8012931C(struct vec *a0);
    s32 p;

    p = *(s32 *)((s32)a0 + 0x20);
    if ((s16)--*(u16 *)((s32)a0 + 0x2C) == -1) {
        func_801292C8((u8 *)a0);
        return;
    }
    *(u16 *)(p + 0x14) += 0x155;
    func_8012931C((struct vec *)a0);
}



extern void (*D_8018B198[])(void);

void func_80183138(void *a0) {
    D_8018B198[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_8018B188;
extern s32 D_8019F630;
extern s32 func_80029504(void);
extern s32 func_8012AD50(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8012C1B8(void);

void func_80183174(a0)
s32 a0;
{
    s32 v0;
    s32 v1;
    s32 s0;

    v1 = func_80029504();
    v0 = v1 - 0x460;
    if ((u32)v0 < 0x28 || v1 < 0x3B6) {
        return;
    }

    s0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = s0;
    if (s0 == 0) {
        return;
    }

    func_8001C810(s0, (s32)&D_8019F630);
    *(s32 *)(s0 + 0x28) = 0xFA00FA;
    *(s32 *)(s0 + 4) |= 0x8000;
    *(u8 *)((s8 *)a0 + 0x75) = 2;
    *(s32 *)(a0 + 0x58) = (u32)&D_8018B188 | 0x40000000;
    *(u16 *)(a0 + 0x5C) = 0xC800;
    func_8012AD50((void *)a0);
}


void func_80183228(void) {
}


extern void (*D_8018B1D0[])(void);

void func_80183230(void *a0) {
    D_8018B1D0[*(u16 *)((s32)a0 + 0x2)]();
}




extern void func_80183588(void *arg0);
extern s32 func_8012AD50(void *arg0);

/* 0x24-stride record at D_801E6658 (4 entries; asm/ov_SC04_018/data/tail18.data.s) */


void func_8018326C(void *arg0) {

    extern u8 D_80078EB1;
    extern Ent_8017D6EC_8018326C D_801E6658[];
    s32 i;

    if (D_80078EB1 == 7) {
        for (i = 0; i < 4; i++) {
            Ent_8017D6EC_8018326C *p = &D_801E6658[i];

            p->unk16 = i;
            func_80183588(p);
            if (i & 1) {
                p->unk1C = 1;
            }
        }
        func_8012AD50(arg0);
    }
}






extern s32 func_8004787C(s32 a0);
extern void func_8012AD44(s32 *a0, s16 a1);
extern void func_80183538(void);
extern void func_80183644(void *arg0);

void aF801832FC(void *arg0) __asm__("func_801832FC");
void aF801832FC(void *arg0)
{

    extern u8 D_80078EB1;
    extern u8 D_80078E78[];
    extern u8 D_800AF630[];
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern Ent_8017D6EC_8017DEE8 D_801E6658[];
    u8 *m;
    u8 *e78;
    s32 k;

    m = D_800AF630;
    e78 = D_80078E78;

    if (D_80078EB1 >= 9) {
        s32 count;
        s32 i;
        u8 *base;

        base = (u8 *)D_801E6658;
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
        u8 *p = (u8 *)D_801E6658 + k * 0x24;
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
                        ((void (*)(void *))func_80183538)(p);
                    }
                }
            }
        }

        func_80183644(p);
    }
}




/* func_80183538 - iterate through 4-entry array, call func_80183588 if any unk1C is non-zero */

extern void func_80183588(void *arg0);




void func_80183538(void) {

    extern Ent_8017D6EC D_801E6658[];
    s32 i = 0;
    Ent_8017D6EC *p = &D_801E6658[0];

    while (i < 4) {
        if (p->unk1C != 0) {
            func_80183588(p);
            break;
        }
        i++;
        p = (Ent_8017D6EC *)((char *)p + 0x24);
    }
}



extern s32 rand(void);

void func_80183588(void *arg0) {

    extern void (*D_8018B1A0[])(void);
    s32 base = (s32)arg0;
    s32 r1;
    s32 r2;
    s32 h;
    s32 t;

    *(s32 *)(base + 0x0) = (s32)D_8018B1A0;
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




/* func_80183644 — build a 4-vertex SVECTOR quad from an 8-u16 source record,
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

void func_80183644(void *arg0)
{
    s32 a0 = (s32)arg0;
    Prim_8017DAC4_80183644 prim;
    Prim_8017DAC4_80183644 *q;
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




extern s32 func_80029504(void);
extern s32 D_801E6804;
extern void func_800D06CC(void);
extern void func_8013CB84(void);
extern void func_800D06E8(void);

void func_8018375C(void) {
    s32 temp = func_80029504();

    switch (D_801E6804) {
    case 0:
        if ((u32)(temp - 0x85) < 2U) {
            func_800D06CC();
        }
        D_801E6804++;
        break;
    case 1:
        func_8013CB84();
        func_800D06E8();
        break;
    }
}


#include "common.h"

extern s32 func_8012BEE8(s32 a0);
extern s32 func_80029504(void);
extern s32 rand(void);
extern void func_8012C218(void *arg0);

void func_801837E8(s32 a0) {
    s32 state;
    s32 fv;

    state = *(u16 *)(a0 + 0x34);
    if (state == 1) {
        goto case1;
    }
    if (state < 2) {
        if (state == 0) {
            goto case0;
        }
        goto tail;
    }
    if (state == 2) {
        goto case2;
    }
    if (state == 3) {
        goto case3;
    }
    goto tail;

case0: {
    if (func_8012BEE8(a0) == 0) {
        goto tail;
    }
    *(u16 *)(a0 + 0xFC) = 0;
    *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    fv = rand();
    fv = (fv & 0x1F) + 0x1E;
    goto store1c;
}

case1: {
    s32 v0;
    s32 p;
    v0 = *(u16 *)(a0 + 0xFC);
    p = *(s32 *)(a0 + 0x20);
    v0 = v0 + 6;
    *(u16 *)(a0 + 0xFC) = v0;
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + v0;
    if (func_8012BEE8(a0) == 0) {
        goto tail;
    }
    *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    goto randtail;
}

case2: {
    register s32 p __asm__("$2");
    s32 v0;
    v0 = *(u16 *)(a0 + 0xFC);
    p = *(s32 *)(a0 + 0x20);
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + v0;
    if (func_8012BEE8(a0) == 0) {
        goto tail;
    }
    *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) + 1;
    goto tail;
}

case3: {
    s32 v0;
    s32 p;
    v0 = *(u16 *)(a0 + 0xFC);
    p = *(s32 *)(a0 + 0x20);
    v0 = v0 - 3;
    *(u16 *)(a0 + 0xFC) = v0;
    *(u16 *)(p + 0x12) = *(u16 *)(p + 0x12) + v0;
    if (*(s16 *)(a0 + 0xFC) >= 9) {
        goto tail;
    }
    *(u16 *)(a0 + 0x34) = 0;
}

randtail:
    fv = rand();
    fv = (fv & 0x3F) + 0x3C;

store1c:
    *(s32 *)(a0 + 0x1C) = fv;

tail:
    if (!((u32)func_80029504() < 0x492)) {
        func_8012C218((void *)a0);
    }
}



extern void (*D_801A1068[])(void);

void func_80183960(void *a0) {
    D_801A1068[*(u16 *)((s32)a0 + 0x2)]();
}



extern void (*D_801A1088[])(void);

void func_8018399C(void *a0) {
    D_801A1088[*(u16 *)((s32)a0 + 0x2)]();
}


extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8012E8E0(s32 a0, s32 a1);

void func_801839D8(s32 a0) {

    extern s32 D_801A1060;
    extern s32 D_801A1070;
    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
    } else {
        func_8001C214(v0, 0);
        func_8012E8E0(a0, (s32)&D_801A1060);
        *(s32 *)(a0 + 0x58) = (s32)&D_801A1070 | 0x40000000;
        *(s16 *)(a0 + 0x5C) = 0xC00;
        *(s8 *)(a0 + 0x75) = 8;
        *(u16 *)(a0 + 2) += 1;
    }
}


extern s32 func_80029504(void);
extern void func_8012C218(void *arg0);
extern u16 D_801A1080[];

void func_80183A64(s32 a0) {
    *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = D_801A1080[*(s16 *)(a0 + 0x70)];
    if (!((u32)func_80029504() < 0x492)) {
        func_8012C218((void *)a0);
    }
}



extern s32 func_80029504(void);
extern void func_800183E0(s32 arg0);
extern char D_801A1090;

void func_80183ABC(void) {
    if (!(func_80029504() < 0x492)) {
        func_800183E0((s32)&D_801A1090);
    }
}


extern s32 func_80029504(void);
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8012E8E0(s32 a0, s32 a1);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);

void func_80183AF8(void *a0) {

    extern s32 D_801A13E0;
    extern s32 D_801A1060;

    s32 v0;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)((char *)a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4(a0);
        return;
    }

    func_8001C214(v0, (s32)&D_801A13E0);
    func_8012E8E0((s32)a0, (s32)&D_801A1060);
    func_80183ABC();

    if (!((u32)func_80029504() < 0x492)) {
        func_8012CAE4(a0);
        return;
    }

    func_8012C658(0x3BF, 0, (s32)a0);
    *(s16 *)((char *)a0 + 0x2) = 1;
    *(s16 *)((char *)a0 + 0x34) = 0;
    *(s32 *)((char *)a0 + 0x1C) = 0;
}


extern s32 D_801A10E4;
extern s32 D_801A1164;
extern s32 D_801DA908;
extern s32 D_801DAC58;
extern s32 func_8012B030(u8*);
extern void func_8012A828(void);
extern void func_8012B2CC(s32 a0);
extern void func_8012E88C(s32 a0);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_801848B8(s32 a0, s32 a1, s32 a2, s32 a3);

void func_80183B90(void *arg0) {
    s32 v0;

    *(short *)((char *)arg0 + 0x2) = 5;
    func_8012E8E0((s32)arg0, (s32)&D_801A1164);
    func_8012E88C((s32)arg0);
    ((void (*)(s32, s32))func_8012A828)((s32)arg0, (s32)&D_801DA908);

    v0 = (s32)&D_801A10E4 | 0x40000000;
    *(s32 *)((char *)arg0 + 0x58) = v0;
    *(short *)((char *)arg0 + 0x34) = 0;
    *(short *)((char *)arg0 + 0x5C) = 0x800;
    *(s32 *)((char *)arg0 + 0x1C) = 0;

    func_801848B8((s32)arg0, (s32)&D_801DAC58, 0x1, 0x60);
    ((void (*)(s32))func_8012B030)((s32)arg0);
    func_8012B2CC((s32)arg0);
}


extern s32 D_801A10B0;
extern s32 D_801A10E4;
extern s32 D_801DA908;
extern s32 D_801DAC58;
extern void func_8012A828(void);
extern void func_8012E88C(s32);
extern void func_8012E8E0(s32 a0, s32 a1);
extern void func_801848B8(s32 a0, s32 a1, s32 a2, s32 a3);

void func_80183C2C(arg0)
void *arg0;
{
    s32 v0;
    extern s32 D_801A10B0;

    *(short *)((char *)arg0 + 0x2) = 6;
    func_8012E8E0((s32)arg0, (s32)&D_801A10B0);
    func_8012E88C((s32)arg0);
    ((void (*)(s32, s32))func_8012A828)((s32)arg0, (s32)&D_801DA908);

    v0 = (s32)&D_801A10E4 | 0x40000000;
    *(s32 *)((char *)arg0 + 0x58) = v0;
    *(short *)((char *)arg0 + 0x5C) = 0x800;
    *(short *)((char *)arg0 + 0x34) = 0;
    *(s32 *)((char *)arg0 + 0x1C) = 0;

    func_801848B8((s32)arg0, (s32)&D_801DAC58, 0, 0x60);
}


#include "common.h"

/* func_80183CB8 — actor state-entry dispatcher (mass lane, head-crack).
 * Declarations copied verbatim from this TU's existing spellings (law 2):
 *   func_80029178   -> src line 372  "extern s32 func_80029178(s32 a0);"
 *   func_80029504   -> src line 4389 "extern s32 func_80029504(void);"
 *   func_8012CAE4   -> src line 4496 "extern void func_8012CAE4(void *a0);"
 *   func_801841A0   -> src line 4500 real definition "s32 func_801841A0(void *a0, void *a1)"
 *   func_8012A828   -> src line 4422 "extern void func_8012A828(void);" (cast at call site, §183.1/law 4)
 *   func_8012E88C   -> src line 4421 "extern void func_8012E88C(s32);"
 *   func_8012E8E0   -> src line 4420 "extern void func_8012E8E0(s32, s32);"
 *   func_8012E8A8   -> src line 4877 "extern void func_8012E8A8(u8 *a0);"
 *   func_80184590   -> src line 4451/4467 "extern void func_80184590(s32, s32);" (cast at call site,
 *                       same pattern as this TU's func_80183F9C/func_80183FDC neighbours)
 *   func_801788B8   -> src line 2514 "extern s32 func_801788B8(s32 arg0, s32 arg1);"
 *   D_801A10B0      -> src line 4427 "extern s32 D_801A10B0;" (block-scoped, T51/§103 style)
 * D_801A10C0, D_801A10D4, D_801DA3C0 have no prior TU spelling; typed s32 by address-only use.
 */

extern s32  func_80029178(s32 a0);
extern s32  func_80029504(void);
extern void func_8012CAE4(void *a0);
extern s32  func_801841A0(void *a0, void *a1);
extern void func_8012A828(void);
extern void func_8012E88C(s32);
extern void func_8012E8E0(s32, s32);
extern void func_8012E8A8(u8 *a0);
extern void func_80184590(s32, s32);
extern s32  func_801788B8(s32 arg0, s32 arg1);
extern void func_80183F28(void);

void func_80183CB8(void *a0) {

    extern s32 D_801A10C0;
    extern s32 D_801A10D4;
    extern s32 D_801DA3C0;
    extern s32 D_801A10B0;

    s32 s1;

    if ((func_80029178(0xF0) & 0xFF) != 0 ||
        (u32)(func_80029504() - 0x85) < 2) {
        func_8012CAE4(a0);
        return;
    }

    if (func_801841A0(a0, &D_801A10C0) == 0) {
        return;
    }

    *(s16 *)(*(s32 *)((char *)a0 + 0x68) + 0xC) = 0x7FFF;
    s1 = (s32)&D_801A10D4 | 0x40000000;
    *(s32 *)((char *)a0 + 0x58) = s1;
    *(s16 *)((char *)a0 + 0x5C) = 0x800;

    if (((s32 (*)(s32, s32))func_80184590)(9, 0x12) != 0) {
        *(s16 *)((char *)a0 + 0x2) = 2;
        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801DA3C0);
        func_8012E88C((s32)a0);
        func_8012E8E0((s32)a0, (s32)&D_801A10B0);
        *(s32 *)((char *)a0 + 0x58) = s1;
        *(s16 *)((char *)a0 + 0x5C) = 0x800;
    } else {
        *(s16 *)((char *)a0 + 0x2) = 1;
        *(s16 *)((char *)a0 + 0x98) = 0;
        func_8012E8A8((u8 *)a0);
        func_8012E8E0((s32)a0, (s32)&D_801A10B0);
        *(s32 *)((char *)a0 + 0x58) = s1;
        *(s16 *)((char *)a0 + 0x5C) = 0;
    }

    *(s32 *)((char *)a0 + 0xD4) = func_801788B8((s32)a0, (s32)func_80183F28);
}



extern void (*D_801A116C[])(void);

void func_80183DF0(void *a0) {
    D_801A116C[*(u16 *)((s32)a0 + 0x2)]();
}


extern s32 D_801A0DBC;
extern s32 D_801A0E38;
extern s32 D_801A0ED8;

void func_80183E2C(s32 a0)
{
    s32 s0;

    s0 = (u8)func_800291B4(0xDC);
    func_80029124(0xDE, 1);
    if (s0 == 0) {
        *(s32 *)(a0 + 0xE4) = (s32)&D_801A0DBC;
    } else {
        if (s0 & 1) {
            *(s32 *)(a0 + 0xE4) = (s32)&D_801A0E38;
        } else {
            *(s32 *)(a0 + 0xE4) = (s32)&D_801A0ED8;
        }
    }
    s0 = s0 + 1;
    if ((s0 & 0xFF) == 0) {
        s0 = 2;
    }
    func_800291A0(0xDC, s0 & 0xFF);
}




extern void func_8012E8E0(s32, s32);
extern void func_8012E88C(s32);
extern void func_8012A828(void);
extern void func_80178CBC(s32, s32);

void func_80183EC8(void *arg0) {

    extern s32 D_801A10B0;
    extern s32 D_801A1104;
    /* [T51] scoped in from file scope: a file-scope decl of these symbols constrains every
       LATER function in this TU, which blocks a byte-true decl of a different type.
       Declaration-only move (cookbook §103); the whole-binary byte-gate is the arbiter. */
    extern s32 D_801DAC10;
    *(short *)((char *)arg0 + 0x2) = 4;
    func_8012E8E0((s32)arg0, (s32)&D_801A10B0);
    func_8012E88C((s32)arg0);
    ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801DAC10);
    ((void (*)(s32 *, s32))func_80178CBC)((s32 *)arg0, (s32)&D_801A1104);
}


extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

s32 func_80183F28_body(void *a0) __asm__("func_80183F28");

s32 func_80183F28_body(void *a0)
{
    if (*(u16 *)(*(s32 *)((s32)a0 + 0x64) + 0x2) != 2) {
        return 0;
    }

    if (func_8012BD14((s32)a0) >= 0x4000) {
        return 0;
    }

    {
        s32 p;
        u16 st2;
        p = *(s32 *)((s32)a0 + 0x64);
        st2 = *(u16 *)((s32)p + 0x2);
        st2++;
        *(u16 *)((s32)p + 0x2) = st2;
    }
    func_80178BF8();
    return (s32)func_80172710;
}



/* func_80183F9C — guarded dispatch: ask ((s32 (*)(s32, s32))func_80184590)(9, 0x12); if it answers
 * NON-zero, run func_80183B90 on the incoming entity.  The entity pointer is
 * live across the jal, so it lands in $s0 and comes back out as $a0.
 * §71 sibling: func_80181B34 in this same TU is the identical shape.
 * §3-T4: target branch is `beqz $v0, ret` => the C condition is `!= 0`
 * (the sibling's is `bnez` => `== 0`; polarity is read off the opcode). */

extern void func_80184590(s32, s32);
extern void func_80183B90();

void func_80183F9C(void *arg0) {
    if (((s32 (*)(s32, s32))func_80184590)(9, 0x12) != 0) {
        func_80183B90(arg0);
    }
}



/* func_80183FDC — guarded dispatch: ask ((s32 (*)(s32, s32))func_80184590)(9, 0x12); if it answers
 * zero, run func_80183C2C on the incoming entity.  The entity pointer is live
 * across the jal, so it lands in $s0 and comes back out as $a0.
 * §3-T4: target branch is `bnez $v0, ret` => the C condition is `== 0`. */

extern void func_80184590(s32, s32);
extern void func_80183C2C(void *arg0);

void func_80183FDC(void *arg0) {
    if (((s32 (*)(s32, s32))func_80184590)(9, 0x12) == 0) {
        func_80183C2C(arg0);
    }
}


extern int func_80178970(void);
extern void func_80178D18(void);
extern void func_8012E88C(s32);
extern void func_8012A828(void);
extern void func_8012E8E0(s32, s32);

void func_8018401C(void *a0) {

    extern s32 D_801A10D4;
    extern s32 D_801DA3C0;
    extern s32 D_801A10B0;

    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)a0);
        *(short *)((char *)a0 + 0x2) = 2;
        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801DA3C0);
        func_8012E88C((s32)a0);
        func_8012E8E0((s32)a0, (s32)&D_801A10B0);
        *(s32 *)((char *)a0 + 0x58) = (s32)&D_801A10D4 | 0x40000000;
        *(short *)((char *)a0 + 0x5C) = 0x800;
    }
}


extern void func_8012A828(void);

void func_801840A0(void *a0)
{
    extern s32 D_801DA3C0;
    extern s32 D_801A10B0;
    extern s32 D_801A10D4;

    if (func_80184988(a0) != 0) {
        *(s16 *)((s32)a0 + 2) = 2;
        ((void (*)(s32, s32))func_8012A828)((s32)a0, (s32)&D_801DA3C0);
        func_8012E88C((s32)a0);
        func_8012E8E0((s32)a0, (s32)&D_801A10B0);
        *(s32 *)((s32)a0 + 0x58) = (s32)&D_801A10D4 | 0x40000000;
        *(s16 *)((s32)a0 + 0x5C) = 0x800;
    }
}


void func_80184118(void *a0) {

    extern s32 D_801A10D4;
    extern s32 D_801A10B0;

    if (func_80184988(a0) != 0) {
        *(short *)((char *)a0 + 0x2) = 1;
        *(short *)((char *)a0 + 0x98) = 0;
        func_8012E8A8((u8 *)a0);
        func_8012E8E0((s32)a0, (s32)&D_801A10B0);
        *(s32 *)((char *)a0 + 0x58) = (s32)&D_801A10D4 | 0x40000000;
        *(short *)((char *)a0 + 0x5C) = 0;
    }
}



void func_80184180(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 1;
    }


void func_80184190(void *a0) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xcc) + 0xb0) = 2;
    }



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern s32 func_8012E57C(s32 a0, s32 a1);

s32 func_801841A0(void *a0, void *a1) {

    extern u8 D_801E00B4;
    s32 v0;
    s16 val;

    if (a1 == 0) {
        a1 = (void *)&D_801E00B4;
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



















extern void func_8012A828(void);
void func_8018423C(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  ((void (*)(s32, s32))func_8012A828)(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0x4)));
}



















extern void func_8012A828(void);
void func_80184268(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  ((void (*)(s32, s32))func_8012A828)(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0x8)));
}



















extern void func_8012A828(void);
void func_80184294(void *a0)
{
  s32 v0 = *((s32 *) (((s32) a0) + 0xD0));
  ((void (*)(s32, s32))func_8012A828)(v0, *((s32 *) ((*((s32 *) ((v0 = (s32) a0) + 0xD0))) + 0xc)));
}




/* func_801842C0 — ov_SC04_018 (TU: src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c)
 *
 * DECL SURFACE (§37 / §124 asm-label alias):
 *   The TU already carries three fleet-canonical forward decls
 *     `extern s32 func_801842C0(void);`   (L5361, L5592, L5904 — all ABOVE the
 *   splice point at L6839), each used by a banked caller that invokes it with
 *   NO arguments (`if (func_801842C0() == 0)`).  The byte-true signature takes
 *   a pointer in $a0 (`lw $a2, 0x64($a0)` at 0x801848E4), so the definition
 *   disagrees with the canonical decl on arity -> cc1 emits
 *     "conflicting types for `func_801842C0'".
 *   Neither a fleet widen nor a cast-at-use fixes an arity clash on the symbol
 *   being DEFINED, so the definition is emitted under the C identifier
 *   `aF801848DC` with an __asm__("func_801842C0") label.  The C-level name
 *   never collides with the canonical decls, the emitted symbol is unchanged,
 *   and codegen is byte-identical (verified: match_one MATCH 33/33 with and
 *   without the alias).  Precedent in this very TU: aF8018CB18 @ L8872.
 *
 *   func_8012F2E8 / func_8012CB64 / D_80126B5E / D_80126B62 / D_80126B66 are
 *   reproduced VERBATIM from the TU's own decls (L7717-L7722, L7964-L7965,
 *   L8727-L8729) — identical types, so no second conflict hides behind the
 *   first.  No shared header is touched.
 *
 * BODY: the original draft discarded the func_8012CB64 result and returned a
 *   literal 0, which forced `move $v0,$zero` into the epilogue and displaced
 *   `addiu $sp,$sp,0x30` into the jr delay slot (DIFF 3/33 @ idx 9/30/32).
 *   The target sets $v0=0 in the *branch* delay slot and falls through to a
 *   bare epilogue after `jal func_8012CB64`, i.e. it RETURNS the callee's
 *   value on the taken path — the exact shape of the banked sibling
 *   func_80185D10 (TU L7724-L7733).  Early-return + tail-return reproduces it.
 *
 * ORACLE: .venv/bin/python tools/match_one.py func_801842C0 \
 *           --c .run/s7/ov_SC04_018/func_801842C0.c \
 *           --asm-subdir asm/ov_SC04_018/nonmatchings/ov_SC04_018_jr_8017AE2C
 */


extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CB64(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

s32 aF801848DC(void *a0) __asm__("func_801842C0");

s32 aF801848DC(void *a0) {

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    s16 out[3];
    s16 in[3];
    void *p;

    p = *(void **)((char *)a0 + 0x64);
    if (*(u16 *)(*(s32 *)((char *)p + 0xCC) + 0x2) != 0x2) {
        return 0;
    }

    in[0] = D_80126B5E;
    in[1] = D_80126B62;
    in[2] = D_80126B66;
    func_8012F2E8(*(s32 *)((char *)p + 0xCC), (s32)in, (s32)out);
    return func_8012CB64((s32)out, -0xC0, 0x40, -0x60, 0);
}



/* func_80184344 — 76 instructions */

extern s32 func_801844E8(s32 arg0);

s32 func_80184344(s32 a0) {

    extern u8 D_80078E78[];
    extern u8 D_80078EB1;
    extern u16 D_80078EAC;
    extern s32 D_801E66F8;
    extern s16 D_801E01C8[];
    extern s16 D_801E01FC[];
    extern s32 D_801E00C8[][8];
    u8 *p;
    s32 s0;
    s32 t;
    s32 q;
    s32 r;
    s32 b;
    s32 c;
    s32 idx;

    p = D_80078E78;
    s0 = D_801E01C8[*(s16 *)(*(s32 *)(a0 + 0xD0) + 0x10)];
    if (s0 == -1) {
        D_801E66F8 = 0;
        return 0;
    }

    t = func_801844E8(a0);
    q = t / 24;
    r = t % 24;
    b = D_80078EB1;
    c = D_80078EAC;

    if (t == 0) {
        idx = D_801E01FC[b] - 1;
    } else if (c - q >= 5) {
        idx = 7;
    } else if (c == q && b - r >= 2) {
        idx = 6;
    } else {
        idx = p[0x39];
        idx = D_801E01FC[idx] - 1;
    }

    ((struct { s32 w; } *)&D_801E66F8)->w = 1;
    return D_801E00C8[idx][s0];
}


extern s32 func_80184344(s32 arg);
extern void func_801844A8(s32 arg);

void func_80184474(void *a0) {
    *(s32 *)((char *)a0 + 0xe0) = func_80184344((s32)a0);
    func_801844A8((s32)a0);
}







void aF801844A8(void *a0) __asm__("func_801844A8");
void aF801844A8(void *a0)
{

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
    s32 func_801844E8(s32 arg0) {
        return *(short *)((char *)&D_800BA2BA + (*(short *)(*(s32 *)(arg0 + 0xd0) + 0x10) << 2));
    }



extern void (*D_801E022C[])(void);

void func_80184510(void *a0) {
    D_801E022C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_8018454C(void) {
}



void func_80184554(void *a0, s32 a1, s32 a2)
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







s32 aF80184590(s32 arg0, s32 arg1) __asm__("func_80184590");
s32 aF80184590(s32 arg0, s32 arg1)
{

    extern u8 D_80078EB1;
    return (D_80078EB1 >= arg0) && (D_80078EB1 < arg1);
}





s32 func_801845B4(u8 a0, u8 a1, u8 a2, u8 a3) {

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


void func_8018460C(void *a0, s32 a1)
{
    Vec4s_8018460C loc_10;
    Vec4s_8018460C loc_18;
    Vec4s_8018460C loc_20;

    loc_10.f0 = *(s16 *)((u8 *)a0 + 0x6);
    loc_10.f1 = *(s16 *)((u8 *)a0 + 0xA);
    loc_10.f2 = *(s16 *)((u8 *)a0 + 0xE);

    loc_18.f0 = 0;
    loc_18.f1 = 0;
    loc_18.f2 = (s16)(-a1);

    ((void(*)(s32, s32, s32))func_8012F214)((s32)a0, (s32)&loc_18, (s32)&loc_20);
    func_8012CEB0((s32)&loc_10, (s32)&loc_20, 0);
}





void func_80184674(s32 a0)
{

    extern s32 D_801E0234;
    *(s32 *)(a0 + 0x58) = (u32)&D_801E0234 | 0x40000000;
    *(s16 *)(a0 + 0x5C) = 0x800;
}


void func_80184694(void *a0) {
        *(s16 *)((s32)a0 + 0x5C) = 0;
    }





extern void func_8012E8A8(u8 *a0);
extern void func_8012E8E0(s32 a0, s32 a1);

void aF8018469C(s32 *a0, s32 a1) __asm__("func_8018469C");
void aF8018469C(s32 *a0, s32 a1)
{
    func_8012E8A8((u8 *)a0);
    *(s16 *)((s32)a0 + 0x98) = 0;
    *(s16 *)((s32)a0 + 0x5C) = 0;
    func_8012E8E0((s32)a0, a1);
}


extern s32 func_80029504(void);

s32 func_801846E4(void) {
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

s32 func_80184740(void) {
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

s32 func_801847B4(void) {
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

s32 func_80184828(void) {
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
    void func_80184884(void) {
        if (((s32 (*)(void))func_80029504)() == 0x3A2) {
            ((void (*)(s32))func_80029514)(0x3AC);
        }
    }




extern s32 func_8012B744(void *a0, void *a1);
extern void func_8012B200(u8 *a0);

void func_801848B8(s32 a0, s32 a1, s32 a2, s32 a3) {
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




/* func_80184988 @ 0x80184FA4 — ov_SC04_018_jr_8017AE2C
 * Decls copied verbatim from the TU (src/ov_SC04_018/ov_SC04_018_jr_8017AE2C.c):
 *   line 350   extern s32  func_8016F1AC(void);
 *   line 448   extern void func_8014B12C(void);      <- void! call through a cast (idiom 9)
 *   line 2616  extern s32  func_8012B608(s32, s32, s32);
 *   line 2617  extern void func_8012B178(s32, s32);
 *   line 2618  extern void func_8012AD80(s32);
 *   line 2619  extern s32  func_8012B030(u8 *);
 *   line 2620  extern s32  func_8012B744(void *, void *);
 *   line 2621  extern s32  func_8012BE98(s32, u16 *);
 *   line 4926  extern s32  func_80184988(s32 a0);
 */

extern s32 func_8016F1AC(void);
extern void func_8014B12C(void);
extern s32 func_8012B608(s32 a0, s32 a1, s32 a2);
extern void func_8012B178(s32 a0, s32 a1);
extern void func_8012AD80(s32 a0);
extern s32 func_8012B030(u8 *a0);
extern s32 func_8012B744(void *a0, void *a1);
extern s32 func_8012BE98(s32 a0, u16 *a1);

s32 func_80184988(s32 a0) {
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

s32 func_80184B50(s32 a0) {
    if (func_8016F1C4() != 0) {
        return 0;
    }
    if (((s32 (*)(void))func_8014B12C)() != 0) {
        return 2;
    }
    return 1;
}


extern void (*D_801E024C[])(void);

void func_80184B98(void *a0) {
    D_801E024C[*(u16 *)((s32)a0 + 0x2)]();
}


void func_80184BD4(void) {
}

void func_80184BDC(void) {
}

void func_80184BE4(void) {
}

void func_80184BEC(void) {
}

void func_80184BF4(void) {
}


extern void func_80016714(void *a0, s32 a1);
extern void func_8012CAE4(void *a0);


void func_80184BFC(void *a0) {

    extern s32 D_801E67F0;
    extern s32 D_801E66FC;
    func_80016714(&D_801E67F0, 0x14);
    D_801E66FC = 0;
    func_8012CAE4(a0);
}


void func_80184C40(void) {
}


/* §37 lever (A): conform to the TU's existing decl verbatim (TU lines 6430 /
 * 6862 both say `void`); the s32 return is recovered by a cast at the call
 * site below. Decl-only change => zero bytes move. */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32, s32);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_8012E8E0(s32 a0, s32 a1);


void func_80184C48(s32 a0) {

    extern s32 D_801D2DB8[];
    extern s32 D_801E0244[];
    s32 v0;
    s32 result;

    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(a0 + 0x20) = v0;
    if (v0 == 0) {
        func_8012CAE4((void *)a0);
        return;
    }

    func_8001C214(v0, (s32)D_801D2DB8);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0x7FFF, 0x7FFF);

    result = *(s32 *)(a0 + 0x20);
    *(s32 *)(result + 0x4) |= 0x40;
    func_8012E8E0(a0, (s32)D_801E0244);

    *(s16 *)(a0 + 0x2) = 1;
}



extern void func_8018535C(s32 a0);
extern void func_801852E8(s32 a0);
extern void func_801853BC(s32 a0);
extern void func_80185280(s32 a0);

void func_80184CD0(s32 a0) {

    extern void (*D_801E0524[])(s32);
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
                    func_8018535C(a0);
                } else {
                    func_801852E8(a0);
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
                    func_801853BC(a0);
                } else {
                    func_80185280(a0);
                }
                *(s16 *)(a0 + 0xE8) = 1;
            }
        }
        break;
    case 3:
        if (*(u16 *)(a0 + 0x2) != 2 || *(u16 *)(a0 + 0x34) == 0) {
            func_801852E8(a0);
        }
        break;
    case 4:
        if (*(u16 *)(a0 + 0x2) != 2 || *(u16 *)(a0 + 0x34) == 0) {
            func_80185280(a0);
        }
        break;
    }

    D_801E0524[*(u16 *)(a0 + 0x2)](a0);
}



extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001C214(s32, s32);
extern void func_8001C97C(s32 a0);
extern void func_8001D0E8(s32 arg0, s32 arg1, s32 arg2);
extern void func_80185280(s32 a0);
extern void *func_80185650(void *a0);



void func_80184EA8(s32 a0) {

    extern s32 D_801E0254[][2];
    extern u32 D_801E026C;
    extern u32 D_801E0288;
    extern s16 D_801E0294[];
    extern Blk12_801854C4_80184EA8 D_801E027C;
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
    p = &D_801E0294[idx];
    switch (idx) {
    case 7:
    case 9:
    case 10:
    case 12:
        func_8001C810(v0, D_801E0254[*p][0]);
        *(s32 *)(v0 + 4) |= 0x8040;
        break;
    default:
        func_8001C214(v0, D_801E0254[*p][0]);
        break;
    }

    func_8001C97C(D_801E0254[*p][1]);
    func_8001D0E8(*(s32 *)(a0 + 0x20), 0xC8, 0xB4);
    *(s32 *)(a0 + 0x58) = (u32)&D_801E026C | 0x40000000;
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x20) = (s32)&D_801E0288;
    *(s16 *)(a0 + 0xE8) = 0;
    *(Blk12_801854C4_80184EA8 *)(a0 + 0xEC) = D_801E027C;
    *(s16 *)(a0 + 0x10A) = 6;
    func_80185280(a0);
    *(s32 *)(a0 + 0xDC) = (s32)func_80185650;
}




extern void func_80185754(void *a0);
extern int func_80178970(void);
extern void func_80178D18(void);

void func_80185048(void *a0) {
    switch (*(u16 *)((s32)a0 + 0x34)) {
    case 0:
        break;
    case 1:
        func_80185754(a0);
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



extern s32 func_80184B50(s32 a0);
extern void func_801852E8(s32 a0);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern void func_801858D0(void);

void func_801850C4(s32 a0) {
    s32 s0;
    u16 v0;
    u16 v1;

    if (func_80184B50(a0) == 2) {
        func_801852E8(a0);
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
        func_801852E8(s0);
    }

    ((void (*)(s32))func_801858D0)(s0);
}


extern void func_801858D0(void);
    void func_80185190(void) {
        func_801858D0();
    }



extern s32 func_80184B50(s32 a0);
extern void func_80185280(s32 a0);
extern s32 func_8012BEE8(s32 a0);
extern void func_8012E688(s32 param_1, u16 param_2, u16 param_3);
extern void func_801858D0(void);

void func_801851B0(s32 a0) {
    if (func_80184B50(a0) == 2) {
        func_80185280(a0);
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
        func_80185280(a0);
    } else {
        ((void (*)(s32))func_801858D0)(a0);
    }
}


extern void func_801858D0(void);

void func_80185280(s32 a0) {
    extern s32 D_801E0258[][2];
    extern s16 D_801E0294[];
    *(s16 *)(a0 + 0x2) = 2;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0xFE) = 0;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x24) = D_801E0258[D_801E0294[*(s16 *)(a0 + 0x70)]][0];
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0xB0) = 0;
    func_801858D0();
}




extern void func_801858D0(void);

void func_801852E8(s32 a0) {

    extern s32 D_801E0254[][2];
    extern s16 D_801E0294[];
    s32 idx_val, ptr_val, data_val;

    *(s16 *)(a0 + 0x2) = 0x4;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0xFE) = 0x600;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x102) = 0;
    idx_val = D_801E0294[*(s16 *)(a0 + 0x70)];
    ptr_val = *(s32 *)(a0 + 0x20);
    data_val = D_801E0254[idx_val][0];
    *(s32 *)(ptr_val + 0x24) = data_val;
    *(s16 *)(a0 + 0x84) = 0;
    *(s16 *)(a0 + 0x5C) = 0;
    *(s32 *)(a0 + 0xB0) = 0;
    ((s32 (*)(void))func_801858D0)();
}


void func_8018535C(s32 a0) {

    extern s16 D_801E0294[];
    extern s32 D_801E0254[][2];
    *(s16 *)(a0 + 0x2) = 3;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0xFE) = 0;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x102) = 2;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x24) = D_801E0254[D_801E0294[*(s16 *)(a0 + 0x70)]][0];
    *(s16 *)(a0 + 0x84) = 0;
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0xB0) = 0;
}



extern void func_801858D0(void);

void func_801853BC(s32 a0) {

    extern s16 D_801E0294[];
    extern s32 D_801E0254[][2];
    *(s16 *)(a0 + 0x2) = 1;
    *(s32 *)(a0 + 0x1C) = 8;
    *(s16 *)(a0 + 0xFE) = 0x600;
    *(s16 *)(a0 + 0x34) = 0;
    *(s16 *)(a0 + 0x100) = 0;
    *(s16 *)(a0 + 0x102) = 2;
    *(s32 *)(*(s32 *)(a0 + 0x20) + 0x24) = D_801E0254[D_801E0294[*(s16 *)(a0 + 0x70)]][0];
    *(s16 *)(a0 + 0x5C) = 0x800;
    *(s32 *)(a0 + 0xB0) = 0;
    ((s32 (*)(void))func_801858D0)();
}





void func_8018543C(s32 a0, s32 a1)
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
extern void func_80185A10(s32 a0, s32 a1);

void func_80185494(s32 a0) {
    s32 v0 = func_8012E57C(0x61, (s16)a0);
    if (v0 != 0) {
        if (*(u16 *)((char *)v0 + 0x2) == 2) {
            *(s32 *)((char *)v0 + 0xB0) = 1;
        }
        func_80185A10(a0, 0x3C);
    }
}




extern s32 func_8012E57C(s32 a0, s32 a1);

void func_801854F4(s32 a0) {
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
extern void func_80185A10(s32 a0, s32 a1);

void func_8018553C(s32 a0) {
    s32 v1;

    v1 = func_8012E57C(0x61, (s32)(s16)a0);
    if (v1 != 0) {
        *(s16 *)((char *)v1 + 0x108) = 1;
        func_80185A10(a0, 0x3C);
    }
}




extern s32 func_8012E57C(s32 a0, s32 a1);

void func_8018558C(s32 a0) {
    s32 shift_temp;
    s32 v1;

    shift_temp = ((a0 << 16) >> 16);
    v1 = func_8012E57C(0x61, shift_temp);
    if (v1 != 0) {
        *(s16 *)((char *)v1 + 0x108) = 2;
    }
}


extern s32 func_8012E57C(s32 a0, s32 a1);
s32 func_801855C4(s32 a0) {
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
extern s32 func_801856F4(void *a0);
extern s32 func_80185C8C(void *a0);
extern s32 func_80178BF8();
extern void func_80172710(void);

void *func_80185650(void *a0) {
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
    if (func_801856F4(a0) == 0) {
        return 0;
    }
    if (func_80185C8C(a0) != 0) {
        return 0;
    }
    *(s16 *)((s32)a0 + 0x34) = 1;
    func_80178BF8();
    return (void *)func_80172710;
}





extern void func_8012F2E8(s32 a0, s32 a1, s32 a2);
extern s32 func_8012CB64(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

s32 func_801856F4(void *a0) {

    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    s16 out[3];
    s16 in[3];

    in[0] = D_80126B5E;
    in[1] = D_80126B62;
    in[2] = D_80126B66;
    func_8012F2E8((s32)a0, (s32)in, (s32)out);
    return func_8012CB64((s32)out, -0x80, 0x80, -0x60, 0);
}
